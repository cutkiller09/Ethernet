/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"
#include "cpu_def.h"
#include "cpu_lb.h"
#include "hard_def.h"
#include "interface.h"
#include "ad2s1210.h"

#include "configuration.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/



/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
#define DSPI_TX_FIFO_EMPTY                          (UNS8)0
#define AD2S1210_INIT_CMD_NUMBER                    (UNS16)18
#define AD2S1210_CLEAR_DSPI_BUS                     (UNS32)0x1C000000
#define AD2S1210_TX_DATA_PCS1                       (UNS32)0x10020000

#define AD2S1210_LOS_THRESHOLD_REG                  (UNS32)0x04000088    
#define AD2S1210_DOS_OVERRANGE_THRESHOLD_REG        (UNS32)0x00000089    
#define AD2S1210_DOS_MISMATCH_THRESHOLD_REG         (UNS32)0x0000008A    
#define AD2S1210_DOS_RESET_MAX_THRESHOLD_REG        (UNS32)0x0000008B    
#define AD2S1210_DOS_RESET_MIN_THRESHOLD_REG        (UNS32)0x0000008C
#define AD2S1210_LOT_HIGH_THRESHOLD_REG             (UNS32)0x0000008D
#define AD2S1210_LOT_LOW_THRESHOLD_REG              (UNS32)0x0000008E    
#define AD2S1210_EXCITATION_FREQ_REG                (UNS32)0x00000091
#define AD2S1210_CONTROL_REG                        (UNS32)0x00000092
#define AD2S1210_CONTROL_REG_INIT                   (UNS32)0x0800007E
#define AD2S1210_FAULT_REG                          (UNS32)0x040000FF
#define AD2S1210_FAULT_REG_INIT                     (UNS32)0x08000000
#define AD2S1210_VOLTAGE_CONVERSION                 (REAL32)(127.0/4.82)
#define AD2S1210_DEGREE_CONVERSION                  (REAL32)(127.0/18.0)
#define AD2S1210_FREQUENCY_CONVERSION               (REAL32)0.004096

#define UNS16_MASK                                  (UNS32)0x0000FFFF


/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Local function : ReadAD2S1210                              */
/***************************************************************/
void ReadAD2S1210(UNS8 a_RDC)
{
    UNS32 AD2S1210_spi_command;

    /* Clear Transmit flag */
    DSPI_A.SR.B.TCF = (VUNS32)TRUE;
	
	AD2S1210_spi_command = 0x0;
        
   /* Clear SPI status flags by writing 1 to them */
    DSPI_A.SR.R = 0x98080000;
    
    /* Perform a high pulse > 300ns on the signal SAMPLE_RDCx */
    if (a_RDC == 1)
    {
        I_BSP_In.disc_out_gpio.HW_GPIO_178 = (UNS32)TRUE;
        /* Select chip select of RDC 1 */
        AD2S1210_spi_command = AD2S1210_TX_DATA_PCS1;
    }
    else
    {

    } 
	SIU.GPDO[178].B.PDO = I_BSP_In.disc_out_gpio.HW_GPIO_178;
    Waitus(1); 
    
    /* Read position value and faults register                */
    /* Program the SPI in order to dialog with the AD2S1210   */
    /* 1st command word:                                      */
    /*             CONT     = 1                               */
    /*             CTAS     = 1 (CTAR1)                       */
    /*             EOQ      = 0                               */
    /*             CTCNT    = 1                               */
    /*             TXDATA   = 0x0000                          */
    DSPI_A.PUSHR.R = (AD2S1210_spi_command | (UNS32) 1 << 26) | (UNS32) 1 << 31;

    /* 2nd command word:                                      */
    /*             CONT     = 0                               */
    /*             CTAS     = 1 (CTAR1)                       */
    /*             EOQ      = 1                               */
    /*             CTCNT    = 0                               */
    /*             TXDATA   = 0x0000                          */
    DSPI_A.PUSHR.R = AD2S1210_spi_command | (UNS32) 1 << 27;
    
    /* Wait for the end of the transmission */
    while((BOOLEAN)DSPI_A.SR.B.EOQF != TRUE)
    {
    }

    /* Read two words */
    I_BSP_Out.ad2s1210.TAB_AD2S1210_POSITION = (UNS16)(DSPI_A.POPR.B.RXDATA);
    I_BSP_Out.ad2s1210.fault.data = (UNS8)((DSPI_A.POPR.B.RXDATA) >> 8);
    
    /* Clear SPI status flags by writing 1 to them */
    DSPI_A.SR.R = 0x98080000;
    
    /* Defaut state of SAMPLE_RDCx is forced to 0 */
    I_BSP_In.disc_out_gpio.HW_GPIO_178 = (UNS32)FALSE;
    SIU.GPDO[178].B.PDO = I_BSP_In.disc_out_gpio.HW_GPIO_178;
}


/***************************************************************/
/* Local function : ResetFaultRegister                         */
/***************************************************************/
void ResetFaultRegister(UNS8 a_RDC)
{
    volatile UNS16 dummy_read;
    UNS32 AD2S1210_spi_command;

    /* Clear Transmit flag */
    DSPI_A.SR.B.TCF = (VUNS32)TRUE;
	
	AD2S1210_spi_command = 0x0;
   
   /* Clear SPI status flags by writing 1 to them */
    DSPI_A.SR.R = 0x98080000;
    
    /* Perform a low pulse > 45ns on the signal SAMPLE_RDCx */
    if (a_RDC == 1)
    {
        I_BSP_In.disc_out_gpio.HW_GPIO_178 = (UNS32)FALSE;
		SIU.GPDO[178].B.PDO = I_BSP_In.disc_out_gpio.HW_GPIO_178;
        /* Wait more than 45 ns */
        Waitus(1);
        I_BSP_In.disc_out_gpio.HW_GPIO_178 = (UNS32)TRUE;
        SIU.GPDO[178].B.PDO = I_BSP_In.disc_out_gpio.HW_GPIO_178;
        /* Select chip select of RDC 1 */
        AD2S1210_spi_command = AD2S1210_TX_DATA_PCS1;
        /* Set Mode Select Pin for RDC1 to configuration mode */
        SIU.GPDO[200].B.PDO = (UNS32)TRUE;
	    SIU.GPDO[201].B.PDO = (UNS32)TRUE;

    }
    else
    {

    } 
  
    /**********************************************************/
    /* Program the SPI in order to dialog with the AD2S1210   */
    /* 1st command word:                                      */
    /*             CONT     = 0                               */
    /*             CTAS     = 1 (CTAR1)                       */
    /*             EOQ      = 0                               */
    /*             CTCNT    = 1 (only for the first cmd)      */
    /*             PCSx     = 1                               */
    /*             TXDATA   = 0x00FF (Write to register       */
    /*                                Fault Register )        */
    /**********************************************************/
    DSPI_A.PUSHR.R = AD2S1210_spi_command | AD2S1210_FAULT_REG;
    
    /**********************************************************/
    /* 2nd command word - TXDATA   = 0x00                     */
    /**********************************************************/
    DSPI_A.PUSHR.R = AD2S1210_spi_command | AD2S1210_FAULT_REG_INIT;
    
    /* Wait for the end of the transmission */
    while((BOOLEAN)DSPI_A.SR.B.EOQF != TRUE)
    {
    }
    
    /* Clear the SPI_A input buffer */
    dummy_read = ((UNS16)DSPI_A.POPR.B.RXDATA);
    dummy_read = ((UNS16)DSPI_A.POPR.B.RXDATA);

    /* Perform a low pulse > 45ns on the signal SAMPLE_RDCx */
    if (a_RDC == 1)
    {
        I_BSP_In.disc_out_gpio.HW_GPIO_178 = (UNS32)FALSE;
        SIU.GPDO[178].B.PDO = I_BSP_In.disc_out_gpio.HW_GPIO_178;
        /* Wait more than 45 ns */
        Waitus(1);
        I_BSP_In.disc_out_gpio.HW_GPIO_178 = (UNS32)TRUE;
        SIU.GPDO[178].B.PDO = I_BSP_In.disc_out_gpio.HW_GPIO_178;
        /* Wait more than 16 ns */
        Waitus(1);
        /* Set Mode Select Pin for RDC1 to normal mode */
        SIU.GPDO[200].B.PDO = (UNS32)FALSE;
	    SIU.GPDO[201].B.PDO = (UNS32)FALSE;
    }
    else
    {

    } 
    
}


/***************************************************************/
/* Global function : InitializeAD2S1210                        */
/***************************************************************/
void InitializeAD2S1210(void)
{
    UNS16 i;
    volatile UNS16 dummy_read;
    
    /* Performed the initialization on demand */
    if (I_BSP_conf.ad2s1210_config.F_AD2S1210_perform_config == TRUE)
    {
        /* Clear Transmit flag */
        DSPI_A.SR.B.TCF = (VUNS32)TRUE;
       
       /* Clear SPI status flags by writing 1 to them */
        DSPI_A.SR.R = 0x98080000;
        
        /* Set Mode Select Pin for RDC1 to configuration mode */
		SIU.GPDO[200].B.PDO = (UNS32)TRUE;
	    SIU.GPDO[201].B.PDO = (UNS32)TRUE;
        
        /**********************************************************/
        /* RDC1 on POB_A configuration                            */
        /**********************************************************/
        
        /**********************************************************/
        /* Program the SPI in order to dialog with the AD2S1210   */
        /* 1st command word:                                      */
        /*             CONT     = 0                               */
        /*             CTAS     = 1 (CTAR1)                       */
        /*             EOQ      = 0                               */
        /*             CTCNT    = 1 (only for the first cmd)      */
        /*             PCS1     = 1                               */
        /*             TXDATA   = 0x0088 (Write to register       */
        /*                                LOS Threshold )         */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_LOS_THRESHOLD_REG;
        
        /**********************************************************/
        /* 2nd command word - TXDATA   = LOS Threshold            */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.LOS_THRESHOLD_configuration * AD2S1210_VOLTAGE_CONVERSION));
        
        /**********************************************************/
        /* 3rd command word - TXDATA   = 0x0089 (Write to register*/
        /*                                DOS Overrange Threshold)*/
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_DOS_OVERRANGE_THRESHOLD_REG;
        
        /**********************************************************/
        /* 4th command word - TXDATA   = DOS Overrange Threshold  */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.DOS_OVERRANGE_THRESHOLD_configuration * AD2S1210_VOLTAGE_CONVERSION));
        
        /* Wait DSPI Fifo is empty */
        while ((UNS8)DSPI_A.SR.B.TXCTR != DSPI_TX_FIFO_EMPTY)
        {
        }
        
        /**********************************************************/
        /* 5th command word - TXDATA   = 0x008A (Write to register*/
        /*                               DOS Mismatch Threshold)  */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_DOS_MISMATCH_THRESHOLD_REG;
        
        /**********************************************************/
        /* 6th command word - TXDATA   = DOS Mismatch Threshold   */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.DOS_MISMATCH_THRESHOLD_configuration * AD2S1210_VOLTAGE_CONVERSION));
        
        /**********************************************************/
        /* 7th command word - TXDATA   = 0x008B (Write to register*/
        /*                               DOS Reset Max Threshold) */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_DOS_RESET_MAX_THRESHOLD_REG;
        
        /**********************************************************/
        /* 8th command word - TXDATA   = DOS Reset Max Threshold  */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.DOS_RESET_MAX_THRESHOLD_configuration * AD2S1210_VOLTAGE_CONVERSION));
        
        /* Wait DSPI Fifo is empty */
        while ((UNS8)DSPI_A.SR.B.TXCTR != DSPI_TX_FIFO_EMPTY)
        {
        }
        
        /**********************************************************/
        /* 9th command word - TXDATA   = 0x008C (Write to register*/
        /*                                DOS Reset Min Threshold)*/
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_DOS_RESET_MIN_THRESHOLD_REG;
        
        /**********************************************************/
        /* 10th command word - TXDATA   = DOS Reset Min Threshold */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.DOS_RESET_MIN_THRESHOLD_configuration * AD2S1210_VOLTAGE_CONVERSION));
        
        /**********************************************************/
        /* 11th command word - TXDATA  = 0x008D (Write to register*/
        /*                                 LOT High Threshold)    */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_LOT_HIGH_THRESHOLD_REG;
        
        /**********************************************************/
        /* 12th command word - TXDATA   = LOT High Threshold      */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.LOT_HIGH_THRESHOLD_configuration * AD2S1210_DEGREE_CONVERSION));
        
        /* Wait DSPI Fifo is empty */
        while ((UNS8)DSPI_A.SR.B.TXCTR != DSPI_TX_FIFO_EMPTY)
        {
        }
        
        /**********************************************************/
        /* 13th command word - TXDATA = 0x008E (Write to register */
        /*                                LOT Low Threshold       */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_LOT_LOW_THRESHOLD_REG;
        
        /**********************************************************/
        /* 14th command word - TXDATA   = LOT Low Threshold       */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.LOT_LOW_THRESHOLD_configuration * AD2S1210_DEGREE_CONVERSION));
        
        /**********************************************************/
        /* 15th command word - TXDATA = 0x0091 (Write to register */
        /*                                Excitation Freq POB A   */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_EXCITATION_FREQ_REG;
        
        /**********************************************************/
        /* 16th command word - TXDATA = Excitation Freq POB A     */
        /**********************************************************/    
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | (UNS16_MASK & (UNS32)(I_BSP_conf.ad2s1210_config.FREQ_POBA_configuration * AD2S1210_FREQUENCY_CONVERSION));
        
        /* Wait DSPI Fifo is empty */
        while ((UNS8)DSPI_A.SR.B.TXCTR != DSPI_TX_FIFO_EMPTY)
        {
        }
        
        /**********************************************************/
        /* 17th command word - TXDATA = 0x0092 (Write to register */
        /*                                Control                 */
        /**********************************************************/
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_CONTROL_REG;
        
        /**********************************************************/
        /* 18th command word EOQ = 1 - TXDATA = 0x007E            */
        /**********************************************************/    
        DSPI_A.PUSHR.R = AD2S1210_TX_DATA_PCS1 | AD2S1210_CONTROL_REG_INIT;
        
        /* Wait for the end of the transmission */
        while((BOOLEAN)DSPI_A.SR.B.EOQF != TRUE)
        {
        }
        
        /* Clear the SPI_A input buffer */
        for(i=0; i < AD2S1210_INIT_CMD_NUMBER;i++ )
        {
            dummy_read = ((UNS16)DSPI_A.POPR.B.RXDATA);
        }

        /* Clear SPI status flags by writing 1 to them */
        DSPI_A.SR.R = 0x98080000;

        /* Set Mode Select Pin for RDC1 to normal mode */
        SIU.GPDO[200].B.PDO = (UNS32)FALSE;
	    SIU.GPDO[201].B.PDO = (UNS32)FALSE;
        
        /* Reset All Fault register */
        ResetFaultRegister(1);
    }
    else
    {
    }
}

/***************************************************************/
/* Global function : ReadAllAD2S1210Resolver                   */
/***************************************************************/
void ReadAllAD2S1210Resolver(void)
{
    
    /* Call ReadAD2S1210 for each Resolver activated */
    if (I_BSP_In.ad2s1210_enable.F_AD2S1210_RDC1_perform_acq == TRUE)
    {
        ReadAD2S1210(1);
    }
    else
    {
    }
}

/***************************************************************/
/* Global function : ResetAD2S1210ResolverFaultRegister        */
/***************************************************************/
void ResetAD2S1210ResolverFaultRegister(void)
{
    
    /* Call ReadAD2S1210 for each resolver reset request */
    if (I_BSP_In.ad2s1210_faults_reset.F_AD2S1210_RDC1_faults_reset == TRUE)
    {
        ResetFaultRegister(1);
    }
    else
    {
    }
}

/***************************************************************/
/* Global function : ClearDSPIBBus                             */
/***************************************************************/
void ClearDSPIBBus(void)
{
    volatile UNS16 dummy_read;

    /* Clear Transmit flag */
    DSPI_A.SR.B.TCF = (VUNS32)TRUE;
        
    /* Clear SPI status flags by writing 1 to them */
    DSPI_A.SR.R = 0x98080000;
    
    /* Program the SPI in order to clear the DSPI_A bus:      */
    /*             CONT     = 0                               */
    /*             CTAS     = 1 (CTAR1)                       */
    /*             EOQ      = 1                               */
    /*             CTCNT    = 1                               */
    /*             PCS0-PCS5= 0                               */
    /*             TXDATA   = 0x0000                          */
    DSPI_A.PUSHR.R = AD2S1210_CLEAR_DSPI_BUS;
    
    /* Wait for the end of the transmission */
    while((BOOLEAN)DSPI_A.SR.B.EOQF != TRUE)
    {
    }
    /* Made a dummy read */
    dummy_read = ((UNS16)DSPI_A.POPR.B.RXDATA);
    
    /* Clear SPI status flags by writing 1 to them */
    DSPI_A.SR.R = 0x98080000;
}

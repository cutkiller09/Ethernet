/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"
#include "cpu_def.h"
#include "cpu_lb.h"
#include "etpu_lb.h"
#include "etpu_TIMER_lb.h"
#include "interface.h"
#include "configuration.h"
#include "ad1255.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
BOOLEAN F_AD1255_acquisition_ended;


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
/* TCF=1, TXRXS=0, EOQF=1, TFUF=1, TFFF=0, RFOF=1, RFDF=0, TXCTR=0, TXNXTPTR=0, RXCTR=0, POPNXTPTR=0 */
/* For more information, see MPC5554 document */
#define DSPI_B_STATUS_REGISTER_INIT_CMD       (UNS32)0x98080000

#define FIFO_AD1255_INIT_CMD_SIZE             (UNS8)16
#define FIFO_AD1255_READ_CMD_SIZE             (UNS8)4
#define DSPI_TX_FIFO_SIZE                     (UNS8)4
#define DSPI_TX_FIFO_EMPTY                    (UNS8)0

const UNS32 K_TAB_ad1255_init_cmd[FIFO_AD1255_INIT_CMD_SIZE] =
{
    0x84100050,    
    0x80100000,
    0x80100002,
    0x80100051,    
    0x80100000,
    0x80100008,    
    0x80100052,    
    0x80100000,    
    0x80100000,
    0x80100053,
    0x80100000,    
    0x80100092,    
    0x80100054,    
    0x80100000,    
    0x80100000,    
    0x081000F0
};

const UNS32 K_TAB_ad1255_read_cmd[FIFO_AD1255_READ_CMD_SIZE] =
{
    /* Read command */
    0x84100001,
    0x80100000,
    0x80100000,
    0x08100000
};

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
/* Global function : InitializeAD1255                          */
/***************************************************************/
void InitializeAD1255(void)
{
    UNS8 i, j;
    volatile UNS16 dummy_read;
    
    /* Set end of acquisition flag to FALSE */
    F_AD1255_acquisition_ended = FALSE;  
    
    /* Check for N_PRES_DRDY set to low */
    if (SIU.GPDI[113].R == TRUE)
    {
        /* If set to high then wait 50 ms */
        for (i=0; i<50; i++)
        {
            Waitus(1000);
        }
    }
    else
    {
    }

    /* Clear Transmit flag */
    DSPI_B.SR.B.TCF = (VUNS32)TRUE;

    /* Call function Waitus, to wait (1 ms) for the end of the start of the AD1255 */
    Waitus(1000);

    /* Clear SPI status flags by writing 1 to them */
    DSPI_B.SR.R = DSPI_B_STATUS_REGISTER_INIT_CMD;

    /**********************************************************/
    /* Re-program the SPI in order to dialog with the AD1255  */
    /* Set AD1255 Status register :                           */
    /* 1st command word (Write to the Status register):       */
    /*             CONT     = 1                               */
    /*             CTAS     = 0 (CTAR0)                       */
    /*             EOQ      = 0                               */
    /*             CTCNT    = 1 (only for the first cmd)      */
    /*             PCS0     = 1                               */
    /*             TXDATA   = 0x0050 (Write to the register   */
    /*                                STATUS)                 */
    /* 2nd command word - TXDATA   = 0x0000 (1 byte to write) */
    /* 3rd command word - TXDATA   = 0x0002 (the value 2      */
    /*                    BUFEN=1 (Pressure aqcuisition))     */
    /* 4th command word - TXDATA   = 0x0052 (WREG to the A/D  */
    /*                    Control register)                   */
    /* 5th command word - TXDATA   = 0x0000 (1 byte to write) */
    /* 6th command word with PGA has low - TXDATA   = 0x0000  */
    /*                    (the value 0 (GAIN = 0))            */
    /* 7th command word - TXDATA   = 0x0053                   */
    /*                    (Write to Register DRATE)           */
    /* 8th command word - TXDATA   = 0x0000 (1 byte to write) */
    /* 9th command word - TXDATA   = 0x0092 (the value 0x92)  */
    /* 10th command word - TXDATA   = 0x0054                  */
    /*                    (Write to Register IO)              */
    /* 11th command word - TXDATA   = 0x0000 (1 byte to write)*/
    /* 12th command word - TXDATA   = 0x0000 (the value 0)    */
    /* 13th command word - TXDATA   = 0x0051                  */
    /*                    (Write to MUX Register)             */
    /* 14th command word - TXDATA   = 0x0000 (1 byte to write)*/
    /* 15th command word - TXDATA   = 0x0008 (the value 8     */
    /*                    (Pressure aqcuisition))             */
    /* 16th command word - TXDATA   = 0x00F0(Self-Calibration)*/
    /* (CONT = 0, EOQ = 1)   (Stop read data continusly)      */
    /**********************************************************/
    i = 0;
    while (i < FIFO_AD1255_INIT_CMD_SIZE)
    {
        /* IF there are no SPI commands to be sent */
        if ((UNS8)DSPI_B.SR.B.TXCTR == DSPI_TX_FIFO_EMPTY)
        {
            j = 0;
            while ((i < FIFO_AD1255_INIT_CMD_SIZE) && (j < DSPI_TX_FIFO_SIZE))
            {
                DSPI_B.PUSHR.R = K_TAB_ad1255_init_cmd[i];
                i ++;
                j ++;
            }
        }
        else
        {
        }
    }

    /* Call function Waitus, to wait (7 ms) for the end of the self-calibration of the AD1255 */
    Waitus(7000);

    /* Clear the SPI_C input buffer */
    for(i=0; i < FIFO_AD1255_INIT_CMD_SIZE;i++ )
    {
        dummy_read = ((UNS16)DSPI_B.POPR.B.RXDATA);
    }

    /* Clear SPI status flags by writing 1 to them */
    DSPI_B.SR.R = DSPI_B_STATUS_REGISTER_INIT_CMD;
    
    /* Call EtpuInitializeTimerAD1255 function to initialize the Timer for the AD1255 acquisition */
    EtpuInitializeTimerAD1255();
}


/***************************************************************/
/* Global function : ReadAD1255                                */
/***************************************************************/
UNS32 ReadAD1255(void)
{
    volatile UNS16 dummy_read;
    UNS32 input_byte1;
    UNS32 input_byte2;
    UNS32 input_byte3;
    UNS32 read_input;
    UNS8 i;

    /**********************************************************/
    /* Program the SPI in order to dialog with the AD1255     */
    /* Read previous conversion                               */
    /* 1st command word :                                     */
    /*             CONT     = 1                               */
    /*             CTAS     = 0                               */
    /*             EOQ      = 0                               */
    /*             CTCNT    = 1 (only for the first cmd)      */
    /*             PCS0     = 1                               */
    /*             TXDATA   = 0x0001 (Read Data)              */
    /* 2nd command word - TXDATA   = 0x0000                   */
    /* 3rd command word - TXDATA   = 0x0000                   */
    /* 4th command word - TXDATA   = 0x0000                   */
    /* (CONT = 0, EOQ = 1)                                    */
    /**********************************************************/
    i = 0;
    while (i < FIFO_AD1255_READ_CMD_SIZE)
    {
        /* IF TX FIFO is not full */
        if ((BOOLEAN)DSPI_B.SR.B.TFFF == TRUE)
        {
            DSPI_B.PUSHR.R = K_TAB_ad1255_read_cmd[i];
            i++;
        }
        else
        {
        }
    }

    /* Wait for the end of the transmission */
    while((BOOLEAN)DSPI_B.SR.B.EOQF != TRUE)
    {
    }

    /* Make a "dummy" read */
    dummy_read = ((UNS16)DSPI_B.POPR.B.RXDATA) & (UNS16)0x00FF;
    /* Read three times the received buffer */
    input_byte1 = ((UNS16)DSPI_B.POPR.B.RXDATA) & (UNS16)0x00FF;
    input_byte2 = ((UNS16)DSPI_B.POPR.B.RXDATA) & (UNS16)0x00FF;
    input_byte3 = ((UNS16)DSPI_B.POPR.B.RXDATA) & (UNS16)0x00FF;
    /* Concatenate the 3 received value */
    read_input = (UNS32)((input_byte1 << 16) | (input_byte2 << 8) | input_byte3);

    /* Clear SPI status flags by writing 1 to them */
    DSPI_B.SR.R = DSPI_B_STATUS_REGISTER_INIT_CMD;

    /* Return the result */
    return (read_input);
}


/***************************************************************/
/* Global function : StartAD1255Conversion                     */
/***************************************************************/
void StartAD1255Conversion(void)
{  
    /* IF SPI_B is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_B_enable == (UNS32)TRUE)
    /* THEN */
    {
    
        /* Set end of acquisition flag to FALSE */
        F_AD1255_acquisition_ended = FALSE; 
        
        /* Set N_PRES_SYNC output (GPIO 177) to low level */
        SIU.GPDO[177].B.PDO = FALSE;
        /* Call function Waitus to wait 1 us */
        Waitus(1);
        /* Set N_PRES_SYNC output (GPIO 177) to high level in order to start the conversion */
        SIU.GPDO[177].B.PDO = TRUE;
        
        /* Clear the interrupt bit status of the timeout interrupt */
        ETPU.CISR_B.R = (UNS32)(1 << CHANNEL_0);
        
        /* Enable the interrupt for the timeout of the AD1255 acquisition */
        ETPU.CHAN[(UNS32)AD1255_TIMER_ETPU_CHANNEL].CR.B.CIE = (VUNS32)TRUE;
        
        /* Start a timer of 3 ms */
        SetHSRR(AD1255_TIMER_ETPU_CHANNEL,HSR_TIMER_START);
        
        /* Clear the flag of the IRQ 7 */
        SIU.EISR.R = 0x00000080;
        /* Enable IRQ 7 event (24Bit-ADC Data-Ready indication) */
        SIU.IFEER.B.IFEE7 = (VUNS32)TRUE;
    }
    else
    {
    }
    /* END IF */
}


/***************************************************************/
/* Global function : WaitForEndOfAD1255Conversion              */
/***************************************************************/
void WaitForEndOfAD1255Conversion(void)
{
    /* Wait for end of acquisition of the AD1255 or for the timeout of the acquisition */
    while (F_AD1255_acquisition_ended == FALSE)
    {
    }
}


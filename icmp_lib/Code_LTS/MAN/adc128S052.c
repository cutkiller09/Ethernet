/***************************************************************/
/* FUNCTION : Driver for ADC 128S052                           */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "cpu_def.h"

#include "adc128S052.h"



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
#define DSPI_A_CH0                (UNS32)((0b000 << 3) << 8)
#define DSPI_A_CH1                (UNS32)((0b001 << 3) << 8)
#define DSPI_A_CH2                (UNS32)((0b010 << 3) << 8)
#define DSPI_A_CH3                (UNS32)((0b011 << 3) << 8)
#define DSPI_A_CH4                (UNS32)((0b100 << 3) << 8)
#define DSPI_A_CH5                (UNS32)((0b101 << 3) << 8)
#define DSPI_A_CH6                (UNS32)((0b110 << 3) << 8)
#define DSPI_A_CH7                (UNS32)((0b111 << 3) << 8)

#define DSPI_A_AD128S052_CMD_EOQ  (UNS32)0x08010000
#define DSPI_A_AD128S052_CMD      (UNS32)0x04010000

#define DSPI_A_AD128S052_CH0_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD_EOQ | DSPI_A_CH0)
#define DSPI_A_AD128S052_CH1_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH1)
#define DSPI_A_AD128S052_CH2_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH2)
#define DSPI_A_AD128S052_CH3_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH3)
#define DSPI_A_AD128S052_CH4_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH4)
#define DSPI_A_AD128S052_CH5_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH5)
#define DSPI_A_AD128S052_CH6_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH6)
#define DSPI_A_AD128S052_CH7_CONV_CMD  (UNS32)(DSPI_A_AD128S052_CMD     | DSPI_A_CH7)

#define DSPI_A_CLEAR_FLAG (UNS32)0x90020000


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
/* Global function : InitializeAD128S052                       */
/***************************************************************/
void InitializeAD128S052(void)
{
    volatile UNS16 temp;

    /***************************************/
    /* Program the command to select       */
    /* channel 0 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 1            */
    /*             CTCNT    = 0            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x0000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH0_CONV_CMD;

    /* Wait for Receive FIFO contains one message */
    while (DSPI_A.SR.B.RXCTR != 1)
    {
    }

    /* Read the POPR */
    temp = (UNS16)(DSPI_A.POPR.B.RXDATA);

    /* Clear TCF, EOQF and RDRF flags by writing 1 to them */
    DSPI_A.SR.R = DSPI_A_CLEAR_FLAG;
}

/***************************************************************/
/* Global function : ReadAD128S052                             */
/***************************************************************/
void ReadAD128S052(T_AD128S052Input *a_read_input_PTR)
{
    /***************************************/
    /* Program the first command to select */
    /* channel 1 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x1000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH1_CONV_CMD;

    /***************************************/
    /* Program the command to select       */
    /* channel 2 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x2000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH2_CONV_CMD;

    /***************************************/
    /* Program the command to select       */
    /* channel 3 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x3000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH3_CONV_CMD;

    /***************************************/
    /* Program the command to select       */
    /* channel 4 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x4000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH4_CONV_CMD;
	
	/* Wait for Receive FIFO contains four messages */
    while (DSPI_A.SR.B.RXCTR != 4)
    {
    }

    /* Read the POPR : channel 1 to 4 inputs */
    a_read_input_PTR->channel[0] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);
    a_read_input_PTR->channel[1] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);
    a_read_input_PTR->channel[2] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);
    a_read_input_PTR->channel[3] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);

    /***************************************/
    /* Program the command to select       */
    /* channel 5 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x5000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH5_CONV_CMD;

    /***************************************/
    /* Program the command to select       */
    /* channel 6 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x6000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH6_CONV_CMD;

    /***************************************/
    /* Program the command to select       */
    /* channel 7 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 0            */
    /*             CTCNT    = 1            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x7000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH7_CONV_CMD;
	
	/***************************************/
    /* Program the command to select       */
    /* channel 0 for the next conversion   */
    /*             CONT     = 0            */
    /*             CTAS     = 0            */
    /*             EOQ      = 1            */
    /*             CTCNT    = 0            */
    /*             PCS0     = 1            */
    /*             TXDATA   = 0x0000       */
    /***************************************/
    DSPI_A.PUSHR.R = DSPI_A_AD128S052_CH0_CONV_CMD;

    /* Wait for Receive FIFO contains four messages */
    while (DSPI_A.SR.B.RXCTR != 4)
    {
    }

    /* Read the POPR : channel 4 to 7 inputs */
    a_read_input_PTR->channel[4] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);
    a_read_input_PTR->channel[5] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);
    a_read_input_PTR->channel[6] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);
    a_read_input_PTR->channel[7] = (UNS16)(DSPI_A.POPR.B.RXDATA & 0x0FFF);

    /* Clear TCF, EOQF and RDRF flags by writing 1 to them */
    DSPI_A.SR.R = DSPI_A_CLEAR_FLAG;
}

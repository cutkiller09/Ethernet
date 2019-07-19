/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"
#include "interface.h"
#include "configuration.h"
#include "fifo_lb.h"
#include "cpu_def.h"

#include "ad4005.h"


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
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
const UNS32 K_TAB_AD4005_READ_CMD[AD4005_INPUT_MAX] =
{
    /* Read command */
    (UNS32)0x84000000,
    (UNS32)0x80000000,
    (UNS32)0x80000000,
    (UNS32)0x08000000
};


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Global function : ReadAD4005                                */
/***************************************************************/
void ReadAD4005(T_LEAK_DETECTION_ACQ * a_leak_detection_PTR)
{
    UNS8 i;

    /* IF SPI_D is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_D_enable == TRUE)
    /* THEN */
    {       
        /* Clear SPI status flags by writing 1 to them */
        DSPI_D.SR.R = 0x98080000;
    
        /**********************************************************/
        /* Program the SPI in order to dialog with the AD4005     */
        /* Send command to read 4 data (64 bits) from the AD4005  */
        /* Command word :                                         */
        /*             CONT     = 1                               */
        /*             CTAS     = 0                               */
        /*             EOQ      = 0                               */
        /*             CTCNT    = 1 (only for the first cmd)      */
        /*             PCS0-5   = 0                               */
        /* 1st command word - TXDATA   = 0x0000                   */
        /* 2nd command word - TXDATA   = 0x0000                   */
        /* 3rd command word - TXDATA   = 0x0000                   */
        /* 4th command word - EOQ = 1 - TXDATA   = 0x0000         */
        /* Read input value when available                        */
        /**********************************************************/
        i = 0;
        while(i < (AD4005_INPUT_MAX))
        {
            /* IF TX FIFO is not full */
            if (DSPI_D.SR.B.TFFF == TRUE)
            {
                DSPI_D.PUSHR.R = K_TAB_AD4005_READ_CMD[i];
                i ++;
            }
            else
            {
            }
        }
        
        /* Wait for the end of the transmission */
        while(DSPI_D.SR.B.EOQF != TRUE)
        {
        }
        /* Read data from received buffer */
        for (i=0; i < AD4005_INPUT_MAX; i++)
        {
            a_leak_detection_PTR->buffer[i] = (INT16)((UNS16)DSPI_D.POPR.B.RXDATA);    
        }
        /* Clear SPI status flags by writing 1 to them */
        DSPI_D.SR.R = (UNS32)0x98080000;

    }
    else
    {
    }
    /* END IF */
}

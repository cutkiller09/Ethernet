/***************************************************************/
/* FUNCTION : Library for serial communication interface       */
/*            management                                       */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "cpu_def.h"
#include "cpu_lb.h"
#include "cpu_load.h"
#include "sci_lb.h"


/***************************************************************/
/*                                                             */
/*                        GLOBAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                       GLOBAL CONSTANTS                      */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
#define TDRE_MASK (UNS32)(1 << 31)
#define RDRF_MASK (UNS32)(1 << 29)

#define RECEIVE_ERROR_MASK (UNS32)0x0F000000

/***************************************************************/
/*                                                             */
/*                         LOCAL TYPES                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
T_SCI_BUFFER_RX sci_a_rx;

/***************************************************************/
/* Local function : GetChar_A                                  */
/***************************************************************/
BOOLEAN GetChar_A(UNS8 *a_char_PTR)
{
    BOOLEAN F_char_received;

    /***********************************************/
    /* IF the RDRF bit of ESCI_A.SR is not set     */
    /* THEN                                        */
    /*    RETURN FALSE                             */
    /* ELSE                                        */
    /*   Read the character                        */
    /*   Clear the RDRF bit of ESCI_A.SR register  */
    /*   RETURN TRUE                               */
    /* END IF                                      */
    /***********************************************/
    if (ESCI_A.SR.B.RDRF == 0)
    {
        F_char_received = FALSE;
    }
    else
    {
        *a_char_PTR = (UNS8)ESCI_A.DR.B.D;
        ESCI_A.SR.R &= RDRF_MASK;
        F_char_received = TRUE;
    }
    return(F_char_received);
}

/***************************************************************/
/* Local function : SendChar_A                                 */
/***************************************************************/
void SendChar_A(UNS8 a_char)
{
    /* Wait until a new character may now be written */
    while (ESCI_A.SR.B.TDRE == 0)
    {
    }

    /* Clear TDRE flag  of SCISR_A register */
    ESCI_A.SR.R &= TDRE_MASK;

    /* Write the character in TDR register */
    ESCI_A.DR.B.D = a_char;
}

/***************************************************************/
/* Local function : MaskSCI_A                                 */
/***************************************************************/
void MaskSCI_A(void)
{
    /* Disable reception interrupt of eSCI_A */
    ESCI_A.CR1.B.RIE = (VUNS32)FALSE;
}

/***************************************************************/
/* Global function : UnmaskSCI_A                               */
/***************************************************************/
void UnmaskSCI_A(void)
{
    /* Enable reception interrupt of eSCI_A */
    ESCI_A.CR1.B.RIE = (VUNS32)TRUE;
}

/***************************************************************/
/* Global function : GetSCI_A                                  */
/***************************************************************/
void GetSCI_A(void)
{
    UNS16 i;
    
    /* Call function MaskSCI to disable SCI interrupt */
    MaskSCI_A();

    /* Store the received data into the interface layer */
    if ((I_BSP_Out.scia_buffer_rx.number + sci_a_rx.number) <= (UNS32)MAX_SCI_DATA_IN)
    {
        for (i = 0; i < sci_a_rx.number; i++)
        {
            I_BSP_Out.scia_buffer_rx.TAB_data[I_BSP_Out.scia_buffer_rx.number] = sci_a_rx.TAB_data[i];
            sci_a_rx.TAB_data[i] = (UNS8)0;
            I_BSP_Out.scia_buffer_rx.number++;
        }
        /* reset number of received data */
        sci_a_rx.number = (UNS32)0;
    }
    else
    {
    }
    /* Call function UnmaskSCI to enable SCI interrupt */
    UnmaskSCI_A();
}

/***************************************************************/
/* Global function : SendSCI_A                                 */
/***************************************************************/
void SendSCI_A(void)
{
    UNS16 i;

    /* IF the number of bytes to send does not exceed the size of the table */
    if (I_BSP_In.scia_buffer_tx.number <= (UNS32)MAX_SCI_DATA_OUT)
    {
        /* THEN */
        /* FOR all bytes to send */
        for (i = 0 ; i < I_BSP_In.scia_buffer_tx.number ; i ++)
        {
            /* Call SendChar_A to send one byte */
            SendChar_A(I_BSP_In.scia_buffer_tx.TAB_data[i]);
        }
        /* END FOR */

        /* Set the number of bytes to send to 0 */
        I_BSP_In.scia_buffer_tx.number = 0;
    }
    else
    {
    }
    /* END IF */
}

/***************************************************************/
/* Global function : SendNumber_A                              */
/***************************************************************/
void SendNumber_A(UNS32 a_number, UNS8 a_digit_number)
{
 UNS8 i;
 UNS32 byte;

 /* FOR each digit DO */
 for(i = a_digit_number; i > 0; i--)
 {
    /* Convert digit to ASCII car */
    byte = (a_number >> ((i - 1) * 4)) & (UNS32)0xF;
    byte = (UNS16)((byte > (UNS32)9) ? (byte + (UNS32)55) : (byte + (UNS32)48)) & (UNS16)0x00ff;
    
    /* Call SendChar_A function to sent a byte */
    SendChar_A((UNS8)byte);
 }
 /* END FOR */
}


/***************************************************************/
/* Global function : SCITask_A                                 */
/***************************************************************/
void SCITask_A(void)
{
    UNS8 receive_char;
    volatile BOOLEAN F_char;

    /* Call StartTaskTimeMeasurement function to start time measurement for the SCI task */
    StartTaskTimeMeasurement(SCI_TASK);
    /* IF (OR, NF, FE, PF flags of status register are not set) */
    if ((UNS32)(ESCI_A.SR.R & RECEIVE_ERROR_MASK) == 0u)
    {
        /* Call GetChar_A function to read a char */
        F_char = GetChar_A(&receive_char);
        /* WHILE there is a received char  */
        while(F_char == TRUE)
        {
            /* IF the number of bytes received does not exceed the size of the table */
            if (sci_a_rx.number < (UNS32)MAX_SCI_DATA_IN)
            {
                /* THEN */
                /* Record received byte in SCI reception buffer */
                sci_a_rx.TAB_data[sci_a_rx.number] = receive_char;
                /* Increment current number of received byte */
                sci_a_rx.number++;
            }
            /* ELSE */
            else
            {
               /* Nothing to do */
            }
            /* ENDIF */

            /* Call GetChar_A function to read a char */
            F_char = GetChar_A(&receive_char);
        }
    }
    else
    {
        F_char = GetChar_A(&receive_char);

        ESCI_A.SR.R = RECEIVE_ERROR_MASK;
    }

    /* Call StopTaskTimeMeasurement function to stop time measurement for the SCI task */
    StopTaskTimeMeasurement(SCI_TASK);
}

/***************************************************************/
/* Global function : InitializeSCI_Lb                          */
/***************************************************************/
void InitializeSCI_Lb(void)
{
    UNS8 i;
        
    /* Initialize data for SCI library */
    for (i = 0; i < MAX_SCI_DATA_IN; i++)
    {
        sci_a_rx.TAB_data[i] = (UNS8)0;
    }
    sci_a_rx.number = (UNS32)0;
}

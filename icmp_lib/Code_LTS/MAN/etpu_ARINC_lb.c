/***************************************************************/
/* FUNCTION : eTPU arinc library services                      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"

#include "interface.h"
#include "fifo_lb.h"

#include "etpu_lb.h"
#include "etpu_ARINC_lb.h"


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
/*                       LOCAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* ---- ARINC LIBRARY FUNCTIONS ---- */
#define K_LABEL_MASK (UNS32)0x000000FF

/* eTPU ARINC429 RX function */
#define ETPU_A429_RX_SCR_INIT                  (UNS32)0x00000000
#define ETPU_HSR_INIT_RX                       (UNS32)0x7
#define ETPU_A429_MASTER_RX_FCT_NB             (UNS8) 0
#define ETPU_A429_SLAVE_RX_FCT_NB              (UNS8) 1
#define ETPU_A429_RX_OFFSET_STATUS             (UNS8) 4
#define ETPU_A429_RX_OFFSET_BITTIME            (UNS8) 8
#define ETPU_A429_RX_OFFSET_PTR_BUFFER_CURRENT (UNS8) 12
#define ETPU_A429_RX_OFFSET_PTR_BUFFER_END     (UNS8) 16
#define ETPU_A429_RX_OFFSET_BUFFER_START       (UNS8) 28
#define ETPU_RX_MESSAGE_VOID                   (UNS32)0x00000000

/* eTPU ARINC429 TX function */
#define ETPU_A429_TX_SCR_INIT                  (UNS32)0x00000000
#define ETPU_HSR_INIT_TX                       (UNS32)0x7
#define ETPU_HSR_REQUEST_TX                    (UNS32)0x5
#define ETPU_A429_MASTER_TX_FCT_NB             (UNS8) 2
#define ETPU_A429_SLAVE_TX_FCT_NB              (UNS8) 3
#define ETPU_A429_TX_OFFSET_BITTIME            (UNS8) 8
#define ETPU_A429_TX_OFFSET_PTR_BUFFER_CURRENT (UNS8) 12
#define ETPU_A429_TX_OFFSET_PTR_BUFFER_END     (UNS8) 16
#define ETPU_A429_TX_OFFSET_BUFFER_START       (UNS8) 20
#define ETPU_TX_MESSAGE_VOID                   (UNS32)0x00000000
#define ETPU_A429_TX_CLEAR_PARITY              (UNS32)0x7FFFFFFF
#define TX_STATUS_IDLE                         ((UNS32) 0x00000000)

/* ARINC protocol */
#define ETPU_ARINC_LABEL_MSK                   (UNS32)0x000000FF
#define ETPU_ARINC_DATA_MSK                    (UNS32)0xFFFFFF00
#define ETPU_ARINC_LABEL_OFFSET                (UNS32) 24
#define ETPU_ARINC_DATA_OFFSET                 (UNS32) 8

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


/***************************************************************/
/* Local function : InvertDataAndLabelFieldToEtpuTxBuffer      */
/***************************************************************/
UNS32 InvertDataAndLabelFieldToEtpuTxBuffer(UNS32 a_message)
{
    /* Invert data and label fields */
    a_message = (UNS32)(((a_message & ETPU_ARINC_LABEL_MSK) << ETPU_ARINC_LABEL_OFFSET)
                | ((a_message & ETPU_ARINC_DATA_MSK) >> ETPU_ARINC_DATA_OFFSET));

    return a_message;
}


/***************************************************************/
/* Local function : InvertDataAndLabelFieldFromEtpuRxBuffer    */
/***************************************************************/
UNS32 InvertDataAndLabelFieldFromEtpuRxBuffer(UNS32 a_message)
{
    /* Invert data and label fields */
    a_message = (UNS32)(((a_message >> ETPU_ARINC_LABEL_OFFSET) & ETPU_ARINC_LABEL_MSK)
                | ((a_message << ETPU_ARINC_DATA_OFFSET) & ETPU_ARINC_DATA_MSK));

    return a_message;
}


/***************************************************************/
/* Global function : EtpuInitializeA429Rx                      */
/***************************************************************/
UNS32 EtpuInitializeA429Rx(T_Etpu_fnc * a_RX_function_PTR, UNS32 a_baudrate, UNS8 a_RX_buffer_size)
{
    UNS32 parameter_end_add;
    UNS32 *ram_PTR;

    /* Clear channel priority to disable channels */
    ETPU.CHAN[a_RX_function_PTR->channel].CR.B.CPR = (VUNS32)ETPU_PRIORITY_DISABLED;
    ETPU.CHAN[a_RX_function_PTR->channel + 1].CR.B.CPR = (VUNS32)ETPU_PRIORITY_DISABLED;

    /* Configure channels for ARINC429 Rx*/
    ETPU.CHAN[a_RX_function_PTR->channel].SCR.R = ETPU_A429_RX_SCR_INIT;
    ETPU.CHAN[a_RX_function_PTR->channel + 1].SCR.R = ETPU_A429_RX_SCR_INIT;

    /* parameter_start_add is a relative address */
    /* The function parameter start address value must be a multiple of 8 */
    /* The value has to be multiplied by 8 to get the absolute parameter address seen at host side */
    /* -> Check the parameter is a multiple of 8. */
    /* If not, increment the address to have the next multiple of 8 */
    if (((a_RX_function_PTR->parameter_start_add) % 8u) != 0u)
    {
        a_RX_function_PTR->parameter_start_add = a_RX_function_PTR->parameter_start_add
        + (8u -((a_RX_function_PTR->parameter_start_add) % 8u));
    }
    else
    {
    }

    /* Master channel configuration */
    /*   - CIE  = 1                            Interrupt enabled for master channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 1                            Alternate entry table used           */
    /*   - CFS  = ETPU_A429_MASTER_RX_FCT_NB                                        */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_RX_function_PTR->channel].CR.R = (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                                                 (UNS32)(a_RX_function_PTR->priority << ETPU_SCR_CPR_OFFSET) +
                                                 (UNS32)(ALTERNATE_TABLE << ETPU_SCR_ETCS_OFFSET) +
                                                 (UNS32)(ETPU_A429_MASTER_RX_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                                                 (a_RX_function_PTR->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    /* Slave channel configuration */
    /*   - CIE  = 0                            Interrupt disabled for slave channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 1                            Alternate entry table used           */
    /*   - CFS  = ETPU_A429_SLAVE_RX_FCT_NB                                         */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_RX_function_PTR->channel + 1].CR.R = (UNS32)(a_RX_function_PTR->priority << ETPU_SCR_CPR_OFFSET) +
                                                     (UNS32)(ALTERNATE_TABLE << ETPU_SCR_ETCS_OFFSET) +
                                                     (UNS32)(ETPU_A429_SLAVE_RX_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                                                     (a_RX_function_PTR->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    /* Initialise RAM function area to 0 */
    /* Get the end of parameter area address */
    parameter_end_add = (UNS32)(a_RX_function_PTR->parameter_start_add
                               + (UNS32)ETPU_A429_RX_OFFSET_BUFFER_START
                               + (UNS32)(4 * a_RX_buffer_size));

    /* Set data RAM to 0 */
    ram_PTR = (UNS32 *) (a_RX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
        *ram_PTR = 0x0;
        ram_PTR ++;
    }

    /* Initialise function parameters */
    /* - Rx BitTime */
    ram_PTR = (UNS32 *)(a_RX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_RX_OFFSET_BITTIME );
    *ram_PTR = a_baudrate;

    /* - Set buffer current pointer to the beginning of the Rx buffer */
    ram_PTR = (UNS32 *)(a_RX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_RX_OFFSET_PTR_BUFFER_CURRENT);
    *ram_PTR = (UNS32)(a_RX_function_PTR->parameter_start_add + (UNS32)ETPU_A429_RX_OFFSET_BUFFER_START);

    /* - Rx buffer end address */
    ram_PTR = (UNS32 *)(a_RX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_RX_OFFSET_PTR_BUFFER_END);
    *ram_PTR = (UNS32)(a_RX_function_PTR->parameter_start_add
                      + (UNS32)ETPU_A429_RX_OFFSET_BUFFER_START
                      + (UNS32)(4 * (a_RX_buffer_size - 1)));

    /* Request initialisation HSR to master channel*/
    ETPU.CHAN[a_RX_function_PTR->channel].HSRR.R = ETPU_HSR_INIT_RX;

    /* Return end of parameter area address */
    return parameter_end_add;
}


/***************************************************************/
/* Global function : EtpuGetAllNewMessages                     */
/***************************************************************/
void EtpuGetAllNewMessages(UNS32 a_parameter_start, UNS8 a_RX_buffer_size, T_FIFOQueue * a_queue_PTR)
{
    UNS32 *message_PTR;
    UNS32 message;
    UNS8 i;

    /* Set message pointer to the first message of the eTPU ARINC RX buffer */
    message_PTR = (UNS32*) (a_parameter_start + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_RX_OFFSET_BUFFER_START);

    /* Get all messages of ARINC RX eTPU circular buffer */
    for (i = 1; i <= a_RX_buffer_size; i++)
    {
        /* IF received message is not null */
        if ( *message_PTR != ETPU_RX_MESSAGE_VOID)
        {
            /* THEN */
            /* Call InvertDataAndLabelFieldFromEtpuRxBuffer function to invert current message */
            message = InvertDataAndLabelFieldFromEtpuRxBuffer(*message_PTR);
            /* Call PushElement function to save current message into the FIFO a_queue_PTR*/
            PushElement(message, a_queue_PTR);
            /* Clear message from eTPU RAM buffer */
            *message_PTR = ETPU_RX_MESSAGE_VOID;
            /* Next ARINC RX message */
            message_PTR ++;
        }
        else
        {
        }
        /* END IF */
    }
}


/***************************************************************/
/* Global function : EtpuInitializeA429Tx                      */
/***************************************************************/
UNS32 EtpuInitializeA429Tx(T_Etpu_fnc * a_TX_function_PTR, UNS32 a_baudrate, UNS8 a_TX_buffer_size)
{
    UNS32 parameter_end_add;
    UNS32 *ram_PTR;

    /* Clear channel priority to disable channels */
    ETPU.CHAN[a_TX_function_PTR->channel].CR.B.CPR = (VUNS32)ETPU_PRIORITY_DISABLED;
    ETPU.CHAN[a_TX_function_PTR->channel + 1].CR.B.CPR = (VUNS32)ETPU_PRIORITY_DISABLED;

    /* Configure channels for ARINC429 Tx*/
    ETPU.CHAN[a_TX_function_PTR->channel].SCR.R = ETPU_A429_TX_SCR_INIT;
    ETPU.CHAN[a_TX_function_PTR->channel + 1].SCR.R = ETPU_A429_TX_SCR_INIT;

    /* !!! parameter_start_add is a relative address for the eTPU */
    /* The function parameter start address value must be a multiple of 8 */
    /* The value has to be multiply by to get the absolute parameter address seen at host side */
    /* -> Check the parameter is a multiple of 8. */
    /* If not, increment the address to have the next multiple of 8 */
    if (((a_TX_function_PTR->parameter_start_add) % 8u) != 0u)
    {
        a_TX_function_PTR->parameter_start_add = a_TX_function_PTR->parameter_start_add
        + (8u -((a_TX_function_PTR->parameter_start_add) % 8u));
    }
    else
    {
    }

    /* Master channel configuration */
    /*   - CIE  = 0                            Interrupt disabled                   */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 1                            Alternate entry table used           */
    /*   - CFS  = ETPU_A429_MASTER_TX_FCT_NB                                        */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_TX_function_PTR->channel].CR.R = (UNS32)(a_TX_function_PTR->priority << ETPU_SCR_CPR_OFFSET) +
                                                 (UNS32)(ALTERNATE_TABLE << ETPU_SCR_ETCS_OFFSET) +
                                                 (UNS32)(ETPU_A429_MASTER_TX_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                                                 (a_TX_function_PTR->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    /* Slave channel configuration */
    /*   - CIE  = 0                            Interrupt disabled                   */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 1                            Alternate entry table used           */
    /*   - CFS  = ETPU_A429_SLAVE_TX_FCT_NB                                         */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_TX_function_PTR->channel + 1].CR.R = (UNS32)(a_TX_function_PTR->priority << ETPU_SCR_CPR_OFFSET) +
                                                     (UNS32)(ALTERNATE_TABLE << ETPU_SCR_ETCS_OFFSET) +
                                                     (UNS32)(ETPU_A429_SLAVE_TX_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                                                     (a_TX_function_PTR->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    /* Initialise RAM function area to 0 */
    /* Get the end of parameter area address */
    parameter_end_add = (UNS32)(a_TX_function_PTR->parameter_start_add
                               + (UNS32)ETPU_A429_TX_OFFSET_BUFFER_START
                               + (UNS32)(4 * a_TX_buffer_size));

    /* Set data RAM to 0 */
    ram_PTR = (UNS32 *) (a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
        /* SET data RAM to zero */
        *ram_PTR = (UNS32)0x0;
        ram_PTR ++;
    }

    /* Initialise function parameters */
    /* - Tx BitTime */
    ram_PTR = (UNS32 *)(a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_BITTIME );
    *ram_PTR = a_baudrate;

    /* - Set buffer current pointer to the beginning of the Tx buffer */
    ram_PTR = (UNS32 *)(a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_PTR_BUFFER_CURRENT);
    *ram_PTR = (UNS32)(a_TX_function_PTR->parameter_start_add + (UNS32)ETPU_A429_TX_OFFSET_BUFFER_START);

    /* - Tx buffer end address */
    ram_PTR = (UNS32 *)(a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_PTR_BUFFER_END);
    *ram_PTR = (UNS32)(a_TX_function_PTR->parameter_start_add
                      + (UNS32)ETPU_A429_TX_OFFSET_BUFFER_START
                      + (UNS32)(4 * (a_TX_buffer_size - 1)));

    /* Request initialisation HSR to master channel*/
    ETPU.CHAN[a_TX_function_PTR->channel].HSRR.R = ETPU_HSR_INIT_TX;

    /* Return end of parameter area address */
    return parameter_end_add;
}


/***************************************************************/
/* Global function : EtpuWriteNewMessage                       */
/***************************************************************/
void EtpuWriteNewMessage(UNS32 a_parameter_start, UNS32 a_message, UNS8 a_TX_buffer_size)
{
    UNS32 *ram_PTR;
    UNS32 message_number;

    /* Get 1st free position in TX buffer */
    ram_PTR = (UNS32*) (a_parameter_start + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_BUFFER_START);
    message_number = 0;
    while ((*ram_PTR != ETPU_TX_MESSAGE_VOID) && (message_number < a_TX_buffer_size))
    {
        ram_PTR += 1;
        message_number++;
    }

    /* Check the end of the buffer is not reached and the label id is not 0 */
    if (( message_number < a_TX_buffer_size ) &&
        ( (a_message & K_LABEL_MASK) != 0u  ))
    {
        /* Clear parity bit in the message to send */
        a_message = ETPU_A429_TX_CLEAR_PARITY & a_message;

        /* Write message into eTPU buffer */
        *ram_PTR = InvertDataAndLabelFieldToEtpuTxBuffer(a_message);
    }
    else
    {
        /* Do not write message in transmission buffer */
    }
}


/***************************************************************/
/* Global function : EtpuSendAllNewMessages                    */
/***************************************************************/
void EtpuSendAllNewMessages(T_Etpu_fnc * a_TX_function_PTR, UNS8 a_TX_buffer_size)
{
    UNS32 *ram_PTR;
    UNS32 *TX_start_PTR; 
    UNS32 temp;
    UNS32 message_number;

    temp = (*(UNS32*)(a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS+ (UNS32)ETPU_A429_TX_OFFSET_BITTIME)) >> 24;
    /* Check if eTPU is not curently transmitting */
    if ( temp == TX_STATUS_IDLE )
    {
        /* Get 1st message to send in TX buffer */
        TX_start_PTR = (UNS32 *) (a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_BUFFER_START);
        message_number = 0;
        while ((*TX_start_PTR == ETPU_TX_MESSAGE_VOID) && (message_number < a_TX_buffer_size))
        {
            TX_start_PTR += 1;
            message_number ++;
        }

        /* Check if messages need to be sent */
        if ( message_number < a_TX_buffer_size )
        {
            /* Set TX buffer current position at ram_PTR address */
            /* !! Relative address !! */
            ram_PTR = (UNS32 *) (a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_PTR_BUFFER_CURRENT);
            temp = (UNS32)TX_start_PTR - ETPU_DATA_RAM_START_ABS;
            *ram_PTR = temp;

            /* Request transmission setting HSR 5 on master channel*/
            ETPU.CHAN[a_TX_function_PTR->channel].HSRR.R = ETPU_HSR_REQUEST_TX;
        }
        else
        {
        }
    }
    else
    {
    }
}


/***************************************************************/
/* Global function : DisableInterruptOnARINCChannel            */
/***************************************************************/
void DisableInterruptOnARINCChannel(UNS8 a_channel)
{
    /* Set bit CIE of register CR for current channel to 0 */
    ETPU.CHAN[ETPU_A_OFFSET+a_channel].CR.B.CIE = (VUNS32)FALSE;
}

/***************************************************************/
/* Global function : EnableInterruptOnARINCChannel             */
/***************************************************************/
void EnableInterruptOnARINCChannel(UNS8 a_channel)
{
    /* Set bit CIE of register CR for current channel to 0 */
    ETPU.CHAN[ETPU_A_OFFSET+a_channel].CR.B.CIE = (VUNS32)TRUE;
}

/***************************************************************/
/* Global function : EtpuMonitorA429RxParameters               */
/***************************************************************/
BOOLEAN EtpuMonitorA429RxParameters(T_Etpu_fnc * a_RX_function_PTR, UNS32 a_baudrate, UNS8 a_RX_buffer_size)
{
    UNS32 *ram_PTR;
    BOOLEAN F_error;

    F_error = FALSE;

    /* Check function parameters */
    /* - Rx BitTime */
    ram_PTR = (UNS32 *)(a_RX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_RX_OFFSET_BITTIME );
    if((*ram_PTR & ETPU_CLEAR_MSB) != a_baudrate)
    {
        F_error = TRUE;
    }
    else
    {

    }

    /* - Rx buffer end address */
    ram_PTR = (UNS32 *)(a_RX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_RX_OFFSET_PTR_BUFFER_END);
    if((*ram_PTR & ETPU_CLEAR_MSB) != (UNS32)(a_RX_function_PTR->parameter_start_add
            + (UNS32)ETPU_A429_RX_OFFSET_BUFFER_START
            + (UNS32)(4 * (a_RX_buffer_size - 1))))
    {
        F_error = TRUE;
    }
    else
    {

    }

    /* Return end of parameter area address */
    return F_error;
}

/***************************************************************/
/* Global function : EtpuMonitorA429TxParameters               */
/***************************************************************/
BOOLEAN EtpuMonitorA429TxParameters(T_Etpu_fnc * a_TX_function_PTR, UNS32 a_baudrate, UNS8 a_TX_buffer_size)
{
    UNS32 *ram_PTR;
    BOOLEAN F_error;

    F_error = FALSE;

    /* Check function parameters */
    /* - Tx BitTime */
    ram_PTR = (UNS32 *)(a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_BITTIME );
    if((*ram_PTR & ETPU_CLEAR_MSB) != a_baudrate)
    {
        F_error = TRUE;
    }
    else
    {

    }

    /* - Tx buffer end address */
    ram_PTR = (UNS32 *)(a_TX_function_PTR->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_A429_TX_OFFSET_PTR_BUFFER_END);
    if((*ram_PTR & ETPU_CLEAR_MSB) != (UNS32)(a_TX_function_PTR->parameter_start_add
            + (UNS32)ETPU_A429_TX_OFFSET_BUFFER_START
            + (UNS32)(4 * (a_TX_buffer_size - 1))))
    {
        F_error = TRUE;
    }
    else
    {

    }

    /* Return end of parameter area address */
    return F_error;
}

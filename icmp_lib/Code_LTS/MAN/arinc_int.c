/***************************************************************/
/* FUNCTION : ARINC interface                                  */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"


#include "cpu_lb.h"
#include "cpu_def.h"
#include "hard_def.h"
#include "interface.h"
#include "configuration.h"
#include "fifo_lb.h"
#include "etpu_lb.h"
#include "etpu_ARINC_lb.h"
#include "cpu_load.h"

#include "arinc_int.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
T_FIFOQueue TAB_arinc_fifo_rx[ARINC_RX_NB];


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
/* Communication buffer size */
#define ARINC_RX_BUFFER_SIZE        (UNS8)1

/* ARINC baudrate */
/* High speed -> 100kHz */
#define ARINC_HIGH_SPEED            (BOOLEAN)1
#define ARINC_BAUDRATE_HIGH_SPEED   (UNS32)(ETPU_SYSTEM_CLOCK_TCR1 / 100000u)
/* Low speed -> 12.5kHz */
#define ARINC_BAUDRATE_LOW_SPEED    (UNS32)(ETPU_SYSTEM_CLOCK_TCR1 / 12500u)

#define ARINC_RX_FILTER_TAB_SIZE    (UNS32)512

/* eTPU ARINC IT clear flag */
#define ARINC_RX1_CLEAR_ETPU_IT     (UNS32)0x00000200 /* ETPU_A channel 0 */
#define ARINC_RX2_CLEAR_ETPU_IT     (UNS32)0x00000800 /* ETPU_A channel 1 */
#define ARINC_RX3_CLEAR_ETPU_IT     (UNS32)0x00002000 /* ETPU_A channel 2 */
#define ARINC_RX4_CLEAR_ETPU_IT     (UNS32)0x00008000 /* ETPU_A channel 3 */
#define ARINC_RX5_CLEAR_ETPU_IT     (UNS32)0x00020000 /* ETPU_A channel 4 */



/***************************************************************/
/*                                                             */
/*                        LOCAL TYPES                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
T_Etpu_fnc TAB_etpu_ARINC_channel[ETPU_NUMBER_MAX][ETPU_CHANNEL_NUMBER_MAX];
UNS16 TAB_arinc_rx_robustness_nbr_it[ARINC_RX_NUMBER];

/***************************************************************/
/* Local function : ConvertARINCSpeed                          */
/***************************************************************/
UNS32 ConvertARINCSpeed (BOOLEAN a_arinc_speed)
{
    UNS32 arinc_baudrate;

    if ( a_arinc_speed == ARINC_HIGH_SPEED )
    {
        arinc_baudrate = ARINC_BAUDRATE_HIGH_SPEED;
    }
    else
    {
        arinc_baudrate = ARINC_BAUDRATE_LOW_SPEED;
    }

    return (arinc_baudrate);
}


/***************************************************************/
/* Local function : InitializeARINCChannels                    */
/***************************************************************/
void InitializeARINCChannels(void)
{
    UNS8 i;

    /* Initialize structure parameters               */
    /*   -> loop on all eTPU A channels              */
    /*   -> Priority Low by default */
    /*   -> initialise parameter start address to 0  */
    for (i = 0; i < ETPU_CHANNEL_NUMBER_MAX; i++)
    {
        TAB_etpu_ARINC_channel[ETPU_A][i].channel = ETPU_A_OFFSET + i;
        TAB_etpu_ARINC_channel[ETPU_A][i].priority = ETPU_PRIORITY_LOW;
        TAB_etpu_ARINC_channel[ETPU_A][i].parameter_start_add = 0;
    }

	/*   -> Priority High for channel 0 to 13 (RX and TX High speed) */
	TAB_etpu_ARINC_channel[ETPU_A][0-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][1-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][2-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][3-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][4-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][5-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][6-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][7-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][8-0].priority = ETPU_PRIORITY_HIGH;
	TAB_etpu_ARINC_channel[ETPU_A][9-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][10-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][11-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][12-0].priority = ETPU_PRIORITY_HIGH;
    TAB_etpu_ARINC_channel[ETPU_A][13-0].priority = ETPU_PRIORITY_HIGH;

}


/***************************************************************/
/* Local function : InitializeARINCTxChannels                  */
/***************************************************************/
void InitializeARINCTxChannels(void)
{
    UNS32 arinc_baudrate_channel;

    /* Initialize each ARINC channels with library service */
    /* The starting address for a channel parameters is the end of the previous channel parameter area */
    TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_1_HI].parameter_start_add = data_free_ram;

    /* Call EtpuInitializeA429Tx function to Initialize ARINC output bus and get address for next channel */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_TX1);
    TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_2_HI].parameter_start_add =
        EtpuInitializeA429Tx(&TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_1_HI], arinc_baudrate_channel, I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[0]);
	
	/* Call EtpuInitializeA429Tx function to Initialize ARINC output bus and get address for next channel  */
    /* Save free RAM position in data_free_ram */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_TX2);
    data_free_ram =
        EtpuInitializeA429Tx(&TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_2_HI], arinc_baudrate_channel, I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[1]);
}


/***************************************************************/
/* Local function : InitializeARINCRxChannels                  */
/***************************************************************/
void InitializeARINCRxChannels(void)
{

    UNS32 arinc_baudrate_channel;

     /* Initialize each ARINC channels with library service */
    /* The starting address for a channel parameters is the end of the previous channel parameter area */
    /* The 1st address is located after the ARINC filter table */
    TAB_etpu_ARINC_channel[ETPU_A][AR_IN_1_HI].parameter_start_add = data_free_ram;

    /* Call EtpuInitializeA429Rx function to Initialize ARINC input bus 1 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX1);
    TAB_etpu_ARINC_channel[ETPU_A][AR_IN_2_HI].parameter_start_add =
        EtpuInitializeA429Rx(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_1_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

   /* Call EtpuInitializeA429Rx function to Initialize ARINC input bus 2 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX2);
    TAB_etpu_ARINC_channel[ETPU_A][AR_IN_3_HI].parameter_start_add =
        EtpuInitializeA429Rx(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_2_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuInitializeA429Rx function to Initialize ARINC input bus 3 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX3);
    TAB_etpu_ARINC_channel[ETPU_A][AR_IN_4_HI].parameter_start_add =
        EtpuInitializeA429Rx(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_3_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuInitializeA429Rx function to Initialize ARINC input bus 4 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX4);
    TAB_etpu_ARINC_channel[ETPU_A][AR_IN_XTALK_HI].parameter_start_add =
        EtpuInitializeA429Rx(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_4_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuInitializeA429Rx function to Initialize ARINC input bus 5 */
    /* Save free RAM position in data_free_ram */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX5);
    data_free_ram =
        EtpuInitializeA429Rx(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_XTALK_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);
}


/***************************************************************/
/* Local function : ReportARINCMessages                        */
/***************************************************************/
void ReportARINCMessages(void)
{
    UNS8 i;
    UNS8 j;

    /* Loop on all ARINC transmitters */
    for ( i = 0 ; i < ARINC_TX_NB ; i++ )
    {
        /* Check messages need to be sent on current transmitter */
        if ( I_BSP_In.arinc_tx[i].number > 0u )
        {
            /* Loop on all messages to transmit */
            for ( j = 0 ; j < I_BSP_In.arinc_tx[i].number ; j++ )
            {
                /* Write message to send in eTPU associated buffer */
                EtpuWriteNewMessage(TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_1_HI + (UNS32)(2*i)].parameter_start_add,
                                    I_BSP_In.arinc_tx[i].TAB_label[j],
                                    I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[i]);
            }

            /* Send all messages on current transmitter */
            EtpuSendAllNewMessages(&TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_1_HI + (UNS32)(2*i)],
                                   I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[i]);

            /* Clear the number of messages provided by the APPLICATIVE S/W */
            I_BSP_In.arinc_tx[i].number = 0;
        }
        else
        {
            /* No message to transmit : do nothing */
        }
    }
}


/***************************************************************/
/* Local function : ARINCTaskRX                                */
/***************************************************************/
void ARINCTaskRX(UNS8 a_channel)
{
    /* Increment the number of ARINC tasks triggered this PIT */
    CPT_ARINC_RX_occurrence ++;

    /* Call EtpuGetAllNewMessage function */
    EtpuGetAllNewMessages(TAB_etpu_ARINC_channel[ETPU_A][a_channel].parameter_start_add, ARINC_RX_BUFFER_SIZE, &TAB_arinc_fifo_rx[(UNS32)((a_channel - AR_IN_1_HI)/ 2u)]);
}


/***************************************************************/
/* Local function : ARINCOverflowClear                         */
/***************************************************************/
void ARINCOverflowClear(void)
{
    UNS32 i, j;
    UNS32 bit_mask;

    i = 0;
    j = AR_IN_1_HI;

    /* For each bit of ETPU_CIOSR set corresponding to an ARINC input bus Do */
    while (i < (UNS32)ARINC_RX_NB)
    {
        bit_mask = (1u << j);
        
        /* IF Over Flow is detected */
        if ((ETPU.CIOSR_B.R & bit_mask) == bit_mask)
        {
            /* Set the eTPU Channel Interrupt Status Register ETPU_CIOSR to 2^i */
            /* to clear the eTPU ARINC reception master channel interrupt associated to RXn */
            ETPU.CIOSR_B.R = bit_mask;

            /* Call the ARINCTaskRX function to read ARINC label of bus RXn. */
            ARINCTaskRX((UNS8)j);            
        }
        else
        {
            /* do nothing */
        }

        i ++;
        j = j + 2u;
    }
}


/***************************************************************/
/* Global function : ARINCTaskRX1                              */
/***************************************************************/
void ARINCTaskRX1(void)
{
    /* Clear eTPU ARINC reception master channel interrupt associated to RX 1 */
    ETPU.CISR_B.R = ARINC_RX1_CLEAR_ETPU_IT;
    
    /* If the number of interrupt for current RX is higher than the limit set */
    if (TAB_arinc_rx_robustness_nbr_it[RX1] >
                    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX1])
    /* THEN */
    {
        /* Disable interrupt on current RX */
        DisableInterruptOnARINCChannel((UNS8)AR_IN_1_HI);
    }
    /* ELSE */
    else
    {
        /* Call function ARINCTaskRX to receive ARINC label of bus RX1 */
        ARINCTaskRX(AR_IN_1_HI);

        /* Increment interrupt number for current RX */
        TAB_arinc_rx_robustness_nbr_it[RX1]++;
    }
}


/***************************************************************/
/* Global function : ARINCTaskRX2                              */
/***************************************************************/
void ARINCTaskRX2(void)
{
    /* Clear eTPU ARINC reception maser channel interrupt associated to RX 2 */
    ETPU.CISR_B.R = ARINC_RX2_CLEAR_ETPU_IT;

    /* If the number of interrupt for current RX is higher than the limit set */
    if (TAB_arinc_rx_robustness_nbr_it[RX2] >
                    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX2])
    /* THEN */
    {
        /* Disable interrupt on current RX */
        DisableInterruptOnARINCChannel((UNS8)AR_IN_2_HI);
    }
    /* ELSE */
    else
    {
        /* Call function ARINCTaskRX to receive ARINC label of bus RX 2 */
        ARINCTaskRX(AR_IN_2_HI);

        /* Increment interrupt number for current RX */
        TAB_arinc_rx_robustness_nbr_it[RX2]++;
    }
}


/***************************************************************/
/* Global function : ARINCTaskRX3                              */
/***************************************************************/
void ARINCTaskRX3(void)
{
    /* Clear eTPU ARINC reception master channel interrupt associated to RX 3 */
    ETPU.CISR_B.R = ARINC_RX3_CLEAR_ETPU_IT;

    /* If the number of interrupt for current RX is higher than the limit set */
    if (TAB_arinc_rx_robustness_nbr_it[RX3] >
                    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX3])
    /* THEN */
    {
        /* Disable interrupt on current RX */
        DisableInterruptOnARINCChannel((UNS8)AR_IN_3_HI);
    }
    /* ELSE */
    else
    {
        /* Call function ARINCTaskRX to receive ARINC label of bus RX 3 */
        ARINCTaskRX(AR_IN_3_HI);

        /* Increment interrupt number for current RX */
        TAB_arinc_rx_robustness_nbr_it[RX3]++;
    }
}


/***************************************************************/
/* Global function : ARINCTaskRX4                              */
/***************************************************************/
void ARINCTaskRX4(void)
{
    /* Clear eTPU ARINC reception master channel interrupt associated to RX 4 */
    ETPU.CISR_B.R = ARINC_RX4_CLEAR_ETPU_IT;

    /* If the number of interrupt for current RX is higher than the limit set */
    if (TAB_arinc_rx_robustness_nbr_it[RX4] >
                    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX4])
    /* THEN */
    {
        /* Disable interrupt on current RX */
        DisableInterruptOnARINCChannel((UNS8)AR_IN_4_HI);
    }
    /* ELSE */
    else
    {
        /* Call function ARINCTaskRX to receive ARINC label of bus RX 4 */
        ARINCTaskRX(AR_IN_4_HI);

        /* Increment interrupt number for current RX */
        TAB_arinc_rx_robustness_nbr_it[RX4]++;
    }
}


/***************************************************************/
/* Global function : ARINCTaskRX5  Xtalk                       */
/***************************************************************/
void ARINCTaskRX5(void)
{
    /* Clear eTPU ARINC reception master channel interrupt associated to RX 5 */
    ETPU.CISR_B.R = ARINC_RX5_CLEAR_ETPU_IT;

    /* If the number of interrupt for current RX is higher than the limit set */
    if (TAB_arinc_rx_robustness_nbr_it[RX5] >
                    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX5])
    /* THEN */
    {
        /* Disable interrupt on current RX */
        DisableInterruptOnARINCChannel((UNS8)AR_IN_XTALK_HI);
    }
    /* ELSE */
    else
    {
        /* Call function ARINCTaskRX to receive ARINC label of bus RX 5 */
        ARINCTaskRX(AR_IN_XTALK_HI);

        /* Increment interrupt number for current RX */
        TAB_arinc_rx_robustness_nbr_it[RX5]++;
    }
}


/***************************************************************/
/* Global function : ARINCActiveInterrupt                      */
/***************************************************************/
void ARINCActiveInterrupt(void)
{
    UNS8 i;

    /* Call MaskInterruptINTC function, to disable the interrupt */
    MaskInterruptINTC();

    /* For each RX do */
    for (i = (UNS8)RX1; i < (UNS8)ARINC_RX_NUMBER ; i++)
    {
        /* Reset the number of interrupt */
        TAB_arinc_rx_robustness_nbr_it[i] = 0;
    }

    /* Enable interrupt on all ARINc RX channel */
    EnableInterruptOnARINCChannel(AR_IN_1_HI);
    EnableInterruptOnARINCChannel(AR_IN_2_HI);
    EnableInterruptOnARINCChannel(AR_IN_3_HI);
    EnableInterruptOnARINCChannel(AR_IN_4_HI);
	EnableInterruptOnARINCChannel(AR_IN_XTALK_HI);

    /* Call ARINCOverflowClear, to clean reception */
    ARINCOverflowClear();

    /* Call UnmaskInterruptINTC, to enable the interrupt */
    UnmaskInterruptINTC();
}

/***************************************************************/
/* Global function : GetARINCData                              */
/***************************************************************/
void GetARINCData(void)
{
    UNS8 FIFO_index;
    UNS32 label;
    BOOLEAN FIFO_empty_status;

    /* move arinc label data from arinc_fifo_rx to I_BSP_Out.arinc_fifo_rx */
    /* FOR each ARINC FIFO ARINC input from 0 to 7*/
    for(FIFO_index=0;FIFO_index < ARINC_RX_NB;FIFO_index++)
    {
        /* Call PopUpElement function to Pop-up one label from arinc reception FIFO TAB_arinc_fifo_rx */
        FIFO_empty_status = PopUpElement(&TAB_arinc_fifo_rx[FIFO_index], &label);
        /* WHILE the reception FIFO arinc_fifo_rx is not empty DO */
        while(FIFO_empty_status == TRUE)
        {
            /* Call PushElement function to Push message in the target FIFO I_BSP_Out.arinc_fifo_rx*/
            PushElement(label, &I_BSP_Out.arinc_fifo_rx.TAB_queue[FIFO_index]);
            /* Call PopUpElement function to Pop-up one label from arinc reception FIFO TAB_arinc_fifo_rx */
            FIFO_empty_status = PopUpElement(&TAB_arinc_fifo_rx[FIFO_index], &label);
        }
    }
    /* END FOR */
}


/***************************************************************/
/* Global function : MonitorARINCChannelsParameters            */
/***************************************************************/
BOOLEAN MonitorARINCChannelsParameters(void)
{
    UNS32 arinc_baudrate_channel;
    BOOLEAN F_error;

    /* Call EtpuMonitorA429RxParameters function to Monitor ARINC input bus RX1 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX1);
    F_error = EtpuMonitorA429RxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_1_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuMonitorA429RxParameters function to Monitor ARINC input bus RX2 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX2);
    F_error |= EtpuMonitorA429RxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_2_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuMonitorA429RxParameters function to Monitor ARINC input bus RX3 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX3);
    F_error |= EtpuMonitorA429RxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_3_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuMonitorA429RxParameters function to Monitor ARINC input bus RX4 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX4);
    F_error |= EtpuMonitorA429RxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_4_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);
	
	/* Call EtpuMonitorA429RxParameters function to Monitor ARINC input bus RX5 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_RX5);
    F_error |= EtpuMonitorA429RxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_IN_XTALK_HI], arinc_baudrate_channel, ARINC_RX_BUFFER_SIZE);

    /* Call EtpuMonitorA429TxParameters function to Monitor ARINC output bus TX1 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_TX1);
    F_error |= EtpuMonitorA429TxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_1_HI], arinc_baudrate_channel, I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[0]);

    /* Call EtpuMonitorA429TxParameters function to Monitor ARINC output bus TX2 */
    arinc_baudrate_channel = ConvertARINCSpeed(I_BSP_conf.arinc_conf.channel_TX2);
    F_error |= EtpuMonitorA429TxParameters(&TAB_etpu_ARINC_channel[ETPU_A][AR_OUT_2_HI], arinc_baudrate_channel, I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[2]);
	
    return F_error;
}

/***************************************************************/
/* Global function : Initializearinc_int                       */
/***************************************************************/
void Initializearinc_int(void)
{
    UNS32 i;
    UNS16 *ram_PTR;
    UNS16 *arinc_filter_APP_PTR;


    /* Set ARINC pointer to address of APP filter table given by APP */
    arinc_filter_APP_PTR = (UNS16 *)I_BSP_conf.arinc_conf.TAB_address_arinc_rx_filter;

    /* Set ram pointer to the beginning of eTPU data RAM */
    ram_PTR = (UNS16 *)(ETPU_DATA_RAM_START_ABS);
    /* Set ARINC reception filter table defined by APP into eTPU data RAM  */
    for (i = 0; i < ARINC_RX_FILTER_TAB_SIZE; i++)
    {
       *ram_PTR = *arinc_filter_APP_PTR;
       arinc_filter_APP_PTR ++;
       ram_PTR ++;
    }

    /* For  all ARINC FIFO input structure TAB_arinc_fifo_rx,  to zero */
    for(i = 0; i < (UNS32)ARINC_RX_NB; i++)
    {
       /* Call CreateQueue to initialize TAB_arinc_fifo_rx */
       CreateQueue(&TAB_arinc_fifo_rx[i]);
    }

    /* Initialize all element of TAB_arinc_rx_robustness_nbr_it to zero */
    for(i = 0 ; i < (UNS32)ARINC_RX_NUMBER ; i++)
    {
       /* Call CreateQueue to initialize TAB_arinc_fifo_rx */
        TAB_arinc_rx_robustness_nbr_it[i] = 0;
    }

    /* Initialize ARINC channels structure */
    InitializeARINCChannels();
    /* Initialize transmission */
    InitializeARINCTxChannels();
    /* Initialize reception */
    InitializeARINCRxChannels();
}

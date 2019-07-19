/***************************************************************/
/* FUNCTION : To define the standard type used by software     */
/*            on BSP and APP interface                         */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "intc_isr_vectors.h"
#include "cpu_lb.h"
#include "l91152ae.h"
#include "mon_memory.h"
#include "wdg_ts.h"

#include "interface.h"
#include "configuration.h"

#include "can_lb.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
T_BSP_INPUT        I_BSP_In;
T_BSP_OUTPUT       I_BSP_Out;

T_CAN_TX_VALUES can_A_tx;
T_CAN_TX_VALUES can_B_tx;
T_CAN_TX_VALUES can_C_tx;


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
/* Local function : CopyArincData                              */
/***************************************************************/
void CopyArincData(T_ARINC_TX *an_arinc_tx_PTR)
{
    UNS32 i, j, n;


    /* Loop on all ARINC transmitters */
    for ( i = 0 ; i < (UNS32)ARINC_TX_NB ; i++ )
    {
        n = I_BSP_In.arinc_tx[i].number;

        /* Check messages need to be sent on current transmitter */
        if ( an_arinc_tx_PTR[i].number > 0u )
        {
            /* Loop on all messages to transmit */
            for ( j = 0 ; j < an_arinc_tx_PTR[i].number ; j++ )
            {
                /* If the internal buffer is not full, copy the message to send at the end of the BSP internal buffer */
                if (I_BSP_In.arinc_tx[i].number < ARINC_MAX_LABEL_NUMBER)
                {
                    I_BSP_In.arinc_tx[i].TAB_label[n+j] = an_arinc_tx_PTR[i].TAB_label[j];
                    I_BSP_In.arinc_tx[i].number++;
                }
                else
                {
                }
            }

            /* Clear the number of messages provided by the APPLICATIVE S/W */
            an_arinc_tx_PTR[i].number = 0;
        }
        else
        {
            /* No message to transmit : do nothing */
        }
    }
}


/***************************************************************/
/* Local function : CopyCANData                                */
/***************************************************************/
UNS8 * CopyCANData(T_CAN_TX_VALUES *a_can_tx_PTR, T_CAN_TX_VALUES *an_internal_can_tx_PTR,
        UNS8 * a_CAN_tx_MB_list_PTR, UNS8 * a_CAN_tx_MB_initial_list_PTR)
{
    UNS32 j, n;
    UNS8 * CAN_tx_MB_PTR;
    
    CAN_tx_MB_PTR = a_CAN_tx_MB_list_PTR;

    n = an_internal_can_tx_PTR->number;

    /* Check messages need to be sent on current transmitter */
    if ( a_can_tx_PTR->number > 0 )
    {
        /* Loop on all messages to transmit */
        for ( j = 0 ; j < a_can_tx_PTR->number ; j++ )
        {
            /* If the internal buffer is not full, copy the message to send at the end of the BSP internal buffer */
            if (an_internal_can_tx_PTR->number < CAN_BUFFER_SIZE)
            {
                an_internal_can_tx_PTR->TAB_label[n+j] = a_can_tx_PTR->TAB_label[j];
                an_internal_can_tx_PTR->MB_identifier[n+j] = *CAN_tx_MB_PTR;
                an_internal_can_tx_PTR->number++;
                
                /* Compute message box identifier for next message to be send */
                CAN_tx_MB_PTR++;
                if (*CAN_tx_MB_PTR == 0xFF)
                {
                    CAN_tx_MB_PTR = a_CAN_tx_MB_initial_list_PTR;
                }
                else
                {
                }
            }
            else
            {
            }
        }

        /* Clear the number of messages provided by the APPLICATIVE S/W */
        a_can_tx_PTR->number = 0;
    }
    else
    {
        /* No message to transmit : do nothing */
    }

    return CAN_tx_MB_PTR;
}

/***************************************************************/
/* Local function : CopySCIData                                */
/***************************************************************/
void CopySCIData(T_SCI_BUFFER_TX *a_sci_tx_PTR, T_SCI_BUFFER_TX *an_internal_sci_tx_PTR)
{
    UNS32 j, n;

    n = an_internal_sci_tx_PTR->number;

    /* Check messages need to be sent on current transmitter */
    if ( a_sci_tx_PTR->number > 0u )
    {
        /* Loop on all messages to transmit */
        for ( j = 0 ; j < a_sci_tx_PTR->number ; j++ )
        {
            /* If the internal buffer is not full, copy the message to send at the end of the BSP internal buffer */
            if (an_internal_sci_tx_PTR->number < (UNS32)MAX_SCI_DATA_OUT)
            {
                an_internal_sci_tx_PTR->TAB_data[n+j] = a_sci_tx_PTR->TAB_data[j];
                an_internal_sci_tx_PTR->number++;
            }
            else
            {
            }
        }

        /* Clear the number of messages provided by the APPLICATIVE S/W */
        a_sci_tx_PTR->number = 0;
    }
    else
    {
        /* No message to transmit : do nothing */
    }
}

/***************************************************************/
/* Local function : ClearSCIReceptionBuffer                    */
/***************************************************************/
void ClearSCIReceptionBuffer(void)
{
    /* Reset CAN reception FIFO */
    I_BSP_Out.scia_buffer_rx.number = 0;
}

/***************************************************************/
/* Local function : ClearARINCReceptionFIFO                    */
/***************************************************************/
void ClearARINCReceptionFIFO(void)
{
    UNS8 FIFO_index;

    /* FOR each ARINC input from 0 to 7*/
    for(FIFO_index=0;FIFO_index < ARINC_RX_NB;FIFO_index++)
    {
        /* Reset ARINC reception FIFO */
        I_BSP_Out.arinc_fifo_rx.TAB_queue[FIFO_index].FirstEmptyElement = 0;
        I_BSP_Out.arinc_fifo_rx.TAB_queue[FIFO_index].FirstInElement = 0;
    }
}

/***************************************************************/
/* Local function : ClearCANReceptionFIFO                      */
/***************************************************************/
void ClearCANReceptionFIFO(void)
{
    /* Reset CAN reception FIFO */
    I_BSP_Out.can_A_rx.FirstEmptyElement = 0;
    I_BSP_Out.can_A_rx.FirstInElement = 0;
    I_BSP_Out.can_B_rx.FirstEmptyElement = 0;
    I_BSP_Out.can_B_rx.FirstInElement = 0;
	I_BSP_Out.can_C_rx.FirstEmptyElement = 0;
    I_BSP_Out.can_C_rx.FirstInElement = 0;
}


/***************************************************************/
/* Global function : ClearNumericalBusesReceptionBuffer        */
/***************************************************************/
void ClearNumericalBusesReceptionBuffer(void)
{
    /* Clear reception buffer and FIFO for numerical buses: CAN, ARINC & SCI */
    ClearARINCReceptionFIFO();
    ClearCANReceptionFIFO();
    ClearSCIReceptionBuffer();
}

/***************************************************************/
/* Global function : InitializeInterface                       */
/***************************************************************/
void InitializeInterface(void)
{
    UNS32 i, j;
    UNS32 * ptr;
    
    /* Initialize global data of the module */
    for ( i = 0 ; i < (UNS32)ARINC_TX_NB ; i++ )
    {
        I_BSP_In.arinc_tx[i].number = 0;
        for ( j = 0 ; j < ARINC_MAX_LABEL_NUMBER ; j++ )
        {
            I_BSP_In.arinc_tx[i].TAB_label[j] = 0;
        }
    }

    I_BSP_In.can_A_tx.number = 0;
    I_BSP_In.can_B_tx.number = 0;
	I_BSP_In.can_C_tx.number = 0;
    /* Loop on all messages to transmit */
    for ( j = 0 ; j < (UNS32)CAN_BUFFER_SIZE ; j++ )
    {
        I_BSP_In.can_A_tx.MB_identifier[j] = 0;
        I_BSP_In.can_B_tx.MB_identifier[j] = 0;
		I_BSP_In.can_C_tx.MB_identifier[j] = 0;
        I_BSP_In.can_A_tx.TAB_label[j].CAN_id.identifier = 0;
        I_BSP_In.can_A_tx.TAB_label[j].label_MSB = 0;
        I_BSP_In.can_A_tx.TAB_label[j].label_LSB = 0;
        I_BSP_In.can_A_tx.TAB_label[j].message_length = 0;
        I_BSP_In.can_B_tx.TAB_label[j].CAN_id.identifier = 0;
        I_BSP_In.can_B_tx.TAB_label[j].label_MSB = 0;
        I_BSP_In.can_B_tx.TAB_label[j].label_LSB = 0;
        I_BSP_In.can_B_tx.TAB_label[j].message_length = 0;
		I_BSP_In.can_C_tx.TAB_label[j].CAN_id.identifier = 0;
        I_BSP_In.can_C_tx.TAB_label[j].label_MSB = 0;
        I_BSP_In.can_C_tx.TAB_label[j].label_LSB = 0;
        I_BSP_In.can_C_tx.TAB_label[j].message_length = 0;
    }
   
    I_BSP_In.scia_buffer_tx.number = 0; 
    for ( j = 0 ; j < (UNS32)MAX_SCI_DATA_OUT ; j++ )
    {
        I_BSP_In.scia_buffer_tx.TAB_data[i] = 0;
    }
    
    /* Set default value (0) to the whole interface memory area */
    ptr = (UNS32 *)&_INTERFACE_DATA_START_ADDR;
    while (ptr < (UNS32 *)&_INTERFACE_DATA_END_ADDR)
    {
        *ptr = 0;
        ptr++;
    }

    /* - Initialize CAN structures and CAN configuration structure */
    for (i = 0; i < (UNS32)CAN_BUFFER_SIZE; i++)
    {
        I_BSP_In.can_A_tx.TAB_label[i].CAN_id.identifier = 0;
        I_BSP_In.can_A_tx.TAB_label[i].label_LSB = 0;
        I_BSP_In.can_A_tx.TAB_label[i].label_MSB = 0;
        I_BSP_In.can_A_tx.MB_identifier[i] = 0;
		I_BSP_In.can_B_tx.TAB_label[i].CAN_id.identifier = 0;
        I_BSP_In.can_B_tx.TAB_label[i].label_LSB = 0;
        I_BSP_In.can_B_tx.TAB_label[i].label_MSB = 0;
        I_BSP_In.can_B_tx.MB_identifier[i] = 0;
		I_BSP_In.can_C_tx.TAB_label[i].CAN_id.identifier = 0;
        I_BSP_In.can_C_tx.TAB_label[i].label_LSB = 0;
        I_BSP_In.can_C_tx.TAB_label[i].label_MSB = 0;
        I_BSP_In.can_C_tx.MB_identifier[i] = 0;
        
        I_BSP_Out.can_A_rx.TAB_label[i].CAN_id.identifier = 0;
        I_BSP_Out.can_A_rx.TAB_label[i].label_LSB = 0;
        I_BSP_Out.can_A_rx.TAB_label[i].label_MSB = 0;
		I_BSP_Out.can_B_rx.TAB_label[i].CAN_id.identifier = 0;
        I_BSP_Out.can_B_rx.TAB_label[i].label_LSB = 0;
        I_BSP_Out.can_B_rx.TAB_label[i].label_MSB = 0;
		I_BSP_Out.can_C_rx.TAB_label[i].CAN_id.identifier = 0;
        I_BSP_Out.can_C_rx.TAB_label[i].label_LSB = 0;
        I_BSP_Out.can_C_rx.TAB_label[i].label_MSB = 0;
    }
    I_BSP_In.can_A_tx.number = 0;
	I_BSP_In.can_B_tx.number = 0;
	I_BSP_In.can_C_tx.number = 0;
    I_BSP_Out.can_A_rx.FirstEmptyElement = 0;
    I_BSP_Out.can_A_rx.FirstInElement = 0;
    I_BSP_Out.can_B_rx.FirstEmptyElement = 0;
    I_BSP_Out.can_B_rx.FirstInElement = 0;
	I_BSP_Out.can_C_rx.FirstEmptyElement = 0;
    I_BSP_Out.can_C_rx.FirstInElement = 0;
    I_BSP_Out.can_A_status.F_transmit_failure = 0;
    I_BSP_Out.can_B_status.F_transmit_failure = 0;
	I_BSP_Out.can_C_status.F_transmit_failure = 0;

    /* Disable AD128S02 12 BITS EXTERNAL*/
    for(i = 0; i < (UNS32)EXT_ADC_INPUT_NUMBER; i++)
    {
        for(j = 0; j < (UNS32)ANALOG_MULTIPLEXER_INPUT_NUMBER; j++)
        {
            I_BSP_Out.adc128s052_acq.TAB[i][j] = 0;
        }
    }

    /* AD2S1210 RDC */
    I_BSP_In.ad2s1210_enable.F_AD2S1210_RDC1_perform_acq = FALSE;
    I_BSP_In.ad2s1210_faults_reset.F_AD2S1210_RDC1_faults_reset = FALSE;

    I_BSP_Out.ad2s1210.TAB_AD2S1210_POSITION = 0;
    I_BSP_Out.ad2s1210.fault.data = 0;

    /* AD1255 : PRESSURE 24 BITS */
    I_BSP_Out.ad1255_acq.pressure_24_bits = 0;
    I_BSP_Out.ad1255_acq.ADC_F = 0;

    /* - ARINC 429 */
    for (i = 0; i < (UNS32)ARINC_TX_NB; i++)
    {
        I_BSP_In.arinc_tx[i].number = 0;
        for (j = 0; j < (UNS32)ARINC_MAX_LABEL_NUMBER; j++)
        {
            I_BSP_In.arinc_tx[i].TAB_label[j] = 0;
        }
    }
    
    /* - SCI */
    for (i = 0; i < (UNS32)MAX_SCI_DATA_IN; i++)
    {
        I_BSP_Out.scia_buffer_rx.TAB_data[i] = (UNS8)0;
    }
    for (i = 0; i < (UNS32)MAX_SCI_DATA_OUT; i++)
    {
        I_BSP_In.scia_buffer_tx.TAB_data[i] = (UNS8)0;
    }
    I_BSP_Out.scia_buffer_rx.number = 0;
    I_BSP_In.scia_buffer_tx.number = 0;

    /* - Torque Motor interfaces */
    I_BSP_In.torq_motor.torq_motor1_cmd = 0.0;
    I_BSP_In.torq_motor.torq_motor2_cmd = 0.0;
    I_BSP_In.torq_motor.torq_motor3_cmd = 0.0;
    I_BSP_In.torq_motor.torq_motor4_cmd = 0.0;
    I_BSP_In.torq_motor.torq_motor5_cmd = 0.0;    
	
	I_BSP_In.torq_motor.torq_motor1_EN = FALSE;
    I_BSP_In.torq_motor.torq_motor2_EN = FALSE;
    I_BSP_In.torq_motor.torq_motor3_EN = FALSE;
    I_BSP_In.torq_motor.torq_motor4_EN = FALSE;
    I_BSP_In.torq_motor.torq_motor5_EN = FALSE;

    /* - Leak Detection command */
    for (i = 0; i < (UNS32)LEAK_ACQ_CMD_NB_MAX; i++)
    {
        I_BSP_In.leak_detection_cmd.TAB_configuration_id[i] = 0;
    }
	
    /* - Leak Detection timings configuration */
    I_BSP_conf.leak_detection_conf.clock_period       = 0;
    I_BSP_conf.leak_detection_conf.init_test_delay    = 0;
    I_BSP_conf.leak_detection_conf.setup_test_delay   = 0;
    I_BSP_conf.leak_detection_conf.setup_mux_delay    = 0;
    I_BSP_conf.leak_detection_conf.setup_conf_delay   = 0;
    I_BSP_conf.leak_detection_conf.pulse_width        = 0;
    I_BSP_conf.leak_detection_conf.leak_timeout       = 0;

    /* - Leak acquisition */
    for(i=0; i < (UNS32)LEAK_CONF_MAX; i++)
    {
       for(j=0; j < (UNS32)AD4005_INPUT_MAX; j++)
       {
           I_BSP_Out.leak_detection_acq[i].buffer[j] = 0;
       }
    }

    /* - Identification */
    for (i = 0; i < (UNS32)MAX_HW_PARTNUMBER; i++)
    {
        I_BSP_Out.identification.TAB_hw_part_number[i] = 0;
    }
    for (i = 0; i < (UNS32)MAX_HW_SERIALNUMBER; i++)
    {
        I_BSP_Out.identification.TAB_hw_serial_number[i] = 0;
    
    }
    for (i = 0; i < (UNS32)MAX_SW_PARTNUMBER; i++)
    {
        I_BSP_Out.identification.TAB_sw_boot_part_number[i] = 0;
        I_BSP_Out.identification.TAB_sw_sloader_part_number[i] = 0;
        I_BSP_Out.identification.TAB_sw_bsp_part_number[i] = 0;
        I_BSP_Out.identification.TAB_sw_app1_part_number[i] = 0;
        I_BSP_Out.identification.TAB_sw_bite_part_number[i] = 0;
    }
    for (i = 0; i < (UNS32)MAX_SW_CRC; i++)
    {
        I_BSP_Out.identification.TAB_sw_boot_crc32[i] = 0;
        I_BSP_Out.identification.TAB_sw_sloader_crc32[i] = 0;
        I_BSP_Out.identification.TAB_sw_bsp_crc32[i] = 0;
        I_BSP_Out.identification.TAB_sw_app1_crc32[i] = 0;
        I_BSP_Out.identification.TAB_sw_bite_crc32[i] = 0;
    }

    /* - BITE */
    I_BSP_Out.bite_status.F_BITE_to_be_reset = 0;
    I_BSP_Out.bite_status.F_BITE_short_action_enabled = 0;
    I_BSP_Out.bite_status.F_BITE_long_action_enabled = 0;
    
    /* - Initialize T_DISC_OUTPUT structure */
    for (i=0; i < (UNS32)DISC_OUTPUT_BUFFER_NUMBER; i++)
    {
        I_BSP_In.disc_out.port[i].data = 0;
    }
	
    /* - Watchdog */
    I_BSP_In.watchdog_rearm_flag = 0;
    /* Set watchdog test result */
    I_BSP_Out.monitoring.hardware.watchdog_F = F_watchdog_fail;
    
    /* Set RAM test result */
    I_BSP_Out.monitoring.software.ram_F = F_ram_fail;

    /* Set crc boot test result */    
    I_BSP_Out.monitoring.software.crc_F.B.boot_crc_F = F_crc_boot_fail;  
    
    /* - DC motors */
    I_BSP_In.dc_motor.HW_DC_MOTOR_1_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_1_CMD = 0.0;
	I_BSP_In.dc_motor.HW_DC_MOTOR_1_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_2_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_2_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_2_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_3_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_3_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_3_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_4_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_4_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_4_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_5_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_5_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_5_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_6_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_6_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_6_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_7_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_7_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_7_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_8_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_8_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_8_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_9_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_9_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_9_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_10_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_10_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_10_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_11_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_11_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_11_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_12_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_12_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_12_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_13_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_13_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_13_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_14_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_14_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_14_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_15_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_15_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_15_ENABLE = FALSE;

    I_BSP_In.dc_motor.HW_DC_MOTOR_16_PERIOD_MS = 0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_16_CMD = 0.0;
    I_BSP_In.dc_motor.HW_DC_MOTOR_16_ENABLE = FALSE;
}


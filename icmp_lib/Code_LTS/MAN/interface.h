/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
#define CAN_BUFFER_SIZE                     (UNS8)(64*2)
#define CAN_MB_NOT_MSG_TO_SEND              (UNS32)0xFFFFFFFF

#define MAX_ELEM_FIFO_ARINC                 (UNS16)280

#define NB_STEP_MOTOR                       (UNS8)4

/* ---- INTERNAL ANALOG INPUT INTERFACE ---- */
#define INTERNAL_12BIT_ADC_ENTRY_NUMBER     (UNS8)40

/* ---- IDENTIFICATION INTERFACE ---- */
#define MAX_SW_PARTNUMBER                   (UNS8)15
#define MAX_SW_CRC                          (UNS8)4
#define MAX_HW_PARTNUMBER                   (UNS8)32
#define MAX_HW_SERIALNUMBER                 (UNS8)32

/* ---- EXTERNAL ANALOG INPUT INTERFACE ---- */
#define EXT_ADC_INPUT_NUMBER                (UNS8)8
#define ANALOG_MULTIPLEXER_INPUT_NUMBER     (UNS8)8

/* ---- DISCRETE INPUT/OUTPUT INTERFACE ---- */
#define DISC_INPUT_BUFFER_NUMBER            (UNS8)11
#define DISC_OUTPUT_BUFFER_NUMBER           (UNS8)8

/* ---- ARINC INTERFACE ---- */
#define ARINC_RX_NB                         (UNS8)5
#define ARINC_TX_NB                         (UNS8)2
#define ARINC_MAX_LABEL_NUMBER              (UNS32)137

/* ---- SCI INTERFACE ---- */
#define MAX_SCI_DATA_IN                     (UNS8)112
#define MAX_SCI_DATA_OUT                    (UNS8)32

/* ---- MMU CONFIGURATION INTERFACE ---- */
#define TAB_SW_MMU_CONFIG_MAX               (UNS8)18

/* DATA exchange */
#define DATA_EXCHANGE_BUFFER_SIZE           (UNS32)128

/* ---- LEAK ACQUISITION INTERFACE ---- */
#define AD4005_INPUT_MAX                    (UNS8)4
#define LEAK_CONF_MAX                       (UNS8)72
#define LEAK_ACQ_CMD_NB_MAX                 (UNS8)20


/***************************************************************/
/*                                                             */
/*                      GLOBAL TYPES                           */
/*                                                             */
/***************************************************************/
typedef struct 
{
    union 
    {
        UNS32 identifier;
        struct 
        {
            UNS32 spare          : 25;
            UNS32 destination_ID : 3;
            UNS32 request        : 1;
            UNS32 size           : 3;
        }
        field;
    }
    CAN_id;
    UNS32 label_MSB;
    UNS32 label_LSB;
    UNS32 message_length;
}
T_CAN_Label;

typedef struct
{
        UNS16 FirstEmptyElement;
        UNS16 FirstInElement;
        UNS32 TAB_Element[MAX_ELEM_FIFO_ARINC];
}
T_FIFOQueue;

/*******************************/
/* BSP/APP INTERFACE STRUCTURE */
/*******************************/
/* T_LEAK_DETECTION_CMD */
typedef struct
{
    UNS8 TAB_configuration_id[LEAK_ACQ_CMD_NB_MAX];
}
T_LEAK_DETECTION_CMD;

/* T_LEAK_DETECTION */
typedef struct
{
    INT16 buffer[AD4005_INPUT_MAX];
}
T_LEAK_DETECTION_ACQ;


/* T_EQADC */
typedef struct
{
    UNS16 TAB_12_bits[INTERNAL_12BIT_ADC_ENTRY_NUMBER];
}
T_EQADC;

/* T_AD1255 */
typedef struct
{
    UNS32 pressure_24_bits;
    BOOLEAN ADC_F;
}
T_AD1255;

/* T_ADC128S052 */
typedef struct
{
    UNS16 TAB[EXT_ADC_INPUT_NUMBER][ANALOG_MULTIPLEXER_INPUT_NUMBER];
}
T_ADC128S052;


/* T_AD2S1210_ENABLE */
typedef struct
{
    /* Resolvers reading */
    BOOLEAN F_AD2S1210_RDC1_perform_acq;
}
T_AD2S1210_ENABLE;

/* T_AD2S1210_FAULTS_RESET */
typedef struct
{
    /* Resolvers reading */
    BOOLEAN F_AD2S1210_RDC1_faults_reset;
}
T_AD2S1210_FAULTS_RESET;

/* T_AD2S1210 */
typedef struct
{
    UNS16 TAB_AD2S1210_POSITION;
    union
    {
        UNS8 data;
        struct
        {
            UNS8 F_inputs_clipped                  :1;
            UNS8 F_inputs_below_LOS                :1;
            UNS8 F_inputs_exceed_DOS_overrange     :1;
            UNS8 F_inputs_exceed_DOS_mismatch      :1;
            UNS8 F_tracking_error                  :1;
            UNS8 F_velocity_error                  :1;
            UNS8 F_phase_error                     :1;
            UNS8 F_parity_error                    :1;
        }
        B;    
    }
    fault;
}
T_AD2S1210;


/* T_DISC_INPUT_PORT */
typedef struct
{
    union
    {
        UNS32 data;
        struct
        {
            UNS32 D_IO_31     :1;
            UNS32 D_IO_30     :1;
            UNS32 D_IO_29     :1;
            UNS32 D_IO_28     :1;
            UNS32 D_IO_27     :1;
            UNS32 D_IO_26     :1;
            UNS32 D_IO_25     :1;
            UNS32 D_IO_24     :1;
            UNS32 D_IO_23     :1;
            UNS32 D_IO_22     :1;
            UNS32 D_IO_21     :1;
            UNS32 D_IO_20     :1;
            UNS32 D_IO_19     :1;
            UNS32 D_IO_18     :1;
            UNS32 D_IO_17     :1;
            UNS32 D_IO_16     :1;
            UNS32 D_IO_15     :1;
            UNS32 D_IO_14     :1;
            UNS32 D_IO_13     :1;
            UNS32 D_IO_12     :1;
            UNS32 D_IO_11     :1;
            UNS32 D_IO_10     :1;
            UNS32 D_IO_09     :1;
            UNS32 D_IO_08     :1;
            UNS32 D_IO_07     :1;
            UNS32 D_IO_06     :1;
            UNS32 D_IO_05     :1;
            UNS32 D_IO_04     :1;
            UNS32 D_IO_03     :1;
            UNS32 D_IO_02     :1;
            UNS32 D_IO_01     :1;
            UNS32 D_IO_00     :1;
        }
        B;
    }
    port[DISC_INPUT_BUFFER_NUMBER];
}
T_DISC_INPUT_PORT;

/* T_DISC_OUTPUT_PORT */
typedef struct
{
    union
    {
        UNS32 data;
        struct
        {
            UNS32 D_IO_31     :1;
            UNS32 D_IO_30     :1;
            UNS32 D_IO_29     :1;
            UNS32 D_IO_28     :1;
            UNS32 D_IO_27     :1;
            UNS32 D_IO_26     :1;
            UNS32 D_IO_25     :1;
            UNS32 D_IO_24     :1;
            UNS32 D_IO_23     :1;
            UNS32 D_IO_22     :1;
            UNS32 D_IO_21     :1;
            UNS32 D_IO_20     :1;
            UNS32 D_IO_19     :1;
            UNS32 D_IO_18     :1;
            UNS32 D_IO_17     :1;
            UNS32 D_IO_16     :1;
            UNS32 D_IO_15     :1;
            UNS32 D_IO_14     :1;
            UNS32 D_IO_13     :1;
            UNS32 D_IO_12     :1;
            UNS32 D_IO_11     :1;
            UNS32 D_IO_10     :1;
            UNS32 D_IO_09     :1;
            UNS32 D_IO_08     :1;
            UNS32 D_IO_07     :1;
            UNS32 D_IO_06     :1;
            UNS32 D_IO_05     :1;
            UNS32 D_IO_04     :1;
            UNS32 D_IO_03     :1;
            UNS32 D_IO_02     :1;
            UNS32 D_IO_01     :1;
            UNS32 D_IO_00     :1;
        }
        B;
    }
    port[DISC_OUTPUT_BUFFER_NUMBER];
}
T_DISC_OUTPUT_PORT;

/* T_DISC_INPUT_GPIO */
typedef struct
{
    /* WD_COUNTER_1Q PIN */
    UNS32 HW_GPIO_111 :1;
    /* WD_COUNTER_2Q PIN */
    UNS32 HW_GPIO_112 :1;

    /* DI_GND_1L2_16 PIN - SHOP PIN */
    UNS32 HW_GPIO_179 :1;
    UNS32 HW_GPIO_180 :1;
    /* DI_INT_1 PIN - Channel coding COD_1 */
    UNS32 HW_GPIO_181 :1;
    /* DI_INT_2 PIN - Channel coding COD_2 */
    UNS32 HW_GPIO_182 :1;
    
    /* ITD_200 MS PIN */
    UNS32 HW_GPIO_193 :1;
    /* N_SID PIN */
    UNS32 HW_GPIO_194 :1;
}
T_DISC_INPUT_GPIO;

/* T_DISC_OUTPUT_GPIO */
typedef struct
{
    /* RDC_SAMPLE */
    UNS32 HW_GPIO_178 :1;
	/* ITD_INIT PIN */
    UNS32 HW_GPIO_195 :1;
    /* N_RESET_ETH */
    UNS32 HW_GPIO_199 :1;
	/* RDC_A0 */
    UNS32 HW_GPIO_200 :1;
    /* RDC_A1 */
    UNS32 HW_GPIO_201 :1;
	/* SID_TEST */
    UNS32 HW_GPIO_203 :1;
	/* DI_TEST */
    UNS32 HW_GPIO_204 :1;
    /* N_RESET_RDC */
    UNS32 HW_GPIO_206 :1;
}
T_DISC_OUTPUT_GPIO;

/* ---- ARINC INTERFACE ---- */
/* T_ARINC_FIFO_RX */
typedef struct
{
    T_FIFOQueue TAB_queue[ARINC_RX_NB];
}
T_ARINC_FIFO_RX;

/* T_ARINC_TX */
typedef struct
{
    UNS32 number;
    UNS32 TAB_label[ARINC_MAX_LABEL_NUMBER];
}
T_ARINC_TX;


/*! ---- CAN INTERFACE ---- */
/* T_CAN_RX_VALUES */
typedef struct
{
    UNS16 FirstEmptyElement;
    UNS16 FirstInElement;
    T_CAN_Label TAB_label[CAN_BUFFER_SIZE];
}
T_CAN_RX_VALUES;

/* T_CAN_TX_VALUES */
typedef struct
{
    UNS8 number;
    UNS8 MB_identifier[CAN_BUFFER_SIZE];
    T_CAN_Label TAB_label[CAN_BUFFER_SIZE];
}
T_CAN_TX_VALUES;

/* T_CAN_STATUS */
typedef struct
{
    BOOLEAN F_transmit_failure;
}
T_CAN_STATUS;


/*! ---- SCI INTERFACE ---- */

/* T_SCI_BUFFER_RX */
typedef struct
{
    UNS8 TAB_data[MAX_SCI_DATA_IN];
    UNS32 number;
}
T_SCI_BUFFER_RX;

/* T_SCI_BUFFER_TX */
typedef struct
{
    UNS8 TAB_data[MAX_SCI_DATA_OUT];
    UNS32 number;
}
T_SCI_BUFFER_TX;


/*! ---- MOTOR INTERFACE ---- */
/*! T_TORQ_MOTOR */
typedef struct
{
    REAL32  torq_motor1_cmd;
	REAL32  torq_motor2_cmd;
	REAL32  torq_motor3_cmd;
	REAL32  torq_motor4_cmd;
	REAL32  torq_motor5_cmd;
    BOOLEAN  torq_motor1_EN;
    BOOLEAN  torq_motor2_EN;
    BOOLEAN  torq_motor3_EN;
    BOOLEAN  torq_motor4_EN;
    BOOLEAN  torq_motor5_EN;
}
T_TORQ_MOTOR;

/* T_DC_MOTOR */
typedef struct
{
	/* Enable from APP: to command the enabling and disabling sequences */
	BOOLEAN HW_DC_MOTOR_1_ENABLE;
    BOOLEAN HW_DC_MOTOR_2_ENABLE;
    BOOLEAN HW_DC_MOTOR_3_ENABLE;    
    BOOLEAN HW_DC_MOTOR_4_ENABLE;
    BOOLEAN HW_DC_MOTOR_5_ENABLE;
    BOOLEAN HW_DC_MOTOR_6_ENABLE; 
    BOOLEAN HW_DC_MOTOR_7_ENABLE;
    BOOLEAN HW_DC_MOTOR_8_ENABLE;
    BOOLEAN HW_DC_MOTOR_9_ENABLE;
    BOOLEAN HW_DC_MOTOR_10_ENABLE;
    BOOLEAN HW_DC_MOTOR_11_ENABLE; 
    BOOLEAN HW_DC_MOTOR_12_ENABLE;
    BOOLEAN HW_DC_MOTOR_13_ENABLE;
    BOOLEAN HW_DC_MOTOR_14_ENABLE; 
    BOOLEAN HW_DC_MOTOR_15_ENABLE;
    BOOLEAN HW_DC_MOTOR_16_ENABLE;
	
    /* Configuration */
    UNS16 HW_DC_MOTOR_1_PERIOD_MS;    
    UNS16 HW_DC_MOTOR_2_PERIOD_MS;
    UNS16 HW_DC_MOTOR_3_PERIOD_MS;
    UNS16 HW_DC_MOTOR_4_PERIOD_MS;
    UNS16 HW_DC_MOTOR_5_PERIOD_MS;
    UNS16 HW_DC_MOTOR_6_PERIOD_MS;
    UNS16 HW_DC_MOTOR_7_PERIOD_MS;
    UNS16 HW_DC_MOTOR_8_PERIOD_MS;
    UNS16 HW_DC_MOTOR_9_PERIOD_MS;
    UNS16 HW_DC_MOTOR_10_PERIOD_MS;
    UNS16 HW_DC_MOTOR_11_PERIOD_MS;
    UNS16 HW_DC_MOTOR_12_PERIOD_MS;
    UNS16 HW_DC_MOTOR_13_PERIOD_MS;
    UNS16 HW_DC_MOTOR_14_PERIOD_MS;
    UNS16 HW_DC_MOTOR_15_PERIOD_MS;
    UNS16 HW_DC_MOTOR_16_PERIOD_MS;

    /* Commands */
    REAL32 HW_DC_MOTOR_1_CMD;
    REAL32 HW_DC_MOTOR_2_CMD;
    REAL32 HW_DC_MOTOR_3_CMD;
    REAL32 HW_DC_MOTOR_4_CMD;
    REAL32 HW_DC_MOTOR_5_CMD;
    REAL32 HW_DC_MOTOR_6_CMD;
    REAL32 HW_DC_MOTOR_7_CMD;
    REAL32 HW_DC_MOTOR_8_CMD;
    REAL32 HW_DC_MOTOR_9_CMD;
    REAL32 HW_DC_MOTOR_10_CMD;
    REAL32 HW_DC_MOTOR_11_CMD;
    REAL32 HW_DC_MOTOR_12_CMD;
    REAL32 HW_DC_MOTOR_13_CMD;
    REAL32 HW_DC_MOTOR_14_CMD;
    REAL32 HW_DC_MOTOR_15_CMD;
    REAL32 HW_DC_MOTOR_16_CMD;
    
}
T_DC_MOTOR;


/*! T_STP_MOTOR */
typedef struct
{

    /* Commands */
    REAL32 HW_STP_MOTOR_1_CMD;

    /* Step counting */
    BOOLEAN SET_STEPCOUNT;
    INT32 STEPCOUNT_VALUE;
}
T_STP_MOTOR;

/* T_STP_MOTOR_2PH_CMD_FREQ */
typedef struct
{
    /* Configuration */
    UNS16 HW_STP_MOTOR_1_CMD_FREQ;
    /* Flag synchronisation */
    BOOLEAN HW_STP_MOTOR_1_NEW_CMD_FREQ;   
}
T_STP_MOTOR_2PH_CMD_FREQ;

/* T_BITE_STATUS */
typedef struct
{
    /* F_BITE_to_be_reset shall be set to first parameter to be used in DefaultHandler function */
    BOOLEAN F_BITE_to_be_reset;
    BOOLEAN F_BITE_short_action_enabled;
    BOOLEAN F_BITE_long_action_enabled;
}
T_BITE_STATUS;

/* T_IDENTIFICATION */
typedef struct
{
   UNS8 TAB_hw_part_number[MAX_HW_PARTNUMBER];
   UNS8 TAB_hw_serial_number[MAX_HW_SERIALNUMBER];
   UNS8 TAB_sw_boot_part_number[MAX_SW_PARTNUMBER];
   UNS8 TAB_sw_boot_crc32[MAX_SW_CRC];
   UNS8 TAB_sw_sloader_part_number[MAX_SW_PARTNUMBER];
   UNS8 TAB_sw_sloader_crc32[MAX_SW_CRC];
   UNS8 TAB_sw_bsp_part_number[MAX_SW_PARTNUMBER];
   UNS8 TAB_sw_bsp_crc32[MAX_SW_CRC];
   UNS8 TAB_sw_app1_part_number[MAX_SW_PARTNUMBER];
   UNS8 TAB_sw_app1_crc32[MAX_SW_CRC];
   UNS8 TAB_sw_bite_part_number[MAX_SW_PARTNUMBER];
   UNS8 TAB_sw_bite_crc32[MAX_SW_CRC];
}
T_IDENTIFICATION;



/*! T_MONITORING_SW */
typedef struct
{
    BOOLEAN register_F;
    union
    {
        UNS32 status;
        struct
        {
            UNS32 boot_crc_F        :1;
            UNS32 shop_loader_crc_F :1;
            UNS32 bsp_crc_F         :1;
            UNS32 app1_crc_F        :1;
            UNS32 bite_crc_F        :1;
        }
        B;
    }
    crc_F;
    BOOLEAN ram_F;
    BOOLEAN stack_F;
}
T_MONITORING_SW;

/*! T_MONITORING_HW */
typedef struct
{
    union
    {
        UNS32 status;
        struct
        {
            UNS32 spare            :13;
            UNS32 disc_in_19_F     :1;
            UNS32 disc_in_18_F     :1;
            UNS32 disc_in_17_F     :1;
            UNS32 disc_in_16_F     :1;
            UNS32 disc_in_15_F     :1;
            UNS32 disc_in_14_F     :1;
            UNS32 disc_in_13_F     :1;
            UNS32 disc_in_12_F     :1;
            UNS32 disc_in_11_F     :1;
            UNS32 disc_in_10_F     :1;
            UNS32 disc_in_9_F      :1;
            UNS32 disc_in_8_F      :1;
            UNS32 disc_in_7_F      :1;
            UNS32 disc_in_6_F      :1;
            UNS32 disc_in_5_F      :1;
            UNS32 disc_in_4_F      :1;
            UNS32 disc_in_3_F      :1;
            UNS32 disc_in_2_F      :1;
            UNS32 disc_in_1_F      :1;
        }
        B;
    }
    discrete_buffer_F;
    union
    {
        UNS32 status;
        struct
        {
            UNS32 AN_31_F     :1;
            UNS32 AN_30_F     :1;
            UNS32 AN_29_F     :1;
            UNS32 AN_28_F     :1;
            UNS32 AN_27_F     :1;
            UNS32 AN_26_F     :1;
            UNS32 AN_25_F     :1;
            UNS32 AN_24_F     :1;
            UNS32 AN_23_F     :1;
            UNS32 AN_22_F     :1;
            UNS32 AN_21_F     :1;
            UNS32 AN_20_F     :1;
            UNS32 AN_19_F     :1;
            UNS32 AN_18_F     :1;
            UNS32 AN_17_F     :1;
            UNS32 AN_16_F     :1;
            UNS32 AN_15_F     :1;
            UNS32 AN_14_F     :1;
            UNS32 AN_13_F     :1;
            UNS32 AN_12_F     :1;
            UNS32 AN_11_F     :1;
            UNS32 AN_10_F     :1;
            UNS32 AN_09_F     :1;
            UNS32 AN_08_F     :1;
            UNS32 AN_07_F     :1;
            UNS32 AN_06_F     :1;
            UNS32 AN_05_F     :1;
            UNS32 AN_04_F     :1;
            UNS32 AN_03_F     :1;
            UNS32 AN_02_F     :1;
            UNS32 AN_01_F     :1;
            UNS32 AN_00_F     :1;
        }
        B;
    }
    internal_voltage_l_F;
    union
    {
        UNS32 status;
        struct
        {
            UNS32 spare       :24;
            UNS32 AN_39_F     :1;
            UNS32 AN_38_F     :1;
            UNS32 AN_37_F     :1;
            UNS32 AN_36_F     :1;
            UNS32 AN_35_F     :1;
            UNS32 AN_34_F     :1;
            UNS32 AN_33_F     :1;
            UNS32 AN_32_F     :1;
        }
        B;
    }
    internal_voltage_h_F;
    BOOLEAN watchdog_F;
    BOOLEAN supply_interrupt_detection_F;
    BOOLEAN interrupt_time_detection_F;
}
T_MONITORING_HW;

/* T_MONITORING*/
typedef struct
{
    T_MONITORING_SW software;
    T_MONITORING_HW hardware;
}
T_MONITORING;

/* T_SET_2PH_STP_STEPCOUNT */
typedef struct
{
    struct
    {
        BOOLEAN SET_STEPCOUNT;
        INT32 STEPCOUNT_VALUE;
    }
    TAB_STEPCOUNT[NB_STEP_MOTOR];
}
T_SET_2PH_STP_STEPCOUNT;



/* T_BITE_MANAGEMENT */
typedef struct
{
    BOOLEAN F_enable_BITE_short_action;
    BOOLEAN F_enable_BITE_long_action;
}
T_BITE_MANAGEMENT;

/* ---- BSP INPUT STRUCTURE ---- */
/*! Data provide BY the APPLICATIVE SW */
typedef struct
{
    T_CAN_TX_VALUES             can_A_tx;
    T_CAN_TX_VALUES             can_B_tx;
    T_CAN_TX_VALUES             can_C_tx;
    
    T_AD2S1210_ENABLE           ad2s1210_enable;
    T_AD2S1210_FAULTS_RESET     ad2s1210_faults_reset;
                                
    T_DISC_OUTPUT_PORT          disc_out;
    T_DISC_OUTPUT_GPIO          disc_out_gpio;
                                

    T_ARINC_TX                  arinc_tx[ARINC_TX_NB];
    T_SCI_BUFFER_TX             scia_buffer_tx;  
                                
    T_TORQ_MOTOR                torq_motor;
    T_DC_MOTOR                  dc_motor;
    T_STP_MOTOR                 stp_motor_2ph;
    T_SET_2PH_STP_STEPCOUNT     stp_motor_2ph_set_stepcount;
    T_STP_MOTOR_2PH_CMD_FREQ    stp_motor_2ph_cmd_freq;

    BOOLEAN                     watchdog_rearm_flag;
    BOOLEAN                     F_SEU_detected;

    T_BITE_MANAGEMENT           bite_management;       
        
    T_LEAK_DETECTION_CMD        leak_detection_cmd;
}
T_BSP_INPUT;


/* ---- BSP OUTPUT STRUCTURE ---- */
/*! Data provide TO the APPLICATIVE SW */
typedef struct
{
/* T_BITE_STATUS shall be set to first parameter to be used in DefaultHandler function */
    T_BITE_STATUS           bite_status;
    T_CAN_RX_VALUES         can_A_rx;
    T_CAN_STATUS            can_A_status;
    T_CAN_RX_VALUES         can_B_rx;    
    T_CAN_STATUS            can_B_status;
    T_CAN_RX_VALUES         can_C_rx;
    T_CAN_STATUS            can_C_status;

    T_EQADC                 eqadc_acq;
    T_AD1255                ad1255_acq; 
    T_ADC128S052            adc128s052_acq;
    T_AD2S1210              ad2s1210;

    T_DISC_INPUT_PORT       disc_acq;
    T_DISC_INPUT_GPIO       disc_acq_gpio;

    T_STP_MOTOR             stepper_motor_status;

    T_ARINC_FIFO_RX         arinc_fifo_rx;
        
    T_SCI_BUFFER_RX         scia_buffer_rx;

    T_LEAK_DETECTION_ACQ    leak_detection_acq[LEAK_CONF_MAX];

    T_MONITORING            monitoring;

    T_IDENTIFICATION        identification;
}
T_BSP_OUTPUT;

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
extern T_CAN_TX_VALUES can_A_tx;
extern T_CAN_TX_VALUES can_B_tx;
extern T_CAN_TX_VALUES can_C_tx;

#pragma section DATA ".bss" ".bsp_interfaceIn"
extern T_BSP_INPUT    I_BSP_In;
#pragma section DATA ".bss" ".bsp_interfaceOut"
extern T_BSP_OUTPUT  I_BSP_Out;
#pragma section DATA ".bss"

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeInterface(void);
extern void SetApplicativeData(void);
extern void GetApplicativeData(void);
extern void ClearNumericalBusesReceptionBuffer(void);

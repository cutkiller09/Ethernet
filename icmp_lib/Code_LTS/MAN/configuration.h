#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
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
#define CAN_MB_NUMBER                       (UNS8)64
#define STP_MOTOR_NB                        (UNS8)1
#define ARINC_RX_FILTER_TABLE_SIZE   		(UNS32) 512
#define TAB_SW_MMU_CONFIG_MAX               (UNS8)18


/***************************************************************/
/*                                                             */
/*                      GLOBAL TYPES                           */
/*                                                             */
/***************************************************************/
/* T_ARINC_SPEED */
typedef struct
{
    BOOLEAN channel_TX1;
    BOOLEAN channel_TX2;
    BOOLEAN channel_RX1;
    BOOLEAN channel_RX2;
    BOOLEAN channel_RX3;
    BOOLEAN channel_RX4;
    BOOLEAN channel_RX5;
    UNS8    TAB_tx_buffer_size_configuration[ARINC_TX_NB];
    UNS8    TAB_rx_robustness_nbr_it_max[ARINC_RX_NB];
    UNS32   TAB_address_arinc_rx_filter;
}
T_ARINC_CONF;

/* T_CAN_CONFIGURATION */
typedef struct
{
    struct
    {
        union
        {
            UNS32 R;
            struct
            {
                UNS32:4;
                UNS32 CODE:4;
                UNS32:1;
                UNS32 SRR:1;
                UNS32 IDE:1;
                UNS32 RTR:1;
                UNS32 LENGTH:4;
                UNS32 TIMESTAMP:16;
            }
            B;
        }
        CS;
        union
        {
            UNS32 R;
            struct
            {
                UNS32:3;
                UNS32 STD_ID:11;
                UNS32 EXT_ID:18;
            }
            B;
        }
        ID;
    }
    box[CAN_MB_NUMBER];
    union
    {
        UNS32 R;
        struct
        {
            UNS32 PRESDIV:8;
            UNS32 RJW:2;
            UNS32 PSEG1:3;
            UNS32 PSEG2:3;
            UNS32 :1;
            UNS32 :1;
            UNS32 CLKSRC:1;
            UNS32 LPB:1;
            UNS32:4;
            UNS32 SMP:1;
            UNS32 :1;
            UNS32 :1;
            UNS32 :1;
            UNS32 :1;
            UNS32 PROPSEG:3;
        }
        B;
    }
    CR;
    UNS32 MAXMB;
    UNS32 RXGMASK;
    UNS32 RX14MASK;
    UNS32 RX15MASK;
    UNS32 IMRL;
    UNS32 IMRH;
    BOOLEAN F_can_enable;
    UNS8 TAB_list_of_rx_MB[CAN_MB_NUMBER];
    /*! number_of_rx_MB have to be less than CAN_MB_NUMBER */
    UNS8 number_of_rx_MB;
}
T_CAN_CONFIGURATION;

/* T_SCI_CONFIGURATION */
typedef struct
{
    UNS32 sci_speed;
}
T_SCI_CONFIGURATION;

/* T_STP_MOTOR_CONFIGURATION */
typedef struct
{
    struct
    {
        UNS32 overlap_time;
        UNS32 pwm_off_time;
        UNS32 pwm_on_time;
    }
    motor[STP_MOTOR_NB];
}
T_STP_MOTOR_CONFIGURATION;

/* ---- MMU CONFIGURATION INTERFACE ---- */
/* T_MAS_CONFIG */
typedef struct
{
   UNS32 mas1;
   UNS32 mas2;
   UNS32 mas3;
}
T_MAS_CONFIG;

/* T_MMU_CONFIGURATION */
typedef struct
{
   T_MAS_CONFIG TAB[TAB_SW_MMU_CONFIG_MAX];
}
T_MMU_CONFIGURATION;

/* T_LEAK_CONFIGURATION */
typedef struct
    {
    UNS32 clock_period;
    UNS32 init_test_delay;
    UNS32 setup_test_delay;
    UNS32 setup_mux_delay;
    UNS32 setup_conf_delay;
    UNS32 pulse_width;
    UNS32 leak_timeout;
}
T_LEAK_CONFIGURATION;

/* T_SPI_ENABLE */
typedef union
{
    UNS32 value;
    struct
    {
        UNS32 F_SPI_A_enable    :1;
        UNS32 F_SPI_B_enable    :1;
        UNS32 F_SPI_C_enable    :1;
        UNS32 F_SPI_D_enable    :1;
        UNS32                   :28;
    }
    B;
}
T_SPI_ENABLE;

/* T_AD2S1210_CONFIG */
typedef struct
{
    /* Configuration parameters */
    REAL32 LOS_THRESHOLD_configuration;
    REAL32 DOS_OVERRANGE_THRESHOLD_configuration;
    REAL32 DOS_MISMATCH_THRESHOLD_configuration;
    REAL32 DOS_RESET_MAX_THRESHOLD_configuration;
    REAL32 DOS_RESET_MIN_THRESHOLD_configuration;
    REAL32 LOT_HIGH_THRESHOLD_configuration;
    REAL32 LOT_LOW_THRESHOLD_configuration;

    BOOLEAN F_AD2S1210_perform_config;
    REAL32 FREQ_POBA_configuration;
    REAL32 FREQ_POBB_configuration;
    }
T_AD2S1210_CONFIG;

/* ----------- BSP BUS CONFIGURATION STRUCTURE ----------- */
typedef struct
{
    T_CAN_CONFIGURATION             can_A_message_box_conf;
    T_CAN_CONFIGURATION             can_B_message_box_conf;
    T_CAN_CONFIGURATION             can_C_message_box_conf;
    
    T_ARINC_CONF                    arinc_conf;
    T_SCI_CONFIGURATION             sci_conf;
    T_STP_MOTOR_CONFIGURATION       stp_motor_conf;
    T_AD2S1210_CONFIG               ad2s1210_config;
    T_LEAK_CONFIGURATION            leak_detection_conf;

    T_MMU_CONFIGURATION             MMU_configuration;

    T_DISC_OUTPUT_GPIO              disc_out_gpio;
    T_SPI_ENABLE                    SPI_enable;
    T_ADC128S052                    adc128s052_acq;
    T_AD2S1210_ENABLE               ad2s1210_enable;
    T_DC_MOTOR                      dc_motor;
}
T_BSP_CONFIGURATION;


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
#pragma section DATA ".bss" ".bsp_Configuration"
extern T_BSP_CONFIGURATION         I_BSP_conf;
#pragma section DATA ".bss"

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeConfiguration(void);
#endif

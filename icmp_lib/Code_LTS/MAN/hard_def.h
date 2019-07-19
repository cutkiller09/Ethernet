#ifndef __HARD_DEF_H__
#define __HARD_DEF_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         GLOBAL TYPES                        */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* Global system clock (Hz) */
#define SYSTEM_CLOCK                                   (UNS32) 112000000
#define PIT_PERIOD                                     (UNS32) 50

/* Memory mapping */
#define ERAM_ADDRESS                                   (UNS32)0x20000000
#define ERAM_SIZE                                      (UNS32)0x00200000
#define IRAM_ADDRESS                                   (UNS32)0x40000000
#define IRAM_SIZE                                      (UNS32)0x00010000

#define K_HW_PART_NUMBER_ADDRESS                       (UNS32)ERAM_ADDRESS
#define K_HW_NUMBER_SIZE                               (UNS32)32

/* I/O Port mapping */
#define I_O_ADDRESS                                    (UNS32) 0x20800000

/* Input Port mapping */
#define DI1_ADDRESS                                    *(volatile UNS32*)0x20900000
#define DI2_ADDRESS                                    *(volatile UNS32*)0x20920000
#define DI3_ADDRESS                                    *(volatile UNS32*)0x20940000
#define DI4_1_AUX_ADDRESS                              *(volatile UNS32*)0x20960000
#define DI4_2_AUX_ADDRESS                              *(volatile UNS32*)0x20964000
#define DI4_3_AUX_ADDRESS                              *(volatile UNS32*)0x20968000
#define DI4_4_AUX_ADDRESS                              *(volatile UNS32*)0x2096C000
#define DI4_5_AUX_ADDRESS                              *(volatile UNS32*)0x20970000
#define DI4_6_AUX_ADDRESS                              *(volatile UNS32*)0x20974000
#define DI4_7_AUX_ADDRESS                              *(volatile UNS32*)0x20978000

/* Output Port mapping */
#define DO_CLK_DO_1_5V_ADDRESS                         *(volatile UNS32*)0x20980000
#define DO_CLK_DO_2_5V_ADDRESS                         *(volatile UNS32*)0x20984000
#define DO_CLK_DO_3_5V_ADDRESS                         *(volatile UNS32*)0x20988000
#define DO_CLK_DO_4_5V_ADDRESS                         *(volatile UNS32*)0x2098C000
#define DO_CLK_DO_5_5V_ADDRESS                         *(volatile UNS32*)0x20990000
#define DO_CLK_DO_6_5V_ADDRESS                         *(volatile UNS32*)0x20994000
#define DO_CLK_DO_7_5V_ADDRESS                         *(volatile UNS32*)0x20998000

/* GPIO configuration */
#define GPIO_CANA_TX_PIN                               (UNS32) 83
#define GPIO_CANB_TX_PIN                               (UNS32) 85
#define GPIO_CANC_TX_PIN                               (UNS32) 87
#define GPIO_LOAD_CPU_1_PIN                            (UNS32) 179
#define GPIO_LOAD_CPU_2_PIN                            (UNS32) 180
#define GPIO_CH_COD_1_PIN                              (UNS32) 181
#define GPIO_CH_COD_2_PIN                              (UNS32) 182
#define GPIO_POS_1_PIN                                 (UNS32) 183
#define GPIO_POS_2_PIN                                 (UNS32) 184
#define GPIO_SPARE_1_PIN                               (UNS32) 185
#define GPIO_SPARE_2_PIN                               (UNS32) 186

#define GPIO_AMUX_0_PIN                                (UNS32) 188
#define GPIO_AMUX_1_PIN                                (UNS32) 189
#define GPIO_AMUX_2_PIN                                (UNS32) 190

#define GPIO_POW_INT_200MS_PIN                         (UNS32) 193
#define GPIO_N_IRQ_POW_WARN_PIN                        (UNS32) 194
#define GPIO_POW_INT_RES_200MS_PIN                     (UNS32) 195
#define GPIO_LED_PIN                                   (UNS32) 202
#define GPIO_N_POW_INT_TEST_200MS_PIN                  (UNS32) 203
#define GPIO_DI_PORT_TEST_PIN                          (UNS32) 204
#define GPIO_WDG_PIN                                   (UNS32) 205

/* eTPU pin configuration ARINC */
#define AR_IN_1_HI                                     (UNS32)(ETPU_A_OFFSET + CHANNEL_0)
#define AR_IN_2_HI                                     (UNS32)(ETPU_A_OFFSET + CHANNEL_2)
#define AR_IN_3_HI                                     (UNS32)(ETPU_A_OFFSET + CHANNEL_4)
#define AR_IN_4_HI                                     (UNS32)(ETPU_A_OFFSET + CHANNEL_6)
#define AR_IN_XTALK_HI                                 (UNS32)(ETPU_A_OFFSET + CHANNEL_8)

#define AR_OUT_1_HI                                    (UNS32)(CHANNEL_10)
#define AR_OUT_2_HI                                    (UNS32)(CHANNEL_12)

/* eTPU pin configuration DC MOTOR */
#define HEN1_DCM_1_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_14)
#define HEN2_DCM_1_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_15)
#define HEN1_DCM_2_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_16)
#define HEN2_DCM_2_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_17)
#define HEN1_DCM_3_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_18)
#define HEN2_DCM_3_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_19)
#define HEN1_DCM_4_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_20)
#define HEN2_DCM_4_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_21)
#define HEN1_DCM_5_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_22)
#define HEN2_DCM_5_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_23)
#define HEN1_DCM_6_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_24)
#define HEN2_DCM_6_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_25)
#define HEN1_DCM_7_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_26)
#define HEN2_DCM_7_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_27)
#define HEN1_DCM_8_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_28)
#define HEN2_DCM_8_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_29)
#define HEN1_DCM_9_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_30)
#define HEN2_DCM_9_CHANNEL                             (UNS32)(ETPU_A_OFFSET + CHANNEL_31)

#define HEN1_DCM_10_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_16)
#define HEN2_DCM_10_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_17)
#define HEN1_DCM_11_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_18)
#define HEN2_DCM_11_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_19)
#define HEN1_DCM_12_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_20)
#define HEN2_DCM_12_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_21)
#define HEN1_DCM_13_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_22)
#define HEN2_DCM_13_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_23)
#define HEN1_DCM_14_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_24)
#define HEN2_DCM_14_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_25)
#define HEN1_DCM_15_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_26)
#define HEN2_DCM_15_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_27)
#define HEN1_DCM_16_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_28)
#define HEN2_DCM_16_CHANNEL                            (UNS32)(ETPU_B_OFFSET + CHANNEL_29)

/* eTPU pin configuration STEP MOTOR 2PH  */
#define CLK_2PH_1_CHANNEL                              (UNS32)(ETPU_B_OFFSET + CHANNEL_11)
#define CLK_2PH_2_CHANNEL                              (UNS32)(ETPU_B_OFFSET + CHANNEL_12)
#define CMD_2PH_1_CHANNEL                              (UNS32)(ETPU_B_OFFSET + CHANNEL_13)
#define CMD_2PH_2_CHANNEL                              (UNS32)(ETPU_B_OFFSET + CHANNEL_14)

/* eMIOS pin configuration */
#define EMIOS_INTERNAL_COUNTER_A_CHANNEL               (UNS32)23
#define EMIOS_PWM_TM_OUT_1_CHANNEL                     (UNS32)4
#define EMIOS_PWM_TM_OUT_2_CHANNEL                     (UNS32)5
#define EMIOS_PWM_TM_OUT_3_CHANNEL                     (UNS32)6
#define EMIOS_PWM_TM_OUT_4_CHANNEL                     (UNS32)7
#define EMIOS_PWM_TM_OUT_5_CHANNEL                     (UNS32)8

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                       GLOBAL FUNCTIONS                      */
/*                                                             */
/***************************************************************/
#endif
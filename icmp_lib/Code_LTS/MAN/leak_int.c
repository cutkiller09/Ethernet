/***************************************************************/
/* FUNCTION : To define the standard type used by software     */
/*            configuration                                    */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "configuration.h"
#include "fifo_lb.h"
#include "hard_def.h"
#include "etpu_lb.h"
#include "cpu_lb.h"
#include "cpu_def.h"
#include "ad4005.h"
#include "cpu_load.h"
#include "etpu_LEAK_lb.h"

#include "leak_int.h"




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
#define LEAK_CHANNEL_START      (UNS8)1
#define LEAK_CHANNEL_END        (UNS8)10

/* LEAK TIMING VALUES (  x s * ETPU_SYSTEM_CLOCK_xxxx Hz) */
/* Leak clock period on TCR1                              */
#define LEAK_CLOCK_PERIOD       (UNS32) (0.0005   * ETPU_SYSTEM_CLOCK_TCR1)
/* Leak init test pin delay on TCR2 */
#define LEAK_INIT_TEST_DELAY    (UNS32) (2.0      * ETPU_SYSTEM_CLOCK_TCR2)
/* Leak setup test pin delay on TCR1 */
#define LEAK_SETUP_TEST_DELAY   (UNS32) (0.0001   * ETPU_SYSTEM_CLOCK_TCR1)
/* Leak setup mux pin delay on TCR1 */
#define LEAK_SETUP_MUX_DELAY    (UNS32) (0.0001   * ETPU_SYSTEM_CLOCK_TCR1)
/* Leak convstart pulse on TCR1 */
#define LEAK_PULSE_WIDTH_DELAY  (UNS32) (0.000005 * ETPU_SYSTEM_CLOCK_TCR1)
/* Leak setup conf delay on TCR1 */
#define LEAK_SETUP_CONV_DELAY   (UNS32) (0.000015 * ETPU_SYSTEM_CLOCK_TCR1)
/* Leak time out delay on TCR1 (ADC conversion time) */
#define LEAK_TIME_OUT_DELAY     (UNS32) (0.000002 * ETPU_SYSTEM_CLOCK_TCR1)

/* MUX signals index */
#define MUX_12_A1_INDEX            (UNS8)0
#define MUX_12_A2_INDEX            (UNS8)1
#define MUX_34_A0_INDEX            (UNS8)2
#define MUX_34_A1_INDEX            (UNS8)3
#define MUX_34_A2_INDEX            (UNS8)4

/* pin offset */
#define MUX_12_A1_PIN_OFFSET       (UNS8)1
#define MUX_12_A2_PIN_OFFSET       (UNS8)2
#define MUX_34_A0_PIN_OFFSET       (UNS8)3
#define MUX_34_A1_PIN_OFFSET       (UNS8)4
#define MUX_34_A2_PIN_OFFSET       (UNS8)5
#define TEST_A_PIN_OFFSET          (UNS8)6
#define TEST_B_PIN_OFFSET          (UNS8)7
#define CLOCK_PIN_OFFSET           (UNS8)8
#define CONV_START_PIN_OFFSET      (UNS8)9
#define PIN_INIT                   (UNS8)0x00

/* Pin selection mask  */
#define MASK_LEAK_TEST_A           (UNS16)0x0001
#define MASK_LEAK_TEST_B           (UNS16)0x0002
#define MASK_LEAK_MUX_12_A0        (UNS16)0x0004
#define MASK_LEAK_MUX_12_A1        (UNS16)0x0008
#define MASK_LEAK_MUX_12_A2        (UNS16)0x0010
#define MASK_LEAK_MUX_34_A0        (UNS16)0x0020
#define MASK_LEAK_MUX_34_A1        (UNS16)0x0040
#define MASK_LEAK_MUX_34_A2        (UNS16)0x0080
#define MASK_LEAK_POLARITY         (UNS16)0x8000

/* Pin selection shift  */
#define N_LEAK_TEST_A              (UNS32)0
#define N_LEAK_TEST_B              (UNS32)1
#define LEAK_MUX_12_A0             (UNS32)2
#define LEAK_MUX_12_A1             (UNS32)3
#define LEAK_MUX_12_A2             (UNS32)4
#define LEAK_MUX_34_A0             (UNS32)5
#define LEAK_MUX_34_A1             (UNS32)6
#define LEAK_MUX_34_A2             (UNS32)7
#define SHIFT_LEAK_POLARITY        (UNS32)15

const UNS16 K_TAB_LEAK_PIN_CONF[LEAK_CONF_MAX] =
{
    /* bit16 = polarity bit8 = MUX_34_A_2, bit7 = MUX_34_A_1, bit6 = MUX_34_A_0 ,bit5 = MUX_12_A_2*/
    /* bit4 = MUX_12_A_1, bit3 = MUX_12_A_0, bit2 = TEST LO, bit1 = TEST HI                       */
    /*ID Polarity   Measure         MUX_CONF   MUX_34_A_2_1_0  MUX_12_A_2_1_0   TEST_B   TEST_A  */
    /*1  Positive   LOOP1  HI         LOOP1          110             000           1        0    */
    /*2  Positive   LOOP1  LO         LOOP1          110             000           0        1    */
    /*3  Positive   LOOP1  TEST       LOOP1          110             000           1        1    */
    /*4  Positive   LOOP2  HI         LOOP2          110             001           1        0    */
    /*5  Positive   LOOP2  LO         LOOP2          110             001           0        1    */
    /*6  Positive   LOOP2  TEST       LOOP2          110             001           1        1    */
    /*7  Positive   LOOP3  HI         LOOP3          110             010           1        0    */
    /*8  Positive   LOOP3  LO         LOOP3          110             010           0        1    */
    /*9  Positive   LOOP3  TEST       LOOP3          110             010           1        1    */
    /*10 Positive   LOOP4  HI         LOOP4          110             011           1        0    */
    /*11 Positive   LOOP4  LO         LOOP4          110             011           0        1    */
    /*12 Positive   LOOP4  TEST       LOOP4          110             011           1        1    */
    /*13 Positive   LOOP5  HI         LOOP5          110             100           1        0    */
    /*14 Positive   LOOP5  LO         LOOP5          110             100           0        1    */
    /*15 Positive   LOOP5  TEST       LOOP5          110             100           1        1    */
    /*16 Positive   LOOP6  HI         LOOP6          000             110           1        0    */
    /*17 Positive   LOOP6  LO         LOOP6          000             110           0        1    */
    /*18 Positive   LOOP6  TEST       LOOP6          000             110           1        1    */
    /*19 Positive   LOOP7  HI         LOOP7          001             110           1        0    */
    /*20 Positive   LOOP7  LO         LOOP7          001             110           0        1    */
    /*21 Positive   LOOP7  TEST       LOOP7          001             110           1        1    */
    /*22 Positive   LOOP8  HI         LOOP8          010             110           1        0    */
    /*23 Positive   LOOP8  LO         LOOP8          010             110           0        1    */
    /*24 Positive   LOOP8  TEST       LOOP8          010             110           1        1    */
    /*25 Positive   LOOP9  HI         LOOP9          011             110           1        0    */
    /*26 Positive   LOOP9  LO         LOOP9          011             110           0        1    */
    /*27 Positive   LOOP9  TEST       LOOP9          011             110           1        1    */
    /*28 Positive   LOOP10 HI         LOOP10         100             110           1        0    */
    /*29 Positive   LOOP10 LO         LOOP10         100             110           0        1    */
    /*30 Positive   LOOP10 TEST       LOOP10         100             110           1        1    */
    /*31 Positive   GND HI            GND            101             101           1        0    */
    /*32 Positive   GND LO            GND            101             101           0        1    */
    /*33 Positive   GND TEST          GND            101             101           1        1    */
    /*34 Positive   VREF_LDL HI       VREF_LDL       111             111           1        0    */
    /*35 Positive   VREF_LDL LO       VREF_LDL       111             111           0        1    */
    /*36 Positive   VREF_LDL TEST     VREF_LDL       111             111           1        1    */
    
    (UNS16)0b1000000011000010,
    (UNS16)0b1000000011000001,
    (UNS16)0b1000000011000011,
    (UNS16)0b1000000011000110,
    (UNS16)0b1000000011000101,
    (UNS16)0b1000000011000111,
    (UNS16)0b1000000011001010,
    (UNS16)0b1000000011001001,
    (UNS16)0b1000000011001011,
    (UNS16)0b1000000011001110,
    (UNS16)0b1000000011001101,
    (UNS16)0b1000000011001111,
    (UNS16)0b1000000011010010,
    (UNS16)0b1000000011010001,
    (UNS16)0b1000000011010011,
    (UNS16)0b1000000000011010,
    (UNS16)0b1000000000011001,
    (UNS16)0b1000000000011011,
    (UNS16)0b1000000000111010,
    (UNS16)0b1000000000111001,
    (UNS16)0b1000000000111011,
    (UNS16)0b1000000001011010,
    (UNS16)0b1000000001011001,
    (UNS16)0b1000000001011011,
    (UNS16)0b1000000001111010,
    (UNS16)0b1000000001111001,
    (UNS16)0b1000000001111011,
    (UNS16)0b1000000010011010,
    (UNS16)0b1000000010011001,
    (UNS16)0b1000000010011011,
    (UNS16)0b1000000010110110,
    (UNS16)0b1000000010110101,
    (UNS16)0b1000000010110111,
    (UNS16)0b1000000011111110,
    (UNS16)0b1000000011111101,
    (UNS16)0b1000000011111111,
    
    /*ID Polarity   Measure        MUX_CONF   MUX_34_A_2_1_0  MUX_12_A_2_1_0   TEST_B   TEST_A  */
    /*37 Negative   LOOP1  HI         LOOP1          110             000           1        0    */
    /*38 Negative   LOOP1  LO         LOOP1          110             000           0        1    */
    /*39 Negative   LOOP1  TEST       LOOP1          110             000           1        1    */
    /*40 Negative   LOOP2  HI         LOOP2          110             001           1        0    */
    /*41 Negative   LOOP2  LO         LOOP2          110             001           0        1    */
    /*42 Negative   LOOP2  TEST       LOOP2          110             001           1        1    */
    /*43 Negative   LOOP3  HI         LOOP3          110             010           1        0    */
    /*44 Negative   LOOP3  LO         LOOP3          110             010           0        1    */
    /*45 Negative   LOOP3  TEST       LOOP3          110             010           1        1    */
    /*46 Negative   LOOP4  HI         LOOP4          110             011           1        0    */
    /*47 Negative   LOOP4  LO         LOOP4          110             011           0        1    */
    /*48 Negative   LOOP4  TEST       LOOP4          110             011           1        1    */
    /*49 Negative   LOOP5  HI         LOOP5          110             100           1        0    */
    /*50 Negative   LOOP5  LO         LOOP5          110             100           0        1    */
    /*51 Negative   LOOP5  TEST       LOOP5          110             100           1        1    */
    /*52 Negative   LOOP6  HI         LOOP6          000             110           1        0    */
    /*53 Negative   LOOP6  LO         LOOP6          000             110           0        1    */
    /*54 Negative   LOOP6  TEST       LOOP6          000             110           1        1    */
    /*55 Negative   LOOP7  HI         LOOP7          001             110           1        0    */
    /*56 Negative   LOOP7  LO         LOOP7          001             110           0        1    */
    /*57 Negative   LOOP7  TEST       LOOP7          001             110           1        1    */
    /*58 Negative   LOOP8  HI         LOOP8          010             110           1        0    */
    /*59 Negative   LOOP8  LO         LOOP8          010             110           0        1    */
    /*60 Negative   LOOP8  TEST       LOOP8          010             110           1        1    */
    /*61 Negative   LOOP9  HI         LOOP9          011             110           1        0    */
    /*62 Negative   LOOP9  LO         LOOP9          011             110           0        1    */
    /*63 Negative   LOOP9  TEST       LOOP9          011             110           1        1    */
    /*64 Negative   LOOP10 HI         LOOP10         100             110           1        0    */
    /*65 Negative   LOOP10 LO         LOOP10         100             110           0        1    */
    /*66 Negative   LOOP10 TEST       LOOP10         100             110           1        1    */
    /*67 Negative   GND HI            GND            101             101           1        0    */
    /*68 Negative   GND LO            GND            101             101           0        1    */
    /*69 Negative   GND TEST          GND            101             101           1        1    */
    /*70 Negative   VREF_LDL HI       VREF_LDL       111             111           1        0    */
    /*71 Negative   VREF_LDL LO       VREF_LDL       111             111           0        1    */
    /*72 Negative   VREF_LDL TEST     VREF_LDL       111             111           1        1    */
    
    (UNS16)0b0000000011000010,
    (UNS16)0b0000000011000001,
    (UNS16)0b0000000011000011,
    (UNS16)0b0000000011000110,
    (UNS16)0b0000000011000101,
    (UNS16)0b0000000011000111,
    (UNS16)0b0000000011001010,
    (UNS16)0b0000000011001001,
    (UNS16)0b0000000011001011,
    (UNS16)0b0000000011001110,
    (UNS16)0b0000000011001101,
    (UNS16)0b0000000011001111,
    (UNS16)0b0000000011010010,
    (UNS16)0b0000000011010001,
    (UNS16)0b0000000011010011,
    (UNS16)0b0000000000011010,
    (UNS16)0b0000000000011001,
    (UNS16)0b0000000000011011,
    (UNS16)0b0000000000111010,
    (UNS16)0b0000000000111001,
    (UNS16)0b0000000000111011,
    (UNS16)0b0000000001011010,
    (UNS16)0b0000000001011001,
    (UNS16)0b0000000001011011,
    (UNS16)0b0000000001111010,
    (UNS16)0b0000000001111001,
    (UNS16)0b0000000001111011,
    (UNS16)0b0000000010011010,
    (UNS16)0b0000000010011001,
    (UNS16)0b0000000010011011,
    (UNS16)0b0000000010110110,
    (UNS16)0b0000000010110101,
    (UNS16)0b0000000010110111,
    (UNS16)0b0000000011111110,
    (UNS16)0b0000000011111101,
    (UNS16)0b0000000011111111
};


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
UNS8                 current_leak_index;
BOOLEAN              F_leak_acq_to_be_done;
T_Etpu_fnc           etpu_LEAK_channel[ETPU_NUMBER_MAX][ETPU_CHANNEL_NUMBER_MAX];
T_LEAK_DETECTION_CMD leak_detection_cmd_copy;
T_LEAK_DETECTION_ACQ TAB_leak_detection_acq_copy[LEAK_CONF_MAX];
T_ETPU_LEAK_CONF     leak_conf_struct;


/***************************************************************/
/* Local function : SetLeakAcquisition                         */
/***************************************************************/
void SetLeakAcquisition(UNS8 a_leak_index)
{
    UNS8 leak_pol;
	
    /* Record the index of the leak measurement to do into current_leak_index   */
    current_leak_index = leak_detection_cmd_copy.TAB_configuration_id[a_leak_index] - 1;

    /* Clear current configuration index of leak_detection_cmd_copy */
    leak_detection_cmd_copy.TAB_configuration_id[a_leak_index] = 0;

    /* Build the TEST_HI/LO and MUX pins configuration in leak_conf_struct */
    leak_conf_struct.test_hi.pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                            & MASK_LEAK_TEST_A) >> N_LEAK_TEST_A;
    leak_conf_struct.test_lo.pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                            & MASK_LEAK_TEST_B) >> N_LEAK_TEST_B;

    leak_conf_struct.mux0_value        = (UNS8)((K_TAB_LEAK_PIN_CONF[current_leak_index]
                                            & MASK_LEAK_MUX_12_A0) >> LEAK_MUX_12_A0);
											
    leak_conf_struct.TAB_mux[MUX_12_A1_INDEX].pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                                            & MASK_LEAK_MUX_12_A1) >> LEAK_MUX_12_A1;
    leak_conf_struct.TAB_mux[MUX_12_A2_INDEX].pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                                            & MASK_LEAK_MUX_12_A2) >> LEAK_MUX_12_A2;
    leak_conf_struct.TAB_mux[MUX_34_A0_INDEX].pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                                            & MASK_LEAK_MUX_34_A0) >> LEAK_MUX_34_A0;
    leak_conf_struct.TAB_mux[MUX_34_A1_INDEX].pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                                            & MASK_LEAK_MUX_34_A1) >> LEAK_MUX_34_A1;
    leak_conf_struct.TAB_mux[MUX_34_A2_INDEX].pin_value = (BOOLEAN) (K_TAB_LEAK_PIN_CONF[current_leak_index]
                                                            & MASK_LEAK_MUX_34_A2) >> LEAK_MUX_34_A2;

    /* Get acquisition polarity from leak_detection_cmd_copy to leak_pol*/
    leak_pol = (UNS8) ((K_TAB_LEAK_PIN_CONF[current_leak_index] & MASK_LEAK_POLARITY) >> SHIFT_LEAK_POLARITY);

    /* Set F_leak_acq_to_be_done flag to TRUE to authorize the leak acquisitions */
    F_leak_acq_to_be_done = TRUE;

    /* Call EtpuStartLeakConversion function to Launch leak acquisition */
    EtpuStartLeakConversion(&etpu_LEAK_channel[ETPU_B][CHANNEL_1], leak_pol, &leak_conf_struct);
}


/***************************************************************/
/* Local function : GetLeakAcquisition                         */
/***************************************************************/
void GetLeakAcquisition(void)
{
    UNS8 i;
    UNS8 j;

    /* Copy TAB_leak_detection_acq_copy (acquisition from previous PIT) into the interface I_BSP_Out.leak_detection_acq */
    for(i=0;i < LEAK_CONF_MAX;i++)
    {
       /* Store acquisition data in the interface I_BSP_Out.leak_detection_acq */
       for(j=0;j < AD4005_INPUT_MAX;j++)
       {
          I_BSP_Out.leak_detection_acq[i].buffer[j] = TAB_leak_detection_acq_copy[i].buffer[j];
       }
    }
}


/***************************************************************/
/* Local function : GetLeakCommand                             */
/***************************************************************/
void GetLeakCommand(void)
{
    UNS8 i;

    /* Save the requested commands in I_BSP_In.leak_detection_cmd data into leak_detection_cmd_copy */
    for(i=0;i < LEAK_ACQ_CMD_NB_MAX;i++)
    {
        leak_detection_cmd_copy.TAB_configuration_id[i] = I_BSP_In.leak_detection_cmd.TAB_configuration_id[i];
    }
 }


/***************************************************************/
/* Local function : StartLeakAcquisition                       */
/***************************************************************/
void StartLeakAcquisition(void)
{
    UNS8 i;
    BOOLEAN F_measurement_to_do;

    /* IF SPI_D is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_D_enable == TRUE)
    {
        /* THEN */    
        /* Get the first leak measurement to do if requested */
        F_measurement_to_do = FALSE;
        i = 0;
        while ((F_measurement_to_do == FALSE) && (i < LEAK_ACQ_CMD_NB_MAX))
        {
            if (leak_detection_cmd_copy.TAB_configuration_id[i] > 0)
            {
                F_measurement_to_do = TRUE;
                SetLeakAcquisition (i);
            }
            else
            {
            }
            i++;
        }
    }
    else
    {
    }
}


/***************************************************************/
/* Global function : AcquireLeakDataTask                       */
/***************************************************************/
void AcquireLeakDataTask(void)
{
    /* Call StartTaskTimeMeasurement function for the LEAK_ACQUISITION task */
    StartTaskTimeMeasurement(LEAK_ACQUISITION);

    /********************************************************************/
    /* IF leak acquisition data and leak command data are not currently */
    /* updated by periodic interrupt                                    */
    /********************************************************************/
    if (F_leak_acq_to_be_done == TRUE)
    {
       /* THEN */
       /* Call ReadAD4005 function to get current_leak_index acquisition */
       ReadAD4005(&TAB_leak_detection_acq_copy[current_leak_index]);

       /* Clear the eTPU leak interrupt pending flag  */
       ETPU.CISR_B.R = 0x00000400;

       /* Call StartLeakAcquisition function to start next leak measurement */
       StartLeakAcquisition();
    }
    else
    {
        /* Robustness case:                                                                             */
        /* eTPU leak interrupt pending flag shall be also cleared when leak acquisitions not authorized */
        /* Clear the eTPU leak interrupt pending flag                                                   */
        ETPU.CISR_B.R = 0x00000400;
    }

    /* Call StopTaskTimeMeasurement function for the LEAK_ACQUISITION task */
    StopTaskTimeMeasurement(LEAK_ACQUISITION);
}


/***************************************************************/
/* Global function : ManageLeakAcquisition                     */
/***************************************************************/
void ManageLeakAcquisition(void)
{
    /* Forbid the leak acquisition during the update of interface leak data */
    F_leak_acq_to_be_done = FALSE;

    /* Get previous leak acquisitions for the APP software */
    GetLeakAcquisition();
    /* Get the next leak acquisitions to perform */
    GetLeakCommand();

    /* Call StartLeakAcquisition function to start the ADC conversion with the delay defined by the APPLICATIVE S/W */
    StartLeakAcquisition();
    
}


/***************************************************************/
/* Global function : InitializeLeakInterface                   */
/***************************************************************/
void InitializeLeakInterface(void)
{
    UNS8 i;
    UNS8 j;
    T_ETPU_LEAK_TIME leak_time_struct;

    /******************************************************/
    /* Initialise structure parameters etpu_LEAK_channel  */
    /*   -> loop eTPU B channels 1 to 10                  */
    /*   -> priority high for all channels                */
    /*   -> initialise parameter start address to 0       */
    /******************************************************/
    for (i = LEAK_CHANNEL_START; i <= LEAK_CHANNEL_END; i++)
    {
        etpu_LEAK_channel[ETPU_B][i].channel = ETPU_B_OFFSET + i;
        etpu_LEAK_channel[ETPU_B][i].priority = ETPU_PRIORITY_HIGH;
        etpu_LEAK_channel[ETPU_B][i].parameter_start_add = 0;
    }

    /* Prepare timing structure leak_time_struct */
    leak_time_struct.t_clock_period =   I_BSP_conf.leak_detection_conf.clock_period;
    leak_time_struct.t_init_test =      I_BSP_conf.leak_detection_conf.init_test_delay;
    leak_time_struct.t_setup_test =     I_BSP_conf.leak_detection_conf.setup_test_delay;
    leak_time_struct.t_setup_mux =      I_BSP_conf.leak_detection_conf.setup_mux_delay;
    leak_time_struct.t_setup_conf =     I_BSP_conf.leak_detection_conf.setup_conf_delay;
    leak_time_struct.t_pulse_width =    I_BSP_conf.leak_detection_conf.pulse_width;
    leak_time_struct.t_leak_timeout =   I_BSP_conf.leak_detection_conf.leak_timeout;

    /* Leak configuration structure */
    leak_conf_struct.nb_mux_signals = NB_MUX_SIGNALS;
    /* Initialize mux A0 pin (reference pin) */
    leak_conf_struct.mux0_value = PIN_INIT;
    /* Initialize others mux pin offset  */
    leak_conf_struct.TAB_mux[MUX_12_A1_INDEX].pin_offset = MUX_12_A1_PIN_OFFSET;
    leak_conf_struct.TAB_mux[MUX_12_A2_INDEX].pin_offset = MUX_12_A2_PIN_OFFSET;
    leak_conf_struct.TAB_mux[MUX_34_A0_INDEX].pin_offset = MUX_34_A0_PIN_OFFSET;
    leak_conf_struct.TAB_mux[MUX_34_A1_INDEX].pin_offset = MUX_34_A1_PIN_OFFSET;
    leak_conf_struct.TAB_mux[MUX_34_A2_INDEX].pin_offset = MUX_34_A2_PIN_OFFSET;
    /* Initialize mux pins value */
    for (i = 0; i < (UNS8)(NB_MUX_SIGNALS-1); i++)
    {
        leak_conf_struct.TAB_mux[i].pin_value = (BOOLEAN)PIN_INIT;
    }
    /* Initialize test pins offset and values */
    leak_conf_struct.test_hi.pin_offset = TEST_A_PIN_OFFSET;
    leak_conf_struct.test_hi.pin_value  = (BOOLEAN)PIN_INIT;
    leak_conf_struct.test_lo.pin_offset = TEST_B_PIN_OFFSET;
    leak_conf_struct.test_lo.pin_value  = (BOOLEAN)PIN_INIT;
    /* Initialize clock pin */
    leak_conf_struct.clock_offset = CLOCK_PIN_OFFSET;
    /* Initialize convstart pin */
    leak_conf_struct.convstart_offset = CONV_START_PIN_OFFSET;


    /* Get starting address for the leak parameters area */
    etpu_LEAK_channel[ETPU_B][CHANNEL_1].parameter_start_add = data_free_ram;

    /* Call EtpuInitializeLeak function to Initialise leak output channels */
    /* Save free RAM position */
    data_free_ram = EtpuInitializeLeak(&etpu_LEAK_channel[ETPU_B][CHANNEL_1], &leak_time_struct, &leak_conf_struct);

    /* Initialize leak detection command data */
    current_leak_index = (UNS8)0;
    for(i=0;i < LEAK_ACQ_CMD_NB_MAX;i++)
    {
       leak_detection_cmd_copy.TAB_configuration_id[i] = 0;
    }
    /* Initialize leak acquisition data */
    for(i=0;i < LEAK_CONF_MAX;i++)
    {
       for(j=0;j < AD4005_INPUT_MAX;j++)
       {
           TAB_leak_detection_acq_copy[i].buffer[j] = 0;
       }
    }
    /* Set F_leak_acq_to_be_done flag to TRUE to authorize the leak acquisitions */
    F_leak_acq_to_be_done = TRUE;  
}

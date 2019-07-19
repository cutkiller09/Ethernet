/***************************************************************/
/* FUNCTION : Perform the analog input acquisitions            */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "configuration.h"

#include "adc128s052.h"
#include "cpu_def.h"
#include "cpu_lb.h"
#include "eqadc_lb.h"
#include "hard_def.h"

#include "anlg_acq.h"


/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
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
const UNS16 K_wait_time_for_mux_switching_in_us = 5;

const UNS8 K_TAB_gray_code[ANALOG_MULTIPLEXER_INPUT_NUMBER] =
{
    0,
    1,
    3,
    2,
    6,
    7,
    5,
    4
};


/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL DATA                             */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Local function : SelectMUX                                  */
/***************************************************************/
void SelectMUX(UNS8 a_channel_MUX_1_2)
{
    /* Select the input of the multiplexor (GPIO[188..190]) */
    /*              GPIO188 GPIO189 GPIO190                 */
    /*  Input 1      0       0       0                      */
    /*  Input 2      1       0       0                      */
    /*  Input 3      0       1       0                      */
    /*  Input 4      1       1       0                      */
    /*  Input 5      0       0       1                      */
    /*  Input 6      1       0       1                      */
    /*  Input 7      0       1       1                      */
    /*  Input 8      1       1       1                      */
    SIU.GPDO[GPIO_AMUX_0_PIN].R = (UNS8)((a_channel_MUX_1_2 >> 0) & 1);
    SIU.GPDO[GPIO_AMUX_1_PIN].R = (UNS8)((a_channel_MUX_1_2 >> 1) & 1);
    SIU.GPDO[GPIO_AMUX_2_PIN].R = (UNS8)((a_channel_MUX_1_2 >> 2) & 1);
}

/***************************************************************/
/* Local function : ReadExternalADC                            */
/***************************************************************/
void ReadExternalADC(void)
{
    UNS8 i, j;
    T_AD128S052Input AD128S052_inputs;

    /* IF SPI_A is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_A_enable == (UNS32)TRUE)
    /* THEN */
    {
        /* FOR each inputs of the multiplexer */
        for (j = 0 ; j < ANALOG_MULTIPLEXER_INPUT_NUMBER ; j ++)
        {
            /* Call SelectMUX function to select the input of the multiplexer according to gray code table */
            SelectMUX(K_TAB_gray_code[j]);

            /* Call Waitus function to wait at least 5 us */
            Waitus(K_wait_time_for_mux_switching_in_us);

            /* Call ReadAD128S052 function to acquire value on external ADC */
            ReadAD128S052(&AD128S052_inputs);

            /* FOR each inputs of the ADC */
            for (i = 0 ; i < EXT_ADC_INPUT_NUMBER ; i ++)
            {
                /* Store the read value into BSP interface data */
                I_BSP_Out.adc128s052_acq.TAB[i][K_TAB_gray_code[j]] = AD128S052_inputs.channel[i];
            }
        }
        /* END FOR */
    }
    else
    {
    }
}


/***************************************************************/
/* Global function : MakeAnalogInputAcquisition                */
/***************************************************************/
void MakeAnalogInputAcquisition(void)
{
    /***************************************************************/
    /* Call ReadAnalogInputsEQADC function to read Analog Input    */
    /*  from eQADC                                                 */
    /***************************************************************/
    ReadAnalogInputsEQADC();

    /*! External ADC acquisition */
    ReadExternalADC();
}

/***************************************************************/
/* FUNCTION : To define the standard type used by software     */
/*            on BSP and APP interface                         */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"
#include "cpu_def.h"
#include "interface.h"
#include "eqadc_lb.h"

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
#define EQADC_MCR_INIT              (UNS32)0x00000000
/* ENOQ; ADC0_EN = 1; ADC0_CR(ADC0_CLK_PS = 20) */
#define EQADC_CFIFO_0_CONF_INIT     (UNS32)0x80800901
#define EQADC_CFIFO_0_SW_TRIG       (UNS16)0x0410
/* ENOQ; ADC1_EN = 1; ADC0_CR(ADC1_CLK_PS = 20) */
#define EQADC_CFIFO_1_CONF_INIT     (UNS32)0x82800901
#define EQADC_CFIFO_1_SW_TRIG       (UNS16)0x0410
#define EQADC_CAL_SAMPLE_CNT        (UNS8) 10

#define FIFO_CMD_SIZE               (UNS8)(20)

#define ADC_0    (UNS8) 0
#define ADC_1    (UNS8) 1
#define INDEX_OFFSET_TAB_ADC_1  (UNS8) (INTERNAL_12BIT_ADC_ENTRY_NUMBER /2)

/* Conversion command of Channel 0 to 19, results stored in FIFO_0 */
const UNS32 K_TAB_eqadc_fifo_0[FIFO_CMD_SIZE] =
{
   (UNS32)0x01000000,
   (UNS32)0x01000100,
   (UNS32)0x01000200,
   (UNS32)0x01000300,
   (UNS32)0x01000400,
   (UNS32)0x01000500,
   (UNS32)0x01000600,
   (UNS32)0x01000700,
   (UNS32)0x01000800,
   (UNS32)0x01000900,
   (UNS32)0x01000A00,
   (UNS32)0x01000B00,
   (UNS32)0x01000C00,
   (UNS32)0x01000D00,
   (UNS32)0x01000E00,
   (UNS32)0x01000F00,
   (UNS32)0x01001000,
   (UNS32)0x01001100,
   (UNS32)0x01001200,
   (UNS32)0x81001300
};

/* Conversion command of Channel 20 to 39, results stored in FIFO_1 */
const UNS32 K_TAB_eqadc_fifo_1[FIFO_CMD_SIZE] =
{
   (UNS32)0x03101400,
   (UNS32)0x03101500,
   (UNS32)0x03101600,
   (UNS32)0x03101700,
   (UNS32)0x03101800,
   (UNS32)0x03101900,
   (UNS32)0x03101A00,
   (UNS32)0x03101B00,
   (UNS32)0x03101C00,
   (UNS32)0x03101D00,
   (UNS32)0x03101E00,
   (UNS32)0x03101F00,
   (UNS32)0x03102000,
   (UNS32)0x03102100,
   (UNS32)0x03102200,
   (UNS32)0x03102300,
   (UNS32)0x03102400,
   (UNS32)0x03102500,
   (UNS32)0x03102600,
   (UNS32)0x83102700
};


/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Local function : AutoCalibration                            */
/***************************************************************/
void AutoCalibration (UNS8 a_adc_number)
{
    UNS32  raw_result_25;
    UNS32  raw_result_75;
    UNS32  gain;
    VINT32 offset;
    UNS32  ADC_result;
    UNS8   i;


    /* Clear ADC result */
    ADC_result = 0;

    /* Perform 10 acquisitions of 25% VREF */
    for (i = 0; i < EQADC_CAL_SAMPLE_CNT; i++)
    {
        /* Send a command to perform an acquisition of 25% Vref Voltage (Channel 44) on the current ADC */
        /* EOQ = 1, LST=0b11, CHANNEL_NUMBER = 0x2C    */
        EQADC.CFPR[0].R = 0x800C2C00 | (UNS32)(a_adc_number << 25);

        /* Trigger CFIFO 0 using Single Scan SW mode */
        /* SSE = 1, MODE = 0b0001 */
        EQADC.CFCR[0].R = 0x0410;

        /* Wait for End Of Queue flag (EOQF) of CFIFO 0 */
        while ((EQADC.FISR[0].R & (UNS32)0x10000000) == (UNS32)0)
        {
        }

        /* Clear End Of Queue flag of CFIFO 0 */
        EQADC.FISR[0].R = 0x10000000;

        /* Check result of CFIFO 0 for new data */
        while ((EQADC.FISR[0].R & (UNS32)0x00020000) == (UNS32)0)
        {
        }

        /* Read CFIFO 0 to get result of the acquisition */
        ADC_result = ADC_result + EQADC.RFPR[0].R;

        /* Reset RFDF flag of CFIFO 0 */
        EQADC.FISR[0].R = 0x00020000;
    }

    /* Compute the average of the 10 previous acquisitions for 25% Vref voltage */
    raw_result_25 = ADC_result / (UNS32)EQADC_CAL_SAMPLE_CNT;

    /* Clear ADC result */
    ADC_result = 0;

    /* Perform 10 acquisitions of 75% VREF */
    for (i = 0; i < EQADC_CAL_SAMPLE_CNT; i++)
    {
        /* Send command to perform acquisition of 75% Vref Voltage (Channel 43) on the current ADC */
        /* EOQ = 1, LST=0b11, CHANNEL_NUMBER = 0x2B    */
        EQADC.CFPR[0].R = (UNS32)0x800C2B00 | (UNS32)(a_adc_number << 25);

        /* Trigger CFIFO 0 using Single Scan SW mode */
        /* SSE = 1, MODE = 0b0001 */
        EQADC.CFCR[0].R = 0x0410;

        /* Wait for End Of Queue flag (EOQF) of CFIFO 0 */
        while ((EQADC.FISR[0].R & (UNS32)0x10000000) == (UNS32)0)
        {
        }

        /* Clear End Of Queue flag of CFIFO 0 */
        EQADC.FISR[0].R = 0x10000000;

        /* Check result of CFIFO 0 for new data */
        while ((EQADC.FISR[0].R & (UNS32)0x00020000) == (UNS32)0)
        {
        }

        /* Read CFIFO 0 to get result of the acquisition */
        ADC_result = ADC_result + EQADC.RFPR[0].R;

        /* Reset RFDF flag of CFIFO 0 */
        EQADC.FISR[0].R = 0x00020000;
    }

    /* Compute the average of the 10 previous measures for 75% Vref voltage */
    raw_result_75 = ADC_result / (UNS32)EQADC_CAL_SAMPLE_CNT;



    /* Compute the gain of the current ADC by applying the following formula:       */
    /* GAIN = (CAL_RES75%VREF - CAL_RES25%VREF) / (RAW_RES75%VREF - RAW_RES25%VREF) */
    /* The gain operand is a 15-bit fixed point unsigned value                      */
    /* GAIN = ((0x3000 - 0x1000) << 14) / (RAW_RES75%VREF - RAW_RES25%VREF)         */
    gain = (UNS32)(0x8000000) / (UNS32)(raw_result_75 - raw_result_25);

    /* Compute the offset of the current ADC by applying the following formula: */
    /* OCC = CAL_RES75%VREF - GAIN*RAW_RES75%VREF – 2                           */
    offset = 0x3000 - ((VINT32)(gain * raw_result_75) >> 14) - 2;


    /* Send a command to write the computed calibration gain of the current ADC */
    /* Addr. 4 (GAIN) EOQ = 1 */
    EQADC.CFPR[0].R = (UNS32)0x80000004 | ((UNS32)(gain << 8) & (UNS32)0x00FFFF00) | (UNS32)(a_adc_number << 25);

    /* Trigger CFIFO 0 using Single Scan SW mode */
    EQADC.CFCR[0].R = 0x0410;

    /* Wait for End Of Queue flag of CFIFO 0 */
    while ((EQADC.FISR[0].R & (UNS32)0x10000000) == (UNS32)0)
    {
    }

    /* Clear End Of Queue flag of CFIFO 0 */
    EQADC.FISR[0].R = 0x10000000;


    /* Send a command to write the computed calibration offset of the current ADC */
    /* Addr. 5 (OFFSET) EOQ = 1 */
    EQADC.CFPR[0].R = (UNS32)0x80000005 | ((UNS32)(offset << 8) & (UNS32)0x00FFFF00) | (UNS32)(a_adc_number << 25);

    /* Trigger CFIFO 0 using Single Scan SW mode */
    EQADC.CFCR[0].R = 0x0410;

    /* Wait for End Of Queue flag of CFIFO 0 */
    while ((EQADC.FISR[0].R & (UNS32)0x10000000) == (UNS32)0)
    {
    }

    /* Clear End Of Queue flag of CFIFO 0 */
    EQADC.FISR[0].R = 0x10000000;
}


/***************************************************************/
/* Global function : InitializeEQADC                           */
/***************************************************************/
void InitializeEQADC(void)
{
    UNS8 i;

    /* eQADC initialization */
    EQADC.MCR.R = EQADC_MCR_INIT;

    /* Configure the CFIFO 0 for the ADC0 at 5.6 MHz */
    EQADC.CFPR[0].R = EQADC_CFIFO_0_CONF_INIT;
    /* Trigger CFIFO 0 using Single Scan SW mode */
    EQADC.CFCR[0].R = EQADC_CFIFO_0_SW_TRIG;

    /* Configure the CFIFO 1 for the ADC1 at 5.6 MHz */
    EQADC.CFPR[1].R = EQADC_CFIFO_1_CONF_INIT;
    /* Trigger CFIFO 1 using Single Scan SW mode */
    EQADC.CFCR[1].R = EQADC_CFIFO_1_SW_TRIG;

    /* Wait for End of Queue Flag for CFIFO 0 */
    while (EQADC.FISR[0].B.EOQF !=1)
    {
    }
    /* Clear End Of Queue flag for CFIFO 0 */
    EQADC.FISR[0].B.EOQF = 1;

    /* Wait for End of Queue Flag for CFIFO 1 */
    while (EQADC.FISR[1].B.EOQF !=1)
    {
    }
    /* Clear End Of Queue flag for CFIFO 1 */
    EQADC.FISR[1].B.EOQF = 1;

    /* Initialize result arrays */
    for(i = 0; i < INTERNAL_12BIT_ADC_ENTRY_NUMBER; i++)
    {
        I_BSP_Out.eqadc_acq.TAB_12_bits[i] = (UNS16)0;
    }

    /* Call AutoCalibration function to compute the gain and the offset of the ADC0 */
    AutoCalibration(ADC_0);
    /* Call AutoCalibration function to compute the gain and the offset of the ADC1 */
    AutoCalibration(ADC_1);
}


/***************************************************************/
/* Global function : ReadAnalogInputsEQADC                     */
/***************************************************************/
void ReadAnalogInputsEQADC(void)
{
    UNS16 i;
    UNS8 index_cmd_ADC;
    UNS8 nbr_received_data_ADC0;
    UNS8 nbr_received_data_ADC1;

    /* Initialization local data to 0*/
    index_cmd_ADC = 0;
    nbr_received_data_ADC0 = 0;
    nbr_received_data_ADC1 = 0;

    /* Trigger CFIFO 0 using Single Scan SW mode */
    EQADC.CFCR[0].R = EQADC_CFIFO_0_SW_TRIG;
    /* Trigger CFIFO 1 using Single Scan SW mode */
    EQADC.CFCR[1].R = EQADC_CFIFO_1_SW_TRIG;

    /* WHILE all ADC input value have not been acquired */
    while((UNS8)(nbr_received_data_ADC0 + nbr_received_data_ADC1) < INTERNAL_12BIT_ADC_ENTRY_NUMBER)
    /* DO */
    {
        /* Set 4 ADC commands into the CFPR0 and CFPR1 registers */
        for(i = 0; i < 4; i++)
        {
            EQADC.CFPR[0].R = K_TAB_eqadc_fifo_0[index_cmd_ADC];
            EQADC.CFPR[1].R = K_TAB_eqadc_fifo_1[index_cmd_ADC];
            index_cmd_ADC ++;
        }
        /* Wait for ADC0 data avaibility */
        i = 0;
        while(i != 4)
        {
            if (EQADC.FISR[0].B.RFCTR != 0)
            {
                /* Read and store the 4 acquired input data of ADC0 on I_BSP_Out.eqadc_acq*/
                I_BSP_Out.eqadc_acq.TAB_12_bits[nbr_received_data_ADC0] = (UNS16)(EQADC.RFPR[0].B.RFPOP >> 2);
                nbr_received_data_ADC0 ++;
                i++;
            }
            else
            {
            }
        }

        /* Wait for ADC1 data avaibility */
        i = 0;
        while(i != 4)
        {
            if (EQADC.FISR[1].B.RFCTR != 0)
            {
                /* Read and store the 4 acquired input data of ADC1 on I_BSP_Out.eqadc_acq*/
                I_BSP_Out.eqadc_acq.TAB_12_bits[nbr_received_data_ADC1 + INDEX_OFFSET_TAB_ADC_1] = (UNS16)(EQADC.RFPR[1].B.RFPOP >> 2);
                nbr_received_data_ADC1 ++;
                i++;
            }
            else
            {
            }
        }
    }
    /* END DO */


    /* Wait for End of Queue Flag for CFIFO 0 */
    while (EQADC.FISR[0].B.EOQF !=1)
    {
    }
    /* Clear End Of Queue flag for CFIFO 0 */
    EQADC.FISR[0].B.EOQF = 1;

    /* Wait for End of Queue Flag for CFIFO 1 */
    while (EQADC.FISR[1].B.EOQF !=1)
    {
    }
    /* Clear End Of Queue flag for CFIFO 1 */
    EQADC.FISR[1].B.EOQF = 1;
}

/***************************************************************/
/* FUNCTION : Driver for discrete inputs                       */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "hard_def.h"
#include "interface.h"
#include "main_tsk.h"
#include "disc_out.h"
#include "disc_acq.h"


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
/* Verify that the DI_TEST should be done every 800 ms         */
const UNS32 K_test_delay_in_ms   = 800;
#define D_PB1_TEST_SET_MASK (UNS32)0x00000800
#define D_SAF_TEST_SET_MASK (UNS32)0x00000100
#define D_PB1_TEST_RESET_MASK (UNS32)0xFFFFF7FF
#define D_SAF_TEST_RESET_MASK (UNS32)0xFFFFFEFF

/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/
typedef struct
{
    union
    {
        UNS32 status;
        struct
        {
            UNS32 spare                  :13;
            UNS32 disc_in_11_failure     :1;
            UNS32 disc_in_10_failure     :1;
            UNS32 disc_in_9_failure      :1;
            UNS32 disc_in_8_failure      :1;
            UNS32 disc_in_7_failure      :1;
            UNS32 disc_in_6_failure      :1;
            UNS32 disc_in_5_failure      :1;
            UNS32 disc_in_4_failure      :1;
            UNS32 disc_in_3_failure      :1;
            UNS32 disc_in_2_failure      :1;
            UNS32 disc_in_1_failure      :1;
        }
        B;
    }
    test_H;
    union
    {
        UNS32 status;
        struct
        {
            UNS32 spare                  :13;
            UNS32 disc_in_11_failure     :1;
            UNS32 disc_in_10_failure     :1;
            UNS32 disc_in_9_failure      :1;
            UNS32 disc_in_8_failure      :1;
            UNS32 disc_in_7_failure      :1;
            UNS32 disc_in_6_failure      :1;
            UNS32 disc_in_5_failure      :1;
            UNS32 disc_in_4_failure      :1;
            UNS32 disc_in_3_failure      :1;
            UNS32 disc_in_2_failure      :1;
            UNS32 disc_in_1_failure      :1;
        }
        B;
    }
    test_L;
}
T_Discrete_buffer_failures;

/***************************************************************/
/*                                                             */
/*                      LOCAL DATA                             */
/*                                                             */
/***************************************************************/
UNS32 test_start_TIME;

T_Discrete_buffer_failures disc_in_failures;

UNS32    last_disc_input1;
UNS32    disc_input1_MEM;
UNS32    last_disc_input2;
UNS32    disc_input2_MEM;
UNS32    last_disc_input3;
UNS32    disc_input3_MEM;
UNS32    last_disc_input4;
UNS32    disc_input4_MEM;
UNS32    last_disc_input5;
UNS32    disc_input5_MEM;
UNS32    last_disc_input6;
UNS32    disc_input6_MEM;
UNS32    last_disc_input7;
UNS32    disc_input7_MEM;
UNS32    last_disc_input8;
UNS32    disc_input8_MEM;
UNS32    last_disc_input9;
UNS32    disc_input9_MEM;
UNS32    last_disc_input10;
UNS32    disc_input10_MEM;
UNS32    last_disc_input11;
UNS32    disc_input11_MEM;

BOOLEAN  disc_GPDI_179_MEM;
BOOLEAN  disc_GPDI_180_MEM;
BOOLEAN  disc_GPDI_181_MEM;
BOOLEAN  disc_GPDI_182_MEM;

/***************************************************************/
/* Local function : ReadDiscreteInputBuffer                    */
/***************************************************************/
void ReadDiscreteInputBuffer(void)
{
    /*! local data */
    UNS32 disc_input;
    UNS32 out_word;

    /**************************************************************/
    /*    NOTE :                                                  */
    /*    ------                                                  */
    /*                                                            */
    /*    The discrete inputs are filtered (anti-bouncing filter) */
    /*    using the following logic :                             */
    /*                                                            */
    /*     If the disc. input is consecutively read with the      */
    /*        same value (last read value = current read value),  */
    /*     then, the taken value is the current reading value     */
    /*                                                            */
    /*     If the 'last' read value (value read during previous   */
    /*        sample) is not equal to the current read value (val.*/
    /*        read during the current sample),                    */
    /*     then, the taken value is the same that the value taken */
    /*           at previous sample                               */
    /*                                                            */
    /*    Samples :                                               */
    /*     |     |     |     |     |     |     |     |     |      */
    /*     V     V     V     V     V     V     V     V     V      */
    /*                                                            */
    /*    Current disc. input value (c) :                         */
    /*    ____      _______            __________________________ */
    /*       |______|     |____________|                          */
    /*                                                            */
    /*    Last discrete input value (l) :                         */
    /*    ( l is equal to c at previous sample)                   */
    /*    _________      _______           ______________________ */
    /*            |______|     |___________|                      */
    /*                                                            */
    /*    value taken for discrete input :                        */
    /*    __________________________           __________________ */
    /*                             |___________|                  */
    /*                                                            */
    /*    Memorized value taken for discrete input (m) :          */
    /*    ________________________________           ____________ */
    /*                                   |___________|            */
    /*                                                            */
    /*                                                            */
    /*    This logic could be simplified using the following      */
    /*    thrue table (give the result of filter) :               */
    /*                                                            */
    /*         +------------------+-----------+-----------+       */
    /*         | Last acq. (l)    |     0     |     1     |       */
    /*         +------------------+-----+-----+-----+-----+       */
    /*         | Current acq. (c) |  0  |  1  |  1  |  0  |       */
    /*         +-----------+------+-----+-----+-----+-----+       */
    /*         | Memorized |  0   |  0  |  0  |  1  |  0  |       */
    /*         |           +------+-----+-----+-----+-----+       */
    /*         | value (m) |  1   |  0  |  1  |  1  |  1  |       */
    /*         +-----------+------+-----+-----+-----+-----+       */
    /*                                                            */
    /*     Taken value = (c * l) + (c * m) + (l * m)              */
    /*                                                            */
    /**************************************************************/

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 1                                 */
    /*------------------------------------------------------------*/
    disc_input = DI1_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 1               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input1) |
               (disc_input       & disc_input1_MEM)  |
               (last_disc_input1 & disc_input1_MEM);
    last_disc_input1 = disc_input;

    if (out_word != disc_input1_MEM)
    {
      disc_input1_MEM = out_word;
      I_BSP_Out.disc_acq.port[0].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 2                                 */
    /*------------------------------------------------------------*/
    disc_input = DI2_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 2               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input2) |
               (disc_input       & disc_input2_MEM)  |
               (last_disc_input2 & disc_input2_MEM);
    last_disc_input2 = disc_input;

    if (out_word != disc_input2_MEM)
    {
      disc_input2_MEM = out_word;
      I_BSP_Out.disc_acq.port[1].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 3                                 */
    /*------------------------------------------------------------*/
    disc_input = DI3_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 3               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input3) |
               (disc_input       & disc_input3_MEM)  |
               (last_disc_input3 & disc_input3_MEM);
    last_disc_input3 = disc_input;

    if (out_word != disc_input3_MEM)
    {
      disc_input3_MEM = out_word;
      I_BSP_Out.disc_acq.port[2].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 1 of Auxiliary Board  */
    /*------------------------------------------------------------*/
    disc_input = DI4_1_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 4               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input4) |
               (disc_input       & disc_input4_MEM)  |
               (last_disc_input4 & disc_input4_MEM);
    last_disc_input4 = disc_input;

    if (out_word != disc_input4_MEM)
    {
      disc_input4_MEM = out_word;
      I_BSP_Out.disc_acq.port[3].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 2 of Auxiliary Board  */
    /*------------------------------------------------------------*/
    disc_input = DI4_2_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 4               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input5) |
               (disc_input       & disc_input5_MEM)  |
               (last_disc_input5 & disc_input5_MEM);
    last_disc_input5 = disc_input;

    if (out_word != disc_input5_MEM)
    {
      disc_input5_MEM = out_word;
      I_BSP_Out.disc_acq.port[4].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 3 of Auxiliary Board  */
    /*------------------------------------------------------------*/
    disc_input = DI4_3_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 4               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input6) |
               (disc_input       & disc_input6_MEM)  |
               (last_disc_input6 & disc_input6_MEM);
    last_disc_input6 = disc_input;

    if (out_word != disc_input6_MEM)
    {
      disc_input6_MEM = out_word;
      I_BSP_Out.disc_acq.port[5].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 4 of Auxiliary Board  */
    /*------------------------------------------------------------*/
    disc_input = DI4_4_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 4               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input7) |
               (disc_input       & disc_input7_MEM)  |
               (last_disc_input7 & disc_input7_MEM);
    last_disc_input7 = disc_input;

    if (out_word != disc_input7_MEM)
    {
      disc_input7_MEM = out_word;
      I_BSP_Out.disc_acq.port[6].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 5 of Auxiliary Board   */
    /*------------------------------------------------------------*/
    disc_input = DI4_5_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 5               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input8) |
               (disc_input       & disc_input8_MEM)  |
               (last_disc_input8 & disc_input8_MEM);
    last_disc_input8 = disc_input;

    if (out_word != disc_input8_MEM)
    {
      disc_input8_MEM = out_word;
      I_BSP_Out.disc_acq.port[7].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 6 of Auxiliary Board  */
    /*------------------------------------------------------------*/
    disc_input = DI4_6_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 6               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input9) |
               (disc_input       & disc_input9_MEM)  |
               (last_disc_input9 & disc_input9_MEM);
    last_disc_input9 = disc_input;

    if (out_word != disc_input9_MEM)
    {
      disc_input9_MEM = out_word;
      I_BSP_Out.disc_acq.port[8].data = out_word;
    }
    else
    {
    }

    /*------------------------------------------------------------*/
    /*    DISCRETE INPUT BUFFER 4 - DI Port 7 of Auxiliary Board  */
    /*------------------------------------------------------------*/
    disc_input = DI4_7_AUX_ADDRESS;

    /**************************************************************/
    /* - Filter all bits of DISCRETE INPUT BUFFER 7               */
    /* IF (After filtering any bit has changed)                   */
    /*   THEN                                                     */
    /*   - Memorize result of filtering                           */
    /**************************************************************/
    out_word = (disc_input       & last_disc_input10) |
               (disc_input       & disc_input10_MEM)  |
               (last_disc_input10 & disc_input10_MEM);
    last_disc_input10 = disc_input;

    if (out_word != disc_input10_MEM)
    {
      disc_input10_MEM = out_word;
      I_BSP_Out.disc_acq.port[9].data = out_word;
    }
    else
    {
    }
}

/***************************************************************/
/* Local function : DebounceDiscrete                           */
/***************************************************************/
BOOLEAN DebounceDiscrete(BOOLEAN discrete_input, BOOLEAN *discrete_input_mem)
{
    BOOLEAN discrete_filtered;
    
    if (discrete_input == *discrete_input_mem)
    {
        discrete_filtered = discrete_input;
    }
    else
    {
        /* if the discrete value is not equal to the previous one: */
        /* - keep the previous value                               */
        /* - update memorized value                                */
        discrete_filtered = *discrete_input_mem;
        *discrete_input_mem = discrete_input;
    }
    
    return (discrete_filtered);
}

/***************************************************************/
/* Local function : ReadDiscreteInputGpio                      */
/***************************************************************/
void ReadDiscreteInputGpio(void)
{
    /******************************************************************/
    /* Store all bit of the GPIO discrete input into the structure    */
    /* provided to the Applicative S/W                                */
    /******************************************************************/
    
    I_BSP_Out.disc_acq_gpio.HW_GPIO_111 = SIU.GPDI[111].B.PDI;
    I_BSP_Out.disc_acq_gpio.HW_GPIO_112 = SIU.GPDI[112].B.PDI;
    I_BSP_Out.disc_acq_gpio.HW_GPIO_179 = DebounceDiscrete((BOOLEAN) (SIU.GPDI[179].B.PDI), &disc_GPDI_179_MEM);
    I_BSP_Out.disc_acq_gpio.HW_GPIO_180 = DebounceDiscrete((BOOLEAN) (SIU.GPDI[180].B.PDI), &disc_GPDI_180_MEM);
    I_BSP_Out.disc_acq_gpio.HW_GPIO_181 = DebounceDiscrete((BOOLEAN) (SIU.GPDI[181].B.PDI), &disc_GPDI_181_MEM);
    I_BSP_Out.disc_acq_gpio.HW_GPIO_182 = DebounceDiscrete((BOOLEAN) (SIU.GPDI[182].B.PDI), &disc_GPDI_182_MEM);
    I_BSP_Out.disc_acq_gpio.HW_GPIO_193 = SIU.GPDI[193].B.PDI;
    I_BSP_Out.disc_acq_gpio.HW_GPIO_194 = SIU.GPDI[194].B.PDI;
}

/***************************************************************/
/* Local function : TestDiscreteInputBuffer                    */
/***************************************************************/
void TestDiscreteInputBuffer(void)
{
    T_DISC_INPUT_PORT local_discrete_port_value;

    /* Each 800 ms */
    if ((UNS32)(MC_PIT_NUMBER - test_start_TIME) >= (K_test_delay_in_ms / PIT_PERIOD))
    {
        /* Initialize test data */
        test_start_TIME = MC_PIT_NUMBER;
        disc_in_failures.test_H.status = 0;
        disc_in_failures.test_L.status = 0;

        /* Test High state */
        SIU.GPDO[GPIO_DI_PORT_TEST_PIN].B.PDO = (UNS32)TRUE;
        DO_CLK_DO_1_5V_ADDRESS = disc_output_1.buffer;
        DO_CLK_DO_2_5V_ADDRESS = disc_output_2.buffer;
        DO_CLK_DO_3_5V_ADDRESS = disc_output_3.buffer;
        DO_CLK_DO_4_5V_ADDRESS = disc_output_4.buffer;
        DO_CLK_DO_5_5V_ADDRESS = disc_output_5.buffer;
        DO_CLK_DO_6_5V_ADDRESS = disc_output_6.buffer;
        DO_CLK_DO_7_5V_ADDRESS = disc_output_7.buffer;

        /* Read all discrete input port */
        local_discrete_port_value.port[0].data  = DI1_ADDRESS;
        local_discrete_port_value.port[1].data  = DI2_ADDRESS;
        local_discrete_port_value.port[2].data  = DI3_ADDRESS;

        disc_in_failures.test_H.B.disc_in_1_failure  = ~local_discrete_port_value.port[0].B.D_IO_00;
        disc_in_failures.test_H.B.disc_in_2_failure  = ~local_discrete_port_value.port[0].B.D_IO_15;
        disc_in_failures.test_H.B.disc_in_3_failure  = ~local_discrete_port_value.port[0].B.D_IO_16;
        disc_in_failures.test_H.B.disc_in_4_failure  = ~local_discrete_port_value.port[0].B.D_IO_31;

        disc_in_failures.test_H.B.disc_in_5_failure  = ~local_discrete_port_value.port[1].B.D_IO_00;
        disc_in_failures.test_H.B.disc_in_6_failure  = ~local_discrete_port_value.port[1].B.D_IO_15;
        disc_in_failures.test_H.B.disc_in_7_failure  = ~local_discrete_port_value.port[1].B.D_IO_16;
        disc_in_failures.test_H.B.disc_in_8_failure  = ~local_discrete_port_value.port[1].B.D_IO_31;

        disc_in_failures.test_H.B.disc_in_9_failure  = ~local_discrete_port_value.port[2].B.D_IO_00;
        disc_in_failures.test_H.B.disc_in_10_failure = ~local_discrete_port_value.port[2].B.D_IO_15;
        disc_in_failures.test_H.B.disc_in_11_failure = ~local_discrete_port_value.port[2].B.D_IO_16;

        /* Test Low state */
        SIU.GPDO[GPIO_DI_PORT_TEST_PIN].B.PDO = (UNS32)FALSE;
        DO_CLK_DO_1_5V_ADDRESS = disc_output_1.buffer;
        DO_CLK_DO_2_5V_ADDRESS = disc_output_2.buffer;
        DO_CLK_DO_3_5V_ADDRESS = disc_output_3.buffer;
        DO_CLK_DO_4_5V_ADDRESS = disc_output_4.buffer;
        DO_CLK_DO_5_5V_ADDRESS = disc_output_5.buffer;
        DO_CLK_DO_6_5V_ADDRESS = disc_output_6.buffer;
        DO_CLK_DO_7_5V_ADDRESS = disc_output_7.buffer;

        /* Read all discrete input port */
        local_discrete_port_value.port[0].data  = DI1_ADDRESS;
        local_discrete_port_value.port[1].data  = DI2_ADDRESS;
        local_discrete_port_value.port[2].data  = DI3_ADDRESS;

        disc_in_failures.test_L.B.disc_in_1_failure  = local_discrete_port_value.port[0].B.D_IO_00;
        disc_in_failures.test_L.B.disc_in_2_failure  = local_discrete_port_value.port[0].B.D_IO_15;
        disc_in_failures.test_L.B.disc_in_3_failure  = local_discrete_port_value.port[0].B.D_IO_16;
        disc_in_failures.test_L.B.disc_in_4_failure  = local_discrete_port_value.port[0].B.D_IO_31;

        disc_in_failures.test_L.B.disc_in_5_failure  = local_discrete_port_value.port[1].B.D_IO_00;
        disc_in_failures.test_L.B.disc_in_6_failure  = local_discrete_port_value.port[1].B.D_IO_15;
        disc_in_failures.test_L.B.disc_in_7_failure  = local_discrete_port_value.port[1].B.D_IO_16;
        disc_in_failures.test_L.B.disc_in_8_failure  = local_discrete_port_value.port[1].B.D_IO_31;

        disc_in_failures.test_L.B.disc_in_9_failure  = local_discrete_port_value.port[2].B.D_IO_00;
        disc_in_failures.test_L.B.disc_in_10_failure = local_discrete_port_value.port[2].B.D_IO_15;
        disc_in_failures.test_L.B.disc_in_11_failure = local_discrete_port_value.port[2].B.D_IO_16;

        /* Compute test status */
        I_BSP_Out.monitoring.hardware.discrete_buffer_F.status = (disc_in_failures.test_L.status | disc_in_failures.test_H.status);
    }
    else
    {
    }
}

/***************************************************************/
/* Global function : HandleDiscreteInputAcquisition            */
/***************************************************************/
void HandleDiscreteInputAcquisition(void)
{
    /******************************************************************/
    /* Call function ReadDiscreteInputBuffer to acquire               */
    /* discrete input  of port 1, port 2, port 3, and port 4          */
    /******************************************************************/
    ReadDiscreteInputBuffer();
    
    /******************************************************************/
    /* Call function ReadDiscreteInputGpio to acquire discrete        */
    /* input of GPIO and set it on I_BSP_Out.disc_acq_gpio            */
    /******************************************************************/
    ReadDiscreteInputGpio();

    /******************************************************************/
    /* Call function TestDiscreteInputBuffer to test the discrete     */
    /* input ports                                                    */
    /******************************************************************/
    TestDiscreteInputBuffer();
}


/***************************************************************/
/* Global function : InitializeDisc_acq                        */
/***************************************************************/
void InitializeDisc_acq(void)
{
   UNS32 out_word;

   test_start_TIME = 0;
   disc_in_failures.test_H.status = 0;
   disc_in_failures.test_L.status = 0;
 
   out_word = DI1_ADDRESS;
   last_disc_input1 = out_word;
   disc_input1_MEM = out_word;
   I_BSP_Out.disc_acq.port[0].data = out_word;
   
   out_word = DI2_ADDRESS;
   last_disc_input2 = out_word;
   disc_input2_MEM = out_word;
   I_BSP_Out.disc_acq.port[1].data = out_word;
   
   out_word = DI3_ADDRESS;
   last_disc_input3 = out_word;
   disc_input3_MEM = out_word;
   I_BSP_Out.disc_acq.port[2].data = out_word;
   
   out_word = DI4_1_AUX_ADDRESS;
   last_disc_input4 = out_word;
   disc_input4_MEM = out_word;
   I_BSP_Out.disc_acq.port[3].data = out_word;
   
   out_word = DI4_2_AUX_ADDRESS;
   last_disc_input5 = out_word;
   disc_input5_MEM = out_word;
   I_BSP_Out.disc_acq.port[4].data = out_word;

   out_word = DI4_3_AUX_ADDRESS;
   last_disc_input6 = out_word;
   disc_input6_MEM = out_word;
   I_BSP_Out.disc_acq.port[5].data = out_word;

   out_word = DI4_4_AUX_ADDRESS;
   last_disc_input7 = out_word;
   disc_input7_MEM = out_word;
   I_BSP_Out.disc_acq.port[6].data = out_word;

   out_word = DI4_5_AUX_ADDRESS;
   last_disc_input8 = out_word;
   disc_input8_MEM = out_word;
   I_BSP_Out.disc_acq.port[7].data = out_word;

   out_word = DI4_6_AUX_ADDRESS;
   last_disc_input9 = out_word;
   disc_input9_MEM = out_word;
   I_BSP_Out.disc_acq.port[8].data = out_word;

   out_word = DI4_7_AUX_ADDRESS;
   last_disc_input10 = out_word;
   disc_input10_MEM = out_word;
   I_BSP_Out.disc_acq.port[9].data = out_word;

   /******************************************************************/
   /* Call function ReadDiscreteInputGpio to acquire discrete        */
   /* input of GPIO and set it on I_BSP_Out.disc_acq_gpio            */
   /******************************************************************/
   disc_GPDI_179_MEM = (BOOLEAN)(SIU.GPDI[179].B.PDI);
   disc_GPDI_180_MEM = (BOOLEAN)(SIU.GPDI[180].B.PDI);   
   disc_GPDI_181_MEM = (BOOLEAN)(SIU.GPDI[181].B.PDI);
   disc_GPDI_182_MEM = (BOOLEAN)(SIU.GPDI[182].B.PDI);
   ReadDiscreteInputGpio();
}

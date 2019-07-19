/***************************************************************/
/* FUNCTION : Update discrete output buffer                    */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "hard_def.h"
#include "cpu_def.h"
#include "interface.h"
#include "hard_ini.h"
#include "cpu_lb.h"

#include "disc_out.h"

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
T_Do_buffer disc_output_1;
T_Do_buffer disc_output_2;
T_Do_buffer disc_output_3;
T_Do_buffer disc_output_4;
T_Do_buffer disc_output_5;
T_Do_buffer disc_output_6;
T_Do_buffer disc_output_7;

/* DC MOTOR VARIABLES */
BOOLEAN HW_LEN1_DCM_1;
BOOLEAN HW_LEN1_DCM_2;
BOOLEAN HW_LEN1_DCM_3;
BOOLEAN HW_LEN1_DCM_4;
BOOLEAN HW_LEN1_DCM_5;
BOOLEAN HW_LEN1_DCM_6;
BOOLEAN HW_LEN1_DCM_7;
BOOLEAN HW_LEN1_DCM_8;
BOOLEAN HW_LEN1_DCM_9;
BOOLEAN HW_LEN1_DCM_10;
BOOLEAN HW_LEN1_DCM_11;
BOOLEAN HW_LEN1_DCM_12;
BOOLEAN HW_LEN1_DCM_13;
BOOLEAN HW_LEN1_DCM_14;
BOOLEAN HW_LEN1_DCM_15;
BOOLEAN HW_LEN1_DCM_16;
/* DC MOTOR VARIABLES */
BOOLEAN HW_LEN2_DCM_1;
BOOLEAN HW_LEN2_DCM_2;
BOOLEAN HW_LEN2_DCM_3;
BOOLEAN HW_LEN2_DCM_4;
BOOLEAN HW_LEN2_DCM_5;
BOOLEAN HW_LEN2_DCM_6;
BOOLEAN HW_LEN2_DCM_7;
BOOLEAN HW_LEN2_DCM_8;
BOOLEAN HW_LEN2_DCM_9;
BOOLEAN HW_LEN2_DCM_10;
BOOLEAN HW_LEN2_DCM_11;
BOOLEAN HW_LEN2_DCM_12;
BOOLEAN HW_LEN2_DCM_13;
BOOLEAN HW_LEN2_DCM_14;
BOOLEAN HW_LEN2_DCM_15;
BOOLEAN HW_LEN2_DCM_16;
/* DC MOTOR VARIABLES */
BOOLEAN HW_EN_DCM_1;
BOOLEAN HW_EN_DCM_2;
BOOLEAN HW_EN_DCM_3;
BOOLEAN HW_EN_DCM_4;
BOOLEAN HW_EN_DCM_5;
BOOLEAN HW_EN_DCM_6;
BOOLEAN HW_EN_DCM_7;
BOOLEAN HW_EN_DCM_8;
BOOLEAN HW_EN_DCM_9;
BOOLEAN HW_EN_DCM_10;
BOOLEAN HW_EN_DCM_11;
BOOLEAN HW_EN_DCM_12;
BOOLEAN HW_EN_DCM_13;
BOOLEAN HW_EN_DCM_14;
BOOLEAN HW_EN_DCM_15;
BOOLEAN HW_EN_DCM_16;
/* TORQUE MOTOR VARIABLES */
BOOLEAN EN_TM_1;
BOOLEAN EN_TM_2;
BOOLEAN EN_TM_3;
BOOLEAN EN_TM_4;
BOOLEAN EN_TM_5;

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
/* Local function : ComputeDiscreteOutputBuffer                */
/***************************************************************/
void ComputeDiscreteOutputBuffer(void)
{
   /***************************************************************/
   /* Compute discrete output port 1 with:                        */
   /*      - N/A                                                  */
   /* Compute discrete AUX output port 1-2-3-4 with:              */
   /*      - the enable signals of DC motors 1 to 16              */
   /*      - the enable signals of DC motors 1 to 6   low side  1 */
   /*      - the enable signals of DC motors 1 to 6   low side  2 */
   /* Update the discrete output port 1                           */
   /* Update the discrete output port 2                           */
   /* Update the discrete output port 3                           */
   /* Update the discrete output port 4                           */
   /***************************************************************/
   disc_output_1.bin.bit0 = HW_EN_DCM_1;
   disc_output_1.bin.bit1 = HW_LEN1_DCM_1;
   disc_output_1.bin.bit2 = HW_LEN2_DCM_1;
   disc_output_1.bin.bit3 = HW_EN_DCM_2;
   disc_output_1.bin.bit4 = HW_LEN1_DCM_2;   
   disc_output_1.bin.bit5 = HW_LEN2_DCM_2;
   disc_output_1.bin.bit6 = HW_EN_DCM_3;
   disc_output_1.bin.bit7 = HW_LEN1_DCM_3;
   disc_output_1.bin.bit8 = HW_LEN2_DCM_3;
   disc_output_1.bin.bit9 = HW_EN_DCM_4;
   disc_output_1.bin.bit10 = HW_LEN1_DCM_4;    
   disc_output_1.bin.bit11 = HW_LEN2_DCM_4;    

   disc_output_2.bin.bit0 = HW_EN_DCM_5;
   disc_output_2.bin.bit1 = HW_LEN1_DCM_5;
   disc_output_2.bin.bit2 = HW_LEN2_DCM_5;
   disc_output_2.bin.bit3 = HW_EN_DCM_6;
   disc_output_2.bin.bit4 = HW_LEN1_DCM_6;   
   disc_output_2.bin.bit5 = HW_LEN2_DCM_6;
   disc_output_2.bin.bit6 = HW_EN_DCM_7;
   disc_output_2.bin.bit7 = HW_LEN1_DCM_7;
   disc_output_2.bin.bit8 = HW_LEN2_DCM_7;
   disc_output_2.bin.bit9 = HW_EN_DCM_8;
   disc_output_2.bin.bit10 = HW_LEN1_DCM_8;    
   disc_output_2.bin.bit11 = HW_LEN2_DCM_8; 

   disc_output_3.bin.bit0 = HW_EN_DCM_9;
   disc_output_3.bin.bit1 = HW_LEN1_DCM_9;
   disc_output_3.bin.bit2 = HW_LEN2_DCM_9;
   disc_output_3.bin.bit3 = HW_EN_DCM_10;
   disc_output_3.bin.bit4 = HW_LEN1_DCM_10;   
   disc_output_3.bin.bit5 = HW_LEN2_DCM_10;
   /* Attention: LEN1_DCM11 and EN_DCM11 are switched in the first HSI release */
   disc_output_3.bin.bit6 = HW_LEN1_DCM_11; 
   disc_output_3.bin.bit7 = HW_EN_DCM_11;
   disc_output_3.bin.bit8 = HW_LEN2_DCM_11;
   disc_output_3.bin.bit9 = HW_EN_DCM_12;
   disc_output_3.bin.bit10 = HW_LEN1_DCM_12;    
   disc_output_3.bin.bit11 = HW_LEN2_DCM_12; 

   disc_output_4.bin.bit0 = HW_EN_DCM_13;
   disc_output_4.bin.bit1 = HW_LEN1_DCM_13;
   disc_output_4.bin.bit2 = HW_LEN2_DCM_13;
   disc_output_4.bin.bit3 = HW_EN_DCM_14;
   disc_output_4.bin.bit4 = HW_LEN1_DCM_14;   
   disc_output_4.bin.bit5 = HW_LEN2_DCM_14;
   disc_output_4.bin.bit6 = HW_EN_DCM_15;
   disc_output_4.bin.bit7 = HW_LEN1_DCM_15;
   disc_output_4.bin.bit8 = HW_LEN2_DCM_15;
   disc_output_4.bin.bit9 = HW_EN_DCM_16;
   disc_output_4.bin.bit10 = HW_LEN1_DCM_16;    
   disc_output_4.bin.bit11 = HW_LEN2_DCM_16; 

   disc_output_5.bin.bit0 = I_BSP_In.disc_out.port[4].B.D_IO_00;   /*HW_EN_2PH_1_SUP;*/
   disc_output_5.bin.bit1 = I_BSP_In.disc_out.port[4].B.D_IO_01;   /*HW_EN_2PH_1_OUT;*/
   /* disc_output_5.bin.bit2 = N/A; */                                
   disc_output_5.bin.bit3 = I_BSP_In.disc_out.port[4].B.D_IO_03;   /*HW_EN_2PH_2_SUP;*/
   disc_output_5.bin.bit4 = I_BSP_In.disc_out.port[4].B.D_IO_04;   /*HW_EN_2PH_2_OUT;*/
   /* disc_output_5.bin.bit5 = N/A; */
   disc_output_5.bin.bit6  = EN_TM_1;  /*HW_EN_TM1;*/
   disc_output_5.bin.bit7  = EN_TM_2;  /*HW_EN_TM2;*/
   disc_output_5.bin.bit8  = EN_TM_3;  /*HW_EN_TM3;*/
   disc_output_5.bin.bit9  = EN_TM_4;  /*HW_EN_TM4;*/
   disc_output_5.bin.bit10 = EN_TM_5;  /*HW_EN_TM5;*/
   /* disc_output_5.bin.bit11 = N/A; */

   disc_output_6.buffer = I_BSP_In.disc_out.port[5].data;
   disc_output_7.buffer = I_BSP_In.disc_out.port[6].data;

   /* Write discrete output port data provide by Applicative S/W */
   /* Update the DO port of auxiliary Board */
   DO_CLK_DO_1_5V_ADDRESS = disc_output_1.buffer;
   DO_CLK_DO_2_5V_ADDRESS = disc_output_2.buffer;
   DO_CLK_DO_3_5V_ADDRESS = disc_output_3.buffer;
   DO_CLK_DO_4_5V_ADDRESS = disc_output_4.buffer;
   DO_CLK_DO_5_5V_ADDRESS = disc_output_5.buffer;
   DO_CLK_DO_6_5V_ADDRESS = disc_output_6.buffer;
   DO_CLK_DO_7_5V_ADDRESS = disc_output_7.buffer;

}

/***************************************************************/
/* Local function : ComputeDiscreteOutputGpio                  */
/***************************************************************/
void ComputeDiscreteOutputGpio(void)
{
    /******************************************************************/
    /* Set all GPIO discrete output provided from the Applicative     */
    /* S/W to the output                                              */
    /******************************************************************/
    SIU.GPDO[195].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_195;
    SIU.GPDO[199].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_199;
    SIU.GPDO[200].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_200;
    SIU.GPDO[201].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_201;
    /* blink led, done in BSP */
	/*SIU.GPDO[202].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_202;*/
	SIU.GPDO[203].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_203;
	SIU.GPDO[204].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_204;
    SIU.GPDO[206].B.PDO  =  I_BSP_In.disc_out_gpio.HW_GPIO_206;
}

/***************************************************************/
/* Global function : ComputeDiscreteOutput                     */
/***************************************************************/
void ComputeDiscreteOutput(void)
{
    /* Call ComputeDiscreteOutputBuffer function to drive the discrete outputs ports */
    ComputeDiscreteOutputBuffer();

    /* Call ComputeDiscreteOutputGpio function to drive the GPIO outputs */
    ComputeDiscreteOutputGpio();
}


/***************************************************************/
/* Global function : InitializeDisc_Out                        */
/***************************************************************/
void InitializeDisc_Out(void)
{
	UNS8 i;
   /* Initialize all data of compute of discrete ouput */
   disc_output_1.buffer = (UNS32)0;
   disc_output_2.buffer = (UNS32)0;
   disc_output_3.buffer = (UNS32)0;
   disc_output_4.buffer = (UNS32)0;
   disc_output_5.buffer = (UNS32)0;
   disc_output_6.buffer = (UNS32)0;
   disc_output_7.buffer = (UNS32)0;
   
   /* Initialize the HW_EN_2PH_x_SUP to TRUE */ 
   /* The initialization process > 20ms, so, the stepper motors will be driven >20ms after HW_EN_2PH_x_SUP are set to TRUE */ 
   disc_output_5.bin.bit0 = TRUE;
   disc_output_5.bin.bit3 = TRUE;
	
   /* Disable All EN_MOTOR signals */
   DO_CLK_DO_1_5V_ADDRESS = disc_output_1.buffer;
   DO_CLK_DO_2_5V_ADDRESS = disc_output_2.buffer;
   DO_CLK_DO_3_5V_ADDRESS = disc_output_3.buffer;
   DO_CLK_DO_4_5V_ADDRESS = disc_output_4.buffer;
   DO_CLK_DO_5_5V_ADDRESS = disc_output_5.buffer;
   DO_CLK_DO_6_5V_ADDRESS = disc_output_6.buffer;
   DO_CLK_DO_7_5V_ADDRESS = disc_output_7.buffer;

   HW_LEN1_DCM_1  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_2  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_3  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_4  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_5  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_6  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_7  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_8  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_9  = (BOOLEAN)FALSE;
   HW_LEN1_DCM_10 = (BOOLEAN)FALSE;
   HW_LEN1_DCM_11 = (BOOLEAN)FALSE;
   HW_LEN1_DCM_12 = (BOOLEAN)FALSE;
   HW_LEN1_DCM_13 = (BOOLEAN)FALSE;
   HW_LEN1_DCM_14 = (BOOLEAN)FALSE;
   HW_LEN1_DCM_15 = (BOOLEAN)FALSE;
   HW_LEN1_DCM_16 = (BOOLEAN)FALSE;  

   HW_LEN2_DCM_1  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_2  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_3  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_4  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_5  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_6  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_7  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_8  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_9  = (BOOLEAN)FALSE;
   HW_LEN2_DCM_10 = (BOOLEAN)FALSE;
   HW_LEN2_DCM_11 = (BOOLEAN)FALSE;
   HW_LEN2_DCM_12 = (BOOLEAN)FALSE;
   HW_LEN2_DCM_13 = (BOOLEAN)FALSE;
   HW_LEN2_DCM_14 = (BOOLEAN)FALSE;
   HW_LEN2_DCM_15 = (BOOLEAN)FALSE;
   HW_LEN2_DCM_16 = (BOOLEAN)FALSE;
   
   HW_EN_DCM_1  = (BOOLEAN)FALSE;
   HW_EN_DCM_2  = (BOOLEAN)FALSE;
   HW_EN_DCM_3  = (BOOLEAN)FALSE;
   HW_EN_DCM_4  = (BOOLEAN)FALSE;
   HW_EN_DCM_5  = (BOOLEAN)FALSE;
   HW_EN_DCM_6  = (BOOLEAN)FALSE;
   HW_EN_DCM_7  = (BOOLEAN)FALSE;
   HW_EN_DCM_8  = (BOOLEAN)FALSE;
   HW_EN_DCM_9  = (BOOLEAN)FALSE;
   HW_EN_DCM_10 = (BOOLEAN)FALSE;
   HW_EN_DCM_11 = (BOOLEAN)FALSE;
   HW_EN_DCM_12 = (BOOLEAN)FALSE;
   HW_EN_DCM_13 = (BOOLEAN)FALSE;
   HW_EN_DCM_14 = (BOOLEAN)FALSE;
   HW_EN_DCM_15 = (BOOLEAN)FALSE;
   HW_EN_DCM_16 = (BOOLEAN)FALSE;
   
   EN_TM_1 = (BOOLEAN)FALSE;
   EN_TM_2 = (BOOLEAN)FALSE;
   EN_TM_3 = (BOOLEAN)FALSE;
   EN_TM_4 = (BOOLEAN)FALSE;
   EN_TM_5 = (BOOLEAN)FALSE;
}


#ifndef __DISC_OUT_H__
#define __DISC_OUT_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL TYPES                           */
/*                                                             */
/***************************************************************/


typedef union
{
    UNS32 buffer;
    struct
    {
        UNS8 bit15  :1;
        UNS8 bit14  :1;
        UNS8 bit13  :1;
        UNS8 bit12  :1;
        UNS8 bit11  :1;
        UNS8 bit10  :1;
        UNS8 bit9   :1;
        UNS8 bit8   :1;
        UNS8 bit7   :1;
        UNS8 bit6   :1;
        UNS8 bit5   :1;
        UNS8 bit4   :1;
        UNS8 bit3   :1;
        UNS8 bit2   :1;
        UNS8 bit1   :1;
        UNS8 bit0   :1;
    }
    bin;
}
T_Do_buffer;


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/

/* Define the number of DC Motor */
#define NB_DCMOTOR    (UNS8) 16

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
extern T_Do_buffer disc_output_1;
extern T_Do_buffer disc_output_2;
extern T_Do_buffer disc_output_3;
extern T_Do_buffer disc_output_4;
extern T_Do_buffer disc_output_5;
extern T_Do_buffer disc_output_6;
extern T_Do_buffer disc_output_7;

extern BOOLEAN HW_LEN1_DCM_1;
extern BOOLEAN HW_LEN1_DCM_2;
extern BOOLEAN HW_LEN1_DCM_3;
extern BOOLEAN HW_LEN1_DCM_4;
extern BOOLEAN HW_LEN1_DCM_5;
extern BOOLEAN HW_LEN1_DCM_6;
extern BOOLEAN HW_LEN1_DCM_7;
extern BOOLEAN HW_LEN1_DCM_8;
extern BOOLEAN HW_LEN1_DCM_9;
extern BOOLEAN HW_LEN1_DCM_10;
extern BOOLEAN HW_LEN1_DCM_11;
extern BOOLEAN HW_LEN1_DCM_12;
extern BOOLEAN HW_LEN1_DCM_13;
extern BOOLEAN HW_LEN1_DCM_14;
extern BOOLEAN HW_LEN1_DCM_15;
extern BOOLEAN HW_LEN1_DCM_16;

extern BOOLEAN HW_LEN2_DCM_1;
extern BOOLEAN HW_LEN2_DCM_2;
extern BOOLEAN HW_LEN2_DCM_3;
extern BOOLEAN HW_LEN2_DCM_4;
extern BOOLEAN HW_LEN2_DCM_5;
extern BOOLEAN HW_LEN2_DCM_6;
extern BOOLEAN HW_LEN2_DCM_7;
extern BOOLEAN HW_LEN2_DCM_8;
extern BOOLEAN HW_LEN2_DCM_9;
extern BOOLEAN HW_LEN2_DCM_10;
extern BOOLEAN HW_LEN2_DCM_11;
extern BOOLEAN HW_LEN2_DCM_12;
extern BOOLEAN HW_LEN2_DCM_13;
extern BOOLEAN HW_LEN2_DCM_14;
extern BOOLEAN HW_LEN2_DCM_15;
extern BOOLEAN HW_LEN2_DCM_16;

extern BOOLEAN HW_EN_DCM_1;
extern BOOLEAN HW_EN_DCM_2;
extern BOOLEAN HW_EN_DCM_3;
extern BOOLEAN HW_EN_DCM_4;
extern BOOLEAN HW_EN_DCM_5;
extern BOOLEAN HW_EN_DCM_6;
extern BOOLEAN HW_EN_DCM_7;
extern BOOLEAN HW_EN_DCM_8;
extern BOOLEAN HW_EN_DCM_9;
extern BOOLEAN HW_EN_DCM_10;
extern BOOLEAN HW_EN_DCM_11;
extern BOOLEAN HW_EN_DCM_12;
extern BOOLEAN HW_EN_DCM_13;
extern BOOLEAN HW_EN_DCM_14;
extern BOOLEAN HW_EN_DCM_15;
extern BOOLEAN HW_EN_DCM_16;

extern BOOLEAN EN_TM_1;
extern BOOLEAN EN_TM_2;
extern BOOLEAN EN_TM_3;
extern BOOLEAN EN_TM_4;
extern BOOLEAN EN_TM_5;

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void ComputeDiscreteOutput(void);
extern void InitializeDisc_Out(void);
#endif
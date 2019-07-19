#ifndef __ADC128S052_H__
#define __ADC128S052_H__
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
typedef struct 
{
    UNS16 channel[EXT_ADC_INPUT_NUMBER];
}
T_AD128S052Input;


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeAD128S052(void);
extern void ReadAD128S052(T_AD128S052Input *a_read_input_PTR);
#endif
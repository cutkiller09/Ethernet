#ifndef __SCI_LB_H__
#define __SCI_LB_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                        GLOBAL TYPES                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                        GLOBAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void UnmaskSCI_A(void);
extern void GetSCI_A(void);
extern void SendSCI_A(void);
extern void SCITask_A(void);
extern void SendChar_A(UNS8 a_char);
extern void SendNumber_A(UNS32 a_number, UNS8 a_digit_number);
extern void InitializeSCI_Lb(void);
#endif
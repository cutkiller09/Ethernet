#ifndef __LEAK_INT_H__
#define __LEAK_INT_H__
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


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void ManageLeakAcquisition(void);
extern void InitializeLeakInterface(void);
extern void AcquireLeakDataTask(void);
#endif
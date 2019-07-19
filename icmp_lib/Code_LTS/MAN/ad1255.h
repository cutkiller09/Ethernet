#ifndef __AD1255_H__
#define __AD1255_H__
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
#define AD1255_TIMER_ETPU_CHANNEL       (UNS32)(ETPU_B_OFFSET + CHANNEL_0)


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
extern BOOLEAN F_AD1255_acquisition_ended;


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeAD1255(void);
extern UNS32 ReadAD1255(void);
extern void StartAD1255Conversion(void);
extern void WaitForEndOfAD1255Conversion(void);
#endif
#ifndef __MON_REGISTER_H__
#define __MON_REGISTER_H__
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
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeRegisterMonitoring(void);
extern void GetRegistersInformation(void);
extern void MonitorRegisters(void);
#endif
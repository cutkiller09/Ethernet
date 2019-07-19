#ifndef __ETPU_QOM_LB_H__
#define __ETPU_QOM_LB_H__
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
/* QOM HSR definitions */
#define HSR_QOM_INIT_HIGH_IMMEDIATE       (UNS8)7
#define HSR_QOM_INIT_LOW_IMMEDIATE        (UNS8)6
#define HSR_QOM_INIT_HIGH_REFERENCED      (UNS8)5
#define HSR_QOM_INIT_LOW_REFERENCED       (UNS8)4

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
extern void EtpuUpdateQOMStepperMotorEnable(UNS8 a_channel, REAL32 a_command, UNS32 a_period);
extern void EtpuUpdateAndStartQOMDCMotor(UNS8 a_channel, REAL32 a_command, UNS32 a_period);
extern void EtpuInitializeQOMDCMotors(void);
#endif
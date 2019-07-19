#ifndef __ETPU_STP_LB_H__
#define __ETPU_STP_LB_H__
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
    REAL32 command;
    UNS8   channel_cmd_1;
    BOOLEAN motor_stopped;
}
T_STP_CMD;

/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* HSR STP2 definitions */
#define HSR_ETPU_STP2_INIT                       (UNS8)1
#define HSR_ETPU_STP2_START                      (UNS8)6
#define HSR_ETPU_STP2_STOP                       (UNS8)2

/* HSR SPWM definitions */
#define HSR_ETPU_SPWM_INIT                       (UNS8)7
#define HSR_ETPU_SPWM_START                      (UNS8)5
#define HSR_ETPU_SPWM_STOP                       (UNS8)3

/* Configurations */
#define ETPU_USE_TCR1       (UNS8) 0
#define ETPU_USE_TCR2       (UNS8) 1

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
extern void EtpuInitializeStepperMotor(void);
extern void EtpuUpdateStepperMotorCommand(UNS8 a_channel, UNS16 a_frequency, UNS8 positive_cmd);
extern void EtpuStopStepperMotorCommand(UNS8 a_channel);
extern void EtpuStartStepperMotorCommand(UNS8 a_channel);
extern UNS32 EtpuGetStepperMotorPosition(UNS8 a_channel);
extern void EtpuSetStepperMotorPosition(UNS32 a_position, UNS8 a_channel);
#endif

#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__
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
/* Define DC motor reference */
typedef enum
{
    DC_MOTOR1  = 0,
    DC_MOTOR2  = 1,
    DC_MOTOR3  = 2,
    DC_MOTOR4  = 3,
    DC_MOTOR5  = 4,
    DC_MOTOR6  = 5,
    DC_MOTOR7  = 6,
    DC_MOTOR8  = 7,
    DC_MOTOR9  = 8,
    DC_MOTOR10 = 9,
    DC_MOTOR11 = 10,
    DC_MOTOR12 = 11,
    DC_MOTOR13 = 12,
    DC_MOTOR14 = 13,
    DC_MOTOR15 = 14,
    DC_MOTOR16 = 15
    }
T_Dc_motor;


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* Define refresh time period */
#define REFRESH_50MS  (UNS32)50



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
extern void DriveMotorOut(REAL32 a_Motor_Out_CMD, T_Dc_motor a_DC_Motor, UNS32 a_refresh_period_msec, BOOLEAN a_DC_Motor_EN);
extern void InitializeDcMotorsInterface(void);
#endif
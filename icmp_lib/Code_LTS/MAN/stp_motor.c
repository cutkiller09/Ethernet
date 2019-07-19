/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "hard_def.h"
#include "interface.h"
#include "cpu_lb.h"
#include "etpu_lb.h"
#include "etpu_STP_lb.h"
#include "gpr_lb.h"
#include "disc_out.h"

#include "stp_motor.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
#define STP_CMD_FREQUENCY     (UNS16) 250


/***************************************************************/
/*                                                             */
/*                       LOCAL CONSTANTS                       */
/*                                                             */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                        LOCAL TYPES                          */
/*                                                             */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
T_STP_CMD STP_cmd_motor_1;


/***************************************************************/
/* Local Function : DriveSTPMotor                              */
/***************************************************************/
void DriveSTPMotor(T_STP_CMD *a_STP_cmd)
{
    REAL32 unsigned_motor_CMD;
    UNS8 delay;
    UNS8 positive_cmd;

        

    /* IF the command to apply, coming from the Applicative S/W, is less than -20Hz or higher than 20Hz */
    if ((a_STP_cmd->command > (REAL32)20.0) || (a_STP_cmd->command < (REAL32)-20.0))
    /* THEN */
    {
        /* IF the command to appy, comming from the Applicative S/W, is more than 0.0 */
        if (a_STP_cmd->command > (REAL32)0.0)
        /* THEN */
        {
            positive_cmd = 1;
            /* Compute the command to an unsigned */
            unsigned_motor_CMD = a_STP_cmd->command;

        }
        /* ELSE */
        else
        {
           positive_cmd = 0;
            /* Compute the command to an unsigned */
            unsigned_motor_CMD = (REAL32)-1.0 * a_STP_cmd->command;
        }
        /* END IF */
        
        /* IF the motor was stopped */
        if (a_STP_cmd->motor_stopped == TRUE)
        /* THEN */
        {
            /* Call function EtpuUpdateSPWMStepperMotorCommand to update the delay of the PWM signals on slave eTPU command channel */
            EtpuUpdateStepperMotorCommand(a_STP_cmd->channel_cmd_1, unsigned_motor_CMD,positive_cmd);
            /* Call function SetHSRR to Start the eTPU SPWM channel */
            a_STP_cmd->motor_stopped = FALSE;
            SetHSRR(a_STP_cmd->channel_cmd_1,HSR_ETPU_STP2_START);
        }
        else
        {
           /* Call function EtpuUpdateSPWMStepperMotorCommand to update the delay of the PWM signals on slave eTPU command channel */
           EtpuUpdateStepperMotorCommand(a_STP_cmd->channel_cmd_1, unsigned_motor_CMD,positive_cmd);
        }
        /* END IF */


    }
    /* ELSE IF the motor is not previously stopped */
    else if (a_STP_cmd->motor_stopped == FALSE)
    {
        /*! Stop CMD signals */
        /* Call SetHSRR to stop the eTPU SPWM channel */
        SetHSRR(a_STP_cmd->channel_cmd_1,HSR_ETPU_STP2_STOP);
        a_STP_cmd->motor_stopped = TRUE;
        
        /*! Stop CMD  signals */

    }
    else    
    {
    }
    /* END IF */
}

/***************************************************************/
/* Global Function : DriveAllSTPMotors                         */
/***************************************************************/
void DriveAllSTPMotors(void)
{    
    /* Drive the stepper motors if new command is set by the applicative SW */
    STP_cmd_motor_1.command = I_BSP_In.stp_motor_2ph.HW_STP_MOTOR_1_CMD;
    I_BSP_Out.stepper_motor_status.STEPCOUNT_VALUE  = EtpuGetStepperMotorPosition(STP_cmd_motor_1.channel_cmd_1);

    if(I_BSP_In.stp_motor_2ph.SET_STEPCOUNT == TRUE)
    {
       I_BSP_In.stp_motor_2ph.SET_STEPCOUNT = FALSE;
       EtpuSetStepperMotorPosition(I_BSP_In.stp_motor_2ph.STEPCOUNT_VALUE,STP_cmd_motor_1.channel_cmd_1);
    }
    else
    {

    }
    DriveSTPMotor(&STP_cmd_motor_1);

}

/***************************************************************/
/* Global Function : InitializeSTP_Motor                       */
/***************************************************************/
void InitializeSTP_Motor(void)
{
   UNS32 parameter_start;

    /* Initialize data for stepper motor module */
        
    /*! Motor 1 */
    STP_cmd_motor_1.command = I_BSP_In.stp_motor_2ph.HW_STP_MOTOR_1_CMD;
    STP_cmd_motor_1.channel_cmd_1 = (UNS8)CMD_2PH_1_CHANNEL;
    STP_cmd_motor_1.motor_stopped = TRUE;
    
    /* Call EtpuInitializeStepperMotor function to Initialize STP output channels */
    EtpuInitializeStepperMotor();
    


}

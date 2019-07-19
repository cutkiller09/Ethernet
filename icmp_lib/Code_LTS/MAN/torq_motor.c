/***************************************************************/
/* FUNCTION : Drive the torq motor                             */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "cpu_def.h"
#include "cpu_lb.h"

#include "hard_def.h"
#include "hard_ini.h"

#include "disc_out.h"

#include "torq_motor.h"


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


/***************************************************************/
/*                                                             */
/*                       LOCAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
#define EMIOS_FULL_SPEED_FACTOR      (UNS32)(0x00000002)
#define EMIOS_LOW_SPEED_FACTOR      (UNS32)(0x0000002F)

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
REAL32 torq_motor1_previous_cmd;
REAL32 torq_motor2_previous_cmd;
REAL32 torq_motor3_previous_cmd;
REAL32 torq_motor4_previous_cmd;
REAL32 torq_motor5_previous_cmd;

BOOLEAN torq_motor1_previous_EN;
BOOLEAN torq_motor2_previous_EN;
BOOLEAN torq_motor3_previous_EN;
BOOLEAN torq_motor4_previous_EN;
BOOLEAN torq_motor5_previous_EN;

REAL32 torq_motor_cmd;
REAL32 torq_motor_previous_cmd; 


/***************************************************************/
/* Local Function : EnableTorqueMotor	                       */
/***************************************************************/
BOOLEAN ManageTorqueMotorEnable(UNS8 a_Channel_TM, BOOLEAN a_TM_EN, BOOLEAN a_TM_previous_EN)
{
	BOOLEAN EN = a_TM_previous_EN;
	/* If the Enable goes from 0 to 1 */
	if((a_TM_EN == TRUE) && (a_TM_previous_EN == FALSE))
	{
		/*Set duty cycle to 0*/
		EMIOS.CH[a_Channel_TM].CADR.R = CLK_5KHZ;
		EMIOS.CH[a_Channel_TM].CBDR.R = CLK_5KHZ;
		/*Set enable to False */
		EN = TRUE;
	}
	else if((a_TM_EN == FALSE) && (a_TM_previous_EN == TRUE))
	{
		/*Set duty cycle to 0*/
		EMIOS.CH[a_Channel_TM].CADR.R = CLK_5KHZ;
		EMIOS.CH[a_Channel_TM].CBDR.R = CLK_5KHZ;
	}
	else if((a_TM_EN == TRUE) && (a_TM_previous_EN == TRUE))
	{
		/*Wait a cycle before setting enable to true (to respect delay of > 10 ms)*/
		EN = TRUE;
	}
	else
	{
		EN = FALSE;
	}
	return EN;
}

/***************************************************************/
/* Local Function : TorqMotorUpdateCommand                     */
/***************************************************************/
void TorqMotorUpdateCommand(REAL32 a_Channel_TM_command)
{
    /* Get absolute value of the torq_motor_cmd */
    if (a_Channel_TM_command < (REAL32)0.0)
    {
        torq_motor_cmd = - a_Channel_TM_command;
    }
    else if (a_Channel_TM_command > (REAL32)0.0)
    /* THEN */
    {
        torq_motor_cmd = + a_Channel_TM_command;
    }
    else
    {
    }
    /* END IF */
}

/***************************************************************/
/* Local Function : DriveTorqMotorCommand                      */
/***************************************************************/
void DriveTorqMotorCommand(UNS8 a_Channel_TM)
{   
	BOOLEAN TM_EN = FALSE;
    torq_motor_cmd = 0.0;
    torq_motor_previous_cmd = 0.0;
    
    switch(a_Channel_TM){
        case EMIOS_PWM_TM_OUT_1_CHANNEL:
			/* Check if the torque motor is enabled */
			TM_EN = (torq_motor1_previous_EN & I_BSP_In.torq_motor.torq_motor1_EN);
			/* Store the current enable value for next TM command */
			torq_motor1_previous_EN = I_BSP_In.torq_motor.torq_motor1_EN;
			/*If the interface is enabled, drive the torque motor*/
			if(TM_EN == TRUE)
			{
				/* Get absolute value of the command */
				TorqMotorUpdateCommand(I_BSP_In.torq_motor.torq_motor1_cmd);
				/* Set the last value TM command */
				torq_motor_previous_cmd = torq_motor1_previous_cmd;
				/* Save the current command for the next TM command */
				torq_motor1_previous_cmd = torq_motor_cmd;
			}
			/*ELSE keep the cmd at 0*/
			else
			{
				torq_motor1_previous_cmd = 0.0;
			}
            break;
        
        case EMIOS_PWM_TM_OUT_2_CHANNEL:
			/* Check if the torque motor is enabled */
			TM_EN = (torq_motor2_previous_EN & I_BSP_In.torq_motor.torq_motor2_EN);
			/* Store the current enable value for next TM command */
			torq_motor2_previous_EN = I_BSP_In.torq_motor.torq_motor2_EN;
			/*If the interface is enabled, drive the torque motor*/
			if (TM_EN == TRUE)
			{
				/* Get absolute value of the command */
				TorqMotorUpdateCommand(I_BSP_In.torq_motor.torq_motor2_cmd);
				/* Set the last value TM command */
				torq_motor_previous_cmd = torq_motor2_previous_cmd;
				/* Save the current command for the next TM command */
				torq_motor2_previous_cmd = torq_motor_cmd;
			}
			/*ELSE keep the cmd at 0*/
			else
			{
				torq_motor2_previous_cmd = 0.0;
			}
            break;
        
        case EMIOS_PWM_TM_OUT_3_CHANNEL:
			/* Check if the torque motor is enabled */
			TM_EN = (torq_motor3_previous_EN & I_BSP_In.torq_motor.torq_motor3_EN);
			/* Store the current enable value for next TM command */
			torq_motor3_previous_EN = I_BSP_In.torq_motor.torq_motor3_EN;
			/*If the interface is enabled, drive the torque motor*/
			if (TM_EN == TRUE)
			{
				/* Get absolute value of the command */
				TorqMotorUpdateCommand(I_BSP_In.torq_motor.torq_motor3_cmd);
				/* Set the last value TM command */
				torq_motor_previous_cmd = torq_motor3_previous_cmd;
				/* Save the current command for the next TM command */
				torq_motor3_previous_cmd = torq_motor_cmd;
			}
			/*ELSE keep the cmd at 0*/
			else
			{
				torq_motor3_previous_cmd = 0.0;
			}
            break;
        
        case EMIOS_PWM_TM_OUT_4_CHANNEL:
			/* Check if the torque motor is enabled */
			TM_EN = (torq_motor4_previous_EN & I_BSP_In.torq_motor.torq_motor4_EN);
			/* Store the current enable value for next TM command */
			torq_motor4_previous_EN = I_BSP_In.torq_motor.torq_motor4_EN;
			/*If the interface is enabled, drive the torque motor*/
			if (TM_EN == TRUE)
			{
				/* Get absolute value of the command */
				TorqMotorUpdateCommand(I_BSP_In.torq_motor.torq_motor4_cmd);
				/* Set the last value TM command */
				torq_motor_previous_cmd = torq_motor4_previous_cmd;
				/* Save the current command for the next TM command */
				torq_motor4_previous_cmd = torq_motor_cmd;
			}
			/*ELSE keep the cmd at 0*/
			else
			{
				torq_motor4_previous_cmd = 0.0;
			}
            break;
        
        case EMIOS_PWM_TM_OUT_5_CHANNEL:
			/* Check if the torque motor is enabled */
			TM_EN = (torq_motor5_previous_EN & I_BSP_In.torq_motor.torq_motor5_EN);
			/* Store the current enable value for next TM command */
			torq_motor5_previous_EN = I_BSP_In.torq_motor.torq_motor5_EN;
			/*If the interface is enabled, drive the torque motor*/
			if (TM_EN == TRUE)
			{
				/* Get absolute value of the command */
				TorqMotorUpdateCommand(I_BSP_In.torq_motor.torq_motor5_cmd);
				/* Set the last value TM command */
				torq_motor_previous_cmd = torq_motor5_previous_cmd;
				/* Save the current command for the next TM command */
				torq_motor5_previous_cmd = torq_motor_cmd;
			}
			/*ELSE keep the cmd at 0*/
			else
			{
				torq_motor5_previous_cmd = 0.0;
			}
            break;
        
        default:
        break;
    }
    
	/* If torque motor is enabled */
	if(TM_EN == TRUE)
	{
		/* Verify that the channel number is between 4 and 8*/
		if((a_Channel_TM >= EMIOS_PWM_TM_OUT_1_CHANNEL) || (a_Channel_TM <= EMIOS_PWM_TM_OUT_5_CHANNEL))
		{
			/* IF the new torq_motor_cmd differs from the current one */
			if (((torq_motor_cmd - torq_motor_previous_cmd) >  (REAL32)0.01) ||
				((torq_motor_cmd - torq_motor_previous_cmd) < (REAL32)(-0.01)))
			/* THEN */
			{
				/* IF the new torq_motor_cmd is less than or equals to 5, set it to 5 */
				if (torq_motor_cmd <= (REAL32)5)
				/* THEN */
				{
					/* Force CBDR and CADR register to CLK_5KHZ */
					EMIOS.CH[a_Channel_TM].CADR.R = CLK_5KHZ;
					EMIOS.CH[a_Channel_TM].CBDR.R = EMIOS_LOW_SPEED_FACTOR;
				}
				/* IF the new torq_motor_cmd is higher of equal to 95 than set it to 95 */
				else if (torq_motor_cmd >= (REAL32)95)
				/* THEN */
				{
					/* Force CBDR and CADR register to 95*/
					EMIOS.CH[a_Channel_TM].CADR.R = CLK_5KHZ;
					EMIOS.CH[a_Channel_TM].CBDR.R = EMIOS_FULL_SPEED_FACTOR;
				}
				/* ELSE */
				else
				{
					/* Force CADR register to initialize value */
					EMIOS.CH[a_Channel_TM].CADR.R = CLK_5KHZ;
			
					/* Compute the duty cycle to apply on DC motor and set the corresponding value on the eMIOS channel CBDR register */
					/* CBDR = (torq_motor_cmd from APP S/W / 100) * Channel frequency */
					EMIOS.CH[a_Channel_TM].CBDR.R = (UNS32)(((100u - (UNS32)torq_motor_cmd) * CLK_5KHZ) / 100u);
				}
			}
			else
			{
			}
			/* END IF */
		}
		else
		{
		}
		/*END IF*/
	}
	else
	{
		/*Set duty cycle to 0*/
		EMIOS.CH[a_Channel_TM].CADR.R = CLK_5KHZ;
		EMIOS.CH[a_Channel_TM].CBDR.R = CLK_5KHZ;
	}
	/*END If*/
}

/***************************************************************/
/* Global Function : DriveTorqMotor                            */
/***************************************************************/
void DriveTorqMotor(void)
{
	EN_TM_1 = ManageTorqueMotorEnable(EMIOS_PWM_TM_OUT_1_CHANNEL,I_BSP_In.torq_motor.torq_motor1_EN,torq_motor1_previous_EN);
	EN_TM_2 = ManageTorqueMotorEnable(EMIOS_PWM_TM_OUT_2_CHANNEL,I_BSP_In.torq_motor.torq_motor2_EN,torq_motor2_previous_EN);
	EN_TM_3 = ManageTorqueMotorEnable(EMIOS_PWM_TM_OUT_3_CHANNEL,I_BSP_In.torq_motor.torq_motor3_EN,torq_motor3_previous_EN);
	EN_TM_4 = ManageTorqueMotorEnable(EMIOS_PWM_TM_OUT_4_CHANNEL,I_BSP_In.torq_motor.torq_motor4_EN,torq_motor4_previous_EN);
	EN_TM_5 = ManageTorqueMotorEnable(EMIOS_PWM_TM_OUT_5_CHANNEL,I_BSP_In.torq_motor.torq_motor5_EN,torq_motor5_previous_EN);
	
    DriveTorqMotorCommand(EMIOS_PWM_TM_OUT_1_CHANNEL);
    DriveTorqMotorCommand(EMIOS_PWM_TM_OUT_2_CHANNEL);
    DriveTorqMotorCommand(EMIOS_PWM_TM_OUT_3_CHANNEL);
    DriveTorqMotorCommand(EMIOS_PWM_TM_OUT_4_CHANNEL);
    DriveTorqMotorCommand(EMIOS_PWM_TM_OUT_5_CHANNEL);
}

/***************************************************************/
/* Global Function : InitializeTorq_Motor                      */
/***************************************************************/
void InitializeTorq_Motor(void)
{
    /* Initialize data for Torque motor module */
	
    torq_motor1_previous_cmd = 0.0;
    torq_motor2_previous_cmd = 0.0;
    torq_motor3_previous_cmd = 0.0;
    torq_motor4_previous_cmd = 0.0;
    torq_motor5_previous_cmd = 0.0;
	
	torq_motor1_previous_EN = FALSE;
	torq_motor2_previous_EN = FALSE;
	torq_motor3_previous_EN = FALSE;
	torq_motor4_previous_EN = FALSE;
	torq_motor5_previous_EN = FALSE;
	
}


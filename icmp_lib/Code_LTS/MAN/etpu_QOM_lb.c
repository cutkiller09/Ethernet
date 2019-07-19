/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "./eTPU_Lib/eTPU_auto.h"
#include "dc_motor.h"
#include "stp_motor.h"

#include "etpu_lb.h"
#include "etpu_QOM_lb.h"
#include "hard_def.h"


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
/* LTS eTPU QOM function */
#define ETPU_QOM_LTS_FCT_NB                        (UNS8)_FUNCTION_NUM_eTPU_QOM_
/* OFFSET for uns32 pointer */                     
#define ETPU_QOM_OPTION_OFFSET                     (UNS32) 0x00
#define ETPU_QOM_OPTION_MASK                       (UNS32) 0xFF000000
#define ETPU_QOM_OPTION_SHIFT                      (UNS32) 24
                                                   
#define ETPU_QOM_EVENT_TABLE_END_OFFSET            (UNS32) 0x00
#define ETPU_QOM_EVENT_TABLE_END_MASK              (UNS32) 0x00FFFFFF
#define ETPU_QOM_EVENT_TABLE_END_SHIFT             (UNS32) 0
                                                   
#define ETPU_QOM_NB_LOOP_OFFSET                    (UNS32) 0x08
#define ETPU_QOM_NB_LOOP_MASK                      (UNS32) 0x00FFFFFF
#define ETPU_QOM_NB_LOOP_SHIFT                     (UNS32) 0
                                                   
#define ETPU_QOM_PTR_REFERENCE_OFFSET              (UNS32) 0x0C
#define ETPU_QOM_PTR_REFERENCE_MASK                (UNS32) 0x00FFFFFF
#define ETPU_QOM_PTR_REFERENCE_SHIFT               (UNS32) 0
                                                   
#define ETPU_QOM_FIRST_TABLE_EVENT_OFFSET          (UNS32) 0x14
#define ETPU_QOM_EVENT_TABLE_MASK                  (UNS32) 0xFFFFFFFF
#define ETPU_QOM_EVENT_TABLE_SHIFT                 (UNS32) 0
                                                   
#define ETPU_QOM_EVENT_PARAMETER_SIZE              (UNS32) 0x04
/* Function Option Bit Definitions */              
#define ETPU_QOM_USE_TCR1                          (UNS8)0
/* Function Mode Bit Definitions - mode options */
#define ETPU_QOM_SINGLE_SHOT                       (UNS8)0

/* Pin state */
#define ETPU_PIN_HIGH                              (UNS8)1
#define ETPU_PIN_LOW                               (UNS8)0


/***************************************************************/
/*                                                             */
/*                         LOCAL TYPES                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Local function : EtpuInitializeQOM                          */
/***************************************************************/
UNS32 EtpuInitializeQOM(UNS32 a_channel,
                        UNS32 a_parameter_start_addr,
                        UNS32 a_QOM_mode,
                        UNS8 a_interrupt_mode,
                        UNS8  a_channel_priority,
                        UNS8  a_time_base,
                        UNS8  a_number_event,
                        UNS32 a_nb_loop,
                        UNS32 a_master_time_reference)
{
    UNS32 parameter_start;
    UNS32 parameter_end_add;
    UNS32 *ram_PTR;

    /* The function parameter start address value must be a multiple of 8 */
    /* The value has to be multiply by to get the absolute parameter address seen at host side */
    /* -> Check the parameter is a multiple of 8. */
    /* If not, increment the address to have the next multiple of 8 */
    parameter_start = a_parameter_start_addr;
    if ((a_parameter_start_addr % 8u) != 0u)
    {
        parameter_start = a_parameter_start_addr + (UNS32)(8u -(a_parameter_start_addr % 8u));
    }
    else
    {        
    }

    /*   - CIE  = a_interrupt_mode                                                  */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_QOM_LTS_FCT_NB                                               */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start         / 8                                       */
    ETPU.CHAN[a_channel].CR.R =    (UNS32)(a_interrupt_mode    << ETPU_SCR_CIE_OFFSET)  +
                                   (UNS32)(a_channel_priority  << ETPU_SCR_CPR_OFFSET)  +
                                   (UNS32)(STANDARD_TABLE      << ETPU_SCR_ETCS_OFFSET) +
                                   (UNS32)(ETPU_QOM_LTS_FCT_NB << ETPU_SCR_CFS_OFFSET)  +
                                   (UNS32)(parameter_start     >> (UNS32)ETPU_SCR_CPBA_OFFSET);
    
    /* Initialise RAM function area to 0: */
    /*  - Get the end of parameter area address: parameter start + last parameter offset  + last parameter size */
    parameter_end_add = (UNS32)(parameter_start
                               + (UNS32)_FRAME_SIZE_eTPU_QOM_ 
                               + (UNS32)((a_number_event - 1u) * ETPU_QOM_EVENT_PARAMETER_SIZE));
    /*  - Set data RAM to 0 */
    ram_PTR = (UNS32 *) (parameter_start + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
       *ram_PTR = 0x0;
       ram_PTR ++;
    }
    
    /* Initialise function parameters */
    /*  - QOM qom_option: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_QOM_OPTION_OFFSET );
    *ram_PTR |= ETPU_QOM_OPTION_MASK & (UNS32)(a_time_base << ETPU_QOM_OPTION_SHIFT);

    /*  - QOM PTR_event_table_end : There is one event used */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_QOM_EVENT_TABLE_END_OFFSET );
    *ram_PTR |= ETPU_QOM_EVENT_TABLE_END_MASK & ((parameter_end_add - ETPU_QOM_EVENT_PARAMETER_SIZE) << ETPU_QOM_EVENT_TABLE_END_SHIFT);

    /*  - QOM nb_loop: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_QOM_NB_LOOP_OFFSET );
    *ram_PTR |= ETPU_QOM_NB_LOOP_MASK & (UNS32)(a_nb_loop << ETPU_QOM_NB_LOOP_SHIFT);

    /*  - QOM PTR_T_reference : Referenced mode not used */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_QOM_PTR_REFERENCE_OFFSET );
    *ram_PTR |= ETPU_QOM_PTR_REFERENCE_MASK & (a_master_time_reference << ETPU_QOM_PTR_REFERENCE_SHIFT);
    
    /*  - QOM table_event: (Default done by initialization of the parameters) */
    
    /* Set SCR channel register to configure the QOM as single shot */
    ETPU.CHAN[a_channel].SCR.R = a_QOM_mode;
    
    return parameter_end_add;
}    


/***************************************************************/
/* Global function : EtpuUpdateQOMStepperMotorEnable           */
/***************************************************************/
void EtpuUpdateQOMStepperMotorEnable(UNS8 a_channel, REAL32 a_command, UNS32 a_period)
{    
    UNS32 *parameter_event_table_PTR;
    UNS32 high_state_delay;
    UNS8 next_pin_state;

    if (a_command > (REAL32)99.9)
    {
        high_state_delay = (a_period * (ETPU_SYSTEM_CLOCK_TCR1 / 100000u) * (UNS32)(a_command)) >> 2;
        next_pin_state = ETPU_PIN_HIGH;
    }
    else
    {
        high_state_delay = (a_period * (ETPU_SYSTEM_CLOCK_TCR1 / 100000u) * (UNS32)(a_command));
        next_pin_state = ETPU_PIN_LOW;
    }

    /* Get parameter RAM for the Event Table of the channel to command the enable signal */
    parameter_event_table_PTR = (UNS32 *)(ETPU_DATA_RAM_START_ABS + (UNS32)(ETPU.CHAN[a_channel].CR.B.CPBA << (UNS32)ETPU_SCR_CPBA_OFFSET) + ETPU_QOM_FIRST_TABLE_EVENT_OFFSET);

    /* Write event table to configure the counter offset and the action of the event */
    /*  - QOM first_table_event : delay = period/command ms ; next pin state */
    *parameter_event_table_PTR = ETPU_QOM_EVENT_TABLE_MASK & 
                               (((UNS32)(next_pin_state << 24) + high_state_delay) << ETPU_QOM_EVENT_TABLE_SHIFT);                   
}

/***************************************************************/
/* Global function : EtpuUpdateAndStartQOMDCMotor              */
/***************************************************************/
void EtpuUpdateAndStartQOMDCMotor(UNS8 a_channel, REAL32 a_command, UNS32 a_period)
{
    UNS32 *parameter_event_table_PTR;
    UNS32 high_state_delay;
    UNS8 start_mode, next_pin_state;
    
    if (a_command < (REAL32)0.1)
    {
        high_state_delay = (a_period * (ETPU_SYSTEM_CLOCK_TCR1 / 100000u) * (UNS32)(a_command)) >> 2;
        start_mode = HSR_QOM_INIT_LOW_IMMEDIATE;
        next_pin_state = ETPU_PIN_LOW;
    }
    else if (a_command > (REAL32)99.9)
    {
        high_state_delay = (a_period * (ETPU_SYSTEM_CLOCK_TCR1 / 100000u) * (UNS32)(a_command)) >> 2;
        start_mode = HSR_QOM_INIT_HIGH_IMMEDIATE;
        next_pin_state = ETPU_PIN_HIGH;
    }
    else
    {
        high_state_delay = (a_period * (ETPU_SYSTEM_CLOCK_TCR1 / 100000u) * (UNS32)(a_command));
        start_mode = HSR_QOM_INIT_HIGH_IMMEDIATE;
        next_pin_state = ETPU_PIN_LOW;
    }

    /* Get parameter RAM for the Event Table of the channel to command the enable signal */
    parameter_event_table_PTR = (UNS32 *)(ETPU_DATA_RAM_START_ABS + (UNS32)(ETPU.CHAN[a_channel].CR.B.CPBA << (UNS32)ETPU_SCR_CPBA_OFFSET) + ETPU_QOM_FIRST_TABLE_EVENT_OFFSET);

    /* Write event table to configure the counter offset and the action of the event */
    /*  - QOM first_table_event : delay = period/command ms ; next pin state */
    *parameter_event_table_PTR = ETPU_QOM_EVENT_TABLE_MASK & 
                               (((UNS32)(next_pin_state << 24) + high_state_delay) << ETPU_QOM_EVENT_TABLE_SHIFT);        
                               
    SetHSRR(a_channel,start_mode);            
}

/***************************************************************/
/* Global function : EtpuInitializeQOMDCMotors                 */
/***************************************************************/
void EtpuInitializeQOMDCMotors(void)
{
    UNS32 parameter_start;

    /* Clear channel priority to disable channels */
    ETPU.CHAN[HEN1_DCM_1_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_1_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_2_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_2_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_3_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_3_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_4_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_4_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
	ETPU.CHAN[HEN1_DCM_5_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
	ETPU.CHAN[HEN2_DCM_5_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
	ETPU.CHAN[HEN1_DCM_6_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_6_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_7_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_7_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_8_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_8_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_9_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_9_CHANNEL].CR.B.CPR  = (VUNS32)ETPU_DISABLED;
	
	ETPU.CHAN[HEN1_DCM_10_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_10_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_11_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_11_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_12_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_12_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_13_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_13_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
	ETPU.CHAN[HEN1_DCM_14_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
	ETPU.CHAN[HEN2_DCM_14_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
	ETPU.CHAN[HEN1_DCM_15_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN2_DCM_15_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[HEN1_DCM_16_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;

    /* parameter_start_add is a relative address */
    parameter_start = data_free_ram;

    /* 1/ High Enables 1 of DC Motor 1 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_1_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 1 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_1_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   
    
    /* 2/ High Enables 1 of DC Motor 2 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_2_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 2 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_2_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 3/ High Enables 1 of DC Motor 3 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_3_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 3 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_3_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 4/ High Enables 1 of DC Motor 4 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_4_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 4 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_4_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);


    /* 5/ High Enables 1 of DC Motor 5 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_5_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 5 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_5_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 6/ High Enables 1 of DC Motor 6 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_6_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 6 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_6_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
    
    /* 7/ High Enables 1 of DC Motor 7 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_7_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 7 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_7_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 8/ High Enables 1 of DC Motor 8 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_8_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 8 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_8_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 9/ High Enables 1 of DC Motor 9 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_9_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 9 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_9_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 10/ High Enables 1 of DC Motor 10 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_10_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 10 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_10_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 11/ High Enables 1 of DC Motor 11 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_11_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 11 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_11_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 12/ High Enables 1 of DC Motor 12 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_12_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 12 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_12_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 13/ High Enables 1 of DC Motor 13 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_13_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 13 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_13_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 14/ High Enables 1 of DC Motor 14 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_14_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 14 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_14_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 15/ High Enables 1 of DC Motor 15 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_15_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 15 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_15_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);

    /* 16/ High Enables 1 of DC Motor 16 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN1_DCM_16_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
   /* High Enables 2 of DC Motor 16 channel configuration */
    parameter_start = EtpuInitializeQOM(HEN2_DCM_16_CHANNEL,
                                        parameter_start,
                                        ETPU_QOM_SINGLE_SHOT,
                                        ETPU_DISABLE_CHAN_INTERRUPT,
                                        ETPU_PRIORITY_MIDDLE,
                                        ETPU_QOM_USE_TCR1,
                                        1,
                                        0,
                                        0);
    
    /* Set the data free ram address for the next eTPU channel configuration (shall be aligned to a 64 bit address) to the next free ram address */
    data_free_ram = parameter_start;
    if (((data_free_ram) % 8u) != 0u)
    {
        data_free_ram = data_free_ram + (UNS32)(8u - (data_free_ram % 8u));
    }
    else
    {
    }
}


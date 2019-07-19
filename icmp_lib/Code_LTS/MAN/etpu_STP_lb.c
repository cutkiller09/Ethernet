/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "cpu_def.h"
#include "./eTPU_Lib/eTPU_auto.h"
#include "stp_motor.h"
#include "hard_def.h"
#include "etpu_lb.h"

#include "etpu_STP_lb.h"



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
/* eTPU STP2 function */
#define ETPU_SCR_INIT                  (UNS32)0x00000000
#define ETPU_MASTER_LTS_STP2_NB                    (UNS8) _FUNCTION_NUM_eTPU_StepperMotor2PH_


/* STP2 Master function OFFSET for uns32 pointer */
#define ETPU_M_CHAN1_OFFSET               (UNS32) 0x00
#define ETPU_M_CHAN1_MASK                 (UNS32) 0xFF000000
#define ETPU_M_CHAN1_SHIFT                (UNS32) 24

#define ETPU_M_STEP_CONT_OFFSET           (UNS32) 0x00
#define ETPU_M_STEP_CONT_MASK             (UNS32) 0x00FFFFFF
#define ETPU_M_STEP_CONT_SHIFT            (UNS32) 0

#define ETPU_M_CHAN2_OFFSET               (UNS32) 0x04
#define ETPU_M_CHAN2_MASK                 (UNS32) 0xFF000000
#define ETPU_M_CHAN2_SHIFT                (UNS32) 24

#define ETPU_M_SPEED_OFFSET               (UNS32) 0x04
#define ETPU_M_SPEED_MASK                 (UNS32) 0x00FFFFFF
#define ETPU_M_SPEED_SHIFT                (UNS32) 0

#define ETPU_M_DIRECTION_OFFSET           (UNS32) 0x08
#define ETPU_M_DIRECTION_MASK             (UNS32) 0xFF000000
#define ETPU_M_DIRECTION_SHIFT            (UNS32) 24

#define ETPU_M_TCR_OFFSET                 (UNS32) 0x0C
#define ETPU_M_TCR_MASK                   (UNS32) 0xFF000000
#define ETPU_M_TCR_SHIFT                  (UNS32) 24


/* eTPU SPWM function */
#define ETPU_SPWM_SCR_INIT                  (UNS32)0x00000000
#define ETPU_SPWM_MASTER_LTS_FCT_NB                    (UNS8) _FUNCTION_NUM_eTPU_SPWM_Master_
#define ETPU_SPWM_SLAVE_LTS_FCT_NB                    (UNS8) _FUNCTION_NUM_eTPU_SPWM_Slave_
/* SPWM Master function OFFSET for uns32 pointer */
#define ETPU_SPWM_M_LINK1_OFFSET                   (UNS32) 0x00
#define ETPU_SPWM_M_LINK1_MASK                     (UNS32) 0xFFFFFFFF
#define ETPU_SPWM_M_LINK1_SHIFT                    (UNS32) 0

#define ETPU_SPWM_M_TIME_BASE_OFFSET               (UNS32) 0x04
#define ETPU_SPWM_M_TIME_BASE_MASK                 (UNS32) 0xFF000000
#define ETPU_SPWM_M_TIME_BASE_SHIFT                (UNS32) 24

#define ETPU_SPWM_M_PERIOD_OFFSET                  (UNS32) 0x04
#define ETPU_SPWM_M_PERIOD_MASK                    (UNS32) 0x00FFFFFF
#define ETPU_SPWM_M_PERIOD_SHIFT                   (UNS32) 0

#define ETPU_SPWM_M_LINK2_OFFSET                   (UNS32) 0x08
#define ETPU_SPWM_M_LINK2_MASK                     (UNS32) 0xFFFFFFFF
#define ETPU_SPWM_M_LINK2_SHIFT                    (UNS32) 0

#define ETPU_SPWM_M_PULSE_ON_OFFSET                (UNS32) 0x0C
#define ETPU_SPWM_M_PULSE_ON_MASK                  (UNS32) 0x00FFFFFF
#define ETPU_SPWM_M_PULSE_ON_SHIFT                 (UNS32) 0

#define ETPU_SPWM_M_REFERENCE_OFFSET               (UNS32) 0x10

/* SPWM Slave function OFFSET for uns32 pointer */
#define ETPU_SPWM_S_PERIOD_OFFSET                  (UNS32) 0x00
#define ETPU_SPWM_S_PERIOD_MASK                    (UNS32) 0x00FFFFFF
#define ETPU_SPWM_S_PERIOD_SHIFT                   (UNS32) 0

#define ETPU_SPWM_S_TIME_BASE_OFFSET               (UNS32) 0x04
#define ETPU_SPWM_S_TIME_BASE_MASK                 (UNS32) 0xFF000000
#define ETPU_SPWM_S_TIME_BASE_SHIFT                (UNS32) 24

#define ETPU_SPWM_S_PULSE_ON_OFFSET                (UNS32) 0x04
#define ETPU_SPWM_S_PULSE_ON_MASK                  (UNS32) 0x00FFFFFF
#define ETPU_SPWM_S_PULSE_ON_SHIFT                 (UNS32) 0

#define ETPU_SPWM_S_DELAY_OFFSET                   (UNS32) 0x08
#define ETPU_SPWM_S_DELAY_MASK                     (UNS32) 0x00FFFFFF
#define ETPU_SPWM_S_DELAY_SHIFT                    (UNS32) 0

#define ETPU_SPWM_M_REFERENCE_PTR_OFFSET           (UNS32) 0x0C
#define ETPU_SPWM_M_REFERENCE_PTR_MASK             (UNS32) 0x00FFFFFF
#define ETPU_SPWM_M_REFERENCE_PTR_SHIFT            (UNS32) 0

/* Configurations */
#define ETPU_SPWM_USE_TCR1       (UNS8) 0

/* 10 KHz */
#define ETPU_PWM_CLK_FREQ                    (UNS32)(ETPU_SYSTEM_CLOCK_TCR1/(UNS32)10000) 
#define ETPU_PWM_CLK_PULSE_ON_TIME           (UNS32)((ETPU_PWM_CLK_FREQ * (UNS32)98) / (UNS32)100)
#define DELAY_PWM_CLK_CMD1_CMD2              (UNS32)((UNS32)50 * (ETPU_SYSTEM_CLOCK_TCR1/(UNS32)1000000))
#define DELAY_PWM_CLK_GRP1_GRP2              (UNS32)((UNS32)25 * (ETPU_SYSTEM_CLOCK_TCR1/(UNS32)1000000))
#define DELAY_PWM_CLK_CMD1_CMD2_GRP2_GRP1    (UNS32)((UNS32)75 * (ETPU_SYSTEM_CLOCK_TCR1/(UNS32)1000000))

/* Offset added to the step counting value to avoid underflow */
#define STP2_COUNT_OFFSET (UNS32)5000

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
/*                                                             */
/*                         LOCAL FUNCTIONS                     */
/*                                                             */
/***************************************************************/
/***************************************************************/
/* Local function : EtpuInitializeMasterSPWM                  */
/***************************************************************/
UNS32 EtpuInitializeMasterSPWM(UNS8  a_channel,
                               UNS32 a_parameter_start_addr,
                               UNS32 *a_master_time_reference,
                               UNS8  a_channel_priority,
                               UNS8  a_time_base,
                               UNS32 a_frequency,
                               UNS32 a_duty_cycle,
                               UNS32 a_channel_link_1,
                               UNS32 a_channel_link_2)
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
        
        
    /*   - CIE  = 0                            Interrupt disabled                   */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = a_channel_priority           Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_SPWM_MASTER_LTS_FCT_NB                                       */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start / 8                                               */
    ETPU.CHAN[a_channel].CR.R =    (UNS32)(ETPU_DISABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET)  +
                                   (UNS32)(a_channel_priority          << ETPU_SCR_CPR_OFFSET)  +
                                   (UNS32)(STANDARD_TABLE              << ETPU_SCR_ETCS_OFFSET) +
                                   (UNS32)(ETPU_SPWM_MASTER_LTS_FCT_NB << ETPU_SCR_CFS_OFFSET)  +
                                   (UNS32)(parameter_start             >> (UNS32)ETPU_SCR_CPBA_OFFSET);
    
    /* Initialise RAM function area to 0 */
    /*  - Get the offset of the end of parameter area address */
    parameter_end_add = parameter_start + (UNS32)_FRAME_SIZE_eTPU_SPWM_Master_;
    /*  - Set data RAM to 0 */
    ram_PTR = (UNS32 *) (parameter_start + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
       *ram_PTR = 0x0;
       ram_PTR ++;
    }
    
    /* Initialise function parameters */
    /* - Time base: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_M_TIME_BASE_OFFSET);
    *ram_PTR |= ETPU_SPWM_M_TIME_BASE_MASK & (UNS32)(a_time_base << ETPU_SPWM_M_TIME_BASE_SHIFT);
    
    /* - SPWM period: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_M_PERIOD_OFFSET);
    *ram_PTR |= ETPU_SPWM_M_PERIOD_MASK & (UNS32)(a_frequency << ETPU_SPWM_M_PERIOD_SHIFT);

    /* - SPWM Pulse On Time (Duty cycle): */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_M_PULSE_ON_OFFSET);
    *ram_PTR |= ETPU_SPWM_M_PULSE_ON_MASK & (UNS32)(a_duty_cycle << ETPU_SPWM_M_PULSE_ON_SHIFT);

    /* - Link the Channel to the channel a_channel_link_1 and a_channel_link_2 */
    /*! Warning: The default eTPU channel used, SHALL NOT be used or configured by an other driver */
    /*! Warning: The two MSB bits of each byte of the link value define the eTPU to used */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_M_LINK1_OFFSET);
    *ram_PTR = ETPU_SPWM_M_LINK1_MASK & (UNS32)(a_channel_link_1 << ETPU_SPWM_M_LINK1_SHIFT);
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_M_LINK2_OFFSET);
    *ram_PTR = ETPU_SPWM_M_LINK2_MASK & (UNS32)(a_channel_link_2 << ETPU_SPWM_M_LINK2_SHIFT);
    
    /* Write the HSR register to initialize the channel */
    ETPU.CHAN[a_channel].HSRR.R = (UNS32)HSR_ETPU_SPWM_INIT;
        
    /* Get address of the channel to configure the slave channels */
    *a_master_time_reference = parameter_start + (UNS32)ETPU_SPWM_M_REFERENCE_OFFSET;
    
    /* return start address for the next channel */
    return parameter_end_add;
}

/***************************************************************/
/* Local function : EtpuInitializeSlaveSPWM                   */
/***************************************************************/
UNS32 EtpuInitializeSlaveSPWM(UNS8  a_channel,
                               UNS32 a_parameter_start_addr,
                               UNS32 a_master_time_reference,
                               UNS8  a_channel_priority,
                               UNS8  a_time_base,
                               UNS32 a_frequency,
                               UNS32 a_duty_cycle,
                               UNS32 a_delay)
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
        
        
    /*   - CIE  = 0                            Interrupt disabled                   */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_SPWM_SLAVE_LTS_FCT_NB                                        */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start / 8                                               */
    ETPU.CHAN[a_channel].CR.R = (UNS32)(ETPU_DISABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                                (UNS32)(a_channel_priority          << ETPU_SCR_CPR_OFFSET) +
                                (UNS32)(STANDARD_TABLE              << ETPU_SCR_ETCS_OFFSET) +
                                (UNS32)(ETPU_SPWM_SLAVE_LTS_FCT_NB  << ETPU_SCR_CFS_OFFSET) +
                                (UNS32)(parameter_start             >> (UNS32)ETPU_SCR_CPBA_OFFSET);
   
    /* Initialise RAM function area to 0 */
    /* - Get the end of parameter area address */
    parameter_end_add = parameter_start + (UNS32)_FRAME_SIZE_eTPU_SPWM_Slave_;
    /* - Set data RAM to 0 */
    ram_PTR = (UNS32 *) (parameter_start + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
       *ram_PTR = 0x0;
       ram_PTR ++;
    }
    
    /* Initialise function parameters */
    /* - Time base: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_S_TIME_BASE_OFFSET);
    *ram_PTR |= ETPU_SPWM_S_TIME_BASE_MASK & (UNS32)(a_time_base << ETPU_SPWM_S_TIME_BASE_SHIFT);
    
    /* - SPWM period: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_S_PERIOD_OFFSET);
    *ram_PTR |= ETPU_SPWM_S_PERIOD_MASK & (UNS32)(a_frequency << ETPU_SPWM_S_PERIOD_SHIFT);

    /* - SPWM Active Time (Duty cycle): */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_S_PULSE_ON_OFFSET);
    *ram_PTR |= ETPU_SPWM_S_PULSE_ON_MASK & (UNS32)(a_duty_cycle << ETPU_SPWM_S_PULSE_ON_SHIFT);
  
     /* - SPWM Delay: */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_S_DELAY_OFFSET);
    *ram_PTR |= ETPU_SPWM_S_DELAY_MASK & (UNS32)(a_delay << ETPU_SPWM_S_DELAY_SHIFT);  
    
    /* - SPWM Master reference */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_SPWM_M_REFERENCE_PTR_OFFSET);
    *ram_PTR |= ETPU_SPWM_M_REFERENCE_PTR_MASK & (UNS32)(a_master_time_reference << ETPU_SPWM_M_REFERENCE_PTR_SHIFT);
    
    /* Write the HSR register to initialize the channel */
    ETPU.CHAN[a_channel].HSRR.R = (UNS32)HSR_ETPU_SPWM_INIT;
    
    /* return start address for the next channel */
    return parameter_end_add;
}

/***************************************************************/
/*                                                             */
/*                         GLOBAL FUNCTIONS                    */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Global function : EtpuInitializeMasterSPWM                  */
/***************************************************************/
void EtpuInitializeStepperMotor()
{
    UNS32 parameter_start;
    UNS32 parameter_end_add;
    UNS32 master_time_reference;
    UNS32 *ram_PTR;

    /* The function parameter start address value must be a multiple of 8 */
    /* The value has to be multiply by to get the absolute parameter address seen at host side */
    /* -> Check the parameter is a multiple of 8. */
    /* If not, increment the address to have the next multiple of 8 */
    parameter_start = data_free_ram;
    if ((data_free_ram % 8u) != 0u)
    {
        parameter_start = data_free_ram + (UNS32)(8u -(data_free_ram % 8u));
    }
    else
    {        
    }

    /*!******************************************************************************/
    /*!                                                                             */
    /*! Configure the Clock signal of the Stepper Motor function                    */
    /*!                                                                             */
    /*!******************************************************************************/
    
    /* 1/ CLK_2PH_1 channel configuration */
    data_free_ram = EtpuInitializeMasterSPWM(CLK_2PH_1_CHANNEL,
                                   parameter_start,
                                   &master_time_reference,
                                   ETPU_PRIORITY_MIDDLE,
                                   ETPU_SPWM_USE_TCR1,
                                   /* - SPWM period: frequency 10kHz */
                                   ETPU_PWM_CLK_FREQ,
                                   /* - SPWM Active Time: Duty cycle = 9800/100 = 98% */
                                   ETPU_PWM_CLK_PULSE_ON_TIME,

    /* - Link the Channel to the channel of signals CLK_2PH_2 (eTPU_B CHANNEL_12),    */
    /*     Other link are mapped to un unsued eTPU channel (eTPU_B CHANNEL_0)                     */
    /*! Warning: the default eTPU channel used, SHALL NOT be used or configured by an other driver */
                                   (UNS32)(((ETPU_B_LINK_ID|CHANNEL_12) << 24) | 
                                    ((ETPU_B_LINK_ID|CHANNEL_0) << 16) |
									((ETPU_B_LINK_ID|CHANNEL_0) << 8)  |
                                     (ETPU_B_LINK_ID|CHANNEL_0)), 
                                    (((ETPU_B_LINK_ID|CHANNEL_0) << 24) | 
                                    ((ETPU_B_LINK_ID|CHANNEL_0) << 16) |
                                    ((ETPU_B_LINK_ID|CHANNEL_0) << 8)  |									
                                     (ETPU_B_LINK_ID|CHANNEL_0)));
    
    /* The function parameter start address value must be a multiple of 8 */
    /* The value has to be multiply by to get the absolute parameter address seen at host side */
    /* -> Check the parameter is a multiple of 8. */
    /* If not, increment the address to have the next multiple of 8 */
    parameter_start = data_free_ram;
       if ((data_free_ram % 8u) != 0u)
       {
           parameter_start = data_free_ram + (UNS32)(8u -(data_free_ram % 8u));
       }
       else
       {
       }
   
    /* 2/ CLK_2PH_2 channel configuration */
       data_free_ram = EtpuInitializeSlaveSPWM(CLK_2PH_2_CHANNEL,
                              parameter_start,
                              master_time_reference,
                              ETPU_PRIORITY_MIDDLE,
                              ETPU_SPWM_USE_TCR1,
                              /* - SPWM period: frequency 10kHz */
                              ETPU_PWM_CLK_FREQ,
                              /* - SPWM Active Time: Duty cycle = 9800/100 = 98% */
                              ETPU_PWM_CLK_PULSE_ON_TIME,
                              /* - SPWM Delay: 50 us */
                              DELAY_PWM_CLK_CMD1_CMD2);    


    /*!******************************************************************************/
    /*!                                                                             */
    /*! Configure the Command signals of the Stepper Motor function                 */
    /*!                                                                             */
    /*!******************************************************************************/
       /* The function parameter start address value must be a multiple of 8 */
       /* The value has to be multiply by to get the absolute parameter address seen at host side */
       /* -> Check the parameter is a multiple of 8. */
       /* If not, increment the address to have the next multiple of 8 */
       parameter_start = data_free_ram;
          if ((data_free_ram % 8u) != 0u)
          {
              parameter_start = data_free_ram + (UNS32)(8u -(data_free_ram % 8u));
          }
          else
          {
          }

    /*   - CIE  = 0                            Interrupt disabled                   */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = middle                       Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_MASTER_LTS_STP2_NB                                       */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start / 8                                               */
    ETPU.CHAN[CMD_2PH_1_CHANNEL].CR.R =    (UNS32)(ETPU_DISABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET)  +
                                   (UNS32)(ETPU_PRIORITY_MIDDLE          << ETPU_SCR_CPR_OFFSET)  +
                                   (UNS32)(ALTERNATE_TABLE             << ETPU_SCR_ETCS_OFFSET) +
                                   (UNS32)(ETPU_MASTER_LTS_STP2_NB << ETPU_SCR_CFS_OFFSET)  +
                                   (UNS32)(parameter_start             >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    ETPU.CHAN[CMD_2PH_2_CHANNEL].CR.R =    (UNS32)(ETPU_DISABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET)  +
                                       (UNS32)(ETPU_PRIORITY_MIDDLE          << ETPU_SCR_CPR_OFFSET)  +
                                       (UNS32)(ALTERNATE_TABLE             << ETPU_SCR_ETCS_OFFSET) +
                                       (UNS32)(ETPU_MASTER_LTS_STP2_NB << ETPU_SCR_CFS_OFFSET)  +
                                       (UNS32)(parameter_start             >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    /* Initialize RAM function area to 0 */
    /*  - Get the offset of the end of parameter area address */
    parameter_end_add = parameter_start + (UNS32)_FRAME_SIZE_eTPU_StepperMotor2PH_;
    /*  - Set data RAM to 0 */
    ram_PTR = (UNS32 *) (parameter_start + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
       *ram_PTR = 0x0;
       ram_PTR ++;
    }
     
    /* Initialize function parameters */
    /* - Channel 1 : */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_M_CHAN1_OFFSET);
    *ram_PTR |= ETPU_M_CHAN1_MASK & (UNS32)(CMD_2PH_1_CHANNEL << ETPU_M_CHAN1_SHIFT);

    /* - Channel 2 : */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_M_CHAN2_OFFSET);
    *ram_PTR |= ETPU_M_CHAN2_MASK & (UNS32)(CMD_2PH_2_CHANNEL << ETPU_M_CHAN2_SHIFT);

    /* - TRC definition : */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_M_TCR_OFFSET);
    *ram_PTR |= ETPU_M_TCR_MASK & (UNS32)(ETPU_USE_TCR2 << ETPU_M_TCR_SHIFT);

    /* Write the HSR register to initialize the channel */
    ETPU.CHAN[CMD_2PH_1_CHANNEL].HSRR.R = (UNS32)HSR_ETPU_STP2_INIT;
    
    /*!******************************************************************************/
    /*!                                                                             */
    /*! Start Clock signals of the Stepper Motor function                           */
    /*!                                                                             */
    /*!******************************************************************************/
    
    /* 5/ CLK_2PH_1 channel start */
    /* Write the ETPU channel CLK_2PH_1 HSR register to start the clock of the Stepper 2PH */
    ETPU.CHAN[CLK_2PH_1_CHANNEL].HSRR.R = (UNS32)HSR_ETPU_SPWM_START;

    /* Set the data free ram address for the next eTPU channel configuration (shall be aligned to a 64 bit address) to the next free ram address */
    data_free_ram = parameter_end_add;
}


/***************************************************************/
/* Global function : EtpuUpdateStepperMotorCommand             */
/***************************************************************/
void EtpuUpdateStepperMotorCommand(UNS8 a_channel, UNS16 a_frequency, UNS8 positive_cmd)
{
    UNS32 *ram_PTR;
    UNS32 cmd;

    /* Determine the command to apply */
    cmd = (UNS32)(ETPU_SYSTEM_CLOCK_TCR2 / a_frequency);

    /* Get pointer to the command parameter */
    ram_PTR = (UNS32*)((UNS8*)ETPU_DATA_RAM_START_ABS + (ETPU.CHAN[a_channel].CR.B.CPBA << 3) + ETPU_M_SPEED_OFFSET);
    /* Write new cmd to data memory of the master channel */
    *ram_PTR &= ~ETPU_M_SPEED_MASK;
    *ram_PTR |=ETPU_M_SPEED_MASK & (UNS32)(cmd << ETPU_M_SPEED_SHIFT);

    /* Get pointer to the direction parameter */
    ram_PTR = (UNS32*)((UNS8*)ETPU_DATA_RAM_START_ABS + (ETPU.CHAN[a_channel].CR.B.CPBA << 3) + ETPU_M_DIRECTION_OFFSET);
    /* Write new direction to data memory of the master channel */
    *ram_PTR &= ~ETPU_M_DIRECTION_MASK;
    *ram_PTR |=ETPU_M_DIRECTION_MASK & (UNS32)(positive_cmd << ETPU_M_DIRECTION_SHIFT);
}

/***************************************************************/
/* Global function : EtpuStopStepperMotorCommand               */
/***************************************************************/
void EtpuStopStepperMotorCommand(UNS8 a_channel)
{
    /* Write the HSR register to stop the channel */
    ETPU.CHAN[a_channel].HSRR.R = (UNS32)HSR_ETPU_STP2_STOP;
}

/***************************************************************/
/* Global function : EtpuStartStepperMotorCommand              */
/***************************************************************/
void EtpuStartStepperMotorCommand(UNS8 a_channel)
{
    /* Write the HSR register to stop the channel */
    ETPU.CHAN[a_channel].HSRR.R = (UNS32)HSR_ETPU_STP2_START;
}

/***************************************************************/
/* Global function : EtpuGetStepperMotorPosition               */
/***************************************************************/
UNS32 EtpuGetStepperMotorPosition(UNS8 a_channel)
{
   UNS32 *ram_PTR;
   UNS32 Actual_Pos_Cnt;

   /* Get pointer to the step count parameter */
   ram_PTR = (UNS32*)((UNS8*)ETPU_DATA_RAM_START_ABS + (ETPU.CHAN[a_channel].CR.B.CPBA << 3) + ETPU_M_STEP_CONT_OFFSET);
   /* Read step count from data memory of the master channel */
   Actual_Pos_Cnt = ((*ram_PTR) & ETPU_M_STEP_CONT_MASK) - STP2_COUNT_OFFSET;
   return Actual_Pos_Cnt;
}

/***************************************************************/
/* Global function : EtpuGetStepperMotorPosition               */
/***************************************************************/
void EtpuSetStepperMotorPosition(UNS32 a_position, UNS8 a_channel)
{
   UNS32 *ram_PTR;

   /* Get pointer to the step count parameter */
   ram_PTR = (UNS32*)((UNS8*)ETPU_DATA_RAM_START_ABS + (ETPU.CHAN[a_channel].CR.B.CPBA << 3) + ETPU_M_STEP_CONT_OFFSET);
   /* Write new step count to data memory of the master channel */
   *ram_PTR &= ~ETPU_M_STEP_CONT_MASK;
   *ram_PTR |=ETPU_M_STEP_CONT_MASK & (UNS32)((a_position + STP2_COUNT_OFFSET) << ETPU_M_STEP_CONT_SHIFT);
}

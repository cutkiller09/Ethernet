/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"
#include "cpu_def.h"
#include "ad1255.h"
#include "./eTPU_Lib/eTPU_auto.h"

#include "interface.h"
#include "hard_def.h"
#include "etpu_lb.h"
#include "etpu_TIMER_lb.h"


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
/* LTS eTPU TIMER function */
#define ETPU_TIMER_LTS_FCT_NB                 (UNS8)_FUNCTION_NUM_eTPU_TIMER_
/* OFFSET for uns32 pointer */
#define ETPU_TIMER_OPTION_OFFSET          (UNS32) 0x00
#define ETPU_TIMER_OPTION_MASK            (UNS32) 0xFF000000
#define ETPU_TIMER_OPTION_SHIFT           (UNS32) 24

#define ETPU_TIMER_DELAY_OFFSET            (UNS32) 0x04
#define ETPU_TIMER_DELAY_MASK              (UNS32) 0x00FFFFFF
#define ETPU_TIMER_DELAY_SHIFT             (UNS32) 0

/* Function Option Bit Definitions */
#define ETPU_TIMER_USE_TCR1       (UNS8)0
#define ETPU_TIMER_SET_INTERRUPT  (UNS8)2
/* Function Mode Bit Definitions - mode options */
#define ETPU_TIMER_SINGLE_SHOT    (UNS32)0
/* Configurations */
#define DELAY_TIMER_AD1255_3MS               (UNS32)(ETPU_SYSTEM_CLOCK_TCR1 * 3u / 1000u)
#define DELAY_TIMER_ARINC_9MS                (UNS32)(ETPU_SYSTEM_CLOCK_TCR1 * 9u / 1000u)

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
/*                                                             */
/*                         GLOBAL FUNCTIONS                    */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Global function : EtpuInitializeTimerAD1255                 */
/***************************************************************/
void EtpuInitializeTimerAD1255(void)
{
    UNS32 parameter_start;
    UNS32 parameter_end_add;
    UNS32 *ram_PTR;

    /* Clear channel priority to disable channels */
    ETPU.CHAN[AD1255_TIMER_ETPU_CHANNEL].CR.B.CPR = (VUNS32)ETPU_DISABLED;

    /* Get the data_free_ram address to set the parameter start address value */
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

    /* 1/ AD1255_TIMER_ETPU_CHANNEL channel configuration */
    /*   - CIE  = 0                            Interrupt disabled                   */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_TIMER_LTS_FCT_NB                                             */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start         / 8                                       */
    ETPU.CHAN[AD1255_TIMER_ETPU_CHANNEL].CR.R =    (UNS32)(ETPU_DISABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                                        (UNS32)(ETPU_PRIORITY_MIDDLE << ETPU_SCR_CPR_OFFSET) +
                                        (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                                        (UNS32)(ETPU_TIMER_LTS_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                                        (UNS32)(parameter_start >> (UNS32)ETPU_SCR_CPBA_OFFSET);
    
    /* Initialise RAM function area to 0: */
    /*  - Get the end of parameter area address: parameter start + _FRAME_SIZE_eTPU_TIMER_ */
    parameter_end_add = parameter_start  +(UNS32)_FRAME_SIZE_eTPU_TIMER_;
    /*  - Set data RAM to 0 */
    ram_PTR = (UNS32 *) (parameter_start + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
       *ram_PTR = 0x0;
       ram_PTR ++;
    }
    
    /* Initialise function parameters */
    /*  - QOM Timer_option : use of TCR1 counter */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_TIMER_OPTION_OFFSET );
    *ram_PTR |= ETPU_TIMER_OPTION_MASK & (UNS32)((ETPU_TIMER_USE_TCR1 | ETPU_TIMER_SET_INTERRUPT) << ETPU_TIMER_OPTION_SHIFT);

    /*  - QOM Time_delay : 3 ms */
    ram_PTR = (UNS32 *)(parameter_start + ETPU_DATA_RAM_START_ABS + ETPU_TIMER_DELAY_OFFSET );
    *ram_PTR |= (UNS32)(ETPU_TIMER_DELAY_MASK & (UNS32)(DELAY_TIMER_AD1255_3MS << ETPU_TIMER_DELAY_SHIFT));

    /* Set SCR channel register to configure the TIMER as single shot */
    ETPU.CHAN[AD1255_TIMER_ETPU_CHANNEL].SCR.R = ETPU_TIMER_SINGLE_SHOT;  
    
    /* Set the data free ram address for the next eTPU channel configuration (shall be aligned to a 64 bit address) to the next free ram address */
    data_free_ram = parameter_end_add;
    if ((data_free_ram % 8u) != 0u)
    {
        data_free_ram = data_free_ram + (UNS32)(8u -(data_free_ram % 8u));
    }
    else
    {
    }
}


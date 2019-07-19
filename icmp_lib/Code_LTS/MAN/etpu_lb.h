#ifndef __ETPU_LB_H__
#define __ETPU_LB_H__
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
    UNS8 channel;
    UNS8 priority;
    UNS32 parameter_start_add ;
} 
T_Etpu_fnc;

/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* eTPU clock */
#define ETPU_SYSTEM_CLOCK_TCR1    (UNS32)(SYSTEM_CLOCK/2u)
#define ETPU_SYSTEM_CLOCK_TCR2    (UNS32)(SYSTEM_CLOCK/16u)

/* eTPU definitions */
#define ETPU_DATA_RAM_START_ABS   (UNS32)0xC3FC8000
#define ETPU_NUMBER_MAX           (UNS8)2
#define ETPU_A                    (UNS32)0
#define ETPU_B                    (UNS32)1
#define ETPU_A_OFFSET             (UNS8)0
#define ETPU_B_OFFSET             (UNS8)64
#define ETPU_A_LINK_ID            (UNS8)0x40
#define ETPU_B_LINK_ID            (UNS8)0x80

/* Channel definitions */
#define ETPU_CHANNEL_NUMBER_MAX   (UNS8)32
#define CHANNEL_0                 (UNS8)0
#define CHANNEL_1                 (UNS8)1
#define CHANNEL_2                 (UNS8)2
#define CHANNEL_3                 (UNS8)3
#define CHANNEL_4                 (UNS8)4
#define CHANNEL_5                 (UNS8)5
#define CHANNEL_6                 (UNS8)6
#define CHANNEL_7                 (UNS8)7
#define CHANNEL_8                 (UNS8)8
#define CHANNEL_9                 (UNS8)9
#define CHANNEL_10                (UNS8)10
#define CHANNEL_11                (UNS8)11
#define CHANNEL_12                (UNS8)12
#define CHANNEL_13                (UNS8)13
#define CHANNEL_14                (UNS8)14
#define CHANNEL_15                (UNS8)15
#define CHANNEL_16                (UNS8)16
#define CHANNEL_17                (UNS8)17
#define CHANNEL_18                (UNS8)18
#define CHANNEL_19                (UNS8)19
#define CHANNEL_20                (UNS8)20
#define CHANNEL_21                (UNS8)21
#define CHANNEL_22                (UNS8)22
#define CHANNEL_23                (UNS8)23
#define CHANNEL_24                (UNS8)24
#define CHANNEL_25                (UNS8)25
#define CHANNEL_26                (UNS8)26
#define CHANNEL_27                (UNS8)27
#define CHANNEL_28                (UNS8)28
#define CHANNEL_29                (UNS8)29
#define CHANNEL_30                (UNS8)30
#define CHANNEL_31                (UNS8)31

/* Channel priority */
#define ETPU_PRIORITY_HIGH        (UNS8)0x3
#define ETPU_PRIORITY_MIDDLE      (UNS8)0x2
#define ETPU_PRIORITY_LOW         (UNS8)0x1
#define ETPU_PRIORITY_DISABLED    (UNS8)0x0
#define ETPU_DISABLED              (UNS8)0x0

/* Channel configuration registers */
/* CR register bit field offset */
#define ETPU_SCR_CIE_OFFSET                    (UNS8) 31
#define ETPU_SCR_CPR_OFFSET                    (UNS8) 28
#define ETPU_SCR_ETCS_OFFSET                   (UNS8) 24
#define ETPU_SCR_CFS_OFFSET                    (UNS8) 16
#define ETPU_SCR_CPBA_OFFSET                   (UNS8) 3

#define ETPU_ENABLE_CHAN_INTERRUPT             (UNS8) 1
#define ETPU_DISABLE_CHAN_INTERRUPT            (UNS8) 0

/* Entry table coding */
#define ALTERNATE_TABLE                        (UNS8) 1
#define STANDARD_TABLE                         (UNS8) 0

#define ETPU_SHIFT_TO_MSB                      (UNS8) 24
#define ETPU_CLEAR_MSB                         (UNS32)0x00FFFFFF

/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/
extern UNS32 data_free_ram;


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void EtpuInitializeEngine(void);
extern void EtpuStartTimeBase(void);
extern void SetHSRR(UNS8 a_channel,UNS8 a_value);
#endif
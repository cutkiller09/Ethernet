/***************************************************************/
/* FUNCTION : eTPU library services                            */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "./eTPU_Lib/eTPU_auto.h"

#include "etpu_lb.h"

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
UNS32 data_free_ram;


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
/* ---- ETPU HW CONFIGURATION ---- */
/* eTPU SCM */
#define ETPU_SCM_ADDRESS                       (UNS32)0xC3FD0000
#define ETPU_SCM_SIZE                          (UNS32)4096

/* eTPU RAM (relative address) */
#define ETPU_A429_RX_FILTER_SIZE               (UNS32)1024
#define ETPU_DATA_RAM_START_REL                (UNS32)(ETPU_A429_RX_FILTER_SIZE)
#define ETPU_DATA_RAM_SIZE                     (UNS32)0xC00
#define ETPU_DATA_RAM_INIT                     (UNS32)0x00000000

/* eTPU Engine A configuration                                               */
/* ECR - Engine configuration:                                               */
/*    FEND    = 0            - Normal Operation                              */
/*    MDIS    = 0            - eTPU engine runs                              */
/*    STF     = 0            - Stop flag bit                                 */
/*    HLTF    = 0            - Halt mode flag                                */
/*    FPSCK   = 0b000        - Filter prescaler clock => sysclk/2            */
/*    CDFC    = 0b00         - Channel digital filter => 2 samples mode      */
/*    ETB     = 0b00000      - Entry table base => adr SCM 0x00000              */
#define ETPU_ECR_A_INIT                        (UNS32)0x00000000

/* TBCR - Time base:                                                         */
/*    TCR2CTL = 0b100        - TCR2 clock control => sysclk/8                */
/*    TCRCF   = 0b00         - External clock filter => not used             */
/*    AM      = 0            - Angle Mode disable                            */
/*    TCR2P   = 0b000001     - TCR2 prescaler of 2 (1+1) applied to TCR2CTL/2 */
/*    TCR1CTL = 0b10         - TCR1 clock control => sysclk/2                */
/*    TCR1P   = 0b00000000   - TCR1 prescaler of 0 (0+1) applied to sysclk/1 */
#define ETPU_TBCR_A_INIT            (UNS32)0x80018000

/* Stack bus configuration */
#define ETPU_REDCR_A_INIT                      (UNS32)0x00000000

/* eTPU Engine B configuration                                              */
/* ECR - Engine configuration:                                              */
/*    FEND    = 0            - Normal Operation                             */
/*    MDIS    = 0            - eTPU engine runs                             */
/*    STF     = 0            - Stop flag bit                                */
/*    HLTF    = 0            - Halt mode flag                               */
/*    FPSCK   = 0b110        - Filter prescaler clock => sysclk/128         */
/*                             Min. Width Detected = 2.29 us                */
/*                             Max. Width Filtered = 1.14 us                */
/*    CDFC    = 0b00         - Channel digital filter => 2 samples mode     */
/*    ETB     = 0b00000      - Entry table base => adr SCM 0x00000             */
#define ETPU_ECR_B_INIT                        (UNS32)0x00060000

/* TBCR - Time base:                                                         */
/*    TCR2CTL = 0b100        - TCR2 clock control => sysclk/8                */
/*    TCRCF   = 0b00         - External clock filter => not used             */
/*    AM      = 0            - Angle Mode disable                            */
/*    TCR2P   = 0b000001     - TCR2 prescaler of 2 (1+1) applied to TCR2CTL/2 */
/*    TCR1CTL = 0b10         - TCR1 clock control => sysclk/2                */
/*    TCR1P   = 0b00000000   - TCR1 prescaler of 0 (0+1) applied to sysclk/1 */
#define ETPU_TBCR_B_INIT            (UNS32)0x80018000

/* Stack bus configuration */
#define ETPU_REDCR_B_INIT                      (UNS32)0x00000000

/* ---- ETPU SCM CONSTANT ---- */
/* eTPU SCM constant */
const UNS32 K_TAB_etpu_image[ETPU_SCM_SIZE] =
{
    #include "eTPU_Lib/eTPU_code.h"
};


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
/* Global function : EtpuInitializeEngine                      */
/***************************************************************/
void EtpuInitializeEngine(void)
{
    UNS32 *ram_PTR;
    UNS32 i;

    /* Stop eTPU_A */
    ETPU.ECR_A.B.MDIS = (VUNS32)TRUE;
    /* Stop eTPU_B */
    ETPU.ECR_B.B.MDIS = (VUNS32)TRUE;
    /* Make SCM visible for CPU */
    ETPU.MCR.B.VIS = (VUNS32)TRUE;
    /* Wait until SCM is visible */
    while(ETPU.MCR.B.VIS != (VUNS32)TRUE)
    {
    }

    /* Copy eTPU code image */
    ram_PTR = (UNS32 *)ETPU_SCM_ADDRESS;
    for (i = 0; i < ETPU_SCM_SIZE; i++)
    {
        *ram_PTR = K_TAB_etpu_image[i];
        ram_PTR++;
    }
    /* Enable SCM for eTPU engines */
    ETPU.MCR.B.VIS = (VUNS32)FALSE;

    /* Set ram pointer to the begining of eTPU data RAM */
    ram_PTR = (UNS32 *)ETPU_DATA_RAM_START_ABS;

    /* Initialize eTPU data RAM */
    for (i = 0; i < (ETPU_DATA_RAM_SIZE / 4u); i++)
    {
        *ram_PTR = ETPU_DATA_RAM_INIT;
        ram_PTR ++;
    }

    /* Configure MISC register */
    ETPU.MISCCMPR.R = _MISC_VALUE_;
    /* Clear Global exception */
    ETPU.MCR.B.GEC = (VUNS32)TRUE;
    /* Enable MISC logic */
    ETPU.MCR.B.SCMMISEN = (VUNS32)TRUE;

    /* Configure Engine ETPU_A */
    ETPU.ECR_A.R =   ETPU_ECR_A_INIT;
    ETPU.TBCR_A.R =  ETPU_TBCR_A_INIT;
    ETPU.REDCR_A.R = ETPU_REDCR_A_INIT;

    /* Configure Engine ETPU_B */
    ETPU.ECR_B.R =   ETPU_ECR_B_INIT;
    ETPU.TBCR_B.R =  ETPU_TBCR_B_INIT;
    ETPU.REDCR_B.R = ETPU_REDCR_B_INIT;

    /* Available RAM starts after filter label table */
    /* !!! relative address */
    data_free_ram = ETPU_DATA_RAM_START_REL;
}


/***************************************************************/
/* Global function : EtpuStartTimeBase                         */
/***************************************************************/
void EtpuStartTimeBase(void)
{
    /* Global Time Base enabled - synchronous start of TCRs */
    ETPU.MCR.B.GTBE = (VUNS32)TRUE;
}


/***************************************************************/
/* Global function : SetHSRR                                   */
/***************************************************************/
void SetHSRR(UNS8 a_channel,UNS8 a_value)
{
    /* Set HSRR register to the specified value */
    ETPU.CHAN[a_channel].HSRR.R = a_value;
}


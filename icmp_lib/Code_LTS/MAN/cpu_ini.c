/***************************************************************/
/* FUNCTION : Initialize PPC5554 registers                     */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "cpu_lb.h"
#include "interface.h"
#include "configuration.h"

#include "cpu_ini.h"


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
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
/* System Frequency = 112 MHZ                                          */
/* Fsys = Fxtal * ((FMPLL_MFD + 4)/((FMPLL_PREDIV + 1) x 2^FMPLL_RFD)) */
/*      - Fxtal         = 8MHz                                         */
/*      - FMPLL_MFD     = 10                                           */
/*      - FMPLL_PREDIV  = 0                                            */
/*      - FMPLL_RFD     = 0                                            */

#define FMPLL_PREDIV_VAL        (UNS32) (0 * (0x10000000))
#define FMPLL_MFD_VAL           (UNS32) (10 * (0x00800000))
#define FMPLL_RFD_VAL_INIT      (UNS32) (1 * (0x00080000))
#define FMPLL_RFD_VAL           (UNS32) (0 * (0x00080000))
#define FMPLL_RATE_VAL          (UNS32) (1 * (0x00001000))

#define FMPLL_SYNCR_FIRST_INIT  (UNS32) (FMPLL_PREDIV_VAL + FMPLL_MFD_VAL + FMPLL_RFD_VAL_INIT + FMPLL_RATE_VAL)
#define FMPLL_SYNCR_SEC_INIT    (UNS32) (FMPLL_PREDIV_VAL + FMPLL_MFD_VAL + FMPLL_RFD_VAL + FMPLL_RATE_VAL)



/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Local function : InitializeFMPLL                            */
/***************************************************************/
void InitializeFMPLL(void)
{  
    /* Initialize the FMPLL control registers, Set the RFD field to final RFD value + 1 */
    FMPLL.SYNCR.R = FMPLL_SYNCR_FIRST_INIT;
    /* Wait for FMPLL to LOCK before setting the final RFD value */
    while (FMPLL.SYNSR.B.LOCK != 1)
    {
    }
    /* e2181: Set the RFD field to final RFD value */
    FMPLL.SYNCR.R = FMPLL_SYNCR_SEC_INIT;
}


/***************************************************************/
/* Local function : InitializeMMU                              */
/***************************************************************/
void InitializeMMU(void)
{
    /* Call InitializeMMUTlb function to initialize access for current code (read/execution) in TLB entry 0 */
    /* Mapped from the address 0x00000000 to 0x003FFFFF (4 Mbytes, covering the 2Mbytes of Flash) for all process ID in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x10000000, 0xC0000600, 0x00000008, 0x00000033);

    /* Call SetPID0 function to change the current PID value to 4 for the BSP and APPLICATIVE software execution */
    SetPID0(4);

    /*! External SRAM access configuration */
    /*! NOTE: Other specific access External SRAM will be computed after APPLICATIVE S/W initialization */
    /* Call InitializeMMUTlb function to initialize access (read/write) to the external SRAM data in TLB entry 1 */
    /* Mapped from the address 0x20000000 to 0x200FFFFF (4 Mbytes, only 2 Mb in reality) for BSP/APP process ID (4) in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x10010000, 0xC0040600, 0x20000008, 0x2000000F);

    /*! Internal SRAM access configuration */
    /* Call InitializeMMUTlb function to initialize access (read/write) to the internal SRAM data in TLB entry 2 */
    /* Mapped from the address 0x40000000 to 0x4000FFFF (64 Kbytes) for BSP/APP process ID (4) in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x10020000, 0xC0040300, 0x40000008, 0x4000000F);

    /*! Internal FLASH access configuration */
    /*! NOTE: Specific access FLASH will be computed after APPLICATIVE S/W initialization */
    /* Call InitializeMMUTlb function to initialize access (read/execution) to the internal FLASH Interrupt handler (user part) code in TLB entry 3 */
    /* Mapped from the address 0x0003E000 to 0x0003EFFF (4 Kbytes) for BITE process ID (5) in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x10030000, 0xC0050100, 0x0003E008, 0x0003E033);
    
    /* Call InitializeMMUTlb function to initialize access (read/execution) to the internal FLASH Interrupt handler (supervisor part) code in TLB entry 4 */
    /* Mapped from the address 0x0003F000 to 0x0003FFFF (4 Kbytes) for BITE process ID (5) in supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x10040000, 0xC0050100, 0x0003F008, 0x0003F011);
    
    /* Call InitializeMMUTlb function to initialize access (read/execution) to the internal FLASH in TLB entry 5 */
    /* Mapped from the address 0x00000000 to 0x001FFFFF, for BSP/APP process ID (4) in user/supervisor mode */
    /* This entry table is protected from invalidation and is cached inhibited */
    InitializeMMUTlb(0x10050000, 0xC0040600, 0x00000008, 0x00000033);

    /*! Other general access configuration */
    /* Call InitializeMMUTlb function to initialize access (R/W) to the EBI (I/O ports, PLDs) peripheral in TLB entry 6 */
    /* Mapped from the address 0x20800000 to 0x20BFFFFF (4 Mbytes) for BSP/APP process ID (4) in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x10060000, 0xC0040600, 0x20800008, 0x2080000F);

    /* Call InitializeMMUTlb function to initialize access (R/W) to the Peripheral Bridge A in TLB entry 30 */
    /* Mapped from the address 0xC3F00000 to 0xC3FFFFFF (1 Mbytes) for BSP/APP process ID (4) in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x101E0000, 0xC0040500, 0xC3F00008, 0xC3F0000F);

    /* Call InitializeMMUTlb function to initialize access (R/W) to the Peripheral Bridge B in TLB entry 31 */
    /* Mapped from the address 0xFFF00000 to 0xFFFFFFFF (1 Mbytes) for BSP/APP process ID (4) in user/supervisor mode */
    /* This entry table is protected from invalidation and cached inhibited */
    InitializeMMUTlb(0x101F0000, 0xC0040500, 0xFFF00008, 0xFFF0000F);

    /* Call InitializeMMUTlb function to invalidate MMU TLB entry 7 to 23 */
    /*! Note: entry 7 to 23 are used for specific configuration for partitioning */
    InitializeMMUTlb(0x10070000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10080000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10090000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x100A0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x100B0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x100C0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x100D0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x100E0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x100F0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10100000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10110000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10120000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10130000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10140000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10150000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10160000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x10170000, 0x00000000, 0x00000000, 0x00000000);
	InitializeMMUTlb(0x10180000, 0x00000000, 0x00000000, 0x00000000);
    /*! NOTE: Next six entries are free to use */
    InitializeMMUTlb(0x10190000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x101A0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x101B0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x101C0000, 0x00000000, 0x00000000, 0x00000000);
    InitializeMMUTlb(0x101D0000, 0x00000000, 0x00000000, 0x00000000);
}


/***************************************************************/
/* Global function : InitializeMMUForPartition                 */
/***************************************************************/
void InitializeMMUForPartition(void)
{    
    /* Call InitializeMMUTlb function to initialize access (read/write/execution) for the BSP, APP and BITE software in TLB entry 7 to 23 */
    /* The software shall use configuration provided by the APPLICATIVE software */
    InitializeMMUTlb(0x10070000, I_BSP_conf.MMU_configuration.TAB[0].mas1,  I_BSP_conf.MMU_configuration.TAB[0].mas2,  I_BSP_conf.MMU_configuration.TAB[0].mas3);
    InitializeMMUTlb(0x10080000, I_BSP_conf.MMU_configuration.TAB[1].mas1,  I_BSP_conf.MMU_configuration.TAB[1].mas2,  I_BSP_conf.MMU_configuration.TAB[1].mas3);
    InitializeMMUTlb(0x10090000, I_BSP_conf.MMU_configuration.TAB[2].mas1,  I_BSP_conf.MMU_configuration.TAB[2].mas2,  I_BSP_conf.MMU_configuration.TAB[2].mas3);
    InitializeMMUTlb(0x100A0000, I_BSP_conf.MMU_configuration.TAB[3].mas1,  I_BSP_conf.MMU_configuration.TAB[3].mas2,  I_BSP_conf.MMU_configuration.TAB[3].mas3);
    InitializeMMUTlb(0x100B0000, I_BSP_conf.MMU_configuration.TAB[4].mas1,  I_BSP_conf.MMU_configuration.TAB[4].mas2,  I_BSP_conf.MMU_configuration.TAB[4].mas3);
    InitializeMMUTlb(0x100C0000, I_BSP_conf.MMU_configuration.TAB[5].mas1,  I_BSP_conf.MMU_configuration.TAB[5].mas2,  I_BSP_conf.MMU_configuration.TAB[5].mas3);
    InitializeMMUTlb(0x100D0000, I_BSP_conf.MMU_configuration.TAB[6].mas1,  I_BSP_conf.MMU_configuration.TAB[6].mas2,  I_BSP_conf.MMU_configuration.TAB[6].mas3);
    InitializeMMUTlb(0x100E0000, I_BSP_conf.MMU_configuration.TAB[7].mas1,  I_BSP_conf.MMU_configuration.TAB[7].mas2,  I_BSP_conf.MMU_configuration.TAB[7].mas3);
    InitializeMMUTlb(0x100F0000, I_BSP_conf.MMU_configuration.TAB[8].mas1,  I_BSP_conf.MMU_configuration.TAB[8].mas2,  I_BSP_conf.MMU_configuration.TAB[8].mas3);
    InitializeMMUTlb(0x10100000, I_BSP_conf.MMU_configuration.TAB[9].mas1,  I_BSP_conf.MMU_configuration.TAB[9].mas2,  I_BSP_conf.MMU_configuration.TAB[9].mas3);
    InitializeMMUTlb(0x10110000, I_BSP_conf.MMU_configuration.TAB[10].mas1, I_BSP_conf.MMU_configuration.TAB[10].mas2, I_BSP_conf.MMU_configuration.TAB[10].mas3);
    InitializeMMUTlb(0x10120000, I_BSP_conf.MMU_configuration.TAB[11].mas1, I_BSP_conf.MMU_configuration.TAB[11].mas2, I_BSP_conf.MMU_configuration.TAB[11].mas3);
    InitializeMMUTlb(0x10130000, I_BSP_conf.MMU_configuration.TAB[12].mas1, I_BSP_conf.MMU_configuration.TAB[12].mas2, I_BSP_conf.MMU_configuration.TAB[12].mas3);
    InitializeMMUTlb(0x10140000, I_BSP_conf.MMU_configuration.TAB[13].mas1, I_BSP_conf.MMU_configuration.TAB[13].mas2, I_BSP_conf.MMU_configuration.TAB[13].mas3);
    InitializeMMUTlb(0x10150000, I_BSP_conf.MMU_configuration.TAB[14].mas1, I_BSP_conf.MMU_configuration.TAB[14].mas2, I_BSP_conf.MMU_configuration.TAB[14].mas3);
    InitializeMMUTlb(0x10160000, I_BSP_conf.MMU_configuration.TAB[15].mas1, I_BSP_conf.MMU_configuration.TAB[15].mas2, I_BSP_conf.MMU_configuration.TAB[15].mas3);
    InitializeMMUTlb(0x10170000, I_BSP_conf.MMU_configuration.TAB[16].mas1, I_BSP_conf.MMU_configuration.TAB[16].mas2, I_BSP_conf.MMU_configuration.TAB[16].mas3);
    InitializeMMUTlb(0x10180000, I_BSP_conf.MMU_configuration.TAB[17].mas1, I_BSP_conf.MMU_configuration.TAB[17].mas2, I_BSP_conf.MMU_configuration.TAB[17].mas3);
    
	/* Call InitializeMMUTlb function to invalidate MMU TLB entry 0 */
    InitializeMMUTlb(0x10000000, 0x00000000, 0x00000000, 0x00000000);
}

/***************************************************************/
/* Global function : InitializeCPU_Ini                         */
/***************************************************************/
void InitializeCPU_Ini(void)
{
    /* Call the function InitializeSPEFSCR, to initialize the SPEFSCR register */
    InitializeSPEFSCR();

    /* Call the function InitializeFMPLL, to initialize the FMPLL */
    InitializeFMPLL();

    /* Call the function InitializeMMU, to initialize the MMU */
    InitializeMMU();

	/* Call InitializeMMUForPartition function to finalize the MMU configuration with the configuration provided by the APPLICATIVE S/W */
    InitializeMMUForPartition();
	
	/* Call the function InitializeL1Cache, to disable the L1 cache */
    InitializeL1Cache();
}



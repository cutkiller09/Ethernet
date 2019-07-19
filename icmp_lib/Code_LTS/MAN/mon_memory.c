/***************************************************************/
/* FUNCTION : Monitor controller memory                        */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"
#include "crc32_lb.h"
#include "interface.h"
#include "l91152ae.h"
#include "wdg_lb.h"

#include "mon_memory.h"

/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/
BOOLEAN F_ram_fail;
BOOLEAN F_crc_boot_fail;

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
#define K_FLASH_BOOT_ADDR                     (UNS32)0x00000000
#define K_FLASH_BOOT_SIZE                     (UNS32)0x00004000
                                              
#define K_FLASH_SPLOADER_ADDR                 (UNS32)0x00004000
#define K_FLASH_SPLOADER_SIZE                 (UNS32)0x0000C000
                                              
#define K_FLASH_BSP_ADDR                      (UNS32)0x00010000
#define K_FLASH_BSP_SIZE                      (UNS32)0x00030000
                                              
#define K_FLASH_ACSC_ADDR                     (UNS32)0x00040000
#define K_FLASH_ACSC_SIZE                     (UNS32)0x00140000
                                              
#define K_FLASH_BITE_ADDR                     (UNS32)0x00140000
#define K_FLASH_BITE_SIZE                     (UNS32)0x00040000
                                              
#define K_FLASH_AC_ADDR                       (UNS32)0x00160000
#define K_FLASH_AC_SIZE                       (UNS32)0x00A00000
                                              
#define K_VALID_CRC                           (UNS32)0
                                              
#define BLOCK_SIZE    (UNS32)0x00001000    /* 4 KByte */

/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL DATA                             */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Global function : MonitorCRC                                */
/***************************************************************/
void MonitorCRC(void)
{
    UNS32 return_value;

    /* Monitor BOOT CRC */
    /* Call CalculateCRC32 function to calculate CRC from K_FLASH_BOOT_ADDR */
    /* and for K_FLASH_BOOT_SIZE 32bits */
    return_value = CalculateCRC32((UNS8 *)(K_FLASH_BOOT_ADDR), K_FLASH_BOOT_SIZE);
    /* Set a CRC error in case of the computed CRC is different than K_VALID_CRC */
    if (return_value != K_VALID_CRC)
    {
        I_BSP_Out.monitoring.software.crc_F.B.boot_crc_F = (UNS32)TRUE;
        F_crc_boot_fail = TRUE;
    }
    else
    {
    }

    /* Monitor SHOP LOADER CRC */
    /* Call CalculateCRC32 function to calculate CRC from K_FLASH_SPLOADER_ADDR */
    /* and for K_FLASH_SPLOADER_SIZE 32bits */
    return_value = CalculateCRC32((UNS8 *)(K_FLASH_SPLOADER_ADDR), K_FLASH_SPLOADER_SIZE);
    /* Set a CRC error in case of the computed CRC is different than K_VALID_CRC */
    if (return_value != K_VALID_CRC)
    {
        I_BSP_Out.monitoring.software.crc_F.B.shop_loader_crc_F = (UNS32)TRUE;
    }
    else
    {
    }

    /* Monitor BSP CRC */
    /* Call CalculateCRC32 function to calculate CRC from K_FLASH_BSP_ADDR */
    /* and for K_FLASH_BSP_SIZE 32bits */
    return_value = CalculateCRC32((UNS8 *)(K_FLASH_BSP_ADDR), K_FLASH_BSP_SIZE);
    /* Set a CRC error in case of the computed CRC is different than K_VALID_CRC */
    if (return_value != K_VALID_CRC)
    {
        I_BSP_Out.monitoring.software.crc_F.B.bsp_crc_F = (UNS32)TRUE;
    }
    else
    {
    }

    /* Monitor ACSC CRC */
    /* Call CalculateCRC32 function to calculate CRC from K_FLASH_ACSC_ADDR */
    /* and for K_FLASH_ACSC_SIZE 32bits */
    return_value = CalculateCRC32((UNS8 *)(K_FLASH_ACSC_ADDR), K_FLASH_ACSC_SIZE);
    /* Set a CRC error in case of the computed CRC is different than K_VALID_CRC */
    if (return_value != K_VALID_CRC)
    {
        I_BSP_Out.monitoring.software.crc_F.B.app1_crc_F = (UNS32)TRUE;
    }
    else
    {
    }

    /* Monitor BITE CRC */
    /* Call CalculateCRC32 function to calculate CRC from K_FLASH_BITE_ADDR */
    /* and for K_FLASH_BITE_SIZE 32bits */
    return_value = CalculateCRC32((UNS8 *)(K_FLASH_BITE_ADDR), K_FLASH_BITE_SIZE);
    /* Set a CRC error in case of the computed CRC is different than K_VALID_CRC */
    if (return_value != K_VALID_CRC)
    {
        I_BSP_Out.monitoring.software.crc_F.B.bite_crc_F = (UNS32)TRUE;
    }
    else
    {
    }
}


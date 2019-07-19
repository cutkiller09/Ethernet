/***************************************************************/
/* FUNCTION : Manage software initialization according to cold */
/*            start and internal RAM data back up              */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "configuration.h"
#include "disc_acq.h"
#include "data_ini.h"
#include "hard_def.h"
#include "wdg_lb.h"
#include "trap_tab.h"

#include "soft_ini.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
T_Function_PTR LaunchAPP1Maintask_PTR;
T_Function_PTR InitializeAPPSoftware_PTR;

T_Function_PTR LaunchBITELongAction_PTR;
T_Function_PTR LaunchBITEShortAction_PTR;

UNS32 bsp_address;
UNS32 app1_address;
UNS32 bite_address;
UNS32 acloader_address;

UNS32 bsp_size;
UNS32 app1_size;
UNS32 bite_size;
UNS32 acloader_size;

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
#define K_BSP_START_ADDRESS          (UNS32)0x00010000
#define K_APP1_START_ADDRESS         (UNS32)0x0015FFE8
/* Not yet define */
#define K_BITE_START_ADDRESS         (UNS32)0xFFFFFFFF

#define K_ACLOADER_START_ADDRESS     (UNS32)0x00180000
#define K_PART_NUMBER_OFFSET         (UNS32)40

#define K_BOOT_ADDRESS               (UNS32)0x00000000
#define K_BOOT_SIZE                  (UNS32)0x00004000

#define K_SLOADER_ADDRESS            (UNS32)0x00004000
#define K_SLOADER_SIZE               (UNS32)0x0000C000

#define K_ACLOADER_SIZE              (UNS32)0x00040000

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
T_Function_PTR InitializeAPP1Software_PTR;
T_Function_PTR LaunchAPP1MaintaskCPCS_PTR;
T_Function_PTR InitializeAPP3Software_PTR;



/***************************************************************/
/* Global function : GetHardwareSoftwareIdentification         */
/***************************************************************/
void GetHardwareSoftwareIdentification(void)
{
    UNS8 i;
    UNS8 *flash_PTR;
    UNS8 *mram_PTR;

    /* Get All Hardware Part Number and Serial Number*/
    /* Set pointer to the start address of hardware Part Number */
    mram_PTR = (UNS8 *)(K_HW_PART_NUMBER_ADDRESS);
    /* Copy the BOOT software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_boot_part_number */
    for(i=0;i < K_HW_NUMBER_SIZE;i++)
    {
        I_BSP_Out.identification.TAB_hw_part_number[i] = *mram_PTR;
        mram_PTR++;
    }
    /* Set pointer to the start address of hardware Serial Number */
    mram_PTR = (UNS8 *)(K_HW_PART_NUMBER_ADDRESS + K_HW_NUMBER_SIZE);
    /* Copy the BOOT software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_boot_part_number */
    for(i=0;i < K_HW_NUMBER_SIZE;i++)
    {
        I_BSP_Out.identification.TAB_hw_serial_number[i] = *mram_PTR;
        mram_PTR++;
    }

    /* Set pointer to the start address of BOOT software Part Number in the header */
    flash_PTR = (UNS8 *)(K_BOOT_ADDRESS + K_PART_NUMBER_OFFSET);
    /* Copy the BOOT software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_boot_part_number */
    for(i=0;i < MAX_SW_PARTNUMBER;i++)
    {
        I_BSP_Out.identification.TAB_sw_boot_part_number[i] = *flash_PTR;
        flash_PTR++;
    }
    /* Set pointer to the start address of BOOT software CRC32 in the header */
    flash_PTR = (UNS8 *)(K_BOOT_ADDRESS + K_BOOT_SIZE - 4u);
    /* Copy the BOOT software CRC32 from software header to structure I_BSP_Out.identification.TAB_sw_boot_crc32 */
    for(i=0;i < MAX_SW_CRC;i++)
    {
        I_BSP_Out.identification.TAB_sw_boot_crc32[i] = *flash_PTR;
        flash_PTR++;
    }

    /* Set pointer to the start address of SLOADER software Part Number in the header */
    flash_PTR = (UNS8 *)(K_SLOADER_ADDRESS + K_PART_NUMBER_OFFSET);
    /* Copy the SLOADER software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_sloader_part_number */
    for(i=0;i < MAX_SW_PARTNUMBER;i++)
    {
        I_BSP_Out.identification.TAB_sw_sloader_part_number[i] = *flash_PTR;
        flash_PTR++;
    }
    /* Set pointer to the start address of SLOADER software CRC32 in the header */
    flash_PTR = (UNS8 *)(K_SLOADER_ADDRESS + K_SLOADER_SIZE - 4u);
    /* Copy the SLOADER software CRC32 from software header to structure I_BSP_Out.identification.TAB_sw_sloader_crc32 */
    for(i=0;i < MAX_SW_CRC;i++)
    {
        I_BSP_Out.identification.TAB_sw_sloader_crc32[i] = *flash_PTR;
        flash_PTR++;
    }

    /* Set pointer to the start address of BSP software Part Number in the header */
    flash_PTR = (UNS8 *)(bsp_address + K_PART_NUMBER_OFFSET);
    /* Copy the BSP software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_bsp_part_number */
    for(i=0;i < MAX_SW_PARTNUMBER;i++)
    {
        I_BSP_Out.identification.TAB_sw_bsp_part_number[i] = *flash_PTR;
        flash_PTR++;
    }
    /* Set pointer to the start address of BSP software CRC32 in the header */
    flash_PTR = (UNS8 *)(bsp_address + bsp_size - 4u);
    /* Copy the BSP software CRC32 from software header to structure I_BSP_Out.identification.TAB_sw_bsp_crc32 */
    for(i=0;i < MAX_SW_CRC;i++)
    {
        I_BSP_Out.identification.TAB_sw_bsp_crc32[i] = *flash_PTR;
        flash_PTR++;
    }

    /* Set pointer to the start address of APP1 software Part Number in the header */
    flash_PTR = (UNS8 *)(app1_address + K_PART_NUMBER_OFFSET);
    /* Copy the APP1 software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_app1_part_number */
    for(i=0;i < MAX_SW_PARTNUMBER;i++)
    {
        I_BSP_Out.identification.TAB_sw_app1_part_number[i] = *flash_PTR;
        flash_PTR++;
    }
    /* Set pointer to the start address of APP1 software CRC32 in the header */
    flash_PTR = (UNS8 *)(app1_address + app1_size - 4u);
    /* Copy the APP1 software CRC32 from software header to structure I_BSP_Out.identification.TAB_sw_app1_crc32 */
    for(i=0;i < MAX_SW_CRC;i++)
    {
        I_BSP_Out.identification.TAB_sw_app1_crc32[i] = *flash_PTR;
        flash_PTR++;
    }
    
    
    if(bite_size != 0u)
    {
        /* Set pointer to the start address of BITE software Part Number in the header */
      flash_PTR = (UNS8 *)(bite_address + K_PART_NUMBER_OFFSET);
      /* Copy the BITE software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_bite_part_number */
      for(i=0;i < MAX_SW_PARTNUMBER;i++)
      {
         I_BSP_Out.identification.TAB_sw_bite_part_number[i] = *flash_PTR;
         flash_PTR++;
      }
      /* Set pointer to the start address of BITE software CRC32 in the header */
      flash_PTR = (UNS8 *)(bite_address + bite_size - 4u);
      /* Copy the BITE software CRC32 from software header to structure I_BSP_Out.identification.TAB_sw_bite_crc32 */
      for(i=0;i < MAX_SW_CRC;i++)
      {
         I_BSP_Out.identification.TAB_sw_bite_crc32[i] = *flash_PTR;
         flash_PTR++;
      }
    }
    else
    {
        /* Initialize the structure I_BSP_Out.identification.TAB_sw_bite_part_number to 0xFF*/
      for(i=0;i < MAX_SW_PARTNUMBER;i++)
      {
         I_BSP_Out.identification.TAB_sw_bite_part_number[i] = (UNS8)0xFF;
      }
      /* Initialize the structure I_BSP_Out.identification.TAB_sw_bite_crc32  to 0xFF*/
      for(i=0;i < MAX_SW_CRC;i++)
      {
         I_BSP_Out.identification.TAB_sw_bite_crc32[i] = (UNS8)0xFF;
      }
    }
    
    /* Set pointer to the start address of ACLOADER software Part Number in the header */
    flash_PTR = (UNS8 *)(acloader_address + K_PART_NUMBER_OFFSET);
    /* Copy the acloader_address software Part Number from software header to structure I_BSP_Out.identification.TAB_sw_bite_part_number */
    for(i=0;i < MAX_SW_PARTNUMBER;i++)
    {
         I_BSP_Out.identification.TAB_sw_bite_part_number[i] = *flash_PTR;
         flash_PTR++;
    }
    /* Set pointer to the start address of acloader_address software CRC32 in the header */
    flash_PTR = (UNS8 *)(acloader_address + acloader_size - 4u);
    /* Copy the acloader_address software CRC32 from software header to structure I_BSP_Out.identification.TAB_sw_bite_crc32 */
    for(i=0;i < MAX_SW_CRC;i++)
    {
         I_BSP_Out.identification.TAB_sw_bite_crc32[i] = *flash_PTR;
         flash_PTR++;
    }
}

/***************************************************************/
/* Global function : InitializeSoftware                        */
/***************************************************************/
void InitializeSoftware(void)
{
    /* Set BSP SW start address and size using BSP header information */
    bsp_address = K_BSP_START_ADDRESS;
    bsp_size = *(UNS32 *)(bsp_address + 8u);
    /* Set APP SW start address and size using Identification Table and APP SW header information*/
    app1_address = *(UNS32 *)(K_APP1_START_ADDRESS);
    app1_size = *(UNS32 *)(app1_address + 8u);
    /* Get APP1 software maintask function address into LaunchAPP1Maintask_PTR */
    LaunchAPP1Maintask_PTR = (void *)(*((UNS32 *)(app1_address + 4u)));

    /* Point to the address of APP1 initialization function into LaunchAPP1MaintaskCPCS_PTR */
    /* by adding an offset of 4 bytes to the start address of APP software LaunchAPPMaintask_PTR */
    LaunchAPP1MaintaskCPCS_PTR = LaunchAPP1Maintask_PTR + 4;
	/* Point to the address of APP initialization function into InitializeAPP1Software_PTR */
    /* by adding an offset of 4 bytes to the start address of APP software LaunchAPPCPCStask_PTR */
    InitializeAPP1Software_PTR = LaunchAPP1MaintaskCPCS_PTR + 4;
    
    /* Set BITE SW start address and size using Identification Table and BITE SW header information*/
    bite_address = K_BITE_START_ADDRESS;
	/* IF BITE software is uploaded */
    if ((bite_address < 0x00200000) && (*(UNS32 *)(bite_address) == 0xCAFEBEAF))
    {
    /* THEN */
        /* Get BITE SW size from BITE SW header information */ 
        bite_size = *(UNS32 *)(bite_address + 8);
    }
    else
    /* ELSE */
    {
        /* Set BITE SW size to 0 */
        bite_size = 0;
    }
    /* END IF */ 

	/* Set acloader SW start address and size using Identification Table and acloader SW header information*/
    acloader_address = K_ACLOADER_START_ADDRESS;
    /* Get acloader SW size from acloader SW header information */ 
    acloader_size = *(UNS32 *)(acloader_address + 8u);
	
    /* Call InitializeData function to initialize software data */
    InitializeData();
	
	/* IF BITE software is uploaded */
    if (bite_size != 0)
    {
       /* Get BITE Long Action function address into LaunchBITELongAction_PTR */
       LaunchBITELongAction_PTR = (void *)(*(UNS32*)(bite_address + 4));
       
       /* Point to the address of BITE Short Action function into LaunchBITEShortAction_PTR */
       /* by adding an offset of 4 bytes to the address of BITE Long Action function LaunchBITELongAction_PTR */
       LaunchBITEShortAction_PTR = LaunchBITELongAction_PTR + 4;
    }
    else
    {
        /* Initialize BITE functions pointer to the Default Handler */
        LaunchBITELongAction_PTR = DefaultHandlerUser;
        LaunchBITEShortAction_PTR = DefaultHandlerUser;
    }
    /* END IF */
       
    /* Call RearmWatchdog function */
    RearmWatchdog();
    
    /* Call function pointed by InitializeAPPSoftware_PTR to Initialize Applicative software */
    InitializeAPP1Software_PTR();
}


/*****************************************************************************/
/* MODULE HEADER                                                             */
/*****************************************************************************/
/*
  MODULE:      
  PROJECT:   F6X  

  DESCRIPTION:
  This module contains functions for manipulation of memory areas, like:
   - copy memory area
   - setting a memory area to given value
   - compare contents of two memory areas
   - host-to-network and network-to-host conversions
   - byte-swap

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/

#ifndef __MEMORY_H__  /* test for multiple inclusion */
#define __MEMORY_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/

/* ---- From supplier classes / modules ------------------------------------ */
#include "standard.h"

/* ---- From sub-classes --------------------------------------------------- */

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

#define MEMORY_BYTE0_MASK_C ((UNS32) 0x000000FF)
#define MEMORY_BYTE1_MASK_C ((UNS32) 0x0000FF00)
#define MEMORY_BYTE2_MASK_C ((UNS32) 0x00FF0000)
#define MEMORY_BYTE3_MASK_C ((UNS32) 0xFF000000)
#define MEMORY_BYTE0_3_SHIFT_C ((UNS32) 24)
#define MEMORY_BYTE1_2_SHIFT_C ((UNS32) 8)
#define MEMORY_BIG_ENDIAN_C   1
#define MEMORY_LITTLE_ENDIAN_C   2
#define MEMORY_BYTE_ORDER_C   (MEMORY_BIG_ENDIAN_C)

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
extern void Memory_Copy8 		(UNS8 * const cDest_ocp,
								UNS8 const * const cSource_icp,
								UNS32 lLength_i);

extern void Memory_Copy16 		(UNS16 * const nDest_ocp,
								UNS16 const * const nSource_icp,
								UNS32 lLength_i);

extern void Memory_Copy32 		(UNS32 * const lDest_ocp,
								UNS32 const * const lSource_icp,
								UNS32 lLength_i);

extern void Memory_Set8 		(UNS8 * const cDest_ocp,
								UNS8 cValue_i,
								UNS32 lLength_i);

extern void Memory_Set16 		(UNS16 * const nDest_ocp,
								UNS16 nValue_i,
								UNS32 lLength_i);

extern void Memory_Set32 		(UNS32 * const lDest_ocp,
								UNS32 lValue_i,
								UNS32 lLength_i);

extern BOOLEAN Memory_Compare8	(UNS8 const * const cArea1_icp,
								UNS8 const * const cArea2_icp,
								UNS32 lLength_i);

extern UNS16 Memory_Htons		(UNS16 nHostShort_i);

extern UNS32 Memory_Htonl		(UNS32 lHostLong_i);

extern UNS16 Memory_Ntohs		(UNS16 nNetShort_i);

extern UNS32 Memory_Ntohl		(UNS32 lNetLong_i);

extern UNS16 Memory_Swap16		(UNS16 nWord_i);

extern UNS32 Memory_Swap32		(UNS32 lLong_i);

#endif /*__MEMORY_H__*/

/* EOF */


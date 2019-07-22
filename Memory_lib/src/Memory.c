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

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/
#include "Memory.h"


/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINEs (private)                          */
/*****************************************************************************/

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */

/* ---- private embedded classes ------------------------------------------- */

/*****************************************************************************/
/* FUNCTION PROTOTYPE                                                        */
/*****************************************************************************/

/* ---- private operations ------------------------------------------------- */
/*****************************************************************************/
/* SPECIAL MODULE DEFINITIONS                                                */
/*****************************************************************************/

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/***************************************************************/
/* Function : Memory_Copy8                                     */
/***************************************************************/
void Memory_Copy8 (UNS8 * const cDest_ocp,
                   UNS8 const * const cSource_icp,
                   UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_53651C60-9946-408b-BB2B-46A0EC696EC6) Memory_Copy8 */
    UNS32  lIndex;

    for (lIndex = (UNS32)0U; lIndex < lLength_i; lIndex++)
    {
        cDest_ocp[lIndex] = cSource_icp[lIndex];
    }
    /*#end ACD# Memory_Copy8 */
}

/***************************************************************/
/* Function : Memory_Copy16                                    */
/***************************************************************/
void Memory_Copy16 (UNS16 * const nDest_ocp,
                    UNS16 const * const nSource_icp,
                    UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_BED8C655-7FD0-4f6f-983F-6DD1177204E6) Memory_Copy16 */
    UNS32  lIndex;

    for (lIndex = (UNS32)0U; lIndex < lLength_i; lIndex++)
    {
        nDest_ocp[lIndex] = nSource_icp[lIndex];
    }
    /*#end ACD# Memory_Copy16 */
}

/***************************************************************/
/* Function : Memory_Copy32                                    */
/***************************************************************/
void Memory_Copy32 (UNS32 * const lDest_ocp,
                    UNS32 const * const lSource_icp,
                    UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_FFDD26C8-693E-4e79-B4C3-8B3D48DE24C8) Memory_Copy32 */
    UNS32  lIndex;

    for (lIndex = (UNS32)0U; lIndex < lLength_i; lIndex++)
    {
        lDest_ocp[lIndex] = lSource_icp[lIndex];
    }
    /*#end ACD# Memory_Copy32 */
}

/***************************************************************/
/* Function : Memory_Set8                                      */
/***************************************************************/
void Memory_Set8 (UNS8 * const cDest_ocp,
                  UNS8 cValue_i,
                  UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_1A0805DB-9A9C-4bc2-B473-9C3E72A4BFA1) Memory_Set8 */
    UNS32  lIndex;

    for (lIndex = (UNS32)0U; lIndex < lLength_i; lIndex++)
    {
        cDest_ocp[lIndex] = cValue_i;
    }
    /*#end ACD# Memory_Set8 */
}

/***************************************************************/
/* Function : Memory_Set16                                     */
/***************************************************************/
void Memory_Set16 (UNS16 * const nDest_ocp,
                   UNS16 nValue_i,
                   UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_039F2BE4-35D9-4f97-A022-D9FF34A799AF) Memory_Set16 */
    UNS32  lIndex;

    for (lIndex = (UNS32)0U; lIndex < lLength_i; lIndex++)
    {
        nDest_ocp[lIndex] = nValue_i;
    }
    /*#end ACD# Memory_Set16 */
}

/***************************************************************/
/* Function : Memory_Set32                                     */
/***************************************************************/
void Memory_Set32 (UNS32 * const lDest_ocp,
                   UNS32 lValue_i,
                   UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_D4DD4023-A55E-44cc-900B-3323C81B7572) Memory_Set32 */
    UNS32  lIndex;

    for (lIndex = (UNS32)0U; lIndex < lLength_i; lIndex++)
    {
        lDest_ocp[lIndex] = lValue_i;
    }
    /*#end ACD# Memory_Set32 */
}

/***************************************************************/
/* Function : Memory_Compare8                                  */
/***************************************************************/
BOOLEAN Memory_Compare8 (UNS8 const * const cArea1_icp,
                        UNS8 const * const cArea2_icp,
                        UNS32 lLength_i)
{
    /*#ACD# M(UDMF::UID_89D1D58C-10A7-43ac-9E37-0E3EA32F2A56) Memory_Compare8 */
    UNS32 lIndex = (UNS32)0U;
    BOOLEAN   bResult = TRUE;
    UNS8  cVal1;
    UNS8  cVal2;

    while ((bResult == TRUE) &&
           (lIndex < lLength_i))
    {
        /* Select next characters */
        cVal1 = cArea1_icp[lIndex];
        cVal2 = cArea2_icp[lIndex];

        /* Or a difference is detected */
        if (cVal1 != cVal2)
        {
            bResult = FALSE;
        }
        lIndex++;
    }
    return bResult;
    /*#end ACD# Memory_Compare8 */
}

/***************************************************************/
/* Function : Memory_Htons                                     */
/***************************************************************/
UNS16 Memory_Htons (UNS16 nHostShort_i)
{
    /*#ACD# M(UDMF::UID_EC104D66-3746-4f06-B878-84BCDA216770) Memory_Htons */
    UNS16 nNetShort;

#if MEMORY_BYTE_ORDER_C == MEMORY_BIG_ENDIAN_C
    nNetShort = nHostShort_i;
#else
    nNetShort = Memory_Swap16(nHostShort_i);
#endif

    return nNetShort;
    /*#end ACD# Memory_Htons */
}

/***************************************************************/
/* Function : Memory_Htonl                                     */
/***************************************************************/
UNS32 Memory_Htonl (UNS32 lHostLong_i)
{
    /*#ACD# M(UDMF::UID_5BC36462-F0D3-4016-8565-9F2E6A78EE43) Memory_Htonl */
    UNS32 lNetLong;

#if MEMORY_BYTE_ORDER_C == MEMORY_BIG_ENDIAN_C
    lNetLong = lHostLong_i;
#else
    lNetLong = Memory_Swap32(lHostLong_i);
#endif

    return lNetLong;
    /*#end ACD# Memory_Htonl */
}

/***************************************************************/
/* Function : Memory_Ntohs                                     */
/***************************************************************/
UNS16 Memory_Ntohs (UNS16 nNetShort_i)
{
    /*#ACD# M(UDMF::UID_26EB2918-4A36-45b7-BC1F-BF0F44FACE7F) Memory_Ntohs */
    return Memory_Htons(nNetShort_i);
    /*#end ACD# Memory_Ntohs */
}

/***************************************************************/
/* Function : Memory_Ntohl                                     */
/***************************************************************/
UNS32 Memory_Ntohl (UNS32 lNetLong_i)
{
    /*#ACD# M(UDMF::UID_BFD0002A-B92E-43db-A635-7D3AEF955D72) Memory_Ntohl */
    return Memory_Htonl(lNetLong_i);
    /*#end ACD# Memory_Ntohl */
}

/***************************************************************/
/* Function : Memory_Swap16                                    */
/***************************************************************/
UNS16 Memory_Swap16 (UNS16 nWord_i)
{
    /*#ACD# M(UDMF::UID_47B48148-9EE3-4fc7-834F-B61BAA43D282) Memory_Swap16 */
    UNS16 nSwapped = (((nWord_i & (UNS16)MEMORY_BYTE1_MASK_C) >>
                                     (UNS16)MEMORY_BYTE1_2_SHIFT_C) |
                         ((nWord_i & (UNS16)MEMORY_BYTE0_MASK_C) <<
                                     (UNS16)MEMORY_BYTE1_2_SHIFT_C));
    return nSwapped;
    /*#end ACD# Memory_Swap16 */
}

/***************************************************************/
/* Function : Memory_Swap32                                    */
/***************************************************************/
UNS32 Memory_Swap32 (UNS32 lLong_i)
{
    /*#ACD# M(UDMF::UID_A8DA6559-5B53-4cf0-B634-A83FF72CABC6) Memory_Swap32 */
    UNS32 lSwapped = (((lLong_i & MEMORY_BYTE3_MASK_C) >> MEMORY_BYTE0_3_SHIFT_C) |
                         ((lLong_i & MEMORY_BYTE2_MASK_C) >> MEMORY_BYTE1_2_SHIFT_C) |
                         ((lLong_i & MEMORY_BYTE1_MASK_C) << MEMORY_BYTE1_2_SHIFT_C) |
                         ((lLong_i & MEMORY_BYTE0_MASK_C) << MEMORY_BYTE0_3_SHIFT_C));
    return lSwapped;
    /*#end ACD# Memory_Swap32 */
}

/* EOF */


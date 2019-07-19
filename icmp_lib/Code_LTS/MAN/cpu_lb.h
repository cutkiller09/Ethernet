#ifndef __CPU_LB_H__
#define __CPU_LB_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         GLOBAL TYPES                        */
/*                                                             */
/***************************************************************/
typedef struct
{
   UNS32 MSB;
   UNS32 LSB;
}
T_Time;


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeL1Cache(void);
extern void InitializeSPEFSCR(void);
extern void InitializeInternalSRAMFirst32KB(void);
extern void InitializeInternalMRAMBSP(void);
extern void InitializeInternalMRAMAPP(void);
extern void InitializeDEC(void);
extern void InitializeMMUTlb(UNS32 a_MAS0_register_value, UNS32 a_MAS1_register_value, UNS32 a_MAS2_register_value, UNS32 a_MAS3_register_value);
extern void SetPID0(UNS32 a_PID0_value);
extern void UnmaskInterrupt(void);
extern void Waitus(UNS16 a_time_in_us);
extern void WaitHundredus(UNS16 a_time_in_tenth_ms);
extern T_Time GetTime(void);
extern void UnmaskInterruptINTC(void);
extern void MaskInterruptINTC(void);
#endif
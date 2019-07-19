#ifndef __SOFT_INI_H__
#define __SOFT_INI_H__
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
/*! Function pointer Type */
typedef void (*T_Function_PTR)(void);

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
extern T_Function_PTR LaunchAPP1Maintask_PTR;
extern T_Function_PTR LaunchAPP1MaintaskCPCS_PTR;
extern T_Function_PTR InitializeAPPSoftware_PTR;

extern T_Function_PTR LaunchBITELongAction_PTR;
extern T_Function_PTR LaunchBITEShortAction_PTR;

extern UNS32 bsp_address;
extern UNS32 app1_address;
extern UNS32 bite_address;

extern UNS32 bsp_size;
extern UNS32 app1_size;
extern UNS32 bite_size;


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeSoftware(void);
extern void GetHardwareSoftwareIdentification(void);
#endif
#ifndef __CPU_LOAD_H__
#define __CPU_LOAD_H__
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
typedef enum
{
    MAIN_TASK         = 0,
	ARINC             = 1,
	SCI_TASK          = 2,
	LEAK_ACQUISITION  = 3,
    APP_CPCS          = 4,
	CAN               = 5,
	APP_ACSC          = 6,
    APP_OTHER         = 7,
    DUMMY             = 8
}
T_TaskID;


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
extern UNS32 CPT_ARINC_RX_occurrence;
extern UNS32 CPT_CAN_RX_occurrence;

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeCPU_Load(void);
extern void StartTaskTimeMeasurement(T_TaskID a_task_ID);
extern void StopTaskTimeMeasurement(T_TaskID a_task_ID);
extern void CalculateCPULoad(void);
#endif
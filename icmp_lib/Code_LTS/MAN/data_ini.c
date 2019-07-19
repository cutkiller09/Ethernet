/***************************************************************/
/* FUNCTION : Initialize all data                              */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"

#include "cpu_def.h"
#include "configuration.h"
#include "can_lb.h"
#include "cpu_load.h"
#include "intc_isr_vectors.h"
#include "main_tsk.h"
#include "mon_memory.h"
#include "mon_register.h"
#include "sci_lb.h"

#include "data_ini.h"


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
/* Global function : InitializeData                            */
/***************************************************************/
void InitializeData(void)
{
    /* Call InitializeMain_Task function to initialize the data of corresponding the module */
    InitializeMain_Task();
	/* Call InitializeCPU_Load function to initialize the data of corresponding the module */
    InitializeCPU_Load();
    /* Call InitializeInterface function to initialize the data of corresponding the module */
    InitializeInterface();
	/* Call InitializeConfiguration function to initialize hardware configuration */
    InitializeConfiguration();
    /* Call InitializeSCI_Lb function to initialize the data of corresponding the module */
    InitializeSCI_Lb();
    /* Call InitializeCan_Lb function to initialize the data of corresponding the module */
    InitializeCan_Lb();
    /* Call InitializeRegisterMonitoring function to initialize the data of corresponding the module */
    InitializeRegisterMonitoring();  
}

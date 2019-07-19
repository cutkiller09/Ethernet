/***************************************************************/
/* FUNCTION : Background task                                  */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_lb.h"
#include "mon_memory.h"
#include "sci_lb.h"
#include "back_tsk.h"


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
/*                      LOCAL DATA                             */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Global function : BackgroundTask                            */
/***************************************************************/
void BackgroundTask(void)
{
    /* Call functions UnmaskSCI_A to enable SCI interrupt */
    UnmaskSCI_A();

    /* Call UnmaskInterrupt function to enable all exception */
    UnmaskInterrupt();

    /* Start an infinite loop */
    for(;;)
    {
        /* Executes monitoring */
        MonitorCRC();
    }
}

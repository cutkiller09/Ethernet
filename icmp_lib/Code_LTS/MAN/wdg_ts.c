/***************************************************************/
/* FUNCTION : Test the watchdog external device                */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_lb.h"
#include "hard_ini.h"
#include "l91152ae.h"
#include "wdg_lb.h"

#include "wdg_ts.h"

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
BOOLEAN F_watchdog_fail;

/***************************************************************/
/*                                                             */
/*                       GLOBAL CONSTANTS                      */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                        LOCAL CONSTANTS                      */
/*                                                             */
/***************************************************************/


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

/***************************************************************/
/* Global function : InitializeWatchdogTest                    */
/*                                                             */
/* Purpose : watchdog test module initialization               */
/* Input   : none                                              */
/* Output  : none                                              */
/***************************************************************/
void InitializeWatchdogTest (void)
{
    /* Watchdog test ok by default */
    F_watchdog_fail = FALSE;

}

/***************************************************************/
/* Global function : TestWatchdog                              */
/***************************************************************/
void TestWatchdog(void)
{
    /***************************************************************/
    /* IF watchdog reset has occured                               */
    /* THEN                                                        */
    /*     IF watchdog test was in progress                        */
    /*     THEN                                                    */
    /*        Stop watchdog test                                   */
    /*     END IF                                                  */
    /* ELSE                                                        */
    /*     IF it is a long power cut                               */
    /*     THEN                                                    */
    /*        Reset watchdog failure flag                          */
    /*        Rearm watchdog (watchdog time [800n,200ms] )         */
    /*        Start watchdog test                                  */
    /*        Wait 500 ms                                          */
    /*        Set watchdog failure flag                            */
    /*        Stop watchdog test                                   */
    /*     END IF                                                  */
    /* END IF                                                      */
    /***************************************************************/
    if (MC_WATCHDOG_RESET == TRUE)
    {
        if (MC_WATCHDOG_TESTED == TRUE)
        {
            MC_WATCHDOG_TESTED = FALSE;
            MC_WATCHDOG_RESET = FALSE;
        }
        else
        {
        }
    }
    else
    { 
        if (MC_LONG_POWER_CUT == 1u)
        {
            F_watchdog_fail = FALSE;
            RearmWatchdog();
            MC_WATCHDOG_TESTED = TRUE;
            WaitHundredus(5000);

            /*!    N.B. : If a watchdog reset occurs during this delay,    */
            /*!    the following treatments will not be performed          */
            F_watchdog_fail = TRUE;
            MC_WATCHDOG_TESTED = FALSE;
        }
        else
        {
        }
    }
}


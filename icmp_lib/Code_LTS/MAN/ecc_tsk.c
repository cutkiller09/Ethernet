/***************************************************************/
/* FUNCTION : Task launch in case of ECC interrupt             */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "cpu_lb.h"
#include "hard_ini.h"
#include "trap_tab.h"

#include "ecc_tsk.h"


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
/*                        LOCAL TYPES                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Local function :                                            */
/***************************************************************/


/***************************************************************/
/* Global function : ECCTask                                   */
/***************************************************************/
void ECCTask(void)
{
    /* IF an ECC error has been reported from the FLASH */
    if (ECSM.ESR.B.FNCE == 1)
    /* THEN */
    {
        /* IF the reported error is real and not erroneous (errata e2071) */
        if (FLASH.MCR.B.EER == 1)
        /* THEN */
        {
            /* Call the DefaultHandlerUser function to wait for a reset */
            user_reset_source = SEU_FLASH;
            DefaultHandlerUser();
        }
        else
        {
        }
        /* END IF */

        /* Reset the EER flag of register FLASH MCR */
        ECSM.ESR.B.FNCE = 1;
    }
    /* ELSE */
    else
    {
        /* Call the DefaultHandlerUser function to wait for a reset */
        user_reset_source = SEU_INTERNAL_SRAM;
        DefaultHandlerUser();
    }
    /* END IF */
}

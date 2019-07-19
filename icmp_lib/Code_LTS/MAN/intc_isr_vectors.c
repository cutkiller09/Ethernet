/***************************************************************/
/* FUNCTION : Contains addresses for all ISR vectors           */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "interface.h"

#include "arinc_int.h"
#include "configuration.h"
#include "can_lb.h"
#include "soft_ini.h"
#include "etpu_lb.h"
#include "hard_def.h"
#include "sci_lb.h"
#include "trap_tab.h"
#include "ad1255.h"
#include "leak_int.h"

#include "intc_isr_vectors.h"


/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
 #pragma section CONST ".External_Interrupt_Handler_Table"
const UNS32 K_TAB_intc_isr_vector_table[] = 
{
    (UNS32)&Software0IRQHandler, (UNS32)&Software1IRQHandler, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,              /* ISRs 00 - 04   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 05 - 09   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 10 - 14   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 15 - 19   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 20 - 24   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 25 - 29   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 30 - 34   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 35 - 39   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 40 - 44   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 45 - 49   */
                                                                                                                                                                                 
    (UNS32)&ExternalIRQHandler, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 50 - 54   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 55 - 59   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 60 - 64   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&ARINCTaskRX1,       (UNS32)&DefaultHandlerUser,                /* ISRs 65 - 69   */
    (UNS32)&ARINCTaskRX2,       (UNS32)&DefaultHandlerUser, (UNS32)&ARINCTaskRX3,       (UNS32)&DefaultHandlerUser, (UNS32)&ARINCTaskRX4,                      /* ISRs 70 - 74   */
    (UNS32)&DefaultHandlerUser, (UNS32)&ARINCTaskRX5,       (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 75 - 79   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 80 - 84   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 85 - 89   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 90 - 94   */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 95 - 99   */

    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 100 - 104 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 105 - 109 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 110 - 114 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 115 - 119 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 120 - 124 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 125 - 129 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 130 - 134 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 135 - 139 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 140 - 144 */
    (UNS32)&DefaultHandlerUser, (UNS32)&SCITask_A,          (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 145 - 149 */
                                                                                                                                                               
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 150 - 154 */
    (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        			   /* ISRs 155 - 159 */
    (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,       				   /* ISRs 160 - 164 */
    (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,       				   /* ISRs 155 - 169 */
    (UNS32)&CANAHandler,        (UNS32)&CANAHandler,        (UNS32)&CANAHandler,		(UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 170 - 174 */
    (UNS32)&DefaultHandlerUser, (UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		               /* ISRs 175 - 179 */
    (UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		               /* ISRs 180 - 184 */
    (UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&CANCHandler,		               /* ISRs 185 - 189 */
    (UNS32)&CANCHandler,		(UNS32)&CANCHandler,		(UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 190 - 194 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 195 - 199 */
                                                                                                                                                               
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 200 - 204 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 205 - 209 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 210 - 214 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 215 - 219 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 220 - 224 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 225 - 229 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 230 - 234 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 235 - 239 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&ETPUAD1255TimerInterruptHandler, (UNS32)&DefaultHandlerUser,                /* ISRs 240 - 244 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 245 - 249 */
                                                                                                                                                               
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&AcquireLeakDataTask, (UNS32)&DefaultHandlerUser,                /* ISRs 250 - 254 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 255 - 259 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 260 - 264 */
	(UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 265 - 269 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 270 - 274 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 275 - 279 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        			   /* ISRs 280 - 284 */
    (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        			   /* ISRs 285 - 289 */
    (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        			   /* ISRs 290 - 294 */
    (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,        (UNS32)&CANBHandler,	                   /* ISRs 295 - 299 */
                                                                                                                                                               
    (UNS32)&CANBHandler,		(UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                /* ISRs 300 - 304 */
    (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser, (UNS32)&DefaultHandlerUser,                                                                        /* ISRs 305 - 307 */
};


/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/

#define BITE_START_ADDRESS             (UNS32)0x00180004
#define BITE_SHORT_ACTION_OFFSET       (UNS32)4

/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/
/*! Function pointer Type */
typedef void (*T_Function_PTR)(void);

/***************************************************************/
/*                                                             */
/*                      LOCAL DATA                             */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Global function : ExternalIRQHandler                        */
/***************************************************************/
void ExternalIRQHandler(void)
{

   if (SIU.EISR.B.EIF6 == 1)
    /* THEN */
    {
        /*IRQ IT */
        
        /* todo Handle if necessary the ethernet IT function*/
        
        /* Clear the flag of the IRQ 6 */
        SIU.EISR.R = 0x00000040;
    }
   else if (SIU.EISR.B.EIF7 == 1)
    /* ELSE IF */
    {
        /* Disable the interrupt for the timeout of the AD1255 acquisition */
        ETPU.CHAN[AD1255_TIMER_ETPU_CHANNEL].CR.B.CIE = (VUNS32)FALSE;
        /* Stop the timer of the AD1255 acquisition */
        SetHSRR(AD1255_TIMER_ETPU_CHANNEL,HSR_TIMER_STOP);
            
        /* Disable IRQ 7 event (24Bit-ADC Data-Ready indication) */
        SIU.IFEER.B.IFEE7 = (VUNS32)FALSE;

        /* Reset 24Bit-ADC (AD1255) failure flag */
        I_BSP_Out.ad1255_acq.ADC_F = FALSE;

        /* Call ReadAD1255 function to make AD1255 input acquisition */
        I_BSP_Out.ad1255_acq.pressure_24_bits = ReadAD1255();
        
        /* Declare the AD1255 acquisition as ended */
        F_AD1255_acquisition_ended = TRUE;
        
        /* Clear the flag of the IRQ 7 */
        SIU.EISR.R = 0x00000080;
    }  
   /* ELSE */
    else
    {
        /* Unexpected interrupt */
        /* Call DefaultHandlerUser function */
        DefaultHandlerUser();
    }
    /* ENDIF */
}

/***************************************************************/
/* Global function : Software0IRQHandler                       */
/***************************************************************/
void Software0IRQHandler(void)
{
    /* Launch the BITE software long action */
    ((T_Function_PTR)((void *)(*(UNS32*)(BITE_START_ADDRESS))))();
}

/***************************************************************/
/* Global function : Software1IRQHandler                       */
/***************************************************************/
void Software1IRQHandler(void)
{
    /* Launch the BITE software short action */
    ((T_Function_PTR)((void *)(*(UNS32*)(BITE_START_ADDRESS) + BITE_SHORT_ACTION_OFFSET)))();
}


/***************************************************************/
/* Global function : ETPUAD1255TimerInterruptHandler           */
/***************************************************************/
void ETPUAD1255TimerInterruptHandler(void)
{
    /* Disable IRQ 7 event (24Bit-ADC Data-Ready indication) */
    SIU.IFEER.B.IFEE7 = (VUNS32)FALSE;
    
    /* Stop the timer */
    SetHSRR(AD1255_TIMER_ETPU_CHANNEL,HSR_TIMER_STOP);
        
    /* Disable the interrupt for the timeout of the AD1255 acquisition */
    ETPU.CHAN[AD1255_TIMER_ETPU_CHANNEL].CR.B.CIE = (VUNS32)FALSE;
    
    /* Clear the interrupt bit status */
    ETPU.CISR_B.R = (UNS32)(1 << CHANNEL_0);
    
    /* Set 24Bit-ADC (AD1255) failure flag */
    I_BSP_Out.ad1255_acq.ADC_F = TRUE;
    
    /* Declare the AD1255 acquisition as ended */
    F_AD1255_acquisition_ended = TRUE;
}


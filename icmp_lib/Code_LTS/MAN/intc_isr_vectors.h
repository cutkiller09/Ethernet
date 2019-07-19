#ifndef __INTC_ISR_VECTORS_H__
#define __INTC_ISR_VECTORS_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL TYPES                           */
/*                                                             */
/***************************************************************/
#define AD1255_TIMER_ETPU_CHANNEL       (UNS32)(ETPU_B_OFFSET + CHANNEL_0)
#define ARINC_TIMER_ETPU_CHANNEL        (UNS32)(ETPU_B_OFFSET + CHANNEL_15)
#define HSR_TIMER_STOP                  (UNS8)2

extern BOOLEAN F_AD1255_acquisition_ended;

/***************************************************************/
/*                                                             */
/*                    GLOBAL CONSTANTS                         */
/*                                                             */
/***************************************************************/
extern const UNS32 K_TAB_intc_isr_vector_table[];


/***************************************************************/
/*                                                             */
/*                       GLOBAL DATA                           */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                    GLOBAL FUNCTIONS                         */
/*                                                             */
/***************************************************************/
extern void ETPUAD1255TimerInterruptHandler(void);
extern void ExternalIRQHandler(void);
extern void EnableSMFCInterrupt(void);
extern void DisableSMFCInterrupt(void);
extern void InitializeIntc_isr_vectors(void);

#pragma section CODE ".exception_handlers_user_mode"
extern void Software0IRQHandler(void);
extern void Software1IRQHandler(void);
#pragma section CODE ".text"
#endif
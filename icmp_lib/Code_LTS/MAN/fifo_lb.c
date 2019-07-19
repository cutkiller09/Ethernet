/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "cpu_lb.h"

#include "fifo_lb.h"


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
/*                         LOCAL TYPES                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/* Global function : CreateQueue                               */
/***************************************************************/
void CreateQueue(T_FIFOQueue *a_queue_PTR)
{
   UNS16 i;

   /************************************/
   /* reset the FirstEmptyElement data */
   /* reset the FirstInElement data    */
   /* reset all elements of fifo       */
   /************************************/
   a_queue_PTR->FirstEmptyElement = 0;
   a_queue_PTR->FirstInElement = 0;
   for (i = 0; i < (UNS16)MAX_ELEM_FIFO_ARINC; i++)
   {
      a_queue_PTR->TAB_Element[i] = 0;
   }
}


/***************************************************************/
/* Global function : PushElement                               */
/***************************************************************/
void PushElement(UNS32 an_element,
                     T_FIFOQueue *a_queue_PTR)
{

   /*************************************************************/
   /* Call MaskInterruptINTC function, to disable the interrupt */
   /* IF the queue is not full                                  */
   /* THEN                                                      */
   /*    store the element in the queue                         */
   /*    increase the first empty element number                */
   /* ELSE                                                      */
   /* END IF                                                    */
   /* Call UnmaskInterruptINTC, to enable the interrupt         */
   /*************************************************************/ 
   MaskInterruptINTC();

   if (((UNS16)(a_queue_PTR->FirstEmptyElement + 1) % MAX_ELEM_FIFO_ARINC) !=
       a_queue_PTR->FirstInElement)
   {
      a_queue_PTR->TAB_Element[a_queue_PTR->FirstEmptyElement] = an_element;
      a_queue_PTR->FirstEmptyElement = (UNS16)((UNS16)(a_queue_PTR->FirstEmptyElement + 1)
                                       % MAX_ELEM_FIFO_ARINC);
   }
   else
   {
   }
   UnmaskInterruptINTC();
}

/***************************************************************/
/* Global function : PopUpElement                              */
/***************************************************************/
BOOLEAN PopUpElement(T_FIFOQueue *a_queue_PTR,
                          UNS32 *an_element_PTR)
{
   BOOLEAN F_queue_not_empty;

   /*************************************************************/
   /* Call MaskInterruptINTC function, to disable the interrupt */
   /* Disable the interrupt                                     */
   /* IF queue is not empty                                     */
   /* THEN                                                      */
   /*    update the parameter                                   */
   /*    increase the first in element number                   */
   /*    set return flag to true                                */
   /* END IF                                                    */
   /* Call UnmaskInterruptINTC, to enable the interrupt         */
   /* Return the return flag                                    */
   /*************************************************************/
   F_queue_not_empty = FALSE;
   MaskInterruptINTC();
   if (a_queue_PTR->FirstEmptyElement != a_queue_PTR->FirstInElement)
   {
      *an_element_PTR = a_queue_PTR->TAB_Element[a_queue_PTR->FirstInElement];
      a_queue_PTR->FirstInElement = (UNS16)((UNS16)(a_queue_PTR->FirstInElement + 1) 
                                            % (UNS16)MAX_ELEM_FIFO_ARINC);
      F_queue_not_empty = TRUE;
   }
   else
   {
   }
   UnmaskInterruptINTC();
   return(F_queue_not_empty);
}

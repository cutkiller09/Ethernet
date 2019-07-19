#ifndef __ARINC_INI_H__
#define __ARINC_INI_H__
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
    RX1   = 0,
    RX2   = 1,
    RX3   = 2,
    RX4   = 3,
    RX5   = 4,
    ARINC_RX_NUMBER = 5
}
T_ARINC_RX_INDEX;

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
extern T_FIFOQueue TAB_arinc_fifo_rx[ARINC_RX_NB];

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void Initializearinc_int(void);
extern void ReportARINCMessages(void);
extern void ARINCTaskRX1(void);
extern void ARINCTaskRX2(void);
extern void ARINCTaskRX3(void);
extern void ARINCTaskRX4(void);
extern void ARINCTaskRX5(void);
extern void ARINCActiveInterrupt(void);
extern void GetARINCData(void);
extern BOOLEAN MonitorARINCChannelsParameters(void);
#endif
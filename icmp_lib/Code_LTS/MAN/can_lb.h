#ifndef __CAN_LB_H__
#define __CAN_LB_H__
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
extern UNS8 TAB_CANA_list_of_tx_MB[CAN_MB_NUMBER];
extern UNS8 TAB_CANB_list_of_tx_MB[CAN_MB_NUMBER];
extern UNS8 TAB_CANC_list_of_tx_MB[CAN_MB_NUMBER];


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeAllCAN(void);
extern void InitializeCan_Lb(void);
extern void ReportAllCANMessages(void);
extern void GetCANData(void);
extern void CANAHandler(void);
extern void CANBHandler(void);
extern void CANCHandler(void);
#endif
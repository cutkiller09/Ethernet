#ifndef __ETPU_ARINC_LB_H__
#define __ETPU_ARINC_LB_H__
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
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern UNS32 EtpuInitializeA429Rx(T_Etpu_fnc *a_RX_function_PTR, UNS32 a_baudrate, UNS8 a_RX_buffer_size);
extern void EtpuGetAllNewMessages (UNS32 a_parameter_start, UNS8 a_RX_buffer_size, T_FIFOQueue *a_queue_PTR);
extern UNS32 EtpuInitializeA429Tx(T_Etpu_fnc *a_TX_function_PTR, UNS32 a_baudrate, UNS8 a_TX_buffer_size);
extern void EtpuWriteNewMessage(UNS32 a_parameter_start, UNS32 a_message, UNS8 a_TX_buffer_size);
extern void EtpuSendAllNewMessages(T_Etpu_fnc *a_TX_function_PTR, UNS8 a_TX_buffer_size);
extern void DisableInterruptOnARINCChannel(UNS8 a_channel);
extern void EnableInterruptOnARINCChannel(UNS8 a_channel);
extern BOOLEAN EtpuMonitorA429RxParameters(T_Etpu_fnc * a_RX_function_PTR, UNS32 a_baudrate, UNS8 a_RX_buffer_size);
extern BOOLEAN EtpuMonitorA429TxParameters(T_Etpu_fnc * a_TX_function_PTR, UNS32 a_baudrate, UNS8 a_TX_buffer_size);
#endif
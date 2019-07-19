/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: Service_BatteryManager.h 
 * $Author: Slo 
 * $Date: 2015/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  Service_BatteryManager.h 
  * \brief Fichier Header du Service BatteryManager
*/
/*============================================================================*/
/* COPYRIGHT (C) ROBOSOFT 2015	                                              */ 
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/  

#pragma once

/* Includes 							              */
/*============================================================================*/  
#include "Library_LibBatMngBmv700.h"

/* Constants and types 							      */
/*============================================================================*/

typedef struct
{
	uint32 u32_timestamp_sec;		/* Resolution: 1s (time from 1/1/1970 0:0:0 UTC) */
	uint32 u32_timestamp_ns;		/* Resolution: 1ns (number of nano-seconds into second */

	ts_Bmv700_Data s_data ;
} ts_SrvBat_Data ;

/**
 * @enum te_SrvBat_error
 * @brief define the Battery error
 */
typedef enum
{
	E_SRVBAT_ERR_NO_ERROR=0,
	E_SRVBAT_ERR_NOT_INITIALIZED,
	E_SRVBAT_ERR_NOT_CONFIGURED,
	E_SRVBAT_ERR_SERIAL_DRIVER,
	E_SRVBAT_ERR_CHECKSUM
} te_SrvBat_error ;

/* Exported Variables 						              */
/*============================================================================*/

/* Exported functions prototypes 					      */
/*============================================================================*/    
 
void SrvBat_Initialize(void) ;
Std_ReturnType SrvBat_Manage(void) ;
Std_ReturnType SrvBat_Configure( const ts_libBatMngBmv700_configuration * const ps_configuration );
Std_ReturnType SrvBat_GetData(ts_SrvBat_Data * const  ps_Bat_Data);
Std_ReturnType SrvBat_Close(void);
Std_ReturnType SrvBat_Get_Error(te_SrvBat_error * const pe_SrvBat_error);

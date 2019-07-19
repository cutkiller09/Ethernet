/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: Library_LibBatMngBmv700.h 
 * $Author: MDega 
 * $Date: 2015/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  Library_LibBatMngBmv700.h 
  * \brief Fichier Header du Service LibBatMngBmv700
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

/* Includes 								      */
/*============================================================================*/  
#include "Driver_SerialDriver.h"

/* Constants and types 							      */
/*============================================================================*/

typedef struct
{
	serialdrv_cfg_type s_serial_configuration ;
} ts_libBatMngBmv700_configuration ;

/**
 * @enum  te_Bmv700_Pid_status
 * @brief define the Bmv700 product identification
 */
typedef enum {
	E_PID_BMV_700=0x203,
	E_PID_BMV_702=0x204,
	E_PID_BMV_700H=0x205,
	E_PID_MPPT_7015=0x300,
	E_PID_MPPT_7515=0xA042,
	E_PID_MPPT_10015=0xA043,
	E_PID_MPPT_10030=0xA044,
	E_PID_MPPT_15035=0xA041,
	E_PID_MPPT_7550=0xA040,
	E_PID_MPPT_10050=0xA045
}te_Bmv700_Pid_status;

typedef struct
{
	sint32 s32_Voltage; 					/* in mV	*/
	sint32 s32_AuxVoltage;					/* in mV	*/
	sint32 s32_MidPointVoltage;				/* in mV	*/
	sint32 s32_MidPointDeviation;			/* per mill */
	sint32 s32_BatteryCurrent;				/* in mA 	*/
	sint32 s32_BatteryTemperature;		    /* in °C 	*/
	sint32 s32_InstantaneousPower;		    /* in W 	*/
	sint32 s32_ConsumedAmpHours;		    /* in mAH 	*/
	sint32 s32_StateOfCharge;		    	/* per mill 	*/
	sint32 s32_TimeToGo;		   			/* in minutes	*/
	uint8  au8_AlarmState[4];		   	    /* OFF / ON  	*/
	uint8  au8_RelayState[4];		    	/* OFF / ON  	*/
	sint32 s32_AlarmReason;						/*  	*/
	sint32 s32_DeepestDischargeDepth;		/* in mAh 	*/
	sint32 s32_LastDischargeDepth;		    /* in mAh 	*/
	sint32 s32_AvgDischargeDepth;		    /* in mAh 	*/
	sint32 s32_NumberOfChargeCycles;		/* in °C 	*/
	sint32 s32_NumberOfFullDischarges;		/* in °C 	*/
	sint32 s32_CumulativeAmpHoursDrawn;		/* in mAh 	*/
	sint32 s32_MiniMainVoltage;
	sint32 s32_MaxiMainVoltage;
	sint32 s32_NbSecSinceLastFullCharge;
	sint32 s32_NbAutoSynchro;
	sint32 s32_NbLowMainVoltageAlarms;
	sint32 s32_NbHighMainVoltageAlarms;
	sint32 s32_MiniAuxiVoltage;				/* in mV	*/
	sint32 s32_MaxiAuxiVoltage;				/* in mV	*/
	sint32 s32_DischargedEnergyAmount;
	sint32 s32_ChargedEnergyAmount;
	sint32 s32_ModelDescription;
	sint32 s32_FirmwareVersion;
	te_Bmv700_Pid_status t_ProductId;
}ts_Bmv700_Data;

/**
 * @enum te_LibLidarLms151_error
 * @brief define the LMS151 error
 */
typedef enum
{
	E_BMV700_ERR_NO_ERROR=0,
	E_BMV700_ERR_NOT_INITIALIZED,
	E_BMV700_ERR_NOT_CONFIGURED,
	E_BMV700_ERR_SERIAL_DRIVER,
	E_BMV700_ERR_CHECKSUM
} te_Bmv700_error ;

/* Exported Variables 							      */
/*============================================================================*/

/* Exported functions prototypes 					      */
/*============================================================================*/    
 
void LibBatMngBmv700_Initialize(void);
Std_ReturnType LibBatMngBmv700_Open(void);
Std_ReturnType LibBatMngBmv700_Close(void);
Std_ReturnType LibBatMngBmv700_Configure( const ts_libBatMngBmv700_configuration * const ps_configuration );
Std_ReturnType LibBatMngBmv700_Manage(void);
Std_ReturnType LibBatMngBmv700_Get_Data(ts_Bmv700_Data * const ps_Bmv700_Data, bool * const pb_IsNewData);
Std_ReturnType LibBatMngBmv700_Get_Error(te_Bmv700_error * const pe_Bmv700_error);


/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: TI_Service_BatteryManager.c 
 * $Author: Slo 
 * $Date: 2015/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  TI_Service_BatteryManager.c 
  * \brief Fichier Source file of Integration Test BatteryManager
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

/* Includes 								      */
/*============================================================================*/ 
#include "types.h"
#include "Library_StdLib.h"
#include "Service_BatteryManager.h" 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Constants and types  						      */
/*============================================================================*/  
#define K_TV_SRVBATMNG_PERIOD_MS 100

/* Variables 								      */
/*============================================================================*/ 
ts_SrvBat_Data s_Data;

/* Private functions prototypes 					      */
/*============================================================================*/ 

/* Inline functions 							      */
/*============================================================================*/

/* Private functions 							      */
/*============================================================================*/

/**
 * \fn  Std_ReturnType main(void)  
 * \brief this function is the entry point of the integration test
 *
 * \param  
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
int main(void)
{
    /*! Declaration */     
    Std_ReturnType t_main_Status; 
	ts_libBatMngBmv700_configuration s_configuration ;
	uint16 u16_cnt ;
	uint32 u32_time_sec ;
	uint32 u32_time_ns ;

    /*! Initialization */ 
    t_main_Status = E_OK;
	strcpy( s_configuration.s_serial_configuration.sz_serialport_name , "/dev/ttyS1" ) ;
	s_configuration.s_serial_configuration.u32_baudrate = 19200 ;
	s_configuration.s_serial_configuration.u8_bitsize = 8 ;
	s_configuration.s_serial_configuration.t_parity_mode = E_DRVSERIAL_NO_PARITY ;
	s_configuration.s_serial_configuration.b_stopbitena = K_TRUE ;
	u32_time_sec = 0 ;
	u32_time_ns = 0 ;
	/* Function Body */

	/* Initialize Modules */
	t_main_Status |= DrvSerial_Initialize() ;
	SrvBat_Initialize() ;
	if (E_OK == t_main_Status)
	{
		printf("SrvBat_Initialize well Initialized %i \n",t_main_Status);
	}
	else
	{
		printf("SrvBat_Initialize bad Initialized %i \n",t_main_Status);
	}

	t_main_Status |= SrvBat_Configure(&s_configuration) ;
	if (E_OK == t_main_Status)
	{
		printf("SrvBat_Configure well called %i \n",t_main_Status);
	}
	else
	{
		printf("SrvBat_Configure bad called %i \n",t_main_Status);
	}

	u16_cnt = 0 ;
	while( 10000 > u16_cnt )
	{
		usleep( K_TV_SRVBATMNG_PERIOD_MS*1000 ) ;
		u16_cnt = u16_cnt + K_TV_SRVBATMNG_PERIOD_MS ;

		t_main_Status |= SrvBat_Manage() ;
		if (E_OK == t_main_Status)
		{
			printf("SrvBat_Manage well called %i \n",t_main_Status);
		}
		else
		{
			printf("SrvBat_Manage bad called %i \n",t_main_Status);
		}

		t_main_Status |= SrvBat_GetData(&s_Data) ;
		if (E_OK == t_main_Status)
		{
			if( (u32_time_sec != s_Data.u32_timestamp_sec) || (u32_time_ns != s_Data.u32_timestamp_ns) )
			{
				printf( "\n" );
				printf("SrvBat_GetData well called %i \n",t_main_Status);
				printf("s_Bmv700_Data.s32_Voltage : %d \n",s_Data.s_data.s32_Voltage);
				printf("s_Bmv700_Data.s32_AuxVoltage : %d \n",s_Data.s_data.s32_AuxVoltage);
				printf("s_Bmv700_Data.s32_MidPointVoltage : %d \n",s_Data.s_data.s32_MidPointVoltage);
				printf("s_Bmv700_Data.s32_MidPointDeviation : %d \n",s_Data.s_data.s32_MidPointDeviation);
				printf("s_Bmv700_Data.s32_BatteryCurrent : %d \n",s_Data.s_data.s32_BatteryCurrent);
				printf("s_Bmv700_Data.s32_BatteryTemperature : %d \n",s_Data.s_data.s32_BatteryTemperature);
				printf("s_Bmv700_Data.s32_InstantaneousPower : %d \n",s_Data.s_data.s32_InstantaneousPower);
				printf("s_Bmv700_Data.s32_ConsumedAmpHours : %d \n",s_Data.s_data.s32_ConsumedAmpHours);
				printf("s_Bmv700_Data.s32_StateOfCharge : %d \n",s_Data.s_data.s32_StateOfCharge);
				printf("s_Bmv700_Data.s32_TimeToGo : %d \n",s_Data.s_data.s32_TimeToGo);
				printf("s_Bmv700_Data.au8_AlarmState : %s \n",s_Data.s_data.au8_AlarmState);
				printf("s_Bmv700_Data.au8_RelayState : %s \n",s_Data.s_data.au8_RelayState);
				printf("s_Bmv700_Data.s32_AlarmReason : %d \n",s_Data.s_data.s32_AlarmReason);
				printf("s_Bmv700_Data.s32_DeepestDischargeDepth : %d \n",s_Data.s_data.s32_DeepestDischargeDepth);
				printf("s_Bmv700_Data.s32_LastDischargeDepth : %d \n",s_Data.s_data.s32_LastDischargeDepth);
				printf("s_Bmv700_Data.s32_AvgDischargeDepth : %d \n",s_Data.s_data.s32_AvgDischargeDepth);
				printf("s_Bmv700_Data.s32_NumberOfChargeCycles : %d \n",s_Data.s_data.s32_NumberOfChargeCycles);
				printf("s_Bmv700_Data.s32_NumberOfFullDischarges : %d \n",s_Data.s_data.s32_NumberOfFullDischarges);
				printf("s_Bmv700_Data.s32_CumulativeAmpHoursDrawn : %d \n",s_Data.s_data.s32_CumulativeAmpHoursDrawn);
				printf("s_Bmv700_Data.s32_MiniMainVoltage : %d \n",s_Data.s_data.s32_MiniMainVoltage);
				printf("s_Bmv700_Data.s32_MaxiMainVoltage : %d \n",s_Data.s_data.s32_MaxiMainVoltage);
				printf("s_Bmv700_Data.s32_NbSecSinceLastFullCharge : %d \n",s_Data.s_data.s32_NbSecSinceLastFullCharge);
				printf("s_Bmv700_Data.s32_NbAutoSynchro : %d \n",s_Data.s_data.s32_NbAutoSynchro);
				printf("s_Bmv700_Data.s32_NbLowMainVoltageAlarms : %d \n",s_Data.s_data.s32_NbLowMainVoltageAlarms);
				printf("s_Bmv700_Data.s32_NbHighMainVoltageAlarms : %d \n",s_Data.s_data.s32_NbHighMainVoltageAlarms);
				printf("s_Bmv700_Data.s32_MiniAuxiVoltage : %d \n",s_Data.s_data.s32_MiniAuxiVoltage);
				printf("s_Bmv700_Data.s32_MaxiAuxiVoltage : %d \n",s_Data.s_data.s32_MaxiAuxiVoltage);
				printf("s_Bmv700_Data.s32_DischargedEnergyAmount : %d \n",s_Data.s_data.s32_DischargedEnergyAmount);
				printf("s_Bmv700_Data.s32_ChargedEnergyAmount : %d \n",s_Data.s_data.s32_ChargedEnergyAmount);
				printf("s_Bmv700_Data.s32_ModelDescription : %d \n",s_Data.s_data.s32_ModelDescription);
				printf("s_Bmv700_Data.s32_FirmwareVersion : %d \n",s_Data.s_data.s32_FirmwareVersion);
				printf("s_Bmv700_Data.t_ProductId : %d \n",s_Data.s_data.t_ProductId);

				u32_time_sec = s_Data.u32_timestamp_sec ;
				u32_time_ns = s_Data.u32_timestamp_ns ;
			}
		}
		else
		{
			printf("SrvBat_Configure bad called %i \n",t_main_Status);
		}
	}

	t_main_Status |= SrvBat_Close() ;
	if (E_OK == t_main_Status)
	{
		printf("SrvBat_Close well called %i \n",t_main_Status);
	}
	else
	{
		printf("SrvBat_Close bad called %i \n",t_main_Status);
	}


    /*! return code */ 
    return(t_main_Status);
} 

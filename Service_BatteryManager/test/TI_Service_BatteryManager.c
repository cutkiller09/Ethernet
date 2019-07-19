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
#include "Library_LibBatMngBmv700.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Constants and types  						      */
/*============================================================================*/  
#define MACRO_START_UT(u16_num_case, sz_title_case) printf( "\nCase %d : \\************ %s ************\\ \n" , u16_num_case , sz_title_case ) ; fflush( stdout ) ;
#define MACRO_ASSERT_UT(u16_num_case , u16_error_count , u16_num_error_expected ) \
		printf( "Case %d : tested_value = %d (expected : %d) : %s\n" , \
				u16_num_case , \
				u16_error_count , \
				u16_num_error_expected , \
				(u16_num_error_expected==u16_error_count)?"SUCCESS":"FAILED" ) ; fflush( stdout ) ;
   
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
    uint32 u32_i;
    uint16 u16_j;
	ts_libBatMngBmv700_configuration s_configuration ;

    /*! Initialization */ 
    t_main_Status = E_OK;
    u16_j=0;
	strcpy( s_configuration.s_serial_configuration.sz_serialport_name , "/dev/ttyUSB0" ) ;
	s_configuration.s_serial_configuration.u32_baudrate = 19200 ;
	s_configuration.s_serial_configuration.u8_bitsize = 8 ;
	s_configuration.s_serial_configuration.t_parity_mode = E_DRVSERIAL_NO_PARITY ;
	s_configuration.s_serial_configuration.b_stopbitena = K_TRUE ;

	/* Function Body */

	/* Case 0 : Module not initialized */
	MACRO_START_UT( u16_j , "Module not initialized" )
	t_main_Status = SrvBat_Configure( &s_configuration ) ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = SrvBat_Manage() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = SrvBat_GetData(&s_Data);
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = SrvBat_Close();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )


	/* Case 1 : Module not configured */
	u16_j++;
	MACRO_START_UT( u16_j , "Module not configured" )
	SrvBat_Initialize() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
	t_main_Status = SrvBat_Manage() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = SrvBat_GetData(&s_Data);
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = SrvBat_Close();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )

	/* Case 3 : Nominal Mode Initialize Modules */
	u16_j++;
	MACRO_START_UT( u16_j , "Nominal Test" )
	SrvBat_Initialize() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
	t_main_Status = SrvBat_Configure(&s_configuration) ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )

	for (u32_i=0;u32_i<100;u32_i++)
	{

		usleep( 100*1000 ) ; // Wait 100ms
		/* Manage */
		t_main_Status = SrvBat_Manage() ;
		MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )

		/* Get Data */
		t_main_Status = SrvBat_GetData(&s_Data) ;
		MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
		if (E_OK == t_main_Status)
		{
			printf("SrvBat_GetData well called %i \n",t_main_Status);
			printf("s_Bmv700_Data.s32_Voltage : %d (V)\n",s_Data.s_data.s32_Voltage);
			printf("s_Bmv700_Data.s32_AuxVoltage : %d (VS)\n",s_Data.s_data.s32_AuxVoltage);
			printf("s_Bmv700_Data.s32_MidPointVoltage : %d (VM)\n",s_Data.s_data.s32_MidPointVoltage);
			printf("s_Bmv700_Data.s32_MidPointDeviation : %d (DM)\n",s_Data.s_data.s32_MidPointDeviation);
			printf("s_Bmv700_Data.s32_BatteryCurrent : %d (I)\n",s_Data.s_data.s32_BatteryCurrent);
			printf("s_Bmv700_Data.s32_BatteryTemperature : %d (T)\n",s_Data.s_data.s32_BatteryTemperature);
			printf("s_Bmv700_Data.s32_InstantaneousPower : %d (P)\n",s_Data.s_data.s32_InstantaneousPower);
			printf("s_Bmv700_Data.s32_ConsumedAmpHours : %d (CE)\n",s_Data.s_data.s32_ConsumedAmpHours);
			printf("s_Bmv700_Data.s32_StateOfCharge : %d (SOC)\n",s_Data.s_data.s32_StateOfCharge);
			printf("s_Bmv700_Data.s32_TimeToGo : %d (TTG)\n",s_Data.s_data.s32_TimeToGo);
			printf("s_Bmv700_Data.au8_AlarmState : %s (Alarm)\n",s_Data.s_data.au8_AlarmState);
			printf("s_Bmv700_Data.au8_RelayState : %s (Relay)\n",s_Data.s_data.au8_RelayState);
			printf("s_Bmv700_Data.s32_AlarmReason : %d (AR)\n",s_Data.s_data.s32_AlarmReason);
			printf("s_Bmv700_Data.s32_DeepestDischargeDepth : %d (H1)\n",s_Data.s_data.s32_DeepestDischargeDepth);
			printf("s_Bmv700_Data.s32_LastDischargeDepth : %d (H2)\n",s_Data.s_data.s32_LastDischargeDepth);
			printf("s_Bmv700_Data.s32_AvgDischargeDepth : %d (H3)\n",s_Data.s_data.s32_AvgDischargeDepth);
			printf("s_Bmv700_Data.s32_NumberOfChargeCycles : %d (H4)\n",s_Data.s_data.s32_NumberOfChargeCycles);
			printf("s_Bmv700_Data.s32_NumberOfFullDischarges : %d (H5)\n",s_Data.s_data.s32_NumberOfFullDischarges);
			printf("s_Bmv700_Data.s32_CumulativeAmpHoursDrawn : %d (H6)\n",s_Data.s_data.s32_CumulativeAmpHoursDrawn);
			printf("s_Bmv700_Data.s32_MiniMainVoltage : %d (H7)\n",s_Data.s_data.s32_MiniMainVoltage);
			printf("s_Bmv700_Data.s32_MaxiMainVoltage : %d (H8)\n",s_Data.s_data.s32_MaxiMainVoltage);
			printf("s_Bmv700_Data.s32_NbSecSinceLastFullCharge : %d (H9)\n",s_Data.s_data.s32_NbSecSinceLastFullCharge);
			printf("s_Bmv700_Data.s32_NbAutoSynchro : %d (H10)\n",s_Data.s_data.s32_NbAutoSynchro);
			printf("s_Bmv700_Data.s32_NbLowMainVoltageAlarms : %d (H11)\n",s_Data.s_data.s32_NbLowMainVoltageAlarms);
			printf("s_Bmv700_Data.s32_NbHighMainVoltageAlarms : %d (H12)\n",s_Data.s_data.s32_NbHighMainVoltageAlarms);
			printf("s_Bmv700_Data.s32_MiniAuxiVoltage : %d (H15)\n",s_Data.s_data.s32_MiniAuxiVoltage);
			printf("s_Bmv700_Data.s32_MaxiAuxiVoltage : %d (H16)\n",s_Data.s_data.s32_MaxiAuxiVoltage);
			printf("s_Bmv700_Data.s32_DischargedEnergyAmount : %d (H17)\n",s_Data.s_data.s32_DischargedEnergyAmount);
			printf("s_Bmv700_Data.s32_ChargedEnergyAmount : %d (H18)\n",s_Data.s_data.s32_ChargedEnergyAmount);
			printf("s_Bmv700_Data.s32_ModelDescription : %d (BMV)\n",s_Data.s_data.s32_ModelDescription);
			printf("s_Bmv700_Data.s32_FirmwareVersion : %d (FW)\n",s_Data.s_data.s32_FirmwareVersion);
			printf("s_Bmv700_Data.t_ProductId : 0x%x (PID)\n",s_Data.s_data.t_ProductId);
		}
		else
		{
			printf("SrvBat_Configure bad called %i \n",t_main_Status);
		}
	}

	/* close */
	t_main_Status = SrvBat_Close() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )


    /*! return code */ 
    return(t_main_Status);
} 

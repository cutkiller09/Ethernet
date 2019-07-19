/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: TI_Library_LibBatMngBmv700.c 
 * $Author: MDega 
 * $Date: 2015/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  TI_Library_LibBatMngBmv700.c 
  * \brief Fichier Source file of Integration Test LibBatMngBmv700
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
#include "Driver_SerialDriver.h"
#include "Library_LibBatMngBmv700.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
#define K_NB_LOOP 10000
   
/* Variables 								      */
/*============================================================================*/ 

static 	ts_Bmv700_Data s_Bmv700_Data;
static bool b_IsNewData;

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
	/* Declaration */
	Std_ReturnType t_main_Status;
	ts_libBatMngBmv700_configuration s_configuration ;
	uint32 u32_i;
	uint32 u32_cptwell;
	uint32 u32_cptbad;
	uint16 u16_j;

	/* Initialization */
	t_main_Status = E_OK ;
	u32_cptwell=0;
	u32_cptbad=0;
	u16_j=0;
	strcpy( s_configuration.s_serial_configuration.sz_serialport_name , "/dev/ttyUSB0" ) ;
	s_configuration.s_serial_configuration.u32_baudrate = 19200 ;
	s_configuration.s_serial_configuration.u8_bitsize = 8 ;
	s_configuration.s_serial_configuration.t_parity_mode = E_DRVSERIAL_NO_PARITY ;
	s_configuration.s_serial_configuration.b_stopbitena = K_TRUE ;

	/* Function Body */
	t_main_Status |= DrvSerial_Initialize() ;

	/* Case 0 : Module not initialized */
	MACRO_START_UT( u16_j , "Module not initialized" )
	t_main_Status = LibBatMngBmv700_Configure( &s_configuration ) ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Open() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Manage();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Get_Data(&s_Bmv700_Data, &b_IsNewData);
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Close();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )


	/* Case 1 : Module not configured */
	u16_j++;
	MACRO_START_UT( u16_j , "Module not configured" )
	LibBatMngBmv700_Initialize() ;
	t_main_Status = LibBatMngBmv700_Open() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Manage();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Get_Data(&s_Bmv700_Data, &b_IsNewData);
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )
	t_main_Status = LibBatMngBmv700_Close();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK )

	/* Case 2 : Nominal Mode Initialize Modules */
	u16_j++;
	MACRO_START_UT( u16_j , "Nominal Test" )
	LibBatMngBmv700_Initialize() ;
	t_main_Status = LibBatMngBmv700_Configure( &s_configuration ) ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
	t_main_Status = LibBatMngBmv700_Open() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
	t_main_Status = LibBatMngBmv700_Manage();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK ) // First Checksum modified to test Checksum Error (toto value added in BMV700.dat)
	t_main_Status = LibBatMngBmv700_Get_Data(&s_Bmv700_Data, &b_IsNewData);
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_NOT_OK ) // First Checksum modified to test Checksum Error (toto value added in BMV700.dat)

	for (u32_i=1;u32_i<K_NB_LOOP;u32_i++)
	{

		usleep( 100*1000 ) ; // Wait 100ms
		if(u32_i>70)
		{
			t_main_Status = LibBatMngBmv700_Manage(); // Bad checksum compute when u32_i value is 70
			MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
		}
		t_main_Status = LibBatMngBmv700_Manage();
		MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )
		if (E_OK ==t_main_Status )
		{
			printf("LibBatMngBmv700_Manage well called %i time \n",u32_i);
			u32_cptwell++;
		}
		else
		{
			printf("LibBatMngBmv700_Manage bad called %i time \n",u32_i);
			u32_cptbad++;
		}

		t_main_Status = LibBatMngBmv700_Get_Data(&s_Bmv700_Data, &b_IsNewData);
	}

	printf("LibBatMngBmv700_Manage well called %i per cents \n",(u32_cptwell+1));
	printf("LibBatMngBmv700_Manage bad called %i per cents \n",u32_cptbad);

	t_main_Status = LibBatMngBmv700_Close();
	MACRO_ASSERT_UT( u16_j , t_main_Status , E_OK )

    /* return code */ 
    return(t_main_Status);
} 

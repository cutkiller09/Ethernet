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
#define K_NB_LOOP 100000
   
/* Variables 								      */
/*============================================================================*/ 

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

	/* Initialization */
	t_main_Status = E_OK ;
	u32_cptwell=0;
	u32_cptbad=0;
	strcpy( s_configuration.s_serial_configuration.sz_serialport_name , "/dev/ttyS1" ) ;
	s_configuration.s_serial_configuration.u32_baudrate = 19200 ;
	s_configuration.s_serial_configuration.u8_bitsize = 8 ;
	s_configuration.s_serial_configuration.t_parity_mode = E_DRVSERIAL_NO_PARITY ;
	s_configuration.s_serial_configuration.b_stopbitena = K_TRUE ;

	/* Function Body */

	/* Initialize Modules */
	t_main_Status |= DrvSerial_Initialize() ;
	LibBatMngBmv700_Initialize() ;

	t_main_Status |= LibBatMngBmv700_Configure( &s_configuration ) ;
	if (E_OK ==t_main_Status )
	{
		printf("LibBatMngBmv700_Configure well configured %i \n",t_main_Status);
	}
	else
	{
		printf("LibBatMngBmv700_Configure bad configured %i \n",t_main_Status);
	}


	t_main_Status |= LibBatMngBmv700_Open() ;
	if (E_OK == t_main_Status)
	{
		printf("LibBatMngBmv700_Open well Initialized %i \n",t_main_Status);
	}
	else
	{
		printf("LibBatMngBmv700_Open bad Initialized %i \n",t_main_Status);
	}

	for (u32_i=0;u32_i<K_NB_LOOP;u32_i++)
	{

		usleep( 100*1000 ) ; // Wait 100ms
		t_main_Status = LibBatMngBmv700_Manage();
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
	}

	printf("LibBatMngBmv700_Manage well called %i per cents \n",u32_cptwell);
	printf("LibBatMngBmv700_Manage bad called %i per cents \n",u32_cptbad);

	t_main_Status |= LibBatMngBmv700_Close();
	if (E_OK ==t_main_Status )
	{
		printf("LibBatMngBmv700_Close well called %i \n",t_main_Status);
	}
	else
	{
		printf("LibBatMngBmv700_Close bad called %i \n",t_main_Status);
	}

    /* return code */ 
    return(t_main_Status);
} 

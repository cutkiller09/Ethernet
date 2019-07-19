/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: Service_BatteryManager.c 
 * $Author: Slo 
 * $Date: 2015/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  Service_BatteryManager.c 
  * \brief Fichier Source du Service BatteryManager
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
#include "Library_LibBatMngBmv700.h"
#include "Service_BatteryManager.h" 
#include <string.h>

/* Constants and types  						      */
/*============================================================================*/ 
   
/* Variables 								      */
/*============================================================================*/ 
static Std_ReturnType gt_InitBatteryManager_Status=E_NOT_OK; /* Global Initialization variable */
static Std_ReturnType gt_ConfBatteryManager_Status=E_NOT_OK; /* Global Initialization variable */
static ts_Bmv700_Data gs_Bmv700_NewData;
static ts_SrvBat_Data gs_Data;
static te_SrvBat_error ge_SrvBat_error=E_SRVBAT_ERR_NOT_INITIALIZED;

/* Private functions prototypes 					      */
/*============================================================================*/ 
static void LibraryErrorManage(void);

/* Inline functions 							      */
/*============================================================================*/

/* Private functions 							      */
/*============================================================================*/

/* Public functions 							      */
/*============================================================================*/

/**
 * \fn  Std_ReturnType SrvBat_Initialize(void) 
 * \brief this function will Initialize module and battery manager library
 *
 * \param  none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
void SrvBat_Initialize(void)
{
    /*! Declaration */

    /*! Initialization */

    /*! Function Body */
    LibBatMngBmv700_Initialize();
	gt_InitBatteryManager_Status=E_OK;
	ge_SrvBat_error=E_SRVBAT_ERR_NO_ERROR;

    /*! return code */
}

/**
 * \fn  Std_ReturnType SrvBat_Configure( const ts_SrvBat_configuration * const ps_configuration )
 * \brief this function will configure and open battery manager library
 *
 * \param  <const ts_libBatMngBmv700_configuration * const ps_configuration> { library manager configuration }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType SrvBat_Configure( const ts_libBatMngBmv700_configuration * const ps_configuration )
{
    /* Declaration */
    Std_ReturnType t_Configure_Status ;

    /* Initialization */
    t_Configure_Status = E_OK ;

	/* Function Body */

	if( (E_NOT_OK != gt_InitBatteryManager_Status) &&
		(NULL_PTR != ps_configuration) )
	{
		t_Configure_Status |= LibBatMngBmv700_Configure( ps_configuration ) ;
		t_Configure_Status |= LibBatMngBmv700_Open() ;
    	LibraryErrorManage();
	}
	else
	{
	    t_Configure_Status = E_NOT_OK ;
	}

	gt_ConfBatteryManager_Status=t_Configure_Status;

    /*! return code */
    return(t_Configure_Status);
}

/**
 * \fn  Std_ReturnType SrvBat_Manage(void)
 * \brief this function will call LibBatMngBmv700_Manage
 *
 * \param  none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType SrvBat_Manage(void)
{
    /*! Declaration */
    Std_ReturnType t_Manage_Status;
    bool b_IsNewData;
	uint32 u32_time_sec ;
	uint32 u32_time_ns ;

    /*! Initialization */
    t_Manage_Status=E_OK;
    b_IsNewData=K_FALSE;

    /*! Function Body */
    if((E_NOT_OK!=gt_InitBatteryManager_Status)&&
		(E_NOT_OK!=gt_ConfBatteryManager_Status))
    {
    	u32_time_sec = 0 ;
    	u32_time_ns = 0 ;

    	/*! Read current time */
		t_Manage_Status |= StdLib_GetTime( &u32_time_sec , &u32_time_ns ) ;

    	t_Manage_Status|=LibBatMngBmv700_Manage();
    	if (E_NOT_OK!=t_Manage_Status)
    	{
    		t_Manage_Status|=LibBatMngBmv700_Get_Data(&gs_Bmv700_NewData,&b_IsNewData);
    		if (K_FALSE!=b_IsNewData)
    		{
    			gs_Data.u32_timestamp_sec = u32_time_sec ;
    			gs_Data.u32_timestamp_ns = u32_time_ns ;

    			/*! If New data valid, copy it in s_Bmv700_Data data structure */
    			memcpy(&(gs_Data.s_data),&gs_Bmv700_NewData,sizeof(ts_Bmv700_Data));
    		}
    		else
    		{
    			; /* Do Nothing */
    		}
    	}
    	LibraryErrorManage();

    }
    else
    {
		/* Module is not initialized, Halt */
        t_Manage_Status=E_NOT_OK;
    }

    /*! return code */
    return(t_Manage_Status);
}

/**
 * \fn static void LibraryErrorManage(void)
 * \brief this function
 *
 * \param  none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
static void LibraryErrorManage(void)
{
	/*! Declaration */
	te_Bmv700_error e_Bmv700_error;
    Std_ReturnType t_Error_Status;

	/*! Initialization */
	e_Bmv700_error = E_BMV700_ERR_NO_ERROR;

	/*! Function Body */
	/*! Get Lib Battery error */
	t_Error_Status=LibBatMngBmv700_Get_Error(&e_Bmv700_error);

	if (E_NOT_OK != t_Error_Status)
	{
		switch(e_Bmv700_error)
		{
			case E_BMV700_ERR_NO_ERROR:
								ge_SrvBat_error = E_SRVBAT_ERR_NO_ERROR;
								break;
			case E_BMV700_ERR_SERIAL_DRIVER:
								ge_SrvBat_error = E_SRVBAT_ERR_SERIAL_DRIVER;
								break;
			case E_BMV700_ERR_CHECKSUM :
								ge_SrvBat_error = E_SRVBAT_ERR_CHECKSUM;
								break;
			case E_BMV700_ERR_NOT_CONFIGURED:
			case E_BMV700_ERR_NOT_INITIALIZED:
			default:
								break;
		}
	}
	else
	{
		;
	}

	/*! return code */
}

/**
 * \fn  Std_ReturnType SrvBat_GetData(ts_SrvBat_Data * const  ps_Bat_Data)
 * \brief this function will return Battery Data
 *
 * \param  none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType SrvBat_GetData(ts_SrvBat_Data * const  ps_Bat_Data)
{
    /*! Declaration */
    Std_ReturnType t_GetData_Status;

    /*! Initialization */
    t_GetData_Status=E_OK;

    /*! Function Body */
    if ((E_NOT_OK!=gt_InitBatteryManager_Status)&&
		(E_NOT_OK!=gt_ConfBatteryManager_Status)&&
		(NULL_PTR!=ps_Bat_Data))
    {
    	memcpy(ps_Bat_Data,&gs_Data,sizeof(ts_SrvBat_Data));
    }
    else
    {
    	t_GetData_Status=E_NOT_OK;
    }

    /*! return code */
    return(t_GetData_Status);
}

/**
 * \fn  Std_ReturnType SrvBat_Close(void)
 * \brief this function will close Battery manager library
 *
 * \param  <parameter-name> { parameter description }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType SrvBat_Close(void)
{
	/* Declaration */
	Std_ReturnType t_Close_Status;

	/* Initialization */
	t_Close_Status = E_OK ;

	/* Function Body */
	if((E_NOT_OK != gt_InitBatteryManager_Status)&&
		(E_NOT_OK!=gt_ConfBatteryManager_Status))
	{
		t_Close_Status |= LibBatMngBmv700_Close();
	}
	else
	{
		/*! Module is not initialized, Halt */
		t_Close_Status = E_NOT_OK ;
	}

	/* return code */
	return(t_Close_Status);
}


/**
 * \fn  Std_ReturnType SrvBat_Get_Error(te_SrvBat_error * const pe_SrvBat_error)
 * \brief this function will return Battery error value
 *
 * \param  te_SrvBat_error * const pe_SrvBat_error
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType SrvBat_Get_Error(te_SrvBat_error * const pe_SrvBat_error)
{
    /*! Declaration */
    Std_ReturnType t_Error_Status;

    /*! Initialization */
    t_Error_Status=E_OK;

    /*! Function Body */
    if(NULL_PTR!=pe_SrvBat_error)
    {
    	*pe_SrvBat_error=ge_SrvBat_error;
        ge_SrvBat_error = E_SRVBAT_ERR_NO_ERROR ;
    }
    else
    {
		/* Module is not initialized, Halt */
    	t_Error_Status=E_NOT_OK;
    }

    /*! return code */
    return(t_Error_Status);
}

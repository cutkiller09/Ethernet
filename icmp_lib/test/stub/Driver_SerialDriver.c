/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Driver_SerialDriver.c
 * $Author: MDEGA
 * $Date: 2015/12/28
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  Driver_SerialDriver.c
  * \brief Source file of SerialDriver Service
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

#define K_DEBUG 1

/* Includes 								      */
/*============================================================================*/
#include "types.h"
#include "Library_StdLib.h"
#include "Driver_SerialDriver.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>



/* Constants and types  						      */
/*============================================================================*/

/* Variables 								      */
/*============================================================================*/
uint8 au8_Message[100];
uint8 au8_Data[100];
uint32 u32_j;
static uint8 au8_filename[512] ;
static sint32 gs32_port_desc;
static uint32 gu32_BufferIndex;

/* Private functions prototypes 					      */
/*============================================================================*/

/* Inline functions 							      */
/*============================================================================*/

/* Private functions 							      */
/*============================================================================*/

/**
 * \fn  Std_ReturnType DrvSerial_Initialize(void)
 * \brief this function initialize internal parametres
 *
 * \param  void
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType DrvSerial_Initialize(void)
{
    /*! return code */
	gu32_BufferIndex=0;
    return(gDrvSerial_t_state_of_function);
}

/**
 * \fn  Std_ReturnType DrvSerial_Open( serialdrv_cfg_type t_configuration , sint32 *ps32_port_desc )
 * \brief this function opens serial link
 *
 * \param  t_configuration [in] : Serial configuration (port name, baudrate, size byte, parity, stop bit)
 * \param  ps32_port_desc [out] : Serial port description
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType DrvSerial_Open( const serialdrv_cfg_type * const t_configuration , sint32 *ps32_port_desc )
{
	if( (NULL_PTR != t_configuration) && (NULL_PTR != ps32_port_desc))
	{
		sprintf( (char*)au8_filename ,
				"02_Code/02_Middleware/Library_LibBatMngBmv700/test/BMV700.dat") ;

		/* Read file frame */
		gs32_port_desc = (sint32 *)fopen( (char*)au8_filename , "rb" );

		*ps32_port_desc  = gs32_port_desc;

		if (ps32_port_desc==NULL)
		{
		  fputs ("File error, 02_Code/02_Middleware/Library_LibBatMngBmv700/test/BMV700.dat doesn't exist",stderr);
		}
	}

    /*! return code */
    return(gDrvSerial_t_state_of_function);
}

/**
 * \fn  Std_ReturnType DrvSerial_Close(void)
 * \brief this function closes serial link
 *
 * \param  ps32_port_desc [in/out] : Serial port description
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType DrvSerial_Close( sint32 * const ps32_port_desc )
{
	if( NULL_PTR != ps32_port_desc )
	{
		fclose( (FILE *)gs32_port_desc ) ;
	}
    /*! return code */
    return(gDrvSerial_t_state_of_function);
}

/**
 * \fn  Std_ReturnType DrvSerial_Send( sint32 s32_port_desc , uint8 *au8_buffer, uint32 u32_buffer_size , sint32 *ps32_written )
 * \brief this function sends datas on serial link
 *
 * \param  s32_port_desc [in] : Serial port description
 * \param  au8_buffer [in] : bytes to send
 * \param  u32_buffer_size [in] : Size of bytes to send
 * \param  ps32_written [out] : Number of datas written (< 0 : error )
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType DrvSerial_Send( const sint32 s32_port_desc , const uint8 * const au8_buffer, const uint32 u32_buffer_size , sint32 * const ps32_written )
{
	if( (NULL_PTR != au8_buffer) && (K_DRVSERIAL_CLOSED == s32_port_desc) && (0 == u32_buffer_size))
	{
		/* NOP */
		;
	}

    /*! Function Body */
    if( NULL_PTR != ps32_written )
    {
		*ps32_written = gDrvSerial_current_s32_written ;
    }

    /*! return code */
    return(gDrvSerial_t_state_of_function);
}

/**
 * \fn  Std_ReturnType DrvSerial_Receive( sint32 s32_port_desc , uint8 *au8_buffer, uint32 u32_buffer_size , sint32 *ps32_read )
 * \brief this function receives datas from serial link
 *
 * \param  s32_port_desc [in] : Serial port description
 * \param  au8_buffer [out] : bytes reading
 * \param  u32_buffer_size [in] : Number of bytes to read
 * \param  ps32_read [out] : Number of datas reading (< 0 : error )
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType DrvSerial_Receive( const sint32 s32_port_desc , uint8 * const au8_buffer, const uint32 u32_buffer_size , sint32 * const ps32_read )
{
    if( (K_DRVSERIAL_CLOSED == s32_port_desc) && (0 == u32_buffer_size) )
    {
    	/* NOP */
    	;
    }
    if( (NULL_PTR != ps32_read) && (NULL_PTR != au8_buffer) )
    {
    	fread( au8_buffer , 1 , u32_buffer_size, s32_port_desc ) ;
    	*ps32_read = u32_buffer_size;
    	gu32_BufferIndex=gu32_BufferIndex+u32_buffer_size;
    }

    /*! return code */
    return(gDrvSerial_t_state_of_function);
}

/**
 * \fn  Std_ReturnType DrvSerial_Flush( sint32 s32_port_desc )
 * \brief this function flush buffer
 *
 * \param  s32_port_desc [in] : Serial port description
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType DrvSerial_Flush( const sint32 s32_port_desc )
{
	if( (K_DRVSERIAL_CLOSED == s32_port_desc) )
	{
		/* NOP */
		;
	}

    /*! return code */
    return(gDrvSerial_t_state_of_function);
}

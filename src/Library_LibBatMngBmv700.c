/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: Library_LibBatMngBmv700.c 
 * $Author: MDega 
 * $Date: 2015/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  Library_LibBatMngBmv700.c 
  * \brief Fichier Source du Service LibBatMngBmv700
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
#include <string.h>
#include <stdio.h>

/* Constants and types  						      */
/*============================================================================*/ 
uint8 au8_FieldLabelBuffer[9];
uint8 au8_FieldValueBuffer[33];
uint8 au8_svalue[4];
uint8 au8_zsvalue[4];

#define K_LABEL_SIZE_MAX					10

typedef enum{
	E_BMV_READ_LABEL=0,
	E_BMV_READ_VALUE,
	E_NO_VALID_VALUE
}te_Bmv700_ReadMode;

typedef enum
{
	E_BMV_LABEL_P = 0x50,
	E_BMV_LABEL_V = 0x56,
	E_BMV_LABEL_I = 0x49,
	E_BMV_LABEL_T = 0x54,
	E_BMV_LABEL_CE = 0x4345,
	E_BMV_LABEL_SOC = 0x534F43,
	E_BMV_LABEL_TTG = 0x545447,
	E_BMV_LABEL_ALARM = 0x6c61726d,
	E_BMV_LABEL_RELAY = 0x656c6179,
	E_BMV_LABEL_AR = 0x4152,
	E_BMV_LABEL_H1 = 0x4831,
	E_BMV_LABEL_H2 = 0x4832,
	E_BMV_LABEL_H3 = 0x4833,
	E_BMV_LABEL_H4 = 0x4834,
	E_BMV_LABEL_H5 = 0x4835,
	E_BMV_LABEL_H6 = 0x4836,
	E_BMV_LABEL_H7 = 0x4837,
	E_BMV_LABEL_H8 = 0x4838,
	E_BMV_LABEL_H9 = 0x4839,
	E_BMV_LABEL_H10 = 0x483130,
	E_BMV_LABEL_H11 = 0x483131,
	E_BMV_LABEL_H12 = 0x483132,
	E_BMV_LABEL_H13 = 0x483133,
	E_BMV_LABEL_H14 = 0x483134,
	E_BMV_LABEL_H15 = 0x483135,
	E_BMV_LABEL_H16 = 0x483136,
	E_BMV_LABEL_H17 = 0x483137,
	E_BMV_LABEL_H18 = 0x483138,
	E_BMV_LABEL_H19 = 0x483139,
	E_BMV_LABEL_H20 = 0x483230,
	E_BMV_LABEL_H21 = 0x483231,
	E_BMV_LABEL_H22 = 0x483232,
	E_BMV_LABEL_H23 = 0x483233,
	E_BMV_LABEL_ERR = 0x455252,
	E_BMV_LABEL_CS = 0x4353,
	E_BMV_LABEL_BMV = 0x424D56,
	E_BMV_LABEL_FW = 0x4657,
	E_BMV_LABEL_PID = 0x504944,
	E_BMV_LABEL_SER = 0x534552,
	E_BMV_LABEL_HSDS = 0x48534453,
	E_BMV_LABEL_CHECKSUM=0x6b73756d
}te_Bmv700_label;

#define BUFFERSIZE_BMV 600
#define RS232_TIMEOUT_BMV 2 //in seconds
#define RET_LIMIT 3

#define K_FRAME_SIZE_MAX  2048
#define K_BUFFER_SIZE_MAX 128

/* Variables 								      */
/*============================================================================*/ 
static Std_ReturnType gt_InitLibBatMngBmv700_Status=E_NOT_OK; /* Global Initialization variable */
static Std_ReturnType gt_ConfigLibBatMngBmv700_Status=E_NOT_OK; /* Global Configuration variable */
static ts_libBatMngBmv700_configuration gs_configuration;
static uint8 au8_Label[100];
static uint8 gau8_buffer[UINT16_MAX];
static uint8 gau8_GlobalBuffer[UINT16_MAX];
static uint8 gau8_tempBuffer[UINT16_MAX];
static sint32 gs32_port_desc;
static ts_Bmv700_Data gs_Temp_Bmv700_Data;
static ts_Bmv700_Data gs_Bmv700_Data;
static uint8 au8_RawData[UINT16_MAX];
static uint16 gu16_index_LastEndOfBlockChecksum;
static uint16 gu16_index_StartOfBlock;
static bool gb_ChecksumValid;
static uint16 gu16_GlobaLBufferIndex;
static te_Bmv700_error ge_Bmv700_error=E_BMV700_ERR_NOT_INITIALIZED;

/* Private functions prototypes 					      */
/*============================================================================*/
static Std_ReturnType receive_label_and_value(void);
Std_ReturnType CompleteDataStructure(const te_Bmv700_label e_label,const sint32 s32_value, const uint32 u32_hexvalue, const uint8 * const pu8_svalue, uint32 u32_index_EndOfBlock);
static Std_ReturnType ComputeChecksum( uint8 * const pu8_data, const uint32 u32_BlockStart, const uint32 u32_BlockLength, const uint32 u32_BufferMaxSize);
static Std_ReturnType Found_PID_Start(void);

/* Inline functions 							      */
/*============================================================================*/


/* Private functions 							      */
/*============================================================================*/

/**
 * \fn  ComputeChecksum( uint8* pau8_data , uint16 u16_dataLength , uint8* pau8_checksum )
 * \brief this function calculates checksum
 *
 * \param  pau8_data [in] : Pointer of message
 * \param  pu16_dataLength [in] : Size of message
 * \param  pau8_checksum [OUT] : Checksum
 *
* \return void
 */
//static Std_ReturnType ComputeChecksum( uint8 * const pu8_data, const uint32 u32_BlockLength, const uint32 u32_Checksum_receive, uint8 * const pu8_RawData )
static Std_ReturnType ComputeChecksum( uint8 * const pu8_data, const uint32 u32_BlockStart, const uint32 u32_BlockLength, const uint32 u32_BufferMaxSize)
{
	/* Declaration */
	Std_ReturnType t_checksum_status;
	uint32 u32_checksum_compute ;
	uint32 u32_i ;
	uint32 u32_j ;

	/* Initialization */
	t_checksum_status=E_OK;
	u32_checksum_compute=0;

	/* Function body */
	if(NULL_PTR != pu8_data)
	{
		for( u32_i = u32_BlockStart ; u32_i < u32_BlockLength; u32_i++ )
		{
			u32_j=u32_i%u32_BufferMaxSize;
			u32_checksum_compute = u32_checksum_compute + *(pu8_data+u32_j) ;
		}
		u32_checksum_compute=u32_checksum_compute%256;
		if (u32_checksum_compute!=0)
		{
			gb_ChecksumValid=K_FALSE;
			ge_Bmv700_error=E_BMV700_ERR_CHECKSUM;
		}
		else
		{
			gb_ChecksumValid=K_TRUE;
			memcpy (&gs_Bmv700_Data,&gs_Temp_Bmv700_Data,sizeof(ts_Bmv700_Data));
		}
	}
	else
	{
		t_checksum_status=E_NOT_OK;
	}

	/* return code */
	return(t_checksum_status);
}

/* Public functions 							      */
/*============================================================================*/

/**
 * \fn  Std_ReturnType LibBatMngBmv700_Initialize(void) 
 * \brief this function <TBD>
 *
 * \param  <parameter-name> { parameter description }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
void LibBatMngBmv700_Initialize(void)
{
    /* Declaration */

    /* Initialization */
	gu16_index_LastEndOfBlockChecksum=0;
	gu16_index_StartOfBlock=0;
	gb_ChecksumValid=K_FALSE;

    /* Function Body */
	gu16_GlobaLBufferIndex=0;
	gs32_port_desc = K_DRVSERIAL_CLOSED ;
	memset(&gs_Temp_Bmv700_Data,0,sizeof(gs_Temp_Bmv700_Data));
	memset(&gs_Bmv700_Data,0,sizeof(gs_Bmv700_Data));
	memcpy(&gs_Temp_Bmv700_Data.au8_AlarmState,"OFF",3);
	memcpy(&gs_Temp_Bmv700_Data.au8_RelayState,"OFF",3);
	memset(&gau8_buffer[0],0,K_FRAME_SIZE_MAX);

    gt_InitLibBatMngBmv700_Status=E_OK;
    ge_Bmv700_error=E_BMV700_ERR_NO_ERROR;

    /* return code */
}


/**
 * \fn  Std_ReturnType LibImuMti_Open(void)
 * \brief this function opens serial port
 *
 * \param  none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType LibBatMngBmv700_Open(void)
{
    /*! Declaration */
	Std_ReturnType t_Open_Status;

    /*! Initialization */

    /*! Function Body */
    if((E_NOT_OK!=gt_InitLibBatMngBmv700_Status) &&
		(E_NOT_OK!=gt_ConfigLibBatMngBmv700_Status))
	{
		/*! Open serial link */
		t_Open_Status = DrvSerial_Open( &(gs_configuration.s_serial_configuration) , &gs32_port_desc ) ;
		if (E_NOT_OK!=t_Open_Status)
		{
			t_Open_Status = DrvSerial_Flush( gs32_port_desc ) ;
		}
		else
		{
			; /* Do Nothing */
		}
		if (E_NOT_OK!=t_Open_Status)
		{
			ge_Bmv700_error=E_BMV700_ERR_NO_ERROR;
		}
		else
		{
			ge_Bmv700_error=E_BMV700_ERR_SERIAL_DRIVER;
		}
	}
	else
	{
		/* Module is not initialized, Halt */
		t_Open_Status = E_NOT_OK ;
	}


    /*! return code */
    return(t_Open_Status);
}

/**
 * \fn  Std_ReturnType LibImuMti_Close(void)
 * \brief this function closes the Imu Controller
 *
 * \param none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType LibBatMngBmv700_Close(void)
{
    /*! Declaration */
	Std_ReturnType t_Close_Status;

    /*! Initialization */
	t_Close_Status = E_OK;

    /*! Function Body */
    if((E_NOT_OK!=gt_InitLibBatMngBmv700_Status) &&
		(E_NOT_OK!=gt_ConfigLibBatMngBmv700_Status))
    {
    	t_Close_Status |= DrvSerial_Close( &gs32_port_desc ) ;
		if (E_NOT_OK!=t_Close_Status)
		{
			ge_Bmv700_error=E_BMV700_ERR_NO_ERROR;
		}
		else
		{
			ge_Bmv700_error=E_BMV700_ERR_SERIAL_DRIVER;
		}
    }
    else
    {
		/* Module is not initialized, Halt */
    	t_Close_Status = E_NOT_OK;
    }

    /*! return code */
    return(t_Close_Status);
}

/**
 * \fn  Std_ReturnType LibImuMti_Configure( const ts_libImuMti_configuration * const ps_configuration )
 * \brief this function configures Imu module
 *
 * \param  ps_configuration : Imu configuration
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType LibBatMngBmv700_Configure( const ts_libBatMngBmv700_configuration * const ps_configuration )
{
    /*! Declaration */
	Std_ReturnType t_Configure_status;

    /*! Initialization */

    /*! Function Body */

	if((E_NOT_OK != gt_InitLibBatMngBmv700_Status) &&
		(NULL_PTR != ps_configuration))
	{
		t_Configure_status = E_OK ;
		memcpy( &gs_configuration , ps_configuration , sizeof(ts_libBatMngBmv700_configuration) ) ;
	}
	else
	{
		/* Module is not initialized, Halt */
		t_Configure_status = E_NOT_OK ;
		ge_Bmv700_error=E_BMV700_ERR_NOT_CONFIGURED;
	}

	gt_ConfigLibBatMngBmv700_Status=t_Configure_status;

    /*! return code */
	return(t_Configure_status);
}

/**
 * \fn  Std_ReturnType LibBatMngBmv700_Manage(void)
 * \brief this function <TBD>
 *
 * \param  <parameter-name> { parameter description }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType LibBatMngBmv700_Manage(void)
{
    /* Declaration */
    Std_ReturnType t_Manage_Status;

    /* Initialization */
	t_Manage_Status=E_OK;

    /* Function Body */
    if((E_NOT_OK!=gt_InitLibBatMngBmv700_Status)&&
		(E_NOT_OK!=gt_ConfigLibBatMngBmv700_Status))
    {
    	/*! Receive Label and value from BMV700 message */
    	t_Manage_Status|=receive_label_and_value();
    }
    else
    {
	/*! Module is not initialized, Halt */
    	t_Manage_Status=E_NOT_OK;
    }

    /* return code */
    return(t_Manage_Status);
}

/**
 * \fn  Std_ReturnType LibBatMngBmv700_Manage(void)
 * \brief this function <TBD>
 *
 * \param  <parameter-name> { parameter description }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType LibBatMngBmv700_Get_Data(ts_Bmv700_Data * const ps_Bmv700_Data, bool * const pb_IsNewData)
{
    /* Declaration */
    Std_ReturnType t_GetData_Status;

    /* Initialization */
    t_GetData_Status=E_OK;

    /* Function Body */
    if((E_NOT_OK!=gt_InitLibBatMngBmv700_Status)&&
    		(E_NOT_OK!=gt_ConfigLibBatMngBmv700_Status)&&
		(NULL_PTR!=ps_Bmv700_Data))
    {
		/*! Data returned only if Checksum is correct */
		memcpy(ps_Bmv700_Data,&gs_Bmv700_Data,sizeof(ts_Bmv700_Data));
    	*pb_IsNewData=gb_ChecksumValid;
    	gb_ChecksumValid=K_FALSE;
    }
    else
    {
	/*! Module is not initialized, Halt */
    	t_GetData_Status=E_NOT_OK;
    }

    /* return code */
    return(t_GetData_Status);
}

/**
 * \fn  Std_ReturnType SrvImu_Get_Error(te_Bmv700_error * const pe_Bmv700_error)
 * \brief this function <TBD>
 *
 * \param  <parameter-name> { parameter description }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
Std_ReturnType LibBatMngBmv700_Get_Error(te_Bmv700_error * const pe_Bmv700_error)
{
    /* Declaration */
    Std_ReturnType t_GetError_Status;

    /* Initialization */
    t_GetError_Status=E_OK;

    /* Function Body */
    if(NULL_PTR!=pe_Bmv700_error)
    {
    	*pe_Bmv700_error=ge_Bmv700_error;
        ge_Bmv700_error = E_BMV700_ERR_NO_ERROR ;
    }
    else
    {
	/*! Module is not initialized, Halt */
    	t_GetError_Status=E_NOT_OK;
    }

    /* return code */
    return(t_GetError_Status);
}

/**
 * \fn  static Std_ReturnType receive_label_and_value(void)
 * \brief this function will receive Bmv700 datas and values
 *
 * \param  none
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
static Std_ReturnType receive_label_and_value(void)
{
	/* Declaration */
	Std_ReturnType t_Receive_Status;
    uint8 * pu8_Message;
    sint32 s32_read;
    uint32 u32_label;
    uint32 u32_i;
    uint32 u32_j;
    te_Bmv700_ReadMode e_BmvReadMode;
    sint32 s32_value;
    uint32 u32_index_EndOfBlock;
    uint32 u32_hexvalue;
    uint32 u32_CptRawData;
	uint32 u32_DataRead;
	uint32 u32_NbDataRead_Max;
	sint8 s8_ReturnScanf;

	/* Initialization */
	s32_read = 0 ;
    u32_label=0;
    u32_j=0;
    u32_i=0;
    u32_index_EndOfBlock=0;
    t_Receive_Status=E_OK;
    e_BmvReadMode=E_BMV_READ_LABEL;
    u32_CptRawData=0;
    u32_DataRead=0;

	/* Function Body */
	/*!   Read serial link */
	t_Receive_Status |= DrvSerial_Receive( gs32_port_desc, &gau8_buffer[0] , K_BUFFER_SIZE_MAX , &s32_read ) ;

	if( 0 < s32_read )
	{

#ifdef K_DEBUG
		printf("gu32_GlobaLBufferIndex :%u \n",gu16_GlobaLBufferIndex);
		printf("s32_read :%i \n",s32_read);
		printf("gu32_index_StartOfBlock :%u \n",gu16_index_StartOfBlock);
#endif
		/*! Check if buffer max size is not reached */
		if ((gu16_GlobaLBufferIndex+s32_read)>K_FRAME_SIZE_MAX)
		{
			/*! Max buffer size reached => circular buffer set to zer0 */
			memcpy(&gau8_GlobalBuffer[gu16_GlobaLBufferIndex],gau8_buffer,(K_FRAME_SIZE_MAX-gu16_GlobaLBufferIndex));
			memcpy(&gau8_GlobalBuffer[0],&gau8_buffer[K_FRAME_SIZE_MAX-gu16_GlobaLBufferIndex],(s32_read-(K_FRAME_SIZE_MAX-gu16_GlobaLBufferIndex)));
			gu16_GlobaLBufferIndex=0;
		}
		else
		{
			/*! Copy RS232 buffer in global buffer */
			memcpy(&gau8_GlobalBuffer[gu16_GlobaLBufferIndex],gau8_buffer,s32_read);
			gu16_GlobaLBufferIndex=(gu16_GlobaLBufferIndex+(uint32)s32_read)%(K_FRAME_SIZE_MAX+1);
		}

		if(E_NOT_OK!=Found_PID_Start())
		{
			if (gu16_GlobaLBufferIndex>gu16_index_StartOfBlock)
			{
				;
			}
			/* If Circular buffer maximum value reached */
			else
			{
				gu16_index_StartOfBlock=0; /* Start at Zero, actual frame will be rejected at checksum computation because she will certainly be incomplete */
											/*! Solution is not the best one, but is the easiest */

				/*! previous management of circular buffer, not functional */
				// memcpy(&gau8_tempBuffer,&gau8_GlobalBuffer[gu16_index_StartOfBlock],(K_FRAME_SIZE_MAX-gu16_index_StartOfBlock));
				// memcpy(&gau8_tempBuffer[K_FRAME_SIZE_MAX-gu16_index_StartOfBlock],&gau8_GlobalBuffer[0],gu16_GlobaLBufferIndex);
				// u32_NbDataRead_Max=gu16_GlobaLBufferIndex+(K_FRAME_SIZE_MAX-gu16_index_StartOfBlock);
			}
			memcpy(&gau8_tempBuffer,&gau8_GlobalBuffer[gu16_index_StartOfBlock],(gu16_GlobaLBufferIndex-gu16_index_StartOfBlock));
			u32_NbDataRead_Max=gu16_GlobaLBufferIndex-gu16_index_StartOfBlock;

	#ifdef K_DEBUG
				printf("Circular buffer maximum value reached \n");
	#endif

	#ifdef K_DEBUG
			printf("u32_NbDataRead_Max :%u \n",u32_NbDataRead_Max);
	#endif

			pu8_Message = (uint8 *)strtok ((char *)gau8_tempBuffer,(const char *)"\r");
			if (NULL_PTR!=pu8_Message)
			{
				u32_index_EndOfBlock=(gu16_index_StartOfBlock+strlen((const char *)pu8_Message)+1)%K_FRAME_SIZE_MAX;
				u32_DataRead=u32_DataRead+strlen((const char *)pu8_Message)+1;
				while ((E_NO_VALID_VALUE!=e_BmvReadMode)&&
						(u32_DataRead<u32_NbDataRead_Max)&&
					   (NULL_PTR!=pu8_Message))
				{
					switch(e_BmvReadMode)
					{
						case E_BMV_READ_LABEL :
												/* Robustness test */
												if (u32_i>K_LABEL_SIZE_MAX)
												{
													e_BmvReadMode=E_NO_VALID_VALUE;
												}
												else
												{
													u32_label=0;
													if ((*(pu8_Message+u32_i)!='\r')&&
															(*(pu8_Message+u32_i)!='\t')&&
															(*(pu8_Message+u32_i)!='\n'))
													{
														au8_Label[u32_j]=*(pu8_Message+u32_i);
														u32_i++;
														u32_j++;
													}
													else
													{
														u32_i++;
													}
													if (*(pu8_Message+u32_i)!='\t')
													{
														;
													}
													else
													{
														e_BmvReadMode=E_BMV_READ_VALUE;
														for (u32_j=0; u32_j<(u32_i-1); u32_j++)
														{
															u32_label=(u32_label<<8)+au8_Label[u32_j];
															au8_RawData[u32_CptRawData++]=au8_Label[u32_j];
														}
													}

												}
#ifdef K_DEBUG_2
													printf("u32_i :%u \n",u32_i);
													printf("u32_j :%u \n",u32_j);
#endif
												break;
						case E_BMV_READ_VALUE :
												s32_value=0;
												u32_hexvalue=0;
												au8_svalue[0]=*(pu8_Message+u32_i+0);
												if (au8_svalue[0]!='\t')
												{
													au8_svalue[1]=*(pu8_Message+u32_i+1);
													au8_svalue[2]=*(pu8_Message+u32_i+2);
													au8_svalue[3]=*(pu8_Message+u32_i+3);
												}
												else
												{
													au8_svalue[0]=*(pu8_Message+u32_i+1);
													au8_svalue[1]=*(pu8_Message+u32_i+2);
													au8_svalue[2]=*(pu8_Message+u32_i+3);
													au8_svalue[3]=0;
												}
	#ifdef K_DEBUG_2
			printf("u32_i :%u \n",u32_i);
	#endif
												s8_ReturnScanf=sscanf((const char * volatile)(pu8_Message+u32_i), "%d", &s32_value);
												if (s8_ReturnScanf>0)
												{
													;
												}
												else
												{
													s32_value=0;
												}

												s8_ReturnScanf=sscanf((const char * volatile)(pu8_Message+u32_i), "%x", &u32_hexvalue);
												if (s8_ReturnScanf>0)
												{
													;
												}
												else
												{
													u32_hexvalue=0;
												}

												t_Receive_Status|=CompleteDataStructure((te_Bmv700_label)u32_label,s32_value,u32_hexvalue,au8_svalue,u32_index_EndOfBlock);

												pu8_Message = (uint8 *)strtok ((char *)NULL,(const char *) "\r");
												if (NULL_PTR!=pu8_Message)
												{
													u32_index_EndOfBlock=(u32_index_EndOfBlock+strlen((const char *)pu8_Message)+1)%K_FRAME_SIZE_MAX;
													u32_DataRead=u32_DataRead+strlen((const char *)pu8_Message)+1;
	#ifdef K_DEBUG_2
			printf("u32_index_EndOfBlock :%u \n",u32_index_EndOfBlock);
			printf("u32_DataRead :%u \n",u32_DataRead);
	#endif
												}
												else
												{
													;
												}
												u32_i=0;
												u32_j=0;
												e_BmvReadMode=E_BMV_READ_LABEL;
												break;

						case E_NO_VALID_VALUE :
						default:
												t_Receive_Status=E_OK;
												break;
					}

				}
			}
		}
		else
		{
			;
		}
	}
	else
	{
		; /* Do Nothing */
	}

	/* return code */
	return(t_Receive_Status);
}

/**
 * \fn Std_ReturnType CompleteDataStructure(const te_Bmv700_label e_label,const sint32 s32_value)
 * \brief this function will complete data structure
 *
 * \param  <te_Bmv700_label e_label> { Bmv700 label }
 * 			<sint32 s32_value> { Bmv700 label value }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
//Std_ReturnType CompleteDataStructure(const te_Bmv700_label e_label,const sint32 s32_value, const uint32 u32_hexvalue, uint32 u32_index_EndOfBlock, uint8 * const pu8_RawData)
static Std_ReturnType Found_PID_Start(void)
{
    /* Declaration */
	Std_ReturnType t_Pid_Status;
	uint32 u32_CurrentIndex_StartOfBlock_Saved;
	bool b_CircularBufferLoop_Done;

    /* Initialization */
	u32_CurrentIndex_StartOfBlock_Saved=gu16_index_StartOfBlock;
	b_CircularBufferLoop_Done=K_FALSE;

    /* Function Body */
	while ((gau8_GlobalBuffer[gu16_index_StartOfBlock]!='\n')&&
			(gau8_GlobalBuffer[gu16_index_StartOfBlock+1]!='P')&&
			(gau8_GlobalBuffer[gu16_index_StartOfBlock+2]!='I')&&
			(gau8_GlobalBuffer[gu16_index_StartOfBlock+3]!='D')&&
			(gu16_index_StartOfBlock<gu16_GlobaLBufferIndex))
	{
		gu16_index_StartOfBlock=(gu16_index_StartOfBlock+1)%K_FRAME_SIZE_MAX;
		if (gu16_index_StartOfBlock<u32_CurrentIndex_StartOfBlock_Saved)
		{
			b_CircularBufferLoop_Done=K_TRUE;
		}
	}

	/*! If A complet circular buffer loop have been executed and nothing founded, then return E_NOT_OK status */
	if ((gu16_index_StartOfBlock>=u32_CurrentIndex_StartOfBlock_Saved)&&
		(K_FALSE!=b_CircularBufferLoop_Done))
	{
		t_Pid_Status=E_NOT_OK;
	}
	else
	{
		t_Pid_Status=E_OK;
	}

	/* Return code */
	return(t_Pid_Status);
}

/**
 * \fn Std_ReturnType CompleteDataStructure(const te_Bmv700_label e_label,const sint32 s32_value)
 * \brief this function will complete data structure
 *
 * \param  <te_Bmv700_label e_label> { Bmv700 label }
 * 			<sint32 s32_value> { Bmv700 label value }
 *
* \return Std_ReturnType :
*         - E_OK if good return function
*         - E_NOT_OK if not
 */
//Std_ReturnType CompleteDataStructure(const te_Bmv700_label e_label,const sint32 s32_value, const uint32 u32_hexvalue, uint32 u32_index_EndOfBlock, uint8 * const pu8_RawData)
Std_ReturnType CompleteDataStructure(const te_Bmv700_label e_label,const sint32 s32_value, const uint32 u32_hexvalue, const uint8 * const pu8_svalue, uint32 u32_index_EndOfBlock)
{
    /* Declaration */
	Std_ReturnType t_Complete_Status;

    /* Initialization */
	t_Complete_Status=E_OK;

    /* Function Body */
	switch(e_label)
	{
		case E_BMV_LABEL_V:
			gs_Temp_Bmv700_Data.s32_Voltage=s32_value;
			break;
		case E_BMV_LABEL_I:
			gs_Temp_Bmv700_Data.s32_BatteryCurrent=s32_value;
			break;
		case E_BMV_LABEL_T:
			gs_Temp_Bmv700_Data.s32_BatteryTemperature=s32_value;
			break;
		case E_BMV_LABEL_P:
			gs_Temp_Bmv700_Data.s32_InstantaneousPower=s32_value;
			break;
		case E_BMV_LABEL_ALARM:
			memcpy(&gs_Temp_Bmv700_Data.au8_AlarmState,pu8_svalue,4);
			break;
		case E_BMV_LABEL_AR:
			gs_Temp_Bmv700_Data.s32_AlarmReason=s32_value;
			break;
		case E_BMV_LABEL_BMV:
			gs_Temp_Bmv700_Data.s32_ModelDescription=s32_value;
			break;
		case E_BMV_LABEL_CE:
			gs_Temp_Bmv700_Data.s32_ConsumedAmpHours=s32_value;
			break;
		case E_BMV_LABEL_FW:
			gs_Temp_Bmv700_Data.s32_FirmwareVersion=s32_value;
			break;
		case E_BMV_LABEL_H1:
			gs_Temp_Bmv700_Data.s32_DeepestDischargeDepth=s32_value;
			break;
		case E_BMV_LABEL_H2:
			gs_Temp_Bmv700_Data.s32_LastDischargeDepth=s32_value;
			break;
		case E_BMV_LABEL_H3:
			gs_Temp_Bmv700_Data.s32_AvgDischargeDepth=s32_value;
			break;
		case E_BMV_LABEL_H4:
			gs_Temp_Bmv700_Data.s32_NumberOfChargeCycles=s32_value;
			break;
		case E_BMV_LABEL_H5:
			gs_Temp_Bmv700_Data.s32_NumberOfFullDischarges=s32_value;
			break;
		case E_BMV_LABEL_H6:
			gs_Temp_Bmv700_Data.s32_CumulativeAmpHoursDrawn=s32_value;
			break;
		case E_BMV_LABEL_H7:
			gs_Temp_Bmv700_Data.s32_MiniMainVoltage=s32_value;
			break;
		case E_BMV_LABEL_H8:
			gs_Temp_Bmv700_Data.s32_MaxiMainVoltage=s32_value;
			break;
		case E_BMV_LABEL_H9:
			gs_Temp_Bmv700_Data.s32_NbSecSinceLastFullCharge=s32_value;
			break;
		case E_BMV_LABEL_H10:
			gs_Temp_Bmv700_Data.s32_NbAutoSynchro=s32_value;
			break;
		case E_BMV_LABEL_H11:
			gs_Temp_Bmv700_Data.s32_NbLowMainVoltageAlarms=s32_value;
			break;
		case E_BMV_LABEL_H12:
			gs_Temp_Bmv700_Data.s32_NbHighMainVoltageAlarms=s32_value;
			break;
		case E_BMV_LABEL_H15:
			gs_Temp_Bmv700_Data.s32_MiniAuxiVoltage=s32_value;
			break;
		case E_BMV_LABEL_H16:
			gs_Temp_Bmv700_Data.s32_MaxiAuxiVoltage=s32_value;
			break;
		case E_BMV_LABEL_H17:
			gs_Temp_Bmv700_Data.s32_DischargedEnergyAmount=s32_value;
			break;
		case E_BMV_LABEL_H18:
			gs_Temp_Bmv700_Data.s32_ChargedEnergyAmount=s32_value;
			break;
		case E_BMV_LABEL_PID:
			gs_Temp_Bmv700_Data.t_ProductId=u32_hexvalue;
			t_Complete_Status=ComputeChecksum( gau8_GlobalBuffer, gu16_index_StartOfBlock,gu16_index_LastEndOfBlockChecksum,K_FRAME_SIZE_MAX);
			gu16_index_StartOfBlock=gu16_index_LastEndOfBlockChecksum;
			break;
		case E_BMV_LABEL_RELAY:
			memcpy(&gs_Temp_Bmv700_Data.au8_RelayState,pu8_svalue,4);
			break;
		case E_BMV_LABEL_SOC:
			gs_Temp_Bmv700_Data.s32_StateOfCharge=s32_value;
			break;
		case E_BMV_LABEL_TTG:
			gs_Temp_Bmv700_Data.s32_TimeToGo=s32_value;
			break;
		case E_BMV_LABEL_CHECKSUM:
			gu16_index_LastEndOfBlockChecksum=u32_index_EndOfBlock;
			break;
		case E_BMV_LABEL_SER:
		case E_BMV_LABEL_H13:
		case E_BMV_LABEL_H14:
		case E_BMV_LABEL_H19:
		case E_BMV_LABEL_H20:
		case E_BMV_LABEL_H21:
		case E_BMV_LABEL_H22:
		case E_BMV_LABEL_H23:
		case E_BMV_LABEL_HSDS:
		case E_BMV_LABEL_CS:
		case E_BMV_LABEL_ERR:
		default :
			break;
	}

    /* return code */
    return(t_Complete_Status);
}

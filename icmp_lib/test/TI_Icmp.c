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
#include "Icmp.h"


/* Constants and types  						      */
/*============================================================================*/  
#define MACRO_START_UT(u16_num_case, sz_title_case) printf( "\nCase %d : \\************ %s ************\\ \n" , u16_num_case , sz_title_case ) ; fflush( stdout ) ;
#define MACRO_ASSERT_UT(u16_num_case , u16_error_count , u16_num_error_expected ) \
		printf( "Case %d : " #u16_error_count " = %d ("#u16_num_error_expected") : %d) : %s\n" , \
				u16_num_case , \
				u16_error_count , \
				u16_num_error_expected , \
				(u16_num_error_expected==u16_error_count)?"SUCCESS":"FAILED" ) ; 
#define K_NB_LOOP 10000
   
/* Variables 								      */
/*============================================================================*/ 
IpPacket_t SIMU_IpPacket_SEND;
IpPacket_t SIMU_IpPacket_RECEIVED;   
 

static IpPacket_t SIMU_IpPacket_ECHO_REQUEST;   

/* Private functions prototypes 					      */
/*============================================================================*/ 
void Initialization(void);

/* Inline functions 							      */
/*============================================================================*/



/* Private functions 							      */
/*============================================================================*/
void Check_Ping_Answer(UNS16 Test_Number)
{
	/* Declaration */
	
	/* Initialization */

	/* Body */
	
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cDestAddress_a[0] , SIMU_IpPacket_RECEIVED.Header.cSourceAddress_a[0] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cDestAddress_a[1] , SIMU_IpPacket_RECEIVED.Header.cSourceAddress_a[1] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cDestAddress_a[2] , SIMU_IpPacket_RECEIVED.Header.cSourceAddress_a[2] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cDestAddress_a[3] , SIMU_IpPacket_RECEIVED.Header.cSourceAddress_a[3] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cProtocol , SIMU_IpPacket_RECEIVED.Header.cProtocol )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cServiceType , SIMU_IpPacket_RECEIVED.Header.cServiceType )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cSourceAddress_a[0] , SIMU_IpPacket_RECEIVED.Header.cDestAddress_a[0] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cSourceAddress_a[1] , SIMU_IpPacket_RECEIVED.Header.cDestAddress_a[1] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cSourceAddress_a[2] , SIMU_IpPacket_RECEIVED.Header.cDestAddress_a[2] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cSourceAddress_a[3] , SIMU_IpPacket_RECEIVED.Header.cDestAddress_a[3] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cTimeToLive , SIMU_IpPacket_RECEIVED.Header.cTimeToLive )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.cVersion_IHL , SIMU_IpPacket_RECEIVED.Header.cVersion_IHL )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Header.nHeaderChecksum , SIMU_IpPacket_RECEIVED.Header.nHeaderChecksum )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.Header.cCode , SIMU_IpPacket_RECEIVED.Payload.Icmp.Header.cCode )
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.Header.cType , 8 ) 
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.Header.lHeaderData , SIMU_IpPacket_RECEIVED.Payload.Icmp.Header.lHeaderData )   
	// MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.Header.nChecksum , SIMU_IpPacket_RECEIVED.Payload.Icmp.Header.nChecksum )     
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.cData_a[0] , SIMU_IpPacket_RECEIVED.Payload.Icmp.cData_a[0] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.cData_a[1] , SIMU_IpPacket_RECEIVED.Payload.Icmp.cData_a[1] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.cData_a[2] , SIMU_IpPacket_RECEIVED.Payload.Icmp.cData_a[2] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.cData_a[3] , SIMU_IpPacket_RECEIVED.Payload.Icmp.cData_a[3] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.Payload.Icmp.cData_a[4] , SIMU_IpPacket_RECEIVED.Payload.Icmp.cData_a[4] )   

	/* Return code */
}


void Initialization (void)
{	
	/* Declaration */
	UNS16 u16_i=0; 

	/* Initialization */
    SIMU_IpPacket_ECHO_REQUEST.Header.cVersion_IHL=0x04;
    SIMU_IpPacket_ECHO_REQUEST.Header.cServiceType=0x00;
    SIMU_IpPacket_ECHO_REQUEST.Header.nTotalLength=0x0054;
    SIMU_IpPacket_ECHO_REQUEST.Header.nIdentification=0x5E39;
    SIMU_IpPacket_ECHO_REQUEST.Header.nFlags_FOffset=0x4000;
    SIMU_IpPacket_ECHO_REQUEST.Header.cTimeToLive=0x40;
    SIMU_IpPacket_ECHO_REQUEST.Header.cProtocol=0x01;
    SIMU_IpPacket_ECHO_REQUEST.Header.nHeaderChecksum=0x8448;
    SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[0]=0xac;
    SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[1]=0x12;
    SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[2]=0x00;
    SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[3]=0x01;
    SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[0]=0xac;
    SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[1]=0x12;
    SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[2]=0x00;
    SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[3]=0x02;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.cType=0x08;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.cCode=0x00;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.nChecksum=0x1428;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.lHeaderData=0x25ed0007;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[0]=0x96;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[1]=0xf0;
    SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[2]=0x08;
    for (u16_i=3;u16_i<ROUTER_ICMP_PAYLOAD_SIZE_C;u16_i++)
    {
        SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[u16_i]=0x00;
    }

	/* Body */

	/* Return Code */     
}

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
	DriverReturnCode_t t_main_Status;
	UNS16 u16_j=0;

	/* Initialization */
	Initialization();

	/* Function Body */
	
	/* Good IP frame sent */
    Memory_Copy8(&SIMU_IpPacket_RECEIVED, &SIMU_IpPacket_ECHO_REQUEST, sizeof(IpPacket_t)); 	

	t_main_Status |= Manage_ICMP() ;

	/* Case 0 : Module not initialized */ 
	Check_Ping_Answer(u16_j++);

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  

    /* return code */ 
    return(t_main_Status);
} 

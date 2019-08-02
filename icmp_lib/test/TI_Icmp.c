/*============================================================================*/
/*                        	ROBOSOFT                                      */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*! 
 * $Source: TI_Icmp.c 
 * $Author: Sebastien Loisel 
 * $Date: 2019/12/08  
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file  TI_Icmp.c 
  * \brief Fichier Source file of Integration Test Icmp lib
*/
/*============================================================================*/
/* COPYRIGHT (C) ALTRAN 2019	                                              */ 
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
#include "Packet.h"
#include "Memory.h"
#include  <stdio.h>

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
Packet_t SIMU_IpPacket_SEND;
Packet_t SIMU_IpPacket_RECEIVED; 
Packet_t SIMU_IpPacket_ECHO_REQUEST;  
BOOLEAN B_Frame_Send=TRUE;
// IpPacket_t PING_REQUEST2[]={0x00,0x1B,0x17,0x00,0x1F,0x11,0x64,0x51,0x06,0x5A,0xEE,0x96,0x08,0x00,0x45,0x00,0x00,0x1C,0x00,0x01,0x00,0x00,0x40,0x01,0x20,0x36,0x0A,0x01,0xA2,0xAA,0x0A,0x01,0xA3,0xFE,0x08,0x00,0xF7,0xFF,0x00,0x00,0x00,0x00};


UNS8  PING_REQUEST2[]={0x02,0x42,0x71,0x67,0x2a,0x5f,0x02,0x42,0xac,0x12,0x00,0x02,0x08,0x00,0x45,0x00,0x00,0x54,0x8b,0xf3,0x00,0x00,0x40,0x01,0x96,0x8e,0xac,0x12,0x00,0x02,0xac,0x12,0x00,0x01,0x00,0x00,0x1c,0x28,0x25,0xed,0x00,0x07,0x2e,0xc3,0x31,0x5d,0x00,0x00,0x00,0x00,0x96,0xf0,0x08,0x00,0x00,0x00,0x00,0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25};   

/* Private functions prototypes 					      */
/*============================================================================*/ 
void Initialization(void); 
void Check_Ping_Answer(UNS16 Test_Number);

/* Inline functions 							      */
/*============================================================================*/



/* Private functions 							      */
/*============================================================================*/


void Check_Random_DataPayload_Send(UNS16 Test_Number)
{
	/* Declaration */
	
	/* Initialization */

	/* Body */
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[0] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[1] , 1 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[2] , 2 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[3] , 3 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[4] , 4 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[5] , 5 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[6] , 6 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[7] , 7 )  
	

	/* Return code */
}  

	Check_Zero_DataPayload_Send(UNS16 Test_Number)
{
	/* Declaration */
	
	/* Initialization */

	/* Body */
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[0] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[1] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[2] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[3] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[4] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[5] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[6] , 0 )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.cPayload_a[7] , 0 )  

	/* Return code */
}  


void Check_Ping_Answer(UNS16 Test_Number)
{
	/* Declaration */
	
	/* Initialization */

	/* Body */
 
	/*! Dest Mac Adress */ 
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cDestMACAddress_a[0] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cSourceMACAddress_a[0] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cDestMACAddress_a[1] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cSourceMACAddress_a[1] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cDestMACAddress_a[2] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cSourceMACAddress_a[2] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cDestMACAddress_a[3] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cSourceMACAddress_a[3] )  
	
	/*! Source Mac Adress */ 
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cSourceMACAddress_a[0] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cDestMACAddress_a[0] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cSourceMACAddress_a[1] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cDestMACAddress_a[1] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cSourceMACAddress_a[2] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cDestMACAddress_a[2] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.cSourceMACAddress_a[3] , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.cDestMACAddress_a[3] )  
	
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Header.nEtherType , SIMU_IpPacket_RECEIVED.EthernetFrame.Header.nEtherType )  
	 	
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[0] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[0] ) 
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[1] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[1] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[2] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[2] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[3] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[3] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cProtocol , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cProtocol )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cServiceType , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cServiceType )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[0] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[0] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[1] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[1] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[2] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[2] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[3] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[3] )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cTimeToLive , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cTimeToLive )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.cVersion_IHL , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.cVersion_IHL )  
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Header.nHeaderChecksum , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Header.nHeaderChecksum )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cCode , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cCode )
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType , ICMP_ECHOREPLY ) 
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.lHeaderData , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.lHeaderData )   
	// MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.nChecksum , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.nChecksum )     
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[0] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[0] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[1] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[1] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[2] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[2] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[3] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[3] )   
	MACRO_ASSERT_UT( Test_Number , SIMU_IpPacket_SEND.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[4] , SIMU_IpPacket_RECEIVED.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[4] )   

	/* Return code */
}  

void Initialization (void)
{	
	/* Declaration */
	UNS16 u16_i=0; 
	UNS8 a_data[]={0x00};
	B_Frame_Send=FALSE;

	/* Initialization */ 
	Memory_Copy8(&SIMU_IpPacket_ECHO_REQUEST.cData_a[0],&PING_REQUEST2[0],sizeof(PING_REQUEST2) );


    // SIMU_IpPacket_ECHO_REQUEST.Header.cVersion_IHL=0x04;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cServiceType=0x00;
    // SIMU_IpPacket_ECHO_REQUEST.Header.nTotalLength=0x0054;
    // SIMU_IpPacket_ECHO_REQUEST.Header.nIdentification=0x5E39;
    // SIMU_IpPacket_ECHO_REQUEST.Header.nFlags_FOffset=0x4000;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cTimeToLive=0x40;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cProtocol=0x01;
    // SIMU_IpPacket_ECHO_REQUEST.Header.nHeaderChecksum=0x8448;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[0]=0xac;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[1]=0x12;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[2]=0x00;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cSourceAddress_a[3]=0x01;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[0]=0xac;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[1]=0x12;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[2]=0x00;
    // SIMU_IpPacket_ECHO_REQUEST.Header.cDestAddress_a[3]=0x02;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.cType=0x08;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.cCode=0x00;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.nChecksum=0x1428;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.Header.lHeaderData=0x25ed0007;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[0]=0x96;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[1]=0xf0;
    // SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[2]=0x08;
    // for (u16_i=3;u16_i<ROUTER_ICMP_PAYLOAD_SIZE_C;u16_i++)
    // {
    //     SIMU_IpPacket_ECHO_REQUEST.Payload.Icmp.cData_a[u16_i]=0x00;
    // } 

    for (u16_i=3;u16_i<ROUTER_PACKET_SIZE_C;u16_i++)
    {
        SIMU_IpPacket_RECEIVED.cData_a[u16_i]=0x00;
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

	/*--------------------- Case 0 ---------------------*/
	/* ICMP_ECHO frame received */
	MACRO_START_UT(u16_j, " test ICMP_ECHO frame received ") 

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_ECHO;
    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;	
	MACRO_ASSERT_UT( u16_j , B_Frame_Send , TRUE )   

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  

	/* Check Ping answer received */ 
	Check_Ping_Answer (u16_j++);

	/*--------------------- Case 1 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_ECHOREPLY frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_ECHOREPLY frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_ECHOREPLY;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;
	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 2 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_DEST_UNREACH frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_DEST_UNREACH frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_DEST_UNREACH;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 3 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_SOURCE_QUENCH frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_SOURCE_QUENCH frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_SOURCE_QUENCH;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 4 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_REDIRECT frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_REDIRECT frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_REDIRECT;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 5 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_TIME_EXCEEDED frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_TIME_EXCEEDED frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_TIME_EXCEEDED;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 6 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_PARAMETERPROB frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_PARAMETERPROB frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_PARAMETERPROB;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 7 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_TIMESTAMP frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_TIMESTAMP frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_TIMESTAMP;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 8 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_TIMESTAMPREPLY frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_TIMESTAMPREPLY frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_TIMESTAMPREPLY;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 9 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_INFO_REQUEST frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_INFO_REQUEST frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_INFO_REQUEST;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 10 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_INFO_REPLY frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_INFO_REPLY frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_INFO_REPLY;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 11 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_ADDRESS frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_ADDRESS frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_ADDRESS;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 12 ---------------------*/
	/* Initialization */
	Initialization();

	/* ICMP_ADDRESSREPLY frame received */ 
	MACRO_START_UT(u16_j, "test ICMP_ADDRESSREPLY frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = ICMP_ADDRESSREPLY;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 13 ---------------------*/
	/* Initialization */
	Initialization();

	/* NR_ICMP_TYPES frame received */ 
	MACRO_START_UT(u16_j, "test NR_ICMP_TYPES frame received")

	SIMU_IpPacket_ECHO_REQUEST.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType = NR_ICMP_TYPES;

    Memory_Copy8(&SIMU_IpPacket_RECEIVED.cData_a[0], &SIMU_IpPacket_ECHO_REQUEST.cData_a[0], sizeof(Packet_t)); 	

	t_main_Status |= Manage_ICMP() ;

	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  
	MACRO_ASSERT_UT( u16_j++ , B_Frame_Send , FALSE )   

	/*--------------------- Case 14 ---------------------*/
	/* NR_ICMP_TYPES frame received */ 
	MACRO_START_UT(u16_j, "Zero DataPayload frame generated")

	t_main_Status |= Zero_DataPayload_Generation();
	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E )  

	/* Check Check_Zero_DataPayload frame send */ 
	Check_Zero_DataPayload_Send (u16_j++);

	/*--------------------- Case 15 ---------------------*/
	/* NR_ICMP_TYPES frame received */ 
	MACRO_START_UT(u16_j, "Random DataPayload frame generated")

	t_main_Status |= Random_DataPayload_Generation();
	MACRO_ASSERT_UT( u16_j , t_main_Status , DRVRC_NO_ERROR_E ) 

	/* Check Check_Zero_DataPayload frame send */ 
	Check_Random_DataPayload_Send (u16_j++);

    /* return code */ 
    return(t_main_Status);
} 

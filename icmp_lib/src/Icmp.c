/*****************************************************************************/
/* MODULE HEADER                                                             */
/*****************************************************************************/
/*
  MODULE:      
  PROJECT:   F6X  

  DESCRIPTION:
  This module implements interface of the LAN9250 controller driver.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/ 
#include "Icmp.h"
#include "Packet.h"

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/
LAN9250_Instance_t LAN9250Instance;
UNS32 lSendDataSize_i = (UNS32)24;
UNS32 lReceiveDataSize_i = (UNS32)24;

/*****************************************************************************/
/* FUNCTION PROTOTYPE                                                        */
/*****************************************************************************/
void Ping_Echo_CMD (void);
void Ping_Echo_ANSWER (void);
                         
/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINEs (private)                          */
/*****************************************************************************/
UNS8 DESTINATION_MAC_ADDR_TAB[6] = {0x80,0x00,0x20,0x7A,0x3F,0x3E};
UNS8 SOURCE_MAC_ADDR_TAB[6] = {0x80,0x00,0x20,0x20,0x3A,0xAE};
UNS8 ETHERNET_PAYLOAD_TAB[8] = {0x08,0x00,0x12,0x15,0x66,0x54,0xAB,0xCE};
UNS8 ETHERNET_IP_PACKET_TAB[8] ={0x08,0x00,0xAC,0xBD,0xFE,0xCB,0xCD,0xC5};
UNS8 ETHERNET_ARP_HEADER_TAB[8] ={0x08,0x00,0xBA,0xCD,0xEC,0xFA,0xA3,0x82};

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */
/* ---- private embedded classes ------------------------------------------- */

/*****************************************************************************/
/* SPECIAL MODULE DEFINITIONS                                                */
/*****************************************************************************/

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/  

/***************************************************************/
/* Global function : LAN9250_Read                              */
/***************************************************************/
DriverReturnCode_t Manage_ICMP (void)
{     
	/* Declaration */
	DriverReturnCode_t ReturnCode_op;
	IpPacket_t SendData_ip;
	IpPacket_t ReceiveData_ip;

	/* Initialization */
    ReturnCode_op = DRVRC_NO_ERROR_E;
					
	//LAN9250_Write	((void *)&LAN9250Instance, &SendData_ip, lSendDataSize_i, &ReturnCode_op);
	/* Body */		
	while(1)
	{
		LAN9250_Read	((void *)&LAN9250Instance, &ReceiveData_ip, lReceiveDataSize_i, &ReturnCode_op);
	}

	/* Return Code */
	return(ReturnCode_op);
} 

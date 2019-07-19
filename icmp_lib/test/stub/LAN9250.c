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
#include "LAN9250.h"
#include "Packet.h"
#include "standard.h"
#include "Memory.h"

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/
LAN9250_Instance_t LAN9250Instance;

/*****************************************************************************/
/* FUNCTION PROTOTYPE                                                        */
/*****************************************************************************/
                         
/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINEs (private)                          */
/*****************************************************************************/

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
void LAN9250_Read	(void * Instance_iop,
					void * ReceiveData_op,
					UNS32 lReceiveDataSize_i,
					DriverReturnCode_t * ReturnCode_op)
{ 
    /* Declaration */
   IpPacket_t IpPacket;   

    UNS8    cVersion_IHL;
    UNS8    cServiceType;
    UNS16   nTotalLength;
    UNS16   nIdentification;
    UNS16   nFlags_FOffset;
    UNS8    cTimeToLive;
    UNS8    cProtocol;
    UNS16   nHeaderChecksum;
    UNS8    cSourceAddress_a[ROUTER_IP_LENGTH_C];
    UNS8    cDestAddress_a[ROUTER_IP_LENGTH_C];

    /* Initialization */
    IpPacket.Header.cVersion_IHL=0x04;
    IpPacket.Header.cServiceType=0x00;
    IpPacket.Header.nTotalLength=0x0054;
    IpPacket.Header.nIdentification=0x5E39;
    IpPacket.Header.nFlags_FOffset=0x4000;
    IpPacket.Header.cTimeToLive=0x40;
    IpPacket.Header.cProtocol=0x01;
    IpPacket.Header.nHeaderChecksum=0x8448;
    IpPacket.Header.cSourceAddress_a[0]=0xac120001;
    IpPacket.Header.cDestAddress_a[0]=0xac120002;
    IpPacket.Payload.Icmp.Header.cType=0x08;
    IpPacket.Payload.Icmp.Header.cCode=0x00;
    IpPacket.Payload.Icmp.Header.nChecksum=0x1428;
    IpPacket.Payload.Icmp.Header.lHeaderData=0x25ed0007;
    IpPacket.Payload.Icmp.cData_a[0]=0x96f0080000000000; 
 
    Memory_Copy8(ReceiveData_op,&IpPacket,ROUTER_PACKET_SIZE_C);   
    
    *ReturnCode_op = DRVRC_NO_ERROR_E;
}

/***************************************************************/
/* Global function : LAN9250_Write                             */
/***************************************************************/
void LAN9250_Write	(void * Instance_iop,
                    void * SendData_ip,
					UNS32 lSendDataSize_i,
                    DriverReturnCode_t * ReturnCode_op)
{  
    *ReturnCode_op = DRVRC_NO_ERROR_E;


} 
/*EOF*/
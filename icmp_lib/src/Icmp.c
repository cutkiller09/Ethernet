/*****************************************************************************/
/* MODULE HEADER                                                             */
/*****************************************************************************/
/*
  MODULE:      
  PROJECT:   F6X  

  DESCRIPTION:
  This module implements UNS32erface of the LAN9250 controller driver.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/ 
#include "Icmp.h"
#include "Packet.h"
#include "Memory.h"
#include "RouterDefines_public.h"
#include "LAN9250_SystemMemory.h"
#include "LAN9250.h"
#include "LAN9250_SPI.h"

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/ 

#define BYTE_ORDER BIG_ENDIAN

#if BYTE_ORDER == LITTLE_ENDIAN
# define ODDBYTE(v)	(v)
#elif BYTE_ORDER == BIG_ENDIAN
# define ODDBYTE(v)	((UNS8)(v) << 8)
#else
# define ODDBYTE(v)	htons((UNS8)(v) << 8)
#endif


UNS8  FRAME_EXAMPLE[]={0x02,0x42,0x71,0x67,0x2a,0x5f,0x02,0x42,0xac,0x12,0x00,0x02,0x08,0x00,0x45,0x00,0x00,0x54,0x8b,0xf3,0x00,0x00,0x40,0x01,0x96,0x8e,0xac,0x12,0x00,0x02,0xac,0x12,0x00,0x01,0x00,0x00,0x1c,0x28,0x25,0xed,0x00,0x07,0x2e,0xc3,0x31,0x5d,0x00,0x00,0x00,0x00,0x96,0xf0,0x08,0x00,0x00,0x00,0x00,0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25};   


/*****************************************************************************/
/* FUNCTION PROTOTYPE                                                        */
/*****************************************************************************/ 
void ICMP_Ping_Echo_ANSWER (Packet_t ReceiveData_p, UNS32 lReceiveDataSize_i, DriverReturnCode_t *ReturnCode_op);
                         
/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINEs (private)                          */
/*****************************************************************************/
// UNS8 DESTINATION_MAC_ADDR_TAB[6] = {0x80,0x00,0x20,0x7A,0x3F,0x3E};
// UNS8 SOURCE_MAC_ADDR_TAB[6] = {0x80,0x00,0x20,0x20,0x3A,0xAE};
// UNS8 ETHERNET_PAYLOAD_TAB[8] = {0x08,0x00,0x12,0x15,0x66,0x54,0xAB,0xCE};
// UNS8 ETHERNET_IP_PACKET_TAB[8] ={0x08,0x00,0xAC,0xBD,0xFE,0xCB,0xCD,0xC5};
// UNS8 ETHERNET_ARP_HEADER_TAB[8] ={0x08,0x00,0xBA,0xCD,0xEC,0xFA,0xA3,0x82};

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */
/* ---- private embedded classes ------------------------------------------- */
UNS8 in_cksum(const UNS8 *addr, UNS32 len, UNS8 csum)
{
	UNS32 nleft = len;
	const UNS8 *w = addr;
	UNS8 answer;
	UNS32 sum = csum;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits UNS32o the lower
	 *  16 bits.
	 */
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft == 1)
		sum += ODDBYTE(*(unsigned char *)w); /* le16toh() may be unavailable on old systems */

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}

UNS8 calcul_du_checksum(UNS8 *data, UNS32 taille_de_data)
{
	UNS32 checksum=0;

	// ********************************************************
	// Complément à 1 de la somme des complément à 1 sur 16 bits
	// ********************************************************
	while(taille_de_data>1)
	{ 
		checksum=checksum+*data++;
		taille_de_data=taille_de_data-1;
	}
	if(taille_de_data)
	{
		checksum=checksum+*(UNS8*)data;
	}
	checksum=(checksum>>16)+(checksum&0xffff);
	checksum=checksum+(checksum>>16);

	return ((UNS8)(~checksum));
} 

// Permet     : Permet le calcul du checksum de l'entête ICMP. 
// Argument 1 : Structure de l'entête ICMP dont il faut calculer le checksum.
// Argument 2 : Char 65535 contennant tous ce qu'il y après l'entête ICMP.
// Argument 3 : longueur des data. Cet argument est présent car il ne faut pas utilser strlen(data) car data pourrait contenir des 0.
// Renvoi     : Le checksum sur deux octets (unsigned short).
UNS8 calcul_du_checksum_icmp(IcmpHeader_t icmp_frame,UNS8 data_buffer[ROUTER_ICMP_PAYLOAD_SIZE_C],UNS8 data_buffer_length)
{
	UNS8 buffer[ROUTER_ICMP_PAYLOAD_SIZE_C];
	UNS8 checksum;

	// ********************************************************
	// Initialisation du checksum
	// ********************************************************
	icmp_frame.nChecksum=0; // Doit être à 0 pour le calcul

	// ********************************************************
	// Calcul du ICMP
	// ********************************************************
	Memory_Copy8 (buffer,(UNS8*)&icmp_frame,sizeof(IcmpHeader_t));
	Memory_Copy8 (buffer+sizeof(IcmpHeader_t),data_buffer,data_buffer_length);
	checksum=calcul_du_checksum((UNS8*)buffer,sizeof(IcmpHeader_t)+data_buffer_length);

	return(checksum);
}

void ICMP_Ping_Echo_CMD (void)
{

}

void ICMP_Ping_Echo_ANSWER (Packet_t ReceiveData_p, UNS32 lReceiveDataSize_i, DriverReturnCode_t *ReturnCode_op)
{
	/* Declaration */
	Packet_t SendData_p;
	UNS8 lSendDataSize_i;

	/* Initialization */
	lSendDataSize_i = sizeof(EthernetFrame_t);
	Memory_Copy8  (&SendData_p,&ReceiveData_p,lReceiveDataSize_i);
	
	Memory_Copy8  (&SendData_p.EthernetFrame.Header.cDestMACAddress_a[0],&ReceiveData_p.EthernetFrame.Header.cSourceMACAddress_a[0],ROUTER_IP_LENGTH_C);
	Memory_Copy8  (&SendData_p.EthernetFrame.Header.cSourceMACAddress_a[0],&ReceiveData_p.EthernetFrame.Header.cDestMACAddress_a[0],ROUTER_IP_LENGTH_C);
	

	Memory_Copy8  (&SendData_p.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[0],&ReceiveData_p.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[0],ROUTER_IP_LENGTH_C);
	Memory_Copy8  (&SendData_p.EthernetFrame.Payload.IpPacket.Header.cSourceAddress_a[0],&ReceiveData_p.EthernetFrame.Payload.IpPacket.Header.cDestAddress_a[0],ROUTER_IP_LENGTH_C);
	

	SendData_p.EthernetFrame.Payload.IpPacket.Header.nHeaderChecksum=ReceiveData_p.EthernetFrame.Payload.IpPacket.Header.nHeaderChecksum;  /* TO BE DONE ??? !!! */
	SendData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType=ICMP_ECHOREPLY;
	SendData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.lHeaderData=ReceiveData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.lHeaderData;
	SendData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.nChecksum=calcul_du_checksum_icmp(SendData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header,&(SendData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a), (ReceiveData_p.EthernetFrame.Payload.IpPacket.Header.nTotalLength-ICMP_CHECKSUM_FRAME_OFFSET));  
	Memory_Copy8(&SendData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[0],&ReceiveData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a[0],ROUTER_ICMP_PAYLOAD_SIZE_C);

	/* Body */ 
	LAN9250_Write	(&SendData_p, sizeof(Packet_t), ReturnCode_op);

	/* Return Code */ 
}

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
	Packet_t SendData_p;
	Packet_t ReceiveData_p;

	/* Initialization */
    ReturnCode_op = DRVRC_NO_ERROR_E;
					
	//LAN9250_Write	( &SendData_p, lSendDataSize_i, &ReturnCode_op);
	/* Body */		 
	LAN9250_Read (&ReceiveData_p, sizeof(Packet_t), &ReturnCode_op);

	if (DRVRC_NO_ERROR_E==ReturnCode_op)
	{
		switch (ReceiveData_p.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.cType)
		{
		case ICMP_ECHOREPLY :
			/* Nothing to do */
			break; 

		case ICMP_DEST_UNREACH :
			/* Nothing to do */		
			break;

		case ICMP_SOURCE_QUENCH :
			/* Nothing to do */		
			break;

		case ICMP_REDIRECT :
			/* Nothing to do */		
			break;

		case ICMP_ECHO :
			/* Nothing to do */	
			ICMP_Ping_Echo_ANSWER(ReceiveData_p, sizeof(Packet_t), &ReturnCode_op);	
			break;

		case ICMP_TIME_EXCEEDED :
			/* Nothing to do */		
			break;

		case ICMP_PARAMETERPROB :
			/* Nothing to do */		
			break;

		case ICMP_TIMESTAMP :
			/* Nothing to do */		
			break;

		case ICMP_TIMESTAMPREPLY :
			/* Nothing to do */		
			break;

		case ICMP_INFO_REQUEST :
			/* Nothing to do */		
			break;

		case ICMP_INFO_REPLY :
			/* Nothing to do */		
			break;

		case ICMP_ADDRESS :
			/* Nothing to do */		
			break;

		case ICMP_ADDRESSREPLY :
			/* Nothing to do */		
			break;
		
		default:
			break;
		}
	}
	else
	{
		/* Nothing to be done */
	} 		

	/* Return Code */
	return(ReturnCode_op);
} 




/***************************************************************/
/* Global function : Zero_DataPayload_Generation                */
/***************************************************************/
DriverReturnCode_t Zero_DataPayload_Generation(void)
{
	/* Declaration */
	DriverReturnCode_t ReturnCode_op; 
	Packet_t Frame_Packet;
	UNS16 i=0; 

	/* Initialization */
    ReturnCode_op = DRVRC_NO_ERROR_E;

	/* Body */
	Memory_Copy8(&Frame_Packet.cData_a[0],&FRAME_EXAMPLE[0],sizeof(FRAME_EXAMPLE) );
 
	/* All data set to '0' in Payload */  
	for(i=0; i<(ROUTER_ETH_PAYLOAD_SIZE_C); i++)
	{
	 	Frame_Packet.EthernetFrame.Payload.cPayload_a[i]=0;
	}

	Frame_Packet.EthernetFrame.Header.nEtherType = ETHERNET_IPV4_TYPE;
	Frame_Packet.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.nChecksum=calcul_du_checksum_icmp(Frame_Packet.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header,&(Frame_Packet.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a), (Frame_Packet.EthernetFrame.Payload.IpPacket.Header.nTotalLength-ICMP_CHECKSUM_FRAME_OFFSET));   
	 
	LAN9250_Write	(&Frame_Packet, sizeof(Packet_t), &ReturnCode_op);

	/* Return Code */
	return(ReturnCode_op); 
}


/***************************************************************/
/* Global function : Random_DataPayload_Generation              */
/***************************************************************/
DriverReturnCode_t Random_DataPayload_Generation(void)
{
	/*  Declaration */
	DriverReturnCode_t ReturnCode_op; 
	Packet_t Frame_Packet;
	UNS16 i=0;
	UNS32 lCurrentTime;
	LAN9250_SystemMemory_t LAN9250SystemMemory;


	/* Initialization */
    ReturnCode_op = DRVRC_NO_ERROR_E;
	i=0;
	lCurrentTime=0;

	/* Body */
	Memory_Copy8(&Frame_Packet.cData_a[0],&FRAME_EXAMPLE[0],sizeof(FRAME_EXAMPLE) ); 


	for(i=0; i<(ROUTER_ETH_PAYLOAD_SIZE_C); i++)
	{
		ReadRegistersLAN9250(LAN9250_FREE_RUN_ADDR, &(LAN9250SystemMemory.SYSTEM_CSR.FREE_RUN.lReg));
		lCurrentTime = LAN9250SystemMemory.SYSTEM_CSR.FREE_RUN.lReg;
		Frame_Packet.EthernetFrame.Payload.cPayload_a[i] = (UNS8)lCurrentTime;
	}

	Frame_Packet.EthernetFrame.Header.nEtherType = ETHERNET_IPV4_TYPE;
	Frame_Packet.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header.nChecksum=calcul_du_checksum_icmp(Frame_Packet.EthernetFrame.Payload.IpPacket.Payload.Icmp.Header,&(Frame_Packet.EthernetFrame.Payload.IpPacket.Payload.Icmp.cData_a), (Frame_Packet.EthernetFrame.Payload.IpPacket.Header.nTotalLength-ICMP_CHECKSUM_FRAME_OFFSET));   
	 
	LAN9250_Write	(&Frame_Packet, sizeof(Packet_t), &ReturnCode_op);

	/* Return Code */
	return(ReturnCode_op); 
}
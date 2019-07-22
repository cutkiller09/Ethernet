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

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/
LAN9250_Instance_t LAN9250Instance; 

#define BYTE_ORDER BIG_ENDIAN

#if BYTE_ORDER == LITTLE_ENDIAN
# define ODDBYTE(v)	(v)
#elif BYTE_ORDER == BIG_ENDIAN
# define ODDBYTE(v)	((UNS8)(v) << 8)
#else
# define ODDBYTE(v)	htons((UNS8)(v) << 8)
#endif

/*****************************************************************************/
/* FUNCTION PROTOTYPE                                                        */
/*****************************************************************************/ 
void ICMP_Ping_Echo_ANSWER (IpPacket_t ReceiveData_ip, DriverReturnCode_t *ReturnCode_op);
                         
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

void ICMP_Ping_Echo_ANSWER (IpPacket_t ReceiveData_ip, DriverReturnCode_t *ReturnCode_op)
{
	/* Declaration */
	IpPacket_t SendData_ip;
	UNS8 lSendDataSize_i;

	/* Initialization */
	lSendDataSize_i = sizeof(EthernetFrame_t);
	Memory_Copy8  (&SendData_ip.Header.cDestAddress_a[0],&ReceiveData_ip.Header.cSourceAddress_a[0],ROUTER_IP_LENGTH_C);
	Memory_Copy8  (&SendData_ip.Header.cSourceAddress_a[0],&ReceiveData_ip.Header.cDestAddress_a[0],ROUTER_IP_LENGTH_C);
	SendData_ip.Header.cProtocol=ReceiveData_ip.Header.cProtocol;
	SendData_ip.Header.cServiceType=ReceiveData_ip.Header.cServiceType;
	SendData_ip.Header.cTimeToLive=ReceiveData_ip.Header.cTimeToLive;
	SendData_ip.Header.cVersion_IHL=ReceiveData_ip.Header.cVersion_IHL;
	SendData_ip.Header.nFlags_FOffset=ReceiveData_ip.Header.nFlags_FOffset; 

	SendData_ip.Header.nHeaderChecksum=ReceiveData_ip.Header.nHeaderChecksum;  /* TO BE DONE ??? !!! */
	SendData_ip.Header.nIdentification=ReceiveData_ip.Header.nIdentification;
	SendData_ip.Header.nTotalLength=ReceiveData_ip.Header.nTotalLength; 
	SendData_ip.Payload.Icmp.Header.cCode=ReceiveData_ip.Payload.Icmp.Header.cCode;
	SendData_ip.Payload.Icmp.Header.cType=ICMP_ECHOREPLY;
	SendData_ip.Payload.Icmp.Header.lHeaderData=ReceiveData_ip.Payload.Icmp.Header.lHeaderData;
	SendData_ip.Payload.Icmp.Header.nChecksum=calcul_du_checksum_icmp(SendData_ip.Payload.Icmp.Header,&(SendData_ip.Payload.Icmp.cData_a), (ReceiveData_ip.Header.nTotalLength-36));  /* 36 TO BE DEFINE */
	Memory_Copy8(&SendData_ip.Payload.Icmp.cData_a[0],&ReceiveData_ip.Payload.Icmp.cData_a[0],ROUTER_ICMP_PAYLOAD_SIZE_C);

	/* Body */ 
	LAN9250_Write	((void *)&LAN9250Instance, &SendData_ip, sizeof(IpPacket_t), ReturnCode_op);

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
	IpPacket_t SendData_ip;
	IpPacket_t ReceiveData_ip;

	/* Initialization */
    ReturnCode_op = DRVRC_NO_ERROR_E;
					
	//LAN9250_Write	((void *)&LAN9250Instance, &SendData_ip, lSendDataSize_i, &ReturnCode_op);
	/* Body */		 
	LAN9250_Read ((void *)&LAN9250Instance, &ReceiveData_ip, sizeof(IpPacket_t), &ReturnCode_op);

	if (DRVRC_NO_ERROR_E==ReturnCode_op)
	{
		switch (ReceiveData_ip.Payload.Icmp.Header.cType)
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
			ICMP_Ping_Echo_ANSWER(ReceiveData_ip, &ReturnCode_op);	
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

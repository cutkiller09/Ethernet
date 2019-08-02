/*****************************************************************************/
/* INCLUDE HEADER                                                            */
/*****************************************************************************/
/*
  MODULE:      Router
  PROJECT:     LaosRouterModules

  DESCRIPTION: 
  This module implements network communication functionality and
  performs handling of basic network services (ARP, ICMP).

  Copyright (C) by Liebherr-Aerospace Lindenberg GmbH
******************************************************************************/

#ifndef __PACKET_H__  /* test for multiple inclusion */
#define __PACKET_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/

/* ---- From supplier classes / modules ------------------------------------ */
#include "standard.h"

/* ---- From sub-classes --------------------------------------------------- */
#include "RouterDefines_public.h"

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

typedef struct ArpHeader_tag
{
    UNS16   nHWType;
    UNS16   nPrType;
    UNS8    cHWLength;
    UNS8    cPrLength;
    UNS16   nOperation;
    UNS8    cSenderHWAddress_a[ROUTER_MAC_LENGTH_C];
    UNS8    cSenderPrAddress_a[ROUTER_IP_LENGTH_C];
    UNS8    cTargetHWAddress_a[ROUTER_MAC_LENGTH_C];
    UNS8    cTargetPrAddress_a[ROUTER_IP_LENGTH_C];
} ArpHeader_t;

/* [Code-2F7BC412-Router::UdpHeader] */
/* [Covers: ] */
typedef struct UdpHeader_tag
{
    UNS16   nSourcePort;
    UNS16   nDestPort;
    UNS16   nLength;
    UNS16   nChecksum;
} UdpHeader_t;

/* [Code-DCDAC95D-Router::UdpFind] */
/* [Covers: ] */
typedef struct UdpFind_tag
{
    UNS16   nOpCode;
    UNS8    cData_a[ROUTER_FIND_PAYLOAD_SIZE_C];
} UdpFind_t;

/* [Code-CA462703-Router::UdpPayload] */
/* [Covers: ] */
typedef union UdpPayload_tag
{
    UNS8     cData_a[ROUTER_UDP_PAYLOAD_SIZE_C];
    UdpFind_t   Find;
} UdpPayload_t;

/* [Code-E51D2152-Router::UdpPacket] */
/* [Covers: ] */
typedef struct UdpPacket_tag
{
    UdpHeader_t    Header;
    UdpPayload_t   Payload;
} UdpPacket_t;

/* [Code-1BF1285F-Router::IcmpHeader] */
/* [Covers: ] */
typedef struct IcmpHeader_tag
{
    UNS8    cType;
    UNS8    cCode;
    UNS16   nChecksum;
    UNS32   lHeaderData;
} IcmpHeader_t;

/* [Code-79AF8AC9-Router::IcmpPacket] */
/* [Covers: ] */
typedef struct IcmpPacket_tag
{
    IcmpHeader_t   Header;
    UNS8        cData_a[ROUTER_ICMP_PAYLOAD_SIZE_C];
} IcmpPacket_t;

/* [Code-9E228353-Router::IpPayload] */
/* [Covers: ] */
typedef union IpPayload_tag
{
    UNS8        cData_a[ROUTER_IP_PAYLOAD_SIZE_C];
    IcmpPacket_t   Icmp;
    UdpPacket_t    Udp;
} IpPayload_t;

/* [Code-DBFAD6F5-Router::IpHeader] */
/* [Covers: ] */
typedef struct IpHeader_tag
{
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
} IpHeader_t;

/* [Code-3E84AEA2-Router::IpPacket] */
/* [Covers: ] */
typedef struct IpPacket_tag
{
    IpHeader_t    Header;
    IpPayload_t   Payload;
} IpPacket_t;

/* [Code-35123698-Router::EthernetPayload] */
/* [Covers: ] */
typedef union EthernetPayload_tag
{
    UNS8        cPayload_a[ROUTER_ETH_PAYLOAD_SIZE_C];
    UNS8        cIpPacket_a[ROUTER_ETH_PAYLOAD_SIZE_C];
    UNS8        cArpHeader_a[ROUTER_ETH_PAYLOAD_SIZE_C];
    IpPacket_t  IpPacket;
} EthernetPayload_t;

/* [Code-10293034-Router::EthernetHeader] */
/* [Covers: ] */
typedef struct EthernetHeader_tag
{
    UNS8    cDestMACAddress_a[ROUTER_MAC_LENGTH_C];
    UNS8    cSourceMACAddress_a[ROUTER_MAC_LENGTH_C];
    UNS16   nEtherType;
} EthernetHeader_t;

/* [Code-F425EE14-Router::EthernetFrame] */
/* [Covers: ] */
typedef struct EthernetFrame_tag
{
    EthernetHeader_t    Header;
    EthernetPayload_t   Payload;
} EthernetFrame_t;


/* ---- Master Class ------------------------------------------------------- */
/* [Code-1EF3F7AC-Router::Packet] */
/* [Covers: ] */
typedef union Packet_tag
{
    UNS8           cData_a[ROUTER_PACKET_SIZE_C];
    EthernetFrame_t   EthernetFrame;
} Packet_t;

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
#endif /*__PACKET_H__*/

/* EOF */


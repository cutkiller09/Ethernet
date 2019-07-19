/*****************************************************************************/
/* MODULE HEADER                                                             */
/*****************************************************************************/
/*
  MODULE:      Router
  PROJECT:     LaosRouterModules

  DESCRIPTION: 
  This module implements network communication functionality and
  performs handling of basic network services (ARP, ICMP).
  
  Copyright (C) by Liebherr-Aerospace Lindenberg GmbH
******************************************************************************/

#ifndef __ROUTERDEFINES_PUBLIC_H__  /* test for multiple inclusion */
#define __ROUTERDEFINES_PUBLIC_H__

/*****************************************************************************/
/* SPECIAL MODULE DEFINITIONS                                                */
/*****************************************************************************/
/* [Code-630E9DBF-Router::RouterDefines.public] */
/* [Covers: ] */

#define ROUTER_IP_LENGTH_C ((UNS16) (4U))
#define ROUTER_MAC_LENGTH_C ((UNS16) (6U))
#define ROUTER_HW_ID_SIZE_C ((UNS16) (16U))
#define ROUTER_HW_TYPE_SIZE_C ((UNS16) (9U))
#define ROUTER_HW_POS_SIZE_C ((UNS16) (9U))
#define ROUTER_HW_NAME_SIZE_C ((UNS16) (21U))
#define ROUTER_HW_MAN_SIZE_C ((UNS16) (4U))
#define ROUTER_PACKET_SIZE_C ((UNS16) (1518U))
#define ROUTER_ETH_PAYLOAD_SIZE_C ((UNS16) (8U)) //((UNS16) (1500U))
#define ROUTER_IP_PAYLOAD_SIZE_C ((UNS16) (556U))
#define ROUTER_ICMP_PAYLOAD_SIZE_C ((UNS16) (548U))
#define ROUTER_UDP_PAYLOAD_SIZE_C ((UNS16) (512U))
#define ROUTER_FIND_PAYLOAD_SIZE_C ((UNS16) (60U))
#define ROUTER_ETH_HEADER_SIZE_C ((UNS32) (14U))
#define ROUTER_IP_HEADER_SIZE_C ((UNS32) (20U))
#define ROUTER_UDP_HEADER_SIZE_C ((UNS32) (8U))

#endif /*__ROUTERDEFINES_PUBLIC_H__*/

/* EOF */


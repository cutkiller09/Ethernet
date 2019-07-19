/*****************************************************************************/
/* INCLUDE HEADER                                                            */
/*****************************************************************************/
/*
  MODULE:    
  PROJECT:   F6X 

  DESCRIPTION:
  This module implements ICMP of the LAN9250 controller driver.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/

#ifndef __IP_ICMP_H__  /* test for multiple inclusion */
#define __IP_ICMP_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/
#include "standard.h"
#include "LAN9250.h"

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */
 

/*
 * Lower bounds on packet lengths for various types.
//  * For the error advice packets must first insure that the
//  * packet is large enough to contain the returned ip header.
//  * Only then can we do the check to see if 64 bits of packet
//  * data have been returned, since we need to check the returned
//  * ip header length.
//  */
// #define    ICMP_MINLEN    8                /* abs minimum */
// #define    ICMP_TSLEN    (8 + 3 * sizeof (n_time))    /* timestamp */
// #define    ICMP_MASKLEN    12                /* address mask */
// #define    ICMP_ADVLENMIN    (8 + sizeof (struct ip) + 8)    /* min */

// /* Definition of type and code fields. */
// /* defined above: ICMP_ECHOREPLY, ICMP_REDIRECT, ICMP_ECHO */
// #define    ICMP_UNREACH        3        /* dest unreachable, codes: */
// #define    ICMP_SOURCEQUENCH    4        /* packet lost, slow down */
// #define    ICMP_ROUTERADVERT    9        /* router advertisement */
// #define    ICMP_ROUTERSOLICIT    10        /* router solicitation */
// #define    ICMP_TIMXCEED        11        /* time exceeded, code: */
// #define    ICMP_PARAMPROB        12        /* ip header bad */
// #define    ICMP_TSTAMP        13        /* timestamp request */
// #define    ICMP_TSTAMPREPLY    14        /* timestamp reply */
// #define    ICMP_IREQ        15        /* information request */
// #define    ICMP_IREQREPLY        16        /* information reply */
// #define    ICMP_MASKREQ        17        /* address mask request */
// #define    ICMP_MASKREPLY        18        /* address mask reply */

// #define    ICMP_MAXTYPE        18

// /* UNREACH codes */
// #define    ICMP_UNREACH_NET            0    /* bad net */
// #define    ICMP_UNREACH_HOST            1    /* bad host */
// #define    ICMP_UNREACH_PROTOCOL            2    /* bad protocol */
// #define    ICMP_UNREACH_PORT            3    /* bad port */
// #define    ICMP_UNREACH_NEEDFRAG            4    /* IP_DF caused drop */
// #define    ICMP_UNREACH_SRCFAIL            5    /* src route failed */
// #define    ICMP_UNREACH_NET_UNKNOWN        6    /* unknown net */
// #define    ICMP_UNREACH_HOST_UNKNOWN       7    /* unknown host */
// #define    ICMP_UNREACH_ISOLATED            8    /* src host isolated */
// #define    ICMP_UNREACH_NET_PROHIB            9    /* net denied */
// #define    ICMP_UNREACH_HOST_PROHIB        10    /* host denied */
// #define    ICMP_UNREACH_TOSNET            11    /* bad tos for net */
// #define    ICMP_UNREACH_TOSHOST            12    /* bad tos for host */
// #define    ICMP_UNREACH_FILTER_PROHIB      13    /* admin prohib */
// #define    ICMP_UNREACH_HOST_PRECEDENCE    14    /* host prec vio. */
// #define    ICMP_UNREACH_PRECEDENCE_CUTOFF  15    /* prec cutoff */

// /* REDIRECT codes */
// #define    ICMP_REDIRECT_NET    0        /* for network */
// #define    ICMP_REDIRECT_HOST    1        /* for host */
// #define    ICMP_REDIRECT_TOSNET    2        /* for tos and net */
// #define    ICMP_REDIRECT_TOSHOST    3        /* for tos and host */

// /* TIMEXCEED codes */
// #define    ICMP_TIMXCEED_INTRANS    0        /* ttl==0 in transit */
// #define    ICMP_TIMXCEED_REASS    1        /* ttl==0 in reass */

// /* PARAMPROB code */
// #define    ICMP_PARAMPROB_OPTABSENT 1        /* req. opt. absent */
 
/* ---- Basic Types -------------------------------------------------------- */

/* ---- Embedded Classes --------------------------------------------------- */
// typedef struct {
//   UNS8    Type;
//   UNS8    Code;
//   UNS16    Checksum;
//   union {
//         struct {
//                 UNS16    Id;
//                 UNS16    Sequence;
//         } echo;
//         UNS32    Gateway;
//         struct {
//                 UNS16    Unused;
//                 UNS16    Mtu;
//         } frag;
//   } un;
// }T_ICMP_HDR;


// /*
//  * Internal of an ICMP Router Advertisement
//  */
// struct icmp_ra_addr
// {
//   UNS32 ira_addr;
//   UNS32 ira_preference;
// };

// struct icmp
// {
//   UNS8  icmp_type;    /* type of message, see below */
//   UNS8  icmp_code;    /* type sub code */
//   UNS16 icmp_cksum;    /* ones complement checksum of struct */
//   union
//   {
//     UNS8 ih_pptr;        /* ICMP_PARAMPROB */
//     struct in_addr ih_gwaddr;    /* gateway address */
//     struct ih_idseq        /* echo datagram */
//     {
//       UNS16 icd_id;
//       UNS16 icd_seq;
//     } ih_idseq;
//     UNS32 ih_void;

//     /* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
//     struct ih_pmtu
//     {
//       UNS16 ipm_void;
//       UNS16 ipm_nextmtu;
//     } ih_pmtu;

//     struct ih_rtradv
//     {
//       UNS8 irt_num_addrs;
//       UNS8 irt_wpa;
//       UNS16 irt_lifetime;
//     } ih_rtradv;
//   } icmp_hun;
 
//   union
//   {
//     struct
//     {
//       UNS32 its_otime;
//       UNS32 its_rtime;
//       UNS32 its_ttime;
//     } id_ts;
//     struct
//     {
//       struct ip idi_ip;
//       /* options and then 64 bits of data */
//     } id_ip;
//     struct icmp_ra_addr id_radv;
//     UNS32   id_mask;
//     UNS8    id_data[1];
//   } icmp_dun;
 
/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
DriverReturnCode_t Manage_ICMP (void);

#endif /*__IP_ICMP_H__*/

/* EOF */ 
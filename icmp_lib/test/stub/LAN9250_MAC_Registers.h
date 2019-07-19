/*****************************************************************************/
/* INCLUDE HEADER                                                            */
/*****************************************************************************/
/*
  MODULE:     
  PROJECT:   F6X  

  DESCRIPTION: 
  This module implements interface of the LAN9250 controller driver.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/

#ifndef __LAN9250_HMAC_REGISTERS_H__  /* test for multiple inclusion */
#define __LAN9250_HMAC_REGISTERS_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/
#include "standard.h"

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */

/* ---- Basic Types -------------------------------------------------------- */

/* ---- Embedded Classes --------------------------------------------------- */
/* [Code-59A49FB3-LAN9250::LAN9250_HMAC_Reg_Index] */
/* [Covers: ] */
typedef enum LAN9250_HMAC_Reg_Index_tag
{
    LAN9250_HMAC_CR_E                    	  = 1,  /* Host MAC Control Register (HMAC_CR)*/
    LAN9250_HMAC_ADDRH_E                      = 2,  /* Host MAC Address High Register (HMAC_ADDRH) */
    LAN9250_HMAC_ADDRL_E                      = 3,  /* Host MAC Address Low Register (HMAC_ADDRL) */
    LAN9250_HMAC_HASHH_E                      = 4,  /* Host MAC Multicast Hash Table High Register (HMAC_HASHH) */
    LAN9250_HMAC_HASHL_E                      = 5,  /* Host MAC Multicast Hash Table Low Register (HMAC_HASHL) */
    LAN9250_HMAC_MII_ACC_E                    = 6,  /* Host MAC MII Access Register (HMAC_MII_ACC) */
    LAN9250_HMAC_MII_DATA_E                   = 7,  /* Host MAC MII Data Register (HMAC_MII_DATA) */
    LAN9250_HMAC_FLOW_E                       = 8,  /* Host MAC Flow Control Register (HMAC_FLOW) */
    LAN9250_HMAC_VLAN1_E                      = 9,  /* Host MAC VLAN1 Tag Register (HMAC_VLAN1) */
    LAN9250_HMAC_VLAN2_E                      = 10, /* Host MAC VLAN2 Tag Register (HMAC_VLAN2) */ 
    LAN9250_HMAC_WUFF_E                       = 11, /* Host MAC Wake-up Frame Filter Register (HMAC_WUFF) */
    LAN9250_HMAC_WUCSR_E                      = 12, /* Host MAC Wake-up Control and Status Register (HMAC_WUCSR) */
    LAN9250_HMAC_COE_CR_E                     = 13, /* Host MAC Checksum Offload Engine Control Register (HMAC_COE_CR) */
    LAN9250_HMAC_EEE_TW_TX_SYS_E              = 14, /* Host MAC EEE Time Wait TX System Register (HMAC_EEE_TW_TX_SYS) */
    LAN9250_HMAC_HMAC_EEE_TX_LPI_REQ_DELAY_E  = 15  /* Host MAC EEE TX LPI Request Delay Register (HMAC_EEE_TX_LPI_REQ_DELAY) */
} LAN9250_HMAC_Reg_Index_t;


/* ---- Master Class ------------------------------------------------------- */
/* [Code-5339B0FE-LAN9250::LAN9250_HMAC_Registers] */
/* [Covers: ] */
typedef struct LAN9250_HMAC_Registers_tag
{
        /*#ACD# M(UDMF::UID_5339B0FE-2745-4371-BCB2-94CF6F8C7AC8_AttributesByHand) LAN9250_HMAC_Registers */
    /* HMAC Control Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 RX_ALL_MODE     :1; /* Receive All Mode R/W */
            UNS32 Reserved0       :5; /* reserved, bit 30:26 RO */
            UNS32 HMAC_EEE_ENABLE :1; /* Host MAC Energy Efficient Ethernet R/W*/
            UNS32 Reserved1       :1; /* reserved, bit 24 RO */
            UNS32 DIS_RX_OWN      :1; /* Disable receive own R/W */
            UNS32 Reserved2       :1; /* reserved, bit 22 RO */
            
            UNS32 LOOPBACK        :1; /* Loopback operation mode R/W */
            UNS32 FULL_DPX_MODE   :1; /* Full Duplex Mode R/W*/
            UNS32 PASS_ALL_MC     :1; /* Pass All Multicast R/W */
            UNS32 PROMISCUOUS     :1; /* Promiscuous Mode R/W */
            UNS32 INV_FILT        :1; /* Inverse filtering R/W */
            UNS32 PASS_BAD_FR     :1; /* Pass Bad Frames R/W */
            
            UNS32 HASH_ONLY_FILT  :1; /* Hash Only Filter mode R/W */
            UNS32 Reserved3       :1; /* reserved, bit 14 RO */
            UNS32 HASH_PERF_FILT  :1; /* Hash Perfect Filter Mode R/W */
            UNS32 Reserved4       :1; /* reserved, bit 12 RO */
            UNS32 DIS_BC_FRAME    :1; /* Disable Broadcast Frames R/W */
            UNS32 DIS_RETRY       :1; /* Disable Retry R/W */
            UNS32 Reserved5       :1; /* reserved, bit 9 RO */
            
            UNS32 PAD_STRIP       :1; /* Atomatic Pad Stripping R/W */
            UNS32 BACK_OFF_LIMIT  :2; /* BackOff Limit R/W */
            UNS32 DEFERRAL_CHECK  :1; /* Deferral Check R/W */
            UNS32 Reserved6       :1; /* reserved, bit 4 RO */
            UNS32 TX_EN           :1; /* Transmitter Enable R/W */
            UNS32 RX_EN           :1; /* Receiver Enable R/W */
            UNS32 Reserved7       :2; /* reserved, bit 1:0 RO */
        } Bit;
    } HMAC_CR; /* HMAC Control Register: establishes the RX and TX operation modes */
               /* and controls for address filtering and packet filtering         */

    /* Host MAC Address High Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0   :16; /* reserved, bit 31:16 RO */
            UNS32 HMAC_ADDR_H :16; /* Upper 16 bits[47:32] of the 48-bit HMAC Physical Address R/W */
        } Bit;
    } ADDR_H; /* HMAC Address High Register: contains the upper 16-bits of the */
              /* physical address of the HMAC                                  */

    /* Host MAC Address Low Register */
    union {
        UNS32 lReg; /* Lower 32 bits[31:0] of the 48-bit HMAC Physical Address R/W */
    } ADDR_L; /* HMAC Address Low Register: contains the lower 32 bits of the */
              /* physical address of the HMAC                                 */

    /* Host MAC Multicast Hash Table High Register */
    union {
        UNS32 lReg; /* Upper 32 bits of the 64-bit Hash Table R/W */
    } HASH_H; /* Multicast Hash Table High Register: contains the higher */
              /* 32-bits of the Multicast Hash Table                     */

    /* Host MAC Multicast Hash Table Low Register */
    union {
        UNS32 lReg; /* Lower 32 bits of the 64-bit Hash Table R/W */
    } HASH_L; /* Multicast Hash Table Low Register: defines the lower 32-bits */
              /* of the Multicast Hash Table                                  */

    /* Host MAC MII Access Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0     :16; /* reserved, bit 31:16 RO */
            UNS32 PHY_ADDR      :5;  /* PHY Address R/W */
            UNS32 MII_REG_INDEX :5;  /* MII Register Index R/W */
            UNS32 Reserved1     :4;  /* reserved, bit 5:2 RO */
            UNS32 MII_WRITE     :1;  /* MII Write/Read command R/W */
            UNS32 MII_BUSY      :1;  /* MII Busy RO SC */
        } Bit;
    } MII_ACC; /* MII Access Register: is used in conjunction with the Host MAC MII Data Register */
               /* to access the internal PHY registers.                                            */

    /* Host MAC MII Data Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0 :16; /* reserved, bit 31:16 RO */
            UNS32 MII_DATA  :16; /* MII Data R/W */
        } Bit;
    } MII_DATA; /* MII Data Register: contains either the data to be written */
                /* to the PHY register specified in the MII Access Register  */
                /* (MII_ACC), or the read data from the PHY register whose   */
                /* index is specified in the MII Access Register             */

    /* Host MAC Flow Control Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 FC_PAUSE_TIME :16; /* Pause Time R/W */
            UNS32 Reserved0     :13; /* reserved, bit 15:3 RO */
            UNS32 FC_PASS_CF    :1;  /* Pass Control Frame R/W */
            UNS32 FC_EN         :1;  /* Flow Control Enable R/W */
            UNS32 FC_BUSY       :1;  /* FLOW Control Busy R/W SC */
        } Bit;
    } FLOW; /* Flow Control Register: controls the generation and reception     */
            /* of the Control (Pause Command) frames by the HMAC's flow control */
            /* block                                                            */

    /* Host MAC VLAN1 Tag Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0 :16; /* reserved, bit 31:16 RO */
            UNS32 VTI1      :16; /* VLAN1 Tag Identifier R/W */
        } Bit;
    } VLAN1; /* VLAN1 Tag Register: contains the VLAN tag field to identify */
             /* the VLAN1 frames                                             */

    /* Host MAC VLAN2 Tag Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0 :16; /*reserved, bit 31:16 RO */
            UNS32 VTI2      :16; /* VLAN2 Tag Identifier R/W */
        } Bit;
    } VLAN2; /* VLAN2 Tag Register: contains the VLAN tag field to identify */
             /* the VLAN2 frames                                             */

    /* Host MAC Wake-up Frame Filter Register */
    union {
        UNS32 lReg; /* Wake-Up Frame Filter R/W */
    } WUFF; /* Wake-Up Frame Filter: is used to configure the wake up frame filter */

    /* Host MAC Wake-up Control and Status Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 WFF_PTR_RST    :1;  /* WFF Pointer Reset SC */
            UNS32 Reserved0      :21; /* reserved, bit 30:10 RO */
            UNS32 GU_EN          :1;  /* Global Unicast Enable R/W */
            UNS32 WOL_WAIT_SLEEP :1;  /* WoL Wait for Sleep R/W */
            UNS32 PFDA_FR        :1;  /* Perfect DA Frame Received R/WC */
            UNS32 WUFR              :1;  /* Remote Wake-Up Frame Received R/WC */
            UNS32 MPR               :1;  /* Magic Packet Received R/WC */
            UNS32 BCAST_FR       :1;  /* Broadcast Frame Received R/WC */
            UNS32 PFDA_EN        :1;  /* Perfect DA Wakeup Enable R/W */
            UNS32 WUEN              :1;  /* Wake-Up Frame Enable R/W */
            UNS32 MPEN           :1;  /* Magic Packet Enable R/W */
            UNS32 BCST_EN        :1;  /* Broadcast Wakeup Enable R/W */
        } Bit;
    } WUCSR; /* Wake-Up Control and Status Register: contains data and control settings */ 
             /* pertaining to the HMAC's remote wake-up status and capabilities         */
             
    /* Host MAC Checksum Offload Engine Control Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0   :15; /* reserved, bit 31:17 RO */
            UNS32 TX_COE_EN   :1; /* TX Checksum Offload Engine Enable R/W */
            UNS32 Reserved1   :14; /* reserved, bit 15:2 RO */
            UNS32 RX_COE_MODE :1;  /* PRX Checksum Offload Engine Mode R/W */
            UNS32 RX_COE_EN   :1;  /* RX Checksum Offload Engine Enable R/W */
        } Bit;
    } HMAC_COE_CR; /* This register controls the RX and TX checksum offload engines. */
    
    /* Host MAC EEE Time Wait TX System Register */
    union {
        UNS32 lReg;
        struct {
            UNS32 Reserved0             :8;  /* reserved, bit 31:24 RO */
            UNS32 TX_DELAY_AFT_LPI_RMV :24; /* TX Delay After TX LPI Removal R/W */
        } Bit;
    } HMAC_EEE_TW_TX_SYS; /* This register configures the time to wait before starting packet */
                          /* transmission after TX LPI removal.                               */

    /* Host MAC EEE TX LPI Request Delay Register */
    union {
        UNS32 lReg; /* EEE TX LPI Request Delay R/W */
    } HMAC_EEE_TX_LPI_REQ_DELAY; /* This register contains the amount of time, in microseconds, */
                                 /* the Host MAC must wait after the TX FIFO is empty before    */
                                 /* invoking the LPI protocol.                                     */
                                 
    /*#end ACD# LAN9250_HMAC_Registers */
} LAN9250_HMAC_Registers_t;

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
#endif /*__LAN9250_HMAC_REGISTERS_H__*/

/* EOF */


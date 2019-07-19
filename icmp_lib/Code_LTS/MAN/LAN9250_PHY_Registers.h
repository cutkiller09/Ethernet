/*****************************************************************************/
/* INCLUDE HEADER                                                            */
/*****************************************************************************/
/*
  MODULE :     
  PROJECT:   F6X  

  DESCRIPTION: 
  This module implements interface of the LAN9250 controller driver.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/

#ifndef __LAN9250_PHY_REGISTERS_H__  /* test for multiple inclusion */
#define __LAN9250_PHY_REGISTERS_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/


/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */

/* ---- Basic Types -------------------------------------------------------- */

/* ---- Embedded Classes --------------------------------------------------- */
/* [Code-C21FFF84-LAN9250::LAN9250_PHY_Reg_Index] */
/* [Covers: ] */
typedef enum LAN9250_PHY_Reg_Index_tag
{
    LAN9250_PHY_BASIC_CONTROL_E            = 0,  /* PHY Basic Control Register */
    LAN9250_PHY_BASIC_STATUS_E                = 1,  /* PHY Basic Status Register */
    LAN9250_PHY_ID_MSB_E                        = 2,  /* PHY Identification MSB Register */
    LAN9250_PHY_ID_LSB_E                     = 3,  /* PHY Identification LSB Register */
    LAN9250_PHY_AN_ADV_E                     = 4,  /* PHY Auto-Negotiation Advertisement Register */
    LAN9250_PHY_AN_LP_BASE_ABILITY_E         = 5,  /* PHY Auto-Negotiation Link Partner Base Page Ability Register */
    LAN9250_PHY_AN_EXP_E                     = 6,  /* PHY Auto-Negotiation Expansion Register */
    LAN9250_PHY_AN_NP_TX_E                 = 7,  /* PHY Auto Negotiation Next Page TX Register */
    LAN9250_PHY_AN_NP_RX_E                   = 8,  /* PHY Auto Negotiation Next Page RX Register */
    LAN9250_PHY_MMD_ACCESS_E                 = 13, /* PHY MMD Access Control Register */
    LAN9250_PHY_MMD_ADDR_DATA_E            = 14, /* PHY MMD Access Address/Data Register */
    LAN9250_PHY_EDPD_CFG_E                    = 16, /* PHYEDPD NLP / Crossover Time / EEE Configuration Register */
    LAN9250_PHY_MODE_CONTROL_STATUS_E      = 17, /* PHY Mode Control/Status Register */
    LAN9250_PHY_SPECIAL_MODES_E            = 18, /* PHY Special Modes Register */
    LAN9250_PHY_TDR_PAT_DELAY_E            = 24, /* PHY TDR Patterns/Delay Control Register */
    LAN9250_PHY_TDR_CONTROL_STAT_E            = 25, /* PHY TDR Control/Status Register */
    LAN9250_PHY_SYMBOL_ERROR_CNT_E            = 26, /* PHY Symbol Error Counter Register*/
    LAN9250_PHY_SPECIAL_CONTROL_STAT_IND_E = 27, /* PHY Special Control/Status Indication Register */
    LAN9250_PHY_CABLE_LEN_E                = 28, /* PHY Cable Length Register */
    LAN9250_PHY_INTERRUPT_SOURCE_E            = 29, /* PHY Interrupt Source Flags Register */
    LAN9250_PHY_INTERRUPT_MASK_E            = 30, /* PHY Interrupt Mask Register */
    LAN9250_PHY_SPECIAL_CONTROL_STATUS_E   = 31  /* PHY Special Control/Status Register */
} LAN9250_PHY_Reg_Index_t;


/* ---- Master Class ------------------------------------------------------- */
/* [Code-529C184D-LAN9250::LAN9250_PHY_Registers] */
/* [Covers: ] */
typedef struct LAN9250_PHY_Registers_tag
{
        /*#ACD# M(UDMF::UID_529C184D-475A-4baa-A272-AA2E478701D4_AttributesByHand) LAN9250_PHY_Registers */
    /* PHY Basic Control Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 PHY_SRST		 	:1; /* Soft Reset R/W SC */
            UNS16 PHY_LOOPBACK   	:1; /* Loopback R/W */
            UNS16 PHY_SPEED_SEL_LSB :1; /* Speed Select LSB R/W */
            UNS16 PHY_AN     		:1; /* Auto-Negotiation Enable R/W */
            UNS16 PHY_PWR_DWN     	:1; /* Power Down R/W */
            UNS16 Reserved0      	:1; /* reserved, bit 10 RO */
            UNS16 PHY_RST_AN    	:1; /* Restart Auto-Negotiate R/W SC */
            UNS16 PHY_DUPLEX   	 	:1; /* Duplex Mode R/W */
            UNS16 PHY_COL_TEST    	:1; /* Collision Test Mode R/W */
            UNS16 Reserved1      	:7; /* reserved, bit 6:0 RO */
        } Bit;
    } PHY_BASIC_CONTROL; /* Basic Control Register: is used to configure the PHY. */

    /* PHY Basic Status Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 _100BASE_T4      :1; /* 100Base-T4 RO */
            UNS16 _100BASE_X_FDPX  :1; /* 100Base-X Full Duplex RO */
            UNS16 _100BASE_X_HDPX  :1; /* 100Base-X Half Duplex RO */
            UNS16 _10BASE_T_FDPX   :1; /* 10Base-T Full Duplex RO */
            UNS16 _10BASE_T_HDPX   :1; /* 10Base-T Half Duplex RO */
            UNS16 _100BASE_T2_FDPX :1; /* 100Base-T2 Full Duplex RO */
            UNS16 _100BASE_T2_HDPX :1; /* 100Base-T2 Half Duplex RO */
            UNS16 EXT_STS          :1; /* Extended Status RO */
            UNS16 UNIDIR_ABLT      :1; /* Unidirectional Ability RO */
            UNS16 MF_PRE_SUPPR     :1; /* MF Preamble Suppression RO */
            UNS16 AUTONEG_COMPLETE :1; /* Auto-Negotiation Complete RO */
            UNS16 REMOTE_FAULT     :1; /* Remote Fault RO/LH */
            UNS16 AUTONEG_ABLT     :1; /* Auto-Negotiation Ability RO */
            UNS16 LINK_STATUS      :1; /* Link Status RO/LL */
            UNS16 JABBER_DETECT    :1; /* Jabber Detect RO/LH*/
            UNS16 EXT_CAPABLE      :1; /* Extended Capabilities RO */
        } Bit;
    } PHY_BASIC_STATUS; /* Basic Status Register: is used to monitor the status of the PHY. */

    /* PHY Identification MSB Register */
    union {
        UNS16 nReg; /* PHY ID */
    } PHY_ID_MSB; /* PHY Identification MSB Register:contains the MSB            */
                  /* of the Organizationally Unique Identifier (OUI) for the PHY */

    /* PHY Identification LSB Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 PHY_ID   :6; /* PHY ID Number R/W */
            UNS16 MODEL_ID :6; /* Model Number R/W */
            UNS16 REV_ID   :4; /* Revision Number R/W */
        } Bit;
    } PHY_ID_LSB; /* PHY Identification LSB Register: contains the LSB of the */
                  /* Organizationally Unique Identifier (OUI) for the PHY     */
    
    /* PHY Auto-Negotiation Advertisement Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 NEX_PAGE        :1; /* Next Page R/W */
            UNS16 Reserved0       :1; /* reserved, bit 14 RO */
            UNS16 REMOTE_FAULT    :1; /* Remote Fault R/W */
            UNS16 EXT_NEX_PAGE    :1; /* Extended Next Page R/W */
            UNS16 ASYM_PAUSE      :1; /* Asymmetric Pause R/W */
            UNS16 SYM_PAUSE       :1; /* Symmetric Pause R/W */
            UNS16 Reserved1       :1; /* reserved,  bit 9 RO */
            UNS16 _100BASE_X_FDPX :1; /* 100BASE-X Full Duplex R/W */
            UNS16 _100BASE_X_HDPX :1; /* 100BASE-X Half Duplex R/W */
            UNS16 _10BASE_T_FDPX  :1; /* 10BASE-T Full Duplex R/W */
            UNS16 _10BASE_T_HDPX  :1; /* 10BASE-T Half Duplex R/W */
            UNS16 SELECTOR_FIELD  :5; /* Selector Field R/W */
        } Bit;
    } PHY_AN_ADV; /* PHY Auto-Negotiation Advertisement Register: contains the */
                   /* advertised ability of the PHY and is used in the             */
                   /* Auto-Negotiation process with the link partner.              */
                   
    /* PHY Auto-Negotiation Link Partner Base Page Ability Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 NEX_PAGE        :1; /* Next Page RO */
            UNS16 ACKN            :1; /* Acknowledge RO */
            UNS16 REMOTE_FAULT    :1; /* Remote Fault RO */
            UNS16 EXT_NEX_PAGE    :1; /* Extended Next Page RO */
            UNS16 ASYM_PAUSE      :1; /* Asymmetric Pause RO */
            UNS16 PAUSE           :1; /* Pause RO */
            UNS16 _100BASE_T4     :1; /* 100BASE_T4 RO */
            UNS16 _100BASE_X_FDPX :1; /* 100BASE-X Full Duplex RO */
            UNS16 _100BASE_X_HDPX :1; /* 100BASE-X Half Duplex RO */
            UNS16 _10BASE_T_FDPX  :1; /* 10BASE-T Full Duplex RO */
            UNS16 _10BASE_T_HDPX  :1; /* 10BASE-T Half Duplex RO */
            UNS16 SELECTOR_FIELD  :5; /* Selector Field RO */
        } Bit;
    } PHY_AN_LP_BASE_ABILITY; 	/* PHY Auto-Negotiation Link Partner Base Page Ability Register:    */
								/* contains the advertised ability of the link partner’s PHY and    */
								/* is used in the Auto-Negotiation process between the link partner */
								/* and the PHY.                                                        */
    
    /* PHY Auto-Negotiation Expansion Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 Reserved0         :9; /* reserved, bit 15:7 RO */
            UNS16 RX_NP_LOCT_ABLE   :1; /* Receive Next Page Location Able RO */
            UNS16 RXD_NP_STORG_ABLE :1; /* Received Next Page Storage Location RO */
            UNS16 PAR_DET_FAULT     :1; /* Parallel Detection Fault RO/LH */
            UNS16 LNK_PART_NP_ABLE  :1; /* Link Partner Nex Page Able RO */
            UNS16 NEXT_PAGE_ABLE    :1; /* Next Page Able RO */
            UNS16 PAGE_RECEIVED     :1; /* Page Received RO/LH */
            UNS16 LNK_PART_AN_ABLE  :1; /* Link Partner Auto-Negotiation Able RO */
        } Bit;
    } PHY_AN_EXP; /* PHY Auto-Negotiation Expansion Register: is used in the             */
                   /* Auto-Negotiation process between the link partner and the PHY.  */
                   
    /* PHY Auto Negotiation Next Page TX Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 NEXT_PAGE  :1;  /* Next Page R/W */
            UNS16 Reserved0  :1;  /* reserved, bit 14 RO */
            UNS16 MESSG_PAGE :1;  /* Message Page R/W */
            UNS16 ACKN2      :1;  /* Acknowledge 2 R/W */
            UNS16 TOOGLE     :1;  /* Toggle RO */
            UNS16 MESSG_CODE :11; /* Message Code R/W */
        } Bit;
    } PHY_AN_NP_TX; /* PHY Auto Negotiation Next Page TX Register */
    
    /* PHY Auto Negotiation Next Page RX Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 NEXT_PAGE  :1;  /* Next Page R/O */
            UNS16 ACKN       :1;  /* Acknowledge R/O */
            UNS16 MESSG_PAGE :1;  /* Message Page R/O */
            UNS16 ACKN2      :1;  /* Acknowledge 2 R/O */
            UNS16 TOOGLE     :1;  /* Toggle RO */
            UNS16 MESSG_CODE :11; /* Message Code R/O */
        } Bit;
    } PHY_AN_NP_RX; /* PHY Auto Negotiation Next Page RX Register */

    /* PHY MMD Access Control Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 MMD_FUNC        :2; /* MMD Function R/W */
            UNS16 Reserved0       :9; /* reserved, bit 13:5 RO */
            UNS16 MMD_DEVICE_ADDR :5; /* MMD Device Address R/W */
        } Bit;
    } PHY_MMD_ACCESS; /* PHY MMD Access Control Register: provides indirect access */
                      /* to the MDIO Manageable Device (MMD) registers               */
					  
	    /* PHY MMD Access Address/Data Register*/
    union {
        UNS16 nReg; /* MMD Register Address/Data R/W */
    } PHY_MMD_ADDR_DATA; /* PHY MMD Access Address/Data Register */        
	
    /* PHYEDPD NLP / Crossover Time / EEE Configuration Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 EDPD_TX_NLP_EN         :1; /* EDPD TX NLP Enable R/W NASR */
            UNS16 INTERVAL_TMR_SEL       :2; /* EDPD TX NLP Interval Timer Select R/W NASR */
            UNS16 SGLE_NLP_WK_EN         :1; /* EDPD RX Single NLP Wake Enable R/W NASR */
            UNS16 MAX_INTVL_DETECT_SEL   :2; /* EDPD RX NLP Max Interval Detect Select R/W NASR */
            UNS16 Reserved0              :7; /* reserved, bit 9:3 RO */
            UNS16 PHYEEEEN               :1; /* PHY Energy Efficient Ethernet Enable R/W NASR */
            UNS16 EDPD_EXT_CROSS         :1; /* EDPD Extend Crossover R/W NASR */
            UNS16 EXT_MAN_AUTO_MDIX_CRTM :1; /* Extend Manual 10/100 Auto-MDIX Crossover Time R/W NASR */
        } Bit;
    } PHY_EDPD_CFG; /* PHYEDPD NLP / Crossover Time / EEE Configuration Register: is used */
                    /* to Enable EEE functionality and control NLP pulse generation and   */
                    /* the Auto-MDIX Crossover Time of the PHY.                             */
    
    /* PHY Mode Control/Status Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 Reserved0     :2; /* reserved, bit 15:14 RO */
            UNS16 EDPWRDOWN		:1; /* Energy Detect Power-Down R/W */
            UNS16 Reserved1     :6; /* reserved, bit 12:7 RO */
            UNS16 ALTER_INT     :1; /* Alternate Interrupt Mode R/W NASR  */
            UNS16 Reserved2     :4; /* reserved, bit 5:2 RO */
            UNS16 ENERGY_ON     :1; /* Indicates whether energy is detected RO */
            UNS16 Reserved3     :1; /* reserved, bit 0 RO */
        } Bit;
    } PHY_MODE_CONTROL_STATUS; /* PHY Mode Control/Status Register: is used to control */
               /* and monitor various PHY configuration options        */

    /* PHY Special Modes Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 Reserved0 :5; /* reserved, bit 15:11 RO */
            UNS16 FX_MODE   :1; /* 100BASE-FX Mode R/W NASR */
            UNS16 Reserved1 :2; /* reserved, bit 9:8 RO */
            UNS16 PHY_MODEn :3; /* PHY Mode R/W NASR */
            UNS16 PHYADD  	:5; /* PHY Address R/W NASR */
        } Bit;
    } PHY_SPECIAL_MODES; /* PHY Special Modes Register: is used to control */
                 /* the special modes of the PHY                      */
                 
    /* PHY TDR Patterns/Delay Control Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 TDR_DELAY_IN     :1; /* TDR Delay In R/W NASR */
            UNS16 TDR_LINE_BRK_CNT :3; /* TDR Line Break Counter R/W NASR */
            UNS16 TDR_PAT_H        :6; /* TDR Pattern High R/W NASR */
            UNS16 TDR_PAT_L        :6; /* TDR Pattern Low R/W NASR */
        } Bit;
    } PHY_TDR_PAT_DELAY; /* PHY TDR Patterns/Delay Control Register: */             
    
    /* PHY TDR Control/Status Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 TDR_EN           :1; /* TDR Enable R/W NASR SC */
            UNS16 TDR_AD_FILTER_EN :1; /* TDR Analog to Digital Filter Enable R/W NASR */
            UNS16 Reserved0        :3; /* reserved, bit 13:11 RO */
            UNS16 TDR_CHAN_CAB_TYP :2; /* TDR Channel Cable Type R/W NASR */
            UNS16 TDR_CHAN_STS     :1; /* TDR Channel Status R/W NASR */
            UNS16 TDR_CHAN_LENGHT  :8; /* TDR Channel Length R/W NASR */
        } Bit;
    } PHY_TDR_CONTROL_STAT; /* PHY TDR Control/Status Register: */    
                 
    /* PHY Symbol Error Counter Register*/
    union {
        UNS16 nReg; /* Symbol Error Counter RO */
    } MMD_ADDR_DATA; /* PHY Symbol Error Counter Register*/             
                 
    /* PHY Special Control/Status Indication Register */             
    union {
        UNS16 nReg;
        struct {
            UNS16 AMDIXCTRL		   :1; /* Auto-MDIX Control R/W NASR */
            UNS16 AMDIXEN		   :1; /* Auto-MDIX Enable R/W NASR */
            UNS16 AMDIXSTATE	   :1; /* Auto-MDIX State R/W NASR */
            UNS16 Reserved0        :1; /* reserved, bit 12 RO */
            UNS16 SQEOFF		   :1; /* SQE Test Disable R/W NASR */
            UNS16 Reserved1        :5; /* reserved, bit 10:6 RO */
            UNS16 FEFI_EN          :1; /* Far End Fault Indication Enable R/W */
            UNS16 XPOL             :1; /* 10Base-T Polarity State  RO */
            UNS16 Reserved2        :4; /* reserved, bit 3:0 RO */
        } Bit;
    } PHY_SPECIAL_CONTROL_STAT_IND; /* PHY Special Control/Status Indication Register: is used */
               /* to control various options of the PHY.                    */
               
    /* PHY Cable Length Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 CBLN		:4;  /* Cable Length RO */
            UNS16 Reserved0 :12; /* reserved, bit 12 R/W */
        } Bit;
    } PHY_CABLE_LEN; /* PHY Cable Length Register*/

    /* PHY Interrupt Source Flags Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 Reserved0 :6; /* reserved, bit 15:10 RO */
            UNS16 INT9      :1; /* Link Up RO/LH */
            UNS16 Reserved1 :1; /* reserved */
            UNS16 INT7      :1; /* Energy ON RO/LH */
            UNS16 INT6      :1; /* Auto-Negotiation complete RO/LH */
            UNS16 INT5      :1; /* Remote Fault Detected RO/LH */
            UNS16 INT4      :1; /* Link Down RO/LH */
            UNS16 INT3      :1; /* Auto-Negotiation LP Acknowledge RO/LH */
            UNS16 INT2      :1; /* Parallel Detection Fault RO/LH */
            UNS16 INT1      :1; /* Auto-Negotiation Page Received RO/LH */
            UNS16 Reserved2 :1; /* reserved, bit 0 RO */
        } Bit;
    } PHY_INTERRUPT_SOURCE; /* PHY Interrupt Source Flags Register: is used to determine */
                    /* to source of various PHY interrupts. All interrupt source */
                    /* bits in this register are read-only and latch high upon   */
                    /*detection of the corresponding interrupt (if enabled).     */
    
    /* PHY Interrupt Mask Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 Reserved0 :6; /* reserved, bit 15:10 RO */
            UNS16 INT9_MASK :1; /* Enables/masks the Link Up interrupt R/W */
            UNS16 Reserved1 :1; /* reserved, bit 8 RO*/
            UNS16 INT7_MASK :1; /* Enables/masks the ENERGYON interrupt R/W */
            UNS16 INT6_MASK :1; /* Enables/masks the Auto-Negotiation interrupt R/W */
            UNS16 INT5_MASK :1; /* Enables/masks the remote fault interrupt R/W */
            UNS16 INT4_MASK :1; /* Enables/masks the Link Down interrupt R/W */
            UNS16 INT3_MASK :1; /* Enables/masks the Auto-Negotiation LP acknowledge interrupt R/W */
            UNS16 INT2_MASK :1; /* Enables/masks the Parallel Detection fault interrupt R/W */
            UNS16 INT1_MASK :1; /* Enables/masks the Auto-Negotiation page received interrupt R/W */
            UNS16 Reserved2 :1; /* reserved, bit 0 RO */
        } Bit;
    } PHY_INTERRUPT_MASK; /* PHY Interrupt Mask Register: is used to   */
                /* enable or mask the various PHY interrupts */

    /* PHY Special Control/Status Register */
    union {
        UNS16 nReg;
        struct {
            UNS16 Reserved0 :3; /* reserved, bit 15:13 RO */
            UNS16 AUTO_DONE :1; /* Autodone: 0 = Auto-Negotiation is not completed, is disabled, or is not active */
                                      /*           1 = Auto-Negotiation is completed            RO                         */
            UNS16 Reserved1 :7; /* reserved, bit 11:5 R/W */
            UNS16 SPEED_IND :3; /* Speed Indication RO */
            UNS16 Reserved2 :2; /* reserved, bit 1:0 RO */
        } Bit;
    } PHY_SPECIAL_CONTROL_STATUS; /* PHY Special Control/Status Register: is used to control */ 
                   /* and monitor various options of the PHY.                  */
        /*#end ACD# LAN9250_PHY_Registers */
} LAN9250_PHY_Registers_t;

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
#endif /*__LAN9250_PHY_REGISTERS_H__*/

/* EOF */


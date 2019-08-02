/*****************************************************************************/
/* INCLUDE HEADER                                                            */
/*****************************************************************************/
/*
  MODULE:     
  PROJECT:     F6X

  DESCRIPTION: 
  This module implements interface of the LAN9250 controller driver.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS 
******************************************************************************/

#ifndef __LAN9250_SYSTEMMEMORY_H__  /* test for multiple inclusion */
#define __LAN9250_SYSTEMMEMORY_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/


/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */
/* Defines (public) from Class 'LAN9250_SysMem_Defines' */
#define LAN9250_ALIAS_PORT_SIZE_C ((UNS16) 7)
#define LAN9250_RESERVED2_SIZE_C ((UNS16) 45)


/* ---- Basic Types -------------------------------------------------------- */

/* ---- Embedded Classes --------------------------------------------------- */
/* [Code-AEB6C851-LAN9250::LAN9250_RX_Status] */
/* [Covers: ] */
typedef union LAN9250_RX_Status_tag
{
        /*#ACD# M(UDMF::UID_AEB6C851-76AA-4b47-B4E9-F4D4EE220021_AttributesByHand) LAN9250_RX_Status */
    UNS32 lReg;
    struct {
        UNS16 PacketFilter:1;   /* Packet Filter */
        UNS16 FilteringFail:1;  /* Filtering Fail */
        UNS16 PacketLength:14;  /* Packet Length */
        UNS16 ErrorStatus:1;    /* Error status */
        UNS16 Reserved0:1;      /* reserved, bit 14 */
        UNS16 BroadcastFrame:1; /* Broadcast Frame */
        UNS16 LengthError:1;    /* Length Error */
        UNS16 RuntFrame:1;      /* Runt Frame */
        UNS16 MulticastFrame:1; /* Multicast Frame */
        UNS16 Reserved1:2;      /* reserved, bits 9:8 */
        UNS16 LongFrame:1;      /* Frame Too Long */
        UNS16 Collision:1;      /* Collision Seen */
        UNS16 FrameType:1;      /* Frame Type */
        UNS16 RxTimeout:1;      /* Receive Watchdog time-out */
        UNS16 MIIError:1;       /* MII Error */
        UNS16 Dribbling:1;      /* Dribbling Bit */
        UNS16 CRCError:1;       /* CRC Error */
        UNS16 Reserved2:1;      /* reserved, bit 0 */
	} Bit;
        /*#end ACD# LAN9250_RX_Status */
} LAN9250_RX_Status_t;

/* [Code-F296870D-LAN9250::LAN9250_TX_Status] */
/* [Covers: ] */
typedef union LAN9250_TX_Status_tag
{
        /*#ACD# M(UDMF::UID_F296870D-C47A-452c-B7B4-DBFF5414209A_AttributesByHand) LAN9250_TX_Status */
    UNS32 lReg;
    struct {
        UNS16 PacketTag:16;       /* Packet TAG           */
        UNS16 ErrorStatus:1;      /* Error Status         */
        UNS16 Reserved0:3;        /* reserved, bits 14:12 */
        UNS16 LossOfCarrier:1;    /* Loss of Carrier      */
        UNS16 NoCarrier:1;        /* No Carrier           */
        UNS16 LateCollision:1;    /* Late Collision       */
        UNS16 ExcessCollisions:1; /* Excessive Collisions */
        UNS16 Reserved1:1;        /* reserved, bit 7      */
        UNS16 CollisionCount:4;   /* Collision Count      */
        UNS16 ExcessDeferral:1;   /* Excessive Deferral   */
        UNS16 Reserved2: 1;       /* reserved, bit 1      */
        UNS16 Deferred:1;         /* Deferred             */
    } Bit;
/*#end ACD# LAN9250_TX_Status */
} LAN9250_TX_Status_t;

/* [Code-188B3D0C-LAN9250::LAN9250_TX_Command] */
/* [Covers: ] */
typedef struct LAN9250_TX_Command_tag
{
        /*#ACD# M(UDMF::UID_188B3D0C-7444-43a3-9326-5BD909803BB8_AttributesByHand) LAN9250_TX_Command */
    union {
        UNS32 lReg;
        struct {
            UNS16 IntOnComplete:1;   /* Interrupt on Completion: when set, the TXIOC */
                                           /* bit will be asserted in the Interrupt Status */ 
										   /* Register (INT_STS) when the current buffer   */
                                           /* has been fully loaded into the TX FIFO       */
            UNS16 Reserved0:5;       /* reserved, bit 30:26 */
            UNS16 BuffEndAlign:2;    /* Buffer end alignment: this buffer specifies the */
                                           /* alignment that must be maintained on the last   */
                                           /* datatransfer of a buffer                        */
                                           /* 00 - 4-byte alignment                           */
                                           /* 01 - 16-byte alignment                          */
                                           /* 10 - 32-byte alignment                          */
                                           /* 11 - reserved                                   */
            UNS16 Reserved1:3;       /* reserved, bit 23-21 */
            UNS16 DataStartOffset:5; /* Data Start Offset (bytes): This field        */
                                           /* specifies the offset of the fist byte        */
                                           /* of TX data. The offset value can be anywhere */
                                           /* from 0 bytes to 31 a Byte offset             */
            UNS16 Reserved2:2;       /* reserved, bit 15:14 */
            UNS16 FirstSegment:1;    /* First Segment: When set, this bit indicates     */
                                           /* that the associated buffer is the first segment */
                                           /* of the packet                                   */
            UNS16 LastSegment:1;     /* Last Segment: When set, this bit indicates      */
                                           /* that the associated buffer is the last segment  */
                                           /* of the packet                                   */
            UNS16 Reserved3:1;       /* reserved,bit 11 */
            UNS16 BufferSize:11;     /* This field indicates the number of bytes        */
                                           /* contained in the buffer following this command  */
        } Bit;
    } A; /* TX Command A structure */
    union {
        UNS32 lReg;
        struct {
            UNS16 PacketTag:16;     /* Packet Tag: The host should write a unique packet */
                                          /* identifier to this filed                          */
            UNS16 Reserved0:1;      /* reserved, bit 15:14 */
			UNS16 TXChecksumEnable:1;  /* TX checksum offload engine (TXCOE) will calculate */
									   /* a L3 checksum for the associated frame.           */		
            UNS16 AddCRCDisable:1;  /* Add CRC Disable: When set, the automatic      */
                                    /* addition of the CRC is disabled               */
            UNS16 DisEthFramePad:1; /* Disable Ethernet Frame Padding: When set,   */
                                          /* this bit prevents the automatic addition of */
                                          /* padding to an Ethernet frame of less than   */
                                          /* 64-bytes                                    */
            UNS16 Reserved1:1;      /* reserved, bit 11 */
            UNS16 PacketLength:11;  /* Packet Length (bytes): This field indicates the */
                                          /* total number of bytes in the current packet.    */
                                          /* This length does not include the offset or padding */
        } Bit;
    } B; /* TX Command B structure */
        /*#end ACD# LAN9250_TX_Command */
} LAN9250_TX_Command_t;

typedef struct LAN9250_SystemMemory_tag
{
	// /* 1588 PORT RX PARSING CONFIGURATION REGISTER */
	// union {
        // UNS32 lReg;
        // struct {
			// UNS16 Reserved0              :16; /* reserved, bit 31:15 RO */
			// UNS16 RX_LAYER2_ADD1_EN      :1;  /* RX Layer 2 Address 1 Enable R/W */
			// UNS16 RX_LAYER2_ADD2_EN      :1;  /* RX Layer 2 Address 2 Enable R/W */
			// UNS16 RX_ADD1_EN             :1;  /* RX Address 1 Enable R/W */
			// UNS16 RX_ADD2_EN             :1;  /* RX Address 2 Enable R/W */
			                                     
			// UNS16 RX_ADD3_EN             :1;  /* RX Address 3 Enable R/W */
			// UNS16 RX_ADD4_EN             :1;  /* RX Address 4 Enable R/W */
			// UNS16 RX_ADD5_EN             :1;  /* RX Address 5 Enable R/W */
			// UNS16 RX_LAYER2_USER_MAC_EN  :1;  /* RX User Defined Layer 2 MAC Address Enable R/W */
			// UNS16 RX_IPV6_USER_MAC_EN    :1;  /* RX User Defined IPv6 MAC Address Enable R/W */
			                                     
			// UNS16 RX_IPV4_USER_MAC_EN    :1;  /* RX User Defined IPv4 MAC Address Enable R/W */
			// UNS16 RX_IP_ADDR_EN          :1;  /* RX IP Address Enable R/W */
			// UNS16 RX_MAC_ADDR_EN         :1;  /* RX MAC Address Enable R/W */
			// UNS16 RX_LAYER2_EN           :1;  /* RX Layer 2 Enable R/W */
			// UNS16 RX_IPV6_EN             :1;  /* RX IPv6 Enable R/W */
			// UNS16 RX_IPV4_EN             :1;  /* RX IPv4 Enable R/W */
			// } Bit;
    // } RX_PARSE_CONFIG_1588; /* Interrupt enable Register: contains the interrupt enable for IRQ output pin. */
                  // /* Writing 1 to any of this bits enables the corresponding interrupt as a   */
                  // /* source for IRQ                                                           */
				  
    // /* 1588 PORT TX PARSING CONFIGURATION REGISTER */
	// union {
        // UNS32 lReg;
        // struct {
			// UNS16 Reserved0              :16; /* reserved, bit 31:15 RO */
			// UNS16 TX_LAYER2_ADD1_EN      :1;  /* TX Layer 2 Address 1 Enable R/W */
			// UNS16 TX_LAYER2_ADD2_EN      :1;  /* TX Layer 2 Address 2 Enable R/W */
			// UNS16 TX_ADD1_EN             :1;  /* TX Address 1 Enable R/W */
			// UNS16 TX_ADD2_EN             :1;  /* TX Address 2 Enable R/W */
			
			// UNS16 TX_ADD3_EN             :1;  /* TX Address 3 Enable R/W */
			// UNS16 TX_ADD4_EN             :1;  /* TX Address 4 Enable R/W */
			// UNS16 TX_ADD5_EN             :1;  /* TX Address 5 Enable R/W */
			// UNS16 TX_LAYER2_USER_MAC_EN  :1;  /* TX User Defined Layer 2 MAC Address Enable R/W */
			// UNS16 TX_IPV6_USER_MAC_EN    :1;  /* TX User Defined IPv6 MAC Address Enable R/W */
			
			// UNS16 TX_IPV4_USER_MAC_EN    :1;  /* TX User Defined IPv4 MAC Address Enable R/W */
			// UNS16 TX_IP_ADDR_EN          :1;  /* TX IP Address Enable R/W */
			// UNS16 TX_MAC_ADDR_EN         :1;  /* TX MAC Address Enable R/W */
			// UNS16 TX_LAYER2_EN           :1;  /* TX Layer 2 Enable R/W */
			// UNS16 TX_IPV6_EN             :1;  /* TX IPv6 Enable R/W */
			// UNS16 TX_IPV4_EN             :1;  /* TX IPv4 Enable R/W */
			// } Bit;
    // } TX_PARSE_CONFIG_1588; /* This register is used to configure the PTP transmit message detection.*/              
		
	/*#ACD# M(UDMF::UID_E85DF76D-B086-4ae4-A674-622509EE711D_AttributesByHand) LAN9250_SystemMemory */
    UNS32 lRX_Data_FIFO_Port;   /* Rx Data FIFO Port */
    UNS32 lRX_Data_FIFO_Alias_Port_a[LAN9250_ALIAS_PORT_SIZE_C]; /* Rx Data FIFO Alias Ports */
    UNS32 lTX_Data_FIFO_Port;   /* Tx Data FIFO Port */
    UNS32 lTX_Data_FIFO_Alias_Port_a[LAN9250_ALIAS_PORT_SIZE_C]; /* Tx Data FIFO Alias Ports */
    UNS32 lRX_Status_FIFO_Port; /* Rx Status FIFO Port */
    UNS32 lRX_Status_FIFO_PEEK; /* Rx Status FIFO PEEK */
    UNS32 lTX_Status_FIFO_Port; /* Tx Status FIFO Port */
    UNS32 lTX_Status_FIFO_PEEK; /* Tx Status FIFO PEEK */

    /* System control and status registers */
    struct {
		
		/* ***************** */
		/* General Registers */
		/* ***************** */
		
		/* Chip ID and Revision */
        union {
            UNS32 lReg;
            struct {
                UNS16 CHIP_REV:16; /* Chip Revision: this field indicates the design revision */
                UNS16 CHIP_ID :16; /* Chip-ID. This field indicates the chip ID */
            } Bit;
        } ID_REV; /* Chip ID and Revision: contains the ID */
                  /* and Revision fields for the device    */

        /* Interrupt Configuration Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0    	   :9; /* reserved, bit 23:15 */
                UNS16 IRQ_POL      	   :1; /* IRQ Polarity */
                UNS16 Reserved1    	   :3; /* reserved, bit 11:9 */
                UNS16 IRQ_TYPE     	   :1; /* IRQ Buffer Type */
				UNS16 IRQ_CLK_SELECT     :1; /* IRQ Clock Select */

                UNS16 Reserved2          :3; /* reserved, bit 7:5 */
                UNS16 INT_DEAS_CLR       :1; /* Interrupt Deassertion Interval Clear */
                UNS16 INT_DEAS_STS 	   :1; /* Interrupt Deassertion Status */
                UNS16 IRQ_INT      	   :1; /* Master Interrupt */
                UNS16 Reserved3    	   :2; /* reserved, bit 3:2 */
                UNS16 IRQ_EN       	   :1; /* IRQ Enable */

                UNS16 INT_DEAS     	   :8; /* Interrupt Deassertion Interval */
            } Bit;
        } IRQ_CFG; /* Interrupt Configuration Register: configures  */
                   /* and indicates the state of the IRQ signal     */

        /* Interrupt Status Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 SW_INT        :1; /* Software Interrupt R/WC */
				UNS16 READY         :1; /* Device Ready R/WC */
				UNS16 l1588_INT_EVNT :1; /* 1588 Interrupt Event R/O */
				UNS16 Reserved0     :1; /* reserved, bit 28 */
				UNS16 Reserved1     :1; /* reserved, bit 27 */
				UNS16 PHY_INT       :1; /* PHY Interrupt Event R/O */
				UNS16 TX_STOP_INT   :1; /* TX Stopped Interrupt R/WC */
				UNS16 RX_STOP_INT   :1; /* RX Stopped Interrupt R/WC */
				
				UNS16 RX_DFH_INT    :1; /* RX D  ropped Frame Counter Halfway Interrupt R/WC */
				UNS16 Reserved2     :1; /* reserved, bit 22  */
				UNS16 TX_IOC_INT    :1; /* TX IOC Interrupt R/WC */
				UNS16 RX_DMA_INT    :1; /* RX DMA Interrupt R/WC */
				UNS16 GPTIMER_INT   :1; /* GP Timer R/WC */
				UNS16 Reserved3     :1; /* reserved, bit 18  */
				UNS16 PME_INT       :1; /* Power Management Interrupt Event R/WC */
                UNS16 TX_STATF_OF   :1; /* TX Status FIFO Overflow R/WC */
				
				UNS16 RX_WDT_INT    :1; /* Receive Watchdog Time-Out Interrupt R/WC */
				UNS16 RXE_INT       :1; /* Receiver Error Interrupt R/WC */
				UNS16 TXE_INT       :1; /* Transmiter Error Interrupt R/WC */
				UNS16 GPIO_INT      :1; /* GPIO Interrupt Event R/WC */
				UNS16 Reserved4     :1; /* reserved, bit 11  */
				UNS16 TX_DFO_INT    :1; /* TX Data FIFO Overrun Interrupt R/WC */
                UNS16 TX_DFA_INT    :1; /* TX Data FIFO Available Interrupt R/WC */
                UNS16 TX_SFF_INT    :1; /* TX Status FIFO Full Interrupt R/WC */
				
				UNS16 TX_SFL_INT    :1; /* TX Status FIFO Level Interrupt R/WC */
				UNS16 RX_DF_INT     :1; /* RX Dropped Frame Interrupt R/WC */
				UNS16 Reserved5     :1; /* reserved, bit 5   */
				UNS16 RX_SFF_INT    :1; /* RX Status FIFO Full Interrupt R/WC */
				UNS16 RX_SFL_INT    :1; /* RX Status FIFO Level Interrupt R/WC */
				UNS16 Reserved6     :2; /* reserved, bit 2:1 */
				UNS16 Reserved7     :1; /* reserved, bit 0  */
			} Bit;
        } INT_STS; /* Interrupt Status: This register contains the current status of the generated interrupts      */ 
				   /* A value of 1 indicates the corresponding interrupt conditions have been met, while a value   */ 
				   /* of 0 indicates the interrupt conditions have not been met. The bits of this register         */
				   /* reflect the status of the interrupt source regardless of whether the source has been enabled */
				   /* as an interrupt in the Interrupt Enable Register (INT_EN). Where indicated as R/WC, writing  */
				   /* a 1 to the corresponding bits acknowledges and clears the interrupt.                         */

        /* Interrupt enable Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 SW_INT_EN      :1; /* Software Interrupt Enable R/W */
				UNS16 READY_EN       :1; /* Device Ready Enable R/W */
				UNS16 l1588_EVNT_EN   :1; /* 1588 Interrupt Event Enable R/W */
				UNS16 Reserved0      :2; /* reserved, bit 28:27 RO */
				UNS16 PHY_INT_EN     :1; /* PHY Interrupt Event Enable R/W */
				UNS16 TX_STOP_INT_EN :1; /* TX Stopped Interrupt Enable R/W */
                UNS16 RX_STOP_INT_EN :1; /* RX Stopped Interrupt Enable R/W */
				
				UNS16 RX_DFH_INT_EN  :1; /* RX Dropped Frame Counter Halfway Interrupt Enable R/W */
				UNS16 Reserved1      :1; /* reserved, bit 22 RO  */
				UNS16 TX_IOC_INT_EN  :1; /* TX IOC Interrupt Enable R/W */
				UNS16 RX_DMA_INT_EN  :1; /* RX DMA Interrupt Enable R/W */
				UNS16 GPTIMER_INT_EN :1; /* GP Timer Interrupt Enable R/W */
				UNS16 Reserved2      :1; /* reserved, bit 18 RO */
				UNS16 PME_INT_EN     :1; /* Power Management Event Interrupt Enable R/W */
				UNS16 TX_STATF_OF_EN :1; /* TX Status FIFO Overflow Interrupt Enable R/W */
				
				UNS16 RX_WDT_INT_EN  :1; /* Receive Watchdog Time-Out Interrupt Enable R/W */
				UNS16 RXE_INT_EN     :1; /* Receiver Error Interrupt Enable R/W */
				UNS16 TXE_INT_EN     :1; /* Transmitter Error Interrupt Enable R/W */
				UNS16 GPIO_INT_EN    :1; /* GPIO Interrupt Event Enable */
				UNS16 Reserved3      :1; /* reserved, bit 11 RO  */
				UNS16 TX_DFO_INT_EN  :1; /* TX Data FIFO Overrun Interrupt Enable R/W */
				UNS16 TX_DFA_INT_EN  :1; /* TX Data FIFO Available Interrupt Enable R/W */ 
				UNS16 TX_SFF_INT_EN  :1; /* TX Status FIFO Full Interrupt Enable R/W */
				
				UNS16 TX_SFL_INT_EN  :1; /* TX Status FIFO Level Interrupt Enable R/W */
				UNS16 RX_DF_INT_EN   :1; /* RX Dropped Frame Interrupt Enable R/W */
				UNS16 Reserved4      :1; /* reserved, bit 5 RO  */
				UNS16 RX_SFF_INT_EN  :1; /* RX Status FIFO Full Interrupt R/W */
                UNS16 RX_SFL_INT_EN  :1; /* RX Status FIFO Level Interrupt R/W */
				UNS16 Reserved5      :2; /* reserved,bit 2:1 RO  */
				UNS16 Reserved6      :1; /* reserved, bit 0 RO */
			} Bit;
        } INT_EN; /* Interrupt enable Register: contains the interrupt enable for IRQ output pin.*/
                  /* Writing 1 to any of this bits enables the corresponding interrupt as a      */
                  /* source for IRQ                                                              */

        /* Byte Test */
        union {
            UNS32 lReg;
        } BYTE_TEST; /* RO: This register can be used to determine     */
                     /* the byte ordering of the current configuration */

        /* FIFO Level Interrupt Register*/
        union {
            UNS32 lReg;
            struct {
				UNS16 TX_DATA_LEVEL   :8; /* TX Data Available Level R/W  */
				UNS16 TX_STATUS_LEVEL :8; /* TX Status Level R/W */
				UNS16 Reserved0        :8; /* reserved, bit 15:8 RO */
                UNS16 RX_STATUS_LEVEL :8; /* RX Status Level R/W */
            } Bit;
        } FIFO_INT; /* FIFO Level Interrupt: configures the limits where the RX/TX Data*/  		
                    /* and Status FIFO’s will generate system interrupts */

        /* Receive Configuration Register */
        union {
            UNS32 lReg;
            struct {
				UNS16 RX_END_ALIGN :2; /* RX End Alignment R/W */
                UNS16 Reserved0    :2; /* reserved, bit 29:28 RO */
				UNS16 RX_DMA_CNT_H :4; /* RX DMA Count R/W */
				UNS16 RX_DMA_CNT_L :8; /* RX DMA Count R/W */
                UNS16 RX_DUMP      :1; /* Force RX Discard WO SC  */
                UNS16 Reserved1    :2; /* reserved, bit 14:13 RO */
				UNS16 RX_DATA_OFF  :5; /* RX Data Offset R/W */
                UNS16 Reserved2    :8; /* reserved, bit 7:0 RO */
            } Bit;
        } RX_CFG; /* Receive Configuration Register: controls the Host MAC receive engine */

        /* Transmit Configuration Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0      :16; /* reserved, bit 31:16 RO */
				UNS16 TX_STATUS_DUMP :1;  /* Force TX Status Discard WO SC */
                UNS16 TX_DATA_DUMP   :1;  /* Force TX Data Discard WO SC */
				UNS16 Reserved1      :11; /* reserved, bit 13:3 RO */
				UNS16 TXSAO          :1;  /* TX Status Allow Overrun R/W */
                UNS16 TX_ON          :1;  /* Transmitter Enable R/W*/
                UNS16 STOP_TX        :1;  /* Stop Transmitter R/W SC*/
			} Bit;
        } TX_CFG; /* Transmit Configuration Register: controls the Host MAC transmit functions */
                  

        /* Hardware Configuration Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0       :4; /* reserved, bit 31:28 RO */
				UNS16 READY      		:1; /* Device Ready RO */
				UNS16 Reserved1       :1; /* reserved, bit 26 RO */
				UNS16 AMDIX_EN_SS     :1; /* AMDIX_EN Strap State RO */
				UNS16 Reserved2       :3; /* reserved, bit 24:22 RO */
				UNS16 Reserved3       :1; /* reserved, bit 21 R/W */
				UNS16 MUST_BE_ONE     :1; /* Must Be One R/W */
				UNS16 TX_FIFO_SIZE    :4; /* TX FIFO Size R/W*/
				UNS16 Reserved4       :2; /* reserved, bit 15:14 RO */
				UNS16 Reserved5       :2; /* reserved, bit 13:12 R/W */
				UNS16 Reserved6       :12; /* reserved, bit 11:0 RO */
			} Bit;
        } HW_CFG; /* This register allows the configuration of various hardware features   */
				  /*including TX/RX FIFO sizes and Host MAC transmit threshold properties. */

				  			
        /* Receive Datapath Control Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 RX_FIFO_FFWD :1;   /* RX Data FIFO Fast Forward R/W SC */
                UNS32 Reserved0     :31;  /* reserved, bit 30:0 RO */
            } Bit;
        } RX_DP_CTRL; /* Receive Datapath Control Register:         */
                     /* is used to discard unwanted receive frames */

        /* Receive FIFO Information Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 RX_DATA_FIFO_USED_L :8; /* RX Data FIFO Used Space RO */
                UNS16 RX_DATA_FIFO_USED_H :8; /* RX Data FIFO Used Space RO */
                UNS16 RX_STS_FIFO_USED    :8; /* RX Status FIFO Used Space RO */
                UNS16 Reserved0           :8; /* reserved RO */
            } Bit;
        } RX_FIFO_INF; /* Receive FIFO Information Register: this register contains    */
                       /* the used space in the receive FIFOs of the LAN9250 Eth Contr */

        /* Transmit FIFO Information Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 TX_DATA_FIFO_USED_L :8; /* TX Data FIFO Used Space RO */
                UNS16 TX_DATA_FIFO_USED_H :8; /* TX Data FIFO Used Space RO */
                UNS16 TX_STS_FIFO_USED    :8; /* TX Status FIFO Used Space RO */
                UNS16 Reserved0           :8; /* reserved RO */
            } Bit;
        } TX_FIFO_INF; /* Transmit FIFO Information Register: contains the free space  */
                       /* in the transmit data FIFO and the used space in the transmit */
                       /* status FIFO in the LAN9250                                   */

        /* Power Management Control Register */
        union {
            UNS32 lReg;
            struct {
				UNS16 PM_MODE    :3; /* Power Management Mode R/W/SC */
				UNS16 PM_SLEEP_EN    :1; /* Power Management Sleep Enable R/W/SC  */
				UNS16 PM_WAKE  :1; /* Power Management Wakeup R/W */
				UNS16 LED_DIS  :1; /* LED Disable R/W */
				UNS16 l1588_CLK_DIS  :1; /* 1588 Clock Disable R/W */
				UNS16 Reserved0  :2; /* reserved, bit 24:23 RO */
				
				UNS16 l1588_TSU_CLK_DIS  :1; /* 1588 Timestamp Unit Clock Disable R/W */
				UNS16 Reserved1  :1; /* reserved, bit 21 RO */
				UNS16 Reserved2  :1; /* reserved, bit 20 RO */
				UNS16 HMAC_CLK_DIS  :1; /* Host MAC Clock Disable R/W */
				UNS16 HMAC_SYS_CLK_ONLY_DIS  :1; /* Host MAC System Clock Only Disable R/W */
				UNS16 Reserved3  :1; /* reserved, bit 17 RO */
				UNS16 EDETECT_STS :1; /* Energy-Detect Status R/WC */
				
				UNS16 Reserved4  :1; /* reserved, bit 15 RO */
				UNS16 EDETECT_EN :1; /* Energy-Detect Enable R/W */
				UNS16 Reserved5  :4; /* reserved, bit 13:10 RO */
				UNS16 WOL_EN     :1; /* Wake_on-Lan Enable R/W */
				UNS16 Reserved6  :2; /* reserved, bit 8:7 RO */
				
				UNS16 PME_TYPE   :1; /* PME Buffer Type R/W NASR*/
				UNS16 WOL_STS     :1; /* Wake On Status R/WC */
				UNS16 Reserved7  :1; /* reserved, bit4 RO */
				UNS16 PME_IND    :1; /* PME Indication R/W */
				UNS16 PME_POL    :1; /* PME Polarity R/W NASR */
				UNS16 PME_EN     :1; /* PME Enable R/W*/
				UNS16 READY      :1; /* Device Ready RO */
			} Bit;
        } PMT_CTRL;  /* Power Management Control Register: controls the Power */
                     /* Management features. It can be read while the LAN9250 */
                     /* is in power saving mode                               */

        /* General Purpose Timer Configuration Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0       :2;  /* reserved, bit 31:30 RO */
				UNS16 GP_TIMER_EN     :1;  /* GP Timer Enable R/W */
				UNS16 Reserved1       :13; /* reserved, bit 28:16  RO*/
                UNS16 GP_TIMER_LOAD_L :8;  /* General Purpose Timer Pre-Load R/W */
                UNS16 GP_TIMER_LOAD_H :8;  /* General Purpose Timer Pre-Load R/W */
			} Bit;
        } GPT_CFG; /* General Purpose Timer Configuration Register: configures */
                   /* the General Purpose timer. The GP Timer can be configured*/
                   /* to generate host interrupts at intervals defined in this register*/

        /* General Purpose Timer Count Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 GP_TIMER_CNT :16; /* General Purpose Timer Current Counter RO*/
                UNS16 Reserved0    :16; /* reserved, bit 31:16 RO */
            } Bit;
        } GPT_CNT;   /* General Purpose Timer Count Register: This read-only register */
					 /* reflects the current general purpose timer (GPT) value.       */
					 
		/* Free Run 25MHz Counter */
        union {
            UNS32 lReg;
        } FREE_RUN;  /* Free Run 25MHz Counter */

        /* Host MAC RX Dropped Frames Counter Register*/
        union {
            UNS32 lReg;
        } RX_DROP;   /* Receiver Dropped Frames Counter: This register indicates the number */
					 /* of receive frames that have been dropped by the Host MAC.           */

        /* Host MAC CSR Interface Command Register */
        union {
            UNS32 lReg;
            struct {
				UNS16 CSR_BUSY   :1;  /* CSR Busy R/W SC */
				UNS16 READ_WRITE :1;  /* Read/-Write R/W */
				UNS32 Reserved0  :22; /* reserved, bit 29-8 RO */
                UNS16 CSR_ADDR   :8;  /* CSR Address R/W */
            } Bit;
        } MAC_CSR_CMD;  /* Host MAC CSR Interface Command Register: This read-write register      */
						/* is used to control the read and write operations to/from the Host MAC. */
						/* This register in used in conjunction with the Host MAC CSR Interface   */
						/* Data Register (MAC_CSR_DATA) to indirectly access the Host MAC CSRs.   */

        /* Host MAC CSR Interface Data Register */
        union {
            UNS32 lReg;
        } MAC_CSR_DATA; /* Host MAC CSR Interface Data Register: This read-write register is used   	 */
						/* in conjunction with the Host MAC CSR Interface Command Register (MAC_CSR_CMD) */
						/* to indirectly access the Host MAC CSRs. 										 */

        /* Host MAC Automatic Flow Control Configuration Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 BACK_PR_DUR :4; /* Backpressure Duration R/W */
				UNS16 FC_MC_FRAME :1; /* Flow Control on Multicast Frame R/W */
                UNS16 FC_BC_FRAME :1; /* Flow Control on Broadcast Frame R/W */
                UNS16 FC_ADDR_DEC :1; /* Flow Control on Address Decode R/W */
                UNS16 FC_ANY      :1; /* Flow Control on Any Frame */
				UNS16 AFC_LO      :8; /* Automatic Flow Control Low Level R/W */
                UNS16 AFC_HI      :8; /* Automatic Flow Control High Level R/W */
                UNS16 Reserved0   :8; /* reserved, bit 31:24 RO */
            } Bit;
        } AFC_CFG; /* Host MAC Automatic Flow Control Configuration Register : This read/write register */
				   /* configures the mechanism that controls the automatic and software-initiated 	    */
				   /* transmission of pause frames and back pressure from the Host MAC to the network.  */

        /* Host MAC RX LPI Transitions Register */
        union {
            UNS32 lReg;
        } HMAC_RX_LPI_TRANSITION;  /* Host MAC RX LPI Transitions Register: indicates the number of times that the */
								   /* RX LPI indication from the PHY changed from de-asserted to asserted. 	       */
		
		 /* Host MAC RX LPI Time Register */
        union {
            UNS32 lReg;
        } HMAC_RX_LPI_TIME;  /* This register shows the total duration that the PHY has indicated RX LPI. */
					
		 /* Host MAC TX LPI Transitions Register */
        union {
            UNS32 lReg;
        } HMAC_TX_LPI_TRANSITION;  /* This register indicates the total number of times TX LPI request */
								   /* to the PHY changed from de-asserted to asserted.				   */
		
		 /* Host MAC TX LPI Time Register */
        union {
            UNS32 lReg;
        } HMAC_TX_LPI_TIME;  /* This register shows the total duration that TX LPI request to the PHY has been asserted. */
		
		/* ************** */
		/* 1588 Registers */
		/* ************** */
		
		
		
		/* ******************** */
		/* EEPROM/LED Registers */
		/* ******************** */
					
		/* EEPROM Command Register */
        union {
            UNS32 lReg;
            struct {
				UNS16 EPC_BUSY          :1;  /* EEPROM Controller Busy R/W SC */
				UNS16 EPC_COMMAND       :3;  /* EEPROM Controller Command R/W */
				UNS16 Reserved0         :9;  /* reserved, bit 27:19 RO */
				UNS16 LOADER_OVERFLOW   :1;  /* EEPROM Loader Address Overflow RO */
				UNS16 EPC_TIMEOUT       :1;  /* EEPROM Controller Timeout R/WC */
                UNS16 CFG_LOADED   	  :1;  /* Configuration Loaded R/WC */
				UNS16 EPC_ADDRESS       :16; /* EEPROM Controller Address R/W */
            } Bit;
        } E2P_CMD;  /* EEPROM Command Register: This read/write register is used      */
					/* to control the read and write operations of the serial EEPROM. */

        /* EEPROM Data Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 EEPROM_DATA :8;  /* EEPROM Data R/W*/
                UNS32 Reserved0   :24; /* reserved RO */
            } Bit;
        } E2P_DATA; /* EEPROM Data Register: This read/write register is used in conjunction           */
					/* with the EEPROM Command Register (E2P_CMD) to perform read and write operations */
					/* with the serial EEPROM. 														   */
		
		/* LED Configuration Register */
        union {
            UNS32 lReg;
            struct {
				UNS32 Reserved0     :21; /* reserved, bit 31:11 RO */
				UNS16 LED_FUNn      :3;  /* LED Function 2-0 R/W */
				UNS16 Reserved1     :5;  /* reserved, bit 7:3 RO */
				UNS16 LED_ENn       :3;  /* LED Enable 2-0 R/W*/
            } Bit;
        } LED_CFG;  /* LED Configuration Register: This read/write register configures */
					/* the GPIO[2:0] pins as LED pins and sets their functionality.    */
					
		/* ************** */
		/* GPIO Registers */
		/* ************** */
		
		/* General Purpose IO Configuration Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0     :5; /* reserved, bit 31:27 RO */
                UNS16 GPIO_CH_SELn  :3; /* 1588 GPIO Channel Select 2-0 R/W */
				UNS16 Reserved1     :5; /* reserved, bit 23:19 RO */
				UNS16 GPIO_POLn	  :3; /* GPIO Interrupt/1588 Polarity 2-0 */
				UNS16 Reserved2     :5; /* reserved, bit 15:11 RO */
				UNS16 l1588_GPIO_OEn :3; /* 1588 GPIO Output Enable 2-0 R/W*/
                UNS16 Reserved3     :5; /* reserved, bit 7:3 RO */
				UNS16 GPIO_BUF_TYPE :3; /* GPIO Buffer Type 0-2 R/W */
            } Bit;
        } GPIO_CFG;  /* This read/write register configures the GPIO input and output pins.  */
					 /* The polarity of the GPIO pins is configured here as well as the IEEE */
					 /* 1588 timestamping and clock compare event output properties.         */
		
		/* General Purpose I/O Data & Direction Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0     :13; /* reserved, bit 31:19 RO */
                UNS16 GPIO_DIRn     :3;  /* GPIO Direction 2-0 R/W */
                UNS16 Reserved1     :13; /* reserved, bit 15:3 RO */
				UNS16 GPIO_DATAn    :3;  /* GPIO Data 2-0 R/W */
			} Bit;
        } GPIO_DATA_DIR;  /* This read/write register configures the direction of the GPIO pins */
						  /* and contains the GPIO input and output data bits.   			 	*/

        /* General Purpose I/O Interrupt Status and Enable Register */
        union {
            UNS32 lReg;
            struct {
                UNS16 Reserved0     :13; /* reserved, bit 31:19 RO */
                UNS16 GPIOn_INT_EN  :3;  /* GPIO Interrupt Enable[2:0] R/W */
                UNS16 Reserved1     :13; /* reserved, bit 15:3 RO */
				UNS16 GPIOn_INT     :3;  /* GPIO Interrupt[2:0] R/W */
            } Bit;
        } GPIO_INT_STS_EN;  /* This read/write register contains the GPIO interrupt status bits. */
							/* Writing a 1 to any of the interrupt status bits acknowledges and  */
							/* clears the interrupt.											 */

        /* *************** */
		/* Reset Registers */
		/* *************** */
		
		/* Reset Control Register */
        union {
            UNS32 lReg;
            struct {
				UNS32 Reserved0         :25; /* reserved, bit 31:7 RO */
				UNS16 Reserved1         :1;  /* reserved, bit 6 RO */
				UNS16 HMAC_RST          :1;  /* Host MAC Reset R/W SC */
				UNS16 Reserved2         :1;  /* reserved, bit 4 RO */
				UNS16 Reserved3         :1;  /* reserved, bit 3 RO */
				UNS16 Reserved4         :1;  /* reserved, bit 2 RO */
				UNS16 PHY_RST           :1;  /* PHY Reset R/W SC */
				UNS16 DIGITAL_RST       :1;  /* Digital Reset R/W SC */
            } Bit;
        } RESET_CTL;  /* This register contains software controlled resets. */
        
    } SYSTEM_CSR; /* System control and status registers: are directly */
                  /* addressable by the host bus                       */
				  
                  /*#end ACD# LAN9250_System Memory */
} LAN9250_SystemMemory_t;

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
#endif /*__LAN9250_SYSTEMMEMORY_H__*/

/* EOF */


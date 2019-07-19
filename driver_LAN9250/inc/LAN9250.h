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

#ifndef __LAN9250_H__  /* test for multiple inclusion */
#define __LAN9250_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/ 
#include "standard.h"

/*****************************************************************************/
/*                              GLOBAL CONSTANTS                             */
/*****************************************************************************/

/* Bit incremented for Address field on READ/WRITE*/
#define LAN9250_BIT_INCREMENTED (UNS16) 0x4000

/*Size of TX and RX Data FIFO Alias Port array*/
#define LAN9250_ALIAS_PORT_SIZE_C ((UNS16) 7)

/* Defines (private) from Class 'xx' */
#define DRIVERCONFIG_LAN_BASE_ARRD_C ((UNS32) 0x00000000)

/********************************************************************/

/* ******************** */
/* SPI Instruction Code */
/* ******************** */
#define LAN9250_SPI_RESET_SQI (UNS8) 0xFF
#define LAN9250_SPI_READ (UNS8) 0x03
#define LAN9250_SPI_FAST_READ (UNS8) 0x0B
#define LAN9250_SPI_WRITE (UNS8) 0x02

/********************************************************************/

/***************/
/* TX/RX FIFOs */
/***************/
#define lRX_Data_FIFO_Port_ADDR   							  (UNS16)0x00
#define lRX_Data_FIFO_Alias_Port_a[LAN9250_ALIAS_PORT_SIZE_C] 
#define lTX_Data_FIFO_Port_ADDR   							  (UNS16)0x20
#define lTX_Data_FIFO_Alias_Port_a[LAN9250_ALIAS_PORT_SIZE_C] 
#define lRX_Status_FIFO_Port_ADDR  						      (UNS16)0x40
#define lRX_Status_FIFO_PEEK_ADDR							  (UNS16)0x44  
#define lTX_Status_FIFO_Port_ADDR  							  (UNS16)0x48
#define lTX_Status_FIFO_PEEK_ADDR  							  (UNS16)0x4C
#define TX_STATUS_FIFO_USED_MASK 						      (UNS32)0x00FF0000

/********************************************************************/ 

/***********************************************/
/* System Control and Status Registers Address */
/***********************************************/
#define LAN9250_ID_REV_ADDR                 (UNS16)0x050 
#define LAN9250_IRQ_CFG_ADDR                (UNS16)0x054 
#define LAN9250_INT_STS_ADDR                (UNS16)0x058 
#define LAN9250_INT_EN_ADDR                 (UNS16)0x05C 
#define LAN9250_BYTE_TEST_ADDR              (UNS16)0x064 
#define LAN9250_FIFO_INT_ADDR               (UNS16)0x068 
#define LAN9250_RX_CFG_ADDR                 (UNS16)0x06C 
#define LAN9250_TX_CFG_ADDR                 (UNS16)0x070 
#define LAN9250_HW_CFG_ADDR                 (UNS16)0x074 
#define LAN9250_R_DP_CTRL_ADDR              (UNS16)0x078 
#define LAN9250_RX_FIFO_INF_ADDR            (UNS16)0x07C 
#define LAN9250_TX_FIFO_INF_ADDR            (UNS16)0x080 
#define LAN9250_PMT_CTRL_ADDR               (UNS16)0x084 
#define LAN9250_GPT_CFG_ADDR                (UNS16)0x08C 
#define LAN9250_GPT_CNT_ADDR                (UNS16)0x090 
#define LAN9250_FREE_RUN_ADDR               (UNS16)0x09C 
#define LAN9250_RX_DROP_ADDR                (UNS16)0x0A0 
#define LAN9250_HMAC_CSR_CMD_ADDR           (UNS16)0x0A4 
#define LAN9250_HMAC_CSR_DATA_ADDR          (UNS16)0x0A8 
#define LAN9250_AFC_CFG_ADDR                (UNS16)0x0AC 
#define LAN9250_HMAC_RX_LPI_TRANSITION_ADDR (UNS16)0x0B0 
#define LAN9250_HMAC_RX_LPI_TIME_ADDR       (UNS16)0x0B4 
#define LAN9250_HMAC_TX_LPI_TRANSITION_ADDR (UNS16)0x0B8 
#define LAN9250_HMAC_TX_LPI_TIME_ADDR       (UNS16)0x0BC 
#define LAN9250_E2P_CMD_ADDR                (UNS16)0x1B4 
#define LAN9250_E2P_DATA_ADDR               (UNS16)0x1B8 
#define LAN9250_LED_CFG_ADDR                (UNS16)0x1BC 
#define LAN9250_GPIO_CFG_ADDR               (UNS16)0x1E0 
#define LAN9250_GPIO_DATA_DIR_ADDR          (UNS16)0x1E4 
#define LAN9250_GPIO_INT_STS_EN_ADDR        (UNS16)0x1E8 
#define LAN9250_RESET_CTL_ADDR              (UNS16)0x1F8

/********************************************************************/ 

/********************************************/
/*Constants for Memory Operations Functions */
/********************************************/
#define MEMORY_BYTE0_MASK_C		((UNS32) 0x000000FF)
#define MEMORY_BYTE1_MASK_C		((UNS32) 0x0000FF00)
#define MEMORY_BYTE2_MASK_C		((UNS32) 0x00FF0000)
#define MEMORY_BYTE3_MASK_C		((UNS32) 0xFF000000)
#define MEMORY_BYTE0_3_SHIFT_C	((UNS32) 24)
#define MEMORY_BYTE1_2_SHIFT_C	((UNS32) 8)

/********************************************************************/
 
/***************************************/
/* System Control and Status Registers */
/***************************************/
/*CHIP ID AND REVISION (ID_REV): bit 31-16 Chip ID: 9250h */
#define LAN9250_ID_REV_C					 			((UNS32) 0x92500000)   // OK
/*INTERRUPT CONFIGURATION REGISTER (IRQ_CFG)*/
#define LAN9250_IRQ_CFG_C								((UNS32) 0x00000001)   // OK Pas d'interruption mais du polling
/*INTERRUPT STATUS REGISTER (INT_STS)*/
#define LAN9250_INT_STS_C								((UNS32) 0x00000000)   // OK Pas d'interruption mais du polling
/*INTERRUPT ENABLE REGISTER (INT_EN)*/
#define LAN9250_INT_EN_C								((UNS32) 0x00000000)   // OK Pas d'interruption mais du polling
/*BYTE ORDER TEST REGISTER (BYTE_TEST)*/
#define LAN9250_BYTE_TEST_C								((UNS32) 0x87654321) 	// OK Pas d'interruption mais du polling
/*FIFO LEVEL INTERRUPT REGISTER (FIFO_INT): bit 31-24 TX Data Available Level: 48h*/  
#define LAN9250_FIFO_INT_C								((UNS32) 0x48000000)   // OK Pas d'interruption mais du polling
/*RECEIVE CONFIGURATION REGISTER (RX_CFG)*/
#define LAN9250_RX_CFG_C                                ((UNS32) 0x00000000)   // OK
/*TRANSMIT CONFIGURATION REGISTER (TX_CFG)*/
#define LAN9250_TX_CFG_C                                ((UNS32) 0x0000C001)   // // Force TX Status Discard (TXS_DUMP) : 1 / Force TX Data Discard (TXD_DUMP) : 1 / STOP_TX bit 1 : 1 --  ATTENTION : Différent du LAN9218
/*HARDWARE CONFIGURATION REGISTER (HW_CFG): Bit 20 MBO : 1h, Bit 19:16 FIFO_SIZE 5h*/
#define LAN9250_HW_CFG_C							    ((UNS32) 0x00150000) 		// OK, a voir par rapport à la taille de la FIFO voulue
/*RECEIVE DATAPATH CONTROL REGISTER (RX_DP_CTRL): Set the RX Data FIFO Fast Forward Bit(bit 31) to initiate the fast forwarding (discarding) operation*/
#define LAN9250_RX_DP_CTRL_C							((UNS32) 0x80000000)	// OK
/*RX FIFO INFORMATION REGISTER (RX_FIFO_INF)*/
#define LAN9250_RX_FIFO_INF_C                           ((UNS32) 0x00000000)	// OK, read only
/*TX FIFO INFORMATION REGISTER (TX_FIFO_INF): bit 15-0 TX Data FIFO Free Space (TXFREE): 1200h  */
#define LAN9250_TX_FIFO_INF_C                           ((UNS32) 0x00001200)
/*Power Management Control Register (PMT_CTRL)*/
/* Bit 28 : 0: Device is not in a low power sleep state
		27 0: Manual Wakeup only
		26 0: LEDs are enabled
		25 0: Clocks are enabled
		22 1588 Timestamp Unit Clock 0: Clocks are enabled
		19 Host MAC Clock 0: Clocks are enabled
		18 Host MAC System Clock 0: Clocks are enabled
		(..) */
#define LAN9250_PMT_CTR_C								((UNS32) 0x00000000)	// OK
/*GENERAL PURPOSE TIMER CONFIGURATION REGISTER (GPT_CFG): bit 15-0 General Purpose Timer Pre-Load (GPT_LOAD): FFFFh*/
#define LAN9250_GPT_CFG_C                               ((UNS32) 0x0000FFFF)	// OK, GPT disabled
/*GENERAL PURPOSE TIMER COUNT REGISTER (GPT_CNT): bit 15-0 General Purpose Timer Current Count (GPT_CNT): FFFFh  */
#define LAN9250_GPT_CNT_C                               ((UNS32) 0x0000FFFF)	// OK
/*FREE RUNNING 25MHZ COUNTER REGISTER (FREE_RUN)*/
#define LAN9250_FREE_RUN_C                              ((UNS32) 0x00000000)	// OK
/*HOST MAC RX DROPPED FRAMES COUNTER REGISTER (RX_DROP)*/
#define LAN9250_RX_DROP_C                       		((UNS32) 0x00000000)	// OK 
/*HOST MAC CSR INTERFACE DATA REGISTER (MAC_CSR_DATA)*/
#define LAN9250_HMAC_CSR_DATA_C							((UNS32) 0x00000000)    // OK , ne sert à rien
/*HOST MAC AUTOMATIC FLOW CONTROL CONFIGURATION REGISTER (AFC_CFG)*/
#define LAN9250_AFC_CFG_C                       		((UNS32) 0x006E3740) 	// OK
/*HOST MAC RX LPI TRANSITIONS REGISTER (HMAC_RX_LPI_TRANSITION)*/
#define LAN9250_HMAC_RX_LPI_TRANSITION_ADDR_C   		((UNS32) 0x00000000)	// OK, ne sert à rien
/*HOST MAC RX LPI TIME REGISTER (HMAC_RX_LPI_TIME)*/
#define LAN9250_HMAC_RX_LPI_TIME_C              		((UNS32) 0x00000000)	// OK, ne sert à rien
/*HOST MAC TX LPI TRANSITIONS REGISTER (HMAC_TX_LPI_TRANSITION)*/
#define LAN9250_HMAC_TX_LPI_TRANSITION_ADDR_C   		((UNS32) 0x00000000)	// OK, ne sert à rien
/*HOST MAC TX LPI TIME REGISTER (HMAC_TX_LPI_TIME)*/
#define LAN9250_HMAC_TX_LPI_TIME_C              		((UNS32) 0x00000000)	// OK, ne sert à rien

/************************/
/* EEPROM/LED Registers */
/************************/
/*EEPROM COMMAND REGISTER (E2P_CMD)*/
#define LAN9250_E2P_CMD_C						((UNS32) 0x00000000)
/*EEPROM DATA REGISTER (E2P_DATA): bit 7-0 EEPROM Data (EEPROM_DATA): 00h */
#define LAN9250_E2P_DATA_C                      ((UNS32) 0x00000000)
/*LED CONFIGURATION REGISTER (LED_CFG): bit 2-0 LED Enable 2-0 (LED_EN[2:0]): 110*/
#define LAN9250_LED_CFG_C                       ((UNS32) 0x00000006)

/******************/
/* GPIO Registers */
/******************/
/*GENERAL PURPOSE I/O CONFIGURATION REGISTER (GPIO_CFG)*/                                     
#define LAN9250_GPIO_CFG_C                      ((UNS32) 0x00000000)
/*GENERAL PURPOSE I/O DATA & DIRECTION REGISTER (GPIO_DATA_DIR): bit 18-16 GPIO Direction 2-0 (GPIODIR[2:0]): 111h*/
#define LAN9250_GPIO_DATA_DIR_C					((UNS32) 0x00070000)
/*GENERAL PURPOSE I/O INTERRUPT STATUS AND ENABLE REGISTER (GPIO_INT_STS_EN)*/
#define LAN9250_GPIO_INT_STS_EN_C               ((UNS32) 0x00000000)

/******************/
/* Reset Register */
/******************/
/*Reset Control Register (RESET_CTL): bit 5 Host MAC Reset (HMAC_RST) 0b*/                                     
#define LAN9250_RESET_CTL_C                     ((UNS32) 0x00000001)
 
/********************************************************************/

/*****************************************/
/* Host MAC Control and Status Registers */
/*****************************************/
/*HOST MAC CONTROL REGISTER (HMAC_CR): bit 18 Promiscuous Mode (PRMS): 1b*/
#define LAN9250_HMAC_CR_C								((UNS32) 0x00040000) // OK , ne sert à rien
/*HOST MAC ADDRESS HIGH REGISTER (HMAC_ADDRH): bit 15-0 Physical Address [47:32]: FFFFh */
#define LAN9250_HMAC_ADDRH_C                            ((UNS32) 0x0000FFFF) // OK , ne sert à rien
/*HOST MAC ADDRESS LOW REGISTER (HMAC_ADDRL): bit 31-0 Physical Address [31:0]: FFFFFFFFh */
#define LAN9250_HMAC_ADDRL_C                            ((UNS32) 0xFFFFFFFF) // OK , ne sert à rien
/*HOST MAC MULTICAST HASH TABLE HIGH REGISTER (HMAC_HASHH)*/
#define LAN9250_HMAC_HASHH_C                            ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC MULTICAST HASH TABLE LOW REGISTER (HMAC_HASHL)*/
#define LAN9250_HMAC_HASHL_C                            ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC MII ACCESS REGISTER (HMAC_MII_ACC)*/
#define LAN9250_HMAC_MII_ACC_C                          ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC MII DATA REGISTER (HMAC_MII_DATA)/ BIT 15-0 MII Data: 0000h*/
#define LAN9250_HMAC_MII_DATA_C                         ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC FLOW CONTROL REGISTER (HMAC_FLOW)*/
#define LAN9250_HMAC_FLOW_C                             ((UNS32) 0x)		 // OK , ne sert à rien
/*HOST MAC VLAN1 TAG REGISTER (HMAC_VLAN1): bit 15-0 VLAN1 Tag Identifier (VTI1): FFFFh*/
#define LAN9250_HMAC_VLAN1_C                            ((UNS32) 0x0000FFFF) // OK , ne sert à rien
/*HOST MAC VLAN2 TAG REGISTER (HMAC_VLAN2): bit 15-0 VLAN2 Tag Identifier (VTI2): FFFFh */
#define LAN9250_HMAC_VLAN2_C                            ((UNS32) 0x0000FFFF) // OK , ne sert à rien
/*HOST MAC WAKE-UP FRAME FILTER REGISTER (HMAC_WUFF): bit 31-0 Wake-Up Frame Filter (WFF) */
#define LAN9250_HMAC_WUFF_C                             ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC WAKE-UP CONTROL AND STATUS REGISTER (HMAC_WUCSR)*/
#define LAN9250_HMAC_WUCSR_C                            ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC CHECKSUM OFFLOAD ENGINE CONTROL REGISTER (HMAC_COE_CR)*/
#define LAN9250_HMAC_COE_CR_C                           ((UNS32) 0x00000000) // OK , ne sert à rien
/*HOST MAC EEE TIME WAIT TX SYSTEM REGISTER (HMAC_EEE_TW_TX_SYS): bit 23-0 TX Delay After TX LPI Removal: 00001Eh*/
#define LAN9250_HMAC_EEE_TW_TX_SYS_C                    ((UNS32) 0x0000001E) // OK , ne sert à rien
/*HOST MAC EEE TX LPI REQUEST DELAY REGISTER (HMAC_EEE_TX_LPI_REQ_DELAY)*/
#define LAN9250_HMAC_EEE_TX_LPI_REQ_DELAY_C             ((UNS32) 0x00000000) // OK , ne sert à rien

/********************************************************************/

/************************************/
/* PHY Control and Status Registers */
/************************************/
/*PHY Basic Control Register (PHY_BASIC_CONTROL)*/
#define LAN9250_PHY_BASIC_CONTROL_C                      ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Basic Status Register (PHY_BASIC_STATUS): bit 14 100BASE-X Full Duplex: 1b, bit 13 100BASE-X Half Duplex: 1b,  
bit 12 10BASE-T Full Duplex :1b, bit 11 10BASE-T Half Duplex: 1b, bit 3 Auto-Negotiation Ability: 1b, bit 0 Extended Capability: 1b*/
#define LAN9250_PHY_BASIC_STATUS_C                       ((UNS32) 0x7809) // OK , ne sert à rien
/*PHY Identification MSB Register (PHY_ID_MSB): bit 15-0 PHY ID 0007h*/
#define LAN9250_PHY_ID_MSB_C                             ((UNS32) 0x0007) // OK , ne sert à rien
/*PHY Identification LSB Register (PHY_ID_LSB): */
#define LAN9250_PHY_ID_LSB_C                             ((UNS32) 0xC140) // OK , ne sert à rien
/*PHY Auto-Negotiation Advertisement Register (PHY_AN_ADV): bit 8 100BASE-X Full Duplex: 1b, bit 7 100BASE-X Half Duplex: 1b,
bit 6 10BASE-X Full Duplex: 1b, bit 5 10BASE-X Half Duplex: 1b, bit 4-0 Selector Field: 00001b -- REG: _10BASE_T_FDPX */
#define LAN9250_PHY_AN_ADV_C                             ((UNS32) 0x0040) // Update it using the structure
/*PHY Auto-Negotiation Link Partner Base Page Ability Register (PHY_AN_LP_BASE_ABILITY): bit 4-0 Selector Field: 00001b*/
#define LAN9250_PHY_AN_LP_BASE_ABILITY_C                 ((UNS32) 0x0001) // OK , ne sert à rien
/*PHY Auto-Negotiation Expansion Register (PHY_AN_EXP): bit 6 Receive Next Page Location Able: 1b, 
bit 5 Received Next Page Storage Location: 1b, bit 2 Next Page Able: 1b */
#define LAN9250_PHY_AN_EXP_C                             ((UNS32) 0x0064) // OK , ne sert à rien
/*PHY Auto Negotiation Next Page TX Register (PHY_AN_NP_TX): bit 13 Message Page: 1b, bit 10-0 Message Code: 00000000001b */
#define LAN9250_PHY_AN_NP_TX_C                           ((UNS32) 0x2001) // OK , ne sert à rien
/*PHY Auto Negotiation Next Page RX Register (PHY_AN_NP_RX)*/
#define LAN9250_PHY_AN_NP_RX_C                           ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY MMD Access Control Register (PHY_MMD_ACCESS)*/
#define LAN9250_PHY_MMD_ACCESS_C                         ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY MMD Access Address/Data Register (PHY_MMD_ADDR_DATA)*/
#define LAN9250_PHY_MMD_ADDR_DATA_C                      ((UNS32) 0x0000) // OK , ne sert à rien
/*PHYEDPD NLP / Crossover Time / EEE Configuration Register (PHY_EDPD_CFG): bit 0 Extend Manual 10/100 Auto-MDIX Crossover Time: 1b */
#define LAN9250_PHY_EDPD_CFG_C                           ((UNS32) 0x0001)  // OK , ne sert à rien
/*PHY Mode Control/Status Register (PHY_MODE_CONTROL_STATUS): bit 1 Energy On (ENERGYON): 1b */
#define LAN9250_PHY_MODE_CONTROL_STATUS_C                ((UNS32) 0x0020) // OK , ne sert à rien
/*PHY Special Modes Register (PHY_SPECIAL_MODES)*/
#define LAN9250_PHY_SPECIAL_MODES_C                      ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY TDR Patterns/Delay Control Register (PHY_TDR_PAT_DELAY): bit 15 TDR Delay In 1b, bit 14-12 TDR Line Break Counter 001b, 
bit 11-6 TDR Pattern High 101110b, bit 5-0  TDR Pattern Low 011101 */
#define LAN9250_PHY_TDR_PAT_DELAY_C                      ((UNS32) 0x9B9D) // OK , ne sert à rien
/*PHY TDR Control/Status Register (PHY_TDR_CONTROL_STAT)*/
#define LAN9250_PHY_TDR_CONTROL_STAT_C  				 ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Symbol Error Counter Register*/
#define LAN9250_SYM_ERR_CNT_C                            ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Special Control/Status Indication Register (PHY_SPECIAL_CONTROL_STAT_IND)*/
#define LAN9250_PHY_SPECIAL_CONTROL_STAT_IND_C           ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Cable Length Register (PHY_CABLE_LEN): bit 11-0 RESERVED - Write as 100000000000b, ignore on read*/
#define LAN9250_PHY_CABLE_LEN_C                          ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Interrupt Source Flags Register (PHY_INTERRUPT_SOURCE)*/
#define LAN9250_PHY_INTERRUPT_SOURCE_C                   ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Interrupt Mask Register (PHY_INTERRUPT_MASK)*/
#define LAN9250_PHY_INTERRUPT_MASK_C                     ((UNS32) 0x0000) // OK , ne sert à rien
/*PHY Special Control/Status Register (PHY_SPECIAL_CONTROL_STATUS): bit 11-5 RESERVED - Write as 0000010b, ignore on read, 
bit 4-2 Speed Indication: XXXb */
#define LAN9250_PHY_SPECIAL_CONTROL_STATUS_C             ((UNS32) 0x0040) // OK , ne sert à rien

/********************************************************************/

/* Miscellaneous Constants */
#define STDDEFINES_MAX_UINT32_C				((UNS32) 0xFFFFFFFF)
#define LAN9250_LAN_TIMEOUT_C				((UNS32) 500)
#define LAN9250_LINK_TIMEOUT_C				((UNS32) 0x0000FFFF)   
#define LAN9250_HMAC_TIMEOUT_C				((UNS32) 500) //50?
#define LAN9250_PHY_TIMEOUT_C 				((UNS32) 100) 
#define LAN9250_TIMER_DIVIDER_C				((UNS32) 25)
#define LAN9250_INIT_WAIT_C					((UNS32) 200)
#define LAN9250_LINK_WAIT_C					((UNS32) 2000)
#define LAN9250_TEST_PATTERN_C				((UNS32) 0x55555555)                                                    
#define LAN9250_RESET_PIN_C					((UNS32) 169)
#define LAN9250_MIN_PACKET_SIZE_C			((UNS32) 15)
#define LAN9250_DIGITAL_RESET_WAIT_C		((UNS32) 760)	
#define LAN9250_PHY_ADDR_SHIFT_C		    ((UNS32) 6)
#define LAN9250_RX_STATUS_FAILED_C		    ((UNS32) 0x40009018) // Mask all bits that reflect error status in RX Status
#define LAN9250_PHY_SPEED_STATUS_FDX_C	    ((UNS16 ) 0x0010)    //bit 4 in 3bits 4-2 of Speed Indication field: 1h for Full-duplex Configuration
#define LAN9250_RX_CFG_CLEAR_C			    ((UNS32) 0x00008000) // bit 15 Force RX Discard (RX_DUMP): 1h for clearing RX Data and Status

/*HMAC and PHY Read/Write Command*/
#define LAN9250_HMAC_READ_CMD_C			    ((UNS32) 0xC0000000)
#define LAN9250_HMAC_WRITE_CMD_C		    ((UNS32) 0x80000000)
#define LAN9250_PHY_READ_CMD_C			    ((UNS32) 0x00000801)		 
#define LAN9250_PHY_WRITE_CMD_C			    ((UNS32) 0x00000803)

/*Masks and bit positions*/
#define LAN9250_E2P_CONTROLLER_BUSY_BIT_C   ((UNS32) 0x80000000)
#define LAN9250_E2P_DATA_BYTE0_MASK_C       ((UNS32) 0x800000FF)
#define LAN9250_READY_BIT_MASK_C			((UNS32) 0x00000001)
#define LAN9250_IRQ_OUTPUT_DISABLE_MASK_C	((UNS32) 0xFFFFFEFF)
#define LAN9250_DIGITAL_RESET_BIT_MASK_C	((UNS32) 0x00000001) 
#define LAN9250_HMAC_CSR_BUSY_MASK_C	    ((UNS32) 0x80000000)         
#define LAN9250_DEVICE_READY_MASK_C	    	((UNS32) 0x08000000)         
#define LAN9250_HMAC_ADDR_MASK_C		    ((UNS32) 0x000000FF)         
#define LAN9250_TX_ON_BIT_MASK_C	        ((UNS32) 0x00000020)		 
#define LAN9250_TX_ON_MASK_C		        ((UNS32) 0x00000002)         
#define LAN9250_TX_ERROR_MASK_C		        ((UNS32) 0x00002000)		 
#define LAN9250_PHY_BUSY_MASK_C			    ((UNS32) 0x00000001)		 
#define LAN9250_PHY_ADDR_MASK_C			    ((UNS32) 0x0000001F)		 
#define LAN9250_PHY_DATA_MASK_C			    ((UNS32) 0x0000FFFF)		 

#define LAN9250_STOP_TX_BIT_C				((UNS32) 0x00000001)
#define LAN9250_STOP_TX_INT_BIT_C			((UNS32) 0x02000000)
#define LAN9250_DIGITAL_RESET_BIT_C			((UNS32) 0x00000001) 
#define LAN9250_DIGITAL_RESET_BIT_WRITE_C	((UNS32) 0x00000001)
#define LAN9250_TX_ON_BITNUMBER_C	 		((UNS32) 0x01)              
#define LAN9250_TX_ERROR_INT_BIT_C			((UNS8)  0x0D)

                                                         
/* ---- Embedded Classes --------------------------------------------------- */
typedef enum DriverReturnCode_tag
{
    DRVRC_NO_ERROR_E          = 0,
    DRVRC_NO_DATA_E           = 1,
    DRVRC_HARD_FAIL_E         = 2,
    DRVRC_SOFT_FAIL_E         = 3,
    DRVRC_CONFIG_FAIL_E       = 4,
    DRVRC_DISABLED_E          = 5,
    DRVRC_FULL_E              = 6,
    DRVRC_TIMEOUT_E           = 7,
    DRVRC_INVALID_PARAMETER_E = 8
} DriverReturnCode_t;

/* [Code-F5A39F0A-LAN9250::LAN9250_SpeedMode] */
/* [Covers: ] */
typedef enum LAN9250_SpeedMode_tag
{
    LAN9250_SPEED_MODE_10_MBPS_E  = 0,
    LAN9250_SPEED_MODE_100_MBPS_E = 1
} LAN9250_SpeedMode_t;

/* [Code-E1178498-LAN9250::LAN9250_IO_Cfg] */
/* [Covers: ] */
typedef struct LAN9250_IO_Cfg_tag
{
    UNS32              	   lIdTag;
    UNS32              	   lBaseAddress;
	UNS8                   cOwnMACAddress_a[6];
    BOOLEAN                bAutonegotiationMode;
    BOOLEAN                bDuplexMode;
    BOOLEAN                bPromiscuousMode;
    LAN9250_SpeedMode_t    SpeedMode;
} LAN9250_IO_Cfg_t;

/* [Code-AD657720-LAN9250::LAN9250_Instance] */
/* [Covers: ] */
typedef struct LAN9250_Instance_tag
{
    UNS32               lIdTag;
    UNS32               lReserved_a[4];
    LAN9250_IO_Cfg_t *	InstanceCfg_p;
} LAN9250_Instance_t;

/* [Code-13083D7C-LAN9250::LAN9250_Command] */
/* [Covers: ] */
typedef enum LAN9250_Command_tag
{
    LAN9250_CMD_GET_TIME_E = 0,
    LAN9250_CMD_WAIT_E,
    LAN9250_CMD_INVALID_E
} LAN9250_Command_t;

/* [Code-ACEA8238-LAN9250::LAN9250_ControlData] */
/* [Covers: ] */
typedef struct LAN9250_ControlData_tag
{
    UNS32            lIdTag;
    UNS32            lParameter;
    LAN9250_Command_t   Command;
} LAN9250_ControlData_t;

extern LAN9250_Instance_t LAN9250Instance;

/* ---- Master Class ------------------------------------------------------- */

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/ 
extern void LAN9250_Read	(void * Instance_iop,
							void * ReceiveData_op,
							UNS32 lReceiveDataSize_i,
							DriverReturnCode_t * ReturnCode_op);

extern void LAN9250_Write	(void * Instance_iop,
							void * SendData_ip,
							UNS32 lSendDataSize_i,
							DriverReturnCode_t * ReturnCode_op); 
#endif /*__LAN9250_H__*/

/* EOF */


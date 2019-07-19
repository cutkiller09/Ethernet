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
#include "standard.h"
#include "cpu_def.h"
#include "Memory.h"
#include "LAN9250_PHY_Registers.h"
#include "LAN9250_MAC_Registers.h"
#include "LAN9250_SystemMemory.h"
#include "LAN9250.h"
#include "LAN9250_SPI.h"
#include "DataCoupling.h"

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

void LAN9250InstanceInit(LAN9250_Instance_t * LAN9250Instance, LAN9250_IO_Cfg_t * LANConfig)
{
	LANConfig->lIdTag = TAG_LAN9250_IO_CFG_E;
	LANConfig->lBaseAddress = DRIVERCONFIG_LAN_BASE_ARRD_C;
	LANConfig->cOwnMACAddress_a[0] = (UNS8)0x00U;
	LANConfig->cOwnMACAddress_a[1] = (UNS8)0x80U;
	LANConfig->cOwnMACAddress_a[2] = (UNS8)0xA2U;
	LANConfig->cOwnMACAddress_a[3] = (UNS8)0x10U;
	LANConfig->cOwnMACAddress_a[4] = (UNS8)0x90U;
	LANConfig->cOwnMACAddress_a[5] = (UNS8)0x6FU;
	LANConfig->bAutonegotiationMode = FALSE;  // Not functional with TRUE
	LANConfig->bDuplexMode = TRUE;  
	LANConfig->bPromiscuousMode = FALSE;
	LANConfig->SpeedMode = LAN9250_SPEED_MODE_100_MBPS_E; // FOR TEST DEBUG PURPOSE ONLY , REPLACE WITH LAN9250_SPEED_MODE_10_MBPS_E
	
	LAN9250Instance->InstanceCfg_p = LANConfig;
	
	LAN9250Instance->lIdTag = TAG_LAN9250_INSTANCE_E;
	LAN9250Instance->lReserved_a[0] = (UNS8)0U;
	LAN9250Instance->lReserved_a[1] = (UNS8)0U;
	LAN9250Instance->lReserved_a[2] = (UNS8)0U;
	LAN9250Instance->lReserved_a[3] = (UNS8)0U;
}

/***************************************************************/
/* Global function : LAN9250_Init                              */
/***************************************************************/
void LAN9250_Init	(void * Instance_iop,
					void * Config_ip,
					DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
	DriverReturnCode_t			Result        = DRVRC_HARD_FAIL_E;
    LAN9250_Instance_t *		LANInstance_p = (LAN9250_Instance_t *)Instance_iop;
    LAN9250_IO_Cfg_t *			LANCfg_p      = (LAN9250_IO_Cfg_t *)Config_ip;
    LAN9250_HMAC_Registers_t	HMAC_Regs;
    BOOLEAN		bSuccess = FALSE;
	UNS32		lTimeout;
	UNS32		PowerMgtReg;
    UNS32		LAN9250ReadyBit;
	UNS32		LAN9250ResetControlReg;
	UNS32		LAN9250HW_CFG_ControlReg;
	UNS32		LAN9250DigitalResetBit;
	UNS32		LAN9250DeviceReadyBit;
	UNS32		LAN9250TXConfigReg;
	UNS32		LAN9250TXConfigBit;
	UNS32		LAN9250InterruptStatusReg;
	UNS32		LAN9250TXStopINTBit;
	UNS32		LAN9250InterruptConfigReg;
	UNS32		IRQOutputDisableReg;
	UNS32		lDebug = 0;
	UNS32		lCommand=0;
	UNS32       LAN9250E2PDataByte0;
	UNS32       LAN9250HW_E2P_CommandReg;
	UNS32       LAN9250E2PControllerBusyBit;

    UNS32 test;
	test = 0;
	
	//LANConfigInit(LANInstance_p);
	if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    {
        if (LANCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E)
        {
            LANInstance_p->InstanceCfg_p = LANCfg_p;
			
			SIU.PCR[LAN9250_RESET_PIN_C].B.OBE = (UNS16)1U;
			SIU.GPDO[LAN9250_RESET_PIN_C].B.PDO = (UNS16)0U;
            LAN9250_Wait_uSeconds(Instance_iop, LAN9250_INIT_WAIT_C);
			SIU.GPDO[LAN9250_RESET_PIN_C].B.PDO = (UNS16)1U;

            lTimeout = LAN9250_LAN_TIMEOUT_C;
            /* If the LAN9250 is not yet ready to be accessed, wait until it is ready */
			ReadRegistersLAN9250(LAN9250_PMT_CTRL_ADDR, &PowerMgtReg);
			LAN9250ReadyBit = PowerMgtReg & LAN9250_READY_BIT_MASK_C;
            while ((LAN9250ReadyBit == (UNS32)0U) && (lTimeout > (UNS32)0U))
            {
                /* MCU frequency independent waiting for time out */
                LAN9250_Wait_uSeconds(Instance_iop, LAN9250_INIT_WAIT_C);
                lTimeout--;
				
				ReadRegistersLAN9250(LAN9250_PMT_CTRL_ADDR, &PowerMgtReg);
				LAN9250ReadyBit = PowerMgtReg & LAN9250_READY_BIT_MASK_C;
            }
            /* Check timeout */
            if (lTimeout > (UNS32)0U)
            {
                /* Soft Reset */
                lTimeout = LAN9250_LAN_TIMEOUT_C;
                /* Write 1 to bit 0 (Digital Reset Bit) in the Reset Control Register(RESET_CTL) */
				WriteRegistersLAN9250(LAN9250_RESET_CTL_ADDR, LAN9250_RESET_CTL_C);
                /* Wait at least 2 us, at which time the SOFT RESET is complete */
				ReadRegistersLAN9250(LAN9250_RESET_CTL_ADDR, &LAN9250ResetControlReg);
				LAN9250DigitalResetBit = LAN9250ResetControlReg & LAN9250_DIGITAL_RESET_BIT_MASK_C;
                while ((LAN9250DigitalResetBit == (UNS32)1U) && (lTimeout > (UNS32)0U))
                {
                    /* MCU frequency independent waiting for time out */
                    LAN9250_Wait_uSeconds(Instance_iop, LAN9250_DIGITAL_RESET_WAIT_C);
                    lTimeout--;
					
					ReadRegistersLAN9250(LAN9250_RESET_CTL_ADDR, &LAN9250ResetControlReg);
					LAN9250DigitalResetBit = LAN9250ResetControlReg & LAN9250_DIGITAL_RESET_BIT_MASK_C;
					
				/* While the EEPROM Loader is active, the Device Ready (READY) bit of the Hardware Configuration Register
				(HW_CFG) is cleared */
					// ReadRegistersLAN9250(LAN9250_HW_CFG_ADDR, &LAN9250HW_CFG_ControlReg);

					// ReadRegistersLAN9250(LAN9250_E2P_CMD_ADDR, &LAN9250HW_E2P_CommandReg);
					// LAN9250E2PControllerBusyBit = LAN9250HW_E2P_CommandReg & LAN9250_E2P_CONTROLLER_BUSY_BIT_C;
					// while(LAN9250E2PControllerBusyBit == 1)
					// {
						// /**/
						// lCommand = 0x00000000;
						// /**/
						// WriteRegistersLAN9250((UNS16)LAN9250_E2P_CMD_ADDR, lCommand);
						// /**/
						/*BYTE_TEST Register Read*/
						// ReadRegistersLAN9250(LAN9250_BYTE_TEST_ADDR, &test);
						// ReadRegistersLAN9250(LAN9250_RESET_CTL_ADDR, &lCommand);
						// LAN9250E2PDataByte0 = lCommand & LAN9250_E2P_DATA_BYTE0_MASK_C;
						// if(LAN9250E2PDataByte0 == (UNS32)0xA5)
						// {
							
						// }
					// }
					

                }
				
				/* While the EEPROM Loader is active, the Device Ready (READY) bit of the Hardware Configuration Register
				(HW_CFG) is cleared */
					ReadRegistersLAN9250(LAN9250_E2P_CMD_ADDR, &LAN9250HW_E2P_CommandReg);
					LAN9250E2PControllerBusyBit = LAN9250HW_E2P_CommandReg & LAN9250_E2P_CONTROLLER_BUSY_BIT_C;
					while(LAN9250E2PControllerBusyBit == 1)
					{
						/**/
						lCommand = 0x00000000;
						/**/
						WriteRegistersLAN9250((UNS16)LAN9250_E2P_CMD_ADDR, lCommand);
						/**/
						ReadRegistersLAN9250(LAN9250_E2P_CMD_ADDR, &LAN9250HW_E2P_CommandReg);
						LAN9250E2PControllerBusyBit = LAN9250HW_E2P_CommandReg & LAN9250_E2P_CONTROLLER_BUSY_BIT_C;
						if(LAN9250E2PControllerBusyBit == 0)
						{
							ReadRegistersLAN9250(LAN9250_E2P_DATA_ADDR, &lCommand);
						}
						LAN9250E2PDataByte0 = lCommand & LAN9250_E2P_DATA_BYTE0_MASK_C;
						if(LAN9250E2PDataByte0 == (UNS32)0xA5)
						{
							
						}
					}
					
                /* Check timeout */
                if (lTimeout > (UNS32)0U)
                {
                    /* Configure of Transmitter */
					WriteRegistersLAN9250(LAN9250_HW_CFG_ADDR, LAN9250_HW_CFG_C );
					
		// FOR DEBUG PURPOSE ONLY
		ReadRegistersLAN9250(LAN9250_HW_CFG_ADDR , &lDebug); 
		// FOR DEBUG PURPOSE ONLY
		
                    /* Configure TX Status FIFO level interrupt threshold */
					WriteRegistersLAN9250(LAN9250_FIFO_INT_ADDR, LAN9250_FIFO_INT_C );
                    /* Discard the Tx data FIFO and TX status FIFO */
					WriteRegistersLAN9250(LAN9250_TX_CFG_ADDR, LAN9250_TX_CFG_C );

                    lTimeout = LAN9250_LAN_TIMEOUT_C;
                    /* Wait till the transmitter will be stopped */
					ReadRegistersLAN9250(LAN9250_TX_CFG_ADDR, &LAN9250TXConfigReg);
					LAN9250TXConfigBit = LAN9250TXConfigReg & LAN9250_STOP_TX_BIT_C;
                    while ((LAN9250TXConfigBit == (UNS32)1U) && (lTimeout > (UNS32)0U))
                    {
                        /* MCU frequency independent waiting for time out */
                        LAN9250_Wait_uSeconds(Instance_iop, ONE_C);
                        lTimeout--;
						
						ReadRegistersLAN9250(LAN9250_TX_CFG_ADDR, &LAN9250TXConfigReg);
						LAN9250TXConfigBit = LAN9250TXConfigReg & LAN9250_STOP_TX_BIT_C;
                    }
					/*Transmitter Stop Interrupt*/
					ReadRegistersLAN9250(LAN9250_INT_STS_ADDR, &LAN9250InterruptStatusReg);
					LAN9250TXStopINTBit = LAN9250InterruptStatusReg & LAN9250_STOP_TX_INT_BIT_C;
                    if ((lTimeout > (UNS32)0U) && (LAN9250TXStopINTBit != (UNS32)0U))
                    {
                        /* Clear register RX_CFG, specify no padding at start or end */
                        WriteRegistersLAN9250(LAN9250_RX_CFG_ADDR, LAN9250_RX_CFG_C );
                        /* Discard the Rx data FIFO and RX status FIFO */
                        bSuccess = LAN9250_HMacReadReg(Instance_iop, LAN9250_HMAC_CR_E,
										 &HMAC_Regs.HMAC_CR.lReg);
						/* Check if the Receiver is disabled */
                        if (HMAC_Regs.HMAC_CR.Bit.RX_EN == (UNS32)0U)
                        {
							/*Clear the RX Data and Status FIFO*/
							WriteRegistersLAN9250(LAN9250_RX_CFG_ADDR, LAN9250_RX_CFG_CLEAR_C );
                        }

                        /* Configure automatic flow control */
						bSuccess = LAN9250_HMacWriteReg(Instance_iop, LAN9250_HMAC_FLOW_E, LAN9250_AFC_CFG_C);
                        /*LEDs configure */
                        WriteRegistersLAN9250(LAN9250_LED_CFG_ADDR, LAN9250_LED_CFG_C  );
						
                        /* Configure IRQ pin - disable IRQ output */
						ReadRegistersLAN9250(LAN9250_IRQ_CFG_ADDR, &LAN9250InterruptConfigReg);
						IRQOutputDisableReg = LAN9250InterruptConfigReg & LAN9250_IRQ_OUTPUT_DISABLE_MASK_C;
						WriteRegistersLAN9250(LAN9250_IRQ_CFG_ADDR, IRQOutputDisableReg );
						/* Configure internal interrupts - disable any interrupt */
						WriteRegistersLAN9250(LAN9250_INT_EN_ADDR, LAN9250_INT_EN_C );
                        /* Clear status of all interrupts */
						WriteRegistersLAN9250(LAN9250_INT_STS_ADDR, LAN9250_INT_STS_C );
                        /* Configure Power Management */
						WriteRegistersLAN9250(LAN9250_PMT_CTRL_ADDR, LAN9250_PMT_CTR_C );
						/* Configure Interrupts*/
						WriteRegistersLAN9250(LAN9250_IRQ_CFG_ADDR, LAN9250_IRQ_CFG_C );
						/* Disable General Purpose Timer */
						WriteRegistersLAN9250(LAN9250_GPT_CFG_ADDR, LAN9250_GPT_CFG_C );
						/* Configure MAC address high */
						HMAC_Regs.ADDR_H.Bit.HMAC_ADDR_H =(*(UNS16*)&LANCfg_p->cOwnMACAddress_a[FOUR_C]);
                        /* Store the upper 16 bits of MAC */
                        bSuccess &= LAN9250_HMacWriteReg(Instance_iop, LAN9250_HMAC_ADDRH_E,
                                    HMAC_Regs.ADDR_H.lReg);
						/* Configure MAC address low */
                        HMAC_Regs.ADDR_L.lReg =(*(UNS32*)&LANCfg_p->cOwnMACAddress_a[ZERO_C]);
                        /* Store the lower 32 bits of MAC */
                        bSuccess &= LAN9250_HMacWriteReg(Instance_iop, LAN9250_HMAC_ADDRL_E,
                                         HMAC_Regs.ADDR_L.lReg);

                        /* Enable/disable Promiscuous Mode */
                        bSuccess &= LAN9250_HMacReadReg(Instance_iop, LAN9250_HMAC_CR_E,
                                         &HMAC_Regs.HMAC_CR.lReg);
                        if (LANCfg_p->bPromiscuousMode == FALSE)
                        {
                            /* Disable Promiscuous Mode and enable perfect filtering */
                            HMAC_Regs.HMAC_CR.Bit.PROMISCUOUS    = (UNS32)0U;
                            HMAC_Regs.HMAC_CR.Bit.HASH_PERF_FILT = (UNS32)0U;
                        }
                        else
                        {
                            /* Enable Promiscuous Mode and disable perfect filtering */
                            HMAC_Regs.HMAC_CR.Bit.PROMISCUOUS    = (UNS32)1U;
                            HMAC_Regs.HMAC_CR.Bit.HASH_PERF_FILT = (UNS32)1U;
                        }
						/* Save the changes in the MAC Control Register */
                        bSuccess &= LAN9250_HMacWriteReg(Instance_iop, LAN9250_HMAC_CR_E,
                                         HMAC_Regs.HMAC_CR.lReg);
                    }
                }
            }
        }
        else
        {
            Result = DRVRC_SOFT_FAIL_E;
        }
    }
    else
    {
        Result = DRVRC_SOFT_FAIL_E;
    }

    if (bSuccess == FALSE)
    {
        LANInstance_p->InstanceCfg_p = NULL;
    }
    else
    {
        Result = DRVRC_NO_ERROR_E;
    }
    *ReturnCode_op = Result;
}

/***************************************************************/
/* Global function : LAN9250_Read                              */
/***************************************************************/
void LAN9250_Read	(void * Instance_iop,
					void * ReceiveData_op,
					UNS32 lReceiveDataSize_i,
					DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
	LAN9250_Instance_t *	LANInstance_p = (LAN9250_Instance_t *)Instance_iop;
	DriverReturnCode_t		Result;


    if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    {
        if (LANInstance_p->InstanceCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E)
        {
            LAN9250_ReceivePacket(Instance_iop, ReceiveData_op, lReceiveDataSize_i, &Result);
        }
        else
        {
            Result = DRVRC_SOFT_FAIL_E;
        }
    }
    else
    {
        Result = DRVRC_SOFT_FAIL_E;
    }
	

    *ReturnCode_op = Result;
}

/***************************************************************/
/* Global function : LAN9250_Write                             */
/***************************************************************/
void LAN9250_Write	(void * Instance_iop,
                    void * SendData_ip,
					UNS32 lSendDataSize_i,
                    DriverReturnCode_t * ReturnCode_op)
{
    /*#ACD# M(UDMF::UID_693EA820-6933-4a1e-B754-1E79EC630A1B) LAN9250_Write */
	LAN9250_Instance_t *	LANInstance_p = (LAN9250_Instance_t *)Instance_iop;
	DriverReturnCode_t		Result;
    
	// to be modified
	// if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    // {
        // if (LANInstance_p->InstanceCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E)
        // {
            LAN9250_TransmitPacket(Instance_iop, SendData_ip, lSendDataSize_i, &Result);
        // }
        // else
        // {
            // Result = DRVRC_SOFT_FAIL_E;
        // }
    // }
    // else
    // {
        // Result = DRVRC_SOFT_FAIL_E;
    // }

    *ReturnCode_op = Result;
}

/***************************************************************/
/* Global function : LAN9250_Test                              */
/***************************************************************/
void LAN9250_Test	(void * Instance_iop,
					void * TestData_ip,
					DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
	LAN9250_Instance_t *	LANInstance_p	= (LAN9250_Instance_t *)Instance_iop;
	DriverReturnCode_t		Result			= DRVRC_NO_ERROR_E;
	UNS32		lTemp;
	UNS32		ByteTestReg;
	UNS32		InterruptEnableReg;

    if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    {
        if (LANInstance_p->InstanceCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E)
        {
            /* Check that byte order is correct */
			ReadRegistersLAN9250(LAN9250_BYTE_TEST_ADDR, &ByteTestReg);
            if (ByteTestReg != LAN9250_BYTE_TEST_C)
            {
                Result = DRVRC_HARD_FAIL_E;
            }
            else
            {
				/*Read the Interrupt Enable Register et save it to a variable*/
                ReadRegistersLAN9250(LAN9250_INT_EN_ADDR, &lTemp);
				
				/*Test the Interrupt Enable Register with a test pattern value*/
                WriteRegistersLAN9250(LAN9250_INT_EN_ADDR, LAN9250_TEST_PATTERN_C);
				ReadRegistersLAN9250(LAN9250_INT_EN_ADDR, &InterruptEnableReg);
                if (InterruptEnableReg == LAN9250_TEST_PATTERN_C)
                {
                    Result = DRVRC_HARD_FAIL_E;
                }
				/*Rewrite back the temporary value previously saved to Interrupt Enable Register*/
                WriteRegistersLAN9250(LAN9250_INT_EN_ADDR, lTemp);
            }
        }
        else
        {
            Result = DRVRC_SOFT_FAIL_E;
        }
    }
    else
    {
        Result = DRVRC_SOFT_FAIL_E;
    }

    *ReturnCode_op = Result;
}

/***************************************************************/
/* Global function : LAN9250_Control                           */
/***************************************************************/
void LAN9250_Control(void * Instance_iop, 
					void * ControlData_ip,
					DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
	LAN9250_Instance_t *	LANInstance_p	= (LAN9250_Instance_t *)Instance_iop;
	LAN9250_ControlData_t *	LANControl_p	= (LAN9250_ControlData_t *)ControlData_ip;
	DriverReturnCode_t		Result			= DRVRC_NO_ERROR_E;
	UNS32		FreeRunCounter;

    if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    {
        if ((LANInstance_p->InstanceCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E) &&
            (LANControl_p->lIdTag == TAG_LAN9250_CONTROL_DATA_E))
        {
            switch (LANControl_p->Command)
            {
                case LAN9250_CMD_GET_TIME_E:
                    ReadRegistersLAN9250(LAN9250_FREE_RUN_ADDR, &FreeRunCounter);
                    LANControl_p->lParameter = FreeRunCounter;
                    break;

                case LAN9250_CMD_WAIT_E:
                    LAN9250_Wait_uSeconds(Instance_iop, LANControl_p->lParameter);
                    break;

                default:
                    Result = DRVRC_INVALID_PARAMETER_E;
            }
        }
        else
        {
            Result = DRVRC_SOFT_FAIL_E;
        }
    }
    else
    {
        Result = DRVRC_SOFT_FAIL_E;
    }

    *ReturnCode_op = Result;
}

/***************************************************************/
/* Global function : LAN9250_Start                             */
/***************************************************************/
void LAN9250_Start	(void * Instance_iop,
					UNS16 nStartType_i,
					DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
    DriverReturnCode_t      Result        = DRVRC_NO_ERROR_E;
    LAN9250_Instance_t *    LANInstance_p = (LAN9250_Instance_t *)Instance_iop;
    LAN9250_PHY_Registers_t PHY_Regs;
    LAN9250_HMAC_Registers_t HMAC_Regs;
    BOOLEAN		bSuccess;
    UNS32		lTimeout;
	UNS32		TransmitConfigReg;
	UNS32		TransmitterEnableBit;
	UNS32		lDebug;
	UNS32		LAN9250TXConfigReg;
	
	if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    {
        if (LANInstance_p->InstanceCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E)
        {
            /* Check either Auto-Negotiation is enabled           */
            if (LANInstance_p->InstanceCfg_p->bAutonegotiationMode == TRUE)
            {
                PHY_Regs.PHY_AN_ADV.Bit._10BASE_T_FDPX = (UNS16)1U;
                bSuccess = LAN9250_PhyWriteReg(Instance_iop, LAN9250_PHY_AN_ADV_E,
                                PHY_Regs.PHY_AN_ADV.nReg);
                /* Restart Auto-Negotiation before the new abilities will be advertised */
                bSuccess &= LAN9250_PhyReadReg(Instance_iop, LAN9250_PHY_BASIC_CONTROL_E,
                                &PHY_Regs.PHY_BASIC_CONTROL.nReg);
                PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_AN = (UNS16)1U;
                PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_RST_AN = (UNS16)1U;
                bSuccess &= LAN9250_PhyWriteReg(Instance_iop, LAN9250_PHY_BASIC_CONTROL_E,
                              PHY_Regs.PHY_BASIC_CONTROL.nReg);

                /* Wait till Auto-Negotiation process is complete: it takes ~2sec */
                lTimeout = LAN9250_LINK_TIMEOUT_C;
                do
                {
                    bSuccess &= LAN9250_PhyReadReg(Instance_iop, LAN9250_PHY_BASIC_CONTROL_E,
                                    &PHY_Regs.PHY_BASIC_CONTROL.nReg);
                    LAN9250_Wait_uSeconds(Instance_iop, LAN9250_LINK_WAIT_C);
                    lTimeout--;
                } while ((PHY_Regs.PHY_BASIC_STATUS.Bit.AUTONEG_COMPLETE == (UNS16)0U) &&
                         (bSuccess == TRUE) &&
                         (lTimeout > (UNS32)0U));

                /* Check if the Link is down */
                if ((PHY_Regs.PHY_BASIC_STATUS.Bit.LINK_STATUS == (UNS16)0U)  ||
                    (bSuccess == FALSE) ||
                    (lTimeout == (UNS32)0U))
                {
                    /* Failed to complete Auto-Negotiation restart */
                    Result = DRVRC_TIMEOUT_E;
                }
            }
            else
            {
                /* Set Ethernet mode: 10/100 Mbps, Auto-Negotiation disabled, FDPL/HDPL */
                PHY_Regs.PHY_BASIC_CONTROL.nReg = (UNS16)0U;
                if (LANInstance_p->InstanceCfg_p->bDuplexMode == TRUE)
                {
                    PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_DUPLEX = (UNS16)1U;
                }
                if (LANInstance_p->InstanceCfg_p->SpeedMode == LAN9250_SPEED_MODE_10_MBPS_E)
                {
                    PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_SPEED_SEL_LSB = (UNS16)0U;
                }
				else
                {
                    PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_SPEED_SEL_LSB = (UNS16)1U;
                }
				
				/* PHY Soft Reset for normal operation, loopback disabled and collision test mode disabled, */
				PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_SRST = (UNS16)0U;
				PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_LOOPBACK = (UNS16)0U;
				PHY_Regs.PHY_BASIC_CONTROL.Bit.PHY_COL_TEST = (UNS16)0U;
				
                bSuccess = LAN9250_PhyWriteReg(Instance_iop, LAN9250_PHY_BASIC_CONTROL_E,
                                PHY_Regs.PHY_BASIC_CONTROL.nReg);
                if (bSuccess != TRUE)
                {
                    Result = DRVRC_HARD_FAIL_E;
                }
				
		/* For DEBUG PURPOSE ONLY */
		bSuccess  = LAN9250_PhyReadReg(&LAN9250Instance, LAN9250_PHY_BASIC_CONTROL_E, &(PHY_Regs.PHY_BASIC_CONTROL.nReg));
		bSuccess  = LAN9250_PhyReadReg(&LAN9250Instance, LAN9250_PHY_BASIC_STATUS_E, &(PHY_Regs.PHY_BASIC_STATUS.nReg));		
		ReadRegistersLAN9250(LAN9250_TX_CFG_ADDR, &LAN9250TXConfigReg);
		ReadRegistersLAN9250(LAN9250_HW_CFG_ADDR , &lDebug);
		/* For DEBUG PURPOSE ONLY */
            }

            if (Result == DRVRC_NO_ERROR_E)
            {
						/* For DEBUG PURPOSE ONLY */
                // /* Waiting till Link is up */
                // lTimeout = LAN9250_LINK_TIMEOUT_C;
                // do
                // {
                    // bSuccess = LAN9250_PhyReadReg(Instance_iop, LAN9250_PHY_BASIC_STATUS_E,
                                    // &(PHY_Regs.PHY_BASIC_STATUS.nReg));
                    // LAN9250_Wait_uSeconds(Instance_iop, LAN9250_LINK_WAIT_C);
                    // lTimeout--;
					
                // } while ((PHY_Regs.PHY_BASIC_STATUS.Bit.LINK_STATUS == (UNS16)0U) &&
                         // (bSuccess == TRUE) &&
                         // (lTimeout > (UNS32)0U));

                /* Read current state of MAC control register */
                bSuccess = LAN9250_HMacReadReg(Instance_iop, LAN9250_HMAC_CR_E,
                                &HMAC_Regs.HMAC_CR.lReg);

                /* If PHYs is in full duplex mode, enable full duplex in MAC */
                bSuccess &= LAN9250_PhyReadReg(Instance_iop, LAN9250_PHY_SPECIAL_CONTROL_STATUS_E,
                                &PHY_Regs.PHY_SPECIAL_CONTROL_STATUS.nReg);
                PHY_Regs.PHY_SPECIAL_CONTROL_STATUS.nReg &= LAN9250_PHY_SPEED_STATUS_FDX_C;
                if (PHY_Regs.PHY_SPECIAL_CONTROL_STATUS.nReg != (UNS16)0U)
                {
                    /* Get the current Duplex mode regardless of which mode is configured */
                    bSuccess &= LAN9250_PhyReadReg(Instance_iop, LAN9250_PHY_BASIC_STATUS_E,
                                    &PHY_Regs.PHY_BASIC_STATUS.nReg);
                    if ((PHY_Regs.PHY_BASIC_STATUS.Bit._100BASE_X_FDPX == (UNS16)1U) ||
                        (PHY_Regs.PHY_BASIC_STATUS.Bit._10BASE_T_FDPX == (UNS16)1U))
                    {
                        /* Configure the MAC module into the full-duplex mode */
                       HMAC_Regs.HMAC_CR.Bit.FULL_DPX_MODE = (UNS32)1U;
                    }
                }

                /* Enable Rx and Tx in MAC */
                HMAC_Regs.HMAC_CR.Bit.TX_EN = (UNS32)1U;
                HMAC_Regs.HMAC_CR.Bit.RX_EN = (UNS32)1U;
				
				/*Receive All Mode Disabled and Loopback disabled for normal operation*/
				HMAC_Regs.HMAC_CR.Bit.LOOPBACK    = (UNS32)0U;
				HMAC_Regs.HMAC_CR.Bit.DIS_RX_OWN     = (UNS32)0U;

                /* Update MAC control register */
                bSuccess &= LAN9250_HMacWriteReg(Instance_iop, LAN9250_HMAC_CR_E,
                                HMAC_Regs.HMAC_CR.lReg);

                /* Enable transmission */
				ReadRegistersLAN9250(LAN9250_TX_CFG_ADDR, &TransmitConfigReg);
			    TransmitterEnableBit = TransmitConfigReg & LAN9250_TX_ON_BIT_MASK_C;
                if (TransmitterEnableBit == (UNS32)0U)
                {
					SetLAN9250RegistersBits(LAN9250_TX_CFG_ADDR, LAN9250_TX_ON_BITNUMBER_C );
                }

                if (lTimeout == (UNS32)0U)
                {
                    Result = DRVRC_TIMEOUT_E;
                }
                else if (bSuccess == FALSE)
                {
                    Result = DRVRC_HARD_FAIL_E;
                }
            }
        }
        else
        {
            Result = DRVRC_SOFT_FAIL_E;
        }
    }
    else
    {
        Result = DRVRC_SOFT_FAIL_E;
    }

    *ReturnCode_op = Result;
}

/***************************************************************/
/* Global function : LAN9250_Halt                              */
/***************************************************************/
void LAN9250_Halt	(void * Instance_iop, 
					DriverReturnCode_t * ReturnCode_op)
{
    /* Declarations */
	LAN9250_Instance_t *		LANInstance_p = (LAN9250_Instance_t *)Instance_iop;
	LAN9250_HMAC_Registers_t	HMAC_Regs;
	DriverReturnCode_t			Result;
	BOOLEAN		bSuccess;
	UNS32		TX_CFG_Register;
	UNS32		TX_ON_Bit;
    
    /* The Host MAC transmitter is halted by clearing the TX_ON bit in TX_CFG Register */
    if (LANInstance_p->lIdTag == TAG_LAN9250_INSTANCE_E)
    {
        if (LANInstance_p->InstanceCfg_p->lIdTag == TAG_LAN9250_IO_CFG_E)
        {
			ReadRegistersLAN9250((UNS16)LAN9250_TX_CFG_ADDR, &TX_CFG_Register);
            TX_ON_Bit = (UNS32)((TX_CFG_Register & LAN9250_TX_ON_MASK_C)>>1); 
            if(TX_ON_Bit == (UNS32)1)
            {
                /*TX_ON is bit 1 on TX_CFG register*/
                ClearLAN9250RegistersBits((UNS16)LAN9250_TX_CFG_ADDR, 1);
            }

            /*Read current state of LAN9250's HMAC control register */
            bSuccess = LAN9250_HMacReadReg(Instance_iop, LAN9250_HMAC_CR_E, &HMAC_Regs.HMAC_CR.lReg);
            if (bSuccess == TRUE)
            {
                /* Host HMAC Transmitter is disabled by clearing the bit3 TXEN in HMAC_CR register. */
                if (HMAC_Regs.HMAC_CR.Bit.TX_EN == 1)
                {
                    HMAC_Regs.HMAC_CR.Bit.TX_EN = 0;
                }
                
                /* Host HMAC Receiver is disabled by clearing the bit2 RXEN in HMAC_CR register named. */
                if (HMAC_Regs.HMAC_CR.Bit.RX_EN == 1)
                {
                    HMAC_Regs.HMAC_CR.Bit.RX_EN = 0;
                }
                /* Write updated state of HMAC control register */
                bSuccess = LAN9250_HMacWriteReg(Instance_iop, LAN9250_HMAC_CR_E,
                        HMAC_Regs.HMAC_CR.lReg);
            }

            if (bSuccess == TRUE)
            {
                Result = DRVRC_NO_ERROR_E;
            }
            else
            {
                Result = DRVRC_HARD_FAIL_E;
            }
        }
        else
        {
            Result = DRVRC_SOFT_FAIL_E;
        }
    }
    else
    {
        Result = DRVRC_SOFT_FAIL_E;
    }

    *ReturnCode_op = Result;
    /*#end ACD# LAN9250_Halt */
}

/***************************************************************/
/* Function : LAN9250_HMacNotBusy                               */
/***************************************************************/
BOOLEAN LAN9250_HMacNotBusy	(void * Instance_ip)
{
	/* Declarations */
	BOOLEAN		bResult = TRUE;
	UNS32		lTimeout = LAN9250_HMAC_TIMEOUT_C;
	UNS32		HMAC_CSR_CMD_Register;
	UNS32		lHMAC_Busy;
    
    /* Wait for HMAC not busy */
    do
    {
        /* frequency independent waiting */
        LAN9250_Wait_uSeconds(Instance_ip, 1); 
        /* Host HMAC CSR Interface Command register Read by SPI*/
        ReadRegistersLAN9250(LAN9250_HMAC_CSR_CMD_ADDR, &HMAC_CSR_CMD_Register);
        /* Host HMAC CSR Busy Bit by using a mask */
        //lHMAC_Busy = (UNS32)((HMAC_CSR_CMD_Register)& LAN9250_HMAC_CSR_BUSY_MASK);
		lHMAC_Busy = (UNS32)(HMAC_CSR_CMD_Register & LAN9250_HMAC_CSR_BUSY_MASK_C);
        lTimeout--;
    } while ((lHMAC_Busy != (UNS32)0U) && 
			lTimeout != (UNS32)0U);

    /* Check if timeout occurred during waiting */
    if (lTimeout == (UNS32)0U)
    {
        bResult = FALSE;
    }

    return bResult;
}

/***************************************************************/
/* Function : LAN9250_HMACReadReg                               */
/***************************************************************/
BOOLEAN LAN9250_HMacReadReg (void * Instance_ip,
							LAN9250_HMAC_Reg_Index_t RegIndex_i,
							UNS32 * lData_op)
{
	/* Declarations */
	BOOLEAN	bResult;
	UNS32	lCommand;
    
    /* Initialization of default return value */
    bResult = LAN9250_HMacNotBusy(Instance_ip);
    if (bResult == TRUE)
    {
        /* Compound HMAC command */
        lCommand = (LAN9250_HMAC_READ_CMD_C | ((UNS32)RegIndex_i & LAN9250_HMAC_ADDR_MASK_C));
		
        /* Write HMAC command to register HMAC_CSR_CMD by using SPI */
        WriteRegistersLAN9250((UNS16)LAN9250_HMAC_CSR_CMD_ADDR, lCommand);
        /* Read a dummy value from the BYTE_TEST register */
        ReadRegistersLAN9250(LAN9250_BYTE_TEST_ADDR, &lCommand);

        /* Wait until data valid indication (with timeout) */
        bResult = LAN9250_HMacNotBusy(Instance_ip);
        if (bResult == TRUE)
        {
            /* Read register HMAC_CSR_DATA into Data */
            ReadRegistersLAN9250(LAN9250_HMAC_CSR_DATA_ADDR, lData_op);
        }
    }

    return bResult;
}

/***************************************************************/
/* Function : LAN9250_HMACWriteReg                              */
/***************************************************************/
BOOLEAN LAN9250_HMacWriteReg 	(void * Instance_ip,
								LAN9250_HMAC_Reg_Index_t RegIndex_i,
								UNS32 lData_i)
{
	/* Declarations */
	BOOLEAN	bResult;
	UNS32	lCommand;
    
    /* Initialization of default return value */
    bResult = LAN9250_HMacNotBusy(Instance_ip);
    if (bResult == TRUE)
    {
        /* Write value to register HMAC_CSR_DATA */
        WriteRegistersLAN9250((UNS16)LAN9250_HMAC_CSR_DATA_ADDR, lData_i);
		
        /* Compound HMAC command */
        lCommand = (LAN9250_HMAC_WRITE_CMD_C | ((UNS32)RegIndex_i & LAN9250_HMAC_ADDR_MASK_C));
		
		/* Write HMAC command to register HMAC_CSR_CMD */
        WriteRegistersLAN9250(LAN9250_HMAC_CSR_CMD_ADDR, lCommand);
        
        /* Read a dummy value from the BYTE_TEST register */
        ReadRegistersLAN9250(LAN9250_BYTE_TEST_ADDR, &lCommand);

        /* Wait until data valid indication (with timeout) */
        bResult = LAN9250_HMacNotBusy(Instance_ip);
    }

    return bResult;
}

/***************************************************************/
/* Function : LAN9250_PhyNotBusy                               */
/***************************************************************/
BOOLEAN LAN9250_PhyNotBusy	(void * Instance_ip)
{
	/* Declarations */
	BOOLEAN		bResult  = TRUE;
	UNS32		lTimeout = LAN9250_PHY_TIMEOUT_C;
	UNS32		lPHY_Busy;
	
	LAN9250_Instance_t *    LANInstance_p = (LAN9250_Instance_t *)Instance_ip;

    /* Wait for PHY not busy */
    do
    {
        /* Read HMAC register MII_ACC */
        bResult = LAN9250_HMacReadReg(LANInstance_p, LAN9250_HMAC_MII_ACC_E, &lPHY_Busy);
        lPHY_Busy &= LAN9250_PHY_BUSY_MASK_C;
        LAN9250_Wait_uSeconds(LANInstance_p, 1); /* frequency independent waiting */
        lTimeout--;
    } while ((lPHY_Busy != (UNS32)0U) && /* PHY is not busy */
             (lTimeout != (UNS32)0U) && /* Timeout occurred */
             (bResult == TRUE)); /* HMAC read is unsuccessful (busy or other) */

    /* Check if timeout occurred during waiting */
    if (lTimeout == (UNS32)0U)
    {
        bResult = FALSE;
    }

    return bResult;
}

/***************************************************************/
/* Function : LAN9250_PhyReadReg                               */
/***************************************************************/
BOOLEAN LAN9250_PhyReadReg	(void * Instance_ip,
							LAN9250_PHY_Reg_Index_t RegIndex_i,
							UNS16 * nData_op)
{
	/* Declarations */
	LAN9250_Instance_t *	LANInstance_p = (LAN9250_Instance_t *)Instance_ip;
	BOOLEAN	bResult;
	UNS32	lCommand;
	UNS32	lData;
	
	/* Wait until PHY is not busy */
    bResult = LAN9250_PhyNotBusy(LANInstance_p);
    if (bResult == TRUE)
    {
        /* Set the address, index & direction (read from PHY) */
        lCommand = (LAN9250_PHY_READ_CMD_C |
                   (((UNS32)RegIndex_i & LAN9250_PHY_ADDR_MASK_C) <<
                     LAN9250_PHY_ADDR_SHIFT_C));
        /* Write command to HMAC register MII_ACC */
        bResult = LAN9250_HMacWriteReg(LANInstance_p, LAN9250_HMAC_MII_ACC_E, lCommand);
        if (bResult == TRUE) /* If write was successful */
        {
            /* Wait for the read to complete */
            bResult = LAN9250_PhyNotBusy(LANInstance_p);
            if (bResult == TRUE)
            {
                /* Read HMAC register MII_DATA and put the lower 16 bits into Data */
                bResult = LAN9250_HMacReadReg(LANInstance_p, LAN9250_HMAC_MII_DATA_E, &lData);
                if (bResult == TRUE)
                {
                    *nData_op = (UNS16)(lData & LAN9250_PHY_DATA_MASK_C);
                }
            }
        }
    }

    return bResult;
}

/***************************************************************/
/* Function : LAN9250_PhyWriteReg                              */
/***************************************************************/                           
BOOLEAN LAN9250_PhyWriteReg	(void * Instance_ip,
                            LAN9250_PHY_Reg_Index_t RegIndex_i,
                            UNS16 nData_i)
{
	/* Declarations */
	LAN9250_Instance_t *    LANInstance_p = (LAN9250_Instance_t *)Instance_ip;
	BOOLEAN	bResult;
	UNS32	lCommand;
	
    /* Wait until PHY is not busy */
    bResult = LAN9250_PhyNotBusy(LANInstance_p);
    if (bResult == TRUE)
    {
        /* write data to register MII_DATA */
        bResult = LAN9250_HMacWriteReg(LANInstance_p, LAN9250_HMAC_MII_DATA_E, (UNS32)nData_i);
        if (bResult == TRUE) /* if write was successful */
        {
            /* Set the address, index & direction (read from PHY) */
            lCommand = (LAN9250_PHY_WRITE_CMD_C |
                       (((UNS32)RegIndex_i & LAN9250_PHY_ADDR_MASK_C) <<
                       LAN9250_PHY_ADDR_SHIFT_C));
            /* Write command to HMAC register MII_ACC */
            bResult = LAN9250_HMacWriteReg(LANInstance_p, LAN9250_HMAC_MII_ACC_E, lCommand);
            if(bResult == TRUE)
            {
                /* Wait for the write to complete */
                bResult = LAN9250_PhyNotBusy(LANInstance_p);
            }
        }
    }

    return bResult;
}

/***************************************************************/
/* Function : LAN9250_ReceivePacket                            */
/***************************************************************/                            
void LAN9250_ReceivePacket	(void * Instance_ip,
                            void * Data_op,
                            UNS32 lLength_i,
                            DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
	LAN9250_RX_Status_t  RxStatus;
	DriverReturnCode_t   Result = DRVRC_HARD_FAIL_E;
	LAN9250_SystemMemory_t LAN9250SystemMemory;
	UNS32	lStatus;
	UNS32	lOffset;
	UNS32	lTimeout = LAN9250_LAN_TIMEOUT_C;
	UNS32	RXFIFOInfoReg;
	UNS32	RXStatusUsed;
	UNS32   lData;
	/*Read the RX Status FIFO used space*/
	ReadRegistersLAN9250(LAN9250_RX_FIFO_INF_ADDR, &RXFIFOInfoReg);
	RXStatusUsed = (UNS32)((UNS32)RXFIFOInfoReg & 0x0000FFFF);
	
	/* Check if the FIFO is empty */
    if (RXStatusUsed != (UNS32)0U)
	{
        /* Read the status word of the received packet */
        ReadRegistersLAN9250(lRX_Status_FIFO_Port_ADDR, &(RxStatus.lReg));
        lStatus = (RxStatus.lReg & LAN9250_RX_STATUS_FAILED_C);
		/* Check status of the received packet */
        if (lStatus != (UNS32)0U)
        {
            /* Activate the Fast forwarding to skip the packet at the head of the Rx Data FIFO */
            /* The size of discarding packet must be at least 4 DWORDs */
            if ((UNS32)RxStatus.Bit.PacketLength > LAN9250_MIN_PACKET_SIZE_C)
            {
				
				/* Initiate the fast forwarding (discarding) operation */
                WriteRegistersLAN9250(LAN9250_R_DP_CTRL_ADDR, LAN9250_RX_DP_CTRL_C);
				ReadRegistersLAN9250(LAN9250_R_DP_CTRL_ADDR, &(LAN9250SystemMemory.SYSTEM_CSR.RX_DP_CTRL.lReg)); 

                /* Wait till the Fast Forwarding operation is completed */
                while ((LAN9250SystemMemory.SYSTEM_CSR.RX_DP_CTRL.lReg != (UNS32)0U) &&
                       (lTimeout != (UNS32)0U))
                {
                    LAN9250_Wait_uSeconds(Instance_ip, ONE_C);
                    lTimeout--;
                                                                              
					ReadRegistersLAN9250(LAN9250_R_DP_CTRL_ADDR, &(LAN9250SystemMemory.SYSTEM_CSR.RX_DP_CTRL.lReg)); 
                }
                if (lTimeout == (UNS32)0U)
                {
                    Result = DRVRC_TIMEOUT_E;
                }
            }
            else
            {
                /* Clear RX FIFO */
                LAN9250_ClearRxFIFO(Instance_ip, (UNS32)RxStatus.Bit.PacketLength);
            }
        }
        else
        {
            if (lLength_i >= (UNS32)RxStatus.Bit.PacketLength)
            {
                /* Copy data */
                lStatus = ((UNS32)RxStatus.Bit.PacketLength + (UNS32)THREE_C) >>
                            (UNS32)TWO_C;
                for (lOffset = (UNS32)0U; lOffset < lStatus; lOffset++)
                {
					 ReadRegistersLAN9250(lRX_Data_FIFO_Port_ADDR, &lData);
                    ((UNS32 *)Data_op)[lOffset] = lData;
                }

                Result = DRVRC_NO_ERROR_E;
            }
            else
            {
                /* Clear RX FIFO */
                LAN9250_ClearRxFIFO(Instance_ip, (UNS32)RxStatus.Bit.PacketLength);
            }
        }
    }
    else
    {
        Result = DRVRC_NO_DATA_E;
    }

    *ReturnCode_op = Result;
    /*#end ACD# LAN9250_ReceivePacket */
}

/***************************************************************/
/* Function : LAN9250_TransmitPacket                           */
/***************************************************************/                            
void LAN9250_TransmitPacket (void * Instance_ip,
                             void * Data_ip,
                             UNS32 lLength_i,
                             DriverReturnCode_t * ReturnCode_op)
{
	/* Declarations */
	LAN9250_TX_Command_t TxCommand;
	LAN9250_TX_Status_t  TxStatus;
	BOOLEAN	bStatus;	
	UNS32	lDWords;
	UNS32	lStartTime;
	UNS32	lTimeout;
	UNS32	lData;
	UNS32	lTxFIFOInfoReg;
	UNS32	lTxStatusFIFOUsed;
	UNS32	lInterruptStatusReg;
	UNS32	lDebug1 = (UNS32)0U;
	UNS32	lDebug2 = (UNS32)0U;
	UNS32	lDebug3 = (UNS32)0U;
	UNS32	lDebug4 = (UNS32)0U;
	UNS32	lDebug5 = (UNS32)0U;
	UNS32	lDebug6 = (UNS32)0U;
	UNS32	lDebug7 = (UNS32)0U;
	UNS32	lDebug8 = (UNS32)0U;
	BOOLEAN bSuccess;
	UNS32	ban = (UNS32)0U;
	LAN9250_SystemMemory_t		System_Regs;
	LAN9250_HMAC_Registers_t	HMAC_Regs;
	LAN9250_PHY_Registers_t		PHY_Regs;
	
	/* FOR DEBUG PURPOSE ONLY */
	ReadRegistersLAN9250(LAN9250_TX_FIFO_INF_ADDR, &lTxFIFOInfoReg);
	lTxStatusFIFOUsed = (UNS32)(lTxFIFOInfoReg & TX_STATUS_FIFO_USED_MASK);
	/* FOR DEBUG PURPOSE ONLY */
	
	/*TX Command A*/
	TxCommand.A.lReg = (UNS32)0U;
    TxCommand.A.Bit.FirstSegment = (UNS32)1U;
    TxCommand.A.Bit.LastSegment = (UNS32)1U;
    TxCommand.A.Bit.BufferSize = (UNS32)lLength_i;

	/*TX Command B*/
    TxCommand.B.lReg = (UNS32)0U;
    TxCommand.B.Bit.PacketLength = (UNS32)lLength_i;

	TxCommand.B.Bit.PacketTag = (UNS32)((LAN9250_Instance_t *)Instance_ip)->lReserved_a[0];
    ((LAN9250_Instance_t *)Instance_ip)->lReserved_a[0]++;

    lDWords = (UNS32)((lLength_i + (UNS32)THREE_C) >> (UNS32)TWO_C);
	
	/* Start transmit of data to Tx-FIFO*/
	/* Write TxCmdA to Tx Data FIFO */
    WriteRegistersLAN9250(lTX_Data_FIFO_Port_ADDR, (UNS32)TxCommand.A.lReg);
    /* Write TxCmdB to Tx Data FIFO */	
    WriteRegistersLAN9250(lTX_Data_FIFO_Port_ADDR, (UNS32)TxCommand.B.lReg);
	
	/*Copy payload data into the TX Data FIFO*/
	while (lDWords > (UNS32)0U)
    {
        Memory_Copy8((UNS8*)&lData, (UNS8*)Data_ip, (UNS32)FOUR_C);
        /* Copy a uint32 data from local host Tx buffer to Tx FIFO */
        WriteRegistersLAN9250(lTX_Data_FIFO_Port_ADDR, (UNS32)lData);
        Data_ip = (void *)&((UNS8 *)Data_ip)[FOUR_C];
        lDWords--;
    }
	
	/*Wait until having data in TX Status FIFO then Read them*/
	*ReturnCode_op = DRVRC_NO_ERROR_E;
#pragma info: lDWords is always zero after while loop => No wait time
    //LAN9250_Wait_uSeconds(Instance_ip, lDWords);
    lDWords = (lLength_i << (UNS32)ONE_C);
    ReadRegistersLAN9250(LAN9250_FREE_RUN_ADDR, &lStartTime);
    do
    {
    	ReadRegistersLAN9250(LAN9250_FREE_RUN_ADDR, &lTimeout);
        if (lTimeout >= lStartTime)
        {
        	lTimeout -= lStartTime;
        }
        else
        {
        	lTimeout += (STDDEFINES_MAX_UINT32_C - lStartTime);
        }
        lTimeout = (lTimeout / LAN9250_TIMER_DIVIDER_C);
		/* Amount of space currently used in TX Status FIFO*/
		ReadRegistersLAN9250(LAN9250_TX_FIFO_INF_ADDR, &lTxFIFOInfoReg);
		lTxStatusFIFOUsed = (UNS32)(lTxFIFOInfoReg & TX_STATUS_FIFO_USED_MASK);
		
		// FOR DEBUG PURPOSE ONLY
		ReadRegistersLAN9250(LAN9250_HW_CFG_ADDR , &(System_Regs.SYSTEM_CSR.HW_CFG.lReg));
		
		bSuccess = LAN9250_HMacReadReg(&LAN9250Instance, LAN9250_HMAC_CR_E, &(HMAC_Regs.HMAC_CR.lReg));
		
		/* frequency independent waiting */
        LAN9250_Wait_uSeconds(Instance_ip, 1000);
		
		bSuccess  = LAN9250_PhyReadReg(&LAN9250Instance, LAN9250_PHY_BASIC_CONTROL_E, &(PHY_Regs.PHY_BASIC_CONTROL.nReg));
		
		/* frequency independent waiting */
        LAN9250_Wait_uSeconds(Instance_ip, 1000);
		
		bSuccess  = LAN9250_PhyReadReg(&LAN9250Instance, LAN9250_PHY_BASIC_STATUS_E, &(PHY_Regs.PHY_BASIC_STATUS.nReg));
		
		/* frequency independent waiting */
        LAN9250_Wait_uSeconds(Instance_ip, 1000);
		
		ReadRegistersLAN9250(lTX_Data_FIFO_Port_ADDR, &lDebug5); 
		
		// ReadRegistersLAN9250( , &lDebug6); 
		// ReadRegistersLAN9250( , &lDebug7); 
		// ReadRegistersLAN9250( , &lDebug8); 
		
		// FOR DEBUG PURPOSE ONLY
    }
    while ( lTxStatusFIFOUsed== (UNS32)0U); //&&
          // (lTimeout < lDWords));
    
	/* Read the status of TX FIFO */
    if (lTxStatusFIFOUsed != (UNS32)0U)
    {
		/*Read the TX Status FIFO Port*/
        ReadRegistersLAN9250(lTX_Status_FIFO_Port_ADDR, &(TxStatus.lReg ));
		/*Check the Transmitter Error Bit in Interrupt Status Register*/
		ReadRegistersLAN9250(LAN9250_INT_STS_ADDR, &lInterruptStatusReg);
        bStatus = ((lInterruptStatusReg & LAN9250_TX_ERROR_MASK_C) != (UNS32)0U);
		/*Check all bits in TX Status FIFO  to see if they are set*/
		bStatus |= (TxStatus.Bit.LossOfCarrier != (UNS32)0U);
        bStatus |= (TxStatus.Bit.LateCollision != (UNS32)0U);
        bStatus |= (TxStatus.Bit.ExcessCollisions != (UNS32)0U);
        bStatus |= (TxStatus.Bit.ExcessDeferral != (UNS32)0U);
        if (bStatus != FALSE)
        {
            /* Clear the interrupt status by setting it to 1*/
			SetLAN9250RegistersBits(LAN9250_INT_STS_ADDR, LAN9250_TX_ERROR_INT_BIT_C);
            *ReturnCode_op = DRVRC_NO_DATA_E;
        }
    }
    else
    { /* If the Tx FIFO status is empty the error was occurred during the transmission */
        *ReturnCode_op = DRVRC_NO_DATA_E;
    }
}

/***************************************************************/
/* Function : LAN9250_ClearRxFIFO                              */
/***************************************************************/                             
void LAN9250_ClearRxFIFO	(void * Instance_ip,
							UNS32 lSize_i)
{
	/* Declarations */
	UNS32	lLength;
	UNS32	lTemp;
    
	/*Number of DWord RX FIFO Data*/
    lLength = (lSize_i + (UNS32)THREE_C) >> (UNS32)TWO_C;
    while (lLength > (UNS32)0U)
    { 
		/*Clear the RX Data FIFO by reading the RX Data FIFO Port */
		ReadRegistersLAN9250(lRX_Data_FIFO_Port_ADDR, &lTemp);
        lLength--;
    }
}

/***************************************************************/
/* Function : LAN9250_Wait_uSeconds                            */
/***************************************************************/
void LAN9250_Wait_uSeconds	(void * Instance_ip,
                            UNS32 lDelay_i)
{
	/* Declarations */
	UNS32	lStartTime;
	UNS32	lCurrentTime;
	UNS32	lFree_Run_Register;
    
    ReadRegistersLAN9250(LAN9250_FREE_RUN_ADDR, &lFree_Run_Register);
    lStartTime = (lFree_Run_Register);
    do
    {
        ReadRegistersLAN9250(LAN9250_FREE_RUN_ADDR, &lFree_Run_Register);
        lCurrentTime = (lFree_Run_Register);
        if (lCurrentTime >= lStartTime)
        {
            lCurrentTime -= lStartTime;
        }
        else
        {
            lCurrentTime += (STDDEFINES_MAX_UINT32_C - lStartTime);
        }
        lCurrentTime = (lCurrentTime / LAN9250_TIMER_DIVIDER_C);
    } while (lCurrentTime < lDelay_i);
}
/*EOF*/
/***************************************************************/
/* FUNCTION : Sequence all treatments                          */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "hard_def.h"
#include "interface.h"
#include "hard_ini.h"
#include "trap_tab.h"

#include "dc_motor.h"
#include "anlg_acq.h"
#include "arinc_int.h"
#include "configuration.h"
#include "can_lb.h"
#include "cpu_load.h"
#include "disc_acq.h"
#include "disc_out.h"
#include "mon_register.h"
#include "mon_memory.h"
#include "sci_lb.h"
#include "soft_ini.h"
#include "torq_motor.h"
#include "wdg_lb.h"

#include "leak_int.h"

#include "LAN9250_SPI.h"
#include "LAN9250.h"
#include "DataCoupling.h"
#include "Packet.h"

#include "ad1255.h"
#include "ad2s1210.h"
#include "stp_motor.h"

#include "LAN9250_MAC_Registers.h"
#include "LAN9250_PHY_Registers.h"

#include "main_tsk.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
const UNS32 K_led_blink_delay_in_ms   = 500;
#define LED_ENABLE_2_0_MASK (UNS32)0xFFFFFFF8
#define GPIO_BUFFER_2_0_TYPE_MASK (UNS32)0x00000007
#define GPIO_DIRECTION_2_0_MASK (UNS32)0x00070000
#define LED_ON_2_0_MASK (UNS32)0x00000007
#define LED_OFF_2_0_MASK (UNS32)0xFFFFFFF8
#define ETHERNET_TYPE (UNS16)0x0800
#define DESTINATION_MAC_ADDR (UNS64)0x8000207A3F3E
#define SOURCE_MAC_ADDR (UNS64)0x800020203AAE
#define ETHERNET_PAYLOAD    (UNS64)0x080012156654ABCE
#define ETHERNET_IP_PACKET  (UNS64)0x0800ACBDFECBCDC5
#define ETHERNET_ARP_HEADER (UNS64)0x0800BACDECDFA382




/***************************************************************/
/*                                                             */
/*                        LOCAL TYPES                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
UNS32   last_led_blink_TIME;
UNS32   data_i;
UNS32   data_o;
BOOLEAN  InitTrue = TRUE;

EthernetHeader_t EthernetMAC;
EthernetPayload_t EthernetPayl;
EthernetFrame_t SendData_ip;

DriverReturnCode_t * ReturnCode_op;

/* Initialization for test Ethernet in maintask function */
LAN9250_HMAC_Reg_Index_t HMACRegIndex;
HMACRegIndex = LAN9250_HMAC_ADDRH_E;

LAN9250_PHY_Reg_Index_t PHYRegIndex;
BOOLEAN bResult = FALSE;
/***************************************************************/
/* Local function : BlinkLed                                   */
/***************************************************************/
void BlinkLed(void)
{
    /* Invert the state of the GPIO202 each 500 ms */
    if ((UNS32)(MC_PIT_NUMBER - last_led_blink_TIME) >= (K_led_blink_delay_in_ms / PIT_PERIOD))
    {
        SIU.GPDO[GPIO_LED_PIN].R = (UNS8)(~SIU.GPDO[GPIO_LED_PIN].R);
        last_led_blink_TIME = MC_PIT_NUMBER;
    }
    else
    {
    }
}

/***************************************************************/
/* Local function : DataExchangeLAN9250                                   */
/***************************************************************/
void DataExchangeLAN9250(void)
{
	UNS32 lSendDataSize_i = (UNS32)24;
	UNS32 lReceiveDataSize_i = (UNS32)24;
	UNS8  i;
	UNS32 * ReceiveData_op;
	DriverReturnCode_t  ReturnCode_op;
	UNS16 nStartType_i = (UNS16)0U; /* TO VERIFY !!!! UNUSED*/

	UNS8 DESTINATION_MAC_ADDR_TAB[6] = {0x80,0x00,0x20,0x7A,0x3F,0x3E};
	UNS8 SOURCE_MAC_ADDR_TAB[6] = {0x80,0x00,0x20,0x20,0x3A,0xAE};
	UNS8 ETHERNET_PAYLOAD_TAB[8] = {0x08,0x00,0x12,0x15,0x66,0x54,0xAB,0xCE};
	UNS8 ETHERNET_IP_PACKET_TAB[8] ={0x08,0x00,0xAC,0xBD,0xFE,0xCB,0xCD,0xC5};
	UNS8 ETHERNET_ARP_HEADER_TAB[8] ={0x08,0x00,0xBA,0xCD,0xEC,0xFA,0xA3,0x82};
	
	for(i=0; i<6; i++)
	{
		EthernetMAC.cDestMACAddress_a[i] = DESTINATION_MAC_ADDR_TAB[i];
		EthernetMAC.cSourceMACAddress_a[i] = SOURCE_MAC_ADDR_TAB[i];
	}
    for(i=0; i<8; i++)
	{	
		EthernetPayl.cPayload_a[i] = ETHERNET_PAYLOAD_TAB[i];            
		EthernetPayl.cIpPacket_a[i] = ETHERNET_IP_PACKET_TAB[i];              
		EthernetPayl.cArpHeader_a[i] = ETHERNET_ARP_HEADER_TAB[i];
	}

	EthernetMAC.nEtherType = ETHERNET_TYPE;
	
	SendData_ip.Header = EthernetMAC;
	SendData_ip.Payload = EthernetPayl;
	
					
	LAN9250_Write	((void *)&LAN9250Instance, &SendData_ip, lSendDataSize_i, &ReturnCode_op);
			
	LAN9250_Read	((void *)&LAN9250Instance, ReceiveData_op, lReceiveDataSize_i, &ReturnCode_op);
	
}

/***************************************************************/
/* Local function : ManageBITEActivation                      */
/***************************************************************/
void ManageBITEActivation(void)
{
    /* IF the BITE SHORT action has been activated by the APPLICATIVE S/W into the interface layer */
    if (I_BSP_Out.bite_status.F_BITE_short_action_enabled == TRUE)
    /* THEN */
    {
        /* Active the Software interrupt 1 */
		/*todo: check if these are really supposed to be FALSE */
        INTC.SSCIR[1].B.SET = (UNS32)FALSE;
    }
    else
    {
    }
    /* ENDIF */
    /* IF the BITE LONG action has been activated by the APPLICATIVE S/W into the interface layer */
    if (I_BSP_Out.bite_status.F_BITE_long_action_enabled == TRUE)
    /* THEN */
    {
        /* Active the Software interrupt 0 */
        INTC.SSCIR[0].B.SET = (UNS32)FALSE;
    }
    else
    {
    }
    /* ENDIF */
}

/***************************************************************/
/* Local function : ManageAPPActivation                       */
/***************************************************************/
void ManageAPPActivation(void)
{
    /* Call StartTaskTimeMeasurement function for the APPLICATIVE software task */
    StartTaskTimeMeasurement(APP_ACSC);

    /* Call function LaunchAPP1Maintask_PTR to launch the ACS software */
    LaunchAPP1Maintask_PTR();
    
    /* Call StopTaskTimeMeasurement function for the APPLICATIVE task */
    StopTaskTimeMeasurement(APP_ACSC);

}

/***************************************************************/
/* Local function : ManageAPPDCMotors                          */
/***************************************************************/
void ManageAPPDCMotors(void)
{
    /* Call DriveMotorOut function to command DC Motor x output with a period of 50ms */	
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_1_CMD , DC_MOTOR1 , I_BSP_In.dc_motor.HW_DC_MOTOR_1_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_1_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_2_CMD , DC_MOTOR2 , I_BSP_In.dc_motor.HW_DC_MOTOR_2_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_2_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_3_CMD , DC_MOTOR3 , I_BSP_In.dc_motor.HW_DC_MOTOR_3_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_3_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_4_CMD , DC_MOTOR4 , I_BSP_In.dc_motor.HW_DC_MOTOR_4_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_4_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_5_CMD , DC_MOTOR5 , I_BSP_In.dc_motor.HW_DC_MOTOR_5_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_5_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_6_CMD , DC_MOTOR6 , I_BSP_In.dc_motor.HW_DC_MOTOR_6_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_6_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_7_CMD , DC_MOTOR7 , I_BSP_In.dc_motor.HW_DC_MOTOR_7_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_7_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_8_CMD , DC_MOTOR8 , I_BSP_In.dc_motor.HW_DC_MOTOR_8_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_8_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_9_CMD , DC_MOTOR9 , I_BSP_In.dc_motor.HW_DC_MOTOR_9_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_9_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_10_CMD , DC_MOTOR10 , I_BSP_In.dc_motor.HW_DC_MOTOR_10_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_10_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_11_CMD , DC_MOTOR11 , I_BSP_In.dc_motor.HW_DC_MOTOR_11_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_11_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_12_CMD , DC_MOTOR12 , I_BSP_In.dc_motor.HW_DC_MOTOR_12_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_12_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_13_CMD , DC_MOTOR13 , I_BSP_In.dc_motor.HW_DC_MOTOR_13_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_13_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_14_CMD , DC_MOTOR14 , I_BSP_In.dc_motor.HW_DC_MOTOR_14_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_14_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_15_CMD , DC_MOTOR15 , I_BSP_In.dc_motor.HW_DC_MOTOR_15_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_15_ENABLE);
    DriveMotorOut(I_BSP_In.dc_motor.HW_DC_MOTOR_16_CMD , DC_MOTOR16 , I_BSP_In.dc_motor.HW_DC_MOTOR_16_PERIOD_MS,I_BSP_In.dc_motor.HW_DC_MOTOR_16_ENABLE);	

}

/***************************************************************/
/* Global function : MainTask                                  */
/***************************************************************/
void MainTask(void)
{
	LAN9250_PHY_Registers_t tutu;
    UNS32 test;
	UNS32 a_read_HMAC;
	UNS16 a_read_PHY1;
	UNS16 a_read_PHY2;
	UNS32 Result;
	test = 0;
	
    /* Call CalculateCPULoad function to calculate the CPU load values */
    CalculateCPULoad();

    /* Call StartTaskTimeMeasurement function for the MAIN task */
    StartTaskTimeMeasurement(MAIN_TASK);

    /* Call BlinkLed function, to blink the led each 500ms */
    BlinkLed();
	
	/* Resolver management : */
    /* - Clear the DSPI_A bus before RDC management */
    ClearDSPIBBus();    
    /* - Perform AD2S1210 configuration */
    InitializeAD2S1210();
    /* - Reset resolver faults on demand */
    ResetAD2S1210ResolverFaultRegister();
    /* - Read all angular position from resolvers */
    ReadAllAD2S1210Resolver();
	
	/* Call ManageLeakAcquisition to get the current acquisition and prepare the next ones */
    ManageLeakAcquisition();
	
	/* Call StartTaskTimeMeasurement function for the APP_CPCS task */
    StartTaskTimeMeasurement(APP_CPCS);
	
	/* Call StartAD1255Conversion function */
    StartAD1255Conversion();
    
    /*! Inputs management */
    /* Call HandleDiscreteInputAcquisition to acquire discrete input */
    HandleDiscreteInputAcquisition();
    
    /* Call GetSCI_A function to get the sci_A data received */
    GetSCI_A();
    
    /* Active interrupt for ARINC reception */
    ARINCActiveInterrupt();
    
    /* Call GetARINCData function to get the ARINC data received */
    GetARINCData();
	
	/* IF SPI_B is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_B_enable == (UNS32)TRUE)
    /* THEN */
    {
        /* Call WaitForEndOfAD1255Conversion function to wait for acquisition of the AD1255 or for the acquisition timeout */
        WaitForEndOfAD1255Conversion();
    }
    else
    {
    }
    /* END IF */
	
	/* Call GetCANData function to get the CAN_A, CAN_B and CAN_C data received */
    GetCANData();
	
	/* Call function LaunchAPP1MaintaskCPCS_PTR to launch the APPLICATIVE_1 CPCS software */
	LaunchAPP1MaintaskCPCS_PTR();
	
	/* Call SendSCI_A function to send message on SCI A bus */
    SendSCI_A();
	
	/* Call StopTaskTimeMeasurement function for the APP_CPCS task */
    StopTaskTimeMeasurement(APP_CPCS);

    /* Call MakeAnalogInputAcquisition function to acquire all the analog data */
    MakeAnalogInputAcquisition();
	
	/* Call function ManageAPPActivation to launch the APPLICATIVE software */
    ManageAPPActivation();
    	
    /*! Outputs management */
    /* Call ClearNumericalBusesReceptionBuffer function to clear reception buffer */
    ClearNumericalBusesReceptionBuffer();
		
	/* Call ManageAPPDCMotors function to drive DC Motor */
	ManageAPPDCMotors();
    
	/* Call DriveTorqMotor function to drive the Torque Motor */
    DriveTorqMotor();

    /* Call ComputeDiscreteOutput function to set discrete output port */
    ComputeDiscreteOutput();
	
	/* Call DriveAllSTPMotors function to drive Stepper Motor */
    DriveAllSTPMotors();
	
    /* Call ReportARINCMessages function to send the ARINC messages */
    ReportARINCMessages();
           
    /* Call ReportAllCANMessages function to send the CAN messages */
    ReportAllCANMessages();
        
    /* Call ManageBITEActivation function, to activate or not the BITE tasks */
    ManageBITEActivation();

    /* Register monitoring */
    /* MonitorRegisters(); */

    /* IF the APP S/W commands to rearm the watchdog */
    if (I_BSP_In.watchdog_rearm_flag == TRUE)
    /* THEN */
    {
        /* Call RearmWatchdog function to rearm the watchdog */
        RearmWatchdog();
    }
    else
    {
    }
	
	/************************************/
	/*SystemCSR Registers Read and Write*/
	/************************************/
	
	// /*BYTE_TEST Register Read*/
	// ReadRegistersLAN9250(LAN9250_BYTE_TEST_ADDR, &test);
	
	// WriteRegistersLAN9250(0x0074,0x00090000);
	// WriteRegistersLAN9250(LAN9250_HW_CFG_ADDR,0x00030000);
	
	/*Hardware Configuration Register Read*/
	// ReadRegistersLAN9250(LAN9250_HW_CFG_ADDR, &test);
	
	// /*Receive Configuration Register*/
	// test = ReadRegistersLAN9250(0x006C);
	
	// /*Chip ID and Revison Read*/
	// ReadRegistersLAN9250(LAN9250_ID_REV_ADDR, &test);
	
	/*TX FIFO  Information Register Read*/
	//test = ReadRegistersLAN9250(0x0080);
    
	// /* write Host MAC CSR Interface Command Register (MAC_CSR_CMD)*/
    // WriteRegistersLAN9250(0x00A4, 0x82BBADEC);
    // /* Host MAC CSR Interface Data Register (MAC_CSR_DATA)*/
    // WriteRegistersLAN9250(0x00A8, 0x82BBADEC);
	// ReadRegistersLAN9250_new(0x00A8, &test);
	// if(test != 0x82BBADEC)
	// {
		// test=0;
		
	// }
	// else
	// {
	   // WriteRegistersLAN9250(0x00A8, 0);
	// }
	
	//ReadRegistersLAN9250_new(0x00A4, &test);

	/******************************************************************************/
	/*Host MAC and PHY Registers Read and Write: to configure HMAC and PHY Modules*/
	/******************************************************************************/
	/*Write to HMAC Register 0x82BBADEC pour HMAC CR*/
	// bResult = LAN9250_HMacWriteReg(&LAN9250Instance, LAN9250_HMAC_ADDRH_E, 0x2468);
	
	/*Read the HMAC Register*/
	// bResult = LAN9250_HMacReadReg (&LAN9250Instance, LAN9250_HMAC_ADDRH_E, &a_read_HMAC);
	
	/*Write to PHY Register*/
	// bResult = LAN9250_PhyWriteReg (&LAN9250Instance, LAN9250_PHY_ID_MSB_E, 0x2468);
	
	/*Read the PHY Register*/
    // bResult = LAN9250_PhyReadReg (&LAN9250Instance, LAN9250_PHY_ID_MSB_E, &a_read_PHY);
	
	
	
	// /*Write to PHY Register*/
	tutu.PHY_BASIC_CONTROL.Bit.PHY_SRST				 = 0 ;
	tutu.PHY_BASIC_CONTROL.Bit.PHY_LOOPBACK   		 = 1 ;
	tutu.PHY_BASIC_CONTROL.Bit.PHY_SPEED_SEL_LSB 	 = 1 ;
	tutu.PHY_BASIC_CONTROL.Bit.PHY_AN     		     = 1 ;
	tutu.PHY_BASIC_CONTROL.Bit.PHY_PWR_DWN     		 = 1 ; 
	tutu.PHY_BASIC_CONTROL.Bit.PHY_RST_AN    	     = 0 ;
	tutu.PHY_BASIC_CONTROL.Bit.PHY_DUPLEX   	 	 = 0 ;
	tutu.PHY_BASIC_CONTROL.Bit.PHY_COL_TEST    		 = 1 ;
	
	bResult = LAN9250_PhyWriteReg (&LAN9250Instance, LAN9250_PHY_BASIC_CONTROL_E, (tutu.PHY_BASIC_CONTROL.nReg));
	
	// /*Read the PHY Register*/
    bResult = LAN9250_PhyReadReg (&LAN9250Instance, LAN9250_PHY_BASIC_CONTROL_E, &(tutu.PHY_BASIC_CONTROL.nReg));
	
	// /*Read the PHY Register*/
    bResult = LAN9250_PhyReadReg (&LAN9250Instance, LAN9250_PHY_BASIC_STATUS_E, &(tutu.PHY_BASIC_STATUS.nReg));
	
	/*Send and receive Ethernet trames*/

	DataExchangeLAN9250();
	
	/* Increase PIT number */
    MC_PIT_NUMBER++;

    /* If a SEU has been detected reset the controller */
    if(I_BSP_In.F_SEU_detected == TRUE)
    {
        user_reset_source = SEU_REGISTERS;
        DefaultHandlerUser();
    }
    else
    {
    }

    /* Call StopTaskTimeMeasurement function for MAIN task */
    StopTaskTimeMeasurement(MAIN_TASK);
}


/***************************************************************/
/* Global function : InitializeMain_Task                       */
/***************************************************************/
void InitializeMain_Task(void)
{
    /* Initialize data for main task module */
    MC_PIT_NUMBER = (UNS32)0;
    last_led_blink_TIME = (UNS32)0;
}

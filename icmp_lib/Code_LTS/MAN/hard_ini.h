#ifndef __HARD_INI_H__
#define __HARD_INI_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                        GLOBAL TYPES                         */
/*                                                             */
/***************************************************************/
typedef enum
{
    SEU_FLASH         = 1,
    SEU_INTERNAL_SRAM = 2,
    SEU_REGISTERS     = 3,
    DEFAULT           = 4
}
T_UserResetSource;

/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* eSCI register initialization */
/* ESCIA_CR1: */
/* SBR = 0x342 ; 1 start bit, 9 data bits, 1 stop bit; odd parity; Transmitter and Receiver enable  */
#define ESCIA_CR1_INIT (UNS32)0x003D130C /* 0x003D130C*/
#define ESCIA_CR2_INIT (UNS16)0x2000

/* Initialize interrupt in software vector mode and the vector table entry size to 4 bytes*/
#define INTC_MCR_INIT (UNS32)0

/* EBI register initialization */
#define EBI_MCR_INIT  (UNS32)0x00008800
#define EBI_BR0_INIT  (UNS32)0x20000823
#define EBI_OR0_INIT  (UNS32)0xFFE00020
#define EBI_BR1_INIT  (UNS32)0x20400802
#define EBI_BR2_INIT  (UNS32)0x20800003
#define EBI_OR2_INIT  (UNS32)0xFFC00090
#define EBI_BR3_INIT  (UNS32)0x20C00802
/* errata e1844 */
#define EBI_BMCR_INIT (UNS32)0x0000FF00

/* SIU register initialization */

/* ENGDIV = 0x38 => EngineeringClk = 1MHz ; EBDF = 0b01   => CLKOUT = 56MHz; EBTS = 1 */
#define SIU_ECCR_INIT  (UNS32)0x00003809

#define SIU_SRCR_INIT           (UNS32)0x00000000
/* Enable IRQ6 and IRQ7 */
#define SIU_DIRER_INIT          (UNS32)0x000000C0 
#define SIU_DIRSR_INIT          (UNS32)0x00000000
#define SIU_ORER_INIT           (UNS32)0x00000000
#define SIU_IREER_INIT          (UNS32)0x00000000
/* Falling edge of : IRQ6 */
#define SIU_IFEER_INIT          (UNS32)0x000000C0
/* DFL = 1 */
#define SIU_IDFR_INIT           (UNS32)0x00000001 
#define SIU_EIISR_INIT          (UNS32)0x00000000

#define SIU_PCR0_INIT           (UNS16)0x0643
#define SIU_PCR1_INIT           (UNS16)0x00C3
#define SIU_PCR2_INIT           (UNS16)0x0683
#define SIU_PCR3_INIT           (UNS16)0x00C3
/* External Address Bus */
#define SIU_PCR4_5_INIT         (UNS16)0x0600
#define SIU_PCR6_7_INIT         (UNS16)0x0640
#define SIU_PCR8_INIT           (UNS16)0x0680
#define SIU_PCR9_10_INIT        (UNS16)0x0640
#define SIU_PCR11_13_INIT       (UNS16)0x0680
#define SIU_PCR14_26_INIT       (UNS16)0x0640
#define SIU_PCR27_INIT          (UNS16)0x0600
/* External Data Bus */
#define SIU_PCR28_59_INIT       (UNS16)0x0740
/* Transfer Size signals for Logic Analyzer POD */
#define SIU_PCR60_61_INIT       (UNS16)0x0600
/* External Read/Write */
#define SIU_PCR62_INIT          (UNS16)0x0640
/* External Burst Data In Progress */
#define SIU_PCR63_INIT          (UNS16)0x0603
/* External Byte Enable */
#define SIU_PCR64_INIT          (UNS16)0x0643
#define SIU_PCR65_INIT          (UNS16)0x0643
#define SIU_PCR66_INIT          (UNS16)0x0603
#define SIU_PCR67_INIT          (UNS16)0x0683
/* External Output Enable */
#define SIU_PCR68_INIT          (UNS16)0x0683
/* External Transfer Start Logic Analyzer POD */
#define SIU_PCR69_INIT          (UNS16)0x0600
/* External Transfer Acknowledge for Logic Analyzer */
#define SIU_PCR70_INIT          (UNS16)0x0603
/* N/A */
#define SIU_PCR71_INIT          (UNS16)0x00C3
#define SIU_PCR72_INIT          (UNS16)0x0003
#define SIU_PCR73_INIT          (UNS16)0x0003
#define SIU_PCR74_INIT          (UNS16)0x0003

/* NEXUS Message Data Out */
#define SIU_PCR75_82_INIT          (UNS16)0x00C2

/* CAN_A Transmitter */
#define SIU_PCR83_INIT      (UNS16)0x060F
/* CAN_A Transmitter in GPIO */
#define SIU_PCR_CANA_TX_GPIO_INIT (UNS16)0x0203
/* CAN_A Receiver */
#define SIU_PCR84_INIT      (UNS16)0x0403
/* CAN_B Transmitter */
#define SIU_PCR85_INIT      (UNS16)0x0607
/* CAN_B Transmitter in GPIO */
#define SIU_PCR_CANB_TX_GPIO_INIT (UNS16)0x0203
/* CAN_B Receiver */
#define SIU_PCR86_INIT      (UNS16)0x0403
/* CAN_C Transmitter */
#define SIU_PCR87_INIT      (UNS16)0x0607
/* CAN_C Transmitter in GPIO */
#define SIU_PCR_CANC_TX_GPIO_INIT (UNS16)0x0203
/* CAN_C Receiver */
#define SIU_PCR88_INIT      (UNS16)0x0403

/* SCI_A Transmitter */
#define SIU_PCR89_INIT      (UNS16)0x0607
/* SCI_A Receiver */
#define SIU_PCR90_INIT      (UNS16)0x0400
/* N/A */
#define SIU_PCR91_INIT      (UNS16)0x0003
#define SIU_PCR92_INIT      (UNS16)0x0003

/* SPIA - SPI-Clock for external ADC/RDC */
#define SIU_PCR93_INIT      (UNS16)0x0607
/* SPIA - SPI-Data-In from external ADC/RDC */
#define SIU_PCR94_INIT      (UNS16)0x0500
/* SPIA - SPI-Data-Out to external ADC/RDC */
#define SIU_PCR95_INIT      (UNS16)0x0606
/* SPIA - SPI-Chip-Select for external ADC */
#define SIU_PCR96_INIT      (UNS16)0x0607
/* SPIA - SPI-Chip-Select for external RDC */
#define SIU_PCR97_INIT      (UNS16)0x0607
/* SPIA - SPI-Clock for leak detection */
#define SIU_PCR98_INIT      (UNS16)0x0A07

#define SIU_PCR99_INIT      (UNS16)0x0900

#define SIU_PCR100_INIT     (UNS16)0x0606
#define SIU_PCR101_INIT     (UNS16)0x0003

#define SIU_PCR102_INIT     (UNS16)0x0606
#define SIU_PCR103_INIT     (UNS16)0x0503
#define SIU_PCR104_INIT     (UNS16)0x0607
#define SIU_PCR105_INIT     (UNS16)0x0607

#define SIU_PCR106_INIT     (UNS16)0x0003

#define SIU_PCR107_INIT     (UNS16)0x0A07
#define SIU_PCR108_INIT     (UNS16)0x0900
#define SIU_PCR109_INIT     (UNS16)0x0A07
#define SIU_PCR110_INIT     (UNS16)0x0A07

/* WD Counter Feedback */
#define SIU_PCR111_INIT     (UNS16)0x0100
#define SIU_PCR112_INIT     (UNS16)0x0100

#define SIU_PCR113_INIT     (UNS16)0x0803

/* ETPU_A[0..23] set to eTPU for Stepper Motor purpose */
#define SIU_PCR114_123_INIT (UNS16)0x0502
#define SIU_PCR124_127_INIT (UNS16)0x0604
#define SIU_PCR128_137_INIT (UNS16)0x0606

#define SIU_PCR138_141_INIT (UNS16)0x060E
#define SIU_PCR142_145_INIT (UNS16)0x0606
/* N_ETH_IRQ  (Ethernet Interupt - IRQ */
#define SIU_PCR146_INIT     (UNS16)0x0803
#define SIU_PCR147_INIT     (UNS16)0x0002

/* ETPU_B[3..24] set to eTPU for leak aquisition purpose */
#define SIU_PCR148_155_INIT (UNS16)0x0606
#define SIU_PCR156_161_INIT (UNS16)0x060E
#define SIU_PCR162_INIT     (UNS16)0x0002
#define SIU_PCR163_176_INIT (UNS16)0x0606

/* N_PRES_SYNC - GPIO */
#define SIU_PCR177_INIT     (UNS16)0x0204
/* AD1255 - N_PRES_SYNC set to 1 */
#define SIU_GPDO177_INIT    (UNS8)0x01    

#define SIU_PCR178_INIT     (UNS16)0x0206

/* SHOP and start Configuration */
/* DI_GND_1L2_16 Shop Pin 1 */
#define SIU_PCR179_INIT         (UNS16)0x0102
#define SIU_PCR180_INIT         (UNS16)0x0102
#define SIU_PCR181_INIT         (UNS16)0x0100
#define SIU_PCR182_INIT         (UNS16)0x0100
/* GPIO_IASC_RESET_LATCHED_PIN - GPIO */
#define SIU_PCR183_187_INIT      (UNS16)0x060E
/* AMUX_Ax */
#define SIU_PCR188_190_INIT      (UNS16)0x0206
#define SIU_PCR191_192_INIT      (UNS16)0x0002
/* POW_ITD_200MS - GPIO */
#define SIU_PCR193_INIT         (UNS16)0x0100
/* N_SID (Power Warning - GPIO */
#define SIU_PCR194_INIT         (UNS16)0x0100
/* POW_ITD_INIT */
#define SIU_PCR195_INIT         (UNS16)0x020C

/* TORQ MOTOR CMD - EMIOS[17] - Does not follow HSI configuration design for eTPU */
#define SIU_PCR196_198_INIT     (UNS16)0x0202
/* AC Motor Direction Command - GPIO */
#define SIU_PCR199_INIT         (UNS16)0x020E
#define SIU_PCR200_INIT         (UNS16)0x020C

/* CLR_IASC_RESET_LATCH - GPIO */
#define SIU_PCR201_INIT         (UNS16)0x020C
/* ALIVE LED - GPIO */
#define SIU_PCR202_INIT         (UNS16)0x020C
/* µC ALIVE LED */
#define SIU_GPDO202_INIT        (UNS8)0x01
/* SID_TEST - GPIO */
#define SIU_PCR203_INIT         (UNS16)0x0204
/* µC SID_TEST */
#define SIU_GPDO203_INIT        (UNS8)0x01
/* DI_TEST - GPIO */
#define SIU_PCR204_INIT         (UNS16)0x0204
/* N_CS_WD - GPIO */
#define SIU_PCR205_INIT         (UNS16)0x0204
/* N_TEST_LANE_FAULT - GPIO */
#define SIU_PCR206_INIT         (UNS16)0x0202
#define SIU_PCR207_INIT         (UNS16)0x0000

/* Reset / Configuration signals */
#define SIU_PCR208_INIT         (UNS16)0x0C13
#define SIU_PCR209_INIT         (UNS16)0x0C12
#define SIU_PCR210_INIT         (UNS16)0x0412
#define SIU_PCR211_INIT         (UNS16)0x0C12
#define SIU_PCR212_INIT         (UNS16)0x0C12
#define SIU_PCR213_INIT         (UNS16)0x0412

/* ENGCLK pin */
#define SIU_PCR214_INIT         (UNS16)0x0000

/* eQADC */
#define SIU_PCR215_INIT     (UNS16)0x0C00
#define SIU_PCR216_INIT     (UNS16)0x0C00
#define SIU_PCR217_INIT     (UNS16)0x0C00
#define SIU_PCR218_INIT     (UNS16)0x0400

/* NEXUS Signals */
#define SIU_PCR219_227_INIT         (UNS16)0x00C0
/* JTAG */
#define SIU_PCR228_INIT         (UNS16)0x00C0

/* CLKOUT pin */
#define SIU_PCR229_INIT         (UNS16)0x0200

/* N_RSTOUT pin */
#define SIU_PCR230_INIT         (UNS16)0x0004

/* FLASH register initialization */
/* errata e2773, e2046, e989 */
/* APC = 0b010; RWSC = 0b011; WWSC = 0b01; No prefectching */
#define FLASH_BIUCR_INIT (UNS32)0x00004B00

/* DSPI register initialization */
/* MSTR = 1; ROOE = 0; PCSIS0 = 1; CLR_TXF = 1; CLR_RXF = 1; HALT = 1 */
#define DSPIA_MCR_INIT   (UNS32)0x80030C01
/*DBR=0; FMSZ=1111; CPOL=1; CPHA=1; LSBFE=0; PCSSCK=01; PASC=01; PDT=01; PBR=11
CSSCK=0110; ASC=0001; DT=0001; BR=0001*/
#define DSPIA_CTAR0_INIT (UNS32)0x7E576111
/*DBR=0; FMSZ=1111; CPOL=1; CPHA=0; LSBFE=0; PCSSCK=11; PASC=11; PDT=00; PBR=11
CSSCK=0001; ASC=0001; DT=0000; BR=0010*/
#define DSPIA_CTAR1_INIT (UNS32)0x7CF31102

/*******************************************************************************/
/*       DSPI registrr for serial interface of the cabin pressure sensor       */
/*******************************************************************************/
/* MSTR = 1; ROOE = 0; PCSIS0 = 1; CLR_TXF = 1; CLR_RXF = 1; HALT = 1 */
#define DSPIB_MCR_INIT   (UNS32)0x80010C01
/*DBR=0; FMSZ=1111; CPOL=0; CPHA=0; LSBFE=0; PCSSCK=00; PASC=00; PDT=00; PBR=11
CSSCK=0000; ASC=0000; DT=0010; BR=0010*/
#define DSPIB_CTAR0_INIT (UNS32)0x7A771614

/*******************************************************************************/
/*      DSPI register for serial interface of the Ethernet Controller           */
/*******************************************************************************/
/* MSTR = 1; ROOE = 0; PCSIS0 = 1; CLR_TXF = 1; CLR_RXF = 1; HALT = 1 */
#define DSPIC_MCR_INIT   (UNS32)0x80010C01
/*DBR=0; FMSZ=0111; CPOL=1; CPHA=1; LSBFE=0; PCSSCK=00; PASC=00; PDT=00; PBR=11
CSSCK=0101; ASC=0000; DT=0010; BR=0100*/
#define DSPIC_CTAR0_INIT (UNS32)0x38035024

/*******************************************************************************/
/*       DSPI register for serial interface of the Leak Detection ADCs          */
/*******************************************************************************/
/* MSTR = 1; ROOE = 0; PCSIS0 = 1; CLR_TXF = 1; CLR_RXF = 1; HALT = 1 */
#define DSPID_MCR_INIT   (UNS32)0x80010C01
/*DBR=0; FMSZ=1111; CPOL=1; CPHA=1; LSBFE=0; PCSSCK=10; PASC=00; PDT=10; PBR=00
CSSCK=0101; ASC=0010; DT=0101; BR=0100*/
#define DSPID_CTAR0_INIT (UNS32)0x7E885254

/* EDMA register initialization */
#define EDMA_ERQRH_INIT (UNS32)0x00000000
#define EDMA_ERQRL_INIT (UNS32)0x00000000
#define EDMA_EEIRH_INIT (UNS32)0x00000000
#define EDMA_EEIRL_INIT (UNS32)0x00000000

/* XBAR register initialization */
#define XBAR_MPR_INIT   (UNS32)0x00000210
#define XBAR_SGPCR_INIT (UNS32)0x00000000

/* PBRIGE register initialization */
/* Allow user access to peripheral */
#define PBRIDGE_A_OPACR0_INIT  (UNS32)0x00000000
#define PBRIDGE_A_OPACR1_INIT  (UNS32)0x00000000
#define PBRIDGE_A_OPACR2_INIT  (UNS32)0x00000000
#define PBRIDGE_B_OPACR0_INIT  (UNS32)0x00000000
#define PBRIDGE_B_OPACR1_INIT  (UNS32)0x00000000
#define PBRIDGE_B_OPACR2_INIT  (UNS32)0x00000000
#define PBRIDGE_B_OPACR3_INIT  (UNS32)0x00000000
#define PBRIDGE_A_PACR0_INIT   (UNS32)0x00000000
#define PBRIDGE_B_PACR0_INIT   (UNS32)0x00000000
#define PBRIDGE_B_PACR2_INIT   (UNS32)0x00000000

/* ECSM register initialization */
/* Enable Reporting of non-correctable FLASH/RAM errors */
#define ECSM_ECR_INIT           (UNS8)0x3   

/*! EMIOS register initialization */
/*! FRZ = 1; GTBE = 1; GPREN = 1; GPRE = 111 */
/* System Frequency = 112 MHZ */
/* Unified channel input prescaler input clock = System Frequency / (GPRE + 1) */
/* Unified channel input prescaler input clock = 1 MHz (period = 1 us)*/
#define EMIOS_MCR_INIT    (UNS32)0x34006F00

/* eMIOS16 generate the time base for the Counter Bus A */
/* UCPRE = 3 (clock divider value for the unified channel internal prescaler = 4) */
/* UCPREN = 1; FCK = 1; BSL = 3 (Internal counter); MODE = 0b0010000 (MC Internal source) */
/* 1MHZ ===> 1us ====> 1MHZ / 4 = 250KHZ ===> 4us */
/* 5MHZ ===> 0.2ms ===> 0.2 / 0.004 = 50 ===> 0x00000032 */
#define CLK_5KHZ (UNS32)0x00000032
#define EMIOS_CCR23_INIT  (UNS32)0x060C0610
#define EMIOS_CBDR23_INIT (UNS32)CLK_5KHZ
#define EMIOS_CADR23_INIT (UNS32)CLK_5KHZ

/* EMIOS channel 4-8 */
/*! UCPRE = 0; UCPREN = 1; FCK = 1; BSL = 00 (Counter Bus A); EDPOL = 0; MODE = 0b0100001 (OPWM) */
#define EMIOS_CCR4_INIT          (UNS32)0x02040021
#define EMIOS_CCR5_INIT          (UNS32)0x02040021
#define EMIOS_CCR6_INIT          (UNS32)0x02040021
#define EMIOS_CCR7_INIT          (UNS32)0x02040021
#define EMIOS_CCR8_INIT  		 (UNS32)0x02040021

/* Period = 200 Hz */
#define EMIOS_CADR4_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CADR5_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CADR6_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CADR7_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CBDR8_INIT 		 (UNS32)CLK_5KHZ

/* Force current duty cycle to 0% */
#define EMIOS_CBDR4_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CBDR5_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CBDR6_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CBDR7_INIT         (UNS32)CLK_5KHZ
#define EMIOS_CADR8_INIT 	     (UNS32)CLK_5KHZ

/* Ethernet register initialization */
#define ETH_HW_CFG               0x00100800
#define ETH_IRQ_CFG              0x00000001 
#define HMAC_CR_toto                  0x0010000C
#define PHY_BASIC_CTR            0x0100  

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
extern T_UserResetSource  user_reset_source;
extern BOOLEAN            F_check_for_internal_SRAM_ECC_error;

/* Declaration of global data that are set by BOOT software or previously set before a short power cut */
extern UNS32 MC_LONG_POWER_CUT;
extern BOOLEAN MC_WATCHDOG_RESET;
extern BOOLEAN MC_WATCHDOG_TESTED;

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern void InitializeHardware(void);
#endif

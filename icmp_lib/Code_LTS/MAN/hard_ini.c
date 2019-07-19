/***************************************************************/
/* FUNCTION : Initialize all parts of PPC5554 and peripherals  */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"
#include "hard_def.h"
#include "interface.h"

#include "dc_motor.h"
#include "adc128S052.h"
#include "ad1255.h"
#include "configuration.h"
#include "can_lb.h"
#include "cpu_ini.h"
#include "cpu_lb.h"
#include "data_ini.h"
#include "disc_acq.h"
#include "disc_out.h"
#include "eqadc_lb.h"
#include "etpu_lb.h"
#include "arinc_int.h"
#include "intc_isr_vectors.h"
#include "mon_memory.h"
#include "mon_register.h"
#include "sci_lb.h"
#include "soft_ini.h"
#include "stp_motor.h"
#include "wdg_lb.h"
#include "wdg_ts.h"
#include "hard_ini.h"
#include "LAN9250.h"


#include "leak_int.h"
#include "torq_motor.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
T_UserResetSource  user_reset_source;
BOOLEAN            F_check_for_internal_SRAM_ECC_error;

/***************************************************************/
/*                                                             */
/*                       GLOBAL CONSTANTS                      */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                        LOCAL CONSTANTS                      */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL TYPES                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                    EXTERNAL VARIABLES                       */
/***************************************************************/
extern unsigned int MRAM_BSP_data_adress;
extern unsigned int MRAM_BSP_data_size;
extern unsigned int MRAM_APP_data_adress;
extern unsigned int MRAM_APP_data_size;
extern unsigned int MRAM_SHARED_APP_data_adress;
extern unsigned int MRAM_SHARED_APP_data_size;
extern unsigned int MRAM_HW_adress;        
extern unsigned int MRAM_HW_size;         
extern unsigned int MRAM_EEPROM_APP_adress;
extern unsigned int MRAM_EEPROM_APP_size;  
extern unsigned int MRAM_BITE_adress;      
extern unsigned int MRAM_BITE_size;        
extern unsigned int MRAM_stack_BITE_adress;
extern unsigned int MRAM_stack_BITE_size;  
extern unsigned int MRAM_Spare_adress;     
extern unsigned int MRAM_Spare_size;       
extern unsigned int MRAM_TOTAL_adress;     
extern unsigned int MRAM_TOTAL_size;       

/***************************************************************/
/* Local function : InitializeSIU                              */
/***************************************************************/
void InitializeSIU(void)
{
    UNS8 i;
    /* Initialize SIU registers */

    /* Initialize the SRCR register */
    /* No '1' shall be written to SER in the System Reset Control Register */
    SIU.SRCR.R  = SIU_SRCR_INIT;

    /* Initialize PCR registers */
    SIU.PCR[0].R = SIU_PCR0_INIT;
    SIU.PCR[1].R = SIU_PCR1_INIT;
    SIU.PCR[2].R = SIU_PCR2_INIT;
    SIU.PCR[3].R = SIU_PCR3_INIT;
    SIU.PCR[4].R = SIU_PCR4_5_INIT;
    SIU.PCR[5].R = SIU_PCR4_5_INIT;
    SIU.PCR[6].R = SIU_PCR6_7_INIT;
    SIU.PCR[7].R = SIU_PCR6_7_INIT;
    SIU.PCR[8].R = SIU_PCR8_INIT;
    SIU.PCR[9].R = SIU_PCR9_10_INIT;
    SIU.PCR[10].R = SIU_PCR9_10_INIT;
    for(i = 11; i <= 13; i++)
    {
        SIU.PCR[i].R = SIU_PCR11_13_INIT;
    }
    for(i = 14; i <= 26; i++)
    {
        SIU.PCR[i].R = SIU_PCR14_26_INIT;
    }
    SIU.PCR[27].R = SIU_PCR27_INIT;
    for(i = 28; i <= 59; i++)
    {
        SIU.PCR[i].R = SIU_PCR28_59_INIT;
    }
    SIU.PCR[60].R = SIU_PCR60_61_INIT;
    SIU.PCR[61].R = SIU_PCR60_61_INIT;
    SIU.PCR[62].R = SIU_PCR62_INIT;
    SIU.PCR[63].R = SIU_PCR63_INIT;
    SIU.PCR[64].R = SIU_PCR64_INIT;
    SIU.PCR[65].R = SIU_PCR65_INIT;
    SIU.PCR[66].R = SIU_PCR66_INIT;
    SIU.PCR[67].R = SIU_PCR67_INIT;
    SIU.PCR[68].R = SIU_PCR68_INIT;
    SIU.PCR[69].R = SIU_PCR69_INIT;
    SIU.PCR[70].R = SIU_PCR70_INIT;
    SIU.PCR[71].R = SIU_PCR71_INIT;
    SIU.PCR[72].R = SIU_PCR72_INIT;
    SIU.PCR[73].R = SIU_PCR73_INIT;
    SIU.PCR[74].R = SIU_PCR74_INIT;
    SIU.PCR[75].R = SIU_PCR75_82_INIT;
    SIU.PCR[76].R = SIU_PCR75_82_INIT;
    SIU.PCR[77].R = SIU_PCR75_82_INIT;
    SIU.PCR[78].R = SIU_PCR75_82_INIT;
    SIU.PCR[79].R = SIU_PCR75_82_INIT;
    SIU.PCR[80].R = SIU_PCR75_82_INIT;
    SIU.PCR[81].R = SIU_PCR75_82_INIT;
    SIU.PCR[82].R = SIU_PCR75_82_INIT;
    SIU.PCR[83].R = SIU_PCR83_INIT;
    SIU.PCR[84].R = SIU_PCR84_INIT;
    SIU.PCR[85].R = SIU_PCR85_INIT;
    SIU.PCR[86].R = SIU_PCR86_INIT;
    SIU.PCR[87].R = SIU_PCR87_INIT;
    SIU.PCR[88].R = SIU_PCR88_INIT;
    SIU.PCR[89].R = SIU_PCR89_INIT;
    SIU.PCR[90].R = SIU_PCR90_INIT;
    SIU.PCR[91].R = SIU_PCR91_INIT;
    SIU.PCR[92].R = SIU_PCR92_INIT;
    SIU.PCR[93].R = SIU_PCR93_INIT;
    SIU.PCR[94].R = SIU_PCR94_INIT;
    SIU.PCR[95].R = SIU_PCR95_INIT;
    SIU.PCR[96].R = SIU_PCR96_INIT;
    SIU.PCR[97].R = SIU_PCR97_INIT;
    SIU.PCR[98].R = SIU_PCR98_INIT;
    SIU.PCR[99].R = SIU_PCR99_INIT;
    SIU.PCR[100].R = SIU_PCR100_INIT;
    SIU.PCR[101].R = SIU_PCR101_INIT;
    SIU.PCR[102].R = SIU_PCR102_INIT;
    SIU.PCR[103].R = SIU_PCR103_INIT;
    SIU.PCR[104].R = SIU_PCR104_INIT;
    SIU.PCR[105].R = SIU_PCR105_INIT;
    SIU.PCR[106].R = SIU_PCR106_INIT;
    SIU.PCR[107].R = SIU_PCR107_INIT;
    SIU.PCR[108].R = SIU_PCR108_INIT;
    SIU.PCR[109].R = SIU_PCR109_INIT;
    SIU.PCR[110].R = SIU_PCR110_INIT;
    SIU.PCR[111].R = SIU_PCR111_INIT;
    SIU.PCR[112].R = SIU_PCR112_INIT;
    SIU.PCR[113].R = SIU_PCR113_INIT;
    for(i = 114; i <= 123; i++)
    {
        SIU.PCR[i].R = SIU_PCR114_123_INIT;
    }
    for(i = 124; i <= 127; i++)
    {
        SIU.PCR[i].R = SIU_PCR124_127_INIT;
    }
    for(i = 128; i <= 137; i++)
    {
        SIU.PCR[i].R = SIU_PCR128_137_INIT;
    }
    SIU.PCR[138].R = SIU_PCR138_141_INIT;
	SIU.PCR[139].R = SIU_PCR138_141_INIT;
	SIU.PCR[140].R = SIU_PCR138_141_INIT;
	SIU.PCR[141].R = SIU_PCR138_141_INIT;
	
	SIU.PCR[142].R = SIU_PCR142_145_INIT;
	SIU.PCR[143].R = SIU_PCR142_145_INIT;
	SIU.PCR[144].R = SIU_PCR142_145_INIT;
	SIU.PCR[145].R = SIU_PCR142_145_INIT;
	
	SIU.PCR[146].R = SIU_PCR146_INIT;
	SIU.PCR[147].R = SIU_PCR147_INIT;
	
    for(i = 148; i <= 155; i++)
    {
        SIU.PCR[i].R = SIU_PCR148_155_INIT;
    }
    for(i = 156; i <= 161; i++)
    {
        SIU.PCR[i].R = SIU_PCR156_161_INIT;
    }
	SIU.PCR[162].R = SIU_PCR162_INIT;
    for(i = 163; i <= 176; i++)
    {
        SIU.PCR[i].R = SIU_PCR163_176_INIT;
    }
    
    SIU.PCR[177].R = SIU_PCR177_INIT;
	SIU.GPDO[177].R = SIU_GPDO177_INIT;
    SIU.PCR[178].R = SIU_PCR178_INIT;
    SIU.PCR[179].R = SIU_PCR179_INIT;
    SIU.PCR[180].R = SIU_PCR180_INIT;
    SIU.PCR[181].R = SIU_PCR181_INIT;
    SIU.PCR[182].R = SIU_PCR182_INIT;
	
	for(i = 183; i <= 187; i++)
    {
        SIU.PCR[i].R = SIU_PCR183_187_INIT;
    }
	
    SIU.PCR[188].R = SIU_PCR188_190_INIT;
    SIU.PCR[189].R = SIU_PCR188_190_INIT;
    SIU.PCR[190].R = SIU_PCR188_190_INIT;
    SIU.PCR[191].R = SIU_PCR191_192_INIT;
    SIU.PCR[192].R = SIU_PCR191_192_INIT;
    SIU.PCR[193].R = SIU_PCR193_INIT;
    SIU.PCR[194].R = SIU_PCR194_INIT;
    SIU.PCR[195].R = SIU_PCR195_INIT;
    SIU.PCR[196].R = SIU_PCR196_198_INIT;
    SIU.PCR[197].R = SIU_PCR196_198_INIT;
    SIU.PCR[198].R = SIU_PCR196_198_INIT;
    SIU.PCR[199].R = SIU_PCR199_INIT;
    SIU.PCR[200].R = SIU_PCR200_INIT;
    SIU.PCR[201].R = SIU_PCR201_INIT;
    SIU.PCR[202].R = SIU_PCR202_INIT;
    /* Configure the ALIVE LED output */
    SIU.GPDO[202].R = SIU_GPDO202_INIT;
    SIU.PCR[203].R = SIU_PCR203_INIT;
	/* Set GPIO203 value to 1 before to configure it as an output */
    SIU.GPDO[203].R = SIU_GPDO203_INIT;
    SIU.PCR[204].R = SIU_PCR204_INIT;
    SIU.PCR[205].R = SIU_PCR205_INIT;
    SIU.PCR[206].R = SIU_PCR206_INIT;
    SIU.PCR[207].R = SIU_PCR207_INIT;
    SIU.PCR[208].R = SIU_PCR208_INIT;
    SIU.PCR[209].R = SIU_PCR209_INIT;
    SIU.PCR[210].R = SIU_PCR210_INIT;
    SIU.PCR[211].R = SIU_PCR211_INIT;
    SIU.PCR[212].R = SIU_PCR212_INIT;
    SIU.PCR[213].R = SIU_PCR213_INIT;
    SIU.PCR[214].R = SIU_PCR214_INIT;
    SIU.PCR[215].R = SIU_PCR215_INIT;
    SIU.PCR[216].R = SIU_PCR216_INIT;
    SIU.PCR[217].R = SIU_PCR217_INIT;
    SIU.PCR[218].R = SIU_PCR218_INIT;
	
	for(i = 219; i <= 227; i++)
    {
        SIU.PCR[i].R = SIU_PCR219_227_INIT;
    }
	
    SIU.PCR[228].R = SIU_PCR228_INIT;
    SIU.PCR[229].R = SIU_PCR229_INIT;
    SIU.PCR[230].R = SIU_PCR230_INIT;

    /* Initialize DIRER, DIRSR, ORER, IREER, IFEER, IDFR, EIISR and ECCR registers */
    SIU.DIRER.R = SIU_DIRER_INIT;
    SIU.DIRSR.R = SIU_DIRSR_INIT;
    SIU.ORER.R  = SIU_ORER_INIT;
    SIU.IREER.R = SIU_IREER_INIT;
    SIU.IFEER.R = SIU_IFEER_INIT;
    SIU.IDFR.R  = SIU_IDFR_INIT;
    SIU.EIISR.R = SIU_EIISR_INIT;
    SIU.ECCR.R  = SIU_ECCR_INIT;
}

/***************************************************************/
/* Local function : InitializeEBI                              */
/***************************************************************/
void InitializeEBI(void)
{
    /* Initialize EBI registers */
    EBI.MCR.R = EBI_MCR_INIT;
    EBI.CS[0].BR.R = EBI_BR0_INIT;
    EBI.CS[0].OR.R = EBI_OR0_INIT;
    EBI.CS[1].BR.R = EBI_BR1_INIT;
    EBI.CS[2].BR.R = EBI_BR2_INIT;
    EBI.CS[2].OR.R = EBI_OR2_INIT;
    EBI.CS[3].BR.R = EBI_BR3_INIT;
    EBI.BMCR.R     = EBI_BMCR_INIT;
}

/***************************************************************/
/* Local function : InitializeDSPI                             */
/***************************************************************/
void InitializeDSPI(void)
{
    /* Initialize DSPI registers */
    DSPI_A.MCR.R = DSPIA_MCR_INIT;
	/* Enable external ADC */
    DSPI_A.CTAR[0].R = DSPIA_CTAR0_INIT;
	/* Enable RDC */
	DSPI_A.CTAR[1].R = DSPIA_CTAR1_INIT;
	

	/* Enable serial interface of the pressure sensor */
    DSPI_B.MCR.R = DSPIB_MCR_INIT;
	DSPI_B.CTAR[0].R = DSPIB_CTAR0_INIT;
	
	/* Enable Ethernet Controller */
    DSPI_C.MCR.R = DSPIC_MCR_INIT;
	DSPI_C.CTAR[0].R = DSPIC_CTAR0_INIT;

	
	/* Communication with Leak Detection */
    DSPI_D.MCR.R = DSPID_MCR_INIT;
	DSPI_D.CTAR[0].R = DSPID_CTAR0_INIT;

    /* Exit HALT mode for SPI_A module: go from STOPPED to RUNNING state */
    DSPI_A.MCR.B.HALT = 0x0;
}

/***************************************************************/
/* Local function : InitializeESCI                             */
/***************************************************************/
void InitializeESCI(void)
{
    /* Initialize eSCI registers */
    
    /* Baudrate is configured by APP software */
    /* SBR = System Frequency / (16 * baudrate_APP) */
    ESCI_A.CR1.R = (UNS32)((UNS32)(SYSTEM_CLOCK / ((UNS32)16 * I_BSP_conf.sci_conf.sci_speed)) << 16 ) + ESCIA_CR1_INIT;
    ESCI_A.CR2.R = ESCIA_CR2_INIT;
}

/***************************************************************/
/* Local function : InitializeEMIOS                            */
/***************************************************************/
void InitializeEMIOS(void)
{
    /* Initialize eMIOS registers */
    EMIOS.MCR.R = EMIOS_MCR_INIT;

    EMIOS.CH[EMIOS_INTERNAL_COUNTER_A_CHANNEL].CCR.R  = EMIOS_CCR23_INIT;
    EMIOS.CH[EMIOS_INTERNAL_COUNTER_A_CHANNEL].CBDR.R = EMIOS_CBDR23_INIT;
    EMIOS.CH[EMIOS_INTERNAL_COUNTER_A_CHANNEL].CADR.R = EMIOS_CADR23_INIT;
	
    EMIOS.CH[EMIOS_PWM_TM_OUT_1_CHANNEL].CCR.R  = EMIOS_CCR4_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_1_CHANNEL].CBDR.R = EMIOS_CBDR4_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_1_CHANNEL].CADR.R = EMIOS_CADR4_INIT;

    EMIOS.CH[EMIOS_PWM_TM_OUT_2_CHANNEL].CCR.R  = EMIOS_CCR5_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_2_CHANNEL].CBDR.R = EMIOS_CBDR5_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_2_CHANNEL].CADR.R = EMIOS_CADR5_INIT;

    EMIOS.CH[EMIOS_PWM_TM_OUT_3_CHANNEL].CCR.R  = EMIOS_CCR6_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_3_CHANNEL].CBDR.R = EMIOS_CBDR6_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_3_CHANNEL].CADR.R = EMIOS_CADR6_INIT;

    EMIOS.CH[EMIOS_PWM_TM_OUT_4_CHANNEL].CCR.R  = EMIOS_CCR7_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_4_CHANNEL].CBDR.R = EMIOS_CBDR7_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_4_CHANNEL].CADR.R = EMIOS_CADR7_INIT;

    EMIOS.CH[EMIOS_PWM_TM_OUT_5_CHANNEL].CCR.R  = EMIOS_CCR8_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_5_CHANNEL].CBDR.R = EMIOS_CBDR8_INIT;
    EMIOS.CH[EMIOS_PWM_TM_OUT_5_CHANNEL].CADR.R = EMIOS_CADR8_INIT;
}

/***************************************************************/
/* Local function : InitializeINTC                             */
/***************************************************************/
void InitializeINTC(void)
{
    UNS16 i;
    
    /* Initialize INTC registers */
    INTC.MCR.R = INTC_MCR_INIT;
    /* Set the interrupt priority 2 for the software interrupt 1 (Long action of BITE S/W) */
    INTC.PSR[0].R = 2;
    /* Set the interrupt priority 3 for the software interrupt 2 (Short action of BITE S/W) */
    INTC.PSR[1].R = 3;
    /* Disable the interrupt for the Flash and SRAM non-correctable ECC errors (managed by IVOR2) (errata 2071) */
    INTC.PSR[9].R = 0;
    /* Set the interrupt priority 13 for the external interrupt (external IRQ...) */
    INTC.PSR[50].R = 13;
    /* Set the interrupt priority 15 for the eTPU Global Exception */
    INTC.PSR[67].R = 15;
	/* Set the interrupt priority 13 for the eTPU ARINC reception interrupt requests */
    INTC.PSR[68].R = 13;
    INTC.PSR[70].R = 13;
    INTC.PSR[72].R = 13;
    INTC.PSR[74].R = 13;
    INTC.PSR[76].R = 13;
	
    /* Set the interrupt priority 15 for the eSCI_A module */
    INTC.PSR[146].R = 15;
    /* Set the interrupt priority 10 for the CAN_A module */
    for (i = 155; i <= 172; i++)
    {
        INTC.PSR[i].R = 10;
    }
	/* todo: add CAN_B and CAN_C interrupt priorities */
	
	/* Set the interrupt priority 11 for the eTPU AD1255 timer function */
    INTC.PSR[243].R = 11;
    /* Set the interrupt priority 12 for the eTPU Leak IT */
    INTC.PSR[253].R = 12;	
    /* Set lower INTC's current priority */
    INTC.CPR.B.PRI = 0;
    /* Initialize ISR vector table base address */
    INTC.IACKR.R = (UNS32) &K_TAB_intc_isr_vector_table[0];
}

/***************************************************************/
/* Local function : InitializeEDMA                             */
/***************************************************************/
void InitializeEDMA(void)
{
    /* Initialize eDMA registers */
    /* Disable Request (EDMA_ERQRH & EDMA_ERQRL) to eDMA */
    EDMA.ERQRH.R = EDMA_ERQRH_INIT;
    EDMA.ERQRL.R = EDMA_ERQRL_INIT;
    /* Disable Interrupt (EDMA_EEIRH & EDMA_EEIRL) to the eDMA */
    EDMA.EEIRH.R = EDMA_EEIRH_INIT;
    EDMA.EEIRL.R = EDMA_EEIRL_INIT;
}

/***************************************************************/
/* Local function : InitializeXBAR                             */
/***************************************************************/
void InitializeXBAR(void)
{
    /* Initialize XBAR registers */
    /* Set XBAR_MPR[0;1;3;6;7] and XBAR_SGPCR[0;1;3;6;7] registers to their reset value */
    XBAR.MPR0.R   = XBAR_MPR_INIT;
    XBAR.MPR1.R   = XBAR_MPR_INIT;
    XBAR.MPR3.R   = XBAR_MPR_INIT;
    XBAR.MPR6.R   = XBAR_MPR_INIT;
    XBAR.MPR7.R   = XBAR_MPR_INIT;
    XBAR.SGPCR0.R = XBAR_SGPCR_INIT;
    XBAR.SGPCR1.R = XBAR_SGPCR_INIT;
    XBAR.SGPCR3.R = XBAR_SGPCR_INIT;
    XBAR.SGPCR6.R = XBAR_SGPCR_INIT;
    XBAR.SGPCR7.R = XBAR_SGPCR_INIT;
}

/***************************************************************/
/* Local function : InitializeFLASH                            */
/***************************************************************/
void InitializeFLASH(void)
{
    /* Initialize BIUCR register (errata e2773, e2046, e989) */
    FLASH.BIUCR.R = FLASH_BIUCR_INIT;
}

/***************************************************************/
/* Local function : InitializePBRIDGE                          */
/***************************************************************/
void InitializePBRIDGE(void)
{
    /* Initialize PBRIDGE registers */
    /* Configures the PACRx Registers to allow software to access all peripheral in user mode */
    PBRIDGE_A.PACR0.R  = PBRIDGE_A_PACR0_INIT;
    PBRIDGE_B.PACR0.R  = PBRIDGE_B_PACR0_INIT;
    PBRIDGE_B.PACR2.R  = PBRIDGE_B_PACR2_INIT;
    /* Configures the OPACRx Registers to allow software to access all peripheral in user mode */
    PBRIDGE_A.OPACR0.R = PBRIDGE_A_OPACR0_INIT;
    PBRIDGE_A.OPACR1.R = PBRIDGE_A_OPACR1_INIT;
    PBRIDGE_A.OPACR2.R = PBRIDGE_A_OPACR2_INIT;
    PBRIDGE_B.OPACR0.R = PBRIDGE_B_OPACR0_INIT;
    PBRIDGE_B.OPACR1.R = PBRIDGE_B_OPACR1_INIT;
    PBRIDGE_B.OPACR2.R = PBRIDGE_B_OPACR2_INIT;
    PBRIDGE_B.OPACR3.R = PBRIDGE_B_OPACR3_INIT;
}

/***************************************************************/
/* Local function : InitializeECSM                             */
/***************************************************************/
void InitializeECSM(void)
{
    /* Initialize ECSM ECR register to enable reporting of non-correctable FLASH or internal RAM errors */
    ECSM.ECR.R = ECSM_ECR_INIT;
}

/***************************************************************/
/* Local function : InitializeMRAMBSP                          */
/***************************************************************/
void InitializeMRAMBSP(void)
{
    unsigned int index;
    unsigned int * PTR_bsp;

    PTR_bsp = &MRAM_BSP_data_adress;
    for(index=0; index < (unsigned int)&MRAM_BSP_data_size; index+=4)
    {
        *PTR_bsp = 0;
        PTR_bsp++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMAPP                          */
/***************************************************************/
void InitializeMRAMAPP(void)
{
    unsigned int index;
    unsigned int * PTR_app;

    PTR_app = &MRAM_APP_data_adress;
    for(index=0; index < (unsigned int)&MRAM_APP_data_size; index+=4)
    {
        *PTR_app = 0;
        PTR_app++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMSHAREDAPP                    */
/***************************************************************/
void InitializeMRAMSHAREDAPP(void)
{
    unsigned int index;
    unsigned int * PTR_shared_app;

    PTR_shared_app = &MRAM_SHARED_APP_data_adress;
    for(index=0; index < (unsigned int)&MRAM_SHARED_APP_data_size; index+=4)
    {
        *PTR_shared_app = 0;
        PTR_shared_app++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMHW                           */
/***************************************************************/
void InitializeMRAMHW(void)
{
    unsigned int index;
    unsigned int * PTR_hw;

    PTR_hw = &MRAM_HW_adress;
    for(index=0; index < (unsigned int)&MRAM_HW_size; index+=4)
    {
        *PTR_hw = 0;
        PTR_hw++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMEEPROMAPP                    */
/***************************************************************/
void InitializeMRAMEEPROMAPP(void)
{
    unsigned int index;
    unsigned int * PTR_eeprom_app;

    PTR_eeprom_app = &MRAM_EEPROM_APP_adress;
    for(index=0; index < (unsigned int)&MRAM_EEPROM_APP_size; index+=4)
    {
        *PTR_eeprom_app = 0;
        PTR_eeprom_app++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMBITE                         */
/***************************************************************/
void InitializeMRAMBITE(void)
{
    unsigned int index;
    unsigned int * PTR_bite;

    PTR_bite = &MRAM_BITE_adress;
    for(index=0; index < (unsigned int)&MRAM_BITE_size; index+=4)
    {
        *PTR_bite = 0;
        PTR_bite++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMSTACKBITE                    */
/***************************************************************/
void InitializeMRAMSTACKBITE(void)
{
    unsigned int index;
    unsigned int * PTR_stack_bite;

    PTR_stack_bite = &MRAM_stack_BITE_adress;
    for(index=0; index < (unsigned int)&MRAM_stack_BITE_size; index+=4)
    {
        *PTR_stack_bite = 0;
        PTR_stack_bite++;
    }
}

/***************************************************************/
/* Local function : InitializeMRAMSAPER                    */
/***************************************************************/
void InitializeMRAMSAPER(void)
{
    unsigned int index;
    unsigned int * PTR_saper;

    PTR_saper = &MRAM_Spare_adress;
    for(index=0; index < (unsigned int)&MRAM_Spare_size; index+=4)
    {
        *PTR_saper = 0;
        PTR_saper++;
    }
}

/***************************************************************/
/* Local function : ComputeStartUpType                         */
/***************************************************************/
void ComputeStartUpType(void)
{
    volatile UNS8 dummy;
    UNS32 i;

    /* IF a "long power cut" has been detected */
    if (MC_LONG_POWER_CUT == (UNS32)TRUE)
    /* THEN */
    {
        /* Call function InitializeInternalSRAMFirst32KB, to initialize the first 32KB of the internal SRAM */
        InitializeInternalSRAMFirst32KB();
		/* Call function InitializeMRAMHW, to initialize MRAM for HW */
		InitializeMRAMHW();
		/* Call function InitializeMRAMBSP, to initialize MRAM for BSP */
		InitializeMRAMBSP();
		/* Call function InitializeMRAMAPP, to initialize MRAM for APP */
		InitializeMRAMAPP();
		/* Call function InitializeMRAMSHAREDAPP, to initialize MRAM for SHARED_APP */
		InitializeMRAMSHAREDAPP();
		/* Call function InitializeMRAMEEPROMAPP, to initialize MRAM for EEPROM_APP */
		InitializeMRAMEEPROMAPP();
		/* Call function InitializeMRAMBITE, to initialize MRAM for BITE */
		InitializeMRAMBITE();
		/* Call function InitializeMRAMSTACKBITE, to initialize MRAM for STACK_BITE */
		InitializeMRAMSTACKBITE();
		/* Call function InitializeMRAMSAPER, to initialize MRAM for SAPER */
		InitializeMRAMSAPER();
        /* Declare power up is a "long power cut" (The data was erased by the initialization of the internal SRAM) */
        MC_LONG_POWER_CUT = (UNS32)TRUE;
        /* Declare the reset as not a Watchdog reset (The data was erased by the initialization of the internal SRAM) */
        MC_WATCHDOG_RESET = FALSE;
        /* Declare the watchdog is not currently tested (The data was erased by the initialization of the internal SRAM) */
        MC_WATCHDOG_TESTED = FALSE;
    }
    /* ELSE */
    else
    {
        /* Reset internal SRAM ECC error */
        ECSM.ESR.B.RNCE = 1;

        /* Declare the S/W as currently testing the internal SRAM */
        F_check_for_internal_SRAM_ECC_error = TRUE;

        /* Perform read accesses to the internal SRAM until end of the first 32Kbyte or until a SRAM ECC error occurs */
        i = 0;
        while ((i < (SRAM_SIZE / (UNS32)2)) && (ECSM.ESR.B.RNCE == 0))
        {
            dummy = ((UNS8*)SRAM_START)[i];
            i ++;
        }

        /* Declare the S/W as not currently testing the internal SRAM */
        F_check_for_internal_SRAM_ECC_error = FALSE;

        /* IF there is an internal SRAM ECC error */
        if (ECSM.ESR.B.RNCE == 1)
        /* THEN */
        {
            /* Reset internal SRAM ECC error */
            ECSM.ESR.B.RNCE = 1;

            /* Call function InitializeInternalSRAMFirst32KB, to initialize the first 32KB of the internal SRAM */
            InitializeInternalSRAMFirst32KB();

            /* Declare power up is a "long power cut" */
            MC_LONG_POWER_CUT = (UNS32)TRUE;
        }
        else
        {
        }
        /* END IF */
    }
    /* END IF */

    /***********************************************************/
    /* IF an external reset has occured                        */
    /* THEN                                                    */
    /*       The restart is a watchdog reset                   */
    /*    END IF                                               */
    /* ELSE                                                    */
    /*    The restart is not due to a watchdog reset           */
    /* END IF                                                  */
    /***********************************************************/
    if ((SIU.RSR.B.ERS == 1) && (SIU.RSR.B.PORS == 0))
    {
        MC_WATCHDOG_RESET = TRUE;
    }
    else
    {
        MC_WATCHDOG_RESET = FALSE;
    }
}

/***************************************************************/
/* Global function : InitializeHardware                        */
/***************************************************************/
void InitializeHardware(void)
{ 
	// TODO : A deplacer
	/*LAN9250_Instance_t LAN9250Instance;*/
	LAN9250_IO_Cfg_t LANConfig;
	DriverReturnCode_t ReturnCode_op;
	UNS16 nStartType_i;

    /*! FIRST HARDWARE Initialization */
    /* Initialize user reset source */
    user_reset_source = DEFAULT;

    /* Call InitializeCPU_Ini function, to initialize core modules */
    InitializeCPU_Ini();

    /* Call InitializePBRIDGE function, to initialize PBRIDGE registers */
    InitializePBRIDGE();

    /* Call InitializeSIU function, to initialize SIU registers */
    InitializeSIU();
    
    /* Call RearmWatchdog function */
    RearmWatchdog();

    /* Call InitializeDSPI function, to initialize the DSPI register */
    InitializeDSPI();
    
    /* Call InitializeEMIOS function, to initialize eMIOS registers */
    InitializeEMIOS();

    /* Call InitializeEDMA function, to initialize eDMA registers */
    InitializeEDMA();

    /* Call InitializeXBAR function, to initialize XBAR registers */
    InitializeXBAR();

    /* Call InitializeFLASH function to initialize FLASH registers */
    InitializeFLASH();

    /* Call InitializeECSM function to initialize ECSM registers */
    InitializeECSM();

    /* Call InitializeINTC function, to initialize Interrupt controller */
    InitializeINTC();
    
    /* Call InitializeEBI function, to initialize EBI registers */
    InitializeEBI();

    /* Call InitializeEQADC function, to initialize eQADC registers and functionality */
    /* TBD */
    InitializeEQADC();
	
	/* Call InitializeDisc_acq function, to initialize the discrete input module */
    InitializeDisc_acq();
	
	/* Call ComputeStartUpType function, to compute the start up type */
    ComputeStartUpType();

    /* Call EtpuInitializeEngine function, to initialize eTPU hardware */
    EtpuInitializeEngine();

    /* Call InitializeWatchdogTest function */    
    InitializeWatchdogTest();

    /* Call TestWatchdog function */
    TestWatchdog();
	
    /* Call InitializeSoftware function, to initialize all data of the BSP s/w and the APP s/w */
    InitializeSoftware();
	
	/* Call InitializeESCI function, to initialize eSCI registers */
    InitializeESCI();
	
	/* Initialize eTPU LEAK function */
	InitializeLeakInterface();
	
	/* Call InitializeARINCInterface function, to initialize eTPU ARINC function */
	Initializearinc_int();

	/* Call InitializeDC_Motor ETPU function */
    InitializeDcMotorsInterface();
	
	/* Call InitializeTorq_Motor function to initialize the data of corresponding the module */
	InitializeTorq_Motor();
	
	/* Call InitializeSTP_Motor ETPU function */
    InitializeSTP_Motor();
	

	
    /* Call EtpuStartTimeBase function, to Start eTPU */
    EtpuStartTimeBase();    

    /* Call InitializeDiscreteOutput function, to initialize the discrete output module */
    InitializeDisc_Out();
	
	/* IF SPI_A is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_A_enable == (UNS32)TRUE)
    /* THEN */
    {
        /* Exit HALT mode for SPI module A: go from STOPPED to RUNNING state */
        DSPI_A.MCR.B.HALT = 0x0;
        
        /* Call InitializeAD128S052 function */
        /* The AD128S052 is an external 12-bit ADC */
        InitializeAD128S052();
    }
    else
    {
    }
    /* END IF */
	
	/* IF SPI_B is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_B_enable == (UNS32)TRUE)
    /* THEN */
    {
        /* Exit HALT mode for SPI module B: go from STOPPED to RUNNING state */
        DSPI_B.MCR.B.HALT = 0x0;
		
		/* Call InitializeAD1255 function */
        /* The ADS1255 is an external 24-bit ADC */
        InitializeAD1255(); 
    }
    else
    {
    }
    /* END IF */
	
	/* IF SPI_C is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_C_enable == (UNS32)TRUE)
    /* THEN */
    {
        /* Exit HALT mode for SPI module C: go from STOPPED to RUNNING state */
        DSPI_C.MCR.B.HALT = 0x0;
    }
    else
    {
    }
    /* END IF */
	
	/* IF SPI_D is enable */
    if (I_BSP_conf.SPI_enable.B.F_SPI_D_enable == (UNS32)TRUE)
    /* THEN */
    {
        /* Exit HALT mode for SPI module D: go from STOPPED to RUNNING state */
        DSPI_D.MCR.B.HALT = 0x0;
    }
    else
    {
    }
    /* END IF */

    /* Call InitializeAllCAN function to initialize all CAN */
    InitializeAllCAN();
        
    /* Call the function InitializeDEC to start the Decrementer service */
    InitializeDEC();
    
    /* Call RearmWatchdog function */
    RearmWatchdog();
	
	/* Call GetRegistersInformation function to memorize the initialization values of the registers to monitor */
    /*GetRegistersInformation();*/
	
	/* Call GetHardwareSoftwareIdentification function to read the IASC configuration */
    GetHardwareSoftwareIdentification();
	
	// TODO : A reprendre
	LAN9250InstanceInit(&LAN9250Instance, &LANConfig);
	
	LAN9250_Init	((void *)&LAN9250Instance, (void *)&LANConfig, &ReturnCode_op);

	LAN9250_Start	((void *)&LAN9250Instance, nStartType_i, &ReturnCode_op);
		 
}

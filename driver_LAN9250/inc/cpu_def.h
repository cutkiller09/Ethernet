#ifndef __CPU_DEF_H__
#define __CPU_DEF_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                         GLOBAL TYPES                        */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*             MODULE : PBRIDGE_A Peripheral Bridge            */
/***************************************************************/
    struct PBRIDGE_A_tag 
    {
        /* Master Privilege Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 MBW0:1;
                VUNS32 MTR0:1;
                VUNS32 MTW0:1;
                VUNS32 MPL0:1;
                VUNS32 MBW1:1;
                VUNS32 MTR1:1;
                VUNS32 MTW1:1;
                VUNS32 MPL1:1;
                VUNS32 MBW2:1;
                VUNS32 MTR2:1;
                VUNS32 MTW2:1;
                VUNS32 MPL2:1;
                VUNS32 MBW3:1;
                VUNS32 MTR3:1;
                VUNS32 MTW3:1;
                VUNS32 MPL3:1;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
            }
            B;
        }
        MPCR;

        UNS32 pbridge_a_reserved2[7];

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32:28;
            }
            B;
        }
        PACR0;

        UNS32 pbridge_a_reserved3[7];

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32 BW1:1;
                VUNS32 SP1:1;
                VUNS32 WP1:1;
                VUNS32 TP1:1;
                VUNS32 BW2:1;
                VUNS32 SP2:1;
                VUNS32 WP2:1;
                VUNS32 TP2:1;
                VUNS32:4;
                VUNS32 BW4:1;
                VUNS32 SP4:1;
                VUNS32 WP4:1;
                VUNS32 TP4:1;
                VUNS32:12;
            }
            B;
        }
        OPACR0;

        union 
        {
            VUNS32 R;
            struct 
            {

                /* EMIOS */
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32:28;
            }
            B;
        }
        OPACR1;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32:4;
                VUNS32 BW2:1;
                VUNS32 SP2:1;
                VUNS32 WP2:1;
                VUNS32 TP2:1;
                VUNS32 BW3:1;
                VUNS32 SP3:1;
                VUNS32 WP3:1;
                VUNS32 TP3:1;
                VUNS32 BW4:1;
                VUNS32 SP4:1;
                VUNS32 WP4:1;
                VUNS32 TP4:1;
                VUNS32:12;
            }
            B;
        }
        OPACR2;

    };

/***************************************************************/
/*             MODULE : PBRIDGE_B Peripheral Bridge            */
/***************************************************************/
    struct PBRIDGE_B_tag 
    {
        /* Master Privilege Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 MBW0:1;
                VUNS32 MTR0:1;
                VUNS32 MTW0:1;
                VUNS32 MPL0:1;
                VUNS32 MBW1:1;
                VUNS32 MTR1:1;
                VUNS32 MTW1:1;
                VUNS32 MPL1:1;
                VUNS32 MBW2:1;
                VUNS32 MTR2:1;
                VUNS32 MTW2:1;
                VUNS32 MPL2:1;
                VUNS32 MBW3:1;
                VUNS32 MTR3:1;
                VUNS32 MTW3:1;
                VUNS32 MPL3:1;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
            }
            B;
        }
        MPCR;

        UNS32 pbridge_b_reserved2[7];

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32 BW1:1;
                VUNS32 SP1:1;
                VUNS32 WP1:1;
                VUNS32 TP1:1;
                VUNS32:24;
            }
            B;
        }
        PACR0;

        UNS32 pbridge_b_reserved3;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32 BW1:1;
                VUNS32 SP1:1;
                VUNS32 WP1:1;
                VUNS32 TP1:1;
                VUNS32 BW2:1;
                VUNS32 SP2:1;
                VUNS32 WP2:1;
                VUNS32 TP2:1;
                VUNS32:4;
                VUNS32:16;
            }
            B;
        }
        PACR2;

        UNS32 pbridge_b_reserved4[5];

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;
                VUNS32:12;

                /* DSPI_A */
                VUNS32 BW4:1;
                VUNS32 SP4:1;
                VUNS32 WP4:1;
                VUNS32 TP4:1;

                /* DSPI_B */
                VUNS32 BW5:1;
                VUNS32 SP5:1;
                VUNS32 WP5:1;
                VUNS32 TP5:1;
                VUNS32 BW6:1;
                VUNS32 SP6:1;
                VUNS32 WP6:1;
                VUNS32 TP6:1;
                VUNS32 BW7:1;
                VUNS32 SP7:1;
                VUNS32 WP7:1;
                VUNS32 TP7:1;
            }
            B;
        }
        OPACR0;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 BW4:1;
                VUNS32 SP4:1;
                VUNS32 WP4:1;
                VUNS32 TP4:1;

                /* ESCI_B */
                VUNS32 BW5:1;
                VUNS32 SP5:1;
                VUNS32 WP5:1;
                VUNS32 TP5:1;
                VUNS32:8;
            }
            B;
        }
        OPACR1;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BW0:1;
                VUNS32 SP0:1;
                VUNS32 WP0:1;
                VUNS32 TP0:1;

                /* CAN_B */
                VUNS32 BW1:1;
                VUNS32 SP1:1;
                VUNS32 WP1:1;
                VUNS32 TP1:1;
                VUNS32 BW2:1;
                VUNS32 SP2:1;
                VUNS32 WP2:1;
                VUNS32 TP2:1;
                VUNS32:4;
                VUNS32:4;
                VUNS32:12;
            }
            B;
        }
        OPACR2;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32:24;
                VUNS32 BW7:1;
                VUNS32 SP7:1;
                VUNS32 WP7:1;
                VUNS32 TP7:1;
            }
            B;
        }
        OPACR3;

    };

/***************************************************************/
/*                     MODULE : FMPLL                          */
/***************************************************************/
    struct FMPLL_tag 
    {
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:1;
                VUNS32 PREDIV:3;
                VUNS32 MFD:5;
                VUNS32:1;
                VUNS32 RFD:3;
                VUNS32 LOCEN:1;
                VUNS32 LOLRE:1;
                VUNS32 LOCRE:1;
                VUNS32 DISCLK:1;
                VUNS32 LOLIRQ:1;
                VUNS32 LOCIRQ:1;
                VUNS32 RATE:1;
                VUNS32 DEPTH:2;
                VUNS32 EXP:10;
            }
            B;
        }
        SYNCR;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:22;
                VUNS32 LOLF:1;
                VUNS32 LOC:1;
                VUNS32 MODE:1;
                VUNS32 PLLSEL:1;
                VUNS32 PLLREF:1;
                VUNS32 LOCKS:1;
                VUNS32 LOCK:1;
                VUNS32 LOCF:1;
                VUNS32 CALDONE:1;
                VUNS32 CALPASS:1;
            }
            B;
        }
        SYNSR;

    };

/***************************************************************/
/*                MODULE : External Bus Interface (EBI)       */
/***************************************************************/
    struct CS_tag 
    {
        /* Base Register Bank */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BA:17;
                VUNS32:3;
                VUNS32 PS:1;
                VUNS32:4;
                VUNS32 BL:1;
                VUNS32 WEBS:1;
                VUNS32 TBDIP:1;
                VUNS32:2;
                VUNS32 BI:1;
                VUNS32 V:1;
            }
            B;
        }
        BR;

        /* Option Register Bank */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 AM:17;
                VUNS32:7;
                VUNS32 SCY:4;
                VUNS32:1;
                VUNS32 BSCY:2;
                VUNS32:1;
            }
            B;
        }
        OR;
    };
    struct EBI_tag 
    {
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:5;
                VUNS32 SIZEEN:1;
                VUNS32 SIZE:2;
                VUNS32:8;
                VUNS32 ACGE:1;
                VUNS32 EXTM:1;
                VUNS32 EARB:1;
                VUNS32 EARP:2;
                VUNS32:4;
                VUNS32 MDIS:1;
                VUNS32:5;
                VUNS32 DBM:1;
            }
            B;
        }
        MCR;
        UNS32 EBI_reserved1;

        /* Transfer Error Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:30;
                VUNS32 TEAF:1;
                VUNS32 BMTF:1;
            }
            B;
        }
        TESR;

        /* Bus Monitor Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 BMT:8;
                VUNS32 BME:1;
                VUNS32:7;
            }
            B;
        }
        BMCR;
        struct CS_tag CS[4];
    };

/***************************************************************/
/*                     MODULE : FLASH                          */
/***************************************************************/
    struct FLASH_tag 
    {
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32 SIZE:4;
                VUNS32:1;
                VUNS32 LAS:3;
                VUNS32:3;
                VUNS32 MAS:1;
                VUNS32 EER:1;
                VUNS32 RWE:1;
                VUNS32 BBEPE:1;
                VUNS32 EPE:1;
                VUNS32 PEAS:1;
                VUNS32 DONE:1;
                VUNS32 PEG:1;
                VUNS32:2;
                VUNS32 STOP:1;
                VUNS32:1;
                VUNS32 PGM:1;
                VUNS32 PSUS:1;
                VUNS32 ERS:1;
                VUNS32 ESUS:1;
                VUNS32 EHV:1;
            }
            B;
        }
        MCR;

        /* LML Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 LME:1;
                VUNS32:10;
                VUNS32 SLOCK:1;
                VUNS32 MLOCK:4;
                VUNS32 LLOCK:16;
            }
            B;
        }
        LMLR;

        /* HL Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 HBE:1;
                VUNS32:3;
                VUNS32 HBLOCK:28;
            }
            B;
        }
        HLR;

        /* SLML Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 SLE:1;
                VUNS32:10;
                VUNS32 SSLOCK:1;
                VUNS32 SMLOCK:4;
                VUNS32 SLLOCK:16;
            }
            B;
        }
        SLMLR;

        /* LMS Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:12;
                VUNS32 MSEL:4;
                VUNS32 LSEL:16;
            }
            B;
        }
        LMSR;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32 HBSEL:28;
            }
            B;
        }
        HSR;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:10;
                VUNS32 ADDR:19;
                VUNS32:3;
            }
            B;
        }
        AR;

        union 
        {
            VUNS32 R;
            struct 
            {

                VUNS32:11;
                VUNS32:1;
                VUNS32 M3PFE:1;
                VUNS32 M2PFE:1;
                VUNS32 M1PFE:1;
                VUNS32 M0PFE:1;
                VUNS32 APC:3;
                VUNS32 WWSC:2;
                VUNS32 RWSC:3;
                VUNS32 DPFEN:2;
                VUNS32 IPFEN:2;
                VUNS32 PFLIM:3;
                VUNS32 BFEN:1;
            }
            B;
        }
        BIUCR;

        union 
        {
            VUNS32 R;
            struct 
            {

                VUNS32:22;
                VUNS32:2;
                VUNS32 M3AP:2;
                VUNS32 M2AP:2;
                VUNS32 M1AP:2;
                VUNS32 M0AP:2;
            }
            B;
        }
        BIUAPR;
    };

/***************************************************************/
/*                     MODULE : SIU                            */
/***************************************************************/
    struct SIU_tag 
    {
        INT32 SIU_reserved0;

        /* MCU ID Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 PARTNUM:16;
                VUNS32 MASKNUM:16;
            }
            B;
        }
        MIDR;
        INT32 SIU_reserved00;

        /* Reset Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 PORS:1;
                VUNS32 ERS:1;
                VUNS32 LLRS:1;
                VUNS32 LCRS:1;
                VUNS32 WDRS:1;
                VUNS32 CRS:1;
                VUNS32:8;
                VUNS32 SSRS:1;
                VUNS32 SERF:1;
                VUNS32 WKPCFG:1;
                VUNS32:12;
                VUNS32 BOOTCFG:2;
                VUNS32 RGF:1;
            }
            B;
        }
        RSR;

        /* System Reset Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 SSR:1;
                VUNS32 SER:1;
                VUNS32:14;
                VUNS32 CRE:1;
                VUNS32:15;
            }
            B;
        }
        SRCR;

        /* External Interrupt Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 EIF15:1;
                VUNS32 EIF14:1;
                VUNS32 EIF13:1;
                VUNS32 EIF12:1;
                VUNS32 EIF11:1;
                VUNS32 EIF10:1;
                VUNS32 EIF9:1;
                VUNS32 EIF8:1;
                VUNS32 EIF7:1;
                VUNS32 EIF6:1;
                VUNS32 EIF5:1;
                VUNS32 EIF4:1;
                VUNS32 EIF3:1;
                VUNS32 EIF2:1;
                VUNS32 EIF1:1;
                VUNS32 EIF0:1;
            }
            B;
        }
        EISR;

        /* DMA/Interrupt Request Enable Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 EIRE15:1;
                VUNS32 EIRE14:1;
                VUNS32 EIRE13:1;
                VUNS32 EIRE12:1;
                VUNS32 EIRE11:1;
                VUNS32 EIRE10:1;
                VUNS32 EIRE9:1;
                VUNS32 EIRE8:1;
                VUNS32 EIRE7:1;
                VUNS32 EIRE6:1;
                VUNS32 EIRE5:1;
                VUNS32 EIRE4:1;
                VUNS32 EIRE3:1;
                VUNS32 EIRE2:1;
                VUNS32 EIRE1:1;
                VUNS32 EIRE0:1;
            }
            B;
        }
        DIRER;

        /* DMA/Interrupt Select Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:28;
                VUNS32 DIRS3:1;
                VUNS32 DIRS2:1;
                VUNS32 DIRS1:1;
                VUNS32 DIRS0:1;
            }
            B;
        }
        DIRSR;

        /* Overrun Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 OVF15:1;
                VUNS32 OVF14:1;
                VUNS32 OVF13:1;
                VUNS32 OVF12:1;
                VUNS32 OVF11:1;
                VUNS32 OVF10:1;
                VUNS32 OVF9:1;
                VUNS32 OVF8:1;
                VUNS32 OVF7:1;
                VUNS32 OVF6:1;
                VUNS32 OVF5:1;
                VUNS32 OVF4:1;
                VUNS32 OVF3:1;
                VUNS32 OVF2:1;
                VUNS32 OVF1:1;
                VUNS32 OVF0:1;
            }
            B;
        }
        OSR;

        /* Overrun Request Enable Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 ORE15:1;
                VUNS32 ORE14:1;
                VUNS32 ORE13:1;
                VUNS32 ORE12:1;
                VUNS32 ORE11:1;
                VUNS32 ORE10:1;
                VUNS32 ORE9:1;
                VUNS32 ORE8:1;
                VUNS32 ORE7:1;
                VUNS32 ORE6:1;
                VUNS32 ORE5:1;
                VUNS32 ORE4:1;
                VUNS32 ORE3:1;
                VUNS32 ORE2:1;
                VUNS32 ORE1:1;
                VUNS32 ORE0:1;
            }
            B;
        }
        ORER;

        /* External IRQ Rising-Edge Event Enable Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 IREE15:1;
                VUNS32 IREE14:1;
                VUNS32 IREE13:1;
                VUNS32 IREE12:1;
                VUNS32 IREE11:1;
                VUNS32 IREE10:1;
                VUNS32 IREE9:1;
                VUNS32 IREE8:1;
                VUNS32 IREE7:1;
                VUNS32 IREE6:1;
                VUNS32 IREE5:1;
                VUNS32 IREE4:1;
                VUNS32 IREE3:1;
                VUNS32 IREE2:1;
                VUNS32 IREE1:1;
                VUNS32 IREE0:1;
            }
            B;
        }
        IREER;

        /* External IRQ Falling-Edge Event Enable Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 IFEE15:1;
                VUNS32 IFEE14:1;
                VUNS32 IFEE13:1;
                VUNS32 IFEE12:1;
                VUNS32 IFEE11:1;
                VUNS32 IFEE10:1;
                VUNS32 IFEE9:1;
                VUNS32 IFEE8:1;
                VUNS32 IFEE7:1;
                VUNS32 IFEE6:1;
                VUNS32 IFEE5:1;
                VUNS32 IFEE4:1;
                VUNS32 IFEE3:1;
                VUNS32 IFEE2:1;
                VUNS32 IFEE1:1;
                VUNS32 IFEE0:1;
            }
            B;
        }
        IFEER;

        /* External IRQ Digital Filter Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:28;
                VUNS32 DFL:4;
            }
            B;
        }
        IDFR;

        INT32 SIU_reserved1[3];

        /* Pad Configuration Registers */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16:3;
                VUNS16 PA:3;
                VUNS16 OBE:1;
                VUNS16 IBE:1;
                VUNS16 DSC:2;
                VUNS16 ODE:1;
                VUNS16 HYS:1;
                VUNS16 SRC:2;
                VUNS16 WPE:1;
                VUNS16 WPS:1;
            }
            B;
        }
        PCR[512];

        INT16 SIU_reserved_0[224];

        /* GPIO Pin Data Output Registers */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:7;
                VUNS8 PDO:1;
            }
            B;
        }
        GPDO[256];

        INT32 SIU_reserved_3[64];

        /* GPIO Pin Data Input Registers */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:7;
                VUNS8 PDI:1;
            }
            B;
        }
        GPDI[256];

        /* IMUX Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 TSEL5:2;
                VUNS32 TSEL4:2;
                VUNS32 TSEL3:2;
                VUNS32 TSEL2:2;
                VUNS32 TSEL1:2;
                VUNS32 TSEL0:2;
                VUNS32:20;
            }
            B;
        }
        ETISR;

        /* IMUX Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 ESEL15:2;
                VUNS32 ESEL14:2;
                VUNS32 ESEL13:2;
                VUNS32 ESEL12:2;
                VUNS32 ESEL11:2;
                VUNS32 ESEL10:2;
                VUNS32 ESEL9:2;
                VUNS32 ESEL8:2;
                VUNS32 ESEL7:2;
                VUNS32 ESEL6:2;
                VUNS32 ESEL5:2;
                VUNS32 ESEL4:2;
                VUNS32 ESEL3:2;
                VUNS32 ESEL2:2;
                VUNS32 ESEL1:2;
                VUNS32 ESEL0:2;
            }
            B;
        }
        EIISR;

        /* IMUX Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 SINSELA:2;
                VUNS32 SSSELA:2;
                VUNS32 SCKSELA:2;
                VUNS32 TRIGSELA:2;
                VUNS32 SINSELB:2;
                VUNS32 SSSELB:2;
                VUNS32 SCKSELB:2;
                VUNS32 TRIGSELB:2;
                VUNS32 SINSELC:2;
                VUNS32 SSSELC:2;
                VUNS32 SCKSELC:2;
                VUNS32 TRIGSELC:2;
                VUNS32 SINSELD:2;
                VUNS32 SSSELD:2;
                VUNS32 SCKSELD:2;
                VUNS32 TRIGSELD:2;
            }
            B;
        }
        DISR;

        INT32 SIU_reserved2[29];

        /* Chip Configuration Register Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:14;
                VUNS32 MATCH:1;
                VUNS32 DISNEX:1;
                VUNS32:16;
            }
            B;
        }
        CCR;

        /* External Clock Configuration Register Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:18;
                VUNS32 ENGDIV:6;
                VUNS32:4;
                VUNS32 EBTS:1;
                VUNS32:1;
                VUNS32 EBDF:2;
            }
            B;
        }
        ECCR;

        union 
        {
            VUNS32 R;
        }
        CARH;

        union 
        {
            VUNS32 R;
        }
        CARL;

        union 
        {
            VUNS32 R;
        }
        CBRH;

        union 
        {
            VUNS32 R;
        }
        CBRL;

    };

/***************************************************************/
/*                          MODULE : EMIOS                     */
/***************************************************************/
    struct EMIOS_tag 
    {
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:1;
                VUNS32 MDIS:1;
                VUNS32 FRZ:1;
                VUNS32 GTBE:1;
                VUNS32 ETB:1;
                VUNS32 GPREN:1;
                VUNS32:6;
                VUNS32 SRV:4;
                VUNS32 GPRE:8;
                VUNS32:8;
            }
            B;
        }
        MCR;

        /* Global FLAG Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:8;
                VUNS32 F23:1;
                VUNS32 F22:1;
                VUNS32 F21:1;
                VUNS32 F20:1;
                VUNS32 F19:1;
                VUNS32 F18:1;
                VUNS32 F17:1;
                VUNS32 F16:1;
                VUNS32 F15:1;
                VUNS32 F14:1;
                VUNS32 F13:1;
                VUNS32 F12:1;
                VUNS32 F11:1;
                VUNS32 F10:1;
                VUNS32 F9:1;
                VUNS32 F8:1;
                VUNS32 F7:1;
                VUNS32 F6:1;
                VUNS32 F5:1;
                VUNS32 F4:1;
                VUNS32 F3:1;
                VUNS32 F2:1;
                VUNS32 F1:1;
                VUNS32 F0:1;
            }
            B;
        }
        GFR;

        /* Output Update Disable Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:8;
                VUNS32 OU23:1;
                VUNS32 OU22:1;
                VUNS32 OU21:1;
                VUNS32 OU20:1;
                VUNS32 OU19:1;
                VUNS32 OU18:1;
                VUNS32 OU17:1;
                VUNS32 OU16:1;
                VUNS32 OU15:1;
                VUNS32 OU14:1;
                VUNS32 OU13:1;
                VUNS32 OU12:1;
                VUNS32 OU11:1;
                VUNS32 OU10:1;
                VUNS32 OU9:1;
                VUNS32 OU8:1;
                VUNS32 OU7:1;
                VUNS32 OU6:1;
                VUNS32 OU5:1;
                VUNS32 OU4:1;
                VUNS32 OU3:1;
                VUNS32 OU2:1;
                VUNS32 OU1:1;
                VUNS32 OU0:1;
            }
            B;
        }
        OUDR;

        UNS32 emios_reserved[5];

        struct 
        {
            union 
            {
                /* Channel A Data Register */
                VUNS32 R;
            }
            CADR;

            union 
            {
                /* Channel B Data Register */
                VUNS32 R;
            }
            CBDR;

            union 
            {
                /* Channel Counter Register */
                VUNS32 R;
            }
            CCNTR;

            /* Channel Control Register */
            union 
            {
                VUNS32 R;
                struct 
                {
                    VUNS32 FREN:1;
                    VUNS32 ODIS:1;
                    VUNS32 ODISSL:2;
                    VUNS32 UCPRE:2;
                    VUNS32 UCPREN:1;
                    VUNS32 DMA:1;
                    VUNS32:1;
                    VUNS32 IF:4;
                    VUNS32 FCK:1;
                    VUNS32 FEN:1;
                    VUNS32:3;
                    VUNS32 FORCMA:1;
                    VUNS32 FORCMB:1;
                    VUNS32:1;
                    VUNS32 BSL:2;
                    VUNS32 EDSEL:1;
                    VUNS32 EDPOL:1;
                    VUNS32 MODE:7;
                }
                B;
            }
            CCR;

            /* Channel Status Register */
            union 
            {
                VUNS32 R;
                struct 
                {
                    VUNS32 OVR:1;
                    VUNS32:15;
                    VUNS32 OVFL:1;
                    VUNS32:12;
                    VUNS32 UCIN:1;
                    VUNS32 UCOUT:1;
                    VUNS32 FLAG:1;
                }
                B;
            }
            CSR;
            UNS32 emios_channel_reserved[3];

        }
        CH[24];

    };

/***************************************************************/
/*                              MODULE :ETPU                   */
/***************************************************************/
    struct ETPU_tag 
    {
        /* MODULE CONFIGURATION REGISTER */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Global Exception Clear */
                VUNS32 GEC:1;
                VUNS32:3;

                /* Microcode Global Exception-ETPU_A */
                VUNS32 MGE1:1;

                /* Microcode Global Exception-ETPU_B */
                VUNS32 MGE2:1;

                /* Illegal Instruction Flag-ETPU_A */
                VUNS32 ILF1:1;

                /* Illegal Instruction Flag-ETPU_B */
                VUNS32 ILF2:1;
                VUNS32:3;

                /* Shared Code Memory size */
                VUNS32 SCMSIZE:5;
                VUNS32:5;

                /* SCM MISC Flag */
                VUNS32 SCMMISF:1;

                /* SCM MISC Enable */
                VUNS32 SCMMISEN:1;
                VUNS32:2;

                /* SCM Visability */
                VUNS32 VIS:1;
                VUNS32:5;

                /* Global Time Base Enable */
                VUNS32 GTBE:1;
            }
            B;
        }
        MCR;

        /* COHERENT DUAL-PARAMETER CONTROL */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Start Status bit */
                VUNS32 STS:1;

                /* Channel Transfer Base */
                VUNS32 CTBASE:5;

                /* Parameter Buffer Base Address */
                VUNS32 PBASE:10;

                /* Parameter Width */
                VUNS32 PWIDTH:1;

                /* Channel Parameter 0 */
                VUNS32 PARAM0:7;
                VUNS32 WR:1;

                /* Channel Parameter 1 */
                VUNS32 PARAM1:7;
            }
            B;
        }
        CDCR;

        UNS32 etpu_reserved1;

        /* MISC Compare Register */
        union 
        {
            VUNS32 R;
        }
        MISCCMPR;

        /* SCM off-range Date Register */
        union 
        {
            VUNS32 R;
        }
        SCMOFFDATAR;

        /* ETPU_A Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Force END */
                VUNS32 FEND:1;

                /* Low power Stop */
                VUNS32 MDIS:1;
                VUNS32:1;

                /* Stop Flag */
                VUNS32 STF:1;
                VUNS32:4;

                /* Halt Mode Flag */
                VUNS32 HLTF:1;
                VUNS32:4;

                /* Filter Prescaler Clock Control */
                VUNS32 FPSCK:3;
                VUNS32 CDFC:2;
                VUNS32:9;

                /* Entry Table Base */
                VUNS32 ETB:5;
            }
            B;
        }
        ECR_A;

        /* ETPU_B Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Force END */
                VUNS32 FEND:1;

                /* Low power Stop */
                VUNS32 MDIS:1;
                VUNS32:1;

                /* Stop Flag */
                VUNS32 STF:1;
                VUNS32:4;

                /* Halt Mode Flag */
                VUNS32 HLTF:1;
                VUNS32:4;

                /* Filter Prescaler Clock Control */
                VUNS32 FPSCK:3;
                VUNS32 CDFC:2;
                VUNS32:9;

                /* Entry Table Base */
                VUNS32 ETB:5;
            }
            B;
        }
        ECR_B;

        UNS32 etpu_reserved4;

        /* ETPU_A Timebase Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* TCR2 Clock/Gate Control */
                VUNS32 TCR2CTL:3;

                /* TCRCLK Signal Filter Control */
                VUNS32 TCRCF:2;
                VUNS32:1;

                /* Angle Mode */
                VUNS32 AM:1;
                VUNS32:3;

                /* TCR2 Prescaler Control */
                VUNS32 TCR2P:6;

                /* TCR1 Clock/Gate Control */
                VUNS32 TCR1CTL:2;
                VUNS32:6;

                /* TCR1 Prescaler Control */
                VUNS32 TCR1P:8;
            }
            B;
        }
        TBCR_A;

        /* ETPU_A TCR1 Visibility Register */
        union 
        {
            VUNS32 R;
        }
        TB1R_A;

        /* ETPU_A TCR2 Visibility Register */
        union 
        {
            VUNS32 R;
        }
        TB2R_A;

        /* ETPU_A STAC Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Resource Enable TCR1 */
                VUNS32 REN1:1;

                /* Resource Control TCR1 */
                VUNS32 RSC1:1;
                VUNS32:2;
                VUNS32 SERVER_ID1:4;
                VUNS32:4;

                /* Resource Server Slot */
                VUNS32 SRV1:4;

                /* Resource Enable TCR2 */
                VUNS32 REN2:1;

                /* Resource Control TCR2 */
                VUNS32 RSC2:1;
                VUNS32:2;
                VUNS32 SERVER_ID2:4;
                VUNS32:4;

                /* Resource Server Slot */
                VUNS32 SRV2:4;
            }
            B;
        }
        REDCR_A;

        UNS32 etpu_reserved5[4];

        /* ETPU_B Timebase Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* TCR2 Clock/Gate Control */
                VUNS32 TCR2CTL:3;

                /* TCRCLK Signal Filter Control */
                VUNS32 TCRCF:2;
                VUNS32:1;

                /* Angle Mode */
                VUNS32 AM:1;
                VUNS32:3;

                /* TCR2 Prescaler Control */
                VUNS32 TCR2P:6;

                /* TCR1 Clock/Gate Control */
                VUNS32 TCR1CTL:2;

                  VUNS32:6;

                /* TCR1 Prescaler Control */
                VUNS32 TCR1P:8;
            }
            B;
        }
        TBCR_B;

        /* ETPU_B TCR1 Visibility Register */
        union 
        {
            VUNS32 R;
        }
        TB1R_B;

        /* ETPU_B TCR2 Visibility Register */
        union 
        {
            VUNS32 R;
        }
        TB2R_B;

        /* ETPU_B STAC Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Resource Enable TCR1 */
                VUNS32 REN1:1;

                /* Resource Control TCR1 */
                VUNS32 RSC1:1;

                  VUNS32:2;
                VUNS32 SERVER_ID1:4;
                  VUNS32:4;

                /* Resource Server Slot */
                VUNS32 SRV1:4;

                /* Resource Enable TCR2 */
                VUNS32 REN2:1;

                /* Resource Control TCR2 */
                VUNS32 RSC2:1;

                  VUNS32:2;
                VUNS32 SERVER_ID2:4;
                  VUNS32:4;

                /* Resource Server Slot */
                VUNS32 SRV2:4;
            }
            B;
        }
        REDCR_B;

        UNS32 etpu_reserved7[108];

/*****************************Status and Control Registers**************************/

        /* ETPU_A Channel Interrut Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Interrut Status */
                VUNS32 CIS31:1;

                /* Channel 30 Interrut Status */
                VUNS32 CIS30:1;

                /* Channel 29 Interrut Status */
                VUNS32 CIS29:1;

                /* Channel 28 Interrut Status */
                VUNS32 CIS28:1;

                /* Channel 27 Interrut Status */
                VUNS32 CIS27:1;

                /* Channel 26 Interrut Status */
                VUNS32 CIS26:1;

                /* Channel 25 Interrut Status */
                VUNS32 CIS25:1;

                /* Channel 24 Interrut Status */
                VUNS32 CIS24:1;

                /* Channel 23 Interrut Status */
                VUNS32 CIS23:1;

                /* Channel 22 Interrut Status */
                VUNS32 CIS22:1;

                /* Channel 21 Interrut Status */
                VUNS32 CIS21:1;

                /* Channel 20 Interrut Status */
                VUNS32 CIS20:1;

                /* Channel 19 Interrut Status */
                VUNS32 CIS19:1;

                /* Channel 18 Interrut Status */
                VUNS32 CIS18:1;

                /* Channel 17 Interrut Status */
                VUNS32 CIS17:1;

                /* Channel 16 Interrut Status */
                VUNS32 CIS16:1;

                /* Channel 15 Interrut Status */
                VUNS32 CIS15:1;

                /* Channel 14 Interrut Status */
                VUNS32 CIS14:1;

                /* Channel 13 Interrut Status */
                VUNS32 CIS13:1;

                /* Channel 12 Interrut Status */
                VUNS32 CIS12:1;

                /* Channel 11 Interrut Status */
                VUNS32 CIS11:1;

                /* Channel 10 Interrut Status */
                VUNS32 CIS10:1;

                /* Channel 9 Interrut Status */
                VUNS32 CIS9:1;

                /* Channel 8 Interrut Status */
                VUNS32 CIS8:1;

                /* Channel 7 Interrut Status */
                VUNS32 CIS7:1;

                /* Channel 6 Interrut Status */
                VUNS32 CIS6:1;

                /* Channel 5 Interrut Status */
                VUNS32 CIS5:1;

                /* Channel 4 Interrut Status */
                VUNS32 CIS4:1;

                /* Channel 3 Interrut Status */
                VUNS32 CIS3:1;

                /* Channel 2 Interrut Status */
                VUNS32 CIS2:1;

                /* Channel 1 Interrut Status */
                VUNS32 CIS1:1;

                /* Channel 0 Interrut Status */
                VUNS32 CIS0:1;
            }
            B;
        }
        CISR_A;

        /* ETPU_B Channel Interrupt Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Interrut Status */
                VUNS32 CIS31:1;

                /* Channel 30 Interrut Status */
                VUNS32 CIS30:1;

                /* Channel 29 Interrut Status */
                VUNS32 CIS29:1;

                /* Channel 28 Interrut Status */
                VUNS32 CIS28:1;

                /* Channel 27 Interrut Status */
                VUNS32 CIS27:1;

                /* Channel 26 Interrut Status */
                VUNS32 CIS26:1;

                /* Channel 25 Interrut Status */
                VUNS32 CIS25:1;

                /* Channel 24 Interrut Status */
                VUNS32 CIS24:1;

                /* Channel 23 Interrut Status */
                VUNS32 CIS23:1;

                /* Channel 22 Interrut Status */
                VUNS32 CIS22:1;

                /* Channel 21 Interrut Status */
                VUNS32 CIS21:1;

                /* Channel 20 Interrut Status */
                VUNS32 CIS20:1;

                /* Channel 19 Interrut Status */
                VUNS32 CIS19:1;

                /* Channel 18 Interrut Status */
                VUNS32 CIS18:1;

                /* Channel 17 Interrut Status */
                VUNS32 CIS17:1;

                /* Channel 16 Interrut Status */
                VUNS32 CIS16:1;

                /* Channel 15 Interrut Status */
                VUNS32 CIS15:1;

                /* Channel 14 Interrut Status */
                VUNS32 CIS14:1;

                /* Channel 13 Interrut Status */
                VUNS32 CIS13:1;

                /* Channel 12 Interrut Status */
                VUNS32 CIS12:1;

                /* Channel 11 Interrut Status */
                VUNS32 CIS11:1;

                /* Channel 10 Interrut Status */
                VUNS32 CIS10:1;

                /* Channel 9 Interrut Status */
                VUNS32 CIS9:1;

                /* Channel 8 Interrut Status */
                VUNS32 CIS8:1;

                /* Channel 7 Interrut Status */
                VUNS32 CIS7:1;

                /* Channel 6 Interrut Status */
                VUNS32 CIS6:1;

                /* Channel 5 Interrut Status */
                VUNS32 CIS5:1;

                /* Channel 4 Interrut Status */
                VUNS32 CIS4:1;

                /* Channel 3 Interrut Status */
                VUNS32 CIS3:1;

                /* Channel 2 Interrut Status */
                VUNS32 CIS2:1;

                /* Channel 1 Interrupt Status */
                VUNS32 CIS1:1;

                /* Channel 0 Interrupt Status */
                VUNS32 CIS0:1;
            }
            B;
        }
        CISR_B;

        UNS32 etpu_reserved9[2];

        /* ETPU_A Data Transfer Request Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Data Transfer Request Status */
                VUNS32 DTRS31:1;

                /* Channel 30 Data Transfer Request Status */
                VUNS32 DTRS30:1;

                /* Channel 29 Data Transfer Request Status */
                VUNS32 DTRS29:1;

                /* Channel 28 Data Transfer Request Status */
                VUNS32 DTRS28:1;

                /* Channel 27 Data Transfer Request Status */
                VUNS32 DTRS27:1;

                /* Channel 26 Data Transfer Request Status */
                VUNS32 DTRS26:1;

                /* Channel 25 Data Transfer Request Status */
                VUNS32 DTRS25:1;

                /* Channel 24 Data Transfer Request Status */
                VUNS32 DTRS24:1;

                /* Channel 23 Data Transfer Request Status */
                VUNS32 DTRS23:1;

                /* Channel 22 Data Transfer Request Status */
                VUNS32 DTRS22:1;

                /* Channel 21 Data Transfer Request Status */
                VUNS32 DTRS21:1;

                /* Channel 20 Data Transfer Request Status */
                VUNS32 DTRS20:1;

                /* Channel 19 Data Transfer Request Status */
                VUNS32 DTRS19:1;

                /* Channel 18 Data Transfer Request Status */
                VUNS32 DTRS18:1;

                /* Channel 17 Data Transfer Request Status */
                VUNS32 DTRS17:1;

                /* Channel 16 Data Transfer Request Status */
                VUNS32 DTRS16:1;

                /* Channel 15 Data Transfer Request Status */
                VUNS32 DTRS15:1;

                /* Channel 14 Data Transfer Request Status */
                VUNS32 DTRS14:1;

                /* Channel 13 Data Transfer Request Status */
                VUNS32 DTRS13:1;

                /* Channel 12 Data Transfer Request Status */
                VUNS32 DTRS12:1;

                /* Channel 11 Data Transfer Request Status */
                VUNS32 DTRS11:1;

                /* Channel 10 Data Transfer Request Status */
                VUNS32 DTRS10:1;

                /* Channel 9 Data Transfer Request Status */
                VUNS32 DTRS9:1;

                /* Channel 8 Data Transfer Request Status */
                VUNS32 DTRS8:1;

                /* Channel 7 Data Transfer Request Status */
                VUNS32 DTRS7:1;

                /* Channel 6 Data Transfer Request Status */
                VUNS32 DTRS6:1;

                /* Channel 5 Data Transfer Request Status */
                VUNS32 DTRS5:1;

                /* Channel 4 Data Transfer Request Status */
                VUNS32 DTRS4:1;

                /* Channel 3 Data Transfer Request Status */
                VUNS32 DTRS3:1;

                /* Channel 2 Data Transfer Request Status */
                VUNS32 DTRS2:1;

                /* Channel 1 Data Transfer Request Status */
                VUNS32 DTRS1:1;

                /* Channel 0 Data Transfer Request Status */
                VUNS32 DTRS0:1;
            }
            B;
        }
        CDTRSR_A;

        /* ETPU_B Data Transfer Request Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Data Transfer Request Status */
                VUNS32 DTRS31:1;

                /* Channel 30 Data Transfer Request Status */
                VUNS32 DTRS30:1;

                /* Channel 29 Data Transfer Request Status */
                VUNS32 DTRS29:1;

                /* Channel 28 Data Transfer Request Status */
                VUNS32 DTRS28:1;

                /* Channel 27 Data Transfer Request Status */
                VUNS32 DTRS27:1;

                /* Channel 26 Data Transfer Request Status */
                VUNS32 DTRS26:1;

                /* Channel 25 Data Transfer Request Status */
                VUNS32 DTRS25:1;

                /* Channel 24 Data Transfer Request Status */
                VUNS32 DTRS24:1;

                /* Channel 23 Data Transfer Request Status */
                VUNS32 DTRS23:1;

                /* Channel 22 Data Transfer Request Status */
                VUNS32 DTRS22:1;

                /* Channel 21 Data Transfer Request Status */
                VUNS32 DTRS21:1;

                /* Channel 20 Data Transfer Request Status */
                VUNS32 DTRS20:1;

                /* Channel 19 Data Transfer Request Status */
                VUNS32 DTRS19:1;

                /* Channel 18 Data Transfer Request Status */
                VUNS32 DTRS18:1;

                /* Channel 17 Data Transfer Request Status */
                VUNS32 DTRS17:1;

                /* Channel 16 Data Transfer Request Status */
                VUNS32 DTRS16:1;

                /* Channel 15 Data Transfer Request Status */
                VUNS32 DTRS15:1;

                /* Channel 14 Data Transfer Request Status */
                VUNS32 DTRS14:1;

                /* Channel 13 Data Transfer Request Status */
                VUNS32 DTRS13:1;

                /* Channel 12 Data Transfer Request Status */
                VUNS32 DTRS12:1;

                /* Channel 11 Data Transfer Request Status */
                VUNS32 DTRS11:1;

                /* Channel 10 Data Transfer Request Status */
                VUNS32 DTRS10:1;

                /* Channel 9 Data Transfer Request Status */
                VUNS32 DTRS9:1;

                /* Channel 8 Data Transfer Request Status */
                VUNS32 DTRS8:1;

                /* Channel 7 Data Transfer Request Status */
                VUNS32 DTRS7:1;

                /* Channel 6 Data Transfer Request Status */
                VUNS32 DTRS6:1;

                /* Channel 5 Data Transfer Request Status */
                VUNS32 DTRS5:1;

                /* Channel 4 Data Transfer Request Status */
                VUNS32 DTRS4:1;

                /* Channel 3 Data Transfer Request Status */
                VUNS32 DTRS3:1;

                /* Channel 2 Data Transfer Request Status */
                VUNS32 DTRS2:1;

                /* Channel 1 Data Transfer Request Status */
                VUNS32 DTRS1:1;

                /* Channel 0 Data Transfer Request Status */
                VUNS32 DTRS0:1;
            }
            B;
        }
        CDTRSR_B;

        UNS32 etpu_reserved11[2];

        /* ETPU_A Interrupt Overflow Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Interrupt Overflow Status */
                VUNS32 CIOS31:1;

                /* Channel 30 Interrupt Overflow Status */
                VUNS32 CIOS30:1;

                /* Channel 29 Interrupt Overflow Status */
                VUNS32 CIOS29:1;

                /* Channel 28 Interrupt Overflow Status */
                VUNS32 CIOS28:1;

                /* Channel 27 Interrupt Overflow Status */
                VUNS32 CIOS27:1;

                /* Channel 26 Interrupt Overflow Status */
                VUNS32 CIOS26:1;

                /* Channel 25 Interrupt Overflow Status */
                VUNS32 CIOS25:1;

                /* Channel 24 Interrupt Overflow Status */
                VUNS32 CIOS24:1;

                /* Channel 23 Interrupt Overflow Status */
                VUNS32 CIOS23:1;

                /* Channel 22 Interrupt Overflow Status */
                VUNS32 CIOS22:1;

                /* Channel 21 Interrupt Overflow Status */
                VUNS32 CIOS21:1;

                /* Channel 20 Interrupt Overflow Status */
                VUNS32 CIOS20:1;

                /* Channel 19 Interrupt Overflow Status */
                VUNS32 CIOS19:1;

                /* Channel 18 Interrupt Overflow Status */
                VUNS32 CIOS18:1;

                /* Channel 17 Interrupt Overflow Status */
                VUNS32 CIOS17:1;

                /* Channel 16 Interrupt Overflow Status */
                VUNS32 CIOS16:1;

                /* Channel 15 Interrupt Overflow Status */
                VUNS32 CIOS15:1;

                /* Channel 14 Interrupt Overflow Status */
                VUNS32 CIOS14:1;

                /* Channel 13 Interrupt Overflow Status */
                VUNS32 CIOS13:1;

                /* Channel 12 Interrupt Overflow Status */
                VUNS32 CIOS12:1;

                /* Channel 11 Interrupt Overflow Status */
                VUNS32 CIOS11:1;

                /* Channel 10 Interrupt Overflow Status */
                VUNS32 CIOS10:1;

                /* Channel 9 Interrupt Overflow Status */
                VUNS32 CIOS9:1;

                /* Channel 8 Interrupt Overflow Status */
                VUNS32 CIOS8:1;

                /* Channel 7 Interrupt Overflow Status */
                VUNS32 CIOS7:1;

                /* Channel 6 Interrupt Overflow Status */
                VUNS32 CIOS6:1;

                /* Channel 5 Interrupt Overflow Status */
                VUNS32 CIOS5:1;

                /* Channel 4 Interrupt Overflow Status */
                VUNS32 CIOS4:1;

                /* Channel 3 Interrupt Overflow Status */
                VUNS32 CIOS3:1;

                /* Channel 2 Interrupt Overflow Status */
                VUNS32 CIOS2:1;

                /* Channel 1 Interrupt Overflow Status */
                VUNS32 CIOS1:1;

                /* Channel 0 Interrupt Overflow Status */
                VUNS32 CIOS0:1;
            }
            B;
        }
        CIOSR_A;

        /* ETPU_B Interrupt Overflow Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Interrupt Overflow Status */
                VUNS32 CIOS31:1;

                /* Channel 30 Interrupt Overflow Status */
                VUNS32 CIOS30:1;

                /* Channel 29 Interrupt Overflow Status */
                VUNS32 CIOS29:1;

                /* Channel 28 Interrupt Overflow Status */
                VUNS32 CIOS28:1;

                /* Channel 27 Interrupt Overflow Status */
                VUNS32 CIOS27:1;

                /* Channel 26 Interrupt Overflow Status */
                VUNS32 CIOS26:1;

                /* Channel 25 Interrupt Overflow Status */
                VUNS32 CIOS25:1;

                /* Channel 24 Interrupt Overflow Status */
                VUNS32 CIOS24:1;

                /* Channel 23 Interrupt Overflow Status */
                VUNS32 CIOS23:1;

                /* Channel 22 Interrupt Overflow Status */
                VUNS32 CIOS22:1;

                /* Channel 21 Interrupt Overflow Status */
                VUNS32 CIOS21:1;

                /* Channel 20 Interrupt Overflow Status */
                VUNS32 CIOS20:1;

                /* Channel 19 Interrupt Overflow Status */
                VUNS32 CIOS19:1;

                /* Channel 18 Interrupt Overflow Status */
                VUNS32 CIOS18:1;

                /* Channel 17 Interrupt Overflow Status */
                VUNS32 CIOS17:1;

                /* Channel 16 Interrupt Overflow Status */
                VUNS32 CIOS16:1;

                /* Channel 15 Interrupt Overflow Status */
                VUNS32 CIOS15:1;

                /* Channel 14 Interrupt Overflow Status */
                VUNS32 CIOS14:1;

                /* Channel 13 Interrupt Overflow Status */
                VUNS32 CIOS13:1;

                /* Channel 12 Interrupt Overflow Status */
                VUNS32 CIOS12:1;

                /* Channel 11 Interrupt Overflow Status */
                VUNS32 CIOS11:1;

                /* Channel 10 Interrupt Overflow Status */
                VUNS32 CIOS10:1;

                /* Channel 9 Interrupt Overflow Status */
                VUNS32 CIOS9:1;

                /* Channel 8 Interrupt Overflow Status */
                VUNS32 CIOS8:1;

                /* Channel 7 Interrupt Overflow Status */
                VUNS32 CIOS7:1;

                /* Channel 6 Interrupt Overflow Status */
                VUNS32 CIOS6:1;

                /* Channel 5 Interrupt Overflow Status */
                VUNS32 CIOS5:1;

                /* Channel 4 Interrupt Overflow Status */
                VUNS32 CIOS4:1;

                /* Channel 3 Interrupt Overflow Status */
                VUNS32 CIOS3:1;

                /* Channel 2 Interrupt Overflow Status */
                VUNS32 CIOS2:1;

                /* Channel 1 Interrupt Overflow Status */
                VUNS32 CIOS1:1;

                /* Channel 0 Interrupt Overflow Status */
                VUNS32 CIOS0:1;
            }
            B;
        }
        CIOSR_B;

        UNS32 etpu_reserved13[2];

        /* ETPU_A Data Transfer Overflow Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Data Transfer Overflow Status */
                VUNS32 DTROS31:1;

                /* Channel 30 Data Transfer Overflow Status */
                VUNS32 DTROS30:1;

                /* Channel 29 Data Transfer Overflow Status */
                VUNS32 DTROS29:1;

                /* Channel 28 Data Transfer Overflow Status */
                VUNS32 DTROS28:1;

                /* Channel 27 Data Transfer Overflow Status */
                VUNS32 DTROS27:1;

                /* Channel 26 Data Transfer Overflow Status */
                VUNS32 DTROS26:1;

                /* Channel 25 Data Transfer Overflow Status */
                VUNS32 DTROS25:1;

                /* Channel 24 Data Transfer Overflow Status */
                VUNS32 DTROS24:1;

                /* Channel 23 Data Transfer Overflow Status */
                VUNS32 DTROS23:1;

                /* Channel 22 Data Transfer Overflow Status */
                VUNS32 DTROS22:1;

                /* Channel 21 Data Transfer Overflow Status */
                VUNS32 DTROS21:1;

                /* Channel 20 Data Transfer Overflow Status */
                VUNS32 DTROS20:1;

                /* Channel 19 Data Transfer Overflow Status */
                VUNS32 DTROS19:1;

                /* Channel 18 Data Transfer Overflow Status */
                VUNS32 DTROS18:1;

                /* Channel 17 Data Transfer Overflow Status */
                VUNS32 DTROS17:1;

                /* Channel 16 Data Transfer Overflow Status */
                VUNS32 DTROS16:1;

                /* Channel 15 Data Transfer Overflow Status */
                VUNS32 DTROS15:1;

                /* Channel 14 Data Transfer Overflow Status */
                VUNS32 DTROS14:1;

                /* Channel 13 Data Transfer Overflow Status */
                VUNS32 DTROS13:1;

                /* Channel 12 Data Transfer Overflow Status */
                VUNS32 DTROS12:1;

                /* Channel 11 Data Transfer Overflow Status */
                VUNS32 DTROS11:1;

                /* Channel 10 Data Transfer Overflow Status */
                VUNS32 DTROS10:1;

                /* Channel 9 Data Transfer Overflow Status */
                VUNS32 DTROS9:1;

                /* Channel 8 Data Transfer Overflow Status */
                VUNS32 DTROS8:1;

                /* Channel 7 Data Transfer Overflow Status */
                VUNS32 DTROS7:1;

                /* Channel 6 Data Transfer Overflow Status */
                VUNS32 DTROS6:1;

                /* Channel 5 Data Transfer Overflow Status */
                VUNS32 DTROS5:1;

                /* Channel 4 Data Transfer Overflow Status */
                VUNS32 DTROS4:1;

                /* Channel 3 Data Transfer Overflow Status */
                VUNS32 DTROS3:1;

                /* Channel 2 Data Transfer Overflow Status */
                VUNS32 DTROS2:1;

                /* Channel 1 Data Transfer Overflow Status */
                VUNS32 DTROS1:1;

                /* Channel 0 Data Transfer Overflow Status */
                VUNS32 DTROS0:1;
            }
            B;
        }
        CDTROSR_A;

        /* ETPU_B Data Transfer Overflow Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Data Transfer Overflow Status */
                VUNS32 DTROS31:1;

                /* Channel 30 Data Transfer Overflow Status */
                VUNS32 DTROS30:1;

                /* Channel 29 Data Transfer Overflow Status */
                VUNS32 DTROS29:1;

                /* Channel 28 Data Transfer Overflow Status */
                VUNS32 DTROS28:1;

                /* Channel 27 Data Transfer Overflow Status */
                VUNS32 DTROS27:1;

                /* Channel 26 Data Transfer Overflow Status */
                VUNS32 DTROS26:1;

                /* Channel 25 Data Transfer Overflow Status */
                VUNS32 DTROS25:1;

                /* Channel 24 Data Transfer Overflow Status */
                VUNS32 DTROS24:1;

                /* Channel 23 Data Transfer Overflow Status */
                VUNS32 DTROS23:1;

                /* Channel 22 Data Transfer Overflow Status */
                VUNS32 DTROS22:1;

                /* Channel 21 Data Transfer Overflow Status */
                VUNS32 DTROS21:1;

                /* Channel 20 Data Transfer Overflow Status */
                VUNS32 DTROS20:1;

                /* Channel 19 Data Transfer Overflow Status */
                VUNS32 DTROS19:1;

                /* Channel 18 Data Transfer Overflow Status */
                VUNS32 DTROS18:1;

                /* Channel 17 Data Transfer Overflow Status */
                VUNS32 DTROS17:1;

                /* Channel 16 Data Transfer Overflow Status */
                VUNS32 DTROS16:1;

                /* Channel 15 Data Transfer Overflow Status */
                VUNS32 DTROS15:1;

                /* Channel 14 Data Transfer Overflow Status */
                VUNS32 DTROS14:1;

                /* Channel 13 Data Transfer Overflow Status */
                VUNS32 DTROS13:1;

                /* Channel 12 Data Transfer Overflow Status */
                VUNS32 DTROS12:1;

                /* Channel 11 Data Transfer Overflow Status */
                VUNS32 DTROS11:1;

                /* Channel 10 Data Transfer Overflow Status */
                VUNS32 DTROS10:1;

                /* Channel 9 Data Transfer Overflow Status */
                VUNS32 DTROS9:1;

                /* Channel 8 Data Transfer Overflow Status */
                VUNS32 DTROS8:1;

                /* Channel 7 Data Transfer Overflow Status */
                VUNS32 DTROS7:1;

                /* Channel 6 Data Transfer Overflow Status */
                VUNS32 DTROS6:1;

                /* Channel 5 Data Transfer Overflow Status */
                VUNS32 DTROS5:1;

                /* Channel 4 Data Transfer Overflow Status */
                VUNS32 DTROS4:1;

                /* Channel 3 Data Transfer Overflow Status */
                VUNS32 DTROS3:1;

                /* Channel 2 Data Transfer Overflow Status */
                VUNS32 DTROS2:1;

                /* Channel 1 Data Transfer Overflow Status */
                VUNS32 DTROS1:1;

                /* Channel 0 Data Transfer Overflow Status */
                VUNS32 DTROS0:1;
            }
            B;
        }
        CDTROSR_B;

        UNS32 etpu_reserved15[2];

        /* ETPU_A Channel Interrupt Enable */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Interrupt Enable */
                VUNS32 CIE31:1;

                /* Channel 30 Interrupt Enable */
                VUNS32 CIE30:1;

                /* Channel 29 Interrupt Enable */
                VUNS32 CIE29:1;

                /* Channel 28 Interrupt Enable */
                VUNS32 CIE28:1;

                /* Channel 27 Interrupt Enable */
                VUNS32 CIE27:1;

                /* Channel 26 Interrupt Enable */
                VUNS32 CIE26:1;

                /* Channel 25 Interrupt Enable */
                VUNS32 CIE25:1;

                /* Channel 24 Interrupt Enable */
                VUNS32 CIE24:1;

                /* Channel 23 Interrupt Enable */
                VUNS32 CIE23:1;

                /* Channel 22 Interrupt Enable */
                VUNS32 CIE22:1;

                /* Channel 21 Interrupt Enable */
                VUNS32 CIE21:1;

                /* Channel 20 Interrupt Enable */
                VUNS32 CIE20:1;

                /* Channel 19 Interrupt Enable */
                VUNS32 CIE19:1;

                /* Channel 18 Interrupt Enable */
                VUNS32 CIE18:1;

                /* Channel 17 Interrupt Enable */
                VUNS32 CIE17:1;

                /* Channel 16 Interrupt Enable */
                VUNS32 CIE16:1;

                /* Channel 15 Interrupt Enable */
                VUNS32 CIE15:1;

                /* Channel 14 Interrupt Enable */
                VUNS32 CIE14:1;

                /* Channel 13 Interrupt Enable */
                VUNS32 CIE13:1;

                /* Channel 12 Interrupt Enable */
                VUNS32 CIE12:1;

                /* Channel 11 Interrupt Enable */
                VUNS32 CIE11:1;

                /* Channel 10 Interrupt Enable */
                VUNS32 CIE10:1;

                /* Channel 9 Interrupt Enable */
                VUNS32 CIE9:1;

                /* Channel 8 Interrupt Enable */
                VUNS32 CIE8:1;

                /* Channel 7 Interrupt Enable */
                VUNS32 CIE7:1;

                /* Channel 6 Interrupt Enable */
                VUNS32 CIE6:1;

                /* Channel 5 Interrupt Enable */
                VUNS32 CIE5:1;

                /* Channel 4 Interrupt Enable */
                VUNS32 CIE4:1;

                /* Channel 3 Interrupt Enable */
                VUNS32 CIE3:1;

                /* Channel 2 Interrupt Enable */
                VUNS32 CIE2:1;

                /* Channel 1 Interrupt Enable */
                VUNS32 CIE1:1;

                /* Channel 0 Interrupt Enable */
                VUNS32 CIE0:1;
            }
            B;
        }
        CIER_A;

        /* ETPU_B Channel Interrupt Enable */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Interrupt Enable */
                VUNS32 CIE31:1;

                /* Channel 30 Interrupt Enable */
                VUNS32 CIE30:1;

                /* Channel 29 Interrupt Enable */
                VUNS32 CIE29:1;

                /* Channel 28 Interrupt Enable */
                VUNS32 CIE28:1;

                /* Channel 27 Interrupt Enable */
                VUNS32 CIE27:1;

                /* Channel 26 Interrupt Enable */
                VUNS32 CIE26:1;

                /* Channel 25 Interrupt Enable */
                VUNS32 CIE25:1;

                /* Channel 24 Interrupt Enable */
                VUNS32 CIE24:1;

                /* Channel 23 Interrupt Enable */
                VUNS32 CIE23:1;

                /* Channel 22 Interrupt Enable */
                VUNS32 CIE22:1;

                /* Channel 21 Interrupt Enable */
                VUNS32 CIE21:1;

                /* Channel 20 Interrupt Enable */
                VUNS32 CIE20:1;

                /* Channel 19 Interrupt Enable */
                VUNS32 CIE19:1;

                /* Channel 18 Interrupt Enable */
                VUNS32 CIE18:1;

                /* Channel 17 Interrupt Enable */
                VUNS32 CIE17:1;

                /* Channel 16 Interrupt Enable */
                VUNS32 CIE16:1;

                /* Channel 15 Interrupt Enable */
                VUNS32 CIE15:1;

                /* Channel 14 Interrupt Enable */
                VUNS32 CIE14:1;

                /* Channel 13 Interrupt Enable */
                VUNS32 CIE13:1;

                /* Channel 12 Interrupt Enable */
                VUNS32 CIE12:1;

                /* Channel 11 Interrupt Enable */
                VUNS32 CIE11:1;

                /* Channel 10 Interrupt Enable */
                VUNS32 CIE10:1;

                /* Channel 9 Interrupt Enable */
                VUNS32 CIE9:1;

                /* Channel 8 Interrupt Enable */
                VUNS32 CIE8:1;

                /* Channel 7 Interrupt Enable */
                VUNS32 CIE7:1;

                /* Channel 6 Interrupt Enable */
                VUNS32 CIE6:1;

                /* Channel 5 Interrupt Enable */
                VUNS32 CIE5:1;

                /* Channel 4 Interrupt Enable */
                VUNS32 CIE4:1;

                /* Channel 3 Interrupt Enable */
                VUNS32 CIE3:1;

                /* Channel 2 Interrupt Enable */
                VUNS32 CIE2:1;

                /* Channel 1 Interrupt Enable */
                VUNS32 CIE1:1;

                /* Channel 0 Interrupt Enable */
                VUNS32 CIE0:1;
            }
            B;
        }
        CIER_B;

        UNS32 etpu_reserved17[2];

        /* ETPU_A Channel Data Transfer Request Enable */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Data Transfer Request Enable */
                VUNS32 DTRE31:1;

                /* Channel 30 Data Transfer Request Enable */
                VUNS32 DTRE30:1;

                /* Channel 29 Data Transfer Request Enable */
                VUNS32 DTRE29:1;

                /* Channel 28 Data Transfer Request Enable */
                VUNS32 DTRE28:1;

                /* Channel 27 Data Transfer Request Enable */
                VUNS32 DTRE27:1;

                /* Channel 26 Data Transfer Request Enable */
                VUNS32 DTRE26:1;

                /* Channel 25 Data Transfer Request Enable */
                VUNS32 DTRE25:1;

                /* Channel 24 Data Transfer Request Enable */
                VUNS32 DTRE24:1;

                /* Channel 23 Data Transfer Request Enable */
                VUNS32 DTRE23:1;

                /* Channel 22 Data Transfer Request Enable */
                VUNS32 DTRE22:1;

                /* Channel 21 Data Transfer Request Enable */
                VUNS32 DTRE21:1;

                /* Channel 20 Data Transfer Request Enable */
                VUNS32 DTRE20:1;

                /* Channel 19 Data Transfer Request Enable */
                VUNS32 DTRE19:1;

                /* Channel 18 Data Transfer Request Enable */
                VUNS32 DTRE18:1;

                /* Channel 17 Data Transfer Request Enable */
                VUNS32 DTRE17:1;

                /* Channel 16 Data Transfer Request Enable */
                VUNS32 DTRE16:1;

                /* Channel 15 Data Transfer Request Enable */
                VUNS32 DTRE15:1;

                /* Channel 14 Data Transfer Request Enable */
                VUNS32 DTRE14:1;

                /* Channel 13 Data Transfer Request Enable */
                VUNS32 DTRE13:1;

                /* Channel 12 Data Transfer Request Enable */
                VUNS32 DTRE12:1;

                /* Channel 11 Data Transfer Request Enable */
                VUNS32 DTRE11:1;

                /* Channel 10 Data Transfer Request Enable */
                VUNS32 DTRE10:1;

                /* Channel 9 Data Transfer Request Enable */
                VUNS32 DTRE9:1;

                /* Channel 8 Data Transfer Request Enable */
                VUNS32 DTRE8:1;

                /* Channel 7 Data Transfer Request Enable */
                VUNS32 DTRE7:1;

                /* Channel 6 Data Transfer Request Enable */
                VUNS32 DTRE6:1;

                /* Channel 5 Data Transfer Request Enable */
                VUNS32 DTRE5:1;

                /* Channel 4 Data Transfer Request Enable */
                VUNS32 DTRE4:1;

                /* Channel 3 Data Transfer Request Enable */
                VUNS32 DTRE3:1;

                /* Channel 2 Data Transfer Request Enable */
                VUNS32 DTRE2:1;

                /* Channel 1 Data Transfer Request Enable */
                VUNS32 DTRE1:1;

                /* Channel 0 Data Transfer Request Enable */
                VUNS32 DTRE0:1;
            }
            B;
        }
        CDTRER_A;

        /* ETPU_B Channel Data Transfer Request Enable */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Data Transfer Request Enable */
                VUNS32 DTRE31:1;

                /* Channel 30 Data Transfer Request Enable */
                VUNS32 DTRE30:1;

                /* Channel 29 Data Transfer Request Enable */
                VUNS32 DTRE29:1;

                /* Channel 28 Data Transfer Request Enable */
                VUNS32 DTRE28:1;

                /* Channel 27 Data Transfer Request Enable */
                VUNS32 DTRE27:1;

                /* Channel 26 Data Transfer Request Enable */
                VUNS32 DTRE26:1;

                /* Channel 25 Data Transfer Request Enable */
                VUNS32 DTRE25:1;

                /* Channel 24 Data Transfer Request Enable */
                VUNS32 DTRE24:1;

                /* Channel 23 Data Transfer Request Enable */
                VUNS32 DTRE23:1;

                /* Channel 22 Data Transfer Request Enable */
                VUNS32 DTRE22:1;

                /* Channel 21 Data Transfer Request Enable */
                VUNS32 DTRE21:1;

                /* Channel 20 Data Transfer Request Enable */
                VUNS32 DTRE20:1;

                /* Channel 19 Data Transfer Request Enable */
                VUNS32 DTRE19:1;

                /* Channel 18 Data Transfer Request Enable */
                VUNS32 DTRE18:1;

                /* Channel 17 Data Transfer Request Enable */
                VUNS32 DTRE17:1;

                /* Channel 16 Data Transfer Request Enable */
                VUNS32 DTRE16:1;

                /* Channel 15 Data Transfer Request Enable */
                VUNS32 DTRE15:1;

                /* Channel 14 Data Transfer Request Enable */
                VUNS32 DTRE14:1;

                /* Channel 13 Data Transfer Request Enable */
                VUNS32 DTRE13:1;

                /* Channel 12 Data Transfer Request Enable */
                VUNS32 DTRE12:1;

                /* Channel 11 Data Transfer Request Enable */
                VUNS32 DTRE11:1;

                /* Channel 10 Data Transfer Request Enable */
                VUNS32 DTRE10:1;

                /* Channel 9 Data Transfer Request Enable */
                VUNS32 DTRE9:1;

                /* Channel 8 Data Transfer Request Enable */
                VUNS32 DTRE8:1;

                /* Channel 7 Data Transfer Request Enable */
                VUNS32 DTRE7:1;

                /* Channel 6 Data Transfer Request Enable */
                VUNS32 DTRE6:1;

                /* Channel 5 Data Transfer Request Enable */
                VUNS32 DTRE5:1;

                /* Channel 4 Data Transfer Request Enable */
                VUNS32 DTRE4:1;

                /* Channel 3 Data Transfer Request Enable */
                VUNS32 DTRE3:1;

                /* Channel 2 Data Transfer Request Enable */
                VUNS32 DTRE2:1;

                /* Channel 1 Data Transfer Request Enable */
                VUNS32 DTRE1:1;

                /* Channel 0 Data Transfer Request Enable */
                VUNS32 DTRE0:1;
            }
            B;
        }
        CDTRER_B;

        UNS32 etpu_reserved20[10];

        /* ETPU_A Channel Pending Service Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Pending Service Status */
                VUNS32 SR31:1;

                /* Channel 30 Pending Service Status */
                VUNS32 SR30:1;

                /* Channel 29 Pending Service Status */
                VUNS32 SR29:1;

                /* Channel 28 Pending Service Status */
                VUNS32 SR28:1;

                /* Channel 27 Pending Service Status */
                VUNS32 SR27:1;

                /* Channel 26 Pending Service Status */
                VUNS32 SR26:1;

                /* Channel 25 Pending Service Status */
                VUNS32 SR25:1;

                /* Channel 24 Pending Service Status */
                VUNS32 SR24:1;

                /* Channel 23 Pending Service Status */
                VUNS32 SR23:1;

                /* Channel 22 Pending Service Status */
                VUNS32 SR22:1;

                /* Channel 21 Pending Service Status */
                VUNS32 SR21:1;

                /* Channel 20 Pending Service Status */
                VUNS32 SR20:1;

                /* Channel 19 Pending Service Status */
                VUNS32 SR19:1;

                /* Channel 18 Pending Service Status */
                VUNS32 SR18:1;

                /* Channel 17 Pending Service Status */
                VUNS32 SR17:1;

                /* Channel 16 Pending Service Status */
                VUNS32 SR16:1;

                /* Channel 15 Pending Service Status */
                VUNS32 SR15:1;

                /* Channel 14 Pending Service Status */
                VUNS32 SR14:1;

                /* Channel 13 Pending Service Status */
                VUNS32 SR13:1;

                /* Channel 12 Pending Service Status */
                VUNS32 SR12:1;

                /* Channel 11 Pending Service Status */
                VUNS32 SR11:1;

                /* Channel 10 Pending Service Status */
                VUNS32 SR10:1;

                /* Channel 9 Pending Service Status */
                VUNS32 SR9:1;

                /* Channel 8 Pending Service Status */
                VUNS32 SR8:1;

                /* Channel 7 Pending Service Status */
                VUNS32 SR7:1;

                /* Channel 6 Pending Service Status */
                VUNS32 SR6:1;

                /* Channel 5 Pending Service Status */
                VUNS32 SR5:1;

                /* Channel 4 Pending Service Status */
                VUNS32 SR4:1;

                /* Channel 3 Pending Service Status */
                VUNS32 SR3:1;

                /* Channel 2 Pending Service Status */
                VUNS32 SR2:1;

                /* Channel 1 Pending Service Status */
                VUNS32 SR1:1;

                /* Channel 0 Pending Service Status */
                VUNS32 SR0:1;
            }
            B;
        }
        CPSSR_A;

        /* ETPU_B Channel Pending Service Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Pending Service Status */
                VUNS32 SR31:1;

                /* Channel 30 Pending Service Status */
                VUNS32 SR30:1;

                /* Channel 29 Pending Service Status */
                VUNS32 SR29:1;

                /* Channel 28 Pending Service Status */
                VUNS32 SR28:1;

                /* Channel 27 Pending Service Status */
                VUNS32 SR27:1;

                /* Channel 26 Pending Service Status */
                VUNS32 SR26:1;

                /* Channel 25 Pending Service Status */
                VUNS32 SR25:1;

                /* Channel 24 Pending Service Status */
                VUNS32 SR24:1;

                /* Channel 23 Pending Service Status */
                VUNS32 SR23:1;

                /* Channel 22 Pending Service Status */
                VUNS32 SR22:1;

                /* Channel 21 Pending Service Status */
                VUNS32 SR21:1;

                /* Channel 20 Pending Service Status */
                VUNS32 SR20:1;

                /* Channel 19 Pending Service Status */
                VUNS32 SR19:1;

                /* Channel 18 Pending Service Status */
                VUNS32 SR18:1;

                /* Channel 17 Pending Service Status */
                VUNS32 SR17:1;

                /* Channel 16 Pending Service Status */
                VUNS32 SR16:1;

                /* Channel 15 Pending Service Status */
                VUNS32 SR15:1;

                /* Channel 14 Pending Service Status */
                VUNS32 SR14:1;

                /* Channel 13 Pending Service Status */
                VUNS32 SR13:1;

                /* Channel 12 Pending Service Status */
                VUNS32 SR12:1;

                /* Channel 11 Pending Service Status */
                VUNS32 SR11:1;

                /* Channel 10 Pending Service Status */
                VUNS32 SR10:1;

                /* Channel 9 Pending Service Status */
                VUNS32 SR9:1;

                /* Channel 8 Pending Service Status */
                VUNS32 SR8:1;

                /* Channel 7 Pending Service Status */
                VUNS32 SR7:1;

                /* Channel 6 Pending Service Status */
                VUNS32 SR6:1;

                /* Channel 5 Pending Service Status */
                VUNS32 SR5:1;

                /* Channel 4 Pending Service Status */
                VUNS32 SR4:1;

                /* Channel 3 Pending Service Status */
                VUNS32 SR3:1;

                /* Channel 2 Pending Service Status */
                VUNS32 SR2:1;

                /* Channel 1 Pending Service Status */
                VUNS32 SR1:1;

                /* Channel 0 Pending Service Status */
                VUNS32 SR0:1;
            }
            B;
        }
        CPSSR_B;

        UNS32 etpu_reserved20a[2];

        /* ETPU_A Channel Service Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Service Status */
                VUNS32 SS31:1;

                /* Channel 30 Service Status */
                VUNS32 SS30:1;

                /* Channel 29 Service Status */
                VUNS32 SS29:1;

                /* Channel 28 Service Status */
                VUNS32 SS28:1;

                /* Channel 27 Service Status */
                VUNS32 SS27:1;

                /* Channel 26 Service Status */
                VUNS32 SS26:1;

                /* Channel 25 Service Status */
                VUNS32 SS25:1;

                /* Channel 24 Service Status */
                VUNS32 SS24:1;

                /* Channel 23 Service Status */
                VUNS32 SS23:1;

                /* Channel 22 Service Status */
                VUNS32 SS22:1;

                /* Channel 21 Service Status */
                VUNS32 SS21:1;

                /* Channel 20 Service Status */
                VUNS32 SS20:1;

                /* Channel 19 Service Status */
                VUNS32 SS19:1;

                /* Channel 18 Service Status */
                VUNS32 SS18:1;

                /* Channel 17 Service Status */
                VUNS32 SS17:1;

                /* Channel 16 Service Status */
                VUNS32 SS16:1;

                /* Channel 15 Service Status */
                VUNS32 SS15:1;

                /* Channel 14 Service Status */
                VUNS32 SS14:1;

                /* Channel 13 Service Status */
                VUNS32 SS13:1;

                /* Channel 12 Service Status */
                VUNS32 SS12:1;

                /* Channel 11 Service Status */
                VUNS32 SS11:1;

                /* Channel 10 Service Status */
                VUNS32 SS10:1;

                /* Channel 9 Service Status */
                VUNS32 SS9:1;

                /* Channel 8 Service Status */
                VUNS32 SS8:1;

                /* Channel 7 Service Status */
                VUNS32 SS7:1;

                /* Channel 6 Service Status */
                VUNS32 SS6:1;

                /* Channel 5 Service Status */
                VUNS32 SS5:1;

                /* Channel 4 Service Status */
                VUNS32 SS4:1;

                /* Channel 3 Service Status */
                VUNS32 SS3:1;

                /* Channel 2 Service Status */
                VUNS32 SS2:1;

                /* Channel 1 Service Status */
                VUNS32 SS1:1;

                /* Channel 0 Service Status */
                VUNS32 SS0:1;
            }
            B;
        }
        CSSR_A;

        /* ETPU_B Channel Service Status */
        union 
        {
            VUNS32 R;
            struct 
            {
                /* Channel 31 Service Status */
                VUNS32 SS31:1;

                /* Channel 30 Service Status */
                VUNS32 SS30:1;

                /* Channel 29 Service Status */
                VUNS32 SS29:1;

                /* Channel 28 Service Status */
                VUNS32 SS28:1;

                /* Channel 27 Service Status */
                VUNS32 SS27:1;

                /* Channel 26 Service Status */
                VUNS32 SS26:1;

                /* Channel 25 Service Status */
                VUNS32 SS25:1;

                /* Channel 24 Service Status */
                VUNS32 SS24:1;

                /* Channel 23 Service Status */
                VUNS32 SS23:1;

                /* Channel 22 Service Status */
                VUNS32 SS22:1;

                /* Channel 21 Service Status */
                VUNS32 SS21:1;

                /* Channel 20 Service Status */
                VUNS32 SS20:1;

                /* Channel 19 Service Status */
                VUNS32 SS19:1;

                /* Channel 18 Service Status */
                VUNS32 SS18:1;

                /* Channel 17 Service Status */
                VUNS32 SS17:1;

                /* Channel 16 Service Status */
                VUNS32 SS16:1;

                /* Channel 15 Service Status */
                VUNS32 SS15:1;

                /* Channel 14 Service Status */
                VUNS32 SS14:1;

                /* Channel 13 Service Status */
                VUNS32 SS13:1;

                /* Channel 12 Service Status */
                VUNS32 SS12:1;

                /* Channel 11 Service Status */
                VUNS32 SS11:1;

                /* Channel 10 Service Status */
                VUNS32 SS10:1;

                /* Channel 9 Service Status */
                VUNS32 SS9:1;

                /* Channel 8 Service Status */
                VUNS32 SS8:1;

                /* Channel 7 Service Status */
                VUNS32 SS7:1;

                /* Channel 6 Service Status */
                VUNS32 SS6:1;

                /* Channel 5 Service Status */
                VUNS32 SS5:1;

                /* Channel 4 Service Status */
                VUNS32 SS4:1;

                /* Channel 3 Service Status */
                VUNS32 SS3:1;

                /* Channel 2 Service Status */
                VUNS32 SS2:1;

                /* Channel 1 Service Status */
                VUNS32 SS1:1;

                /* Channel 0 Service Status */
                VUNS32 SS0:1;
            }
            B;
        }
        CSSR_B;

        UNS32 etpu_reserved23[90];

/*****************************Channels********************************/
/* Channel number: 0-31 for ETPU_A and 64-95 for ETPU_B */

        struct 
        {
            union 
            {
                /* Channel Configuration Register */
                VUNS32 R;
                struct 
                {
                    /* Channel Interrupt Enable */
                    VUNS32 CIE:1;

                    /* Data Transfer Request Enable */
                    VUNS32 DTRE:1;

                    /* Channel Priority */
                    VUNS32 CPR:2;

                    VUNS32:3;

                    /* Entry Table Condition Select */
                    VUNS32 ETCS:1;

                    VUNS32:3;

                    /* Channel Function Select */
                    VUNS32 CFS:5;

                    /* Output disable */
                    VUNS32 ODIS:1;

                    /* output polarity */
                    VUNS32 OPOL:1;

                    VUNS32:3;

                    /* Channel Parameter Base Address */
                    VUNS32 CPBA:11;
                }
                B;
            }
            CR;
            union 
            {
                /* Channel Status Control Register */
                VUNS32 R;
                struct 
                {
                    /* Channel Interrupt Status */
                    VUNS32 CIS:1;

                    /* Channel Interrupt Overflow Status */
                    VUNS32 CIOS:1;

                    VUNS32:6;

                    /* Data Transfer Status */
                    VUNS32 DTRS:1;

                    /* Data Transfer Overflow Status */
                    VUNS32 DTROS:1;

                    VUNS32:6;

                    /* Input Pin State */
                    VUNS32 IPS:1;

                    /* Output Pin State */
                    VUNS32 OPS:1;

                    /* Output Buffer Enable */
                    VUNS32 OBE:1;

                    VUNS32:11;

                    /* Function mode */
                    VUNS32 FM1:1;

                    /* Function mode */
                    VUNS32 FM0:1;
                }
                B;
            }
            SCR;
            union 
            {
                /* Channel Host Service Request Register */
                VUNS32 R;
                struct 
                {
                    /* Host Service Request */
                    VUNS32:29;
                    VUNS32 HSR:3;
                }
                B;
            }
            HSRR;
            UNS32 etpu_reserved23;
        }
        CHAN[127];

    };

/***************************************************************/
/*                          MODULE : XBAR CrossBar             */
/***************************************************************/
    struct XBAR_tag 
    {
        /* Master Priority Register for Slave Port 0 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:1;
                VUNS32 MSTR2:3;
                VUNS32:1;
                VUNS32 MSTR1:3;
                VUNS32:1;
                VUNS32 MSTR0:3;
            }
            B;
        }
        MPR0;

        UNS32 xbar_reserved1[3];

        /* General Purpose Control Register for Slave Port 0 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 RO:1;
                VUNS32:21;
                VUNS32 ARB:2;
                VUNS32:2;
                VUNS32 PCTL:2;
                VUNS32:1;
                VUNS32 PARK:3;
            }
            B;
        }
        SGPCR0;

        UNS32 xbar_reserved2[59];

        /* Master Priority Register for Slave Port 1 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:1;
                VUNS32 MSTR2:3;
                VUNS32:1;
                VUNS32 MSTR1:3;
                VUNS32:1;
                VUNS32 MSTR0:3;
            }
            B;
        }
        MPR1;

        UNS32 xbar_reserved3[3];

        /* General Purpose Control Register for Slave Port 1 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 RO:1;
                VUNS32:21;
                VUNS32 ARB:2;
                VUNS32:2;
                VUNS32 PCTL:2;
                VUNS32:1;
                VUNS32 PARK:3;
            }
            B;
        }
        SGPCR1;

        UNS32 xbar_reserved4[123];

        /* Master Priority Register for Slave Port 3 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:1;
                VUNS32 MSTR2:3;
                VUNS32:1;
                VUNS32 MSTR1:3;
                VUNS32:1;
                VUNS32 MSTR0:3;
            }
            B;
        }
        MPR3;

        UNS32 xbar_reserved5[3];

        /* General Purpose Control Register for Slave Port 3 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 RO:1;
                VUNS32:21;
                VUNS32 ARB:2;
                VUNS32:2;
                VUNS32 PCTL:2;
                VUNS32:1;
                VUNS32 PARK:3;
            }
            B;
        }
        SGPCR3;
        UNS32 xbar_reserved6[187];

        /* Master Priority Register for Slave Port 6 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:1;
                VUNS32 MSTR2:3;
                VUNS32:1;
                VUNS32 MSTR1:3;
                VUNS32:1;
                VUNS32 MSTR0:3;
            }
            B;
        }
        MPR6;

        UNS32 xbar_reserved7[3];

        /* General Purpose Control Register for Slave Port 6 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 RO:1;
                VUNS32:21;
                VUNS32 ARB:2;
                VUNS32:2;
                VUNS32 PCTL:2;
                VUNS32:1;
                VUNS32 PARK:3;
            }
            B;
        }
        SGPCR6;

        UNS32 xbar_reserved8[59];

        /* Master Priority Register for Slave Port 7 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:4;
                VUNS32:1;
                VUNS32 MSTR2:3;
                VUNS32:1;
                VUNS32 MSTR1:3;
                VUNS32:1;
                VUNS32 MSTR0:3;
            }
            B;
        }
        MPR7;

        UNS32 xbar_reserved9[3];

        /* General Purpose Control Register for Slave Port 7 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 RO:1;
                VUNS32:21;
                VUNS32 ARB:2;
                VUNS32:2;
                VUNS32 PCTL:2;
                VUNS32:1;
                VUNS32 PARK:3;
            }
            B;
        }
        SGPCR7;

    };

/***************************************************************/
/*                     MODULE : ECSM                                        */
/***************************************************************/
    struct ECSM_tag 
    {

        UNS32 ecsm_reserved1[5];

        UNS16 ecsm_reserved2;

        /* Software Watchdog Timer Control */
        union 
        {
            VUNS16 R;
        }
        SWTCR;

        UNS8 ecsm_reserved3[3];

        /* SWT Service Register */
        union 
        {
            VUNS8 R;
        }
        SWTSR;

        UNS8 ecsm_reserved4[3];

        /* SWT Interrupt Register */
        union 
        {
            VUNS8 R;
        }
        SWTIR;

        UNS32 ecsm_reserved5a[1];
        UNS32 ecsm_reserved5b[1];

        UNS32 ecsm_reserved5c[6];

        UNS8 ecsm_reserved6[3];

        /* ECC Configuration Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:6;
                VUNS8 ERNCR:1;
                VUNS8 EFNCR:1;
            }
            B;
        }
        ECR;

        UNS8 mcm_reserved8[3];

        /* ECC Status Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:6;
                VUNS8 RNCE:1;
                VUNS8 FNCE:1;
            }
            B;
        }
        ESR;

        UNS16 ecsm_reserved9;

        /* ECC Error Generation Register */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16:6;
                VUNS16 FRCNCI:1;
                VUNS16 FR1NCI:1;
                VUNS16:1;
                VUNS16 ERRBIT:7;
            }
            B;
        }
        EEGR;

        UNS32 ecsm_reserved10;

        /* Flash ECC Address Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 FEAR:32;
            }
            B;
        }
        FEAR;

        UNS16 ecsm_reserved11;

        /* Flash ECC Master Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:4;
                VUNS8 FEMR:4;
            }
            B;
        }
        FEMR;

        /* Flash ECC Attributes Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8 WRITE:1;
                VUNS8 SIZE:3;
                VUNS8 PROT0:1;
                VUNS8 PROT1:1;
                VUNS8 PROT2:1;
                VUNS8 PROT3:1;
            }
            B;
        }
        FEAT;

        /* Flash ECC Data High Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 FEDH:32;
            }
            B;
        }
        FEDRH;

        /* Flash ECC Data Low Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 FEDL:32;
            }
            B;
        }
        FEDRL;

        /* RAM ECC Address */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 REAR:32;
            }
            B;
        }
        REAR;

        UNS8 ecsm_reserved12[2];

        /* RAM ECC Master */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:4;
                VUNS8 REMR:4;
            }
            B;
        }
        REMR;

        /* RAM ECC Attributes Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8 WRITE:1;
                VUNS8 SIZE:3;
                VUNS8 PROT0:1;
                VUNS8 PROT1:1;
                VUNS8 PROT2:1;
                VUNS8 PROT3:1;
            }
            B;
        }
        REAT;

        /* RAM ECC Data High Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 REDH:32;
            }
            B;
        }
        REDRH;

        /* RAMECC Data Low Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 REDL:32;
            }
            B;
        }
        REDRL;

    };

/***************************************************************/
/*                          MODULE : eDMA                                   */
/***************************************************************/
    struct EDMA_tag 
    {
        /* Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 GRP3PRI:2;
                VUNS32 GRP2PRI:2;
                VUNS32 GRP1PRI:2;
                VUNS32 GRP0PRI:2;
                VUNS32:4;
                VUNS32 ERGA:1;
                VUNS32 ERCA:1;
                VUNS32 EDBG:1;
                VUNS32 EBW:1;
            }
            B;
        }
        CR;

        /* Error Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 VLD:1;
                VUNS32:15;
                VUNS32 GPE:1;
                VUNS32 CPE:1;
                VUNS32 ERRCHN:6;
                VUNS32 SAE:1;
                VUNS32 SOE:1;
                VUNS32 DAE:1;
                VUNS32 DOE:1;
                VUNS32 NCE:1;
                VUNS32 SGE:1;
                VUNS32 SBE:1;
                VUNS32 DBE:1;
            }
            B;
        }
        ESR;

        /* DMA Enable Request Register High */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 ERQ63:1;
                VUNS32 ERQ62:1;
                VUNS32 ERQ61:1;
                VUNS32 ERQ60:1;
                VUNS32 ERQ59:1;
                VUNS32 ERQ58:1;
                VUNS32 ERQ57:1;
                VUNS32 ERQ56:1;
                VUNS32 ERQ55:1;
                VUNS32 ERQ54:1;
                VUNS32 ERQ53:1;
                VUNS32 ERQ52:1;
                VUNS32 ERQ51:1;
                VUNS32 ERQ50:1;
                VUNS32 ERQ49:1;
                VUNS32 ERQ48:1;
                VUNS32 ERQ47:1;
                VUNS32 ERQ46:1;
                VUNS32 ERQ45:1;
                VUNS32 ERQ44:1;
                VUNS32 ERQ43:1;
                VUNS32 ERQ42:1;
                VUNS32 ERQ41:1;
                VUNS32 ERQ40:1;
                VUNS32 ERQ39:1;
                VUNS32 ERQ38:1;
                VUNS32 ERQ37:1;
                VUNS32 ERQ36:1;
                VUNS32 ERQ35:1;
                VUNS32 ERQ34:1;
                VUNS32 ERQ33:1;
                VUNS32 ERQ32:1;
            }
            B;
        }
        ERQRH;

        /* DMA Enable Request Register Low */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 ERQ31:1;
                VUNS32 ERQ30:1;
                VUNS32 ERQ29:1;
                VUNS32 ERQ28:1;
                VUNS32 ERQ27:1;
                VUNS32 ERQ26:1;
                VUNS32 ERQ25:1;
                VUNS32 ERQ24:1;
                VUNS32 ERQ23:1;
                VUNS32 ERQ22:1;
                VUNS32 ERQ21:1;
                VUNS32 ERQ20:1;
                VUNS32 ERQ19:1;
                VUNS32 ERQ18:1;
                VUNS32 ERQ17:1;
                VUNS32 ERQ16:1;
                VUNS32 ERQ15:1;
                VUNS32 ERQ14:1;
                VUNS32 ERQ13:1;
                VUNS32 ERQ12:1;
                VUNS32 ERQ11:1;
                VUNS32 ERQ10:1;
                VUNS32 ERQ09:1;
                VUNS32 ERQ08:1;
                VUNS32 ERQ07:1;
                VUNS32 ERQ06:1;
                VUNS32 ERQ05:1;
                VUNS32 ERQ04:1;
                VUNS32 ERQ03:1;
                VUNS32 ERQ02:1;
                VUNS32 ERQ01:1;
                VUNS32 ERQ00:1;
            }
            B;
        }
        ERQRL;

        /* DMA Enable Error Interrupt Register High */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 EEI63:1;
                VUNS32 EEI62:1;
                VUNS32 EEI61:1;
                VUNS32 EEI60:1;
                VUNS32 EEI59:1;
                VUNS32 EEI58:1;
                VUNS32 EEI57:1;
                VUNS32 EEI56:1;
                VUNS32 EEI55:1;
                VUNS32 EEI54:1;
                VUNS32 EEI53:1;
                VUNS32 EEI52:1;
                VUNS32 EEI51:1;
                VUNS32 EEI50:1;
                VUNS32 EEI49:1;
                VUNS32 EEI48:1;
                VUNS32 EEI47:1;
                VUNS32 EEI46:1;
                VUNS32 EEI45:1;
                VUNS32 EEI44:1;
                VUNS32 EEI43:1;
                VUNS32 EEI42:1;
                VUNS32 EEI41:1;
                VUNS32 EEI40:1;
                VUNS32 EEI39:1;
                VUNS32 EEI38:1;
                VUNS32 EEI37:1;
                VUNS32 EEI36:1;
                VUNS32 EEI35:1;
                VUNS32 EEI34:1;
                VUNS32 EEI33:1;
                VUNS32 EEI32:1;
            }
            B;
        }
        EEIRH;

        /* DMA Enable Error Interrupt Register Low */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 EEI31:1;
                VUNS32 EEI30:1;
                VUNS32 EEI29:1;
                VUNS32 EEI28:1;
                VUNS32 EEI27:1;
                VUNS32 EEI26:1;
                VUNS32 EEI25:1;
                VUNS32 EEI24:1;
                VUNS32 EEI23:1;
                VUNS32 EEI22:1;
                VUNS32 EEI21:1;
                VUNS32 EEI20:1;
                VUNS32 EEI19:1;
                VUNS32 EEI18:1;
                VUNS32 EEI17:1;
                VUNS32 EEI16:1;
                VUNS32 EEI15:1;
                VUNS32 EEI14:1;
                VUNS32 EEI13:1;
                VUNS32 EEI12:1;
                VUNS32 EEI11:1;
                VUNS32 EEI10:1;
                VUNS32 EEI09:1;
                VUNS32 EEI08:1;
                VUNS32 EEI07:1;
                VUNS32 EEI06:1;
                VUNS32 EEI05:1;
                VUNS32 EEI04:1;
                VUNS32 EEI03:1;
                VUNS32 EEI02:1;
                VUNS32 EEI01:1;
                VUNS32 EEI00:1;
            }
            B;
        }
        EEIRL;

        /* DMA Set Enable Request Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        SERQR;

        /* DMA Clear Enable Request Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        CERQR;

        /* DMA Set Enable Error Interrupt Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        SEEIR;

        /* DMA Clear Enable Error Interrupt Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        CEEIR;

        /* DMA Clear Interrupt Request Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        CIRQR;

        /* DMA Clear error Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        CER;

        /* Set Start Bit Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        SSBR;

        /* Clear Done Status Bit Register */
        union 
        {
            VUNS8 R;
            VUNS8 B;
        }
        CDSBR;

        /* DMA Interrupt Request High */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 INT63:1;
                VUNS32 INT62:1;
                VUNS32 INT61:1;
                VUNS32 INT60:1;
                VUNS32 INT59:1;
                VUNS32 INT58:1;
                VUNS32 INT57:1;
                VUNS32 INT56:1;
                VUNS32 INT55:1;
                VUNS32 INT54:1;
                VUNS32 INT53:1;
                VUNS32 INT52:1;
                VUNS32 INT51:1;
                VUNS32 INT50:1;
                VUNS32 INT49:1;
                VUNS32 INT48:1;
                VUNS32 INT47:1;
                VUNS32 INT46:1;
                VUNS32 INT45:1;
                VUNS32 INT44:1;
                VUNS32 INT43:1;
                VUNS32 INT42:1;
                VUNS32 INT41:1;
                VUNS32 INT40:1;
                VUNS32 INT39:1;
                VUNS32 INT38:1;
                VUNS32 INT37:1;
                VUNS32 INT36:1;
                VUNS32 INT35:1;
                VUNS32 INT34:1;
                VUNS32 INT33:1;
                VUNS32 INT32:1;
            }
            B;
        }
        IRQRH;

        /* DMA Interrupt Request Low */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 INT31:1;
                VUNS32 INT30:1;
                VUNS32 INT29:1;
                VUNS32 INT28:1;
                VUNS32 INT27:1;
                VUNS32 INT26:1;
                VUNS32 INT25:1;
                VUNS32 INT24:1;
                VUNS32 INT23:1;
                VUNS32 INT22:1;
                VUNS32 INT21:1;
                VUNS32 INT20:1;
                VUNS32 INT19:1;
                VUNS32 INT18:1;
                VUNS32 INT17:1;
                VUNS32 INT16:1;
                VUNS32 INT15:1;
                VUNS32 INT14:1;
                VUNS32 INT13:1;
                VUNS32 INT12:1;
                VUNS32 INT11:1;
                VUNS32 INT10:1;
                VUNS32 INT09:1;
                VUNS32 INT08:1;
                VUNS32 INT07:1;
                VUNS32 INT06:1;
                VUNS32 INT05:1;
                VUNS32 INT04:1;
                VUNS32 INT03:1;
                VUNS32 INT02:1;
                VUNS32 INT01:1;
                VUNS32 INT00:1;
            }
            B;
        }
        IRQRL;

        /* DMA Error High */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 ERR63:1;
                VUNS32 ERR62:1;
                VUNS32 ERR61:1;
                VUNS32 ERR60:1;
                VUNS32 ERR59:1;
                VUNS32 ERR58:1;
                VUNS32 ERR57:1;
                VUNS32 ERR56:1;
                VUNS32 ERR55:1;
                VUNS32 ERR54:1;
                VUNS32 ERR53:1;
                VUNS32 ERR52:1;
                VUNS32 ERR51:1;
                VUNS32 ERR50:1;
                VUNS32 ERR49:1;
                VUNS32 ERR48:1;
                VUNS32 ERR47:1;
                VUNS32 ERR46:1;
                VUNS32 ERR45:1;
                VUNS32 ERR44:1;
                VUNS32 ERR43:1;
                VUNS32 ERR42:1;
                VUNS32 ERR41:1;
                VUNS32 ERR40:1;
                VUNS32 ERR39:1;
                VUNS32 ERR38:1;
                VUNS32 ERR37:1;
                VUNS32 ERR36:1;
                VUNS32 ERR35:1;
                VUNS32 ERR34:1;
                VUNS32 ERR33:1;
                VUNS32 ERR32:1;
            }
            B;
        }
        ERH;

        /* DMA Error Low */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 ERR31:1;
                VUNS32 ERR30:1;
                VUNS32 ERR29:1;
                VUNS32 ERR28:1;
                VUNS32 ERR27:1;
                VUNS32 ERR26:1;
                VUNS32 ERR25:1;
                VUNS32 ERR24:1;
                VUNS32 ERR23:1;
                VUNS32 ERR22:1;
                VUNS32 ERR21:1;
                VUNS32 ERR20:1;
                VUNS32 ERR19:1;
                VUNS32 ERR18:1;
                VUNS32 ERR17:1;
                VUNS32 ERR16:1;
                VUNS32 ERR15:1;
                VUNS32 ERR14:1;
                VUNS32 ERR13:1;
                VUNS32 ERR12:1;
                VUNS32 ERR11:1;
                VUNS32 ERR10:1;
                VUNS32 ERR09:1;
                VUNS32 ERR08:1;
                VUNS32 ERR07:1;
                VUNS32 ERR06:1;
                VUNS32 ERR05:1;
                VUNS32 ERR04:1;
                VUNS32 ERR03:1;
                VUNS32 ERR02:1;
                VUNS32 ERR01:1;
                VUNS32 ERR00:1;
            }
            B;
        }
        ERL;
        UNS32 edma_reserved1[52];

        /* Channel n Priority */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8 ECP:1;
                VUNS8:1;
                VUNS8 GRPPRI:2;
                VUNS8 CHPRI:4;

            }
            B;
        }
        CPR[64];

        UNS32 edma_reserved2[944];

/***************************************************************/
/*       DMA2 Transfer Control Descriptor                      */
/***************************************************************/

        /* transfer_control_descriptor */
        /*for "standard" format TCDs (when EDMA.TCD[x].CITER.E_LINK==BITER.E_LINK=0 && EDMA.EMLM=0 ) */
        struct tcd_t 
        {

            /* source address */
            VUNS32 SADDR;

            /* source address modulo */
            VUNS16 SMOD:5;

            /* source transfer size */
            VUNS16 SSIZE:3;

            /* destination address modulo */
            VUNS16 DMOD:5;

            /* destination transfer size */
            VUNS16 DSIZE:3;

            /* signed source address offset */
            VINT16 SOFF;

            /* inner (minor) byte count */
            VUNS32 NBYTES;

            /* last destination address adjustment, or scatter/gather address (if e_sg = 1) */
            VINT32 SLAST;

            /* destination address */
            VUNS32 DADDR;

            VUNS16 CITERE_LINK:1;
            VUNS16 CITER:15;

            /* signed destination address offset */
            VINT16 DOFF;

            VINT32 DLAST_SGA;

            /* beginning (major) iteration count */
            VUNS16 BITERE_LINK:1;

            VUNS16 BITER:15;

            /* bandwidth control */
            VUNS16 BWC:2;

            /* enable channel-to-channel link */
            VUNS16 MAJORLINKCH:6;

            /* channel done */
            VUNS16 DONE:1;

            /* channel active */
            VUNS16 ACTIVE:1;

            /* enable channel-to-channel link */
            VUNS16 MAJORE_LINK:1;

            /* enable scatter/gather descriptor */
            VUNS16 E_SG:1;

            /* disable ipd_req when done */
            VUNS16 D_REQ:1;

            /* interrupt on citer = (biter >> 1) */
            VUNS16 INT_HALF:1;

            /* interrupt on major loop completion */
            VUNS16 INT_MAJ:1;

            /* explicit channel start */
            VUNS16 START:1;
        }
        TCD[64];

    };

    /*for alternate format TCDs (when EDMA.TCD[x].CITER.E_LINK==BITER.E_LINK=1 ) */
    struct EDMA_TCD_alt1_tag 
    {

        /* transfer_control_descriptor */
        struct tcd_alt1_t 
        {
            /* source address */
            VUNS32 SADDR;

            /* source address modulo */
            VUNS16 SMOD:5;

            /* source transfer size */
            VUNS16 SSIZE:3;

            /* destination address modulo */
            VUNS16 DMOD:5;

            /* destination transfer size */
            VUNS16 DSIZE:3;

            /* signed source address offset */
            VINT16 SOFF;

            /* inner (minor) byte count */
            VUNS32 NBYTES;

            /* last destination address adjustment, or scatter/gather address (if e_sg = 1) */
            VINT32 SLAST;

            /* destination address */
            VUNS32 DADDR;

            VUNS16 CITERE_LINK:1;
            VUNS16 CITERLINKCH:6;
            VUNS16 CITER:9;

            /* signed destination address offset */
            VINT16 DOFF;

            VINT32 DLAST_SGA;

            /* beginning (major) iteration count */
            VUNS16 BITERE_LINK:1;

            VUNS16 BITERLINKCH:6;
            VUNS16 BITER:9;

            /* bandwidth control */
            VUNS16 BWC:2;

            /* enable channel-to-channel link */
            VUNS16 MAJORLINKCH:6;

            /* channel done */
            VUNS16 DONE:1;

            /* channel active */
            VUNS16 ACTIVE:1;

            /* enable channel-to-channel link */
            VUNS16 MAJORE_LINK:1;

            /* enable scatter/gather descriptor */
            VUNS16 E_SG:1;

            /* disable ipd_req when done */
            VUNS16 D_REQ:1;

            /* interrupt on citer = (biter >> 1) */
            VUNS16 INT_HALF:1;

            /* interrupt on major loop completion */
            VUNS16 INT_MAJ:1;

            /* explicit channel start */
            VUNS16 START:1;
        }
        TCD[64];
    };

/***************************************************************/
/*                          MODULE : INTC                      */
/***************************************************************/
    struct INTC_tag 
    {
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:26;
                VUNS32 VTES:1;
                VUNS32:4;
                VUNS32 HVEN:1;
            }
            B;
        }
        MCR;

        INT32 INTC_reserved00;

        /* Current Priority Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:28;
                VUNS32 PRI:4;
            }
            B;
        }
        CPR;

        UNS32 intc_reserved1;

        /* Interrupt Acknowledge Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 VTBA:21;
                VUNS32 INTVEC:9;
                VUNS32:2;
            }
            B;
        }
        IACKR;

        UNS32 intc_reserved2;

        /* End of Interrupt Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:32;
            }
            B;
        }
        EOIR;

        UNS32 intc_reserved3;

        /* Software Set/Clear Interrupt Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:6;
                VUNS8 SET:1;
                VUNS8 CLR:1;
            }
            B;
        }
        SSCIR[8];

        UNS32 intc_reserved4[6];

        /* Software Set/Clear Interrupt Register */
        union 
        {
            VUNS8 R;
            struct 
            {
                VUNS8:4;
                VUNS8 PRI:4;
            }
            B;
        }
        PSR[358];

    };

/***************************************************************/
/*                          MODULE : EQADC                                  */
/***************************************************************/
    struct EQADC_tag 
    {
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:27;
                VUNS32 ESSIE:2;
                VUNS32:1;
                VUNS32 DBG:2;
            }
            B;
        }
        MCR;

        INT32 EQADC_reserved00;

        /* Null Message Send Format Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:6;
                VUNS32 NMF:26;
            }
            B;
        }
        NMSFR;

        /* External Trigger Digital Filter Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:28;
                VUNS32 DFL:4;
            }
            B;
        }
        ETDFR;

        /* CFIFO Push Registers */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 CFPUSH:32;
            }
            B;
        }
        CFPR[6];

        UNS32 eqadc_reserved1;

        UNS32 eqadc_reserved2;

        /* Result FIFO Pop Registers */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 RFPOP:16;
            }
            B;
        }
        RFPR[6];

        UNS32 eqadc_reserved3;

        UNS32 eqadc_reserved4;

        /* CFIFO Control Registers */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16:5;
                VUNS16 SSE:1;
                VUNS16 CFINV:1;
                VUNS16:1;
                VUNS16 MODE:4;
                VUNS16:4;
            }
            B;
        }
        CFCR[6];

        UNS32 eqadc_reserved5;

        /* Interrupt and DMA Control Registers */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16 NCIE:1;
                VUNS16 TORIE:1;
                VUNS16 PIE:1;
                VUNS16 EOQIE:1;
                VUNS16 CFUIE:1;
                VUNS16:1;
                VUNS16 CFFE:1;
                VUNS16 CFFS:1;
                VUNS16:4;
                VUNS16 RFOIE:1;
                VUNS16:1;
                VUNS16 RFDE:1;
                VUNS16 RFDS:1;
            }
            B;
        }
        IDCR[6];

        UNS32 eqadc_reserved6;

        /* FIFO and Interrupt Status Registers */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 NCF:1;
                VUNS32 TORF:1;
                VUNS32 PF:1;
                VUNS32 EOQF:1;
                VUNS32 CFUF:1;
                VUNS32 SSS:1;
                VUNS32 CFFF:1;
                VUNS32:5;
                VUNS32 RFOF:1;
                VUNS32:1;
                VUNS32 RFDF:1;
                VUNS32:1;
                VUNS32 CFCTR:4;
                VUNS32 TNXTPTR:4;
                VUNS32 RFCTR:4;
                VUNS32 POPNXTPTR:4;
            }
            B;
        }
        FISR[6];

        UNS32 eqadc_reserved7;

        UNS32 eqadc_reserved8;

        /* CFIFO Transfer Counter Registers */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16:5;
                VUNS16 TCCF:11;
            }
            B;
        }
        CFTCR[6];

        UNS32 eqadc_reserved9;

        /* CFIFO Status Register 0 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 CFS0:2;
                VUNS32 CFS1:2;
                VUNS32 CFS2:2;
                VUNS32 CFS3:2;
                VUNS32 CFS4:2;
                VUNS32 CFS5:2;
                VUNS32:5;
                VUNS32 LCFTCB0:4;
                VUNS32 TC_LCFTCB0:11;
            }
            B;
        }
        CFSSR0;

        /* CFIFO Status Register 1 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 CFS0:2;
                VUNS32 CFS1:2;
                VUNS32 CFS2:2;
                VUNS32 CFS3:2;
                VUNS32 CFS4:2;
                VUNS32 CFS5:2;
                VUNS32:5;
                VUNS32 LCFTCB1:4;
                VUNS32 TC_LCFTCB1:11;
            }
            B;
        }
        CFSSR1;

        /* CFIFO Status Register 2 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 CFS0:2;
                VUNS32 CFS1:2;
                VUNS32 CFS2:2;
                VUNS32 CFS3:2;
                VUNS32 CFS4:2;
                VUNS32 CFS5:2;
                VUNS32:4;
                VUNS32 ECBNI:1;
                VUNS32 LCFTSSI:4;
                VUNS32 TC_LCFTSSI:11;
            }
            B;
        }
        CFSSR2;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 CFS0:2;
                VUNS32 CFS1:2;
                VUNS32 CFS2:2;
                VUNS32 CFS3:2;
                VUNS32 CFS4:2;
                VUNS32 CFS5:2;
                VUNS32:20;
            }
            B;
        }
        CFSR;

        UNS32 eqadc_reserved11;

        /* SSI Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:21;
                VUNS32 MDT:3;
                VUNS32:4;
                VUNS32 BR:4;
            }
            B;
        }
        SSICR;

        /* SSI Recieve Data Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 RDV:1;
                VUNS32:5;
                VUNS32 RDATA:26;
            }
            B;
        }
        SSIRDR;

        UNS32 eqadc_reserved12[17];

        struct 
        {
            union 
            {
                VUNS32 R;
                struct 
                {
                    VUNS32:32;
                }
                B;
            }
            R[4];

            UNS32 eqadc_reserved13[12];

        }
        CF[6];

        UNS32 eqadc_reserved14[32];

        struct 
        {
            union 
            {
                VUNS32 R;
                struct 
                {
                    VUNS32:32;
                }
                B;
            }
            R[4];

            UNS32 eqadc_reserved15[12];

        }
        RF[6];

    };

/***************************************************************/
/*                          MODULE : DSPI                                   */
/***************************************************************/
    struct DSPI_tag 
    {
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 MSTR:1;
                VUNS32 CONT_SCKE:1;
                VUNS32 DCONF:2;
                VUNS32 FRZ:1;
                VUNS32 MTFE:1;
                VUNS32 PCSSE:1;
                VUNS32 ROOE:1;
                VUNS32:2;
                VUNS32 PCSIS5:1;
                VUNS32 PCSIS4:1;
                VUNS32 PCSIS3:1;
                VUNS32 PCSIS2:1;
                VUNS32 PCSIS1:1;
                VUNS32 PCSIS0:1;
                VUNS32 DOZE:1;
                VUNS32 MDIS:1;
                VUNS32 DIS_TXF:1;
                VUNS32 DIS_RXF:1;
                VUNS32 CLR_TXF:1;
                VUNS32 CLR_RXF:1;
                VUNS32 SMPL_PT:2;
                VUNS32:7;
                VUNS32 HALT:1;
            }
            B;
        }
        MCR;

        UNS32 dspi_reserved1;

        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 TCNT:16;
                VUNS32:16;
            }
            B;
        }
        TCR;

        /* Clock and Transfer Attributes Registers */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 DBR:1;
                VUNS32 FMSZ:4;
                VUNS32 CPOL:1;
                VUNS32 CPHA:1;
                VUNS32 LSBFE:1;
                VUNS32 PCSSCK:2;
                VUNS32 PASC:2;
                VUNS32 PDT:2;
                VUNS32 PBR:2;
                VUNS32 CSSCK:4;
                VUNS32 ASC:4;
                VUNS32 DT:4;
                VUNS32 BR:4;
            }
            B;
        }
        CTAR[8];

        /* Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 TCF:1;
                VUNS32 TXRXS:1;
                VUNS32:1;
                VUNS32 EOQF:1;
                VUNS32 TFUF:1;
                VUNS32:1;
                VUNS32 TFFF:1;
                VUNS32:5;
                VUNS32 RFOF:1;
                VUNS32:1;
                VUNS32 RFDF:1;
                VUNS32:1;
                VUNS32 TXCTR:4;
                VUNS32 TXNXTPTR:4;
                VUNS32 RXCTR:4;
                VUNS32 POPNXTPTR:4;
            }
            B;
        }
        SR;

        /* DMA/Interrupt Request Select and Enable Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 TCFRE:1;
                VUNS32:2;
                VUNS32 EOQFRE:1;
                VUNS32 TFUFRE:1;
                VUNS32:1;
                VUNS32 TFFFRE:1;
                VUNS32 TFFFDIRS:1;
                VUNS32:4;
                VUNS32 RFOFRE:1;
                VUNS32:1;
                VUNS32 RFDFRE:1;
                VUNS32 RFDFDIRS:1;
                VUNS32:16;
            }
            B;
        }
        RSER;

        /* PUSH TX FIFO Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 CONT:1;
                VUNS32 CTAS:3;
                VUNS32 EOQ:1;
                VUNS32 CTCNT:1;
                VUNS32:4;
                VUNS32 PCS5:1;
                VUNS32 PCS4:1;
                VUNS32 PCS3:1;
                VUNS32 PCS2:1;
                VUNS32 PCS1:1;
                VUNS32 PCS0:1;
                VUNS32 TXDATA:16;
            }
            B;
        }
        PUSHR;

        /* POP RX FIFO Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 RXDATA:16;
            }
            B;
        }
        POPR;

        /* Transmit FIFO Registers */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 TXCMD:16;
                VUNS32 TXDATA:16;
            }
            B;
        }
        TXFR[4];

        VUNS32 DSPI_reserved_txf[12];

        /* Transmit FIFO Registers */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 RXDATA:16;
            }
            B;
        }
        RXFR[4];

        VUNS32 DSPI_reserved_rxf[12];

        /* DSI Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 MTOE:1;
                VUNS32:1;
                VUNS32 MTOCNT:6;
                VUNS32:4;
                VUNS32 TXSS:1;
                VUNS32 TPOL:1;
                VUNS32 TRRE:1;
                VUNS32 CID:1;
                VUNS32 DCONT:1;
                VUNS32 DSICTAS:3;
                VUNS32:6;
                VUNS32 DPCS5:1;
                VUNS32 DPCS4:1;
                VUNS32 DPCS3:1;
                VUNS32 DPCS2:1;
                VUNS32 DPCS1:1;
                VUNS32 DPCS0:1;
            }
            B;
        }
        DSICR;

        /* DSI Serialization Data Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 SER_DATA:16;
            }
            B;
        }
        SDR;

        /* DSI Alternate Serialization Data Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 ASER_DATA:16;
            }
            B;
        }
        ASDR;

        /* DSI Transmit Comparison Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 COMP_DATA:16;
            }
            B;
        }
        COMPR;

        /* DSI deserialization Data Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 DESER_DATA:16;
            }
            B;
        }
        DDR;

    };

/***************************************************************/
/*                          MODULE : eSCI                                   */
/***************************************************************/
    struct ESCI_tag 
    {
        /* Control Register 1 */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:3;
                VUNS32 SBR:13;
                VUNS32 LOOPS:1;
                VUNS32 SCISDOZ:1;
                VUNS32 RSRC:1;
                VUNS32 M:1;
                VUNS32 WAKE:1;
                VUNS32 ILT:1;
                VUNS32 PE:1;
                VUNS32 PT:1;
                VUNS32 TIE:1;
                VUNS32 TCIE:1;
                VUNS32 RIE:1;
                VUNS32 ILIE:1;
                VUNS32 TE:1;
                VUNS32 RE:1;
                VUNS32 RWU:1;
                VUNS32 SBK:1;
            }
            B;
        }
        CR1;

        /* Control Register 2 */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16 MDIS:1;
                VUNS16 FBR:1;
                VUNS16 BSTP:1;
                VUNS16 IEBERR:1;
                VUNS16 RXDMA:1;
                VUNS16 TXDMA:1;
                VUNS16 BRK13:1;
                VUNS16:1;
                VUNS16 BESM13:1;
                VUNS16 SBSTP:1;
                VUNS16:2;
                VUNS16 ORIE:1;
                VUNS16 NFIE:1;
                VUNS16 FEIE:1;
                VUNS16 PFIE:1;
            }
            B;
        }
        CR2;

        /* Data Register */
        union 
        {
            VUNS16 R;
            struct 
            {
                VUNS16 R8:1;
                VUNS16 T8:1;
                VUNS16:6;
                VUNS8 D;
            }
            B;
        }
        DR;

        /* Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 TDRE:1;
                VUNS32 TC:1;
                VUNS32 RDRF:1;
                VUNS32 IDLE:1;
                VUNS32 OR:1;
                VUNS32 NF:1;
                VUNS32 FE:1;
                VUNS32 PF:1;
                VUNS32:3;
                VUNS32 BERR:1;
                VUNS32:3;
                VUNS32 RAF:1;
                VUNS32 RXRDY:1;
                VUNS32 TXRDY:1;
                VUNS32 LWAKE:1;
                VUNS32 STO:1;
                VUNS32 PBERR:1;
                VUNS32 CERR:1;
                VUNS32 CKERR:1;
                VUNS32 FRC:1;
                VUNS32:7;
                VUNS32 OVFL:1;
            }
            B;
        }
        SR;

        /* LIN Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 LRES:1;
                VUNS32 WU:1;
                VUNS32 WUD0:1;
                VUNS32 WUD1:1;
                VUNS32 LDBG:1;
                VUNS32 DSF:1;
                VUNS32 PRTY:1;
                VUNS32 LIN:1;
                VUNS32 RXIE:1;
                VUNS32 TXIE:1;
                VUNS32 WUIE:1;
                VUNS32 STIE:1;
                VUNS32 PBIE:1;
                VUNS32 CIE:1;
                VUNS32 CKIE:1;
                VUNS32 FCIE:1;
                VUNS32:7;
                VUNS32 OFIE:1;
                VUNS32:8;
            }
            B;
        }
        LCR;

        /* LIN Transmit Register */
        union 
        {
            VUNS32 R;
        }
        LTR;

        /* LIN Recieve Register */
        union 
        {
            VUNS32 R;
        }
        LRR;

        /* LIN CRC Polynom Register  */
        union 
        {
            VUNS32 R;
        }
        LPR;

    };

/***************************************************************/
/*                          MODULE : FlexCAN                                */
/***************************************************************/
typedef struct  
{
        /* Module Configuration Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 MDIS:1;
                VUNS32 FRZ:1;
                VUNS32:1;
                VUNS32 HALT:1;
                VUNS32 NOTRDY:1;
                VUNS32:1;
                VUNS32 SOFTRST:1;
                VUNS32 FRZACK:1;
                VUNS32:1;
                VUNS32:1;
                VUNS32:1;
                VUNS32 MDISACK:1;
                VUNS32:1;
                VUNS32:1;
                VUNS32:12;
                VUNS32 MAXMB:6;
            }
            B;
        }
        MCR;

        /* Control Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 PRESDIV:8;
                VUNS32 RJW:2;
                VUNS32 PSEG1:3;
                VUNS32 PSEG2:3;
                VUNS32 BOFFMSK:1;
                VUNS32 ERRMSK:1;
                VUNS32 CLKSRC:1;
                VUNS32 LPB:1;
                VUNS32:4;
                VUNS32 SMP:1;
                VUNS32 BOFFREC:1;
                VUNS32 TSYN:1;
                VUNS32 LBUF:1;
                VUNS32 LOM:1;
                VUNS32 PROPSEG:3;
            }
            B;
        }
        CR;

        /* Free Running Timer */
        union 
        {
            VUNS32 R;
        }
        TIMER;
        INT32 FLEXCAN_reserved00;

        /* RX Global Mask */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:3;
                VUNS32 MI:29;
            }
            B;
        }
        RXGMASK;

        /* RX 14 Mask */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:3;
                VUNS32 MI:29;
            }
            B;
        }
        RX14MASK;

        /* RX 15 Mask */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:3;
                VUNS32 MI:29;
            }
            B;
        }
        RX15MASK;

        /* Error Counter Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:16;
                VUNS32 RXECNT:8;
                VUNS32 TXECNT:8;
            }
            B;
        }
        ECR;

        /* Error and Status Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32:14;

                VUNS32:2;

                VUNS32 BIT1ERR:1;
                VUNS32 BIT0ERR:1;
                VUNS32 ACKERR:1;
                VUNS32 CRCERR:1;
                VUNS32 FRMERR:1;
                VUNS32 STFERR:1;
                VUNS32 TXWRN:1;
                VUNS32 RXWRN:1;
                VUNS32 IDLE:1;
                VUNS32 TXRX:1;
                VUNS32 FLTCONF:2;
                VUNS32:1;
                VUNS32 BOFFINT:1;
                VUNS32 ERRINT:1;
                VUNS32:1;
            }
            B;
        }
        ESR;

        /* Interrupt Masks Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BUF63M:1;
                VUNS32 BUF62M:1;
                VUNS32 BUF61M:1;
                VUNS32 BUF60M:1;
                VUNS32 BUF59M:1;
                VUNS32 BUF58M:1;
                VUNS32 BUF57M:1;
                VUNS32 BUF56M:1;
                VUNS32 BUF55M:1;
                VUNS32 BUF54M:1;
                VUNS32 BUF53M:1;
                VUNS32 BUF52M:1;
                VUNS32 BUF51M:1;
                VUNS32 BUF50M:1;
                VUNS32 BUF49M:1;
                VUNS32 BUF48M:1;
                VUNS32 BUF47M:1;
                VUNS32 BUF46M:1;
                VUNS32 BUF45M:1;
                VUNS32 BUF44M:1;
                VUNS32 BUF43M:1;
                VUNS32 BUF42M:1;
                VUNS32 BUF41M:1;
                VUNS32 BUF40M:1;
                VUNS32 BUF39M:1;
                VUNS32 BUF38M:1;
                VUNS32 BUF37M:1;
                VUNS32 BUF36M:1;
                VUNS32 BUF35M:1;
                VUNS32 BUF34M:1;
                VUNS32 BUF33M:1;
                VUNS32 BUF32M:1;
            }
            B;
        }
        IMRH;

        /* Interrupt Masks Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BUF31M:1;
                VUNS32 BUF30M:1;
                VUNS32 BUF29M:1;
                VUNS32 BUF28M:1;
                VUNS32 BUF27M:1;
                VUNS32 BUF26M:1;
                VUNS32 BUF25M:1;
                VUNS32 BUF24M:1;
                VUNS32 BUF23M:1;
                VUNS32 BUF22M:1;
                VUNS32 BUF21M:1;
                VUNS32 BUF20M:1;
                VUNS32 BUF19M:1;
                VUNS32 BUF18M:1;
                VUNS32 BUF17M:1;
                VUNS32 BUF16M:1;
                VUNS32 BUF15M:1;
                VUNS32 BUF14M:1;
                VUNS32 BUF13M:1;
                VUNS32 BUF12M:1;
                VUNS32 BUF11M:1;
                VUNS32 BUF10M:1;
                VUNS32 BUF09M:1;
                VUNS32 BUF08M:1;
                VUNS32 BUF07M:1;
                VUNS32 BUF06M:1;
                VUNS32 BUF05M:1;
                VUNS32 BUF04M:1;
                VUNS32 BUF03M:1;
                VUNS32 BUF02M:1;
                VUNS32 BUF01M:1;
                VUNS32 BUF00M:1;
            }
            B;
        }
        IMRL;

        /* Interrupt Flag Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BUF63I:1;
                VUNS32 BUF62I:1;
                VUNS32 BUF61I:1;
                VUNS32 BUF60I:1;
                VUNS32 BUF59I:1;
                VUNS32 BUF58I:1;
                VUNS32 BUF57I:1;
                VUNS32 BUF56I:1;
                VUNS32 BUF55I:1;
                VUNS32 BUF54I:1;
                VUNS32 BUF53I:1;
                VUNS32 BUF52I:1;
                VUNS32 BUF51I:1;
                VUNS32 BUF50I:1;
                VUNS32 BUF49I:1;
                VUNS32 BUF48I:1;
                VUNS32 BUF47I:1;
                VUNS32 BUF46I:1;
                VUNS32 BUF45I:1;
                VUNS32 BUF44I:1;
                VUNS32 BUF43I:1;
                VUNS32 BUF42I:1;
                VUNS32 BUF41I:1;
                VUNS32 BUF40I:1;
                VUNS32 BUF39I:1;
                VUNS32 BUF38I:1;
                VUNS32 BUF37I:1;
                VUNS32 BUF36I:1;
                VUNS32 BUF35I:1;
                VUNS32 BUF34I:1;
                VUNS32 BUF33I:1;
                VUNS32 BUF32I:1;
            }
            B;
        }
        IFRH;

        /* Interrupt Flag Register */
        union 
        {
            VUNS32 R;
            struct 
            {
                VUNS32 BUF31I:1;
                VUNS32 BUF30I:1;
                VUNS32 BUF29I:1;
                VUNS32 BUF28I:1;
                VUNS32 BUF27I:1;
                VUNS32 BUF26I:1;
                VUNS32 BUF25I:1;
                VUNS32 BUF24I:1;
                VUNS32 BUF23I:1;
                VUNS32 BUF22I:1;
                VUNS32 BUF21I:1;
                VUNS32 BUF20I:1;
                VUNS32 BUF19I:1;
                VUNS32 BUF18I:1;
                VUNS32 BUF17I:1;
                VUNS32 BUF16I:1;
                VUNS32 BUF15I:1;
                VUNS32 BUF14I:1;
                VUNS32 BUF13I:1;
                VUNS32 BUF12I:1;
                VUNS32 BUF11I:1;
                VUNS32 BUF10I:1;
                VUNS32 BUF09I:1;
                VUNS32 BUF08I:1;
                VUNS32 BUF07I:1;
                VUNS32 BUF06I:1;
                VUNS32 BUF05I:1;
                VUNS32 BUF04I:1;
                VUNS32 BUF03I:1;
                VUNS32 BUF02I:1;
                VUNS32 BUF01I:1;
                VUNS32 BUF00I:1;
            }
            B;
        }
        IFRL;

        UNS32 flexcan2_reserved2[19];

        struct canbuf_t 
        {
            union 
            {
                VUNS32 R;
                struct 
                {
                    VUNS32:4;
                    VUNS32 CODE:4;
                    VUNS32:1;
                    VUNS32 SRR:1;
                    VUNS32 IDE:1;
                    VUNS32 RTR:1;
                    VUNS32 LENGTH:4;
                    VUNS32 TIMESTAMP:16;
                }
                B;
            }
            CS;

            union 
            {
                VUNS32 R;
                struct 
                {
                    VUNS32:3;
                    VUNS32 STD_ID:11;
                    VUNS32 EXT_ID:18;
                }
                B;
            }
            ID;

            union 
            {
                /* Data buffer in Bytes (8 bits) */
                VUNS8 B[8];

                /* Data buffer in Half-words (16 bits) */
                VUNS16 H[4];

                /* Data buffer in words (32 bits) */
                VUNS32 W[2];

                /* Data buffer in words (32 bits) */
                VUNS32 R[2];
            }
            DATA;

        }
        BUF[64];
    }
    T_FLEXCAN2_tag;

    
    
/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* Define memories */
#define SRAM_START  (UNS32)0x40000000
#define SRAM_SIZE   (UNS32)0x10000
#define SRAM_END    (UNS32)0x4000FFFF

#define FLASH_START    (UNS32)0x0
#define FLASH_SIZE     (UNS32)0x200000
#define FLASH_END      (UNS32)0x1FFFFF


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
/* Define instances of modules */
#define PBRIDGE_A (*( volatile struct PBRIDGE_A_tag *) 0xC3F00000)
#define FMPLL     (*( volatile struct FMPLL_tag *)     0xC3F80000)
#define EBI       (*( volatile struct EBI_tag *)       0xC3F84000)
#define FLASH     (*( volatile struct FLASH_tag *)     0xC3F88000)
#define SIU       (*( volatile struct SIU_tag *)       0xC3F90000)

#define EMIOS     (*( volatile struct EMIOS_tag *)     0xC3FA0000)
#define ETPU      (*( volatile struct ETPU_tag *)      0xC3FC0000)

#define PBRIDGE_B (*( volatile struct PBRIDGE_B_tag *) 0xFFF00000)
#define XBAR      (*( volatile struct XBAR_tag *)      0xFFF04000)
#define ECSM      (*( volatile struct ECSM_tag *)      0xFFF40000)
#define EDMA      (*( volatile struct EDMA_tag *)      0xFFF44000)
#define INTC      (*( volatile struct INTC_tag *)      0xFFF48000)

#define EQADC     (*( volatile struct EQADC_tag *)     0xFFF80000)

#define DSPI_A    (*( volatile struct DSPI_tag *)      0xFFF90000)
#define DSPI_B    (*( volatile struct DSPI_tag *)      0xFFF94000)
#define DSPI_C    (*( volatile struct DSPI_tag *)      0xFFF98000)
#define DSPI_D    (*( volatile struct DSPI_tag *)      0xFFF9C000)

#define ESCI_A    (*( volatile struct ESCI_tag *)      0xFFFB0000)
#define ESCI_B    (*( volatile struct ESCI_tag *)      0xFFFB4000)

#define CAN_A     (*( volatile T_FLEXCAN2_tag *)       0xFFFC0000)
#define CAN_B     (*( volatile T_FLEXCAN2_tag *)       0xFFFC4000)
#define CAN_C     (*( volatile T_FLEXCAN2_tag *)       0xFFFC8000)


/***************************************************************/
/*                                                             */
/*                       GLOBAL FUNCTIONS                      */
/*                                                             */
/***************************************************************/
#endif
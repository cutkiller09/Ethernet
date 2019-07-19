/*****************************************************************************/
/* INCLUDE HEADER                                                            */
/*****************************************************************************/
/*
  MODULE:      DataCoupling
  PROJECT:     

  DESCRIPTION: 
  This module defines the unique identifiers that are used
  for the object validity check (data coupling).

  Copyright (C) by Liebherr-Aerospace Lindenberg GmbH
******************************************************************************/

#ifndef __DATACOUPLING_H__  /* test for multiple inclusion */
#define __DATACOUPLING_H__

/*****************************************************************************/
/* INCLUDES                                                                  */
/*****************************************************************************/

/* ---- From supplier classes / modules ------------------------------------ */
#include "standard.h"

/* ---- From sub-classes --------------------------------------------------- */

/*****************************************************************************/
/* CLASSES / STRUCTURES / TYPES / DEFINES                                    */
/*****************************************************************************/

/* ---- DEFINEs from <<embedded>> classes ---------------------------------- */

/* ---- Basic Types -------------------------------------------------------- */

/* ---- Embedded Classes --------------------------------------------------- */
/* [Code-7FFF81D3-DataCoupling::DummyStruct] */
/* [Covers: ] */
typedef struct DummyStruct_tag
{
    UNS32   lIdTag;
} DummyStruct_t;

/* [Code-6992C4A5-DataCoupling::IdTagValue] */
/* [Covers: ] */
typedef enum IdTagValue_tag
{
    TAG_INVALID_E                 = 0xA55A0000U,
    TAG_DRVHANDLERCFG_E           = 0xA55A0001U,
    TAG_PARTITION_ENTRY_TABLE_E   = 0xA55A0002U,
    TAG_GPIO_INSTANCE_E           = 0xA55A1000U,
    TAG_GPIO_IO_CFG_E             = 0xA55A1001U,
    TAG_GPIO_HW_ENTRY_CFG_E       = 0xA55A1002U,
    TAG_ESCI_INSTANCE_E           = 0xA55A1100U,
    TAG_ESCI_IO_CFG_E             = 0xA55A1101U,
    TAG_ESCI_CONTROL_DATA_E       = 0xA55A1102U,
    TAG_FLEXCAN_INSTANCE_E        = 0xA55A1200U,
    TAG_FLEXCAN_IO_CFG_E          = 0xA55A1201U,
    TAG_FLEXCAN_HW_ENTRY_CFG_E    = 0xA55A1202U,
    TAG_MULTICAN_INSTANCE_E       = 0xA55A1210U,
    TAG_MULTICAN_IO_CFG_E         = 0xA55A1211U,
    TAG_MULTICAN_HW_ENTRY_CFG_E   = 0xA55A1212U,
    TAG_DSPI_INSTANCE_E           = 0xA55A1300U,
    TAG_DSPI_IO_CFG_E             = 0xA55A1301U,
    TAG_DSPI_HW_ENTRY_CFG_E       = 0xA55A1302U,
    TAG_FLASH_INSTANCE_E          = 0xA55A1400U,
    TAG_FLASH_IO_CFG_E            = 0xA55A1401U,
    TAG_FLASH_HW_ENTRY_CFG_E      = 0xA55A1402U,
    TAG_FLASH_CONTROL_DATA_E      = 0xA55A1403U,
    TAG_M95256W_INSTANCE_E        = 0xA55A1500U,
    TAG_M95256W_IO_CFG_E          = 0xA55A1501U,
    TAG_M95256W_HW_ENTRY_CFG_E    = 0xA55A1502U,
    TAG_M95256W_CONTROL_DATA_E    = 0xA55A1503U,
    TAG_LANCONTROL_E              = 0xA55A1600U,
    TAG_LAN9250_INSTANCE_E        = 0xA55A1610U,
    TAG_LAN9250_IO_CFG_E          = 0xA55A1611U,
    TAG_LAN9250_HW_ENTRY_CFG_E    = 0xA55A1612U,
    TAG_LAN9250_CONTROL_DATA_E    = 0xA55A1613U,
    TAG_KSZ8851_INSTANCE_E        = 0xA55A1620U,
    TAG_KSZ8851_IO_CFG_E          = 0xA55A1621U,
    TAG_KSZ8851_CONTROL_DATA_E    = 0xA55A1622U,
    TAG_GIO_INSTANCE_E            = 0xA55A1700U,
    TAG_GIO_IO_CFG_E              = 0xA55A1701U,
    TAG_GIO_HW_ENTRY_CFG_E        = 0xA55A1702U,
    TAG_SCI_INSTANCE_E            = 0xA55A1800U,
    TAG_SCI_IO_CFG_E              = 0xA55A1801U,
    TAG_MIBSPI_INSTANCE_E         = 0xA55A1900U,
    TAG_MIBSPI_IO_CFG_E           = 0xA55A1901U,
    TAG_MIBSPI_HW_ENTRY_CFG_E     = 0xA55A1902U,
    TAG_DCAN_INSTANCE_E           = 0xA55A1A00U,
    TAG_DCAN_IO_CFG_E             = 0xA55A1A01U,
    TAG_DCAN_HW_ENTRY_CFG_E       = 0xA55A1A02U,
    TAG_MIBADC_INSTANCE_E         = 0xA55A1B00U,
    TAG_MIBADC_IO_CFG_E           = 0xA55A1B01U,
    TAG_MIBADC_HW_ENTRY_CFG_E     = 0xA55A1B02U,
    TAG_EMAC_INSTANCE_E           = 0xA55A1C00U,
    TAG_EMAC_IO_CFG_E             = 0xA55A1C01U,
    TAG_EMAC_CONTROL_DATA_E       = 0xA55A1C02U,
    TAG_HMBASIC_INSTANCE_E        = 0xA55A1D00U,
    TAG_HMBASIC_IO_CFG_E          = 0xA55A1D01U,
    TAG_HMTAGDATA_INSTANCE_E      = 0xA55A1D02U,
    TAG_HMTAGDATA_IO_CFG_E        = 0xA55A1D03U,
    TAG_ROUTER_CFG_E              = 0xA55A2001U,
    TAG_LDR_LOADER_CFG_E          = 0xA55A3001U,
    TAG_LDR_MODULE_CFG_E          = 0xA55A3010U,
    TAG_LDR_HWIDENT_CFG_E         = 0xA55A3011U,
    TAG_LDR_SECTIONS_CFG_E        = 0xA55A3020U,
    TAG_LDR_SECTION_ENTRY_CFG_E   = 0xA55A3021U,
    TAG_LDR_DRV_CFG_E             = 0xA55A3030U,
    TAG_LDR_DRV_ENTRY_CFG_E       = 0xA55A3031U,
    TAG_MEMACCESS_INSTANCE_E      = 0xA55A9970U,
    TAG_MEMACCESS_IO_CFG_E        = 0xA55A9971U,
    TAG_MEMACCESS_HW_ENTRY_CFG_E  = 0xA55A9972U,
    TAG_UAFDX_INSTANCE_E          = 0xA55A9980U,
    TAG_UAFDX_IO_CFG_E            = 0xA55A9981U,
    TAG_UAFDX_RX_PORT_CFG_E       = 0xA55A9982U,
    TAG_UAFDX_TX_PORT_CFG_E       = 0xA55A9983U,
    TAG_TTP_INSTANCE_E            = 0xA55A9990U,
    TAG_TTP_IO_CFG_E              = 0xA55A9991U,
    TAG_TTP_CONTROLPARAM_E        = 0xA55A9992U,
    TAG_MR25H40SPI_INSTANCE_E     = 0xA55A9960U,
    TAG_MR25H40SPI_IO_CFG_E       = 0xA55A9961U,
    TAG_MR25H40SPI_HW_ENTRY_CFG_E = 0xA55A9962U,
    TAG_LOGBOOK_INSTANCE_E        = 0xA55A1D00U,
    TAG_LOGBOOK_IO_CFG_E          = 0xA55A1D01U,
    TAG_DEACTIVATED_E             = 0xA55A9999U
} IdTagValue_t;


/* ---- Master Class ------------------------------------------------------- */

/*****************************************************************************/
/* OBJECTS / INSTANCES OF CLASSES (supplied by the class)                    */
/*****************************************************************************/

/*****************************************************************************/
/* OPERATION PROTOTYPES                                                      */
/*****************************************************************************/
#endif /*__DATACOUPLING_H__*/

/* EOF */


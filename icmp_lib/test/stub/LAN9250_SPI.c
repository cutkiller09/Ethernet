/*****************************************************************************/
/* MODULE HEADER                                                             */
/*****************************************************************************/
/*
  MODULE:      
  PROJECT:   F6X  

  DESCRIPTION:
  This module implements SPI Communication Operations between MPC5554 and LAN9250.

  Copyright (C) by Liebherr-Aerospace Toulouse SAS
******************************************************************************/
#include "standard.h"
#include "cpu_def.h"
#include "LAN9250_SPI.h"

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/

UNS32 a_read_input;

/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/*SPI Instruction */
#define READ_INSTRUCTION            (UNS8)0x03
#define WRITE_INSTRUCTION           (UNS8)0x02
#define LAN9250_INIT_CMD_SIZE       (UNS8)7
#define DSPI_TX_FIFO_EMPTY          (UNS8)0
#define DSPI_TX_FIFO_SIZE           (UNS8)4
/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
UNS32 i=0;

/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Global function :ReadRegistersLAN9250_new framesize 8 bits	   */
/* RX FIFO has only 4 entries				                   */                  
/***************************************************************/
void ReadRegistersLAN9250(UNS16 address_register, UNS32* a_read_input_PTR)
{ 
    *a_read_input_PTR = i++;
}

/***************************************************************/
/* Global function : WriteRegistersLAN9250                     */
/* TX FIFO has only 4 entries                                  */
/***************************************************************/
void WriteRegistersLAN9250(UNS16 address_register, UNS32 value_towrite)
{ 

}

/***************************************************************/
/* Global function : ClearRegistersBits                        */
/***************************************************************/
void ClearLAN9250RegistersBits(UNS16 address_register, UNS8 bit_number)
{ 

}

/***************************************************************/
/* Global function : SetRegistersBits                          */
/***************************************************************/
void SetLAN9250RegistersBits(UNS16 address_register, UNS8 bit_number)
{ 

}


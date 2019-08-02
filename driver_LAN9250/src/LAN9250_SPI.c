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
    volatile UNS16 dummy_read;
    UNS16 input_byte1;
    UNS16 input_byte2;
    UNS16 input_byte3;
	UNS16 input_byte4;
	UNS8 i;
	UNS16 address_register_H;
    UNS16 address_register_L;
	
	/**********************************************************/
    /* Program the SPI in order to dialog with the LAN9250    */
	/* Frame size: 8 bits 				  					  */
    /* 1st command word :                                     */
    /*             CONT     = 1                               */
    /*             CTAS     = 0                               */
    /*             EOQ      = 0                               */
    /*             CTCNT    = 1 (only for the first cmd)      */
    /*             PCS0     = 1                               */
    /*             TXDATA   = 0x03             			 	  */
    /* 2nd command word - TXDATA   =                    	  */
    /* 3rd command word - TXDATA   =                    	  */
	/* 4th command word - TXDATA   =              	  		  */
	/* 5th command word - TXDATA   =              	  		  */
	/* 6th command word - TXDATA   =              	  		  */
	/* 7th command word - TXDATA   =              	  		  */
	/* (CONT = 0, EOQ = 1) for 7th command word               */
    /**********************************************************/    
    UNS32 LAN9250_read_cmd[7] =
    {
        /* Read commands */
        0x84010000,
        0x80010000,
        0x80010000,
		0x80010000,
		0x80010000,
		0x80010000,
		0x08010000
    };
	
	/* Clear SPI status flags by writing 1 to them */
    DSPI_C.SR.R = 0x98080000;
	
     /* Clear the SPI_C input buffer */
    for(i=0; i < LAN9250_INIT_CMD_SIZE;i++ )
    {
        dummy_read = ((UNS16)DSPI_C.POPR.B.RXDATA);
    }
	
	/* Divide 16 address into 2 parts */
    address_register_H = (UNS16)((address_register & 0xFF00) >> 8);
    address_register_L = (UNS16)(address_register & 0x00FF);
	
	/* Reading Command send on MOSI */
	LAN9250_read_cmd[0] = (UNS32)((LAN9250_read_cmd[0] & 0xFFFF0000) | (READ_INSTRUCTION   & 0x000000FF));
	LAN9250_read_cmd[1] = (UNS32)((LAN9250_read_cmd[1] & 0xFFFF0000) | (address_register_H & 0x000000FF));
	LAN9250_read_cmd[2] = (UNS32)((LAN9250_read_cmd[2] & 0xFFFF0000) | (address_register_L & 0x000000FF));
	
	/* Sending the first 4 bytes of the frame */
	DSPI_C.PUSHR.R = LAN9250_read_cmd[0];
	DSPI_C.PUSHR.R = LAN9250_read_cmd[1];
	DSPI_C.PUSHR.R = LAN9250_read_cmd[2];
	DSPI_C.PUSHR.R = LAN9250_read_cmd[3];
	
	/* Wait for Receive FIFO contains four messages */
    while (DSPI_C.SR.B.RXCTR != 4)
    {
    }
	
	/* Make a "dummy" read x 3 bytes refer to read command length */
    dummy_read  = (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
    dummy_read 	= (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
    dummy_read 	= (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
    input_byte1 = (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
	
	/* Sending the last 3 bytes of the frame */	
	DSPI_C.PUSHR.R = LAN9250_read_cmd[4];
    DSPI_C.PUSHR.R = LAN9250_read_cmd[5];
    DSPI_C.PUSHR.R = LAN9250_read_cmd[6];
	
	/* Wait for the end of the transmission */
    while(DSPI_C.SR.B.EOQF != 1)
    {
    }
	
	/* Make a "dummy" read x 3 bytes refer to read command length */
    input_byte2 = (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
    input_byte3 = (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
    input_byte4 = (UNS16)(DSPI_C.POPR.B.RXDATA & 0xFFFF);
	
	/* Concatenate the 4 received value MSB -LSB   bit25-bit56 */   
	*a_read_input_PTR = (UNS32)((input_byte4 & 0x00FF) <<24  | (input_byte3 & 0x00FF) << 16 | (input_byte2 & 0x00FF) << 8 | input_byte1);

    /* Clear SPI status flags by writing 1 to them */
    DSPI_C.SR.R = 0x98080000;
}

/***************************************************************/
/* Global function : WriteRegistersLAN9250                     */
/* TX FIFO has only 4 entries                                  */
/***************************************************************/
void WriteRegistersLAN9250(UNS16 address_register, UNS32 value_towrite)
{
	volatile UNS16 dummy_read;
	UNS8 address_register_H;
	UNS8 address_register_L;
	UNS8 data_first_byte;
	UNS8 data_second_byte;
	UNS8 data_third_byte;
	UNS8 data_fourth_byte;
	UNS8 i,j;
	
    /**********************************************************/
    /* Program the SPI in order to dialog with the LAN9250    */
	/* Frame size: 8 bits 				  					  */
    /* 1st command word :                                     */
    /*             CONT     = 1                               */
    /*             CTAS     = 0                               */
    /*             EOQ      = 0                               */
    /*             CTCNT    = 1 (only for the first cmd)      */
    /*             PCS0     = 1                               */
    /*             TXDATA   = 0x03             			 	  */
    /* 2nd command word - TXDATA   =                    	  */
    /* 3rd command word - TXDATA   =                    	  */
	/* 4th command word - TXDATA   =              	  		  */
	/* 5th command word - TXDATA   =              	  		  */
	/* 6th command word - TXDATA   =              	  		  */
	/* 7th command word - TXDATA   =              	  		  */
	/* (CONT = 0, EOQ = 1) for 7th command word               */
    /**********************************************************/  
	UNS32 LAN9250_write_cmd[7] =
    {
        /* Write commands */
        0x84010000,
        0x80010000,
        0x80010000,
		0x80010000,
		0x80010000,
		0x80010000,
		0x08010000
    };
	
	/* Clear Transmit flag */
    DSPI_C.SR.B.TCF = 1;
	
	/* Clear SPI status flags by writing 1 to them */
    DSPI_C.SR.R = 0x98080000;
	
	/* Address of register to write to */
	address_register_H = (UNS8)((address_register & 0xFF00)>>8);
	address_register_L = (UNS8)(address_register & 0x00FF);
	
	/* Partition of data to write in 4 parts of 8 bits */
	data_first_byte =(UNS8)(value_towrite & 0x000000FF); 
	data_second_byte = (UNS8)((value_towrite & 0x0000FF00)>>8); 
	data_third_byte = (UNS8)((value_towrite & 0x00FF0000)>>16);
	data_fourth_byte = (UNS8)((value_towrite & 0xFF000000)>>24); 
	
	/* Populate the write command array with values */
    LAN9250_write_cmd[0] = (UNS32)((LAN9250_write_cmd[0] & 0xFFFF0000) | (WRITE_INSTRUCTION & 0x000000FF));
	LAN9250_write_cmd[1] = (UNS32)((LAN9250_write_cmd[1] & 0xFFFF0000) | (address_register_H & 0x000000FF));
	LAN9250_write_cmd[2] = (UNS32)((LAN9250_write_cmd[2] & 0xFFFF0000) | (address_register_L & 0x000000FF));
	LAN9250_write_cmd[3] = (UNS32)((LAN9250_write_cmd[3] & 0xFFFF0000) | (data_first_byte & 0x000000FF));
	LAN9250_write_cmd[4] = (UNS32)((LAN9250_write_cmd[4] & 0xFFFF0000) | (data_second_byte & 0x000000FF));
	LAN9250_write_cmd[5] = (UNS32)((LAN9250_write_cmd[5] & 0xFFFF0000) | (data_third_byte & 0x000000FF));
	LAN9250_write_cmd[6] = (UNS32)((LAN9250_write_cmd[6] & 0xFFFF0000) | (data_fourth_byte & 0x000000FF));

	/* Sending all 7 bytes to the LAN9250 including 4 bytes data*/
    i = 0;
    while (i < LAN9250_INIT_CMD_SIZE)
    {
        /* IF there are no SPI commands to be sent */
        if ((UNS8)DSPI_C.SR.B.TXCTR == 0)
        {
            j = 0;
            while ((i < LAN9250_INIT_CMD_SIZE) && (j < DSPI_TX_FIFO_SIZE))
            {
                DSPI_C.PUSHR.R = LAN9250_write_cmd[i];
                i ++;
                j ++;
            }
        }
        else
        {
        }
    }
    
    /* Wait for the end of the transmission */
    while((BOOLEAN)DSPI_C.SR.B.EOQF != TRUE)
    {
    }
    
    /* Clear the SPI_C input buffer */
    for(i=0; i < LAN9250_INIT_CMD_SIZE;i++ )
    {
        dummy_read = ((UNS16)DSPI_C.POPR.B.RXDATA);
    }
    
    /* Clear Transmit flag */
    DSPI_C.SR.B.TCF = 1;
   
   /* Clear SPI status flags by writing 1 to them */
    DSPI_C.SR.R = 0x98080000;
}

/***************************************************************/
/* Global function : ClearRegistersBits                        */
/***************************************************************/
void ClearLAN9250RegistersBits(UNS16 address_register, UNS8 bit_number)
{
	UNS32 register_value;
	UNS32 register_after_clear;
	UNS32 mask;
	
	/* Mask */
	mask = (UNS32)((UNS32)00000001 << bit_number);  

	/* Register Read and Clear wanted bits */
	ReadRegistersLAN9250(address_register, &register_value);
	register_after_clear = (UNS32)(register_value & ~mask); 
	
	/* Update register's values */
	WriteRegistersLAN9250(address_register, register_after_clear);
}

/***************************************************************/
/* Global function : SetRegistersBits                          */
/***************************************************************/
void SetLAN9250RegistersBits(UNS16 address_register, UNS8 bit_number)
{
	UNS32 register_value;
	UNS32 register_after_set;
	UNS32 mask;
	
	/* Mask */
	mask = (UNS32)((UNS32)00000001 << bit_number); 

	/* Register Read and Set wanted bits */
	ReadRegistersLAN9250(address_register, &register_value);
	register_after_set = (UNS32)(register_value | mask); 
	
	/* Update register's values */
	WriteRegistersLAN9250(address_register, register_after_set);
}


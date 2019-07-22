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
#include "LAN9250.h"
#include "Packet.h"
#include "standard.h"
#include "Memory.h"

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

/***************************************************************/
/* Global function : LAN9250_Read                              */
/***************************************************************/
void LAN9250_Read	(void * Instance_iop,
					void * ReceiveData_op,
					UNS32 lReceiveDataSize_i,
					DriverReturnCode_t * ReturnCode_op)
{ 
    /* Declaration */ 

    /* Initialization */
    Memory_Copy8(ReceiveData_op, &SIMU_IpPacket_RECEIVED, lReceiveDataSize_i); 

    *ReturnCode_op = DRVRC_NO_ERROR_E;
}

/***************************************************************/
/* Global function : LAN9250_Write                             */
/***************************************************************/
void LAN9250_Write	(void * Instance_iop,
                    void * SendData_ip,
					UNS32 lSendDataSize_i,
                    DriverReturnCode_t * ReturnCode_op)
{  
    *ReturnCode_op = DRVRC_NO_ERROR_E;

    /* Declaration */

    /* Function Body */
    Memory_Copy8(&SIMU_IpPacket_SEND, SendData_ip, lSendDataSize_i); 
} 
/*EOF*/
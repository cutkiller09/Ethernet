/***************************************************************/
/* FUNCTION : Initialize and drive the Flex CAN modules        */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"


#include "cpu_def.h"
#include "cpu_lb.h"
#include "hard_def.h"
#include "hard_ini.h"
#include "interface.h"
#include "configuration.h"
#include "cpu_load.h"

#include "can_lb.h"



/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
UNS8 TAB_CANA_list_of_tx_MB[CAN_MB_NUMBER];
UNS8 TAB_CANB_list_of_tx_MB[CAN_MB_NUMBER];
UNS8 TAB_CANC_list_of_tx_MB[CAN_MB_NUMBER];

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
#define CAN_BM_CODE_TX_INACTIVE             (UNS8)0b1000
#define CAN_BM_CODE_TX_SEND                 (UNS8)0b1100
#define CAN_BM_CODE_RX_EMPTY                (UNS8)0b0100
#define CAN_RX_BUFF_BUSY_MASK               (UNS32)0b0001
#define CAN_BM_DEFINE_TX                    (UNS8)CAN_BM_CODE_TX_INACTIVE
#define CAN_BM_DEFINE_RX                    (UNS8)CAN_BM_CODE_RX_EMPTY
#define CAN_MCR_FREEZE                      (UNS32)0x50000000
#define CAN_MCR_START_MASK                  (UNS32)0xAFFFFFFF
#define CAN_MCR_DISABLE                     (UNS32)0xC0000000

#define CAN_MAXMB_FIELD_MASK                (UNS32)0x0000003F

/***************************************************************/
/*                                                             */
/*                      LOCAL TYPES                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
T_CAN_RX_VALUES CANA_input_buffer;
T_CAN_RX_VALUES CANB_input_buffer;
T_CAN_RX_VALUES CANC_input_buffer;

/***************************************************************/
/* Local function : ReadCANLabel                               */
/***************************************************************/
void ReadCANLabel(volatile T_FLEXCAN2_tag * a_CAN_register_PTR, UNS8 a_reception_buffer_number, T_CAN_RX_VALUES* a_CAN_data_PTR)
{
    volatile UNS32 dummy_read;

    /* IF the reception buffer is not full */
    if (a_CAN_data_PTR->FirstEmptyElement < (UNS16)CAN_BUFFER_SIZE)
    /* THEN */
    {
        /* Wait until the message box is not busy and lock it by reading the CODE field of the MB's Control and Status word */
        while (((UNS32)a_CAN_register_PTR->BUF[a_reception_buffer_number].CS.B.CODE & CAN_RX_BUFF_BUSY_MASK) != (UNS32)0x0)
        {
        }
        
        /* Store received message to provide it to the Applicative S/W: */
        /*   - Store ID */
        a_CAN_data_PTR->TAB_label[a_CAN_data_PTR->FirstEmptyElement].CAN_id.identifier = a_CAN_register_PTR->BUF[a_reception_buffer_number].ID.R;
        /*   - Store data MSB */
        a_CAN_data_PTR->TAB_label[a_CAN_data_PTR->FirstEmptyElement].label_MSB = a_CAN_register_PTR->BUF[a_reception_buffer_number].DATA.W[0];
        /*   - Store data LSB */
        a_CAN_data_PTR->TAB_label[a_CAN_data_PTR->FirstEmptyElement].label_LSB = a_CAN_register_PTR->BUF[a_reception_buffer_number].DATA.W[1];
        /*   - Store message length */
        a_CAN_data_PTR->TAB_label[a_CAN_data_PTR->FirstEmptyElement].message_length = a_CAN_register_PTR->BUF[a_reception_buffer_number].CS.B.LENGTH;
        
        /* Increment the first empty element of the reception buffer */
        a_CAN_data_PTR->FirstEmptyElement ++;
    }
    else
    {
    }
    /* END IF */

    /* IF the message box is in the first 32 buffer */
    if (a_reception_buffer_number <= 31)
    /* THEN */
    {
        /* Clear the flag of successful reception in IFRL register */
        a_CAN_register_PTR->IFRL.R = (UNS32)(1 << a_reception_buffer_number);
    }
    /* ELSE */
    else
    {
        /* Clear the flag of successful reception in IFRH register */
        a_CAN_register_PTR->IFRH.R = (UNS32)(1 << (a_reception_buffer_number - 32));
    }
    /* END IF */

    /* Unlock the buffer by reading the Free running timer register */
    dummy_read = a_CAN_register_PTR->TIMER.R;
}


/***************************************************************/
/* Local function : SendCANLabel                               */
/***************************************************************/
void SendCANLabel(volatile T_FLEXCAN2_tag * a_CAN_register_PTR, 
                  T_CAN_Label* a_CAN_frame_PTR, 
                  UNS8 a_buffer_id)
{
    /* Wait for end of previous transmit process when their is no transmit error */
    while(((UNS8)a_CAN_register_PTR->BUF[a_buffer_id].CS.B.CODE == CAN_BM_CODE_TX_SEND) && 
          ((BOOLEAN)a_CAN_register_PTR->ESR.B.TXWRN == FALSE))
    {
    }
    
    /* Reset message buffer of CAN module for transmit transfer */
    a_CAN_register_PTR->BUF[a_buffer_id].CS.B.CODE = (VUNS32)CAN_BM_CODE_TX_INACTIVE;

    /* Fill-up Message Buffer with the frame to send: */
    /*   - Message identifier */
    a_CAN_register_PTR->BUF[a_buffer_id].ID.R = a_CAN_frame_PTR->CAN_id.identifier;
    /*   - Message data */
    a_CAN_register_PTR->BUF[a_buffer_id].DATA.W[0] = a_CAN_frame_PTR->label_MSB;
    a_CAN_register_PTR->BUF[a_buffer_id].DATA.W[1] = a_CAN_frame_PTR->label_LSB;
    /*   - Message length */
    a_CAN_register_PTR->BUF[a_buffer_id].CS.B.LENGTH = a_CAN_frame_PTR->message_length;

    /* Start transmission */
    a_CAN_register_PTR->BUF[a_buffer_id].CS.B.CODE = (VUNS32)CAN_BM_CODE_TX_SEND;
}


/***************************************************************/
/* Local function : ReadAllCANLabel                            */
/***************************************************************/
void ReadAllCANLabel(volatile T_FLEXCAN2_tag *   a_CAN_register_PTR,
                     const T_CAN_CONFIGURATION * a_CAN_message_box_conf_PTR,
                     T_CAN_RX_VALUES *           a_CAN_data_PTR)
{
    UNS8 i;
    UNS8 MB_number;

    /* FOR each message box of the current CAN module configured in reception */
    for (i = 0 ; i < a_CAN_message_box_conf_PTR->number_of_rx_MB ; i ++)
    {        
        MB_number = a_CAN_message_box_conf_PTR->TAB_list_of_rx_MB[i];
        
        /* IF the message box is in the first 32 buffer */
        if (MB_number < 32)
        /* THEN */
        {
            /* IF the message box has received a new message */
            if ((a_CAN_register_PTR->IFRL.R & (UNS32)(1 << MB_number)) != (UNS32)0)
            /* THEN */
            {
                /* Call the function ReadCANLabel to read the label from the message box */
                /* and to store it into the data buffer */
                ReadCANLabel(a_CAN_register_PTR, MB_number, a_CAN_data_PTR);
            }
            else
            {
            }
            /* END IF */
        }
        /* ELSE */
        else
        {
            /* IF the message box has received a new message */
            if ((a_CAN_register_PTR->IFRH.R & (UNS32)(1 << (MB_number - 32))) != (UNS32)0)
            /* THEN */
            {
                /* Call the function ReadCANLabel to read the label from the message box */
                /* and to store it into the data buffer */
                ReadCANLabel(a_CAN_register_PTR, MB_number, a_CAN_data_PTR);
            }
            else
            {
            }
            /* END IF */
        }
        /* END IF */
    }
    /* END FOR */
}

/***************************************************************/
/* Local function : ReportCANMessages                          */
/***************************************************************/
void ReportCANMessages(volatile T_FLEXCAN2_tag *   a_CAN_register_PTR,
                          const T_CAN_CONFIGURATION * a_CAN_message_box_conf_PTR,
                          T_CAN_TX_VALUES *           a_CAN_data_PTR,
                          T_CAN_STATUS *              a_CAN_status_PTR)
{
    UNS32 i;

    /* FOR each label to be sent */
    for (i=0; i<a_CAN_data_PTR->number; i++)
    {
        /* IF the message box is defined as output and there is CAN data to be sent */
        if (((UNS8)((UNS8)a_CAN_message_box_conf_PTR->box[a_CAN_data_PTR->MB_identifier[i]].CS.B.CODE & CAN_BM_DEFINE_TX) == CAN_BM_DEFINE_TX) &&
            (a_CAN_data_PTR->TAB_label[i].CAN_id.identifier != CAN_MB_NOT_MSG_TO_SEND))
        /* THEN */
        {
            /* Call SendCANLabel to send the data */
            SendCANLabel(a_CAN_register_PTR, &(a_CAN_data_PTR->TAB_label[i]), a_CAN_data_PTR->MB_identifier[i]);
            /* Clear the data send */
            a_CAN_data_PTR->TAB_label[i].CAN_id.identifier = CAN_MB_NOT_MSG_TO_SEND;
        }
        else
        {
        }
        /* END IF */
    }
    /* END FOR */
    
    /* Clear send buffer */
    a_CAN_data_PTR->number = 0;

    /* IF there is an error on CAN transmit function */
    if ((BOOLEAN)a_CAN_register_PTR->ESR.B.TXWRN == TRUE)
    /* THEN */
    {        
        /* Active the transmit failure flag */
        a_CAN_status_PTR->F_transmit_failure = TRUE;
    }
    else
    {
        /* Clear the transmit failure flag */
        a_CAN_status_PTR->F_transmit_failure = FALSE;
    }
}



/***************************************************************/
/* Local function : InitializeCAN                              */
/***************************************************************/
void InitializeCAN(volatile T_FLEXCAN2_tag * a_CAN_register_PTR, 
                                          const T_CAN_CONFIGURATION * a_CAN_message_box_conf_PTR,
                                          UNS8 * a_CAN_tx_MB_list_PTR)
{
    UNS8 i;

    /* Freeze and initialize the FlexCAN MCR register according to the configuration provided by the APP software for MAXMB field */
    a_CAN_register_PTR->MCR.R      = CAN_MCR_FREEZE | (CAN_MAXMB_FIELD_MASK & a_CAN_message_box_conf_PTR->MAXMB);
    
    /* Initialize the CR register of the current CAN module, according to the configuration provided by the APP software for */
    /* PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP & PROPSEG fields */
    a_CAN_register_PTR->CR.R       = (0xFFFF3087 & a_CAN_message_box_conf_PTR->CR.R);
    /* Set the acceptance masks of the current CAN module according to the configuration provided by the APP software */
    a_CAN_register_PTR->RXGMASK.R  = a_CAN_message_box_conf_PTR->RXGMASK;
    a_CAN_register_PTR->RX14MASK.R = a_CAN_message_box_conf_PTR->RX14MASK;
    a_CAN_register_PTR->RX15MASK.R = a_CAN_message_box_conf_PTR->RX15MASK;
    
    /* FOR all message buffers of the current CAN module */
    for (i = 0 ; i < CAN_MB_NUMBER ; i ++)
    {
        /* Write the MB's Control and Status word according to the configuration provided by the APP software to activate it */
        a_CAN_register_PTR->BUF[i].CS.R = a_CAN_message_box_conf_PTR->box[i].CS.R;
        /* Initialize the MB's Identifier Field according to the configuration provided by the APP software */
        a_CAN_register_PTR->BUF[i].ID.R = a_CAN_message_box_conf_PTR->box[i].ID.R;
        /* Check if the message box is configured as TX */
        if (a_CAN_message_box_conf_PTR->box[i].ID.R == CAN_MB_NOT_MSG_TO_SEND)
        {
            *a_CAN_tx_MB_list_PTR = i;
            a_CAN_tx_MB_list_PTR++;
        }
        else
        {            
        }
    }
    /* END FOR */
    
    /* Set the interrupt configuration of the current CAN module according to the configuration provided by the APP software */
    a_CAN_register_PTR->IMRL.R  = a_CAN_message_box_conf_PTR->IMRL;
    a_CAN_register_PTR->IMRH.R  = a_CAN_message_box_conf_PTR->IMRH;

    /* Start the FlexCAN module by clearing the FRZ and HALT fields of the MCR register */
    a_CAN_register_PTR->MCR.R = CAN_MCR_START_MASK & a_CAN_register_PTR->MCR.R;
}

/***************************************************************/
/* Global function : InitializeCan_Lb                          */
/***************************************************************/
void InitializeCan_Lb(void)
{    
    UNS8 i;
    
    /* Initialize data of the module to 0 (except for identifer set to 0xFFFFFFFF and list of tx MB to 0xFF) */
    for (i=0; i<CAN_BUFFER_SIZE;i++)
    {
        CANA_input_buffer.TAB_label[i].CAN_id.identifier = (UNS32)CAN_MB_NOT_MSG_TO_SEND;
        CANA_input_buffer.TAB_label[i].label_LSB = 0;
        CANA_input_buffer.TAB_label[i].label_MSB = 0;
        CANA_input_buffer.TAB_label[i].message_length = 0;
        CANB_input_buffer.TAB_label[i].CAN_id.identifier = (UNS32)CAN_MB_NOT_MSG_TO_SEND;
        CANB_input_buffer.TAB_label[i].label_LSB = 0;
        CANB_input_buffer.TAB_label[i].label_MSB = 0;
        CANB_input_buffer.TAB_label[i].message_length = 0;
		CANC_input_buffer.TAB_label[i].CAN_id.identifier = (UNS32)CAN_MB_NOT_MSG_TO_SEND;
        CANC_input_buffer.TAB_label[i].label_LSB = 0;
        CANC_input_buffer.TAB_label[i].label_MSB = 0;
        CANC_input_buffer.TAB_label[i].message_length = 0;
    }    
    for (i=0; i < CAN_MB_NUMBER; i++)
    {
        TAB_CANA_list_of_tx_MB[i] = 0xFF;
        TAB_CANB_list_of_tx_MB[i] = 0xFF;
		TAB_CANC_list_of_tx_MB[i] = 0xFF;
    }
    CANA_input_buffer.FirstEmptyElement = 0;
    CANA_input_buffer.FirstInElement = 0;
    CANB_input_buffer.FirstEmptyElement = 0;
    CANB_input_buffer.FirstInElement = 0;
	CANC_input_buffer.FirstEmptyElement = 0;
    CANC_input_buffer.FirstInElement = 0;
}


/***************************************************************/
/* Global function : DisableCANModule                          */
/***************************************************************/
void DisableCANModule(volatile T_FLEXCAN2_tag * a_CAN_register_PTR)
{
    /* Freeze and disable the current CAN interface */
    a_CAN_register_PTR->MCR.R = CAN_MCR_DISABLE;
}


/***************************************************************/
/* Global function : GetCANData                                */
/***************************************************************/
void GetCANData(void)
{
	
	/*todo check if the CAN enable should be checked before executing all this             */
    UNS32 i;
    
    /* Call MaskInterruptINTC function to mask the interrupt from the interrupt controller */
    MaskInterruptINTC();
    
    /* CAN A enable  */
    if(I_BSP_conf.can_A_message_box_conf.F_can_enable == TRUE)
    {
       /* Call ReadAllCANLabel function for each CAN input (CAN_A) to read all CAN label stored on the CAN MessageBox */
       ReadAllCANLabel((T_FLEXCAN2_tag *)&CAN_A, &I_BSP_conf.can_A_message_box_conf, &CANA_input_buffer);
    
       /* Copy and clear received data from internal buffer to the interfaced buffer with the APPLICATIVE software */
       /*! NOTE : The BSP software will erase data previously received */
       for (i = CANA_input_buffer.FirstInElement ; i < CANA_input_buffer.FirstEmptyElement ;i++)
       {
           /*! Copy */
           I_BSP_Out.can_A_rx.TAB_label[i].CAN_id.identifier = CANA_input_buffer.TAB_label[i].CAN_id.identifier;
           I_BSP_Out.can_A_rx.TAB_label[i].label_LSB = CANA_input_buffer.TAB_label[i].label_LSB;
           I_BSP_Out.can_A_rx.TAB_label[i].label_MSB = CANA_input_buffer.TAB_label[i].label_MSB;
           /*! Clear temporary buffer */
           CANA_input_buffer.TAB_label[i].CAN_id.identifier = (UNS32)0xFFFFFFFF;
           CANA_input_buffer.TAB_label[i].label_LSB = 0;
           CANA_input_buffer.TAB_label[i].label_MSB = 0;
       }   
    }
    
    /* CAN B enable  */
    if(I_BSP_conf.can_B_message_box_conf.F_can_enable == TRUE)
    {
        /* Call ReadAllCANLabel function for each CAN input (CAN_B) to read all CAN label stored on the CAN MessageBox */
        ReadAllCANLabel((T_FLEXCAN2_tag *)&CAN_B, &I_BSP_conf.can_B_message_box_conf, &CANB_input_buffer);
    
       /* Copy and clear received data from internal buffer to the interfaced buffer with the APPLICATIVE software */
       /*! NOTE : The BSP software will erase data previously received */    
       for (i = CANB_input_buffer.FirstInElement ; i < CANB_input_buffer.FirstEmptyElement ; i++)
       {
           /*! Copy */
           I_BSP_Out.can_B_rx.TAB_label[i].CAN_id.identifier = CANB_input_buffer.TAB_label[i].CAN_id.identifier;
           I_BSP_Out.can_B_rx.TAB_label[i].label_LSB = CANB_input_buffer.TAB_label[i].label_LSB;
           I_BSP_Out.can_B_rx.TAB_label[i].label_MSB = CANB_input_buffer.TAB_label[i].label_MSB;
           /*! Clear temporary buffer */
           CANB_input_buffer.TAB_label[i].CAN_id.identifier = (UNS32)0xFFFFFFFF;
           CANB_input_buffer.TAB_label[i].label_LSB = 0;
           CANB_input_buffer.TAB_label[i].label_MSB = 0;
       }       
    }
 
    /* CAN C enable  */
    if(I_BSP_conf.can_C_message_box_conf.F_can_enable == TRUE)
    {
        /* Call ReadAllCANLabel function for each CAN input (CAN_C) to read all CAN label stored on the CAN MessageBox */
     	ReadAllCANLabel((T_FLEXCAN2_tag *)&CAN_C, &I_BSP_conf.can_C_message_box_conf, &CANC_input_buffer); 
    
       /* Copy and clear received data from internal buffer to the interfaced buffer with the APPLICATIVE software */
       /*! NOTE : The BSP software will erase data previously received */
       for (i = CANC_input_buffer.FirstInElement ; i < CANC_input_buffer.FirstEmptyElement ; i++)
       {
           /*! Copy */
           I_BSP_Out.can_C_rx.TAB_label[i].CAN_id.identifier = CANC_input_buffer.TAB_label[i].CAN_id.identifier;
           I_BSP_Out.can_C_rx.TAB_label[i].label_LSB = CANC_input_buffer.TAB_label[i].label_LSB;
           I_BSP_Out.can_C_rx.TAB_label[i].label_MSB = CANC_input_buffer.TAB_label[i].label_MSB;
           /*! Clear temporary buffer */
           CANC_input_buffer.TAB_label[i].CAN_id.identifier = (UNS32)0xFFFFFFFF;
           CANC_input_buffer.TAB_label[i].label_LSB = 0;
           CANC_input_buffer.TAB_label[i].label_MSB = 0;
       } 
    }
	
    /*! Copy */
    I_BSP_Out.can_A_rx.FirstEmptyElement = CANA_input_buffer.FirstEmptyElement;
    I_BSP_Out.can_A_rx.FirstInElement = CANA_input_buffer.FirstInElement;
    I_BSP_Out.can_B_rx.FirstEmptyElement = CANB_input_buffer.FirstEmptyElement;
    I_BSP_Out.can_B_rx.FirstInElement = CANB_input_buffer.FirstInElement;
	I_BSP_Out.can_C_rx.FirstEmptyElement = CANC_input_buffer.FirstEmptyElement;
    I_BSP_Out.can_C_rx.FirstInElement = CANC_input_buffer.FirstInElement;
    /*! Clear temporary buffer */
    CANA_input_buffer.FirstEmptyElement = 0;
    CANA_input_buffer.FirstInElement = 0;
    CANB_input_buffer.FirstEmptyElement = 0;
    CANB_input_buffer.FirstInElement = 0;
	CANC_input_buffer.FirstEmptyElement = 0;
    CANC_input_buffer.FirstInElement = 0;
    
    /* Call UnmaskInterruptINTC function to unmask the interrupt from the interrupt controller */
    UnmaskInterruptINTC();
}

/***************************************************************/
/* Global function : CANAHandler                               */
/***************************************************************/
void CANAHandler(void)
{
    /* Call ReadAllCANLabel function to read label frem CAN_A register */
    /* and set data buffer CANA_input_buffer using the configuration data I_BSP_conf.can_A_message_box_conf */
    ReadAllCANLabel((T_FLEXCAN2_tag *)&CAN_A, &I_BSP_conf.can_A_message_box_conf, &CANA_input_buffer);
    /* Increment the number of CAN tasks triggered this PIT */
    CPT_CAN_RX_occurrence++;
}

/***************************************************************/
/* Global function : CANBHandler                               */
/***************************************************************/
void CANBHandler(void)
{
    /* Call ReadAllCANLabel function to read label frem CAN_B register */
    /* and set data buffer CANB_input_buffer using the configuration data I_BSP_conf.can_B_message_box_conf */
    ReadAllCANLabel((T_FLEXCAN2_tag *)&CAN_B, &I_BSP_conf.can_B_message_box_conf, &CANB_input_buffer);
    /* Increment the number of CAN tasks triggered this PIT */
    CPT_CAN_RX_occurrence++;
}

/***************************************************************/
/* Global function : CANCHandler                               */
/***************************************************************/
void CANCHandler(void)
{
    /* Call ReadAllCANLabel function to read label frem CAN_C register */
    /* and set data buffer CANC_input_buffer using the configuration data I_BSP_conf.can_C_message_box_conf */
    ReadAllCANLabel((T_FLEXCAN2_tag *)&CAN_C, &I_BSP_conf.can_C_message_box_conf, &CANC_input_buffer);
    /* Increment the number of CAN tasks triggered this PIT */
    CPT_CAN_RX_occurrence++;
}

/***************************************************************/
/* Global function : ReportAllCANMessages                      */
/***************************************************************/
void ReportAllCANMessages(void)
{
    /* IF the CAN A module has to be enabled */
    if (I_BSP_conf.can_A_message_box_conf.F_can_enable == TRUE)
    /* THEN */
    {
        /* Call ReportCANMessages function to send CAN label on CAN_A */
        /* by using data buffer I_BSP_In.can_A_tx and CAN configuration I_BSP_conf.can_A_message_box_conf */
        ReportCANMessages((T_FLEXCAN2_tag *)&CAN_A, &I_BSP_conf.can_A_message_box_conf, &I_BSP_In.can_A_tx, &I_BSP_Out.can_A_status);
    }
    else
    {
		/* Set the TX signal to HIGH state: */
        /*    - Set the pin 83 to GPIO mode */
        SIU.PCR[83].R = 0x0203;
        /*    - Set the GPIO 85 to HIGH state */
        SIU.GPDO[83].B.PDO = TRUE;
    
        /* Call DisableCANModule to disable unused CAN module A */
        DisableCANModule((T_FLEXCAN2_tag *)&CAN_A);
    }
    /* END IF */
    /* IF the CAN B module has to be enabled */
    if (I_BSP_conf.can_B_message_box_conf.F_can_enable == TRUE)
    /* THEN */
    {
        /* Call ReportCANMessages function to send CAN label on CAN_B */
        /* by using data buffer I_BSP_In.can_B_tx and CAN configuration I_BSP_conf.can_B_message_box_conf */
        ReportCANMessages((T_FLEXCAN2_tag *)&CAN_B, &I_BSP_conf.can_B_message_box_conf, &I_BSP_In.can_B_tx, &I_BSP_Out.can_B_status);
    }
    else
    {
        /* Set the TX signal to HIGH state: */
        /*    - Set the pin 85 to GPIO mode */
        SIU.PCR[85].R = 0x0203;
        /*    - Set the GPIO 85 to HIGH state */
        SIU.GPDO[85].B.PDO = TRUE;
    
        /* Call DisableCANModule to disable unused CAN module B */
        DisableCANModule((T_FLEXCAN2_tag *)&CAN_B);
    }
    /* END IF */
	/* IF the CAN C module has to be enabled */
    if (I_BSP_conf.can_C_message_box_conf.F_can_enable == TRUE)
    /* THEN */
    {
        /* Call ReportCANMessages function to send CAN label on CAN_C */
        /* by using data buffer I_BSP_In.can_C_tx and CAN configuration I_BSP_conf.can_C_message_box_conf */
        ReportCANMessages((T_FLEXCAN2_tag *)&CAN_C, &I_BSP_conf.can_C_message_box_conf, &I_BSP_In.can_C_tx, &I_BSP_Out.can_C_status);
    }
    else
    {
        /* Set the TX signal to HIGH state: */
        /*    - Set the pin 87 to GPIO mode */
        SIU.PCR[87].R = 0x0203;
        /*    - Set the GPIO 87 to HIGH state */
        SIU.GPDO[87].B.PDO = TRUE;
    
        /* Call DisableCANModule to disable unused CAN module C */
        DisableCANModule((T_FLEXCAN2_tag *)&CAN_C);
    }
    /* END IF */
}

/***************************************************************/
/* Global function : InitializeAllCAN                          */
/***************************************************************/
void InitializeAllCAN(void)
{
    /* IF the CAN A module has to be enable */
    if (I_BSP_conf.can_A_message_box_conf.F_can_enable == TRUE)
    /* THEN */
    {
        /* Call InitializeCAN function to initialize the CAN A */
        InitializeCAN((T_FLEXCAN2_tag *)&CAN_A, &I_BSP_conf.can_A_message_box_conf, (UNS8 *)TAB_CANA_list_of_tx_MB);
    }
    else
    /* ELSE */
    {
        /* Set the TX signal to HIGH state: */
		/*    - Set the pin to GPIO mode */
        SIU.PCR[GPIO_CANA_TX_PIN].R = SIU_PCR_CANA_TX_GPIO_INIT;
		/*    - Set the GPIO to HIGH state */
        SIU.GPDO[GPIO_CANA_TX_PIN].B.PDO = (UNS32)TRUE;
		
		/* Call DisableCANModule to disable unused CAN module A */
        DisableCANModule((T_FLEXCAN2_tag *)&CAN_A);
    }
    /* END IF */

    /* IF the CAN B module has to be enable */
    if (I_BSP_conf.can_B_message_box_conf.F_can_enable == TRUE)
    /* THEN */
    {
        /* Call InitializeCAN function to initialize the CAN B */
        InitializeCAN((T_FLEXCAN2_tag *)&CAN_B, &I_BSP_conf.can_B_message_box_conf, (UNS8 *)TAB_CANB_list_of_tx_MB);
    }
    else
    /* ELSE */
    {
        /* Set the TX signal to HIGH state: */
		/*    - Set the pin to GPIO mode */
        SIU.PCR[GPIO_CANB_TX_PIN].R = SIU_PCR_CANB_TX_GPIO_INIT;
        /*    - Set the GPIO to HIGH state */
        SIU.GPDO[GPIO_CANB_TX_PIN].B.PDO = (UNS32)TRUE;
		
		/* Call DisableCANModule to disable unused CAN module A */
        DisableCANModule((T_FLEXCAN2_tag *)&CAN_B);
    }
    /* END IF */

    /* IF the CAN C module has to be enable */
    if (I_BSP_conf.can_C_message_box_conf.F_can_enable == TRUE)
    /* THEN */
    {
        /* Call InitializeCAN function to initialize the CAN C */
        InitializeCAN((T_FLEXCAN2_tag *)&CAN_C, &I_BSP_conf.can_C_message_box_conf, (UNS8 *)TAB_CANC_list_of_tx_MB);
    }
    else
    /* ELSE */
    {
        /* Set the TX signal to HIGH state: */
		/*    - Set the pin to GPIO mode */
        SIU.PCR[GPIO_CANC_TX_PIN].R = SIU_PCR_CANC_TX_GPIO_INIT;
        /*    - Set the GPIO to HIGH state */
        SIU.GPDO[GPIO_CANC_TX_PIN].B.PDO = (UNS32)TRUE;
		
		/* Call DisableCANModule to disable unused CAN module A */
        DisableCANModule((T_FLEXCAN2_tag *)&CAN_C);
    }
    /* END IF */

}

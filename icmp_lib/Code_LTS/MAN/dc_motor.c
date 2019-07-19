/***************************************************************/
/* FUNCTION : Generate the DC motor commands                   */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "hard_def.h"
#include "cpu_lb.h"
#include "disc_out.h"

#include "interface.h"
#include "etpu_lb.h"
#include "etpu_QOM_lb.h"

#include "dc_motor.h"


/***************************************************************/
/*                                                             */
/*                        GLOBAL DATA                          */
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
#define CMD_HI_DC_MOTOR (BOOLEAN)0
#define CMD_LO_DC_MOTOR (BOOLEAN)1

/* Define the number of DC Motor */
#define NB_DCMOTOR    (UNS8) 16

/* Define delay >= 1ms before switching on the inactive FET s */
#define FET_DELAY (UNS16)11

/***************************************************************/
/*                                                             */
/*                        LOCAL TYPES                          */
/*                                                             */
/***************************************************************/

/* Define the structure used to memorize the discrete output value for EN and LEN1/2 */
typedef struct
{
    /* Disc addr */
	BOOLEAN	   *PTR_HW_DC_MOT_EN;
    BOOLEAN    *PTR_HW_DC_MOT_LEN1;
    BOOLEAN    *PTR_HW_DC_MOT_LEN2;
}
T_Dc_motor_conf;

/* Define the structure used for EN and LEN interface */
typedef struct
{
    T_Do_buffer      *PTR_disc_out;
    UNS8             disc_out_bit_position;
    volatile UNS32  *PTR_disc_out_addr;
}
T_Dc_motor_en_conf;

/* Define the structure used for HEN interface */
typedef struct
{
    UNS8             ETPUCH_value;
}
T_Dc_motor_hen_conf;

/* Define the structure used for HSI DC Motor definition */
typedef struct
{
	/* EN information */
	T_Dc_motor_en_conf EN;
	
    /* LEN1 information */
    T_Dc_motor_en_conf LEN1;

    /* LEN2 information */
    T_Dc_motor_en_conf LEN2;

    /* HEN1 information */
    T_Dc_motor_hen_conf HEN1;

    /* HEN2 information */
    T_Dc_motor_hen_conf HEN2;
}
T_Dc_motor_hsi_conf;

/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
/* Table to memorize each DC Motor's previous command */
BOOLEAN TAB_F_CMD_DIR_Motor_MEM[NB_DCMOTOR];

/* Table to memorize each DC Motor's enable state */
BOOLEAN TAB_F_EN_Motor_MEM[NB_DCMOTOR];

/* Table to memorize the Flag of the Motor first command */
BOOLEAN TAB_F_Motor_First_CMD[NB_DCMOTOR];

/* Table to memorize each DC Motor discrete output value on LEN1/2 */
const T_Dc_motor_conf K_tab_dc_mot_conf[NB_DCMOTOR] =
{
   /* DC MOT EN Value, DC MOT LEN1 Value, DC MOT LEN2 Value */
   {&(HW_EN_DCM_1),   &(HW_LEN1_DCM_1),   &(HW_LEN2_DCM_1)},
   {&(HW_EN_DCM_2),   &(HW_LEN1_DCM_2),   &(HW_LEN2_DCM_2)},
   {&(HW_EN_DCM_3),   &(HW_LEN1_DCM_3),   &(HW_LEN2_DCM_3)},
   {&(HW_EN_DCM_4),   &(HW_LEN1_DCM_4),   &(HW_LEN2_DCM_4)},
   {&(HW_EN_DCM_5),   &(HW_LEN1_DCM_5),   &(HW_LEN2_DCM_5)},
   {&(HW_EN_DCM_6),   &(HW_LEN1_DCM_6),   &(HW_LEN2_DCM_6)},
   {&(HW_EN_DCM_7),   &(HW_LEN1_DCM_7),   &(HW_LEN2_DCM_7)},
   {&(HW_EN_DCM_8),   &(HW_LEN1_DCM_8),   &(HW_LEN2_DCM_8)},
   {&(HW_EN_DCM_9),   &(HW_LEN1_DCM_9),   &(HW_LEN2_DCM_9)},
   {&(HW_EN_DCM_10),  &(HW_LEN1_DCM_10),  &(HW_LEN2_DCM_10)},
   {&(HW_EN_DCM_11),  &(HW_LEN1_DCM_11),  &(HW_LEN2_DCM_11)},
   {&(HW_EN_DCM_12),  &(HW_LEN1_DCM_12),  &(HW_LEN2_DCM_12)},
   {&(HW_EN_DCM_13),  &(HW_LEN1_DCM_13),  &(HW_LEN2_DCM_13)},
   {&(HW_EN_DCM_14),  &(HW_LEN1_DCM_14),  &(HW_LEN2_DCM_14)},
   {&(HW_EN_DCM_15),  &(HW_LEN1_DCM_15),  &(HW_LEN2_DCM_15)},   
   {&(HW_EN_DCM_16),  &(HW_LEN1_DCM_16),  &(HW_LEN2_DCM_16)}
};

/* Table to define each DC motor HEN/LEN definition issued from HSI */
const T_Dc_motor_hsi_conf K_tab_dc_mot_hsi_conf[NB_DCMOTOR] =
{
   /*                           EN                          |                            LEN1                            |                       LEN2                                |       HEN1                   |      HEN2        */
   /*   Dis OUT      , Bit POS ,   DO Buffer addr           |     Dis OUT      ,  Bit POS   ,   DO Buffer addr           |      Dis OUT    ,  Bit POS  ,   DO Buffer addr            |   eTPU    Channel            |  eTPU    Channel */
     &(disc_output_1),        0,   &DO_CLK_DO_1_5V_ADDRESS,    &(disc_output_1),           1,   &DO_CLK_DO_1_5V_ADDRESS,   &(disc_output_1),          2,   &DO_CLK_DO_1_5V_ADDRESS,        HEN1_DCM_1_CHANNEL,        HEN2_DCM_1_CHANNEL,   
     &(disc_output_1),        3,   &DO_CLK_DO_1_5V_ADDRESS,    &(disc_output_1),           4,   &DO_CLK_DO_1_5V_ADDRESS,   &(disc_output_1),          5,   &DO_CLK_DO_1_5V_ADDRESS,        HEN1_DCM_2_CHANNEL,        HEN2_DCM_2_CHANNEL,   
     &(disc_output_1),        6,   &DO_CLK_DO_1_5V_ADDRESS,    &(disc_output_1),           7,   &DO_CLK_DO_1_5V_ADDRESS,   &(disc_output_1),          8,   &DO_CLK_DO_1_5V_ADDRESS,        HEN1_DCM_3_CHANNEL,        HEN2_DCM_3_CHANNEL,   
     &(disc_output_1),        9,   &DO_CLK_DO_1_5V_ADDRESS,    &(disc_output_1),          10,   &DO_CLK_DO_1_5V_ADDRESS,   &(disc_output_1),         11,   &DO_CLK_DO_1_5V_ADDRESS,        HEN1_DCM_4_CHANNEL,        HEN2_DCM_4_CHANNEL,   
     &(disc_output_2),        0,   &DO_CLK_DO_2_5V_ADDRESS,    &(disc_output_2),           1,   &DO_CLK_DO_2_5V_ADDRESS,   &(disc_output_2),          2,   &DO_CLK_DO_2_5V_ADDRESS,        HEN1_DCM_5_CHANNEL,        HEN2_DCM_5_CHANNEL,   
     &(disc_output_2),        3,   &DO_CLK_DO_2_5V_ADDRESS,    &(disc_output_2),           4,   &DO_CLK_DO_2_5V_ADDRESS,   &(disc_output_2),          5,   &DO_CLK_DO_2_5V_ADDRESS,        HEN1_DCM_6_CHANNEL,        HEN2_DCM_6_CHANNEL,   
     &(disc_output_2),        6,   &DO_CLK_DO_2_5V_ADDRESS,    &(disc_output_2),           7,   &DO_CLK_DO_2_5V_ADDRESS,   &(disc_output_2),          8,   &DO_CLK_DO_2_5V_ADDRESS,        HEN1_DCM_7_CHANNEL,        HEN2_DCM_7_CHANNEL,   
     &(disc_output_2),        9,   &DO_CLK_DO_2_5V_ADDRESS,    &(disc_output_2),          10,   &DO_CLK_DO_2_5V_ADDRESS,   &(disc_output_2),         11,   &DO_CLK_DO_2_5V_ADDRESS,        HEN1_DCM_8_CHANNEL,        HEN2_DCM_8_CHANNEL,   
     &(disc_output_3),        0,   &DO_CLK_DO_3_5V_ADDRESS,    &(disc_output_3),           1,   &DO_CLK_DO_3_5V_ADDRESS,   &(disc_output_3),          2,   &DO_CLK_DO_3_5V_ADDRESS,        HEN1_DCM_9_CHANNEL,        HEN2_DCM_9_CHANNEL,   
     &(disc_output_3),        3,   &DO_CLK_DO_3_5V_ADDRESS,    &(disc_output_3),           4,   &DO_CLK_DO_3_5V_ADDRESS,   &(disc_output_3),          5,   &DO_CLK_DO_3_5V_ADDRESS,        HEN1_DCM_10_CHANNEL,       HEN2_DCM_10_CHANNEL,  
     &(disc_output_3),        7,   &DO_CLK_DO_3_5V_ADDRESS,    &(disc_output_3),           6,   &DO_CLK_DO_3_5V_ADDRESS,   &(disc_output_3),          8,   &DO_CLK_DO_3_5V_ADDRESS,        HEN1_DCM_11_CHANNEL,       HEN2_DCM_11_CHANNEL,  
     &(disc_output_3),        9,   &DO_CLK_DO_3_5V_ADDRESS,    &(disc_output_3),          10,   &DO_CLK_DO_3_5V_ADDRESS,   &(disc_output_3),         11,   &DO_CLK_DO_3_5V_ADDRESS,        HEN1_DCM_12_CHANNEL,       HEN2_DCM_12_CHANNEL,  
     &(disc_output_4),        0,   &DO_CLK_DO_4_5V_ADDRESS,    &(disc_output_4),           1,   &DO_CLK_DO_4_5V_ADDRESS,   &(disc_output_4),          2,   &DO_CLK_DO_4_5V_ADDRESS,        HEN1_DCM_13_CHANNEL,       HEN2_DCM_13_CHANNEL,  
     &(disc_output_4),        3,   &DO_CLK_DO_4_5V_ADDRESS,    &(disc_output_4),           4,   &DO_CLK_DO_4_5V_ADDRESS,   &(disc_output_4),          5,   &DO_CLK_DO_4_5V_ADDRESS,        HEN1_DCM_14_CHANNEL,       HEN2_DCM_14_CHANNEL,  
     &(disc_output_4),        6,   &DO_CLK_DO_4_5V_ADDRESS,    &(disc_output_4),           7,   &DO_CLK_DO_4_5V_ADDRESS,   &(disc_output_4),          8,   &DO_CLK_DO_4_5V_ADDRESS,        HEN1_DCM_15_CHANNEL,       HEN2_DCM_15_CHANNEL,  
     &(disc_output_4),        9,   &DO_CLK_DO_4_5V_ADDRESS,    &(disc_output_4),          10,   &DO_CLK_DO_4_5V_ADDRESS,   &(disc_output_4),         11,   &DO_CLK_DO_4_5V_ADDRESS,        HEN1_DCM_16_CHANNEL,       HEN2_DCM_16_CHANNEL      
};

/****************************************************************/
/*                                                              */
/*                      LOCAL FUNCTIONS                         */
/*                                                              */
/****************************************************************/

/***************************************************************/
/* Local function : Enable_DC_Motor                            */
/***************************************************************/
void Enable_DC_Motor(T_Dc_motor a_DC_Motor)
{
	/* todo: talk to LEG about this */
    //Disc addr
    BOOLEAN          *PTR_HW_DC_MOT;

    // Disc out information
    T_Do_buffer       *disc_out_PTR;
    UNS8             disc_out_bit_position_a;
    volatile UNS32   *disc_out_addr_PTR;

    // Set the Discrete Output associated to DC_MOTx_EN to TRUE before commanding the motor
    // Extract conf from table
    PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_EN;
    disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].EN.PTR_disc_out;
    disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].EN.disc_out_bit_position;
    disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].EN.PTR_disc_out_addr;

    /* Set Data */
    *PTR_HW_DC_MOT = TRUE;
    (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) & ~((UNS32)( 1 << (disc_out_bit_position_a)) ));
    *disc_out_addr_PTR = (*disc_out_PTR).buffer;	
}

/***************************************************************/
/* Local function : Disable_DC_Motor                           */
/***************************************************************/
void Disable_DC_Motor(T_Dc_motor a_DC_Motor)
{
    /* Disc addr */
    BOOLEAN          *PTR_HW_DC_MOT;

    /* Disc out information */
    T_Do_buffer       *disc_out_PTR;
    UNS8             disc_out_bit_position_a;
    volatile UNS32   *disc_out_addr_PTR;

    /* TPU information */
    UNS8              a_ETPUCH_value;
	
	/* Set the TPU OC mode associated to DC_MOTx_HEN1 to OFF */
    a_ETPUCH_value = K_tab_dc_mot_hsi_conf[a_DC_Motor].HEN1.ETPUCH_value;
    EtpuUpdateAndStartQOMDCMotor(a_ETPUCH_value,0,REFRESH_50MS);

    /* Set the TPU OC mode associated to DC_MOTx_HEN2 to OFF */   
    a_ETPUCH_value = K_tab_dc_mot_hsi_conf[a_DC_Motor].HEN2.ETPUCH_value;
    EtpuUpdateAndStartQOMDCMotor(a_ETPUCH_value,0,REFRESH_50MS);

	/* Wating delay > 1ms before switching on the inactive FET´s */
    WaitHundredus(FET_DELAY);
		
    /* Set the Discrete Output associated to DC_MOTx_LEN1 to FALSE */
    /* Extract conf from table */
    PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_LEN1;
    disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.PTR_disc_out;
    disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.disc_out_bit_position;
    disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.PTR_disc_out_addr;

    /* Set Data */
    *PTR_HW_DC_MOT = FALSE;
    (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) & ~((UNS32)( 1 << (disc_out_bit_position_a)) ));
    *disc_out_addr_PTR = (*disc_out_PTR).buffer;

    /* Set the Discrete Output associated to DC_MOTx_LEN2 to FALSE */
    /* Extract conf from table */
    PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_LEN2;
    disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.PTR_disc_out;
    disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.disc_out_bit_position;
    disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.PTR_disc_out_addr;

    /* Set Data */
    *PTR_HW_DC_MOT = FALSE;
    (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) & ~((UNS32)( 1 << (disc_out_bit_position_a)) ));
    *disc_out_addr_PTR = (*disc_out_PTR).buffer;
	
    /* Set the Discrete Output associated to DC_MOTx_EN to FALSE */
    /* Extract conf from table */
    PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_EN;
    disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].EN.PTR_disc_out;
    disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].EN.disc_out_bit_position;
    disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].EN.PTR_disc_out_addr;

    /* Set Data */
    *PTR_HW_DC_MOT = FALSE;
    (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) & ~((UNS32)( 1 << (disc_out_bit_position_a)) ));
    *disc_out_addr_PTR = (*disc_out_PTR).buffer;	

}

/***************************************************************/
/* Local function : SwitchOFF_DC_Motor                         */
/***************************************************************/
void SwitchOFF_DC_Motor(T_Dc_motor a_DC_Motor)
{
    /* Disc addr */
    BOOLEAN          *PTR_HW_DC_MOT;

    /* Disc out information */
    T_Do_buffer       *disc_out_PTR;
    UNS8             disc_out_bit_position_a;
    volatile UNS32   *disc_out_addr_PTR;

    /* TPU information */
    UNS8              a_ETPUCH_value;
	
	/* Set the TPU OC mode associated to DC_MOTx_HEN1 to OFF */
    a_ETPUCH_value = K_tab_dc_mot_hsi_conf[a_DC_Motor].HEN1.ETPUCH_value;
    EtpuUpdateAndStartQOMDCMotor(a_ETPUCH_value,0,REFRESH_50MS);

    /* Set the TPU OC mode associated to DC_MOTx_HEN2 to OFF */   
    a_ETPUCH_value = K_tab_dc_mot_hsi_conf[a_DC_Motor].HEN2.ETPUCH_value;
    EtpuUpdateAndStartQOMDCMotor(a_ETPUCH_value,0,REFRESH_50MS);

    /* Set the Discrete Output associated to DC_MOTx_LEN1 to FALSE */
    /* Extract conf from table */
    PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_LEN1;
    disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.PTR_disc_out;
    disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.disc_out_bit_position;
    disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.PTR_disc_out_addr;

    /* Set Data */
    *PTR_HW_DC_MOT = FALSE;
    (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) & ~((UNS32)( 1 << (disc_out_bit_position_a)) ));
    *disc_out_addr_PTR = (*disc_out_PTR).buffer;

    /* Set the Discrete Output associated to DC_MOTx_LEN2 to FALSE */
    /* Extract conf from table */
    PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_LEN2;
    disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.PTR_disc_out;
    disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.disc_out_bit_position;
    disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.PTR_disc_out_addr;

    /* Set Data */
    *PTR_HW_DC_MOT = FALSE;
    (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) & ~((UNS32)( 1 << (disc_out_bit_position_a)) ));
    *disc_out_addr_PTR = (*disc_out_PTR).buffer;
	
	/* Memorize DC motor OFF by setting first DC Motor CMD TRUE */
	TAB_F_Motor_First_CMD[a_DC_Motor] = TRUE;
}


/***************************************************************/
/* Local function : CommandHIMotorOut                          */
/***************************************************************/
void CommandHIMotorOut(REAL32 a_Motor_Out_CMD, T_Dc_motor a_DC_Motor, UNS32 a_refresh_period_msec)
{
    /* Disc addr */
    BOOLEAN          *PTR_HW_DC_MOT;

    /* Disc out information */
    T_Do_buffer       *disc_out_PTR;
    UNS8             disc_out_bit_position_a;
    volatile UNS32   *disc_out_addr_PTR;

    /* ETPU information */
    UNS8              a_ETPUCH_value;

    /* IF the command memorized of DC-motor is the line LO OR it is the first command  */
    if (TAB_F_Motor_First_CMD[a_DC_Motor] == TRUE)
    {
    /* THEN */
        /* Set DC Motor is not the first command */
        TAB_F_Motor_First_CMD[a_DC_Motor] = FALSE;

        /* Set the Discrete Output associated to DC_MOTx_LEN2 to TRUE */
        /* Extract conf from table */
        PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_LEN2;
        disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.PTR_disc_out;
        disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.disc_out_bit_position;
        disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN2.PTR_disc_out_addr;

        /* Set Data */
        *PTR_HW_DC_MOT = TRUE;
        (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) | ((UNS32)(1 << (disc_out_bit_position_a)) ));
        *disc_out_addr_PTR = (*disc_out_PTR).buffer;

    }
    /* ELSE */
    else
    {
    }
    /* END IF */
   
    /* Set DC_MOT_HEN1 = SWITCH ON proportional to DC Motor Command PWR UP value */
    a_ETPUCH_value = K_tab_dc_mot_hsi_conf[a_DC_Motor].HEN1.ETPUCH_value;
    EtpuUpdateAndStartQOMDCMotor(a_ETPUCH_value,(REAL32)-1*a_Motor_Out_CMD,a_refresh_period_msec);
}


/***************************************************************/
/* Local function : CommandLOMotorOut                          */
/***************************************************************/
void CommandLOMotorOut(REAL32 a_Motor_Out_CMD, T_Dc_motor a_DC_Motor, UNS32 a_refresh_period_msec)
{
  /* Disc addr */
    BOOLEAN          *PTR_HW_DC_MOT;

    /* Disc out information */
    T_Do_buffer       *disc_out_PTR;
    UNS8             disc_out_bit_position_a;
    volatile UNS32   *disc_out_addr_PTR;

    /* ETPU information */
    UNS8              a_ETPUCH_value;

    /* IF the command memorized of DC-motor is the line HI OR it is the first command */
    if (TAB_F_Motor_First_CMD[a_DC_Motor] == TRUE)
    {
    /* THEN */
        /* Set DC Motor is not the first command */
        TAB_F_Motor_First_CMD[a_DC_Motor] = FALSE;

        /* Set the Discrete Output associated to DC_MOTx_LEN1 to TRUE */
        /* Extract conf from table */
        PTR_HW_DC_MOT = K_tab_dc_mot_conf[a_DC_Motor].PTR_HW_DC_MOT_LEN1;
        disc_out_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.PTR_disc_out;
        disc_out_bit_position_a = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.disc_out_bit_position;
        disc_out_addr_PTR = K_tab_dc_mot_hsi_conf[a_DC_Motor].LEN1.PTR_disc_out_addr;

        /* Set Data */
        *PTR_HW_DC_MOT = TRUE;
        (*disc_out_PTR).buffer = (UNS32) (((*disc_out_PTR).buffer) | ((UNS32)(1 << (disc_out_bit_position_a)) ));
        *disc_out_addr_PTR = (*disc_out_PTR).buffer;
    }
    /* ELSE */
    else
    {
    }
    /* END IF */
    
    /* Set DC_MOT_HEN2 = SWITCH ON proportional to DC Motor Command PWR UP value */  
    a_ETPUCH_value = K_tab_dc_mot_hsi_conf[a_DC_Motor].HEN2.ETPUCH_value;
    EtpuUpdateAndStartQOMDCMotor(a_ETPUCH_value,a_Motor_Out_CMD,a_refresh_period_msec);
}


/***************************************************************/
/* Global Function : DriveMotorOut                             */
/***************************************************************/
void DriveMotorOut(REAL32 a_Motor_Out_CMD, T_Dc_motor a_DC_Motor, UNS32 a_refresh_period_msec, BOOLEAN a_DC_Motor_EN)
{
	/* If the DC Motor interface is switched off */
	if (a_DC_Motor_EN == FALSE && TAB_F_EN_Motor_MEM[a_DC_Motor] == TRUE){
		/* Perform the motor disabling sequence */
		Disable_DC_Motor(a_DC_Motor);		
		/* Memorize that the motor is off */
		TAB_F_EN_Motor_MEM[a_DC_Motor] = FALSE;
		/* Memorize DC motor OFF by setting first DC Motor CMD TRUE */
		TAB_F_Motor_First_CMD[a_DC_Motor] = TRUE;	
	}
	else if (a_DC_Motor_EN == TRUE && TAB_F_EN_Motor_MEM[a_DC_Motor] == FALSE){
		/* Turn DC_MOTx_EN on before commanding the motor */
		Enable_DC_Motor(a_DC_Motor);		
		/* Memorize that the motor is on */
		TAB_F_EN_Motor_MEM[a_DC_Motor] = TRUE;	
	}
	
	/* IF DC motor interface is enabled */
	if (a_DC_Motor_EN == TRUE){
		/* IF DC Motor commans is near 0.00% */
		if ((a_Motor_Out_CMD > (REAL32)-0.01) && (a_Motor_Out_CMD < (REAL32)0.01))
		{
		/* THEN */
			/* DC Motor shall be set to OFF until next command */
			SwitchOFF_DC_Motor(a_DC_Motor);
		}
		/* ELSE */
		else
		{
			/* IF the command DC-motor is lower than 0.0 */
			if (a_Motor_Out_CMD < (REAL32)0.0)
			{
				if(TAB_F_CMD_DIR_Motor_MEM[a_DC_Motor] == CMD_LO_DC_MOTOR){
					/* Switching off the active FET s */
					SwitchOFF_DC_Motor(a_DC_Motor);
				}				
				else{
					/* Command the line HI of DC-motor */
					CommandHIMotorOut(a_Motor_Out_CMD, a_DC_Motor, a_refresh_period_msec);
				}
				/* Memorize the state of direction */
				TAB_F_CMD_DIR_Motor_MEM[a_DC_Motor] = CMD_HI_DC_MOTOR;
			}
			/* ELSE */
			else
			{
				if(TAB_F_CMD_DIR_Motor_MEM[a_DC_Motor] == CMD_HI_DC_MOTOR){
					/* Switching off the active FET s */
					SwitchOFF_DC_Motor(a_DC_Motor);
				}
				else{
					/* Command the line LO of DC-motor */
					CommandLOMotorOut(a_Motor_Out_CMD, a_DC_Motor, a_refresh_period_msec);
				}
				/* Memorize the state of direction */
				TAB_F_CMD_DIR_Motor_MEM[a_DC_Motor] = CMD_LO_DC_MOTOR;
			}
			/* END IF */
		}
		/* END IF */
	}
	/* END If */
}


/***************************************************************/
/* Global Function : InitializeDcMotorsInterface               */
/***************************************************************/
void InitializeDcMotorsInterface(void)
{
    UNS8 i;

    /* Initialize all data used by the module DC-motor */
    for (i = 0; i < NB_DCMOTOR; i++)
    {
        TAB_F_CMD_DIR_Motor_MEM[i] = FALSE;
        TAB_F_Motor_First_CMD[i] = TRUE;
    }
    
   /* Disable in DO Auxiliary port all DC Motor EN, LENx [1-16] signals  */
   DO_CLK_DO_1_5V_ADDRESS =  (UNS32)0;
   DO_CLK_DO_2_5V_ADDRESS =  (UNS32)0;
   DO_CLK_DO_3_5V_ADDRESS =  (UNS32)0;
   DO_CLK_DO_4_5V_ADDRESS =  (UNS32)0;

    /* Call EtpuInitializeQOMDCMotors function to Initialise QOM output channels */
    EtpuInitializeQOMDCMotors();   
}

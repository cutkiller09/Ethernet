/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "cpu_def.h"

#include "etpu_lb.h"
#include "etpu_LEAK_lb.h"
/* eTPU LEAK function */
#define ETPU_LEAK_SCR_INIT                  (UNS32)0x00000000
#define ETPU_HSR_INIT_LEAK                  (UNS32)0x7
#define ETPU_HSR_REQUEST_LEAK               (UNS32)0x5

#define ETPU_LEAK_REF_PIN_FCT_NB            (UNS8)    4
#define ETPU_LEAK_MUX_FCT_NB                (UNS8)    5
#define ETPU_LEAK_CONVSTART_FCT_NB          (UNS8)    6
#define ETPU_LEAK_CLOCK_FCT_NB              (UNS8)    7
#define ETPU_LEAK_TEST_FCT_NB               (UNS8)    8

#define ETPU_LEAK_OFFSET_T_SETUP_TEST        (UNS8) 0
#define ETPU_LEAK_OFFSET_POLARISATION        (UNS8) 4
#define ETPU_LEAK_OFFSET_T_CLK_PERIOD        (UNS8) 4
#define ETPU_LEAK_OFFSET_NB_MUX              (UNS8) 8
#define ETPU_LEAK_OFFSET_T_SETUP_MUX         (UNS8) 8
#define ETPU_LEAK_OFFSET_MUX0_VAL            (UNS8) 12
#define ETPU_LEAK_OFFSET_T_PULSE_WIDTH       (UNS8) 12
#define ETPU_LEAK_OFFSET_CLOCK_CHAN          (UNS8) 16
#define ETPU_LEAK_OFFSET_T_SETUP_CONF        (UNS8) 16
#define ETPU_LEAK_OFFSET_CONVSTART_CHAN      (UNS8) 20
#define ETPU_LEAK_OFFSET_T_INIT_TEST         (UNS8) 20
#define ETPU_LEAK_OFFSET_T_LEAK_TIMEOUT      (UNS8) 24
#define ETPU_LEAK_OFFSET_TAB_MUX             (UNS8) 28
#define ETPU_LEAK_OFFSET_TEST_HI             (UNS8) 52
#define ETPU_LEAK_OFFSET_TEST_LO             (UNS8) 56
#define ETPU_LEAK_OFFSET_PIN_READY           (UNS8) 64

#define ETPU_SHIFT_TO_MSB                    (UNS8) 24
#define ETPU_CLEAR_MSB                       (UNS32)0x00FFFFFF



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
/* Global function : EtpuInitializeLeak                        */
/***************************************************************/
UNS32 EtpuInitializeLeak(T_Etpu_fnc *a_leak_function, T_ETPU_LEAK_TIME *a_leak_timings, T_ETPU_LEAK_CONF *a_leak_configuration)
{
    UNS32 parameter_end_add;
    UNS32 *ram_PTR;
    UNS8 i;

    /* parameter_start_add is a relative address */
    /* The function parameter start address value must be a multiple of 8 */
    /* The value has to be multiply by to get the absolute parameter address seen at host side */
    /* -> Check the parameter is a multiple of 8. */
    /* If not, increment the address to have the next multiple of 8 */
    if (((a_leak_function->parameter_start_add) % 8u) != 0u)
    {
        a_leak_function->parameter_start_add = a_leak_function->parameter_start_add
                                          + (8u -((a_leak_function->parameter_start_add) % 8u));
    }
    else
    {
    }    
    
    /* Initialize channels: */
    /* - Clear priority to disable channels */
    /* - Configure channels */
    
    /* 1/ MUX0 channel : reference channel */
    ETPU.CHAN[a_leak_function->channel].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[a_leak_function->channel].SCR.R = ETPU_LEAK_SCR_INIT;

    /* MUX_0 channel configuration */
    /*   - CIE  = 1                            Interrupt enabled for master channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_LEAK_MUX_A0_FCT_NB                                           */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_leak_function->channel].CR.R = 
                    (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                    (UNS32)(a_leak_function->priority << ETPU_SCR_CPR_OFFSET) +
                    (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                    (UNS32)(ETPU_LEAK_REF_PIN_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                    (UNS32)(a_leak_function->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);
    
    /* 2/ MUX channels */
    for (i = 0 ; i < (UNS8)(NB_MUX_SIGNALS-1) ; i++ )
    {
        ETPU.CHAN[a_leak_function->channel+ a_leak_configuration->TAB_mux[i].pin_offset].CR.B.CPR = (VUNS32)ETPU_DISABLED;
        ETPU.CHAN[a_leak_function->channel+ a_leak_configuration->TAB_mux[i].pin_offset].SCR.R = ETPU_LEAK_SCR_INIT;

        /* MUX channels configuration */
        /*   - CIE  = 1                            Interrupt enabled for master channel */
        /*   - DTRE = 0                            Data transfer disabled               */
        /*   - CPR  = priority                     Function priority                    */
        /*   - ETCS = 0                            Standard entry table used            */
        /*   - CFS  = ETPU_LEAK_MUX_A1_FCT_NB                                           */
        /*   - ODIS = 0                            OFF                                  */
        /*   - OPOL = 0                            NA                                   */
        /*   - CPBA = parameter_start_address / 8                                       */
        ETPU.CHAN[a_leak_function->channel + a_leak_configuration->TAB_mux[i].pin_offset].CR.R = 
                    (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                    (UNS32)(a_leak_function->priority << ETPU_SCR_CPR_OFFSET) +
                    (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                    (UNS32)(ETPU_LEAK_MUX_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                    (UNS32)(a_leak_function->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);
    }

    /* 3/ TEST channels */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->test_hi.pin_offset].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->test_lo.pin_offset].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->test_hi.pin_offset].SCR.R = ETPU_LEAK_SCR_INIT;
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->test_lo.pin_offset].SCR.R = ETPU_LEAK_SCR_INIT;

    /* TEST_HI channel configuration */
    /*   - CIE  = 1                            Interrupt enabled for master channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_LEAK_TEST_HI_FCT_NB                                          */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->test_hi.pin_offset].CR.R =
                    (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                    (UNS32)(a_leak_function->priority << ETPU_SCR_CPR_OFFSET) +
                    (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                    (UNS32)(ETPU_LEAK_TEST_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                    (UNS32)(a_leak_function->parameter_start_add >>(UNS32)ETPU_SCR_CPBA_OFFSET);
                    
    /* TEST_LO channel configuration */
    /*   - CIE  = 1                            Interrupt enabled for master channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_LEAK_TEST_LO_FCT_NB                                          */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->test_lo.pin_offset].CR.R = 
                    (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                    (UNS32)(a_leak_function->priority << ETPU_SCR_CPR_OFFSET) +
                    (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                    (UNS32)(ETPU_LEAK_TEST_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                    (UNS32)(a_leak_function->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);                    
    
    
    /* 4/ CLOCK channel */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->clock_offset].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->clock_offset].SCR.R = ETPU_LEAK_SCR_INIT;

    /* Clock channel configuration */
    /*   - CIE  = 1                            Interrupt enabled for master channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_LEAK_CLOCK_FCT_NB                                            */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->clock_offset ].CR.R = 
                    (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                    (UNS32)(a_leak_function->priority << ETPU_SCR_CPR_OFFSET) +
                    (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                    (UNS32)(ETPU_LEAK_CLOCK_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                    (UNS32)(a_leak_function->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);
    
    /* 5/ CONVSTART channel */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->convstart_offset].CR.B.CPR = (VUNS32)ETPU_DISABLED;
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->convstart_offset].SCR.R = ETPU_LEAK_SCR_INIT;

    /* CONVSTART channel configuration */
    /*   - CIE  = 1                            Interrupt enabled for master channel */
    /*   - DTRE = 0                            Data transfer disabled               */
    /*   - CPR  = priority                     Function priority                    */
    /*   - ETCS = 0                            Standard entry table used            */
    /*   - CFS  = ETPU_LEAK_CONVSTART_FCT_NB                                        */
    /*   - ODIS = 0                            OFF                                  */
    /*   - OPOL = 0                            NA                                   */
    /*   - CPBA = parameter_start_address / 8                                       */
    ETPU.CHAN[a_leak_function->channel + a_leak_configuration->convstart_offset].CR.R = 
                    (UNS32)(ETPU_ENABLE_CHAN_INTERRUPT << ETPU_SCR_CIE_OFFSET) +
                    (UNS32)(a_leak_function->priority << ETPU_SCR_CPR_OFFSET) +
                    (UNS32)(STANDARD_TABLE << ETPU_SCR_ETCS_OFFSET) +
                    (UNS32)(ETPU_LEAK_CONVSTART_FCT_NB << ETPU_SCR_CFS_OFFSET) +
                    (UNS32)(a_leak_function->parameter_start_add >> (UNS32)ETPU_SCR_CPBA_OFFSET);

    /* Initialise RAM function area to 0 */
    /* Get the end of parameter area address: parameter start + last parameter offset  + last parameter size*/
    parameter_end_add = (UNS32)(a_leak_function->parameter_start_add
                               + (UNS32)ETPU_LEAK_OFFSET_PIN_READY + 4u);

    /* Set data RAM to 0 */
    ram_PTR = (UNS32 *) (a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS);
    while ( (UNS32)ram_PTR < (parameter_end_add + ETPU_DATA_RAM_START_ABS))
    {
       *ram_PTR = 0x0;
       ram_PTR ++;
    }

    /* Initialise function parameters */
    /* - T_SETUP_TEST timing */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_SETUP_TEST );
    *ram_PTR = a_leak_timings->t_setup_test;
    
    /* - T_CLOCK_PERIOD period */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_CLK_PERIOD );
    *ram_PTR = a_leak_timings->t_clock_period;

    /* - NB_MUX + T_SETUP_MUX timing */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_SETUP_MUX );
    *ram_PTR = (a_leak_timings->t_setup_mux) | (UNS32)((a_leak_configuration->nb_mux_signals)<<ETPU_SHIFT_TO_MSB);

    /* - T_PULSE_WIDTH timing */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_PULSE_WIDTH );
    *ram_PTR = a_leak_timings->t_pulse_width;

    /* - CLOCK_CHAN + T_SETUP_CONF timing */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_SETUP_CONF );
    *ram_PTR = (a_leak_timings->t_setup_conf) | (UNS32)((a_leak_configuration->clock_offset)<<ETPU_SHIFT_TO_MSB);

    /* - CONVSTART_CHAN + T_INIT_TEST timing */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_INIT_TEST );
    *ram_PTR = (a_leak_timings->t_init_test) | (UNS32)((a_leak_configuration->convstart_offset)<<ETPU_SHIFT_TO_MSB);

    /* - T_LEAK_TIMEOUT timing */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_T_LEAK_TIMEOUT );
    *ram_PTR = a_leak_timings->t_leak_timeout;
    
    /* - MUX table */
    for (i = 0 ; i < (UNS8)(NB_MUX_SIGNALS-1) ; i++ )
    {
        ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_TAB_MUX + (UNS32)(4*i) );
        *ram_PTR = a_leak_configuration->TAB_mux[i].pin_offset;
    }

    /* - TEST_HI channel */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_TEST_HI );
    *ram_PTR = a_leak_configuration->test_hi.pin_offset; 
    
    /* - TEST_LO channel */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_TEST_LO );
    *ram_PTR = a_leak_configuration->test_lo.pin_offset; 
    
    /* Request initialisation HSR to MUX_A0 channel*/
    ETPU.CHAN[a_leak_function->channel].HSRR.R = ETPU_HSR_INIT_LEAK;

    /* Return end of parameter area address */
    return parameter_end_add;
}

/***************************************************************/
/* Global function : EtpuStartLeakConversion                   */
/***************************************************************/
void EtpuStartLeakConversion(T_Etpu_fnc *a_leak_function, UNS8 a_acq_polarisation, T_ETPU_LEAK_CONF *a_leak_configuration)
{
     UNS32 *ram_PTR;
     UNS8 i;

    /* Polarisation  */
    ram_PTR = (UNS32*) (a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_POLARISATION);
    *ram_PTR &= ETPU_CLEAR_MSB;
    *ram_PTR |= ((UNS32) (a_acq_polarisation << ETPU_SHIFT_TO_MSB));   
    
    /* Pin setup */
    /* - MUX0 value */
    ram_PTR = (UNS32*) (a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_MUX0_VAL);
    *ram_PTR &= ETPU_CLEAR_MSB;
    *ram_PTR |= (UNS32)(a_leak_configuration->mux0_value << ETPU_SHIFT_TO_MSB);
    
    /* - Other MUX */
    for (i = 0 ; i < (UNS8)(NB_MUX_SIGNALS-1) ; i++ )
    {
        ram_PTR = (UNS32*) (a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_TAB_MUX + (UNS32)(4*i));
        *ram_PTR &= ETPU_CLEAR_MSB;
        *ram_PTR |= (UNS32)(a_leak_configuration->TAB_mux[i].pin_value << (UNS32)ETPU_SHIFT_TO_MSB);
    }

    /* - TEST_HI channel */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_TEST_HI );
    *ram_PTR &= ETPU_CLEAR_MSB;
    *ram_PTR |= (UNS32)(a_leak_configuration->test_hi.pin_value << (UNS32)ETPU_SHIFT_TO_MSB); 
    
    /* - TEST_LO channel */
    ram_PTR = (UNS32 *)(a_leak_function->parameter_start_add + ETPU_DATA_RAM_START_ABS + (UNS32)ETPU_LEAK_OFFSET_TEST_LO );
    *ram_PTR &= ETPU_CLEAR_MSB;
    *ram_PTR |= (UNS32)(a_leak_configuration->test_lo.pin_value << (UNS32)ETPU_SHIFT_TO_MSB); 
        
   /* Request transmission setting HSR 5 on master channel*/
   ETPU.CHAN[a_leak_function->channel].HSRR.R = ETPU_HSR_REQUEST_LEAK;
}

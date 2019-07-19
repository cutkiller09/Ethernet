#ifndef __ETPU_LEAK_LB_H__
#define __ETPU_LEAK_LB_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL TYPES                           */
/*                                                             */
/***************************************************************/  
typedef struct
{
    BOOLEAN pin_value;
    UNS8   pin_offset;
}
T_ETPU_LEAK_PIN;

typedef struct
{
    UNS32 t_clock_period;
    UNS32 t_init_test;
    UNS32 t_setup_test;
    UNS32 t_setup_mux;
    UNS32 t_setup_conf;
    UNS32 t_pulse_width;
    UNS32 t_leak_timeout;
}
T_ETPU_LEAK_TIME;


#define NB_MUX_SIGNALS      (UNS8)6
typedef struct
{
    UNS8 nb_mux_signals;
    UNS8 mux0_value;
    T_ETPU_LEAK_PIN TAB_mux[NB_MUX_SIGNALS-1];
    T_ETPU_LEAK_PIN test_hi;
    T_ETPU_LEAK_PIN test_lo;
    UNS8 clock_offset;
    UNS8 convstart_offset;    
}
T_ETPU_LEAK_CONF;

/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/

/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
extern UNS32 EtpuInitializeLeak(T_Etpu_fnc *a_leak_function, T_ETPU_LEAK_TIME *a_leak_timings, T_ETPU_LEAK_CONF *a_leak_configuration);
extern void EtpuStartLeakConversion(T_Etpu_fnc *a_leak_function, UNS8 a_acq_polarisation, T_ETPU_LEAK_CONF *a_leak_configuration);
#endif
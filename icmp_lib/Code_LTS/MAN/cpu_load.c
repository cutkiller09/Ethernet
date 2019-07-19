/***************************************************************/
/* FUNCTION : Initialize PPC5554 registers                     */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "hard_def.h"

#include "cpu_lb.h"
#include "main_tsk.h"

#include "cpu_load.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
UNS32 CPT_ARINC_RX_occurrence;
UNS32 CPT_CAN_RX_occurrence;

/***************************************************************/
/*                                                             */
/*                       GLOBAL CONSTANTS                      */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      LOCAL CONSTANTS                        */
/*                                                             */
/***************************************************************/
#define MAIN_TSK_SEGMENTATION   (UNS16)20
#define SYSTEM_CLOCK_PERIOD_MS  (REAL32)(((REAL32)1.0 / (REAL32)SYSTEM_CLOCK) * (REAL32)1000.0)
#define K_ARINC_TASK_DURATION_IN_CLK ((UNS32)1598) /*! ARINCTaskRXy function last about 14.27us ( i.e. 1598. clock time */
#define K_CAN_TASK_DURATION_IN_CLK ((UNS32)1395) /*! CANxHandler function last about 12.46us ( i.e. 1395. clock time */


/***************************************************************/
/*                                                             */
/*                         LOCAL TYPES                         */
/*                                                             */
/***************************************************************/
typedef struct
{
    BOOLEAN F_task_started;
    UNS16   occurrence_number;
    UNS32   CPT_ARINC_RX_occurrence_MEM;
    UNS32   CPT_CAN_RX_occurrence_MEM;
    T_Time  real_start_time;
    T_Time  computed_start_time;
    T_Time  duration;
}
T_TaskTime;
typedef struct
{
    UNS32  PIT_max_load;
    REAL32 max_load;
    REAL32 average_load;
    REAL32 current_load;
}
T_TasksDetails;


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/
T_TaskTime     TAB_time[MAIN_TSK_SEGMENTATION][DUMMY];
UNS16          measure_index;
UNS32          CPU_LOAD_MAX_PIT_number;
REAL32         CPU_LOAD_current;
REAL32         CPU_load_MAX;
REAL32         CPU_LOAD_average;
T_TasksDetails TAB_CPU_LOAD_details[DUMMY];


/***************************************************************/
/* Local function : SubstractTime                              */
/***************************************************************/
T_Time SubstractTime(T_Time a_A_time, T_Time a_B_time)
{
    T_Time A_moins_B_time;

    /* IF a_A_time LSB value is less than a_B_time LSB value */
    if (a_A_time.LSB < a_B_time.LSB)
    /* THEN */
    {
        /* Return LSB and MSB value with carry */
        A_moins_B_time.LSB = ~(a_B_time.LSB - a_A_time.LSB) + 1u;
        A_moins_B_time.MSB = a_A_time.MSB - a_B_time.MSB - 1u;
    }
    /* ELSE */
    else
    {
        /* Return LSB and MSB value */
        A_moins_B_time.LSB = a_A_time.LSB - a_B_time.LSB;
        A_moins_B_time.MSB = a_A_time.MSB - a_B_time.MSB;
    }
    /* END IF */

    return(A_moins_B_time);
}


/***************************************************************/
/* Local function : AddTime                                    */
/***************************************************************/
T_Time AddTime(T_Time a_A_time, T_Time a_B_time)
{
    T_Time A_plus_B_time;

    /* IF the sum of the a_A_time and a_B_time LSB value is less than initial LSB values */
    if (((a_A_time.LSB + a_B_time.LSB) < a_A_time.LSB) ||
    ((a_A_time.LSB + a_B_time.LSB) < a_B_time.LSB))
    /* THEN */
    {
        /* Return LSB and MSB value with carry */
        A_plus_B_time.LSB = a_A_time.LSB + a_B_time.LSB;
        A_plus_B_time.MSB = a_A_time.MSB + a_B_time.MSB + 1u;
    }
    /* ELSE */
    else
    {
        /* Return LSB and MSB value */
        A_plus_B_time.LSB = a_A_time.LSB + a_B_time.LSB;
        A_plus_B_time.MSB = a_A_time.MSB + a_B_time.MSB;
    }
    /* END IF */

    return(A_plus_B_time);
}


/***************************************************************/
/* Global function : InitializeCPU_Load                        */
/***************************************************************/
void InitializeCPU_Load(void)
{
    UNS16 i;
    UNS8 j;

    /* Initialize data for CPU load measures */
    for(i = 0 ; i < MAIN_TSK_SEGMENTATION ; i ++)
    {
        for(j = 0 ; j < DUMMY ; j ++)
        {
            TAB_time[i][j].F_task_started          = FALSE;
            TAB_time[i][j].occurrence_number       = (UNS16)0;
            TAB_time[i][j].real_start_time.LSB     = (UNS32)0;
            TAB_time[i][j].real_start_time.MSB     = (UNS32)0;
            TAB_time[i][j].computed_start_time.LSB = (UNS32)0;
            TAB_time[i][j].computed_start_time.MSB = (UNS32)0;
            TAB_time[i][j].duration.LSB            = (UNS32)0;
            TAB_time[i][j].duration.MSB            = (UNS32)0;
        }
    }
    for (i = 0 ; i < DUMMY ; i ++)
    {
        TAB_CPU_LOAD_details[i].PIT_max_load = (UNS32)0;
        TAB_CPU_LOAD_details[i].max_load     = (REAL32)0.0;
        TAB_CPU_LOAD_details[i].average_load = (REAL32)0.0;
        TAB_CPU_LOAD_details[i].current_load = (REAL32)0.0;
    }
    measure_index    = (UNS16)0;
    CPU_LOAD_MAX_PIT_number   = (UNS32)0;
    CPU_LOAD_current = (REAL32)0.0;
    CPU_load_MAX     = (REAL32)0.0;
    CPU_LOAD_average = (REAL32)0.0;

    /* Initialize global data */
    CPT_ARINC_RX_occurrence = (UNS32)0;
    CPT_CAN_RX_occurrence = (UNS32)0;
}


/***************************************************************/
/* Global function : StartTaskTimeMeasurement                  */
/***************************************************************/
void StartTaskTimeMeasurement(T_TaskID a_task_ID)
{
    /* Mask the interrupts */
    MaskInterruptINTC();
    
    /* IF the task is started */
    if (TAB_time[measure_index][a_task_ID].occurrence_number == 0)
    /* THEN */
    {
        /* Set the task started flag to TRUE */
        TAB_time[measure_index][a_task_ID].F_task_started = TRUE;
        /* Read the starting time and save it as real start time */
        TAB_time[measure_index][a_task_ID].real_start_time = GetTime();
        /* Save the real start time as computed start time */
        TAB_time[measure_index][a_task_ID].computed_start_time = TAB_time[measure_index][a_task_ID].real_start_time;
        /* Set the duration time to 0 */
        TAB_time[measure_index][a_task_ID].duration.LSB = (UNS32)0;
        TAB_time[measure_index][a_task_ID].duration.MSB = (UNS32)0;
    }
    /* ELSE */
    else
    {
        /* Set the task started flag to TRUE */
        TAB_time[measure_index][a_task_ID].F_task_started = TRUE;
        /* Read the starting time and save it as real start time */
        TAB_time[measure_index][a_task_ID].real_start_time = GetTime();
        /* Save the difference between the real start time and the duration as computed start time */
        TAB_time[measure_index][a_task_ID].computed_start_time = SubstractTime(TAB_time[measure_index][a_task_ID].real_start_time,
        TAB_time[measure_index][a_task_ID].duration);
    }
    
    /* Save CPT_ARINC_RX_occurrence and CPT_CAN_RX_occurrence for current task */ 
    TAB_time[measure_index][a_task_ID].CPT_ARINC_RX_occurrence_MEM = CPT_ARINC_RX_occurrence;
    TAB_time[measure_index][a_task_ID].CPT_CAN_RX_occurrence_MEM   = CPT_CAN_RX_occurrence;
    
    /* Unmask the interrupts */
    UnmaskInterruptINTC();
}


/***************************************************************/
/* Global function : StopTaskTimeMeasurement                   */
/***************************************************************/
void StopTaskTimeMeasurement(T_TaskID a_task_ID)
{
    UNS8 i;
    T_Time task_duration, temp_time, can_time, arinc_time;

    /* Mask the interrupts */
    MaskInterruptINTC();
    /* Set the task started flag to FALSE */
    TAB_time[measure_index][a_task_ID].F_task_started = FALSE;
    /* Compute the duration of the current occurrence of the task */
    temp_time = GetTime();
    task_duration = SubstractTime(temp_time, TAB_time[measure_index][a_task_ID].computed_start_time);
    
    /* Remove time of ARINC and CAN interrupt */    
    arinc_time.LSB = (CPT_ARINC_RX_occurrence - TAB_time[measure_index][a_task_ID].CPT_ARINC_RX_occurrence_MEM) * K_ARINC_TASK_DURATION_IN_CLK;
    arinc_time.MSB = 0;
    can_time.LSB   = (CPT_CAN_RX_occurrence   - TAB_time[measure_index][a_task_ID].CPT_CAN_RX_occurrence_MEM  ) * K_CAN_TASK_DURATION_IN_CLK;
    can_time.MSB = 0;
    task_duration = SubstractTime(task_duration, arinc_time);
    task_duration = SubstractTime(task_duration, can_time);

    /* Unmask the interrupts */
    UnmaskInterruptINTC();

    /* Update the duration of the task with the duration of the current occurrence of the task */
    task_duration = SubstractTime(task_duration, TAB_time[measure_index][a_task_ID].duration);
    TAB_time[measure_index][a_task_ID].duration = AddTime(TAB_time[measure_index][a_task_ID].duration, task_duration);

    /* Increase the number of occurrence of task */
    TAB_time[measure_index][a_task_ID].occurrence_number++;

    /* FOR all the tasks DO */
    for(i = 0; i < DUMMY; i++)
    {
        /* IF the task has started */
        if (TAB_time[measure_index][i].F_task_started == TRUE)
        /* THEN */
        {
            /* Add the duration of the current occurrence of the task to lower priority task computed start time */
            TAB_time[measure_index][i].computed_start_time = AddTime(TAB_time[measure_index][i].computed_start_time, task_duration);
        }
        else
        {
        }
        /* END IF */
    }
    /* END FOR */
}


/***************************************************************/
/* Global function : CalculateCPULoad                          */
/***************************************************************/
void CalculateCPULoad(void)
{
    UNS8 i;

    /* IF PIT number is greater than 0 (do not calculate CPU load the first time) */
    if (MC_PIT_NUMBER > 0u)
    /* THEN */
    {
        /* Disable interrupt */
        MaskInterruptINTC();

        /* Compute the total duration of all the ARINC tasks triggered this PIT */
        TAB_time[measure_index][ARINC].duration.LSB = CPT_ARINC_RX_occurrence * K_ARINC_TASK_DURATION_IN_CLK;
        /* Reset the number of ARINC tasks triggered this PIT */
        CPT_ARINC_RX_occurrence = 0;

        /* Compute the total duration of all the CAN tasks triggered this PIT */
        TAB_time[measure_index][CAN].duration.LSB = CPT_CAN_RX_occurrence * K_CAN_TASK_DURATION_IN_CLK;
        /* Reset the number of CAN tasks triggered this PIT */
        CPT_CAN_RX_occurrence = 0;

        /* Reset current CPU load */
        CPU_LOAD_current = (REAL32)0.0;
        
        /* FOR each task DO */
        for(i = 0 ; i < DUMMY ; i ++)
        {
            /* Store the duration of the task */
            TAB_CPU_LOAD_details[i].current_load = (REAL32)TAB_time[measure_index][i].duration.LSB;
            /* Add the duration time of the task to the current CPU load */
            CPU_LOAD_current += (REAL32)TAB_time[measure_index][i].duration.LSB;
            /* Reset the occurrence number of the task for the starting PIT */
            TAB_time[measure_index][i].occurrence_number = 0;
        }
        /* END FOR */

        /************************************************************/
        /*! SYSTEM_CLOCK is 112MHz so its period is                 */
        /*! 8.9285 x 10^-9 seconds              (9.9285 x 10^-6 ms) */
        /*! PIT_PERIOD is                                           */
        /*! 25 x 10^-3 seconds                              (25 ms) */
        /************************************************************/
        /*! CALCUL                                                  */
        /*!  (1). CPU_LOAD_current x SYSTEM_CLOCK  (duration in ms) */
        /*!  (2). / MAINTASK_PIT_PERIOD                     (ratio) */
        /*!  (3). x 100                                (ratio in %) */
        /************************************************************/
        /* FOR each task DO */
        for(i = 0 ; i < DUMMY ; i ++)
        {
            /* Set the load in percentage */
            TAB_CPU_LOAD_details[i].current_load = (SYSTEM_CLOCK_PERIOD_MS *  TAB_CPU_LOAD_details[i].current_load) / (REAL32)PIT_PERIOD * (REAL32)100.0;
        }
        /* END FOR */
        /* Set the CPU load in percentage */
        CPU_LOAD_current = (SYSTEM_CLOCK_PERIOD_MS * CPU_LOAD_current) / (REAL32)PIT_PERIOD * (REAL32)100.0;

        /* Update the measurement index */
        measure_index++;
        if (measure_index >= MAIN_TSK_SEGMENTATION)
        {
            measure_index = 0;
        }
        else
        {
        }

        /* Enable interrupt */
        UnmaskInterruptINTC();
        
        /* FOR each task DO */
        for(i = 0 ; i < DUMMY ; i ++)
        {
            /* IF the load on the last PIT is greater than the memorized max load */
            if (TAB_CPU_LOAD_details[i].current_load > TAB_CPU_LOAD_details[i].max_load)
            /* THEN */
            {
                /* Memorize the load as max load */
                TAB_CPU_LOAD_details[i].max_load = TAB_CPU_LOAD_details[i].current_load;
                /* Memorize the last PIT number as max PIT */
                TAB_CPU_LOAD_details[i].PIT_max_load = MC_PIT_NUMBER - 1u;
            }
            else
            {
            }
            /* END IF */
        }
        /* END FOR */
        /* IF the CPU load on the last PIT is greater than the memorized CPU load */
        if (CPU_LOAD_current > CPU_load_MAX)
        /* THEN */
        {
            /* Memorize the CPU load as max load */
            CPU_load_MAX = CPU_LOAD_current;
            /* Memorize the last PIT number as max PIT */
            CPU_LOAD_MAX_PIT_number = MC_PIT_NUMBER - 1u;
        }
        else
        {
        }
        /* END IF */

        /* FOR each task DO */
        for (i = 0 ; i < DUMMY ; i ++)
        {
            /* Compute the average of load since the first PIT */
            TAB_CPU_LOAD_details[i].average_load = ((REAL32)(MC_PIT_NUMBER - 1u) * TAB_CPU_LOAD_details[i].average_load) + TAB_CPU_LOAD_details[i].current_load;
            TAB_CPU_LOAD_details[i].average_load = TAB_CPU_LOAD_details[i].average_load / (REAL32)MC_PIT_NUMBER;
        }
        /* END FOR */
        /* Compute the average of CPU load since the first PIT */
        CPU_LOAD_average = ((REAL32)(MC_PIT_NUMBER - 1u) * CPU_LOAD_average) + CPU_LOAD_current;
        CPU_LOAD_average = CPU_LOAD_average / (REAL32)MC_PIT_NUMBER;
    }
    else
    {
    }
    /* END IF */
}

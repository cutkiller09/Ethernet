#ifndef __STANDARD_H__
#define __STANDARD_H__
/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/


/* To force the compiler to not use the register r14 */
/* This register will be used to memorize the BITE partition stack pointer */
#pragma global_register __SP_BITE_PARTITION=r14

/* To force the compiler to not use the register r15 */
/* This register will be used to memorize the common stack pointer */
#pragma global_register __SP_COMMON_SOFTWARE=r15

/* To force the compiler to not use the register r16 */
/* This register will be used to memorize the exception */
#pragma global_register __EXCEPTION_SOFTWARE=r16

/* To force the compiler to not use the register r17 */
/* This register will be used memorize the current INTC CPR priority value */
#pragma global_register __EXCEPTION_SOFTWARE=r17

/* To force the compiler to not use the register r18 */
/* This register will be used to memorize if the stack pointer shall change to Control or BITE zone */
#pragma global_register __EXCEPTION_SOFTWARE=r18


/***************************************************************/
/*                                                             */
/*                      GLOBAL TYPES                           */
/*                                                             */
/***************************************************************/
typedef unsigned char BOOLEAN;

typedef signed char INT8;
typedef short int INT16;
typedef volatile signed short VINT16;
typedef int INT32;
typedef volatile signed int VINT32;
typedef long long INT64;
typedef volatile signed long long VINT64;

typedef unsigned char UNS8;
typedef volatile unsigned char VUNS8;
typedef unsigned short int UNS16;
typedef volatile unsigned short VUNS16;
typedef unsigned int UNS32;
typedef volatile unsigned int VUNS32;
typedef unsigned long long UNS64;
typedef volatile unsigned long long VUNS64;

typedef float REAL32;


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
#define FALSE	(BOOLEAN)0
#define TRUE	(BOOLEAN)1

#define NULL	((void* ) 0)

#define ZERO_C	(0U)
#define ONE_C	(1U) 
#define TWO_C	(2U)
#define THREE_C	(3U)
#define FOUR_C	(4U)

/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL FUNCTIONS                       */
/*                                                             */
/***************************************************************/
#endif
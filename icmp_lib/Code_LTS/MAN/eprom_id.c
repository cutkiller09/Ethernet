/***************************************************************/
/* FUNCTION : Defines the program identification, date,        */
/*            owner and check-sum correction                   */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "eprom_id.h"


/***************************************************************/
/*                                                             */
/*                      GLOBAL DATA                            */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/
/* The owner shall be "COPYRIGHT LTS"                              */
const UNS8  K_TAB_owner[]              = "COPYRIGHT LTS";

/*******************************************************************/
/* The date shall be format "DD MMM YYYY"                          */
/* MMM shall contain the 3 first characters of the month           */
/*******************************************************************/
const UNS8  K_TAB_date[]               = "01 AVR 2019";

/*******************************************************************/
/* The SW PN shall be format for unformal release "L91152AxTrrrrCC"*/
/*               with x the identifier of the software             */
/*               with rrrr the svn revision of the software        */
/*               with NN the next tag of the software              */
/* The SW PN shall be format for formal release "BSP5554NN"        */
/*               with x the identifier of the software             */
/*               with NN the next tag of the software              */
/*******************************************************************/
const UNS8  K_TAB_soft_ident[]         = "L91152AET0061AA";


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
/*                                                             */
/*                      LOCAL DATA                             */
/*                                                             */
/***************************************************************/

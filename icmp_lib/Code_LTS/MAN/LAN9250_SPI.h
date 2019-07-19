/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#ifndef __LAN9250_SPI_H__  /* test for multiple inclusion */
#define __LAN9250_SPI_H__

/***************************************************************/
/*                                                             */
/*                         GLOBAL TYPES                        */
/*                                                             */
/***************************************************************/
enum continuous_accesses
{
	AUTO_DECREMENTED,
	AUTO_INCREMENTED,
	SINGLE_REGISTER
};
/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/


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
extern void ReadRegistersLAN9250(UNS16 address_register, UNS32* a_read_input_PTR);
extern void WriteRegistersLAN9250(UNS16 address_register, UNS32 value_towrite);
extern void ClearLAN9250RegistersBits(UNS16 address_register, UNS8 bit_number);
extern void SetLAN9250RegistersBits(UNS16 address_register, UNS8 bit_number);
#endif /*__LAN9250_SPI_H__*/

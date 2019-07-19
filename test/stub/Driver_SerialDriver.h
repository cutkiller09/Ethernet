
#pragma once

#define DRVSERIAL_SERIAL_PORT_NAME_MAX_LEN		32

typedef enum {
	E_DRVSERIAL_CLOSED = -1
} descriptor_state_type ;

/* Parity mode options */
typedef enum {
	E_DRVSERIAL_NO_PARITY = 0,
	E_DRVSERIAL_ODD_PARITY = 1,
	E_DRVSERIAL_EVEN_PARITY = 2
} parity_mode_type ;


/* Configuration structure of a serial port */
typedef struct {
	/* Serial port filename */
	char	sz_serialport_name[DRVSERIAL_SERIAL_PORT_NAME_MAX_LEN];
	/* Serial port baudrate: 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600 */
	uint32	u32_baudrate ;
	/* Size of a byte (7 or 8) */
	uint8   u8_bitsize;
	/* Parity mode: none, odd or even */
	parity_mode_type t_parity_mode ;
	/* Stop bit presence */
	bool b_stopbitena ;
} serialdrv_cfg_type ;


extern Std_ReturnType gDrvSerial_t_state_of_function ;
extern sint32 gDrvSerial_current_s32_written ;
extern sint32 gDrvSerial_current_s32_read ;
extern uint8 gDrvSerial_au8_read_buffer[4096] ;


Std_ReturnType DrvSerial_Initialize(void);
Std_ReturnType DrvSerial_Open( const serialdrv_cfg_type * const t_configuration , sint32 * const ps32_port_desc ) ;
Std_ReturnType DrvSerial_Close( sint32 * const ps32_port_desc ) ;
Std_ReturnType DrvSerial_Receive( const sint32 s32_port_desc , uint8 * const au8_buffer, const uint32 u32_buffer_size , sint32 * const ps32_read ) ;
Std_ReturnType DrvSerial_Send( const sint32 s32_port_desc , const uint8 * const au8_buffer, const uint32 u32_buffer_size , sint32 * const ps32_written ) ;
Std_ReturnType DrvSerial_Flush( const sint32 s32_port_desc ) ;

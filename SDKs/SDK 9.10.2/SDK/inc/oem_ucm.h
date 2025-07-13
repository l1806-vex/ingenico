#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_UCM_H_INCLUDED__
#define __OEM_UCM_H_INCLUDED__

#ifdef __FRAMEWORK_TELIUM_2__
#include "oem_ucm_deprecated.h"
#endif

/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*
======================================================================
					List of Defines
======================================================================
*/

// FIOCTL
#define COM_FIOCTL_SET_DTR              	0x8008	/*!< Turn on DTR Com Signal if signal supported */


// FORMAT: Programming specifical MDB mode a serial port COM
// format (		unsigned char *filename,	COMx serial port
//				int speed,					baud rate (9600)
//				unsigned char lenght_byte,	7 or 8 bits
//				unsigned char stop_bits,	1 or 2 stop bits
//				unsigned char config_MDB,	
//				unsigned char address_MDB1,	address MDB in slave mode
//				unsigned char address_MDB2)	address MDB in slave mode
//
// config mdb:
#define EMI_ACTIVATED		0x10	/*!< unused */
#define MULTIDROP				0x08	/*!< Multi Drop 9bits*/
#define MASTER					0x04	/*!< Slave / Master */
#define SLAVE						0x00	/*!< Slave / Master */
#define TYP_ADD					0x02	/*!< no type address / type adress */
#define NO_TYP_ADD			0x00	/*!< no type address / type adress */

// FORMAT: Programming a serial port COM
// format (		unsigned char *filename,	COMx serial port
//				int speed,					baud rate (300 to 115200)
//				unsigned char lenght_byte,	7 or 8 bits
//				unsigned char stop_bits,	1 or 2 stop bits
//				unsigned char parity,		PARITY/NO_PARITY
//				unsigned char parity mode,	EVEN/ODD
//				unsigned char mode)			
//
// mode
#define MODE_HANDSHAKING	0x01	/*!< hardware handshaking (CTS/RTS)			 */
#define MODE_MODEM				0x02	/*!< management of signals DCD, RI, DSR */

// additionnal signal for mask_event or status (other signals are defined in oem.h)
#define RI                	 0x08 	/*!< Ring Indicator */
#define DSR                	 0x04 	/*!< Data Set Ready */

/*! @}  */ 


#endif   // __OEM_UCM_H_INCLUDED__
 
#ifdef __cplusplus
}
#endif

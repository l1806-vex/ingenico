/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_UCM_H
#define OEM_UCM_H

/*
======================================================================
					List of Defines
======================================================================
*/

// FIOCTL
//#define COM_FIOCTL_SET_RTS              0x8000	// defined in oem_com.h
//#define COM_FIOCTL_CLEAR_RTS            0x8001	// defined in oem_com.h
//#define COM_FIOCTL_GET_CTS              0x8003	// defined in oem_com.h
//#define COM_FIOCTL_SET_RECEIVER_TIMEOUT 0x8004	// defined in oem_com.h
//#define COM_FIOCTL_GET_RECEIVER_TIMEOUT 0x8005	// defined in oem_com.h
//#define COM_FIOCTL_LOCAL_LOOPBACK       0x8006	// defined in oem_com.h
//#define COM_FIOCTL_REMOTE_LOOPBACK      0x8007	// defined in oem_com.h
#define COM_FIOCTL_SET_DTR              	0x8008	/*!< Turn on DTR Com Signal if signal supported */
#define COM_FIOCTL_CLEAR_DTR            	0x8009	/*!< Turn off DTR Com Signal if signal supported*/
#define COM_FIOCTL_GET_DSR              	0x800a	/*!< read DSR com signal if signal supported*/
#define COM_FIOCTL_GET_RI	          		  0x800b	/*!< read DSR com signal if signal supported*/
#define COM_FIOCTL_GET_DCD             	 	0x800c	/*!< read DCD com signal if signal supported */
#define MDB_FIOCTL_SEND_NEXT_BYTE_9BIT  	0x800d	/*!< Indicate to the system that next byte need to be transmit as MDB Address */
#define MDB_FIOCTL_SET_SLAVE_1          	0x800e	/*!< configuration command of the first MDB Address in slave Mode */
#define MDB_FIOCTL_SET_SLAVE_2          	0x800f	/*!< configuration command of the secondt MDB Address in slave Mode */
//#define COM_FIOCTL_BREAK_START          0x8010	// defined in oem_com.h
//#define COM_FIOCTL_BREAK_STOP           0x8011	// defined in oem_com.h
#define IRDA_FIOCTL_SET_FILTER      			0x8012	/*!< Configure filter Level in IRDA mode */
#define MDB_FIOCTL_SET_RESP_DELAY     	  0x8013	/*!< configuration command of Time-out MDB protocol  */
#define MDB_FIOCTL_GET_RESP_DELAY     	  0x8014	/*!< return Time-out programmed for MDB protocol */
//#define COM_FIOCTL_GET_CONFIG           0x8015	// defined in oem_com.h


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


/*
======================================================================
					List of Defines (IO)
======================================================================
*/
// FIOCTL
// LEDs (from UCM board)
#define IO_FIOCTL_SET_LED0              0x8000	/*!< switch led0 on */
#define IO_FIOCTL_CLEAR_LED0            0x8001	/*!< switch led0 off */
#define IO_FIOCTL_SET_LED1              0x8002	/*!< switch led1 on */
#define IO_FIOCTL_CLEAR_LED1            0x8003	/*!< switch led1 off */
#define IO_FIOCTL_SET_LED2              0x8004	/*!< switch led2 on */
#define IO_FIOCTL_CLEAR_LED2            0x8005	/*!< switch led2 off */

// IO inputs/outputs
#define IO_FIOCTL_SET_IO0               0x8008	/*!< set output IO0 to 1 */
#define IO_FIOCTL_CLEAR_IO0             0x8009	/*!< set output IO0 to 0 */
#define IO_FIOCTL_SET_IO1               0x800a	/*!< set output IO1 to 1 */
#define IO_FIOCTL_CLEAR_IO1             0x800b	/*!< set output IO1 to 0 */
#define IO_FIOCTL_GET_STATE_IO0         0x800c	/*!< read input IO0	 */
#define IO_FIOCTL_GET_STATE_IO1         0x800d	/*!< read input IO1 */
#define IO_FIOCTL_GET_STATE_PUSH0	    	0x8010	/*!< read input push */
 
// Battery state
#define IO_FIOCTL_GET_STATE_BATTERY     0x8006 	/*!< give battery state: 	0 -> battery low /	1 -> battery ok */

// cmd external com power (COM1,2,COM10,COM11,COM3_MDB,USB_HOST) 
#define IO_FIOCTL_EXTERNAL_POWER_ON    	 0x800e 	 /*!< turn on 5VDC power on connectors:COM1,COM2,COM10,COM11,COM3_MDB,USB_HOST */
#define IO_FIOCTL_EXTERNAL_POWER_OFF     0x800f 	 /*!< turn off 5VDC power on connectors:COM1,COM2,COM10,COM11,COM3_MDB,USB_HOST */


#endif
 
/*! @}  */ 


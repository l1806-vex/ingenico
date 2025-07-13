/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_COM_H
#define OEM_COM_H


// BAUD RATE
#define COM_BAUD_RATE_SYNC                0x80000000		/*!< Can be used with format function for for baud rate argument : for exemple COM_BAUD_RATE_SYNC|9600 = 9600 bauds synchronous mode */
#define COM_BAUD_RATE_SYNC_EXTERNAL_CLOCK 0							/*!< Can be used with format function for for baud rate argument : synchronous mode with clock sent by peer */

/*
======================================================================
 FIOCTL 0x8000 to 0x801F are reserved for COM RS232/USB compatibility
======================================================================
*/
#define COM_FIOCTL_SET_RTS                0x8000				/*!< Set RTS in active state ( pin = 0) */
#define COM_FIOCTL_CLEAR_RTS              0x8001				/*!< Clear RTS in idle state (pin = 1) */
#define COM_FIOCTL_GET_CTS                0x8003				/*!< Value returned by fioctl is CTS pin logical state (1=active / 0=idle) */
#define COM_FIOCTL_SET_RECEIVER_TIMEOUT   0x8004  			/*!< unsigned int : 0 = no timeout  1-65535 : number of bits */
#define COM_FIOCTL_GET_RECEIVER_TIMEOUT   0x8005 				/*!< unsigned int : 0 = no timeout  1-65535 : number of bits */
#define COM_FIOCTL_LOCAL_LOOPBACK         0x8006				/*!< Reserved for future use */
#define COM_FIOCTL_REMOTE_LOOPBACK        0x8007				/*!< Reserved for future use */

#define COM_FIOCTL_SET_DTR                0x8008				/*!< Turn on DTR Com Signal if signal supported  */
#define COM_FIOCTL_CLEAR_DTR              0x8009				/*!< Turn off DTR Com Signal if signal supported */
#define COM_FIOCTL_BREAK_START            0x8010				/*!< Start sending break on the seriel line */
#define COM_FIOCTL_BREAK_STOP             0x8011				/*!< Stop sending break on the seriel line */
#define COM_FIOCTL_GET_CONFIG             0x8015				/*!< parameter type is COM_CONFIG : Read serial line configuration  */

// FIOCTL 0x8020 to 0x803F are reserved for USB legacy - Do not use this values


/*
======================================================================
 FIOCTL 0x8100 to 0x8200 are reserved for new Modem fioctl
======================================================================
*/

/*
================================================================================
 FIOCTL 0x8500 to 0x8600 are reserved for new Modem/COM RS232/USB compatibility
================================================================================
*/
#define COM_FIOCTL_GET_CONFIGURATION      0x8500				/*!< parameter type is COM_CONFIG : Read serial line configuration  */



/*! @brief Information about the COM configuration. */
typedef struct {
	unsigned long Baudrate;									/*!< Baudrate */
	unsigned char Character_Length;					/*!< length of a character */
	unsigned char Parity_Type;							/*!< type of parity */
	unsigned char Stop_Bits_Number;					/*!< number of stop bits */
	unsigned char Rts_Cts_Enabled;					/*!< activate flow control or not */
}COM_CONFIG;


#define COM_UNDEFINED					0xFF		/*!< Possible value for COM_CONFIG->Stop_Bits_Number and COM_CONFIG->Parity_Type */

#define COM_5_BITS						0x05		/*!< Value for COM_CONFIG->Character_Length */
#define COM_6_BITS						0x06		/*!< Value for COM_CONFIG->Character_Length */
#define COM_7_BITS						0x07		/*!< Value for COM_CONFIG->Character_Length */
#define COM_8_BITS						0x08		/*!< Value for COM_CONFIG->Character_Length */

#define COM_1_STOP_BIT				0x01		/*!< Value for COM_CONFIG->Stop_Bits_Number */
#define COM_2_STOP_BITS				0x02		/*!< Value for COM_CONFIG->Stop_Bits_Number */
#define COM_1_5_STOP_BITS			0x03		/*!< Value for COM_CONFIG->Stop_Bits_Number */

#define COM_NO_PARITY					0x00		/*!< Value for COM_CONFIG->Parity_Type */
#define	COM_ODD_PARITY				0x01		/*!< Value for COM_CONFIG->Parity_Type */
#define COM_EVEN_PARITY				0x02		/*!< Value for COM_CONFIG->Parity_Type */
#define COM_MULTI_DROP_MODE		0x06		/*!< Value for COM_CONFIG->Parity_Type */




#endif

/*! @}  */ 



#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_PUBLIC_DEF_H_INCLUDED__
#define __OEM_PUBLIC_DEF_H_INCLUDED__

#include "basearm_def.h" // Word typedef

/*! @addtogroup KSFAM_OS
	* @{
 */ 


// NOTE : pour inclure OEM_PUBLIC.H dans des fichiers utilisant les flux standards et non les redefinitions, il faut declarer : #define USE_ANSI_STREAM

/*
======================================================================
					List of Defines
======================================================================
*/
/*! @brief This type describes a function. */
typedef struct {
  const char *fct_name;					/*!< name of the function. */
  void *fct;										/*!< pointer to the function described. */
}fct_desc_t;


#include "rtctime_def.h"
#include "trace_sap_def.h"

// time slice
#define XecTimeUnit        10 			//OS_k_TICK 	(10 ms par coup d'horloge)

#define TIMEOUT	           0				/*!< value returned by ttestall if timeout occured */
#define EOF                (-1)			/*!< value returned by many OEMC functions (ferror, ...)  */
#define NO_SEM             0xFF			/*!< Value used when no semaphore is associated to OEMC file */
#define NOTASK             0xFFFF		/*!< value used when OEMC file is not opened */

#ifndef NULL
	#define NULL             ((void *)0)					/*!< NULL pointer definition */
#endif

#define pNULL              ((void *)0)   				/* NULL - pointer */

#ifndef OK
	#define OK               (unsigned char)0			/*!< successful return value */
#endif

#ifndef KO
  #define KO               (unsigned char)!OK		/*!< error return value */
#endif

#ifndef OFF
   #define OFF             0			/*!< OFF */
#endif

#ifndef ON
   #define ON             !OFF		/*!< ON */
#endif

#define _max_string_length 512		/*!< max string length for frintf */
#define _overrun_err_id    0xFF		/*!< value returned by ferror when overrun has occured */

// temps d'attente (en 1/100 secondes) quand les buffers sont pleins avant d'ecraser (mode circulaire)
#define timeout_send       1			/*!< timeout before buffer overwrite for putc and fputc functions */
#define timeout_rec        0			/*!< timeout when no byte ready in getc function */

// identificateur buffer emission ou reception
#define _send_id           0			/*!< parameter for reset_buf : reset out FIFO */
#define _receive_id        1			/*!< parameter for reset_buf : reset in FIFO */


// Event associated to OEMC file
//! \defgroup OEMC_PER_BITS Events associated to OEMC file
//! @{

// keyboard
#define E_KEYBOARD		0										/*!< event number for KEYBOARD */
#define KEYBOARD		 (1 << E_KEYBOARD)		/*!< event mask used as parameter for ttestall */

// Printer
#define E_PRINTER		  1										/*!< event number for PRINTER */
#define PRINTER			 (1 << E_PRINTER)			/*!< event mask used as parameter for ttestall */

// COM0
#define E_COM0			  2										/*!< event number for COM0 */
#define COM0			   (1 << E_COM0)				/*!< event mask used as parameter for ttestall */

// IRDA (UCM only)
#define E_IRDA			  2										/*!< event number for IRDA */
#define COMIRDA			 (1 << E_IRDA)				/*!< event mask used as parameter for ttestall */

// COM1
#define E_COM1			  3										/*!< event number for COM */
#define COM1		  	 (1 << E_COM1)				/*!< event mask used as parameter for ttestall */

// MODEM
#define E_MODEM		  	4										/*!< event number for MODEM */
#define MODEM			   (1 << E_MODEM)				/*!< event mask used as parameter for ttestall */

// CAM0 (CAM0 of Pin Pad Readder if connected)
#define E_CAM0 		  	5										/*!< event number for CAM0 */
#define CAM0 			   (1 << E_CAM0)				/*!< event mask used as parameter for ttestall */

// CAM1
#define E_CAM1 		  	6										/*!< event number for CAM1 */
#define CAM1 			   (1 << E_CAM1)				/*!< event mask used as parameter for ttestall */

// SWIPE2
#define E_SWIPE2      7										/*!< event number for SWIPE2 */
#define SWIPE2       (1 << E_SWIPE2)			/*!< event mask used as parameter for ttestall */

// IAPP
#define E_IAPP  		  0x8									/*!< event number for IAPP */
#define IAPP 			   (1 << E_IAPP)				/*!< event mask used as parameter for ttestall */

// SWIPE31
#define E_SWIPE31     9										/*!< event number for SWIPE31 */
#define SWIPE31      (1<<E_SWIPE31)				/*!< event mask used as parameter for ttestall */

// USB device CDC ACM
#define E_COM5		  	10									/*!< event number for COM5 */
#define COM5			   (1 << E_COM5)				/*!< event mask used as parameter for ttestall */

// USB Host CDC ACM
#define E_COM6			  11									/*!< event number for COM6 */
#define COM6			   (1 << E_COM6)				/*!< event mask used as parameter for ttestall */

/**************************************************************/
/*        Events 15 is available for user application         */
/**************************************************************/

// PinPad Reader Keyboard
#define E_KEYBOARD_PPR  16												/*!< event number for KEYBOARD_PPR */
#define KEYBOARD_PPR    (1 << E_KEYBOARD_PPR)			/*!< event mask used as parameter for ttestall */

// C30 Keyboard (CAD30VT)
#define E_KEYBOARD_C30	 E_KEYBOARD_PPR 					/*!< event number for KEYBOARD_C30 */
#define KEYBOARD_C30    (1 << E_KEYBOARD_C30)			/*!< event mask used as parameter for ttestall */

// PinPad Reader IAPP
#define E_IAPP_PPR      17												/*!< event number for IAPP_PPR */
#define IAPP_PPR        (1 << E_IAPP_PPR)					/*!< event mask used as parameter for ttestall */

// C30 IAPP 
#define E_IAPP_C30		   E_IAPP_PPR 							/*!< event number for IAPP_C30 */
#define IAPP_C30        (1 << E_IAPP_C30)					/*!< event mask used as parameter for ttestall */

// IAPP CAD30USR
#define E_IAPP_CAD30USR	E_IAPP_PPR 								/*!< event number for IAPP_CAD30USR	*/
#define IAPP_CAD30USR   (1 << E_IAPP_CAD30USR)		/*!< event mask used as parameter for ttestall */

// CAM2 (Terminal CAM0 if PinPad Reader connected
#define E_CAM2			     18									/*!< event number for CAM2 */
#define CAM2            (1 << E_CAM2)				/*!< event mask used as parameter for ttestall */

// CAM9
#define E_CAM9		      18									/*!< event number for CAM9 */
#define CAM9           (1 << E_CAM9)				/*!< event mask used as parameter for ttestall */

//COM11 Master Duart link for UCM
#define E_COM11 		    18									/*!< event number for COM11 */
#define COM11          (1 << E_COM11)				/*!< event mask used as parameter for ttestall */

// COM2
#define E_COM2			    19									/*!< event number for COM2 */
#define COM2			     (1 << E_COM2)				/*!< event mask used as parameter for ttestall */

// MOUSE
#define E_MOUSE			    20									/*!< event number for MOUSE */
#define MOUSE			     (1 << E_MOUSE)				/*!< event mask used as parameter for ttestall */

// CLESS
#define E_CLESS			   20 								 /*!< event number for CLESS */
#define CLESS			     (1 << E_CLESS)			 /*!< event mask used as parameter for ttestall */

// KEYBOARD USB
#define E_KEYUSB		   21									/*!< event number for KEYBUSB */
#define KEYUSB			  (1 << E_KEYUSB)			/*!< event mask used as parameter for ttestall */
#define E_KEYBUSB		   E_KEYUSB						/*!< event number for KEYBUSB */
#define KEYBUSB			  (1 << E_KEYBUSB)		/*!< event mask used as parameter for ttestall */

// SWIPE3
#define E_SWIPE3       22									/*!< event number for SWIPE3 */
#define SWIPE3        (1<<E_SWIPE3)				/*!< event mask used as parameter for ttestall */

#define E_DRV_GPRS		 23									/*!< event number for DRV_GPRS */
#define DRV_GPRS			(1 << E_DRV_GPRS)		/*!< event mask used as parameter for ttestall */

#define E_DRV_UMS			 24									/*!< event number for DRV_UMS */
#define DRV_UMS			  (1 << E_DRV_UMS)		/*!< event mask used as parameter for ttestall */
	
#define E_DBLUETOOTH   25										/*!< event number for DBLUETOOTH */
#define DBLUETOOTH    (1 << E_DBLUETOOTH)		/*!< event mask used as parameter for ttestall */

//COM11 Slave Duart link for UCM
#define E_COM10 		   25										/*!< event number for COM10  */
#define COM10         (1 << E_COM10)				/*!< event mask used as parameter for ttestall */

//Event UCM COM3 
#define E_COM3         26										/*!< event number for COM3 */
#define COM3          (1 << E_COM3)					/*!< event mask used as parameter for ttestall */

#define E_COM_EXT      26										/*!< event number for COM_EXT many drivers as COM20, COM21, COM_KEYSPAN, COM_SL, ... */
#define COM_EXT       (1 << E_COM_EXT)			/*!< event mask used as parameter for ttestall */


#define E_COM_AIAP      26										/*!< event number for COM_EXT many drivers as COM20, COM21, COM_KEYSPAN, COM_SL, ... */
#define COM_AIAP       (1 << E_COM_AIAP)			/*!< event mask used as parameter for ttestall */

#define E_BARCODE      26										/*!< event number for COM_EXT many drivers as COM20, COM21, COM_KEYSPAN, COM_SL, ... */
#define BARCODE       (1 << E_BARCODE)			/*!< event mask used as parameter for ttestall */

// Event for COMH (USB Serial Converter on USB Host of BME base)
#define E_COMH          27                      /*!< Event number for COMH (USB Serial Converter on USB Host of BME base) */
#define COMH           (1 << E_COMH)            /*!< Event mask for COMH (USB Serial Converter on USB Host of BME base)*/

// Event for Touch Screen
#define E_TSCREEN      27										/*!< event number for TSCREEN */
#define TSCREEN       (1 << E_TSCREEN)			/*!< event mask used as parameter for ttestall */

// C30 IAPP2
#define E_IAPP2 		   28 							    /*!< event number for IAPP2 */
#define IAPP2              (1 << E_IAPP2)		/*!< event mask used as parameter for ttestall */

/**********************************************************/
/*        Events 31 is available for user application     */
/**********************************************************/
//! @} 

// Standard OEMC FILES status bits *
//! \defgroup OEMC_STATUS_BITS OEMC status bits returned by status function
//! @{
#define COM_FIN_EMI        0x80		/*!< End of sending (at physical level) */
#define COM_SEND_END       0x80		/*!< End of sending (at physical level) */
#define PRINT_END          0x80		/*!< End of printing (at physical level) */
#define PRINT_ERROR        0x10		/*!< Printer error */
#define COM_EMI_EMPTY      0x40		/*!< Out FIFO empty */
#define COM_SEND_EMPTY     0x40		/*!< Out FIFO empty */
#define PRINT_BUFFER_EMPTY 0x40		/*!< Printer FIFO empty */
#define COM_REC_NOT_EMPTY  0x20		/*!< Bytes in receive FIFO */
#define KEYS_IN_BUFFER     0x20		/*!< Bytes in receive FIFO */
#define TRACK_READ         0x20		/*!< Bytes in receive FIFO for SWIPE reader */
#define ERR_BUFFER         0x10 	/*!< printer specific error  */
#define DCD                0x10  	/*!< Data Carrier Detect : The modem is receiving a valid carrier signal from the remote modem. */
#define SYNCHRO_MODEM      0x0F		/*!< Only for compatibility */
#define CHG_STATUS         0x08 	/*!< dgprs and dbluetooth, state changed */
#define PRINTER_BAT_LOW    0x08 	/*!< external printer - battery low */
#define CONNECT_OK         0x04 	/*!< dgprs and dbluetooth, asynchronous fioctl successful */
#define CONNECT_KO         0x02 	/*!< dgprs and dbluetooth, asynchronous fioctl unsuccessful */
#define PAPER_OUT          0x01		/*!< No more paper in printer */
#define COM_REC_FBREAK     0x01		/*!< Break received on serial line */
#define USB_PRESENT        0x01		/*!< status for USB driver when device is connected */
#define CAM_PRESENT        0x0001  /*!< Smart card inserted into reader */
#define CAM_ARRACHEE       0x0008   /*!< Smart card removed */
//! @} 

// APPLE IAP
#define APPLE_STS_CONNECTED      0x01   /*!< status for Apple IAP driver when Iphone is connected to iSPM */
#define APPLE_STS_POWERED        0x02   /*!< status for Apple IAP driver when Iphone is powered (not sleeping) */
#define APPLE_STS_AUTHENTICATED  0x04   /*!< status for Apple IAP driver when Iphone has authenticated the iSPM */

#define APPLE_CHANNEL_PRESENT    0x08	/*!< status for Apple IAP specific driver when channel is open */


// mode d'acces aux periphs
#ifndef __SWI_FLASH_H__
#define _read              0x01  /*!< 0 = don't read,        1 = read           */
#define _write             0x02  /*!< 0 = don't write,       1 = write          */
#define _elt_send          0x04  /*!< 0 = char,              1 = word           */
#define _elt_rec           0x08  /*!< 0 = char,              1 = word           */
#define _unget_full        0x10  /*!< 0 = not full,          1 = full           */
#define _reset             0x20  /*!< 0 = send EOF,          1 = reset          */
#define _append            0x40  /*!< 0 = clear if writing,  1 = don't clear    */
#define _overrun           0x80  /*!< 0 = no overrun,        1 = overrun        */
#endif

/*
======================================================================
			Data Structures Definition
======================================================================
*/

#ifndef uchar
#define uchar unsigned char
#endif

/*! @brief This type defines an amount. */
typedef unsigned long MONTANT;

/*! @brief This type defines a commercial number. */
typedef unsigned char NO_COMMERCANT[7];

/*! @brief This type defines a terminal number. */
typedef unsigned char NO_TERMINAL;

/*! @brief This type defines a CRC. */
typedef unsigned short CRC16;


// iso
#define TAILLE_MAXBUF 40			/*!< Max size of ISO track */

/*! @brief This type defne a long reference. */
typedef unsigned char LG_REF_CLI;

/*! @brief This type defines a buffer track. */
typedef unsigned char       BUFFER_PISTE[TAILLE_MAXBUF];

/*! @brief This type defines the chip buffer. */
typedef unsigned char BUFFER_PUCE [TAILLE_MAXBUF];


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief dec_iso1 is used for decoding ISO1 stripe.
 * @param swipe_read_length : customer reference length if decoded, char decoded count otherwise
 * @param data_bit[data_bit_length] : bit buffer with following bits arrangement [01234567][89......] right justified with 0 bits
 * @param swipe_read : decoded chain (not null terminated if up to ISOx_LEN char decoded)
 * @param data_bit_length : data_bit length
 * @return same as is_isox()
 */
int dec_iso1(unsigned char*swipe_read_length,unsigned char*swipe_read,unsigned char*data_bit,int data_bit_length);

/*! @brief dec_iso2 is used for decoding ISO2 stripe.
 * @param swipe_read_length : customer reference length if decoded, char decoded count otherwise
 * @param data_bit[data_bit_length] : bit buffer with following bits arrangement [01234567][89......] right justified with 0 bits
 * @param swipe_read : decoded chain (not null terminated if up to ISOx_LEN char decoded)
 * @param data_bit_length : data_bit length
 * @return same as is_isox()
 */
int dec_iso2(unsigned char*swipe_read_length,unsigned char*swipe_read,unsigned char*data_bit,int data_bit_length);

/*! @brief dec_iso3 is used for decoding ISO3 stripe.
 * @param swipe_read_length : customer reference length if decoded, char decoded count otherwise
 * @param data_bit[data_bit_length] : bit buffer with following bits arrangement [01234567][89......] right justified with 0 bits
 * @param swipe_read : decoded chain (not null terminated if up to ISOx_LEN char decoded)
 * @param data_bit_length : data_bit length
 * @return same as is_isox()
 */
int dec_iso3(unsigned char*swipe_read_length,unsigned char*swipe_read,unsigned char*data_bit,int data_bit_length);

#define SWP_FIOCTL_UNGET_TRACKS  0x9003 /*!< fioctl : unget tracks to oemc file*/
#define ALTERNATE_HEAD	0				/*!< fioctl parameter SWP_FIOCTL_UNGET_TRACKS :get alternate tracks read on 2nd magnetic head   */


/*
==================
		fichier.c
==================
*/


/*! @brief This type defines a segment number. */
typedef unsigned char       NO_SEGMENT;

/*! @brief This type defines a segment type. */
typedef unsigned char       TYPE_SEG;

/* description d'un des parametres de info_seg */
/*! @brief This type defines a version. */
typedef char                T_VERSION[9];

/*! @brief This type defines an address. */
typedef unsigned int        ADRESSE;

/*! @brief This type defines a checksum. */
typedef unsigned short int  CHECKSUM;

/*! @brief This type defines a flag change state : CHGT_OUI if change and CHGT_NON otherwise. */
typedef char                FLAG_CHGT;

/*! @brief This type defines a type change. */
typedef char                TYPE_CHGT;

/*! @brief This type define a flag transfer */
typedef unsigned char       FLAG_RELOC;

/*! @brief This type define a segment. */
typedef struct
{
   T_VERSION libelle ;						/*!< name of the segment. */
   CHECKSUM crc ;									/*!< CRC. */
   ADRESSE  debut_code ;					/*!< address of the begining of the code */
   TYPE_SEG typ_code ;						/*!< type of the code */
   ADRESSE  debut_donnees ;				/*!< address of the begining of the data */
   ADRESSE  debut_fichier;				/*!< address of the begining of the file */
   FLAG_RELOC ind_relog;					/*!< index of a flag transfer. */
} SEGMENT;


/*! @}  */ 



/*! @addtogroup KSFAM_AUTRES
	* @{
 */ 

#define start	OEM_start

#define sem_user_1       sem_user(1)			/*!< gets 1st semaphore identifier for user */
#define sem_user_2       sem_user(2)			/*!< gets 2nd semaphore identifier for user */
#define sem_user_3       sem_user(3)			/*!< gets 3rd semaphore identifier for user */
#define sem_user_4       sem_user(4)			/*!< gets 4th semaphore identifier for user */
#define sem_user_5       sem_user(5)			/*!< gets 5th semaphore identifier for user */
#define sem_user_6       sem_user(6)			/*!< gets 5th semaphore identifier for user */
#define sem_user_7       sem_user(7)			/*!< gets 7th semaphore identifier for user */
#define sem_user_8       sem_user(8)			/*!< gets 8th semaphore identifier for user */
#define sem_user_9       sem_user(9)			/*!< gets 9th semaphore identifier for user */
#define sem_user_10      sem_user(10)			/*!< gets 10th semaphore identifier for user */

#define mailbox_user_1   mailbox_user(1)	/*!< gets 1st mailbox identifier for user */
#define mailbox_user_2   mailbox_user(2)	/*!< gets 2nd mailbox identifier for user */
#define mailbox_user_3   mailbox_user(3)	/*!< gets 3rd mailbox identifier for user */
#define mailbox_user_4   mailbox_user(4)	/*!< gets 4th mailbox identifier for user */
#define mailbox_user_5   mailbox_user(5)	/*!< gets 5th mailbox identifier for user */
#define mailbox_user_6   mailbox_user(6)	/*!< gets 5th mailbox identifier for user */
#define mailbox_user_7   mailbox_user(7)	/*!< gets 7th mailbox identifier for user */
#define mailbox_user_8   mailbox_user(8)	/*!< gets 8th mailbox identifier for user */
#define mailbox_user_9   mailbox_user(9)	/*!< gets 9th mailbox identifier for user */
#define mailbox_user_10  mailbox_user(10)	/*!< gets 10th mailbox identifier for user */

#define delay_user_1     delay_user(1)		/*!< gets 1st delay identifier for user */
#define delay_user_2     delay_user(2)		/*!< gets 2nd delay identifier for user */
#define delay_user_3     delay_user(3)		/*!< gets 3rd delay identifier for user */
#define delay_user_4     delay_user(4)		/*!< gets 4th delay identifier for user */
#define delay_user_5     delay_user(5)		/*!< gets 5th delay identifier for user */
#define delay_user_6     delay_user(6)		/*!< gets 5th delay identifier for user */
#define delay_user_7     delay_user(7)		/*!< gets 7th delay identifier for user */
#define delay_user_8     delay_user(8)		/*!< gets 8th delay identifier for user */

#define task_user_1      task_user(1)			/*!< Only for compatibility : not to be used */
#define task_user_2      task_user(2)			/*!< Only for compatibility : not to be used */
#define task_user_3      task_user(3)			/*!< Only for compatibility : not to be used */
#define task_user_4      task_user(4)			/*!< Only for compatibility : not to be used */

/*! @}  */ 


/*
==================
	oem_open.c
==================
*/

/*! @addtogroup KSFAM_IOSF
	* @{
 */ 


/*! @brief format programs a serial port COM0/COM1.This function is used to format a serial link.
 * @param peripheral_name : COM0, COM1, COM2.
 * @param arglist : List of arguments :
 * - arglist[0]        : baud_rate = 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 bps.
 * - arglist[1]        : 7 or 8 bits.
 * - arglist[2]        : 1 or 2 stop bits.
 * - arglist[3]       :
 *	- PARITY, parity tested.
 *	- NO_PARITY, parity not tested.
 * - arglist[4] :
 *	- EVEN parity.
 *	- ODD parity.
 * - arglist[5] : flow control ( only on COM0 )
 *	- 00 No flow control
 *	- 01 flow control via RTS/CTS management
 *
 * @return
 * - 0 if function has been correctly executed
 * - -1 if COMx file was not open.
 *
 * @note
 * The parity parameter indicates that the character parity has been tested. The evenodd parameter
 * indicates whether the parity is EVEN or ODD. This function can be accessed even if the peripheral
 * is not open. The format is preserved up to the next time the serial port is programmed.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int FormatOem(const char *peripheral_name, va_list arglist);


/*! @brief format programs a serial port COM0/COM1.This function is used to format a serial link. This function can be used to set the marging of PRINTER too.
 * @param peripheral_name : COM0, COM1, COM2.
 * @param ... : List of arguments :
 * - speed        : baud_rate = 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 bps.
 * - length_byte  : 7 or 8 bits.
 * - stop_bits    : 1 or 2 stop bits.
 * - parity       :
 *  - PARITY, parity tested.
 *  - NO_PARITY, parity not tested.
 * - evenodd :
 *  - EVEN parity.
 *  - ODD parity.
 * - rtscts : flow control ( only on COM0 )
 *  - 00 No flow control
 *  - 01 flow control via RTS/CTS management
 *
 * @param peripheral_name : PRINTER.
 * @param ... : List of arguments :
 * - Left Marging : Max value 384. (0 by default)
 * - Right Marging: Max value 384. (0 by default)
 * - set the next parameters to 0
 *
 * @return
 * - 0 if function has been correctly executed
 * - -1 if COMx file was not open.
 *
 * @note
 * The parity parameter indicates that the character parity has been tested. The evenodd parameter
 * indicates whether the parity is EVEN or ODD. This function can be accessed even if the peripheral
 * is not open. The format is preserved up to the next time the serial port is programmed.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int format(const char *peripheral_name, ...);


#define PARITY    0		/*!< May be used for format : parity used. */
#define NO_PARITY 1		/*!< May be used for format : parity not tested. */
#define EVEN      0		/*!< May be used for format : even parity. */
#define ODD       1		/*!< May be used for format : odd parity. */
#define OVERRUN_BUFFER 0xFF		  /*!< return value for ferror : OEMC buffer overrun */
#define OVERRUN_ERROR  0x2000		/*!< return value for ferror : USART overrun error */
#define FRAMING_ERROR  0x4000		/*!< return value for ferror : USART framing error */
#define PARITY_ERROR   0x8000		/*!< return value for ferror : USART parity error */

/*! @brief Define a size used by Telium. */
typedef unsigned int Telium_size_t;


/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*! @brief sprintf writes in a string.
 * @param s      : pointer to string.
 * @param format : string to be formatted.
 * @return
 * - number of characters written in the string if OK.
 * - (-1) if problem detected.
 *
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int sprintf(char *s, const char *format, ...);

/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*
======================================================================
					List of Defines
======================================================================
*/

/*
==================
	clavier.c
==================
*/

// keys returned by KEYBOARD
#define T_NUM0		'0'				/*!< keys returned by KEYBOARD : '0' */
#define T_NUM1		'1'				/*!< keys returned by KEYBOARD : '1' */
#define T_NUM2		'2'				/*!< keys returned by KEYBOARD : '2' */
#define T_NUM3		'3'				/*!< keys returned by KEYBOARD : '3' */
#define T_NUM4		'4'				/*!< keys returned by KEYBOARD : '4' */
#define T_NUM5		'5'				/*!< keys returned by KEYBOARD : '5' */
#define T_NUM6		'6'				/*!< keys returned by KEYBOARD : '6' */
#define T_NUM7		'7'				/*!< keys returned by KEYBOARD : '7' */
#define T_NUM8		'8'				/*!< keys returned by KEYBOARD : '8' */
#define T_NUM9		'9'				/*!< keys returned by KEYBOARD : '9' */
#define T_POINT	    '.'			/*!< keys returned by KEYBOARD : '.' */
#define T_APAP      0x07		/*!< keys returned by KEYBOARD : Paper Feed */
#define T_VAL				0x16		/*!< keys returned by KEYBOARD : Green key */
#define T_ANN				0x17		/*!< keys returned by KEYBOARD : Red key */
#define T_CORR			0x18		/*!< keys returned by KEYBOARD : Yellow key */
#define T_SK1				0x19		/*!< keys returned by KEYBOARD : F1 */
#define T_SK2				0x20		/*!< keys returned by KEYBOARD : F2 */
#define T_SK3				0x21		/*!< keys returned by KEYBOARD : F3 */	
#define T_SK4				0x22		/*!< keys returned by KEYBOARD : F4 */
#define T_SKHAUT		0x23		/*!< keys returned by KEYBOARD : Up */
#define T_SKBAS			0x24		/*!< keys returned by KEYBOARD : Down */
#define T_SKVAL			0x25		/*!< keys returned by KEYBOARD : OK */
#define T_SKCLEAR		0x26		/*!< keys returned by KEYBOARD : C */
#define T_SK10			0x28		/*!< keys returned by KEYBOARD : F */

#define NB_KEY      24			/*!< number of keys returned */

/*
==================
	fonctions Cam
==================
*/

#define PB_COMM 	   	 0x6  		/*!< PB_DIALOGUE or PB_PARITE */
#define CAM_CONNECTEE  0x0004		/*!< Only for compatibility : Do not Use */

#define VALIDE         0x00			/*!< Return value for power ON : success */
#define ABSENTE        0x01			/*!< Return value for power ON : smart card not found */
#define CRT_NONTRAITEE 0x02  		/*!< VPP non compatible */     
#define PAS_REPONSE    0x03  		/*!< No answer to reset */         
#define PB_VPP         0x04			/*!< Only for compatibility : Do not Use */
#define PB_VCC         0x05			/*!< Only for compatibility : Do not Use */
#define PB_PARITE      0x06  		/*!< Pb parity on transmission / reception character */
#define RETIREE        0x07			/*!< Powered smart card removed */
#define CAM_KO_UNSECURED_IUC  0x08 /* Unauthorized command as long as IUC is unsecured */
#define PLEINE_CODE    0x10  		/*!< Presentation code impossible ME2=0x80      */
#define BLOQUEE        0x11  		/*!< 3 code faux                                */
#define MUETTE         0x13  		/*!< ME2= 01 ou 05                              */
#define PLEINE_BLOQUEE 0x14  		/*!< ME2 = 0xC0                                 */
#define ERREUR_SYSTEME 0x20  		/*!< ME1 <> 0x90                                */
#define MASQUE_DIF4    0x21  		/*!< Masque <> 4                                */
#define DEFAUT_PERSO   0x22  		/*!< Defaut personalisation                     */
#define ZONE_ABSENTE   0x23  		/*!< Zone State Reading or absent Transaction   */
#define VA_ERRONEE     0x25  		/*!< VA KO                                      */
#define CODE_DIF3FE5   0x26  		/*!< Code application <> 0x3FE5                 */
#define CODE_DIF250    0x27  		/*!< Code language or usage <> 250                */
#define PB_DIALOGUE    0x29  		/*!< ME2 <> 0  or time-out                      */


// controle de code avec codes precedemment definis 
#define PRESQUE_PLEINE 0x30  		/*!< Smart card full in code area */
#define CODE_FAUX      0x31  		/*!< ME2.2 = 1                                  */

#define MAX_HISTORIC   15				/*!< Max length of historic bytes  */


/*! @brief This type define a historical */
typedef struct {
		unsigned char length;											/*!< length of the historical */
    unsigned char historic[MAX_HISTORIC];			/*!< data of the historical */
} HISTORIC;

/*! @brief Structure to command the card management. */
// COMMAND_CAM:DATA_CODE(4*2 + strlen(statusword1) + strlen(statusword2) )
typedef struct {
	unsigned char *header;								/*!< pointer to header */
	unsigned char *data;									/*!< pointer to POS data */
	unsigned char statusword1;						/*!< SW1 value */
	unsigned char statusword2;						/*!< SW2value */
} COMMAND_CAM;

/*! @brief This type define an APDU. */
typedef struct{
    unsigned char *data ;							/*!< data of the APDU. */
    unsigned int length ;							/*!< length of the APDU. */
} T_APDU ;

/*! @}  */ 

/*! @addtogroup KSFAM_OS_TASK
	* @{
 */ 
/*! @brief A pointer on t_topstack is returned by a handle (fork) protected by the superuser mode. Don't try to read 'fur' value */
typedef struct{			
  char fur;
}t_topstack;

/*! @}  */ 

/*! @addtogroup KSFAM_CARD
	* @{
 */ 

#define	T1G				3			/*!< synchronous smart card protocol : T1G */
#define	T2G				4			/*!< synchronous smart card protocol : T2G */
#define	S10				5			/*!< synchronous smart card protocol : S10 */
#define	S9					6			/*!< synchronous smart card protocol : S9 */
#define	GPM896			13			/*!< synchronous smart card protocol : GPM896 */
#define	GFM				14			/*!< synchronous smart card protocol : GFM */
#define	SLE4436			15			/*!< synchronous smart card protocol : SLE4436  */
#define	SLE4404			0x1C		/*!< synchronous smart card protocol : SLE4404  */
#define	AT88SC			0x1D		/*!< synchronous smart card protocol : AT88SC */
#define	GFM32K			0x1E		/*!< synchronous smart card protocol : GFM32K (calls generic GFM driver) */
#define	AT88SC102    	0x2B		/*!< synchronous smart card protocol : AT88SC102 */
#define	AT88SC1608     	0x2D		/*!< synchronous smart card protocol : AT88SC1608 */

#define ISO_OK        0	 /*!< return code for is_iso functions : success */
#define DEF_SEP       1	 /*!< return code for is_iso functions : separator error */
#define DEF_PAR   		2  /*!< return code for is_iso functions : parity error */
#define DEF_LRC   	  3  /*!< return code for is_iso functions : LRC error */
#define DEF_LUH       4  /*!< return code for is_iso functions : Luhn code error */
#define DEF_NUM       5  /*!< return code for is_iso functions : numerical fault detected */
#define NO_DATA       6  /*!< return code for is_iso functions : no readable data detected */
#define DEF_OVR       7  /*!< return code for is_iso functions : too many coded char, not ISO:7811 compliant */

#define Defaut_Separateur (unsigned char)1   /*!< For compatibility only. Use DEF_SEP */
#define Defaut_Parite     (unsigned char)2   /*!< For compatibility only. Use DEF_PAR */
#define Defaut_LRC        (unsigned char)3   /*!< For compatibility only. Use DEF_LRC */
#define Defaut_Luhn       (unsigned char)4   /*!< For compatibility only. Use DEF_LUH */
#define Defaut_Numericite (unsigned char)5   /*!< For compatibility only. Use DEF_NUM */
#define Data_Available 1   /*!< For compatibility only. Do not use. */
#define Reading        2   /*!< For compatibility only. Do not use. */
#define Closed         3   /*!< For compatibility only. Do not use. */
#define No_Data        6   /*!< For compatibility only. Do not use. */





/*! @}  */ 


/*! @addtogroup KSFAM_AUTRES
	* @{
 */ 
 
 
// \brief vprintf formats an output (argc argv) (cf doc ansi C)
// \param argc
// \param argv
// \return
// cf doc ansi C
// \note
int vsprintf(char *, const char *, va_list );

/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*
=========================
	driver printer et power
=========================
*/



/*! @brief This function replaces a standard character with a special character. 
 *
 * Up to 100 characters can be redefined.
 * @param weight : it can take the following values :
 * - Normal PRINTER_WEIGHT_LIGHT 0
 * - Bold PRINTER_WEIGHT_BOLD 1
 *
 * @param density : it can take the following values :
 * - PRINTER_DENSITY_NORMAL 0
 * - PRINTER_DENSITY_CONDENSED 1
 * - PRINTER_DENSITY_WIDE 3
 *
 * @param key : ASCII value of key parameter
 * @param pattern : Definition of character, pattern .
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if more characters are available.
 *
 * @note The key value will vary between 20 Hex and FF hex. Character code :
 * - 1 byte specifies the number of blank columns prior to the first column of dots.
 * - 1 byte specifies the number of useful columns containing at least one dot.
 * - x bytes : dot matrix represented for vertical with 8 lines defined, i.e. 1 byte per column as below :
 * - b0 highest line
 * - b1
 * - b2
 * - b3
 * - b4
 * - b5
 * - b6 lowest line
 * - b7 line under character
 * - 1 byte specifies the number of useful columns containing at least one dot.
 * - 1 byte specifies the number of blank columns after the last columns of dots.
 * - \\0 end-of-string character
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
extern int  defprinterpatternHR (char weight, char density,char key,char *pattern);



/*! @brief This function replaces a standard character with a special character. 
 *
 * Up to 100 characters can be redefined.
 * @param key     : ASCII value of key parameter
 * @param pattern : Definition of character, pattern .
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if more characters are available.
 *
 * @note The key value will vary between 20 Hex and FF hex. Character code :
 * - 1 byte specifies the number of blank columns prior to the first column of dots.
 * - 1 byte specifies the number of useful columns containing at least one dot.
 * - x bytes : dot matrix represented for vertical with 8 lines defined, i.e. 1 byte per column as below :
 * - b0 highest line
 * - b1
 * - b2
 * - b3
 * - b4
 * - b5
 * - b6 lowest line
 * - b7 line under character
 * - 1 byte specifies the number of useful columns containing at least one dot.
 * - 1 byte specifies the number of blank columns after the last columns of dots.
 * - \\0 end-of-string character
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int  defprinterpattern (char key, char *pattern);


/*! @}  */ 


/*! @addtogroup KSFAM_AUTRES
	* @{
 */ 

/*! @brief cnfbattery programs the stop of the terminal after "inactivedelay" if no activity is detected.
 * @param activedelay : activity duration (in seconds)
 * @param inactivedelay : Inactivity duration (in seconds)
 * @return None.
 * @note Default 40 seconds, min 10 seconds.
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
void cnfbattery(int activedelay, int inactivedelay);


/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*! @brief Sets wake-up date.
 * @param pt_date : pointer to structure DATE. Wake up date.
 * @return None.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int SetNextWakeUp(DATE* pt_date);



/*! @}  */ 


#define GET_SWI_NUMBER(fct) (((unsigned char *)fct)[1]+((((unsigned char *)fct)[5]-0x13)<<8))


/*! @addtogroup KSFAM_DIAG
	* @{
 */ 

/*
==================
	loader
==================
*/


/*! @brief Sets an application in 'not yet initialised' state
 * @param type_appli : Application type (field of ADF file)
 * @return 0 if OK.
 * @note
 * - Resets first init flag of an application.
 * - Removes all application's disks.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int ApplicationUnInitialize(unsigned short type_appli);



/*! @brief This function is used to recover the application information with its literal and CRC as well as their type.
 * @param num_segment : segment number
 * @param pt_param : pointer to structure SEGMENT. Output parameter.
 * @return -1 if segment is not existing.
 * @note This function must enable an application to edit its configuration (version
   and CRC). As EFT30 application are not relocatable, addresses are no more provided.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int info_seg(unsigned int num_segment,SEGMENT *pt_param);



/*! @brief info_seg_SE returns the release and checksum of currently loaded O/S.
 *
 * This function is used to recover the application information with its literal and CRC as well as their type.
 * @param version_name : version.
 * @param pt_crc : pointer to structure CHECKSUM. Output parameter.
 * @return The number of SWI managed by the system.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int info_seg_SE (T_VERSION version_name,CHECKSUM *pt_crc);



/*! @brief This function is used to determine if it is the first time the specified application is started up
     since a downloading operation and the type of downloading (local or remote).
     Once read, first execution flag could be reseted using raz_init function
 * @param num_segment : application number.
 * @param flag : pointer to download information. Output parameter.
 * @param type : pointer to type of download. (local or remote). Output parameter.
 * @return  -1 if segment requested does not exist.
 * @note
 *
 * flag =
 * - FF it is the first time the application is started.
 * - 00 if application had already ran.
 *
 * type =
 * - FF hex for remote downloading .
 * - 00 for local downloading.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int first_init(unsigned char num_segment,unsigned char *flag,unsigned char *type);


#define CHGT_OUI 0xFF	/* possibles values FLAG_CHGT (cf fct first_init */
#define CHGT_NON 0


/*! @brief first_init_SE  is used to determine if it is the first time Telium System is started.
 *   Once read, first execution flag could be reseted using raz_init_SE function
 *
 * @return - 0 if there is no new system component (driver) loaded in the terminal.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int first_init_SE(void);



/*! @brief This function reset the first execution flag.
 * @param num_segment : application number given by the manager.
 * @return -1 if application number does not exist.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int raz_init(unsigned char num_segment);



/*! @brief This function resets the flag returned by the function first_init_SE.
 *
 * This flag is set when a new system component is loaded.
 * @return  0 if OK.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int raz_init_SE(void);


/*! @}  */ 


/*! @addtogroup KSFAM_DIAG
	* @{
 */ 

/*! @brief This function records fault. 
 *
 * This fault is identified by a number. The fault list is defined in defdiag_TSys.h.
 * @param nu_def : Fault number.
 * @param level : Fault criticality.
 * - 0 : Not critical
 * - 1 : Critical or severe
 *
 * @return -1 if function cannot be processed.
 * @note nu_def : 0x1000 to 0xffff
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int  upload_diagnostic_def(unsigned short nu_def, unsigned char level);



/*! @brief This function increments and create a diagnostic counter.
 * @param num_cpt : counter number.
 * @return -1 if function cannot be processed.
 * @note
 * - num_cpt : value between 0x1000 to 0xffff.
 * - Calling the upload_diagnostic_cpt function automatically increments the
     value of the counter and creates it if it does not exist.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int  upload_diagnostic_cpt(unsigned short num_cpt);



/*! @brief This function records a text message in APPTEXT.DIA file.
 * @param pt_param : Address of character string of text to be stored.
 * @return  -1 if function cannot be processed.
 * @note pt_param : the pointer on the free text must be terminated by '\0'. The character string
   must have a carriage return character at the end ('\n') to ensure easier separation of the text.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int  upload_diagnostic_txt(unsigned char *pt_param);



/*! @brief This function prints diagnostics stored in the buffer. 
 *
 *The diagnostics are stored in the buffer by the function upload_diagnostic_txt.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
void print_diagnostic(void);



/*! @brief reset_diagnostic empties the buffer that stores diagnostics and faults. 
 *
 * After calling this routine, buffers are empty.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
void reset_diagnostic(void);


 

#define read_terminal_informations          lire_infos_terminal   


/*! @brief This function can be used for hardware identification.
 * @param function_id : define in diagdef.h :
 * - FCT_TERMINAL_INFO 1
 * - FCT_MEMORY_SIZE 2	
 * - FCT_SERIAL_NUMBER 3 : 14 digits serial number
 * - FCT_ROM_IDENTITY 4
 * - FCT_ALL_INFOS 5
 * - FCT_SYSTEM_SOFTWARE_INFO 6
 * - FCT_MEMORY_INFO 7 : deprecated Since the SDK 8.1 - Please use RamGetSize(), FreeSpace(), FS_AreaGetSize(), FS_AreaGetFreeSize()
 * - FCT_CARD_READER 8
 * - FCT_DOWNLOAD_STATUS 9
 * - FCT_RESET_DOWNLOAD_STATUS 10
 * - FCT_TERMINAL_NAME 11
 * - FCT_EXTENDED_SERIAL_NUMBER 13 : 16 digits serial number.
 *
 * @param pResult : pointer to an object according to indiceFct parameter :
 * - FCT_TERMINAL_INFO 1 : pointer to structure TERMINAL_INFOS .
 * - FCT_MEMORY_SIZE 2 : pointer to int memory size (= 4 bytes).
 * - FCT_SERIAL_NUMBER 3 : 14 digits serial number = array of 7 bytes.
 * - FCT_ROM_IDENTITY 4 : not used.
 * - FCT_ALL_INFOS 5 : pointer to structure TERMINAL_INFOS .
 * - FCT_SYSTEM_SOFTWARE_INFO 6 : pointer to structure SYSTEM_SOFTWARE_INFO .
 * - FCT_CARD_READER 8 : pointer to structure CARD_READER_INFO .
 * - FCT_DOWNLOAD_STATUS 9 : pointer to structure DOWNLOAD_STATUS .
 * - FCT_RESET_DOWNLOAD_STATUS 10 : nothing.
 * - FCT_TERMINAL_NAME 11 : string of 6 char + '/0' (total = 7 bytes)
 * - FCT_EXTENDED_SERIAL_NUMBER 13 : 16 digits serial number = array of 8 bytes.
 *
 * @return 0 if OK.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int read_terminal_informations(int function_id, void *pResult);


/*! @brief This function can be used for hardware identification.
 * @param function_id : define in diagdef.h :
 * - FCT_INFOS_TERMINAL 1
 * - FCT_TAILLE_MEMOIRE 2	
 * - FCT_NUMERO_SERIE 3 : 14 digits serial number
 * - FCT_IDENTITE_ROM 4
 * - FCT_TOUTES_INFOS 5
 * - FCT_INFOS_LOG_SYS 6
 * - FCT_MEMOIRE 7 : deprecated Since the SDK 8.1 - Please use RamGetSize(), FreeSpace(), FS_AreaGetSize(), FS_AreaGetFreeSize()
 * - FCT_COUPLEUR 8
 * - FCT_DOWNLOAD 9
 * - FCT_ACQUIT_DOWNLOAD 10
 * - FCT_LIBELLE_TERMINAL 11
 * - FCT_AFF_REVEIL_DISPO 12 : Nimh battery management
 * - FCT_EXTENDED_SERIAL_NUMBER 13 : 16 digits serial number.
 *
 * @param pResult : pointer to an object according to indiceFct parameter :
 * - FCT_INFOS_TERMINAL 1 : pointer to structure INFOS_TERMINAL .
 * - FCT_TAILLE_MEMOIRE 2 : pointer to int memory size (= 4 bytes).
 * - FCT_NUMERO_SERIE 3 : 14 digits serial number = array of 7 bytes.
 * - FCT_IDENTITE_ROM 4 : not used.
 * - FCT_TOUTES_INFOS 5 : pointer to structure INFOS_TERMINAL .
 * - FCT_INFOS_LOG_SYS 6 : pointer to structure INFOS_LOG_SYSTEME .
 * - FCT_MEMOIRE 7 : pointer to structure MEMOIRE .
 * - FCT_COUPLEUR 8 : pointer to structure VERSION_COUPLEUR .
 * - FCT_DOWNLOAD 9 : pointer to structure CR_DOWNLOAD .
 * - FCT_ACQUIT_DOWNLOAD 10 : nothing.
 * - FCT_LIBELLE_TERMINAL 11 : string of 6 char + '/0' (total = 7 bytes)
 * - FCT_AFF_REVEIL_DISPO 12 : not used.
 * - FCT_EXTENDED_SERIAL_NUMBER 13 : 16 digits serial number = array of 8 bytes.
 *
 * @return 0 if OK.
 *
 * @link KSFAM_DIAG Back to top @endlink
 * !see \ref read_terminal_informations
 */ 
int lire_infos_terminal(int function_id, void *pResult);


/*! @brief This function can be used for hardware identification.
 * @param indiceFct : define in diagdef.h :
 * - FCT_INFOS_TERMINAL 1
 * - FCT_TOUTES_INFOS 5
 * - FCT_COUPLEUR 8
 * - FCT_LIBELLE_TERMINAL 11 : string of 6 char + '/0' (total = 7 bytes)
 *
 * @param pResu : pointer to an object according to indiceFct parameter :
 * - FCT_INFOS_TERMINAL 1 : pointer to structure INFOS_TERMINAL .
 * - FCT_TOUTES_INFOS 5 : pointer to structure INFOS_TERMINAL .
 * - FCT_COUPLEUR 8 : pointer to structure VERSION_COUPLEUR .
 * - FCT_LIBELLE_TERMINAL 11 : pointer to a 6 char string.
 *
 * @return 0 if OK.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int lire_infos_PPR(int indiceFct, void *pResu);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief archive_diagnostic gets the diagnosis of the terminal. 
 *
 * The internal diagnosis will be copied in the 'label' disk.
 * @param label : label of the disk where the diagnosis will have to be stored.
 * @return none
 * @note The disk must be mount and exist before calling this function.
 * @par Example:

 * @include oem_public_Sample_04.c
 *    
 * @link KSFAM_IOSF Back to top @endlink
 */ 
void archive_diagnostic(char *label);


/*! @}  */ 


/*! @addtogroup KSFAM_M2OS
	* @{
 */ 

/*! @brief Delete an application
 * @param num_segment : rank of the application during the loading.
 * @return
 * - 0 if succeed,
 * - otherwise -1
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
int suppr_info_seg_appli(short num_segment);



/*! @brief Suppress an application and its files in flash memory from the terminal.
 * param type_appli : Application type (field of ADF file)
 * @return 0 if OK.
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
int suppr_appli(unsigned short type_appli);


/*! @}  */ 


/*! @addtogroup KSFAM_KBD
	* @{
 */ 

/*
==================
	driver buzzer
==================
*/


/*! @brief This function activates a param etrizable beep. It must be stopped with StopBuzzer.
 * @param diviseur : dividor value :
 *
 * - diviseur = 0 -> divide by 2.
 * - diviseur = 1 -> divide by 8.
 * - diviseur = 2 -> divide by 32.
 * - diviseur = 3 -> divide by 128.
 * - diviseur = x -> divide by 1024.
 *
 * @param duree_high : activation time (part of period).
 * @param duree_totale : total time (period).
 * @return None.
 * @note Example of use :
 * - StartBuzzer(0, 0x1300, 0x2600);
 * - Freq Buzzer = Bus Frequency / period / 2
 * - Freq Buzzer = 57 000 000 Hz / 2600 / 2 = 3000 Hz.
 *
 * @b Example (to control sound volume)
 * @include oem_public_Sample_22.c
 * @link KSFAM_KBD Back to top @endlink
 */ 
int StartBuzzer (unsigned char diviseur,  unsigned short int duree_high , unsigned short int duree_totale );



/*! @brief This function stops the beep previously activated by StartBuzzer.
 * @return None.
 *
 * @link KSFAM_KBD Back to top @endlink
 */ 
int StopBuzzer (void);



/*! @brief This function activates the buzzer during a multiple of 10 milliseconds given as parameter.
 * @param Duree_P : duration operates in units of 10 milliseconds.
 * @return None.
 *
 * @link KSFAM_KBD Back to top @endlink
 */ 
void buzzer(unsigned short Duree_P);



/*! @}  */ 



/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief calcrc calculates CRC 16 for parameter buffer.
 * @param buffer : buffer on witch CRC 16 is calculated.
 * @param size : size of the buffer in bytes.
 * @return CRC 16 calculated.
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
unsigned short  calcrc(void *buffer, unsigned int size);


/*! @}  */ 


/*! @addtogroup KSFAM_DIAG
	* @{
 */ 

/* utilisation de la multi-application */

/*! @brief This function is used to determine the number of segments in the terminal.
 * @return The number of applications (including manager) in terminal.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int num_seg    (void);






#define boot_info entete_message_ident


/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*! @brief The purpose of this function is to enable / disable the paper feed key. 
 *
 * It only affects application ( not the O/S ). The default value is ON after a reset.
   A paper feed disabling must be followed by a paper feed enabling
 * @param newState :
 * - ON paper feed key enabled
 * - OFF paper feed key disabled
 *
 * @return None.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
void paper_feed(unsigned char newState);


/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

// fichier>.c

/*! @brief Suppress a DLL from the terminal
 * @param name : family name.
 * @return 0 if OK.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int suppr_dll(char *name);


/*! @}  */ 


/*! @addtogroup KSFAM_M2OS
	* @{
 */ 

//diagnostic.c

/*! @brief This routine returns the terminal type.
 * @param pt : string. Length = 12 characters.
 * @return None.
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
void entete_message_ident(char *pt);


/*! @}  */ 



/*! @addtogroup KSFAM_OS
	* @{
 */ 

//MMU

/*! @brief umalloc allocates memory for an user application idem standardANSI malloc and free.
 * @param size : size of memory to allocate. size range : from 0 to 4 Mb. 
   The total allocation size allocated by an application can reach to a maximum of 4 Mb.
 * @return
 * - Pointer to the beginning of the area allocated if successfull.
 * - Null pointer otherwise.
 *
 * @note The allocated memory area is not accessible for other applications.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
void *umalloc(unsigned int size);



/*! @brief Free of memory for an user application idem standard ANSI malloc and free.
 * @param p : adress of allocated area by umalloc.
 * @return None.
 * @note The memory free by ufree can't be reusable by another application. The memory is still available for the current application.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
void ufree(void*p);



/*! @brief HeapFree returns the size of the private heap of the current application.
 * @return heap size.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
unsigned int HeapFree(void);



/*! @brief Allocates memory segment in application user space and copy previous data in new segment.
 * @param old_p : Previous memory segment pointer
 * @param new_size : Expected size
 * @return
 * - New memory segment pointer.
 * - NULL.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
void *urealloc(void *old_p, unsigned int new_size);


/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*
==================
	Modem
==================
*/

/*! @brief esc_command returns to command mode. 
 *
 * This function is used to send commands to the modem when it is in line mode. This routine outputs ++ on the line.
 * @return 0 if command has been correctly executed.
 * @note The ATO command is used to return to data mode.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
void esc_command(void);


/*! @}  */ 


/*! @addtogroup KSFAM_DIAG
	* @{
 */ 

/*
==================
	trace
==================
*/


/*! @brief This functions is used to send a trace.
 * @param sap_id : Service Access Point identifier.
 * @param length : Length of trace data.
 * @param data : Trace data.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
void trace(trace_sap_id_t sap_id, unsigned int length, const void* data);


/*! @}  */ 



/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*
==================
	Booster
==================
*/


/*! @brief This function enables the simulation of an input peripheral.
 * @param periph : Name of the simulated peripheral. "KEYBOARD", "SWIPE2", "SWIPE31" "SWIPE3" supported
 * @param len : Length of input Data in bytes.
 * @param buf : buffer containing data to be simulated.
 * @return
 * - TRUE if simulation succesfull. 
 * - FALSE in case of problem.
 *
 * @note In case of simulation of SWIPE2, or SWIPE31, the data must be compliant with ISO 7813 formats.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int input_sim(char * periph, int len, unsigned char *buf);


/*! @}  */ 


/*! @addtogroup CHIP_Utilities
	* @{


 * @include oem_public_Sample_05.c
 *
 * @link CHIP_Utilities Back to top @endlink


 @}  */
 

/*! @addtogroup CHIP_GPM271
	* @{


 * @include oem_public_Sample_06.c
 *
 * @link CHIP_GPM271 Back to top @endlink


 @}  */ 





/*! @addtogroup CHIP_S9
	* @{


 * @include oem_public_Sample_07.c
 *
 * @link CHIP_S9 Back to top @endlink


 @}  */
 


/*! @addtogroup CHIP_S10
	* @{


 * @include oem_public_Sample_08.c
 *
 * @link CHIP_S10 Back to top @endlink


 @}  */






/*! @addtogroup CHIP_GPM896
	* @{


 * @include oem_public_Sample_09.c
 *
 * @link CHIP_GPM896 Back to top @endlink


 @}  */





/*! @addtogroup CHIP_GFM
	* @{


 * @include oem_public_Sample_10.c
 *
 * @link CHIP_GFM Back to top @endlink


 @}  */
 

/*! @addtogroup CHIP_SLE4436
	* @{



 * @include oem_public_Sample_11.c
 *
 * @link CHIP_SLE4436 Back to top @endlink


 @}  */



/*! @addtogroup Code_Power
	* @{


 * @include oem_public_Sample_12.c
 *
 * @link Code_Power Back to top @endlink
 

 @}  */





/*! @addtogroup Code_Read
	* @{


 * @include oem_public_Sample_13.c
 *
 * @link Code_Read Back to top @endlink


 @}  */


/*! @addtogroup Code_Write
	* @{


 * @include oem_public_Sample_14.c
 *
 * @link Code_Write Back to top @endlink


 @}  */



/*! @addtogroup Code_Erase
	* @{


 * @include oem_public_Sample_15.c
 *
 * @link Code_Erase Back to top @endlink


 @}  */



/*! @addtogroup Code_Key 
	* @{


 * @include oem_public_Sample_16.c
 *
 * @link Code_Key Back to top @endlink


 @}  */



/*! @addtogroup Code_C4 
	* @{


 * @include oem_public_Sample_17.c
 *
 * @link Code_C4 Back to top @endlink


 @}  */
 


/*! @addtogroup CHIP_SLE4404 
	* @{


 * @include oem_public_Sample_18.c
 *
 * @link CHIP_SLE4404 Back to top @endlink


 @}  */
 


/*! @addtogroup CHIP_AT88SC1003 
	* @{


 * @include oem_public_Sample_19.c
 *
 * @link CHIP_AT88SC1003 Back to top @endlink


 @}  */
 


/*! @addtogroup CHIP_AT88SC102 
	* @{


 * @include oem_public_Sample_20.c
 *
 * @link CHIP_AT88SC102 Back to top @endlink


 @}  */
 


/*! @addtogroup CHIP_AT88SC1608 
	* @{


 * @include oem_public_Sample_21.c
 *
 * @link CHIP_AT88SC1608 Back to top @endlink

 @}  */
 
 
#endif   // __OEM_PUBLIC_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif

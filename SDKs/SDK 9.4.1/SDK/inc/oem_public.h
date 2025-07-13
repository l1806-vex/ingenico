#ifndef OEM_PUBLIC_H
#define OEM_PUBLIC_H

#include "basearm.h" // Word typedef

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


#ifdef _GSIM_
// analyse GSIM : a ajouter si non defini par les autres includes
typedef __builtin_va_list   __gnuc_va_list;
typedef __gnuc_va_list   va_list;
#endif

// suppression des majuscules pour analyse GSIM
#include "rtctime.h"
#include "trace_sap.h"

// time slice
#define XecTimeUnit        10 			//OS_k_TICK 	(10 ms par coup d'horloge)

#define TIMEOUT	           0				/*!< value returned by ttestall if timeout occured */
#define EOF                (-1)			/*!< value returned by many OEMC functions (ferror, ...)  */
#define NO_SEM             0xFF			/*!< Value used when no semaphore is associated to OEMC FILE */
#define NOTASK             0xFFFF		/*!< value used when OEMC FILE is not opened */

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


// Event associated to OEMC FILE
//! \defgroup OEMC_PER_BITS Events associated to OEMC FILE
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
/*        Events 12, 13, 14, 15 are available for M2OS        */
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
/*        Events 29, 30, 31 are available for M2OS        */
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

/*! @brief Define the structure of a buffer. */
typedef struct {
      unsigned char *addr;							/*!< address of the buffer */
      unsigned char *readptr;						/*!< pointer to address of next character to read */
      unsigned char *writeptr;					/*!< pointer to address of next character to write */
      unsigned short int   size;				/*!< size of the buffer in max different elements */
} Buffer;


/*! @brief Define the structure of a file. */
typedef struct {
      unsigned char    _descr;					/*!<  number of channel, neccessary for _INCHRW */
      Buffer _send;											/*!< buffer for sending */
	  	Buffer _rec;											/*!< buffer for receiving */
      unsigned short int   _task;				/*!< owner of the channel (0xFFFF = unused) */
      unsigned short int   _event;			/*!< event to occur when waiting for in- or output */
      unsigned short int 	 _error;			/*!< indicates the error (if one has occurred) */
      char  _unget_char;								/*!< character which has been 'unget' */
      unsigned char _state;							/*!< state of the channel */
      unsigned char _mode;							/*!< mode of the channel (read,write,reset,..) */
      unsigned char _masque;						/*!< mask of the state wich lead to events */
      unsigned char _raison;						/*!< event goal */
      unsigned char _autsend;						/*!< authorization of sending */
      unsigned char _autreceive;				/*!< authorization of  reception */
      void *PtData;											/*!< pointer to the data. */
}FILE;

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

/*! @brief This function is used to check and format the ISO1 stripe buffer.
 * @param stream : Address of SWIPE31 file. *stream, uses the same peripheral as ISO3 driver
   ( SWIPE31 peripheral event, file handle ).
 * @param length : length of swipe_read parameter.
 * @param swipe_read : data read on the swipe.
 * @return
 * - length : not used ( always returned 00 )
 * - ASCII-formatted card buffer ( 79 characters Max ) , swipe_read
		%.............^............ ? 'LRC' in ASCII
		% and ? characters are defined as ISO1 sentinels
		^ character is ISO1 separator
		( several ^ characters can be found on track 1 ).
 * - Returns ISO 1 status
 * - ISO_OK if card is ISO 1 compatible
 * - DEF_SEP if separator fault detected
 * - DEF_PAR if parity fault detected
 * - DEF_LRC if LRC fault detected
 * - NO_DATA if no readable data detected
 *
 * @note The following checks are performed for the ISO1 stripe :
 * - check of sentinels presence (%, ?)
 * - length : stripe length must be less than or equal to 79 characters
 * - character parity
 * - LRC fault
 *
 *  ISO1 separator (^) is not checked.
 *
 *  The is_iso1 function must always be preceded by the fopen function on the swipe31 peripheral .
	  SWIPE31 event can occur at the same time as SWIPE2 event, this is very
	  important when application waits for both events and returns from ttestall
 *
 * Note:
 * If the read magnetic track contains non ISO character or has a non 
 * ISO format, you can recover raw track stream of bits by 
 * using fread(). To build your own algorithm to re-form data from 
 * magnetic tracks, you have to consider that stream of bits may differ 
 * according to terminal types and to read cards (= number of 
 * synchronisation bits may differ). 
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:is_iso1:KSFAM_CARD:0x03
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:DATA_SIZE(110)
//  @GSIM_A:3:OUT_ONLY
// \endif
int is_iso1(FILE *stream,unsigned char *length,unsigned char *swipe_read);


/*! @brief This function is used to check and format the ISO2 stripe buffer.
 * @param stream : pointer to FILE.
 * @param length : length of swipe_read parameter.
 * @param swipe_read  : data read on the swipe.
 * @return PAN length : 13, 16, 19 are standard lengths.
		ASCII-formatted card buffer ( 40 characters Max ) , BUFFER_PISTE.
		B.............D..............F 'LRC' in ASCII
 *
 * Returns ISO 2 status :
 * - ISO_OK if card is ISO
 * - DEF_SEP if separator fault detected
 * - DEF_PAR if parity fault detected
 * - DEF_LRC if LRC fault detected
 * - DEF_LUH if LUHN fault detected
 * - DEF_NUM if numerical fault detected
 * - NO_DATA if no readable data detected
 *
 * @note The following checks are performed for the ISO2 stripe :
 * - Check of separators (B,D,F) and length (stripe length less than or equal to
		 40 characters), character parity, stripe LRC, luhn code, numerical fault.
 * - The is_iso2 function must always be preceded by the fopen function on the swipe2 peripheral.
 *
 * Note:
 * If the read magnetic track contains non ISO character or has a non 
 * ISO format, you can recover raw track stream of bits by 
 * using fread(). To build your own algorithm to re-form data from 
 * magnetic tracks, you have to consider that stream of bits may differ 
 * according to terminal types and to read cards (= number of 
 * synchronisation bits may differ). 
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:is_iso2:KSFAM_CARD:0x01
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:DATA_SIZE(45)
//  @GSIM_A:3:OUT_ONLY
// \endif
int is_iso2(FILE *stream, LG_REF_CLI *length, BUFFER_PISTE swipe_read);


/*! @brief This function is used to check and format the ISO3 stripe buffer.
 * @param stream : pointer to FILE.
 * @param length : length of swipe_read parameter.
 * @param swipe_read  : data read on the swipe.
 * @return PAN length : not used ( always returned 00 )
		ASCII-formatted card buffer ( 107 characters max ) , swipe_read
		B.........................F 'LRC' in ASCII
		several D delimiters can be found on the track 3.
 * - Returns ISO 3 status
 * - ISO_OK if card is ISO
 * - DEF_SEP if separator fault detected
 * - DEF_PAR if parity fault detected
 * - DEF_LRC if LRC fault detected
 * - DEF_NUM if numerical fault detected
 * - NO_DATA if no readable data detected
 *
 * @note The following checks are performed for the ISO3 stripe :
 * - Check of separators (B,F) and length (stripe length less than or equal to 107
		 characters), character parity, stripe LRC, numerical fault.
 * - The is_iso3 function must always be preceded by the fopen function on the swipe31 peripheral.
 * - SWIPE31 event can occur at the same time as SWIPE2 event, this is very
		 important when application waits for both events and returns from ttestall
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:is_iso3:KSFAM_CARD:0x02
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:DATA_SIZE(110)
//  @GSIM_A:3:OUT_ONLY
// \endif
int is_iso3(FILE *stream,unsigned char *length,unsigned char *swipe_read);


/*! @brief dec_iso1 is used for decoding ISO1 stripe.
 * @param swipe_read_length : customer reference length if decoded, char decoded count otherwise
 * @param data_bit[data_bit_length] : bit buffer with following bits arrangement [01234567][89......] right justified with 0 bits
 * @param swipe_read[ISOx_LEN] : decoded chain (not null terminated if up to ISOx_LEN char decoded)
 * @param data_bit_length : data_bit length
 * @return same as is_isox()
 */
int dec_iso1(unsigned char*swipe_read_length,unsigned char*swipe_read,unsigned char*data_bit,int data_bit_length);

/*! @brief dec_iso2 is used for decoding ISO2 stripe.
 * @param swipe_read_length : customer reference length if decoded, char decoded count otherwise
 * @param data_bit[data_bit_length] : bit buffer with following bits arrangement [01234567][89......] right justified with 0 bits
 * @param swipe_read[ISOx_LEN] : decoded chain (not null terminated if up to ISOx_LEN char decoded)
 * @param data_bit_length : data_bit length
 * @return same as is_isox()
 */
int dec_iso2(unsigned char*swipe_read_length,unsigned char*swipe_read,unsigned char*data_bit,int data_bit_length);

/*! @brief dec_iso3 is used for decoding ISO3 stripe.
 * @param swipe_read_length : customer reference length if decoded, char decoded count otherwise
 * @param data_bit[data_bit_length] : bit buffer with following bits arrangement [01234567][89......] right justified with 0 bits
 * @param swipe_read[ISOx_LEN] : decoded chain (not null terminated if up to ISOx_LEN char decoded)
 * @param data_bit_length : data_bit length
 * @return same as is_isox()
 */
int dec_iso3(unsigned char*swipe_read_length,unsigned char*swipe_read,unsigned char*data_bit,int data_bit_length);

#define SWP_FIOCTL_CONFIG_SWIPE		0x9000			/*!< fioctl for ISO2 and ISO31 : select which swipe is activated 
                                               parameter int : SWP_INTERNAL / SWP_PINPAD / SWP_BOTH
                                               */
// 

#define SWP_FIOCTL_GET_USED_SWIPE	0x9001			/*!< fioctl for ISO2 and ISO31 : gets which swipe is activated  
                                               parameter int : SWP_INTERNAL / SWP_PINPAD
                                               */

#define SWP_INTERNAL	0		/*!< fioctl SWP_FIOCTL_CONFIG_SWIPE : Internal Swipe used */
#define SWP_PINPAD		1		/*!< fioctl SWP_FIOCTL_CONFIG_SWIPE : PinPad swipe used */
#define SWP_BOTH			2		/*!< fioctl SWP_FIOCTL_CONFIG_SWIPE : Use internal and pinpad swipe */

#define SWP_FIOCTL_GET_USED_HEAD 0x9002			/*!< fioctl for ISO2 and ISO31 : Get type of magnetic head
                                                 parameter typre int : SWP_NORMAL / SWP_MAGTEK
                                             */
#define SWP_NORMAL   0		/*!< fioctl SWP_FIOCTL_GET_USED_HEAD : Normal head */
#define SWP_MAGTEK   1		/*!< fioctl SWP_FIOCTL_GET_USED_HEAD : MAGTEK head */


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
/* @GSIM_T:T_VERSION:SUPPLIED(BUF_SER_T_VERSION;BUF_DES_T_VERSION) */
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
/* @GSIM_T:SEGMENT:SUPPLIED(BUF_SER_SEGMENT;BUF_DES_SEGMENT) */
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

/*
==================
		oem.c
==================
*/

/*! @brief OEM_exit performs a startup of the Terminal. 
 *
 *  This routine records a startup diagnostic.
 *
 *  The diagnostic code is given by the parameter code.
 * @param code : diagnostic code. Diagnostic codes are described in file defdiag_TSys.h.
 * @return None
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OEM_exit:KSFAM_AUTRES:0x40
//  @GSIM_S:OEM_exit:E_OEM_exit
// \endif
void	OEM_exit(int code);

/*! @brief sem_user gets semaphore identifier using specified index.
 *
 * @param index : semaphore index.
 * @return semaphore identifier
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:sem_user:KSFAM_AUTRES:
//  @GSIM_S:sem_user:E_sem_user
// \endif
Word	sem_user(int index);

/*! @brief mailbox_user gets mailbox identifier using specified index.
 *
 * @param index : mailbox index.
 * @return mailbox identifier
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:mailbox_user:KSFAM_AUTRES:
//  @GSIM_S:mailbox_user:E_mailbox_user
// \endif
Word	mailbox_user(int index);

/*! @brief delay_user gets delay identifier using specified index.
 *
 * @param index : delay index.
 * @return delay identifier
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:delay_user:KSFAM_AUTRES:
//  @GSIM_S:delay_user:E_delay_user
// \endif
Word	delay_user(int index);

/*! @brief task_user gets task identifier using specified index.
 *
 *  Only for compatibility : not to be used
 *
 * @param index : task index.
 * @return -1
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:task_user:KSFAM_AUTRES:
//  @GSIM_S:task_user:task_user
// \endif
Word	task_user(int index);

#define exit	OEM_exit
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


/*! @addtogroup KSFAM_FIC
	* @{
 */ 


/*
==================
	oem_open.c
==================
*/


/*! @brief fopen opens a file with a file_name and associates a buffer to this file.
 * @param *file_name : name of file .
 * @param *type : type of opening.
 * @return
 * - pointer to FILE structure.
 * - null pointer if the function has not been correctly executed.
 * @note 
 *  The peripheral files must be opened in all cases to drive a peripheral.
 *
 *  The standard peripheral files are : KEYBOARD, DISPLAY, PRINTER, SWIPE2, SWIPE3, SWIPE31,
		CAM0, CAM1, COM0, COM1, MODEM, SAM1, SAM2, SAM3, SAM4, IAPP.
 *
 *  These files are created by the software on initialisation if the peripherals are present.
		For other peripherals have a look to other documentation.
 *
 *  The following opening types are available :
 * - The '-' option is used to wait for a peripheral to be released (non-ANSI). In this case,
		the function waits for release of the peripheral by another task before turning over control
		to the calling task (indispensable for the printer).
 * - The '*' option is used to obtain a report complying with C ANSI requirements. This opening
		option is used to select the processing when a problem occurs (peripheral already open,
		port non-existent) ; by default, when a problem occurs, it generates a RESET and stores a
		diagnostic information. If the '*' option is positioned, the fopen will comply with the C ANSI
		return as well as the other functions (fclose, etc.).
 * - The 'a' option is used to avoid resetting the context when opening a peripheral. This function
		is implemented for the DISPLAY, for example.
 * - The standard options accepted are 'r' and 'w' for read and write.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fopen:KSFAM_FIC:0x01
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:IN_ONLY
// \endif
FILE *fopen(const char *file_name, const char *type);


/*! @brief fclose closes a file which has been opened by fopen.
 * @param *stream : pointer to file structure.
 * @return
 * - Return 0 if OK.
 * - EOF if problem is detected.
 *
 * @note
 * - Writing in the file takes place immediately.
 * - A peripheral which is closed during a dialogue will reset the dialogue
		 buffers and wait for a stable peripheral status before turning over control.
 * - Fclose on the modem peripheral is only permitted provided the line is cut
		 off, otherwise the terminal will generate a diagnostic indication and perform a reset.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fclose:KSFAM_FIC:0x02
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int fclose(FILE *stream);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief reset_buf resets a peripheral file. 
 *
 * This function resets a peripheral buffer.
 * @param stream : peripheral where buffer is to be reset.
 * @param id_buffer : buffer identification. id_buffer can take following values :
 * - _send_id : transmission buffer
 * - _receive_id : reception buffer
 *
 * @return None
 * @note It also clears the reception related events (see APPENDIX B)
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:reset_buf:KSFAM_IOSF:0x02
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int reset_buf(FILE *stream,int id_buffer);

/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

/*! @brief __STDIN returns the FILE handle of standard input (keyboard, generally).
 * @return
 * - 0 if standard input is not open (keyboard generally).
 * - FILE * otherwise.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:__STDIN:KSFAM_FIC:0x16
//  @GSIM_A:0:ONE_ADDRESS
// \endif
FILE *__STDIN(void);


/*! @brief __STDOUT returns the FILE handle of standard output (screen generally).
 * @return
 * - 0 if the screen is not open.
 * - FILE * otherwise.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:__STDOUT:KSFAM_FIC:0x17
//  @GSIM_A:0:ONE_ADDRESS
// \endif
FILE *__STDOUT(void);


/*! @brief stdprt returns the FILE structure of the printer.
 * @return
 * - 0 if the printer is not open.
 * - FILE * otherwise.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:__stdprt:KSFAM_FIC:0x1B
//  @GSIM_A:0:ONE_ADDRESS
// \endif
FILE *__stdprt(void);

#define stdin()    __STDIN()			/*!< Gets OEMC FILE standard input */
#define stdout()   __STDOUT()			/*!< Gets OEMC FILE standard output */

/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*! @brief ttestall is used to place the calling task in a standby status for reactivation on an event.
 *
 *  When an event arrives on a peripheral, the function reads the status of the concerned peripheral
	  and acknowledges the event (reset) if the event was produced by a completed action (transmission
	  buffer empty or end-of-transmission).
 * @param events : expected-peripherals in the form of a 32-bit long word :
	  CAM0, CAM1, SWIPE2, SWIPE31, COM0, COM1, MODEM, IAPP,
		KEYBOARD, PRINTER, PINPAD . Or00 if no peripheral is expected (case of pause).
 * @param TimeOut : operates in units of 10 milliseconds. To set an infinite timeout value TimeOut = 0.
 * @return Expected peripherals positioned in the form of a 32-bit long word mask or 00 for time-out.
 * - BIT 0 : KEYBOARD
 * - BIT 1 : PRINTER
 * - BIT 2 : COM0
 * - BIT 3 : COM1
 * - BIT 4 : MODEM
 * - BIT 5 : CAM0
 * - BIT 6 : CAM1
 * - BIT 7 : SWIPE2
 * - BIT 8 : IAPP
 * - BIT 9 : SWIPE31
 * - BIT 10 : COM5
 * - BIT 11 : COM6
 * - BIT 12 : Manager event. This bit cannot be used by applications
 * - BIT 15 : available for  application
 * - BIT 16 : PPR KEYBOARD 
 * - BIT 17 : IAPP PPR
 * - BIT 18 : CAM2, CAM9, COM11
 * - BIT 19 : COM2
 * - BIT 20 : MOUSE, CLESS
 * - BIT 21 : KEYBOARD USB
 * - BIT 22 : SWIPE3
 * - BIT 23 : DRV_GPRS
 * - BIT 24 : DRV_UMS
 * - BIT 25 : DBLUETOOTH
 * - BIT 26 : COM3 and USB serial drivers (COM20, COM21, COM_KEYSPAN, COM_SL, ...)
 * - BIT 27 : TSCREEN
 * - BIT 31 : available for  application
 *
 * @link OEMC_PER_BITS Events associated to OEMC FILE @endlink
 *
 * @note
 *
 *  Events not linked to peripherals are systematically cleared by ttestall.
 *
 *  Application must handle all of the events positioned as a ttestall return.
 *
 *  Non peripherals events can be used by the user by means of event positioning primitives : see [3].
 *
 *  Caution :
 * - if both parameters are 0, the calling task will be blocked forever,
 * - this function does not clear end-of-reception events ; it is
		 necessary to read the entire buffer or call the reset_buf function,
 * - before calling ttestall, it is necessary to select the events expected by the mask_event function.
 * - The following instruction to get a peripheral event is now forbidden ttestall ( 1<<fd->event , .. )
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ttestall:KSFAM_OS:0x08
//  @GSIM_S:ttestall:E_ttestall
// \endif
unsigned int ttestall(unsigned int events,unsigned int TimeOut);


/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 


/*! @brief mask_event modifies conditions generating an event. 
 *
 * This function is used to modify the conditions by which an event, for a given peripheral, is obtained.
 * @param stream : peripheral where event mask is to be modified.
 * @param mask : value of mask
 * @return None
 * @note The values of the conditions for obtaining a peripheral event are given in Appendix B.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:mask_event:KSFAM_IOSF:0x03
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int mask_event(FILE *stream,unsigned char mask);


/*! @brief ChngEventFile modifies generating event for a specified peripheral. 
 *
 * This function is used to modify the event raised by the given peripheral to wake-up application task.
 * @param stream : peripheral to modify.
 * @param evt_nbr : event number to use (from 0 to 31)
 * @return :OK ou EOF
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ChngEventFile:KSFAM_IOSF
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int ChngEventFile(FILE* stream, unsigned short evt_nbr);



/*! @brief mask_event_read reads conditions generating an event. 
 *
 * This function is used to read the conditions by which an event, for a given peripheral, is obtained.
 * @param fd : peripheral where event mask is to be modified.
 * @param mask : value of mask.
 * @return None
 * @note The values of the conditions for obtaining a peripheral event are given in Appendix B.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:mask_event_read:KSFAM_IOSF:0x04
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
int mask_event_read(FILE *fd,unsigned char *mask);



/*! @brief status tests status of a peripheral. 
 *
 * This function is used to poll the peripheral.
 * @param fd : file address
 * @param ad_status : binary OR (|) of OEMC status bits for the specified peripheral
 * @return None
 * @note Given below are the status information items per peripheral :
 * - KEYBOARD : Keyboard FIFO not empty
 * - PRINTER : End of printing, Printing error, Printing buffer empty paper Out detection in bit 0.
 * - SWIPE2 / SWIPE31 : Track read
 * - CAM0 : 0 - No card inserted.
 *          1 - Card inserted (CAM_PRESENT).
 *          8 - Card removed (CAM_ARRACHEE).
 *          9 - Card inserted after a removal (CAM_PRESENT | CAM_ARRACHEE).
 * - CAM1 : Same as CAM0.
 * - CAM2 : Same as CAM0.
 * - COM0 : Transmission FIFO empty, reception FIFO not empty, end of transmission .
 * - COM1 : Transmission FIFO empty, reception FIFO not empty, end of transmission .
 * - MODEM : Transmission FIFO empty, reception FIFO not empty, end of transmission, Loss of carrier .
 * - MOUSE : tests presence of mouse.
 * - KEYBUSB : tests presence of USB keyboard.
 * - MASS STORAGE : tests the presence of USB mass storage.
 * - COM5 : tests the presence of a USB host.
 *
 * @link OEMC_STATUS_BITS Possible values returned by status @endlink
 *
 * Be careful not to confuse the flows associated to the stream file and the
   peripheral information bits (the modem defined below is the flow
   whereas MODEM is the bit associated to the peripheral for ttestall).
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:status:KSFAM_IOSF:0x01
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
void status(FILE* fd, unsigned char* ad_status);

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
// \if SIMULATION
//  @GSIM_F:FormatOem:KSFAM_IOSF:
//  @GSIM_S:FormatOem:E_FormatOem
// \endif
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
// \if SIMULATION
//  @GSIM_F:format:KSFAM_IOSF:0x10
//  @GSIM_S:format:E_format
// \endif
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


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

/*
==================
	reading.c
==================
*/

/*! @brief getc reads a character in a file.
 * @param stream : address of file where information will be read.
 * @return character read.
 * @note
 * This function only returns control provided a character has been read. The
   function blocks the current task while waiting for a character to be read. To
   avoid blocking the calling task, the status of the peripheral reception buffer
   must be tested before calling.
 *
 * In case of serial link, the function returns EOF when an end-of-file or a
   reception error has been detected. The ferror routine must be used to
   determine the type of error.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:getc:KSFAM_FIC:0x0C
//  @GSIM_A:1:ONE_ADDRESS(4)
// \endif
int getc(FILE *stream);



/*! @brief fgets reads a string from a file.
 * @param s : address of character string read.
 * @param n : maximum number of characters to be read
 * @param stream : file address where information will be read,
 * @return
 * - s : address of string s if OK,
 * - null pointer otherwise.
 *
 * @note This function only returns control provided an end of string condition is
   detected (i.e /n or /0 or EOF ) .
 *
 * @b Caution : There is no time out supervision ; there is a potential risk of
   blocking the calling task if the end of string condition is not detected.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fgets:KSFAM_FIC:0x0F
//  @GSIM_A:3:ONE_ADDRESS
// \endif
char* fgets(char *s,int n,FILE *stream);



/*! @brief fread : copies, starting from address indicated by ptr, a number of data
    items , (nitems) having indicated size in file buffer.
 * @param ptr : pointer used to read into a file
 * @param size : size of item handled.
 * @param nitems : number of items handled.
 * @param stream : address of FILE.
 * @return
 * - number of items read in file buffer if Ok
 * - 0 if nothing has occurred.
 *
 * @note
 * The fread function used for a serial link (MODEM, COM0, COM1) must be used with a size=1 (char)
 * In this case, fread does not return the number of characters requested when a reception error is detected. 
 *
 * The user must therefore request the ferror() function to determine the cause of the reception error.
 *
 * If the reception buffer is empty (see status function), there is no error.
 *
 * If ferror is not called, the next call to fread will automatically clear the error and read the following characters.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fread:KSFAM_FIC:0x0A
//  @GSIM_A:1:DATA_CODE(size*nitems)
//  @GSIM_A:4: ONE_ADDRESS
// \endif
Telium_size_t fread(void *ptr, Telium_size_t size, Telium_size_t nitems,FILE *stream);



/*! @brief ungetc recovers last character from a file.
 * @param c : position of the character in file.
 * @param stream : address of file.
 * @return EOF if character could not be inserted.
 * @note character inserted can be recovered by next getc.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ungetc:KSFAM_FIC:0x10
//  @GSIM_A:2:ONE_ADDRESS
// \endif
int ungetc(int c,FILE *stream);


/*! @brief getchar reads a character from standard input.
 * @return character read.
 * @note
 * This function only returns control provided a character has been read. The
   function blocks the current task while waiting for a character to be read. To
   avoid blocking the calling task, the status of the standard input peripheral 
   must be tested before calling.
 *
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
#define getchar() getc(__STDIN())


/*
==================
	writing.c
==================
*/


/*! @brief putc writes a character in a file opened by fopen.
 * @param c : value of character
 * @param stream : pointer to FILE structure
 * @return
 * - 0 if OK.
 * - EOF if problem is detected.
 *
 * @note Writing in a file immediately triggers start up of the peripheral without
	  waiting for a start character. If the dialogue buffer is full, the routine waits
	  for a free space in buffer before returning control to the application.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:putc:KSFAM_FIC:0x03
//  @GSIM_A:2:ONE_ADDRESS
// \endif
int putc(int c, FILE *stream);


/*! @brief puts sends a character string to display.
 * @param s: formated string to be transmitted to output. Formated character string is addressed to standard output (display).
 * @return: Upon successful completion, fputs() returns a non-negative number. Otherwise, it returns EOF
 * @note Writing in a file immediately triggers initiation of the peripheral without waiting for a start character.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:puts:KSFAM_FIC:0x08
//  @GSIM_A:1:IN_ONLY
// \endif
int puts(const char *s);



/*! @brief fputs sends a character string to a file.
 * @param s : formatted string to be transmitted to output.
 * @param stream : pointer to specified FILE.
 * @return: Upon successful completion, fputs() returns a non-negative number. Otherwise, it returns EOF
 * @note Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character (except for printer).
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fputs:KSFAM_FIC:0x09
//  @GSIM_A:2:ONE_ADDRESS
//  @GSIM_A:1:IN_ONLY
// \endif
int fputs(const char *s, FILE *stream);



/*! @brief fwrite : recovers, starting from address indicated by ptr, a number of data
    items (nitems) with indicated size in stream file buffer.
 * @param ptr : pointer used to write into a file
 * @param size : size of item handled.
 * @param nitems : number of items handled.
 * @param stream : address of FILE.
 * @return
 * - number of items written in file buffer if Ok.
 * - EOF (-1) if an error has occurred (FILE not oppened in write mode) .
 *
 * @note Writing in a file immediately initiates start up of the peripheral without waiting for a start character.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fwrite:KSFAM_FIC:0x0B
//  @GSIM_A:1:DATA_CODE(size*nitems)
//  @GSIM_A:4:ONE_ADDRESS
// \endif
Telium_size_t fwrite(const void * ptr, Telium_size_t size, Telium_size_t nitems, FILE *stream);


/*
==================
	print.c
==================
*/


/*! @brief printf formats an output to display on screen.
 * @param format : string to be formatted. The character string to be formatted is addressed to the standard output (display).
 * @return
 * Upon successful completion, the printf() functions return the number of bytes transmitted  
 * If an output error was encountered, these functions return a negative value. 
 *
 * @note 
 * <ul><li>Writing in a file immediately triggers start up of the peripheral without
 *  waiting for a start character.</li>
 *  <li>"\x1b" clears the display</li></ul>
 *
 * @b Caution : the maximum size of the string to be formatted must not exceed 256 bytes.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:printf:KSFAM_FIC:0x05
//  @GSIM_S:S_printf:E_printf
// \endif
int printf(const char * format, ...);



/*! @brief pprintf formats an output to printer with flow control
 * @param format : String to be formatted. The character string to be formatted is addressed to the printer.
 * @return
 * - number of characters formatted if OK.
 * - -1 if problem is detected.
 *
 * @note <ul>
 *		<li>Standard printing mode: single-width, black on white background, 4-microline as interlining space,7*5 dots matrice printing.</li>
 *		<li>Printing modes:
 *			<ul>
 *				<li>Single and double-width printing (12 or 24 characters/line).</li>			
 *				<li>Printing in white on black background or black on white background.</li>
 				<li>Condensed mode printing:
 *				<ul>
 *					<li>character width reduced by 2 (24 or 48 characters/line)</li>
 * 					<li>interline modification</li>
 *				</ul>
 *				<li>Printing in bold font. The bold font printing mode is not compatible with the condensed mode</li>
 *			</ul>
 *		</li>
 *		<li>Fast paper feed by line feed increments</li>
 *		<li>Definition/editing of printable characters (\ref defprinterpatternHR).</li>
 *		<li>Formatting the margins via format routine (\ref format)<br>

 * @include oem_public_Sample_01.c
 * </li>
 *		<li>Font size changing via added ESC sequence</li>
 *		<li>Paper out detection via status routine</li>
 * </ul>
 *
 * @b Caution:<ul>
 * <li>Only the lines are printed. A line is terminated by "\n" or "\r".
 * <li>The maximum size of the string to be formatted must not exceed 128 bytes.</li>
 * <li>characters not forming part of the standard ASCII table (code exceeding 7F Hex) cannot be used directly in C language.</li>
 * 
 * </ul>
 * @b Commands
 * <table>
 * <tr><th></th><th>enable</th><th>disable</th></tr>
 * <tr><td>Return to the default mode (useful at the beginning and end of ticket to restore the default mode)</td><td>"\x1B""@"</td><td></td></tr>
 * <tr><td>Printout in white with black background</td><td>"\x1B""B1"</td><td>"\x1B""B0"</td></tr>
 * <tr><td>Printout in black with white background</td><td>"\x1B""B0"</td><td>"\x1B""B1"</td></tr>
 * <tr><td>User character printing (\ref defprinterpatternHR)</td><td>"\x1B""U"</td><td>"\x1B""V"</td></tr>
 * <tr><td>Modification of interlining space</td><td>"\x1B""A"\em n<br>with n(in hex) the number of dots for the line </td><td>"\x1B""@"</td></tr>
 * <tr><td>Bold font print</td><td>"\x1B""E"</td><td>"\x1B""F" or "\x1B""@"</td></tr>
 * <tr><td>Normal print mode</td><td>"\x1B""F"</td><td></td></tr>
 * <tr><td>Double height</td><td>"\x1B""H"</td><td>"\x1B""@" , "\r" or "\n"</td></tr>
 * <tr><td>Double width</td><td>"\xE"</td><td>"\x12" , "\r" or "\n"</td></tr>
 * <tr><td>Condensed mode</td><td>"\xF"</td><td>"\x12"</td></tr>
 * <tr><td>Normal mode</td><td>"\x12"</td><td></td></tr>
 * <tr><td>End of ticket (add some carriage returns to exit the ticket according to the terminal type) </td><td>"\xC"</td><td></td></tr>
 * </table>
 *
 * @b Example

 * @include oem_public_Sample_02.c
 * 
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:pprintf:KSFAM_FIC:0x06
//  @GSIM_S:pprintf:E_pprintf
// \endif
int pprintf(const char * format, ...);



/*! @brief fprintf writes in file opened by fopen.
 * @param stream : pointer to FILE structure.
 * @param format : string to be formatted.
 * @return
 * - number of characters formatted if OK.
 * - (-1) if problem detected.
 *
 * @note <ul><li> Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character.</li>
 		 <li>If the peripheral is PRINTER, refer to \ref pprintf to get the ESC sequences.</li>
 		 </ul>

 *
 * @b Caution: the maximum size of the string to be formatted must not exceed 256 bytes for a "COM" devices and 128 bytes for "PRINTER"
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fprintf:KSFAM_FIC:0x71
//  @GSIM_S:S_fprintf:E_vfprintf
// \endif
int fprintf(FILE *stream, const char *format,...);


/*! @brief sprintf writes in a string.
 * @param s      : pointer to string.
 * @param format : string to be formatted.
 * @return
 * - number of characters written in the string if OK.
 * - (-1) if problem detected.
 *
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:sprintf:KSFAM_FIC:0x71
// \endif
int sprintf(char *s, const char *format, ...);

/*
==================
	error.c
==================
*/


/*! @brief ferror returns error status linked to last file read operations.
 * @param stream : address of file.
 * @return
 * - EOF if access to file is unsuccessful (file not opened, file opened in write mode only, ...).
 * - file read status otherwise.
 *
 * @note Status of ferror function :
 *   OVERRUN_BUFFER 0xFF		  : OEMC buffer overrun 
 *   OVERRUN_ERROR  0x2000		: USART overrun error 
 *   FRAMING_ERROR  0x4000		: USART framing error 
 *   PARITY_ERROR   0x8000		: USART parity error
 * - 0 if no error present.
 *
 * bit mask should be used if ferror returns neither 0 nor 0xFF :
 *  if(ferror & FRAMING_ERROR  ) {  ==> framming error }
 *  if(ferror & OVERRUN_ERROR ) {  ==>overrun error }
 *  if(ferror & PARITY_ERROR) {  ==> parity error }
 *  other bits are not error flags
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ferror:KSFAM_FIC:0x11
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int ferror( FILE *stream);



/*! @brief clearerr clears file error indicator.
 * @param stream : file address.
 * @return None
 * @note After clearing the error on the character which should have been read, the
   character can be read by a function such as fgetc or fread.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:clearerr:KSFAM_FIC:0x13
//  @GSIM_A:1:ONE_ADDRESS
// \endif
void clearerr(FILE *stream);


/*! @}  */ 


/*! @addtogroup KSFAM_VISU
	* @{
 */ 


/*
==================
	visu.c
==================
*/


/*! @brief This function is used to position the cursor.
 * @param line : This parameter is used to give the line number.
 * @param column : This parameter is used to give the line column.
 * @return
 * - 0 if function has been executed,
 * - if not, returns -1.
 *
 * @note
 * - x and y may vary according to the display and font size.
 * - Using the small font ( 6* 8 pixels for a character ) on the 128*64 pixels
   display, x is between 0 and 7, y is between 0 and 20 .
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:gotoxy:KSFAM_VISU:
// \endif
int  gotoxy (int line, int column);



/*! @brief This function reads the cursor line number, or returns -1 if display is not open.
 * @return
 * - cursor line number if OK
 * - -1 otherwise.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:wherex:KSFAM_VISU:
// \endif
int  wherex (void);



/*! @brief This function reads the cursor column number, or returns -1 if display is not open.
 * @return
 * - cursor line number if OK.
 * - -1 otherwise.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:wherey:KSFAM_VISU:
// \endif
int  wherey (void);


/*! @}  */ 


/*! @addtogroup KSFAM_PPS
	* @{
 */ 

/*! @brief Set display position
 * @param stream : pointer on FILE.
 * @param line   : line number.
 * @param row    : column number.
 * @return
 * - OK (0)
 * - or -1.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:gotoxydsp:KSFAM_PPS:0x40
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int  gotoxydsp(FILE *stream, int line ,int row);


/*! @brief Return display cursor position (column)
 * @param stream : pointer on FILE
 * @return Column of display cursor position.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:wherexdsp:KSFAM_PPS:0x41
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int  wherexdsp(FILE *stream);


/*! @brief Return display cursor position (line)
 * @param stream : pointer on FILE
 * @return Line of display cursor position.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:whereydsp:KSFAM_PPS:0x42
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int  whereydsp(FILE *stream);

/*! @}  */ 


/*! @addtogroup KSFAM_VISU
	* @{
 */ 

/*! @brief The blink function is used to display future characters blinking.
 * @param flag : A bool parameter (ON for start blinking, OFF for stop blinking).
 * @return 0 if function has been executed.
 * @note Blinking is done in a background task.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:blink:KSFAM_VISU:
// \endif
int  blink  (int flag);



/*! @brief This function has been kept for compatibility purpose but does not operate
    any more on graphic display device such as EFT30.
 * @param flag : A bool parameter (ON for enabling, OFF for disabling).
 * @return 0 if function has been executed.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:cursor:KSFAM_VISU:
// \endif
int  cursor (int flag);



/*! @brief This routine configures the character font.
 * @param pdoth : number of horizontal dots.
 * @param pdotv : number of vertical dots.
 * @return None.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:startupcv20:KSFAM_VISU:
// \endif
void startupcv20 (char pdoth,char pdotv);


/*! @}  */ 


/*! @addtogroup KSFAM_PPS
	* @{
 */ 

/*! @brief Define a bitmap to display
 * @param Fp : pointer on FILE.
 * @param key : Hexadecimal value of byte to replace
 * @param pattern : Bitmap
 * @return
 * - OK (0)
 * - or -1.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:defdisplaypatterndsp:KSFAM_PPS:0x44
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:3:DATA_CODE(sizePattern(pattern))
//  @GSIM_A:3:IN_ONLY
// \endif
int defdisplaypatterndsp (FILE *Fp, char key,char *pattern);



/*! @brief Init size font for display
 * @param Fp : pointer on FILE.
 * @param pdoth : number of horizontal dot for a character
 * @param pdotv : number of vertical dot for a character
 * @return None
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:startupcv20dsp:KSFAM_PPS:0x43
//  @GSIM_A:1:ONE_ADDRESS
// \endif
void startupcv20dsp (FILE *Fp, char pdoth,char pdotv);

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
// \if SIMULATION
//  @GSIM_F:lire_infos_PPR:KSFAM_DIAG:
//  @GSIM_A:2:DATA_SIZE(80)
//  xxx choisir le buffer de plus grande taille.
// \endif
int lire_infos_PPR(int indiceFct, void *pResu);

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
// @GSIM_T:T_APDU:SUPPLIED(BUF_SER_T_APDU;BUF_DES_T_APDU)
typedef struct{
    unsigned char *data ;							/*!< data of the APDU. */
    unsigned int length ;							/*!< length of the APDU. */
} T_APDU ;

int CAMSPED_Mount(void);

/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 


#ifdef _DEPRECATED_SDK90_
/*! @brief This function is obsolete.
 *
 *  @deprecated Since the SDK 9.0
 *
 */
extern void encrit(void);		 /*!< @deprecated */
#endif


#ifdef _DEPRECATED_SDK90_
/*! @brief This function is obsolete.
 *
 *  @deprecated Since the SDK 9.0
 *
 */
extern int excrit(void);		 /*!< @deprecated */
#endif


/*! @brief A pointer on t_topstack is returned by a handle (fork) protected by the superuser mode. Don't try to read 'fur' value */
typedef struct{			
  char fur;
}t_topstack;


/*! @brief This function is used to create and start a user task
 * @param Startaddress : address of the entry point of the task
 * @param dummy1 : kept for for EFT10/20 compatibility purpose (USP is OS handled)
 * @param prior : This parameter allows to choose the priority level of the created task. 
 *  Priority level goes from -32 to +32. -32 corresponds to the highest priority level.
 * @return the task handle
 * @sa 
 *	- @link t_topstack topstack structure@endlink
 *
 * @b Include: to be defined in your application
 *
 * @b Compatibility: Non-ANSI
 *
 * @note  exit ( EXIT_MAX_TASK_NUMBER ) if no more task available (up to 20 tasks can be defined including task 1 )
 * - It must be called prior to any kernel routines
 * - stacks are located in O/S, user stack by 2Kb incremented up to 64Kb
 * - fork creates and starts the task
 * - Use CurrentTask to get the task number at task level
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
t_topstack *fork (word(*Startaddress) (),byte* dummy1, int prior );
                          
                          

/*! @brief task stopping and killing, fork must be called prior to kill routine. 
 *
 * It replaces StopTask / Terminate kernel routines.
 *
 * It is recommended to signal the task by sending an event before killing it.
 * @param TaskHdl1 : t_topstack pointer returned by fork routine when creating task
 * @param options  : see below.
 * - ""   reset if the task is using peripheral, a diagnostic is recorded EXIT_LINKED_TO_PERIPH in that case
 * - "-*" wait for peripheral closing by the task
 *
 * @return None
 *
 * @b Include: to be defined in your application
 *
 * @b Compatibility: Non-ANSI
 *
 *  @par Example:

 * @include oem_public_Sample_03.c
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
int kill ( t_topstack *TaskHdl1, char *options);



/*! @brief GiveNoTask converts one pointer to type t_topstack to an OEMC task number.
 * @param topstack : pointer on t_topstack structure. This pointer is returned by fork routine when creating task.
 * @return OEMC task number.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:GiveNoTask:KSFAM_OS:0x03
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern word        GiveNoTask (t_topstack *topstack);


//tms
//typedef struct {
//    char bidon;
//} S_PARAM_TLCHGT ;



/*! @}  */ 

/*! @addtogroup KSFAM_CARD
	* @{
 */ 

/*! @brief This routine executes an APDU command and handles the response according to EMV 3.1.1. 
 *
 * The protocol to be used is the one asked by the card at the reset time.
 * @param Fd_P : card flow address.
 * @param C_apdu : The APDU command.
 * @param R_apdu : The APDU response.
 * @return
 *<table><tr><th>Value</th><th>Description</th></tr>
 *<tr><td>\a 0</td><td>OK, no error.</td></tr>
 *<tr><td>\a 1</td><td>N.A.</td></tr>
 *<tr><td>\a 2</td><td>Invalid card because Answer To Reset is not EMV compliant.</td></tr>
 *<tr><td>\a 3</td><td>Card is mute.</td></tr>
 *<tr><td>\a 4</td><td>VCC or VPP problem.</td></tr>
 *<tr><td>\a 5</td><td>VCC or VPP problem.</td></tr>
 *<tr><td>\a 6</td><td>Communication problem (driver problem).</td></tr>
 *<tr><td>\a 7</td><td>Card removed.</td></tr>
 *<tr><td>\a 8</td><td>Unauthorized command as long as IUC is unsecured.</td></tr>   
 *</table>
 *  
 * @note
 * This routine is equivalent to send_receive_t1 () for T=1 protocol.
 *
 * In case of T=0 protocol, this routine executes automatically input and output commands according to EMV 3.1.1.
 *
 * If the chip card is EMV compliant, application does not need to know any more the card protocol.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:EMV_apdu:KSFAM_CARD:0x21
//  GSIM_A:1:ONE_ADDRESS
//  GSIM_A:2:ONE_POINTER
//  GSIM_A:2:IN_ONLY
//  GSIM_A:3:ONE_POINTER
//  GSIM_A:3:OUT_ONLY
//  @GSIM_S:EMV_apdu:E_EMV_apdu
// \endif
extern unsigned char EMV_apdu(FILE *Fd_P, T_APDU *C_apdu, T_APDU *R_apdu);



/*! @brief This function is used to shutdown the card per standard ISO 7816-3.
 * @param Fd_P : pointer to Card flow.
 * @return
 * - 0 if function has been correctly executed.
 * - 1 if card has already been removed.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  power_down:KSFAM_CARD:0x11
//  1:ONE_ADDRESS
// \endif
extern int power_down ( FILE *Fd_P );



/*! @brief This routine must be used instead of already existing power_down_gpm routine.
 * @param Fd_P : pointer to FILE structure. CAM0 only.
 * @return Always returned 00.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:power_down_sync:KSFAM_CARD:0x25
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern int power_down_sync ( FILE *Fd_P );


/*! @brief InitGkDrv init of CAM IFD context to use T=1 after T=0 ATR (Moneo specific)
 * @param Fd_P : Card flow address.
 * @param  arglist :
 * - arglist[0] : Convention (0 : same than ATR - 1 : direct convention - 2 : inverse convention)
 * - arglist[1] : ATR TA3 byte (which defines IFSC)
 * - arglist[2] : ATR TB3 byte (which defines CWI and BWI)
 * - arglist[3] : ruf
 * - arglist[4] : ruf
 * @return None.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern void InitGkDrv(FILE *Fd_P, va_list arglist);


/*! @brief Check the card according to EMV 3.1.1.
 * @param Fd_P : Card flow address.
 * @param pOctetsHisto_P : pointer to structure HISTORIC.
 * @return Read address for card history data generated by the reset pOctetsHisto_P. Return codes are unchanged :
 * - ok 0
 * - invalid card 2 Answer To Reset is not EMV compliant
 * - card is mute 3
 * - VCC or VPP problem 4/5
 * - communication problem 6
 * - card removed 7
 *
 * @note Accept T0 or T1 protocol. The card historical data may be :
 * - Manufacturer's identifier
 * - Mask number
 * - Lock word
 * - Status word 1
 * - Status word 2
 *
 * The history data are only recovered provided the function returns 0.
 *
 * The HISTORIC structure contains the length (up to 15 characters) and the history data.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:EMV_power_on:KSFAM_CARD:0x20
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
extern unsigned char  EMV_power_on ( FILE *Fd_P , HISTORIC *pOctetsHisto_P );



/*! @brief Check the card according to ISO7816  
 * @param Fd_P : Card flow address.
 * @param pOctetsHisto_P : pointer to structure HISTORIC.
 * @return Read address for card history data generated by the reset pOctetsHisto_P. Return codes are unchanged :
 * - ok 0
 * - invalid card 2 Answer To Reset is not EMV compliant
 * - card is mute 3
 * - VCC or VPP problem 4/5
 * - communication problem 6
 * - card removed 7
 *
 * @note Accept T0 or T1 protocol. The card historical data may be :
 * - Manufacturer's identifier
 * - Mask number
 * - Lock word
 * - Status word 1
 * - Status word 2
 *
 * The history data are only recovered provided the function returns 0.
 *
 * The HISTORIC structure contains the length (up to 15 characters) and the history data.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:power_on:KSFAM_CARD:0x20
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
extern int power_on ( FILE *Fd_P , HISTORIC *pOctetsHisto_P );



/*! @brief This function must be called when SLE4432/SLE4442 cards have to be powered- up.
 *
 * This routine must be used instead of already existing power_on_gpm routine.
 * @param Fd_P : CAM0 only.
 * @param PROTOCOL : protocole type.
 * @return
 * - 0 OK
 * - 5 VCC problem ( short circuit for example )
 * - 7 card removed
 *
 * @note This routine doesn't applied any voltage on VPP pin ( C6 contact ).
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:power_on_sync:KSFAM_CARD:0x24
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern int power_on_sync ( FILE * Fd_P,int PROTOCOL  );



/*! @brief This function is used to execute an input command per standard ISO 7816-3. 
 *
 * The function returns control following execution.
 * @param FILE : Card flow address.
 * @param COMMAND_CAM : Address of structure of input command.
 * @return
 * - 0 if function has been correctly executed
 * - 3 if card is silent
 * - 4 if VDC voltage fault detected
 * - 5 if VPP problem detected
 * - 6 if card communication fault detected
 * - 7 if card removed
 * - 8 if unauthorized command as long as IUC is unsecured
 * - 29Hex if card communication fault detected
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  input_command:KSFAM_CARD:0x12
//  1:ONE_ADDRESS
//  2:ONE_POINTER
// \endif
extern int input_command(FILE * FILE, COMMAND_CAM * COMMAND_CAM );



/*! @brief This function is used to execute an output command per standard ISO 7816-3.
 * @param stream : pointer to FILE. Card flow address.
 * @param outputcommand : Address of output command structure.
 * @return
 * - 0 if function has been correctly executed
 * - 3 if card is silent
 * - 4 if VDC voltage fault detected
 * - 5 if VPP problem detected
 * - 6 if card communication fault detected
 * - 7 if card removed
 * - 8 if unauthorized command as long as IUC is unsecured
 * - 29Hex if card communication fault detected
 *
 * @note The header includes 5 bytes :
 * - application class
 * - instruction code
 * - P1 card parameter
 * - P2 card parameter
 * - length of data to read from the card from 0 to 248.
 * 
 * The status words are only significant provided the function returns to 0.
 * 
 * These are updated by the operating system in the input structure.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
// \if SIMULATION
//  output_command:KSFAM_CARD:0x13
//  1:ONE_ADDRESS
//  2:ONE_POINTER
// \endif
extern int output_command(FILE *stream, COMMAND_CAM *outputcommand);


extern int f_sync_fct(FILE *stream,int NbParam,int *arglist);			/*!< Only for compatibility : do not use */



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


/*! @addtogroup KSFAM_VISU
	* @{
 */ 


/*! @brief This routine stops the backlight (for system usage).
 * @return None
 *
 * @note
 * This function is for system usage only and it declared here for compatibility.
 * The application must use \ref HWCNF_SetBacklightIntensity and \ref HWCNF_SetBacklightDuration functions for backlight management.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:StopRetroEclairage:KSFAM_VISU:
// \endif
int StopRetroEclairage (void);


/*! @brief StartRetroEclairage starts the backlight (for system usage).
 * @param diviseur : dividor value :
 * - diviseur = 0 -> divide by 2.
 * - diviseur = 1 -> divide by 8.
 * - diviseur = 2 -> divide by 32.
 * - diviseur = 3 -> divide by 128.
 * - diviseur = x -> divide by 1024.
 *
 * @param duree_high   : activation time (part of period).
 * @param duree_totale : total time (period).
 * @return None
 *
 * @note
 * This function is for system usage only and it declared here for compatibility.
 * The application must use \ref HWCNF_SetBacklightIntensity and \ref HWCNF_SetBacklightDuration functions for backlight management.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:StartRetroEclairage:KSFAM_VISU:
// \endif
int StartRetroEclairage (unsigned char diviseur,  unsigned short int duree_high , unsigned short int duree_totale );


/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

/*
==================
	print.c
==================
*/

/*! @brief putchar sends a character to display.
 * @param c : value of character.
 * @return
 * - the character sent if OK.
 * - EOF if problem is detected.
 *
 * @note stream file is standard output file (display).
		Writing in the display immediately triggers start up of the peripheral without waiting for a start
		character. If the dialogue buffer is full, the routine waits for a free space before turning over control to the application.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:putchar:KSFAM_FIC:0x04
// \endif
int putchar(int c);


/*! @brief vprintf formats an output (argc argv) (cf doc ansi C)
 * @param argc : Number of arguments
 * @param argv : array of arguments
 * @return cf doc ansi C
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
// \endif
int _vprintf(const char * argc, va_list argv );


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
// \if SIMULATION
// \endif
int vsprintf(char *, const char *, va_list );

/*
==================
	oem_cal.c
==================
*/


/*! @brief get_tick_counter returns the tick counter. one tick = 10 ms.
 * @return Number of elapsed ticks since startup.
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:get_tick_counter:KSFAM_AUTRES:0x08
// \endif
unsigned long int get_tick_counter (void);

/*! @}  */ 


/*! @addtogroup KSFAM_CAL
	* @{
 */ 

#define Wrong_Date (unsigned char)1

/*! @brief This function is used to check the date by verifying the coherency of the parameterized date.
 * @param date : pointer to structure DATE.
 * @return
 * - 0 if function has been correctly executed
 * - 1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ctrl_date:KSFAM_CAL:0x02
//  @GSIM_A:1:ONE_POINTER
// \endif
int  ctrl_date     (DATE *date);


/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*
==================
	Liaison serie
==================
*/


/*! @brief fbreak generates a break on communication port.
 *
 * Sends a logical 0 on TX signal for a duration of time.
 * @param stream : pointer to FILE.
 * @param time : time of break in miliseconds.
 * @return 0
 * @note send and receive can take values ON or OFF.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fbreak:KSFAM_IOSF:0x16
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int fbreak(FILE *stream, unsigned short time);


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
// \if SIMULATION
//  @GSIM_F:defprinterpatternHR:KSFAM_OS:
//  @GSIM_A:4:DATA_CODE(sizePattern(pattern))
//  @GSIM_A:4:IN_ONLY
// \endif
extern int  defprinterpatternHR (char weight, char density,char key,char *pattern);



/*! @brief This function replaces a standard character with a special character. 
 *
 * Up to 128 characters can be redefined.
 * @param key : ASCII value of key parameter
 * @param *pattern : Definition of character, pattern .
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if more characters are available.
 *
 * @note
 * - same routine as defprinterpattern
 * - allows to have common font between display and printer
 * - the key value will vary between 20 Hex and FF hex.
 * - Character code :
 * - 1 byte specifies the number of blank columns prior to the first column of dots
 * - 1 byte specifies the number of useful columns containing at least one dot
 * - x bytes : dot matrix represented for vertical with 8 dots defined, i.e. 1 byte per column as below :
 * - b0 highest line
 * - b1
 * - b2
 * - b3
 * - b4
 * - b5
 * - b6 lowest line
 * - b7 line under character
 * - 1 byte specifies if the character involves more than 1 'line' ( 8 dots ) is
 *
 * FF : all other value signifies last line.
 * - 1 byte specifies the number of blank columns after the last columns of dots.
 * - This sequence has to be repeated as long as lines have to be defined.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:defdisplaypattern:KSFAM_VISU:
//  @GSIM_A:2:DATA_CODE(sizePattern(pattern))
//  @GSIM_A:2:IN_ONLY
// \endif
int  defdisplaypattern (char key,char *pattern);



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
// \if SIMULATION
//  @GSIM_F:defprinterpattern:KSFAM_OS:
//  @GSIM_A:2:DATA_CODE(sizePattern(pattern))
//  @GSIM_A:2:IN_ONLY
// \endif
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
// \if SIMULATION
//  @GSIM_F:cnfbattery:KSFAM_AUTRES:0x03
// \endif
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
// \if SIMULATION
//  @GSIM_F:SetNextWakeUp:KSFAM_OS:
//  @GSIM_A:1: ONE_POINTER
// \endif
int SetNextWakeUp(DATE* pt_date);



/*! @brief This routine suppresses characters redefined by the user.
 * @return None.
 *
 * @link KSFAM_VISU Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:dspdef_reset:KSFAM_VISU:
// \endif
extern void dspdef_reset (void);


/*! @}  */ 


/*! @addtogroup KSFAM_AUTRES
	* @{
 */ 

/*! @brief Tests if battery is present
 * @return 0 if no battery is present.
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:isbattery:KSFAM_AUTRES:0x7C
// \endif
extern int  isbattery (void);



/*! @brief powered checks if the terminal need to be powered for communication layout.
 *
 * If the caller is linked to DLL CB2A (French communication layout), the return depends on the network access parameter :
 * - GPRS and GSM, return always TRUE.
 * - Bluetooth terminal, return always TRUE.
 * - WiFi terminal, return TRUE if terminal is powered;
    if not, return TRUE only if network access parameter does not need to be powered
    (IP/Eth for instance), FALSE instead.
 * - Other value, return TRUE if terminal is powered, FALSE instead.
 *
 * If the caller is not linked to DLL CB2A (French communication layout), return TRUE if terminal is powered, FALSE instead
 * @return see above
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:powered:KSFAM_AUTRES:0x01
// \endif
extern int  powered (void);

#define GET_SWI_NUMBER(fct) (((unsigned char *)fct)[1]+((((unsigned char *)fct)[5]-0x13)<<8))


/*! @}  */ 


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
// \if SIMULATION
//  @GSIM_F:ApplicationUnInitialize:KSFAM_DIAG:0x19
// \endif
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
// \if SIMULATION
//  @GSIM_F:info_seg:KSFAM_DIAG:0x09
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
// \endif
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
// \if SIMULATION
//  @GSIM_F:info_seg_SE:KSFAM_DIAG:0x0A
//  @GSIM_A:2:ONE_POINTER
// \endif
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
// \if SIMULATION
//  @GSIM_F:first_init:KSFAM_DIAG:0x0B
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
// \endif
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
// \if SIMULATION
//  @GSIM_F:first_init_SE:KSFAM_DIAG:0x0F
// \endif
int first_init_SE(void);



/*! @brief This function reset the first execution flag.
 * @param num_segment : application number given by the manager.
 * @return -1 if application number does not exist.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:raz_init:KSFAM_DIAG:0x0C
// \endif
int raz_init(unsigned char num_segment);



/*! @brief This function resets the flag returned by the function first_init_SE.
 *
 * This flag is set when a new system component is loaded.
 * @return  0 if OK.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:raz_init_SE:KSFAM_DIAG:0x0E
// \endif
int raz_init_SE(void);


/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 


/*
==================
	oemc
==================
*/


/*! @brief send_receive programs of a port for send/receive. 
 *
 * This function is used to selectively enable the 2 ways directions COMx or MODEM channels for send or receive.
 * @param stream : file address.
 * @param send : boolean for enabling/disabling send.
 * @param receive : boolean for enabling/disabling receive.
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if COMx or MODEM file was not open.
 * @note send and receive can take values ON or OFF.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:send_receive:KSFAM_IOSF:0x11
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int send_receive (FILE *stream, char send, char receive);

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
// \if SIMULATION
//  @GSIM_F:upload_diagnostic_def:KSFAM_DIAG:0x06
// \endif
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
// \if SIMULATION
//  @GSIM_F:upload_diagnostic_cpt:KSFAM_DIAG:0x02
// \endif
int  upload_diagnostic_cpt(unsigned short num_cpt);



/*! @brief This function records a text message in APPTEXT.DIA file.
 * @param pt_param : Address of character string of text to be stored.
 * @return  -1 if function cannot be processed.
 * @note pt_param : the pointer on the free text must be terminated by '\0'. The character string
   must have a carriage return character at the end ('\n') to ensure easier separation of the text.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:upload_diagnostic_txt:KSFAM_DIAG:0x03
//  @GSIM_A:1:DATA_SIZE(512)
//  @GSIM_A:1:IN_ONLY
// \endif
int  upload_diagnostic_txt(unsigned char *pt_param);



/*! @brief This function prints diagnostics stored in the buffer. 
 *
 *The diagnostics are stored in the buffer by the function upload_diagnostic_txt.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:print_diagnostic:KSFAM_DIAG:0x05
// \endif
void print_diagnostic(void);



/*! @brief reset_diagnostic empties the buffer that stores diagnostics and faults. 
 *
 * After calling this routine, buffers are empty.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:reset_diagnostic:KSFAM_DIAG:0x07
// \endif
void reset_diagnostic(void);



/*! @brief This function can be used for hardware identification.
 * @param indiceFct : define in diagdef.h :
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
 * @param pResu : pointer to an object according to indiceFct parameter :
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
 */ 
// \if SIMULATION
//  @GSIM_F:lire_infos_terminal:KSFAM_DIAG:0x15
//  @GSIM_A:2:DATA_SIZE(80)
//  xxx choisir le buffer de plus grande taille.
// \endif
int lire_infos_terminal(int indiceFct, void *pResu);


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
// \if SIMULATION
//  @GSIM_F:archive_diagnostic:KSFAM_IOSF:0x33
// \endif
void archive_diagnostic(char *label);


/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

#define getchar()  getc(__STDIN())


/*! @brief stdperif gets the address of the Stream and Copy the file in an application area.
 *
 * This function is used to read the FILE of a given peripheral and get the address of the stream.
 * @param *name : name of the peripheral.
 * @param *fd : destination of the structure FILE.
 * @return
 * - the address FILE of the peripheral if OK.
 * - NULL if unsuccessful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:stdperif:KSFAM_FIC:0x18
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_ADDRESS
// \endif
FILE *stdperif(const char *name, FILE *fd);



/*! @brief CopyFile copies the file in an application area.
 *
 * This function is used to read the FILE of a given peripheral.
 * @param *Hdl: source of the stream FILE.
 * @param *fd: destination of the stream FILE.
 * @return
 * - EOF if unsuccessful.
 * - 0 if succesful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:CopyFile:KSFAM_FIC:0x20
//  @GSIM_S:CopyFile:E_CopyFile
// \endif
int CopyFile(FILE* Hdl, FILE *fd);


/*! @brief fioctl calls low level OEMC driver control function.
 *
 * @param cmd: Function code to be executed by OEMC device driver.
 * @param *data: command parameter(s).
 * @param *fd: target stream FILE.
 * @return
 * - 0 if succesful.
 * - other if unsuccessful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fioctl:KSFAM_FIC:
//  @GSIM_S:fioctl:E_fioctl
// \endif
int fioctl(int cmd, const void *data, FILE *fd);


/*! @brief fputc writes a character in specified file opened by fopen.
 * @param  c : value of character.
 * @param fd : pointer to FILE structure.
 * @return
 * - Returns the character sent if OK.
 * - EOF if problem detected.
 *
 * @note Writing in a file immediately triggers start up of the peripheral without waiting for
    the start character. If the dialogue buffer is full, the routine waits for a space in
    buffer to be released before returning control to the application.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fputc:KSFAM_FIC:0x29
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_ADDRESS
// \endif
int fputc(int   c, FILE *fd);



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
// \if SIMULATION
//  @GSIM_F:suppr_info_seg_appli:KSFAM_M2OS:0x06
// \endif
int suppr_info_seg_appli(short num_segment);



/*! @brief Suppress an application and its files in flash memory from the terminal.
 * param type_appli : Application type (field of ADF file)
 * @return 0 if OK.
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:suppr_appli:KSFAM_M2OS:0xCB
// \endif
int suppr_appli(unsigned short type_appli);


/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 


/*! @brief fowner modifies the task in the file descriptor. 
 *
 * This function is used to modify the task number for a given peripheral.
 * @param *device_name : peripheral where stream task number is to be modified.
 * @param notask : number of the task.
 * @return
 * - FILE * : the stream if OK.
 * - NULL if the change is unsuccessful.
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fowner:KSFAM_FIC:0x28
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:IN_ONLY
// \endif
FILE *fowner(const char *device_name,unsigned short notask);


/*! @}  */ 


/*! @addtogroup KSFAM_M2OS
	* @{
 */ 

/********************************************** */ 
// callhost

/*! @brief Start a download instance.
 * @return None
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:download:KSFAM_M2OS:0x90
// \endif
void download(void );


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
 * @link KSFAM_KBD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:StartBuzzer:KSFAM_KBD:0x02
// \endif
int StartBuzzer (unsigned char diviseur,  unsigned short int duree_high , unsigned short int duree_totale );



/*! @brief This function stops the beep previously activated by StartBuzzer.
 * @return None.
 *
 * @link KSFAM_KBD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:StopBuzzer:KSFAM_KBD:0x03
// \endif
int StopBuzzer (void);



/*! @brief This function activates the buzzer during a multiple of 10 milliseconds given as parameter.
 * @param Duree_P : duration operates in units of 10 milliseconds.
 * @return None.
 *
 * @link KSFAM_KBD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:buzzer:KSFAM_KBD:0x04
// \endif
void buzzer(unsigned short Duree_P);



/*! @}  */ 



/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief On mobile terminal only : shutdown() turn terminal in standby mode
 * Terminal can pe powered down using :
 *   FILE *pwr; 
 *   pwr = fopen("POWER","r");
 *   r=fioctl(PWR_FIOCTL_ENTER_PWRDWN,NULL,pwr); 
 * @return None.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:shutdown:KSFAM_IOSF:0x3C
// \endif
void shutdown (void);





/*! @brief On wireless terminal : restart low power watchdog.
 * @return None.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:WatchdogRefresh:KSFAM_IOSF:
// \endif
void WatchdogRefresh(void);
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
// \if SIMULATION
//  @GSIM_F:calcrc:KSFAM_AUTRES:0x10
//  @GSIM_A:1:DATA_SIZE(size)
// \endif
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
// \if SIMULATION
//  @GSIM_F:num_seg:KSFAM_DIAG:0x08
// \endif
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
// \if SIMULATION
//  @GSIM_F:paper_feed:KSFAM_OS:
// \endif
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
// \if SIMULATION
//  @GSIM_F:suppr_dll:KSFAM_OS:0x45
//  @GSIM_A:1:IN_ONLY
// \endif
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
// \if SIMULATION
//  @GSIM_F:entete_message_ident:KSFAM_M2OS:0x60
// \endif
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
// \if SIMULATION
//  @GSIM_F:umalloc:KSFAM_OS:0x33
//  @GSIM_S:umalloc:E_umalloc
// \endif
void *umalloc(unsigned int size);



/*! @brief Free of memory for an user application idem standard ANSI malloc and free.
 * @param p : adress of allocated area by umalloc.
 * @return None.
 * @note The memory free by ufree can't be reusable by another application. The memory is still available for the current application.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ufree:KSFAM_OS:0x34
//  @GSIM_S:ufree:E_ufree
// \endif
void ufree(void*p);



/*! @brief HeapFree returns the size of the private heap of the current application.
 * @return heap size.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:HeapFree:KSFAM_OS:0x35
// \endif
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
// \if SIMULATION
//  @GSIM_F:urealloc:KSFAM_OS:0x41
//  @GSIM_A:0:DATA_SIZE(4)
//  @GSIM_A:1:DATA_SIZE(4)
// \endif
void *urealloc(void *old_p, unsigned int new_size);



/*! @brief Allocates memory segment in DLL context : all application may share this memory.
 *
 * Allocation is limited to 64 MB.
 * @param size : Expected size.
 * @return
 * - Memory segment pointer.
 * - NULL.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  dllmalloc:KSFAM_OS:0x42
//  0:DATA_SIZE(4)
// \endif
void *dllmalloc(unsigned long size);



/*! @brief Frees memory segment in DLL space.
 * @param ptr :Previous memory segment pointer
 * @return None.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  dllfree:KSFAM_OS:0x43
// \endif
void dllfree(void* ptr);



/*! @brief Allocates memory segment in application user space and copy previous data in new segment.
 * @param old_p    : Previous memory segment pointer
 * @param new_size : Expected size
 * @return
 * - New memory segment pointer.
 * - NULL.
 *
 * @note Old memory segment is disallocated only if new allocation is possible.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  dllrealloc:KSFAM_OS:0x44
// \endif
void *dllrealloc(void *old_p, unsigned int new_size);


/*! @}  */ 


/*! @addtogroup KSFAM_VFS
	* @{
 */ 

/*! @brief This function returns error code occured at last function call of VFS.
 * @return Error code.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:errno_p:KSFAM_VFS:0x16
//  @GSIM_A:0:ONE_ADDRESS
// \endif
int *errno_p(void);


/*! @}  */ 


/*! @addtogroup KSFAM_KBD
	* @{
 */ 

/*
==================
	Dummy
==================
*/


/*! @brief Used to place a key in automatic repeat mode. 
 *
 * This function is disabled by the fclose function. This mode is used to automatically repeat the character
    entered on the keyboard when a key is held down.
 * @param key : Physical identification of key.
 * @return
 * - 0 when request has been accepted,
 * - -1 if not accepted.
 *
 * @note 
 *
 * The key is repeated when held down for more than 1 second, then every 400 ms.
 *
 * To stop the auto repeat mode, it is necessary to call fclose, then fopen again.
 *
 * @link KSFAM_KBD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:auto_repeat:KSFAM_KBD:0x01
// \endif
int auto_repeat(int key);



/*! @brief This function is used to enter an alphanumeric key at the cursor position on the display.
 *
 * It manages the display during the entry phase.
 *
 * It returns control as soon as the keyboard is in alphanumeric mode and is used to enter all the ASCII characters. (20 to 7F by
   default, or table passed as parameter ).
 * @param x : x position on display.
 * @param y : y position on display.
 * @param table : ASCII table address.
 * @return -1 if problem is detected, if not, returns 0.
 * @note 
 * 
 * It uses keys Up and Down.
 * 
 * These keys are used, when held down, to scroll alphanumeric characters
   on the display. Key Down is used to scroll the characters in a decreasing
   order in the table while key Up will scroll the characters in increasing order.
 * 
 * When the desired character is displayed, the operator must press the
   validation key. All of the other keys are processed normally.
 * 
 * The ASCII table defines all of the values which can be entered. This table is
   defined as a character string ( NULL terminated ). For a standard table, the
   table address must be NULL.
 * 
 * When the function returns control, the character entered is no longer
   displayed and the cursor is at position (x, y).
   fclose, then fopen must be called to disable the alphanumeric data entry mode.
 *
 * @link KSFAM_KBD Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:auto_repeat:KSFAM_KBD:
// \endif
int key_c_alpha( int x , int y, const char *table);


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
// \if SIMULATION
//  @GSIM_F:esc_command:KSFAM_IOSF:0x15
// \endif
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
// \if SIMULATION
//  @GSIM_F:trace:KSFAM_DIAG:0x04
//  @GSIM_A:3:DATA_SIZE(length)
//  @GSIM_A:3:IN_ONLY
// \endif
void trace(trace_sap_id_t sap_id, unsigned int length, const void* data);


/*! @}  */ 


#include "uiram.h"

/*! @brief SysCmd send command to Booster.
 * @param Cmd : Command identifier.
 * @param spydata : data.
 * @param diagnostic : data.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:SysCmd:KSFAM_DIAG:
// \endif
int SysCmd(unsigned char Cmd, spy_data_t * spydata , char * diagnostic);




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
// \if SIMULATION
//  input_sim:KSFAM_OS:
//  @GSIM_A:3:DATA_SIZE(len)
//  @GSIM_A:3:IN_ONLY
// \endif
int input_sim(char * periph, int len, unsigned char *buf);


/*! @}  */ 


/*! @addtogroup KSFAM_PPS
	* @{
 */ 

/*
==================
	PPR
==================
*/

/*! @brief This function initialises the system
 * @return None
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:PPR_Mount:KSFAM_PPS:0x49
// \endif
int PPR_Mount (void);

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
#endif


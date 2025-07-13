/*! @addtogroup KSFAM_OK
	* @{
 */ 

#ifndef DESCRIPT_H
#define DESCRIPT_H

#include "oem.h"

#define NO_SEM     0xFF			/*!< Do not use semaphore  */
#define CREATE_SEM 0x01			/*!< Use a semaphore */
#define NO_EVT     0xFF			/*!< Do not use event */

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Device descriptor structure. */
typedef struct {
   char *name;											/*!< name of the FILE */
   void *_addr_send;								/*!< send buffer */
   void *_addr_rec;									/*!< receive buffer */
   unsigned char _event;						/*!< real time event */
   unsigned char _mode_permit;			/*!< read/write mode */
   unsigned char _mode_elts;				/*!< byte/word mode */
   unsigned char _size_send;				/*!< send buffer size */
   unsigned char _size_rec;					/*!< receive buffer size */
   unsigned char _sem;							/*!< semaphore */
   void* (*pt_open)(FILE *,char *,void *);								/*!< open function */
   char  (*pt_close)(FILE *,void *);											/*!< close function */
   void  (*pt_status)(FILE *, unsigned char *,void *);		/*!< status function */
   void  (*pt_write)(FILE *,void *);											/*!< write function */
   void  (*pt_break)(FILE *, int,void *);									/*!< break function */
   void  (*pt_fillatopen)(FILE *,void *);									/*!< fillatopen function */
   int   (*pt_format)(va_list,void *);										/*!< format function */
   void* (*pt_generic)(int,void *);												/*!< statup/fioctl function */
   void  (*pt_diffusion)(int,void *);											/*!< power down function */
} DESCRIPTOR;


/*! @brief Device header structure. */
typedef struct {
	char 			 Profile[8];			/*!< name of the FILE */
	DESCRIPTOR 	DesPeriph;			/*!< Device descriptor */
	void			*DataPeriph;			/*!< dynamic device memory */
} ENTETE_PERIPH;


/*! @brief Fioctl structure. */
typedef struct FIOCTL_S{
  FILE *fd;									/*!< FILE */
  void *data_periph;				/*!< device dynamic data */
  void *data_cmd;  					/*!< fioctl command */
}FIOCTL_S;


/*
======================================================================
					List of Defines
======================================================================
*/

//mode d'accès au buffer : _mode_elts
#define _call_status_at_read   0x01   /*!< 0 = don't call status after read         1 = call  */
#define _power_management      0x02   /*!< 0 = no power mgt                         1 = power mgt  */



/*
======================================================================
					FIOCTL code handled by all OEMC devices  0-->0x7000
======================================================================
*/
#define FIOCTL_INSTALL                 		0		/*!< Fioctl install command */
#define FIOCTL_UNINSTALL               		1		/*!< Fioctl uninstall command */
#define FIOCTL_GET_VERSION             		2		/*!< Fioctl get version command */
#define FIOCTL_GET_LENGTH              		3		/*!< Fioctl get length command */
#define FIOCTL_GET_CRC                 		4		/*!< Fioctl get CRC command */
#define FIOCTL_POWER_DOWN              		5 	/*!< Fioctl power down command */
#define FIOCTL_ENTER_LOW_POWER        		6 	/*!< Fioctl enter low power command */
#define FIOCTL_EXIT_LOW_POWER          		7 	/*!< Fioctl exit low power command */

// 8 9 10 11 are reserved for USB device */
#define _USBDEV_FIOCTL_RESET               8 		/*!< Only for compatibility with existing projects. It has not to be used. */
#define _USBDEV_FIOCTL_GET_STATE           9 		/*!< Only for compatibility with existing projects. It has not to be used. */
#define _USBDEV_FIOCTL_CNX                 10 	/*!< Only for compatibility with existing projects. It has not to be used. */
#define _USBDEV_FIOCTL_HANG                11		/*!< Only for compatibility with existing projects. It has not to be used. */

#define FIOCTL_TTESTALL_VERIFY_STATUS  	   12		/*!< Called at fopen : verify status */
#define FIOCTL_GET_NIL_DESCRIPTOR      		 13		/*!< Check if dummy descriptor */
#define FIOCTL_EXTERNAL            				 2		/*!< Only for compatibility with existing projects. It has not to be used. */
#define FIOCTL_GET_INF_STRING         		 14 	/*!< Gets 16 chars descriptor string. (15 chars + '\0' )
                                                     example : 
                                                     char buf[16];
                                                     FILE *mdm;
                                                     mdm = fopen("MODEM","rw");
                                                     fioctl(FIOCTL_GET_INF_STRING, buf, mdm);                                                    
                                                 */
#define FIOCTL_IS_USB                 		 15 	/*!< Check if drivers manages USB device. return values :
                                                     1 if USB 
                                                     -1 if not implemented
                                                     other if not USB
                                                */
#define FIOCTL_IS_MODEM                		 16 	/*!< Check if drivers use MODEM fioctl. return values :
                                                     1 if driver is MODEM class
                                                     -1 if not implemented
                                                     other if not MODEM class
                                                */
#define FIOCTL_IS_CONNECTED            		 17 	/*!< Check if removable device is connected. return values :
                                                     1 if device is connected
                                                     -1 if not implemented
                                                     other if device not connected
                                                */

#define FIOCTL_SET_DBUG_LEVEL              18 	//!< to set debug level of a device (0=no debug)
                                                //!< @param unsigned int* debug level (0=no debug) 
                                                //!< @return
                                                //!< @li 0 OK
                                                //!< @li -1 not implemented
                                                //!< @li -2 bad parameter (NULL for ex).
                                                //!< @note
                                                //!< @include descript_Sample_01.c

#define FIOCTL_SET_ASYNC_MODE		           19	  //!< to set device function "fwrite" in asynchronous mode 
                                                //!< @param unsigned int* asynchronous mode (1=asynchonous)
                                                //!< @return
                                                //!< @li 0 OK
                                                //!< @li -1 not implemented
                                                //!< @li -2 bad parameter (NULL for ex).
                                                //!< @note
                                                //!< @include descript_Sample_02.c

                                                
/*
======================================================================
					FIOCTL code handled by all OEMC USB devices  0x7000-->0x8000
======================================================================
*/
#define USB_FIOCTL_GET_DEVICE_PID            0x7000		/*!< Get connected device PID, parameter is unsigned int */
#define USB_FIOCTL_GET_DEVICE_VID            0x7001		/*!< Get connected device VID, parameter is unsigned int */
#define USB_FIOCTL_SET_COMPTABILITY_MODE     0x7002		/*!< internal use only : add previous supported VID PID bcddevice */


/*
======================================================================
					FIOCTL code not handled 0xFFFF (reserved value for NOP)
======================================================================
*/
#define FIOCTL_NOT_IMPLEMENTED              0xFFFF		/*!< FIOCTL code not handled 0xFFFF (reserved value for NOP) */

#endif


/*! @}  */ 


#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_SYSFIOCTL_H_INCLUDED__
#define __OEM_SYSFIOCTL_H_INCLUDED__

//! \addtogroup SYSTEMFIOCTL
//! @{
		//! \defgroup SYSFIOCTL_MISCELLANEOUS Miscellaneous system commands
		//! \defgroup SYSTEMFIOCTL_CMD System commands
		//! \defgroup SYSFIOTCL_IDENT Terminal identification
		//! @{
				//! \defgroup PLATEFORM_VALUE Platform ID
				//! \defgroup TERMTYPE_VALUE Type of Terminal
		//! @}
		//! \defgroup SYSFIOTCL_FEATURES Terminal features
		//! @{
				//! \defgroup SYSFIOCTL_IS	IS_fioctl
				//! \defgroup TERM_RADIO_TYPE Type of Radio
				//! @{
						//! \defgroup TERM_MAIN_RADIO_TYPE Type of the main radio
						//! \defgroup TERM_RADIO_MASK Type of the radio (detailed)
				//! @}
				//! \defgroup TERM_DISPLAY_TYPE Type of Display
				//! \defgroup CLESS_LED_TYPE Type of CLESS Leds
		//! @}
		//! \defgroup SYSFIOCTL_PINPAD_FEATURES Pinpad features
		//! @{
				//! \defgroup PINPAD_DISPLAY_TYPE Type of pinpad display
		//! @}
		//! \defgroup SYSFIOCTL_SNMP SNMP sysfioctl
		//! \defgroup SYSFIOCTL_ETHERNET Ethernet sysfioctl
		//! @{
				//! \defgroup ETHERNET_CONNECTED_TYPE Type of Ethernet connected
		//! @}
		//! \defgroup SYSFIOCTL_USB USB sysfioctl
		//! \defgroup SYSFIOCTL_CLESS CLESS sysfioctl
		//! \defgroup SYSFIOCTL_TOUCH TOUCH sysfioctl
		//! \defgroup SYSFIOCL_SECURITY Security sysfioctl
		//! @{
				//! \defgroup OPERATIONAL_STATE Operational state
				//! \defgroup ACTIVATION_STATE Activation state
				//! \defgroup BOOSTER_VERSION Type of the secure processor
				//! \defgroup SECURITY_LEVEL Security level
				//! \defgroup PCI_PTS_VERSION PCI PTS version
				//! \defgroup SYSFIOCTL_PCI_FIRMWARE PCI firmware versions
				//! \defgroup SECURITYLOCKS Security Locks
				//! \defgroup INGETRUST_TYPES Type of INGETRUST PKI
				//! \defgroup INGETRUSTLOCKED INGETRUST lock status
		//! @}
		//! \defgroup SYSFIOCTL_DEBUG Debug sysfioctl
		//! \defgroup SYSFIOTCL_PINPAD_EMULATION Pinpad Emulation
		//! \defgroup SYSTEMFIOCTL_LIFE_COUNTER Life counters
		//! \defgroup SYSTEMFIOCTL_MISCELLANEOUS Miscellaneous
		//! \defgroup SYSTEMFIOCTL_AUDIO Audio
//! @}

#include "oem_sysfioctl_def.h"
#ifdef __FRAMEWORK_TELIUM_2__
#include "oem_sysfioctl_deprecated.h"
#endif


//! \addtogroup PLATEFORM_VALUE
//! @brief Set by \ref SYS_FIOCTL_GET_PLATFORM_ID
//! 
//! @include oem_sysfioctl_Sample_01.c
//!
//! @{

#define SUB_PLATFORM_ICMP      0x01		/*!< iCMP of ISMP family */

//! @}


//! \addtogroup SYSFIOTCL_IDENT
//! @{
#define SYS_FIOCTL_GET_PLATFORM_ID                      0x8002         /*!< Get the platform ID.
																			@param int :\ref PLATEFORM_VALUE 
																			@return 0 :OK */
//! @}

//! \addtogroup SYSFIOTCL_IDENT
//! @{

#define SYS_FIOCTL_GET_PRODUCT_IDENTIFICATION           0x8006		/*!< parameter type is Unsigned char[4] : 87M or 90M : 8 digits BCD  */


#define SYS_FIOCTL_GET_PRODUCT_REFERENCE                0x8008		/*!< parameter type is Unsigned char[12] : 87M or 90M with release number : 12 ASCII  */

#define SYS_FIOCTL_GET_PRODUCT_MANUFACTURING_DATE       0x8009		/*!<Get the Manufacturing date : 8 ASCII  DDMMYYYY. @param unsigned char[8] : 8 ASCII  DDMMYYYY without \\0 */

#define SYS_FIOCTL_GET_CONSTRUCTOR_CODE                 0x800A		/*!<Get the Product code M3X @param Unsigned char[3] : 3 ASCII without \\0 */
//! @}

//! \addtogroup SYSFIOTCL_FEATURES
//! @{
#define SYS_FIOCTL_GET_FLASH_SIZE                       0x800C		/*!< Get the Total nand size. @param Unsigned int* : 0x800000 = 8MBytes */

//! @}


//! \addtogroup TERM_MAIN_RADIO_TYPE
//! @brief Set by \ref SYS_FIOCTL_GET_RADIO_TYPE
//! @note SYS_FIOCTL_GET_RADIO_TYPE contains only the main radio type, but some products can support two radio types (ex : BT + GPRS).
//! @warning \ref SYS_FIOCTL_GET_RADIO_MASK provides more information (bit field) about Radio features
//!
//! @include oem_sysfioctl_Sample_04.c
//!
//! @{

#define TERM_RADIO_GPRS   0			/*!< GPRS (\ref SYS_FIOCTL_GET_RADIO_TYPE ) */
#define TERM_RADIO_BT     8			/*!< Blue Tooth (\ref SYS_FIOCTL_GET_RADIO_TYPE )  */
#define TERM_RADIO_WIFI   4			/*!< Wifi (\ref SYS_FIOCTL_GET_RADIO_TYPE )  */
#define TERM_RADIO_CDMA   12		/*!< CDMA (\ref SYS_FIOCTL_GET_RADIO_TYPE ) */

//! @}


//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_MODEM_COUNTRY_CODE               0x8015			/*!<no parameter : Modem country code : 33 (0x21)=France  */

//! @}


//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_ICC_READER_HARD_VERSION          0x802A			/*!<parameter type is : ICC reader hardware version : 4 digits ASCII */
#define SYS_FIOCTL_GET_ICC_READER_SOFT_VERSION          0x802B			/*!<parameter type is : ICC reader software version : 4 digits ASCII */

//! @}

//! \addtogroup SYSFIOCTL_ETHERNET
//! @{

#define SYS_FIOCTL_GET_ETHERNET_INFO                    0x802D			/*!< Get the type of connected ethernet. 
																			@param unsigned int * : \ref ETHERNET_CONNECTED_TYPE 
																			@return 0*/
																				

//! @}


//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_IRDA	                            0x802F			/*!< no parameter : Test if IRDA available */
#define SYS_FIOCTL_IS_DUART                             0x8030			/*!< no parameter : Test if DUART available  */
#define SYS_FIOCTL_IS_MDB_C3                            0x8031			/*!< no parameter : Test if MDB available  */

//! @}

//! \addtogroup SYSFIOCL_SECURITY
//! @{

#define SYS_FIOCTL_GET_SECURE_UNIT_TYPE                 0x8032			/*!< Get the secure processor type (Booster).
																			@param unsigned int * pType : \ref BOOSTER_VERSION
																			@return 0 																		*/

//! @}


//! \addtogroup SYSFIOCL_SECURITY
//! @{

#define SYS_FIOCTL_GET_OPERATIONAL_STATE				0x8034  			/*!< Gets state of secure processor.
																				 @param unsigned char * : \ref OPERATIONAL_STATE
																				 @return 0.
																				 @note Not implemented on Booster I  */

//! @}


//! \addtogroup OPERATIONAL_STATE
//! @brief Set by \ref SYS_FIOCTL_GET_OPERATIONAL_STATE
//! 
//! @include oem_sysfioctl_Sample_08.c
//! @{

#define BL2_UNAUTHORIZED_STATE							0x02				/*!< Unautorized state */
#define BL2_OUT_OF_SERVICE_STATE						0x01				/*!< Out of order */
#define BL2_READY_STATE									0x00				/*!< Ready */

//! @}

//! \addtogroup SYSFIOCTL_USB
//! @{

#define SYS_FIOCTL_GET_USB_DEV_NBR                      0x8040 			/*!< param : unsigned int, Get number of USB device connected */
#define SYS_FIOCTL_GET_USB_DEV_ID                       0x8041 			/*!< param : SYS_FIOCTL_GET_USB_DEV_ID_S, Used to get the ID (pid, vid, ...) of an USB device */

//! @}

//! \addtogroup SYSTEMFIOCTL_LIFE_COUNTER
//! @{
#define SYS_FIOCTL_GET_LIFE_COUNTER                     0x8043 			/*!< Get the life counter values.	
																			 @param  SYS_FIOCTL_GET_LIFE_COUNTER_S * : pointer to life counter struct
																			 @return 0
																			 @note \ref SYS_FIOCTL_GET_LIFE_COUNTER_S.life_counter_id must be set with the life counter id.
																			 */

//! @}
																		 
//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_SYSTEM_RESTART                       0x8046 			/*!< Restart the terminal @param NULL   */

//! @}

//! \addtogroup SYSFIOCTL_SNMP
//! @{

#define SYS_FIOCTL_SNMP_GET_PORT                   		0x8053 			/*!< param : unsigned int *, Get SNMP Agent port */

//! @}


//! \addtogroup SYSFIOCL_SECURITY
//! @{

#define SYS_FIOCTL_BOOSTER_GET_MOCKUP_MODE        			0x8063 			/*!< Test if Booster is in Mockup mode 
																				@param unsigned char*
																				@return 
																				\li \ref BOOSTER_MODE_NORMAL=Not Mockup
																				\li	\ref BOOSTER_MODE_MOCKUP =Mockup 
																				*/


#define BOOSTER_MODE_MOCKUP 1											/*!< Mockup mode disabled ( \ref SYS_FIOCTL_BOOSTER_GET_MOCKUP_MODE )*/
#define BOOSTER_MODE_NORMAL 0											/*!< Mockup mode enabled ( \ref SYS_FIOCTL_BOOSTER_GET_MOCKUP_MODE )*/

//! @}



//! \addtogroup SYSFIOCL_SECURITY
//! @{

#define SYS_FIOCTL_BOOSTER_GET_ACTIVATED_STATE    			0x8064 			/*!< Get booster activation state
																				 @param *unsigned char Booster \ref ACTIVATION_STATE 
																				 @return 0 OK
																			*/

//! @}

//! \addtogroup ACTIVATION_STATE
//! @{

#define BOOSTER_IS_ACTIVATED     1
#define BOOSTER_IS_NOT_ACTIVATED 0

//! @}

//! \addtogroup SECURITY_LEVEL
//! @brief Returned by \ref SYS_FIOCTL_BOOSTER_GET_SECURITY_LEVEL
//! 
//! @include oem_sysfioctl_Sample_09.c
//! @{

#define BOOSTER_SECURITY_LEVEL_0         								0x00 				/*!< no security */
#define BOOSTER_SECURITY_LEVEL_PEDS      								0x80 				/*!< grids & mecanicals sensors only */
#define BOOSTER_SECURITY_LEVEL_PEDS_PCI  								0x81 				/*!< SECURITY_LEVEL_STD & voltage supervisors  */
#define BOOSTER_SECURITY_LEVEL_ZKA       								0x82 				/*!< SECURITY_LEVEL_PCI & temperature supervisors  */

//! @}



//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_THUNDER_GET_ROM_VERSION      				0x8067 			/*!<param : char[4] Get Booster ROM version */
#define SYS_FIOCTL_BOOSTER_GET_ROM_VERSION       				0x8068 			/*!<param : char[4] Get Booster ROM version */
#define SYS_FIOCTL_BOOSTER_GET_ACTIVATION_MANUFACTURING_DATE    0x8069 			/*!<param : char[12]  */
#define SYS_FIOCTL_BOOSTER_GET_ACTIVATION_PROFILE              	0x806A 			/*!<param : char[3]   */


//! @}

//! \addtogroup SYSFIOCTL_PINPAD_FEATURES
//! @{

#define SYS_FIOCTL_GET_PINPAD_INFORMATIONS											0x806D  /*!<give the information of the pinpad 
@param SYS_FIOCTL_PINPAD_DEF * *  pointer to struct of pinpad features
@return 0 OK.

\b Example:

 @include oem_sysfioctl_Sample_10.c
*/

//! @}

//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_SECURITY_FIRMWARE_ID											0x806E  /*!< get security firmware version param : char[5] (ex:"0101") */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_REPUDIATION_INFO_GET                 0x8077 /*!< parameter type is SYS_FIOCTL_REPUDIATION_INFO_GET_S : Gets repudiation informations */
//! @}


//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_CLESS_LED_TYPE	                0x8078 /*!< @param unsigned int * pType : gets \ref CLESS_LED_TYPE 
																	@return 
																	\li 0 OK
																	\li -1 No Cless Leds*/
//! @}


//! \addtogroup CLESS_LED_TYPE
//! @brief Returned by \ref SYS_FIOCTL_GET_CLESS_LED_TYPE
//! 
//! @include oem_sysfioctl_Sample_11.c
//! @{

#define HARDWARE_CLESS_LED	 0								/*!< value for \ref SYS_FIOCTL_GET_CLESS_LED_TYPE : hardware led */
#define CLESS_LED_ON_DISPLAY 1								/*!< value for \ref SYS_FIOCTL_GET_CLESS_LED_TYPE : led on display */

//! @}




//! \addtogroup INGETRUSTLOCKED
//! @brief returned by \ref SYS_FIOCTL_SECURITY_GET_INGETRUST_LOCK
//! @note On TELIUM II only.
//!
//! @include oem_sysfioctl_Sample_14.c
//! @{

	#define INGETRUST_LOCK_DISABLED	0 /*!< Terminal is not Ingetrust locked */
	#define INGETRUST_LOCK_READY	1 /*!< Terminal will be Ingetrust locked at first connection with Ingetrust */
	#define INGETRUST_LOCKED		2 /*!< Terminal is Ingetrust locked */

//! @}

                                                                            
//! \addtogroup SYSFIOCTL_ETHERNET
//! @{
																			

#define  SYS_FIOCTL_FTPS_DISABLE                       0x810F /*!<Fioctl used to disable FTP server. 
                                                                   This SystemFioctl must be called each time terminal reboots, for example in after_reset function.
                                                                            No parameters.
                                                                            Return value :
                                                                            0 OK
                                                                            -1 not implemented */



//! @}


//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_SET_CALLHOST_TCP_TIMEOUT            0x8115 	//!<  to set the timeout of callhost TCP connection
                                                                    //!< @param unsigned int * : timeout of callhost TCP connection in second
                                                                    //!< @return
                                                                    //!< @li 0 OK
                                                                    //!< @li -1 not implemented
                                                                    //!< @li -2 bad parameter (NULL for ex).

//! @}


//! \addtogroup SYSFIOCTL_TOUCH
//! @{

#define SYS_FIOCTL_TRANSACTION_BEGIN                           0x830D  /*!< Signal for touch screen driver: transaction begins, background comp should be disabled
																			@param NULL
																			@return
																			\li 0: OK
																			\li -1 : not implemented*/
#define SYS_FIOCTL_TRANSACTION_END                             0x830E  /*!< Signal for touch screen driver: transaction ends, background comp should be enabled
																			@param NULL
																			@return
																			\li 0: OK
																			\li -1 : not implemented*/

//! @}

//! \addtogroup SYSFIOCTL_DEBUG
//! @{

#define SYS_FIOCTL_DEBUG_TRACE                                  0x8400 /*!< to pass trace to debugger */

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

/*! @brief structure used with SYS_FIOCTL_REPUDIATION_INFO_GET fioctl : Gets repudiation informations. */
typedef struct
{
  unsigned int Repudiation_Number1;		/*!< index of last active key (1...)  */
  unsigned int Repudiation_Number2;		/*!< page   */
}SYS_FIOCTL_REPUDIATION_INFO_GET_S;


/*! @brief structure used with SYS_FIOCTL_RENAME_DESCRIPTOR fioctl : rename OEMC file. */
typedef struct
{
	char *old_name_descriptor;						/*!< old name of the descriptor. */
	char *new_name_descriptor;						/*!< new name of the descriptor. */
}SYS_FIOCTL_RENAME_DESCRIPTOR_S;


/*! @brief structure used with SYS_FIOCTL_CHANGE_EVENT_DESCRIPTOR fioctl : Used to associate an event with a descriptor. */
typedef struct
{
	char *name_descriptor;							/*!< name of the descriptor*/
	unsigned char event;							/*!< event associated */
}SYS_FIOCTL_CHANGE_EVENT_DESCRIPTOR_S;

//! @}

//! \addtogroup SYSFIOCTL_USB
//! @{

/*! @brief structure used with SYS_FIOCTL_GET_USB_DEV_ID fioctl : Used to get the ID of an USB device */
typedef struct
{
	unsigned int   in_address;						/*!< (input) 1 to SYS_FIOCTL_GET_USB_DEV_NBR */
	unsigned short out_pid;							/*!< (output) device PID */
	unsigned short out_vid;							/*!< (output) device VID */
	unsigned char  out_class;						/*!< (output) device or interface class */
	unsigned char  out_subclass;					/*!< (output) device or interface subclass  */
	unsigned char  out_protocol;					/*!< (output) device or interface protocol  */
}SYS_FIOCTL_GET_USB_DEV_ID_S;


/*! @brief structure used with SYS_FIOCTL_GET_USB_DEV_ID fioctl : Used to get the ID of an USB device */
typedef struct
{
	unsigned int   in_index;						/*!< (input) 1 to SYS_FIOCTL_GET_USB_DEV_NBR */
	unsigned char  szManufacturer[127];				/*!< (output) Manufacturer string - Reserve for Future Use */
	unsigned char  szProduct[127];					/*!< (output) Product string */
	unsigned char  szSerialNumb[127];				/*!< (output) Serial numb string - Reserve for Future Use */
}SYS_FIOCTL_GET_USB_DEV_STRINGS_S;

//! @}

//! \addtogroup SYSTEMFIOCTL_LIFE_COUNTER
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_GET_LIFE_COUNTER fioctl : Basic informations about a life counter. */
typedef struct
{
	unsigned short life_counter_id;					/*!< ID of the counter    */
	unsigned long  value;							/*!< value of the counter */
}SYS_FIOCTL_GET_LIFE_COUNTER_S;

//! @}

//! \addtogroup PINPAD_DISPLAY_TYPE
//! @brief Value of \ref SYS_FIOCTL_PINPAD_DEF.display.

//! @{

#define PINPAD_DISPLAY_GRAPHIC 1  		/*!< value of \ref SYS_FIOCTL_PINPAD_DEF.display : graphic display */
#define PINPAD_DISPLAY_COLOR   2		/*!< value of \ref SYS_FIOCTL_PINPAD_DEF.display : graphic color display */
#define PINPAD_DISPLAY_ALPHA   0		/*!< value of \ref SYS_FIOCTL_PINPAD_DEF.display : alpha display */
#define PINPAD_DISPLAY_NONE    0xFF		/*!< value of \ref SYS_FIOCTL_PINPAD_DEF.display : no display */

//! @}

//! \addtogroup SYSFIOCTL_PINPAD_FEATURES
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_GET_PINPAD_INFORMATIONS fioctl : give the information of the pinpad. */
typedef struct
{
	char  *version;      		/*!< for compatibility */
	char  *name;         		/*!< name of pinpad */
	char  booster_type;  		/*!< BOOSTER_1,BOOSTER_2, BOOSTER_3, BOOSTER_4 */
	char  display; 				/*!< if present true else  false */
	char  graphic_display;  	/*!< \ref PINPAD_DISPLAY_TYPE (for ex \ref PINPAD_DISPLAY_GRAPHIC)*/
	int   width_size; 			/*!< In pixel or character if non graphic */
	int   hight_size; 			/*!< In pixel or character if non graphic */
	int   nb_bit_par_pixel; 	/*!< 8 bits for 256  , 12 bits for 4k or 16 bits for 65 k colos */
	char  keyboard; 			/*!< if present true else  false */
	char  swipe2; 				/*!< if present true else  false */
 	char  swipe1; 				/*!< if present true else  false */
	char  swipe3; 				/*!< if present true else  false */
  char  smartcard; 				/*!< if present true else  false */
	char  sam1; 				/*!< if present true else  false */
	char  sam2; 				/*!< if present true else  false */
	char  backligth; 			/*!< if present true else  false */
	char  buzzer; 				/*!< if present true else  false */
	char  iapp; 				/*!< if present true else  false */
	char  cless;				/*!< if present true else  false */
	char  leds; 				/*!< if present true else  false */
	char  ruf[32];
}SYS_FIOCTL_PINPAD_DEF;

//! @}

//! \addtogroup SYSFIOCTL_USB
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_GET_DEVICE_RELEASE_NUMBER fioctl :Information about a device release number. (fioctl function) */
typedef struct
{
	unsigned int in_address;							/*!< (input) address */
  unsigned int out_bcdDevice;						/*!< (output) device (BCD) */
}SYS_FIOCTL_GET_DEVICE_RELEASE_NUMBER_S;

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

/*! @brief This structure define the state of a BL2 product : \li OK, \li HORS_SERVICE : broken, \li DESACTIVE : disactivated. */
typedef struct
{
	unsigned int	bl2_pioa_state;					/*!< state of the BL2 pioA */
	unsigned int	bl2_pioa_mask;					/*!< mask  */
	unsigned int	bl2_piob_state;					/*!< state of the BL2 pioB */
	unsigned int	bl2_piob_mask;					/*!< mask */
}
SYS_FIOCTL_GET_PIO_BL2_S;

//! @}

//! \addtogroup SYSFIOTCL_PINPAD_EMULATION
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_START_INTERUC_THUNDER and \ref SYS_FIOCTL_STOP_INTERUC_THUNDER fioctl : set parameters for INTER UC THUNDER (optional). */

#define INTERUC_THUNDER_CMD_START		1
#define INTERUC_THUNDER_CMD_STOP		2

typedef struct
{
	unsigned int nCmd;
}SYS_FIOCTL_INTER_UC_THUNDER_START_S;

typedef struct
{
	unsigned int nCmd;
}SYS_FIOCTL_INTER_UC_THUNDER_STOP_S;

typedef union
{

	SYS_FIOCTL_INTER_UC_THUNDER_START_S stStart;
	SYS_FIOCTL_INTER_UC_THUNDER_STOP_S stStop;
}SYS_FIOCTL_INTER_UC_THUNDER_S;

typedef struct
{
	unsigned int nVersion;		/*!< 1 --> to manage the evolution of the struct and the compatibility */
	unsigned int nCmd; 			/*!< cmd value */

}SYS_FIOCTL_INTERUC_ADMIN_HEADER_S;


#define INTERUC_ADMIN_CMD_DOWNLOAD			0	/*!< \ref SYS_FIOCTL_INTERUC_ADMIN_CMD_S 		remote downloading	*/
#define INTERUC_ADMIN_CMD_LLT				1	/*!< \ref SYS_FIOCTL_INTERUC_ADMIN_CMD_S  local 	downloading	*/
#define INTERUC_ADMIN_GETINFO_IN			2	/*!< \ref SYS_FIOCTL_INTERUC_ADMIN_GETINFO_IN_S  get_info request	*/
#define INTERUC_ADMIN_GETINFO_OUT			3	/*!< \ref SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_S get_info reply		*/
#define INTERUC_ADMIN_SETMODE_INTELLIGENT 	4	/*!< \ref SYS_FIOCTL_INTERUC_ADMIN_CMD_S  		modify the device mode, set intelligent mode*/

typedef struct
{
	unsigned int nVersion;		/*!< 1 --> to manage the evolution of the struct and the compatibility */
	unsigned int nCmd; 			/*!< cmd value */

}SYS_FIOCTL_INTERUC_ADMIN_CMD_S;

// nInfoId
#define  MAINTENANCE_PINPAD_INFO_SUMMARY	1

typedef struct
{
	unsigned int nVersion; 		/*!< 1 --> to manage the evolution of the struct and the compatibility */
	unsigned int nCmd; 			/*!< cmd value */
	unsigned int nInfoId;
	union
	{
		unsigned char buf[64];
	}u;

}SYS_FIOCTL_INTERUC_ADMIN_GETINFO_IN_S;


typedef struct
{
	char	appli_family[20];		//OBJECT_FILE_NAME_LEN
    char	file_name[20];
	unsigned short	crc;
}SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_SUMMARY_ELT_S;

typedef struct
{

	// OS
	SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_SUMMARY_ELT_S stSystem;
	// Manager
	SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_SUMMARY_ELT_S stManager;
}SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_SUMMARY_S;

typedef struct
{
	unsigned int nVersion;		/*!< 1 --> to manage the evolution of the struct and the compatibility */
	unsigned int nCmd;			/*!< cmd value */
	unsigned int nInfoId;
	union
	{
		SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_SUMMARY_S stSummary;
	}u;

}SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_S;

typedef union
{
	unsigned char buf[512];
	//not used
	SYS_FIOCTL_INTERUC_ADMIN_HEADER_S stHeader;
	SYS_FIOCTL_INTERUC_ADMIN_CMD_S stCmd;
	SYS_FIOCTL_INTERUC_ADMIN_GETINFO_IN_S stGetInfoIn;
	SYS_FIOCTL_INTERUC_ADMIN_GETINFO_OUT_S stGetInfoOut;
}SYS_FIOCTL_INTERUC_ADMIN_S; //-> TX


#define DEVICE_MODE_INTERUC				0	// the device is slave and uses the InterUC protocole
#define DEVICE_MODE_INTELLIGENT			1	// the device is slave and uses the intelligent mode
#define DEVICE_MODE_TERMINAL			2	// compatiblity mode (telium generic VID PID)

//! @}


//! \addtogroup SYSTEMFIOCTL_AUDIO
//! @{

// AUDIO FUNCTIONS
#define AUDIO_FILE_MAX_SIZE	50
typedef struct //SYS_FIOCTL_AUDIO_SET_VOLUME
{
	unsigned short usPercent;			/*!< Volume : 0..100 			   		*/
}SYS_AUDIO_SET_VOLUME_S;

typedef struct //SYS_FIOCTL_AUDIO_SET_ATTENUATION
{
	unsigned short usDecibel;				/*!< Attenuation : 0..100 -> 100=mute    */
}SYS_AUDIO_SET_ATTENUATION_S;


typedef struct //SYS_FIOCTL_AUDIO_PLAY_OGG
{
	char szFileOgg[AUDIO_FILE_MAX_SIZE+1];
}SYS_FIOCTL_AUDIO_PLAY_OGG_S;

typedef struct //SYS_FIOCTL_AUDIO_PLAY_OGG_WITH_VOL
{
	unsigned short usPercent;
	char szFileOgg[AUDIO_FILE_MAX_SIZE+1];
}SYS_FIOCTL_AUDIO_PLAY_OGG_WITH_VOL_S;


typedef struct //SYS_FIOCTL_AUDIO_PLAY_TONE
{
	unsigned int nDuration;
	unsigned int nTone;
}SYS_FIOCTL_AUDIO_PLAY_TONE_S;

typedef struct //SYS_FIOCTL_AUDIO_PLAY_TONE_WITH_VOL
{
	unsigned short usPercent;
	unsigned int nDuration;
	unsigned int nTone;
}SYS_FIOCTL_AUDIO_PLAY_TONE_WITH_VOL_S;

typedef struct //SYS_FIOCTL_AUDIO_PLAY_OGG
{
	char szFileWav[AUDIO_FILE_MAX_SIZE+1];
}SYS_FIOCTL_AUDIO_PLAY_WAV_S;

typedef struct //SYS_FIOCTL_AUDIO_PLAY_OGG_WITH_VOL
{
	unsigned short usPercent;
	char szFileWav[AUDIO_FILE_MAX_SIZE+1];
}SYS_FIOCTL_AUDIO_PLAY_WAV_WITH_VOL_S;


typedef union
{
	SYS_AUDIO_SET_VOLUME_S	tSetVolume;
	SYS_AUDIO_SET_ATTENUATION_S tSetAttenuation;
	SYS_FIOCTL_AUDIO_PLAY_OGG_S tPlayOgg;
	SYS_FIOCTL_AUDIO_PLAY_OGG_WITH_VOL_S	tPlayOgg_WithVol;
	SYS_FIOCTL_AUDIO_PLAY_TONE_S	tPlayTone;
	SYS_FIOCTL_AUDIO_PLAY_TONE_WITH_VOL_S	tPlayTone_WithVol;
	SYS_FIOCTL_AUDIO_PLAY_WAV_S tPlayWav;
	SYS_FIOCTL_AUDIO_PLAY_WAV_WITH_VOL_S	tPlayWav_WithVol;
	
}SYS_FIOCTL_AUDIO;
//! @}


//! \addtogroup SYSTEMFIOCTL
//! @{

/*! @brief This function allows application to get or set system parameters.
 * @param cmd : command identifier .
 * @param data : command parameters.
 * @return
 *   \li  0 if succesful.
 *   \li -1 if function not available.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */
int SystemFioctl(int cmd, void *data);

//! @}

#endif   // __OEM_SYSFIOCTL_H_INCLUDED__

#ifdef __cplusplus
}
#endif

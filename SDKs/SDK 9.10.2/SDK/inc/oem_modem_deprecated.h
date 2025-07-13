#ifndef __OEM_MODEM_DEPRECATED_H_INCLUDED__
#define __OEM_MODEM_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_OEM_MODEM_SDK091000_

#define MODEM_FIOCTL_EXTERNAL		    		(0x8000)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																			  @brief General access for internal use only */

// career state : MODEM_FIOCTL_CD_ON or MODEM_FIOCTL_CD_OFF
#define MODEM_FIOCTL_GET_CD_STATE	    (MODEM_FIOCTL_EXTERNAL + 0)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                 @brief Return Carrier Detect */
#define MODEM_FIOCTL_CD_ON	            (1)		/*!< Carrier ON */
#define MODEM_FIOCTL_CD_OFF	            (0)		/*!< Carrier OFF */

#define MODEM_FIOCTL_GET_RELAY_STATE    (MODEM_FIOCTL_EXTERNAL + 1)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                 @brief Return Modem Relay State */
#define MODEM_FIOCTL_RELAY_UNKNOWN    	(0)		/*!< RELAY UNKNOWN */
#define MODEM_FIOCTL_RELAY_ONLINE     	(1)		/*!< RELAY ONLINE */
#define MODEM_FIOCTL_RELAY_OFFLINE    	(2)		/*!< RELAY OFFLINE */

// 930 only.
#define MODEM_FIOCTL_GET_MAX_SPEED      (MODEM_FIOCTL_EXTERNAL + 2)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                 @brief Speed IR for debug */

// Cooection state (BlueTooth only)
#define MODEM_FIOCTL_GET_CONNECTED_STATE           (MODEM_FIOCTL_EXTERNAL + 3)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                             @brief Modem Connection ( in Bluetooth mode only) */
#define MODEM_FIOCTL_CONNECTED_STATE_CONNECTED     (0)		/*!< modem connected */
#define MODEM_FIOCTL_CONNECTED_STATE_NOT_CONNECTED (1)		/*!< modem not connected */
#define MODEM_FIOCTL_CONNECTED_STATE_DISCONNECTED  (2)		/*!< modem disconnected */

#define MODEM_FIOCTL_SET_ALL_DAA_OFF_STATE			( MODEM_FIOCTL_EXTERNAL + 4 )		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                             @brief Activation of DAA  */
#define MODEM_FIOCTL_ALL_DAA_OFF_DISABLE				( 0 )		/*!< Disable DAA */
#define MODEM_FIOCTL_ALL_DAA_OFF_ENABLE					( 1 )		/*!< Enabled */

#define MODEM_FIOCTL_DESYNCHRO			            ( MODEM_FIOCTL_EXTERNAL + 5 )		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                             @brief Verification of desynchro */

#define MODEM_FIOCTL_GET_REVISIONS                  (MODEM_FIOCTL_EXTERNAL + 6)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                             @brief Get Chip revision */
#define MODEM_FIOCTL_GET_CHIP_A_REVISION(X)         (((X) >> 4) & 0xF)		/*!< Revision of Chip A */
#define MODEM_FIOCTL_GET_CHIP_B_REVISION(X)         ((X) & 0xF)						/*!< Revision of Chip B */
#define MODEM_FIOCTL_GET_LINE_SIDE_REVISION(X)      MODEM_FIOCTL_GET_CHIP_B_REVISION(X)		/*!< Revision of line side A */
#define MODEM_FIOCTL_GET_DIGITAL_SIDE_REVISION(X)   MODEM_FIOCTL_GET_CHIP_A_REVISION(X)		/*!< Revision of digital side B */

// Arret du modem Netbricks pour pouvoir lancer le modem V34 (les 2 modems sont exclusifs)
#define MODEM_FIOCTL_MODEM_STATE	    (MODEM_FIOCTL_EXTERNAL + 7)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				              @brief Stop netbricks modem */
#define MODEM_FIOCTL_MODEM_ON	        (1)		/*!< Start of modem Netbricks */
#define MODEM_FIOCTL_MODEM_OFF	      (0)		/*!< Stop of modem Netbricks */

// is modem opened or closed?
#define MODEM_FIOCTL_GET_MODEM_STATUS	(MODEM_FIOCTL_EXTERNAL + 8)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                 @brief State of the modem driver */
#define MODEM_FIOCTL_MODEM_STATUS_OPENED    (1)		/*!< State opened */
#define MODEM_FIOCTL_MODEM_STATUS_CLOSED    (0)		/*!< State Closed */

#define MODEM_FIOCTL_GET_V34_COUNTRY_CODE           (MODEM_FIOCTL_EXTERNAL + 9)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                             @brief Get the country code (default value France if not found)*/
#define MODEM_FIOCTL_READ_V34_COUNTRY_CODE          (MODEM_FIOCTL_EXTERNAL + 10)	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				                          @brief Read the country code (return NO_COUNTRY_CODE_DEFINED if not found) */

#define NO_COUNTRY_CODE_DEFINED 0xFFFF

/*
======================================================================
 FIOCTL 0x8100 to 0x8200 are reserved for new Modem fioctl
======================================================================
*/
#define MODEM_FIOCTL_ESC_COMMAND         	(0x8100)     /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				@brief Send esc command. Return code :
                                                            0 if OK
                                                            -1 if not implemented
                                                       */
#define MODEM_FIOCTL_IDENT               	(0x8101)     /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				@brief Gets modem identification. Parameter type is MODEM_FIOCTL_IDENT_S
                                                            Return code :
                                                            0 if OK
                                                            -1 if not implemented
                                                       */
#define MODEM_FIOCTL_DO_NOT_USE_1          	(0x8102)     /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																				   @brief Don't tell, don't ask.
                                                               Return code : 0 if OK, -1 if not implemented */

                                                               /*
================================================================================
 FIOCTL 0x8500 to 0x8600 are reserved for new Modem/COM RS232/USB compatibility
================================================================================
*/
#define COM_FIOCTL_GET_CONFIGURATION      0x8500				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_MODEM_SDK091000_ in your application. 
																			        @brief parameter type is COM_CONFIG : Read serial line configuration  */


                                                             
typedef enum{
  MODEM_NETBRICKS = 0,
  MODEM_MOTOROLA  = 1,
  MODEM_CONEXANT  = 2
} MODEM_FIOCTL_IDENT_MANUFACTURER ;

/*!< use this structure with MODEM_FIOCTL_IDENT */
typedef struct {
  unsigned int size; /*!< init this field with : sizeof(MODEM_FIOCTL_IDENT_S) */
  MODEM_FIOCTL_IDENT_MANUFACTURER manufacturer;
  unsigned int vers; /*!< internal telium version */
  char firmware[32]; /*!< modem identification string */
} MODEM_FIOCTL_IDENT_S ;

#endif // _DEPRECATED_OEM_MODEM_SDK091000_

#endif // __OEM_MODEM_DEPRECATED_H_INCLUDED__

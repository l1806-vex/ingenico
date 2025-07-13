/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_COM_DEPRECATED_H
#define OEM_COM_DEPRECATED_H

#ifdef _DEPRECATED_OEM_COM_SDK091000_

#define COM_FIOCTL_SET_RECEIVER_TIMEOUT   0x8004  			   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief unsigned int : 0 = no timeout  1-65535 : number of bits */
#define COM_FIOCTL_GET_RECEIVER_TIMEOUT   0x8005 			   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief unsigned int : 0 = no timeout  1-65535 : number of bits */
#define COM_FIOCTL_LOCAL_LOOPBACK         0x8006				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief Reserved for future use */
#define COM_FIOCTL_REMOTE_LOOPBACK        0x8007				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief Reserved for future use */
#define COM_FIOCTL_CLEAR_DTR              0x8009				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief Turn off DTR Com Signal if signal supported */
#define COM_FIOCTL_BREAK_START            0x8010				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief Start sending break on the seriel line */
#define COM_FIOCTL_BREAK_STOP             0x8011				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief Stop sending break on the seriel line */
#define COM_FIOCTL_GET_CONFIGURATION      0x8500				/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_COM_SDK091000_ in your application. 
																					  @brief parameter type is COM_CONFIG : Read serial line configuration  */

#endif   // _DEPRECATED_OEM_COM_SDK091000_

#endif   // OEM_COM_DEPRECATED_H

/*! @}  */ 

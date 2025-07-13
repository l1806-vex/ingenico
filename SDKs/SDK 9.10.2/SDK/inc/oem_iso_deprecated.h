#ifndef __OEM_ISO_DEPRECATED_H_INCLUDED__
#define __OEM_ISO_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_OEM_ISO_SDK091000_

#define SWP_FIOCTL_GET_MIN_CLOCK 			0x8000   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param unsigned int: get clock minimum value ( noted during F2F decoding ) */
#define SWP_FIOCTL_GET_MOY_CLOCK 			0x8001   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param unsigned int: get clock average value ( noted during F2F decoding ) */
#define SWP_FIOCTL_GET_MAX_CLOCK 			0x8002   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param unsigned int: get clock maximum value ( noted during F2F decoding ) */
#define SWP_FIOCTL_GET_MAX_JITTER 			0x8004   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param int ( low level basic decoding only ) */
#define SWP_FIOCTL_SET_MAX_JITTER 			0x8005   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param int ( low level basic decoding only ) */
#define SWP_FIOCTL_GET_COEF_ACCEL 			0x8006   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param int ( low level basic decoding only ) */
#define SWP_FIOCTL_SET_COEF_ACCEL 			0x8007   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param int ( low level basic decoding only ) */
#define SWP_FIOCTL_GET_SAMPLE 				0x8008		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief param unsigned int: get queue item indexed value ( index must be defined by caller ) */
#define SWP_FIOCTL_GET_SAMPLE_COUNT 		0x8009		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief For test & terminal with BOOSTER1/2 only: param unsigned int: get queue available items count */
#define SWP_FIOCTL_SET_REFILL 				0x800a		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief For test & terminal with BOOSTER1/2 only: param void 		  : refill last read file buffer, the goal is to re-run decoding algorithm with new parameters */
#define SWP_FIOCTL_SET_DECODING_LEVEL		0x800b		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief For test & terminal with BOOSTER1/2 only: param unsigned int: modify F2F decoding level (uses: SWP_F2F_DECODING_LEVEL_X parameter ) */
#define SWP_FIOCTL_LNK_DUMP_ANALOGIQUE		0x8100		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief For test & terminal with BOOSTER3 only: subscribe an analog buffer to receive ISO analog samples */
#define SWP_FIOCTL_UPDATE_DUMP_ANALOGIQUE	0x8101		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief For test & terminal with BOOSTER3 only: to be used after reading :updates analog buffer last got samples */
#define SWP_FIOCTL_PARAM_MODIFY				0x8102		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																			  @brief For test & terminal with BOOSTER3 only: modify swipe parameters */
#define SWP_FIOCTL_PARAM_GET				0x8103		   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_ISO_SDK091000_ in your application. 
																		     @brief For test & terminal with BOOSTER3 only: read swipe parameters  */

                                                           
#endif // _DEPRECATED_OEM_ISO_SDK091000_

#endif // __OEM_ISO_DEPRECATED_H_INCLUDED__

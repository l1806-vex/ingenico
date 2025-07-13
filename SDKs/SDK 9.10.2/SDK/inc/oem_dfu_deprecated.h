#ifndef __OEM_DFU_DEPRECATED_H_INCLUDED__
#define __OEM_DFU_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_OEM_DFU_SDK091000_

#define DFU_FIOCTL_GET_STATUS               0x8000        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param unsigned int : Get DFU driver state */
#define DFU_FIOCTL_SET_FILE                 0x8001        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param char*        : Set file to download "/DISK/FILE" */
#define DFU_FIOCTL_GET_VID                  0x8003        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param unsigned int : read PID of connected device */
#define DFU_FIOCTL_GET_PID                  0x8004        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param char*        : read VID of connected device */
#define DFU_FIOCTL_START_DNLOAD             0x8005        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param none         : Start downloading */
#define DFU_FIOCTL_GET_FILE_PROGRESS        0x8007        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param unsigned int : get current file achivement rate (0-100) */
#define DFU_FIOCTL_ABORT_DNLOAD             0x8010        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																				   @brief param none         : Abort downloading */


//DFU_FIOCTL_GET_STATUS
#define DFU_STATUS_NOT_CNX            0		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : not connected */
#define DFU_STATUS_CNX                1		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : connected */
#define DFU_STATUS_DNLOAD_IN_PROGRESS 2		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : download in progress */
#define DFU_STATUS_DNLOAD_END         3		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : end of download */
#define DFU_STATUS_FILE_ERR           4		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : file error (probably not found) */
#define DFU_STATUS_USB_ERR            5		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : download fail - USB error (probably device removed) */
#define DFU_STATUS_USER_ABORT_ERR     6		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_DFU_SDK091000_ in your application. 
																  @brief value for DFU_FIOCTL_GET_STATUS : download aborted by user (using DFU_FIOCTL_ABORT_DNLOAD) */


#endif // _DEPRECATED_OEM_DFU_SDK091000_

#endif // __OEM_DFU_DEPRECATED_H_INCLUDED__
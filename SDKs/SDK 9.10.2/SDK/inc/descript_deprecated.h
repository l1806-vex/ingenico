#ifndef __DESCRIPT_DEPRECATED_H_INCLUDED__
#define __DESCRIPT_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_TRAP_SDK091000_

#define USB_FIOCTL_GET_DEVICE_PID            0x7000		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_TRAP_SDK091000_ in your application. 
																				  @brief Get connected device PID, parameter is unsigned int */
#define USB_FIOCTL_GET_DEVICE_VID            0x7001		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_TRAP_SDK091000_ in your application. 
																				  @brief Get connected device VID, parameter is unsigned int */

#endif // _DEPRECATED_TRAP_SDK091000_

#endif // __DESCRIPT_DEPRECATED_H_INCLUDED__

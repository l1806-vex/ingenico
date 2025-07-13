#ifndef __OEM_GEN_IO_DEPRECATED_H_INCLUDED__
#define __OEM_GEN_IO_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_OEM_GEN_IO_SDK091000_

// define for all product
#define GEN_IO_FIOCTL_READ			0x8001			/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_GEN_IO_SDK091000_ in your application. 
																	  @brief Generic command to read an IO port */
#define GEN_IO_FIOCTL_WRITE			0x8002		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_GEN_IO_SDK091000_ in your application. 
																	  @brief Generic command to write on an IO port */

// define for product MR40
#define GEN_IO_FIOCTL_READ_MR40		0x8100		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_GEN_IO_SDK091000_ in your application. 
																	  @brief Specific command to read IO port on the connector of the MR40 which is used for the additionnal card (modem/GPRS) */
#define GEN_IO_FIOCTL_WRITE_MR40	0x8101			/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_GEN_IO_SDK091000_ in your application. 
																	  @brief Specific command to write IO port on the connector of the MR40 which is used for the additionnal card (modem/GPRS) */

                                                     
#endif // _DEPRECATED_OEM_GEN_IO_SDK091000_

#endif // __OEM_GEN_IO_DEPRECATED_H_INCLUDED__

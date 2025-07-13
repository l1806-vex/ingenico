/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_USB_H
#define OEM_USB_H

#include "oem_com.h"

/*
======================================================================
                  *** USB HOST - Communication devices *** 
======================================================================
*/

//! \addtogroup USB_DEVICE_CODE USB error codes
//! \brief error codes returned by fioctl
//! @{

#define USBDEV_OK						0			//!< OK
#define USBDEV_ERR_BAD_CMD				(-1)		//!< unknown fioctl
#define USBDEV_ERR_NOT_SUPPORTED		(-2)		//!< unsupported fioctl or mode
#define USBDEV_ERR_BAD_PRM				(-3)		//!< wrong parameter
#define USBDEV_ERR_DEPRECATED			(-4)		//!< deprecated fioctl

//!@}

// FIOCTL 0x8000 to 0x801F are reserved for COM RS232/USB compatibility

#ifdef _DEPRECATED_USB_SDK96_
#define USBCOM_FIOCTL_SET_DTR            0x8020		/*!< @deprecated Set DTR signal - Only for compatibility : please use \ref COM_FIOCTL_SET_DTR */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBCOM_FIOCTL_CLEAR_DTR          0x8021		/*!< @deprecated Clear DTR signal - Only for compatibility : please use \ref COM_FIOCTL_CLEAR_DTR */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBCOM_FIOCTL_SET_RTS            0x8022		/*!< @deprecated Set RTS signal. Flow control must be disabled - Only for compatibility : please use \ref COM_FIOCTL_SET_RTS */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBCOM_FIOCTL_CLEAR_RTS          0x8023		/*!< @deprecated Clear RTS signal. Flow control must be disable - Only for compatibility : please use \ref COM_FIOCTL_CLEAR_RTS */
#endif

/*
======================================================================
                  *** USB HOST - COM6 only *** 
======================================================================
*/

// FIOCTL 0x8000 to 0x801F are reserved for COM RS232/USB compatibility

#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_GET_PID            0x8026		/*!< COM6 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief Get PID, parameter is unsigned int */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_GET_VID            0x8027		/*!< COM6 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief Get VID, parameter is unsigned int */
#endif

/*
======================================================================
                  *** USB DEVICE - COM5 only *** 
======================================================================
*/

#define USBDEV_FIOCTL_RESET              0x8008 	/*!< COM5 : Disconnect and then reconnect USB device */

#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_GET_STATE          0x8009 	/*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief gets device state - parameter type is unsigned int : 
                                                       1 = a "set configuration" command has been received 
                                                       0 = device is not connected
                                                   */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_CNX                0x8010 	/*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief gets device connection state - parameter type is unsigned int :
                                                       1 = device is connect
                                                       0 = device is not connected
                                                   */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_HANG               0x8011		/*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief gets device connection state - parameter type is unsigned int : 
                                                       1 = USB bus is suspended or disconnected 
                                                       0 = device is operationnal state
                                                   */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_SET_VID            0x8012   /*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Set VID, parameter is unsigned int.  Only for compatibility : use \ref USBDEV_FIOCTL_SET_MODE.*/
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_SET_PID            0x8013   /*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Set PID, parameter is unsigned int.  Only for compatibility : use \ref USBDEV_FIOCTL_SET_MODE.*/
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_SET_MAX_PWR        0x8014   /*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief Set max power consumption.
                                                       Parameter type is unsigned int
                                                       unit is 1 mA 
                                                  */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_SET_SPEED          0x8015   /*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Set USB device bus speed: HS(1)/FS(0) if available */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_START_DRIVER       0x8024		/*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Start USB device stack */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_STOP_DRIVER        0x8025		/*!< COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Stop USB device stack */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_START_HID          0x8028    /*!<  COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Activate default HID mode. Only for compatibility : use \ref USBDEV_FIOCTL_SET_MODE. \return 0. \warning only for the products which support \ref USB_DEVICE_MODE_HID */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_STOP_HID           0x8029    /*!<  COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Deactivate all HID modes, Only for compatibility : use \ref USBDEV_FIOCTL_SET_MODE. return to CDC class.\return 0.*/
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_HID_STATUS         0x8030    /*!<  COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Get HID status On/Off.   Only for compatibility : use \ref USBDEV_FIOCTL_GET_MODE.*/
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_START_HID_SV       0x8031    /*!<  COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Activate Sesame Vitale HID mode. This mode is no longer supported */
#endif

#define USBDEV_FIOCTL_HID_GET_ENDPT_SZ   0x8032    /*!<  COM5 : Get endpoint size according to the HID mode and speed.*/ 

#define USBDEV_FIOCTL_SET_MODE	         0x8033    /*!<  COM5 : Set usb dev mode : store the value and swith the usb device mode \param int* \ref USB_DEVICE_MODE. \return \ref USB_DEVICE_CODE. \note @li supported by SDK>=8.2. @li supported if \ref FIOCTL_GET_VERSION (COM5) returns >=2. @li To swith mode without saving, use \ref USBDEV_FIOCTL_SWITCH_MODE.*/

#define USBDEV_FIOCTL_GET_MODE	         0x8034    /*!<  COM5 : Get usb dev mode : store the value and swith the usb device mode \param int* \return \ref USB_DEVICE_CODE. \note supported by SDK>=8.2.<br>supported if \ref FIOCTL_GET_VERSION (COM5) returns >=2.*/

#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_SWITCH_MODE	     0x8035    /*!<  COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Switch the USB device mode without saving it. The previous mode will be restored at the terminal startup \param int* \ref USB_DEVICE_MODE. \return \ref USB_DEVICE_CODE. \note @li supported by SDK>=8.2.@li supported if \ref FIOCTL_GET_VERSION (COM5) returns >=2.@li To swith mode and save it, use \ref USBDEV_FIOCTL_SET_MODE*/
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_SET_USER_SERIAL_NUMBER	0x8036    /*!<  COM5 : @deprecated This fioctl has been parsed as unused and will be no longer supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  enable and set the serial number string. \param char* user string (max size 20, 0 included) \return \ref USB_DEVICE_CODE.

\note The string is stored (and restored at startup).

\n\b Example:
\include oem_usb_Sample_01.c


 */
#endif
#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_GET_USER_SERIAL_NUMBER	0x8037    /*!<  COM5 : enable and set the serial number string.*/
#endif

#define USBDEV_FIOCTL_SET_SERIAL_NUMBER_STATUS	0x8038    /*!<  COM5 : enable the serial number string: \param unsigned int* \ref USBDEV_SERIAL_NUMBER_ENABLED or \ref USBDEV_SERIAL_NUMBER_DISABLED.

\return \ref USB_DEVICE_CODE.
\note The status is stored (and restored at startup).

\n\b Example:
\include oem_usb_Sample_02.c
*/

#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_GET_SERIAL_NUMBER_STATUS	0x8039    /*!<  COM5 : get the serial number string state: \param \ref USBDEV_SERIAL_NUMBER_ENABLED or \ref USBDEV_SERIAL_NUMBER_DISABLED \return \ref USB_DEVICE_CODE */
#endif
//! \addtogroup USB_DEVICE_MODE USB Device Mode values
//! @{
//! \brief Available modes (fioctl \ref USBDEV_FIOCTL_SET_MODE, \ref USBDEV_FIOCTL_GET_MODE, \ref USBDEV_FIOCTL_SWITCH_MODE)
//!
//! \n\b Example:
//! \include oem_usb_Sample_03.c
#define USB_DEVICE_MODE_CDC_DEFAULT				0 	/*!< default cdc mode : \ref USB_DEVICE_MODE_CDC_LEGACY or \ref USB_DEVICE_MODE_CDC ( manufacturer settings ). \warning USB_DEVICE_MODE_CDC_DEFAULT is used to set the default mode but \ref USBDEV_FIOCTL_GET_MODE can't return this value.*/
#define USB_DEVICE_MODE_CDC_LEGACY				1	/*!< CDC Legacy  : VID PID Telium.\note VID=0x079B PID=0x0028*/
#define USB_DEVICE_MODE_CDC						2	/*!< CDC : proper VID PID<br>\note Mode supported by products Thunder II & III.<br>Values of VID PID: <br><br><table>
<tr><th>  Product  </th><th>  VID  </th><th>  PID  </th></tr>
<tr><td>iCT220</td><td>0x0B00</td><td>0x0066</td></tr>
<tr><td>iCT250</td><td>0x0B00</td><td>0x0066</td></tr>
<tr><td>iPP320</td><td>0x0B00</td><td>0x0060</td></tr>
<tr><td>iPP350</td><td>0x0B00</td><td>0x0060</td></tr>
<tr><td>iPP480</td><td>0x0B00</td><td>0x0060</td></tr>
<tr><td>iSC250</td><td>0x0B00</td><td>0x0062</td></tr>
<tr><td>iSC350</td><td>0x0B00</td><td>0x0061</td></tr>
<tr><td>iWL220</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>iWL250</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>iWL280</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>iWL350</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>E532</td><td>0x0B00</td><td>0x0067</td></tr>
</table>
*/

#define USB_DEVICE_MODE_HID						3	/*!< HID mode 
\note This mode is supported by the products below.
<br><table>
<tr><th>Product</th><th>VID</th><th>PID</th></tr>
<tr><td>iPP320</td><td>0x0B00</td><td>0x0071</td></tr>
<tr><td>iPP350</td><td>0x0B00</td><td>0x0072</td></tr>
<tr><td>iPP480</td><td>0x0B00</td><td>0x0075</td></tr>
<tr><td>iSC250</td><td>0x0B00</td><td>0x0074</td></tr>
<tr><td>iSC350</td><td>0x0B00</td><td>0x0073</td></tr>
</table>
*/
#define USB_DEVICE_MODE_CDC_SV					4	/*!< French Health Care Domain CDC Sesame Vitale.\note VID=0x079B PID=0x0028*/
#define USB_DEVICE_MODE_TELIUM_IUC				5   /*!< Internal use only */
#define USB_DEVICE_MODE_DEVICE_INTELLIGENT		6   /*!< Internal use only */

//!@}


#define USBDEV_SERIAL_NUMBER_DISABLED			0	/*!< Serial number string disabled*/
#define USBDEV_SERIAL_NUMBER_ENABLED 			1	/*!< Serial number string enabled*/
	
/*
======================================================================
 FIOCTL 0x8100 to 0x8200 are reserved for new Modem fioctl
======================================================================
*/

/*
================================================================================
 FIOCTL 0x8500 to 0x8600 are reserved for new Modem/COM RS232/USB compatibility
================================================================================
*/

#ifdef _DEPRECATED_USB_SDK96_
#define COM_FIOCTL_GET_CONFIGURATION      0x8500				/*!< parameter type is COM_CONFIG : Read serial line configuration  */
#endif

/*
======================================================================
                  *** Only for compatibility *** 
======================================================================
*/
#define _USBDEV_FIOCTL_RESET             8 				/*!< Only for compatibility : do not use */
#define _USBDEV_FIOCTL_GET_STATE         9 				/*!< Only for compatibility : do not use */
#define _USBDEV_FIOCTL_CNX               10 			/*!< Only for compatibility : do not use */
#define _USBDEV_FIOCTL_HANG              11				/*!< Only for compatibility : do not use */
// For Manager compatibility. Delete thereafter

#define FIOCTL_RESET_USB         _USBDEV_FIOCTL_RESET				/*!< Only for compatibility : do not use */

#define FIOCTL_STATE_USB_DEV     _USBDEV_FIOCTL_GET_STATE 			/*!< Only for compatibility : do not use */

#define FIOCTL_CNX_USB_DEV       _USBDEV_FIOCTL_CNX 				/*!< Only for compatibility : do not use */

#define FIOCTL_USB_HANG			 _USBDEV_FIOCTL_HANG				/*!< Only for compatibility : do not use */

#ifdef _DEPRECATED_USB_SDK96_
#define USBDEV_FIOCTL_GET_CTS            0x8003		/*!< Returns CTS state - Only for compatibility : please use \ref COM_FIOCTL_GET_CTS */
#endif

#endif
/*! @}  */ 

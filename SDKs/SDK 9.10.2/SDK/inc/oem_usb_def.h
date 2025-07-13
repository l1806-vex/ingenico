#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_USB_DEF_H_INCLUDED__
#define __OEM_USB_DEF_H_INCLUDED__

#include "oem_com_def.h"

/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

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



/*
======================================================================
                  *** USB DEVICE - COM5 only *** 
======================================================================
*/

#define USBDEV_FIOCTL_RESET              0x8008 	/*!< COM5 : Disconnect and then reconnect USB device */


#define USBDEV_FIOCTL_HID_GET_ENDPT_SZ   0x8032    /*!<  COM5 : Get endpoint size according to the HID mode and speed.*/ 

#define USBDEV_FIOCTL_SET_MODE	         0x8033    /*!<  COM5 : Set usb dev mode : store the value and swith the usb device mode \param int* \ref USB_DEVICE_MODE. \return \ref USB_DEVICE_CODE. \note @li supported by SDK>=8.2. @li supported if \ref FIOCTL_GET_VERSION (COM5) returns >=2.*/

#define USBDEV_FIOCTL_GET_MODE	         0x8034    /*!<  COM5 : Get usb dev mode : store the value and swith the usb device mode \param int* \return \ref USB_DEVICE_CODE. \note supported by SDK>=8.2.<br>supported if \ref FIOCTL_GET_VERSION (COM5) returns >=2.*/

#define USBDEV_FIOCTL_SET_SERIAL_NUMBER_STATUS	0x8038    /*!<  COM5 : enable the serial number string: \param unsigned int* \ref USBDEV_SERIAL_NUMBER_ENABLED or \ref USBDEV_SERIAL_NUMBER_DISABLED.

\return \ref USB_DEVICE_CODE.
\note The status is stored (and restored at startup).

\n\b Example:
\include oem_usb_Sample_02.c
*/

//! \addtogroup USB_DEVICE_MODE USB Device Mode values
//! @{
//! \brief Available modes (fioctl \ref USBDEV_FIOCTL_SET_MODE, \ref USBDEV_FIOCTL_GET_MODE)
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

/*! @}  */ 


#endif   // __OEM_USB_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif

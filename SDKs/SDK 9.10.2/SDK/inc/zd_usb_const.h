#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ZD_USB_CONST_H_INCLUDED__
#define __ZD_USB_CONST_H_INCLUDED__

/*! @addtogroup KSFAM_IOSF
	* @{
 */

/*
======================================================================
					List of Defines
======================================================================
*/

// events flags : INTERNAL
#define CONNECT_EVT              0x00000001		/*!< Event mask : !0 <-> detected USB connect */
#define DISCONNECT_EVT           0x00000002		/*!< Event mask : !0 <-> detected USB disconnect */
#define WRITE_COMPLETE_EVT       0x00000010		/*!< Event mask : !0 <-> Write complete */
#define READ_COMPLETE_EVT        0x00000020		/*!< Event mask : !0 <-> Read complete */
#define WRITE_EVT                0x00000100		/*!< Event mask : !0 <-> Received data */
#define SPEED_EVT                0x00001000		/*!< Event mask : !0 <-> Received new Speed */
#define CMD_COMPLETE_EVT         0x00010000		/*!< Event mask : !0 <-> Command completed */
#define RSP_COMPLETE_EVT         0x00020000		/*!< Event mask : !0 <-> RSP completed */
#define RUN_TASKLET_EVT          0x00100000		/*!< Event mask : !0 <-> Started a Tasklet */

// events flags : EXTERNAL
// Event sent to the system when associated to an AP
#define WIFI_JOIN_EVENT          0x00000001		/*!< Event mask : !0 <-> Found a Wifi AP */
// Event sent to the system to inform of AP lost
#define WIFI_DISJOIN_EVENT       0x00000002		/*!< Event mask : !0 <-> Lost a Wifi AP */
// Event sent to system when scan is done
#define WIFI_SCAN_EVENT          0x00000004		/*!< Event mask : !0 <-> End of scan */

// possible return value for OEM_WIFI_IOCTL_GET_CONNECTION_PROGRESS
#define OEM_WIFI_IOCTL_CONNECTION_PROGRESS_IDLE       (0)		/*!< Wifi connection idle */
#define OEM_WIFI_IOCTL_CONNECTION_PROGRESS_SCANNING   (1)		/*!< Wifi scanning */
#define OEM_WIFI_IOCTL_CONNECTION_PROGRESS_SCAN_DONE  (2)		/*!< Wifi scan finished */
#define OEM_WIFI_IOCTL_CONNECTION_PROGRESS_CONNECTING (3)		/*!< Wifi connection in progress */
#define OEM_WIFI_IOCTL_CONNECTION_PROGRESS_CONNECTED  (4)		/*!< Wifi connected */

/*! @}  */


#endif   // __ZD_USB_CONST_H_INCLUDED__

#ifdef __cplusplus
}
#endif

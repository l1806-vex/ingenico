/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_DFU_H
#define OEM_DFU_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define DFU_FIOCTL_GET_STATUS               0x8000        /*!< param unsigned int : Get DFU driver state */
#define DFU_FIOCTL_SET_FILE                 0x8001        /*!< param char*        : Set file to download "/DISK/FILE" */
#define DFU_FIOCTL_GET_VID                  0x8003        /*!< param unsigned int : read PID of connected device */
#define DFU_FIOCTL_GET_PID                  0x8004        /*!< param char*        : read VID of connected device */
#define DFU_FIOCTL_START_DNLOAD             0x8005        /*!< param none         : Start downloading */
#define DFU_FIOCTL_GET_FILE_PROGRESS        0x8007        /*!< param unsigned int : get current file achivement rate (0-100) */
#define DFU_FIOCTL_ABORT_DNLOAD             0x8010        /*!< param none         : Abort downloading */


//DFU_FIOCTL_GET_STATUS
#define DFU_STATUS_NOT_CNX            0		/*!< value for DFU_FIOCTL_GET_STATUS : not connected */
#define DFU_STATUS_CNX                1		/*!< value for DFU_FIOCTL_GET_STATUS : connected */
#define DFU_STATUS_DNLOAD_IN_PROGRESS 2		/*!< value for DFU_FIOCTL_GET_STATUS : download in progress */
#define DFU_STATUS_DNLOAD_END         3		/*!< value for DFU_FIOCTL_GET_STATUS : end of download */
#define DFU_STATUS_FILE_ERR           4		/*!< value for DFU_FIOCTL_GET_STATUS : file error (probably not found) */
#define DFU_STATUS_USB_ERR            5		/*!< value for DFU_FIOCTL_GET_STATUS : download fail - USB error (probably device removed) */
#define DFU_STATUS_USER_ABORT_ERR     6		/*!< value for DFU_FIOCTL_GET_STATUS : download aborted by user (using DFU_FIOCTL_ABORT_DNLOAD) */

#endif

/*! @}  */ 



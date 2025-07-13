#ifdef __cplusplus
extern "C" {
#endif
 
#ifndef __OEM_CAM_H_INCLUDED__
#define __OEM_CAM_H_INCLUDED__

#ifdef __FRAMEWORK_TELIUM_2__
#include "oem_cam_deprecated.h"
#endif

/*! @addtogroup KSFAM_IOSF
	* @{
 */  

/*
======================================================================
					List of Defines
======================================================================
*/

// Returns oem
#define CAM_FIOCTL_SUCCESS             (1)      /*!< Return if the fioctl command is successful */
#define CAM_FIOCTL_NOT_IMPLEMENTED     (0)      /*!< Return if the fioctl command is unknown */
#define CAM_FIOCTL_ERR_UNAUTHORIZED    (-1)     /*!< Return if the fioctl is unauthorized (depending on the product) */
#define CAM_FIOCTL_BAD_PARAM           (-2)     /*!< Return if parameters are incorrect */
#define CAM_FIOCTL_ERR_LEVEL1          (-3)     /*!< Return if level 1 error (see status in fioctl parameter) */


// FIOCTL defines functions
#define CAM_XX_FIOCTL_EXTERNAL         0x8100		/*!< Base for the following fioctl */




#define CAM_FIOCTL_SET_PPS             CAM_XX_FIOCTL_EXTERNAL+3      /*!< Command to enable or disable the PPS function after ATR 
                                                                          @param (int *) */

#define CAM_FIOCTL_SET_TENSION         CAM_XX_FIOCTL_EXTERNAL+5      /*!< Command to set the current cam supply voltage 
                                                                          @param (int *) */

#define CAM_FIOCTL_GET_VCC_STATE       CAM_XX_FIOCTL_EXTERNAL+9      /*!< Command to get the current cam power state 
                                                                          @param (int *) */

#define CAM_FIOCTL_SET_FIRST_IFS_RQST  CAM_XX_FIOCTL_EXTERNAL+10     /*!< Command to enable or disable the IFS request send at the first card exchange after ATR (in T=1, ISO7816)  
                                                                          @param (int *) */
                                                                          
#


// Used with CAM_FIOCTL_SET_PPS and CAM_FIOCTL_GET_PPS
#define PPS_ENABLE                     0		/*!< Default state. Enable the PPS function */
#define PPS_DISABLE                    1		/*!< Disable the PPS function */

// Used with \ref CAM_FIOCTL_SET_TENSION and \ref CAM_FIOCTL_GET_TENSION 
#define CAM_TENSION_5VOLT              0		/*!< Default state. Set the cam supply voltage to 5V */
#define CAM_TENSION_3VOLT              1		/*!< Set the cam supply voltage to 3V  */

// Used with \ref CAM_FIOCTL_GET_VCC_STATE  
#define CAM_VCC_OFF                    0		/*!< Cam power state is Off */
#define CAM_VCC_ON                     1		/*!< Cam power state is On */

//Used with \ref CAM_FIOCTL_SET_FIRST_IFS_RQST and \ref CAM_FIOCTL_GET_FIRST_IFS_RQST
#define IFS_RQST_DISABLE               0     	/*!< Default state. Disable the IFS request send at the first card exchange. */
#define IFS_RQST_ENABLE                1		/*!< Enable the IFS request send at the first card exchange. */

/*! @}  */ 


#endif   // __OEM_CAM_H_INCLUDED__

#ifdef __cplusplus
}
#endif

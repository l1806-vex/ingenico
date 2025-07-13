/*! @addtogroup KSFAM_IOSF
	* @{
 */  
 
#ifndef CAM_OEM_H
#define CAM_OEM_H

/*
======================================================================
					List of Defines
======================================================================
*/

// Returns oem
#define CAM_FIOCTL_SUCCESS             (1)		/*!< Return if the fioctl command is successful */
#define CAM_FIOCTL_NOT_IMPLEMENTED     (0)		/*!< Return if the fioctl command is unknown */
#define CAM_FIOCTL_ERR_UNAUTHORIZED    (-1)		/*!< Return if the fioctl is unauthorized (depending on the product) */



// FIOCTL defines functions
#define CAM_XX_FIOCTL_EXTERNAL         0x8100		/*!< Base for the following fioctl : you must pass an integer pointeur parameter (int *) for in/out fioctl */

#define CAM_FIOCTL_SET_NET1_SPEED      CAM_XX_FIOCTL_EXTERNAL+1		/*!< Command to enable or disable the Net1 speed function */
#define CAM_FIOCTL_GET_NET1_SPEED      CAM_XX_FIOCTL_EXTERNAL+2		/*!< Command to get the current Net1 Speed function state (enable or disable) */
#define CAM_FIOCTL_SET_PPS             CAM_XX_FIOCTL_EXTERNAL+3		/*!< Command to enable or disable the PPS function after ATR */
#define CAM_FIOCTL_GET_PPS             CAM_XX_FIOCTL_EXTERNAL+4		/*!< Command to get the current PPS function state (enable or disable) */
#define CAM_FIOCTL_SET_TENSION         CAM_XX_FIOCTL_EXTERNAL+5		/*!< Command to set the current cam supply voltage */
#define CAM_FIOCTL_GET_TENSION         CAM_XX_FIOCTL_EXTERNAL+6		/*!< Command to get the current cam supply voltage */
#define CAM_FIOCTL_SET_FREQ            CAM_XX_FIOCTL_EXTERNAL+7		/*!< Command to set the current cam frequence */
#define CAM_FIOCTL_GET_FREQ            CAM_XX_FIOCTL_EXTERNAL+8		/*!< Command to get the current cam frequence */
#define CAM_FIOCTL_GET_VCC_STATE       CAM_XX_FIOCTL_EXTERNAL+9		/*!< Command to get the current cam power state */
#define CAM_FIOCTL_SET_FIRST_IFS_RQST  CAM_XX_FIOCTL_EXTERNAL+10	/*!< Command to enable or disable the IFS request send at the first card exchange after ATR (in T=1, ISO7816)  */
#define CAM_FIOCTL_GET_FIRST_IFS_RQST  CAM_XX_FIOCTL_EXTERNAL+11	/*!< Command to get the current First IFS request state */


// Used with CAM_FIOCTL_SET_NET1_SPEED and CAM_FIOCTL_GET_NET1_SPEED
#define NET1_SPEED_ENABLE              1		/*!< Enable the Net1 Speed function */
#define NET1_SPEED_DISABLE             0		/*!< Default state. Disable the Net1 Speed function */

// Used with CAM_FIOCTL_SET_PPS and CAM_FIOCTL_GET_PPS
#define PPS_ENABLE                     0		/*!< Default state. Enable the PPS function */
#define PPS_DISABLE                    1		/*!< Disable the PPS function */

// Used with CAM_FIOCTL_SET_TENSION and CAM_FIOCTL_GET_TENSION 
#define CAM_TENSION_5VOLT              0		/*!< Default state. Set the cam supply voltage to 5V */
#define CAM_TENSION_3VOLT              1		/*!< Set the cam supply voltage to 3V  */

// Used with CAM_FIOCTL_SET_FREQ and CAM_FIOCTL_GET_FREQ 
#define CAM_FREQ_3_57_MHZ              1		/*!< Set the cam frequence to 3.57MHz */
#define CAM_FREQ_5_MHZ                 0		/*!< Default state. Set the cam frequence to 5MHz */

// Used with CAM_FIOCTL_GET_VCC_STATE  
#define CAM_VCC_OFF                    0		/*!< Cam power state is Off */
#define CAM_VCC_ON                     1		/*!< Cam power state is On */

//Used with CAM_FIOCTL_SET_FIRST_IFS_RQST and CAM_FIOCTL_GET_FIRST_IFS_RQST
#define IFS_RQST_DISABLE               0     	/*!< Default state. Disable the IFS request send at the first card exchange. */
#define IFS_RQST_ENABLE                1		/*!< Enable the IFS request send at the first card exchange. */

#endif

/*! @}  */ 



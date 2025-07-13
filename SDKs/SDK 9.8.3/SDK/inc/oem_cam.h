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
#define CAM_FIOCTL_SUCCESS             (1)      /*!< Return if the fioctl command is successful */
#define CAM_FIOCTL_NOT_IMPLEMENTED     (0)      /*!< Return if the fioctl command is unknown */
#define CAM_FIOCTL_ERR_UNAUTHORIZED    (-1)     /*!< Return if the fioctl is unauthorized (depending on the product) */
#define CAM_FIOCTL_BAD_PARAM           (-2)     /*!< Return if parameters are incorrect */
#define CAM_FIOCTL_ERR_LEVEL1          (-3)     /*!< Return if level 1 error (see status in fioctl parameter) */


// FIOCTL defines functions
#define CAM_XX_FIOCTL_EXTERNAL         0x8100		/*!< Base for the following fioctl */


#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_SET_NET1_SPEED      CAM_XX_FIOCTL_EXTERNAL+1      /*!< @deprecated This fioctl has been parsed as unused.It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief Command to enable or disable the Net1 speed function 
                                                                          @param (int *) */
#endif

#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_GET_NET1_SPEED      CAM_XX_FIOCTL_EXTERNAL+2      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current Net1 Speed function state (enable or disable) 
                                                                          @param (int *) */
#endif                                                                          


#define CAM_FIOCTL_SET_PPS             CAM_XX_FIOCTL_EXTERNAL+3      /*!< Command to enable or disable the PPS function after ATR 
                                                                          @param (int *) */

#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_GET_PPS             CAM_XX_FIOCTL_EXTERNAL+4      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current PPS function state (enable or disable) 
                                                                          @param (int *) */
#endif

#define CAM_FIOCTL_SET_TENSION         CAM_XX_FIOCTL_EXTERNAL+5      /*!< Command to set the current cam supply voltage 
                                                                          @param (int *) */


#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_GET_TENSION         CAM_XX_FIOCTL_EXTERNAL+6      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current cam supply voltage 
                                                                          @param (int *) */
#endif

#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_SET_FREQ            CAM_XX_FIOCTL_EXTERNAL+7      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to set the current cam frequence 
                                                                          @param (int *) */
#endif

#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_GET_FREQ            CAM_XX_FIOCTL_EXTERNAL+8      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current cam frequence 
                                                                          @param (int *) */
#endif


#define CAM_FIOCTL_GET_VCC_STATE       CAM_XX_FIOCTL_EXTERNAL+9      /*!< Command to get the current cam power state 
                                                                          @param (int *) */

#define CAM_FIOCTL_SET_FIRST_IFS_RQST  CAM_XX_FIOCTL_EXTERNAL+10     /*!< Command to enable or disable the IFS request send at the first card exchange after ATR (in T=1, ISO7816)  
                                                                          @param (int *) */
                                                                          
#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_GET_FIRST_IFS_RQST  CAM_XX_FIOCTL_EXTERNAL+11     /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current First IFS request state 
                                                                          @param (int *) */
#endif                                                                          

#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_WARM_RESET          CAM_XX_FIOCTL_EXTERNAL+12	   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to issue a warm reset : available only in ISO7816 mode (use power_on function) 
                                                                          @param (CAM_FIOCTL_WARM_RESET_S *) */
#endif   

#ifdef _DEPRECATED_OEM_CAM_SDK96_
#define CAM_FIOCTL_SET_CUSTOM_ATR      CAM_XX_FIOCTL_EXTERNAL+13	   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to overwrite the current card ATR by a custom ATR : available only in ISO7816 mode (use power_on function)
                                                                          @param (CAM_FIOCTL_SET_CUSTOM_ATR_S *) */
#endif                                                                          


/*! @brief structure used with \ref CAM_FIOCTL_SET_CUSTOM_ATR fioctl : Used to overwrite the current card ATR by a custom ATR */
typedef struct
{
	int            status;                 /*!< (output) level 1 status */
	unsigned int   length;                 /*!< (input) length of custom ATR */
	unsigned char  *custom_atr;	         /*!< (input) custom ATR */
}CAM_FIOCTL_SET_CUSTOM_ATR_S; 


/*! @brief structure used with \ref CAM_FIOCTL_WARM_RESET fioctl : Used to issue a warm reset */
typedef struct
{
	int            status;                 /*!< (output) level 1 status */
	HISTORIC       historical_bytes;       /*!< (output) historical bytes */  
}CAM_FIOCTL_WARM_RESET_S; 


// Used with \ref CAM_FIOCTL_SET_NET1_SPEED and \ref CAM_FIOCTL_GET_NET1_SPEED
#define NET1_SPEED_ENABLE              1		/*!< Enable the Net1 Speed function */
#define NET1_SPEED_DISABLE             0		/*!< Default state. Disable the Net1 Speed function */

// Used with CAM_FIOCTL_SET_PPS and CAM_FIOCTL_GET_PPS
#define PPS_ENABLE                     0		/*!< Default state. Enable the PPS function */
#define PPS_DISABLE                    1		/*!< Disable the PPS function */

// Used with \ref CAM_FIOCTL_SET_TENSION and \ref CAM_FIOCTL_GET_TENSION 
#define CAM_TENSION_5VOLT              0		/*!< Default state. Set the cam supply voltage to 5V */
#define CAM_TENSION_3VOLT              1		/*!< Set the cam supply voltage to 3V  */

// Used with \ref CAM_FIOCTL_SET_FREQ and \ref CAM_FIOCTL_GET_FREQ 
#define CAM_FREQ_3_57_MHZ              1		/*!< Set the cam frequence to 3.57MHz */
#define CAM_FREQ_5_MHZ                 0		/*!< Default state. Set the cam frequence to 5MHz */

// Used with \ref CAM_FIOCTL_GET_VCC_STATE  
#define CAM_VCC_OFF                    0		/*!< Cam power state is Off */
#define CAM_VCC_ON                     1		/*!< Cam power state is On */

//Used with \ref CAM_FIOCTL_SET_FIRST_IFS_RQST and \ref CAM_FIOCTL_GET_FIRST_IFS_RQST
#define IFS_RQST_DISABLE               0     	/*!< Default state. Disable the IFS request send at the first card exchange. */
#define IFS_RQST_ENABLE                1		/*!< Enable the IFS request send at the first card exchange. */


#endif

/*! @}  */ 



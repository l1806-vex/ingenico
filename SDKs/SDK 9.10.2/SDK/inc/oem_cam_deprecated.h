/*! @addtogroup KSFAM_IOSF
	* @{
 */  
 
#ifndef CAM_OEM_DEPRECATED_H
#define CAM_OEM_DEPRECATED_H


#ifdef _DEPRECATED_OEM_CAM_SDK96_

/*
======================================================================
					List of Defines
======================================================================
*/


#define CAM_FIOCTL_SET_NET1_SPEED      CAM_XX_FIOCTL_EXTERNAL+1      /*!< @deprecated This fioctl has been parsed as unused.It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief Command to enable or disable the Net1 speed function 
                                                                          @param (int *) */

#define CAM_FIOCTL_GET_NET1_SPEED      CAM_XX_FIOCTL_EXTERNAL+2      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current Net1 Speed function state (enable or disable) 
                                                                          @param (int *) */

#define CAM_FIOCTL_GET_PPS             CAM_XX_FIOCTL_EXTERNAL+4      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current PPS function state (enable or disable) 
                                                                          @param (int *) */

#define CAM_FIOCTL_GET_TENSION         CAM_XX_FIOCTL_EXTERNAL+6      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current cam supply voltage 
                                                                          @param (int *) */

#define CAM_FIOCTL_SET_FREQ            CAM_XX_FIOCTL_EXTERNAL+7      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to set the current cam frequence 
                                                                          @param (int *) */

#define CAM_FIOCTL_GET_FREQ            CAM_XX_FIOCTL_EXTERNAL+8      /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current cam frequence 
                                                                          @param (int *) */

                                                                          
#define CAM_FIOCTL_GET_FIRST_IFS_RQST  CAM_XX_FIOCTL_EXTERNAL+11     /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to get the current First IFS request state 
                                                                          @param (int *) */

#define CAM_FIOCTL_WARM_RESET          CAM_XX_FIOCTL_EXTERNAL+12	   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to issue a warm reset : available only in ISO7816 mode (use power_on function) 
                                                                          @param (CAM_FIOCTL_WARM_RESET_S *) */

#define CAM_FIOCTL_SET_CUSTOM_ATR      CAM_XX_FIOCTL_EXTERNAL+13	   /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. If you need it, you may define _DEPRECATED_OEM_CAM_SDK96_ in your application.
                                                                          @brief  Command to overwrite the current card ATR by a custom ATR : available only in ISO7816 mode (use power_on function)
                                                                          @param (CAM_FIOCTL_SET_CUSTOM_ATR_S *) */

																		  
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

// Used with \ref CAM_FIOCTL_SET_FREQ and \ref CAM_FIOCTL_GET_FREQ 
#define CAM_FREQ_3_57_MHZ              1		/*!< Set the cam frequence to 3.57MHz */
#define CAM_FREQ_5_MHZ                 0		/*!< Default state. Set the cam frequence to 5MHz */
																		  

#endif  // _DEPRECATED_OEM_CAM_SDK96_

#endif  // CAM_OEM_DEPRECATED_H

/*! @}  */ 



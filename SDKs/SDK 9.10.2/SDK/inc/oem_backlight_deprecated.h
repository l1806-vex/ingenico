#ifndef __OEM_BACKLIGHT_DEPRECATED_H_INCLUDED__
#define __OEM_BACKLIGHT_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_BACKLIGHT_SDK96_
/*
======================================================================
					List of Defines
======================================================================
*/


//! \addtogroup BACKLIGHTFIOCTL_FIOCTL
//! @{ 

#define BACKLIGHT_FIOCTL_SET_TIME         	0x8000  /*!<  @deprecated You should use HWCNF_SetBacklightDelayEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set the timeout backlight delay @param unsigned int * : time before backlight off ; 0 = infinity / unit is 10 ms @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_START            	0x8002  /*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Start backlight @param NULL or \ref BACKLIGHT_PWM_PARAM_T* : if NULL, start the backlight with the previous level @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_STOP             	0x8003  /*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Stop backlight @param NULL  */
#define BACKLIGHT_FIOCTL_GET_STATE       	0x8004  /*!<  @deprecated You should use HWCNF_GetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Read backlight enable/disable state @param unsigned int *: \ref BACKLIGHT_ENABLE  , \ref BACKLIGHT_DISABLE @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_GET_ONOFF_STATE  	0x8005  /*!<  @deprecated This fioctl has been parsed as unused in our survey. It may not be supported in future releases of the SDK. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Read current backlight on/off state @param unsigned int *: \ref BACKLIGHT_FIOCTL_ON , \ref BACKLIGHT_FIOCTL_OFF @return \ref BACKLIGHTFIOCTL_ERR  */
#define BACKLIGHT_FIOCTL_GET_TYPE         	0x8006  /*!<  @deprecated This fioctl has been parsed as unused in our survey. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Get backlight type @param unsigned int * : @li \ref BACKLIGHT_STANDART_BW Single @li \ref BACKLIGHT_AFF_SEPARE_BW Dual (Display and Keyboard) @li \ref BACKLIGHT_3LED_RGB RGB @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_SET_DISPLAY     	0x8008  /*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set only display backlight value @param BACKLIGHT_EXT_PARAM_T * level in % (0-100) @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_SET_KEYBOARD     	0x8009  /*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set only keyboard backlight value @param BACKLIGHT_EXT_PARAM_T * level in % (0-100) @return \ref BACKLIGHTFIOCTL_ERR */

#define BACKLIGHT_FIOCTL_GET_DISPLAY      	0x800A  /*!<  @deprecated You should use HWCNF_GetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Get the display backlight value @param unsigned int*  level in % (0-100) @return \ref BACKLIGHTFIOCTL_ERR  */
#define BACKLIGHT_FIOCTL_GET_KEYBOARD     	0x800B  /*!<  @deprecated You should use HWCNF_GetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Get the keyboard backlight value @param unsigned int* level in % (0-100) @note Only if \ref BACKLIGHT_AFF_SEPARE_BW @return \ref BACKLIGHTFIOCTL_ERR   */

#define BACKLIGHT_FIOCTL_SET_KEYBOARD_STATE 0x800C  /*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set the keyboard backlight state @param unsigned int* : \ref BACKLIGHT_KEYBOARD_ENABLE , \ref BACKLIGHT_KEYBOARD_DISABLE @return \ref BACKLIGHTFIOCTL_ERR @note Only if \ref BACKLIGHT_AFF_SEPARE_BW */
#define BACKLIGHT_FIOCTL_GET_KEYBOARD_STATE 0x800D 	/*!<  @deprecated You should use HWCNF_GetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Get the current keyboard backlight status @param unsigned int* : \ref BACKLIGHT_KEYBOARD_ENABLE ,\ref BACKLIGHT_KEYBOARD_DISABLE @return \ref BACKLIGHTFIOCTL_ERR  @note Only if \ref BACKLIGHT_AFF_SEPARE_BW*/

#define BACKLIGHT_FIOCTL_SET_POWER_LEVEL  	0x800E	/*!<  @deprecated This fioctl has been parsed as unused in our survey. It may not be supported in future releases of the SDK. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set the power level @param unsigned int * : \ref BACKLIGHT_POWER_LEVEL_DEFAULT , \ref BACKLIGHT_POWER_LEVEL_LOW_01 @return \ref BACKLIGHTFIOCTL_ERR @note used to decrease the backlight consumption when other hight consumption functions are ON; cless for ex */
#define BACKLIGHT_FIOCTL_GET_POWER_LEVEL  	0x800F  /*!<  @deprecated This fioctl has been parsed as unused in our survey. It may not be supported in future releases of the SDK. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Get the power level @param unsigned int * : \ref BACKLIGHT_POWER_LEVEL_DEFAULT , \ref BACKLIGHT_POWER_LEVEL_LOW_01 @return \ref BACKLIGHTFIOCTL_ERR @note used to decrease the backlight consumption when other hight consumption functions are ON; cless for ex */

#define BACKLIGHT_FIOCTL_SET_TIME_DISPLAY	0x8010	/*!<  @deprecated This fioctl has been parsed as unused in our survey. It may not be supported in future releases of the SDK. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set the display backlight delay @param unsigned int * : 0 = infinity / unit is 10 ms @return \ref BACKLIGHTFIOCTL_ERR */	   
#define BACKLIGHT_FIOCTL_SET_TIME_KEYBOARD	0x8011	/*!<  @deprecated This fioctl has been parsed as unused in our survey. It may not be supported in future releases of the SDK. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Set the keyboard  delay @param unsigned int * : 0 = infinity / unit is 10 ms @note Only if \ref BACKLIGHT_AFF_SEPARE_BW @return \ref BACKLIGHTFIOCTL_ERR  */	 	   

#define BACKLIGHT_FIOCTL_START_DISPLAY		0x8013	/*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Start backlight Display @param NULL or \ref BACKLIGHT_PWM_PARAM_T* : if NULL, start the backlight with the previous level @return \ref BACKLIGHTFIOCTL_ERR  */
#define BACKLIGHT_FIOCTL_STOP_DISPLAY		0x8014	/*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Stop backlight Display @param NULL @return \ref BACKLIGHTFIOCTL_ERR  */ 	   

#define BACKLIGHT_FIOCTL_START_KEYBOARD		0x8015	/*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Start backlight Keyboard @param NULL or \ref BACKLIGHT_PWM_PARAM_T* : if NULL, start the backlight with the previous level @return \ref BACKLIGHTFIOCTL_ERR @note Only if \ref BACKLIGHT_AFF_SEPARE_BW  */
#define BACKLIGHT_FIOCTL_STOP_KEYBOARD		0x8016	/*!<  @deprecated You should use HWCNF_SetBacklightLevelEx API instead. To use this fioctl, you may define _DEPRECATED_BACKLIGHT_SDK96_. <br/> @brief.Stop backlight Keyboard @param NULL @return \ref BACKLIGHTFIOCTL_ERR @note Only if \ref BACKLIGHT_AFF_SEPARE_BW  */ 	   

//! @}

//! \addtogroup BACKLIGHTFIOCTL
//! @{ 


// parameters values :
#define BACKLIGHT_FIOCTL_ENABLE  BACKLIGHT_ENABLE		/*!< @deprecated replaced by \ref BACKLIGHT_ENABLE */
#define BACKLIGHT_FIOCTL_DISABLE BACKLIGHT_DISABLE		/*!< @deprecated replaced by \ref BACKLIGHT_DISABLE */


#define BACKLIGHT_ON      1								/*!< value for \ref BACKLIGHT_FIOCTL_GET_ONOFF_STATE : backlight is ON */
#define BACKLIGHT_OFF     0								/*!< value for \ref BACKLIGHT_FIOCTL_GET_ONOFF_STATE : backlight is OFF */

#define BACKLIGHT_FIOCTL_ON      BACKLIGHT_ON			/*!< @deprecated replaced by \ref BACKLIGHT_ON */
#define BACKLIGHT_FIOCTL_OFF     BACKLIGHT_OFF			/*!< @deprecated replaced by \ref BACKLIGHT_OFF  */

// parameters values :
#define BACKLIGHT_KEYBOARD_ENABLE  0					/*!< value for \ref BACKLIGHT_FIOCTL_SET_KEYBOARD_STATE : enable the keyboard backlight */
#define BACKLIGHT_KEYBOARD_DISABLE 1					/*!< value for \ref BACKLIGHT_FIOCTL_SET_KEYBOARD_STATE : disable the keyboard backlight */
#define BACKLIGHT_KEYBOARD_FIOCTL_ENABLE  BACKLIGHT_KEYBOARD_ENABLE			/*!< @deprecated  replaced by \ref BACKLIGHT_KEYBOARD_ENABLE */
#define BACKLIGHT_KEYBOARD_FIOCTL_DISABLE BACKLIGHT_KEYBOARD_DISABLE		/*!< @deprecated  replaced by \ref BACKLIGHT_KEYBOARD_DISABLE*/


//Field "Type" from BACKLIGHT_INFO_T 
#define BACKLIGHT_STANDART_BW    0      				/*!< value for \ref BACKLIGHT_FIOCTL_GET_TYPE fioctl : Single Backlight, one color.  */
#define BACKLIGHT_AFF_SEPARE_BW  1        				/*!< value for \ref BACKLIGHT_FIOCTL_GET_TYPE fioctl : Keyboard and Display backlight apart, one color*/
#define BACKLIGHT_3LED_RGB       2        				/*!< value for \ref BACKLIGHT_FIOCTL_GET_TYPE fioctl : Display backlight RGB (3 colored leds) */


// parameters values :
#define BACKLIGHT_POWER_LEVEL_DEFAULT 	0				/*!< value for \ref BACKLIGHT_FIOCTL_SET_POWER_LEVEL and \ref BACKLIGHT_FIOCTL_GET_POWER_LEVEL : default mode with user parameters */
#define BACKLIGHT_POWER_LEVEL_LOW_01 	1				/*!< value for \ref BACKLIGHT_FIOCTL_SET_POWER_LEVEL and \ref BACKLIGHT_FIOCTL_GET_POWER_LEVEL : low consumption if necessary, backlight level adjusted*/

//! @}


//! \addtogroup BACKLIGHTFIOCTL
//! @{ 

/*
======================================================================
					List of Structure
======================================================================
*/

/*! @brief Parameters of display/keyboard backlight */
typedef struct {
   unsigned char      cmd;				/*!< cmd parameter : \ref BACKLIGHT_CMD_OFF / \ref BACKLIGHT_CMD_ON */
   unsigned char      value;   /*!< value : in percent (0 to 100%) */
}BACKLIGHT_EXT_PARAM_T;

//! @}

#endif
#endif





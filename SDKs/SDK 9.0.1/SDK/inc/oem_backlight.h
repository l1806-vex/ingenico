/*! @addtogroup KSFAM_IOSF
* @{
 */ 

//! \defgroup BACKLIGHTFIOCTL Backlight
//! @{

	//! \defgroup BACKLIGHTFIOCTL_ERR Return Codes
	//! \defgroup BACKLIGHTFIOCTL_FIOCTL Fioctl
	
//! @}
 
/*! @}  */ 

#ifndef OEM_BACKLIGHT_H
#define OEM_BACKLIGHT_H


/*
======================================================================
					List of Defines
======================================================================
*/


//! \addtogroup BACKLIGHTFIOCTL_FIOCTL
//! @{ 

#define BACKLIGHT_FIOCTL_SET_TIME         	0x8000  /*!<  Set the timeout backlight delay @param unsigned int * : time before backlight off ; 0 = infinity / unit is 10 ms @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_SET_STATE        	0x8001  /*!<  Set the backlight state (enabled/disabled) @param unsigned int * : \ref BACKLIGHT_ENABLE = enable backlight / \ref BACKLIGHT_DISABLE = disable backlight @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_START            	0x8002  /*!<  Start backlight @param NULL or \ref BACKLIGHT_PWM_PARAM_T* : if NULL, start the backlight with the previous level @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_STOP             	0x8003  /*!<  Stop backlight @param NULL  */
#define BACKLIGHT_FIOCTL_GET_STATE       	0x8004  /*!<  Read backlight enable/disable state @param unsigned int *: \ref BACKLIGHT_ENABLE  , \ref BACKLIGHT_DISABLE @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_GET_ONOFF_STATE  	0x8005  /*!<  Read current backlight on/off state @param unsigned int *: \ref BACKLIGHT_FIOCTL_ON , \ref BACKLIGHT_FIOCTL_OFF @return \ref BACKLIGHTFIOCTL_ERR  */
#define BACKLIGHT_FIOCTL_GET_TYPE         	0x8006  /*!<  Get backlight type @param unsigned int * : @li \ref BACKLIGHT_STANDART_BW Single @li \ref BACKLIGHT_AFF_SEPARE_BW Dual (Display and Keyboard) @li \ref BACKLIGHT_3LED_RGB RGB @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_SET_RGB_PWM      	0x8007  /*!<  Set RGB pwm param @param BACKLIGHT_RGB_PARAM_T *  */
#define BACKLIGHT_FIOCTL_SET_DISPLAY     	0x8008  /*!<  Set only display backlight value @param BACKLIGHT_EXT_PARAM_T * level in % (0-100) @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_SET_KEYBOARD     	0x8009  /*!<  Set only keyboard backlight value @param BACKLIGHT_EXT_PARAM_T * level in % (0-100) @return \ref BACKLIGHTFIOCTL_ERR */

#define BACKLIGHT_FIOCTL_GET_DISPLAY      	0x800A  /*!<  Get the display backlight value @param unsigned int*  level in % (0-100) @return \ref BACKLIGHTFIOCTL_ERR  */
#define BACKLIGHT_FIOCTL_GET_KEYBOARD     	0x800B  /*!<  Get the keyboard backlight value @param unsigned int* level in % (0-100) @note Only if \ref BACKLIGHT_AFF_SEPARE_BW @return \ref BACKLIGHTFIOCTL_ERR   */

#define BACKLIGHT_FIOCTL_SET_KEYBOARD_STATE 0x800C  /*!<  Set the keyboard backlight state @param unsigned int* : \ref BACKLIGHT_KEYBOARD_ENABLE , \ref BACKLIGHT_KEYBOARD_DISABLE @return \ref BACKLIGHTFIOCTL_ERR @note Only if \ref BACKLIGHT_AFF_SEPARE_BW */
#define BACKLIGHT_FIOCTL_GET_KEYBOARD_STATE 0x800D 	/*!<  Get the current keyboard backlight status @param unsigned int* : \ref BACKLIGHT_KEYBOARD_ENABLE ,\ref BACKLIGHT_KEYBOARD_DISABLE @return \ref BACKLIGHTFIOCTL_ERR  @note Only if \ref BACKLIGHT_AFF_SEPARE_BW*/

#define BACKLIGHT_FIOCTL_SET_POWER_LEVEL  	0x800E	/*!<  Set the power level @param unsigned int * : \ref BACKLIGHT_POWER_LEVEL_DEFAULT , \ref BACKLIGHT_POWER_LEVEL_LOW_01 @return \ref BACKLIGHTFIOCTL_ERR @note used to decrease the backlight consumption when other hight consumption functions are ON; cless for ex */
#define BACKLIGHT_FIOCTL_GET_POWER_LEVEL  	0x800F  /*!<  Get the power level @param unsigned int * : \ref BACKLIGHT_POWER_LEVEL_DEFAULT , \ref BACKLIGHT_POWER_LEVEL_LOW_01 @return \ref BACKLIGHTFIOCTL_ERR @note used to decrease the backlight consumption when other hight consumption functions are ON; cless for ex */

#define BACKLIGHT_FIOCTL_SET_TIME_DISPLAY	0x8010	/*!<  Set the display backlight delay @param unsigned int * : 0 = infinity / unit is 10 ms @return \ref BACKLIGHTFIOCTL_ERR */	   
#define BACKLIGHT_FIOCTL_SET_TIME_KEYBOARD	0x8011	/*!<  Set the keyboard  delay @param unsigned int * : 0 = infinity / unit is 10 ms @note Only if \ref BACKLIGHT_AFF_SEPARE_BW @return \ref BACKLIGHTFIOCTL_ERR  */	 	   

#define BACKLIGHT_FIOCTL_START_DISPLAY		0x8013	/*!<  Start backlight Display @param NULL or \ref BACKLIGHT_PWM_PARAM_T* : if NULL, start the backlight with the previous level @return \ref BACKLIGHTFIOCTL_ERR  */
#define BACKLIGHT_FIOCTL_STOP_DISPLAY		0x8014	/*!<  Stop backlight Display @param NULL @return \ref BACKLIGHTFIOCTL_ERR  */ 	   

#define BACKLIGHT_FIOCTL_START_KEYBOARD		0x8015	/*!<  Start backlight Keyboard @param NULL or \ref BACKLIGHT_PWM_PARAM_T* : if NULL, start the backlight with the previous level @return \ref BACKLIGHTFIOCTL_ERR @note Only if \ref BACKLIGHT_AFF_SEPARE_BW  */
#define BACKLIGHT_FIOCTL_STOP_KEYBOARD		0x8016	/*!<  Stop backlight Keyboard @param NULL @return \ref BACKLIGHTFIOCTL_ERR @note Only if \ref BACKLIGHT_AFF_SEPARE_BW  */ 	   

//! @}

//! \addtogroup BACKLIGHTFIOCTL
//! @{ 


// parameters values :
#define BACKLIGHT_ENABLE  0								/*!< value for \ref BACKLIGHT_FIOCTL_SET_STATE fioctl : enable backlight @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_DISABLE 1								/*!< value for \ref BACKLIGHT_FIOCTL_SET_STATE fioctl : disable backlight @return \ref BACKLIGHTFIOCTL_ERR */
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


//Field "cmd" from BACKLIGHT_PWM_PARAM_T
#define BACKLIGHT_CMD_OFF        0        				/*!< value for cmd field of \ref BACKLIGHT_PWM_PARAM_T structure : switch off the led */
#define BACKLIGHT_CMD_ON         1       				/*!< value for cmd field of \ref BACKLIGHT_PWM_PARAM_T structure : switch on the led with the other values in the structure */

// parameters values :
#define BACKLIGHT_POWER_LEVEL_DEFAULT 	0				/*!< value for \ref BACKLIGHT_FIOCTL_SET_POWER_LEVEL and \ref BACKLIGHT_FIOCTL_GET_POWER_LEVEL : default mode with user parameters */
#define BACKLIGHT_POWER_LEVEL_LOW_01 	1				/*!< value for \ref BACKLIGHT_FIOCTL_SET_POWER_LEVEL and \ref BACKLIGHT_FIOCTL_GET_POWER_LEVEL : low consumption if necessary, backlight level adjusted*/

//! @}


//! \addtogroup BACKLIGHTFIOCTL_ERR
//! @{

// return values :
#define BACKLIGHT_OK				0					/*!< processing OK */
#define BACKLIGHT_ERR_BAD_CMD		(-1)				/*!< the command (fioctl) is unknown */
#define BACKLIGHT_ERR_BAD_PRM		(-2)				/*!< bad format or wrong parameters */
#define BACKLIGHT_ERR_NOT_SUPPORTED	(-3)				/*!< the requested command is not supported (Rgb cmd on B/W backlight for ex) */

//! @}

//! \addtogroup BACKLIGHTFIOCTL
//! @{ 

/*
======================================================================
					List of Structure
======================================================================
*/
/*! @brief Parameters of a pwm */
typedef struct {
   unsigned char      cmd;				/*!< cmd parameter : \ref BACKLIGHT_CMD_OFF / \ref BACKLIGHT_CMD_ON */
   unsigned char      diviseur;			/*!< divisor : 0 - 1 -2 - 3 - 4 */
   unsigned short int duree_high;		/*!< activation time (part of period) */
   unsigned short int duree_totale;		/*!< total time (period) */
}BACKLIGHT_PWM_PARAM_T;


/*! @brief Structure to set 3 rgb backlight leds */
typedef struct {
   BACKLIGHT_PWM_PARAM_T BluePwm;	/*!< Pwm parameters of blue led */
   BACKLIGHT_PWM_PARAM_T GreenPwm;	/*!< Pwm parameters of green led */
   BACKLIGHT_PWM_PARAM_T RedPwm;    /*!< Pwm parameters of red led */
}BACKLIGHT_RGB_PARAM_T;


/*! @brief Parameters of display/keyboard backlight */
typedef struct {
   unsigned char      cmd;				/*!< cmd parameter : \ref BACKLIGHT_CMD_OFF / \ref BACKLIGHT_CMD_ON */
   unsigned char      value;   /*!< value : in percent (0 to 100%) */
}BACKLIGHT_EXT_PARAM_T;

//! @}


#endif





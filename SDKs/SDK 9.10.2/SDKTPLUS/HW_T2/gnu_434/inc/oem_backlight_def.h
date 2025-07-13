#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_BACKLIGHT_DEF_H_INCLUDED__
#define __OEM_BACKLIGHT_DEF_H_INCLUDED__

/*! @addtogroup SYSTEMFIOCTL
* @{
 */ 

//! \defgroup BACKLIGHTFIOCTL Backlight
//! @{

	//! \defgroup BACKLIGHTFIOCTL_ERR Return Codes
	//! \defgroup BACKLIGHTFIOCTL_FIOCTL Fioctl
	
//! @}
 
/*! @}  */ 

//! \addtogroup BACKLIGHTFIOCTL_FIOCTL
//! @{ 

#define BACKLIGHT_FIOCTL_SET_STATE        	0x8001  /*!< @brief Set the backlight state (enabled/disabled) @param unsigned int * : \ref BACKLIGHT_ENABLE = enable backlight / \ref BACKLIGHT_DISABLE = disable backlight @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_FIOCTL_SET_RGB_PWM      	0x8007  /*!< @brief Set RGB pwm param @param BACKLIGHT_RGB_PARAM_T *  */

//! @}

//! \addtogroup BACKLIGHTFIOCTL
//! @{

#define BACKLIGHT_ENABLE  0								/*!< value for \ref BACKLIGHT_FIOCTL_SET_STATE fioctl : enable backlight @return \ref BACKLIGHTFIOCTL_ERR */
#define BACKLIGHT_DISABLE 1								/*!< value for \ref BACKLIGHT_FIOCTL_SET_STATE fioctl : disable backlight @return \ref BACKLIGHTFIOCTL_ERR */

//Field "cmd" from BACKLIGHT_PWM_PARAM_T
#define BACKLIGHT_CMD_OFF        0        				/*!< value for cmd field of \ref BACKLIGHT_PWM_PARAM_T structure : switch off the led */
#define BACKLIGHT_CMD_ON         1       				/*!< value for cmd field of \ref BACKLIGHT_PWM_PARAM_T structure : switch on the led with the other values in the structure */

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

//! @}

//! \addtogroup BACKLIGHTFIOCTL_ERR
//! @{

// return values :
#define BACKLIGHT_OK				0					/*!< processing OK */
#define BACKLIGHT_ERR_BAD_CMD		(-1)				/*!< the command (fioctl) is unknown */
#define BACKLIGHT_ERR_BAD_PRM		(-2)				/*!< bad format or wrong parameters */
#define BACKLIGHT_ERR_NOT_SUPPORTED	(-3)				/*!< the requested command is not supported (Rgb cmd on B/W backlight for ex) */

//! @}


#endif   // __OEM_BACKLIGHT_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif

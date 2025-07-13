/*! @addtogroup KSFAM_IOSF
	* @{
 */ 
 
#ifndef LEDS_CAD30VR_OEM_H
#define LEDS_CAD30VR_OEM_H

#ifdef _DEPRECATED_LEDSPERI_SDK96_
/*
======================================================================
					List of Defines
======================================================================
*/ 

// LEDS  number (1 Bit per LED) 
#define LED_1           (1)			/*!< Red led index for unattended Terminal*/
#define LED_2           (2)			/*!< Orange led index for unattended Terminal */
#define LED_3           (4)			/*!< Green led index for unattended Terminal */
//#define LED_4         (8)			/*!< Unused command */

// Returns oem 
#define LEDS_SUCCESS           0		/*!< ioctl successful*/
#define LEDS_NOT_IMPLEMENTED (-1)		/*!< ioctl not implemented */
#define LEDS_ERROR           (-2)		/*!< error occured during ioctl */


/*! @brief FIOCTL LEDS Data Structure  */
typedef struct
{
    unsigned char  NumLed;			/*!< Led number */
    unsigned char  TimeOn;			/*!< turn on time led command */
    unsigned char  TimeOff; 		/*!< turn off time led command */
    unsigned char  Ruf;					/*!< not used (Reserved for future use) */
}LEDS_FIOCTL_T;


// FIOCTL defines functions 
#define LEDS_FIOCTL_EXTERNAL      0x8100		/*!< External led ioctl base address */

#define LEDS_FIOCTL_CMD_STOP      (LEDS_FIOCTL_EXTERNAL+1)		/*!< @deprecated This fioctl has been parsed as unused. It will no longer be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_LEDSPERI_SDK96_ in your application. @brief stop leds */
#define LEDS_FIOCTL_CMD_START     (LEDS_FIOCTL_EXTERNAL+2)		/*!< @deprecated This fioctl has been parsed as unused. It will no longer be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_LEDSPERI_SDK96_ in your application. @brief start leds */
#define LEDS_FIOCTL_CMD_BLINK     (LEDS_FIOCTL_EXTERNAL+3)		/*!< @deprecated This fioctl has been parsed as unused. It will no longer be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_LEDSPERI_SDK96_ in your application. @brief blink leds */

#endif
#endif

/*! @}  */ 



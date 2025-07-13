/*! @addtogroup KSFAM_IOSF
	* @{
 */ 
 
#ifndef LEDS_C30_OEM_H
#define LEDS_C30_OEM_H
 
/*
======================================================================
					List of Defines
======================================================================
*/

// LEDS  number (1 Bit per LED) */
#define LED_C30_1           (1)		/*!< first LED */
#define LED_C30_2           (2)		/*!< second LED */
#define LED_C30_3           (4)		/*!< third LED */
#define LED_C30_4           (8)		/*!< fourth LED */

// Leds EVA for Vending Pass */
#define LED_EVA_RED         (16)	/*!< vending PASS red LED */
#define LED_EVA_ORANGE      (32)	/*!< vending PASS orange LED */
#define LED_EVA_GREEN       (64)	/*!< vending PASS green LED */

// Returns oem */
#define LEDS_C30_SUCCESS           0		/*!< ioctl successful */
#define LEDS_C30_NOT_IMPLEMENTED (-1)		/*!< ioctl not implemented */
#define LEDS_C30_ERROR           (-2)		/*!< error occured during ioctl */

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief FIOCTL LEDS C30 Data Structure */
typedef struct
{
    unsigned char  		NumLed;				/*!< LEDs to be configured with the following paramters */
    unsigned char  		TimeOn;				/*!< used by blink ioctl : time during LED is ON, unit : periodic task period */
    unsigned char  		TimeOff; 			/*!< used by blink ioctl : time during LED is OFF, unit : periodic task period */	
    unsigned char     Diviseur;				/*!< used by PWM ioctl : frequency dividor value */
    unsigned short    Duree_high;			/*!< used by PWM ioctl : activation time (part of period) */
    unsigned short    Duree_totale;		    /*!< used by PWM ioctl : total time (period) */
    unsigned char  		Ruf;						/*!< not used (Reserved for future use) */
}LEDS_C30_FIOCTL_T;


// FIOCTL defines functions */
#define LEDS_C30_FIOCTL_EXTERNAL      0x8100		/*!< led ioctl base address */

#define LEDS_C30_FIOCTL_CMD_STOP      (LEDS_C30_FIOCTL_EXTERNAL+1)		/*!< stop led */
#define LEDS_C30_FIOCTL_CMD_START     (LEDS_C30_FIOCTL_EXTERNAL+2)		/*!< start led */
#define LEDS_C30_FIOCTL_CMD_BLINK     (LEDS_C30_FIOCTL_EXTERNAL+3)		/*!< start blink led */
#define LEDS_C30_FIOCTL_CMD_PWM     	(LEDS_C30_FIOCTL_EXTERNAL+4)		/*!< start led using PWM */

#endif

/*! @}  */ 

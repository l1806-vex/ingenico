/*! @addtogroup KSFAM_IOSF
	* @{
 */ 
 
#ifndef LEDS_OEM_H
#define LEDS_OEM_H

/*
======================================================================
					List of Defines
======================================================================
*/

// LEDS  number (1 Bit per LED) */
#define LED_01		(0x01)		/*!< Led n° 1 C'Less (Green color)*/
#define LED_02		(0x02)		/*!< Led n° 2 C'Less (Green color)*/
#define LED_03		(0x04)		/*!< Led n° 3 C'Less (Green color) */
#define LED_04		(0x08)		/*!< Led n° 4 C'Less (Green color)*/
#define LED_05		(0x10)		/*!< Led n° 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)*/
#define LED_06		(0x20)		/*!< Led n° 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx)*/
#define LED_07		(0x40)		/*!< Led n° 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)*/
#define LED_08		(0x80)		/*!< Led n° 8 C'Less Logo (blue color on iST150)*/

// Returns oem */
#define LEDS_FIOCTL_SUCCESS					(0)			/*!< Return value if fioctl command is successful */
#define LEDS_FIOCTL_IOCTL_NOT_IMPLEMENTED	(-1)		/*!< Return value if fioctl command is unknown */
#define LEDS_FIOCTL_ERROR					(-2)		/*!< Return value if fioctl command is not successful */
#define LEDS_FIOCTL_NO_PARAM				(-3)		/*!< Return value if fioctl command is sent without parameters */
#define LEDS_FIOCTL_INVALID_PARAMETER		(-4)		/*!< Return value if fioctl command is sent with wrong parameters */

// for ISC350
#define LED_FIOCTL_MAG_LED1          LED_01			/*!< Magnetic card reader led 1 */
#define LED_FIOCTL_MAG_LED2          LED_02			/*!< Magnetic card reader led 2 */
#define LED_FIOCTL_MAG_LED3          LED_03			/*!< Magnetic card reader led 3 */
#define LED_FIOCTL_MAG_LED4          LED_04			/*!< Magnetic card reader led 4 */
#define LED_FIOCTL_MAG_LED5          LED_05			/*!< Magnetic card reader led 5 */
#define LED_FIOCTL_MAG_LED6          LED_06			/*!< Magnetic card reader led 6 */
#define LED_FIOCTL_SMC_LEDS          LED_07			/*!< Smart card reader led 7 */


#define LED_FIOCTL_EXT_CAM          LED_01			/*!< optional contact card reader led (available on IPP3xx only)*/
#define LED_FIOCTL_EXT_SWIPE        LED_02			/*!< optional Magnetic card reader led (available on IPP3xx only) */


/*
======================================================================
			Data Structures Definition
======================================================================
*/


/*! @brief FIOCTL LEDS Data Structure */
typedef struct
{
    unsigned char  NumLed;		/*!< LEDs to be configured */
    unsigned char  TimeOn;		/*!< time the led is on (used with blink command) */
    unsigned char  TimeOff; 	/*!< time the led is off (used with blink command) */
    unsigned char  Config;		/*!< (used on ISC350 only) define color of each leds (bit set to 0 => green, to 1 => red) */
}LEDS_DEFINITION;


// FIOCTL defines functions *
#define LEDS_XX_FIOCTL_EXTERNAL    0x8100		/*!< External led ioctl base address */

#define LEDS_XX_FIOCTL_CMD_STOP				( LEDS_XX_FIOCTL_EXTERNAL + 1 )		/*!< command to switch off the leds (Only C'Less leds on IPP3xx) */
#define LEDS_XX_FIOCTL_CMD_START			( LEDS_XX_FIOCTL_EXTERNAL + 2 )		/*!< command to switch on the leds (Only C'Less leds on IPP3xx) */
#define LEDS_XX_FIOCTL_CMD_BLINK			( LEDS_XX_FIOCTL_EXTERNAL + 3 )		/*!< command to make the leds blink (Only C'Less leds on IPP3xx) */
#define LEDS_XX_FIOCTL_CMD_FOR_USER			( LEDS_XX_FIOCTL_EXTERNAL + 4 )		/*!< command to set the leds in user mode (available for applications) */
#define LEDS_XX_FIOCTL_CMD_FOR_SYSTEM		( LEDS_XX_FIOCTL_EXTERNAL + 5 )		/*!< command to set the leds in system mode */
#define LEDS_XX_FIOCTL_MCR_LEFT_TO_RIGHT	( LEDS_XX_FIOCTL_EXTERNAL + 6 )		/*!< Magnetic carte reader left to right */
#define LEDS_XX_FIOCTL_MCR_RIGHT_TO_LEFT	( LEDS_XX_FIOCTL_EXTERNAL + 7 )		/*!< Magnetic carte reader right to left */
#define LEDS_XX_FIOCTL_CMD_STOP_EXT		    ( LEDS_XX_FIOCTL_EXTERNAL + 8 )		/*!< command to stop the leds other that C'less */
#define LEDS_XX_FIOCTL_CMD_START_EXT    	( LEDS_XX_FIOCTL_EXTERNAL + 9 )		/*!< command to start the leds other that C'less */



#endif

/*! @}  */ 


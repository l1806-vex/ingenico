/*! @addtogroup KSFAM_IOSF
	* @{
 */ 
 
#ifndef __RETRO_ECLAIRAGE_C30_OEM_H
#define __RETRO_ECLAIRAGE_C30_OEM_H
 
/*
======================================================================
					List of Defines
======================================================================
*/
// type de retroeclairage 
#define RETRO_ECLAIRAGE_C30_STANDARD    0     /*!< value for RETRO_ECLAIRAGE_C30_FIOCTL_CMD_GET_TYPE fioctl : standart backlight */
#define RETRO_ECLAIRAGE_C30_3LED_RGB    2     /*!< value for RETRO_ECLAIRAGE_C30_FIOCTL_CMD_GET_TYPE fioctl : display backlight RGB (3 colored leds) */

// Frequency Divisor Values  
#define DIVISEUR_0          (0) /*!< divide Frequency by 2    */
#define DIVISEUR_1          (1) /*!< divide Frequency by 8    */
#define DIVISEUR_2          (2) /*!< divide Frequency by 32   */
#define DIVISEUR_3          (3) /*!< divide Frequency by 128  */
#define DIVISEUR_4          (4) /*!< divide Frequency by 1024 */

// Returns oem 
#define RETRO_ECLAIRAGE_C30_SUCCESS           0		/*!< ioctl successful */
#define RETRO_ECLAIRAGE_C30_NOT_IMPLEMENTED (-1)	/*!< ioctl not implemented */
#define RETRO_ECLAIRAGE_C30_ERROR           (-2)	/*!< error occured during ioctl */

/*
======================================================================
			Data Structures Definition
======================================================================
*/

typedef struct
{
   unsigned char      diviseur;	    	/*!< frequency dividor value */
   unsigned char      ruf;				/*!< not used (Reserved for future use) */
   unsigned short int duree_high ;		/*!< activation time (part of period) */
   unsigned short int duree_totale; 	/*!< total time (period) */
}RETRO_ECLAIRAGE_C30_FIOCTL_T;		

/*! @brief Structure to set 3 rgb backlight leds */
typedef struct {
   RETRO_ECLAIRAGE_C30_FIOCTL_T BluePwm;	/*!< Pwm parameters of blue led */
   RETRO_ECLAIRAGE_C30_FIOCTL_T GreenPwm;	/*!< Pwm parameters of green led */
   RETRO_ECLAIRAGE_C30_FIOCTL_T RedPwm;    /*!< Pwm parameters of red led */
}RETRO_ECLAIRAGE_C30_RGB_FIOCTL_T;


// FIOCTL defines functions
#define RETRO_ECLAIRAGE_C30_FIOCTL_EXTERNAL      0x8300		/*!< backlight ioctl base address */

#define RETRO_ECLAIRAGE_C30_FIOCTL_CMD_STOP      (RETRO_ECLAIRAGE_C30_FIOCTL_EXTERNAL+1)		/*!< stop backlight */
#define RETRO_ECLAIRAGE_C30_FIOCTL_CMD_START     (RETRO_ECLAIRAGE_C30_FIOCTL_EXTERNAL+2)		/*!< start backlight */
#define RETRO_ECLAIRAGE_C30_FIOCTL_CMD_RGB       (RETRO_ECLAIRAGE_C30_FIOCTL_EXTERNAL+3)		/*!< set rgb backlight */
#define RETRO_ECLAIRAGE_C30_FIOCTL_CMD_GET_TYPE  (RETRO_ECLAIRAGE_C30_FIOCTL_EXTERNAL+4)		/*!< get backlight type*/

#endif

/*! @}  */ 


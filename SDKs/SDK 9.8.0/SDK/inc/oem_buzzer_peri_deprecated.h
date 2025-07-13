/*! @addtogroup KSFAM_IOSF
	* @{
 */ 
 
#ifndef __BUZZER_PERI_OEM_H
#define __BUZZER_PERI_OEM_H
 
#ifdef _DEPRECATED_OEM_BUZZERPERI_SDK96_
/*
======================================================================
					List of Defines
======================================================================
*/

// Frequency Divisor Values 
#define DIVISEUR_0          (0) /*!< MCK_2    */
#define DIVISEUR_1          (1) /*!< MCK_8    */
#define DIVISEUR_2          (2) /*!< MCK_32   */
#define DIVISEUR_3          (3) /*!< MCK_128  */
#define DIVISEUR_4          (4) /*!< MCK_1024 */


// Returns oem 
#define BUZZER_SUCCESS           0		/*!< ioctl successful */
#define BUZZER_NOT_IMPLEMENTED (-1)		/*!< ioctl not implemented */
#define BUZZER_ERROR           (-2)		/*!< error occured during ioctl */


/*
======================================================================
			Data Structures Definition
======================================================================
*/


/*! @brief BUZZER_FIOCTL_CMD_START and BUZZER_FIOCTL_CMD_STOP data structure */
typedef struct
{
   unsigned char      diviseur;				/*!< frequency dividor value */
   unsigned char      ruf;						/*!< not used (Reserved for future use) */
   unsigned short int duree_high ;		/*!<activation time (part of period) */
   unsigned short int duree_totale; 	/*!< total time (period) */
}BUZZER_FIOCTL_T;

/*! @brief BUZZER_FIOCTL_CMD_CONFIGURE_BEEP_ON_PIN_ENTRY data structure */
typedef struct
{
   unsigned char      diviseur;				/*!< frequency dividor value */
   unsigned char      ruf;						/*!< not used (Reserved for future use) */
   unsigned short int duree_high ;		/*!<activation time (part of period) */
   unsigned short int duree_totale; 	/*!< total time (period) */
   unsigned short int duree_beep; 	    /*!< time of beep (10ms) */
}BUZZER_FIOCTL_BEEP_ON_PIN_ENTRY_T;


// FIOCTL defines functions 
#define BUZZER_FIOCTL_EXTERNAL       0x8200												/*!< External buzzer ioctl base address */

#define BUZZER_FIOCTL_CMD_STOP      (BUZZER_FIOCTL_EXTERNAL+1)		/*!< @deprecated This fioctl has been parsed as unused by applications. It may not be supported in future releases of the SDK. You can use it by defining _DEPRECATED_OEM_BUZZERPERI_SDK96_ in your application. @brief stop buzzer (use BUZZER_FIOCTL_T parameter).   */
#define BUZZER_FIOCTL_CMD_START     (BUZZER_FIOCTL_EXTERNAL+2)		/*!< @deprecated This fioctl has been parsed as unused by applications. It may not be supported in future releases of the SDK. You can use it by defining _DEPRECATED_OEM_BUZZERPERI_SDK96_ in your application. @brief start buzzer (use BUZZER_FIOCTL_T parameter) . */
#define BUZZER_FIOCTL_CMD_CONFIGURE_BEEP_ON_PIN_ENTRY     (BUZZER_FIOCTL_EXTERNAL+3)		/*!< @deprecated This fioctl has been parsed as unused by applications. It may not be supported in future releases of the SDK. You can use it by defining _DEPRECATED_OEM_BUZZERPERI_SDK96_ in your application. @brief configure buzzer on pin entry. only for IWL350 (use BUZZER_FIOCTL_BEEP_ON_PIN_ENTRY_T parameter).*/

#endif
#endif

/*! @}  */ 


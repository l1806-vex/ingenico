#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_POWER_H_INCLUDED__
#define __OEM_POWER_H_INCLUDED__

#include "oem_power_def.h"
#ifdef __FRAMEWORK_TELIUM_2__
#include "oem_power_deprecated.h"
#endif

/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Describe a lowerpower bitmap. */
typedef struct pwr_fioctl_lowpwr_screen_t{
  unsigned int   length;							/*!< length of bitmap in bytes */
  unsigned char *bitmap;							/*!< lowpower bitmap  */
}pwr_fioctl_lowpwr_screen_t;

/*! @brief Structre to use with fioctl PWR_FIOCTL_ENTER_LOWPWR */
typedef struct PWR_ACTIVITY{
  char activity[32];             /*!< current activities */
}PWR_ACTIVITY;


/*
======================================================================
					List of Defines
======================================================================
*/



#define PWR_FIOCTL_GET_CHARGER_STATE            0x8002        /*!< param unsigned int : Get charger state */


#define PWR_FIOCTL_GET_BATTERY_TYPE             0x8004        /*!< param unsigned int : Get battery type */

#define PWR_FIOCTL_GET_BATTERY_LEVEL            0x8005        /*!< param unsigned int : Get battery average level */


#define PWR_FIOCTL_GET_TEMPERATURE              0x800F        /*!< param unsigned int : Get temperature K */


#define PWR_FIOCTL_GET_CC_CHARG_COUNTER         0x8011        /*!< param unsigned int : Get Coulomb counter Charg counter  */


#define PWR_FIOCTL_GET_USB_CHARGER_PARAM        0x8014        /*!< param unsigned int : Get USB charger param (enable/disable) */

#define PWR_FIOCTL_SET_USB_CHARGER_PARAM        0x8015        /*!< param unsigned int : Set USB charger param (enable/disable) */


#define PWR_FIOCTL_SET_LOWPWR_SCREEN            0x8018        /*!< param pwr_fioctl_lowpwr_screen Set low power screen.
                                                                   Length : size in bytesBitmap : 1 pixel per bit, vertical bytes, left to right, then top to bottom */

#define PWR_FIOCTL_ENTER_PWRDWN                 0x8019        /*!< no parameter : Put terminal in power down mode */


#define PWR_FIOCTL_ACTIVITY_START               0x8023        /*!< no parameter : Start application periodic activity */
#define PWR_FIOCTL_ACTIVITY_STOP                0x8024        /*!< no parameter : Stop application periodic activity */


#define PWR_FIOCTL_GET_USB_PRES_STATE           0x8030        /*!< param unsigned int : USB_PRES state */

#define PWR_FIOCTL_GET_USB_CHARG_STATE          0x8031        /*!< param unsigned int : USB charger 1000 mA state */


#define PWR_FIOCTL_GET_BASE_PRES_STATE          0x8034        /*!< param unsigned int : base pres state */


#define PWR_FIOCTL_GET_VBAT                     0x8039        /*!< param unsigned int : Get Vbat value in mV */

// parameters values :


//   PWR_FIOCTL_GET_BATTERY_TYPE
#define PWR_FIOCTL_BATTERY_TYPE_NONE 0		/*!< value for PWR_FIOCTL_GET_BATTERY_TYPE : no battery */
#define PWR_FIOCTL_BATTERY_TYPE_LION 1		/*!< value for PWR_FIOCTL_GET_BATTERY_TYPE : Li-Ion battery */
#define PWR_FIOCTL_BATTERY_TYPE_NIMH 2		/*!< value for PWR_FIOCTL_GET_BATTERY_TYPE : Ni-Mh battery */

//   PWR_FIOCTL_SET_USB_CHARGER_PARAM
#define PWR_FIOCTL_USB_CHARGER_PARAM_ON   1		/*!< value for PWR_FIOCTL_SET_USB_CHARGER_PARAM : USB charger is enabled */
#define PWR_FIOCTL_USB_CHARGER_PARAM_OFF  0		/*!< value for PWR_FIOCTL_SET_USB_CHARGER_PARAM : USB charger is disabled */



#define PWR_OK	0						/*!< OK  */
#define PWR_ERR_NOT_IMPLEMENTED (-1)	/*!< not implemented */
#define PWR_ERR_NOT_SUPPORTED (-2)		/*!< not supported */
#define PWR_ERR_BAD_PARAMETER (-3)		/*!< bad parameter */

/*! @}  */ 


#endif   // __OEM_POWER_H_INCLUDED__

#ifdef __cplusplus
}
#endif

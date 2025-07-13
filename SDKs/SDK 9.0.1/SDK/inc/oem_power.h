/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_POWER_H
#define OEM_POWER_H

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Describe a lowerpower bitmap. */
// @GSIM_T:pwr_fioctl_lowpwr_screen_t:DATA_CODE(sizeof(int) + length)  
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

#define PWR_FIOCTL_SET_WD_PWRDWN                0x8000        /*!< param unsigned int : Set watchdog power down */
#define PWR_FIOCTL_SET_WD_LOWPWR                0x8001        /*!< param unsigned int : Set watchdog low power 32KHz */
#define PWR_FIOCTL_GET_CHARGER_STATE            0x8002        /*!< param unsigned int : Get charger state */
#define PWR_FIOCTL_GET_POWER_STATE              0x8003        /*!< param unsigned int : Get main power current 0, 500, 1000 */
#define PWR_FIOCTL_GET_BATTERY_TYPE             0x8004        /*!< param unsigned int : Get battery type */
#define PWR_FIOCTL_GET_BATTERY_LEVEL            0x8005        /*!< param unsigned int : Get battery average level */
#define PWR_FIOCTL_GET_BATTERY_MIN_LEVEL        0x8006        /*!< param unsigned int : Get battery min level */
#define PWR_FIOCTL_GET_BATTERY_MAX_LEVEL        0x8007        /*!< param unsigned int : Get battery max level */
#define PWR_FIOCTL_SET_BATTERY_MIN_LEVEL        0x8008        /*!< param unsigned int : Set battery min level */
#define PWR_FIOCTL_SET_BATTERY_MAX_LEVEL        0x8009        /*!< param unsigned int : Set battery max level */
#define PWR_FIOCTL_SET_BATTERY_LEVEL            0x800A        /*!< param unsigned int : Set battery level min and max to same value */
#define PWR_FIOCTL_DEBUG_ON                     0x800B        /*!< no param           : Start debugger (battery informations diplay on LCD) */
#define PWR_FIOCTL_DEBUG_OFF                    0x800C        /*!< no param           : Stop debugger (battery informations diplay on LCD) */
#define PWR_FIOCTL_GET_AVERAGE_CURRENT          0x800E        /*!< param unsigned int : Get average current */
#define PWR_FIOCTL_GET_TEMPERATURE              0x800F        /*!< param unsigned int : Get temperature K */
#define PWR_FIOCTL_GET_FIQ_COUNTER              0x8010        /*!< param unsigned int : Get FIQ counter */
#define PWR_FIOCTL_GET_CC_CHARG_COUNTER         0x8011        /*!< param unsigned int : Get Coulomb counter Charg counter  */
#define PWR_FIOCTL_GET_CC_DISCHARG_COUNTER      0x8012        /*!< param unsigned int : Get Coulomb counter DisCharg counter  */
#define PWR_FIOCTL_GET_CC_SELF_DISCHARG_COUNTER 0x8013        /*!< param unsigned int : Get Coulomb counter Self disCharg counter  */
#define PWR_FIOCTL_GET_USB_CHARGER_PARAM        0x8014        /*!< param unsigned int : Get USB charger param (enable/disable) */
#define PWR_FIOCTL_SET_USB_CHARGER_PARAM        0x8015        /*!< param unsigned int : Set USB charger param (enable/disable) */
#define PWR_FIOCTL_SET_CHARGER_STATE            0x8016        /*!< param unsigned int : Set charger param (enable/disable) */
#define PWR_FIOCTL_GET_SERVICE                  0x8017        /*!< param unsigned int : Get service state (full limited) */
#define PWR_FIOCTL_SET_LOWPWR_SCREEN            0x8018        /*!< param pwr_fioctl_lowpwr_screen Set low power screen.
                                                                   Length : size in bytesBitmap : 1 pixel per bit, vertical bytes, left to right, then top to bottom */
#define PWR_FIOCTL_ENTER_PWRDWN                 0x8019        /*!< no parameter : Put terminal in power down mode */
#define PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM        0x8020        /*!< param unsigned int : Set Tilt wake-up (enable/disable) */
#define PWR_FIOCTL_GET_EXT_WAKEUP1_COUNTER      0x8022        /*!< param unsigned int : Tilt IRQ counter */
#define PWR_FIOCTL_ACTIVITY_START               0x8023        /*!< no parameter : Start application periodic activity */
#define PWR_FIOCTL_ACTIVITY_STOP                0x8024        /*!< no parameter : Stop application periodic activity */
#define PWR_FIOCTL_UPDATE                       0x8025        /*!< no parameter : imediatly update consumption counters */
#define PWR_FIOCTL_GET_USB_PRES_STATE           0x8030        /*!< param unsigned int : USB_PRES state */
#define PWR_FIOCTL_GET_USB_CHARG_STATE          0x8031        /*!< param unsigned int : USB charger 1000 mA state */
#define PWR_FIOCTL_GET_CHARGE_POWON_STATE       0x8033        /*!< param unsigned int : charger powon state */
#define PWR_FIOCTL_GET_BASE_PRES_STATE          0x8034        /*!< param unsigned int : base pres state */
#define PWR_FIOCTL_DEBUG_ENABLE                 0x8035        /*!< no parameter       : Enable debugger */
#define PWR_FIOCTL_DEBUG_DISABLE                0x8036        /*!< no parameter       : Diable debugger */
#define PWR_FIOCTL_SET_LOWPWR_COLOR_SCREEN      0x8037        /*!< param DISPLAY_BITMAP_COLOR_FILM_FIOCTL structure (oem_display.h) : Set low power color screen. */
#define PWR_FIOCTL_SET_VBAT_UPDATE_PERIOD       0x8038        /*!< param unsigned int : Set Vbat update period. unit is 10 ms from 1=10ms to 256=2560 ms */
#define PWR_FIOCTL_GET_VBAT                     0x8039        /*!< param unsigned int : Get Vbat value in mV */
#define PWR_FIOCTL_PARTNER_CHARGER_REQ          0x803F        /*!< param unsignet int : Defines if the charger is assigned to partner */
#define PWR_FIOCTL_ENERGY_CLAIM                 0x8040        /*!< param unsignet int : Defines if energy is supplied to partner */
#define PWR_FIOCTL_GET_IO_STATE                 0x8041        /*!< param unsignet int : Get Power and USB I/O state */
#define PWR_FIOCTL_GET_LIGHT_UPDATE_PERIOD      0x8042        /*!< param unsignet int : Get light update period. unit is 10 ms - 0 = stoped - 0xFFFFFFFF = test mode - all other value = 5s for now */
#define PWR_FIOCTL_SET_LIGHT_UPDATE_PERIOD      0x8043        /*!< param unsignet int : Set light update period. unit is 10 ms - 0 = stoped - 0xFFFFFFFF = test mode - all other value = 5s for now */
#define PWR_FIOCTL_GET_LIGHT                    0x8044        /*!< param unsignet int : Get Light value in Lux */
#define PWR_FIOCTL_IS_BACKLIGHT_WAKEUP_SUPPORTED 0x8045       /*!< param unsignet int : Is the backlight wakeup supported ? NULL=YES -2=NO */
#define PWR_FIOCTL_IS_LOWPWR_SUPPORTED          0x8046        /*!< param unsignet int : Is the low power mode supported ? NULL=YES -2=NO */
#define PWR_FIOCTL_SET_LOWPWR_STATE             0x8047        /*!< param unsigned int : Enable or disable lowpower */
#define PWR_FIOCTL_GET_LOWPWR_STATE             0x8048        /*!< param unsigned int : Get the lowpower state (enable/disable) */
#define PWR_FIOCTL_ENTER_LOWPWR                 0x8049        /*!< param PWR_ACTIVITY : Put terminal in low power mode synchronously
                                                                   fioctl returns -2 if low power is not suypported
                                                                   fioctl returns -3 after 3 s if low power is not allowed by an active device (PRINTER, ...) 
                                                                                     see string in PWR_ACTIVITY to now the current activity */
#define PWR_FIOCTL_SET_TEMP_INPUT_CURRENT       0x804A        /*!< param unsigned int : 500mA or 1000mA for 5 sec */
// parameters values :

//   PWR_FIOCTL_GET_CHARGER_STATE
#define PWR_FIOCTL_CHARGER_STATE_OFF 0 		/*!< value for PWR_FIOCTL_GET_CHARGER_STATE : charger is OFF */
#define PWR_FIOCTL_CHARGER_STATE_ON  1		/*!< value for PWR_FIOCTL_GET_CHARGER_STATE : charger is ON */

//   PWR_FIOCTL_GET_BATTERY_TYPE
#define PWR_FIOCTL_BATTERY_TYPE_NONE 0		/*!< value for PWR_FIOCTL_GET_BATTERY_TYPE : no battery */
#define PWR_FIOCTL_BATTERY_TYPE_LION 1		/*!< value for PWR_FIOCTL_GET_BATTERY_TYPE : Li-Ion battery */
#define PWR_FIOCTL_BATTERY_TYPE_NIMH 2		/*!< value for PWR_FIOCTL_GET_BATTERY_TYPE : Ni-Mh battery */

//   PWR_FIOCTL_SET_USB_CHARGER_PARAM
#define PWR_FIOCTL_USB_CHARGER_PARAM_ON   1		/*!< value for PWR_FIOCTL_SET_USB_CHARGER_PARAM : USB charger is enabled */
#define PWR_FIOCTL_USB_CHARGER_PARAM_OFF  0		/*!< value for PWR_FIOCTL_SET_USB_CHARGER_PARAM : USB charger is disabled */

//   PWR_FIOCTL_GET_SERVICE
#define PWR_FIOCTL_SERVICE_FULL           0		/*!< value for PWR_FIOCTL_GET_SERVICE : full service */
#define PWR_FIOCTL_SERVICE_LIMITED        1		/*!< value for PWR_FIOCTL_GET_SERVICE : limited service */

//   PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM      	
#define PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM_ON  1		/*!< value for PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM : enable external wakeup source 1 - Tilt */
#define PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM_OFF 0		/*!< value for PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM : disable external wakeup source 1 - Tilt */

//  PWR_FIOCTL_GET_IO_STATE
#define PWR_FIOCTL_GET_IO_STATE_ISPM_SW_USB_SEL   (1<<0)  /*!< value mask for PWR_FIOCTL_GET_IO_STATE : ISPM_SW_USB_SEL is on */
#define PWR_FIOCTL_GET_IO_STATE_ISPM_VBAT_PW      (1<<1)  /*!< value mask for PWR_FIOCTL_GET_IO_STATE : ISPM_VBAT_PW is on */

// PWR_FIOCTL_SET_LOWPWR_STATE / PWR_FIOCTL_GET_LOWPWR_STATE
#define PWR_LOWPWR_STATE_ON		  		 		1		/*!< value for PWR_FIOCTL_GET_CHARGER_STATE or PWR_FIOCTL_SET_LOWPWR_STATE : lowpower is enabled */
#define PWR_LOWPWR_STATE_OFF  					0		/*!< value for PWR_FIOCTL_GET_CHARGER_STATE or PWR_FIOCTL_SET_LOWPWR_STATE : lowpower is disabled */

// PWR_FIOCTL_SET_500MA / PWR_FIOCTL_SET_1000MA
#define PWR_FIOCTL_SET_500MA		  		 	500		/*!< value for PWR_FIOCTL_SET_TEMP_INPUT_CURRENT : 500 mA is forced for 5 sec */
#define PWR_FIOCTL_SET_1000MA		  		 	1000		/*!< value for PWR_FIOCTL_SET_TEMP_INPUT_CURRENT : 1000 mA is forced for 5 sec */

#endif

/*! @}  */ 




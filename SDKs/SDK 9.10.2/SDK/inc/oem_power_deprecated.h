/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_POWER_DEPRECATED_H
#define OEM_POWER_DEPRECATED_H


#ifdef _DEPRECATED_POWER_SDK96_


/*
======================================================================
					List of Defines
======================================================================
*/

#define PWR_FIOCTL_SET_WD_PWRDWN                0x8000        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set watchdog power down */
#define PWR_FIOCTL_SET_WD_LOWPWR                0x8001        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set watchdog low power 32KHz */
#define PWR_FIOCTL_GET_POWER_STATE              0x8003        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get main power current 0, 500, 1000 */
#define PWR_FIOCTL_GET_BATTERY_MIN_LEVEL        0x8006        /*!< @deprecated You should not call directly this fioctl. Use Get_battery_level API instead. @brief param unsigned int : Get battery min level */
#define PWR_FIOCTL_GET_BATTERY_MAX_LEVEL        0x8007        /*!< @deprecated You should not call directly this fioctl. Use Get_battery_level API instead. @brief param unsigned int : Get battery max level */
#define PWR_FIOCTL_SET_BATTERY_MIN_LEVEL        0x8008        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set battery min level */
#define PWR_FIOCTL_SET_BATTERY_MAX_LEVEL        0x8009        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set battery max level */
#define PWR_FIOCTL_SET_BATTERY_LEVEL            0x800A        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set battery level min and max to same value */
#define PWR_FIOCTL_DEBUG_ON                     0x800B        /*!< @deprecated You should not call directly this fioctl. Create a debug window for the battery with GOAL. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no param           : Start debugger (battery informations diplay on LCD) */
#define PWR_FIOCTL_DEBUG_OFF                    0x800C        /*!< @deprecated You should not call directly this fioctl. Create a debug window for the battery with GOAL. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no param           : Stop debugger (battery informations diplay on LCD) */
#define PWR_FIOCTL_GET_AVERAGE_CURRENT          0x800E        /*!< @deprecated You should not call directly this fioctl. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get average current */
#define PWR_FIOCTL_GET_FIQ_COUNTER              0x8010        /*!< @deprecated You should not call directly this fioctl. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get FIQ counter */
#define PWR_FIOCTL_GET_CC_DISCHARG_COUNTER      0x8012        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get Coulomb counter DisCharg counter  */
#define PWR_FIOCTL_GET_CC_SELF_DISCHARG_COUNTER 0x8013        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get Coulomb counter Self disCharg counter  */
#define PWR_FIOCTL_SET_CHARGER_STATE            0x8016        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set charger param (enable/disable) */
#define PWR_FIOCTL_GET_SERVICE                  0x8017        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get service state (full limited) */
#define PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM        0x8020        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set Tilt wake-up (enable/disable) */
#define PWR_FIOCTL_GET_EXT_WAKEUP1_COUNTER      0x8022        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Tilt IRQ counter */
#define PWR_FIOCTL_UPDATE                       0x8025        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no parameter : imediatly update consumption counters */
#define PWR_FIOCTL_GET_CHARGE_POWON_STATE       0x8033        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : charger powon state */
#define PWR_FIOCTL_DEBUG_ENABLE                 0x8035        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no parameter       : Enable debugger */
#define PWR_FIOCTL_DEBUG_DISABLE                0x8036        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no parameter       : Diable debugger */
#define PWR_FIOCTL_SET_LOWPWR_COLOR_SCREEN      0x8037        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param DISPLAY_BITMAP_COLOR_FILM_FIOCTL structure (oem_display.h) : Set low power color screen. */
#define PWR_FIOCTL_SET_VBAT_UPDATE_PERIOD       0x8038        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Set Vbat update period. unit is 10 ms from 1=10ms to 256=2560 ms */
#define PWR_FIOCTL_PARTNER_CHARGER_REQ          0x803F        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Defines if the charger is assigned to partner */
#define PWR_FIOCTL_ENERGY_CLAIM                 0x8040        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Defines if energy is supplied to partner */
#define PWR_FIOCTL_GET_IO_STATE                 0x8041        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Get Power and USB I/O state */
#define PWR_FIOCTL_GET_LIGHT_UPDATE_PERIOD      0x8042        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Get light update period. unit is 10 ms - 0 = stoped - 0xFFFFFFFF = test mode - all other value = 5s for now */
#define PWR_FIOCTL_SET_LIGHT_UPDATE_PERIOD      0x8043        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Set light update period. unit is 10 ms - 0 = stoped - 0xFFFFFFFF = test mode - all other value = 5s for now */
#define PWR_FIOCTL_GET_LIGHT                    0x8044        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Get Light value in Lux */
#define PWR_FIOCTL_IS_BACKLIGHT_WAKEUP_SUPPORTED 0x8045       /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no parameter : Is the backlight wakeup supported ? NULL=YES -2=NO */
#define PWR_FIOCTL_IS_LOWPWR_SUPPORTED          0x8046        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief no parameter : Is the low power mode supported ? 0=YES -2=NO */
#define PWR_FIOCTL_SET_LOWPWR_STATE             0x8047        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Enable or disable lowpower */
#define PWR_FIOCTL_GET_LOWPWR_STATE             0x8048        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get the lowpower state (enable/disable) */
#define PWR_FIOCTL_ENTER_LOWPWR                 0x8049        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. 
                                                                   @brief  param PWR_ACTIVITY : Put terminal in low power mode synchronously
                                                                   fioctl returns -2 if low power is not suypported
                                                                   fioctl returns -3 after 3 s if low power is not allowed by an active device (PRINTER, ...) 
                                                                                     see string in PWR_ACTIVITY to now the current activity */
#define PWR_FIOCTL_SET_TEMP_INPUT_CURRENT       0x804A        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : 500mA or 1000mA for 5 sec */

#define PWR_FIOCTL_SET_PWRDWN_THRESHOLD         0x804B        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. 
                                                                   @brief param unsigned int : battery level form 0 to 100
                                                                   This function is used to specify a battery level below which terminal enters power down mode instead of low power mode.
                                                                   Default value is 5 : terminal shutdowns if battery level is below 5 %
                                                                   0 means terminal never shutdown. It always goes in low power mode whatever is battery level
                                                                   100 means terminal always shutdowns and never uses low power mode whatever is battery level
                                                              */

#define PWR_FIOCTL_IS_LOWPWR_ON_CRADLE_SUPPORTED  0x804C        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int : Is the low power mode on cradle supported ? 0=YES -2=NO */

#define PWR_FIOCTL_SET_LOWPWR_ON_CRADLE_STATE     0x804E        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Enable or disable lowpower on cradle (iWL only)*/

#define PWR_FIOCTL_GET_LOWPWR_ON_CRADLE_STATE     0x804F        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsigned int : Get the lowpower on cradle state (iWL only). */


#define PWR_FIOCTL_GET_AAM_VOLTAGE              0x8050        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. 
                                                                   @brief param unsigned int : ISMP only permit to read Cless antenna voltage
                                                                   in factory process */

#define PWR_FIOCTL_IS_SHUTDOWN_MODE_SUPPORTED  	  0x8051     /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_POWER_SDK96_ in your application. @brief param unsignet int nMode*/
#define PWR_FIOCTL_SET_SHUTDOWN_MODE		      0x8052    /*!< param unsignet int nMode */
#define PWR_FIOCTL_GET_SHUTDOWN_MODE		    	  0x8053    /*!< no parameter , returns PWR_SHUTDOWN_MODE_AUTOMATIC or PWR_SHUTDOWN_MODE_MANUAL*/


// parameters values :


//   PWR_FIOCTL_GET_SERVICE
#define PWR_FIOCTL_SERVICE_FULL           0		/*!< @deprecated value for PWR_FIOCTL_GET_SERVICE : full service */
#define PWR_FIOCTL_SERVICE_LIMITED        1		/*!< @deprecated value for PWR_FIOCTL_GET_SERVICE : limited service */

//   PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM      	
#define PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM_ON  1		/*!< @deprecated value for PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM : enable external wakeup source 1 - Tilt */
#define PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM_OFF 0		/*!< @deprecated value for PWR_FIOCTL_SET_EXT_WAKEUP1_PARAM : disable external wakeup source 1 - Tilt */

//  PWR_FIOCTL_GET_IO_STATE
#define PWR_FIOCTL_GET_IO_STATE_ISPM_SW_USB_SEL   (1<<0)  /*!< @deprecated value mask for PWR_FIOCTL_GET_IO_STATE : ISPM_SW_USB_SEL is on */
#define PWR_FIOCTL_GET_IO_STATE_ISPM_VBAT_PW      (1<<1)  /*!< @deprecated value mask for PWR_FIOCTL_GET_IO_STATE : ISPM_VBAT_PW is on */

// PWR_FIOCTL_SET_LOWPWR_STATE / PWR_FIOCTL_GET_LOWPWR_STATE / PWR_FIOCTL_SET_LOWPWR_ON_CRADLE_STATE / PWR_FIOCTL_GET_LOWPWR_ON_CRADLE_STATE
#define PWR_LOWPWR_STATE_ON		  		 		1		/*!< @deprecated value for \ref PWR_FIOCTL_GET_CHARGER_STATE , \ref PWR_FIOCTL_SET_LOWPWR_STATE , \ref PWR_FIOCTL_SET_LOWPWR_ON_CRADLE_STATE and \ref PWR_FIOCTL_GET_LOWPWR_ON_CRADLE_STATE  : lowpower is enabled */
#define PWR_LOWPWR_STATE_OFF  					0		/*!< @deprecated value for \ref PWR_FIOCTL_GET_CHARGER_STATE , \ref PWR_FIOCTL_SET_LOWPWR_STATE , \ref PWR_FIOCTL_SET_LOWPWR_ON_CRADLE_STATE and \ref PWR_FIOCTL_GET_LOWPWR_ON_CRADLE_STATE : lowpower is disabled */

// PWR_FIOCTL_SET_500MA / PWR_FIOCTL_SET_1000MA
#define PWR_FIOCTL_SET_500MA		  		 	500		/*!< @deprecated value for PWR_FIOCTL_SET_TEMP_INPUT_CURRENT : 500 mA is forced for 5 sec */
#define PWR_FIOCTL_SET_1000MA		  		 	1000		/*!< @deprecated value for PWR_FIOCTL_SET_TEMP_INPUT_CURRENT : 1000 mA is forced for 5 sec */

//   PWR_FIOCTL_SET_SHUTDOWN_MODE // PWR_FIOCTL_GET_SHUTDOWN_MODE // PWR_FIOCTL_IS_SHUTDOWN_MODE_SUPPORTED
#define PWR_SHUTDOWN_MODE_AUTOMATIC 1					/*!< @deprecated automatic shutdown enabled  . value for PWR_FIOCTL_SET_SHUTDOWN_MODE // PWR_FIOCTL_IS_SHUTDOWN_MODE_SUPPORTED */
#define PWR_SHUTDOWN_MODE_MANUAL	2					/*!< @deprecated automatic shutdown disabled . value for PWR_FIOCTL_SET_SHUTDOWN_MODE // PWR_FIOCTL_IS_SHUTDOWN_MODE_SUPPORTED */

#endif

#endif  //OEM_POWER_DEPRECATED_H

/*! @}  */ 




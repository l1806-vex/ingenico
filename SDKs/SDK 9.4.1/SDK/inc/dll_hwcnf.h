#ifndef __DLL_HWCNF_H_INCLUDED__
#define __DLL_HWCNF_H_INCLUDED__

/*! @addtogroup KSFAM_HWCNF
* @{
**/   

//! \defgroup HWCNF_ENERGY	Energy Save Management
//! @{
		//! \defgroup HWCNF_ENERGY_ERR Energy Save return codes
		//! \defgroup HWCNF_ENERGY_MODE List of Energy Save Modes
		//! \defgroup HWCNF_ENERGY_PARAM_ID Energy save Parameters Id
		//! \defgroup HWCNF_ENERGY_MR40 Energy Management on CAD30UCR 	
//! @}


//! \defgroup HWCNF_BACKLIGHT Backlight Management
//! @{
		//! \defgroup HWCNF_BACKLIGHT_ERR Backlight return codes
		//! \defgroup HWCNF_BACKLIGHT_DEVICES Backlight device
		//! \defgroup HWCNF_BACKLIGHT_TARGET Backlight target
//! @}



//! \defgroup HWCNF_ETHERNET Ethernet Parameters

//! \defgroup HWCNF_BLUETOOTH_PRINTER External Bluetooth Printer

//! \defgroup HWCNF_BATTERY Battery Management


//! \brief Pop up the Hardware Configuration Top Level Menu, equivalent to F->Manager->Initialization->Hardware
//! \par exit None
//! \note @li DISPLAY, KEYBOARD shall be closed before call.
//! @li PRINTER should be closed if any impression is required.
//! \return void
// \if SIMULATION
//  @GSIM_F:HWCNF_Configure:KSFAM_HWCNF:
// \endif

extern void HWCNF_Configure(void);

/*! @} **/


//! @addtogroup HWCNF_BATTERY
//! @{

/*!
 * @brief Pop up Deep Discharging utility.
 * @param exit_key : the code for the key to interrupt deep discharging (for example T_ANN).
 * @return values in
 * @li 0 -  DISCHARGE_COMPLETE
 * @li 1 -  DISCHARGE_ERROR
 * @li 2 -  DISCHARGE_BATTERY_NOT_AVAILABLE
 * @li 3 -  DISCHARGE_BATTERY_NOT_COMPATIBLE
 * @li 4 -  DISCHARGE_PRINTER_NOT_AVAILABLE
 * @li 5 -  DISCHARGE_KEYBOARD_NOT_AVAILABLE
 * @li 6 -  DISCHARGE_USER_ABORTED
 * @li 7 -  DISCHARGE_TERMINAL_NOT_ON_CRADLE
 * @li 8 -  DISCHARGE_PRINTER_NOT_SUPPORTED
 * @li 9 -  DISCHARGE_DISPLAY_NOT_AVAILABLE
 * @par exit None
 * @note equivalent to F->Telium Manager->Initialization->Hardware->Battery->Deep Discharging
 * @note @li DISPLAY, KEYBOARD shall be closed before call.
 * @li PRINTER should be closed if any impression is required.
// \if SIMULATION
//  @GSIM_F:HWCNF_DeepDischarging:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_DeepDischarging(int exit_key);

//! @}

//! @addtogroup HWCNF_BACKLIGHT_ERR
//! @{

#define HWNCNF_BACKLIGHT_OK				0			/*!< OK  */
#define HWNCNF_BACKLIGHT_ERR_BAD_PARAM		(-1)	/*!< Bad parameter */
#define HWNCNF_BACKLIGHT_ERR_NOT_SUPPORTED	(-2)	/*!< The backlight management is not supported*/
#define HWNCNF_BACKLIGHT_ERR_DISABLED		(-3)	/*!< The backlight management is disabled. Set the energy save mode \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT to enable it*/

//! @}



//! @addtogroup HWCNF_BACKLIGHT_DEVICES
//! @brief Allow to specify only one device when there are several devices connected (pinpad, cless etc)
//! @{

//nDevice
#define BACKLIGHT_DEVICE_ALL			(0)	//!< All devices : Backlight on Terminal, pinpad, cless ... 

#define BACKLIGHT_DEVICE_TERMINAL		(1) //!< The backlight(s) of the terminal 

#define BACKLIGHT_DEVICE_PINPAD			(2) //!< The backlight(s) of the pinpad 

#define BACKLIGHT_DEVICE_CLESS_READER	(3) //!< The backlight(s) of the cless reader (!! not available yet !!)

#define BACKLIGHT_DEVICE_READER			(4) //!< The backlight(s) of the reader (Unattended only - iUN)

//! @}

//! @addtogroup HWCNF_BACKLIGHT_TARGET
//! @brief Allow to specify only one target when the device owns several backlight (keyboard, display...)
//! @{

//nTarget
#define BACKLIGHT_TARGET_ALL			(0)	//!< All backlight of the devices (keyboard, display)

#define BACKLIGHT_TARGET_DISPLAY		(1) //!< The main backlight (if single backlight) or the display backlight (if dual backlight - hardware features)

#define BACKLIGHT_TARGET_KEYBOARD		(2) //!< The backlight of the keyboard (Dual backlight only - hardware features) : iPP3xx for ex.

#define BACKLIGHT_TARGET_READER_SLOT	(3)	//!< The backlight of the reader slot (Unattended only - iUN)

//! @}


//! @addtogroup HWCNF_BACKLIGHT
//! @{

/*!
 * @brief Set the backlight intensity
 * @return The current setting for the backlight intensity, in the range [0x00000001 (FULL backlight) .. 0x0000FFFF (NO Backlight)]
 * @note Same value as modified by F->Telium Manager->Initialization->Hardware->Display->Back Light
// \if SIMULATION
//  @GSIM_F:HWCNF_GetBacklightIntensity:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_GetBacklightIntensity(void);

/*!
 * @brief set the backlight intensity with values in the range [0x0001 (FULL backlight) .. 0xFFFF (NO Backlight)]
 * @param intensity : the backlight intensity in the range [0x0001 (FULL backlight) .. 0xFFFF (NO Backlight)]
 * @note @li Same value as modified by F->Telium Manager->Initialization->Hardware->Display->Back Light
 * @li To set level in percent, use \ref HWCNF_SetBacklightLevelEx ( BACKLIGHT_DEVICE_ALL , BACKLIGHT_TARGET_ALL, level ).
// \if SIMULATION
//  @GSIM_F:HWCNF_SetBacklightIntensity:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_SetBacklightIntensity(unsigned short intensity);

/*!
 * @brief Get backlight duration
 * @return the backlight duration in second
 * @par exit None
 * @note Same value as @li F->Telium Manager->Initialization->Hardware->Display->backlight Duration 
 * @li or F->Telium Manager->Initialization->Hardware->Energy save->Light standby 
 * @li or F->Telium Manager->Initialization->Hardware->Energy save->Backight  
// \if SIMULATION
//  @GSIM_F:HWCNF_GetBacklightDuration:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_GetBacklightDuration(void);

/*!
 * @brief Set backlight duration.
 * @param duration : delay (in seconds) before automatic backlight shutdown (min 10s, max 120s)
 * @return the new backlight duration in second (may be limited to a maximum possible value).
 * @par exit None
 * @note Same value as @li F->Telium Manager->Initialization->Hardware->Display->backlight Duration 
 *  @li or F->Telium Manager->Initialization->Hardware->Energy save->Light standby 
 *  @li or F->Telium Manager->Initialization->Hardware->Energy save->Backight 
 * @note To modify the delay of one device or target, use \ref HWCNF_SetBacklightLevelEx.
 * @note Only for Wireless terminal, iCT2xx, iPP3xx, iSC250 and iSC350 (if the energy save mode is ENERGYSAVE_MODE_BACKLIGHT or ENERGYSAVE_MODE_LIGHT). 
// \if SIMULATION
//  @GSIM_F:HWCNF_SetBacklightDuration:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_SetBacklightDuration(int duration);

/*!
 * @brief Get the backlight level (percent)
 * @note Only if the energy save mode is \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT.
 * @param nDevice : \ref HWCNF_BACKLIGHT_DEVICES ...
 * @param nTarget : \ref HWCNF_BACKLIGHT_TARGET ...
 * @return level (percent)  or \ref HWCNF_BACKLIGHT_ERR.
 */
extern int HWCNF_GetBacklightLevelEx(unsigned int nDevice,unsigned int nTarget);

/*!
 * @brief Set the backlight level (percent)
 * @note Only if the energy save mode is \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT.
 * @param nDevice : specify the \ref HWCNF_BACKLIGHT_DEVICES ... (use \ref BACKLIGHT_DEVICE_ALL to modify all backlight devices)
 * @param nTarget : specify the \ref HWCNF_BACKLIGHT_TARGET ...	(use \ref BACKLIGHT_TARGET_ALL to modify all backlight targets)
 * @param nPercent : level (percent)
 * @return level (percent) or \ref HWCNF_BACKLIGHT_ERR.
 */
extern int HWCNF_SetBacklightLevelEx(unsigned int nDevice,unsigned int nTarget, unsigned int nPercent);

/*!
 * @brief Get the backlight delay
 * @note Only if the energy save mode is \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT
 * @param nDevice : \ref HWCNF_BACKLIGHT_DEVICES ...
 * @param nTarget : \ref HWCNF_BACKLIGHT_TARGET ...
 * @return delay in seconds (>0)  or \ref HWCNF_BACKLIGHT_ERR.
 */
extern int HWCNF_GetBacklightDelayEx(unsigned int nDevice,unsigned int nTarget);

/*!
 * @brief Set the backlight delay
 * @note Only if the energy save mode is \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT.
 * @param nDevice : specify the \ref HWCNF_BACKLIGHT_DEVICES ... (use \ref BACKLIGHT_DEVICE_ALL to modify all backlight devices)
 * @param nTarget : specify the \ref HWCNF_BACKLIGHT_TARGET ...	(use \ref BACKLIGHT_TARGET_ALL to modify all backlight targets)
 * @param nDuration_sec : delay in second (min 10s, max 120s)
 * @return delay in seconds (>0) or \ref HWCNF_BACKLIGHT_ERR.
 */
extern int HWCNF_SetBacklightDelayEx(unsigned int nDevice,unsigned int nTarget, int nDuration_sec);


/*!
 * @brief Restore and update the backlight from the user settings (delay and level)
 * @note Only if the energy save mode is \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT.
 * @param nDevice : \ref HWCNF_BACKLIGHT_DEVICES ...
 * @param nTarget : \ref HWCNF_BACKLIGHT_TARGET ...
 */
void HWCNF_UpdateBacklightEx(unsigned int nDevice,unsigned int nTarget);

/*!
 * @brief Is the specified backlight available ?
 * @param nDevice : \ref HWCNF_BACKLIGHT_DEVICES ...
 * @param nTarget : \ref HWCNF_BACKLIGHT_TARGET ...
 * @return @li TRUE The specified backlight is available
 * @li FALSE The specified backlight is not available
 */
extern int HWCNF_IsBacklightAvailable(unsigned int nDevice,unsigned int nTarget);

//! @}

//! @addtogroup HWCNF_ENERGY_MODE
//! @{

#define ENERGYSAVE_MODE_NONE  					(0)		/*!< No energy save mode (Standby and backlight delay disabled). @note not supported by the wireless terminals.*/

#define ENERGYSAVE_MODE_BACKLIGHT 				(1)		/*!< Backlight timeout enabled. The backight delay is set by \ref HWCNF_SetBacklightDelayEx. Wake up if key pressed. @note iCTxx, iPP3xx, iSC250, iSC350 only*/

#define ENERGYSAVE_MODE_LIGHT 					(2)		/*!< Thunder frozen and Booster standby. Backlight timeout is enabled too. 
														@li The standby delay is set by \ref HWCNF_SetStandbyDelay.
														@li The backight delay is set by \ref HWCNF_SetBacklightDelayEx.
														
														@note @li iCTxx and Wireless terminals only.*/

//#define ENERGYSAVE_MODE_LIGHT_AND_CRADLE 		(0x12)	/*!< @deprecated. use \ref HWCNF_SetEnergySaveParameter.*/
					
																							
#define ENERGYSAVE_MODE_DEEP 					(3)		/*!< Thunder off and Booster deep standby @note unattended terminals only : CAD30UCR, IUN250, IUC180)  */

//! @}

//! @addtogroup HWCNF_ENERGY_ERR
//! @{

#define HWNCNF_ENERGYSAVE_OK				0			/*!< OK  */
#define HWNCNF_ENERGYSAVE_ERR_BAD_PARAM		(-1)	/*!< Bad parameter */
#define HWNCNF_ENERGYSAVE_ERR_NOT_SUPPORTED	(-2)	/*!< mode or function supported*/
#define HWNCNF_ENERGYSAVE_ERR_UNKNOWN_ID	(-3)	/*!< unknown param ID */
#define HWNCNF_ENERGYSAVE_ERR_NOT_IMPLEMENTED (-4)	/*!< not implemented (older dll)*/

//! @}



//! @addtogroup HWCNF_ENERGY_PARAM_ID
//! @{

#define ENERGYSAVE_ID_AUTOMATIC_SHUTDOWN  		(1)		/*!<Set or Get the automatic shutdown state.

															pData =  unsigned int * @li TRUE automatic shutdown enabled; @li FALSE automatic shutdown disabled.
															
															@note @li only supported by the IWL terminals (default mode=automic).
																@li The parameter is not saved. The application must call it at each startup (after_reset for ex).
																@li If the automatic shutdown is disabled, the standby delay input is not displayed in the hardware settings .
														*/

#define ENERGYSAVE_ID_LOWPOWER_ON_CRADLE		(2)		/*!<Lowpower mode if the terminal is on the cradle. Backlight timeout is enabled too.
															
															pData = unsigned int * @li TRUE lowpower on cradle enabled; @li FALSE lowpower on cradle.
															
															@note @li iWLxx terminals only
															@li The standby delay is set by \ref HWCNF_SetStandbyDelay.
															@li The backight delay is set by \ref HWCNF_SetBacklightDelayEx.
														*/

//! @}


//! @addtogroup HWCNF_ENERGY
//! @{

/*!
 * @brief Get the power save mode 
 * @return @li \ref ENERGYSAVE_MODE_NONE, @li \ref ENERGYSAVE_MODE_BACKLIGHT @li \ref ENERGYSAVE_MODE_LIGHT @li \ref ENERGYSAVE_MODE_DEEP.
 */
extern int HWCNF_GetEnergySaveMode(void);

/*!
 * @brief Set the power save mode 
 * @param mode : @li \ref ENERGYSAVE_MODE_NONE @li \ref ENERGYSAVE_MODE_BACKLIGHT @li \ref ENERGYSAVE_MODE_LIGHT @li \ref ENERGYSAVE_MODE_DEEP
 * @return @li the value of the mode set --> successful @li -1 Unknown mode @li -2 Mode supported by the terminal but disabled
 * @note Same value as F->Telium Manager->Initialization->Hardware->Energy save (available if at least 2 modes are supported)
 */
extern int HWCNF_SetEnergySaveMode(int mode);

/*!
 * @brief Is the energy save mode supported
 * @param mode : @li \ref ENERGYSAVE_MODE_NONE @li \ref ENERGYSAVE_MODE_BACKLIGHT @li \ref ENERGYSAVE_MODE_LIGHT @li \ref ENERGYSAVE_MODE_DEEP
 * @return TRUE / FALSE.
 */
extern int HWCNF_IsEnergySaveModeSupported(int mode);


/*!
 * @brief Set the energy save parameter
 * @param nParamId : \ref HWCNF_ENERGY_PARAM_ID
 * @param pData : pointer to data (refer to \ref HWCNF_ENERGY_PARAM_ID)
 * @return \ref HWNCNF_ENERGYSAVE_OK or \ref HWCNF_ENERGY_ERR.
 */
extern int HWCNF_SetEnergySaveParameter(unsigned int nParamId, void* pData);

/*!
 * @brief Get the energy save parameter
 * @param nParamId : \ref HWCNF_ENERGY_PARAM_ID
 * @param pData : pointer to data (refer to \ref HWCNF_ENERGY_PARAM_ID)
 * @return \ref HWNCNF_ENERGYSAVE_OK or \ref HWCNF_ENERGY_ERR.
 */
extern int HWCNF_GetEnergySaveParameter(unsigned int nParamId, void* pData);



/*!
 * @brief Get Standby delay
 * @return the standby delay in second
 * @par exit None
 * @note Same value as F->Telium Manager->Initialization->Hardware->Battery Setup->Standby Delay or  F->Telium Manager->Initialization->Hardware->Energy save->Light standby.
// \if SIMULATION
//  @GSIM_F:HWCNF_GetStandbyDelay:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_GetStandbyDelay(void);

/*!
 * @brief Set the Standby delay.
 *        minimum value 10s, no maximum value.
 * @param duration : delay (in seconds) before entering standby mode.
 * @return the new standby delay in seconds.
 * @par exit None
 * @note @li Same value as F->Telium Manager->Initialization->Hardware->Battery Setup->Standby Delay
 * @li Only on Wireless terminal and the terminals which support the energy save mode \ref ENERGYSAVE_MODE_LIGHT
// \if SIMULATION
//  @GSIM_F:HWCNF_SetStandbyDelay:KSFAM_HWCNF:
// \endif
 */
extern int HWCNF_SetStandbyDelay(int duration);

//! @}

//! @addtogroup HWCNF_ETHERNET
//! @{


//! \brief Define the structure to get dynamic Ethernet interface info. (total size 5 * 4)
typedef struct {
  unsigned int addr;    //!< IP address
  unsigned int netmask; //!< IP netmask
  unsigned int gateway; //!< Ethernet gateway IP address
  unsigned int dns1;    //!< First DNS IP address
  unsigned int dns2;    //!< Second DNS IP address
} ip_param_s;

/*!
 * @brief Obtain Mac Address both for Bluetooth and non-Bluetooth device, except Wifi.
 * @param mac_addr : pointer to an array of 6 char
 * @return @li 0 if parameters could be obtained. @li -1 else (parameter download failure).
 * @note @li Wifi interface parameter shall be retrieved using the Wifi DLL.
 * @li Bluetooth devices will try to get the configuration from the base, either by IR or BT.
// \if SIMULATION
//  @GSIM_F:HWCNF_EthernetGetMacAddress:KSFAM_HWCNF:
//  @GSIM_A:1:ONE_POINTER
// \endif
 */
extern int HWCNF_EthernetGetMacAddress(char *mac_addr);

/*!
 * @brief Obtain Ethernet setting, both for Bluetooth and non-Bluetooth device, except Wifi.
 * @param param : pointer to an ip_param_s that will hold the IP parameters on return.
 * @param display : if !=0, the progress of the base parameter download will be displayed.
 * @return @li 0 if parameters could be obtained. @li -1 else (parameter download failure).
 * @note @li Wifi interface parameter shall be retrieved using the Wifi DLL.
 * @li Bluetooth devices will try to get the configuration from the base, either by IR or BT.
// \if SIMULATION
//  @GSIM_F:HWCNF_EthernetGetCurrentParameters:KSFAM_HWCNF:
//  @GSIM_A:1:ONE_POINTER
// \endif
 */
extern int HWCNF_EthernetGetCurrentParameters(ip_param_s *param, int display);

//! @}

//! @addtogroup HWCNF_ENERGY_MR40
//! @{

/*!
 * @brief Get Standby delay for MR40
 * @return the standby delay in second
 * @par exit None
 * @note Same value as F->Telium Manager->Initialization->Hardware->Standby settings->Standby Delay
// \if SIMULATION
//  @GSIM_F:HWCNF_MR40GetStandbyDelay:KSFAM_HWCNF:
// \endif
 */
extern int  HWCNF_MR40GetStandbyDelay(void);

/*!
 * @brief Set Standby delay for MR40
 * @param delay : standby delay in seconds (max 900s)
 * @par exit None
 * @note Same value as F->Telium Manager->Initialization->Hardware->Standby settings->Standby Delay
// \if SIMULATION
//  @GSIM_F:HWCNF_MR40SetStandbyDelay:KSFAM_HWCNF:
// \endif
 */
extern void HWCNF_MR40SetStandbyDelay(unsigned short delay);

#define MR40_STANDBY_TYPE_NONE  (0)	//!< No standby
#define MR40_STANDBY_TYPE_LIGHT (1) //!< Thunder frozen and Booster standby
#define MR40_STANDBY_TYPE_DEEP  (2) //!< Thunder off and Booster deep standby

/*!
 * @brief Get Standby type for MR40
 * @deprecated only for compatibility. replaced by \ref HWCNF_GetStandbyDelay
 * @return the standby type, value @li \ref MR40_STANDBY_TYPE_NONE @li \ref MR40_STANDBY_TYPE_LIGHT @li \ref MR40_STANDBY_TYPE_DEEP
 * @par exit None
 * @note Same value as F->Telium Manager->Initialization->Hardware->Standby settings->Standby Type
// \if SIMULATION
//  @GSIM_F:HWCNF_MR40GetStandbType:KSFAM_HWCNF:
// \endif
 */
extern int  HWCNF_MR40GetStandbyType(void);

/*!
 * @brief Get Standby delay for MR40
 * @param type : the standby type, value in @li \ref MR40_STANDBY_TYPE_NONE @li \ref MR40_STANDBY_TYPE_LIGHT @li \ref MR40_STANDBY_TYPE_DEEP
 * @par exit None
 * @note Same value as F->Telium Manager->Initialization->Hardware->Standby settings->Standby Type
// \if SIMULATION
//  @GSIM_F:HWCNF_MR40SetStandbType:KSFAM_HWCNF:
// \endif
 */
extern void HWCNF_MR40SetStandbyType(int type);

//! @}

//! @addtogroup HWCNF_BATTERY
//! @{

/*!
 * @brief Signal battery was just changed
 * @param min_val : presumed battery level (in [0 .. 100])
 * @par exit None
 * @note Same effect as F->Telium Manager->Initialization->Hardware->Battery->New->yes
// \if SIMULATION
//  @GSIM_F:HWCNF_NewBattery:KSFAM_HWCNF:
// \endif
 */
extern void HWCNF_NewBattery(int min_val);

//! @}

//! @addtogroup HWCNF_BLUETOOTH_PRINTER
//! @{

#include "dbluetooth.h"

/*!
 * @brief Get the Bluetooth address of the external printer
 * @param addr the address of the bluetooth device 
 * @return NONE 
 * @note
// \if SIMULATION
//  @GSIM_F:HWCNF_GetExternalPrinterBluetoothAddress:KSFAM_HWCNF:
// \endif
 */
extern void HWCNF_GetExternalPrinterBluetoothAddress(dbluetooth_device_addr_s *addr);


//! @}

#endif // __DLL_HWCNF_H_INCLUDED__


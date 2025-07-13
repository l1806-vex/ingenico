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
//! @{
		//! \defgroup HWCNF_BLUETOOTH_PRINTER_ERR Bluetooth external printer error codes
		//! \defgroup HWCNF_BLUETOOTH_PRINTER_MENU_MODES Menu Modes
		//! \defgroup HWCNF_BLUETOOTH_PRINTER_STATUS Ext printer status (iSMP Only)
		//! \defgroup HWCNF_BLUETOOTH_PRINTER_KEEPALIVE Keep alive status
//! @}


//! \defgroup HWCNF_BATTERY Battery Management

//! \defgroup HWCNF_USBDEV USB Device Settings
	//! @{
	
	//! \defgroup HWCNF_USBDEV_MODES USB Device Modes
	//! \defgroup HWCNF_USBDEV_SN USB Device Serial Number Status
	//! \defgroup HWCNF_USBDEV_ERR USB Device return codes

	//! @}

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



//! @addtogroup HWCNF_BACKLIGHT_ERR
//! @{

#define HWCNF_BACKLIGHT_OK				0			/*!< OK  */
#define HWCNF_BACKLIGHT_ERR_BAD_PARAM		(-1)	/*!< Bad parameter */
#define HWCNF_BACKLIGHT_ERR_NOT_SUPPORTED	(-2)	/*!< The backlight management is not supported*/
#define HWCNF_BACKLIGHT_ERR_DISABLED		(-3)	/*!< The backlight management is disabled. Set the energy save mode \ref ENERGYSAVE_MODE_BACKLIGHT or \ref ENERGYSAVE_MODE_LIGHT to enable it*/

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
extern int HWCNF_SetBacklightDelayEx(unsigned int nDevice,unsigned int nTarget, unsigned int nDuration_sec);


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

#define HWCNF_ENERGYSAVE_OK				0				/*!< OK  */
#define HWCNF_ENERGYSAVE_ERR_BAD_PARAM		(-1)		/*!< Bad parameter */
#define HWCNF_ENERGYSAVE_ERR_NOT_SUPPORTED	(-2)		/*!< mode or function supported*/
#define HWCNF_ENERGYSAVE_ERR_UNKNOWN_ID	(-3)			/*!< unknown param ID */
#define HWCNF_ENERGYSAVE_ERR_NOT_IMPLEMENTED (-4)		/*!< not implemented (older dll)*/

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
 * @return \ref HWCNF_ENERGYSAVE_OK or \ref HWCNF_ENERGY_ERR.
 */
extern int HWCNF_SetEnergySaveParameter(unsigned int nParamId, void* pData);

/*!
 * @brief Get the energy save parameter
 * @param nParamId : \ref HWCNF_ENERGY_PARAM_ID
 * @param pData : pointer to data (refer to \ref HWCNF_ENERGY_PARAM_ID)
 * @return \ref HWCNF_ENERGYSAVE_OK or \ref HWCNF_ENERGY_ERR.
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


//! @addtogroup HWCNF_BLUETOOTH_PRINTER_ERR
//! @{

#define HWCNF_BTPRINTER_OK					0		/*!< OK  */
#define HWCNF_BTPRINTER_ERR_BAD_PARAM		(-1)	/*!< Bad parameter */
#define HWCNF_BTPRINTER_ERR_NOT_SUPPORTED	(-2)	/*!< The external bt printer management is not supported*/
#define HWCNF_BTPRINTER_ERR_DISABLED		(-3)	/*!< The external bt printer is disabled*/
#define HWCNF_BTPRINTER_ERR_NOT_IMPLEMENTED	(-4)	/*!< The dll needs to be updated*/
#define HWCNF_BTPRINTER_ERR_KEYBOARD		(-5)	/*!< keyboard must be closed before calling the function  */
#define HWCNF_BTPRINTER_ERR_DISPLAY			(-6)	/*!< display must be closed before calling the function  */
#define HWCNF_BTPRINTER_ERR_NOT_LOADED		(-9999)	/*!< dll not loaded*/	
//! @}

//! @addtogroup HWCNF_BLUETOOTH_PRINTER_MENU_MODES
//! @brief parameters of \ref HWCNF_ConfigureExternalPrinter (to display BT printer settings from an application )
//! @{

#define HWCNF_BTPRINTER_MENU_USER				0	//!< display the items discovery + information only
#define HWCNF_BTPRINTER_MENU_SUPERVISOR			1	//!< display all settings

//! @}

//! @addtogroup HWCNF_BLUETOOTH_PRINTER_STATUS
//! @brief parameters of \ref HWCNF_SetExternalPrinterBluetoothStatus
//! @{

#define HWCNF_BTPRINTER_ENABLED				1	//!< external BT printer enabled - iSPM only
#define HWCNF_BTPRINTER_DISABLED				0	//!< external BT printer disabled - iSPM only

//! @}


//! @addtogroup HWCNF_BLUETOOTH_PRINTER_KEEPALIVE
//! @brief parameters of \ref HWCNF_SetExternalPrinterBluetoothKeepalive
//! @{

#define HWCNF_BTPRINTER_KEEPALIVE_ON			1	//!< bluetooth keepalive on (quick open/close printer)
#define HWCNF_BTPRINTER_KEEPALIVE_OFF			0	//!< bluetooth keepalive off (bluetooth disconnected if printer driver closed)

//! @}


//! @addtogroup HWCNF_BLUETOOTH_PRINTER
//! @brief External printer settings (iSMP and iUC only)
//! @{

/*!
 * @brief Get the Bluetooth address of the external printer
 * @param addr the address of the bluetooth device 
 * @return NONE 
 * @note
*/
extern void HWCNF_GetExternalPrinterBluetoothAddress(dbluetooth_device_addr_s *addr);

/*!
 * @brief Get the Bluetooth address of the external printer
 * @param bt_string the address of the bluetooth device (string 20bytes with 0) -> "XXXX:XX:XXXXXX"
 * @return \ref HWCNF_BTPRINTER_OK	if successful else \ref HWCNF_BLUETOOTH_PRINTER_ERR
 * 
*/
extern int HWCNF_GetExternalPrinterBluetoothAddressString(char bt_string[20+1]);

/*!
 * @brief Set the Bluetooth address of the external printer
 * @param bt_string the address of the bluetooth device (string 20bytes with 0) -> "XXXX:XX:XXXXXX"
 * @return \ref HWCNF_BTPRINTER_OK	if successful else \ref HWCNF_BLUETOOTH_PRINTER_ERR
 * 
*/
extern int HWCNF_SetExternalPrinterBluetoothAddressString(char bt_string[20+1]);

/*!
 * @brief Set the status of the Bluetooth external printer
 * @param nStatus \ref HWCNF_BLUETOOTH_PRINTER_STATUS
 * @return \ref HWCNF_BTPRINTER_OK	if successful else \ref HWCNF_BLUETOOTH_PRINTER_ERR
 * @note iSMP only
*/
extern int HWCNF_SetExternalPrinterBluetoothStatus( int nStatus);

/*!
 * @brief Get the status of the Bluetooth external printer
 * @return \ref HWCNF_BLUETOOTH_PRINTER_STATUS if successful else \ref HWCNF_BLUETOOTH_PRINTER_ERR
 * @note iSMP only
 */
extern int HWCNF_GetExternalPrinterBluetoothStatus( void);

/*!
 * @brief Set the keepalive status of the Bluetooth external printer
 * @param nStatus : \ref HWCNF_BLUETOOTH_PRINTER_KEEPALIVE
 * @return \ref HWCNF_BTPRINTER_OK	if successful or \ref HWCNF_BLUETOOTH_PRINTER_ERR
 */
extern int HWCNF_SetExternalPrinterBluetoothKeepalive( int nStatus);

/*!
 * @brief Get the keepalive status of Bluetooth printer
 * @return \ref HWCNF_BLUETOOTH_PRINTER_KEEPALIVE if successful else \ref HWCNF_BLUETOOTH_PRINTER_ERR
 * @note iSMP only
*/
extern int HWCNF_GetExternalPrinterBluetoothKeepalive( void );

//! \brief Pop up the Hardware Configuration Top Level Menu, equivalent to F->Manager->Initialization->Hardware->BT Printer
//! @param nMode: \ref HWCNF_BLUETOOTH_PRINTER_MENU_MODES
//! @return \ref HWCNF_BTPRINTER_OK	if successful else \ref HWCNF_BLUETOOTH_PRINTER_ERR
//! \note @li DISPLAY, KEYBOARD, PRINTER shall be closed before call.
//! \return void
extern int HWCNF_ConfigureExternalPrinter(unsigned int nMode);


//! @}

//! @addtogroup HWCNF_USBDEV
//! @{

/*!
 * @brief Set the USB device Mode
 * @return \n \ref HWCNF_USBDEV_MODES (successful) or \ref HWCNF_USBDEV_ERR
 * @note The driver COM5 must be closed before calling this function
 */
extern int HWCNF_GetUSBDevMode(void);

/*!
 * @brief Get the USB device Mode
 * @param nMode int* \ref HWCNF_USBDEV_MODES
 * @return \n HWCNF_USBDEV_OK (successful) or \ref HWCNF_USBDEV_ERR
 * @note The driver COM5 must be closed before calling this function
 */
 extern int HWCNF_SetUSBDevMode(int nMode);

/*!
 * @brief Enable/Disable the USB Device Serial Number String
 * @param nStatus: \ref HWCNF_USBDEV_SN
 * @return \n HWCNF_USBDEV_OK (successful) or \ref HWCNF_USBDEV_ERR
 * @note The driver COM5 must be closed before calling this function
 */
extern int HWCNF_SetUSBDevSerialNumbStatus( int nStatus);


/*!
 * @brief Get the USB Device Serial Number String state
 * @return \n \ref HWCNF_USBDEV_SN (successful) or \ref HWCNF_USBDEV_ERR
 * @note The driver COM5 must be closed before calling this function
 */
extern int HWCNF_GetUSBDevSerialNumbStatus(void);

//! @}


//! @addtogroup HWCNF_USBDEV_MODES
//! @{

#define USBDEV_MODE_CDC_DEFAULT			0		/*!< default cdc mode : \ref USBDEV_MODE_CDC_LEGACY or \ref USBDEV_MODE_CDC ( manufacturer settings ). \warning USBDEV_MODE_CDC_DEFAULT is used to set the default mode but \ref HWCNF_GetUSBDevMode can't provide this value. */
#define USBDEV_MODE_CDC_LEGACY			1		/*!< CDC Legacy  : VID PID Telium.\note VID=0x079B PID=0x0028 */
#define USBDEV_MODE_CDC					2		/*!< CDC : proper VID PID<br>\note Mode supported by products Thunder II & III.<br>Values of VID PID: <br><br><table>
<tr><th>  Product  </th><th>  VID  </th><th>  PID  </th></tr>
<tr><td>iCT220</td><td>0x0B00</td><td>0x0066</td></tr>
<tr><td>iCT250</td><td>0x0B00</td><td>0x0066</td></tr>
<tr><td>iPP320</td><td>0x0B00</td><td>0x0060</td></tr>
<tr><td>iPP350</td><td>0x0B00</td><td>0x0060</td></tr>
<tr><td>iPP480</td><td>0x0B00</td><td>0x0060</td></tr>
<tr><td>iSC250</td><td>0x0B00</td><td>0x0062</td></tr>
<tr><td>iSC350</td><td>0x0B00</td><td>0x0061</td></tr>
<tr><td>iWL220</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>iWL250</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>iWL280</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>iWL350</td><td>0x0B00</td><td>0x0064</td></tr>
<tr><td>E532</td><td>0x0B00</td><td>0x0067</td></tr>
</table>*/

#define USBDEV_MODE_HID					3		/*!< HID mode 
\note This mode is supported by the products below.
<br><table>
<tr><th>Product</th><th>VID</th><th>PID</th></tr>
<tr><td>iPP320</td><td>0x0B00</td><td>0x0071</td></tr>
<tr><td>iPP350</td><td>0x0B00</td><td>0x0072</td></tr>
<tr><td>iPP480</td><td>0x0B00</td><td>0x0075</td></tr>
<tr><td>iSC250</td><td>0x0B00</td><td>0x0074</td></tr>
<tr><td>iSC350</td><td>0x0B00</td><td>0x0073</td></tr>
</table>
*/

#define USBDEV_MODE_CDC_SESAM_VITALE	4		/*!< French Health Care Sesam Vitale  */

//! @}

//! @addtogroup HWCNF_USBDEV_ERR
//! @{

#define HWCNF_USBDEV_OK					0		/*!< OK  */
#define HWCNF_USBDEV_ERR_BAD_PARAM			(-1)	/*!< Bad parameter */
#define HWCNF_USBDEV_ERR_NOT_SUPPORTED		(-2)	/*!< mode or function supported*/
#define HWCNF_USBDEV_ERR_COM5_UNAIVABLE	(-3)	/*!< COM5 is unavailable or already opened*/
#define HWCNF_USBDEV_ERR_NOT_IMPLEMENTED	(-4)	/*!< The dll needs to be updated*/
#define HWCNF_USBDEV_ERR_INTERNAL	(-99)			/*!< unknown */
#define HWCNF_USBDEV_ERR_NOT_LOADED		(-9999)	/*!< dll not loaded*/

//! @}

//! @addtogroup HWCNF_USBDEV_SN
//! @{

#define USBDEV_SERIAL_NUMB_DISABLED		0 /*!< Disabled  */
#define USBDEV_SERIAL_NUMB_ENABLED		1 /*!< Enabled - Serial numb string provided */

//! @}



#endif // __DLL_HWCNF_H_INCLUDED__


#ifdef __cplusplus
extern "C" {
#endif

#ifndef __DLL_HWCNF_DEPREATED_H_INCLUDED__
#define __DLL_HWCNF_DEPREATED_H_INCLUDED__

/*! @addtogroup KSFAM_HWCNF
* @{
**/   

//! @addtogroup HWCNF_ENERGY_MODE
//! @{
//#define ENERGYSAVE_MODE_LIGHT_AND_CRADLE 		(0x12)	/*!< @deprecated. use \ref HWCNF_SetEnergySaveParameter.*/
//! @}


//! @addtogroup HWCNF_BATTERY
//! @{

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Internal use only.
 *
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
 */
#ifndef _DEPRECATED_MANAGER_SDK980_
#define HWCNF_DeepDischarging ERROR_Deprecation_For_Function_HWCNF_DeepDischarging_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int HWCNF_DeepDischarging(int exit_key) MACRO_DEPRECATED;
#endif

//! @}

//! @addtogroup HWCNF_ENERGY_MR40
//! @{

/*!
 * @brief Get Standby type for MR40
 * @deprecated only for compatibility. replaced by \ref HWCNF_GetStandbyDelay
 * @return the standby type, value @li \ref MR40_STANDBY_TYPE_NONE @li \ref MR40_STANDBY_TYPE_LIGHT @li \ref MR40_STANDBY_TYPE_DEEP
 * @par exit None
 * @note Same value as F->Telium Manager->Initialization->Hardware->Standby settings->Standby Type
 */
#ifndef _DEPRECATED_MANAGER_SDK980_
#define HWCNF_MR40GetStandbyType ERROR_Deprecation_For_Function_HWCNF_MR40GetStandbyType_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int  HWCNF_MR40GetStandbyType(void) MACRO_DEPRECATED;
#endif
//! @}

//! @}



#endif // __DLL_HWCNF_DEPREATED_H_INCLUDED__

#ifdef __cplusplus
}
#endif

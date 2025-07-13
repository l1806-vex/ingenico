#ifndef __DLL_HWCNF_DEPREATED_H_INCLUDED__
#define __DLL_HWCNF_DEPREATED_H_INCLUDED__

/*! @addtogroup KSFAM_HWCNF
* @{
**/   

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
// \if SIMULATION
//  @GSIM_F:HWCNF_DeepDischarging:KSFAM_HWCNF:
// \endif
 */
#ifndef _DEPRECATED_MANAGER_SDK980_
#define HWCNF_DeepDischarging ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int HWCNF_DeepDischarging(int exit_key) MACRO_DEPRECATED;
#endif

//! @}

//! @}



#endif // __DLL_HWCNF_DEPREATED_H_INCLUDED__


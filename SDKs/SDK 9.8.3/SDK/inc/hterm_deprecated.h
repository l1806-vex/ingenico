/*! @addtogroup KSFAM_M2OS
	* @{
**/

#ifndef _HTERM_DEPRECATED_H
#define _HTERM_DEPRECATED_H


/*! 
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GetEthernetConfiguration API instead.
 *
 * @brief This function returns the MAC address of the terminal.
 * @param mac_addr : MAC address.
 * @return MAC Address
 *
 * @note 
 * Since the SDK 8.1.2,this function is no longer in EF30.LIB but in the DLL EXTENS.
 * When an application is generated with the SDK 8.1.2, it will only work correctly on a terminal loaded with the components of a SDK 8.1.2 or higher
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:GetMacAddress:KSFAM_M2OS:
//  \endif

#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetMacAddress ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          GetMacAddress(char * mac_addr) MACRO_DEPRECATED;
#endif


#endif
/*! @} **/

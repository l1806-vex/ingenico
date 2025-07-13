/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifndef _MANAGER_CONFIG_DEPRECATED_H
#define _MANAGER_CONFIG_DEPRECATED_H


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Some information might not be consistent.
 * 
 * @brief This function reads the state of the hardware.
 * @param Hterm : pointer to structure hterm_t
 * @return None 
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 35) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:lire_etat_materiel:KSFAM_AUTRES_MANAGER:0xB0
//  @GSIM_A:1:ONE_POINTER
// \endiff
#ifndef _DEPRECATED_MANAGER_SDK980_
#define lire_etat_materiel ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
void lire_etat_materiel(hterm_t *Hterm) MACRO_DEPRECATED;
#endif
#define _MANAGER_CONFIG_DEPRECATED_H


#endif
/*! @} **/

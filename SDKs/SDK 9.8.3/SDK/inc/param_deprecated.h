/*! @addtogroup KSFAM_PSQ
	* @{
**/
#ifndef PARAM_DEPRECATED_H
#define PARAM_DEPRECATED_H


/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use PSQ_GetPacksInfos function instead.
 *
 * @brief This function is used to get the Pack system informations
 * @param hPack : pointer to structure hPack_t.
 * @param ucTypeAppli : object type
 *		TYPE_LOG_PACK  =  for manager PACK
 *		OEM            =  for system PACK
 * @param FilePath : file path.
 * @param FileName : file name.
 * @return
 * - OK (0).
 * - KO (!= 0)
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 48) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:GetPackInfos:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetPackInfos ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern unsigned char GetPackInfos(hPack_t *hPack,unsigned short ucTypeAppli, char *FilePath, char *FileName) MACRO_DEPRECATED;
#endif


//param.h

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use the following functions instead:
 * -mode equip=>ITP French Domain
 * -no_log_seq=> object_get_info
 * -no_log_sys=> object_get_info
 * -va_log_sys=> Non renseigné
 * -no_serie => PSQ_Give_Serial_Number
 * -nb_cam => Is_CAM1,2,3
 * -nb_app_priv =>French domain only
 * -typ_archi => French domain only
 * -taille_mem_flash => Read State memory
 * -taille_mem_flash_rest => Read State memory
 * -taille_mem_ram => Read State memory
 * -taille_mem_ram_rest => Read State memory
 * -materiel_coupleur =>lire_info_terminal
 * -log_coupleur =>lire_info_terminal
 * -no_spec_coupleur= "200"
 *
 * @brief This function is used to get terminal hardware information needed for French Bank application .
 * @param p_equip : pointer to S_EQUIPEMENT structure ( see param .h .
 *
 *	May be used in other domains to get, for instance, more details about terminal type (EFT930 family),mod_equip[1] :
 * - 2 EFTSmart
 * - 3 EFT30
 * - 4 EFT30 Plus
 * - 5 Twin 30 or EFT930-W (Wifi)
 * - 6 EFT930 IR
 * - 7 EFT930G (GPRS)
 * - 8 EFT930 B (Blue-Tooth)
 * - 9 EFT930-S (Stationnary)
 *
 * @return None
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 30) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Donner_reference:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define PSQ_Donner_reference ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          PSQ_Donner_reference ( S_EQUIPEMENT * p_equip ) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Internal use only.
 *
 * @brief This routine returns informations recorded by applications on the entry point give_your_specific_context.
 * !!! Does not support more than 15 applications in the terminal.
 * @param paramout : pointer to S_ SPECIFIC_CONTEXT structure
 * @return None
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 78) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_give_specific_context:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define PSQ_give_specific_context ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          PSQ_give_specific_context(S_SPECIFIC_CONTEXT *paramout) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Internal use only.
 *
 * @brief This routine returns informations recorded by applications on the entry point give_your_specific_context.
 * @param paramout : pointer to S_SPECIFIC_CONTEXT_EXTENDED structure
 * @return None
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 96) if function does not exist
 * @note
 *  This routine manage NUMBER_OF_APPLI applications
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_give_specific_context_extended:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define PSQ_give_specific_context_extended ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          PSQ_give_specific_context_extended(S_SPECIFIC_CONTEXT_EXTENDED *paramout) MACRO_DEPRECATED;
#endif


#endif
/*! @} **/

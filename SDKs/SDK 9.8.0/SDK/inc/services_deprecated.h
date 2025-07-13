
#ifndef SERVICES_DEPRECATED_H
#define SERVICES_DEPRECATED_H

/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Internal use only.
 *
 * @brief  This function is used to get the header area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 227) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetScreenArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:4:OUT_ONLY
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetHeaderArea ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int GetHeaderArea(int *left,int *top,int *right,int *bottom) MACRO_DEPRECATED;
#endif

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Internal use only.
 *
 * @brief GetLedsSize read the Leds size (Software LEDS)
* @param Height : return the Leds Height.
* @param Width :  return the Leds Width.
* @return
* - 0= Leds is inactive
* - 1= Leds is active
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 233) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetLedsSize:KSFAM_LEDS:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetLedsSize ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int  GetLedsSize(int *Height,int *Width) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Internal use only.
 *
 * @brief This function is used to get the LEDS area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 227) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetLedsArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:4:OUT_ONLY
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetLedsArea ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int GetLedsArea(int *left,int *top,int *right,int *bottom) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Internal use only.
 *
 * @brief SetHeaderAreaBmp sets the bitmap of an area into header
* @param HeaderArea : Area Id
* - HEADER_GPRS_AREA
* - HEADER_BT_AREA
* - HEADER_WIFI_AREA
* - HEADER_NETWORK_AREA
* @param PtBmp : New bitmap for key.
* @par exit(EXIT_DLL_COLOR_NOT_INITIALIZED + 132) if function does not exist
 *
 *	@section Sample SetHeaderBMP

 * @include services_Sample_02.c
 *
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetHeaderAreaBmp:KSFAM_AUTRES_MANAGER:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SetHeaderAreaBmp ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void SetHeaderAreaBmp(int HeaderArea,char *PtBmp) MACRO_DEPRECATED;
#endif

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Internal use only.
 *
 * @brief This function is used to get the footer area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
* @return
* - 0= if no footer management
* - 1= if footer management
* @note Footer area is not supported on Monochrome terminals.
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetFooterArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetFooterArea ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int GetFooterArea(int *left,int *top,int *right,int *bottom) MACRO_DEPRECATED;
#endif

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use GOAL instead.
 *
 * @brief Display a choices selection.
* @param file : pointer on the screen's handle
* @param table : table of the choices
* @param name : name of the choices
* @param select : pointer on the selected choice
* @param choice: choice
* @param report : selection report.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 37) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Affichage_choix:KSFAM_VISU:
//  @GSIM_S:SLC_Affichage_choix:E_SLC_Affichage_choix
//  1:ONE_ADDRESS
//  3:DATA_SIZE(6)
//  4:DATA_SIZE(1)
//  5:DATA_SIZE(1)
//  6:DATA_SIZE(1)
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Affichage_choix ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Affichage_choix  (FILE *file, char **table, unsigned char *name, unsigned char *select, unsigned char *choice, unsigned char *report) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use GOAL instead.
 *
 * @brief Display a message on the screen.
* @param message : message to be displayed.
* @param option : * a r w
* - r, w : for read and write
* - * : force the opening
* - a : the screen is not cleaned
* @param flag : wait or not after display.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 38) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Afficher:KSFAM_VISU:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Afficher ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Afficher (char *message, char *option, unsigned char flag) MACRO_DEPRECATED;
#endif




/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use GOAL instead.
 *
 * @brief Display the amount.
* @param option : openning of the display peripheric
* @param amount (long): amount
* @param flag : forced to 1.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 39) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Afficher_montant:KSFAM_VISU:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Afficher_montant ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Afficher_montant (char          *option,MONTANT        amount,unsigned char  flag) MACRO_DEPRECATED;
#endif




/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use USQ_AddMinutes.
 *
 * @brief This function add N minutes to a date.
* @param increment : number of minutes to add
* @param date : date to set.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 40) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Ajoutermn:KSFAM_VISU:
//  @GSIM_A:2:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Ajoutermn ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Ajoutermn (unsigned int  increment,DATE *date) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use GOAL instead.
 *
 * @brief Clear the display
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 45) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Clear_display:KSFAM_USQ:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Clear_display ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Clear_display    (void) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use SLSQ_TimeGapInSeconds
 *
 * @brief Returns the number of days between date2 and date1.
* @param date1 : the first date
* @param date2 : the second date
* @return Number of days.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 46) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Ecart_date:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Ecart_date ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int           SLC_Ecart_date       (DATE *date1, DATE *date2) MACRO_DEPRECATED;
#endif




/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use SLSQ_TimeGapInSeconds
 *
 * @brief Returns the number of hour between date2 and date1.
* @param date1 : first date
* @param date2 : second date
* @return Number of minute.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 47) if function does not exist
 *
 * @note
 * The DATE Fields (day, month, year) have no effect on the result.
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Ecart_heure:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Ecart_heure ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int           SLC_Ecart_heure      (DATE *date1, DATE *date2) MACRO_DEPRECATED;
#endif




/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use GOAL instead.
 *
 * @brief Clear a line on the display
* @param ligne : number of the line (0 or 1)
* @param position : position of the cursor on this line
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 48) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Effacer_ligne:KSFAM_USQ:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Effacer_ligne ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Effacer_ligne    (int ligne, unsigned char position) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Use USQ_AddDays
 *
 * @brief Set the date to the next day.
* @param date : date to set.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 49) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Joursuivant:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Joursuivant ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void          SLC_Joursuivant      (DATE *date) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. EFT10 API deprecated. Internal use only.
 *
 * @brief State automaton.
* @param etat : begining state
* @param table : pointer to structure TAB_EV, wich describe the begining and the ending states.
* @param offset : offset on the first element of the automaton
* @return
* -255 when the automaton stops
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Moteur:KSFAM_VISU:
//  @GSIM_S:SLC_Moteur:E_SLC_Moteur
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLC_Moteur ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern short         SLC_Moteur           (short etat,TAB_EV *table,ADRESSE offset) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Use GOAL instead.
 *
 * @brief Display a message
* @param nomessage : identifier of the message.
* @return None.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 61) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Afficher_message:KSFAM_VISU:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLSQ_Afficher_message ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void           SLSQ_Afficher_message        (unsigned char nomessage) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Use GOAL instead.
 *
 * @brief Display a message without cleaning the screen before.
* @param nomessage : identifier of the message.
* @return None.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 62) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Afficher_message_ss_eff:KSFAM_VISU:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLSQ_Afficher_message_ss_eff ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void           SLSQ_Afficher_message_ss_eff (unsigned char nomessage) MACRO_DEPRECATED;
#endif


/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Use GOAL instead.
 *
 * @brief Manual entry of a card number.
* @param noporteur : the card number
* @param dateexp : expiration date.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 194) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Manual_entry:KSFAM_USQ:
//  @GSIM_A:1:DATA_SIZE(19)
//  @GSIM_A:2:DATA_SIZE(4)
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLSQ_Manual_entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern unsigned char  SLSQ_Manual_entry (unsigned char *noporteur,unsigned char *dateexp) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Use GOAL instead.
 *
 * @brief Display the version.
* @param version : buffer containing the version.
* @return None.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 63) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Afficher_bienvenue:KSFAM_VISU:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLSQ_Afficher_bienvenue ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void           SLSQ_Afficher_bienvenue      (T_VERSION version) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Use GOAL instead.
 *
 * @brief This function display the string : "monnaie refusee par LIBELLE".
* @param libelle : name of the application.
* @return None (void).
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 64) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Aff_pb_money:KSFAM_USQ:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLSQ_Aff_pb_money ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void           SLSQ_Aff_pb_money            (T_AFFNOM libelle) MACRO_DEPRECATED;
#endif



/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Internal use only.
 *
 * @brief Reset the terminal and gives an error code on the diagnostic ticket.
* @param numero : reset code.
* @return None (void).
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 65) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Exception:KSFAM_USQ:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define SLSQ_Exception ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void           SLSQ_Exception               (unsigned char numero) MACRO_DEPRECATED;
#endif


/*! @} **/




/*! @addtogroup KSFAM_CGUI
	* @{
**/
/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 * @brief GetCguiFileName return the file name of the manager CGUI resource
 * @param FileName : pointer to a string to store the name
 *
 * @return
 *   pointer to a string containing the name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note
// \if SIMULATION
//  @GSIM_F:GetCguiFileName:KSFAM_CGUI:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetCguiFileName ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern char          *GetCguiFileName(char *FileName) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief GetCguiPageList return the resource name for CGUI page list.
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note
// \if SIMULATION
//  @GSIM_F:GetCguiPageList:KSFAM_CGUI:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetCguiPageList ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern char          *GetCguiPageList(void) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief GetCguiPageFList return the resource name for CGUI page list.
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note
// \if SIMULATION
//  @GSIM_F:GetCguiPageFList:KSFAM_CGUI:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetCguiPageFList ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern char          *GetCguiPageFList(void) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief GetCguiPageNavi return the resource name for CGUI page navigation.
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note
// \if SIMULATION
//  @GSIM_F:GetCguiPageNavi:KSFAM_CGUI:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetCguiPageNavi ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern char          *GetCguiPageNavi(void) MACRO_DEPRECATED;
#endif


/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief GetCguiPathIcon return the path for the resource icon in a CGUI icon list or a list entry.
 * @return
 *   pointer to a string containing the path
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note
// \if SIMULATION
//  @GSIM_F:GetCguiPathIcon:KSFAM_CGUI:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetCguiPathIcon ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern char          *GetCguiPathIcon(void) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief GetCguiEntryDirectory return the resource name for CGUI page entry.
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note
// \if SIMULATION
//  @GSIM_F:GetCguiEntryDirectory:KSFAM_CGUI:
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetCguiEntryDirectory ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern char          *GetCguiEntryDirectory(void) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief Display a message on the screen with WGUI interface
 *  WGUI window is automatically resized to fill the user area
 *  "DISPLAY" must be closed before calling this function
 *  if terminal is not WGUI, "old" way for displaying
 *  Waiting time, if the flag parameter is WAITING, can be parametered with the TimeOutDisplayMessage parameter
 *  (see function PSQ_write_state_param)
* @param message : buffer containing the message
* @param option : display options
* @param flag : wait after display (WAITING or !WAITING)
* @return none
* @par exit exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 271) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CGUI_Display:KSFAM_CGUI:
//  @GSIM_A:1:DATA_CODE(strlen(message) +1)
// (depend de la taille de l'ecran)
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define CGUI_Display ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern void           CGUI_Display (unsigned char *message,char *option,unsigned char flag) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief Display a message on the screen with WGUI interface
 *  WGUI window is automatically resized to fill the user area
 *  "DISPLAY" must be closed before calling this function
 *  if terminal is not WGUI, "old" way for displaying
 *  Waiting time, if the flag parameter is WAITING, can be parametered with the TimeOutDisplayMessage parameter
 *  (see function PSQ_write_state_param)
* @param pMSGinfos : struct containing the info message
* @param option : display options
* @param flag : wait after display (WAITING or !WAITING)
* @return none
* @par exit exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 272) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CGUI_DisplayMSG:KSFAM_CGUI:
//  @GSIM_A:1:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define CGUI_DisplayMSG ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern void 		  CGUI_DisplayMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 * The application should not call this function. Cgui interface deprecated.
 *
 *  @brief Display a message on the screen with WGUI interface
 *  WGUI window is automatically resized to fill the user area
 *  "DISPLAY" must be closed before calling this function
 *  if terminal is not WGUI, "old" way for displaying
 *  Waiting time, if the flag parameter is WAITING, can be parametered with the TimeOutDisplayMessage parameter
 *  (see function PSQ_write_state_param)
* @param num : Contain the range of the message (see english.h or french.h)
* @param option : display options
* @param flag : wait after display (WAITING or !WAITING)
* @return none
* @par exit exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 273) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CGUI_DisplayMSGnum:KSFAM_CGUI:
//  @GSIM_A:1:ONE_POINTER
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define CGUI_DisplayMSGnum ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern void 		  CGUI_DisplayMSGnum(int num,char *option,unsigned char flag) MACRO_DEPRECATED;
#endif


//!see \ref CGUI_Display
#ifndef _DEPRECATED_MANAGER_SDK980_
#define CGUI_Afficher ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern void CGUI_Afficher (unsigned char *message,char *option,unsigned char flag) MACRO_DEPRECATED;
#endif


//!see \ref CGUI_DisplayMSG
#ifndef _DEPRECATED_MANAGER_SDK980_
#define CGUI_AfficherMSG ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern void CGUI_AfficherMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag) MACRO_DEPRECATED;
#endif


//!see \ref CGUI_DisplayMSGnum
#ifndef _DEPRECATED_MANAGER_SDK980_
#define CGUI_AfficherMSGnum ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
#else
extern void CGUI_AfficherMSGnum(int num,char *option,unsigned char flag) MACRO_DEPRECATED;
#endif

#ifdef _DEPRECATED_MANAGER_SDK980_
/*! \cond NON_VISIBLE */
#define CGUI_Display        CGUI_Afficher
#define CGUI_DisplayMSG     CGUI_AfficherMSG
#define CGUI_DisplayMSGnum  CGUI_AfficherMSGnum
/*!\endcond*/
#endif

/*! @} **/


#endif

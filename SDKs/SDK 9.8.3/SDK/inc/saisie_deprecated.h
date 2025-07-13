#ifndef SAISIE_DEPRECATED_H
#define SAISIE_DEPRECATED_H

/*! @addtogroup KSFAM_CGUI
 * @{
 */

/*! 
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief Start Navigating in a list and select an item within a window;
 * - If the dll cgui is loaded this routine is running with the cgui APIs else this routine
 * - uses the graphic library capabilities.
 * - This routine starts an entry system task. Application has to wait for the event ENTRY,
 * - then it can get the entry using Get_Entry .
 * @param Menu : Graphic context
 * @param MenuCgui : Cgui Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 27) if function does not exist
 * @section Sample List entry

 * @include saisie_Sample_11.c
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_List_Entry:KSFAM_CGUI:
//  GSIM_S:cGUI_List_Entry:E_cGUI_List_Entry
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_List_Entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_List_Entry(wStructListe *Menu, cGuiStructList *MenuCgui) MACRO_DEPRECATED;
#endif

/*! 
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief Start Navigating in a list and select an item within a window;
 * - If the dll cgui is loaded this routine is running with the cgui APIs else this routine
 * - uses the graphic library capabilities.
 * - This routine starts an entry system task. Application has to wait for the event ENTRY,
 * - then it can get the entry using Get_Entry .
 * @param Menu : Graphic context
 * @param MenuCgui : Cgui Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 51) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_Large_List_Entry:KSFAM_CGUI:
//  GSIM_S:cGUI_Large_List_Entry:cGUI_Large_List_Entry
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Large_List_Entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Large_List_Entry(wStructListe *Menu,
		cGuiLargeStructList *MenuCgui) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief Start Navigating in a list and select an item within a window;
 * - This routine is running only with the cgui APIs
 * - This routine starts an entry system task. Application has to wait for the event ENTRY,
 * - then it can get the entry using Get_Entry .
 * @param tablewgui : Cgui Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 49) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_List_Multi_Entry:KSFAM_CGUI:
//  GSIM_S:cGUI_List_Multi_Entry:E_cGUI_List_Multi_Entry
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_List_Multi_Entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
void cGUI_List_Multi_Entry(cGuiStructList *tablewgui) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief Display a list of items.
 * - If the dll cgui is loaded this routine is running with the cgui APIs else this routine
 * - uses the graphic library capabilities.
 * @param table : structure of the screen.
 * @param MenuCgui : Cgui Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 28) if function does not exist
 * @section sample Aff List

 * @include saisie_Sample_12.c
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_Aff_Liste:KSFAM_CGUI:
//  GSIM_S:cGUI_Aff_Liste:E_cGUI_Aff_Liste
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Aff_Liste ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Aff_Liste(wStructListe *table, cGuiStructList *MenuCgui) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief This function allows to enter a numerical entry within a window.
 * - If the dll cgui is loaded this routine is running with the cgui APIs else this routine
 * - uses the graphic library capabilities.
 * - This routine starts an entry system task. Application has to wait for the event ENTRY , then it can
 * - get the entry using Get_Entry
 * @param menu : see G_List_Entry.
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * @param NumEntry : Cgui Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 29) if function does not exist
 * @section sample Numerical Entry

 * @include saisie_Sample_13.c
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_Numerical_Entry:KSFAM_CGUI:
//  GSIM_S:cGUI_Numerical_Entry:E_cGUI_Numerical_Entry
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Numerical_Entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Numerical_Entry(wStructListe *menu, TAB_ENTRY_STRING *table,
		cGuiStructEntry *NumEntry) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief Start Navigating in a Icon list and select an item within a window;
 * - Use this routine only if the dll cgui is loaded
 * - This routine starts an entry system task. Application has to wait for the event ENTRY,
 * - then it can get the entry using Get_Entry .
 * @param IconList : Icon Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 30) if function does not exist
 * @section Sample Icon List

 * @include saisie_Sample_14.c
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_Icon_List:KSFAM_CGUI:
//  GSIM_S:cGUI_Icon_List:E_cGUI_Icon_List
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Icon_List ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Icon_List(wIconList *IconList) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief Start Navigating in a Icon list and select an item within a window;
 * - Use this routine only if the dll cgui is loaded
 * - This routine starts an entry system task. Application has to wait for the event ENTRY,
 * - then it can get the entry using Get_Entry .
 * @param IconList : Icon Graphic Context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 52) if function does not exist
 */
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Large_Icon_List ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Large_Icon_List(wLargeIconList *IconList) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief This function allows to enter an alpha-numerical entry within a window using a friendly entry screen.
 * - If the dll cgui is loaded this routine is running with the cgui APIs else this routine
 * - uses the graphic library capabilities.
 * @param menu : see G_Saisie_Liste
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * @param NumEntry: Cgui graphic Context.
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 31) if function does not exist
 * @section Sample Extended Entry

 * @include saisie_Sample_15.c
 *
 * @link KSFAM_CGUI Back to top @endlink
 */

// \if SIMULATION
//  @GSIM_F:cGUI_Extended_Entry:KSFAM_CGUI:
//  GSIM_S:cGUI_Extended_Entry:E_cGUI_Extended_Entry
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Extended_Entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Extended_Entry(wStructListe *menu, TAB_ENTRY_STRING *table,
		cGuiStructEntry *NumEntry) MACRO_DEPRECATED;
#endif

/*!  
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL API: GL_Dialog instead.
 * 
 * @brief This Function allows to enter an alphanumerical entry within a window. This routine 
 * - starts an entry system task. Application has to wait for the event ENTRY , then it can
 * - get the entry using Get_Entry .
 * - If the dll cgui is loaded this routine is running with the cgui APIs else this routine
 * - uses the graphic library capabilities.
 * @param menu : see G_Saisie_Liste.
 * @param table : pointer to TAB_ENTRY_ALPHA structure.
 * @param NumEntry: Cgui graphic Context.
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 32) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:cGUI_Alphanum_Entry:KSFAM_CGUI:
//  GSIM_S:cGUI_Alphanum_Entry:E_cGUI_Alphanum_Entry
// \endif
#ifndef _DEPRECATED_MANAGER_SDK980_
#define cGUI_Alphanum_Entry ERROR_Deprecation_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern void cGUI_Alphanum_Entry(wStructListe *menu, TAB_ENTRY_ALPHA *table,
		cGuiStructEntry *NumEntry) MACRO_DEPRECATED;
#endif

/*! @} **/

#endif


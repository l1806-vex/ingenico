/*! @addtogroup KSFAM_M2OS
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UTIL_SQ_DEPRECATED_INCLUDE_
#define _UTIL_SQ_DEPRECATED_INCLUDE_

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use GOAL instead.
 *
 *  @brief  This function allows the amount entry.
 *	@param data_money : Name of the currency and position of the coma.
 *	@param saisie : Amount entry (output)
 *	@param *reponse : entry's response
 *	@param chaine1 : string to display on the first line
 *	@param table : mask of the keys and time out.
 *	@param *tab_devise : address of the available currency table
 *	@param nb_money : number of money in the table
 *	@return Returns the event KEYBOARD or TIMEOUT
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define USQ_Amount_Entry ERROR_Deprecation_For_Function_USQ_Amount_Entry_For_Module_Manager_SeeDocumentation_In_CHM_File;
#define USQ_Saisie_montant ERROR_Deprecation_For_Function_USQ_Saisie_montant_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern unsigned int   USQ_Amount_Entry( S_MONEY  *data_money ,  /* nom de la devise et position de la virgule (e/s)  */
                                 ENTRY_BUFFER    * saisie ,  /* Montant saisie en retour                          */
                                 unsigned char    *reponse ,  /* reponse du compte rendu de la saisie              */
                                 char             *chaine1 ,  /* Chaine a afficher sur la premiere ligne           */
                                 TAB_ENTRY_AMOUNT *table ,  /* Masque des touches et time out   */
                                 S_MONEY          *tab_devise ,  /* adresse de la table des devises diponibles*/
                                 unsigned char     nb_money    /* nombre de money contenue dans la table */
                               ) MACRO_DEPRECATED;

extern unsigned int   USQ_Saisie_montant( S_MONEY  *data_money ,  /* nom de la devise et position de la virgule (e/s)  */
                                 ENTRY_BUFFER    * saisie ,  /* Montant saisie en retour                          */
                                 unsigned char    *reponse ,  /* reponse du compte rendu de la saisie              */
                                 char             *chaine1 ,  /* Chaine a afficher sur la premiere ligne           */
                                 TAB_ENTRY_AMOUNT *table ,  /* Masque des touches et time out   */
                                 S_MONEY          *tab_devise ,  /* adresse de la table des devises diponibles*/
                                 unsigned char     nb_money    /* nombre de money contenue dans la table */
                               ) MACRO_DEPRECATED;
#define USQ_Amount_Entry      USQ_Saisie_montant
#endif

/*! @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  This function is no longer consistent, it always returns NIV_GEST_V5 | NIV_GEST_V5_2 | NIV_GEST_PROTOCOLE_E | NIV_GEST_DEMARRE_PISTE.
 *
 *  @brief  Returns the compatibility level of the manager.
 *	@return Compatibility level :
 * -	NIV_GEST_V5 0x0004
 * -	NIV_GEST_PROTOCOLE_E 0x0008
 * -	NIV_GEST_VITALE 0x0010
 * -	NIV_GEST_DEMARRE_PISTE 0x0040
 * -	NIV_GEST_V5_2 0x0080
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 29) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define USQ_Manager_level ERROR_Deprecation_For_Function_USQ_Manager_level_For_Module_Manager_SeeDocumentation_In_CHM_File;
#define USQ_Niveau_seq ERROR_Deprecation_For_Function_USQ_Niveau_seq_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern unsigned int USQ_Manager_level(void);
extern unsigned int USQ_Niveau_seq(void);
#define USQ_Manager_level     USQ_Niveau_seq
#endif

#endif


/*! @} **/
#ifdef __cplusplus
}
#endif

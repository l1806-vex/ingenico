/*! @addtogroup KSFAM_PARTAGE
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PARTAGE_H
#define PARTAGE_H


//! \brief Types de donnees a partager
#define TYPE_ENVELOPPE 1



/*! @brief Creation d'un fichier par l'emetteur
@param recepteur : nom du destinataire des donnees
@param emetteur  : nom de l'emetteur des donnees
@return 
@ -      TRUE si le fichier s'est bien ouvert
@ -      FALSE sinon
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 0) if function does not exist
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
char PART_creer_fichier (char *recepteur, char *emetteur);



/*! @brief Ecriture d'un fichier par l'emetteur
@param type_donnees : type des donnees ecrites dans le fichier
@param donnees      : buffer contenant les donnees
@param taille       : taille des donnees a ecrire
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 1) if function does not exist
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
void PART_ecrire_donnees (int type_donnees, char *donnees, int taille);




/*! @brief ferme un fichier et descend le disque de partage
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 2) if function does not exist
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
void PART_fermer_fichier (void);




/*! @brief Initialise la recherche des fichiers par un recepteur
@param recepteur : nom du destinataire des donnees
@return 
@- TRUE si le disque de partage existe
@- FALSE sinon
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 3) if function does not exist
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
char PART_init_recherche (char *recepteur);




/*! @brief Lance la recherche des fichiers par un recepteur
@return 
//!      TRUE si un fichier pour ce recepteur existe
//!      FALSE sinon
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 4) if function does not exist
//! \note 
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
char PART_fichier_existe (void);




/*! @brief Lecture d'un fichier par le recepteur
@param type_donnees : type des donnees lues dans le fichier
@param donnees : buffer contenant les donnees
@param taille : taille des donnees a lire
@return 
//!      TRUE si un fichier pour ce recepteur existe
//!      FALSE sinon
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 5) if function does not exist
//! \note 
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
void PART_lire_fichier (int *type_donnees, char *donnees, int *taille);




/*! @brief Efface le fichier lu par le recepteur
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 6) if function does not exist
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
void PART_effacer_fichier (void);



/*! @brief Arrete la recherche des fichiers par un recepteur
 *  @par exit (EXIT_DLL_PARTAGE_NOT_INITIALIZED + 7) if function does not exist
*
 * @link KSFAM_PARTAGE Back to top @endlink
*/
void PART_stop_recherche (void);



#endif

/*! @} **/
#ifdef __cplusplus
}
#endif

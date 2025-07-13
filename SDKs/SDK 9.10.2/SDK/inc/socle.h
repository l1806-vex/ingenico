/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SOCLE_INC
#define _SOCLE_INC

/*
======================================================================
					List of Defines
======================================================================
*/
#define FONCTION_TELECHARGEMENT	0
#define FONCTION_CAISSE_PSC		1
#define FONCTION_CAISSE_PSS		2
#define FONCTION_CB2A			3



/*
======================================================================
			Data Structures Definition
======================================================================
*/
/*! @brief This structure is used to manage a return on a base. When a connection is not used, its values is EOF(-1).*/
typedef struct
{
	//See constant above		
	int service;													/*!< service ID */
	int Com1;															/*!< COM1 serial link */
	int Com2;															/*!< COM2 serial link */
	union
	{
		S_CC_Connexion 	xpsConnexion ;				/*!< for CB2A*/
		S_PARAM_TLCHGT 	param_telechgt;				/*!< parameters for the download*/
		//For connection box				*/
		//When connection is in idle state, it's EOF is (-1) 
	} Val;
} StructRetourSocle;

/*! @brief This structure defines the basic remote informations.*/
typedef struct
{
  unsigned short	application_type;				/*!< Informations about the type of the calling application.*/
  S_PARAM_TLCHGT 	param_telechgt;					/*!< download parameters.*/
} StructRemote;


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function provides information about the necessity of placing the terminal on its base.
 * @param Param : pointer to structure StructRetourSocle.
 * @return
 * - 1 if ok
 * - 2 if cancel
 * - 0 otherwise.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 125) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int            GestionRetourSocle(StructRetourSocle *Param );


/*! @brief For the portable range, manages the necessity of placing the terminal on its base.
 * @param Param : pointer to structure StructRetourSocle.
 * @return 1 if ok 0 otherwise
 * @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int            GestionSocle(StructRetourSocle *Param );


#endif
/*! @} **/
#ifdef __cplusplus
}
#endif

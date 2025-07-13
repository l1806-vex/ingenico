/*! @addtogroup KSFAM_CB2A
	* @{
**/
#ifndef INC_CB2A_CMP_
#define INC_CB2A_CMP_

/* ----- niveau de specifications ----- */
#define SPECIF_5_1  1
#define SPECIF_5_2  2
#define SPECIF_5_2b 3                   /* RA : SMO/ETU/03/1561/SC */

/* ----- niveau de compatibilite appli ----- */
#define NIV_COMP_APPLI_1 1
#define NIV_COMP_APPLI_2 2
#define NIV_COMP_APPLI_3 3
#define NIV_COMP_APPLI_4 4

/* ----- niveau de compatibilite gest ----- */
#define NIV_COMP_SEQ_1 1
#define NIV_COMP_SEQ_2 2
#define NIV_COMP_SEQ_3 3
#define NIV_COMP_SEQ_4 4


/*! @brief This function returns the protocol's compatibility with the applications.
 *	@param no_appli 	   : application's identifiant,
 *	@param type_log 		 : type of applicative software (CB, AMEX, ...),
 *	@param type_paiement : type of payment (PPBO, PPEMV, VAD, ...),
 *	@param no_specif     : specifications' level (5.1, 5.2, ...),
 *	@param niv_cmp_appli : application's compatibility level
 *	@param niv_cmp_seq   : manager's compatibility level
 *	@return
 * -	TRUE if there is compatibility between the manager and the application
 * -	FALSE otherwise
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 2) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_Cb2a_compatibilite:KSFAM_CB2A:
//  @GSIM_A:6:DATA_SIZE(4)
// \endif
extern unsigned char  PSQ_Est_Cb2a_compatibilite   (int no_appli, int type_log, int type_paiement, int no_specif, int niv_cmp_appli, int * niv_cmp_seq);


#endif
/*! @} **/

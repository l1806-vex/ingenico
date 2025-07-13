/*! @addtogroup KSFAM_CB2A
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SERV_AUTO_INC
#define SERV_AUTO_INC

/*
======================================================================
					List of Defines
======================================================================
*/

/* compte-rendu autorisation_CBSA */

#define CR_AUTO_AUTORISEE        0
#define CR_AUTO_CA_NON_ATTEINT   1
#define CR_AUTO_INTERDITE        2
#define CR_AUTO_REFUSEE          3
#define CR_AUTO_REFUSEE_FORCABLE 4
#define CR_AUTO_PHONIE           5
#define CR_AUTO_PHONIE_CENTRE    6
#define CR_AUTO_TAC_DEFAULT      7

/* *** mode d'acquisition, pour renseigner les champs CB2A pour l'auto *** */
#define DEB_PUCE	    0
#define DEB_PISTE	    1
#define DEB_DEGRADE     2
#define DEB_SAISIE_MAN  3   /*!< VAD */



/*!< informations necessaires a la demande d'autorisation */

typedef struct
{
    unsigned char    date_debut[2];                /*!< date de debut en BCD  AA MM */                                    /*!< pour champ 59 103 */
    unsigned char    date_fin[2];                  /*!< date de fin en BCD  AA MM */                                      /*!< pour champ 14 */
    unsigned char    code_monnaie_carte[3] ;       /*!< code numerique de la monnaie */                                   /*!< pour champ 55 DFA9 */
    unsigned char    code_restriction[3];          /*!< code restriction de service ASCII = code service */               /*!< pour champ 40*/
    unsigned char    adr_mot_fixe_CAI_emetteur[4]; /*!< donnees utilisees pour calcul CAI emetteur adr mot fixe ASCII */  /*!< pour champ 55 DFA1 */
    unsigned int     mot_fixe_CAI_emetteur;        /*!< donnees utilisees pour calcul CAI emetteur mot fixe */            /*!< pour champ 55 DFA1 */
    unsigned char    CAI_emetteur[16];             /*!< CAI emetteur ASCII */                                             /*!< pour champ 55 DFA0 */
}AUTO_DDE_B0;



typedef struct
{
/*----------------------- specifique EMV ----------------------------------------------------------- */
	unsigned char        no_seq_carte_pres;     /*!< presence du numero sequentiel de la carte TRUE ou FALSE */
	unsigned char        no_seq_carte;          /*!< numero sequentiel de la carte */
	unsigned char        lg_track2;             /*!< si lg track2 = 0, pas de track2*/
	unsigned char        track2_equ_data[19];   /*!< track2 equivalent data */
	TERM_VERIF_RESULTS   TVR;                   /*!< terminal verification results (TVR) */
	unsigned char        transaction_type_emv;  /*!< transaction type utilise pour un 'application usage control'*/
    unsigned char        date_exp_carte_emv[3]; /*!< date d'expiration d'une carte EMV en BCD  AA MM JJ */
    unsigned char        lg_AID;                /*!< si lg = 0, pad d'AID */
	AID                  AID;                   /*!< application identifier AID */
	unsigned char        lg_IAD;                /*!< si lg = 0, pas d'IAD */
	ISSUER_APPLI_DATA    IAD;                   /*!< issuer application data */
	APPLI_CRYPTO         appli_crypto;          /*!< application cryptogram */
	unsigned char        crypto_info_data;      /*!< cryptogram information data */
	TERM_CAPABILITIES    terminal_capabilities; /*!< terminal capabilities */
	ATC                  ATC;                   /*!< application transaction counter ATC */
	UNPREDIC_NO_TERMINAL unpredictable_number;  /*!< unpredictable_number */
	AIP                  AIP;                   /*!< application interchange profile */
}AUTO_DDE_EMV;

typedef struct
{
   unsigned char    no_tran[2];                   /*!< numero sequentiel de la transaction en DCB */        /*!< pour champ 11 */
   unsigned char    montant[4];                   /*!< montant de la transaction en BIN */                  /*!< pour champ 4 */	
   unsigned char    cond_trans;                   /*!< condition de la transaction = 0 */                   /*!< pour champ 25 */
   unsigned char    ctrl_code;                    /*!< informations de securite ASCII seulement la pos 2 */ /*!< pour champ 53 */
   unsigned char    date[3];                      /*!< date             en BCD  AA MM JJ */                 /*!< pour champ 13, champ 59 102 */
   unsigned char    heure[3];                     /*!< heure            en BCD  HH MM SS */                 /*!< pour champ 12 */
   unsigned char    piste_iso[40];                /*!< piste ISO2       en ASCII */                         /*!< pour champ 35 */
   unsigned char    code_monnaie[3];              /*!< code numerique de la monnaie */                      /*!< pour champ 49 */
   unsigned short   code_raison;                  /*!< raison d'appel */                                    /*!< pour champ 59 101 */
   unsigned long    mnt_cumule;                   /*!< montant cumule des transactions autorisees */        /*!< pour champ 59 207 */
   unsigned char    mode_acq;                     /*!< DEB_PUCE, DEB_PISTE, DEB_DEGRADE */                  /*!< pour champ 22,35,40,55 DF80 DF81 DFA0 DFA1 DFA9, 59 103 */
   NO_PORTEUR       no_porteur;                   /*!< numero porteur */                                    /*!< pour champ 2 */
   unsigned char    no_dossier[12];               /*!< no dossier pour PNF ASCII*/                          /*!< pour champ 37 */
   unsigned char    type_differe;                 /*!< Differe : TRUE ou FALSE */                           /*!< pour champ 3 */
   unsigned char    date_fin[2];                  /*!< date de fin en BCD  AA MM */                         /*!< pour champ 14 UNIQUEMENT EMV PISTE*/

   union
   {
      AUTO_DDE_B0   dde_b0;
      AUTO_DDE_EMV  dde_emv;
   } u_dde;
   
} FT_SERV_S_DDE_AUTO;


/* informations presentes dans la reponse de l'acquereur
a la demande d'autorisation */

typedef struct
{
   /*!< 1er des types du champ 44 arrive (sauf AF : activation de service) EBCDIC */
   unsigned char champ_pres;
   unsigned char val_champ[25];
}
SERV_FT_S_DONNEES_COMP;

typedef struct
{
   /*!< no de telephone */
   unsigned char no_tel_pres;
   unsigned char no_tel_lg;
   unsigned char no_tel[21];
}
SERV_FT_S_TEL;

typedef struct
{
   /*!< message a destination de l'initiateur de la transaction */
   unsigned char message_pres;
   unsigned char message_lg;
   unsigned char message[21];
}SERV_FT_S_MSG;

typedef struct
{
   /*!< message a destination de l'initiateur de la transaction */
   unsigned char activation_srv_pres;
   unsigned char activation_srv;
}
SERV_FT_S_ACTIV;

typedef struct
{
  unsigned char lg_tag;
  unsigned char val_tag[128];
} TAG_71_72;

typedef struct
{
   unsigned char nb_tag_71;
   unsigned char nb_tag_72;
   TAG_71_72 liste_tag_71[5];
   TAG_71_72 liste_tag_72[5];
} REP_AUTO_SCRIPT;

typedef struct
{
   /*!< issuer_authentication_data */
   /*!< pour recup champ 55 91 */
   unsigned char issuer_auth_data_lg; /*!< lg = 0, pas de issuer_auth_data */
   unsigned char issuer_auth_data[16];
   
   /*!< card authentication results code : specifique VISA */ 
   /*!< pour recup champ 55 DFD0 */
   unsigned char card_auth_results_code_pres;
   unsigned char card_auth_results_code;

}AUTO_REP_EMV;


typedef struct
{
   unsigned char no_auto_pres;                                                                          /*!< pour recup champ 38 */
   unsigned char no_auto[6];             /*!< pas de \\0 */                                                /*!< pour recup champ 38 */
   unsigned char code_reponse[2];                                                                       /*!< pour recup champ 39 */
   SERV_FT_S_DONNEES_COMP donnees_comp;                                                                 /*!< pour recup champ 44 */
   SERV_FT_S_TEL tel;                    /*!< numero de telephone */                                      /*!< pour recup champ 44 no tel */
   SERV_FT_S_MSG msg;                    /*!< message a destination de l'initiateur de l atransaction */  /*!< pour recup champ 44 msg */
   SERV_FT_S_ACTIV activation;           /*!< activation de service apres l'autorisation */               /*!< pour recup champ 44 code activation */
   
   union
   {
	  AUTO_REP_EMV  rep_emv;
   } u_rep;
}
SERV_FT_S_REP_DDE_AUTO;

typedef struct
{
   unsigned char no_la_centre ;  /*!< dernier trame acquitter par le centre */
   unsigned char no_la_tpe ;     /*!< dernier trame acquitter par le tpe */

}SERVEUR_CBCOM;

/*!<--------------------------- PUBLIC ---------------------------------*/

/*!<***************************
   CONSTANTES
*****************************/

/*!< types d'activation de service en ASCII */
#define SERVEUR_AUCUNE_ACTIVATION      0x31
#define SERVEUR_ACTIVER_TLP            0x32
#define SERVEUR_ACTIVER_TLC            0x33
#define SERVEUR_ACTIVER_TLCH           0x34

/*!< code reponse de l'autorisation */
#define SERVEUR_TRANS_OK               0x3030
#define SERVEUR_TRANS_OK_APRES_ID      0x3038

/*!< type de centre d'autorisation : Normal ou Secours */
#define SERVEUR_CENTRE_NORMAL  0
#define SERVEUR_CENTRE_SECOURS 1

/*!<***************************
   TYPES
*****************************/

typedef unsigned char SERVEUR_AUTO_T_CR_NUMER[2];
#define COD_TRT_DIFF_REC "003300"

/****************************
   PROTOTYPES
*****************************/


/*! @brief gere la demande d'autorisation selon le protocole CB2A
* @param type_centre : type de centre a contacter (normal ou secours).
* @param info_demande : informations necessaires a la constitution du message de demande d'autorisation.
* @param rep_auto : informations presente dans la reponse a la demande d'autorisation.
* @param cr_numerotation : compte-rendu de la numerotation.
* @param pt_rep_auto_script_appli : init de la zone de stockage des tags 71 et 72.
* @param pt_fct : Pointeur sur les fonctions de controle des TAGS.
* @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 0) if function does not exist
*
* @link KSFAM_CB2A Back to top @endlink
*/
unsigned int SERVEUR_demander_auto(unsigned char type_centre,
                                   FT_SERV_S_DDE_AUTO *info_demande,
                                   SERV_FT_S_REP_DDE_AUTO *rep_auto,
                                   SERVEUR_AUTO_T_CR_NUMER cr_numerotation,
                                   REP_AUTO_SCRIPT *pt_rep_auto_script_appli
								   ,StructFctCb2a *pt_fct
								   );


/****************************
   CONSTANTES
*****************************/

/*!< mode de lecture du terminal */
/*!< champ 22  format n3 : pade avec un 0 a gauche */
#define SERVEUR_PISTE_SANS_SAISIE_CODE             0x0022
#define SERVEUR_PUCE_AVEC_SAISIE_CODE              0x0051
#define SERVEUR_PUCE_SANS_SAISIE_CODE              0x0052 /*!< RA : TEDT/Z3/02/1055/IR */
#define SERVEUR_PISTE_DEGRADEE_SANS_SAISIE_CODE    0x0812
#define SERVEUR_MANUEL_SANS_SAISIE_CODE            0x0012  /*!< VAD */


/*!< types du champs 44 */

#define SERVEUR_TYPE_CHAMP_ERRONE       0xC1C1 /*!< AA */
#define SERVEUR_TYPE_ERR_SECURITE       0xC1C2 /*!< AB */
#define SERVEUR_TYPE_CONV_CHAMP         0xC1C3 /*!< AC */
#define SERVEUR_TYPE_REFUS_ACCORD       0xC1C4 /*!< AD */
#define SERVEUR_TYPE_CODE_ACTIVATION    0xC1C6 /*!< AF */
#define SERVEUR_TYPE_MONTANT_MAX        0xC2C1 /*!< BA */
#define SERVEUR_TYPE_NO_TEL             0xC2C2 /*!< BB */
#define SERVEUR_TYPE_MESSAGE            0xC2C3 /*!< BC */
#define SERVEUR_TYPE_INFO_CVV_CVC       0xC3C1 /*!< CA */
#define SERVEUR_TYPE_INFO_CAI_EMETTEUR  0xC3C2 /*!< CB */  /*!< TEDT/Z3/01/1553/SC : pas de remontee du champ 44 type CB */



/*!< types du champs 47 */

#define SERVEUR_TYPE_IDSA               0xC1F0 /*!< A0 */
#define SERVEUR_TYPE_IDPA               0xF9F7 /*!< 97 */
#define SERVEUR_TYPE_SIRET              0xF9F6 /*!< 96 */
#define SERVEUR_TYPE_INFO_CTRL_INT_PIST 0xF7F2 /*!< 72 */
#define SERVEUR_TYPE_CODE_CHGT_ETAT     0xF7F1 /*!< 71 */
#define SERVEUR_TYPE_CONVERSION         0xF2F0 /*!< 20 */
#define SERVEUR_TYPE_SITE               0xF0F8 /*!< 08 */
#define SERVEUR_TYPE_CODE_DONNEE        0xF0F3 /*!< 03 */




/*!< types du champs 55 */
#define SERVEUR_TYPE_CARD_AUTH_RES_CODE    0xDFD0 /*!< MPEV5.2 */
#define SERVEUR_TYPE_MOT_ETAT_FINAL        0xDFAA /*!< MPEV5.2 */
#define SERVEUR_TYPE_CODE_DEV_CARTE        0xDFA9 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CODE_EXPOSANT         0xDFA8 /*!< MPEV5.2 */
#define SERVEUR_TYPE_DON_INT_CAI_TELE      0xDFA7 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CAI_TELEPAIE          0xDFA6 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ELT_CAL_CERTIF_CAM    0xDFA5 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CERTIFICAT_CAM        0xDFA4 /*!< MPEV5.2 */
#define SERVEUR_TYPE_DONNEES_ELT_AUTH      0xDFA3 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ELT_AUTHENTIF         0xDFA2 /*!< MPEV5.2 */
#define SERVEUR_TYPE_DONNEES_INT_CAI       0xDFA1 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CAI_EMETTEUR          0xDFA0 /*!< MPEV5.2 */
#define SERVEUR_TYPE_APPLI_CARTE           0xDF81 /*!< MPEV5.2 */
#define SERVEUR_TYPE_RES_TRAIT_PUCE        0xDF80 /*!< MPEV5.2 */
#define SERVEUR_TYPE_UNPREDIVTABLE_NUM     0x9F37 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ATC                   0x9F36 /*!< MPEV5.2 */
#define SERVEUR_TYPE_TERMINAL_CAPABILI     0x9F33 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CRYTO_INFO_DATA       0x9F27 /*!< MPEV5.2 */
#define SERVEUR_TYPE_APPLI_CRYTO           0x9F26 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ISSUER_APPLI_DATA     0x9F10 /*!< MPEV5.2 */
#define SERVEUR_TYPE_APPLI_IDENTIFIER      0x9F06 /*!< MPEV5.2 */
#define SERVEUR_TYPE_AMOUNT                0x9F03 /*!< MPEV5.2 */
#define SERVEUR_TYPE_APPLI_EFFECT_DATE     0x5F25 /*!< MPEV5.2 */
#define SERVEUR_TYPE_APPLI_EXPIRAT_DATE    0x5F24 /*!< MPEV5.2 */
#define SERVEUR_TYPE_TRANSACTION_TYPE      0x009C /*!< MPEV5.2 */
#define SERVEUR_TYPE_TVR                   0x0095 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ISSUER_AUTH_DATA      0x0091 /*!< MPEV5.2 */
#define SERVEUR_TYPE_AIP                   0x0082 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ISSUER_SCRIPT_TEMP2   0x0072 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ISSUER_SCRIPT_TEMP1   0x0071 /*!< MPEV5.2 */
#define SERVEUR_TYPE_TRACK2_EQU_DATA       0x0057 /*!< MPEV5.2 */


/*!< type de puce du message de la demande d'autorisation */
/*!< champ 55 type DF81 */
/*!< Valeurs prises par rapport au champ 55 type DF73 de TCL TLP */
#define SERVEUR_TYPE_PUCE_BO_PRIME       1
#define SERVEUR_TYPE_PUCE_EMV            2

/*!< Resultat des traitements effectues sur micro circuit */
/*!< champ 55 type DF80 */
#define SERVEUR_MICRO_CIRCUIT_SANS_ERREUR 0x00
#define SERVEUR_PAS_REP_RAZ               0x10

/*!< types du champs 59 */
#define SERVEUR_TYPE_VISA_CPS_ATM_VC    0x0602 /*!< MPEV5.2 */
#define SERVEUR_TYPE_VISA_CPS_ATM_TI    0x0601 /*!< MPEV5.2 */
#define SERVEUR_TYPE_VISA_CPS_ATM_ACI   0x0600 /*!< MPEV5.2 */
#define SERVEUR_TYPE_IDENT_GEST_TELEP   0x0501 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CERTIF_ACCEPT      0x0500 /*!< MPEV5.2 */
#define SERVEUR_TYPE_VALIDITE_CERTIF    0x0408 /*!< MPEV5.2 */
#define SERVEUR_TYPE_SECU_TR_ELEC       0x0407 /*!< MPEV5.2 */
#define SERVEUR_TYPE_DELIVRANCE_CERTIF  0x0406 /*!< MPEV5.2 */
#define SERVEUR_TYPE_NATURE_CERTIF      0x0405 /*!< MPEV5.2 */
#define SERVEUR_TYPE_IDENT_RES_EMETTEUR 0x0404 /*!< MPEV5.2 */
#define SERVEUR_TYPE_NO_SERIE_POR_SET   0x0403 /*!< MPEV5.2 */
#define SERVEUR_TYPE_NO_SERIE_COM_SET   0x0402 /*!< MPEV5.2 */
#define SERVEUR_TYPE_TRANSTAIN          0x0401 /*!< MPEV5.2 */
#define SERVEUR_TYPE_XID                0x0400 /*!< MPEV5.2 */
#define SERVEUR_TYPE_INFOS_CVC_CVV      0x0301 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CVC_CVV            0x0300 /*!< MPEV5.2 */
#define SERVEUR_TYPE_TASA               0x020B /*!< MPEV5.2 */
#define SERVEUR_TYPE_ACTION_PUCE        0x020A /*!< MPEV5.2 */
#define SERVEUR_TYPE_RES_FLUX           0x0209 /*!< MPEV5.2 */
#define SERVEUR_TYPE_DUREE_VAL_PRE_AUTO 0x0208 /*!< MPEV5.2 */
#define SERVEUR_TYPE_MONTANT_CUMULE     0x0207 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ACTEUR             0x0206 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CODE_PAYS          0x0205 /*!< MPEV5.2 */
#define SERVEUR_NO_LOG_PA               0x0204 /*!< MPEV5.2 */
#define SERVEUR_TYPE_NO_LOGIQUE         0x0203 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CONTRAT_ACC        0x0202 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ITP                0x0201 /*!< MPEV5.2 */
#define SERVEUR_TYPE_PAIEMENT           0x0200 /*!< MPEV5.2 */
#define SERVEUR_TYPE_DEBUT_VAL_CARTE    0x0103 /*!< MPEV5.2 */
#define SERVEUR_TYPE_ANNEE_TRANS        0x0102 /*!< MPEV5.2 */   /*!< controler en reponse */
#define SERVEUR_TYPE_CODE_RAISON        0x0101 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CODE_FONCTION      0x0100 /*!< MPEV5.2 */
#define SERVEUR_TYPE_CRYPTO_VISUEL       0x0300 /*!< MPEV5.2 */ /*!< SC 06/03 VAD 5.2 */

/*!< type d'applicatif du système d'acceptation */
/*!< champ 59 type 020B */
#define ident_type_appli_oct1     "10"         /*!< B4-B0'/piste ISO2 */
#define ident_type_appli_oct1_emv "20"         /*!< EMV/piste ISO2    */
#define ident_type_appli_oct1_vad "00"         /*!< non specifie pour VAD */
#define ident_type_appli_oct2     "10"         /*!< B4-B0'/piste ISO2 */
#define ident_type_appli_oct2_vad "20"         /*!< VAD */
#define ident_type_appli_oct2_quasi "60" /*!< SMO/ETU/04/20073/SC */ /*!< SMO/ETU/04/20181/SC */
#define ident_type_appli_oct2_cash  "75" /*!< SMO/ETU/04/20073/SC */ /*!< SMO/ETU/04/20181/SC */


/*!< type de paiement en CB2A autorisation (EBCDIC) */
/*!< champ 59 type 0200 */
#define SERVEUR_PAIEMENT_PROX_AUTO    			  	0x10
#define SERVEUR_PAIEMENT_VAD_AUTO     			  			0x20  /*!< VAD */
#define SERVEUR_PAIEMENT_QUASI        			  	0x60  /*!< SMO/ETU/04/20073/SC */ /*!< SMO/ETU/04/20181/SC */
#define SERVEUR_PAIEMENT_CASH          				0x75  /*!< SMO/ETU/04/20073/SC */ /*!< SMO/ETU/04/20181/SC */
#define SERVEUR_PAIEMENT_AUTOMATE_CLASSE21   		0x50 /*!< MPC10S 07/2005 */
#define SERVEUR_PAIEMENT_AUTOMATE_CLASSE21_ADM   	0x42 /*!< MPC10S 07/2005 */
#define SERVEUR_PAIEMENT_AUTOMATE_CLASSE21_LOCATION	0x57 /*!< MPC10S 07/2005 */


/*!< code raison du message de la demande d'autorisation */
/*!< champ 59 type 0101 */
#define SERVEUR_RAIS_ALEATOIRE          0x1503
#define SERVEUR_RAIS_ONLINE_ACCEPTEUR   0x1506
#define SERVEUR_ONLINE_TERMINAL         0x1508
#define SERVEUR_RAIS_CODE_SERVICE       0x1509
#define SERVEUR_RAIS_SEUIL_APPEL        0x1510
#define SERVEUR_RAIS_BIN_INTERDIT       0x1512
#define SERVEUR_RAIS_INTERDIT_LN        0x1513
#define SERVEUR_RAIS_CUMUL              0x1651
#define SERVEUR_RAIS_BINSURV            0x1652
#define SERVEUR_RAIS_BININC             0x1653
#define SERVEUR_RAIS_CARTESURV          0x1654
#define SERVEUR_RAIS_CTRLFLUX           0x1656
#define SERVEUR_RAIS_MONNAIE_ETRANGERE  0x1657
#define SERVEUR_RAIS_CODE_MONNAIE       0x1658
#define SERVEUR_RAIS_CARTEREFU          0x1659
#define SERVEUR_RAIS_ARQC_CARTE         0x1660
#define SERVEUR_BIN_REFUSE              0x1663 /*!< TEDT/Z3/02/1450/SC point 5 */
/*!< TEDT/Z3/01/1383/sc : 2 point 3 : suppression de la raison d'appel suspicion COM 1511 */

/****************************
   TYPES
*****************************/

/*types pour acceder aux fonctions de controle et de recuperation des champs */

typedef unsigned int (*PFONCT_AUTO) (SERV_FT_S_REP_DDE_AUTO *);

typedef struct
{
   PFONCT_AUTO fonc;
} SERVEUR_TAB_RELOC_AUTO;

#endif

/*!<! @} **/
#ifdef __cplusplus
}
#endif

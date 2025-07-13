/*! @addtogroup KSFAM_CB2A
	* @{
**/

#ifndef SERVEUR_INC
#define SERVEUR_INC


/*------------------------ PUBLIC --------------------------*/

/*
**************************************************************
        declarations des define
**************************************************************
*/



/* code retour des fonctions */   /* !!! isa !!! */
#define SERVEUR_OK                            CB2A_OK
#define SERVEUR_ERR_INTERNE                   0x0501
#define SERVEUR_REPONDRE_INC_DIAL             0x0502
#define SERVEUR_ERR_STOCKAGE_DONNEES          0x0503
#define SERVEUR_ERR_FORMAT_MSG_MAJ            0x0504

#define SERVEUR_ERR_COUPURE_SECT              0x0506

#define SERVEUR_ERR_xxx                       0x05xx

#define  NB_MAX_ERREUR                        3 /* !!! isa !!! test 2.3.10 */

/* valeur initiale du cr de numerotation  */
#define SERV_PAS_NUMEROTE                     "??"

/* nombre de tables que l'on peut recevoir (different du nombre de tables
reellement gerees */
#define SERVEUR_MAX_TABLES_RECEVABLES     29   /* MPE V5.2 */

/* valeur prise par la raison d'appel */
#define SERVEUR_PROGRAMME_ACQ         CB2A_PROGRAMME_ACQ
#define SERVEUR_CHGT_LOGICIEL         CB2A_CHGT_LOGICIEL
#define SERVEUR_CHGT_MATERIEL         CB2A_CHGT_MATERIEL
#define SERVEUR_PREMIERE_INIT         CB2A_PREMIERE_INIT
#define SERVEUR_VIDAGE_TRANS          CB2A_VIDAGE_TRANS
#define SERVEUR_MAJ_PARAM             CB2A_MAJ_PARAM
#define SERVEUR_FICHIER_TRANS_PLEIN   CB2A_FICHIER_TRANS_PLEIN
#define SERVEUR_REPRISE_INCIDENT      CB2A_REPRISE_INCIDENT
#define SERVEUR_APPEL_ACQ             CB2A_APPEL_ACQ
#define SERVEUR_MAINTENANCE           CB2A_MAINT  /* MPEV5.2 */


/* valeur prise par le compte rendu de la consolidation */
#define SERVEUR_CONSO_OK               0
#define SERVEUR_CONSO_KO               1
 
/* service demarre ou pas dans le compte-rendu */
#define SERV_ACTIVE                    0
#define SERV_PAS_ACTIVE                1

#define SERV_SERVICE_OK                0
#define SERV_SERVICE_KO                1

#define SERV_PAS_TABLE_TELEPARAMETREE  0xFF

/*
**************************************************************
        declarations des typedef
**************************************************************
*/


/* compte rendu d'une remise */
typedef struct
{  
   unsigned char cr;            /* cr de la remise */
   unsigned long id_remise_acc; /* binaire */
   unsigned long id_remise_acq; /* binaire */
   DATE          date_conso;
   S_MONEY       monnaie;
   S_CUMUL       cumul;
   CB2A_STRUC_CODE_CONSO code_conso;   /* ascii */
} SERVEUR_S_REMISE;


/* compte rendu de numerotation */
typedef unsigned char SERV_T_CR_NUMER[2];


/* compte rendu de la telecollecte */
typedef struct
{
   unsigned char active; /* SERV_ACTIVE ou SERV_PAS_ACTIVE */
   unsigned char cr;     /* SERV_SERVICE_OK ou SERV_SERVICE_KO 
                         (significatif seulement si active = SERV_ACTIVE) */
   unsigned char nb_remises;
   SERVEUR_S_REMISE les_remises[NB_MONEY];

}SERV_S_CR_TLC;   

/* compte rendu du teleparametrage */
typedef struct
{
   unsigned char active; /* SERV_ACTIVE ou SERV_PAS_ACTIVE */
   unsigned char cr;     /* SERV_SERVICE_OK ou SERV_SERVICE_KO 
                         (significatif seulement si active = SERV_ACTIVE) */
   unsigned char der_tb_teleparametree; /* derniere table teleparametree */
   unsigned char tables_stockees[SERVEUR_MAX_TABLES_RECEVABLES+1]; /* table  
   stockee ou non : TRUE FALSE. L'indice du tableau est le numero de la table */

}SERV_S_CR_TLP;   

typedef struct
{
   unsigned char lg;
   unsigned char contenu[255];

} SERV_S_IMPRIMER;

/* compte rendu des derniers services realises lors de la
derniere connexion a un centre */
typedef struct
{
   unsigned int cr;           /* SERVEUR_OK ou SERVEUR_ERR_xxx */
   SERV_T_CR_NUMER cr_num; /* cr de numerotation */
   SERV_S_CR_TLC   cr_tlc; /* cr du service TLC  */
   SERV_S_CR_TLP   cr_tlp; /* cr du service TLP  */
   unsigned char   code_activation; /* code activation de service SERVICE_xxx */
   SERV_S_IMPRIMER libelle; /* libelle de reponse */
   unsigned char   pi01; /* pi01 envoye par le TPE en cas d'echec */ /* !!! isa !!! */   
} SERV_S_CR_SERVICES;


/* informations pour la phase de connexion */
typedef struct
{
   char              type_pad;
   STR_ADR_RACCORD   adr_raccord;
   unsigned char     lg_adr_raccord;
   STR_ADR_APPEL     adr_appel;
   unsigned char     lg_adr_appel;
} SERVEUR_S_CONNEX;


/*! @brief gere la demande d'autorisation selon le protocole CB2A
* @param service_initial :
* -            SERVICE_TELECOLLECTE
* -            SERVICE_TELECHARGEMENT
* -            SERVICE_TELEPARAMETRAGE
* -            SERVICE_AUTORISATION
* @param raison_appel    : 
* -           CB2A_PROGRAMME_ACQ
* -           CB2A_CHGT_LOGICIEL
* -           CB2A_CHGT_MATERIEL
* -           CB2A_PREMIERE_INIT
* -           CB2A_VIDAGE_TRANS
* -           CB2A_MAJ_PARAM
* -           CB2A_FICHIER_TRANS_PLEIN 
* -           CB2A_REPRISE_INCIDENT
* -           CB2A_APPEL_ACQ
* -           CB2A_MAINT
* @param info_connexion  : informations pour la phase de connexion
* @param cr_services     : compte rendu des derniers services realises lors de la derniere connexion a un centre
* @param date            : date mise a jour
* @param pt_fct          : Pointeur sur les fonctions de controle des TAGS.
// \if SIMULATION
//  @GSIM_F:SERVEUR_demander_service:KSFAM_CB2A:
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:5:ONE_POINTER
//  @GSIM_A:6:ONE_POINTER
// \endif
*
* @link KSFAM_CB2A Back to top @endlink
*/
void SERVEUR_demander_service(unsigned char service_initial,
                             unsigned char raison_appel,
                             SERVEUR_S_CONNEX *info_connexion,
                             SERV_S_CR_SERVICES *cr_services,
							        DATE *date
									,StructFctCb2a *pt_fct
									);

/*------------------------ PRIVE --------------------------*/

/*
**************************************************************
        declarations des typedef
**************************************************************
*/
 

/* informations relatives a la phase de transfert de parametres (TELEPRAM) */

typedef struct 
{
   unsigned char dernier_num_ok;
   unsigned char nb_dde_repet;

} SERVEUR_S_INFO_ERR;

typedef struct 
{
   unsigned char num_repete;   /* numero de message repete par l'acq */
   unsigned char nb_repet;     /* nombre de fois ou le message a ete */
                               /* repete par l'acq */

} SERVEUR_S_INFO_ERR_REPET;

typedef struct 
{
   unsigned char num_deb_fen;  /* 1er numero de message de la fenetre 
                               incorrectement acquittee */
   unsigned char nb_dde_repet; /* nombre de fois ou on a demande la repetition*/

} SERVEUR_S_INFO_ERR_ACQ;

typedef struct
{
   unsigned long nb_msg_ds_fen;
   unsigned long nb_msg_cumul;
   unsigned char erreur;
   unsigned long num_msg_prec;
   unsigned char nb_essais;
   SERVEUR_S_INFO_ERR derniere_err_retour;
   SERVEUR_S_INFO_ERR derniere_err_saut;
   SERVEUR_S_INFO_ERR derniere_err_format;
   SERVEUR_S_INFO_ERR_REPET derniere_err_repet;
   SERVEUR_S_INFO_ERR_ACQ derniere_err_acq;

} SERVEUR_S_INFO_TRANSFERT;

/* informations relatives a la phase de transfert de parametres (TELECOLL) */
typedef struct
{
   /* erreur de repetitions de messages */
   unsigned char err_repet_msg;
   unsigned char dernier_msg_recu; /* dernier msg correctement recu par l'acq*/
   unsigned char nb_repet_msg;     /* nbre de repetitions demandees par l'acq */

   /* erreur de repetitions de remise */
   unsigned char err_repet_rem;
   unsigned char remise_repetee;   /* remise repetee (demandee par l'acq) */
   unsigned char nb_repet_rem;     /* nbre de repetitions demandees par l'acq */

} SERVEUR_S_INFO_TRANS_REM;

/*
**************************************************************
        declarations des define
**************************************************************
*/

/* type de reponse suite a la reception d'un msg de mise a jour */
#define SERVEUR_NE_PAS_REPONDRE       0x0510
#define SERVEUR_REPONDRE_ACQ          0x0511

/* phases pendant un dialogue avec l'acquereur */
#define SERVEUR_DEBUT_DIAL             1
#define SERVEUR_DEBUT_SRV              2 
#define SERVEUR_FIN_SRV_ECHEC          3


/* valeurs prises par l'indicateur de fermeture de dialogue */ 

#define SERVEUR_FERMER_DIAL_FIN_SERV     0x31 /* 1 */
#define SERVEUR_FERMER_DIAL_IMM          0x32 /* 2 */
#define SERVEUR_NE_PAS_FERMER_DIAL       0x33 


/* valeurs prises par l'indicateur de droit de parole */
#define SERVEUR_DP_ACC                   0
#define SERVEUR_DP_ACQ                   1

/* types d'erreurs pendant un transfert de TELEPARAMETRAGE */
#define SERVEUR_PAS_ERR             0
#define SERVEUR_REPETITION_MSG      1
#define SERVEUR_RETOUR_MSG          2
#define SERVEUR_SAUT_MSG            3
#define SERVEUR_ERR_FORMAT_MSG      4
#define SERVEUR_ERR_STOCKAGE        5

/* taille du tableau des tables infructueues car teleparametrees
avec un calcul de sceau incorrect */
#define SERVEUR_MAX_TABLES          29 /* MPE V5.2 */

/* maximum d'essais de teleparametrage pour une table dont 
le calcul de sceau est incorrect */
#define SERVEUR_MAX_ESSAIS          3

/* maximum de repetitions demande pour une erreur de retour en arriere , saut
ou erreur de format pendant un transfert */
#define SERVEUR_MAX_REPET_RETOUR    1
#define SERVEUR_MAX_REPET_SAUT      1
#define SERVEUR_MAX_REPET_FORMAT    1

/* maximum de fois tolerees ou on recoit le meme message */
#define SERVEUR_MAX_REPET_TOLERE    2

/* maximum de repetitions demande pour une erreur de demande d'acq alors
que la fenetre n'est pas atteinte */
#define SERVEUR_MAX_REPET_ERR_ACQ   1

/* type de table teleparametree */
#define SERVEUR_TABLE_SIMPLE        0
#define SERVEUR_TABLE_COMPOSEE      1
#define SERVEUR_TABLE_SPECIALE      2 

/* type d'action suite a la reception d'un message de mise a jour.
On controle ou stocke les donnees */
#define SERVEUR_CONTROLER_DONNEES   0
#define SERVEUR_STOCKER_DONNEES     1

#define SERVEUR_CALCULER_INTEG          0
#define SERVEUR_NE_PAS_CALCULER_INTEG   1

/* rang utilise pour le stockage des enregistrements d'une table composee */
#define SERVEUR_PREMIER_ENREG     0
#define SERVEUR_ENREG_SUIVANT     1

/* maximum de demande de repetitions du meme message tolere pour la TELECOL */
#define SERVEUR_MAX_REPET_MSG_TLC     3

/* maximum de demande de repetitions d'une meme remise pour la TELECOL */
#define SERVEUR_MAX_REPET_REM_TLC     2

/*! @} **/
#endif


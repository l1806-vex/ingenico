/*! @addtogroup KSFAM_M2OS
	* @{
**/
#ifndef APPEL_H
#define APPEL_H

/* definition de la CAM supplementaires */
#define CAM_EXTERNE           "CAM9"
#define CAM0_PERIPH            0
#define CAM1_PERIPH            1
#define CAM2_PERIPH            2
#define CAM9_PERIPH            9

/*! @brief Define the priority for Hybrid reader */
#define CARD_EXTENDED_SUPPORT   0x01
#define SWIPE_EXTENDED_SUPPORT  0x02

/* compte-rendu fonction MO_Request */
#define REQUEST_STOP       1
#define REQUEST_OK         2
#define REQUEST_NSTOP      3
#define REQUEST_NSELECTION 4
#define REQUEST_NAVI       5

/* compte-rendu des fonctions */
#define FCT_OK      0
#define STOP        1

#define AUTO_NON_IMPOSER  0
#define AUTO_IMPOSER      1

/* type des applications */
#define TYP_CARTE  0x8000
#define TYP_CHEQUE 0x4000
#define TYP_SANTE  0x2000
#define TYP_EXPORT 0x1000
#define ALL        0xF000

/* niveau compatibilite gestionnaire */
#define NIV_GEST_V5            0x0004
#define NIV_GEST_PROTOCOLE_E   0x0008
#define NIV_GEST_VITALE        0x0010
#define NIV_GEST_DEMARRE_PISTE 0x0040
#define NIV_GEST_V5_2          0x0080

#define APPEL_EFT30      0xEF30

/*! @brief Define a pointer on a function (entry point). */
typedef int (*POINT_ENTREE) (NO_SEGMENT, void *, void *);

/*! @brief Define a short used as an entry point identity. */
typedef unsigned short E_IDF_PENTREE;

/*! @brief Enumerate the function mode. */
typedef enum {SELECTIVE, ALL_DIFFUSION, STOP_DIFFUSION} MODE_FONCTION;

/*! @brief Define a date format. */
typedef struct
{
  int  year;									/*!< year. */
  char month;									/*!< month. */
  char day;										/*!< day. */
} DATE_EXT;

#define NB_MAX_PENTREE 2

/*! @brief Define a redirection table.*/
typedef struct
{
   TYPE type_appli;										/*!< the type of the application. */
   struct
   {
      unsigned char priorite;					/*!< priority */
      POINT_ENTREE pfonc;							/*!< entry point function. */
   } s_fonction [NB_MAX_PENTREE];			/*!< array of function descriptor. */
} TABLE_REDIRECTION;

/*! @defgroup KSFAM_M2OS_SERVICE    Manager Entry points
	* @{
**/

/*! @brief 
 *
 * Define all entry point of manager.
 *
 * BROADCAST means : all applications are called from highest priority to lowest priority
 *                   highest priority equal 0, lowest priority equal 255
 *
 * SELECTING means : only one application is called
 *
 * POLLING means   : all applications are called from highest priority to lowest priority
 *                   highest priority equal 0, lowest priority equal 255
 *                   The polling is stopped when an application return STOP
 *
**/
#define DEBIT_OVER					0	/*!< SELECTING mode : manager informs the application which has activated a debit transaction that the transaction is over */
#define MORE_FUNCTION				1	/*!< SELECTING mode : processing of functions accessed via F key */
#define IS_TIME_FUNCTION			2   /*!< BROADCAST mode : determines whether a long periodic function is to be performed */
#define TIME_FUNCTION				3   /*!< BROADCAST mode : processing of periodic functions */
#define TIME_FUNCTION_CHAINE		4   /*!< BROADCAST mode : processing of periodic functions ( French Bank domain ) */
#define CONSULT						5   /*!< BROADCAST mode : printout of consultation receipt of application transaction file */
#define MCALL						6   /*!< BROADCAST mode : printout of automatic call schedules (remote collection, etc.) */
#define STATE						7   /*!< BROADCAST mode : printout of application status (whether it is initialized or not) */
#define AUTO_OVER					8   /*!< BROADCAST mode : overrules application authorisation to modify manager parameters */
#define IS_NAME						9   /*!< BROADCAST mode : informs the manager of the application name */
										/*!< SELECTING mode : to put name of application in header */
#define IS_STATE					10	/*!< BROADCAST mode : application status (whether it is initialized or not) */
										/*!< SELECTING mode : application status (whether it is initialized or not) */
#define IS_EVOL_PG					11	/*!< BROADCAST mode : loading or downloading restrictions */
#define IS_CHANGE_INIT				12	/*!< BROADCAST mode : conditions for changing general parameters */
										/*!< SELECTING mode : conditions for changing general parameters */
#define MODIF_PARAM					13	/*!< BROADCAST mode : actions to be carried out after modifying manager parameters. */
#define IS_ORDER					14	/*!< BROADCAST mode : check if PSS message is a message for this application (Health Care domain) */
#define ORDER						15	/*!< SELECTING mode : get and process the PSS message ( Health Care domain )  */
#define IS_SUPPR_PG					16	/*!< SELECTING mode : condition to remove this application  ( Health Care domain )  */
#define IS_INSTALL_PG				17	/*!< SELECTING mode : condition to update this application ( Health Care domain )  */
#define GET_ORDER					18	/*!< SELECTING mode : get application profile ( Health Care domain )   */
#define IS_LIBELLE					19	/*!< BROADCAST mode : allow to take application name  ( Health Care domain ) */
#define IS_DELETE					20	/*!< SELECTING mode : conditions to suppress the application   */
#define EVOL_CONFIG					21	/*!< BROADCAST mode : change in software and hardware configuration ( French Bank domain )  */
#define GIVE_MONEY					22	/*!< BROADCAST mode : get the currencies supported by the application  */
#define IDLE_MESSAGE				23	/*!< SELECTING mode : idle messages displayed by application */
#define COM_EVENT					24	/*!< POLLING mode   : actions to be carried out on COM0 event, COM0 open/close process */
#define MODEM_EVENT					25	/*!< POLLING mode   : actions to be carried out on modem event, modem open/close process */
#define KEYBOARD_EVENT				26	/*!< BROADCAST mode : actions to be carried out when key is pressed and manager is idle ( old ) */
										/*!< SELECTING mode : actions to be carried out when key is pressed and manager is idle ( new ) */
#define GIVE_INFOS_CX				27	/*!< SELECTING mode : get information returned to Cash Register via PSC protocol ( French Bank domain )  */
#define FILE_RECEIVED				28	/*!< BROADCAST mode : actions to be carried out when a parameters file has been received   */
#define MESSAGE_RECEIVED			29	/*!< BROADCAST mode : actions to be carried out when a message is received from the interface  task to all applications  */
										/*!< SELECTING mode : actions to be carried out when a message is received from the interface  task to one application */
#define CARD_INSIDE					30	/*!< SELECTING mode : process the card in transparent mode   */
#define GIVE_INTERFACE				31
#define IS_BIN_CB					32	/*!< BROADCAST mode : informs Manager that the magnetic stripe is CB ( French Bank domain ) */
#define IS_CARD_SPECIFIC			33	/*!< POLLING mode   : allow to take a card transparently  */
#define IS_FOR_YOU_BEFORE			34	/*!< BROADCAST mode : chip card selection  before EMV power on  */
#define GIVE_AID					35	/*!< SELECTING mode : gives to the Manager the list of AIDs supported  */
#define IS_FOR_YOU_AFTER			36	/*!< BROADCAST mode : chip card selection after EMV power on   */
#define IS_CARD_EMV_FOR_YOU			37	/*!< SELECTING mode : ask application supporting the selected AID if it will process this card   */
#define DEBIT_EMV					38	/*!< SELECTING mode : EMV debit transaction processing by chip card   */
#define DEBIT_NON_EMV				39	/*!< SELECTING mode : debit transaction processing by magnetic stripe card ( ISO2 only or  ISO2 + ISO1 or ISO2 + ISO3 track ), non EMV chip card or card manual entry    */
#define SELECT_FUNCTION				40	/*!< SELECTING mode : start a Credit or Cancel transaction ( French Bank domain )     */
#define SELECT_FUNCTION_EMV			41	/*!< SELECTING mode : start a Credit or Cancel EMV transaction ( French Bank domain )      */
#define GIVE_YOUR_DOMAIN 			42	/*!< BROADCAST mode : gives to the Manager the working domain ( Export  ) */
#define AFTER_RESET       	    	43	/*!< BROADCAST mode : processing of actions to be carried out after reset */
#define SELECT_AID					44	/*!< SELECTING mode : allows applications to manage the final step of application selection     */
#define DIAL_RECEPT					45	/*!< SELECTING mode : use to simulate PSS reception ( Health Care domain ) */
#define DIAL_EMISS					46	/*!< SELECTING mode : use to simulate PSS emission ( Health Care domain ) */
#define FALL_BACK 					47	/*!< POLLING mode   : "chip to stripe" processing (if different from the EMV standard fallback)     */
#define IS_LICENCED					48	/*!< SELECTING mode : informs Manager if the application is licensed or not  */
#define TRACK_STREAM				49	/*!< POLLING mode   : allows application to process a magnetic card which is impossible to decode (parity problem....).      */
#define SELECT_AID_EXTENDED			50	/*!< SELECTING mode : allows applications to manage the final step of application selection. To be used instead of SELECT_AID when application needs more information about EMV selection.     */
#define CARD_REMOVAL     			51	/*!< SELECTING mode : manager asks the application which has activated a debit transaction to manage the card removal (for instance, asks the card removal in the  card's owner language).     */
#define CARD_OUTSIDE				52	/*!< BROADCAST mode : Inform applications that card has been removed at idle */
#define GIVE_YOUR_SPECIFIC_CONTEXT	53	/*!< BROADCAST mode : gives manager parameters to customise selection */
#define DEBIT_TPASS			    	54	/*!< BROADCAST mode : process a contact less payment (called when F2 key is pressed after amount keying) */
#define SERVICE_SHORTCUT       		55	/*!< Reserved to MANAGER for shortcut calling */
#define APPEL_TELECOLLECTE     		56 	/*!< BROADCAST mode : Inform applications to make BATCH DATA CAPTURE ( French Bank domain ) */
#define CLESS_GIVE_INFO		  		57  /*!< Reserved to MANAGER CLESS management */
#define CLESS_IS_FOR_YOU       		58  /*!< Reserved to MANAGER CLESS management */
#define CLESS_DEBIT             	59  /*!< Reserved to MANAGER CLESS management */
#define CLESS_DEBIT_AID         	60  /*!< Reserved to MANAGER CLESS management */
#define CLESS_IS_SPECIFIC			61  /*!< Reserved to MANAGER CLESS management */
#define CLESS_INSIDE		   		62  /*!< Reserved to MANAGER CLESS management */
#define GIVE_MONEY_EXTENDED	    	63	/*!< BROADCAST mode : get the currencies supported by the application ( All domain )   */
#define CLESS_END			    	64  /*!< Reserved to MANAGER CLESS management */
#define CLEAR_TRANSACTION_FILE  	65  /*!< Reserved to MANAGER ( French Bank domain )  */
#define SERVICE_SHORTCUT_PRINT  	66	/*!< Reserved to MANAGER for shortcut printing */
#define PRINTER_IDLE_STATUS     	67	/*!< POLLING mode   : call to customise printer idle status (NO PAPER screen for exemple) */
#define PINPAD_IDLE_STATUS      	68	/*!< POLLING mode   : call to customise pinpad idle status (WELCOME screen for exemple) */
#define CLESS_IDLE_STATUS       	69	/*!< POLLING mode   : call to customise CLESS idle status (WELCOME screen for exemple) */
#define GET_IDLE_STATE_PARAMETER 	70	/*!< BROADCAST mode : gives manager parameters to customise idle state   */
#define GET_AMOUNT_STATE_PARAMETER 	71	/*!< BROADCAST mode : gives manager parameters to customise card waiting state   */
#define CUSTOMIZE_MESSAGE       	72  /*!< Reserved to customize the manager messages @include msglib_Sample_01.c  */
#define SELECT_CARD_HOLDER      	74	/*!< SELECTING mode : allows applications to manage the final step of card holder selection  */
#define SELECT_MERCHANT         	75	/*!< SELECTING mode : allows applications to manage the final step of merchant selection   */
#define START_OF_TRANSACTION    	76	/*!< BROADCAST mode : inform applications at the beginning of a transaction    */
#define END_OF_TRANSACTION      	77	/*!< BROADCAST mode : inform applications at the ending of a transaction    */
#define CAISSE_DIVERS_1         	78  /*!< Reserved to MANAGER for FRANFINANCE ( French Bank domain )  */
#define CASH_CARD_REMOVAL 			79	/*!< SELECTING mode : manager asks the application which has activated a cash flow debit transaction to manage the card removal (for instance, asks the card removal in the  card's owner language).     */
#define MAINT_INIT     				80  /*!< Reserved to MANAGER ( Health Care domain )  */
#define MAINT_PRINT    				81  /*!< Reserved to MANAGER ( Health Care domain )  */
#define CUSTOMIZE_CARD_ENTRY        82  /*!< Reserved to customize the waiting card screen */
#define DEBIT_IAM                   83  /*!< POLLING mode   : to start a transaction with DEBIT_IAM_REQUEST message */
#define IS_NAME_EXTENDED            84  /*!< BROADCAST mode : informs the manager of the application name extended up to 38 responses*/
#define WAKE_UP                     85  /*!< BROADCAST mode : Inform applications that terminal has been waked up */
#define MANUAL_ENTRY_EXTENDED 		86	/*!< SELECTING mode : allows applications to manage the manual entry keying. */
#define NB_MAX_SERVICE				100 /*!< Number of last service reserved by MANAGER to manage applications */

/*! @} **/

#define NB_MAX_MONEY            20


#define VAL_INIT    0x20

/* output */
#define REP_OK      0
#define REP_KO      1
#define REP_STOP   2
#define REP_FIN    3

//! \brief Define a private area.
typedef unsigned char ZONE_PRIV[10];
//! \brief Response of the cash register connection.
typedef unsigned char ZONE_REP[55];

#define TRACK2_SUPPORT_MASK     0x01
#define TRACK1_SUPPORT_MASK     0x02
#define TRACK3_SUPPORT_MASK     0x04
#define CHIP_SUPPORT_MASK       0x08
#define OPERATOR_SUPPORT_MASK   0x10
#define CLESS_SUPPORT_MASK      0x20
#define CGUI_MASK               0x40 
#define LUHN_SUPPORT_MASK       0x80

#define CAM0_MASK    			0x01
#define CAM1_MASK    		 	0x02
#define CAM2_MASK    		  	0x04

#ifndef LEN_AID
#define LEN_AID     16
#endif


#ifndef _EXPORT_


/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char nb_reponse;						/*!< number of responses */
	struct
	{ 
		T_AFFNOM  libelle;								/*!< name of the application */
		NO_SEGMENT no_appli;							/*!< number of the application */
		union
		{
			MASQUE        masque;						/*!< mask */
			unsigned char reponse;					/*!< response. */
		} etat;														/*!< state of the application */
	} etat_retour[NB_MAX_APPLI];				/*!< array containing the return state of all the applications */
} S_ETATOUT;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char nb_reponse;						/*!< number of responses */
	struct
	{
		T_AFFNOM_EXTENDED  libelle;								/*!< name of the application */
		char               icone[FS_FILENAMESIZE];				/*!< name of the icon (see GIVE_YOUR_SPECIFIC_CONTEXT) */
		NO_SEGMENT         no_appli;							/*!< number of the application */
		union
		{ 
			MASQUE        masque;						/*!< mask */
			unsigned char reponse;					/*!< response. */
		} etat;														/*!< state of the application */
	} etat_retour[NUMBER_OF_APPLI];			/*!< array containing the return state of all the applications */
} S_ETATOUT_EXTENDED;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char nb_reponse;						/*!< number of responses */
	struct
	{
		NO_SEGMENT no_appli;						/*!< number of the application */
		MASQUE     masque;							/*!< mask */
		MASQUE     touche;							/*!< mask */
	} etat_retour[NB_MAX_APPLI];			/*!< array containing the return state of all the applications */
} S_STATEOUT;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char nb_reponse;					/*!< number of responses */
	struct
	{
		NO_SEGMENT no_appli;						/*!< number of the application */
		MASQUE     masque;							/*!< mask */
		MASQUE     touche;							/*!< mask */
	} etat_retour[NUMBER_OF_APPLI];		/*!< array containing the return state of all the applications */
} S_STATEOUT_EXTENDED;


/*! @brief Manage the entry point GIVE_YOUR_SPECIFIC_CONTEXT. */
// @GSIM_T:S_SPECIFIC_CONTEXT:SUPPLIED(BUF_SER_S_SPECIFIC_CONTEXT;BUF_DES_S_SPECIFIC_CONTEXT)  
typedef struct
{ 
	unsigned char nb_reponse;					/*!< number of responses. */
	struct
	{
		T_AFFNOM    libelle;						/*!< name of the application. */
		NO_SEGMENT  no_appli;						/*!< number of the application. */
		MASQUE      masque;							/*!< mask,MSK_CB2A_MPA 0x000001 (French domain only). */
		MASQUE      type;								/*!< type of application (bank or not bank). */
		MASQUE      support;						/*!< support managed by the application TRACK2_SUPPORT_MASK */
		MASQUE      cam;								/*!< CAM mask : CAM2_MASK 0x04. */
		MASQUE      cgui;                        /*!< Cgui compatibility */
		unsigned char ruf[4];						/*!< reserved for future use. */
	} etat_retour[NB_MAX_APPLI];	
} S_SPECIFIC_CONTEXT;
/*! @brief Manage the entry point GIVE_YOUR_SPECIFIC_CONTEXT. */
// @GSIM_T:S_SPECIFIC_CONTEXT:SUPPLIED(BUF_SER_S_SPECIFIC_CONTEXT;BUF_DES_S_SPECIFIC_CONTEXT)  
typedef struct
{ 
	unsigned char nb_reponse;					/*!< number of responses. */
	struct
	{
		T_AFFNOM    libelle;						/*!< name of the application. */
		NO_SEGMENT  no_appli;						/*!< number of the application. */
		MASQUE      masque;							/*!< mask,MSK_CB2A_MPA 0x000001 (French domain only). */
		MASQUE      type;								/*!< type of application (bank or not bank). */
		MASQUE      support;						/*!< support managed by the application TRACK2_SUPPORT_MASK */
		MASQUE      cam;								/*!< CAM mask : CAM2_MASK 0x04. */
		MASQUE      cgui;                        /*!< Cgui compatibility */
		unsigned char ruf[4];						/*!< reserved for future use. */
	} etat_retour[NUMBER_OF_APPLI];	
} S_SPECIFIC_CONTEXT_EXTENDED;
#else
// same struct, but fields names are in english.
// T_AFFNOM and MASQUE, translated as T_APPNAME and T_MASK,
// used to be defined in nttypes.h

/*! @brief This type define the name of an object (application...). EFT30 like. */
typedef char               T_APPNAME            [12+1];
typedef char               T_APPNAME_EXTENDED   [32+1];

/*! @brief Define a mask (EFT30 like). */
typedef unsigned long      T_MASK;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char response_number;					/*!< number of responses */
	struct
	{
		T_APPNAME   appname;   				/*!< name of the application */
		NO_SEGMENT  no_appli;				/*!< number of the application */
		union
		{
			T_MASK        mask;							/*!< mask */
			unsigned char response;					/*!< response. */
		} state;													/*!< state of the application */
	} returned_state[NB_MAX_APPLI];			/*!< array containing the return state of all the applications */
} S_ETATOUT;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char response_number;					/*!< number of responses */
	struct
	{
		T_APPNAME_EXTENDED  appname;						/*!< name of the application */
		char                iconname[FS_FILENAMESIZE];		/*!< name of the icon (see GIVE_YOUR_SPECIFIC_CONTEXT) */
		NO_SEGMENT          no_appli;						/*!< number of the application */
		union
		{
			T_MASK        mask;								/*!< mask */
			unsigned char response;						/*!< response. */
		} state;														/*!< state of the application */
	} returned_state[NUMBER_OF_APPLI];		/*!< array containing the return state of all the applications */
} S_ETATOUT_EXTENDED;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char response_number;						/*!< number of responses */
	struct
	{
		NO_SEGMENT no_appli;						/*!< number of the application */
		MASQUE     mask;								/*!< mask */
		MASQUE     key;									/*!< mask */
	} returned_state[NB_MAX_APPLI];		/*!< array containing the return state of all the applications */
} S_STATEOUT;

/*! @brief Define a structure describing all the output states of the applications */
typedef struct
{
	unsigned char response_number;			/*!< number of responses */
	struct
	{
		NO_SEGMENT no_appli;							/*!< number of the application */
		MASQUE     mask;									/*!< mask */
		MASQUE     key;										/*!< mask */
	} returned_state[NUMBER_OF_APPLI];	/*!< array containing the return state of all the applications */
} S_STATEOUT_EXTENDED;

/*! @brief Manage the entry point GIVE_YOUR_SPECIFIC_CONTEXT. */
// @GSIM_T:S_SPECIFIC_CONTEXT:SUPPLIED(BUF_SER_S_SPECIFIC_CONTEXT;BUF_DES_S_SPECIFIC_CONTEXT)  
typedef struct
{
	unsigned char response_number;			/*!< number of responses. */
	struct
	{
		T_AFFNOM      appname;						/*!< name of the application. */
		NO_SEGMENT    no_appli;						/*!< number of the application */
		MASQUE        mask;								/*!< mask,MSK_CB2A_MPA 0x000001 (French domain only). */
		MASQUE        type;								/*!< type of application (bank or not bank). */
		MASQUE        support;						/*!< support managed by the application TRACK2_SUPPORT_MASK */
		MASQUE        cam;								/*!< CAM mask : CAM2_MASK 0x04. */
		MASQUE        cgui;                        /*!< Cgui compatibility*/
		unsigned char ruf[4];						/*!< reserved for future use.*/
	} returned_state[NB_MAX_APPLI];
} S_SPECIFIC_CONTEXT;

/*! @brief Manage the entry point GIVE_YOUR_SPECIFIC_CONTEXT. */
// @GSIM_T:S_SPECIFIC_CONTEXT:SUPPLIED(BUF_SER_S_SPECIFIC_CONTEXT;BUF_DES_S_SPECIFIC_CONTEXT)  
typedef struct
{
	unsigned char response_number;			/*!< number of responses. */
	struct
	{
		T_AFFNOM      appname;						/*!< name of the application. */
		NO_SEGMENT    no_appli;						/*!< number of the application */
		MASQUE        mask;								/*!< mask,MSK_CB2A_MPA 0x000001 (French domain only). */
		MASQUE        type;								/*!< type of application (bank or not bank). */
		MASQUE        support;						/*!< support managed by the application TRACK2_SUPPORT_MASK */
		MASQUE        cam;								/*!< CAM mask : CAM2_MASK 0x04. */
		MASQUE        cgui;                        /*!< Cgui compatibility*/
		unsigned char ruf[4];						/*!< reserved for future use.*/
	} returned_state[NUMBER_OF_APPLI];
} S_SPECIFIC_CONTEXT_EXTENDED;

#endif

#ifndef _EXPORT_
/*! @brief Manage an entry point.*/
typedef struct
{
	S_ETATOUT etatout;									/*!< output state (entry point MODEM_EVENT) */
	int       ecart_date;								/*!< date difference */
	int       ecart_heure;							/*!< time difference */
} S_MODIF_P;

#else

/*! @brief Manage an entry point.*/
typedef struct
{
	S_ETATOUT etatout;										/*!< output state (entry point MODEM_EVENT) */
	int       date_difference;						/*!< date difference */
	int       time_difference;						/*!< time difference */
} S_MODIF_P;
#endif

/*! @brief Manage an entry point.*/
typedef struct
{
	int       reason;						/*!< wake-up reason */
} S_WAKE_UP;

/*! @brief Manage an entry point.*/
typedef struct
{
	unsigned char card_holder_nb[19+1];						/*!< holder nb */
	unsigned char expiration_date[4+1];						/*!< expiration date */
	int           status;                                   /*!< status of entry point CR_ENTRY_OK or CR_ENTRY_CANCEL */
}
S_MANUAL_ENTRY;

/*! @brief Give domain informations.*/
typedef struct
{
	unsigned char ident_domaine;					/*!< domain concerned : bank, health... */
	unsigned char ref_domaine1;						/*!< domain 1 reference */
	unsigned char ref_domaine2;						/*!< domain 2 reference */
} S_IDENT_LOG;

/*! @brief Define the output order structure. */
typedef struct
{
	unsigned char nb_reponse;						/*!< response count  */
	struct
	{
		NO_SEGMENT    no_appli;						/*!< number of the application */
		MASQUE        masque;							/*!< mask */ 
		unsigned char reponse;						/*!< response of the application */
	} etat_retour[NB_MAX_APPLI];
} S_ORDEROUT;

#define max_trame_pss 0x8000

/*! @brief This type describe a message.*/
typedef struct
{
	unsigned char  donnees[max_trame_pss];	/*!< data of the message */
	unsigned long  long_mess;								/*!< length of the message */
    unsigned char  PAD_recept;						/*!< reception pad */
	unsigned long  time_exe;								/*!< transmission timeout. */
} S_MESSAGE;

#define REFUS              1
#define SUPPR_OK           0
#define INSTALL_OK         0

/*! @brief This type define an ouput action from an application.*/
typedef struct
{
	NO_SEGMENT no_appli;							/*!< number of the application */
	int        action;								/*!< action of the application */
} S_ACTIONOUT;

/*! @brief Give software informations.*/
typedef struct
{
	S_IDENT_LOG nolog;								/*!< software number */
	int         noversion;						/*!< version number */
} S_IDENT_PG;

/*! @brief Manage the entry point MODEM_EVENT*/
typedef struct
{
	NO_SEGMENT  no_appli;							/*!< number of the application */
	S_IDENT_LOG nolog;								/*!< software number. */
} S_IDENT_OUT; 

/*! @brief Define a name (most of the time, the name of an application) */
typedef char          T_LIBELLE[30];

/*! @brief Manage the entry point IS_LIBELLE */
typedef struct
{
	unsigned char nb_reponse;						/*!< number of response. */
	struct
	{
		T_LIBELLE     libelle;						/*!< name of the application. */
		NO_SEGMENT    no_appli;						/*!< number of the application. */
		unsigned char DateHeure[12];			/*!< date in french format : JJMMAAAAHHMM. */
	} etat_retour[NB_MAX_APPLI];
} S_LIBELLEOUT;

#define REPRISE_OUI    1
#define REPRISE_NON    0

#ifndef _EXPORT_
#define DEL_OUI             1
#define DEL_NON             0
/*! @brief Define a structure containing the deleting character. */
typedef struct
{
	unsigned char effacer;				/*!< deleting character : 
	                                  - DEL_YES 1 to delete, 
	                                  - DEL_NO 0 otherwise. */
} S_DELETE;
#else
#define DEL_YES             1
#define DEL_NO              0

/*! @brief Define a structure containing the deleting character. */
typedef struct
{
	unsigned char deleting;				/*!< deleting character : 
	                                  - DEL_YES 1 to delete, 
	                                  - DEL_NO 0 otherwise. */
} S_DELETE;
#endif

#define MODIF_MAT           1
#define MODIF_LOG           2

/*! @brief This type define an evolution of the settings. */
typedef struct
{
	unsigned char type_modif;			/*!< type of modification : 
	                                 - MODIF_MAT for hardware modification, 
	                                 - MODIF_LOG for software modification. */
} S_EVOL_CONF;

#define NB_MAX_MONAPP          7
//! \brief Define the name of the money (EUR, USD...) */
typedef unsigned char T_NOM_MONEY[3];

/*! @brief Define the code of the money. */
typedef unsigned char T_COD_MONEY[3];

/*! @brief Define the money (name and code). */
typedef struct
{
	T_NOM_MONEY   nom;								/*!< name of the money : 
	                                         - USD, 
	                                         - EUR, 
	                                         - ... */
	T_COD_MONEY   code;								/*!< code of the money. */
	unsigned char posdec;							/*!< decimal position in the amount */
} S_MONEY;

#define CURRENCY_AFTER_AMOUNT    0
#define CURRENCY_BEFORE_AMOUNT   1

/*! @brief Define the money extended informations, complementary with S_MONEY. */
typedef struct
{
	unsigned char cents_separator;			/*!< character used to separate the cents. By default : ',' */
	unsigned char thousands_separator;	/*!< character used to separate the thousands. By default : nothing. */
	unsigned char currency_position;		/*!< position of the currency. By default : after amount. */
} S_MONEY_EXTENDED_INFOS;

/*! @brief Define the money, with all the informations about the name and code (S_MONEY) plus all the extended informations (S_MONEY_EXTENDED_INFOS). */
typedef struct
{
	S_MONEY                  currency;				/*!< informations about the name and the code of the money. */
	S_MONEY_EXTENDED_INFOS   infos;						/*!< extended informations about the money : 
	                                              - cents separator, 
	                                              - thousands separator, 
	                                              - position of the currency 
	                                              - ... */
} S_MONEY_EXTENDED;

/*! @brief Define the basic output money data. */
typedef struct
{
	unsigned char nb_reponse;						/*!< count of different return state */
	struct
	{
		T_AFFNOM      libelle;									/*!< name of the return state. */
		unsigned char nb_money;									/*!< money count */
		S_MONEY       money[NB_MAX_MONAPP];			/*!< array of money basic informations */
	} etat_retour[NB_MAX_APPLI];							/*!< array of return states */
} S_MONEYOUT;

/*! @brief Define the extended output money data. */
typedef struct
{
	unsigned char nb_reponse;							/*!< count of different return state */
	struct
	{
		T_AFFNOM          libelle;								/*!< name of the return state. */
		unsigned char     nb_money;								/*!< money count */
		S_MONEY_EXTENDED  money[NB_MAX_MONAPP];		/*!< array of money extended informations */
	} etat_retour[NB_MAX_APPLI];								/*!< array of return states */
} S_MONEYOUT_EXTENDED;

#define MAX_DATA_ELEMENT 50
#define MAX_ELT_LENGTH		264

/************ DEL pass by value **********/
/*! @brief This type defines a data element.*/
typedef struct
{
	unsigned long	tag ;													/*!< tag of the element. */
	unsigned int	length ;											/*!< length of the element. */
	unsigned char   ptValue[MAX_ELT_LENGTH];		/*!< data of the element. */
} _DataElement_;

/*! @brief This type defines a data element list.*/
typedef struct {
	int			  current;												/*!< index of the current data element. */
	int			  count ;													/*!< count of data elements in the list. */
	_DataElement_ list[MAX_DATA_ELEMENT] ;		/*!< list of MAX_DATA_ELEMENT data elements. */
} _DEL_ ;
/************ DEL pass by value **********/

/*! @brief This type defines a data element.*/
// @GSIM_T:DataElement:DATA_CODE(length + sizeof(int)+sizeof(long))  
typedef struct
{ 
	unsigned long	tag ;							/*!< tag of the element. */
	unsigned int	length ;					/*!< length of the element. */
	unsigned char  *ptValue ;				/*!< pointer to the data of the element. */
} DataElement;

#ifdef _SECDEL_
//DEL structure, with data buffer inside. Safe implementation of DEL      
/*! @brief This type defines a data element list, with data buffer inside. Safe implementation of DEL. */
typedef struct {
	int			current;										/*!< index of the current data element. */
	int			count ;											/*!< count of data elements in the list. */
	DataElement list[MAX_DATA_ELEMENT] ;											/*!< list of MAX_DATA_ELEMENT data elements. */
	unsigned char  ValBuf[MAX_DATA_ELEMENT][MAX_ELT_LENGTH];	/*!< data buffer. */

} DEL ;

#else

// Original implementation of DEL. Memory size optimisation                

/************ DEL pass by address *********/

/*! @brief This type defines a data element list. This is the original implementation of DEL. Memory size optimisation */
typedef struct {
	int			current;													/*!< index of the current data element. */
	int			count ;														/*!< count of data elements in the list. */
	DataElement list[MAX_DATA_ELEMENT] ;			/*!< list of MAX_DATA_ELEMENT data elements. */
} DEL ;
#endif

// C. Ardin 02/03/04 Cst identique France / Export
#define NB_MAX_AID_PAR_APPLI 20
#define NB_MAX_AID_PER_APPLI 20

#define Taille_LABEL	16
/*! @brief Define a label.*/
typedef unsigned char T_LABEL [Taille_LABEL+1];

/*! @brief This type define the language prefix, on 2 characters. */
typedef unsigned char PREF_LANGUE1[2]; /* 2 caracteres */

// Structure representant les elements apres selection d'un AID 
/*! @brief Structure wich describe the elements after a AID selection. */
typedef struct 
{
   unsigned char type_appli;							/*!< type of the application */
   unsigned char aid [LEN_AID];						/*!< AID selected */
   unsigned char libelle [Taille_LABEL];	/*!< name */
   unsigned char lg_libelle;							/*!< length of the name */
   PREF_LANGUE1  code_langue[4];					/*!< language code */
   unsigned char API;											/*!< API */ 
   unsigned char priorite;								/*!< priority */
   unsigned char ASI;											/*!< ASI */
} S_INFO_AID;
// Structure representant la liste avant choix client 
// Melange EMV et non-EMV   
/*! @brief Structure wich describe a list of elements after a AID selection and before the choice of the customer. (EMV and non-EMV). */
typedef struct
{
   int           nb_elt_liste;							/*!< count of element of the list. */
   NO_SEGMENT    no_appli [NB_MAX_APPLI];		/*!< number of the application. */
   S_INFO_AID   elt;												/*!< element of the list. */
} S_INFOS_LISTE_AID ;
// Structure representant les elements apres selection d'un AID pour une appli
/*! @brief Structure wich describe the elements after an AID selection for an application. */
typedef struct
{
   NO_SEGMENT    no_appli ;							/*!< number of the application. */
   S_INFO_AID   elt;										/*!< elements described. */
} S_INFOS_APPLI_AID ;

#ifndef _EXPORT_
// Structure representant un AID
/*! @brief Structure describing an AID.*/
typedef struct
{
   unsigned char lg_aid;							/*!< AID length. */
   unsigned char aid[Taille_LABEL];		/*!< AID described (max. size 16). */
} S_AID;

/*! @brief Enumerate the different support types.*/
typedef enum 
{
	SUPPORT_PISTE2,									/*!< swipe 1 */
	SUPPORT_PISTE12,								/*!< swipe 12 */
	SUPPORT_PISTE32,								/*!< swipe 32 */
	SUPPORT_PUCE,										/*!< chip */
	SUPPORT_MANUEL,									/*!< manual	 */
	SUPPORT_INCONNU,								/*!< unknown */
	SUPPORT_PISTE123,								/*!< swipe 123 */
	SUPPORT_CLESS										/*!< contactless */
} TYPE_SUPPORT;

/*! @brief Enumerate the different type of entry.*/
typedef enum 
{
	SAISIE_MANUELLE,								//!< manual entry */
	SAISIE_CAISSE,									//!< cash register entry */
	SAISIE_AUCUNE										//!< no entry */
} TYPE_SAISIE;

/*! @brief Define the mode of payment.*/
typedef enum 
{
	PAIEMENT_CARTE,									/*!< card payment mode */
	PAIEMENT_CHEQUE,								/*!< cheque payment mode */
	PAIEMENT_INCONNU,								/*!< unknown payment mode */
	PAIEMENT_AUTRES,                                /*!< other payment mode */
	PAIEMENT_CARTE_SANS_CLESS                     /*!<card payment mode with target cless disable*/
} TYPE_MODE_PAIEMENT;

/*! @brief Enumerate the different type of transaction*/
typedef enum 
{
	TRANSAC_DEBIT,									/*!< flow transaction */
	TRANSAC_CREDIT,									/*!< credit transaction */
	TRANSAC_ANNUL_SIMPLE,						/*!< simple cancel transaction */
	TRANSAC_ANNUL_ETENDU,						/*!< extended cancel transaction */
	TRANSAC_PRE_AUTO								/*!< automatic transaction */
} TYPE_TRANSAC;

/*! @brief This type define a Key.*/
typedef int TOUCHE;

/*! @brief This type define the buffer of a track 1.*/
typedef unsigned char BUFFER_PISTE1 [79];

/*! @brief This type define the buffer of a track 2.*/
typedef unsigned char BUFFER_PISTE2 [41];

/*! @brief This type define the buffer of a track 3.*/
typedef unsigned char BUFFER_PISTE3 [107];

/*! @brief This structure describe an input transaction.*/
typedef struct
{
	_DEL_              del;									/*!< data element list */
#ifdef _SIMULPC_
	unsigned char      support;							/*!< type of support  */
    unsigned char      saisie;						/*!< type of entry */
	unsigned char	   paiement;							/*!< mode of payment */
	unsigned char      transaction;					/*!< type of transaction */
#else
	TYPE_SUPPORT       support;							/*!< type of support  */
    TYPE_SAISIE        saisie;						/*!< type of entry */
	TYPE_MODE_PAIEMENT paiement;						/*!< mode of payment */
	TYPE_TRANSAC       transaction;					/*!< type of transaction */
#endif
	MONTANT            montant;						/*!< transaction amount */
	S_MONEY            monnaie;						/*!< transaction currency  ( French domain only ) */
	TOUCHE             periph;						/*!< number of CAM */
	T_NOCAISSE         caisse;						/*!< Cash Register number ( French domain only ) */
    unsigned char      num_applicrt;				/*!< application card number */
	TYPE_SEG	       log_emv[NB_MAX_APPLI];		/*!< EMV login number  */
	int			       nb_log_emv;					/*!< appplications number that accepted this card( French domain only ) */
	unsigned char      cr_mise_sous_tension;		/*!< power_on return code */
	int                auto_force;					/*!< auto-forcing (Y/N) */
	unsigned char      cents_separator;				/*!< cents separator (',' default). */
	unsigned char      thousands_separator;			/*!< thousands separator (nothing default) */
	unsigned char      currency_position;			/*!< position of the currency (after amount default) */
	char               fallback;                    /*!< number of retry before fallback */
	int                cr_iso1;                     /*!< Cr read iso1 */
	int                cr_iso2;                     /*!< Cr read iso2 */
	int                cr_iso3;                     /*!< Cr read iso3 */
	char               big_amount_size;             /*!< different of zero when size amount > 8 */
	char               big_amount[12+1];            /*!< amount when size > 8 */
	char               affiche;                     /*!< pour inhiber l'afichage de l'ecran d'attente carte (0=affichage) */
	char               cless;                       /*!< inhibit cless */
	int                applicationtype;             /*!< application type to select */
	char               extended_support;            /*!< extended support */
	char               support2;                    /*!< second support */
	char               rfu2[3];                     /*!< reserved for future use */
    ZONE_PRIV          zone_privee;					/*!< Private area */
	unsigned char      report_piste;				/*!< track postponement */
	unsigned char      no_dossier[12];				/*!< folder number */
	HISTORIC           historiq;					/*!< historical */
	BUFFER_PISTE1      piste1;						/*!< track 1 buffer */
	BUFFER_PISTE2      piste2;						/*!< track 2 buffer */
	BUFFER_PISTE3      piste3;						/*!< track 3 buffer */
} S_TRANSIN;

/*! @brief This structure associate a list of AID with an application.*/
typedef struct
{
   unsigned char nb_appli;														/*!< number of the application. */
   T_LABEL       AID_list [NB_MAX_AID_PER_APPLI];			/*!< list of 20 AID. */
} S_SELECT_AID;

/*! @brief This structure associate an application with a list of AID, with additional informations (in the data element list).*/
typedef struct
{
  unsigned char nb_appli;											/*!< number of the application. */
  _DEL_       del;														/*!< data element list. */
  S_INFO_AID  elt[NB_MAX_AID_PER_APPLI];			/*!< list of 20 S_INFO_AID elements. */
} S_SELECT_AID_EXTENDED;

/*! @brief define an output AID.*/
typedef struct
{
   NO_SEGMENT    noappli;								/*!< number of the application */
   unsigned char aid_value;							/*!< value of the AID. */ 
} S_AID_OUT;

#define PAIEM_OK         0 /*!< Paiement OK                     */
#define PAIEM_KO         1 /*!< Paiement KO                     */
#define PAIEM_AUTRE_AID  2 /*!< AID refuse                      */
#define PAIEM_EN_COURS   3 /*!< Paiement avec reponse immediate */

/*! @brief Define an output transaction.*/
typedef struct
{
   NO_SEGMENT    noappli;								/*!< number of the application */
   unsigned char cr_paiement;						/*!< payment report : 
                                              - PAIEM_OK 0        : Payment OK 
                                              - PAIEM_KO 1        : Payment KO 
                                              - PAIEM_AUTRE_AID 2 : AID refused 
                                              - PAIEM_EN_COURS 3  : Payment with immediate answer. */
   NO_PORTEUR    no_porteur;						/*!< number of the holder. */
} S_TRANSOUT;
#else

/*! @brief Structure describing an AID.*/
typedef struct
{ 
   unsigned char aid_length;						/*!< AID length. */
   unsigned char aid[16];								/*!< AID described (max. size 16). */
} S_AID;

typedef enum {TRACK2_SUPPORT,TRACK12_SUPPORT,TRACK32_SUPPORT,CHIP_SUPPORT,OPERATOR_SUPPORT,UNKNOWN_SUPPORT,TRACK123_SUPPORT,CLESS_SUPPORT} SUPPORT_TYPE;
typedef enum {MANUAL_ENTRY,CASH_REG_ENTRY,NO_ENTRY} ENTRY_TYPE;
typedef enum {CARD_PAYMENT,CHEQUE_PAYMENT,UNKNOWN_PAYMENT} PAYMENT_MODE;
typedef enum {DEBIT_TR,CREDIT_TR,CANCEL_TR,EXT_CANCEL_TR} TRANSACTION_TYPE;

// DEBIT_TR  debit transaction
// CREDIT_TR credit transaction ( French domain only )
// CANCEL_TR cancel transaction ( French domain only )
// EXT_CANCEL_TR extended cancel transaction ( French domain only )

typedef int KEYSTART;
typedef unsigned char TRACK1_BUFFER [79]; 	/*!< track 1 */
typedef unsigned char TRACK2_BUFFER [41]; 	/*!< track 2 */
typedef unsigned char TRACK3_BUFFER [107];	/*!< track 3 */
typedef struct
{
	_DEL_              del;								/*!< data element list */
#ifdef _SIMULPC_
	unsigned char      support;						/*!< type of support  */
    unsigned char      entry;						/*!< type of entry */
	unsigned char      payment;						/*!< mode of payment */
	unsigned char      transaction;				/*!< type of transaction */
#else
	SUPPORT_TYPE       support;						/*!< type of support  */
    ENTRY_TYPE         entry;						/*!< type of entry */
	PAYMENT_MODE       payment;						/*!< mode of payment */
	TRANSACTION_TYPE   transaction;				/*!< type of transaction */
#endif
	MONTANT            amount;						/*!< transaction amount */
	S_MONEY            currency;					/*!< transaction currency ( French domain only ) */
	KEYSTART           peri;						/*!< number of CAM */
	T_NOCAISSE         cashreg;						/*!< Cash Register number ( French domain only ) */
        unsigned char      cardapplinum;			/*!< application card number */
	TYPE_SEG	   emv_app[NB_MAX_APPLI];			/*!< EMV application type that accepted this card ( French domain only ) */
	int		   emv_app_num;							/*!< appplications number that accepted this card( French domain only ) */
	unsigned char      power_on_result;				/*!< power_on return code */
	int                rfu1;						/*!< reserved for future use */
	unsigned char      cents_separator;				/*!< cents separator (',' default). */
	unsigned char      thousands_separator;			/*!< thousands separator (nothing default) */
	unsigned char      currency_position;			/*!< position of the currency (after amount default) */
	char               fallback;                    /*!< number of retry before fallback */
	int                cr_iso1;                     /*!< Cr read iso1 */
	int                cr_iso2;                     /*!< Cr read iso2 */
	int                cr_iso3;                     /*!< Cr read iso3 */
	char               big_amount_size;             /*!< different of zero when size amount > 8 */
	char               big_amount[12+1];            /*!< amount when size > 8 */
	char               display;                     /*!< To disable display in waiting card state (0=display) */
	char               cless;                       /*!< inhibit cless */
	int                applicationtype;             /*!< application type to select */
	char               extended_support;            /*!< extended support */
	char               support2;                    /*!< second support */
	char               rfu2[3];                     /*!< reserved for future use */
	ZONE_PRIV          private_data;				/*!< Private area (French domain only) */
	unsigned char      report_piste;				/*!< fallback flag ( French domain only ) */
	unsigned char      rfu3[12]; 					/*!< file number ( French domain only ) */
	HISTORIC           historical_bytes;            /*!< historical bytes from chip card power on */
	TRACK1_BUFFER      track1;						/*!< track 1 buffer */
	TRACK2_BUFFER      track2;						/*!< track 2 buffer */
	TRACK3_BUFFER      track3;						/*!< track 3 buffer */
} S_TRANSIN;

/*! @brief This structure associate a list of AID with an application. */
typedef struct
{
   unsigned char nb_appli;														/*!< number of the application. */
   T_LABEL       AID_list [NB_MAX_AID_PAR_APPLI];			/*!< list of 20 AID. */
} S_SELECT_AID;

/*! @brief This structure associate an application with a list of AID, with additional informations (in the data element list). */
typedef struct
{
  unsigned char nb_appli;												/*!< number of the application. */
  _DEL_         del;														/*!< data element list. */
  S_INFO_AID    elt[NB_MAX_AID_PAR_APPLI];			/*!< list of 20 S_INFO_AID elements. */
} S_SELECT_AID_EXTENDED;

/*! @brief define an output AID.*/
typedef struct
{
   NO_SEGMENT    noappli;								/*!< number of the application */
   unsigned char aid_value;							/*!< value of the AID. */
} S_AID_OUT;

#define PAY_OK         0
#define PAY_KO         1
#define PAY_OTHER_AID  2

#define HOLDER_NB NO_PORTEUR
/*! @brief Define an output transaction.*/
typedef struct
{
   NO_SEGMENT    noappli;									/*!< number of the application */
   unsigned char rc_payment;							/*!< payment report : \li PAIEM_OK 0 : Payment OK \li PAIEM_KO 1 : Payment KO \li PAIEM_AUTRE_AID 2 : AID refused \li PAIEM_EN_COURS 3 : Payment with immediate answer. */
   HOLDER_NB     card_holder_nb;					/*!< number of the holder. */
} S_TRANSOUT;
#endif

#define DO_OPEN          0
#define DO_CLOSE         1
#define DO_RECEPT        2

/*! @brief Define an input event.*/
typedef struct
{
	unsigned char action;							/*!< action to perform. */
} S_EVENTIN;

/*! @brief Manage the entry point MODEM_EVENT*/
//@GSIM_T:S_EVENTOUT:DATA_CODE(sizeof(no_appli) + 4)  
typedef struct
{
	NO_SEGMENT  no_appli;							/*!< number of the application */
	FILE       *handle;								/*!< handle of the event. */
} S_EVENTOUT;

/*! @brief This structure is a call on the COM_EVENT entry point. */
typedef struct
{
	unsigned char action;							/*!< action to perform. */
} S_COMIN;


/*! @brief This structure is the response of a call on the COM_EVENT entry point. */
// @GSIM_T:S_COMOUT:DATA_CODE( sizeof(short) + 4 + sizeof(no_appli) )  
typedef struct
{
	NO_SEGMENT      no_appli;						/*!< number of the application */
	FILE           *handle;							/*!< handle */
	unsigned short  cr;									/*!< report */
} S_COMOUT;

/*! @brief Defines a key*/
typedef struct
{
	int    keycode;									/*!< code of the key */
} S_KEY;

/*! @brief Defines an output CX information structure. */
typedef struct
{
	unsigned char presence_REP;						/*!< REP presence. */
	ZONE_REP      zone_REP;								/*!< Response of the cash register connection. */
	unsigned char presence_PRIV;					/*!< PRIV presence. */
	ZONE_PRIV     zone_PRIV;							/*!< PRIV area. */
} S_INFOS_CXOUT;

/*! @brief Defines a file (disk and name)*/
typedef struct
{
	char          volume_name[FS_LABELNAMESIZE];							/*!< name of the disk wich contains the file. */
	char          file_name  [FS_PATHSIZE+FS_FILENAMESIZE];		/*!< name of the file. */
} S_FILE;

/*! @brief Defines an IAM message.*/
typedef struct
{
	unsigned short  sender;							/*!< sender of the message. */
	unsigned short  receiver;						/*!< receiver of the message. */
	unsigned short  type;								/*!< type of the message. */
	unsigned short  length;							/*!< length of the message. */
	unsigned char   value[1024];				/*!< value of the message. */
} S_MESSAGE_IAM;

/*! @brief Defines a (input) buffer.*/
typedef struct
{
	BUFFER_PISTE    piste;							/*!< track buffer */
} S_BIN_IN;

#ifndef _EXPORT_
/*! @brief This structure give the initial configuration : type of application and parameters mask, for each application. */
typedef struct
{
    unsigned char nb_reponse;						/*!< application count */
	struct
	{
	  MASQUE         masque_param;					/*!< parameters mask */
	  unsigned short type_application;			/*!< type of application */
    }etat_retour[NB_MAX_APPLI];						/*!< array of application configuration. */
} S_INITPARAMOUT;

/*! @brief The structure appcarte must contain the priority and name of card application.  */
typedef struct
{
   unsigned char priorite ;							/*!< priority of card application. */
   T_AFFNOM      libelle  ;							/*!< name of card application. */
} S_APPCARTE ;

#define NB_MAX_APPCARTE 4

#define CARD_REFUSEE     0
#define CARD_TRAITEE     5
#define CARD_ACCEPTEE    10
#define CARD_PRIORITAIRE 15

#define MAXI_MONEO       0x10
#define MINI_MONEO       0x03

/*! @brief This structure define if an application need to deal with a card wich accords to the conditions of the application selection in the entry point : 
 * - IS_FOR_YOU_AFTER for a non EMV card
 * - IS_CARD_EMV_FOR_YOU for an EMV card
 * - CLESS_IS_FOR_YOU for a contact less card*/
 
typedef struct
{
   unsigned char nb_reponse;							/*!< number of responses */
   struct
   {
      T_AFFNOM      libelle;							/*!< name of the application */
      NO_SEGMENT    no_appli;							/*!< number of the application */
      unsigned char nb_appcarte;					/*!< if =0 then card rejected */
      S_APPCARTE    appcarte [NB_MAX_APPCARTE];		/*!< Structure containing the priority and name of card application.  */
   } etat_retour [NB_MAX_APPLI];									/*!< return state */
} S_CARDOUT ;

/*! @brief This structure define if an application need to deal non-EMV selection */
typedef struct
{
   unsigned char nb_appcarte;																/*!< if =0 then card rejected */
   unsigned char appvalue;                      						   
   S_APPCARTE    appcarte [NB_MAX_APPLI*NB_MAX_APPCARTE];		/*!< Structure containing the priority and name of card application.  */
} S_SELECT_CARDHOLDER ;

/*! @brief This structure define if an application need to deal non-EMV selection */
typedef struct
{
   unsigned char nb_appcarte;									/*!< if =0 then card rejected */
   unsigned char appvalue;                       
   T_LABEL       appcarte [NB_MAX_APPLI];			/*!< Structure containing the priority and name of card application.  */
} S_SELECT_MERCHANT ;

/*! @brief Define a track 2 stream.*/
typedef struct
{
    int                cr_iso2;						/*!< ISO2 report */
	BUFFER_PISTE2      track2;							/*!< track 2 contents  */
    unsigned char      stream[ISO2_LEN];	/*!< track 2 stream  */
	int                length;							/*!< length of the stream. */
} S_TRACKSTREAM;

#else
/*! @brief This structure give the initial configuration : type of application and parameters mask, for each application. */
typedef struct
{
    unsigned char response_number;					/*!< application count */
    struct
    {
	T_MASK         mask;										/*!< parameters mask */
	unsigned short application_type;				/*!< type of application */
    } returned_state[NB_MAX_APPLI];				/*!< array of application configuration. */
} S_INITPARAMOUT;

#define NB_MAX_CARDAPPLICATION 4
#define CARD_REJECTED    0
#define CARD_PROCESSED   5  /*!< card accepted low priority */
#define CARD_RECOGNIZED 10  /*!< card accepted medium priority */
#define CARD_PRIORITY   15  /*!< card accepted high priority */

/*! @brief The structure appcarte must contain the priority and name of card application.  */
typedef struct
{
   unsigned char priority;							/*!< priority of card application. */
   T_APPNAME     cardappname;						/*!< name of card application. */
} S_APPCARTE ;

/*! @brief This structure define if an application need to deal non-EMV selection */
typedef struct
{
   unsigned char cardappnumber;						/*!< if =0 then card rejected */
   unsigned char appvalue;                   
   S_APPCARTE    appcarte [NB_MAX_APPLI*NB_MAX_CARDAPPLICATION];		/*!< Structure containing the priority and name of card application.  */
} S_SELECT_CARDHOLDER ;

/*! @brief This structure define if an application need to deal non-EMV selection */
typedef struct
{
   unsigned char cardappnumber;					/*!< if =0 then card rejected */
   unsigned char appvalue;                  
   T_LABEL       appcarte [NB_MAX_APPLI];		/*!< Structure containing the priority and name of card application.  */
} S_SELECT_MERCHANT ;

/*! @brief This structure define if an application need to deal with a card wich accords to the conditions of the application selection in the entry point : 
 * - IS_FOR_YOU_AFTER for a non EMV card
 * - IS_CARD_EMV_FOR_YOU for an EMV card
 * - CLESS_IS_FOR_YOU for a contact less card */

typedef struct
{
   unsigned char response_number;							/*!< number of responses */
   struct
   {
      T_APPNAME      appname;									/*!< name of the application */
      NO_SEGMENT    no_appli;									/*!< number of the application */
      unsigned char cardappnumber;						/*!< if =0 then card rejected */
      S_APPCARTE    cardapp [NB_MAX_CARDAPPLICATION];	/*!< Structure containing the priority and name of card application.  */
    } returned_state [NB_MAX_APPLI];					/*!< return state */
} S_CARDOUT ;

/*! @brief Define a track 2 stream.*/
typedef struct
{
    int                cr_iso2;								/*!< ISO2 report */
		TRACK2_BUFFER      track2;								/*!< track 2 contents  */
    unsigned char      stream[ISO2_LEN];			/*!< track 2 stream  */
	int                length;									/*!< length of the stream. */
} S_TRACKSTREAM;

#endif

/*! @brief Give informations about the priority level. */
typedef struct
{
	unsigned char bucEnable;						/*!< enable or disable priority */
	unsigned char ucPriority;						/*!< priority level  */
} S_ENABLE_PRIOR;

/*! @brief Give informations about the Cless configuration. */
typedef struct
{
  S_ENABLE_PRIOR stRestartCless;							/*!< Priority informations about restart with Cless */
  S_ENABLE_PRIOR stRestartWithoutCless;				/*!< Priority informations about restart without Cless */
  _DEL_          del;													/*!< data element list  */
} S_CLESS_GIVEINFO;

/* Values for cr_process in S_CLESSDEBITAIDOUT structure */
#define C_CLESS_CR_END					 					0
#define C_CLESS_CR_RSTART				 					1
#define C_CLESS_CR_RSTART_WITHOUTCLESS		                2
#define C_CLESS_CR_REMOVEAID			 				    3
#define C_CLESS_CR_RSTART_WITHOUTCLESS_CHIP                 4
#define C_CLESS_CR_RSTART_WITHOUTCLESS_SWIPE                5

/*! @brief Give informations about the priority level. */
typedef struct
{
   S_TRANSIN     transin;							/*!< input parameter  */
   S_MESSAGE_IAM message;							/*!< input parameter  */
} S_TRANSIN_IAM;

/*! @brief Define a Cless output AID transaction.*/
typedef struct
{
  S_TRANSOUT  debitaidout;						/*!< output transaction */
	int         cr_process;							/*!< progress report : \li C_CLESS_CR_END \li C_CLESS_CR_RSTART \li C_CLESS_CR_RSTART_WITHOUTCLESS \li C_CLESS_CR_REMOVEAID */
} S_CLESSDEBITAIDOUT;

/*! @brief Manage the entry point GET_IDLE_STATE_PARAMETER*/
typedef struct
{
	S_STATEOUT param_out;							/*!< output parameter. */
} StructGetIdleStateParameter;

/*! @brief Manage the entry point IS_TIME_FUNCTION*/
typedef struct
{
	S_ETATOUT param_out;							/*!< output parameter. */
} StructIsTimeFunction;

/*! @brief Manage the entry point IS_NAME*/
typedef struct
{
	S_ETATOUT param_out;							/*!< output parameter. */
} StructIsName;

/*! @brief Manage the entry point IS_NAME_EXTENDED*/
typedef struct
{
	S_ETATOUT_EXTENDED param_out;							/*!< output parameter. */
} StructIsNameExtended;

/*! @brief Manage the entry point IS_STATE*/
typedef struct
{
	S_ETATOUT param_out;							/*!< output parameter. */
} StructIsState;

/*! @brief Manage the entry point IS_EVOL_PG*/
typedef struct
{
	S_ETATOUT param_out;							/*!< output parameter. */
} StructIsEvolPg;

/*! @brief Manage the entry point IS_CHANGE_INIT*/
typedef struct
{
	S_ETATOUT param_out;							/*!< output parameter. */
} StructIsChangeInit;

/*! @brief Manage the entry point MODIF_PARAM*/
typedef struct
{
	S_MODIF_P param_in;								/*!< input parameter. */
} StructModifParam;

/*! @brief  Manage the entry point IS_ORDER.*/
typedef struct
{
	S_IDENT_LOG param_in;								/*!< input parameter */
	S_ORDEROUT  param_out;							/*!< output parameter  */
} StructIsOrder;

/*! @brief  Manage the entry point ORDER*/
typedef struct
{
	S_MESSAGE param_in;								/*!< input parameter  */
} StructOrder;

/*! @brief  Manage the entry point IS_SUPPR_PG */
typedef struct
{
	S_IDENT_LOG  param_in;							/*!< input parameter  */
	S_ACTIONOUT  param_out;							/*!< output parameter  */
} StructIsSupprPg;

/*! @brief  Manage the entry point IS_INSTALL_PG*/
typedef struct
{
	S_IDENT_PG   param_in;							/*!< input parameter  */
	S_ACTIONOUT  param_out;							/*!< output parameter  */
} StructIsInstallPg;

/*! @brief  Manage the entry point GET_ORDER*/
typedef struct
{
	S_IDENT_OUT  param_out;							/*!< output parameter  */
} StructGetOrder;

/*! @brief  Manage the entry point IS_LIBELLE */
typedef struct
{
	S_LIBELLEOUT  param_out;						/*!< output parameter  */
} StructIsLibelle;

/*! @brief  Manage the entry point IS_DELETE */
typedef struct
{
	S_DELETE  param_out;							/*!< output parameter  */
} StructIsDelete;

/*! @brief  Manage the entry point EVOL_CONFIG */
typedef struct
{
	S_EVOL_CONF  param_in;							/*!< input parameter  */
} StructEvolConfig;

/*! @brief  Manage the entry point GIVE_MONEY */
typedef struct
{
	S_MONEYOUT  param_out;							/*!< output parameter  */
} StructGiveMoney;

/*! @brief  Manage the entry point GIVE_MONEY_EXTENDED */
typedef struct
{
	S_MONEYOUT_EXTENDED  param_out;					/*!< output parameter  */
} StructGiveMoneyExtended;

/*! @brief  Manage the entry point COM_EVENT */
typedef struct
{
	S_COMIN    param_in;							/*!< input parameter  */
	S_COMOUT   param_out;							/*!< output parameter  */
} StructComEvent;

/*! @brief  Manage the entry point MODEM_EVENT */
typedef struct
{
	S_EVENTIN  param_in;							/*!< input parameter  */
	S_EVENTOUT param_out;							/*!< output parameter  */
} StructModemEvent; 

/*! @brief  Manage the entry point KEYBOARD_EVENT */
typedef struct
{
	S_KEY param_in;									/*!< input parameter  */
	S_KEY param_out;								/*!< output parameter  */
} StructKeyboardEvent;

/*! @brief  Manage the entry point GIVE_INFOS_CX */
typedef struct
{
	S_INFOS_CXOUT param_out;						/*!< output parameter  */
} StructGiveInfosCx;

/*! @brief  Manage the entry point FILES_RECEIVED */
typedef struct
{
	S_FILE param_in;								/*!< input parameter  */
} StructFileReceived;

/*! @brief  Manage the entry point MESSAGE_RECEIVED */
typedef struct
{
	S_MESSAGE_IAM param_in;							/*!< input parameter  */
} StructMessageReceived;

/*! @brief  Manage the entry point IS_BIN_CB */
typedef struct
{
	S_BIN_IN      param_in;							/*!< input parameter  */
	S_ETATOUT     param_out;						/*!< output parameter  */
} StructIsBinCb;

/*! @brief  Manage the entry point IS_CARD_SPECIFIC */
typedef struct
{
	S_ETATOUT     param_out;						/*!< output parameter  */
	S_TRANSIN     param_in;							/*!< input parameter  */
} StructIsCardSpecific;

/*! @brief  Manage the entry point GET_AMOUNT_STATE_PARAMETER*/
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_STATEOUT     param_out;						/*!< output parameter  */
} StructGetAmountStateParameter;

/*! @brief  Manage the entry point CARD_INSIDE */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructCardInside;

/*! @brief  Manage the entry point IS_FOR_YOU_BEFORE */
typedef struct
{
	S_ETATOUT     param_out;						/*!< output parameter  */
	S_TRANSIN     param_in;							/*!< input parameter  */
} StructIsForYouBefore;

/*! @brief  Manage the entry point GIVE_YOUR_TYPE */
typedef struct
{
	S_INITPARAMOUT  param_out;						/*!< output parameter  */
} StructGiveYourType;

/*! @brief  Manage the entry point AFTER_RESET */
typedef struct
{
	S_TRANSOUT      param_out;						/*!< output parameter  */
} StructAfterReset;

/*! @brief  Manage the entry point GIVE_AID */
typedef struct
{
	_DEL_           param_out;						/*!< output parameter  */
	S_TRANSIN       param_in;							/*!< input parameter  */
} StructGiveAid;

/*! @brief  Manage the entry point IS_FOR_YOU_AFTER */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_CARDOUT     param_out;						/*!< output parameter  */
} StructIsForYouAfter;

/*! @brief  Manage the entry point CARD_EMV_FOR_YOU */
typedef struct
{
	S_AID         param_in;							/*!< input parameter  */
	S_CARDOUT     param_out;						/*!< output parameter  */
} StructIsCardEmvForYou;

/*! @brief  Manage the entry point DEBIT_EMV */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructDebitEmv;

/*! @brief  Manage the entry point DEBIT_NON_EMV*/
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructDebitNonEmv;

/*! @brief  Manage the entry point DEBIT_TPASS */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructDebitTpass;

/*! @brief  Manage the entry point SELECT_FUNCTION */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructSelectFunction;

/*! @brief  Manage the entry point SELECT_FUNCTION_EMV */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructSelectFunctionEmv;

/*! @brief  Manage the entry point SELECT_AID */
typedef struct
{
	S_TRANSIN            param_in;					/*!< input parameter  */
	S_SELECT_CARDHOLDER  param_out;					//!< output parameter  */
} StructSelectCardHolder;

/*! @brief  Manage the entry point SELECT_AID */
typedef struct
{
	S_TRANSIN            param_in;					/*!< input parameter  */
	S_SELECT_MERCHANT    param_out;					/*!< output parameter  */
} StructSelectMerchant;

/*! @brief  Manage the entry point SELECT_AID */
typedef struct
{
	S_SELECT_AID  param_in;							/*!< input parameter  */
	S_AID_OUT     param_out;						/*!< output parameter  */
} StructSelectAid;

/*! @brief  Manage the entry point FALL_BACK */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;							/*!< output parameter */
} StructFallBack;

/*! @brief  Manage the entry point FALL_BACK */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
} StructCardOutside;

/*! @brief  Manage the entry point IS_LICENCED*/
typedef struct
{
	S_ETATOUT param_out;							/*!< output parameter  */
} StructIsLicenced;

/*! @brief  Manage the entry point TRACK_STREAM */
typedef struct
{
  S_TRACKSTREAM param_in;								/*!< input parameter  */
  S_TRANSIN     param_out;							/*!< output parameter  */
} StructTrackStream;

/*! @brief  Manage the entry point SELECT_AID_EXTENDED */
typedef struct
{
	S_SELECT_AID_EXTENDED  param_in;				/*!< input parameter  */
	S_AID_OUT           param_out;					/*!< output parameter  */
} StructSelectAidExtended;		

/*! @brief  Manage the entry point GIVE_YOUR_CONTEXT */
typedef struct
{
	S_SPECIFIC_CONTEXT    param_out;				/*!< output parameter  */
} StructGiveyourcontext;

/*! @brief  Manage the entry point CLESS_GIVE_INFO */
typedef struct
{
	S_TRANSIN           param_in;						/*!< input parameter  */
	S_CLESS_GIVEINFO    param_out;					/*!< output parameter  */
} StructClessGiveInfo;

/*! @brief  Manage the entry point CLESS_IS_FOR_YOU */
typedef struct
{
	_DEL_        param_in;							/*!< input parameter  */
	S_CARDOUT    param_out;							/*!< output parameter  */
} StructClessIsForYou;

/*! @brief  Manage the entry point CLESS_DEBIT*/
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter  */
	S_TRANSOUT    param_out;						/*!< output parameter  */
} StructClessDebit;

/*! @brief  Manage the entry point CLESS_DEBIT_AID */
typedef struct
{
	S_TRANSIN     param_in;									/*!< input parameter  */
	S_CLESSDEBITAIDOUT  param_out;					/*!< output parameter  */
} StructClessDebitAid;

/*! @brief  Manage the entry point APPEL_TELECOLLECTE */
typedef struct		
{
	S_ETATOUT param_out;							/*!< output parameter  */
} StructAppelTelecollecte;

/*!  \brief  Manage the entry point START_OF_TRANSACTION */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter */
} StructStartOfTransaction;

/*!  \brief  Manage the entry point END_OF_TRANSACTION */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter */
	S_TRANSOUT    param_out;						/*!< output parameter */
} StructEndOfTransaction;

/*! \brief Manage the entry point MORE_FUNCTION */
typedef struct
{
	S_ETATOUT_EXTENDED param_in;	  							/*!< input parameter.*/
} StructMoreFunction;

/*!  \brief  Manage the entry point END_OF_TRANSACTION */
typedef struct
{
	S_TRANSIN     param_in;							/*!< input parameter */
	S_TRANSOUT    param_out;						/*!< output parameter */
} StructCaisseDivers1;

/*!  \brief  Manage the entry point END_OF_TRANSACTION */
typedef struct
{
	S_TRANSIN_IAM   param_in;						/*!< input parameter */
	S_TRANSOUT      param_out;						/*!< output parameter */
} StructDebitIam;

/*!  \brief  Manage the entry point END_OF_TRANSACTION */
typedef struct
{
	S_WAKE_UP   param_in;						/*!< input parameter */
} StructWakeUp;

/*!  \brief  Manage the entry point MANUAL_ENTRY_EXTENDED */
typedef struct
{
	S_MANUAL_ENTRY   param_out;						/*!< output parameter */
} StructManualEntry;

/*! @brief This type is a union of all the entry point with additional information.*/
typedef struct
{
	unsigned short type_code;								/*!< type of code */
	unsigned short service;									/*!< service ID */
	union
	{
		/* DEBIT_OVER              */
		/* MORE_FUNCTION           */
        StructMoreFunction    MoreFunction;
		/* IS_TIME_FUNCTION        */
		StructIsTimeFunction  IsTimeFunction;
		/* TIME_FUNCTION           */
		/* TIME_FUNCTION_CHAINE    */
		/* CONSULT                 */
		/* MCALL                   */
		/* STATE                   */
		/* AUTO_OVER               */
		/* IS_NAME                 */
		StructIsName            IsName;
		/* IS_STATE                */
		StructIsState           IsState;
		/* IS_EVOL_PG              */
		StructIsEvolPg          IsEvolPg;
		/* IS_CHANGE_INIT          */
		StructIsChangeInit      IsChangeInit;
		/* MODIF_PARAM             */
		StructModifParam        ModifParam;
		/* IS_ORDER                */
		StructIsOrder           IsOrder;
		/* ORDER                   */
		StructOrder             Order;
		/* IS_INSTALL_PG           */
		StructIsInstallPg       IsInstallPg;
		/* IS_SUPPR_PG             */
		StructIsSupprPg         IsSupprPg;
		/* GET_ORDER               */
		StructGetOrder          GetOrder;
		/* IS_LIBELLE              */
		StructIsLibelle         IsLibelle;
		/* IS_DELETE               */
		StructIsDelete          IsDelete;
		/* EVOL_CONFIG             */
		StructEvolConfig        EvolConfig;
		/* GIVE_MONEY              */
		StructGiveMoney         GiveMoney;
		/* IDLE_MESSAGE            */
		/* COM_EVENT               */
		StructComEvent          ComEvent;
		/* MODEM_EVENT             */
		StructModemEvent        ModemEvent;
		/* KEYBOARD_EVENT          */
		StructKeyboardEvent     KeyboardEvent;
		/* GIVE_INFOS_CX           */
		StructGiveInfosCx       GiveInfosCx;
		/* FILE_RECEIVED           */
		StructFileReceived      FileReceived;
		/* MESSAGE_RECEIVED        */
		StructMessageReceived   MessageReceived;
		/* CARD_INSIDE             */
        StructCardInside        CardInside;
		/* CARD_OUTSIDE            */
        StructCardOutside       CardOutside;
		/* IS_BIN_CB               */
		StructIsBinCb           IsBinCb;
		/* IS_CARD_SPECIFIC        */
		StructIsCardSpecific    IsCardSpecific;
		/* IS_FOR_YOU_BEFORE       */
		StructIsForYouBefore    IsForYouBefore;
		/* GIVE_AID                */
		StructGiveAid           GiveAid;
		/* IS_FOR_YOU_AFTER        */
		StructIsForYouAfter     IsForYouAfter;
		/* IS_CARD_EMV_FOR_YOU     */
		StructIsCardEmvForYou   IsCardEmvForYou;
		/* DEBIT_EMV               */
		StructDebitEmv          DebitEmv;
		/* DEBIT_NON_EMV           */
		StructDebitNonEmv       DebitNonEmv;
		/* SELECT_FUNCTION         */
		StructSelectFunction    SelectFunction;
		/* SELECT_FUNCTION_EMV     */
		StructSelectFunctionEmv SelectFunctionEmv;
		/* GIVE_YOUR_TYPE          */
		StructGiveYourType      GiveYourType;
		/* AFTER_RESET             */
		StructAfterReset        AfterReset;
		/* SELECT_AID              */
		StructSelectAid         SelectAid;
		/* FALL_BACK               */
		StructFallBack          FallBack;
		/* IS_LICENCED             */	/* PBE : Serveur Licence 04-979 */
		StructIsLicenced        IsLicenced;
		/* TRACK STREAM            */
	    StructTrackStream       TrackStream;
		/* SELECT_AID_EXTENDED     */  	/* MF  : Selection bis   05-20394 */
		StructSelectAidExtended SelectAidExtended;
		/* GIVE YOUR SPECIFIC CONTEXT */
		StructGiveyourcontext   GiveYourSpecificContext;
		/* DEBIT_TPASS             */
		StructDebitTpass        DebitTpass;
		/* CLESS_GIVE_INFO             */
		StructClessGiveInfo     ClessGiveInfo;
		/* CLESS_IS_FOR_YOU           */
		StructClessIsForYou     ClessIsForYou;
		/* CLESS_DEBIT             */
		StructClessDebit        ClessDebit;
		/* CLESS_DEBIT_AID            */
		StructClessDebitAid     ClessDebitAid;
		/* IS_CARD_SPECIFIC        */
		StructIsCardSpecific    ClessIsSpecific;
		/* CARD_INSIDE             */
        StructCardInside        ClessInside;
		/* GIVE_MONEY              */
		StructGiveMoneyExtended GiveMoneyExtended;
		/*APPLI_TELECOLLECTE       */
		StructAppelTelecollecte   AppelTelecollecte;
		/* PRINTER_IDLE_STATUS */
		/* PINPAD_IDLE_STATUS */
		/* CLESS_IDLE_STATUS */
		/* GET_IDLE_STATE_PARAMETER    */
		StructGetIdleStateParameter  GetIdleStateParameter;
		/* GET_AMOUNT_STATE_PARAMETER    */
		StructGetAmountStateParameter  GetAmountStateParameter;
		/* SELECT_CARD_HOLDER          */
		StructSelectCardHolder      SelectCardHolder;
		/* SELECT_MERCHANT            */
		StructSelectMerchant        SelectMerchant;
		/* START_OF_TRANSACTION    */
        StructStartOfTransaction   StartOfTransaction;
		/* END_OF_TRANSACTION      */
        StructEndOfTransaction   EndOfTransaction;
		/* CAISSE_DIVERS_1*/
		StructCaisseDivers1      CaisseDivers1;
		/* DEBIT_IAM */
		StructDebitIam      DebitIam;
		/* IS_NAME_EXTENDED */
		StructIsNameExtended IsNameExtended;
		/* WAKE_UP */
		StructWakeUp      WakeUp;
		/* MANUAL_ENTRY_EXTENDED */
		StructManualEntry      ManualEntry;
	} Param;												//!< union of all the entry point.
} StructPt;

/*! @brief This type is a union of all the entry point. */
typedef struct
{
	union
	{
		
		S_ETATOUT               IsTimeFunction;						/*!< IS_TIME_FUNCTION        */
		S_ETATOUT               IsName;								/*!< IS_NAME                 */
		S_ETATOUT               IsState; 							/*!< IS_STATE                */
		S_ETATOUT               IsEvolPg;							/*!< IS_EVOL_PG              */
		S_ETATOUT               IsChangeInit;						/*!< IS_CHANGE_INIT          */
		S_ORDEROUT              IsOrder;							/*!< IS_ORDER                */
		S_MONEYOUT              GiveMoney;							/*!< GIVE_MONEY              */
		S_LIBELLEOUT            IsLibelle;							/*!< IS_LIBELLE              */
		S_ETATOUT               IsBinCb;							/*!< IS_BIN_CB               */
		S_ETATOUT               IsCardSpecific;						/*!< IS_CARD_SPECIFIC        */
		S_ETATOUT               IsForYouBefore;						/*!< IS_FOR_YOU_BEFORE       */
		S_CARDOUT               IsForYouAfter;						/*!< IS_FOR_YOU_AFTER        */
		S_INITPARAMOUT          GiveYourType;						/*!< GIVE_YOUR_TYPE          */
		S_SPECIFIC_CONTEXT      GiveYourSpecificContext;			/*!< GIVE YOUR SPECIFIC CONTEXT */
        S_CARDOUT               ClessIsForYou;						/*!< CLESS_IS_FOR_YOU           */
		S_ETATOUT               ClessIsSpecific;					/*!< IS_CARD_SPECIFIC        */
		S_MONEYOUT_EXTENDED     GiveMoneyExtended;					/*!< GIVE_MONEY_EXTENDED     */
		S_ETATOUT               AppelTelecollecte;					/*!< APPLI_TELECOLLECTE       */
        S_STATEOUT              GetIdleStateParameter;				/*!< GET_IDLE_STATE_PARAMETER        */
		S_STATEOUT              GetAmountStateParameter;			/*!< GET_AMOUNT_STATE_PARAMETER        */
		S_ETATOUT_EXTENDED      IsNameExtended;                     /*!< IS_NAME_EXTENDED                 */
	} Param;														/*!< union of variables associated with entry points.*/
} StructPtBis;

/* PBE : Gestion PACK  */
#define	CAR_MAX_PACK_VERSION		        3
#define	CAR_MAX_PACK_NAME			       20
#define	CAR_MAX_PACK_CRC			        5
#define	CAR_MAX_PACK_PATCH			        3
#define	CAR_MAX_PACK_AMENDEMENT			3


#ifdef WIN32
#undef _MAX_PATH 
#undef _MAX_DRIVE 
#undef _MAX_DIR 
#undef _MAX_FNAME 
#undef _MAX_EXT 
#endif

#define _MAX_PATH   FS_DISKNAMESIZE+FS_FILENAMESIZE+2  /*!< max. length of full pathname */
#define _MAX_DRIVE  3                                  /*!< max. length of drive component */
#define _MAX_DIR    FS_LABELNAMESIZE                   /*!< max. length of path component */
#define _MAX_FNAME  FS_FILENAMESIZE                    /*!< max. length of file name component */
#define _MAX_EXT    16                                 /*!< max. length of extension component */


/*! @brief Define an hPack type.*/
typedef struct {
  unsigned char version[CAR_MAX_PACK_VERSION];				/*!< version of the Pack.*/
  unsigned char name[CAR_MAX_PACK_NAME];							/*!< name of the pack.*/
  unsigned char crc[CAR_MAX_PACK_CRC];								/*!< crc of the pack.*/
  unsigned char patch[CAR_MAX_PACK_PATCH];						/*!< patch*/
  unsigned char amendement[CAR_MAX_PACK_AMENDEMENT];	/*!< amendment.*/
}hPack_t;

//PBE : Gestion PACK 
/*! @brief Define a structure which describe a pack.*/
typedef struct DescripPack_t{
  unsigned long	 FileType;									/*!< type of the file.*/
  unsigned char	 FileName[16];							/*!< name of the file.*/
  unsigned long  TypeAppli;									/*!< type of the application concerned.*/
}DescripPack_t;

/*! @brief Describe basic information about a file.*/
typedef struct {
  unsigned char  name[_MAX_FNAME];						/*!< file name component*/
  unsigned char  ext[_MAX_EXT];								/*!< extension component	*/
  unsigned short crc[CAR_MAX_PACK_CRC];				/*!< CRC*/
}prod_t;

/*! @brief This function calls a service known of the manager registred by an application using ServiceRegister.
 * @param mode : 
 * - SELECTIVE (SELECTING) : 
 *      only call the application with the rank noappli. 
 *
 * - ALL_DIFFUSION (BROADCAST) :
 *      call all applications of the same type 
 *      call applications from highest to lowest priority (255 is the lowest priority)
 *      loading order is respected for applications with the same priority
 *
 * - STOP_DIFFUSION (POLLING) :
 *      call all applications of the same type 
 *      call the applications from highest to lowest priority (255 is the lowest priority)
 *      loading order is respected for applications with the same priority
 *      stop the call when one of the application answer STOP in response.
 *
 * @param type : Type of the application :
 * - TYP_CARTE  0x8000
 * - TYP_CHEQUE 0x4000
 * - TYP_SANTE  0x2000
 * - TYP_EXPORT 0x1000
 * - ALL        0xF000 
 *
 * @param noappli : Rank of the application in case of SELECTIVE mode. Parameter not significant in the ALL_DIFFUSION and STOP_DIFFUSION cases.
 * @param service : Service to call 
 *
 * @link KSFAM_M2OS_SERVICE Back to top @endlink
 *
 * @param param_in,param_out : Parameters send to the application. Depends of the service called .
 * @return 
 * - REQUEST_NSELECTION : the service can't be called.
 * - REQUEST_STOP       : OK in STOP_DIFFUSION mode.
 * - REQUEST_NSTOP      : no application has stopped the call in STOP_DIFFUSION mode.
 * - REQUEST_OK         : OK in ALL_DIFFUSION and SELECTIVE mode.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 2) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:MO_Request:KSFAM_M2OS:0xC2
//  @GSIM_A:5:DATA_CODE(strlen(param_in)+1)
//  @GSIM_A:6:DATA_CODE(strlen(param_out)+1)
// \endif
extern int            MO_Request (MODE_FONCTION mode,TYPE type,NO_SEGMENT noappli,E_IDF_PENTREE service,void *param_in,void *param_out);
//! @}
/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

/*! @brief This function splits a path name into its individual components
 * @param path  : pointer to path name to be parsed
 * @param drive : pointer to buffer for drive component, if any
 * @param dir   : pointer to buffer for subdirectory component, if any
 * @param fname : pointer to buffer for file base name component, if any
 * @param ext   : pointer to buffer for file name extension component, if any
 * @return None
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 34) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:splitpath:KSFAM_AUTRES_MANAGER:0x0C
// \endif
extern void           splitpath (char *path,char *drive,char *dir,char *fname,char *ext);


#endif /* APPEL_H */
/*! @} **/

/*! @addtogroup KSFAM_PSQ
	* @{
**/
#ifndef PARAM_H
#define PARAM_H


#define CLESS_INTERNE    (255)
#define INTERNAL_TYPE    CLESS_INTERNE
#define SERIAL_TYPE      0
#define USB_TYPE         5

#define PARAM_FILE       "PARAM.TXT"
#define PARAM_FILE_EXT   "PARAMEXT.TXT"
#define PARAM_FILE_REPLI "PARAMREP.TXT"
#define PARAM_APN        "PARAMAPN.TXT"
#define COMP_FILE        "COMP.TXT"
#define PROT_FILE        "PROT.TXT"
#define STATE_FILE_PARAM "STATE.TXT"

#define LABEL_TICKET                       "SEQ_TICKET"
#define LABEL_APPLI_REPONSE                "SEQ_APPLI_REPONSE"
#define LABEL_ENVOI_REPONSE                "SEQ_ENVOI_REPONSE"
#define LABEL_EVOL_ENCOURS                 "SEQ_EVOL_ENCOURS"
#define LABEL_REPRISE_SUPPR_LOG            "SEQ_REPRISE_SUPPR_LOG"
#define LABEL_SEQ_ETAT                     "SEQ_ETAT"
#define LABEL_SUPPR_LOG                    "SEQ_SUPPR_LOG"
#define LABEL_MONTANT                      "SEQ_MONTANT"
#define LABEL_BIG_AMOUNT                   "SEQ_BIG_AMOUNT"
#define LABEL_DEVISE                       "SEQ_DEVISE"
#define LABEL_NIVEAU                       "SEQ_NIVEAU"
#define LABEL_DATE                         "SEQ_DATE_SV"
#define LABEL_ACTIV_LICENCE                "SEQ_ACTIV_LICENCE"		/* PBE : Serveur Licence 04-979 */
#define LABEL_NO_SERV_LICENCE              "SEQ_NO_SERV_LICENCE"	 /* PBE : Serveur Licence 04-979 */
#define LABEL_PAS_APPEL_LICENCE            "SEQ_PAS_APPEL_LICENCE"	 /* PBE : Serveur Licence 04-979 */
#define LABEL_COLOR                        "SEQ_COLOR"
#define LABEL_PINPAD_MODE                  "SEQ_PINPAD_MODE"
#define LABEL_LLT_MODE                     "SEQ_LLT_MODE"
#define LABEL_PINPAD_MODE_COMPATIBILITY    "SEQ_COMPATIBILITY"
#define LABEL_HWCNF_DATA                   "HW_CF_AP"

/* Liste des services que le gestionnaire utilise pour ses propres moyens */
#define SERVICE_DEBIT_GESTIONNAIRE               100
#define SERVICE_CLOSE_ALL_PERIPH                 101
#define SERVICE_DOWNLOAD_GESTIONNAIRE            110
#define SERVICE_DIAGNOSTIC_GESTIONNAIRE          111
#define SERVICE_LICENCING_GESTIONNAIRE           112
#define SERVICE_DOWNLOAD_FROM_GESTIONNAIRE       113
#define SERVICE_MORE_FUNCTION_GESTIONNAIRE       114
#define SERVICE_DOWLOAD_IST                      115 
#define SERVICE_DISPLAY_GOAL                     116
#define SERVICE_DISPLAY_GOAL_LEDS                117
#define SERVICE_DISPLAY_GOAL_HEADER				  118
#define SERVICE_DISPLAY_GOAL_FOOTER				  119
#define SERVICE_DOWLOAD_IPP					  120
#define SERVICE_ETAT_LICENCE                     999
#define SERVICE_ECRIRE_NO_CONTRAT_TEMP           998
#define SERVICE_IS_FONCTION_LICENCE_ACTIVATED    997
#define SERVICE_INIT_GESTIONNAIRE               0x1300
#define SERVICE_PROTOCOLE_GESTIONNAIRE          0x1301
#define SWI_FCLOSE                              0x1313
#define SWI_FOPEN                               0x1314
#define SWI_EMV_APDU     						0x1332
#define SWI_EMV_POWER_ON     					0x1335
#define SWI_EMV_APDU_HOOK						0x1332
#define SWI_EMV_POWER_ON_HOOK					0x1335
#define SWI_EMV_APDU_UNHOOK						(SWI_EMV_APDU_HOOK+0x8000)
#define SWI_EMV_POWER_ON_UNHOOK					(SWI_EMV_POWER_ON_HOOK+0x8000)
#define SWI_POWERED                             0x1380
#define SWI_DLLLINK                             0x1350
#define SWI_DOWNLOAD                            0x1375

#define SERVICE_SRED_PCIPTS                     200

/*v5rr pour la table des bins*/
#define TYPE_GESTIONNAIRE  2
#define TYPE_LOG_BANCAIRE  3
#define TYPE_LOG_CHEQUE    4
#define AMERICAN_EXPRESS   5
#define CETELEM_PASS       6
#define DINERS             7
#define COFINOGA           8
#define JCB                10
#define CREDITPAR_SOVAC    11
#define ACCORD_FINANCES    12
#define TYPE_LOG_UCM       18
#define TYPE_LOG_SESAME    18
#define TYPE_LOG_SECURISE  19
#define TYPE_LOG_EMVDC     96
#define TYPE_SRED		 0xAE38

/* GYPE_YOUR_SPECIFIC_CONTEXTE */
#define TYPE_APPLI_NON_BANCAIRE 1
#define TYPE_APPLI_SANTE        2

/*! @brief Return of PSQ_GetSDKInfos function */
#define TELIUM_SDK_FILE_NOT_EXIST                   1
#define TELIUM_SDK_FILE_TS_PACK_TYPE_INCORRECT      2
#define TELIUM_SDK_FILE_TS_PACK_VERSION_INCORRECT   3
#define TELIUM_SDK_FILE_M_PACK_TYPE_INCORRECT       4
#define TELIUM_SDK_FILE_M_PACK_VERSION_INCORRECT    5
#define TELIUM_TS_PACK_FILE_NOT_EXIST               7
#define TELIUM_M_PACK_FILE_NOT_EXIST                8

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief This type is used to give information about the current telium pack.*/
typedef struct
{
  unsigned char telium_manager_name[CAR_MAX_PACK_NAME];					//!< Telium manager name.
  unsigned char telium_manager_version[CAR_MAX_PACK_VERSION];			//!< Telium manager version.
  unsigned char telium_manager_amendement[CAR_MAX_PACK_AMENDEMENT];		//!< Telium manager amendment.
  unsigned char telium_manager_crc[CAR_MAX_PACK_CRC];					//!< Telium manager CRC.
  unsigned char telium_system_name[CAR_MAX_PACK_NAME];					//!< Telium system name.
  unsigned char telium_system_version[CAR_MAX_PACK_VERSION];			//!< Telium system version.
  unsigned char telium_system_amendement[CAR_MAX_PACK_AMENDEMENT];		//!< Telium system amendment.
  unsigned char telium_system_crc[CAR_MAX_PACK_CRC];					//!< Telium system CRC.
}Pack_Infos_Telium;

/*! @brief This type is used to give information about the current telium SDK.*/
typedef struct
{
  unsigned char telium_SDK_release[3*CAR_MAX_PACK_NAME];				                  //!< Telium SDK release
  unsigned char telium_M_PACK_version[CAR_MAX_PACK_VERSION+CAR_MAX_PACK_AMENDEMENT];  //!< Telium manager pack version.
  unsigned char telium_TS_PACK_version[CAR_MAX_PACK_VERSION+CAR_MAX_PACK_AMENDEMENT]; //!< Telium system pack version
}SDK_Infos_Telium;

/*! @brief Define the basic TAB_ informations.*/
typedef struct
{
   char         *nom;								//!< name
   char         *val;								//!< value
   char          type;								//!< type
} TAB_NOMVAL [76];


/*! @brief Define the basic wTAB_ informations.*/
typedef struct
{
   MSGinfos     nom;								/*!< name*/
   MSGinfos     val;								/*!< value*/
   char         type;								/*!< type*/
} wTAB_NOMVAL [76];

/*! @brief Define access to several functions.*/
typedef struct
{
  int			itemlabel;								/*!< label of an item*/
  PFONCNAVI		function;							/*!< navigation function.*/
  MASQUE		masque;									/*!< navigation mask for access to the name*/
  void			*ad_valeur;							/*!< value to modify*/
  char          type;								/*!< type of value*/
} NavigationInit;

//divers
#define MSK_SYSTV5   0x0008

#define TYPE_NON   0
#define TYPE_OUI    1

#define	TYPE_CLE		 0x00
#define	TYPE_RTC		 0x01
#define	TYPE_GSM		 0x02
#define	TYPE_RNIS		 0x03
#define	TYPE_EXT		 0x04
#define	TYPE_GSM_INT	 0x05
#define	TYPE_GPRS		 0x06
#define TYPE_MODEM_HOTE  0x07
#define	TYPE_ERR		 0x10


//for network key
#define DOUBLE90_NON    0
#define DOUBLE90_OUI    1

#define F_NUL			0
#define F_STRING		1
#define F_OUINON		2
#define F_CAISSE 		3
#define F_RESEAU		4
#define F_LANGUE		5
#define F_ISO			6
#define F_PINPAD		7
#define F_MDP			8
#define F_MONEY			9
#define F_PROTOCOLE     10
#define F_INT           11
#define F_IP            12
#define F_LIAISON       13
#define F_LOGIN 		14
#define F_PASSWORD      15
#define F_SEP           16
#define F_SSL           17
#define F_C30           18
#define F_IDENTIFIANT	19
#define F_NO_PAD     	20
#define F_NO_CENTRE    	21
#define F_PORT          22
#define F_DOMAIN       23
/*****************************/

//defines for initialisation
#define PARAM_NOT_IMPLEMENTED -1
#define INIT_OK				   0
#define INIT_KO				   1
#define MODIF_IMPOSSIBLE	   2
#define ANNUL				   3
#define RESTER				   4
#define VALID				   5
#define INIT_VAL			   6
#define INIT_SK1			   7

//defines for ticket
/*! @brief Define to inhibit ticket.*/
/*! Set flag to manage ticket printing.*/
#define	INHIBIT_UPDATE_SOFTWARE_TICKET_BEFORE_DOWNLOAD   0x00000001		/*!< If set, don't print the ticket before downloading action*/
#define	INHIBIT_UPDATE_SOFTWARE_TICKET_AFTER_DOWNLOAD    0x00000002		/*!< If set, don't print the ticket after donwloading action*/
#define	INHIBIT_UPDATE_SOFTWARE_TICKET_REFUSED           0x00000004		/*!< If set, don't print the ticket when an application refuse donwloading action*/
#define	INHIBIT_INITIALISATION_TICKET                    0x00000008		/*!< If set, don't print the initialization ticket of manager (F+INITIALIZATION)*/
#define	INHIBIT_INITIALISATION_REFUSED                   0x00000010		/*!< If set, don't print the ticket when an application refuse the initialization (F+INITIALIZATION)*/
#define	INHIBIT_DOWNLOAD_M2OS_TICKET                     0x00000020		/*!< If set, don't print the ticket of M2OS after a dowload manager*/
#define	INHIBIT_DOWNLOAD_DLL_TICKET                      0x00000040		/*!< If set, don't print the ticket of DLL after a dowload dll*/
#define	INHIBIT_DOWNLOAD_SYSTEM_TICKET                   0x00000080		/*!< If set, don't print the ticket of SYSTEM after a dowload system*/
#define  INHIBIT_DOWLOAD_SOFTWARE_TICKET                 0x00000100  /*!< If set, an application doesn't print his ticket after a dowload */

//parameters
/*! @brief Define the terminal number type.*/
typedef char NO_TERMIN  		[3+1];
/*! @brief Define the standard type.*/
/* @GSIM_T:T_STANDARD:SUPPLIED(BUF_SER_T_STANDARD;BUF_DES_T_STANDARD) */
typedef char T_STANDARD			[16+1];
/*! @brief Define the password type.*/
typedef char T_MDP				[15+1];
/*! @brief Define the serial number type.*/
typedef char NO_SERIE			[20+1];
/*! @brief Define the reader number type.*/
typedef char NO_LECTEUR			[2+1];
/*! @brief Define the download code type.*/
typedef char CODE_TLCH			[4+1];

/*
======================================================================
			Data Structures Definition
======================================================================
*/
/* hardware informations for French Bank domain  */
/*! @brief This type gives the hardware informations for French Bank domain.*/
typedef struct
{
 unsigned char mod_equip  					 [3];						/*!< for the 46th field, type DF50 */
 unsigned char no_log_seq 					 [8];						/*!< AxxxVVAA*/
 unsigned char no_log_sys						 [8];						/*!< AxxxVVAA*/
 unsigned char va_log_sys 					 [6];						/*!< VAVAVA*/
 NO_SERIE 	   no_serie;														/*!< Serial number.*/
 unsigned char nb_cam                   ;						/*!< ASCII*/
 unsigned char taille_mem 					 [6];						/*!< total memory size (in Kbytes).*/
 unsigned char nb_app_priv					 [2];						/*!< the private bank */
 unsigned char typ_archi  					 [2];						/*!< independent or concentrate type of architecture, defined by the manager.*/
 unsigned char taille_mem_flash      [6];						/*!< size of the flash memory*/
 unsigned char taille_mem_flash_rest [6];						/*!< size of the free flash memory*/
 unsigned char taille_mem_ram        [6];						/*!< size of the RAM.*/
 unsigned char taille_mem_ram_rest   [6];						/*!< size of the free RAM.*/
 unsigned char materiel_coupleur     [4];						/*!< hardware card reader.*/
 unsigned char log_coupleur          [4];						/*!< software card reader.*/
 unsigned char no_spec_coupl         [4];						/*!< non specific reader.*/
} S_EQUIPEMENT;


/*! @brief Parameters of initialisation manager*/
typedef struct
{
  struct
  { 
    int 		    format_date;						/*!< Date format.*/
    int 		    langue;									/*!< language.*/
    NO_TERMIN 	no_terminal;						/*!< terminal number*/
    S_MONEY		  monnaie;								/*!< informations about the money.*/
    int			    flag_standard;					/*!< standard flag*/
    T_STANDARD	no_standard;						/*!< standard number.*/
    int			    pin_pad;								/*!< pinpad*/
    int		 	    type_pinpad;						/*!< type of the pinpad*/
    int			    swipe;									/*!< type of swipe*/
    NO_SERIE	  no_serie;								/*!< serial number*/
    int 		    flag_no_serie;					/*!< flag serial number*/
    NO_LECTEUR	no_lecteur;							/*!< reader number.*/
    /* FT 461 = Network type IP fallback */
    int			    type_reseau_repli;			/*!< network withdrawal type.*/
    /* FT 461 = reply YES / NO             */
    int			    repli;									/*!< withdrawal YES/NO*/
    int			    cb_com;									/*!< type of network*/
    int			    liaison_serie;					/*!< serial connection*/
    int 		    caisse;									/*!< cash register*/
    /******************************************************/
    /* Telechargement RTC                                 */
    /* Telechargement X25                                 */
    /* Telechargement IP                                  */
    /******************************************************/
    int			  type_res;												/*!< type of network : \li RTC, \li X25, \li IP download.*/
    int			  f_manager; // MF : 06/06/2002		/*!< blok access fct initialisation manager*/
    /******************************************************/
    /* Telechargement RTC :                               */
    /*           Numero MDP                               */
    /* Telechargement X25 :                               */
    /*           Numero PAD                               */
    /* Telechargement IP  :                               */
    /*           Adresse IP xxx.xxx.xxx.xxx               */
    /******************************************************/
    T_MDP		  no_mdp;													/*!< \li if RTC download : MDP number \li if X25 download : PAD number \li if IP download : IP address xxx.xxx.xxx.xxx*/
    /******************************************************/
    /* Telechargement RTC :                               */
    /*           Non-utilise                              */
    /* Telechargement X25 :                               */
    /*           Adresse X25                              */
    /* Telechargement IP  :                               */
    /*           Port xxxx                                */
    /******************************************************/
    T_TRANSPAC	  no_transpac;							/*!< \li if RTC download : unused \li if X25 download : X25 address \li if IP download : port xxxx*/
    T_CONTRAT	  no_contrat;									/*!< contract number*/
    int			  tlch_protege ;								/*!< protected download (Y/N)*/
    CODE_TLCH	  code_tlch;									/*!< download code*/
    unsigned char apn[LG_APN];							/*!< APN*/
    unsigned char pincode[LG_PIN];					/*!< PIN code*/
    unsigned char login[LG_LOGIN];					/*!< login*/
    unsigned char password[LG_PASSWORD];		/*!< login*/
    unsigned int  passerelle;								/*!< gateway*/
    unsigned int  ip;												/*!< IP address*/
    unsigned int  port;											/*!< port xxxx*/
    unsigned int  type_pad;									/*!< type of pinpad*/
    unsigned char presence_c30;							/*!< C30 presence (Y/N)*/
    unsigned char liaison_serie_c30;				/*!< C30 serial connection*/
    unsigned char modem_sur_socle;					/*!< modem on its base (Y/N)*/
    unsigned char dtr;											/*!< DTR Y/N*/
    unsigned char presence_swipe;						/*!< swipe presence*/
    unsigned char activ_gprs;
  }val;
    CRC crc;																/*!< CRC.*/
} S_OLD_PARAM;

//! \brief Manager init parameters
typedef struct
{
  struct
  { 
    T_MDP		  no_mdp_tms;																/*!< seller ID (size : 15+1)*/
    unsigned int  ip_tms;																/*!< TMS IP address (size : 4)*/
    unsigned int  port_tms;															/*!< TMS port (size : 4)*/
		unsigned int  liaison_serie_tms;										/*!< TMS serial link (size : 4)*/
    unsigned char login_tms[LG_LOGIN];									/*!< TMS login (size : 22+1)*/
    unsigned char password_tms[LG_PASSWORD];						/*!< TMS password (size : 22+1)*/
		unsigned char apn_tms[LG_APN];											/*!< TMS APN (size : 22+1)*/
		unsigned char maint_password[8+1];									/*!< password for the TMS parameters access (size : 8+1)*/
		unsigned char ligne1[16+1];													/*!< message line 1*/
		unsigned char ligne2[16+1];													/*!< message line 2*/
    unsigned char profil_ssl_tms[PROFILE_NAME_SIZE];		/*!< SSL profile.*/
    unsigned char ruf[120-(16+1)-(16+1)-(8+1)-(Taille_ADR_RACCORD+4)-(4+10)-(4+11)-11];  /*!< reserved for future use (size : 24).*/
    int           presence_ssl_reseau;									/*!< SSL network available (Y/N).*/
    unsigned char profil_ssl_reseau[PROFILE_NAME_SIZE];	/*!< SSL network profile*/
    unsigned int  forcage_v32;													/*!< pad number*/
    unsigned char pad_forcage_v32[Taille_ADR_RACCORD];		/*!< is pad v32 forced ?*/
    unsigned int  forcage_prefixe;							/*!< is prefix forced ?*/
    unsigned char prefixe [10];													/*!< prefix*/
    int           presence_ssl_tms;											/*!< SSL_tms available (Y/N)*/
		int           indice_profil_ssl_tms;								/*!< SSL_tms profile index*/
	
  }val;
  CRC crc;													//!< CRC.
} S_NEW_PARAM;

/*! @brief Define the withdrawal parameters*/
typedef struct
{
  struct
  { 
	unsigned char apn[LG_APN];													/*!< APN , size 22+1*/
	unsigned int  liaison_serie;												/*!< serial connection*/
    unsigned char login[LG_LOGIN];										/*!< login.*/
    unsigned char password[LG_PASSWORD];							/*!< password.*/
    unsigned int  passerelle;													/*!< gateway.*/
    unsigned int  ip;																	/*!< IP address*/
    unsigned int  port;																/*!< port xxxx*/
    unsigned int  type_pad;														/*!< type of pinpad*/
    int           presence_ssl;												/*!< SSL available (Y/N)*/
    unsigned char profil_ssl[PROFILE_NAME_SIZE];			/*!< SSL profile*/
    unsigned char modem_sur_socle;										/*!< modem on its base Y/N)*/
    unsigned char dtr;																/*!< dtr informations*/
    unsigned int  forcage_v32;												/*!< v32 forced (Y/N)*/
    unsigned char pad_forcage_v32[MAX_RACCORD];				/*!< PAD v32 forced (Y/N)*/
    unsigned int  forcage_prefixe;										/*!< forcing prefix*/
    unsigned char prefixe [10];												/*!< prefix*/
  }val;
  CRC crc;																						/*!< CRC.*/
} S_REPLI_PARAM;

/*! @brief Defines the APN parameters*/
typedef struct
{
  struct
  { 
    unsigned char apn[GPRS_APN_LGR+1];							/*!< APN , size 100+1*/
    unsigned char apn_repli[GPRS_APN_LGR+1];				/*!< withdrawal APN , size 100+1*/
    unsigned char apn_tms[GPRS_APN_LGR+1];					/*!< tms APN , size 100+1*/
    unsigned char entry_type;
    unsigned char domain_name[257];
    unsigned char ruf[254];					/*!< reserved for future use*/
  }val;
  CRC crc;																					/*!< CRC.*/
} S_APN_PARAM;

/*! @brief Defines the APN parameters. All timeout are in 1/100 seconds */
#define COMPATIBILITY_NUMBER  20
typedef struct
{
  int  TimeOutNoPaper;                   /*!< Timeout to display no paper*/
  int  DisplayEuroSymbol;                /*!< 1 if display euro symbol instead of EUR*/
  int  TimeOutAmountGlobal;              /*!< Global timeout for amount*/
  int  TimeOutAmountInterCharacter;      /*!< Timeout between two charactere in amount entry*/
  int  TimeOutWaitingCardBeforeAmount;   /*!< Timeout for payment before amount entry*/
  int  TimeOutWaitingCardAfterAmount;    /*!< Timeout for payment after amount entry*/
  int  TimeOutDisplayMessage;            /*!< Timeout to see a message on screen*/
  int  TimeOutRemoveCard;                /*!< Timeout to wait for card remove*/
  int  HeaderActivated;                  /*!< Header activated*/
  int  KeyboardEvent;                    /*!< keyboard_event management 0=new 1=old*/
  int  Compatibility;                    /*!< 0 if next paramaters must be set to default*/
  int  ForceHeader;                      /*!< Force header managment*/
  int  HeaderPosition;                   /*!< Header position (0 up default, 1 down)*/
  int  HeaderWidth;                      /*!< Header width */
  int  HeaderHeight;                     /*!< Header Height*/
  int  FooterActivated;                  /*!< Header activated*/
  int  BeepOn;                           /*!< BIP ON if non-zero*/
  int  Beep;                             /*!< BIP every key pressed */
                                         // Four bytes
                                         // Note = One byte
                                         // 	#define C			0	(DO)
                                         // 	#define C_SHARP		1	(DO#)
                                         // 	#define D			2	(RE)
                                         // 	#define D_SHARP		3	(RE#)
                                         // 	#define E			4	(MI)
                                         // 	#define F			5 	(FA)
                                         // 	#define F_SHARP		6	(FA#)
                                         // 	#define G			7	(SOL)
                                         // 	#define G_SHARP		8	(SOL#)
                                         // 	#define A			9	(LA)
                                         // 	#define A_SHARP		10	(LA#)
                                         // 	#define B			11	(SI)
                                         // Octave = One byte
                                         // Duration = Two bytes (1/100 s)
                                         // Ex : 0x09040005 => A of octave 4 for 50ms
  int  TypeArchitecture;                 /*!< Type d'architecture (PSQ_Donner_reference)*/
  int  CardBeepOn;                       /*!< BIP ON if non-zero*/
  int  CardBeep;                         /*!< BIP every key pressed */
  int  UseBackgroundColor;               /*!<  Use Background color instead of default BMP (0 (default)=NO)*/
  int  FooterPosition;                   /*!<  Footer Position 0=DOWN,1=RIGHT,2=LEFT*/
  int  KeyboardActivated;                /*!<Keyboard activated*/
  int  IPPBackgroundColor;               /*!<  Define Background color for Color IPP */
  int  NbTryRemoteDownload;              /*!<Number of try to remote download  (default)=5)*/
  int  TicketEvent;                      /*!<Tag to mask ticket*/
  int  FullTicket;                       /*!<Tag to print full ticket*/
  int  UseNetworkName;                   /*!<Tag to display NetworkName in header default = 0 */
                                         // In header for GPRS network
                                         // SimProvider is known
                                         //   ==> UseNetworkName = 0, display SimProvider
                                         //   ==> UseNetworkName = 1, display NetworkName
                                         // SimProvider is not known
                                         //   ==> display NetworkName
  int  PowerBeepOn;                      /*!< BIP ON if non-zero*/
  int  PowerBeep;                        /*!< BIP every key pressed */
  int  ManageSwipeError;                 /*!< disable DEF_SEP,DEF_NUM       */
                                         //   ==> ManageSwipeError = 0, enable DEF_SEP,DEF_NUM (default)
                                         //   ==> ManageSwipeError = 1, disable DEF_SEP,DEF_NUM
  int  StopClessBefore;                  /*!< Stop Cless before retry reading Swipe */
                                         //   ==> StopClessBefore = 0, Stop Cless before retry reading Swipe (default)
                                         //   ==> StopClessBefore = 1, Dont stop Cless before retry reading Swipe
  int  NbTrySwipe;                       /*!< While error reading swipe */
  int  ISTBackgroundColor;               /*!<  Define Background color for IST1XX */
  int  ModelEquipment;                   /*!<  Define Model Equipment (PSQ_Donner_reference) */
  int  OldCompatibility;                 /*!< Old value before start-up*/
  int  StartCam0       ;                 /*!< Enable transaction with card in CAM0 at startup*/
  int  StartCam1;                        /*!< Enable transaction with card in CAM1 at startup*/
  int  StartCam2;                        /*!< Enable transaction with card in CAM2 at startup*/
  int  StartCam9;                        /*!< Enable transaction with card in CAM9 at startup*/
  int  DisableYellowDot;                 /*!< Enable/Disable DOT+YELLOW*/
  int  NbTryBeforeFallBack;              /*!< Number of CAM reading before fallback */
  int  EnableCamManagement;              /*!< Enable GetGeneralStatus Management at startup */
                                         //   ==> EnableCamManagement = 0, (default)
                                         //   ==> EnableCamManagement = 1, Enable GetGeneralStatus Management at startup
  int  EnablePinpadManagement;           /*!< Enable Pinpad managment on IWL2XX */
                                         //   ==> EnablePinpadManagement = 0, (default)
                                         //   ==> EnablePinpadManagement = 1, Pinpad managment on IWL2XX
  int  TimeoutWaitingCamAfterSwipeEvent; /*!< Timeout for CAM After SWIPE (Hybrid Reader Only) */
  int  TimeoutWaitingSwipeAfterCamEvent; /*!< Timeout for SWIPE After CAM (Hybrid Reader Only) */
  int  CamSwipePriority;                 /*!< Choose support priority (Hybrid Reader Only) */
  int  PincodeBeepOn;                    /*!< BIP ON if non-zero*/
  int  PincodeBeep;                      /*!< BIP for pincode entry (IWL350) */
  int  DisableCamSwipe;                  /*!< Disable CAM/SWIPE at idle state */
  int  EnableF3F4;                       /*!< Enable F3/F4 in entry list */
  int  ManualSelectionKey;               /*!< Key code for manual transaction selection (default=T_F) */
  char ToBeContinued[4*5];               // RUF : 5 more parameters
} S_STATE_PARAM;

typedef struct
{
  S_STATE_PARAM val;
  CRC           crc;									/*!< CRC.*/
} S_FILE_STATE_PARAM;

/*
======================================================================
			DEFINITION OF TELIUM MANAGER PARAMETERS 
======================================================================
*/
//! \brief Define all the manager initialization parameters.
typedef struct
{
  struct
  {
    S_OLD_PARAM   old_val;							  /*!< manager initialization parameters*/
    //ADD FOR PM 3200 
    S_NEW_PARAM   new_val;							  /*!< new manager initialization parameters (added for PM 3200)*/
    // END -    PM 3200
    // FT 461          
    S_REPLI_PARAM repli_val;						//!< network withdrawal parameters
    //FT 3698-3700     
    S_APN_PARAM   new_apn;
  }val;
  CRC          crc;												/*!< crc*/
} S_PARAM;


/*
======================================================================
			default value for the manager parameters
======================================================================
*/

/* date format  */
#define format_defaut		0
/* language */
#define langue_defaut		FRANCAIS

/* MASQUE for parameters to be initialised or not */
#define NB_MAX_PARAM	18

#define MSK_ALL				0xFFFFFFFF

#define MSK_TOUS_PARAM		0x7FFFF
#define MSK_ALL_PARAM		0x7FFFF

#define MSK_PROTOCOLE		0x80000
#define MSK_FICHPARAM		0x40000
#define MSK_DATE			0x20000
#define MSK_FRMT_DATE		0x10000
#define MSK_LANGUE			0x08000
#define MSK_NO_TERM			0x04000
#define MSK_MONNAIE			0x02000
#define MSK_STANDARD		0x01000 /* to get acces to PABX standard menu */
#define MSK_PINPAD			0x00800
#define MSK_TYPE_PPAD		0x00400
#define MSK_SWIPE			0x00200
#define MSK_NO_SERIE		0x00100
#define MSK_NO_LECT			0x00080
#define MSK_VITESSE			0x00040
#define MSK_C30    		    0x00020
#define MSK_CHAINAGE		0x00020
#define MSK_TYPE_RESEAU		0x00010
#define MSK_DTR				0x00008
#define MSK_CAISSE			0x00004
#define MSK_MDP			    0x00002 /* to get access to TMS menu */
#define MSK_TLCH_PROTEGE	0x00001
#define MSK_NULL			0x00000

//Mask for idle state 
#define INHIBIT_AMOUNT_ENTRY                0x00000001 /*!< inhibit amount keying*/
#define INHIBIT_IDLE_MANUAL_ENTRY           0x00000002 /*!< Inhibit manual entry*/
#define INHIBIT_LAST_AMOUNT                 0x00000004 /*!< Inhibit Last amount recall*/
#define INHIBIT_MONEY_SELECTION             0x00000008 /*!< Inhibit money selection*/
#define INHIBIT_IDLE_AUTHOR_SELECTION       0x00000010 /*!< Inhibit force author selection*/
#define ACTIV_BIG_AMOUNT_ENTRY              0x00000020 // activ entry of big amount (10 max)
//Mask for amount state
#define INHIBIT_AMOUNT_MANUAL_ENTRY         0x00010000 /*!< Inhibit manual entry*/
#define INHIBIT_CLESS_SELECTION             0x00020000 /*!< Inhibit CLESS selection*/
#define INHIBIT_CHECK_SELECTION             0x00040000 /*!< Inhibit Check selection*/
#define INHIBIT_CANCEL_SELECTION            0x00080000 /*!< Inhibit cancel selection*/
#define ACTIV_AMOUNT_AUTHOR_SELECTION       0x00100000 /*!< activ force author selection*/
#define ACTIV_BIG_AMOUNT_TRANSACTION        0x00200000 /*!< activ entry of big amount (10 max)*/
#define ACTIV_EXPLICIT_TRANSACTION          0x00400000 /*!< activ explicit transaction (F2 key)*/
#define ACTIV_SPECIFIC_DISPLAY              0x00800000 /*!< activ specific display*/
#define ACTIV_SPECIFIC_SELECTION            0x01000000 /*!< activ specific selection*/
#define INHIBIT_CLESS_KEY_SHUTDOWN          0x02000000 /*!< Inhibit cancel selection*/

/*
======================================================================
			Initialisation of Date and Time
======================================================================
*/

#define menu_regler_date	0
#define menu_regler_heure	1
#define menu_format_date	2

#define format_defaut	0
#define format_us		1
#define format_chinois  2
#define format_deutch   3

#define french_format  format_defaut
#define us_format      format_us
#define chinese_format format_chinois
#define german_format  format_deutch

/*
======================================================================
			initialisation of Language
======================================================================
*/
#define langue_francais		0
#define langue_english		1
#define MAX_LANGUE         10
#define T_LANGUE          12+1

/*
======================================================================
			initialisation No terminal  
======================================================================
*/

/*
======================================================================
			initialisation Standard  
======================================================================
*/
#define sans_standard   0
#define avec_standard   1
#define standard_alpha  2

#define avant_standard 0
#define apres_standard 1

#define dtmf          0
#define impulsionelle  1

#define AVANT 1
#define APRES 2

#define STNON	1
#define STOUI	2
#define STREF	3
#define STINF	4

/*
======================================================================
			initialisation Pin_pad   
======================================================================
*/
#define pinpad_present	1
#define pinpad_absent	0
#define pinpad_auto_detect 2

#define pinpad_simple	0
#define pinpad_crypto	1
#define pinpad_lecteur	2
#define pinpad_p30		3
#define pinpad_pp30s	4
#define pinpad_ipp220   5
#define pinpad_ipp250   6
#define pinpad_ipp280   7
#define pinpad_ipp320   8
#define pinpad_ipp350   9
#define pinpad_ipp285   10
#define pinpad_ipp310   11
#define pinpad_unknown 255

#define c30_present	    1
#define c30_absent	    0

#define CLESS_ON	    c30_present
#define CLESS_OFF	    c30_absent

#define swipe_terminal  0
#define swipe_p30       1
#define swipe_both      2

#define PP_ON  pinpad_present
#define PP_OFF pinpad_absent
#define PP_AUTO_DETECT pinpad_auto_detect

#define PP30_PPAD    pinpad_simple
#define PPC30_PPAD   pinpad_crypto
#define PPR30_PPAD   pinpad_lecteur
#define P30_PPAD     pinpad_p30
#define PP30S_PPAD   pinpad_pp30s
#define IPP220_PPAD  pinpad_ipp220
#define IPP250_PPAD  pinpad_ipp250
#define IPP280_PPAD  pinpad_ipp280
#define IPP320_PPAD  pinpad_ipp320
#define IPP350_PPAD  pinpad_ipp350
#define IPP285_PPAD  pinpad_ipp285
#define IPP310_PPAD  pinpad_ipp310
#define UNKNOWN_PPAD pinpad_unknown

/*
======================================================================
			initialisation swipe   
======================================================================
*/
#define swipe_iso2				0
#define swipe_iso1_iso2			1
#define swipe_iso3_iso2			2
#define swipe_iso1_iso2_iso3	3

/*
======================================================================
	set serial number of terminal autorized  
======================================================================
*/
#define no_serie_saisie		1
#define no_serie_non_saisie	0



/**************************************************************************************/
/*
======================================================================
	serials of call enable or disable    
======================================================================
*/
#define chainage_actif		1
#define chainage_inactif	0

/*
======================================================================
	initialisation reply    
======================================================================
*/
#define repli_inactif       0
#define repli_actif         1

/*
======================================================================
	initialisation CBCom    
======================================================================
*/
#define reseau_RTC			0
#define reseau_RNIS			1
#define reseau_GSM			2
#define reseau_EXT			3
#define reseau_GSM_INTERNE	4
#define reseau_GPRS			5


/*
======================================================================
	network type   
======================================================================
*/
#define reseau_X25			0
#define reseau_IP   		1
#define reseau_IP_EXT  		2

#define dtr_actif		1
#define dtr_inactif		0

#define passerelle_nulle    0
#define passerelle_non_ssl 1
#define passerelle_ssl      2
#define passerelle_ko      3

/*
======================================================================
	cash connection off or on 
======================================================================
*/
#define cnx_caisse_actif	1
#define cnx_caisse_inactif	0
/* In english dans le texte                                                           */
#define cash_connection_on	1
#define cash_connection_off	0

/*
======================================================================
	initialisation MDP 
======================================================================
*/
#define MDP_RTC		     0
#define MDP_MODEM_RTC 	0
#define MDP_X25		     1
#define MDP_MODEM_X25  1
#define MDP_RNIS 	     2
#define MDP_IP   	     3
#define MDP_GSM   	     4
#define MDP_GSM_X25		 4
#define MDP_GPRS  	     5
#define MDP_IPRTC 	     6
#define MDP_GSM_RTC		 9
#define MDP_EXT         11
#define MDP_EXT_RTC    12
#define MDP_EXT_X25    13
#define MDP_IP_EXT     14

#define sans_ssl    0
#define avec_ssl    1
#define without_ssl 0
#define with_ssl    1

/*
======================================================================
	initialisation code telechargement
======================================================================
*/
#define code_tlch_actif		1
#define code_tlch_inactif	0

/*
======================================================================
	initialisation code telechargement
======================================================================
*/
#define periode_actif		1
#define periode_inactif		0

/*
======================================================================
	modem on base enable or disable
======================================================================
*/
#define modem_sur_socle_actif		1
#define modem_sur_socle_inactif		0

/*
======================================================================
	forced V32 GSM french domain only
======================================================================
*/
#define forcage_desactive 0
#define forcage_active    1

/*
======================================================================
	initialisation GPRS GSM start auto 
======================================================================
*/
#define gprs_auto_disable 0
#define start_link_ppp     1
#define start_gprs_module 2

/*
======================================================================
	               Type of terminal 
======================================================================
*/
/**************************************************************************************/
/*
======================================================================
	terminal Gamme (see HTERMINAL.CNF) 
======================================================================
*/
#define TYPE_TERMINAL_ML30    '1'
#define TYPE_TERMINAL_SMART   '2'
#define TYPE_TERMINAL_EFT30F  '3'
#define TYPE_TERMINAL_EFT30P  '4'
#define TYPE_TERMINAL_TWIN30  '5'
#define TYPE_TERMINAL_EFT930  '6'
#define TYPE_TERMINAL_CAD30   '7'
#define TYPE_TERMINAL_X07     '8'
#define TYPE_TERMINAL_MR40    '9'

/*
======================================================================
	product (if TYPE_TERMINAL_TWIN30)
======================================================================
*/
#define TYPE_TERMINAL_TWIN33  '6'
#define TYPE_TERMINAL_TWIN32  '7'
#define TYPE_TERMINAL_TWIN31  '8'
/**************************************************************************************/
/*
======================================================================
	product (if TYPE_TERMINAL_ML30) 
======================================================================
*/
#define TYPE_TERMINAL_SPM     '2'
#define TYPE_TERMINAL_IPP320  '3'
#define TYPE_TERMINAL_IPP350  '4'
#define TYPE_TERMINAL_IMP350  '5'
#define TYPE_TERMINAL_IPP480  '6'
#define TYPE_TERMINAL_IPP310  '7'
/*
======================================================================
	product (if TYPE_TERMINAL_EFT930)
======================================================================
*/
#define TYPE_TERMINAL_EFT930W '5'
#define TYPE_TERMINAL_EFT930P '6'
#define TYPE_TERMINAL_EFT930G '7'
#define TYPE_TERMINAL_EFT930B '8'
#define TYPE_TERMINAL_EFT930F '9'
/**************************************************************************************/
/*
======================================================================
	product (if TYPE_TERMINAL_ICT) 
======================================================================
*/
#define TYPE_TERMINAL_E532    '9'
#define TYPE_TERMINAL_ICT220  '8'
#define TYPE_TERMINAL_ICT250  '7'
#define TYPE_TERMINAL_ICT280  '6'
#define TYPE_TERMINAL_ISC350  '5'
#define TYPE_TERMINAL_ISC250  '4'
#define TYPE_TERMINAL_IWL220  '3'
#define TYPE_TERMINAL_IWL250  '2'
#define TYPE_TERMINAL_IWL280  '1'
#define TYPE_TERMINAL_IWL350  '0'
#define TYPE_TERMINAL_IWB220  'A'
#define TYPE_TERMINAL_IWB250  'B'
#define TYPE_TERMINAL_ISC480  'C'
/* added for compatibility with old name */
#define TYPE_TERMINAL_EFT930S TYPE_TERMINAL_EFT930F 

/*
======================================================================
	product (if TYPE_TERMINAL_CAD30)
======================================================================
*/
#define TYPE_TERMINAL_IUN150  '1'
#define TYPE_TERMINAL_IUN180  '2'
#define TYPE_TERMINAL_IUN230  '3'
#define TYPE_TERMINAL_IUN180B '4'

/*
======================================================================
	Modele Equipement
======================================================================
*/
#define MODELE_EQUIPEMENT_C30 "110"
#define MODELE_EQUIPEMENT_C30UCR "120"
#define MODELE_EQUIPEMENT_IUN1XX "230"
#define MODELE_EQUIPEMENT_IUN2XX "200"

/*
======================================================================
			Functions Definition
======================================================================
*/

/*!@brief This routine start manager menu.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 150) if function does not exist
 * @return != 0 if available.
 *
 * @link KSFAM_PSQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PSQ_Manager_menu :KSFAM_PSQ:
// \endif
extern int          PSQ_Manager_menu (void);


/*! @brief This routine initializes manager parameters.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 3) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PSQ_Init_new_param :KSFAM_PSQ:
// \endif
extern void          PSQ_Init_new_param (void);


/*! @brief This routine initializes default values of manager parameters.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 5) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Init_param_def:KSFAM_PSQ:
// \endif
extern void          PSQ_Init_param_def (void);


/*! @brief This function initialize the date format.
 * @param date_format : date format.
 *   french_format ( dd/mm/yyyy ) 
 *   us_format ( mm/dd/yyyy ) 
 *   chinese_format (yyyy/mm/dd)
 *   german_format (dd.mm.yyyy)
 * @return 
 *   INIT_OK                : correct initialization
 *   INIT_KO                : value of param incorrect
 *   PARAM_NOT_IMPLEMENTED  : function is not implemented
 * @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Update_date_format:KSFAM_PSQ:
// \endif
extern int           PSQ_Update_date_format(int date_format);

/*! @brief This function has the date format: dd/mm/aaaa or mm/dd/aaaa
 * @return 
 * - 0 : format_defaut ( dd/mm/yyyy ) 
 * - 1 : format_us ( mm/dd/yyyy ) 
 * - 2 : Chinese format (yyyy/mm/dd)
 * - 3 : German format (dd.mm.yyyy)
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 6) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_Date_Format:KSFAM_PSQ:
// \endif
extern int           PSQ_Give_Date_Format(void);

/*! @brief This function gives the Manager language
 * @return 
 * - 0 : Manager language is English 
 * - 1 : Manager language is French 
 * - 2 : Manager language is first user additionnal language
 * - 3 : Manager language is secondt user additionnal language
 * - ....
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 6) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_Language:KSFAM_PSQ:
// \endif
extern int           PSQ_Give_Language(void);

/*! @brief This function returns the terminal number that is initialised.
 * @param *noterminal : pointer to NO_TERMIN structure.
//typedef char NO_TERMIN [3]; 
 * @return Returns the terminal number that is initialised
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 8) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_Terminal_Number:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_Give_Terminal_Number (NO_TERMINAL *noterminal);


/*! @brief This function returns the terminal number that is initialised.
 * @return Returns the terminal number that is initialised
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 151) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Terminal_Number:KSFAM_PSQ:
// \endif
extern int          PSQ_Terminal_Number (void);


/*! @brief This function is used to get the current Manager currencies (see give_money service)
 * @param devise : pointer to structure S_MONEY.
 * @return S_MONEY structure updated
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_Default_Currency:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_Give_Default_Currency ( S_MONEY *devise);


/*! @brief This function is used to get the two letters of the terminal product 
 * @param Identifier : pointer to a string (three bytes min)
 * @return
 *    0 : OK
 *   -1 : not implemented
 *   -2 : unkwown terminal
 *
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 152) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Get_Product_Identifier:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int          PSQ_Get_Product_Identifier ( char *Identifier);

/*! @brief This function places the current Manager currencies (see give_money service) .
 * @param devise : pointer to structure S_MONEY.
 * @return none
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 91) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Write_money:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_Write_money ( S_MONEY *devise);


/*! @brief This function provides PABX string for dialling.
 * @param nostandard : T_STANDARD 
// typedef char T_STANDARD [17]; 
 * @return None (void).
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 10) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_PABX_Value:KSFAM_PSQ:
// \endif
extern void          PSQ_Give_PABX_Value (T_STANDARD nostandard);


/*! @brief This function checks if pinpad is declared or not at Manager level.
 * @return 
 * - 0 if absent,
 * - !0 otherwise.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 11) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_pinpad:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_pinpad (void);

/*! @brief This function checks if pinpad is Contactless.
 * @return 
 * - 0 if absent,
 * - !0 otherwise.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 1) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Pinpad_Contactless:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Pinpad_Contactless (void);

/*! @brief This function tests the c30 connection state.
 * @param liaison : link type on whitch the c30 is connected (INTERNAL_TYPE,SERIAL_TYPE,USB_TYPE)
 * @return
 * - 1 if c30 connected.
 * - 0 otherwise.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 55) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_c30:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_c30(char *liaison);

/*! @brief This function returns the pinpad type ( simple or reader ).
 * @return 
 * - PPR30_PPAD = pinpad reader     
 * - PP30_PPAD  = pinpad not reader 
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Pinpad_Type:KSFAM_PSQ:
// \endif
extern int           PSQ_Pinpad_Type (void);

/*! @brief This function returns the type of pinpad.
 * @return pinpad type.
 * -  PP30_PPAD
 * -  PPC30_PPAD
 * -  PPR30_PPAD
 * -  P30_PPAD
 * -  PP30S_PPAD
 * -  IPP220_PPAD
 * -  IPP250_PPAD
 * -  IPP280_PPAD
 * -  IPP310_PPAD
 * -  IPP320_PPAD
 * -  IPP350_PPAD
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Pinpad_Value:KSFAM_PSQ:
// \endif
extern int           PSQ_Pinpad_Value (void);

  
/*! @brief This function checks manager configuration and ISO2 magnetic stripe reader.
 * @return 
 * - !0 if only ISO2 is defined in manager configuration, 
 * -  0 otherwise (for instance, if ISO1 &amp; ISO2 are both configured) 
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 13) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_ISO2:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_ISO2 (void);

/*! @brief CThis function checks manager configuration and ISO1 magnetic stripe reader.
 * @return 
 * - !0 if iso1 is defined in manager configuration (i.e. ISO1+ISO2 or ISO1+ISO2+ISO3), 
 * - 0 otherwise (ISO2+ISO3 or ISO2 ).
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 14) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_ISO1:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_ISO1 (void);

/*! @brief This function checks manager configuration and ISO3 magnetic stripe reader.
 * @return 
 * - !0 if iso3 iso1 is defined in manager configuration (i.e. ISO3+ISO2 or ISO1+ISO2+ISO3),
 * -  0 otherwise (ISO2+ISO1 or ISO2) 
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 15) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_ISO3:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_ISO3 (void);

/*! @brief This function is used to Get the terminal serial number.
 * @param noserie : Serial number.
 * @return A byte (*noserie).
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_Serial_Number:KSFAM_PSQ:
//  @GSIM_A:1:OUT_ONLY
// \endif
extern void          PSQ_Give_Serial_Number ( char *noserie );


/*! @brief This function is used to Get full terminal serial number.
 * @param noserie : Serial number (64 bytes length max.).
 * @return 
 *   - 0 OK
 *   - -1 if not implemented
 * @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_Full_Serial_Number:KSFAM_PSQ:
//  @GSIM_A:1:OUT_ONLY
// \endif
extern int          PSQ_Give_Full_Serial_Number (unsigned char *noserie );


/*! @brief This function checks if the pinpad has a swipe.
 * @return
 * - 1 if OK
 * - 0 otherwise.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 72) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Swipe:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Swipe (void);


/*! @brief This function is used to get the terminal number.
 * @return A byte.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 17) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Get_Terminal_Number:KSFAM_PSQ:
// \endif
extern unsigned char PSQ_Get_Terminal_Number(void);


/*! @brief This function is used to get communication baud rate between the PC and terminal .
 * @return An integer.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 18) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Get_Baud_Rate:KSFAM_PSQ:
// \endif
extern int           PSQ_Get_Baud_Rate(void);


/*! @brief This function checks against Cluster parameter .
 * @return 
 * - 0 if RTC,
 * - !0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 19) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_chainage:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_chainage (void);


/*! @brief This function checks if TMS access is done via PSTN or X25 mode.
 * @return 
 * - !0 : if RTC(PSTN).
 * - 0 otherwise.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 20) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_RTC:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_RTC (void);


/*! @brief This function checks against CBCOM parameter .
 * @return 
 * -  0 if CBCOM,
 * -  !0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 21) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_cbcom_RTC:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_cbcom_RTC (void);


/*! @brief This function checks against CLE parameter .
//! \return 
 * - 0 if CLE,
 * - !0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 22) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_CLE:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_CLE (void);


/*! @brief This function checks against COM_RESEAU parameter.
 * @return 
 * - !0 if COM_RESEAU,
 * - 0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_dtr:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_dtr (void);


/*! @brief This function checks against RNIS parameter .
 * @return 
 * - 0 if RNIS,
 * - !0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 24) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_RNIS:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_RNIS (void);


/*! @brief This function checks against GSM parameter .
 * @return 
 *  0 if GSM,
 *  !0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_GSM:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_GSM (void);


/*! @brief This function returns network information in the pointer.
 * @param pt_infos : pointer to S_INFOS_RESEAU structure ( see param .h ).
 * @return None 
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 26) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Donner_infos_reseau:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_Donner_infos_reseau           ( S_INFOS_RESEAU     * pt_infos );


/*! @brief This function returns additional network information (i.e. GPRS configuration) .
 * @param pt_infos : pointer to structure S_INFOS_RESEAU_SUP ( see param .h ).
 * @return None (void).
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 49) if function does not exist
 * @note 
 * - Release N : definition of infos_sup_reseau has been changed.
 * - Release H : definition of infos_sup_reseau has been changed.
 * - Release G : The field 'cle' has been renamed into 'liaison_serie' and now contains the serial link of external device (RNIS modem, external modem...); 0 for COM0, 2 for COM2, 5 for USB. Default value is 0 for COM0.
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Give_network_extended_inf:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
// \endif
extern void          PSQ_Give_network_extended_inf       ( S_INFOS_RESEAU_SUP * pt_infos );


/*! @brief This function returns the connection's informations for a network withdrawal.
 * @param pt_infos : pointer to structure S_INFOS_RESEAU_SUP_REPLI.
 * @return None 
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 74) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Donner_infos_reseau_sup_repli:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
// \endif
extern void          PSQ_Donner_infos_reseau_sup_repli ( S_INFOS_RESEAU_SUP_REPLI * pt_infos );


/*! @brief This function returns the APN informations for all network.
 * @param pt_infos : pointer to structure S_INFOS_RESEAU_SUP_APN_REPLI.
 * @return None 
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 81) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Donner_infos_apn:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
// \endif
extern void          PSQ_Donner_infos_apn              ( S_INFOS_RESEAU_SUP_APN_REPLI  *pt_infos );


/*! @brief This function checks against COM_RESEAU parameter.
 * @return 
 * - !0 if COM_RESEAU, 
 * - 0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 27) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_com_reseau:KSFAM_PSQ:
// \endif
extern unsigned char PSQ_Est_com_reseau   ( void );


/*! @brief This function provides remote downloading parameters when calling the TMS.
 * @param idftelchgt : pointer to structure S_PARAM_TLCHGT.
 * @return S_PARAM_TLCHGT structure updated (all fields are filled according following scheme) : 
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 28) if function does not exist
 *  
 *  <table cellpading="0" cellspacing="0" border="1" width="100%">
 *  <tr><th> 'TMS access'= </th><th>.</th><th> 'xxx' : TMS manager parameter \n XXX : constant </th></tr>
 *  <tr><th> nPSTN or X25 TMS :</th><td> .</td><td> .</td></tr>
 * 
 *  <tr><td> PSTN \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel </td>
 *      <td> RTC \n V22 \n 'PABX'+'NO TEL TMS' \n NULL \n RTC \n 'TMS identifier' \n not initialized</td>
 *  </tr>
 * 
 *  <tr><td> X25 \n \n \n </td>
 *      <td> \n type_reseau \n t_transpac \n appel </td>
 *      <td> Idem excepted : \n X25 \n 'TMS X25 ADDRESS' \n X25</td>
 *  </tr>
 * 
 *  <tr><td> Rnis \n \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel \n liaison_serie </td>
 *      <td> TMSRNIS \n V22 \n NULL \n 'TMS X25 ADDRESS' \n X25 \n 'TMS identifier' \n not initialized \n 0 (COM0), 2 (COM2), 5 (USB) </td>
 *  </tr>
 * 
 *  <tr><td> External modem PSTN \n \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel \n liaison_serie </td>
 *      <td> TMSEXT \n V22 \n 'NO TEL TMS' \n NULL \n RTC \n 'TMS identifier' \n not initialized \n 0 (COM0), 2 (COM2), 5 (USB) </td>
 *  </tr>
 * 
 *  <tr><td> External modem X25 \n \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel \n liaison_serie </td>
 *      <td> TMSEXT \n V22 \n 'NO TEL TMS' \n 'TMS X25 ADDRESS' \n X25 \n 'TMS identifier' \n not initialized \n 0 (COM0), 2 (COM2), 5 (USB) </td>
 *  </tr>
 * 
 *  <tr><td> Int. Gsm \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel </td>
 *      <td> TMSGSM \n V22 \n 'NO TEL TMS' (*) \n 'TMS X25 ADDRESS' \n RTC or X25 \n 'TMS identifier' \n not initialized </td>
 *  </tr>
 * 
 *  <tr><th> TMS IP : </th><td> .</td><td> .</td></tr>
 *  <tr><td> IP/Eth \n IP/GPRS \n IP/Pstn \n \n \n \n </td>
 *      <td> type_modem \n ip \n port \n login \n password \n t_nocontrat \n t_nologiciel </td>
 *      <td> VIP \n 'IP ADDRESS' \n 'PORT' \n 'LOGIN' \n 'PASSWORD' \n 'TMS identifier' \n not initialized </td>
 *  </tr>
 * 
 *  <tr><th> Additional parameters for IP mode depending on TMS access : </th><td> .</td><td> .</td></tr>
 *  <tr><td> IP/Eth \n \n \n \n \n \n </td>
 *      <td> type_reseau \n t_noappel \n \n \n \n \n t_transpac </td>
 *      <td> TMSIP \n 'IP ADDRESS: PORT' \n (xxx.yyy.zzz.www:pppp) \n or if SSL is to be used  \n 'IP ADDRESS: PORT/SSL profile' \n (xxx.yyy.zzz.www:pppp/SSL profile) \n NULL  </td>
 *  </tr>

 *  <tr><td> IP/PSTN \n \n \n </td>
 *      <td> type_reseau \n t_noappel \n t_transpac\n \n </td>
 *      <td> TMSIPRTC \n "PABX" + "No TEL FAI" \n NULL or SSL profile \n if SSL is to be used </td>
 *  </tr>
 * 
 *  <tr><td> IP/GPRS \n \n \n \n \n \n </td>
 *      <td> type_reseau \n t_noappel \n \n \n \n \n t_transpac </td>
 *      <td> TMSGPRS \n 'IP ADDRESS: PORT' \n (xxx.yyy.zzz.www:pppp) \n or if SSL is to be used  \n 'IP ADDRESS: PORT/SSL profile' \n (xxx.yyy.zzz.www:pppp/SSL profile) \n NULL  </td>
 *  </tr>
 * 
 *  </table>
 * - (*) : without PABX informations.
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Idf_telechgt:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_Idf_telechgt (S_PARAM_TLCHGT *idftelchgt);


/*! @brief This function provides remote downloading parameters when calling the TMS.
 * @param idftelchgt : pointer on S_PARAM_TLCHGT structure updated (all fields are filled according to the following scheme) : 
 *  
 *  <table cellpading="0" cellspacing="0" border="1" width="100%">
 *  <tr><th> 'TMS access'= </th><th>.</th><th> 'xxx' : TMS manager parameter \n XXX : constant </th></tr>
 *  <tr><th> nPSTN or X25 TMS :</th><td> .</td><td> .</td></tr>
 * 
 *  <tr><td> PSTN \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel </td>
 *      <td> RTC \n V22 \n 'PABX'+'NO TEL TMS' \n NULL \n RTC \n 'TMS identifier' \n not initialized</td>
 *  </tr>
 * 
 *  <tr><td> X25 \n \n \n </td>
 *      <td> \n type_reseau \n t_transpac \n appel </td>
 *      <td> Idem excepted : \n X25 \n 'TMS X25 ADDRESS' \n X25</td>
 *  </tr>
 * 
 *  <tr><td> Rnis \n \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel \n liaison_serie </td>
 *      <td> TMSRNIS \n V22 \n NULL \n 'TMS X25 ADDRESS' \n X25 \n 'TMS identifier' \n not initialized \n 0 (COM0), 2 (COM2), 5 (USB) </td>
 *  </tr>
 * 
 *  <tr><td> External modem PSTN \n \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel \n liaison_serie </td>
 *      <td> TMSEXT \n V22 \n 'NO TEL TMS' \n NULL \n RTC \n 'TMS identifier' \n not initialized \n 0 (COM0), 2 (COM2), 5 (USB) </td>
 *  </tr>
 * 
 *  <tr><td> External modem X25 \n \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel \n liaison_serie </td>
 *      <td> TMSEXT \n V22 \n 'NO TEL TMS' \n 'TMS X25 ADDRESS' \n X25 \n 'TMS identifier' \n not initialized \n 0 (COM0), 2 (COM2), 5 (USB) </td>
 *  </tr>
 * 
 *  <tr><td> Int. Gsm \n \n \n \n \n \n </td>
 *      <td> type_reseau \n type_modem \n t_noappel \n t_transpac \n appel \n t_nocontrat \n t_nologiciel </td>
 *      <td> TMSGSM \n V22 \n 'NO TEL TMS' (*) \n 'TMS X25 ADDRESS' \n RTC or X25 \n 'TMS identifier' \n not initialized </td>
 *  </tr>
 * 
 *  <tr><th> TMS IP : </th><td> .</td><td> .</td></tr>
 *  <tr><td> IP/Eth \n IP/GPRS \n IP/Pstn \n \n \n \n </td>
 *      <td> type_modem \n ip \n port \n login \n password \n t_nocontrat \n t_nologiciel </td>
 *      <td> VIP \n 'IP ADDRESS' \n 'PORT' \n 'LOGIN' \n 'PASSWORD' \n 'TMS identifier' \n not initialized </td>
 *  </tr>
 * 
 *  <tr><th> Additional parameters for IP mode depending on TMS access : </th><td> .</td><td> .</td></tr>
 *  <tr><td> IP/Eth \n \n \n \n \n \n </td>
 *      <td> type_reseau \n t_noappel \n \n \n \n \n t_transpac </td>
 *      <td> TMSIP \n 'IP ADDRESS: PORT' \n (xxx.yyy.zzz.www:pppp) \n or if SSL is to be used  \n 'IP ADDRESS: PORT/SSL profile' \n (xxx.yyy.zzz.www:pppp/SSL profile) \n NULL  </td>
 *  </tr>
 * 
 *  <tr><td> IP/PSTN \n \n \n </td>
 *      <td> type_reseau \n t_noappel \n t_transpac\n \n </td>
 *      <td> TMSIPRTC \n "PABX" + "No TEL FAI" \n NULL or SSL profile \n if SSL is to be used </td>
 *  </tr>
 * 
 *  <tr><td> IP/GPRS \n \n \n \n \n \n </td>
 *      <td> type_reseau \n t_noappel \n \n \n \n \n t_transpac </td>
 *      <td> TMSGPRS \n 'IP ADDRESS: PORT' \n (xxx.yyy.zzz.www:pppp) \n or if SSL is to be used  \n 'IP ADDRESS: PORT/SSL profile' \n (xxx.yyy.zzz.www:pppp/SSL profile) \n NULL  </td>
 *  </tr>
 * 
 *  </table>
 *  - (*) : without PABX informations.
 *  
 * @return None
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 51) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_telechgt:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_telechgt (S_PARAM_TLCHGT *idftelchgt);

/*! @brief This function is used to check the pinpad is a two row type.
 * @return 
 * - 0 if absent,
 * - !0 otherwise.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 34) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Two_Lines_Pinpad:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Two_Lines_Pinpad (void);


/*! @brief This function checks a Cash register is declared .
 * @return 
 * - 0 if Cash Register
 * - !0 otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 36) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Cash_Connection:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Cash_Connection(void);


/*! @brief This function checks the manager configuration.
 * @return
 *    0 to display and authorize access
 *       you may have to enter a password if one has been configured
 *       with MANAGER/INITIALIZATION/PASSWORD menu.
 *    1 to display and un-authorize access
 *       When Manager is selected a screen with
 *                MANAGER OPTIONS
 *                    LOCKED
 *       is displayed
 *    2 to mask
 *    3 to set to the last position and authorize access
 *       you may have to enter a password if one has been configured
 *       with MANAGER/INITIALIZATION/PASSWORD menu.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 38) if function does not exist
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:is_F_Manager:KSFAM_PSQ:
// \endif
extern int           is_F_Manager(void);


/*! @brief This routine allows to update manager's language via application.
 * @param *type_language : language value, string of 1 char, null terminated .
 * - '0' = select english, 
 * - '1' = select french, 
 * - '2' = select first user additonnal language
 * - '3' = select second user additonnal language
 * - ...
 * @return Initialization's report:
 * - INIT_OK
 * - INIT_KO
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 39) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Update_language:KSFAM_PSQ:
// \endif
extern char          PSQ_Update_language ( char *type_language );


/*! @brief This routine allows to update manager's language  using ISO639-1 code
 * @param Language : language value, string of 2 char.
 * - "EN" = english, 
 * - "FR" = local, 
 * - ....
 * @return Initialization's report:
 * - INIT_OK
 * - INIT_KO
 * @par exit None
 *	@section test_PSQ_init_language

 * @include param_Sample_01.c
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_init_language:KSFAM_PSQ:
// \endif
extern char PSQ_init_language (unsigned char *Language);


/*! @brief This routine allows to update manager's phone number TMS via application.
 * @param *phone_num : string size less or equal than 16 chars, null terminated .
 * @return C.R. Initi :
 * - INIT_OK
 * - INIT_KO
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 40) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Update_phonenumber:KSFAM_PSQ:
// \endif
extern char          PSQ_Update_phonenumber ( char *phone_num );


/*! @brief This routine allows to update manager's pabx options via application.
 * @param *type_pabx : string size less or equal than 16 chars, null terminated, 
 * Example :  'T',',,T',',,P' 
 * @return C.R. Initi :
 * - INIT_OK
 * - INIT_KO
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 41) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Update_pabx:KSFAM_PSQ:
// \endif
extern char          PSQ_Update_pabx ( char *type_pabx );


/*! @brief This function enable or disable the cash connection.
 * @param cash_connection : the cash connection
 * - cash_connection_on 1
 * - cash_connection_off 0
 * @return Execution report :
 * - INIT_OK : ok
 * - INIT_KO : otherwise
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 45) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Update_Cash_Connection:KSFAM_PSQ:
// \endif
extern char          PSQ_Update_Cash_Connection (int cash_connection);



/*! @brief This function checks the manager configuration.
 * @return
 * - 1 if pinpad reader
 * - 0 otherwise.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 43) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Pinpad_Reader:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Pinpad_Reader (void);


/*! @brief This routine allows or inhibit the access to the manager maintenance menu. 
 * @param value : 
 *    0 to display and authorize access
 *       you may have to enter a password if one has been configured
 *       with MANAGER/INITIALIZATION/PASSWORD menu.
 *    1 to display and un-authorize access
 *       When Manager is selected a screen with
 *                MANAGER OPTIONS
 *                    LOCKED
 *       is displayed
 *    2 to mask
 *    3 to set to the last position and authorize access
 *       you may have to enter a password if one has been configured
 *       with MANAGER/INITIALIZATION/PASSWORD menu.
 * @return Returns current value (see input parameter).
 * - INIT_OK
 * - INIT_KO
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 44) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Manager_F:KSFAM_PSQ:
// \endif
extern int           PSQ_Manager_F (int value);


/*! @brief This function is used to get Hardware terminal type.
 * @return The product type.
 * - TYPE_TERMINAL_ML30    '1'
 * - TYPE_TERMINAL_SMART   '2'
 * - TYPE_TERMINAL_EFT30F  '3'
 * - TYPE_TERMINAL_EFT30P  '4'
 * - TYPE_TERMINAL_TWIN30  '5'
 * - TYPE_TERMINAL_EFT930  '6'
 * - TYPE_TERMINAL_CAD30   '7'
 * - TYPE_TERMINAL_X07     '8'
 * - TYPE_TERMINAL_MR40    '9'
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 46) if function does not exist
 * @note Be Careful : Please use PSQ_Donner_reference if you need more information about terminal type (for instance,EFT930-G or EFT930-B).
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Get_hardware_type:KSFAM_PSQ:
// \endif
extern char          PSQ_Get_hardware_type(void);

/*! @brief This function returns the product range.
 * @param produit : The product type.
 * - TYPE_TERMINAL_ML30    '1'
 * - TYPE_TERMINAL_SMART   '2'
 * - TYPE_TERMINAL_EFT30F  '3'
 * - TYPE_TERMINAL_EFT30P  '4'
 * - TYPE_TERMINAL_TWIN30  '5'
 * - TYPE_TERMINAL_EFT930  '6'
 * - TYPE_TERMINAL_CAD30   '7'
 * - TYPE_TERMINAL_X07     '8'
 * - TYPE_TERMINAL_MR40    '9'
 *
 * @return the product range depending on product type
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 80) if function does not exist
 *	  
 *	@section sample1

 * @include param_Sample_02.c
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Get_product_type:KSFAM_PSQ:
//  @GSIM_A:1:DATA_SIZE(3)
// \endif
extern unsigned char PSQ_Get_product_type(unsigned char *produit);



/*! @brief This function checks if device is Peds.
 * @param Device :  PERIPH_DISPLAY or PERIPH_PPR
 * @return
 * - 1 if Device Peds,
 * - 0 otherwise.
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 19) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:IsTerminalPeds:KSFAM_PSQ:
// \endif
extern int           IsTerminalPeds(int Device);


/*! @brief This function checks if device is IngeTrust.
 * @param Device : PERIPH_DISPLAY or PERIPH_PPR
 * @return
 * - 1 if Device Ingetrust,
 * - 0 otherwise.
* @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 50) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:IsTerminalIngetrust:KSFAM_PSQ:
// \endif
extern int           IsTerminalIngetrust(int Device);


/*! @brief This function checks the manager configuration.
 * @return
 *   INGETRUST_TYPE_UNKNOWN
 *   INGETRUST_TYPE_NONE
 *   INGETRUST_TYPE_PKIv1
 *   INGETRUST_TYPE_PKIv3
 * @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:GetTerminalPKIVersion:KSFAM_PSQ:
// \endif
extern int           GetTerminalPKIVersion(void);

/*! @brief This function checks the manager configuration.
 * @return
 *   -1              NOT IMPLEMENTED
 *   PCI_PTS_V2      PCI V2
 *   PCI_PTS_V3      PCI V3
 * @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:GetTerminalPCIPTSVersion:KSFAM_PSQ:
// \endif
extern int           GetTerminalPCIPTSVersion(void);

/*! @brief This function checks the pinpad configuration.
 * @return
 *   INGETRUST_TYPE_UNKNOWN
 *   INGETRUST_TYPE_NONE
 *   INGETRUST_TYPE_PKIv1
 *   INGETRUST_TYPE_PKIv3
 * @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:GetPinpadPKIVersion:KSFAM_PSQ:
// \endif
extern int           GetPinpadPKIVersion(void);


/*! @brief This function provides the download parameters.
 * @param idftelchgt : pointer to structure S_PARAM_TLCHGT (param aters)
 * @param old : always 0
 * @param type_reseau : type of TMS
 * @return None (void).
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 54) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Idf_telechgt_auto:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_Idf_telechgt_auto (S_PARAM_TLCHGT *idftelchgt,int old,int type_reseau);


/*! @brief This function is used to get the Pack system informations and the Pack manager informations.
 * @param infos : pointer to structure Pack_Infos_Telium.
 * @return Pack_Infos_Telium structure (see param .h)
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 56) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_GetPacksInfos:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PSQ_GetPacksInfos ( Pack_Infos_Telium *infos);


/*! @brief This function is used to get the SDK informations
 * @param SDK_infos : pointer to structure SDK_Infos_Telium.
 * @return 
 * - OK
 * - TELIUM_SDK_FILE_NOT_EXIST
 * - TELIUM_SDK_FILE_TS_PACK_TYPE_INCORRECT
 * - TELIUM_SDK_FILE_TS_PACK_VERSION_INCORRECT
 * - TELIUM_SDK_FILE_M_PACK_TYPE_INCORRECT
 * - TELIUM_SDK_FILE_M_PACK_VERSION_INCORRECT
 * - TELIUM_TS_PACK_FILE_NOT_EXIST
 * - TELIUM_M_PACK_FILE_NOT_EXIST
 *  @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_GetSDKInfos:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int PSQ_GetSDKInfos (SDK_Infos_Telium *SDK_infos);


/*! @brief This function tests if the modem is on its base.
 * @return
 * - Returns 1 if the Modem is on its base, 
 * - 0 otherwise.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 57) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_Modem_Sur_Socle:KSFAM_PSQ:
// \endif
extern unsigned char PSQ_Est_Modem_Sur_Socle (void);


/*! @brief This function returns 1 if V32 is forced.
 * @return
 * - 1 if V32 is forced,
 * - 0 otherwise.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 58) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_Forcage_V32:KSFAM_PSQ:
// \endif
extern unsigned int  PSQ_Est_Forcage_V32(void);


/*! @brief This function returns the pad number.
 * @param num_pad : pad number.
 * @return None
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 59) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_PAD_Forcage_V32:KSFAM_PSQ:
//  @GSIM_A:1:DATA_SIZE(20)
// \endif
extern void          PSQ_Est_PAD_Forcage_V32(unsigned char *num_pad);


/*! @brief This function returns 1 if the prefix is present.
 * @return 1 if prefix.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 60) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
//! \note 
// \if SIMULATION
//  @GSIM_F:PSQ_Est_Forcage_Prefixe:KSFAM_PSQ:
// \endif
extern unsigned int  PSQ_Est_Forcage_Prefixe (void);


/*! @brief This function returns the prefix (ex : 0033).
 * @param prefixe : prefix
 * @return None
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 61) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_Prefixe:KSFAM_PSQ:
//  @GSIM_A:1:DATA_SIZE(10)
// \endif
extern void          PSQ_Est_Prefixe ( unsigned char *prefixe );


/*! @brief PThis function provides the number of banking applications. (French domain only)
 * @return Number of banking applications : (see GIVE_YOUR_SPECIFIC_CONTEXT)
 * @par exit None
 * @note Telium manager does not count itself . To be used by French applications instead of num_seg (); 
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_num_seg:KSFAM_PSQ:
// \endif
extern int           PSQ_num_seg    (void);

/*! @brief This function checks the DTR signal.
 * @return 1 if ok
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 69) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Est_DTR:KSFAM_PSQ:
// \endif
extern int           PSQ_Est_DTR (void);


/*! @brief This function checks the pinpad type.
 * @return
 * - 0 pinpad_simple ( PP30 ) .
 * - 1 pinpad graphic.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 70) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Graphic_Pinpad:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Graphic_Pinpad(void);


/*! @brief This function checks if the terminal has an internal or external printer device.
 * @return
 * - 1 if printer material,
 * - 0 otherwise
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 73) if function does not exist
*
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Printer:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Printer(void);


/*! @brief This routine tests if the terminal runs in behavior UCM.
 * @return
 * - 1 if yes
 * - 0 otherwise.
 *  @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Is_Ucm_Behaviour:KSFAM_PSQ:
// \endif
extern int           PSQ_Is_Ucm_Behaviour(void);


/*! @brief This routine return the state of the data automatic start of gprs
 * @return
 * - 1 if start is ON.
 * - 0 otherwise.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 83) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Start_gprs:KSFAM_PSQ:
// \endif
extern int           PSQ_Start_gprs(void);


/*! @brief This routine writes S_STATE_PARAM structure
 * @param param : pointer to S_STATE_PARAM structure
 * @return None 
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 88) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_write_state_param:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void PSQ_write_state_param(S_STATE_PARAM *param);



/*! @brief This routine reads S_STATE_PARAM structure
 * @param param : pointer to S_STATE_PARAM structure
 * @return None (void).
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 89) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_read_state_param:KSFAM_PSQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void PSQ_read_state_param(S_STATE_PARAM *param);


/*! @brief Define for PSQ_update_ClessReader function */
#define BAD_TYPE                         1
#define NO_DEVICE_FOUND                  2
#define INVALID_SOFTWARE_CONFIGURATION   3
#define INVALID_HARDWARE_CONFIGURATION   4
#define BAD_VALUE                        6
/*! @brief This routine sets CLESS configuration
 *  The terminal reset after completion when ClessType value is CLESS_ON)
 * @param ClessEnable : CLESS_ON to enable,CLESS_OFF to disable
 * @param ClessType   : Cless type (SERIAL_TYPE,USB_TYPE,INTERNAL_TYPE)
 * @return
 * - INIT_OK                          if done
 * - BAD_TYPE                         ClessType is not valid
 * - BAD_VALUE                        ClessEnable is not valid
 * - NO_DEVICE_FOUND                  Device for Cless type does not exist
 * - INVALID_SOFTWARE_CONFIGURATION   TPass DLL is not loaded
 * - INVALID_HARDWARE_CONFIGURATION   Terminal is not Cless (when ClessType value is INTERNAL_TYPE)
 * - PARAM_NOT_IMPLEMENTED            If function does not exist
 *  @par exit none
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_update_ClessReader:KSFAM_PSQ:
// \endif
extern int PSQ_update_ClessReader(int ClessEnable,int ClessType);

/*! @brief This routine sets PINPAD configuration
 * @param PinpadEnable : PP_ON to enable,PP_OFF to disable,PP_AUTO_DETECT to start an auto detection 
 * @param PinpadType : Pinpad type (PP30_PPAD,PPC30_PPAD,PPR30_PPAD,P30_PPAD,PP30S_PPAD,UNKNOWN)
 * - Set the pinpad type to UNKNOWN to start on auto detect
 * - The auto detect of pinpad is started only if the function PSQ_Is_pinpad return FALSE
 * @return
 * - INIT_OK if done
 * - INIT_KO if error
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 92) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_SetPinpad:KSFAM_PSQ:
// \endif
extern int PSQ_SetPinpad(int PinpadEnable,int PinpadType);

/*! @brief This function initialize background color on IPP250 and IPP280.
 * @param val : color in ARGB (0xFF00FF00 mean Green)
 * @return 
 * - 0 if there is no IPP with background,
 * - !0 if there is IPP with background,.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 94) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_init_ippcolor:KSFAM_PSQ:
// \endif
extern int           PSQ_init_ippcolor (int val);

/*! @brief This function initialize background color on IST1XX.
 * @param val : color in ARGB (0xFF00FF00 mean Green)
 * @return 
 * - 0 if there is no IST1XX with color background,
 * - !0 if there is IST1XX with background,.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 97) if function does not exist
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:IST1XX_init_color:KSFAM_PSQ:
// \endif
extern int           IST1XX_init_color (int val);

/*! @brief This function read the manager parameters.
 * @param param : struct of parameters
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 51) if function does not exist
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_lire_param:KSFAM_PSQ:
// \endif
extern void 		 PSQ_lire_param(S_PARAM *param);

/*! @brief This function write the manager parameters.
 * @param param : struct of parameters
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 51) if function does not exist
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_lire_param:KSFAM_PSQ:
// \endif
extern void 		 PSQ_ecrire_param(S_PARAM *param);

/*! @brief This function print the currency list.
 * the peripheral printer must be open before and close
 * after.
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 31) if function does not exist
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Imprimer_money:KSFAM_PSQ:
// \endif
extern void          PSQ_Imprimer_money (void);

/*! @brief Defines for PSQ_Get_Cless_Capabilities return */
#define CLESS_ACTIVATED    0x00000001
#define INTERNAL_CLESS     0x00000002
#define TELIUM_PASS_CLESS  0x00000004
#define PINPAD_CLESS       0x00000008


/*! @brief This function is used to get CLESS capability
 * @return mask of capability.
 * - 0 mean that the terminal is not and can't be CLESS
 * - CLESS_ACTIVATED   bit  = CLESS is already activated (PSQ_Is_c30)
 * - INTERNAL_CLESS    bit  = Internal CLESS terminal (IsCless) (1)
 * - TELIUM_PASS_CLESS bit  = Telium PASS connected             (2)
 * - PINPAD_CLESS      bit  = Cless Pinpad Connected            (3)
 *  @par exit none
 * @note 
 * - only CLESS_ACTIVATED bit is returned when CLESS was set on USB, but no peripheral that supports CLESS connected to USB. 
 * - CLESS_ACTIVATED and INTERNAL_CLESS bits are positionned for Internal CLESS terminal and CLESS was set.
 * - CLESS_ACTIVATED and TELIUM_PASS_CLESS bits are positionned when Telium PASS connected and CLESS was set on USB.
 * - CLESS_ACTIVATED and PINPAD_CLESS bits are positionned when Cless Pinpad Connected and CLESS was set on USB.
 * - If CLESS_ACTIVATED bit is not positionned, terminal can be (1),(3) or (1)+(3)
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Get_Cless_Capabilities:KSFAM_PSQ:
// \endif
extern int PSQ_Get_Cless_Capabilities(void);

/*
======================================================================
	For TMS parameters initialisation
======================================================================
*/
/*! @brief Defines for tms_type field of S_PARAM_TMS struct in PSQ_Init_TMS_Parameters function */
#define TMS_MODEM_PSTN  0      
#define TMS_MODEM_X25   1
#define TMS_EXT_PSTN    2
#define TMS_EXT_X25     3
#define TMS_ISDN_X25    4
#define TMS_IP          5
#define TMS_IP_EXT      6
#define TMS_GSM_PSTN    7
#define TMS_GSM_X25     8
#define TMS_IP_PSTN     9
#define TMS_GPRS        10

/*! @brief This type is used to initialize TMS parameters with PSQ_Init_TMS_Parameters.*/
typedef struct
{
    int			  tms_type;                             /*!< type of network : \li TMS_MODEM_PSTN, \li TMS_MODEM_X25, \li TMS_EXT_PSTN, \li TMS_EXT_X25, \li TMS_ISDN_X25, \li TMS_IP, \li TMS_IP_EXT, \li TMS_GSM_PSTN, \li TMS_GSM_X25, \li TMS_IP_PSTN, \li TMS_GPRS.*/
    T_MDP		  tms_call_number;                      /*!< used if type of network is : \li TMS_MODEM_PSTN, \li TMS_MODEM_X25, \li TMS_EXT_PSTN, \li TMS_EXT_X25, \li TMS_GSM_PSTN, \li TMS_GSM_X25.*/
    T_TRANSPAC	  tms_transpac_number;                  /*!< used if type of network is : \li TMS_MODEM_X25, \li TMS_EXT_X25, \li TMS_ISDN_X25, \li TMS_GSM_X25.*/
    T_CONTRAT	  tms_identifier;                       /*!< used if type of network is : \li TMS_MODEM_PSTN, \li TMS_MODEM_X25, \li TMS_EXT_PSTN, \li TMS_EXT_X25, \li TMS_ISDN_X25, \li TMS_IP, \li TMS_IP_EXT, \li TMS_GSM_PSTN, \li TMS_GSM_X25, \li TMS_IP_PSTN, \li TMS_GPRS.*/
    unsigned int  tms_ip_address;                       /*!< used if type of network is : \li TMS_IP, \li TMS_IP_PSTN, \li TMS_GPRS.*/
    unsigned int  tms_port;                             /*!< used if type of network is : \li TMS_IP, \li TMS_IP_PSTN, \li TMS_GPRS.*/
	unsigned int  tms_serial_link;                      /*!< used if type of network is : \li TMS_EXT_PSTN, \li TMS_EXT_X25, \li TMS_ISDN_X25, \li TMS_IP_EXT, \li TMS_GSM_PSTN, \li TMS_GSM_X25, \li TMS_GPRS.*/
    unsigned char tms_login[LG_LOGIN];                  /*!< used if type of network is : \li TMS_IP_PSTN, \li TMS_GPRS.*/
    unsigned char tms_password[LG_PASSWORD];            /*!< used if type of network is : \li TMS_IP_PSTN, \li TMS_GPRS.*/
    unsigned char tms_profil_ssl[PROFILE_NAME_SIZE];    /*!< used if type of network is : \li TMS_IP, \li TMS_IP_PSTN, \li TMS_GPRS.*/
    int           tms_presence_ssl;                     /*!< used if type of network is : \li TMS_IP, \li TMS_IP_PSTN, \li TMS_GPRS.*/
	unsigned char tms_apn[GPRS_APN_LGR+1];              /*!< used if type of network is : \li TMS_GPRS.*/
    unsigned char tms_entry_type;                       /*!< used if type of network is : \li TMS_IP, \li TMS_IP_PSTN, \li TMS_GPRS.*/
    unsigned char tms_domain_name[LG_DOMAINE];          /*!< used if type of network is : \li TMS_IP, \li TMS_IP_PSTN, \li TMS_GPRS.*/
} S_PARAM_TMS;

/*! @brief Defines for return code of PSQ_Init_TMS_Parameters function */
#define PSQ_Init_TMS_Parameters_OK               0   /*!< OK */
#define PSQ_Init_TMS_Parameters_Unavailable     -1   /*!< Function doest not exist in SDK */
#define PSQ_Init_TMS_Parameters_Syntax_Error    -2   /*!< Syntax Error */

/*! @brief This function is used to initialize TMS parameters
 * @param newval : New parameters
 * @return
 * - FALSE if error occured
 * - TRUE if OK
 *  @par exit none
 * @note 
 *
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PSQ_Init_TMS_Parameters:KSFAM_PSQ:
// \endif
extern int PSQ_Init_TMS_Parameters(S_PARAM_TMS *newval);



////////////////////////////////////////////////////////////////////////////
// Fonctions PSQ : English / French pb
////////////////////////////////////////////////////////////////////////////
//!see \ref PSQ_Is_Pinpad_Reader
extern int           PSQ_Est_pinpad_lecteur (void);
//!see \ref PSQ_Give_Date_Format
extern int           PSQ_Donner_format_date(void);
//!see \ref PSQ_Give_Language
extern int           PSQ_Donner_langue(void);
//!see \ref PSQ_Give_Terminal_Number
extern void          PSQ_No_terminal (NO_TERMINAL *noterminal);
//!see \ref PSQ_Give_Default_Currency
extern void          PSQ_Est_money ( S_MONEY *devise);
//!see \ref PSQ_Give_PABX_Value
extern void          PSQ_No_standard (T_STANDARD nostandard);
//!see \ref PSQ_Is_pinpad
extern int           PSQ_Est_pinpad (void);
//!see \ref PSQ_Pinpad_Type
extern int           PSQ_type_pinpad (void);
//!see \ref PSQ_Pinpad_Value
extern int           PSQ_donner_type_pinpad (void);
//!see \ref PSQ_Is_ISO2
extern int           PSQ_Est_ISO2 (void);
//!see \ref PSQ_Is_ISO1
extern int           PSQ_Est_ISO1 (void);
//!see \ref PSQ_Is_ISO3
extern int           PSQ_Est_ISO3 (void);
//!see \ref PSQ_Give_Serial_Number
extern void          PSQ_Donner_noserie ( char *noserie );
//!see \ref PSQ_Is_Swipe
extern int           PSQ_presence_swipe (void);
//!see \ref PSQ_Get_Terminal_Number
extern unsigned char PSQ_get_no_lecteur(void);
//!see \ref PSQ_Get_Baud_Rate
extern int           PSQ_get_vitesse_lecteur(void);
//!see \ref PSQ_Is_Two_Lines_Pinpad
extern int           PSQ_Est_pinpad_2_lignes (void);
//!see \ref PSQ_Is_Cash_Connection
extern int           PSQ_Est_caisse(void);
//!see \ref PSQ_Get_hardware_type
extern char          PSQ_lire_type_materiel(void);
//!see \ref PSQ_Give_network_extended_inf
extern void          PSQ_Donner_infos_reseau_sup ( S_INFOS_RESEAU_SUP * pt_infos );
//!see \ref PSQ_Get_product_type
extern unsigned char PSQ_Lire_Gamme_Produit(unsigned char *produit);
//!see \ref PSQ_Is_Graphic_Pinpad
extern int           PSQ_est_pinpad_graphique(void);
//!see \ref PSQ_Is_c30
extern int           PSQ_Est_c30(char *liaison);

/*! \cond NON_VISIBLE */
#define PSQ_Is_Pinpad_Reader          PSQ_Est_pinpad_lecteur   
#define	PSQ_Give_Date_Format	      PSQ_Donner_format_date
#define	PSQ_Give_Language		      PSQ_Donner_langue
#define	PSQ_Give_Terminal_Number	  PSQ_No_terminal
#define	PSQ_Give_Default_Currency     PSQ_Est_money
#define	PSQ_Give_PABX_Value           PSQ_No_standard
#define	PSQ_Is_pinpad			      PSQ_Est_pinpad
#define	PSQ_Pinpad_Type			      PSQ_type_pinpad
#define	PSQ_Pinpad_Value  		      PSQ_donner_type_pinpad
#define PSQ_Is_ISO2                   PSQ_Est_ISO2   
#define PSQ_Pinpad_value              PSQ_Pinpad_Value
#define	PSQ_Is_ISO2			          PSQ_Est_ISO2
#define	PSQ_Is_ISO1				      PSQ_Est_ISO1
#define	PSQ_Is_ISO3				      PSQ_Est_ISO3
#define	PSQ_Is_PSTN				      PSQ_Est_RTC
#define	PSQ_Give_Serial_Number        PSQ_Donner_noserie
#define	PSQ_Is_Swipe                  PSQ_presence_swipe			  
#define	PSQ_Get_Terminal_Number       PSQ_get_no_lecteur
#define PSQ_Get_Baud_Rate             PSQ_get_vitesse_lecteur
#define PSQ_Is_Two_Lines_Pinpad       PSQ_Est_pinpad_2_lignes
#define PSQ_Is_Cash_Connection        PSQ_Est_caisse
#define PSQ_Get_hardware_type         PSQ_lire_type_materiel
#define PSQ_Give_network_extended_inf PSQ_Donner_infos_reseau_sup
#define PSQ_Is_ISO3                   PSQ_Est_ISO3   
#define PSQ_Is_ISO1                   PSQ_Est_ISO1
#define PSQ_Is_c30                    PSQ_Est_c30 
#define PSQ_Get_product_type          PSQ_Lire_Gamme_Produit
#define PSQ_Is_Graphic_Pinpad         PSQ_est_pinpad_graphique
/*!\endcond*/

#endif
/*! @} **/

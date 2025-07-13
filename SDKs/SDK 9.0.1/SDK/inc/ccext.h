/*! @addtogroup KSFAM_CB2A
	* @{
**/

#ifndef _EXTCC
#define _EXTCC

/*
======================================================================
					List of Defines
======================================================================
*/
/* DEFINITIONS UTILISEES PAR LA COUCHE LIAISON PNCSA */

#define SYN '\x16'
#define DLE '\x10'
#define ETX '\x03'
#define STX '\x02'
#define CR  '\x0d'
#define LF  '\x0a'

#define READ_TRAME    etat0     /* demande lecture Trame sur la ligne */

#define TPS_TRANSMIT  '\5' /* temps de transmission 256 octets 1200bd avec
                              DLE --> 512 octet de 10 bits */

/* modif NF pour CBCOM juin 98 */

#define LG_LA          '\3'          /* longueur parametres trame LA */
#define LG_LT          '\2'          /* longueur parametres trame LT */
#define LG_LD          '\4'          /* longueur parametres trame LD */
#define NK             '\1'          /* credit en reception */
#define LA_ID          '\5'          /* ident. d'une trame LA */
#define LT_ID          '\4'          /* ident. d'une trame LT */
#define LD_ID          '\2'          /* ident. d'une trame LD */


#define T4        20 /* time_out d'attente 'TRANSPAC' */
#define T4_DTR    60
#define T5        30 /* time_out d'attente 'COM' */ /* FT 538 20s --> 30s */
#define T5_CBPR   20 /* time_out d'attente COM en CBPR : attente PWD ou msg bancaire */
#define N401     256        /* octets max ds un champ information */
/* DEFINITIONS UTILISEES PAR LA COUCHE IPDU PNCSA */
#define N400       3       /* nb d'emission max sur erreur de transmission */
#define T401       6       /* time_out d'attente d'une trame LA en secondes */

/* definition pour les interfaces couches de communication EIS308 */
#define EXTCC_MODEM  0x1000	/* Type de modem, interne, externe, RTC, RNIS Vitesse, parite, nombre de bits, changement de parite ... */
#define EXTCC_PAD	   0x2000	/* Type des PAD EBA, EMA, pas de PAD ... */
#define EXTCC_APPEL  0x3000	/* Numero de telephone, adresse X25, donnees complementaires, mot de passe, adresse IP */
#define EXTCC_PROT   0x4000	/* Liste des protocoles, V42A, X25, CBSA, CBCOM ... */
#define EXTCC_CR     0x5000	/* Compte rendu, detaille, trace, affichage, impression. */
#define EXTCC_TIMER  0x6000	/* Time out, porteuse, inter caractere, inter trame... */
#define EXTCC_AFF    0x7000	/* Affichage, messages à afficher selon les phases... */
#define EXTCC_DATA   0x8000	/* Donnees reçues ou à emettre */

/*! @brief  Enumerate all the EXTCC_ types.*/
typedef enum {
	EXTCC_MODEM_CONF              =(EXTCC_MODEM | 0x0000),		/*!<  Modem */
	EXTCC_MODEM_EXTERNE           =(EXTCC_MODEM | 0x0100),		/*!<  External Modem*/
	EXTCC_MODEM_COM               =(EXTCC_MODEM | 0x0001),		/*!<  port number*/
	EXTCC_MODEM_PROFILE	     			=(EXTCC_MODEM | 0x0002),		/*!<  Profile number. ATZ, ATZ0 or ATZ1 */
	EXTCC_MODEM_MODULATION	      =(EXTCC_MODEM | 0x0003),		/*!<  Max. speed, parity, stop byte, number of bytes*/
	EXTCC_MODEM_CMD_AT	      		=(EXTCC_MODEM | 0x0004),		/*!<  Initialisation Commands given by the application */
	EXTCC_MODEM_CHGT_PARITE       =(EXTCC_MODEM | 0x0005),		/*!<  parity change during the connexion */
	EXTCC_MODEM_HANDLE            =(EXTCC_MODEM | 0x0006),		/*!<  HANDLE of the modem port*/
	EXTCC_MODEM_CR_NUMEROTATION   =(EXTCC_MODEM | 0x0007),		/*!<  number report*/
	EXTCC_MODEM_LS                =(EXTCC_MODEM | 0x0010),		/*!<  Special line connection*/
	EXTCC_MODEM_TYPE              =(EXTCC_MODEM | 0x0011),		/*!<  RTC Connection - RNIS B D - GPRS ... */
	EXTCC_MODEM_TYPE_FORCE        =(EXTCC_MODEM | 0x0012),		/*!<  RTC Connection - RNIS B D - GPRS ... */
	EXTCC_MODEM_APPLI             =(EXTCC_MODEM | 0x0018),		/*!<  Modem managed by the application */
	
	EXTCC_PAD_CONF                =(EXTCC_PAD    | 0x0000),		/*!<  PAD Configuration*/
	EXTCC_PAD_EBA                 =(EXTCC_PAD    | 0x0001),		/*!<  Access by PAD EBA */
	EXTCC_PAD_EMA                 =(EXTCC_PAD    | 0x0002),		/*!<  Access by PAD EMA */
	EXTCC_PAD_MODULATION          =(EXTCC_PAD    | 0x0003),		/*!<  Speed of the Pad */

	EXTCC_APPEL_CONF              =(EXTCC_APPEL  | 0x0000),		/*!<  Configuration of the call category*/
	EXTCC_APPEL_TEL               =(EXTCC_APPEL  | 0x0001),		/*!<  Number to take the call*/
	EXTCC_APPEL_TEL_SECOURS       =(EXTCC_APPEL  | 0x0002),		/*!<  Help number*/
	EXTCC_APPEL_STANDARD          =(EXTCC_APPEL  | 0x0003),		/*!<  Number to call if the line is not direct*/
	EXTCC_APPEL_ADRESSE_TRSPAC    =(EXTCC_APPEL  | 0x0010),		/*!<  transpac Number */
	EXTCC_APPEL_D_COMP            =(EXTCC_APPEL  | 0x0011),		/*!<  Complementary data*/
	EXTCC_APPEL_ADRESSE_IP        =(EXTCC_APPEL  | 0x0012),		/*!<  IP Address*/
	EXTCC_APPEL_SERVEUR           =(EXTCC_APPEL  | 0x0013),		/*!<  Adress of the access server*/
	EXTCC_APPEL_ADRESSE_RESEAU    =(EXTCC_APPEL  | 0x0014),		/*!<  Netxork Adress plus complementary data*/
	EXTCC_APPEL_BASCUL            =(EXTCC_APPEL  | 0x0015),		/*!<  overbalance on the help number in case of failure*/
	EXTCC_APPEL_REPRISE           =(EXTCC_APPEL  | 0x0016),		/*!<  Number renewal after a time out */
	EXTCC_APPEL_REPRISE_SECOURS   =(EXTCC_APPEL  | 0x0017),		/*!<  Renewal on the authorized help number (from RTC to RNIS for example)*/
	EXTCC_APPEL_RAISON            =(EXTCC_APPEL  | 0x0018),		/*!<  Type of connexion, parameters, init*/
	EXTCC_APPEL_CHAINAGE          =(EXTCC_APPEL  | 0x0020),		/*!<  Chained list authorized*/
	EXTCC_APPEL_DCNX              =(EXTCC_APPEL  | 0x0021),		/*!<  Physical and/or logical disconnection*/
	EXTCC_APPEL_DCNX_TO           =(EXTCC_APPEL  | 0x0022),		/*!<  TO before disconnection */
	EXTCC_APPEL_AVEC_SSL          =(EXTCC_APPEL  | 0x0023),		/*!<  SSL active */
	EXTCC_APPEL_PROFIL_SSL        =(EXTCC_APPEL  | 0x0024),		/*!<  Index of the SSL profile if active*/
	EXTCC_APPEL_AVEC_REPLI        =(EXTCC_APPEL  | 0x0025),		/*!<  Widthdrawal autorise*/
	EXTCC_APPEL_PORT              =(EXTCC_APPEL  | 0x0026),		/*!<  Port if DNS */
	
	EXTCC_PROT_CONF               =(EXTCC_PROT	| 0x0000),		/*!<  Protocol configuration */
	EXTCC_PROT_SET_STD            =(EXTCC_PROT	| 0x0001),		/*!<  Standard SET command*/
	EXTCC_PROT_SET_APPLI          =(EXTCC_PROT	| 0x0002),		/*!<  Application SET commande*/
	EXTCC_PROT_SET_FIXATION       =(EXTCC_PROT	| 0x0003),		/*!<  SET command (fix the parameters afetr "COM")*/
	EXTCC_PROT_PARITE_APPLI       =(EXTCC_PROT	| 0x0004),		/*!<  Parity managed by the application */
	EXTCC_PROT_FORMAT_CAR         =(EXTCC_PROT	| 0x0005),		/*!<  EBCDIC or ASCII */
	EXTCC_PROT_LG_TRAME           =(EXTCC_PROT	| 0x0006),		/*!<  max length of a framework. (A message = several frameworks) */
	EXTCC_PROT_X25                =(EXTCC_PROT	| 0x0010),		/*!<  X25 Protocol*/
	EXTCC_PROT_X28                =(EXTCC_PROT	| 0x0011),		/*!<  X28 Protocol*/
	EXTCC_PROT_TYPE               =(EXTCC_PROT	| 0x0012),		/*!<  "Value" contain the CB2A version*/
	EXTCC_PROT_MESSAGE_BANCAIRE   =(EXTCC_PROT	| 0x0011),		/*!<  TO wait for a bank message*/
	EXTCC_PROT_SET_CHAINAGE       =(EXTCC_PROT	| 0x0013),		/*!<  Chained-list SET commande ! same value than EXTCC_PROT_X28 for compatibility*/
	EXTCC_PROT_V42A               =(EXTCC_PROT	| 0x001A),		/*!<  V42A */
	EXTCC_PROT_APPLI              =(EXTCC_PROT	| 0x001B),		/*!<  Protocol known by the application */
	EXTCC_PROT_PSWD               =(EXTCC_PROT	| 0x0020),		/*!<  Password after "COM" or server */
	EXTCC_PROT_TRAME_ACQ          =(EXTCC_PROT	| 0x0021),		/*!<  Settlement management for a framework*/
	EXTCC_PROT_MSG_ACQ            =(EXTCC_PROT	| 0x0022),		/*!<  Settlement management for a message*/
	EXTCC_PROT_TRAME_RSP          =(EXTCC_PROT	| 0x0023),		/*!<  Wait for the response framework after a framework emission.*/
	EXTCC_PROT_MSG_RSP            =(EXTCC_PROT	| 0x0024),		/*!<  Wait for the response message after a message emission. */
	EXTCC_PROT_MULTI              =(EXTCC_PROT	| 0x0025),		/*!<  Multi-Window*/
	EXTCC_PROT_TOUCHE_ANNULE      =(EXTCC_PROT	| 0x0030),		/*!<  Cancel Key management.*/
			
	EXTCC_CR_CONF                 =(EXTCC_CR	| 0x0000),		/*!<  Read all the reports.*/
	EXTCC_CR_RET                  =(EXTCC_CR	| 0x0001),		/*!<  Report version 5.1*/
	EXTCC_CR_ERREUR               =(EXTCC_CR	| 0x0002),		/*!<  Syntax Error report, unknown parameter*/
	EXTCC_CR_ECHEC                =(EXTCC_CR	| 0x0003),		/*!<  Reason of the failure*/
	EXTCC_CR_PHASE                =(EXTCC_CR	| 0x0004),		/*!<  Accurate stop phase of the function*/
	EXTCC_CR_TRACE                =(EXTCC_CR	| 0x0010),		/*!<  Track management*/
	EXTCC_CR_TRACE_CR_IMP         =(EXTCC_CR	| 0x0011),		/*!<  Phases report printing*/
	EXTCC_CR_TRACE_TRAME_IMP      =(EXTCC_CR	| 0x0012),		/*!<  Framework printing*/
	EXTCC_CR_TRACE_AFF            =(EXTCC_CR	| 0x0013),		/*!<  Track display*/

	EXTCC_TIMER_CONF              =(EXTCC_TIMER	| 0x0000),		/*!<  Timers Configuration*/
	EXTCC_TIMER_TEL               =(EXTCC_TIMER	| 0x0001),		/*!<  Max waiting time between number and call*/
	EXTCC_TIMER_CARA              =(EXTCC_TIMER	| 0x0002),		/*!<  Max waiting time between two characters*/
	EXTCC_TIMER_TRAME             =(EXTCC_TIMER	| 0x0003),		/*!<  Max waiting time between two frameworks.*/
			
	EXTCC_AFF_CONF                =(EXTCC_AFF	| 0x0000),			/*!<  Messages Configuration*/
	EXTCC_AFF_MESS                =(EXTCC_AFF	| 0x0001),			/*!<  Switch the phases, display the message or not.*/
					
	EXTCC_DATA_IPDU               =( EXTCC_DATA	| 0x0001),		/*!<  List of the ipdu and the values */
	EXTCC_DATA_TAG                =( EXTCC_DATA	| 0x0002),		/*!<  List of the TAG and the values */
	EXTCC_DATA_TRAME              =( EXTCC_DATA	| 0x0003),		/*!<  Size + data of the framework*/
	EXTCC_DATA_MESSAGE            =( EXTCC_DATA	| 0x0004),		/*!<  Size + data of the message */
	EXTCC_DATA_CONFIG             =( EXTCC_DATA	| 0x0005), 		/*!<  Complete List of the configuration */
	EXTCC_DATA_TAB_REC            =( EXTCC_DATA	| 0x0006),		/*!<  Size + data of the message */
	EXTCC_DATA_TAB_REC_CA         =( EXTCC_DATA	| 0x0007),		/*!<  Size + data of the message */
	EXTCC_DATA_TAB_REC_TO         =( EXTCC_DATA	| 0x0008) 		/*!<  Size + data of the message */
} E_EXTCC_TYPE ;

#define CC_ERR_DEV   	0xFFFF	/* non developpe */
#define CC_UC_DEFAULT	0xFF		/* valeur par defaut sur un unsigned char */
#define CC_US_DEFAULT	0xFFFF	/* valeur par defaut sur un unsigned short */
#define CC_INTERDIT     0x00
#define CC_OBLIGATOIRE  0xFF
#define CC_FACULTATIF   0x01

#define CC_TRACE_NON     0x00
#define CC_TRACE_LISTE   0x01
#define CC_TRACE_CONF    0x02
#define CC_TRACE_MODEM   0x04
#define CC_TRACE_PAD     0x08
#define CC_TRACE_APPEL   0x10
#define CC_TRACE_PROT    0x20
#define CC_TRACE_ALL     0xFF

#define CC_MODEM_INTERNE 0x00
#define CC_MODEM_EXTERNE 0xF0
#define CC_MODEM_RTC     0x00
#define CC_MODEM_GSM     0x01
#define CC_MODEM_GPRS    0x02
#define CC_MODEM_RNIS	 0x03 /* sans distinction */
#define CC_MODEM_RNIS_B  0x04
#define CC_MODEM_RNIS_D  0x05
#define CC_MODEM_TCPIP   0x06
#define CC_MODEM_HOTE    0x07


#define CC_AFF_MAX	      40
#define CC_PH_INIT_MODEM    0
#define CC_PH_NUMEROTATION  1
#define CC_PH_APPEL         2
#define CC_PH_TRANSFERT     3
#define CC_AFF_NB_MESS      4

#define CC_PAD_IP  3
#define CC_PAD_EBA 2
#define CC_PAD_EMA 1
#define CC_NUM_PAD 20 

#define CC_IPDU_MAX 40
#define CC_MAX_BUF_DATA (SIZE_BUF_IN+6)
#define CC_MAX_BUF_LIST (SIZE_BUF_IN+6)

//#define CC_MAX_RACCORD  20
//#define CC_MAX_APPEL    40
//#define CC_MAX_COMP     40
//#define CC_MAX_STANDARD 20
/* 05/2004 SMO/ETU/RA/04/20093 - Taille parametres SET 20->30 */
#define CC_MAX_SET      30
#define CC_MAX_PSWD     20

#define CC_APPEL_DIVERS     0
#define CC_APPEL_INITIALISATION   1
#define CC_APPEL_DEM_AUTORISA     2
#define CC_APPEL_TELEPARAM_AUTO   3
#define CC_APPEL_TELEPARAM_MANU   4
#define CC_APPEL_TELECOLLE_AUTO   5
#define CC_APPEL_TELECOLLE_MANU   6

#define CC_DCNX_LOGIQUE  0x01
#define CC_DCNX_PHYSIQUE 0x10

#define CC_SERVICE_TELECOLLECTE        1
#define CC_SERVICE_TELECHARGEMENT      2
#define CC_SERVICE_TELEPARAMETRAGE     3
#define CC_SERVICE_AUTORISATION        4

#define CC_PROT_V42A   0x01
#define CC_PROT_CB2A   0x02
#define CC_PROT_CBCOM  0x03
#define CC_PROT_CBSA   0x04
#define CC_PROT_CBPR   0x10
#define CC_PROT_CAPR   0x11
#define CC_PROT_SVPR   0x12
#define CC_PROT_SFPR   0x13
#define CC_PROT_CHPR   0x14
#define CC_PROT_MULTI  0x15

/*
======================================================================
			Data Structures Definition
======================================================================
*/
/*! @brief  EXTCC Report.*/
typedef struct 
{
	unsigned short usRaison;						//!< Report.*/
} S_EXTCC_CR; 




/*! @brief  Define the modem configuration.*/
typedef struct 
{
	unsigned char  ucMode;									/*!<  0xFF = Default,  0 = Internal, 0xF0 = port 0, 0xF1 = port 1 ... */
	unsigned char  ucType;									/*!<  0xFF = Default, RTC = 0x00, GSM = 0x01, GPRS = 0x02, RNIS_D = 0x03, RNIS_C = 0x04*/
	unsigned short usModel;									/*!<  0xFFFF = Default model of the external modem*/
	unsigned short usModulationMax;					/*!<  0xFFFF = Default, 12 = 1200, 24 = 2400, 96 = 9600, 144 = 14400 */
	unsigned short usSerialLink;						/*!<  0xFF = Defaut, 0 = internal, 0xF0 = port 0, 0xF1 = port 1 ... */
	unsigned short usRuf2;
} S_EXTCC_MODEM_CONF;




/*! @brief  Define the PAD configuration.*/
typedef struct 
{
	unsigned char  ucType;							/*!<  0xFF = Defaut 0 = EBA 1 = EMA */
	unsigned short usTimerTNR;					/*!<  in seconds*/
	unsigned char  ucLgNum;							/*!<  Length of the PAD number*/
	unsigned char  ucNum[CC_NUM_PAD];		/*!<  PAD number or join address*/
	unsigned short usModulationMax;			/*!<  0xFFFF=default  12=1200  24=2400 96=9600 144=14400 */
	unsigned char  ucRaison;						/*!<  reason of the call*/
	unsigned char  ucDernierMess;				/*!<  different of zero if TPE is the last sent to PAD */
	unsigned char  ucDcnx;							/*!<  Disconnexion informations.*/
	unsigned char  ucRuf1;							/*!<  Reserved for future use.*/
	unsigned short usDcnxTO;						/*!<  Disconnexion informations.*/
	unsigned short usRuf2;							/*!<  Reserved for future use.*/
} S_EXTCC_PAD_CONF;


/*! @brief  Define the server configuration*/
typedef struct 
{
	unsigned char  tucNum[40];					/*!<  SERVER number + complementary data or call address*/
} S_EXTCC_SERVEUR_CONF;




/*! @brief  Define the protocol (type, version...).*/
typedef struct 
{
	unsigned char  ucProt;							/*!<  Type of the protocol*/
	unsigned char  ucOption;						/*!<  forbidden, obligatory, optionnal*/
	unsigned short usVersion;						/*!<  version without point or comma */
} S_EXTCC_PROT;




/*! @brief  Give informations about an IPDU.*/
typedef struct 
{
	unsigned char usType;											/*!<  Type of IPDU*/
	unsigned char ucLg;												/*!<  length of IPDU*/
	unsigned char tucValeur[CC_IPDU_MAX];			/*!<  Value  of IPDU*/
} S_EXTCC_IPDU ;




/*! @brief  Define an EXTCC message.*/
typedef struct 
{
	unsigned char  tucBuf[CC_MAX_BUF_DATA];			/*!< data Buffer containing the message.*/
} S_EXTCC_MES ;




/*! @brief  Define an EXTCC profile.*/
typedef struct 
{
	unsigned char  tucBuf[PROFILE_NAME_SIZE];		/*!< data Buffer containing the profile name.*/
} S_EXTCC_PROFILE ;




/*! @brief  Define a structure giving informations about the display of a message.*/
typedef struct 
{
	unsigned char  ucPhase;							/*!<  display phase*/
	unsigned char  ucNum;								/*!<  number of the message. 0=no display*/
	unsigned char  ucEfface;						/*!<  Display with/without cleaning*/
	unsigned char  ucPosition;					/*!<  Position on the screen (not used by the display function)*/
	unsigned char  ucAttente;						/*!<  wait or not after the display*/
	unsigned char  ucLgMess;						/*!<  length of the message to display*/
	unsigned char  tucMess[CC_AFF_MAX];	/*!<  Message to display.*/
} S_EXTCC_AFF ;




/*! @brief  This structure define a parameter to add or delete form a list.*/
typedef struct
{
	unsigned short eType ;									/*!<  type of the parameter*/
	unsigned short usLg ;										/*!<  length of the parameter*/
	union U_EXTCC_PARAM
	{
		FILE                 *pFile;						/*!<  handle on the device (modem or GPRS)*/
		unsigned char        tucBuf[CC_MAX_BUF_DATA];		/*!<  data*/
		S_EXTCC_CR           sCr;								/*!<  EXTCC report*/
		unsigned int         uiInt;							/*!<  re-define an unsigned integer*/
		int	                 iInt;							/*!<  re-define an integer*/
		unsigned short       usShort;						/*!<  re-define an unsigned short*/
		unsigned char        ucChar;						/*!<  re-define an unsigned character*/
		S_EXTCC_PROT         sProt;							/*!<  EXTCC Protocol*/
		S_EXTCC_AFF          sAff;							/*!<  EXTCC display informations*/
		S_EXTCC_IPDU         sIpdu;							/*!<  EXTCC IPDU*/
		S_EXTCC_MES          sMess;							/*!<  EXTCC message*/
		S_EXTCC_MODEM_CONF   sModem;						/*!<  EXTCC modem configuration*/
		S_EXTCC_PAD_CONF     sPad;							/*!<  EXTCC PAD configuration*/
		S_EXTCC_SERVEUR_CONF sServeur;					/*!<  EXTCC server configuration*/
       	S_EXTCC_PROFILE      sProfile;			/*!<  EXTCC profile*/
		TAB_REC_CA           sTabRecCa;					/*!<  Entry table for reception on a stop code.*/
		TAB_REC_TO           sTabRecTo;					/*!<  Entry table for reception on a stop code.*/
	} uP;
} S_EXTCC_PARAM;


/*! @brief  Define an EXTCC list.*/
typedef struct
{
	unsigned short usNbParam ;									/*!<  parameters count*/
	unsigned short usTaille ;										/*!<  size for the list*/
	unsigned char  ucMaxBuf[CC_MAX_BUF_LIST];		/*!<  data of the list*/
} S_EXTCC_LISTE;





/*! @brief  Define the bank connection parameters.*/
typedef struct
{
	unsigned short     usPhase;														/*!<  For the EIS308 communication layer*/
	S_EXTCC_MODEM_CONF sModem;														/*!<  EXTCC modem configuration*/
	S_EXTCC_PAD_CONF   sPad;															/*!<  EXTCC PAD configuration*/
	unsigned char      ucV42A;														/*!<  connection V42A (Y/N)*/
	unsigned char      ucToMessageBancaire;								/*!<  bank message timeout*/
	unsigned char      ucMultiFenetre;										/*!<  multi-window (Y/N)*/
	unsigned char      ucProtocole;												/*!<  communication protocol*/
	unsigned short     usProtocole_version;								/*!<  protocol version*/
	unsigned char      ucToucheAnnule;										/*!<  CANCEL management (Y/N)*/
	unsigned char      ucTrace;														/*!<  trace*/
	unsigned char      ucLgStandard;											/*!<  Length of the standard data*/
	unsigned char      uiSSLActif;												/*!<  SSL active (Y/N)*/
	int                uiProfilSSL;												/*!<  nameof the SSL profile*/
	unsigned char      uiRepliActif;											/*!<  withdrawal active (Y/N)*/
	unsigned char      tucStandard[ Taille_CMD_STAND ];		/*!<  standard data*/
	unsigned char      ucLgRaccord;											  /*!<  length of the PAD data*/
	unsigned char	   	 tucRaccord[Taille_ADR_RACCORD];		/*!<  PAD data*/
	unsigned char      ucLgAppel;													/*!<  length of the X25 server address*/
	unsigned char      tucAppel[ Taille_ADR_APPEL ];			/*!<  X25 server address*/
	unsigned char      ucLgPort;													/*!<  length of the port*/
	unsigned char      tucPort[ Taille_ADR_APPEL ];				/*!<  port data*/
	unsigned char      ucLgAppelComp;											/*!<  length of the complementary data*/
	unsigned char      tucAppelComp[ Taille_COMPL_X25 ]; 	/*!<  complementary data*/
	unsigned char      ucLgSet;														/*!<  length of the set*/
	unsigned char      tucSet[ CC_MAX_SET ];							/*!<  data of the set */
	unsigned char      ucLgPswd;													/*!<  length of the password*/
	unsigned char      tucPswd[ CC_MAX_PSWD ];						/*!<  data of the password*/
	unsigned char      ucChgtParite;											/*!<  parity change (Y/N)*/
	unsigned char      ucSetFixation;											/*!<  set fixed (Y/N)*/
	unsigned char      ucSetChainage;											/*!<  chained set (Y/N)*/
	unsigned char      ucRepliEnCours;															/*!<  Reserved for future use*/
	S_EXTCC_AFF        tsAff[CC_AFF_NB_MESS];							/*!<  array of messages*/
} S_CC_Connexion;


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function allows to establish the connexion (CBCOM layer).
 * @param p_param : pointer to structure S_EXTCC_LISTE, connexion parameters.
 * @return 0
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 14) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_connexion:KSFAM_CB2A:0x30
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int            EXTCC_connexion( S_EXTCC_LISTE *p_param );


/*! @brief Emission of an applicative framework.
 * @param p_data : pointer to structure S_EXTCC_LISTE, the list of asked data.
 * @return 0
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 15) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_emission:KSFAM_CB2A:0x37
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int            EXTCC_emission( S_EXTCC_LISTE *p_data );

/*! @brief Reception of an applicative framework.
 * @param p_data : pointer to structure S_EXTCC_LISTE, the list of asked data
 * @return 0
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_reception:KSFAM_CB2A:0x38
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int            EXTCC_reception( S_EXTCC_LISTE *p_data );


/*! @brief This function returns the modem's handle pointer.
 * @return pointer to modem peripheric.
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 17) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_Handle:KSFAM_CB2A:0x31
//  @GSIM_A:0:ONE_ADDRESS 
// \endif
extern FILE          *EXTCC_Handle( void );


/*! @brief This function resets the modem's reception buffer.
 * @return None
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 18) if function does not exist
// \if SIMULATION
//  @GSIM_F:EXTCC_Reset_buf:KSFAM_CB2A:0x32
// \endif
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern void           EXTCC_Reset_buf(void);


/*! @brief This function returns the numbers of the expected and sent LT frameworks.
 * @param xpucData : the numbers of frames.
 * - byte 1 : expected framework
 * - byte 2 : sent framework
 * @return None
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 19) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_Numero_Message_V42A:KSFAM_CB2A:0x3C
//  @GSIM_A:1:ARRAY_OF(2)
// \endif
extern void           EXTCC_Numero_Message_V42A( unsigned char *xpucData );


/*! @brief This function sets to zero the list of parameters
 * @param p_data : pointer to structure S_EXTCC_LISTE.
 * @return None
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 20) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_init_liste:KSFAM_CB2A:0x39
//  1:ONE_POINTER
// \endif
extern void           EXTCC_init_liste( S_EXTCC_LISTE  * p_data);


/*! @brief This function adda a parameter in the list.
 * @param p_data : pointer to structure S_EXTCC_LISTE.
 * @param xpsParam : pointer to stucture S_EXTCC_PARAM
 * @return
 * - 0 ok
 * - 1 overtaking.
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 21) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  EXTCC_ajoute_liste:KSFAM_CB2A:0x3A
//  1:ONE_POINTER
//  2:USE_CODE ou SUPPLIED
// \endif
extern unsigned char  EXTCC_ajoute_liste( S_EXTCC_LISTE   * p_data , S_EXTCC_PARAM	*xpsParam );


/*! @brief This function extracts a parameter of the list.
 * @param pCCListe : pointer to structure S_EXTCC_LISTE.
 * @param eType : type of parameter to extract
 * @param pgsParam : pointer to stucture S_EXTCC_PARAM
 * @return
 * - 0 if find and ok.
 * - 1 otherwise.
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 22) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  EXTCC_extraire_liste:KSFAM_CB2A:0x3B
//  1:ONE_POINTER
//  3:SUPPLIED
// \endif
extern unsigned char  EXTCC_extraire_liste( S_EXTCC_LISTE  *pCCListe,unsigned short eType ,S_EXTCC_PARAM  *pgsParam);


/*! @brief This function disconnects the communication (CBCOM layer)
 * @param xp_conf : pointer to structure S_EXTCC_LISTE, the list of asked data.
 * @return 0
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXTCC_deconnexion:KSFAM_CB2A:0x36
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int            EXTCC_deconnexion( S_EXTCC_LISTE *xp_conf );


#endif
/*! @} **/

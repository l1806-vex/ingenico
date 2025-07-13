/*! @addtogroup KSFAM_OS
	* @{
 */


#ifndef OEM_SYS_H
#define OEM_SYS_H

#include "uiram.h"         // pour spy_data_t


/*
======================================================================
					List of Defines
======================================================================
*/

// Utilises dans les numeros de version dans les traces


/*
===================================
				MODULES SECURITAIRES
===================================
*/

#define DRIVER_LIAISON_INTER_UC 1		/*!< IUC driver number */
#define DRIVER_KEYBOARD         2		/*!< Keyboard driver number */
#define DRIVER_DISPLAY_64       3		/*!< Display 128x64 driver number */
#define DRIVER_COM              4		/*!< COM driver number */
#define DRIVER_PRINTER          5		/*!< Printer driver number */
#define DRIVER_RETRO_ECLAIRAGE  6		/*!< Backlight driver number */
#define DRIVER_BUZZER           7		/*!< Buzzer driver number */
#define DRIVER_RTC              8		/*!< RTC driver number */
#define DRIVER_ISO2             9		/*!< ISO2 driver number */
#define DRIVER_SECURITE         10		/*!< Security driver number */
#define MODULE_SYSTEME          11		/*!< System module number */
#define MODULE_SWI              12		/*!< SWI module number */
#define MODULE_SCHEMA           13		/*!< Schemes module number */
#define DRIVER_DISPLAY_128      14		/*!< Display 128x128 driver number */
#define DRIVER_IAPP			    15		/*!< IAPP driver number */
#define DRIVER_DMMC             16		/*!< MMC driver number */
#define DRIVER_LEDS             17		/*!< Leds driver number */
#define DRIVER_CLESS            18		/*!< Cless driver number */
#define DRIVER_SWIPE2           19		/*!< Swipe2 driver number */
#define DRIVER_SWIPE31          20		/*!< Swipe31 driver number */
#define DRIVER_SWIPE3           21		/*!< Swipe3 driver number */
#define DRIVER_SWIPE_INTER_UC   22		/*!< IUC Swipe driver number */
#define DRIVER_DISPLAY_2x16     24		/*!< Display 2x16 driver number */
#define DRIVER_TOUCH_SCREEN     26		/*!< Touch Screen driver number */
#define DRIVER_CONFIG_SYSTEM    27	 /*!< Configuration system driver number (internal use) */
#define DRIVER_LIAISON_INTER_UC_THUNDER	 28		/*!< IUC thunder driver number (thunder to thunder )) */
#define DRIVER_GATEWAY_INTER_UC	 29		/*!< GATEWAY IUC*/
#define DRIVER_ADMIN_INTER_UC	 30		/*!< IUC admin channel (thunder to thunder)*/

/*
===================================
				MODULES APPLICATIFS
===================================
*/


#define DRIVER_KEYBOARD_APP       102			/*!< Application keyboard driver number */
#define MODULE_SCHEMA_APP         112 			/*!< Application scheme driver number */
#define DRIVER_DISPLAY_APP_64     103			/*!< Application display 128x64 driver number */
#define DRIVER_DISPLAY_APP_128    113			/*!< Application display 128x128 driver number */
#define DRIVER_DISPLAY_APP_COLOR  123			/*!< Application color display driver number */


/*
======================================================================
					LIAISON INTER UC
======================================================================
*/


/*
===================================
	  CONFIGURATION DE LA LIAISON
===================================
*/

//serial link
#define	NB_MAX_RE_EM                15      /*!< Max number of retry */
#define	NB_MAX_RE_EM_AVEC_DELAI     5       /*!< Max number of retry */
#define TIMEOUT_TX_LIAISON_UC       5 	  	/*!< unit: 20-30ms  */
#define DELAI_ATTENTE_RE_EM         2       /*!< unit: 10-20ms    */
#define TIMEOUT_RX_LIAISON_UC       15      /*!< unit: 15 bits  */
#define TAILLE_BUF_INTER_UC	        1048    /*!< Receive buffer size */
#define	LIAISON_UC_HISR_PRIORITY    0       /*!< hisr */

//usb
#define	NB_MAX_RE_EM_USB                10      /*!< Max number of retry */
#define	NB_MAX_RE_EM_AVEC_DELAI_USB     5       /*!< Max number of retry */
#define TIMEOUT_TX_LIAISON_UC_USB       4       /*!< unit: 10 */
#define DELAI_ATTENTE_RE_EM_USB         3       /*!< unit: 10-20ms    */


/*
===================================
	   CANAUX DE DIALOGUES
===================================
*/


//serie
#define CANAL_SCHEMAS        			0		/*!< Schemes IUC channel */
#define CANAL_SYSTEME        			1		/*!< Systeme IUC channel */
#define CANAL_CLAVIER        			2		/*!< Keyboard IUC channel */
#define CANAL_DISPLAY        			3		/*!< Display IUC channel */
#define CANAL_RETRO          			4		/*!< Backlight IUC channel */
#define CANAL_CAM_SAM        			5		/*!< CAM IUC channel */
#define CANAL_IAPP           			6		/*!< IAPP IUC channel */
#define CANAL_HORODATEUR     			7		/*!< RTC (time) IUC channel */
#define CANAL_DIAGNOSTIC     			8		/*!< Diagnostic IUC channel */
#define CANAL_TEST_1         			9		/*!< Test 1 IUC channel */
#define CANAL_TEST_2         			10		/*!< Test 2 IUC channel */
#define CANAL_TEST_3         			11		/*!< Test 3 IUC channel */
#define CANAL_CAM_EVT        			12		/*!< CAM Event IUC channel */
#define CANAL_BUZZER         			13		/*!< Buzzer IUC channel */
#define CANAL_LEDS           			14		/*!< Leds IUC channel */
#define CANAL_CLESS          			15		/*!< CLESS IUC channel */
#define CANAL_SWIPE          			16		/*!< Swipe IUC channel */
#define CANAL_DISPLAY_ALPHANUM	  		17		/*!< Alphanumeric display IUC channel */
#define CANAL_DISPLAY_FULL_COLOR		18		/*!< Color Display IUC channel */
#define CANAL_SECURITE            		19		/*!< Security IUC channel */
#define CANAL_TSCREEN             		20		/*!< Touch Screen IUC channel */
#define CANAL_IAPP2           			21		/*!< IAPP IUC channel */
#define CANAL_ADMIN           			22		/*!< IUC administration channel */
#define	NB_MAX_CANAUX		 	        23		/*!< Max IUC channel number */

//usb
#define	NB_MAX_CANAUX_USB	 	      	NB_MAX_CANAUX		/*!< Max USB IUC channel number */
#define CANAL_PROTOCOLE_USB       		0xFF				/*!< USB protocol channel */


/*
===================================
	STRUCTURE DE DONNEES DES TRAMES
===================================
*/


/*! @brief Frame Header */
typedef struct
{
    unsigned short   NumCanal;		/*!< Channel number */
    unsigned short   LgDta;			/*!< Data length */
}
BUF_ENTETE_T;



/*! @brief Trame (Entete + Data) */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;		/*!< Frame header */
    unsigned char    Dta[TAILLE_BUF_INTER_UC-sizeof(BUF_ENTETE_T)];		/*!< Data */
}
ENCODE_BUF_T;



/*! @brief Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char    DtaBrute[TAILLE_BUF_INTER_UC];		/*!< Raw data */
    ENCODE_BUF_T     DtaDecode;		/*!< Decoded data */
}
BUF_INTER_UC_T;


// Frame header with 3 data bytes

#define TAILLE_BUF_INTER_3_UC (sizeof(BUF_ENTETE_T)+3)	/*!< Size of the IUC 3 buffer */


/*! @brief Trame (Entete + Data) */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;			/*!< Frame header */
    unsigned char    Dta[TAILLE_BUF_INTER_3_UC-sizeof(BUF_ENTETE_T)];			/*!< Data */
}
ENCODE_BUF_3_T;



/*! @brief Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char      DtaBrute[TAILLE_BUF_INTER_3_UC];		/*!< Raw data */
    ENCODE_BUF_3_T     DtaDecode;		/*!< Decoded date */
}
BUF_INTER_UC_3_T;



// CODE DE RETOUR DES FONCTIONS DU FIRMWARE
#define     BASE_CODE_ERREUR_INTER_UC   0									/*!< IUC root error code  */
#define     OK_INTER_UC                 (BASE_CODE_ERREUR_INTER_UC    )		/*!< Return if the IUC transfer was successful */
#define     KO_INTER_UC                 (BASE_CODE_ERREUR_INTER_UC -1 )		/*!< Return if the IUC transfer was not acknowledge */
#define     TIMEOUT_INTER_UC            (BASE_CODE_ERREUR_INTER_UC -2 )		/*!< Return if the IUC transfer ended on timeout (no ack nor nack) */


// PRIORITE DE l'INTERRUPTION USART
#define PRIORITY_IT_USART_INTER_UC      (AIC_SRCTYPE_INT_LEVEL_SENSITIVE | 0x00)		/*!< Priority of the IUC Usart interrupt */


/*
======================================================================
					DRIVER SYSTEM  (TACHES + EVENEMENTS + RTC + SYSTEM)
======================================================================
*/


/*
============================================
	  Informations concernant la TASK SYSTEM
============================================
*/


#define TASK_SYSTEM_STACK_SIZE             4000		/*!< Size of the system task stack */
#define TASK_SYSTEM_PRIORITY                  5		/*!< Priority of the system task */
#define USER_TASK_PRIORITY_BASE             128		/*!< Root priority of the user tasks */
#define TASK_SYSTEM_TIME_SLICE               20		/*!< Time slice of the system task */


/*
============================================
	  Informations concernant la HISR SYTEM
============================================
*/



//#define HISR_SYSTEM_STACK_SIZE              512
#define HISR_SYSTEM_PRIORITY              0					/*!< Priority of the system Hisr */

#define EVENT_SCHEMA                      0x00000001		/*!< Scheme event */
#define EVENT_RTC                         0x00000002		/*!< RTC event */
#define EVENT_LINKPER_FOR_TASK_SYSTEM     0x00000004		/*!< Linker for system task event */
#define EVENT_LINKPER_FOR_TASK_PERIOD     0x00000008		/*!< Linker for periodical task event */
#define EVENT_SEND_IAPP                   0x00000010		/*!< Send on Iapp event */
#define EVENT_FIN_SCHEMA                  0x00000020		/*!< Scheme end event */
#define EVENT_DELETE_TASK                 0x00000040		/*!< Task deleted event */
#define EVENT_RESET                       0x00000080		/*!< Reset event */
#define EVENT_SYSTEME                     0x00000100		/*!< System event */
#define EVENT_RUF1                        0x00000200		/*!< Ruf1 event */
#define EVENT_RUF2                        0x00000400		/*!< Ruf2 event */
#define EVENT_RUF3                        0x00000800		/*!< Ruf3 event */
#define EVENT_SEND_IAPP_PPR               0x00001000		/*!< Send on PPR Iapp event */
#define EVENT_RESET_PPR                   0x00002000		/*!< PPR reset event */
#define EVENT_SYSTEME_PPR                 0x00004000		/*!< PPR system event */
#define EVENT_DELETE_TASK_OEM             0x00008000		/*!< OEM task deleted event */
#define EVENT_ALARME_RTC                  0x00010000		/*!< RTC alarm event */
#define EVENT_SEND_IAPP_C30               0x00100000		/*!< Send on C30 Iapp event */
#define EVENT_RESET_C30                   0x00200000		/*!< C30 reset event */
#define EVENT_SYSTEME_C30                 0x00400000		/*!< C30 system event */
#define EVENT_SEND_IAPP_CAD30USR          0x01000000		/*!< Send on CAD30USR Iapp event */
#define EVENT_RESET_CAD30USR              0x02000000		/*!< CAD30USR reset event */
#define EVENT_SYSTEME_CAD30USR            0x04000000		/*!< CAD30USR system event */
#define EVENT_SCHEMA_USB				  0x08000000		/*!< USB scheme event */
#define EVENT_SCHEMA_USB_READER			  0x10000000		/*!< Reader USB scheme event */
#define EVENT_SEND_IAPP2                  0x20000000		/*!< Send on Iapp event */

#define TAILLE_BUF_RTC                    21				/*!< Size of the RTC buffer */

/*
============================================
	 Informations concernant le protocole RTC
============================================
*/

#define TIMEOUT_REPONSE_RTC                 200					/*!< Timeout on RTC answer */


/*
============================================
	  STRUCTURE DE DONNEES DES TRAMES RTC
============================================
*/


/*! @brief Real Time Clock  */
typedef struct
{
    unsigned char    Cmd;			/*!< RTC Command */
    DATE             Date;			/*!< Date */
}
DATA_RTC_T;



/*! @brief trame RTC (entete+data)*/
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;		/*!< Frame header */
    DATA_RTC_T       DataRtc;			/*!< RTC data */
    int              CptRendu;			/*!< RTC report code */
}
ENCODE_BUF_RTC_T;


/*! @brief Union {(Trame brute) ou (Entete + Data)}*/
typedef union
{
    unsigned char    DataBrute[TAILLE_BUF_RTC];		/*!< Raw data */
    ENCODE_BUF_RTC_T DataDecode;					/*!< Decoded data */
}
BUF_RTC_T;


/*
============================================
	   DESCRIPTION DES TRAMES RTC
============================================
*/


#define RTC_CMD_READ           0x01		/*!< RTC read command */
#define RTC_CMD_WRITE          0x02		/*!< RTC write command */


/*
============================================
	CODE DE RETOUR DANS LA TRAME DE REPONSE
============================================
*/

#define     BASE_CODE_ERREUR_RTC      0								/*!< RTC root report code */
#define     OK_RTC                    (BASE_CODE_ERREUR_RTC)		/*!< Return if the RTC command was successful */
#define     KO_RTC                    (BASE_CODE_ERREUR_RTC-1)		/*!< Return if the RTC command is KO */
#define     KO_RTC_PROBLEME_EMISSION  (BASE_CODE_ERREUR_RTC-3)		/*!< Return if the RTC command is KO due to a transmit error */
#define     KO_RTC_PAS_DE_REPONSE     (BASE_CODE_ERREUR_RTC-4)		/*!< Return if the RTC command ended on timeout */


/*
============================================
	STRUCTURE DE DONNEES DES TRAMES SYSTEME
============================================
*/


// System Frame
#define TAILLE_DATA_SYSTEME                   32		/*!< Size of the system data */


/*! @brief Structure of the system frame */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;					/*!< Frame header */
    unsigned char    Cmd;							/*!< Command */
    unsigned int     Adresse_Dump;					/*!< Dump address */
    char             Data[TAILLE_DATA_SYSTEME];   	/*!< Data */
}
ENCODE_BUF_SYS_CMD_T;


// System diagnostic frame
#define TAILLE_DIAGNOSTIC_SYSTEME            256		/*!< Size of the system diagnostic */


/*! @brief Structure of the diagnostic frame */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;							/*!< Frame header */
    unsigned char    Cmd;									/*!< Command */
    spy_data_t       Spy_Data;								/*!< Spy data */
    unsigned char    Diagnostic[TAILLE_DIAGNOSTIC_SYSTEME];	/*!< Diagnostic data */
    int              CptRendu;								/*!< Report code */
}
ENCODE_BUF_SYS_DIAG_T;

typedef struct
{
 BUF_ENTETE_T       EnteteTrame;
 unsigned char      Cmd;
 unsigned int       MaintenanceSousCmd;
 char               Data[TAILLE_DATA_SYSTEME];
}
ENCODE_BUF_SYS_CMD_MAINTENANCE_T;

/*! @brief Union {(Trame brute) ou (Entete + Data)}  (Commandes) */
typedef union
{
    unsigned char          DataBrute[sizeof(ENCODE_BUF_SYS_CMD_T)];		/*!< Raw data */
    ENCODE_BUF_SYS_CMD_T   DataDecode;		/*!< Decoded data */
    ENCODE_BUF_SYS_CMD_MAINTENANCE_T      DataDecodeMaintenance;
}
BUF_SYS_CMD_T;


/*! @brief Union {(Trame brute) ou (Entete + Data)}  (Diagnostics) */
typedef union
{
    unsigned char          DataBrute[sizeof(ENCODE_BUF_SYS_DIAG_T)];		/*!< Raw data */
    ENCODE_BUF_SYS_DIAG_T  DataDecode;		/*!< Decoded data */
}
BUF_SYS_DIAG_T;


/*! @brief Union {SYS_CMD ou SYS_DIAG} */
typedef union
{
    BUF_SYS_CMD_T   DataSysCmd;		/*!< System command structure */
    BUF_SYS_DIAG_T  DataSysDiag;	/*!< System diagnostic structure */
}
BUF_SYS_T;

// ----------------------------------------------------
// Trame du MODE LOCK du PIN_ENTRY sur un VAR ID (CTAP)
// ----------------------------------------------------
typedef struct
{
   unsigned char   SousCmd;             // sous commande du Mode Lock Pin Entry: READ ou WRITE du var_id
   unsigned char   Ruf;                 // Ruf (pour combler le trou)
   unsigned short  VarId;               // Valeur du VAR ID ('0' is not allowed)
   int             CptRenduSousCmd;     // Compte rendu de la sous command
} MODE_LOCK_PIN_ENTRY_T;

typedef struct
{
    BUF_ENTETE_T              EnteteTrame;
    unsigned char             Cmd;
    MODE_LOCK_PIN_ENTRY_T     ModeLockPinEntry;
}
ENCODE_BUF_MODE_LOCK_PIN_ENTRY_T;

// ---------------------------------------------------------------------------------
// Trame de Validation/Invalidation du MOZART par imposition des mains (ZKA-Germany)
// ---------------------------------------------------------------------------------
typedef struct
{
   unsigned char   SousCmd;             // sous commande MOZART par imposition des mains : VALIDATE / INVALIDATE / STATUS
   unsigned char   Ruf;                 // Ruf (pour combler le trou)
   unsigned short  Status;              // Status de la combinaison Mozart dans le booster
   int             CptRenduSousCmd;     // Compte rendu de la sous command
} MODE_LOCK_MOZART_BY_HANDS_T;

typedef struct
{
    BUF_ENTETE_T              	EnteteTrame;
    unsigned char             	Cmd;
    MODE_LOCK_MOZART_BY_HANDS_T  ModeLockMozartByHands;
}
ENCODE_BUF_MODE_LOCK_MOZART_BY_HANDS_T;

/*
============================================
	DESCRIPTION DES TRAMES SYSTEM
============================================
*/

#define NB_MAX_SYSTEME_CMD_RUF           2			/*!< Maximum number of ruf command */


#define SYSTEME_SIGNAL_RESET             0x01		/*!< To report a system reset */
#define SYSTEME_CMD_RESET                0x02		/*!< Command to do a reset */
#define SYSTEME_CMD_DIAG                 0x03		/*!< Command to get diagnostic */
#define SYSTEME_CMD_DUMP                 0x04		/*!< Command to do a memory dump */
#define SYSTEME_CMD_RESET_HARD           0x05		/*!< Command to do a hard reset */
#define SYSTEME_CMD_RUF_1                0x06		/*!< Command to do a ruf1 action (use for*/
#define SYSTEME_CMD_RUF_2                0x07		/*!< Command to do a ruf2 action */
#define SYSTEME_CMD_INCONNUE             0x08		/*!< Unknown system command */
#define SYSTEME_CMD_DIAGPLUS_1           0x09		/*!< Command to get diagnostic plus1 */
#define SYSTEME_CMD_DIAGPLUS_2           0x0A		/*!< Command to get diagnostic plus2 */
#define SYSTEME_CMD_BREAK                0x0B		/*!< Command to do a break  */
#define SYSTEME_CMD_WAKEUP               0x0C		/*!< Command to do a wakeup */
#define SYSTEME_CMD_RESET_HARD_NEW       0x0D		/*!< Command to do a new hard reset */
#define SYSTEME_CMD_SYS_SECURITY_FILE    0x0E		/*!< Unimplemented command */

#define SYSTEME_CMD_MODE_LOCK_NUMKEY_ZKA      0xA0  /*!< System command to lock all numerical keys */
#define SYSTEME_CMD_MODE_LOCK_PIN_ENTRY       0xA1  /*!< System command to lock Pin Entry to a dedicated VarId  */
   #define MLPE_CMD_READ                     (0xA5) /*!< System command to Read Pin Entry dedicated VarId       */
   #define MLPE_CMD_WRITE                    (0x5A) /*!< System command to Write Pin Entry to a dedicated VarId */
#define SYSTEME_CMD_MODE_LOCK_MOZART_BY_HANDS 0xA2  /*!< System command to Lock or Unlock the Mozart by Hands    */
   #define MLMBH_CMD_GET_STATUS              (0x5A) /*!< System command to Get   the "Mozart by Hand" Status    */
   #define MLMBH_CMD_SET_LOCK                (0xAA) /*!< System command to Set   the "Mozart by Hand" Lock      */
   #define MLMBH_CMD_CLEAR_LOCK              (0xA5) /*!< System command to Clear the "Mozart by Hand" Lock      */
#define SYSTEM_CMD_DISABLE_POINT_JAUNE        0xA3  /*!< System command to disable the yellow dot comb -NOT TO BE USED- (specific configuration) */
#define SYSTEME_CMD_QUOTA_CLESS         0x41        /*!< System command to change Cless behwviour, used to stop field after each polling loop */

// la Cmd Maintenance pour les ML30&SMART2 ne sont differentes qu'au niveau du thunder. Elles sont "traduites" avant emission BL2 des ML30&SMART2
#define SYSTEME_CMD_MAINTENANCE          0x0F		/*!< Maintenance system command */

		#define SYSTEME_SOUS_CMD_MAINTENANCE_DOWNLOAD            0x00000000		/*!< Command to go in download mode */
		#define SYSTEME_SOUS_CMD_MAINTENANCE_COMPONENT_NUMBER    0x00000001		/*!< Command to get a component by its number  */
		#define SYSTEME_SOUS_CMD_MAINTENANCE_COMPONENT_SHTYP     0x00000002		/*!< Command to get a component by its kind */

		// Sub-command (not used on BL2 ML30 & SMART2)
		#define SYSTEME_SOUS_CMD_MAINTENANCE_MANUFACTORING       0x00000003		/*!< Manufactoring maintenance command */

				#define SYSTEME_SCM_MANUFACTORING_MOZART_PROD              0x00000001		/*!< Command to do a Mozard for manufacturing */
				#define SYSTEME_SCM_MANUFACTORING_FLASH_ERASE_PROD         0x00000002		/*!< Command to do a flash erase for manufacturing (all flash without hterminal file) */
				#define SYSTEME_SCM_MANUFACTORING_SECURITY_MATCHES_PROD    0x00000003		/*!< Command to get the security file state (ko or security matches or security doesn't match) */
				#define SYSTEME_SCM_MANUFACTORING_DOWNLOAD_PROD            0x00000004		/*!< Command to go in manufacturing download */
				#define SYSTEME_SCM_MANUFACTORING_FLASH_LOCK               0x00000005		/*!< Command to lock the flash */
				#define SYSTEME_SCM_MANUFACTORING_FLASH_UNLOCK             0x00000006		/*!< Command to unlock the flash */

#define SYSTEME_CMD_DIAG_2               0x10		/*!< Command to get diagnostic 2 */
#define SYSTEME_CMD_INFO	             0x11		/*!< Command to get system informations */

// les commandes pour le PPR ne sont differentes qu'au niveau du thunder. Elles sont "traduites" avant emission au PPR
#define SYSTEME_CMD_RESET_PPR            0x12		/*!< Command to reset a PPR */
#define SYSTEME_CMD_DIAG_PPR             0x13		/*!< Command to get diagnostic from PPR */
#define SYSTEME_CMD_DUMP_PPR             0x14		/*!< Command to do a memory dump from PPR */
#define SYSTEME_CMD_RESET_HARD_PPR       0x15		/*!< Command to do a hard reset on PPR */
#define SYSTEME_CMD_USB_SENA_DECON_PPR   0x16   	/*!< Desactivate USB Pull-up and reset PPR */
#define SYSTEME_CMD_USB_SENA_CON_PPR     0x17		/*!< Unimplemented command */
#define SYSTEME_CMD_MAINTENANCE_P30      0x18		/*!< P30 maintenance system command */
#define SYSTEME_CMD_INFO_P30             0x19   	/*!< P30 info system command */

#define SYSTEME_CMD_DIAG_2_PPR           0x20		/*!< Command to get diagnostic 2 from PPR */

// les commandes pour le C30 ne sont differentes qu'au niveau du thunder. Elles sont "traduites" avant emission au C30
#define SYSTEME_CMD_RESET_C30            0x22		/*!< Command to reset a C30 */
#define SYSTEME_CMD_DIAG_C30             0x23		/*!< Command to get diagnostic from C30 */
#define SYSTEME_CMD_DUMP_C30             0x24		/*!< Command to do a memory dump from C30 */
#define SYSTEME_CMD_RESET_HARD_C30       0x25		/*!< Command to do a hard reset on C30 */
#define SYSTEME_CMD_USB_SENA_DECON_C30   0x26   	/*!< Unimplemented command */
#define SYSTEME_CMD_USB_SENA_CON_C30     0x27   	/*!< Unimplemented command */
#define SYSTEME_CMD_MAINTENANCE_C30      0x28   	/*!< C30 maintenance system command */
#define SYSTEME_CMD_INFO_C30             0x29   	/*!< C30 info system command */


// les commandes pour le CAD30USR ne sont differentes qu'au niveau du thunder. Elles sont "traduites" avant emission au CAD30USR
#define SYSTEME_CMD_RESET_CAD30USR            0x32		/*!< Command to reset a CAD30USR */
#define SYSTEME_CMD_DIAG_CAD30USR             0x33		/*!< Command to get diagnostic from CAD30USR */
#define SYSTEME_CMD_DUMP_CAD30USR             0x34		/*!< Command to do a memory dump from CAD30USR */
#define SYSTEME_CMD_RESET_HARD_CAD30USR       0x35		/*!< Command to do a hard reset on CAD30USR */
#define SYSTEME_CMD_USB_SENA_DECON_CAD30USR   0x36    	/*!< Unimplemented command */
#define SYSTEME_CMD_USB_SENA_CON_CAD30USR     0x37    	/*!< Unimplemented command */
#define SYSTEME_CMD_MAINTENANCE_CAD30USR      0x38    	/*!< CAD30USR maintenance system command */
#define SYSTEME_CMD_INFO_CAD30USR             0x39   	/*!< CAD30USR info system command */

#define SYSTEME_CMD_DIAG_2_CAD30USR           0x40		/*!< Command to get diagnostic 2 from CAD30USR */


// commandes X930. Elles sont "traduites" avant emission
#define SYSTEME_CMD_LOW_POWER            0x80		/*!< Command to go in low power mode */

#define SYSTEME_CMD_CLOCK_MODEM          0x81		/*!< Command to configure the modem clock */

#define SYSTEME_SOUS_CMD_START_CLOCK_MODEM            0x00000001		/*!< Command to switch on the modem clock */
#define SYSTEME_SOUS_CMD_STOP_CLOCK_MODEM             0x00000002		/*!< Command to switch off the modem clock */

#define SYSTEME_CMD_INFO_IDENT           0x82  /*!< Command to get booster unique identification */
#define SYSTEME_CMD_GET_CLEAR_FLAG_DISPLAY_BOOSTER  0x84


#define TAILLE_TRAME_SYS_DIAG              sizeof(BUF_SYS_DIAG_T)				/*!< Size of the system diagnostic frame */
#define TAILLE_TRAME_SYS_CMD               sizeof(BUF_SYS_CMD_T )				/*!< Size of the system command frame */
#define TAILLE_ZONE_SPY_ET_DIAG_TRAME_SYS  (sizeof(spy_data_t) + TAILLE_DIAGNOSTIC_SYSTEME) 		/*!< Size of the spy and diagnostic buffer */


// Informations concernant le protocole SYSTEME
#define TIMEOUT_REPONSE_SYSTEME            75		/*!< Awaited time for Booster answer before timeout (in Nucleus ticks)  */


// CODE DE RETOUR DANS LA TRAME DE REPONSE
#define     BASE_CODE_ERREUR_SYSTEME      0									/*!< System root report code */
#define     OK_SYSTEME                    (BASE_CODE_ERREUR_SYSTEME  )		/*!< Return if the system command was successful */
#define     KO_SYSTEME                    (BASE_CODE_ERREUR_SYSTEME-1)		/*!< Return if the system command is KO */
#define     KO_SYSTEME_PROBLEME_EMISSION  (BASE_CODE_ERREUR_SYSTEME-3)		/*!< Return if the system command is KO due to a transmit error */
#define     KO_SYSTEME_PAS_DE_REPONSE     (BASE_CODE_ERREUR_SYSTEME-4)		/*!< Return if the system command ended on timeout */




// Informations concernant la Table d'abonnement aux fonctions periodiques
#define	NB_MAX_FONCTIONS_PERIODIQUES         		9		/*!< Maximum number of periodical functions */

#define FONCTION_PERIODIQUE_VISUPPR         		0		/*!< Periodical function number of PPR display */
#define FONCTION_PERIODIQUE_VISU             		1		/*!< Periodical function number of display */
#define FONCTION_PERIODIQUE_CLAVIER 				2		/*!< Periodical function number of keyboard */
#define FONCTION_PERIODIQUE_CLAVIERPPR 				3		/*!< Periodical function number of PPR keyboard */
#define FONCTION_PERIODIQUE_TST_USB        			4		/*!< Periodical function number of USB test */
#define FONCTION_PERIODIQUE_VISUC30          		5		/*!< Periodical function number of C30 display */
#define FONCTION_PERIODIQUE_DRV_TWIN           		6		/*!< Periodical function number of Twin driver */
#define FONCTION_PERIODIQUE_LEDS               		7		/*!< Periodical function number of leds */
#define FONCTION_PERIODIQUE_LEDS2             		8		/*!< Periodical function number of leds 2 */
#define FONCTION_PERIODIQUE_9                		9		/*!< ruf */


/*
======================================================================
			            DRIVER RETRO ECLAIRAGE
======================================================================
*/

// Informations concernant la trame de commande RETRO ECLAIRAGE
#define TAILLE_BUF_RETRO_ECLAIRAGE             10		/*!< Size of the backlight buffer */


/*
============================================
	   STRUCTURE DE DONNEES DES TRAMES
============================================
*/

/*! @brief Backlight command */
typedef struct
{
    unsigned char      Cmd;				/*!< Command */
    unsigned char      Diviseur;		/*!< Divisor */
    unsigned short     Duree_high;		/*!< High period */
    unsigned short     Duree_totale;	/*!< Complete period */
}
DATA_RETRO_ECLAIRAGE_T;


/*! @brief trame Retro Eclairage (entete+data) */
typedef struct
{
    BUF_ENTETE_T             EnteteTrame;		/*!< Frame header */
    DATA_RETRO_ECLAIRAGE_T   DataRetroEcl;		/*!< Data */
}
ENCODE_BUF_RETRO_ECLAIRAGE_T;


/*! @brief Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char                 DataBrute[TAILLE_BUF_RETRO_ECLAIRAGE];		/*!< Raw data */
    ENCODE_BUF_RETRO_ECLAIRAGE_T  DataDecode;			/*!< Decoded data */
}
BUF_RETRO_ECLAIRAGE_T;


/*! @brief Backlight header to set several pwm */
typedef struct
{
    unsigned char    Cmd;        /*!< Command */
    unsigned char    NbPwm;      /*!< Number of pwm to set */
    unsigned char    ruf[2];     /*!< ruf */
}
HEADER_RETRO_ECLAIRAGE_T;


/*! @brief Backlight header frame to set several pwm */
typedef struct
{
    BUF_ENTETE_T               EnteteTrame;  /*!< Frame header */
    HEADER_RETRO_ECLAIRAGE_T   InfoRetroEcl; /*!< Backlight header */
}
BUF_RETRO_ECLAIRAGE_HEADER_T;


// DESCRIPTION DES TRAMES
#define RETRO_ECLAIRAGE_CMD_STOP           0x01		/*!< Command to switch off standard backlight */
#define RETRO_ECLAIRAGE_CMD_START          0x02		/*!< Command to switch on standard backlight */
#define RETRO_ECLAIRAGE_AFF_CMD_STOP       0x03		/*!< Command to switch off separated display backlight */
#define RETRO_ECLAIRAGE_AFF_CMD_START      0x04		/*!< Command to switch on separated display backlight */
#define RETRO_ECLAIRAGE_CMD_SET_PWM        0x05		/*!< Command to set the value of one or several pwms */



/*
======================================================================
			            DRIVER BUZZER
======================================================================
*/

// Informations concernant la trame de commande BUZZER
#define TAILLE_BUF_BUZZER             12		/*!< Size of the buzzer buffer */


/*
======================================================================
			           STRUCTURE DE DONNEES DES TRAMES
======================================================================
*/


/*! @brief BUZZER command */
typedef struct
{
    unsigned char      Cmd;					/*!< Command */
    unsigned char      Diviseur;			/*!< Divisor */
    unsigned short     Duree_high;			/*!< High period */
    unsigned short     Duree_totale;		/*!< Complete period */
    unsigned short     Duree_beep;			/*!< Beep duration (10ms) */
}
DATA_BUZZER_T;


/*! @brief trame BUZZER (entete+data) */
typedef struct
{
    BUF_ENTETE_T       EnteteTrame;		/*!< Frame header */
    DATA_BUZZER_T      DataBuzzer;		/*!< Data */
}
ENCODE_BUF_BUZZER_T;


/*! @brief Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char          DataBrute[TAILLE_BUF_BUZZER];		/*!< Raw data */
    ENCODE_BUF_BUZZER_T    DataDecode;		/*!< Decoded data */
}
BUF_BUZZER_T;

// DESCRIPTION DES TRAMES
#define BUZZER_CMD_STOP             0x01		/*!< Command to switch off the buzzer */
#define BUZZER_CMD_START            0x02		/*!< Command to switch on the buzzer */
#define BUZZER_CMD_CONFIG_PIN_BEEP	0x03		/*!< Command to configure beep on pin entry */



/*
======================================================================
			            DRIVER LEDS
======================================================================
*/


// Informations concernant la trame de commande LED pour le C30
#define TAILLE_BUF_LEDS             13		/*!< Size of the leds buffer */


/*
======================================================================
			           STRUCTURE DE DONNEES DES TRAMES
======================================================================
*/

/*! @brief LEDs command */
typedef struct
{
    unsigned char      Cmd;					/*!< Command */
    unsigned char      NumLed;				/*!< Mask of leds */
    unsigned char      TimeOn;				/*!< On period */
    unsigned char      TimeOff;				/*!< Off period */
    unsigned char      Diviseur;			/*!< Divisor */
    unsigned short     Duree_high;			/*!< High period */
    unsigned short     Duree_totale;		/*!< Complete period */
}
DATA_LEDS_T;


/*! @brief  Trame Leds (entete+data) */
typedef struct
{
    BUF_ENTETE_T       EnteteTrame;		/*!< Frame header */
    DATA_LEDS_T        DataLeds;		/*!< Data */
}
ENCODE_BUF_LEDS_T;


/*! @brief  Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char      DataBrute[TAILLE_BUF_LEDS];		/*!< Raw data */
    ENCODE_BUF_LEDS_T  DataDecode;			/*!< Decoded data */
}
BUF_LEDS_T;


// DESCRIPTION DES TRAMES
#define LEDS_CMD_STOP           0x01		/*!< Command to switch off the led */
#define LEDS_CMD_START          0x02		/*!< Command to switch on the led */
#define LEDS_CMD_BLINK          0x03		/*!< Command to put the led in blinking mode */




/*
======================================================================
			            DRIVER IAPP
======================================================================
*/


// Informations concernant les objets noyaux du driver iapp
#define	HISR_IAPP_PRIORITY                1    				/*!< Priority of the IAPP Hisr */
#define EVENT_IAPP                        0x00000001		/*!< Iapp event */


// Informations concernant la trame de commande IAPP
#define TAILLE_DATA_IAPP         (128)				/*!< Size of the Iapp data */
#define TAILLE_BUF_IAPP          (sizeof(BUF_ENTETE_T) + TAILLE_DATA_IAPP)		/*!< Size of the Iapp buffer */


/*
======================================================================
			     STRUCTURE DE DONNEES DES TRAMES
======================================================================
*/

/*! @brief  IAPP command */
typedef struct
{
    unsigned char      Data[TAILLE_DATA_IAPP];		/*!< Data */
}
DATA_IAPP_T;


/*! @brief  trame Retro Eclairage (entete+data) */
typedef struct
{
    BUF_ENTETE_T       EnteteTrame;		/*!< Frame header */
    DATA_IAPP_T        DataIapp;		/*!< Data */
}
ENCODE_BUF_IAPP_T;


/*! @brief  Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char      DataBrute[TAILLE_BUF_IAPP];		/*!< Raw data */
    ENCODE_BUF_IAPP_T  DataDecode;		/*!< Decoded data */
}
BUF_IAPP_T;


/*
======================================================================
			     DRIVER SWIPE
======================================================================
*/

#define TAILLE_BITS_ISO			 		 (704)										/*!< maximum bit count on a 210bpi & 86mm long track */
#define TAILLE_DATA_SWIPE        ((TAILLE_BITS_ISO+7) / 8)							/*!< buffer byte size to fit TAILLE_BITS_ISO bits */
#define TAILLE_BUF_SWIPE         (sizeof(ENCODE_BUF_SWIPE_T))						/*!< total ISO buffer size */
#define TAILLE_BUF_DATA_SWIPE    (sizeof(ENCODE_BUF_SWIPE_T)-sizeof(BUF_ENTETE_T))	/*!< ISO buffer size without preamble */
#define TAILLE_CMD_SWIPE         (sizeof(ENCODE_CMD_SWIPE)-sizeof(BUF_ENTETE_T))	/*!< CMD buffer size without preamble */
#define TAILLE_CMD_PARAM_GET     (sizeof(ENCODE_CMD_SWIPE_T)-sizeof(BUF_ENTETE_T))	/*!< WPAR buffer size without preamble */
#define TAILLE_CMD_PARAM_SET     (sizeof(ENCODE_CMD_SWIPE_R)-sizeof(BUF_ENTETE_T))	/*!< WPAR buffer size without preamble */
#define TAILLE_CMD_SET_MIN_NOISE_LEVEL     (sizeof(ENCODE_CMD_SWIPE_R)-sizeof(BUF_ENTETE_T))	/*!< WNOISE buffer size without preamble */
#define TAILLE_CMD_DEL_MIN_NOISE_LEVEL     (sizeof(ENCODE_CMD_SWIPE_R)-sizeof(BUF_ENTETE_T))	/*!< WNOISE buffer size without preamble */

#define SWIPE_CMD_DATA				0		/*!< Cmd field value :ISO incoming data (BL3 analog channels) */
#define SWIPE_CMD_OPEN				1		/*!< Cmd field value :open request (BL3 only)*/
#define SWIPE_CMD_CLOSE				2		/*!< Cmd field value :close request (BL3 only)*/
#define SWIPE_CMD_VERSION			3		/*!< Cmd field value :get driver internal release (BL3 only)*/
#define SWIPE_CMD_ANA_BFR		  	4		/*!< Cmd field value :ANALOG incoming data (BL3 analog channels) */
#define SWIPE_CMD_PARAM_GET			5		/*!< Cmd field value :get internal parameters (BL3 analog channels) */
#define SWIPE_CMD_PARAM_SET			6		/*!< Cmd field value :set internal parameters (BL3 analog channels)*/
#define SWIPE_CMD_PIC_GET			7		/*!< Cmd field value :PIC incoming data (BL3 analog channels) */
#define SWIPE_CMD_DATA_MAGTEK		8		/*!< Cmd field value :ISO incoming data (origin=optionnal BL3 Magtek IC) */
#define SWIPE_CMD_SET_MIN_NOISE_LEVEL 9		/*!< Cmd field value :set ISO min noise treshold value */
#define SWIPE_CMD_DEL_MIN_NOISE_LEVEL  10	/*!< Cmd field value :del ISO min noise treshold value, back to default (no param) */

/*
======================================================================
			     STRUCTURE DE DONNEES DES TRAMES
======================================================================
*/

// trame swipe (entete+data)
#include "oem_iso.h"


/*! @brief  "request for NEXT PICs buffer" (BL3 analog channels) sub-sub data structure */
typedef struct
{
	int track_number;					/*!< track concerned  {0=ISO1,1=ISO2,2=ISO3} */
	int bpic_requiered_index;			/*!< start reading PICs data at this index value */
} t_bpic;

typedef struct
{
	unsigned short min_noise_level; 	/*!< noise treshold value unit=1/1024 of total ADC range*/
} t_noise;

/*! @brief  ISO incoming data (BL3 analog channels) data structure */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;						/*!< common preamble */
    int				 Cmd;								/*!< must be set to SWIPE_CMD_DATA */
    unsigned char    Data_iso1[TAILLE_DATA_SWIPE];		/*!< ISO1 incoming data */
    unsigned char    Data_iso2[TAILLE_DATA_SWIPE];		/*!< ISO2 incoming data */
    unsigned char    Data_iso3[TAILLE_DATA_SWIPE];		/*!< ISO3 incoming data */
}
ENCODE_BUF_SWIPE_T;


/*! @brief SEND COMMAND (BL3 analog channels) data structure */
typedef struct
{
    BUF_ENTETE_T   			EnteteTrame;	/*!< common preamble */
    int				 		Cmd;			/*!< must be set to SWIPE_CMD_PARAM_GET */
    int						Ruf[3];			/*!< reserved for future, max size for historical BL3 OS !! do not increase*/
}
ENCODE_CMD_SWIPE;


/*! @brief READ PARAMETERS (BL3 analog channels) sub data structure */
typedef union
{
    int			 	 Value;			/*!< filler */
	t_parametre_ro	 parametre;		/*!< parameters incluling read-only extension*/
}
ENCODE_CMD_SWIPE_T_EXT;


/*! @brief READ PARAMETERS (BL3 analog channels) data structure */
typedef struct
{
    BUF_ENTETE_T   			EnteteTrame;	/*!< common preamble */
    int				 		Cmd;			/*!< must be set to SWIPE_CMD_PARAM_GET */
    ENCODE_CMD_SWIPE_T_EXT 	ext;			/*!< sub data structure */
}
ENCODE_CMD_SWIPE_T;

/*! @brief "SET PARAMETERS" or "request for NEXT PICs buffer" sub data structure */
typedef union
{
    t_bpic		 bpic;			/*!< PICs reading request (if Cmd==SWIPE_CMD_PIC_GET) */
	t_parametre	 parametre;		/*!< new PARAMETERs setting (if Cmd==SWIPE_CMD_PARAM_SET) */
    t_noise		 noise;			/*!< noise threshold value setting (if Cmd==TAILLE_CMD_SET_MIN_NOISE_LEVEL) */
}
ENCODE_CMD_SWIPE_R_EXT;


/*! @brief "SET PARAMETERS" or "request for NEXT PICs buffer" CMD REQUEST  */
typedef struct
{
    BUF_ENTETE_T     		EnteteTrame;/*!< common preamble */
    int				 		Cmd;		/*!< must be set to SWIPE_CMD_PARAM_SET or SWIPE_CMD_PIC_GET */
	ENCODE_CMD_SWIPE_R_EXT	ext;
}
ENCODE_CMD_SWIPE_R;

#define TAILLE_ANA_SWP (TAILLE_BUF_INTER_UC-sizeof(BUF_ENTETE_T)-3*sizeof(int))		/*!< size for ANALOG buffer */


/*! @brief READ ANALOG SAMPLES (BL3 analog channels) data structure */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;					/*!< common preamble */
    int				 Cmd;							/*!< must be set to SWIPE_CMD_ANA_BFR */
    char             track[MAX_CHANNEL_COUNT+1];	/*!< true if track concerned (track[0]=ISO1, track[1]=ISO2, track[2]=ISO3 up to 3 tracks */
    int				 b_siz;							/*!< available valid elements in following b[] incomming data */
    unsigned char    b[TAILLE_ANA_SWP];				/*!< ANALOG SAMPLES read buffer */
}ANALOG_BUF_SWIPE_T;

#define TAILLE_PIC_SWP ((TAILLE_BUF_INTER_UC-sizeof(BUF_ENTETE_T)-3*sizeof(int))/2)

/*! @brief READ PICs (BL3 analog channels) data structure */
typedef struct
{
    BUF_ENTETE_T     EnteteTrame;		/*!< common preamble */
    int				 Cmd;				/*!< must be set to SWIPE_CMD_PIC_GET */
    int              track_number;		/*!< must be < MAX_CHANNEL_COUNT :(track[0]=ISO1, track[1]=ISO2, track[2]=ISO3 up to 3 tracks */
    int				 b_count;			/*!< available valid elements in following b[]  incomming data */
    unsigned short   b[TAILLE_PIC_SWP];	/*!< PICs read buffer */
}PICS_BUF_SWIPE_T;



/*! @brief BL3 to Thunder buffer union data structure*/
typedef union
{
    unsigned char      DataBrute[TAILLE_BUF_SWIPE];		/*!< char buffer form */
    ENCODE_BUF_SWIPE_T DataDecode;	/*!< ISO incoming data form */
    ENCODE_CMD_SWIPE_T CmdDecode;	/*!< PARAMETERs incoming data form  */
    ANALOG_BUF_SWIPE_T Ana;			/*!< ANALOG incoming data form */
    PICS_BUF_SWIPE_T   Pic;			/*!< PICs incoming data form */
	BUF_INTER_UC_T     BufInterUc;	/*!< Generic inter-uc data form */
}
BUF_SWIPE_T;


/*
======================================================================
			     DRIVER CLESS
======================================================================
*/


// Informations concernant la trame de commande CLESS pour le C30
#define TAILLE_BUF_CLESS_DATA        (400)			/*!< max size of contact less data on inter UC */
#define TAILLE_BUF_CLESS             (  4       + 4   + TAILLE_BUF_CLESS_DATA)		/*!< max size of contact less packet (interuc header + cless command + data) on inter UC */
                                   //  Entete   + Cmd +       Data



/*
======================================================================
			     STRUCTURE DE DONNEES DES TRAMES
======================================================================
*/



/*! @brief  CLESS command */
typedef struct
{
    unsigned short     Cmd;			/*!< contact less command */
    unsigned char      Data[TAILLE_BUF_CLESS_DATA];		/*!< parameters of contact less command  */
}
DATA_CLESS_T;


/*! @brief  trame Cless (entete+data)*/
typedef struct
{
    BUF_ENTETE_T       EnteteTrame;			/*!< inter UC header */
    DATA_CLESS_T       DataCless;				/*!< inter uc contact less packet */
}
ENCODE_BUF_CLESS_T;


/*! @brief  Union {(Trame brute) ou (Entete + Data)}*/
typedef union
{
    unsigned char       DataBrute[TAILLE_BUF_CLESS];			/*!< Raw packet received from interuc */
    ENCODE_BUF_CLESS_T  DataDecode;				/*!< packet received from interuc (inter UC header + interuc data) */
}
BUF_CLESS_T;


/*
======================================================================
			     DESCRIPTION DES TRAMES
======================================================================
*/

//CLESS ISO inter uc commands
#define CLESS_CMD_DETECTCARDS    0x01		/*!< detect an ISO card using 1.1 driver interface */
#define CLESS_CMD_ACTIVECARD     0x02		/*!< activate an ISO card using 1.1 driver interface */
#define CLESS_CMD_DESELECTCARD   0x03		/*!< deselect an ISO card using 1.1 driver interface */
#define CLESS_CMD_APDU           0x04		/*!< DEPRECATED : send an APDU to ISO card using 1.1 driver interface ( limited to 255 bytes ) */
#define CLESS_CMD_XX_FORMAT      0x05		/*!< custom ISO driver command using 1.1 driver interface */
#define CLESS_CMD_OPEN           0x06		/*!< open ISO driver using 1.1 driver interface */
#define CLESS_CMD_CLOSE          0x07		/*!< close ISO driver using 1.1 driver interface */
#define CLESS_CMD_APDU_L         0x08		/*!< send an APDU to ISO card using 1.1 driver interface */
#define CLESS_CMD_MULTIDETECTCARDS 0x09     /*!< detect and activate an ISO card using 2.0 driver interface, this function can detect proprietary cards */

//CLESS MF1 inter uc commands
#define CLESS_CMD_MF1DETECTCARDS 0x11		/*!< detect Mifare classic cards */
#define CLESS_CMD_MF1ACTIVECARD  0x12		/*!< activate a detected card */
#define CLESS_CMD_MF1AUTHENT     0x13		/*!< perform MF classic authentication */
#define CLESS_CMD_MF1READBLOCK   0x14		/*!< read a memory block */
#define CLESS_CMD_MF1WRITEBLOCK  0x15		/*!< write a memory block */
#define CLESS_CMD_MF1VALUEOP     0x16		/*!< perform a value operation on a Mifare classic card */
#define CLESS_CMD_MF1XX_FORMAT   0x17		/*!< custom Mifare command */
#define CLESS_CMD_MF1OPEN        0x18		/*!< open Mifare driver */
#define CLESS_CMD_MF1CLOSE       0x19		/*!< close Mifare driver */
#define CLESS_CMD_MF1DETECTCARDS_EX 0x1A		/*!< detect Mifare cards (classic, ultralight) */
#define CLESS_CMD_MF1REMOVAL     0x1B

//CLESS STM inter uc commands
#define CLESS_CMD_STMDETECT      0x21		/*!< detect and activate a STM tag */
#define CLESS_CMD_STMDEACTIVATE  0x22		/*!< deselect tag */
#define CLESS_CMD_STMREADBLOCK   0x23		/*!< read a memory block */
#define CLESS_CMD_STMWRITEBLOCK  0x24		/*!< write a memory block */
#define CLESS_CMD_STMPROTECT     0x25		/*!< perform a protect command on a SR176 card */
#define CLESS_CMD_STMGETPROTEC   0x26		/*!< retrieve protect status on a SR176 card */
#define CLESS_CMD_STMXX_FORMAT   0x27		/*!< custom STM command */
#define CLESS_CMD_STMOPEN        0x28		/*!< open STM driver */
#define CLESS_CMD_STMCLOSE       0x29		/*!< close STM driver */
#define CLESS_CMD_STMGETUID      0x2A		/*!< retrieve card UID */
#define CLESS_CMD_STMREMOVAL     0x2B


//CLESS ISO EMV2.0 inter uc commands
#define CLESS_CMD_EMVDETECT      0x31		/*!< detect and activate an ISO card using 2.0 driver interface */
#define CLESS_CMD_EMVREMOVAL     0x32		/*!< deselect an ISO card using 2.0 driver interface */
#define CLESS_CMD_EMVAPDU        0x33		/*!< send an APDU to ISO card using 2.0 driver interface */
#define CLESS_CMD_EMVXX_FORMAT   0x34		/*!< custom ISO driver command using 2.0 driver interface */
#define CLESS_CMD_EMVOPEN        0x35		/*!< open ISO driver command using 2.0 driver interface */
#define CLESS_CMD_EMVCLOSE       0x36		/*!< close ISO driver using 2.0 driver interface */
#define CLESS_CMD_EMVMULTIDETECT   0x37     /*!< detect and activate an ISO card using 2.0 driver interface, this function can detect proprietary cards */

//Cless Generic inter uc commands
#define CLESS_CMD_GET_VERSION    0x40		/*!< get version of cless ISO driver */
#define CLMF1_CMD_GET_VERSION    0x41       /*!< get version of Mifare driver */
#define CLBP_CMD_GET_VERSION     0x42		/*!< get version of B' driver */
#define CLSTM_CMD_GET_VERSION    0x43       /*!< get version of STM driver */

//CLESS BP
#define CLESS_CMD_BPDETECT       0x51
#define CLESS_CMD_BPDISCONNECT   0x52
#define CLESS_CMD_BPAPDU         0x53
#define CLESS_CMD_BPATR          0x54
#define CLESS_CMD_BPOPEN         0x55
#define CLESS_CMD_BPCLOSE        0x56
#define CLESS_CMD_BPXX_FORMAT    0x57

/*
======================================================================
			            DRIVER INTER UC ADMIN
======================================================================
*/


// Informations concernant la trame de commande Admin Inter UC
#define TAILLE_BUF_ADMIN_IUC			(512+sizeof(BUF_ENTETE_T)+(2*sizeof(int)))

/*
======================================================================
			           STRUCTURE DE DONNEES DES TRAMES
======================================================================
*/

/*! @brief  Trame Admin Set Mode (entete+data) */
typedef struct
{
    BUF_ENTETE_T       	EnteteTrame;		/*!< Frame header */
   	int				 	Cmd;				/*!<  Cmd or return */
   	unsigned 			Data[TAILLE_BUF_ADMIN_IUC-sizeof(BUF_ENTETE_T)-sizeof(int)];
}
ENCODE_BUF_ADMIN_IUC_HEADER_T;



/*! @brief  Trame Admin Set Mode (entete+data) */
typedef struct
{
    BUF_ENTETE_T       	EnteteTrame;		/*!< Frame header */
   	int				 	Cmd;				/*!< must be set to ADMIN_IUC_CMD_MODE_SET */
    int				    Mode;				/*!< Data */
}
ENCODE_BUF_ADMIN_IUC_SETMODE_T;


// Mode (ENCODE_BUF_ADMIN_IUC_SETMODE_T)
#define ADMIN_IUC_MODE_NONE			   	0x00		/*!< unused, default mode */
#define ADMIN_IUC_MODE_ACTIVE       	0x01		/*!< The terminal uses the peripheral */
#define ADMIN_IUC_MODE_IDLE       	   	0x02		/*!< The terminal doesn't use the peripheral*/
#define ADMIN_IUC_MODE_MAINTENANCE      0x03		/*!< The peripheral has to go to the maintenance mode*/
#define ADMIN_IUC_MODE_LLT			    0x04		/*!< The peripheral has to go to the LLT mode*/

#define ADMIN_IUC_MODE_INTELLIGENT      0x101		/*!< The peripheral has to go to the intelligent mode*/


/*! @brief  Trame Admin Get Info (entete+data) */
typedef struct
{
    BUF_ENTETE_T       	EnteteTrame;		/*!< Frame header */
   	int				 	Cmd;				/*!< must be set to ADMIN_IUC_CMD_INFO */
    unsigned char    	Data[512];
}
ENCODE_BUF_ADMIN_IUC_GETINFO_T;


/*! @brief  Union {(Trame brute) ou (Entete + Data)} */
typedef union
{
    unsigned char      				DataBrute[TAILLE_BUF_ADMIN_IUC];		/*!< Raw data */
    ENCODE_BUF_T	 				DataDecode;
    ENCODE_BUF_ADMIN_IUC_HEADER_T	Header;
	ENCODE_BUF_ADMIN_IUC_SETMODE_T  SetMode;								/*!< Decoded data */
    ENCODE_BUF_ADMIN_IUC_GETINFO_T  GetInfo;								/*!< Decoded data */
}BUF_ADMIN_IUC_T;


/*!  @brief cmd */
#define ADMIN_IUC_CMD_MODE_SET		1
#define ADMIN_IUC_CMD_INFO			2



/*
======================================================================
			     DRIVER SOCLE 930
======================================================================
*/

// Voir DSoc930.h


/*
======================================================================
			     DRIVER PERIPHERIQUES
======================================================================
*/

#define PRIORITY_IT_FIQ             (AIC_SRCTYPE_EXT_POSITIVE_EDGE | 0x00)		/*!< Priority of the FIQ */




/*
======================================================================
			     liaison SPI booster <-> Display
======================================================================
*/

#define DISPLAY_HISR               "DISPLAY_HISR"			/*!< Name of the display hisr */
#define SPI_DISPLAY_HISR_PRIORITY      1					/*!< Priority of the spi display hisr */

#define CONFIG_PORT_DISPLAY_64x64      0x03					/*!< Pio value for the 64x64 display */
#define CONFIG_PORT_DISPLAY_64x128     0x02					/*!< Pio value for the 64x128 display */
#define CONFIG_PORT_DISPLAY_RUF1       0x01					/*!< ruf display pio value */
#define CONFIG_PORT_DISPLAY_RUF2       0x00					/*!< ruf display pio value */



// SCHEMA MANAGMENT

#define SCHEMA_HISR_PRIORITY   HISR_SYSTEM_PRIORITY		/*!< Priority of the Scheme hisr */
// semaphores


//DRIVER COM 0

#define PRIORITY_IT_COM_0     (AIC_SRCTYPE_INT_LEVEL_SENSITIVE | 0x00)		/*!< Priority of the COM0 driver interrupt */


// DRIVER COM 1

#define PRIORITY_IT_COM_1     (AIC_SRCTYPE_INT_LEVEL_SENSITIVE | 0x00)		/*!< Priority of the COM1 driver interrupt */


// PIO 0

#define PRIORITY_IT_PIOA      (AIC_SRCTYPE_INT_LEVEL_SENSITIVE | 0x00)		/*!< Priority of the PIOA interrupt */


//  PIO 1

#define PRIORITY_IT_PIOB      (AIC_SRCTYPE_INT_LEVEL_SENSITIVE | 0x00)		/*!< Priority of the PIOB interrupt */


// DRIVER DISPLAY SPI

#define  PRIOTRITE_IT_SPI     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE  | 0x00)		/*!< Priority of the spi interrupt */


/*
======================================================================
                      DRIVER TOUCH SCREEN
======================================================================
*/

#define TSCREEN_CMD_OPEN               0x01  /*!< Open touch screen TH->BL*/
#define TSCREEN_CMD_CLOSE              0x02  /*!< Close touch screen TH->BL */
#define TSCREEN_CMD_GET_MODE           0x03  /*!< Get the mode beeing used TH<->BL*/
#define TSCREEN_CMD_SET_MODE           0x04  /*!< Set the new mode to use TH->BL */
#define TSCREEN_CMD_SAMPLE             0x05  /*!< Transmit sample BL->TH */
#define TSCREEN_CMD_RC                 0x06  /*!< Return code BL->TH */
#define TSCREEN_CMD_CALIB              0x07  /*!< Request autocalibration TH->BL */
#define TSCREEN_CMD_GET_MATRIXES       0x08  /*!< Request calibration matrixes for saving TH<->BL */
#define TSCREEN_CMD_SET_MATRIXES       0x09  /*!< Force the booster to use saved matrixes TH->BL */
#define TSCREEN_CMD_SET_PARAM          0x10  /*!< Force the booster to use new thresholds in pen mode TH->BL */
#define TSCREEN_CMD_GET_TSBVER         0x11  /*!< Get version of the Booster Touch Screen driver TH<->BL */
#define TSCREEN_CMD_GET_PANEL_TYPE     0x12  /*!< Get type of panel TH<->BL */
#define TSCREEN_CMD_SENSITIVITY_ADJUST 0x13  /*!< Adjust sensitivity: increase/decrease TH->BL */
#define TSCREEN_CMD_SET_TOUCH_WAKE_UP  0x14  /*!< Activate/Disactivate ability to wake up terminal by touch TH->BL*/
#define TSCREEN_CMD_CLESS_FIELD_ON     0x15  /*!< Signal to booster: contactless is going to switch ON the field */
#define TSCREEN_CMD_CLESS_FIELD_OFF    0x16  /*!< Signal to booster: contactless is going to switch OFF the field */
#define TSCREEN_CMD_EXT_SAMPLE         0x17  /*!< Activate/Disactivate extended sample format */
#define TSCREEN_CMD_TRANSACTION_BEGIN  0x18  /*!< Signal to booster: transaction begins, background comp should be disabled */
#define TSCREEN_CMD_TRANSACTION_END    0x19  /*!< Signal to booster: transaction ends, background comp should be enabled */
#define TSCREEN_CMD_APERTURE_OLD       0x20  /*!< Signal to booster: old value of aperture must be used for compatibility reason */
#define TSCREEN_CMD_SET_CFG_FILE       0x21  /*!< Set MXT224 Config File */
#define TSCREEN_CMD_GET_MXT_MATRIXES   0x22  /*!< Get MXT224 matrix */

#define TSCREEN_ONE_MATRIX_SZ       92 /*!< Number of bytes in Cirque Compensation matrix */
#define TSCREEN_COMP_MATRIXES_SZ    3*TSCREEN_ONE_MATRIX_SZ /*!< Number of bytes required by all matrixes */

#define TSCREEN_MXT_MATRIXES_SZ     448   /* 17x * 13y short values */

#define TSCREEN_MXT_CFG_FILE_SZ     400   /* Typical MXT224 config file size*/

/*! @brief Enumeration data type for different touch panels */
typedef enum
{
   TSCREEN_PANEL_RP02               = 0,               /*!< RP02, initial version of panel */
   TSCREEN_PANEL_RP02_EXT           = 1,               /*!< RP02, extended version of panel */
   TSCREEN_PANEL_RP01               = 2,               /*!< RP01, initial version of panel */
   TSCREEN_PANEL_RP01_WINTEK_SITO   = 2,               /*!< RP01, initial version of panel Wintek SITO */
   TSCREEN_PANEL_RP01_GIANT_DITO    = 3,               /*!< RP01, panel Giant DITO */
   TSCREEN_PANEL_RP01_WINTEK_DITO   = 4,               /*!< RP01, panel Wintek DITO */
   /*------------------------*/
   TSCREEN_PANEL_UNKNOWN  = 255              /*!< Unknown panel */
}
TSCREEN_PANEL_TYPE_T;

/*! @brief Data sent with OPEN command. Default mode */
typedef struct
{
   unsigned short mode;		/*!< mode in use source and capture mode */
   unsigned short speed;	/*!< Sampling speed */
}
TSCREEN_CMDDATA_OPEN_T;


typedef TSCREEN_CMDDATA_OPEN_T TSCREEN_CMDDATA_SETMODE_T; /*!< Same struct for GET_MODE and SET_MODE commands */

/*! @brief Pen mode configurable thresholds sent with SET_PARAM command */
typedef struct
{
   unsigned char penZoff;  /*!< Pen lift off threshold */
   unsigned char penZon;   /*!< Pen touchdown threshold */
   unsigned char smoothZoff;/*!< Pen smoothing lift off threshold */
   unsigned char smoothZon; /*!< Pen smoothing touchdown threshold */
}
TSCREEN_CMDDATA_SETPARAM_T;


/*! @brief  Sample format */
typedef struct
{
   unsigned short x_extended;		/*!< X coordinate + Source flag + Touch/release flag */
   unsigned short y;					/*!< Y coordinate */
}
TSCREEN_SAMPLE_T;


/*! @brief  Timed stamped sample format */
typedef struct
{
   unsigned short x_extended;	 /*!< X coordinate + Source flag + Touch/release flag */
   unsigned short y;			 /*!< Y coordinate */
   unsigned short z;             /*!< Z coordinate */
   unsigned int   t;             /*!< T time stamp */
}
TSCREEN_EXTSAMPLE_T;

/*! @brief  Data going from/to the booster*/
typedef union
{
   TSCREEN_CMDDATA_OPEN_T     open;			/*!< Open params */
   TSCREEN_SAMPLE_T           sample;		/*!< Sample sent by booster */
   TSCREEN_EXTSAMPLE_T        extsample;  /*!< Time stamped sample sent by booster */
   TSCREEN_CMDDATA_SETMODE_T  setmode;	   /*!< Mode to use by booster */
   unsigned char              rc;			/*!< Return code */
   TSCREEN_CMDDATA_SETPARAM_T param;      /*!< Param to use by booster */
   unsigned char              CompMatrixes[TSCREEN_COMP_MATRIXES_SZ];   /*!< Calibration matrixes from/to booster */
   unsigned int               version;    /*!< Version of the Booster Touch Screen driver */
   TSCREEN_PANEL_TYPE_T       panel;      /*!< Type of panel */
   signed char                sensitivity;/*!< Sensitivity adjustment */
   unsigned char              touchWkUpOnOff;/*!< Wake up by touch On/Off */
   unsigned char              extSampOnOff;/*!< Activate/Disactivate extended sample usage */
   unsigned char              mxtConfigFile[TSCREEN_MXT_CFG_FILE_SZ];  /*!< Config File buffer */
   unsigned char              mxtMatrixes[TSCREEN_MXT_MATRIXES_SZ]; /*!< Calibration matrixes from/to booster */
   unsigned char              mxtMatrixesType; /*!< Reference or Delta matrix */
} TSCREEN_UCEXCHDATA_T;


/*! @brief  Touch screen command buffer to be sent TH<->BL*/
typedef struct
{
   unsigned int         cmd;				/*!< Command */
   TSCREEN_UCEXCHDATA_T data;				/*!< Data */
} TSCREEN_UCEXCHPACK_T;


/*! @brief  Buffer received TH<->BL*/
typedef struct
{
   BUF_ENTETE_T         EnteteTrame;		/*!< InterUC format */
   TSCREEN_UCEXCHPACK_T package;				/*!< Touch screen command*/
} TSCREEN_UCEXCH_T;


/*
======================================================================
			     DRIVER SECURITE
======================================================================
*/

#define  PRIORITY_IT_IRQ1     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ1 */
#define  PRIORITY_IT_IRQ2     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ2 */
#define  PRIORITY_IT_IRQ3     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ3 */
#define  PRIORITY_IT_IRQ4     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ4 */
#define  PRIORITY_IT_IRQ5     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ5 */
#define  PRIORITY_IT_IRQ6     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ6 */
#define  PRIORITY_IT_IRQ7     ( AIC_SRCTYPE_EXT_POSITIVE_EDGE |  0x00)		/*!< Priority of the IRQ7 */


/*
======================================================================
			     AUTHENTIFICATION
======================================================================
*/

#define SECURITE_CMD_AUTHENTIFICATION     0x01			/*!< Booster secure command to start the Thunder authentification  */
#define SECURITE_RSP_AUTHENTIFICATION     SECURITE_CMD_AUTHENTIFICATION		/*!< Thunder authentification answer */
#define SECURITE_CMD_START_SECU_IUC       0x02			/*!< Booster secure command to start secure iuc  */
#define SECURITE_RSP_START_SECU_IUC       SECURITE_CMD_START_SECU_IUC  /*!< Thunder start secure iuc answer  */
#define SECURITE_GET_PINPAD_IUC_KEY       0x03			/*!< Booster secure command to get iuc key */


#define TAILLE_ALEA                       8			/*!< Size of the alea */


/*! @brief  Authentification data structure (use in authentification frame) */
typedef struct
{
    unsigned char      Cmd;							/*!< Command */
    char               Alea[TAILLE_ALEA];   		/*!< Alea given by the Booster */
    char               Reponse[TAILLE_ALEA]; 		/*!< Answer given by the Thunder */
    char               Ruf[32];   					/*!< ruf */
}
DATA_AUTHENTIFICATION_T;


/*! @brief  Secure authentification frame structure */
typedef struct
{
    BUF_ENTETE_T                EnteteTrame;				/*!< Frame header */
    DATA_AUTHENTIFICATION_T     DataAuthentification;		/*!< Data */
}
ENCODE_BUF_SECURITE_AUTHENTIFICATION_T;


/*! @brief  Secure start secu IUC structure (use in start secu IUC frame) */
typedef struct
{
    unsigned char      Cmd;			/*!< Command */
    unsigned char      Version;		/*!< Version */
    unsigned char      Ret;			/*!< Return status */
    char               Rufc;		/*!< ruf */
    unsigned int       CptInit;		/*!< Cpt init */
    char               Kcv[4];		/*!< KCV */
    char               ruf[8];		/*!< ruf */
}
DATA_START_SECU_IUC_T;

/*! @brief  Secure start secu IUC frame structure */
typedef struct
{
    BUF_ENTETE_T           EnteteTrame;			/*!< Frame header */
    DATA_START_SECU_IUC_T  DataStartSecuIuc;	/*!< Data */
}
ENCODE_BUF_SECURITE_START_SECU_IUC_T;




/*! @brief  Secure get key structure (use in get key frame) */
typedef struct
{
    unsigned char      Cmd;			/*!< Command */
    unsigned char      Ret;			/*!< Return status */
    char               Key[16];		/*!< Key */
    unsigned char      Init[8];		/*!< Init */
}
DATA_GET_IUC_KEY_T;

/*! @brief  Secure get key frame structure */
typedef struct
{
    BUF_ENTETE_T           EnteteTrame;		/*!< Frame header */
    DATA_GET_IUC_KEY_T     DataIucKey;		/*!< Data */
}
ENCODE_BUF_SECURITE_IUC_KEY_T;



typedef void (*PtFctVoidInt)(int );
typedef void (*PtFctVoidpVoid)(void *);
typedef void (*PtFctVoidVoid)(void );
typedef unsigned short int (*PtFctWordInt)(int );
typedef  int (*PtFctIntIntInt)(int,int );


/*! @brief  ARM structure use to cal the IRQ or Hisr Proc function with the AdrData parameter */
typedef struct{
	unsigned long 	LdrR0AdrData;		/*!< ARM code to load "AdrData" in R0 */
	unsigned long 	LdrR1Proc;			/*!< ARM code to load "Proc" in R1 */
	unsigned long 	BxR1;				/*!< ARM code to branch to the adress contains in R1 */
	void 			*AdrData;			/*!< Data pointeur given as parameter to "Proc" function */
	PtFctVoidpVoid	Proc;				/*!< Function pointeur */
	}MEM_CONTEXTE_ARM;


/*! @brief  Thumb structure use to cal the IRQ or Hisr Proc function with the AdrData parameter */
typedef struct{
	unsigned short 	LdrR0AdrData;		/*!< Thumb code to load "AdrData" in R0 */
	unsigned short	LdrR1Proc;			/*!< Thumb code to load "Proc" in R1 */
	unsigned short 	BxR1;				/*!< Thumb code to branch to the adress contains in R1 */
	void 			*AdrData;			/*!< Data pointeur given as parameter to "Proc" function */
	PtFctVoidpVoid	Proc;				/*!< Function pointeur */
	}MEM_CONTEXTE_THUMB;



// divers
#define 	IRQ_CPSR		       				0x80		/*!< Value of CPSR in IRQ mode */
//#define 	HISR_STACK_SIZE	      	512			/*!< Size of the Hisr stack */
#define 	OFFSET_DEBUT_CODE 				0x1C		/*!< Offset of the PATCHROMV2 in the Booster system */


#if !defined(UNSIGNED) && !defined(NUCLEUS)
typedef unsigned long           UNSIGNED;			/*!< Unsigned lon typedef */
typedef unsigned char           DATA_ELEMENT;		/*!< Unsigned char typedef */
typedef DATA_ELEMENT            OPTION;				/*!< DATA_ELEMENT typedef */
#endif



#endif

/*! @}  */

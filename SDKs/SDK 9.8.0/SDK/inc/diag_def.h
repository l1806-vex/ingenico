/*! @addtogroup KSFAM_DIAG
	* @{
 */ 

#ifndef _DIAG_DEF_H_
#define _DIAG_DEF_H_

/*
======================================================================
					List of Defines
======================================================================
*/

// index function for lire_infos_terminal
#define	FCT_INFOS_TERMINAL			1			/*!< lire_infos_terminal parameter : gets terminal informations */
#define	FCT_TAILLE_MEMOIRE			2			/*!< lire_infos_terminal parameter : memory size */
#define	FCT_NUMERO_SERIE				3   	/*!< lire_infos_terminal parameter : 14 digits serial number */
#define	FCT_IDENTITE_ROM				4			/*!< lire_infos_terminal parameter : ROM identifier */
#define	FCT_TOUTES_INFOS				5			/*!< lire_infos_terminal parameter : all informations */
#define FCT_INFOS_LOG_SYS				6			/*!< lire_infos_terminal parameter : gets system software identifier */
#define FCT_MEMOIRE							7			/*!< lire_infos_terminal parameter : memory informations */
#define FCT_COUPLEUR       			8			/*!< lire_infos_terminal parameter : smart card reader informations  */
#define FCT_DOWNLOAD						9			/*!< lire_infos_terminal parameter : download status */
#define FCT_ACQUIT_DOWNLOAD     10		/*!< lire_infos_terminal parameter : reset download status */
#define FCT_LIBELLE_TERMINAL    11		/*!< lire_infos_terminal parameter : terminal name (6 char max) */
#define FCT_AFF_REVEIL_DISPO    12  	/*!< lire_infos_terminal parameter : Only for compatibility with existing projects. It has not to be used. */

// index function for read_terminal_informations
#define	FCT_TERMINAL_INFO 			  1			/*!< read_terminal_informations parameter : gets terminal informations */
#define	FCT_MEMORY_SIZE   			  2			/*!< read_terminal_informations parameter : memory size */
#define	FCT_SERIAL_NUMBER				  3   	/*!< read_terminal_informations parameter : 14 digits serial number */
#define	FCT_ROM_IDENTITY				  4			/*!< read_terminal_informations parameter : ROM identifier */
#define	FCT_ALL_INFOS   				  5			/*!< read_terminal_informations parameter : all informations */
#define FCT_SYSTEM_SOFTWARE_INFO  6			/*!< read_terminal_informations parameter : gets system software identifier */
#define FCT_MEMORY_INFO					  7			/*!< read_terminal_informations parameter : memory informations */
#define FCT_CARD_READER    			  8			/*!< read_terminal_informations parameter : smart card reader informations  */
#define FCT_DOWNLOAD_STATUS			  9			/*!< read_terminal_informations parameter : download status */
#define FCT_RESET_DOWNLOAD_STATUS 10		/*!< read_terminal_informations parameter : reset download status */
#define FCT_TERMINAL_NAME         11		/*!< read_terminal_informations parameter : terminal name (6 char max) */
#define FCT_EXTENDED_SERIAL_NUMBER 13   /*!< read_terminal_informations parameter : 16 digits serial number */


#define TERM_FIXE 				0						/*!< Counter top terminal */
#define TERM_PORTABLE 		1						/*!< wireless terminal */
#define	TERM_RADIO				2  					/*!< wireless terminal */
#define MODEM_V32BIS  		0x02				/*!< V32 bis modem  */
#define GRAPHIQUE_4L  		0x04				/*!< graphic display 4 lines */
#define GRAPHIQUE_8L  		0x08				/*!< graphic display 8 lines */
#define GRAPHIQUE_16L 		0x10				/*!< graphic display 16 lines */
#define STANDARD 					0						/*!< standard display */
#define CAM2_PRESENT 			0x80				/*!< smart card reader "CAM2" present */
#define SAM_PRESENT  			0x40				/*!< Security module reader present */
#define SAM1_PRESENT 			0x01				/*!< Security module reader "SAM1" present */
#define SAM2_PRESENT 			0x02				/*!< Security module reader "SAM2" present */
#define SAM3_PRESENT 			0x04				/*!< Security module reader "SAM3" present */
#define SAM4_PRESENT 			0x08				/*!< Security module reader "SAM4" present */
#define EXIT_SYSTEM_ERROR 0x10				/*!< Only for compatibility with existing projects. It has not to be used. */


/*! @brief Give the name of the system software. */
typedef struct 
	{
		unsigned char	nom[8];			/*!< name of the software	 */
		unsigned short	crc;			/*!< CRC */
	}NOM_LOG_SYS;

/*! @brief Give the name of the system software. */
typedef struct 
	{
		unsigned char	name[8];			/*!< name of the software	 */
		unsigned short	crc;			/*!< CRC */
	}SYSTEM_NAME;


/*! @brief Give informations about the system software. */
typedef struct
		{
			unsigned char	nb_logiciels;			/*!< software number */
			NOM_LOG_SYS		infos_sys[6];			/*!< name of the system software. */
		}INFOS_LOG_SYSTEME;


/*! @brief Give informations about the system software. */
typedef struct
		{
			unsigned char	software_nbr;			/*!< software number */
			SYSTEM_NAME		infos_sys[6];			/*!< name of the system software. */
		}SYSTEM_SOFTWARE_INFO;


// constantes de retour de la fonction lire_infos_terminal 
#define	FORMAT_RETOUR_INCOHERENT	20			/*!< Only for compatibility with existing projects. It has not to be used. */
#define	FCT_NON_SUPPORTEE					21			/*!< function not supported by lire_infos_terminal */

/*! @brief Define a structure wich gives informations about the terminal. */
typedef struct
		{
			char						type_materiel;			/*!< hardware type. */
			char						config_materiel;		/*!< hardware configuration */
			unsigned long		taille_memoire;			/*!< memory size */
			char						os_type;						/*!< OS type */
			T_VERSION				os_version;					/*!< OS version */
			unsigned short	os_crc;							/*!< CRC of the OS */
			char						infos_materiel;			/*!< informations about the hardware. */
		}INFOS_TERMINAL;

/*! @brief Define a structure wich gives informations about the terminal. */
typedef struct
		{
			char						hardware_type;			/*!< hardware type. */
			char						hardware_config;		/*!< hardware configuration */
			unsigned long		memory_size;	  		/*!< memory size */
			char						os_type;						/*!< OS type */
			T_VERSION				os_version;					/*!< OS version */
			unsigned short	os_crc;							/*!< CRC of the OS */
			char						hardwatrer_info;		/*!< informations about the hardware. */
		}TERMINAL_INFOS;


/*! @brief Give he informations about the terminal (hardware, OS, etc.). */
typedef struct
		{
		INFOS_TERMINAL	infos_term;					/*!< Informations about the terminal */
		}TOUTES_INFOS;
		
/*! @brief Describe the memory state. */
typedef struct
		{
			unsigned short Taille_memoire_flash;						/*!< size of the flash memory. */
			unsigned short Taille_memoire_flash_restante;		/*!< size of the free flash memory. */
			unsigned short Taille_memoire_ram;							/*!< size of the RAM. */
			unsigned short Taille_memoire_ram_restante;			/*!< size of the free RAM. */
		}MEMOIRE;


/*! @brief Give the version of the reader. */
typedef struct
		{
			unsigned char materiel_coupleur[4];		/*!< hardware reader information */
			unsigned char log_coupleur[4];				/*!< software reader information */
		}VERSION_COUPLEUR;

/*! @brief Give the version of the reader. */
typedef struct
		{
			unsigned char hardware[4];		/*!< hardware reader information */
			unsigned char sogtware[4];		/*!< software reader information */
		}CARD_READER_INFO;
		
/*! @brief Define the download report. */
typedef struct
		{
			unsigned char etat;						/*!< state of the download. */
		}CR_DOWNLOAD;

/*! @brief Define the download report. */
typedef struct
		{
			unsigned char state;						/*!< state of the download. */
		}DOWNLOAD_STATUS;



#define EFT30F 		0x30		/*!< returned by lire_infos_terminal(FCT_LIBELLE_TERMINAL) */
#define EFT30   	0x30		/*!< returned by lire_infos_terminal(FCT_LIBELLE_TERMINAL) */
#define TWIN30    0x38		/*!< returned by lire_infos_terminal(FCT_LIBELLE_TERMINAL) */
#define X930    	0x34		/*!< returned by lire_infos_terminal(FCT_LIBELLE_TERMINAL) */


#define DEF_DIAG 10				/*!< number of defaults */
#define CPT_DIAG 52				/*!< number of counters */
#define TXT_DIAG 600			/*!< Text diag size */
#define CPT_LIFE 31				/*!< number of life counters (counter 0 reserved) */
#define CLE      0x1234		/*!< useful key value */

/*! @brief Describe a fault. */
typedef struct
  {
  unsigned char date[5];							/*!< Date of the fault */
  unsigned char critique;							/*!< critical */
  unsigned short num_def;							/*!< fault number */
  } DEFAUT; 

/*! @brief Define a structure describing a CPT. */
typedef struct
  {
  unsigned short num_cpt;							/*!< number of the CPT */
  unsigned long  valeur;							/*!< value of the CPT */
  } CPT;

/*! @brief Internal structure, the applications can't get access to it. */
typedef struct 
 {
  unsigned char date[5];							/*!< binary date */
  unsigned char nb_def_dia; 					/*!< maximum number of default  */
  unsigned int  nb_cpt_dia;						/*!< number of counters */
  unsigned int  len_txt_dia;					/*!< text diag length */
  unsigned char nb_def_dia_cur;				/*!< current number  */
  unsigned char nb_def_dia_cur_crit;	/*!< current number of defaults */
  unsigned int  nb_cpt_dia_cur; 			/*!< current number of counter */
  unsigned int  len_txt_dia_cur;			/*!< length of text diagnostic */
  DEFAUT defaut[DEF_DIAG];						/*!< default array */
  CPT cpt[CPT_DIAG];									/*!< counter array */
  char txt[TXT_DIAG+2];								/*!< text diagnostic */
} DIAG ;

/*! @brief This structure allows to stock the life counter of the terminal.  Never set to zero. (access to this structure : diagnostical mode via LLT). */
typedef struct 
 {
  unsigned char date[5];							/*!< Date of the first information saving. */
  unsigned int  nb_cpt_dia_cur;				/*!< count of life counter stocked. */
  CPT cpt[CPT_LIFE];									/*!< CPT. */
} LIFE ;


/*! @brief Describe a card (serial number, type, manufacturing date...). */
typedef struct
{
 unsigned char noserie[7];						/*!< serial number of the card (14 numbers) */
 unsigned char typeprod;							/*!< type of product (2 numbers) */
 unsigned char M87[11];								/*!< 22 BCD code number for the card. */
 unsigned char datefab[6];						/*!< manufacturing date */
} CONFPROD;


/*! @brief This structure is used to check the presence of all the components. */
typedef struct
{
 unsigned char printer;								/*!< 0 not present, 1 present */
 unsigned char buzzer;								/*!< 0 not present, 1 present */
 unsigned char swipe3;								/*!< 0 not present, 1 present */
 unsigned char com0;									/*!< 0 not present, 1 present */
 unsigned char com1;									/*!< 0 not present, 1 present */
 unsigned char usbhost;								/*!< 0 not present, 1 present */
 unsigned char usbslave;							/*!< 0 not present, 1 present */
 unsigned char ethernet;							/*!< 0 not present, 1 present */
 unsigned char mmc;										/*!< 0 not present, 1 present */
 unsigned char modemV32;							/*!< 0 not present, 1 present */
 unsigned char modemV34;							/*!< 0 not present, 1 present */
 unsigned char modemV90;							/*!< 0 not present, 1 present */
 unsigned char cflash;								/*!< 0 not present, 1 present */
 unsigned char cam1;									/*!< 0 not present, 1 present */
 unsigned char cam2;									/*!< 0 not present, 1 present */
 unsigned char sam1;									/*!< 0 not present, 1 present */
 unsigned char sam2;									/*!< 0 not present, 1 present */
 unsigned char sam3;									/*!< 0 not present, 1 present */
 unsigned char sam4;									/*!< 0 not present, 1 present */
 unsigned char tcpip;									/*!< 0 not present, 1 present */
 unsigned char ruf[50];								/*!< reserved for future use  */
} CONFLOG;

#endif

/*! @}  */ 


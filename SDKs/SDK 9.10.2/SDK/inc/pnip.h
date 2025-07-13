/*! @addtogroup KSFAM_CB2A
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PNIP_H
#define PNIP_H

#define CBCOMV5		    0x01
#define ENABLE		    0x01
#define ATT_DEFAUT	    0x05
#define TNR_DEFAUT	    30 /* secondes */
#define TSI_DEFAUT	    30 /* secondes */
#define COMV42A		    0x02
#define CBCOM12         0x12
#define CBCOM13         0x13
#define IPDU_LONGUE 28
#define IPDU_COURTE 12

/* ajout NF pour CBCOM juin 98 */
#define TNR_MIN       15
#define TNR_MAX       50

/* Gestion TSI */
#define TSI_MIN       30
#define TSI_MAX       1800

#define ANNUL_ACTIVE      			0x41

/*   parametres zone IPDU */
#define PGI    		  0xC1   /* identification protocole */
#define PGI_IPDU_CN   0xC2   /* IPDU de connexion. On choisit une IPDU_CN
                                courte, qui se fait dans le demande d'abonne */
#define PGI_IPDU_AC   0xC3   /* IPDU acquitement de deconnexion */
#define PGI_IPDU_AB   0xC4   /* IPDU de deconnexion */

#define	ZERO		    0x00
#define	UN			    0x01
#define	DEUX		    0x02
#define	TROIS		    0x03
#define	QUATRE	        0x04
#define	CINQ		    0x05
#define	SIX		        0x06
#define	SEPT		    0x07
#define	HUIT		    0x08
#define	NEUF		    0x09

#define	VAL_MAX_CNX		1070
#define	VAL_MAX_WRITE	1070
#define	VAL_MAX_READ	1070

#define	COMM_CONX		0X00		/*	les commandes ne doivent pas commencer	*/
#define	COMM_WRIT		0X01		/* par 0x05 pour rester compatible			*/
#define	COMM_READ		0X02
#define	COMM_COUP		0X03
#define	COMM_DECO		0X04
#define	COMM_ORIG		'\5'
#define	COMM_CR			0x06
#define	COMM_ACK		0x07
#define	COMM_OUT 		0x08
#define	COMM_ABORT 		0x09
#define	COMM_TEST		'_'

#define	PI_RACCORD		0x01
#define	PI_STANDARD		0x02
#define	PI_APPEL		0x03
#define	PI_CMD_MODEM	0x04
#define	PI_OUT_BUF		0x05
#define	PI_IN_BUF		0x06
#define	PI_CODE_REP		0x07
#define	PI_COMPL_X25	0x08

#define	LIAISON			0x03
#define	PROTOCOLE		0x04
#define	TYPE_PAD		0x05
#define	DOUBLE_90		0x06
#define	TIMER1			0x07
#define CHAINAGE        0x08
#define AUTO            0x09
#define	INDICE_LGR		0x0A
#define	INDICE_LGR_TOT	0x01

/* raison de l'appel : auto ou service */
#define TYPE_AUTO    0
#define TYPE_SERVICE 1

/*
======================================================================
			Data Structures Definition
======================================================================
*/
// compte rendu de numerotation 
/*! @brief Number report. */
typedef unsigned char CR_NUMEROTATION[2];

/*! @brief Structure STR_ETABL_CONNEX*/
typedef struct
{
   /*********************** CBCOM V5+V42A,CBCOM1.2,CBCOM1.3 *****************************/
                                               
   unsigned char   type_liaison;					/*!< Modem int/ext RNIS CLE GSM */
                                                
   unsigned char   type_protocole;				/*!< CBCOM V5 / V42A,CBCOM1.2,CBCOM1.3*/
                                               
   unsigned char   type_PAD;							/*!< type PAD
                                                - PAD_EBA
                                                - PAD_EMA
                                                - PAD_IP */
                                                
   unsigned char   timer_TNR; 						/*!< initial value of TNR*/
                                                
   unsigned char   lgr_data_compl;  			/*!< string length*/
                                               
   STR_COMP_X25    data_compl_X25;      	/*!< CBCOM V5+V42A = IPDU CN data
                                                - CBCOM1.2,CBCOM1.3 = pseudo session*/
                                               
   unsigned char   lgr_adr_raccord;				/*!< string length*/
                                                
   STR_ADR_RACCORD adr_raccord; 					/*!< PAD_EBA,PAD_EMA = PAD Number*/
                                                
   unsigned char   lgr_port;	        		/*!< string length*/
   unsigned char   port[40];     			    /*!< PAD_IP : port if DNS*/
                                              
   unsigned char   lgr_adr_appel;				  /*!< string length*/
   STR_ADR_APPEL   adr_appel; 					 				/*!<  PAD_EBA,PAD_EMA = adresse X25
                                                			- PAD_IP = XXX.XXX.XXX.XXX:PPPP  or
                                                			- http:\\www.monsite.com */
                                               

   /************************************* CBCOM 1.2 *************************************/
                                               
   unsigned char   type_codage_alpha;   		/*!< coding type
                                        				-  CODAGE_ASCII
                                        				-  CODAGE_EBCDIC*/
                                               
                                                
   /************************************* CBCOM 1.2 et 1.3 ******************************/
                                               
   unsigned char   type_protocole_cb2a;			/*!< protocole type
                                        				-  CB2A_TRANSFERT
                                        				-  CB2A_TRANSACTIONNEL */
                                        		
   unsigned char   version_cb2a[2];     		/*!< CB2A version*/
   
   unsigned char   service_initial;     		/*!< service CB2A
                                        		-  SERVICE_TELECOLLECTE
                                        		-  SERVICE_TELEPARAMETRAGE
                                        		-  SERVICE_AUTORISATION */
                                        		
   unsigned char   lgr_profile;  								//!< string length */
   
   unsigned char   profile[PROFILE_NAME_SIZE]; 	/*!< SSL profile (PAD_IP)*/
   
   unsigned char   timer_TSI; 									/*!< initial value of TSI*/
                                                
   unsigned char   lgr_unused2;  								/*!< string length */
                                            
   unsigned char   unused2[22+1]; 							/*!< unused2 */
 
   /**************************** Compatible avec CB2A dans application ******************/
                                                /****************************************/
   unsigned char   raison_appel;						/*!< Call reason
                                        			- CC_APPEL_DEM_AUTORISA
                                        			- CC_APPEL_INITIALISATION
                                        			- CC_APPEL_TELEPARAM_MANU
                                        			- CC_APPEL_TELEPARAM_AUTO
                                        			- CC_APPEL_TELECOLLE_MANU
                                        			- CC_APPEL_DIVERS
                                        			- CC_APPEL_TELECOLLE_AUTO*/
}STR_ETABL_CONNEX ;

#define RACCORDEMENT_GPRS_IP           0x10
#define RACCORDEMENT_GSM_X25           0x08
#define RACCORDEMENT_RNIS_CANALD       0x04
#define RACCORDEMENT_RTC_X25           0x02
#define RACCORDEMENT_LAN_IP            0x01



/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function sends an IPDU containing an applicative message (LT framework emission, and waits for the acquittal LT framework)
 * @param buf : message
 * @param lg : length of the message
 * @return Returns the report, 0 if ok
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern unsigned int ipdu_de_write(unsigned char *buf,unsigned short lg) ;


/*! @brief This function establishes the connection. (communication layer)
 * @param cr_numerotation : numerotation's report
 * @param param : pointer to structure STR_ETABL_CONNEX, parameters gave to establish the connexion.
 * @return None
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern unsigned int ipdu_etab_ligne(CR_NUMEROTATION cr_numerotation, STR_ETABL_CONNEX *param) ;


/*! @brief This function disconnects the communication.
 * @return
 * - report of the disconnexion.
 * - 0 if ok.
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 10) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern unsigned int ipdu_coup_ligne(void) ;


/*! @brief This function reads an IPDU containing an applicative message (read LT framework and acquit LA framework).
 * @param buf : message
 * @param lg : length of the message
 * @return 
 * - 0 if OK.
 * - see crcomm.h for detail
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 13) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern unsigned int ipdu_dt_read(unsigned char *buf,unsigned short *lg) ;


/*! @brief This function sends the IPDU for disconnection (C4 framework)
 * @param code_reponse : disconnection's answer.
 * @return None
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 11) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern void         ipdu_deconnecte(char code_reponse );


/*! @brief This function sets the IPDU effective timer.
 * @param val : timer value.
 * @return None 
 * @par exit (EXIT_DLL_CB2A_NOT_INITIALIZED + 34) if function does not exist
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern void         ipdu_set_timer_effectif(unsigned int val);


/*! @brief This function is used to get the IPDU effective timer.
 * @return Returns the timer value.
 * @par exit none
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern unsigned int ipdu_get_timer_effectif(void);

/*! @brief Get terminal network capabilities
* @return mask of terminal capabilities
* - RACCORDEMENT_GPRS_IP 0x10
* - RACCORDEMENT_GSM_X25 0x08
* - RACCORDEMENT_RNIS_CANALD 0x04
* - RACCORDEMENT_RTC_X25 0x02
* - RACCORDEMENT_LAN_IP 0x01
* @par exit none
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
extern unsigned int ipdu_capacite_raccordement(void) ;


/* ------------------------------------------------------------------------- */

#endif
/*! @} **/
#ifdef __cplusplus
}
#endif

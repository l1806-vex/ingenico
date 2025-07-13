/*! @addtogroup KSFAM_SANTE
	* @{
**/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef PROTOCOLE_H
#define PROTOCOLE_H

/*
======================================================================
					List of Defines
======================================================================
*/
#define TAILLE_PILE_SYSTEME      800

#define CR_DIALOGUE_OK           0        /*!< Execution without error.                             */
#define CR_DIALOGUE_KO           1        /*!< Execution with error.                             */
#define CR_DIALOGUE_CAISSE_ON    2        /*!< Enabling the connection box                    */
#define CR_DIALOGUE_CAISSE_OFF   3        /*!< Execution with error.                             */
#define CR_DIALOGUE_FCT          4        /*!< Execution with switching to FCT   */
#define LI_ENTETERECEPT         32        /*!< Header error expected for DIAL_Recept        */
#define LI_PARAMENTETE          33        /*!< Setting Error for DIAL_Recept             */
#define ACK_DEM_TEMPS          262        /*!< longer time gives                      */


/*
======================================================================
			State of the PLC treatment protocol
======================================================================
*/

#define PROTOCOLE_DEFAUT                0  /*!< default */
#define PROTOCOLE_ATTENTE_INIT          1  /*!< wait init with InitDLLProtocole */
#define PROTOCOLE_ATTENTE_OPEN          2  /*!<  wait open with       OpenDLLProtocole */
#define PROTOCOLE_ATTENTE_COM           3  /*!< wait message on COM                      */
#define PROTOCOLE_ATTENTE_TRAITEMENT    4  /*!< message receive wait treatment */
#define PROTOCOLE_TRAITEMENT            5  /*!< treatment of message                        */
#define PROTOCOLE_SUSPENDU              6  /*!< suspend protocol                          */
#define PROTOCOLE_HORS_DE_PORTEE        7  /*!< with Bluetooth out of range               */
#define PROTOCOLE_SUSPENDU_CAISSE       8  /*!< suspend protocol                          */

/*
======================================================================
			Protocol Event
======================================================================
*/
#define DEMANDE_INIT                    0  /*!< Request initialization                     */
#define DEMANDE_OPEN                    1  /*!< Request Open                          */
#define DEMANDE_CLOSE                   2  /*!< Request to Close                         */
#define DEMANDE_EMISSION                3  /*!< request send message             */
#define DEMANDE_RECEPTION               4  /*!< request receive message            */
#define DEMANDE_ALLONGEMENT             5  /*!< request of longer time   */
#define DEMANDE_TRAITEMENT              6  /*!<request treatment       */
#define FIN_DIALOGUE                    7  /*!< Closing peripherals                  */
#define DEMANDE_SUSPENSION              8  /*!< suspend request                      */
#define DEMANDE_TRAITEMENT_APPLI        9  /*!<request treatment       */

/*
=================================================================================
			            automate of treatment
=================================================================================
   ETAT0 : PROTOCOLE_ATTENTE_INIT
      Only event 0 is authorise                              ==>  STATE1
=================================================================================
   ETAT1 : PROTOCOLE_ATTENTE_OPEN
      Only event 1 is authorise                              ==>  STATE2
   ETAT2 : PROTOCOLE_ATTENTE_COM                                                 
    --> event 2, close                                         ==> STATE1      
    --> event 3, send message                                 ==> STATE2      
    --> event 4, receive message                               ==> STATE2       
    --> event 5, send a request of longer time                   ==> STATE2       
    --> If the message is ok send an event to the manager       ==> STATE3   
=================================================================================
   ETAT3 : PROTOCOLE_ATTENTE_TRAITEMENT                                               
    --> event 2, fermeture                                     ==> STATE1        
    --> event 6, traitement                                    ==> STATE4     
=================================================================================
   ETAT4 : PROTOCOLE_TRAITEMENT                                                    
    --> event 2, fermeture                                     ==> STATE1        
    --> event 3, emission du message                           ==> STATE4      
    --> event 4, reception d'un message                        ==> STATE4    
    --> event 5, emission d'une demande d'allongemen de temps  ==> STATE4  
    --> End of treatment                                       ==> STATE2  
=================================================================================
*/



/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function initializes internal variables of the protocol 
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  InitDLLProtocole(void);


/*! @brief This function is used to initiate seizure of parameters for the DLL protocol
 *	@return
 *	- CR_DIALOGUE_CAISSE_ON		 Request activation of the connection box	
 *	- CR_DIALOGUE_CAISSE_OFF   Request to cancel the connection box 
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  ParamDLLProtocole(void);


/*! @brief This function is used to initiate seizure of parameters for the DLL protocol 
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  PrintDLLProtocole(void);


/*! @brief This function is used to open devices and wait message
 *
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  OpenDLLProtocole(PFONCDEBITCAISSE ptr);


/*! @brief This function closes peripherals   
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  CloseDLLProtocole(void);

/*! @brief This function Suspend the dialog peripherals   
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  SuspendDLLProtocole(void);

/*! @brief This function Set the default parameters   
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  DefaultDLLProtocole(void);

/*! @brief This function perform the treatment of message   
 *	@return
 *	- CR_DIALOGUE_OK		no error.	
 *	- CR_DIALOGUE_KO    error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int TraiterDLLProtocole(NO_SEGMENT no_appli);

#define MAX_TRANSACTION_MODE 100

/*! @brief This function return the transaction mode of an application 
 *  @param typ_code           : input parameter. application type.
 *  @param transaction_mode   : output parameter. transaction mode.
 *	@return
 *	- 0   if OK
 *	- EOF if function doesnt not exist
 *  @note The transaction is used to send the response to cash register in PSC protocol
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  CA_Get_Transaction_mode(unsigned short typ_code,unsigned char *transaction_mode);

/*! @brief This function allow an application to set his transaction mode
 *  @param typ_code           : input parameter. application type.
 *  @param transaction_mode   : input parameter. transaction mode.
 *	@return
 *	- 0   if OK
 *	- 1   number maximum of applications reached
 *	- EOF if function doesnt not exist
 *  @note The transaction is used to send the response to cash register in PSC protocol
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
**/
int  CA_Set_Transaction_mode(unsigned short typ_code,unsigned char transaction_mode);

/*! @brief This function waits for a PPS message.
 * @param pucRecepMessage   : output parameter. Reception message buffer.
 * @param pusLgRecepMessage : input/output parameter. Input : maximum size of reception buffer. Output : real size of received message.
 * @param pucPAD_Appelant   : output parameter. emiter pad.
 * @param pusEXT            : output parameter. Time allocated by caller to execute the request.
 * @param pucEnteteMessage  : input parameter. header of awaited message.  If NULL, all headers are accepted.
 * @param usLgEnteteMessage : input parameter. Header length. (between1 and 3)
 * @return
 * - CR_DIALOGUE_OK = no error.
 * - CR_DIALOGUE_KO = error in execution.
 * - LI_ENTETERECEPT = incorrect awaited header for DIAL_Recept. 
 * - LI_PARAMENTETE = error in param etering DIAL_Recept.
 *  @par exit (EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 8) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
unsigned short DIAL_Recept (unsigned char  * pucRecepMessage,
                            unsigned short * pusLgRecepMessage,
                            unsigned char  * pucPAD_Appelant,
                            unsigned short * pusEXT,
                            unsigned char  * pucEnteteMessage,
                            unsigned short   usLgEnteteMessage);



/*! @brief This function sends a message.
 * @param pucEmissMessage : buffer containing the message.
 * @param usLgEmissMessage : length of the message.
 * @param ucPAD_Dest : calling PAD.
 * @return
 * - CR_DIALOGUE_OK		 no error.	
 * - CR_DIALOGUE_KO    error in execution.
 *  @par exit (EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
unsigned short DIAL_Emiss (unsigned char  * pucEmissMessage,
                           unsigned short   usLgEmissMessage,
                           unsigned char    ucPAD_Dest);



/*! @brief This function emits a request for adding time.
 * @param pucEmissMessage : buffer containing the message. 
 * This message will be sent back to calling application if the added time request is refused.
 * @param usLgEmissMessage : length of the message.
 * @param ucPAD_Dest : reception PAD.
 * @param usTMax : add time requested.
 * @return 
 * - CR_DIALOGUE_OK = No errors during the execution.
 * - CR_DIALOGUE_KO = Error during the execution.
 * - ACK_DEM_TEMPS = Adding time allowed.
 *  @par exit (EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 10) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
unsigned short DIAL_DemTemps (unsigned char  * pucEmissMessage,
                              unsigned short   usLgEmissMessage,
                              unsigned char    ucPAD_Dest,
                              unsigned short   usTMax);


/*! @brief This function emits an event message
 * @param pucMessage : buffer containing the message. This message will be sent to POS.
 * @param ulLgMsg : length of the message.
 * @return 
 * - CR_DIALOGUE_OK = No errors during the execution.
 * - CR_DIALOGUE_KO = Error during the execution.
 *  @par exit (EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 18) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
unsigned short DIAL_EnvoyerEvt( unsigned char* pucMessage, 
								unsigned long ulLgMsg);

							
/*! @brief This function force protocole to work with TLV4 specifications.
 * @return
 * - CR_DIALOGUE_OK		no error.	
 * - CR_DIALOGUE_KO		error in execution.
 *  @par exit None
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
unsigned short DIAL_ActiverTLV4 (void);



/*! @brief This function simulates emission/reception of PSS messages.
 * @param noappli : Number of the calling application.
 * @param pucEmissMessage   : Message.
 * @param usLgEmissMessage  : Length of the message.
 * @param pucRecepMessage   : Answer.
 * @param pusLgRecepMessage : Length of the answer.
 * @return
 * - CR_DIALOGUE_OK = No errors during the execution.
 * - CR_DIALOGUE_KO = Error during the execution.
 *  @par exit (EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
void APPLI_Dialogue(NO_SEGMENT      noappli,
                    unsigned char  *pucEmissMessage,
                    unsigned short  usLgEmissMessage,
                    unsigned char  *pucRecepMessage,
                    unsigned short *pusLgRecepMessage);


/*! @brief This function reads PSS parameters.
 * @param pucPAD_Appelant : calling PAD.
 * @param pusBWT : inter block time.
 * @param pusEXT : execution time.
 * @return None (void).
 *  @par exit (EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 11) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
void OS_SysGetParamEXT (unsigned char  * pucPAD_Appelant,
                        unsigned short * pusEXT,
                        unsigned short * pusBWT);

#endif

/*! @} **/
#ifdef __cplusplus
}
#endif

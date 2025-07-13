/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/


/*
======================================================================
					List of Defines
======================================================================
*/


/*
======================================================================
	TO_BE_TRANSLATED: evenement fin de time out 
	Aucun conflit car dans une tache differente
	Tache saisie clavier : timer de supervision de la saisie                      
	Tache saisie pinpad  : timer de supervision de la saisie  
	Tache PSC            : Supervision de reception de la trame  
	Couche MODEM         : Supervision de reception de la trame  
	Tache ecran de repos : Pour dire qu'il faut sortir de l'ecran de repos  
======================================================================
*/

#ifdef __cplusplus
extern "C" {
#endif


#define EVT_TIMER              10																 
#define TIMER                  (unsigned int)(1<<EVT_TIMER)			 

// Les evenements remontes aux applications sont : 
// evenement message IAM 
#define EVT_MSG                29															 	 
#define MSG                    (unsigned int)(1<<EVT_MSG)				 

// evenement de fin de saisie 
#define EVT_SAISIE             12																 
#define SAISIE                 (unsigned int)(1<<EVT_SAISIE)		 

// English version 
#define EVT_ENTRY              12																 
#define ENTRY                  (unsigned int)(1<<EVT_ENTRY)			 

// evenement de fin traitement de la tache PSC 
#define EVT_PSC                13																 
#define PSC                    (unsigned int)(1<<EVT_PSC) 			 

// evenement de fin de saisie pinpad 
#define EVT_SAISIE_PPAD        14																			 
#define SAISIE_PPAD            (unsigned int)(1<<EVT_SAISIE_PPAD) 		 

// English version 
#define EVT_ENTRY_PPAD         14																			 
#define ENTRY_PPAD             (unsigned int)(1<<EVT_ENTRY_PPAD) 			 

// evenement de synchro entre tache protocole et M2OS  	
#define EVT_SYNCHRO_WAKEUP     31																			 
#define SYNCHRO_WAKEUP         (unsigned int)((unsigned int)1<<EVT_SYNCHRO_WAKEUP)	 

// evenement de synchro entre tache protocole et M2OS  	
#define EVT_SYNCHRO_WAKE_UP    15
#define SYNCHRO_WAKE_UP        (unsigned int)((unsigned int)1<<EVT_SYNCHRO_WAKE_UP)	 

// evenement de synchro entre tache protocole et M2OS  	
#define EVT_SYNCHRO_DIALOG     11																			 
#define SYNCHRO_DIALOG         (unsigned int)(1<<EVT_SYNCHRO_DIALOG)	 

// evenement message PROTOCOLE 
#define EVT_DIALOG             30																			 
#define DIALOG                 (unsigned int)(1<<EVT_DIALOG)					 


/*
======================================================================
	evenement interne 
	evenement arret de la saisie 
	Aucun conflit car dans une tache differente  
	Tache saisie clavier : fin de la saisie demandee par l'application 
	Tache saisie pinpad  : fin de la saisie demandee par l'application  
======================================================================
*/


#define EVT_ARRET_SAISIE       11																		 
#define ARRET_SAISIE           (unsigned int)(1<<EVT_ARRET_SAISIE)	 

/*
======================================================================
	evenement PSC 
======================================================================
*/

// evenement prise de contact 
#define EVT_CONTACT_OCL  5																				 
#define CONTACT_OCL      (unsigned int)(1<<EVT_CONTACT_OCL)				 

// evenement pour acquitement du bloc intermediaire 
#define EVT_ACK_PSC      6																				 
#define ACK_PSC          (unsigned int)(1<<EVT_ACK_PSC)						 

// evenement timeout de la tache PSC 
#define E_TIMEOUT_PSC	   8																				 
#define TIMEOUT_PSC 	  (1 << E_TIMEOUT_PSC)											 

// evenement suspension de la tache PSC
#define EVT_SUSPEND_PSC  7																				 
#define SUSPEND_PSC      (unsigned int)(1<<EVT_SUSPEND_PSC)				 

// evenement arret de la psc 
#define EVT_ARRET_PSC    12																				 
#define ARRET_PSC        (unsigned int)(1<<EVT_ARRET_PSC) 				 

// evenement debut de l'emission 
#define EVT_EMI_PSC      14																				 
#define EMI_PSC          (unsigned int)(1<<EVT_EMI_PSC)						 

// evenement debut de la reception 
#define EVT_REC_PSC      15																				 
#define REC_PSC          (unsigned int)(1<<EVT_REC_PSC)						 

#define         TaskApplication          3												 
#define         TaskIam1                 7												 
#define         TaskIam2                 8												 
#define         TaskIam3                 9												 
#define         TaskIam4                10												 
#define         TaskModem144            11												 

/*! @} **/
#ifdef __cplusplus
}
#endif

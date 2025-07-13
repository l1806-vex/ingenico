/*! @addtogroup KSFAM_M2OS
	* @{
**/


/*
======================================================================
					List of Defines
======================================================================
*/

#ifndef ETAT_H
#define ETAT_H

#define DIAL_NON 0
#define DIAL_OUI 1

#define SEQ_INITIALISE      0xC3
#define SEQ_NON_INITIALISE  0x3C
#define EVOLHOST     3 								/*!< evolution in progress       */
#define EVOLREUSSI   2 								/*!< evolution as creation DOWNLOAD.LST    */
#define EVOLENCOURS  1 								/*!< evolution in progress      */
#define RAZEVOL      0 								/*!< no evolution in progress         */

#define VOLUME_TRANSFER       "TRANSFER"
#define VOLUME_ACTIVATE       "ACTIVATE"
#define VOLUME_MANAGER        "MANAGER"
#define VOLUME_MANAGER_RECEPT "MGR_RECEPT"
#define VOLUME_SYSTEM         "SYSTEM"
#define VOLUME_HOST           "HOST"
#define EXT_FILE_PARAM        "PAR"  /* extension des fichiers parametres */
#define VEILLE_INI            "SCREEN.INI"
#define TRANSFER_INI          "TRANSFER.INI"
#define FICHIER_VEILLE        "SCREEN.BMP"
#define VOLUME_LICENCE	      "LICENCE"  			/*!<  PBE : Server License 04-979 */     
#define VOLUME_LIC_DIA		  "LIC_DIA"  				/*!<  PBE : Server License 04-979 */    
#define VOLUME_LIC_TMP		  "LIC_TMP"  				/*!<  PBE : Server License 04-979 */     
#define NB_MAX_FICHIER        (10+2)    			/*!<  for copies in writing  */

#define NIV_V5_AVECMONTANT   2
#define NIV_V5_SANSMONTANT   3
 

/*! @brief This function is the main function in an application  
 *
 *	@param size  : data size
 *	@param data  : Is a union of all the entry point with additional information
  *	@return 
 * -  FCT_OK
 * -  STOP   
 *
 * @include etat_Sample_09.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/
extern int Main                       (unsigned int size, StructPt *data);

/*! @brief This function is used to carry out the actions required after a reset or an initial load 
 *
 *	i.e Services registration, recovery procedure, disk creation and formatting, ram back-up, check for cold / warm reset
 *
 *	@b Activation: when the application is restarted on terminal reset 
 *
 *  @b Type: @c BROADCAST : all applications are called                                            
 *
 *  @b Environment: All peripherals are closed
 *	@param no  : application rank
 *	@param in  : NULL pointer
 *	@param out : S_TRANSOUT structure
 *	@return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/
extern int after_reset                (NO_SEGMENT no, void *in,                  S_TRANSOUT *out);


/*! @brief This function is used to inform applications that Manager force its own parameters initialisation
 *
 * @b Activation: called upon manager initialisation
 *
 * @b Type: @c BROADCAST : all applications are called                                            
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/ 
extern int auto_over                  (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function Allows application to print its own calls schedule receipt         
 *
 * @b Activation: called when operator selects the Manager menu > Consultation > Call > Planning of Call
 *
 * @b Type: @c BROADCAST : all applications are called                                            
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int mcall                      (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function is used to ask an application to process a card in the reader 
 *
 * @b Activation: when an application want to process a card in transparent mode
 *
 * @b Type: 
 * -  @c POLLING : Manager stops when the first application returns STOP or
 * -  @c SELECTING : if the field response is_card_specific service take the value REP_STOP; The field response takes the value REP_STOP when application want to process the card 
 *
 * @b Environment: 
 * -  All peripherals are closed
 * -  card present in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int card_inside                (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief This function is used to process serial link event. 
 *
 * @b Activation: handled by the NULL protocol ( NULL protocol DLL to be loaded )
 *
 * @b Type: @c POLLING : Manager stops when the first application returns STOP 
 *
 * @b Environment: No card in CAM0 reader
 * @param no  : application rank
 * @param in  : S_COMIN structure
 * @param out : S_COMOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int com_event                  (NO_SEGMENT no, S_COMIN *in,               S_COMOUT  *out);


/*! @brief This function allows applications to print transactions total receipt
 *
 * @b Activation: called when operator selects the Manager menu > Consultation > Transactions
 *
 * @b Type: @c BROADCAST : all applications are called                                            
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int consult                    (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function is used to process a debit EMV chip card transaction. 
 *
 * @b Activation: called when AID is selected for this application 
 *
 * @b Type: @c SELECTING : only one application is called
 *
 * @b Environment: 
 * -  All peripherals are closed except CAM0 reader and chip card is already powered on 
 * -  chip card in reader 
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int debit_emv                  (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief This function is used to process a non EMV chip card or a magnetic stripe or card manual entry transaction. 
 *
 * @b Activation:  
 * -  @c case1 : called when a magnetic stripe is swiped ( ISO2 or ISO1+ISO2 or ISO3+ISO2 or ISO1+ISO2+ISO3 ) 
 * -  @c case2 : called when a non EMV card is detected and after application selection 
 * @b Type: 
 * -  case1 : @c BROADCAST : all applications are called
 * -  case2 : @c SELECTIVE : application selected by application selection
 *
 * @b Environment: 
 * -  All peripherals are closed except CAM0 reader 
 * -  chip card already in CAM0 reader and powered on 
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int debit_non_emv              (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief This function is the end of transaction process
 *
 * @b Activation: after debit_non_EMV or debit_EMV 
 *
 * @b Type: @c SELECTING : only one application is called
 *
 * @b Environment: 
 * -  All peripherals are closed 
 * -  No card in CAM0 reader         
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 * @note DEBIT_OVER is not called if the field rc_payment (in DEBIT_EMV response) takes the "PAY_OTHER_AID" value.
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int debit_over                 (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function inform applications that a software or an hardware configuration has been done on the terminal
 *
 * @b Activation: After running the INITM Manager operator function 
 *
 * @b Type: @c BROADCAST : all applications are called
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : S_EVOL_CONF structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int evol_config                (NO_SEGMENT no, S_EVOL_CONF *in,           void *out);


/*! @brief This function informs application that a parameters file is detected in the system disk [3] or the host disk.
 *
 * Parameters files are loaded as an application using LLT and must have .par extension. 
 *
 * @b Activation: called upon reception of a parameter file by the Manager, this is done on a reset. As this file is never cleared (except if the file is sent on host disk; in this case, the file is deleted by the manager after the broadcast (*)) otherwise explicitely removed using LLT ,  it is submitted on each reset to the application. 
 *
 * (*) : files with .BRD, .BDF send on HOST disk are also removed by the manager after processing by applications.
 *
 * @b Type: @c BROADCAST : all applications are called
 *
 * @b Environment: 
 * -  All peripherals are closed 
 * -  No card in CAM0 reader         
 *
 * @param no  : application rank
 * @param in  : S_FILE structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/      
extern int file_received              (NO_SEGMENT no, S_FILE *in,                void *out);


/*! @brief This function is used to get the application profile 
 *
 * @b Activation: Upon receiving a date or software update PSS message  
 *
 * @b Type: @c SELECTING : only application that rejects the update is called
 *
 * @b Environment: All peripherals are closed 
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_IDENT_OUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int get_order                  (NO_SEGMENT no, void *in,                  S_IDENT_OUT *out);


/*! @brief This function asks application AIDs list that it supports  
 *
 * @b Activation: after IS_FOR_YOU_BEFORE when an EMV card is detected 
 *
 * @b Type: @c BROADCAST : only EMV applications are polled
 *
 * @b Environment:  
 * -  All peripherals are closed except CAM0 reader 
 * -  chip card already in CAM0 reader and powered on         
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : _DEL_ structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int give_aid                   (NO_SEGMENT no, S_TRANSIN *in,             _DEL_ *out);


/*! @brief This function is used to Get from applications supplementary information to be returned to the Cash Register via the PSC protocol ( in case of Cash Register connexion )
 *
 * @b Activation: after a transaction 
 *
 * @b Type: @c SELECTING : only the application that process the payment
 *
 * @b Environment:  
 * -  All peripherals are closed 
 * -  no chip card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_INFOS_CXOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/      
extern int give_info_cx               (NO_SEGMENT no, void *in,                  S_INFOS_CXOUT *out);


/*! @brief This function is used to Get the currencies supported by the application
 *
 * @b Activation: called when currency table is updated by the Manager ( on reset, end of more_function and time_function services)
 *
 * @b Type: @c BROADCAST : all applications are polled              
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_MONEYOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP  
 * @note  
 * -  The field response_number contains the response number coming from the applications to the manager 
 * -  S_MONEY contains the supported currencies for this application ( name, code and decimal position ). 
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int give_money                 (NO_SEGMENT no, void *in,                  S_MONEYOUT *out);


/*! @brief This function asks application to define its working environment.
 *
 *	3 working environments are defined today:
 *
 * -  TYP_CARTE  : Generic  
 * -  TYP_HEALTH : French Health Care   
 * -  TYP_EXPORT : Export (Don't use in French Bank domain) 
 *
 * According to the environment, Manager will select common parameters set and adapt its internal processing (some messages, keyboard management...)	
 *
 * @b Activation: called at the boot time.
 *
 * @b Type: @c BROADCAST : all applications are polled              
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_INITPARAMOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 *  @par Example:
 *
 *	2 Parameters: Param 1 | Param2
 *
 *	Application1 needs parameter param1 only. Application2 needs both parameters param1 and param2. mask returned by application1 will be : 0x10 mask returned by application2 will be : 0x11
 *
 *	Both param1 and param2 will also be handled (if at least one application need this parameter, it will be handled by the manager)  See #is_change_init for parameter mask defines.
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int give_your_domain           (NO_SEGMENT no, void *in,                  S_INITPARAMOUT *out);


/*! @brief This function allows an application to display its own idle message
 *
 *  TIMER event is sent to specify the user application must exit from 
 *  idle_message() service call, because manager needs the DISPLAY to 
 *  continue its treatment. 
 *
 *  If user application use this event, it has to give the hand back to 
 *  manager as soon as your application gets the TIMER event.
 *
 * @b Activation: each time the manager goes back idle;  This entry point is launched by a specific Manager task
 *
 * @b Type: @c SELECTING : only one application is called, the one that has an higher priority on idle_message  
 *
 * @b Environment: 
 * -  All peripherals are open except the display 
 * -  No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @include etat_Sample_10.c
 * @include etat_Sample_11.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int idle_message               (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function Informs the Manager that track read is CB type
 *
 * @b Activation: called in case of  E protocol on track 2 reading 
 *
 * @b Type: @c BROADCAST  : all applications are polled
 *
 * @b Environment: 
 * -  All peripherals are closed
 * -  No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : S_BIN_IN structure
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note
 * -  The field response takes the value REP_OK when application has recognised a CB card 
 * -  The field response takes the value REP_KO when application does not recognised a CB card 
 * -  The field response_number contains the response number coming from the applications to the manager 
 * 
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int is_bin_cb                  (NO_SEGMENT no, S_BIN_IN *in,              S_ETATOUT *out);


/*! @brief This functions asks the application that process the selected AID if the EMV transaction can be run
 *
 * @b Activation: called once AID has been selected for this application prior running the EMV debit. This is to solve the case of several applications that can process a same AID
 *
 * @b Type: @c SELECTING : only EMV applications that can process the selected AID
 *
 * @b Environment: 
 * -  All peripherals are closed except the card reader
 * -  card in CAM0 reader and powered on
 *
 * @param no  : application rank
 * @param in  : S_AID structure
 * @param out : S_CARDOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP  
 * 
 * @note
 * -  The field cardappnumber takes a value different from 0 when application want to process the EMV card. In such case   cardapp.priority must contain the priority and name for each application inside the card. 
 * -  The field cardappnumber takes the value 0 when application don't want to process the EMV card  
 * -  The field response_number contains the response number coming from the applications to the manager 
 *	
 *  @par Example:
 *
 *	A sample of implementation of IS_CARD_EMV_FOR_YOU entry point
    Two merchants with four card holder each.
 *
 *	In this sample, there is a cardholder selection with 'VISA', 
    'AMEX', 'DINERS', 'MASTER' and 'CB'
 *	
 *	1. If cardholder is 'VISA', there is a merchant selection with 'LOG1' and 'LOG2'
 * -  If merchant is 'LOG1',entry point DEBIT_EMV is called 
      with value 2 for cardapplinum field of S_TRANSIN structure.
 * -  If merchant is 'LOG2',entry point DEBIT_EMV is called 
      with value 1 for cardapplinum field of S_TRANSIN structure.
 *
 *	2. If cardholder is 'MASTER', entry point DEBIT_EMV is called with value 2 for cardapplinum field of S_TRANSIN structure.
 *
 *	3. If cardholder is 'AMEX', entry point DEBIT_EMV is called with value 3 for cardapplinum field of S_TRANSIN structure.
 *
 *  4. If cardholder is 'DINERS', entry point DEBIT_EMV is called with value 4 for cardapplinum field of S_TRANSIN structure.
 *
 *  5. If cardholder is 'CB', entry point DEBIT_EMV is called with value 4 for cardapplinum field of S_TRANSIN structure.
 *

 * @include etat_Sample_01.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int is_card_emv_for_you        (NO_SEGMENT no, S_AID *in,                 S_CARDOUT *out);


/*! @brief This function asks if application want to process the card when it is swiped or introduced in CAM0 reader. 
 *
 * This is dedicated to card specific processing. 
 *
 * @b Activation: 
 * -  once a card is detected in swipe or CAM0 reader
 * -  after amount entry and once a card is detected in swipe or CAM0 reader
 * -  French domain : also for credit and cancel operations 
 *
 * @b Type: @c POLLING : Manager stops when the first application returns STOP
 *
 * @b Environment: 
 * -  All peripherals are closed
 * -  card in swipe or CAM0 reader 
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note
 * -  The field response takes the value REP_OK when applicaiton want that a domain (Type Card, Healt or Export) to process the card in CARD_INSIDE entry point.
 * -  The field response takes the value REP_STOP when application want to process the card in CARD_INSIDE entry point.
 * -  The field response takes the value REP_KO when application don't want to process the card coming from the applications to the manager.
 * -  The field response_number contains the response number coming from the application to the manager.
 *
 * @b Comment:
 * -  If only one application wants to process the card, the manager then calls CARD_INSIDE entry point
 * -  If more than one application wants to process the card, the manager stops its selection process and asks for card removal
 * -  If no application wants to process the card, the managers goes on with the selection process.
 *
 * @include etat_Sample_06.c
 * @include etat_Sample_07.c
 * @include etat_Sample_08.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int is_card_specific           (NO_SEGMENT no, S_TRANSIN *in,             S_ETATOUT *out);


/*! @brief this function provides to the manager a list of parameters that cannot be changed
 *
 * @b Activation: called when Manager needs to update its own parameters or when an application request  a Manager parameters modification.
 *
 * @b Type: @c BROADCAST: all applications are polled
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int is_change_init             (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief This function is an authorisation to be deleted by the OS
 *
 * @b Activation: each time the operator selects the menu SUPPRESSION 
 *
 * @b Type: @c SELECTING      : Manager calls the application that must be suppressed
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_DELETE structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int is_delete                  (NO_SEGMENT no, void *in,                  S_DELETE *out);


/*! @brief This function provides authorisation to the Manager to process a terminal downloading  (local or remote)                  
 *
 * @b Activation: each time the operator selects the Downloading menu 
 *
 * @b Type: @c BROADCAST: all applications are polled 
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int is_evol_pg                 (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief Prior to running a debit transaction, this function asks application to recognise the magnetic stripe card or the card number manually entered or chip card in reader in order to be a candidate. 
 *
 * Applications being declared candidates will be placed after EMV applications in the list.
 *
 * @b Activation: 
 * -  called upon magnetic stripe reading or card number manual entry 
 * -  called after IS_FOR_YOU_BEFORE in case of non EMV card 
 * -  called after GIVE_AID in case of EMV card 
 *
 * @b Type: @c BROADCAST: all applications are polled
 *
 * @b Environment: 
 * -  All peripherals are closed except CAM0 
 * -  card in CAM0 reader and powered on 
 *
 * @param no  : application rank
 * @param in  : NULL structure
 * @param out : S_CARDOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *	
 *  @par Example:
 *
 *	A sample of implementation of IS_FOR_YOU_AFTER entry point
    Two merchants with four card holder each.
 *
 *  Entry point DEBIT_EMV is called with value 2 for cardapplinum field of S_TRANSIN structure ('VISA' of 'LOG1')
 *	

 * @include etat_Sample_02.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int is_for_you_after           (NO_SEGMENT no, S_TRANSIN *in,             S_CARDOUT *out);


/*! @brief Prior to running a debit transaction, this function asks application to recognise the magnetic stripe card or the card number manually entered or chip card in reader in order to be a candidate. 
 *
 *	Applications being declared candidate will be placed before EMV applications in the list. 
 *
 * @b Activation: called on chip card insertion 
 *
 * @b Type: @c BROADCAST: all applications are polled
 *
 * @b Environment: 
 * -  All peripherals are closed
 * -  card in CAM0 reader and powered off
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int is_for_you_before          (NO_SEGMENT no, S_TRANSIN *in,             S_ETATOUT *out);


/*! @brief This function provides authorisation for an update from the application 
 *
 * @b Activation: called upon reception of PSS update message 
 *
 * @b Type: @c SELECTING : only the application that must be updated is called     
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : S_IDENT_PG structure
 * @param out : S_ACTIONOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note
 * -  The field action must be equal to REFUS to reject the software update
 * -  The field action must be equal to INSTALL_OK to accept the software update  
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int is_install_pg              (NO_SEGMENT no, S_IDENT_PG *in,            S_ACTIONOUT *out);


/*! @brief This function is used to get the specific application name for this domain
 *
 * @b Activation: called at Manager start-up if this application returns Health Care domain
 *
 * @b Type: @c BROADCAST : all applications are polled  from this domain
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_LIBELLEOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note The field response_number contains the response number coming from the applications to the manager
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int is_libelle                 (NO_SEGMENT no, void *in,                  S_LIBELLEOUT *out);


/*! @brief This function is used to get application name ( 12 ASCII + 0 characters ) to be displayed at operator side
 *
 * @b Activation: called when F key is pressed
 * @b Limitation to 15 applications
 *
 * @b Type: 
 * -  @c BROADCAST : all applications are polled or;
 * -  @c SELECTING : only few applications are to be called (in case of application selection)
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int is_name                    (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief This function checks if application can process the PSS message by providing the header bytes ( first 3 bytes of the message )
 *
 * @b Activation: called upon reception of a PSS message on the COM0 serial port. PSS DLL must be loaded and active
 *
 * @b Type: @c BROADCAST : all applications are called for this domain                                            
 *
 * @b Environment: All peripherals are closed (except the COM0 port) 
 * @param no  : application rank
 * @param in  : S_IDENT_LOG structure
 * @param out : S_ORDEROUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int is_order                   (NO_SEGMENT no, S_IDENT_LOG *in,           S_ORDEROUT *out);


/*! @brief This function is used to provide application state ( initialised or not ) to the Manager
 *
 * @b Activation: called when the Manager checks if there is at least one initialised application in order to display the idle message otherwise the message 'Initialise an application' is displayed. 
 *
 * @b Type: @c BROADCAST : all applications are polled 
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int is_state                   (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief In this function, Manager ask if application can be deleted        
 *
 * @b Activation: called upon reception of a PSS message from the COM0 port.  
 *
 * @b Type: @c SELECTING : only the application that can be deleted is called 
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : S_IDENT_LOG structure
 * @param out : S_ACTIONOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int is_suppr_pg                (NO_SEGMENT no, S_IDENT_LOG *in,           S_ACTIONOUT *out);


/*! @brief This function allows to signal to the Manager that application needs to execute long or short periodical treatments
 *
 * @b Activation: periodically called  (every minute when Manager is idle)
 *
 * @b Type: @c BROADCAST: all applications are polled
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int is_time_function           (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief This function captures the keys by application. 
 *
 * @b Activation: called each time a key is pressed when Manager is idle.
 *
 * @b Type: depends off custom parameter "020610 KEYBOARD_EVENT"
 * - @c BROADCAST: SDK5.8 and lower, old management with [020610]=1
 *                 all applications are polled
 * - @c SELECTING: SDK6.0 and higher, new management (default) with [020610]=1
 *                 Check if there is a conflict between application
 *                 Example with a conflict
 *                   Soft1   keyin '5' keyout '5'     |
 *                   Soft2   keyin '5' keyout  0      |--> Conflict because Soft2 want to overload key '5' with 0 and
 *                   Soft3   keyin '5' keyout  T_ANN  |    Soft2 want to overload key '5' with T_ANN so key is not overloaded
 * 
 *                 Example with no conflict
 *                   Soft1   keyin '5' keyout '5'     |
 *                   Soft2   keyin '5' keyout  0      |--> No Conflict because only one application (Soft2) want to overload key '5' with 0
 *                   Soft3   keyin '5' keyout '5'     | 
 *
 * @b Environment: 
 * -  All peripherals are closed
 * -  No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : S_KEY structure
 * @param out : S_KEY structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @include etat_Sample_05.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int keyboard_event             (NO_SEGMENT no, S_KEY *in,                 S_KEY *out);


/*! @brief This function informs an application that a message has been received in the Manager mailbox.
 *
 * @b Activation: called when an interface task ( Manager embedded user task ) sends a message to one particular application.
 *
 * @b Type: 
 * - @c SELECTING : if the destination address is an application, this one will be called upon message_received 
 * - @c BROADCAST: if the destination address is a broadcasting address, all applications will be called upon message_received.
 *
 * @b Environment: 
 * - All peripherals are closed
 * - No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : S_MESSAGE_IAM structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int message_received           (NO_SEGMENT no, S_MESSAGE_IAM *in,         void *out);


/*! @brief This function is used to process the answer to an incoming call, only one application can implement this service. 
 *
 * @b Activation: called when Manager (when idle) detects an event on the modem peripheral ( such as RING message  indicator )
 *
 * @b Type:  @c POLLING : Manager stop polling when an application returns STOP
 *
 * @b Environment: 
 * - All peripherals are closed except the modem 
 * - No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : S_EVENTIN structure
 * @param out : S_EVENTOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int modem_event                (NO_SEGMENT no, S_EVENTIN *in,             S_EVENTOUT *out);


/*! @brief In this function, Manager gives to the applications its modified parameters
 *
 * @b Activation: after parameters changing ( initialisation done by operator, parameters update routine ) 
 *
 * @b Type:  @c BROADCAST: all applications are polled  
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : S_MODIF_P structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int modif_param                (NO_SEGMENT no, S_MODIF_P *in,             void *out);


/*! @brief This function allows applications to execute their own functions via menus. 
 *
 * @b Activation: called when the operator has selected the application following the F key activation\n
 * @note Use the following prototype for applications managing more than one application name
 (development of Incendo for instance):\n
 * extern int more_function (NO_SEGMENT no, S_ETATOUT *in, void *out);\n
 * The struct S_ETATOUT allows to know the name selected by the user after pressing key "F".
 *
 * @b Type:  @c SELECTING : only one application is called, the one that has been selected.
 *
 * @b Environment: 
 * - All peripherals are closed
 * - No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int more_function              (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function launches the PSS message processing 
 *
 * @b Activation: called upon reception of a PSS message on the COM port that has been accepted by this application 
 *
 * @b Type:  @c SELECTING : only application that has accepted the message on IS_ORDER is called
 *
 * @b Environment: All peripherals are closed except the COM port 
 * @param no  : application rank
 * @param in  : S_MESSAGE structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int order                      (NO_SEGMENT no, S_MESSAGE *in,             void *out);


/*! @brief This function is used to process Credit and Cancel transaction launched by the Manager on non EMV card. 
 *
 * @b Activation: strike on key F then Cancel or Credit then amount entry then waits for card introduction then selection of the application done by the operator
 *
 * @b Type:  @c SELECTING : only the selected application is called. 
 *
 * @b Environment: 
 * - All peripherals are closed except CAM0 
 * - card in CAM0 reader and powered on 
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int select_function            (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief This function is used to process Credit and Cancel transaction launched by the Manager on EMV card. 
 *
 * @b Activation: strike on key F then Cancel or Credit then amount entry then waits for card introduction then selection of the application done by the operator
 *
 * @b Type:  @c SELECTING : only the selected application is called. 
 *
 * @b Environment: 
 * - All peripherals are closed except CAM0 
 * - card in CAM0 reader and powered on 
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int select_function_emv        (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief service_boot entry point
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int service_boot               (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function allows applications to print their own state receipt ( application name, loadable filename, version, checksum)
 *
 * @b Activation: called when the operator has selected the menu: Consultation> State 
 *
 * @b Type:  @c BROADCAST: all applications are polled
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int state                      (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function allows applications to execute their own periodical processes    
 *
 * @b Activation: called periodically ( every minute ) 
 *
 * @b Type:  @c BROADCAST: all applications are polled 
 *
 * @b Environment: 
 * - All peripherals are closed for long process ( see #is_time_function )
 * - All peripherals are closed except keyboard and display for short process ( see #is_time_function )
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int time_function              (NO_SEGMENT no, void *in,                  void *out);


/*! @brief TIME_FUNCTION_CHAINE entry point
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int time_function_chaine       (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function allows applications to manage the final step of application selection.    
 *
 * @b Activation: called after the candidate list is built, to select one application in the list.
 *
 * @b Type:  @c SELECTING : only one application is called.
 *
 * @b Environment: All peripherals are closed except CAM0 reader, and chip card is already powered on.
 * @param no  : application rank
 * @param in  : S_SELECT_AID structure
 * @param out : S_AID_OUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int select_aid                 (NO_SEGMENT no, S_SELECT_AID *in,          S_AID_OUT *out);


/*! @brief This function is used to process specific fallback (chip to stripe) instead of EMV standard fallback
 *
 * @b Activation: when EMV power on fails (mute card)
 *
 * @b Type:  @c when EMV power on fails (mute card)
 *
 * @b Environment: 
 * - All peripherals are closed 
 * - No card in CAM0 reader
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int fall_back                  (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief This function informs the manager that the application is licensed or not
 *
 * @b Activation: called at Manager start-up if a new application (or new release has been loaded)- @b Future @b use
 *
 * @b Type:  @c BROADCAST : all applications are polled
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int is_licenced                (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief This function processes a magnetic stripe 
 *
 * @b Activation: called when a magnetic stripe is swiped ( ISO2 or ISO1+ ISO2 or ISO3+ISO2 ) 
   and a problem is detected on ISO2 track (LRC,PARITY, LUHN(*) , SEPARATOR, Numericity, ...).
 *
 * (*) : Luhn default may be detected in case of separator 'D' missing.
 *
 * @b Type:  @c POLLING : Manager stop polling when an application returns STOP
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : S_TRACKSTREAM structure
 * @param out : S_TRANSIN structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int track_stream               (NO_SEGMENT no, S_TRACKSTREAM *in,         S_TRANSIN *out);


/*! @brief This function allows applications to manage the final step of application selection.
 *
 *	To be used instead of SELECT_AID when application needs more information about EMV selection.   
 *
 * @b Activation: 
 * -	called after the candidate list is built, to select one application in the list.
 * -	If SELECT_AID_EXTENDED is defined in one application, SELECT_AID is not activated
 *
 * @b Type:  @c SELECTING : only one application is called.
 *
 * @b Environment: All peripherals are closed except CAM0 reader, and chip card is already powered on.
 * @param no  : application rank
 * @param in  : S_SELECT_AID_EXTENDED structure
 * @param out : S_AID_OUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int select_aid_extended        (NO_SEGMENT no, S_SELECT_AID_EXTENDED *in, S_AID_OUT *out);


/*! @brief This function allows an application to manage the card removal.
 *
 * If the card is still in the reader after the application processing, the Telium manager will ask for the card removal
 *
 * @b Activation: after the end of transaction after debit_OVER
 *
 * @b Type:  @c SELECTING : only one application is called, the one that has processed the debit
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note
 * - 	Application is called even if the card has already been removed
 * -	DEBIT_OVER, CARD_REMOVAL is not called if the field rc_payment (in DEBIT_EMV response) takes the 'PAY_OTHER_AID' value.
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int card_removal               (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function allows an application to manage the card removal after cash flow transaction.
 *
 * If the card is still in the reader after the application processing, the Telium manager will ask for the card removal
 *
 * @b Activation: after the end of transaction after debit_OVER
 *
 * @b Type:  @c SELECTING : only one application is called, the one that has processed the debit
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note
 * - 	Application is called even if the card has already been removed
 * - 	card reader is opened
 * -	DEBIT_OVER, CARD_REMOVAL is not called if the field rc_payment (in DEBIT_EMV response) takes the 'PAY_OTHER_AID' value.
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int cash_card_removal               (NO_SEGMENT no, void *in,                  void *out);

/*! @brief This function informs applications that card has been removed 
 *
 * @b Activation: When card is removed
 *
 * @b Type:  @c BROADCAST: all applications are called
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int card_outside               (NO_SEGMENT no, S_TRANSIN *in,             void *out);


/*! @brief This function processes a contact less payment.
 *
 * @b Activation: called when F2 key is pressed after amount keying
 *
 * @b Type:  @c BROADCAST: all applications are called
 *
 * @b Environment: All peripherals are closed except CAM0 reader 
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int debit_tpass                (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief This function asks application to:
 *
 * -	define its spefic communication layout (MPE or MPA) (masque)
 * -	define its type : banking application or not  (type)
 * - 	activate CLESS detection in IDLE state (support)
 *
 * @b Activation: called on InitDLLCB2A . If the caller is linked to DLL CB2A (French communication layout)
 *
 * @b Type:  @c BROADCAST: all applications are called
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_SPECIFIC_CONTEXT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @note
 * -	Only CLESS_SUPPORT_MASK is treated to activate CLESS selection in IDLE state and ContactLESS presence must be set to 'YES'
 * -	If an application does not use this entry point, it is asumed that the application uses MPE communication layout with no CLESS selection in IDLE state and is a banking application.
 * -	If an application set cam field to CAM2_MASK, CAM2 is also used for application selection 
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int give_your_specific_context (NO_SEGMENT no, void *in,                  S_SPECIFIC_CONTEXT *out);


/*! @brief APPEL_TELECOLLECTE entry point
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int appel_telecollecte         (NO_SEGMENT no, void *in,                  S_ETATOUT *out);


/*! @brief This function asks if application want to process the CLESS card when it is activated. This is dedicated to CLESS card specific processing.
 *
 * @b Activation: 
 * -	Once a CLESS card is detected and activated 
 * -	After amount entry and once a CLESS card is detected and activated
 *
 * @b Type:  @c BROADCAST: all applications from this domain are polled
 *
 * @b Environment: 
 * -	All peripherals are closed 
 * -	CLESS card is activated
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_ETATOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP  
 *
 * @note
 * -	If only one application wants to process the card, the manager then calls CLESS_INSIDE entry point.
 * -	If more than one application wants to process the card, the manager stops its selection process and asks for card removal.
 * -	If no application wants to process the card, the manager goes on with the selection process.
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int cless_is_specific          (NO_SEGMENT no, S_TRANSIN *in,             S_ETATOUT *out);


/*! @brief This function asks an application to process a CLESS 
 *
 * @b Activation: when an application want to process a CLESS in transparent mode
 *
 * @b Type:  @c POLLING : Manager stops when the first application returns STOP
 *
 * @b Environment: 
 * -	All peripherals are closed 
 * -	CLESS card is activated
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int cless_inside               (NO_SEGMENT no, S_TRANSIN *in,             S_TRANSOUT *out);


/*! @brief MAINT_INIT entry point
 *
 * @b Activation: Called at the end of maintenance initialization (YELLOW+RED key)
 *
 * @b Type:  @c BROADCAST : all applications of HEALTH are polled
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int maint_init                 (NO_SEGMENT no, void *in,                  void *out);

/*! @brief MAINT_PRINT entry point
 *
 * @b Activation: Called at the end of maintenance initialization (YELLOW+RED key)
 *
 * @b Type:  @c BROADCAST : all applications of HEALTH are polled
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int maint_print                (NO_SEGMENT no, void *in,                  void *out);

/*! @brief This function is used to get the currencies supported by the application 
 *
 * @b Activation: called when currency table is updated by the Manager ( on reset, end of more_function and time_function services )
 *
 * @b Type:  @c BROADCAST : all applications are polled
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_MONEYOUT_EXTENDED structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int give_money_extended        (NO_SEGMENT no, void *in,                  S_MONEYOUT_EXTENDED *out);


/*! @brief PRINTER_IDLE_STATUS entry point
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int printer_idle_status        (NO_SEGMENT no, void *in,                  void *out);


/*! @brief PINPAD_IDLE_STATUS entry point
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int pinpad_idle_status         (NO_SEGMENT no, void *in,                  void *out);


/*! @brief CLESS_IDLE_STATUS entry point
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int cless_idle_status          (NO_SEGMENT no, void *in,                  void *out);


/*! @brief This function asks application to:
 *
 * -	Define peripherals accepted by the application in selection (CAM0,SWIPE2 etc.)
 * -	Inhibit some keyboard function
 *
 * @b Activation: At the beginning of idle state
 *
 * @b Type:  @c BROADCAST : all payment applications are polled
 *
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_STATEOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP
 *
 * @note
 * -	Application is called in selection application only for supported support 
 * -	If an application inhibit a traitment (money selection for exemple), the traitment is inhibited for all applications
 * -	Entry point concerned by mask field are: IS_FOR_YOU_BEFORE,IS_FOR_YOU_AFTER, GIVE_AID,IS_CARD_EMV_FOR_YOU,IS_CARD_SPECIFIC,CARD_INSIDE)
 *
 *  @par Example:

 * @include etat_Sample_03.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int get_idle_state_parameter   (NO_SEGMENT no, void *in,                  S_STATEOUT *out);


/*! @brief This function asks application to :
 *
 * -	define peripherals accepted by the application in selection (CAM0,SWIPE2 etc.)
 * -	inhibit some keyboard function
 *
 * @b Activation: At the beginning of waiting payment support after amount entry.
 *
 * @b Type:  @c BROADCAST: all payment applications are polled  
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_STATEOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/   
extern int get_amount_state_parameter (NO_SEGMENT no, S_TRANSIN *in,             S_STATEOUT *out);


/*! @brief This function allows applications to manage the cardholder final selection
 *
 * @b Activation: called after an AID or an application has been selected.
 *
 * @b Type:  @c SELECTING : only one application is called.
 *
 * @b Environment: All peripherals are closed except CAM0 reader, and chip card is already powered on.
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_SELECT_CARDHOLDER structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/  
extern int select_card_holder         (NO_SEGMENT no, S_TRANSIN *in,             S_SELECT_CARDHOLDER *out);


/*! @brief This function allows applications to manage the MERCHANT final selection   
 *
 * @b Activation: called after cardholder selection.
 *
 * @b Type:  @c SELECTING : only one application is called.
 *
 * @b Environment: All peripherals are closed except CAM0 reader, and chip card is already powered on.
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : S_SELECT_MERCHANT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 *  @note
 * -	The number of merchant selected is put into appvalue of S_SELECT_MERCHANT structure.
 * -	To signal to the manager that the selection is aborted, put (cardappnumber+1) into appvalue of S_SELECT_MERCHANT structure
 *
 *  @par Example:
 *
 *	A sample of implementation of SELECT_MERCHANT entry point
 *
 *	Print current selection and choose on display the merchant.
 *

 * @include etat_Sample_04.c
 *
 * @link KSFAM_M2OS Back to top @endlink
**/    
extern int select_merchant            (NO_SEGMENT no, S_TRANSIN *in,             S_SELECT_MERCHANT *out);



/*! @brief This function allows applications to know that a transaction is started
 *
 * @b Activation: called before is_card_specific
 *
 * @b Type:  @c ALL_DIFFUSION 
 *
 * @b Environment: All peripherals are closed except CAM0 reader
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out : NULL pointer
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/
extern int start_of_transaction      (NO_SEGMENT no, S_TRANSIN *in,             void *out);


/*! @brief This function allows applications to know that a transaction is started
 *
 * @b Activation: called before the return in the idle state manager
 *
 * @b Type:  @c ALL_DIFFUSION 
 *
 * @b Environment: All peripherals are closed 
 * @param no  : application rank
 * @param in  : S_TRANSIN structure
 * @param out  : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/
extern int end_of_transaction        (NO_SEGMENT no, S_TRANSIN *in,                  S_TRANSOUT *out);


/*! @brief This function allows applications to start a transaction with DEBIT_IAM_REQUEST
 *
 * @b Activation: called when an application send DEBIT_IAM_REQUEST message to manager
 * An application send a DEBIT_IAM_REQUEST message to the manager
 * {
 *   char             str_message[1024]; // Data
 *   S_MESSAGE_IAM    message;           // IAM message
 *   unsigned short   sender;            // Sender
 *   unsigned short   receiver;          // Receiver
 *   unsigned short   type_message;      // Type = DEBIT_IAM_REQUEST
 *   unsigned short   type_appli;        // My application type
 *     
 *   receiver      = (TaskApplication*256) + MANAGER_TYPE;
 *   sender        = MANAGER_TYPE;type
 *   type_message  = DEBIT_IAM_REQUEST;
 *   sprintf((char *)str_message,
 *           "App %04x -> App %04x",Get_TypeCode(noappli),type_appli);
 *   // Send message
 *   message.receiver = receiver; 
 *   message.sender   = sender;
 *   message.type     = type_message;
 *   message.length   = strlen(str_message);
 *   memcpy(message.value,
 *         (unsigned char *)str_message,message.length); 
 *   Send_Message( &message );
 * }
 *
 * The manager receive the message and call DEBIT_IAM entry point
 * 
 * typedef struct
 * {
 *    S_TRANSIN     transin;
 *    S_MESSAGE_IAM message;
 * } S_TRANSIN_IAM;
 * 
 * "transin" field contain transaction characteristics (amount,currency,...)
 * "message" field contain IAM message sending by the application.
 * 
 * Works :
 *   1) In idle state.
 *   2) After amount entry.
 *   3) With cash connection.
 *   4) for Cash,Credit,Cancel,Credit transaction
 *
 * @b Type:  @c STOP_DIFFUSION 
 *
 * @b Environment: 
 * -  All peripherals are closed except CAM0 reader 
 *
 * @param no  : application rank
 * @param in  : S_TRANSIN_IAM structure
 * @param out  : S_TRANSOUT structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/
extern int debit_iam        (NO_SEGMENT no, S_TRANSIN_IAM *in,                  S_TRANSOUT *out);

/*! @brief This function is used to get application name ( 12 ASCII + 0 characters ) to be displayed at operator side
 *
 * @b Activation: called when F key is pressed
 * @b Limitation to NUMBER_OF_APPLI applications
 *
 * @b Type: 
 * -  @c BROADCAST : all applications are polled or;
 * -  @c SELECTING : only few applications are to be called (in case of application selection)
 *
 * @b Environment: All peripherals are closed
 * @param no  : application rank
 * @param in  : NULL pointer
 * @param out : S_ETATOUT_EXTENDED structure
 * @return 
 * -  FCT_OK
 * -  STOP   
 *
 * @link KSFAM_M2OS Back to top @endlink
**/     
extern int is_name_extented(NO_SEGMENT no,void *in,S_ETATOUT_EXTENDED *out);

#endif
/*! @} **/

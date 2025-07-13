//****************************************************************************
//       INGENICO                                INGEDEV 7
//============================================================================
//       FILE  MAIN.C                               (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-June-2012     Kassovic
//  Last modified : 13-June-2012     Kassovic
//  Module : CASHREG
//
//  Purpose :
//  Each time Manager calls an application, it generates only one service
//  call that reaches your application main with the corresponding service
//  number.
//
//  List of routines in file :
//      Main : Services management.
//
//  File history :
//  130612-BK : File created
//
//****************************************************************************

/****************************************************************************/
/*      INCLUDES                                                            */
/****************************************************************************/
#include "SDK30.H"

/****************************************************************************/
/*      EXTERN                                                              */
/****************************************************************************/
	/* */

/****************************************************************************/
/*      PRIVATE CONSTANTS                                                   */
/****************************************************************************/
#define SAP_TRACE_0  0xF000        // Initialize tracing with trace tool

#ifdef _TRACE_REMOTE_              // Initialize tracing with remote debugger
	#define TRACE_DEBUG(BUF) {SystemFioctl(SYS_FIOCTL_DEBUG_TRACE, (char*) BUF);}
#else
	#define TRACE_DEBUG(BUF)
#endif

/****************************************************************************/
/*      PRIVATE TYPES                                                       */
/****************************************************************************/
    /* */

/****************************************************************************/
/*      PRIVATE DATA                                                        */
/****************************************************************************/
const char *tzMsgTrace[] =
{
	"Cashreg give_your_domain\n",
	"Cashreg after_reset\n",
	"Cashreg is_name\n",
	"Cashreg is_state\n",
	"Cashreg more_function\n",
	"Cashreg get_idle_state_parameter\n",
	"Cashreg state\n",
	"Cashreg is_delete\n",
	"Cashreg message_received\n"
};

// ***************************************************************************
//                  int Main (doubleword size, StructPt *data)
/** Application has to call ServiceRegister for each service with a same 
 *  address Main and using predefined service number.
 * \param    size (I-) 
 *    - data size.
 * \param    data (I-)
 *    - contains data needed between the Manager and application regarding services.
 * \return                                           
 *  service call status.
 * \header sdk30.h etat.h
 * \source main.c 
*/
// ***************************************************************************
int Main(doubleword size, StructPt *data)
{
	// Local variables *
    // *****************
	NO_SEGMENT No;
	int ret;
	
	// Service call management
    // ***********************
	No = ApplicationGetCurrent();         // Return the application number
		
	switch(data->service)
	{
	case GIVE_YOUR_DOMAIN :               // Return application domain to Manager
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[0]), tzMsgTrace[0]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[0]);                                                // Trace with remote debugger
		ret = give_your_domain(No, NULL, &data->Param.GiveYourType.param_out);
        break;
        
	case AFTER_RESET :                    // Activated on each terminal reset
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[1]), tzMsgTrace[1]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[1]);                                                // Trace with remote debugger
		ret = after_reset(No, NULL, &data->Param.AfterReset.param_out);
        break;

	case IS_NAME :                        // Activated when Manager wants to get application name
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[2]), tzMsgTrace[2]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[2]);                                                // Trace with remote debugger
		ret = is_name(No, NULL, &data->Param.IsName.param_out);
        break;

	case IS_STATE :                       // Activated at boot and every minute to check if application initialised
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[3]), tzMsgTrace[3]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[3]);                                                // Trace with remote debugger
		ret = is_state(No, NULL, &data->Param.IsState.param_out);
        break;

	case MORE_FUNCTION :                  // Activated on "F" key and dedicated to navigation menus
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[4]), tzMsgTrace[4]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[4]);                                                // Trace with remote debugger
		ret = more_function(No, NULL, NULL);
        break;

	case GET_IDLE_STATE_PARAMETER :       // Gives manager parameters to customize idle state
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[5]), tzMsgTrace[5]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[5]);                                                // Trace with remote debugger
		ret = get_idle_state_parameter(No, NULL, &data->Param.GetIdleStateParameter.param_out);
		break;

	case STATE :                          // Activated on "F" key: Consultation->State, to print terminal content receipt
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[6]), tzMsgTrace[6]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[6]);                                                // Trace with remote debugger
		ret = state(No, NULL, NULL);
        break;

	case IS_DELETE :                      // Activated on "F" key: Deletion, Conditions for application deletion?
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[7]), tzMsgTrace[7]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[7]);                                                // Trace with remote debugger
        ret = is_delete(No, NULL, &data->Param.IsDelete.param_out);
        break;

	case MESSAGE_RECEIVED:                // Activated each time Manager received a message in its own mailbox for this application
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[8]), tzMsgTrace[8]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[8]);                                                // Trace with remote debugger
		ret = message_received(No, &data->Param.MessageReceived.param_in, NULL);
        break;

	case GIVE_YOUR_SPECIFIC_CONTEXT :     // Return specific context to Manager
	case IDLE_MESSAGE :                   // Activated when Manager goes back to idle, to display its message
	case KEYBOARD_EVENT :                 // Activated when key is pressed
	case CONSULT :                        // Activated on "F" key: Consultation->Transactions, to print transaction totals receipt 
	case MCALL :                          // Activated on "F" key: Consultation->Call->Planning of Call, to print host call planning receipt
	case IS_TIME_FUNCTION :               // Activated every minute, do you need the peripherals at the next call of time_function()?
	case TIME_FUNCTION :                  // Activated every minute, to execute automatic periodic functions 
	case IS_CHANGE_INIT :                 // Activated on "F" key: Initialization->Parameters->List, Conditions for changing Manager parameters?
	case MODIF_PARAM :                    // Activated on "F" key: Initialization->Parameters->List, Manager reports parameters changed.
	case IS_EVOL_PG :                     // Activated on "F" key: Evolution->Load->Local or RemoteLoad, Conditions for application downloading?
	case FILE_RECEIVED :                  // Activated each time Manager received a file from a "parameters" downloading session

	case TIME_FUNCTION_CHAINE :           // French Bank Domain 
	case GIVE_INFOS_CX:		              // French Bank Domain 
	case FALL_BACK: 
	case DEBIT_OVER:
	case AUTO_OVER:
	case IS_ORDER:			              // French Health Care Domain 
	case ORDER:				              // French Health Care Domain 
	case IS_SUPPR_PG:		              // French Health Care Domain 
	case IS_INSTALL_PG:		              // French Health Care Domain 
	case GET_ORDER:			              // French Health Care Domain 
	case IS_LIBELLE:		              // French Health Care Domain 
	case EVOL_CONFIG:		              // French Bank Domain 
	case GIVE_MONEY:		              // French Bank Domain 
	case COM_EVENT:
	case MODEM_EVENT:
	case GIVE_INTERFACE: 
	case IS_BIN_CB:			              // French Bank Domain
	case IS_CARD_SPECIFIC:                // Activated when card inserted card swiped or manually entry, do you want to process the card?
    case CARD_INSIDE:		              // Activated when the card is specific, the application process the card in transparent mode
	case IS_FOR_YOU_BEFORE:               // Activated when chip card inserted, ask application to recognize the chip card in order to a candidate
	case IS_FOR_YOU_AFTER :
	case DEBIT_NON_EMV :
	case SELECT_FUNCTION:
	case GIVE_AID:
	case IS_CARD_EMV_FOR_YOU:
	case DEBIT_EMV:
	case SELECT_FUNCTION_EMV:	          // French Bank Domain
	case CLESS_IS_SPECIFIC:              // Activated after amount entry and once a CLESS card is detected and activated, do you want to process the card?
	case CLESS_INSIDE:                   // Activated when the CLESS card is specific, the application process the CLESS card in transparent mode
	case CLESS_GIVE_INFO:                // Setting card detection and selection parameters (implicit selection)
	case CLESS_IS_FOR_YOU:               // Manage specific cards (implicit selection)
	case CLESS_DEBIT:                    // Perform a transaction with other method than AID (implicit selection)
	case CLESS_END:                      // Process when transaction has been completed (implicit selection)
	default:
        break;
	}

	return FCT_OK;
}


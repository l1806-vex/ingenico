//****************************************************************************
//       INGENICO                                INGEDEV 7
//============================================================================
//       FILE  MAIN.C                             (Copyright INGENICO 2012)
//============================================================================
//  Created :       17-July-2012     Kassovic
//  Last modified : 17-July-2012     Kassovic
//  Module : TRAINING
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
//  071712-BK : File created
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
	"Training give_your_domain\n",
	"Training give_your_specific_context\n",
	"Training after_reset\n",
	"Training is_name\n",
	"Training is_state\n",
	"Training idle_message\n",
	"Training more_function\n",
	"Training keyboard_event\n",
	"Training get_idle_state_parameter\n",
	"Training give_money_extended\n",
	"Training state\n",
	"Training consult\n",
	"Training mcall\n",
	"Training is_time_function\n",
	"Training time_function\n",
	"Training is_change_init\n",
	"Training modif_param\n",
	"Training is_evol_pg\n",
	"Training is_delete\n",
	"Training file_received\n",
	"Training message_received\n",
	"Training is_card_specific\n",
	"Training card_inside\n",
	"Training is_for_you_before\n",
	"Training is_for_you_after\n",
	"Training debit_none_emv\n",
	"Training select_function\n"
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
        
	case GIVE_YOUR_SPECIFIC_CONTEXT :     // Return specific context to Manager
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[1]), tzMsgTrace[1]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[1]);                                                // Trace with remote debugger
		ret = give_your_specific_context(No, NULL, &data->Param.GiveYourSpecificContext.param_out);
		break;

	case AFTER_RESET :                    // Activated on each terminal reset
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[2]), tzMsgTrace[2]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[2]);                                                // Trace with remote debugger
		ret = after_reset(No, NULL, &data->Param.AfterReset.param_out);
        break;

	case IS_NAME :                        // Activated when Manager wants to get application name
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[3]), tzMsgTrace[3]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[3]);                                                // Trace with remote debugger
		ret = is_name(No, NULL, &data->Param.IsName.param_out);
        break;

	case IS_STATE :                       // Activated at boot and every minute to check if application initialized
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[4]), tzMsgTrace[4]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[4]);                                                // Trace with remote debugger
		ret = is_state(No, NULL, &data->Param.IsState.param_out);
        break;

	case IDLE_MESSAGE :                   // Activated when Manager goes back to idle, to display its message
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[5]), tzMsgTrace[5]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[5]);                                                // Trace with remote debugger
        idle_message(No, NULL, NULL);
        break;

	case MORE_FUNCTION :                  // Activated on "F" key and dedicated to navigation menus
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[6]), tzMsgTrace[6]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[6]);                                                // Trace with remote debugger
		ret = more_function(No, NULL, NULL);
        break;

	case KEYBOARD_EVENT :                 // Activated when key is pressed
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[7]), tzMsgTrace[7]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[7]);                                                // Trace with remote debugger
        ret = keyboard_event(No, &data->Param.KeyboardEvent.param_in, &data->Param.KeyboardEvent.param_out);
		break;

	case GET_IDLE_STATE_PARAMETER :       // Gives manager parameters to customize idle state
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[8]), tzMsgTrace[8]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[8]);                                                // Trace with remote debugger
		ret = get_idle_state_parameter(No, NULL, &data->Param.GetIdleStateParameter.param_out);
		break;

	case GIVE_MONEY_EXTENDED :            // Get the currencies supported by the application
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[9]), tzMsgTrace[9]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[9]);                                                // Trace with remote debugger
		ret = give_money_extended(No, NULL, &data->Param.GiveMoneyExtended.param_out);
		break;

	case STATE :                          // Activated on "F" key: Consultation->State, to print terminal content receipt
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[10]), tzMsgTrace[10]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[10]);                                                // Trace with remote debugger
		ret = state(No, NULL, NULL);
        break;

	case CONSULT :                        // Activated on "F" key: Consultation->Transactions, to print transaction totals receipt 
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[11]), tzMsgTrace[11]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[11]);                                                 // Trace with remote debugger
		ret = consult(No, NULL, NULL);
        break;

	case MCALL :                          // Activated on "F" key: Consultation->Call->Planning of Call, to print host call planning receipt
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[12]), tzMsgTrace[12]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[12]);                                                 // Trace with remote debugger
		ret = mcall(No, NULL, NULL);
        break;

	case IS_TIME_FUNCTION :               // Activated every minute, do you need the peripherals at the next call of time_function()?
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[13]), tzMsgTrace[13]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[13]);                                                 // Trace with remote debugger
		ret = is_time_function(No, NULL, &data->Param.IsTimeFunction.param_out); 
		break;

	case TIME_FUNCTION :                  // Activated every minute, to execute automatic periodic functions 
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[14]), tzMsgTrace[14]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[14]);                                                 // Trace with remote debugger
        ret = time_function(No, NULL, NULL); 
		break;

	case IS_CHANGE_INIT :                 // Activated on "F" key: Initialization->Parameters->List, Conditions for changing Manager parameters?
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[15]), tzMsgTrace[15]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[15]);                                                 // Trace with remote debugger
        ret = is_change_init(No,NULL,&data->Param.IsChangeInit.param_out);
        break;

	case MODIF_PARAM :                    // Activated on "F" key: Initialization->Parameters->List, Manager reports parameters changed.
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[16]), tzMsgTrace[16]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[16]);                                                 // Trace with remote debugger
        ret = modif_param(No, &data->Param.ModifParam.param_in, NULL);
		break;

	case IS_EVOL_PG :                     // Activated on "F" key: Evolution->Load->Local or RemoteLoad, Conditions for application downloading?
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[17]), tzMsgTrace[17]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[17]);                                                 // Trace with remote debugger
		ret = is_evol_pg(No,NULL,&data->Param.IsEvolPg.param_out);
        break;

	case IS_DELETE :                      // Activated on "F" key: Deletion, Conditions for application deletion? 
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[18]), tzMsgTrace[18]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[18]);                                                 // Trace with remote debugger
        ret = is_delete(No, NULL, &data->Param.IsDelete.param_out);
        break;

	case FILE_RECEIVED :                  // Activated each time Manager received a file from a "parameters" downloading session
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[19]), tzMsgTrace[19]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[19]);                                                 // Trace with remote debugger
        ret = file_received(No, &data->Param.FileReceived.param_in, NULL);
        break;

	case MESSAGE_RECEIVED:                // Activated each time Manager received a message in its own mailbox for this application
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[20]), tzMsgTrace[20]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[20]);                                                 // Trace with remote debugger
		ret = message_received(No, &data->Param.MessageReceived.param_in, NULL);
        break;

	case IS_CARD_SPECIFIC:                // Activated when card inserted card swiped or manually entry, do you want to process the card?
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[21]), tzMsgTrace[21]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[21]);                                                 // Trace with remote debugger
		ret = is_card_specific(No, &data->Param.IsCardSpecific.param_in, &data->Param.IsCardSpecific.param_out);
        break;
    
    case CARD_INSIDE:		              // Activated when the card is specific, the application process the card in transparent mode
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[22]), tzMsgTrace[22]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[22]);                                                 // Trace with remote debugger
		ret = card_inside(No, &data->Param.CardInside.param_in, &data->Param.CardInside. param_out);
        break;

	case IS_FOR_YOU_BEFORE:               // Activated when chip card inserted, ask application to recognise the chip card in order to a candidate               
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[23]), tzMsgTrace[23]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[23]);                                                 // Trace with remote debugger
		ret = is_for_you_before(No, &data->Param.IsForYouBefore.param_in, &data->Param.IsForYouBefore.param_out);
        break;

	case IS_FOR_YOU_AFTER : 
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[24]), tzMsgTrace[24]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[24]);                                                 // Trace with remote debugger
		ret = is_for_you_after(No,&data->Param.IsForYouAfter.param_in,&data->Param.IsForYouAfter.param_out);
        break;

	case DEBIT_NON_EMV :
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[25]), tzMsgTrace[25]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[25]);                                                 // Trace with remote debugger
		ret = debit_non_emv(No,&data->Param.DebitNonEmv.param_in,&data->Param.DebitNonEmv.param_out);
        break;

	case SELECT_FUNCTION:
		trace((trace_sap_id_t) SAP_TRACE_0, strlen(tzMsgTrace[26]), tzMsgTrace[26]); // Trace with trace tool
		TRACE_DEBUG(tzMsgTrace[26]);                                                 // Trace with remote debugger
		ret = select_function(No,&data->Param.SelectFunction.param_in,&data->Param.SelectFunction.param_out);
		break;

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
	case GIVE_AID:
	case IS_CARD_EMV_FOR_YOU:
	case DEBIT_EMV:
	case SELECT_FUNCTION_EMV:	          // French Bank Domain
	default:
        break;
	}

	return FCT_OK;
}


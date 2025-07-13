/***
 * Copyright (c) 2004 Sagem Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Sagem Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Sagem Monetel.
 *
 * @Title:        
 * @Description: SDK30 sample application 
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         
 */
#include "SDK30.H"
#include "etat.h"

extern int after_reset         (NO_SEGMENT, void *,        S_TRANSOUT *);

int Main(unsigned int size, StructPt *data)
{
	NO_SEGMENT No;
	int            ret;
	
	No = ApplicationGetCurrent();
	switch(data->service)
	{
	case AFTER_RESET :
		ret = after_reset(No,NULL,&data->Param.AfterReset.param_out);
        break;

	case MORE_FUNCTION :
		ret = more_function(No,NULL,NULL);
        break;

	case IS_TIME_FUNCTION :
		ret = is_time_function(No,NULL,&data->Param.IsTimeFunction.param_out); 
		break;

	case TIME_FUNCTION :
        ret = time_function(No,NULL,NULL); 
		break;

	case CONSULT :
		ret = consult(No,NULL,NULL);
        break;

	case MCALL :
		ret = mcall(No,NULL,NULL);
        break;

	case STATE :
		ret = state(No,NULL,NULL);
        break;

	case IS_NAME :
		ret = is_name(No,NULL,&data->Param.IsName.param_out);
        break;

	case IS_STATE :
		ret = is_state(No,NULL,&data->Param.IsState.param_out);
        break;

	case IS_EVOL_PG :
		ret = is_evol_pg(No,NULL,&data->Param.IsEvolPg.param_out);
        break;

	case IS_CHANGE_INIT :
        ret = is_change_init(No,NULL,&data->Param.IsChangeInit.param_out);
        break;

	case MODIF_PARAM :
        ret = modif_param(No, &data->Param.ModifParam.param_in, NULL);
		break;

	case IS_DELETE :
        ret = is_delete(No,NULL,&data->Param.IsDelete.param_out);
        break;

	case GIVE_YOUR_DOMAIN :
		ret = give_your_domain(No,NULL,&data->Param.GiveYourType.param_out);
        break;


	case DEBIT_NON_EMV :
	case FILE_RECEIVED :
    case IS_FOR_YOU_AFTER : 
	case IDLE_MESSAGE :
	case TIME_FUNCTION_CHAINE : // French Bank Domain 
	case GIVE_INFOS_CX:		// French Bank Domain 
	case FALL_BACK: 
	case DEBIT_OVER:
	case AUTO_OVER:
	case IS_ORDER:			// French Health Care Domain 
	case ORDER:				// French Health Care Domain 
	case IS_SUPPR_PG:		// French Health Care Domain 
	case IS_INSTALL_PG:		// French Health Care Domain 
	case GET_ORDER:			// French Health Care Domain 
	case IS_LIBELLE:		// French Health Care Domain 
	case EVOL_CONFIG:		// French Bank Domain 
	case GIVE_MONEY:		// French Bank Domain 
	case COM_EVENT:
	case MODEM_EVENT:
	case MESSAGE_RECEIVED:
	case CARD_INSIDE:		// French Health Care Domain
	case GIVE_INTERFACE: 
	case IS_BIN_CB:			// French Bank Domain
	case IS_CARD_SPECIFIC: // French Health Care Domain
	case GIVE_AID:
	case IS_FOR_YOU_BEFORE : 
	case IS_CARD_EMV_FOR_YOU:
	case DEBIT_EMV:
	case SELECT_FUNCTION:		// French Bank Domain
	case SELECT_FUNCTION_EMV:	// French Bank Domain
	default:
        break;
	}

	return FCT_OK;
}


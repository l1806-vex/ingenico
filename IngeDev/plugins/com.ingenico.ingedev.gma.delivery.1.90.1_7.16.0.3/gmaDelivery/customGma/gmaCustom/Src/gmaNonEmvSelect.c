
/**
 * @file NoneEmvSelect.c
 *
 * None Emv application selection.
 */

#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "gmaDefines.h"
#include "gmaCustomDefines.h"

#include "appInit.h"
#include "gmaMsg.h"
#include "gmaMsgSup.h"
#include "gmaMsgCon.h"
#include "gmaAppMsg.h"

#include "SmcSupport.h"
#include "gmaGenCustom.h"



/**
 * Process the smart card that was inserted.
 *
 * Send a query to all application to see which application
 * can treat this transaction, and then send the transaction
 * to this application
 */
int16 gmaNoneEmvSelectApplication (gmaSmcAtrResult_t* smcAtr)
{
	amgMsg_t defaultMsg;
	amgMsg_t responseMsg;
	uint8*   answer;
	int16    appSel;
	uint16   appID; 
	uint8    logicalID;
	
	gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION_QUERY);
	gmaMsgAddTransType(0xFF, GMA_TRANS_SMART_CARD);
	if(    ((smcAtr->status == SMC_BAD_TS) && (smcAtr->length == 1))
	    || (smcAtr->status == SMC_ATR_NOT_19200) )
	{
      gmaMsgsAddTransSmartCard(GMA_SMART_CARD_SYNCHRONOUS, GMA_SELECTION_NOT_DONE);
	}
	// TGO 2009 Sep 17 removed, see tracker #932
//   else
//   {
//      gmaMsgsAddTransSmartCard(GMA_SMART_CARD_ASYNCHRONOUS, GMA_SELECTION_NOT_DONE);
//   }
	
 	gmaMsgsAddTransSmcAtr(smcAtr->data, smcAtr->length);
	gmaMsgEndEncode();

	gmaAppMsgQueryDriven (&defaultMsg, &answer);

	appSel = gmaCustomSelectApp(answer, &appID, &logicalID);

	if (appSel >= 0)    // if <0 No Application to select
	{
		gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION);
		gmaMsgAddTransType(logicalID, GMA_TRANS_SMART_CARD);
      
		if ((uint8)smcAtr->length == 0)
         gmaMsgsAddTransSmartCard(GMA_SMART_CARD_SYNCHRONOUS, GMA_SELECTION_DONE); 
      else
         gmaMsgsAddTransSmartCard(GMA_SMART_CARD_ASYNCHRONOUS, GMA_SELECTION_DONE);
       
	   gmaMsgsAddTransSmcAtr(smcAtr->data, smcAtr->length);
	   
	   gmaMsgAddSmcSelectionMode(appSel);
	   
		gmaMsgEndEncode();
		
		gmaAppMsgWakeApp(appID, logicalID, &defaultMsg, &responseMsg);
		gmaInitProcessResponse(appID, &responseMsg);
	}

	if (appSel == GMA_NO_FUNC_AVAILABLE)
	{
	    return GMA_NO_FUNC_AVAILABLE;	
	}    

	return RET_OK;
}



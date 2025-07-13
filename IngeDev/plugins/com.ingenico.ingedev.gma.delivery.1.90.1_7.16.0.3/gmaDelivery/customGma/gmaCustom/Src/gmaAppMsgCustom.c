
/** @file gmaAppMsgCustom.c
 * 
 * This file contains the function \ref gmaCustomMsgFromApp which
 *	will handle the optional structures received from applications in the amg messages.
 * 
 *	Actually the custom only treat the \ref GMA_STRUCT_EMV_AID structure.
 */

#include "unicapt.h"

#include "string.h"

#include "appList.h"
#include "gmaDefines.h"
#include "gmaGenCustom.h"
#include "gmaHmiTransfer.h"
#include "gmaCLibDefines.h"
#include "gmaMenuResource.h"
#include "gmaCusEmvSel.h"

//#define DEBUG_ON
#include "debuglib.h"

static int16 gmaAppNothing(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaMsgsProcessEmvAid(uint16 appId, gmaStructHeader_t *data);
static int16 gmaMsgsTreatTransferHmiSup(uint16 appId, gmaStructHeader_t *data);
static int16 gmaMsgsTreatMenuResource(uint16 appId, gmaStructHeader_t *data);
static int16 gmaMsgsProcessEmvAidDel(uint16 appId, gmaStructHeader_t *data);
static int16 gmaMsgsTreatBroadcast(uint16 appId, gmaStructHeader_t *data);
static int16 gmaMsgsTreatTransactionReq(uint16 appId, gmaStructHeader_t *data);

/**
 * treat the messages received from the applications
 */
int16 gmaCustomMsgFromApp(uint16 appId, gmaStructHeader_t *msg)
{
   uint16 i;

   struct 
   {
      uint32 id;
      int16 (*func)(uint16 appId, gmaStructHeader_t *msg);
   } treatAppFuncs[] = 
   {
      {GMA_STRUCT_EMV_AID, gmaMsgsProcessEmvAid},
      {GMA_STRUCT_EMV_AID_DEL, gmaMsgsProcessEmvAidDel},
      {GMA_STRUCT_TRANSFER_HMI_SUP, gmaMsgsTreatTransferHmiSup},
      {GMA_STRUCT_CUS_MENU_RESOURCE, gmaMsgsTreatMenuResource},
      {GMA_STRUCT_PG_BROADCAST, gmaMsgsTreatBroadcast},
      {GMA_STRUCT_PG_TRANSACTION_REQ, gmaMsgsTreatTransactionReq},
      {0xFFFFFFFF, gmaAppNothing}
   };

   for(i=0; treatAppFuncs[i].id != 0xFFFFFFFF; i++)
   {
      if(msg->id == treatAppFuncs[i].id)
         break;
   }
   
   return treatAppFuncs[i].func(appId, msg);
}

/**
 * Now the plug-in can send the blocked functions using the return amg message
 * too.
 */
static int16 gmaMsgsTreatBroadcast(uint16 appId, gmaStructHeader_t *data)
{
	return gmaPGTreatBroadcastMessageMain(data, 0);
}

/**
 * 
 */
static int16 gmaMsgsTreatTransactionReq(uint16 appId, gmaStructHeader_t *data)
{
	return gmaPGtreatTransactionReqMsgmain(data, 0);
}


/**
 * 
 */
static int16 gmaMsgsTreatTransferHmiSup(uint16 appId, gmaStructHeader_t *data)
{
	gmaHmiTrTreatTransferHmiSup(appId, data);
	
	return RET_OK;
}


/**
 * Delete all EMV AID
 */
static int16 gmaMsgsProcessEmvAidDel(uint16 appId, gmaStructHeader_t *data)
{
	return gmaEmvSelDelAids(appId, 0xFF);
	//return amgSelectionCriteriaDel(T_AID);
}

/**
 * EMV AIDs -- forward to PAM
 */
static int16 gmaMsgsProcessEmvAid(uint16 appId, gmaStructHeader_t *data)
{
   gmaStructEmvAid_t *aid = (gmaStructEmvAid_t *) data;
   amgAid_t amgAid;
   
   amgAid.aidAppSelIndicator = aid->aidAppSelIndicator;
   amgAid.aidLength = aid->aidLength;
   memcpy(amgAid.aidName, aid->aidName, aid->aidLength);
   amgAid.aidPriorityIndex = aid->aidPriorityIndex;
   IFDEBUG(debugPrintf(DEBUG_COM1, "gmaMsgsProcessEmvAid"));
   IFDEBUG(debugPrintf(DEBUG_COM1, "appId=%d ", appId));
   return gmaEmvSelAddAid(appId, aid->logicalID, &amgAid);
}


static int16 gmaAppNothing(uint16 appId, gmaStructHeader_t *msg)
{
	return RET_OK;
}


static int16 gmaMsgsTreatMenuResource(uint16 appId, gmaStructHeader_t *data)
{
	gmaStructCmenuResourse_t *mnuRes = (gmaStructCmenuResourse_t *) data;
	
	
	gmaMRESSetMnuResAppShowStatus(appId, mnuRes->logicalId, mnuRes->useResMenu);
	
	return RET_OK;
}

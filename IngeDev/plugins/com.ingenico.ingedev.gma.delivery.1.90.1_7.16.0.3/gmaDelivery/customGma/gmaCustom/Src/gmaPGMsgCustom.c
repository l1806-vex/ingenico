
/**
 * 
 * @file gmaPGMsgCustom.c
 *
 *
 * This file contains the function "gmaCustomMsgFromPlugIn" wich
 *	will handle the messages received from installed plug-ins using the
 * plugin queue command.
 * 
 * The structures received from the plugins that is treated in the
 * Custom are:
 *
 * - \ref GMA_STRUCT_PG_KEYBOARD_CFG
 * - \ref GMA_STRUCT_PG_MENU_ITEM
 * - \ref GMA_STRUCT_PG_EDIT_RESOURCE
 */

#include "stdlib.h"
#include "string.h"

#include "unicapt.h"

#include "gmaDefines.h"
#include "gmaHmiCustom.h"
#include "gmaGenCustom.h"
#include "applist.h"
#include "appInit.h"
#include "GmaMsg.h"
#include "gmaCustomCBs.h"
#include "gmaMsgSup.h"
#include "gmaAppMsg.h"
#include "gmaCusSync.h"
#include "gmaQueueTask.h"
#include "gmaCustomUtil.h"
#include "gmaHmiProcess.h"
#include "gmaHmiTransfer.h"
#include "gmaCLibDefines.h"
#include "gmaCusTouchScr.h"
#include "gmaMedia.h"

//#define DEBUG_ON
#include "DebugLib.h"

static int16 gmaPGAlertMessage(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGKeyboardCfg(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGNothing(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGTecFunMenuCfg(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGEditResource(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGTreatBroadcastMessage(uint16 appId, gmaStructHeader_t *msg);

static int16 gmaPGtreatTransactionReqMsg(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGtreatDisplayConfig(uint16 appId, gmaStructHeader_t *msg);

static int16 gmaPGtreatTransferHmiSup(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGtreatTransferHmiBack(uint16 appId, gmaStructHeader_t *msg);
static int16 gmaPGtreadTouchAction(uint16 appId, gmaStructHeader_t *msg);


/**
 * Treat messages received from plugin
 */
int16 gmaCustomMsgFromPlugIn(uint16 appId, gmaStructHeader_t *msg)
{
   uint16 i;

   static const struct 
   {
      uint32 id;
      int16 (*func)(uint16 appId, gmaStructHeader_t *msg);
   } treatFuncs[] = 
   {
      {GMA_STRUCT_PG_ALERT_MESSAGE,   gmaPGAlertMessage},
      {GMA_STRUCT_PG_KEYBOARD_CFG,    gmaPGKeyboardCfg},
      {GMA_STRUCT_PG_MENU_ITEM,       gmaPGTecFunMenuCfg},
      {GMA_STRUCT_PG_EDIT_RESOURCE,   gmaPGEditResource},
      {GMA_STRUCT_PG_BROADCAST,       gmaPGTreatBroadcastMessage},
      {GMA_STRUCT_PG_TRANSACTION_REQ, gmaPGtreatTransactionReqMsg},
      {GMA_STRUCT_PG_DISP_CONFIG,     gmaPGtreatDisplayConfig},
      {GMA_STRUCT_TRANSFER_HMI_SUP,   gmaPGtreatTransferHmiSup},
      {GMA_STRUCT_TRANSFER_HMI,       gmaPGtreatTransferHmiBack},
      
      {GMA_STRUCT_PG_CUS_TOUCH_ACTION, gmaPGtreadTouchAction},
      {0xFFFFFFFF,                    gmaPGNothing}
   };

   for(i=0; treatFuncs[i].id != 0xFFFFFFFF; i++)
   {
      if(msg->id == treatFuncs[i].id)
         break;
   }
   
   return treatFuncs[i].func(appId, msg);
}


struct backLight_st{
   uint8 status; //!< 0 - on || 1 - off
   uint8 rfu;
   uint16 timeOut; //!< timeout in seconds. The time the backlight remain turned on.
};

struct beepStatus_st{
   uint8 status;
};

/**
 * 
 */
static int16 gmaPGtreatDisplayConfig(uint16 appId, gmaStructHeader_t *msg)
{
   gmaStructPGDispConfig_t *str = (gmaStructPGDispConfig_t *) msg;
   
   switch(str->configItem)
   {
      case GMA_PG_DISP_CONFIG_BACKLIGHT:
      {
         uint32 timeout;
         struct backLight_st *plt = 
            (struct backLight_st *) str->configData;
         timeout = plt->timeOut * 100;
         
         gmaCustomUtilConfigBLE(plt->status, timeout);
      }
      break;
      case GMA_PG_DISP_CONFIG_BEEP:
         gmaHmiSetBeepStatus(str->configData[0]);
      break;
      
   }
   
   return RET_OK;
}

/**
 * 
 */
static int16 gmaPGTreatBroadcastMessage(uint16 appId, gmaStructHeader_t *msg)
{
	
   return gmaCtSynSendMainTask(gmaPGTreatBroadcastMessageMain, (void *) msg, GMA_QTASK_MAX_MSG_SIZE);
}

/**
 * 
 */
int16 gmaPGTreatBroadcastMessageMain(void *msgRec, uint32 param2)
{
   // Check to see if the message is to warn a Sleep mode begin or end
	gmaStructPGBroadcast_t *broad = 
      (gmaStructPGBroadcast_t *) msgRec;
   
   gmaStructPowerLevel_t *msgdata = 
      (gmaStructPowerLevel_t *)(broad->data);

   if(msgdata->header.id == GMA_STRUCT_POWER_LEVEL)
   {
      //IFDEBUG(debugPrintf(DEBUG_PRN, "indication=%d",msgdata->indication));
      switch(msgdata->indication)
      {
      case GMA_POWER_OFF:
         break;
      case GMA_POWER_LOW_BATTERY:
         // will enter in sleep mode
         
         gmaCBCancelEvents();
         gmaCBEnablePerStart(0);
         break;
      case GMA_POWER_RESTORE:
         // will go out from sleep mode
         gmaCBEnablePerStart(1);
         
         break;
      }
   }
   return RET_OK;
}

/*
 * treat the message  gmaPGAlertMessage. Not implemented yet.
 */
static int16 gmaPGAlertMessage(uint16 appId, gmaStructHeader_t *msg)
{
	return RET_OK;
}

/**
 * Treat the message \ref GMA_STRUCT_PG_MENU_ITEM.
 */
static int16 gmaPGTecFunMenuCfg(uint16 appId, gmaStructHeader_t *msg)
{
	return gmaTecFunMenuAddItem(appId, msg);
}

/**
 * treat the message \ref GMA_STRUCT_PG_KEYBOARD_CFG.
 */
static int16 gmaPGKeyboardCfg(uint16 appId, gmaStructHeader_t *msg)
{
   return gmaHmiKeyTableUpdate(appId, msg);
}

static int16 gmaPGNothing(uint16 appId, gmaStructHeader_t *msg)
{

	return RET_OK;
}

/**
 * treat the message \ref GMA_STRUCT_PG_EDIT_RESOURCE.
 */
static int16 gmaPGEditResource(uint16 appId, gmaStructHeader_t *msg)
{
   return gmaTecFunAddEditResource(appId, (gmaStructPGEditResource_t *)msg);
}

/**
 * 
 */
static int16 gmaPGtreatTransactionReqMsg(uint16 appId, gmaStructHeader_t *msg)
{
   // need to send an event to the main task. The treatment must be done there
   gmaCtSynSendMainTask(gmaPGtreatTransactionReqMsgmain,(void *)msg, GMA_QTASK_MAX_MSG_SIZE);
   return RET_OK;
}

/**
 * 
 */
static int16 gmaPGtreatTransferHmiSup(uint16 appId, gmaStructHeader_t *msg)
{
	gmaHmiTrTreatTransferHmiSup(appId, msg);
	
	return RET_OK;
}

/**
 * The GMA receive back a hmiHandle that the application change
 */
static int16 gmaPGtreatTransferHmiBack(uint16 appId, gmaStructHeader_t *msg)
{
	gmaHmiTrTreatTransferHmiBack(appId, msg);
	return RET_OK;
}

/**
 * 
 */
int16 gmaPGtreatTransactionReqMsgmain(void *msg, uint32 param2)
{
   uint16  appId;
   uint8 logId;
   uint8 i;
   uint8 queryDefault[GMA_APP_LIST_LOGICAL_APP_NUMBER];
   int16 ret;
	
   gmaStructPGTransactionReq_t *trReq = 
      (gmaStructPGTransactionReq_t *)msg;

   uint8 *queryAnswer;
   gmaAppListLogicalData_t* logicalEntry;
	gmaAppListPhysicalData_t *phyEntry;
   amgMsg_t msgsend, msgReceive;

   const uint16 sizeOfstruct = 
            sizeof(gmaStructPGTransactionReq_t)  - sizeof(gmaStructHeader_t) - 4;
   
   
	memset(queryDefault, 0, sizeof(queryDefault));
	
	if(trReq->selectionType == GMA_SELECTION_MENU)
	{
		for(i=0; gmaAppListGetLogicalEntryFromInd(i, &logicalEntry)==RET_OK;i++)
		{
			gmaAppListGetAppEntryFromId(logicalEntry->appId, &phyEntry);
			if(phyEntry->type == GMA_USER_APPLICATION)
			{
				queryDefault[i] = 0xFF;
			}
			else
			{
				queryDefault[i] = 0;
			}
		}
	}
	
	queryAnswer = queryDefault;
	
   switch(trReq->selectionType)
   {
   case GMA_SELECTION_QUERY:
      {
         
         
         gmaMsgEncode(&msgsend, GMA_MSG_TRANSACTION_QUERY);
         gmaMsgSetLogicalId(0xFF);
         gmaMsgAddTransType(0xFF, trReq->transType);

         if(trReq->header.length > sizeOfstruct)
         {
            gmaMsgAdd(trReq->data, (uint16)(trReq->header.length - sizeOfstruct));
         }

         gmaMsgEndEncode();

         gmaAppMsgQueryDriven(&msgsend, &queryAnswer);
      }
   case GMA_SELECTION_MENU:
      {
      	
         gmaCustomSelectApp(queryAnswer, &appId, &logId);
      }
      break;

   case GMA_SELECTION_NONE:
      appId = trReq->appId;
      logId = trReq->logicalId;
      break;

   default:
      return -1;
   }

   gmaMsgEncode(&msgsend, GMA_MSG_TRANSACTION);

   gmaMsgSetLogicalId(logId);

   gmaMsgAddTransType(logId, trReq->transType);
   
   if(trReq->header.length > sizeOfstruct)
   {
      gmaMsgAdd(trReq->data, (uint16)(trReq->header.length - sizeOfstruct));
   }

   gmaMsgEndEncode();
   
   gmaCustomUtilBLEnable(BACKLIGHT_NONE); 

   if (gmaAppMsgWakeApp(appId, logId, &msgsend, &msgReceive) == RET_OK)
	   gmaInitProcessResponse(appId, &msgReceive);
   
   gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT); 

	return ret;
}


/**
 *****************************************************************************
 *****************************************************************************
 *****************************************************************************
 */


/**
 * 
 */
static int16 gmaPGtreadTouchAction(uint16 appId, gmaStructHeader_t *msg)
{
	int16 ret;

	uint16 index;
	gmaStructCPGtouchAction_t *touchAction = 
	    (gmaStructCPGtouchAction_t *)msg;
	gmaCTtouchData_t touchParam;
	
	gmaMediaListData_t *mediaData;
	
	// first, get the index of this entry in the mediaId table
	ret = gmaMediaGetIndex(touchAction->logicalId, appId, touchAction->mediaId);
	
	if(ret >= 0)
	{
		gmaMediaGetEntryFromIndex((uint16) ret, &mediaData);
	}
	else
	{
		return -1;
	}
	
	index = (uint16)ret;
	
	if(touchAction->action != 0)
	{
		touchParam.action = touchAction->action;
		touchParam.parameter = touchAction->parameter;
		
		if(mediaData->customData == NULL)
		{
			mediaData->customData = malloc(sizeof(gmaCTtouchData_t));
		}
		
		memcpy(mediaData->customData, &touchParam, sizeof(gmaCTtouchData_t));
	}
	else
	{
		if(mediaData->customData)
		{
			free(mediaData->customData);
			mediaData->customData = NULL;
		}
	}
	
	return RET_OK;
}




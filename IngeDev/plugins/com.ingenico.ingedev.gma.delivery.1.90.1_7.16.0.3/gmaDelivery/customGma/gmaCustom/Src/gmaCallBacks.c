
/** @file gmaCallBacks.c
 *
 * This files has the implementations of all the Custom callbacks.
 */

#include "stdlib.h"
#include "string.h"

#include "unicapt.h"
#include "gmaDefines.h"

#include "gmaMsg.h"
#include "gmaMsgCon.h"
#include "gmaMsgSup.h"
#include "gmaCBCustom.h"
#include "gmaHmiCustom.h"
#include "gmaMagCustom.h"
#include "gmaGenCustom.h"
#include "gmaHmiProcess.h"

#include "gmaCustomSemaphores.h"
#include "gmaHmiCustom.h"

#include "appInit.h"
#include "smcSupport.h"
#include "gmaCustomUtil.h"
#include "MenuLib.h"
#include "gmaAppMsg.h"
#include "gmaCustomCBs.h"
#include "gmaCusSync.h"
#include "gmaUtil.h"
#include "gmaHmiTransfer.h"
#include "gmaHmiProcess.h"
#include "menusup.h"
#include "gmaCusTouchScr.h"
#include "gmaMenuResource.h"
#include "gmaCustomParameters.h"

//#define DEBUG_ON
#include "debugLib.h"

#ifdef WIN32
#define DEBUG_TARGET DEBUG_PRN
#else
#define DEBUG_TARGET DEBUG_COM1
#endif

extern void dumpMedia(void);
static volatile uint8 perStartStatus = 1;

/**
 * This function is called when the core state change
 *
 * The following states are reported. The first number indicate
 * the state number.
 *
 * GMA_CB_STATE_BEF_POWER_ON:
 *   will start to send the power On messages to the applications
 * GMA_CB_STATE_BEF_INTEGRITY_CHECK:
 *   the power on was sent, will start to send the Integrity check messages
 * GMA_CB_STATE_BEF_STARTUP:
 *   the integrity check messages was sent, will start to sent the Startup message
 * GMA_CB_STATE_BEF_LOOP:
 *   the Startup message was sent. The GMA will enter the Main loop
 * GMA_CB_STATE_WAKE_APPL:
 *   the GMA will wake up an application
 * GMA_CB_STATE_IDLE_STATE:
 *   the terminal will return to the IDLE state
 *
 * @param state (I) the state of the GMA (see the states above)
 */
static int16 gmaCBStateChange(uint16 state)
{
   switch(state)
   {
   case GMA_CB_STATE_BEF_POWER_ON:
      
      amgSelectionCriteriaDel(T_AID);
      
      gmaCustomUtilInit();
      
      gmaCusParameterInit();
      
      gmaCustomUtilSetSpecKeys();
      gmaHmiUtilSetSpecKeys();
      
      gmaHmiOpen();
      gmaCustomUtilBLEnable (BACKLIGHT_TIMEOUT);
      gmaHmiDisplayText(1, 2, gmaGetStringResource(IDS_PLEASE_WAIT));
      gmaHmiClose();
      
      mnustsIdentifyTerminal();
      
      gmaMsgCreateGlobalFile();
      gmaMsgResetGlobalFile();
      
      gmaHmiTrInit();
      
      gmaMRESInitialize();
      //IFDEBUG(debugPrintf(DEBUG_TARGET,"Global File"));
      break;
      
   case GMA_CB_STATE_WAKE_APPL:
      gmaCBStopPerSup();
      break;
      
   case GMA_CB_STATE_IDLE_STATE:
      psyIdleNotify(PSY_IDLE_ON);
      gmaCBBeginPerSup();
      gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
      break;
      
   case GMA_CB_STATE_BEF_INTEGRITY_CHECK:
      break;
      
   case GMA_CB_STATE_MAINTENANCE:
      gmaCBStopPerSup();
      break;
      
   case GMA_CB_STATE_BEF_LOOP:
      gmaCustomSemaphoreInit();
      gmaCBBeginPerSup();
      gmaCtSynInitialize();
      
      // set the callback to treat the touchScreen
      gmaCTSetHandlerFunction(gmaHmiTouchProcess);
      gmaCTSEnableTouchScreen(1);
      break;
      
   }
   return RET_OK;
}

/**
 * This function is called before the core send the message to
 * the application and after the default message is prepare by
 * the core.
 *
 * @param sendMsg a pointer to the message to be send.
 */
static int16 gmaCBBeforeSendMessage(amgMsg_t *sendMsg)
{

    return RET_OK;
}

/**
 * 
 * This function is called after the answer message is received 
 * by the core part. And after the core do its default treatment.
 *
 * @param recMsg a pointer to the message received.
 *
 */
static int16 gmaCBAfterReceiveMessage(amgMsg_t *recMsg)
{

    return RET_OK;
}

/**
 * This function is called in the GMA loop. The custom
 * will use the function to make asynchronous requests
 * or some quickly synchronous requests.After this function
 * returns the core will call the OS function
 * psyPeripheralResultWait with the parameters returned by this
 * function
 *
 * @param perIds the peripheral ids that a request was made
 * @param timeout the timeout to wait in the psyPeripheralResultWait function
 */
static int16 gmaCBRequests(uint32 *perIds, uint32 *timeout)
{
   //IFDEBUG(debugPrintf(DEBUG_TARGET, "perStartStatus=%d", perStartStatus));
   psyIdleNotify(PSY_IDLE_ON);
   if(perStartStatus)
   {
	   *perIds = 0;
	   if (gmaHmiKeyReq() == RET_RUNNING)
	   {
		   (*perIds) |= HMI_WAIT;
	   }
	   
	   if (gmaMagCrdReq() == RET_RUNNING)
	   {
		   (*perIds) |= MAG_WAIT;
	   }

	   if (smcSupRequest() == RET_RUNNING)
	   {
		   (*perIds) |= SMC_WAIT;
	   }
	   
	   gmaCTSreq();
   }
   else
   {
      *perIds = 0;
   }
   IFDEBUG(debugPrintf(DEBUG_TARGET, "perIds = %X", *perIds));

	*timeout = 50;		//	Wait for 500ms
	
	return RET_OK;
}

/**
 * This callback will be called when the psyPeripheralResultWait in 
 * the core part return and after the normal core treatment for that is
 * finished.
 *
 * @param ret the return from the psyPeripheralResultWait function
 */
static int16 gmaCBResult(int32 ret)
{
	int16 retVal = 0;
	IFDEBUG(debugPrintf(DEBUG_TARGET, "gmaCBResult=%x", ret));
	if (ret >= 0)
	{
      psyIdleNotify(PSY_IDLE_OFF);
      //
		if (PSY_PER_EXECUTED_OK (ret,HMI_WAIT))
		{
         gmaCBActivityStart();
			retVal = gmaHmiKeyResultGet ();
			if(retVal >= 0)
			{
				gmaMagSupCancel();
      		smcSupCancel();
				gmaHmiKeyProcess(retVal);
			}
			gmaCTSresult(ret);
		}
		else if (PSY_PER_EXECUTED_OK(ret,MAG_WAIT))
		{
         gmaCBActivityStart();
			retVal = gmaMagCrdResultGet ();
		}
		else if (PSY_PER_EXECUTED_OK(ret,SMC_WAIT))
		{
         gmaCBActivityStart();
			gmaCustomUtilBLEnable(BACKLIGHT_NONE);
			retVal = smcSupResult();
			gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
		}
		else if (ret & PSY_EVENT_RECEIVED)
		{
         gmaCtSynTreatmainTaskEvent(ret);
			if (ret & EVENT_5)
			{
			   gmaCustomUtilBLDisable ();
			}
         
		}

      gmaCBActivityEnd();
	}
	else
	{
		retVal = -1; // DEFINIR
	}
	
   return retVal;
}

/**
 * Function called to the custom redraw the screen
 */
static int16 gmaCBRedrawDisplay(void)
{
   return gmaDisplayCustom();
}

/**
 * Function called when the GMA receives a message from a plugin 
 * (plugin sent a message to the plugin command queue).
 *
 * @param appId the plugin Id that sends this message
 *
 * @param msg the message sent.
 */
static int16 gmaCBMsgFromPlugIn (uint16 appId, gmaStructHeader_t *msg)
{
	return gmaCustomMsgFromPlugIn (appId, msg);
}

/**
 * Function called when the application send an optional struct in the reply message.
 *
 * @param appId application Identifier that sends the reply message
 *
 * @param msg a pointer to the optional reply structure
 */
static int16 gmaCBMsgFromApp (uint16 appId, gmaStructHeader_t *msg)
{
	return gmaCustomMsgFromApp (appId, msg);
}

/**
 * Function called when an schedule event occur
 *
 * @param appId appID of the application that schedule the event
 *
 * @param logicalId logicalId of the application that schedule the event
 *
 * @param eventId the event identifier
 */
static int16 gmaCBTreatEvent(uint16 appId, uint8 logicalId, uint16 eventId)
{
   int16 ret;
	amgMsg_t defaultMsg;
	amgMsg_t responseMsg;
	gmaMsgEncode(&defaultMsg, GMA_MSG_EVENT_OCCUR);
   gmaMsgSetLogicalId(logicalId); 
	gmaMsgsAddEventOccur(logicalId, eventId);
	gmaMsgEndEncode();

   ret = gmaAppMsgWakeApp(appId, logicalId, &defaultMsg, &responseMsg);
   
   gmaInitProcessResponse(appId, &responseMsg);
   
	return ret;

}


static uint8 activityActualStatus = 0;
/**
 * An activity is finished. Only send a message to the plugins
 * if a previous \ref gmaCBActivityStart was called
 */
int16 gmaCBActivityEnd(void)
{
   if(activityActualStatus == 1)
   {
      activityActualStatus = 0;
      gmaAppMsgSendActivityMsg(GMA_PG_ACTIVITY_END);
      //teste
      
   }
   return RET_OK;
}

/**
 * An activity is begun. Call the function \ref gmaAppMsgSendActivityMsg
 * to warn the plugins about it
 */
int16 gmaCBActivityStart(void)
{
   activityActualStatus = 1;
   gmaAppMsgSendActivityMsg(GMA_PG_ACTIVITY_START);
   return RET_OK;
}



/**
 * Begin the peripheral support
 */
int16 gmaCBBeginPerSup(void)
{
   //gmaHmiOpen();
	// TGOTODO Check the return values and do something if one periph
	// fails (e.g. store in an array the list of periph that succeeded
	// so that they can be checked later on).
   gmaHmiTrHmiOpen();
   gmaCTOpenHandle();
   gmaMagOpen();
   smcSupBegin();
   return RET_OK;
}

/**
 * Stop the peripheral support
 */
int16 gmaCBStopPerSup(void)
{
   //gmaHmiClose();
   gmaHmiTrHmiClose();
   gmaCTCloseHandle();
   gmaMagClose();
   smcSupEnd();
   return RET_OK;
}

/**
 * Cancel all pending events
 */
int16 gmaCBCancelEvents(void)
{
   gmaHmiSupCancel();
   gmaMagSupCancel();
   smcSupCancel();
   return RET_OK;
}

/**
 * Enable/disable peripheral start
 */
void gmaCBEnablePerStart(uint8 status)
{
   perStartStatus = status;
}

/**
 * 
 */
static int16 gmaCBBeforeWakeUpApp(uint16 appId, uint8 logicalId, amgMsg_t *sendMsg)
{
	
	
	// beep status is set, prepare the message to be sent
	gmaStructConfigInfo_t *config = 
	(gmaStructConfigInfo_t *) &(sendMsg->msg[sendMsg->msgLength]);
	memset(config, 0, sizeof(gmaStructConfigInfo_t));
	
	gmaMsgGenerateHeader(&config->header, GMA_STRUCT_CONFIG_INFO,
                        sizeof(gmaStructConfigInfo_t));
   
   config->beepStatus = gmaHmiGetBeepStatus();
   sendMsg->msgLength += sizeof(gmaStructConfigInfo_t);

	return gmaHmiTrAppMsgWakeApp(appId, logicalId, sendMsg);
}


/**
 * Set the custom call backs
 *
 * 
 */
int16 gmaInitCustomCallBacks(void)
{
	gmaCustomCallBacks_t cbs;
	gmaCustomNewCallBacks_t newCbs;
	memset(&newCbs, 0, sizeof(newCbs));
		
	cbs.afterSendMsg  = gmaCBAfterReceiveMessage;
	cbs.beforeSendMsg = gmaCBBeforeSendMessage;
	cbs.redrawDisplay = gmaCBRedrawDisplay;
	cbs.requests      = gmaCBRequests;
	cbs.results       = gmaCBResult;
	cbs.stateChange   = gmaCBStateChange;
	cbs.msgFromPlugin = gmaCBMsgFromPlugIn; 
	cbs.msgFromApp    = gmaCBMsgFromApp;
	cbs.treatEvent    = gmaCBTreatEvent;
	
	newCbs.beforeWakeUpApp = gmaCBBeforeWakeUpApp;

	gmaCBCustomSetCallBacks(&cbs);
	
	gmaCBCustomSetNewCallBacks(&newCbs);
	
	return RET_OK;
}



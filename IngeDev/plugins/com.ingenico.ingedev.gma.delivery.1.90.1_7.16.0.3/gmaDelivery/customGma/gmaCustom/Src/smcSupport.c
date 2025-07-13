
/*
 * IDLE support for SMC peripheral.
 *
 * Unicapt32 - Idle Application
 *  Ingenico Latin America
 */

/**
 * @file smcSupport.c
 *
 * Smart card support functions.
 *
 * In this module there are functions to make the SMC request and 
 * to get the SMC result if available. If a SMC is detected this
 * module sends a power on to the card and call the function
 * \ref emvSelectApplication to selection an application
 */

#include <string.h>
#include <unicapt.h>

//#define DEBUG_ON
#include "DebugLib.h"
#include "AppList.h"
#include "appInit.h"
#include "GmaDefines.h"
#include "GmaMsg.h"
#include "GmaMsgCon.h"
#include "GmaHmiCustom.h"
#include "GmaMagCustom.h"
#include "SmcSupport.h"
#include "GmaMsgSup.h"
#include "GmaAppMsg.h"
#include "gmaHmiProcess.h"
#include "gmaCustomUtil.h"
#include "gmaGenCustom.h"
#include "gmaCustomParameters.h"

/*#ifdef WIN32
#define DEBUG_TARGET DEBUG_PRN
#else
#define DEBUG_TARGET DEBUG_PRN
#endif*/
#define DEBUG_TARGET DEBUG_COM1


/*
 * Local (static) values.
 */

/**
 * Define if the smc is enabled or not.
 */
static uint8 s_smcEnabled = GMA_SMC_DEVICE_ENABLE;

/**
 * Store the smc handle
 */
static uint32 s_smcHandle = 0;
static uint8 s_smcFallBack = 0;
static uint8 s_smcFallBackStep = 0;
static int16  s_smcFallBackStatus = 0;
static psyTime_t s_smcFallBackTime = 0;

static gmaSmcAtrResult_t smcAtrResult;

/**
 * Defined at emvSelect.c
 */
int emvSelectApplication(char *finSelRsp, uint16 *pid);

/**
 * Internal
 */
static int16 smcSupTreatResult(void);
static void smcDoFallback(void);
static uint8 smcIsFallBackStatusEnable(char *name, int16 error);

/**
 * Enable/Disable SMC events.
 *
 * @param enabled If 0 the SMC will be disabled.
 *                If 1 the SMC will be enabled
 */
int16 smcSupSetEnable(uint8 enabled)
{
   s_smcEnabled = enabled;
   return RET_OK;
}

/**
 * Return mask to use in call to psyPeripheralResultWait()
 * in main Idle loop.
 */
uint32 smcSupWaitMask(void)
{
   return (s_smcEnabled) ? SMC_WAIT : 0;
}

/**
 * Begin the SMC support.
 */
int16 smcSupBegin(void)
{
   int16 ret = smcOpen("DEFAULT", &s_smcHandle);
   if (ret != RET_OK)
   {
      IFDEBUG( debugPrintf(DEBUG_TARGET, "Error openning SMC"); )
      smcSupSetEnable(GMA_SMC_DEVICE_DISABLE);
   }
   return ret;
}

/**
 * End SMC support.
 * Cancel events and close handle.
 */
int16 smcSupEnd(void)
{
   if(s_smcHandle)
   {
      smcSupCancel();

      smcClose(s_smcHandle);
      s_smcHandle = 0;
   }
   return RET_OK;
}

/**
 * Return the SMC handle currently open.
 */
uint32 smcSupGetHandle(void)
{
   return s_smcHandle;
}

/**
 * Make SMC request for card insertion.
 * If the card is already inserted, will ask user to
 * remove it.
 */
int16 smcSupRequest(void)
{
	int16 ret;
   if (s_smcEnabled)
   {
   	
   	if (smcResultCheck (s_smcHandle, SMC_OTHERS) == RET_RUNNING)
   		return RET_RUNNING;
   	
      ret = smcInsertCardReq(s_smcHandle);
      if(ret == RET_OK)
      {
         /* tell user to remove card*/
         smcSupRemoveCard();
         ret = smcInsertCardReq(s_smcHandle);
         

         /* TTM -- Apr 6 2005 */
         //IFDEBUG(debugPrintf(DEBUG_TARGET, "smcInsertCardReq RET_OK"));

         //smcSupTreatResult();

         return ret;
      }
      return ret;
   }

   // TGOTODO Error code instead?
   return RET_OK;
}

/**
 * Send a power on message to the inserted card
 */
int smcPowerOn(void)
{
	int ret;
   smcCommand_t com;
   union smcCommandIn_t cit;

	

	com.commandType = SMC_NEW_POWER_ON;
   cit.newPowerCommand.cardStandards = SMC_EMV;
   cit.newPowerCommand.GRClassByte00 = SMC_CLA_00;
   cit.newPowerCommand.preferredProtocol = SMC_DEFAULT_PROTOCOL;
   com.commandIn = &cit;
    
   ret= smcCommandReq(s_smcHandle,&com);
   IFDEBUG(debugPrintf(DEBUG_COM1, "POWER ON->%d", ret));
	if(ret!=RET_RUNNING) return -1;

   memset(&smcAtrResult,0,sizeof(smcAtrResult));
   do {
      ret= smcResultGet(s_smcHandle,SMC_OTHERS,sizeof(smcAtrResult),&smcAtrResult);
      psyTimerWakeAfter(1);
   } while(ret==RET_RUNNING);
   IFDEBUG(debugPrintf(DEBUG_COM1, "POWER ON RET->%d -  %d", ret, smcAtrResult.status));
   
	if (ret != RET_OK) return -1;
   
   return smcAtrResult.status; 
}

/**
 * Display a message that card is not accepted.
 */
static
void smcSupSCardNotAcceptedMsg(void)
{
   gmaHmiClearLine(HMI_ALL_LINES);
   gmaHmiAutoCentre(1);
   gmaHmiDisplayText(1, 0, gmaGetStringResource(IDS_CARD_NOT_ACCEPT1));
   gmaHmiDisplayText(2, 0, gmaGetStringResource(IDS_CARD_NOT_ACCEPT2));
   hmiBeep(gmaHmiGetHandle(), HMI_BEEP_SHORT, HMI_BEEP_MIDTONE);
   gmaHmiAutoCentre(0);
   psyTimerWakeAfter(2*100);
}

/**
 * Non EMV card support
 */
static int16 smcQueryNonEmv(amgMsg_t *msg, amgMsg_t *answer)
{
   uint8 logicalID;
   uint16 appID;
   int16 ret;
   uint8 *queryAns;
   
   /* error during card power-on. try to send a message to
      an application. maybe it's a weird card and the application
      can handle it */
   
   /* send info without selection info */
   gmaMsgEncode(msg, GMA_MSG_TRANSACTION_QUERY);
   gmaMsgSetLogicalId(0xFF);
   gmaMsgAddTransType(0xFF, GMA_TRANS_SMART_CARD);
   gmaMsgsAddTransSmartCard(GMA_SMART_CARD_UNKNOWN, GMA_SELECTION_CARD_INSERTED);
   gmaMsgEndEncode();

   ret = gmaAppMsgQueryDriven(msg, &queryAns);
   if(ret != RET_OK)
   {
      return ret;
   }

   ret = gmaCustomSelectApp(queryAns, &appID, &logicalID);
   if(ret < 0)
   {
      return ret;
   }
   gmaMsgEncode(msg, GMA_MSG_TRANSACTION);
   gmaMsgSetLogicalId(logicalID);
   gmaMsgAddTransType(logicalID, GMA_TRANS_SMART_CARD);
   gmaMsgsAddTransSmartCard(GMA_SMART_CARD_UNKNOWN, GMA_SELECTION_CARD_INSERTED);
   gmaMsgEndEncode();

   ret = gmaAppMsgWakeApp(appID, logicalID, msg, answer); //TODO
   gmaInitProcessResponse(appID, answer);

   //appMngSendAwake(0, IDLE_AWAKE_SMC, 0, NULL);

   return RET_OK;
}

/**
 * Treat a assynchronous pending result in the SMC
 */
static int16 smcSupTreatResult(void)
{
   int16 ret;
   uint32 finSelRsp_[264/4];    // final application select response (force 4 bytes alignment)
   uint16 pid;             // selected application pid
	uint16 appId;           // selected terminal application identifier
   char * const finSelRsp = (char *)finSelRsp_; // final application select response (alingned)
   amgMsg_t msg, answer;
   
   /* cancel other pending requests */
   gmaHmiSupCancel();
   gmaMagSupCancel();
   smcSupClearFallback();
   
   
   IFDEBUG(
      debugPrintf(DEBUG_TARGET, "smcPowerOn");
   )

	ret = smcPowerOn();
	IFDEBUG(debugPrintf(DEBUG_TARGET, "smcPowerOn=%d", ret));
	if (ret < 0)
   {
   	if(ret != SMC_CARD_MUTE && ret != SMC_ATR_NOT_19200 && ret != SMC_NO_ATR_RECEIVED)
   	{
      	ret = smcQueryNonEmv(&msg, &answer);
   	}
   	else
   	{
   		smcSupSCardNotAcceptedMsg();
      	smcSupRemoveCard();
      	smcSupSetFallBack(GMA_SMC_FALLBACK_POWER_ON, ret);
   	}
      return ret;
   }

   IFDEBUG(
      debugPrintf(DEBUG_TARGET, "emvSelectApplication");
   )

   /* try the EMV selection process */   
   smcSupEnd();
   ret = emvSelectApplication(finSelRsp, &pid);
   //amgEndPayment();
   smcSupBegin();

   IFDEBUG(
      debugPrintf(DEBUG_TARGET, "returned %d", ret);
   )

   if (ret < 0)
   {
      
     // Try a None Emv selection
  	  if (gmaNoneEmvSelectApplication(&smcAtrResult) != RET_OK)      // B.K
  	  {
           smcSupSCardNotAcceptedMsg();
  	  }

     s_smcFallBack = 1;
     psyTimeGet(&s_smcFallBackTime);
      //smcSupSetFallBack(2, ret);
   }
	else if (ret > 0)
   {
		int16 len = ret;
		int16 index;
		gmaAppListPhysicalData_t* appData;

		index = gmaAppListGetIndexFromPid (pid);
		ret = gmaAppListGetAppEntryFromInd(index, &appData);
		appId = appData->appId;

      IFDEBUG(
         debugPrintf(DEBUG_TARGET, "IdFromPid(%d) %d --> %d", ret, pid, appId);
      )

      /* if an application was found */
		if (ret >= 0)
      {
         /* send info with selection info */
         gmaMsgEncode(&msg, GMA_MSG_TRANSACTION);
         gmaMsgSetLogicalId(0xFF);
         gmaMsgAddTransType(0xFF, GMA_TRANS_SMART_CARD);
         gmaMsgsAddTransSmartCard(GMA_SMART_CARD_ASYNCHRONOUS, GMA_SELECTION_DONE);
         gmaMsgsAddTransSmcEmv((uint8*)finSelRsp, len + 1); // For the "+ 1" see tracker #932
         gmaMsgEndEncode();
         ret = gmaAppMsgWakeApp(appId, 0xFF, &msg, &answer);
         gmaInitProcessResponse(appId, &answer);
         amgEndPayment();// added here
         //appMngSendAwake(appId, IDLE_AWAKE_SMC_EMV, len, (uint8*)finSelRsp);
      }
      else
      {
         smcSupSCardNotAcceptedMsg();
         amgEndPayment();// added here
      }
	}
   else
   {
   	if (gmaNoneEmvSelectApplication(&smcAtrResult) != RET_OK)
	   {
	      smcSupSCardNotAcceptedMsg();
	   }
      
      amgEndPayment(); // added here
   }
   
   return RET_OK;
}

/**
 * Process the SMC result.
 */
int16 smcSupResult(void)
{
   
   struct {
      int16 status;
      uint16 length;
   } result;
   int16 ret;

   IFDEBUG(
      debugPrintf(DEBUG_TARGET, "smcSupResult");
   )

   ret = smcResultGet(s_smcHandle, SMC_OTHERS, sizeof(result), &result);
   if(ret == RET_RUNNING)
   {
   	return ret;
   }
   if (ret == RET_OK && result.status == RET_OK)
   {
      smcSupTreatResult();
   }

   smcSupRemoveCard();
   
   // check if a fallback is necessary
   if(s_smcFallBack)
   {
   	// error occurs... Need to analise which error and decide if a fallback is needed
   	smcDoFallback();
   	
   	smcSupClearFallback();
   }
   
   return RET_OK;
}

/**
 * Cancel any pending requests
 */
int16 smcSupCancel(void)
{
   return smcCancel(s_smcHandle, PER_ALL_EVENTS);
}

/**
 * Tell the user to remove the smart card.
 */
int16 smcSupRemoveCard(void)
{
   int32 wait;

   /* cancel any pending event */
   smcSupCancel();

   /* check if card is still inserted */
   if (smcDetect(s_smcHandle) != RET_OK)
   {
      return RET_OK;
   }
   gmaHmiClearLine(HMI_ALL_LINES);
   gmaHmiSetFont(HMI_INTERNAL_FONT_DEFAULT);
   gmaHmiAutoCentre(1);
   gmaHmiDisplayText(1, 0, gmaGetStringResource(IDS_PLEASE));
   gmaHmiDisplayText(2, 0, gmaGetStringResource(IDS_REMOVE_SMC));
   gmaHmiAutoCentre(0);
   
   for (;;)
   {
      smcRemoveReq(s_smcHandle);
      wait = psyPeripheralResultWait(SMC_WAIT, PSY_INFINITE_TIMEOUT, 0);
      if (PSY_PER_EXECUTED_OK(wait, SMC_WAIT))
      {
         struct {
            int16 status;
            uint16 length;
            uint8 data[8];
         } result;
         smcResultGet(s_smcHandle, SMC_REMOVAL, sizeof(result), &result);
         gmaHmiClearLine(HMI_ALL_LINES);
         break;
      }
   }

   smcCancel(s_smcHandle, SMC_REMOVAL);
   return RET_OK;
}

/**
 * Return 1 if there is a pending fallback condition.
 * 0 or a negative number if not.
 */
int16 smcSupIsFallbackPending(void)
{
   return (s_smcFallBack);
}

/**
 * Clear the fallback condition flag.
 */
int16 smcSupClearFallback(void)
{
   s_smcFallBack = 0;
   s_smcFallBackTime = 0;
   s_smcFallBackStep = 0;
	s_smcFallBackStatus = 0;
   return RET_OK;
}

/**
 * 
 */
int16 smcSupSetFallBack(uint16 step, int16 status)
{
	s_smcFallBackStep = step;
	s_smcFallBackStatus = status;
	psyTimeGet(&s_smcFallBackTime);
	s_smcFallBack = 1;
	return RET_OK;
}

/**
 * Return the number of seconds elapsed since the last SMC transaction
 * that generated a fallback.
 * Return zero if no fallback is pending.
 */
uint32 smcSupFallbackTimer(void)
{
   psyTime_t now;

   if (s_smcFallBackTime)
   {
      psyTimeGet(&now);
      return (uint32) (now - s_smcFallBackTime);
   }
   else
   {
      return 0;
   }
}

/**
 * 
 */
int16 smcSupAddFallBackMsg(void)
{
	return gmaMsgsAddSmcFallback(s_smcFallBack, smcSupFallbackTimer(), s_smcFallBackStep, s_smcFallBackStatus);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

static uint8 smcIsFallBack(void)
{
	
	
	if(s_smcFallBack)
	{
		switch(s_smcFallBackStep)
		{
			case GMA_SMC_FALLBACK_POWER_ON:
				if(smcIsFallBackStatusEnable("SMC_FB_POWER_ON",s_smcFallBackStatus))
				{
					return 1;
				}
				break;
			case GMA_SMC_FALLBACK_EMV_INIT_SELECTION:
				if(smcIsFallBackStatusEnable("SMC_FB_INIT_SELEC",s_smcFallBackStatus))
				{
					return 1;
				}
				break;
			case GMA_SMC_FALLBACK_EMV_NO_APPS:
				if(smcIsFallBackStatusEnable("SMC_FB_NO_APPS",s_smcFallBackStatus))
				{
					return 1;
				}
				break;
			case GMA_SMC_FALLBACK_ASK_SELECTION:
				if(smcIsFallBackStatusEnable("SMC_FB_ASK_SELEC",s_smcFallBackStatus))
				{
					return 1;
				}
				break;
			case GMA_SMC_FALLBACK_FINAL_SELECTION:
				if(smcIsFallBackStatusEnable("SMC_FB_FINAL_SELEC",s_smcFallBackStatus))
				{
					return 1;
				}
				break;
			default:
				break;
		}
	}
	
	return 0;
}

/**
 * 
 */
static void smcDoFallback(void)
{
	int16 ret16;
	int32 ret;
	if(smcIsFallBack())
	{
		gmaHmiClearLine(HMI_ALL_LINES);
		gmaHmiAutoCentre(1);
		gmaHmiDisplayText(0, 0, gmaGetStringResource(IDS_SWIPE));
		gmaHmiDisplayText(1, 0, gmaGetStringResource(IDS_MAGCARD));
		gmaHmiDisplayText(2, 0, gmaGetStringResource(IDS_OR));
		gmaHmiDisplayText(3, 0, gmaGetStringResource(IDS_PRESS_CAN));
		gmaHmiAutoCentre(0);

      gmaMagOpen();

      
		while(42)
		{
			uint32 perId = 0;
			if (gmaHmiKeyReq() == RET_RUNNING)
			{
				perId |= HMI_WAIT;
			}
			
			if (gmaMagCrdReq() == RET_RUNNING)
			{
				perId |= MAG_WAIT;
			}
			
			// TGOTODO What do we do if perId is 0?
			
			ret = psyPeripheralResultWait(perId, 3000, 0);
			
			if(ret >= 0)
			{
				if(PSY_PER_EXECUTED_OK (ret,HMI_WAIT))
				{
					ret16 = gmaHmiKeyResultGet();
					
					if(ret16 == HMI_KEY_CLEAR || ret16 == HMI_KEY_BCKSP)
					{
						break;
					}
				}
				else if(PSY_PER_EXECUTED_OK(ret,MAG_WAIT))
            {
               gmaMagCrdResultGet();
               break;
            }
            
			}
		}
      
      gmaHmiSupCancel();
      gmaMagSupCancel();
	}
}

/**
 * 
 */
static uint8 smcIsFallBackStatusEnable(char *name, int16 error)
{
	uint16 i;
	int16 ret;
	uint16 size;
	int16 list[10];
	size = sizeof(list)/sizeof(list[0]);
	
	ret = gmaCusGetValueList(name, list, &size);
	
	if(ret != RET_OK)
	{
		return 0;
	}
	
	if(size==0)
		return 1;
	for(i=0; i<size;i++)
	{
		if(error==list[i])
			return 1;
	}
	return 0;
}




/*
 *  EMV Application Select
 *
 *  Unicapt32 - Idle Application
 *  Alexei BARANTSEV
 *  non Ingenico 
 */


/** @file emvSelect.c
 * 
 * EMV Application selection.
 *
 * Make the application selection based in the information
 * provided by the application using the structure \ref gmaStructEmvAid_s.
 */

#include <string.h>
#include <unicapt.h>

//#define DEBUG_ON
#include "DebugLib.h"

//#include "hmiSupport.h"
//#include "Display.h"
#include "menuLib.h"
//#include "IdleStrings.h"
#include "appList.h"
#include "gmaDefines.h"
#include "gmaHmiCustom.h"
#include "gmaCustomUtil.h"
#include "smcSupport.h"
#include "resources.h"
#include "gmaCusEmvSel.h"

#ifdef WIN32
#define DEBUG_TARGET DEBUG_PRN
#else
#define DEBUG_TARGET DEBUG_PRN
#endif


/**
 * Initialize the emv payment process.
 */
static
int emvInit(void)
{
	int ret;
   amgMsg_t msg;

   msg.msgType = MSG_SMART_CARD;
   msg.msgLength = 0;
   msg.receiverPid= 0xFFFF;
   msg.callerTaskId= 0xFFFF;
   ret = amgInitPayment("DEFAULT",&msg);
   if(ret!= RET_OK)
   {
	  IFDEBUG(debugPrintf(DEBUG_COM1, "amgInitPayment=%d",ret));
   	  smcSupSetFallBack(GMA_SMC_FALLBACK_EMV_INIT_SELECTION, ret);
      amgEndPayment();
      return -1;
   }
	return RET_OK;
}

/**
 * Display the list of applications supported by the Chip.
 */
static
int selectCandidate(amgSelectionResult_t *rsp)
{
	uint8 ret;
	int dim;
	uint16 idx;
	int16  retVal;
	char* itemList[GMA_APP_LIST_LOGICAL_APP_NUMBER];
	char buf[(16+1)*GMA_APP_LIST_LOGICAL_APP_NUMBER];
	uint8 len = 0;

	dim = rsp->dataList.emv2List.nbAid;
	
	for(idx = 0; idx < dim; idx++)
    {
		len = rsp->dataList.emv2List.tbAid[idx].appNameLength;

		if(len>16) return -1; //invalid length

		memcpy(&buf[(16+1)*idx],rsp->dataList.emv2List.tbAid[idx].appName,len);
		buf[((16+1)*idx)+len]= 0;	

        IFDEBUG(debugPrintf(DEBUG_COM1 , "APP: %s", &buf[(16+1)*idx]) );
        IFDEBUG(debugPrintf(DEBUG_COM1 , "AID:"));
        IFDEBUG(debugHexDump(DEBUG_COM1, rsp->dataList.emv2List.tbAid[idx].aidName, rsp->dataList.emv2List.tbAid[idx].aidLength));

        itemList[idx] = &buf[(16+1)*idx];
	}
	ret = 0;
    retVal = gmaHmiMenu (gmaGetStringResource(IDS_SMC_APP_SEL), (const char **)itemList, (uint8)dim, &ret, 6000);

	if (retVal != RET_OK)
	{
		ret = 0xFF;
	}

	return ret;
}

/**
 * If more than one application is capable of handling an AID, display
 * a menu of the available applications.
 * If only one is available, return its pid.
 * If no application is found, return -1.
 */
static
int selectTermApp(amgSelectionResult_t *rsp,int idx)
{
   int16 retVal;
   uint8 ret;
   char* itemList[GMA_APP_LIST_LOGICAL_APP_NUMBER];
   int16 index, count = 0;
   uint16 lastAdded = 0;
   uint16 pidVec[GMA_APP_LIST_LOGICAL_APP_NUMBER];

   for (index = 0; index < 10; ++index)
   {
      int16 appindex;
      gmaAppListPhysicalData_t* app;
      uint16 pid = rsp->dataList.emv2List.tbAid[idx].termAppliCandidate[index];

      if (pid == 0) break;

      IFDEBUG( debugPrintf(DEBUG_COM1, "Pid[%d]==%u", index, pid); )

      /* If PID is not found into list of active applications, we ignore it.
         This may happen if application did its AddCriteria() but it is not
         active, or an error happened during power-on */
      appindex = gmaAppListGetIndexFromPid(pid);
      if (appindex >= 0)
      {
		 pidVec[count] = pid;
         gmaAppListGetAppEntryFromInd(appindex, &app);
		 itemList[count] = (char*)(app->name);
         ++ count;
         lastAdded = pid;
      }
   }

   IFDEBUG( debugPrintf(DEBUG_COM1, "%d apps found", count) );
   

   if (count == 0)
   {
   	smcSupSetFallBack(GMA_SMC_FALLBACK_EMV_NO_APPS, -1);
      return -1;
   }
   else if (count == 1)
      return lastAdded;
   else
   {
   	  ret = 0;
      retVal = gmaHmiMenu (gmaGetStringResource(IDS_APP_SEL), (const char **)itemList, (uint8) count, &ret, 6000);
   }

	if (retVal != RET_OK)
	{
      return -1;
	}

	return pidVec[ret];
}


/**
 * Communicate with the PAM to select the PID of one application
 * capable of handling a selected application from the currently inserted
 * smart-card.
 *
 * finSelRsp: final result from EMV selection
 * pid: process ID of selected application
 *
 * Return: the length of finSelRsp on success.
 *         a negative error code in case of error.
 *         zero if not application can handle this application.
 */
int emvSelectApplication(char *finSelRsp,uint16 *pid)
{
   int ret;
	int idx = 0;
	int cardholderConfirm = 0;
	amgSelectionResult_t rsp; //structure containing amgAskSelection response
   typedef struct {
     int16   cardStatus;
     uint16  len;
     uint8   Answer[1];
	} emvSsmcAnswer_t;
   
	
   gmaEmvSelAddNow(); // add the AID list
	
   *pid = 0; //initialise it somehow

   ret = emvInit();
   if(ret<0) return ret;

   //Let EMV Kernel prepare candidate list
   ret = amgAskSelection(&rsp, 0, 0, 0);
   if (ret!=RET_OK)
   {
   	IFDEBUG(debugPrintf(DEBUG_COM1, "amgAskSelection=%d", ret));
      smcSupSetFallBack(GMA_SMC_FALLBACK_ASK_SELECTION, ret);
   	  return -1;
   }

   ret = rsp.dataList.emv2List.nbAid;

   IFDEBUG( debugPrintf(DEBUG_COM1, "nbAid = %d", rsp.dataList.emv2List.nbAid) );

	switch (ret) {
	case 0: //the candidate list is empty
      return 0;

	case 1:  //only one candidate in the list; ret is the index of the candidate
      idx = 0;
      cardholderConfirm = 1;
      break;

	default: //select a candidate from menu
      if (ret > 0) idx = selectCandidate(&rsp);
      break;
	}

	// Watch out: selectCandidate can return 0xFF but this is not
	// a negative value because it is put inside an int!
	//  Therefore a specific check for 0xFF must be done.
	if (ret < 0 || idx < 0 || idx == 0xFF)
		return -1;

   IFDEBUG( debugPrintf(DEBUG_COM1, "Index %d", idx) );

   // select a terminal application
	ret = selectTermApp(&rsp, idx);
	if (ret < 0 ) return -1;
	*pid = ret;

   IFDEBUG( debugPrintf(DEBUG_COM1, "Selected PID %d", *pid); )

	ret = rsp.dataList.emv2List.tbAid[idx].priorityIndic;
   if ((ret & 0x80) && cardholderConfirm)
   {
		ret = gmaHmiConfirm((char*)rsp.dataList.emv2List.tbAid[idx].appName,
                       rsp.dataList.emv2List.tbAid[idx].appNameLength);
		IFDEBUG(debugPrintf(DEBUG_COM1, "gmaHmiConfirm = %d", ret));
		if (!ret) return 0; //not confirmed
	}
	
	ret = amgEmvFinalSelect("DEFAULT", &rsp.dataList.emv2List.tbAid[idx], &rsp, finSelRsp, 0, NULL);
	IFDEBUG(debugPrintf(DEBUG_COM1, "amgEmvFinalSelect=%d", ret));
   IFDEBUG( debugPrintf(DEBUG_COM1, "FinalSelect %d", ret) );

	if (ret<0)
	{
		smcSupSetFallBack(GMA_SMC_FALLBACK_FINAL_SELECTION, ret);
		 return ret;
	}

	return ((emvSsmcAnswer_t *)finSelRsp)->len + 4; //return the length of the response including the header (4 bytes)

}


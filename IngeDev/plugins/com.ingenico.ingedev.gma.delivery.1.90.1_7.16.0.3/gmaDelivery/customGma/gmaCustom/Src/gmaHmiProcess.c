
/**
 * @file gmaHmiProcess.c
 *
 * Process the keyboard events.
 *
 * When a key is pressed the function \ref gmaHmiKeyProcess will be called
 * and will treat the key pressed according to the \ref keyAssignTable
 * table.
 */

#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "gmaDefines.h"

#include "appList.h"
#include "appInit.h"
#include "gmaMsg.h"
#include "gmaMsgCon.h"
#include "gmaMsgSup.h"
#include "gmaAppMsg.h"
#include "gmaHmiProcess.h"
#include "gmaHmiCustom.h"
#include "gmaGenCustom.h"
#include "gmaPrnCustom.h"
#include "gmaCustomSemaphores.h"
#include "gmaCustomUtil.h"
#include "gmaCLibDefines.h"
#include "gmaMenuResource.h"

//#define DEBUG_ON
#include "debugLib.h"

#ifdef WIN32
#define DEBUG_TARGET DEBUG_PRN
#else
#define DEBUG_TARGET DEBUG_PRN
//#define DEBUG_TARGET DEBUG_COM2
#endif

/**
 * Key changes to terminals 8200, 8500 and 8550
 */
s_keyAssignTable keyTableStyle1[] = 
{
   {HMI_KEY_F3, GMA_KEY_ACTION_NONE, 0, 0},
   {HMI_KEY_F2, GMA_KEY_ACTION_FUNCTION, GMA_KEY_FUNC_MENU, 0}
};

/**
 * Key changes to terminal 6550
 */
s_keyAssignTable keyTableStyle2[] = 
{
   {HMI_KEY_F3, GMA_KEY_ACTION_NONE, 0, 0},
   {'0', GMA_KEY_ACTION_FUNCTION, GMA_KEY_FUNC_MENU, 0}
};

/**
 * Key changes to terminal 9530
 */
s_keyAssignTable keyTableStyle3[] = 
{
   {HMI_KEY_F9, GMA_KEY_ACTION_FUNCTION, GMA_KEY_FUNC_MENU, 0},  // Arrow up
   {HMI_KEY_F8, GMA_KEY_ACTION_FUNCTION, GMA_KEY_FUNC_TECHNICAL, 0}  // Arrow down
};


/**
 * Key changes between terminals.
 * Each 'termiKeyChange' element of the array matches a specific keyboard
 * type. The element #i matches keyboard #i, keyboard values being defined
 * in gmaCustomUtil.h (GMA_UTIL_KEYBOARD_xxx).
 */
struct termiKeyChange_s
{
   uint8 keyTableSize;
   s_keyAssignTable *keyTable;
} termiKeyChange[] = 
{
   {0, NULL},
   {sizeof(keyTableStyle1)/sizeof(s_keyAssignTable), keyTableStyle1},
   {sizeof(keyTableStyle2)/sizeof(s_keyAssignTable), keyTableStyle2},
   {sizeof(keyTableStyle3)/sizeof(s_keyAssignTable), keyTableStyle3}
};

const uint16 n_termKeyChangeTable = sizeof(termiKeyChange)/sizeof(struct termiKeyChange_s);

/**
 * Key table that defines the action for each key
 */
s_keyAssignTable keyAssignTable[] = 
{
    {'0'                , GMA_KEY_ACTION_NONE,     0 , 0,    0},
    {'1'                , GMA_KEY_ACTION_NONE,     0 , 0,    0},
    {'2'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'3'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'4'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'5'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'6'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'7'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'8'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {'9'                , GMA_KEY_ACTION_NONE      , 0,    0},
    {HMI_KEY_ENTER      , GMA_KEY_ACTION_NONE      , 0,    0},
    {HMI_KEY_CLEAR      , GMA_KEY_ACTION_NONE      , 0,    0},
    {HMI_KEY_BCKSP      , GMA_KEY_ACTION_NONE      , 0,    0},
    {HMI_KEY_00_PT      , GMA_KEY_ACTION_FUNCTION  , GMA_KEY_FUNC_TECHNICAL,    0},
    {HMI_KEY_PAPER_FEED , GMA_KEY_ACTION_FUNCTION  , GMA_KEY_FUNC_PAPER_FEED, 0},
    {HMI_KEY_F1         , GMA_KEY_ACTION_NONE   , 0,    0},
    {HMI_KEY_F2         , GMA_KEY_ACTION_NONE   , 0,    0},
    {HMI_KEY_F3         , GMA_KEY_ACTION_FUNCTION  , GMA_KEY_FUNC_MENU,       0},
    {HMI_KEY_F4         , GMA_KEY_ACTION_NONE      , 0,    0}, //Up arrow
    {HMI_KEY_F5         , GMA_KEY_ACTION_NONE      , 0,    0}, //Left arrow
    {HMI_KEY_F6         , GMA_KEY_ACTION_NONE      , 0,    0}, //Center arrow
    {HMI_KEY_F7         , GMA_KEY_ACTION_NONE      , 0,    0}, //Right arrow
    {HMI_KEY_F8         , GMA_KEY_ACTION_NONE      , 0,    0},  //Down arrow
    {HMI_KEY_F9         , GMA_KEY_ACTION_NONE      , 0,    0},
    {0,                   0, 0, 0}
};

static int16 gmaHmiKeyFunction(uint8 function);
static int16 gmaHmiKeyNotify(uint16 appID, uint8 logApp, uint8 keyPressed);
static int16 gmaHmiKeyDefault(uint8 keyPressed);
static int16 gmaHmiKeyFuncMenu(void);
static int16 gmaHmiKeyFuncFF(void);


/**
 * Change the specific keys for this terminal
 */
void gmaHmiUtilSetSpecKeys(void)
{
   uint16 keyboardType = (uint16)gmaUtilGetKeyboardType();
   s_keyAssignTable *keyTable;
   uint16 keyTableSize;
   uint16 i;
   
   if(keyboardType >= n_termKeyChangeTable)
   	return;
   
   keyTable = termiKeyChange[keyboardType].keyTable;
   keyTableSize = termiKeyChange[keyboardType].keyTableSize;
   
   for(i=0; i<keyTableSize; i++)
   {
      gmaHmiKeyChangeTable(keyTable[i].keyVal, keyTable[i].action, 
            keyTable[i].parameter, keyTable[i].appID);
   }
}


/**
 * Change an entry in the key table
 *
 * @param keyVal the code of the key to be changed
 *
 * @param action the new action to be performed by this key. See the 
 * \ref gmaPGSendKeyboardConfigMsg
 *
 * @param parameter the new parameter for this key. See the \ref gmaPGSendKeyboardConfigMsg
 *
 * @param appID the application Id that send the request for change the behaviour 
 * of this key.
 */
int16 gmaHmiKeyChangeTable(uint8 keyVal, uint8 action, uint8 parameter, uint16 appID)
{
   uint8 size = (sizeof (keyAssignTable) / sizeof (s_keyAssignTable));
   uint8 i;
   
   for (i = 0; i < size; i++)
   {
   	  if (keyAssignTable[i].keyVal == keyVal)
   	  {
   	     break;
   	  }
   }
   if (i < size)
   {
   	  keyAssignTable[i].action = action;
   	  keyAssignTable[i].parameter = parameter;
   	  keyAssignTable[i].appID = appID;
   	  return RET_OK;
   }
   return -1;
}

/**
 * This function is called in custom module.
 * It will execute the action related to the key pressed.
 *
 * @param keyPress the key pressed
 */
int16 gmaHmiKeyProcess(char keyPress)
{
	uint8 index;
	int16 retVal = RET_OK;

	s_keyAssignTable locLine;
   IFDEBUG(debugPrintf(DEBUG_TARGET, "keyPress = %d", keyPress));
	gmaCustomSemaphoreAcquire(GMA_CUSTOM_SEMAPHORE_KEY_TABLE);

	for (index=0;index<SZ_KEY_ASSIGN_TABLE-1;index++)
		if (keyAssignTable[index].keyVal == keyPress)
			break;

   if(keyAssignTable[index].keyVal == 0)
   {
  		gmaCustomSemaphoreRelease(GMA_CUSTOM_SEMAPHORE_KEY_TABLE);
      return retVal;
   }

   IFDEBUG(debugPrintf(DEBUG_TARGET, "index = %d", index));
   
	memcpy(&locLine, &keyAssignTable[index], sizeof(s_keyAssignTable));
   IFDEBUG(debugPrintf(DEBUG_TARGET, "locLine.action = %d", locLine.action));
   IFDEBUG(debugPrintf(DEBUG_TARGET, "locLine.action = %d", locLine.parameter));
	gmaCustomSemaphoreRelease(GMA_CUSTOM_SEMAPHORE_KEY_TABLE);

	//	ASSERT (index<SZ_KEY_ASSIGN_TABLE);
   
   

	switch (locLine.action)
	{
		case GMA_KEY_ACTION_FUNCTION:
         IFDEBUG(debugPrintf(DEBUG_TARGET, "Entering function"));
         retVal = gmaHmiKeyFunction (locLine.parameter);
         break;
			
		case GMA_KEY_ACTION_NOTIFY:
         gmaCustomUtilBLEnable(BACKLIGHT_NONE);
		   retVal = gmaHmiKeyNotify (locLine.appID, locLine.parameter, keyPress);
         gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			break;

		case GMA_KEY_ACTION_DEFAULT:
         gmaCustomUtilBLEnable(BACKLIGHT_NONE);
		   retVal = gmaHmiKeyDefault (keyPress);
         gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			break;
			
		default:
			gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			break;
	}
   
	return retVal;
}

/**
 * Process the touch screen action
 */
void gmaHmiTouchProcess(uint8 pluginId, uint16 appId,uint16 action, uint16 parameter)
{
	int16 retVal;
	
	gmaHmiSupCancel();
	
	switch (action)
	{
		case GMA_KEY_ACTION_FUNCTION:
         IFDEBUG(debugPrintf(DEBUG_TARGET, "Entering function"));
         retVal = gmaHmiKeyFunction (parameter);
         break;
			
		case GMA_KEY_ACTION_NOTIFY:
         gmaCustomUtilBLEnable(BACKLIGHT_NONE);
		   retVal = gmaHmiKeyNotify (appId, pluginId, parameter);
         gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			break;
		case GMA_KEY_ACTION_TOUCH_KEY:
			gmaHmiKeyProcess(parameter);
			break;
			
	}
}


/**
 * Execute a function when the action of a key is \ref GMA_KEY_ACTION_FUNCTION
 *
 * @param function the action function. Could be \ref GMA_KEY_FUNC_MENU,
 * \ref GMA_KEY_FUNC_PAPER_FEED or GMA_KEY_FUNC_TECHNICAL.
 */
static int16 gmaHmiKeyFunction(uint8 function)
{
	int16 retVal;
   IFDEBUG(debugPrintf(DEBUG_TARGET, "Function = %d", function));	
	switch (function)
	{
		case GMA_KEY_FUNC_MENU:
            gmaCustomUtilBLEnable(BACKLIGHT_NONE);
			retVal = gmaHmiKeyFuncMenu();
            gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			break;
			
		case GMA_KEY_FUNC_PAPER_FEED:
		    gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			retVal = gmaHmiKeyFuncFF();
			break;

		case GMA_KEY_FUNC_TECHNICAL:
         
         gmaCustomUtilBLEnable(BACKLIGHT_NONE);

         retVal = gmaTecFunDisplayPGMenu();
         gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			break;
			
		default:
			gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
			retVal = RET_OK;
			break;
	}

	return retVal;
}

/**
 * 
 */
static int16 gmaHmiShowResMenu(uint16 *sel, char *appName, uint8 logicalId)
{
	uint8 i;
	int16 ret;
	char *entries[10];
	char buffer[10*20];
	uint16 action[10];
	
	uint8 entryNumber;
	uint8 choice;
	char path[50];
	char *pathPtr;
	
	
	memset(path, 0, sizeof(path));
	
	for(i=0;i<10;i++)
	{
		entries[i] = &buffer[i*20];
	}
	
	while(42)
	{
		if(path[0] == 0)
		{
			pathPtr = NULL;
		}
		else
		{
			pathPtr = path;
		}

		gmaMRESGetMenuEntries(pathPtr, entries, action, &entryNumber, logicalId);
		
		// need to show the menu
		
		if(entryNumber != 0)
		{	
			choice = 0;
			ret = gmaHmiMenu (appName, (const char **)entries, entryNumber, &choice, 3000);
			if(ret != RET_OK)
				return ret;
		
			if(action[choice] != 0xFFFF)
			{
				*sel = action[choice];
				return RET_OK;
			}
			
			if(strlen(path)!=0)
			{
				strcat(path, ".");
			}
			strcat(path,entries[choice]);
		}
		else
		{
			*sel = 0;
			return RET_OK;
		}
	}
	
	return ret;
}

/**
 * Execute the menu function. A list of all logical applications
 * is shown.
 */
static int16 gmaHmiKeyFuncMenu(void)
{
	gmaAppListLogicalData_t* pAppData;
	gmaAppListPhysicalData_t *pPhyAppData;
	uint16 indexList[GMA_APP_LIST_LOGICAL_APP_NUMBER];
	uint16 index = 0;
	uint16 count = 0;
	int16  retVal;
	amgMsg_t defaultMsg;
	amgMsg_t responseMsg;


	while(gmaAppListGetLogicalEntryFromInd(index, &pAppData)==RET_OK)
	{
		if (gmaCustomGetAppType (pAppData->appId)==GMA_USER_APPLICATION)
		{
			indexList[count] = index;
			count++;
		}
		index++;
	}

	retVal = gmaCustomAppMenu (indexList, count);

	if (retVal == RET_OK)
	{
		count = 0xFFFF;
		gmaAppListGetLogicalEntryFromInd(indexList[0], &pAppData);
		
		// now we get the logical application selected. We need to check if it is
		// required to show a menu based in the application resource or not.
		gmaAppListGetAppEntryFromId(pAppData->appId, &pPhyAppData);
		
		if(gmaMRESGetMnuResAppShowStatus(pAppData->appId, pAppData->logicalId) == 1)
		{
			retVal = gmaMRESinitialize(pPhyAppData->dfsName);
			if(retVal == RET_OK)
			{
				gmaHmiShowResMenu(&count, pAppData->name, pAppData->logicalId);
			}
		}
		
	   gmaHmiClose();

		gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION);
		gmaMsgSetLogicalId(pAppData->logicalId);
		gmaMsgAddTransType(pAppData->logicalId, GMA_TRANS_MENU);
		gmaMsgsAddTransMenu(count);
		gmaMsgEndEncode();
		gmaAppMsgWakeApp(pAppData->appId, pAppData->logicalId, &defaultMsg, &responseMsg);

		gmaInitProcessResponse(pAppData->appId, &responseMsg);
		
		gmaHmiOpen();
	}
	
	return RET_OK;
}

/**
 * Execute the paper feed function
 */
static int16 gmaHmiKeyFuncFF(void)
{

	gmaPrnLineFeed (1);
	return RET_OK;
}

/**
 * A key is pressed and the action is \ref GMA_KEY_ACTION_NOTIFY.
 * A notification is sent to the plugin that change the behaviour of this key.
 *
 * @param appID the application Id of the plugin that request this key.
 *
 * @param logApp the plugin Id that request this key.
 *
 * @param keyPressed the key pressed.
 */
static int16 gmaHmiKeyNotify(uint16 appID, uint8 logApp, uint8 keyPressed)
{
	amgMsg_t defaultMsg;
	amgMsg_t responseMsg;
	
	gmaHmiClose();

	gmaMsgEncode(&defaultMsg, GMA_MSG_PG_NOTIFY);
   gmaMsgSetLogicalId(logApp);
	gmaMsgAddNotificationType(logApp, GMA_NOTIFICATION_KEY_PRESS, keyPressed);
	gmaMsgsAddTransKeyPressed(keyPressed);
	gmaMsgEndEncode();
	gmaAppMsgWakeApp(appID, logApp, &defaultMsg, &responseMsg);

	gmaInitProcessResponse(appID, &responseMsg);
	
	gmaHmiOpen();
	
	return RET_OK;
}


/**
 * A key is pressed and the action is \ref GMA_KEY_ACTION_DEFAULT.
 *
 * The treatment is generate a key press transaction
 */
static int16 gmaHmiKeyDefault(uint8 keyPressed)
{
	amgMsg_t defaultMsg;
	amgMsg_t responseMsg;
	uint8*   answer;
	int16    appSel;
	uint16   appID; 
	uint8    logicalID;
	
	gmaHmiClose();

	gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION_QUERY);
   gmaMsgSetLogicalId(0xFF);
	gmaMsgAddTransType(0xFF, GMA_TRANS_KEY_PRESSED);
	gmaMsgsAddTransKeyPressed(keyPressed);
	gmaMsgEndEncode();
	
	
	gmaAppMsgQueryDriven (&defaultMsg, &answer);
	
	gmaHmiOpen();
	appSel = gmaCustomSelectApp(answer, &appID, &logicalID);
	gmaHmiClose();

	if (appSel >= 0)
	{
		gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION);
      gmaMsgSetLogicalId(logicalID);
		gmaMsgAddTransType(logicalID, GMA_TRANS_KEY_PRESSED);
		gmaMsgsAddTransKeyPressed(keyPressed);
		gmaMsgEndEncode();
		gmaAppMsgWakeApp(appID, logicalID, &defaultMsg, &responseMsg);
		gmaInitProcessResponse(appID, &responseMsg);
	}

	gmaHmiOpen();

	return RET_OK;
}

/**
 * Treat the message to update a key entry in the key table
 *
 * @param appId the application id of the plugin that sends this request
 *
 * @param msg the message that the plugin send, must be of type \ref gmaStructPGKeyboardCfg_t.
 */
int16 gmaHmiKeyTableUpdate(uint16 appId, gmaStructHeader_t* msg)
{
	gmaStructPGKeyboardCfg_t* pKeyCfgData;
	uint8 index;

	gmaCustomSemaphoreAcquire(GMA_CUSTOM_SEMAPHORE_KEY_TABLE);

	pKeyCfgData = (gmaStructPGKeyboardCfg_t*)(msg);

	for (index=0;index<SZ_KEY_ASSIGN_TABLE;index++)
		if (pKeyCfgData->key == keyAssignTable[index].keyVal)
			break;

	if (index==SZ_KEY_ASSIGN_TABLE)
	{
		gmaCustomSemaphoreRelease(GMA_CUSTOM_SEMAPHORE_KEY_TABLE);
		return (-1);	//	definir retorno em caso de erro
	}

	keyAssignTable[index].action = pKeyCfgData->action;

	if (keyAssignTable[index].action == GMA_KEY_ACTION_FUNCTION)
		keyAssignTable[index].parameter = pKeyCfgData->parameter;
	
	else if (keyAssignTable[index].action == GMA_KEY_ACTION_NOTIFY)
		keyAssignTable[index].parameter = pKeyCfgData->pluginId;
	
	else
		keyAssignTable[index].parameter = pKeyCfgData->pluginId;

	if (keyAssignTable[index].action == GMA_KEY_ACTION_NOTIFY)
		keyAssignTable[index].appID = appId;
	else
		keyAssignTable[index].appID = NULL;

	gmaCustomSemaphoreRelease(GMA_CUSTOM_SEMAPHORE_KEY_TABLE);

	return RET_OK;

}



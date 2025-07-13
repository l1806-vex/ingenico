
/** @file gmaGenCustom.c
 * 
 *
 * This file gathers some generic functions, not related to a specific task,
 * they may be used in different parts of the code
 * 
 * - gmaCustomAppMenu
 * - gmaCustomGetAppType
 * - gmaCustomSelectApp
 *
 *	Their prototypes are in "gmaGenCustom.h"
 * 
 *	Any new custom function that may be called from different parts of the
 * application must be placed here. This file has no handle in it.
 *
 */


#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "AppList.h"
#include "gmaDefines.h"
#include "gmaMsg.h"
#include "gmaMsgSup.h"
#include "gmaAppMsg.h"

#include "gmaCustomDefines.h"
#include "gmaGenCustom.h"
#include "gmaHmiCustom.h"
#include "resources.h"
#include "gmaCustomUtil.h"


#include "debuglib.h"

static uint32 timerId = 0;

/**
 * 
 */
int16 gmaCustomSelectApp(uint8* acceptLevel, uint16* appID, uint8* logicalID)
{
	uint16 maxIndex[GMA_APP_LIST_LOGICAL_APP_NUMBER];

	uint16 numMax = 0;
	uint16 offset = 0;
	uint8  maxLevel = 1;
	gmaAppListLogicalData_t* pointer;
	int16 ret = GMA_MAG_SELECTION_NONE;

	while (gmaAppListGetLogicalEntryFromInd(offset, &pointer) == RET_OK)
	{
		
		
		if (acceptLevel[offset]>maxLevel)
		{
			maxLevel = acceptLevel[offset];
			memset (maxIndex, 0, 10);
			maxIndex[0] = offset;
			numMax = 1;
		}
		else if (acceptLevel[offset]==maxLevel)
		{
			maxIndex[numMax] = offset;
			numMax++;
		}

		offset++;
	}

	if (numMax)
	{
		if (numMax != 1)
		{
			if (gmaCustomAppMenu (maxIndex, numMax)!=RET_OK)
				return GMA_NO_FUNC_SELECTED;
			else
				ret = GMA_MAG_SELECTION_MENU;
		}
		else
			ret = GMA_MAG_SELECTION_QUERY;
		
		if (offset == 2)
			ret = GMA_MAG_SELECTION_NONE;

		gmaAppListGetLogicalEntryFromInd(maxIndex[0], &pointer);
		*logicalID = pointer->logicalId;
		*appID = pointer->appId;
		return ret;
	}

	return GMA_NO_FUNC_AVAILABLE;

}


static uint8 _menuOneItemBehaviour = 0;
/**
 * Set if show or not the menu when only one item
 *
 */
void gmaCustomGenSettMnOneItemBeh(uint8 behaviour)
{
   _menuOneItemBehaviour = behaviour;
}

/**
 * Show a menu to select one application with the applications
 * in the indexList vector.
 */
int16 gmaCustomAppMenu(uint16* indexList, uint16 length)
{
	gmaAppListLogicalData_t* pAppData;
	uint8* itemList[GMA_APP_LIST_LOGICAL_APP_NUMBER];
	uint16 index;
	uint8 menuSel;
	uint16 appSel;
	int16 retVal = GMA_NO_FUNC_SELECTED;

	if (length != 0)
	{
		for (index=0;index<length;index++)
		{
			gmaAppListGetLogicalEntryFromInd(indexList[index], &pAppData);
			itemList[index] = (uint8 *)pAppData->name;
		}
      if(length > 1 || _menuOneItemBehaviour == 1)
      {
      	menuSel = 0;
         retVal = gmaHmiMenu(gmaGetStringResource(GMA_APP_MENU_TITLE), (const char**)itemList, (uint8)length, &menuSel, GMA_APP_MENU_TIMEOUT);
      }
      else
      {
         retVal = RET_OK;
         menuSel = 0;
      }

		if (retVal == RET_OK)
		{
			appSel = indexList[menuSel];
			indexList[0] = appSel;
		}
	}
	
	return retVal;

}

/**
 * Return if the application with appId is a plugin or 
 * a user application
 */
uint8 gmaCustomGetAppType (uint16 appId)
{
	int16 index;
	gmaAppListPhysicalData_t* pAppData;
	
	index = gmaAppListGetIndexFromAppId(appId);
	
	index = gmaAppListGetAppEntryFromInd(index, &pAppData);

	if (index == RET_OK)
		return pAppData->type;

	return GMA_APPLICATION_TYPE_ERROR;
	
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////



static uint8 statusBLE = 1;
static uint32 timeoutBLE = 1000;
static psyTime_t lastSetBacklight = 0;

/**
 * 
 */
void gmaCustomUtilConfigBLE(uint8 status, uint32 timeout)
{
   statusBLE = status;
   
   timeoutBLE = timeout;
}

/**
 * Disable the back light
 *
 */
void gmaCustomUtilBLDisable (void)
{
	psyTime_t actualTime;
	uint32 diff;
   IFDEBUG(
      debugPrintf(DEBUG_PRN, "Backlight off")
   );
   psyTimeGet(&actualTime);
   
   diff = (uint32) (actualTime - lastSetBacklight);
   //check if it is realy what need to be done
   if(diff < timeoutBLE)
   {
   	if (timerId != 0)
	   {
	      psyTimerCancel (timerId);
	      timerId = 0;
	   }
	   psyTimerEventAfter ((uint32) timeoutBLE - diff, EVENT_5, &timerId);
   	return;
   }
   
   if (timerId != 0)
   {
      psyTimerCancel (timerId);
      timerId = 0;
   }
   gmaHmiBackLight (0);
}

/**
 * Enable the back light
 *
 * 
 * @param timeout the period the back ligth will be on.
 */
void gmaCustomUtilBLEnable (uint32 timeout)
{
   IFDEBUG(
      debugPrintf(DEBUG_COM1, "Backlight on (%d)", timeout)
   );
   if(statusBLE != 0)
   {
	   if (timerId != 0)
	   {
	      psyTimerCancel (timerId);
	      timerId = 0;
	   }
	   if (timeout != BACKLIGHT_NONE)
	   {
	   	psyTimeGet(&lastSetBacklight);
	      psyTimerEventAfter ((uint32) timeoutBLE, EVENT_5, &timerId);
	   }
	   IFDEBUG(debugPrintf(DEBUG_COM1, "Backlight on (%d)", timeout));
	   
	   gmaHmiBackLight (100);
   }
   else
   {
   	gmaHmiBackLight (0);
   }
}

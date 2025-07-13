#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "unicapt.h"

#include "gmaMenuResource.h"
#include "resources.h"

#include "appList.h"


//#define DEBUG_ON
#include "debuglib.h"




static char menuStr[1024];

/**
 * This function read the MENU RESOURCE MODULE from the resource file
 * This function should be called prior to other functions
 */
int16 gmaMRESinitialize(char *appName)
{
	int16 ret;
	memset(menuStr, 0, sizeof(menuStr));
	amgSetLanguage(LANGUAGE_EN);
	ret = amgModuleGet(appName, AMG_MENU_MODULE, sizeof(menuStr), menuStr);
	IFDEBUG(debugPrintf(DEBUG_PRN, "amgModuleGet = %d", ret));
	if(ret != RET_OK)
		return ret;
	
	return RET_OK;	
}

static uint16 posLine = 0;

static void getLineStart(void)
{
	for(posLine = 0; menuStr[posLine] != '\n' && menuStr[posLine] != 0; posLine++);
	if(menuStr[posLine] == '\n')
		posLine++;
}

static int16 getNextLine(char *path, char *entry, uint16 *value, uint8 *hasSubMenu)
{
	uint16 i;

	char *entryPtr;
	char strTemp[6];
	*value=0;
	*hasSubMenu = 0;
	if(path!= NULL)
	{
		// check if path is ok
		while(42)
		{
			if(memcmp(&menuStr[posLine], path, strlen(path)) != 0)
			{
				for(;menuStr[posLine] != '\n' && menuStr[posLine] != 0; posLine++);
				if(menuStr[posLine] == '\n')
				{
					posLine++;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				break;
			}
		}
		
		// jump the path
		posLine+= strlen(path) + 1; // jump the period
	}
	entryPtr = entry;
	for(i=posLine;menuStr[i]!='.' && menuStr[i]!=',' && menuStr[i] != 0; i++)
	{
		*(entryPtr++) = menuStr[i];
	}
	if(menuStr[i] == 0)
		return -1;
	*entryPtr = 0;
	if(menuStr[i]=='.')
	{
		*hasSubMenu = 1; // there is submenu
	}
	
	for(;menuStr[i]!=',';i++);
	i++;
	entryPtr = strTemp;
	for(;menuStr[i]!='\r';i++)
	{
		*(entryPtr++) = menuStr[i];
	}
	*entryPtr=0;
	
	*value = atoi(strTemp);
	posLine = i+2;
	return RET_OK;
}

/**
 * Get the menu entries to be shown
 */
int16 gmaMRESGetMenuEntries(char *path, char **entries, uint16 *actions, uint8 *entryNumber, uint8 logicalId)
{
	int16 ret;
	char actualEntry[20];
	char lastEntry[20];
	uint8 hasSubMenu;
	uint16 action;
	getLineStart();
	memset(lastEntry,0,sizeof(lastEntry));
	*entryNumber = 0;
	
	while(42)
	{
		ret = getNextLine(path, actualEntry, &action, &hasSubMenu);
		if(ret!= RET_OK)
		{
			return RET_OK;
		}
		
		if(strcmp(actualEntry, lastEntry) != 0)
		{
			if(logicalId == 0 || logicalId == 0xFF ||
			   ( (((logicalId-1)*100 <= action) && (logicalId*100 > action))) || logicalId == 0 )
			{
				IFDEBUG(debugPrintf(DEBUG_PRN, "ent=%s-action=%d (%d)", actualEntry, action, hasSubMenu));
				strcpy(entries[*entryNumber], actualEntry);
				if(hasSubMenu == 0)
				{
					actions[*entryNumber] = action;
				}
				else
				{
					actions[*entryNumber] = 0xFFFF;
				}
				(*entryNumber)++;
				strcpy(lastEntry, actualEntry);
			}
		}
	}
	
	return RET_OK;
}


static uint8 mnuResAppShow[(GMA_APP_LIST_LOGICAL_APP_NUMBER + 7) / 8];

/**
 * 
 */
void gmaMRESInitialize(void)
{
	memset(mnuResAppShow, 0, sizeof(mnuResAppShow));
	
}


/**
 * 
 */
void gmaMRESSetMnuResAppShowStatus(uint16 appId, uint8 logicalId, uint8 status)
{
	uint8 index;
	uint8 value;
	gmaAppListLogicalData_t *appLog;
	
	for(index = 0; gmaAppListGetLogicalEntryFromInd(index, &appLog) == RET_OK; index++)
	{
		if(appLog->appId == appId && (appLog->logicalId == logicalId || logicalId == 0 
		|| logicalId == GMA_APP_LIST_LOGICAL_ID_DEFAULT))
		{
			
			value = 1 << (index % 8);
			
			if(status)
			{
				mnuResAppShow[index/8] |= value;
			}
			else
			{
				mnuResAppShow[index/8] &= ~value;
			}
		}
	}
}

/**
 * 
 */
int16 gmaMRESGetMnuResAppShowStatus(uint16 appId, uint8 logicalId)
{
	uint8 index;
	uint8 found = 0;
	uint8 value;
	
	gmaAppListLogicalData_t *appLog;
	
	for(index = 0; gmaAppListGetLogicalEntryFromInd(index, &appLog) == RET_OK; index++)
	{
		if(appLog->appId == appId && appLog->logicalId == logicalId)
		{
			found = 1;
			break;
		}
	}
	if(found == 0)
		return -1;
	
	value = 1 << (index % 8);
	
	if(mnuResAppShow[index/8] & value)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}


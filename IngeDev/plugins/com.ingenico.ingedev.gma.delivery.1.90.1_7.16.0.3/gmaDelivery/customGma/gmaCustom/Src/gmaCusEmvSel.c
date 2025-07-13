#include <stdlib.h>
#include <string.h>

#include <unicapt.h>
#include "applist.h"
#include "gmaCusEmvSel.h"

//#define DEBUG_ON
#include "debuglib.h"


struct gmaCusEmvSelList_st
{
	amgAid_t aid;
	uint16   appId;
	uint8    logicalId;
	uint8    used;
};

struct gmaCusEmvSelList_st gmaCusEmvSelList[64]; 

void gmaEmvSelInitialize(void)
{
	memset(gmaCusEmvSelList, 0, sizeof(gmaCusEmvSelList));
}

/**
 * Add a new AID for the application appId, logicalId
 */
int16 gmaEmvSelAddAid(uint16 appId, uint8 logicalId, amgAid_t *aid)
{
	uint32 i;
	for(i=0; i<(sizeof(gmaCusEmvSelList)/sizeof(gmaCusEmvSelList[0])); i++)
	{
		if(gmaCusEmvSelList[i].used == 0)
		{
			memcpy(&(gmaCusEmvSelList[i].aid),aid, sizeof(amgAid_t));
			gmaCusEmvSelList[i].used = 1;
			gmaCusEmvSelList[i].appId = appId;
			gmaCusEmvSelList[i].logicalId = logicalId;
			return RET_OK;
		}
	}
	return -1;
}

/**
 * Delete the AID list for the appId
 */
int16 gmaEmvSelDelAids(uint16 appId, uint8 logicalId)
{
	uint32 i;
	
	for(i=0; i<(sizeof(gmaCusEmvSelList)/sizeof(gmaCusEmvSelList[0])); i++)
	{
		if(gmaCusEmvSelList[i].used != 0 && gmaCusEmvSelList[i].appId == appId)
		{
			if(logicalId == 0xFF || logicalId == gmaCusEmvSelList[i].logicalId)
			{
				gmaCusEmvSelList[i].used = 0;
			}
		}
	}
	return RET_OK;
}

/**
 * Call the function amgSelectionCriteriaAdd to add the AIDs to the AMG,
 * to prepare the selection process
 */
int16 gmaEmvSelAddNow(void)
{
	uint16 i = 0;
	uint16 j;
	uint16 k;
	gmaAppListPhysicalData_t *app;
	
	struct sAidList{
     uint16   TermAppID;
     uint8    TermAppName[16];
     uint8    AddTermCapp[2];
     amgAid_t tbAid[20];
   } crit;
	
	IFDEBUG(debugPrintf(DEBUG_PRN, "sizeof(crit)=%d", sizeof(crit)));
	IFDEBUG(debugPrintf(DEBUG_PRN, "sizeof(amgAid_t)=%d", sizeof(amgAid_t)));
	
	while(gmaAppListGetAppEntryFromInd(i++, &app) == RET_OK)
	{
		crit.TermAppID = app->pid;
		memcpy(crit.AddTermCapp, "\x00\x01", 2);
		memcpy(crit.TermAppName, app->name, 16);
		k=0;
		for(j=0; j<(sizeof(gmaCusEmvSelList)/sizeof(gmaCusEmvSelList[0])); j++)
		{
			if(gmaCusEmvSelList[j].used != 0 && gmaCusEmvSelList[j].appId == app->appId)
			{
				memcpy(&(crit.tbAid[k]), &(gmaCusEmvSelList[j].aid), sizeof(amgAid_t));
				k++;
			}
		}
		if(k>0)
		{
			IFDEBUG(debugPrintf(DEBUG_COM1, "amgSelectionCriteriaAdd"));
			IFDEBUG(debugPrintf(DEBUG_COM1, "appId=%d", crit.TermAppID));
			IFDEBUG(debugPrintf(DEBUG_COM1, "number=%d", k));
			
			amgSelectionCriteriaAdd(T_AID, 20 + sizeof(amgAid_t)*k, &crit);
		}
		
	}
	return RET_OK;
}




/**
 * @file gmaMagProcess.c
 *
 * Process a magnetic card data.
 */

#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "gmaDefines.h"
#include "appInit.h"

#include "gmaMsg.h"
#include "gmaMsgSup.h"
#include "gmaMsgCon.h"
#include "gmaAppMsg.h"

#include "smcSupport.h"
#include "gmaMagCustom.h"
#include "gmaGenCustom.h"
#include "gmaHmiCustom.h"
#include "gmaCustomUtil.h"
#include "resources.h"

/**
 * Analyze magnetic card swiped.  (Add by B.K)
 *
 * RET_OK : Track's data was red successfully 
 * MAG_ERR_DURING_SWIPE : Track's data was garbeled and NOT red
 * Return ISO1-ISO2-ISO3 if exists
 */
static int16 gmaGetTracks (magTripleResult_t* magStripe, uint8 appSelection )
{
	uint8  magType;
	uint8  index;

	for (index=0; index<magStripe->numberOfResults; index++)
	{
		// Get Mag Type
		switch (magStripe->mag_resultAvailableTrack[index].isoTrackNumber)
		{ 
		case MAG_ISO1: case MAG_ISO2: case MAG_ISO3: magType = GMA_MAG_TRACK_ISO; break;
		case MAG_AAMVA1: case MAG_AAMVA2: case MAG_AAMVA3: magType = GMA_MAG_TRACK_AAMVA; break;
        case MAG_CDL1: case MAG_CDL2: case MAG_CDL3: magType = GMA_MAG_TRACK_CDL; break;
        case MAG_ISOJIS: magType = GMA_MAG_TRACK_ISOJIS; break;
		default: return MAG_ERR_DURING_SWIPE;
		}

		// Check Error during Swipe
		if (magStripe->mag_resultAvailableTrack[index].isoStatus == MAG_ERR_DURING_SWIPE)
		{ 
			return MAG_ERR_DURING_SWIPE;
		}

		// Send Transaction Mag Card to Application 
		if (index==0)
			gmaMsgsAddTransMagCard(magType, appSelection);

		// Send Transaction Mag Track to Application
		gmaMsgsAddTransMagTrack((uint8)magStripe->mag_resultAvailableTrack[index].isoTrackNumber, 
								(uint8)magStripe->mag_resultAvailableTrack[index].isoLength, 
								 magStripe->mag_resultAvailableTrack[index].isoTrack);
     
	}

    return RET_OK;
}

/**
 * Process the magnetic card that was sweaped.
 *
 * Send a query to all application to see which application
 * can treat this transaction, and then send the transaction
 * to this application
 */
int16 gmaMagCrdProcess (magTripleResult_t* magStripe)
{
	amgMsg_t defaultMsg;
	amgMsg_t responseMsg;
	uint8*   answer;
	int16    appSel;
	uint16   appID; 
	uint8    logicalID;
	int16    ret;
	
	ret = gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION_QUERY);
   gmaMsgSetLogicalId(0xFF);
	gmaMsgAddTransType(0xFF, GMA_TRANS_MAG_CARD);
	
	ret = gmaGetTracks (magStripe, GMA_MAG_SELECTION_NONE);
	
	if(ret != RET_OK)
	{
		gmaHmiClearLine(HMI_ALL_LINES);
	   gmaHmiSetFont(HMI_INTERNAL_FONT_2);
	   gmaHmiAutoCentre(1);
 	   gmaHmiDisplayText(1, 0, gmaGetStringResource(IDS_UNREADABLE_CARD_1));//IDS_UNREADABLE_CARD_1
	   gmaHmiDisplayText(2, 0, gmaGetStringResource(IDS_UNREADABLE_CARD_2)); //IDS_UNREADABLE_CARD_2
	   gmaHmiAutoCentre(0);
	   psyTimerWakeAfter(2*100);
		gmaMsgEndEncode(); 
		return ret;
	}
	
	// check if the fallback is enabled and add this information to the structure fall back enabled
	smcSupAddFallBackMsg();
	
	gmaMsgEndEncode();

	gmaAppMsgQueryDriven (&defaultMsg, &answer);

	appSel = gmaCustomSelectApp(answer, &appID, &logicalID);

	if (appSel >= 0)
	{
		gmaMsgEncode(&defaultMsg, GMA_MSG_TRANSACTION);
      gmaMsgSetLogicalId(logicalID);
		gmaMsgAddTransType(logicalID, GMA_TRANS_MAG_CARD);

        if ((ret = gmaGetTracks (magStripe, (uint8)appSel)) != RET_OK)    // Selection None, Menu and Query B.K
        {
             gmaMsgEndEncode(); 
             return ret;
        }
	
		// check if the fallback is enabled and add this information to the structure fall back enabled
		smcSupAddFallBackMsg();
		
		gmaMsgEndEncode();
		gmaAppMsgWakeApp(appID, logicalID, &defaultMsg, &responseMsg);
		gmaInitProcessResponse(appID, &responseMsg);
	}
	
	// clear the fallback flag
	smcSupClearFallback();
	
	return RET_OK;
}



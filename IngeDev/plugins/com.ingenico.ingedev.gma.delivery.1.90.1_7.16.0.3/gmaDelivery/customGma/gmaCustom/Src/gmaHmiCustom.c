
/**
 *  @file gmaHmiCustom.c
 *
 *
 * This file contains the functions wich will handle keyboard and display
 *	operations and need the HMI handle to operate:
 * 
 * - gmaHmiOpen
 * - gmaHmiClose
 * - gmaHmiKeyReq
 * - gmaHmiKeyResultGet
 * - gmaHmiMenu
 * - gmaHmiGraphUpdate
 *
 *	Their prototypes are in "gmaHmiCustom.h"
 * 
 *	Any new custom function that need the HMI handle may be placed in this
 * file. The function names shall start with 'gmaHmi'
 *
 *	Other functions related to 'human-machine interface' that don't need the 
 *	handle must be placed in the file \ref gmaHmiProcess.c
 *
 *	Functions related to the task of drawing the idle screen (graphiscs or
 *	text) shall be placed in the file \ref gmaHmiDisplay.c
 *
 */


#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "gmaDefines.h"

#ifdef GMA_USE_MENU_LIB_LIBRARY
#include "menuLib.h"
#else
#include "menuLiblaf.h"
#endif

#include "gmaHmiCustom.h"
#include "gmaCustomDefines.h"
#include "gmaMagCustom.h"
#include "SmcSupport.h"
#include "editLib.h"
#include "gmaCustomUtil.h"
#include "gmaUtil.h"
#include "gmaCusTouchScr.h"
#include "ssaStd.h"
#include "gmaHmiProcess.h"
//#define DEBUG_ON
#include "debuglib.h"

#ifdef WIN32
#define DEBUG_TARGET DEBUG_PRN
#else
#define DEBUG_TARGET DEBUG_PRN
#endif


static uint32 gHmiHandle; //=0
static uint8 beepStatus;


/**
 * Set the beep status
 */
void gmaHmiSetBeepStatus(uint8 status)
{
   beepStatus = status;
}

/**
 * Get the beep status
 */
uint8 gmaHmiGetBeepStatus(void)
{
	return beepStatus;
}

/**
 * This function is called from main custom call back module and will
 * make a key request
 */
int16 gmaHmiKeyReq (void)
{
   int16 status;
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   
   status = hmiKeyReq (gHmiHandle);
   if (status == RET_RUNNING || status == ERR_BUSY)
   {
	   // ERR_BUSY means a request has already been made.
	   return RET_RUNNING;
   }
   else
   {
	   return status;
   }
}

/**
 * This function read an asynchronous key request result.
 * This function is called in there is an available result in the HMI.
 */
int16 gmaHmiKeyResultGet (void)
{
	typedef struct 
	{ 
		int16 status;	//	Execution status 
		uint16 length;	//	Length of returned data
		uint8 data[1]; 	//	Key entered
	} keyResult_t; 

	int16 retVal;
	keyResult_t keyResult;
   
   if(!gHmiHandle)
      return -1;
   
	retVal = hmiResultGet(gHmiHandle, sizeof (keyResult), &keyResult);
	
	if (retVal == RET_OK)
	{
      IFDEBUG(debugPrintf(DEBUG_PRN, "key = %d", keyResult.data[0]));
		return keyResult.data[0];
	}
	

	return retVal;
}




/**
 * Opens the HMI handle and store the handle in a global variable
 *
 */
int16 gmaHmiOpen (void)
{
	int16 retVal;
	uint32 channels;

   if (!gHmiHandle)
   {
#ifndef GMA_USE_MENU_LIB_LIBRARY  
      mnuLafSecHandleClose();
#endif
      
      channels = HMI_CH_DISPLAY;
      if(gmaUtilHasKeyboard())
      {
      	channels |= HMI_CH_KEYBOARD;
      }
       
      do{
         //retVal = hmiOpen("DEFAULT", &gHmiHandle);
         retVal = hmiOpenShared("DEFAULT", &gHmiHandle, channels, NULL);
         
         if(retVal != RET_OK)
         {
            psyTimerWakeAfter(30);
         }
      }while(retVal != RET_OK);
      
      if(beepStatus)
      {
          hmiInputConfig_t config;
          config.fields = HMI_INPUT_CONFIG_KEYCLICK_ENABLED;
          config.keyClick = TRUE;
          hmiInputConfigWrite(gHmiHandle, &config);
      }
		
		if (gmaUtilTermColor())
		{
			hmiGraphicBppSet (gHmiHandle, HMI_BPP_8);
		}
		else
		{
			hmiGraphicBppSet (gHmiHandle, HMI_BPP_1);
		}
		gmaDispInitConf (gHmiHandle);
		//hmiADFont(gHmiHandle, HMI_INTERNAL_FONT_1);
		return retVal;
    }
	
    return RET_OK;
}

/**
 * Close the HMI handle
 *
 */
int16 gmaHmiClose (void)
{
   int16 retVal;
   
#ifndef GMA_USE_MENU_LIB_LIBRARY  
   mnuLafSecHandleClose();
#endif
   
   if (gHmiHandle)
   {      
      retVal = hmiClose(gHmiHandle);
      
      if (retVal == RET_OK)
         gHmiHandle = 0;
      
      return retVal;
   }
   
   return RET_OK;
}


/**
 * This function draws a menu on the screen
 *
 * @param title the menu title
 *
 * @param itemList a vector with points to the menu item text strings.
 *
 * @param length the number of menu itens
 *
 * @param timeout the timeout of the menu
 *
 * @param choice a pointer to a uint8 that will receive the select menu item
 */
int16 gmaHmiMenu (const char* title, const char** itemList, uint8 length, uint8* choice, uint32 timeout)
{
   

	int16 i, retVal;
   
   
#ifdef GMA_USE_MENU_LIB_LIBRARY   
   
	mnuReset(gHmiHandle, gmaCTGetTouchHandle());

	if (title!=NULL)
		mnuSetTitle (title);
	else
		mnuSetTitle ("");

	
	mnuSetFont(GMA_APP_MENU_FONT);
	mnuSetTitleFont(GMA_APP_MENU_TITLE_FONT);
	mnuSetTimeout(timeout);

	for (i=0;i<length;i++)
	{
		mnuAddItem(itemList[i], TRUE, i);
	}
   
	hmiADClearLine(gHmiHandle, HMI_ALL_LINES);

   retVal = mnuRun(*choice);
   
#else
   if(gHmiHandle != 0)
   {
      hmiClose(gHmiHandle);
      gHmiHandle = 0;
   }
   
   gmaCTCloseHandle();
   
   mnuLafReset();

   if (title!=NULL)
      mnuLafSetTitle (title);
   else
      mnuLafSetTitle ("");
   
   
   
   mnuLafSetTimeout(timeout);

   for (i=0;i<length;i++)
   {
      mnuLafAddItem(itemList[i], i);
   }
   
   mnuLafSecHandleOpen();
   
   retVal = mnuLafRun(*choice);
   

#endif
   


	if (retVal>=0)
	{
		*choice = (uint8)retVal;
		retVal = RET_OK;		
	}

	return retVal;
   

}

/**
 * Set the HMI font
 */
int16 gmaHmiSetFont(void *font)
{
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   return hmiADFont(gHmiHandle, font);
}

/**
 * Change the auto center option.
 */
int16 gmaHmiAutoCentre(uint8 status)
{
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   return hmiADAutoCentre(gHmiHandle, status);
}

/**
 * Display a line of text
 *
 */
int16 gmaHmiDisplayText(uint32 line, uint32 column, char * text)
{
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   
	return hmiADDisplayText(gHmiHandle, line, column, text);
}

/**
 * Actualize the display with the information in memory
 */
int16 gmaHmiGraphUpdate(void)
{
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   
	return hmiGraphicWrite(gHmiHandle);
}

/**
 * Display a message to the user and ask for confirmation.
 */
bool gmaHmiConfirm(const char *name, int len)
{
   uint8 key;
   uint8 line, columns;
   int16 ret;
	char buf[16+1];
   
   if (len > 16) return -1;

	memcpy(buf, name, len);
	buf[len] = 0;
   
   line = (uint8) (gmaUtilGetDispHeight() / 16);
   columns = (uint8) (gmaUtilGetDispWidth() / 8);
   
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   

   /* display message plus "OK/CANCEL" string */
   hmiADFont(gHmiHandle, HMI_INTERNAL_FONT_DEFAULT);
   hmiADClearLine(gHmiHandle, HMI_ALL_LINES);
   hmiADAutoCentre(gHmiHandle, FALSE);
   hmiADDisplayText(gHmiHandle, 1, 0, buf);
   
   hmiADDisplayText(gHmiHandle, line-1, 1, gmaGetStringResource(IDS_OK));
   hmiADDisplayText(gHmiHandle, line-1, columns - 6, gmaGetStringResource(IDS_CANCEL));
   

   /* wait for use to press ENTER or CLEAR */
   while(42)
   {
      ret = hmiKeyWait(gHmiHandle, &key, 2000);
      if (ret == RET_OK && (key == HMI_KEY_ENTER || key == HMI_KEY_F1))
    	  return TRUE;
      else
    	  return FALSE;
   }
   
}


/**
 * Cancel any pending requests
 */
int16 gmaHmiSupCancel(void)
{
   if(!gHmiHandle)
   {
      return RET_OK;
   }
   
   return hmiCancel(gHmiHandle);
}


/**
 * Clear display line
 */
int16 gmaHmiClearLine(uint16 line)
{
   if(!gHmiHandle)
   {
      return RET_OK;
   }
   
   return hmiADClearLine(gHmiHandle, line);
}

/**
 * 
 */
static edtParams_t edtParams = 
{
   0,
   2,
   NULL,
   NULL,
   0,
   '_',
   EDT_LEFT_TO_RIGHT,
   3000,
   EDT_SPECIAL_KEY,
   HMI_KEY_PAPER_FEED,
   NULL,
   0
};

/**
 * Start a editing of an string
 *
 * @param mask the edition mask
 *
 * @param editItem the string to receive the edition result
 *
 * @param minLen the minimun length of the edition
 *
 * @param caption the text to appear above the edit entry
 */
int16 gmaHmiEditMask(char *mask, char *editItem, uint16 minLen, char *caption)
{
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   
   hmiADClearLine(gHmiHandle, HMI_ALL_LINES);
   hmiADFont(gHmiHandle, HMI_INTERNAL_FONT_DEFAULT);
   hmiADDisplayText(gHmiHandle, 1, 0, caption);

   edtParams.result = editItem;
   edtParams.mask = mask;
   edtParams.minLength = minLen;

   return edtEditMasked(gHmiHandle, gmaCTGetTouchHandle(), &edtParams);
   
}

/**
 * Set the backlight
 *
 */
int16 gmaHmiBackLight(uint8 value)
{
   
   hmiOutputConfig_t config;
   
   if(!gHmiHandle)
   {
      gmaHmiOpen();
   }
   
   
   config.fields = HMI_OUTPUT_CONFIG_BACKLIGHT;
   config.backlight = value;
   IFDEBUG(debugPrintf(DEBUG_COM1, "pass1"));   
   hmiOutputConfigWrite(gHmiHandle, &config);
   IFDEBUG(debugPrintf(DEBUG_COM1, "pass2"));   
   return hmiCfgAccess(CFG_WRITE_MODE, HMI_DISPLAY_1_BACKLIGHT, HMI_DISPLAY_1_BACKLIGHT_SIZE, &value);
}


/**
 * return the HMI handle
 */
uint32 gmaHmiGetHandle(void)
{
	if(gHmiHandle == 0)
	{
		gmaHmiOpen();
	}
	return gHmiHandle;
}

/**
 * Set the hmiHandle
 */
void gmaHmiSetHandle(uint32 hmiHandle)
{
	gHmiHandle = hmiHandle;
}


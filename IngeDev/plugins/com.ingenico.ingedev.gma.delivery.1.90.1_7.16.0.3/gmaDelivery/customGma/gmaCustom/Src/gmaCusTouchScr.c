
#include "stdlib.h"
#include "string.h"

#include "unicapt.h"
#include "gmaDefines.h"
#include "gmaMedia.h"
#include "gmaCusTouchScr.h"
#include "gmaGenCustom.h"
#include "gmaCustomUtil.h"


static uint8 _status = 0;
static uint32 touchscreenHandle = 0;
static gmaCTHandler _handler = NULL;


/**
 * Reset the library
 */
void gmaCTReset(void)
{
	_handler = NULL;
}

static uint8 initialized = 0;
struct screenData_st
{
	uint16 widthScr;
	uint16 widthTouch;
	uint16 heightScr;
	uint16 heightTouch;
};
static struct screenData_st scrData;


static void gmaCTGetData(void)
{

	hmiDynamicConfigResolution_t touchResolution;
	
	hmiCfgAccess(CFG_READ_MODE, HMI_TOUCH_1_RESOLUTION, sizeof(touchResolution), &touchResolution);


	scrData.heightScr = gmaUtilGetDispHeight();
	scrData.widthScr  = gmaUtilGetDispWidth();
	scrData.heightTouch = touchResolution.y_dimension;
	scrData.widthTouch = touchResolution.x_dimension;
}

static uint8 statusOnce = 0;

static void gmaCTOpenHandleOnce(void)
{
	if(touchscreenHandle == 0)
	{
		if(statusOnce == 0)
		{
			gmaCTOpenHandle();
			statusOnce = 1;
		}
	}
}


/**
 * Open the touch screen handle
 */
void gmaCTOpenHandle(void)
{
	int16 ret;
	
	if(initialized == 0)
	{
		gmaCTGetData();
		initialized = 1;
	}
	
	if(touchscreenHandle == 0)
	{
		ret = hmiOpenShared("DEFAULT", &touchscreenHandle, HMI_CH_TOUCH, NULL);
		if(ret != RET_OK)
		{
			touchscreenHandle = 0;
		}
	}
}

/**
 * Get the touchHandle
 */
uint32 gmaCTGetTouchHandle()
{
	return touchscreenHandle;
}

/**
 * Close the touch Screen handle
 */
void gmaCTCloseHandle(void)
{
	if(touchscreenHandle != 0)
	{
		hmiClose(touchscreenHandle);
		touchscreenHandle = 0;
	}
	statusOnce = 0;
}

/**
 * Set the function that will be called when an touch screen event happens
 */
void gmaCTSetHandlerFunction(gmaCTHandler handler)
{
	_handler = handler;
}

/**
 * Make the request to get a touch screen entry
 */
void gmaCTSreq(void)
{
	if(_status)
	{
		gmaCTOpenHandleOnce();
		if(touchscreenHandle!=0)
		{
			hmiTouchCoordReq(touchscreenHandle);
		}
	}
}

/**
 * Analise the coords touched
 *
 */
static void gmaCTAnaliseCoords(uint16 x, uint16 y)
{

	uint8 status = 0;
	uint16 xPos, yPos, xPos2, yPos2;
	gmaMediaListData_t *data;
		
   gmaMediaGetEntryStart();
   
   if ((x < gmaUtilReductionGet()) || (y < gmaUtilReductionGet()))
	   return;

   x -= gmaUtilReductionGet();
   y -= gmaUtilReductionGet();
   
   while(gmaMediaGetNextEntry(&data)==RET_OK)
   {
   	if(data->customData)
   	{
   		if(data->mediaType == GMA_MEDIA_MONO_BITMAP ||
   		   data->mediaType == GMA_MEDIA_COLOR_BITMAP)
   		{
   			xPos = data->posX;
   			yPos = data->posY;
   			xPos2 = xPos + data->data[0];
   			yPos2 = yPos + data->data[1];
   			status = 1;			
   			
   		}
			else if(data->mediaType == GMA_MEDIA_TEXT)
			{
				status = 0;
			}
			
			if(status == 1)
			{
				if(x >= xPos && x<= xPos2)
				{
					if(y >= yPos && y <= yPos2)
					{
						gmaCTtouchData_t *touchData = 
						   (gmaCTtouchData_t *) data->customData;
						
						if(_handler)
						{
							_handler(data->logicalId, data->physicalId, 
							         touchData->action, touchData->parameter);
						}
						return;
					}
				}
			}
   	}
   }
}

/**
 * Analise the result.
 * 
 * @param ret return value from the psyPeripheralResultWait
 */
void gmaCTSresult(int32 ret)
{
	hmiTouchCoordResult_t   tchResult;
	
	if(PSY_PER_EXECUTED_OK(ret,HMI_WAIT))
	{
		if(touchscreenHandle)
		{
			if(hmiResultGet(touchscreenHandle, sizeof(tchResult),
	                      (void *)&tchResult) == RET_OK)
	      {
	      	//touch screen available result
	      	if(tchResult.status == RET_OK && tchResult.eventType  == HMI_TOUCH_EV_DOWN)
	      	{
	      		gmaCustomUtilBLEnable(BACKLIGHT_NONE);
	      		tchResult.xCoord = ((uint32)tchResult.xCoord * (uint32)scrData.widthScr) / (uint32)scrData.widthTouch;
	      		tchResult.yCoord = ((uint32)tchResult.yCoord * (uint32)scrData.heightScr) / (uint32)scrData.heightTouch;
	      		gmaCTAnaliseCoords(tchResult.xCoord, tchResult.yCoord);
	      		gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
	      	}
	      }
		}
	}
}

/**
 * enable or disable the touch screen support
 * 
 * @param status if 1 activate the library, if 0 deactivate
 */
void gmaCTSEnableTouchScreen(uint8 status)
{
	_status = status;
}


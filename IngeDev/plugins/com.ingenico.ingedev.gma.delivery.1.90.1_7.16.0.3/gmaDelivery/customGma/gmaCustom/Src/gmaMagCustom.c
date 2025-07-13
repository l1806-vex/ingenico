
/**
 * 
 * @file gmaMagCustom.c
 *
 *
 * This file contains the four basic functions wich will handle
 *	magnetic card operations:
 * 
 * - gmaMagOpen
 * - gmaMagClose
 * - gmaMagCrdReq
 * - gmaMagCrdresultGet
 *
 *	Their prototypes are in "gmaMagCustom.h"
 * 
 *	The functions gathered in this file need the magnetic card handle to 
 *	operate.
 *
 * In this module there are functions to make the Mag request and 
 * to get the mag result if available. If there is a result available
 * the function \ref gmaMagCrdProcess will process the result.
 */



#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "gmaDefines.h"

#include "gmaMagCustom.h"
#include "gmaHmiCustom.h"
#include "SmcSupport.h"
#include "gmaHmiProcess.h"
#include "gmaCustomUtil.h"
#include "gmaGenCustom.h"

static uint32 gMagHandle = 0;

static magTripleResult_t magStripe;

static uint8 needRequest = 1;
/**
 * This function is called from main custom call back module and will
 * make a magnetic card read request
 *
 */
int16 gmaMagCrdReq (void)
{
	if (gMagHandle == 0)
	{
		return ERR_NOT_OPEN;
	}	
	else if(needRequest)
	{
		needRequest = 0;
		return magReadReq (gMagHandle, MAG_ALL_AVAILABLE);
	}
	else
	{
		return RET_RUNNING;
	}
}

/**
 * This function is called from main custom call back module when
 * a magnetic card event happens
 */
int16 gmaMagCrdResultGet (void)
{
	int16 retVal;

	retVal = magResultGet(gMagHandle, MAG_ALL_REQUESTED, sizeof(magTripleResult_t), &magStripe);
	
	if (retVal == RET_OK)
	{
		needRequest = 1;
    	gmaHmiSupCancel();
      smcSupCancel();
      gmaCustomUtilBLEnable(BACKLIGHT_NONE);
		retVal = gmaMagCrdProcess(&magStripe);
      gmaCustomUtilBLEnable(BACKLIGHT_TIMEOUT);
	}

	return retVal;
}

/**
 * This function open the magnetic card handle
 */
int16 gmaMagOpen (void)
{
    if (!gMagHandle)
    {
    	  needRequest = 1;
        return magOpen("DEFAULT", &gMagHandle);
    }

    return RET_OK;
}

/**
 * This function 
 * close the Magnetic Card Reader handle
 *
 */
int16 gmaMagClose (void)
{
   int16 retVal;
   needRequest = 1;
   if (gMagHandle)
   {
      gmaMagSupCancel();

      retVal = magClose(gMagHandle);
      
      if (retVal == RET_OK)
         gMagHandle = 0;
      
      return retVal;
   }
   
   return RET_OK;
}

/**
 * Cancel any pending requests
 */
int16 gmaMagSupCancel(void)
{
	needRequest = 1;
   return magCancel(gMagHandle);
}



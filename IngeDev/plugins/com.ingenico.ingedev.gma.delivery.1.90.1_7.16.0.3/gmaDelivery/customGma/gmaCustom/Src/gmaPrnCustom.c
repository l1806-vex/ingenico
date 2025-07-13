
/**
 * 
 *	@file gmaPrnCustom.c
 *
 *
 * This file contains two simple functions wich will perform simple printer
 * operations
 * 
 * - gmaPrnPrintLine
 * - gmaPrnLineFeed
 *
 *	Their prototypes are in "gmaPrnCustom.h"
 * 
 *	Those functions will open the printer handle, do what they have to do, 
 * and close the handle. The idea is not to lock the printer when the POS
 * is in idle state.
 *
 */


#include "unicapt.h"
#include "stdlib.h"
#include "string.h"
#include "gmaDefines.h"

#include "menuLib.h"
#include "gmaPrnCustom.h"
#include "gmaCustomDefines.h"



/**
 * This function print a text line.
 * The printer handle is opened and then closed.
 */
int16 gmaPrnPrintLine (char* line)
{
	uint32 prnHandle;
	
	if (prnOpen("DEFAULT", &prnHandle, PRN_IMMEDIATE)==PRN_OK)
	{
	    prnPrint (prnHandle, line);
		prnClose(prnHandle);
	}
	return RET_OK;
}

/**
 * This function will feed paper
 * The printer handle is opened and then closed.
 */
int16 gmaPrnLineFeed (uint8 numOfLines)
{
	uint32 prnHandle;
	
	if (prnOpen("DEFAULT", &prnHandle, PRN_IMMEDIATE)==PRN_OK)
	{
		prnLinefeed(prnHandle, numOfLines);
		prnClose(prnHandle);
	}
	return RET_OK;
}



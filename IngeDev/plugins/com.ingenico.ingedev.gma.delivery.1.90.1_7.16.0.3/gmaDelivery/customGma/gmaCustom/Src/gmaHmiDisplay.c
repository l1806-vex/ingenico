
/**
 * 
 * @file gmaHmiDisplay.c
 *
 *
 * This file contains the functions wich will be used to compose and
 * display the idle screen. This file will have the display config
 * available. Any function that needs to use 'canvas' or 'graphicContext'
 * must be placed here:
 * 
 */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#include "unicapt.h"

#include "gmaMedia.h"
#include "gmaDefines.h"
#include "gmaCustomDefines.h"
#include "gmaHmiCustom.h"
#include "gmaGenCustom.h"
#include "gmaCustomUtil.h"
#include "gmaHmiDisplay.h"
#include "gmaUtil.h"
#include "gmaDispOp.h"

/**
 * Structure with the media data mono bitmap.
 */
typedef struct 
{
   uint8 width;      /*!< width in pixels */
   uint8 height;     /*!< height in pixels */
   uint8 data[1];    /*!< bitmap, 1-bpp */
}sLogoData;

/**
 * Structure with the media data color bitmap
 */
typedef struct 
{
   uint8 width;        /*!< width in pixels */
   uint8 height;       /*!< height in pixels */
   uint8 deep;         /*!< Image deep: 4-bpp/8-bpp */
   uint8 compression;  /*!< COMP_NONE, COMP_RLE */
   uint8 data[1];      /*!< bitmap, 4-bpp/8-bpp */
}sLogoDataColor;

/*
 typedef struct 
{
   uint16   appId;
   uint16   iconId;
   uint8    x, y;
   uint8    width, height;
   uint8    *data;
}sIconData;
*/

hmiOutputConfig_t sDisplayConfig;
uint16 dispCounter = 0;
uint16 logoStatus = GMA_MEDIA_LOGO_EMPTY;

static uint32 terminalDate, terminalTime;


gmaMediaListData_t* pMediaData;

static void gmaMediaChange (void);
static int16 gmaDispMediaTableUpdate (void);
static int16 gmaDispClearCanvas (void);
static int16 gmaDispCurrLogo (bool center, uint16 posX, uint16 posY, uint16 mType, void* pData);
static int16 gmaDispDrawBmpMono (bool center, uint16 posX, uint16 posY, sLogoData* pData);
static int16 gmaDispDrawBmpColor (bool center, uint16 posX, uint16 posY, sLogoDataColor* pData);
static int16 gmaDispDrawText (bool center, uint16 posX, uint16 posY, char* pData);
static int16 gmaDispDrawIcon(uint16 posX, uint16 posY, uint16 width, uint16 height, uint8* pData);
static int16 gmaDispDrawIconColor(uint16 posX, uint16 posY, uint16 width, uint16 height, uint8 deep, uint8 compression, uint8* pData);
static void gmaDrawCompressedIcon (uint16 posX, uint16 posY, uint16 width,
						uint16 height, uint8* pData);

static void gmaDispAdjustPos(uint16 *pPosX, uint16 *pPosY);
static void gmaDispDrawReductionBlackStripe(void);
//static int16 gmaDispDateHour(void);
//static void gmaDispDrawMenuIcon(void);

/**
 * Function that will redraw the GMA display in the idle state
 */
int16 gmaDisplayCustom (void)
{

	int16 retVal;
   
   psyDateTimeGet(&terminalDate, &terminalTime);
   /**
    * Define the optic fonts
    */
	//hmiOp DefineFont(0, HMI_INTERNAL_FONT_DEFAULT);
	//hmiOp DefineFont(1, HMI_INTERNAL_FONT_1);
	//hmiOp DefineFont(2, HMI_INTERNAL_FONT_2);
	//hmiOp DefineFont(3, HMI_INTERNAL_FONT_3);
	//hmiOp DefineFont(4, HMI_INTERNAL_FONT_4);
	//hmiOp DefineFont(5, HMI_INTERNAL_FONT_5);

	
   /**
    * Update the media table
    */
	gmaDispMediaTableUpdate ();
	
	if (logoStatus == GMA_MEDIA_LOGO_EMPTY)
		gmaDispMediaTableUpdate ();
	

   /*
   * First all the text media data will be displayed than
   * all the graphics media is displayed. It is the reson
   * for the two while bellow.
   */

   /**
    * Call a core function to 
    * start the available media data in the core internal table
    */
   gmaMediaGetEntryStart();

   /**
    * Get a next first media data from the internal core table
    */
	retVal = gmaMediaGetNextEntry(&pMediaData);		

	gmaDispClearCanvas();

	gmaDispDrawReductionBlackStripe();

	while (retVal == RET_OK)
	{
		if (pMediaData->mediaType != GMA_MEDIA_TEXT)
			switch (pMediaData->customField)
			{
				case GMA_MEDIA_CUSTOM_APPL:
					gmaDispCurrLogo(TRUE, (uint16)(sDisplayConfig.wwidth/2), (uint16)(sDisplayConfig.wheight/2),
                  pMediaData->mediaType, pMediaData->data);
					break;
					
				case GMA_MEDIA_CUSTOM_PGIN:
					gmaDispCurrLogo(FALSE, pMediaData->posX, pMediaData->posY, pMediaData->mediaType, pMediaData->data);
					break;
					
				default:
					break;
			}

		retVal = gmaMediaGetNextEntry(&pMediaData);			
	}

   //gmaDispDrawMenuIcon(); // now in the settings plug-in
	
   gmaMediaGetEntryStart();

	retVal = gmaMediaGetNextEntry(&pMediaData);		

	while (retVal == RET_OK)
	{
		if (pMediaData->mediaType == GMA_MEDIA_TEXT)
			switch (pMediaData->customField)
			{
				case GMA_MEDIA_CUSTOM_APPL:
					gmaDispCurrLogo(TRUE, (uint16)(sDisplayConfig.wwidth/2), (uint16)(sDisplayConfig.wheight/2),
                  pMediaData->mediaType, pMediaData->data);
					break;
					
				case GMA_MEDIA_CUSTOM_PGIN:
					gmaDispCurrLogo(FALSE, pMediaData->posX, pMediaData->posY, pMediaData->mediaType, pMediaData->data);
					break;
					
				default:
					break;
			}

		retVal = gmaMediaGetNextEntry(&pMediaData);			
	}

   /**
    * Display the date and time of the terminal
    */
//   gmaDispDateHour();
	
   /**
    * Ask for a refresh in the display
    */
	gmaHmiGraphUpdate();

	return RET_OK;
}

/**
 * Display the media data passed as parameter.
 *
 * @param center if the coords represents the upper left corner or the center of the media data
 *
 * @param posX the x position of the media data (center or left corner)
 *
 * @param posY the y position of the media data  (center or left corner)
 *
 * @param mType the media data type. Support now \ref GMA_MEDIA_MONO_BITMAP, \ref GMA_MEDIA_COLOR_BITMAP and
 * \ref GMA_MEDIA_TEXT
 *
 * @param pData a pointer to the media data
 */
static int16 gmaDispCurrLogo (bool center, uint16 posX, uint16 posY, uint16 mType, void* pData)
{
	switch(mType)
	{
		case GMA_MEDIA_MONO_BITMAP:
			gmaDispDrawBmpMono(center, posX, posY, (sLogoData*) pData);
			break;

		case GMA_MEDIA_COLOR_BITMAP:
			gmaDispDrawBmpColor(center, posX, posY, (sLogoDataColor*) pData);
			break;

		case GMA_MEDIA_TEXT:
			gmaDispDrawText (center, posX, posY, (char*) pData);
			break;

		default:
			break;
	}
	       
    return RET_OK;
}

/**
 * Update the core internal table to help the display 
 * of the applications logos and the plugins media datas.
 */
static int16 gmaDispMediaTableUpdate (void)
{
	uint8 appType;
	int16 retVal;

   gmaMediaGetEntryStart();

	retVal = gmaMediaGetNextEntry(&pMediaData);		

	gmaMediaChange();

	while (retVal == RET_OK)
	{
		appType = gmaCustomGetAppType (pMediaData->physicalId);

		if ((appType == GMA_USER_APPLICATION)&&(pMediaData->mediaId == 0))
		{
			if (logoStatus == GMA_MEDIA_LOGO_EMPTY)
			{
				pMediaData->customField = GMA_MEDIA_CUSTOM_APPL;
				logoStatus = GMA_MEDIA_LOGO_DISPLAY;
			}
			else if ((logoStatus == GMA_MEDIA_LOGO_CHANGE)&&(pMediaData->customField == GMA_MEDIA_CUSTOM_APPL))
			{
				pMediaData->customField = GMA_MEDIA_CUSTOM_HIDE;
				logoStatus = GMA_MEDIA_LOGO_EMPTY;
			}
		}
		else if ((appType == GMA_PLUGIN_APPLICATION)&&(pMediaData->status == GMA_MEDIA_VISIBLE))
		{
			pMediaData->customField = GMA_MEDIA_CUSTOM_PGIN;
		}
		else
		{
			pMediaData->customField = GMA_MEDIA_CUSTOM_HIDE;
		}

		retVal = gmaMediaGetNextEntry(&pMediaData);		
		
	}

	return RET_OK;
}


/**
 * Check if it is time to change the actual application logo displayed
 */
static void gmaMediaChange (void)
{

	if (dispCounter > GMA_IDLE_SCREEN_PERIOD)
	{
		dispCounter = 0;
		logoStatus = GMA_MEDIA_LOGO_CHANGE;
	}
	else
	{
		dispCounter++;
	}

}

/**
 * date scape sequence treatment
 */
static int16 gmaDispTreatScapeSeqDate(char *pText, uint16 *lenScape, char *buff, uint16 *lenBuf)
{

   const char *tempStr;
   uint8 month;
   uint8 i;
   *lenScape = 3;
   switch(pText[2])
   {
      case 'd':
         sprintf(buff,"%02d", (int)PSY_DAY(terminalDate));
         *lenBuf=2;
         return RET_OK;
      case 'm':
         month = PSY_MONTH(terminalDate);
         if(month > 12 || month == 0)  
            month = 12;
         if(pText[3] == 'u' || pText[3] == 'l')
         {
            tempStr = gmaGetStringResource(IDS_JAN + PSY_MONTH(terminalDate) - 1);
            *lenBuf = strlen(tempStr);
            strcpy(buff, tempStr);
            for(i=0; i<*lenBuf; i++)
            {
	            if(pText[3] == 'u')
	            {
	            	buff[i] = toupper(buff[i]);
	            }
	            else
	            {
	            	buff[i] = tolower(buff[i]);
	            }
            }
         }
         else if(pText[3] == 'd')
         {
            sprintf(buff, "%02d", month);
            *lenBuf = 2;
         }
         else
         {
            return -1;
         }
         *lenScape = 4;
         return RET_OK;
      case 'y':
         sprintf(buff,"%04d", (int)PSY_YEAR(terminalDate));
         *lenBuf=4;
         return RET_OK;
      default:
         return -1;
   }
}

/**
 * time scape sequence treatment
 */
static int16 gmaDispTreatScapeSeqTime(char *pText, uint16 *lenScape, char *buff, uint16 *lenBuf)
{
   *lenScape = 3;
   switch(pText[2])
   {
      case 'h':
         sprintf(buff, "%02d", (int)PSY_HOUR(terminalTime));
         *lenBuf = 2;
         return RET_OK;
      case 'm':
         sprintf(buff, "%02d", (int)PSY_MIN(terminalTime));
         *lenBuf = 2;
         return RET_OK;
      case 's':
         sprintf(buff, "%02d", (int)PSY_SEC(terminalTime));
         *lenBuf = 2;
         return RET_OK;
      default:
         return -1;
   }
}

/**
 * 
 */
static int16 gmaDispTreatScapeSeq(char *pText, uint16 *lenScape, char *buff, uint16 *lenBuf)
{
   switch(pText[1])
   {
      case 'd': // Date scape command
         return gmaDispTreatScapeSeqDate(pText, lenScape, buff, lenBuf);
      case 't': // time scape command
         return gmaDispTreatScapeSeqTime(pText, lenScape, buff, lenBuf);
      default:
         return -1;
   }
}


/**
 * Draw the media data of type GMA_MEDIA_TEXT
 *
 * @param center if the coords represents the upper left corner or the center of the media data
 *
 * @param posX the x position of the media data (center or left corner)
 *
 * @param posY the y position of the media data  (center or left corner)
 *
 * @param pData a pointer to the media data
 */
static int16 gmaDispDrawText (bool center, uint16 posX, uint16 posY, char* pData)
{
	char* pText;
	//uint16 maxLen;
	//uint16 maxHeight;
	uint16 intY;

   uint16 i, k, indexLine = 0, index = 0;
   uint16 heigh = 0, width = 0;
   TextExtent te;
   Canvas* cv;
   GC* gc;
   char buff[256];  // MAX of 240 characters
   char *lines[16]; // MAX of 16 lines
   uint8 color[2], aux[4];
   uint8 alignRight = 0;
   
   gmaDispAdjustPos(&posX, &posY);

    cv = sDisplayConfig.wcanvas;
    gc = sDisplayConfig.wgraphicContext;

	//	Check for font redefinition
	//hmiOp SetFont (gc,(uint16)3);
	gmaDopSetFontNum(gc, 3);
	pText = pData;
	color[0] = SETCOLOR(0);
	color[1] = SETCOLOR(0);
	
   for (i = 0; pText[i] != 0; i++)
   {
     if ((pText[0]=='%')&&(pText[1]>='0')&&(pText[1]<='5')&&(pText[2]=='f'))
	  {
 	     //hmiOp SetFont (gc,(uint16)(pText[1]-'0'));
 	     gmaDopSetFontNum(gc, pText[1]-'0');
	     pText = &pText[3];
	     i = 0;
	  }
	  else if(pText[0]=='%' && pText[1] == 'r')
	  {
	  	  alignRight = 1;
	  	  pText = &pText[2];
	  	  i=0;
	  }
	  else if ((pText[0]=='%')&&(pText[2]=='c' || pText[3]=='c' || pText[4]=='c'))
	  {
			uint8 j;
         for (k = 0; pText[k + 1] != 'c'; aux[k] = pText[k + 1], k++);
         aux[k] = '\0';
         for(j=0;j<k;j++)
         {
         	if(aux[j]<'0' || aux[j]>9)
         	{
         		break;
         	}
         }
         if(j==k)
         {
         	color[0] = SETCOLOR((uint8) atoi ((char *) aux));
	     		pText = &pText[k + 2];
	     		i = 0;
         }
	  }
	  else
	  {
	  	 break;
	  }
   }
   
   hmiOpSetForeground(gc, color[0]);
   lines[0] = &buff[0];
   memset(buff,0,sizeof(buff));
   for(i=0; pText[i]!=0;i++)
   {
      switch(pText[i])
      {
      case 0x0a:
         indexLine++;
         buff[index++] = 0;
         lines[indexLine] = &buff[index];
         hmiOpTextExtent(gc, lines[indexLine-1], (short) strlen(lines[indexLine-1]), &te);
         heigh += te.h;
         if(width < te.w)
         	width = te.w;
         break;
      case '%':
         if(pText[i+1] != '%')
         {
         	uint16 lenScape;
         	uint16 lenBuff;
            // treat commands (NOT Exist in this version)
            if(gmaDispTreatScapeSeq(&pText[i], &lenScape, &buff[index], &lenBuff) != RET_OK)
            {
            	return -1;
            }
            index += lenBuff;
            i+= lenScape-1;

         }
         else
         {
            i++;
            buff[index++] = '%';
         }
         break;
      default:
         buff[index++] = pText[i];
         break;
      }
   }
   buff[index]=0;
   
   
   hmiOpTextExtent(gc, lines[indexLine], (short) strlen(lines[indexLine]), &te);
   if(width < te.w)
   	width = te.w;
   
   
	if(center)
   {
      intY = posY - heigh/2;
   }
   else
   {
      intY = posY;
      if(alignRight)
	   {
   		posX = posX - width;
	   }
      
   }
   for(i=0; i<=indexLine; i++)
   {
      hmiOpTextExtent(gc, lines[i], (short) strlen(lines[i]), &te);
      if(center)
      {
         hmiOpDrawText(cv, gc, (uint16)(posX - te.w/2), (uint16)(intY + te.baseline), lines[i], (uint16) strlen(lines[i]));
      }
      else
      {
         hmiOpDrawText(cv, gc, posX, intY, lines[i], (uint16) strlen(lines[i]));
      }
      intY += te.h;
   }

   
	hmiOpSetForeground(gc, color[1]);
	return RET_OK;
}

/**
 * Draw the media data of type GMA_MEDIA_MONO_BITMAP
 *
 * @param center if the coords represents the upper left corner or the center of the media data
 *
 * @param posX the x position of the media data (center or left corner)
 *
 * @param posY the y position of the media data  (center or left corner)
 *
 * @param pData a pointer to the media data
 */
static int16 gmaDispDrawBmpMono (bool center, uint16 posX, uint16 posY, sLogoData* pData)
{
	uint16 logo_x;
	uint16 logo_y;
		
	if (center)
	{
	   // center logo on display
	   logo_x = (int16) ((sDisplayConfig.wwidth - pData->width) / 2);
	   logo_y = (int16) ((sDisplayConfig.wheight - pData->height) / 2);
	}
	else
	{
		logo_x = posX;
		logo_y = posY;
	}

	return gmaDispDrawIcon(logo_x, logo_y, pData->width, pData->height, pData->data);
}


/**
 * Draw the media data of type GMA_MEDIA_COLOR_BITMAP
 *
 * @param center if the coords represents the upper left corner or the center of the media data
 *
 * @param posX the x position of the media data (center or left corner)
 *
 * @param posY the y position of the media data  (center or left corner)
 *
 * @param pData a pointer to the media data
 */
static int16 gmaDispDrawBmpColor (bool center, uint16 posX, uint16 posY, sLogoDataColor* pData)
{
	uint16 logo_x;
	uint16 logo_y;
		
	if (center)
	{
	   // center logo on display
	   logo_x = (int16) ((sDisplayConfig.wwidth - pData->width) / 2);
	   logo_y = (int16) ((sDisplayConfig.wheight - pData->height) / 2);
	}
	else
	{
		logo_x = posX;
		logo_y = posY;
	}

	return gmaDispDrawIconColor(logo_x, logo_y, pData->width, pData->height, pData->deep, pData->compression, pData->data);

}

/**
 * 
 */
static void gmaDispCopyCanvas1bpp(uint8 *pDest, uint8 *pData, uint16 width, uint16 height)
{
	uint16 x, y;
	uint8 *p = pData;
	uint8 *pD = pDest;
	uint8 bit = 0x80;
	uint8 bit2 = 0x80;
	
	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++)
		{
			if(*p & bit)
			{
				*pD |= bit2;
			}
			
			if((bit >>= 1) == 0) bit = 0x80, ++p;
			if((bit2 >>= 1) == 0) bit2 = 0x80, ++pD;
			
		}
		if(bit2 != 0x80) bit2 = 0x80, ++pD; // line aligment
			
	}
}

/**
 * Draw the mono bitmap media data
 *
 * @param posX the x position of the left part of the bitmap in the screen
 *
 * @param posY the y position of the upper part of the bitmap in the screen
 *
 * @param width the width of the bitmap
 *
 * @param height the height of the bitmap
 *
 * @param pData the bitmap one bit per pixel
 */
static int16 gmaDispDrawIcon(uint16 posX, uint16 posY, uint16 width, uint16 height, uint8* pData)
{

   uint8 bit = 0x80;
   int32 x, y;
   Canvas* cv;
   GC* gc;

   cv = sDisplayConfig.wcanvas;
   gc = sDisplayConfig.wgraphicContext;
   
   gmaDispAdjustPos(&posX, &posY);

   /* clear bitmap region */
   hmiOpSetForeground(gc, SETCOLOR(15));
   hmiOpDrawRect(cv, gc, posX, posY, width, height);

   /* draw only black pixels */
   hmiOpSetForeground(gc, SETCOLOR(0));
	
	if(!gmaUtilTermColor())
	{
		uint8 *pDest = NULL;
		uint8 *pDataEnd = pData;
		uint16 widthCanvas = ((width + 7) / 8) * 8;
		
		if(widthCanvas != width)
		{
			uint16 sizeDest =((width + 7)/8) * height; 
	      pDest = malloc(sizeDest);
	      memset(pDest, 0, sizeDest);
			gmaDispCopyCanvas1bpp(pDest, pData, width, height);
			pDataEnd = pDest;
		}
		
		hmiGraphicBLTWrite(gmaHmiGetHandle(), posX, posY, pDataEnd, widthCanvas, height, 0, 0, width, height, HMI_BLT_LOG_OP_NONE, FALSE);
		if(pDest)
		{
			free(pDest);
		}
	}
	else
	{
		uint8 *tempLine = malloc(width);
		uint8 *p = pData;

		if(tempLine == NULL)
			return -1;

		for (y = 0; y < height; ++y)
		{
			memset(tempLine, SETCOLOR(15), width);
			for (x = 0; x < width; ++x)
	      {
	         if (*p & bit)
	         {
	         	tempLine[x] = SETCOLOR(0);
	         }
	         if ((bit >>= 1) == 0) bit = 0x80, ++p;
	      }
	      
			hmiGraphicBLTWrite(gmaHmiGetHandle(), posX, posY + y, tempLine, width, 1, 0, 0, width, 1, HMI_BLT_LOG_OP_NONE, FALSE);
		}
		free(tempLine);
	}

   /**for (y = 0; y < height; ++y)
      for (x = 0; x < width; ++x)
      {
         if (*p & bit)
            hmiOpDrawPoint(cv, gc, (int16)(x + posX), (int16)(y + posY));
         if ((bit >>= 1) == 0) bit = 0x80, ++p;
      }*/

   return RET_OK;
}

/**
 * Draw the mono bitmap media data
 *
 * @param posX the x position of the left part of the bitmap in the screen
 *
 * @param posY the y position of the upper part of the bitmap in the screen
 *
 * @param width the width of the bitmap
 *
 * @param height the height of the bitmap
 *
 * @param pData the bitmap one bit per pixel compressed used RLE
 */
/*static void gmaDrawCompressedIcon (uint16 posX, uint16 posY, uint16 width, uint16 height, uint8* pData)
{
   int32 x, y, index;
   Canvas* cv;
   GC* gc;
   uint8 color, count;
   
   cv = sDisplayConfig.wcanvas;
   gc = sDisplayConfig.wgraphicContext;
   
   x = 0; y = 0;
   for (index = 0; (width * height) > (x + (y * width));)
   {
      color = pData[index++];
      count = color & 0x7F;
      if ((color & 0x80) == 0)
      {
         for (; count > 0; x++, count--)
         {
            if (x >= width)
            {
               x = 0;
               y++;
            }
            color = pData[index++];
            hmiOpSetForeground(gc, SETCOLOR(color));
            hmiOpDrawPoint(cv, gc, (int16)(x + posX), (int16)(y + posY));
         }
      }
      else
      {
         color = pData[index++];
         for (; count > 0; x++, count--)
         {
            if (x >= width)
            {
               x = 0;
               y++;
            }
            hmiOpSetForeground(gc, SETCOLOR(color));
            hmiOpDrawPoint(cv, gc, (int16)(x + posX), (int16)(y + posY));
         }
      }
   }
}*/

/**
 * Draw the color bitmap media data
 *
 * @param posX the x position of the left part of the bitmap in the screen
 *
 * @param posY the y position of the upper part of the bitmap in the screen
 *
 * @param width the width of the bitmap
 *
 * @param height the height of the bitmap
 *
 * @param deep the number of bits per pixel
 *
 * @param compression if compression is used in this media data.
 *
 * @param pData the bitmap can be 4 bits per pixel or 8 bits per pixel.
 */
static int16 gmaDispDrawIconColor(uint16 posX, uint16 posY, uint16 width, uint16 height, uint8 deep, uint8 compression, uint8* pData)
{
   int32 x, y;
   Canvas* cv;
   GC* gc;
   uint8 color;

   cv = sDisplayConfig.wcanvas;
   gc = sDisplayConfig.wgraphicContext;
  
   gmaDispAdjustPos(&posX, &posY);

   /* clear bitmap region */
   hmiOpSetForeground(gc, SETCOLOR(15));
   hmiOpDrawRect(cv, gc, posX, posY, width, height);

   switch (deep)
   {
      case 4:
      	
         for (y = 0; y < height; y++)
 	     {
            for (x = 0; x < width; x++) 
            {
               /* draw pixels */
               color = (uint8) NIBBLE(pData[(x / 2) + (y * (width / 2))], x % 2);
               hmiOpSetForeground(gc, SETCOLOR(color));
               hmiOpDrawPoint(cv, gc, (int16)(x + posX), (int16)(y + posY));
		    }
		 }
		 break;

      case 8:
         if (compression == GMA_MEDIA_COMP_RLE)
         {
            //gmaDrawCompressedIcon (posX, posY, width, height, pData);
            gmaDrawCompressedIcon (posX, posY, width, height, pData);
            
         }
         else
         {
         	//uint8 *row = malloc(width);
         	//if(row == NULL)
         	//	return -1;
         	
            for (y = 0; y < height; y++)
		      {
               //for (x = 0; x < width; x++)
		         //{
                  /* draw pixels */
                  //color = pData[x + (y * width)];
                  //hmiOpSetForeground(gc, SETCOLOR(color));
                  //hmiOpDrawPoint(cv, gc, (int16)(x + posX), (int16)(y + posY));
                  //row[x] = pData[x + (y * width)];
               //}
               hmiGraphicBLTWrite(gmaHmiGetHandle(), posX, posY + y, &pData[(y * width)], width, 1, 0, 0, width, 1, HMI_BLT_LOG_OP_NONE, FALSE);
		      }
		      //free(row);
         }
	 	 break;
   }

   return RET_OK;
}



/**
 * Draw the mono bitmap media data
 *
 * @param posX the x position of the left part of the bitmap in the screen
 * @param posY the y position of the upper part of the bitmap in the screen
 * @param width the width of the bitmap
 * @param height the height of the bitmap
 * @param pData the bitmap one bit per pixel compressed used RLE
 */
static void gmaDrawCompressedIcon (uint16 posX, uint16 posY, uint16 width,
uint16 height, uint8* pData)
{
   uint16 x, y;
   uint8 *row = malloc(width);
   uint8 color = 0, in_run = 0;
   int count = 0;
	
	if(row == NULL)
		return;
	
	gmaDispAdjustPos(&posX, &posY);
   
   /*
    * The RLE encoded bitmap is decoded line by line.
    * Actually, the processing is done byte by byte on each run and when
    * a sequence of 'width' pixels is formed, it is drawn and a new line
    * is started.
    */

   for (y = x = 0; y < height;)
   {
      // check if need to fetch a new run
      if (count == 0)
      {
         in_run = *pData & 0x80;
         count = *pData++ & 0x7F;
         if (in_run) color = *pData++;
      }

      // decode until we reach the end of this line or the end of this run
      if (in_run)
      {
         // run of equal pixels
         for (; count > 0 && x < width; --count)
            row[x++] = color;
      }
      else
      {
         // run of different pixels
         for (; count > 0 && x < width; --count)
            row[x++] = *pData++;
      }

      // if reached end of line, draw it and prepare to start a new line
      if (x == width)
      {
         hmiGraphicBLTWrite(gmaHmiGetHandle(), posX, posY + y, row, width, 1, 0, 0, width, 1, HMI_BLT_LOG_OP_NONE, FALSE);
         x = 0;
         ++ y;
      }
   }

   free(row);
}


/**
 * Small menu icon definition
 */
/*static const uint8 G_iconMenu[] = {
   24, 8,
	0x1f, 0xff, 0xff, 
	0x20, 0x00, 0x00, 
	0x28, 0xbd, 0x29, 
	0x4d, 0xa1, 0xa9, 
	0x4a, 0xb9, 0x69, 
	0x48, 0xa1, 0x29, 
	0x88, 0xa1, 0x29, 
	0x88, 0xbd, 0x26, 
};*/

/**
 * Big Menu icon definition
 */
/*static const uint8 G_iconMenuBig[] = {
   48, 16,
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x08, 
	0xbf, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0xa0, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0xa0, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0xa0, 0x31, 0xbf, 0x63, 0x63, 0x02, 
	0xa0, 0x3b, 0xb0, 0x73, 0x63, 0x02, 
	0xa0, 0x35, 0xb0, 0x6b, 0x63, 0x02, 
	0xa0, 0x31, 0xbc, 0x67, 0x63, 0x02, 
	0xa0, 0x31, 0xb0, 0x63, 0x63, 0x02, 
	0xa0, 0x31, 0xb0, 0x63, 0x63, 0x02, 
	0xa0, 0x31, 0xb0, 0x63, 0x63, 0x02, 
	0xa0, 0x31, 0xbf, 0x63, 0x3e, 0x02, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 

};*/

/**
 * Draw the menu icon
 */
/*static void gmaDispDrawMenuIcon(void)
{
   if(gmaUtilUseBigFont())
   {
      gmaDispDrawBmpMono (0, (uint16) (sDisplayConfig.wwidth - G_iconMenuBig[0] - 2), 
         (uint16) (sDisplayConfig.wheight -  G_iconMenuBig[1]),  (sLogoData*) G_iconMenuBig);
      
      // set the menu as a region to be touched
      
   }
   else
   {
      gmaDispDrawBmpMono (0, (uint16) (sDisplayConfig.wwidth - G_iconMenu[0] - 2), 
         (uint16) (sDisplayConfig.wheight -  G_iconMenu[1]),  (sLogoData*) G_iconMenu);
         
      // set the menu as a region to be touched
      
   }
}*/

/**
 * Translate the month to the string format
 */
/*static void gmaDispFormatDate(char *str, uint32 date)
{
   const char *monthString[] = 
   {
      "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", 
         "sep", "oct", "nov", "dec"
   };
   sprintf(str, "%02ld/%s/%04ld",
         PSY_DAY(date),
         monthString[PSY_MONTH(date) - 1],
         PSY_YEAR(date));
}*/

/**
 * Display the date and time in the screen
 */
/*static int16 gmaDispDateHour(void)
{
   char str[17];
   uint32 date, time;
   TextExtent te;
   int16 fontType;
   
   if(gmaUtilUseBigFont())
   {
      fontType = 0;
   }
   else
   {
      fontType = 3;
   }

   hmiOp SetFont(sDisplayConfig.wgraphicContext, fontType);
   psyDateTimeGet(&date, &time);
   gmaDispFormatDate(str, date);

   hmiOpTextExtent(sDisplayConfig.wgraphicContext, str, (short) strlen(str), &te);
   hmiOpDrawText(sDisplayConfig.wcanvas, sDisplayConfig.wgraphicContext,
      2, te.h, str, (short) strlen(str));

   sprintf(str, "%02ld:%02ld", PSY_HOUR(time), PSY_MIN(time));
   hmiOpTextExtent(sDisplayConfig.wgraphicContext, str, (short) strlen(str), &te);
   hmiOpDrawText(sDisplayConfig.wcanvas, sDisplayConfig.wgraphicContext,
      (short) (sDisplayConfig.wwidth - te.w - 2), te.h, str, (short) strlen(str));
   return RET_OK;
}*/

/**
 * Clear the canvas
 */
static int16 gmaDispClearCanvas (void)
{
   if (gmaUtilTermColor())
   {
	  hmiOpSetForeground(sDisplayConfig.wgraphicContext, 15);
   }
   else
   {
      hmiOpSetForeground(sDisplayConfig.wgraphicContext, 0);
   }
   hmiOpDrawRect(sDisplayConfig.wcanvas, sDisplayConfig.wgraphicContext, 0, 0,
      (uint16) sDisplayConfig.wwidth, (uint16) sDisplayConfig.wheight);

   return RET_OK;   
}

static void gmaDispAdjustPos(uint16 *pPosX, uint16 *pPosY)
{
	if (gmaUtilReductionStatusGet() == TRUE)
	{
		(*pPosX) += gmaUtilReductionGet();
		(*pPosY) += gmaUtilReductionGet();
	}
}

static void gmaDispDrawReductionBlackStripe(void)
{
	Canvas* cv;
	GC* gc;
	uint32 w, h, x=0, y=0;

	if ((gmaUtilStripeStatusGet() == FALSE) || (gmaUtilReductionStatusGet() == FALSE))
		return;

	if (gmaUtilReductionGet() <= 1)
		return;
		
	// Prepare Black Stripe
	w = sDisplayConfig.wwidth;
	h = sDisplayConfig.wheight;
	cv = sDisplayConfig.wcanvas;
	gc = sDisplayConfig.wgraphicContext;
	hmiOpSetForeground(gc, SETCOLOR(0));
	hmiOpDrawRect(cv, gc, x, y, w, h);
	
	// Prepare Free Area
	x = gmaUtilReductionGet()-1;
	y = gmaUtilReductionGet()-1;
	w = gmaUtilGetDispWidthR()+2;
	h = gmaUtilGetDispHeightR()+2;
	hmiOpSetForeground(gc, SETCOLOR(15));
	hmiOpDrawRect(cv, gc, x, y, w, h);
}

/**
 * Set the optic fonts and get the display config structure
 */
int16 gmaDispInitConf (uint32 hmiHandle)
{
	//hmiOp DefineFont(0, HMI_INTERNAL_FONT_DEFAULT);
	//hmiOp DefineFont(1, HMI_INTERNAL_FONT_1);
	//hmiOp DefineFont(2, HMI_INTERNAL_FONT_2);
	//hmiOp DefineFont(3, HMI_INTERNAL_FONT_3);
	//hmiOp DefineFont(4, HMI_INTERNAL_FONT_4);
	//hmiOp DefineFont(5, HMI_INTERNAL_FONT_5);
	
	return hmiOutputConfigRead (hmiHandle, &sDisplayConfig);
}


/**
 * 
 */
int16 gmaDispGetDispSize(uint16 *height, uint16 *width)
{
   *height = (uint16) sDisplayConfig.wheight;
   *width  = (uint16) sDisplayConfig.wwidth;
   return RET_OK;
}





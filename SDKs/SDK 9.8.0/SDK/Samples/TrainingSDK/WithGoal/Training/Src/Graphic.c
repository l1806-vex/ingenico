//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  GRAPHIC.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       16-July-2012     Kassovic
//  Last modified : 16-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                         *** Graphic management ***
//  This file DOES NOT use the following API(s) for graphic:
//    # Graphic library level (DrawLine, DrawRect, DrawCircle, DrawEllipse, ...)
//      - No access to color function, only monochrome mode
//      - Does not support touch screen
//    # Color library level (Line, Rect, Circle, Ellipse, ...)
//      - Only for color terminals
//      - Does not support touch screen
//  This file uses the Graphic Object Advanced Library (GOAL) for graphic:
//    # Manager goal must be loaded
//    # For all type of terminals (B&W, Color, touch) and display ration supported
//    # Customized mode
//      . By API(s) (used inside this file)
//        Build your graphic using API(s) widgets
//        Pixels, lines, rectangles, forms, animations, logo...
//
//  List of routines in file :
//      testCnvPixel : Display pixels randomly.
//      testCnvLine : Display rotating lines.
//      testCnvBar : Display a moving rectangle. 
//      testCnvForm : Display different forms and animations.  
//      Draw : Start the animation demo.
//      Image : Display and print an image (JPG or BMP).
//      Animated : Display an animated image (GIF).
//                            
//  File history :
//  071612-BK : File created
//                                                                           
//****************************************************************************
//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library
int rand(void);

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define cnvW    100
#define cnvH    100
#define cnvD    2
#define cnvP (1<<cnvD)

#define MAX_LINE  14

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
typedef struct stGraphic
{
	T_GL_COLOR ulPen;     // Pen
	T_GL_COLOR ulBrush;   // Brush
}ST_GRAPHIC;

//****************************************************************************
//      PRIVATE DATA
//****************************************************************************
const char *pcS = "123456789A@";
const ulong tulColor[] = {GL_COLOR_WHITE, GL_COLOR_RED, GL_COLOR_BLUE, GL_COLOR_GREEN, GL_COLOR_YELLOW};
const char tcX[] = {14, 14, 14, 14, 19, 24, 29, 24, 19, 14, 14, 14, 14};  // Coordinate of the ball
const char tcY[] = {70, 78, 86, 93, 93, 93, 93, 93, 93, 93, 86, 78, 70};

// Properties of the Image screen (Goal)
// =====================================
static const ST_IMAGE xImage =
{
	{GL_COLOR_WHITE, TRUE, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}, GL_DIRECTION_ALL, {4, 4, 4, 4, GL_COLOR_RED}, {5, 4, 5, 4} },
	{TRUE, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}, GL_DIRECTION_ALL, {1, 1, 1, 1, GL_COLOR_BLACK}, {2, 1, 2, 1} }
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}
};

static const ST_BORDER xBorder = {4, 4, 4, 4, GL_COLOR_BLACK};

static const ST_DRAW_FONT xFontColor = {NULL, GL_FONT_STYLE_NORMAL, 15, 15};
static const ST_DRAW_FONT xFontBW = {NULL, GL_FONT_STYLE_NORMAL, 5, 5};

// Graphic initialization for forms and animation
// ==============================================
static const ST_GRAPHIC txColor[MAX_LINE] =
{
	{GL_COLOR_RED,    GL_COLOR_RED},     // Rectangle and fill it
	{GL_COLOR_GREEN,  GL_COLOR_BLACK},   // Rectangle and empty it
	{GL_COLOR_BLUE,   GL_COLOR_BLACK},   // Circle and empty it
	{GL_COLOR_YELLOW, GL_COLOR_YELLOW},  // Circle and fill it
	{GL_COLOR_RED,    GL_COLOR_RED},     // Rectangle and empty it
	{GL_COLOR_WHITE,  GL_COLOR_BLACK},   // Text
	{GL_COLOR_RED,    GL_COLOR_BLACK},   // Rectangle and empty it
	{GL_COLOR_WHITE,  GL_COLOR_BLACK},   // Text
	{GL_COLOR_WHITE,  GL_COLOR_BLACK},   // Text
	{GL_COLOR_RED,    GL_COLOR_BLACK},   // Under line
	{GL_COLOR_BLUE,   GL_COLOR_BLACK},   // Ellipse and empty it
	{GL_COLOR_YELLOW, GL_COLOR_BLACK},   // Pixels
	{GL_COLOR_YELLOW, GL_COLOR_BLACK},   // Rectangle and empty it
	{GL_COLOR_RED,    GL_COLOR_RED}      // Circle and empty it
};

static const ST_GRAPHIC txBW[MAX_LINE] =
{
	{GL_COLOR_BLACK, GL_COLOR_BLACK},    // Rectangle and fill it
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Rectangle and empty it
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Circle and empty it
	{GL_COLOR_BLACK, GL_COLOR_BLACK},    // Circle and fill it
	{GL_COLOR_BLACK, GL_COLOR_BLACK},    // Rectangle and empty it
	{GL_COLOR_WHITE, GL_COLOR_BLACK},    // Reverse Text
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Rectangle and empty it
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Text
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Text
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Under line
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Ellipse and empty it
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Pixels
	{GL_COLOR_BLACK, GL_COLOR_WHITE},    // Rectangle and empty it
	{GL_COLOR_BLACK, GL_COLOR_WHITE}     // Circle and empty it
};

//****************************************************************************
//                      void TestCnvPixel (void)
//  This function shows the capabilities of the graphic when using GOAL.
//  It shows color pixels randomly (Screen saver).
//  The following functions have been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateDrawing() : To build drawing (Line, ...) screen.
//   - GoalClrDrawing() : To clear all drawing on screen.
//   - GoalDrawLine() : To display a pixel on screen.
//   - GoalDestroyDrawing() : To destroy all drawing on screen.
//   Support B&W, color and touch terminals.
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static int TestCnvPixel(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xDrawing;
	T_GL_COLOR ulPen;
	T_GL_COORD x, y;
    byte c, ucIdx;
	int iRet=-1;

	// Show pixels randomly
	// ********************
    xDrawing = GoalCreateDrawing(xGoal, GL_ENCODING_UTF8);
    CHECK(xDrawing!=NULL, lblKO);          // Create drawing and clear it
    iRet = GoalClrDrawing(xDrawing, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	ucIdx=0;
	while(1)
	{
        x = (T_GL_COORD) (rand() % cnvW);  // x coordinate
        y = (T_GL_COORD) (rand() % cnvH);  // y coordinate
        c = (byte) (rand() % 2);           // c on/off

        if (c == 1)
        	if (IsColorDisplay())          // Color display?
        		ulPen = GL_COLOR_BLACK;    // Yes, pixel off
        	else
        		ulPen = GL_COLOR_WHITE;    // No, pixel off
        else
        {
        	if (IsColorDisplay())          // Color display?
        	{
        		ulPen = tulColor[ucIdx];   // Yes, pixel on
        		ucIdx++;
        		if (ucIdx == 5)
        			ucIdx=0;
        	}
        	else
        		ulPen = GL_COLOR_BLACK;    // No, pixel on
        }
                                           // Put a pixel (x,y) with pen (on/off) on screen
    	iRet = GoalDrawLine(xDrawing, ulPen, x, y, x, y, 100, true);
    	CHECK(iRet>=0, lblKO);
    	if (iRet!=0)                       // Exit on valid/cancel key
    		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                     // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if(xDrawing)
		GoalDestroyDrawing(&xDrawing);     // Destroy drawing
	return iRet;
}

//****************************************************************************
//                      void testCnvLine (void)
//  This function shows the capabilities of the graphic when using GOAL.
//  It shows rotating lines.
//  The following functions have been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateDrawing() : To build drawing (Line, ...) screen.
//   - GoalClrDrawing() : To clear all drawing on screen.
//   - GoalDrawLine() : To display a line on screen.
//   - GoalDestroyDrawing() : To destroy all drawing on screen.
//   Support B&W, color and touch terminals.
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static int TestCnvLine(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xDrawing;
	T_GL_COLOR ulPen;
	T_GL_COORD x1, y1;
	T_GL_COORD x2, y2;
    word dx, dy;
    byte ucIdx;
    bool bClr;
	bool bExit=FALSE;
	int i, iRet=-1;

	// Show rotating lines
	// *******************
    xDrawing = GoalCreateDrawing(xGoal, GL_ENCODING_UTF8);
    CHECK(xDrawing!=NULL, lblKO);        // Create drawing and clear it
	iRet = GoalClrDrawing(xDrawing, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

    dx = cnvW/16;
    dy = cnvH/16;

	ucIdx=0;
    bClr=false;
    while(1)
    {
        if (bClr)
        	if (IsColorDisplay())        // Color display?
        		ulPen=GL_COLOR_BLACK;    // Yes, clear line
        	else
        		ulPen=GL_COLOR_WHITE;    // No, clear line
        else
        	if (IsColorDisplay())        // Color display?
        		ulPen = tulColor[ucIdx]; // Yes, draw line
        	else
        		ulPen=GL_COLOR_BLACK;    // No, draw line

        y1 = 0;
        x2 = cnvW;
        for (i=1; i<16; i++)             // First quarter
        {
            x1 = i*dx;
            y2 = i*dy;

        	iRet = GoalDrawLine(xDrawing, ulPen, x1, y1, x2, y2, 50, true);
        	CHECK(iRet>=0, lblKO);
        	if (iRet!=0)                 // Exit on valid/cancel key
        	{
        		bExit=TRUE;
        		break;
        	}
        }

		if (bExit) break;

        x1 = cnvW;
        y2 = cnvH;
        for (i=1; i<16; i++)             // Second quarter
        {
            y1 = i*dy;
            x2 = cnvW - (i*dx);

        	iRet = GoalDrawLine(xDrawing, ulPen, x1, y1, x2, y2, 50, true);
        	CHECK(iRet>=0, lblKO);
        	if (iRet!=0)                 // Exit on valid/cancel key
        	{
        		bExit=TRUE;
        		break;
        	}
        }

		if (bExit) break;

        y1 = cnvH;
        x2 = 0;
        for (i=1; i<16; i++)             // Third quarter
        {
            x1 = cnvW - (i*dx);
            y2 = cnvH - (i*dy);

        	iRet = GoalDrawLine(xDrawing, ulPen, x1, y1, x2, y2, 50, true);
        	CHECK(iRet>=0, lblKO);
        	if (iRet!=0)                 // Exit on valid/cancel key
        	{
        		bExit=TRUE;
        		break;
        	}
        }

		if (bExit) break;

        x1 = 0;
        y2 = 0;
        for (i=1; i<16; i++)             // Last quarter
        {
            y1 = cnvH - (i*dy);
            x2 = i*dx;

        	iRet = GoalDrawLine(xDrawing, ulPen, x1, y1, x2, y2, 50, true);
        	CHECK(iRet>=0, lblKO);
        	if (iRet!=0)                 // Exit on valid/cancel key
        	{
        		bExit=TRUE;
        		break;
        	}
		}

		if (bExit) break;
 
        if(bClr)
        {
        	ucIdx++;                     // Rotation under color
        	if (ucIdx == 5)
        		ucIdx=0;
            bClr=false;
        }
        else                             // Clear rotation
            bClr=true;
    }

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                   // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if(xDrawing)
		GoalDestroyDrawing(&xDrawing);   // Destroy drawing
	return iRet;
}

//****************************************************************************
//                      void TestCnvBar (void)
//  This function shows the capabilities of the graphic when using GOAL.
//  It shows a moving rectangle.
//  The following functions have been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateDrawing() : To build drawing (Rectangle, ...) screen.
//   - GoalClrDrawing() : To clear all drawing on screen.
//   - GoalDrawRect() : To display a rectangle on screen.
//   - GoalDestroyDrawing() : To destroy all drawing on screen.
//   Support B&W, color and touch terminals.
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static int TestCnvBar(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xDrawing;
	T_GL_COLOR ulPen, ulBrush;
	T_GL_COORD x1, y1;
	T_GL_COORD x2, y2;
    byte ucIdx;
    int iKey;
    int iRand, iRet=-1;

	// Show a moving rectangle
	// ***********************
    xDrawing = GoalCreateDrawing(xGoal, GL_ENCODING_UTF8);
    CHECK(xDrawing!=NULL, lblKO);
	iRet = GoalClrDrawing(xDrawing, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

    x1 = cnvW / 2 - 1;
    y1 = cnvH / 2 - 1;
    x2 = cnvW / 2 + 1;
    y2 = cnvH / 2 + 1;

    ucIdx=0;
    while(1)
    {
    	if (IsColorDisplay())          // Color display?
    	{                              // Yes
    		ulPen = tulColor[ucIdx];
    		ulBrush = tulColor[ucIdx];
    	}
    	else                           // No
    	{
    		ulPen = GL_COLOR_BLACK;
    		ulBrush = GL_COLOR_BLACK;
    	}

        iRet = GoalDrawRect(xDrawing, ulPen, ulBrush, x1, y1, x2-x1, y2-y1, 0, true);
		CHECK(iRet>=0, lblKO);         // Show rectangle

		iKey = GoalGetKey(xDrawing, xGoal, false, 100, false); // Get all keys

    	if (IsColorDisplay())          // Color display?
    	{                              // Yes
    		ulPen = GL_COLOR_BLACK;
    		ulBrush = GL_COLOR_BLACK;
    	}
    	else                           // No
    	{
    		ulPen = GL_COLOR_WHITE;
    		ulBrush = GL_COLOR_WHITE;
    	}

        iRet = GoalDrawRect(xDrawing, ulPen, ulBrush, x1, y1, x2-x1, y2-y1, 0, false);
		CHECK(iRet>=0, lblKO);         // Clear rectangle

		if ((iKey == GL_KEY_CANCEL) || (iKey == GL_KEY_VALID))
		{
			iRet=iKey;                 // Exit on key Cancel/Valid
			break;
		}

		if (iKey == 0)
		{
			iRand = rand();            // Key randomly generated
			iRand %= strlen(pcS);
			iKey = *(pcS + iRand);
		}

		switch (iKey)
		{
		case '4':                      // Moving left
			if(!x1) continue;
			x1--; x2--;
			break;
		case '6':                      // Moving right
			if(x2 >= cnvW - 1) continue;
			x1++; x2++;
			break;
		case '2':                      // Moving up
			if(!y1) continue;
			y1--; y2--;
			break;
		case '8':                      // Moving down
			if(y2 >= cnvH - 1) continue;
			y1++; y2++; break;
		case '1':                      // Moving North/West
			if(!x1) continue; if(!y1) continue;
			x1--; x2--; y1--; y2--;
			break;
		case '3':                      // Moving North/East
			if(x2 >= cnvW - 1) continue;
			if(!y1) continue;
			x1++; x2++; y1--; y2--;
			break;
		case '7':                      // Moving South/West
			if(!x1) continue;
			if(y2 >= cnvH - 1) continue;
			x1--; x2--; y1++; y2++;
			break;
		case '9':                      // Moving South/East
			if(x2 >= cnvW - 1) continue; if(y2 >= cnvH - 1) continue;
			x1++; x2++; y1++; y2++;
			break;
		case 'A':                      // Growing
			if(!x1) continue; if(x2 >= cnvW - 1) continue;
			if(!y1) continue; if(y2 >= cnvH - 1) continue;
			x1--; x2++; y1--; y2++; 
			break;
		case '@':                      // Shrink
			if(x1 + 1 >= x2 - 1) continue;
			if(y1 + 1 >= y2 - 1) continue;
			x1++; x2--; y1++; y2--;
			break;
		case '5':                      // Change color
			ucIdx++;
			if (ucIdx == 5)
				ucIdx=0;
			break;
		}
    }

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if(xDrawing)                       // Destroy drawing
		GoalDestroyDrawing(&xDrawing);
	return iRet;
}

//****************************************************************************
//                      void testCnvForms (void)
//  This function shows the capabilities of the graphic when using GOAL.
//  It shows different forms and animations.
//  The following functions have been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateDrawing() : To build drawing (Rectangle, ...) screen.
//   - GoalClrDrawing() : To clear all drawing on screen.
//   - GoalDrawRect() : To display a rectangle on screen.
//   - GoalDrawEllipse(): To display an ellipse on screen.
//   - GoalDrawLine(): To display a line on screen.
//   - GoalDrawText(): To display a text on screen.
//   - GoalDestroyDrawing() : To destroy all drawing on screen.
//   Support B&W, color and touch terminals.
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static int TestCnvForm(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xDrawing;
	ST_GRAPHIC txG[MAX_LINE];
	byte ucIdx=0;
	T_GL_SIZE xSize;
	int i, j, k = 0;
	int iRet;

	// Show different forms and animations
	// ***********************************
    xDrawing = GoalCreateDrawing(xGoal, GL_ENCODING_UTF8);
    CHECK(xDrawing!=NULL, lblKO);   // Create drawing and clear it
	iRet = GoalClrDrawing(xDrawing, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

    if (IsColorDisplay())           // Color display?
    	memcpy(txG, txColor, MAX_LINE*sizeof(ST_GRAPHIC)); // Yes, color initialization
    else
    	memcpy(txG, txBW, MAX_LINE*sizeof(ST_GRAPHIC));    // No, B&W initialization

	// Rectangles
	// ==========
	iRet = GoalDrawRect(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 0, 0, 10, 20, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Show rectangle and fill it (RED/RED or BLACK/BLACK)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;
	iRet = GoalDrawRect(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 10, 20, 22, 39, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Display rectangle and empty it (GREEN/BLACK or BLACK/WHITE)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

   	// Circles
   	// =======
	iRet = GoalDrawEllipse(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 21, 39, 10, 18, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Show circle and empty it (BLUE/BLACK or BLACK/WHITE)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;
	iRet = GoalDrawEllipse(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 21, 39, 5, 9, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Show circle and fill it (YELLOW/YELLOW or BLACK/BLACK)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

	// Texts
   	// =====
   	xSize = GL_GraphicLib_GetScreenSize(xGoal);
	iRet = GoalDrawRect(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 40, 6, 22, 26, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Show rectangle and empty it (RED/RED or BLACK/BLACK)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;
	if (IsColorDisplay())           // Color display?
	{                               // Yes, show text (WHITE)
		if((xSize.width == 240) && (xSize.height == 320))
			iRet = GoalDrawText(xDrawing, "Txt", &xFontColor, txG[ucIdx].ulPen, 43, 10, 1*1000, true);
		else
			iRet = GoalDrawText(xDrawing, "Text 1", &xFontColor, txG[ucIdx].ulPen, 43, 10, 1*1000, true);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                               // No, show reverse text (WHITE)
		iRet = GoalDrawText(xDrawing, "Text1", &xFontBW, txG[ucIdx].ulPen, 43, 14, 1*1000, true);
		CHECK(iRet>=0, lblKO);
	}
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

	iRet = GoalDrawRect(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 40, 38, 22, 26, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Display rectangle and empty it (RED/BLACK or BLACK/WHITE)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;
   	if (IsColorDisplay())           // Color display?
   	{                               // Yes, show text (WHITE)
		if((xSize.width == 240) && (xSize.height == 320))
			iRet = GoalDrawText(xDrawing, "Txt", &xFontColor, txG[ucIdx].ulPen, 43, 42, 1*1000, true);
		else
			iRet = GoalDrawText(xDrawing, "Text 2", &xFontColor, txG[ucIdx].ulPen, 43, 42, 1*1000, true);
   		CHECK(iRet>=0, lblKO);
   	}
   	else
   	{                               // No, show text (BLACK)
   		iRet = GoalDrawText(xDrawing, "Text2", &xFontBW, txG[ucIdx].ulPen, 43, 46, 1*1000, true);
   		CHECK(iRet>=0, lblKO);
	}
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

   	if (IsColorDisplay())           // Color display?
   	{                               // Yes, show text (WHITE)
		if((xSize.width == 240) && (xSize.height == 320))
			iRet = GoalDrawText(xDrawing, "Txt", &xFontColor, GL_COLOR_WHITE, 43, 70, 1*1000, true);
		else
			iRet = GoalDrawText(xDrawing, "Text 3", &xFontColor, GL_COLOR_WHITE, 43, 70, 1*1000, true);
   		CHECK(iRet>=0, lblKO);
   	}
   	else
   	{                               // No, show text (WHITE)
   		iRet = GoalDrawText(xDrawing, "Text3", &xFontBW, GL_COLOR_BLACK, 43, 74, 1*1000, true);
   		CHECK(iRet>=0, lblKO);
	}
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

	iRet = GoalDrawLine(xDrawing, txG[ucIdx].ulPen, 43, 88, 59, 88, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Show under line (RED or BLACK)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

	// Ellipse
   	// =======
	iRet = GoalDrawEllipse(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 80, 70, 16, 16, 1*1000, true);
	CHECK(iRet>=0, lblKO);          // Show ellipse and empty it (BLUE/BLACK or BLACK/WHITE)
   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
   	ucIdx++;

	// Set Pixel and draw a pattern rectangle
   	// ======================================
	k=0;                            // Show pixels (YELLOW or BLACK)
	for(j=0; j<24; j++, j++)
	{
		for(i=0; i<30; i++)
		{
			if((k % 3) == 0)
			{
				iRet = GoalDrawLine(xDrawing, txG[ucIdx].ulPen, 69+i, j+1, 69+i, j+1, 0, true);
				CHECK(iRet>=0, lblKO);
			}
			k++;
		}
		k++;
	}
	ucIdx++;

	// Draw ball animation
	// ===================
	i=0;
	while(1)
	{
		iRet = GoalDrawRect(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, 10, 60, 22, 39, 0, false);
		CHECK(iRet>=0, lblKO);          // Show rectangle and empty it (YELLOW/BLACK or BLACK/WHITE)
	   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
	   	ucIdx++;
		iRet = GoalDrawEllipse(xDrawing, txG[ucIdx].ulPen, txG[ucIdx].ulBrush, tcX[i], tcY[i], 2, 4, 200, true);
		CHECK(iRet>=0, lblKO);          // Show circle (ball) and empty it (RED/RED or BLACK/WHITE)
	   	CHECK(iRet==0, lblEnd);         // Exit on valid/cancel key
	   	ucIdx--;

		i++;
		if(i == 12)
			i=0;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                  // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if(xDrawing)                        // Destroy drawing
		GoalDestroyDrawing(&xDrawing);
	return iRet;
}

//****************************************************************************
//                          void Draw (void)                            
//  This function starts the animation demo.      
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Draw(void) 
{
	// Local variables 
    // ***************
    int iRet;
	
	// Graphic display in progress
	// ***************************
    iRet = TestCnvPixel();   // Random pixels
    if (iRet == GL_KEY_CANCEL)
    	return;

    iRet = TestCnvLine();    // Rotating lines
	if (iRet == GL_KEY_CANCEL)
		return;

	iRet = TestCnvBar();     // Moving rectangle
	if (iRet == GL_KEY_CANCEL)
		return;

	TestCnvForm();           // Showing forms
}

//****************************************************************************
//                            void Image (void)
//  This function shows the capabilities of the graphic when using GOAL.
// 	The following images formats are supported:
//                  JPEG, PNG, BMP, GIF and owner WGU
//  It shows and prints image (JPG or BMP).
//  The following functions have been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreatePicture() : To build image (JPEG, BMP, ...) screen.
//   - GoalClrPicture() : To clear image on screen.
//   - GoalDspPicture() : To display an image on screen.
//   - GoalDestroyPicture() : To destroy image on screen.
//   - GoalPrnPicture() : To add an image on document.
//  This function has no parameters.
//  This function has no return value.
//****************************************************************************

void Image(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xPicture=NULL;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
	byte p;
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
					   // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	int iRet;

	// Show image on screen
	// ********************
	xPicture = GoalCreatePicture(xGoal);
    CHECK(xPicture!=NULL, lblKO);                      // Create picture on screen and clear it
	iRet = GoalClrPicture(xPicture, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	// Format JPG (Color terminal) or BMP (B&W terminal) file
	// ======================================================
	iRet = FS_mount("/HOST", &uiMode);                 // Disk HOST initialization
	CHECK(iRet==FS_OK, lblHostKO);
    if (IsColorDisplay())                              // Color terminal?
    {
    	iRet = FS_exist("/HOST/TIGER_CL.JPG");         // Yes, check if JPG present
    	CHECK(iRet==FS_OK, lblFile1Missing);
                                                       // Display JPG
    	iRet = GoalDspPicture(xPicture, NULL, "file://flash/HOST/TIGER_CL.JPG", &xImage, 0, true);
    	CHECK(iRet>=0, lblKO);
    }
    else
    {
    	iRet = FS_exist("/HOST/TIGERD_BW.BMP");        // No, check if BMP present
   		CHECK(iRet==FS_OK, lblFile2Missing);
                                                       // Display BMP
    	iRet = GoalDspPicture(xPicture, NULL, "file://flash/HOST/TIGERD_BW.BMP", &xImage, 0, true);
    	CHECK(iRet>=0, lblKO);
	}

	// Print image on ticket
	// *********************
	p=0;                                               // Create a document
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);

    if (IsColorDisplay())                              // Color terminal?
    {
    	iRet = FS_exist("/HOST/TIGER_CL.JPG");         // Yes, check if JPG present
    	CHECK(iRet==FS_OK, lblFile1Missing);

    	xLine = xPrinter;                              // Build document (Demo, Image)
    	xLine.bReverse = TRUE;
    	xLine.usSizeWidth = 100;
    	xLine.xMargin.usBottom = PIXEL_BOTTOM;
    	iRet = GoalPrnLine(xDocument, p++, "BMP Demo", &xLine);
    	CHECK(iRet>=0, lblKO);
                                                       // Image JPG
    	iRet = GoalPrnPicture(xDocument, p++, "file://flash/HOST/TIGER_CL.JPG", &xBorder);
    	CHECK(iRet>=0, lblKO);
    }
    else
    {
    	iRet = FS_exist("/HOST/TIGERP_BW.BMP");        // No, check if BMP present
   		CHECK(iRet==FS_OK, lblFile3Missing);

    	xLine = xPrinter;                              // Build document (Demo, Image)
    	xLine.bReverse = TRUE;
    	xLine.usSizeWidth = 100;
    	xLine.xMargin.usBottom = PIXEL_BOTTOM;
    	iRet = GoalPrnLine(xDocument, p++, "BMP Demo", &xLine);
    	CHECK(iRet>=0, lblKO);
                                                       // Image BMP
    	iRet = GoalPrnPicture(xDocument, p++, "file://flash/HOST/TIGERP_BW.BMP", &xBorder);
    	CHECK(iRet>=0, lblKO);
	}

	iRet = GoalPrnLine(xDocument, p++, "\n\n", &xPrinter);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xPicture, xGoal, true, 30*1000, true);  // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblHostKO:                                             // HOST disk failed
	GL_Dialog_Message(xGoal, NULL, "HOST Disk failed", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblFile1Missing:                                       // File JPG not found
	GL_Dialog_Message(xGoal, NULL, "File TIGER_CL.JPG\nMissing from Host", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFile2Missing:                                       // File BMP not found
	GL_Dialog_Message(xGoal, NULL, "File TIGERD_BW.BMP\nMissing from Host", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFile3Missing:                                       // File BMP not found
	GL_Dialog_Message(xGoal, NULL, "File TIGERP_BW.BMP\nMissing from Host", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    FS_unmount("/HOST");                               // Disk HOST deactivation

	if(xPicture)
		GoalDestroyPicture(&xPicture);                 // Destroy picture
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}

//****************************************************************************
//                           void Animated (void)
//  This function shows the capabilities of the graphic when using GOAL.
// 	It shows on screen an animated GIF.
//   - GoalCreatePicture() : To build image (JPEG, BMP, ...) screen.
//   - GoalClrPicture() : To clear image on screen.
//   - GoalDspPicture() : To display an image on screen.
//   - GoalDestroyPicture() : To destroy image on screen.
//  This function has no parameters.
//  This function has no return value.
//****************************************************************************

void Animated(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xPicture=NULL;
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
					   // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	int iRet;

	// Show animated image on screen
	// *****************************
	xPicture = GoalCreatePicture(xGoal);
    CHECK(xPicture!=NULL, lblKO);                    // Create picture on screen and clear it
	iRet = GoalClrPicture(xPicture, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	// Display GIF file
	// ================
	iRet = FS_mount("/HOST", &uiMode);               // Disk HOST initialization
	CHECK(iRet==FS_OK, lblHostKO);
	if (IsColorDisplay())                            // Color terminal?
	{
		iRet = FS_exist("/HOST/MICHAEL.GIF");        // Yes, check if color GIF present
		CHECK(iRet==FS_OK, lblFile1Missing);
                                                     // Display animated GIF
		iRet = GoalDspPicture(xPicture, NULL, "file://flash/HOST/MICHAEL.GIF", &xImage, 30*1000, true);
		CHECK(iRet>=0, lblKO);
	}
	else
	{
		iRet = FS_exist("/HOST/POPPING.GIF");        // No, check if B&W GIF present
		CHECK(iRet==FS_OK, lblFile2Missing);
		                                             // Display animated GIF
		iRet = GoalDspPicture(xPicture, NULL, "file://flash/HOST/POPPING.GIF", &xImage, 30*1000, true);
		CHECK(iRet>=0, lblKO);
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblHostKO:                                           // HOST disk failed
	GL_Dialog_Message(xGoal, NULL, "HOST Disk failed", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblFile1Missing:                                     // File color GIF not found
	GL_Dialog_Message(xGoal, NULL, "File MICHAEL.GIF\nMissing from Host", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFile2Missing:                                     // File B&W GIF not found
	GL_Dialog_Message(xGoal, NULL, "File POPPING.GIF\nMissing from Host", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    FS_unmount("/HOST");                             // Disk HOST deactivation

	if(xPicture)
		GoalDestroyPicture(&xPicture);               // Destroy picture
}

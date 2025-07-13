//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  GRAPHIC.C                          (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  graphic functions:
//              Pixels, lines, rectangles, forms, animations, logo... 
//                                                                            
//  List of routines in file :
//      testCnvPixel : Display pixels randomly.
//      testCnvLine : Display rotating lines.
//      testCnvBar : Display a moving rectangle. 
//      testCnvForm : Display different forms and animations.  
//      Draw : Start the animation demo.
//      Logo : Start the logo demo.                                        
//                            
//  File history :
//  120508-BK : File created 
//                                                                           
//****************************************************************************
//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"

// Bitmaps definitions. 
#include "Bmp\Anim1.h"
#include "Bmp\Anim2.h"
#include "Bmp\Anim3.h"
#include "Bmp\Anim4.h"
#include "Bmp\Anim5.h"
#include "Bmp\Anim6.h"
#include "Bmp\Anim7.h"
#include "Bmp\OldYoungD.h"
#include "Bmp\OldYoungP.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxKbd;      // Peripheral file Keyboard
int rand(void);

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define cnvW    128
#define cnvH    64
#define cnvD    1 
#define cnvP (1<<cnvD)

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
const byte *__ANIM[12] =
{
	anim1, anim2, anim3, anim4, anim5, anim6, anim7,
	anim6, anim5, anim4, anim3, anim2
};

//****************************************************************************
//                      void testCnvPixel (void)                            
//  This function displays pixels ramdomly (Screen saver).      
//       _SetPixel() : Put pixel on a canvas
//       PaintGraphic() : Display the canvas
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static void testCnvPixel(void)
{
	// Local variables
    // ***************
    word x, y;
    byte c;
	char cKey;
    int iSta;

    _clrscr();
    PaintGraphics();

    // Screen saver
    // ************
	reset_buf(pxKbd, _receive_id);         // Reset keyboard FIFO
    while(1) 
	{
        x = (word) (rand() % cnvW);
        y = (word) (rand() % cnvH);
        c = (byte) (rand() % cnvP);

		_SetPixel(x, y, c);                // Put a pixel (x,y) with c (on or off) on a canvas          
        PaintGraphics();                   // Display the canvas 

		iSta = ttestall(KEYBOARD, 1);
 
		if(iSta & KEYBOARD)                // Key event
		{
			cKey = getchar();              // Exit on red or green key
		    if ((cKey == T_ANN) || (cKey == T_VAL)) break;
		}
    }
}

//****************************************************************************
//                      void testCnvLine (void)                            
//  This function displays rotating lines.      
//       _DrawLine() : Put lines on a canvas
//       PaintGraphic() : Display the canvas
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static void testCnvLine(void)
{
	// Local variables
    // ***************
    word x1, y1;
    word x2, y2;
    word dx, dy;
    byte ucClr;
    byte ucIdx;
	char cKey;
	bool bExit=FALSE;
    int iSta;

	_clrscr();
    PaintGraphics();

    // Rotating lines
    // **************
    dx = cnvW / 16;
    dy = cnvH / 16;

    ucClr=1;
    reset_buf(pxKbd, _receive_id);             // Reset keyboard FIFO
    while(1) {
        y1 = 0;
        x2 = cnvW - 1;
        for (ucIdx=1; ucIdx<16; ucIdx++) {
            x1 = ucIdx * dx;
            y2 = ucIdx * dy;

			_DrawLine(x1, y1, x2, y2, ucClr);
		    PaintGraphics();                   // Display the canvas 

            iSta = ttestall(KEYBOARD, 5);
			if(iSta & KEYBOARD)                // Key event
			{
				cKey = getchar();              // Exit on red or green key
				if ((cKey == T_ANN) || (cKey == T_VAL)) {
                    bExit=TRUE;
					break;     
				}
			}
        }

		if (bExit) break;

        x1 = cnvW - 1;
        y2 = cnvH - 1;
        for (ucIdx=1; ucIdx<16; ucIdx++) {
            y1 = ucIdx * dy;
            x2 = cnvW - ucIdx * dx;

			_DrawLine(x1, y1, x2, y2, ucClr);
		    PaintGraphics();                   // Display the canvas 

			iSta = ttestall(KEYBOARD, 5);
			if(iSta & KEYBOARD)                // Key event
			{
				cKey = getchar();              // Exit on red or green key
				if ((cKey == T_ANN) || (cKey == T_VAL)) {
                    bExit=TRUE;
					break;     
				}
			}
        }

		if (bExit) break;

        y1 = cnvH - 1;
        x2 = 0;
        for (ucIdx=1; ucIdx<16; ucIdx++) {
            x1 = cnvW - ucIdx * dx;
            y2 = cnvH - ucIdx * dy;

			_DrawLine(x1, y1, x2, y2, ucClr);
		    PaintGraphics();                   // Display the canvas 

			iSta = ttestall(KEYBOARD, 5);
			if(iSta & KEYBOARD)                // Key event
			{
				cKey = getchar();              // Exit on red or green key
				if ((cKey == T_ANN) || (cKey == T_VAL)) {
                    bExit=TRUE;
					break;     
				}
			}
        }

		if (bExit) break;

        x1 = 0;
        y2 = 0;
        for (ucIdx=1; ucIdx<16; ucIdx++) {
            y1 = cnvH - ucIdx * dy;
            x2 = ucIdx * dx;

  		    _DrawLine(x1, y1, x2, y2, ucClr);
		    PaintGraphics();                  // Display the canvas 

            iSta = ttestall(KEYBOARD, 5);
			if(iSta & KEYBOARD)               // Key event
			{
				cKey = getchar();             // Exit on red or green key
				if ((cKey == T_ANN) || (cKey == T_VAL)) {
                    bExit=TRUE;
					break;     
				}
			}
		}

		if (bExit) break;
 
        if(ucClr == 1)
            ucClr=0;
        else
            ucClr=1;
    }
}

//****************************************************************************
//                      void testCnvBar (void)                            
//  This function displays a moving rectangle.      
//       _DrawRect() : Put a rectangle on a canvas
//       PaintGraphic() : Display the canvas
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static void testCnvBar(void)
{
	// Local variables
    // ***************
    word x1, y1;
    word x2, y2;
    byte ucClr;
    char cKey;
    const char *pcS = "123456789A@";
    int iSta, iRet;

	_clrscr();
    PaintGraphics();

    // Moving rectangle
    // ****************
    x1 = cnvW / 2 - 1;
    y1 = cnvH / 2 - 1;
    x2 = cnvW / 2 + 1;
    y2 = cnvH / 2 + 1;
    ucClr=1;
    reset_buf(pxKbd, _receive_id);                  // Reset keyboard FIFO
    while(1) {
        ucClr = (byte) (rand() % cnvP);

		_clrscr();
        _DrawRect(x1, y1, x2, y2, 0, _OFF_, ucClr);
		PaintGraphics();                            // Display the canvas 

		iSta = ttestall(KEYBOARD, 10);
 
		if(iSta & KEYBOARD)                         // Key event
		{
			cKey = getchar();                       // Exit on red or green key
		    if ((cKey == T_ANN) || (cKey == T_VAL)) break;
		} else {
			iRet = rand();
			iRet %= 11;
			cKey = *(pcS + iRet);
		}
			
		switch (cKey) {
		case '4':            //left
			if(!x1) continue;
			x1--; x2--;
			break;
		case '6':            //right
			if(x2 >= cnvW - 1) continue;
			x1++; x2++;
			break;
		case '2':            //up
			if(!y1) continue;
			y1--; y2--;
			break;
		case '8':            //down
			if(y2 >= cnvH - 1) continue;
			y1++; y2++; break;
		case '1':            //NW
			if(!x1) continue; if(!y1) continue;
			x1--; x2--; y1--; y2--;
			break;
		case '3':            //NE
			if(x2 >= cnvW - 1) continue;
			if(!y1) continue;
			x1++; x2++; y1--; y2--;
			break;
		case '7':            //SW
			if(!x1) continue;
			if(y2 >= cnvH - 1) continue;
			x1--; x2--; y1++; y2++;
			break;
		case '9':            //SE
			if(x2 >= cnvW - 1) continue; if(y2 >= cnvH - 1) continue;
			x1++; x2++; y1++; y2++;
			break;
		case 'A':            //grow
			if(!x1) continue; if(x2 >= cnvW - 1) continue;
			if(!y1) continue; if(y2 >= cnvH - 1) continue;
			x1--; x2++; y1--; y2++; 
			break;
		case '@':            //shrink
			if(x1 + 1 >= x2 - 1) continue;
			if(y1 + 1 >= y2 - 1) continue;
			x1++; x2--; y1++; y2--;
			break;
		case '5':            //blink
			ucClr = 1 - ucClr;
			break;
		}
    }
}

//****************************************************************************
//                      void testCnvForms (void)                            
//  This function displays different forms and animations.      
//       DrawRect() : Display a rectangle
//       DrawCircle() : Display a circle
//       DrawEllipse() : Display Ellipse
//       DrawString() : Display a string
//       DrawLine() : Display a line
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Animation done
//     <0 : Animation failed                                       
//****************************************************************************

static void testCnvForm(void)
{
	// Local variables
    // ***************
	int iWidth;
	int i, j, k = 0;
	int iIndex;			                                 // Image index.

	_clrscr();
    PaintGraphics();

    // Forms and animations
    // ********************
	// Rectangles
	DrawRect(0, 0, 10, 10, 0, _ON_, _ON_);               // Fill Rect.
	ttestall(0, 1*100);
	DrawRect(10, 10, 30, 30, 1, _ON_, _OFF_);            // Empty Rect.
	ttestall(0, 1*100);

	// Circles
	DrawCircle(20, 20, 10, _OFF_);                       // Empty circle.
	ttestall(0, 1*100);
	DrawCircle(20, 20, 5,  _ON_ );                       // Fill circle.
	ttestall(0, 1*100);

	// Text
	DrawString("Text1", 40, 10, _ON_);	                 // Inverted text.
	ttestall(0, 1*100);

	// Text with border.
	// Calculate the size of the string
	// and draw the border rectangle first.
	iWidth = StringWidth( "Text2" );                     // Border
	DrawRect(40-1, 30-1, 40 + iWidth + 1,  30 + _SIZE_MEDIUM_ + 1, 1, _ON_, _OFF_);
	ttestall(0, 1*100);
	DrawString("Text2", 40, 30, _OFF_);
	ttestall(0, 1*100);

	// Underlined text.
	iWidth = StringWidth( "Text3" );
	DrawString("Text3", 40, 50, _OFF_);
	ttestall(0, 1*100);
	DrawLine(40, 50 + _SIZE_MEDIUM_, 40 + iWidth,  50 + _SIZE_MEDIUM_, _ON_);
	ttestall(0, 1*100);

	// Ellipse
	DrawEllipse(100, 40, 20, 10, _OFF_);                 // Empty.
	ttestall(0, 1*100);

	// Set Pixel.
	// Draw a pattern rectangle.
	k=0;
	for(j=0; j<24; j++)
	{
		for(i=0; i<48; i++)
		{
			if((k % 3) == 0)
			{
				SetPixel(80 + i, j, _ON_);
			}
			k++;
		}
		k++;
	}

	// Draw Animation
	// Wait for a key pressed.
    reset_buf(pxKbd, _receive_id);                        // Reset keyboard FIFO
	iIndex=0;
	do
	{
		_DisplayBitmap(10, 35, (byte*)__ANIM[iIndex], 8, _OFF_);
		PaintGraphics();

		// Process Next Image.
		iIndex++;
		if(iIndex == 12 ) iIndex=0;
	}
	while(ttestall(KEYBOARD, 20) != KEYBOARD);
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
       // Empty
	
	// Graphic display in progress
	// ***************************
    testCnvPixel();                                     // Random pixels
	testCnvLine();                                      // Rotating lines
	testCnvBar();                                       // Moving rectangle
	testCnvForm();                                      // Showing forms

	_clrscr();                                          // Clear screen context
    PaintGraphics();                                    // Display the graphic context
}

//****************************************************************************
//                      void Logo (void)                            
//  This function prints and displays a logo.
//  The logo is converted from .BMP to an unsigned char bit map buffer.
//  See Tool "Bmp converter" inside SDK.
//       DisplayBitmap() : Display a bit map
//       defprinterpattern() : Print a bit map
//  This function has no parameters.    
//  This function has return value.
//    >=0 : Bit map buffer done
//     <0 : Bit map buffer failed
//****************************************************************************

void Logo(void)
{
	// Local variables
    // ***************
    int i, iRet;

	// Display Logo by changing mode
	// *****************************
	for (i=0; i<4; i++) {
		DisplayBitmap (0, 0, (byte*)OldYoungD, 8, _OFF_);
        ttestall (0, 1*100);
		DisplayBitmap (0, 0, (byte*)OldYoungD, 8, _ON_);
        ttestall (0, 1*100);
	}
	DisplayBitmap(0, 0, (byte*)OldYoungD, 8, _OFF_);

	// Print Logo by pattern
	// *********************
	iRet = pprintf("\x1b""E""          BMP Demo\n\n"      // Print demo in progress
				   "\x1b""F"); CHECK(iRet>=0, lblKO);
	iRet = defprinterpattern('\xFF', (char *) OldYoungP); // Pattern \xFF set to logo OldYoungP
	CHECK(iRet==0, lblKO);
	iRet = pprintf("\xFF\n\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	ttestall(0, 5*100);                                   // Delay 5s

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                            // Clear screen
	DisplayMedium(0, 0, "Processing Error");              // Oops! error
    ttestall(0, 5*100);                                   // Delay 5s
lblEnd: 
    defprinterpattern ('\xFF', (char*)PT_NULL);           // Pattern \xFF reseted
	return;
}

//****************************************************************************
//                         void BMP (void)
//  This function prints and displays a BMP file format.
//  Size max 384/1024px.
//       SetBmp() : Display a BMP file format
//       _PrintBmpXY() : Print a BMP file format
//  This function has no parameters.
//  This function has return value.
//    >=0 : BMP done
//     <0 : BMP failed
//****************************************************************************

void BMP(void)
{
	// Local variables
    // ***************
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
					   // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	S_FS_FILE *pxFile=NULL, *pxFile1=NULL;
	char *pcBMP=NULL, *pcBMP1=NULL;
	int iLenData, iRet;

	_clrscr();                                                                  // Clear screen context
    PaintGraphics();                                                            // Display the graphic context

	// Display BMP file
	// ****************
	iRet = FS_mount ("/HOST", &uiMode); CHECK(iRet==FS_OK, lblHostKO);          // Disk HOST initialization
	pxFile = FS_open ("/HOST/TIGERD.BMP", "r");                                 // Open the file TIGERD.BMP
	CHECK(pxFile!=NULL, lblFileMissing);
    iLenData = FS_length(pxFile);                                               // File length in bytes
    pcBMP = umalloc(iLenData); CHECK(pcBMP!=NULL, lblKO);                       // BMP dynamic memory space
    iRet = FS_read(pcBMP, 1, iLenData, pxFile);                                 // Read data from file into BMP memory space
    CHECK(iRet==iLenData, lblHostKO);

	iRet = SetBmp(0, 0, (byte*)pcBMP, _OFF_); CHECK(iRet==BMP_OK, lblKO);       // Display Bitmap at BMP format from BMP memory space

	// Print BMP file
	// **************
	pxFile1 = FS_open ("/HOST/TIGERP.BMP", "r");                                // Open the file TIGERP.BMP
	CHECK(pxFile1!=NULL, lblFile1Missing);
    iLenData = FS_length(pxFile1);                                              // File length in bytes
    pcBMP1 = umalloc(iLenData); CHECK(pcBMP1!=NULL, lblKO);                     // BMP dynamic memory space
    iRet = FS_read(pcBMP1, 1, iLenData, pxFile1);                               // Read data from file into BMP memory space
    CHECK(iRet==iLenData, lblHostKO);

    iRet = pprintf("\x1b""E""         BMP Demo\n\n"                             // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);
    InitPrinterBitmap(220);                                                     // Allow 220 pixels height(default 128/ max 1024)
    iRet = _PrintBmpXY(0, 0, (byte*)pcBMP1, _OFF_); CHECK(iRet==BMP_OK, lblKO); // Print Bitmap at BMP format from BMP memory space
	PaintPrinterGraphics();
	iRet = pprintf ("\n\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	ttestall(0, 5*100);                                                         // Delay 5s

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:
	_clrscr();                                            				        // Clear screen
	DisplayMedium(0, 0, "Processing Error");              				        // Oops! error
    ttestall(0, 5*100);                                                         // Delay 5s
    goto lblEnd;
lblHostKO:                                                                      // HOST disk failed
	_clrscr();                                            				        // Clear screen
	DisplayMedium(0, 0, "HOST Disk failed");              				        // Oops! error
    ttestall(0,5*100);                                                          // Delay 5s
    goto lblEnd;
lblFileMissing:                                                                 // File not found
	_clrscr();                                            				        // Clear screen
	DisplayMedium(0, 0, "FILE NOT FOUND:");              				        // Oops! error
	DisplayMedium(1, 0, "/HOST/TIGERD.BMP");
    ttestall(0,5*100);                                                          // Delay 5s
    goto lblEnd;
lblFile1Missing:                                                                // File1 not found
	_clrscr();                                            				        // Clear screen
	DisplayMedium(0, 0, "FILE NOT FOUND:");              				        // Oops! error
	DisplayMedium(1, 0, "/HOST/TIGERP.BMP");
    ttestall(0,5*100);                                                          // Delay 5s
lblEnd:
    if (pcBMP)
      	ufree(pcBMP);                                                           // Release memory space
    if (pcBMP1)
    	ufree(pcBMP1);                                                          // Release memory space

    if (pxFile)
     	FS_close(pxFile);                                                       // Close file TIGERD.BMP
     if (pxFile1)
     	FS_close(pxFile1);                                                      // Close file TIGERP.BMP

    FS_unmount("/HOST");                                                        // Disk HOST deactivation
}

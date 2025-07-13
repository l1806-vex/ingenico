//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  KEYBOARD.C                         (Copyright INGENICO 2012)
//============================================================================
//  Created :       11-July-2012     Kassovic
//  Last modified : 11-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :
//                        *** Keyboard management ***
//  This file uses GOAL to detect key pressed (keyboard) and touched (touch screen):
//    # Manager goal must be loaded
//    # Customized mode
//      . By API(s) (used inside this file)
//        Management done by call back to process keyboard and touch screen
//
//  List of routines in file :  
//      Keyboard : Key detection demo.
//                            
//  File history :
//  071112-BK : File created
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

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Keyboard screen (Goal)
// ========================================
static const ST_DSP_LINE txKeyboard[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_RED,   46, FALSE, {0, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, TRUE,  60, FALSE, {0, 7, 0, 7}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,  46, FALSE, {0, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, TRUE,  60, FALSE, {0, 7, 0, 7}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} }
};

//****************************************************************************
//                         void Keyboard (void)                            
//  This function shows the key number and the key value when the key is
//  pressed on keyboard or touched on touch screen.
//   - ttestall() : Wait for key pressed on keyboard or a key touched on screen.
//   - getchar() : Retrieve a key pressed on keyboard (OS function).
//   - GoalGetKey() : Retrieve a key pressed on keyboard (shortcut) or a key
//                    touched on touch screen (See file Goal.c)
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Keyboard(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	char tcKey[16+1];    // Key name
	char tcValue[16+1];  // Key Value
    int iKey, iRet;

	// Key detection in progress
	// *************************
	xScreen = GoalCreateScreen(xGoal, txKeyboard, NUMBER_OF_LINES(txKeyboard), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);            // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_VALID | KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

    iRet = GoalDspLine(xScreen, 0, "Press a key", &txKeyboard[0], 0, true);
	CHECK(iRet>=0, lblKO);                  // Prompt for key pressed/touched

    memset(tcKey, 0, sizeof(tcKey));
    memset(tcValue, 0, sizeof(tcValue));
    while (1)
	{
    	iKey = GoalGetKey(xScreen, xGoal, false, 30*1000, true); // Get all keys

    	if(iKey == 0)
            break;                         // Exit on timeout

        switch (iKey)
        {
        case GL_KEY_0:                     // Key returned by keyboard : '0' (0x0030)
        	strcpy(tcKey, "KEY 0");
        	break;
        case GL_KEY_1:                     // Key returned by keyboard : '1' (0x0031)
        	strcpy(tcKey, "KEY 1");
        	break;
        case GL_KEY_2:                     // Key returned by keyboard : '2' (0x0032)
        	strcpy(tcKey, "KEY 2");
        	break;
        case GL_KEY_3:                     // Key returned by keyboard : '3' (0x0033)
        	strcpy(tcKey, "KEY 3");
        	break;
        case GL_KEY_4:                     // Key returned by keyboard : '4' (0x0034)
        	strcpy(tcKey, "KEY 4");
        	break;
        case GL_KEY_5:                     // Key returned by keyboard : '5' (0x0035)
        	strcpy(tcKey, "KEY 5");
        	break;
        case GL_KEY_6:                     // Key returned by keyboard : '6' (0x0036)
        	strcpy(tcKey, "KEY 6");
        	break;
        case GL_KEY_7:                     // Key returned by keyboard : '7' (0x0037)
        	strcpy(tcKey, "KEY 7");
        	break;
        case GL_KEY_8:                     // Key returned by keyboard : '8' (0x0038)
        	strcpy(tcKey, "KEY 8");
        	break;
        case GL_KEY_9:                     // Key returned by keyboard : '9' (0x0039)
        	strcpy(tcKey, "KEY 9");
        	break;
        case GL_KEY_DOT:                   // Key returned by keyboard : '.' (0x002E)
        	strcpy(tcKey, "KEY DOT");
        	break;
        case GL_KEY_PAPER:                 // Key returned by keyboard : Paper Feed (0xF853)
        	strcpy(tcKey, "KEY PAPER");
        	break;
        case GL_KEY_VALID:                 // Key returned by keyboard or touch screen : Green key (0xF850)
        	strcpy(tcKey, "KEY GREEN");
        	break;
        case GL_KEY_CANCEL:                // Key returned by keyboard or touch screen : Red key (0xF851)
        	strcpy(tcKey, "KEY RED");
        	break;
        case GL_KEY_CORRECTION:            // Key returned by keyboard : Yellow key (0xF852)
        	strcpy(tcKey, "KEY YELLOW");
        	break;
        case GL_KEY_F1:                    // Key returned by keyboard : F1 (0xF855)
        	strcpy(tcKey, "KEY F1");
        	break;
        case GL_KEY_F2:	                   // Key returned by keyboard : F2 (0xF856)
        	strcpy(tcKey, "KEY F2");
        	break;
        case GL_KEY_F3:                    // Key returned by keyboard : F3 (0xF857)
        	strcpy(tcKey, "KEY F3");
        	break;
        case GL_KEY_F4:                    // Key returned by keyboard : F4 (0xF858)
        	strcpy(tcKey, "KEY F4");
        	break;
        case GL_KEY_UP:                    // Key returned by keyboard or touch screen : Up (0xF859)
        	strcpy(tcKey, "KEY UP");
        	break;
        case GL_KEY_DOWN:                  // Key returned by keyboard or touch screen : Down (0xF85A)
        	strcpy(tcKey, "KEY DOWN");
        	break;
        case GL_KEY_OK:                    // Key returned by keyboard : OK (0xF86B)
        	strcpy(tcKey, "KEY OK");
        	break;
        case GL_KEY_CLEAR:                 // Key returned by keyboard : C (0xF86C)
        	strcpy(tcKey, "KEY C");
        	break;
        case GL_KEY_F:                     // Key returned by keyboard : F (0xF854)
        	strcpy(tcKey, "KEY F");
        	break;
        case 0x002A:                       // Numeric Keyboard locked to ZKA mode
        	strcpy(tcKey, "KEY ZKA");
        	break;
        default:                           // Key unknown
        	strcpy(tcKey, "UNKNOWN");
        	break;
        }

        sprintf(tcValue, "VALUE 0x%04X", iKey);

    	iRet = GoalDspLine(xScreen, 1, tcKey, &txKeyboard[1],  0, false);          // Show key name
    	CHECK(iRet>=0, lblKO);

    	if (iKey == GL_KEY_CANCEL)
    	{
    		iRet = GoalDspLine(xScreen, 2, tcValue, &txKeyboard[2], 3*1000, true); // Show cancel value and exit
    		CHECK(iRet>=0, lblKO);
    		break;
    	}
    	else
    	{
       		iRet = GoalDspLine(xScreen, 2, tcValue, &txKeyboard[2], 0, true);      // Show key value
        	CHECK(iRet>=0, lblKO);
		}
    }

    goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}


//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  INPUT.C                            (Copyright INGENICO 2012)
//============================================================================
//  Created :       16-July-2012     Kassovic
//  Last modified : 16-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                       *** Input management ***
//  This file DOES NOT use the following API(s) for input:
//    # Manager level (G_Extended_entry(), GetAmount(), ...)
//  This file uses the Graphic Object Advanced Library (GOAL) for input:
//    # Predefined mode (used inside this file)
//      GL_Dialog_VirtualKeyboard, GL_Dialog_Amount, etc...
//                                                                            
//  List of routines in file :  
//      ExtendedEntry : Alphanumeric entry.
//      AmountEntry : Amount entry.
//      DemoEntry :
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

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define APN_LEN    30 

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Main menu
// =========
static const char *tzMenuEntry[] =
{
	"Extended Entry", // Menu entry
	"Get Amount",
	NULL
};

// Sub Menu for amount type
// ========================
static const char *tzMenuAmt[] =
{
	"1.000,00",  // How to display the amount
	"1,000.00",
	"1 000,00",
	"1.000",
	"1,000",
	"1 000",
	"1.000,000",
	"1,000.000",
	"1 000,000",
	NULL
};

//****************************************************************************
//                          void ExtendedEntry (void)                            
//  This function allows to enter alpha-numerical entry in a grid or "GSM style".      
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

static void ExtendedEntry (void)
{
	// Local variables 
    // ***************
	char tcMask[256];
	char tcApn[APN_LEN+1];
	char tcDisplay[50+1];
	int iHeader, iFooter;
	int i, iRet;

	// Enter alphanumerical value in a grid or "GSM style"
	// ***************************************************
	iHeader = IsHeader();                    // Save header state
	iFooter = IsFooter();                    // Save footer state

	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<APN_LEN; i++)
		strcat(tcMask, "/c");                // Accept any character
	strcpy(tcApn, "telium@ingenico.com");    // Apn by default

	DisplayLeds(_OFF_);                      // Disable Leds
	DisplayHeader(_OFF_);                    // Disable Header
	DisplayFooter(_OFF_);                    // Disable Footer
                                             // Enter a string from Virtual keyboard
	iRet = GL_Dialog_VirtualKeyboard(xGoal, NULL, "Enter Apn :", tcMask, tcApn, sizeof(tcApn), GL_TIME_MINUTE);

	DisplayLeds(_ON_);                       // Enable Leds
	DisplayHeader(iHeader);                  // Enable Header
	if(!GL_GraphicLib_IsTouchPresent(xGoal)) // Check if it is a touch screen
		DisplayFooter(iFooter);              // Enable Footer

	switch (iRet)
	{
	case GL_KEY_VALID:                       // Valid entry
		sprintf(tcDisplay, "Input Valid\n%s", tcApn);
		GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_INFORMATION, GL_BUTTON_VALID, 30*1000);
        break;
    case GL_KEY_CANCEL:                      // Timeout/cancel
    case GL_RESULT_INACTIVITY:
		GL_Dialog_Message(xGoal, NULL, "Input Cancel / TimeOut", GL_ICON_INFORMATION, GL_BUTTON_VALID, 5*1000);
		break;
    default:                                 // Input error
		GL_Dialog_Message(xGoal, NULL, "Input Failed", GL_ICON_INFORMATION, GL_BUTTON_VALID, 5*1000);
    	break;
	}
}

//****************************************************************************
//                       void AmountEntry(void)                            
//  This function is requesting an amount to be entered in a given format and
//   currency is given as a parameter.
//  This function no has parameters.
//  This function has no return value.                                      
//****************************************************************************

static void AmountEntry(void)
{
	// Local variables 
    // ***************
	char tcMask[256];
	char tcAmount[11+1];
	char tcDisplay[50+1];
	int iRet;

	// Enter amount in progress
	// ************************	
	while(1)
	{
	    // Select format
	    // =============
		iRet = GL_Dialog_Choice(xGoal, "Format", tzMenuAmt, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
		CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Exit on cancel/timeout

		switch (iRet)
		{
		case 0: strcpy(tcMask, "/d/d/d./d/d/d./d/d/d,/d/d"); break;  // xxx.xxx.xxx,xx
		case 1: strcpy(tcMask, "/d/d/d,/d/d/d,/d/d/d./d/d"); break;  // xxx,xxx,xxx.xx
		case 2: strcpy(tcMask, "/d/d/d /d/d/d /d/d/d,/d/d"); break;  // xxx xxx xxx,xx
		case 3: strcpy(tcMask, "/d/d./d/d/d./d/d/d./d/d/d"); break;  // xx.xxx.xxx.xxx
		case 4: strcpy(tcMask, "/d/d,/d/d/d,/d/d/d,/d/d/d"); break;  // xx,xxx,xxx.xxx
		case 5: strcpy(tcMask, "/d/d /d/d/d /d/d/d /d/d/d"); break;  // xx xxx xxx xxx
		case 6: strcpy(tcMask, "/d/d./d/d/d./d/d/d,/d/d/d"); break;  // xx.xxx.xxx,xxx
		case 7: strcpy(tcMask, "/d/d,/d/d/d,/d/d/d./d/d/d"); break;  // xx,xxx,xxx.xxx
		case 8: strcpy(tcMask, "/d/d /d/d/d /d/d/d,/d/d/d"); break;  // xx xxx xxx,xxx
		default: break;
		}

		// Enter Amount
		// ============
		memset(tcAmount, 0, sizeof(tcAmount));
		iRet = GL_Dialog_Amount(xGoal, NULL, "Enter Amount :", tcMask, tcAmount, sizeof(tcAmount), "EUR", GL_ALIGN_LEFT, GL_TIME_MINUTE);
		switch (iRet)
		{
		case GL_KEY_VALID:                               // Valid entry
			sprintf(tcDisplay, "Input Valid\n%s", tcAmount);
			GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_INFORMATION, GL_BUTTON_VALID, 30*1000);
			break;
	    case GL_KEY_CANCEL:                              // Timeout/cancel
	    case GL_RESULT_INACTIVITY:
			GL_Dialog_Message(xGoal, NULL, "Input Cancel / TimeOut", GL_ICON_INFORMATION, GL_BUTTON_VALID, 5*1000);
			break;
	    default:                                         // Input error
			GL_Dialog_Message(xGoal, NULL, "Input Failed", GL_ICON_INFORMATION, GL_BUTTON_VALID, 5*1000);
	    	break;
		}
	}

	goto lblEnd;
	
	// Errors treatment 
    // ****************
lblEnd:
	return;
}

//****************************************************************************
//                        void DemoEntry (void)
//  This function shows a demo regarding alphanumeric entry  and amount entry.
//  This function has no parameters.   
//  This function has no return value.                                      
//****************************************************************************

void DemoEntry(void) 
{
	// Local variables 
    // ***************
	int bContinue=1;

	// Entry in progress
	// *****************
	do
	{
		switch (GL_Dialog_Menu(xGoal, "Demo Entry", tzMenuEntry, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
		{
		case 0: ExtendedEntry(); break; // Alphanumeric entry
		case 1: AmountEntry();   break; // Amount entry
		default: bContinue=0;    break; // Abort key pressed
		}
	} while (bContinue==1);
}


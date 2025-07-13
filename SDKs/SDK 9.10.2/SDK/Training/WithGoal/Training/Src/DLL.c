//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  DLL.C                              (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                          *** DLL management ***
//      Show how to call a DLL.
//      The dynamic library BeepDll is generated during the training.
//                                                                            
//  List of routines in file :  
//      OneBeepDLL : To execute the function OneBeepDLL() from DLL.
//      ManyBeepDLL : To execute the function ManyBeepDLL() from DLL.
//      BeepDll : Beep DLL demo.
//                            
//  File history :
//  071312-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
// !!! Warning : Functions ONLY supported for Telium 1&2 and will be replaced
// or removed for Telium+ to clean the platform.
// Add _DEPRECATED_TRAP_SDK091000_ inside Properties\Build Configurations\Users Symbols
// if needed and not yet replaced.
// DllLink => This function returns a pointer to the 'GetProcAddress' function of the specified DLL name.
#include "SDK30.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define DLL_NAME     "BEEPDLL"  // The name of the "family name of the DLL descriptor"

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
// Properties of the Dll screen (Goal)
// ===================================
static const ST_DSP_LINE txDll[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} }
};

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
typedef void* (*DLL_GET_PROC_ADDRESS) (char*);
typedef void (*ONE_BEEP_DLL) (void);
typedef int (*MANY_BEEP_DLL) (int);

static DLL_GET_PROC_ADDRESS DllGetProcAddress=NULL;
static ONE_BEEP_DLL _OneBeepDLL=NULL;
static MANY_BEEP_DLL _ManyBeepDLL=NULL;

//****************************************************************************
//                          int OneBeepDLL (void)
//  This function runs the function OneBeepDLL() from DLL.
//  This function has no parameters.
//  This function has return value.
//    >=0 : function done.
//     <0 : function failed (-1:BeepDll missing, -2:Processing error).
//****************************************************************************

int OneBeepDLL(void)
{
	// Local variables
    // ***************
	int iRet;

	// Call the function OneBeepDLL() from DLL
	// ***************************************
	iRet = ObjectLoad (OBJECT_TYPE_DLL, DLL_NAME);                  // Map the DLL
    CHECK((iRet==0) || (iRet==OL_ALREADY_LOADED), lblNoBeepDll);
    DllGetProcAddress = (DLL_GET_PROC_ADDRESS) DllLink(DLL_NAME);   // Allow the MMU to access the DLL
    CHECK(DllGetProcAddress != NULL, lblKO);
    _OneBeepDLL  = (ONE_BEEP_DLL) DllGetProcAddress ("OneBeepDLL"); // Check the function address from DLL
    CHECK(_OneBeepDLL != NULL, lblKO);
    _OneBeepDLL();                                                  // If exist, call the function from DLL

    iRet=0;
    goto lblEnd;

	// Errors treatment
    // ****************
lblNoBeepDll:                                                       // BeepDll missing
	iRet=-1;
    goto lblEnd;
lblKO:                                                              // Call function from DLL failed
    iRet=-2;
lblEnd:
    return iRet;
}

//****************************************************************************
//                          int ManyBeepDLL (int n)
//  This function runs the function ManyBeepDLL() from DLL.
//  This function has parameters.
//    n (I-) : Number of beep.
//  This function has return value.
//    >=0 : function done.
//     <0 : function failed (-1:BeepDll missing, -2:Processing error).
//****************************************************************************

int ManyBeepDLL(int n)
{
	// Local variables
    // ***************
	int iRet;

	// Call the function OneBeepDLL() from DLL
	// ***************************************
	iRet = ObjectLoad (OBJECT_TYPE_DLL, DLL_NAME);                    // Map the DLL
    CHECK((iRet==0) || (iRet==OL_ALREADY_LOADED), lblNoBeepDll);
    DllGetProcAddress = (DLL_GET_PROC_ADDRESS) DllLink(DLL_NAME);     // Allow the MMU to access the DLL
    CHECK(DllGetProcAddress != NULL, lblKO);
    _ManyBeepDLL = (MANY_BEEP_DLL) DllGetProcAddress ("ManyBeepDLL"); // Check the function address from DLL
    CHECK(_ManyBeepDLL != NULL, lblKO);
    iRet = _ManyBeepDLL(n);                                           // If exist, call the function from DLL

    goto lblEnd;

	// Errors treatment
    // ****************
lblNoBeepDll:                                                         // BeepDll missing
	iRet=-1;
    goto lblEnd;
lblKO:                                                                // Call function from DLL failed
    iRet=-2;
lblEnd:
    return iRet;
}

//****************************************************************************
//                          void BeepDll (void)                            
//  This function runs the DLL called Beep.      
//  This function has no parameters.    
//  This function has no return value.
//****************************************************************************

void BeepDll(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
    int iRet;            

	// Call the functions from the DLL
	// *******************************
	xScreen = GoalCreateScreen(xGoal, txDll, NUMBER_OF_LINES(txDll), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);       // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Press Valid", &txDll[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "To hear 1 Beep", &txDll[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet==GL_KEY_VALID, lblEnd); // Exit on cancel key or timeout

	iRet = OneBeepDLL();               // Call function OneBeepDLL()
	CHECK(iRet>=0, lblKO);

	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "Press Valid", &txDll[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "To hear 3 Beeps", &txDll[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet==GL_KEY_VALID, lblEnd); // Exit on cancel key or timeout

	iRet = ManyBeepDLL(3);             // Call function ManyBeepDLL()
	CHECK(iRet==2*3, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                 // None-classified low level error
	if (iRet == -1)                    // Beep DLL missing
		GL_Dialog_Message(xGoal, NULL, "Beep DLL missing\nPlease load it", GL_ICON_WARNING, GL_BUTTON_VALID  , 3*1000);
	else                               // Oops! error
		GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);   // Destroy screen
}



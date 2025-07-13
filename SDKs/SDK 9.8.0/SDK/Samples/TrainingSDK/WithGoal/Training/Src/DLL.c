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
//      BeepDll_open : Open the DLL called Beep. 
//      BeepDll : Beep DLL demo.                                            
//                            
//  File history :
//  071312-BK : File created
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
typedef void (*ONE_BEEP) (void);
typedef int (*MANY_BEEP) (int);
typedef void (*INIT_VAR) (void);

static DLL_GET_PROC_ADDRESS DllGetProcAddress=NULL;
static ONE_BEEP _OneBeep=NULL;
static MANY_BEEP _ManyBeep=NULL;
static INIT_VAR _InitVar=NULL;

//****************************************************************************
//                          int BeepDll_Open (void)                            
//  This function opens the DLL called Beep.      
//   - ObjectLoad() : Map the DLL
//   - DllLink() : Link the MMU to the DLL
//   - DllGetProcAddress() : Get the function address
//  This function has no parameters.    
//  This function has return value.
//     >0 : DLL loaded
//    <=0 : DLL failed
//****************************************************************************

static int BeepDll_open(void)
{
	// Local variables 
    // ***************
	int iRet;

	// Map the DLL
	// ===========
	iRet = ObjectLoad (OBJECT_TYPE_DLL, DLL_NAME);
    CHECK((iRet==0) || (iRet==OL_ALREADY_LOADED), lblNoBeepDll); 

	// Allows the MMU to access the DLL
    // ================================
    DllGetProcAddress = (DLL_GET_PROC_ADDRESS) DllLink(DLL_NAME);
    CHECK(DllGetProcAddress != NULL, lblKO);

	// Get the functions address
    // =========================
	_OneBeep  = (ONE_BEEP) DllGetProcAddress ("OneBeep");
    _ManyBeep = (MANY_BEEP) DllGetProcAddress ("ManyBeep");
    _InitVar  = (INIT_VAR) DllGetProcAddress ("initvar");

	// Run the initialization routine if any
    // =====================================
	if (_InitVar != NULL)
		_InitVar();

	iRet=1;
    goto lblEnd;
	
	// Errors treatment 
    // ****************
lblNoBeepDll:              // Missing Beep DLL
	GL_Dialog_Message(xGoal, NULL, "Beep DLL missing\nPlease load it", GL_ICON_WARNING, GL_BUTTON_VALID  , 3*1000);
    iRet=0;
    goto lblEnd;
lblKO:                     // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID  , 5*1000);
    iRet=-1;
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

	// Open BeepDll
	// ============
	iRet = BeepDll_open();
	CHECK(iRet>0, lblStop);
	
	// Call the functions from the DLL
	// ===============================
	xScreen = GoalCreateScreen(xGoal, txDll, NUMBER_OF_LINES(txDll), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);      // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Press Valid", &txDll[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "To hear 1 Beep", &txDll[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet==GL_KEY_VALID, lblEnd); // Exit on cancel key or timeout

	_OneBeep();                       // Call function OneBeep()

	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "Press Valid", &txDll[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "To hear 3 Beeps", &txDll[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet==GL_KEY_VALID, lblEnd); // Exit on cancel key or timeout

	iRet = _ManyBeep(3);              // Call function ManyBeep()
	CHECK(iRet==2*3, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblStop:                              // Execution interrupted
    if (!iRet)                        // ret==0 means that the exception is already processed
    	goto lblEnd;
    GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);  // Destroy screen
}



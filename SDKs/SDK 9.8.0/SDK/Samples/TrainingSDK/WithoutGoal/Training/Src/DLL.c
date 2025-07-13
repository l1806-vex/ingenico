//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  DLL.C                              (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Delay management:
//      Show how to call a DLL.
//      The dynamic library BeepDll is generated during the training.
//                                                                            
//  List of routines in file :  
//      BeepDll_open : Open the DLL called Beep. 
//      BeepDll : Beep DLL demo.                                            
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

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define DLL_NAME     "BEEPDLL"    // The name of the "family name of the DLL descriptor"

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

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
//       ObjectLoad() : Map the DLL
//       DllLink() : Link the MMU to the DLL
//       DllGetProcAddress() : Get the function address
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
lblNoBeepDll:
    _clrscr();                                        // Clear screen
    DisplayMedium(0, 0, "Missing Beep DLL");          // Beep DLL missing
    ttestall(0,5*100);                                // Delay 5s 
    iRet=0;
    goto lblEnd;
lblKO:
	_clrscr();                                        // Clear screen
	DisplayMedium(0, 0, "Processing Error");          // Oops! error
    ttestall(0,5*100);                                // Delay 5s 
    iRet=0;
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
    int iRet;            

	// Change font size
	// ================
    _clrscr();                                         // Clear screen

	// Open BeepDll
	// ============
	iRet = BeepDll_open();  CHECK(iRet>0, lblStop);
	
	// Call the functions from the DLL
	// ===============================
	DisplayMedium(0, 0, "Press a key");
	DisplayMedium(1, 0, "to hear 1 beep");
	getchar();
	_OneBeep();                                        // Call function _OneBeep()

	DisplayMedium(0, 0, "Press a key");
	DisplayMedium(1, 0, "to hear 3 beeps");
	getchar();
	iRet = _ManyBeep(3); CHECK(iRet==2*3, lblKO);      // Call function _ManyBeep() 

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                         // Clear screen
	DisplayMedium(0, 0, "Processing Error");           // Oops! error
    ttestall(0,5*100);                                 // Delay 5s 
    goto lblEnd;
lblStop:                                               // Execution interrupted
    if (!iRet)                                         // ret==0 means that the exception is already processed
        { goto lblEnd; }                                   
	_clrscr();                                         // Clear screen
	DisplayMedium(1, 0, "Processing Error");           // Oops! error
    goto lblEnd;    
lblEnd:
    return;
}



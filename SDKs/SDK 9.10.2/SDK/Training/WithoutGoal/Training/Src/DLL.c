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
//  120508-BK : File created 
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
typedef void (*ONE_BEEP_DLL) (void);
typedef int (*MANY_BEEP_DLL) (int);

static DLL_GET_PROC_ADDRESS DllGetProcAddress=NULL;
static ONE_BEEP_DLL _OneBeepDLL=NULL;
static MANY_BEEP_DLL _ManyBeepDLL=NULL;

//****************************************************************************
//                          int OneBeepDLL (void)
//  This function runs the function OneBeepDLL() from DLL.
//   - ObjectLoad() : Map the DLL
//   - DllLink() : Link the MMU to the DLL
//   - DllGetProcAddress() : Get the function address
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
//   - ObjectLoad() : Map the DLL
//   - DllLink() : Link the MMU to the DLL
//   - DllGetProcAddress() : Get the function address
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
//  This function runs the DLL called BeepDll.
//  This function has no parameters.
//  This function has no return value.
//****************************************************************************

void BeepDll(void) 
{
	// Local variables 
    // ***************
    int iRet;            

	// Call the functions from DLL
	// ***************************
    _clrscr();                                      // Clear screen
	DisplayMedium(0, 0, "Press a key");
	DisplayMedium(1, 0, "to hear 1 beep");
	getchar();
	iRet = OneBeepDLL(); CHECK(iRet>=0, lblKO);     // Call function OneBeepDLL()

	DisplayMedium(0, 0, "Press a key");
	DisplayMedium(1, 0, "to hear 3 beeps");
	getchar();
	iRet = ManyBeepDLL(3); CHECK(iRet==2*3, lblKO); // Call function ManyBeepDLL()

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                      // Clear screen
	if (iRet == -1)
	    DisplayMedium(0, 0, "Missing Beep DLL");    // Beep DLL missing
	else
		DisplayMedium(0, 0, "Processing Error");    // Oops! error
    ttestall(0,5*100);                              // Delay 5s
lblEnd:
    return;
}

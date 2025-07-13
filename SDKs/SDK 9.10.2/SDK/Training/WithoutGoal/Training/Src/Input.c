//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  INPUT.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Navigation and data entry:
//          Enter an alphanumeric value in a grid or "GSM" style
//          Enter a formatted amount 
//                                                                            
//  List of routines in file :  
//      DefaultMenu : Setting default menu.
//      ExtendedEntry : Alphanumeric entry.
//      AmountEntry : Amount entry.                                            
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
extern FILE *pxKbd;      // Peripheral file Keyboard

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define APN_LEN    30 
#define NUMBER_OF_ITEMS(a) (sizeof(a)/sizeof((a)[0]))

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
static const TAB_ENTRY_FCT t_montant = 
{
	0x0400,               // Mask (default: numeric, red, green, yellow and mask '.')
	NO_TIME_OUT           // TimeOut
};

static const char *tzMenuEntry[] =
{
	"Extended Entry",     // Menu entry      
	"Get Amount"		
};

static const char *tzMenuAmt[] =
{
	"1.000,00",           // How to display the amount
	"1,000.00",
	"1 000,00",
	"1.000",
	"1,000",
	"1 000",
	"1.000,000",
	"1,000.000",
	"1 000,000"
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
	char tcApn[APN_LEN+1];
	int iRet;

	// Enter alphanumerical value in a grid or "GSM style"
	// ***************************************************
	strcpy(tcApn, "bill.gates@sagem.com");                  // apn by default
	iRet = ShowEntry("APN", "", tcApn, 0, APN_LEN, 0);      // Input in progress
	_clrscr();                                              // Clear screen
	switch (iRet)
	{
	case 2:                                                 // Valid with entry
        DisplaySmall(0, 0, "Input Ok");
        DisplaySmall(2, 0, tcApn);
        break;
    case 1:                                                 // Valid without entry
        DisplaySmall(0, 0, "Input Valid");
        DisplaySmall(2, 0, tcApn);
        break;
    case 0:                                                 // Timeout, Cancel
        DisplaySmall(0, 0, "Input Cancel/TimeOut");
		break;
    default:                                                // Input error
        DisplaySmall(0, 0, "Input Failed");
    	break;
	}
	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                          // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                             // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                          // Reset keyboard FIFO to clear key pressed
}

//****************************************************************************
//                       void AmountEntry(void)                            
//  This function is requesting an amount to be entered in a given format and
//  currency is given as a parameter.
//  !!! Bug on GetAmount, pressing "0" first will be bufferized.
//  This function no has parameters.
//  This function has no return value.                                      
//****************************************************************************

static void AmountEntry(void)
{
	// Local variables 
    // ***************
	char tcDisplay[16+1];
	TAB_ENTRY_FCT t_val;
	unsigned long lAmount;
	byte ucFormat;
	int iRet;

	// Enter amount in progress
	// ************************	
	while(1)
	{
		iRet = ShowMenu("FORMAT", 1, 0, NUMBER_OF_ITEMS(tzMenuAmt), tzMenuAmt);
		CHECK(iRet>=0, lblEnd);

		ucFormat = (byte) iRet;                                     // Format selected to enter amount
		t_val.mask     = t_montant.mask;
		t_val.time_out = t_montant.time_out;
	    fclose(pxKbd);                                              // Close "keyboard" channel before calling GetAmount
		lAmount=0;
	    iRet = GetAmount( ucFormat,                                 // How to display the amount
                          (byte *) "EUR",                           // Currency
                          0,                                        // How to display currency "EUR    1000"
                          &lAmount,                                 // Returned amount
                          (byte *) "AMOUNT",                        // Message to be displayed on the first line
                          (TAB_ENTRY_FCT *) &t_val );               // Table configuring the entry
	    pxKbd = fopen("KEYBOARD", "r*"); CHECK(pxKbd!=NULL, lblKO); // Re-Open "keyboard" channel
		_clrscr();                                                  // Clear screen
		switch (iRet)
		{
		case 0:
			DisplayMedium(0, 0, "Input TimeOut");
			break;
		case T_ANN:
			DisplayMedium(0, 0, "Input Cancel");
			break;
		case T_VAL :
			DisplayMedium(0, 0, "Input Valid");
			sprintf(tcDisplay, "%lu", lAmount);
			DisplayMedium(1, 0, tcDisplay);
			break;
		}
		DisplayMedium(3, 2, "Press a key");
		reset_buf(pxKbd, _receive_id);                              // Reset keyboard FIFO
		ttestall(KEYBOARD, 30*100);                                 // Wait for a key pressed or a timeout
		reset_buf(pxKbd, _receive_id);                              // Reset keyboard FIFO to clear key pressed
	}

	goto lblEnd;
	
	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                      // Clear screen
	DisplayMedium(0, 0, "Processing Error");                        // Oops! error
    ttestall(0, 5*100);                                             // Delay 5s
lblEnd: 
	return;
}

//****************************************************************************
//                        void DemoEntry (FILE *pxKbd)                            
//  This function shows a demo regarding navigation and entry routines.      
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
		switch (ShowMenu("DEMO ENTRY", 0, 0, NUMBER_OF_ITEMS(tzMenuEntry), tzMenuEntry))
		{
		case 0: ExtendedEntry(); break; // Alphanumeric entry
		case 1: AmountEntry();   break; // Amount entry
		default: bContinue=0;    break; // Abort key pressed
		}
	} while (bContinue==1);
}


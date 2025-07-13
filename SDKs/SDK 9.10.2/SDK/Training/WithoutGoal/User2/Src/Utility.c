//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  UTILITY.C                          (Copyright INGENICO 2009)   
//============================================================================
//  Created :       26-Janvier-2009     Kassovic                                 
//  Last modified : 26-Janvier-2009     Kassovic                                
//  Module : USER2                                                          
//                                                                          
//  Purpose :                                                               
//  Utilities regarding some useful functions  
//                                                                            
//  List of routines in file :  
//      DisplaySmall, DisplayMedium, DisplayLarge : Using graphic library.
//      Display25 : Display a buffer (25 columns) using graphic library.
//      Printer24 : Print a buffer (24 columns).
//      ShowMenu : Menu management.
//      parseStr : String parsing.
//      IsoError : Iso error analysis.
//                            
//  File history :
//  260109-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "User2.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
    /* */

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
    /* */

//****************************************************************************
//     void DisplaySmall (byte ucLine, byte ucColumn, char *pcText)
//     void DisplayMedium (byte ucLine, byte ucColumn, char *pcText)
//     void DisplayLarge (byte ucLine, byte ucColumn, char *pcText)
//  The following standard functions:
//  - fopen(), fclose() (enable, disable display)
//  - putc(), puts(), printf() (write character, string and formatted string)
//  MUST NOT be used anymore.
//  Use Graphic Library instead to keep compatibility between B&W and color
//  terminal on colorized mode.
//  What is colorized mode?
//  - Emulation mode: monochrome application runs on a color terminal
//  – header controlled by the manager
//  – Text & background colors setting through Manager menu
//    (Initialization/Hardware/Display/Color Setup)
//  – Expansion factor performed by manager
//  This function has parameters.
//     ucLine (I-) : Line number
//     ucColumn (I-) : Column number
//     pcText (I-) : String to display
//  This function has no return value.
//****************************************************************************

void DisplaySmall (byte ucLine, byte ucColumn, char *pcText)
{
	DrawExtendedString((ucColumn*5)+2, ucLine*8, pcText, _OFF_, _POLICE4x7_, _NORMALE_);
}

void DisplayMedium (byte ucLine, byte ucColumn, char *pcText)
{
	DrawExtendedString(ucColumn*8, (ucLine*16)+2, pcText, _OFF_, _POLICE8x12_, _NORMALE_);
}

void DisplayLarge (byte ucLine, byte ucColumn, char *pcText)
{
	DrawExtendedString((ucColumn*16)+4, ucLine*24, pcText, _OFF_, _XLARGE_, _NORMALE_);
}

//****************************************************************************
//             int Display25(byte ucLine, char *pcData, int iLen)
//  This function sends a data buffer to the display (format 25 columns).
//  The buffer is divided on lines of 25 bytes except the last line.
//  Each line is automatically displayed on screen. The '\n' automatically
//  switches to the next line.
//  The function can display up to 8 lines.
//  This function has parameters:
//     ucLine (I-) : Line number
//     pcData (I-) : Data to display.
//     iLen (I-) : Number of bytes to display.
//  This function has return value.
//     Number of bytes sent to the display.
//****************************************************************************

int Display25(byte ucLine, char *pcData , int iLen)
{
	// Local variables
    // ***************
	int iCount=0;
	char tcBuffer[25+1];
	int iLength;

	// Printing in progress
	// ********************
	if ((pcData==NULL) || (iLen==0))
		return 0;
	iLength = iLen;

	memset(tcBuffer, 0, sizeof(tcBuffer));
	while(ucLine <= 7)
	{
		if ((iCount<25) && (iLen>0))                 // Check if a line of 25 bytes or the last line
		{                                            // No, it's a line with '\n' detected
			if (*pcData != '\n')                     // Save character into buffer
			{
				tcBuffer[iCount++] = *pcData++;
				tcBuffer[iCount]=0;
				iLen--;
			}
			else                                     // '\n' detected
			{
				DisplaySmall(ucLine++, 0, tcBuffer); // Display the buffer
				iCount=0;
				tcBuffer[iCount]=0;
				pcData++;
				iLen--;
			}
		}
		else
		{                                            // Yes, it's a line of 25 bytes or the last line
			if (iCount!=0)                           // Display the buffer if not already done
			{
				DisplaySmall(ucLine++, 0, tcBuffer);
				if (*pcData == '\n')                 // Remove the extra '\n'
					pcData++;
				iCount=0;
				tcBuffer[iCount]=0;
			}
			if (iLen == 0)                           // End of displaying => exit
				break;
		}
	}

    return iLength-iLen;                             // Return number of bytes sent to the display
}

//****************************************************************************
//                 int Print24(char *pcData, int iLen)
//  This function sends a data buffer to the printer (format 24 columns).
//  The buffer is divided on 5 lines of 120 bytes except the last line.
//  The '\n' automatically switches to the next line.
//  This function has parameters:
//     pcData (I-) : Data to print.
//     iLen (I-) : Number of bytes to print.
//  This function has return value.
//     Number of bytes sent to the printer.
//****************************************************************************

int Print24(char *pcData , int iLen)
{
	// Local variables
    // ***************
	int iCount=0;
	char tcBuffer[120+1];
	int iRet, iLength=0;

	// Printing in progress
	// ********************
	CHECK((pcData!=NULL) && (iLen!=0), lblEnd);
	iLength = iLen;

	while(1)
	{
		if ((iCount<120) && (iLen>0))              // Check if a 5 lines of 120 bytes or the last line
		{                                          // No, it's less than 5 lines with '\n' detected
			if (*pcData != '\n')                   // Save character into buffer
			{
				if (*pcData != '\r')               // '\r' not escape character for Telium printer
					tcBuffer[iCount++] = *pcData++;
				else
					pcData++;
				tcBuffer[iCount]=0;
				iLen--;
			}
			else                                   // '\n' detected
			{
				tcBuffer[iCount++] = *pcData++;    // Save it
				tcBuffer[iCount]=0;
				iLen--;
				if (*pcData != '\n')               // no more '\n' => print the buffer
				{
					iRet = pprintf("%s", tcBuffer);
					CHECK(iRet>=0, lblKO);
					iCount=0;
				}
			}
		}
		else
		{                                          // Yes, it's a 5 lines of 120 bytes or the last line
			if (iCount!=0)                         // Print the buffer if not already done
			{
				iRet = pprintf("%s\n", tcBuffer);  // Add final '\n' to print it
				CHECK(iRet>=0, lblKO);
				iCount=0;
			}
			if (iLen == 0)                         // End of printing => exit
				break;
		}
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                             // None-classified low level error
    iLength=-1;
lblEnd:
    return iLength;                                // Return number of bytes sent to the printer
}

//****************************************************************************
//     void ShowMenu (cont char *pcTitle, int iMenuStyle, int iDefaultItem,
//                    int iMaxItems, const char *tpcItems[])
//  This function shows the navigation menu.
//  This function has parameters.
//     (I-) pcTitle : Menu title
//     (I-) iMenuStyle : 0-with shortcut 1-without shortcut 2-with predefined value
//     (I-) iDefaultItem : Pre-select item number
//     (I-) iMaxItems : Maximum items
//     (I-) tpcItems : Items table
//  This function has return value.
//    >=0 : Selected item
//    <0  : Cancel/timeout/backspace
//****************************************************************************

int ShowMenu (const char *pcTitle, int iMenuStyle, int iDefaultItem,
			  int iMaxItems, const char *tpcItems[])
{
	// Local variables
    // ***************
	StructList xMenu;                                       // List definition
	int iMaxX, iMaxY;
	ENTRY_BUFFER xEntry;                                    // Result entry
	int i, iInput;
    int iRet;

	// Menu management
	// ***************
	GetScreenSize(&iMaxY, &iMaxX);                          // Get screen size
	if ((iDefaultItem < 0) || (iDefaultItem >= iMaxItems))  // Initialise pre-select item
		iDefaultItem=0;
    if ((iMenuStyle < 0) || (iMenuStyle > 2))               // Initialise menu style
    	iMenuStyle=0;

	memset(&xMenu, 0, sizeof(xMenu));
	xMenu.MyWindow.left         = 0;                        // Windows
	xMenu.MyWindow.top          = 0;                        //   position
	xMenu.MyWindow.rigth        = iMaxX-1;                  //     in
	xMenu.MyWindow.bottom       = iMaxY-1;                  //       pixels
	if (iMaxY == 128)
		xMenu.MyWindow.nblines  = 10;                       // Large screen
	else
		xMenu.MyWindow.nblines  = 5;                        // Normal screen
	xMenu.MyWindow.fontsize		= _MEDIUM_;
	xMenu.MyWindow.type			= _PROPORTIONNEL_;          // Font type
	xMenu.MyWindow.font			= 0;                        // Should be zero
	xMenu.MyWindow.correct		= _ON_;                     // Process correction key
	xMenu.MyWindow.offset		= 0;                        // Table index for selection
    if (iMenuStyle == 0)
    	xMenu.MyWindow.shortcommand	= _ON_;                 // Shortcut key
    else
    	xMenu.MyWindow.shortcommand	= _OFF_;
	if (iMenuStyle == 2)
		xMenu.MyWindow.selected = _ON_;                     // Display a predefined item
	else
		xMenu.MyWindow.selected = _OFF_;
	xMenu.MyWindow.thickness    = 2;                        // Border thickness of the window entry
	xMenu.MyWindow.border		= _ON_;                     // Display window entry border
	xMenu.MyWindow.popup		= _NOPOPUP_;                // Save an restore screen
	xMenu.MyWindow.first		= iDefaultItem;             // Pre select item if selected is _OFF_
	xMenu.MyWindow.current		= iDefaultItem;             // Pre select item if selected is _ON_
	xMenu.MyWindow.time_out		= 60;                       // Time-out in seconde
	xMenu.MyWindow.title		= (byte*)pcTitle;           // Window title, no title is NULL

	for (i=0; i<iMaxItems; i++ )                            // Initialise the item list
		xMenu.tab[i] = (byte*)tpcItems[i];

	G_List_Entry((void*)&xMenu);                            // Start navigating menu
	ttestall(ENTRY, 0);                                     // Wait for confirmation key
	iInput = Get_Entry((void*)&xEntry);                     // Get the result of the selection

	switch(iInput)
	{
	case CR_ENTRY_OK:      iRet = xEntry.d_entry[0]; break; // Retrieve the item selected
	default:               iRet=-1;                  break; // Timeout/Cancel/BackSpace
	}

	return iRet;
}

//****************************************************************************
//  const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim)
//  This function parses a string to extract part of it when reaching a token.
//  This function has parameters.
//    ucToken (I-) : Token to reach.
//    pcDst (-O) : Result buffer.
//    pcSrc (I-) : String to parse.
//    iDim (I-) : Result buffer size.
//  This function has return value.
//    NULL : Parsing failed
//    !NULL : Pointer to the end of string extracted.
//****************************************************************************

const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim)
{
    while(*pcSrc)
    {
    	if (iDim == 0)        // Buffer pcDst overflow
    		return NULL;      // Parsing failed

        if(*pcSrc == ucToken) // Token found
        {
            pcSrc++;          // Skip token
            break;
        }

        *pcDst++ = *pcSrc++;
        iDim--;
    }

    *pcDst=0;
    return pcSrc;
}

//****************************************************************************
//                 void IsoError (int iSta, char *pcTrk)                            
//  This function analyses the Iso error.      
//  This function has parameters:
//     iSta (I-) : Iso error
//     pcTrk (I-) : Track buffer error    
//  This function has no return value.                                      
//****************************************************************************

void IsoError(int iSta, char *pcTrk)
{
	switch (iSta)
	{
		case DEF_SEP: strcpy(pcTrk, "Separator fault");  break;
		case DEF_PAR: strcpy(pcTrk, "Parity fault");     break;
		case DEF_LRC: strcpy(pcTrk, "LRC fault");        break;
		case DEF_LUH: strcpy(pcTrk, "Luhn fault");       break;
		case DEF_NUM: strcpy(pcTrk, "Numerical fault");  break;
		case NO_DATA: strcpy(pcTrk, "No readable data"); break;
		default:      strcpy(pcTrk, "Unknown error");    break;
	}
}


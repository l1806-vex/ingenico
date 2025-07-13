//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  UTILITY.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-June-2012     Kassovic
//  Last modified : 13-June-2012     Kassovic
//  Module : CASHREG
//                                                                          
//  Purpose :                                                               
//  Utilities regarding some useful functions  
//                                                                            
//  List of routines in file :  
//      DisplaySmall, DisplayMedium, DisplayLarge : Using graphic library.
//      Display25 : Display a buffer (25 columns) using graphic library.
//      Printer24 : Print a buffer (24 columns).
//                            
//  File history :
//  130612-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "CashReg.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxKbd;      // Peripheral file Keyboard

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
	DrawExtendedString(ucColumn*5, ucLine*8, pcText, _OFF_, _POLICE4x7_, _NORMALE_);
	DrawExtendedString(25*5, ucLine*8, " ", _OFF_, _POLICE4x7_, _NORMALE_); // To remove garbage on 26 character
}

void DisplayMedium (byte ucLine, byte ucColumn, char *pcText)
{
	DrawExtendedString(ucColumn*8, ucLine*17, pcText, _OFF_, _POLICE8x12_, _NORMALE_);
}

void DisplayLarge (byte ucLine, byte ucColumn, char *pcText)
{
	DrawExtendedString(ucColumn*8, ucLine*16, pcText, _OFF_, _XLARGE_, _PROPORTIONNEL_);
}

void DisplayLargeCenter (byte ucLine, char *pcText)
{
	byte ucColumn;
	byte ucLen;

	ucLen = strlen(pcText);
	if (ucLen <= 15)
		ucColumn = (15-ucLen);
	else
		ucColumn = 0;

	DrawExtendedString((ucColumn*4+3), ucLine*16, pcText, _OFF_, _XLARGE_, _PROPORTIONNEL_);
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


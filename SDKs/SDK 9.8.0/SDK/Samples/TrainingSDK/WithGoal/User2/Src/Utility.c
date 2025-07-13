//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  UTILITY.C                         (Copyright INGENICO 2012)
//============================================================================
//  Created :       17-July-2012     Kassovic
//  Last modified : 17-July-2012     Kassovic
//  Module : USER2                                                          
//                                                                          
//  Purpose :                                                               
//  Utilities regarding some useful functions  
//                                                                            
//  List of routines in file :
//      parseStr : String parsing.
//      IsoError : Iso error analysis.
//                            
//  File history :
//  071712-BK : File created
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


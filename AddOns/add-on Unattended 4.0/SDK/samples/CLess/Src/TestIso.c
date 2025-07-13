/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.H"
#include "TlvTree.h"

#include "oem_cless.h"    // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		// Telium Pass include DLL
#include "ConfigurationTest.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"

//// Defines ////////////////////////////////////////////////////


//// Local variable definition //////////////////////////////////


//// Local function declarations ////////////////////////////////

static int __TestIso_DetectCard (int bAsync, int nTimeout);
static void __TestIso_DeselectCard (void);



//// Local functions ///////////////////////////////////////////

static int __TestIso_DetectCard (int bAsync, int nTimeout)
{
	int bEnd;
	int nKey;
	unsigned int nNumOfCards;
	int nResult;
	unsigned int nEvent;
	int bStop;
      char cTemp[100];
      
	nNumOfCards = 1;
	bStop = FALSE;

     // Open the driver

      // Asynchronous mode
      if (bAsync)
      {
         // Start the asynchronous card detection
         nResult = ClessEmv_DetectCardsStart  ( 1,  CL_TYPE_AB ) ;

         if (nResult == CL_OK)
         {
            // The card is correctly detected
            bEnd = FALSE;

            do
            {
               // Wait for an event : keyboard, cless or timeout
               nEvent = ttestall(KEYBOARD | CLESS, nTimeout * 100);
               if (nEvent == KEYBOARD)
               {
                  // Keyboard event
                  nKey = getchar(); // get the pressed key

                  if (nKey == T_ANN) // The detection is cancelled only if the red key is pressed
                  {
                     iLIBUCM_Print_Message( UCMC_PRINT,"TEST CANCELLED !!!\n");
                     bEnd = TRUE;
                  }
               }
               else // Cless or timeout
               {
                  if (nEvent == 0)
                  {
                     // Timeout event
                     iLIBUCM_Print_Message( UCMC_PRINT,"CLESS_DetectCardsStart timeout\n");
                  }
                  bEnd = TRUE;
               }
            } while(!bEnd);

            // If the cless event is received
            if (nEvent == CLESS)
               nResult = ClessEmv_DetectCards( CL_TYPE_AB, &nNumOfCards, 1);
            else bStop = TRUE;
         }
         else
         {
            sprintf(cTemp,  "CLESS_DetectCardsStart=%i\n", nResult );
            iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
           
            return FALSE;
         }

      }
      else // Synchronous mode
      {
         // Deselect the card (synchronous mode)
         nResult = ClessEmv_DetectCards(  CL_TYPE_AB, &nNumOfCards, nTimeout);
      }

   	if (!bStop)
   	{
   		switch(nResult)
   		{
   		case CL_OK: // Card correctly detected
               sprintf(cTemp,  "%i cards detected.\n", nNumOfCards);
               iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
		 			
   			return TRUE;
   			break;

   		case CL_KO: // An error occurs during the card detection
   			iLIBUCM_Print_Message( UCMC_PRINT,"CLESS_DetectCards=CL_KO\n");
   			break;

   		case CL_NOCARD: // No card has been detected
   			iLIBUCM_Print_Message( UCMC_PRINT,"CLESS_DetectCards=No card detected.\n");
   			break;

   		case CL_TOOMANYCARDS: // Too many cards on the reader
   			iLIBUCM_Print_Message( UCMC_PRINT,"CLESS_DetectCards=Too many cards.\n");
   			break;

   		case CL_INVALIDCARD: // The presented card is not valid
   			iLIBUCM_Print_Message( UCMC_PRINT,"CLESS_DetectCards=Invalid card.\n");
   			break;

   		default: // Default case
               sprintf(cTemp,  "CLESS_DetectCards=%i\n", nResult);
               iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
   			break;
   		}
   	}
   	else
   	{
   		nResult = ClessEmv_DetectCardsStop();
   		if (nResult == CL_OK)
   		{
               sprintf(cTemp,  "CLESS_DetectCardsStop=%i\n", nResult);
               iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
   		}
   	}

	return FALSE;
}


static void __TestIso_DeselectCard (void)
{
	int nResult;
   char cTemp[100];

   nResult = ClessEmv_DeselectCard  ( 0, TRUE, TRUE ) ;

   // Check the deselection result
   if (nResult == CL_OK)
      iLIBUCM_Print_Message( UCMC_PRINT,"Card removal detected !\n");
   else 
   {
      sprintf(cTemp,  "CLESS_DeselectCard=%i\n", nResult);
      iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
   }
	
}




//// Main functions ////////////////////////////////////////////

void TestIso_ISO14443Test (int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	//FILE* hPrinter;

	int bIsOpened;
	int bEnd;
	int nIndex;
	unsigned char nKeyboardState;
	int nKey;
	int nResult;
	static const unsigned char SelectPPSE[] =
		{ 0x00, 0xa4, 0x04, 0x00, 0x0e, 0x32, 0x50, 0x41, 0x59, 0x2e, 0x53, 0x59, 0x53, 0x2e, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};
	unsigned char CardResponse[256];
	unsigned int nResponseLength;
   char cTemp[100];
   
	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	bIsOpened = ClessEmv_OpenDriver ();

	//hPrinter= fopen("PRINTER", "w");

	bEnd = FALSE;
	nIndex = FALSE;
	do
	{
		switch(nIndex)
		{
		///////////////////////////////////////////////////////////////////////
		// ISO Card detection
		case 0:
			// Detect card
               sprintf(cTemp,  "\x1b" "@\n\x1b" "ECLESS Test %i\n\x1b" "@", nTest + 1);
               iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
			
			if (nTest == 0)
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nNe presentez\npas de carte", CUC30_ALIGN_CENTER);
				//printf("\x1b" "  PAS DE CARTE");
				nResult = __TestIso_DetectCard (FALSE, 3);
				nIndex = 99;
			}
			else if (nTest == 1)
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nNe presentez\npas de carte", CUC30_ALIGN_CENTER);
				//printf("\x1b" "  PAS DE CARTE");
				nResult = __TestIso_DetectCard (TRUE, 3);
				nIndex = 99;
			}
			else if ((nTest == 2) || (nTest == 3))
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nPresentez\ncarte", CUC30_ALIGN_CENTER);
				//printf("\x1b" "   PRESENTEZ\n     CARTE");
				nResult = __TestIso_DetectCard (FALSE, 30);
				if (nResult)
					nIndex = 1;
				else nIndex = 99;
			}
			else
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nPresentez\ncarte", CUC30_ALIGN_CENTER);
				//printf("\x1b" "   PRESENTEZ\n     CARTE");
				nResult = __TestIso_DetectCard (TRUE, 30);
				if (nResult)
					nIndex = 1;
				else nIndex = 99;
			}
			break;

		///////////////////////////////////////////////////////////////////////
		// ISO Card activation
		case 1:
			// Activate card
			TPass_FirstLine();
			TPass_Display ("\n\nActivation\ncarte");
			//printf("\x1b" "   ACTIVATION\n     CARTE");
			
			// Active the ISO card
			nResult = ClessEmv_ActiveCard( 0, CL_ISO14443_4);

			if (nResult == CL_OK)
			{
				iLIBUCM_Print_Message( UCMC_PRINT,"CLESS_ActiveCard OK\n");
				nIndex = 2;
			}
			else
			{
                     sprintf(cTemp,  "CLESS_ActiveCard=%i\n", nResult);
                     iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
				nIndex = 3;
			}
			break;

		///////////////////////////////////////////////////////////////////////
		// ISO Card APDU send
		case 2:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nCommande\ncarte", CUC30_ALIGN_CENTER);
			//printf("\x1b" "    COMMANDE\n     CARTE");

			// Initialise the max response length
			nResponseLength = 256;

			// Send the APDU to the card
			nResult = ClessEmv_Apdu ( 0, SelectPPSE, sizeof(SelectPPSE), CardResponse, &nResponseLength);

			if (nResult == CL_OK)
				iLIBUCM_Print_Message( UCMC_PRINT,"CLESSEmv_Apdu OK\n");
			else 
			{
                  sprintf(cTemp,  "CLESSEmv_Apdu=%i\n", nResult);
                  iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
                }
			nIndex = 3;
			break;

		///////////////////////////////////////////////////////////////////////
		// ISO Card deselection
		case 3:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nRetirez\ncarte", CUC30_ALIGN_CENTER);
			//printf("\x1b" "    RETIREZ\n     CARTE");
			
			// Process the card deselection
			__TestIso_DeselectCard ();
			nIndex = 99;
			break;

		///////////////////////////////////////////////////////////////////////
		// Error or End case
		case 99:
			bEnd = TRUE;
			break;
		}

		// If the test is cancelled ...
		if (!bEnd)
		{
			status(hKeyboard, &nKeyboardState);
			if (nKeyboardState != 0)
			{
				nKey = getchar();
				if (nKey == T_ANN)
				{
					iLIBUCM_Print_Message( UCMC_PRINT,"TEST CANCELLED !!!\n");
					bEnd = TRUE;
				}
			}
		}
	} while(!bEnd);

	iLIBUCM_Print_Message( UCMC_PRINT,"\n\n\n\n\x0c");

	// Close the contactless driver
	ClessEmv_CloseDriver ();

	// Close other peripheral drivers
	//fclose(hPrinter);
	fclose(hKeyboard);
	fclose(hDisplay);
}

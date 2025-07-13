/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.H"
#include "TlvTree.h"

#include "oem_cless.h"    // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		// Telium Pass include DLL
#include "ConfigurationTest.h"


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

	nNumOfCards = 1;
	bStop = FALSE;

	// Asynchronous mode
	if (bAsync)
	{
		// Start the asynchronous card detection
		nResult = CLESS_DetectCardsStart(NULL, CL_TYPE_AB);

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
						pprintf("TEST CANCELLED !!!\n");
						ttestall(PRINTER, 0);
						bEnd = TRUE;
					}
				}
				else // Cless or timeout
				{
					if (nEvent == 0)
					{
						// Timeout event
						pprintf("CLESS_DetectCardsStart timeout\n");
						ttestall(PRINTER, 0);
					}
					bEnd = TRUE;
				}
			} while(!bEnd);

			// If the cless event is received
			if (nEvent == CLESS)
				nResult = CLESS_DetectCards(NULL, CL_TYPE_AB, &nNumOfCards, 1);
			else bStop = TRUE;
		}
		else
		{
			pprintf("CLESS_DetectCardsStart=%i\n", nResult);
			ttestall(PRINTER, 0);
			return FALSE;
		}
	}
	else // Synchronous mode
	{
		// Deselect the card (synchronous mode)
		nResult = CLESS_DetectCards(NULL, CL_TYPE_AB, &nNumOfCards, nTimeout);
	}

	if (!bStop)
	{
		switch(nResult)
		{
		case CL_OK: // Card correctly detected
			pprintf("%i cards detected.\n", nNumOfCards);
			ttestall(PRINTER, 0);
			return TRUE;
			break;

		case CL_KO: // An error occurs during the card detection
			pprintf("CLESS_DetectCards=CL_KO\n");
			ttestall(PRINTER, 0);
			break;

		case CL_NOCARD: // No card has been detected
			pprintf("CLESS_DetectCards=No card detected.\n");
			ttestall(PRINTER, 0);
			break;

		case CL_TOOMANYCARDS: // Too many cards on the reader
			pprintf("CLESS_DetectCards=Too many cards.\n");
			ttestall(PRINTER, 0);
			break;

		case CL_INVALIDCARD: // The presented card is not valid
			pprintf("CLESS_DetectCards=Invalid card.\n");
			ttestall(PRINTER, 0);
			break;

		default: // Default case
			pprintf("CLESS_DetectCards=%i\n", nResult);
			ttestall(PRINTER, 0);
			break;
		}
	}
	else
	{
		nResult = CLESS_DetectCardsStop(NULL);
		if (nResult == CL_OK)
		{
			pprintf("CLESS_DetectCardsStop=%i\n", nResult);
			ttestall(PRINTER, 0);
		}
	}

	return FALSE;
}



static void __TestIso_DeselectCard (void)
{
	int nResult;

	// Deselect the card
	nResult = CLESS_DeselectCard(NULL, 0, TRUE, TRUE);

	// Check the deselection result
	if (nResult == CL_OK)
		pprintf("Card removal detected !\n");
	else pprintf("CLESS_DeselectCard=%i\n", nResult);
}




//// Main functions ////////////////////////////////////////////

void TestIso_ISO14443Test (int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	FILE* hPrinter;

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

	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	bIsOpened = CLESS_OpenDriver ();

	hPrinter= fopen("PRINTER", "w");

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
			pprintf("\x1b" "@\n\x1b" "ECLESS Test %i\n\x1b" "@", nTest + 1);
			ttestall(PRINTER, 0);
			if (nTest == 0)
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nNe presentez\npas de carte", CUC30_ALIGN_CENTER);
				printf("\x1b" "  PAS DE CARTE");
				nResult = __TestIso_DetectCard (FALSE, 3);
				nIndex = 99;
			}
			else if (nTest == 1)
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nNe presentez\npas de carte", CUC30_ALIGN_CENTER);
				printf("\x1b" "  PAS DE CARTE");
				nResult = __TestIso_DetectCard (TRUE, 3);
				nIndex = 99;
			}
			else if ((nTest == 2) || (nTest == 3))
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nPresentez\ncarte", CUC30_ALIGN_CENTER);
				printf("\x1b" "   PRESENTEZ\n     CARTE");
				nResult = __TestIso_DetectCard (FALSE, 30);
				if (nResult)
					nIndex = 1;
				else nIndex = 99;
			}
			else
			{
				TPass_FirstLine();
				CUC30_DisplayText("\n\nPresentez\ncarte", CUC30_ALIGN_CENTER);
				printf("\x1b" "   PRESENTEZ\n     CARTE");
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
			printf("\x1b" "   ACTIVATION\n     CARTE");
			
			// Active the ISO card
			nResult = CLESS_ActiveCard(NULL, 0, CL_ISO14443_4);

			if (nResult == CL_OK)
			{
				pprintf("CLESS_ActiveCard OK\n");
				nIndex = 2;
			}
			else
			{
				pprintf("CLESS_ActiveCard=%i\n", nResult);
				nIndex = 3;
			}
			ttestall(PRINTER, 0);
			break;

		///////////////////////////////////////////////////////////////////////
		// ISO Card APDU send
		case 2:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nCommande\ncarte", CUC30_ALIGN_CENTER);
			printf("\x1b" "    COMMANDE\n     CARTE");

			// Initialise the max response length
			nResponseLength = 256;

			// Send the APDU to the card
			nResult = CLESS_Apdu (NULL, 0, SelectPPSE, sizeof(SelectPPSE), CardResponse, &nResponseLength);

			if (nResult == CL_OK)
				pprintf("CLESS_Apdu OK\n");
			else pprintf("CLESS_Apdu=%i\n", nResult);

			ttestall(PRINTER, 0);
			nIndex = 3;
			break;

		///////////////////////////////////////////////////////////////////////
		// ISO Card deselection
		case 3:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nRetirez\ncarte", CUC30_ALIGN_CENTER);
			printf("\x1b" "    RETIREZ\n     CARTE");
			
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
					pprintf("TEST CANCELLED !!!\n");
					ttestall(PRINTER, 0);
					bEnd = TRUE;
				}
			}
		}
	} while(!bEnd);

	pprintf("\n\n\n\n\x0c");
	ttestall(PRINTER, 0);

	// Close the contactless driver
	CLESS_CloseDriver();

	// Close other peripheral drivers
	fclose(hPrinter);
	fclose(hKeyboard);
	fclose(hDisplay);
}

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.H"
#include "TlvTree.h"

#include "ConfigurationTest.h"
#include "oem_cless.h"    // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		  // Telium Pass include DLL
#include "oem_clmf1.h"    // Mifare
#include "TestMifare.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"


//// Defines ////////////////////////////////////////////////////

// Mifare constant
#define MONEY_SECTORS_NUMBER	1
#define ACCESS_SECTORS_NUMBER	6
#define READ_SECTORS_NUMBER		9
#define WRITE_SECTORS_NUMBER	9

//MF1
#define READ			0x30
#define INCREMENT		0xC1
#define DECREMENT		0xC0
#define WRITE			0xA0


//// Local variables ////////////////////////////////////////////

typedef byte t_MF_Key[6];		// define the lenght of a key for CRYPTO1

static const t_MF_Key MoneyKey_A[MONEY_SECTORS_NUMBER] = {// define the key (A) for money payment (sector=0)
  {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5}};

static const t_MF_Key MoneyKey_B[MONEY_SECTORS_NUMBER] = {// define the key (B) for money payment (sector=0)
  {0xB0,0xB1,0xB2,0xB3,0xB4,0xB5}};


//// Local function declarations ////////////////////////////////

static int __TestMifare_DetectCard (int nTimeout);


//// Local functions ////////////////////////////////////////////

static int __TestMifare_DetectCard (int nTimeout)
{
	unsigned int nNumOfCards;
	int nResult;
      char cTemp[100];
      
	nNumOfCards = 100;

	// Detect the Mifare cards
	nResult = ClessMifare_DetectCards ( &nNumOfCards, nTimeout);

	// Analyse the detection result
	switch(nResult)
	{
	case MF_OK: // The Mifare card is correctly detected
		sprintf(cTemp, "%i cards detected.\n", nNumOfCards);
          iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
		return TRUE;
		break;

	case MF_KO: // An error occurs during the card detection
		sprintf(cTemp, "ClessMifare_DetectCards =MF_KO\n");
           iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
		break;

	default: // Default case, unknown returned code
		sprintf(cTemp, "ClessMifare_DetectCards =%i\n", nResult);
		 iLIBUCM_Print_Message( UCMC_PRINT, cTemp);

		break;
	}

	return FALSE;
}


//===============================================================================


void TestMifare_Test (int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	//FILE* hPrinter;

	int bEnd;
	int nIndex;
	unsigned char nKeyboardState;
	int nKey;
	int nResult;
	unsigned char BlockBuffer[16];
	unsigned char Amount[4];
    unsigned char cTemp[100];
    
	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

      if (ClessMifare_OpenDriver() != MF_OK)
      {
         return;
      }
   
	//hPrinter= fopen("PRINTER", "w");

	bEnd = FALSE;
	nIndex = FALSE;
	do
	{
		switch(nIndex)
		{
		///////////////////////////////////////////////////////////////////////
		// Mifare Card detection
		case 0:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nTAP\nCARD", CUC30_ALIGN_CENTER);
			//printf("\x1b" "   TAP\n     CARD");
			
			// Detect a Mifare card
			nResult = __TestMifare_DetectCard (3);

			// Result analysis
			if (nResult)
				nIndex = 1;
			else
				nIndex = 99;
			break;

		///////////////////////////////////////////////////////////////////////
		// Mifare Card activation
		case 1:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nCARD\nACTIVATION", CUC30_ALIGN_CENTER);
			//printf("\x1b" "   ACTIVATION\n     CARTE");

			// Mifare card activation
			nResult = ClessMifare_ActiveCard( 0);

			if (nResult == MF_OK)
			{
				iLIBUCM_Print_Message( UCMC_PRINT, "CLESS_ActiveCard OK\n");
				nIndex = 2;
			}
			else
			{
                     sprintf(cTemp,  "CLESS_ActiveCard=%i\n", nResult);
                     iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
				nIndex = 99;
			}

			break;

		///////////////////////////////////////////////////////////////////////
		// Mifare Card authentication
		case 2:
			TPass_FirstLine();
			CUC30_DisplayText("\n\ncard\nauthentication", CUC30_ALIGN_CENTER);
			//printf("\x1b" "     CARD\nAUTHENTIFICATION");

			// According the test
			if ((nTest == 2) || (nTest == 3))
				nResult = ClessMifare_Authentication( KEY_A, MoneyKey_A[0], 0);
			else nResult = ClessMifare_Authentication( KEY_B, MoneyKey_B[0], 0);

			if (nResult == MF_OK)
			{
				 iLIBUCM_Print_Message( UCMC_PRINT, "ClessMifare_Authentication OK\n");
				nIndex = 3;
			}
			else
			{
                     sprintf(cTemp,  "ClessMifare_Authentication=%i\n", nResult);
                     iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
				nIndex = 99;
			}

			break;

		///////////////////////////////////////////////////////////////////////
		// Mifare Card operation
		case 3:
			TPass_FirstLine();
			CUC30_DisplayText("\n\nOperation\ncarte", CUC30_ALIGN_CENTER);
			//printf("\x1b" "   OPERATION\n     CARTE");

			// Do operation on the card (according the test).
			if ((nTest == 1) || (nTest == 2))
			{
				// Initialise the mifare transaction amount
				memset(Amount, 0, sizeof(Amount));
				if (nTest == 1)
				{
					Amount[0] = 200;
					nResult = ClessMifare_ValueOperation( INCREMENT, 0, 1, 1, &Amount);
				}
				else
				{
					Amount[0] = 3;
					nResult = ClessMifare_ValueOperation( DECREMENT, 0, 1, 1, &Amount);
				}

				// The operation has succeed
				if (nResult == MF_OK)
				{
					iLIBUCM_Print_Message( UCMC_PRINT,"ClessMifare_ValueOperation OK\n");
					nIndex = 99;
				}
				else // The operation failed
				{
                        sprintf(cTemp,  "ClessMifare_ValueOperation=%i\n", nResult);
                        iLIBUCM_Print_Message( UCMC_PRINT, cTemp);

					nIndex = 99;
				}

			}
			else if (nTest == 3) // Read a block on the card
			{
				// Set the output buffer
				memset(BlockBuffer, 0, sizeof(BlockBuffer));

				// Read the block on the card
				nResult = ClessMifare_ReadBlock( VALUE, 0, 1, BlockBuffer);

				if (nResult == MF_OK) // The block read succeed
				{
					iLIBUCM_Print_Message( UCMC_PRINT,"ClessMifare_ReadBlock OK\n");
		
					sprintf(cTemp, "BLOCK = %02X %02X %02X %02X\n", BlockBuffer[0], BlockBuffer[1], BlockBuffer[2], BlockBuffer[3]);
                           iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
                           
					nIndex = 99;
				}
				else // The block read failed
				{
					sprintf(cTemp, "ClessMifare_ReadBlock=%i\n", nResult);
					iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
					nIndex = 99;
				}
			}
			else if (nTest == 4) // Write a block on the Mifare card (reset the purse)
			{
				// Init the input buffer to 0 (to reset the block)
				memset(BlockBuffer, 0, sizeof(BlockBuffer));

				// Write the block on the Mifare card
				nResult = ClessMifare_WriteBlock( VALUE, 0, 1, BlockBuffer);

				if (nResult == MF_OK) // The block write succeed
				{
					iLIBUCM_Print_Message( UCMC_PRINT,"ClessMifare_WriteBlock OK\n");
					nIndex = 99;
				}
				else // The block write failed
				{
					sprintf(cTemp, "ClessMifare_WriteBlock=%i\n", nResult);
					iLIBUCM_Print_Message( UCMC_PRINT, cTemp);
					nIndex = 99;
				}
			}
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

	// Close the contactless driver
     ClessMifare_CloseDriver ();

	// Close other peripheral drivers
	//fclose(hPrinter);
	fclose(hKeyboard);
	fclose(hDisplay);
}

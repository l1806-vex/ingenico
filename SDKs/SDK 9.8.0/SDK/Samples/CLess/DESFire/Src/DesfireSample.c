/**
 *
 * \author      INGENICO
 * \version     1.0
 * \author      Ingenico has intellectual property rights relating to the technology embodied \n
 *           in this software. In particular, and without limitation, these intellectual property rights may\n
 *           include one or more patents.\n
 *           This software is distributed under licenses restricting its use, copying, distribution, and\n
 *           and decompilation. No part of this software may be reproduced in any form by any means\n
 *           without prior written authorization of Ingenico.
 *
 **/

/* ===================================================================== */
/*                      INCLUDES                        */
/* ===================================================================== */


#include "SDK30.H"
#include "DesfireSample.h"
#include "Desfire.h"

#include "Cless_LowLevel.h"     // low level interface of the contactless DLL.
#include "oem_cless.h"          // Telium Pass include driver


// Local variables

FILE* hSAM = NULL;
T_MIFARE_SAM_CONTEXT *pSamContext = NULL;

/***********************************************************
 *
 * name:       detectCard
 *
 * definition:  ISO A / B card detection
 *
 * param:      type of detection
 *             time out value
 *
 * return:     final result
 *
 ***********************************************************/
static int detectCard(int bAsync, int nTimeout)
{
   int bEnd;
   int nKey;
   unsigned int nNumOfCards;
   int nResult;
   unsigned int nEvent;
   int bStop;

   nNumOfCards = 1;
   bStop = FALSE;

   if (bAsync) // Asynchronous mode
   {
      // Start the asynchronous card detection
      nResult = ClessEmv_DetectCardsStart(3, CL_TYPE_AB);//number max is 3 here for ex.

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
                  pprintf("CLESS_DetectCardsStart() timeout\n");
                  ttestall(PRINTER, 0);
               }
               bEnd = TRUE;
            }
         } while (!bEnd);

         // If the cless event is received
         if (nEvent == CLESS)
            nResult = ClessEmv_DetectCards(CL_TYPE_AB, &nNumOfCards, 1);
         else
            bStop = TRUE;
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
      nResult = ClessEmv_DetectCards(CL_TYPE_AB, &nNumOfCards, nTimeout);
   }

   if (!bStop)
   {
      switch (nResult)
      {
      case CL_OK: // Card correctly detected
         pprintf("%i card(s) detected\n", nNumOfCards);
         ttestall(PRINTER, 0);
         return TRUE;
         break;

      case CL_KO: // An error occurs during the card detection
         pprintf("CLESS_DetectCards=CL_KO\n");
         ttestall(PRINTER, 0);
         break;

      case CL_NOCARD: // No card has been detected
         pprintf("CLESS_DetectCards =  No card detected / Timeout\n");// timeout
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
      nResult = ClessEmv_DetectCardsStop();
      if (nResult == CL_OK)
      {
         pprintf("CLESS_DetectCardsStop=%i\n", nResult);
         ttestall(PRINTER, 0);
      }
   }

   return FALSE;
}

static void Desfire_Print_Return_Code(int error)
{
   char string[64];
   switch (error)
   {
   case DESFIRE_OPERATION_OK:
      sprintf(string, "<--- DESFIRE_OPERATION_OK");
      break;
   case DESFIRE_NO_CHANGES:
      sprintf(string, "<--- DESFIRE_NO_CHANGES");

      break;
   case DESFIRE_OUT_OF_EEPROM_ERROR:
      sprintf(string, "<--- DESFIRE_OUT_OF_EEPROM_ERROR");

      break;
   case DESFIRE_ILLEGAL_COMMAND:
      sprintf(string, "<--- DESFIRE_ILLEGAL_COMMAND");

      break;
   case DESFIRE_INTEGRITY_ERROR:
      sprintf(string, "<--- DESFIRE_INTEGRITY_ERROR");

      break;
   case DESFIRE_NO_SUCH_KEY:
      sprintf(string, "<--- DESFIRE_NO_SUCH_KEY");
      break;
   case DESFIRE_LENGTH_ERROR:
      sprintf(string, "<--- DESFIRE_LENGTH_ERROR");
      break;
   case DESFIRE_PERMISSION_DENIED:
      sprintf(string, "<--- DESFIRE_PERMISSION_DENIED");
      break;
   case DESFIRE_PARAMETER_ERROR:
      sprintf(string, "<--- DESFIRE_PERMISSION_DENIED");
      break;
   case DESFIRE_APPLICATION_NOT_FOUND:
      sprintf(string, "<--- DESFIRE_APPLICATION_NOT_FOUND");
      break;
   case DESFIRE_APPL_INTEGRITY_ERROR:
      sprintf(string, "<--- DESFIRE_APPL_INTEGRITY_ERROR");
      break;
   case DESFIRE_AUTHENTICATION_ERROR:
      sprintf(string, "<--- DESFIRE_AUTHENTICATION_ERROR");
      break;
   case DESFIRE_ADDITIONAL_FRAME:
      sprintf(string, "<--- DESFIRE_ADDITIONAL_FRAME");
      break;
   case DESFIRE_BOUNDARY_ERROR:
      sprintf(string, "<--- DESFIRE_BOUNDARY_ERROR");
      break;
   case DESFIRE_PICC_INTEGRITY_ERROR:
      sprintf(string, "<--- DESFIRE_PICC_INTEGRITY_ERROR");
      break;
   case DESFIRE_COMMAND_ABORTED:
      sprintf(string, "<--- DESFIRE_COMMAND_ABORTED");
      break;
   case DESFIRE_PICC_DISABLED:
      sprintf(string, "<--- DESFIRE_PICC_DISABLED");
      break;
   case DESFIRE_COUNT_ERROR:
      sprintf(string, "<--- DESFIRE_COUNT_ERROR");
      break;
   case DESFIRE_DUPLICATE_ERROR:
      sprintf(string, "<--- DESFIRE_DUPLICATE_ERROR");
      break;
   case DESFIRE_EEPROM_ERROR:
      sprintf(string, "<--- DESFIRE_EEPROM_ERROR");
      break;
   case DESFIRE_FILE_NOT_FOUND:
      sprintf(string, "<--- DESFIRE_FILE_NOT_FOUND");
      break;
   case DESFIRE_FILE_INTEGRITY_ERROR:
      sprintf(string, "<--- DESFIRE_FILE_INTEGRITY_ERROR");
      break;
   case DESFIRE_DLL_NOT_LOADED:
      sprintf(string, "<--- DESFIRE_DLL_NOT_LOADED");
      break;
   default:
      sprintf(string, "<--- UNKNOWN_ERROR : 0x%02X", error); //Not Desfire error

      break;
   }
   pprintf(string);
   pprintf("\n");
   ttestall(PRINTER, 0);
}

/***********************************************************
 *
 * name:       Sample_Desfire_Thunder
 *
 * definition:  Sample of DESFire application using Thunder
 *              for key management and cryptographic operations.
 *
 * param:      none
 *
 * return:     final result
 *
 ***********************************************************/
int Sample_Desfire(int iTestNum)
{
   FILE* hDisplay;
   FILE* hKeyboard;
   FILE* hPrinter;

   int bIsOpened, ret;

   // unique IDentifier of the card detected
   unsigned char cardUid[12];

   hDisplay = fopen("DISPLAY", "w");
   hKeyboard = fopen("KEYBOARD", "r");
   hPrinter = fopen("PRINTER", "w");

   bIsOpened = ClessEmv_OpenDriver();
   if (bIsOpened == CL_KO)
   {
      pprintf("ClessEmv_OpenDriver() KO");
      goto EXIT;
      return 0;
   }
   // \x0f -> print as condensed mode
   pprintf("\x0f\n========= MIFARE DESfire sample =========\n\n");
   printf("\x1b" "    PRESENT\n   YOUR CARD");

   ////////////////////////////////////////////
   pprintf("Card detection...  ");
   ret = detectCard(FALSE, 30);
   if (!ret)
   {
      goto EXIT;
      return 0;
   }

   ///////////////////////////////////////////////////
   // Retrieve the UID of an ISO14443-4 card.
   // unique IDentifier of the card
   // buffer must be 12 bytes long. The UID can be on 4, 7 or 10 bytes.
   //
   ///////////////////////////////////////////////////
   memset(cardUid, 0, sizeof(cardUid));
   pprintf("ClessEmv_GetUid() =");
   ret = ClessEmv_GetUid(cardUid);
   switch (ret)
   {
   case CL_OK: // One or several cards are detected.
   {
      pprintf(" OK\n");
      break;
   }
   case CL_KO: // error
   {
      pprintf(" KO\n");
      break;
   }
   case CLESS_NOT_IMPLEMENTED: // The function is not implemented (the driver is too old)
   {
      pprintf(" CLESS_NOT_IMPLEMENTED\n");
      break;
   }
   }
   pprintf("UID = %02X %02X %02X %02X %02X %02X %02X\n", cardUid[0],
         cardUid[1], cardUid[2], cardUid[3], cardUid[4], cardUid[5], cardUid[6]);

   ////////////////////////////////////////////
   // Activate an ISO14443-4 contactless card
   ////////////////////////////////////////////
   ret = ClessEmv_ActiveCard(0, CL_ISO14443_4);
   switch (ret)
   {
   case CL_OK: // Card activated
      pprintf("ClessEmv_ActiveCard()=OK  -> card is activated\n");
      break;

   case CL_KO: // An error occurs during the card detection
      pprintf("ClessEmv_ActiveCard()=CL_KO\n");
      break;

   case CL_INVALIDCARD: // The presented card is not valid
      pprintf(
            "ClessEmv_ActiveCard()=Invalid card.\nit is not a MIFARE DESfire one\n\n");
      break;

   default: // Default case
      pprintf("ClessEmv_ActiveCard()=%i\n", ret);
      break;
   }
   ttestall(PRINTER, 0);

   if (ret != CL_OK)
   {
      goto EXIT;
      return 0;
   }

   switch (iTestNum)
   {
   case 0:
      Sample_Desfire_Thunder();
      break;
   case 1:
      Sample_Format_PICC();
      break;
   case 2:
      Sample_Authenticate_Host();
      break;
   case 3:
      Sample_ChangeKeyEntry();
      break;
   case 4:
      Sample_ResetKeyEntry();
      break;
   case 5:
   	  Sample_FreeContext();
   	  break;
   default:
      break;
   }

EXIT:
   pprintf("\n\n\n\n");
   ttestall(PRINTER, 0);
   // Close peripheral drivers
   fclose(hDisplay);
   fclose(hKeyboard);
   fclose(hPrinter);
   ClessEmv_CloseDriver();// Close the contactless driver

   return 0;
}

void Sample_Desfire_Thunder(void)
{
   /***********/
   /* DESFire */
   /***********/
   T_DESFIRE_CONTEXT *pDesfireContext;
   T_MIFARE_KEY *pKey;
   T_DESFIRE_AID arrayAID[MAX_APPLICATION_COUNT];
   struct S_DESFIRE_VERSION_INFO sInfo;
   int iReturn = 0;
   unsigned char array[32];
   int arrayLen = 0;
   int count = 0;
   int i = 0;

   /* Context initialization */
   pDesfireContext = desfire_NewContext(APDU_NATIVE); //could have been APDU_WRAPPED

   /* Create a simple DES key (here master key default value */
   pKey = mifare_NewDesKeyWithVersion((unsigned char*) "\0\0\0\0\0\0\0\0",
		   MF_CHAINING_DESFIRE_NATIVE); // MF_CHAINING_DESFIRE_NATIVE because we want this key to be DESFire EV0 compliant

   /* DESFire commands */

   /* Get version */
   iReturn = desfire_GetVersion(pDesfireContext, &sInfo);
   pprintf("---> desfire_GetVersion\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   if (iReturn == DESFIRE_OPERATION_OK)
   {
      for (i = 0; i < sizeof(struct S_DESFIRE_VERSION_INFO); i++)
      {
         if (i == 0)
         {
            pprintf("HW info :");
         }
         else if (i == 7)
         {
            pprintf("\nSW info :");
         }
         else if (i == 14)
         {
            pprintf("\nOther info :");
         }
         pprintf(" %02X", ((unsigned char*) &sInfo)[i]);
      }
      pprintf("\n");
      ttestall(PRINTER, 0);
   }

   /* Authentication with the created key */
   iReturn = desfire_Authenticate(pDesfireContext, 0, pKey);
   pprintf("---> desfire_Authenticate\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Get card UID with DESFire command */
   iReturn = desfire_GetCardUID(pDesfireContext, array, &arrayLen);
   pprintf("---> desfire_GetCardUID\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   if (iReturn == DESFIRE_OPERATION_OK)
   {
      pprintf("UID :");
      for (i = 0; i < arrayLen; i++)
      {
         pprintf(" %02X", array[i]);
      }
      pprintf("\n");
   }

   /* Get the list of existing applications */
   iReturn = desfire_GetApplicationIds(pDesfireContext, arrayAID, &count);
   pprintf("---> desfire_GetApplicationIds\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   if (iReturn == DESFIRE_OPERATION_OK)
   {
      if (count != 0)
      {
         for (i = 0; i < count; i++)
         {
            pprintf("%02X %02X %02X\n", arrayAID[i][0], arrayAID[i][1],
                  arrayAID[i][2]);
         }
      }
   }

   /* Creation of 3 applications with different settings */
   iReturn = desfire_CreateApplication(pDesfireContext, 0x11, 0xFF, 0x00, 0, 0, 0);
   pprintf("---> desfire_CreateApplication\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   iReturn = desfire_CreateApplication(pDesfireContext, 0x22, 0xEF, 0x06, 0, 0, 0);
   pprintf("---> desfire_CreateApplication\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   iReturn = desfire_CreateApplication(pDesfireContext, 0x33, 0xC2, 0x0E, 0, 0, 0);
   pprintf("---> desfire_CreateApplication\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Get the list of existing applications */
   iReturn = desfire_GetApplicationIds(pDesfireContext, arrayAID, &count);
   pprintf("---> desfire_GetApplicationIds\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   if (iReturn == DESFIRE_OPERATION_OK)
   {
      if (count != 0)
      {
         for (i = 0; i < count; i++)
         {
            pprintf("%02X %02X %02X\n", arrayAID[i][0], arrayAID[i][1],
                  arrayAID[i][2]);
         }
      }
   }

   /* Selection of the 2nd application */
   iReturn = desfire_SelectApplication(pDesfireContext, 0x22);
   pprintf("---> desfire_SelectApplication\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Authentication with application master key (use the same default key)*/
   iReturn = desfire_Authenticate(pDesfireContext, 0, pKey);
   pprintf("---> desfire_Authenticate\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Creation of a file backup data file within the selected application */
   iReturn = desfire_CreateBackupDataFile(pDesfireContext, (T_DESFIRE_FID) 0x09, NULL,
         DCM_ENCIPHERED, 0x0000, 20);
   pprintf("---> desfire_CreateBackupDataFile\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Get the list of existing files */
   iReturn = desfire_GetFileIds(pDesfireContext, array, &count);
   pprintf("---> desfire_GetFileIds\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   if (iReturn == DESFIRE_OPERATION_OK)
   {
      if (count != 0)
      {
         for (i = 0; i < count; i++)
         {
            pprintf("%02X\n", array[i]);
         }
      }
   }

   /* Write data into the file */
   iReturn = desfire_WriteData(pDesfireContext, (T_DESFIRE_FID) 0x09, 0, 11,
         "Hello World");
   pprintf("---> desfire_WriteData\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Read the file without having commited the data */
   iReturn = desfire_ReadData(pDesfireContext, (T_DESFIRE_FID) 0x09, 0, 0,
         (unsigned long*) &count, array);
   pprintf("---> desfire_ReadData\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   if (iReturn == DESFIRE_OPERATION_OK)
   {
      if (count != 0)
      {
         for (i = 0; i < count; i++)
         {
            pprintf("%c", array[i]);
         }
         pprintf("\n", array[i]);
      }
   }

   /* Commit transaction (mandatory, except for standard data files, to validate files changes) */
   iReturn = desfire_CommitTransaction(pDesfireContext);
   pprintf("---> desfire_CommitTransaction\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);

   /* Read the file after having commited the data */
   iReturn = desfire_ReadData(pDesfireContext, (T_DESFIRE_FID) 0x09, 0, 0,
         (unsigned long*) &count, array);
   pprintf("---> desfire_ReadData\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iReturn);
   if (iReturn == DESFIRE_OPERATION_OK)
   {
      if (count != 0)
      {
         for (i = 0; i < count; i++)
         {
            pprintf("%c", array[i]);
         }
         pprintf("\n", array[i]);
      }
   }

   /* Destruction of created keys */
   mifare_FreeKey(pKey);
   /* Context destruction */
   desfire_FreeContext(pDesfireContext);
}

void Sample_Format_PICC(void)
{
   int iResult = 0;
   T_DESFIRE_CONTEXT *pDesfireContext;
   T_MIFARE_KEY *pKey;

   /* Context initialization */
   pDesfireContext = desfire_NewContext(APDU_NATIVE); //could have been APDU_WRAPPED

   /* Create a simple DES key (here master key default value */
   pKey = mifare_NewDesKeyWithVersion((unsigned char*) "\0\0\0\0\0\0\0\0",
		  MF_CHAINING_DESFIRE_NATIVE); // MF_CHAINING_DESFIRE_NATIVE because we want this key to be DESFire EV0 compliant

   /* Authentication with the created key */
   iResult = desfire_Authenticate(pDesfireContext, 0, pKey);
   pprintf("---> desfire_Authenticate\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iResult);

   /* Format PICC */
   iResult = desfire_FormatPicc(pDesfireContext);
   pprintf("---> desfire_FormatPicc\n");
   ttestall(PRINTER, 0);
   Desfire_Print_Return_Code(iResult);

   /* Destruction of created keys */
   mifare_FreeKey(pKey);
   /* Context destruction */
   desfire_FreeContext(pDesfireContext);
}

void Sample_Authenticate_Host(void)
{
  int iResult = 0;
  T_MIFARE_KEY *pKey;
  unsigned char ucAuthMode;
  unsigned char ucKeyNo;
  unsigned char ucKeyVersion;
  unsigned char ucDivInp[2];
  char tucString[128];

  trace(0, strlen("Sample_Authenticate_Host()"), "Sample_Authenticate_Host()");

  Sample_FreeContext();

  //SAM activation
  hSAM = mifareSAM_AutoDetectSAM();
  if (hSAM == NULL)
  {
     sprintf(tucString, "SAM init failed");
     trace(0, strlen(tucString), tucString);
     return;
  }

  pSamContext = mifareSAM_NewContext(hSAM, MF_SAM_AV1); //could have been APDU_WRAPPED
  if (pSamContext == NULL)
  {
      sprintf(tucString, "SAM not found or if power on failed");
      trace(0, strlen(tucString), tucString);
      return;
   }

  /* Create a simple DES key (here master key default value */
  pKey = mifare_NewDesKeyWithVersion((unsigned char*) "\0\0\0\0\0\0\0\0",
		  MF_CHAINING_CBC); // MF_CHAINING_CBC because NATIVE should not occurs for SAM keys

  ucAuthMode   = 0;    // ok
  ucKeyNo      = 0x02; // ok
  ucKeyVersion = 0;    // ok
  memset(ucDivInp, 0x00, sizeof(ucDivInp));

  /* Format PICC */
  iResult = mifareSAM_AuthenticateHost(pSamContext, pKey, ucAuthMode, ucKeyNo, ucKeyVersion, ucDivInp, sizeof(ucDivInp));
  pprintf("---> mifareSAM_AuthenticateHost\n");
  ttestall(PRINTER, 0);
  Desfire_Print_Return_Code(iResult);

  {
    sprintf(tucString, "mifareSAM_AuthenticateHost result : %x", iResult);
    trace(0, strlen(tucString), tucString);
  }

  /* Destruction of created keys */
  if (pKey != NULL)
      mifare_FreeKey(pKey);
  pKey = NULL;
}

void Sample_ChangeKeyEntry(void)
{
  int iResult = 0;
  char tucString[128];

  const unsigned char ucNewPosAkey[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
  const unsigned char ucNewPosBkey[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  const unsigned char ucNewPosCkey[16] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0x90, 0x81, 0x72, 0x63, 0x54, 0x5E, 0x74, 0x0F};
  const unsigned char ucDfAid[3] = {0x00, 0x00, 0x00};
  const unsigned char ucSet[2] = {0x20, 0x00};


  unsigned char ucKeyNo;
  unsigned char ucProgMask;
  T_MIFARE_KEY_ENTRY KeyEntry;

  trace(0, strlen("Sample_ChangeKeyEntry()"), "Sample_ChangeKeyEntry()");

  return;

  // Check input parameters
  if ((hSAM == NULL) || (pSamContext == NULL))
  {
    sprintf(tucString, "SAM not initialized");
    trace(0, strlen(tucString), tucString);
    return;
  }

  memcpy(KeyEntry.tKeyA, ucNewPosAkey, sizeof(ucNewPosAkey));
  memcpy(KeyEntry.tKeyB, ucNewPosBkey, sizeof(ucNewPosBkey));
  memcpy(KeyEntry.tKeyC, ucNewPosCkey, sizeof(ucNewPosCkey));
  memcpy(KeyEntry.dfAid, ucDfAid, sizeof(ucDfAid));
  KeyEntry.dfKeyNr = 0;
  KeyEntry.CEK_No = 0;
  KeyEntry.CEK_V = 0;
  KeyEntry.KUC = 0xff;
  memcpy(KeyEntry.SET, ucSet, sizeof(ucSet));
  KeyEntry.VerA = 0x00;
  KeyEntry.VerB = 0x01;
  KeyEntry.VerC = 0x02;

  ucKeyNo = 0;       // Key entry number
  ucProgMask = 0xFF; // Versions are sent separately and all items are updated.

  iResult = mifareSAM_ChangeKeyEntry(pSamContext, ucKeyNo, ucProgMask, &KeyEntry);
  pprintf("---> Sample_ChangeKeyEntry\n");
  ttestall(PRINTER, 0);
  {
    sprintf(tucString, "Sample_ChangeKeyEntry result : %x", iResult);
    trace(0, strlen(tucString), tucString);
  }
  Desfire_Print_Return_Code(iResult);
}


void Sample_ResetKeyEntry(void)
{
  int iResult = 0;
  char tucString[128];

  const unsigned char ucNewPosAkey[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
  const unsigned char ucNewPosBkey[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  const unsigned char ucNewPosCkey[16] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0x90, 0x81, 0x72, 0x63, 0x54, 0x5E, 0x74, 0x0F};
  const unsigned char ucDfAid[3] = {0x00, 0x00, 0x00};
  const unsigned char ucSet[2] = {0x20, 0x80}; // AES-192


  unsigned char ucKeyNo;
  unsigned char ucProgMask;
  T_MIFARE_KEY_ENTRY KeyEntry;

  trace(0, strlen("Sample_ResetKeyEntry()"), "Sample_ResetKeyEntry()");

  // Check input parameters
  if ((hSAM == NULL) || (pSamContext == NULL))
  {
    sprintf(tucString, "SAM not initialized");
    trace(0, strlen(tucString), tucString);
    return;
  }

  memcpy(KeyEntry.tKeyA, ucNewPosAkey, sizeof(ucNewPosAkey));
  memcpy(KeyEntry.tKeyB, ucNewPosBkey, sizeof(ucNewPosBkey));
  memcpy(KeyEntry.tKeyC, ucNewPosCkey, sizeof(ucNewPosCkey));
  memcpy(KeyEntry.dfAid, ucDfAid, sizeof(ucDfAid));
  KeyEntry.dfKeyNr = 0;
  KeyEntry.CEK_No = 0;
  KeyEntry.CEK_V = 0;
  KeyEntry.KUC = 0xff;
  memcpy(KeyEntry.SET, ucSet, sizeof(ucSet));
  KeyEntry.VerA = 0x00;
  KeyEntry.VerB = 0x01;
  KeyEntry.VerC = 0x02;

  ucKeyNo = 0;       // Key entry number
  ucProgMask = 0xFF; // Versions are sent separately and all items are updated.

  iResult = mifareSAM_ChangeKeyEntry(pSamContext, ucKeyNo, ucProgMask, &KeyEntry);
  pprintf("---> mifareSAM_ChangeKeyEntry\n");
  ttestall(PRINTER, 0);
  Desfire_Print_Return_Code(iResult);

  {
    sprintf(tucString, "mifareSAM_ChangeKeyEntry result : %x", iResult);
    trace(0, strlen(tucString), tucString);
  }
}


void Sample_FreeContext(void)
{
  /* Context destruction */
  if (pSamContext != NULL)
  	mifareSAM_FreeContext(pSamContext);
  pSamContext = NULL;
}

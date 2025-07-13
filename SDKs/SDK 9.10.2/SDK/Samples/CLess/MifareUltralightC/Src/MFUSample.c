/**
 *
 * \author      INGENICO
 * \version     1.0
 * \author   Ingenico has intellectual property rights relating to the technology embodied \n
 *           in this software. In particular, and without limitation, these intellectual property rights may\n
 *           include one or more patents.\n
 *           This software is distributed under licenses restricting its use, copying, distribution, and\n
 *           and decompilation. No part of this software may be reproduced in any form by any means\n
 *           without prior written authorization of Ingenico.
 *
 **/

/* ===================================================================== */
/*                      INCLUDES                                         */
/* ===================================================================== */

#include "SDK30.H"
#include "ClessMFU.h"
#include "Cless_LowLevel.h"     // low level interface of the contactless DLL.
#include "oem_cless.h"          // Telium Pass include driver
#include "oem_clmf1.h"          // Mifare

#define MAX_TRIES        3      // Number tries before ending up with a communication error

/***********************************************************
 *
 * name:       Sample_MF_UltralightC
 *
 * definition:  Sample of Mifare Ultralight C application
 *              using Thunder for cryptographic operations.
 *
 * param:      none
 *
 * return:     none
 *
 ***********************************************************/
void Sample_MF_ULC(void)
{
   FILE* hDisplay = NULL;
   FILE* hKeyboard = NULL;
   FILE* hPrinter = NULL;
   T_MFU_CONTEXT* pMFUContext = NULL;
   int nResult;
   int nbTries;
   unsigned int nNumOfCards;
   unsigned char buff[64];
   char* keyVal;


   hDisplay = fopen("DISPLAY", "w");
   hKeyboard = fopen("KEYBOARD", "r");
   hPrinter = fopen("PRINTER", "w");

   pprintf("\x0f======== MIFARE Ultralight C sample =========\n\n");

   ///////////////////////////////////////////////////////////////////////
   // Manage retries, in this sample we manage retries only on detection/activation
   nbTries = 1;
   while(nbTries <= MAX_TRIES)
   {
      if(nbTries > 1)
      {  // Close the contactless driver (shut down the RF field)
         ClessMifare_CloseDriver();
      }

      ///////////////////////////////////////////////////////////////////////
      // Open contactless Mifare driver
      nResult = ClessMifare_OpenDriver();
      if (nResult != MF_OK)
      {
         pprintf("ClessMifare_OpenDriver() KO\n");
         goto EXIT;
      }
      pprintf("ClessMifare Driver open\n");

      ///////////////////////////////////////////////////////////////////////
      // Ultralight card detection
      printf("\x1b" "   Tap ULC\n     card");
      // Detect the card (synchronous mode)
      nNumOfCards = 1;
      nResult = ClessMifare_DetectCardsEx(CL_MF_ULTRALIGHT, &nNumOfCards, 30);
      if (nResult != MF_OK)
      {
         if (nResult == MF_NO_CARD)
         {  //case detection timeout
            pprintf("ClessMifare_DetectCardsEx KO (Timeout)\n");
            goto EXIT;
         }
         else
         {
            pprintf("ClessMifare_DetectCardsEx KO\n");
            nbTries++;
            continue;
         }
      }
      pprintf("Card detected\n");

      ///////////////////////////////////////////////////////////////////////
      // Card activation
      nResult = ClessMifare_ActiveCard(0);
      if (nResult != MF_OK)
      {
         pprintf("ClessMifare_ActiveCard KO\n");
         nbTries++;
         continue;
      }
      pprintf("Card activated\n");
      break;
   }

   if(nbTries > MAX_TRIES)
   {
      pprintf("Nb Tries KO\n");
      goto EXIT;
   }

   ///////////////////////////////////////////////////////////////////////
   // Create Mifare Ultralight Context
   pMFUContext = ClessMFU_NewContext();
   if (pMFUContext == NULL)
   {
      pprintf("ClessMFU_NewContext KO\n");
      goto EXIT;
   }
   pprintf("MFU context created\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read pages 0..3
   nResult = ClessMFU_Read(pMFUContext, 0, buff);
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Read KO\n");
      goto EXIT;
   }
   pprintf("Read pages 0..3 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Ultralight C Authentication
   keyVal = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
   nResult = ClessMFU_Authenticate(pMFUContext, keyVal);
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Authenticate KO\n");
      goto EXIT;
   }
   pprintf("ULC Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write page x11
   nResult = ClessMFU_Write(pMFUContext, 0x11, "P.11");
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Write KO\n");
      goto EXIT;
   }
   pprintf("Write page x11 OK\n");


   ///////////////////////////////////////////////////////////////////////
   //  Read page x11
   nResult = ClessMFU_Read(pMFUContext, 0x11, buff);
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Read KO\n");
      goto EXIT;
   }
   if(0 != memcmp(buff,  "P.11", 4))
   {
      pprintf("Read Data KO\n");
      goto EXIT;
   }
   pprintf("Read page x11 OK\n");

   printf("\x1b" "   SAMPLE ULC\n      DONE");
   pprintf("\nSample Ultralight C Done\n");
EXIT:
   pprintf("\n\n\n\n");
   ttestall(PRINTER, 0);
   printf("\x1b");

   ClessMFU_FreeContext(pMFUContext);

   // Close the contactless driver (shut down the RF field)
   ClessMifare_CloseDriver();

   // Close peripheral drivers
   if(hDisplay != NULL)
      fclose(hDisplay);
   if(hKeyboard != NULL)
      fclose(hKeyboard);
   if(hPrinter != NULL)
      fclose(hPrinter);
}


/***********************************************************
 *
 * name:       Sample_MF_ULC_With_SAM
 *
 * definition:  Sample of Mifare Ultralight C application
 *              using a Mifare SAM AV2 for cryptographic operations.
 *              A Mifare SAM in AV2 mode should be present in SAM1 slot and the following keys are expected:
 *                - key 1 V0 : AES Host Authentication key with value 00 ... 00
 *                - key 6 V0 : TDEA-ISO (16 bits) Picc key with value 00 ... 00 00  (Keep IV bit set)
 *
 * param:      none
 *
 * return:     none
 *
 ***********************************************************/
void Sample_MF_ULC_With_SAM(void)
{
   FILE* hDisplay = NULL;
   FILE* hKeyboard = NULL;
   FILE* hPrinter = NULL;
   FILE* hSAM = NULL;
   HISTORIC historic;
   T_MFU_CONTEXT* pMFUContext = NULL;
   T_MIFARE_KEY *pSamKey = NULL;
   int nResult;
   int nbTries;
   unsigned int nNumOfCards;
   unsigned char buff[64];
   unsigned char mode;

   hDisplay = fopen("DISPLAY", "w");
   hKeyboard = fopen("KEYBOARD", "r");
   hPrinter = fopen("PRINTER", "w");

   pprintf("\x0f====== MIFARE Ultralight C sample with SAM =====\n\n");

   ///////////////////////////////////////////////////////////////////////
   // Manage retries, in this sample we manage retries only on detection/activation
   nbTries = 1;
   while(nbTries <= MAX_TRIES)
   {
      if(nbTries > 1)
      {  // We are making a retry -> close the contactless driver (shut down the RF field)
         ClessMifare_CloseDriver();
      }

      ///////////////////////////////////////////////////////////////////////
      // Open MIFARE Classic (ISO 14443-3) driver
      nResult = ClessMifare_OpenDriver();
      if (nResult != MF_OK)
      {
         pprintf("ClessMifare_OpenDriver() KO\n");
         goto EXIT;
      }
      pprintf("ClessMifare Driver open\n");

      ///////////////////////////////////////////////////////////////////////
      // Ultralight card detection
      printf("\x1b" "   Tap ULC\n     card");;
      // Detect the card (synchronous mode)
      nNumOfCards = 1;
      nResult = ClessMifare_DetectCardsEx(CL_MF_ULTRALIGHT, &nNumOfCards, 30);
      if (MF_OK != nResult)
      {
         if (nResult == MF_NO_CARD)
         {  //case detection timeout
            pprintf("ClessMifare_DetectCardsEx KO (Timeout)\n");
            goto EXIT;
         }
         else
         {
            pprintf("ClessMifare_DetectCardsEx KO\n");
            nbTries++;
            continue;
         }
      }
      pprintf("Card detected\n");

      ///////////////////////////////////////////////////////////////////////
      // Card activation
      nResult = ClessMifare_ActiveCard(0);
      if (nResult != MF_OK)
      {
         nbTries++;
         continue;
      }
      pprintf("Card activated\n");
      break;
   }

   if(nbTries > MAX_TRIES)
   {
      pprintf("Nb Tries KO\n");
      goto EXIT;
   }

   ///////////////////////////////////////////////////////////////////////
   //SAM1 activation
   hSAM = fopen("SAM1", "rw");
   if (hSAM == NULL)
   {
      pprintf("SAM fopen KO\n");
      goto EXIT;
   }
   nResult = power_on(hSAM, &historic);
   if (nResult != 0)
   {
      pprintf("SAM power_on KO\n");
      goto EXIT;
   }
   pprintf("SAM found\n");

   ///////////////////////////////////////////////////////////////////////
   // Create Mifare Ultralight Context
   pMFUContext = ClessMFU_NewContextWithSAM(hSAM, MF_SAM_AV2);
   if (pMFUContext == NULL)
   {
      pprintf("ClessMFU_NewContextWithSAM KO\n");
      goto EXIT;
   }
   pprintf("MFU context created\n");

   ///////////////////////////////////////////////////////////////////////
   // Host-SAM AES Authentication with SAM Key 1 version 0, no diversification and Full protection mode
   pSamKey = mifare_NewAesKey((unsigned char*) "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
   if (pSamKey == NULL)
   {
      pprintf("mifare_NewAesKey KO\n");
      goto EXIT;
   }

   mode = 2;  // Full protection mode
   nResult = mifareSAM_AuthenticateHost(ClessMFU_GetSAMContext(pMFUContext), pSamKey, mode, 1, 0, NULL, 0);
   mifare_FreeKey(pSamKey);
   if (nResult != MF_OK)
   {
      pprintf("mifareSAM_AuthenticateHost KO\n");
      goto EXIT;
   }
   pprintf("SAM Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read pages 0..3
   nResult = ClessMFU_Read(pMFUContext, 0, buff);
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Read KO\n");
      goto EXIT;
   }
   pprintf("Read pages 0..3 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Mifare Ultralight C Authentication using SAM Key 6 V0, no diversification
   mode = 0;
   nResult = ClessMFU_AuthenticateWithSAM(pMFUContext, 6, 0, mode, 0, NULL);
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_AuthenticateWithSAM KO\n");
      goto EXIT;
   }
   pprintf("Ultralight C Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write page x11
   nResult = ClessMFU_Write(pMFUContext, 0x11, "P.11");
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Write KO\n");
      goto EXIT;
   }
   pprintf("Write page x11 OK\n");


   ///////////////////////////////////////////////////////////////////////
   //  Read page x11
   nResult = ClessMFU_Read(pMFUContext, 0x11, buff);
   if (nResult != MFU_OK)
   {
      pprintf("ClessMFU_Read KO\n");
      goto EXIT;
   }
   if(0 != memcmp(buff,  "P.11", 4))
   {
      pprintf("Read Data KO\n");
      goto EXIT;
   }
   pprintf("Read page x11 OK\n");

   printf("\x1b" "   SAMPLE ULC\n      DONE");
   pprintf("\nSample Ultralight C with SAM done\n");
EXIT:
   pprintf("\n\n\n\n");
   ttestall(PRINTER, 0);
   printf("\x1b");


   ClessMFU_FreeContext(pMFUContext);

   // Power off / close the SAM
   if(hSAM)
   {
      power_down(hSAM);
      fclose(hSAM);
   }

   // Close the contactless driver (shut down the RF field)
   ClessMifare_CloseDriver();

   // Close other peripheral drivers
   if(hDisplay != NULL)
      fclose(hDisplay);
   if(hKeyboard != NULL)
      fclose(hKeyboard);
   if(hPrinter != NULL)
      fclose(hPrinter);
}

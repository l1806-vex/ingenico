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
#include "ClessMFP.h"
#include "Desfire.h"

#include "Cless_LowLevel.h"     // low level interface of the contactless DLL.
#include "oem_cless.h"          // Telium Pass include driver
#include "oem_clmf1.h"          // Mifare


// Local variables


/***********************************************************
 *
 * name:       Sample_MFP_SL3
 *
 * definition:  Sample of Mifare Plus in Security Level 3 application
 *              using Thunder for key management and cryptographic operations.
 *
 * param:      none
 *
 * return:     none
 *
 ***********************************************************/
void Sample_MFP_SL3(void)
{
   FILE* hDisplay;
   FILE* hKeyboard;
   FILE* hPrinter;
   T_MFP_CONTEXT* pMFPContext = NULL;
   unsigned int nNumOfCards = 1;
   int nResult;
   unsigned char buff[64];
   int val;


   hDisplay = fopen("DISPLAY", "w");
   hKeyboard = fopen("KEYBOARD", "r");
   hPrinter = fopen("PRINTER", "w");

   pprintf("\x0f\n========= MIFARE Plus SL3 sample =========\n\n");

   ///////////////////////////////////////////////////////////////////////
   // Open ISO 14443-4 driver
   nResult = ClessEmv_OpenDriver();
   if (nResult == CL_KO)
   {
      pprintf("ClessEmv_OpenDriver() KO\n");
      goto EXIT;
   }
   pprintf("ClessEmv Driver open\n");

   ///////////////////////////////////////////////////////////////////////
   // ISO Card detection
   printf("\x1b" "PRESENT MFP SL3\n     CARD");
   // Detect the card (synchronous mode)
   nResult = ClessEmv_DetectCards(CL_TYPE_A, &nNumOfCards, 30);
   if (CL_OK != nResult)
   {
      pprintf("ClessEmv_DetectCards KO\n");
      goto EXIT;
   }
   pprintf("Card detected\n");

   ///////////////////////////////////////////////////////////////////////
   // ISO Card activation
   nResult = ClessEmv_ActiveCard(0, CL_ISO14443_4);
   if (nResult != CL_OK)
   {
      pprintf("ClessEmv_ActiveCard KO\n");
      goto EXIT;
   }
   pprintf("Card activated\n");

   ///////////////////////////////////////////////////////////////////////
   // Create Mifare Plus Context
   pMFPContext = ClessMFP_NewContext();
   if (pMFPContext == NULL)
   {
      pprintf("ClessMFP_NewContext KO\n");
      goto EXIT;
   }
   pprintf("MFP context created\n");

   ///////////////////////////////////////////////////////////////////////
   // Proximity check with Proximity Check Key (PC key is 00 ... 00)
   nResult = ClessMFP_SL3ProximityCheck(pMFPContext, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3ProximityCheck KO x%04X\n", nResult);
      goto EXIT;
   }
   pprintf("Proximity Check OK\n");


   ///////////////////////////////////////////////////////////////////////
   //  Authenticate with AES key 0x4002 (Sector 1 Key A)
   nResult = ClessMFP_SL3Authenticate(pMFPContext, 0x4002, MFP_AUTH_F, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3Authenticate KO\n");
      goto EXIT;
   }
   pprintf("AES Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write 2 blocks (4, 5)
   nResult = ClessMFP_SL3Write(pMFPContext, MFP_WRITE_MAC, 4, 2, "- Hello Block 4 from MFPSample -");
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3Write KO\n");
      goto EXIT;
   }
   pprintf("Write blocks 4 & 5 OK\n");


   ///////////////////////////////////////////////////////////////////////
   //  Read blocks 4, 5
   nResult = ClessMFP_SL3Read(pMFPContext, MFP_READ_MAC, 4, 2, buff);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3Read KO\n");
      goto EXIT;
   }
   if(0 != memcmp(buff,  "- Hello Block 4 from MFPSample -", 2*16))
   {
      pprintf("Read Data KO\n");
      goto EXIT;
   }
   pprintf("Read blocks 4 & 5 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write value 2012 in block 6
   val = 2012;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_WRITE, 6, 0, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Write Value KO\n");
      goto EXIT;
   }
   pprintf("Write Value 2012 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Increment(+3) & Transfer Value (block 6)
   val = 3;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_INC_TRANSFER_MAC, 6, 6, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP IncTransfer value KO\n");
      goto EXIT;
   }
   pprintf("Add Value 3 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read value in block 6
   val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_READ_MAC, 6, 0, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Read Value KO\n");
      goto EXIT;
   }
   if(val != 2012+3)
   {
      pprintf("Read Value KO\n");
      goto EXIT;
   }
   pprintf("Read Value 2012+3 OK\n");

   printf("\x1b" "   SAMPLE\n      DONE");
   pprintf("\nSample MFP SL3 Done\n");
EXIT:
   pprintf("\n\n\n\n");
   ttestall(PRINTER, 0);
   printf("\x1b");

   ClessMFP_FreeContext(pMFPContext);

   // Close peripheral drivers
   fclose(hDisplay);
   fclose(hKeyboard);
   fclose(hPrinter);
   ClessEmv_CloseDriver();// Close the contactless driver
}


/***********************************************************
 *
 * name:       Sample_MFP_SL3_With_SAM
 *
 * definition:  Sample of Mifare Plus in Security Level 3 application
 *              using a Mifare SAM AV2 for key management and cryptographic operations.
 *              A Mifare SAM in  AV2 mode should be present and the following keys are expected:
 *                - key 1 V0 : AES Host Authentication key with value 00 ... 00
 *                - key 2 V0 : AES Picc key with value 00 ... 00
 *
 * param:      none
 *
 * return:     none
 *
 ***********************************************************/
void Sample_MFP_SL3_With_SAM(void)
{
   FILE* hDisplay;
   FILE* hKeyboard;
   FILE* hPrinter;
   FILE* hSAM = NULL;
   T_MFP_CONTEXT* pMFPContext = NULL;
   unsigned int nNumOfCards = 1;
   int nResult;
   unsigned char buff[64];
   int val;

   hDisplay = fopen("DISPLAY", "w");
   hKeyboard = fopen("KEYBOARD", "r");
   hPrinter = fopen("PRINTER", "w");

   pprintf("\x0f\n========= MIFARE Plus SL3 sample with SAM =====\n\n");

   ///////////////////////////////////////////////////////////////////////
   //SAM activation
   hSAM = mifareSAM_AutoDetectSAM();
   if (hSAM == NULL)
   {
      pprintf("SAM not found\n");
      goto EXIT;
   }
   pprintf("SAM found\n");

   ///////////////////////////////////////////////////////////////////////
   // Open ISO 14443-4 driver
   nResult = ClessEmv_OpenDriver();
   if (nResult == CL_KO)
   {
      pprintf("ClessEmv_OpenDriver() KO\n");
      goto EXIT;
   }
   pprintf("ClessEmv Driver open\n");

   ///////////////////////////////////////////////////////////////////////
   // ISO Card detection
   printf("\x1b" "PRESENT MFP SL3\n     CARD");
   // Detect the card (synchronous mode)
   nResult = ClessEmv_DetectCards(CL_TYPE_A, &nNumOfCards, 30);
   if (CL_OK != nResult)
   {
      pprintf("ClessEmv_DetectCards KO\n");
      goto EXIT;
   }
   pprintf("Card detected\n");

   ///////////////////////////////////////////////////////////////////////
   // ISO Card activation
   nResult = ClessEmv_ActiveCard(0, CL_ISO14443_4);
   if (nResult != CL_OK)
   {
      pprintf("ClessEmv_ActiveCard KO\n");
      goto EXIT;
   }
   pprintf("Card activated\n");

   ///////////////////////////////////////////////////////////////////////
   // Create Mifare Plus Context
   pMFPContext = ClessMFP_NewContextWithSAM(hSAM);
   if (pMFPContext == NULL)
   {
      pprintf("ClessMFP_NewContextWithSAM KO\n");
      goto EXIT;
   }
   pprintf("MFP context created\n");

   ///////////////////////////////////////////////////////////////////////
   // Host-SAM Authentication with SAM Key 1 version 0 and Full protection mode
   nResult = ClessMFP_SAMAuthenticate(pMFPContext, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 1, 0, 2);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SAMAuthenticate KO\n");
      goto EXIT;
   }
   pprintf("SAM Authenticated\n");

   ///////////////////////////////////////////////////////////////////////
   // Proximity check with Proximity Check Key (PC key is 00 ... 00)
   nResult = ClessMFP_SL3ProximityCheckWithSAM(pMFPContext, 2, 0, 0, NULL);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3ProximityCheck KO x%04X\n", nResult);
      goto EXIT;
   }
   pprintf("Proximity Check OK\n");


   ///////////////////////////////////////////////////////////////////////
   //  Authenticate First SL3 using MFP AES key 0x4002 (Sector 1 Key A) and SAM Key 2 V0, no diversification
   nResult = ClessMFP_SL3AuthenticateWithSAM(pMFPContext, 0x4002, MFP_AUTH_F, 2, 0, 0, NULL);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3AuthenticateWithSAM KO\n");
      goto EXIT;
   }
   pprintf("AES Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write 2 blocks (4, 5)
   nResult = ClessMFP_SL3Write(pMFPContext, MFP_WRITE_MAC, 4, 2, "- Hello Block 4 from MFPSample -");
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3Write KO\n");
      goto EXIT;
   }
   pprintf("Write blocks 4 & 5 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read blocks 4, 5
   nResult = ClessMFP_SL3Read(pMFPContext, MFP_READ_MAC, 4, 2, buff);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL3Read KO\n");
      goto EXIT;
   }
   if(0 != memcmp(buff,  "- Hello Block 4 from MFPSample -", 2*16))
   {
      pprintf("Read Data KO\n");
      goto EXIT;
   }
   pprintf("Read blocks 4 & 5 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write value 2012 in block 6
   val = 2012;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_WRITE, 6, 0, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Write Value KO\n");
      goto EXIT;
   }
   pprintf("Write Value 2012 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Increment(+3) & Transfer Value (block 6)
   val = 3;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_INC_TRANSFER_MAC, 6, 6, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP IncTransfer value KO\n");
      goto EXIT;
   }
   pprintf("IncTransfer Value 3 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read value in block 6
   val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_READ_MAC, 6, 0, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Read Value KO\n");
      goto EXIT;
   }
   if(val != 2012+3)
   {
      pprintf("Read Value KO\n");
      goto EXIT;
   }
   pprintf("Read Value 2012+3 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Decrement (-4) block 6
   val = 4;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_DECREMENT, 6, 0, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Decrement value KO\n");
      goto EXIT;
   }
   pprintf("Decrement Value 4 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Tranfert to block 6
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_TRANSFER_MAC, 6, 0, NULL);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Tranfer value KO\n");
      goto EXIT;
   }
   pprintf("Tranfert Value OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read value in block 6
   val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL3ValueOperation(pMFPContext, MFP_READ_MAC, 6, 0, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP Read Value KO\n");
      goto EXIT;
   }
   if(val != 2015-4)
   {
      pprintf("Read Value KO\n");
      goto EXIT;
   }
   pprintf("Read Value 2015+4 OK\n");

   printf("\x1b" "   SAMPLE\n      DONE");
   pprintf("\nSample MFP SL3 with SAM Done\n");
EXIT:
   pprintf("\n\n\n\n");
   ttestall(PRINTER, 0);
   printf("\x1b");

   // Close peripheral drivers

   ClessMFP_FreeContext(pMFPContext);
   if(hSAM)
      fclose(hSAM);

   fclose(hDisplay);
   fclose(hKeyboard);
   fclose(hPrinter);
   ClessEmv_CloseDriver();// Close the contactless driver
}

/***********************************************************
 *
 * name:       Sample_MFP_SL2_With_SAM
 *
 * definition:  Sample of Mifare Plus in Security Level 2 application
 *              using a Mifare SAM AV2 for key management and cryptographic operations.
 *              A Mifare SAM in  AV2 mode should be present and the following keys are expected:
 *                - key 1 V0 : AES Host Authentication key with value 00 ... 00
 *                - key 2 V0 : AES Picc key with value 00 ... 00
 *                - key 4 V0 : MIFARE Picc key with value FF FF FF FF FF FF
 *
 * param:      none
 *
 * return:     none
 *
 ***********************************************************/
void Sample_MFP_SL2_With_SAM(void)
{
   FILE* hDisplay;
   FILE* hKeyboard;
   FILE* hPrinter;
   FILE* hSAM = NULL;
   T_MFP_CONTEXT* pMFPContext = NULL;
   unsigned int nNumOfCards = 1;
   int nResult;
   unsigned char buff[64];
   int val;

   hDisplay = fopen("DISPLAY", "w");
   hKeyboard = fopen("KEYBOARD", "r");
   hPrinter = fopen("PRINTER", "w");

   pprintf("\x0f\n========= MIFARE Plus SL2 sample with SAM =====\n\n");

   ///////////////////////////////////////////////////////////////////////
   //SAM activation
   hSAM = mifareSAM_AutoDetectSAM();
   if (hSAM == NULL)
   {
      pprintf("SAM not found\n");
      goto EXIT;
   }
   pprintf("SAM found\n");

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
   // ISO Card detection
   printf("\x1b" "PRESENT MFP SL2\n     CARD");
   // Detect the card (synchronous mode)
   nResult = ClessMifare_DetectCards(&nNumOfCards, 30);
   if (CL_OK != nResult)
   {
      pprintf("ClessMifare_DetectCards KO\n");
      goto EXIT;
   }
   pprintf("Card detected\n");

   ///////////////////////////////////////////////////////////////////////
   // ISO Card activation
   nResult = ClessMifare_ActiveCard(0);
   if (nResult != CL_OK)
   {
      pprintf("ClessMifare_ActiveCard KO\n");
      goto EXIT;
   }
   pprintf("Card activated\n");

   ///////////////////////////////////////////////////////////////////////
   // Create Mifare Plus Context
   pMFPContext = ClessMFP_NewContextWithSAM(hSAM);
   if (pMFPContext == NULL)
   {
      pprintf("ClessMFP_NewContextWithSAM KO\n");
      goto EXIT;
   }
   pprintf("MFP context created\n");

   ///////////////////////////////////////////////////////////////////////
   // Host-SAM Authentication with SAM Key 1 version 0 and Full protection mode
   nResult = ClessMFP_SAMAuthenticate(pMFPContext, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 1, 0, 2);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SAMAuthenticate KO\n");
      goto EXIT;
   }
   pprintf("SAM Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  AES Authenticate using MFP AES key 0x4002 (Sector 1 Key A) and SAM Key 2 V0, no diversification
   nResult = ClessMFP_SL2AuthenticateAESWithSAM(pMFPContext, 0x4002, MFP_AUTH_N, 2, 0, 0, NULL);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL2AuthenticateAESWithSAM KO\n");
      goto EXIT;
   }
   pprintf("AES Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Mifare Classic Authenticate using Key A of sector 1 and SAM Key 4 V0, no diversification
   nResult = ClessMFP_SL12AuthenticateClassicWithSAM (pMFPContext, MFP_KEY_A, 1, 4, 0, NULL);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL12AuthenticateClassicWithSAM KO\n");
      goto EXIT;
   }
   pprintf("Classic Authentication OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write 2 blocks (4, 5)
   nResult = ClessMFP_SL2WriteMultiBlock(pMFPContext, 4, 2, "-Hello Blk 4 from SL2 MFPSample-");
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL2WriteMultiBlock KO\n");
      goto EXIT;
   }
   pprintf("Write blocks 4 & 5 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read blocks 4, 5
   nResult = ClessMFP_SL2ReadMultiBlock(pMFPContext, 4, 2, buff);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP_SL2ReadMultiBlock KO\n");
      goto EXIT;
   }
   if(0 != memcmp(buff,  "-Hello Blk 4 from SL2 MFPSample-", 2*16))
   {
      pprintf("Read Data KO\n");
      goto EXIT;
   }
   pprintf("Read blocks 4 & 5 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Write value 7964 in block 6
   val = 7964;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL12ValueOperation(pMFPContext, MFP_SL12_WRITE, 6, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP SL12 Write Value KO\n");
      goto EXIT;
   }
   pprintf("Write Value 7964 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Decrement (-4) block 6
   val = 4;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL12ValueOperation(pMFPContext, MFP_SL12_DECREMENT, 6, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP SL12 Decrement value KO\n");
      goto EXIT;
   }
   pprintf("Decrement Value 4 OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Transfer to block 6
   nResult = ClessMFP_SL12ValueOperation(pMFPContext, MFP_SL12_TRANSFER, 6, NULL);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP SL12 Tranfer value KO\n");
      goto EXIT;
   }
   pprintf("Transfer Value OK\n");

   ///////////////////////////////////////////////////////////////////////
   //  Read value in block 6
   val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   nResult = ClessMFP_SL12ValueOperation(pMFPContext, MFP_SL12_READ, 6, &val);
   if (nResult != MFP_OK)
   {
      pprintf("ClessMFP SL12 Read Value KO\n");
      goto EXIT;
   }
   if(val != 7964-4)
   {
      pprintf("Read Value KO\n");
      goto EXIT;
   }
   pprintf("Read Value 7964-4 OK\n");

   printf("\x1b" "   SAMPLE\n      DONE");
   pprintf("\nSample MFP SL2 with SAM Done\n");
EXIT:
   pprintf("\n\n\n\n");
   ttestall(PRINTER, 0);
   printf("\x1b");

   // Close peripheral drivers

   ClessMFP_FreeContext(pMFPContext);
   if(hSAM)
      fclose(hSAM);
   ClessMifare_CloseDriver();// Close the contactless driver

   fclose(hDisplay);
   fclose(hKeyboard);
   fclose(hPrinter);
}

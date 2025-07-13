/**
 * \file
 * This module implement the Mastercard PayPass 3 Torn recover feature.
 *
 * \author  Ingenico
 * \author  Copyright (c) 2012 Ingenico
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *       in this software. In particular, and without limitation, these intellectual property rights may\n
 *       include one or more patents.\n
 *       This software is distributed under licenses restricting its use, copying, distribution, and\n
 *       and decompilation. No part of this software may be reproduced in any form by any means\n
 *       without prior written authorization of Ingenico.
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.h"
#include "APCLESS.h"

#ifdef PAYPASS_TORN


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define __APCLESS_PAYPASS_TORN_RECORD_MAX_SIZE              2048     ///< Max size of a Torn Record.
#define __APCLESS_PAYPASS_TORN_RECORD_LIFETIME_DEFAULT      0x12C    ///< Maximum time, in seconds, that a record can remain in the Torn Transaction Log (300 seconds).



/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static TLV_TREE_NODE __APCLESS_PayPassTorn_transactionLog = NULL;   ///< TLV Tree used for Torn Transaction Log management.
static TLV_TREE_NODE __APCLESS_PayPassTorn_record = NULL;           ///< TLV Tree used to identify the torn record used for the current transaction.


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static unsigned long __APCLESS_PayPassTorn_DateYYMMDDConvertToUl(const unsigned char* date);
static TLV_TREE_NODE __APCLESS_PayPassTorn_GetRecord(unsigned int recordIdx);
static int __APCLESS_PayPassTorn_CopyRecordInSharedBuffer(const unsigned long recordTag, const TLV_TREE_NODE tlvRecord, T_SHARED_DATA_STRUCT* outputDataStruct);
static int __APCLESS_PayPassTorn_RemoveRecordFromLog(TLV_TREE_NODE *treeRecord);
static int __APCLESS_PayPassTorn_CleanOldRecord(DATE *currentDate, int lifeTime);
static int __APCLESS_PayPassTorn_CopyRecordInTornLog(T_SHARED_DATA_STRUCT* recordDataStruct, TLV_TREE_NODE treeTornLog);
static int __APCLESS_PayPassTorn_AddRecordByDate(T_SHARED_DATA_STRUCT* recordDataStruct);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

/**
 * Convert a DCB coded date (YYMMDD) into an unsigned long.
 * @param date
 * @return
 */
static unsigned long __APCLESS_PayPassTorn_DateYYMMDDConvertToUl(const unsigned char* date)
{
   unsigned char year, month, day;
   unsigned long binDate;

   year = date[0];
   month = date[1];
   day = date[2];

   if (year >= 0x50)
      binDate = (0x19 << 24) + (year << 16) + (month << 8) + day;
   else
      binDate = (0x20 << 24) + (year << 16) + (month << 8) + day;

   return binDate;
}


/**
 * Get the number of torn transaction log records.
 * @return
 */
unsigned int APCLESS_PayPassTorn_GetNumberOfTornTxnLogRecords(void)
{
   TLV_TREE_NODE record;
   unsigned int recordNumber = 0;

   if(__APCLESS_PayPassTorn_transactionLog != NULL)
   {
      record = TlvTree_GetFirstChild(__APCLESS_PayPassTorn_transactionLog);

      while (record != NULL)
      {
         recordNumber++;

         // Get the next record
         record = TlvTree_GetNext(record);
      }
   }

   return recordNumber;
}


/**
 * Get a record from the torn transaction log.
 * @param[in] recordIdx Position of the record in the torn transaction log (i.e. if recordIdx is 1, the oldest record is returned).
 * @return
 *     - A pointer on the requested record node
 *     - NULL if a problem occurred
 */
static TLV_TREE_NODE __APCLESS_PayPassTorn_GetRecord (unsigned int recordIdx)
{
   unsigned int i;
   TLV_TREE_NODE record = NULL;

   if((__APCLESS_PayPassTorn_transactionLog != NULL) && (recordIdx > 0))
   {
      // Get the first record of the log
      record = TlvTree_GetFirstChild(__APCLESS_PayPassTorn_transactionLog);

      // Get the requested record
      for(i = 1; (i < recordIdx) && (record != NULL); i++)
         record = TlvTree_GetNext(record);
   }

   return record;
}


/**
 * Copy the given record in the shared buffer.
 * @param[in] recordTag Tag to be added in the shared buffer. This tag will contain the record data.
 * @param[in] tlvRecord TLV Tree containing all the record data.
 * @param[out] outputDataStruct Shared buffer filled with the given record.
 * @return
 *     - \ref TRUE if correctly performed (data found and \a outputDataStruct filled).
 *     - \ref FALSE if an error occurred.
 */
static int __APCLESS_PayPassTorn_CopyRecordInSharedBuffer (const unsigned long recordTag, const TLV_TREE_NODE tlvRecord, T_SHARED_DATA_STRUCT* outputDataStruct)
{
   T_SHARED_DATA_STRUCT* internalDataStruct;
   TLV_TREE_NODE currentTlvTag;
   unsigned long tag, length;
   int result = FALSE;
   int cr = STATUS_SHARED_EXCHANGE_ERROR;

   // Create an internal data structure to create the torn transaction record
   internalDataStruct = GTL_SharedExchange_InitLocal (__APCLESS_PAYPASS_TORN_RECORD_MAX_SIZE);

   if((internalDataStruct != NULL) && (tlvRecord != NULL))
   {
      // Add each tag of the stored record in the data structure

      currentTlvTag = TlvTree_GetFirstChild(tlvRecord);

      while(currentTlvTag != NULL)
      {
         tag = TlvTree_GetTag(currentTlvTag);
         length = TlvTree_GetLength(currentTlvTag);

         // Add the tag in the internal structure to create the record.
         cr = GTL_SharedExchange_AddTag (internalDataStruct, tag, length, TlvTree_GetData(currentTlvTag));
         if (cr != STATUS_SHARED_EXCHANGE_OK)
         {
            result = FALSE;
            break;
         }

         // Get the next tag in the record
         currentTlvTag = TlvTree_GetNext(currentTlvTag);
      }

      if(cr == STATUS_SHARED_EXCHANGE_OK) // At least one tag has been added to the internal data structure (record is not empty)
      {
         // Torn transaction record is constructed, add it to the output buffer
         if (GTL_SharedExchange_AddTag (outputDataStruct, recordTag, internalDataStruct->ulDataLength, internalDataStruct->nPtrData) == STATUS_SHARED_EXCHANGE_OK)
         {
            result = TRUE;
         }
         else
         {
            result = FALSE;
         }
      }

      // Free the allocated buffer
      GTL_SharedExchange_DestroyLocal (internalDataStruct);
   }

   return result;
}


/**
 * Remove the given record from the torn transaction log.
 * @param[in] treeRecord TLV Record to remove.
 *     - TRUE if the record has been correctly removed
 *     - FALSE else.
 */
static int __APCLESS_PayPassTorn_RemoveRecordFromLog(TLV_TREE_NODE *treeRecord)
{
   if (treeRecord != NULL)
   {
      if (*treeRecord != NULL)
      {
         TlvTree_Release(*treeRecord);
         *treeRecord = NULL;
         return TRUE;
      }
   }

   return FALSE;
}


/**
 * Check if the current transaction is a torn transaction (if it appears in the torn transaction log).
 * @param[in,out] sharedDataStruct Shared buffer filled with the transaction information (PAN, PAN sequence number...).
 *                           Output buffer is filled with the torn record in the case of a torn transaction.
 * @return
 *     - TRUE if the transaction is in the torn transaction log, FALSE else.
 */
int APCLESS_PayPassTorn_IsTornTxn(T_SHARED_DATA_STRUCT* sharedDataStruct)
{
   int position;
   const unsigned char* pan = NULL;
   const unsigned char* panSeqNb = NULL;
   unsigned long panLength = 0;
   unsigned long panSeqNbLength = 0;
   unsigned char* value = NULL;
   unsigned int valueLength;
   int nbRecords;
   int recordIdx;
   int isTornTransaction;
   TLV_TREE_NODE tlvRecord;
   TLV_TREE_NODE tlvNode;


   isTornTransaction = FALSE;

   // Init the variable that identify a torn record during a transaction
   if (__APCLESS_PayPassTorn_record != NULL)
      __APCLESS_PayPassTorn_record = NULL;

   // Get the PAN
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext (sharedDataStruct, &position, TAG_EMV_APPLI_PAN, &panLength, &pan) != STATUS_SHARED_EXCHANGE_OK)
   {
      // Pan is missing, we cannot check the Torn Transaction List
      return FALSE;
   }

   // Get the PAN Sequence Number
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext (sharedDataStruct, &position, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, &panSeqNbLength, &panSeqNb) != STATUS_SHARED_EXCHANGE_OK)
   {
      // Pan Sequence Number is not present
      panSeqNb = NULL;
   }

   // Clear the output structure and fill it with the torn transaction record in the case of a torn transaction.
   GTL_SharedExchange_ClearEx (sharedDataStruct, FALSE);

   // Check torn transaction log presence
   if(__APCLESS_PayPassTorn_transactionLog != NULL)
   {
      // Get the number of torn records stored in the log.
      nbRecords = APCLESS_PayPassTorn_GetNumberOfTornTxnLogRecords();

      // For every record in torn transaction log, check for a matching entry (i.e. entry with the same PAN and same PAN Sequence Number)
      for(recordIdx = nbRecords; recordIdx > 0; recordIdx--) // Search starts from the most recent record
      {
         tlvRecord = __APCLESS_PayPassTorn_GetRecord(recordIdx);

         if (tlvRecord != NULL)
         {
            // Get the PAN in the record
            tlvNode = TlvTree_Find(tlvRecord, TAG_EMV_APPLI_PAN, 0);

            if (tlvNode != NULL)
            {
               value = TlvTree_GetData(tlvNode);
               valueLength = TlvTree_GetLength(tlvNode);
               if((valueLength == panLength) && (memcmp(value, pan, panLength) == 0))
               {
                  // Same PAN
                  // Check if PAN Sequence Number is the same (if available)
                  tlvNode = TlvTree_Find(tlvRecord, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, 0);

                  if ((tlvNode != NULL) && (panSeqNb != NULL))
                  {
                     value = TlvTree_GetData(tlvNode);
                     valueLength = TlvTree_GetLength(tlvNode);
                     if((valueLength == panSeqNbLength) && (memcmp (value, panSeqNb, panSeqNbLength) == 0))
                     {
                        // Record with the same PAN and same PAN Sequence Number.
                        isTornTransaction = TRUE;
                     }
                  }
                  if ((tlvNode == NULL) && (panSeqNb == NULL))
                  {
                     // Record with the same PAN (PAN Sequence Number not present)..
                     isTornTransaction = TRUE;
                  }

                  if(isTornTransaction)
                  {
                     // Copy the record in the exchange buffer to indicate PayPass kernel it is a torn transaction.
                     __APCLESS_PayPassTorn_record = tlvRecord;
                     return __APCLESS_PayPassTorn_CopyRecordInSharedBuffer(TAG_PAYPASS_TORN_RECORD, tlvRecord, sharedDataStruct);
                  }
               }
            }
         }
      }
   }

   return FALSE;
}


/**
 * Update the torn transaction log by adding a new record according to its date and time.
 * @param[in,out] recordDataStruct Shared buffer filled with the transaction data that must be added in a new record.
 * @return
 *     - TRUE if the record has been correctly added in the torn transaction log, FALSE else.
 */
static int __APCLESS_PayPassTorn_AddRecordByDate (T_SHARED_DATA_STRUCT* recordDataStruct)
{
   int position;
   const unsigned char *date, *time;
   unsigned char *recordDate, *recordTime;
   unsigned long dateLength, timeLength;
   TLV_TREE_NODE tlvTempTornLog, tlvRecord, tlvTmp;
   unsigned long ulDate, ulRecordDate, ulTime, ulRecordTime;
   int addRecord;


   // Get the date of the record to add
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext (recordDataStruct, &position, TAG_EMV_TRANSACTION_DATE, &dateLength, &date) != STATUS_SHARED_EXCHANGE_OK)
   {
      // Date is missing in the record to add
      return FALSE;
   }

   // Get the time of the record to add
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext (recordDataStruct, &position, TAG_EMV_TRANSACTION_TIME, &timeLength, &time) != STATUS_SHARED_EXCHANGE_OK)
   {
      // Time is missing in the record to add
      return FALSE;
   }

   // Create a temp torn log
   tlvTempTornLog = TlvTree_New(0);
   if (tlvTempTornLog == NULL)
   {
      return FALSE;
   }

   // New record has not been added yet
   addRecord = FALSE;

   // Check were the new record must be inserted by comparing its date/time with each record in the torn transaction log
   tlvRecord = TlvTree_GetFirstChild(__APCLESS_PayPassTorn_transactionLog);

   while (tlvRecord != NULL)
   {
      // If the new record has not been added yet, check its date and time
      if(!addRecord)
      {
         // Get the Date in the record
         tlvTmp = TlvTree_Find(tlvRecord, TAG_EMV_TRANSACTION_DATE, 0);
         if (tlvTmp != NULL)
         {
            recordDate = TlvTree_GetData(tlvTmp);
         }
         else
         {
            return FALSE;
         }

         // Get the Time in the record
         tlvTmp = TlvTree_Find(tlvRecord, TAG_EMV_TRANSACTION_TIME, 0);
         if (tlvTmp != NULL)
         {
            recordTime = TlvTree_GetData(tlvTmp);
         }
         else
         {
            return FALSE;
         }

         // Convert the dates
         ulDate = __APCLESS_PayPassTorn_DateYYMMDDConvertToUl(date);
         ulRecordDate = __APCLESS_PayPassTorn_DateYYMMDDConvertToUl(recordDate);

         // Compare the dates
         if(ulDate == ulRecordDate)
         {
            // Convert the times
            ulTime = (time[0] << 16) + (time[1] << 8) + time[2];
            ulRecordTime = (recordTime[0] << 16) + (recordTime[1] << 8) + recordTime[2];

            if(ulTime < ulRecordTime)
            {
               // The record to add is older than the current record from the torn log. The new record must be inserted here in the torn log.
               addRecord = TRUE;
            }
         }
         else if(ulDate < ulRecordDate)
         {
            // The record to add is older than the current record from the torn log.  The new record must be inserted here in the torn log
            addRecord = TRUE;
         }

         if(addRecord)
         {
            // The new record is inserted in the torn log
            __APCLESS_PayPassTorn_CopyRecordInTornLog(recordDataStruct, tlvTempTornLog);
         }
      }

      // Copy the record
      tlvTmp = TlvTree_Copy(tlvRecord);
      if(tlvTmp == NULL)
      {
         return FALSE;
      }
      if(TlvTree_Graft(tlvTempTornLog, tlvTmp) != TLV_TREE_OK)
      {
         return FALSE;
      }

      // Get the next record of the torn log
      tlvRecord = TlvTree_GetNext(tlvRecord);
   }

   // If the new record has not been added yet, it is added at the end of the tree
   if(!addRecord)
      __APCLESS_PayPassTorn_CopyRecordInTornLog(recordDataStruct, tlvTempTornLog);

   // Update the torn transaction log
   TlvTree_Release(__APCLESS_PayPassTorn_transactionLog);
   __APCLESS_PayPassTorn_transactionLog = tlvTempTornLog;

   return TRUE;
}


/**
 * Add a new record in the torn transaction log.
 * @param[in] recordDataStruct Shared buffer filled with the transaction data that must be added in a new record.
 * @param[in,out] treeTornLog Torn transaction log to be updated.
 * @return
 *     - TRUE if the record has been correctly added in the torn transaction log, FALSE else.
 */
static int __APCLESS_PayPassTorn_CopyRecordInTornLog (T_SHARED_DATA_STRUCT* recordDataStruct, TLV_TREE_NODE treeTornLog)
{
   int position, result;
   TLV_TREE_NODE tlvNewRecord;
   unsigned long readTag;
   unsigned long readLength;
   unsigned char *readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Create a new record (add a child in the torn transaction log tree)
   tlvNewRecord = TlvTree_AddChild (treeTornLog, TAG_PAYPASS_TORN_RECORD, NULL, 0);
   if (tlvNewRecord == NULL)
   {
      return FALSE;
   }

   // Parse the structure that contains the record to add and store every tag in the new record
   do
   {
      // Try to get following tag.
      result = GTL_SharedExchange_GetNext (recordDataStruct, &position, &readTag, &readLength, (const unsigned char **)&readValue);

      if (result == STATUS_SHARED_EXCHANGE_OK) // If tag found
      {
         TlvTree_AddChild (tlvNewRecord, readTag, readValue, readLength);
      }
   } while (result == STATUS_SHARED_EXCHANGE_OK);

   return TRUE;
}


/**
 * Add the current transaction in a new record in the torn transaction log. Remove the oldest record if maximum number is exceeded.
 * @param[in,out] sharedDataStruct Shared buffer filled with the transaction record to add in the log (PAN, PAN sequence number....).
 *                           Output buffer is filled with the removed record if maximum number of record is exceeded.
 * @return
 *     - TRUE if the record has been correctly added in the torn transaction log, FALSE else.
 */
int APCLESS_PayPassTorn_AddRecord(T_SHARED_DATA_STRUCT* sharedDataStruct)
{
   int position;
   const unsigned char* record = NULL;
   unsigned long recordLength = 0;
   const unsigned char* doNotRemoveLog = NULL;
   unsigned long doNotRemoveLogLength = 0;
   int keepRecord = FALSE;
   T_SHARED_DATA_STRUCT dataStructure;
   TLV_TREE_NODE tlvOldRecord;


   // Kernel C2, S11.E12 (v2)
   // In the case of a recovered transaction that is torned for a second time, the old record must be removed before adding the new torn transaction record in the log.
   // This record shall not be removed if tag TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD is present and set to '01'
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext (sharedDataStruct, &position, TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD, &doNotRemoveLogLength, &doNotRemoveLog) == STATUS_SHARED_EXCHANGE_OK)
   {
      // TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD is present, check if value is '01'
      keepRecord = (doNotRemoveLogLength == 1) && (doNotRemoveLog[0] == 0x01);
   }

   if (!keepRecord)
   {
      APCLESS_PayPassTorn_RemoveRecord();
   }

   // Check torn transaction log presence
   if(__APCLESS_PayPassTorn_transactionLog == NULL)
   {
      // Create the Torn Transaction Log
      __APCLESS_PayPassTorn_transactionLog = TlvTree_New(0);
      if (__APCLESS_PayPassTorn_transactionLog == NULL)
      {
         return FALSE;
      }
   }

   // Get the Record to add in the torn transaction log
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext (sharedDataStruct, &position, TAG_PAYPASS_TORN_RECORD, &recordLength, &record) != STATUS_SHARED_EXCHANGE_OK)
   {
      // Torn record is missing for adding a new record in the torn transaction log
      return FALSE;
   }

   // Init a parsing structure to parse the torn transaction record
   GTL_SharedExchange_InitEx (&dataStructure, recordLength, recordLength, (unsigned char *)record);

   // Add the record in the torn transaction log according to its date and time
   __APCLESS_PayPassTorn_AddRecordByDate (&dataStructure);


   // The new record has been correctly added to the torn transaction log.
   // If adding this new record to the log means that an old record is removed (maximum number of torn transaction log records exceeded), then the old record is sent to the kernel (in the output structure).

   // Clear the output structure.
   GTL_SharedExchange_ClearEx (sharedDataStruct, FALSE);

   // Check if maximum number of torn transaction log records exceeded
   if(APCLESS_PayPassTorn_GetNumberOfTornTxnLogRecords() > APCLESS_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS)
   {
      // Add the oldest record in the output structure
      tlvOldRecord = __APCLESS_PayPassTorn_GetRecord(1);
      if (tlvOldRecord != NULL)
         __APCLESS_PayPassTorn_CopyRecordInSharedBuffer(TAG_PAYPASS_OLD_TORN_RECORD, tlvOldRecord, sharedDataStruct);

      // Remove the oldest record from the torn transaction log
      __APCLESS_PayPassTorn_RemoveRecordFromLog(&tlvOldRecord);
   }

   return TRUE;
}


/**
 * Remove the current transaction record from the torn transaction log.
 * @return
 *     - TRUE if the record has been correctly removed from the torn transaction log, FALSE else.
 */
int APCLESS_PayPassTorn_RemoveRecord(void)
{
   return __APCLESS_PayPassTorn_RemoveRecordFromLog(&__APCLESS_PayPassTorn_record);
}


/**
 * Clean up the Torn Transaction log by removing torn transaction that were not recovered and that have been aged off the log.
 * @param[in] pCurrentDate Date to be compared with the date in a record.
 * @param[in] nlLifeTime Maximum time, in seconds, that a record can remain in the Torn Transaction Log.
 * @return
 *     - TRUE a aged off record has been removed from the torn transaction log, FALSE else.
 */
static int __APCLESS_PayPassTorn_CleanOldRecord (DATE *currentDate, int lifeTime)
{
   TLV_TREE_NODE tlvRecord, tlvTmp;
   unsigned char *date, *time;
   unsigned int dateLength, timeLength;
   DATE recordDate;
   int timeGap, dayGap, gapInSeconds;
   T_SHARED_DATA_STRUCT *outputTransactionDataStruct, *oldRecordDataStruct;
   int cr, isOldRecordRemoved;
   unsigned char payPassOutcomeParameterSet[]={PAYPASS_OPS_STATUS_END_APPLICATION,
                                     PAYPASS_OPS_START_NA,
                                     PAYPASS_OPS_ONLINE_RESPONSE_DATA_NA,
                                     PAYPASS_OPS_CVM_NA,
                                     PAYPASS_OPS_DATA_PRESENCE_MASK_DISCRET_DATA,
                                     PAYPASS_OPS_ALTERNATIVE_INTERFACE_PREF_NA,
                                     PAYPASS_OPS_FIELD_OFF_REQUEST_NA,
                                     0};

   isOldRecordRemoved = FALSE;

   // Create internal data structures that will contain the OUT signals (OPS and discretionary data)
   // The OUT signals are generated like the kernel
   outputTransactionDataStruct = GTL_SharedExchange_InitLocal (__APCLESS_PAYPASS_TORN_RECORD_MAX_SIZE + PAYPASS_OPS_LENGTH);
   oldRecordDataStruct = GTL_SharedExchange_InitLocal (__APCLESS_PAYPASS_TORN_RECORD_MAX_SIZE);
   if((outputTransactionDataStruct == NULL) || (oldRecordDataStruct == NULL))
   {
      goto End;
   }

   if(__APCLESS_PayPassTorn_transactionLog != NULL)
   {
      // Get the first record of the log
      tlvRecord = TlvTree_GetFirstChild(__APCLESS_PayPassTorn_transactionLog);

      if (tlvRecord != NULL)
      {
         // Get the Date in the record
         tlvTmp = TlvTree_Find(tlvRecord, TAG_EMV_TRANSACTION_DATE, 0);
         if (tlvTmp != NULL)
         {
            date = TlvTree_GetData(tlvTmp);
            dateLength = TlvTree_GetLength(tlvTmp);
         }
         else
         {
            goto End;
         }

         // Get the Time in the record
         tlvTmp = TlvTree_Find(tlvRecord, TAG_EMV_TRANSACTION_TIME, 0);
         if (tlvTmp != NULL)
         {
            time = TlvTree_GetData(tlvTmp);
            timeLength = TlvTree_GetLength(tlvTmp);
         }
         else
         {
            goto End;
         }

         // Copy the current transaction Date/Time in a DATE structure
         recordDate.year[0]=(date[0]/16) + '0';
         recordDate.year[1]=(date[0]%16) + '0';
         recordDate.month[0]=(date[1]/16) + '0';
         recordDate.month[1]=(date[1]%16) + '0';
         recordDate.day[0]=(date[2]/16) + '0';
         recordDate.day[1]=(date[2]%16) + '0';
         recordDate.hour[0]=(time[0]/16) + '0';
         recordDate.hour[1]=(time[0]%16) + '0';
         recordDate.minute[0]=(time[1]/16) + '0';
         recordDate.minute[1]=(time[1]%16) + '0';
         recordDate.second[0]=(time[2]/16) + '0';
         recordDate.second[1]=(time[2]%16) + '0';


         // Get the number of days between the two dates.
         dayGap = APCLESS_Tools_NumberOfDaysBetweenTwoDates (&recordDate, currentDate);
         // Get the number of seconds between the two dates.
         timeGap = SLSQ_Ecart_heure_minute_seconde(&recordDate, currentDate);

         if(dayGap >= 0)
         {
            gapInSeconds = (dayGap*24*3600) + timeGap ;

            if(gapInSeconds > lifeTime)
            {
               // The record must be removed from the torn transaction log.

               // Copy the content of the old record in the TAG_PAYPASS_TORN_RECORD_IN_DISCRETIONARY_DATA tag
               __APCLESS_PayPassTorn_CopyRecordInSharedBuffer(TAG_PAYPASS_TORN_RECORD_IN_DISCRETIONARY_DATA, tlvRecord, oldRecordDataStruct);

               // Remove the old record from the torn transaction log
               __APCLESS_PayPassTorn_RemoveRecordFromLog(&tlvRecord);

               isOldRecordRemoved = TRUE;
            }
         }
      }
   }

   // Set the outcome parameter set
   cr = GTL_SharedExchange_AddTag (outputTransactionDataStruct, TAG_PAYPASS_OUTCOME_PARAMETER_SET, PAYPASS_OPS_LENGTH, payPassOutcomeParameterSet);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Add the old record in the discretionnary data
   cr = GTL_SharedExchange_AddTag (outputTransactionDataStruct, TAG_PAYPASS_DISCRETIONARY_DATA, oldRecordDataStruct->ulDataLength, oldRecordDataStruct->nPtrData);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // TODO: If necessary, send the result (outputTransactionDataStruct)

End:
   // Free the allocated buffers
   if(outputTransactionDataStruct != NULL)
      GTL_SharedExchange_DestroyLocal(outputTransactionDataStruct);
   if(oldRecordDataStruct != NULL)
      GTL_SharedExchange_DestroyLocal(oldRecordDataStruct);

   if(isOldRecordRemoved)
      return TRUE;
   else
      return FALSE;
}


/**
 * Clean up the Torn Transaction log by removing torn records that were not recovered and that have been aged off the log.
 */
void APCLESS_PayPassTorn_CleanLog(void)
{
   DATE currentDate;
   unsigned long lifeTime;
   int result;

   // Read the current date and time
   if (read_date(&currentDate) != OK)
      return;

   // TODO: Get the maximum time, in seconds, that a record can remain in the Torn Transaction Log (from the application parameter)
   // or set to the default value
   lifeTime = __APCLESS_PAYPASS_TORN_RECORD_LIFETIME_DEFAULT;   // 300 seconds

   // Remove each record that has been aged off
   do
   {
      result = __APCLESS_PayPassTorn_CleanOldRecord(&currentDate, (int) lifeTime);
   }while(result);
}

#endif //PAYPASS_TORN


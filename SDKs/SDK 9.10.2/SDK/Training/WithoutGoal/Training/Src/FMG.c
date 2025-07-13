//****************************************************************************
//       INGENICO                                INGEDEV 7                  
//============================================================================
//       FILE  FMG.C                            (Copyright INGENICO 2009)   
//============================================================================
//  Created :       22-May-2009     Kassovic                                 
//  Last modified : 22-May-2009     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  File Management (FMG):
//       FMG provides a high level of services allowing the applications to 
//       save files in the flash memory easily.
//       Show how to create a disk and open a file for writing and reading 
//       inside the flash.
//                                                                            
//  List of routines in file :  
//      FMGCreateBatch : Create FMG0161 disk and BATCH file.
//      FMGDeleteBatch : Delete BATCH file.
//      GetBatchIdx : Retrieve transaction's index from BATCH file.
//      SetBatchIdx : Update transaction's index into BATCH file.
//      FMGAddDelTransactions : Add/Delete transactions from BATCH file.
//      FMGReadTransactions : Read transactions from BATCH file.
//                            
//  File history :
//  220509-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "VGE_FMG.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxKbd;      // Peripheral file Keyboard

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define MAX_TRANS 10

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
// Transaction info
// ================
typedef struct stTransac
{
	char tcInvoice[6+1];           // Invoice number
	char tcDate[14+1];             // Date and Time
	char tcAccount[16+1];          // Account
	char tcAmount[15+1];           // Amount
	char tcType[11+1];             // Transaction type
} ST_TRANSAC;

// Batch
// =====
typedef struct stBatch
{
	int iBatIdx;               // Batch index
	ST_TRANSAC txTable[10];    // Table of transactions
} ST_BATCH;

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Batch contain to transfer into data file system (using FMG Library)
// ===================================================================
static const ST_BATCH zBatch = { 
	0,                                                                                         // Batch index
	{
		{ "835302", "04/08/09 09:34", "4972037641051717", "EUR       10.00", "CREDIT VISA" },  // Transaction 1
		{ "394182", "04/08/09 09:46", "373235587881007 ", "EUR      145.45", "DEBIT  AMEX" },  // Transaction 2
		{ "724104", "04/08/09 10:15", "4926925476062867", "EUR     1837.56", "DEBIT  VISA" },  // Transaction 3
		{ "927519", "04/08/09 10:59", "373958451209674 ", "EUR    11945.67", "DEBIT  AMEX" },  // Transaction 4
		{ "510328", "04/08/09 11:38", "4983610857894520", "EUR      154.98", "CREDIT VISA" },  // Transaction 5
		{ "621739", "04/08/09 11:49", "376207852407529 ", "EUR     1598.74", "DEBIT  AMEX" },  // Transaction 6
		{ "185293", "04/08/09 12:12", "4906835286709654", "EUR       12.89", "CREDIT VISA" },  // Transaction 7
		{ "031046", "04/08/09 14:23", "377895395286349 ", "EUR      136.78", "DEBIT  AMEX" },  // Transaction 8
		{ "263847", "04/08/09 14:49", "4983751970584978", "EUR     1947.65", "DEBIT  VISA" },  // Transaction 9
		{ "103657", "04/08/09 15:37", "377306983460698 ", "EUR        5.00", "CREDIT AMEX" }   // Transaction 10
	}
};

static FMG_t_file_info xFileInfo;

//****************************************************************************
//                       void FMGCreateBatch (void)                            
//  This function creates FMG0161 disk and the BATCH file. 
//  !!! FMG_Init() must be done in after_reset() to initialize the file
//  management at each power-on.
//       FMG_Init() : File management initialization.
//       FMG_CreateFileType() : FMG0161 disk + BATCH file creation.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FMGCreateBatch(void)
{
	// Local variables 
    // ***************
    int iRet;

	// FMG0161 Disk + BATCH File creation
    // **********************************
	_clrscr();                                                    // Clear screen
    iRet = FMG_CreateFileType(FMGBatch, FMG_VARIABLE_LENGTH, FMG_WITH_CKECKSUM); 
    CHECK((iRet==FMG_SUCCESS)||(iRet==FMG_FILE_ALREADY_EXIST), lblFmgKO);
	
    if (iRet == FMG_SUCCESS)
    {
    	DisplayMedium(0, 0, "Batch Created");                     // Display Msg
    	xFileInfo.eCreationType = FMGFileType;                    // Creation file => File Type 
        xFileInfo.eFileType = FMGBatch;                           // File Type = BATCH file        
    	iRet = FMG_AddRecord(&xFileInfo, (void*) &zBatch.iBatIdx, sizeof(int), FMGBegin, 0); CHECK(iRet==FMG_SUCCESS, lblFmgKO);
    }
    else
    	DisplayMedium(0, 0, "Already Exist");                     // Display Msg
    ttestall(0, 3*100);                                           // Delay 3s      

    goto lblEnd;
    
	// Errors treatment 
    // ****************
lblFmgKO:                                                         // File Management error    
    _clrscr();                                                    // Clear screen
    DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                      // Oops! error
    ttestall(0,5*100);                                            // Delay 5s     
lblEnd:
    return;
}

//****************************************************************************
//                       void FMGDeleteBatch (void)                            
//  This function deletes the BATCH file. 
//       FMG_DeleteFileType() : BATCH file deletion.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FMGDeleteBatch(void)
{
	// Local variables 
    // ***************
    int iRet;

    // BATCH File deletion
    // *******************
	_clrscr();                                                    // Clear screen
    iRet = FMG_DeleteFileType(FMGBatch); 
    CHECK(iRet==FMG_SUCCESS, lblFmgKO);

    DisplayMedium(0, 0, "Batch Deleted");                         // Display Msg
    ttestall(0, 3*100);                                           // Delay 3s      

    goto lblEnd;
    
	// Errors treatment 
    // ****************
lblFmgKO:                                                         // File Management error    
    _clrscr();                                                    // Clear screen
    DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                      // Oops! error
    ttestall(0,5*100);                                            // Delay 5s     
lblEnd:
    return;
}

//****************************************************************************
//                   int GetBatchIdx (void)                            
//  This function retrieves the transaction's index from the BATCH file. 
//       FMG_ReadRecord() : Read the transaction's index.
//  This function has no parameters.
//  This function has return value.
//    >=0 : Return transaction's index.
//    <0  : Batch error.
//****************************************************************************

static int GetBatchIdx(void)
{
	// Local variables 
    // ***************
	long lLength;
    int iRet, iBatchIdx;
	
    // Retrieve Idx from BATCH file
    // ****************************
    lLength = sizeof(int);    
	xFileInfo.eCreationType = FMGFileType;                     // Creation file => File Type 
    xFileInfo.eFileType = FMGBatch;                            // File Type = BATCH file
    iRet = FMG_ReadRecord(&xFileInfo, &iBatchIdx, &lLength, FMGBegin, 0);
	if (iRet == FMG_SUCCESS)
		iRet = iBatchIdx;                                      // Read Batch Index (Transactions available)
	else if (iRet == FMG_READ_RECORD_ERROR)
		iRet = 0;                                              // Reset Batch Index (No transaction)
	else
		iRet = -1;                                             // Batch error
	
    return iRet;
}

//****************************************************************************
//                   int SetBatchIdx (void)                            
//  This function updates the transaction's index into the BATCH file. 
//       FMG_ModifyRecord() : Update the transaction's index.
//  This function has no parameters.
//  This function has return value.
//    FMG_SUCCESS : Transaction's index updated.
//    Others  : Batch error.
//****************************************************************************

static int SetBatchIdx(int iBatchIdx)
{
	// Local variables 
    // ***************
	int iRet;
	
	// Update and store Idx into BATCH file
	// ************************************
	xFileInfo.eCreationType = FMGFileType;                     // Creation file => File Type 
    xFileInfo.eFileType = FMGBatch;                            // File Type = BATCH file    
	iRet = FMG_ModifyRecord(&xFileInfo, &iBatchIdx, sizeof(int), FMGBegin, 0);	        	
	if (iRet == FMG_READ_RECORD_ERROR)                         // No more first record       
		iRet = FMG_SUCCESS;                                                                        
	
    return iRet;
}

//****************************************************************************
//                   void FMGAddDelTransactions (void)                            
//  This function adds a transaction into the BATCH when pressing Up key.
//  This function deletes a transaction from the BATCH when pressing Down key.
//       FMG_AddRecord() : Add a transaction.
//       FMG_DeleteRecord() : Delete a transaction.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FMGAddDelTransactions(void) 
{
	// Local variables 
    // ***************
	char tcDisplay[25+1];
    char cKey;
    int iRet, iBatchIdx;

    // Batch management
	// ****************
	_clrscr();                                                                     // Clear screen
    iBatchIdx = GetBatchIdx(); CHECK(iBatchIdx>=0, lblKO);                         // Read Batch Index
	DisplaySmall(0, 16, "UP to add");
	if (iBatchIdx == 0)
		DisplaySmall(4, 0, "Batch Empty !!!");
	if (iBatchIdx == MAX_TRANS)
		DisplaySmall(4, 0, "Batch Full !!!");
	DisplaySmall(7, 14, "DOWN to del");

	reset_buf(pxKbd, _receive_id);                                                 // Reset keyboard FIFO
    while(1) 
	{
        cKey=0;
		iRet = ttestall(KEYBOARD, 30*100);                                         // Wait for a key pressed or a timeout
		if (iRet & KEYBOARD)                                                       // Key detected
			cKey = getchar();                                                      // Retrieve key pressed
      
		// Exit from the batch
		// ===================
        if(!cKey)
            break;                                                                 // Exit loop if nothing is pressed during 5s
        if((cKey == T_ANN) || (cKey ==T_VAL))
            break;                                                                 // Exit loop if red or green key is pressed

        
        // Add transactions into the batch
        // ===============================
		if ((cKey==T_SKHAUT) || (cKey==T_SK4))                                     // Key UP
		{
			if (iBatchIdx < MAX_TRANS)                                             // Add transaction
			{        
	        	iRet = FMG_AddRecord(&xFileInfo, (void*) &zBatch.txTable[iBatchIdx], sizeof(ST_TRANSAC), FMGMiddle, iBatchIdx+1); CHECK(iRet==FMG_SUCCESS, lblFmgKO);
	        	iBatchIdx++;                                                       // Inc Batch Index
	        	iRet = SetBatchIdx(iBatchIdx); CHECK(iRet==FMG_SUCCESS, lblFmgKO); // Save Batch Index  
	        	sprintf(tcDisplay, "Transaction %d recorded", iBatchIdx);          // Transaction recorded
	        	DisplaySmall(3, 0, tcDisplay);
	        	DisplaySmall(4, 0, "                         ");
	            if ((iBatchIdx > MAX_TRANS-3) && (iBatchIdx != MAX_TRANS))         // Batch almost full
	            	DisplaySmall(4, 0, "Batch almost Full !!!    ");
	            if (iBatchIdx == MAX_TRANS)                                        // Batch full
					DisplaySmall(4, 0, "Batch Full !!!           ");
			}
		}
				
		// Delete transactions from the batch
		// ==================================
        if((cKey == T_SKBAS) || (cKey==T_SK3))                                     // Key DOWN
		{
        	if (iBatchIdx > 0)                                                     // Delete transaction
			{
				iBatchIdx--;                                                       // Dec Batch Index
	        	iRet = FMG_DeleteRecord(&xFileInfo, FMGMiddle, sizeof(ST_TRANSAC), iBatchIdx+1); CHECK(iRet==FMG_SUCCESS, lblFmgKO);
	        	iRet = SetBatchIdx(iBatchIdx); CHECK(iRet==FMG_SUCCESS, lblFmgKO); // Save Batch Index  
	        	sprintf(tcDisplay, "Transaction %d deleted ", iBatchIdx+1);        // Transaction deleted
	        	DisplaySmall(3, 0, tcDisplay);
	        	DisplaySmall(4, 0, "                         ");
	            if (iBatchIdx == 0)                                                // Batch empty
					DisplaySmall(4, 0, "Batch Empty !!!          ");
			}
		}
    }
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                                     // Clear screen
	DisplayMedium(0, 0, "Processing Error");                                       // Oops! error
    ttestall(0, 5*100);                                                            // Delay 5s 
    goto lblEnd;
lblFmgKO:                                                                          // File Management error    
    _clrscr();                                                                     // Clear screen
    DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                                       // Oops! error
    ttestall(0,5*100);                                                             // Delay 5s     
lblEnd: 
    return;
}
	
//****************************************************************************
//                     void FMGReadTransactions (void)                            
//  This function scrolls the transactions from the BATCH file.
//       FMG_ReadRecord() : Read a transaction.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FMGReadTransactions(void) 
{
	// Local variables 
    // ***************
    char cKey;
    char tcDisplay[25+1];
    ST_TRANSAC xTransac;
    long lLength;
	int iRet, iBatchIdx, iIdx;

    // Batch management
	// ****************
	_clrscr();                                                 // Clear screen
	memset(&xTransac, 0, sizeof(ST_TRANSAC));
    iIdx=1;                                                    // Transactions start at iIdx=1
		
    // Read first transaction
    // ======================
    iBatchIdx = GetBatchIdx(); CHECK(iBatchIdx>=0, lblKO);     // Read Batch Index    
	CHECK(iBatchIdx!=0, lblEmpty);                             // Check if batch empty
    DisplaySmall(0, 23, "UP");                                 // Display first transaction
    lLength = sizeof(ST_TRANSAC);
	iRet = FMG_ReadRecord(&xFileInfo, &xTransac, &lLength, FMGMiddle, iIdx); CHECK(iRet==FMG_SUCCESS, lblFmgKO);	
    sprintf(tcDisplay, "TRANSACTION %02d", iIdx);
	DisplaySmall(1, 4, tcDisplay);
    sprintf(tcDisplay, "INV #: %s", xTransac.tcInvoice);
    DisplaySmall(2, 0, tcDisplay);
    sprintf(tcDisplay, "DATE : %s", xTransac.tcDate);
    DisplaySmall(3, 0, tcDisplay);
    sprintf(tcDisplay, "ACC #: %s", xTransac.tcAccount);
    DisplaySmall(4, 0, tcDisplay);
    sprintf(tcDisplay, "AMT  : %s", xTransac.tcAmount);
    DisplaySmall(5, 0, tcDisplay);
    sprintf(tcDisplay, "TYPE : %s", xTransac.tcType);
    DisplaySmall(6, 0, tcDisplay);
    DisplaySmall(7, 21, "DOWN");

	// Scroll next transactions
	// ========================	                   
	reset_buf(pxKbd, _receive_id);                             // Reset keyboard FIFO
    while(1) 
	{
        cKey=0;
		iRet = ttestall(KEYBOARD, 30*100);                     // Wait for a key pressed or a timeout
		if (iRet & KEYBOARD)                                   // Key detected
			cKey = getchar();                                  // Retrieve key pressed
      
		// Exit from batch
		// ---------------
        if(!cKey)
            break;                                             // Exit loop if nothing is pressed during 5s
        if((cKey == T_ANN) || (cKey == T_VAL))
            break;                                             // Exit loop if red or green key is pressed
       
        // Scrolling UP transactions
        // -------------------------
		if ((cKey==T_SKHAUT) || (cKey==T_SK4))                 // Key UP
		{
			if (iIdx < iBatchIdx)                              // Reading transactions UP
			{         
				iIdx++;
		        lLength = sizeof(ST_TRANSAC);
		    	iRet = FMG_ReadRecord(&xFileInfo, &xTransac, &lLength, FMGMiddle, iIdx); CHECK(iRet==FMG_SUCCESS, lblFmgKO);
		        sprintf(tcDisplay, "TRANSACTION %02d", iIdx);
		    	DisplaySmall(1, 4, tcDisplay);
		        sprintf(tcDisplay, "INV #: %s", xTransac.tcInvoice);
		        DisplaySmall(2, 0, tcDisplay);
		        sprintf(tcDisplay, "DATE : %s", xTransac.tcDate);
		        DisplaySmall(3, 0, tcDisplay);
		        sprintf(tcDisplay, "ACC #: %s", xTransac.tcAccount);
		        DisplaySmall(4, 0, tcDisplay);
		        sprintf(tcDisplay, "AMT  : %s", xTransac.tcAmount);
		        DisplaySmall(5, 0, tcDisplay);
		        sprintf(tcDisplay, "TYPE : %s", xTransac.tcType);
		        DisplaySmall(6, 0, tcDisplay);
			}
		}
				
		// Scrolling DOWN transactions
		// ---------------------------
        if((cKey ==T_SKBAS) || (cKey==T_SK3))                  // Key DOWN
		{
        	if (iIdx > 1)                                      // Reading transaction DOWN
			{
				iIdx--;
		        lLength = sizeof(ST_TRANSAC);
		    	iRet = FMG_ReadRecord(&xFileInfo, &xTransac, &lLength, FMGMiddle, iIdx); CHECK(iRet==FMG_SUCCESS, lblFmgKO);
		        sprintf(tcDisplay, "TRANSACTION %02d", iIdx);
		    	DisplaySmall(1, 4, tcDisplay);
		        sprintf(tcDisplay, "INV #: %s", xTransac.tcInvoice);
		        DisplaySmall(2, 0, tcDisplay);
		        sprintf(tcDisplay, "DATE : %s", xTransac.tcDate);
		        DisplaySmall(3, 0, tcDisplay);
		        sprintf(tcDisplay, "ACC #: %s", xTransac.tcAccount);
		        DisplaySmall(4, 0, tcDisplay);
		        sprintf(tcDisplay, "AMT  : %s", xTransac.tcAmount);
		        DisplaySmall(5, 0, tcDisplay);
		        sprintf(tcDisplay, "TYPE : %s", xTransac.tcType);
		        DisplaySmall(6, 0, tcDisplay);
			}
		}
    }
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                 // Clear screen
	DisplayMedium(0, 0, "Processing Error");                   // Oops! error
    ttestall(0, 5*100);                                        // Delay 5s 
    goto lblEnd;
lblEmpty:                                                      // Batch file empty
    _clrscr();                                                 // Clear screen
    DisplayMedium(0, 0, "Batch Empty !!!");                    // Oops! error
    ttestall(0, 5*100);                                        // Delay 5s
    goto lblEnd;
lblFmgKO:                                                      // File Management error    
    _clrscr();                                                 // Clear screen
    DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                   // Oops! error
    ttestall(0,5*100);                                         // Delay 5s     
lblEnd: 
    return;
}
	
	


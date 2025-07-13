//****************************************************************************
//       INGENICO                                INGEDEV 7                  
//============================================================================
//       FILE  FMG.C                             (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                       *** File Management (FMG) ***
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
//  071312-BK : File created
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
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

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
	char tcDate[16+1];             // Date and Time
	char tcAccount[16+1];          // Account
	char tcAmount[15+1];           // Amount
	char tcType[13+1];             // Transaction type
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
// Properties of the Batch screen (Goal)
// =====================================
static const ST_DSP_LINE txBatch[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE, GL_COLOR_GREEN, 25, TRUE,  {2, 2, 2, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 2, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  TRUE,   44, TRUE,  {0, 2, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 1, 2, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_RED,  100, FALSE, {0, 2, 0, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE, 100, FALSE, {0, 2, 0, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE, GL_COLOR_GREEN, 25, TRUE,  {2, 2, 2, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 3, 2}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  TRUE,   44, TRUE,  {0, 2, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 2, 1}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} }
};

// Properties of the Trans screen (Goal)
// =====================================
static const ST_DSP_LINE txTrans[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE,  GL_COLOR_GREEN,  25, TRUE,  {2, 2, 2, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 2, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  TRUE,   44, TRUE,  {0, 2, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 1, 2, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_YELLOW, GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line2
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line4
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line5
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line6
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE,  GL_COLOR_GREEN,  25, TRUE,  {2, 2, 2, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 3, 2}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line7
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  TRUE,   44, TRUE,  {0, 2, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 2, 1}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} }
};

// Batch contain to transfer into data file system (using FMG Library)
// ===================================================================
static const ST_BATCH zBatch = { 
	0,                                                                               // Batch index
	{
		{ "04/08/09   09:34", "4972037641051717", "EUR       10.00", "CREDIT   VISA" },  // Transaction 1
		{ "04/08/09   09:46", "373235587881007 ", "EUR      145.45", "DEBIT    AMEX" },  // Transaction 2
		{ "04/08/09   10:15", "4926925476062867", "EUR     1837.56", "DEBIT    VISA" },  // Transaction 3
		{ "04/08/09   10:59", "373958451209674 ", "EUR    11945.67", "DEBIT    AMEX" },  // Transaction 4
		{ "04/08/09   11:38", "4983610857894520", "EUR      154.98", "CREDIT   VISA" },  // Transaction 5
		{ "04/08/09   11:49", "376207852407529 ", "EUR     1598.74", "DEBIT    AMEX" },  // Transaction 6
		{ "04/08/09   12:12", "4906835286709654", "EUR       12.89", "CREDIT   VISA" },  // Transaction 7
		{ "04/08/09   14:23", "377895395286349 ", "EUR      136.78", "DEBIT    AMEX" },  // Transaction 8
		{ "04/08/09   14:49", "4983751970584978", "EUR     1947.65", "DEBIT    VISA" },  // Transaction 9
		{ "04/08/09   15:37", "377306983460698 ", "EUR        5.00", "CREDIT   AMEX" }   // Transaction 10
	}
};

static FMG_t_file_info xFileInfo;

//****************************************************************************
//                       void FMGCreateBatch (void)                            
//  This function creates FMG0161 disk and the BATCH file. 
//  !!! FMG_Init() must be done in after_reset() to initialize the file
//  management at each power-on.
//   - FMG_Init() : File management initialization.
//   - FMG_CreateFileType() : FMG0161 disk + BATCH file creation.
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
    iRet = FMG_CreateFileType(FMGBatch, FMG_VARIABLE_LENGTH, FMG_WITH_CKECKSUM); 
    CHECK((iRet==FMG_SUCCESS)||(iRet==FMG_FILE_ALREADY_EXIST), lblFmgKO);
	
    if (iRet == FMG_SUCCESS)
    {
    	xFileInfo.eCreationType = FMGFileType;    // Creation file => File Type
        xFileInfo.eFileType = FMGBatch;           // File Type = BATCH file
    	iRet = FMG_AddRecord(&xFileInfo, (void*) &zBatch.iBatIdx, sizeof(int), FMGBegin, 0);
    	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
    	GL_Dialog_Message(xGoal, NULL, "Batch Created", GL_ICON_INFORMATION, GL_BUTTON_VALID, 3*1000);
    }
    else
    	GL_Dialog_Message(xGoal, NULL, "Batch\nAlready Created", GL_ICON_WARNING, GL_BUTTON_VALID, 3*1000);

    goto lblEnd;
    
	// Errors treatment 
    // ****************
lblFmgKO:                                         // File Management error
	GL_Dialog_Message(xGoal, NULL, FMG_ErrorMsg(iRet), GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	return;
}

//****************************************************************************
//                       void FMGDeleteBatch (void)                            
//  This function deletes the BATCH file. 
//   - FMG_DeleteFileType() : BATCH file deletion.
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
    iRet = FMG_DeleteFileType(FMGBatch); 
    CHECK(iRet==FMG_SUCCESS, lblFmgKO);
    GL_Dialog_Message(xGoal, NULL, "Batch Deleted", GL_ICON_INFORMATION, GL_BUTTON_VALID, 3*1000);

    goto lblEnd;
    
	// Errors treatment 
    // ****************
lblFmgKO:                                 // File Management error
	if (iRet == FMG_FILE_DOES_NOT_EXIST)
		GL_Dialog_Message(xGoal, NULL, "Batch\nAlready Deleted", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	else
		GL_Dialog_Message(xGoal, NULL, FMG_ErrorMsg(iRet), GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	return;
}

//****************************************************************************
//                   int GetBatchIdx (void)                            
//  This function retrieves the transaction's index from the BATCH file. 
//   - FMG_ReadRecord() : Read the transaction's index.
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
	xFileInfo.eCreationType = FMGFileType;  // Creation file => File Type
    xFileInfo.eFileType = FMGBatch;         // File Type = BATCH file
    iRet = FMG_ReadRecord(&xFileInfo, &iBatchIdx, &lLength, FMGBegin, 0);
	if (iRet == FMG_SUCCESS)
		iRet = iBatchIdx;                   // Read Batch Index (Transactions available)
	else if (iRet == FMG_READ_RECORD_ERROR)
		iRet = 0;                           // Reset Batch Index (No transaction)
	else
		iRet = -1;                          // Batch error
	
    return iRet;
}

//****************************************************************************
//                   int SetBatchIdx (void)                            
//  This function updates the transaction's index into the BATCH file. 
//   - FMG_ModifyRecord() : Update the transaction's index.
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
	xFileInfo.eCreationType = FMGFileType;  // Creation file => File Type
    xFileInfo.eFileType = FMGBatch;         // File Type = BATCH file
	iRet = FMG_ModifyRecord(&xFileInfo, &iBatchIdx, sizeof(int), FMGBegin, 0);	        	
	if (iRet == FMG_READ_RECORD_ERROR)      // No more first record
		iRet = FMG_SUCCESS;                                                                        
	
    return iRet;
}

//****************************************************************************
//                   void FMGAddDelTransactions (void)                            
//  This function adds a transaction into the BATCH when pressing Up key.
//  This function deletes a transaction from the BATCH when pressing Down key.
//   - FMG_AddRecord() : Add a transaction.
//   - FMG_DeleteRecord() : Delete a transaction.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FMGAddDelTransactions(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	char tcDisplay[50+1];
    int iKey, iRet, iBatchIdx;

    // Batch management
	// ****************
	xScreen = GoalCreateScreen(xGoal, txBatch, NUMBER_OF_LINES(txBatch), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                           // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_DOWN | KEY_UP, false);
	CHECK(iRet>=0, lblKO);

	iBatchIdx = GetBatchIdx();                                             // Read Batch Index
	CHECK(iBatchIdx>=0, lblKO);

    iRet = GoalDspLine(xScreen, 0, "Up to add", &txBatch[0], 0, false);
	CHECK(iRet>=0, lblKO);                                                 // Show transaction remaining
    sprintf(tcDisplay, "%d Transaction(s)", iBatchIdx);
	iRet = GoalDspLine(xScreen, 2, "", &txBatch[2], 0, false);
	CHECK(iRet>=0, lblKO);
	if (iBatchIdx == 0)
	{
	    memset(tcDisplay, 0, sizeof(tcDisplay));
		iRet = GoalDspLine(xScreen, 2, "Batch Empty !!!", &txBatch[2], 0, false);
		CHECK(iRet>=0, lblKO);                                             // Warm message = Batch empty
	}
	if (iBatchIdx == MAX_TRANS)
	{
		iRet = GoalDspLine(xScreen, 2, "Batch Full !!!", &txBatch[2], 0, false);
		CHECK(iRet>=0, lblKO);                                             // Warm message = Batch full
	}
   	iRet = GoalDspLine(xScreen, 3, "Down to del", &txBatch[3], 0, false);
    CHECK(iRet>=0, lblKO);

    while(1) 
	{
    	iRet = GoalDspLine(xScreen, 1, tcDisplay, &txBatch[1], 0, true);
    	CHECK(iRet>=0, lblKO);                                             // Show transaction recorded or deleted

		iKey = GoalGetKey(xScreen, xGoal, true, 30*1000, true);            // Wait for key pressed/touched (shortcut)

		// Exit from the batch
		// ===================
        if(iKey==0)
            break;                                                         // Exit loop if nothing is pressed during 5s
        if ((iKey==GL_KEY_CANCEL) || (iRet==GL_KEY_VALID))
            break;                                                         // Exit loop if red or green key is pressed

        // Add transactions into the batch
        // ===============================
        if (iKey==GL_KEY_UP)                                               // *** Key UP ***
		{
			if (iBatchIdx < MAX_TRANS)                                     // Add transaction
			{        
	        	iRet = FMG_AddRecord(&xFileInfo, (void*) &zBatch.txTable[iBatchIdx], sizeof(ST_TRANSAC), FMGMiddle, iBatchIdx+1);
	        	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
	        	iBatchIdx++;                                               // Inc Batch Index
	        	iRet = SetBatchIdx(iBatchIdx);                             // Save Batch Index
	        	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
	        	sprintf(tcDisplay, "Transaction %d recorded", iBatchIdx);  // Transaction recorded

	            if ((iBatchIdx > MAX_TRANS-3) && (iBatchIdx != MAX_TRANS)) // Batch almost full
	            {
		    		iRet = GoalDspLine(xScreen, 2, "Batch almost Full !!!", &txBatch[2], 0, false);
		    		CHECK(iRet>=0, lblKO);
	            }
	            else if (iBatchIdx == MAX_TRANS)                           // Batch full
	            {
			    	iRet = GoalDspLine(xScreen, 2, "Batch Full !!!", &txBatch[2], 0, false);
			    	CHECK(iRet>=0, lblKO);
			    	buzzer(10);
	            }
	            else
	            {
		    		iRet = GoalDspLine(xScreen, 2, "", &txBatch[2], 0, false);
		    		CHECK(iRet>=0, lblKO);
				}
			}
		}
				
		// Delete transactions from the batch
		// ==================================
		if (iKey==GL_KEY_DOWN)                                              // *** Key DOWN ***
		{
        	if (iBatchIdx > 0)                                              // Delete transaction
			{
				iBatchIdx--;                                                // Dec Batch Index
	        	iRet = FMG_DeleteRecord(&xFileInfo, FMGMiddle, sizeof(ST_TRANSAC), iBatchIdx+1);
	        	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
	        	iRet = SetBatchIdx(iBatchIdx);                              // Save Batch Index
	        	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
	        	sprintf(tcDisplay, "Transaction %d deleted", iBatchIdx+1);  // Transaction deleted

	    		iRet = GoalDspLine(xScreen, 2, "", &txBatch[2], 0, false);
	    		CHECK(iRet>=0, lblKO);

	            if (iBatchIdx == 0)                                         // Batch empty
	            {
		    		iRet = GoalDspLine(xScreen, 2, "Batch Empty !!!", &txBatch[2], 0, false);
		    		CHECK(iRet>=0, lblKO);
		    		buzzer(10);
	            }
			}
		}
    }
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFmgKO:                            // File Management error
	GL_Dialog_Message(xGoal, NULL, FMG_ErrorMsg(iRet), GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd: 
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}
	
//****************************************************************************
//                     void FMGReadTransactions (void)                            
//  This function scrolls the transactions from the BATCH file.
//   - FMG_ReadRecord() : Read a transaction.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FMGReadTransactions(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
    char tcDisplay[50+1];
    ST_TRANSAC xTransac;
    long lLength;
	int iKey, iRet, iBatchIdx, iIdx;

    // Batch management
	// ****************
	memset(&xTransac, 0, sizeof(ST_TRANSAC));
    iIdx=1;                                                    // Transactions start at iIdx=1

	xScreen = GoalCreateScreen(xGoal, txTrans, NUMBER_OF_LINES(txTrans), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                               // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_DOWN | KEY_UP, false);
	CHECK(iRet>=0, lblKO);

	// Read first transaction
    // ======================
    iBatchIdx = GetBatchIdx();                                 // Read Batch Index
    CHECK(iBatchIdx>=0, lblKO);
	CHECK(iBatchIdx!=0, lblEmpty);                             // Check if batch empty

    lLength = sizeof(ST_TRANSAC);                              // Read first transaction
	iRet = FMG_ReadRecord(&xFileInfo, &xTransac, &lLength, FMGMiddle, iIdx);
	CHECK(iRet==FMG_SUCCESS, lblFmgKO);

	iRet = GoalDspLine(xScreen, 0, "Up to inc", &txTrans[0], 0, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 6, "Down to dec", &txTrans[6], 0, false);
	CHECK(iRet>=0, lblKO);

	// Scrolling transactions
	// ======================
    while(1) 
	{
        sprintf(tcDisplay, "TRANSACTION %02d", iIdx);          // Show transaction
    	iRet = GoalDspLine(xScreen, 1, tcDisplay, &txTrans[1], 0, false);
    	CHECK(iRet>=0, lblKO);
    	sprintf(tcDisplay, "DATE: %s", xTransac.tcDate);
        iRet = GoalDspLine(xScreen, 2, tcDisplay, &txTrans[2], 0, false);
    	CHECK(iRet>=0, lblKO);
        sprintf(tcDisplay, "ACCOUNT #: %s", xTransac.tcAccount);
        iRet = GoalDspLine(xScreen, 3, tcDisplay, &txTrans[3], 0, false);
    	CHECK(iRet>=0, lblKO);
        sprintf(tcDisplay, "AMOUNT: %s", xTransac.tcAmount);
        iRet = GoalDspLine(xScreen, 4, tcDisplay, &txTrans[4], 0, false);
    	CHECK(iRet>=0, lblKO);
        sprintf(tcDisplay, "TYPE: %s", xTransac.tcType);
        iRet = GoalDspLine(xScreen, 5, tcDisplay, &txTrans[5], 0, true);
    	CHECK(iRet>=0, lblKO);

		iKey = GoalGetKey(xScreen, xGoal, true, 30*1000, false);  // Wait for key pressed/touched (shortcut)

		// Exit from batch
		// ---------------
        if(iKey==0)
            break;                                             // Exit loop if nothing is pressed during 5s
        if((iKey==GL_KEY_CANCEL) || (iKey==GL_KEY_VALID))
            break;                                             // Exit loop if red or green key is pressed
       
        // Scrolling UP transactions
        // -------------------------
        if (iKey==GL_KEY_UP)                                   // *** Key UP ***
		{
			if (iIdx < iBatchIdx)                              // Reading transaction
			{         
				iIdx++;
		        lLength = sizeof(ST_TRANSAC);
		    	iRet = FMG_ReadRecord(&xFileInfo, &xTransac, &lLength, FMGMiddle, iIdx);
		    	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
			}
		}
				
		// Scrolling DOWN transactions
		// ---------------------------
		if (iKey==GL_KEY_DOWN)                                 // *** Key DOWN ***
		{
        	if (iIdx > 1)                                      // Reading transaction
			{
				iIdx--;
		        lLength = sizeof(ST_TRANSAC);
		    	iRet = FMG_ReadRecord(&xFileInfo, &xTransac, &lLength, FMGMiddle, iIdx);
		    	CHECK(iRet==FMG_SUCCESS, lblFmgKO);
			}
		}
    }
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblEmpty:                            // Batch file empty
	GL_Dialog_Message(xGoal, NULL, "Batch Empty !!!", GL_ICON_WARNING, GL_BUTTON_VALID, 3*1000);
    goto lblEnd;
lblFmgKO:                            // File Management error
	GL_Dialog_Message(xGoal, NULL, FMG_ErrorMsg(iRet), GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd: 
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}
	
	


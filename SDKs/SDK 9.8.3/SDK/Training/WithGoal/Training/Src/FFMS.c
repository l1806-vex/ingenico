//****************************************************************************
//       INGENICO                                INGEDEV 7                  
//============================================================================
//       FILE  FFMS.C                             (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2008     Kassovic
//  Last modified : 13-July-2008     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                    *** Flash File Management System (FFMS) ***
//       FFMS provides a low level of services allowing the applications to 
//       manage and save files in the flash.
//       Show how to create a disk and open a file for writing and reading 
//       inside the flash.
//                                                                            
//  List of routines in file :  
//      DiskCreate : Create initialize and format a disk.
//      DiskKill : Suppress a disk.
//      DiskUse : Space used by the disk.
//      FileOpen : Open a file in flash and associate it to a flow.
//      FileRead : Read N bytes from a file.
//      FileWrite : Write N bytes into a file.                                        
//                            
//  File history :
//  071312-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

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
// Properties of the FFMS screen (Goal)
// =====================================
static const ST_DSP_LINE txFFMS[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line4
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

static long lMsgNbr;      // Message number

static const char *tzMsg[4] = { "One",      // Messages to write in Flash
                                "Two",
						        "Three",
						        "Seven" };

static char tcBufR[50+1]; // Reading buffer from file
static char tcBufW[50+1]; // Writing buffer into file
static int iLen;          // Message length

//****************************************************************************
//                          void DiskCreate (void)                            
//  This function creates, initializes (mount) and formats a disk.
//   - FS_dskcreate() : Create a volume or a disk.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DiskCreate(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	S_FS_PARAM_CREATE xCfg;
    unsigned long ulSize; // Not a doubleword but unsigned long inside prototype
    char *pcMsg=NULL;
    char tcDisplay[50+1];
	int iRet;
	
	// Disk creation in progress
	// *************************
	xScreen = GoalCreateScreen(xGoal, txFFMS, NUMBER_OF_LINES(txFFMS), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                          // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	strcpy(xCfg.Label, "TRAINING" );                                      // Disk name
    xCfg.Mode = FS_WRITEONCE;                                             // Disk on Flash
	xCfg.AccessMode	= FS_WRTMOD;                                          // r/w access
	xCfg.NbFichierMax = 16;                                               // Max files number
	xCfg.IdentZone	= FS_WO_ZONE_DATA;                                    // Zone id
	ulSize= xCfg.NbFichierMax*32768;                                      // Disk size in bytes

    iRet = FS_dskcreate(&xCfg, &ulSize);                                  // Create and format the disk
    CHECK(iRet==FS_OK, lblKODisk);

	iRet = GoalDspLine(xScreen, 0, "Disk name: TRAINING", &txFFMS[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "Disk created in Flash", &txFFMS[1], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 2, "Disk r/w access", &txFFMS[2], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 3, "Max files: 16", &txFFMS[3], 0, false);
	CHECK(iRet>=0, lblKO);
	sprintf (tcDisplay, "Size: %ld bytes", (long) ulSize);
	iRet = GoalDspLine(xScreen, 4, tcDisplay, &txFFMS[4], 30*1000, true); // Show disk size
	CHECK(iRet>=0, lblKO);

	lMsgNbr=0;

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
    GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblKODisk:                           // Disk error
    switch (iRet)
	{
	case FS_NAMEUSED: pcMsg = "Disk already created";    break;
	case FS_NOMEM:    pcMsg = "No space in Flash";       break;
	case FS_NOACCESS: pcMsg = "No access from Appli";    break;
	case FS_NOFORMAT: pcMsg = "Volume not formatted";    break;
	case FS_KO:
	default:          pcMsg = "Disk Flash KO";           break;
	}
    GL_Dialog_Message(xGoal, NULL, pcMsg, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:  
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}

//****************************************************************************
//                          void DiskKill (void)                            
//  This function suppresses a disk.      
//   - FS_unmount() : Release resources on disk.
//   - FS_dskkill() : Suppress a disk.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DiskKill(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	doubleword uiMode;  // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                        // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char *pcMsg=NULL;
	int iRet;

    // Mount the disk first
    // ********************
	xScreen = GoalCreateScreen(xGoal, txFFMS, NUMBER_OF_LINES(txFFMS), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);            // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = FS_mount ("/TRAINING", &uiMode); // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKODisk);

	// Disk suppression in progress
	// ****************************
    iRet = FS_unmount("/TRAINING");         // Release resources on disk
    CHECK(iRet==FS_OK, lblKODisk);
    iRet = FS_dskkill("/TRAINING");         // Disk suppression
    CHECK(iRet==FS_OK, lblKODisk);
    
	iRet = GoalDspLine(xScreen, 0, "Disk name: TRAINING", &txFFMS[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "Disk killed in Flash", &txFFMS[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                      // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblKODisk:                                  // Disk error
    switch (iRet)
	{
	case FS_NOACCESS: pcMsg = "No access from Appli";  break;
	case FS_DSKUSED:  pcMsg = "Disk is still mounted"; break;
	case FS_FILEUSED: pcMsg = "Files are still open";  break;
	case FS_KO:	
	default:          pcMsg = "Disk not found";        break;
	}
    GL_Dialog_Message(xGoal, NULL, pcMsg, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);        // Destroy screen
}

//****************************************************************************
//                          void DiskUse (void)                            
//  This function gives the space used by the disk in bytes (size-free).      
//   - FS_dsksize() : Disk size in bytes
//   - FS_dskfree() : Free space in bytes
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DiskUse(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char *pcMsg;
	char tcDisplay[50+1];
    long lSize, lFree;          
    int iRet;

    // Mount the disk first
    // ********************
	xScreen = GoalCreateScreen(xGoal, txFFMS, NUMBER_OF_LINES(txFFMS), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                          // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

    pcMsg = "Disk not found";
	iRet = FS_mount ("/TRAINING", &uiMode);                               // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKODisk);

	// Disk space used info
	// ********************
    lSize = FS_dsksize("/TRAINING");                                      // Disk size in bytes
    CHECK(lSize!=FS_ERROR, lblKODisk);
    lFree = FS_dskfree("/TRAINING");                                      // Free space in bytes
    CHECK(lFree!=FS_ERROR, lblKODisk);

	iRet = GoalDspLine(xScreen, 0, "Disk name: TRAINING", &txFFMS[0], 0, false);
	CHECK(iRet>=0, lblKO);
	sprintf(tcDisplay, "Used: %ld bytes", lSize-lFree);
	iRet = GoalDspLine(xScreen, 1, tcDisplay, &txFFMS[1], 30*1000, true); // Show disk size
	CHECK(iRet>=0, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblKODisk:                           // Disk error
	GL_Dialog_Message(xGoal, NULL, pcMsg, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}

//****************************************************************************
//                      void FileOpen (const char *pcMode)                            
//  This function opens a file in flash and associates it to a flow.
//       "r" open an existing file
//       "r+" open an existing file in updating mode (read and write)
//       "a" create or open an existing file in writing (end of file only)
//   - FS_open() : Open a file.
//  This function has parameters.
//    pcMode (I-) : how to open a file     
//  This function has no return value.                                      
//****************************************************************************

static S_FS_FILE *FileOpen(const char *pcMode) 
{
	// Local variables 
    // ***************
    S_FS_FILE *pxFid;                                        // FFMS file handle

	// File open in progress
	// *********************
    pxFid = FS_open("/TRAINING/MyFile.txt", (char*) pcMode); // "r", "r+" mode existing file  
    if(!pxFid)
	{
		if(    (strcmp(pcMode, "r+")==0)
            || (strcmp(pcMode, "r")==0) )
    		pxFid = FS_open("/TRAINING/MyFile.txt", "a");    // "a" mode creation or existing file
    }
	CHECK(pxFid!=NULL, lblKO);                               // "w", "w+" forbidden in flash
	
	return pxFid;

	// Errors treatment 
    // ****************
lblKO:
    return NULL;
}

//****************************************************************************
//                          void FileRead (void)                            
//  This function reads N bytes from the file.      
//   - FS_open() : Open the file in reading mode.
//   - FS_length() : Retrieve file length in bytes
//   - FS_seek() : Set the offset into the file.
//   - FS_read() : Read N bytes from the file.
//   - FS_close() : Close the file.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void FileRead(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char *pcMsg;
	long lOfs=0;
	char tcDisplay[21+1];
	S_FS_FILE *pxFid;                           // FFMS file handle
	int iRet;

    // Mount the disk first
    // ********************
	xScreen = GoalCreateScreen(xGoal, txFFMS, NUMBER_OF_LINES(txFFMS), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);


    pcMsg = "File missing";
	iRet = FS_mount ("/TRAINING", &uiMode);     // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKOFile);

    // File open in progress
	// *********************
    pxFid = FileOpen("r");                      // Open file in reading mode
    pcMsg = "File open failed";
    CHECK(pxFid!=NULL, lblKOFile);

	// File length
    // ===========
    iLen = FS_length(pxFid);                    // File length in bytes
    pcMsg = "File length failed";
	CHECK(iLen!=FS_ERROR, lblKOFile);

	// Offset start to file beginning
	// ==============================
	lOfs=0;
    iRet = FS_seek(pxFid, lOfs, FS_SEEKSET);    // Seek given offset
    pcMsg = "File seek failed";
    if(iRet != FS_OK)                           // Fail when file empty so continue anyway
	{
		CHECK(iLen==0, lblKOFile);
        iRet = FS_OK;
    }

	// File read in progress
	// *********************
	memset (tcBufR, 0, sizeof(tcBufR));
	if (iLen != 0)
	{
		iRet = FS_read(tcBufR, 1, iLen, pxFid); // Read from file
		pcMsg = "File read failed";
		CHECK(iRet==iLen, lblKOFile);
	}

	// File close in progress
	// **********************
    iRet = FS_close(pxFid);                     // Close file
    pcMsg = "File close failed";
    CHECK(iRet==FS_OK, lblKOFile);

	// Display file contain
	// ====================
	if (tcBufR[0] == 0)
		strcpy(tcBufR, "Empty");

	iRet = GoalDspLine(xScreen, 0, "File name: MyFile.txt", &txFFMS[0], 0, false);
	CHECK(iRet>=0, lblKO);                      // Show file contain in bytes
    sprintf(tcDisplay, "Read: %d bytes", iLen);
	iRet = GoalDspLine(xScreen, 1, tcDisplay, &txFFMS[1], 0, false);
	CHECK(iRet>=0, lblKO);                      // Show number of byte
	iRet = GoalDspLine(xScreen, 2, tcBufR, &txFFMS[2], 30*1000, true);
	CHECK(iRet>=0, lblKO);                      // Show bytes
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblKOFile:                           // File error
	GL_Dialog_Message(xGoal, NULL, pcMsg, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}

//****************************************************************************
//                          void FileWrite (void)                            
//  This function writes N bytes into the file.      
//  !!! NAND flash is composed of 512 bytes pages. 
//  Page is the unit for writing data in flash.
//  Block is the unit for erasing, pages are grouped in blocs.
//  Mechanism of buffered data is implemented so that writing is done per page of
//  512 bytes. Application can flush at any time and the flushing is automatically
//  done when closing the file.   
//   - FS_open() : Open the file in updating mode.
//   - FS_length() : Retrieve file length in bytes
//   - FS_seek() : Set the offset into the file.
//   - FS_write() : Write N bytes into the file.
//   - FS_flush() : Flush buffer 512 bytes into file.
//   - FS_close() : Close file.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void FileWrite(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	long lOfs=0;
	char *pcMsg;
	char tcDisplay[21+1];
	S_FS_FILE *pxFid;                        // FFMS file handle
	int iRet;

    // Mount the disk first
    // ********************
	xScreen = GoalCreateScreen(xGoal, txFFMS, NUMBER_OF_LINES(txFFMS), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);                   // Create screen and clear it

    pcMsg = "File missing";
	iRet = FS_mount ("/TRAINING", &uiMode);  // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKOFile);

	// Delete file after 5 writing 
	// ===========================
    if (lMsgNbr == 4){
		FS_unlink ("/TRAINING/MyFile.txt");  // Delete file
		lMsgNbr=0;
	}

    // File open in progress
	// *********************
    pxFid = FileOpen("r+");                  // Open file in updating mode
    pcMsg = "File open failed";
    CHECK(pxFid!=NULL, lblKOFile);
    
	// File length
    // ===========
	iLen = FS_length(pxFid);                 // File length in bytes
    pcMsg = "File length failed";
	CHECK(iLen!=FS_ERROR, lblKOFile);

	// Offset initialization
	// =====================
	if (lMsgNbr == 3) 
		lOfs=3;                              // Update the second message
	else 
		lOfs = iLen;                         // Write message at the end of file
    iRet = FS_seek(pxFid, lOfs, FS_SEEKSET); // Seek given offset
    pcMsg = "File seek failed";
	if(iRet != FS_OK)                        // Fail when file empty so continue anyway
	{
		CHECK(iLen==0, lblKOFile);                                 
        iRet = FS_OK;
    }
    
	// File write in progress
	// **********************
	strcpy (tcBufW, tzMsg[lMsgNbr]);
	iLen = strlen(tcBufW);
    iRet = FS_write(tcBufW, 1, iLen, pxFid); // Write into file
    pcMsg = "File write failed";
	CHECK(iRet==iLen, lblKOFile);
	lMsgNbr++;                               // Next message to write

	// Flush buffer 512 bytes on file
	// ==============================
	iRet = FS_flush(pxFid);                  // Flush buffer into file
    pcMsg = "File flush failed";
    CHECK(iRet>=0, lblKOFile);

	// File close in progress
	// **********************
	iRet = FS_close(pxFid);                  // Close file
    pcMsg = "File close failed";             // Done automatically the flush if missing
    CHECK(iRet==FS_OK, lblKOFile);

	// Display file contain
	// ====================
	iRet = GoalDspLine(xScreen, 0, "File name: MyFile.txt", &txFFMS[0], 0, false);
	CHECK(iRet>=0, lblKO);                   // Show file contain in bytes
    sprintf(tcDisplay, "Write: %d bytes", iLen);
	iRet = GoalDspLine(xScreen, 1, tcDisplay, &txFFMS[1], 0, false);
	CHECK(iRet>=0, lblKO);                   // Show number of byte
	iRet = GoalDspLine(xScreen, 2, tcBufW, &txFFMS[2], 30*1000, true);
	CHECK(iRet>=0, lblKO);                   // Show bytes

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblKOFile:                           // File error
	GL_Dialog_Message(xGoal, NULL, pcMsg, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}



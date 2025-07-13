//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  VFS.C                        (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                  *** Virtual File System management ***
//  1) Load file VFS.TXT inside HOST disk with LLT.
//  2) Demo USB Key
//      - Write file VFS.TXT into USB key 
//      - Read file VFS.TXT from USB key
//      - Delete file VFS.TXT from USB key
//  3) Demo MMC card
//      - Write file VFS.TXT into MMC card 
//      - Read file VFS.TXT from MMC card
//      - Delete file VFS.TXT from MMC card
//                                                                                       
//  List of routines in file :  
//      VFSWrite : Write file VFS.TXT from HOST to VFS (USB/MMC).
//      VFSRead : Read file VFS.TXT from VFS (USB/MMC).
//      VFSDelete : Delete file VFS.TXT from VFS (USB/MMC). 
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
// Properties of the Ums screen (Goal)
// ===================================
static const ST_DSP_LINE txUms[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} }
};

// Properties of the File screen (Goal)
// ====================================
static const ST_DSP_LINE txFile[] =
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

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};


static const char *tpcFspec[] = { "/dev/umsd0a", "/dev/mmcd0a" };         // Mass storage devices
static const char *tpcVolume[] = { "/USB", "/MMC" };                      // USB key or MMC card
static const char *tpcDirFile[] = { "/USB/VFS.TXT", "/MMC/VFS.TXT" };     // Path for VFS.TXT file
static const char *tpcInsert[] = { "USB Key", "MMC Card" };               // Prompt for USB key or MMC card
static const char *tpcVfsKO[] = { "USB Disk Failed", "MMC Disk Failed" }; // VFS problem

//****************************************************************************
//                    void VFSWrite (int VFSType)                             
//  This function writes the file VFS.TXT from the HOST disk to the USB key
//  or MMC card.
//   - WaitForUms() : Wait for USB key or MMC card
//   - mount() : Mount USB/MMC disk
//   - open() : Create/Open a file
//   - write() : Write a file
//   - close() : Close a file
//   - unmount() : Unmount USB/MMC disk
//  This function has parameters.  
//    VFSType (I-) : TYPE_USB or TYPE_MMC
//  This function has no return value.
//****************************************************************************

void VFSWrite(int VFSType) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	doubleword uiMode;   // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
	                     // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	S_FS_FILE *pxFile;
	char tcData[512];
    struct msdosfs_args xFatArgs;
    int iFile; 
    int iLenData;
	int iLen, iRet;
    
	// Wait for USB key or MMC card
	// ****************************
	xScreen = GoalCreateScreen(xGoal, txUms, NUMBER_OF_LINES(txUms), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                   // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, true);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Please Insert",  &txUms[0], 0, false);
	CHECK(iRet>=0, lblKO);                     	   // Insert USB key or MMC card

    iRet = TimerStart(0, 60*100);                  // Timer0 starts to 60s
    CHECK(iRet>=0, lblKO);
	while(1)
	{
		iRet = WaitForUms(0, VFSType);             // Wait for USB key or MMC card
		CHECK(iRet!=CR_ENTRY_NOK, lblKO);
		if (iRet == CR_ENTRY_OK)                   // Device present?
			break;                                 // Yes, start the writing process

		iRet = TimerGet(0);                        // Retrieve timer value
		CHECK(iRet!=0, lblEnd);                    // Exit on timeout

		iRet = GoalDspLine(xScreen, 1, (char*)tpcInsert[VFSType], &txUms[1],  1000, true);
		CHECK(iRet!=GL_KEY_CANCEL, lblEnd);        // Exit on cancel key
	}

	// Retrieve data from file VFS.TXT located in HOST disk
	// ****************************************************
	iRet = FS_mount ("/HOST", &uiMode);            // Disk HOST initialization (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblHostKO);
	pxFile = FS_open ("/HOST/VFS.TXT", "r");       // Open the file VFS.TXT
	CHECK(pxFile!=NULL, lblFileMissing);
    iLenData = FS_length(pxFile);                  // File length in bytes
    memset (tcData, 0, sizeof(tcData));
    iRet = FS_read(tcData, 1, iLenData, pxFile);   // Read data from file
    CHECK(iRet==iLenData, lblHostKO);
	iRet = FS_close(pxFile);                       // Close file
	CHECK(iRet==FS_OK, lblHostKO);
	iRet = FS_unmount("/HOST");                    // Disk HOST deactivation
	CHECK(iRet==FS_OK, lblHostKO);
	
	GoalDestroyScreen(&xScreen);                   // Destroy screen

    // Copy data into file VFS.TXT located in USB/MMC disk
    // ***************************************************
	xScreen = GoalCreateScreen(xGoal, txFile, NUMBER_OF_LINES(txFile), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                   // Create a new screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "1-Mount Disk", &txFile[0], 500, true);
	CHECK(iRet>=0, lblKO);
	memset(&xFatArgs, 0, sizeof(xFatArgs));
    xFatArgs.fspec = (char*)tpcFspec[VFSType];     // USB/MMC mass storage device 0 partition a
    xFatArgs.mask  = 0666;                         // rwx msdosfs perms
    xFatArgs.flags = MSDOSFSMNT_LONGNAME;          // Constant
    xFatArgs.magic = MSDOSFS_ARGSMAGIC;            // Constant
    iRet = mount(MOUNT_MSDOS, (char*) tpcVolume[VFSType], MNT_SYNCHRONOUS, &xFatArgs) ;  
    CHECK(iRet>=0, lblVfsKO);                      // Disk USB/MMC initialization

	iRet = GoalDspLine(xScreen, 1, "2-Open File", &txFile[1], 500, true);
	CHECK(iRet>=0, lblKO);                         // Create if not exist and open the file VFS.TXT
    iFile = open(tpcDirFile[VFSType], O_RDWR|O_CREAT|O_TRUNC, 0666);
    CHECK(iFile>=0, lblVfsKO);

	iRet = GoalDspLine(xScreen, 2, "2-Write File", &txFile[2], 500, true);
	CHECK(iRet>=0, lblKO);
    iLen = write(iFile, tcData, iLenData);         // Write data into file
    CHECK(iLen==iLenData, lblVfsKO);

	iRet = GoalDspLine(xScreen, 3, "2-Close File", &txFile[3], 500, true);
	CHECK(iRet>=0, lblKO);
    iRet = close(iFile);                           // Close file
    CHECK(iRet>=0, lblVfsKO);
 
	iRet = GoalDspLine(xScreen, 4, "3-Unmount Disk", &txFile[4], 1*1000, true);
	CHECK(iRet>=0, lblKO);
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                             // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblHostKO:                                         // HOST disk failed
	GL_Dialog_Message(xGoal, NULL, "HOST Disk Failed", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblVfsKO:                                          // USB/MMC disk failed
	GL_Dialog_Message(xGoal, NULL, tpcVfsKO[VFSType], GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblFileMissing:                                    // File not found
	GL_Dialog_Message(xGoal, NULL, "File VFS.TXT\nMissing from Host", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	TimerStop(0);                                  // Stop Timer0
    unmount(tpcVolume[VFSType], MNT_FORCE);        // Disk USB/MMC deactivation

	if (xScreen)
		GoalDestroyScreen(&xScreen);               // Destroy screen
}

//****************************************************************************
//                       void VFSRead (int VFSType)                             
//  This function reads the file VFS.TXT from the the USB key or MMC card.
//   - WaitForUms() : Wait for USB key or MMC card
//   - mount() : Mount USB/MMC disk
//   - open() : Open a file
//   - read() : Read a file
//   - close() : Close a file
//   - unmount() : Unmount USB/MMC disk
//  This function has parameters.  
//    VFSType (I-) : TYPE_USB or TYPE_MMC
//  This function has no return value.
//****************************************************************************

void VFSRead(int VFSType) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
	char tcData[512];
	char tcDisplay[50+1];
	char tcPrint[50+1];
    struct msdosfs_args xFatArgs;
    int iFile; 
    int iLenData;
    byte p; // Printer line index
	int iLen, iRet;
    	
	// Wait for USB key or MMC card
	// ****************************
	xScreen = GoalCreateScreen(xGoal, txUms, NUMBER_OF_LINES(txUms), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                    // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, true);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Please Insert",  &txUms[0], 0, false);
	CHECK(iRet>=0, lblKO);                     	    // Insert USB key or MMC card

    iRet = TimerStart(0, 60*100);                   // Timer0 starts to 60s
    CHECK(iRet>=0, lblKO);
	while(1)
	{
		iRet = WaitForUms(0, VFSType);              // Wait for USB key or MMC card
		CHECK(iRet!=CR_ENTRY_NOK, lblKO);
		if (iRet == CR_ENTRY_OK)                    // Device present?
			break;                                  // Yes, start the writing process

		iRet = TimerGet(0);                         // Retrieve timer value
		CHECK(iRet!=0, lblEnd);                     // Exit on timeout

		iRet = GoalDspLine(xScreen, 1, (char*)tpcInsert[VFSType], &txUms[1],  1000, true);
		CHECK(iRet!=GL_KEY_CANCEL, lblEnd);         // Exit on cancel key
	}

    GoalDestroyScreen(&xScreen);                    // Destroy screen

    // Read file VFS.TXT located in USB/MMC disk
    // *****************************************
	xScreen = GoalCreateScreen(xGoal, txFile, NUMBER_OF_LINES(txFile), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                    // Create a new screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "1-Mount Disk", &txFile[0], 500, true);
	CHECK(iRet>=0, lblKO);
    memset(&xFatArgs, 0, sizeof(xFatArgs));
    xFatArgs.fspec = (char*)tpcFspec[VFSType];      // USB/MMC mass storage device 0 partition a
    xFatArgs.mask  = 0666;                          // rwx msdosfs perms
    xFatArgs.flags = MSDOSFSMNT_LONGNAME;           // Constant
    xFatArgs.magic = MSDOSFS_ARGSMAGIC;             // Constant
    iRet = mount(MOUNT_MSDOS, (char*) tpcVolume[VFSType], MNT_SYNCHRONOUS, &xFatArgs) ;  
    CHECK(iRet>=0, lblVfsKO);                       // Disk USB/MMC initialization

	iRet = GoalDspLine(xScreen, 1, "2-Open File", &txFile[1], 500, true);
	CHECK(iRet>=0, lblKO);                          // Open the file VFS.TXT
    iFile = open(tpcDirFile[VFSType], O_RDONLY, 0666);
    CHECK(iFile>=0, lblFileMissing);

	iRet = GoalDspLine(xScreen, 2, "2-Read File", &txFile[2], 500, true);
	CHECK(iRet>=0, lblKO);
    iLenData = lseek(iFile, 0, SEEK_END);           // Get size of the file (offset to the end of file)
    lseek(iFile, 0, SEEK_SET);                      // Set offset to the beginning of file
    memset (tcData, 0, sizeof(tcData));
    iLen = read(iFile, tcData, iLenData);           // Read data from file
    CHECK(iLen==iLenData, lblVfsKO);

	iRet = GoalDspLine(xScreen, 3, "2-Close File", &txFile[3], 500, true);
	CHECK(iRet>=0, lblKO);
    iRet = close(iFile);                            // Close file
    CHECK(iRet>=0, lblVfsKO);
 
	iRet = GoalDspLine(xScreen, 4, "3-Unmount Disk", &txFile[4], 1*1000, true);
	CHECK(iRet>=0, lblKO);

    // Display file VFS.TXT
    // ********************
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcData, strlen(tcData), txFile, NUMBER_OF_LINES(txFile), 0, true);
	CHECK(iRet>=0, lblKO);

    // Print file VFS.TXT
	// ******************
	p=0;                                            // Create document
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);

	xLine = xPrinter;                               // Build document (Demo, File contain, data)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "VFS Demo", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // Data to print
    sprintf(tcPrint, "File: %s\n", tpcDirFile[VFSType]);
	iRet = GoalPrnLine(xDocument, p++, tcPrint, &xLine);
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcData, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);              // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true); // Wait for key pressed/touched (shortcut)
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                              // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblVfsKO:                                           // USB/MMC disk failed
	GL_Dialog_Message(xGoal, NULL, tpcVfsKO[VFSType], GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblFileMissing:                                     // File not found
	sprintf(tcDisplay, "FILE NOT FOUND\n%s", tpcDirFile[VFSType]);
	GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd: 
	TimerStop(0);                                   // Stop Timer0
    unmount(tpcVolume[VFSType], MNT_FORCE);         // Disk USB/MMC deactivation

	if (xScreen)
		GoalDestroyScreen(&xScreen);                // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);            // Destroy document
}

//****************************************************************************
//                       void VFSDelete (int VFSType)                             
//  This function deletes the file VFS.TXT from the the USB key or MMC card.
//   - WaitForUms() : Wait for USB key or MMC card
//   - mount() : Mount USB/MMC disk
//   - unlink() : Delete a file
//   - unmount() : Unmount USB/MMC disk
//  This function has parameters.  
//    VFSType (I-) : TYPE_USB or TYPE_MMC
//  This function has no return value.
//****************************************************************************

void VFSDelete(int VFSType) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
    struct msdosfs_args xFatArgs;
    int iFile; 
	char tcDisplay[50+1];
	int iRet;
	
	// Wait for USB key or MMC card
	// ****************************
	xScreen = GoalCreateScreen(xGoal, txUms, NUMBER_OF_LINES(txUms), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);               // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, true);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Please Insert",  &txUms[0], 0, false);
	CHECK(iRet>=0, lblKO);                     // Insert USB key or MMC card

    iRet = TimerStart(0, 60*100);              // Timer0 starts to 60s
    CHECK(iRet>=0, lblKO);
	while(1)
	{
		iRet = WaitForUms(0, VFSType);         // Wait for USB key or MMC card
		CHECK(iRet!=CR_ENTRY_NOK, lblKO);
		if (iRet == CR_ENTRY_OK)               // Device present?
			break;                             // Yes, start the writing process

		iRet = TimerGet(0);                    // Retrieve timer value
		CHECK(iRet!=0, lblEnd);                // Exit on timeout

		iRet = GoalDspLine(xScreen, 1, (char*)tpcInsert[VFSType], &txUms[1], 1000, true);
		CHECK(iRet!=GL_KEY_CANCEL, lblEnd);    // Exit on cancel key
	}

    GoalDestroyScreen(&xScreen);               // Destroy screen

    // Delete file VFS.TXT located in USB/MMC disk
    // *******************************************
	xScreen = GoalCreateScreen(xGoal, txFile, NUMBER_OF_LINES(txFile), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);               // Create a new screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "1-Mount Disk", &txFile[0], 500, true);
	CHECK(iRet>=0, lblKO);
    memset(&xFatArgs, 0, sizeof(xFatArgs));
    xFatArgs.fspec = (char*)tpcFspec[VFSType]; // USB/MMC mass storage device 0 partition a
    xFatArgs.mask  = 0666;                     // rwx msdosfs perms
    xFatArgs.flags = MSDOSFSMNT_LONGNAME;      // Constant
    xFatArgs.magic = MSDOSFS_ARGSMAGIC;        // Constant
    iRet = mount(MOUNT_MSDOS, (char*) tpcVolume[VFSType], MNT_SYNCHRONOUS, &xFatArgs) ;  
    CHECK(iRet>=0, lblVfsKO);                  // Disk USB/MMC initialization

	iRet = GoalDspLine(xScreen, 1, "2-Delete File", &txFile[1], 500, true);
	CHECK(iRet>=0, lblKO);
    iFile = unlink(tpcDirFile[VFSType]);       // Delete file VFS.TXT
    CHECK(iFile>=0, lblFileMissing);
    
	iRet = GoalDspLine(xScreen, 2, "3-Unmount Disk", &txFile[2], 1*1000, true);
	CHECK(iRet>=0, lblKO);
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                         // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblVfsKO:                                      // USB/MMC disk failed
	GL_Dialog_Message(xGoal, NULL, tpcVfsKO[VFSType], GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblFileMissing:                                // File not found
	sprintf(tcDisplay, "ALREADY DELETED\n%s", tpcDirFile[VFSType]);
	GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd: 
	TimerStop(0);                              // Stop Timer0
    unmount(tpcVolume[VFSType], MNT_FORCE);    // Disk USB/MMC deactivation

	if (xScreen)
		GoalDestroyScreen(&xScreen);           // Destroy screen
}

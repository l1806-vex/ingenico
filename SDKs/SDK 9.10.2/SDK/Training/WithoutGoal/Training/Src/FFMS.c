//****************************************************************************
//       INGENICO                                INGEDEV 7                  
//============================================================================
//       FILE  FFMS.C                            (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Flash File Management System (FFMS):
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
//  120508-BK : File created 
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
extern FILE *pxKbd;      // Peripheral file Keyboard

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
static long lMsgNbr;

static const char *tzMsg[4] = { "One",
                                "Two",
						        "Three",
						        "Six" };

static char tcBufR[50+1];                // Reading buffer from file
static char tcBufW[50+1];                // Writing buffer into file
static int iLen;                         // Message length   

//****************************************************************************
//                          void DiskCreate (void)                            
//  This function creates, initializes (mount) and formats a disk.
//       FS_dskcreate() : Create a volume or a disk.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DiskCreate(void) 
{
	// Local variables 
    // ***************
	S_FS_PARAM_CREATE xCfg;
    unsigned long ulSize;             // Not a doubleword but unsigned long inside prototype
    char *pcMsg;
    char tcDisplay[21+1];
	int iRet;
	
	// Disk creation in progress
	// *************************
    strcpy(xCfg.Label, "TRAINING" );                                         // Disk name
    xCfg.Mode = FS_WRITEONCE;                                                // Disk on Flash
	xCfg.AccessMode	= FS_WRTMOD;                                             // r/w access
	xCfg.NbFichierMax = 16;                                                  // Max files number
	xCfg.IdentZone	= FS_WO_ZONE_DATA;                                       // Zone id
	ulSize= xCfg.NbFichierMax*32768;                                         // Disk size in bytes

	pcMsg = "Disk create failed";
    iRet = FS_dskcreate(&xCfg, &ulSize); CHECK(iRet==FS_OK, lblKODisk);      // Create and format the disk

    _clrscr();                                                               // Clear screen
    DisplaySmall(0, 0, "Disk name: TRAINING");                               // Display disk info
    DisplaySmall(1, 0, "Disk created in Flash");
    DisplaySmall(2, 0, "Disk r/w access");
    DisplaySmall(3, 0, "Max files: 16");
    sprintf (tcDisplay, "Size : %ld bytes", (long) ulSize);
    DisplaySmall(4, 0, tcDisplay);

	lMsgNbr=0;

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKODisk:
	_clrscr();                                                                // Clear screen
	DisplaySmall(0, 0, pcMsg);
    switch (iRet)
	{
	case FS_NAMEUSED: pcMsg = "Disk already created";    break;
	case FS_NOMEM:    pcMsg = "No space in Flash";       break;
	case FS_NOACCESS: pcMsg = "No access from Appli";    break;
	case FS_NOFORMAT: pcMsg = "Volume not formatted";    break;
	case FS_KO:       
	default:          pcMsg = "Disk create failed";      break;
	}
	DisplaySmall(1, 0, pcMsg);                                               // Oops! error
    goto lblEnd;
lblEnd:  
	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                           // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                              // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                           // Reset keyboard FIFO to clear key pressed
}

//****************************************************************************
//                          void DiskKill (void)                            
//  This function suppresses a disk.      
//       FS_unmount() : Release resources on disk.
//       FS_dskkill() : Suppress a disk.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DiskKill(void) 
{
	// Local variables 
    // ***************
	doubleword uiMode;  // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                        // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char *pcMsg;
	int iRet;

    // Mount the disk first
    // ********************
	iRet = FS_mount ("/TRAINING", &uiMode); CHECK(iRet==FS_OK, lblKODisk);   // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))

	// Disk suppression in progress
	// ****************************
    iRet = FS_unmount("/TRAINING"); CHECK(iRet==FS_OK, lblKODisk);           // Release ressources on disk
    iRet = FS_dskkill("/TRAINING"); CHECK(iRet==FS_OK, lblKODisk);           // Disk suppression
    
    _clrscr();                                                               // Clear screen
    DisplaySmall(0, 0, "Disk name: TRAINING");                               // Display disk info
    DisplaySmall(1, 0,	"Disk killed in Flash");

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKODisk:
	_clrscr();                                                               // Clear screen
    switch (iRet)
	{
	case FS_NOACCESS: pcMsg = "No access from Appli";  break;
	case FS_DSKUSED:  pcMsg = "Disk is still mounted"; break;
	case FS_FILEUSED: pcMsg = "Files are still open";  break;
	case FS_KO:	
	default:          pcMsg = "Disk kill failed";      break;
	}
	DisplaySmall(0, 0, pcMsg);                                               // Oops! error
    goto lblEnd;
lblEnd:
	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                           // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                              // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                           // Reset keyboard FIFO to clear key pressed
}

//****************************************************************************
//                          void DiskUse (void)                            
//  This function gives the space used by the disk in bytes (size-free).      
//       FS_dsksize() : Disk size in bytes
//       FS_dskfree() : Free space in bytes
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DiskUse(void) 
{
	// Local variables 
    // ***************
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char *pcMsg;
	char tcDisplay[21+1];
    long lSize, lFree;          
    int iRet;

    // Mount the disk first
    // ********************
    pcMsg = "Disk Use failed";
	iRet = FS_mount ("/TRAINING", &uiMode); CHECK(iRet==FS_OK, lblKODisk); // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))

	// Disk space used info
	// ********************
    lSize = FS_dsksize("/TRAINING"); CHECK(lSize!=FS_ERROR, lblKODisk);      // Disk size in bytes
    lFree = FS_dskfree("/TRAINING"); CHECK(lFree!=FS_ERROR, lblKODisk);      // Free space in bytes

    _clrscr();                                                               // Clear screen
    DisplaySmall(0, 0, "Disk name: TRAINING");                               // Display used space in bytes
	sprintf(tcDisplay, "Used: %ld bytes", lSize-lFree);
	DisplaySmall(1, 0, tcDisplay);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKODisk:
	_clrscr();                                                               // Clear screen
	DisplaySmall(0, 0, pcMsg);                                               // Oops! error
    goto lblEnd;
lblEnd:
	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                           // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                              // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                           // Reset keyboard FIFO to clear key pressed
}

//****************************************************************************
//                      void FileOpen (const char *pcMode)                            
//  This function opens a file in flash and associates it to a flow.
//       "r" open an existing file
//       "r+" open an existing file in updating mode (read and write)
//       "a" create or open an existing file in writing (end of file only)
//       FS_open() : Open a file.
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
//       FS_open() : Open the file in reading mode.
//       FS_length() : Retrieve file length in bytes
//       FS_seek() : Set the offset into the file.
//       FS_read() : Read N bytes from the file.
//       FS_close() : Close the file.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void FileRead(void) 
{
	// Local variables 
    // ***************
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char *pcMsg;
	long lOfs=0;
	char tcDisplay[21+1];
	S_FS_FILE *pxFid;                               // FFMS file handle
	int iRet;

    // Mount the disk first
    // ********************
    pcMsg = "File missing";
	iRet = FS_mount ("/TRAINING", &uiMode);         // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKOFile);

    // File open in progress
	// *********************
    pxFid = FileOpen("r");                          // Open file in reading mode
    pcMsg = "File open failed\n";
    CHECK(pxFid!=NULL, lblKOFile);

	// File length
    // ===========
    iLen = FS_length(pxFid);                        // File length in bytes
    pcMsg = "File length failed\n";
	CHECK(iLen!=FS_ERROR, lblKOFile);

	// Offset start to file beginning
	// ==============================
	lOfs=0;
    iRet = FS_seek(pxFid, lOfs, FS_SEEKSET);        // Seek given offset
    pcMsg = "File seek failed";
    if(iRet != FS_OK)                               // Fail when file empty so continue anyway
	{
		CHECK(iLen==0, lblKOFile);
        iRet = FS_OK;
    }

	// File read in progress
	// *********************
	memset (tcBufR, 0, sizeof(tcBufR));
	if (iLen != 0)
	{
		iRet = FS_read(tcBufR, 1, iLen, pxFid);     // Read from file
		pcMsg = "File read failed";
		CHECK(iRet==iLen, lblKOFile);
	}

	// File close in progress
	// **********************
    iRet = FS_close(pxFid);                         // Close file
    pcMsg = "File close failed";
    CHECK(iRet==FS_OK, lblKOFile);

	// Display file contain
	// ====================
	if (tcBufR[0] == 0)
		strcpy(tcBufR, "Empty");

    _clrscr();                                      // Clear screen
	DisplaySmall(0, 0, "File name: MyFile.txt");    // Display file contain in bytes
    sprintf(tcDisplay, "Read: %d bytes", iLen);
    DisplaySmall(1, 0, tcDisplay);
    DisplaySmall(2, 0, tcBufR);
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKOFile:
	_clrscr();                                      // Clear screen
	DisplaySmall(0, 0, pcMsg);                      // Oops! error
    goto lblEnd;
lblEnd:
	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                  // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                     // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                  // Reset keyboard FIFO to clear key pressed
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
//       FS_open() : Open the file in updating mode.
//       FS_length() : Retrieve file length in bytes
//       FS_seek() : Set the offset into the file.
//       FS_write() : Write N bytes into the file.
//       FS_flush() : Flush buffer 512 bytes into file.
//       FS_close() : Close file.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void FileWrite(void) 
{
	// Local variables 
    // ***************
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	long lOfs=0;
	char *pcMsg;
	char tcDisplay[21+1];
	S_FS_FILE *pxFid;                               // FFMS file handle
	int iRet;

    // Mount the disk first
    // ********************
    pcMsg = "File missing";
	iRet = FS_mount ("/TRAINING", &uiMode);         // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKOFile);

	// Delete file after 5 writing 
	// ===========================
    if (lMsgNbr == 4){
		FS_unlink ("/TRAINING/MyFile.txt");         // Delete file
		lMsgNbr=0;
	}

    // File open in progress
	// *********************
    pxFid = FileOpen("r+");                         // Open file in updating mode
    pcMsg = "File open failed";
    CHECK(pxFid!=NULL, lblKOFile);
    
	// File length
    // ===========
	iLen = FS_length(pxFid);                        // File length in bytes
    pcMsg = "File length failed";
	CHECK(iLen!=FS_ERROR, lblKOFile);

	// Offset initialization
	// =====================
	if (lMsgNbr == 3) 
		lOfs=3;                                     // Update the second message
	else 
		lOfs = iLen;                                // Write message at the end of file
    iRet = FS_seek(pxFid, lOfs, FS_SEEKSET);        // Seek given offset
    pcMsg = "File seek failed";
	if(iRet != FS_OK)                               // Fail when file empty so continue anyway
	{
		CHECK(iLen==0, lblKOFile);                                 
        iRet = FS_OK;
    }
    
	// File write in progress
	// **********************
	strcpy (tcBufW, tzMsg[lMsgNbr]);
	iLen = strlen(tcBufW);
    iRet = FS_write(tcBufW, 1, iLen, pxFid);        // Write into file
    pcMsg = "File write failed";
	CHECK(iRet==iLen, lblKOFile);
	lMsgNbr++;                                      // Next message to write

	// Flush buffer 512 bytes on file
	// ==============================
	iRet = FS_flush(pxFid);                         // Flush buffer into file
    pcMsg = "File flush failed";
    CHECK(iRet>=0, lblKOFile);

	// File close in progress
	// **********************
	iRet = FS_close(pxFid);                         // Close file
    pcMsg = "File close failed";                    // Done automatically the flush if missing
    CHECK(iRet==FS_OK, lblKOFile);

	// Display file contain
	// ====================
    _clrscr();                                      // Clear screen
	DisplaySmall(0, 0, "File name: MyFile.txt");    // Display file contain in bytes
    sprintf(tcDisplay, "Write: %d bytes", iLen);
    DisplaySmall(1, 0, tcDisplay);
    DisplaySmall(2, 0, tcBufW);

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKOFile:
	_clrscr();                                      // Clear screen
	DisplaySmall(0, 0, pcMsg);                      // Oops! error
    goto lblEnd;
lblEnd:
	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                  // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                     // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                  // Reset keyboard FIFO to clear key pressed
}



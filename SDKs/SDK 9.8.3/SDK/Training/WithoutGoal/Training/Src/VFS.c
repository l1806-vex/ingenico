//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  VFS.C                        (Copyright INGENICO 2009)   
//============================================================================
//  Created :       16-May-2009     Kassovic                                 
//  Last modified : 16-May-2009     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Virtual File System process:
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
//  160509-BK : File created 
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
static const char *tpcFspec[] = { "/dev/umsd0a", "/dev/mmcd0a" };
static const char *tpcVolume[] = { "/USB", "/MMC" };
static const char *tpcDirFile[] = { "/USB/VFS.TXT", "/MMC/VFS.TXT" };
static const char *tpcInsert[] = { "Please Insert\nUSB Key", "Please Insert\nMMC Card" };
static const char *tpcVfsKO[] = { "USB Disk Failed", "MMC Disk Failed" };

//****************************************************************************
//                    void VFSWrite (int VFSType)                             
//  This function writes the file VFS.TXT from the HOST disk to the USB key
//  or MMC card.
//       WaitForUms() : Wait for USB key or MMC card
//       mount() : Mount USB/MMC disk
//       open() : Create/Open a file
//       write() : Write a file
//       close() : Close a file
//       unmount() : Unmount USB/MMC disk
//  This function has parameters.  
//    VFSType (I-) : TYPE_USB or TYPE_MMC
//  This function has no return value.
//****************************************************************************

void VFSWrite(int VFSType) 
{
	// Local variables 
    // ***************
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
	_clrscr();                                                                   // Clear screen
	DisplayMedium(0, 0, (char*)tpcInsert[VFSType]);                              // Insert USB key or MMC card
    iRet = WaitForUms(30, VFSType);
    CHECK((iRet!=CR_ENTRY_CANCEL) && (iRet!=CR_ENTRY_TIME_OUT), lblEnd);
    CHECK(iRet==CR_ENTRY_OK, lblKO);
	
	// Retrieve data from file VFS.TXT located in HOST disk
	// ****************************************************
	iRet = FS_mount ("/HOST", &uiMode); CHECK(iRet==FS_OK, lblHostKO);           // Disk HOST initialization (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	pxFile = FS_open ("/HOST/VFS.TXT", "r");                                     // Open the file VFS.TXT
	CHECK(pxFile!=NULL, lblFileMissing);
    iLenData = FS_length(pxFile);                                                // File length in bytes
    memset (tcData, 0, sizeof(tcData));
    iRet = FS_read(tcData, 1, iLenData, pxFile);                                 // Read data from file
    CHECK(iRet==iLenData, lblHostKO);
	iRet = FS_close(pxFile); CHECK(iRet==FS_OK, lblHostKO);                      // Close file   
	iRet = FS_unmount("/HOST"); CHECK(iRet==FS_OK, lblHostKO);                   // Disk HOST deactivation
	
    // Copy data into file VFS.TXT located in USB/MMC disk
    // ***************************************************
	_clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "1-Mount Disk");                                         // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms 
    memset(&xFatArgs, 0, sizeof(xFatArgs));
    xFatArgs.fspec = (char*)tpcFspec[VFSType];                                   // USB/MMC mass storage device 0 partition a
    xFatArgs.mask  = 0666;                                                       // rwx msdosfs perms
    xFatArgs.flags = MSDOSFSMNT_LONGNAME;                                        // Constant
    xFatArgs.magic = MSDOSFS_ARGSMAGIC;                                          // Constant
    iRet = mount(MOUNT_MSDOS, (char*) tpcVolume[VFSType], MNT_SYNCHRONOUS, &xFatArgs) ;  
    CHECK(iRet>=0, lblVfsKO);                                                    // Disk USB/MMC initialisation

    DisplayMedium(1, 0, "1-Open File");                                          // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms  
    iFile = open(tpcDirFile[VFSType], O_RDWR|O_CREAT|O_TRUNC, 0666);             // Create if not exist and open the file VFS.TXT
    CHECK(iFile>=0, lblVfsKO);

    DisplayMedium(2, 0, "1-Write File");                                         // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms  
    iLen = write(iFile, tcData, iLenData); CHECK(iLen==iLenData, lblVfsKO);      // Write data into file

    DisplayMedium(3, 0, "1-Close File");                                         // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms      
    iRet = close(iFile); CHECK(iRet>=0, lblVfsKO);                               // Close file
 
	_clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "2-Unmount Disk");                                       // Display Msg
    ttestall(0, 1*100);                                                          // Delay 1s      
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                                           // None-classified low level error
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "Processing Error");                                     // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblHostKO:                                                                       // HOST disk failed
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "HOST Disk failed");                                     // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblVfsKO:                                                                        // USB/MMC disk failed
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, (char*)tpcVfsKO[VFSType]);                               // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblFileMissing:                                                                  // File not found
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "FILE NOT FOUND:");                                      // Oops! error
    DisplayMedium(1, 0, "/HOST/VFS.TXT");
    ttestall(0,5*100);                                                           // Delay 5s 
lblEnd: 
    unmount(tpcVolume[VFSType], MNT_FORCE);                                      // Disk USB/MMC deactivation
}

//****************************************************************************
//                       void VFSRead (int VFSType)                             
//  This function reads the file VFS.TXT from the the USB key or MMC card.
//       WaitForUms() : Wait for USB key or MMC card
//       mount() : Mount USB/MMC disk
//       open() : Open a file
//       read() : Read a file
//       close() : Close a file
//       unmount() : Unmount USB/MMC disk
//  This function has parameters.  
//    VFSType (I-) : TYPE_USB or TYPE_MMC
//  This function has no return value.
//****************************************************************************

void VFSRead(int VFSType) 
{
	// Local variables 
    // ***************
	char tcData[512];
	char tcDisplay[25+1];
    struct msdosfs_args xFatArgs;
    int iFile; 
    int iLenData;
	int iLen, iRet;
    	
	// Wait for USB key or MMC card
	// ****************************
	_clrscr();                                                                   // Clear screen
	DisplayMedium(0, 0, (char*)tpcInsert[VFSType]);
    iRet = WaitForUms(60, VFSType);
    CHECK((iRet!=CR_ENTRY_CANCEL) && (iRet!=CR_ENTRY_TIME_OUT), lblEnd);
    CHECK(iRet==CR_ENTRY_OK, lblKO);

    // Read file VFS.TXT located in USB/MMC disk
    // *****************************************
	_clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0,"1-Mount Disk");                                          // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms 
    memset(&xFatArgs, 0, sizeof(xFatArgs));
    xFatArgs.fspec = (char*)tpcFspec[VFSType];                                  // USB/MMC mass storage device 0 partition a
    xFatArgs.mask  = 0666;                                                       // rwx msdosfs perms
    xFatArgs.flags = MSDOSFSMNT_LONGNAME;                                        // Constant
    xFatArgs.magic = MSDOSFS_ARGSMAGIC;                                          // Constant
    iRet = mount(MOUNT_MSDOS, (char*) tpcVolume[VFSType], MNT_SYNCHRONOUS, &xFatArgs) ;  
    CHECK(iRet>=0, lblVfsKO);                                                    // Disk USB/MMC initialisation

    DisplayMedium(1, 0, "1-Open File");                                          // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms  
    iFile = open(tpcDirFile[VFSType], O_RDONLY, 0666);                           // Open the file VFS.TXT
    CHECK(iFile>=0, lblFileMissing);

    DisplayMedium(2, 0, "1-Read File");                                          // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms  
    iLenData = lseek(iFile, 0, SEEK_END);                                        // Get size of the file (offset to the end of file)
    lseek(iFile, 0, SEEK_SET);                                                   // Set offset to the beginning of file
    iLen = read(iFile, tcData, iLenData); CHECK(iLen==iLenData, lblVfsKO);       // Read data from file

    DisplayMedium(3, 0, "1-Close File");                                         // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms      
    iRet = close(iFile); CHECK(iRet>=0, lblVfsKO);                               // Close file
 
	_clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "2-Unmount Disk");                                       // Display Msg
    ttestall(0, 1*100);                                                          // Delay 1s      

    // Display file VFS.TXT
    // ********************
    _clrscr();                                                                   // Clear screen
    sprintf(tcDisplay, "FILE %s:", tpcDirFile[VFSType]);
    DisplaySmall(0, 0, tcDisplay);                                               // Display file name
    Display25(1, tcData, iLenData);                                              // Display data file
    DisplaySmall(7, 6, "Press a key");

    // Print file VFS.TXT
	// ******************
	iRet = pprintf("\x1b""E""         VFS Demo\n\n"                              // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
    iRet = pprintf("FILE %s:\n", tpcDirFile[VFSType]); CHECK(iRet>=0, lblKO);    // Print data file
	iRet = Print24(tcData, iLenData); CHECK(iRet>=0, lblKO);
	iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	reset_buf(pxKbd, _receive_id);                                               // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                                  // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                               // Reset keyboard FIFO to clear key pressed

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                                           // None-classified low level error
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "Processing Error");                                     // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblVfsKO:                                                                        // USB/MMC disk failed
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, (char*)tpcVfsKO[VFSType]);                               // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblFileMissing:                                                                  // File not found
	_clrscr();                                                                   // Clear screen
	DisplayMedium(0, 0, "FILE NOT FOUND:");                                      // Oops! error
	DisplayMedium(1, 0, (char*)tpcDirFile[VFSType]);
    ttestall(0,5*100);                                                           // Delay 5s 
lblEnd: 
    unmount(tpcVolume[VFSType], MNT_FORCE);                                      // Disk USB/MMC deactivation
}

//****************************************************************************
//                       void VFSDelete (int VFSType)                             
//  This function deletes the file VFS.TXT from the the USB key or MMC card.
//       WaitForUms() : Wait for USB key or MMC card
//       mount() : Mount USB/MMC disk
//       unlink() : Delete a file
//       unmount() : Unmount USB/MMC disk
//  This function has parameters.  
//    VFSType (I-) : TYPE_USB or TYPE_MMC
//  This function has no return value.
//****************************************************************************

void VFSDelete(int VFSType) 
{
	// Local variables 
    // ***************
    struct msdosfs_args xFatArgs;
    int iFile; 
	int iRet;
	
	// Wait for USB key or MMC card
	// ****************************
	_clrscr();                                                                   // Clear screen
	DisplayMedium(0, 0, (char*)tpcInsert[VFSType]);
    iRet = WaitForUms(30, VFSType);
    CHECK((iRet!=CR_ENTRY_CANCEL) && (iRet!=CR_ENTRY_TIME_OUT), lblEnd);
    CHECK(iRet==CR_ENTRY_OK, lblKO);

    // Delete file VFS.TXT located in USB/MMC disk
    // *******************************************
	_clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "1-Mount Disk");                                         // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms 
    memset(&xFatArgs, 0, sizeof(xFatArgs));
    xFatArgs.fspec = (char*)tpcFspec[VFSType];                                   // USB/MMC mass storage device 0 partition a
    xFatArgs.mask  = 0666;                                                       // rwx msdosfs perms
    xFatArgs.flags = MSDOSFSMNT_LONGNAME;                                        // Constant
    xFatArgs.magic = MSDOSFS_ARGSMAGIC;                                          // Constant
    iRet = mount(MOUNT_MSDOS, (char*) tpcVolume[VFSType], MNT_SYNCHRONOUS, &xFatArgs) ;  
    CHECK(iRet>=0, lblVfsKO);                                                    // Disk USB/MMC initialisation

    DisplayMedium(1, 0, "1-Delete File");                                        // Display Msg
    ttestall(0, 50);                                                             // Delay 500ms  
    iFile = unlink(tpcDirFile[VFSType]); CHECK(iFile>=0, lblFileMissing);        // Delete file VFS.TXT
    
    DisplayMedium(2, 0, "1-Unmount Disk");                                       // Display Msg
    ttestall(0, 1*100);                                                          // Delay 1s      
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                                           // None-classified low level error
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, "Processing Error");                                     // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblVfsKO:                                                                        // USB/MMC disk failed
    _clrscr();                                                                   // Clear screen
    DisplayMedium(0, 0, (char*)tpcVfsKO[VFSType]);                               // Oops! error
    ttestall(0,5*100);                                                           // Delay 5s 
    goto lblEnd;
lblFileMissing:                                                                  // File not found
    _clrscr();                                                                   // Clear screen
	DisplayMedium(0, 0, "ALREADY DELETED:");                                     // Oops! error
	DisplayMedium(1, 0, (char*)tpcDirFile[VFSType]);
    ttestall(0,5*100);                                                           // Delay 5s 
lblEnd: 
    unmount(tpcVolume[VFSType], MNT_FORCE);                                      // Disk USB/MMC deactivation
}

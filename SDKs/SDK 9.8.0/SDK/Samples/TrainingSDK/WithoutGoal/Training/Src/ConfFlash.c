//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  CONFFLASH.C                         (Copyright INGENICO 2011)
//============================================================================
//  Created :       02-May-2011     Kassovic
//  Last modified : 02-May-2011     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Describe the complete Flash memory configuration.
//  CFS disk (System disk)
//  DFS disks (Host disk, Os disks, Manager disks,..., Application disks) 
//                                                                            
//  List of routines in file :  
//      ReadDirectories : Read files from a disk.
//      ConfFlash : Configuration regarding the Flash memory.                                            
//                            
//  File history :
//  020511-BK : File created
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
static FILE *pxCom=NULL;

static S_FS_DIR *pxDir;
static S_FS_FILEINFO xFile;
static S_FS_FILE *pxFid;

static int iTotStorage;
static int iTotFiles;
static char tcBuffer[256+1];

//****************************************************************************
//            int ReadDirectories (doubleword uiCom, char *pcDir)
//  This function parses directories and sub-directories inside a disk to
//  read files (Name, Size and Storage). A recursive method is used.
//  The information is sent through COM0 to a console.
//       FS_opendir() : open a flow on a directory.
//       FS_readdir() : read information on a file.
//  This function has parameters.
//      uiCom (I-) : Communication channel.
//		pcDir (I-) : Path regarding the directory to parse.
//  This function has return value.
//      <0 : Open flow on directory failed.
//       0 : Read files on directory failed.
//      >0 : Read files on directory done.
//****************************************************************************

static int ReadDirectories(doubleword uiCom, char *pcDir)
{
	// Local variables
	// ***************
	Telium_size_t uiLen;
	char tcDir[256+1];
	unsigned long ulStorage;
	int iRet;

	// Parsing directories and sub-directories in progress
	// ***************************************************
	iRet=-1;                                                                              // By default open flow on directory failed
	pxDir = FS_opendir(pcDir);                                                            // *** Open flow on a directory to read files "/DISKNAME/DIRECTORY/*" ***
	if(pxDir)
	{
		iRet=0;                                                                           // By default reading files on directory failed
		pcDir[strlen(pcDir)-1]=0;
		memset(&xFile, 0, sizeof(S_FS_FILEINFO));
		while(FS_readdir(pxDir, &xFile) == FS_OK)                                         // *** Read files on a directory "/DISKNAME/DIRECTORY/" ***
		{
			iRet=1;                                                                       // Access file or sub-directory done
			if (xFile.FileSize == -1)                                                     // Check if SUB-DIRECTORY
			{
				sprintf(tcDir, "%s%s/*", pcDir, xFile.FileName);
				sprintf(tcBuffer, "%s Size: %ld Storage: -1\r\n", tcDir, xFile.FileSize);
				iRet=ReadDirectories(uiCom, tcDir);                                       // *** Open flow on a sub-directory to read files ***
				if (iRet==0)                                                              // Access files on sub-directory failed
				{
					// *** Send buffer to console (hyper terminal) ***
					uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom);         // Send sub-directory without access
					mask_event(pxCom, COM_SEND_END);
					ttestall(uiCom, 5*100);
					iRet=1;
				}
				return iRet;
			}
			else
			{
				sprintf(tcDir, "%s%s", pcDir, xFile.FileName);
				pxFid = FS_open(tcDir, "r");                                              // Open file in reading mode "/DISKNAME/DIRECTORY/FILENAME"
				ulStorage = FS_StorageSize(pxFid);                                        // File description (Name, Size and Storage)
				sprintf(tcBuffer, "%s Size: %ld Storage: %ld\r\n", tcDir, xFile.FileSize, ulStorage);

            	if (ulStorage != -1)                                                      // Update counter if necessary
            	{
            		iTotStorage += ulStorage;
        		    iTotFiles++;
            	}
    		    FS_close(pxFid);                                                          // Close file

				// *** Send buffer to console (hyper terminal) ***
				uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom);              // Send file description
				mask_event(pxCom, COM_SEND_END);
				ttestall(uiCom, 5*100);
			}
		}
	}

	return iRet;
}

//****************************************************************************
//                  void ConfFlash (doubleword uiCom)
//  This function sent to a console (hyper-terminal) the complete configuration
//  regarding the Flash memory.
//  1) 3 blocks of Flash => Size, Free and Garbage spaces
//  2) Issuer, Type, Size, Pages by Block, Block size and Bad Blocks
//  3) CFS (SYSTEM DISK) => Size, Free and Garbage spaces
//     DFS (OTHER DISKS) => Size, Free and Garbage spaces
//  4) Disks => Name, Size and Free spaces
//              Access, Appli owner, Appli using it
//              Files description => Name, Size and Storage
//       FS_Diag() : retrieve flash memory informations.
//       FS_AreaGetSize() : return size of flash area (CFS or DFS).
//       FS_AreaGetFreeSize() : return free size of a flash area (CFS or DFS).
//       FS_AreaGetGarbageSize() : return garbage size of a flash area (CFS or DFS).
//       FS_disklist() : list the number of disks.
//  This function has parameters.
//      uiCom (I-) : Communication channel.
//  This function has no return value.
//****************************************************************************

void ConfFlash(doubleword uiCom)
{
	// Local variables
    // ***************
	Telium_size_t uiLen;
	char tcDriver[24+1];
	S_FS_DIAG xDiag;
	doubleword uiNbrDisk;
	S_FS_INFO_CONTEXT xInfo;
	char* pcBuffer;
	char tcName[1+FS_DISKNAMESIZE+1];
	doubleword uiMode;  // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                        // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char tcAccessMode[16+1];
    int iRet, i;

    // Com channel initialization
    // **************************
	switch (uiCom)
	{
	case COM0:
		pxCom = fopen("COM0", "rw*"); CHECK(pxCom!=NULL, lblKO);                              // Open "com0" channel
	    iRet = format("COM0", 115200, 8, 1, NO_PARITY, EVEN, 0);  CHECK(iRet>=0, lblKO);      // Format COM0 channel
		break;
	case COM5:
		pxCom = fopen("COM5", "rw*"); CHECK(pxCom!=NULL, lblKO);                              // Open "com5" channel
		break;
	case COM_EXT:                                                                             // Open "Converter USB->RS232" channel
		// Telium supports the following drivers:
		// - "COM_KEYSPAN" (Keyspan USA19HS)
		// - "COM_SL" (SiliconLabs CP2102)
		// - "COM20" (Prolific 2303)
		// - "COM21" (FTDI)
		// - "COM_MGBX" (Generic Magic Box)
		// With event generated COM_EXT
		pxCom = OpenConverter(tcDriver, sizeof(tcDriver)); CHECK(pxCom!=NULL, lblKO);
	    iRet = format(tcDriver, 115200, 8, 1, NO_PARITY, EVEN, 0); CHECK(iRet>=0, lblKO);     // Format converter channel
		break;
	default:
		goto lblKO;
	}

    // Flash memory configuration
    // **************************
    FS_Diag(&xDiag);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "###################################################################\r\n");
	pcBuffer += sprintf(pcBuffer, "#                     FLASH CONFIGURATION                         #\r\n");
	sprintf(pcBuffer,             "###################################################################\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    pcBuffer=tcBuffer;
    pcBuffer += sprintf(pcBuffer, "Area[0] Ident: %i Size: %ld Free: %ld Garbage: %ld\r\n", xDiag.Area[0].Ident, xDiag.Area[0].Size, xDiag.Area[0].Free, xDiag.Area[0].Erasable);
    pcBuffer += sprintf(pcBuffer, "Area[1] Ident: %i Size: %ld Free: %ld Garbage: %ld\r\n", xDiag.Area[1].Ident, xDiag.Area[1].Size, xDiag.Area[1].Free, xDiag.Area[1].Erasable);
    pcBuffer += sprintf(pcBuffer, "Area[2] Ident: %i Size: %ld Free: %ld Garbage: %ld\r\n", xDiag.Area[2].Ident, xDiag.Area[2].Size, xDiag.Area[2].Free, xDiag.Area[2].Erasable);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcBuffer += sprintf(pcBuffer, "Issuer: 0x%02X Type: %ld Size: %ld\r\n", (int)xDiag.DeviceMaker, xDiag.DeviceType, xDiag.SizeFlash);
    pcBuffer += sprintf(pcBuffer, "PagesBlock: %ld Block: %ld BadBlocks: %ld\r\n", xDiag.PagesBlock, xDiag.SizeBlock, xDiag.BadBlockNb);
	sprintf (pcBuffer,            "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    pcBuffer=tcBuffer;
    pcBuffer += sprintf(pcBuffer, "Code File System (SYSTEM disk)\r\n");                      // *** CFS => Total size, Free size, Garbage size(become free after garbage collection) ***
    pcBuffer += sprintf(pcBuffer, "Size: %i ", FS_AreaGetSize(FS_WO_ZONE_APPLICATION));
    pcBuffer += sprintf(pcBuffer, "Free: %i ", FS_AreaGetFreeSize(FS_WO_ZONE_APPLICATION));
    pcBuffer += sprintf(pcBuffer, "Garbage: %i\r\n", FS_AreaGetGarbageSize(FS_WO_ZONE_APPLICATION));
    pcBuffer += sprintf(pcBuffer, "Data File System (Other disks)\r\n");                      // *** DFS => Total size, Free size, Garbage size(become free after garbage collection) ***
    pcBuffer += sprintf(pcBuffer, "Size: %i ", FS_AreaGetSize(FS_WO_ZONE_DATA));
    pcBuffer += sprintf(pcBuffer, "Free: %i ", FS_AreaGetFreeSize(FS_WO_ZONE_DATA));
    pcBuffer += sprintf(pcBuffer, "Garbage: %i\r\n", FS_AreaGetGarbageSize(FS_WO_ZONE_DATA));
	sprintf (pcBuffer,            "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    // Disks memory information
    // ************************
    FS_dsklist(&uiNbrDisk, &xInfo);                                                           // *** Retrieve number of disks ***
    for (i=0; i<uiNbrDisk; i++)
    {
    	sprintf(tcName, "/%.16s", xInfo.DiskIdent[i].Label);                                  // *** Mount disk "/DISKNAME" ***
    	iRet = FS_mount (tcName, &uiMode);
    	pcBuffer=tcBuffer;
    	pcBuffer += sprintf(pcBuffer, "Disk: %s ", tcName);                                   // Disk name
    	pcBuffer += sprintf(pcBuffer, "Size: %ld ", FS_dsksize(tcName));                      // Disk total size
//    	pcBuffer += sprintf(pcBuffer, "Size1: %i ", FS_AreaGetSize(FS_WO_ZONE_APPLICATION));
//    	pcBuffer += sprintf(pcBuffer, "Free1: %i ", FS_AreaGetFreeSize(FS_WO_ZONE_APPLICATION));
    	pcBuffer += sprintf(pcBuffer, "Free: %ld\r\n", FS_dskfree(tcName));                   // Disk free size

    	iRet = FS_readmode(tcName);                                                           // *** Access disk ***
    	switch (iRet)
    	{
    	case FS_WRTMOD:   strcpy(tcAccessMode, "ReadWrite"); break;                           // Read/Write mode
    	case FS_RONLYMOD: strcpy(tcAccessMode, "ReadOnly");  break;                           // Read only mode
    	default:          strcpy(tcAccessMode, "NoAccess");  break;                           // No access mode
    	}
    	pcBuffer += sprintf(pcBuffer, "Access: %s ", tcAccessMode);                           // Disk access
    	pcBuffer += sprintf(pcBuffer, "AppliCreate: 0x%04X ", xInfo.DiskIdent[i].NumAppli);   // Which appli creates the disk
    	sprintf(pcBuffer,             "AppliUsed: 0x%04X\r\n", _ING_APPLI_TYPE);              // Which appli uses the disk

		// *** Send buffer to console (hyper terminal ***
    	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
    	mask_event(pxCom, COM_SEND_END);
    	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    	iTotStorage =0;                                                                       // Reset storage size in disk
    	iTotFiles=0;                                                                          // Reset number of files in disk
    	sprintf(tcName, "/%.16s/*", xInfo.DiskIdent[i].Label);                                // *** Open flow on a directory to read files "/DISKNAME/*" ***
    	iRet=ReadDirectories(uiCom, tcName);
    	pcBuffer=tcBuffer;
    	if (iRet>=0)
    	{
        	pcBuffer += sprintf(pcBuffer, "%i files ", iTotFiles);                            // Total files in disk
    		pcBuffer += sprintf(pcBuffer, "Storage: %i\r\n", iTotStorage);                    // Total storage size in disk
    	}
    	sprintf (pcBuffer,                "-------------------------------------------------------------------\r\n");

        // *** Send buffer to console (hyper terminal) ***
    	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
    	mask_event(pxCom, COM_SEND_END);
    	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    	tcName[strlen(tcName)-1]=0;                                                           // *** Unmount disk "/DISKNAME" ***
    	FS_unmount(tcName);
    }

    goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                                        // None-classified low level error
	_clrscr();                                                                                // Clear screen
	DisplayMedium(0, 0, "Processing Error");                                                  // Oops! error
    ttestall(0, 5*100);                                                                       // Delay 5s
lblEnd:
	if(pxCom)
	{
		fclose(pxCom);                                                                        // Close "com" channel
		pxCom=NULL;
	}
}



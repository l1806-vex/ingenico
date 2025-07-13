//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  CONFSOFTWARE.C                      (Copyright INGENICO 2011)
//============================================================================
//  Created :       13-May-2011     Kassovic
//  Last modified : 13-May-2011     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Describe the software configuration.
//  Application(s), Dll(s), Driver(s), Param(s), Key(s) and memory state.
//                                                                            
//  List of routines in file :  
//      ConfSoftware : Configuration regarding the software loaded.                                           
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
    /* */

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
static char tcBuffer[256+1];

//****************************************************************************
//                  void ConfSoftware(doubleword uiCom)
//  This function sent to a console (hyper-terminal) the configuration
//  regarding the software loaded inside the terminal.
//  1) Application(s) => App Name, App File, CRC, App Type, Loaded flag,
//                       App position, Ram/Flash used
//  2) Dll(s) => Dll Name, Dll File, CRC, Dll Type, Loaded flag, Dll position,
//               Ram/Flash used
//  3) Driver(s) => Driver Name, Driver File, Driver Type, Loaded flag,
//                  Driver position, Ram/Flash used
//  4) Param(s) => Param Name, Param File, Param Type, Loaded flag,
//                 Param position, Ram/Flash used
//  5) Key(s) => Key Name, Key File, Key Type, Loaded flag, Key position
//               Ram/Flash used
//  6) Memory state => Total Ram/Flash used, Size Ram, Free Ram,
//                     Size Flash, Free Flash (code+data)
//       ObjectGetNumber() : return the object number available for a given object type.
//       ObjectGetInfo() : get information about the object.
//       ObjectGetSize() : retrieve memory information of an object.
//       RamGetSize() : return RAM size.
//       FreeSpace() : return the free RAM space.
//       FS_AreaGetSize() : return size of flash area (CFS or DFS).
//       FS_AreaGetFreeSize() : return free size of a flash area (CFS or DFS).
//       FS_AreaGetGarbageSize() : return garbage size of a flash area (CFS or DFS).
//  This function has parameters.
//      uiCom (I-) : Communication channel.
//  This function has no return value.
//****************************************************************************

void ConfSoftware(doubleword uiCom)
{
	// Local variables
    // ***************
	FILE *pxCom=NULL;
	Telium_size_t uiLen;
	char tcDriver[24+1];
	object_type_t eType;
	object_info_t xInfo;
	object_size_t xSize;
	doubleword uiRamLength, uiFlashLength, uiTotalRamLength=0, uiTotalFlashLength=0;
	int iNbr, i;
	char* pcBuffer;
    int iRet;

    // Com channel initialization
    // **************************
	switch (uiCom)
	{
	case COM0:
		pxCom = fopen("COM0", "rw*"); CHECK(pxCom!=NULL, lblKO);                              // Open "com0" channel
	    iRet = format("COM0", 115200, 8, 1, NO_PARITY, EVEN, 0);  CHECK(iRet>=0, lblKO);      // Format the COM0 channel
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

    // Objects configuration (Applications, Dlls, Drivers, Parameter files, Key files)
    // *****************************************************************************
	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "###################################################################\r\n");
	pcBuffer += sprintf(pcBuffer, "#                   SOFTWARE CONFIGURATION                        #\r\n");
	sprintf(pcBuffer,             "###################################################################\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	eType = OBJECT_TYPE_APPLI;                                                                // Start by Application object first
    i=0;
    while(eType <= OBJECT_TYPE_KEY)                                                           // Finish by Key object
    {
    	iNbr = ObjectGetNumber(eType);                                                        // Object number available
    	while(i<iNbr)
    	{
    	    if (i==0)
    	    {
    	    	pcBuffer=tcBuffer;                                                            // Send which object to analyse
    	    	pcBuffer += sprintf (pcBuffer, "===================================================================\r\n");
    	    	switch (eType)
    	    	{
    	    	case OBJECT_TYPE_APPLI:  pcBuffer += sprintf(pcBuffer, "APPLICATION(S)\r\n"); break;
    	    	case OBJECT_TYPE_DLL:    pcBuffer += sprintf(pcBuffer, "DLL(S)\r\n");         break;
    	    	case OBJECT_TYPE_DRIVER: pcBuffer += sprintf(pcBuffer, "DRIVER(S)\r\n");      break;
    	    	case OBJECT_TYPE_PARAM:  pcBuffer += sprintf(pcBuffer, "PARAM(S)\r\n");       break;
    	    	default:                 pcBuffer += sprintf(pcBuffer, "KEY(S)\r\n");         break;
    	    	}
    	    	sprintf(pcBuffer,              "===================================================================\r\n");

        		// *** Send buffer to console (hyper terminal) ***
        		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
        		mask_event(pxCom, COM_SEND_END);
        		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
    	    }

    		ObjectGetInfo(eType, i, &xInfo);                                                  // Information about the object
    		ObjectGetSize(eType, xInfo.application_type, sizeof(object_size_t), &xSize);      // Memory about the object

    	    pcBuffer=tcBuffer;                                                                // Send full description of the object
    	    pcBuffer += sprintf(pcBuffer, "%s\r\n", xInfo.name);
    	    pcBuffer += sprintf(pcBuffer, "File: %s\r\n", xInfo.file_name);
    	    pcBuffer += sprintf(pcBuffer, "CRC: 0x%04X Type: 0x%04X Loaded: %d (%d)\r\n", xInfo.crc, xInfo.application_type, xInfo.loaded_flag, i);

    		// *** Send buffer to console (hyper terminal) ***
    		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
    		mask_event(pxCom, COM_SEND_END);
    		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    		uiRamLength = xSize.code_size + xSize.data_size + xSize.umalloc_size;             // Ram used by the object
    		uiFlashLength = xSize.flash_prog + xSize.flash_data;                              // Flash used by the object

    		pcBuffer=tcBuffer;                                                                // Send memory used by the object
    		pcBuffer += sprintf(pcBuffer, "RAM length: %i Code: %i Data: %i Dyn: %i\r\n", uiRamLength, xSize.code_size, xSize.data_size, xSize.umalloc_size);
    		pcBuffer += sprintf(pcBuffer, "FLASH length: %i Code: %i Data: %i\r\n", uiFlashLength, xSize.flash_prog, xSize.flash_data);
    	    sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

    		// *** Send buffer to console (hyper terminal) ***
    		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
    		mask_event(pxCom, COM_SEND_END);
    		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    		if (xInfo.loaded_flag == 1)
    			uiTotalRamLength += uiRamLength;
    		uiTotalFlashLength += uiFlashLength;
    		i++;
    	}
    	eType+=1;
    	i=0;
    }

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "===================================================================\r\n");
	pcBuffer += sprintf(pcBuffer, "MEMORY STATE\r\n");
	sprintf (pcBuffer,            "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;                                                                        // Send full Ram/Flash memory information
	pcBuffer += sprintf(pcBuffer, "Total length Ram: %i\r\n", uiTotalRamLength);
	pcBuffer += sprintf(pcBuffer, "Total length Flash: %i\r\n\r\n", uiTotalFlashLength);
	pcBuffer += sprintf(pcBuffer, "RAM Memory: %i RAM Free: %ld\r\n\r\n", RamGetSize(), FreeSpace());
	pcBuffer += sprintf(pcBuffer, "FLASH Memory: %i FLASH Free: %i\r\nCode Free: %i Data Free: %i\r\n",
									FS_AreaGetSize(FS_WO_ZONE_APPLICATION) + FS_AreaGetSize(FS_WO_ZONE_DATA),
									FS_AreaGetFreeSize(FS_WO_ZONE_APPLICATION) + FS_AreaGetFreeSize(FS_WO_ZONE_DATA),
									FS_AreaGetFreeSize(FS_WO_ZONE_APPLICATION),
									FS_AreaGetFreeSize(FS_WO_ZONE_DATA));
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                                        // None-classified low level error
	_clrscr();                                                                                // Clear screen
	DisplayMedium(0, 0, "Processing Error");                                                  // Oops! error
    ttestall(0, 5*100);                                                                       // Delay 5s
lblEnd:
	if(pxCom)
		fclose(pxCom);                                                                        // Close "com" channel
}



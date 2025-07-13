//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  MAPAPP.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       09-July-2012     Kassovic
//  Last modified : 09-July-2012     Kassovic
//  Module : TRAINING
//                                                                          
//  Purpose :                                                               
//  Supply access by integer key number to data by using the functions
//  appGet() and appPut(). It contains all the application parameters
//  saved inside none-volatile memory (DFS).
//                                                                            
//  List of routines in file :  
//      appReset : Reset none-volatile application parameters.
//      appPut : Store application parameter.
//      appGet : Retrieve application parameter.
//                            
//  File history :
//  070912-BK : File created
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
const char *getAppCmpDat(void){ return __DATE__;} // Return the date of compilation of the file Mapapp.c
const char *getAppCmpTim(void){ return __TIME__;} // Return the time of compilation of the file Mapapp.c

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
// Parameter row
// =============
typedef struct stParamRow
{
	word usKey;                // Parameter key
	word usLen;                // Parameter length
	void *pvDefault;           // Parameter default
} ST_PARAM_ROW;

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Parameter table
// ===============
static const ST_PARAM_ROW tzApp[appEnd-appBeg] = {
	{ appCmpDat,             lenCmpDat,            "" },                      // Compile date Mapapp.c
	{ appCmpTim,             lenCmpTim,            "" },                      // Compile time Mapapp.c

	{ appSerialItem,         lenSerialItem,        "\x00\x01\x00\x00\x08" },  // Com Port, Data Bits, Parity, Stop Bits, Baud Rate
	{ appSerialInit,         lenSerialInit,        "8N1115200" },             //              8         N        1         115200

	{ appModemItem,          lenModemItem,         "\x01\x00\x08" },          //   ,Data Bits, Parity,   ,Baud Rate
	{ appModemInit,          lenModemInit,         "T8N1115200" },            // T      8         N    1    115200
	{ appModemPabx,          lenModemPabx,         "" },                      // Pabx
	{ appModemPrefix,        lenModemPrefix,       "" },                      // Prefix
	{ appModemCountry,       lenModemCountry,      "" },                      // Country code
	{ appModemPhone,         lenModemPhone,        "0169012345" },            // Phone number

	{ appEthIpLocal,         lenEthIpLocal,        "192.168.1.2" },           // Local Ip Address
	{ appEthPort,            lenEthPort,           "23" },                    // Port number

	{ appGprsRequirePin,     lenGprsRequirePin,    "0" },                     // Pin required?
	{ appGprsApn,            lenGprsApn,           "internet-entreprise" },   // Apn
	{ appGprsUser,           lenGprsUser,          "orange" },                // User name
	{ appGprsPass,           lenGprsPass,          "orange" },                // Password
	{ appGprsIpRemote,       lenGprsIpRemote,      "77.196.251.113" },        // Remote Ip Address
	{ appGprsPort,           lenGprsPort,          "23" },                    // Port number

	{ appPppPabx,            lenPppPabx,           "" },                      // Pabx
	{ appPppPrefix,          lenPppPrefix,         "" },                      // Prefix
	{ appPppCountry,         lenPppCountry,        "" },                      // Country code
	{ appPppPhone,           lenPppPhone,          "0169012345" },            // Phone number
	{ appPppUser,            lenPppUser,           "Test" },                  // User name
	{ appPppPass,            lenPppPass,           "1234" },                  // Password
	{ appPppIpLocal,         lenPppIpLocal,        "192.168.1.4" },           // Local Ip Address
	{ appPppPort,            lenPppPort,           "23" }                     // Port number
};

static const char zAppTab[] = "appTab.par";

//****************************************************************************
//                          int appReset(void)
// This function creates "app" table (\PARAMDISK\appTab.par).
//  If the file already exist, delete it then re-create it.
//  Finally "app" table is built with parameters initialized to default value.
// This function has no parameters.
// This function has return value.
//	 >=0 : Initialization done (size of bytes reseted).
//   <0  : Initialization failed (FMG failed).
//****************************************************************************

int appReset (void)
{
	// Local variables 
    // ***************
	FMG_t_file_info xFileInfo;
	word usIdx;
	int iByteNbr=0, iRet;
	
    // Create "app" table
	// ******************
	iRet = FMG_CreateFile(PARAM_DISK, (char*)zAppTab, FMG_VARIABLE_LENGTH, FMG_WITH_CKECKSUM);
    CHECK((iRet==FMG_SUCCESS)||(iRet==FMG_FILE_ALREADY_EXIST), lblKO);

    if (iRet==FMG_FILE_ALREADY_EXIST)                    // File already exist?
    {
        iRet = FMG_DeleteFile(PARAM_DISK, (char*)zAppTab);
        CHECK(iRet==FMG_SUCCESS, lblKO);                 // Delete it
    	iRet = FMG_CreateFile(PARAM_DISK, (char*)zAppTab, FMG_VARIABLE_LENGTH, FMG_WITH_CKECKSUM);
        CHECK(iRet==FMG_SUCCESS, lblKO);                 // Re-create it
    }

	// Reset "app" table
	// *****************
	xFileInfo.eCreationType = FMGPathAndName;            // File type with Path and Name
    strcpy((char*)xFileInfo.ucFilePath, PARAM_DISK);     // \PARAMDISK
    strcpy((char*)xFileInfo.ucFileName, zAppTab);        // \appTab.par
    for (usIdx=0; usIdx<appEnd-appBeg; usIdx++)          // Build "app" table with parameters filled with default value
	{
    	CHECK(tzApp[usIdx].usKey==usIdx+appBeg, lblKO);  // Check if it is the right key

    	iByteNbr += (int)tzApp[usIdx].usLen;
    	iRet = FMG_AddRecord(&xFileInfo, tzApp[usIdx].pvDefault, (long)tzApp[usIdx].usLen, FMGMiddle, usIdx);
    	CHECK(iRet==FMG_SUCCESS, lblKO);
	}

    iRet = iByteNbr;                                     // Size of bytes reseted
	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                   // Initialization failed
	iRet=-1;
lblEnd:
    return iRet;
}

//****************************************************************************
//              int appPut(word usKey, void *pvDat, word usLen)
// This function stores the parameter related to the key into the appTab
//  file.
// This function has parameters.
//     (I-) usKey : Key from enum
//     (I-) pvDat : Parameter to be stored
//     (I-) usLen : Parameter length
// This function has return value.
//   >=0 : Storage done (size of bytes stored).
//   <0  : Storage failed (FMG failed).
//****************************************************************************

int appPut (word usKey, void *pvDat, word usLen)
{
	// Local variables 
    // ***************
	FMG_t_file_info xFileInfo;
	long lLength;
	int iRet;

	// Store parameter
	// ***************
	CHECK(tzApp[usKey-appBeg].usKey==usKey, lblKO);     // Check if it is the right key
	
	lLength = (long)tzApp[usKey-appBeg].usLen;
	if (lLength > usLen)
		lLength = (long)usLen;
	xFileInfo.eCreationType = FMGPathAndName;           // File type with Path and Name
    strcpy((char*)xFileInfo.ucFilePath, PARAM_DISK);    // \PARAMDISK
    strcpy((char*)xFileInfo.ucFileName, zAppTab);       // \appTab.par
	iRet = FMG_ModifyRecord(&xFileInfo, pvDat, lLength, FMGMiddle, usKey-appBeg);
	CHECK(iRet==FMG_SUCCESS, lblKO);                    // Store the parameter related to this key

	iRet = (int)lLength;                                // Size of bytes stored.
	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                  // Storage parameter failed
    iRet=-1;
lblEnd:
    return iRet;
}

//****************************************************************************
//              int appGet(word usKey, void *pvDat, word usLen)
// This function retrieves the parameter related to the key from the appTab
//  file.
// This function has parameters.
//     (I-) usKey : Key from enum
//     (-O) pvDat : Parameter to be retrieved
//     (I-) usLen : Parameter length
// This function has return value.
//   >=0 : Retrieve done (size of bytes retrieved)
//   <0  : Retrieve failed (FMG failed)
//****************************************************************************

int appGet (word usKey, void *pvDat, word usLen)
{
	// Local variables 
    // ***************
	FMG_t_file_info xFileInfo;
	long lLength;
	int iRet;

	// Retrieve parameter
	// ******************
	CHECK(tzApp[usKey-appBeg].usKey==usKey, lblKO);

	memset(pvDat, 0, usLen);
    lLength = (long) tzApp[usKey-appBeg].usLen;
    if (lLength > usLen)
    	lLength = (long)usLen;
	xFileInfo.eCreationType = FMGPathAndName;            // File type with Path and Name
    strcpy((char*)xFileInfo.ucFilePath, PARAM_DISK);     // \PARAMDISK
    strcpy((char*)xFileInfo.ucFileName, zAppTab);        // \appTab.par
	iRet = FMG_ReadRecord(&xFileInfo, pvDat, &lLength, FMGMiddle, usKey-appBeg);
	CHECK(iRet==FMG_SUCCESS, lblKO);	                 // Retrieve the parameter related to this key

	iRet = (int)lLength;                                 // Size of bytes retrieved.
	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                   // Retrieve parameter failed
    iRet=-1;
lblEnd:
    return iRet;
}

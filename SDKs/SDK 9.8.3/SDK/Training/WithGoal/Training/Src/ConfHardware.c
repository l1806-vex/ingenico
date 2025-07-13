//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  CONFHARDWARE.C                      (Copyright INGENICO 2012)
//============================================================================
//  Created :       17-July-2012     Kassovic
//  Last modified : 17-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//             *** Describe the hardware configuration ***
//          Transmission by serial communication COM0/COM5/COM_EXT
//             Test done with Hyper-terminal (8-N-1-115200)
//                                                                        
//  List of routines in file :  
//      ProductName : Terminal product name.
//      ConfHardware : Hardware configuration of the terminal.                                          
//                            
//  File history :
//  071712-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
// !!! Warning : Functions ONLY supported for Telium 1&2 and will be replaced
// or removed for next product Telium 3 coming later
#define _DEPRECATED_SYSTEMFIOCTL_SDK96_
// SYS_FIOCTL_IS_INGETRUST => Test if terminal is Ingetrusted.
// SYS_FIOCTL_GET_INGETRUST_TYPE => Get Ingetrust certificate type.
// SYS_FIOCTL_GET_SECURITY_MODE => Get the security mode.
// SYS_FIOCTL_SECURITY_GET_FALLBACK_DISABLED => Test software version fall back mode
// SYS_FIOCTL_SECURITY_GET_VARID_CHECKING => Test software varID checking mode.
// SYS_FIOCTL_SECURITY_GET_SCHEME_VARID_CHECKING => Test scheme varID checking mode
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
static const char zTrue[] = "YES";
static const char zFalse[] = "NO";
static const char zFast[] = "YES (FAST)";
static const char zSlow[] = "YES (SLOW)";
static const char zV34[] = "YES (V34)";
static const char zColor[] = "COLOR";
static const char z2Lines[] = "2 LINES";
static const char z128x64[] = "128x64";
static const char z128x128[] = "128x128";
static const char zTTL[] = "YES (TTL)";

static char tcBuffer[256+1];
static char tcName[24+1];

//****************************************************************************
//                     char* ProductName (void)
//  This function returns the product terminal name.
//  This function has no parameters.
//  This function has return value.
//    A string buffer regarding the product name.
//****************************************************************************

static char* ProductName(void)
{
	// Local variables
    // ***************
	byte ucProduct;
	byte ucRange;

	// Return the product name
	// ***********************
	ucRange=PSQ_Get_product_type(&ucProduct);
	switch(ucProduct)
	{
	case TYPE_TERMINAL_SMART :      strcpy(tcName, "EFTSMART"); break;  // 2 EFTsmart
	case TYPE_TERMINAL_EFT30F:      strcpy(tcName, "EFT30F");   break;  // 3 EFT30F
	case TYPE_TERMINAL_EFT30P:      strcpy(tcName, "EFT30P");   break;  // 4 EFT30plus
	case TYPE_TERMINAL_TWIN30:                                          // 5
		switch(ucRange)
		{
		case TYPE_TERMINAL_TWIN30:  strcpy(tcName, "TWIN30");   break;  // 55 TWIN30
		case TYPE_TERMINAL_TWIN33:  strcpy(tcName, "TWIN33");   break;  // 56 TWIN33
		case TYPE_TERMINAL_TWIN32:  strcpy(tcName, "TWIN32");   break;  // 57 TWIN32
		default:                    strcpy(tcName, "UNKNOWN");  break;
		}
		break;
	case TYPE_TERMINAL_EFT930:                                          // 6
		switch(ucRange)
		{
		case TYPE_TERMINAL_EFT930G: strcpy(tcName, "EFT930G");  break;  // 67 EFT930G
		case TYPE_TERMINAL_EFT930B: strcpy(tcName, "EFT930B");  break;  // 68 EFT930B
		case TYPE_TERMINAL_EFT930F: strcpy(tcName, "EFT930F");  break;  // 69 EFT930F
		case TYPE_TERMINAL_EFT930W:	strcpy(tcName, "EFT930W");  break;  // 65 EFT930W
		case TYPE_TERMINAL_EFT930P: strcpy(tcName, "EFT930P");  break;  // 66 EFT930P
		default:                    strcpy(tcName, "UNKNOWN");  break;
		}
		break;
	case TYPE_TERMINAL_ML30:                                            // 1
		switch(ucRange)
		{
		case TYPE_TERMINAL_ML30:    strcpy(tcName, "ML30");     break;  // 11 ML30
		case TYPE_TERMINAL_SPM:     strcpy(tcName, "SPM");      break;  // 12 SPM
		case TYPE_TERMINAL_IPP320:  strcpy(tcName, "IPP320");   break;  // 13 IPP320
		case TYPE_TERMINAL_IPP350:  strcpy(tcName, "IPP350");   break;  // 14 IPP350
		case TYPE_TERMINAL_IPP480:  strcpy(tcName, "IPP480");   break;  // 16 IPP480
		default:                    strcpy(tcName, "UNKNOWN");  break;
		}
		break;
	case TYPE_TERMINAL_CAD30:       strcpy(tcName, "CAD30");    break;  // 7 CAD30
	case TYPE_TERMINAL_MR40:        strcpy(tcName, "MR40");     break;  // 9 MR40
	case TYPE_TERMINAL_X07:                                             // 8
		switch(ucRange)
		{
		case TYPE_TERMINAL_IWL220:  strcpy(tcName, "IWL220");   break;  // 83 IWL220
		case TYPE_TERMINAL_IWL250:  strcpy(tcName, "IWL250");   break;  // 82 IWL250
		case TYPE_TERMINAL_ICT220:  strcpy(tcName, "ICT220");   break;  // 88 ICT220
		case TYPE_TERMINAL_ICT250:  strcpy(tcName, "ICT250");   break;  // 87 ICT250
		case TYPE_TERMINAL_ICT280:  strcpy(tcName, "ICT280");   break;  // 86 ICT280
		case TYPE_TERMINAL_ISC350:  strcpy(tcName, "ISC350");   break;  // 85 ISC350
		case TYPE_TERMINAL_ISC250:  strcpy(tcName, "ISC250");   break;  // 84 ISC250
		default:                    strcpy(tcName, "UNKNOWN");  break;
		}
		break;
	default:                        strcpy(tcName, "UNKNOWN");  break;
	}

	return tcName;
}

//****************************************************************************
//                    void ConfHardware(doubleword uiCom)
//  This function sent to a console (hyper-terminal) the configuration regarding
//  the hardware of the terminal.
//   Similar to the configuration ticket from Manager:
//   (TELIUM MANAGER-Consultation-Configuration-Hardware)
//  1) GENERAL INFORMATIONS
//     Product Name, Product Id, Serial Number, Product Code, Constructor Code,
//     Product Ref, Manufacturing, Coupler Hardware and Software.
//  2) ACTIVATION INFORMATIONS
//     First activation, SXX extension, Profile ID, Ingetrust Security,
//     ZKA protection, Fallback, Security VARID and Scheme VARID.
//  3) MEMORY INFORMATIONS
//     Flash Memory and RAM Memory.
//  4) HARDWARE INFORMATIONS
//     -- Miscellaneous --
//     Printer, Display, Buzzer, Modem, Portable, Tilto, MMC, Cless, Hardware LEDS,
//     -- Serial links --
//     COM0, COM1, COM2, COM3, COMN and COMU.
//     -- USB Controller --
//     USB Host and USB Device.
//     -- MORPHO Device --
//     Biometric
//     -- Radio Device --
//     GPRS, CDMA, Bluetooth and Wifi.
//     -- Swipe Readers --
//     ISO1, ISO2, ISO3, CAM0, CAM1 and CAM2.
//     -- CAM & SAM Readers --
//     SAM1, SAM2, SAM3 and SAM4.
//  5) SOFTWARE INFORMATIONS
//     Country Code, Firmware Version, Booster Type, Booster and Thunder versions.
//      - GetConfiguration() : return standard hardware configuration.
//      - SystemFioctl() : return specific hardware configuration.
//      - IsXXX() : check hardware configuration.
//      - fioctl() : call low level OEMC driver.
//      - GetMacAddress() : return the MAC address of the terminal.
//      - HWCNF_EthernetGetCurrentParameters() : return Ethernet setting.
//      - BoosterType() : return Booster Type (1-2-3).
//      - RamGetSize() : return RAM size.
//      - FreeSpace() : return the free RAM space.
//      - FS_AreaGetSize() : return size of flash area (CFS or DFS).
//      - FS_AreaGetFreeSize() : return free size of a flash area (CFS or DFS).
//      - FS_AreaGetGarbageSize() : return garbage size of a flash area (CFS or DFS).
//  This function has parameters.
//    uiCom (I-) : Communication channel.
//  This function has no return value.
//****************************************************************************

void ConfHardware(doubleword uiCom)
{
	// Local variables
    // ***************
	FILE *pxCom=NULL;
	Telium_size_t uiLen;
	char tcDriver[24+1];
	int iSizeFlash, iSizeRam;
	hterm_t *pxHterm;
	ip_param_s xEth;
	FILE *pxGprs=NULL;
	T_DGPRS_GET_INFORMATION xInfoGprs;
	FILE *pxModem=NULL;
	MODEM_FIOCTL_IDENT_S xInfoModem;
	char *pcFlag, *pcV34;
	char tcActivation[12+1];
	char tcProfile[6+1];  // 6 OK!!! No, 7 OK yes => Buffer should be 3 but wait for 7
	char tcFirmware[4+1];
	char tcMac[6+1];
	char tcSmcHard[4+1], tcSmcSoft[4+1];
	char tcThunder[4+1], tcBooster[4+1];
	SYS_FIOCTL_REPUDIATION_INFO_GET_S xRepudiation;
	char* pcBuffer;
    int iRet;

    // Com channel initialization
    // **************************
	switch (uiCom)
	{
	case COM0:
		pxCom = fopen("COM0", "rw*");
		CHECK(pxCom!=NULL, lblKO);                                  // Open "com0" peripheral
	    iRet = format("COM0", 115200, 8, 1, NO_PARITY, EVEN, 0);    // Format COM0 channel
	    CHECK(iRet>=0, lblKO);
		break;
	case COM5:
		pxCom = fopen("COM5", "rw*");                               // Open "com5" peripheral
		CHECK(pxCom!=NULL, lblKO);
		break;
	case COM_EXT:                                                   // Open "converter USB->RS232" peripheral
		// Telium supports the following drivers:
		// - "COM_KEYSPAN" (Keyspan USA19HS)
		// - "COM_SL" (SiliconLabs CP2102)
		// - "COM20" (Prolific 2303)
		// - "COM21" (FTDI)
		// - "COM_MGBX" (Generic Magic Box)
		// With event generated COM_EXT
		pxCom = OpenConverter(tcDriver, sizeof(tcDriver));
		CHECK(pxCom!=NULL, lblKO);
	    iRet = format(tcDriver, 115200, 8, 1, NO_PARITY, EVEN, 0);  // Format converter channel
	    CHECK(iRet>=0, lblKO);
		break;
	default:
		goto lblKO;
	}
	GL_Dialog_Message(xGoal, NULL, "Configuration Hardware\nTransmitting...", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);

    // Hardware configuration
    // **********************
	pxHterm = GetConfiguration();                                   // Equivalent to => lire_etat_materiel(&xHterm);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "###################################################################\r\n");
	pcBuffer += sprintf(pcBuffer, "#                   HARDWARE CONFIGURATION                        #\r\n");
	sprintf(pcBuffer,             "###################################################################\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "===================================================================\r\n");
	pcBuffer += sprintf(pcBuffer, "GENERAL INFORMATIONS\r\n");
	sprintf(pcBuffer,             "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcBuffer += sprintf(pcBuffer, "Product Name       : %s\r\n", ProductName());                 // Product Name
	pcBuffer += sprintf(pcBuffer, "Product Id         : %02x%02x%02x%02x\r\n"                    // Product ID
			                      "Serial Number      : %02x%02x%02x%02x\r\n",                   // Serial Number
											 pxHterm->terminal_number[0],
											 pxHterm->terminal_number[1],
											 pxHterm->terminal_number[2],
											 pxHterm->terminal_number[3],
											 pxHterm->terminal_number[4],
											 pxHterm->terminal_number[5],
											 pxHterm->terminal_number[6],
											 pxHterm->terminal_number[7]);
	sprintf(pcBuffer,             "Product Code       : %.3s\r\n", pxHterm->product_code);       // Product Code

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "Constructor Code   : %.8s\r\n", pxHterm->constructor_code);   // Constructor Code
	pcBuffer += sprintf(pcBuffer, "Product Ref        : %.12s\r\n", pxHterm->product_reference); // Product Reference
	pcBuffer += sprintf(pcBuffer, "Manufacturing      : %.8s\r\n", pxHterm->manufacturing_date); // Manufacturing Date
	memset(tcSmcHard, 0, sizeof(tcSmcHard));
	SystemFioctl(SYS_FIOCTL_GET_ICC_READER_HARD_VERSION, tcSmcHard);                             // Smc Reader Hard Info
	memset(tcSmcSoft, 0, sizeof(tcSmcSoft));
	SystemFioctl(SYS_FIOCTL_GET_ICC_READER_SOFT_VERSION, tcSmcSoft);                             // Smc Reader Software Info
	sprintf(pcBuffer,             "Coupler Hardware   : %.4s\r\n"
								  "Coupler Software   : %.4s\r\n",
					                         tcSmcHard, tcSmcSoft);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "===================================================================\r\n");
	pcBuffer += sprintf(pcBuffer, "ACTIVATION INFORMATIONS\r\n");
	sprintf(pcBuffer,             "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	memset(tcActivation, 0, sizeof(tcActivation));
	SystemFioctl(SYS_FIOCTL_BOOSTER_GET_ACTIVATION_MANUFACTURING_DATE, tcActivation);            // First Activation Date
	pcBuffer += sprintf(pcBuffer, "First Activation   : %s\r\n", tcActivation);
    memset (tcProfile, 0, sizeof(tcProfile));
    SystemFioctl(SYS_FIOCTL_BOOSTER_GET_ACTIVATION_PROFILE, tcProfile);                          // Terminal Profile
	pcBuffer += sprintf(pcBuffer, "SXX Extension      : %s\r\n", tcProfile);
	memset (&xRepudiation, 0, sizeof(SYS_FIOCTL_REPUDIATION_INFO_GET_S));
	SystemFioctl(SYS_FIOCTL_REPUDIATION_INFO_GET, &xRepudiation);  					             // Repudiation table
	pcBuffer += sprintf(pcBuffer, "Profile ID         : [%04d-%03d]\r\n", xRepudiation.Repudiation_Number1, xRepudiation.Repudiation_Number2);
	pcFlag = (char*)zFalse;
	iRet = SystemFioctl(SYS_FIOCTL_IS_INGETRUST, (void*)NULL);                                   // Ingetrusted mode
	if (iRet == 1)
	{
		iRet = SystemFioctl(SYS_FIOCTL_GET_INGETRUST_TYPE, (void*)NULL);
		switch (iRet)
		{
		case INGETRUST_TYPE_UNKNOWN: pcFlag="UNKNOWN"; break;
		case INGETRUST_TYPE_PKIv1:   pcFlag="PKIv1";   break;
		case INGETRUST_TYPE_PKIv3:   pcFlag="PKIv3";   break;
		default:                     pcFlag="NONE";    break;
		}
	}
	pcBuffer += sprintf(pcBuffer, "INGETRUST Security : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;
	iRet = SystemFioctl(SYS_FIOCTL_GET_SECURITY_MODE, (void*)NULL);                              // Security ZKA mode
	if (iRet == 1)
		pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "ZKA Protection     : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;
	iRet = SystemFioctl(SYS_FIOCTL_SECURITY_GET_FALLBACK_DISABLED, (void*)NULL);                 // Fallback mode
	if (iRet == 0)
		pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "Fallback           : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;
	iRet = SystemFioctl(SYS_FIOCTL_SECURITY_GET_VARID_CHECKING, (void*)NULL);                    // Security VARID
	if (iRet == 1)
		pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "Security VARID     : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;
	iRet = SystemFioctl(SYS_FIOCTL_SECURITY_GET_SCHEME_VARID_CHECKING, (void*)NULL);             // Scheme VARID
	if (iRet == 1)
		pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "Scheme VARID       : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "===================================================================\r\n");
	pcBuffer += sprintf(pcBuffer, "MEMORY INFORMATIONS\r\n");
	sprintf(pcBuffer,             "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;                                                                            // Flash & Ram sizes
	iSizeFlash = (pxHterm->total_flash[3]*256*256*256) + (pxHterm->total_flash[2]*256*256) + (pxHterm->total_flash[1]*256) + pxHterm->total_flash[0];
	iSizeRam = (pxHterm->total_ram[3]*256*256*256) + (pxHterm->total_ram[2]*256*256) + (pxHterm->total_ram[1]*256) + pxHterm->total_ram[0];
	pcBuffer += sprintf(pcBuffer, "FLASH Memory       : %iKb\r\n", iSizeFlash/1024);
	sprintf(pcBuffer,             "RAM Memory         : %iKb\r\n", iSizeRam/1024);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "===================================================================\r\n");
	pcBuffer += sprintf(pcBuffer, "HARDWARE INFORMATIONS\r\n");
	sprintf(pcBuffer,             "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "Miscellaneous\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcFlag = (char*)zFalse;                                                                      // Printer
    if (IsPrinter() == 1)
    {
    	if (IsSlowPrinter() == 1)
    		pcFlag = (char*)zSlow;    // Slow
    	else
    		pcFlag = (char*)zFast;    // Fast
    }
	pcBuffer += sprintf(pcBuffer, "PRINTER            : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                      // Display
    if (IsColorDisplay() == 1)
    	pcFlag = (char*)zColor;       // Color
    else
    {
    	pcFlag = (char*)z2Lines;      // 2 lines
    	if (IsSmallDisplay() == 1)
    		pcFlag = (char*)z128x64;  // 128x64
    	if (IsLargeDisplay() == 1)
    		pcFlag = (char*)z128x128; // 128x128
    }
	pcBuffer += sprintf(pcBuffer, "DISPLAY            : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                      // Buzzer
    if (IsBUZZER() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "BUZZER             : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // Modem
	pcV34 = (char*)"";
    if (IsMODEM() == 1)
    {
    	pxModem = fopen("MODEM", "r*");
    	CHECK(pxModem!=NULL, lblKO);

    	memset(&xInfoModem, 0, sizeof(MODEM_FIOCTL_IDENT_S));
    	iRet = fioctl(MODEM_FIOCTL_IDENT, &xInfoModem, pxModem);
    	CHECK(iRet==0, lblKO);

    	switch(xInfoModem.manufacturer)
    	{
    	case MODEM_NETBRICKS: pcFlag = "NETBRICKS";  break;  // Modem Netbricks (Soft Modem)
    	case MODEM_MOTOROLA:  pcFlag = "MOTOROLA";   break;  // Modem Motorola (Soft Modem)
    	case MODEM_CONEXANT:  pcFlag = "CONEXANT";   break;  // Modem Conexant (Hard Modem)
    	default:              pcFlag = (char*)zTrue; break;
    	}

    	if (IsModemV34() == 1)
    		pcV34 = (char*)zV34; // V34
   }
	sprintf(pcBuffer,             "MODEM              : %s %s\r\n", pcFlag, pcV34);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;                                                                       // Portable
    if (IsPortable() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "PORTABLE           : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                       // Tilto
    if (IsTILTO() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "TILTO              : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                       // MMC
    if (IsMMC() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "MMC                : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                       // Contactless
    if (IsCless() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "CLESS              : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                       // Hardware leds
    if (IsLedOnDisplay() == 0)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "HARDWARE LEDS      : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "Serial Links\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;                                                                         // RS232 COM0
    if (IsCOM0() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "COM0               : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                         // RS232/TTL COM1
    if (IsCOM1() == 1)
    {
    	if (IsCOM1RS232() == 1)
    		pcFlag = (char*)zTrue; // Com1 RS232
    	if (IsCOM1Pinpad() == 1)
    		pcFlag = (char*)zTTL;  // Com1 TTL
    }
	pcBuffer += sprintf(pcBuffer, "COM1               : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                         // RS232 COM2
    if (IsCOM2() == 1)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "COM2               : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;                                                                         // RS232 COM3
    if (IsCOM3() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "COM3               : %s\r\n", pcFlag);
    pcFlag =  (char*)zFalse;                                                                        // RS232 COMN
    if (IsCOMN() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "COMN               : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                         // RS232 COMU
    if (IsCOMU() == 1)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "COMU               : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "USB Controler\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;                                                                         // USB Host
    if (IsUsbHost() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "USB HOST           : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                         // USB Slave
    if (IsUsbSlave() == 1)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "USB DEVICE         : %s\r\n", pcFlag);
    // USB BASE MISSING

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "MORPHO Device\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;                                                                          // Biometric
    if (IsBIO() == 1)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "BIO                : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "RADIO Device\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    if (IsRadio() == 1)
    {
    	if (IsRadioGPRS() == 1)                                                                      // GPRS
    	{
    		sprintf(tcBuffer,     "GPRS               : YES\r\n");

    		// *** Send buffer to console (hyper terminal) ***
    		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
    		mask_event(pxCom, COM_SEND_END);
    		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

           	if (IsGPRS() != 0)
        	{
        	    pxGprs = stdperif((char*)"DGPRS", NULL);
        		CHECK(pxGprs!=NULL, lblKO);

        		memset(&xInfoGprs, 0, sizeof(T_DGPRS_GET_INFORMATION));
        		iRet = fioctl(DGPRS_FIOCTL_GET_INFORMATION, &xInfoGprs, pxGprs);
        		CHECK(iRet==0, lblKO);

        		pcBuffer=tcBuffer;
        		pcBuffer += sprintf(pcBuffer, "    Module Version : %s\r\n"             // Version
								              "    Imei Number    : %s\r\n"             // Imei
								              "    Sim ID         : %s\r\n",            // Id
									               xInfoGprs.module_software_version,
									               xInfoGprs.module_imei_number,
									               xInfoGprs.simIccId);
        		sprintf(pcBuffer,             "    Network        : %s\r\n"             // Network
								              "    Provider       : %s\r\n",            // Provider
									               xInfoGprs.network_name,
									               xInfoGprs.sim_provider);

        		// *** Send buffer to console (hyper terminal) ***
        		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
        		mask_event(pxCom, COM_SEND_END);
        		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
        	}
    	}
    	else
    	{
    		sprintf(tcBuffer,         "GPRS               : NO\r\n");

    		// *** Send buffer to console (hyper terminal) ***
    		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
    		mask_event(pxCom, COM_SEND_END);
    		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
    	}

    	pcBuffer=tcBuffer;
    	pcFlag = (char*)zFalse;
    	if (IsRadioCDMA() == 1)
    		pcFlag = (char*)zTrue;                                                                   // CDMA
		pcBuffer += sprintf(pcBuffer, "CDMA               : %s\r\n", pcFlag);
    	pcFlag = (char*)zFalse;
    	if (IsBT() == 1)
    		pcFlag = (char*)zTrue;                                                                   // Bluetooth
		pcBuffer += sprintf(pcBuffer, "BLUETOOTH          : %s\r\n", pcFlag);
    	pcFlag = (char*)zFalse;
    	if (IsRadioWifi() == 1)
    		pcFlag = (char*)zTrue;                                                                   // Wifi
		sprintf(pcBuffer,             "WIFI               : %s\r\n", pcFlag);

		// *** Send buffer to console (hyper terminal) ***
		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
		mask_event(pxCom, COM_SEND_END);
		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
    }
	else
	{
		sprintf(tcBuffer,             "RADIO              : NO\r\n");

		// *** Send buffer to console (hyper terminal) ***
		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
		mask_event(pxCom, COM_SEND_END);
		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
	}

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "Ethernet Controler\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	if (IsETHERNET() == 1)                                                                    // Ethernet
	{
		pcBuffer=tcBuffer;
		if (IsRadioETHERNET() == 1)
			pcBuffer += sprintf(pcBuffer, "ETHERNET           : YES (Terminal)\r\n");         // Ethernet interface inside terminal
		else
			pcBuffer += sprintf(pcBuffer, "ETHERNET           : YES (Base)\r\n");             // Ethernet interface inside base
		memset(tcMac, 0, sizeof(tcMac));
		HWCNF_EthernetGetMacAddress(tcMac);                                                   // Mac Address
		pcBuffer += sprintf(pcBuffer, "    Mac Address    : %02X:%02X:%02X:%02X:%02X:%02X\r\n", tcMac[0], tcMac[1], tcMac[2], tcMac[3], tcMac[4], tcMac[5]);
		memset(&xEth, 0, sizeof(ip_param_s));
		iRet = HWCNF_EthernetGetCurrentParameters(&xEth, 0); CHECK(iRet==0, lblKO);
		pcBuffer += sprintf(pcBuffer, "    IP Address     : %s\r\n", UintToIp(xEth.addr));    // Ip
		sprintf(pcBuffer,             "    Netmask        : %s\r\n", UintToIp(xEth.netmask)); // Netmask

		// *** Send buffer to console (hyper terminal) ***
		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
		mask_event(pxCom, COM_SEND_END);
		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

		pcBuffer=tcBuffer;
		pcBuffer += sprintf(pcBuffer, "    Gateway        : %s\r\n", UintToIp(xEth.gateway)); // Gateway
		pcBuffer += sprintf(pcBuffer, "    DNS1           : %s\r\n", UintToIp(xEth.dns1));    // Dns1
		sprintf(pcBuffer,             "    DNS2           : %s\r\n", UintToIp(xEth.dns2));    // Dns2

		// *** Send buffer to console (hyper terminal) ***
		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
		mask_event(pxCom, COM_SEND_END);
		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
	}
	else
	{
		sprintf(tcBuffer,             "ETHERNET           : NO\r\n");

		// *** Send buffer to console (hyper terminal) ***
		uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
		mask_event(pxCom, COM_SEND_END);
		iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);
	}

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "SWIPE Readers\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
    pcFlag = (char*)zFalse;                                                                      // ISO1 reader
    if (IsISO1() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "ISO1               : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // ISO2 reader
    if (IsISO2() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "ISO2               : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // ISO3 reader
    if (IsISO3() == 1)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "ISO3               : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "-------------------------------------------------------------------\r\n");
	pcBuffer += sprintf(pcBuffer, "CAM-SAM Readers\r\n");
	sprintf(pcBuffer,             "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcFlag = (char*)zFalse;                                                                      // CAM0 reader
    if (IsCAM1() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "CAM0               : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // CAM1 reader
    if (IsCAM2() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "CAM1               : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // CAM2 reader
    if (IsCAM3() == 1)
    	pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "CAM2               : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcFlag = (char*)zFalse;                                                                      // SAM0 reader
    if (IsSAM1() == 1)
    	pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "SAM1               : %s\r\n", pcFlag);
    pcFlag = (char*)zFalse;                                                                      // SAM1 reader
	if (IsSAM2() == 1)
		pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "SAM2               : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // SAM3 reader
	if (IsSAM3() == 1)
		pcFlag = (char*)zTrue;
	pcBuffer += sprintf(pcBuffer, "SAM3               : %s\r\n", pcFlag);
	pcFlag = (char*)zFalse;                                                                      // SAM4 reader
	if (IsSAM4() == 1)
		pcFlag = (char*)zTrue;
	sprintf(pcBuffer,             "SAM4               : %s\r\n", pcFlag);

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf(pcBuffer, "===================================================================\r\n");
	pcBuffer += sprintf(pcBuffer, "SOFTWARE INFORMATIONS\r\n");
	sprintf(pcBuffer,             "===================================================================\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

	pcBuffer=tcBuffer;
	pcBuffer += sprintf (pcBuffer, "Country Code       : %02d%02d\r\n",                          // Country code
			                             pxHterm->country_code[1],
			                             pxHterm->country_code[0]);
    memset (tcFirmware, 0, sizeof(tcFirmware));
	SystemFioctl(SYS_FIOCTL_GET_SECURITY_FIRMWARE_ID, tcFirmware);                               // Get firmware version
	pcBuffer += sprintf (pcBuffer, "Firmware Version   : %s\r\n", tcFirmware);
	iRet = BoosterType();                                                                        // Booster type
	pcBuffer += sprintf (pcBuffer, "Booster type       : %d\r\n", iRet);
	memset(tcBooster, 0, sizeof(tcBooster));
	SystemFioctl(SYS_FIOCTL_BOOSTER_GET_ROM_VERSION, tcBooster);                                 // Booster version
	memset(tcThunder, 0, sizeof(tcThunder));
	SystemFioctl(SYS_FIOCTL_THUNDER_GET_ROM_VERSION, tcThunder);                                 // Thunder version
	pcBuffer += sprintf (pcBuffer, "Booster Version    : %.4s\r\n"
			                       "Thunder Version    : %.4s\r\n",
			                              tcBooster,
			                              tcThunder);
	sprintf(pcBuffer,              "-------------------------------------------------------------------\r\n");

	// *** Send buffer to console (hyper terminal) ***
	uiLen = fwrite((void*)tcBuffer, 1, strlen(tcBuffer), pxCom); CHECK(uiLen>0, lblKO);
	mask_event(pxCom, COM_SEND_END);
	iRet = ttestall(uiCom, 5*100); CHECK(iRet!=0, lblKO);

    goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                                           // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);                                                                // Delay 5s
lblEnd:
	if (pxModem)
		fclose(pxModem);                                                                         // Close "modem" peripheral

	if(pxCom)
		fclose(pxCom);                                                                           // Close "com" peripheral
}



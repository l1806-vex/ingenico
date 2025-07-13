#include "basearm.h"

#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
#define NUMBER_OF_ITEMS(a) (sizeof(a)/sizeof((a)[0]))

#define WAIT_RESPONSE  101

#define PARAM_DISK   "PARAMDISK"

// Data base keys
// ==============
enum
{
	appBeg=0,      // Application parameter keys (Record)
};

// Application Parameters keys
// ===========================
enum
{
	appCmpDat=appBeg,    // Compile date Mapapp.c     Oct 24 2011
	appCmpTim,           // Compile time Mapapp.c     01:12:49

	appSerialItem,       // Com Port, Data Bits, Parity, Stop Bits, Baud Rate
	appSerialInit,       //              8         N        1         115200

	appModemItem,        //   ,Data Bits, Parity,   ,Baud Rate
	appModemInit,        // T      8         N    1    115200
	appModemPabx,        // Pabx
	appModemPrefix,      // Prefix
	appModemCountry,     // Country code
	appModemPhone,       // Phone number

	appEthIpLocal,       // Local Ip Address
	appEthPort,          // Port number

	appGprsRequirePin,   // Pin required?
	appGprsApn,          // Apn
	appGprsUser,         // User name
	appGprsPass,         // Password
	appGprsIpRemote,     // Remote Ip Address
    appGprsPort,         // Port number

	appPppPabx,          // Pabx
	appPppPrefix,        // Prefix
	appPppCountry,       // Country code
	appPppPhone,         // Phone number
	appPppUser,          // User name
	appPppPass,          // Password
    appPppIpLocal,       // Local Ip Address
	appPppPort,          // Port number

	appEnd
};

// Parameters length
// =================
enum
{
    lenCmpDat = 11,
    lenCmpTim = 8,

	lenSerialItem = 5,
	lenSerialInit = 16,

	lenModemItem = 3,
	lenModemInit = 16,
	lenModemPabx = 4,
	lenModemPrefix = 4,
	lenModemCountry = 3,
	lenModemPhone = 16,

	lenEthIpLocal = 15,
	lenEthPort = 5,

	lenGprsRequirePin = 1,
	lenGprsPin = 8,
	lenGprsPuk = 8,
	lenGprsApn = 30,
	lenGprsUser = 30,
	lenGprsPass = 30,
	lenGprsIpRemote = 15,
	lenGprsPort = 5,

	lenPppPabx = 4,
	lenPppPrefix = 4,
	lenPppCountry = 3,
	lenPppPhone = 16,
	lenPppUser = 30,
	lenPppPass = 30,
	lenPppIpLocal = 15,
	lenPppPort = 5,

	lenAppEnd
};

// Mapapp.c
// ========
int appReset(void);
int appPut(word usKey, void *pvDat, word usLen);
int appGet(word usKey, void *pvDat, word usLen);

// LL GPRS Status 
#define LL_STATUS_GPRS_NO_SIM                 LL_ERRORS+10
#define LL_STATUS_GPRS_ERR_SIM_LOCK           LL_ERRORS+9
#define LL_STATUS_GPRS_ERR_PPP                LL_ERRORS+8
#define LL_STATUS_GPRS_ERR_UNKNOWN            LL_ERRORS+7

// LL ETHERNET Status
#define LL_STATUS_ETH_AVAILABLE               LL_ERRORS+20
#define LL_STATUS_ETH_NO_DEFAULT_ROUTE        LL_ERRORS+19
#define LL_STATUS_ETH_NOT_PLUGGED             LL_ERRORS+18
#define LL_STATUS_ETH_BASE_NOT_READY          LL_ERRORS+17
#define LL_STATUS_ETH_OUT_OF_BASE             LL_ERRORS+16

// LL PHYSICAL Status
#define LL_STATUS_PHY_PERIPHERAL_BUSY         LL_ERRORS+30
#define LL_STATUS_PHY_PERIPHERAL_OUT_OF_BASE  LL_ERRORS+31
#define LL_STATUS_PHY_CONVERTER_NOT_PLUGGED   LL_ERRORS+32

// LL BLUETOOTH Status
#define LL_STATUS_BT_NO_BASE_ASSOCIATED		  LL_ERRORS+40
#define LL_STATUS_BT_PERIPHERAL_NOT_AVAILABLE LL_ERRORS+41
#define LL_STATUS_BT_PERIPHERAL_BUSY		  LL_ERRORS+42
#define LL_STATUS_BT_BASE_NOT_AVAILABLE		  LL_ERRORS+43

void Display(void);
void Printer(void);
void Keyboard(void);
void IsoError(int iSta, char *pcTrk);
void Magnetic(void);
void Smart(void);
void PromptSerial(void);
void ComSerial(void);
void PromptModem(void);
void ComModem(void);
void ComUSB(void);
void PromptEthernet(void);
void ComEthernet(void);
void PromptGPRS(void);
void ComGPRS(void);
void PromptPPP(void);
void ComPPP(void);
void VFSWrite(int VFSType);
void VFSRead(int VFSType);
void VFSDelete(int VFSType);
void Buzzer(void); 
void Backlight(void);
void WriteInRam(byte ucMsgNbr);
void ReadFromRam(void);
void Task(void);
void Delay(void);
int TimerStart(byte ucTimerNbr, int iDelay);
int TimerGet(byte ucTimerNbr);
int TimerStop(byte ucTimerNbr);
void Timer(void);
void DiskCreate(void);
void FileWrite(void);
void FileRead(void);
void DiskUse(void);
void DiskKill(void);
void FMGCreateBatch(void);
void FMGDeleteBatch(void);
void FMGAddDelTransactions(void);
void FMGReadTransactions(void);
void BeepDll(void);
void BeepLib(void);
int GetPpdDisplay(void);
void SetConfig(void);
void GetConfig(void);
void CreateSecret(void);
void FreeSecret(void);
void LoadIso9564Key(void);
void Iso9564PinEntry(void);
void LoadMacKey(void);
void MacCalculation(void);
void Draw(void);
void Logo(void);
void BMP(void);
int IacCallUser2(void);
void TrainingToUser2(void);
void TrainingToAll(void);
void TrainingToItself(void);
void TrainingToTask(void);
void DemoEntry(void);
void Candara(void);
void German(void);
void Polish(void);
void Turkish(void);
void Russian(void);
void Arabic(void);
void Greek(void);
void GetMsg(void);
void SelectLang(void);
void Testing(void);
void ConfFlash(doubleword uiCom);
void ConfSoftware(doubleword uiCom);
void ConfHardware(doubleword uiCom);
void SoftwareReset(void);
void DisplaySmall (byte ucLine, byte ucColumn, char *pcText);
void DisplayMedium (byte ucLine, byte ucColumn, char *pcText);
void DisplayLarge (byte ucLine, byte ucColumn, char *pcText);
int Display25(byte ucLine, char *pcData , int iLen);
int Print24(char *pcData, int iLen);
int ShowMenu(const char *pcTitle, int iMenuStyle, int iDefaultItem, 
			 int iMaxItems, const char *tpcItems[]);
int ShowEntry (const char *pcTitle, const char *pcText, char *pcInput, byte ucMinDigit, byte ucMaxDigit, byte ucEntryMode);
char* FMG_ErrorMsg (int iValue);
char* LL_ErrorMsg (int iValue); 
char* SEC_ErrorMsg (int iValue);
FILE *OpenConverter(char *pcName, byte ucSize);
void SetParity(char *pcBuf, word usDim, byte ucPar, byte ucTyp);
byte CheckParity(const char *pcBuf, word usDim, byte ucPar, byte ucTyp);
const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim);
char* UintToIp(doubleword uiVal);
doubleword IpToUint(const char *pcStr);



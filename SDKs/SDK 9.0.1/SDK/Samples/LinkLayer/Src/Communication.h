/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////
#define DEFAULT_INIT_STRING_EXTERNAL	"AT&FE0"
#define DEFAULT_INIT_STRING_ASYNC		"ATZE0"
#define DEFAULT_INIT_STRING_SYNC		"ATE0X3S6=1$M249$M251F4S144=16"
#define DEFAULT_INIT_STRING_HTTP		DEFAULT_INIT_STRING_ASYNC
#define DEFAULT_INIT_STRING_GREECE		DEFAULT_INIT_STRING_SYNC
#define DEFAULT_INIT_STRING_MALAYSIA	DEFAULT_INIT_STRING_SYNC
#define DEFAULT_PHONE_NUMBER_ASYNC		"0836062424"
#define DEFAULT_PHONE_NUMBER_SYNC		"00302103397710"			// Greek host
#define DEFAULT_PHONE_NUMBER_HTTP		"0860015555"				// Tiscali
#define DEFAULT_PHONE_NUMBER_GREECE		"00302103397710"			// Greek host
#define DEFAULT_PHONE_NUMBER_MALAYSIA	"0060389921624"				// Malaysian host
#define DEFAULT_LOGIN					"ssag0010@tiscali.fr"		// SAGEM test account at Tiscali
#define DEFAULT_PASSWORD				"ECIROM"
#define DEFAULT_HOST_NAME_PPP			"www.google.com"
#define DEFAULT_PORT_PPP				80
#define DEFAULT_HOST_NAME_ETHERNET		"10.138.2.163"
#define DEFAULT_PORT_ETHERNET			80

#define DEFAULT_APN						"XXXXXXXXa2bouygtel.com"
#define DEFAULT_PIN_CODE				"0027"

#define USE_HDLC_NO				0

#define MODE_NONE				0
#define MODE_SEND				1
#define MODE_ECHO				2
#define MODE_DOWNLOAD_HTTP		3
#define MODE_GREEK_HOST			4
#define MODE_MALAYSIAN_HOST		5
#define MODE_MASTERCARD_MIT		6

//// Types //////////////////////////////////////////////////////
typedef struct
{
	int m_nLink;
	int m_nBaudrate;
	int m_nBitsPerByte;
	int m_nStopBits;
	int m_nParity;
	int m_nFlowCtrl;

	int m_bUseModem;
	int m_nModemCmdTerminator;
	char m_szInitString[LL_MODEM_L_INIT_STRING_MAX + 1];
	char m_szPhoneNumber[LL_MODEM_L_PHONE_NUMBER_MAX + 1];


	int m_bUseGsm;
	int m_nGsmMode;
	int m_nGsmModulation;
	int m_nConnectionTimeout;

	char m_szPinCode[LL_GPRS_L_PIN_CODE_MAX+1];

	int m_bUseHdlc;

	int m_bUsePpp;
	char m_szLogin[LL_PPP_L_LOGIN_MAX + 1];
	char m_szPassword[LL_PPP_L_PASSWORD_MAX + 1];

	int m_bUseTcpIp;
	char m_szHostName[LL_TCPIP_L_HOST_NAME_MAX + 1];
	int m_nPort;

	int m_bUseGprs;
	char m_szAPN[LL_GPRS_L_APN_MAX + 1];

	int m_nTestMode;
} T__LL_CONFIGURATION;

//// Global variables ///////////////////////////////////////////
extern T__LL_CONFIGURATION CurrentConfig;

//// Static function definitions ////////////////////////////////

//// Functions //////////////////////////////////////////////////
void InitCommunication(void);
void InitDefaultConfig(void);
void DoCommunication(void);

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.h"
#include "LinkLayer.h"

#include "Assert.h"

#include "Communication.h"
#include "UserInterfaceHelpers.h"
#include "Menu.h"

//// Macros & preprocessor definitions //////////////////////////
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////
static const char* MainMenu[] =
{
	"Connect", "Link", "HDLC", "PPP", "TCP/IP", "MODE"
};
#define MAIN_MENU_NUM_OF_ITEMS		NUMBER_OF_ITEMS(MainMenu)

static const char* LinksMenu[] =
{
	"COM0", "COM1", "COM2", "USB", "MODEM", "GSM", "GPRS", "ETHERNET"
};
#define LINKS_MENU_NUM_OF_ITEMS		NUMBER_OF_ITEMS(LinksMenu)

static const char* YesNoChoice[] =
{
	"YES", "NO"
};
#define YES_NO_CHOICE_NUM_OF_ITEMS	NUMBER_OF_ITEMS(YesNoChoice)

static const char* ModesMenu[] =
{
	"None", "Send", "Echo", "HTTP", "Greek host", "Malaysian host", "Mastercard MIT"
};
#define MODES_MENU_NUM_OF_ITEMS		NUMBER_OF_ITEMS(ModesMenu)

static const char* GsmProtocol[] =
{
	"None", "RLP"
};
#define GSM_PROTOCOL_NUM_OF_ITEMS	NUMBER_OF_ITEMS(GsmProtocol)

static const char* GsmModulation[] =
{
	"V22B/2400",
	"V32/4800",
	"V32/9600",
	"V110/2400",
	"V110/4800",
	"V110/9600"
};

#define GSM_MODE_NUM_OF_ITEMS	NUMBER_OF_ITEMS(GsmModulation)

//// Functions //////////////////////////////////////////////////
static int DisplayConfig(const T__LL_CONFIGURATION* pConfig, int nLine)
{
	char* pPtr;
	const char* szOption;
	char szString[512 + 1];

	pPtr = szString;

	// Display the link
	switch(pConfig->m_nLink)
	{
	case LL_PHYSICAL_V_COM0:		szOption = "COM0";		break;
	case LL_PHYSICAL_V_COM1:		szOption = "COM1";		break;
	case LL_PHYSICAL_V_COM2:		szOption = "COM2";		break;
	case LL_PHYSICAL_V_USB:			szOption = "USB";		break;
	case LL_PHYSICAL_V_MODEM:		szOption = "MODEM";		break;
	case LL_PHYSICAL_V_GSM:			szOption = "GSM";		break;
	case LL_PHYSICAL_V_GPRS:		szOption = "GPRS";		break;
	case LL_PHYSICAL_V_ETHERNET:	szOption = "ETHERNET";	break;
	default:						szOption = "???";		break;
	}
	pPtr += sprintf(pPtr, "%s", szOption);

	// Display the serial port configuration
	if ((pConfig->m_nLink == LL_PHYSICAL_V_COM0) ||
		(pConfig->m_nLink == LL_PHYSICAL_V_COM1) ||
		(pConfig->m_nLink == LL_PHYSICAL_V_COM2))
	{
		switch(pConfig->m_nParity)
		{
		case LL_PHYSICAL_V_NO_PARITY:		szOption = "N";		break;
		case LL_PHYSICAL_V_ODD_PARITY:		szOption = "O";		break;
		case LL_PHYSICAL_V_EVEN_PARITY:		szOption = "E";		break;
		default:							szOption = "?";		break;
		}
		pPtr += sprintf(pPtr, "\n %i-%i-%s-%i", pConfig->m_nBaudrate,
			pConfig->m_nBitsPerByte, szOption, pConfig->m_nFlowCtrl);
	}

	// Display the modem configuration
	if (pConfig->m_bUseModem)
	{
		if (pConfig->m_nLink != LL_PHYSICAL_V_MODEM)
			pPtr += sprintf(pPtr, "\nMODEM");

		pPtr += sprintf(pPtr, "\n %s\n %s", pConfig->m_szInitString,
			pConfig->m_szPhoneNumber);
	}

	// Display the GPRS configuration
	if (pConfig->m_bUseGprs)
	{
		pPtr += sprintf(pPtr, "\n %s\n", pConfig->m_szAPN );
	}


	// Display the GSM configuration
	if (pConfig->m_bUseGsm)
	{
		pPtr += sprintf(pPtr, "\n %s\n", pConfig->m_szPhoneNumber );

		if (pConfig->m_nGsmMode == LL_GSM_V_MODE_RLP)
			pPtr += sprintf(pPtr, " RLP");


		switch( pConfig->m_nGsmModulation )
		{
		case LL_GSM_V_MODULATION_V22B_2400:
			pPtr += sprintf(pPtr, " V22B/2400");
			break;
		case LL_GSM_V_MODULATION_V32_4800:
			pPtr += sprintf(pPtr, " V32/4800");
			break;
		case LL_GSM_V_MODULATION_V32_9600:
			pPtr += sprintf(pPtr, " V32/9600");
			break;

		case LL_GSM_V_MODULATION_V110_2400:
			pPtr += sprintf(pPtr, " V110/2400");
			break;
		case LL_GSM_V_MODULATION_V110_4800:
			pPtr += sprintf(pPtr, " V110/4800");
			break;
		case LL_GSM_V_MODULATION_V110_9600:
			pPtr += sprintf(pPtr, " V110/9600");
			break;
		}
	}

	// Display the HDLC configuration
	if (pConfig->m_bUseHdlc)
		pPtr += sprintf(pPtr, "\nHDLC");

	// Display the PPP configuration
	if (pConfig->m_bUsePpp)
	{
		pPtr += sprintf(pPtr, "\nPPP\n %s\n %s",
			pConfig->m_szLogin, pConfig->m_szPassword);
	}

	// Display the TCP/IP configuration
	if (pConfig->m_bUseTcpIp)
	{
		pPtr += sprintf(pPtr, "\nTCP/IP\n %s\n %i", pConfig->m_szHostName,
			pConfig->m_nPort);
	}

	return HelperDisplayString(szString, nLine);
}

static int ConfigureLink(void)
{
	static const char szInitStringAllowedChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789#$%&*+,-./:;=?@^";
	int nState;
	int nLink;
	T__LL_CONFIGURATION Config;
	int nItem;
	char szInput[256];

	nState = 0;
	Config = CurrentConfig;
	do
	{
		switch(nState)
		{
		case 0:
			// Select the link
			switch(Config.m_nLink)
			{
			case LL_PHYSICAL_V_COM0:		nItem = 0;	break;
			case LL_PHYSICAL_V_COM1:		nItem = 1;	break;
			case LL_PHYSICAL_V_COM2:		nItem = 2;	break;
			case LL_PHYSICAL_V_USB:			nItem = 3;	break;
			case LL_PHYSICAL_V_MODEM:		nItem = 4;	break;
			case LL_PHYSICAL_V_GSM:			nItem = 5;	break;
			case LL_PHYSICAL_V_GPRS:		nItem = 6;	break;
			case LL_PHYSICAL_V_ETHERNET:	nItem = 7;	break;
			default:						nItem = 0;	break;
			break;
			}

			// Display the menu
			switch(HelperDisplayMenu("LINK", nItem, LINKS_MENU_NUM_OF_ITEMS, LinksMenu))
			{
			case 0:		nLink = LL_PHYSICAL_V_COM0;		break;
			case 1:		nLink = LL_PHYSICAL_V_COM1;		break;
			case 2:		nLink = LL_PHYSICAL_V_COM2;		break;
			case 3:		nLink = LL_PHYSICAL_V_USB;		break;
			case 4:		nLink = LL_PHYSICAL_V_MODEM;	break;
			case 5:		nLink = LL_PHYSICAL_V_GSM;		break;
			case 6:		nLink = LL_PHYSICAL_V_GPRS;		break;
			case 7:		nLink = LL_PHYSICAL_V_ETHERNET;	break;

			case -2:	nLink = 0; nState = -2;			break;
			default:	nLink = 0; nState = -1;			break;
			}

			if (nState >= 0)
			{
				if (nLink != Config.m_nLink)
					Config = CurrentConfig;

				Config.m_nLink = nLink;
				if ((nLink == LL_PHYSICAL_V_COM0) || (nLink == LL_PHYSICAL_V_COM1) || (nLink == LL_PHYSICAL_V_COM2))
				{
					Config.m_bUseGsm = FALSE;
					Config.m_bUseGprs = FALSE;
					Config.m_bUseHdlc = FALSE;
					nState = 10;
				}
				else if (nLink == LL_PHYSICAL_V_MODEM)
				{
					Config.m_bUseGsm = FALSE;
					Config.m_bUseGprs = FALSE;
					Config.m_bUseModem = TRUE;
					nState = 30;
				}
				else if (nLink == LL_PHYSICAL_V_GSM)
				{
					Config.m_bUseGsm = TRUE;
					Config.m_bUseModem = FALSE;
					Config.m_bUseHdlc = FALSE;
					Config.m_bUseGprs = FALSE;
					nState = 50;
				}
				else if (nLink == LL_PHYSICAL_V_GPRS )
				{
					Config.m_bUseGprs = TRUE;

					Config.m_bUseGsm = FALSE;
					Config.m_bUseModem = FALSE;
					Config.m_bUseHdlc = FALSE;
					Config.m_bUsePpp = FALSE;
					if (!Config.m_bUseTcpIp)
					{
						strcpy(Config.m_szHostName, DEFAULT_HOST_NAME_ETHERNET);
						Config.m_nPort = DEFAULT_PORT_ETHERNET;
					}
					Config.m_bUseTcpIp = TRUE;
					nState = 1000;
				}
				else if (nLink == LL_PHYSICAL_V_ETHERNET)
				{
					Config.m_bUseGsm = FALSE;
					Config.m_bUseGprs = FALSE;
					Config.m_bUseModem = FALSE;
					Config.m_bUseHdlc = FALSE;
					Config.m_bUsePpp = FALSE;
					if (!Config.m_bUseTcpIp)
					{
						strcpy(Config.m_szHostName, DEFAULT_HOST_NAME_ETHERNET);
						Config.m_nPort = DEFAULT_PORT_ETHERNET;
					}
					Config.m_bUseTcpIp = TRUE;
					nState = 1000;
				}
				else
				{
					Config.m_bUseGsm = FALSE;
					Config.m_bUseGprs = FALSE;
					Config.m_bUseModem = FALSE;
					Config.m_bUseHdlc = FALSE;
					nState = 1000;
				}
			}
			break;

		case 10:
			// Input the serial port parameters
			Config.m_nBaudrate = LL_PHYSICAL_V_BAUDRATE_115200;
			Config.m_nBitsPerByte = LL_PHYSICAL_V_8_BITS;
			Config.m_nStopBits = LL_PHYSICAL_V_1_STOP;
			Config.m_nParity = LL_PHYSICAL_V_NO_PARITY;
			Config.m_nFlowCtrl = LL_PHYSICAL_V_NO_FLOW_CTRL;
			nState = 20;
			break;

		case 20:
			// Choose if modem is used or not
			if (Config.m_bUseModem)
				nItem = 0;
			else nItem = 1;
			switch(HelperDisplayChoices("MODEM", nItem, YES_NO_CHOICE_NUM_OF_ITEMS, YesNoChoice))
			{
			case 0:
				Config.m_bUseModem = TRUE;
				nState = 30;
				break;
			case 1:
				Config.m_bUseModem = FALSE;
				nState = 1000;
				break;
			case -2:
				nState = 0;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 30:
			// Input the initialisation string
			switch(HelperAlphanumericInput("MODEM", "Init string:", 1, 40, Config.m_szInitString, szInitStringAllowedChars, szInput))
			{
			case 0:
				strcpy(Config.m_szInitString, szInput);
				nState = 40;
				break;
			case -2:
				nState = 20;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 40:
			// Input the phone number
			switch(HelperNumericInput("MODEM", "Phone number:", 1, 20, Config.m_szPhoneNumber, szInput))
			{
			case 0:
				strcpy(Config.m_szPhoneNumber, szInput);
				nState = 1000;
				break;
			case -2:
				nState = 30;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 50:
			Config.m_nBaudrate = LL_PHYSICAL_V_BAUDRATE_2400;

			// Input the phone number
			switch(HelperNumericInput("GSM", "Phone number:", 1, 20, Config.m_szPhoneNumber, szInput))
			{
			case 0:
				strcpy(Config.m_szPhoneNumber, szInput);
				nState++;
				break;
			case -2:
				nState = 0;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 51:
			// Choose the GSM protocol
			if (Config.m_nGsmMode == LL_GSM_V_MODE_RLP)
				nItem = 1;
			else nItem = 0;
			switch(HelperDisplayChoices("GSM Mode", nItem, GSM_PROTOCOL_NUM_OF_ITEMS, GsmProtocol))
			{
			case 0:
				Config.m_nGsmMode = LL_GSM_V_MODE_TRANSPARENT;
				nState++;
				break;
			case 1:
				Config.m_nGsmMode = LL_GSM_V_MODE_RLP;
				nState++;
				break;
			case -2:
				nState--;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 52:
			// Choose the GSM modulation
			switch( Config.m_nGsmModulation )
			{
			case LL_GSM_V_MODULATION_V22B_2400:
				nItem = 0;
				break;
			case LL_GSM_V_MODULATION_V32_4800:
				nItem = 1;
				break;

			case LL_GSM_V_MODULATION_V110_2400:
				nItem = 3;
				break;

			case LL_GSM_V_MODULATION_V110_4800:
				nItem = 4;
				break;

			case LL_GSM_V_MODULATION_V110_9600:
				nItem = 5;
				break;

			default:
			case LL_GSM_V_MODULATION_V32_9600:
				nItem = 2;
				break;
			}

			switch(HelperDisplayChoices("GSM Modulation", nItem, GSM_MODE_NUM_OF_ITEMS, GsmModulation))
			{
			case 0:
				Config.m_nGsmModulation = LL_GSM_V_MODULATION_V22B_2400;
				nState = 1000;
				break;
			case 1:
				Config.m_nGsmModulation = LL_GSM_V_MODULATION_V32_4800;
				nState = 1000;
				break;

			case 2:
				Config.m_nGsmModulation = LL_GSM_V_MODULATION_V32_9600;
				nState = 1000;
				break;

			case 3:
				Config.m_nGsmModulation = LL_GSM_V_MODULATION_V110_2400;
				nState = 1000;
				break;

			case 4:
				Config.m_nGsmModulation = LL_GSM_V_MODULATION_V110_4800;
				nState = 1000;
				break;

			case 5:
				Config.m_nGsmModulation = LL_GSM_V_MODULATION_V110_9600;
				nState = 1000;
				break;

			case -2:
				nState--;
				break;
			default:
				nState = -1;
				break;
			}
			break;
		}
	} while((nState >= 0) && (nState < 1000));

	if (nState == 1000)
	{
		CurrentConfig = Config;
		return 0;
	}
	else return nState;
}

static int ConfigureHdlc(void)
{
	T__LL_CONFIGURATION Config;
	int nResult;
	int nItem;

	nResult = 0;
	Config = CurrentConfig;

	// Choose if HDLC must be used or not
	if (Config.m_bUseHdlc)
		nItem = 0;
	else nItem = 1;
	switch(HelperDisplayChoices("HDLC", nItem, YES_NO_CHOICE_NUM_OF_ITEMS, YesNoChoice))
	{
	case 0:
		Config.m_nLink = LL_PHYSICAL_V_MODEM;
		Config.m_bUseModem = TRUE;
		Config.m_nModemCmdTerminator = LL_MODEM_V_CMD_TERMINATOR_CR;

		if (!Config.m_bUseHdlc)
		{
			strcpy(Config.m_szInitString, DEFAULT_INIT_STRING_SYNC);
			strcpy(Config.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_SYNC);
			Config.m_nTestMode = MODE_NONE;
		}

		Config.m_bUseHdlc = TRUE;
		Config.m_bUsePpp = FALSE;
		Config.m_bUseTcpIp = FALSE;
		break;
	case 1:
		if (Config.m_bUseHdlc)
		{
			strcpy(Config.m_szInitString, DEFAULT_INIT_STRING_ASYNC);
			strcpy(Config.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_ASYNC);
		}

		Config.m_bUseHdlc = FALSE;
		break;
	case -2:
		nResult = -2;
		break;
	default:
		nResult = -1;
		break;
	}

	if (nResult >= 0)
		CurrentConfig = Config;

	return nResult;
}

static int ConfigurePpp(void)
{
	static const char szAllowedChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%\'()*+,-./:;<=>?@[\\]^_`{|}~";
	int nState;
	T__LL_CONFIGURATION Config;
	int nItem;
	char szInput[256];

	nState = 0;
	Config = CurrentConfig;
	do
	{
		switch(nState)
		{
		case 0:
			// Choose if PPP must be used or not
			if (Config.m_bUsePpp)
				nItem = 0;
			else nItem = 1;
			switch(HelperDisplayChoices("PPP", nItem, YES_NO_CHOICE_NUM_OF_ITEMS, YesNoChoice))
			{
			case 0:
				if (!Config.m_bUsePpp)
					Config = CurrentConfig;

				Config.m_bUseHdlc = FALSE;
				Config.m_bUsePpp = TRUE;
				nState = 10;
				break;
			case 1:
				if (Config.m_bUsePpp)
					Config = CurrentConfig;

				if (Config.m_nLink != LL_PHYSICAL_V_ETHERNET)
					Config.m_bUseTcpIp = FALSE;

				Config.m_bUsePpp = FALSE;
				nState = 1000;
				break;
			case -2:
				nState = -2;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 10:
			// Input the login
			switch(HelperAlphanumericInput("PPP", "Login:", 1, 20, Config.m_szLogin, szAllowedChars, szInput))
			{
			case 0:
				strcpy(Config.m_szLogin, szInput);
				nState = 20;
				break;
			case -2:
				nState = 0;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 20:
			// Input the password
			switch(HelperAlphanumericInput("PPP", "Password:", 1, 20, Config.m_szPassword, szAllowedChars, szInput))
			{
			case 0:
				strcpy(Config.m_szPassword, szInput);
				nState = 1000;
				break;
			case -2:
				nState = 10;
				break;
			default:
				nState = -1;
				break;
			}
			break;
		}
	} while((nState >= 0) && (nState < 1000));

	if (nState == 1000)
	{
		CurrentConfig = Config;
		return 0;
	}
	else return nState;
}

static int ConfigureTcpIp(void)
{
	static const char szAllowedChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%\'()*+,-./:;<=>?@[\\]^_`{|}~";
	int nState;
	T__LL_CONFIGURATION Config;
	int nItem;
	char szDefault[20];
	char szInput[256];
	const char* pPtr;
	int nValue;

	nState = 0;
	Config = CurrentConfig;
	do
	{
		switch(nState)
		{
		case 0:
			// Choose if TCP/IP must be used or not
			if (Config.m_bUseTcpIp)
				nItem = 0;
			else nItem = 1;
			switch(HelperDisplayChoices("TCP/IP", nItem, YES_NO_CHOICE_NUM_OF_ITEMS, YesNoChoice))
			{
			case 0:
				if (!Config.m_bUseTcpIp)
					Config = CurrentConfig;

				Config.m_bUseHdlc = FALSE;
				if (Config.m_nLink != LL_PHYSICAL_V_ETHERNET)
					Config.m_bUsePpp = TRUE;
				else Config.m_bUsePpp = FALSE;

				if (!Config.m_bUseTcpIp)
				{
					if (Config.m_nLink == LL_PHYSICAL_V_ETHERNET)
					{
						strcpy(Config.m_szHostName, DEFAULT_HOST_NAME_PPP);
						Config.m_nPort = DEFAULT_PORT_PPP;
					}
					else
					{
						strcpy(Config.m_szHostName, DEFAULT_HOST_NAME_ETHERNET);
						Config.m_nPort = DEFAULT_PORT_ETHERNET;
					}
				}
				Config.m_bUseTcpIp = TRUE;
				nState = 10;
				break;
			case 1:
				if (Config.m_bUseTcpIp)
					Config = CurrentConfig;

				Config.m_bUseTcpIp = FALSE;
				nState = 1000;
				break;
			case -2:
				nState = -2;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 10:
			// Input the host name
			switch(HelperAlphanumericInput("TCP/IP", "Host:", 1, 40, Config.m_szHostName, szAllowedChars, szInput))
			{
			case 0:
				strcpy(Config.m_szHostName, szInput);
				nState = 20;
				break;
			case -2:
				nState = 0;
				break;
			default:
				nState = -1;
				break;
			}
			break;

		case 20:
			// Input the port
			sprintf(szDefault, "%i", Config.m_nPort);
			switch(HelperNumericInput("TCP/IP", "Port:", 1, 20, szDefault, szInput))
			{
			case 0:
				nValue = 0;
				pPtr = szInput;
				while((*pPtr >= '0') && (*pPtr <= '9'))
				{
					nValue = nValue * 10 + (*pPtr - '0');
					pPtr++;
				}
				if ((nValue > 0) && (nValue < 65536))
				{
					Config.m_nPort = nValue;
					nState = 1000;
				}
				break;
			case -2:
				nState = 10;
				break;
			default:
				nState = -1;
				break;
			}
			break;
		}
	} while((nState >= 0) && (nState < 1000));

	if (nState == 1000)
	{
		CurrentConfig = Config;
		return 0;
	}
	else return nState;
}

static int ConfigureMode(void)
{
	T__LL_CONFIGURATION Config;
	int nItem;
	int nResult;

	Config = CurrentConfig;

	// Select the mode
	nItem = Config.m_nTestMode;

	// Display the menu
	nResult = 0;
	switch(HelperDisplayMenu("MODE", nItem, MODES_MENU_NUM_OF_ITEMS, ModesMenu))
	{
	case MODE_NONE:
		Config.m_nTestMode = MODE_NONE;
		break;
	case MODE_SEND:
		Config.m_nTestMode = MODE_SEND;
		break;
	case MODE_ECHO:
		Config.m_nTestMode = MODE_ECHO;
		break;
	case MODE_DOWNLOAD_HTTP:
		Config.m_nLink = LL_PHYSICAL_V_MODEM;

		Config.m_bUseModem = TRUE;
		Config.m_nModemCmdTerminator = LL_MODEM_V_CMD_TERMINATOR_CR;

		strcpy(Config.m_szInitString, DEFAULT_INIT_STRING_HTTP);
		strcpy(Config.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_HTTP);

		Config.m_bUseHdlc = FALSE;

		Config.m_bUsePpp = TRUE;
		strcpy(Config.m_szLogin, DEFAULT_LOGIN);
		strcpy(Config.m_szPassword, DEFAULT_PASSWORD);

		Config.m_bUseTcpIp = TRUE;
		strcpy(Config.m_szHostName, DEFAULT_HOST_NAME_PPP);
		Config.m_nPort = DEFAULT_PORT_PPP;

		Config.m_nTestMode = MODE_DOWNLOAD_HTTP;
		break;
	case MODE_GREEK_HOST:
		Config.m_nLink = LL_PHYSICAL_V_MODEM;

		Config.m_bUseModem = TRUE;
		Config.m_nModemCmdTerminator = LL_MODEM_V_CMD_TERMINATOR_CR;

		strcpy(Config.m_szInitString, DEFAULT_INIT_STRING_GREECE);
		strcpy(Config.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_GREECE);

		Config.m_bUseHdlc = TRUE;

		Config.m_bUsePpp = FALSE;
		Config.m_bUseTcpIp = FALSE;

		Config.m_nTestMode = MODE_GREEK_HOST;
		break;
	case MODE_MALAYSIAN_HOST:
		Config.m_nLink = LL_PHYSICAL_V_MODEM;

		Config.m_bUseModem = TRUE;
		Config.m_nModemCmdTerminator = LL_MODEM_V_CMD_TERMINATOR_CR;

		strcpy(Config.m_szInitString, DEFAULT_INIT_STRING_MALAYSIA);
		strcpy(Config.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_MALAYSIA);

		Config.m_bUseHdlc = TRUE;

		Config.m_bUsePpp = FALSE;
		Config.m_bUseTcpIp = FALSE;

		Config.m_nTestMode = MODE_MALAYSIAN_HOST;
		break;
	case MODE_MASTERCARD_MIT:
		Config.m_nLink = LL_PHYSICAL_V_ETHERNET;

		Config.m_bUseModem = FALSE;
		Config.m_bUseHdlc = FALSE;

		Config.m_bUsePpp = FALSE;
		Config.m_bUseTcpIp = TRUE;

		strcpy(Config.m_szHostName, "89.0.17.237");
		Config.m_nPort = 3331;

		Config.m_nTestMode = MODE_MASTERCARD_MIT;
		break;

	case -2:
		nResult = -2;
		break;
	default:
		nResult = -1;
		break;
	}

	if (nResult >= 0)
	{
		CurrentConfig = Config;
		return 0;
	}
	else return nResult;
}

void ManageUserInterface(void)
{
	FILE* hKeyboard;
	int nKey;
	int nLine;

	nLine = 0;
	do
	{
		nLine = DisplayConfig(&CurrentConfig, nLine);

		// Wait a key
		hKeyboard = fopen("KEYBOARD", "r");
		if (ttestall(KEYBOARD, 6000) == KEYBOARD)
			nKey = getchar();
		else nKey = T_ANN;
		fclose(hKeyboard);

		if ((nKey == T_SK10) || (nKey == T_VAL))
		{
			switch(HelperDisplayMenu("LINK LAYER TEST", 0, MAIN_MENU_NUM_OF_ITEMS, MainMenu))
			{
			case 0:
				// Connect
				DoCommunication();
				break;
			case 1:
				// Configure link
				if (ConfigureLink() == -1)
					nKey = T_ANN;
				break;
			case 2:
				// Configure HDLC
				if (ConfigureHdlc() == -1)
					nKey = T_ANN;
				break;
			case 3:
				// Configure PPP
				if (ConfigurePpp() == -1)
					nKey = T_ANN;
				break;
			case 4:
				// Configure TCP/IP
				if (ConfigureTcpIp() == -1)
					nKey = T_ANN;
				break;
			case 5:
				// Configure mode
				if (ConfigureMode() == -1)
					nKey = T_ANN;
				break;

			case -1:
				nKey = T_ANN;
				break;
			}
		}
		else if (nKey == T_SKHAUT)
			nLine--;
		else if (nKey == T_SKBAS)
			nLine++;
		else if (nKey == T_CORR)
			nKey = T_ANN;
	} while(nKey != T_ANN);
}

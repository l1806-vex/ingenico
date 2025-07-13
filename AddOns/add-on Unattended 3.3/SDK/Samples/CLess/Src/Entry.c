/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"
#include "oem_cless.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"

#include "UserInterfaceHelpers.h"
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"
#include "ConfigurationTest.h"
#include "TPassMenu.h"
#include "ImplicitSelection.h"
#include "DllTesting_DumpData.h"
#include "util.h"

//// Macros & preprocessor definitions //////////////////////////
#define STATE_READY            0
#define STATE_EPURSE_BALANCE   1
#define STATE_WAIT_EVT         2
#define STATE_DEBIT            3
#define STATE_DEBIT_RECORD     4
#define STATE_REVALUE          5
#define STATE_REVALUE_RECORD   6
#define STATE_REMOVE_CARD      7
#define STATE_END          0xFF

#define SERVICES_LOW_PRIORITY			30
#define SERVICES_HIGH_PRIORITY			10
#define SERVICES_DEFAULT_PRIORITY		20


//// Static function definitions ////////////////////////////////

void entry(void);

//static int PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed);
static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut);
//static int idle_message_(NO_SEGMENT AppliNum);
static int is_card_emv_for_you_(NO_SEGMENT AppliNum, const S_AID* pParamIn, S_CARDOUT* pParamOut);
static int is_change_init_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_delete_(NO_SEGMENT AppliNum, S_DELETE* pParamOut);
static int is_evol_pg_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_for_you_after_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_CARDOUT* pParamOut);
static int is_for_you_before_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_ETATOUT* pParamOut);
static int is_licenced_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_name_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_state_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_time_function_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int give_your_domain_(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut);
static int more_function_(NO_SEGMENT AppliNum);
static int state_(NO_SEGMENT AppliNum);
static int cless_give_info_(NO_SEGMENT AppliNum, S_TRANSIN * pParamIn, S_CLESS_GIVEINFO* pParamOut);
static int cless_is_for_you_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData);
static int cless_debit_aid_Banking (NO_SEGMENT AppliNum, unsigned int nSize, void * pData, int iWhoCalled_p);
static int cless_debit_aid_Vending (NO_SEGMENT AppliNum, unsigned int nSize, void * pData, int iWhoCalled_p);
//static int cless_debit_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData);
static int cless_end_ (NO_SEGMENT AppliNum);
//static int give_your_specific_context (NO_SEGMENT AppliNum,void * p1, S_SPECIFIC_CONTEXT *pParamOut );

static int Main_(unsigned int nSize, StructPt* pData);
extern int MainAppliUCMC_IAC(unsigned int size_p, T_UCMC_IAC_SERVICE *pdata_p);


//// Global variables ///////////////////////////////////////////
static const char APP_NAME[] = "APP_Cless";
static const unsigned char tcAppName_g []    = "APP_CLESS01";

static service_desc_t Services[] = {
	{ 0, AFTER_RESET, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_CARD_EMV_FOR_YOU, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_CHANGE_INIT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_DELETE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_EVOL_PG, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_FOR_YOU_AFTER, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_FOR_YOU_BEFORE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_LICENCED, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_NAME, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_TIME_FUNCTION, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_YOUR_DOMAIN, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, MORE_FUNCTION, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_GIVE_INFO, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_IS_FOR_YOU, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_DEBIT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_DEBIT_AID, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_END, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
   { 0, GIVE_YOUR_SPECIFIC_CONTEXT,(SAP)Main_, SERVICES_DEFAULT_PRIORITY },   
	{ 0, SERVICE_APPLI_UCMC, (SAP)MainAppliUCMC_IAC, SERVICES_HIGH_PRIORITY }	
};

int giDisplayBackColor;
int giDisplay;
unsigned char gucCinematicType;
int giModeMainteance;
//// Functions //////////////////////////////////////////////////
void Buzzer_Test(void)
{
	char cTemp[ 50 ];
	T_UCMC_IAC_BUZ sBuz;

	sBuz.ucCmd = UCMC_BUZ_NORMAL;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
	sBuz.usDelay = 1;
	sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
      ttestall(0,50);
	sBuz.ucCmd = UCMC_BUZ_HIGH;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
	sBuz.usDelay = 1;
	sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
      ttestall(0,50);
	sBuz.ucCmd = UCMC_BUZ_BASS;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
	sBuz.usDelay = 1;
	sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
      ttestall(0,50);
	sBuz.ucCmd = UCMC_BUZ_OFF;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
	sBuz.usDelay = 0;
	sprintf( cTemp, "Off = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
}


static int iUN_CAD30_PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed)
{
	int nResult;
	SEGMENT Infos;
	unsigned char Status;
	char ucTemp[200];
	object_info_t info;

	// Get information on the application
	info_seg(AppliNum, &Infos);

	// Open the printer
	if( iLIBUCM_Print_Exist(UCMC_PRINT) > 0 )
	{
		// Print
		sprintf(ucTemp, "\x1b" "@\n\x1b" "E%s\n\x1b" "@", APP_NAME);
		iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
		if(ObjectGetInfo(OBJECT_TYPE_APPLI,AppliNum,&info) ==0)
		{
			sprintf(ucTemp,"Version : %s\n", info.name /*Get_AppliName(AppliNum)*/);
		}
		else
		{
			sprintf(ucTemp,"Version : unknown\n");
		}
		iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
		sprintf(ucTemp,"CRC     : %04X\n\n", Infos.crc);
		iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;

		sprintf(ucTemp,"\n\n\n\n");
		iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;


		iLIBUCM_Print_Status(UCMC_PRINT, &Status);
		if ((Status & (PRINT_ERROR | PAPER_OUT)) != 0)
			nResult = STOP;
		else nResult = FCT_OK;
	}
	else nResult = FCT_OK;

	return nResult;
}

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */
int iUcmIac_BckColor( unsigned char ucChannel_p, unsigned char ucCmd_p )
{
	int iRet;
   T_UCMC_DISPLAY_BACKLIGHT_COLOR sBlkColor;

   sBlkColor.ucColorDefined = ucCmd_p;
   sBlkColor.ucOption = 0;
   sBlkColor.usBlue = 0;
   sBlkColor.usGreen = 0;
   sBlkColor.usRed = 0;

   iRet = iLIBUCM_Display_Backlight_Color( ucChannel_p, &sBlkColor );

   return( iRet );
}

static int iGraphic_message( char *pMessage_p, int iTo_p )
{
FILE* hDisplay;
int nDefaultFont;
int nScreenWidth;
int nScreenHeight;
int nFontHeight;
char cTemp[400];
int i, iLg, iDeb,iFin,iNbLigne,iDecalHeader,iDecalHeaderH;

    iLIBUCM_Display_Graphic_Start(giDisplay);

    // Terminal idle message
    if( giDisplay == PARAM_TYPE_TPASS)
    {
        TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

        hDisplay = fopen("DISPLAY_C30", "w");
    }
    else
    {
        hDisplay = fopen("DISPLAY", "w"); /* for reset graphic window */
    }

    nDefaultFont = GetDefaultFont();

    CreateGraphics(_XLARGE_);
    GetScreenSize(&nScreenHeight, &nScreenWidth);
    nFontHeight = GetPoliceSize();

    // Display according header
    if (giModeMainteance != 0)
    {
        iDecalHeader = 22;
        iDecalHeaderH = 7;
    }
    else
    {
        /* no header */  
        iDecalHeader = 0;
        iDecalHeaderH = 0;
    }

    _DrawRect(0, 0+iDecalHeader, nScreenWidth-1, nScreenHeight-1-iDecalHeaderH, 1, _ON_, _OFF_);
    _DrawRect(1, 1+iDecalHeader, nScreenWidth-2, nScreenHeight-2-iDecalHeaderH, 1, _ON_, _OFF_);
    _DrawRect(3, 3+iDecalHeader, nScreenWidth-4, nScreenHeight-4-iDecalHeaderH, 1, _ON_, _OFF_);

    SetFont(_MEDIUM_);
    if( pMessage_p [0] == 0 )
        _DrawString("Message blank", 15, 7+30, _OFF_);
    else
    {
        /* formatage */
        iFin = 0;
        iDeb = 0;
        iNbLigne=0;
        iLg = strlen( pMessage_p);
        for( i = 0; i < iLg; i++ )
        {
            /* delete newline */
            if( ( pMessage_p[i] == 0x0A ) || (i==iLg-1) )
            {
                if( iDeb != i ) 
                {
                    if( i == (iLg-1 ) )
                    {
                        memcpy( cTemp, &pMessage_p[iDeb], iFin-iDeb+1);
                        cTemp[iFin-iDeb+1] = 0;
                    }
                    else
                    {
                        memcpy( cTemp, &pMessage_p[iDeb], iFin-iDeb);
                        cTemp[iFin-iDeb] = 0;
                    }
                    _DrawString(cTemp, 20, 7+20+iNbLigne*10, _OFF_);
                    trace( 0x6E01, strlen(cTemp), cTemp);
                    sprintf( cTemp, "i=%d iDeb=%d iFin=%d", i, iDeb, iFin);
                    trace( 0x6E01, strlen(cTemp), cTemp);
                    iNbLigne++;
                }
                iDeb = i+1;
                iFin++;
            }
            else
            {
                iFin++;
            }
        }
    }

    PaintGraphics();

    SetDefaultFont(nDefaultFont);
    if( hDisplay != NULL)
        fclose(hDisplay);

    // Turn on the reader screen backligth
//    TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

    iLIBUCM_Display_Graphic_Stop(giDisplay);

    if( iTo_p != 0 )
        ttestall( 0, iTo_p );

    return (FCT_OK);
}
static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut)
{
	unsigned char ChangeFlag;
	unsigned char ChangeType;
	unsigned int nResult;
	unsigned char ucITP[4];
	int iRet, iLg,i;
  T_UCM_DEVICE_STATUS sDeviceStatus;
T_LIBUCM_DEVICE_STATUS sStatus;

  /* vending parameters */
  int                     iSize ;
  T_UCMC_IAC_HOST2         sHostCmd ;
  T_UCMC_IAC_HOST2         sHostCmdAnsw ;
  T_UCMHOST_DA_PARAMV5		sParam;
  T_UCMHOST_DA_PARAM_MSGV3	sParamMsg;
  /*****end vending*****************/

	// Clear the output parameter
	memset(pParamOut, 0, sizeof(*pParamOut));

        giModeMainteance = 0;
       iRet = iLIBUCM_Device_Ucm_Status( &sStatus );

        if( iRet != FCT_OK)
        {
            return( -1 );
        }
        else
        {
          if( sStatus.ucUCM == 3 )
          {
                giModeMainteance = 1;
          }            
        }

	iLg = 0;
	ucITP[0] = 0;
	// French banking application iRet = iLIBUCM_Device_Cmd( UCMDEVICE_CMD_ICL_ITP, &ucITP[0], &iLg, &iRet2);
	//sprintf( cTemp, "iLIBUCM_Device_Cmd ICL %.3s %d %d %d", ucITP, iRet, iRet2, iLg );
	//trace(0x6E02, strlen(cTemp), cTemp);

	// Check for first run
	if (first_init(AppliNum, &ChangeFlag, &ChangeType) != FSE_FAILED)
	{
		if (ChangeFlag == (unsigned char)-1)
		{
			// Print the version
			iUN_CAD30_PrintAppliVersion(AppliNum, TRUE);

			// Cold reset
			raz_init(AppliNum);
		}
	}

    /**************************/
    /* choice back color or display */
    /**************************/
    giDisplay = 0;
    giDisplayBackColor = 0;

    i = iLIBUCM_Display_Exist(UCMC_DISPLAY_ICL);

    switch( i)
    {
        case PARAM_TYPE_IUC180:
        case PARAM_TYPE_IUC150: /* IUC150 special) */
            giDisplay = UCMC_DISPLAY_ICL;
            giDisplayBackColor = UCMC_DISPLAY_ICL;
   //         sprintf( cTemp, "DISPLAY ICL\n TYPE %d",i);
   //         iLIBUCM_Display_Message( giDisplay, cTemp, 400 ) ;
        break;
        case PARAM_TYPE_TPASS:
            giDisplay = UCMC_DISPLAY_ICL;
   //         sprintf( cTemp, "DISPLAY ICL\n TYPE %d",i);
   //         iLIBUCM_Display_Message( giDisplay, cTemp, 400 ) ;
        break;
        default:
            giDisplayBackColor = 0 ;
            i = iLIBUCM_Display_Exist(UCMC_DISPLAY);

            switch(i )         
            {
                case PARAM_TYPE_IUP250:
                    giDisplay = UCMC_DISPLAY_PPAD;
                    giDisplayBackColor = UCMC_DISPLAY_PPAD;
   //                 sprintf( cTemp, "DISPLAY\n TYPE %d",i);
   //                 iLIBUCM_Display_Message( giDisplay, cTemp, 400 ) ;
                break;
                case PARAM_TYPE_UPP:
                case PARAM_TYPE_CAD30VR:
                case PARAM_TYPE_HOST:
                default:
                    if( i > 0)
                    {
                        giDisplay = UCMC_DISPLAY;
    //                    sprintf( cTemp, "DISPLAY\n TYPE %d",i);
    //                    iLIBUCM_Display_Message( giDisplay, cTemp, 400 ) ;
                    }
                break;
            }

        break;
    }

  iRet = iLIBUCM_Device_GetStatus( UCM_DEVICE_HOST, &sDeviceStatus );
  gucCinematicType = sDeviceStatus.ucType; /* real ucm cinematic must be same as define  UCMCINEMATIC */

  if( gucCinematicType != UCMCINEMATIC)
  {
    /* VENDING MACHINE EXE MDB */
    if( giDisplay > 0 )    
        iLIBUCM_Display_Message( giDisplay, "UCMCINEMATIC\nBAD VALUE\nor PARAMETER", 800 ) ;

  }
  
  if(gucCinematicType == 2) /* Vending payment cinematic EXE MDB */
  {
    /* vending parameters */
    sHostCmd.usHostCmd = UCMHOSTLIB_CMD_PARAM_DA_MSG ;
  	sHostCmd.usHostWaitTimeout = 10 ; // seconds
  	sHostCmd.usSize = sizeof( sParamMsg ) ;
  	UTIL_InitStruct_ParamVmcMsg ( &sParamMsg ) ;
  	memcpy(&sHostCmd.u.ucBuf[0],&sParamMsg,sizeof(sParamMsg));
  	
  	iSize = ( sizeof( T_UCMC_IAC_HOST2 ) // struct size - data max size + real data size */
  				- UCMC_IAC_HOST2_BUFFER_SIZE ) 
  				+ sizeof( sParamMsg ) ;
  
  	if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) != FCT_OK )
  	{
  		if( giDisplay > 0 )    
                iLIBUCM_Display_Message ( giDisplay, "Dll protocol\ncannot be\n initialised\n", 10 );
  	}

    /* VENDING MACHINE EXE MDB */    
    if( giDisplay > 0 )   
        iGraphic_message( "CLESS\nVENDING", 200 ); 
        //    iLIBUCM_Display_Message( giDisplay, "CLESS\nVENDING", 200 ) ;

	sHostCmd.usHostCmd = UCMHOSTLIB_CMD_PARAM_DA ;
	sHostCmd.usHostWaitTimeout = 10 ; //seconds
	sHostCmd.usSize = sizeof( sParam ) ;

	UTIL_InitStruct_ParamVmc (&sParam) ;
	memcpy(&sHostCmd.u.ucBuf[0],&sParam,sizeof(sParam));

	iSize = ( sizeof( T_UCMC_IAC_HOST2 ) // struct size - data max size + real data size */
				- UCMC_IAC_HOST2_BUFFER_SIZE )
				+ sizeof( sParam ) ;

	if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) != FCT_OK )
	{
            if( giDisplay > 0 )    
                iLIBUCM_Display_Message ( giDisplay, "Dll protocol\ncannot be\n initialised\n", 10 );
	}

  }
  else
  { 
 	/* idle message event not recommanded used */
	//iLIBUCM_Display_Idle_Event( UCMC_DISPLAY, 1 ); /* 1=event on  0=event off */

    /* HOST */  
    if( giDisplay > 0 ) 
      {
         if (gucCinematicType == 0)
         {
            iGraphic_message("SAMPLE CLESS", 200);
         }
         else
         {
         iGraphic_message( "CLESS\nBANKING", 200 );    
         }
  }

   }
  
  	Buzzer_Test();

	TPasslib_open();

	nResult = TPass_IsConnected();
	if (nResult == ERR_TPASS_OK)
	{
		TPass_BacklightLevel(0);
		TPass_FirstLine();
		CUC30_DisplayText("\n\nTeliumPass Test", CUC30_ALIGN_CENTER);
		return FCT_OK;
	}
	else
	{
		TPass_FirstLine();
		CUC30_DisplayText("CHECK TeliumPass\nPRESENCE ", CUC30_ALIGN_CENTER);
		ttestall(0, 300);
		return STOP;
	}

 // led 1 blinking;
   TPass_LedsBlink(TPASS_LED_1, 10, 240);
}



/* Not USED IUN */
static int idle_message_UCMC(NO_SEGMENT AppliNum, char *pMessage_p)
{
    if( giDisplay > 0 )
        iLIBUCM_Display_Message(giDisplay, "Sample Cless\nPresent your\nCard", 0);

    if( pMessage_p[0] == 0 )
    {
        iGraphic_message( "Sample Cless\nPresent your\nCard", 0 );
    }
    else
    {
        iGraphic_message( pMessage_p, 0 );
    }

    if( giDisplayBackColor != 0 )
    {
        iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_WHITE);
    }

    // Turn on the reader screen backligth
    //TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

    // Turn off all the LEDs
    TPass_LedsOff (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);

    return (FCT_OK);
}


static int is_card_emv_for_you_(NO_SEGMENT AppliNum, const S_AID* pParamIn, S_CARDOUT* pParamOut)
{
	(void)pParamIn;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].cardappnumber = 0;
	//pParamOut->returned_state[pParamOut->response_number].cardapp;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_change_init_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.mask = MSK_NULL;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_delete_(NO_SEGMENT AppliNum, S_DELETE* pParamOut)
{
	(void)AppliNum;

	// Initialise the output parameter
	memset(pParamOut, 0, sizeof(*pParamOut));

	pParamOut->deleting = DEL_YES;

	return FCT_OK;
}

static int is_evol_pg_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_for_you_after_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_CARDOUT* pParamOut)
{
	(void)pParamIn;
   char ucTemp[200];
   
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].cardappnumber = 0;
	//pParamOut->returned_state[pParamOut->response_number].cardapp;
	pParamOut->response_number++;

   sprintf( ucTemp, "is_for_you_after" );
   trace( 0x6E01, strlen(ucTemp), ucTemp);

	return FCT_OK;
}

static int is_for_you_before_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_ETATOUT* pParamOut)
{
	(void)pParamIn;
   char ucTemp[200];
   
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = 0;
	pParamOut->response_number++;

   sprintf( ucTemp, "is_for_you_before" );
   trace( 0x6E01, strlen(ucTemp), ucTemp);

	return FCT_OK;
}

static int is_licenced_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_KO;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_name_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_state_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
//	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
//		sizeof(pParamOut->returned_state[pParamOut->response_number]));

//	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
//		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
//	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
//	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
//	pParamOut->response_number++;
      S_ETATOUT etatout;
   
      memcpy (&etatout, pParamOut, sizeof(etatout));
   
      etatout.returned_state[etatout.response_number].state.response = REP_OK;
      etatout.returned_state[etatout.response_number].no_appli = AppliNum;
      etatout.response_number++;
   
      memcpy (pParamOut, &etatout, sizeof(etatout));

	return FCT_OK;
}

static int is_time_function_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_KO;
	pParamOut->response_number++;

	return FCT_OK;
}

static int give_your_domain_(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut)
{
	(void)AppliNum;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	if( gucCinematicType == 2) /* Vending payment cinematic EXE MDB */
	{
      pParamOut->returned_state[pParamOut->response_number].mask = MSK_MDP|MSK_SWIPE|MSK_TYPE_PPAD|MSK_PINPAD|MSK_STANDARD|MSK_LANGUE|MSK_FRMT_DATE|MSK_DATE;
   }
   else
   {
    pParamOut->returned_state[pParamOut->response_number].mask = MSK_ALL_PARAM;
   }
    
	pParamOut->returned_state[pParamOut->response_number].application_type = TYP_EXPORT;
	pParamOut->response_number++;

	return FCT_OK;
}


static int more_function_(NO_SEGMENT AppliNum)
{
	(void)AppliNum;
	
        iGraphic_message( "Menu graphic", 100 );

	TPassMenu_MainMenu ();
			
	return FCT_OK;
}

static int state_(NO_SEGMENT AppliNum)
{
	// Print the version
	//PrintAppliVersion(AppliNum, FALSE);
	iUN_CAD30_PrintAppliVersion(AppliNum, FALSE);
	return FCT_OK;

}

/////////////////////////////////////////////////////////////////
//// give_your_specific_context_ ////////////////////////////////
/////////////////////////////////////////////////////////////////
int give_your_specific_context (NO_SEGMENT AppliNum,void * p1, S_SPECIFIC_CONTEXT *pParamOut )
{
	unsigned char ucTemp[200];
   
	// Used to specify the list of parameters
	pParamOut->returned_state[pParamOut->response_number].mask             = 0;
	// My type of application
	pParamOut->returned_state[pParamOut->response_number].type             = TYPE_APPLI_NON_BANCAIRE;

	if( gucCinematicType == 2) /* Vending payment cinematic EXE MDB */
	{
      // support
	   pParamOut->returned_state[pParamOut->response_number].support		   = CLESS_SUPPORT_MASK; // to detect chip from idle screen
      sprintf( ucTemp, "give_your_specific_context CLESS ON IDLE" );
      trace( 0x6E01, strlen(ucTemp), ucTemp);

   }
   else
   {
	   pParamOut->returned_state[pParamOut->response_number].support		   = 0; // not to detect chip from idle screen
      sprintf( ucTemp, "give_your_specific_context CLESS OFF" );
      trace( 0x6E01, strlen(ucTemp), ucTemp);

   }
   
	// My reference
	strcpy((char *)pParamOut->returned_state[pParamOut->response_number].appname,(const char *)tcAppName_g);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->response_number++;
   
	return (FCT_OK);
}

static int cless_give_info_(NO_SEGMENT AppliNum, S_TRANSIN * pParamIn, S_CLESS_GIVEINFO* pParamOut)
{
	TLV_TREE_NODE hOutputTlvTree;
	int nResult;
	unsigned char ucTemp[200];

   sprintf( ucTemp, "give_info START" );
   trace( 0x6E01, strlen(ucTemp), ucTemp);
   
   nResult = 0;
	if (DumpOpenOutputDriver())
	{
		if (pParamIn->entry != NO_ENTRY)
		{
			// Print
			DumpData ("CLESS_GIVE_INFO");

			if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
				DumpData ("\x0f");
			
//			DumpData ("S_TRANSIN content :");
//			DumpNewLine ();
			DumpData ("S_TRANSIN content :\nTransaction amount = %02lx ->%lu", pParamIn->amount, pParamIn->amount);
//			DumpNewLine ();
			DumpData ("Currency Code = %c%c%c", pParamIn->currency.code[0], pParamIn->currency.code[1], pParamIn->currency.code[2]);
//			DumpNewLine ();
			DumpData ("Currency Label = %c%c%c", pParamIn->currency.nom[0], pParamIn->currency.nom[1], pParamIn->currency.nom[2]);
//			DumpNewLine ();
//			DumpNewLine ();

//			if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
//				DumpData("\x1b" "@");
		}
	}

	memset (pParamOut, 0, sizeof(*pParamOut));

	// Create the TLV Tree
	hOutputTlvTree = TlvTree_New(0);
	
	// Fill the hOutputTlvTree with the correct parameters (depending on the choosen configuration identifier)
	DllTesting_ParametersManagement_GetParameters(hOutputTlvTree);
	
	if (hOutputTlvTree != NULL)
	{
		// Serialize the TLV Tree in the DEL * of pParamOut
		nResult = TlvTree_Serialize(hOutputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (unsigned char *)(&(pParamOut->del)), sizeof (_DEL_));
		
		if (nResult < 0)
		{
         sprintf( ucTemp, "give_info TlvTree_Serialize < 0" );
         trace( 0x6E01, strlen(ucTemp), ucTemp);

			memset (&(pParamOut->del), 0, sizeof (_DEL_));
		}

		// Release the TLV Tree
		TlvTree_Release(hOutputTlvTree);
	}
   else
   {
      sprintf( ucTemp, "give_info hOutputTlvTree = NULL" );
      trace( 0x6E01, strlen(ucTemp), ucTemp);
   }
	
/*	if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
	{
		DumpData("\x1b" "@");
		DumpNewLine ();
		DumpNewLine ();
		DumpNewLine ();
	}*/
	DumpCloseOutputDriver ();


//   DumpData ("CLESS_GIVE_INFO END=%d\n", nResult);
//   DumpNewLine ();

   sprintf( ucTemp, "give_info END nResult=%d", nResult );
    trace( 0x6E01, strlen(ucTemp), ucTemp);
   
	return (FCT_OK);
}

int iUcmIac_Buz( unsigned char ucChannel_p, unsigned char ucCmd_p, unsigned short usDelay_p )
{
	T_UCMC_IAC_BUZ sBuz;

	sBuz.ucCmd = ucCmd_p;
	sBuz.usDelay = usDelay_p;

	return( /*iLIBUCM_BUZZER_Cmd*/ iLIBUCM_BUZZER_CmdCh( ucChannel_p, &sBuz ) );
}

int iDebit_Mission ( T_UCMHOST_DEBIT *psDebit_p )
{
int             iRet;
unsigned char ucTemp[ 200 ];
int iDsp;

   memset( psDebit_p, 0, sizeof( T_UCMHOST_DEBIT) );

   sprintf( ucTemp, "iDebit_Mission");
   trace( 0x6E01, strlen( ucTemp), ucTemp ) ;
   
	psDebit_p->ucFunction = CLESS_DEBIT_AID; /* Nom du point d'entree a rappeler pour enregistrement*/
   psDebit_p->ucTrsSupport = CLESS_SUPPORT ;
   psDebit_p->ucTrsMode = 0; /* v0300 1 en vending */

	iRet = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), psDebit_p ) ;

   iDsp = iLIBUCM_Display_Exist( UCMC_DISPLAY ) ;

   /* pour effacer l'écran partage avec le gestionnnaire */
   iLIBUCM_Display_Clear( UCMC_DISPLAY_ICL ) ;

	switch( iRet )
	{
		case UCMCPAY_SOLV:
      	  sprintf( ucTemp, "CLESS SOLV %d\nAmount=%lu",
             psDebit_p->ucClasse, psDebit_p->ulAmount );


     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
            if( giDisplay > 0 )        
                iLIBUCM_Display_Message( giDisplay, ucTemp, 200 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }
     
		break;

		case UCMCPAY_RECORD:
      	sprintf( ucTemp, "CLESS RECO" );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
                if( giDisplay > 0 )    
                        iLIBUCM_Display_Message( giDisplay, ucTemp, 200 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }
		break;

		case UCMCPAY_SOLV_LOC:
      	sprintf( ucTemp, "CLESS SOLV\nLOC" );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
                if( giDisplay > 0 )    
                        iLIBUCM_Display_Message( giDisplay, ucTemp, 100 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }
		break;

		case UCMCPAY_RECORD_LOC:
      	sprintf( ucTemp, "CLESS RECO\nLOC" );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
                if( giDisplay > 0 )    
                        iLIBUCM_Display_Message( giDisplay, ucTemp, 100 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }
		break;

		case UCMCPAY_CARD_INFO:
      	sprintf( ucTemp, "CLESS CARD\nINFO" );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
                if( giDisplay > 0 )    
                     iLIBUCM_Display_Message( giDisplay, ucTemp, 100 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }
		break;

		case UCMCPAY_REVALUE_EPURSE:
      	sprintf( ucTemp, "CLESS REVALUE\nSOLV" );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
            if( giDisplay > 0 )    
                 iLIBUCM_Display_Message( giDisplay, ucTemp, 100 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }
		break;

      case UCMCPAY_ASK_EPURSE_BALANCE:
      	sprintf( ucTemp, "CLESS ASK EP\nBAL" );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
                if( giDisplay > 0 )    
                    iLIBUCM_Display_Message( giDisplay, ucTemp, 100 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }

		break;

		default:
      	sprintf( ucTemp, "CLESS DEBIT\n??? %d", iRet );
     	   if( iLIBUCM_Print_Exist( UCMC_PRINT ) > 0 )
         {
	   	   iLIBUCM_Print_Message( UCMC_PRINT, ucTemp ) ;
         }

     	   if( iDsp > 0 )
         {
              if( giDisplay > 0 )    
                    iLIBUCM_Display_Message( giDisplay, ucTemp, 100 ) ;
         }
         else
         {
            trace( 0x6E01, strlen(ucTemp), ucTemp);
         }

			iRet = -11;
		break;
	}

   return ( iRet );
}

static int cless_debit_aid_Banking (NO_SEGMENT AppliNum, unsigned int nSize, void * pData, int iWhoCalled_p)
{
T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;

int iWhat, iRet;
T_UCMHOST_DEBIT sDebit;
T_UCMHOST_R_DEBITV3 sRDeb; 


    (void)AppliNum;
    (void)nSize;

    pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;


   if (gucCinematicType != 0)
    {

    iWhat = iDebit_Mission( &sDebit ) ;


    switch( iWhat )
    {
        case UCMCPAY_SOLV:
            if( iLIBUCM_BUZZER_Exist() > 0 )
            {
                iUcmIac_Buz( UCMC_BUZZER_ICL, UCMC_BUZ_NORMAL, 1 ) ;
            }

            /******* RESPONSE ************/
            memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;

            //TODO debit card
            // amount  sDebit.ulAmount
            sRDeb.ucTypeCardStruct = UCMHOST_CARD_UNKNOWN ;
            sRDeb.ucCr			=UCMHOST_CR_OK;
            sRDeb.ulAmount=sDebit.ulAmount;
            if( giDisplay > 0 )    
                iGraphic_message( "SOLV OK", 200 );   

            //        				iLIBUCM_Display_Message ( giDisplay, "DEBIT OK", 100 ) ;
            sRDeb.ucFunction   = UCMHOST_FCT_SOLV ;
            sRDeb.usAppName    = AppliNum ;
            strcpy ( (char *)sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;

            memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
            memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
            sRDeb.tCurrency.posdec = 2 ;

            iRet=iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) ;	

            iLIBUCM_Pay_End (sizeof( T_UCMHOST_R_DEBIT ), &sRDeb);
        break;

        case UCMCPAY_RECORD:
            memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;

            //TODO record transaction
            // update amount  sDebit.ulAmount

            sRDeb.ucCr         = UCMHOST_CR_OK ;

            sRDeb.ucFunction   = UCMHOST_FCT_ENREG ;
            sRDeb.usAppName    = AppliNum ;
            strcpy ( (char *)sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;

            sRDeb.ulAmount=sDebit.ulAmount;

            read_date( &sRDeb.u.sCard.uAppli.sApp.sLocalDate ) ;

            memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
            memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
            sRDeb.tCurrency.posdec = 2 ;

            if( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) < 0 )
            {
                if( giDisplay > 0 )    
                  iLIBUCM_Display_Message ( giDisplay, "Result_Debit\nKO", 100 ) ;
            }

            iLIBUCM_Pay_End (sizeof( T_UCMHOST_R_DEBIT ), &sRDeb);							

        break;
    }
   }
   else
   {
      iUcmIac_BckColor(giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_GREEN);
      TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
      TPass_BuzzerBeep(1500, 50, 5);
      if (giDisplay > 0)
          iGraphic_message("CLESS DEBIT  -  OK", 200);
      TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
   }

    if (DumpOpenOutputDriver())
    {
        // Print
        if( iWhoCalled_p == CLESS_DEBIT_AID )
        {
            DumpData ("CLESS_DEBIT_AID\n\n");
        }
        else
        {
            DumpData ("CLESS_DEBIT\n\n");
        }
        //		DumpNewLine ();
        //		DumpNewLine ();

      /*
      if (giDisplayBackColor != 0)
      {
         iUcmIac_BckColor(giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_BLUE);

         iLIBUCM_Display_Message(giDisplayBackColor, "BKL BLUE", 5);
      }*/
    }

    if (nSize != sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT) )
    {
        if( giDisplayBackColor != 0 )
        {   	
            iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_CYAN);
            iLIBUCM_Display_Message( giDisplayBackColor, "BKL CYAN", 50 ) ;
        }
        DumpData ("nSize %d<>%lu not a shared structure\n", nSize, sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT) );
        //		DumpNewLine ();
        //		DumpData ("(nSize = %02x\n\n", nSize);
        //		DumpNewLine ();
        //		DumpNewLine ();

        //		return CLESS_CR_MANAGER_END;
    }
    else
    {
        DllTesting_DumpData_DumpSharedBuffer (pSharedStruct->pDataStruct, 0);

        if( giDisplayBackColor != 0 )
        {
         //iUcmIac_BckColor(giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_GREEN);
         //iLIBUCM_Display_Message(giDisplayBackColor, "BKL GREEN", 50);
        }

        if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
        {
            //		DumpData("\x1b" "@" "\n\n\n");
            //		DumpNewLine ();
            //		DumpNewLine ();
            //		DumpNewLine ();
        }
    }

    DumpCloseOutputDriver ();   


    return (CLESS_CR_MANAGER_END);
}

static int __TestIso_DetectCard (int nTimeout,unsigned char * pcErrMsg)
{
	unsigned int nNumOfCards;
	int nResult;

    // Open the driver
    if (ClessEmv_OpenDriver() == CL_OK)
    {
		nNumOfCards = 1;

		//Deselect the card (synchronous mode)
		nResult = ClessEmv_DetectCards(CL_TYPE_AB, &nNumOfCards, nTimeout);
	
        // Close the driver
        ClessEmv_CloseDriver();

		switch(nResult)
		{
			case CL_OK: // Card correctly detected
				return TRUE;
				break;

			case CL_KO: // An error occurs during the card detection
				if (pcErrMsg!=NULL)
				{
					strcpy((char *)pcErrMsg,"INVALID CARD");
				}
				break;

			case CL_NOCARD: // No card has been detected
				break;

			case CL_TOOMANYCARDS: // Too many cards on the reader
				if (pcErrMsg!=NULL)
				{
					strcpy((char *)pcErrMsg,"TOO MANY CARDS");
				}
				break;

			case CL_INVALIDCARD: // The presented card is not valid
				if (pcErrMsg!=NULL)
				{
					strcpy((char *)pcErrMsg,"INVALID CARD");
				}
				break;

			default: // Default case
				if (pcErrMsg!=NULL)
				{
					strcpy((char *)pcErrMsg,"INVALID CARD");
				}

				break;
			}
    }
	return FALSE;
}

static int __TestIso_DeselectCard (unsigned char  nCardIndex_p,unsigned int  bSendDeselect_p, unsigned int  bWaitRemove_p )
{
	int nResult;

    // Open the driver
    nResult = ClessEmv_OpenDriver();
    
    if (nResult == CL_OK)
    {

         nResult = ClessEmv_DeselectCard  ( nCardIndex_p,  bSendDeselect_p, bWaitRemove_p ) ;
    }
    
   return nResult;
}
static int cless_debit_aid_Vending(NO_SEGMENT AppliNum, unsigned int nSize, void * pData, int iWhoCalled_p)
{
   T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;
   char                   cMess [ 100+1 ] ;
   char                   cErrMess [ 100+1 ] ;

   int                    iSize ;
   int                    iWhat ;
   unsigned short         usEvent ;

   unsigned char          ucState ;
   unsigned long          ulEpurseBalance ;
   unsigned long          ulCreditAmount;
   unsigned char          ucMultiVend ;
   unsigned char		   bIccOK;
   unsigned char          bPreselected ;

   T_UCMHOST_DEBIT        sDebit ;
   T_UCMHOST_R_DEBIT      sRDeb ;
   T_UCMHOST_DA_EPURSE_BALANCEV3        sEpurseBalance ;
   T_UCMHOST_DA_CR_EPURSE_REVALUEV3     sEpurseRevalue;
   T_UCMHOST_DA_CR_REC_EPURSE_REVALUE sRecEpurseRevalue;	
   T_UCMC_IAC_HOST2        sHostCmd ;
   T_UCMC_IAC_HOST2        sHostCmdAnsw ;
   unsigned char ucTemp[200];


   (void)AppliNum;
   (void)nSize;

   pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;

   sprintf( ucTemp, "cless_debit_aid_Vending_START %d", iWhoCalled_p );
   trace( 0x6E01, strlen(ucTemp), ucTemp);
   upload_diagnostic_txt("CLESS6E cless_debit_aid_Vending_START");

   ucMultiVend        = 0 ;
   ulCreditAmount     = 0 ;
   cErrMess[0]=0;
   ulEpurseBalance     = 100 ;
   
   memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
   memset ( &sDebit, 0x00, sizeof ( T_UCMHOST_DEBIT ) ) ;
   iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

   bPreselected=FALSE;

   switch( iWhat )
   {
      case UCMCPAY_ASK_EPURSE_BALANCE:
         ucState=STATE_EPURSE_BALANCE;
      break;

      case UCMCPAY_SOLV:
      case UCMCPAY_ASK_DEFAULT_BALANCE:
         ucState=STATE_DEBIT;
         bPreselected=TRUE;
      break;

      default:
         ucState=STATE_REMOVE_CARD;
      break;
   }

   bIccOK=TRUE;

   do
    {
      switch(ucState)
      {
         case STATE_EPURSE_BALANCE:	// read and display Balance
         {
            bPreselected=FALSE;

            // ***balance reading must be implemented here
            sHostCmd.usHostCmd = UCMHOSTLIB_CMD_EPURSE_BALANCE ;
            sHostCmd.usHostWaitTimeout = 10 ; /* 10 secondes */
            sHostCmd.usSize = sizeof( sEpurseBalance ) ;
            memset(&sEpurseBalance,0,sizeof(sEpurseBalance));

            TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);
            TPass_LedsOn(TPASS_LED_1);
            ttestall(0,10);
            TPass_LedsOn(TPASS_LED_1|TPASS_LED_2);

            if (bIccOK)
            {
               ttestall(0,10);
               TPass_LedsOn(TPASS_LED_1|TPASS_LED_2|TPASS_LED_3);

               sEpurseBalance.ucCr            = UCMHOST_CR_OK ;
               sEpurseBalance.ucAllowRevalue	=1 ;
               sEpurseBalance.ucAllowRefund	=1 ;
               sEpurseBalance.ucAllowMultiVend	=1;
               sEpurseBalance.ucAllowDisplayBalance =1 ;
               sEpurseBalance.ulEpurseBalance = ulEpurseBalance ;
               memcpy ( sEpurseBalance.tucCurrencyCode, "978", 3 ) ;
               memcpy ( sEpurseBalance.tucLanguageCode, "250", 3 ) ;
               if (sEpurseBalance.ucAllowRevalue)
               {
                  sEpurseBalance.ulRevalueLimitBalance=5000 ;	// max value of Epurse Balance (50€ for ex)
                  sEpurseBalance.ulRevalueLimitAmount=200; // max value of Epurse Balance (2€ for ex)
               }
               else
               {	// else not supported
                  sEpurseBalance.ulRevalueLimitBalance=0;
                  sEpurseBalance.ulRevalueLimitAmount=0;
               }

            }
            else
            {
               sEpurseBalance.ucCr = UCMHOST_CR_CARDINCIDENT ; // to buzz and blink red LED
            }

            memcpy ( sHostCmd.u.ucBuf, ( unsigned char * ) &sEpurseBalance, sizeof ( sEpurseBalance ) ) ;

            iSize = ( sizeof( T_UCMC_IAC_HOST2 ) - UCMC_IAC_HOST2_BUFFER_SIZE )
            		+ sizeof( sEpurseBalance ) ;

            if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) == FCT_OK )
            {
               if (bIccOK)
               {
                  if( giDisplayBackColor != 0 )
                  {
                     iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_GREEN);
                  }

                  sprintf(cMess,"\nBAL %5ld.%02ld"
                  			  "\nYOUR CHOICE ? **\n",ulEpurseBalance/100,ulEpurseBalance%100);
                  iLIBUCM_Display_Option( UCMC_DISPLAY, cMess , UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;
                  ucState = STATE_WAIT_EVT ;
               	}
               	else
               	{
                     sprintf( ucTemp, "STATE_EPURSE_BALANCE called=%d iWhat=%d", iWhoCalled_p, iWhat );
                     trace( 0x6E01, strlen(ucTemp), ucTemp);

               		strcpy(cErrMess,"  INVALID CARD");
               		ucState = STATE_REMOVE_CARD ;
               	}

               }
               else
               {
               	strcpy(cErrMess,"INTERNAL ERROR");
               	iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nBALANCE KO" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
               	ucState = STATE_REMOVE_CARD ;
               }
               TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);

               }break;

				case STATE_WAIT_EVT: // wait for event (ICC or DLL instructions)
				{
					memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
					memset ( &sDebit, 0x00, sizeof ( T_UCMHOST_DEBIT ) ) ;
					usEvent = UCMMULTI_TTESTALL_HOST ;

					if( iLIBUCM_Device_Ttestall( &usEvent, 30000) == UCMTTESTALL_CR_OK_EVENT )
					{
						if( (usEvent & UCMMULTI_TTESTALL_HOST) != 0 )
						{

							iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

							switch( iWhat )
							{
								case UCMCPAY_ASK_EPURSE_BALANCE :		ucState=STATE_EPURSE_BALANCE;break; // ask for balance
								case UCMCPAY_SOLV :						ucState=STATE_DEBIT;break;	// selection done, debit card
								case UCMCPAY_RECORD:					ucState=STATE_DEBIT_RECORD;break; // distribution finished
								case UCMCPAY_REVALUE_EPURSE:			ucState=STATE_REVALUE;break; // revalue request
								case UCMCPAY_RECORD_REVALUE_EPURSE :	ucState=STATE_REVALUE_RECORD;break; //revalue finished
								case UCMCPAY_HOST_REMOVE_CARD :			ucState=STATE_REMOVE_CARD;break; // cancelled

								default:
									iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nEVT UNKNOWN" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;

									strcpy(cErrMess,"INTERNAL ERROR");
									ucState = STATE_REMOVE_CARD ;
									break;
							}

						}
					}
					else
					{
                                        if( giDisplay > 0 )    
                                        {
            						iLIBUCM_Display_Clear(giDisplay);
						    iLIBUCM_Display_Message ( giDisplay, "DLL\nEVT KO", 100 ) ;
                                        }
						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}
				}break;

            case STATE_DEBIT:
            {
               sprintf( ucTemp, "STATE_DEBIT fct=%d cmd=%d sel=%d pre=%d", sDebit.ucFunction, 
                     sDebit.u.tDaAskForDebit.ucCmd, sDebit.u.tDaAskForDebit.ucSelectionNotDefined, bPreselected);
               trace( 0x6E01, strlen(ucTemp), ucTemp);

               if ( ( sDebit.ucFunction == UCMHOST_FCT_SOLV ) &&
                  ( ( sDebit.u.tDaAskForDebit.ucCmd == UCMCPAY_SOLV ) || ( sDebit.u.tDaAskForDebit.ucCmd == UCMCPAY_ASK_DEFAULT_BALANCE ) ) )
               {

                  if (sDebit.u.tDaAskForDebit.ucSelectionNotDefined==0)
                  { 
                     if( !bPreselected ) /* preselect = card is present */
                     {
                        /* test if card present */           
                        if( iWhoCalled_p == CLESS_DEBIT_AID )
                        {
                        	__TestIso_DeselectCard( 0,FALSE,FALSE);

                           /* TO=0 just to see if card is present */
                           if (__TestIso_DetectCard (0,(unsigned char *)cErrMess))
                           {
                              bIccOK=TRUE;
                           }
                           else
                           {
                              bIccOK=FALSE;
                           }
                        }
                        else
                        {
                           bIccOK=FALSE;
                        }
                     }
                     else
                     {
                         bIccOK=TRUE; /* preselect = card is present */
                     }

                     if ((!bIccOK)&&(!bPreselected)) // only if card not present and no preselected sale
                     {

                        if( iWhoCalled_p == CLESS_DEBIT_AID )
                        {
                           if( giDisplayBackColor != 0 )
                           {
                              iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_BLUE);
                           }

                           iLIBUCM_Display_Option( UCMC_DISPLAY, "DEBIT\nPRESENT\nYOUR CARD" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;

                           __TestIso_DeselectCard(0,FALSE,FALSE);

                           if (__TestIso_DetectCard(sDebit.usToWaitingCard,(unsigned char *)cErrMess))
                           {
                              bIccOK=TRUE;
                           }
                           else
                           {
                              bIccOK=FALSE;
                           }
                        }
                        else
                        {
                           bIccOK=TRUE;
                        }
                     }

                     if (bIccOK==TRUE)
                     {
                        ucMultiVend = sDebit.u.tDaAskForDebit.ucVendType ;

                        TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);
                        TPass_LedsOn(TPASS_LED_1);
                        ttestall(0,10);
                        TPass_LedsOn(TPASS_LED_1|TPASS_LED_2);
                        ttestall(0,10);
                        TPass_LedsOn(TPASS_LED_1|TPASS_LED_2|TPASS_LED_3);

                        /* epurse DEBIT */
                        if (sDebit.u.tDaAskForDebit.uiSelectionPrice<=(unsigned int)ulEpurseBalance)
                        {
//                        pParamDa_p->tPriceTable [pParamDa_p->ucNbSelection ].uiPrixCarte 
                           ulEpurseBalance -= sDebit.u.tDaAskForDebit.uiSelectionPrice ;
                           bIccOK=TRUE; // Debit OK
                           TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);
                           TPass_BuzzerBeep(1500, 50, 5);
                        }
                        else
                        {
                           bIccOK=FALSE; // Debit KO
                           strcpy(cErrMess,"REFUSED\nFOR DEBIT");
                        }

                      }
                      else
                      {
                        strcpy(cErrMess,"NO CARD\nFOR DEBIT");
                      }


                     /******* RESPONSE ************/
                     memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
                     sRDeb.ucDiag       = FCT_OK ;
                     sRDeb.ucFunction   = UCMHOST_FCT_SOLV ;
                     sRDeb.usAppName    = AppliNum ;
                     strcpy ( sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;
                     memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
                     memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
                     sRDeb.tCurrency.posdec = 2 ;

                     if ( bIccOK)
                     {// debit ok
                        sRDeb.ucCr         = UCMHOST_CR_OK ;
                        sRDeb.ulAmount     = sDebit.u.tDaAskForDebit.uiSelectionPrice;
                        sRDeb.ucCardInside = 1 ;
                        sRDeb.u.sRDebitDa.ulEpurseBalance = ulEpurseBalance ;

                        if( giDisplayBackColor != 0 )
                        {
                           iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_YELLOW);
                        }

                        sprintf(cMess,"\nBAL %5ld.%02ld"
                             "\nVEND IN PROGRESS",
                             ulEpurseBalance / 100, ulEpurseBalance % 100);
                        iLIBUCM_Display_Option( UCMC_DISPLAY, cMess , UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;

                        ucState = STATE_WAIT_EVT ;
                     }
                     else
                     { // debit ko
                        sRDeb.ucCr         = UCMHOST_CR_REFUSED ;
                        sRDeb.u.sRDebitDa.ulEpurseBalance = 0 ;

                        ucState = STATE_REMOVE_CARD ;
                     }

                     if ( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) != FCT_OK )
                     {
                        iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nDEBIT KO" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
                        strcpy(cErrMess,"INTERNAL ERROR");
                        ucState = STATE_REMOVE_CARD ;
                     }

                  }
                  else
                  {
                     // product not defined in table price
                     strcpy(cErrMess,"SELECT\nNOT DEFINED");
                     ucState = STATE_REMOVE_CARD ;
                  }

               }
               else
               {
                  iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nDEBIT UNKNOWN" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
                  ucState = STATE_REMOVE_CARD ;
               }

               TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);
         }
            break;


				case STATE_DEBIT_RECORD : // distribution finished
				{
					if ( ( sDebit.ucFunction == UCMHOST_FCT_ENREG ) &&
						  ( sDebit.u.tDaCrDistribution.ucCmd == UCMCPAY_RECORD ) )
					{
						if ( sDebit.u.tDaCrDistribution.ucCrDistribution == FCT_OK )
						{
							// distribution succeded
						}
						else
						{
							// distribution failed
							ucMultiVend=0; // VMC can't continue
						}
						// *TODO* store record for statistics...

						sRDeb.ucCr         = UCMHOST_CR_OK ;
						sRDeb.ucDiag       = UCMHOST_CR_OK ;
						sRDeb.ucFunction   = UCMHOST_FCT_ENREG ;
						sRDeb.usAppName    = AppliNum ;
						strcpy ( sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;
						memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
						memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
						sRDeb.tCurrency.posdec = 2 ;
						sRDeb.u.sRDebitDa.ulEpurseBalance = ulEpurseBalance ;

						// DETECT CHIP
						__TestIso_DeselectCard( 0,FALSE,FALSE);
                                if( iWhoCalled_p == CLESS_DEBIT_AID )
                                {
      						if (__TestIso_DetectCard (0,(unsigned char *)cErrMess))
      						{
      							 sRDeb.ucCardInside = 1 ;
      						}
      						else
      						{
      							sRDeb.ucCardInside = 0 ;
      						}
                                 }
                                 else
                                 {
      							sRDeb.ucCardInside = 0 ;
                                  }
	
						if( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) ==FCT_OK )
						{
							if (( ucMultiVend  )  && (sRDeb.ucCardInside))
							{
								iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

								if (iWhat==UCMCPAY_ASK_EPURSE_BALANCE)
								{
									ucState=STATE_EPURSE_BALANCE;
								}
								else
								{
									iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nMULTIVEND KO" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
									strcpy(cErrMess,"INTERNAL ERROR");
									ucState = STATE_REMOVE_CARD ;
								}

							}
							else
							{
								ucState = STATE_REMOVE_CARD ;
							}

						}
						else
						{
							iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nRECORD KO" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;

							strcpy(cErrMess,"INTERNAL ERROR");
							ucState = STATE_REMOVE_CARD ;
						}

					}
					else
					{

						iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nRECORD UNKNOWN" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;

						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}

				}
				break ;

				case STATE_REVALUE :
				{
					ulCreditAmount = 0 ;

					if (	( sDebit.ucFunction == UCMHOST_FCT_REVALUE )
						&&	( sDebit.u.tDaAskForRevalue.ucCmd == UCMCPAY_REVALUE_EPURSE )
						)
					{

						memset(&sHostCmd,0,sizeof(sHostCmd));
						sHostCmd.usHostCmd=UCMHOSTLIB_CMD_ANS_EPURSE_REVALUE;
						sHostCmd.usHostWaitTimeout=10;
						sHostCmd.usSize= sizeof( T_UCMHOST_DA_CR_EPURSE_REVALUEV3 ) ;
						if (sDebit.u.tDaAskForRevalue.uiRevalueAmount<200)	// Max revalue amount 200 for example
						{
							ulCreditAmount = sDebit.u.tDaAskForRevalue.uiRevalueAmount;
							sEpurseRevalue.ucCrRevalue     = UCMHOST_CR_OK ;
							sEpurseRevalue.ulRevalueAmount = ulCreditAmount ;
							sEpurseRevalue.ulEpurseBalance = ulEpurseBalance+ulCreditAmount ;
							ucState = STATE_WAIT_EVT ;
						}
						else
						{
							sEpurseRevalue.ucCrRevalue     = UCMHOST_CR_REFUSED ;
							strcpy(cErrMess,"CREDIT REFUSED");
							ucState = STATE_REMOVE_CARD ;

						}

						memcpy ( sHostCmd.u.ucBuf, &sEpurseRevalue, sizeof ( sEpurseRevalue ) ) ;

						iSize = ( sizeof( T_UCMC_IAC_HOST2 ) - UCMC_IAC_HOST2_BUFFER_SIZE )
								+ sizeof( T_UCMHOST_DA_CR_EPURSE_REVALUEV3 ) ;

						if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) != FCT_OK )
						{
                                                if( giDisplay > 0 )    
                                                {
        							iLIBUCM_Display_Clear(giDisplay);

        							iLIBUCM_Display_Message ( giDisplay, "DLL\nREVALUE KO", 100 ) ;
                                                 }
							strcpy(cErrMess,"INTERNAL ERROR");
							ucState = STATE_REMOVE_CARD ;
						}
					}
					else
					{
						iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nRECORD UNKNOWN" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}
				}
				break ;

				case STATE_REVALUE_RECORD :
				{
					if (	( sDebit.ucFunction == UCMHOST_FCT_REVALUE )
						&& 	( sDebit.u.tDaRecRevalue.ucCmd == UCMCPAY_RECORD_REVALUE_EPURSE )
						)
					{
						if ( sDebit.u.tDaRecRevalue.ucCrRevalue != 0 )
						{
							ulCreditAmount = 0 ;
						}

						// chip is present?
						if (ulCreditAmount!=0)
						{
							// *TODO* Credit Card (detect card if necessary)
							__TestIso_DeselectCard( 0,FALSE,FALSE);

                                    if( iWhoCalled_p == CLESS_DEBIT_AID )
                                    {

      							if (__TestIso_DetectCard (0,(unsigned char *)cErrMess))
      							{
      								bIccOK=TRUE;
      							}
      							else
      							{
      								bIccOK=FALSE;
      							}
                                    }
                                    else
                                    {
      								bIccOK=TRUE;
                                    }

							if (!bIccOK) // only if card not present
							{
								iLIBUCM_Display_Option( UCMC_DISPLAY, "CREDIT\nPRESENT\nYOUR CARD" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;

                                         if( iWhoCalled_p == CLESS_DEBIT_AID )
                                          {

      								if (__TestIso_DetectCard(40,(unsigned char *)cErrMess))
      								{
      									bIccOK=TRUE;
      								}
      								else
      								{
      									bIccOK=FALSE;
      								}
                                          }
                                          else
                                          {
      									bIccOK=TRUE;
                                          }
							}

							if (bIccOK)
							{
								TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);
								TPass_LedsOn(TPASS_LED_1);
								ttestall(0,10);
								TPass_LedsOn(TPASS_LED_1|TPASS_LED_2);
								ttestall(0,10);
								TPass_LedsOn(TPASS_LED_1|TPASS_LED_2|TPASS_LED_3);


								ulEpurseBalance = ulEpurseBalance + ulCreditAmount ;

								TPass_LedsOn(TPASS_LED_1|TPASS_LED_2|TPASS_LED_3|TPASS_LED_4);
							}
							else
							{
								ulCreditAmount =0;
							}


						}


						memset(&sHostCmd,0,sizeof(sHostCmd));
						sHostCmd.usHostCmd=UCMHOSTLIB_CMD_ANS_REC_EPURSE_REVALUE;
						sHostCmd.usHostWaitTimeout=10;
						sHostCmd.usSize= sizeof( T_UCMHOST_DA_CR_REC_EPURSE_REVALUE ) ;

						if (ulCreditAmount>0)
						{

							sRecEpurseRevalue.ucCrRecRevalue = UCMHOST_CR_OK ;
							ucState = STATE_WAIT_EVT ;
						}
						else
						{
							sRecEpurseRevalue.ucCrRecRevalue = UCMHOST_CR_REFUSED ;

							strcpy(cErrMess,"REVALUE FAILED");
							ucState = STATE_REMOVE_CARD ;
						}

						memcpy ( sHostCmd.u.ucBuf, &sRecEpurseRevalue, sizeof ( sRecEpurseRevalue ) ) ;

						iSize = ( sizeof( T_UCMC_IAC_HOST2 ) - UCMC_IAC_HOST2_BUFFER_SIZE )
						+ sizeof( T_UCMHOST_DA_CR_REC_EPURSE_REVALUE ) ;

						if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) == FCT_OK )
						{
								sprintf(cMess,"\nBAL %5ld.%02ld"
                          "\nREVALUE",
                          ulEpurseBalance / 100, ulEpurseBalance % 100);
								iLIBUCM_Display_Option( UCMC_DISPLAY, cMess , UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;
								TPass_BuzzerBeep(1000, 50, 5);
						}
						else
						{
							iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nRECORD RECORD\nKO" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
							strcpy(cErrMess,"INTERNAL ERROR");
							ucState = STATE_REMOVE_CARD ;
						}
					}
					else
					{
						iLIBUCM_Display_Option( UCMC_DISPLAY, "DLL\nRECORD RECORD\nUNKNOWN" , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}

					TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 |TPASS_LED_4);

         }
            break;

				case STATE_REMOVE_CARD:
				{
					
					__TestIso_DeselectCard( 0,FALSE,FALSE);

                           if( iWhoCalled_p == CLESS_DEBIT_AID )
                           {
               
      					if (__TestIso_DetectCard (0,(unsigned char *)cErrMess))
      					{

      						if (cErrMess[0]==0)
      						{
      							strcpy(cErrMess,"REMOVE CARD");
      						}

      						sprintf(cMess,"%s\nREMOVE CARD",cErrMess);

      						iLIBUCM_Display_Option( UCMC_DISPLAY, cMess , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;

      						__TestIso_DeselectCard( 0, TRUE, TRUE);

      					}
      					else
      					{
      						if (cErrMess[0]!=0) // error message to display
                  {
                     sprintf(cMess, "%s", cErrMess);
      							iLIBUCM_Display_Option( UCMC_DISPLAY, cMess , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 100 ) ;
      						}

      					}
                           }
                           else
                           {
   						if (cErrMess[0]==0)
   						{
   							strcpy(cErrMess,"REMOVE CARD");
   						}

   						sprintf(cMess,"%s\nREMOVE CARD",cErrMess);

   						iLIBUCM_Display_Option( UCMC_DISPLAY, cMess , UCMDISPLAY_CENTER|UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END, 0 ) ;

                           }

					ucState=STATE_END;
         }
            break;

				case STATE_END:
				default:
				{
					ucState=STATE_END;
         }
            break;
			}
		}while (ucState!=STATE_END);

		// to inform DLL that card has been removed and terminal is in idle state
		sHostCmd.usHostCmd = UCMHOSTLIB_CMD_END_DEBIT ;
		sHostCmd.usHostWaitTimeout = 10 ;
		sHostCmd.usSize = 0 ;

		iSize = ( sizeof( T_UCMC_IAC_HOST2 ) - UCMC_IAC_HOST2_BUFFER_SIZE ) ;

		iLIBUCM_Display_Clear(UCMC_DISPLAY);
		if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) != FCT_OK )
		{
			if( giDisplayBackColor != 0 )
			{
			  iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_RED );
			}

                        if( giDisplay > 0 )    
            			iLIBUCM_Display_Message ( giDisplay, "MSG END KO\n", 100 ) ;
		}
          else
          {

			if( giDisplayBackColor != 0 )
			{
			  iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_GREEN);
			}

                        if( giDisplay > 0 ) 
                            iGraphic_message( "MSG END\nOK", 200 );   
            			//iLIBUCM_Display_Message ( giDisplay, "MSG END OK\n", 100 ) ;
          }

		if (DumpOpenOutputDriver())
		{		
			// Print
			DumpData ("CLESS_DEBIT_AID\n\n");
	//		DumpNewLine ();
	//		DumpNewLine ();

		}

		if (nSize != sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT) )
		{
			DumpData ("nSize %d<>%lu not a shared structure\n", nSize, sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT) );
	//		DumpNewLine ();
	//		DumpData ("(nSize = %02x\n\n", nSize);
	//		DumpNewLine ();
	//		DumpNewLine ();

	//		return CLESS_CR_MANAGER_END;
		}
	   else
	   {
		   DllTesting_DumpData_DumpSharedBuffer (pSharedStruct->pDataStruct, 0);

			if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			{
	   //		DumpData("\x1b" "@" "\n\n\n");
	   //		DumpNewLine ();
	   //		DumpNewLine ();
	   //		DumpNewLine ();
			}
	   }

	   DumpCloseOutputDriver ();

		// Close the driver
//		ClessEmv_CloseDriver();
//	}

   
   sprintf( ucTemp, "cless_debit_aid_Vending_STOP" );
   trace( 0x6E01, strlen(ucTemp), ucTemp);

   if( giDisplayBackColor != 0 )
   {
      iUcmIac_BckColor( giDisplayBackColor, UCMCDISPLAY_BKL_COLOR_WHITE);
   }


	return CLESS_CR_MANAGER_END;
}

static int cless_end_ (NO_SEGMENT AppliNum)
{
	if (DumpOpenOutputDriver())
	{
		// Print
//		DumpData ("CLESS_END\n\n");
		
		if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		{
			DumpData("\x1b" "@" "\n\n\n");
		}
		DumpCloseOutputDriver ();
	}

   TPass_LedsOff(TPASS_LED_1);
   TPass_LedsBlink(TPASS_LED_1, 10, 240);
	return FCT_OK;
}

static int cless_is_for_you_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData)
{
	T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;
    unsigned char ucPriority;
	unsigned char ucTemp[200];
   
	(void)AppliNum;
	(void)nSize;

	pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;

   sprintf( ucTemp, "cless_is_for_you_ START" );
   trace( 0x6E01, strlen(ucTemp), ucTemp);
   
   upload_diagnostic_txt("CLESS6E cless_is_for_you_START");


	if (DumpOpenOutputDriver())
	{
		// Print
		DumpData ("CLESS_IS_FOR_YOU ");
		DumpNewLine ();
	}

	if (nSize != sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT))
	{
		DumpData ("Error : nSize not a shared structure");
		DumpNewLine ();
		DumpData ("(nSize = %02x", nSize);
		DumpNewLine ();
		DumpNewLine ();

		return FCT_OK;
	}

	DllTesting_DumpData_DumpSharedBuffer (pSharedStruct->pDataStruct, 0);

	if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
	{
		DumpData("\x1b" "@");
		DumpNewLine ();
		DumpNewLine ();
	}
	DumpCloseOutputDriver ();

	// Clear the buffer
    GTL_SharedExchange_ClearEx (pSharedStruct->pDataStruct, FALSE);

    /*  The TAG_GENERIC_PRIORITY tag is mandatory for new architecture if
		the application wants to manage the card on CLESS_DEBIT. If the tag
		is not provided, the application will not be called on CLESS_DEBIT,
		even if it returns STOP. */
    // Set the interest level (=priority)
    ucPriority = 30;
    GTL_SharedExchange_AddTag (pSharedStruct->pDataStruct, TAG_GENERIC_PRIORITY, 1, &ucPriority);

   sprintf( ucTemp, "cless_is_for_you_END" );
   trace( 0x6E01, strlen(ucTemp), ucTemp);
   upload_diagnostic_txt("CLESS6E cless_is_for_you_END");
   
	return FCT_OK;
}

int iAPP_Consult( T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet;
T_UCMHOST_APP_CONSULT *pConsult;

	iRet = FCT_OK;
	pdata_p->uiSize = sizeof( T_UCMHOST_APP_CONSULT );

	pConsult = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pConsult->sInfo );
	
	pConsult->ucAppStatus = UCMHOST_APP_STATUS_INIT_ACTIVE;
	pConsult->ucFileStatus = UCMHOST_APP_FILE_EMPTY;
	
   return( iRet );
}

int iAPPLIUCM_IAC( unsigned short usAppli_p , T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet;

	iRet = FCT_OK;
	
	switch( pdata_p->usFct )
	{
		case UCMHOST_FCTAPP_CONSULT:
			iRet = iAPP_Consult( pdata_p );
		break;
		
		case UCMHOST_FCTAPP_TLP_STATUS:
		case UCMHOST_FCTAPP_TLC_STATUS:
		case UCMHOST_FCTAPP_TLC_START:
      case UCMHOST_FCTAPP_NB_RECORD_LOC:
      case UCMHOST_FCTAPP_INFO_RECORD_LOC:
      case UCMHOST_FCTAPP_LIST_RECORD_LOC:
      case UCMHOST_FCTAPP_EVENT:
      case UCMHOST_FCTAPP_DATA:
   		iRet = -1;
      break;

      case UCMHOST_FCTAPP_IDLE_EVENT:
    	  idle_message_UCMC((NO_SEGMENT)ApplicationGetCurrent(), (char *)&pdata_p->Par.sDisplay.cBuf[0]);
    	  break;

		default:
			iRet = UCMERR_IAC_NO_FCT;
		break;
		
	}

	return( iRet ) ;
}

int MainAppliUCMC_IAC(unsigned int iSize_p, T_UCMC_IAC_SERVICE *pdata_p)
{
	int          iRet;
	object_info_t info;
	unsigned char ucTemp[ 100];
	
	ObjectGetInfo( OBJECT_TYPE_APPLI, pdata_p->usType_code, &info ) ;

	iRet = FCT_OK;
	
	switch( pdata_p->usService )
	{
		case SERVICE_APPLI_UCMC:	
			switch( pdata_p->usModule )
			{
				case UCMAPPLIMODULE_FCTAPP:
					iRet = iAPPLIUCM_IAC( pdata_p->usType_code, pdata_p ) ;
					
					if( iRet < 0 )
					{
						sprintf( ucTemp, "APPLIUCMC IAC FCT %04X %d\n", pdata_p->usFct, iRet );
						upload_diagnostic_txt( ucTemp ) ;
					}
										
				break;

            case UCMAPPLIMODULE_PROTOCOL:
					iRet = -5;
            break;				
				
				default:
					iRet = UCMERR_IAC_NO_MODULE;
               sprintf(ucTemp, "APPLIUCMC IAC Module %04X not exist %d\n", pdata_p->usModule, iRet);
					upload_diagnostic_txt( ucTemp ) ;

				break;
			}

		break;
		
		default:
			iRet = UCMERR_IAC_NO_SERVICE;
         sprintf(ucTemp, "APPLIUCMC IAC Service %04X not exist %d\n", pdata_p->usModule, iRet);
			upload_diagnostic_txt( ucTemp ) ;

			break;
	}

	return( iRet );
}


static int Main_(unsigned int nSize, StructPt* pData)
{
	NO_SEGMENT AppliNum;
	int nResult;

	(void)nSize;

   if( gucCinematicType == 0 ) /* not good value */
   {
      gucCinematicType = UCMCINEMATIC; /* forced to compilation value */
   }
  
	AppliNum = (NO_SEGMENT)ApplicationGetCurrent();
	switch(pData->service)
	{
	case AFTER_RESET:
		nResult = after_reset_(AppliNum, &pData->Param.AfterReset.param_out);
		break;
	case IS_CARD_EMV_FOR_YOU:
		nResult = is_card_emv_for_you_(AppliNum, &pData->Param.IsCardEmvForYou.param_in, &pData->Param.IsCardEmvForYou.param_out);
		break;
	case IS_CHANGE_INIT:
		nResult = is_change_init_(AppliNum, &pData->Param.IsChangeInit.param_out);
		break;
	case IS_DELETE:
		nResult = is_delete_(AppliNum, &pData->Param.IsDelete.param_out);
		break;
	case IS_EVOL_PG:
		nResult = is_evol_pg_(AppliNum, &pData->Param.IsEvolPg.param_out);
		break;
	case IS_FOR_YOU_AFTER:
		nResult = is_for_you_after_(AppliNum, &pData->Param.IsForYouAfter.param_in, &pData->Param.IsForYouAfter.param_out);
		break;
	case IS_FOR_YOU_BEFORE:
		nResult = is_for_you_before_(AppliNum, &pData->Param.IsForYouBefore.param_in, &pData->Param.IsForYouBefore.param_out);
		break;
	case IS_LICENCED:
		nResult = is_licenced_(AppliNum, &pData->Param.IsLicenced.param_out);
		break;
	case IS_NAME:
		nResult = is_name_(AppliNum, &pData->Param.IsName.param_out);
		break;
	case IS_STATE:
		nResult = is_state_(AppliNum, &pData->Param.IsState.param_out);
		break;
	case IS_TIME_FUNCTION:
		nResult = is_time_function_(AppliNum, &pData->Param.IsTimeFunction.param_out);
		break;
	case GIVE_YOUR_DOMAIN:
		nResult = give_your_domain_(AppliNum, &pData->Param.GiveYourType.param_out);
		break;
	case MORE_FUNCTION:
		nResult = more_function_(AppliNum);
		break;
	case STATE:
		nResult = state_(AppliNum);
		break;

	case GIVE_YOUR_SPECIFIC_CONTEXT:
		nResult = give_your_specific_context (AppliNum, NULL, &pData->Param.GiveYourSpecificContext.param_out);
		break;
	case CLESS_GIVE_INFO:
		nResult = cless_give_info_ (AppliNum, &pData->Param.ClessGiveInfo.param_in, &pData->Param.ClessGiveInfo.param_out);
		break;
	case CLESS_IS_FOR_YOU:
		nResult = cless_is_for_you_ (AppliNum, nSize, pData);
		break;
	case CLESS_DEBIT:
		//nResult = cless_debit_ (AppliNum, nSize, pData); 
	 if( gucCinematicType == 2) /* Vending payment cinematic EXE MDB */
	 {
		nResult = cless_debit_aid_Vending (AppliNum, nSize, pData, CLESS_DEBIT);
	 }
	 else
	 {
	  nResult = cless_debit_aid_Banking (AppliNum, nSize, pData, CLESS_DEBIT);
   }
		
		break;
	case CLESS_DEBIT_AID:
	 if( gucCinematicType == 2) /* Vending payment cinematic EXE MDB */
	 {
		nResult = cless_debit_aid_Vending (AppliNum, nSize, pData, CLESS_DEBIT_AID);
	 }
	 else
	 {
	  nResult = cless_debit_aid_Banking (AppliNum, nSize, pData, CLESS_DEBIT_AID);
   }
		break;
	case CLESS_END:
		nResult = cless_end_ (AppliNum);
		break;
	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}

static int give_interface_(unsigned short AppliNum, void* pParamIn, void* pParamOut)
{
	int i;

	(void)pParamIn;
	(void)pParamOut;

	for(i = 0; i < (int)(sizeof(Services) / sizeof(Services[0])); i++)
		Services[i].appli_id = AppliNum;

	ServiceRegister((sizeof(Services) / sizeof(Services[0])), Services);

	return FCT_OK;
}


void entry(void)
{
	object_info_t ObjectInfo;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	give_interface_(ObjectInfo.application_type, NULL, NULL);
}

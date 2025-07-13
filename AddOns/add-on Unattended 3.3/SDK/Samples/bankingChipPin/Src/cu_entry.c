/**
* \file cu_entry.c
* \brief This module contains the entry point functions called by the Manager.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "emv_sq.h"
#include "_emvdctag_.h"
#include "TagOS.h"
#include "MyTlvTree.h"
#include "EngineInterfaceLib.h"
#include "oem_sysfioctl.h"
#include "del_lib.h"
#include "cu_str.h"
#include "EmvEngineInterface.h"
#include "cu_term.h"
#include "cu_batch.h"
#include "cu_black.h"
#include "cu_base.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "convert.h"
#include "cu_param.h"
#include "gestion_param.h"
#include "cu_str.h"
#include "cu_serv.h"
#include "param.h"
#include "cu_file.h"
#include "cu_disk.h"
#include "cu_pinen.h"
#include "cu_more.h"
#include "cu_mess.h"
#include "cu_entry.h"
#include "serveng.h"
#include "sec_interface.h"
#include "Gpinpad.h"

#ifdef _USE_SPED_
#include "Sped.h"
#include "SpedLib.h"
#include "ext_api.h"
#endif

#ifdef _USE_UCM_
#include "ucmtelium.h"
#include "ucmhostdll.h"
#include "ucmclib.h"
#endif

#include "sec_interface.h"
#include "TlvTreeDel.h"
#include "EngineInterface.h"

#include "WGUI.h"
#include "cu_wgui.h"

#include "TrackIac.h"

#ifdef _TRACK_IAC_DC_
#include "spy.h"
#endif

//! \addtogroup Group_cu_entry
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

typedef int (*T_SERVICE_FUNCTION)(unsigned int nSize, void*Data);

typedef struct
{
	unsigned char   priority;
	unsigned char   cardholder;
	unsigned char   codeTableIndex;
	unsigned int    lengthPreferredName;
	unsigned char   preferredName[16];
	unsigned int    lengthApplicationLabel;
	unsigned char   applicationLabel[16];
	unsigned char   lengthLanguagePreference;
	unsigned char   languagePreference[8];
	unsigned int    lengthAID;
	unsigned char   AIDValue[16] ;
	unsigned int    lengthPDOL;
	DataElement     * PDOL;
}AIDCandidate;

typedef struct
{
	unsigned char    count;
	AIDCandidate    list[16];
}AIDCandidateList;

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

#ifdef _USE_UCM_
#define TYPE_UCMC		(0x12)
#define SERVICE_UCMC	(0x1201)
int UCM_Present;
int giDisplay;
int giDisplayBackColor;
int giModeMainteance;
int giDisplayType;
unsigned long gulPaymentAmount;
#endif

static char g_szAppName[32 + 1];
static NO_SEGMENT CustomNoAppli;
static unsigned short CUENT_IsFirst_Init;


#ifdef _TOOLWARE_
unsigned long			ulBegin_transaction;
extern unsigned long	get_tick_counter(void);
extern unsigned long    ulMMI_selappli;
extern unsigned long    ulMMI_langue;
#endif /* _TOOLWARE_ */

int isFallbackAllowed;

/*&BEGIN FT/09/4316/MA  Multi EMV Application*/
unsigned short CustApplicationNumber;
static  StructProcessStep _DELLocale;
static  DEL                DELLocale;
/*&END FT/09/4316/MA  Multi EMV Application*/


// Data needed to call the magstripe application. Declared as global
// parameters, because they does not fit in the stack.
/*static TRACK1_BUFFER bufIso1;
 static TRACK2_BUFFER bufIso2;
 static TRACK3_BUFFER bufIso3;
 static S_TRANSIN trans_in;
 static StructPt EntryPoint;
*/
static AIDCandidateList outAIDCandidateList;
static unsigned char num_aid_selected;

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

static void	Test_DLL_Security_Presence(void);
static void CUENT_First_Init (void);

#ifdef _TRACK_IAC_
void InitTrackIAC (void);
#endif

static int cu_Short_AID_List(byte* Tab,AIDCandidateList* aAIDCandidateList);
static int cu_AS_AffichageCardHolder(byte* TAB, AIDCandidateList *aAIDCandidateList);
static int cu_is_name(NO_SEGMENT noappli, void *param_in, S_ETATOUT *param_out);
/*&BEGIN FT/09/4316/MA  Multi EMV Application*/
static int IsdedicatedFile (S_FILE *param_in);
/*&END FT/09/4316/MA  Multi EMV Application*/
static void EMVCUST_Menu_Select_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

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

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */
void WaitingRemovedCard(void)
{
   int iRet, i;
   unsigned char ucCardInside;
   T_UCMC_IAC_BUZ sBuz;
   i = iLIBUCM_Icc_Status(UCMC_ICC, &ucCardInside);
   if (ucCardInside == UCMC_STATUS_CARD_INSIDE)
   {
      iLIBUCM_Display_No_Wait(UCMC_DISPLAY, "Remove Card\nPlease", 0);
      sBuz.ucCmd = UCMC_BUZ_NORMAL;
      sBuz.usDelay = 500;
      iLIBUCM_BUZZER_Cmd(&sBuz);
      iRet = iLIBUCM_Icc_Ttestall(UCMC_ICC, 500);
      sBuz.ucCmd = UCMC_BUZ_OFF;
      sBuz.usDelay = 0;
      iLIBUCM_BUZZER_Cmd(&sBuz);
   }
}

//===========================================================================
//! \brief This function waitcard if not inserted
//===========================================================================
unsigned char ucWaiting_CardInsert( unsigned short usTO_p )
{
int iRet;
unsigned char ucCardInside;
unsigned short usEvent ;

iRet = iLIBUCM_Icc_Status( UCMC_ICC, &ucCardInside ) ;

/* waiting card stop with key press */
if( ucCardInside == UCMC_STATUS_CARD_OUTSIDE )
{
    if( iLIBUCM_Pinpad_Exist( UCMC_PPAD ) > 0 )
    {
        usEvent = UCMMULTI_TTESTALL_ICC | UCMMULTI_TTESTALL_PINPAD ;
    }
    else
    {
        usEvent = UCMMULTI_TTESTALL_ICC ;
    }

    iLIBUCM_Display_No_Wait( UCMC_DISPLAY, "Insert Card\nPlease", 0 );
    iRet = iLIBUCM_Device_Ttestall( &usEvent, usTO_p );

    if( iRet  == UCMTTESTALL_CR_OK_EVENT )
    {
        if( (usEvent & UCMMULTI_TTESTALL_ICC) != 0 )
        {
        }

        if( (usEvent & UCMMULTI_TTESTALL_PINPAD) != 0 )
        {
        }
    }

    iRet = iLIBUCM_Icc_Status( UCMC_ICC, &ucCardInside ) ;
}

return( ucCardInside );
}

int iUcmIac_BckColor( unsigned char ucChannel_p, unsigned char ucCmd_p )
{
	int iRet;
   T_UCMC_DISPLAY_BACKLIGHT_COLOR sBlkColor;

   sBlkColor.ucColorDefined = ucCmd_p;
   sBlkColor.ucOption = 0;
   sBlkColor.usBlue = 0;
   sBlkColor.usGreen = 0;
   sBlkColor.usRed = 0;

   iRet = STOP;
   switch( ucChannel_p )
   {
	   case 0: /* IUP250 */
		   if( iLIBUCM_Display_Backlight_Color_Exist( UCMC_DISPLAY ) > 0 )
		   {
			   iRet = iLIBUCM_Display_Backlight_Color( UCMC_DISPLAY, &sBlkColor );
		   }
	   break;

	   case 1:/* IUR250 */
		   if( iLIBUCM_Icc_Backlight_Color_Exist( UCMC_ICC ) > 0 )
		   {
			   iRet = iLIBUCM_Icc_Backlight_Color( UCMC_ICC, &sBlkColor );
		   }
   	   break;

   }


   return( iRet );
}

//===========================================================================
//! \brief This function reads swipe track
//===========================================================================
int iUnattendedRead_Iso123( void )
{
int iRet, i, j;
T_UCMC_ICC_TRACKMULTI sIcc;
char cTemp[ 1024 ] ;
 char cTemp2[200];
T_UCM_DEVICE sDevice ;
unsigned char ucCardInside;
   unsigned char ucISO1, ucISO2, ucISO3;

   ucISO1 = 0;
   ucISO2 = 0;
   ucISO3 = 0;
    sIcc.ucTypeTrack = 0;
   iRet = PAY_OK;

    if( iLIBUCM_Icc_Exist( UCMC_ISO1 ) > 0 )
    {
        sIcc.ucTypeTrack |= 1;
    }

    if( iLIBUCM_Icc_Exist( UCMC_ISO2 ) > 0 )
    {
        sIcc.ucTypeTrack |= 2;
    }

    if( iLIBUCM_Icc_Exist( UCMC_ISO3 ) > 0 )
    {
        sIcc.ucTypeTrack |= 4;
    }

    /* Si ISO */
    if( sIcc.ucTypeTrack != 0 )
    {
        sDevice.ucType = UCMC_ICC;
         j = iLIBUCM_Device_Config( UCM_DEVICE_ICC0, &sDevice ) ;

        i = iLIBUCM_Icc_Status( UCMC_ICC, &ucCardInside ) ;

        /* Waiting  card */
        if( ( sDevice.u.sIcc.ucICC_Mixte & UCMC_ICC_RETRY_SWIPE ) && (ucCardInside == 0) )
        {
            /* Ask retrieved card */
            ucCardInside = ucWaiting_CardInsert ( 500 );
        }

      iLIBUCM_Display_No_Wait(UCMC_DISPLAY, "RETREIVED CARD\nSWIPE READING", 0);

      sIcc.usTimeout = 15; /* seconde */
        j =  iLIBUCM_Icc_Read_SwipeMulti( UCMC_ICC, 0, &sIcc );

      if( j == 0 )
      {
           if( sIcc.ucTypeTrack & 1 )
           {
               if (sIcc.iResultStatus1 == UCMHOST_TRACK_OK)
               {
                  ucISO1 = '1';
               }

                  memcpy(cTemp2, &sIcc.sTrack1[0], sIcc.ucResultLg_ref1);
                   cTemp2[sIcc.ucResultLg_ref1] = 0;
                  sprintf(cTemp, "Track1=%d L=%d\n%10s", sIcc.iResultStatus1, sIcc.ucResultLg_ref1, cTemp2);
                  iLIBUCM_Display_No_Wait(UCMC_DISPLAY, cTemp, 0);
                  iLIBUCM_Print_Message(UCMC_PRINT, cTemp);
                  ttestall(0, 200);
           }

           if( sIcc.ucTypeTrack & 2 )
           {
            if (sIcc.iResultStatus2 == UCMHOST_TRACK_OK)
               ucISO2 = '2';

               memcpy(cTemp2, &sIcc.sTrack2[0], sIcc.ucResultLg_ref2);
               cTemp2[sIcc.ucResultLg_ref2] = 0;

               sprintf(cTemp, "Track2=%d L=%d\n%10s", sIcc.iResultStatus2, sIcc.ucResultLg_ref2, cTemp2);
               iLIBUCM_Display_No_Wait(UCMC_DISPLAY, cTemp, 0);
               iLIBUCM_Print_Message(UCMC_PRINT, cTemp);
               ttestall(0, 200);
           }

           if( sIcc.ucTypeTrack & 4 )
           {
            if (sIcc.iResultStatus3 == UCMHOST_TRACK_OK)
               ucISO3 = '3';

               memcpy(cTemp2, &sIcc.sTrack3[0], sIcc.ucResultLg_ref3);
               cTemp2[sIcc.ucResultLg_ref3] = 0;

               sprintf(cTemp, "Track3=%d L=%d\n%10s", sIcc.iResultStatus3, sIcc.ucResultLg_ref3, cTemp2);
               iLIBUCM_Display_No_Wait(UCMC_DISPLAY, cTemp, 0);
               iLIBUCM_Print_Message(UCMC_PRINT, cTemp);
               ttestall(0, 200);
           }
      }

      if ((ucISO1 != 0) || (ucISO2 != 0) || (ucISO3 != 0))
      {
         if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
         {
            iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_GREEN);
            iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_GREEN);
         }
         sprintf(cTemp, "Track OK\nISO %c%c%c", ucISO1, ucISO2, ucISO3);
         iLIBUCM_Display_Message(UCMC_DISPLAY, cTemp, 200);
    }
    else
    {
         if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
         {
            iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_RED);
            iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_RED);
         }
         sprintf(cTemp, "Track KO\n%d",j);
         iRet = PAY_KO;

      iLIBUCM_Display_Message(UCMC_DISPLAY, cTemp, 200);
   }
	}
   else
   {
        sprintf( cTemp, "No swipe ISO123\nconfigured" ) ;
        iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 200 );
      iRet = PAY_KO;
    }

return(iRet);
}

int iGraphic_message( char *pMessage_p, int iTo_p )
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

    iLIBUCM_Display_Graphic_Stop(giDisplay);

    if( iTo_p != 0 )
        ttestall( 0, iTo_p );

    return (FCT_OK);
}

/***********************************************/
/*  iPwr = 0 1:light 2:Deep (restart with card insertion )  */
/* iDaily_p   = seconde starting sleep                            */
/* Deep Sleep for IUP250 and IUC180                           */
/* Light and Deep Sleep for UCR                                   */
/***********************************************/
int iSetSleepPowerManagement (int iPwr_p, int iDaily_p)
{
   T_UCM_IAC_DEVICE_CMD_POWER_MNG tPower, tPower2;
   int iRet, iRet2, iLg ;
   char cTemp[400];

   tPower.iStandByType = 0;
   tPower.iDelay = 0 ;
   tPower.iWakeup = 0 ;
   tPower.iRuf = 0;
   iLg = sizeof(T_UCM_IAC_DEVICE_CMD_POWER_MNG);

   /* GET */
   iRet = iLIBUCM_Device_Cmd( UCMDEVICE_CMD_GET_POWER_MNG, &tPower, &iLg, &iRet2 ) ;

   sprintf ( cTemp,  "iSetPowerSet=\n%d iLg=%d iRet=%d StdType=%d iDelay=%d iWakeup=%d iRuf=%d",
      iRet, iLg, iRet2, tPower.iStandByType, tPower.iDelay, tPower.iWakeup, tPower.iRuf) ;
   trace( 0x6E01, strlen( cTemp), cTemp ) ;

   sprintf ( cTemp,  "GET_POWER_MNG=\n%d iLg=%d iRet=%d",iRet, iLg, iRet2) ;
   iLIBUCM_Display_Option( UCMC_DISPLAY, cTemp,
   UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_CLOSE_AT_END | UCMDISPLAY_CENTER, 200 ) ;

   /* SET */
   tPower2.iStandByType = iPwr_p;
   tPower2.iDelay = iDaily_p ;
   tPower2.iWakeup = tPower.iWakeup ; /* mettre meme valeur que celle recue */
   tPower2.iRuf = tPower.iRuf;
   iLg = sizeof(T_UCM_IAC_DEVICE_CMD_POWER_MNG);

   iRet = iLIBUCM_Device_Cmd( UCMDEVICE_CMD_SET_POWER_MNG, &tPower2, &iLg, &iRet2 ) ;

   sprintf ( cTemp,  "iSetPowerSet= %d iLg=%d iRet=%d, StdType=%d iDelay=%d iWakeup=%d iRuf=%d",
      iRet, iLg, iRet2, tPower2.iStandByType, tPower2.iDelay, tPower2.iWakeup, tPower2.iRuf) ;
   trace( 0x6E01, strlen( cTemp), cTemp ) ;

	return (iRet);
}

/***********************************************/
/*  Sample to get ATR after poweron                             */
/*                                                                               */
/***********************************************/
int iTestAtr( void )
{
HISTORIC Histo ;
UCMC_ATR sAtr;
int iRet;

   iRet = STOP;

   if( ucWaiting_CardInsert( 800 ) == UCMC_STATUS_CARD_INSIDE)
   {
      iLIBUCM_Display_Message( UCMC_DISPLAY, "OPEN", 100 ) ;

      Histo.length = 0;
      iRet = iLIBUCM_Icc_Open( UCMC_ICC, "rw" ) ;

      /* HISTORIC BYTE */
      iRet = iLIBUCM_Icc_PowerOn(UCMC_ICC , UCMCICC_EMV_POWER_ON, &Histo ) ;
      trace( 0x6E01, Histo.length, &Histo.historic[0] ) ;

      /* ATR = PROTOCL BYTE + HISTORIC BYTE */
      iRet = iLIBUCM_Icc_PowerOn(UCMC_ICC , UCMCICC_POWER_ATR, (HISTORIC*) &sAtr ) ;
      trace( 0x6E01, sAtr.length, &sAtr.atr[0] ) ;

      iRet = iLIBUCM_Icc_PowerDown(UCMC_ICC ,  UCMCICC_POWER_DOWN) ;
      iRet = iLIBUCM_Icc_Close( UCMC_ICC ) ;
   }
   
return (FCT_OK);
}


/***********************************************/
/*  Sample to get CAM or SAM handle                            */
/*                                                                               */
/***********************************************/
int iTestSamHandle( void )
{
int iRet;
T_UCMC_IAC_ICC_CMD sIcc;

   iRet = iLIBUCM_Icc_Open( UCMC_ICC, "rw" ) ; /* or UCMC_SAMx or UCM_ICCx */

   if( iRet == FCT_OK )
   {
      sIcc.ucChannel = UCMC_ICC;  /* or UCMC_SAMx or UCM_ICCx */
      sIcc.ctOpen[0] = 0;
      sIcc.usOption = 0;
      sIcc.usCmd = UCMCICC_CMD_GET_HANDLE;
      sIcc.u.pFHandle = NULL;                /* HANDLE */
      iRet = iLIBUCM_Icc_Cmd( &sIcc ) ;

      iRet = iLIBUCM_Icc_Close( UCMC_ICC ) ; /* or UCMC_SAMx or UCM_ICCx */
   }

return (FCT_OK);
}

/*&BEGIN FT/09/4316/MA  Multi EMV Application*/
//===========================================================================
//! \brief This function displays the idle message. It is called on manager
//! entry point IDLE_MESSAGE.
//! \param[in] no : application number.
//! \param[in] null1 : data received from manager. (not used).
//! \param[out] null2 : data sent to manager. (not used).
//===========================================================================
static void cu_idle_message(NO_SEGMENT no , void *null1 ,void*null2)
{
	unsigned char *pc_l_line;
	int lg_code;
   char cTemp[100];

	sprintf( cTemp, "cu_idle_message start");
	trace( 0x6E01, strlen(cTemp), cTemp);

	// memclr(mess_on_display, 33);

	// Header activation
	// ??MF InitContexteGraphique(PERIPH_DISPLAY);
	//StateHeader (1);
	SetPatchAppli(_PERIPH_LEDS,_PERIPH_ON);

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// Get the manager language
	lg_code = PSQ_Give_Language();

	pc_l_line = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_INSERT_CARD, lg_code);

	CUTERMdisplayLine(0, pc_l_line, LEFT, (char *)"w");
}


//===========================================================================
//! \brief This function is used to perform periodic treatments. It is called
//! each minute, on manager entry point TIME_FUNCTION. The code to be executed
//! periodically will be called on manager entry point IS_TIME_FUNCTION.
//! \param[in] no : application number.
//! \param[in] null1 : data received from manager. (not used).
//! \param[out] null2 : data sent to manager. (not used).
//===========================================================================
static void cu_time_function(NO_SEGMENT no, void *null1 ,void*null2)
{
	TLV_TREE_NODE hOutputTree;

   char cTemp[100];

	sprintf( cTemp, "cu_time_function start");
	trace( 0x6E01, strlen(cTemp), cTemp);

	hOutputTree = TlvTree_New(0);

	if(hOutputTree != NULL)
	{
		EMVCUST_Periodic_Call_TLVTree(&hOutputTree);

		// release local TLV tree
		TlvTree_ReleaseEx(&hOutputTree);

	}

}

//===========================================================================
//! \brief This function builds a _DEL_ containing the list of the AID managed
//! by the application.
//! \param[in] AppliNum : application number.
//! \param[in] param_in : data received from manager. (not used).
//! \param[out] _delout : _DEL_ containing the list of AID managed by the application.
//===========================================================================
static void cu_give_aid(NO_SEGMENT AppliNum, S_TRANSIN *param_in,   _DEL_ *_delout)
{
	DataElement	eltExt;
	DataElement Elt;
	unsigned char ucDispList;
	unsigned short cr;
	TLV_TREE_NODE hInputTreeSG;
	TLV_TREE_NODE hInputTree, hOutputTree, hTree;


	hInputTreeSG = TlvTree_New(0);

	if(hInputTreeSG != NULL)
	{
		// Reset the selected mark list
		PAR_ResetMarkList();

		// Select Main ICS + ICSx (Maybe unused)
		CUPAR_SelectAdditionnalICS();

		cr = PAR_ReadParameter(TAG_USE_PSE, (DataElementExt *)&eltExt);
		if (cr)
		{
			TlvTree_AddChild(hInputTreeSG, eltExt.tag, eltExt.ptValue, eltExt.length);
		}
		cr = PAR_ReadParameter(TAG_WAIT_AFTER_ATR, (DataElementExt *)&eltExt);
		if (cr)
		{
			TlvTree_AddChild(hInputTreeSG, eltExt.tag, eltExt.ptValue, eltExt.length);
		}
		cr = PAR_ReadParameter(TAG_COMPATIBILITY_2000, (DataElementExt *)&eltExt);
		if (cr)
		{
			TlvTree_AddChild(hInputTreeSG, eltExt.tag, eltExt.ptValue, eltExt.length);
		}
		cr = PAR_ReadParameter(TAG_WAIT_AFTER_ATR, (DataElementExt *)&eltExt);
		if (cr)
		{
			TlvTree_AddChild(hInputTreeSG, eltExt.tag, eltExt.ptValue, eltExt.length);
		}

		Engine_SetGlobalParameters(hInputTreeSG);

		// release local TLV tree
		TlvTree_ReleaseEx(&hInputTreeSG);

	}

	hOutputTree = TlvTree_New(0);

	if(hOutputTree != NULL)
	{
		EMVCUST_Get_AID_TlvTree(&hOutputTree);

		// Build an input TLV Tree
		hInputTree = TlvTree_New(0);

		if(hInputTree != NULL)
		{
			TlvTree_AddChild(hInputTree, TAG_TERM_APP_NUMBER, (unsigned char*) &AppliNum, 1);

			hTree = TlvTree_GetFirstChild(hOutputTree);

			ucDispList = FALSE;

			while(hTree != NULL)
			{
				Elt.tag = TlvTree_GetTag(hTree);
				Elt.length = TlvTree_GetLength(hTree);
				Elt.ptValue = TlvTree_GetData(hTree);



				if (Elt.tag == TAG_GIVE_AID_NB_AID)
				{
					TlvTree_AddChild(hInputTree, TAG_GIVE_AID_NB_AID, Elt.ptValue, 1);
				}


				else if (Elt.tag ==TAG_GIVE_AID_MANUAL_SELECTION)
				{
					ucDispList = Elt.ptValue [0];
				}

				else if (Elt.tag == TAG_GIVE_AID_AID_VALUE)
				{
					TlvTree_AddChild(hInputTree, Elt.tag, Elt.ptValue, Elt.length);

					// Get the next node
					hTree = TlvTree_GetNext(hTree);
					Elt.tag = TlvTree_GetTag(hTree);
					Elt.length = TlvTree_GetLength(hTree);
					Elt.ptValue = TlvTree_GetData(hTree);

					if (Elt.tag == TAG_GIVE_AID_ASI)
					{
						TlvTree_AddChild(hInputTree, Elt.tag, Elt.ptValue, Elt.length);
					}

					TlvTree_AddChild(hInputTree, TAG_GIVE_AID_MANUAL_SELECTION, (unsigned char*) &ucDispList, 1);
				}

				// Get the next node
				hTree = TlvTree_GetNext(hTree);
			}

			// Copy the input TLV tree to output _DEL_ object
			AddTlvTreeToDelValue(_delout, hInputTree);

			// release local TLV tree
			TlvTree_ReleaseEx(&hInputTree);
		}

		// release local TLV tree
		TlvTree_ReleaseEx(&hOutputTree);
	}
}

//===========================================================================
//! \brief This function tests if the EMV transaction can be run.
//! \param[in] AppliNum : application number.
//! \param[in] pParamIn : data received from manager. (not used).
//! \param[out] pParamOut : structure containing the response : 
//! - if the field cardappnumber is != from 0 then custom application wants to 
//! process the EMV card. In this case, the fields cardapp.priority and cardapp.cardappname
//! have to be fulfilled.
//! - if the field cardappnumber = 0 then custom application doesn't wants to process the EMV card.
//===========================================================================
static void cu_is_card_emv_for_you(NO_SEGMENT AppliNum, const S_AID* pParamIn, S_CARDOUT* pParamOut)
{
	(void)pParamIn;


	// Initialise the output parameter
   memset(&pParamOut->returned_state[pParamOut->response_number], 0, sizeof(pParamOut->returned_state[pParamOut->response_number]));

	// Get the application name
	strcpy(pParamOut->returned_state[pParamOut->response_number].appname, g_szAppName);

	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].cardappnumber = 1;
	// Set the application name and the priority
	pParamOut->returned_state[pParamOut->response_number].cardapp[0].priority = 30;

	strcpy (pParamOut->returned_state[pParamOut->response_number].cardapp [0].cardappname, g_szAppName);

	pParamOut->response_number++;
}

//===========================================================================
//! \brief This function allows the user to execute custom menu functions.
//! \param[in] AppliNum : application number.
//! \param[in] null1 : data received from manager. (not used).
//! \param[out] null2 : data sent to manager. (not used).
//===========================================================================
#ifndef _USE_UCM_
static void cu_more_function(NO_SEGMENT AppliNum, void *null1 ,void*null2)
{
	TLV_TREE_NODE hOutputTree;
	int bStateHeader;

	bStateHeader = StateHeader(0);

	hOutputTree = TlvTree_New(0);

	if(hOutputTree != NULL)
	{
		EMVCUST_More_Function_TLVTree(&hOutputTree);

		// release local TLV tree
		TlvTree_ReleaseEx(&hOutputTree);
	}

	StateHeader(bStateHeader);
}
#endif

//===========================================================================
//! \brief This function allow custom application to capture the key pressed.
//! It is called at each key pressed when manager is idle.
//! \param[in] no : application number.
//! \param[in] key1 : data received from manager. (not used).
//! \param[out] key2 : data sent to manager. (not used).
//===========================================================================
static void cu_keyboard_event(NO_SEGMENT no, S_KEY *key1, S_KEY *key2)
{
	unsigned char OutKey;

	OutKey = (unsigned char)(key1->keycode);
	EMVCUST_KeyManagement_TLVTree(key1->keycode, &OutKey);
	key2->keycode = OutKey;
}

//===========================================================================
//! \brief This function allows custom application to perform a service call
//! to engine application.
//! \param[in] function : engine function number.
//! \param[in] aDEL : input DEL to be transmitted to engine.
//! \param[out] ret_code : service call return code.
//===========================================================================
DEL *ENGINE_ServiceCall( int function,const DEL *aDEL, int* ret_code)
{
	unsigned char priority;

	*ret_code = PAY_KO;
	if (ServiceGet(I_EMVENG_Type_Appli,function,&priority)==0)
	{
		if (aDEL != NULL)
			CopyEntree((DEL *)aDEL,&_DELLocale.DEL);
      else
         _DEL_init(&_DELLocale.DEL);
		_DELLocale.type_code = I_EMVENG_Type_Appli;
		_DELLocale.service   = function;
		_DELLocale.function = function;
		USR_ServiceCall(I_EMVENG_Type_Appli,function,sizeof(_DELLocale),&_DELLocale,ret_code);
		CopySortie(&_DELLocale.DEL,&DELLocale);
		return(&DELLocale);
	}
	else
		return(NULL);
}

/*********************/
/* Cherche dans le parametrage UCMC si le protocole est géré par le HOTE du composant UCM */
/* ou non si pas de hote le nom est ucmxZxx.pas           */
/*********************/
int iIsProtocolUCMC(void)
{
   int iRet;
   T_UCM_DEVICE sDevice;
   iLIBUCM_Device_Config_OPE(UCM_DEVICE_HOST, &sDevice);
   if ((sDevice.ucType == 1) && (sDevice.ucPilote == 0))
   {
      iRet = 0; /* protocol not managed by UCMC */
   }
   else
   {
      iRet = 1;
   }
   return (iRet);
}
//===========================================================================
//! \brief This function performs a debit transaction on an EMV chip card.
//! \param[in] AppliNum : application number.
//! \param[in] param_in : DEL from manager. This DEL contains mandatory parameters 
//! selected AID, application label. And may contain optionally parameters 
//! application preferred name, language preference, issuer code table index,
//! application priority indicator.
//! \param[out] param_out : structure containing the payment return code :
//! - PAY_OK : if the payment successfully performed.
//! - PAY_KO : otherwise.
//===========================================================================
void cu_debit_emv(NO_SEGMENT AppliNum, S_TRANSIN *param_in,   S_TRANSOUT *param_out)
{
	DataElement	AnElt;
	unsigned char EngAppliSel;
	unsigned char TabAmount [4];
	unsigned char TypeAppli[2];
#ifdef _USE_UCM_
	T_UCMHOST_DEBIT sDebit;
	T_UCMHOST_R_DEBIT sRDeb;
#endif
	TLV_TREE_NODE hInputTree, hTree;
	TLV_TREE_NODE hOutputTree; 
	int iret, i;
	char cPinBooster;
	char * pt_PinPeriph;
	int nNbSecurePartsConfig = -1;
	T_SEC_CONFIG tabConfParts[10];
	int bFound;
	int bStateHeader;
#ifdef _USE_UCM_
   char cTemp[ 200 ];
    int j;
#endif

	bStateHeader = StateHeader(0);
    i = 0;
	cPinBooster = 0;
	pt_PinPeriph=NULL;
#ifdef _USE_UCM_
    if (!UCM_Present)
    {
#endif

	if (param_in->peri != 0)
	{
		// If CAM0 is not used, specify that CARD and PIN are on the terminal (CAM2 management)
		iret = SEC_GetConfig (&nNbSecurePartsConfig, tabConfParts);
		if (iret == OK)
		{
			bFound = FALSE;
			for (i=0; i < nNbSecurePartsConfig; i++)
			{
				if (tabConfParts[i].SecureType == C_SEC_CIPHERING)
				{
					pt_PinPeriph = tabConfParts [i].ptszBoosterPeripheral;
					cPinBooster = tabConfParts [i].cBoosterType;
					bFound = TRUE;
					break;
				}
			}
			if (bFound)
			{
				bFound = FALSE;
				for (i=0; i < nNbSecurePartsConfig; i++)
				{
					if (tabConfParts[i].SecureType == C_SEC_CARD)
					{
						tabConfParts [i].ptszBoosterPeripheral = pt_PinPeriph;
						tabConfParts [i].cBoosterType = cPinBooster;
						bFound = TRUE;
						break; /* to go out the for loop */
					}
				}

				if (bFound)
					iret = SEC_SetConfig (nNbSecurePartsConfig, tabConfParts);
			}
		}
	}
#ifdef _USE_UCM_
	}
#endif

	memset(param_out, 0, sizeof(*param_out));
	param_out->noappli = AppliNum;

	CreateTlvTreeFromDel(&hInputTree, (_DEL_ *)&param_in->del);

	hTree = TlvTree_GetFirstChild(hInputTree);

	while (hTree != NULL)
	{
		AnElt.tag = TlvTree_GetTag(hTree);

		if (AnElt.tag == TAG_GIVE_AID_AID_VALUE)
		{
			TlvTree_SetTag(hTree, TAG_AID_ICC);
		}
		else if (AnElt.tag == TAG_GIVE_AID_APP_NAME)
		{
			TlvTree_SetTag(hTree, TAG_APPLICATION_LABEL);
		}
		else if (AnElt.tag == TAG_GIVE_AID_APP_PRIO)
		{
			TlvTree_SetTag(hTree, TAG_APPLI_PRIOR_IND);
		}
		else if (AnElt.tag == TAG_GIVE_AID_PREF_LANGUAGE)
		{
			TlvTree_SetTag(hTree, TAG_LANGUAGE_PREFERENCE);
		}

		// Get the next node
		hTree = TlvTree_GetNext(hTree);
	}

	ShortToChar(CustApplicationNumber,TypeAppli);

	TlvTree_AddChild(hInputTree, TAG_ENG_CUSTOM_APPLI_TYPE, (unsigned char*) &TypeAppli, 2);

	EngAppliSel =1;
	TlvTree_AddChild(hInputTree, TAG_ENG_APPLI_SEL_ALREADY_DONE, (unsigned char*) & EngAppliSel, 1);

	TlvTree_AddChild(hInputTree, TAG_TRANSACTION_CURRENCY_CODE, (unsigned char*) &param_in->currency.code, 2);

	TlvTree_AddChild(hInputTree, TAG_TRANSACTION_CURRENCY_EXP, (unsigned char*) &param_in->currency.posdec, 1);

      LongToChar (param_in->amount, TabAmount);

#ifdef _USE_UCM_
	if(UCM_Present)
	{
         if (iIsProtocolUCMC() == 0)
         {
            /* change amount */
            LongToChar (gulPaymentAmount, TabAmount);
         }
      }
#endif
   TlvTree_AddChild(hInputTree, TAG_AMOUNT_AUTH_BIN, (unsigned char *) TabAmount, 4);


	LongToChar (0, TabAmount);
	TlvTree_AddChild(hInputTree, TAG_AMOUNT_OTHER_BIN, TabAmount, 4);

	hOutputTree = NULL;
	

#ifdef _USE_UCM_
	if(UCM_Present)
	{
		memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
		memset ( &sDebit, 0x00, sizeof ( T_UCMHOST_DEBIT ) ) ;

		sDebit.ucFunction = DEBIT_EMV;
      if (iIsProtocolUCMC() != 0)
      {
		switch(iLIBUCM_Pay_Ready_For_Debit(sizeof(T_UCMHOST_DEBIT), &sDebit))
		{
		case UCMCPAY_SOLV:
         if( ( giDisplayType == PARAM_TYPE_IUC180 ) || ( giDisplayType == PARAM_TYPE_IUP250 ) )
         {
            iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_BLUE);
            iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_BLUE);
         }
         i = Engine_DoTransaction(hInputTree,&hOutputTree);
			switch(i)
			{
			case ERR_ENG_OK:
				param_out->rc_payment = PAY_OK;

				// TODO: Set the correct status (UCMHOST_CR_REFUSED, UCMHOST_CR_CARDFORBIDEN, ...)
				sRDeb.ucCr = UCMHOST_CR_OK;

            /* UCM */
             iGraphic_message( "DEBIT EMV\nOK", 200 );
            //iLIBUCM_Display_Message(UCMC_DISPLAY, "SAMPLE SDK\nOK", 200);
            sRDeb.ucDiag = 0;
            /****/
				break;
			case ERR_ENG_TRY_ANOTHER_AID:
				param_out->rc_payment = PAY_OTHER_AID;
				sRDeb.ucCr = UCMHOST_CR_APPLI_ASK_NEW_SELECTION;
           
            iLIBUCM_Display_Message(UCMC_DISPLAY, "SAMPLE SDK\nOther AID", 200);
				break;
			default:
				param_out->rc_payment = PAY_KO;
				sRDeb.ucCr = UCMHOST_CR_CARDINVALIDE;
            
            /* UCM */
            sRDeb.ucDiag = 5; /* SES 1042 CARD non TRAITEE */
            sprintf( cTemp, "SAMPLE SDK\nKO %d", i );
            iLIBUCM_Display_Message(UCMC_DISPLAY, cTemp, 200);

            /****/

				break;
			}

			sRDeb.usAppName    = AppliNum ;
			strcpy ( sRDeb.tAppLibelle, g_szAppName ) ;

			sRDeb.ulAmount = sDebit.ulAmount;
			memcpy( &sRDeb.tCurrency, &sDebit.tCurrency, sizeof( S_MONEY));

			sRDeb.ucPrinter = 0;
			sRDeb.ucDisplay = 0;

			sRDeb.ucMode = sDebit.ucTrsMode;
			sRDeb.ucTypeCardStruct = UCMHOST_CARD_EMV;
			sRDeb.ucSupport = param_in->support;

			sRDeb.ucCardHolderLanguage = 0xFF;

			read_date( &sRDeb.u.sCard.uAppli.sApp.sLocalDate ) ;

			sRDeb.u.sCard.uAppli.sApp.ucTypeTrs[ 0 ] = 'T';
			sRDeb.u.sCard.uAppli.sApp.ucTypeTrs[ 1 ] = 'T'; /* UCM */

			memset( sRDeb.u.sCard.uAppli.sApp.OwnerNumber, '1', sizeof(NO_PORTEUR) );

                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[0] = 'J';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[1] = 'J';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[2] = 'M';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[3] = 'M';
                 	memset( &sRDeb.u.sCard.uAppli.sApp.ucEndVal2[0], 0, 6 );

			memset( sRDeb.u.sCard.uAppli.sApp.ucServiceCode, 'S', 3 );
			sRDeb.u.sCard.uAppli.sApp.iTrsNumber = 1234;
			sRDeb.u.sCard.uAppli.sApp.iRemisNumber = 5678;
			sRDeb.u.sCard.uAppli.sApp.ulAmountCV = 9999;
			memset( &sRDeb.u.sCard.uAppli.sApp.sCurrencyCV, 'V', sizeof(T_NOM_MONEY) ); /* UCM */      
                       sRDeb.u.sCard.uAppli.sApp.sCurrencyCV.posdec = 2; /* UCM */
         
			sRDeb.u.sCard.uAppli.sApp.ulAmountEstimat = 7777;

			memset( &sRDeb.u.sCard.uAppli.sApp.ucAutoNumber[0], 'A', 6 );
			sRDeb.u.sCard.uAppli.sApp.ucForcingCode = 'F';

			memset( &sRDeb.u.sCard.uAppli.sApp.ucEndVal2[0], 0, 6 );
			memset( &sRDeb.u.sCard.uAppli.sApp.ucRuf1[0], 0, 4 );

			sRDeb.u.sCard.uAppli.sApp.ucReaderMode = 'C';

			sRDeb.u.sCard.uAppli.sApp.usTASA = 9;

                 	memset( &sRDeb.u.sCard.uCard.sEMV.ucCrypto[0], 'C', 16 ) ;

                    for( i = 0; i < Taille_LABEL; i++ )
                    {
                       sRDeb.u.sCard.uCard.sEMV.LabelAID[ i ] = 'A' + i ;

                    }
                 	sRDeb.u.sCard.uCard.sEMV.AID.aid_length = Taille_LABEL ;
                    sRDeb.u.sCard.uCard.sEMV.AID.aid[0] = 0xA0 ;
                    
                    j = 1;
                    for( i = 1; i < Taille_LABEL; i++ )
                    {
                       sRDeb.u.sCard.uCard.sEMV.AID.aid[i] = j*0x10 + ( j + 1 ) ;
                       j+=2;
                    }

			// T_UCMHOST_CARD_ACCEPT
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoContrat, 'C', 7 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoSA, 'S', 3 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoSiret, 'R', 14 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypeActivite, 'C', 4 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypeSite, 'S', 8 ) ;   /* UCM */
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypePaiement, 'P', 2 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucEnseigne, 'E', 60 );
			sRDeb.u.sCard.uAccept.sAcpt.ucEnseigne[ 60 ] = 0 ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucEnteteTicket, 'T', 50 );
			sRDeb.u.sCard.uAccept.sAcpt.ucEnteteTicket[ 50 ] = 0 ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucPiedTicket, 'P', 50 );
			sRDeb.u.sCard.uAccept.sAcpt.ucPiedTicket[ 50 ] = 0 ;
         		memset( sRDeb.u.sCard.uAccept.sAcpt.ucCrVerifAcc, 'V', 2 );

			iLIBUCM_Pay_Result_Debit(sizeof(T_UCMHOST_R_DEBIT), &sRDeb);
			iLIBUCM_Pay_End(0, NULL);

         if( ( giDisplayType == PARAM_TYPE_IUC180 ) || ( giDisplayType == PARAM_TYPE_IUP250 ) )
         {
   			iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_GREEN);
	   		iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_WHITE);
         }
			break;

		case UCMCPAY_RECORD:
			// TODO: Store the transaction here !
         if( ( giDisplayType == PARAM_TYPE_IUC180 ) || ( giDisplayType == PARAM_TYPE_IUP250 ) )
         {
   			iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_MAGENTA);
	   		iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_MAGENTA);
         }
         
        		iLIBUCM_Display_Message ( UCMC_DISPLAY, "RECORD EMV\nIN PROGRESS...", 100 ) ;

			param_out->rc_payment = PAY_OK;
			sRDeb.ucCr = UCMHOST_CR_OK;

			sRDeb.usAppName    = AppliNum ;
			strcpy ( sRDeb.tAppLibelle, g_szAppName ) ;

			sRDeb.ulAmount = sDebit.ulAmount;
			memcpy( &sRDeb.tCurrency, &sDebit.tCurrency, sizeof( S_MONEY));

			sRDeb.ucPrinter = 0;
			sRDeb.ucDisplay = 0;

			sRDeb.ucMode = sDebit.ucTrsMode;
			sRDeb.ucTypeCardStruct = UCMHOST_CARD_EMV;
			sRDeb.ucSupport = param_in->support;

			sRDeb.ucCardHolderLanguage = 0xFF;

			read_date( &sRDeb.u.sCard.uAppli.sApp.sLocalDate ) ;

			sRDeb.u.sCard.uAppli.sApp.ucTypeTrs[ 0 ] = 'T';
			sRDeb.u.sCard.uAppli.sApp.ucTypeTrs[ 1 ] = 'T'; /* UCM */

			memset( sRDeb.u.sCard.uAppli.sApp.OwnerNumber, '1', sizeof(NO_PORTEUR) );

                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[0] = 'J';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[1] = 'J';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[2] = 'M';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[3] = 'M';
                 	memset( &sRDeb.u.sCard.uAppli.sApp.ucEndVal2[0], 0, 6 );

			memset( sRDeb.u.sCard.uAppli.sApp.ucServiceCode, 'S', 3 );
			sRDeb.u.sCard.uAppli.sApp.iTrsNumber = 1234;
			sRDeb.u.sCard.uAppli.sApp.iRemisNumber = 5678;
			sRDeb.u.sCard.uAppli.sApp.ulAmountCV = 9999;
			memset( &sRDeb.u.sCard.uAppli.sApp.sCurrencyCV, 'V', sizeof(T_NOM_MONEY) ); /* UCM */      
                       sRDeb.u.sCard.uAppli.sApp.sCurrencyCV.posdec = 2; /* UCM */
         
			sRDeb.u.sCard.uAppli.sApp.ulAmountEstimat = 7777;

			memset( &sRDeb.u.sCard.uAppli.sApp.ucAutoNumber[0], 'A', 6 );
			sRDeb.u.sCard.uAppli.sApp.ucForcingCode = 'F';

			memset( &sRDeb.u.sCard.uAppli.sApp.ucEndVal2[0], 0, 6 );
			memset( &sRDeb.u.sCard.uAppli.sApp.ucRuf1[0], 0, 4 );

			sRDeb.u.sCard.uAppli.sApp.ucReaderMode = 'C';

			sRDeb.u.sCard.uAppli.sApp.usTASA = 9;

                 	memset( &sRDeb.u.sCard.uCard.sEMV.ucCrypto[0], 'C', 16 ) ;

                    for( i = 0; i < Taille_LABEL; i++ )
                    {
                       sRDeb.u.sCard.uCard.sEMV.LabelAID[ i ] = 'A' + i ;

                    }
                 	sRDeb.u.sCard.uCard.sEMV.AID.aid_length = Taille_LABEL ;
                    sRDeb.u.sCard.uCard.sEMV.AID.aid[0] = 0xA0 ;
                    
                    j = 1;
                    for( i = 1; i < Taille_LABEL; i++ )
                    {
                       sRDeb.u.sCard.uCard.sEMV.AID.aid[i] = j*0x10 + ( j + 1 ) ;
                       j+=2;
                    }

			// T_UCMHOST_CARD_ACCEPT
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoContrat, 'C', 7 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoSA, 'S', 3 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoSiret, 'R', 14 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypeActivite, 'C', 4 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypeSite, 'S', 8 ) ;   /* UCM */
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypePaiement, 'P', 2 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucEnseigne, 'E', 60 );
			sRDeb.u.sCard.uAccept.sAcpt.ucEnseigne[ 60 ] = 0 ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucEnteteTicket, 'T', 50 );
			sRDeb.u.sCard.uAccept.sAcpt.ucEnteteTicket[ 50 ] = 0 ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucPiedTicket, 'P', 50 );
			sRDeb.u.sCard.uAccept.sAcpt.ucPiedTicket[ 50 ] = 0 ;
         		memset( sRDeb.u.sCard.uAccept.sAcpt.ucCrVerifAcc, 'V', 2 );
	
			iLIBUCM_Pay_Result_Debit(sizeof(T_UCMHOST_R_DEBIT), &sRDeb);
			iLIBUCM_Pay_End(0, NULL);

         if( ( giDisplayType== PARAM_TYPE_IUC180 ) || ( giDisplayType == PARAM_TYPE_IUP250 ) )
         {
   			iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_GREEN);
   			iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_WHITE);
         }
			break;

      case UCMCPAY_ASK_EPURSE_BALANCE: /* UCM vending kinematic */
		default:
			param_out->rc_payment = PAY_KO;
			break;
		}
	}
	else
	{
         if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
         {
            iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_CYAN); /* IUR250 */
            iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_CYAN); /* IUP250 */
         }
         iLIBUCM_Display_Message(UCMC_DISPLAY, "PAYMENT EMV\nIN PROGRESS...", 70);
         i = Engine_DoTransaction(hInputTree, &hOutputTree);
         switch (i)
         {
            case ERR_ENG_OK:
               iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_GREEN); /* IUR250 */
               iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_GREEN); /* IUP250 */
               param_out->rc_payment = PAY_OK;
               iGraphic_message("DEBIT EMV\nOK", 200);
               break;
            case ERR_ENG_TRY_ANOTHER_AID:
               param_out->rc_payment = PAY_OTHER_AID;
               iLIBUCM_Display_Message(UCMC_DISPLAY, "SAMPLE SDK\nOther AID", 200);
               break;
            default:
               iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_RED); /* IUR250 */
               iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_RED); /* IUP250 */
               param_out->rc_payment = PAY_KO;
               sprintf(cTemp, "DEBIT EMV\nKO %d", i);
               iLIBUCM_Display_Message(UCMC_DISPLAY, cTemp, 200);
               break;
         }
         if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
         {
            iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_GREEN); /* IUR250 */
            iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_WHITE); /* IUP250 */
         }
      }
   }
   else
   {
#endif


		switch(Engine_DoTransaction(hInputTree,&hOutputTree))
		{
		case ERR_ENG_OK:
			param_out->rc_payment = PAY_OK;
			break;
		case ERR_ENG_TRY_ANOTHER_AID:
			param_out->rc_payment = PAY_OTHER_AID;
			break;
		default:
			param_out->rc_payment = PAY_KO;
			break;
		}
#ifdef _USE_UCM_
	}
#endif

#ifdef _USE_UCM_
    if (!UCM_Present)
    {
#endif
		SEC_SetConfig (0, 0);
#ifdef _USE_UCM_
	}
#endif

	// release local TLV tree
	TlvTree_ReleaseEx(&hInputTree);
	TlvTree_ReleaseEx(&hOutputTree);

	StateHeader(bStateHeader);
   WaitingRemovedCard();
}
/*&END FT/09/4316/MA  Multi EMV Application*/

//===========================================================================
//! \brief This function treats the engine entry points managed 
//! by the custom application.
//! \param[in] size : size of the exchanged data.
//! \param[in,out] data : input/output structure used for the exchange between 
//! engine and custom.
//! \return 0.
//===========================================================================
int Main_EMVCUST_TlvTree(unsigned int size, I_CUST_TLVTREE_SERVICE *data)
{
	int CR_Tree_Conv = TLV_TREE_OK;
	TLV_TREE_NODE hInputTlvTree;
	TLV_TREE_NODE hOutputTlvTree;
	int function;

	// Deserialization of TLV tree
	CR_Tree_Conv = TlvTree_Unserialize(&hInputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, data->m_Buffer, sizeof(data->m_Buffer));
	if((CR_Tree_Conv == TLV_TREE_OK)) //  || (CR_Tree_Conv == TLV_TREE_ERROR_INVALID_BUFFER))
	{ 
		// Deserialization ok
		// Create the output TlvTree
		hOutputTlvTree=TlvTree_New(0);
		if (hOutputTlvTree != NULL)
		{
			switch(data->m_Header.m_usService)
			{
			case I_EMVCUST_Get_Global_Param_TlvTree :
				CUPAR_UpdateGlobalParam();
				EMVCUST_Get_Global_Param_TlvTree(&hOutputTlvTree);
				break;

			case I_EMVCUST_Get_AID_List_TlvTree :
				EMVCUST_Get_AID_List_TlvTree(&hOutputTlvTree);
				break;

			case I_EMVCUST_Get_AID_DATA_TlvTree :
				EMVCUST_Get_AID_DATA_TlvTree(&hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Get_AID_Param_TlvTree :
				EMVCUST_Get_AID_Param_TlvTree(&hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Process_Step_TlvTree :
				function = data->m_Header.m_nFunction;
				EMVCUST_Process_Step_TlvTree (function, &hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Display_Message_TlvTree :
				EMVCUST_Display_Message_TlvTree(&hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Get_Last_Transaction_TlvTree :
				EMVCUST_Get_Last_Transaction_TlvTree(&hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Voice_Referral_TlvTree :
				EMVCUST_Voice_Referral_TlvTree(&hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Authorization_TlvTree :
				EMVCUST_Authorization_TlvTree (&hOutputTlvTree);
				break;

			case I_EMVCUST_Choose_Language_Menu_TlvTree :
				EMVCUST_Choose_Language_Menu_TlvTree (&hOutputTlvTree);
				break;

			case I_EMVCUST_Menu_Select_TlvTree :
				EMVCUST_Menu_Select_TlvTree (&hInputTlvTree, &hOutputTlvTree);
				break;

			case I_EMVCUST_Choose_Account_Type_Menu_TlvTree :
				EMVCUST_Choose_Account_Type_Menu_TlvTree (&hOutputTlvTree);
				break;

			case I_EMVCUST_Get_AID_ICS_TlvTree :
				EMVCUST_Get_AID_ICS_TlvTree(&hInputTlvTree, &hOutputTlvTree);
				break;

			default:
				break;
			}

			// Debug
			// if (data->m_Header.m_usService == I_EMVCUST_Get_Last_Transaction_TlvTree) // && (function == EMVDC_STOP))
			// if ((data->m_Header.m_usService == I_EMVCUST_Display_Message_TlvTree))  //  || (data->m_Header.m_usService == I_EMVCUST_KeyManagement_TlvTree))
			// TraceTLVTree(data->m_Header.m_usService, &hOutputTlvTree);
			// TraceTLVTreeToDEL(hOutputTlvTree);

			// Serialization of output TLV tree
			CR_Tree_Conv = TlvTree_Serialize(hOutputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, data->m_Buffer, sizeof(data->m_Buffer));
			if(CR_Tree_Conv < TLV_TREE_OK)
			{
				memset(data->m_Buffer, 0, sizeof(data->m_Buffer));
			}

			// Destruction of output TLV tree
		//	a  revoir !!!!!TlvTree_ReleaseEx(&hOutputTlvTree);

		}
		else
		{
			memset(data->m_Buffer, 0, sizeof(data->m_Buffer));
		}

		// Destruction of input TLV tree
		// a revoir !!!!!!TlvTree_ReleaseEx(&hInputTlvTree);
	}
	else
	{
		memset(data->m_Buffer, 0, sizeof(data->m_Buffer));
	}


	TlvTree_ReleaseEx(&hInputTlvTree);

	TlvTree_ReleaseEx(&hOutputTlvTree);


	#ifdef _TLVTREE_DEBUG_
	if ((data->m_Header.m_usService==I_EMVCUST_Process_Step_TlvTree)&&(function==EMVDC_STOP))
		TlvTree_DumpAllocatedTrees();
	#endif 


	return 0;
}
extern int TM_GetSerialNumber(unsigned char *serial);

//===========================================================================
//! \brief This function performs the initialisation of the CUSTOM component.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure containing the field noappli updated with 
//! the application number.
//! \return Always FCT_OK.
//===========================================================================
static int cu_after_reset (NO_SEGMENT noappli, void *param_in, S_TRANSOUT *param_out)
{
	S_TRANSOUT   paramseq;
	FLAG_CHGT  chgt;
	TYPE_CHGT  type;
	DATE       date;
	int        size;
	unsigned char serial_number[8+1];
	int iRet;
	object_info_t info;

#ifdef _USE_SPED_
	int cr_Sped_MSREnable;
	FILE *swipe2;
#endif
	unsigned char Tmp[4];
#ifdef _USE_UCM_
	int bIsUcm;
	object_descriptor_t UcmcDescriptor;
	unsigned char ucPriority;
   T_LIBUCM_DEVICE_STATUS sStatus;
   T_UCM_DEVICE			sDevice ;
   T_UCMC_IAC_EVENT		sEvent;   
#endif
	char cTemp[200];

	// Restore global variables stored in RAM
	FILE_Save_Restore_global_RAM_data ();

	// Messages Initialisation
	CUMESS_Initialise();
	
	/*&BEGIN FT/09/4316/MA  Multi EMV Application*/
	if(ObjectGetInfo(OBJECT_TYPE_APPLI,noappli,&info) ==0)
	{
		CustApplicationNumber = info.application_type;
	}
	else
		CustApplicationNumber = 0xFFFF; /*Get_TypeCode(noappli);*/

	sprintf(g_szAppName, "EMV_%04X", CustApplicationNumber);
	/*&END FT/09/4316/MA  Multi EMV Application*/

#ifdef _USE_UCM_

	UCM_Present = FALSE;
    giModeMainteance = 0;
    gulPaymentAmount = 100;
	iRet = iLIBUCM_Device_Ucm_Status( &sStatus );

	 if( iRet == FCT_OK)
	 {
		if( sStatus.ucUCM == 3 /* Maintenance */ )
		{
                    giModeMainteance = 1;
			/* UCMC_EVENT_TYPE_KEY not available in mainteannce mode */
			 /* adding service LLT buton  and USB event */
			 //sEvent.usType = UCMC_EVENT_TYPE_LLT_BT | UCMC_EVENT_TYPE_USB;
			 sEvent.usType = UCMC_EVENT_TYPE_USB;
		}
		else
		{
			 /* adding service function key and LLT press buton:  Warning: UCMC_EVENT_TYPE_KEY service decrease perfomance */
			 //sEvent.usType = UCMC_EVENT_TYPE_KEY | UCMC_EVENT_TYPUCMC_EVENT_TYPE_LLT_BTE_LLT_BT | UCMC_EVENT_TYPE_USB;
			 sEvent.usType = UCMC_EVENT_TYPE_KEY | UCMC_EVENT_TYPE_USB;
		}

		 sEvent.usRuf1 = 0;
		 sEvent.usRuf2 = 0;
		 sEvent.usRuf3 = 0;
		 iRet = iLIBUCM_Device_Event_Service_Set( &sEvent ) ;
	}
 
        /**************************/
        /* choice back color or display */
        /**************************/
        giDisplay = 0;
        giDisplayBackColor = 0;

        giDisplayType = iLIBUCM_Display_Exist(UCMC_DISPLAY_ICL);
      
        switch( giDisplayType)
        {
            case PARAM_TYPE_IUC180:
            case PARAM_TYPE_IUC150: /* IUC150 special) */
                giDisplay = UCMC_DISPLAY_ICL;
                giDisplayBackColor = UCMC_DISPLAY_ICL;
            break;
            case PARAM_TYPE_TPASS:
                giDisplay = UCMC_DISPLAY_ICL;
            break;
            default:
                giDisplayBackColor = 0 ;
                giDisplayType = iLIBUCM_Display_Exist(UCMC_DISPLAY);

                switch(giDisplayType )         
                {
                    case PARAM_TYPE_IUP250:
                        giDisplay = UCMC_DISPLAY_PPAD;
                        giDisplayBackColor = UCMC_DISPLAY_PPAD;
                    break;
                    case PARAM_TYPE_UPP:
                    case PARAM_TYPE_CAD30VR:
                    case PARAM_TYPE_HOST:
                    default:
                        if( giDisplayType > 0)
                        {
                            giDisplay = UCMC_DISPLAY;
                        }
                    break;
                }

            break;
        }

	/* HOST parameters */
	iLIBUCM_Device_Config_OPE( UCM_DEVICE_HOST, &sDevice );

	/* If host exist and host not defined */
   if ((sDevice.ucType == 1) && (sDevice.ucPilote == 0) && (memcmp(&sDevice.uctNomDriver[0], "0xFFFF", 6) == 0))
	{
		sDevice.ucType = 1 ; /* do not change */
		sDevice.ucMode = 0 ; /* do not change */
		sDevice.ucPilote = 2 ; /* do not change */
		sprintf( (char *)&sDevice.uctNomDriver[0], "%s", "0x006E" ) ;  /* Driver protocole = type of application see ADF file */
		sprintf( (char *)&sDevice.uctNomDll[0], "%s", "HOTE10S" ) ;   /* Dll name: do not change */
		sDevice.ucCom = 0;  /* Port com number: not significatif car COM managed by application in this case */

		memclr ( &sDevice.u.uctData[ 0 ], UCM_MAX_SIZE_DATA_DEVICE );

		iRet = iLIBUCM_Host_Init( &sDevice ) ;

		sprintf( cTemp, "Host Init\n %d", iRet ) ;
		iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 200 ) ; 
	}

	/* event idle message */
        if( sStatus.ucUCM != 3 /* Not in Maintenance mode */ )
        { 
            iLIBUCM_Display_Idle_Event( UCMC_DISPLAY, 1 ); /* 0 =oFF 1=On used to customize idle message */
        }
   
	// Check if running in CAD30 configuration
	bIsUcm = PSQ_Is_Ucm_Behaviour();
	if (bIsUcm < 0)
	{
		// PSQ_Is_Ucm_Behaviour is not yet implemented => simply checks the hardware type
		if (PSQ_Get_hardware_type() == TYPE_TERMINAL_CAD30)
		{
			bIsUcm = TRUE;
		}
		else
		{
			bIsUcm = FALSE;
		}
	}

	if (bIsUcm)
	{
		// We are running on a CAD30

		// Check if UCMC is loaded or not
		if (ObjectGetDescriptor(OBJECT_TYPE_APPLI, TYPE_UCMC, &UcmcDescriptor) == 0)
		{
			// A component 0x12 is loaded, but is it UCMC ?

			if (ServiceGet(TYPE_UCMC, SERVICE_UCMC, &ucPriority) == 0)
			{
				// UCMC is loaded ! (functions iLIBUCM_xxx are available)
				UCM_Present = TRUE;
			}
		}
	}

   iGraphic_message("Sample PinChip", 100);

   Buzzer_Test();
   
   /* Sample Power Management */
   /* Deep Sleep for IUP250 and IUC180 */
   /* Light and Deep Sleep for UCR */
   /* example: iRet = iSetSleepPowerManagement( 2,60);  Deep sleep after 60s as soon as possible */
#endif

	CustomNoAppli = noappli;

	nb_time_select =0;

	read_date(&date);
	memcpy (&paramseq, param_out, sizeof (paramseq));

	size = 0;

	CUPAR_Update_Kernel_and_System_Infos();

	isPinpad = B_NON_INIT;

	/*&BEGIN FT/08/3682/NP tests presence and level of security DLL */
	Test_DLL_Security_Presence();
	/*&END FT/08/3682/NP tests presence and level of security DLL */

	// check for first run : cold or warm reset ?
	if (first_init (noappli,&chgt,&type) != FSE_FAILED)
	{
#ifdef _SIMULPC_
		chgt = (FLAG_CHGT)CHGT_OUI;
#endif
		if (chgt == (FLAG_CHGT)CHGT_OUI )
		{   
			// cold reset
			raz_init(noappli);

			memset(Tmp, 0, sizeof(Tmp));
			memset(serial_number, 0, sizeof(serial_number));
			/*SystemFioctl(SYS_FIOCTL_GET_PRODUCT_SERIAL_NUMBER, Tmp);*/
			TM_GetSerialNumber(Tmp);
			Hexasc(serial_number, Tmp, sizeof (serial_number)-1);
			CUTERMsetSerialNumber ((char *)serial_number);
			// Set terminal ID to 0
			memset(Tmp, 0, sizeof(Tmp));
			CUTERMsetTerminalId(Tmp);

			CUENT_IsFirst_Init = TRUE;

			// Make general initalisation
			iRet = CUDISK_CreateDisk();
			if (iRet == FS_OK)
			{
				CUENT_First_Init ();
			}

			// This function call the PAR_ReadArray() function
			CUPAR_InitDefFiles (FALSE);

			CUENT_IsFirst_Init = FALSE;

		}
		else
		{
			char *ptrDummy = 0;
			// Warm reset
			CUENT_IsFirst_Init = FALSE;

			// Initialise TLVTree
			PAR_InitParam(C_PARAM_INIT_APLI, ptrDummy);

			iRet = CUDISK_CreateDisk();
			if (iRet == FS_OK)
			{
				// CUBATCH_RestoreLog();
				CUPAR_RestoreParam (C_MGT_PARAM_PAR_FILE_FIRST);
			}
			else
			{
				upload_diagnostic_txt((unsigned char *)"DISK CREATE HS\n");
			}
		}
	}

	iRet = CUDISK_CreateDisk();
	if (iRet == FS_OK)
	{
		// Test consistency of the batch file
		CUBATCH_RestoreLog();

		// Unmount the volume
		CUDISK_UnmountDisk();
	}

#ifdef _USE_SPED_
	// FT : 2571 swipe
	swipe2 = fopen("SWIPE2","r*");
	if (swipe2 != NULL)
	{
		cr_Sped_MSREnable = Sped_MSREnable (1);
		fclose (swipe2);
	}
#endif

	paramseq.noappli = noappli;

	memcpy (param_out, &paramseq, sizeof (paramseq));

#ifdef _TOOLWARE_
	// Check if the kernel and the system support TOOLWARE
	CUPAR_Init_ToolWare();
#endif /* _TOOLWARE_ */

	return (FCT_OK);
}

//===========================================================================
//! \brief This function tests the presence of security DLL. And if it has
//! at least a release 0204.
//===========================================================================
static void	Test_DLL_Security_Presence(void)
{
	int sec_ver;
	int ret; 

#ifdef _USE_UCM_
#else
FILE * printer;
#endif

#ifndef _SIMULPC_
	ret = ObjectLoad (OBJECT_TYPE_DLL, "SECURITY");  
#else

	ret =0;
#endif 

	if ((ret != 0) && (ret != OL_ALREADY_LOADED))
	{
#ifdef _USE_UCM_
		if(UCM_Present)
		{
         iLIBUCM_Print_Open(UCMC_PRINT,"w-");
         iLIBUCM_Print_Message(UCMC_PRINT,"\nCustom\nPlease LOAD DLL SECURITY\n\n\n\n\n\n ");
         iLIBUCM_Print_Close(UCMC_PRINT);
        
		}
#else
      printer=fopen("PRINTER","w-");
      pprintf ("\n""Custom \n");
      pprintf ("Please LOAD DLL SECURITY\n");

      pprintf ("\n\n\n\n\n");
      ttestall(PRINTER,0);
      fclose(printer);
#endif

	}
	else
	{ 		
#ifndef _SIMULPC_
		sec_ver = SEC_Version();
#else
		sec_ver =0x020400;
#endif 

		if (sec_ver<0x020400)
		{
#ifdef _USE_UCM_
      	if(UCM_Present)
      	{
            iLIBUCM_Print_Open(UCMC_PRINT,"w-");
            iLIBUCM_Print_Message(UCMC_PRINT,"\nCustom\nPlease LOAD DLL SECURITY\nWith VERSION >= 0204\n\n\n\n\n\n ");
            iLIBUCM_Print_Close(UCMC_PRINT);
         }
#else
         printer=fopen("PRINTER","w-");
   		pprintf ("\n""Custom \n");
   		pprintf ("\n""Please LOAD DLL SECURITY\nWith VERSION >= 0204");

   		pprintf ("\n\n\n\n\n");
   		ttestall(PRINTER,0);
   		fclose(printer);
#endif
  		}
   }
}

//===========================================================================
//! \brief This function prints the application info and status.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : not used.
//! \return Always FCT_OK.
//===========================================================================
static int cu_state (NO_SEGMENT noappli,void *param_in,void *param_out)
{
	DATE    date;
	unsigned char text[30];
	object_info_t info;
	object_descriptor_t desc;

	if(ObjectGetInfo(OBJECT_TYPE_APPLI,noappli,&info) ==0)
	{

		sprintf ((char *) text, "\x1b""EEMV CUSTOM""\x1b""F");
		CUTERMprintLine((char*)text);

		read_date (&date);
		//???
		sprintf ((char *) text, "%.2s/%.2s/%.2s  %.2s:%.2s", date.day, date.month, date.year, date.hour, date.minute);
		CUTERMprintLine((char*)text);

		sprintf ((char *) text, "Vers. : %s", info.name); // Get_AppliName(noappli));
		CUTERMprintLine((char*)text);

		sprintf ((char *) text, "CRC   : %04x",info.crc); //Get_AppliCrc(noappli));
		CUTERMprintLine((char*)text);

		ObjectGetDescriptor(OBJECT_TYPE_APPLI,info.application_type, &desc  );
		sprintf ((char *) text, "Code  : %06x",desc.code_adr );// Get_AppliCode(noappli));
		CUTERMprintLine((char*)text);

		sprintf ((char *) text, "Data  : %06lX",(unsigned long)desc.data_adr );//(unsigned long)Get_AppliData(noappli));
		CUTERMprintLine((char*)text);

		CUTERMpaperFeed();
	}

	return (FCT_OK);

}

//===========================================================================
//! \brief This function gives the application state.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing the fields appname 
//! and no_appli updated.
//! \return Always FCT_OK.
//===========================================================================
static int cu_is_state (NO_SEGMENT noappli,void *param_in,S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int iRet ;

	memcpy (&etatout, param_out, sizeof(etatout));

	etatout.returned_state[etatout.response_number].state.response = REP_OK ;

	memcpy (param_out, &etatout, sizeof (etatout));
	iRet = cu_is_name (noappli, PT_NULL, param_out);
	return (iRet);
}

//===========================================================================
//! \brief This function prints a ticket with the total amount in the batch
//! data file.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : not used.
//! \return Always FCT_OK.
//===========================================================================
static int cu_consult (NO_SEGMENT noappli,void *param_in, void *param_out)
{
	int merchLang;
	unsigned long nb_record;
	unsigned long total_amount;
	T_Bool    ret;
	DATE date;
	char str_line [80];

	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();

	// Read Batch status
   ret = CUBATCH_GiveStatistics(&nb_record, &total_amount);

	if (ret)
	{
		// Print the Consult Receipt, using merchant terminal language
		CUTERMprintLine(" ");
		CUTERMsetPrinter(PRINT_LARGE);
		CUTERMprintLine(CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_EMV_CONSULT, merchLang));
		CUTERMsetPrinter(PRINT_NORMAL);
		CUTERMprintLine(" ");

		// Read and print current date
		read_date(&date);
		//???
      sprintf(str_line, "%.2s/%.2s/%.2s  %.2s:%.2s\n", date.day, date.month, date.year, date.hour, date.minute);
		CUTERMprintLine(str_line);

		CUTERMprintLine(" ");

		// Print the number of tx
		sprintf (str_line,
			//                 "%s : %d",
              "%s : %ld", CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_NB_OF_TX, merchLang), nb_record);
		CUTERMprintLine(str_line);

		/* Print the total amount                                          */
		sprintf (str_line,
			//                 "%s : %d",
              "%s : %ld", CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_TOTAL, merchLang), total_amount);
		CUTERMprintLine(str_line);

		/* Ending the print receipt correctely */
		CUTERMpaperFeed();
	}

	return (FCT_OK);
}

//===========================================================================
//! \brief This function allows the manager to modify all the parameters of 
//! the application.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing the fields mask, appname 
//! and no_appli updated.
//! \return Always FCT_OK.
//===========================================================================
static int cu_is_change_init(NO_SEGMENT noappli, void *param_in, S_ETATOUT *param_out)
{
	// Internal data declaration
	S_ETATOUT     etatout;

	// Allow the manager to modify all the parameters : reset the whole mask
	memcpy(&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.mask = 0;

	memcpy (param_out, &etatout, sizeof (etatout));

	// Call the manager service cu_is_name which will give the application name
	// and number and then increment the number of answers
	cu_is_name(noappli, PT_NULL, param_out);

	return(FCT_OK);
}

//===========================================================================
//! \brief This function informs the manager that the application has a 
//! periodic function to be executed.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing the fields response, appname, 
//! no_appli, response updated.
//! \return Always FCT_OK.
//===========================================================================
int is_time_function(NO_SEGMENT noappli, void *param_in, S_ETATOUT *param_out)
{
	// Internal data declaration
	S_ETATOUT etatout;

	memcpy(&etatout, param_out, sizeof(etatout));

	etatout.returned_state[etatout.response_number].state.response = REP_KO;

	memcpy (param_out, &etatout, sizeof (etatout));

	// Call the manager service cu_is_name which will give the application name
	// and number and then increment the number of answers
	cu_is_name(noappli, PT_NULL, param_out);


	return(FCT_OK);
}

//===========================================================================
//! \brief This function prints the scheduled automatic application calls.
//! ("call" is a reserved manager function).
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : not used.
//! \return Always FCT_OK.
//===========================================================================
static int cu_mcall(NO_SEGMENT noappli, void *param_in, void *param_out)
{
	// Internal data declaration
	int    merchLang;
	char   chaine1[40];
	DATE   date_time;

	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();

	// Print the Call Receipt, using merchant terminal language

	CUTERMprintLine(" ");
	CUTERMprintLine(CUMESS_Read_Message(CALL_RECEIPT_TABLE, CALLR_MESS_EMV_CALL, merchLang));
	CUTERMprintLine(CUMESS_Read_Message(CALL_RECEIPT_TABLE, CALLR_MESS_AUTOMATIC_CALLS, merchLang));

	CUBATCH_GetNextTransfDate (&date_time);
	if (PSQ_Donner_format_date() != 0)
	{
      sprintf(chaine1, "%.2s/%.2s/%.2s  %.2s:%.2s\n", date_time.month, date_time.day, date_time.year, date_time.hour, date_time.minute);
	}
	else
	{
      sprintf(chaine1, "%.2s/%.2s/%.2s  %.2s:%.2s\n", date_time.day, date_time.month, date_time.year, date_time.hour, date_time.minute);
	}
	CUTERMprintLine(chaine1);

	// Ending the print receipt correctely
	CUTERMpaperFeed();

	// In all cases, always return FCT_OK
	return(FCT_OK);
}

//===========================================================================
//! \brief This function informs the component that the manager parameters 
//! have been modified. 
//! \param[in] noappli : application number.
//! \param[in] param_in : structure S_MODIF_P containing the fields : 
//! - mask : bitfield where each bit corresponds to a parameter.
//! - date_difference : represents the gap in days between the previous date
//! and the new one.
//! - time_difference : represents the gap in minutes between the previous time
//! and the new one.
//! \param[out] param_out : not used.
//! \return Always FCT_OK.
//===========================================================================
static int cu_modif_param(NO_SEGMENT noappli, S_MODIF_P *param_in, void *param_out)
{
	// Internal data declaration
	S_MODIF_P     etatout;

	// Reading mask in param_in
	memcpy(&etatout, param_in, sizeof(etatout));

	// Signal new parameters to engine
	CUSERV_New_Parameters = TRUE;

	return (FCT_OK);
}

//===========================================================================
//! \brief This function authorizes the download of the parameters file.
//! \param[in] no_appli : application number.
//! \param[in] param_in : S_FILE structure containing the fields volume_name, file_name.
//! \param[out] param_out : not used.
//! \return Always FCT_OK.
//===========================================================================
static int cu_file_received (NO_SEGMENT no_appli,S_FILE *param_in,void *param_out)
{
	unsigned short   lg_code;
	int              iRet;
	S_FS_PARAM_CREATE ParamCreat;
	char             Dir_File[25]; /*1+3+8+1+3+1, slash disk,name,point,extension,null*/
	char             Dir_Label[25];
	char             LabelDiskName[DISK_NAME_SIZE];
   char cTemp[100];
   
	sprintf( cTemp, "cu_file_received start");
	trace( 0x6E01, strlen(cTemp), cTemp);

	sprintf (Dir_Label,"/%s",param_in->volume_name);

	if (IsdedicatedFile(param_in)==TRUE)
	{
		ParamCreat.Mode         = FS_WRITEONCE;

		iRet = FS_mount (Dir_Label,&ParamCreat.Mode);

		if (iRet == FS_OK)
		{
			memclr(Dir_File,sizeof(Dir_File));
			sprintf (Dir_File,"/%s/%s",param_in->volume_name,param_in->file_name);

			trace(0x6E02, strlen("File received :"), "File received :");
			trace(0x6E02, strlen(Dir_File), Dir_File);

			iRet = FALSE;

         if ((strstr(param_in->file_name, C_AID_NAME) != NULL) || (strstr(param_in->file_name, C_ICS_NAME) != NULL) || (strstr(param_in->file_name, C_KREVOK_NAME) != NULL)
            || (strstr(param_in->file_name, C_CAKEYS_NAME) != NULL) || (strstr(param_in->file_name, C_FILE_NAME_XML) != NULL))
			{
				{
					char tmpbuf[30];
					sprintf(tmpbuf, "Load %s file", param_in->file_name);
					trace(0x6E02, strlen(tmpbuf), tmpbuf);
				}

				// CUPAR_FileCopy() is allready called by this function
				iRet = (int)CUPAR_FileRead (Dir_File, param_in->file_name);

				if ((strstr(param_in->file_name, C_ICS_NAME) != NULL) && (iRet != 0))
				{
					iRet = CUPAR_InitICS();
				}
				else if ((strstr (param_in->file_name, C_FILE_NAME_XML) != NULL) && (iRet != 0))
				{
					char FilePath_L[33];

					memclr(LabelDiskName, sizeof(LabelDiskName));
					CUDISK_Get_Disk_Name(LabelDiskName);

					sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM);
					
					// File successfully read. Store it in private disk
					// CUPAR_FileCopy(Dir_File, param_in->file_name);
					trace(0x6E02, strlen("Update PARAM.PAR file"), "Update PARAM.PAR file");
					CUPAR_Update_Param_File(FilePath_L);
				}
				else if (strstr(param_in->file_name, C_CAKEYS_NAME) != NULL)
				{
					// Control and delete bad keys
					iRet = CUPAR_ControlCAKEYS();
				}
			}
			else if (strstr (param_in->file_name, C_BLACKL_NAME) != NULL)  // Black List
			{
				/* CUPAR_FileCopy() is allready called by this function */
				iRet = CUPAR_BlackListInit (Dir_File);
			}
			else
			{
				// This file isn't for us.
				iRet = TRUE; 
				trace(0x6E02, strlen("File not managed by Custom EMV"), "File not managed by Custom EMV");
			}

			if (iRet == FALSE)
			{
				char * pc_l_DisplayTxt;
				trace(0x6E02, strlen("File management KO"), "File management KO");
				CUDB_Get_cardholder_language (&lg_code);
				if (lg_code > C_NBLANGHOLDER)
				{
					lg_code = 0;
				}

				pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROCESSING_ERROR, lg_code);
				CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
				CUTERMsleep (5000);
			}
			else
				trace(0x6E02, strlen("File management ok"), "File management ok");
		}
		FS_unmount(Dir_File);
		return (STOP);

	}
	return (REQUEST_NSTOP);

}

//===========================================================================
//! \brief This function .
//! \param[in] param_in : S_FILE structure containing the fields volume_name, file_name.
//! \return
//===========================================================================
static int IsdedicatedFile (S_FILE *param_in)
{
	unsigned char AppliNb[5];
	unsigned short AppliNbLong;

	memclr(AppliNb,sizeof(AppliNb));

   if ((strstr(param_in->file_name, C_AID_NAME) == NULL) && (strstr(param_in->file_name, C_ICS_NAME) == NULL) && (strstr(param_in->file_name, C_KREVOK_NAME) == NULL)
      && (strstr(param_in->file_name, C_CAKEYS_NAME) == NULL) && (strstr(param_in->file_name, C_BLACKL_NAME) == NULL) && (strstr(param_in->file_name, C_FILE_NAME_XML) == NULL))
	{
		return FALSE;
	}

	if ( (strstr(param_in->file_name, C_AID_NAME) != NULL))
	{
		memcpy (AppliNb,&param_in->file_name[sizeof(C_AID_NAME)+1],4);
	}

	if ((strstr(param_in->file_name, C_ICS_NAME) != NULL) )
	{
		memcpy (AppliNb,&param_in->file_name[sizeof(C_ICS_NAME)],4);
	}

	if ((strstr(param_in->file_name, C_KREVOK_NAME) != NULL ) )
	{
		memcpy (AppliNb,&param_in->file_name[sizeof(C_KREVOK_NAME)],4);
	}

	if ((strstr(param_in->file_name, C_BLACKL_NAME) != NULL ) )
	{
		memcpy (AppliNb,&param_in->file_name[sizeof(C_BLACKL_NAME)],4);
	}

	if ((strstr(param_in->file_name, C_CAKEYS_NAME) != NULL ) )
	{
		memcpy (AppliNb,&param_in->file_name[sizeof(C_CAKEYS_NAME)],4);
	}

	if ((strstr(param_in->file_name, C_FILE_NAME_XML) != NULL) )
	{
		memcpy (AppliNb,&param_in->file_name[sizeof(C_FILE_NAME_XML)-1],4);
	}

	/* if there is no extension for multi custom application and appli type is Standard custom, so file is kept */
	/*  this is to keep compatibility */
	if ((memcmp (AppliNb,"PAR",3)==0)&& (CustApplicationNumber==I_EMVCUST_Type_Appli))
		return TRUE;

	/*&BEGIN FT/09/4668/MA acceptance of ICS_0xxx.par file*/
	if ((AppliNb[0] >= 'A') && (AppliNb[0] <= 'F'))
	   AppliNbLong = (AppliNb[0] - 'A' + 0xa) << 12;
   else
      AppliNbLong = (AppliNb[0] - '0') << 12;
	if ((AppliNb[1] >= 'A') && (AppliNb[1] <= 'F'))
	   AppliNbLong |= (AppliNb[1] - 'A' + 0xa) << 8;
   else
      AppliNbLong |= (AppliNb[1] - '0') << 8;
	if ((AppliNb[2] >= 'A') && (AppliNb[2] <= 'F'))
	   AppliNbLong |= (AppliNb[2] - 'A' + 0xa) << 4;
   else
      AppliNbLong |= (AppliNb[2] - '0') << 4;
	if ((AppliNb[3] >= 'A') && (AppliNb[3] <= 'F'))
	   AppliNbLong |= (AppliNb[3] - 'A' + 0xa);
   else
      AppliNbLong |= (AppliNb[3] - '0');
	/*&END FT/09/4668/MA acceptance of ICS_0xxx.par file*/

	if (AppliNbLong == CustApplicationNumber  )
		return TRUE;

	return FALSE;

}


//===========================================================================
//! \brief This function returns the name of the application.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing significant fields
//! appname, and no_appli.
//! \return Always FCT_OK.
//===========================================================================
static int cu_is_name(NO_SEGMENT noappli, void *param_in, S_ETATOUT *param_out)
{
	// Internal data declaration
	S_ETATOUT etatout;

	memcpy(&etatout, param_out, sizeof(etatout));

	strcpy(etatout.returned_state[etatout.response_number].appname, g_szAppName);
	etatout.returned_state[etatout.response_number].no_appli = noappli;
	etatout.response_number++;

	memcpy (param_out, &etatout, sizeof (etatout));

	return(FCT_OK);
}

//===========================================================================
//! \brief This function authorizes or not, the manager, to perform the downloading of
//! the application which the number is given as parameter.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing the field response appname
//! and no_appli updated.
//! - the field response is set to REP_OK if the download is authorized.
//! - the field response is set to REP_KO if the download is refused.
//! \return Always FCT_OK.
//===========================================================================
static int cu_is_evol_pg (NO_SEGMENT noappli, void *param_in, S_ETATOUT *param_out)
{
	// Internal declaration data
	S_ETATOUT etatout;
	int       isEvolPg;
	unsigned long nb_record;
	unsigned long total_amount;
	T_Bool    ret;

	memcpy(&etatout, param_out, sizeof(etatout));

	// Read Batch status
   ret = CUBATCH_GiveStatistics(&nb_record, &total_amount);

	// EMV CUSTOM download allowed if the batch file is void
	if ((!ret) || nb_record == 0)
	{
		etatout.returned_state[etatout.response_number].state.response = REP_OK;
	}
	else
	{
		etatout.returned_state[etatout.response_number].state.response = REP_KO;
	}

	memcpy (param_out, &etatout, sizeof (etatout));

	isEvolPg = cu_is_name(noappli, NULL, param_out);
	// In all cases, always return FCT_OK

	return(isEvolPg);
}

//===========================================================================
//! \brief This function performs the first initialisation.
//===========================================================================
static void CUENT_First_Init (void)
{
	DATE tmp_date;
	char FilePath_L[33];
	char *ptrDummy = 0;
	char LabelDiskName[DISK_NAME_SIZE];

	ucMode2000 = TRUE;

#ifdef _TOOLWARE_
	ucAdvancedMode = FALSE;
#endif // _TOOLWARE_

	RetransmitIndicator = FALSE;

	usDefaultCurrency = C_IEP_CURCY_EURO;

	// Default mode : No delay
	ucDelayAfterAtr = FALSE;

	// Retreive Terminal merchant language
	PSQ_Give_Language();

	// Create batch log
	// CUBATCH_DeleteLog();
	// CUBATCH_CreateLog(CUBATCH_DEF_LOG_SIZE);

	// Create black-list file
	CUBLACKL_DeleteBlackList();
	CUBLACKL_CreateFile(CUBLACKL_DEF_FILE_SIZE);

	// Initialise default values in databases
	EMVCUST_Initialise_TlvTree (NULL);

	// Initialise date to the next periodic call with default value
	read_date(&tmp_date);
	CUBATCH_SetNextTransfDate (&tmp_date);

	memclr(LabelDiskName, sizeof(LabelDiskName));
	CUDISK_Get_Disk_Name(LabelDiskName);

	memclr(FilePath_L,sizeof(FilePath_L));
	sprintf(FilePath_L, "/%s",LabelDiskName);
	FS_unmount(FilePath_L);

	PAR_InitParam(C_PARAM_INIT_APLI, ptrDummy); /* !!! */
	PAR_InitParam(C_PARAM_DEFAULT, ptrDummy);

	CUPAR_ResetAdditionnalICS();
	CUPAR_ResetAdditionnalAID();
	CUPAR_ResetAdditionnalKRevok();
}


//===========================================================================
//! \brief This function processes a non EMV transaction or a magnetic transaction.
//! \param[in] noappli : application number.
//! \param[in] trans_in : structure S_TRANSIN with fields containing transaction 
//! parameters such as : amount, currency, transaction, entry, payment, support...
//! \param[out] trans_out : structure S_TRANSOUT containing the field noappli.
//! \return
//! - FCT_OK : the application has not recognized the card.
//! - STOP : the application has recognized the card and processed the current
//! debit transaction.
//===========================================================================
static int cu_debit_non_emv(NO_SEGMENT noappli, S_TRANSIN *trans_in, S_TRANSOUT *trans_out)
{
	// Internal data declaration
	int        debitExport;
	S_TRANSOUT transaction_out, *param_out;
	unsigned short lg_code;
	int deb_res;

#ifdef _USE_SPED_
	int cr_Sped_MSREnable;
	FILE *swipe2;
#endif

#ifdef _USE_UCM_
	T_UCMHOST_DEBIT sDebit;
	T_UCMHOST_R_DEBIT sRDeb;
	int RunMSR;
   int i,j;
	unsigned char		   bIccOK;   
   int                    iWhat, iRet;
    char cTemp[10];
#endif
	int bStateHeader;

	bStateHeader = StateHeader(0);

	memcpy(&transaction_out, trans_out, sizeof(S_TRANSOUT));
	param_out = &transaction_out;

	debitExport = FCT_OK;
	CUDB_Get_cardholder_language (&lg_code);


	/*&BEGIN FT/07/2825/MA     inform CAd30 simu of paiement  */
#ifdef _USE_UCM_

	RunMSR = TRUE;

   iLIBUCM_Display_Message(UCMC_DISPLAY, "DEBIT\nIN PROGRESS...", 100);

	if (RunMSR)
	{
#endif
	/*&END FT/07/2825/MA     inform CAd30 simu of paiement  */

		// Begin
		if ((trans_in->support == TRACK2_SUPPORT) || (trans_in->support == TRACK12_SUPPORT) || (trans_in->support == TRACK32_SUPPORT) || (trans_in->support == TRACK123_SUPPORT))
		{
			deb_res = CUSTR_Mag_Stripe_Debit ((trans_in->entry != NO_ENTRY), trans_in->amount, (int) (trans_in->report_piste), (char*)trans_in->track2);
			if (deb_res == FALSE)
			{
				debitExport = FCT_OK;
			}
			else
			{
				debitExport = STOP;
			}
		}  /* End if Chip Card                           */

#ifdef _USE_SPED_

		/* FT : 2571 swipe */
		swipe2 = fopen("SWIPE2","r*");
		if (swipe2 != NULL)
		{
			cr_Sped_MSREnable = Sped_MSREnable (1);
			fclose (swipe2);
		}
#endif

		/*&BEGIN FT/07/2825/MA     inform CAd30 simu of paiement  */
#ifdef _USE_UCM_
		if(UCM_Present)
		{
        	bIccOK=FALSE;
   
  		
      		memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
      		memset ( &sDebit, 0x00, sizeof ( T_UCMHOST_DEBIT ) ) ;
      		
      		sDebit.ucFunction = DEBIT_NON_EMV ;

         if (iIsProtocolUCMC() != 0)
         {
      		// the application gives UCM the entry point to be recalled to when recording is required 
      		iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

   	   	switch ( iWhat )
      		{
       	 	   			
      			case UCMCPAY_SOLV :
      			   {
                            bIccOK=FALSE;

                            if(  bIccOK==FALSE) 
                            {
                                    if ( trans_in->support == TRACK2_SUPPORT )
                                    {
                                         sprintf( cTemp, "Support %d %s", trans_in->support, (char*)trans_in->track2 );
                                         iLIBUCM_Print_Message( UCMC_PRINT, cTemp ) ;
                                    }
                            }

      			 	if( ( giDisplayType == PARAM_TYPE_IUC180 ) || ( giDisplayType == PARAM_TYPE_IUP250 ) )
      			 	{
      					iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_BLUE);
      					iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_BLUE);
      			 	}

      				iLIBUCM_Display_Message ( UCMC_DISPLAY, "TRANSACTION\nIN PROGRESS...", 100 ) ;
                   

           			/******* RESPONSE ************/
      				memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
      				
      				//TODO debit card
      				// amount  sDebit.ulAmount
      				sRDeb.ucTypeCardStruct = UCMHOST_CARD_UNKNOWN ;
      				if ( (bIccOK) || (debitExport == FCT_OK) )
                  {
                     sRDeb.ucCr = UCMHOST_CR_OK;
      					sRDeb.ulAmount=sDebit.ulAmount;
                                   iGraphic_message( "DEBIT OK", 200 );
      					//iLIBUCM_Display_Message ( UCMC_DISPLAY, "DEBIT OK", 100 ) ;
           			}
      				else
                  {
                     sRDeb.ucCr = UCMHOST_CR_CARDINVALIDE;
      					sRDeb.ulAmount=0;
      					iLIBUCM_Display_Message ( UCMC_DISPLAY, "REFUSED", 100 ) ;
           			}
                  
      				sRDeb.usAppName    = noappli ;
         			strcpy ( (char *)sRDeb.tAppLibelle, (char *)g_szAppName ) ;
      				
         			memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
         			memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
         			sRDeb.tCurrency.posdec = 2 ;

           			read_date( &sRDeb.u.sCard.uAppli.sApp.sLocalDate ) ;

      				iRet=iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) ;	
         			if ( iRet < 0 )
         			{
         		 		iLIBUCM_Display_Message ( UCMC_DISPLAY, "iLIBUCM_Pay_Result_Debit\nUCMHOST_FCT_SOLV", 100 ) ;
      				}

      				iLIBUCM_Pay_End (sizeof( T_UCMHOST_R_DEBIT ), &sRDeb);

      			 	if( ( giDisplayType == PARAM_TYPE_IUC180 ) || ( giDisplayType == PARAM_TYPE_IUP250 ) )
      			 	{
      			 		iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_GREEN);
      			 		iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_WHITE);
      			 	}

               }
                  break;

         		case UCMCPAY_RECORD : /* UCMPAY_RECORD */
      		   {
      				iLIBUCM_Display_Message ( UCMC_DISPLAY, "RECORD\nIN PROGRESS...", 100 ) ;

      				memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
      			
      				//TODO record transaction
      				// update amount  sDebit.ulAmount

      				sRDeb.ucCr         = UCMHOST_CR_OK ;
                            sRDeb.ucDiag      = FCT_OK ;

      				sRDeb.usAppName    = noappli ;
      				strcpy ( (char *)sRDeb.tAppLibelle, (const char *)g_szAppName ) ;

			sRDeb.ulAmount = sDebit.ulAmount;
			memcpy( &sRDeb.tCurrency, &sDebit.tCurrency, sizeof( S_MONEY));

			sRDeb.ucPrinter = 0;
			sRDeb.ucDisplay = 0;

			sRDeb.ucMode = sDebit.ucTrsMode;
			sRDeb.ucTypeCardStruct = UCMHOST_CARD_EMV;
			sRDeb.ucSupport = sDebit.ucTrsSupport;

			sRDeb.ucCardHolderLanguage = 0xFF;

			read_date( &sRDeb.u.sCard.uAppli.sApp.sLocalDate ) ;

			sRDeb.u.sCard.uAppli.sApp.ucTypeTrs[ 0 ] = 'T';
			sRDeb.u.sCard.uAppli.sApp.ucTypeTrs[ 1 ] = 'T'; /* UCM */

			memset( sRDeb.u.sCard.uAppli.sApp.OwnerNumber, '1', sizeof(NO_PORTEUR) );

                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[0] = 'J';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[1] = 'J';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[2] = 'M';
                 	sRDeb.u.sCard.uAppli.sApp.ucEndVal[3] = 'M';
                 	memset( &sRDeb.u.sCard.uAppli.sApp.ucEndVal2[0], 0, 6 );

			memset( sRDeb.u.sCard.uAppli.sApp.ucServiceCode, 'S', 3 );
			sRDeb.u.sCard.uAppli.sApp.iTrsNumber = 1234;
			sRDeb.u.sCard.uAppli.sApp.iRemisNumber = 5678;
			sRDeb.u.sCard.uAppli.sApp.ulAmountCV = 9999;
			memset( &sRDeb.u.sCard.uAppli.sApp.sCurrencyCV, 'V', sizeof(T_NOM_MONEY) ); /* UCM */      
                       sRDeb.u.sCard.uAppli.sApp.sCurrencyCV.posdec = 2; /* UCM */
         
			sRDeb.u.sCard.uAppli.sApp.ulAmountEstimat = 7777;

			memset( &sRDeb.u.sCard.uAppli.sApp.ucAutoNumber[0], 'A', 6 );
			sRDeb.u.sCard.uAppli.sApp.ucForcingCode = 'F';

			memset( &sRDeb.u.sCard.uAppli.sApp.ucEndVal2[0], 0, 6 );
			memset( &sRDeb.u.sCard.uAppli.sApp.ucRuf1[0], 0, 4 );

			sRDeb.u.sCard.uAppli.sApp.ucReaderMode = 'C';

			sRDeb.u.sCard.uAppli.sApp.usTASA = 9;

                 	memset( &sRDeb.u.sCard.uCard.sEMV.ucCrypto[0], 'C', 16 ) ;

                    for( i = 0; i < Taille_LABEL; i++ )
                    {
                       sRDeb.u.sCard.uCard.sEMV.LabelAID[ i ] = 'A' + i ;

                    }
                 	sRDeb.u.sCard.uCard.sEMV.AID.aid_length = Taille_LABEL ;
                    sRDeb.u.sCard.uCard.sEMV.AID.aid[0] = 0xA0 ;
                    
                    j = 1;
                    for( i = 1; i < Taille_LABEL; i++ )
                    {
                       sRDeb.u.sCard.uCard.sEMV.AID.aid[i] = j*0x10 + ( j + 1 ) ;
                       j+=2;
                    }

			// T_UCMHOST_CARD_ACCEPT
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoContrat, 'C', 7 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoSA, 'S', 3 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucNoSiret, 'R', 14 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypeActivite, 'C', 4 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypeSite, 'S', 8 ) ;   /* UCM */
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucTypePaiement, 'P', 2 ) ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucEnseigne, 'E', 60 );
			sRDeb.u.sCard.uAccept.sAcpt.ucEnseigne[ 60 ] = 0 ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucEnteteTicket, 'T', 50 );
			sRDeb.u.sCard.uAccept.sAcpt.ucEnteteTicket[ 50 ] = 0 ;
			memset( sRDeb.u.sCard.uAccept.sAcpt.ucPiedTicket, 'P', 50 );
			sRDeb.u.sCard.uAccept.sAcpt.ucPiedTicket[ 50 ] = 0 ;
         		memset( sRDeb.u.sCard.uAccept.sAcpt.ucCrVerifAcc, 'V', 2 );
							  
  				if( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) < 0 )
  				{
  					iLIBUCM_Display_Message ( UCMC_DISPLAY, "iLIBUCM_Pay_Result_Debit\nCMHOST_FCT_ENREG", 100 ) ;
  				}
  			
  				iLIBUCM_Pay_End (sizeof( T_UCMHOST_R_DEBIT ), &sRDeb);							

               }
                  break;
      			 
        			default :
                   /* Error management*/
         			iLIBUCM_Display_Message ( UCMC_DISPLAY, "UNKNOWN REQUEST\n??", 100) ;
           			iLIBUCM_Pay_End(0, NULL);
               break ;
        		}
         }
         else
         {
//gulPaymentAmount
            if( trans_in->power_on_result != 0) /* 3=mute */
            {
               if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
               {
                  //cu_fall_back(noappli, trans_in,trans_out);
                  iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_CYAN);
                  iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_CYAN);
               }

                iRet = iUnattendedRead_Iso123();

               if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
               {
                  iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_GREEN); /* IUR250 */
                  iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_WHITE); /* IUP250 */
               }

            }
            else
            {
               if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
               {
                  iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_CYAN); /* IUR250 */
                  iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_CYAN); /* IUP250 */
               }

               iLIBUCM_Display_Message(UCMC_DISPLAY, "PAYMENT\nIN PROGRESS...", 500);

               if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
               {
                  iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_GREEN); /* IUR250 */
                  iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_WHITE); /* IUP250 */
               }
            }
         }
            transaction_out.rc_payment  = PAY_OK;
 

		}
	}
	else
	{
		debitExport = FCT_OK;
	}
#endif
	/*&END FT/07/2825/MA     inform CAd30 simu of paiement  */

	transaction_out.noappli=noappli;

	memcpy (param_out, &transaction_out, sizeof (transaction_out));

	StateHeader(bStateHeader);

	return(debitExport);
}

//===========================================================================
//! \brief This function returns the priority of EMV selection of chip card
//! application.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing the fields response, appname 
//! and no_appli updated.
//! \return Always FCT_OK.
//===========================================================================
int cu_is_for_you_before  (NO_SEGMENT noappli,S_TRANSIN *param_in, S_ETATOUT *param_out)
{
	int iRet ;
	S_ETATOUT etatout;

#ifdef _TOOLWARE_
	if (ucAdvancedMode == TRUE)
	{
		ulMMI_langue   = 0;
		ulMMI_selappli = 0;
		ulBegin_transaction = get_tick_counter();
	}
#endif // _TOOLWARE_

	TrackIAC_Init();
	memcpy (&etatout, param_out, sizeof(etatout));

	etatout.returned_state[etatout.response_number].state.response = 0 ;
	memcpy (param_out, &etatout, sizeof (etatout));
	iRet = cu_is_name (noappli, PT_NULL, param_out);

	return (FCT_OK);
}

//===========================================================================
//! \brief This function returns the priority of EMV selection of chip card
//! application
//! \param[in] noappli : application number.
//! \param[in] param_in : structure S_TRANSIN containing the fields support, 
//! power_on_result, amount.
//! \param[out] param_out : structure S_CARDOUT with the fields appname, and noappli. 
//! Optionnally it can contain the fields cardappnumber, cardapp, cardappname.
//! \return Always FCT_OK.
//===========================================================================
static int cu_is_for_you_after  (NO_SEGMENT noappli,S_TRANSIN *param_in, S_CARDOUT *param_out)
{
	S_CARDOUT card_out;
	S_ETATOUT etatout;

	etatout.response_number = 0;
	cu_is_name(noappli, NULL, &etatout);

	memcpy (&card_out, param_out, sizeof(card_out));


	// Card recognised only when mag stripe is used
   //if ((param_in->power_on_result) != 0) /* 3=mute */ 
//	{
      strcpy(card_out.returned_state[card_out.response_number].appname, (char*) etatout.returned_state[0].appname);
      card_out.returned_state[card_out.response_number].no_appli = noappli;
      card_out.returned_state[card_out.response_number].cardappnumber = 1;
      card_out.returned_state[card_out.response_number].cardapp[0].priority = 30;
      strcpy(card_out.returned_state[card_out.response_number].cardapp[0].cardappname, (char*) etatout.returned_state[0].appname);
      card_out.response_number++;

#ifdef _USE_UCM_
         	if(UCM_Present)
         	{
                  if (iIsProtocolUCMC() == 0)
                  {
      			ul_InputAmount = gulPaymentAmount;
                  }
                  else
                  {
			      ul_InputAmount = param_in->amount;
                  }
            }
#endif
//}

	memcpy (param_out,&card_out, sizeof(card_out));
	return (FCT_OK);
}

//===========================================================================
//! \brief This function allows to define the custom working environnement.
//! TYP_EXPORT in this case.
//! \param[in] no : application number.
//! \param[in] p1 : not used.
//! \param[out] param_out : structure S_INITPARAMOUT containing the fields mask 
//! (mask of usefull parameters), and application_type.
//! \return Always FCT_OK.
//===========================================================================
static int cu_give_your_domain(NO_SEGMENT no, void *p1, S_INITPARAMOUT *param_out)
{
	S_INITPARAMOUT etatout;

	memcpy (&etatout, param_out, sizeof(etatout));
	// Parameter mask to be determined.
	etatout.returned_state[etatout.response_number].mask     = MSK_TOUS_PARAM;
	etatout.returned_state[etatout.response_number].application_type = TYP_EXPORT;
	etatout.response_number++;
	memcpy (param_out, &etatout, sizeof(etatout));
	return (FCT_OK);
}

//===========================================================================
//! \brief This function authorises the manager to delete the custom application.
//! \param[in] noappli : application number.
//! \param[in] param_in : not used.
//! \param[out] param_out : structure S_ETATOUT containing the field response 
//! set to REP_OK. The fields appname, and noappli are also fulfilled.
//! \return Always FCT_OK.
//===========================================================================
static int cu_is_delete (NO_SEGMENT noappli,void *param_in,S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int iRet ;

	memcpy (&etatout, param_out, sizeof(etatout));

	etatout.returned_state[etatout.response_number].state.response = REP_OK ;

	memcpy (param_out, &etatout, sizeof (etatout));
	iRet = cu_is_name (noappli, PT_NULL, param_out);
	return (iRet);
}

//===========================================================================
int cu_fall_back (NO_SEGMENT noappli, ENTRY_TYPE AmountEntry, unsigned long amount)
{
   int iRet;
	int bStateHeader;

	bStateHeader = StateHeader(0);

   iUcmIac_BckColor(1, UCMCDISPLAY_BKL_COLOR_CYAN);
   iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_CYAN);
	/* FT : 2571 swipe */



	/* --------------------------------------------------------------------*/
	/* Display a message asking to swipe the card                          */

	/* --------------------------------------------------------------------*/
	/* Wait for either a time-out, or a card to be swiped                  */
	/* !! 2 testall are necessary (see system documentation)               */




		/* ----------------------------------------------------------------*/
		/* Call the magstripe application, if present                      */
		//!
		//! \todo FALL-BACK implementation :
		//! This piece of code is just a sample of how the EMV
		//! application could communicate with an independent magstripe one
		//! This is not, for sure, the only one possible implementation.
		//! Update this code to fit with your own implementation.
		//!

			// Fill in trans_in structure
			// No initial amount
   iRet = iUnattendedRead_Iso123();


			// Call the service



			// No Magstripe application present, default treatment.



	/* FT : 2571 swipe */

	StateHeader(bStateHeader);
   return iRet;
}

//===========================================================================
//! \brief This function builds the candidate list with TLV tree returned 
//! by the first application selection.
//! \param[in] phInputTLVTree : TLV tree returned by the first application 
//! selection.
//===========================================================================
static void cu_Build_Candidate_List_TlvTree(TLV_TREE_NODE *phInputTLVTree)
{
	int index_AID;
	DataElement Data_Elt;
	TLV_TREE_NODE hTree_ICC, hTree;

	index_AID = 0;

   do
   {
		// search tag TAG_AID_ICC in input TLV tree
		hTree_ICC = TlvTree_Find(*phInputTLVTree, TAG_AID_ICC, index_AID);
		if (hTree_ICC != NULL)
		{
			// get the length
			Data_Elt.length = TlvTree_GetLength(hTree_ICC);
			// get the value
			Data_Elt.ptValue = TlvTree_GetData(hTree_ICC);
			outAIDCandidateList.count++;
			outAIDCandidateList.list[index_AID].cardholder = FALSE;
			outAIDCandidateList.list[index_AID].lengthAID= Data_Elt.length;
			memcpy(outAIDCandidateList.list[index_AID].AIDValue, Data_Elt.ptValue, Data_Elt.length);
			outAIDCandidateList.list[index_AID].PDOL = PT_NULL ;
			outAIDCandidateList.list[index_AID].lengthPDOL= 0;

			// init hTree
			hTree = TlvTree_GetFirstChild(hTree_ICC);
         do
         {
				if (hTree != NULL)
				{
					// get the tag
					Data_Elt.tag = TlvTree_GetTag(hTree);
					// get the length
					Data_Elt.length = TlvTree_GetLength(hTree);
					// get the value
					Data_Elt.ptValue = TlvTree_GetData(hTree);

					switch (Data_Elt.tag)
					{
					case TAG_APPLICATION_LABEL :
						outAIDCandidateList.list[index_AID].lengthApplicationLabel = Data_Elt.length;
						memcpy(outAIDCandidateList.list[index_AID].applicationLabel, Data_Elt.ptValue, Data_Elt.length);
						break;

					case TAG_APPLICATION_PREFFERRED_NAME :
						outAIDCandidateList.list[index_AID].lengthPreferredName = Data_Elt.length;
						memcpy(outAIDCandidateList.list[index_AID].preferredName, Data_Elt.ptValue, Data_Elt.length);
						break;

					case TAG_LANGUAGE_PREFERENCE :
						outAIDCandidateList.list[index_AID].lengthLanguagePreference = Data_Elt.length;
						memcpy(outAIDCandidateList.list[index_AID].languagePreference, Data_Elt.ptValue, Data_Elt.length);
						break;

					case TAG_ISSUER_CODE_TABLE_INDEX :
						if (Data_Elt.ptValue != NULL)
						{
							outAIDCandidateList.list[index_AID].codeTableIndex = *(Data_Elt.ptValue);
						}
						else
						{
							outAIDCandidateList.list[index_AID].codeTableIndex = 0;
						}
						break;

					case TAG_APPLI_PRIOR_IND :
						if (Data_Elt.ptValue != NULL)
						{
							outAIDCandidateList.list[index_AID].priority = (Data_Elt.ptValue[0] & 0x0F);
							outAIDCandidateList.list[index_AID].cardholder = ((Data_Elt.ptValue[0] & 0x80) != 0);
						}
						else
						{
							outAIDCandidateList.list[index_AID].priority = 0;
							outAIDCandidateList.list[index_AID].cardholder = 0;
						}
						break;

					case TAG_AID_ICC :
					case TAG_SERVICE_STATUS_CODE:
					case TAG_CARDHOLDER_CONFIRMATION:
						break;
					}

					// get next node 
					hTree = TlvTree_GetNext(hTree);

				}
			} while (hTree != NULL);            
		}
		index_AID++;
		// j++;
	}while (hTree_ICC != NULL);
}

//===========================================================================
//! \brief This function asks to the cardholder to choose an AID.
//! \param[in] aAIDCandidateList : list of candidate applications.
//! \param[in] CConfimationSupported : if set to 1, indicates that the AID 
//! cardholder confirmation is supported by the terminal.
//! \return TRUE if an AID has been selected.
//===========================================================================
static int Select_AID(AIDCandidateList* aAIDCandidateList, unsigned short CConfimationSupported )
{

	int i,DisplayAidsConfirmation, cr_select;
	byte TAB_FinalSelection[10];

#ifdef _TOOLWARE_
	unsigned long ulFin_ihm   = 0;
	unsigned long ulDebut_ihm = 0;
#endif

	if (aAIDCandidateList->count == 0)
		return KO;

	for (i=0;i<10;i++)
		TAB_FinalSelection[i] = 0;

	DisplayAidsConfirmation=0;
	i=0;

	cu_Short_AID_List(TAB_FinalSelection, aAIDCandidateList);
	/*&BEGIN FT/08/2636/MA  Manage Cardholder Confirmation parameter is value is NO */

	// is there a cardHolder Confirmation in the aAIDCandidateList ? if yes DisplayAidsConfirmation = 1
	while (i < aAIDCandidateList->count && !DisplayAidsConfirmation)
	{
		DisplayAidsConfirmation = ((aAIDCandidateList->list[i].cardholder == 1)&& (CConfimationSupported == 1));
		i++;
	}

	// Cardholder confirmation if many Aids and Option Confirmation supported :
	if (DisplayAidsConfirmation == 0)
	{
		if (( aAIDCandidateList->count >= 2 ) && (CConfimationSupported == 1))
		{
			DisplayAidsConfirmation = 1;
		}
		/*&END FT/08/2636/MA  Manage Cardholder Confirmation parameter is value is NO */
	}

	cr_select = OK;

	if (DisplayAidsConfirmation == 1)
	{
#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulDebut_ihm = get_tick_counter();
		}
#endif
		if ( cu_AS_AffichageCardHolder(TAB_FinalSelection,aAIDCandidateList) != CR_ENTRY_OK)
		{/* CANCEL */
			cr_select = KO;
		}
#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulFin_ihm = get_tick_counter();
			ulMMI_selappli += ulFin_ihm - ulDebut_ihm;
		}
#endif

	}
	else
	{
		if (CConfimationSupported == 1)
		{
			num_aid_selected = TAB_FinalSelection[0];
		}
		else
		{	
			// If Cardholder Confirmation is not required do not run an application that needs to be confirmed
			num_aid_selected = 0xFF;
			i=0;
			while (i < aAIDCandidateList->count && (num_aid_selected == 0xFF))
			{
				if ((aAIDCandidateList->list[TAB_FinalSelection[i]].cardholder == 0))
					num_aid_selected = TAB_FinalSelection[i];
				i++;
			}

			if (num_aid_selected == 0xFF)
				return KO;
		}
	}
	return (cr_select);
}

//===========================================================================
//! \brief This function shorts the AID by decrease priority.
//! \param[out] Tab : 
//! \param[in] aAIDCandidateList : list of candidate applications.
//! \return
//! - NO_SAME_PRIOR = 1 if no AID with the same priority is found in the candidate list.
//! - SAME_PRIOR = 0 if at least two AID with the same priority are found in the candidate list.
//===========================================================================
static int cu_Short_AID_List(byte* Tab, AIDCandidateList* aAIDCandidateList)
{
	int cpt,i,j,cr;
	unsigned char flag;
	cpt=j=0;
	flag = FALSE;
#define NO_SAME_PRIOR	1
#define SAME_PRIOR		0
#define MAX_PRIORITY	15

	cr = NO_SAME_PRIOR;

	for (i=1;i<=MAX_PRIORITY;i++)
	{
		while(j<aAIDCandidateList->count)
		{
			if(aAIDCandidateList->list[j++].priority == i)
			{
				// Only the same highest priority
				if ( (flag == TRUE) &&  ( aAIDCandidateList->list[Tab[0]].priority == aAIDCandidateList->list[j-1].priority))
					cr=SAME_PRIOR;
				Tab[cpt++]=j-1;
				flag = TRUE;
			}

		}
		j=0;
		flag = FALSE;
	}
	return cr;
}

//===========================================================================
//! \brief This function displays the candidate list to the cardholder.
//! \param TAB : table of AID number.
//! \param[in] aAIDCandidateList : list of candidate applications.
//! \return
//! - CR_ENTRY_OK : Successful entry. 
//! \li the field d_entry[0] of entry_buffer contains the index of the selected 
//! item in the list for G_List_Entry. 
//! \li the field d_len of entry_buffer contains the entry length. 
//! \li the field d_entry [50]  of entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised ) 
//! - CR_ENTRY_TIME_OUT : Timeout elapsed 
//! - CR_ENTRY_CANCEL : Entry Cancelled 
//! - CR_ENTRY_VAL : Green key (confirmation) 
//! - CR_ENTRY_FCT : F key pushed (if authorised ) 
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised ) 
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised ) 
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised ) 
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised ) 
//===========================================================================
static int cu_AS_AffichageCardHolder(byte* TAB, AIDCandidateList *aAIDCandidateList)
{
	byte				i, cr;
	int					select;
	unsigned char		codeTableIndex;
	unsigned short		found;
	unsigned short		IndexManaged;
	DataElement			elt;
//	ENTRY_BUFFER		entry_buffer;
	T_CUTERMtermtype	termtype;

#ifdef _USE_UCM_
	byte index;
	unsigned char		Second_line_name[18];
	unsigned char		NoEnd;
	char				ctMessage[200];
	int					iKey;
#endif

//	T_LABEL				Tab[20 + 1] ;
//	unsigned char		number;
//	unsigned char		CrMenu;
	wStructListe		Menu;
	unsigned short		lg_code;
//	unsigned char		msg[100];
//	unsigned char       *pcline2;
	cGuiStructList		MenuWgui;

   char cTemp[100];
   
	sprintf( cTemp, "cu_file_received start");
	trace( 0x6E01, strlen(cTemp), cTemp);

	cr = CR_ENTRY_OK;

	// Reset the selected mark list
	PAR_ResetMarkList();
	
	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// Get data from TLVTree
	found = PAR_ReadParameter(TAG_ADD_TERMINAL_CAPABILITIES, (DataElementExt *)&elt);

	// first item to be displayed
	select = 0 ;

	termtype = CUTERMgetTerminalType ();

	// Get the cardholder language
	CUDB_Get_cardholder_language(&lg_code);
	// Get the manager language
	// lg_code = PSQ_Give_Language();

	// InitDefaut(_ON_,1);
	InitwStructList(&Menu, _ON_, 1);
	
	// init table from const
	InitMSGinfos(&(Menu.Fenetre.titre));
	Menu.Fenetre.titre.message = (unsigned char *) CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_CHOOSE_AN_AID, lg_code);
	MenuWgui.title.message = Menu.Fenetre.titre.message;
	
	// Optional icon not managed
	MenuWgui.full_screen = 1;

	// init table from const
	for (i=0 ; i < aAIDCandidateList->count ; i++ )
	{
		// Check in Additional Terminal Capabilites the bit corresponding to the code table index
		IndexManaged = FALSE;
		codeTableIndex = aAIDCandidateList->list[i].codeTableIndex;
		if ((codeTableIndex >= 1) && (codeTableIndex < 9))
		{
			// check in byte 5
			if (found)
				IndexManaged = ((elt.ptValue [4] & (0x01 << (codeTableIndex - 1))) != 0);
		}
		if ((codeTableIndex == 9) ||
			(codeTableIndex == 10))
		{
			// check in byte 4
			if (found)
				IndexManaged = ((elt.ptValue [3] & (0x01 << (codeTableIndex - 9))) != 0);
		}

		InitMSGinfos(&(Menu.tab[i]));
		InitMSGinfos(&(MenuWgui.tab[i]));
		if ((aAIDCandidateList->list[i].lengthPreferredName != 0) && IndexManaged)
		{
			Menu.tab[i].message = (unsigned char *)aAIDCandidateList->list[i].preferredName;
			MenuWgui.tab[i].message = (unsigned char *)aAIDCandidateList->list[i].preferredName;
		}
		else
		{
			Menu.tab[i].message = (char*) aAIDCandidateList->list[i].applicationLabel;
			MenuWgui.tab[i].message = (char*) aAIDCandidateList->list[i].applicationLabel;
		}
	
		// Optional icon
		MenuWgui.Icon[i].file_directory = (char *)file_dir;
		MenuWgui.Icon[i].name_icon = " ";
		// CUWGUI_load_icon(STD_MESS_UNDEFINED, &MenuWgui.Icon[i].name_icon);

	}
#ifdef _USE_UCM_
	if(UCM_Present)
	{
		index=0;
		NoEnd=0;

		iLIBUCM_Display_Open(UCMC_DISPLAY, "w");
		iLIBUCM_Pinpad_Open(UCMC_PPAD, "r*");

		if (aAIDCandidateList->count == 1)
		{
			sprintf(ctMessage, "%.16s\n%s",Menu.tab[index].message, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_YESV_NOA, lg_code));

			iLIBUCM_Display_Message( UCMC_DISPLAY, ctMessage,0) ;

			do
			{
				iKey = iLIBUCM_Pinpad_GetChar( UCMC_PPAD );
			}
			while( (iKey!=T_ANN) && (iKey!=T_VAL) );

			if (iKey==T_VAL)
			{
				num_aid_selected = 0;
			}
		}
		else
		{
			memclr( &Second_line_name[0] , sizeof(Second_line_name) );
			strcpy((char *)Second_line_name,"OK(V)   AUTRE(C)");

			do
			{
				sprintf(ctMessage, "%.16s\n%.16s",Menu.tab[index].message, Second_line_name);

				iLIBUCM_Display_Message( UCMC_DISPLAY, ctMessage,0);

				switch( iLIBUCM_Pinpad_GetChar( UCMC_PPAD ) )
				{
				case T_VAL:
					num_aid_selected = index;
					NoEnd = 1;
					break;

				case T_CORR:
					index++;
					if (index==aAIDCandidateList->count)
					{
						index=0;
					}
					break;

				case T_ANN:
					NoEnd = 2;
					break;

				default:
					break;
				}

			}
			while(NoEnd==0);
		}

		iLIBUCM_Display_Close(UCMC_DISPLAY);
		iLIBUCM_Pinpad_Close(UCMC_PPAD);

		return (CR_ENTRY_OK);
	}
	else
#endif
	{
		cr = CR_ENTRY_OK;

	}
	return cr;
}

/*&BEGIN FT/08/2636/MA  Manage Cardholder Confirmation parameter is value is NO */
//===========================================================================
//! \brief This function tests if the cardholder confirmation is possible.
//! \param[in] aAIDCandidateList : list of candidate applications.
//! \return
//! - OK
//! - KO
//===========================================================================
static int Cardholder_Conf_Possible(AIDCandidateList* aAIDCandidateList)
{
	/* 	To ensure that if only one AID is mutually supported, b8 of Application
	priority indicator equals 1, and terminal does not provide for cardholder
	confirmation, the terminal terminates the transaction. */


	if ((aAIDCandidateList->count == 1)&&(aAIDCandidateList->list[0].cardholder == 1))
		return KO;

	return OK;
}
/*&END FT/08/2636/MA  Manage Cardholder Confirmation parameter is value is NO */


//===========================================================================
//! \brief This function tests if the terminal allows AID confirmation by the
//! cardholder.
//! \return
//! - FALSE if the TAG_CUST_IS_CARDHOLDER_CONFIRMATION value is not set.
//! - TRUE otherwise.
//===========================================================================
static int Is_Cardholder_Confirmation_Supported (void)
{
	int found;
	DataElement elt;

	// Reset the selected mark list
	PAR_ResetMarkList();
	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// Get data from TLVTree
	found = PAR_ReadParameter(TAG_CUST_IS_CARDHOLDER_CONFIRMATION, (DataElementExt *)&elt);

	// Search the database number associated with this AID
	if (found)
	{
		if  (elt.ptValue[0]==0x01) 
			return TRUE;
		else
			return FALSE;
	}
	return TRUE;
}

//===========================================================================
//! \brief This function allows to select one AID in the candidate list.
//! \param[in] noappli : application number.
//! \param[in] param_in : input DEL containing a list of AID.
//! \param[out] param_out : structure S_AID_OUT containing the fields aid_value,
//! noappli.
//! \return
//! - OK if an AID was successfully selected.
//! - KO otherwise.
//===========================================================================
static int cu_select_aid_extended(NO_SEGMENT noappli,S_SELECT_AID_EXTENDED *param_in,S_AID_OUT *param_out)
{
	int             cr_int;
	int             i,found_aid;
	unsigned short  lg_code;
	char *			pc_l_DisplayTxt;
	unsigned short	iIsCCSupported;
	TLV_TREE_NODE   hTree;
	int bStateHeader;

   char cTemp[100];
   
	sprintf( cTemp, "cu_select_aid_extended start");
	trace( 0x6E01, strlen(cTemp), cTemp);


	memclr(&outAIDCandidateList, sizeof(outAIDCandidateList));

	// Copy the filled local _DEL_ object into a local TLV Tree object
	CreateCandidateListTlvTreefromDel((_DEL_ * )&param_in->del, &hTree);

	cu_Build_Candidate_List_TlvTree(&hTree);

	// Release the local TlvTree
	TlvTree_ReleaseEx(&hTree);

	iIsCCSupported = (Is_Cardholder_Confirmation_Supported() == TRUE);

	if (!iIsCCSupported)
	{
		if (Cardholder_Conf_Possible(&outAIDCandidateList)==KO) 
		{
			param_out->aid_value= (unsigned char)-1;
			param_out->noappli =noappli;

			return KO ;
		}
	}

	if (iIsCCSupported)
	{
		if (outAIDCandidateList.count != 0)
		{
#ifdef _USE_UCM_
			if(!UCM_Present)
#endif
			{
				if (nb_time_select != 0)
				{ 
					// display message TRY AGAIN for Aids reselection
					CUDB_Get_cardholder_language (&lg_code);
					pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_TRY_AGAIN, lg_code);
					CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
					CUTERMsleep (1500);
				}
			}
		}
	}

	// Performs the choose of an AID
	bStateHeader = StateHeader(0);
	cr_int = Select_AID(&outAIDCandidateList,iIsCCSupported);
	StateHeader(bStateHeader);
	if (cr_int==OK)
	{
		param_out->aid_value= 0;
		found_aid = FALSE;
           i = 0;

		while ((i<NB_MAX_AID_PER_APPLI)&&(found_aid == FALSE))
		{
         if ((param_in->elt[i].lg_libelle == outAIDCandidateList.list[num_aid_selected].lengthAID)
            && (memcmp(param_in->elt[i].aid, outAIDCandidateList.list[num_aid_selected].AIDValue, outAIDCandidateList.list[num_aid_selected].lengthAID) == 0))
				found_aid = TRUE;
			else
				i++;
		}

		param_out->aid_value= i;
	}
	else
	{
		param_out->aid_value= (unsigned char)-1;
		param_out->noappli =noappli;
		return KO ;
	}

	nb_time_select = nb_time_select +1;

	param_out->noappli =noappli;

	return OK ;

}

//===========================================================================
//! \brief This function allows the user to choose an AID.
//! \param[in] phInputTLVTree : input TLV tree containing a list of AID.
//! \param[out] phOutputTLVTree : output TLV tree containing the tag according to 
//! the user choice.
//===========================================================================
static void EMVCUST_Menu_Select_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	int cr_int;
	unsigned short	iIsCCSupported;
	unsigned char StatusCode[2];

	memclr(&outAIDCandidateList, sizeof(outAIDCandidateList));

	cu_Build_Candidate_List_TlvTree(phInputTLVTree);

	if (outAIDCandidateList.count != 0)
	{
		num_aid_selected = 0xff;

		iIsCCSupported = (Is_Cardholder_Confirmation_Supported() == TRUE);

		cr_int = Select_AID(&outAIDCandidateList,iIsCCSupported);
		if ( num_aid_selected != 0xff)
		{
			// Build an output TLV tree
			TlvTree_AddChild(*phOutputTLVTree, TAG_AID_ICC, (unsigned char *)&outAIDCandidateList.list[num_aid_selected].AIDValue, outAIDCandidateList.list[num_aid_selected].lengthAID);

			// Add tag status code
			ShortToChar(TAG_CUST_PROCESS_COMPLETED, StatusCode);
			TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);
		}
		else
		{
			// Build an output TLV tree

			// Add tag status code
			ShortToChar(TAG_CUST_TRANSACTION_CANCELLED, StatusCode);
			TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);

		}

	}

}

//===========================================================================
//! \brief This function allows to select one AID in the candidate list given,
//! as input parameter.
//! \param[in] no : application number.
//! \param[in] param_in : structure S_SELECT_AID containing the candidate list
//! \param[out] param_out : structure S_AID_OUT containing the fields aid_value,
//! noappli.
//! \return 
//! - KO if cardholder confirmation is not supported by the terminal. 
//! - FCT_OK otherwise.
//===========================================================================
static int cu_select_aid(NO_SEGMENT no,S_SELECT_AID *param_in,S_AID_OUT *param_out)
{
	S_AID_OUT		paramout;
//	unsigned short	lg_code;
//	char			*pc_l_DisplayTxt;
//	unsigned short	mask;
//	byte			b_l_TimeOut;
//	T_CUTERMkey		key;
	unsigned short	iIsCCSupported;


#ifdef _USE_UCM_
	byte			index;
	unsigned char	NoEnd;
	char			ctMessage[200];
	int				UCMKey;
#endif
//	char			msg[100];
//	unsigned char	*pcline2;
//	wStructListe	Menu;
//	ENTRY_BUFFER	entry_buffer;
//	unsigned char	cr_entry;
//	cGuiStructList	MenuWgui;
//	int				ind;
	int bStateHeader;

   memclr(&paramout, sizeof(paramout));
   
   char cTemp[100];
   
	sprintf( cTemp, "cu_select_aid start");
	trace( 0x6E01, strlen(cTemp), cTemp);

	iIsCCSupported = (Is_Cardholder_Confirmation_Supported() == TRUE);

	if (!iIsCCSupported)
	{
		param_out->aid_value= (unsigned char)-1;
		param_out->noappli =no;
		return KO ;
	}

	paramout.noappli = no;
	if (param_in->nb_appli==1)
	{

		/* &BEGIN FT/07/1755/MA confirmation AID for UCM */
		bStateHeader = StateHeader(0);

#ifdef _USE_UCM_
		if(UCM_Present)
		{
			unsigned short lg_code;

			index=0;
			NoEnd=0;
			paramout.aid_value = 1;

			iLIBUCM_Display_Open(UCMC_DISPLAY, "w");
			iLIBUCM_Pinpad_Open(UCMC_PPAD, "r*");

			lg_code = PSQ_Give_Language();
			sprintf(ctMessage, "%.16s\n%s",param_in->AID_list[0], CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_YESV_NOA, lg_code));
			iLIBUCM_Display_Message( UCMC_DISPLAY, ctMessage,0) ;

			do
			{
				UCMKey = iLIBUCM_Pinpad_GetChar( UCMC_PPAD );
         } while ((UCMKey != T_ANN) && (UCMKey != T_VAL));

			if (UCMKey==T_VAL)
			{
				paramout.aid_value = 0;
			}

			iLIBUCM_Display_Close(UCMC_DISPLAY);
			iLIBUCM_Pinpad_Close(UCMC_PPAD);
		}
		else
#endif
		{

		}

		StateHeader(bStateHeader);
	}

	param_out->noappli = no;
	param_out->aid_value = paramout.aid_value;

	return (FCT_OK);
}

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	unsigned long m_ulAmount;
	int m_nCurrencyCode;
} T_PERFORM_PAYMENT;

//===========================================================================
//! \brief This function starts an EMV transaction. This function is called
//! on the engine entry point I_EMVCUST_Perform_Transaction.
//! \param[in] size : size of the data received from engine.
//! \param[in] pPaymentData : T_PERFORM_PAYMENT structure contraining the
//! amount and the currency code to perform the transaction.
//! \return Always FCT_OK.
//===========================================================================
int PerformPayment(unsigned int size, T_PERFORM_PAYMENT* pPaymentData)
{
	CUMORE_DebitEx(pPaymentData->m_ulAmount, pPaymentData->m_nCurrencyCode);
	return FCT_OK;
}

//===========================================================================
//! \brief This function allows to customise the Telium Manager at idle state.
//! It is used to enable usage of CAM2 (CAM2 is the terminal chip reader when
//! a pinpad is connected).
//! \param[in] no : application number.
//! \param[in] p1 : NULL.
//! \param[out] param_out : structure S_STATEOUT containing the fields CAM mask.
//! \return Always FCT_OK.
//===========================================================================
/*& BEGIN FT/08/3144/MA  CAM2 Management*/
int cu_get_idle_state_parameter(NO_SEGMENT no, void *p1,   S_STATEOUT *param_out)
{
	S_STATEOUT        etatout;

	memcpy ((char *)&etatout, (char *)param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].no_appli = no;

#ifdef _ENABLE_CAM2_
	etatout.returned_state[etatout.response_number].mask     = CAM0 | CAM2 | SWIPE2;
#else
	etatout.returned_state[etatout.response_number].mask     = CAM0 | SWIPE2;
#endif

	etatout.returned_state[etatout.response_number].key      = 0;
	etatout.response_number++;
	memcpy (param_out, &etatout, sizeof(etatout));
	return (FCT_OK);
}
/*& END FT/08/3144/MA  CAM2 Management*/

//===========================================================================
//! \brief This function allows to customise the Telium Manager after entering an amount.
//! It is used to enable usage of CAM2 (CAM2 is the terminal chip reader when
//! a pinpad is connected).
//! \param[in] no : application number.
//! \param[in] param_in : structure S_TRANSIN.
//! \param[out] param_out : structure S_STATEOUT containing the fields CAM mask.
//! \return Always FCT_OK.
//===========================================================================
/*& BEGIN FT/08/3144/MA  CAM2 Management*/
int cu_get_amount_state_parameter(NO_SEGMENT no, S_TRANSIN *param_in,   S_STATEOUT *param_out)
{
	S_STATEOUT        etatout;

	memcpy ((char *)&etatout, (char *)param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].no_appli = no;

#ifdef _ENABLE_CAM2_
	etatout.returned_state[etatout.response_number].mask     = CAM0 | CAM2 | SWIPE2;
#else
	etatout.returned_state[etatout.response_number].mask     = CAM0 | SWIPE2;
#endif

	etatout.returned_state[etatout.response_number].key      = 0;
	etatout.response_number++;
	memcpy (param_out, &etatout, sizeof(etatout));
	return (FCT_OK);
}
/*& END FT/08/3144/MA  CAM2 Management*/

int cu_give_your_specific_context(NO_SEGMENT No, S_SPECIFIC_CONTEXT *param_out)
{
	// Initialise the output parameter
   memset(&param_out->returned_state[param_out->response_number], 0, sizeof(param_out->returned_state[param_out->response_number]));

	// The name of the resource file
	strcpy(param_out->returned_state[param_out->response_number].appname, "844042----");
	param_out->returned_state[param_out->response_number].no_appli = No;
	param_out->returned_state[param_out->response_number].mask = 0;
	param_out->returned_state[param_out->response_number].type = 0;
	param_out->returned_state[param_out->response_number].support = 0;
	param_out->returned_state[param_out->response_number].cam = 0;


     #ifdef _USE_UCM_ 
   		param_out->returned_state[param_out->response_number].cgui = 0;   
     #else
   	      // The application is CGUI compliant
      	param_out->returned_state[param_out->response_number].cgui = CGUI_MASK;
     #endif
	param_out->response_number++;


	return FCT_OK;
}

//===========================================================================
//! \brief This is the main function. This function treats the manager entry 
//! points managed by the custom application.
//! \param[in] size : size of the exchanged data.
//! \param[in,out] data : input/output structure used for exchange between 
//! manager and custom.
//! \return 0.
//===========================================================================
int Main(unsigned int size, StructPt *data)
{
	NO_SEGMENT No;
#ifdef _USE_SPED_
	int cr_Sped_MSREnable;
	FILE *swipe2;
#endif

	No=ApplicationGetCurrent();

	switch(data->service)
	{
	case AFTER_RESET :
		cu_after_reset((unsigned char)No, NULL, &data->Param.AfterReset.param_out);
		EMVCUST_Initialise_TlvTree(NULL);
		break;

	case CONSULT :
		cu_consult((unsigned char)No, NULL, NULL);
		break;

	case STATE :
		cu_state((unsigned char)No, NULL, NULL);
		break;

	case IS_CHANGE_INIT :
		cu_is_change_init((unsigned char)No, NULL, &data->Param.IsChangeInit.param_out);
		break;

	case IS_EVOL_PG :
		cu_is_evol_pg((unsigned char)No, NULL, &data->Param.IsEvolPg.param_out);
		break;

	case IS_STATE :
		cu_is_state((unsigned char)No, NULL, &data->Param.IsState.param_out);
		break;

	case IS_TIME_FUNCTION :
		is_time_function((unsigned char)No, NULL, &data->Param.IsTimeFunction.param_out);
		break;

	case MCALL :
		cu_mcall((unsigned char)No, NULL, NULL);
		break;

	case MODIF_PARAM :
		cu_modif_param((unsigned char)No, &data->Param.ModifParam.param_in, NULL);
		break;

	case IS_FOR_YOU_BEFORE :
		cu_is_for_you_before((unsigned char)No, NULL, &data->Param.IsForYouBefore.param_out);
		break;

	case DEBIT_NON_EMV :
		cu_debit_non_emv((unsigned char)No, &data->Param.DebitNonEmv.param_in, &data->Param.DebitNonEmv.param_out);
		break;

	case FILE_RECEIVED :
        return (cu_file_received((unsigned char)No, &data->Param.FileReceived.param_in, NULL));
		break;

	case GIVE_YOUR_DOMAIN :
		cu_give_your_domain((unsigned char)No, NULL, &data->Param.GiveYourType.param_out);
		break;

	case IS_FOR_YOU_AFTER :
		cu_is_for_you_after((unsigned char)No, &data->Param.IsForYouAfter.param_in, &data->Param.IsForYouAfter.param_out);
		break;

	case IS_DELETE :
		cu_is_delete((unsigned char)No,NULL, NULL);
		break;

	case FALL_BACK :
#ifdef _USE_UCM_ /* Forbidden expect with ucmxZxx parameters */
         if (!UCM_Present)
			cu_fall_back((unsigned char)No, data->Param.FallBack.param_in.entry, data->Param.FallBack.param_in.amount);
#endif
		break;

	case SELECT_AID_EXTENDED :
		cu_select_aid_extended((unsigned char)No,&data->Param.SelectAidExtended.param_in,&data->Param.SelectAidExtended.param_out);
		break;

	case SELECT_AID :
		cu_select_aid((unsigned char)No,&data->Param.SelectAid.param_in,&data->Param.SelectAid.param_out);
		break;

	case TRACK_STREAM :
#ifdef _USE_SPED_

		/* FT : 2571 swipe */
		swipe2 = fopen("SWIPE2","r*");
		if (swipe2 != NULL)
		{
			cr_Sped_MSREnable = Sped_MSREnable (1);
			fclose (swipe2);
		}
#endif
		upload_diagnostic_txt((unsigned char *)"track_stream \n");

		break;

	/*&BEGIN FT/09/4316/MA  Multi EMV Application*/
    case IDLE_MESSAGE:
		cu_idle_message((unsigned char)No, NULL, NULL);  
		break;

    case TIME_FUNCTION :
		cu_time_function((unsigned char)No, NULL, NULL); 
		break;

    case GIVE_AID :
		cu_give_aid((unsigned char)No,NULL,&data->Param.GiveAid.param_out);
		break;

    case IS_CARD_EMV_FOR_YOU:
		cu_is_card_emv_for_you((unsigned char)No, &data->Param.IsCardEmvForYou.param_in,&data->Param.IsCardEmvForYou.param_out) ;
		break;

	case MORE_FUNCTION :
      #ifdef _USE_UCM_ 
   		cu_more_function_UCM((unsigned char)No, NULL, NULL);      
      #else
   		cu_more_function((unsigned char)No, NULL, NULL);      
      #endif
		break;

	case KEYBOARD_EVENT :
         cu_keyboard_event((unsigned char) No, &data->Param.KeyboardEvent.param_in, &data->Param.KeyboardEvent.param_out);
         ;
		break;

	case DEBIT_EMV :
		cu_debit_emv((unsigned char)No,&data->Param.DebitEmv.param_in,&data->Param.DebitEmv.param_out); 
		break;

    case IS_NAME :
        cu_is_name((unsigned char)No,NULL, &data->Param.IsName.param_out);
		break;
	/*&END FT/09/4316/MA  Multi EMV Application*/

	case GET_IDLE_STATE_PARAMETER :
		cu_get_idle_state_parameter((unsigned char)No,NULL,&data->Param.GetIdleStateParameter.param_out);
		break;                                                           

	case GET_AMOUNT_STATE_PARAMETER :
         cu_get_amount_state_parameter((unsigned char) No, &data->Param.GetAmountStateParameter.param_in, &data->Param.GetAmountStateParameter.param_out);
		break;                                                           

	case GIVE_YOUR_SPECIFIC_CONTEXT:
		cu_give_your_specific_context((unsigned char)No,&data->Param.GiveYourSpecificContext.param_out);
		break;                                                           
	}

	return (0);
}


#ifdef _USE_UCM_


/* Not USED IUN */
static int idle_message_UCMC(NO_SEGMENT AppliNum, char *pMessage_p)
{
char cTemp[200];

    sprintf( cTemp, "idle_message_UCMC start");
    trace( 0x6E01, strlen(cTemp), cTemp);

//    if( giDisplay > 0 )
//        iLIBUCM_Display_Message(giDisplay, "Sample\nInsert your\nCard", 0);

    if( pMessage_p[0] == 0 )
    {
        iGraphic_message( "Sample\nInsert your\nCard", 0 );
    }
    else
    {
        iGraphic_message( pMessage_p, 0 );
    }

   if ((giDisplayType == PARAM_TYPE_IUC180) || (giDisplayType == PARAM_TYPE_IUP250))
   {
      iUcmIac_BckColor(0, UCMCDISPLAY_BKL_COLOR_WHITE); 
   }

	return (FCT_OK);
}

//===========================================================================
//! \brief 
//! \param pdata_p
//! \return
//===========================================================================
static int iAPP_Consult( T_UCMC_IAC_SERVICE *pdata_p )
{
	T_UCMHOST_APP_CONSULT *pConsult;


	pdata_p->uiSize = sizeof( T_UCMHOST_APP_CONSULT );

	pConsult = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pConsult->sInfo );

	// State of the application
	pConsult->ucAppStatus = UCMHOST_APP_STATUS_INIT_ACTIVE;

	// State of the file
	pConsult->ucFileStatus = UCMHOST_APP_FILE_NOT_EMPTY;

	return( FCT_OK );
}

//===========================================================================
//! \brief 
//! \param pdata_p
//! \return
//===========================================================================
static int iAPP_TLC_Status( T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet;
T_UCMHOST_APP_TLC_STATE *pState;

	iRet = FCT_OK;
	
	pdata_p->uiSize = sizeof( T_UCMHOST_APP_TLC_STATE );

	pState = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo( OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pState->sInfo );
	
	pState->ucState = UCMHOST_TLC_STATE_OK;
	pState->ucTypeCardStruct = UCMHOST_CARD_EMV;

	memset( &pState->u.sAccept.ucEnteteTicket[0], 'T', 50 );
	memcpy( &pState->u.sAccept.sDate, "060320102030", 12 );
	memcpy( &pState->u.sAccept.ucNoContrat[0], "1234567", 7);
	memcpy( &pState->u.sAccept.ucNoSiret[0], "01234567891234", 14);
	memcpy( &pState->u.sAccept.ucTypeActivite[0], "ACTI", 4);
	memcpy( &pState->u.sAccept.ucTypePaiement[0], "TP", 2);
	memcpy( &pState->u.sAccept.ucTypeSite[0], "TYPESITE", 8);
	memcpy( &pState->u.sAccept.ucNoSA[0], "NSA", 3);
	memset( &pState->u.sAccept.ucReponse[0], 'R', 32 );
	memset( &pState->u.sAccept.ucPiedTicket[0], 'P', 50 );


	pState->ucNbTrs = 3 ;
	pState->ucRuf2= 0;

	/* DERNIERE REMISE */
	pState->uTrs.sCB[0].iNoSequenceAcq = 1;
	pState->uTrs.sCB[0].iNoRemise = 1;
	pState->uTrs.sCB[0].iNoTransac = 3;
	pState->uTrs.sCB[0].iNoTNA = 4;
	pState->uTrs.sCB[0].tCurrency.code[0] = '9';
	pState->uTrs.sCB[0].tCurrency.code[1] = '7';
	pState->uTrs.sCB[0].tCurrency.code[2] = '8';
	pState->uTrs.sCB[0].tCurrency.nom[0] = 'E';
	pState->uTrs.sCB[0].tCurrency.nom[1] = 'U';
	pState->uTrs.sCB[0].tCurrency.nom[2] = 'R';
	pState->uTrs.sCB[0].tCurrency.posdec = 2;
	pState->uTrs.sCB[0].ulAmount = 123456;

	pState->uTrs.sCB[1].iNoSequenceAcq = 1;
	pState->uTrs.sCB[1].iNoRemise = 2;
	pState->uTrs.sCB[1].iNoTransac = 5;
	pState->uTrs.sCB[1].iNoTNA = 6;
	pState->uTrs.sCB[1].tCurrency.code[0] = '9';
	pState->uTrs.sCB[1].tCurrency.code[1] = '7';
	pState->uTrs.sCB[1].tCurrency.code[2] = '8';
	pState->uTrs.sCB[1].tCurrency.nom[0] = 'E';
	pState->uTrs.sCB[1].tCurrency.nom[1] = 'U';
	pState->uTrs.sCB[1].tCurrency.nom[2] = 'R';
	pState->uTrs.sCB[1].tCurrency.posdec = 2;
	pState->uTrs.sCB[1].ulAmount = 123457;

	pState->uTrs.sCB[2].iNoSequenceAcq = 1;
	pState->uTrs.sCB[2].iNoRemise = 3;
	pState->uTrs.sCB[2].iNoTransac = 7;
	pState->uTrs.sCB[2].iNoTNA = 8;
	pState->uTrs.sCB[2].tCurrency.code[0] = '9';
	pState->uTrs.sCB[2].tCurrency.code[1] = '7';
	pState->uTrs.sCB[2].tCurrency.code[2] = '8';
	pState->uTrs.sCB[2].tCurrency.nom[0] = 'E';
	pState->uTrs.sCB[2].tCurrency.nom[1] = 'U';
	pState->uTrs.sCB[2].tCurrency.nom[2] = 'R';
	pState->uTrs.sCB[2].tCurrency.posdec = 2;
	pState->uTrs.sCB[2].ulAmount = 123458;

   return( iRet );
}

//===========================================================================
//! \brief 
//! \param pdata_p
//! \return
//===========================================================================
static int iAPP_TLP_Status( T_UCMC_IAC_SERVICE *pdata_p )
{
	int iRet;
	T_UCMHOST_APP_TLP_STATE *pState;

	iRet = FCT_OK;
	
	pdata_p->uiSize = sizeof( T_UCMHOST_APP_TLP_STATE );

	pState = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo( OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pState->sInfo );
	
	pState->ucState = UCMHOST_TLC_STATE_OK;
	pState->ucRuf = 0;

	memset( &pState->u.sAccept.ucEnteteTicket[0], 'T', 50 );
	memcpy( &pState->u.sAccept.sDate, "060320102030", 12 );
	memcpy( &pState->u.sAccept.ucNoContrat[0], "1234567", 7);
	memcpy( &pState->u.sAccept.ucNoSiret[0], "01234567891234", 14);
	memcpy( &pState->u.sAccept.ucTypeActivite[0], "ACTI", 4);
	memcpy( &pState->u.sAccept.ucTypePaiement[0], "TP", 2);
	memcpy( &pState->u.sAccept.ucTypeSite[0], "TYPESITE", 8);
	memcpy( &pState->u.sAccept.ucNoSA[0], "NSA", 3);
	memset( &pState->u.sAccept.ucReponse[0], 'R', 32 );
	memset( &pState->u.sAccept.ucPiedTicket[0], 'P', 50 );

	
	pState->ucAppInit = 1;	/* Not initialized = 0  Initialized = 1 */
	pState->ucAppActive = 1; /* Not active = 0     Active = 1 */
	
	sprintf( (char *)&pState->ucTLCError[ 4 ], "%s", "NSA");/* Telecollecte */
	sprintf( (char *)&pState->ucTLCErrorTable[ 2 ], "%s", "NSA");/* Table */
	sprintf( (char *)&pState->ucTLCErrorCnct[ 2 ], "%s", "NSA");/* Connection */
		
	pState->ucNbTable = 3 ;
	pState->ucRuf2= 0;
	pState->ucRuf3= 0;

	/* DERNIERE REMISE */
	pState->uTable.stab[0].uiNo = 97;
	pState->uTable.stab[0].uiVersion = 1234;

	pState->uTable.stab[1].uiNo = 98;
	pState->uTable.stab[1].uiVersion = 5678;

	pState->uTable.stab[2].uiNo = 99;
	pState->uTable.stab[2].uiVersion = 6789;

   return( iRet );
}

//===========================================================================
//! \brief 
//! \param pdata_p
//! \return
//===========================================================================
static int iAPP_TLC_Start( T_UCMC_IAC_SERVICE *pdata_p )
{
	int iRet;
	T_UCMHOST_APP_TLC_START *pState;


	iRet = FCT_OK;

	pdata_p->uiSize = sizeof( T_UCMHOST_APP_TLC_START );
	pState = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo( OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pState->sInfo );

	CUMORE_BatchCapt();

	pState->ucState = UCMHOST_TLC_STATE_OK;
	pState->ucRuf = 0;

	return(FCT_OK);
}

 int iAPP_Event( T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet;
T_UCMC_IAC_EVENT       *pEvent;
char cTemp[ 200 ];

 iRet = FCT_OK;
 
 pEvent = (void*)&pdata_p->Par.ucBuffer[0];

 

    switch( pEvent->usType )
   {
      case UCMC_EVENT_TYPE_KEY:   
         sprintf( cTemp, "Sample Event\nKey 0x%x", pEvent->Par.ucKey ) ;

          switch( pEvent->Par.ucKey )  /* UPP keyboard */ 
         {
            case 0x17: /*  red key  */
            break;
            case 0x18: /*  yellow key */
               Buzzer_Test();
            break;
            case 0x16: /*  green key */
           break;

         }
      break;

      case UCMC_EVENT_TYPE_LLT_BT:
         sprintf( cTemp, "Sample Event\nLLT BT") ;
      break;
     
      case UCMC_EVENT_TYPE_USB:
         sprintf( cTemp, "Sample Event\nUsb") ;
      break;

      default:
         sprintf( cTemp, "Sample Event\n?? 0x%x", pEvent->usType ) ;
      break;
   }

 

   trace( 0x0E01, strlen( cTemp), cTemp );
   iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 100 ) ;

   return( iRet );
}

//===========================================================================
//! \brief 
//! \param usAppli_p
//! \param pdata_p
//! \return
//===========================================================================
int iAPPLIUCM_IAC( unsigned short usAppli_p , T_UCMC_IAC_SERVICE *pdata_p )
{
	int iRet;
	unsigned char ucTemp[ 50 ];

	iRet = FCT_OK;
	
	switch( pdata_p->usFct )
	{
		case UCMHOST_FCTAPP_CONSULT:
			sprintf((char *)ucTemp, "Sample UCMHOST_FCTAPP_CONSULT") ;
         iLIBUCM_Display_Message( UCMC_DISPLAY, (char *)ucTemp, 10 ) ;
			iRet = iAPP_Consult( pdata_p );
				
		break;
		
		case UCMHOST_FCTAPP_TLP_STATUS:
			sprintf((char *)ucTemp, "Sample UCMHOST_FCTAPP_TLP_STATUS") ;
         iLIBUCM_Display_Message( UCMC_DISPLAY, (char *)ucTemp, 10 ) ;
			iRet = iAPP_TLP_Status( pdata_p ) ;

		break;
		
		case UCMHOST_FCTAPP_TLC_STATUS:
			sprintf((char *)ucTemp, "Sample UCMHOST_FCTAPP_TLC_STATUS") ;
			iLIBUCM_Display_Message( UCMC_DISPLAY, (char *)ucTemp, 10 ) ;
			
			iRet = iAPP_TLC_Status( pdata_p ) ;
			
		break;

		case UCMHOST_FCTAPP_TLC_START:
			sprintf((char *)ucTemp, "Sample UCMHOST_FCTAPP_TLC_START") ;
			iLIBUCM_Display_Message( UCMC_DISPLAY, (char *)ucTemp, 10 ) ;
			
			iRet = iAPP_TLC_Start( pdata_p ) ;
		break;

		case UCMHOST_FCTAPP_EVENT:
             iRet = iAPP_Event( pdata_p  ) ;
          break;

		case UCMHOST_FCTAPP_IDLE_EVENT:
	   	  idle_message_UCMC((NO_SEGMENT)ApplicationGetCurrent(), (char *)&pdata_p->Par.sDisplay.cBuf[0]);
	   	  break;

		default:
			iRet = UCMERR_IAC_NO_FCT;
			
			sprintf( (char *)ucTemp, "Sample UCMC IAC TL No Fct %04X %d\n", pdata_p->usFct, iRet );
			upload_diagnostic_txt( ucTemp ) ;
		break;
	}
	return( iRet ) ;
}

int MainUCMC_IAC(unsigned int iSize_p, T_UCMC_IAC_SERVICE *pdata_p)
{
	int          iRet;
	object_info_t info;


	ObjectGetInfo( OBJECT_TYPE_APPLI, pdata_p->usType_code, &info ) ;

	iRet = FCT_OK;

	switch( pdata_p->usService )
	{
	case SERVICE_APPLI_UCMC:
		switch( pdata_p->usModule )
		{
		case UCMAPPLIMODULE_FCTAPP:
			iRet = iAPPLIUCM_IAC( pdata_p->usType_code, pdata_p ) ;
			break;

		default:
			iRet = UCMERR_IAC_NO_MODULE;
			break;
		}
		break;

	default:
		iRet = UCMERR_IAC_NO_SERVICE;
		break;
	}

	return( iRet );
}
#endif

//===========================================================================
//! \brief This function defines the services managed by the application.
//! \param[in] no : application type.
//! \param p1 : not used.
//! \param p2 : not used.
//! \return Always FCT_OK.
//===========================================================================
int give_interface(unsigned short no,void *p1,void *p2)
{
	/*& BEGIN SMO/ETU/04/20286/MA : Do not use pinpad(PPC30 and PPR30) as secret area key storage */
	service_desc_t MesServices[60];
	int i;
	
	memset(g_szAppName, 0, sizeof(g_szAppName));

	// DLL INIT IS REQUIRED BEFORE USE.
	SEClib_Open();

	i = 0;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = AFTER_RESET;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30; /* 25 */

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = CONSULT;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = STATE;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_CHANGE_INIT;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_EVOL_PG;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_STATE;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_TIME_FUNCTION;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MCALL;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MODIF_PARAM;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_FOR_YOU_BEFORE;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = DEBIT_NON_EMV;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = FILE_RECEIVED;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = GIVE_YOUR_DOMAIN;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_FOR_YOU_AFTER;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	/*& BEGIN FT/1393/06/MG : Add a service to ENGINE to start an EMV transaction */
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Perform_Transaction;
	MesServices[i].sap       = (SAP) PerformPayment;
	MesServices[i++].priority  = 30;
	/*& END FT/1393/06/MG */

	/* MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Initialise_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;*/

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_Global_Param_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_AID_List_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_AID_DATA_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_AID_Param_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	/* MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_More_Function_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Periodic_Call_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;*/

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Process_Step_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Display_Message_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_Last_Transaction_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Voice_Referral_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	/* MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_AID_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_KeyManagement_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;*/ 

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Authorization_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Choose_Language_Menu_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	// FT/06/473/MA : selection menu to be done in Custom
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Menu_Select_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	// FT/1126/06/MA : Account Type Selection
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Choose_Account_Type_Menu_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	// FT/2543/07/MA : link ICSx.par file to AIDx.par file
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = I_EMVCUST_Get_AID_ICS_TlvTree;
	MesServices[i].sap       = (SAP) Main_EMVCUST_TlvTree;
	MesServices[i++].priority  = 30;

	// SMO/ETU/04/20286/MA : Do not use pinpad(PPC30 and PPR30) as secret area key storage
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_DELETE;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	// SMO/ETU/05/20090/LB
#ifndef _USE_UCM_  /* forbiden expect if UCMxZxx parameters */
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = FALL_BACK;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;
#endif
	// SMO/ETU/05/20383/LB management of select_aid_extended
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = SELECT_AID_EXTENDED;
	MesServices[i].sap       = (SAP)Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = TRACK_STREAM;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	// FT/732/06  management of select_aid for 1 aid confirmation
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = SELECT_AID;
	MesServices[i].sap       = (SAP)Main;
	MesServices[i++].priority  = 30;

#ifdef _USE_UCM_
	MesServices[i].appli_id  = no  ;
	MesServices[i].serv_id   = SERVICE_APPLI_UCMC;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)MainUCMC_IAC;
	MesServices[i++].priority  = 30;
#endif

	/*&BEGIN FT/09/4316/MA  Multi EMV Application*/
#ifdef _USE_UCM_
   /* idle message forbiden */
#else
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IDLE_MESSAGE;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 70;
#endif

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = TIME_FUNCTION;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = GIVE_AID;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   =IS_CARD_EMV_FOR_YOU ;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MORE_FUNCTION;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

#ifdef _USE_UCM_
   /* idle message forbiden */
#else
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   =KEYBOARD_EVENT ;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;
#endif
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   =DEBIT_EMV ;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 30;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   =IS_NAME ;
	MesServices[i].sap       = (SAP) Main;
	MesServices[i++].priority  = 20;
	/*&END FT/09/4316/MA  Multi EMV Application*/

#ifdef _USE_UCM_
   /* idle message forbiden */
#else
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = GET_IDLE_STATE_PARAMETER;
	MesServices[i].sap       = (SAP)Main;
	MesServices[i++].priority  = 30;
#endif

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = GET_AMOUNT_STATE_PARAMETER;
	MesServices[i].sap       = (SAP)Main;
	MesServices[i++].priority  = 30;

	ServiceRegister(i,MesServices);

	return (FCT_OK);
}

//===========================================================================
//! \brief This function is the entry point for the interface with the manager.
//===========================================================================
void entry(void)
{
	object_info_t info;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
	give_interface(info.application_type, NULL, NULL);
}

//! @}



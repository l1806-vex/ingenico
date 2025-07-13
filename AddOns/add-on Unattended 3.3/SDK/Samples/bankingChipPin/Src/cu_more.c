/**
* \file cu_more.c
* \brief This module contains the functions activated by the navigation menus.
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
#include "_emvdctag_.h"
#include "del_lib.h"
#include "def_tag.h"
#include "cu_term.h"
#include "cu_black.h"
#include "MyTlvTree.h"
#include "cu_batch.h"
#include "cu_base.h"
#include "cu_serv.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "cu_more.h"
#include "cu_entry.h"
#include "convert.h"
#include "cu_param.h"
#include "gestion_param.h"
#include "cu_comm.h"
#include "servcomm.h"
#include "servcomm_TlvTree.h"
#include "convert.h"
#include "cu_file.h"
#include "LinkLayer.h"
#include "serveng.h"
#include "cu_disk.h"
#include "EngineInterfaceLib.h"
#include "TlvTreeDel.h"
#include "EngineInterface.h"
#include "cu_trfile.h"
#include "WGUI.h"
#include "cu_wgui.h"

#ifdef _USE_UCM_
#include "ucmtelium.h"
#include "ucmhostdll.h"
#include "ucmclib.h"
#endif

//! \addtogroup Group_cu_more
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define TO_PARAM    120								//!< Time-out for parameter entry

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

static void CUMORE_Cash          (void);
static void CUMORE_CashBack      (void);
static void CUMORE_BatchStat     (void);
static int  CUMORE_BatchCaptRaz  (void);
static void CUMORE_BatchRAZ      (void);
static void CUMORE_Enter_Terminal_ID (void);
static void CUMORE_Reset         (void);
static void CUMORE_Default       (void);
static void CUMORE_Administrative(void);
static void CUMORE_Inquiry       (void);


static void CUMORE_Dump_GParam   (void);
static void CUMORE_Bypass_PIN (void);

static void CUMORE_ForcedOnline  (void);
static void CUMORE_TransactionLog(void);

static int merchant(void);
static int ParamManagement(void);

#ifdef _TOOLWARE_
static void CUMORE_Demo_Mode(void);
#endif /* _TOOLWARE_ */

static void CUMORE_Dump_ICS(void);
static int CUMORE_Send_Financial_Record (TLV_TREE_NODE hInputTree);
static int CUMORE_Send_Advice_Record (TLV_TREE_NODE hInputTree);
static void CUMORE_Dump_AID(void);

/* ========================================================================*/
/* Constant declarations                                                   */
/* ========================================================================*/

const NavigationListe NavigationEmvdc[] =
{
	{CMN_MESS_DEBIT,                    (PFONCNAVI) CUMORE_Debit},
	{CMN_MESS_REFUND,                   (PFONCNAVI) CUMORE_Refund},
	{CMN_MESS_EMV_CASH,                 (PFONCNAVI) CUMORE_Cash},
	{CMN_MESS_EMV_CASHBACK,             (PFONCNAVI) CUMORE_CashBack},
	{CMN_MESS_EMV_ADMINISTRATIVE,       (PFONCNAVI) CUMORE_Administrative},
	{CMN_MESS_EMV_INQUIRY		,       (PFONCNAVI) CUMORE_Inquiry},
	{CMN_MESS_MERCHANT,                 (PFONCNAVI) merchant}
#ifdef _TOOLWARE_
	,{CMN_MESS_MERCHANT_TOOLWARE, (PFONCNAVI) CUMORE_Demo_Mode}
#endif /* _TOOLWARE_ */
};

static const NavigationListe NavigationMerchant[] =
{
	{CMN_MESS_MERCHANT_BYPASSPIN,       (PFONCNAVI) CUMORE_Bypass_PIN},
	{CMN_MESS_MERCHANT_BATCH_STAT,      (PFONCNAVI) CUMORE_BatchStat},
	{CMN_MESS_MERCHANT_RUN_BATCH,       (PFONCNAVI) CUMORE_BatchCaptRaz},
	{CMN_MESS_MERCHANT_PARAM_MNGT,      (PFONCNAVI) ParamManagement},
	{CMN_MESS_MERCHANT_FORCE_ONLINE,    (PFONCNAVI) CUMORE_ForcedOnline},
	{CMN_MESS_MERCHANT_TRANSACTIONLOG,  (PFONCNAVI) CUMORE_TransactionLog}
};

static const NavigationListe NavigationBatchCapt[] =
{
	{CMN_MESS_MERCHANT_RUN_BATCH_RAZ,   (PFONCNAVI) CUMORE_BatchCapt},
	{CMN_MESS_MERCHANT_BATCH_RAZ,       (PFONCNAVI) CUMORE_BatchRAZ}
};

static const NavigationListe NavigationParamMngt[] =
{
	{CMN_MESS_MERCHANT_RESET_ALL,       (PFONCNAVI) CUMORE_Reset},
	{CMN_MESS_MERCHANT_DEFAUT_CONF,     (PFONCNAVI) CUMORE_Default},
	{CMN_MESS_MERCHANT_TERMINAL_ID,		(PFONCNAVI) CUMORE_Enter_Terminal_ID},
	{CMN_MESS_MERCHANT_DUMP_ICS,		(PFONCNAVI) CUMORE_Dump_ICS},
	{CMN_MESS_MERCHANT_DUMP_AID,		(PFONCNAVI) CUMORE_Dump_AID},
	{CMN_MESS_MERCHANT_GLOBAL_PARAM,	(PFONCNAVI) CUMORE_Dump_GParam},
};


const unsigned char CUMORE_TRUE []   = {0x00, 0x01};
const unsigned char CUMORE_FALSE []  = {0x00, 0x00};

// static const TAB_ENTRY_STRING t_term_id={0x0000,TO_PARAM,1,0,1,8,1};


/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

unsigned short Bypass_Required;

unsigned short TransactionForcedOnline;

//extern unsigned char ucMode2000;

unsigned char RetransmitIndicator;

TLV_TREE_NODE CUMORE_Tree;

#ifdef _USE_UCM_
/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */
void default_menu ( StructList *Menu )
{
    int              MAXX,MAXY;
	
	GetScreenSize(&MAXY,&MAXX);
	Menu->MyWindow.left         = 0;                     
	Menu->MyWindow.top          = 0;                     
	Menu->MyWindow.rigth        = (MAXX-1);               
	Menu->MyWindow.bottom       = (MAXY-1);               
	Menu->MyWindow.fontsize     = _SMALL_;               
    Menu->MyWindow.type         = _NORMALE_;        
	Menu->MyWindow.font         = 0;                      
	Menu->MyWindow.shortcommand = _OFF_;                 
	Menu->MyWindow.thickness    = 1;                      
	Menu->MyWindow.border       = _ON_;                   
	Menu->MyWindow.popup        = _NOPOPUP_;              
	Menu->MyWindow.first        = 0;                     
	Menu->MyWindow.time_out     = 60;                    
    Menu->MyWindow.current      = 0;
    Menu->MyWindow.correct      = _ON_;
    Menu->MyWindow.offset       = 1;
    Menu->MyWindow.selected     = _OFF_;                               
    Menu->MyWindow.nblines      = 15;                      
    Menu->MyWindow.type         = _PROPORTIONNEL_; 
    Menu->tab[0]                = (unsigned char *)PT_NULL;
    Menu->tab[1]                = (unsigned char *)PT_NULL;      
	Menu->tab[2]                = (unsigned char *)PT_NULL;
}

char Print_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;
	unsigned char      Cr;
	char cTemp[ 30 ];
	
	do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"Print MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"New line";
		Menu.tab[2]  = (unsigned char *)"Test line";
		Menu.tab[3] = NULL;
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);

		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0 :
				sprintf( cTemp, "Printer = %d\n", iLIBUCM_Print_Exist ( UCMC_PRINT ) ) ;
				iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 400 ) ;
			break;

			case 1 :
				iLIBUCM_Print_NewLine( UCMC_PRINT, 1 ) ;
			break;

			case 2 :
            /* permit to test a specific printing caracter */
				iLIBUCM_Print_Message( UCMC_PRINT, "\x0e""Sample UCMC\n" );
			break ;
			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}

/***************************************/
/* Lever lock command                                 */
/* for IUR250 only                                        */
/**************************************/
int iUnattendedLeverLock(void)
{
char cTemp[ 100 ];
int iRet,j;
T_UCMC_IAC_ICC_CMD sIcc;

iRet = STOP;
   
    sIcc.ucChannel = UCMC_ICC;
    sIcc.ctOpen[0] = 0;
    sIcc.usOption = 0;
    sIcc.usCmd = UCMCICC_CMD_LOCK;

    j = 10;

    /* exit after 10 tests in this example */
    while( j >= 0 )
    {
        if( (j%2) == 0 )
        {
            iLIBUCM_Display_Message( UCMC_DISPLAY, "Key to\nLOCK OFF", 0 );

            iRet = iLIBUCM_Pinpad_GetChar( UCMC_PPAD ) ;

            sIcc.u.ucLock = 0;  /* 0=OFF 1=ON */
            iRet = iLIBUCM_Icc_Cmd( &sIcc ) ;


            sprintf( cTemp, "lock off =%d\n %d/10",iRet, j  ) ;
        }
        else
        {
            iLIBUCM_Display_Message( UCMC_DISPLAY, "Key to\nLOCK ON", 0 );

            iRet = iLIBUCM_Pinpad_GetChar( UCMC_PPAD ) ;

            sIcc.u.ucLock = 1;  /* 0=OFF 1=ON */
            iRet = iLIBUCM_Icc_Cmd( &sIcc ) ;

            sprintf( cTemp, "lock on\n=%d\n %d/10",iRet, j  ) ;
        }

        iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 0 );
        j --;
        
    }

return( iRet);

}

char Cam_Menu(void)
{
	ENTRY_BUFFER       buf ;
	StructList         Menu ;
	unsigned char      Cr ;
    unsigned char      ucChannel ;

	char cTemp[ 1024 ], cTemp2[ 1024 ] ;
	int j, k, o ;
	HISTORIC Histo ;
	T_UCM_DEVICE sDevice ;

	COMMAND_CAM     sInputCommand ;

	T_APDU sApduIn, sApduOut ;

	unsigned short int usiIndx1 ;

	o = 0;
	j = 0;
	k = 0;
	ucChannel = 0;
	
	do
	{
		default_menu(&Menu) ;
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"Cam MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"Power on";
		Menu.tab[2]  = (unsigned char *)"Power on EMV";
		Menu.tab[3]  = (unsigned char *)"Power on SYNC";
		Menu.tab[4]  = (unsigned char *)"Power off";
		Menu.tab[5]  = (unsigned char *)"Status" ;
		Menu.tab[6]  = (unsigned char *)"Ttestall";
		Menu.tab[7]  = (unsigned char *)"Input/Ouput command";
		Menu.tab[8]  = (unsigned char *)"EMV APDU command";
		Menu.tab[9] = NULL;
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);
		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:  /* Config */
				iLIBUCM_Print_Message( UCMC_PRINT, "Config CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					j = iLIBUCM_Icc_Exist( ucChannel ) ;
					if( j >= 0 )
					{
						sprintf( cTemp, "Cam%d= %d\n",ucChannel , j  );
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

						sDevice.ucType = UCMC_ICC;	/* default ICC */

						if( iLIBUCM_Device_Config( UCM_DEVICE_ICC0, &sDevice ) == FCT_OK )
						{
							if( sDevice.u.sIcc.ucICC_Mixte != 0 )
							{
								sprintf( cTemp, "Mixte = OUI\n");
								iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
							}
							else
							{
								sprintf( cTemp, "Mixte = NON\n" );
								iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

							}
						}
					}
				}
			break;

			case 1: /* power on */
				iLIBUCM_Print_Message( UCMC_PRINT, "Poweron CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						Histo.length = 0;
						o = iLIBUCM_Icc_Open( ucChannel, "rw" ) ;

						if( o == FCT_OK )
						{
							j = iLIBUCM_Icc_PowerOn(ucChannel , UCMCICC_POWER_ON, &Histo ) ;
						}

						if( Histo.length != 0 )
						{
							for( k=0; k<Histo.length; k++)
								sprintf( &cTemp2[ k*3 ], " %02X", Histo.historic[k] ) ;						

							sprintf( cTemp, "Power%d= %d %d %d %s",ucChannel ,o, j ,Histo.length, &cTemp2[0] ) ;
						}
						else	
							sprintf( cTemp, "Power%d= %d %d",ucChannel ,o, j ) ;

						j = iLIBUCM_Icc_Close( ucChannel ) ;
						
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
					

				}
			break;

			case 2 : /* power on EMV */
				iLIBUCM_Print_Message( UCMC_PRINT, "Poweron EMV CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						Histo.length = 0;
						o = iLIBUCM_Icc_Open( ucChannel, "rw" ) ;

						if( o == FCT_OK )
						{
							j = iLIBUCM_Icc_PowerOn(ucChannel , UCMCICC_EMV_POWER_ON, &Histo ) ;
						}

						if( Histo.length != 0 )
						{
							for( k=0; k<Histo.length; k++)
								sprintf( &cTemp2[ k*3 ], " %02X", Histo.historic[k] ) ;						

							sprintf( cTemp, "Power%d= %d %d %d %s",ucChannel ,o, j ,Histo.length, &cTemp2[0] ) ;
						}
						else
							sprintf( cTemp, "Power%d= %d %d",ucChannel ,o, j  ) ;

						j = iLIBUCM_Icc_Close( ucChannel ) ;
						
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
					

				}
			break;

			case 3 : /* power on sync */
				iLIBUCM_Print_Message( UCMC_PRINT, "Poweron SYNC CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						Histo.length = 0;

						o = iLIBUCM_Icc_Open( ucChannel, "rw" ) ;

						if( o == FCT_OK )
						{
							j = iLIBUCM_Icc_PowerOn(ucChannel , UCMCICC_POWER_ON_SYNC, &Histo ) ;
						}

						if( Histo.length != 0 )
						{
							for( k=0; k<Histo.length; k++)
								sprintf( &cTemp2[ k*3 ], " %02X", Histo.historic[k] ) ;

								sprintf( cTemp, "Power%d= %d %d %d %s",ucChannel ,o, j ,Histo.length, &cTemp2[0] ) ;
						}
						else					
							sprintf( cTemp, "Power%d= %d %d",ucChannel ,o, j ) ;

						j = iLIBUCM_Icc_Close( ucChannel ) ;
						
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
					

				}
			break;
			
			case 4: /* power off */
				iLIBUCM_Print_Message( UCMC_PRINT, "Poweroff CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						j = iLIBUCM_Icc_PowerDown(ucChannel, UCMCICC_POWER_DOWN ) ;
			
						sprintf( cTemp, "Poweroff%d= %d",ucChannel ,j ) ;

						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
					
					
				}
			break;

			case 5: /* status */
				iLIBUCM_Print_Message( UCMC_PRINT, "Status CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						j = iLIBUCM_Icc_Status( ucChannel , (unsigned char*)&cTemp2[ 0 ] );
						
						sprintf( cTemp, "Status%d= %d ret=%d",ucChannel , cTemp2[ 0 ],j ) ;
						/* UCMC_STATUS_CARD_INSIDE or UCMC_STATUS_CARD_OUTSIDE */

						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
				}
			break;
			
			case 6: /* ttestall */
				iLIBUCM_Print_Message( UCMC_PRINT, "Ttestall CAM" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						j = iLIBUCM_Icc_Ttestall( ucChannel , 800 );
						
						sprintf( cTemp, "Ttestall%d ret=%d",ucChannel , j ) ;
						
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
				}
			break;

			case 7 : /* input/output command */

				iLIBUCM_Print_Message( UCMC_PRINT, "Input/Output Command" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						Histo.length = 0;

						o = iLIBUCM_Icc_Open( ucChannel, "rw" ) ;

						if( o == FCT_OK )
						{
							j = iLIBUCM_Icc_PowerOn(ucChannel , UCMCICC_POWER_ON, &Histo ) ;

							if ( j == FCT_OK )
							{
								/* print art */
								if( Histo.length != 0 )
								{
									for( k=0; k<Histo.length; k++)
										sprintf( &cTemp2[ k*3 ], " %02X", Histo.historic[k] ) ;						
								}
					
								sprintf( cTemp, "Power%d= %d %d %d %s",ucChannel , o, j ,Histo.length, &cTemp2[0] ) ;
								iLIBUCM_Print_Message( UCMC_PRINT, cTemp );							
								/************************************/
							
								/************************************/
								/* SELECT FILE ROOT*/
								cTemp [ 0] = (char) 0x00 ;
							   cTemp [ 1] = (char) 0xA4 ;
							   cTemp [ 2] = (char) 0x00 ;
							   cTemp [ 3] = (char) 0x00 ;
							   cTemp [ 4] = (char) 0x02 ;
							   cTemp [ 5] = (char) 0x00 ;
								sInputCommand.header = (unsigned char *)cTemp ;

								/* fic 3F00 */
								cTemp2 [ 0 ] = 0x3f ; 
								cTemp2 [ 1 ] = 0x00 ; 
								cTemp2 [ 3 ] = 0x00 ; 
								/*memcpy ( sInputCommand.data, "\x3F\x00\x00" ) ;*/
								sInputCommand.data = (unsigned char *)cTemp2 ;

								
								j = iLIBUCM_Icc_Input( ucChannel, UCMICC_NO_OPTION, &sInputCommand ) ;
								if ( j == FCT_OK )
								{
									sprintf( cTemp, "Select root :\n    SW1=%02x SW2=%02x \n",sInputCommand.statusword1, sInputCommand.statusword2 ) ;
									iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
									/************************************/
									/************************************/
									/* SELECT FILE ICCNS*/
									cTemp [ 0] = (char) 0x00 ;
								   cTemp [ 1] = (char) 0xA4 ;
								   cTemp [ 2] = (char) 0x00 ;
								   cTemp [ 3] = (char) 0x00 ;
								   cTemp [ 4] = (char) 0x02 ;
								   cTemp [ 5] = (char) 0x00 ;
									sInputCommand.header = (unsigned char *)cTemp ;

									/* fic 3F00 */
									cTemp2 [ 0 ] = (char) 0x00 ; 
									cTemp2 [ 1 ] = (char) 0x02 ; 
									cTemp2 [ 3 ] = (char) 0x00 ; 
									/*memcpy ( sInputCommand.data, "\x3F\x00\x00" ) ;*/
									memcpy ( sInputCommand.data, cTemp2, 3 ) ;
									
									j = iLIBUCM_Icc_Input( ucChannel, UCMICC_NO_OPTION, &sInputCommand ) ;
									if ( j == FCT_OK )
									{
										sprintf( cTemp, "Select ICCNS:\n    SW1=%02x SW2=%02x \n",sInputCommand.statusword1, sInputCommand.statusword2 ) ;
										iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
										/************************************/
										/************************************/
										/* READ ICCNS */
										   cTemp [ 0] = (char) 0x00 ;
										   cTemp [ 1] = (char) 0xB2 ;
										   cTemp [ 2] = (char) 0x00 ;
										   cTemp [ 3] = (char) 0x02 ;
										   cTemp [ 4] = (char) 0x08 ;
										   cTemp [ 5] = (char) 0x00 ;

										sInputCommand.header = (unsigned char *)cTemp ;
										sInputCommand.data   = (unsigned char *)cTemp2 ;
										memset ( sInputCommand.data, 0x00, 10 ) ;

										j = iLIBUCM_Icc_Output ( ucChannel, UCMICC_NO_OPTION, &sInputCommand ) ;
										if ( j == FCT_OK )
										{
											sprintf ( cTemp, "Read ICCNS  :\n   SW1=%02x SW2=%02x \n",sInputCommand.statusword1, sInputCommand.statusword2 ) ;
											iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

											sprintf ( cTemp, "ICCNS=%02x%02x%02x%02x\n", sInputCommand.data [ 0 ], sInputCommand.data [ 1 ],
			 									                                          sInputCommand.data [ 2 ], sInputCommand.data [ 3 ] ) ;
											iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
										}
										/************************************/
									}
								}
								j = iLIBUCM_Icc_Close( ucChannel ) ;
								
							}
						}

					}
					

				}
				
			break ;

			case 8 : /* emv apdu command */
				iLIBUCM_Print_Message( UCMC_PRINT, "EMV APDU Command" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Icc_Exist(ucChannel) > 0 )
					{
						Histo.length = 0;

						o = iLIBUCM_Icc_Open( ucChannel, "rw" ) ;

						if( o == FCT_OK )
						{
							j = iLIBUCM_Icc_PowerOn(ucChannel , UCMCICC_EMV_POWER_ON, &Histo ) ;

							if ( j == FCT_OK )
							{
								/* print art */
								if( Histo.length != 0 )
								{
									for( k=0; k<Histo.length; k++)
										sprintf( &cTemp2[ k*3 ], " %02X", Histo.historic[k] ) ;						
								}
					
								sprintf( cTemp, "Power%d= %d %d %d %s",ucChannel , o, j ,Histo.length, &cTemp2[0] ) ;
								iLIBUCM_Print_Message( UCMC_PRINT, cTemp );							
								/************************************/
							
								/************************************/
								/* SELECT FILE ROOT*/
								cTemp [ 0] = (char) 0x00 ;
							   cTemp [ 1] = (char) 0xA4 ;
							   cTemp [ 2] = (char) 0x04 ;
							   cTemp [ 3] = (char) 0x0C ;
							   cTemp [ 4] = (char) 0x06 ;
							   cTemp [ 5] = (char) 0xA0 ;
							   cTemp [ 6] = (char) 0x00 ;
							   cTemp [ 7] = (char) 0x00 ;
							   cTemp [ 8] = (char) 0x00 ;
							   cTemp [ 9] = (char) 0x69 ;
							   cTemp [10] = (char) 0x00 ;
							   
								sApduIn.data   = (unsigned char *)cTemp ;
								sApduIn.length = 0x0B ;

								memset ( cTemp2, 0x00, 50 ) ;
								sApduOut.data   = (unsigned char *)cTemp2 ;
																
								j = iLIBUCM_Icc_EmvApdu ( ucChannel, UCMICC_NO_OPTION, &sApduIn, &sApduOut ) ;

								if ( j == FCT_OK )
								{
									sprintf( cTemp, "Select :\n   LG_Rep=%03d\n   SW1=%02x SW2=%02x \n", 
												sApduOut.length, 
												*( sApduOut.data + sApduOut.length - 2 ), 
												*( sApduOut.data + sApduOut.length - 1 ) ) ;
									
									iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
									/************************************/
									/* read record */
									cTemp [ 0] = (char) 0x00 ;
								   cTemp [ 1] = (char) 0xB2 ;
								   cTemp [ 2] = (char) 0x01 ;
								   cTemp [ 3] = (char) 0xBC ;
								   cTemp [ 4] = (char) 0x16 ;
								   cTemp [ 5] = (char) 0x00 ;

									sApduIn.data   = (unsigned char *)cTemp ;
									sApduIn.length = 0x05 ;
									
									memset ( cTemp2, 0x00, 50 ) ;
									sApduOut.data   = (unsigned char *)cTemp2 ;
									
									j = iLIBUCM_Icc_EmvApdu( ucChannel, UCMICC_NO_OPTION, &sApduIn, &sApduOut ) ;

									if ( j == FCT_OK )
									{
										sprintf( cTemp, "Read record :\n   LG_Rep=%03d\n   SW1=%02x SW2=%02x \n", 
												   sApduOut.length,
										         *( sApduOut.data + sApduOut.length - 2 ),
										         *( sApduOut.data + sApduOut.length - 1 ) ) ;
										
										iLIBUCM_Print_Message( UCMC_PRINT, cTemp ) ;

										for ( usiIndx1 = 0; usiIndx1 < sApduOut.length; usiIndx1++ )
										{
											sprintf( cTemp2 + ( usiIndx1 * 3 ) ,"%02x ", 
												      *( sApduOut.data + usiIndx1 ) ) ;  
										}

										iLIBUCM_Print_Message( UCMC_PRINT, cTemp2 ) ;
										
										sprintf( cTemp, "Data = %s", cTemp2 ) ;
										iLIBUCM_Print_Message( UCMC_PRINT, cTemp ) ;
									}
								}
								j = iLIBUCM_Icc_Close( ucChannel ) ;
							}
						}
					}
				}
			   break ;
			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}

/*********************************/
/* Test key jammed */
/* press a key during 30 s to detect key blocked */
/* Only for UPP and IUP2520     */
/************************************/
void UnattendedKeyJammedTest()
{
T_UCM_IAC_PINPAD_CMD sCmd;
int iRet;
 char cTemp[ 100 ];

    sCmd.iCmd = UCM_PPAD_CMD_KEY_CTRL;
    sCmd.iLg = 0;
    sCmd.iRet = 0;
    sCmd.u.ucKey = 0xFF;

    iRet = 0;
    iLIBUCM_Display_Message( UCMC_DISPLAY, "Press a key\n 30s", 3100 ); 

    /* 31 secondes */
    iRet = iLIBUCM_Pinpad_Cmd( UCMC_PPAD, &sCmd ) ;

    sprintf( cTemp, "Cmd =%d\n%d %x",iRet, sCmd.iRet, sCmd.u.ucKey  ) ;
    iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 300 );

}

void UnattendedKeyPadTest()
{
T_UCM_ENTRY_PPAD     sPPad ;
int iRet,j;
char cTemp[ 100 ];

    if( iLIBUCM_Pinpad_Exist(UCMC_PPAD) > 0 )
    {
        iLIBUCM_Print_Message( UCMC_PRINT, "Input" );

        /* UCM_PPAD_CODE */
        /*This sample works only CAD30PPS, CADTOOL, CAD30UPP (but deprecated) */
        /* Other case use SEC_PinEntry for chip pin dont use iLIBUCM_Pinpad_Input */
        j = iLIBUCM_Pinpad_Open( UCMC_PPAD, "r" ) ;

        if ( j == FCT_OK )
        {
            iLIBUCM_Display_Message( UCMC_DISPLAY, "PPAD Input\nEcho Spe Num 4",100 );
            sPPad.usMask = 0xB800; //0 ;
            sPPad.usTask = 0 ;
            sPPad.ucTimeout = 120; /* 2 minutes seconde */
            sPPad.ucTimeout_inter = 60 ; /* 1 minute */
            sPPad.ucLine = 1 ;
            sPPad.ucColumn  = 8;
            sPPad.ucEcho = ECHO_SPECIAL_PPAD;
            sPPad.ucNb_max = 6;
            sPPad.ucNb_min = 4;
            sPPad.ucType = UCM_PPAD_CODE;
            sPPad.ucClear = 1;
            sPPad.ucPhase = 0;
            sPPad.ucRuf[0] = 0;
            sprintf( sPPad.uctDisplay, "INPUT 4 DIGIT" );
            sPPad.ucLgDisplay = strlen( sPPad.uctDisplay );

            iRet = iLIBUCM_Pinpad_Open( UCMC_PPAD, "r" ) ;

            if( iRet == FCT_OK )
            {
                iRet = iLIBUCM_Pinpad_Input(UCMC_PPAD , UCMPPAD_CLOSE_AT_END, &sPPad ) ;
            }

            sprintf( cTemp, "input=%d\nCr=%d %s", iRet , sPPad.ucResultCr, sPPad.uctResultBuf ) ;
            iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 400 );
        }
        /*******************/

        /* UCM_PPAD_NUMERIQUE */
        /*This sample works only CAD30PPS, CADTOOL, IUP en maintenance mode */
        /* Other case use SEC_PinEntry for chip pin dont use iLIBUCM_Pinpad_Input */
        /* blocage car pas de schéma */
        j = iLIBUCM_Pinpad_Open( UCMC_PPAD, "r" ) ;

        if ( j == FCT_OK )
        {
            iLIBUCM_Display_Message( UCMC_DISPLAY, "PPAD Input\necho Num 2",100 );
            sPPad.usMask = 0xB800; //0 ;
            sPPad.usTask = 0 ;
            sPPad.ucTimeout = 120; /* 2 minutes seconde */
            sPPad.ucTimeout_inter = 60 ; /* 1 minute */
            sPPad.ucLine = 1 ;
            sPPad.ucColumn  = 8;
            sPPad.ucEcho = ECHO_NORMAL;
            sPPad.ucNb_max = 2;
            sPPad.ucNb_min = 1;
            sPPad.ucType = UCM_PPAD_NUMERIQUE;
            sPPad.ucClear = 1;
            sPPad.ucPhase = 0;
            sPPad.ucRuf[0] = 0;
            sprintf( sPPad.uctDisplay, "INPUT 2 DIGIT" );
            sPPad.ucLgDisplay = strlen( sPPad.uctDisplay );

            iRet = iLIBUCM_Pinpad_Open( UCMC_PPAD, "r" ) ;

            if( iRet == FCT_OK )
            {
               iRet = iLIBUCM_Pinpad_Input(UCMC_PPAD , 0, &sPPad ) ;
            }

            sprintf( cTemp, "Saisie=%d\nCr=%d %s", iRet , 
            sPPad.ucResultCr, sPPad.uctResultBuf ) ;

            iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 400 );

            iRet = iLIBUCM_Pinpad_Close( UCMC_PPAD ) ;
        }


        /*******************************/
        /* function keys and numérique key CADTOO et IUP */
        /* Other function key */
        iRet = UCMTTESTALL_CR_OK_EVENT;

        iLIBUCM_Display_Message( UCMC_DISPLAY, "WAIT\nKEY", 0 );

        iRet = iLIBUCM_Pinpad_Ttestall( UCMC_PPAD , 800 );

        if( iRet == UCMTTESTALL_CR_OK_EVENT )
        {
            j = iLIBUCM_Pinpad_GetChar( UCMC_PPAD ) ;
            sprintf( cTemp, "GetChar=%d",j  ) ;
            iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 0 );
        }

        /*******************************/
        /* function keys and numérique key CADTOO et IUP */
        /* Other function key */
        iLIBUCM_Display_Message( UCMC_DISPLAY, "WAIT KEY\nTo 260s", 0 );
        iRet = iLIBUCM_Pinpad_GetChar( UCMC_PPAD ) ;
        sprintf( cTemp, "GetChar\n=%d",iRet  ) ;
        iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 0 );

    }
}

char Pinpad_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;

   unsigned char      Cr;
   unsigned char      ucChannel;

	char cTemp[ 60 ], cTemp2[ 50 ];
	int j;
	
   do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"PPAD MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"Input";
		Menu.tab[2]  = (unsigned char *)"Status";
		Menu.tab[3] = NULL;
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);
		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:  /* Config */
				iLIBUCM_Print_Message( UCMC_PRINT, "Config PPAD" );
				for( ucChannel=0; ucChannel < UCMC_PINPADMAX; ucChannel++ )
				{
					j = iLIBUCM_Pinpad_Exist( ucChannel ) ;
					if( j >= 0 )
					{
						sprintf( cTemp, "PPAD%d= %d\n",ucChannel , j  );
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
				}
			break;

			case 1:  /* Input */
                            UnattendedKeyPadTest();
			break;
	
			case 2:  /* Status */
				iLIBUCM_Print_Message( UCMC_PRINT, "Status PPAD" );
				for( ucChannel=0; ucChannel< UCMC_ICCSAMMAX; ucChannel++ )
				{
					if( iLIBUCM_Pinpad_Exist(ucChannel) > 0 )
					{
						j = iLIBUCM_Pinpad_Status( ucChannel , (unsigned char *)&cTemp2[ 0 ] );
						
						sprintf( cTemp, "Status%d= %d Ret=%d",ucChannel ,cTemp2[ 0 ], j ) ;
						
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
				}
			break;
			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}

extern int iGraphic_message( char *pMessage_p, int iTo_p );

char Display_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;
	unsigned char      Cr;
	char cTemp[ 30 ];
	
	do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"DISPLAY MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"Clear line";
		Menu.tab[2]  = (unsigned char *)"1 line";
		Menu.tab[3]  = (unsigned char *)"Graphic";
		Menu.tab[4] = NULL;
		
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);
		
		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:
				sprintf( cTemp, "Display = %d\n", iLIBUCM_Display_Exist( UCMC_DISPLAY ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

			case 1:
				iLIBUCM_Display_Clear( UCMC_DISPLAY );
				break;
			case 2:
				iLIBUCM_Display_Message( UCMC_DISPLAY,"TEST LINE 1", 200 ) ;
				break;
			case 3:
                            iGraphic_message( "Graphic test", 200 );
				break;

			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}



char Modem_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;
	unsigned char      Cr;
	int iRet;
	T_UCMC_IAC_MODEM_CNX sMod;
	char cTemp[ 30 ];
		
	do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"Modem MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"Cnx";
		Menu.tab[2]  = (unsigned char *)"Dcnx";
		Menu.tab[3] = NULL;
		
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		
		Cr = Get_Entry(&buf);
		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:
				sprintf( cTemp, "Modem = %d\n\n\n\n\n", iLIBUCM_Modem_Exist() );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
			break;
			case 1:
				sprintf( (char *)sMod.uctAppel, "3615UCMC" );
				sprintf( (char *)sMod.uctRaccord, "eon" );
				sMod.ucTypeCentre = 8;
				sMod.ucTypePad = 2;
				
				iRet = iLIBUCM_Modem_Cnx( &sMod ) ;
			break;
			case 2:
				iRet = iLIBUCM_Modem_Dcnx( 2 ) ;
			break;

			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}

char Buzzer_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;
	unsigned char      Cr;
	char cTemp[ 30 ];
	T_UCMC_IAC_BUZ sBuz;
	
	do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"Buzzer MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"On 3s Normal";
		Menu.tab[2]  = (unsigned char *)"On 3s Hight";
		Menu.tab[3]  = (unsigned char *)"On 3s Bass";
		Menu.tab[4]  = (unsigned char *)"Off";
		Menu.tab[5] = NULL;
		
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);
		
		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:
				sprintf( cTemp, "Buzzer = %d\n", iLIBUCM_BUZZER_Exist() );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
			break;	
			case 1:
				sBuz.ucCmd = UCMC_BUZ_NORMAL;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
				sBuz.usDelay = 3;
				sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

				break;

			case 2:
				sBuz.ucCmd = UCMC_BUZ_HIGH;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
				sBuz.usDelay = 3;
				sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;

			case 3:
				sBuz.ucCmd = UCMC_BUZ_BASS;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
				sBuz.usDelay = 3;
				sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;

			case 4:
				sBuz.ucCmd = UCMC_BUZ_OFF;  /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
				sBuz.usDelay = 0;
				sprintf( cTemp, "Off = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;
			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}



char Led_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;
	unsigned char      Cr;
	char cTemp[ 30 ];
	T_UCMC_IAC_LED sLed;
	
	do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"LED MENU";
		Menu.tab[0]  = (unsigned char *)"Config";
		Menu.tab[1]  = (unsigned char *)"On";
		Menu.tab[2]  = (unsigned char *)"Off";
		Menu.tab[3]  = (unsigned char *)"Flash";
		Menu.tab[4]  = (unsigned char *)"Status";
		Menu.tab[5] = NULL;
		
		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);
		
		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:
				sprintf( cTemp, "Led = %d\n", iLIBUCM_LED_Exist() );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

			case 1:
				sLed.ucLedNumber = 1 ;
				sLed.ucCmd = 2 ;
				sLed.usDelay = 4 ;
				sprintf( cTemp, "On = %d\n", iLIBUCM_LED_Cmd( &sLed ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;
			case 2:
				sLed.ucLedNumber = 1 ;
				sLed.ucCmd = 2 ;
				sLed.usDelay = 4 ;
	
				sprintf( cTemp, "Off = %d\n", iLIBUCM_LED_Cmd( &sLed ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;
			case 3:
				sLed.ucLedNumber = 1 ;
				sLed.ucCmd = 3 ;
				sLed.usDelay = 4 ;				
				sprintf( cTemp, "Flash = %d\n", iLIBUCM_LED_Cmd( &sLed ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;
			case 4:
				sprintf( cTemp, "Status = %d %d", iLIBUCM_LED_Status( &Cr ), Cr );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );

				break;
			}
		}
		else
		{
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
}



int cu_more_function_UCM(NO_SEGMENT no,void *p1,void *p2)
{
	int prec;
	ENTRY_BUFFER       buf;
	StructList         Menu;
	unsigned char      Cr;
	
	prec=StateHeader(0);
	
	do
	{
		default_menu(&Menu);
		Menu.MyWindow.shortcommand  = _ON_;                 
		Menu.MyWindow.title         = (unsigned char *)"SAMPLE MENU";
		Menu.tab[0]  = (unsigned char *)"Test DISPLAY";
		Menu.tab[1]  = (unsigned char *)"Test PRINT";
		Menu.tab[2]  = (unsigned char *)"Test MODEM";
		Menu.tab[3]  = (unsigned char *)"Test CAM";
		Menu.tab[4]  = (unsigned char *)"Test PPAD";
		Menu.tab[5]  = (unsigned char *)"Test BUZZER";
		Menu.tab[6]  = (unsigned char *)"Test LED";
		Menu.tab[7]  = NULL;

		G_List_Entry((void*)&Menu);
		ttestall(ENTRY,0);
		Cr = Get_Entry(&buf);

		if (Cr==CR_ENTRY_OK)
		{
			switch (buf.d_entry[0])
			{
			case 0:
				Display_Menu();
				break;
			case 1:
				Print_Menu();
				break;
			case 2:
				Modem_Menu();
				break;
			case 3:
				Cam_Menu();
				break;
			case 4:
				Pinpad_Menu();
				break;
			case 5:
				Buzzer_Menu();
				break;
			case 6:
				Led_Menu();
				break;
			}
		}
		else
		{
			prec  =IsHeader();
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
	
	return (FCT_OK);
}
#endif

//===========================================================================
//! \brief This function manages the application Merchant menu.
//! \return The Get_Entry return value.
//! - CR_ENTRY_OK : Successful entry.
//! \li the field d_entry[0] of Entry_buffer contains the index of the selected
//! item in the list for G_List_Entry.
//! \li the field d_len of Entry_buffer contains the entry length.
//! \li the field d_entry [50]  of Entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised)
//! - CR_ENTRY_TIME_OUT : Timeout elapsed
//! - CR_ENTRY_CANCEL : Entry Cancelled
//! - CR_ENTRY_VAL : Green key (confirmation)
//! - CR_ENTRY_FCT : F key pushed (if authorised)
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised)
//===========================================================================
static int merchant(void)
{
	unsigned char	cr;
	unsigned char	i;
	ENTRY_BUFFER	Entry_buffer;
	unsigned short	lg_code;
	wIconList		IconLst;

	memclr(&IconLst, sizeof(IconLst));

	// Init table from const
	InitDefaut(_ON_,1);

	lg_code = PSQ_Give_Language();


	Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT, lg_code);

	for (i=0 ; i < ELVEC(NavigationMerchant) ; i++ )
	{
		Menu.tab[i] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationMerchant[i].itemlabel, lg_code);
	}

	// Call navigation time-out 30 secs
	Menu.tab[i] = NULL;

	G_List_Entry(&Menu);


	ttestall(ENTRY,0);
	cr=Get_Entry(&Entry_buffer);

	switch(cr)
	{
		case CR_ENTRY_OK :
			ACCES_FCT0 (NavigationMerchant[Entry_buffer.d_entry[0]].function);
			break;
	}

	return(cr);
}

//===========================================================================
//! \brief This function manages the application ParamManagement menu.
//! \return The Get_Entry return value.
//! - CR_ENTRY_OK : Successful entry.
//! \li the field d_entry[0] of Entry_buffer contains the index of the selected
//! item in the list for G_List_Entry.
//! \li the field d_len of Entry_buffer contains the entry length.
//! \li the field d_entry [50]  of Entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised)
//! - CR_ENTRY_TIME_OUT : Timeout elapsed
//! - CR_ENTRY_CANCEL : Entry Cancelled
//! - CR_ENTRY_VAL : Green key (confirmation)
//! - CR_ENTRY_FCT : F key pushed (if authorised)
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised)
//===========================================================================
static int ParamManagement(void)
{
	unsigned char	cr;
	unsigned char	i;
	ENTRY_BUFFER	Entry_buffer;
	unsigned short	lg_code;
	wIconList		IconLst;

	memclr(&IconLst, sizeof(IconLst));

	// Init table from const
	InitDefaut(_ON_,1);

	lg_code = PSQ_Give_Language();


	Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_PARAM_MNGT, lg_code);

	for (i=0 ; i < ELVEC(NavigationParamMngt) ; i++ )
	{
		Menu.tab[i] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationParamMngt[i].itemlabel, lg_code);
	}

	// Call navigation time-out 30 secs
	Menu.tab[i] = NULL;

	G_List_Entry(&Menu);

	ttestall(ENTRY,0);
	cr=Get_Entry(&Entry_buffer);

	switch(cr)
	{
		case CR_ENTRY_OK :
			ACCES_FCT0 (NavigationParamMngt[Entry_buffer.d_entry[0]].function);
			break;
	}
	return(cr);
}

//===========================================================================
//! \brief This function performs a transaction according to transaction type
//! given as parameter.
//! \param[in] TransactionType : type of the transaction.
//! \param ucParameters  : TRUE if ulAmount and nCurrencyCode parameters must be used.
//! \param ulAmount      : amount entered.
//! \param nCurrencyCode : ISO currency code.
//! \ref CUSERV_DEBIT_TRANSACTION
//! \ref CUSERV_REFUND_TRANSACTION
//! \ref CUSERV_CASH_TRANSACTION
//! \ref CUSERV_CASHBACK_TRANSACTION
//===========================================================================
static void CUMORE_PaiementFct(unsigned long TransactionType, unsigned char ucParameters, unsigned long ulAmount, int nCurrencyCode)
{
#ifdef _ENABLE_CAM2_
	static const unsigned long ulChipReaders = CAM0 | CAM2;
#else
	static const unsigned long ulChipReaders = CAM0;
#endif
	int result;
	int found;
	unsigned short currency_code = 0;
	unsigned char  TabAmount [4];
	unsigned char  TabAmountC [4];
	unsigned char  NumAmount [6];
	unsigned char  NumAmountC [6];
	unsigned long  entered_amount;
	DataElement eltCurrency,eltCurrencyExp;
	unsigned char TypeAppli[2];
	unsigned char EngAppliSel;
	TLV_TREE_NODE hInputTree;
	TLV_TREE_NODE hOutputTree;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// -----------------------------------------------------------------
	// Amount Entry
	// -----------------------------------------------------------------

    if (ucParameters == TRUE) // If parameters given in interface must be used
    {
        result = T_VAL;
        entered_amount = ulAmount;
        currency_code = nCurrencyCode;
    }
    else // Parameters : amount and currency code must be inputed or found ...
    {
	    // No card is present at this moment. The currency used is the Terminal currency
	    found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&eltCurrency);
	    if (found)
		    currency_code = (eltCurrency.ptValue[0] << 8) + eltCurrency.ptValue[1];

	    // Read the amount, using the good currency code
	    result = CUMESS_GetAmount (currency_code, &entered_amount);
    }

	if ((result == T_VAL) && (entered_amount!=0))
	{
		// Amount is valid. Convert in num
		CUMESS_ConvertBinNUM (entered_amount, NumAmount);

		LongToChar (entered_amount, TabAmount);

		// Store amounts in current database

		CUTERMclearDisplay();

		hInputTree = TlvTree_New(0);

		if(hInputTree != NULL)
		{
			ShortToChar(CustApplicationNumber,TypeAppli);
			TlvTree_AddChild(hInputTree, TAG_ENG_CUSTOM_APPLI_TYPE, (unsigned char*) &TypeAppli, 2);

			EngAppliSel =0;
			TlvTree_AddChild(hInputTree, TAG_ENG_APPLI_SEL_ALREADY_DONE, (unsigned char*) & EngAppliSel, 1);

			TlvTree_AddChild(hInputTree, TAG_TRANSACTION_CURRENCY_CODE, (unsigned char*) &eltCurrency.ptValue[0], 2);

			found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&eltCurrencyExp);
			if (found)
			{
				TlvTree_AddChild(hInputTree, TAG_TRANSACTION_CURRENCY_EXP, (unsigned char*) &eltCurrencyExp.ptValue[0], 1);
			}

			if (TransactionType == CUSERV_CASHBACK_TRANSACTION)
			{
				ulTransactionType = CUSERV_CASHBACK_TRANSACTION;

				// Read the amount, using the good currency code
				result = CUMESS_GetAmount (currency_code, &entered_amount);
				LongToChar (0, TabAmountC);
				memset (NumAmountC,0,sizeof(NumAmountC));
				if ( (result == T_VAL) && (entered_amount!=0) )
				{
					CUMESS_ConvertBinNUM (entered_amount, NumAmountC);

					LongToChar (entered_amount, TabAmountC);
				}
			}
			else
			{
				memclr  ( TabAmountC,sizeof(TabAmountC));
			}
			TlvTree_AddChild(hInputTree, TAG_AMOUNT_OTHER_BIN, TabAmountC, 4);
			TlvTree_AddChild(hInputTree, TAG_AMOUNT_OTHER_NUM, NumAmountC, 6);
			TlvTree_AddChild(hInputTree, TAG_AMOUNT_AUTH_BIN, TabAmount, 4);

			TlvTree_AddChild(hInputTree, TAG_ENG_WAIT_CHIP_READERS, &ulChipReaders, sizeof(ulChipReaders));
			TlvTree_AddChild(hInputTree, TAG_ENG_REMOVE_CHIP_READERS, &ulChipReaders, sizeof(ulChipReaders));

			// Copy the TLV tree to a local _DEL_ object.
			// Convert local _DEL_ object to local DEL object
			// These conversions will be suppressed when Engine_DoTransaction will be implemented in TLV tree mode.
			hOutputTree = NULL;
			
			Engine_DoTransaction(hInputTree,&hOutputTree);
			TlvTree_ReleaseEx(&hInputTree);
			
			TlvTree_ReleaseEx(&hOutputTree);

		}
	}
}

//===========================================================================
void CUMORE_Debit(void)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
void CUMORE_Administrative(void)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}
//===========================================================================
void CUMORE_Inquiry(void)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

void CUMORE_DebitEx(unsigned long ulAmount, int nCurrencyCode)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, TRUE, ulAmount, nCurrencyCode);
}

//===========================================================================
void CUMORE_Refund (void)
{
	ulTransactionType = CUSERV_REFUND_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_REFUND_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
//! \brief This function performs a cash transaction.
//===========================================================================
static void CUMORE_Cash (void)
{
	/* Memorize the transaction type                                       */
	ulTransactionType = CUSERV_CASH_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_CASH_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
//! \brief This function performs a cash back transaction.
//===========================================================================
static void CUMORE_CashBack(void)
{
	CUMORE_PaiementFct(CUSERV_CASHBACK_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
//! \brief This function gives statistics on the batch data file.
//===========================================================================
static void CUMORE_BatchStat(void)
{
	unsigned long nb_record;
	unsigned long total_amount;
	unsigned long result;
	int merchLang;
	char line[80];
	unsigned char *pcline1;
	unsigned char msg[100];

	// Get manager language
	merchLang = PSQ_Give_Language();
	if (merchLang >= C_NBLANGMERCH)
	{
		merchLang = 0;
	}

	// Display please wait
	pcline1 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PLEASE_WAIT, merchLang);
	sprintf(msg, "\n%s", pcline1);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	// Read statistics
	result = CUBATCH_GiveStatistics (&nb_record, &total_amount);

	if (result)
	{
		// Read language
		// merchLang = PSQ_Give_Language();

		// Print statistics ticket
		CUTERMsetPrinter(PRINT_LARGE);
		CUTERMprintLine("");
		CUTERMprintLine(CUMESS_Read_Message(BATCH_STAT_TABLE, STAT_MESS_BATCH_STATISTICS, merchLang));
		CUTERMprintLine("");
		CUTERMsetPrinter(PRINT_NORMAL);
		sprintf(line,
				"%s   : %ld\n",
				CUMESS_Read_Message(BATCH_STAT_TABLE, STAT_MESS_NB_RECORDS, merchLang),
				nb_record);
		CUTERMprintLine(line);
		sprintf(line,
				"%s   : %ld\n",
				CUMESS_Read_Message(BATCH_STAT_TABLE, STAT_MESS_TOTAL_AMOUNT, merchLang),
				total_amount);
		CUTERMprintLine(line);
		CUTERMprintLine("");
		CUTERMpaperFeed();
	}
}

//===========================================================================
//! \brief This function manages the Bypass PIN function.
//===========================================================================
static void CUMORE_Bypass_PIN (void)
{
	unsigned short		lg_code;
	unsigned char		msg[100];
	unsigned char		*pcline1, *pcline2;

	// Short message to display the BYPASS PIN function is activated for next transaction
	CUDB_Get_cardholder_language (&lg_code);
	if (lg_code >= C_NBLANGMERCH)
	{
		lg_code = 0;
	}
	CUTERMclearDisplay();

	pcline1 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_BYPASS_PIN_1, lg_code);
	pcline2 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_BYPASS_PIN_2, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pcline1, pcline2);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	CUTERMsleep (1500);

	// Set the bypass required flag
	Bypass_Required = (CUMORE_TRUE[0] << 8) + CUMORE_TRUE[1];

}

//===========================================================================
//! \brief This function forces the next transaction to go online.
//===========================================================================
static void CUMORE_ForcedOnline (void)
{
	unsigned short		lg_code;
	unsigned char		msg[100];
	unsigned char		*pcline1, *pcline2;

	// Short message to display that next transaction will go online
	CUDB_Get_cardholder_language (&lg_code);
	if (lg_code >= C_NBLANGMERCH)
	{
		lg_code = 0;
	}

	CUTERMclearDisplay();

	pcline1 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_FORCED_ONLINE_1, lg_code);
	pcline2 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_FORCED_ONLINE_2, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pcline1, pcline2);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	CUTERMsleep (1500);

	// Set the Transaction forced online flag
	TransactionForcedOnline = (CUMORE_TRUE[0] << 8) + CUMORE_TRUE[1];

}

//===========================================================================
//! \brief This function sends the batch data file to the host thru ISO8583 protocol.
//===========================================================================
static void CUMORE_BatchCapt_Iso8583 (void)
{
	int cr;
	unsigned long nb_record;
	DataElement elt;
	unsigned short found;  // transfer_ok
	int transfer_ok;
	unsigned short NeedBlackList;
	int merchLang;
	unsigned char text [255];
	DATE date;
	unsigned char raz_no_serial [ 9 ]  ;
	int bConnected;
	char *pc_l_DisplayTxt;
	TLV_TREE_NODE hTree, hOutTree,hTreeDis;
	unsigned int Trans_pos = 0;
	unsigned short Trans_index = 0;
	unsigned char *pcline1;
	unsigned char msg[100];

	hTreeDis = NULL;

	// Read number of records
	CUBATCH_InitialiseBatchTransfer (&nb_record);

	merchLang = PSQ_Give_Language();

	// Put on base only X930
	if (( powered() !=1)&&(CUTERMgetTerminalType()==T_CUTERM_X930))
	{
		pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_REPLACE_BASE, merchLang);
		CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
		do
		{
			cr = powered();
		} while (cr != 1);

		CUMESS_Display_Message (0, STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT_CARDHOLDER);
	}

	// Display please wait
	pcline1 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PLEASE_WAIT, merchLang);
	sprintf(msg, "\n%s", pcline1);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	/*-----------------------------------------------------------------------*/
	/* Batch transfer initialisation                                         */
	/*-----------------------------------------------------------------------*/
	found = FALSE;

	bConnected = Host_Config_Connect();

	if (bConnected)
	{
		// Sequence Counter : 9F41
		hTree = Engine_GetDataElement(TAG_TRANSACTION_SEQ_COUNTER);

		hOutTree = TlvTree_New(0);

		if(hOutTree != NULL)
		{

			found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_TRANSACTION_SEQ_COUNTER, &elt);
			if (found)
			{
				TlvTree_AddChild(hOutTree, elt.tag, elt.ptValue, elt.length);
			}

			// release local TLV tree
			TlvTree_ReleaseEx(&hTree);

			// Improvement of IFD_serial number and terminal id management
			CUTERMgetSerialNumber((char*)raz_no_serial);
			TlvTree_AddChild(hOutTree, TAG_IFD_SERIAL_NUMBER, raz_no_serial, 8);

			TlvTree_AddChild(hOutTree, TAG_CUST_NB_RECORD_IN_BATCH, ( unsigned char *) &nb_record, 4);

			// Check Black-list validity
			NeedBlackList = !(CUBLACKL_IsValid ());
			TlvTree_AddChild(hOutTree, TAG_CUST_NEW_BLACK_LIST_NEEDED, ( unsigned char *) &NeedBlackList, 2);

			// Batch transfer initialisation
			found = FALSE;

			// Generate batch TLV tree in the same way than for authorisation
			hOutTree = EMVCUST_Build_start_transac_download_TLVTree(&hOutTree);

			hOutTree = COMM_Send_And_Receive_Message_TlvTree(hOutTree);

			found = CUSERV_Extract_Element_TLV_Tree(&hOutTree, TAG_COMM_STATUS_CODE, &elt);
		}
	}
	else
	{
		found = FALSE;
	}

	transfer_ok = (found && (*(elt.ptValue) == 0));
	if (transfer_ok)
	{
		/*-----------------------------------------------------------------------*/
		/* Batch transfer loop                                                   */
		/*-----------------------------------------------------------------------*/

		cr = CUDISK_CreateDisk();
		if (cr == FS_OK)
		{
			do
			{
				cr = Get_Next_Transaction(&Transac_File, &hTree, &Trans_pos);

				if (cr == TRANS_FILE_OK)
				{
					// Get TAG_CUST_BATCH_RECORD_TYPE
					found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CUST_BATCH_RECORD_TYPE, &elt);
					if (found)
					{
						// Check if record read is a financial record
						if (elt.ptValue[0] == FINANCIAL_RECORD)
						{
							transfer_ok = CUMORE_Send_Financial_Record(hTree);
						}
						else
						{
							transfer_ok = CUMORE_Send_Advice_Record(hTree);
						}

						Trans_index++;

						if (transfer_ok)
						{
							// Erase the record
							RetransmitIndicator = FALSE;
						}
						else
						{
							// Mark the record has been transmitted
							RetransmitIndicator = TRUE;
						}
					}
				}

				TlvTree_ReleaseEx(&hTree);
			}
			while ((Trans_index < nb_record) && (transfer_ok));
			// End of batch transfer loop
			// while (cr == TRANS_FILE_OK);

			if ((Trans_index == nb_record) && transfer_ok)
			{
				// All the transaction records are sent. The file can be deleted
				Del_Transaction_File(&Transac_File);
			}

			// Unmount the volume
			CUDISK_UnmountDisk();
		}

		/*-----------------------------------------------------------------------*/
		/* Batch transfer termination                                            */
		/*-----------------------------------------------------------------------*/

		// Sequence Counter : 9F41
		hTree = Engine_GetDataElement(TAG_TRANSACTION_SEQ_COUNTER);

		// release local TLV tree
		TlvTree_ReleaseEx(&hOutTree);

		hOutTree = TlvTree_New(0);

		if(hOutTree != NULL)
		{
			found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_TRANSACTION_SEQ_COUNTER, &elt);
			if (found)
			{
				TlvTree_AddChild(hOutTree, elt.tag, elt.ptValue, elt.length);
			}

			// release local TLV tree
			TlvTree_ReleaseEx(&hTree);

			// Improvement of IFD_serial number and terminal id management
			// CUTERMgetTerminalId ( (char *) card_acceptor_terminal_id ) ;
			CUTERMgetSerialNumber((char*)raz_no_serial);
			TlvTree_AddChild(hOutTree, TAG_IFD_SERIAL_NUMBER, ( unsigned char * ) raz_no_serial, 8);

			// Mixed Communication with ISO8583 and SPDH
			// Send record
			hOutTree = EMVCUST_Build_terminate_transac_download_TLVTree(&hOutTree);

			hOutTree = COMM_Send_And_Receive_Message_TlvTree(hOutTree);

			found = CUSERV_Extract_Element_TLV_Tree(&hOutTree, TAG_COMM_STATUS_CODE, &elt);

			transfer_ok = (found && transfer_ok && (*(elt.ptValue) == 0));

		}
	}
	else
	{
		// else communication KO

		// Mixed Communication with ISO8583 and SPDH
		hOutTree = EMVCUST_Build_terminate_transac_download_TLVTree(&hOutTree);

		hOutTree = COMM_Send_And_Receive_Message_TlvTree(hOutTree);
	}

	// release local TLV tree
	TlvTree_ReleaseEx(&hOutTree);

	// Generate batch TLV tree in the same way than for authorisation
	if (bConnected)
	{
		hTreeDis=COMM_Disconnect_TlvTree (NULL);
		bConnected = FALSE;
		TlvTree_ReleaseEx(&hTreeDis);
	}

	/*-----------------------------------------------------------------------*/
	/* ticket                                                                */
	/*-----------------------------------------------------------------------*/
	sprintf ((char *) text, "\x1b""E%s""\x1b""F", CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPLI_NAME, merchLang));
	CUTERMprintLine((char *)text);

	read_date(&date);
	sprintf ((char *) text, "%.2s/%.2s/%.2s  %.2s:%.2s", date.day, date.month, date.year, date.hour, date.minute);
	CUTERMprintLine((char *)text);

	pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_CAPTURE, merchLang);
	CUTERMprintLine(pc_l_DisplayTxt);
	if (transfer_ok)
	{
		// DATA CAPTURE SUCCESFUL
		pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_SUCCESFUL, merchLang);
		CUTERMprintLine(pc_l_DisplayTxt);
	}
	else
	{
		// DATA CAPTURE ERROR
		pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_ERROR, merchLang);
		CUTERMprintLine(pc_l_DisplayTxt);
	}

	CUTERMpaperFeed();
}

//===========================================================================
//! \brief This function erases the batch data file without data capture.
//! \return The Get_Entry return value.
//! - CR_ENTRY_OK : Successful entry.
//! \li the field d_entry[0] of Entry_buffer contains the index of the selected
//! item in the list for G_List_Entry.
//! \li the field d_len of Entry_buffer contains the entry length.
//! \li the field d_entry [50]  of Entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised)
//! - CR_ENTRY_TIME_OUT : Timeout elapsed
//! - CR_ENTRY_CANCEL : Entry Cancelled
//! - CR_ENTRY_VAL : Green key (confirmation)
//! - CR_ENTRY_FCT : F key pushed (if authorised)
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised)
//===========================================================================
static int CUMORE_BatchCaptRaz(void)
{
	unsigned char	cr;
	unsigned char	i;
	ENTRY_BUFFER	Entry_buffer;
	unsigned short	lg_code;
	wIconList		IconLst;

	memclr(&IconLst, sizeof(IconLst));

	// Init table from const
	InitDefaut(_ON_,1);

	lg_code = PSQ_Give_Language();


	Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_RUN_BATCH, lg_code);

	for (i=0 ; i < ELVEC(NavigationBatchCapt) ; i++ )
	{
		Menu.tab[i] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationBatchCapt[i].itemlabel, lg_code);
	}

	// Call navigation time-out 30 secs
	Menu.tab[i] = NULL;

	G_List_Entry(&Menu);

	ttestall(ENTRY,0);
	cr=Get_Entry(&Entry_buffer);

	switch(cr)
	{
		case CR_ENTRY_OK :
			ACCES_FCT0 (NavigationBatchCapt[Entry_buffer.d_entry[0]].function);
			break;
	}
	return(cr);
}

//===========================================================================
void CUMORE_BatchCapt()
{
	int Protocol_Type;

	// Mixed Communication with ISO8583 and SPDH
	Protocol_Type = Host_Comm_Protocol();
	if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
	{
		CUMORE_BatchCapt_Iso8583();
	}
	else
	{
		// CUMORE_BatchCapt_Spdh();
	}
}



//===========================================================================
//! \brief This function erases the batch data file.
//===========================================================================
static void CUMORE_BatchRAZ(void)
{
	int  retour;

	retour = CUDISK_CreateDisk();
	if (retour == FS_OK)
	{
		// Erase transaction file
		Del_Transaction_File(&Transac_File);

		// Unmount the volume
		CUDISK_UnmountDisk();

	}
}


//===========================================================================
//! \brief This function initialise the serial number of the terminal.
//===========================================================================
static void CUMORE_Enter_Terminal_ID (void)
{

}

//===========================================================================
//! \brief This function resets the database and the keys.
//===========================================================================
static void CUMORE_Reset(void)
{
	char *ptrDummy = 0;

	PAR_InitParam(C_PARAM_INIT_APLI, ptrDummy);
	PAR_InitParam(C_PARAM_INIT_DEFAULT, ptrDummy);

	PAR_ResetMarkList();
	CUPAR_ResetAdditionnalICS();
	CUPAR_ResetAdditionnalAID();
	CUPAR_ResetAdditionnalKRevok();

	CUPAR_InitDefFiles (FALSE);
}

//===========================================================================
//! \brief This function dumps the database from the AID parameters.
//===========================================================================
static void CUMORE_Dump_AID (void)
{
	unsigned int  i_l_NumMark = C_TAG_AID;

	CUTERMprintLine("AID params :\n");
	CUPAR_Tag_Dump(i_l_NumMark);
}

//===========================================================================
//! \brief This function dumps the database from the general parameters.
//===========================================================================
static void CUMORE_Dump_GParam     (void)
{
	CUTERMprintLine("General params :\n");
	CUPAR_TLVTree_Dump(C_TREE_APPLI);
}

//===========================================================================
//! \brief This function reload the parameters with the default values.
//===========================================================================
static void CUMORE_Default(void)
{
	int found;
	char *ptrDummy = 0;
	DataElement elt;

	CUMORE_Reset();

	PAR_InitParam(C_PARAM_DEFAULT, ptrDummy);

	CUPAR_InitDefFiles (TRUE);

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
	if (found)
		usDefaultCurrency  = (elt.ptValue[0] << 8) + elt.ptValue[1];

	// For real card : No delay
	ucDelayAfterAtr = FALSE;
}

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function manages the demo mode selection menu.
//===========================================================================
static void CUMORE_Demo_Mode(void)
{
	T_CUTERMkey		key;
	int				merchLang;
	unsigned short	mask = 0;
	byte			b_l_TimeOut;
	unsigned char	msg[100];
	unsigned char	*pc_line1, *pc_line2;
	wStructListe	Menu;
	ENTRY_BUFFER	entry_buffer;
	unsigned char	cr_entry;
	cGuiStructList	MenuWgui;
	int				index;

	CUTERMclearDisplay();
	merchLang = PSQ_Give_Language();
	key = CU_VALID; /* init =/= CANCEL */

	if (ct_SystemSupportToolWare == FALSE)
	{
		ucAdvancedMode = FALSE;
		pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_NOT_SUPPORTED, merchLang);
		pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_YOUR_SYSTEM, merchLang);
		memset(msg, 0, sizeof(msg));
		sprintf(msg, "%s\n%s", pc_line1, pc_line2);
		CUTERMdisplayLine(0, msg, LEFT, (char *)"w");

		CUTERM_Wait_function_key(2, mask, &key);

		return;
	}
	

	// Enter type of ticket required
	pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_USE_DEMO_MODE, merchLang);
	pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_POS_ADVANCED, merchLang);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pc_line1, pc_line2);
	CUTERMdisplayLine(0, msg, LEFT, (char *)"w");


	key = CU_VALID; /* init =/= CANCEL */
	// Init timeout to 10s
	b_l_TimeOut = 10;
	mask = MASK_ANNULATION | MASK_SKCORR | MASK_SK2 | MASK_VALIDATION | MASK_SKVAL |MASK_SK3;

	// Waits 10s with mask
	if (CUTERM_Wait_function_key(b_l_TimeOut, mask, &key) == TRUE)
	{
		//char * PtrMsg;
		unsigned short mask = 0;

		if ((key == T_ANN) ||
			(key == T_CORR) ||
			(key == T_SK2))
		{
			ucAdvancedMode = FALSE;
			CUTERMclearDisplay();
			pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_POS_DEMO, merchLang);
			pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_SELECTED, merchLang);
			memset(msg, 0, sizeof(msg));
			sprintf(msg, "%s\n%s", pc_line1, pc_line2);
			CUTERMdisplayLine(0, msg, LEFT, (char *)"w");
			CUTERM_Wait_function_key(2, mask, &key);
		}
		else if ((key == T_VAL) ||
			(key == T_SK3))
		{
			ucAdvancedMode = TRUE;
			CUTERMclearDisplay();
			pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_ADVANCED_DEMO, merchLang);
			pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_SELECTED, merchLang);
			memset(msg, 0, sizeof(msg));
			sprintf(msg, "%s\n%s", pc_line1, pc_line2);
			CUTERMdisplayLine(0, msg, LEFT, (char *)"w");
			CUTERM_Wait_function_key(2, mask, &key);
		}
	}
	// else time-out

	CUTERMclearDisplay();
	

}
#endif /* _TOOLWARE_ */

//===========================================================================
//! \brief This function manages the printing of the receipt of the current ICS.
//===========================================================================
static void CUMORE_Dump_ICS(void)
{
	unsigned short lg_code;
	unsigned char msg[100];
	unsigned char *pc_line1, *pc_line2;

	// Retreive language code
	CUDB_Get_cardholder_language (&lg_code);
	if (lg_code > C_NBLANGHOLDER)
	{
		lg_code = 0;
	}

	CUTERMclearDisplay();

	pc_line1 = CUMESS_Read_Message(ICS_TABLE, ICS_MESS_PRINTING_1, lg_code);
	pc_line2 = CUMESS_Read_Message(ICS_TABLE, ICS_MESS_IN_PROGRESS, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pc_line1, pc_line2);
	CUTERMdisplayLine(0, msg, LEFT, (char *)"w");


	{
		CUPAR_Print_ICS_Config();
	}

	CUTERMclearDisplay();
}

//===========================================================================
//! \brief This function sends one financial record.
//! \param[in] hInputTree : Input TLV tree containing the financial transaction
//! read in the batch file.
//! \return
//! - TRUE : The transmission is successful.
//! - FALSE : in case of error.
//===========================================================================
static int CUMORE_Send_Financial_Record (TLV_TREE_NODE hInputTree)
{
	DataElement elt;
	unsigned short transfer_ok, found;
	TLV_TREE_NODE hTree,hTreeSR;
	unsigned char ISC_len;

	transfer_ok = 0;
	hTreeSR = NULL;
	hTree = TlvTree_New(0);

	if ((hTree != NULL) && (hInputTree != NULL))
	{
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AIP, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ATC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_USAGE_CONTROL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CRYPTOGRAM_INFORMATION_DATA, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVM_LIST, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVR_RESULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_IFD_SERIAL_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DEFAULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DENIAL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		} */

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_ONLINE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST_LEN, &elt);
		if (found)
		{
			ISC_len = elt.ptValue[0];
			// Bad storage of Issuer Script results
			if (ISC_len > 0)
			{
				/* elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST_LEN;
				elt.length  = 1;
				elt.ptValue = &(batch_record.record.financial_record.new_data.ISC_len);*/
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

				/* elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST;
				elt.length  = batch_record.record.financial_record.new_data.ISC_len;
				elt.ptValue = batch_record.record.financial_record.new_data.ISC;*/
				found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST, &elt);
				if (found)
				{
					elt.length = ISC_len;
					TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
				}
			}
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_CAPABILITIES, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TVR, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Add TSI to transaction file
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TSI, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_CRYPTOGRAMME_AC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_UNPREDICTABLE_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ACQUIRER_IDENTIFIER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_AUTH_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.financial_record.exist_data.AmAuth, TabAmount);
		elt.ptValue = TabAmount; */
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_AUTH_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_OTHER_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.financial_record.exist_data.AmOth, TabAmount1);
		elt.ptValue = TabAmount1;*/
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_OTHER_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EFFECTIVE_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EXPIRATION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AUTHORISATION_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AUTHORISATION_RESPONSE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_COUNTRY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_MERCHANT_CATEGORY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_POS_ENTRY_MODE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Point of Service Entry Mode
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CUST_POS_ISO8583_93, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_COUNTRY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_IDENTIFICATION, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		} */
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_CURRENCY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TIME, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Issuer Application Data 0x9F10
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_APPLICATION_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Amount, Authorised 0x9F02 (numeric)
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_AUTH_NUM, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Amount, Other 0x9F03 (numeric)
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_OTHER_NUM, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// AID : 4F
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AID_ICC, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Service Code : 5F30
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_SERVICE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Sequence Counter : 9F41
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_SEQ_COUNTER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Track 2 : 57
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRACK2_EQU_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Transaction Currency Exponent : 5F36
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_CURRENCY_EXP, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Application Version Number : 9F09
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_VERSION_NUMBER_TERMINAL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/*
		// Add Application Identifier : 9F06
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AID_TERMINAL, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}*/
		/*& END SMO/ETU/05/20028/MA */

		// TAG_TRANSACTION_FORCED_ACCEPTANCE is tested in Script CM.082
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_FORCED_ACCEPTANCE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* elt.tag     = TAG_COMM_MESSAGE_RETRANSMISSION;
		elt.length  = 1;
		elt.ptValue = &RetransmitIndicator;
		TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length); */
		/*& END SMO/ETU/05/20028/MA */

		// Add ICC dynamic number in batch file
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ICC_DYNAMIC_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Mixed Communication with ISO8583 and SPDH
		// Send record
		hTree = EMVCUST_Build_transac_download_TLVTree(&hTree);

		hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

		found = CUSERV_Extract_Element_TLV_Tree(&hTreeSR, TAG_COMM_STATUS_CODE, &elt);

		transfer_ok = (found && (*(elt.ptValue) == 0));

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);
		TlvTree_ReleaseEx(&hTreeSR);

	}

	return (transfer_ok);

}

//===========================================================================
//! \brief This function sends one advice record.
//! \param[in] hInputTree : Input TLV tree containing the advice transaction
//! read in the batch file.
//! \return
//! - TRUE : The transmission is successful.
//! - FALSE : in case of error.
//===========================================================================
static int CUMORE_Send_Advice_Record (TLV_TREE_NODE hInputTree)
{
	DataElement elt;
	unsigned short transfer_ok, found;
	TLV_TREE_NODE hTree,hTreeSR;
	unsigned char ISC_len;

	transfer_ok = 0;
	hTree = TlvTree_New(0);
	hTreeSR = NULL;

	if ((hTree != NULL) && (hInputTree != NULL))
	{
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AIP, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ATC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_USAGE_CONTROL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CRYPTOGRAM_INFORMATION_DATA, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVM_LIST, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVR_RESULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_IFD_SERIAL_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DEFAULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DENIAL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_ONLINE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST_LEN, &elt);
		if (found)
		{
			ISC_len = elt.ptValue[0];
			// Bad storage of Issuer Script results
			if (ISC_len > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

				found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST, &elt);
				if (found)
				{
					elt.length = ISC_len;
					TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
				}
			}
		}

		/* if (batch_record.record.advice_record.adv_new_data.ISC_len > 0)
		{
			elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST_LEN;
			elt.length  = 1;
			elt.ptValue = &(batch_record.record.advice_record.adv_new_data.ISC_len);
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

			elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST;
			elt.length  = batch_record.record.advice_record.adv_new_data.ISC_len;
			elt.ptValue = batch_record.record.advice_record.adv_new_data.ISC;
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		} */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_CAPABILITIES, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TVR, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_CRYPTOGRAMME_AC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_UNPREDICTABLE_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ACQUIRER_IDENTIFIER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_AUTH_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.advice_record.adv_exist_data.AmAuth, TabAmount);
		elt.ptValue = TabAmount; */
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_AUTH_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_OTHER_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.advice_record.adv_exist_data.AmOth, TabAmount1);
		elt.ptValue = TabAmount1; */
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_OTHER_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EFFECTIVE_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EXPIRATION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AUTHORISATION_RESPONSE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_MERCHANT_CATEGORY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_POS_ENTRY_MODE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_COUNTRY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_IDENTIFICATION, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_CURRENCY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TIME, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Issuer Application Data 0x9F10
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_APPLICATION_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Track 2 : 57
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRACK2_EQU_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_FORCED_ACCEPTANCE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* elt.tag = TAG_COMM_MESSAGE_RETRANSMISSION;
		elt.length  = 1;
		elt.ptValue = &RetransmitIndicator;
		TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length); */
		/*& END SMO/ETU/05/20028/MA */

		// Mixed Communication with ISO8583 and SPDH
		// Send record
		hTree = EMVCUST_Build_transac_advice_TLVTree(&hTree);

		hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

		found = CUSERV_Extract_Element_TLV_Tree(&hTreeSR, TAG_COMM_STATUS_CODE, &elt);

		transfer_ok = (found && (*(elt.ptValue) == 0));

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);
		TlvTree_ReleaseEx(&hTreeSR);
	}

	return (transfer_ok);

}

//===========================================================================
//! \brief This function manages the printing of the transaction log of the ICC.
//===========================================================================
static void CUMORE_TransactionLog(void)
{
	unsigned short TransactionLogAsked;
	unsigned char    buf[11];
	TLV_TREE_NODE hInputTree;
	TLV_TREE_NODE hOutputTree;
	unsigned char TypeAppli[2];
	unsigned char EngAppliSel;


	// release global TLV tree
	TlvTree_ReleaseEx(&CUMORE_Tree);

	CUMORE_Tree = TlvTree_New(0);

	if(CUMORE_Tree != NULL)
	{
		TransactionLogAsked = TRUE;
		ShortToChar(TransactionLogAsked,buf);
		TlvTree_AddChild(CUMORE_Tree, TAG_CUST_TRLOG_IS_ASKED, (unsigned char *)buf, 2);

		hInputTree = TlvTree_New(0);
		if(hInputTree != NULL)
		{
			ShortToChar(CustApplicationNumber,TypeAppli);
			TlvTree_AddChild(hInputTree, TAG_ENG_CUSTOM_APPLI_TYPE, (unsigned char*) &TypeAppli, 2);

			EngAppliSel =0;
			TlvTree_AddChild(hInputTree, TAG_ENG_APPLI_SEL_ALREADY_DONE, (unsigned char*) & EngAppliSel, 1);

			hOutputTree = NULL;
			Engine_DoReadTransactionLog(hInputTree,&hOutputTree);

			// Release local TLV tree
			TlvTree_ReleaseEx(&hInputTree);
			TlvTree_ReleaseEx(&hOutputTree);
		}		
	}
}

//! @}


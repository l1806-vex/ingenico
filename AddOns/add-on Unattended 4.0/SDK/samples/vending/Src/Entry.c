/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.H"
#include "UCMTELIUM.h"

#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"
#include "UCMSTARTDLL.H"

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

static const unsigned char tcAppName_g []    = "APP_VENDING";

extern int MainAppliUCMC_IAC(unsigned int iSize_p, T_UCMC_IAC_SERVICE *pdata_p);
//// Global variables ///////////////////////////////////////////
int giDisplayBackColor;
int giIccBackColor;
int giDisplayCanal;
int giDisplayICLType;
  
/**************************/
/*  pauze of 1sec         */
/**************************/

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
						j = iLIBUCM_Icc_Status( ucChannel , (unsigned char *)&cTemp2[ 0 ] );
						
						sprintf( cTemp, "Status%d= %d ret=%d",ucChannel , cTemp2[ 0 ],j ) ;
						
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
								memcpy ( sInputCommand.data, cTemp2, 3 ) ;

								
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



char Pinpad_Menu(void)
{
	ENTRY_BUFFER       buf;
	StructList         Menu;
	
	unsigned char      Cr;
	unsigned char      ucChannel;

	char cTemp[ 60 ], cTemp2[ 50 ];
	
	int j, k;
	T_UCM_ENTRY_PPAD     sPPad ;
	
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
				ucChannel = 0 ;

				iLIBUCM_Print_Message( UCMC_PRINT, "Input" );
				
				j = iLIBUCM_Pinpad_Open( UCMC_PPAD, "r" ) ;

				if ( j == FCT_OK )
				{
					memset ( &sPPad, 0x00, sizeof ( sPPad ) ) ;
					sPPad.ucTimeout = 5 ;   /* 5 sec */
					j = iLIBUCM_Pinpad_Input(ucChannel , UCMPPAD_CLOSE_AT_END, &sPPad ) ;

					if ( j == FCT_OK )
					{
						sprintf( cTemp, "input = %c", sPPad.uctResultBuf [ 0 ] ) ;
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
				}

				for( ucChannel=0; ucChannel < UCMC_PINPADMAX; ucChannel++ )
				{
					if( iLIBUCM_Pinpad_Exist(ucChannel) > 0 )
					{
						j = iLIBUCM_Pinpad_Open( ucChannel, "r" ) ;

						if( j == FCT_OK )
						{
							j = iLIBUCM_Pinpad_Input(ucChannel , 2, (void*)cTemp ) ;
						}
						cTemp2[ 0 ] = 0;
						if( j == FCT_OK )
						{
							for( k=0; k < 2; k++)
								sprintf( &cTemp2[ k*2 ], " %c", cTemp[k] ) ;						
						}
						
						sprintf( cTemp, "input%d= %d %s", ucChannel ,j , &cTemp2[0] ) ;

						j = iLIBUCM_Pinpad_Close( ucChannel ) ;
						
						iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
					}
				}
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
		Menu.tab[3] = NULL;
		
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
		Menu.tab[1]  = (unsigned char *)"On 5s";
		Menu.tab[2]  = (unsigned char *)"Off";
		Menu.tab[3] = NULL;
		
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

			case 1:
				sBuz.ucCmd = UCMC_BUZ_NORMAL;
				sBuz.usDelay = 10;
				sprintf( cTemp, "On = %d\n", iLIBUCM_BUZZER_Cmd( &sBuz ) );
				iLIBUCM_Print_Message( UCMC_PRINT, cTemp );
				break;
			case 2:
				sBuz.ucCmd = UCMC_BUZ_OFF;
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

/* ======================================================================== */
/* Functions   Back light color                                             */
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

	iRet = STOP;
	switch( ucChannel_p )
	{
      case 0: /* IUP250 IUC180 IUC180B */
         if( giDisplayBackColor > 0 )
         {
            iRet = iLIBUCM_Display_Backlight_Color( UCMC_DISPLAY, &sBlkColor );
         }
      break;

      case 1:/* IUR250 */
         if( giIccBackColor > 0 )
         {
            iRet = iLIBUCM_Icc_Backlight_Color( UCMC_ICC, &sBlkColor );
         }
      break;
	}

	return( iRet );
}


int more_function(NO_SEGMENT no,void *p1,void *p2)
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


int after_reset ( NO_SEGMENT no, void *p1, S_TRANSOUT * etatseq )
{
S_TRANSOUT                 etatout;
unsigned char              chgt;
TYPE_CHGT                  type;
int                        iSize ;
T_UCMC_IAC_HOST2           sHostCmd ;
T_UCMC_IAC_HOST2           sHostCmdAnsw ;
T_UCMHOST_DA_PARAMV5			sParam;
T_UCMHOST_DA_PARAM_MSGV3	sParamMsg;
T_UCMC_IAC_EVENT			   sEvent;
int						      iRet;

   giDisplayBackColor = 0;
   giIccBackColor = 0;
   giDisplayCanal = 0;
   giDisplayICLType = 0;
   
	memcpy (&etatout, etatseq, sizeof(etatout));
	memcpy (etatseq, &etatout, sizeof(etatout));

	first_init ( no, &chgt, (unsigned char *)&type);

   /* contactless display */
   iRet = iLIBUCM_Display_Exist(UCMC_DISPLAY_ICL);
   switch( iRet )
   {
      case PARAM_TYPE_IUC180:
      case PARAM_TYPE_IUC180B:
         giDisplayCanal = UCMC_DISPLAY_ICL; /* or UCMC_DISPLAY_ICC */
      break;
      
      case PARAM_TYPE_IUC150: /* IUC150 special = ICU180 transparent as device */
      case PARAM_TYPE_TPASS:
         giDisplayCanal = UCMC_DISPLAY_ICL; /* or UCMC_DISPLAY_ICC */
         giDisplayICLType = 1; /* special for graphic driver on external contacless device and iLIBUCM_Display_Graphic_Start() */
      break;
   }

   /* default display even if default display is contactless  UCMC_DISPLAY_ICC exist always */
   iRet = iLIBUCM_Display_Exist(UCMC_DISPLAY_ICC);
   switch( iRet )
   {
      case PARAM_TYPE_IUC180:
      case PARAM_TYPE_IUC180B:
      case PARAM_TYPE_IUC150: /* IUC150 special = ICU180 transparent as device */
      case PARAM_TYPE_TPASS:
         giDisplayCanal = UCMC_DISPLAY_ICC; /* or UCMC_DISPLAY_ICL */
      break;
      case PARAM_TYPE_IUP250:
      case PARAM_TYPE_UPP:
         giDisplayCanal = UCMC_DISPLAY_ICC; /* or UCMC_DISPLAY_PPAD */
      break;

      case PARAM_TYPE_CAD30VR:
         giDisplayCanal = UCMC_DISPLAY_ICC;
      break;
      
      case PARAM_TYPE_HOST:        
      default:
         if( iRet < 0)
         {
            if( iRet > 0 )
            {
               giDisplayCanal = UCMC_DISPLAY_ICL;
            }
         }
         else
         {
            giDisplayCanal = UCMC_DISPLAY;
         }        
      break;
   }

	sHostCmd.usHostCmd = UCMHOSTLIB_CMD_PARAM_DA_MSG ;
	sHostCmd.usHostWaitTimeout = 10 ; // seconds
	sHostCmd.usSize = sizeof( sParamMsg ) ;
	UTIL_InitStruct_ParamVmcMsg ( &sParamMsg ) ;
	memcpy(&sHostCmd.u.ucBuf[0],&sParamMsg,sizeof(sParamMsg));
	
	iSize = ( sizeof( T_UCMC_IAC_HOST2 ) // struct size - data max size + real data size */
				- UCMC_IAC_HOST2_BUFFER_SIZE) 
				+ sizeof( sParamMsg ) ;

	if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) != FCT_OK )
	{
		iLIBUCM_Display_Message ( UCMC_DISPLAY, "Dll protocol\ncannot be\n initialised\n", 10 );
	}


	if (1)   // the application is able to work ( prices set...) and to give Dll settings
	{
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

			iLIBUCM_Display_Message ( UCMC_DISPLAY, "Dll protocol\ncannot be\n initialised\n", 10 );
		}

	}

   /* if backlight not used for EVA LED */
   if( sParam.ucEVA == 0 )
   {
      giDisplayBackColor = iLIBUCM_Display_Backlight_Color_Exist( UCMC_DISPLAY ) ;
      giIccBackColor = iLIBUCM_Display_Backlight_Color_Exist( UCMC_ICC ) ;      
   }
   else
   {
      giDisplayBackColor = 0;  /* managed by DLL Vending */
      giIccBackColor = 0;     /* managed by DLL Vending */
   }


	/* adding service Warning: UCMC_EVENT_TYPE_KEY service decrease perfomance */
	sEvent.usType = UCMC_EVENT_TYPE_USB;
	sEvent.usRuf1 = 0;
	sEvent.usRuf2 = 0;
	sEvent.usRuf3 = 0;

	iRet = iLIBUCM_Device_Event_Service_Set( &sEvent ) ;

	return (FCT_OK);
}



int is_state(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
	S_ETATOUT etatout;
	int retour; 
	
	memcpy (&etatout, etatseq, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.response = REP_OK;
	memcpy (etatseq, &etatout, sizeof(etatout));
	retour = is_name (no, PT_NULL, etatseq);
	return (retour);
}



int is_name(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
	S_ETATOUT etatout;
	
	memcpy ((char *)&etatout, (char *)etatseq, sizeof(etatout));
	strcpy((char *)etatout.returned_state[etatout.response_number].appname, (char *)tcAppName_g );
	etatout.returned_state[etatout.response_number].no_appli = no;
	etatout.response_number++;
	memcpy (etatseq, &etatout, sizeof(etatout));
	return (FCT_OK);
}



int give_your_domain(NO_SEGMENT no,void *p1,S_INITPARAMOUT *param_out)
{
	S_INITPARAMOUT etatout;
	
	memcpy (&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].mask     = MSK_MDP|MSK_SWIPE|MSK_TYPE_PPAD|MSK_PINPAD|MSK_STANDARD|MSK_LANGUE|MSK_FRMT_DATE|MSK_DATE;
	etatout.returned_state[etatout.response_number].application_type = TYP_EXPORT;
	etatout.response_number++;
	memcpy (param_out, &etatout, sizeof(etatout));
	return (FCT_OK);
}



int is_delete(NO_SEGMENT no,void *paramin,S_DELETE *paramout)
{
	paramout->deleting=DEL_YES;
	return (FCT_OK);
}



int state (NO_SEGMENT noappli,void *p1,void *p2)
{
	return (FCT_OK);
}



int mcall (NO_SEGMENT noappli,void *p1,void *p2)
{
	return (FCT_OK);
}



int consult (NO_SEGMENT noappli,void *p1,void *p2)
{
	return (FCT_OK);
}



int time_function (NO_SEGMENT noappli,void *p1,void *p2)
{
	return (FCT_OK) ;
}



int file_received(NO_SEGMENT no,S_FILE * param_in,void *p2)
{
	return (FCT_OK);
}



int is_evol_pg(NO_SEGMENT noappli, void *p1, S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int       retour;
	memcpy(&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.response=REP_OK;
	memcpy(param_out,&etatout,sizeof(etatout));
	retour = is_name (noappli, PT_NULL, param_out);
	return(FCT_OK);		 
}



int is_time_function(NO_SEGMENT noappli, void *p1, S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int       retour;
	memcpy(&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.response=REP_OK;
	memcpy(param_out,&etatout,sizeof(etatout));
	retour = is_name (noappli, PT_NULL, param_out);
	return(FCT_OK);		 
}



int is_change_init(NO_SEGMENT noappli, void *p1, S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int       retour;
	memcpy(&etatout, param_out, sizeof(etatout));
	// accept all 
	etatout.returned_state[etatout.response_number].state.mask=0;
	memcpy(param_out,&etatout,sizeof(etatout));
	retour = is_name (noappli, PT_NULL, param_out);
	return(FCT_OK);		 
}



int modif_param(NO_SEGMENT noappli, S_MODIF_P *param_in, void *p2)
{
	S_MODIF_P param_changed;
	
	memcpy(&param_changed, param_in,sizeof(param_changed));
	return(FCT_OK);
}


int is_for_you_after ( NO_SEGMENT no, S_TRANSIN * p1, S_CARDOUT * Cardseq )
{
	S_CARDOUT        card_out ;
	unsigned char    ucPriority;
	HISTORIC         HistoricalBytes ;

	ucPriority  = CARD_PROCESSED ; // priority low to display error message

	memcpy (&card_out, Cardseq, sizeof ( card_out ) ) ;

	if ( iLIBUCM_Icc_Open( UCMC_ICC, "rw" ) == FCT_OK )
	{
		iLIBUCM_Icc_PowerDown ( UCMC_ICC, UCMCICC_POWER_DOWN ) ;	// to be compatible with all managers

		if ( iLIBUCM_Icc_PowerOn ( UCMC_ICC , UCMCICC_POWER_ON, &HistoricalBytes )  == FCT_OK )
		{
			// *TODO* check ICC (use historical bytes, some APDU commands..
			
			// the App accepts ICC
			ucPriority     = CARD_PRIORITY ;

			iLIBUCM_Icc_PowerDown ( UCMC_ICC, UCMCICC_POWER_DOWN ) ;
		}

		iLIBUCM_Icc_Close ( UCMC_ICC ) ;
	}
	
	/* MAJ S_CARDOUT */
	strcpy (card_out.returned_state[card_out.response_number].appname , (char*) tcAppName_g ) ;

	card_out.returned_state[card_out.response_number].no_appli = no ;
	card_out.returned_state[card_out.response_number].cardappnumber = 1 ;

	strcpy (card_out.returned_state[card_out.response_number].cardapp [0].cardappname, (char*) tcAppName_g ) ;
	card_out.returned_state[card_out.response_number].cardapp[0].priority = ucPriority ;

	card_out.response_number++;

	memcpy ( Cardseq, &card_out, sizeof ( card_out ) ) ;      

	return (FCT_OK);
}



int debit_non_emv (NO_SEGMENT no , S_TRANSIN *param_in, S_TRANSOUT *param_out )
{
	char                   cMess [ 100+1 ] ;
	char                   cErrMess [ 100+1 ] ;

	int                    iSize ;
	int                    iWhat ;
	unsigned short         usEvent ;

	unsigned char          ucState ;
	unsigned long          ulEpuseBalance ;
	unsigned long          ulCreditAmount;
	unsigned char          ucMultiVend ;
	unsigned char		   bIccOK;
	unsigned char		   bWaitReply;
	unsigned char          ucOneTime ;
	unsigned char          ucStatusIcc;

	T_UCMHOST_DEBIT        sDebit ;
	T_UCMHOST_R_DEBIT      sRDeb ;
	T_UCMHOST_DA_EPURSE_BALANCEV3        sEpurseBalance ;
	T_UCMHOST_DA_CR_EPURSE_REVALUEV3     sEpurseRevalue;
	T_UCMHOST_DA_CR_REC_EPURSE_REVALUE sRecEpurseRevalue;	
	T_UCMC_IAC_HOST2        sHostCmd ;
	T_UCMC_IAC_HOST2        sHostCmdAnsw ;
	HISTORIC               HistoricalBytes ;



	bWaitReply		   = FALSE;
	ucMultiVend        = 0 ;
	ulCreditAmount     = 0 ;
	cErrMess[0]=0;
	ulEpuseBalance     = 100 ;

 
	if (  iLIBUCM_Icc_Open( UCMC_ICC, "rw" ) == FCT_OK  )			// open ICC media
	{
			iLIBUCM_Icc_PowerDown ( UCMC_ICC, UCMCICC_POWER_DOWN ) ;	// to be compatible with all managers

		//check ICC
		if (iLIBUCM_Icc_PowerOn ( UCMC_ICC, UCMCICC_POWER_ON, &HistoricalBytes )==FCT_OK)
		{
			// *TO DO* check ICC (use historical bytes, some APDU commands..
			
			// the App accepts ICC
			bIccOK=TRUE;
		}
		else
		{
			bIccOK=FALSE;
		}
		
		memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
		memset ( &sDebit, 0x00, sizeof ( T_UCMHOST_DEBIT ) ) ;
		iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

		if (iWhat==UCMCPAY_ASK_EPURSE_BALANCE)
		{
			ucState=STATE_EPURSE_BALANCE;
		}
		else
		{
			ucState=STATE_REMOVE_CARD;
		}
			
		do
		{
			switch(ucState)
			{
				case STATE_EPURSE_BALANCE:	// read and display Balance
				{
					iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_BLUE);
					iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_BLUE);

					bWaitReply=FALSE; //no reply from DLL	

					// ***balance reading must be implemented here
					sHostCmd.usHostCmd = UCMHOSTLIB_CMD_EPURSE_BALANCE ;
					sHostCmd.usHostWaitTimeout = 10 ; /* 10 secondes */
					sHostCmd.usSize = sizeof( T_UCMHOST_DA_EPURSE_BALANCEV3 ) ;
					memset(&sEpurseBalance,0,sizeof(T_UCMHOST_DA_EPURSE_BALANCEV3));
					if (bIccOK)
					{
						sEpurseBalance.ucCr            = UCMHOST_CR_OK ;
						sEpurseBalance.ucAllowRevalue	=1 ;  
						sEpurseBalance.ucAllowRefund	=1 ;
						sEpurseBalance.ucAllowMultiVend	=1;
						sEpurseBalance.ucAllowDisplayBalance =1 ;
						sEpurseBalance.ulEpurseBalance = ulEpuseBalance ; 
						memcpy ( sEpurseBalance.tucCurrencyCode, "978", 3 ) ;
						memcpy ( sEpurseBalance.tucLanguageCode, "250", 3 ) ;
						if (sEpurseBalance.ucAllowRevalue)
						{
							sEpurseBalance.ulRevalueLimitBalance=5000 ;	// max value of Epurse Balance (50€ for ex)
							sEpurseBalance.ulRevalueLimitAmount=sEpurseBalance.ulRevalueLimitBalance=200; // max value of Epurse Balance (2€ for ex)
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
							+ sizeof( T_UCMHOST_DA_EPURSE_BALANCEV3 ) ;

					if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) == FCT_OK )
					{
						if (bIccOK)
						{
							sprintf(cMess,"\nBAL %5ld.%02ld"
										  "\nYOUR CHOICE ? **",ulEpuseBalance/100,ulEpuseBalance%100);
							iLIBUCM_Display_Message ( UCMC_DISPLAY, cMess, 0 ) ;
							ucState = STATE_WAIT_EVT ;
						}
						else
						{
							strcpy(cErrMess,"  INVALID CARD");
							ucState = STATE_REMOVE_CARD ;
						}

					}
					else
					{
						strcpy(cErrMess,"INTERNAL ERROR");
						iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nBALANCE KO", 100 ) ;
						ucState = STATE_REMOVE_CARD ;
					}	
				}break;
				 
				case STATE_WAIT_EVT: // wait for event (ICC or DLL instructions)
				{


					memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
					memset ( &sDebit, 0x00, sizeof ( T_UCMHOST_DEBIT ) ) ;
					usEvent = UCMMULTI_TTESTALL_ICC | UCMMULTI_TTESTALL_HOST ;

					if( iLIBUCM_Device_Ttestall( &usEvent, 30000) == UCMTTESTALL_CR_OK_EVENT )
					{
						if( (usEvent & UCMMULTI_TTESTALL_HOST) != 0 )
						{

							iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

							switch( iWhat )
							{
								case UCMCPAY_ASK_EPURSE_BALANCE :		ucState=STATE_EPURSE_BALANCE;break;  // ask for balance
								case UCMCPAY_SOLV :						   ucState=STATE_DEBIT;break;	          // selection done, debit card
								case UCMCPAY_RECORD:					      ucState=STATE_DEBIT_RECORD;break;    // distribution finished
								case UCMCPAY_REVALUE_EPURSE :	         ucState=STATE_REVALUE;break;         //do revalue epurse
								case UCMCPAY_RECORD_REVALUE_EPURSE :	ucState=STATE_REVALUE_RECORD;break;  //revalue finished
								case UCMCPAY_HOST_REMOVE_CARD :			ucState=STATE_REMOVE_CARD;break;     // cancelled
								default:
									iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nEVT UNKNOWN", 100 ) ;
									strcpy(cErrMess,"INTERNAL ERROR");
									ucState = STATE_REMOVE_CARD ;
									break;
							}

						}


						if(	((usEvent & UCMMULTI_TTESTALL_ICC) != 0 )
							&&	(bWaitReply==FALSE)		// not detect ICC removal during distribution or revalue
							)
						{
							ucState=STATE_END;
						}

					}
					else
					{
						iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nEVT KO", 100 ) ;
						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}
				}break;

				case STATE_DEBIT:
				{
					if ( ( sDebit.ucFunction == UCMHOST_FCT_SOLV ) && 
						  ( sDebit.u.tDaAskForDebit.ucCmd == UCMCPAY_SOLV ) )
					{
						ucMultiVend = sDebit.u.tDaAskForDebit.ucVendType ;

						if (sDebit.u.tDaAskForDebit.ucSelectionNotDefined==0)
						{
							/* epurse DEBIT */
							if (sDebit.u.tDaAskForDebit.uiSelectionPrice<=ulEpuseBalance)
							{
								ulEpuseBalance -= sDebit.u.tDaAskForDebit.uiSelectionPrice ;
								bIccOK=TRUE; // Debit OK
							}
							else
							{
								bIccOK=FALSE; // Debit KO
							}
							
							
							/******* RESPONSE ************/
							memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
							sRDeb.ucDiag       = FCT_OK ;
							sRDeb.ucFunction   = UCMHOST_FCT_SOLV ;
							sRDeb.usAppName    = no ;
							strcpy ( sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;
							memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
							memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
							sRDeb.tCurrency.posdec = 2 ;

							if ( bIccOK)
							{// debit ok
								sRDeb.ucCr         = UCMHOST_CR_OK ;
								sRDeb.ulAmount     = sDebit.u.tDaAskForDebit.uiSelectionPrice;
								sRDeb.ucCardInside = 1 ;
								sRDeb.u.sRDebitDa.ulEpurseBalance = ulEpuseBalance ;

								sprintf(cMess,"\nBAL %5ld.%02ld"
									  "\nVEND IN PROGRESS",ulEpuseBalance/100,ulEpuseBalance%100);
								iLIBUCM_Display_Message ( UCMC_DISPLAY, cMess, 0 ) ;
								ucState = STATE_WAIT_EVT ;
						
							}
							else
							{ // debit ko
								sRDeb.ucCr         = UCMHOST_CR_REFUSED ;   
								sRDeb.u.sRDebitDa.ulEpurseBalance = 0 ;
								
								strcpy(cErrMess,"     REFUSED");
								ucState = STATE_REMOVE_CARD ;
							}

							if ( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) == FCT_OK )
							{
								bWaitReply=TRUE;
							}
							else
							{
								iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nDEBIT KO", 100 ) ;
								strcpy(cErrMess,"INTERNAL ERROR");
								ucState = STATE_REMOVE_CARD ;
							}													

						}
						else
						{
							// product not defined in table price
							strcpy(cErrMess,"NOT DEFINED");
							ucState = STATE_REMOVE_CARD ;
						}

					}
					else
					{
						iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nDEBIT UNKNOWN", 100 ) ;
						ucState = STATE_REMOVE_CARD ;
					}
				}break;

				
				case STATE_DEBIT_RECORD : // distribution finished
				{
					bWaitReply=FALSE;
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
		
						sRDeb.ucCr         = FCT_OK ;
						sRDeb.ucDiag       = FCT_OK ;
						sRDeb.ucFunction   = UCMHOST_FCT_ENREG ;
						sRDeb.usAppName    = no ;
						strcpy ( sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;
						memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
						memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
						sRDeb.tCurrency.posdec = 2 ;
						sRDeb.u.sRDebitDa.ulEpurseBalance = ulEpuseBalance ;

						iLIBUCM_Icc_Status ( UCMC_ICC , &ucStatusIcc ) ;
						if ( ucStatusIcc == UCMC_STATUS_CARD_INSIDE )
						{	
							sRDeb.ucCardInside = 1 ;
						}
						else                                            
						{
							 sRDeb.ucCardInside = 0 ;   
						}

						if( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) ==FCT_OK )
						{
							if ( ucMultiVend &&  ( ucStatusIcc == UCMC_STATUS_CARD_INSIDE ) )  
							{
								ttestall ( 0, 50 ) ; /* To let time to DLL protocol to finalize the transaction with vending machine */
								iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

								if (iWhat==UCMCPAY_ASK_EPURSE_BALANCE)
								{
									ucState=STATE_EPURSE_BALANCE;
								}
								else
								{
									iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nMULTIVEND KO", 100 ) ;
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
								iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nRECORD KO", 100 ) ;
								strcpy(cErrMess,"INTERNAL ERROR");
								ucState = STATE_REMOVE_CARD ;
							}
							
					}
					else
					{
						iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nRECORD UNKNOWN", 100 ) ;
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
							sEpurseRevalue.ulEpurseBalance = ulEpuseBalance ; 
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

						if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) == FCT_OK )
						{
							bWaitReply=TRUE;
						}
						else
						{
							iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nREVALUE KO", 100 ) ;
							strcpy(cErrMess,"INTERNAL ERROR");
							ucState = STATE_REMOVE_CARD ;
						}
					}
					else
					{
						iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nREVALUE UNKNOWN", 100 ) ;
						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}	
				}
				break ;

				case STATE_REVALUE_RECORD :
				{
					bWaitReply=FALSE;
					if (	( sDebit.ucFunction == UCMHOST_FCT_REVALUE ) 
						&& 	( sDebit.u.tDaRecRevalue.ucCmd == UCMCPAY_RECORD_REVALUE_EPURSE ) 
						)
					{
						if ( sDebit.u.tDaRecRevalue.ucCrRevalue != 0 ) 
						{
							ulCreditAmount = 0 ; 
						}

						if (ulCreditAmount!=0)
						{
							// *TODO* Credit Card 
							bIccOK=TRUE;

							if (!bIccOK)
							{
								ulCreditAmount =0;
							}
							ulEpuseBalance = ulEpuseBalance + ulCreditAmount ;
										
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
									      "\n REVALUE",ulEpuseBalance/100,ulEpuseBalance%100);
							iLIBUCM_Display_Message ( UCMC_DISPLAY, cMess, 0 ) ;
						}
						else
						{
							iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nREVALUE RECORD\nKO", 100 ) ;
							strcpy(cErrMess,"INTERNAL ERROR");
							ucState = STATE_REMOVE_CARD ;
						}
					}
					else
					{
						iLIBUCM_Display_Message ( UCMC_DISPLAY, "DLL\nREVALUE RECORD\n UNKNOWN", 100 ) ;
						strcpy(cErrMess,"INTERNAL ERROR");
						ucState = STATE_REMOVE_CARD ;
					}	
				}break ;

				case STATE_REMOVE_CARD:
				{
					iLIBUCM_Icc_PowerDown ( UCMC_ICC, UCMCICC_POWER_DOWN ) ;

					ucOneTime=TRUE;
					do
					{

						iLIBUCM_Icc_Status ( UCMC_ICC , &ucStatusIcc ) ;
					
						if ( ucStatusIcc == UCMC_STATUS_CARD_INSIDE )
						{
							if (ucOneTime)
							{	
								ucOneTime=FALSE;
								if (cErrMess[0]==0)
								{
									strcpy(cErrMess,"   REMOVE CARD");
								}
								
								sprintf(cMess,"\n%s\n   REMOVE CARD",cErrMess);
								iLIBUCM_Display_Message( UCMC_DISPLAY, cMess, 0 ) ;
							}


						}

						usEvent = UCMMULTI_TTESTALL_ICC;
						iLIBUCM_Device_Ttestall(&usEvent, 100);

					}while ( ucStatusIcc == UCMC_STATUS_CARD_INSIDE );

					iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_GREEN);
					iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_BLACK);

					ucState=STATE_END;
				}break;

				case STATE_END:
				default:
				{
					ucState=STATE_END;
				}break;
			}
		}while (ucState!=STATE_END);

		// to inform DLL that card has been removed and terminal is in idle state
		sHostCmd.usHostCmd = UCMHOSTLIB_CMD_END_DEBIT ;
		sHostCmd.usHostWaitTimeout = 10 ; 
		sHostCmd.usSize = 0 ;

		iSize = ( sizeof( T_UCMC_IAC_HOST2 ) - UCMC_IAC_HOST2_BUFFER_SIZE ) ;

		if ( iLIBUCM_Pay_Host_Cmd ( iSize, &sHostCmd, &sHostCmdAnsw ) != FCT_OK )
		{
			 iLIBUCM_Display_Message ( UCMC_DISPLAY, "MSG END KO\n", 100 ) ;
		}

		iLIBUCM_Icc_Close ( UCMC_ICC ) ; 
		
	}


	param_out->noappli     = no;
	param_out->rc_payment  = PAY_OK;

	return ( STOP );
}



int fall_back (NO_SEGMENT noappli, S_TRANSIN *param_in, S_TRANSOUT *p2)
{
	return (FCT_OK);
}


typedef int (*T_SERVICE_FUNCTION)(unsigned int nSize, void*Data);




int give_interface(unsigned short no,void *p1,void *p2)
{
	service_desc_t MesServices[40];
	int i ;


	i = 0 ;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_NAME;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = GIVE_YOUR_DOMAIN;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MORE_FUNCTION;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = AFTER_RESET;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_STATE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_DELETE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = DEBIT_NON_EMV;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_FOR_YOU_AFTER;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = STATE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MCALL;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = CONSULT;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_EVOL_PG;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_TIME_FUNCTION;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = TIME_FUNCTION;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_CHANGE_INIT;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MODIF_PARAM;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = FILE_RECEIVED;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = FALL_BACK;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	/* Special UCM */
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = SERVICE_APPLI_UCMC;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)MainAppliUCMC_IAC;
	MesServices[i].priority  = 10;
	i++;


	
	ServiceRegister(i,MesServices);
	return (FCT_OK);
}

#ifdef _EFT30_
void entry(void)
{
	object_info_t info;
	
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
	give_interface(info.application_type, NULL, NULL);
}
#endif


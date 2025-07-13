/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.H"
#include "UCMTELIUM.h"

#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"
#include "UCMSTARTDLL.H"
//// Macros & preprocessor definitions //////////////////////////

static const unsigned char tcAppName_g []    = "APP_BANKING";


//// Global variables ///////////////////////////////////////////


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
						j = iLIBUCM_Icc_Status( ucChannel , (unsigned char*)&cTemp2[ 0 ] );
						
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
		Menu.tab[1]  = (unsigned char *)"Status";
		Menu.tab[2] = NULL;
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

			case 1:  /* Status */
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
	   case 0: /* IUP */
		   if( iLIBUCM_Display_Backlight_Color_Exist( UCMC_DISPLAY ) > 0 )
		   {
			   iRet = iLIBUCM_Display_Backlight_Color( UCMC_DISPLAY, &sBlkColor );
		   }
	   break;

	   case 1:/* IUC */
		   if( iLIBUCM_Icc_Backlight_Color_Exist( UCMC_ICC ) > 0 )
		   {
			   iRet = iLIBUCM_Icc_Backlight_Color( UCMC_ICC, &sBlkColor );
		   }
   	   break;

   }


   return( iRet );
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
S_TRANSOUT              etatout;
unsigned char           chgt;
TYPE_CHGT               type;
T_UCM_DEVICE			sDevice ;
T_UCMC_IAC_EVENT		sEvent;
int						iRet;
char					cTemp[200]; 
T_LIBUCM_DEVICE_STATUS sStatus;

	memcpy (&etatout, etatseq, sizeof(etatout));
	memcpy (etatseq, &etatout, sizeof(etatout));

	first_init ( no, &chgt, (unsigned char *)&type);

	/* adding service function key and LLT presh buton:  Warning: UCMC_EVENT_TYPE_KEY service decrease perfomance */
//	sEvent.usType = UCMC_EVENT_TYPE_KEY | UCMC_EVENT_TYPE_LLT_BT | UCMC_EVENT_TYPE_USB;
	sEvent.usType = UCMC_EVENT_TYPE_KEY | UCMC_EVENT_TYPE_USB;
	sEvent.usRuf1 = 0;
	sEvent.usRuf2 = 0;
	sEvent.usRuf3 = 0;
	iRet = iLIBUCM_Device_Ucm_Status( &sStatus );

	 if( iRet == FCT_OK)
	 {
		if( sStatus.ucUCM == 3 /* Maintenance */ )
		{
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
 
	/* HOST parameters */
	iLIBUCM_Device_Config_OPE( UCM_DEVICE_HOST, &sDevice );

	/* If host exist and host not defined */
	if( ( sDevice.ucType == 1 ) && ( sDevice.ucPilote == 0 ) && 
	( memcmp(&sDevice.uctNomDriver[0] ,"0xFFFF", 6) == 0) )
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
	/* Specific iLIBUCM_Display_Idle_Event( UCMC_DISPLAY, 1 );  0=stop event idle message */

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



int keyboard_event(NO_SEGMENT noappli,S_KEY *p1,S_KEY *p2)
{
	S_KEY keyA, keyB;
	
	memcpy(&keyA,p1,sizeof(keyA));
	memcpy(&keyB,p2,sizeof(keyB));
	switch (keyA.keycode)
	{
		case N0:
		case N1: 
		case N2:
		case N3: 
		case N4: 
		case N5: 
		case N6: 
		case N7: 
		case N8: 
		case N9: 
		case T_VAL :
		case T_POINT : 
			// inhibits these keys for International domain
			keyB.keycode = 0 ; 
		break; 
		case F1 : 
		case F2 : 
		case F3 : 
		case F4 : 
		case T_CORR :
		case T_ANN : 
		case NAVI_CLEAR : 
		case NAVI_OK : 
		case UP : 
		case DOWN : // return the same key value for keys above ! 
		case T_F :  // do not filter F key and return the same key ! 
			keyB.keycode = keyA.keycode;  
		break; 
	}
	memcpy(p2,&keyB,sizeof(keyB));
	return (FCT_OK);
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

int iAPP_Consult( T_UCMC_IAC_SERVICE *pdata_p )
{
	int iRet;
	T_UCMHOST_APP_CONSULT *pConsult;


	iRet = FCT_OK;
	pdata_p->uiSize = sizeof( T_UCMHOST_APP_CONSULT );

	pConsult = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pConsult->sInfo );
	//TODO pConsult->ucAppStatus = UCMHOST_APP_STATUS_NOT_INIT_ACTIVE;
	pConsult->ucAppStatus = UCMHOST_APP_STATUS_INIT_ACTIVE;
	pConsult->ucFileStatus = UCMHOST_APP_FILE_EMPTY;
	
   return( iRet );
}

    

int iAPP_TLC_Status( T_UCMC_IAC_SERVICE *pdata_p )
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



int iAPP_TLP_Status( T_UCMC_IAC_SERVICE *pdata_p )
{
	int iRet;
	T_UCMHOST_APP_TLP_STATE *pState;

	iRet = FCT_OK;
	
	pdata_p->uiSize = sizeof( T_UCMHOST_APP_TLC_STATE );

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



int iAPP_TLC_Start( T_UCMC_IAC_SERVICE *pdata_p )
{
	int iRet;
	T_UCMHOST_APP_TLC_START *pState;

	iRet = FCT_OK;
	
	pdata_p->uiSize = sizeof( T_UCMHOST_APP_TLC_START );

	pState = (void*)&pdata_p->Par.ucBuffer[0];

	ObjectGetInfo( OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&pState->sInfo );
	
	pState->ucState = UCMHOST_TLC_STATE_OK;
	pState->ucRuf = 0;

   return( iRet );
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
   iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 10 ) ;

 

   return( iRet );
}

 /* Specific used */
 static int idle_message_UCMC(NO_SEGMENT AppliNum, char *pMessage_p)
 {
 	FILE* hDisplay;
 	int nDefaultFont;
 	int nScreenWidth;
 	int nScreenHeight;
 	int nFontHeight;
 	char cTemp[400];
 	(void) AppliNum;
 	int i, iLg, iDeb,iFin,iNbLigne,iDecalHeader,iDecalHeaderH;

 	// Terminal idle message
 	i = iLIBUCM_Display_Exist(UCMC_DISPLAY);
 	if( ( i == PARAM_TYPE_IUC180 ) || ( i == PARAM_TYPE_IUP250 ) || ( i == PARAM_TYPE_UPP ))
 	{
 		iLIBUCM_Display_Graphic_Start(UCMC_DISPLAY);

 		if( i == PARAM_TYPE_UPP)
 		{
 			hDisplay = fopen("DISPLAY_PPR", "w");
 		}
 		else
 		{
 			hDisplay = fopen("DISPLAY", "w");
 		}

 		if( hDisplay == NULL)
 		{
  			iLIBUCM_Display_Graphic_Stop(UCMC_DISPLAY);

 			return( -1 );
 		}
 	}
 	else
 	{
 		if( pMessage_p [0] != 0 )
 		{
 			iLIBUCM_Display_Message(UCMC_DISPLAY, pMessage_p, 0);
 		}

 		return( FCT_OK);
 	}

 	nDefaultFont = GetDefaultFont();

 	CreateGraphics(_XLARGE_);
 	GetScreenSize(&nScreenHeight, &nScreenWidth);
 	nFontHeight = GetPoliceSize();

 	// Display the idle message according to terminal type
 	if (!IsHeader())
 	{
 		iDecalHeader = 0;
 		iDecalHeaderH = 0;
 	}
 	else
 	{
 		iDecalHeader = 22;
 		iDecalHeaderH = 7;
 	}

  	_DrawRect(0, 0+iDecalHeader, nScreenWidth-1, nScreenHeight-1-iDecalHeaderH, 1, _ON_, _OFF_);
 	_DrawRect(1, 1+iDecalHeader, nScreenWidth-2, nScreenHeight-2-iDecalHeaderH, 1, _ON_, _OFF_);
 	_DrawRect(3, 3+iDecalHeader, nScreenWidth-4, nScreenHeight-4-iDecalHeaderH, 1, _ON_, _OFF_);

 	SetFont(_LARGE_);
 	_DrawString("Sample Custom", 15, 7+5, _OFF_);
 	SetFont(_MEDIUM_);

 	if( pMessage_p [0] == 0 )
 		_DrawString("Idle message blank", 15, 7+30, _OFF_);
 	else
 	{
 		/* format */
 		iFin = 0;
 		iDeb = 0;
 		iNbLigne=0;
 		iLg = strlen( pMessage_p);
 		for( i = 0; i < iLg; i++ )
 		{
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
 	fclose(hDisplay);

 	iLIBUCM_Display_Graphic_Stop(UCMC_DISPLAY);

 	return (FCT_OK);
 }

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



int fall_back (NO_SEGMENT noappli, S_TRANSIN *param_in, S_TRANSOUT *p2)

{
	return (FCT_OK);
}


typedef int (*T_SERVICE_FUNCTION)(unsigned int nSize, void*Data);

extern int MainAppliUCMC_IAC(unsigned int size_p, T_UCMC_IAC_SERVICE *pdata_p);



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
	MesServices[i].serv_id   = KEYBOARD_EVENT;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 20;
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
	MesServices[i].serv_id   = DEBIT_OVER;
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

	 MesServices[i].appli_id  = no;
	  MesServices[i].serv_id   = IS_CARD_EMV_FOR_YOU;
	  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	  MesServices[i].priority  = 10;
	i++;
	  MesServices[i].appli_id  = no;
	  MesServices[i].serv_id   = DEBIT_EMV;
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



int debit_non_emv (NO_SEGMENT no , S_TRANSIN *param_in, S_TRANSOUT *param_out )
{

	int                    iWhat, iRet, i;
	unsigned char		   bIccOK;

	T_UCMHOST_DEBIT        sDebit ;
	T_UCMHOST_R_DEBIT      sRDeb ;
	HISTORIC               HistoricalBytes ;

		
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
		
		sDebit.ucFunction = DEBIT_NON_EMV ;
		// the application gives UCM the entry point to be recalled to when recording is required 
		iWhat = iLIBUCM_Pay_Ready_For_Debit( sizeof(T_UCMHOST_DEBIT), &sDebit ) ;

	   	switch ( iWhat )
   		{
 	 	   			
   			case UCMCPAY_SOLV :
			{
				i = iLIBUCM_Display_Exist(UCMC_DISPLAY);
			 	if( ( i == PARAM_TYPE_IUC180 ) || ( i == PARAM_TYPE_IUP250 ) )
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
				if (bIccOK)
				{	sRDeb.ucCr			=UCMHOST_CR_OK;
					sRDeb.ulAmount=sDebit.ulAmount;
					iLIBUCM_Display_Message ( UCMC_DISPLAY, "DEBIT OK", 100 ) ;
     			}
				else
				{	sRDeb.ucCr			=UCMHOST_CR_CARDINVALIDE;
					sRDeb.ulAmount=0;
					iLIBUCM_Display_Message ( UCMC_DISPLAY, "REFUSED", 100 ) ;
     			}
   				sRDeb.ucFunction   = UCMHOST_FCT_SOLV ;
				sRDeb.usAppName    = no ;
   				strcpy ( (char *)sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;
				
   				memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
   				memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
   				sRDeb.tCurrency.posdec = 2 ;
				
				iRet=iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) ;	
   				if ( iRet < 0 )
   				{
   		 			iLIBUCM_Display_Message ( UCMC_DISPLAY, "iLIBUCM_Pay_Result_Debit\nUCMHOST_FCT_SOLV", 100 ) ;
				}

				iLIBUCM_Pay_End (sizeof( T_UCMHOST_R_DEBIT ), &sRDeb);

				i = iLIBUCM_Display_Exist(UCMC_DISPLAY);
			 	if( ( i == PARAM_TYPE_IUC180 ) || ( i == PARAM_TYPE_IUP250 ) )
			 	{
			 		iUcmIac_BckColor( 1, UCMCDISPLAY_BKL_COLOR_GREEN);
			 		iUcmIac_BckColor( 0, UCMCDISPLAY_BKL_COLOR_BLACK);
			 	}

			}break ;

   			case UCMCPAY_RECORD : /* UCMPAY_RECORD */
		{
				iLIBUCM_Display_Message ( UCMC_DISPLAY, "RECORD\nIN PROGRESS...", 100 ) ;

				memset ( &sRDeb, 0x00, sizeof ( T_UCMHOST_R_DEBIT ) ) ;
			
				//TODO record transaction
				// update amount  sDebit.ulAmount

				sRDeb.ucCr         = UCMHOST_CR_OK ;
			
				sRDeb.ucFunction   = UCMHOST_FCT_ENREG ;
				sRDeb.usAppName    = no ;
				strcpy ( (char *)sRDeb.tAppLibelle, (const char *)tcAppName_g ) ;

				sRDeb.ulAmount=sDebit.ulAmount;

				read_date( &sRDeb.u.sCard.uAppli.sApp.sLocalDate ) ;

				memcpy ( sRDeb.tCurrency.nom , "EUR", 3 ) ;
				memcpy ( sRDeb.tCurrency.code, "978", 3 ) ;
				sRDeb.tCurrency.posdec = 2 ;
   									  
				if( iLIBUCM_Pay_Result_Debit( sizeof( T_UCMHOST_R_DEBIT ), &sRDeb ) < 0 )
				{
					iLIBUCM_Display_Message ( UCMC_DISPLAY, "iLIBUCM_Pay_Result_Debit\nCMHOST_FCT_ENREG", 100 ) ;
				}
			
				iLIBUCM_Pay_End (sizeof( T_UCMHOST_R_DEBIT ), &sRDeb);							

			}break ;
			 
   			default :
              /* Error management*/
			iLIBUCM_Display_Message ( UCMC_DISPLAY, "UNKNOWN REQUEST\n??", 100) ;
              break ;
   		}
   			
		iLIBUCM_Icc_Close ( UCMC_ICC ) ; 

	}

	param_out->noappli     = no;
	param_out->rc_payment  = PAY_OK;

	return ( STOP );
}


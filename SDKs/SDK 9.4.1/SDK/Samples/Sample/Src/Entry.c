/***
* Copyright (c) 2004 Sagem Monetel SA, rue claude Chappe,
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* Sagem Monetel SA has intellectual property rights relating
* to the technology embodied in this software.  In particular, 
* and without limitation, these intellectual property rights 
* may include one or more patents.
*
* This software is distributed under licenses restricting 
* its use, copying, distribution, and decompilation.  
* No part of this software may be reproduced in any form 
* by any means without prior written authorization of 
* Sagem Monetel.
*
* @Title:        
* @Description:  SDK30 sample application
* @Reference:    
* @Comment:      
*
* @author        
* @version       
* @Comment:      
* @date:         
*/
#include "SDK30.H"

// Bitmaps definitions. 
#include "Bmp\Swipe1.h"
#include "Bmp\Swipe2.h"
#include "Bmp\Swipe3.h"

#include "Bmp\Anim1.h"
#include "Bmp\Anim2.h"
#include "Bmp\Anim3.h"
#include "Bmp\Anim4.h"
#include "Bmp\Anim5.h"
#include "Bmp\Anim6.h"
#include "Bmp\Anim7.h"


#define BITMAP_SWIPE1  ((char*) swipe1)   // To discard const qualifier.
#define BITMAP_SWIPE2  ((char*) swipe2)  // To discard const qualifier.
#define BITMAP_SWIPE3  ((char*) swipe3)  // To discard const qualifier.

const unsigned char *__ANIM[12] =
{
	anim1, anim2, anim3, anim4, anim5, anim6, anim7,
	anim6, anim5, anim4, anim3, anim2
};


static const char szDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n";
static const unsigned char appname[]    = "BASIC SAMPLE";

#define __ENTER_KEY		-1
#define __BACK_KEY		-2
#define __EXIT_KEY		-3

#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


#define NB_ITEMS  8
const FCT_SUP mylist [] =
{ 
	{"Item0"}, {"Item1"}, {"Item2"}, {"Item3"}, {"Item4"}, {"Item5"}, {"Item6"}, {"Item7"}
};

int			i,select;	
unsigned char     	cr,returned;
ENTRY_BUFFER    	buf_entry;
//int              	MAXX;
//int               	MAXY; 



const char *MenuTest[] =
{
	"ISO",
	"FFMS",
	"User Interface"
};

const char *MenuGraphic[] =
{
	"List Entry",
	"Num Entry",
	"Graphics",
	"Printer"
};

const char *MenuFFMS[] =
{
	"File R&W",
	"Print Dir"
};




// 1 second Delay
#define __1_SECOND__		100
#define __3_SECONDS__		300
#define __500_MSECONDS__	50

void Wait_1Second( void ) 
{
	ttestall( 0, __1_SECOND__ );
}

/* Static functions */
int Main (unsigned int size, StructPt *data);

//
int ManageMenu( const char *szTitle, int bRadioButtons, int nDefaultChoice, 
				int nItems, const char* Items[] )
{
	FILE *hDisplay;
	int DisplayHeaderStatus;

	// Menu.
	StructList Menu;
	int nY;
	int nMaxX;
	int nMaxY;

	ENTRY_BUFFER Entry;

	//
	int i;
	int nInput;
	int nReturn;

	//
	hDisplay = fopen( "DISPLAY", "w" );

	// Get Screen size.
	GetScreenSize( &nMaxY, &nMaxX );

	// For the menu height of the menu,
	nY = 0;
	DisplayHeaderStatus=StateHeader(0); // disable display header

	if ((nDefaultChoice < 0) || (nDefaultChoice >= nItems))
	{
		nDefaultChoice = 0;
	}

	//
	CreateGraphics(_MEDIUM_);

	//
	memset( &Menu, 0, sizeof(Menu) );
	Menu.MyWindow.left   = 0;
	Menu.MyWindow.top    = nY;
	Menu.MyWindow.rigth  = nMaxX - 1;
	Menu.MyWindow.bottom = nMaxY - 1;
	if( nMaxY == 128 )
	{
		Menu.MyWindow.nblines = 10;
	}
	else
	{
		Menu.MyWindow.nblines = 5;
	}

	Menu.MyWindow.fontsize		= _MEDIUM_;
	Menu.MyWindow.type			= _PROPORTIONNEL_;
	Menu.MyWindow.font			= 0;
	Menu.MyWindow.correct		= _ON_;
	Menu.MyWindow.offset		= 0;
	Menu.MyWindow.shortcommand	= _ON_;
	if( bRadioButtons )
	{
		Menu.MyWindow.selected = _ON_;
	}
	else
	{
		Menu.MyWindow.selected = _OFF_;
	}

	Menu.MyWindow.thickness		= 2;
	Menu.MyWindow.border		= _ON_;
	Menu.MyWindow.popup			= _NOPOPUP_;
	Menu.MyWindow.first			= nDefaultChoice;
	Menu.MyWindow.current		= nDefaultChoice;
	Menu.MyWindow.time_out		= 60;
	Menu.MyWindow.title			= (unsigned char*)szTitle;

	for( i = 0; i < nItems; i++ )
	{
		Menu.tab[i] = (unsigned char*)Items[i];
	}

	G_List_Entry((void*)&Menu);
	ttestall(ENTRY, 0);
	nInput = Get_Entry((void*)&Entry);

	switch( nInput )
	{
	case CR_ENTRY_OK:
		nReturn = Entry.d_entry[0];
		break;

	case CR_ENTRY_NOK:
		nReturn = __EXIT_KEY;
		break;

	default:
		nReturn = __BACK_KEY;
		break;
	}
	StateHeader(DisplayHeaderStatus); // move display header in previous state
	fclose( hDisplay );
	
	return nReturn;
}

void DisplaySwipeAnimation()
{
	static int nBitmapIndex = 0;
	int nYBitmap;
	
	//
	nYBitmap = 9;

	//
	CreateGraphics( _LARGE_ );

	DrawString( "Please",   68, nYBitmap + 5, _OFF_ );
	DrawString( "Swipe",	 68, nYBitmap + 17, _OFF_ );
	DrawString( "a card.",  68, nYBitmap + 29, _OFF_ );

	switch( nBitmapIndex )
	{
		case 0:
			DisplayBitmap( 0, nYBitmap, (unsigned char*)BITMAP_SWIPE1, 8, _OFF_);
			nBitmapIndex = 1;
		break;

		case 1:
			DisplayBitmap( 0, nYBitmap, (unsigned char*)BITMAP_SWIPE2, 8, _OFF_ );
			nBitmapIndex = 2;
		break;
		case 2:
			DisplayBitmap( 0, nYBitmap, (unsigned char*)BITMAP_SWIPE3, 8, _OFF_ );
			nBitmapIndex = 0;
		break;
	}

	// Display screen.
	PaintGraphics();
}
void PrintIsoError(FILE *dev, char *track_name, int cr, char *buffer)
{
	switch (cr)
	{
		case ISO_OK:
			// Print the reading status and the contents
			fprintf( dev, "Good %s card\n", track_name);
			fprintf( dev, "%s\n", buffer);
			break;
		case DEF_SEP:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "separator fault");
			break;
		case DEF_PAR:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "parity fault");
			break;
		case DEF_LRC:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "LRC fault");
			break;
		case DEF_LUH:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "Luhn fault");
			break;
		case DEF_NUM:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "numerical fault");
			break;
		case NO_DATA:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "no readable data detected");
			break;
		default:
			// Print the reading status and the status
			fprintf( dev, "Bad %s card\n", track_name);
			fprintf( dev, "%s\n", "unknown error status");
			break;
	}
}

//read all tracks simultanuously
void Iso_Test(void)
{
	FILE *hDisplay;
	FILE *hKeyboard;
	FILE *hPrinter;
	FILE *hSwipe1,*hSwipe2, *hSwipe3;

	//
	int bContinue = 1;
	unsigned int cr;

	// ISO1 Track.
	unsigned char pucBuffer1[79];
	unsigned char ucPanLength1;
	int cr_iso1;
	// ISO2 Track.
	unsigned char pucBuffer2[41];
	unsigned char ucPanLength2;
	int cr_iso2;
	// ISO3 Track.
	unsigned char pucBuffer3[107];
	unsigned char ucPanLength3;
	int cr_iso3;


	// Open drivers
	hDisplay  = fopen( "DISPLAY",  "w"  );
	hKeyboard = fopen( "KEYBOARD", "r"  );
	hPrinter  = fopen( "PRINTER",  "w-" );
	hSwipe1   = fopen( "SWIPE31",  "r*"  ); //open r* => no reset if not present
	hSwipe2   = fopen( "SWIPE2",  "r*"  ); //open r* => no reset if not present
	hSwipe3   = fopen( "SWIPE3",  "r*"  ); //open r* => no reset if not present

	do
	{
		DisplaySwipeAnimation();

		// Wait a key press,
		// a swiped card.
		// Timeout set to 1 second in order to update
		// the bitmap animation.
		/* wait for track readers */
		cr = ttestall ( KEYBOARD | SWIPE31 | SWIPE2 | SWIPE3, 30); // wait for the fist event
		cr |= ttestall ( cr ^ ( SWIPE31 | SWIPE2 | SWIPE3 ) , 30 ); //wait for the second event
		cr |= ttestall ( cr ^ ( SWIPE31 | SWIPE2 | SWIPE3 ) , 30 ); //wait for the third event 
		if (cr & KEYBOARD)
		{
			bContinue = 0;
		}
		else
		{

			if ( cr & SWIPE31 )
			{
				cr_iso1 = is_iso1 ( hSwipe1, &ucPanLength1, pucBuffer1) ;
				PrintIsoError(hPrinter, "ISO1", cr_iso1, (char*)pucBuffer1);
				fprintf(hPrinter,"\n");
				bContinue = 0;
			}
			if ( cr & SWIPE2 )
			{
				cr_iso2 = is_iso2( hSwipe2, &ucPanLength2, pucBuffer2);
				PrintIsoError(hPrinter, "ISO2", cr_iso2, (char*)pucBuffer2);
				fprintf(hPrinter,"\n");
				bContinue = 0;
			}
			if ( cr & SWIPE3 )
			{
				cr_iso3 = is_iso3 ( hSwipe3, &ucPanLength3, pucBuffer3) ;
				PrintIsoError(hPrinter, "ISO3", cr_iso3, (char*)pucBuffer3);
				fprintf(hPrinter,"\n");
				bContinue = 0;
			}
		}
	}	while( bContinue == 1 );
	fprintf( hPrinter, "\n\n\n");

	// Wait for print end.
	ttestall( PRINTER , __3_SECONDS__ );
	// Close drivers
	if (hSwipe1 != NULL)
		fclose( hSwipe1);
	if (hSwipe2 != NULL)
		fclose( hSwipe2);
	if (hSwipe3 != NULL)
		fclose( hSwipe3 );
	fclose( hPrinter );
	fclose( hKeyboard );
	fclose( hDisplay );
}



void FS_FileRW(void)
{
	FILE *hDisplay;

	S_FS_FILE	*pFile;
	int rc,lg ; 
	S_FS_PARAM_CREATE ParamCreat;
	unsigned char buffer[16];
	
	hDisplay = fopen( "DISPLAY", "w" );
	memclr(buffer,sizeof(buffer));
	ParamCreat.Mode = FS_WRITEONCE;
	rc = FS_mount ("/MyDisk",&ParamCreat.Mode);
	switch (rc)
	{ 
	case FS_OK :
		printf("\x1B""File creating.. \n");
		ttestall(0,100);
		pFile = FS_open ("/MyDisk/myfile", "a");
		FS_write ("Test string ",1,12,pFile);
		FS_close(pFile);
		pFile = FS_open ("/MyDisk/myfile", "r");
		lg = FS_read (buffer,1,16,pFile);
		printf("\x1B""File reading...\nLen :%d",lg);
		ttestall(0,100);
		printf("\x1B""File reading...\n%s",buffer);
		ttestall(0,100);
		FS_close( pFile );
		FS_unmount("/MyDisk");
		break ; 
	case FS_NOFORMAT :
		printf("\x1B""Formatting..");
		ttestall(0,100);
		FS_format("/MyDisk",FS_WRTMOD,10);
		break; 

	default : 
		printf("\x1B""FS ERROR..");
		ttestall( 0, __1_SECOND__ );
		break ; 
	}
	fclose(stdout());
}

void FS_PrintDir( void )
{
	FILE *hDisplay;
	FILE *hPrinter;

	//
	S_FS_PARAM_CREATE 	ParamCreat;
	S_FS_DIR			*pMyDir;
	S_FS_FILEINFO  		dirData;
	
	hDisplay = fopen( "DISPLAY", "w"  );
	hPrinter = fopen( "PRINTER", "w-" );

	ParamCreat.Mode = FS_WRITEONCE;
	FS_mount ("/MyDisk",&ParamCreat.Mode);
	pMyDir = FS_opendir ("/MyDisk/*");
	while( FS_readdir ( pMyDir, &dirData ) == FS_OK ) 
	{
		pprintf( "Filename : %s\nFile Size : %lu\n",
				 dirData.FileName,
				 dirData.FileSize );

        ttestall ( PRINTER , __3_SECONDS__ );  
	}

	FS_closedir(pMyDir);
	FS_unmount("/MyDisk");

	// Close drivers.
	fclose( hPrinter );
    fclose( hDisplay );
}

void DoListEntry(void)
{ 
	// Menu.
	StructList Menu;

	// Screen info.
	unsigned int nHeaderStatus;
	int nMaxX;
	int nMaxY;

	// Get Screen size.
	GetScreenSize( &nMaxY, &nMaxX );

	// Remove the top banner.
	nHeaderStatus = StateHeader(0);


	//
	Menu.MyWindow.left         		= 0;           
	Menu.MyWindow.top   			= 0;
	Menu.MyWindow.rigth 			= nMaxX;
	Menu.MyWindow.bottom			= nMaxY;
	Menu.MyWindow.nblines			= 4;
	Menu.MyWindow.fontsize			= _MEDIUM_;
	Menu.MyWindow.type  			= _PROPORTIONNEL_; 
	Menu.MyWindow.font 				= 0;         
	Menu.MyWindow.shortcommand		= _OFF_;
	Menu.MyWindow.selected      	= _ON_;
	Menu.MyWindow.thickness    		= 2;
	Menu.MyWindow.border			= _ON_;
	Menu.MyWindow.popup				= _NOPOPUP_;
	Menu.MyWindow.first				= 0;                   
	Menu.MyWindow.time_out      	= 20;
	Menu.MyWindow.current			= 0;
	Menu.MyWindow.title				= (unsigned char*)"Item List";
	for (i = 0; i < NB_ITEMS; i++)
	{
		Menu.tab[i] = (unsigned char*)mylist[i].Name;
	}
	Menu.tab[i] = NULL;

	G_List_Entry((void*)&Menu);
	ttestall(ENTRY,0);
	switch( Get_Entry( &buf_entry ))
	{ 
    case CR_ENTRY_OK :
		// buf_entry.d_entry[0] contains the index position
		printf("\x1B""Function %2x\nselected",buf_entry.d_entry[0]);
		ttestall(0,200);
		break;

    case CR_ENTRY_TIME_OUT: // Time out do nothing 
    case CR_ENTRY_CANCEL:   // Cancelled do nothing  
		break;
	}

	// Set the initial banner status.
	StateHeader( nHeaderStatus );
}

void DoNumEntry(void)
{
	// Menu.
	StructList Menu;
	TAB_ENTRY_STRING	NumEntry;

	// Screen info.
	unsigned int nHeaderStatus;
	int nMaxX;
	int nMaxY;

	// Get Screen size.
	GetScreenSize( &nMaxY, &nMaxX );

	// Remove the top banner.
	nHeaderStatus = StateHeader(0);

	//
	Menu.MyWindow.left         		= 0;           
	Menu.MyWindow.top   			= 0;
	Menu.MyWindow.rigth 			= nMaxX;
	Menu.MyWindow.bottom			= nMaxY;
	Menu.MyWindow.nblines			= 4;
	Menu.MyWindow.fontsize			= _MEDIUM_;
	Menu.MyWindow.type  			= _PROPORTIONNEL_; 
	Menu.MyWindow.font 				= 0;         
	Menu.MyWindow.shortcommand		= _OFF_;
	Menu.MyWindow.selected      	= _ON_;
	Menu.MyWindow.thickness    		= 2;
	Menu.MyWindow.border			= _ON_;
	Menu.MyWindow.popup         	= _NOPOPUP_;
	Menu.MyWindow.first				= 0;                   
	Menu.MyWindow.time_out      	= 20;
	Menu.MyWindow.current			= 0;
	Menu.MyWindow.title				= (unsigned char*)"Num List";
	
	Menu.tab[0] = (unsigned char*)"Password";
	Menu.tab[1] = (unsigned char*)"      ";
	Menu.tab[2] = NULL;
	
	NumEntry.mask		= 0;
	NumEntry.time_out	= 30;
	NumEntry.line		= 32;
	NumEntry.column		= 8;
	NumEntry.echo		= ECHO_SPECIAL;
	NumEntry.nb_max		= 6 ;
	NumEntry.nb_min		= 6 ;
	memclr(buf_entry.d_entry,sizeof(buf_entry.d_entry));
	G_Numerical_Entry ((void *)&Menu, &NumEntry);
	ttestall(ENTRY,0);

	switch( Get_Entry( &buf_entry ))
	{ 
    case CR_ENTRY_OK :
		// buf_entry.d_len contains the length of entry 
		// buf_entry.d_entry [50] contains the entry
		printf("\x1B""Entry Len %d\n",buf_entry.d_len);
		ttestall(0,200);
		printf("\x1B""Entry %s\n",buf_entry.d_entry); 
		ttestall(0,200);
		break;

    case CR_ENTRY_TIME_OUT: // Time out do nothing 
    case CR_ENTRY_CANCEL:   // Cancelled do nothing  
		break;
	}
	
	// Set the initial banner status.
	StateHeader( nHeaderStatus );
}

void DoMiscPrinter(void)
{
	FILE *hPrinter = fopen( "PRINTER", "w-*" );
	if ( hPrinter != NULL ) 
	{
		// Reset the printer status.
		pprintf( "\x1b" "@" "\n" );	

		// Condensed
		// "\x0f" : conensed section.
		// "\x12" : end condensed section.
		pprintf( "\x0f" "%s\n" "\x12", "Condensed Text" );	

		// Normal
		// "\x1b""F"
		pprintf( "%s\n", "Normal Text" );	

		// Inverted
		// "\x1b""B1"
		// "\x1b""B0"
		pprintf( "\x1b""B1" "%s\n" "\x1b""B0", "Inverted Text" );	

		// Bold.
		// "\x1b""E" : bold section.
		// "\x1b""F" : end bold section.
		pprintf( "\x1b""E" "%s\n" "\x1b""F", "Bold Text" );

		// Double width
		// "\x0e" : double width section
		// "\x14" : end double width section
		pprintf( "\x0e" "%s\n" "\x14", "Double Text" );

		// Bitmap.
		// ...

		// Line feed.
		pprintf( "\n\n\n\n\n" );


		// Wait for the printing end.
		ttestall( PRINTER, 0 );

		fclose( hPrinter );
	}
}

void DoMiscGraphic(void)
{
	FILE *hKeyboard;
	FILE *hDisplay;
	// Screen info.
	unsigned int nHeaderStatus;
	int nMaxX;
	int nMaxY;

	//
	int nWidth;

	int i, j, k = 0;
	int nIndex;			// Image index.

	hDisplay  = fopen( "DISPLAY",  "w"  );
	// Get Screen size.
	GetScreenSize( &nMaxY, &nMaxX );

	// Remove the top banner.
	nHeaderStatus = StateHeader(0);

	//
	
	CreateGraphics( _MEDIUM_ );

	// Rectangles
	DrawRect( 0, 0, 10, 10, 0, _ON_, _ON_ ); // Fill Rect.
	DrawRect( 10, 10, 30, 30, 1, _ON_, _OFF_ ); // Empty Rect.

	// Circles
	DrawCircle( 20, 20, 10, _OFF_  ); // Empty circle.
	DrawCircle( 20, 20, 5,  _ON_   ); // Fill circle.

	// Ellipse
	DrawEllipse( 100, 40, 20, 10, _OFF_   ); // Empty.

	// Text
	DrawString( "Text1", 40, 10, _ON_ );	// Inverted text.

	// Text with border.
	// Calculate the size of the string
	// and draw the border rectangle first.
	nWidth = StringWidth( "Text2" );
	DrawRect( 40-1, 30-1, 40 + nWidth + 1,  30 + _SIZE_MEDIUM_ + 1, 1, _ON_, _OFF_ ); // Border
	DrawString( "Text2", 40, 30, _OFF_ );

	// Underlined text.
	nWidth = StringWidth( "Text3" );
	DrawString( "Text3", 40, 50, _OFF_ );
	DrawLine( 40, 50 + _SIZE_MEDIUM_, 40 + nWidth,  50 + _SIZE_MEDIUM_, _ON_ );

	// Set Pixel.
	// Draw a pattern rectangle.
	k = 0;
	for( j = 0; j < 24; j++ )
	{
		for( i = 0; i < 48; i++ )
		{
			if(( k % 3 ) == 0 )
			{
				SetPixel( 80 + i, j, _ON_ );
			}

			k++;
		}
		k++;
	}

	//
	hKeyboard = fopen( "KEYBOARD", "r" );

	// Draw Animation
	// Wait for a key pressed.
	nIndex = 0;
	do
	{
		DisplayBitmap( 10, 35, (unsigned char *) __ANIM[nIndex], 8, _OFF_ );
		PaintGraphics();

		//
		// Process Next Image.
		nIndex++;
		if( nIndex == 12 )nIndex = 0;
	}
	while( ttestall( KEYBOARD, __500_MSECONDS__ ) != KEYBOARD );

	fclose( hKeyboard );
	fclose( hDisplay );
	// Set the initial banner status.
	StateHeader( nHeaderStatus );
}



void Graphic_Menu(void)
{
	int bContinue = 1;
	do
	{
		switch( ManageMenu( "Graphic", 0, 0, NUMBER_OF_ITEMS(MenuGraphic), MenuGraphic ))
		{
		case 0:
			DoListEntry();
			break;

		case 1:
			DoNumEntry();
			break;

		case 2:
			DoMiscGraphic();
			break;

		case 3:
			DoMiscPrinter();
			break;

		default:
			bContinue = 0;
			break;
		}
	}
	while( bContinue == 1 );
}



void FFMS_Menu(void)
{
	int bContinue = 1;
	do
	{
		switch( ManageMenu( "FFMS", 0, 0, NUMBER_OF_ITEMS(MenuFFMS), MenuFFMS ))
		{
		case 0:
			FS_FileRW();
			break;

		case 1:
			FS_PrintDir();
			break;

		default:
			bContinue = 0;
			break;
		}
	}
	while( bContinue == 1 );
}

int more_function( NO_SEGMENT no, void *p1, void *p2 )
{
	int bContinue = 1;
	do
	{
		switch( ManageMenu( "Tests", 0, 0, NUMBER_OF_ITEMS(MenuTest), MenuTest ))
		{
		case 0:
			Iso_Test();
			break;

		case 1:
			FFMS_Menu();
			break;

		case 2:
			Graphic_Menu();
			break;

		default:
			bContinue = 0;
			break;
		}
	}
	while( bContinue == 1 );
	
	return FCT_OK;
}


int after_reset( NO_SEGMENT no, void *p1, S_TRANSOUT *etatseq )
{
	FILE *hKeyboard;
	FILE *hDisplay;

	//
	unsigned char chgt;
	TYPE_CHGT  type;

	hKeyboard = fopen( "KEYBOARD", "r" );
	hDisplay  = fopen( "DISPLAY",  "w" );

	// Test if it is the first execution of the application.
	first_init( no, &chgt, (unsigned char*)&type);
	if ( chgt == 0xFF )
	{ 
		S_FS_PARAM_CREATE ParamCreat;
		unsigned long DiskSize;
		int rc ;

		// Just downloaded.
		// First execution.
		ParamCreat.Mode = FS_WRITEONCE;
		rc = FS_mount("/MyDisk",&ParamCreat.Mode);
		if ( rc != FS_OK ) 
		{
			// The disk does not exist.
			// So it is created.
			DiskSize = 8192;
			strcpy( ParamCreat.Label, "MyDisk" );
			ParamCreat.Mode			= FS_WRITEONCE;
			ParamCreat.AccessMode	= FS_WRTMOD;
			ParamCreat.NbFichierMax = 10;
			ParamCreat.IdentZone	= FS_WO_ZONE_DATA;
			rc = FS_dskcreate( &ParamCreat, &DiskSize );
			if ( rc == FS_OK )
			{
				printf("\x1B""Creating Disk OK\nStrike a Key");
			}
			else
			{ 
				printf("\x1B""Creating Disk KO\nStrike a Key");
			}
		}
		else
		{
			printf("\x1B""Disk exists\nStrike a Key");
		}

		FS_unmount("/MyDisk");
		raz_init(no);
	}
	else 
	{	// Not the fist execution.
		printf("Warm Reset\nStrike a Key");
	}

	// Wait for a key pressed.
	getchar();

	// Close drivers.
	fclose( hKeyboard );
	fclose( hDisplay  );

	return FCT_OK;
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
	strcpy((char *)etatout.returned_state[etatout.response_number].appname,(char *)appname);
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
	object_info_t infos;
	FILE     *hPrinter;
	
	ObjectGetInfo(OBJECT_TYPE_APPLI, noappli, &infos);

	hPrinter = fopen( "PRINTER", "w-*" );
	if ( hPrinter != NULL ) 
	{	
		pprintf ("\n\n\n");
		pprintf ("\x1b""E%s\n""\x1b""F",appname);

		// get and print application file name and CRC
		pprintf ("Vers. : %s\n",infos.file_name);
		pprintf ("CRC   : %04x\n",infos.crc);

		ttestall (PRINTER, 0 );	  
		fclose( hPrinter ); 
	}
    
	return FCT_OK;
}


int mcall (NO_SEGMENT noappli,void *p1,void *p2)
{
	DATE date;
	FILE *hPrinter;
	
	hPrinter = fopen ( "PRINTER", "w-*" );
	if ( hPrinter != NULL )
	{
		pprintf ("\x1b""E%s\n""\x1b""F",appname);
		read_date (&date);
		pprintf (szDate, date.day, date.month, date.year, date.hour, date.minute);
		pprintf ("Nothing scheduled\n");
	
		ttestall( PRINTER, __3_SECONDS__ );
		fclose( hPrinter );
	}

	return FCT_OK;
}

int consult (NO_SEGMENT noappli,void *p1,void *p2)
{
	DATE date;
	FILE *hPrinter;
	
	hPrinter = fopen ( "PRINTER", "w-*" );
	if ( hPrinter != NULL )
	{
		pprintf ("\x1b""E%s\n""\x1b""F",appname);
		read_date (&date);
		pprintf (szDate, date.day, date.month, date.year, date.hour, date.minute);
		pprintf ("\x1b""@""Nothing to show\n");
	
		ttestall( PRINTER, __3_SECONDS__ );
		fclose( hPrinter );
	}
	return FCT_OK;
}

int time_function (NO_SEGMENT noappli,void *p1,void *p2)
{	
	fopen("DISPLAY","w");
	printf("Time to call\n");
	//  buzzer(100);
	ttestall(0,100);
	fclose(stdout());
	return (FCT_OK);
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
	FILE           *prt;
	S_FS_PARAM_CREATE ParamCreat;
	int		 Retour;
	char		 Dir_File[25];
	char		 Dir_Label[25];
	S_FS_FILE      *pFile;
	
	prt  = fopen("PRINTER","w-");
	pprintf("File Received :\n/%s/%s",param_in->volume_name,param_in->file_name);
	pprintf("\n\n\n\n\n");
	ttestall(PRINTER,0);
	
	memclr(Dir_File,sizeof(Dir_File));
	memclr(Dir_Label,sizeof(Dir_Label));
	
	sprintf(Dir_Label,"/%s",param_in->volume_name);
	ParamCreat.Mode = FS_WRITEONCE;
	Retour = FS_mount (Dir_Label,&ParamCreat.Mode);
	if (Retour == FS_OK)
	{
		sprintf(Dir_File,"/%s/%s",param_in->volume_name,param_in->file_name);
		// the file can be open at this stage
		pFile = FS_open (Dir_File, "r");
		// read the file and get parameters 
		FS_close(pFile);
		// cannot be deleted as it is located in system disk 
		FS_unmount(Dir_Label);
	}
	fclose(prt);
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
	fopen("DISPLAY","w");
	printf("MODIF_PARAM\n%04x",(int)param_changed.etatout.returned_state[0].state.mask);
	ttestall(0,200);
	fclose(stdout());
	return(FCT_OK);
}



int is_for_you_after(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out)
{
#define	MY_ATR	0x38
	
	S_CARDOUT card_out;

	
	memcpy (&card_out, param_out, sizeof(card_out));

	// case of chip card 
	if (param_in->support == CHIP_SUPPORT)
	{
		// depending on ATR, card is accepted or not
		if((param_in->power_on_result ==0) && (param_in->historical_bytes.historic[0] == MY_ATR))
		{
			// accept this card 
			card_out.returned_state[card_out.response_number].cardappnumber = 1;
			card_out.returned_state[card_out.response_number].cardapp [0].priority = CARD_PRIORITY;
		}
		else
		{
			// reject the card
			card_out.returned_state[card_out.response_number].cardappnumber = 0;
		}
	}

	// case of stripe 2 card 
	if (param_in->support == TRACK2_SUPPORT)
	{
		// accept this card 
		card_out.returned_state[card_out.response_number].cardappnumber = 1;
		card_out.returned_state[card_out.response_number].cardapp [0].priority = CARD_PRIORITY;
	}
	
	// case of Card Number Manual entry  
	if (param_in->support == OPERATOR_SUPPORT)
	{
		// accept this card 
		card_out.returned_state[card_out.response_number].cardappnumber = 1;
		card_out.returned_state[card_out.response_number].cardapp [0].priority = CARD_PRIORITY;
	}

	// give my application name 
	strcpy (card_out.returned_state[card_out.response_number].appname , (char *)appname) ;
	// give my application number
	card_out.returned_state[card_out.response_number].no_appli = no;
	strcpy (card_out.returned_state[card_out.response_number].cardapp [0].cardappname, "SAMPLE APP") ;
	// increment the response number 
	card_out.response_number++;

	memcpy (param_out, &card_out, sizeof(card_out));
	return (FCT_OK);
}



//// Functions //////////////////////////////////////////////////
const char CmdSelect[] = { (char)0x00, (char)0xA4, (char)0x04, (char)0x00, (char)0x00 }; // Class/Inst/P1/P2/P3(Len)/Data

T_APDU gC_Apdu; // Command APDU
T_APDU gR_Apdu; // Response APDU

static unsigned char g_pucBufResponse[258] ;
static unsigned char g_pucBufCmd[260] ; /* CLA/INS/P1/P2/Lc/0..255/Le */

int SendSelect( FILE *hCAM, const char *szName )
{
	unsigned char ucSize;

	//APDU Initialize
	gC_Apdu.data = g_pucBufCmd ;
	gR_Apdu.data = g_pucBufResponse;

	// Set template.
	memcpy( gC_Apdu.data, &CmdSelect[0], 5 );

	// Set size
	ucSize = (unsigned char) strlen( szName );
	gC_Apdu.data[4] = ucSize;

	// Set Data
	memcpy( &gC_Apdu.data[5], szName, ucSize );

	//
	gC_Apdu.length = 5 + ucSize;

	if( EMV_apdu( hCAM, &gC_Apdu, &gR_Apdu ) == OK )// Send APDU
	//gR_Apdu contains the response
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


int debit_non_emv (NO_SEGMENT no, S_TRANSIN * param_in, S_TRANSOUT * param_out)
{
	unsigned char cr;
	FILE			*prt;
	FILE			*hcam;
	TRACK2_BUFFER track2; 

	
	memclr(track2,sizeof(track2));
	fopen("KEYBOARD","r");
	fopen("DISPLAY","w");
	prt  = fopen("PRINTER","w-");
	printf("DEBIT_NON_EMV\n%s",appname);
	pprintf("\x1b""EDEBIT_NON_EMV \n""\x1b""F""%s\n",appname);
	
	// case of chip card 
	if ( param_in->support == CHIP_SUPPORT )
	{
		hcam = stdperif("CAM0", NULL);
		cr = SendSelect(hcam, "1PAY.SYS.DDF01" ); //file name selection
		if (cr == TRUE)
			pprintf("cmd APDU OK\n");
		else
			pprintf("cmd APDU KO\n");
	}

	// case of stripe 2 card 
	if ( param_in->support == TRACK2_SUPPORT )
	{
		memcpy (track2,param_in->track2,sizeof(track2));
		pprintf("Track2:\n%s\n",track2); 
	}
	
	// case of Card Number Manual entry  
	if ( param_in->support == OPERATOR_SUPPORT )
	{
		memcpy (track2,param_in->track2,sizeof(track2));
		pprintf("Manual Entry:\n%s\n",track2); 
	}
	
	pprintf("\n\n\n\n\n");
	ttestall(PRINTER,0);
	fclose(prt);
	fclose(stdin());
	fclose(stdout());
	param_out->noappli      = no;
	param_out->rc_payment  = PAY_OK;
	return (FCT_OK);
}


int idle_message (NO_SEGMENT no,void *p1,void *p2)
{
	FILE *hDisplay;
	int nFont;

	// Open the display driver.
	hDisplay = fopen("DISPLAY","w");

	//
	nFont = GetDefaultFont();
	
	// Display screen.
	CreateGraphics( _LARGE_ );
	_DrawString( "Please\nInsert\nA Smart Card...",  0, 20, _OFF_ );
	PaintGraphics();

	//
	SetDefaultFont( nFont );

	// Close the display driver.
	fclose( hDisplay );

	return FCT_OK;
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
	MesServices[i].serv_id   = IDLE_MESSAGE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 20;
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

	ServiceRegister(i,MesServices);

	return FCT_OK;
}

void entry(void)
{
	object_info_t info;
	
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
	give_interface(info.application_type, NULL, NULL);

}


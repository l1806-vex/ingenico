//-------------------------------------------------------------------
//
// Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Sagem Monetel SA has intellectual property rights relating
// to the technology embodied in this software.  In particular, 
// and without limitation, these intellectual property rights 
// may include one or more patents.
//
// This software is distributed under licenses restricting 
// its use, copying, distribution, and decompilation.  
// No part of this software may be reproduced in any form 
// by any means without prior written authorization of 
// Sagem Monetel.
//
// Description: User Interface function set. Miscellaneous.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------

// Includes.
//-------------------------------------------------------------------

#include "SDK30.H"

#include "UserInterfaceHelpers.h"
//#include "malloc.h"

// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))

#define STATE_INPUT_END				0
#define STATE_INPUT_WAIT_KEY		1
#define STATE_INPUT_KEY_STEP		2


#define __GETKEY(tab) \
	if( (tab)[*pnIndex] == '\0' ) *pnIndex = 0; *pcCharacter = (tab)[*pnIndex]; (*pnIndex)++;

// Types.
//-------------------------------------------------------------------
typedef struct
{
	// Bounding box;
	int m_nX, m_nY, m_nW, m_nH;

	// Text
	int m_bNumerical;
	int m_nMaxLen;
	char *m_szText;

	// Input Cursor.
	int m_nCursor; // Cursor Index.
	int m_nXCursor, m_nYCursor;

} T__TEXT;


// Global variables.
//-------------------------------------------------------------------

// Static function definitions.
//-------------------------------------------------------------------
static int HelperDisplayMenuInternal( const char* szTitle, int bRadioButtons, int nDefaultChoice, 
									  int nItems, const char* Items[],
									  int nBanners );



static int GetNextCharacter( int nKey, int nMode, int *pnIndex, char *pcCharacter )
{
	const char tKey0[] = { '0', '-', ' ', '\0' };
	const char tKey1[] = { '1', 'q', 'z', 'Q', 'Z', '\0' };
	const char tKey2[] = { '2', 'a', 'b', 'c', 'A', 'B', 'C', '\0' };
	const char tKey3[] = { '3', 'd', 'e', 'f', 'D', 'E', 'F', '\0' };
	const char tKey4[] = { '4', 'g', 'h', 'i', 'G', 'H', 'I', '\0' };
	const char tKey5[] = { '5', 'j', 'k', 'l', 'J', 'K', 'L', '\0' };
	const char tKey6[] = { '6', 'm', 'n', 'o', 'M', 'N', 'O', '\0' };
	const char tKey7[] = { '7', 'p', 'r', 's', 'P', 'R', 'S', '\0' };
	const char tKey8[] = { '8', 't', 'u', 'v', 'T', 'U', 'V', '\0' };
	const char tKey9[] = { '9', 'w', 'x', 'y', 'W', 'X', 'Y', '\0' };
	const char tKeyDot[] = { '.', ',', '\'', ';', ':', '@', '/', '\\', '\0' };

	switch( nKey )
	{
	case T_NUM0:	__GETKEY(tKey0);	break;
	case T_NUM1:	__GETKEY(tKey1);	break;
	case T_NUM2:	__GETKEY(tKey2);	break;
	case T_NUM3:	__GETKEY(tKey3);	break;
	case T_NUM4:	__GETKEY(tKey4);	break;
	case T_NUM5:	__GETKEY(tKey5);	break;
	case T_NUM6:	__GETKEY(tKey6);	break;
	case T_NUM7:	__GETKEY(tKey7);	break;
	case T_NUM8:	__GETKEY(tKey8);	break;
	case T_NUM9:	__GETKEY(tKey9);	break;
	case T_POINT:	__GETKEY(tKeyDot);	break;

	case T_APAP:
	case T_VAL:
	case T_ANN:
	case T_CORR:
	case T_SK1:
	case T_SK2:
	case T_SK3:
	case T_SK4:
	case T_SKHAUT:
	case T_SKBAS:
	case T_SKVAL:
	case T_SKCLEAR:
	case T_SK10:
	default:
		return '\0';
	}

	switch( nMode )
	{
	case __MODE_LOWERCASE:
		if(( *pcCharacter >= 'A') &&  ( *pcCharacter <= 'Z'))
		{
			*pcCharacter = 'a' +  (*pcCharacter - 'A');
		}
		break;

	case __MODE_UPPERCASE:
		if(( *pcCharacter >= 'a') &&  ( *pcCharacter <= 'z'))
		{
			*pcCharacter = 'A' +  (*pcCharacter - 'a');
		}
		break;

	default:
		break;
	}

	return 1;
}


static void ClearLine( int xInput, int yInput )
{
	int nWidth;

	// Erase all text
	nWidth =  128;

	_SetArea( xInput, yInput, xInput + nWidth, yInput + _SIZE_MEDIUM_, _OFF_ );
}


//
// Graphic Text Management
//

static void TEXT_UpdateBoundingBox( T__TEXT *pText )
{
	pText->m_nW = StringWidth( pText->m_szText );
	pText->m_nH = _SIZE_MEDIUM_;
}

static void TEXT_Create( T__TEXT *pText, int nX, int nY, int nMaxLen, int bNumerical,
						 const char *szDefault )
{
	// Set Text.
	pText->m_szText = (char *) umalloc( nMaxLen );
	strncpy( pText->m_szText, szDefault, nMaxLen - 1 );
	pText->m_szText[ nMaxLen -1 ] = '\0';

	pText->m_nMaxLen = nMaxLen;

	// Update Bounding Box.
	pText->m_nX = nX;
	pText->m_nY = nY;
	TEXT_UpdateBoundingBox( pText );

	//
	pText->m_bNumerical = bNumerical;

	//
	pText->m_nCursor = strlen( pText->m_szText );
	pText->m_nXCursor = -1;
	pText->m_nYCursor = -1;
}


static void TEXT_Delete( T__TEXT *pText )
{
	if( pText->m_szText != NULL )
	{
		ufree( pText->m_szText );
	}
}

static void TEXT_Erase( T__TEXT *pText )
{
	_SetArea( pText->m_nX, pText->m_nY, 
			  pText->m_nX + pText->m_nW, 
			  pText->m_nY + pText->m_nH, _OFF_ );

	if( pText->m_nXCursor != -1 )
	{
		_DrawLine( pText->m_nXCursor,	pText->m_nYCursor,
				  pText->m_nXCursor+4,	pText->m_nYCursor, 
				  _OFF_ );
	}
}


static void TEXT_Display( T__TEXT *pText, int bErase )
{
	// Display the string
	char tc[2];

	int xCursor, yCursor;
	int x, y;

	int i = 0;
	int len = strlen( pText->m_szText );


	tc[1] = '\0';

	if( bErase )
	{
		TEXT_Erase( pText );
	}

	x = pText->m_nX;
	y = pText->m_nY;

	xCursor = x;
	yCursor = y + _SIZE_MEDIUM_;

	for( i = 0; i < len; i++ )
	{
		tc[0] = pText->m_szText[i];
		if( i == pText->m_nCursor )
		{
			xCursor = x;
		}

		_DrawString( tc, x, y, _OFF_ );

		x += StringWidth( tc );
	}

	if( pText->m_nCursor >= len )
	{
		xCursor = x;
	}

	// Draw Cursor.
	pText->m_nXCursor = xCursor;
	pText->m_nYCursor = yCursor;

	_DrawLine( xCursor, yCursor, xCursor + 4, yCursor, _ON_ );

	//
	PaintGraphics();
}

static int TEXT_InsertCharacter( T__TEXT *pText, char cCharacter, int bReplace, int bCursor )
{
	int nLen = strlen( pText->m_szText );
	int i;

	if(( pText->m_nCursor < pText->m_nMaxLen - 1 ) &&
	   ((bReplace) || ( nLen < pText->m_nMaxLen - 1 )))
	{
		// Erase 
		TEXT_Erase( pText );

		if( cCharacter != 0 )
		{
			if( bReplace == 0)
			{
				// Insert Character.
				i = nLen;
				while( i >= pText->m_nCursor )
				{
					pText->m_szText[i+1] = pText->m_szText[i];
					i--;
				}
			}

			pText->m_szText[pText->m_nCursor] = cCharacter;

			if( nLen == pText->m_nCursor )
			{
				pText->m_szText[pText->m_nCursor + 1] = '\0';
			}
		}

		if( bCursor )
		{
			pText->m_nCursor++;
		}

		// Update the bounding box.
		TEXT_UpdateBoundingBox( pText );

		// Display new text.
		TEXT_Display( pText, 0 );

		return 1;
	}

	return 0;
}


static int TEXT_EraseCharacter( T__TEXT *pText )
{
	int i;

	if( pText->m_nCursor > 0 )
	{
		// Erase 
		TEXT_Erase( pText );

		i = pText->m_nCursor - 1;

		memmove(&pText->m_szText[i], &pText->m_szText[i+1],(strlen(&pText->m_szText[i+1])+1));


#if 0
		while( pText->m_szText[i+1] != '\0' )
		{
			pText->m_szText[i] = pText->m_szText[i+1];
			i++;
		}
#endif


		pText->m_szText[i] = '\0';
		pText->m_nCursor--;

		// Update the bounding box.
		TEXT_UpdateBoundingBox( pText );

		// Display new text.
		TEXT_Display( pText, 0 );

		return 1;
	}

	return 0;
}

static void TEXT_MoveCursor( T__TEXT *pText, int nDeltaCursor, int bRedraw )
{
	int nCursor = pText->m_nCursor + nDeltaCursor;
	int nLen = strlen( pText->m_szText );
	
	if( nCursor < 0 )
	{
		nCursor = 0;
	}

	if( nCursor > nLen )
	{
		nCursor = nLen;
	}

	pText->m_nCursor = nCursor;

	if( bRedraw )
	{
		// Display new text.
		TEXT_Display( pText, 1 );
	}
}



static int HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const char* Items[], int nBanners )
{
	int nSizeX;
	int nSizeY;
	StructList Menu;
	int i;
	
	int nInput;
	int nReturn;

	int nBannerHeight = 0;


	ENTRY_BUFFER Entry;

	if ((nDefaultChoice < 0) || (nDefaultChoice >= nItems))
		nDefaultChoice = 0;

	GetScreenSize(&nSizeY, &nSizeX);

	CreateGraphics(_MEDIUM_);

	switch( nBanners )
	{
	case __ONE_BANNER:
		nBannerHeight = 12;
		break;

	case __ALL_BANNERS:
		nBannerHeight = 19;
		break;

	case __NO_BANNER:
	default:
		nBannerHeight = 0;
		break;
	}

	memset(&Menu, 0, sizeof(Menu));
	Menu.MyWindow.left = 0;
	Menu.MyWindow.top = nBannerHeight;
	Menu.MyWindow.rigth = nSizeX - 1;
	Menu.MyWindow.bottom = nSizeY - 1;
	if (nSizeY == 128)
	{
		Menu.MyWindow.nblines = 10;
	}
	else
	{
		Menu.MyWindow.nblines = 5;
	}

	Menu.MyWindow.fontsize = _MEDIUM_;
	Menu.MyWindow.type = _PROPORTIONNEL_;
	Menu.MyWindow.font = 0;
	Menu.MyWindow.correct = _ON_;
	Menu.MyWindow.offset = 0;
	Menu.MyWindow.shortcommand = _ON_;
	if (bRadioButtons)
		Menu.MyWindow.selected = _ON_;
	else Menu.MyWindow.selected = _OFF_;
	Menu.MyWindow.thickness = 2;
	Menu.MyWindow.border = _ON_;
	Menu.MyWindow.popup = _NOPOPUP_;
	Menu.MyWindow.first = nDefaultChoice;
	Menu.MyWindow.current = nDefaultChoice;
	Menu.MyWindow.time_out = 60;
	Menu.MyWindow.title = (unsigned char*)szTitle;

	for(i = 0; i < nItems; i++)
		Menu.tab[i] = (unsigned char*)Items[i];

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

	return nReturn;
}


// Functions.
//-------------------------------------------------------------------

void DisplayText( const char *szInput, int x, int y, int index, int bErase, int bInvert  )
{
	// Display the string
	char tc[2];

	int xCursor, yCursor;

	int nInvert = _OFF_;

	int i = 0;
	int len = strlen( szInput );

	tc[1] = '\0';

	if( bErase == 1 )
	{
		ClearLine( x, y );
	}

	if( bInvert )
	{
		nInvert = _ON_;
	}

	xCursor = x;
	yCursor = y + _SIZE_MEDIUM_;

	for( i = 0; i < len; i++ )
	{
		tc[0] = szInput[i];
		if( i == index )
		{

			xCursor = x;
		}

		_DrawString( tc, x, y, nInvert );

		x += StringWidth( tc );
	}

	if( index >= len )
	{
		xCursor = x;
	}

	if( index != -1 )
	{
		_DrawLine( xCursor, yCursor, xCursor + 4, yCursor, _ON_ );
	}

	PaintGraphics();
}

//
void DisplayScreen( const char *szLine1, const char *szLine2 )
{
	DisplayText( szLine1, 2, 20, -1, __TRUE__, __FALSE__ );
	DisplayText( szLine2, 2, 30, -1, __TRUE__, __FALSE__ );
}



//
int HelperManageInput( char *szLabel, int xLabel, int yLabel,
					   char *szInput, int xInput, int yInput, 
					   int nMaxLen, int bNumerical, int nMode, int nTimeout )
{
	FILE* hKeyboard;


	int nResult	= 0;

	int nKey1		= 0;
	int nKey2		= 0;
	int nKeyIndex	= 0;
	char Character	= '\0';

	// int n;
	T__TEXT Text;

	int nState;

	nResult = 1;
	nState = STATE_INPUT_WAIT_KEY;

	CreateGraphics(_MEDIUM_);

	TEXT_Create( &Text, xInput, yInput, nMaxLen,  bNumerical, szInput );

	// Display title.
	if( szLabel != NULL )
	{
		DisplayText( szLabel, xLabel, yLabel, -1, __FALSE__, __FALSE__ );
	}

	// Display input field.
	TEXT_Display( &Text, 1 );


	//
	hKeyboard = fopen("KEYBOARD", "r");

	while( nState !=  STATE_INPUT_END )
	{
		switch( nState )
		{
			case STATE_INPUT_WAIT_KEY:
			{
				// Wait a key
				if( ttestall(KEYBOARD, nTimeout ) == KEYBOARD ) 
				{
					nKey1 = getchar();

					// Monitor key Step.
					switch( nKey1 )
					{
					case T_CORR:
						// Arrow keys.
						TEXT_EraseCharacter( &Text );
						break;

					case T_SK1: // Left
						// Arrow keys.
						TEXT_MoveCursor( &Text, -1, 1 );
						break;

					case T_SK4: // Right
						// Arrow keys.
						TEXT_MoveCursor( &Text, 1, 1 );
						break;

					case T_VAL: 
						nResult = __ENTER_KEY;
						nState =  STATE_INPUT_END;
						break;

					case T_SK2: // Back
						nResult = __BACK_KEY;
						nState =  STATE_INPUT_END;
						break;

					case T_ANN:
						nResult = __EXIT_KEY;
						nState =  STATE_INPUT_END;					
						break;

					case T_NUM0:
					case T_NUM1:
					case T_NUM2:
					case T_NUM3:
					case T_NUM4:
					case T_NUM5:
					case T_NUM6:
					case T_NUM7:
					case T_NUM8:
					case T_NUM9:
					case T_POINT:
						nState = STATE_INPUT_KEY_STEP;
						nKeyIndex = 0;

						if( GetNextCharacter( nKey1, nMode, &nKeyIndex, &Character ) != 0 )
						{
							TEXT_InsertCharacter( &Text, Character, 0, 0 );
						}
						break;
					}
				}
				else
				{
						nState = STATE_INPUT_END;
						nResult = 0; // Timeout;
				}
			}
			break;

			case STATE_INPUT_KEY_STEP:
			{
				// Monitor key Step.
				Character = nKey1;

				if(( bNumerical == 0) &&  ( ttestall(KEYBOARD, 100 ) == KEYBOARD )) 
				{
					nKey2 = getchar();

					if( nKey1 != nKey2 )
					{
						nKey1 = nKey2;
						Character = nKey1;

						switch( nKey1 )
						{
						case T_CORR:
							// Arrow keys.
							TEXT_EraseCharacter( &Text );
							nState = STATE_INPUT_WAIT_KEY;
							break;

						
						case T_SK1: // Left
							// Arrow keys.
							TEXT_MoveCursor( &Text, -1, 1 );
							break;

						case T_SK4: // Right
							// Arrow keys.
							TEXT_MoveCursor( &Text, 1, 1 );
							nState = STATE_INPUT_WAIT_KEY;
							break;

						case T_VAL: 
							nResult = __ENTER_KEY;
							nState =  STATE_INPUT_END;
							break;

						case T_SK2: // Back
							nResult = __BACK_KEY;
							nState =  STATE_INPUT_END;
							break;


						case T_ANN:
							nResult = __EXIT_KEY;
							nState =  STATE_INPUT_END;					
							break;

						case T_NUM0:
						case T_NUM1:
						case T_NUM2:
						case T_NUM3:
						case T_NUM4:
						case T_NUM5:
						case T_NUM6:
						case T_NUM7:
						case T_NUM8:
						case T_NUM9:
						case T_POINT:
							nKeyIndex = 0;
							TEXT_InsertCharacter( &Text, 0, 0, 1 );
							TEXT_InsertCharacter( &Text, Character, 1, 0 );
							break;
						}
					}
					else
					{
						// Rotate on the same key.
						if( GetNextCharacter( nKey1, nMode, &nKeyIndex, &Character ) != 0 )
						{
							TEXT_InsertCharacter( &Text, Character, 1, 0 );
						}
						else
						{
							// ??
						}
					}
				}
				else
				{
					// Just advance cursor.
					TEXT_InsertCharacter( &Text, 0, 0, 1 );
					nState = STATE_INPUT_WAIT_KEY;
				}
			}
			break;
		}
	}

	fclose(hKeyboard);

	//
	if( nResult == __ENTER_KEY )
	{
		strcpy( szInput, Text.m_szText );
	}

	// Delete Text field.
	TEXT_Delete( &Text );

	return nResult;
}


int HelperDisplaySelection( char *szLabel, int xLabel, int yLabel, 
							int xInput, int yInput,
							int nItems, const char**Items,
							int nBanners, int nTimeout, int *pnSelected )
{
	FILE* hKeyboard;

	int nResult	= 0;
	int nKey	= 0;

	int nState = STATE_INPUT_WAIT_KEY;

	int nIndex = 0;

	//
	CreateGraphics( _MEDIUM_ );

	// Display title.
	if( szLabel != NULL )
	{
		DisplayText( szLabel, xLabel, yLabel, -1, __FALSE__, __FALSE__ );
	}

	//
	if( nItems > 0 )
	{
		hKeyboard = fopen( "KEYBOARD", "r" );

		while( nState !=  STATE_INPUT_END )
		{
			DisplayText( Items[nIndex], xInput, yInput, -1, __TRUE__, __TRUE__  );

			// Wait a key
			if( ttestall( KEYBOARD, nTimeout ) == KEYBOARD ) 
			{
				nKey = getchar();

				// Monitor key Step.
				switch( nKey )
				{
				case UP:
					nIndex++;
					if( nIndex >= nItems ) nIndex = 0;
					break;

				case DOWN: 
					nIndex--;
					if( nIndex < 0 ) nIndex = nItems - 1;
					break;

				case T_VAL: 
					*pnSelected = nIndex;
					nResult = __ENTER_KEY;
					nState =  STATE_INPUT_END;
					break;

				case T_ANN:
					nResult = __EXIT_KEY;
					nState =  STATE_INPUT_END;					
					break;

				default:
					break;
				}
			}
			else
			{
				nState = STATE_INPUT_END;
				nResult = 0; // Timeout;
			}
		}

		fclose( hKeyboard );
	}

	//
	return nResult;
}




int HelperDisplayMenu( const char* szTitle, int nDefaultChoice,
					   int nItems, const char** Items,
					   int nBanners )
{
	return HelperDisplayMenuInternal( szTitle, FALSE, nDefaultChoice, 
									  nItems, Items, nBanners );
}

int HelperDisplayChoices( const char* szTitle, int nDefaultChoice,
						  int nItems, const char* Items[],
					      int nBanners )

{
	return HelperDisplayMenuInternal( szTitle, TRUE, nDefaultChoice, 
									  nItems, Items,
									  nBanners );
}

int PrintText( char *szText, int bClose )
{
	static FILE* hPrinter = NULL;

	if( hPrinter == NULL )
	{
		hPrinter = fopen( "PRINTER", "w-" );
	}

	if( hPrinter != NULL )
	{
		fprintf( hPrinter, szText );

		if( bClose == 1 )
		{
			ttestall ( PRINTER , 0 );
			fclose( hPrinter );
			hPrinter = NULL;
		}

		return 1;
	}

	return 0;
}

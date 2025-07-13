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
 * @author        Erick COURSANGE
 * @version       
 * @Comment:      
 * @date:         
 */

#include <sdk30.h>
#include "fontlib.h"

/*-------------------------------------------------------------------------*
 * function:    TestPrinter
 * @brief:		test the printing of a string using a signed FON file
 */
void TestPrinter(void)
{
	FILE *hPrinter;
	char *Russian, *German, *Polish, *Arabic, *Greek, *Turkish;

	hPrinter  = fopen( "PRINTER",  "w" );

	printf("  Printer test");
	pprintf("\x1B""@");

	//===================== ISO8859-1 test
	// Load the SGN files in memory
	German=LoadFont("/SYSTEM/ISO1.SGN");
	if(German == NULL )
	{
		printf("file not found :\n /SYSTEM/ISO1.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(German);

		// Define the left and the right margins
		DefPrinterMargins(0,150);
		pprintf8859((unsigned char*)"Right margin has been defined to 150\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		DefPrinterMargins(150,0);
		pprintf8859((unsigned char*)"Left margin has been defined to 150\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		DefPrinterMargins(100,100);
		pprintf8859((unsigned char*)"Right and Left margins have been defined to 100\n\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		DefPrinterMargins(0,0);

		// Print the demo in BOLD mode
		pprintf8859((unsigned char*)"ISO 8859-1 DEMO\nGerman message\n\n",_ON_,_pBOLD_,_PROP_WIDTH_);
		// print German welcome ISO8859 coded
		pprintf8859((unsigned char*)"\x4D\x69\x74\x20\x66\x72\x65\x75\x6E\x64\x6C\x69\x63\x68\x65\x6E\x20\x67\x72\xFC\xDF\x65\x6E\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		// print German welcome UNICODE coded
		pprintfUnicode((unsigned char*)"\x00\x4D\x00\x69\x00\x74\x00\x20\x00\x66\x00\x72\x00\x65\x00\x75\x00\x6E\x00\x64\x00\x6C\x00\x69\x00\x63\x00\x68\x00\x65\x00\x6E\x00\x20\x00\x67\x00\x72\x00\xFC\x00\xDF\x00\x65\x00\x6E\x00\n\x00\n",_OFF_,_pBOLD_,_PROP_WIDTH_);

		// Print all the characters of the ISO1.SGN file in BOLD mode
		pprintf8859((unsigned char*)"        FONT DUMP\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		PrintPolice(_pBOLD_,_PROP_WIDTH_);	
	}


	//===================== ISO8859-2 test
	// Load the SGN files in memory
	Polish=LoadFont("/SYSTEM/ISO2.SGN");
	if(Polish == NULL )
	{
		printf("file not found \n /SYSTEM/ISO2.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(Polish); 
	
		// Print the demo in BOLD mode
		pprintf8859((unsigned char*)"ISO 8859-2 DEMO\nPolish message\n\n",_ON_,_pBOLD_,_PROP_WIDTH_);
		// print Polish welcome ISO8859 coded
		pprintf8859((unsigned char*)"\x50\x6F\xBF\xB1\x64\x61\x6E\x79\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		// print Polish welcome UNICODE coded
		pprintfUnicode((unsigned char*)"\x00\x50\x00\x6F\x01\x7C\x01\x05\x00\x64\x00\x61\x00\x6E\x00\x79\x00\n\x00\n\x00",_OFF_,_pBOLD_,_PROP_WIDTH_);

		// Print all the characters of the ISO2.SGN file in BOLD mode
		pprintf8859((unsigned char*)"        FONT DUMP\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		PrintPolice(_pBOLD_,_PROP_WIDTH_);
	}


	//===================== ISO8859-3 test
	// Load the SGN files in memory
	Turkish=LoadFont("/SYSTEM/ISO3.SGN");
	if(Turkish == NULL )
	{
		printf("file not found :\n /SYSTEM/ISO3.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(Turkish);

		// Print the demo in BOLD mode
		pprintf8859((unsigned char*)"ISO 8859-3 DEMO\nTurkish message\n\n",_ON_,_pBOLD_,_PROP_WIDTH_);
		// print Turkish welcome ISO8859 coded
		pprintf8859((unsigned char*)"\x47\xFC\x6E\x61\x79\x64\x69\x6E\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		// print Turkish welcome UNICODE coded
		pprintfUnicode((unsigned char*)"\x00\x47\x00\xFC\x00\x6E\x00\x61\x00\x79\x00\x64\x00\x69\x00\x6E\x00\n\x00\n",_OFF_,_pBOLD_,_PROP_WIDTH_);

		// Print all the characters of the ISO3.SGN file in BOLD mode
		pprintf8859((unsigned char*)"        FONT DUMP\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		PrintPolice(_pBOLD_,_PROP_WIDTH_);	
	}


	//===================== ISO8859-5 test
	// Load the SGN files in memory
	Russian=LoadFont("/SYSTEM/ISO5.SGN");
	if(Russian == NULL)
	{
		printf("file not found \n /SYSTEM/ISO5.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(Russian);
	
		// Print the demo in BOLD mode
		pprintf8859((unsigned char*)"ISO 8859-5 DEMO\nRussian message\n\n",_ON_,_pBOLD_,_PROP_WIDTH_);
		// print Russian welcome ISO8859 coded
		pprintf8859((unsigned char*)"\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		// print Russian welcome UNICODE coded
		pprintfUnicode((unsigned char*)"\x04\x14\x04\x1E\x04\x11\x04\x20\x04\x1E\x00\x20\x04\x1F\x04\x1E\x04\x16\x04\x10\x04\x1B\x04\x1E\x04\x12\x04\x10\x04\x22\x04\x2C\x00\n\x00\n\x00",_OFF_,_pBOLD_,_PROP_WIDTH_);

		// Print all the characters of the ISO5.SGN file in BOLD mode
		pprintf8859((unsigned char*)"        FONT DUMP\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		PrintPolice(_pBOLD_,_PROP_WIDTH_);
	}


	//===================== ISO8859-6 test
	// Load the SGN files in memory
	Arabic=LoadFont("/SYSTEM/ISO6.SGN");
	if(Arabic == NULL)
	{
		printf("file not found \n /SYSTEM/ISO6.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(Arabic);

		// Print the demo in BOLD mode
		pprintf("\x1B""E""ISO 8859-6 DEMO\nArabic message\n\n");
		// print Arabic message  ISO8859 coded
		pprintf8859((unsigned char*)"\xC7\xE4\xD3\xE4\xC7\xE5\x20\xD9\xE4\xEA\xE3\xE5\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		// print Arabic message  UNICODE coded
		pprintfUnicode((unsigned char*)"\xFE\x8D\xFE\xDF\xFE\xB4\xFE\xFC\xFE\xE1\x00\x20\xFE\xCB\xFE\xE0\xFE\xF4\xFE\xDC\xFE\xE2\x0\n\x0\n\x0",_OFF_,_pBOLD_,_PROP_WIDTH_);

		// Print all the characters of the ISO6.SGN file in BOLD mode
		pprintf("\x1B""E""        FONT DUMP\n\n""\x1B""@");
		PrintPolice(_pBOLD_,_PROP_WIDTH_);
	}

		//===================== ISO8859-7 test
	// Load the SGN files in memory
	Greek=LoadFont("/SYSTEM/ISO7.SGN");
	if(Greek == NULL)
	{
		printf("file not found \n /SYSTEM/ISO7.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(Greek);

		// Print the demo in BOLD mode
		pprintf8859((unsigned char*)"ISO 8859-7 DEMO\nGreek message\n\n",_ON_,_pBOLD_,_PROP_WIDTH_);
		// print Greek message  ISO8859 coded
		pprintf8859((unsigned char*)"\xEA\xE1\xEB\xE7\xEC\xDD\xF1\xE1\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		// print Greek message  UNICODE coded
		pprintfUnicode((unsigned char*)"\x03\xBA\x03\xB1\x03\xBB\x03\xB7\x03\xBC\x03\xAD\x03\xC1\x03\xB1\x00\n\x00\n\x00",_OFF_,_pBOLD_,_PROP_WIDTH_);

		// Print all the characters of the ISO7.SGN file in BOLD mode
		pprintf8859((unsigned char*)"        FONT DUMP\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
		PrintPolice(_pBOLD_,_PROP_WIDTH_);
	}

	pprintf("\n\n\n");
	ttestall(PRINTER,0);
	fclose(hPrinter);
}

/*-------------------------------------------------------------------------*
 * function:    TestDisplay
 * @brief:		test the diplay of a string using a signed FON file
 */
void  TestDisplay(void)
{
	char *Russian, *German, *Polish, *Arabic, *Greek, *Turkish;
	int ret;

	ret=PSQ_Is_pinpad();
	if(ret!=0)
	{
		ret=PSQ_Pinpad_Type();
		if (ret!=0) // PPC or PPR
			InitContext(PERIPH_PPR);
	}

	//===================== ISO8859-1 test
	German=LoadFont("/SYSTEM/ISO1.SGN");	// Load the SGN file in memory
	if(German == NULL )
	{
		printf("file not found :\n /SYSTEM/ISO1.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(German);
	
		_clrscr();

		// Display the demo in MEDIUM mode
		DrawExtendedString(0,0,"ISO 8859-1 DEMO\nGerman message\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		// display German welcome ISO8859 coded
		DrawExtendedString8859(0,21,(unsigned char*)"\x4D\x69\x74\x20\x66\x72\x65\x75\x6E\x64\x6C\x69\x63\x68\x65\x6E\x20\n\x67\x72\xFC\xDF\x65\x6E",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		// display German welcome UNICODE coded
		DrawExtendedStringUnicode(0,43,(unsigned char*)"\x00\x4D\x00\x69\x00\x74\x00\x20\x00\x66\x00\x72\x00\x65\x00\x75\x00\x6E\x00\x64\x00\x6C\x00\x69\x00\x63\x00\x68\x00\x65\x00\x6E\x00\n\x00\x67\x00\x72\x00\xFC\x00\xDF\x00\x65\x00\x6E",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		getchar();
	}

	
	//===================== ISO8859-2 test
	Polish=LoadFont("/SYSTEM/ISO2.SGN");	// Load the SGN file in memory
	if(Polish == NULL )
	{
		printf("file not found \n /SYSTEM/ISO2.SGN");
		ttestall(0,300);
	}
	else
	{
		_clrscr();

		// Register the font used by the application
		DefCurrentFont(Polish);

		//Display the demo in MEDIUM mode
		DrawExtendedString(0,0,"ISO 8859-2 DEMO\nPolish message\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		// display Polish welcome ISO8859 coded
		DrawExtendedString8859(0,25,(unsigned char*)"\x50\x6F\xBF\xB1\x64\x61\x6E\x79",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		// display Polish welcome UNICODE coded
		DrawExtendedStringUnicode(0,35,(unsigned char*)"\x00\x50\x00\x6F\x01\x7C\x01\x05\x00\x64\x00\x61\x00\x6E\x00\x79",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		
		DrawExtendedString(0,50,"press a key\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		getchar();
	}

	//===================== ISO8859-3 test
	Turkish=LoadFont("/SYSTEM/ISO3.SGN");	// Load the SGN file in memory
	if(Turkish == NULL )
	{
		printf("file not found \n /SYSTEM/ISO3.SGN");
		ttestall(0,300);
	}
	else
	{
		_clrscr();

		// Register the font used by the application
		DefCurrentFont(Turkish);

		//Display the demo in MEDIUM mode
		DrawExtendedString(0,0,"ISO 8859-3 DEMO\nTurkish message\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		// display Turkish welcome ISO8859 coded
		DrawExtendedString8859(0,25,(unsigned char*)"\x47\xFC\x6E\x61\x79\x64\x69\x6E",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		// display Turkish welcome UNICODE coded
		DrawExtendedStringUnicode(0,35,(unsigned char*)"\x00\x47\x00\xFC\x00\x6E\x00\x61\x00\x79\x00\x64\x00\x69\x00\x6E",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		
		DrawExtendedString(0,50,"press a key\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		getchar();
	}

	//===================== ISO8859-5 test
	Russian=LoadFont("/SYSTEM/ISO5.SGN");	// Load the SGN file in memory
	if(Russian == NULL)
	{
		printf("file not found \n /SYSTEM/ISO5.SGN");
		ttestall(0,300);
	}
	else
	{
		_clrscr();

		// Register the font used by the application
		DefCurrentFont(Russian);

		//Display the demo in MEDIUM mode
		DrawExtendedString(0,0,"ISO 8859-5 DEMO\nRussian message\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		// display Russian welcome ISO8859 coded
		DrawExtendedString8859(0,25,(unsigned char*)"\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		// display Russian welcome UNICODE coded
		DrawExtendedStringUnicode(0,35,(unsigned char*)"\x04\x14\x04\x1E\x04\x11\x04\x20\x04\x1E\x00\x20\x04\x1F\x04\x1E\x04\x16\x04\x10\x04\x1B\x04\x1E\x04\x12\x04\x10\x04\x22\x04\x2C\x00\n\x00\n\x00\n",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		
		DrawExtendedString(0,50,"press a key\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		getchar();
	}

//===================== ISO8859-6 test
	Arabic=LoadFont("/SYSTEM/ISO6.SGN");	// Load the SGN file in memory
	if(Arabic == NULL)
	{
		printf("file not found \n /SYSTEM/ISO6.SGN");
		ttestall(0,300);
	}
	else
	{
		_clrscr();
		//Display the demo in MEDIUM mode
		DrawExtendedString(0,0,"ISO 8859-6 DEMO\nArabic message\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);

		DefCurrentFont(Arabic);
		// display Arabic welcome ISO8859 coded
		DrawExtendedString8859(0,23,(unsigned char*)"\xC7\xE4\xD3\xE4\xC7\xE5\x20\xD9\xE4\xEA\xE3\xE5",_OFF_,_dMEDIUM_,_PROP_WIDTH_);
		// display Arabic welcome UNICODE coded
		DrawExtendedStringUnicode(0,37,(unsigned char*)"\xFE\x8D\xFE\xDF\xFE\xB4\xFE\xFC\xFE\xE1\x00\x20\xFE\xCB\xFE\xE0\xFE\xF4\xFE\xDC\xFE\xE2\x00",_OFF_,_dMEDIUM_,_PROP_WIDTH_);

		DrawExtendedString(0,50,"press a key\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		getchar();
	}

	//===================== ISO8859-7 test
	Greek=LoadFont("/SYSTEM/ISO7.SGN");	// Load the SGN file in memory
	if(Greek == NULL)
	{
		printf("file not found \n /SYSTEM/ISO7.SGN");
		ttestall(0,300);
	}
	else
	{
		_clrscr();
		//Display the demo in MEDIUM mode
		DrawExtendedString(0,0,"ISO 8859-7 DEMO\nGreek message\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);

		DefCurrentFont(Greek);
		// display Greek welcome ISO8859 coded
		DrawExtendedString8859(0,23,(unsigned char*)"\xEA\xE1\xEB\xE7\xEC\xDD\xF1\xE1",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);
		// display Greek welcome UNICODE coded
		DrawExtendedStringUnicode(0,37,(unsigned char*)"\x03\xBA\x03\xB1\x03\xBB\x03\xB7\x03\xBC\x03\xAD\x03\xC1\x03\xB1\x00",_OFF_,_dMEDIUM_,_FIXED_WIDTH_);

		DrawExtendedString(0,50,"press a key\n",_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		getchar();
	}

	_clrscr();
	PaintGraphics();
	
	InitContext(PERIPH_DISPLAY);
}

/*-------------------------------------------------------------------------*
 * function:    LoadBMP
 * @brief:		Load a BMP file in memory
 */
unsigned char *LoadBMP(char *BmpFileName)
{
	int k;
	char Disk[50];		
	char FileName[50];	
	int NameOK=0;
	S_FS_FILE *fdin;
	unsigned long fileLength;
	S_FS_PARAM_CREATE ParamCreat;
	int rc;
	unsigned char *BufferBmp;

	// get disk name
	if(BmpFileName[0]=='/')
	{
		for(k=1;k<strlen(BmpFileName);k++)
		{
			if(BmpFileName[k]=='/')
			{
				strncpy(Disk,BmpFileName,k);
				Disk[k]=0x0;
				sprintf(FileName,&BmpFileName[k+1]);
				NameOK=1;
				break;
			}
		}
	}
	if(NameOK==0)
		return(NULL);
	
	ParamCreat.Mode = FS_READMOD;
	rc = FS_mount(Disk,&ParamCreat.Mode);
	if(rc!=FS_OK) // unable to mount the disk
		return(NULL);
	
	fdin=FS_open(BmpFileName,"r");
	if(fdin==NULL) //unable to open the file
		return(NULL);		

	// Sizing Buffer memory length
	FS_seek(fdin,0,SEEK_END);
	fileLength=FS_tell(fdin);
	BufferBmp = umalloc(fileLength);

	FS_seek(fdin,0,SEEK_SET);
	// Copy to Buffer memory 
	FS_read(BufferBmp,1,fileLength,fdin);
	FS_close(fdin);

	return (BufferBmp);
}


/*-------------------------------------------------------------------------*
 * function:    TestPrinterGraphic
 * @brief:		test the new printer graphic functionalities
 */
void TestPrinterGraphic(void)
{
	FILE *hPrinter;
	char *English;
	unsigned char *bitmap;

	hPrinter  = fopen( "PRINTER",  "w" );

	printf("  Printer test");
	pprintf("\x1B""@");

	// Load the font files in memory
	English=LoadFont("/SYSTEM/ISO1.SGN");
	if(English == NULL )
	{
		printf("file not found :\n /SYSTEM/ISO1.SGN");
		ttestall(0,300);
	}
	else
	{
		// Register the font used by the application
		DefCurrentFont(English);

	// --------- Test printing text and printing bmp file functionalities ---------- //
		
		// Load BMP file			
		bitmap=LoadBMP("/SYSTEM/LOGO.BMP");
		if(bitmap==NULL)
		{
			pprintf("Error:cannot load BMP file\n");
			ttestall(0,300);
		}
		else
		{	
			InitPrinterBitmap(512);
			_pprintf8859XY(0,0,(unsigned char*)"** PRINTER SAMPLE **\n\n",_OFF_,_pBOLD_,_PROP_WIDTH_);
			_pprintf8859((unsigned char*)"Graphic printer test:\n",_OFF_,_pNORMAL_,_FIXED_WIDTH_);
			// Copy the content of the bitmap BMP file in the printer bitmap and print the printer bitmap
			_PrintBmpXY(120,100,bitmap,_OFF_);
			_pprintf8859XY(0,240,(unsigned char*)"BMP file printed !!!\n\n\n",_OFF_,_pNORMAL_,_FIXED_WIDTH_);
			PaintPrinterGraphics();
			// free memory used by the bmp file
			ufree(bitmap);
		}

	// --------- Test drawing functionalities ---------- //
		
		InitContexteGraphique(PERIPH_PRINTER);
		InitPrinterBitmap(512);

		// Print a smiling face that says a message
		
		_DrawRect(0,0,383,320,0,_OFF_,_ON_);		
		// Head
		_DrawEllipse(100,200,100,120,_OFF_);
		// Hat
		_DrawRect(60,70,140,90,1,_ON_,_OFF_);
		_DrawRect(80,60,120,70,0,_OFF_,_OFF_);
		// Left eye
		_DrawEllipse(70,150,20,20,_OFF_);
		_DrawEllipse(70,150,15,10,_ON_);
		_DrawEllipse(70,150,4,6,_OFF_);
		// Right eye
		_DrawEllipse(130,150,20,20,_OFF_);
		_DrawEllipse(130,150,15,10,_ON_);
		_DrawEllipse(130,150,4,6,_OFF_);
		// Mouth
		_DrawRect(58,235,65,255,0,_OFF_,_ON_);
		_DrawRect(60,240,140,260,0,_OFF_,_ON_);
		_DrawEllipse(110,250,15,4,_OFF_);
		_DrawRect(135,235,142,255,0,_OFF_,_ON_);
		// Nose
		_DrawRect(90,190,110,220,1,_ON_,_OFF_);
		// Bubbles
		_DrawCircle(160,220,10,_OFF_);
		_DrawCircle(190,190,17,_OFF_);
		_DrawCircle(230,150,25,_OFF_);
		_DrawEllipse(264,60,120,60,_OFF_);
		_pprintf8859XY(194,40,(unsigned char*)"Graphic printer",_OFF_,_pNORMAL_,_PROP_WIDTH_);
		
		PaintPrinterGraphics();
		InitContexteGraphique(PERIPH_DISPLAY);
	}
	pprintf("\n\n\n");
	ttestall(PRINTER,0);
	fclose(hPrinter);
}


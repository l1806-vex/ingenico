#include <sdk30.h>
#include "MSGlib.h"
#include "MessagesDefinitions.h"	// Messages' name definitions

StructList MenuLang;

#define RU "RU" // Russian
#define AR "AR" // Arabic
#define DE "DE" // German

extern const unsigned char English[]; // Default messages in english

void default_menu ( StructList *Menu )
{
    int              MAXX,MAXY;

	GetScreenSize(&MAXY,&MAXX);
	Menu->MyWindow.left         = 0;                     
	Menu->MyWindow.top          = 0;                     
	Menu->MyWindow.rigth        = (MAXX-1);               
	Menu->MyWindow.bottom       = (MAXY-1);               
	Menu->MyWindow.fontsize     = _MEDIUM_;               
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
    Menu->MyWindow.offset       = 0;
    Menu->MyWindow.selected     = _ON_;                               
    Menu->MyWindow.nblines      = 15;                      
    Menu->MyWindow.type         = _PROP_WIDTH_; 
	Menu->MyWindow.title        = (unsigned char*)"LANGUAGE";
    Menu->tab[0]                = NULL;
}

#ifdef _SIMULPC_
	// This function is used ONLY IN SIMULATION
	// TransfertData copies the local messages from the PC (English.c) 
	// to the terminal (char *LocalMessages variable) to avoid MMU errors.
	extern char * TransfertData(char * msg);
#endif

// Address of the messages copied in the terminal
char *LocalMessages;


/*-------------------------------------------------------------------------*
 * function:    DefaultSettings
 * @brief:		Load the SAMPLEMSG.SGN messages file if this file is present in the terminal
 * @brief:		SAMPLEMSG.SGN allows to customize application's messages and languages
 */
void DefaultSettings(void)
{
	char *NewMessages; 	// Address of the loaded message file
	

#ifdef _SIMULPC_
	// ONLY IN SIMULATION
	// TransfertData copies the local messages from the PC (English.c) 
	// to the terminal (char *LocalMessages variable) to avoid MMU errors.
	LocalMessages=TransfertData((char *)English);
#else
	LocalMessages=(char *)English;
#endif

	default_menu(&MenuLang);

	// Load the message file in memory
	NewMessages=LoadMSG("/SYSTEM/SAMPLEMSG.SGN");	
	if(NewMessages == NULL )
	{
		printf("\x1B""file not found :\n/SYSTEM/SAMPLEMSG.SGN");
		ttestall(0,300);
		// Local messages are used
		DefCurrentMSG(LocalMessages);
	}
	else
	{
		// Messages (from the loaded MSG file) are used
		DefCurrentMSG(NewMessages);
	}
	// Define the messages used by default (if messages are not found in the current MSG file)
	DefDefaultMSG(LocalMessages);
	// Define current and default languages (English)
	DefCurrentLang(EN);
	DefDefaultLang(EN);
}

/*-------------------------------------------------------------------------*
 * function:    LanguageSelection
 * @brief:		Menu that allows to choose the application language
 */
void LanguageSelection(void)
{
	char Languages[16];
	char NewLanguagesTab[5][3];
	int i;
	int nInput;
	ENTRY_BUFFER Entry;
	int NbLang;		 // Number of languages in the loaded MSG file
	int NbNewLang=0; // New languages (not english) in the loaded MSG file
	MenuLang.tab[0]=(unsigned char*)EN; // English messages are always defined (local messages)
	
	// Get the languages supported by the application (local:English or loaded MSG file:Russian...)
	NbLang=GetSupportedLanguages(Languages,GetCurrentMSG());
	for(i=0;i<NbLang;i++)
	{
		if((strncmp(Languages+(i*2),EN,2))!=0)
		{ 
			// Copy the ISO639-1 language code
			strncpy(NewLanguagesTab[NbNewLang],Languages+(i*2),2);
			NewLanguagesTab[NbNewLang][2]='\x00';
			// Initialize menu
			MenuLang.tab[NbNewLang+1]=(unsigned char*)NewLanguagesTab[NbNewLang];
			
			NbNewLang++;
		}
	}
	MenuLang.tab[NbNewLang+1]=NULL;
	
	// Get the user's choice
	G_List_Entry((void*)&MenuLang);
	ttestall(ENTRY,0);
	nInput = Get_Entry((void*)&Entry);
	switch( nInput )
	{
	case CR_ENTRY_OK:
		MenuLang.MyWindow.current=Entry.d_entry[0];
		// Change current language	
		DefCurrentLang((char*)MenuLang.tab[Entry.d_entry[0]]);
		break;
	default:
		break;
	}
}

/*-------------------------------------------------------------------------*
 * function:    TestPrinter
 * @brief:		Print messages in the application's current language
 */
void TestPrinter(void)
{
	FILE *hPrinter;
	
	hPrinter  = fopen( "PRINTER",  "w" );

	pprintf("\x1B""E");
	pprintf("*****************************\n");
	pprintf("****     Printer test      ****\n");
	pprintf("*****************************\n\n");
	pprintf("\x1B""@");

	PrintMSG(PRINTER_LANGUAGE,_OFF_,_pBOLD_,_FIXED_WIDTH_);
	PrintMSG(PRINTER_HELLO,_OFF_,_pNORMAL_,_FIXED_WIDTH_);
	
	pprintf("\n\n\n");
	ttestall(PRINTER,0);
	fclose(hPrinter);
}

/*-------------------------------------------------------------------------*
 * function:    TestDisplay
 * @brief:		Display messages in the application's current language
 */
void  TestDisplay(void)
{
	// Clear the screen
	_clrscr();

	_DisplayMSG(40,0,DISPLAY_LANGUAGE,_ON_,_dLARGE_,_PROP_WIDTH_);
	DisplayMSG(0,21,DISPLAY_HELLO,_OFF_,_dMEDIUM_,_FIXED_WIDTH_);

	getchar();
}

/*-------------------------------------------------------------------------*
 * function:    OtherTest
 * @brief:		Test other functionalities that use MSG files
 */
void OtherTest(void)
{
	FILE *hPrinter;
	MSGinfos MSGtest;
	
	hPrinter  = fopen( "PRINTER",  "w" );

	pprintf("\x1B""E");
	pprintf("******************************\n");
	pprintf("** MSG functions tests **\n");
	pprintf("******************************\n\n");
	pprintf("\x1B""@");

	// Test GetManagerLanguage function
	pprintf("Manager language : %s\n\n",GetManagerLanguage());
	
	// Test GetFileType and GetAppliType functions
	pprintf("File Type : %X\nApplication Type : %X\n\n",GetFileType(),GetAppliType()); 
	
	// Test InitMSGinfos and PrintMSGInfos functions
	InitMSGinfos(&MSGtest);
	MSGtest.message="Message using default font\n\n";
	PrintMSGInfos(&MSGtest,_OFF_,_pNORMAL_,_FIXED_WIDTH_);
	
	// Test GetMessageInfos function
	GetMessageInfos(PRINTER_HELLO,&MSGtest);
	PrintMSGInfos(&MSGtest,_OFF_,_pNORMAL_,_FIXED_WIDTH_);
	
	// Test LanguageExist, GetMessageInfosInLang and InitMSGinfos_message functions
	if(LanguageExist(RU,GetCurrentMSG())==0)
		GetMessageInfosInLang(RU,PRINTER_HELLO,&MSGtest);
	else
		InitMSGinfos_message(&MSGtest,"Russian is not supported\n\n");
	PrintMSGInfos(&MSGtest,_OFF_,_pNORMAL_,_FIXED_WIDTH_);
		
	// Test GetSpecificMessage function
	GetSpecificMessage(LocalMessages,(unsigned char*)EN,GetFileType(),GetAppliType(),PRINTER_HELLO,&MSGtest);
	PrintMSGInfos(&MSGtest,_OFF_,_pNORMAL_,_FIXED_WIDTH_);

	pprintf("\n\n\n");
	ttestall(PRINTER,0);
	fclose(hPrinter);
}


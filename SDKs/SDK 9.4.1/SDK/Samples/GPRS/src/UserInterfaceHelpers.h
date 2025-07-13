#define __ENTER_KEY		-1
#define __BACK_KEY		-2
#define __EXIT_KEY		-3

#define __NO_BANNER		1
#define __ONE_BANNER	2
#define __ALL_BANNERS	3


void DisplayText( char *szInput, int x, int y, int index, int bErase  );


int HelperManageInput( char *szLabel, int xLabel, int yLabel,
					   char *szInput, int xInput, int yInput, 
					   int nMaxLen, int bNumerical, int nTimeout );


int HelperDisplayMenu( const char* szTitle, int nDefaultChoice,
					   int nItems, const char* Items[],
					   int nBanners );

int HelperDisplayChoices( const char* szTitle, int nDefaultChoice,
						  int nItems, const char* Items[],
					      int nBanners );


int HelperNumericInput( const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, 
					    const char* szDefault, char* szInput );




int PrintText( char *szText, int bClose );

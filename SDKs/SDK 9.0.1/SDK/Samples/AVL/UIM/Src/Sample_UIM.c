/* ========================================================================	*/
/* Include																	*/
/* ========================================================================	*/
#include <sdk30.h>
#include "VGE_UIM.h"


#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))

// Bitmap to display: !
static const char excl[]={
	(char)24,(char)0,
	(char)255,(char)0,
	(char)24,(char)0,
	(char)255,(char)0,
	(char)9,(char)5,
	(char)248,(char)248,(char)248,(char)248,(char)248,
	(char)255,(char)10,
	(char)9,(char)5,
	(char)15,(char)255,(char)255,(char)255,(char)15,
	(char)255,(char)10,
	(char)9,(char)5,
	(char)192,(char)199,(char)207,(char)199,(char)192,
	(char)255,(char)10,
	(char)9,(char)5,
	(char)7,(char)7,(char)7,(char)7,(char)7,
	(char)255,(char)10,
	(char)24,(char)0,
	(char)255,(char)0,
	(char)24,(char)0,
	(char)0,(char)0
};


/* ========================================================================	*/
/* External function definitions											*/
/* ========================================================================	*/

extern void printLine(char * txt);
extern void ServiceResultUIM(char * i_pcService, int i_nResult);


/**
 * @function:    Test_UIM_DrawTextMessage 
 * @description: Call UIM_DrawTextMessage and prints results 
 */
void Test_UIM_DrawTextMessage(void)
{
	UIM_t_message_option  i_xMessageOption;
	int iret;
	
	i_xMessageOption.pcMessage="UIM message";
	i_xMessageOption.pcMode=WRITE_MODE;
	i_xMessageOption.iTimeOut=100;
	i_xMessageOption.cDisplay=GRAPHIC_MODE;
	i_xMessageOption.UIM_u_info_draw.sGraphicMode.iPosX=0;
	i_xMessageOption.UIM_u_info_draw.sGraphicMode.iPosY=0;
	i_xMessageOption.UIM_u_info_draw.sGraphicMode.iReversal=_OFF_;
	i_xMessageOption.UIM_u_info_draw.sGraphicMode.iPolice=_PROPORTIONNEL_;
	i_xMessageOption.UIM_u_info_draw.sGraphicMode.iSize=_MEDIUM_;

	iret=UIM_DrawTextMessage(&i_xMessageOption);

	ttestall(0,500);
}

/**
 * @function:		UIM_DrawExtendedStringWithFont
 * @description:	Call UIM_DrawExtendedStringWithFont and prints results 
 */
void Test_DrawExtendedStringWithFont(void)
{
	int iret;

	_clrscr();

	// Font file ISO5.SGN must be loaded in the terminal to display a russian message
	iret=UIM_SetFontMode(UIM_ISO8859_MODE, "/SYSTEM/ISO5.SGN");
	if(iret==UIM_SUCCESS)
	{
		UIM_DrawExtendedStringWithFont("\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC",0,0,_OFF_,_MEDIUM_,_FIXED_WIDTH_);
		ttestall(0,500);
	}
	if(iret==UIM_FONT_FILE_NOT_FOUND)
	{
		printf("\x1B""File not found \n/SYSTEM/ISO5.SGN");
		ttestall(0,300);
	}
}

/**
 * @function:		Test_UIM_DrawWindowWithFont
 * @description:	Call Test_UIM_DrawWindowWithFont and prints results 
 */
void Test_UIM_DrawWindowWithFont(void)
{
	int iret;
	_clrscr();

	// Font file ISO5.SGN must be loaded in the terminal to display a russian message
	iret=UIM_SetFontMode(UIM_ISO8859_MODE, "/SYSTEM/ISO5.SGN");
	if(iret==UIM_SUCCESS)
	{
		UIM_DrawWindowWithFont(0,0,127,63,1,(unsigned char*)"\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC");
		ttestall(0,500);
	}
	if(iret==UIM_FONT_FILE_NOT_FOUND)
	{
		printf("\x1B""File not found \n/SYSTEM/ISO5.SGN");
		ttestall(0,300);
	}
}

/**
 * @function:		Test_UIM_DrawScreen
 * @description:	Call UIM_DrawScreen and prints results 
 */
void Test_UIM_DrawScreen(void)
{
	UIM_t_screen  i_xScreen;
	int l_nRet;
	
	strcpy(i_xScreen.acHeader,"Header");
	strcpy(i_xScreen.acLine1,"Line 1");
	strcpy(i_xScreen.acLine2,"Line 2");
	strcpy(i_xScreen.acLine3,"Line 3");
	strcpy(i_xScreen.acLine4,"Line 4");
	i_xScreen.cDisplayFooter=TRUE;
	if(i_xScreen.cDisplayFooter == TRUE)
	{
		strcpy(i_xScreen.acFooterRight,"Right");
		strcpy(i_xScreen.acFooterLeft,"Left");
	}
	else
		strcpy(i_xScreen.acLine5,"Line 5");
	
	memcpy(i_xScreen.acBmp,excl,sizeof(excl));

	l_nRet=UIM_DrawScreen(&i_xScreen);
	
	ttestall(0,500);
	printLine("\n\n************************");
	printLine("UIM Draw Screen");
	ServiceResultUIM("UIM_DrawScreen",l_nRet );
}

/**
 * @function:		Test_UIM_GetAlphaNumEntry
 * @description:	Call UIM_GetAlphaNumEntry and prints results 
 */
void Test_UIM_GetAlphaNumEntry(void)
{
	UIM_t_alpha_num_option i_xAlphaNumOption;
	TAB_ENTRY_STRING	t_cv2 = {0x0000, TO_PARAM, 30, 34,  ECHO_NORMAL, 4, 3};	
	char l_o_acResult[20];
	int iret;

	memcpy(&(i_xAlphaNumOption.sAlphaNumEntryOption) , &t_cv2 , sizeof(TAB_ENTRY_STRING)) ;
	i_xAlphaNumOption.pcTitle = "Alpha Numeric Entry";
	i_xAlphaNumOption.pcName = "Enter an alpha num";
	i_xAlphaNumOption.iNbTry = 3;
	i_xAlphaNumOption.pcErrMsg = "Re-enter the\nalpha num";
	i_xAlphaNumOption.iTimeOutDispErrMsg = 300;
	i_xAlphaNumOption.cSecurityLevel = SECURITY_LOW_LEVEL;
	
	memclr(l_o_acResult,20);

	iret = UIM_GetAlphaNumEntry( &i_xAlphaNumOption,l_o_acResult);
	
	printLine("\n\n************************");
	printLine("UIM Get Alpha NumEntry");
	printLine(l_o_acResult);
	ServiceResultUIM("UIM_GetAlphaNumEntry",iret );
}

/**
 * @function:		Test_UIM_GetDate
 * @description:	Call UIM_GetDate and prints results 
 */
void Test_UIM_GetDate(void)
{
	char l_ac_Date[20];
	int l_nRet;

	strcpy(l_ac_Date,"");
	
	l_nRet = UIM_GetDate("Input Date",UIMDayMonthYear,l_ac_Date);
	
	printLine("\n\n************************");
	printLine("UIM Get Date");
	printLine(l_ac_Date);
	ServiceResultUIM("UIM_GetDate",l_nRet );
}

/**
 * @function:		Test_UIM_GetIpAddress
 * @description:	Call UIM_GetIpAddress and prints results 
 */
void Test_UIM_GetIpAddress(void)
{
	char l_ac_IpAddress[20];
	char l_ac_Title[20];
	char l_ac_Separetor[2];
	int l_nRet;
	
	strcpy(l_ac_Title,"Title of ip window");
	strcpy(l_ac_Separetor,".");
	memclr(l_ac_IpAddress,sizeof(l_ac_IpAddress));
	
	l_nRet = UIM_GetIpAddress(l_ac_Title,l_ac_IpAddress,l_ac_Separetor);
	
	printLine("\n\n************************");
	printLine("UIM Get Ip Address");
	printLine(l_ac_IpAddress);
	ServiceResultUIM("UIM_GetIpAddress",l_nRet );
}

/**
 * @function:		Test_UIM_GetManualEntry
 * @description:	Call UIM_GetManualEntry and prints results 
 */
void Test_UIM_GetManualEntry(void)
{
	UIM_t_pan_option i_p_PanOption;
	char io_ac_PAN[22];
	UIM_t_exp_date_option i_x_ExpDateOption;
	char io_ac_ExpDate[10];
	char i_b_UseCVV2;
	UIM_t_cvv2_option i_x_CVV2Option;
	char io_ac_CVV2[8];
	TAB_ENTRY_STRING	t_num_porteur = {0x0000, TO_PARAM, 30, 4,  ECHO_NORMAL, 19, 8};
	TAB_ENTRY_STRING	t_date = {0x0000, TO_PARAM, 30, 4,  ECHO_NORMAL, 4, 4};
	TAB_ENTRY_STRING	t_cv2 = {0x0000, TO_PARAM, 30, 34,  ECHO_NORMAL, 4, 3};
	int l_nRet;

	memcpy(&(i_p_PanOption.sPanEntryOption) , &t_num_porteur , sizeof(TAB_ENTRY_STRING)) ;
	i_p_PanOption.pcTitle = "Manual Entry";
	i_p_PanOption.pcName = "Enter PAN";
	i_p_PanOption.pcErrMsg = "Re-enter PAN" ;
	i_p_PanOption.iNbTry = 3;
	i_p_PanOption.iTimeOutDispErrMsg = 300;
	i_p_PanOption.bCheckLuHnCode = FALSE;

	memclr(io_ac_PAN,22);

	memcpy(&(i_x_ExpDateOption.sExpDateEntryOption) , &t_date , sizeof(TAB_ENTRY_STRING)) ;
	i_x_ExpDateOption.pcTitle = "Manual Entry";
	i_x_ExpDateOption.pcName = "Enter Expiration Date";
	i_x_ExpDateOption.pcErrMsg = "Re-enter Exp Date";
	i_x_ExpDateOption.iNbTry = 3;
	i_x_ExpDateOption.iTimeOutDispErrMsg = 300;
	memclr(io_ac_ExpDate,10);
	
	i_b_UseCVV2 = FALSE;

	printLine("\n\n************************");
	printLine("UIM Get Manual Entry");

	if(i_b_UseCVV2)
	{
		memcpy(&(i_x_CVV2Option.sCVV2EntryOption) , &t_cv2 , sizeof(TAB_ENTRY_STRING)) ;
		i_x_CVV2Option.pcTitle = "Manual Entry";
		i_x_CVV2Option.pcName = "Enter CVV2 Code";
		i_x_CVV2Option.pcErrMsg = "Re-enter CVV2" ;
		i_x_CVV2Option.iNbTry = 3;
		i_x_CVV2Option.iTimeOutDispErrMsg = 300;
		memclr(io_ac_CVV2,8);

		l_nRet = UIM_GetManualEntry(&i_p_PanOption,io_ac_PAN,
									&i_x_ExpDateOption,io_ac_ExpDate,
									i_b_UseCVV2,&i_x_CVV2Option,io_ac_CVV2);
		printLine("PAN");
		printLine(io_ac_PAN);
		printLine("Exp Date");
		printLine(io_ac_ExpDate);
		printLine("CVV2");
		printLine(io_ac_CVV2);
	}
	else
	{
		l_nRet = UIM_GetManualEntry(&i_p_PanOption,io_ac_PAN,
									&i_x_ExpDateOption,io_ac_ExpDate,
									i_b_UseCVV2,NULL,NULL);
		printLine("PAN");
		printLine(io_ac_PAN);
		printLine("Exp Date");
		printLine(io_ac_ExpDate);
	}

	ServiceResultUIM("UIM_GetManualEntry",l_nRet );
}

/**
 * @function:		Test_UIM_GetNumericEntry
 * @description:	Call UIM_GetNumericEntry and prints results 
 */
void Test_UIM_GetNumericEntry(void)
{
	UIM_t_numeric_option i_xNumericOption;
	TAB_ENTRY_STRING	t_num_porteur = {0x0000, TO_PARAM, 30, 4,  ECHO_NORMAL, 19, 8};
	char l_o_acResult[20];
	char l_ac_ErrorMsg[40];
	int l_nRet;

	memcpy(&(i_xNumericOption.sNumericEntryOption) , &t_num_porteur , sizeof(TAB_ENTRY_STRING)) ;
	i_xNumericOption.pcTitle = "Numeric Entry";
	i_xNumericOption.pcName = "Enter a Numeric";
	i_xNumericOption.iNbTry = 3;
	i_xNumericOption.iTimeOutDispErrMsg = 300;
	strcpy(l_ac_ErrorMsg,"ERROR : ENTER\nMIN 8 NUMERIC");
	i_xNumericOption.pcErrMsg = l_ac_ErrorMsg ;
	i_xNumericOption.cSecurityLevel = SECURITY_MEDIUM_LEVEL;		
	
	memclr(l_o_acResult,20);

	l_nRet = UIM_GetNumericEntry( &i_xNumericOption,l_o_acResult);
	
	printLine("\n\n************************");
	printLine("UIM Get Numeric Entry");
	printLine(l_o_acResult);
	ServiceResultUIM("UIM_GetNumericEntry",l_nRet );
}

/**
 * @function:		Test_UIM_GetTime
 * @description:	Call UIM_GetTime and prints results 
 */
void Test_UIM_GetTime(void)
{
	int l_nRet;
	char l_ac_Time[20];
	
	strcpy(l_ac_Time,"");
	
	l_nRet = UIM_GetTime("Input Time",UIMHourMinute,l_ac_Time);
	
	printLine("\n\n************************");
	printLine("UIM Get Time");
	printLine(l_ac_Time);
	ServiceResultUIM("UIM_GetTime",l_nRet );
}

/**
 * @function:		Test_UIM_InputValue
 * @description:	Call UIM_InputValue and prints results 
 */
void Test_UIM_InputValue(void)
{
	UIM_t_input i_xInput;
	char l_o_acResult[20];
	int l_nRet;

	i_xInput.iTimeOut = TO_PARAM;
	i_xInput.iLine = 30;
	i_xInput.iColomne = 4;
	i_xInput.cEcho = ECHO_NORMAL;
	i_xInput.iMaxInput = 19;
	i_xInput.iMinInput = 8;
	i_xInput.cInputType = ALPHA_NUMERICAL;

	memclr(l_o_acResult,20);

	_clrscr(); // Rajouté car pas traité dans la lib!
	
	l_nRet = UIM_InputValue(&i_xInput,l_o_acResult);
	
	printLine("\n\n************************");
	printLine("UIM Input Value");
	printLine(l_o_acResult);
	ServiceResultUIM("UIM_InputValue",l_nRet );
}

/**
 * @function:		Test_UIM
 * @description:	Call UIM_NavigateService and prints results 
 */
void Test_UIM(void)
{
	int l_nRet;

	UIM_t_navigate_menu l_x_NavigateMenu[] =
	{
		{"UIM SAMPLE",					"0",		0,	PT_NULL},
		{"DrawTextMessage",		"1",		1,	(PFONCNAVI)Test_UIM_DrawTextMessage},
		{"DrawScreen",			"2",		1,	(PFONCNAVI)Test_UIM_DrawScreen},
		{"DrawStringWithFont",	"3",		1,	(PFONCNAVI)Test_DrawExtendedStringWithFont},
		{"DrawWindowWithFont",	"4",		1,	(PFONCNAVI)Test_UIM_DrawWindowWithFont},
		{"GetAlphaNumEntry",	"5",		1,	(PFONCNAVI)Test_UIM_GetAlphaNumEntry},
		{"GetDate",				"6",		1,	(PFONCNAVI)Test_UIM_GetDate},
		{"GetIpAddress",		"7",		1,	(PFONCNAVI)Test_UIM_GetIpAddress},
		{"GetManualEntry",		"8",		1,	(PFONCNAVI)Test_UIM_GetManualEntry},
		{"GetNumericEntry",		"9",		1,	(PFONCNAVI)Test_UIM_GetNumericEntry},
		{"GetTime",				"10",		1,	(PFONCNAVI)Test_UIM_GetTime},
		{"InputValue",			"11",		1,	(PFONCNAVI)Test_UIM_InputValue},
		
	};
	
	UIM_t_navigate_option l_x_NavigateOption = {
		30,						/*time out in second*/
		1,						/*offset*/
		0,						/*radio button*/
		UIM_DISPLAY_MESSAGE,	/*action to do after time out*/
		0,						/*default choice*/
		"Time Out",				/*message to display after time out*/
		UIM_CONTINUE_AFTER_FCT	/*Action to do after the execution of the function*/
	};

	l_nRet = UIM_NavigateService(l_x_NavigateMenu,NUMBER_OF_ITEMS(l_x_NavigateMenu),&l_x_NavigateOption);
	
	printLine("\n\n************************");
	printLine("UIM Navigate Service:");
	ServiceResultUIM("UIM_NavigateService",l_nRet );
}

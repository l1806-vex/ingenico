//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "DataElement.h"
#include "VGE_TMS.h"
#include "VGE_UIM.h"


/////////////////	External function definitions	///////////////////

extern void hex2str( char *b,char *des,int len);
extern void CUTERMprintLine(char *xs_text);
extern void CUTERMPrintLogFile(char *xs_text);


//// Macros & preprocessor definitions //////////////////////////

#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))

#define TLV				0
#define BIN				1
#define NB_FILE_TMS		3


//// Globals ////////////////////////////////////////////////////

TMS_t_file_descriptor l_x_FileDesc[NB_FILE_TMS];

char l_ac_ResultParse1[512];
char l_ac_ResultParse2[1024];
char l_ac_ResultParse3[512];

static void PrintTag(char * i_pcTag, char *i_pcValue)
{
	FILE *lp_printer;
	
	lp_printer = fopen("PRINTER", "w-");
	
	pprintf("Tag   = %s\n",i_pcTag);
	pprintf("Value = %s\n\n",i_pcValue);

	/* wait for print end */
	ttestall(PRINTER, 0);
	fclose(stdprt());
}

/**
 * @function:		PrintListOfTag
 * @description: 
 */
static void PrintListOfTag(char i_cTypeFile,char * i_pcData,int i_nSizeData)
{
	T_DATA_ELEMENT Element;
	T_ET_STATUS EtStatusData;
	T_ET_POSITION Position;
	T_ET_TAG TagData;
	T_ET_LENGTH Length;
	void* pValue;
	unsigned char is_found;
	unsigned char l_acTag[10];
	unsigned char l_acValue[50];
	
	Element.m_pBuffer = i_pcData;
	Element.m_ulBufferSize = i_nSizeData;
	Position = ET_POSITION_NULL;

	Et_GetFirstPosition (&Element, &Position);
	is_found = FALSE;
	do
	{
		EtStatusData = Et_GetNext(&Element, &Position, &TagData, &Length, (const void**)&pValue);

		if (EtStatusData == EtSuccess)
		{
			memclr(l_acTag,10);
			sprintf((char*)l_acTag,"%x",(int)TagData);
			memclr(l_acValue,50);
			switch(i_cTypeFile)
			{
				case TLV:
					if(Length>49) 
						Length = 49;
					memcpy(l_acValue,pValue,Length);
					break;
				case BIN:
					if(Length>24) 
						Length = 24;
					hex2str( pValue,(char*)l_acValue,Length);
					break;

				default:
					break;
			}
			PrintTag((char*)l_acTag,(char*)l_acValue);
		}
	} while(EtStatusData == EtSuccess);
}

/**
 * @function:		InitParamStruct
 * @description: 
 */
int InitParamStruct(void)
{
	int l_nCmp;

	l_nCmp = 0;

	strcpy(l_x_FileDesc[l_nCmp].sFileName,"TMSDATA.PAR");
	strcpy(l_x_FileDesc[l_nCmp].sFileDescriptor,"");
	l_x_FileDesc[l_nCmp].xListOfTags.iNumberOfTagsElements = 3;

	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[0],"FF01");
	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[1],"FF02");
	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[2],"FF03");
	
	l_x_FileDesc[l_nCmp].iParsingMethode = TMS_PARSE_1;
	memclr(l_ac_ResultParse1,512);
	l_x_FileDesc[l_nCmp].xDataStruct = l_ac_ResultParse1;
	l_x_FileDesc[l_nCmp].nLengthDataStruct = sizeof(l_ac_ResultParse1);

	l_nCmp++;

	strcpy(l_x_FileDesc[l_nCmp].sFileName,"EMVDATA.PAR");
	strcpy(l_x_FileDesc[l_nCmp].sFileDescriptor,"");
	l_x_FileDesc[l_nCmp].xListOfTags.iNumberOfTagsElements = 2;

	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[0],"9F06");
	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[1],"9F812B");
	
	l_x_FileDesc[l_nCmp].iParsingMethode = TMS_PARSE_4;
	memclr(l_ac_ResultParse2,1024);
	l_x_FileDesc[l_nCmp].xDataStruct = l_ac_ResultParse2;
	l_x_FileDesc[l_nCmp].nLengthDataStruct = sizeof(l_ac_ResultParse2);

	l_nCmp++;

	strcpy(l_x_FileDesc[l_nCmp].sFileName,"INIDATA.PAR");
	strcpy(l_x_FileDesc[l_nCmp].sFileDescriptor,"");
	l_x_FileDesc[l_nCmp].xListOfTags.iNumberOfTagsElements = 3;

	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[0],"FF01");
	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[1],"FF05");
	strcpy((char*)l_x_FileDesc[l_nCmp].xListOfTags.sTagsElements[2],"FF15");

	l_x_FileDesc[l_nCmp].iParsingMethode = TMS_PARSE_3;
	memclr(l_ac_ResultParse3,512);
	l_x_FileDesc[l_nCmp].xDataStruct = l_ac_ResultParse3;
	l_x_FileDesc[l_nCmp].nLengthDataStruct = sizeof(l_ac_ResultParse3);

	l_nCmp++;

	return (l_nCmp+1);
}

/**
 * @function:		InitParam_TMS
 * @description:	Call TMS_InitParametersFile and print results 
 */
void InitParam_TMS(void)
{
	int l_n_Ret;
	int l_nNbElement;
	char Text[30];
	
	CUTERMprintLine("* TMS INIT PARAMETERS *");
	
	l_nNbElement = InitParamStruct();
	
	l_n_Ret = TMS_InitParametersFile(l_x_FileDesc,l_nNbElement );

	sprintf(Text, "Return = %d",l_n_Ret);
	CUTERMprintLine(Text);

	if (l_n_Ret==TMS_SUCCESS)
		CUTERMprintLine("INIT PARAM SUCCESS");
	else
		CUTERMprintLine("INIT PARAM FAILED");

	CUTERMprintLine("\n\n\n");
}

/**
 * @function:		CreateLogFile
 * @description:	Call TMS_CreateLogFile and print results 
 */
void CreateLogFile(void)
{
	int cr;
	char Text [30];
	
	CUTERMprintLine("** TMS CREATE LOG **");
	
	cr = TMS_CreateLogFile();

	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);

	if (cr==TMS_SUCCESS)
		CUTERMprintLine("CREATE LOG OK");
	else
	{
		if(cr==TMS_ALREADY_EXIST)
			CUTERMprintLine("LOG ALREADY EXIST");
		else
			CUTERMprintLine("CREATE LOG KO !");
	}
	CUTERMprintLine("\n\n");
}

/**
 * @function:		AddLineLog
 * @description:	Call TMS_AddLineLog and print results 
 */
void AddLineLog(void)
{
	int cr;
	char l_acLogData[100];
	char Text[40];
	unsigned int l_unDataLen;

	CUTERMprintLine("** TMS ADD LOG LINE **");
	
	strcpy(l_acLogData,"First Line");
	
	l_unDataLen=strlen(l_acLogData);
	
	cr = TMS_AddLineLog(l_acLogData,l_unDataLen);

	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);

	if (cr==TMS_SUCCESS)
		CUTERMprintLine("ADD LINE SUCCESS");
	else
		CUTERMprintLine("ADD LINE FAILED");
	
	CUTERMprintLine("\n\n");
}

/**
 * @function:		PrintLogFile
 * @description:	Print Log file content
 */
void PrintLogFile(void)
{
	S_FS_FILE * l_pxLogFile;
	int l_n_Length;
	char * l_pc_Data;
	int i_unMode = FS_WRITEONCE;

	CUTERMprintLine("** PRINT LOG FILE **");
	
	FS_mount("/HOST",(unsigned int*)&i_unMode);
	l_pxLogFile = FS_open("/HOST/LogFile.log","r");
	l_n_Length = FS_length(l_pxLogFile);
	l_pc_Data = PageAlloc(l_n_Length + 5);
	if(l_pc_Data != NULL)
	{	
		memclr(l_pc_Data,l_n_Length + 5);
		FS_read ((void*)l_pc_Data,l_n_Length,1,l_pxLogFile);
		CUTERMPrintLogFile(l_pc_Data);
	}
	CUTERMprintLine("******************");
	CUTERMprintLine("\n\n");
	PageFree(l_pc_Data);
	FS_close(l_pxLogFile);
	FS_unmount("/HOST");
}

/**
 * @function:		InitLogFile
 * @description:	Call TMS_InitLogFile and print results 
 */
void InitLogFile(void)
{
	int cr;
	char Text [30];
	
	CUTERMprintLine("** TMS INIT LOG **");
	
	cr = TMS_InitLogFile();
	
	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);

	if (cr==TMS_SUCCESS)
		CUTERMprintLine("INIT LOG SUCCESS");
	else
		CUTERMprintLine("INIT LOG FAILED");
	
	CUTERMprintLine("\n\n");
}

/**
 * @function:		ParseFileTMS
 * @description:	Call TMS_StartParsingParamFile and print results.
 * @description:	ParseFileTMS is called in FILE_RECEIVED entry point.
 */
void ParseFileTMS(S_FILE *pFile)
{
	char Text[40];
	int l_n_Ret;

	CUTERMprintLine("*****************");
	sprintf(Text , "File Received : \n /%s/%s",pFile->volume_name,pFile->file_name );
	CUTERMprintLine(Text);

	l_n_Ret = TMS_StartParsingParamFile(pFile);

	CUTERMprintLine("Parsing File...");
	CUTERMprintLine("\n\n");

	if(l_n_Ret == TMS_SUCCESS)
	{
		if(strcmp(pFile->file_name,l_x_FileDesc[0].sFileName) == 0)
		{
			PrintListOfTag(TLV,l_ac_ResultParse1,sizeof(l_ac_ResultParse1));
		}
		else
		if(strcmp(pFile->file_name,l_x_FileDesc[1].sFileName) == 0)
		{
			PrintListOfTag(BIN,l_ac_ResultParse2,sizeof(l_ac_ResultParse2));
		}
		else
		if(strcmp(pFile->file_name,l_x_FileDesc[2].sFileName) == 0)
		{
			PrintListOfTag(TLV,l_ac_ResultParse3,sizeof(l_ac_ResultParse3));
		}
	}

	sprintf(Text, "Return = %d",l_n_Ret);
	CUTERMprintLine(Text);
	
	if (l_n_Ret==TMS_SUCCESS)
		CUTERMprintLine("PARSE FILE OK");
	else
		CUTERMprintLine("PARSE FILE KO !");
	
	CUTERMprintLine("\n");
	CUTERMprintLine("\n");
}

/**
 * @function:    Test_TMS
 * @description: Manage menu that contains TMS functions
 */
int Test_TMS(void)
{
	UIM_t_navigate_menu l_x_NavigateMenu[] =
	{
		{"TMS SAMPLE",		"0",		0,	PT_NULL},
		{"Create Log File",	"1",		1,	(PFONCNAVI)CreateLogFile},
		{"Add Log Line",	"2",		1,	(PFONCNAVI)AddLineLog},
		{"Print Log File",	"3",		1,	(PFONCNAVI)PrintLogFile},
		{"Init Log File",	"4",		1,	(PFONCNAVI)InitLogFile},
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

	UIM_NavigateService(l_x_NavigateMenu,NUMBER_OF_ITEMS(l_x_NavigateMenu),&l_x_NavigateOption);

	return FCT_OK;
}




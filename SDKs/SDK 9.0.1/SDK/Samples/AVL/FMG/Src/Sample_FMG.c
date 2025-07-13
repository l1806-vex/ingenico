/* ========================================================================	*/
/* Include																	*/
/* ========================================================================	*/
#include "SDK30.H"
#include "Sample_FMG.h"
#include "VGE_FMG.h"
#include "VGE_UIM.h"


/* ========================================================================	*/
/* External function definitions											*/
/* ========================================================================	*/

extern void CUTERMprintLine(char *xs_text);

#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


FMG_t_file_description Sample_FileDescription;


/**
 * @function     : CUTERMprintLine                                                       
 * @description   : This service prints the text and wait for the end of the job
 * ======================================================================= 
 * @param        : *xs_text : Text to be printed.                                                                             
 * ======================================================================= 
 */
void CUTERMprintLine(char *xs_text)
{
	FILE *lp_printer;
	
	lp_printer = fopen("PRINTER", "w-");
	
	fprintf(lp_printer,"%s\n", xs_text);
	
	/* wait for print end */
	ttestall(PRINTER, 0);
	
	fclose(stdprt());
}

/**
 * @function:		AddRecord
 * @description:	Call FMG_AddRecord and prints results
 */
void AddRecord(void)
{
	FMG_t_file_info sFileInfo;
	int cr;
	char pcBuffer[100],Text[30];
	int iLength=0;

	CUTERMprintLine("*** FMG ADD RECORD ***\n");
	
	memset(&sFileInfo,0,sizeof(FMG_t_file_info));
	
	sFileInfo.eCreationType=FMGPathAndName;
	strcpy((char*)sFileInfo.ucFilePath,(char*)Sample_FileDescription.pcPathName);
	strcpy((char*)sFileInfo.ucFileName,(char*)Sample_FileDescription.PcFileName);
		
	strcpy(pcBuffer,"This record was added");
	iLength=strlen(pcBuffer);
	sprintf(Text,"Value=%s",pcBuffer);
	CUTERMprintLine(Text);
	 
	cr= FMG_AddRecord(&sFileInfo, pcBuffer, iLength, FMGBegin, 0);
	
	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);
	
	if (cr == FMG_SUCCESS)
		CUTERMprintLine("ADD REC SUCCESS");
	else
		CUTERMprintLine("ADD REC FAILED");
	
	CUTERMprintLine("\n\n");
}

/**
 * @function:		ModifyRecord
 * @description:	Call FMG_ModifyRecord and prints results
 */
void ModifyRecord(void)
{
    FMG_t_file_info sFileInfo;
	int cr;
	char pcBuffer[100],Text[50];
	int iLength=0;

	CUTERMprintLine("** FMG MODIFY RECORD **\n");
	
	memset(&sFileInfo,0,sizeof(FMG_t_file_info));
	
	sFileInfo.eCreationType=FMGPathAndName;
	strcpy((char*)sFileInfo.ucFilePath,(char*)Sample_FileDescription.pcPathName);
	strcpy((char*)sFileInfo.ucFileName,(char*)Sample_FileDescription.PcFileName);

	strcpy(pcBuffer,"This record was modify");
	iLength=strlen(pcBuffer);
	sprintf(Text,"Value=%s",pcBuffer);
	CUTERMprintLine(Text);
	
	cr= FMG_ModifyRecord(&sFileInfo	, pcBuffer, iLength, FMGBegin, 0);
	
	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);
	
	if (cr == FMG_SUCCESS)
		CUTERMprintLine("MODIF REC SUCCESS");
	else
		CUTERMprintLine("MODIF REC FAILED");
	
	CUTERMprintLine("\n\n");
}

/**
 * @function:		ReadRecord
 * @description:	Call FMG_ReadRecord and prints results
 */
void ReadRecord(void)
{
	FMG_t_file_info sFileInfo;
	int cr;
	char Text[100], pcRead[50];
	long lLenSaisie=0;

	CUTERMprintLine("*** FMG READ RECORD ***");
	
	memset(&sFileInfo,0,sizeof(FMG_t_file_info));
	memset(pcRead,0,50);
	
	sFileInfo.eCreationType=FMGPathAndName;
	strcpy((char*)sFileInfo.ucFilePath,(char*)Sample_FileDescription.pcPathName);
	strcpy((char*)sFileInfo.ucFileName,(char*)Sample_FileDescription.PcFileName);
	
	cr= FMG_ReadRecord(&sFileInfo, pcRead, (long*)&lLenSaisie, FMGBegin, 0);
	
	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);
	
	if (cr == FMG_SUCCESS)
	{
		CUTERMprintLine("READ REC SUCCESS");
		sprintf(Text, "Record value :\n%s\n",pcRead);
		CUTERMprintLine(Text);
	}
	else
	{	
		CUTERMprintLine("READ REC FAILED");
	}
	CUTERMprintLine("\n\n");
}

/**
 * @function:		DeleteRecord
 * @description:	Call FMG_DeleteRecord and prints results
 */
void DeleteRecord(void)
{
	FMG_t_file_info sFileInfo;
	int cr;
	char Text[50];
	
	CUTERMprintLine("** FMG DELETE RECORD **\n");
	
	memset(&sFileInfo,0,sizeof(FMG_t_file_info));
	
	sFileInfo.eCreationType=FMGPathAndName;
	strcpy((char*)sFileInfo.ucFilePath,(char*)Sample_FileDescription.pcPathName);
	strcpy((char*)sFileInfo.ucFileName,(char*)Sample_FileDescription.PcFileName);
	
	cr= FMG_DeleteRecord (&sFileInfo, FMGBegin, 0, 0);
	
	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);
	
	if (cr == FMG_SUCCESS)
		CUTERMprintLine("DEL REC SUCCESS");
	else
		CUTERMprintLine("DEL REC FAILED");
	CUTERMprintLine("\n\n");
}

/**
 * @function:		CalculMD5
 * @description:	Call FMG_CalculMD5 and prints results
 */
void CalculMD5(void)
{
	char Text[100];
	int iLength;
	char pcBuffer[100];
	unsigned char CalculatedMd5[16];
	char buf[3];
	int i;

    CUTERMprintLine("*** FMG CALCUL MD5 ***\n");
	
	strcpy(pcBuffer,"This record was added");
	iLength=strlen(pcBuffer);
	sprintf(Text,"Value=%s\n",pcBuffer);
	CUTERMprintLine(Text);

	FMG_CalculMD5(pcBuffer,iLength ,(char*)CalculatedMd5);

	// Print Md5 result
	sprintf(Text, "Calculated MD5 =\n");
	for(i=0;i<16;i++)
	{
		sprintf(buf,"%X ",CalculatedMd5[i]);
		strcat(Text,buf);
	}
	CUTERMprintLine(Text);
	CUTERMprintLine("\n\n");
}

/**
 * @function:		DeleteRecord
 * @description:	Call FMG_CheckRecordCoherence and prints results
 */
void CheckRecord(void)
{
	int cr;
	char Text[50];
	int iLength;
	char pcBuffer[100];
	
    CUTERMprintLine("* FMG CHECK COHERENCE *");
	
	strcpy(pcBuffer,"This record was added");
	iLength=strlen(pcBuffer);
	sprintf(Text,"Value=%s",pcBuffer);
	CUTERMprintLine(Text);

	cr = FMG_CheckRecordCoherence( pcBuffer ,iLength,"\xF5\xF2\x2E\x51\xB7\x42\x7F\x18\x6C\x3F\xD1\x96\x76\x6F\xA5\x84");

	sprintf(Text,"Return = %d",cr);
	CUTERMprintLine(Text);

	if (cr == FMG_SUCCESS)
		CUTERMprintLine("SAFE RECORD");
	else
	    CUTERMprintLine("CORRUPTED RECORD");
	CUTERMprintLine("\n\n");
}

/**
 * @function:		CheckFile
 * @description:	Call FMG_CheckFileCoherence and prints results
 */
void CheckFile(void)
{
	int cr;
	char Text[50];
	
    CUTERMprintLine("* FMG CHECK COHERENCE *");
	
	cr = FMG_CheckFileCoherence( Sample_FileDescription.pcPathName ,Sample_FileDescription.PcFileName);

	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);

	if (cr == FMG_SUCCESS)
		CUTERMprintLine("SAFE FILE");
	else
	    CUTERMprintLine("CORRUPTED FILE");
	CUTERMprintLine("\n\n");
}

/**
 * @function:		CreateFile
 * @description:	Call FMG_CreateFile or FMG_CreateFileType and prints results
 */
void CreateFile(void)
{
	char Text[30];
	int FileType;
	FMG_e_file_type eFileType=0;
	int cr=0;

	CUTERMprintLine("** FMG CREATE FILE **\n");

	FileType = 0;

	if (FileType==0)
	{
		cr = FMG_CreateFile(Sample_FileDescription.pcPathName, Sample_FileDescription.PcFileName, Sample_FileDescription.eRecordType, Sample_FileDescription.eChecksum);
	
		sprintf(Text, "Path= %s",Sample_FileDescription.pcPathName);
		CUTERMprintLine(Text);
		sprintf(Text, "Name= %s",Sample_FileDescription.PcFileName);
		CUTERMprintLine(Text);
	}
	else
	{
		eFileType = FMGBlackList;
	 	
		cr = FMG_CreateFileType(eFileType, Sample_FileDescription.eRecordType, Sample_FileDescription.eChecksum);
	}
	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);
	
	if (cr == FMG_SUCCESS)
		CUTERMprintLine("Creation SUCCESS");
	else
		CUTERMprintLine("Creation FAILED");
	
	CUTERMprintLine("\n\n");
}

/**
 * @function:		DeleteFile
 * @description:	Call FMG_DeleteFile and prints results 
 */
void DeleteFile(void)
{
	int cr;
	char Text[30];
	int FileType;
	
	CUTERMprintLine("** FMG DELETE FILE **\n");

	FileType = 0;
	if (FileType==0)
		cr = FMG_DeleteFile (Sample_FileDescription.pcPathName, Sample_FileDescription.PcFileName);
	else
		cr = FMG_DeleteFileType(FMGBlackList);	

	sprintf(Text, "Return = %d",cr);
	CUTERMprintLine(Text);
	
	if (cr == FMG_SUCCESS)
		CUTERMprintLine("DELETE SUCCESS");
	else
		CUTERMprintLine("DELETE FAILED");
	
	CUTERMprintLine("\n\n");
}

/**
 * @function:		FileDescription
 * @description:	Call FMG_GetFileDescription and prints results 
 */
void FileDescription(void)
{
	FMG_t_file_management sFileDescription;
	int iNbFile,i;
	long lLenFile;
	char Text[50];
	char FilePath_L[MAX_FMG_FILE_PATH+MAX_FMG_FILE_NAME+3];
	S_FS_FILE *file;

	memset(&sFileDescription,0,sizeof(FMG_t_file_management));
	
	FMG_GetFileDescription(&sFileDescription);

	iNbFile=sFileDescription.uiNbFile;

	sprintf(Text,"Nb File= %d",iNbFile);
	CUTERMprintLine(Text);
	
	for(i=0;i<iNbFile;i++)
	{
		CUTERMprintLine("\n");
		sprintf(FilePath_L,"/%s/%s",sFileDescription.sFileDescription[i].pcPathName,sFileDescription.sFileDescription[i].PcFileName);
		CUTERMprintLine(FilePath_L);
		
		if(sFileDescription.sFileDescription[i].eChecksum==FMG_WITH_CKECKSUM)
			sprintf(Text,"With checksum");
		else
			sprintf(Text,"No Checksum");
		CUTERMprintLine(Text);

		if(sFileDescription.sFileDescription[i].eRecordType==FMG_VARIABLE_LENGTH)
			sprintf(Text,"Variable length");
		else
			sprintf(Text,"Fix length");
		CUTERMprintLine(Text);

		// Open the file
		file= FS_open (FilePath_L, "r");

		if (file == NULL)
		{
			CUTERMprintLine("Error");
		}
		else
		{
			lLenFile =FS_length(file);
			sprintf(Text,"File size= %d",(int)lLenFile);	
			CUTERMprintLine(Text);
			FS_close(file);
		}
	}

	CUTERMprintLine("\n\n\n");
}

/**
 * @function:    FMG_Test
 * @description: Manage menu that contains FMG functions
 */
int FMG_Test(void)
{	
	UIM_t_navigate_menu l_x_NavigateMenu[] =
	{
		{"FMG SAMPLE",			"0",		0,	PT_NULL},
		{"Create File",			"1",		1,	(PFONCNAVI)CreateFile},
		{"File Management",		"2",		1,	PT_NULL},
		{"Add Record",			"21",		2,	(PFONCNAVI)AddRecord},
		{"Modify Record",		"22",		2,	(PFONCNAVI)ModifyRecord},
		{"Read Record",			"23",		2,	(PFONCNAVI)ReadRecord},
		{"Delete Record",		"24",		2,	(PFONCNAVI)DeleteRecord},
		{"Calculate MD5",		"25",		2,	(PFONCNAVI)CalculMD5},
		{"Record coherency",	"26",		2,	(PFONCNAVI)CheckRecord},
		{"File coherency",		"27",		2,	(PFONCNAVI)CheckFile},
		{"Delete File",			"3",		1,	(PFONCNAVI)DeleteFile},
		{"File Description",	"4",		1,	(PFONCNAVI)FileDescription},
		
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

	// Initialise FMG_t_file_description structure that contains informations about the file
	strcpy(Sample_FileDescription.pcPathName,(char*)DISK_NAME);
	strcpy(Sample_FileDescription.PcFileName,(char*)FILE_NAME);
	Sample_FileDescription.eRecordType=FMG_VARIABLE_LENGTH;
	Sample_FileDescription.eChecksum=FMG_WITH_CKECKSUM;


	UIM_NavigateService(l_x_NavigateMenu,NUMBER_OF_ITEMS(l_x_NavigateMenu),&l_x_NavigateOption);

	return FCT_OK;
}
	
	

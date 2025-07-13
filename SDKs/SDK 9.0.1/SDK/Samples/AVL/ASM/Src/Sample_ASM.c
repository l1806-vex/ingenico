///////////////////	 	Includes				///////////////
#include "SDK30.H"
#include "VGE_ASM.h"
#include "VGE_UIM.h"


//////////////	 Macros & preprocessor definitions		///////////////

#define TASK_DEFAULT_PRIORITY		32

// TASK ID DEFINITIONS
#define TASK_ID_10		10		//	This task lasts 10 seconds and returns ASM_SUCCESS at the end.
#define TASK_NAME_10    "TASK_ID_10"

extern object_info_t ObjectInfo;


/////////////////	External function definitions	///////////////////

extern void ASM_PrintResult(char * i_acCommand, int i_iRet, char * i_acOptional1, char * i_acOptional2);
extern void L_PrintTaskInfoInString(ASM_t_task * i_pxTask, char * i_acPrintOutput);
extern void CUTERMprintLine(char *xs_text);


///////////////			 Local Functions			/////////////////////

static void ConvertDateToString(DATE * i_pxDate, char * l_opcDate)
{
	memcpy(l_opcDate+strlen(l_opcDate), &i_pxDate->day, 2);
	memcpy(l_opcDate+strlen(l_opcDate), "/", 1);
	memcpy(l_opcDate+strlen(l_opcDate), &i_pxDate->month, 2);
	memcpy(l_opcDate+strlen(l_opcDate), "/", 1);
	memcpy(l_opcDate+strlen(l_opcDate), &i_pxDate->year, 2);
}

static void ConvertTimeToString(DATE * i_pxDate, char * l_opcTime)
{
	memcpy(l_opcTime+strlen(l_opcTime), &i_pxDate->hour, 2);
	memcpy(l_opcTime+strlen(l_opcTime), ":", 1);
	memcpy(l_opcTime+strlen(l_opcTime), &i_pxDate->minute, 2);
	memcpy(l_opcTime+strlen(l_opcTime), ":", 1);
	memcpy(l_opcTime+strlen(l_opcTime), &i_pxDate->second, 2);
}

static void GetTimeAndDate(DATE * i_pxDate, char * l_opcTime, char * l_opcDate)
{
	int iRet;
	
	// The user enter the application date
	do
	{
		memclr(l_opcDate,9);
		iRet = UIM_GetDate("APPLICATION DATE",UIMDayYear,l_opcDate);
	}while(iRet!=UIM_SUCCESS);
	
	// The user enter the application time
	do
	{
		memclr(l_opcTime,9);
		iRet=UIM_GetTime("APPLICATION TIME", UIMHourMinuteSecond, l_opcTime);
	}while (iRet!=UIM_SUCCESS);


	memcpy(i_pxDate->day,&l_opcDate[0],2);
	memcpy(i_pxDate->month,&l_opcDate[3],2);
	memcpy(i_pxDate->year,&l_opcDate[6],2);
	
	memcpy(i_pxDate->hour,&l_opcTime[0],2);
	memcpy(i_pxDate->minute,&l_opcTime[3],2);
	memcpy(i_pxDate->second,&l_opcTime[6],2);
}

/**
 * @function:    DurationTask 
 * @description: Display a window during i_iDuration seconds
 *-----------------------------------------------------------------------------
 * @param:       i_iDuration : duration of the task (in second)
 * @param:       i_iTaskId : Task Id
 * @param:       i_pcTaskId : Task name
 * @return:      ASM_SUCCESS
 *-----------------------------------------------------------------------------
 */
int DurationTask(int i_iDuration, int i_iTaskId, char * i_pcTaskId)
{
	UIM_t_screen	l_xTaskInProgressScreen;

	memclr(&l_xTaskInProgressScreen, sizeof(l_xTaskInProgressScreen));
	
	sprintf(l_xTaskInProgressScreen.acHeader, "TASK STATUS");
	sprintf(l_xTaskInProgressScreen.acLine1, i_pcTaskId);
	sprintf(l_xTaskInProgressScreen.acLine2,"TASK ID = %d", i_iTaskId);
	sprintf(l_xTaskInProgressScreen.acLine4, "IN PROGRESS...");

	UIM_DrawScreen(&l_xTaskInProgressScreen);
	
	// wait i_iDuration seconds
	ttestall(0, i_iDuration * 100);

	_clrscr();
	PaintGraphics();

	return(ASM_SUCCESS);
}

/**
 * @function:    execute_task 
 * @description: This service enable to execute automatic tasks called by the calendar component. 
 *-----------------------------------------------------------------------------
 * @param:       i_usTaskId : Task Id
 * @return:      ASM_SUCCESS or ASM_CALL_FAILURE
 *-----------------------------------------------------------------------------
 */
int execute_task(unsigned short i_usTaskId)
{
	int nResult = ASM_CALL_FAILURE;
	char acText[100];

	switch(i_usTaskId)
	{
		case  TASK_ID_10	:
			buzzer(50);
			nResult = DurationTask(10, TASK_ID_10, TASK_NAME_10);
			buzzer(50);
			break;

		default:
			sprintf(acText,"\nTask (Id = %d) Unknown !\n", i_usTaskId);
			CUTERMprintLine(acText);
			nResult = ASM_CALL_FAILURE;
			break;
	}

	return nResult;
}

/**
 * @function:    L_CalculateDeltaDate 
 * @description: Call ASM_CalculateDeltaDate and print results 
 */
void L_CalculateDeltaDate (void)
{
	int l_n_Ret,l_iDeltaDate,l_iDeltaTime;
	DATE xApplicationDate;
	char acDate[9];
	char acTime[9];
	char l_acSystemDate[40];
	char l_acSystemTime[40];
	char l_acOptional1[100];
	char l_acOptional2[100];
	DATE l_xDate;
	
	memset(&xApplicationDate,0,sizeof(DATE));
	memclr(l_acOptional1, sizeof(l_acOptional1));
	memclr(l_acSystemDate, sizeof(l_acSystemDate));
	memclr(l_acSystemTime, sizeof(l_acSystemTime));
	
	// The user enter the application date and time		
	GetTimeAndDate(&xApplicationDate,acTime,acDate);
				
	// Get the system date and time
	memclr(&l_xDate, sizeof(l_xDate));
	read_date(&l_xDate);
	ConvertDateToString(&l_xDate, l_acSystemDate);
	ConvertTimeToString(&l_xDate, l_acSystemTime);
	
	sprintf(l_acOptional1, "Appli Date  = %s\nSystem Date = %s\nAppli Time  = %s\nSystem Time = %s", acDate, l_acSystemDate, acTime, l_acSystemTime);
				
	l_n_Ret = ASM_CalculateDeltaDate(&xApplicationDate,&l_iDeltaDate,&l_iDeltaTime);
						
	memclr(l_acOptional2, sizeof(l_acOptional2));
				
	if (l_n_Ret == ASM_SUCCESS)
		sprintf(l_acOptional2, "Delta date = %d\nDelta time = %d", l_iDeltaDate, l_iDeltaTime);

	// Print ticket
	ASM_PrintResult("ASM_CalculateDeltaDate", l_n_Ret, l_acOptional1, l_acOptional2);
}

/**
 * @function:    L_CreateCalandar 
 * @description: Call ASM_CreateCalendar and print results 
 */
void L_CreateCalandar( void )
{
	int l_n_Ret,l_iDeltaDate,l_iDeltaTime;
	char l_acOptional[100];
	unsigned short	l_usApplicationType;
	
	l_usApplicationType = ObjectInfo.application_type;
	l_iDeltaDate = 0;
	l_iDeltaTime = 0;

	l_n_Ret = ASM_CreateCalendar(l_usApplicationType,l_iDeltaDate,l_iDeltaTime);

	sprintf(l_acOptional, "Application type = %04X\nDelta Date = %d\nDelta Time = %d\n", l_usApplicationType, l_iDeltaDate, l_iDeltaTime);
	ASM_PrintResult("ASM_CreateCalendar", l_n_Ret, l_acOptional, "");
}

/**
 * @function:    L_DeleteCalandar 
 * @description: Call ASM_DeleteCalendar and print results 
 */
void L_DeleteCalandar( void )
{
	int l_n_Ret;
	char l_acOptional[100];
	unsigned short	l_usApplicationType;

	l_usApplicationType = ObjectInfo.application_type;
	
	l_n_Ret = ASM_DeleteCalendar(l_usApplicationType);

	sprintf(l_acOptional, "Application type = %04X\n", l_usApplicationType);
	ASM_PrintResult("ASM_DeleteCalendar", l_n_Ret, l_acOptional, "");
}

/**
 * @function:    L_ActivateCalendar 
 * @description: Call ASM_ActivateCalendar and print results 
 */
void L_ActivateCalendar( void )
{
	int l_n_Ret;
	char l_bStatus;
	unsigned short	l_usApplicationType;
	char	l_acOptional[100];
	
	l_usApplicationType = ObjectInfo.application_type;
	l_bStatus = TRUE;
	
	l_n_Ret = ASM_ActivateCalendar(l_usApplicationType,l_bStatus);

	sprintf(l_acOptional, "Application type = %04X\nInput status : %d\n", l_usApplicationType, l_bStatus);
	ASM_PrintResult("ASM_ActivateCalendar", l_n_Ret, l_acOptional, "");
}

/**
 * @function:    L_AddTask 
 * @description: Enable to : 
 *							- set task parameters
 *							- call  ASM_AddTask
 *							- print results 
 */
void L_AddTask( void )
{
	int l_n_Ret;
    ASM_t_task l_xTask;
	DATE xExecutionDate;
	char acDate[9];
	char acTime[9];
	char l_acOptional[256];
	
	memclr(&l_xTask, sizeof(l_xTask));
	
	// The user enter the application date and time		
	GetTimeAndDate(&xExecutionDate,acTime,acDate);

	l_xTask.usTaskId = TASK_ID_10;
	l_xTask.usApplicationId = ObjectInfo.application_type;
	sprintf(l_xTask.acTaskName , "%s", TASK_NAME_10);
	memcpy(&l_xTask.sExexutionTimeBase ,&xExecutionDate,sizeof(DATE)); 
	l_xTask.iPriority = TASK_DEFAULT_PRIORITY;
	l_xTask.iPeriodicity = 1;
	l_xTask.iDuration = 1;
	l_xTask.iNbMaxTry = 3;
	l_xTask.iTimeRetry = 10;
	l_xTask.iStatusLastCall = 0;

	l_n_Ret = ASM_AddTask(&l_xTask);

	sprintf(l_acOptional, "\nApplication Type = %04X\nTask Id= %d\nTask Name = %s\nDate = %s\nTime = %s\nTask priority = %d\nTask periodicity = %d\nTask duration= %d\nNB max try = %d\nTime retry = %d\n",
		l_xTask.usApplicationId, l_xTask.usTaskId, l_xTask.acTaskName, acDate, acTime, l_xTask.iPriority, l_xTask.iPeriodicity, l_xTask.iDuration, l_xTask.iNbMaxTry, l_xTask.iTimeRetry);

	ASM_PrintResult("ASM_AddTask", l_n_Ret, l_acOptional, "");
}

/**
 * @function:    L_ModifyTask 
 * @description: Modify the date/time of the task, call ASM_ModifyTask and print results
 */
void L_ModifyTask( void )
{
	int l_n_Ret, l_n_Ret2;
	unsigned short l_usMask;
	ASM_t_task l_xTask, l_xTask2;
	DATE  xExecutionDate;
	char acText[50];
	char acDate[9];
	char acTime[9];
	char	l_acOptional[256];
	char	l_acOptional2[256];
	
	memclr(l_acOptional, sizeof(l_acOptional));
	memclr(&l_xTask, sizeof(l_xTask));
	memclr(&l_xTask2, sizeof(l_xTask2));
	l_usMask =0;
	
	l_xTask.usTaskId = TASK_ID_10;
	l_xTask.usApplicationId = ObjectInfo.application_type;
	
	// The user enter the application date and time		
	GetTimeAndDate(&xExecutionDate,acTime,acDate);

	sprintf(acText,"\nDate = %s",acDate);
	strcat(l_acOptional, acText);
	sprintf(acText,"\nTime = %s",acTime);
	strcat(l_acOptional, acText);
	
	memcpy(&l_xTask.sExexutionTimeBase ,&xExecutionDate,sizeof(DATE)); 
	l_usMask |=ASM_TASK_EXECUTION_DATE_MASK;
	
	sprintf(acText,"\n\nMask value = %04x\n",l_usMask);
	strcat(l_acOptional, acText);
	
	l_n_Ret = ASM_ModifyTask(l_usMask, &l_xTask);
	
	l_n_Ret2 = ASM_GetTaskInfo(l_xTask.usApplicationId, (unsigned short) l_xTask.usTaskId, &l_xTask2);
	
	memclr(l_acOptional2, sizeof(l_acOptional2));
	if (l_n_Ret==ASM_SUCCESS)
	{
		if (l_n_Ret2==ASM_SUCCESS)
			L_PrintTaskInfoInString(&l_xTask2,l_acOptional2);
		else
			sprintf(l_acOptional2,"\nASM_GetTaskInfo() Didn't work.\n");
	}
	
	ASM_PrintResult("ASM_ModifyTask", l_n_Ret, l_acOptional, l_acOptional2);
}

/**
 * @function:    L_DeleteTask 
 * @description: Call ASM_DeleteTask and print results
 */
void L_DeleteTask( void )
{
	int l_n_Ret;
	unsigned short usTaskId;
	char l_acOptional[100];
	unsigned short	l_usApplicationType;

	l_usApplicationType = ObjectInfo.application_type;
	usTaskId = TASK_ID_10;

	l_n_Ret = ASM_DeleteTask(l_usApplicationType, usTaskId);

	sprintf(l_acOptional, "\nApplication Type = %04X\nTask Id= %d\n", l_usApplicationType, usTaskId);
	ASM_PrintResult("ASM_DeleteTask", l_n_Ret, l_acOptional, "");
}

/**
 * @function:    L_IsTaskExist 
 * @description: Call ASM_TaskExist and print results
 */
void L_IsTaskExist( void )
{
	int l_n_Ret;
	unsigned short usTaskId;
	char l_acOptional[50];
	unsigned short	l_usApplicationType;
	
	l_usApplicationType = ObjectInfo.application_type;
	usTaskId = TASK_ID_10;

	l_n_Ret = ASM_TaskExist(l_usApplicationType, usTaskId);
	
	sprintf(l_acOptional, "\nApplication Type = %04X\nTask Id = %d\n", l_usApplicationType, usTaskId);
	ASM_PrintResult("ASM_TaskExist", l_n_Ret, l_acOptional, "");
}

/**
 * @function:    L_GetNextTaskInfo 
 * @description: Call ASM_GetNextTaskInfo and print next task infos
 */
void L_GetNextTaskInfo( void )
{
	int l_n_Ret;
	ASM_t_task l_xTask;
	unsigned short	l_usApplicationType;
	char	l_acOptional1[256];
	char	l_acOptional2[256];

	l_usApplicationType = ObjectInfo.application_type;

    l_n_Ret = ASM_GetNextTaskInfo(l_usApplicationType, &l_xTask);

	memclr(l_acOptional2, sizeof(l_acOptional2));
	sprintf(l_acOptional1, "Application Type = %04X", l_usApplicationType);
	if (l_n_Ret==ASM_SUCCESS)
		L_PrintTaskInfoInString(&l_xTask,l_acOptional2);
	ASM_PrintResult("ASM_GetNextTaskInfo", l_n_Ret, l_acOptional1, l_acOptional2);
}


/**
 * @function:    L_GetTaskInfo 
 * @description: Call ASM_GetTaskInfo and print task infos
 */
void L_GetTaskInfo( void )
{
	int l_n_Ret;
	unsigned short usTaskId;
	ASM_t_task l_xTask;
	char	l_acOptional1[256];
	char	l_acOptional2[256];
	unsigned short	l_usApplicationType;
	
	l_usApplicationType = ObjectInfo.application_type;
	usTaskId =TASK_ID_10;

	l_n_Ret = ASM_GetTaskInfo(l_usApplicationType, usTaskId, &l_xTask);

	sprintf(l_acOptional1, "\nApplication Type = %04X\nTask Id = %d\n", l_usApplicationType, usTaskId);
	memclr(l_acOptional2, sizeof(l_acOptional2));
	if (l_n_Ret==ASM_SUCCESS)
		L_PrintTaskInfoInString(&l_xTask,l_acOptional2);
	ASM_PrintResult("ASM_GetTaskInfo", l_n_Ret, l_acOptional1, l_acOptional2);
}


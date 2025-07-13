#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup VGE_ASM
	* @{  **/
		

/*
======================================================================
					List of Defines 
======================================================================
*/


#define ASM_SUCCESS										50 		/*!< @b ASM service is successfull									*/
#define ASM_CALENDAR_DOES_NOT_EXIST		51 		/*!< Specified calendar(application Id) doesn't exist	*/
#define ASM_TASK_DOES_NOT_EXIST				52 		/*!< Specified Task (task Id) doesn't exist				*/
#define ASM_CALENDAR_EXIST						53 		/*!< Specified calendar (application Id) already exists   */
#define ASM_INVALID_DATE							54 		/*!< The input Date parameter is invalid					*/
#define ASM_INVALID_PARAM							55 		/*!< The input parameters are invalid					*/
#define ASM_CALL_FAILURE							56 		/*!< Service call failed									*/
#define ASM_NO_TASK_TO_EXECUTE				57 		/*!< No task to execute for the specified calendar		*/
#define ASM_MAX_CALENDAR_ERROR				59 		/*!< The number of calendar already reached the maximum limit	*/
#define ASM_MAX_TASK_ERROR						60 		/*!< The number of Task already reached the maximum limit		*/
#define ASM_TASK_ALREADY_EXIST      	61 		/*!< Specified Task (task Id) already exists				*/
#define ASM_UPDATE_ERROR							62 		/*!< The save of calendar or task data failed			*/
#define ASM_TASK_IN_PROGRESS					63 		/*!< An @b ASM task is already in progress */


#define	MAX_TASK_NUMBER								20 		/*!< Maximum number of calendars	*/
#define	MAX_CALENDAR_NUMBER						12 		/*!<	Maximum number of Tasks for each calendar */
#define MAX_TASK_RETRY								10 		/*!< Maximum number of retry */ 
#define MAX_TASK_TIME_RETRY						600		/*!< Maximum time between two retry : 10 minutes */

#define	TASK_NAME_LENGTH							16 		/*!<	Task Name maximal length*/

// EXECUTE TASK SERVICE CALL ID
#define I_EXECUTE_TASK								90 		/*!<	Id of exucute_task entry point*/

/*
===========================================================
		Mask for the various parameters of a Task
===========================================================
*/


#define ASM_TASK_NAME_MASK							0x0001   /*!< Mask for the bit of the task name */
#define ASM_TASK_EXECUTION_DATE_MASK		0x0002   /*!< Mask for the bit of the execution date */
#define ASM_TASK_PERIODICITY_MASK				0x0010   /*!< Mask for the bit of the periodicity */	
#define ASM_TASK_PRIORITY_MASK					0x0020   /*!< Mask for the bit of the task priority */
#define ASM_TASK_STATUS_LAST_CALL_MASK	0x0100   /*!< Mask for the bit of the status of the last call */
#define ASM_TASK_NB_MAX_TRY_MASK				0x0200   /*!< Mask for the bit of the maximum number of try */	
#define ASM_TASK_TIME_RETRY_MASK				0x1000   /*!< Mask for the bit of time to retry */
#define ASM_TASK_DURATION_MASK					0x2000   /*!< Mask for the bit of the duration */
#define ASM_TASK_ALL_MASK     (ASM_TASK_NAME_MASK|		\
				ASM_TASK_EXECUTION_DATE_MASK|	\
				ASM_TASK_PERIODICITY_MASK|		\
				ASM_TASK_PRIORITY_MASK |		\
				ASM_TASK_STATUS_LAST_CALL_MASK| \
				ASM_TASK_NB_MAX_TRY_MASK|		\
				ASM_TASK_TIME_RETRY_MASK|		\
				ASM_TASK_DURATION_MASK)


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Task information structure. 
	*/
typedef struct
{
	unsigned short	usApplicationId ;					/*!< @b Mandatory. Id of the application that created the task. @n @n It is obtained by calling the primitive <tt>ObjectGetInfo() : ObjectInfo.application_type</tt>.		**/
	unsigned short	usTaskId ;								/*!< @b Mandatory; Id of the task. @n @n This Id is used by the application in the \c execute_task entry point to execute the task */
	char acTaskName[TASK_NAME_LENGTH] ;				/*!< @b Optional. Task name */
	DATE sExexutionTimeBase ;									/*!< @b Mandatory. Date and time of task execution. @n @n Execution time in application time reference:
																					 	- If #iPeriodicity = @c 0, this value corresponds to the execution time
																						- If #iPeriodicity < @c 24, this value corresponds to the first execution time.
																						- If #iPeriodicity >= @c 24, the fields hour, minute and second will be used as reference to calculate the next call.			*/
	int iPriority ;														/*!< @b Mandatory. Priority of the task. @n @n If two tasks have the same execution time, this priority will be used to determine which task to execute first.	*/					
	int iPeriodicity ;												/*!< @b Mandatory. Call frequency in hour. @n @n If #iPeriodicity = \c 0, the task will be executed only one time. */
	int iDuration ;														/*!< @b Mandatory. Duration in hour. @n @n Used to disperse the execution of tasks on an interval to avoid several terminals call their task at the same time (for example: task which performs a call to TMS server). */
	int iNbMaxTry ;														/*!< @b Mandatory. Maximum number of call try. @n @n When it returns #ASM_CALL_FAILURE: 
																						- Minimum Value  = @c 1
																						- Maximum value = #MAX_TASK_RETRY					*/
	int iTimeRetry ;													/*!< @b Mandatory. Time between two calls in second.	
	- Minimum Value  = \c 1
	- Maximum value = #MAX_TASK_TIME_RETRY		*/
	int iStatusLastCall ;												/*!< @b Optional. Status of last call 
	- #ASM_SUCCESS 
	- #ASM_CALL_FAILURE					*/		
}ASM_t_task;


/*! @brief Calendar structure. */
typedef struct
{
	unsigned short	usApplicationId ;							/*!< Id of the application that created the task.	*/
	char			bCalendarStatus ;										/*!< Status of the calendar	
																								- @c TRUE:	the calendar is activated
																								- @c FALSE: the calendar is inactivated	*/					
	unsigned int	uiNbOfTask ;										/*!< Number of registered tasks.	*/	
	int				iDeltaDate ;												/*!< Delta date between the system and the application (in days).	*/
	int				iDeltaTime ;												/*!< Delta time between the system and the application (in minutes).	*/
} ASM_t_calendar;


/*! @brief Structure containing parameters to exchange between the calendar and the application when calling the @c execute_task entry point. 
*/
typedef struct
{
	unsigned short i_usAppliType;									/*!< Application Type of the called application.	*/
	unsigned short i_usService;										/*!< Id of the Service to be called: @c I_EXECUTE_TASK.	*/
	unsigned short i_usTaskToExecute;							/*!< Id of the task to be executed by the called application.	*/
	int o_nAppliStatus;														/*!< Status to return from the called application to the @b ASM component.	*/
}ASM_t_ExecuteTaskPt;



/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief	This function enables the @a DeltaDate and @a DeltaTime calculation between system date and time and application date and time. 
 *	@param[in]		i_pxApplicationDate		Pointer to the application Date. 
 *	@param[out]		o_iDeltaDate		Delta Date between application and System (in number of Days). 
 *	@param[out]		o_iDeltaTime		Delta Time between application and System (in number of minutes). 
 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_INVALID_DATE; or
 *	- #ASM_TASK_IN_PROGRESS 
 
 * @note This function can be used before the creation of the calendar.	
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_CalculateDeltaDate
(
	DATE * i_pxApplicationDate,
	int  * o_iDeltaDate,
	int  * o_iDeltaTime	
);


/*! @brief	This function enables an application to register itself in the @b ASM module. (Create an internal calendar for the application).

 *	@param[in]		i_usApplicationId		Application Id. 
 *	@param[in]		i_iDeltaDate			Delta date between the system and the application (in days).
 *	@param[in]		i_iDeltaTime			Delta time between the system and the application (in minutes).
 *  @par
 *  The value of @c i_usApplicationId must be obtained by calling the primitive @c ObjectGetInfo() : @c ObjectInfo.application_type 
 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_EXIST; or
 *	- #ASM_UPDATE_ERROR; or
 *	- #ASM_MAX_CALENDAR_ERROR; or
 *	- #ASM_TASK_IN_PROGRESS
 
 *  @note If \a i_iDeltaTime = \c 0 and \a i_iDeltaTime = \c 0, the application calendar will use the system Date & Time and no processing for \a DeltaDate and \a DeltaTime is required.
 *  @note If \a i_iDeltaTime != \c 0 or \a i_iDeltaTime != \c 0, and the system Date & Time are modified, the @b ASM module will calculate automatically the new value of \a DeltaDate and \a DeltaTime.
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_CreateCalendar
(
	unsigned short i_usApplicationId ,
	int i_iDeltaDate,		/*	Number of days	*/
	int i_iDeltaTime		/*	Number of seconds	*/
);


/*! @brief This function enables the application to remove its registration from the calendar module. It involves the removal of all the tasks added for this application.

 *	@param[in]		i_usApplicationId		Application Id. 
 *	@par
 *	The value of \a i_usApplicationId can be obtained by calling the primitive <tt>ObjectGetInfo() : ObjectInfo.application_type</tt>
 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_UPDATE_ERROR; or
 *	- #ASM_TASK_IN_PROGRESS
  
 * @link VGE_ASM Back to top @endlink
**/
int ASM_DeleteCalendar
(
	unsigned short i_usApplicationId
);



/*! @brief	This function modifies the status of an application calendar: @a Active/Inactive 

 * @param[in]		i_usApplicationId		Application Id. 
 * @param[in]		i_bCalenderStatus		Calendar status.
 * @par
 * - @a ACTIVE: @c TRUE
 * - @a NOT @a ACTIVE: @c FALSE
 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_UPDATE_ERROR; or
 *	- #ASM_TASK_IN_PROGRESS
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_ActivateCalendar
(
	unsigned short i_usApplicationId,
	char i_bCalenderStatus
);


/*! @brief	This function adds a new task in the calendar.

 *	@param[in]		i_pxTask : The new task to add to the calendar / Pointer on structure containing information about the task.
 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_MAX_TASK_ERROR; or
 *	- #ASM_TASK_ALREADY_EXIST; or
 *	- #ASM_UPDATE_ERROR; or
 *	-	#ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_INVALID_DATE; or
 *	- #ASM_INVALID_PARAM; or
 *	- #ASM_TASK_IN_PROGRESS

 * @sa 
 * - @link ASM_t_task Task structure@endlink  
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_AddTask
(
	ASM_t_task* i_pxTask
);



/*! @brief	This function modifies an existing task in a calendar.

 *	@param[in]		i_usParamMask		Mask indicating the parameters to modify.
 *	@param[in]		i_pxTask			Task description containing the new parameteres / Pointer on structure containing task parameters
 * @par 
 * The possible mask values:
 * - #ASM_TASK_NAME_MASK
 * - #ASM_TASK_EXECUTION_DATE_MASK
 * - #ASM_TASK_PRIORITY_MASK
 * - #ASM_TASK_STATUS_LAST_CALL_MASK
 * - #ASM_TASK_NB_MAX_TRY_MASK
 * - #ASM_TASK_TIME_RETRY_MASK
 * - #ASM_TASK_DURATION_MASK
 * - #ASM_TASK_ALL_MASK
 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_TASK_DOES_NOT_EXIST; or
 * 	-	#ASM_UPDATE_ERROR; or
 *	- #ASM_INVALID_DATE; or
 *	- #ASM_INVALID_PARAM; or
 *	- #ASM_TASK_IN_PROGRESS
 *
 * @note Only the parameters to be modified are initialized in the task structure
 * 
 * @link VGE_ASM Back to top @endlink
**/

int ASM_ModifyTask
(
	unsigned short i_usParamMask,
	ASM_t_task* i_pxTask
);


/*! @brief	This function deletes an existing task in the calendar.

 *	@param[in]		i_usApplicationId		Application Id. 
 *	@param[in]		i_usTaskId				Id of the task to delete. 

 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_TASK_DOES_NOT_EXIST; or
 *	- #ASM_UPDATE_ERROR; or
 *	- #ASM_TASK_IN_PROGRESS
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_DeleteTask
(
	unsigned short i_usApplicationId,
	unsigned short i_usTaskId
);


/*! @brief	This function checks the existence of calendars and tasks in the @b ASM module.

 *	@param[in]		i_usApplicationId		Application Id. 
 *	@param[in]		i_usTaskId				Task Id. 

 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_TASK_DOES_NOT_EXIST; or
 *	- #ASM_TASK_IN_PROGRESS
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_TaskExist(unsigned short i_usApplicationId,unsigned short i_usTaskId);



/*! @brief	This function gets information about the next task to execute for a specified application.

 *	@param[in]		i_usApplicationId		Application Id. 
 *	@param[out]		o_pxTask				Information about the next task to execute / Pointer on structure containing the information about the next task to execute. 

 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_TASK_DOES_NOT_EXIST; or
 *	- #ASM_TASK_IN_PROGRESS
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_GetNextTaskInfo
(
	unsigned short i_usApplicationId,
	ASM_t_task* o_pxTask
);


/*! @brief	This function gets information about a specified task to execute in a specified calendar.

 *	@param[in]		i_usApplicationId		Application Id. 
 *	@param[in]		i_usTaskId				Task Id. 
 *	@param[out]		o_pxTask				Information about the task / Pointer on structure containing the information about the task. 

 *	@return
 *	- #ASM_SUCCESS; or
 *	- #ASM_CALENDAR_DOES_NOT_EXIST; or
 *	- #ASM_TASK_DOES_NOT_EXIST; or
 *	- #ASM_TASK_IN_PROGRESS
 * 
 * @link VGE_ASM Back to top @endlink
**/
int ASM_GetTaskInfo
(
	unsigned short i_usApplicationId,
	unsigned short i_usTaskId,
	ASM_t_task* o_pxTask
);

 
/*! @} **/

#ifdef __cplusplus
}
#endif

/*! @addtogroup KSFAM_OS_KERNEL
	* @{
 */ 

#ifndef _XECARM_H
#define _XECARM_H

#include "basearm.h"


//  XEC68C.H  :  "C" INTERFACE OF THE XEC68 KERNEL PRIMITIVES   V3.1 */


/*
======================================================================
					List of Defines
======================================================================
*/

#define  cTimeOut            1  /*!< DontTrap, XECProduct,   1 */
#define  cExceptionOccurred  2  /*!< DontTrap, XECProduct,   2 */
#define  cSemOverFlow        3  /*!< DontTrap, XECProduct,   3 */
#define  cSemNonAvailable    4  /*!< DontTrap, XECProduct,   4 */
#define  cFull               5  /*!< DontTrap, XECProduct,   5 */
#define  cNoMessPending      6  /*!< DontTrap, XECProduct,   6 */
#define  cCleared            7  /*!< DontTrap, XECProduct,   7 */

#define  cBadTaskNumber             -32767  /*!< MustTrap, XECProduct,   1 */
#define  cBadSemaphoreNumber        -32766  /*!< MustTrap, XECProduct,   2 */
#define  cBadMailBoxNumber          -32765  /*!< MustTrap, XECProduct,   3 */
#define  cBadDelayNumber            -32764  /*!< MustTrap, XECProduct,   4 */
#define  cBadPriority               -32763  /*!< MustTrap, XECProduct,   5 */
#define  cBadClockTkPriority        -32762  /*!< MustTrap, XECProduct,   6 */
#define  cDataSegmentOverFlow       -32761  /*!< MustTrap, XECProduct,   7 */
#define  cNegMaxValue               -32759  /*!< MustTrap, XECProduct,   9 */
#define  cNegCapacity               -32758  /*!< MustTrap, XECProduct,  10 */
#define  cCurrTask                  -32757  /*!< MustTrap, XECProduct,  11 */
#define  cDelaySlotAlreadyUsed      -32756  /*!< MustTrap, XECProduct,  12 */
#define  cTaskNotInitialized        -32755  /*!< MustTrap, XECProduct,  13 */
#define  cTaskAlreadyStarted        -32754  /*!< MustTrap, XECProduct,  14 */
#define  cTaskNotOperational        -32753  /*!< MustTrap, XECProduct,  15 */
#define  cNestingOverFlow           -32752  /*!< MustTrap, XECProduct,  16 */
#define  cNestingUnderFlow          -32751  /*!< MustTrap, XECProduct,  17 */
#define  cWaitInBackGroundTask      -32749  /*!< MustTrap, XECProduct,  19 */
#define  cMessOverFlow              -32748  /*!< MustTrap, XECProduct,  20 */
#define  cTaskAbnormalEnd           -32747  /*!< MustTrap, XECProduct,  21 */
#define  cNbObjectOverflow          -32746  /*!< MustTrap, XECProduct,  22 */
#define  cInvalidOpCode             -32745  /*!< MustTrap, XECProduct,  23 */
#define  cInsufficientPrivilege     -32744  /*!< MustTrap, XECProduct,  24 */
#define  cTerminateInBackgroundTask -32743  /*!< MustTrap, XECProduct,  25 */


#define  cCurrent            0		/*!< return value for OS_rtc_TaskState : specified task is the running one */
#define  cReady              1		/*!< return value for OS_rtc_TaskState : specified task is ready */
#define  cWaiting            2		/*!< return value for OS_rtc_TaskState : specified task is waiting */
#define  cNonOperational     3		/*!< return value for OS_rtc_TaskState : specified task is stopped */

#define  cInfiniteWaiting    0		/*!< value for endless waiting */



/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Define a status. */
typedef Word tStatus;

/*! @brief Define the timeout time :  \li zero : infinite waiting; cTimeOut never occurs. \li other: max waiting time in clock base units (finite waiting) */
typedef DoubleWord tTimeOut;

/*! @brief Define the state of a task :  \li 0=cCurrent, \li 1=cReady, \li 2=cWaiting, \li 3=cNonOperational */
typedef Word   tTaskState;

/*! @brief Define an event. */
typedef Word tEvent;  /* range 0..15 */

/*! @brief Corresponding to the sum of bits, 1 bit per event. */
typedef DoubleWord tEventList;


/*! @}  */ 



/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @addtogroup KSFAM_OS_TASK
	* @{
	 */ 	

/*
=======================================
			Task management
=======================================
*/


/*! @brief OS_rtc_StartTask resumes a suspended task. 
 * @param TaskNumber : task number of the task to resume
 * @return error code :
 * - cOK 
 * - cBadTaskNumber (fatal error : The task number specified is not in the range configured by the OS).
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
extern tStatus OS_rtc_StartTask(Word TaskNumber);

/*! @brief OS_rtc_StopTask suspend a task. 
 * @param TaskNumber : task number of the task to suspend
 * @return error code :
 * - cOK 
 * - cBadTaskNumber (fatal error : The task number specified is not in the range configured by the OS).
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */
extern tStatus OS_rtc_StopTask(Word TaskNumber);

/*! @brief OS_rtc_CurrentTask returns the OEMC task number of the current task. 
 * @return Current OEMC task number. The TaskNumber for a user defined task 
 * - or -1     for the BackGround Task
 * - or -2     for the Clock Task 
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_CurrentTask:KSFAM_OS:0x04
// \endif
extern short OS_rtc_CurrentTask(void);

                     

/*! @brief OS_rtc_TaskState gets the state of a task.
 * @param TaskNumber : task number affected to this task (see CurrentTask ).
 * @param pTaskState : state of the task.
 * - 0 : cCurrent = specified task is the running one
 * - 1 : cReady   = specified task is ready
 * - 2 : cWaiting = specified task is waiting
 * - 3 : cNonOperational = specified task is stopped
 * @return error code :
 * - cOK 
 * - cBadTaskNumber (fatal error : The task number specified is not in the range configured by the OS).
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_TaskState:KSFAM_OS:0x09
//  @GSIM_A:2:ONE_POINTER
// \endif
extern tStatus OS_rtc_TaskState( Word TaskNumber,
                          Word *pTaskState);


/*! @brief OS_rtc_Terminate Stop Current task.
 *   WARNING : OS_rtc_Terminate doesn't free task's stack. kill must be used instead of OS_rtc_Terminate
 * @return error code : 
 * - cOK 
 * - cBadTaskNumber (called by unknown rtc task).
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_TaskState:KSFAM_OS:0x1E
// \endif
extern tStatus OS_rtc_Terminate(void);



                            
/*! @}  */ 


/*! @addtogroup KSFAM_OS_EVENT
	* @{
	 */ 	
/*
=======================================
			Event management 
=======================================
*/

/*! @brief OS_rtc_SignalEvent signals a real time event, to a given task.
 *
 * The event @c EventNumber of the task identified by @c TaskNumber is set. 
   Should this task be waiting for the occurrence of this event, it is
   reactivated and its state is changed back to the ready or current state.
 * @param TaskNumber  : task number to which an event is to be signalled. 
 * @param EventNumber : event number to signal. from 0 to 31.
 * @return error code :
 * - cOK 
 * - cBadTaskNumber : fatal errors, The task number specified is not in the range configured by the OS
 *
 * @note  Some event numbers are reserved for OEMC peripherals, and for manager. 
 *
 * @link KSFAM_OS_EVENT Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_SignalEvent:KSFAM_OS:0x05
// \endif
extern tStatus OS_rtc_SignalEvent( Word   TaskNumber,
                                   tEvent EventNumber);   /* range 0..15 */



/*! @brief The calling task is put in the waiting (cWaiting) state until one of the events of @c EventList is signalled (i.e. put in the 'set' state). 
 *
 * If one of the events specified in @c EventList is already set upon calling
   WaitEvents, the calling task does not wait nor it is pre-empted.
 *
 * In order to limit the waiting time, a maximum value @c TimeOut can be specified. 
   @c TimeOut is given in terms of number of 10 milliseconds.
   if the time-out occurs before any of the events, the task is reactivated
   and will resume with a status cTimeOut. A value of zero means that
   no limit is requested.
 *
 * If @c Eventlist is empty, then the invoking task only waits for the
   occurrence of a time-out. Note that passing an empty @c EventList
   and a value of zero for @c Timeout will provoke an infinite wait.
 * @param EventsAwaited : List of awaited events : 1 bit per event, 
   where the bit number corresponds to the event number. (The least significant bit corresponds
   to @c EventNumber = 0). If @c EventList = 0 (i.e. the event list is empty)
   then only the @c TimeOut is awaited.
 * @param TimeOut 			 : Maximum waiting time in terms of 10 milliseconds period. A time-out
   value of 0 indicates no waiting limit.
 * @param pEventsOccurred : List of all occurred events : 1 bit per event (included those which are not waited)
 * @return error code :
 * - cOK 
 * - cTimeOut : The time out specified in the call occurred before any of the specified events occurred.
 *
 * @link KSFAM_OS_EVENT Back to top @endlink
 */ 
extern tStatus OS_rtc_WaitEvents( Word EventsAwaited,
                                  DoubleWord TimeOut,
                                  Word *pEventsOccurred);


/*! @brief OS_rtc_WaitEvents32 waits for one or several real time events. 
 * @param EventsAwaited   : 32 bits bitfield. Each bit corresponds to an event. 
 * Each bit set to 1 corresponds to an awaited event.
 * @param TimeOut         : timeout value (unit = 10 ms). To set an infinite timeout value TimeOut = 0.
 * @param pEventsOccurred : pointer to tEventList. 32 bit bitfield. Each bit corresponds to an event. 
 * Each bit set to 1 corresponds to a received event.
 * @return error code :
 * - 0 if OK.
 * - Other returned values are defined in file xecarm.h.
 *
 * @link KSFAM_OS_EVENT Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_WaitEvents32:KSFAM_OS:0x07
//  @GSIM_S:OS_rtc_WaitEvents32:E_OS_rtc_WaitEvents32
// \endif
tStatus OS_rtc_WaitEvents32( tEventList EventsAwaited,
                           DoubleWord TimeOut,
                           tEventList *pEventsOccurred);                           

       /* returns status = cOK or cTimeOut or cExceptionOccurred */


/*! @brief OS_rtc_EventsOccurred tests whether ALL the events of @c EventList of the calling task have occurred.
 * @param EventList : List of events to be tested : 1 bit per event, where the bit number corresponds to the event number. (The least significant bit corresponds to EventNumber>0) 
 * @return 
 * - 1 (TRUE) if all the events in EventList occurred or if EventList is empty.
 * - 0 (FALSE) if at least one of the events in EventList has not occurred. The primitive tests whether ALL the events of EventList of the calling task have occurred.
 *
 * @link KSFAM_OS_EVENT Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_EventsOccurred:KSFAM_OS:0x0A
// \endif
extern Boolean OS_rtc_EventsOccurred(tEventList EventList);



/*! @brief OS_rtc_ClearEvent clears one or several real time events in the current task. 
 * @param EventList : 32 bits bitfield. To each bit corresponds an event. 
 * Each bit set to 1 will erase the corresponding event. 
 * @return error code :
 * - 0 if OK.
 * - Other returned values are defined in file xecarm.h.
 *
 * @link KSFAM_OS_EVENT Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_ClearEvents:KSFAM_OS:0x06
// \endif
extern tStatus OS_rtc_ClearEvents( tEventList EventList);

/*! @}  */ 


/*! @addtogroup KSFAM_OS_SEMAPHORE
	* @{
	 */ 	
	
/*
=======================================
			Semaphore management
=======================================
*/


/*! @brief OS_rtc_InitSemaphore initialises the count limit of the semaphore identified by SemaphoreNumber. 
 *
 * All the semaphores have the following default initialisation : 
 *
 * - UnitCount   = 0 
 * - Task queue  = empty 
 * - Count limit = 32767 
 *
 * The unit count can be initialised by calling repeatedly the V primitive .
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @param CountMaxValue   : Maximum value (limit) that the count may take in the range 0..32767. 
 * @return error code :
 * - cOK 
 * - cBadSemaphoreNumber : fatal errors, the semaphore number specified is not in the range configured by the OS.
 * - cNegMaxValue : The CountMaxValue parameter has a negative value. 
 *
 * @link KSFAM_OS_SEMAPHORE Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_InitSemaphore:KSFAM_OS:0x12
// \endif
extern tStatus OS_rtc_InitSemaphore( Word  SemaphoreNumber,
                                     Word  CountMaxValue);

                               /* range 0..NbSemaphores-1 */
                               /* range 0..32767 */


/*! @brief The calling task is releasing a unit of the semaphore identified by SemaphoreNumber. 
 *
 * The unit count associated with the semaphore is incremented and if any tasks are waiting, 
   the first is dequeued from the task queue associated with the semaphore, put back in the 
   READY or CURRENT state and the unit is granted to it. 
 *
 * Should the maximum value of the semaphore count be exceeded, the unit count remains unchanged and a cSemOverflow status returned.
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @return error code :
 * - cOK 
 * - cSemOverFlow : More V primitives have been performed on this semaphore than allowed by the count limit. 
 * - cBadSemaphoreNumber : Fatal error. The semaphore number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_OS_SEMAPHORE Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_V:KSFAM_OS:0x15
// \endif
extern tStatus OS_rtc_V( Word SemaphoreNumber);

                               /* returns status = cOK or cSemOverFlow */


/*! @brief The calling task is requesting allocation of a unit in the semaphore identified by SemaphoreNumber. 
 *
 * If no unit is available, the calling task is inserted at 
   the end of the task queue associated with semaphore SemaphoreNumber and waits until one unit 
   is available. The unit count associated with the semaphore is decremented. 
 *
 * In order to limit the waiting time, a maximum value TimeOut can be specified. Timeout is 
   specified in terms of number of 10 milliseconds. If the time-out occurs before the granting 
   of the unit, the task is reactivated and will resume with a status cTime-out. A value of 
   zero means that no limit is requested. 
 * @param TimeOut : Maximum waiting time in terms of number of 10 milliseconds. A time-out value of 0 indicates no waiting limit.
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @return error code :
 * - cOK 
 * - cTimeOut : The time out specified in the call occurred before a unit was granted in the specified semaphore. 
 * - cBadSemaphoreNumber : Fatal error. The semaphore number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_OS_SEMAPHORE Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_P:KSFAM_OS:0x14
// \endif
extern tStatus OS_rtc_P( Word SemaphoreNumber,
                       tTimeOut TimeOut);

              /* returns status = cOK or cTimeOut or cExceptionOccurred */



/*! @brief The calling task is requesting allocation of a unit in the semaphore identified by SemaphoreNumber with no waiting if no unit is available.
 *
 * If a semaphore unit is available, it is granted and the unit count is decremented. Otherwise a status indicating
 * that no unit is available is returned (cSemNonAvailable). 
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @return  error code :
 * - cOK 
 * - cSemNonavailable : no unit was available in the specified semaphore. 
 * - cBadSemaphoreNumber : Fatal error. The semaphore number specified is not in the range configured by the OS.
 *
 * @link KSFAM_OS_SEMAPHORE Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_TestP:KSFAM_OS:0x13
// \endif
extern tStatus OS_rtc_TestP( Word SemaphoreNumber);

              /* returns status = cOK or cSemNonAvailable */



/*! @}  */ 



/*! @addtogroup KSFAM_OS_MAILBOX
	* @{
	 */ 	
	
	
/*
=======================================
			Mailbox management
=======================================
*/


/*! @brief Initialises the local message capacity of the mailbox. 
 *
 * All the mailboxes have a default initialisation :
 * - Number of pending messages = 0 
 * - Number of waiting tasks = 0 
 * - Limit on the number of pending messages = 32767 
 *
 * This is done at OS run time. So, all the mailboxes can be immediately used with no 
     further initialisation. The default value of the limit on the number of pending messages 
     will never be reached as the limit on the overall number of pending messages would be 
     reached much before. 
 * 
 * InitMailbox can be called at any moment, even for a mailbox already in use. 
   If the number of pending messages at that point is greater than the newly 
   specified value, all the messages remain pending, but further calls to send will not be 
   accepted until the number of messages in the queue actually becomes lower than the limit. 
 * @param MailBoxNumber : Use GetMailboxUser .
 * @param Capacity : mailbox capacity (max. number of messages waiting in the mailbox) 
 * @return error code :
 * - cOK 
 * - cBadMailBoxNumber : The mailbox number specified is not in the range configured by the OS. 
 * - cNegCapacity : The mailbox capacity specified has a negative value. 
 *
 * @link KSFAM_OS_MAILBOX Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_InitMailBox:KSFAM_OS:0x1B
// \endif
extern tStatus OS_rtc_InitMailBox( Word MailBoxNumber,
                            Word Capacity);

               /* range 0..NbMailBoxes-1 */
               /* range 0..32767 */



/*! @brief The OS_rtc_Send primitive requests the sending of the message 'Message' to the mailbox identified by @c MailboxNumber. 
 *
 * If no task is waiting for a message from the mailbox the @c Message is stored in an 'envelope' and enqueued at the end of the message queue associated with the mailbox.
 *
 * if no envelope is available, a (cMessOverflow) is generated. Should the number of messages in
   the message queue exceed the local capacity specified by the
   primitive InitMailbox, the request is refused and an error status word
   (cFull) is returned to the calling task.
 *
 * In the case where the queue of waiting tasks is not empty, the
   message is directly granted to the first task of the queue, which is
   thus dequeued and activated. 
 * @param MailBoxNumber : Use GetMailboxUser() to get the MailBoxNumber.
 * @param Message : Message to be sent (4 bytes) 
 * @return error code :
 * - cOK 
 * - cFull : The local capacity of the mailbox (specified by InitMailBox) has been exceeded. 
 *
 * @link KSFAM_OS_MAILBOX Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_Send:KSFAM_OS:0x18
// \endif
extern tStatus OS_rtc_Send( Word MailBoxNumber,
                     DoubleWord Message);

               /* returns status = cOK or cFull */



/*! @brief The OS_rtc_Receive primitive requests a message from the mailbox identified by @c MailboxNumber. 
 *
 * If no message is pending in the mailbox, the calling task 
   is put in the waiting state and is inserted at the end of the task queue associated
   with the mailbox and waits until a message is available. 
 *
 * If there is already a message in the mailbox the task does not wait nor it is 
   pre-empted, gets the message and returns its envelope. 
 *
 * In order to limit the waiting time, a maximum value 'TimeOut' can be specified. 
   'TimeOut' is specified in terms of number of 10 milliseconds. If the time-out occurs 
   before the occurrence of a message, the task is reactivated and will resume with a status cTimeOut. 
   A value of zero means that no limit is requested. 
 * @param MailBoxNumber : Use GetMailboxUser() to get the MailBoxNumber.
 * @param pMessage : pointer to the received message (4 bytes).
 * @param TimeOut : Maximum waiting time in terms of number of 10 milliseconds. 
 * A time-out value of 0 indicates no waiting limit. 
 * @return error code :
 * - cOK 
 * - cTimeOut : The time out specified in the call occurred before a message was available in the specified mailbox. 
 * - cBadMailBoxNumber : The mailbox number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_OS_MAILBOX Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_Receive:KSFAM_OS:0x19
//  @GSIM_A:2:ONE_POINTER
// \endif
extern tStatus OS_rtc_Receive( Word MailBoxNumber,
                        DoubleWord *pMessage,
                        tTimeOut   TimeOut);

               /* pointer to the output variable */
               /* returns status = cOK or cTimeOut or cExceptionOccurred */


/*! @brief The Receive Primitive requests a message from the mailbox identified by @c MailboxNumber, with no waiting if no message is pending. 
 *
 * In this case a status (cNoMessPending) indicating that no message is available is returned. 
 * @param MailBoxNumber : Use GetMailboxUser() to get the MailBoxNumber.
 * @param pMessage : pointer to the received message (4 bytes). Output parameter.
 * @return error code :
 * - cOK 
 * - cNoMessPending : No message was pending in the specified mailbox. 
 * - cBadMailBoxNumber : The mailbox number specified is not in the range configured by the OS.
 *
 * @link KSFAM_OS_MAILBOX Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_TestReceive:KSFAM_OS:0x1A
//  @GSIM_A:2:ONE_POINTER
// \endif
extern tStatus OS_rtc_TestReceive( Word MailBoxNumber,
                            DoubleWord *pMessage);

               /* pointer to the output variable */
               /* returns status = cOK or cNoMessPending */



/*! @}  */ 


/*! @addtogroup KSFAM_OS_DELAY
	* @{
	 */ 	
	

/*
=======================================
			Delay management 
=======================================
*/


/*! @brief This primitive requests the execution of @c UserDelayProcedure upon detecting 
 * the expiration of @c FirstDelay, and to repeat cyclically this primitive with a periodic delay 'period'. 
 *
 * The invoking task is not pre-empted through the StartLDelay primitive. 
 * 
 * 'Period' and @c FirstDelay are expressed in number of 10 milliseconds. 
 * 
 * Some examples of what this procedure could do : 
 * - Signal an event to a task waiting for this event to synchronise cyclic execution. 
 * - Release a unit to a semaphore to wake up a task waiting for one unit of this semaphore.
 * - Send a predefined message to a mailbox 
 * - Increment a counter or set a flag for statistical purposes 
 * - Sample values of counters incremented by other tasks in order to make statistics on task activity 
 * 
 * There are some precautions to take concerning the procedure : 
 * - It is technically possible to call all the routines of the kernel but it is highly 
     recommended not to call primitives which could put the clock task in the waiting or 
     in the non-operational state, as this may block the services provided by the clock task. 
 * - No call of OEMC / M2-OS routines 
 * - @c UserDelayProcedure is a procedure called by the JSR instruction, with no parameters. 
 * - @c UserDelayProcedure cannot rely on any register values initialised by a host task. 
     Rather, it should initialize all data and address registers it will use, as is usually 
     done in interrupt routines. But none of them have to be restored, except the system stack 
 * 
 * Besides note that the StartLDelay may be called at any time between two clock interrupts : 
   the accuracy of the first delay is 1 clock tick. 
 *
 * @param DelayNumber : Delay identifier (Use GetDelayUser() to get the DelayNumber). range 0..NbDelays-1 
 * @param FirstDelay : First delay. (in unit of 10ms).
 *     Value in the range 00..65535 (a value of 0 will be considered as 1) .
 * @param Period : Period between successive delays. (in unit of 10ms)
 *     A value of zero indicates that no cyclic delay is requested. 
 * @param FunctionPtr : pointer to the function to be activated at the expiration of the delay
 * @return error code :
 * - cOK 
 * - cBadDelayNumber : The delay number specified is not in the range configured by the OS. 
 * - cDelaySlotAlreadyUsed : The specified delay has already been activated by a call to StartLDelay. 
 *
 * @link KSFAM_OS_DELAY Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_StartLDelay:KSFAM_OS:0x20
//  @GSIM_S:StartLDelay:E_StartLDelay
// \endif
extern tStatus OS_rtc_StartLDelay(
                       Word DelayNumber,   
                       DoubleWord FirstDelay, 
                       DoubleWord Period,     
                       word (*FunctionPtr)());
                                          


/*! @brief This primitive will cancel the handling of the delay identified by DelayNumber and started by StartDelay. 
 * @param DelayNumber  : Delay identifier: Use GetDelayUser() to get the DelayNumber
 * @param pRestOfDelay : Output param. Remaining time before the next expiration of delay. 
 *
 * It is expressed in number of 10 milliseconds.
 * - if > 0 : remaining delay until the next activation of the user procedure.
 * - if = 0 : (non periodical) delay already occurred or stopped.
 *
 * @param pPeriod : Period value or zero in case of non periodical delay. Not used.
 * @return error code :
 * - cOK 
 * - cBadDelayNumber : The delay number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_OS_DELAY Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:OS_rtc_StopDelay:KSFAM_OS:0x21
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
// \endif
extern tStatus OS_rtc_StopDelay( Word DelayNumber,
                          DoubleWord *pRestOfDelay,
                          DoubleWord *pPeriod);


/*! @}  */ 


/*! @addtogroup KSFAM_OS_KERNEL
	* @{
	 */ 	

/*
======================================================================
					List of Defines
======================================================================
*/

#define	Terminate				        OS_rtc_Terminate
#define	StartTask						OS_rtc_StartTask				       	/*!< Only for compatibility */
#define	StopTask			  			OS_rtc_StopTask							/*!< Only for compatibility */
#define	CurrentTask						OS_rtc_CurrentTask						/*!< Only for compatibility */
#define	TaskState						OS_rtc_TaskState			    		/*!< Only for compatibility */
#define	ChangePriority				    OS_rtc_ChangePriority				    /*!< Only for compatibility */
#define	EnterRegion						OS_rtc_EnterRegion						/*!< Only for compatibility */
#define	LeaveRegion						OS_rtc_LeaveRegion						/*!< Only for compatibility */
#define	SignalEvent						OS_rtc_SignalEvent						/*!< Only for compatibility */
#define	WaitEvents						OS_rtc_WaitEvents32						/*!< Only for compatibility */
#define	EventsOccurred				    OS_rtc_EventsOccurred				    /*!< Only for compatibility */
#define	ClearEvents						OS_rtc_ClearEvents						/*!< Only for compatibility */
#define	InitSemaphore					OS_rtc_InitSemaphore					/*!< Only for compatibility */
#define	V								OS_rtc_V					            /*!< Only for compatibility */
#define	P								OS_rtc_P					            /*!< Only for compatibility */
#define	PWithPrio						OS_rtc_PWithPrio					    /*!< Only for compatibility */
#define	TestP							OS_rtc_TestP					        /*!< Only for compatibility */
#define	InitMailBox						OS_rtc_InitMailBox						/*!< Only for compatibility */
#define	Send							OS_rtc_Send						        /*!< Only for compatibility */
#define	SendWithPrio					OS_rtc_SendWithPrio						/*!< Only for compatibility */
#define	Receive							OS_rtc_Receive						    /*!< Only for compatibility */
#define	TestReceive						OS_rtc_TestReceive						/*!< Only for compatibility */
#define	ClearMailBox					OS_rtc_ClearMailBox						/*!< Only for compatibility */
#define	StartLDelay						OS_rtc_StartLDelay						/*!< Only for compatibility */
#define	StopDelay						OS_rtc_StopDelay					    /*!< Only for compatibility */



#endif
/*! @}  */ 

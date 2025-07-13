/*! @addtogroup KSFAM_IAM
	* @{
**/
/* Process the sending or receiving messages */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef MSGMGR_H
#define MSGMGR_H

#define SEQ_READY					0x8000
#define DEVICE_READY				0x8001
#define DISPLAY_REQUEST				0x8002
#define RESET_TERMINAL				0x8003
#define READ_DATE_REQUEST			0x8004
#define READ_DATE_RESPONSE			0x8005
#define WRITE_DATE_REQUEST			0x8006
#define DEBIT_IAM_REQUEST           0x8007
#define EXTERNAL_DISPLAY_REQUEST	0x8009
#define AMOUNT_ENTRY_REQUEST   	    0x8010
#define AMOUNT_ENTRY_RESPONSE  	    0x8011
#define EXTERNAL_DISPLAY_RESULT		0x800A
#define SEQ_START					0x800B
#define SEQ_STOP					0x800C
#define CARD_ACCEPTED				0x8100
#define CARD_UNKNOWN				0x8101
#define CARD_REMOVED				0x8102
#define CARD_STILL_IN_READER		0x8103
#define PME_PROCESSED      		    0x9100




/*! @brief Gives a mailbox to a task.
* @param task_id : id of the task with the new mailbox
* @return 
* - 1 : Creation of the task mailbox is done
* - 0 : Creation of the task mailbox failed
*       - Memory allocation ressources
* @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 3) if function does not exist
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int Register_Mailbox_User (unsigned char task_id);



/*! @brief Allows a task to send a message to the mailbox of another task.
* @param msg : pointer to structure S_MESSAGE_IAM
* @return 
* - 1 : Message sent to the mailbox is done 
* - 0 : Message sent to the mailbox failed
*       - mailbox full (Maximum is 60 messages)
*       - mailbox does not exist
* @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 0) if function does not exist
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int Send_Message (S_MESSAGE_IAM *msg);

/*! @brief Allows a task to read the messages of its mailbox.
* @param msg : pointer to structure S_MESSAGE_IAM
* @param timeout : awaiting time of message
* @return 
* - 1 : At least one message is present inside the mailbox  
* - 0 : The mailbox is empty
* @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 1) if function does not exist
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int Read_Message (S_MESSAGE_IAM *msg, int timeout);


/*! @brief allows an application to verify the message destination
* @param num_appli : application number
* @param msg : pointer to structure S_MESSAGE_IAM
* @return 
* - 1 : Right destination
* - 0 : Wrong destination
* @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 2) if function does not exist
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int SQ_Is_Message_For_Me(NO_SEGMENT num_appli, S_MESSAGE_IAM *msg);

/*! @brief Allows a task to send a message to the all applications
 * @param message : Message type
 * @param length  : length of data
 * @param data    : data
 * @return 
 * - 1 : Message sent to the MANAGER mailbox is done 
 * - 0 : Message sent to the MANAGER mailbox failed
 *       - mailbox full (Maximum is 60 messages)
 * @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 5) if function does not exist
 *
 * @note 
 *  Send message to all applications that implement MESSAGE_RECEIVED
 *  The message is sent when M2OS returns to idle state
 *  Hight level function to replace the generic SendMessage() function
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int SendToAllApplication(unsigned short message,unsigned short length,unsigned char *data);

/*! @brief Allows a task to send a message to an application
 * @param applicationtype : application type
 * @param message         : Message type
 * @param length          : length of data
 * @param data            : data
 * @return 
 * - 1 : Message sent to the MANAGER mailbox is done 
 * - 0 : Message sent to the MANAGER mailbox failed
 *       - mailbox full (Maximum is 60 messages)
 * @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 6) if function does not exist
 *
 * @note 
 *  Send message to application
 *  The message is sent when M2OS returns to idle state
 *  Hight level function to replace the generic SendMessage() function
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int SendToApplication(int applicationtype,unsigned short message,unsigned short length,unsigned char *data);

/*! @brief Allows a task to send a message to the IAM task of an application
 * @param applicationtype : application type
 * @param message         : Message type
 * @param length          : length of data
 * @param data            : data
 * @return 
 * - 1 : Message sent to the TASK mailbox is done 
 * - 0 : Message sent to the TASK mailbox failed
 *       - mailbox full (Maximum is 60 messages)
 *       - Task or mailbox does not exist
 * @par exit (EXIT_DLL_IAM_NOT_INITIALIZED + 7) if function does not exist
 *
 * @note 
 *  Iam TASK has been registered by the application with Register_Mailbox_User function
 *  Send message to the iam TASK immediatly
 *  Hight level function to replace the generic SendMessage() function
 *
 * @link KSFAM_IAM Back to top @endlink
*/
extern int SendToTask(int applicationtype,unsigned short message,unsigned short length,unsigned char *data);

/*! @} **/

#endif
#ifdef __cplusplus
}
#endif

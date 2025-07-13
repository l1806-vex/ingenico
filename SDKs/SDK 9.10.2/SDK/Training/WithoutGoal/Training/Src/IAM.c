//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  IAM.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Inter application messaging (IAM):
//       Iam to one application
//       Iam to all applications
//       Iam to itself
//       Iam to task  
//       
//  The USER2 application must be loaded inside the terminal.
//                                                                                       
//  List of routines in file :  
//      TrainingToUser2 : Iam to one application
//      TrainingToAll : Iam to all applications
//      TrainingToItself : Iam to itself
//      TrainingToTask : Iam to task  
//                            
//  File history :
//  120508-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxPrn;      // Peripheral file Keyboard

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//***************************************************************************
#define TRAINING_APPLI_TYPE    0x161
#define USER2_APPLI_TYPE	   0x162

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
#ifdef OLD_IAM
static S_MESSAGE_IAM xMessage;
#endif

//****************************************************************************
//                       void TrainingToUser2 (void)                            
//  This function sends a message to USER2 by passing through Manager.
//  The message is sent to Manager mailbox. Manager retrieves the message then
//  sends an event MESSAGE_RECEIVED to USER2.
//     *** Application Type on 2 bytes (0x0162) ***
//	   receiver => MSB = TaskApplication id, LSB = Application Type USER2 (LSB=0x62)
//	   sender => MSB = Application Type USER2 (MSB=0x01), LSB = 0
//	   type = 0;                     => Default
//     *** Application Type on 1 byte (0x??) ***
//	   receiver => MSB = TaskApplication id, LSB = Application Type USER2 (0x??)
//	   sender => MSB = 0, LSB = Application Type MANAGER (MANAGER_TYPE)
//	   type = 0;                     => Default
//     !!! Attention
//     The sending message starts ONLY if Training returns to MANAGER (Idle state).
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void TrainingToUser2(void) 
{
	// Local variables 
    // ***************
	char tcSnd[256];

    // Inter application messaging in progress
	// ***************************************

	// Send message to USER2 through Manager mailbox
	// =============================================
	memset (tcSnd, 0, sizeof(tcSnd));
    strcpy(tcSnd, "Msg from TRAINING:\n"                                     // Data to send
		          "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?");

#ifdef OLD_IAM
    // Old method using low level function Send_Message()
    memset(xMessage.value, 0x00, sizeof(xMessage.value)); 
    // 2 bytes Application Type (0x0162)
	xMessage.receiver = (TaskApplication*256) + (USER2_APPLI_TYPE & 0x00FF); // MSB = TaskApplication id, LSB = Application Type (LSB=0x62)
    xMessage.sender = (USER2_APPLI_TYPE & 0xFF00);                           // MSB = Application Type (MSB=0x01), LSB = 0
	xMessage.type = 0;                                                       // IAM type = 0
	xMessage.length = strlen(tcSnd);                                         // Message length
	memcpy(xMessage.value, (byte*)tcSnd, xMessage.length);                   // Copy the message

	Send_Message(&xMessage);                                                 // Send message to Manager mailbox
	                                                                         // Manager will call USER 2 with the message (service call: message_received())
#else
    // New method using high level function SendToApplication()
	SendToApplication(USER2_APPLI_TYPE, 0, strlen(tcSnd), (byte*)tcSnd);     // Send message to Manager mailbox
	                                                                         // Manager will call USER 2 with the message (service call: message_received())
#endif
}

//****************************************************************************
//                       void TrainingToAll (void)                            
//  This function sends a message to all applications by passing through Manager.
//  The message is sent to Manager mailbox. Manager retrieves the message then
//  sends an event MESSAGE_RECEIVED to all applications.
//	   receiver => MSB = TaskApplication id, LSB = 0
//	   sender => MSB = 0, LSB = Application Type MANAGER (MANAGER_TYPE)
//	   type = 0;                     => Default
//     !!! Attention
//     The sending message starts ONLY if Training returns to MANAGER (Idle state).
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void TrainingToAll(void) 
{
	// Local variables 
    // ***************
	char tcSnd[256];

    // Inter application messaging in progress
	// ***************************************

	// Send message to all applications through Manager mailbox
	// ========================================================
	memset (tcSnd, 0, sizeof(tcSnd));
    strcpy(tcSnd, "Msg from TRAINING:\n"                              // Data to send
		          "Hello, do you hear me?\n"
			   	  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?");

#ifdef OLD_IAM
    // Old method using low level function Send_Message()
    memset(xMessage.value, 0x00, sizeof(xMessage.value)); 
	xMessage.receiver = (TaskApplication*256);                        // MSG = TaskApplication id, LSB = 0
    xMessage.sender = MANAGER_TYPE;                                   // MSB = 0, LSB = Application Type of Manager
	xMessage.type = 0;                                                // IAM type = 0
	xMessage.length = strlen(tcSnd);                                  // Message length
	memcpy(xMessage.value, (byte*)tcSnd, xMessage.length);            // Copy the message

	Send_Message(&xMessage);                                          // Send message to Manager mailbox
	                                                                  // Manager will call all applications with the message (service call: message_received())
#else
    // New method using high level function SendToAllApplication()
	SendToAllApplication(0, strlen(tcSnd), (byte*)tcSnd);             // Send message to Manager mailbox
	                                                                  // Manager will call all applications with the message (service call: message_received())
#endif
}

//****************************************************************************
//                       void TrainingToItself (void)                            
//  This function sends a message to TRAINING itself by passing through Manager.
//  The message is sent to Manager mailbox. Manager retrieves the message then
//  sends an event MESSAGE_RECEIVED to TRAINING.
//     *** Application Type on 2 bytes (0x0161) ***
//	   receiver => MSB = TaskApplication id, LSB = Application Type TRAINING (LSB=0x61)
//	   sender => MSB = Application Type TRAINING (MSB=0x01), LSB = 0
//	   type = 0;                       => Default
//     *** Application Type on 1 byte (0x??) ***
//	   receiver => MSB = TaskApplication id, LSB = Application Type TRAINING (0x??)
//	   sender => MSB = 0, LSB = Application Type MANAGER (MANAGER_TYPE)
//	   type = 0;                     => Default
//     !!! Attention
//     The sending message starts ONLY if Training returns to MANAGER (Idle state).
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void TrainingToItself(void) 
{
	// Local variables 
    // ***************
	char tcSnd[256];

    // Inter application messaging in progress
	// ***************************************

	// Send message to TRAINING itself through Manager mailbox
	// =======================================================
	memset (tcSnd, 0, sizeof(tcSnd));
    strcpy(tcSnd, "Msg from TRAINING:\n"                                        // Data to send
		          "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?");

#ifdef OLD_IAM
    // Old method using low level function Send_Message()
    memset(xMessage.value, 0x00, sizeof(xMessage.value)); 
    // 2 bytes Application Type (0x0161)
 	xMessage.receiver = (TaskApplication*256) + (TRAINING_APPLI_TYPE & 0x00FF); // MSB = TaskApplication id, LSB = Application Type (0x61)
    xMessage.sender = (TRAINING_APPLI_TYPE & 0xFF00);                           // MSB = Application Type (0x01), LSB = 0
	xMessage.type = 0;                                                          // IAM type = 0
	xMessage.length = strlen(tcSnd);                                            // Message length
	memcpy(xMessage.value, (byte*)tcSnd, xMessage.length);                      // Copy the message

	Send_Message(&xMessage);                                                    // Send message to Manager mailbox
	                                                                            // Manager will call the application itself with the message (service call: message_received())
#else
    // New method using high level function SendToApplication()
	SendToApplication(TRAINING_APPLI_TYPE, 0, strlen(tcSnd), (byte*)tcSnd);     // Send message to Manager mailbox
	                                                                            // Manager will call the application itself with the message (service call: message_received())
#endif
}

//****************************************************************************
//                  void TrainingToTask (void)                            
//  This function sends a message to a task by passing through Manager.
//  The message is sent to the Task mailbox previously created by Register_Mailbox_User().
//  Then an event MSG is raised inside the task by using ttestall().
//	   receiver => MSB = TaskIam1 id, LSB = Application type MANAGER (MANAGER_TYPE)
//	   sender => MSB = TaskApplication id, LSB = 0
//	   type = 0;                       => Default
//     !!! Attention
//     The sending message starts IMMEDIATLY.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void TrainingToTask(void) 
{
	// Local variables 
    // ***************
	char tcSnd[256];

    // Inter application messaging in progress
	// ***************************************

	// Send message to a task through Manager mailbox
	// ==============================================
	memset (tcSnd, 0, sizeof(tcSnd));
    strcpy(tcSnd, "Msg from TRAINING:\n"                                 // Data to send
		          "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?");

#ifdef OLD_IAM
    // Old method using low level function Send_Message()
    memset(xMessage.value, 0x00, sizeof(xMessage.value)); 
	xMessage.receiver = (TaskIam1*256)+ MANAGER_TYPE;                    // MSB = TaskIam1 id (see Register_Mailbox_User from Task2), LSB = Application Type Manager
    xMessage.sender = (TaskApplication*256);                             // MSB = TaskApplication Id, LSB = 0
	xMessage.type = 0;                                                   // IAM type = 0
	xMessage.length = strlen(tcSnd);                                     // Message length
	memcpy(xMessage.value, (byte*)tcSnd, xMessage.length);               // Copy the message
	
	Send_Message(&xMessage);                                             // Send message to Task2 mailbox

#else
	// New method using high level function SendToTask()
	SendToTask(TRAINING_APPLI_TYPE, 0, strlen(tcSnd), (byte*)tcSnd);     // Send message to Task2 mailbox
#endif
}

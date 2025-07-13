//****************************************************************************
//       INGENICO                                TDS 5.7.3                   
//============================================================================
//       FILE  TASK.C                           (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                        
//                                                                          
//  Purpose :                                                               
//  Task management:
//         Show how to implement task, event and semaphore creation and the way
//         to send messages between 2 tasks.
//                                                                            
//  List of routines in file :  
//      Task : Task and Semaphore demo.                                            
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
#define PRTW  24
#define DSPW  16

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
static char bufM[DSPW+1];
static char bufS[DSPW+1];

static word MainTaskNbr;
static t_topstack *hTsk=NULL;
static word semNbr, boxNbr;
static doubleword mail1=0; 
static doubleword mail2=0;

//****************************************************************************
//                          void play (char beg)                            
//  This function animates main and second tasks.      
//  This function has  parameters.
//       beg (I-) : Start character for animation    
//  This function has no return value.                                      
//****************************************************************************

static void play(char beg) 
{
	// Local variables 
    // ***************
    char buf[DSPW + 1];
    byte ucLine, ucColumn;
    word idx;

	// Play tasks under animation
	// **************************
    memset(buf, 0, sizeof(buf));
	memset(bufM, 0, sizeof(bufM));
	memset(bufS, 0, sizeof(bufS));
    for (idx=0; idx<DSPW*10; idx++)
	{
        buf[idx%DSPW] = idx/DSPW+beg;        
        
		if((beg=='A') | (beg=='0'))
		{
			if (beg=='A')
				strcpy(bufM, buf);
			else
				strcpy(bufS, buf);
			ucLine=1; ucColumn=0;
			_DrawExtendedString(ucColumn*8, (ucLine*16)+2, bufM, _OFF_, _POLICE8x12_, _NORMALE_);
			ucLine=3; ucColumn=0;
			_DrawExtendedString(ucColumn*8, (ucLine*16)+2, bufS, _OFF_, _POLICE8x12_, _NORMALE_);
		}
		else 
			strcpy(bufS, buf);

		PaintGraphics();
        ttestall (0, 4);
    }
}

//****************************************************************************
//                          word SecondTask (void)                            
//  This function waits:
//    - for event 0 from main task to start animation.
//    - for a message from main task and sends a response.   
//       WaitEvents() : Wait for a list of events (here only event 0)   
//       TestReceive() : Retrieve a message from the mailbox
//       Send() : Send a message to the mailbox
//       V() : Semaphore release
//       kill() : kill task
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

static word SecondTask(void) 
{
	// Local variables 
    // ***************
    int ret;
	doubleword msg;
	tStatus sta;

    // Task animation and mailbox management
	// *************************************
	
	// Signal an event to Main task
	// ============================
	sta=SignalEvent(MainTaskNbr, 15); CHECK(sta==cOK, lblKO);          // Send event 15 (0..31) to main task before starting animation
	
    play('a');                                                         // Second task under animation

	// Wait a message from a mail box
	// ==============================
	ret=Receive(boxNbr, &msg, 0);  CHECK(ret==0, lblKO);               // Message retrieves from main task
	if (msg == 1024)
		mail1=msg;                                                     // Save message

	play('0');                                                         // Second task under animation

	// Send a message to a mail box
	// ============================
	msg=2048;
	ret=Send(boxNbr, msg); CHECK(ret==0, lblKO);                       // Message sent to main task

	// Errors treatment 
    // ****************
lblKO:
    DisplayMedium(2, 0, "SecondTask Kill!");                           // Display second task deleted
	DisplayMedium(3, 0, "                ");
	V(semNbr);                                                         // Semaphore release
	kill(hTsk, "");                                                    // Delete second task
	return 0;
}


//****************************************************************************
//                          void Task (void)                            
//  This function forks second task and sends :
//     - an event to it for starting animation.
//     - a message to it and waits for a response.
//       fork() : Fork a second task
//       SignalEvent() : Signal an event to a task
//       Send() : Send a message to the mailbox
//       P() : Semaphore acquire
//       TestReceive() : Retrieve a message from the mailbox
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Task(void) 
{
	// Local variables 
    // ***************
	byte dum1;
	doubleword msg;
	int dum2=0;
	tStatus sta; 
	tEventList eve;	
    int ret;

	memset(bufM, 0, sizeof(bufM));
	memset(bufS, 0, sizeof(bufS));
        
	// Task animation, semaphore and mailbox management
	// ************************************************
    _clrscr();                                                         // Clear screen
	DisplayMedium(0, 0, "MainTask Run... ");                           // Display main task running

	// Init. context
	// =============
	boxNbr=GetMailboxUser();                                           // Get a mailbox number
	semNbr=GetSemaphoreUser();                                         // Get a semaphore number
    MainTaskNbr=CurrentTask();                                         // Get the main task number

	// Task2 creation
	// ==============
    DisplayMedium(2, 0, "SecondTask Run..");                           // Display second task running
    hTsk=fork(SecondTask, &dum1, dum2); CHECK(hTsk!=NULL, lblKO);      // Fork second task
	
	// Wait an event from Second task
	// ==============================
    sta=WaitEvents (0x00008000, 0, &eve); CHECK(sta==cOK, lblKO);      // Wait event 15 (mask bit 1..32) from second task before starting animation
    sta=ClearEvents (0x00008000); CHECK(sta==cOK, lblKO);              // The event bit MUST be cleared when using "WaitEvents"
    //ttestall (0x00008000, 0);                                        // Same effect as "WaitEvents", the event bit is cleared by "ttestall"

    play('A');                                                         // Main task under animation

    // Send a message to a mail box
	// ============================
	DisplayMedium(0, 0, "MainTask Wait!  ");                           // Display main task waiting
    msg=1024;
	ret=Send(boxNbr, msg); CHECK(ret==0, lblKO);                       // Message sent to second task
	
	// Main task is in waiting state until the second task calls Semaphore release
	// ===========================================================================
    buzzer(10);
	ret=P(semNbr, 0); CHECK(ret==0, lblKO);                            // Semaphore acquire infinite timeout

    DisplayMedium(0, 0, "MainTask Restart");                           // Display main task restarting
    buzzer(10);

    // Main task restarts, second task is killed
	// =========================================
    play('A');                                                         // Main task under animation

	// Wait a message from a mail box
	// ==============================
	ret=Receive (boxNbr, &msg, 0);  CHECK(ret==0, lblKO);              // Message retrieves from Task2
	if (msg == 2048)
		mail2=msg;

	DisplayMedium(0, 0, "MainTask End    ");                           // Display main task ending
    buzzer(10);

	// Print messages  
	// ==============
    ret=pprintf("\x1b""E""          Task Demo\n\n"                     // Print demo in progress
		        "\x1b""F"); CHECK(ret>=0, lblKO);      
	ret=pprintf("Main Task to Second Task\n"                           // Print message task 2
		        "Message received : %ld\n\n", mail1); CHECK(ret>=0, lblKO);                 
    ret=pprintf("Second Task to Main Task\n"                           // Print message main task
		        "Message received : %ld\n", mail2); CHECK(ret>=0, lblKO); 
	ret=pprintf("\n\n\n\n\n\n"); CHECK(ret>=0, lblKO);

    ttestall (0, 5*100); 
    
	goto lblEnd;


	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                         // Clear screen
	DisplayMedium(0, 0, "Processing Error");                           // Oops! error
    ttestall(0,5*100);                                                 // Delay 5s 
lblEnd:
	ttestall(PRINTER, 10);   

    FreeMailboxUser(boxNbr);                                           // Release the mailbox number
	FreeSemaphoreUser(semNbr);                                         // Release the semaphore number
}

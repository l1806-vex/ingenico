//****************************************************************************
//       INGENICO                                INGEDEV 7
//============================================================================
//       FILE  TASK.C                             (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                        
//                                                                          
//  Purpose :                                                               
//                          *** Task management ***
//  How to implement task, event and semaphore creation and the way to send
//  messages between 2 tasks.
//                                                                            
//  List of routines in file :  
//      Task : Task and Semaphore demo.                                            
//                            
//  File history :
//  071312-BK : File created
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
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define PRTW  24
#define DSPW  16

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Task screen (Goal)
// ====================================
static const ST_DSP_LINE txTask[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_RED,   100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 2, 0, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,  100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 2, 0, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

static T_GL_HWIDGET xScreen=NULL; // Screen handle

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

static char bufM[DSPW+1];
static char bufS[DSPW+1];

static word MainTaskNbr;       // Task number of the current task
static t_topstack *hTsk=NULL;  // Handle of the task
static word semNbr, boxNbr;    // Semaphore number and mailbox number
static doubleword mail1=0;     // Mail1 (4 bytes)
static doubleword mail2=0;     // Mail2 (4 bytes)

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
    char buf[DSPW+1];
    word idx;

	// Play tasks under animation
	// **************************
    memset(buf, 0, sizeof(buf));
    for (idx=0; idx<DSPW*10; idx++)
	{
    	// Prepare line1 and line3 to display
    	// ==================================
        buf[idx%DSPW] = idx/DSPW+beg;        
        
		if((beg=='A') || (beg=='0'))
		{
			if (beg=='A')
				strcpy(bufM, buf);    // First line main task
			else
				strcpy(bufS, buf);    // Third line second task
			GoalDspLine(xScreen, 1, bufM, &txTask[1], 0, false);
			GoalDspLine(xScreen, 3, bufS, &txTask[3], 0, false);
		}
		else 
			strcpy(bufS, buf);        // Third line second task

		// Refresh screen
		// ==============
		GoalRefreshScreen(xScreen);   // Refresh screen
		if (IsColorDisplay())
			ttestall(0, 1);
		else
			ttestall(0, 4);
	}
}

//****************************************************************************
//                          word SecondTask (void)                            
//  This function waits:
//  For event 15 from main task to start animation.
//  For a message from main task and sends a response.
//   - WaitEvents() : Wait for a list of events (here only event 15)
//   - TestReceive() : Retrieve a message from the mailbox
//   - Send() : Send a message to the mailbox
//   - V() : Semaphore release
//   - kill() : kill task
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
	sta=SignalEvent(MainTaskNbr, 15); // Send event 15 (0..31) to main task before starting animation
	CHECK(sta==cOK, lblKO);
	
    play('a');                        // Second task under animation

	// Wait a message from a mail box
	// ==============================
	ret=Receive(boxNbr, &msg, 0);
	CHECK(ret==0, lblKO);             // Message retrieves from main task
	if (msg == 1024)
		mail1=msg;                    // Save message

	play('0');                        // Second task under animation

	// Send a message to a mail box
	// ============================
	msg=2048;
	ret=Send(boxNbr, msg);            // Message sent to main task
	CHECK(ret==0, lblKO);

	// Errors treatment 
    // ****************
lblKO:
	GoalDspLine(xScreen, 2, "SecondTask Killed !", &txTask[2], 0, true);
	memset(bufS, 0, sizeof(bufS));    // Delete second task

	V(semNbr);                        // Semaphore release
	kill(hTsk, "");                   // Second task killed
	return 0;
}


//****************************************************************************
//                          void Task (void)                            
//  This function forks second task and sends :
//  An event to it for starting animation.
//  A message to it and waits for a response.
//   - fork() : Fork a second task
//   - SignalEvent() : Signal an event to a task
//   - Send() : Send a message to the mailbox
//   - P() : Semaphore acquire
//   - TestReceive() : Retrieve a message from the mailbox
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Task(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
	byte dum1;
	doubleword msg;
	int dum2=0;
	tStatus sta;
	tEventList eve;
	char tcBuffer[50+1];
	byte p; // Printer line index
    int iRet;

	// Task animation, semaphore and mailbox management
	// ************************************************
	xScreen = GoalCreateScreen(xGoal, txTask, NUMBER_OF_LINES(txTask), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                             // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "MainTask Running... ", &txTask[0], 0, false);
	CHECK(iRet>=0, lblKO);

	// Init. context
	// =============
	memset(bufM, 0, sizeof(bufM));
	memset(bufS, 0, sizeof(bufS));
	boxNbr=GetMailboxUser();                                 // Get a mailbox number
	semNbr=GetSemaphoreUser();                               // Get a semaphore number
    MainTaskNbr=CurrentTask();                               // Get the main task number

	// Task2 creation
	// ==============
	iRet = GoalDspLine(xScreen, 2, "SecondTask Running...", &txTask[2], 0, false);
	CHECK(iRet>=0, lblKO);

	hTsk=fork(SecondTask, &dum1, dum2);                      // Fork second task
	CHECK(hTsk!=NULL, lblKO);
	
	// Wait an event from Second task
	// ==============================
    sta=WaitEvents (0x00008000, 0, &eve);                    // Wait event 15 (mask bit 1..32) from second task before starting animation
    CHECK(sta==cOK, lblKO);
    sta=ClearEvents (0x00008000);                            // The event bit MUST be cleared when using "WaitEvents"
    CHECK(sta==cOK, lblKO);
    // ttestall (0x00008000, 0);                             // Same effect as "WaitEvents", the event bit is cleared by "ttestall"

    play('A');                                               // Main task under animation

    // Send a message to a mail box
	// ============================
    msg=1024;
	iRet=Send(boxNbr, msg); CHECK(iRet==0, lblKO);           // Message sent to second task
	iRet = GoalDspLine(xScreen, 0, "MainTask Waits !", &txTask[0], 0, true);
	CHECK(iRet>=0, lblKO);


	// Main task is in waiting state until the second task calls Semaphore release
	// ===========================================================================
    buzzer(10);
    iRet=P(semNbr, 0);                                       // Semaphore acquire infinite timeout
    CHECK(iRet==0, lblKO);

    buzzer(10);
	iRet = GoalDspLine(xScreen, 0, "MainTask Restarts...", &txTask[0], 0, false);
	CHECK(iRet>=0, lblKO);


    // Main task restarts, second task is killed
	// =========================================
    play('A');                                               // Main task under animation

	// Wait a message from a mail box
	// ==============================
	iRet=Receive (boxNbr, &msg, 0);                          // Message retrieves from Task2
	CHECK(iRet==0, lblKO);
	if (msg == 2048)
		mail2=msg;

	buzzer(10);
	iRet = GoalDspLine(xScreen, 0, "MainTask Ended", &txTask[0], 3*1000, true);
	CHECK(iRet>=0, lblKO);

	// Print messages  
	// ==============
	p=0;
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8); // Create document
	CHECK(xDocument!=NULL, lblKO);

	xLine = xPrinter;                                        // Build document (Demo, Msg task2, Msg main task)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Task Demo", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;
	iRet = GoalPrnLine(xDocument, p++, "Main Task to Second Task", &xLine);
	CHECK(iRet>=0, lblKO);
    sprintf(tcBuffer, "Message received : %d\n\n", mail1);
	iRet = GoalPrnLine(xDocument, p++, tcBuffer, &xLine);   // Message task 2
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "Second Task to Main Task", &xLine);
	CHECK(iRet>=0, lblKO);
    sprintf(tcBuffer, "Message received : %d\n\n\n\n\n", mail2);
	iRet = GoalPrnLine(xDocument, p++, tcBuffer, &xLine);   // Message main task
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);
	CHECK(iRet>=0, lblKO);

	// Display messages exchanged
	// ==========================
	iRet = GoalDspLine(xScreen, 0, "MainTask to SecondTask", &txTask[0], 0, false);
	CHECK(iRet>=0, lblKO);
	sprintf(tcBuffer, "Message received : %d", mail1);
	iRet = GoalDspLine(xScreen, 1, tcBuffer, &txTask[1], 0, false);
	CHECK(iRet>=0, lblKO);                                  // Msg=1024 received into second task
	iRet = GoalDspLine(xScreen, 2, "SecondTask to MainTask", &txTask[2], 0, false);
	CHECK(iRet>=0, lblKO);
	sprintf(tcBuffer, "Message received : %d", mail2);
	iRet = GoalDspLine(xScreen, 3, tcBuffer, &txTask[3], 5*1000, true);
	CHECK(iRet>=0, lblKO);                                  // Msg=2048 received into main task

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                      // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	FreeMailboxUser(boxNbr);                                // Release the mailbox number
	FreeSemaphoreUser(semNbr);                              // Release the semaphore number

	if (xScreen)
		GoalDestroyScreen(&xScreen);                        // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);                    // Destroy document
}


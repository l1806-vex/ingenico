//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  TIMER.C                            (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                          *** Timer management ***
//  How to start, get and stop a timer.
//                                                                            
//  List of routines in file :  
//      TimerStart : Start a timer number.
//      TimerGet : Return the state of a timer number.
//      TimerStop : Stop a timer number.
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
#define TMR_NBR 4

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Counter screen (Goal)
// =======================================
static const ST_DSP_LINE txCounter[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,   40, FALSE, {0, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, TRUE, 60, FALSE, {0, 4, 0, 4}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_RED,   GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

typedef struct 
{
    unsigned long ulHi;    // Most significant 32bits of the timer value. 
    unsigned long ulLo;    // Least significant 32bits of the timer value.
} st_timer;

static st_timer txTimer[TMR_NBR];

//****************************************************************************
//             int TimerStart (byte ucTimerNbr, int iDelay)                            
//  This function starts a timer number for iDelay/100 seconds. 
//  After starting a timer a function TimerGet() should be called to know
//  whether it is over or not.
//  The timer should be over after iDelay/100 seconds.
//   - get_tick_counter() : Return number of elapsed ticks since startup(1tick=10ms).
//  This function has parameters.
//     ucTimerNbr (I-) : Timer number 0..3
//     iDelay (I-) : Initial timer value in hundredth of second
//  This function has return value.
//     >=0 : TimerStart done
//     <0  : TimerStart failed
//****************************************************************************

int TimerStart(byte ucTimerNbr, int iDelay)
{
	// Local variables 
    // ***************
    st_timer xTimer;

    // Start timer in progress
    // ***********************
    CHECK(ucTimerNbr<TMR_NBR, lblKO);

    // Get the current timer value
    // ===========================
    xTimer.ulHi = 0;
    xTimer.ulLo = get_tick_counter();    // In 10ms ticks.

    // Set the timer to a 'period' into the future
    // ===========================================
    xTimer.ulLo += (unsigned long) iDelay;

    // If an overflow occurs, adjust the high tick counter
    // ===================================================
    if(xTimer.ulLo < (unsigned long) iDelay)
        xTimer.ulHi++;

    // Assign it to the proper timer
    // =============================
    txTimer[ucTimerNbr].ulHi = xTimer.ulHi;
    txTimer[ucTimerNbr].ulLo = xTimer.ulLo;

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
    iDelay=-1;
lblEnd:
    return iDelay; 
}

//****************************************************************************
//             int TimerGet (byte ucTimerNbr)                            
//  This function returns the state of the timer number. 
//   - get_tick_counter() : Return number of elapsed ticks since startup(1tick=10ms).
//  This function has parameters.
//     ucTimerNbr (I-) : Timer number 0..3
//  This function has return value.
//     >=0 : The number of centiseconds rest
//     <0  : TimerGet failed
//****************************************************************************

int TimerGet(byte ucTimerNbr)
{
	// Local variables 
    // ***************
    unsigned long ulHi, ulLo;
    st_timer xTimer;
    int iRet;
    
    // Get timer in progress
    // *********************
    CHECK(ucTimerNbr<TMR_NBR, lblKO);

    // Get the new timer value 
    // =======================
    xTimer.ulHi = txTimer[ucTimerNbr].ulHi;
    xTimer.ulLo = txTimer[ucTimerNbr].ulLo;

    ulHi = 0;
    ulLo = get_tick_counter();    // In 10ms ticks.

    if(ulLo < xTimer.ulLo)
        iRet = xTimer.ulLo - ulLo;
    else
    	iRet = 0;
    
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
    iRet=-1;
lblEnd:
    return iRet; 
}
          
//****************************************************************************
//               int TimerStop (byte ucTimerNbr)                            
//  This function should be called when the timer number is no more needed. 
//  This function has parameters.
//     ucTimerNbr (I-) : Timer number 0..3
//  This function has return value.
//     >=0 : TimerStop done
//     <0  : TimerStop failed
//****************************************************************************

int TimerStop(byte ucTimerNbr)
{
	// Local variables 
    // ***************
    int iRet;
	
	// Stop timer in progress
	// **********************
    CHECK(ucTimerNbr<TMR_NBR, lblKO);
    
    txTimer[ucTimerNbr].ulHi = 0;
    txTimer[ucTimerNbr].ulLo = 0;
    
    iRet=0;
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
    iRet=-1;
lblEnd:
    return iRet; 
}

//****************************************************************************
//                            void Timer(void)                            
//  This function manages a timer. A timer counts hundredths of second. 
//  When the timer expires after 15s, the terminal reboots.
//  This function has no parameters.
//  This function has no return value.
//****************************************************************************

void Timer(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	char tcDisplay[16+1];
    int iRet, iRet0;
    
    // Timer demo in progress
    // **********************
	xScreen = GoalCreateScreen(xGoal, txCounter, NUMBER_OF_LINES(txCounter), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);       // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

    iRet = GoalDspLine(xScreen, 0, "Expiration Time", &txCounter[0], 0, false);
	CHECK(iRet>=0, lblKO);

    iRet = TimerStart(0, 15*100);      // Timer0 starts to 15s
    CHECK(iRet>=0, lblKO);
    while ((iRet0=TimerGet(0)) > 0)    // Check Timer0
    {
    	CHECK(iRet0>=0, lblKO);
    	
        // Display Remaining Time
    	// ======================
        sprintf(tcDisplay, "%2d.%02d Sec", iRet0/100, iRet0%100);
    	iRet = GoalDspLine(xScreen, 1, tcDisplay, &txCounter[1], 150, true);
		CHECK(iRet>=0, lblKO);
		CHECK(iRet!=GL_KEY_CANCEL, lblEnd);    // Exit on cancel key
    }

	iRet = GoalDspLine(xScreen, 1, " 0.00 Sec", &txCounter[1], 1*1000, true);
	CHECK(iRet>=0, lblKO);
    buzzer(10);
	iRet = GoalDspLine(xScreen, 2, "Timer expired !!!", &txCounter[2], 5*1000, true);
	CHECK(iRet>=0, lblKO);

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    TimerStop(0);                      // Stop Timer0
    TimerStop(1);                      // Stop Timer1

	if (xScreen)
		GoalDestroyScreen(&xScreen);   // Destroy screen
}

	

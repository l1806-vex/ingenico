//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  TIMER.C                          (Copyright INGENICO 2010)   
//============================================================================
//  Created :       02-February-2010     Kassovic                                 
//  Last modified : 02-February-2010     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Timer management:
//      Show how to start, get and stop a timer.  
//                                                                            
//  List of routines in file :  
//      TimerStart : Start a timer number.
//      TimerGet : Return the state of a timer number.
//      TimerStop : Stop a timer number.
//                            
//  File history :
//  020110-BK : File created 
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
    /* */

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
//       get_tick_counter() : Return number of elapsed ticks since startup(1tick=10ms).
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
//       get_tick_counter() : Return number of elapsed ticks since startup(1tick=10ms).
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
	char tcDisplay[16+1];
    int iRet, iRet0;
    
    // Timer demo in progress
    // **********************
    iRet = TimerStart(0, 15*100); CHECK(iRet>=0, lblKO);  // Timer0 starts to 15s
    while ((iRet0=TimerGet(0)) > 0)                       // Check Timer0
    {
    	CHECK(iRet0>=0, lblKO);
    	
        // Display Remaining Time
    	// ======================
    	_clrscr();                                        // Clear screen
        sprintf(tcDisplay, "Exp in %2d.%02d Sec", iRet0/100, iRet0%100);
        DisplayMedium(0, 0, tcDisplay);
        
        // Wait 200ms = ttestall(0, 20)
        // ============================
        iRet = TimerStart(1, 20); CHECK(iRet>=0, lblKO);  // Timer1 starts to 200ms
        while (TimerGet(1) > 0)                           // Check Timer1
        { 
        	/*NOP*/; 
        }
    }
    
    _clrscr();                                            // Clear screen
    DisplayMedium(0, 0, "Timer expired !!");              // Timer expired
    buzzer(10);
    ttestall(0, 3*100);
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
    _clrscr();                                            // Clear screen
    DisplayMedium(0, 0, "Processing Error");              // Oops! error
    ttestall(0, 5*100);                                   // Delay 5s 
lblEnd:
    TimerStop(0);
    TimerStop(1);
}

	

// $Id: GL_Timer.h,v 1.1.2.15 2012/01/16 08:12:56 rbertholet Exp $
// This module provide timer management
#ifndef GL_Timer_h_INCLUDED
#define GL_Timer_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
	
/**
@addtogroup GL_Timer
@{
@addtogroup GL_TimerDoc Documentation
@{

The timer class provides repetitive timers.

Below is a list of specific functions to this class :
	- @ref GL_Timer_Create : Creating a timer
	- @ref GL_Timer_Start : Starts a timer
	- @ref GL_Timer_Stop : Stops a timer
	- @ref GL_Timer_SetInterval : Sets the timeout interval
	- @ref GL_Timer_GetInterval : Gets the timeout interval

Methods inherited from class widget :
	- @ref GL_Widget_Destroy

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with a timer.

	@include GL_SampleTimer.c
@}
*/

/*<ALL>
	Extension("TIMER",           "WIDGET",     "Repetitive timers",
		Bool("enabled",                        "true indicates that the timer is automaticaly started at the creation, false indicates that is not started"),
		Integer("interval",                    "Interval of timer in milliseconds"),
		),
</ALL>*/

/** Creating a timer
@param window handle on the window
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Timer_Create(T_GL_HWIDGET window) GL_EXCEPTION;

/** Starts a timer
@param timer the timer handle */
void GL_Timer_Start(T_GL_HWIDGET timer) GL_EXCEPTION;

/** Stops a timer
@param timer the timer handle */
void GL_Timer_Stop(T_GL_HWIDGET timer) GL_EXCEPTION;

/** Sets the timeout interval
@param timer the timer handle 
@param interval interval in milliseconds */
void GL_Timer_SetInterval(T_GL_HWIDGET timer, ulong interval) GL_EXCEPTION;

/** Gets the timeout interval
@param timer the timer handle 
@return interval interval in milliseconds */
ulong GL_Timer_GetInterval(T_GL_HWIDGET timer) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif // GL_Timer_h_INCLUDED

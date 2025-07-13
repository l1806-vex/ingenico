/*! @addtogroup KSFAM_M2OS
	* @{
**/

#ifndef TIMER_H
#define TIMER_H

#define MAX_TIMER	10

/*! @brief Function to execute when the ontime event of a timer occurs.*/
typedef unsigned short (*MYTIMER) (void);

/*! @brief Defines a timer (delay, delay number, period, on time etc.)*/
typedef struct
{
	unsigned short DelayNumber;						/*!< Number of delay*/
	unsigned long  FirstDelay;						/*!< first delay (may be different).*/
	unsigned long  Period;								/*!< period (after the first delay).*/
  MYTIMER        FunctionPtr;				 		/*!< function to call when on time event occurs.*/
} StructTimer;

/*
======================================================================
			      			 Time Manager
 					SEQ_Del_User1 : Keyboard timer   
 					SEQ_Del_User2 : Timer supervision of the card  
 					SEQ_Del_User3 : Timer modem layer 
 					SEQ_Del_User4 : Timer modem layer 
					SEQ_Del_User5 : Layer CB2A     
 					SEQ_Del_User6 : Timer stain Pinpad  
 					SEQ_Del_User7 : Timer Protocol PSS    
 					SEQ_Del_User8 : Timer banner   			
======================================================================
*/
#define SEQ_Del_User1 1000
#define SEQ_Del_User2 1001
#define SEQ_Del_User3 1002
#define SEQ_Del_User4 1003
#define SEQ_Del_User5 1004
#define SEQ_Del_User6 1005
#define SEQ_Del_User7 1006
#define SEQ_Del_User8 1007
#define SEQ_Del_User9 1008

#endif

/*! @} **/

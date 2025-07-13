/*******************************************************************************
 * Beep.c
 ******************************************************************************/
 
#include "sdk30.h"

/**
 * One Beep
 */
void OneBeep(void)
{
	buzzer(10);
	ttestall(0,100);
}

/**
 * Many Beep
 */
int ManyBeep(int n)
{
	int i;

	for (i=0; i<n; i++)
	{
		buzzer(10);
		ttestall(0,100);
	}
	return(n*2);                      //return twice the number passed
}



/*******************************************************************************
 * Beep.c
 ******************************************************************************/
 
#include "sdk30.h"

//for component min size
const char dummy[8*1024] = {0,1,2,3,4,5}; // this is just to insure that the size of the component will be more than 1kB (in .zip None mockup watch .LDF),
                                          // otherwise it will not be loaded by the system

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

/**
 * Init Var
 */
void initvar(void)
{
}




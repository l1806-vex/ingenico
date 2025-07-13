/** \file
 * TELIUM functions to manage the state processing
 */

// Includes
//-------------------------------------------------------------------
#include <SDK30.H>

#include "Utilities.h"

static int currentState;

void stateNext(void)
{
    trcS("stateNext\n");
    currentState++;
    trcFN("state = %d\n",currentState);
}

void statePrev(void)
{
    trcS("statePrev\n");
    currentState--;
    trcFN("state = %d\n",currentState);
}

void stateSet(int nextState)
{
    trcS("statePrev\n");
    currentState = nextState;
    trcFN("state = %d\n",currentState);
}

int stateGet(void)
{
    trcS("stateGet\n");
    trcFN("state = %d\n",currentState);
    return currentState;

}


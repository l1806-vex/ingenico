#include "basearm.h"
#include "Goal.h"

#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
#define NUMBER_OF_ITEMS(a) (sizeof(a)/sizeof((a)[0]))
#define NUMBER_OF_LINES(a) (sizeof(a)/sizeof((a)[0]))

#define WAIT_RESPONSE  101

#define PIXEL_BOTTOM   40

// Telium
int OpenPeripherals(void);
void ClosePeripherals(void);
void ResetPeripherals(unsigned int uiEvents);
const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim);
void IsoError(int iSta, char *pcTrk);

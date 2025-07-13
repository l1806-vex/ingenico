#include "basearm.h"
#include "Goal.h"

#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
#define NUMBER_OF_ITEMS(a) (sizeof(a)/sizeof((a)[0]))
#define NUMBER_OF_LINES(a) (sizeof(a)/sizeof((a)[0]))

#define CASHREG_APPLI_TYPE      0x163

void ForkListener(void);
byte CheckRestartTransaction(void);
int Svc100Transaction(char* pcMessage);

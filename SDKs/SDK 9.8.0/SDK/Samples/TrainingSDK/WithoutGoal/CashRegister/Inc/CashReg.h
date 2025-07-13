#include "basearm.h"

#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
#define NUMBER_OF_ITEMS(a) (sizeof(a)/sizeof((a)[0]))

#define CASHREG_APPLI_TYPE      0x163

void ForkListener(void);
byte CheckRestartTransaction(void);
int Svc100Transaction(char* pcMessage);

void DisplaySmall (byte ucLine, byte ucColumn, char *pcText);
void DisplayMedium (byte ucLine, byte ucColumn, char *pcText);
void DisplayLarge (byte ucLine, byte ucColumn, char *pcText);
void DisplayLargeCenter (byte ucLine, char *pcText);
int Display25(byte ucLine, char *pcData , int iLen);
int Print24(char *pcData, int iLen);

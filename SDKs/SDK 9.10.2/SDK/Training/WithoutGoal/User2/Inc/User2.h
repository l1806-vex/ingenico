#include "basearm.h"

#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
#define NUMBER_OF_ITEMS(a) (sizeof(a)/sizeof((a)[0]))

#define WAIT_RESPONSE  101

void DisplaySmall (byte ucLine, byte ucColumn, char *pcText);
void DisplayMedium (byte ucLine, byte ucColumn, char *pcText);
void DisplayLarge (byte ucLine, byte ucColumn, char *pcText);
int Display25(byte ucLine, char *pcData , int iLen);
int Print24(char *pcData , int iLen);
int ShowMenu(const char *pcTitle, int iMenuStyle, int iDefaultItem,
			 int iMaxItems, const char *tpcItems[]);
const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim);
void IsoError(int iSta, char *pcTrk);

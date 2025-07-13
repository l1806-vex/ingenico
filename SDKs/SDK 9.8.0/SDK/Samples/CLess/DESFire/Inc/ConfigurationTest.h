//! \file
//! Module that manages a database storage.


//// Defines ////////////////////////////////////////////////////

#define CUC30_ALIGN_LEFT				(1)
#define CUC30_ALIGN_CENTER				(2)
#define CUC30_ALIGN_RIGHT				(3)
#define C30_CHENILLARD_TIME				15

//// Function declarations //////////////////////////////////////

void CUC30_DisplayText (const char* szText, int nAlignment);
void DisplayTest (int nTest);
void BuzzerTest (int nTest);
void LedsTest (int nTest);
void BacklightTest (int nTest);
void InfoTest (void);
void ResetTest (void);
void CheckPresence (void);

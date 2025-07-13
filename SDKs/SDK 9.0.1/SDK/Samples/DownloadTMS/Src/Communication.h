/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define __TCP_TEST_LOOP_HTTP	1
#define __TCP_TEST_ECHO			2
#define __TCP_TEST_RECEIVE_100K	3

//// Global variables ///////////////////////////////////////////
//extern Word g_nCallingTaskNumber;

//// Static function definitions ////////////////////////////////

//// Functions //////////////////////////////////////////////////
int PerformConnectionGPRS( char *szAPN, char *szLogin, char *szPassword );

/*
int PerformDisconnectionPPP();

int PerformConnectionTCP( char *szHostname, int nPort, int nTest );

int PerformConnectionGSM( char *szPhoneNumber,
						  int nMode, int bRLP );

*/
/*
void InitCommunication(void);
void InitDefaultConfig(void);
void DoCommunication(void);
*/


#ifndef _INC_SIMUMAIN		// For Multiple Include ...
#define _INC_SIMUMAIN


////////////////////////////////////////////////////////////
// Exit Code 
////////////////////////////////////////////////////////////
#define	KPB_NO_ERROR		1	// No error / normal 


//
// Externes ...
//
extern void SimuInit(char *, int);
extern void SimExit(int);
extern int SimuWaitTPE(void);

extern int	SimuLogHN;	// To activate log file to trace exchanges between PC and TPE (Primitives, entry point...)
extern char	SimuLogAppliFileName[256]; // Log File name


/***********************************************************************************/

// ... Structure 
typedef struct {
	unsigned short id;				// Id , cf. info.application_type or adf file ...
	void (* entry)() ;				// Entry routine for application
} appliPC;


#endif

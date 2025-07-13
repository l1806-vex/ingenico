/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.h"

#ifdef _SIMULPC_

#include "SimuMain.h"

//// Macros & preprocessor definitions //////////////////////////

#define SIMU_COM_PORT		"COM5"
#define SIMU_PORT_IS_USB	1

//// Types //////////////////////////////////////////////////////

//// Extern functions ///////////////////////////////////////////

extern void entry(void);

//// Global variables ///////////////////////////////////////////

appliPC tabAppliPC[] =
{
	{ 0x0052, entry },
	{ 0x0000, NULL }
};

//// Functions //////////////////////////////////////////////////
void main(int argc, char* argv[])
{
	// Not used parameters
	(void)argc;
	(void)argv;

	// Log file generation
	SimuLogHN = 0;	// 1 : enable log file, 0 : disable
	strcpy(SimuLogAppliFileName, "SimuEFT30_xxx.log");

	// Initialise the simulator
	SimuInit(SIMU_COM_PORT, SIMU_PORT_IS_USB);

	// Start the communication with the POS
	SimuWaitTPE();

	// Exit
	SimExit(KPB_NO_ERROR);
}

#endif // _SIMULPC_

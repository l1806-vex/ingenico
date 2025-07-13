#ifndef __PARAMS_H__INCLUDED__
#define __PARAMS_H__INCLUDED__

/////////////////////////////////////////////////////////////////

//// Macros & preprocessor definitions //////////////////////////

#define TAG_EMV_COMM_PARAMS					(0)
#define TAG_EMV_COMM_PORT					(1)
#define TAG_EMV_COMM_BAUDRATE				(2)
#define TAG_EMV_COMM_FIRST_CHAR_TIMEOUT		(3)
#define TAG_EMV_COMM_NEXT_CHAR_TIMEOUT		(4)

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

void Params_FirstInit(void);
void Params_Load(void);
int Params_Save(void);
int Params_Set(TLV_TREE_NODE hParamsTlvTree);
int Params_GetComPort(void);
int Params_GetComBaudrate(void);
unsigned long Params_GetFirstCharTimeout(void);
unsigned long Params_GetNextCharTimeout(void);

#endif

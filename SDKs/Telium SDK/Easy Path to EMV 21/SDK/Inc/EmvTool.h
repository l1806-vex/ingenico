#ifndef __EMV_TOOL_H__INCLUDED__
#define __EMV_TOOL_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define EMV_TOOL_APPLI_TYPE						(0x61)

#define EMV_TOOL_SERVICE_CARD_TRACE_RESET		(101)
#define EMV_TOOL_SERVICE_CARD_TRACE_ADD			(102)

#define EMV_TOOL_SERVICE_IAC_INPUT				(103)
#define EMV_TOOL_SERVICE_IAC_OUTPUT				(104)

#define EMV_TOOL_SERVICE_TAGS_RESET				(105)
#define EMV_TOOL_SERVICE_TAGS_ADD				(106)

#define EMV_TOOL_SERVICE_DISPLAY_MENU			(200)
#define EMV_TOOL_SERVICE_CONFIGURE				(201)
#define EMV_TOOL_SERVICE_DUMP_TRACE				(202)
#define EMV_TOOL_SERVICE_DUMP_TAGS				(203)
#define EMV_TOOL_SERVICE_DUMP_IAC				(204)

// For backwark compatibility
#define SERVICE_TRACE_RESET						(EMV_TOOL_SERVICE_CARD_TRACE_RESET)
#define SERVICE_TRACE_LOAD						(EMV_TOOL_SERVICE_CARD_TRACE_ADD)

#define SERVICE_IAC_ENTRY						(EMV_TOOL_SERVICE_IAC_INPUT)
#define SERVICE_IAC_OUTPUT						(EMV_TOOL_SERVICE_IAC_OUTPUT)

#define APDUCommandIAC							T_APDU_COMMAND
#define APDUCommandIAC_V2						T_APDU_COMMAND_V2
#define APDUCommandIAC_V3						T_APDU_COMMAND_V3
#define APDUResponseIAC							T_APDU_RESPONSE
#define StructProcessSpy						T_STRUCT_PROCESS_SPY
#define StructProcessSpy_V2						T_STRUCT_PROCESS_SPY_V2


#define EMV_TOOL_TAGS_NAME_MAX_SIZE				32

// Output links
#define EMV_TOOL_OUTPUT_PRINTER					1
#define EMV_TOOL_OUTPUT_USB						2
#define EMV_TOOL_OUTPUT_COM0					3

#define EMV_TOOL_MAX_TAGS_TO_OUTPUT				1024

//// Types //////////////////////////////////////////////////////

typedef struct
{
	unsigned char CLA;
	unsigned char INS;
	unsigned char P1;
	unsigned char P2;
	unsigned char Lc;
	unsigned char Data[100];
	unsigned char Le;
	unsigned char com_type;
} T_APDU_COMMAND;

typedef struct
{
	unsigned char CLA;
	unsigned char INS;
	unsigned char P1;
	unsigned char P2;
	unsigned char Lc;
	unsigned char Data[160];
	unsigned char Le;
	unsigned char com_type;
} T_APDU_COMMAND_V2;

typedef struct
{
	unsigned char CLA;
	unsigned char INS;
	unsigned char P1;
	unsigned char P2;
	unsigned char Lc;
	unsigned char Data[255];
	unsigned char Le;
	unsigned char com_type;
} T_APDU_COMMAND_V3;

typedef struct
{
	unsigned int Lr;
	unsigned char Data[300];
	unsigned char SW1;
	unsigned char SW2;
} T_APDU_RESPONSE;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	T_APDU_COMMAND param_in;
	T_APDU_RESPONSE param_out;
} T_STRUCT_PROCESS_SPY;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	T_APDU_COMMAND_V2 param_in;
	T_APDU_RESPONSE param_out;
} T_STRUCT_PROCESS_SPY_V2;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	T_APDU_COMMAND_V3 param_in;
	T_APDU_RESPONSE param_out;
} T_STRUCT_PROCESS_SPY_V3;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	char szName[EMV_TOOL_TAGS_NAME_MAX_SIZE + 1];
} T_STRUCT_PROCESS_TAGS_RESET;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;
} T_STRUCT_PROCESS_TAGS_ADD;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	_DEL_ del;
} T_STRUCT_PROCESS_TRACK_IAC_DEL;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	int nLink;
	int nBaudrate;
} T_STRUCT_PROCESS_CONFIGURE;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	int bDetailed;
} T_STRUCT_PROCESS_DUMP_TRACE;

typedef struct
{
	unsigned short type_code;
	unsigned short service;
	int function;

	int bDumpAll;
	int nNumberOfTags;
	unsigned long Tags[EMV_TOOL_MAX_TAGS_TO_OUTPUT];
} T_STRUCT_PROCESS_DUMP_TAGS;

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////
/*
void EmvTool_CardTraceReset(void);
int EmvTool_CardTraceAddCommand(int nCommandSize, const unsigned char* pCommand, int nResponseSize, const unsigned char* pResponse);

void EmvTool_TagsReset(const char* szName);
int EmvTool_TagsAdd(int nSize, const void* pBuffer);
*/
#endif // __EMV_TOOL_H__INCLUDED__

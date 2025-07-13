//! \file
//! Module that manages the data dump on a ticket at the end of a transaction

#ifndef __DLL_TESTING_DUMPDATA_H__INCLUDED__
#define __DLL_TESTING_DUMPDATA_H__INCLUDED__

#define CUSTOM_OUTPUT_NONE			0
#define CUSTOM_OUTPUT_PRINTER		1
#define CUSTOM_OUTPUT_COM0			2
#define CUSTOM_OUTPUT_USB			3

void DumpSetOutputId (unsigned char ucOutputId);
void DumpNewLine(void);
void DumpCloseOutputDriver (void);
void DumpData (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(printf, 1, 2)));
#else
	;
#endif

unsigned char DumpGetOutputId (void);
int DumpOpenOutputDriver (void);

void DllTesting_DumpData_DumpSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct, const int nIndent);


#endif // __DLL_TESTING_DUMPDATA_H__INCLUDED__

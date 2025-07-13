//! \file
//! Module that manages a database storage.

#ifndef __BLACK_LIST_H__INCLUDED__
#define __BLACK_LIST_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////
#define C_CLESS_VOID_PAN_SEQ_NUMBER 	0xff

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \brief Black list initialisation with global variables reset.
//! \return
//!		- Nothing.
void ClessSample_BlackListInit(void);

//! \brief Delete the black list.
//! \return
//!		- Nothing.
void ClessSample_BlackListDelete(void);

//! \brief Load a black list file in memory with the default .
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.
int ClessSample_BlackListLoad(void);

//! \brief Load a black list file in memory.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.
int ClessSample_BlackListGetNewFile(const char* szPath, const char* szFile);

//! \brief Save a black list in a default file.
//! \return
//!		- TRUE if the black list file has been correctly updated, FALSE else.
int ClessSample_BlackListSave(void);

//! \brief Check if a Pan + PanSeqNumber is in the black list.
//! This function must be used with an ASCII PAN number and PAN Sequence Number.
//! \param[in] szPan card Pan number.
//! \param[in] nPanSeqNumber card Pan Sequence Number.
//! \return
//!		- TRUE if the Pan + PanSeqNumber is in the Black List, FALSE else.
int ClessSample_BlackListIsPanAscii(const char* szPan, int nPanSeqNumber);

//! \brief Check if a Pan + PanSeqNumber is in the black list.
//! \param[in] szPan card Pan number.
//! \param[in] nPanSeqNumber card Pan Sequence Number.
//! \return
//!		- TRUE if the Pan + PanSeqNumber is in the Black List, FALSE else.
int ClessSample_BlackListIsPan(int nLength, const unsigned char* pPan, int nPanSeqNumber);

//! \brief Check if a Black list has been loaded.
//! \return
//!		- TRUE if a black list with at least one element is loaded.
int ClessSample_IsBlackListPresent(void);

#endif // __BLACK_LIST_H__INCLUDED__

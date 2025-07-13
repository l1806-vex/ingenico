//! \file
//! Module that provides graphical functions for terminal.

#ifndef __CLESS_SAMPLE_TERM_H__INCLUDED__
#define __CLESS_SAMPLE_TERM_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define YESCLEAR					TRUE
#define NOCLEAR						FALSE

#define LONGLINE					TRUE
#define SHORTLINE					FALSE

#define C_NBLANGHOLDER			3				//!< Number of managed languages for card holder.
#define C_NBLANGMERCH			4				//!< Number of managed languages for merchant.

//// Types //////////////////////////////////////////////////////
typedef struct
{
	unsigned char    iso639_code [3];			//!< 2 digits coding the language. ex : "en".
	unsigned char    lang_name [25];			//!< Name to be displayed on the menu. ex : "ENGLISH".
	unsigned char    table_id;					//!< Id in the messages tables. ex : 0.
}
t_lang_code;


//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////


//! \brief Display a message on the diaply using WGUI.
//! \param[in] nline Line where the message shall be displayed.
//! \param[in] ptrMSG Message structure to be used.
//! \param[in] bmode : TRUE to erase before display something, else nothing

void ClessSample_Term_SetMessage (int nline, MSGinfos * ptrMSG, unsigned char bmode);
//! \brief Refresh the screen

void ClessSample_Term_RefreshScreenWgui (void);
//===========================================================================
//! \brief This function display a text line in graphic mode. 
//! \param[in] nline : line index.
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment : center, left, rigth, ....
//! \param[in] bmode : TRUE to erase before display something, else nothing
//! \param[in] bLongLine : TRUE for long line to display (little police will be used), FALSE else.
//! \param[in] nFontSize : Possibility to force the font size.
//===========================================================================
void ClessSample_Term_DisplayGraphicLine(int nline, MSGinfos * ptrMSG, int nAlignment, unsigned char bmode, unsigned char bLongLine, const int nFontSize);


//===========================================================================
//! \brief This function initialise Messages menagement. 
//===========================================================================
void ClessSample_Term_Initialise(void);

//===========================================================================
//! \brief This function gives message referenced by number in appropriate language. 
//! If the specific message in not found, a default text is pointed.
//! \param[in] nNum message number.
//! \param[in] nLanguage language number (0:English, 1:french ...)
//! \param[out] pMsgInfo Structure filled with th emessage info.
//===========================================================================
void ClessSample_Term_Read_Message(int nNum, int nLanguage, MSGinfos * pMsgInfo);

//===========================================================================
//! \brief This function return lang identifier. 
//! \param[in] puc_Lang iso639 text code.
//! \return
//! 	lang code.
//===========================================================================
int ClessSample_Term_GiveLangNumber(unsigned char * puc_Lang);
#endif //__CLESS_SAMPLE_TERM_H__INCLUDED__

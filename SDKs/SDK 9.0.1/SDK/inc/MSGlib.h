/*! @addtogroup KSFAM_MSGLIB
	* @{
 * Each application could use its own messages file but a messages file could be used by several 
 * applications. In the MSG file, messages of an application are identified by the file type and the 
 * application type of the application, Manager or DLL. 
 * To use a messages file, an application must: 
 * - Load the MSG file that contains its messages 
 * - Define the MSG file it uses 
 * - Define the default messages 
 * - Define the current language 
 * - Define the default language 
 * - Call DisplayMSG, PrintMSG, GetMessage functions

 * A message is composed by 3 information: 
 * - The coding: Unicode or ISO8859 standard 
 * - The FON file used to display/print the message 
 * - The message itself 
 * These information are grouped in a structure named MSGinfos 

 **/

/*! @defgroup KSFAM_MSGLIB_LOADING Message loading
	* @{
	* Functions allowing the loading of a message
	* @} **/

/*! @defgroup KSFAM_MSGLIB_REGISTER Message files registration
	* @{
	* An application uses two types of messages: 
	* - The default messages of the application (ex: in english and in french). These messages 
	* are contained in a table embedded in the application. The content of this table is the 
	* content of a MSG file (converted by MSG2C tool). 
	* - The current MSG file (loaded in the terminal): file that could be load by the application in 
	* order to customize default messages and/or to propose a new language. 
	* @} **/

/*! @defgroup KSFAM_MSGLIB_LANGUAGES Message languages
	* @{
	* An application must define the current language and the default language. The default language 
	* is used if the message cannot be found in the current language.  
	* @} **/

/*! @defgroup KSFAM_MSGLIB_INIT Message initialisation 
	* @{
	* Initialisation of the message information
	* @} **/

/*! @defgroup KSFAM_MSGLIB_DISPLAY Message display
	* @{
	* Functions allowing to insert a message in the graphic context with specified font
	* @} **/

/*! @defgroup KSFAM_MSGLIB_PRINT Message printing
	* @{
	* Functions allowing to print a message (2 solutions are possible)
	* @} **/

/*! @defgroup KSFAM_MSGLIB_GET Message information
	* @{
	* Functions allowing to get message information
	* @} **/
/*! @defgroup KSFAM_MSGLIB_MISCELLANOUS Message miscellanous

	* @{
	* Other functions
	* @} **/

#ifndef MSGLIB_H
#define MSGLIB_H

#define EN "EN"				/*!< English */
#define FR "FR"				/*!< French */

#define _ISO8859_ 1
#define _UNICODE_ 0

/*! @brief Message information structure.*/
// @GSIM_T:MSGinfos:SUPPLIED(BUF_SER_MSGinfos;BUF_DES_MSGinfos)
typedef struct {
	int 	coding;									/*!< _ISO8859_ ou _UNICODE_ */
	char 	*file;									/*!< pointer to the loaded file */
	char 	*message;								/*!< pointer to the message */
}MSGinfos;

/*! @brief Message information structure.*/
// @GSIM_T:InfosMSG_CUST:SUPPLIED(BUF_SER_InfosMSG_CUST;BUF_DES_InfosMSG_CUST)
typedef struct {
	int 	 num;												/*!< message number*/
	MSGinfos info_msg;								/*!< pointer to the MSGinfos struct*/
	int       periph;									/*!< Name Periph to display*/
	int       flag;                   /*!< wait after display or not*/
	int       cr_treatment;           /*!< treatment result*/
	char     *option;                 /*!< display option*/
}InfosMSG_CUST;


/*! @addtogroup KSFAM_MSGLIB_LOADING
	* @{
**/
/*! @brief load a signed MSG file from MSG file to buffer
* @param FileMSGName : name of the MSG file
* @return an access to Buffer if OK
* @return The MSG file loaded in the buffer
* @return NULL : unable to open the file, wrong file ID, wrong file version
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 184) if function does not exist
 *
 * @link KSFAM_MSGLIB_LOADING Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:LoadMSG:KSFAM_MSGLIB:0x01
// \endif
extern char *LoadMSG(char *FileMSGName);
/*! @} **/


/*! @addtogroup KSFAM_MSGLIB_REGISTER
	* @{
**/
/*! @brief Register the MSG file used by the application
* @param CurrentMSG : the MSG file used by the application
* @return 0: OK	-1:MyMSG is not a loaded MSG file
* @return The MSG file loaded in the buffer
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 139) if function does not exist
 *
 * @link KSFAM_MSGLIB_REGISTER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefCurrentMSG:KSFAM_MSGLIB:0x02
// \endif
extern int 	DefCurrentMSG(char *CurrentMSG);



/*! @brief Get the MSG file used by the application
* @return : the acces to the MSG file used by the application
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 140) if function does not exist
 *
 * @link KSFAM_MSGLIB_REGISTER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetCurrentMSG:KSFAM_MSGLIB:0x03
// \endif
extern char *GetCurrentMSG(void);

/*! @brief Register the local MSG table used by the application
* @param DefaultMSG : the local MSG used by the application
* @return 0: OK
* @note How to build default messages table? 
* <b> How to build default messages table? </b> 
* - Build a MSG file (ex : DefaultMSG.MSG) with MSGtools 
* - Convert the MSG file with MSG2C tool: 
*     MSG2C DefaultMSG.MSG DefaultMSG.c 
* - The obtained file (DefaultMSG.c) contains the messages table (const unsigned char const DefaultMSG []={...}) \n
* <b> How to use the default messages table? </b> 
* - Add DefaultMSG.c file in the application 
* - Use the DefDefaultMSG function: DefDefaultMSG(DefaultMSG) 
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 141) if function does not exist
 *
 * @link KSFAM_MSGLIB_REGISTER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefDefaultMSG:KSFAM_MSGLIB:0x04
// \endif
extern int 	DefDefaultMSG(char *DefaultMSG);


/*! @brief Get the address of the local MSG used by the application
* @return : the acces to the MSG table used by the application
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 142) if function does not exist
 *
 * @link KSFAM_MSGLIB_REGISTER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetDefaultMSG:KSFAM_MSGLIB:0x05
// \endif
extern char *GetDefaultMSG(void);
/*! @} **/


/*! @addtogroup KSFAM_MSGLIB_LANGUAGES
	* @{
**/
/*! @brief get Manager language
* @return : the ISO639-1 language code of the current Manager language
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 147) if function does not exist
 *
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetManagerLanguage:KSFAM_MSGLIB:0x06
// \endif
extern char *GetManagerLanguage(void);


/*! @brief Register the language used by the application
* @return : char *Language : the ISO639-1 language code
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 143) if function does not exist
 *
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefCurrentLang:KSFAM_MSGLIB:0x07
// \endif
extern void DefCurrentLang(char *Language);



/*! @brief Get the language used by the application
* @return : The ISO639-1 language code
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 144) if function does not exist
 *
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetCurrentLang:KSFAM_MSGLIB:0x08
// \endif
extern char *GetCurrentLang(void);



/*! @brief Get the language used by the application
* @return : The ISO639-1 language code
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 145) if function does not exist
 *
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefDefaultLang:KSFAM_MSGLIB:0x09
// \endif
extern void DefDefaultLang(char *Language);



/*! @brief Get the default language used by the application
* @return : The ISO639-1 language code
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 146) if function does not exist
*
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetDefaultLang:KSFAM_MSGLIB:0x0A
// \endif
extern char *GetDefaultLang(void);
/*! @} **/

/*! @addtogroup KSFAM_MSGLIB_DISPLAY
	* @{
**/
/*! @brief display a message of a MSG file
* @param x: horizontal position
* @param y: vertical position
* @param messageNum : message number
* @param reverse: Reverse video _ON_ or _OFF_
* @param police: font name
* @param type: _FIXED_WIDTH_ or _PROP_WIDTH_
* @return  : OK , -1 : cannot find message
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 155) if function does not exist
*
 * @link KSFAM_MSGLIB_DISPLAY Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayMSG:KSFAM_MSGLIB:0x0B
// \endif
extern int 	DisplayMSG (int x,int y,int messageNum, int reverse, char *police, int type);

/*! @brief display a message of a MSG file
* @param x: horizontal position
* @param y: vertical position
* @param messageNum : message number
* @param reverse: Reverse video _ON_ or _OFF_
* @param police: font name
* @param type: _FIXED_WIDTH_ or _PROP_WIDTH_
* @return  : OK , -1 : cannot find message
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 161) if function does not exist
*
 * @link KSFAM_MSGLIB_DISPLAY Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DisplayMSG:KSFAM_MSGLIB:0x0C
// \endif
extern int 	_DisplayMSG (int x,int y,int messageNum, int reverse, char *police, int type);


/*! @brief display a message
* @param x : horizontal position
* @param y : vertical position
* @param pMSGinfos : struct message (see msglib.h)
* @param reverse: Reverse video _ON_ or _OFF_
* @param police: font name
* @param type: _FIXED_WIDTH_ or _PROP_WIDTH_
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 135) if function does not exist
*
 * @link KSFAM_MSGLIB_DISPLAY Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DisplayMSGinfos:KSFAM_MSGLIB:0x0E
// \endif
extern void _DisplayMSGinfos (int x,int y,MSGinfos *pMSGinfos, int reverse, char *police, int type);


/*! @brief display a message
* @param x: horizontal position
* @param y: vertical position
* @param pMSGinfos : struct message (see msglib.h)
* @param reverse: Reverse video _ON_ or _OFF_
* @param police: font name
* @param type: _FIXED_WIDTH_ or _PROP_WIDTH_
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 193) if function does not exist
*
 * @link KSFAM_MSGLIB_DISPLAY Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayMSGinfos:KSFAM_MSGLIB:0x0D
// \endif
extern void DisplayMSGinfos (int x,int y,MSGinfos *pMSGinfos, int reverse, char *police, int type);
/*! @} **/

/*! @addtogroup KSFAM_MSGLIB_PRINT
	* @{
**/
/*! @brief print a message of a MSG file
* @param messageNum : message number
* @param reverse: Reverse video _ON_ or _OFF_
* @param police: font name
* @param type: _FIXED_WIDTH_ or _PROP_WIDTH_
* @return  : OK , -1 : cannot find message
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 156) if function does not exist
*
 * @link KSFAM_MSGLIB_PRINT Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PrintMSG:KSFAM_MSGLIB:0x0F
// \endif
extern int 	PrintMSG (int messageNum, int reverse, char *police, int type);


/*! @brief print a message
* @param pMSGinfos : struct message (see msglib.h)
* @param reverse: Reverse video _ON_ or _OFF_
* @param police: font name
* @param type: _FIXED_WIDTH_ or _PROP_WIDTH_
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 179) if function does not exist
*
 * @link KSFAM_MSGLIB_PRINT Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PrintMSGInfos:KSFAM_MSGLIB:0x10
// \endif
extern void PrintMSGInfos (MSGinfos *pMSGinfos, int reverse, char *police, int type);
/*! @} **/

/*! @addtogroup KSFAM_MSGLIB_LANGUAGES
	* @{
**/
/*! @brief check if a language exists in a MSG file
* @param Language : the ISO639-1 language code
* @param MSGfile :the acces to the MSG file used by the application
* @return  : 0 language exists , -1 : language not in MSG file
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 157) if function does not exist
*
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:LanguageExist:KSFAM_MSGLIB:0x11
// \endif
extern int 	LanguageExist(char *Language, char *MSGfile);


/*! @brief get all the languages of a MSG file
* @param pLanguages : to get all the ISO639-1 languages codes
* @param MSGfile :the acces to the MSG file used by the application
* @return  : the number of languages contained in the MSG file
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 158) if function does not exist
*
 * @link KSFAM_MSGLIB_LANGUAGES Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetSupportedLanguages:KSFAM_MSGLIB:0x12
// \endif
extern int 	GetSupportedLanguages(char *pLanguages, char *MSGfile);
/*! @} **/


/*! @addtogroup KSFAM_MSGLIB_MISCELLANOUS
	* @{
**/
/*! @brief Get the file type of the application
* @return  : The file type of the application (1:appli,2:DLL,3:driver)
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 148) if function does not exist
*
 * @link KSFAM_MSGLIB_MISCELLANOUS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetFileType:KSFAM_MSGLIB:0x13
// \endif
extern int 	GetFileType(void);


/*! @brief Get the application type of the application
* @return  : The application type of the application
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 149) if function does not exist
*
 * @link KSFAM_MSGLIB_MISCELLANOUS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetAppliType:KSFAM_MSGLIB:0x14
// \endif
extern int 	GetAppliType(void);
/*! @} **/


/*! @addtogroup KSFAM_MSGLIB_INIT
	* @{
**/
/*! @brief Initialize the information of a MSGinfos whith a default value
* coding=_ISO8859_;
* file=default font adress;
* message=NULL;
* @param pMSGinfos : struct message (see msglib.h)
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 152) if function does not exist
*
* @link KSFAM_MSGLIB_INIT Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:InitMSGinfos:KSFAM_MSGLIB:0x15
// \endif
extern void InitMSGinfos(MSGinfos *pMSGinfos);


/*! @brief Initialize the information of a MSGinfos with the given message
* @param pMSGinfos : struct message (see msglib.h)
* @param msg :message 
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 182) if function does not exist
*
 * @link KSFAM_MSGLIB_INIT Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:InitMSGinfos_message:KSFAM_MSGLIB:0x16
// \endif
extern void InitMSGinfos_message(MSGinfos *pMSGinfos,char *msg);
/*! @} **/


/*! @addtogroup KSFAM_MSGLIB_GET
	* @{
**/
/*! @brief return the information of a MSGinfos with the given message number
* @param MSGnum : message number
* @param pMSGinfos : struct message (see msglib.h)
* @return  : 0 if message exists , else -1
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 154) if function does not exist
*
 * @link KSFAM_MSGLIB_GET Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetMessageInfos:KSFAM_MSGLIB:0x17
// \endif
extern int 	GetMessageInfos(int MSGnum,MSGinfos *pMSGinfos);


/*! @brief return the information of a MSGinfos with the given message number
* @param MSGfile : file of message number
* @param language : name of language present in the file
* @param FileType : type of file
* @param AppliType : type of appli
* @param MSGnum : message number
* @param pMSGinfos : struct message (see msglib.h)
* @return  : 0 if message exists , else -1
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 150) if function does not exist
*
 * @link KSFAM_MSGLIB_INIT Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetSpecificMessage:KSFAM_MSGLIB:0x18
// \endif
extern int 	GetSpecificMessage(char *MSGfile,unsigned char *language,int FileType, int AppliType,int MSGnum,MSGinfos *pMSGinfos);


/*! @brief return the information of a MSGinfos with the given language and the given message number
* @param Language : name of language
* @param MSGnum : message number
* @param pMSGinfos : struct message (see msglib.h)
* @return  : 0 if message exists , else -1
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 159) if function does not exist
*
 * @link KSFAM_MSGLIB_INIT Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetMessageInfosInLang:KSFAM_MSGLIB:0x19
// \endif
extern int 	GetMessageInfosInLang(char * Language,int MSGnum,MSGinfos *pMSGinfos);
/*! @} **/

/*! @addtogroup KSFAM_MSGLIB_DISPLAY
	* @{
**/
/*! @brief _DrawText displays an coded string into screen memory
* @param x0 : name of language
* @param y0 : message number
* @param pMSGinfos : struct message (see msglib.h)
* @param police  : font name  
* @param type  : _FIXED_WIDTH_ or _PROP_WIDTH_ 
* @param pen  : color of the text in ARGB mode (0xAARRGGBB)  
* @param brush  : color of the background in ARGB mode (0xAARRGGBB)
* @return  : 0 if OK , else -1 if missing police else -2 if missing message 
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 226) if function does not exist
*
 * @link KSFAM_MSGLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawText:KSFAM_MSGLIB:0x1A
// \endif
extern int _DrawText(int x0,int y0,MSGinfos *pMSGinfos,char *police,int type,int pen,int brush);

/*! @brief _DrawText displays an coded string into screen memory and paint region used by the string. 
* @param x0 : name of language
* @param y0 : message number
* @param pMSGinfos : struct message (see msglib.h)
* @param police  : font name  
* @param type  : _FIXED_WIDTH_ or _PROP_WIDTH_ 
* @param pen  : color of the text in ARGB mode (0xAARRGGBB)  
* @param brush  : color of the background in ARGB mode (0xAARRGGBB)
* @return  : 0 if OK , else -1 if missing police else -2 if missing message 
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 225) if function does not exist
*
 * @link KSFAM_MSGLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawText:KSFAM_MSGLIB:0x1B
// \endif
extern int DrawText(int x0,int y0,MSGinfos *pMSGinfos,char *police,int type,int pen,int brush);
/*! @} **/


/*! @addtogroup KSFAM_MSGLIB_MISCELLANOUS
	* @{
**/
/*! @brief CUSTOMIZED_MESSAGE entry point
* @param size  : Size of data = sizeof(InfosMSG_CUST)
* @param param    : InfosMSG_CUST structure
* @return 
* - FCT_OK
* - STOP
*
* @include msglib_Sample_01.c
*
 * @link KSFAM_MSGLIB Back to top @endlink
*/
extern int customize_message          (int size,InfosMSG_CUST *param);

#endif
/*! @} **/

/*! @} **/


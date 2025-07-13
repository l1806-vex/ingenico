/*! @addtogroup KSFAM_XMLS
* @{
  * @section ex_XMLS Example
  *
  * @subsection sub01_XMLS XMLS INTERFACE:

 * @include XMLs_Sample_01.c
  * 
  * @link KSFAM_XMLS Back to top @endlink
 **/

#ifndef __XMLS_H__
#define __XMLS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define __XMLs_VOID(a) ((void*)(a))

/*! @brief XMLs parser handle. */
typedef void *XMLs_PARSER;

/*
======================================================================
                                List of Defines
======================================================================
*/

#define XMLS_OK                                     ( 0)         /*!< No error. */
#define XMLS_INVALID_HANDLE                         (-1)         /*!< Invalid parser. */
#define XMLS_BAD_PARAMETER                          (-2)         /*!< Bad input parameter (NULL pointer...). */
#define XMLS_ERROR_PARSING                          (-3)         /*!< XML buffer is badly formatted. */
#define XMLS_ERROR_TAG_MISMATCH                     (-4)         /*!< Start tag and End tag of an element are not the same. */
#define XMLS_ERROR_SEVERAL_ROOT_TAGS                (-5)         /*!< Several root tags have been found in the buffer. */
#define XMLS_ERROR_FILE_ACCESS                      (-6)         /*!< Error when accessing the file. */
#define XMLS_ERROR_MEMORY                           (-7)         /*!< Not enough memory. */
#define XMLS_ERROR_OPENING_STREAM					(-8)		 /*!< Error when opening the XML stream. */

#define XMLS_STATE_IDLE                             ( 1)         /*!< Before the root start tag or after the root end tag. */
#define XMLS_STATE_START_TAG                        ( 2)         /*!< A start tag is currently parsed. */
#define XMLS_STATE_END_TAG                          ( 3)         /*!< An end tag is currently parsed. */
#define XMLS_STATE_MISC                             ( 4)         /*!< Other tags are parsed (comments, CDATA). */
#define XMLS_STATE_DATA                             ( 5)         /*!< Data of an element is currently parsed. */

#define XML_DATA_ESCAPED_STRING                     ( 1 << 0 )   /*!< Replaces all the escaped XML strings by their ASCII value. */
#define XML_DATA_TRIM_SPACES                        ( 1 << 1 )   /*!< Removes all leading and final spaces. */
#define XML_DATA_REPLACE_LF                         ( 1 << 2 )   /*!< Replaces all LF (0x0A) by a space. */
#define XML_DATA_REPLACE_CR                         ( 1 << 3 )   /*!< Replaces all CR (0x0D) by a space. */
#define XML_DATA_REPLACE_TABS                       ( 1 << 4 )   /*!< Replaces all tabs by a space. */

#define XML_DATA_ALL    XML_DATA_ESCAPED_STRING | \
                        XML_DATA_TRIM_SPACES    | \
                        XML_DATA_REPLACE_LF     | \
                        XML_DATA_REPLACE_CR     | \
                        XML_DATA_REPLACE_TABS /*!< Activate all the previously described services. */


/*! @brief Options to configure the driver. */
typedef enum
{
	XMLs_START_ELEMENT_HANDLER, /*!< Function called on a start tag. The value set must be of \ref XMLs_StartElementCallback type.*/
	XMLs_END_ELEMENT_HANDLER,   /*!< Function called on a end tag. The value set must be of \ref XMLs_EndElementCallback type.*/
	XMLs_DATA_HANDLER,          /*!< Function called on data. The value set must be of \ref XMLs_DataCallback type.*/
	XMLs_CURRENT_LINE,          /*!< Current line in the file. GET only. */
	XMLs_CURRENT_COLUMN         /*!< Current column in the file. GET only. */
}T_XMLs_OPTION;

/*! @brief XML attributes handle, given to the start tag callback. */
typedef struct T_ATTRIBUTES_HANDLER* XMLs_ATTRIBUTE_HANDLE;

/*! @brief Prototype of the call-back function called on a start tag.
 *	@param		hXmlParser          Handle on the parser object
 *	@param		szName              Name of the start tag
 *	@param		hAttributes         Handle on the attributes
*/  
typedef void (*XMLs_StartElementCallback)( XMLs_PARSER hXmlParser, const char* szName, XMLs_ATTRIBUTE_HANDLE hAttributes );

/*! @brief Prototype of the call-back function called on an end tag.
 *	@param		hXmlParser          Handle on the parser object
 *	@param		szName              Name of the end tag
*/  
typedef void (*XMLs_EndElementCallback)( XMLs_PARSER hXmlParser, const char* szName );

/*! @brief Prototype of the call-back function called on data.
 *	@param		hXmlParser          Handle on the parser object
 *	@param		pcDataBuffer        Pointer on the beginning of the data
 *	@param		nLength             Data length
*/  
typedef void (*XMLs_DataCallback)( XMLs_PARSER hXmlParser, const char* pcDataBuffer, unsigned int nLength );


/*! @brief Prototype of the call-back function called to open a stream.
 *	@param		pUserData          	Pointer on user data
 *  @return
 *	- #XMLS_OK when the stream has been successfully open;
 *	- otherwise a negative value.
*/
typedef int  (*XMLs_STREAM_OpenCallback) ( void *pUserData );

/*! @brief Prototype of the call-back function called to read bytes from a stream.
 *	@param		pUserData        Pointer on user data
 *	@param		pucData          Pointer on the buffer receiving the bytes read from the stream
 *	@param		nDataSize        Number of bytes to read
 *  @return
 *  - a positive value : the number of bytes read from the stream
 *  - 0 when the end of stream has been reached
 *	- otherwise a negative value in case of error
*/
typedef int  (*XMLs_STREAM_ReadCallback) ( void *pUserData, unsigned char *pucData, unsigned int nDataSize  );


/*! @brief Prototype of the call-back function called to write bytes in a stream.
 *	@param		pUserData        Pointer on user data
 *	@param		pucData          Pointer on the buffer containing the bytes to write in the stream
 *	@param		nDataSize        Number of bytes to write
 *  - a positive value : the number of bytes which have been written in the stream
 *  - 0 when the end of stream has been reached
 *	- otherwise a negative value in case of error
*/
typedef int  (*XMLs_STREAM_WriteCallback)( void *pUserData, const unsigned char *pucData, unsigned int nDataSize  );

/*! @brief Prototype of the call-back function called to close a stream.
 *	@param		pUserData          	Pointer on user data
*/
typedef void (*XMLs_STREAM_CloseCallback)( void *pUserData );


//
/*! @brief Options to define a XML stream. */
typedef enum
{
	XMLs_STREAM_OPEN_HANDLER, 		/*!< Function called to open a streal. The value set must be of \ref XMLs_STREAM_OpenCallback type.*/
	XMLs_STREAM_READ_HANDLER,   	/*!< Function called to read bytes from the stream. The value set must be of \ref XMLs_STREAM_ReadCallback type.*/
	XMLs_STREAM_WRITE_HANDLER, 		/*!< Function called on write bytes in the streama. The value set must be of \ref XMLs_STREAM_WriteCallback type.*/
	XMLs_STREAM_CLOSE_HANDLER, 		/*!< Function called to close a stream. The value set must be of \ref XMLs_STREAM_CloseCallback type.*/
	XMLs_STREAM_READ_BLOCK_SIZE   	/*!< Integer value to indicate the size of when reading bytes from the stream. It is by default set to 256. */
}T_XMLs_STREAM_OPTION;


/*! @brief XMLs stream handle */
typedef void *XMLs_STREAM;

/*! @brief	This function parses an XML file stored in flash.
 *
 *	@param	pfOpenCb       	Pointer on the callback function called to open a stream. The value set must be of \ref XMLs_STREAM_OpenCallback type.
 *	@param	pfReadCb       	Pointer on the callback function called to read bytes from a stream. The value set must be of \ref XMLs_STREAM_ReadCallback type.
 *	@param	pfWriteCb       Pointer on the callback function called to write bytes in a stream. The value set must be of \ref XMLs_STREAM_WriteCallback type.
 *	@param	pfCloseCb       Pointer on the callback function called to close a stream. The value set must be of \ref XMLs_STREAM_CloseCallback type.
 *	@param	pUserData       Pointer on user data. This pointer will be passed for every call-back function
 *
 *  @return
 *	- an allocated handle
 *	- or NULL (in case of error)
 *
 *  @note The stream handle allocated by this function must be released by requesting the function \ref XMLs_STREAM_Destroy
 *  @note The parameter 'pfWriteCb' must be set to NULL. It is reserved for future use.
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
XMLs_STREAM XMLs_STREAM_Create( XMLs_STREAM_OpenCallback pfOpenCb,
								XMLs_STREAM_ReadCallback pfReadCb,
								XMLs_STREAM_WriteCallback pfWriteCb,
								XMLs_STREAM_CloseCallback pfCloseCb,
								void *pUserData );

/*! @brief	This function sets an option of an XML stream.
 *
 *	@param	hStream    Handle on the XML streal.
 *	@param	eOption    Option to set. Please refer \ref T_XMLs_STREAM_OPTION
 *	@param	pValue     Value of the option.
 *
 *  @return
 *	- #XMLS_OK
 *  - #XMLS_BAD_PARAMETER
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_STREAM_SetOption( XMLs_STREAM hStream, T_XMLs_STREAM_OPTION eOption, void *pValue );

/*! @brief	This function sets the user data linked to an XML stream.

 *	@param		hStream         Handle on the XML stream.
 *	@param		pUserData       Pointer on user data. This pointer will be passed for every call-back function.
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */

int XMLs_STREAM_SetUserData( XMLs_STREAM hStream, void *pUserData );


/*! @brief	This function destroys an XML stream.
 *
 *	@param	hStream Handle on the XML stream.
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_STREAM_Destroy( XMLs_STREAM hStream );


/*! @brief	This function creates an XML parser.
 *
 *  @return
 *	- Non-NULL value on success;
 *	- otherwise NULL.
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
XMLs_PARSER XMLs_Create( void );

/*! @brief	This function destroys an XML parser.
 *
 *	@param	hXml Handle on the XML parser.
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_Destroy( XMLs_PARSER hXml );

/*! @brief	This function sets an option of an XML parser.
 *
 *	@param	hXml    Handle on the XML parser.
 *	@param	eOption Option to set.
 *	@param	pValue  Value of the option.
 *
 *  @return
 *	- #XMLS_OK
 *  - #XMLS_BAD_PARAMETER
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_SetOption( XMLs_PARSER hXml, T_XMLs_OPTION eOption, const void* pValue );

/*! @brief	This function gets an option of an XML parser.
 *
 *	@param	hXml    Handle on the XML parser.
 *	@param	eOption Option to set.
 *	@param	pValue  Value of the option.
 *
 *  @return
 *	- #XMLS_OK
 *  - #XMLS_BAD_PARAMETER
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_GetOption( XMLs_PARSER hXml, T_XMLs_OPTION eOption, void* pValue );

/*! @brief	This function parses a buffer that contains an XML document.
 *
 *	@param	hXml          Handle on the parser 
 *	@param	pcBuffer      Input buffer
 *	@param	nBufferLength Size of the input buffer
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *	- #XMLS_ERROR_PARSING
 *	- #XMLS_ERROR_TAG_MISMATCH
 *	- #XMLS_ERROR_SEVERAL_ROOT_TAGS
 *  - #XMLS_ERROR_MEMORY
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_ParseBuffer( XMLs_PARSER hXml, const char* pcBuffer, unsigned int nBufferLength );

/*! @brief	This function parses an XML file stored in flash.
 *
 *	@param	hXml       Handle on the parser 
 *	@param	szFilePath Path to the XML file ("/HOST/TEST.XML")
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *	- #XMLS_ERROR_PARSING
 *	- #XMLS_ERROR_TAG_MISMATCH
 *	- #XMLS_ERROR_SEVERAL_ROOT_TAGS
 *  - #XMLS_ERROR_MEMORY
 *  - #XMLS_ERROR_FILE_ACCESS
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_ParseFile( XMLs_PARSER hXml, const char* szFilePath );


/*! @brief	This function parses an XML file stored in flash.
 *
 *	@param	hXml       Handle on the parser 
 *	@param	hIStream   Input stream handle \ref XMLs_STREAM
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *	- #XMLS_ERROR_PARSING
 *	- #XMLS_ERROR_TAG_MISMATCH
 *	- #XMLS_ERROR_SEVERAL_ROOT_TAGS
 *  - #XMLS_ERROR_MEMORY
 *  - #XMLS_ERROR_FILE_ACCESS
 *	- #XMLS_ERROR_OPENING_STREAM
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_ParseStream( XMLs_PARSER hXml, XMLs_STREAM hIStream );


/*! @brief	This function retrieves the number of XML attributes.
 *
 *	@param	hAttributes Handle on the XML attributes
 *
 *  @return
 *	- The number of attributes.
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_Attributes_GetCount( XMLs_ATTRIBUTE_HANDLE hAttributes );

/*! @brief	This function retrieves the name and the value of an attribute, by index.
 *
 *	@param	hAttributes Handle on the XML attributes
 *  @param	nIndex      Index of the attribute.
 *  @param	pName       Pointer to get the name of the attribute.
 *  @param	pValue      Pointer to get the value of the attribute.
 *
 *  @return
 *	- #XMLS_OK
 *  - #XMLS_BAD_PARAMETER
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_Attributes_GetByIndex( XMLs_ATTRIBUTE_HANDLE hAttributes, unsigned int nIndex, const char** pName, const char** pValue );

/*! @brief	This function retrieves the value of an attribute, by name.
 *
 *	@param	hAttributes		Handle on the XML attributes
 *  @param	szName			Attribute's name to search.
 *  @param	bCaseSensitive	Search is case sensitive (1) or not (0).
 *
 *  @return
 *	- Non-NULL value in case of success.
 *  - NULL if the attribute is not found.
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
const char* XMLs_Attributes_GetByName( XMLs_ATTRIBUTE_HANDLE hAttributes, const char* szName, int bCaseSensitive );

/*! @brief	This function sets the user data linked to the parser.

 *	@param		hXml            Handle on the parser
 *	@param		pUserData       Pointer that will be passed every call-back function
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_SetUserData( XMLs_PARSER hXml,
                      void* pUserData );

/*! @brief	This function gets the user data linked to the parser.

 *	@param		hXml            Handle on the parser
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
void* XMLs_GetUserData( XMLs_PARSER hXml );

/*! @brief	This function stops the parsing. It can only be called during a call-back function.

 *	@param		hXml            Handle on the parser
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
int XMLs_Abort( XMLs_PARSER hXml );


/*! @brief	This function processes the data of an XML element.

 *	@param		pcInput         Pointer on the beginning of the data
 *	@param		nInputLength    Length of the input data
 *	@param		nOptions        A bitmap representing the options to use
 *                            @n A combination of: 
 *                            - #XML_DATA_ESCAPED_STRING
 *                            - #XML_DATA_REPLACE_LF
 *                            - #XML_DATA_REPLACE_CR
 *                            - #XML_DATA_REPLACE_TABS 
 *                            - #XML_DATA_TRIM_SPACES
 *
 *  @return
 *	- NULL value if the result is empty, a zero terminating string otherwise.
 *	- If not NULL, the result string must be freed by the application.
 *
 *  @par Example:

 * @include XMLs_Sample_02.c
 * 
 *  @link KSFAM_XMLS Back to top @endlink
 */
char* XMLs_ProcessData( const char*  pcInput,
                        unsigned int nInputLength,
                        unsigned int nOptions );



//////////////////////////////////////////////////////
//////////////////// DEPRECATED ! ////////////////////
//////////////////////////////////////////////////////

#ifndef _DEPRECATED_AVL_SDK091000_
#else
#define __XMLS_ATT_NAME_MAX_LEN		                  20         /*!< DEPRECATED This constant shall not be used anymore. */
#define __XMLS_ATT_VALUE_MAX_LEN	                  40         /*!< DEPRECATED This constant shall not be used anymore. */
#define __XMLS_TAG_NAME_MAX_LEN		                  20         /*!< DEPRECATED This constant shall not be used anymore. */
#endif


/*! @brief Structure describing an XML attribute
 *  This prototype is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.
 *
*/
#ifndef _DEPRECATED_AVL_SDK091000_
#define XMLs_ATTRIBUTE ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
typedef struct
{
    char m_szName[__XMLS_ATT_NAME_MAX_LEN];    /*!< DEPRECATED Attribute's name. */
    char m_szValue[__XMLS_ATT_VALUE_MAX_LEN];   /*!< DEPRECATED Attribute's value. */
} XMLs_ATTRIBUTE;
#endif

/*
======================================================================
                             Callback functions
======================================================================
*/

/*! @brief Prototype of the call-back function called on a start tag.
 *  This prototype is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.
 *
 *	@param		hXmlParser          Handle on the parser object
 *	@param		szName              Name of the start tag
 *	@param		pAttributes         Pointer on an array of attributes
 *	@param		nAttributesNumber   Number of attributes
*/  
#ifndef _DEPRECATED_AVL_SDK091000_
#define XMLs_StartElementHandler ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
typedef void (*XMLs_StartElementHandler)( XMLs_PARSER     hXmlParser,
                                          const char*     szName,
                                          XMLs_ATTRIBUTE* pAttributes,
                                          unsigned int    nAttributesNumber );
#endif

/*! @brief  Prototype of the call-back function called on an end tag.
 *  This prototype is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.
 *
 *	@param		hXmlParser          Handle on the parser object
 *	@param		szName              Name of the end tag
*/  
#ifndef _DEPRECATED_AVL_SDK091000_
#define XMLs_EndElementHandler ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
typedef void (*XMLs_EndElementHandler) ( XMLs_PARSER hXmlParser,
                                         const char* szName );
#endif

/*! @brief DEPRECATED Prototype of the call-back function called on data.
 *  This prototype is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.
 *
 *	@param		hXmlParser          Handle on the parser object
 *	@param		pcDataBuffer        Pointer on the beginning of the data
 *	@param		nLength             Data length
*/  
#ifndef _DEPRECATED_AVL_SDK091000_
#define XMLs_StartElementHandler ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
typedef void (*XMLs_CharacterDataHandler) ( XMLs_PARSER  hXmlParser,
                                            const char*  pcDataBuffer,
                                            unsigned int nLength );
#endif

/*
======================================================================
                    Functions Definition
======================================================================
*/

/*! @brief	This function creates an XML parsing object.
 *  This function is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.

 *	@param		pAttributes         Pointer on an array of attributes allocated by the application
 *	@param		nAttributesNumber   Number of attributes in an array
 *
 *  @return
 *	- Non-NULL value on success;
 *	- otherwise NULL.
 *
 *	@note
 *  The array of attributes is allocated by the application. The XMLs parser uses this array to store the attributes found while processing start tags. 
 *  Therefore, the parser cannot deal with more attributes than the maximum number declared in this function. 
 *
 *  The names and values of attributes are truncated to maximum lengths (of respectively 20 and 40 bytes).
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
#ifndef _DEPRECATED_AVL_SDK091000_
#define XMLs_ParserOpen ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else 
XMLs_PARSER XMLs_ParserOpen( XMLs_ATTRIBUTE *pAttributes, 
                             int nAttributesNumber ) MACRO_DEPRECATED ;
#endif

/*! @brief	This function destroys an XML parsing object.
 *  This function is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, please add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.

 *	@param		hXml    Handle on the parser to destroy
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
#ifndef _DEPRECATED_AVL_SDK091000_
#define XMLs_ParserClose ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else 
int XMLs_ParserClose( XMLs_PARSER hXml ) MACRO_DEPRECATED ;
#endif

/*! @brief	This function parses a text buffer that contains an XML document.
 *  This function is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, please add _DEPRECATED_AVL_SDK091000_ in your compilation define symbols.

 *	@param		hXml            Handle on the parser 
 *	@param		pcBuffer        Input buffer
 *	@param		nLength         Size of the input buffer
 *	@param		pStartFunction  Function to be called when a start tag is found 
 *	@param		pEndFunction    Function to be called when an end tag is found 
 *	@param		pDataFunction   Function to be called when data of an element is found
 *	@param		pUserData       Pointer that will be passed to every call-back function
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *	- #XMLS_ERROR_PARSING
 *	- #XMLS_ERROR_TAG_MISMATCH
 *	- #XMLS_ERROR_SEVERAL_ROOT_TAGS
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
 #ifndef _DEPRECATED_AVL_SDK091000_
 #define XMLs_Parse ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
 #else
int XMLs_Parse( XMLs_PARSER hXml,
                const char* pcBuffer,
                int         nLength,
                XMLs_StartElementHandler  pStartFunction,
                XMLs_EndElementHandler    pEndFunction,
                XMLs_CharacterDataHandler pDataFunction,
                void*       pUserData ) MACRO_DEPRECATED ;
#endif

/*! @brief This function gets the state of the parser.
 *  This function is deprecated. It will not be supported in Telium+ framework.
 *  To keep on using this function, please define the symbol '_DEPRECATED_AVL_SDK091000_' in your compilation settings.
 *
 *
 *	@param		hXml            Handle on the parser
 *	@param		ppcCurrent      Will contain the pointer on the current data parsed, it can be NULL
 *	@param		pnState         Will contain the state of the parser, it can be NULL
 *                            @n Possible values are: 
 *                            - #XMLS_STATE_IDLE
 *                            - #XMLS_STATE_START_TAG
 *                            - #XMLS_STATE_END_TAG
 *                            - #XMLS_STATE_MISC
 *                            - #XMLS_STATE_DATA 
 *
 *  @return
 *	- #XMLS_OK
 *	- #XMLS_INVALID_HANDLE
 *
 *  @link KSFAM_XMLS Back to top @endlink
 */
 #ifndef _DEPRECATED_AVL_SDK091000_
 #define XMLs_GetParsingState ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
 #else
int XMLs_GetParsingState( XMLs_PARSER hXml,
                          char** ppcCurrent,
                          int*   pnState ) MACRO_DEPRECATED;
#endif




#ifdef __cplusplus
}
#endif

#endif // __XMLS_H__

/*! @} **/




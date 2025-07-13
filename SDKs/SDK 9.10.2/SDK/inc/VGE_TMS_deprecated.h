#ifdef __cplusplus
extern "C" {
#endif



/*! @addtogroup VGE_TMS
 * @{
	* @deprecated	VGE_TMS is deprecated since SDK 9.2. 	Use functions provided by system.
 **/
 

/*
======================================================================
					List of Defines
======================================================================
*/
#define TMS_SUCCESS				      1     /*!< The init/parsing/file creation is successful. */
#define TMS_INIT_ERROR		     	2     /*!< The number of TMS files to be added is larger than the maximum number of manageable TMS files. */
#define TMS_NOT_TMS_FILE	    	3     /*!< The file is not a member of the TMS downloading files list. */
#define TMS_FILE_CREATION_ERROR	4     /*!< An error occured during creation of the file. */
#define TMS_FILE_DOES_NOT_EXIST	7     /*!< The log file have not been created. */
#define TMS_OPEN_FILE_ERROR	   	8     /*!< A problem occured during the file reading. */
#define TMS_NOT_ENOUGH_SPACE	  10    /*!< There is not enough space on memory to read the file. */
#define TMS_ALREADY_EXIST		    11    /*!< The log file already exists. */
#define TMS_PARSE_PROBLEM		    12    /*!< A problem occured during the file parsing. */
#define TMS_FILE_INIT_ERROR		  13    /*!< An error occured during the deletion or the creation of the log file.   */
#define TMS_INVALID_PARAM	     	14    /*!< The file descriptor/ i_pcDataLog is NULL. */

#define MAX_TAG_LENGTH			    10     /*!< Maximum length of a tag. */
#define MAX_TAG_ELEMENT			    100    /*!< Maximum number of tags. */
#define MAX_LENGTH_FILE_NAME    32     /*!< Maximum length of a file name. */
	                                    
#define TMS_TAG_DATA			      0xFF00 /*!< Tag of the data element for TMS*/


/*
======================================================================
					    Type Definition
======================================================================
*/


/*! @deprecated Enumeration of the parsing types. */
typedef enum
{
	TMS_PARSE_1,		/*!<  ASCII, T=V ; + Comments				*/
	TMS_PARSE_2,		/*!<  ASCII , T=V ;							*/
	TMS_PARSE_3,		/*!<  ASCII, INI							*/
  TMS_PARSE_4,		/*!<  ASCII, EMV (T=V ; but V in binary)	*/
	TMS_PARSE_5			/*!<  BerTLV								*/
} TMS_e_Parsing_type  ;


/*! @deprecated Tag name type definition	*/
typedef unsigned char TMS_t_tag_elements[MAX_TAG_LENGTH]  ;


/*! @deprecated Data tags list	*/ 
typedef struct
{
	TMS_t_tag_elements sTagsElements[MAX_TAG_ELEMENT];	/*!<  Tables containing the tags	*/
	int iNumberOfTagsElements;													/*!<  Number of tags				*/
} TMS_t_tags_list  ;


/*! @deprecated TMS File descriptor	*/ 
typedef struct
{
	char sFileName[MAX_LENGTH_FILE_NAME];				 /*!<  Name of the TMS file								*/
	char sFileDescriptor[MAX_LENGTH_FILE_NAME];	 /*!<  Name of the file descriptor						*/
	TMS_t_tags_list xListOfTags;				   			 /*!<  The TAG list										*/
	void * xDataStruct;							       			 /*!<  A pointer to the corresponding data structure		*/
	int nLengthDataStruct;					      			 /*!<  The length of the corresponding structure			*/
	TMS_e_Parsing_type iParsingMethode;					 /*!<  The parsing methode								*/
} TMS_t_file_descriptor  ;

/*
======================================================================
					    Functions Definition
======================================================================
*/

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	 	This function defines and initializes, for a given application, 
				the whole set of files that will be downloaded from the TMS. 
 *	@param[in]		i_pxFileDescriptor		Pointer to the list of TMS file descriptors. 
 *	@param[in]		i_nNbElement					Number of TMS files to be downloaded.
 *
 *	@return 
 *	- #TMS_SUCCESS		
 *	- #TMS_INIT_ERROR		
 *	- #TMS_INVALID_PARAM
 *
 *	@note 
 *	Each file is described by a set of parameters contained in TMS_t_file_descriptor structure :
 *	-	TMS file name.
 *	-	TMS file descriptor name.
 *	-	The TAG list.
 *	-	A pointer to the structure of corresponding data.
 *	-	The size of the corresponding data.
 *	-	Method of Parsing.  
 *
 *	@sa 
 *	- @link TMS_t_file_descriptor File Descriptor structure@endlink
 *	- @link TMS_e_Parsing_type Parsing type enumeration@endlink
 * 
 *	@link VGE_TMS Back to top @endlink
**/
#ifndef _DEPRECATED_AVL_SDK090200_
#define TMS_InitParametersFile ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int TMS_InitParametersFile
(	
	TMS_t_file_descriptor* i_pxFileDescriptor,	
	int i_nNbElement
) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief 	This function allows the start-up of the parsing process for a specified parameters file.

 *	@param[in]		pFile				Pointer to the file to parse.
 *	@return 
 *	- #TMS_SUCCESS			
 *	- #TMS_PARSE_PROBLEM		
 *	- #TMS_OPEN_FILE_ERROR	
 *	- #TMS_NOT_ENOUGH_SPACE	
 *	- #TMS_NOT_TMS_FILE		
 *	- #TMS_INVALID_PARAM
 *
 *	@link VGE_TMS Back to top @endlink		
**/
#ifndef _DEPRECATED_AVL_SDK090200_
#define TMS_StartParsingParamFile ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int TMS_StartParsingParamFile 
( 
	S_FILE *pFile
) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief 	This function enables an application to create a log file, if it does not already exist.

 *	@return 
 *	- #TMS_SUCCESS			
 *	- #TMS_ALREADY_EXIST			
 *	- #TMS_FILE_CREATION_ERROR	
 *	@note The log file is created in the path "\HOST" with the name "@c LogFile.log"
 *
 *	@link VGE_TMS Back to top @endlink
**/
#ifndef _DEPRECATED_AVL_SDK090200_
#define TMS_CreateLogFile ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int TMS_CreateLogFile
(	
	void
) MACRO_DEPRECATED ;
#endif

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	This function writes in the log file and adds a line.
 *  Its content depends on the application needs (For instance a list of information to be journalized : date, hour, state, number of transactions 
					carried out, number of transactions accepted, number of transactions refused, etc ...).
 
 *	@param[in]		i_pcDataLog				Pointer to the data to be added in the log file.
 *	@param[in]		i_unLenDataLog		Length of the data to be added in the log file.
 *	@return 
 *	- #TMS_SUCCESS		
 *	- #TMS_FILE_DOES_NOT_EXIST	
 *	- #TMS_INVALID_PARAM		
 *	- #TMS_OPEN_FILE_ERROR	
 *	- #TMS_NOT_ENOUGH_SPACE	
 *
 *	@link VGE_TMS Back to top @endlink
**/
#ifndef _DEPRECATED_AVL_SDK090200_
#define TMS_AddLineLog ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int TMS_AddLineLog
(	
	char * i_pcDataLog,
	unsigned int i_unLenDataLog
) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	This function initializes the contents of the Log file.

 *	@return 
 *	- #TMS_SUCCESS		
 *	- #TMS_FILE_DOES_NOT_EXIST	
 *	- #TMS_FILE_INIT_ERROR	
 *	@note Since the log file is shared between all the applications in the terminal, the initialization will delete all the information added by the other applications.
 *
 *	@link VGE_TMS Back to top @endlink
**/
#ifndef _DEPRECATED_AVL_SDK090200_
#define TMS_InitLogFile ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int TMS_InitLogFile
(	
	void
)  MACRO_DEPRECATED ;
#endif
/*! @} **/


#ifdef __cplusplus
}
#endif

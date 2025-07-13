#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup VGE_FMG
	* @{
	
**/		

/*
======================================================================
					List of Defines
======================================================================
*/
#define FMG_SUCCESS					    	10					/*!< The FMG service is successful*/
#define FMG_FILE_DOES_NOT_EXIST		11					/*!< Can't find the file : file is inexistant*/
#define FMG_FILE_ALREADY_EXIST		12          /*!< The file already exists */
#define FMG_BAD_RECORD_TYPE				13					/*!< Bad record type	: The input record type is not a member of the FMG_eRecordType enumeration*/
#define FMG_BAD_CHECKSUM_TYPE			14					/*!< Bad checksum type: The input checksum type is not a member of the FMG_eChecksumState enumeration*/
#define FMG_BAD_FILE_TYPE				  15					/*!< Bad file type		: The input file type is not a member of the FMG_e_file_type enumeration*/
#define FMG_BAD_RECORD_POSITION	  16					/*!< Bad Position		  : The input position type is not a member of the FMG_e_record_pos enumeration*/
#define FMG_BAD_CREATION_PARAM		17					/*!< Bad creation type: The input creation type is not a member of the FMG_eCreationType enumeration*/
#define FMG_BAD_PATH					    18			    /*!< Bad path name*/

#define FMG_OPEN_FILE_PROBLEM			19					/*!< An error occurred during file opening	*/
#define FMG_CREATE_FILE_PROBLEM		20					/*!< An error occurred during file creation*/
#define FMG_DELETE_FILE_PROBLEM		21					/*!< An error occurred during deletion of file*/
#define FMG_NB_FILE_PROBLEM				22					/*!< The maximal file number, FILE_MAX_NUMBER, is reached*/

#define FMG_MANAGEMENT_ERROR			23		     	/*!< File Management Error*/
#define FMG_ADD_RECORD_ERROR			24					/*!< An error occurred during adding of a record*/
#define FMG_READ_RECORD_ERROR			25					/*!< An error occurred during reading of a record	*/
#define FMG_DELETE_RECORD_ERROR		26					/*!< An error occurred during deleting of a record*/

#define FMG_CHECKSUM_PROBLEM			27					/*!< An error occurred while verifying the file checksum*/
#define FMG_CORRUPTED_FILE				28					/*!< The file is corrupted : bad checksum	*/
#define FMG_CORRUPTED_RECORD			29					/*!< The record is corrupted : bad checksum	*/
	
#define FMG_INIT_OK						    30					/*!< FMG intialisation is successful		*/
#define FMG_INIT_KO						    31					/*!< FMG intialisation failed		*/

#define MAX_FMG_FILE_PATH				FS_DISKNAMESIZE		/*!< Maximal char number for DMG file path	*/
#define	MAX_FMG_FILE_NAME				FS_FILENAMESIZE		/*!< Maximal char number for DMG file name	*/

#define FILE_MAX_NUMBER           100							/*!< Maximal File number	*/

/*
======================================================================
			Data Structures Definition
======================================================================
*/


/*! @brief Enumeration of the file creation mode	*/
typedef enum
{
	FMGPathAndName,
	FMGFileType
}FMG_eCreationType;

/*! @brief Enumeration of the file type when the creation mode is FMGFileType */
typedef enum
{
	FMGBatch,
	FMGBlackList,
	FMGLog
} FMG_e_file_type ;


/*! @brief Enumeration of the record Type : Fixed or variable length */
typedef enum
{
 	FMG_FIXED_LENGTH,
	FMG_VARIABLE_LENGTH
} FMG_eRecordType;


/*! @brief Enumeration of the checksum control state */
typedef enum
{
	FMG_WITHOUT_CKECKSUM,
	FMG_WITH_CKECKSUM
} FMG_eChecksumState;


/*! @brief Enumeration of the record position in the file */
typedef enum
{
	FMGBegin,
	FMGMiddle,
	FMGEnd
} FMG_e_record_pos;


/*! @brief This structure describes a file created with the FMG module	*/
typedef struct
{
	FMG_eCreationType eCreationType;  							/*!< File creation type*/
	unsigned char ucFilePath[MAX_FMG_FILE_PATH+1];	/*!< Path name*/
	unsigned char ucFileName[MAX_FMG_FILE_NAME+1];	/*!< File name*/
	FMG_e_file_type eFileType;											/*!< File type : Batch, BlakList or Log. Used only when eCreationType==FMGFileType	*/
} FMG_t_file_info;



/*! @brief This structure allows to save information for each file created with the FMG module	*/
typedef struct
{
	char pcPathName[MAX_FMG_FILE_PATH+1]; /*!< Path name*/
	char PcFileName[MAX_FMG_FILE_NAME+1]; /*!< File name*/
	FMG_eRecordType  eRecordType;					/*!< File record type : Variable or fixed length	*/
	FMG_eChecksumState eChecksum;					/*!< File checksum control state : active or not	*/
}FMG_t_file_description;


/*! @brief Global structure containing informations about all the files created with the FMG module	*/
typedef struct
{
	unsigned int uiNbFile;																		/*!< Number of file created through the FMG module	*/
	FMG_t_file_description sFileDescription[FILE_MAX_NUMBER];	/*!< File description array containing a description for each file created through the FMG module	*/
}FMG_t_file_management;


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function initializes the file management (FMG) module.
 *
 *	@return
 *	- #FMG_INIT_OK / #FMG_SUCCESS				
 *	- #FMG_INIT_KO / #FMG_OPEN_FILE_PROBLEM	
 * @note This service must be called in the @c after_reset entry point.
 *		   All disks used in the application by the @b FMG library must be mounted before the call to the #FMG_Init() service.
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_Init(void);

/*! @brief This function enables the application to get the description about the files which are managed by the @b FMG library for the current application.
 *
 *	@param[out]	o_sFileManagement	Pointer on file table description.
 *  
 *	@return
 *	- @c  TRUE		  If success.
 *	- @c  FALSE		  If not.
 *
 *	@sa 
 *	- @link FMG_t_file_description File Description structure@endlink
 *	- @link FMG_t_file_management File Management structure@endlink
 *	
 *	@link VGE_FMG Back to top @endlink
 **/
Boolean FMG_GetFileDescription(FMG_t_file_management *  o_sFileManagement);


/*! @brief This function creates a file by indicating its name and its path.
 *
 * @param[in]		i_pcFilePath	: Pointer to the file path.
 * @param[in]   i_pcFileName	: Pointer to the file name.
 * @param[in]		i_eRecordType	: Record type : Fixed or variable length.
 * @param[in]		i_eCheckSum		: Checksum state.
 *	@return
 *	- #FMG_SUCCESS / #FMG_FILE_ALREADY_EXIST / #FMG_MANAGEMENT_ERROR
 *	- #FMG_CREATE_FILE_PROBLEM / #FMG_BAD_CHECKSUM_TYPE 
 *	- #FMG_BAD_RECORD_TYPE / #FMG_NB_FILE_PROBLEM
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_CreateFile(	char * i_pcFilePath,	char * i_pcFileName,	FMG_eRecordType i_eRecordType,FMG_eChecksumState i_eCheckSum);



/*! @brief This function deletes a file by indicating only its name and its path.
 *
 * @param[in]		i_pcFilePath	: Pointer to the file path.
 * @param[in]		i_pcFileName	: Pointer to the file name.
 *	@return
 *	- #FMG_SUCCESS / #FMG_MANAGEMENT_ERROR / #FMG_DELETE_FILE_PROBLEM		
 *	- #FMG_FILE_DOES_NOT_EXIST / #FMG_NB_FILE_PROBLEM
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_DeleteFile ( char * i_pcFilePath, char * i_pcFileName);


/*! @brief This function creates a file by indicating its type : @c BATCH, @c BLACKLIST or @c LOG.
 *
 * @param[in]		i_eFileType		: File type, enumerated in the FMG_e_file_type enumeration.
 * @param[in]   i_eRecordType	: Record type : Fixed or variable length.
 * @param[in]		i_eCheckSum		: Checksum state.

 *	@return
 *	- #FMG_SUCCESS	/ #FMG_FILE_ALREADY_EXIST / #FMG_MANAGEMENT_ERROR 
 *	- #FMG_CREATE_FILE_PROBLEM / #FMG_BAD_CHECKSUM_TYPE / #FMG_BAD_RECORD_TYPE
 *	- #FMG_NB_FILE_PROBLEM /#FMG_BAD_PATH /#FMG_BAD_FILE_TYPE
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_CreateFileType(	FMG_e_file_type  i_eFileType, 	FMG_eRecordType i_eRecordType,FMG_eChecksumState i_eCheckSum);



/*! @brief This function deletes a file by indicating only its Type : @c BATCH, @c BLACKLIST or @c LOG.
 *
 * @param[in]		i_eFileType		: File type, enumerated in the #FMG_e_file_type enumeration.
 *
 *	@return
 *	- #FMG_SUCCESS/ #FMG_MANAGEMENT_ERROR / #FMG_DELETE_FILE_PROBLEM
 *	- #FMG_NB_FILE_PROBLEM / #FMG_FILE_DOES_NOT_EXIST / #FMG_BAD_FILE_TYPE
 *	- #FMG_BAD_PATH	
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_DeleteFileType( FMG_e_file_type  i_eFileType);




/*! @brief This function is used to check the file coherence.
 *		   To enable this control the md5 check is used and the checksum value 
 *		   is added at the end of file (16 byte hash).
 *
 * @param[in]		i_pcFilePath	: Pointer to the file path.
 * @param[in]		i_pcFileName	: Pointer to the file name.
 *
 *	@return
 *	- #FMG_SUCCESS			
 *	- #FMG_CORRUPTED_FILE		
 *	- #FMG_OPEN_FILE_PROBLEM 
 *	- #FMG_CHECKSUM_PROBLEM	
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_CheckFileCoherence( char* 	i_pcFilePath, char * 	i_pcFileName);



/*! @brief This function is used to check the record coherence.
 *		   To enable this control the md5 check is used and the cheksum value 
 *		   is compared with i_pcChecksumValue (16 byte hash).
 *
 * @param[in]		i_pvDataRecord		  :	Pointer to the record.
 * @param[in]		i_lDataRecordLength	:	Record length.
 * @param[in]		i_pcChecksumValue	  :	Md5 checksum value to compare with the calculed one.
 *
 *	@return
 *	- #FMG_SUCCESS			
 *	- #FMG_CORRUPTED_RECORD	
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_CheckRecordCoherence(	void * 	i_pvDataRecord,	long	i_lDataRecordLength ,char * i_pcChecksumValue);

/*! @brief This function calculates the Md5 checksum of a data.
 *
 * @param[in]		i_pvDataRecord		:	Pointer to the record.
 * @param[in]		i_lDataRecordLength	:	Record length.
 * @param[in]		o_pcChecksumValue	:	Md5 checksum value
 
 *	@return None
 *
 *	@link VGE_FMG Back to top @endlink
 **/
void FMG_CalculMD5(	void * 	i_pvDataRecord,	long	i_lDataRecordLength ,char * o_pcChecksumValue);

/*! @brief This service enables to add a record in a file.
 *
 * @param[in]		i_psFileInfo		:	Pointer to the file information.
 * @param[in]		i_pvDataRecord		:	Pointer to the record to add.
 * @param[in]		i_lDataRecordLength	:	Length of the record.
 * @param[in]		i_eRecordPos		:	Position search mode : #FMGBegin, #FMGEnd or #FMGMiddle.
 * @param[in]		i_nPosition			:	The adding position in the file. This value is ignored when @a i_eRecordPos is set to #FMGBegin or #FMGEnd.
 *
 * @return
 *	- #FMG_SUCCESS / #FMG_OPEN_FILE_PROBLEM / #FMG_CORRUPTED_FILE		
 *	- #FMG_FILE_DOES_NOT_EXIST / #FMG_BAD_CHECKSUM_TYPE / #FMG_ADD_RECORD_ERROR 
 *	- #FMG_BAD_CREATION_PARAM / #FMG_BAD_FILE_TYPE / #FMG_BAD_RECORD_TYPE
 *	- #FMG_BAD_RECORD_POSITION
 *
 *  @note 
 *       - This function is also used for files created by indicating the Path and name and also for files created by indicating only the type.
 *       - The value of @a i_nIndex is ignored when @a i_eRecordPos is set to #FMGBegin or #FMGEnd.
 *
 *	@sa 
 *	- @link FMG_t_file_info File Info structure@endlink
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_AddRecord(	FMG_t_file_info * i_psFileInfo	, void * 	i_pvDataRecord,  long	i_lDataRecordLength, 
					FMG_e_record_pos	i_eRecordPos,	int	i_nPosition);



/*! @brief This function enables the modification of a record in a file.
 *
 * @param[in]		i_psFileInfo		:	Pointer to the file information.
 * @param[in]		i_pvDataRecord		:	Pointer to the record to modify.
 * @param[in]		i_lDataRecordLength	:	Length of the record.
 * @param[in]		i_eRecordPos		:	Position search mode : #FMGBegin, #FMGEnd or #FMGMiddle.
 * @param[in]		i_nIndex			:	Record Position in the file. This value is ignored when @a i_eRecordPos is set to #FMGBegin or #FMGEnd.
 *
 *	@return
 *	- #FMG_SUCCESS / #FMG_OPEN_FILE_PROBLEM / #FMG_CORRUPTED_FILE	
 *	- #FMG_FILE_DOES_NOT_EXIST / #FMG_BAD_CHECKSUM_TYPE / #FMG_ADD_RECORD_ERROR 
 *	- #FMG_BAD_CREATION_PARAM / #FMG_BAD_FILE_TYPE / #FMG_BAD_RECORD_TYPE
 *	- #FMG_BAD_RECORD_POSITION
 * @note 
 *       - This function is also used for files created by indicating the Path and name and also for files created by indicating only the type.
 *       - The value of @a i_nIndex is ignored when @a i_eRecordPos is set to #FMGBegin or #FMGEnd.
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_ModifyRecord (FMG_t_file_info * i_psFileInfo, void * 	i_pvDataRecord, long	i_lDataRecordLength, 
					  FMG_e_record_pos	i_eRecordPos,int	i_nIndex);


/*! @brief		This function enables the record reading from a file.
 *
 * @param[in]		    i_psFileInfo		:	Pointer to the file information.
 * @param[out]		  o_pvDataRecord		:	Pointer to the record to read.
 * @param[in, out]	io_plDataRecordLength:	Pointer to the variable containing the record Length. This value is used as input only when 
 *											                  the file is a fixed length record, otherwise, it is used as output.
 * @param[in]		    i_eRecordPos		:	Position search mode : #FMGBegin, #FMGEnd or #FMGMiddle.
 * @param[in]		    i_nIndex			:	Record Position in the file. This value is ignored when @a i_eRecordPos is set to #FMGBegin or #FMGEnd.
 *
 *	@return
 *	- #FMG_SUCCESS / #FMG_OPEN_FILE_PROBLEM / #FMG_CORRUPTED_FILE				
 *	- #FMG_FILE_DOES_NOT_EXIST / #FMG_BAD_CHECKSUM_TYPE / #FMG_READ_RECORD_ERROR 
 *	- #FMG_BAD_CREATION_PARAM / #FMG_BAD_FILE_TYPE / #FMG_BAD_RECORD_TYPE
 *	- #FMG_BAD_RECORD_POSITION
 * @note 
 *       - This function is also used for files created by indicating the Path and name and also for files created by indicating only the type.
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_ReadRecord (FMG_t_file_info * i_psFileInfo, void * 	o_pvDataRecord, long	* io_plDataRecordLength,
	FMG_e_record_pos	i_eRecordPos, int	i_nIndex);


/*! @brief		This function enables the record deletion from a file.
 *
 * @param[in]		i_psFileInfo		:	Pointer to the file informations.
 * @param[in]	  i_lDataRecordLength :	Record length. This value is used only when the file is a fixed length record, otherwise, this value is ignored.
 * @param[in]		i_eRecordPos		:	Position search Mode : #FMGBegin, #FMGEnd or #FMGMiddle.
 * @param[in]		i_nPosition			:	Record Position in the file. This value is ignored when @a i_eRecordPos is set to #FMGBegin or #FMGBegin.
 *
 *	@return
 *	- #FMG_SUCCESS / #FMG_OPEN_FILE_PROBLEM / #FMG_CORRUPTED_FILE 				
 *	- #FMG_FILE_DOES_NOT_EXIST / #FMG_BAD_CHECKSUM_TYPE / #FMG_DELETE_RECORD_ERROR 
 *	- #FMG_BAD_CREATION_PARAM / #FMG_BAD_FILE_TYPE / #FMG_BAD_RECORD_TYPE
 *	- #FMG_BAD_RECORD_POSITION	
 * @note 
 *       - This function is also used for files created by indicating the Path and name and also for files created by indicating only the type.
 *       - The value of i_lDataRecordLength is ignored when the file type is variable Length record.
 *       - The value of i_nPosition is ignored when i_eRecordPos is set to #FMGBegin or #FMGEnd.
 *
 *	@link VGE_FMG Back to top @endlink
 **/
int FMG_DeleteRecord(	FMG_t_file_info * i_psFileInfo, FMG_e_record_pos	i_eRecordPos , long i_lDataRecordLength, int	i_nPosition );

/*! @} **/

#ifdef __cplusplus
}
#endif

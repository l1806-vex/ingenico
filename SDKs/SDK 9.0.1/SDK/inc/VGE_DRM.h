#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup VGE_DRM
 * @{
 	
 *
 **/
/*
======================================================================
					List of Defines
======================================================================
*/

#define DRM_SUCCESS				100  								/*!< The @b DRM service is successful	*/ 
#define DRM_INIT_OK				101  								/*!< Successful first initialization	*/ 
#define DRM_INIT_KO				102  								/*!< Initialization failure			*/
#define DRM_STATUS_ERROR	103 								/*!< Get DRM status failure			*/
#define DRM_SAVE_ERROR		104 								/*!< Save data failure					*/
#define DRM_DELETE_ERROR	105  								/*!< Delete data failure				*/
#define DRM_RESTORE_ERROR	106  								/*!< Restore data failure				*/ 
#define DRM_LABEL_ERROR		107	 								/*!< Data label is not correct; or the input label was not found in the @b DRM label list.		*/

#define NB_DATA_MAX 256			  								/*!< Maximum number of data to save (number of items)*/
#define MAX_DRM_FILE_PATH		FS_DISKNAMESIZE 	/*!< Maximum DRM PathName length	*/
#define	MAX_DRM_FILE_NAME		FS_FILENAMESIZE 	/*!< Maximum DRM FileName length	*/ 


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Structure describing the status of the <b>Data Recover Management module (DRM)</b>. **/
typedef struct
{
	char		  pcPathName[MAX_DRM_FILE_PATH+1];	/*!< PathName  used for saving data		*/
	char		  pcFileName[MAX_DRM_FILE_NAME+1];	/*!< FileName used for saving data			*/
	unsigned int  uiDiskSize;										/*!< Size of the disk used to save data				*/	
	unsigned int  uiFileSize;										/*!< Current size of the file used for saving data	*/	
	unsigned int  uiNbDataSaved;								/*!< Number of data already saved					*/ 
	unsigned int  piIdDataList[NB_DATA_MAX];		/*!< List of the saved data labels					*/ 
} DRM_t_drm_status;



/*
======================================================================
			Functions Definition
======================================================================
*/

/*!
* @brief	This function initializes the <b>Data Recover Management module (DRM)</b>.
* @param[in]		i_pcPathName : PathName of the saved data file.
* @param[in]		i_pcFileName : FileName of the saved data file.
* @param[in]		i_nDiskSize  : Size of the disk containing the saved data file.
* @return		
* - #DRM_SUCCESS; or 
* - #DRM_INIT_OK; or	
* - #DRM_INIT_KO		
* @note This service must be used before the call to any other function of @b DRM library. 	
*
* @link VGE_DRM Back to top @endlink	
*/
int DRM_Init (	char * i_pcPathName,	char * i_pcFileName,	unsigned int i_nDiskSize);


/*!
* @brief	This function gets the status of the @b DRM module: <i> FileName, PathName, File size, Number of data saved, Data ID list</i>

* @param[out]	o_sDrmStatus  : Structure containing DRM Status.
*
* @return		
* - #DRM_SUCCESS; or			
* - #DRM_STATUS_ERROR
* @sa 
* - @link DRM_t_drm_status Status structure@endlink 
*
* @link VGE_DRM Back to top @endlink	
*/
int DRM_GetStatus (DRM_t_drm_status *o_sDrmStatus);


/*!
* @brief	This function saves a data value in the flash memory and enables the recovery of its contents.

* @param[in]		i_uiLabelData	:	Id of the data to be saved in the flash memory.
* @param[in]		i_pvData		:	Pointer to the data to be saved.
* @param[in]		i_nSizeData		:	Size of the data to be saved.
*
* @return		
* - #DRM_SUCCESS; or		
* - #DRM_SAVE_ERROR		
*
* @link VGE_DRM Back to top @endlink	
*/
int DRM_SaveData (	unsigned int  i_uiLabelData,	void * i_pvData,	unsigned int i_nSizeData);


/*!
* @brief	This function deletes a data value (already saved by #DRM_SaveData) from the flash memory and disables the recovery of its contents 

* @param[in]	i_uiLabelData : Id of the data to delete from the flash memory.
*
* @return		
* - #DRM_SUCCESS; or			
* - #DRM_LABEL_ERROR; or		
* - #DRM_DELETE_ERROR	
*
* @link VGE_DRM Back to top @endlink		
*/
int DRM_DeleteData (unsigned int  i_uiLabelData);


/*!
* @brief	This function enables the recovery of the data value saved by #DRM_SaveData in the flash memory.

* @param[in]		i_uiLabelData	:	Id of the data to recover.
* @param[out]		o_pvData	:     Pointer to the recovered data
* @param[out]		o_pnSizeData	:	Size of the the recovered data.
*
* @return		
* - #DRM_SUCCESS; or			
* - #DRM_LABEL_ERROR; or	
* - #DRM_RESTORE_ERROR	
*
* @link VGE_DRM Back to top @endlink	
*/
int DRM_RestoreData ( unsigned int  i_uiLabelData , void * o_pvData,  int* o_pnSizeData);

/*! @} **/

#ifdef __cplusplus
}
#endif

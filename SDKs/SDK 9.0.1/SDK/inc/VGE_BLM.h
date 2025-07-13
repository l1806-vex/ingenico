#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup VGE_BLM
 * @{
 	
 **/

/*
======================================================================
					List of Defines		
======================================================================
*/

#define BLM_SUCCESS											60			/*!< The @b BLM service is performed with success.*/
#define BLM_NOT_EXPIRED									61			/*!< The input date fits within the Activation-Expiration black list dates range.*/		
#define BLM_EXPIRED											62			/*!< The black list is expired regarding the input date.*/			
#define BLM_BLACK_LIST_DOES_NOT_EXIST		63			/*!< The black list file does not exist. */			
#define BLM_DELETE_ERROR								64			/*!< An error occurs when removing the element. */		
#define BLM_ADD_ERROR										65			/*!< The black list is full (maximal elements number is reached). */					
#define BLM_ELT_FOUND										66			/*!< The PAN element exists in the black list. */					
#define BLM_ELT_NOT_FOUND								67			/*!< The PAN element does not exist in the black list. */				
#define BLM_INVALID_PARAM								68			/*!< The input parameters are invalid. */				
#define	BLM_CREATE_ERROR								69			/*!< The black list creation failed (due to file management error). */				
#define BLM_ELT_DOES_NOT_EXIST					70			/*!< The input parameters are invalid. */		
#define BLM_ELT_EXIST										71			/*!< The black list element does not exist. */									
#define BLM_INVALID_RANGE								72			/*!< The range is invalid. */						
#define BLM_SORT_ERROR									73			/*!< An error occurs when the call back to the sort function is performed. */					
#define BLM_UPDATE_ERROR								74			/*!< An error occurs when updating the black list file. */					
#define	BLM_INVALID_DATE								75			/*!< The current date is older than the activation date.	*/
#define BLM_DELETE_BL_ERROR							76			/*!< An error occurs when deleting the black list file. */					
#define BLM_MAX_BL_ELT									1000    /*!< Max number of elements in the blacklist */
#define BLM_MAX_LEN_PAN									20      /*!< Maximum length of the primary account number */
#define BLM_MAX_LEN_RANGE								20      /*!< Maximum length of the elements of the range */
#define BLM_PAN_TYPE										0x01    /*!< Record is a PAN type */
#define BLM_RANGE_TYPE									0x02    /*!< Record is a Range type */


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief PAN structure. 
*/
typedef struct
{
	unsigned char ucPan [BLM_MAX_LEN_PAN] ;									/*!< Primary Account Number. */	
} BLM_t_pan;


/*! @brief Range structure. */
typedef struct
{
	unsigned char ucRangeMin [BLM_MAX_LEN_RANGE] ;					/*!<	The first element of the ranges	*/
	unsigned char ucRangeMax [BLM_MAX_LEN_RANGE] ;					/*!< The last element of the ranges. */	
} BLM_t_range;


/*! @brief Black List Element structure. 
 *  */
typedef struct
{
	unsigned char	ucRecordType ;														/*!< Type of recording 
																													- #BLM_PAN_TYPE 
																													- #BLM_RANGE_TYPE */						
	union
	{
		BLM_t_pan	sPan ;
		BLM_t_range	sRange ;
	} BLM_u_elt_bl;																					/*!< A union between a PAN and a range. */	
} BLM_t_elt_black_list;


/*! @brief Black List structure.
	 */
typedef struct
{
	unsigned long 		ulNbElements ;												/*!<	Number of elements in the black list	*/
	DATE				sActivationDate ;														/*!<	Activation date							*/
	DATE				sExpirationDate ;														/*!<	Expiration date							*/
	int					iVersionNumber ;														/*!<	Black list version number				*/
	BLM_t_elt_black_list		sBLTable [BLM_MAX_BL_ELT] ;			/*!<	Black List Elements Table				*/
} BLM_t_black_list ;


/*! @brief Sort function type. */
typedef int (* BLM_Sorting) ( BLM_t_black_list * io_psBlackList);

/*! @brief Find function type. */
typedef int (* BLM_FindElement) ( BLM_t_black_list* io_psBlackList, BLM_t_pan *i_psPan,
								 int * o_pnPostion);


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief	This function allows the creation of the Black List.
 * @brief It accepts as input the sorting and search methods that will be used to add and to search elements into the black list.

 *	@param[in]		i_pfSort		Pointer to the sorting function used to sort Black List elements.
 *	@param[in]		i_pfFindElt		Pointer to the search function used to search for a PAN element in the black list.
 *	@return
 *	- #BLM_SUCCESS; or
 *	- #BLM_CREATE_ERROR; or
 *	- #BLM_INVALID_PARAM
 * 
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_CreateBlackList(BLM_Sorting i_pfSort,BLM_FindElement i_pfFindElt);


/*! @brief	This function deletes the black list file from the system.
 *	@return
 *	- #BLM_SUCCESS; or
 *	- #BLM_DELETE_BL_ERROR; or
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 * 
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_DeleteBlackList(void);


/*! @brief	Allows the initialization of the black list with the input parameters: the validity dates and the version number.

 *	@param[in]		i_sActivationDate	The activation date of the black list.
 *	@param[in]		i_sExpirationDate	The expiration date of the black list.
 *	@param[in]		i_nVersionNumber	The version number of the black list.
 *	@return
 *	- #BLM_SUCCESS; or
 *	- #BLM_UPDATE_ERROR; or
 *	- #BLM_INVALID_PARAM	This is the case when : 
											- The activation or the expiration dates are invalid dates.
											- The activation date is posterior to the expiration date.
											- The version number is negative.
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 * 
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_InitBlackList(DATE i_sActivationDate,DATE i_sExpirationDate,int i_nVersionNumber);


/*! @brief	This function checks the existence of a PAN in the Black List.
 *	@param[in]		i_psPan				The PAN to check existence of in the black list / Pointer to the PAN to search.
 *	@return
 *	- #BLM_ELT_FOUND; or
 *	- #BLM_ELT_NOT_FOUND; or
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 * @note A call back to the Find function defined in #BLM_CreateBlackList is performed to search the PAN in the black list table.
 *
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_CheckExistenceInBL(	BLM_t_pan *i_psPan);


/*! @brief	This function allows the addition of a PAN or a range to the black list.

 *	@param[in]	i_psEltBlackList		The PAN or the range to add / Pointer to the PAN or to the RANGE to add.
 *	@return
 *	- #BLM_SUCCESS; or
 *	- #BLM_INVALID_RANGE; or
 *	- #BLM_ELT_EXIST; or			
 *	- #BLM_ADD_ERROR; or		
 *	- #BLM_UPDATE_ERROR; or
 *	- #BLM_SORT_ERROR; or
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 * @note A call back to the sort function defined in #BLM_CreateBlackList is performed to insert the new element in the black list table.
 * @sa 
 * - @link BLM_t_elt_black_list Black List Element structure@endlink
 *
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_AddElementInBL(	BLM_t_elt_black_list* i_psEltBlackList);


/*! @brief	This function allows to remove a PAN or a range from the black list.

 *	@param[in]	i_psEltBlackList		The PAN or the range to remove / Pointer to the PAN or to the RANGE to delete.
 *	@return
 *	- #BLM_SUCCESS; or
 *	- #BLM_ELT_DOES_NOT_EXIST; or
 *	- #BLM_DELETE_ERROR; or
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 * @sa 
 * - @link BLM_t_elt_black_list Black List Element structure@endlink
 * 
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_DeleteElementFromBL(BLM_t_elt_black_list* i_psEltBlackList);


/*! @brief	This function allows the modification of the black list temporal validity.
		@brief The black list temporal validity is identified by the activation and expiration dates.

 *	@param[in]		i_sActivationDate		The new activation date of the black list
 *	@param[in]		i_sExpirationDate		The new expiration date of the black list 
 *	@return
 *	- #BLM_SUCCESS; or
 *	- #BLM_UPDATE_ERROR; or
 *	- #BLM_INVALID_PARAM; or	
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_ModifyValidityOfBL(DATE i_sActivationDate,DATE i_sExpirationDate);


/*! @brief	This function checks the validity of the black list regarding the input date.

 *	@param[in]		i_sCurrentDate		The current date.
 *	@return
 *	- #BLM_EXPIRED; or
 *	- #BLM_NOT_EXPIRED; or
 *	- #BLM_INVALID_DATE; or
 *	- #BLM_INVALID_PARAM	; or
 *	- #BLM_BLACK_LIST_DOES_NOT_EXIST
 * 
 *
 * @link VGE_BLM Back to top @endlink
**/
int BLM_VerifyValidityOfBL(DATE i_sCurrentDate);



/*! @brief	This function allows to print the diagnostic concerning the black list.
 *
 * @link VGE_BLM Back to top @endlink
**/
void BLM_PrintDiagOfBL(void);


/*! @} **/

#ifdef __cplusplus
}
#endif

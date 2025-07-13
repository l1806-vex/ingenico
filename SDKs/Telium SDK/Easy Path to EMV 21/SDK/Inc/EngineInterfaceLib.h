/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \addtogroup EngineFunctions
//! \{

//! \brief Free all the buffers used to communicate with EMV ENGINE.
void Engine_FreeMemory(void);

//! \brief Ask EMV ENGINE to perform a transaction.
//! \param hInputTlvTree Contains input parameters:
//! - \ref TAG_ENG_APPLI_SEL_ALREADY_DONE : 0x01 if the application selection has already been done by the Telium Manager, 0x00 (default) otherwise.
//! - \ref TAG_ENG_CUSTOM_APPLI_TYPE : is the application type (on 2 bytes) of the CUSTOM application. Required to call the callback services. If not specified, the historical application type 0x0051 is used.
//! - any other tag (transaction amount, ...).
//! \param pOutputTlvTree Contains output tags (empty for now).
//! \return Any \a ERR_ENG_xxx value. See \ref EngineErrors.
//! \remarks This function runs a state machine that is described here: \ref EngineDoTransactionFlow.
int Engine_DoTransaction(const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE* pOutputTlvTree);

//! \brief Ask EMV ENGINE to resume the previously interrupted transaction.
//! \param hInputTlvTree Contains input parameters.
//! \param pOutputTlvTree Contains output tags (empty for now).
//! \return Any \a ERR_ENG_xxx value. See \ref EngineErrors.
int Engine_ResumeTransaction(const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE* pOutputTlvTree);

//! \brief Ask EMV ENGINE to read the transaction log from a card.
//! \param hInputTlvTree Contains input parameters (card insertion timeout, ...).
//! - \ref TAG_ENG_CUSTOM_APPLI_TYPE : is the application type (on 2 bytes) of the CUSTOM application. Required to call the callback services. If not specified, the historical application type 0x0051 is used.
//! - any other tag (transaction amount, ...).
//! \param pOutputTlvTree Contains output tags (empty for now).
//! \return Any \a ERR_ENG_xxx value. See \ref EngineErrors.
int Engine_DoReadTransactionLog(const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE* pOutputTlvTree);

/*! \brief Set the global parameters used when Application Selection is performed by the manager.
\param hInputTlvTree Contains input parameters. It can contain the tags \ref TAG_USE_PSE and/or \ref TAG_PSE_ALGO (\ref PSE_NORESELECT or \ref PSE_RESELECT).
\return Any \a ERR_ENG_xxx value. See \ref EngineErrors.
\remarks Example:
\code
TLV_TREE_NODE hTlvTree;
int nResult;
unsigned char ucPseMode;

hTlvTree = TlvTree_New(0);
if (hTlvTree == NULL)
	return FALSE;

// Disable the PSE
ucPseMode = FALSE;
if (TlvTree_AddChild(hTlvTree, TAG_USE_PSE, &ucPseMode, sizeof(ucPseMode)) == NULL)
{
	TlvTree_Release(hTlvTree);
	return FALSE;
}

nResult = Engine_SetGlobalParameters(hTlvTree);
TlvTree_Release(hTlvTree);

return TRUE;
\endcode
*/
int Engine_SetGlobalParameters(const TLV_TREE_NODE hInputTlvTree);

//! \brief Retrieves the value of some tags.
//! \param nNumOfTags Number of tags contained in \a pTagsToGet.
//! \param pTagsToGet An array of unsigned long that contains the tags to retrieve the value.
//! \return A TlvTree that contains the requested tags, or NULL if an error occurred. Note that the caller must release the TlvTree.
TLV_TREE_NODE Engine_GetDataElements(int nNumOfTags, const unsigned long* pTagsToGet);

//! \brief Retrieves the value of some proprietary tags read during Application Selection.
//! \param nNumOfTags Number of tags contained in \a pTagsToGet.
//! \param pTagsToGet An array of unsigned long that contains the tags to retrieve the value.
//! \return A TlvTree that contains the requested tags, or NULL if an error occurred. Note that the caller must release the TlvTree.
TLV_TREE_NODE Engine_GetProprietaryDataElements(int nNumOfTags, const unsigned long* pTagsToGet);

//! \brief Retrieves the value of a proprietary tag read during Application Selection.
//! \param ulTagToGet The tag to retrieve the value.
//! \return A TlvTree that contains the requested tag, or NULL if an error occurred. Note that the caller must release the TlvTree.
TLV_TREE_NODE Engine_GetDataElement(unsigned long ulTagToGet);

//! \brief Retrieves the \a nCmdNumber command sent to the card and its response.
//! \param nCmdNumber Index of the command, starting from 0.
//! \return A TlvTree that contains the command and the response.
TLV_TREE_NODE Engine_GetCommand(int nCmdNumber);

//! \brief Retrieves the processing time used to perform Offline Data Authentication.
//! \return A TlvTree that contains the processing time used to perform Offline Data Authentication.
TLV_TREE_NODE Engine_GetODATime(void);

//! \brief Clears all the data related to the last transaction.
//! \return Any \a ERR_ENG_xxx value. See \ref EngineErrors.
//! \remarks To be PA-DSS compliant, the application must always call this function as soon as possible after a transaction.
int Engine_ClearTransactionData(void);

//! \brief Retrieves the value of a tag.
//! \param ulTagToGet The tag to retrieve the value.
//! \return A TlvTree that contains the requested tag, or NULL if an error occurred. Note that the caller must release the TlvTree.
TLV_TREE_NODE Engine_GetProprietaryDataElement(unsigned long ulTagToGet);

//! \}

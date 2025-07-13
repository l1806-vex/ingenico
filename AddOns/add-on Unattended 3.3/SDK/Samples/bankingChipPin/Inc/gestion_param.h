/**
* \file gestion_param.h
* \brief This module contains the functions needed for parameters management.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef CU_GEST_PARAM_H
#define CU_GEST_PARAM_H

//! \defgroup Group_param Parameters management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define TRUE						1
#define FALSE						0


//! \defgroup selectMARK Mark selection for static array or file access
//! @{

#define C_TRACE_ALL_CHILD			0			//!< All tags in all children will be set in file.
#define C_TRACE_MARK				1			//!< All tags with the marks will be set in file.
#define C_TRACE_WITHOUT_MARK		2			//!< All tags without the marks (used by parameters management) will be set in file.
#define C_TRACE_ONE_TAG             3			//!< One type of tag will be concerned by the command.

//! @} // end of selectMARK


// Array for parameters serialisation
#define C_PUC_BUFFER_SIZE			32000		//!< Array size to store data read (or to write) from (in) a file

// Array to memorise activ mark
#define C_NB_MAX_MARK				100			//!< Maximum mark number selected.


// Tool for tag management
//! \defgroup BooleanTag Tag management : boolean type
//! @{

#define NONE						"NONE"		//!< Value used in global parameter file EMVCUST.PAR.
#define NO							"NO"		//!< NO value for a parameter of file EMVCUST.PAR. 0 is also used.
#define YES							"YES"		//!< YES value for a parameter of file EMVCUST.PAR. 1 is also used.

//! @} // end of BooleanTag


// Mark action type
//! \defgroup ActionType Mark action type
//! @{

#define C_SELECT					1			//!< Definition of Mark action select.
#define C_UNSELECT					2			//!< Definition of Mark action unselect.
#define C_SELECT_NEXT_CHILD			3			//!< Definition of Mark action select next child.
#define C_UNSELECT_CHILD			4			//!< Definition of Mark action unselect next child.

//! @} // end of ActionType


// Mark qualification
//! \defgroup ActionQual Mark qualification type
//! @{

#define C_MARK_NOT_DEFINE			1			//!< Definition of Mark qualification undefined.
#define C_MARK_NO_ACTIVATED			2			//!< Definition of Mark qualification not activated.
#define C_MARK_ACTIVATED			3			//!< Definition of Mark qualification activated.

//! @} // end of ActionQual


// Origin of each TLVTree
#define C_TAG_MAIN					0x0000		//!< Origin of each TLVTree.


// TreeType action
//! \defgroup BlockTreeType Definition of Tree types
//! @{

#define C_TREE_ALL					0			//!< Mark will be activated in all TLVTree : pTreeParam & pTreeDefault.
#define C_TREE_PARAM				1			//!< Mark will be activated only in pTreeParam TLVTree.
#define C_TREE_DEFAULT				2			//!< Mark will be activated only in pTreeDefault TLVTree.
#define C_TREE_PARAM_FIRST			3			//!< If present, mark will be activated in p_TreeParam TLVTree else it will be activated in pTreeDefault TLVTree.
#define C_TREE_APPLI				4			//!< Mark will be managed in pTreeAppli TLVTree.

//! @} // end of BlockTreeType


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This structure defines the data used for mark memorization.
typedef struct
{
	unsigned int  NumMark;						//!< Mark number.
	TLV_TREE_NODE ptr_node;						//!< TLV tree.
}Struct_Mark;

typedef struct
{
	unsigned long tag;
	unsigned char tagtype;
	unsigned char * Masq;
}Struct_TagList;

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

#ifndef FILE_H
extern TLV_TREE_NODE pTreeAppli;				//!< Node managed only by the application.
extern TLV_TREE_NODE pTreeParam;				//!< Node from param file parameters.
extern TLV_TREE_NODE pTreeDefault;				//!< Node from default parameters.
#endif /* FILE_H */


/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function initializes TLV tree used to store application tags.
//! \param[in,out] pTree : TLV tree to initialize : pTreeAppli, pTreeDefault, 
//! pTreeParam.
//! \return TLV tree initialized.
//===========================================================================
void CUPAR_InitTree(TLV_TREE_NODE * pTree);

//===========================================================================
//! \brief This function reads the default parameters (xml format).
//! \param[in] ptr_ac_x_ParamTable : parameter array.
//! \param[in] i_x_ArraySize : array size ...
//! \param[in] ul_x_MainTag : tag in the structure used for origin.
//! \return TLV tree containing the parameters read in table.
//===========================================================================
TLV_TREE_NODE PAR_ReadArray(char *ptr_ac_x_ParamTable, int i_x_ArraySize, unsigned long ul_x_MainTag);

//===========================================================================
//! \brief This function initializes one parameter file with default values.
//! The written file is a TLV tree serialized to binary format.
//! \param[in] p_node : TLV tree node in which the mark is searched.
//! \param[in] ptr_x_fileName : file name (text format) to update.
//! \param[in] i_x_Mark : mark to delimit the parameter set.
//===========================================================================
void CUPAR_WriteBinFile(TLV_TREE_NODE p_node, char *ptr_x_fileName, unsigned int i_x_Mark);

//===========================================================================
//! \brief This function initializes one parameter file with the values contained 
//! in the TLV tree given as input parameter.
//! \param[in] pTree : input TLV tree node to set in file.
//! \param[in] ptr_OutBuf : file name (text format) to update.
//! \return 
//! - 0 if successfull.
//! - 1 otherwise.
//===========================================================================
int CUPAR_WriteAllBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf);

//===========================================================================
//! \brief This function reads a file coded in TLVTree binary serialized format.
//! \param[out] p_node : output TLV tree updated with data read in file.
//! \param[in] pc_x_DirFile : file name to read to extract data.
//! \param[in] i_x_ParamFileType : file type to read :
//! - TLV_TREE_SERIALIZER_DEFAULT for TLV Tree Serial format.
//! - TLV_TREE_SERIALIZER_XML for xml format.
//! \return 
//! - 0 if successfull.
//! - 4 if an error occured at p_node deserialization.
//! - 5 if an error occured at opening of file pc_x_DirFile.
//===========================================================================
int CUPAR_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType);

//===========================================================================
//! \brief This function sets a "MARQ_xxx" data on each TLV tree node.
//! \param[in,out] p_node : TLV tree to update with data "MARQ_xxx".
//! \return Always 0.
//===========================================================================
int CUPAR_AddMarqs(TLV_TREE_NODE * p_node);

//===========================================================================
//! \brief This function resets the selected mark list.
//===========================================================================
void PAR_ResetMarkList(void);

//===========================================================================
//! \brief This function checks if the node given as parameter is a mark.
//! \param[in] pMark : TLV tree to test.
//! \return 
//! - Tag number if the node is a mark.
//! - 0 otherwise.
//===========================================================================
int PAR_IsAMark(TLV_TREE_NODE pMark);

//===========================================================================
//! \brief This function looks for a mark in TLV tree given as parameter.
//! \param[in] pTLVTree : input TLV tree in which the i_x_NumMark will be searched.
//! \param[in] i_x_NumMark : Mark number to find in input TLV tree.
//! \return 
//! - TLV tree starting with the mark given as parameter if found.
//! - NULL otherwise.
//===========================================================================
TLV_TREE_NODE PAR_FoundMarkInTree(TLV_TREE_NODE pTLVTree, unsigned int i_x_NumMark);

//===========================================================================
//! \brief This function looks for a mark in global parameter TLV tree. If the
//! mark is not found, it is searched in default parameter TLV tree.
//! \param[in] i_x_NumMark : Mark number to find.
//! \return 
//! - TLV tree starting with the mark given as parameter if found.
//! - NULL otherwise.
//===========================================================================
TLV_TREE_NODE PAR_FoundMark(unsigned int i_x_NumMark);

//===========================================================================
//! \brief This function performs a mark activation.
//! \param[in] i_x_NumMark : Mark number to find.
//! \param[in] i_x_TreeType : TLV tree type in which to search the mark : 
//! - \ref C_TREE_ALL.
//! - \ref C_TREE_PARAM.
//! - \ref C_TREE_DEFAULT.
//! - \ref C_TREE_PARAM_FIRST.
//! - \ref C_TREE_APPLI.
//! \return 
//! - 0 if mark found and activated.
//! - 1 otherwise.
//! \note This fonction doesn't manage several requests of a single mark.
//===========================================================================
int PAR_SelectMark(unsigned int i_x_NumMark, unsigned int i_x_TreeType);

//===========================================================================
//! \brief This function performs the father mark activation of the tag given 
//! as parameter.
//! \param[in] data : tag, length and value of tag to find in TLVTree.
//! \return
//! - Father mark if tag found and father mark found and activated.
//! - 0 otherwise. 
//===========================================================================
unsigned long PAR_SelectFatherMark(DataElementExt data);

//===========================================================================
//! \brief This function deletes a mark activation.
//! \param[in] i_x_NumMark : mark number.
//! \return
//! - 0 if mark found.
//! - 1 otherwise.
//===========================================================================
int PAR_DeSelectMark(unsigned int i_x_NumMark);

//===========================================================================
//! \brief This function tests if the mark given as input parameter is already 
//! selected.
//! \param[in] i_x_NumMark : mark number.
//! \return
//! - 1 if mark found.
//! - 0 otherwise.
//===========================================================================
int PAR_IsMarkSelected(unsigned int i_x_NumMark);

//===========================================================================
//! \brief This function selects each child mark of a father node.
//! \param[in] i_x_NumMark : mark number.
//! \param[in] uc_x_FirstAccess : first call to this function, first child 
//! must be selected.
//! \return
//! - Tag number selected.
//! - 0 otherwise.
//===========================================================================
int PAR_SelectNextMark(unsigned int i_x_NumMark, unsigned char uc_x_FirstAccess);

//===========================================================================
//! \brief This function deletes the mark given as input parameter and all its childs.
//! \param[in] i_x_NumMark : mark number.
//! \return always 0.
//===========================================================================
int PAR_DeleteMark(unsigned int i_x_NumMark);

//===========================================================================
//! \brief This function performs an action on the mark given as input parameter.
//! (allow to use or not parameters under this mark)
//! \param[in] i_x_NumMark : mark number to manage.
//! \param[in] y_x_ActionType : Mark action type :
//! - C_SELECT : select the mark given in parameter.
//! - C_UNSELECT : deselect the mark given in parameter.
//! - C_SELECT_NEXT_CHILD : select the following child from the mark given 
//! in parameter.
//! - C_UNSELECT_CHILD : select the child from the mark given in parameter.
//! \return 
//! - 0 if successfull.
//! - error code otherwise.
//===========================================================================
int PAR_MarkAction(unsigned int i_x_NumMark, unsigned char y_x_ActionType);

//===========================================================================
//! \brief This function allows to know all the informations on the mark
//! given as input parameter.
//! \param[in] i_x_NumMark : mark number on which to have informations.
//! \return The mark state : 
//! - C_MARK_NOT_DEFINE : mark undefined.
//! - C_MARK_NO_ACTIVATED : mark known and not activated.
//! - C_MARK_ACTIVATED : mark known and activated.
//===========================================================================
int PAR_MarkInfos(unsigned int i_x_NumMark);

//===========================================================================
//! \brief This function reads a parameter in param or default TLVTree structure.
//! \param[in] tag : tag number to find in TLVTree.
//! \param[out] data : DataElementExt structure containing tag informations read.
//! \return  
//! - 1 if tag found.
//! - 0 otherwise.
//===========================================================================
int PAR_ReadParameter(unsigned long tag, DataElementExt *data);

//===========================================================================
//! \brief This function reads a list of parameters in param or default TLVTree
//! structure.
//! \param[in] cst_tag_list : tag list.
//! \param[in] i_x_NbTag : tag number in list.
//! \param[out] phTLVTree : TLV tree updated with tags read.
//===========================================================================
void PAR_ReadParameterListTLVTree(const unsigned long cst_tag_list[], unsigned int i_x_NbTag, TLV_TREE_NODE *phTLVTree);

//===========================================================================
//! \brief This function updates a tag, or create it if necessary.
//! \param[in] tag : tag identifier .
//! \param[in] data : structure containing tag informations :
//! - tag id, 
//! - tag length, 
//! - tag value.
//! \return  
//! - 1 if tag updated or created.
//! - 0 otherwise.
//===========================================================================
int PAR_SetParameter(unsigned long tag, DataElementExt data);

//===========================================================================
//! \brief This function sends some parameters on the printer.
//! \param[in] pnode : TLV tree node to print.
//! \param[in] ptr_x_DataName : name of the parameter set.
//! \param[in] i_x_Mark : mark to find.
//! \param[in] c_x_tracetype : allow to trace all nodes (all the parameters),
//! or just a part of the parameters, or just one parameter.
//! \param[in] ul_x_tag : tag number to print if only one tag type must be displayed.
//===========================================================================
void CUPAR_Print_Param_Supported(TLV_TREE_NODE pnode, char *ptr_x_DataName, unsigned int i_x_Mark, unsigned char c_x_tracetype, unsigned long ul_x_tag);

//===========================================================================
//! \brief This function converts a string to an hexadecimal buffer.
//! \param[in] str : string buffer, terminated with null.
//! \param[out] dest : buffer containing hexadecimal values.
//! \return Always true.
//===========================================================================
int PAR_ascii2bytes(unsigned char *str, unsigned char *dest);

//===========================================================================
//! \brief This function reads a parameter file.
//! \param[in] ptr_pTree : ptr node for new tags.
//! \param[in] i_x_tag : main mark (tag), to set data in TLV tree structure.
//! \param[in] ptr_x_tagMark : main mark (text) to set data in TLV tree structure.
//! \param[out] fileName : Parameter file name.
//! \return
//! - 0 if successfull.
//! - 1 otherwise.
//===========================================================================
int CUPAR_ReadTextParamFile (TLV_TREE_NODE * ptr_pTree,unsigned int i_x_tag,char * ptr_x_tagMark,char *fileName);

//===========================================================================
//! \brief This function reads an element in a parameter file
//! \param[in] buf : input buffer.
//! \param[in] lg : buffer length.
//! \param[out] i_x_index : current index in buffer.
//! \param[in] max_len : maximum length for the element.
//! \param[out] tag : tag of the element read.
//! \param[out] length : length of the element read.
//! \param[out] value : value of the element read.
//! \return
//! - TRUE if successfull.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_read_next_element_text (char *buf,int lg,int *i_x_index,int max_len,unsigned long *tag,int *length,char *value);

//===========================================================================
//! \brief This function allows to trace tags on the printer.
//! \param[in] i_x_NumMark : mark to find in TLV tree to trace all children.
//! \return
//! - 0 if successfull.
//! - 1 otherwise.
//===========================================================================
int CUPAR_Tag_Dump(unsigned int  i_x_NumMark);

//===========================================================================
//! \brief This function allows to trace a global TLV tree on the printer.
//! The TLv tree to trace is defined by input parameter i_x_TreeType.
//! \param[in] i_x_TreeType : defines TLV tree to trace :
//! - C_TREE_APPLI : pTreeAppli will be traced.
//! - C_TREE_DEFAULT : pTreeDefault will be traced.
//! - C_TREE_PARAM : pTreeParam will be traced.
//! \return
//! - 0 if successfull.
//! - 1 otherwise.
//===========================================================================
int CUPAR_TLVTree_Dump(unsigned int i_x_TreeType);

//! @}

#endif /* CU_GEST_PARAM_H */



#ifndef __TLVTREEDEL_H__INCLUDED__
#define __TLVTREEDEL_H__INCLUDED__

/////////////////////////////////////////////////////////////////

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

int AddDelValueToTlvTree(TLV_TREE_NODE hTlvTree, const _DEL_* pDel);
int AddTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree);

int CreateTlvTreeFromDel(TLV_TREE_NODE* pTlvTree, const _DEL_* pDel);

#endif

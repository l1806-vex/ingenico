#ifndef __HYPERTERMINAL_H__INCLUDED__
#define __HYPERTERMINAL_H__INCLUDED__

/////////////////////////////////////////////////////////////////

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

int HyperterminalSendAndReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int HyperterminalSendMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int HyperterminalReadMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int HyperterminalReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);

#endif

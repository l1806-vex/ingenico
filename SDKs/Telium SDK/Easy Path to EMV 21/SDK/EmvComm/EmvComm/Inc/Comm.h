#ifndef __COMM_H__INCLUDED__
#define __COMM_H__INCLUDED__

/////////////////////////////////////////////////////////////////

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

int CommGetProtocolInfo(NO_SEGMENT AppliNum, TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommConfigure(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommConnect(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommDisconnect(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommGetStatus(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommSendAndReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommSendMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommReadMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);
int CommUnknownService(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);

#endif

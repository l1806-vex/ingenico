/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.H"
#include "TlvTree.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"
#include "util.h"

#include "oem_cless.h"  // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		// Telium Pass include DLL
#include "ImplicitSelection.h"
#include "implicit_selection_tags.h"
#include "DataElement.h"
#include "_emvdctag_.h"

#include "EmvLib_Tags.h"
#include "EntryPoint_Tags.h"

//// Defines /////////////////////////////////////////////////////////////////

//// Local variable //////////////////////////////////////////////////////////

//static unsigned char gs_uc_AID_PayPass[]    			= {0xA0,0x00,0x00,0x00,0x04,0x10,0x10};
//static unsigned char gs_uc_AID_Maestro[]    			= {0xA0,0x00,0x00,0x00,0x04,0x30,0x60};
//static unsigned char gs_uc_AID_payWave[]    			= {0xA0,0x00,0x00,0x00,0x03,0x10,0x10};
//static unsigned char gs_uc_AID_ExpPay[]     			= {0xA0,0x00,0x00,0x00,0x25,0x01};

static unsigned char gs_uc_AID_payWave_Small[] 			= {0xA0,0x00,0x00,0x00,0x03};
static unsigned char gs_uc_AID_PayPass_Small[] 			= {0xA0,0x00,0x00,0x00,0x04};

//static unsigned char gs_uc_Amount_Bin_25[]  			= {0x00,0x00,0x09,0xC4};
//static unsigned char gs_uc_Amount_Bin_20[]  			= {0x00,0x00,0x07,0xD0};
static unsigned char gs_uc_Amount_Bin_15[]  			= {0x00,0x00,0x05,0xDC};
//static unsigned char gs_uc_Amount_Bin_10[]  			= {0x00,0x00,0x03,0xE8};
//static unsigned char gs_uc_Amount_Bin_05[]  			= {0x00,0x00,0x01,0xF4};

//static unsigned char gs_uc_Amount_Num_50[]  			= {0x00,0x00,0x00,0x00,0x50,0x00};
static unsigned char gs_uc_Amount_Num_25[]  			= {0x00,0x00,0x00,0x00,0x25,0x00};
static unsigned char gs_uc_Amount_Num_20[]  			= {0x00,0x00,0x00,0x00,0x20,0x00};
//static unsigned char gs_uc_Amount_Num_15[]  			= {0x00,0x00,0x00,0x00,0x15,0x00};
static unsigned char gs_uc_Amount_Num_10[]  			= {0x00,0x00,0x00,0x00,0x10,0x00};
//static unsigned char gs_uc_Amount_Num_05[]  			= {0x00,0x00,0x00,0x00,0x05,0x00};

static unsigned char gs_uc_TTQ_NoOption[]   			= {0xB2,0x00,0x00,0x00};
//static unsigned char gs_uc_TTQ_Option[]     			= {0xB2,0xC0,0x00,0x00};

static unsigned char gs_uc_ProprietaryId_1[]    		= {0x12,0x34,0x56,0x78};
static unsigned char gs_uc_ProprietaryId_2[]    		= {0x11,0x22,0x33,0x44};

//static unsigned char gs_uc_Kernel_Jcb[]     			= {0x00,0x01};
static unsigned char gs_uc_Kernel_PayPass[] 			= {0x00,0x02};
static unsigned char gs_uc_Kernel_Visa[]    			= {0x00,0x03};
//static unsigned char gs_uc_Kernel_EmvCo[]   			= {0x01,0x01};
//static unsigned char gs_uc_Kernel_Amex[]    			= {0x01,0x02};

//static unsigned char gs_uc_AID_Option_000[] 			= {0x00,0x03,0x00,0x00};		// No option.
//static unsigned char gs_uc_AID_Option_001[] 			= {0x01,0x03,0x00,0x00};		// Partial AID.
//static unsigned char gs_uc_AID_Option_010[] 			= {0x02,0x03,0x00,0x00};		// Status check.
//static unsigned char gs_uc_AID_Option_011[] 			= {0x03,0x03,0x00,0x00};		// Partial AID & Status check.
//static unsigned char gs_uc_AID_Option_100[] 			= {0x04,0x03,0x00,0x00};		// Zero amount.
static unsigned char gs_uc_AID_Option_101[] 			= {0x05,0x03,0x00,0x00};		// Partial AID & Zero amount.
//static unsigned char gs_uc_AID_Option_110[] 			= {0x06,0x03,0x00,0x00};		// Status check & Zero amount.
//static unsigned char gs_uc_AID_Option_111[] 			= {0x07,0x03,0x00,0x00};		// Partial AID & Status check & Zero amount.
static unsigned char gs_uc_AID_Option_200[] 			= {0x19,0x01,0x00,0x00};		// Zero amount, No amount, partial aid

static unsigned char gs_uc_APDU_Select_PPSE[] 	    	= {0x00,0xA4,0x04,0x00,0x0E,0x32,0x50,0x41,0x59,0x2E,0x53,0x59,0x53,0x2E,0x44,0x44,0x46,0x30,0x31,0x00};
//static unsigned char gs_uc_APDU_Select_payWave_Small[] 	= {0x00,0xA4,0x04,0x00,0x05,0xA0,0x00,0x00,0x00,0x03,0x00};
//static unsigned char gs_uc_APDU_Select_PayPass_Small[]	= {0x00,0xA4,0x04,0x00,0x05,0xA0,0x00,0x00,0x00,0x04,0x00};
//static unsigned char gs_uc_APDU_Select_PayPass[]		= {0x00,0xA4,0x04,0x00,0x07,0xA0,0x00,0x00,0x00,0x04,0x10,0x10,0x00};
//static unsigned char gs_uc_APDU_Select_Maestro[]		= {0x00,0xA4,0x04,0x00,0x07,0xA0,0x00,0x00,0x00,0x04,0x30,0x60,0x00};
//static unsigned char gs_uc_APDU_Select_payWave[]		= {0x00,0xA4,0x04,0x00,0x07,0xA0,0x00,0x00,0x00,0x03,0x10,0x10,0x00};

static unsigned char gs_uc_APDU_SW_9000[]				= {0x90,0x00};

//static unsigned char gs_uc_APDU_OptionBeforeLowPrio[]	= {0x00,0x05,0x00,0x00};
//static unsigned char gs_uc_APDU_OptionBeforeHighPrio[]	= {0x00,0x10,0x00,0x00};
//static unsigned char gs_uc_APDU_OptionAfterLowPrio[]	= {0x01,0x05,0x00,0x00};
static unsigned char gs_uc_APDU_OptionAfterHighPrio[]	= {0x01,0x10,0x00,0x00};

//static unsigned char gs_uc_Detection_Type_IsoAB[]       = {DETECTION_MASK_ISO_A | DETECTION_MASK_ISO_B,0x00,0x00,0x00};
static unsigned char gs_uc_Detection_Type_IsoAB_MIFARE[] = {DETECTION_MASK_ISO_A | DETECTION_MASK_ISO_B | DETECTION_MASK_MIFARE_A | DETECTION_MASK_MIFARE_ULTRA_LIGHT_A,
															DETECTION_MASK_MIFARE_4K_A, 0x00, 0x00};


//// Local function declarations /////////////////////////////////////////////

static void __DllTesting_ParametersManagement_AddAidToTlvTree (TLV_TREE_NODE hTlvTreeOut, 
														const unsigned char * pAid, const unsigned long ulAidLen,
														const unsigned char * pTerminalFloorLimit,const unsigned long ulTerminalFloorLimitLen,
														const unsigned char * pClessTransacFL, const unsigned long ulClessTransacFLLen,
														const unsigned char * pClessFL, const unsigned long ulClessFLLen,
														const unsigned char * pCvmReqLimit, const unsigned long ulCvmReqLimitLen,
														const unsigned char * pAidOptions, const unsigned long ulAidOptionsLen,
														const unsigned char * pDefaultKernelToUse, const unsigned long ulDefaultKernelLen,
														const unsigned char * pTtq, const unsigned long ulTtqLen,
														const unsigned char * pAidPropId, const unsigned long ulAidPropLen);

static void __DllTesting_ParametersManagement_AddApduToTlvTree (TLV_TREE_NODE hTlvTreeOut, 
														const unsigned char * pCommandToSend, const unsigned long ulCommandToSendLen,
														const unsigned char * pExpectedSw, const unsigned long ulExpectedSwLen,
														const unsigned char * pExpectedCardResponse, const unsigned long ulExpectedCardResponseLen,
														const unsigned char * pResponseMask, const unsigned long ulResponseMaskLen,
														const unsigned char * pApduOptions, const unsigned long ulApduOptionsLen);

static void __DllTesting_ParametersManagement_AddDetectionInfoToTlvTree (TLV_TREE_NODE hTlvTreeOut, 
																const unsigned char * pDetectionType, const unsigned long ulDetectionTypeLen);

//// Local functions /////////////////////////////////////////////////////////

//! \brief Add an AID structure for application selection into the global TLV Tree.
//! \param[out] hTlvTreeOut TLV Tree to be filled with the AID structure.
//! \param[in] pAid Application identifier to be added.
//! \param[in] ulAidLen Length of \a pAid.
//! \param[in] pTerminalFloorLimit Terminal floor limit for the AID.
//! \param[in] ulTerminalFloorLimitLen Length of \a pTerminalFloorLimit.
//! \param[in] pClessTransacFL Cless transaction floor limit for this AID.
//! \param[in] ulClessTransacFLLen Length of \a pClessTransacFL.
//! \param[in] pCvmReqLimit Cless CVM required limit for this AID.
//! \param[in] ulCvmReqLimitLen Length of \a pCvmReqLimit.
//! \param[in] pAidOptions AID options for this AID.
//! \param[in] ulAidOptionsLen Length of \a pAidOptions.
//! \param[in] pDefaultKernelToUse Kernel to be used for this AID.
//! \param[in] ulDefaultKernelLen Length of \a pDefaultKernelToUse.
//! \param[in] pTtq Terminal Transaction Qualifiers for this AID.
//! \param[in] ulTtqLen Length of \a pTtq.
//! \param[in] pAppliType Application type providing this AID.
//! \param[in] ulAppliTypeLen Length of \a pAppliType.
//! \param[in] pAidPropId Application proprietary identifier for this AID.
//! \param[in] ulAidPropLen Length of \a pAidPropId.

static void __DllTesting_ParametersManagement_AddAidToTlvTree (TLV_TREE_NODE hTlvTreeOut, 
														const unsigned char * pAid, const unsigned long ulAidLen,
														const unsigned char * pTerminalFloorLimit,const unsigned long ulTerminalFloorLimitLen,
														const unsigned char * pClessTransacFL, const unsigned long ulClessTransacFLLen,
														const unsigned char * pClessFL, const unsigned long ulClessFLLen,
														const unsigned char * pCvmReqLimit, const unsigned long ulCvmReqLimitLen,
														const unsigned char * pAidOptions, const unsigned long ulAidOptionsLen,
														const unsigned char * pDefaultKernelToUse, const unsigned long ulDefaultKernelLen,
														const unsigned char * pTtq, const unsigned long ulTtqLen,
														const unsigned char * pAidPropId, const unsigned long ulAidPropLen)
{
	TLV_TREE_NODE hNode;

	hNode = TlvTree_AddChild (hTlvTreeOut, TAG_EP_AID_INFORMATION, NULL, 0);

	if (ulAidLen > 0)
		TlvTree_AddChild(hNode, TAG_EMV_AID_TERMINAL, pAid, ulAidLen);

	if (ulTerminalFloorLimitLen >0)
		TlvTree_AddChild(hNode, TAG_EMV_TERMINAL_FLOOR_LIMIT, pTerminalFloorLimit, ulTerminalFloorLimitLen);
	
	if (ulClessTransacFLLen >0)
		TlvTree_AddChild(hNode, TAG_EP_CLESS_TRANSACTION_LIMIT, pClessTransacFL, ulClessTransacFLLen);
	
	if (ulClessFLLen >0)
		TlvTree_AddChild(hNode, TAG_EP_CLESS_FLOOR_LIMIT, pClessFL, ulClessFLLen);
	
	if (ulCvmReqLimitLen >0)
		TlvTree_AddChild(hNode, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, pCvmReqLimit, ulCvmReqLimitLen);
	
	if (ulAidOptionsLen >0)
		TlvTree_AddChild(hNode, TAG_EP_AID_OPTIONS, pAidOptions, ulAidOptionsLen);
	
	if (ulDefaultKernelLen >0)
		TlvTree_AddChild(hNode, TAG_EP_KERNEL_TO_USE, pDefaultKernelToUse, ulDefaultKernelLen);
	
	if (ulTtqLen >0)
		TlvTree_AddChild(hNode, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, pTtq, ulTtqLen);
	
	if (ulAidPropLen >0)
		TlvTree_AddChild(hNode, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, pAidPropId, ulAidPropLen);
}



//! \brief Add an APDU structure for application selection into the global TLV Tree.
//! \param[out] hTlvTreeOut TLV Tree to be filled with the APDU structure.
//! \param[in] pCommandToSend Command to be sent to the card.
//! \param[in] ulCommandToSendLen Length of \a pCommandToSend.
//! \param[in] pExpectedSw Expected Status Word.
//! \param[in] ulExpectedSwLen Length of \a pExpectedSw.
//! \param[in] pExpectedCardResponse Expected card response.
//! \param[in] ulExpectedCardResponseLen Length of \a pExpectedCardResponse.
//! \param[in] pResponseMask mask applied on the response.
//! \param[in] ulResponseMaskLen Length of \a pResponseMask.
//! \param[in] pApduOptions APDU options.
//! \param[in] ulApduOptionsLen Length of \a pApduOptions.
//! \param[in] pAppliType Application type providing this AID.
//! \param[in] ulAppliTypeLen Length of \a pAppliType.

static void __DllTesting_ParametersManagement_AddApduToTlvTree (TLV_TREE_NODE hTlvTreeOut, 
														const unsigned char * pCommandToSend, const unsigned long ulCommandToSendLen,
														const unsigned char * pExpectedSw, const unsigned long ulExpectedSwLen,
														const unsigned char * pExpectedCardResponse, const unsigned long ulExpectedCardResponseLen,
														const unsigned char * pResponseMask, const unsigned long ulResponseMaskLen,
														const unsigned char * pApduOptions, const unsigned long ulApduOptionsLen)
{
	TLV_TREE_NODE hNode;

	hNode = TlvTree_AddChild (hTlvTreeOut, TAG_GENERIC_APDU_INFORMATION, NULL, 0);

	if (ulCommandToSendLen > 0)
		TlvTree_AddChild(hNode, TAG_GENERIC_APDU_COMMAND_TO_SEND, pCommandToSend, ulCommandToSendLen);

	if (ulExpectedSwLen >0)
		TlvTree_AddChild(hNode, TAG_GENERIC_APDU_EXPECTED_STATUS_WORD, pExpectedSw, ulExpectedSwLen);
	
	if (ulExpectedCardResponseLen >0)
		TlvTree_AddChild(hNode, TAG_GENERIC_APDU_EXPECTED_CARD_RESPONSE, pExpectedCardResponse, ulExpectedCardResponseLen);
	
	if (ulResponseMaskLen >0)
		TlvTree_AddChild(hNode, TAG_GENERIC_APDU_RESPONSE_MASK, pResponseMask, ulResponseMaskLen);
	
	if (ulApduOptionsLen >0)
		TlvTree_AddChild(hNode, TAG_GENERIC_APDU_OPTIONS, pApduOptions, ulApduOptionsLen);
}



//! \brief Add card detection structure for application selection into the global TLV Tree.
//! \param[out] hTlvTreeOut TLV Tree to be filled with the detection parameters.
//! \param[in] pDetectionType Card detection type (bit field).
//! \param[in] ulDetectionTypeLen Length of \a pDetectionType.
//! \param[in] pNbCardsToBeDetected Number of cards to be detected.
//! \param[in] ulNbCardsToBeDetectedLen Length of \a pNbCardsToBeDetected.
//! \param[in] pGlobalTimeout Detection global timeout (explicit selection only).
//! \param[in] ulGlobalTimeoutLen Length of \a pGlobalTimeout.

static void __DllTesting_ParametersManagement_AddDetectionInfoToTlvTree (TLV_TREE_NODE hTlvTreeOut, 
																const unsigned char * pDetectionType, const unsigned long ulDetectionTypeLen)
{
	if (ulDetectionTypeLen > 0)
		TlvTree_AddChild(hTlvTreeOut, TAG_GENERIC_DETECTION_TYPE, pDetectionType, ulDetectionTypeLen);
}



//! \brief Fills the TLV Tree provided with the parameters corresponding to the configuration identifier.
//! \param[out] hTlvTreeOut TLV Tree to be filled with the parameters corresponding to the configuration identifier.

void DllTesting_ParametersManagement_GetParameters (TLV_TREE_NODE hOuputTlvTree)
{
	__DllTesting_ParametersManagement_AddDetectionInfoToTlvTree (hOuputTlvTree, 
												gs_uc_Detection_Type_IsoAB_MIFARE, sizeof(gs_uc_Detection_Type_IsoAB_MIFARE));

	if( gucCinematicType == 2) /* Vending payment cinematic EXE MDB */
	{
   	__DllTesting_ParametersManagement_AddAidToTlvTree (hOuputTlvTree, 
												gs_uc_AID_PayPass_Small, sizeof(gs_uc_AID_PayPass_Small), 
												gs_uc_Amount_Bin_15, sizeof(gs_uc_Amount_Bin_15), 
												gs_uc_Amount_Num_25, sizeof(gs_uc_Amount_Num_25), 
												gs_uc_Amount_Num_20, sizeof(gs_uc_Amount_Num_20), 
												gs_uc_Amount_Num_10, sizeof(gs_uc_Amount_Num_10), 
												gs_uc_AID_Option_200, sizeof(gs_uc_AID_Option_200), 
												gs_uc_Kernel_PayPass, sizeof(gs_uc_Kernel_PayPass), 
												NULL, 0,
												gs_uc_ProprietaryId_1, sizeof(gs_uc_ProprietaryId_1));


	__DllTesting_ParametersManagement_AddAidToTlvTree (hOuputTlvTree, 
												gs_uc_AID_payWave_Small, sizeof(gs_uc_AID_payWave_Small), 
												gs_uc_Amount_Bin_15, sizeof(gs_uc_Amount_Bin_15), 
												gs_uc_Amount_Num_25, sizeof(gs_uc_Amount_Num_25), 
												gs_uc_Amount_Num_20, sizeof(gs_uc_Amount_Num_20), 
												gs_uc_Amount_Num_10, sizeof(gs_uc_Amount_Num_10), 
												gs_uc_AID_Option_200, sizeof(gs_uc_AID_Option_200), 
												gs_uc_Kernel_Visa, sizeof(gs_uc_Kernel_Visa), 
												gs_uc_TTQ_NoOption, sizeof(gs_uc_TTQ_NoOption),
												gs_uc_ProprietaryId_2, sizeof(gs_uc_ProprietaryId_2));

   }
   else
   {
   	__DllTesting_ParametersManagement_AddAidToTlvTree (hOuputTlvTree, 
												gs_uc_AID_PayPass_Small, sizeof(gs_uc_AID_PayPass_Small), 
												gs_uc_Amount_Bin_15, sizeof(gs_uc_Amount_Bin_15), 
												gs_uc_Amount_Num_25, sizeof(gs_uc_Amount_Num_25), 
												gs_uc_Amount_Num_20, sizeof(gs_uc_Amount_Num_20), 
												gs_uc_Amount_Num_10, sizeof(gs_uc_Amount_Num_10), 
												gs_uc_AID_Option_101, sizeof(gs_uc_AID_Option_101), 
												gs_uc_Kernel_PayPass, sizeof(gs_uc_Kernel_PayPass), 
												NULL, 0,
												gs_uc_ProprietaryId_1, sizeof(gs_uc_ProprietaryId_1));

	__DllTesting_ParametersManagement_AddAidToTlvTree (hOuputTlvTree, 
												gs_uc_AID_payWave_Small, sizeof(gs_uc_AID_payWave_Small), 
												gs_uc_Amount_Bin_15, sizeof(gs_uc_Amount_Bin_15), 
												gs_uc_Amount_Num_25, sizeof(gs_uc_Amount_Num_25), 
												gs_uc_Amount_Num_20, sizeof(gs_uc_Amount_Num_20), 
												gs_uc_Amount_Num_10, sizeof(gs_uc_Amount_Num_10), 
												gs_uc_AID_Option_101, sizeof(gs_uc_AID_Option_101), 
												gs_uc_Kernel_Visa, sizeof(gs_uc_Kernel_Visa), 
												gs_uc_TTQ_NoOption, sizeof(gs_uc_TTQ_NoOption),
												gs_uc_ProprietaryId_2, sizeof(gs_uc_ProprietaryId_2));
   }
   
   __DllTesting_ParametersManagement_AddApduToTlvTree (hOuputTlvTree,
												gs_uc_APDU_Select_PPSE, sizeof(gs_uc_APDU_Select_PPSE), 
												gs_uc_APDU_SW_9000, sizeof(gs_uc_APDU_SW_9000), 
												NULL, 0, 
												NULL, 0, 
												gs_uc_APDU_OptionAfterHighPrio, sizeof(gs_uc_APDU_OptionAfterHighPrio));
}
   

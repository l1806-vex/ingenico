/*!
 ------------------------------------------------------------------------------
                  INGENICO Technical Software Department 
 ------------------------------------------------------------------------------
 Copyright (c) 2012, Ingenico.
 28-32 boulevard de Grenelle 75015 Paris, France.
 All rights reserved.

  This source program is the property of INGENICO Company and may not be copied
  in any form or by any means, whether in part or in whole, except under license
  expressly granted by INGENICO company 
  
  All copies of this program, whether in part or in whole, and
  whether modified or not, must display this and all other	
  embedded copyright and ownership notices in full.
 ------------------------------------------------------------------------------
   
 Project : Tpass Sample
 Module  : PAR - Parameter Management Unit

 @file      par_management.c
 @brief     This file contains the parameters  that is implemented
            by this sample.
            
 @date      08/03/2013

 ------------------------------------------------------------------------------
 */

#include "SDK30.H"
#include "TlvTree.h"

#include "oem_cless.h"  // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		// Telium Pass include DLL
#include "par_management.h"
#include "implicit_selection_tags.h"
#include "DataElement.h"
#include "_emvdctag_.h"

#include "EmvLib_Tags.h"
#include "EntryPoint_Tags.h"

#include "trace.h"
#include "par.h"
#include "Utilities.h"

static TRC_Trace_t trc_fun;

/** Convert hexadecimal character to nibble
 * \return nibble if OK; 0x10 on error
 */
static unsigned char _PAR_chr2nib(char chr) {
    switch (chr) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
          return (unsigned char) (chr - '0');
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
          return (unsigned char) (chr - 'A' + 10);
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
          return (unsigned char) (chr - 'a' + 10);
      default:
          break;
    }
    return 0x10;                //KO
}

/** Convert a hexadecimal string hex into a binary buffer bin of length len. 
 * The zero value of len means that the length is to be calculated as the strlen(hex).
 * The spaces and tabs at the beginning of hex are not allowed.
 * If operation is performed successfully, the number of bytes converted is returned.
 * In case of invalid input (invalid character) zero value is returned.
 * \param bin (O) Pointer to the buffer to be filled.
 * \param hex (I) Source string containing hexadecimal digits only.
 * \param len (I) Number of characters in the destination.
 * \return
 *    - number of bytes written into bin if OK.
 *    - 0 otherwise.
 */
static int _PAR_hex2bin(unsigned char * bin, const char *hex, int len) {
    int ret;                    //to be returned: number of characters processed
    unsigned char tmp;

    //if non-zero, len is the length of acceptor buffer bin
    if(!len)
    {                  //calcualte length if missing
        len = strlen(hex);
    }

    ret = 0;
    while(len--)
    {
        tmp = _PAR_chr2nib(*hex++);  //get first nibble
        if(tmp >= 0x10)
            break;
        *bin = (unsigned char) (tmp << 4);

        tmp = _PAR_chr2nib(*hex++);  //get second nibble
        if (tmp >= 0x10)
        {
            ret = 0;
            break;
        }
        *bin |= tmp;

        bin++;
        ret++;
    }
    return ret;
}

/** Add tag data to the tlv tree
 * \param node (I) tlv tree node
 * \param tag (I) Tag to be added to the tlv tree
 * \param data (I) Tag data to be added to the tlv tree
 * \return
 *    - none
 */
static void _PAR_AddTlv(TLV_TREE_NODE node, unsigned int tag, char * data)
{
    int len;
    unsigned char buf[64];

    memset(buf, 0, sizeof(buf));
    len = _PAR_hex2bin(buf, data, 0);
    if (len > 0)
    {
        TRC_TRACE_INFO(trc_fun, data);
        TlvTree_AddChild(node, tag, buf, len);
    }
}

/** Add paypass AID data to the tlv tree
 * \param tlvTree (I) tlv tree node
 * \return
 *    - none
 */
static void _PAR_PaypassAidToTlvTree(TLV_TREE_NODE tlvTree)
{
    int ret;
    char *data;
    TLV_TREE_NODE node;

    node = TlvTree_AddChild (tlvTree, TAG_EP_AID_INFORMATION, NULL, 0);

    ret = PAR_AidPaywaveSmallGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EMV_AID_TERMINAL, data);
    }
    
    ret = PAR_AmtBin15Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EMV_TERMINAL_FLOOR_LIMIT, data);
    }

    ret = PAR_AmtNum25Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_CLESS_TRANSACTION_LIMIT, data);
    }

    ret = PAR_AmtNum20Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_CLESS_FLOOR_LIMIT, data);
    }

    ret = PAR_AmtNum10Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, data);
    }

    ret = PAR_AidOption101Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_AID_OPTIONS, data);
    }

    ret = PAR_KernelPaypassGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_KERNEL_TO_USE, data);
    }

    ret = PAR_PropId1Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, data);
    }
}

/** Add Visa AID data to the tlv tree
 * \param tlvTree (I) tlv tree node
 * \return
 *    - none
 */
static void _PAR_VisaAidToTlvTree(TLV_TREE_NODE tlvTree)
{
    int ret;
    char *data;
    TLV_TREE_NODE node;

    node = TlvTree_AddChild (tlvTree, TAG_EP_AID_INFORMATION, NULL, 0);

    ret = PAR_AidPaypassSmallGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EMV_AID_TERMINAL, data);
    }
    
    ret = PAR_AmtBin15Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EMV_TERMINAL_FLOOR_LIMIT, data);
    }

    ret = PAR_AmtNum25Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_CLESS_TRANSACTION_LIMIT, data);
    }

    ret = PAR_AmtNum20Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_CLESS_FLOOR_LIMIT, data);
    }

    ret = PAR_AmtNum10Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, data);
    }

    ret = PAR_AidOption101Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_AID_OPTIONS, data);
    }

    ret = PAR_KernelVisaGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_KERNEL_TO_USE, data);
    }

    ret = PAR_TtqNoOptionGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, data);
    }

    ret = PAR_PropId2Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, data);
    }
}

/** Add APDU data to the tlv tree
 * \param tlvTree (I) tlv tree node
 * \return
 *    - none
 */
static void _PAR_AddApduToTlvTree(TLV_TREE_NODE tlvTree)
{
    int ret;
    char *data;
    TLV_TREE_NODE node;
    
    node = TlvTree_AddChild (tlvTree, TAG_GENERIC_APDU_INFORMATION, NULL, 0);

    ret = PAR_SelectPPSEGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_GENERIC_APDU_COMMAND_TO_SEND, data);
    }
    
    ret = PAR_ApduSW9000Get(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_GENERIC_APDU_EXPECTED_STATUS_WORD, data);
    }    

    ret = PAR_ApduOptionGet(&data);
    if (ret==PAR_OK)
    {
        _PAR_AddTlv(node, TAG_GENERIC_APDU_OPTIONS, data);
    }
}

/** Add detection info to the tlv tree
 *
 * \param tlvTree (I) tlv tree node
 * \param type (I) detection type
 * \param len (I) length of the data
 * \return
 *    - none
 */
static void _PAR_DetectionInfoToTlvTree(TLV_TREE_NODE tlvTree, const unsigned char * type, const unsigned long len)
{
    if (len > 0)
        TlvTree_AddChild(tlvTree, TAG_GENERIC_DETECTION_TYPE, type, len);
}

void PAR_GetClessParameters(TLV_TREE_NODE tlvTree)
{
    unsigned char detectionMask[] = 
        {DETECTION_MASK_ISO_A | DETECTION_MASK_ISO_B | DETECTION_MASK_MIFARE_A | DETECTION_MASK_MIFARE_ULTRA_LIGHT_A, DETECTION_MASK_MIFARE_4K_A, 0x00, 0x00};

    trc_fun = TRC_HandleGet();

    _PAR_DetectionInfoToTlvTree(tlvTree, detectionMask, sizeof(detectionMask));

     TRC_TRACE_INFO(trc_fun, "Paypass AID Data");
    _PAR_PaypassAidToTlvTree(tlvTree);

     TRC_TRACE_INFO(trc_fun, "Visa AID Data");
    _PAR_VisaAidToTlvTree (tlvTree);

    _PAR_AddApduToTlvTree (tlvTree);

}


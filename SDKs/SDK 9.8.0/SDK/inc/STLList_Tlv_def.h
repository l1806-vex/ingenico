 
#ifndef _TLV_STLLIST_TLV_DEF_H
#define _TLV_STLLIST_TLV_DEF_H


/*
 TLV Id
 */

#define  NAM_TLV_STLLIST_TLV      ("STLList_Tlv")
#define  ID_TLV_STLLIST_TLV       0x40020408

#define  TAG_TLV_STLLIST_TLV      ID_TLV_STLLIST_TLV


typedef struct {
   int           iTag; /* TAG_END for the last */
   unsigned int  iId;
   int           iLenValue;
} T_LIST_TLV_HEADER;


#endif

/***
 * Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Sagem Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Sagem Monetel.
 *
 * @Title:        lib_iapp.h     
 * @Description:  Iapp header file
 * @Reference:    
 * @Comment:      
 *
 * @author        PL      
 * @version       
 * @Comment:      
 * @date:         2004/01/28 
 *
 * @author        JLM      
 * @version       
 * @Comment:      Proto modification of IAPP_SchGetChar
 * @date:         2006/07/05 
*/ 
 
#ifndef _LIBIAPP_H_
#define _LIBIAPP_H_

/* 
 Exchange with Input Pin Scheme via IAPP 
 */
//! \brief Enumerate the different synchronization values.
typedef enum {
   SYNC_VALID  =  0x01,								//!< 0x01 : OK 
   SYNC_CANCEL =  0x02,								//!< 0x02 : cancel
   SYNC_OTHER  =  0x03,								//!< 0x03 : other kind of synchro information 
   SYNC_ERROR  =  0x04								//!< 0x04 : default 
} T_IAPPSync;


int IAPP_SchGetSync (int Timeout, T_IAPPSync *Synchro, FILE *Iapp);
int IAPP_SchPutSync (T_IAPPSync Synchro, FILE *Iapp);
int IAPP_SchGetChar (int Timeout, char * ptcData, FILE *Iapp);
int IAPP_SchPutChar (char Data, FILE *Iapp);
int IAPP_SchGetData (int Timeout, unsigned char *Data, unsigned int NbData, FILE *Iapp);
int IAPP_SchPutData (unsigned char *Data, unsigned int NbData , FILE *Iapp);

int IAPP_SchGetCharEvent(int Timeout, char * ptcData, FILE* Iapp, unsigned int *pt_iEvents);
int IAPP_SchGetDataEvent(int Timeout, unsigned char* Data, unsigned int DataSize, FILE *Iapp,
						 unsigned int *pt_iEvents);
int IAPP_SchPutDataEvent(unsigned char* Data, unsigned int DataSize, FILE* Iapp,
						 unsigned int *pt_iEvents);

#endif

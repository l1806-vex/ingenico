/*
 * util.h
 *
 *  Created on: 9 janv. 2012
 *      Author: cplessis
 */

#ifndef UTIL_H_
#define UTIL_H_

#define UCMCINEMATIC 2 /*  1= BANKING  2=VENDING */

////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////
extern void   FindMessage                 ( unsigned char, char * ) ;
extern void   UTIL_FormatBalance          ( unsigned long, unsigned char * ) ;
extern void   UTIL_InitStruct_ParamVmcMsg ( void * ) ;
extern void   UTIL_InitStruct_ParamVmc    ( void * ) ;


extern unsigned char gucCinematicType; /* must be same same as UCMCINEMATIC */
#endif /* UTIL_H_ */

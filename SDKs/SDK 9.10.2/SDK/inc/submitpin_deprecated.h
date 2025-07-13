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
 * @Title:       SUBMITPIN.H        
 * @Description:  
 * @Reference:    
 * @Comment:      
 *
 * @author       DF/JR 
 * @version       
 * @Comment:      
 * @date:        2003/12/15 
 */ 
 
#ifndef _SUBMITPIN_H_
#define _SUBMITPIN_H_



//! \addtogroup KSFAM_PINLIB
//! @{
//! @deprecated	Please use functions provided by Security DLL.	


/* IAPP Response for InitDial : APP <-- KSU */
#define R_DIAL_OK	'O'
#define R_DIAL_KO 	'K'

// errors
#define IAPP_ERROR			9
#define PB_PIN_BOOSTER		10


//format
#define		FORMAT_B0		0   


//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	 Load scheme in the crypto processor of the terminal.
//! \param SchId_P : id of the scheme
//! \param pSchName_P : name of the scheme
//! \param codeexit : return of the scheme
//! \param p0 : parameter of the scheme
//! \param p1 : parameter of the scheme
//! \param p2 : parameter of the scheme
//! \param p3 : parameter of the scheme
//! \return 
//! - 0 if ok
//! - negative otherwise.
// \if SIMULATION
//  @GSIM_F:ExeSchAndWaitEnd:KSFAM_PINLIB:0x03
//  @GSIM_A:3:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define ExeSchAndWaitEnd ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int ExeSchAndWaitEnd(SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3) MACRO_DEPRECATED ;
#endif

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	 Asynchronous call, application have the CPU to 
//! send/receive bytes on IAPP peripheral...or other treatment .
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer on the scheme name.
//! \param arg1 : scheme parameter.
//! \param arg2 : scheme parameter.
//! \param arg3 : scheme parameter.
//! \param arg4 : scheme parameter.
//! \return 
//! - 0 : Ok. Otherwise, please check following items :
//! - 1. Are schemes correctly linked with application ? 
//! When an application is signed with SST, schemes used by this application must be linked. 
//! You can use DumpSGN (provided in SDK\\TOOLS) to check your application and linked schemes. 
//! ie : 
//! - D:\\SDK 4.3\\Crypto\\bin>dumpsgn crypto.sgn 
//! - Dump SNG appli file V1.01 
//! - File Check : [crypto.sgn] 
//! - Schema Nam: SchLoadData xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchCipherDa xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchGetPin xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchIso9564 xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchFree xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - ** Application ** xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Application repudiation key : FF800000000000000000000000000000 
//! - On this sample : 
//! schemes SchLoadData, SchCipherDa, SchGetPin, SchIso9564 and SchFree are linked to 
//! you application, and applications and schemes are signed with the same RSA card (card number xxxxxxxx) 
//! - 2. Check that Manager date is not set to 2098 
//! If it is the case, put correct year in manager menu. 
//! - 3. Check Coherency between scheme name and scheme ID , i.e.
//! sch_init ( (SEG_ID)ID_SCH_LOAD_DATA,NAM_SCH_LOAD_DATA.... 
// \if SIMULATION
//  @GSIM_F:sch_init:KSFAM_PINLIB:0x09
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define sch_init ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int sch_init (SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4 ) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief Load scheme in the crypto processor of the pinpad.
//! \param SchId_P : id of the scheme
//! \param pSchName_P : name of the scheme
//! \param codeexit : return of the scheme
//! \param p0 : parameter of the scheme
//! \param p1 : parameter of the scheme
//! \param p2 : parameter of the scheme
//! \param p3 : parameter of the scheme
//! \return 
//! - 0 if ok
//! - negative otherwise.
// \if SIMULATION
//  @GSIM_F:ExeSchAndWaitEndUsb:KSFAM_PINLIB:0x04
//  @GSIM_A:3:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define ExeSchAndWaitEndUsb ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int ExeSchAndWaitEndUsb(SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in the crypto processor of the pinpad. This function doesn't wait the return of the scheme.
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer to the scheme name.
//! \param arg1, arg2, arg3, arg4 : scheme parameters.
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:sch_initUsb:KSFAM_PINLIB:0x0B
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define sch_initUsb ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int sch_initUsb (SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4 ) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in the crypto processor of the terminal.
//! \param i_uc_type : indicates if schemes have to be executed internally (as standard function), on pinpad (USB), or other (futur use).
//! \param SchId_P : id of the scheme
//! \param pSchName_P : name of the scheme
//! \param codeexit : return of the scheme
//! \param p0 : parameter of the scheme
//! \param p1 : parameter of the scheme
//! \param p2 : parameter of the scheme
//! \param p3 : parameter of the scheme
//! \return 
//! - 0 if ok
//! - negative otherwise.
// \if SIMULATION
//  @GSIM_F:ExeSchAndWaitEndGeneric:KSFAM_PINLIB:0x12
//  @GSIM_A:4:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define ExeSchAndWaitEndGeneric ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int ExeSchAndWaitEndGeneric(unsigned char i_uc_type, SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Asynchronous call, application have the CPU to 
//! send/receive bytes on IAPP peripheral...or other treatment .
//! \param i_uc_type : indicates if schemes have to be executed internally (as standard function), on pinpad (USB), or other (futur use).
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer on the scheme name.
//! \param arg1 : scheme parameter.
//! \param arg2 : scheme parameter.
//! \param arg3 : scheme parameter.
//! \param arg4 : scheme parameter.
//! \return 
//! - 0 : Ok. Otherwise, please check following items :
//! - 1. Are schemes correctly linked with application ? 
//! When an application is signed with SST, schemes used by this application must be linked. 
//! You can use DumpSGN (provided in SDK\\TOOLS) to check your application and linked schemes. 
//! ie : 
//! - D:\\SDK 4.3\\Crypto\\bin>dumpsgn crypto.sgn 
//! - Dump SNG appli file V1.01 
//! - File Check : [crypto.sgn] 
//! - Schema Nam: SchLoadData xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchCipherDa xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchGetPin xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchIso9564 xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Schema Nam: SchFree xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - ** Application ** xxxxxxxx 00000004 03 FF800000000000000000000000000000 
//! - Application repudiation key : FF800000000000000000000000000000 
//! - On this sample : 
//! schemes SchLoadData, SchCipherDa, SchGetPin, SchIso9564 and SchFree are linked to 
//! you application, and applications and schemes are signed with the same RSA card (card number xxxxxxxx) 
//! - 2. Check that Manager date is not set to 2098 
//! If it is the case, put correct year in manager menu. 
//! - 3. Check Coherency between scheme name and scheme ID , i.e.
//! sch_init ( (SEG_ID)ID_SCH_LOAD_DATA,NAM_SCH_LOAD_DATA.... 
// \if SIMULATION
//  @GSIM_F:sch_initGeneric:KSFAM_PINLIB:0x13
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define sch_initGeneric ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int sch_initGeneric (unsigned char i_uc_type, SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4 ) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Wait for the end of the scheme.
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:sch_end:KSFAM_PINLIB:0x08
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define sch_end ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int sch_end (void) MACRO_DEPRECATED ;
#endif
//! @}

/* fonctions a appeler depuis les DLLs */

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in current crypto processor (define with SetPprState function).
//! \param SchId_P : Scheme id.
//! \param *pSchName_P : Pointer to the scheme name.
//! \param *codeexit : return code of the scheme.
//! \param p0 : scheme parameter.
//! \param p1 : scheme parameter.
//! \param p2 : scheme parameter.
//! \param p3 : scheme parameter.
//! \param *ad_deb : address to search the scheme in the code.
//! \param *ad_fin : address to search the scheme in the code.
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:DllExeSchAndWaitEnd:KSFAM_PINLIB:0x0C
//  @GSIM_A:3:DATA_SIZE(4)
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define DllExeSchAndWaitEnd ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int DllExeSchAndWaitEnd(SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3, char *ad_deb, char *ad_fin) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in the crypto processor of the pinpad.
//! \param SchId_P : Scheme id.
//! \param *pSchName_P : Pointer to the scheme name.
//! \param *codeexit : return code of the scheme.
//! \param p0 : scheme parameter.
//! \param p1 : scheme parameter.
//! \param p2 : scheme parameter.
//! \param p3 : scheme parameter.
//! \param *ad_deb : address to search the scheme in the code.
//! \param *ad_fin : address to search the scheme in the code.
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:DllExeSchAndWaitEndUsb:KSFAM_PINLIB:0x0D
//  @GSIM_A:3:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define DllExeSchAndWaitEndUsb ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int DllExeSchAndWaitEndUsb(SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3, char *ad_deb, char *ad_fin) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in current crypto processor (define with SetPprState function).
//! \param i_uc_type : indicates if schemes have to be executed internally (as standard function), on pinpad (USB), or other (futur use).
//! \param SchId_P : Scheme id.
//! \param *pSchName_P : Pointer to the scheme name.
//! \param *codeexit : return code of the scheme.
//! \param p0 : scheme parameter.
//! \param p1 : scheme parameter.
//! \param p2 : scheme parameter.
//! \param p3 : scheme parameter.
//! \param *ad_deb : address to search the scheme in the code.
//! \param *ad_fin : address to search the scheme in the code.
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:DllExeSchAndWaitEndGeneric:KSFAM_PINLIB:0x14
//  @GSIM_A:4:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define DllExeSchAndWaitEndGeneric ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int DllExeSchAndWaitEndGeneric(unsigned char i_uc_type, SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3, char *ad_deb, char *ad_fin) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in current crypto processor (define with SetPprState function). This function doesn'i wait the return of the scheme.
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer on the scheme name.
//! \param arg1 : scheme parameter.
//! \param arg2 : scheme parameter.
//! \param arg3 : scheme parameter.
//! \param arg4 : scheme parameter.
//! \param *ad_deb : address of the scheme
//! \param *ad_fin : address of the scheme
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:Dllsch_init:KSFAM_PINLIB:0x0E
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define Dllsch_init ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int Dllsch_init (SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4, char *ad_deb, char *ad_fin ) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in the crypto processor of the pinpad. This function doesn'i wait the return of the scheme.
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer on the scheme name.
//! \param arg1 : scheme parameter.
//! \param arg2 : scheme parameter.
//! \param arg3 : scheme parameter.
//! \param arg4 : scheme parameter.
//! \param *ad_deb : address of the scheme
//! \param *ad_fin : address of the scheme
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:Dllsch_initUsb:KSFAM_PINLIB:0x0F
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define Dllsch_initUsb ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int Dllsch_initUsb (SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4, char *ad_deb, char *ad_fin ) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in current crypto processor (define with SetPprState function). This function doesn'i wait the return of the scheme.
//! \param i_uc_type : indicates if schemes have to be executed internally (as standard function), on pinpad (USB), or other (futur use).
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer on the scheme name.
//! \param arg1 : scheme parameter.
//! \param arg2 : scheme parameter.
//! \param arg3 : scheme parameter.
//! \param arg4 : scheme parameter.
//! \param *ad_deb : address of the scheme
//! \param *ad_fin : address of the scheme
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:Dllsch_initGeneric:KSFAM_PINLIB:0x15
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define Dllsch_initGeneric ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int Dllsch_initGeneric (unsigned char i_uc_type, SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4, char *ad_deb, char *ad_fin ) MACRO_DEPRECATED ;
#endif
//! @}

/* fin fonctions a appeler depuis les DLLs */

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Present PIN code to smart card
//! \param Fd_P : card flow address.
//! \param C_apdu_L : the APDU command.
//! \param R_apdu_L : the APDU response.
//! \param Format_P : format of the PIN Code.
//! \param LgPin_P : length of the PIN Code.
// \if SIMULATION
//  @GSIM_F:ApduSubmitPin:KSFAM_PINLIB:0x10
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define ApduSubmitPin ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern unsigned char ApduSubmitPin(FILE *Fd_P, T_APDU *C_apdu_L, T_APDU *R_apdu_L, int Format_P ,int LgPin_P) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Present PIN code to smart card on a pinpad
//! \param Fd_P : card flow address.
//! \param C_apdu_L : The APDU command.
//! \param R_apdu_L : The APDU response.
//! \param Format_P : format of the PIN code
//! \param LgPin_P : length of the PIN code
// \if SIMULATION
//  @GSIM_F:ApduSubmitPinUsb:KSFAM_PINLIB:0x11
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define ApduSubmitPinUsb ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern unsigned char ApduSubmitPinUsb(FILE *Fd_P, T_APDU *C_apdu_L, T_APDU *R_apdu_L, int Format_P ,int LgPin_P) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  This routine clean up the scheme in the crypto processor.
//! \param ne_pas_razer : array of integers (each integer is a scheme id)
//! \return None
// \if SIMULATION
//  @GSIM_F:purge:KSFAM_PINLIB:0x06
//  @GSIM_S:purge:E_purge
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define purge ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern void purge ( SEG_ID *ne_pas_razer) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  This routine clean up the scheme in the crypto processor of the pinpad.
//! \param ne_pas_razer : array of integers (each integer is a scheme id)
//! \return None
// \if SIMULATION
//  @GSIM_F:purgeUsb:KSFAM_PINLIB:0x07
//  @GSIM_S:purgeUsb:E_purgeUsb
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define purgeUsb ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern void purgeUsb ( SEG_ID *ne_pas_razer) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  This routine clean up the scheme in the crypto processor.
//! \param i_uc_type : indicates if schemes have to be executed internally (as standard function), on pinpad (USB), or other (futur use).
//! \param ne_pas_razer : array of integers (each integer is a scheme id)
//! \return None
// \if SIMULATION
//  @GSIM_F:purgeGeneric:KSFAM_PINLIB:0x16
//  @GSIM_S:purgeGeneric:E_purgeGeneric
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define purgeGeneric ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern void purgeGeneric ( unsigned char i_uc_type, SEG_ID *ne_pas_razer ) MACRO_DEPRECATED ;
#endif
//! @}

/* fonctions gérant automatiquement la redirection des schémas sur EFT30 ou PPR30/PPC30 */

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Define if PPR/PPC is the current crypto processor.
//! \param connected :
//! - TRUE : PPR/PPC is the current crypto processor .
//! - FALSE : EFT is the current crypto processor .
//! \return None
//! \note Default current crypto processor is EFT.
// \if SIMULATION
//  @GSIM_F:SetPprState:KSFAM_PINLIB:0x01
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define SetPprState ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern void SetPprState (int connected) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Load scheme in current crypto processor (define with SetPprState function).
//! \param SchId_P : id of the scheme
//! \param pSchName_P : name of the scheme
//! \param codeexit : return of the scheme
//! \param p0 : parameter of the scheme
//! \param p1 : parameter of the scheme
//! \param p2 : parameter of the scheme
//! \param p3 : parameter of the scheme
//! \return 
//! - 0 if ok
//! - negative otherwise.
// \if SIMULATION
//  @GSIM_F:ExeSchAndWaitEnd_w:KSFAM_PINLIB:0x02
//  @GSIM_A:3:DATA_SIZE(4)
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define ExeSchAndWaitEnd_w ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int    ExeSchAndWaitEnd_w(SEG_ID SchId_P,char *pSchName_P,int*codeexit,int p0,int p1,int p2,int p3) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Asynchronous call, application have the CPU to send/receive bytes on IAPP peripheral...or other treatment.
//! \param Id_P : Scheme id.
//! \param *SchName_P : Pointer to the scheme name.
//! \param arg1 : scheme parameter.
//! \param arg2 : scheme parameter.
//! \param arg3 : scheme parameter.
//! \param arg4 : scheme parameter.
//! \return 0 : Ok.
// \if SIMULATION
//  @GSIM_F:sch_init_w:KSFAM_PINLIB:0x0A
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define sch_init_w ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern int sch_init_w (SEG_ID Id_P , char *SchName_P, int arg1 , int arg2, int arg3 , int arg4 ) MACRO_DEPRECATED ;
#endif
//! @}

//! \addtogroup KSFAM_PINLIB
//! @{

//! \brief Pinlib will not be supported in Telium+ framework. Please use Security DLL.
//! To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
//! \brief	  Open the current iapp.
//! \param *mod : define open mode.
//! \return FILE handle or NULL if error
// \if SIMULATION
//  @GSIM_F:open_iapp:KSFAM_PINLIB:0x05
//  @GSIM_A:0:ONE_ADDRESS
// \endif
#ifndef _DEPRECATED_PINLIB_SDK090200_
#define open_iapp ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
extern FILE * open_iapp (char* mod) MACRO_DEPRECATED ;
#endif
//! @}


#endif


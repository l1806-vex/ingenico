/*! @addtogroup KSFAM_KSU
	* @{
	 */ 	
	
#ifndef SCHMGMT_H
#define SCHMGMT_H


#define  MAX_ELT_DDIR    25         	/*!< code area record number : to be modified	*/

/*
======================================================================
			Data Structures Definition
======================================================================
*/

//parameters for SEGMENT management

/*! @brief Segment identifier, reserved if negative.	*/
typedef long SEG_ID;

/*! @brief Segment status if SEG_ID negative.	*/
typedef char* SERR;

/*! @brief Parameters strutcture for SEGMENT management.	*/
typedef struct {											
   SEG_ID         tag;								/*!< segment identifier, reserved if negative.*/
   CRC16          crc;								/*!< checksum on RECORDS (*ad[lg]).*/
   U16bit         size;								/*!< real size allocated (En_tete structure gives the max size).*/
   void*          ad;								/*!< pointer on pointer to En_tete structure.*/
   unsigned long  cardnb;							/*!< serial nb of card that have signed this segment.*/
} ENR;

/*! @brief Code records.*/
typedef struct {
   unsigned int  max_elt_ddir;						/*!< number of elements, initialized with MAX_ELT_DDIR value.*/
   ENR           elt[MAX_ELT_DDIR];					/*!< list of elements in DDIR.*/
   short         ruf;								/*!< For having crc at end align to 4.*/
   CRC16         crc;								/*!< checksum for DDIR structure.*/
} DDIR;

/*! @brief This type contain the header.
    En_tete:DATA_CODE(size + sizeof(short) + sizeof(char))  */
typedef struct 
	{
	void  *ptr;										/*!< pointer to the data.*/
	U16bit size;									/*!< size of the pointed area.*/
	Uchar   next;									/*!< index of the next element.*/
	} En_tete;


// exporte pour la compilation de swiromro.h
/*! @brief Internal type of direct.c, used for not having more than 4 parameters in the part_copy function.*/
typedef struct 
{
  int  lg;											/*!< length.*/
  long offset;										/*!< offset.*/
}t_dest_sch;

/*
======================================================================
					List of Defines
======================================================================
*/
#define  SERR_OK                 (SERR)   (0)		/*!< NO ERROR                            */
#define  SERR_FULL               (SERR)  (-1)		/*!< ERROR NO MORE ID AVALABLE           */
#define  SERR_ALREADY_DEFINED    (SERR)  (-2)		/*!< ERROR ALREADY DEFINED ID            */
#define  SERR_UNKNOWN_ID         (SERR)  (-3)		/*!< ERROR UNKNOWN ID                    */
#define  SERR_NOT_ENOUGH_MEMORY  (SERR)  (-4)		/*!< ERROR NOT ENOUGH MEMORY             */
#define  SERR_INITIATIZED        (SERR)  (-5) 		/*!< ERROR END LOAD DISPLAY FPGA COMMAND */
#define  SERR_JUSTDOWNLOADED     (SERR)  (-6) 		/*!< ERROR LOAD DISPLAY FPGA COMMAND     */
#define  SERR_INCOHERANT_PARAM   (SERR)  (-7) 		/*!< ERROR INCOHERANT PARAMETERS: ID Sign not correct, Load Adress not correct , Certificat&Signature Error */
#define  SERR_KO                 (SERR)  (-8) 		/*!< ERROR GLOBAL ERROR                  */
#define  SERR_NOT_FOUND          (SERR)  (-9)		/*!< ERROR ID NOT FOUND                  */
#define  SERR_PB_ON_NEW_AD       (SERR)  (-10)		/*!< ERROR WRONG ADRESS VALUE            */
#define  SERR_WARNING_ON_NEW_AD  (SERR)  (-11)		/*!< WARNING WRONG ADRESS VALUE          */
#define  SERR_CERTIFICAT_KO      (SERR)  (-12)		/*!< NOT USED                            */

// valeurs pour l'UC appli
#define  SERR_CALL_EXIT_BY_RESET (SERR)  (-50)		/*!< ERROR CALL EXIT BY RESET            */
#define  SERR_CERTIFICAT_APP_KO  (SERR)  (-51)		/*!< NOT USED                            */
#define  SERR_SIGNATURE_APP_KO   (SERR)  (-52)		/*!< NOT USED                            */
#define  SERR_CERTIFICAT_VI_KO   (SERR)  (-53) 		/*!< ERROR CERTIFICATE VAR ID NOT EQUAL TO APPLICATION ONE */

#ifdef PRIVATE_SCHMGMT
#define C_LG_DONNEE_CANAL        (TAILLE_BUF_INTER_UC - sizeof(BUF_ENTETE_T))	/*!< INTER UC FRAME SIZE WITHOUT HEADER      */
#define C_LG_COPY_DATA           (C_LG_DONNEE_CANAL   - 8)						/*!< INTER UC MAX COPY DATA SIZE             */


// constantes utilisees pour identifier la commande en provenance du micro appli

#define C_TYP_DALLOC                 0				/*!< dalloc()                    INTER UC FRAME KEY. Used for scheme data allocation                                       */
#define C_TYP_DREALLOC               1				/*!< realloc()                   INTER UC FRAME KEY. Used for scheme data reallocation. Data allocation is cleared before  */
#define C_TYP_SALLOC                 2				/*!< salloc()                    INTER UC FRAME KEY. Used for secret data allocation                                       */
#define C_TYP_FREE                   3 				/*!< free()                      INTER UC FRAME KEY. Used for scheme or secret data allocation                             */
#define C_TYP_PUTCRC                 4				/*!< putcrc_schema()             INTER UC FRAME KEY. Used for certificate&signature scheme verification.Sets the CRC if OK */
#define C_TYP_ISCRC                  5				/*!< iscrc()                     INTER UC FRAME KEY. Used for CRC scheme verification. return if the CRC is OK             */
#define C_TYP_DIR                    6				/*!< dir()                       INTER UC FRAME KEY. Used for @ram_directory[]. Blank                                      */
#define C_TYP_FIND                   7				/*!< find()                      INTER UC FRAME KEY. Used to get an ID component adress (scheme or Secret)                 */
#define C_TYP_CALL                   8				/*!< call()                      INTER UC FRAME KEY. Used to launch a scheme                                               */
#define C_TYP_COPY_DEB               9   			/*!< part_copy_schema()          INTER UC FRAME KEY. Used to initiate a scheme copy                                        */
#define C_TYP_SYS_COPY_DEB           C_TYP_COPY_DEB	/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_COPY                   10   			/*!< part_copy                   INTER UC FRAME KEY. Used to download Booster scheme and KeyFile                           */  
#define C_TYP_SYS_COPY               11   			/*!< part_copy_flash()           INTER UC FRAME KEY. Used to download Booster OS and BF                                    */  
#define C_TYP_DIR_ID                 12				/*!< ddir()                      INTER UC FRAME KEY. Used for first ID list                                                */
#define C_TYP_DIR_SUITE_ID           13				/*!< ddir()                      INTER UC FRAME KEY. Used for next  ID list                                                */
#define C_TYP_ENTER_PIN_SEQUENCE     14 			/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_DUMP                   15				/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_RAZ                    16				/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_IAPP                   17				/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_CHECK_CERTIFICAT       18				/*!< SetCertificat()             INTER UC FRAME KEY. Used to check the transmited certificat                               */ 
#define C_TYP_CHECK_APP              19				/*!< CheckApplication()          INTER UC FRAME KEY. Used to evaluate the transmited software (SHA calculation)            */ 
#define C_TYP_CHECK_SIGNATURE        20				/*!< CheckApplicationSignature() INTER UC FRAME KEY. Used to check the transmited software signature                       */ 
#define C_TYP_COPY_TRAP              21   			/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_SYS_COPY_TRAP          22   			/*!<                             INTER UC FRAME KEY. Not Used on BL2/BL3. RAZ one PatchSystem Word on BL1                  */ 
#define C_TYP_RAZ_PATCH              23				/*!<                             INTER UC FRAME KEY. Not Used                                                              */ 
#define C_TYP_COPYTOFLASH            24				/*!< CopyToFlash()               INTER UC FRAME KEY. Used for the KeyFile copy from Scheme area to Flash Area              */  
#define C_TYP_COPY_DEB_CONFIG        25				/*!< disSCtlrControl()           INTER UC FRAME KEY. Used to Start FPGA downloading. BL3 Only                              */ 
#define C_TYP_COPY_CONFIG            26				/*!< disSCtlrControl()           INTER UC FRAME KEY. Used for FPGA Data downloading and SHA calculation. BL3 Only          */ 
#define C_TYP_COPY_SIGN_CONFIG       27				/*!< disSCtlrControl()           INTER UC FRAME KEY. Used for certificate&signature FPGA Data Control. BL3 Only            */ 


#endif

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @deprecated dalloc allocates a component in a non secure area.\n 
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	Allocates a buffer in non secure area of KSU.
 *	@param s_id : component identifier (a buffer). type int.
 *	@param size : number of bytes allocated.
 *	@return
 *	- A pointer on allocated buffer if positive.
 *	- SERR code if negative : 
 *	- SERR_OK (0)
 *	- SERR_FULL (-1)
 *	- SERR_ALREADY_DEFINED (-2)
 *	- SERR_UNKNOWN_ID (-3) (when keyboard is desactivated for instance)
 *	- SERR_NOT_ENOUGH_MEMORY (-4)
 *	- SERR_INITIATIZED (-5) 
 *	- SERR_JUSTDOWNLOADED (-6) 
 *	- SERR_INCOHERANT_PARAM (-7) 
 *	- SERR_KO (-8)
 *	- SERR_NOT_FOUND (SERR) (-9)
 *	- SERR_PB_ON_NEW_AD (SERR) (-10)
 *	- SERR_WARNING_ON_NEW_AD (SERR) (-11)
 *	- SERR_CERTIFICAT_KO (SERR) (-12)
 *	- SERR_UNAUTHORIZED (SERR) (-13)
 *	- SERR_CALL_EXIT_BY_RESET (SERR) (-50)
 *	- SERR_CERTIFICAT_APP_KO (SERR) (-51)
 *	- SERR_SIGNATURE_APP_KO (SERR) (-52)
 *
 *	@note
 *	The pointer is used on allocation and for the component copy. Then application 
    must use the segment identifier.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:dalloc:KSFAM_KSU:0x01
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define dalloc(a,b) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR dalloc (SEG_ID s_id, int size) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_SCHEMES_SDK96_
#define salloc(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR salloc (SEG_ID s_id, int size, char *new_ad) MACRO_DEPRECATED;
#endif


/*! @deprecated Copy loads a component into the memory allocated for it. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 * This is the way to initialise a KSU component from a EFT30 application as far as component identifier and size is known.
 *	@param s_id : segment identifier.
 *	@param src  : buffer to be copied.
 *	@param size : size to be copied.
 *	@return 
 *	 SERR code : 
 *	 - SERR_OK 
 *	 - SERR_UNKNOWN_ID
 *	 - SERR_NOT_ENOUGH_MEMORY
 *
 *	@note
 *	if size > size allocated for s_id, it will be truncated.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:copy:KSFAM_KSU:0x02
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define copy(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR copy (SEG_ID s_id, char *src, int size) MACRO_DEPRECATED;
#endif


/*! @deprecated This function is used to set CRC16 on the component identifier.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id : component identifier ( a buffer ).
 *	@return
 *	SERR code.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:putcrc:KSFAM_KSU:0x03
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define putcrc(a) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR putcrc(SEG_ID s_id) MACRO_DEPRECATED;
#endif


/*! @deprecated Execute a SCHEME identified by its identifier and suspend calling sheme execution.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id     : component identifier.
 *	@param codeexit : error returned by the component.
 *	@param args     : parameters of component passing by value or by address. (4 int)
 *	@return
 *	SERR code. 
 *	See exit code on component error. -9 is specific code that is returned when call is 
    interrupted by a KSU software reset ( only on EFT30 ).
 *	@note
 *	- Only scheme with a valid CRC16 and valid RSA signature can be executed. RSA signature 
    is verified once after component loading.
 *	- arg1, arg2, arg3, arg4 are parameters that are declared at scheme entry point routine ( main ).
 *	- Codeexit is the return code of scheme entry point routine ( main ).
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:call:KSFAM_KSU:0x04
//  @GSIM_A:2:ONE_POINTER 
//  @GSIM_A:3:ARRAY_OF(4) 
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define call(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR call (SEG_ID s_id, int *codeexit, int *args) MACRO_DEPRECATED;
#endif


/*! @deprecated This function allows an application to delete the last scheme loaded into the crypto processor. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 *	It shall be used when a scheme crashes (because of a protection fault, an access denied,...) or to free memory to be able to allocate a new scheme.
 *	In this case the crypto processor reset but the scheme is still remaining into memory. 
 *	It's impossible to load a new scheme before deleting this one. 
 *	@param s_id : component identifier.
 *	@return
 *	SERR codes : 
 *	- SERR_UNKNOWN_ID if the component identifier does not exist.
 *	- SERR_OK : component deleted .
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:dfree:KSFAM_KSU:0x05
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define dfree(a) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR dfree(SEG_ID s_id) MACRO_DEPRECATED;
#endif


/*! @deprecated This function allows an application: 
 *	 - To have the IDs list of both schemes and secret areas already created. 
 * 	 - To be able to verify that the loading / unloading has been correctly performed and managed. 
 *	 - It also allows to verify the creation of secret ID area. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 *	@param iAux : position in component ID table :
 *	 - 0 : means start from the beginning of the component table and get the first component Ids.
 *	 - 1 : means get next component Ids.
 *
 *	@param Id0 : pointer to structure SEG_ID
 *	@param Id1 : pointer to structure SEG_ID
 *	@param Id2 : pointer to structure SEG_ID
 *	@return 
 *	 SERR codes : 
 *	 - SERR_OK.
 *	 - SERR_KO.
 *
 *	@note
 *	 - IDs 0x80000001 and 0x80000002 are reserved and used by crypto precessor OS (owner SMO) 
 *	 - ID 0x40002030 (secret area) is used by the PP30 (owner SMO). 
 *
 *	This part of code is given under src directory in file CheckSch.c 
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:ddir:KSFAM_KSU:0x06
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER 
//  @GSIM_A:4:ONE_POINTER 
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define ddir(a,b,c,d) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR ddir(int iAux,SEG_ID *Id0,SEG_ID *Id1,SEG_ID *Id2) MACRO_DEPRECATED;
#endif

/*! @deprecated Load Booster System in Booster memory.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id : component identifier.
 *	@param src : Booster system.
 *	@param size : system size.
 *	@return
 *	SERR code.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:copy_systeme:KSFAM_KSU:0x03
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define copy_systeme(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR copy_systeme(SEG_ID s_id, char *src, int size) MACRO_DEPRECATED;
#endif

/*! @deprecated dallocUSB allocates a component in a non secure area of the peripheral connected via USB link. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 *	It Allocates a buffer in non secure area of the peripheral.
 *	@param s_id : component identifier ( a buffer ). Type = int.
 *	@param size : number of bytes allocated.
 *	@return
 *	 - A pointer on allocated buffer if positive. 
 *	 - SERR code if negative.
 *	 - SERR_OK (0)
 *	 - SERR_FULL (-1)
 *	 - SERR_ALREADY_DEFINED (-2)
 *	 - SERR_UNKNOWN_ID (-3) (when keyboard is desactivated for instance)
 *	 - SERR_NOT_ENOUGH_MEMORY (-4)
 *	 - SERR_INITIATIZED (-5) 
 *	 - SERR_JUSTDOWNLOADED (-6) 
 *	 - SERR_INCOHERANT_PARAM (-7) 
 *	 - SERR_KO (-8)
 *	 - SERR_NOT_FOUND (SERR) (-9)
 *	 - SERR_PB_ON_NEW_AD (SERR) (-10)
 *	 - SERR_WARNING_ON_NEW_AD (SERR) (-11)
 *	 - SERR_CERTIFICAT_KO (SERR) (-12)
 *	 - SERR_UNAUTHORIZED (SERR) (-13)
 *	 - SERR_CALL_EXIT_BY_RESET (SERR) (-50)
 *	 - SERR_CERTIFICAT_APP_KO (SERR) (-51)
 *	 - SERR_SIGNATURE_APP_KO (SERR) (-52)
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:dallocUsb:KSFAM_KSU:0x07
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define dallocUsb(a,b) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR dallocUsb (SEG_ID s_id, int size) MACRO_DEPRECATED;
#endif

/*! @deprecated copyUSB loads a component into the memory allocated for it in the peripheral connected via the USB link. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id : segment identifier. 
 *	@param src  : buffer to be copied.
 *	@param size : size to be copied.
 *	@return
 *	SERR code :
 *	 - SERR_OK 
 *	 - SERR_UNKNOWN_ID
 *	 - SERR_NOT_ENOUGH_MEMORY
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:copyUsb:KSFAM_KSU:0x08
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define copyUsb(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR copyUsb (SEG_ID s_id, char *src, int size) MACRO_DEPRECATED;
#endif


/*! @deprecated This function is used to set CRC16 on the component identifier allocated in the peripheral connected via the USB link.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id : component identifier ( a buffer ).
 *	@return 
 *	SERR code.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:putcrcUsb:KSFAM_KSU:0x09
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define putcrcUsb(a) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR putcrcUsb(SEG_ID s_id) MACRO_DEPRECATED;
#endif

/*! @deprecated Execute a SCHEME identified by its identifier in the peripheral connected via the USB link.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id     : component identifier.
 *	@param codeexit : error returned by the component.
 *	@param args     : parameters of component passing by value or by address. (4 int)
 *	@return
 *	SERR code. 
 *	See exit code on component error. 
 *	-9 is specific code that is returned when call is interrupted by a KSU software 
 *	reset ( only on EFT30 ).
 *	@note
 *	 - Only scheme with a valid CRC16 and valid RSA signature can be executed. 
 *	 - RSA signature is verified once after component loading.
 *	 - arg1, arg2, arg3 arg4 are parameters that are declared at scheme entry point routine ( main ).
 *	 - Codeexit is the return code of scheme entry point routine ( main ).
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:callUsb:KSFAM_KSU:0x0A
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ARRAY_OF(4) 
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define callUsb(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR callUsb (SEG_ID s_id, int *codeexit, int *args) MACRO_DEPRECATED;
#endif

/*! @deprecated This function allows an application to delete the last scheme loaded into the peripheral connected via the USB link. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param s_id : component identifier.
 *	@return
 *	 SERR codes :
 *	 - SERR_UNKNOWN_ID if the component identifier does not exist.
 *	 - SERR_OK : component deleted .
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:dfreeUsb:KSFAM_KSU:0x0B
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define dfreeUsb(a) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR dfreeUsb(SEG_ID s_id) MACRO_DEPRECATED;
#endif

/*! @deprecated This function lists the Ids of all allocated component in the peripheral connected via USB link.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param iAux : position in component ID table :
 *	 - 0 : means start from the beginning of the component table and get the first component Ids.
 *	 - 1 : means get next component Ids.
 *
 *	@param Id0 : pointer to structure SEG_ID
 *	@param Id1 : pointer to structure SEG_ID
 *	@param Id2 : pointer to structure SEG_ID
 *	@return 
 *	 SERR codes : 
 *	 - SERR_OK.
 *	 - SERR_KO.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:ddirUsb:KSFAM_KSU:0x0C
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define ddirUsb(a,b,c,d) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR ddirUsb(int iAux,SEG_ID *Id0,SEG_ID *Id1,SEG_ID *Id2) MACRO_DEPRECATED;
#endif

#define _INTERNAL_INTER_UC		0									/*!< @deprecated INTER UC TYPE : Internal USART        */
#define _USB_PINPAD_INTER_UC	1									/*!< @deprecated INTER UC TYPE : External USB (PINPAD,CLESS...) */
//#define _USB_CLESS_INTER_UC	2
#define _USB_READER_INTER_UC	3									/*!< @deprecated INTER UC TYPE : External USB (CAD30USR...)    */



/*! @deprecated dalloc allocates a component in a non secure area. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 *	Allocates a buffer in non secure area of KSU.
 *	@param i_uc_type : defines where the scheme will be executed: 
 *	 - _INTERNAL_INTER_UC   : internal.
 *	 - _USB_PINPAD_INTER_UC : on the pinpad.
 *	 - other for future use.
 *	@param s_id : component identifier (a buffer). type int.
 *	@param size : number of bytes allocated.
 *	@return
 *	 - A pointer on allocated buffer if positive.
 *	 - SERR code if negative : 
 *	 - SERR_OK (0)
 *	 - SERR_FULL (-1)
 *	 - SERR_ALREADY_DEFINED (-2)
 *	 - SERR_UNKNOWN_ID (-3) (when keyboard is desactivated for instance)
 *	 - SERR_NOT_ENOUGH_MEMORY (-4)
 *	 - SERR_INITIATIZED (-5) 
 *	 - SERR_JUSTDOWNLOADED (-6) 
 *	 - SERR_INCOHERANT_PARAM (-7) 
 *	 - SERR_KO (-8)
 *	 - SERR_NOT_FOUND (SERR) (-9)
 *	 - SERR_PB_ON_NEW_AD (SERR) (-10)
 *	 - SERR_WARNING_ON_NEW_AD (SERR) (-11)
 *	 - SERR_CERTIFICAT_KO (SERR) (-12)
 *	 - SERR_UNAUTHORIZED (SERR) (-13)
 *	 - SERR_CALL_EXIT_BY_RESET (SERR) (-50)
 *	 - SERR_CERTIFICAT_APP_KO (SERR) (-51)
 *	 - SERR_SIGNATURE_APP_KO (SERR) (-52)
 *
 *	@note The pointer is used on allocation and for the component copy. Then application must use the segment identifier.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:dallocGeneric:KSFAM_KSU:0x0F
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define dallocGeneric(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR dallocGeneric (unsigned char i_uc_type, SEG_ID s_id, int size) MACRO_DEPRECATED;
#endif

/*! @deprecated copy loads a component into the memory allocated for it. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 *	This is the way to initialise a KSU component from a EFT30 application as far as component identifier and size is known.
 *	@param i_uc_type : defines where the scheme will be executed : 
 *	- _INTERNAL_INTER_UC   : internal.
 *	- _USB_PINPAD_INTER_UC : on the pinpad.
 *	- other for future use.
 *
 *	@param s_id : segment identifier.
 *	@param src  : buffer to be copied.
 *	@param size :size to be copied.
 *	@return SERR code : 
 *	 - SERR_OK 
 *	 - SERR_UNKNOWN_ID
 *	 - SERR_NOT_ENOUGH_MEMORY
 *
 *	@note
 *	if size > size allocated for s_id, it will be truncated.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:copyGeneric:KSFAM_KSU:0x10
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define copyGeneric(a,b,c,d) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR copyGeneric (unsigned char i_uc_type, SEG_ID s_id, char *src, int size) MACRO_DEPRECATED;
#endif


/*! @deprecated This function is used to set CRC16 on the component identifier.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param i_uc_type : defines where the scheme will be executed : 
 *	 - _INTERNAL_INTER_UC   : internal.
 *	 - _USB_PINPAD_INTER_UC : on the pinpad.
 *	 - other for future use.
 *
 *	@param s_id : component identifier (a buffer).
 *	@return
 *	 SERR code.
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:putcrcGeneric:KSFAM_KSU:0x11
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define putcrcGeneric(a,b) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR putcrcGeneric(unsigned char i_uc_type, SEG_ID s_id) MACRO_DEPRECATED;
#endif

/*! @deprecated Execute a SCHEME identified by its identifier and suspend calling sheme execution.\n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	@param i_uc_type : defines where the scheme will be executed : 
 *	 - _INTERNAL_INTER_UC   : internal.
 *	 - _USB_PINPAD_INTER_UC : on the pinpad.
 *	 - other for future use.
 *
 *	@param s_id : component identifier.
 *	@param codeexit : error returned by the component.
 *	@param args : parameters of component passing by value or by address. (4 int)
 *	@return
 *	SERR code. 
 *	See exit code on component error. -9 is specific code that is returned when call is 
    interrupted by a KSU software reset ( only on EFT30 ).
 *	@note
 *	 - Only scheme with a valid CRC16 and valid RSA signature can be executed. 
 *	 - RSA signature is verified once after component loading.
 *	 - arg1, arg2, arg3, arg4 are parameters that are declared at scheme entry point routine ( main ).
 *	 - Codeexit is the return code of scheme entry point routine ( main ).
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:callGeneric:KSFAM_KSU:0x12
//  @GSIM_A:3:ONE_POINTER 
//  @GSIM_A:4:ARRAY_OF(4) 
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define callGeneric(a,b,c,d) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR callGeneric (unsigned char i_uc_type, SEG_ID s_id, int *codeexit, int *args) MACRO_DEPRECATED;
#endif


/*! @deprecated This function allows an application to delete the last scheme loaded into the crypto processor. \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *
 *	It shall be used when a scheme crashes (because of a protection fault, an access denied,...) or to free memory to be able to allocate a new scheme.
 *	In this case the crypto processor reset but the scheme is still remaining into memory. 
 *	It's impossible to load a new scheme before deleting this one. 
 *	@param i_uc_type : defines where the scheme will be executed : 
 *	- _INTERNAL_INTER_UC    : internal.
 *	 - _USB_PINPAD_INTER_UC : on the pinpad.
 *	 - other for future use.
 *	@param s_id : component identifier.
 *	@return
 *	 SERR codes : 
 *	 - SERR_UNKNOWN_ID if the component identifier does not exist.
 *	 - SERR_OK : component deleted .
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:dfreeGeneric:KSFAM_KSU:0x13
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define dfreeGeneric(a,b) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR dfreeGeneric(unsigned char i_uc_type, SEG_ID s_id) MACRO_DEPRECATED;
#endif

/*! @deprecated This function allows an application: \n
 *  Information on deprecation of this function is available @link KSFAM_KSU here @endlink\n
 *	 - To have the IDs list of both schemes and secret areas already created. 
 *	 - To be able to verify that the loading / unloading has been correctly performed and managed. 
 *	 - It also allows to verify the creation of secret ID area. 
 *
 *	@param i_uc_type : defines where the scheme will be executed : 
 *	 - _INTERNAL_INTER_UC : internal.
 *	 - _USB_PINPAD_INTER_UC : on the pinpad.
 *	 - other for future use.
 *
 *	@param suite : position in component ID table :
 *	 - 0 : means start from the beginning of the component table and get the first component Ids.
 *	 - 1 : means get next component Ids.
 *
 *	@param id : pointer to array of 3 SEG_ID structures.
 *	@return 
 *	 SERR codes : 
 *	 - SERR_OK.
 *	 - SERR_KO.
 *
 *	@note
 *	 - IDs 0x80000001 and 0x80000002 are reserved and used by crypto precessor OS (owner SMO) 
 *	 - ID 0x40002030 (secret area) is used by the PP30 (owner SMO). 
 *
 *	 This part of code is given under src directory in file CheckSch.c 
 *
 *	@link KSFAM_KSU Back to top @endlink
  */ 
// \if SIMULATION
//  @GSIM_F:ddirGeneric:KSFAM_KSU:0x14
//  @GSIM_A:0:ONE_POINTER 
//  @GSIM_A:3:ARRAY_OF(3) 
// \endif
#ifndef _DEPRECATED_SCHEMES_SDK96_
#define ddirGeneric(a,b,c) ERROR_Deprecation_For_Module_Schemes_SeeDLLSecurityDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for NomModule.
You can remove this error by adding _DEPRECATED_SCHEMES_SDK96_. Please do the necessary to clean your
code.*/
#else
extern SERR ddirGeneric(unsigned char i_uc_type, int suite, SEG_ID *id ) MACRO_DEPRECATED;
#endif

#endif
/*! @}  */ 

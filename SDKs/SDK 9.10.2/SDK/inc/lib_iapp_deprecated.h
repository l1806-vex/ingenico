 
#ifndef _LIBIAPP_DEPRECATED_H_
#define _LIBIAPP_DEPRECATED_H_

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




#ifndef _DEPRECATED_IAPP_SDK980_

/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchGetSync ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchPutSync ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchGetChar ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchPutChar ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchGetData ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchPutData ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/

/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchGetCharEvent ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchGetDataEvent ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/
/*!  
 * @brief IAPP will not be supported in Telium+ framework. Please use DLL Security.
 * @brief To continue to use this function add _DEPRECATED_IAPP_SDK980_ in you compilation defines.
*/
#define IAPP_SchPutDataEvent ERROR_Deprecation_For_ModuleIAPP_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IAPP. You can remove this error by adding _DEPRECATED_IAPP_SDK980_. Please do the necessary to clean your code.*/


#else /* _DEPRECATED_IAPP_SDK980_ */

int IAPP_SchGetSync (int Timeout, T_IAPPSync *Synchro, FILE *Iapp) MACRO_DEPRECATED;
int IAPP_SchPutSync (T_IAPPSync Synchro, FILE *Iapp) MACRO_DEPRECATED;
int IAPP_SchGetChar (int Timeout, char * ptcData, FILE *Iapp) MACRO_DEPRECATED;
int IAPP_SchPutChar (char Data, FILE *Iapp) MACRO_DEPRECATED;
int IAPP_SchGetData (int Timeout, unsigned char *Data, unsigned int NbData, FILE *Iapp) MACRO_DEPRECATED;
int IAPP_SchPutData (unsigned char *Data, unsigned int NbData , FILE *Iapp) MACRO_DEPRECATED;

int IAPP_SchGetCharEvent(int Timeout, char * ptcData, FILE* Iapp, unsigned int *pt_iEvents) MACRO_DEPRECATED;
int IAPP_SchGetDataEvent(int Timeout, unsigned char* Data, unsigned int DataSize, FILE *Iapp,
						 unsigned int *pt_iEvents) MACRO_DEPRECATED;
int IAPP_SchPutDataEvent(unsigned char* Data, unsigned int DataSize, FILE* Iapp,
						 unsigned int *pt_iEvents) MACRO_DEPRECATED;

#endif


#endif

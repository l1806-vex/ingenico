#ifndef __IMG_H__
#define __IMG_H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \addtogroup KSFAM_IMAGE_DLL 
//! @{
    
//! \defgroup IMAGE_FORMAT Supported formats
//! \brief This section describes the image formats supported by the DLL.
//! @{
    
#define __IMG_FORMAT_BMP    ( 1 << 0 ) //!< BMP format.
#define __IMG_FORMAT_JPG    ( 1 << 1 ) //!< JPG format (JPG DLL must be loaded).
#define __IMG_FORMAT_GIF    ( 1 << 2 ) //!< GIF format. This format is not supported.
#define __IMG_FORMAT_PNG    ( 1 << 3 ) //!< PNG format (PNG DLL must be loaded).
    
//! @}

//! \defgroup IMAGE_ERROR Error codes
//! \brief This section describes the error codes returned by the DLL.\n
//! @{
    
#define	__IMG_OK							( 0) //!< No error.
#define	__IMG_ERROR_INVALID_HANDLE			(-1) //!< The handle passed to the function is not valid.
#define	__IMG_ERROR_INVALID_FORMAT			(-2) //!< The format passed to the function is not valid.
#define	__IMG_ERROR_FORMAT_NOT_SUPPORTED	(-3) //!< The format passed to the function is not supported.
    
//! @}

//! \defgroup IMAGE_EXIT Exit codes
//! \brief This section describes the exit codes for the DLLs.
//! @{

#define DLL_IMG_EXIT     (-30000) //!< Base exit code for the IMG DLL.
#define DLL_JPG_EXIT     (-31000) //!< Base exit code for the JPG DLL.
#define DLL_PNG_EXIT     (-32000) //!< Base exit code for the PNG DLL.

//! @}

//! \defgroup IMAGE_API API of the DLL
//! \brief This section describes the API exported by the DLL.
//! @{

//! \brief Image handle, created by a call to \ref IMG_Load().
typedef void *IMAGE_HANDLE;

//! \brief Reading callback context. This context is given to the callback at every call.
typedef void *T_IMAGE_READ_CONTEXT;

//! \brief Prototype of the reading callback.
//! @param[out] pBuffer  Buffer to be filled by the callback.
//! @param[in]  nSize    Size of the buffer.
//! @param[in]  pContext Context of the callback, given using \ref IMG_Load().
//! @return     The size of the data read, or a negative value if an error occured.
typedef int(*T_IMAGE_READ_CALLBACK)(char* pBuffer,long nSize,T_IMAGE_READ_CONTEXT pContext);

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMGlib_open() ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief  Open the Image DLL.
//! @return 0 or \ref OL_ALREADY_LOADED on success, other values on error (see \ref loaderapi.h).
int IMGlib_open( void ) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMGlib_close() ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief  Close the Image DLL.
void IMGlib_close( void ) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMG_Load(a,b,c) ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief Load an image.
//! @param[in] nImageType    Type of the image. See \ref IMAGE_FORMAT for the possible values.
//! @param[in] pReadCallback Reading callback function.
//! @param[in] pReadContext  Context passed at every call of the callback function.
//! @return    Non-NULL on success, NULL otherwise. If the handle returned is not NULL, it must be freed using \ref IMG_Unload().
IMAGE_HANDLE IMG_Load( int nImageType, T_IMAGE_READ_CALLBACK pReadCallback, T_IMAGE_READ_CONTEXT pReadContext ) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMG_Unload(a) ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief Free all the ressources of the image.
//! @param[in] hImg Image handle.
//! @return    \ref __IMG_OK on success, a negative error code otherwise (see \ref IMAGE_ERROR).
int IMG_Unload( IMAGE_HANDLE hImg ) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMG_GetBitmapBuffer(a) ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief Retrieve the internal bitmap.
//! @param[in] hImg Handle on the image.
//! @return    A pointer on the data which can be passed to functions like \ref GetBmpInfos().
unsigned char* IMG_GetBitmapBuffer( IMAGE_HANDLE hImg ) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMG_GetSupportedFormat() ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief Get the image formats supported by the DLL.
//! @return A mask of the supported format, made of the values described in \ref IMAGE_FORMAT.
unsigned int IMG_GetSupportedFormat( void ) MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_IMG_SDK090800_
#define IMG_GetSize(a,b,c) ERROR_Deprecation_For_ModuleIMG_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module IMG. You can remove this error by adding _DEPRECATED_IMG_SDK090800_. Please do the necessary to clean your code.*/
#else
//! \brief IMG will not be supported in Telium+ framework. Please use GOAL instead.
//! \brief To continue to use this function add _DEPRECATED_IMG_SDK090800_ in you compilation defines.
//! \brief Get the size of the image.
//! @param[in]  hImg    Image handle.
//! @param[out] pWidth  Pointer to store the width of the image (in pixel).
//! @param[out] pHeight Pointer to store the height of the image (in pixel).
//! @return    \ref __IMG_OK on success, a negative error code otherwise (see \ref IMAGE_ERROR).
int IMG_GetSize( IMAGE_HANDLE hImg, unsigned int* pWidth, unsigned int* pHeight ) MACRO_DEPRECATED;
#endif





//! @}

//! \defgroup IMAGE_SAMPLE Image sample
//! \brief Code sample to display an image on the screen.
//! @{

//! \include IMG__Sample_01.c
//! @}

//! @}

#ifdef __cplusplus
}
#endif

#endif //__IMG_H__

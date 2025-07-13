#ifndef __IMG_H__
#define __IMG_H__

#ifdef __cplusplus
extern "C"
{
#endif

// Image format supported
#define __IMG_FORMAT_BMP    ( 1 << 0 )
#define __IMG_FORMAT_JPG    ( 1 << 1 )
#define __IMG_FORMAT_GIF    ( 1 << 2 ) // Not supported yet !
#define __IMG_FORMAT_PNG    ( 1 << 3 )

#define	__IMG_OK							( 0)
#define	__IMG_ERROR_INVALID_HANDLE			(-1)
#define	__IMG_ERROR_INVALID_FORMAT			(-2)
#define	__IMG_ERROR_FORMAT_NOT_SUPPORTED	(-3)


typedef void *IMAGE_HANDLE;
typedef void *T_IMAGE_READ_CONTEXT;
typedef int(*T_IMAGE_READ_CALLBACK)(char*,long,T_IMAGE_READ_CONTEXT);

#define DLL_IMG_EXIT     (-30000)
#define DLL_JPG_EXIT     (-31000)
#define DLL_PNG_EXIT     (-32000)

// DLL Management
int  IMGlib_open( void );
void IMGlib_close( void );

// API
IMAGE_HANDLE IMG_Load  ( int nImageType, T_IMAGE_READ_CALLBACK pReadCallback, T_IMAGE_READ_CONTEXT pReadContext );
int          IMG_Unload( IMAGE_HANDLE hImg );

unsigned char* IMG_GetBitmapBuffer( IMAGE_HANDLE hImg );
unsigned int   IMG_GetSupportedFormat( void );
int            IMG_GetSize( IMAGE_HANDLE hImg, unsigned int* pWidth, unsigned int* pHeight );

#ifdef __cplusplus
}
#endif

#endif //__IMG_H__

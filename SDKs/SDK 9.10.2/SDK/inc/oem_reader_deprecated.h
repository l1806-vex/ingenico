#ifndef OEM_READER_DEPRECATED_H
#define OEM_READER_DEPRECATED_H
 
#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated Reader_Mount is obsolete. You have to use ExtReader library */
#define Reader_Mount(a,b) ERROR_Deprecation_For_Function_Reader_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated Reader_Mount is obsolete. You have to use ExtReader library */
int Reader_Mount( int i_i_type, char* lien ) MACRO_DEPRECATED;

#endif


#endif


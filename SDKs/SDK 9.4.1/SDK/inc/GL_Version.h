#ifndef GL_Version_h_INCLUDED
#define GL_Version_h_INCLUDED

#ifdef __cplusplus
extern "C" 
{
#endif 

#define GL_VERSION_DLL     3
#define GL_REVISION_DLL    23
#define GL_COMPANY_NAME    "Ingenico"
#define GL_LEGAL_COPYRIGHT "Ingenico. Tous droits réservés."
#define GL_FAMILY_NAME     "GRAPHIC_LIBRARY"

/** Check if DLL is present
@return 1 if DLL is present 0 otherwise */
int GL_IsPresent(void);

#ifdef __cplusplus
}
#endif 

#endif

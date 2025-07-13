#ifndef OSL_Version_h_INCLUDED
#define OSL_Version_h_INCLUDED

#ifdef __cplusplus
extern "C" 
{
#endif 

#define OSL_VERSION_DLL     1
#define OSL_REVISION_DLL    04
#define OSL_COMPANY_NAME    "Ingenico"
#define OSL_LEGAL_COPYRIGHT "Ingenico. Tous droits réservés."
#define OSL_FAMILY_NAME     "OSLAYER"
#define OSL_APPLI_TYPE      0x8022

	/** Check if OSlayer is present
	@return 1 if OSlayer is present 0 otherwise */
	int OSL_IsPresent(void);
#ifdef __cplusplus
}
#endif 

#endif

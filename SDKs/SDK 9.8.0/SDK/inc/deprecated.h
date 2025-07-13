/*! @addtogroup KSFAM_DEPRECATED
	* @{
**/
#ifndef DEPREC_H
#define DEPREC_H

#ifdef _DEPRECATED_MANAGER_SDK980_
/*! @deprecated This function must not be used by application
*
 *  @deprecated For compatibility purpose only, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_MANAGER_SDK980_
 *
*/
extern int SetRegionColor(int left,int top,int right,int bottom);

/*! @deprecated This function must not be used by application
*
 *  @deprecated For compatibility purpose only, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_MANAGER_SDK980_
 *
*/
extern int GetRegionColor(int *left,int *top,int *right,int *bottom);

/*! @deprecated This function must not be used by application
*
 *  @deprecated For compatibility purpose only, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_MANAGER_SDK980_
 *
*/
extern int ClearRegionColor(void) ;
#endif

/*! @deprecated This function must not be used by application, use PSQ_write_state_param
*
 *  @deprecated For compatibility purpose only, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_MANAGER_SDK980_
 *
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define PSQ_update_state_param ERROR_Deprecation_For_Module_PSQ_update_state_param_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for PSQ_update_state_param.
You can remove this error by adding _DEPRECATED_MANAGER_SDK980_. 
Please do the necessary to clean your code.*/
#else
extern void      PSQ_update_state_param(S_STATE_PARAM *param) MACRO_DEPRECATED;
#endif

#endif
/*! @} **/


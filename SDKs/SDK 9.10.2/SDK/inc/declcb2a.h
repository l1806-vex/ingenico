/*! @addtogroup KSFAM_CB2A
	* @{
**/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DECLCB2A_
#define _DECLCB2A_
typedef void (*PFONCCB2A)  (void);
/*
======================================================================
			Data Structures Definition
======================================================================
*/

 
typedef struct
{
	NO_SEGMENT noappli; /*!< num of the application. */
    PFONCCB2A  fct[60];  /*!< typedef. */
} StructFctCb2a;



/*! @brief french domain only Initialization of the pointers on API control cb2a  (CB2A layer)
* @param pt_fct : pointer to structure StructFctCb2a.
 *
 * @link KSFAM_CB2A Back to top @endlink
*/
void InitPtFctCb2a(StructFctCb2a *pt_fct);


#endif

/*! @} **/
#ifdef __cplusplus
}
#endif

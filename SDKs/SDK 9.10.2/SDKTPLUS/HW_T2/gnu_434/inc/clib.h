#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CLIB_H
#define _CLIB_H
//! \addtogroup KSFAM_AUTRES_MANAGER
//! @{

/*! @brief Returns the signed integer value of string
* @param s: string terminated by a \\0
* @return integer result.
*/
int    atoi( const char *s);


/*! @brief Returns the signed floating point value of string
* @param string: string terminated by a \\0
* @return  float result.
*/
double atof( const char *string );

/*! @} **/
#endif
#ifdef __cplusplus
}
#endif

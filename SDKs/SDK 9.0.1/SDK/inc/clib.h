#ifndef _CLIB_H
#define _CLIB_H
//! \addtogroup KSFAM_AUTRES_MANAGER
//! @{

/*! @brief Returns the signed integer value of string
* @param s: string terminated by a \\0
* @return integer result.
// \if SIMULATION
//  @GSIM_F:atoi:KSFAM_AUTRES_MANAGER:
// \endif
*/
int    atoi( const char *s);


/*! @brief Returns the signed floating point value of string
* @param string: string terminated by a \\0
* @return  float result.
// \if SIMULATION
//  @GSIM_F:atof:KSFAM_AUTRES_MANAGER:
// \endif
*/
double atof( const char *string );

/*! @} **/
#endif

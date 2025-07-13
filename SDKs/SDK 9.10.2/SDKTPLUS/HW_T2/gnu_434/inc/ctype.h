            
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTYPE_H
#define _CTYPE_H
//! \addtogroup KSFAM_AUTRES_MANAGER
//! @{



/*! @brief Returns a nonzero number if the character in __c is an upper_case alphabetic character, return 0 otherwise\n
Upper-case alphabetic characters are A through Z
@param __c: one integer
@return integer result or 0.
*/
extern  int     isupper (int __c);


/*! @brief  Returns a nonzero number if the character in __c is an lower_case alphabetic character, return 0 otherwise\n
lower-case alphabetic characters are a through z
@param __c: one integer
@return integer result or 0.
*/
extern  int     islower (int __c);

/*! @brief Returns a nonzero number if the character in __c is an alphabetic characters (A through Z, a through z and 0 through 9)
@param __c : one integer
@return integer result or 0.
*/
extern  int     isalpha (int __c);


/*! @brief Returns a nonzero number if the character in __c is a digit character (0 through 9)
@param __c: one integer
@return integer result or 0.
*/
extern  int     isdigit (int __c);


/*! @brief Returns a nonzero number if the character in __c is an hexadecimal digit character (0 through 9, A through F and a through f)
@param __c: one integer
@return integer result or 0.
*/
extern  int     isxdigit (int __c);


/*! @brief Returns a nonzero number if the character in __c is a space character
@param __c: one integer
@return integer result or 0.
*/
extern  int     isspace (int __c);


/*! @brief Returns a nonzero number if the character in __c is a punctuation character
@param __c: one integer
@return integer result or 0.
*/
extern  int     ispunct (int __c);


/*! @brief Returns a nonzero number if the character in __c is an alphanumeric characters (0 through 9, A through Z and a through z)
@param __c: one integer
@return integer result or 0.
*/
extern  int     isalnum (int __c);


/*! @brief Returns a nonzero number if the character in __c is a graphic character 
 
@param __c: one integer
@return integer result or 0.
*/
extern  int     isgraph (int __c);


/*! @brief Returns a nonzero number if the character in __c is a printable character 
@param __c: one integer
@return integer result or 0.
*/
extern  int     isprint (int __c);


/*! @brief Returns a nonzero number if the character in __c is a control character 
@param __c: one integer
@return integer result or 0.
*/
extern  int     iscntrl (int __c);

/*! @brief Convert the value of its argument __c to an upper-case letter\n 
-If __c is not an lower-case letter the conversion is not performed
@param __c: one integer
@return __c  or the value converted 
*/
extern  int     toupper (int __c);


/*! @brief Convert the value of its argument __c to an lower-case letter \n
If __c is not a upper-case letter the conversion is not performed
@param __c: one integer
@return __c  or the value converted 
*/
extern  int     tolower (int __c);

                                                                              
#endif 


/*! @} **/





#ifdef __cplusplus
}
#endif

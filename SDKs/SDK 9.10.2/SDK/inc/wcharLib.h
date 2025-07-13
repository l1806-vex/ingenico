#ifdef __cplusplus
extern "C" {
#endif

#ifndef WCHARLIB_H
#define WCHARLIB_H

/*! @addtogroup KSFAM_USQ
	* @{
**/

typedef unsigned short TM_wchar_t;



/*! @brief   wcslen - get wide-character string length 
* - The wcslen() function computes the number of wide-character codes in the wide-character string to which ws points, not including the terminating null wide-character code. 
*	@param   s: size_t wcslen(const TM_wchar_t *ws);
*	@return   The wcslen() function returns the length of ws; no return value is reserved to indicate an error. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 169) if function does not exist
*/
extern int Telium_Wcslen(const TM_wchar_t *s);



/*! @brief   wcschr - wide-character string scanning operation
* - The wcschr() function locates the first occurrence of wc in the wide-character string pointed to by ws. The value of wc must be a character representable as a type TM_wchar_t and must be a wide-character code corresponding to a valid character in the current locale. The terminating null wide-character code is considered to be part of the wide-character string. 
*	@param s:  Null-terminated source string
*	@param c:  Character to be located.
*	@return   Upon completion, wcschr() returns a pointer to the wide-character code, or a null pointer if the wide-character code is not found. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 170) if function does not exist
*/
extern TM_wchar_t * Telium_Wcschr(const TM_wchar_t *s,TM_wchar_t c);


/*! @brief   wcsncpy - copy part of a wide-character string 
* - The wcsncpy() function copies not more than n wide-character codes (wide-character codes that follow a null wide-character code are not copied) from the array pointed to by ws2 to the array pointed to by ws1. If copying takes place between objects that overlap, the behaviour is undefined. 
*	@param s1 :Destination string. 
*	@param s2 :Source string.
*	@param n  :Number of characters to be copied.
*	@return The wcsncpy() function returns ws1; no return value is reserved to indicate an error. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 171) if function does not exist
*/
extern TM_wchar_t * Telium_Wcsncpy(TM_wchar_t * s1,const TM_wchar_t * s2,size_t n);


/*! @brief   wcscat - concatenate two wide-character strings 
* - The wcscat() function appends a copy of the wide-character string pointed to by ws2 (including the terminating null wide-character code) to the end of the wide-character string pointed to by ws1. The initial wide-character code of ws2 overwrites the null wide-character code at the end of ws1. If copying takes place between objects that overlap, the behaviour is undefined. 
*	@param  s1: Null-terminated destination string
*	@param  s2: Null-terminated source string
*	@return The wcscat() function returns ws1; no return value is reserved to indicate an error. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 172) if function does not exist
*/
extern TM_wchar_t * Telium_Wcscat(TM_wchar_t * s1,const TM_wchar_t * s2);



/*! @brief   wcscmp - compare two wide-character strings
* - The wcscmp() function compares the wide-character string pointed to by ws1 to the wide-character string pointed to by ws2. 
* - The sign of a non-zero return value is determined by the sign of the difference between the values of the first pair of wide-character codes that differ in the objects being compared. 
*	@param  s1: Null-terminated destination string
*	@param  s2: Null-terminated source string
*	@return Upon completion, wcscmp() returns an integer greater than, equal to or less than 0, if the wide-character string pointed to by ws1 is greater than, equal to or less than the wide-character string pointed to by ws2 respectively. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 173) if function does not exist
*/
extern int Telium_Wcscmp(const TM_wchar_t * s1,const TM_wchar_t * s2);



/*! @brief   wcscpy - copy a wide-character string 
*-  The wcscpy() function copies the wide-character string pointed to by ws2 (including the terminating null wide-character code) into the array pointed to by ws1. If copying takes place between objects that overlap, the behaviour is undefined. 
*	@param  s1: Null-terminated destination string
*	@param  s2: Null-terminated source string
*	@return The wcscpy() function returns s1; no return value is reserved to indicate an error. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 174) if function does not exist
*/
extern TM_wchar_t * Telium_Wcscpy(TM_wchar_t * s1,const TM_wchar_t * s2);

/*! @brief   wcsncat - concatenate part of two wide-character strings 
* -The wcsncat() function appends not more than n wide-character codes (a null wide-character code and wide-character codes that follow it are not appended) from the array pointed to by ws2 to the end of the wide-character string pointed to by ws1. The initial wide-character code of ws2 overwrites the null wide-character code at the end of ws1. A terminating null wide-character code is always appended to the result. If copying takes place between objects that overlap, the behaviour is undefined. 
*	@param  s1: Null-terminated destination string
*	@param  s2: Null-terminated source string
*   @param  n: size of source string
*	@return The wcsncat() function returns s1; no return value is reserved to indicate an error. 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 175) if function does not exist
*/
extern TM_wchar_t * Telium_Wcsncat(TM_wchar_t * s1,const TM_wchar_t * s2,size_t n);

/*! @brief   The swprintf() function places output followed by the null wide-character in consecutive wide-characters starting at *s; no more than n wide-characters are written, including a terminating null wide-character, which is always added (unless n is zero). 
*  The swprintf() function formats its arguments under control of the format wide-character string. 
*   The format is composed of zero or more directives: ordinary wide-characters, which are simply copied to the output stream and conversion specifications, each of which results in the fetching of zero or more arguments. 
*   The results are undefined if there are insufficient arguments for the format. 
*   If the format is exhausted while arguments remain, the excess arguments are evaluated but are otherwise ignored. 
*   
*   Conversions can be applied to the nth argument after the format in the argument list, rather than to the next unused argument.
*   In this case, the conversion wide-character % (see below) is replaced by the sequence %n$, where n is a decimal integer in the range [1, {NL_ARGMAX}], giving the position of the argument in the argument list.
*   This feature provides for the definition of format wide-character strings that select arguments in an order appropriate to specific languages (see the EXAMPLES section). 
*   
*   In format wide-character strings containing the %n$ form of conversion specifications, numbered arguments in the argument list can be referenced from the format wide-character string as many times as required. 
*   
*   In format wide-character strings containing the % form of conversion specifications, each argument in the argument list is used exactly once. 
*   
*   All forms of the fwprintf() functions allow for the insertion of a language-dependent radix character in the output string, output as a wide-character value.
*   The radix character is defined in the program's locale (category LC_NUMERIC).
*   In the POSIX locale, or in a locale where the radix character is not defined, the radix character defaults to a period (.). 
*   
*   Each conversion specification is introduced by the % wide-character or by the wide-character sequence %n$, after which the following appear in sequence: 
*   
*   Zero or more flags (in any order), which modify the meaning of the conversion specification. 
*   An optional minimum field width.
*   If the converted value has fewer wide-characters than the field width, it will be padded with spaces by default on the left; it will be padded on the right, if the left-adjustment flag (-), described below, is given to the field width.
*   The field width takes the form of an asterisk (*), described below, or a decimal integer. 
*   
*   An optional precision that gives the minimum number of digits to appear for the d, i, o, u, x and X conversions; the number of digits to appear after the radix character for the e, E and f conversions; the maximum number of significant digits for the g and G conversions; or the maximum number of wide-characters to be printed from a string in s conversions.
*   The precision takes the form of a period (.) followed either by an asterisk (*), described below, or an optional decimal digit string, where a null digit string is treated as 0.
*   If a precision appears with any other conversion wide-character, the behaviour is undefined. 
*   
*   An optional l (ell) specifying that a following c conversion wide-character applies to a wint_t argument; an optional l specifying that a following s conversion wide-character applies to a wchar_t argument; an optional h specifying that a following d, i, o, u, x or X conversion wide-character applies to a type short int or type unsigned short int argument (the argument will have been promoted according to the integral promotions, and its value will be converted to type short int or unsigned short int before printing); an optional h specifying that a following n conversion wide-character applies to a pointer to a type short int argument; an optional l (ell) specifying that a following d, i, o, u, x or X conversion wide-character applies to a type long int or unsigned long int argument; an optional l (ell) specifying that a following n conversion wide-character applies to a pointer to a type long int argument; or an optional L specifying that a following e, E, f, g or G conversion wide-character applies to a type long double argument.
*   If an h, l or L appears with any other conversion wide-character, the behaviour is undefined. 
*   
*   A conversion wide-character that indicates the type of conversion to be applied. 
*   
*   A field width, or precision, or both, may be indicated by an asterisk (*).
*   In this case an argument of type int supplies the field width or precision.
*   Arguments specifying field width, or precision, or both must appear in that order before the argument, if any, to be converted.
*   A negative field width is taken as a - flag followed by a positive field width.
*   A negative precision is taken as if the precision were omitted.
*   In format wide-character strings containing the %n$ form of a conversion specification, a field width or precision may be indicated by the sequence *m$, where m is a decimal integer in the range [1, {NL_ARGMAX}] giving the position in the argument list (after the format argument) of an integer argument containing the field width or precision, for example: 
*   
*   wprintf(L"%1$d:%2$.*3$d:%4$.*3$d\n", hour, min, precision, sec); 
*   
*   The format can contain either numbered argument specifications (that is, %n$ and *m$), or unnumbered argument specifications (that is, % and *), but normally not both.
*   The only exception to this is that %% can be mixed with the %n$ form.
*   The results of mixing numbered and unnumbered argument specifications in a format wide-character string are undefined.
*   When numbered argument specifications are used, specifying the Nth argument requires that all the leading arguments, from the first to the (N-1)th, are specified in the format wide-character string. 
*   The flag wide-characters and their meanings are: 
*   
* -   '
*   The integer portion of the result of a decimal conversion (%i, %d, %u, %f, %g or %G) will be formatted with thousands' grouping wide-characters.
*   For other conversions the behaviour is undefined.
*   The non-monetary grouping wide-character is used. 
*
*-  -
*   The result of the conversion will be left-justified within the field.
*   The conversion will be right-justified if this flag is not specified. 
*
*-  +
*   The result of a signed conversion will always begin with a sign (+ or -).
*   The conversion will begin with a sign only when a negative value is converted if this flag is not specified. 
*   space
*   If the first wide-character of a signed conversion is not a sign or if a signed conversion results in no wide-characters, a space will be prefixed to the result.
*   This means that if the space and + flags both appear, the space flag will be ignored. 
*
*-  #
*   This flag specifies that the value is to be converted to an alternative form.
*   For o conversion, it increases the precision (if necessary) to force the first digit of the result to be 0.
*   For x or X conversions, a non-zero result will have 0x (or 0X) prefixed to it.
*   For e, E, f, g or G conversions, the result will always contain a radix character, even if no digits follow it.
*   Without this flag, a radix character appears in the result of these conversions only if a digit follows it.
*   For g and G conversions, trailing zeros will not be removed from the result as they normally are.
*   For other conversions, the behaviour is undefined.

*-  0
*   For d, i, o, u, x, X, e, E, f, g and G conversions, leading zeros (following any indication of sign or base) are used to pad to the field width; no space padding is performed.
*   If the 0 and - flags both appear, the 0 flag will be ignored.
*   For d, i, o, u, x and X conversions, if a precision is specified, the 0 flag will be ignored.
*   If the 0 and ' flags both appear, the grouping wide-characters are inserted before zero padding.
*   For other conversions, the behaviour is undefined. 
*   The conversion wide-characters and their meanings are: 
*   
*-  d, i
*   The int argument is converted to a signed decimal in the style [-]dddd.
*   The precision specifies the minimum number of digits to appear; if the value being converted can be represented in fewer digits, it will be expanded with leading zeros.
*   The default precision is 1.
*   The result of converting 0 with an explicit precision of 0 is no wide-characters. 
*
*-  o
*   The unsigned int argument is converted to unsigned octal format in the style dddd.
*   The precision specifies the minimum number of digits to appear; if the value being converted can be represented in fewer digits, it will be expanded with leading zeros.
*   The default precision is 1.
*   The result of converting 0 with an explicit precision of 0 is no wide-characters. 
*
*-  u
*   The unsigned int argument is converted to unsigned decimal format in the style dddd.
*   The precision specifies the minimum number of digits to appear; if the value being converted can be represented in fewer digits, it will be expanded with leading zeros.
*   The default precision is 1.
*   The result of converting 0 with an explicit precision of 0 is no wide-characters. 

*-  x
*   The unsigned int argument is converted to unsigned hexadecimal format in the style dddd; the letters abcdef are used.
*   The precision specifies the minimum number of digits to appear; if the value being converted can be represented in fewer digits, it will be expanded with leading zeros.
*   The default precision is 1.
*   The result of converting 0 with an explicit precision of 0 is no wide-characters. 
*
*-  X
*   Behaves the same as the x conversion wide-character except that letters ABCDEF are used instead of abcdef. 
*
*-  f
*   The double argument is converted to decimal notation in the style [-]ddd.ddd, where the number of digits after the radix character is equal to the precision specification.
*   If the precision is missing, it is taken as 6; if the precision is explicitly 0 and no # flag is present, no radix character appears.
*   If a radix character appears, at least one digit appears before it.
*   The value is rounded to the appropriate number of digits.
*   The fwprintf() family of functions may make available wide-character string representations for infinity and NaN. 

*-  e, E
*   The double argument is converted in the style [-]d.ddde±dd, where there is one digit before the radix character (which is non-zero if the argument is non-zero) and the number of digits after it is equal to the precision; if the precision is missing, it is taken as 6; if the precision is 0 and no # flag is present, no radix character appears.
*   The value is rounded to the appropriate number of digits.
*   The E conversion wide-character will produce a number with E instead of e introducing the exponent.
*   The exponent always contains at least two digits.
*   If the value is 0, the exponent is 0.
*   The fwprintf() family of functions may make available wide-character string representations for infinity and NaN.
*
*-  g, G
*   The double argument is converted in the style f or e (or in the style E in the case of a G conversion wide-character), with the precision specifying the number of significant digits.
*   If an explicit precision is 0, it is taken as 1.
*   The style used depends on the value converted; style e (or E) will be used only if the exponent resulting from such a conversion is less than -4 or greater than or equal to the precision.
*   Trailing zeros are removed from the fractional portion of the result; a radix character appears only if it is followed by a digit.
*   The fwprintf() family of functions may make available wide-character string representations for infinity and NaN. 
*
*-  c
*   If no l (ell) qualifier is present, the int argument is converted to a wide-character as if by calling the btowc() function and the resulting wide-character is written.
*   Otherwise the wint_t argument is converted to wchar_t, and written. 
*
*-  s
*   If no l (ell) qualifier is present, the argument must be a pointer to a character array containing a character sequence beginning in the initial shift state.
*   Characters from the array are converted as if by repeated calls to the mbrtowc() function, with the conversion state described by an mbstate_t object initialised to zero before the first character is converted, and written up to (but not including) the terminating null wide-character.
*   If the precision is specified, no more than that many wide-characters are written.
*   If the precision is not specified or is greater than the size of the array, the array must contain a null wide-character.
*   If an l (ell) qualifier is present, the argument must be a pointer to an array of type wchar_t.
*   Wide characters from the array are written up to (but not including) a terminating null wide-character.
*   If no precision is specified or is greater than the size of the array, the array must contain a null wide-character.
*   If a precision is specified, no more than that many wide-characters are written. 
*
*-  p
*   The argument must be a pointer to void.
*   The value of the pointer is converted to a sequence of printable wide-characters, in an implementation-dependent manner. 
*
*-  n
*   The argument must be a pointer to an integer into which is written the number of wide-characters written to the output so far by this call to one of the fwprintf() functions.
*   No argument is converted.
*
*-  C
*   Same as lc. 
*
*-  S
*   Same as ls. 
*
*-  %
*   Output a % wide-character; no argument is converted.
*   The entire conversion specification must be %%. 
*   If a conversion specification does not match one of the above forms, the behaviour is undefined. 
*   
*   In no case does a non-existent or small field width cause truncation of a field; if the result of a conversion is wider than the field width, the field is simply expanded to contain the conversion result.
*   Characters generated by fwprintf() and wprintf() are printed as if fputwc() had been called. 
*   
*   The st_ctime and st_mtime fields of the file will be marked for update between the call to a successful execution of fwprintf() or wprintf() and the next successful completion of a call to fflush() or fclose() on the same stream or a call to exit() or abort(). 
*   
*	@return
*   Upon successful completion, these functions return the number of wide-characters transmitted excluding the terminating null wide-character in the case of swprintf() or a negative value if an output error was encountered.
*   If n or more wide characters were requested to be written swprintf() returns a negative value. 
* ERRORS
*   For the conditions under which fwprintf() and wprintf() will fail and may fail, refer to fputwc(). 
*   In addition, all forms of fwprintf() may fail if: 
*   
*   [EILSEQ]
*   A wide-character code that does not correspond to a valid character has been detected. 
*   [EINVAL]
*   There are insufficient arguments. 
*   In addition, wprintf() and fwprintf() may fail if: 
*   
*   [ENOMEM]
*   Insufficient storage space is available. 
*	@param  buffer: 
*   @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 166) if function does not exist
*/
extern int Telium_Swprintf( TM_wchar_t *buffer, ...);

/*! @} **/

#endif
#ifdef __cplusplus
}
#endif

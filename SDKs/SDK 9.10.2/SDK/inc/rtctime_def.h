#ifdef __cplusplus
extern "C" {
#endif

#ifndef __RTCTIMER_DEF_H_INCLUDED__
#define __RTCTIMER_DEF_H_INCLUDED__

/*! @addtogroup KSFAM_CAL
	* @{
 */ 

/*
======================================================================
			Data Structures Definition
======================================================================
*/

#ifndef OEM_RTC_H

/*! @brief This type define the date, in the french or the english format. */
typedef struct {
#ifdef _DATE_EN_FRANCAIS_
   unsigned char jour    [2];						/*!< day.    */
   unsigned char mois    [2];						/*!< month.  */
   unsigned char annee   [2];						/*!< year.   */
   unsigned char heure   [2];						/*!< hour.   */
   unsigned char minute  [2];						/*!< minute. */
   unsigned char seconde [2];						/*!< second. */
#else
   unsigned char day    [2];						/*!< day.    */
   unsigned char month  [2];						/*!< month.  */
   unsigned char year   [2];						/*!< year.   */
   unsigned char hour   [2];						/*!< hour.   */
   unsigned char minute [2];						/*!< minute. */
   unsigned char second [2];						/*!< second. */
#endif
} DATE;

/*! @brief This type define the date, only in the english format. */
typedef struct {
   unsigned char day;				/*!< day.    */
   unsigned char month;			/*!< month.  */
   unsigned char year;			/*!< year.   */
   unsigned char hour;			/*!< hour.   */
   unsigned char minute;		/*!< minute. */
   unsigned char second;		/*!< second. */
} DATE_BIN ;
#endif

/*! @brief Define the date in the english format and the day of the week.
 *
 * The year is stored on one byte (offset compared with 1900). \n
 *
 * For the day of week, Sunday = 0. */
typedef struct {
    DATE_BIN      d;									/*!< binary date. */
    unsigned char wday;								/*!< day of the week (sunday = 0). */
    unsigned int  century;						/*!< century. */
}S_TM_LOCAL;

/*
======================================================================
					List of Defines
======================================================================
*/

#define Wrong_Date (unsigned char)1		/*!< return value if date syntaxe is incorrect */
#define DATE1_SUP 			1		/*!< Date 1 > date 2  */
#define DATES_EGALES 		0		/*!< Date 1 == date 2  */
#define DATE1_INF 			2		/*!< Date 1 < date 2  */


/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief This function is used to read the date in the terminal's Booster.
 * @param pt_date : pointer to structure DATE. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
int ReadDateBooster (DATE *pt_date );



/*! @brief This function is used to read the date in the terminal's Pinpad.
 * @param pt_date : pointer to structure DATE. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
int read_dateUsb(DATE *pt_date);

/*! @}  */ 


#endif   // __RTCTIMER_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif

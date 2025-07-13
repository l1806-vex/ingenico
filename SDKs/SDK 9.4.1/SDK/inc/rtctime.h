/*! @addtogroup KSFAM_CAL
	* @{
 */ 

#ifndef _RTCTIMER_H
#define _RTCTIMER_H

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

/*! @brief This function is used to check the date by verifying the coherency of the param eterized date.
 * @param date : pointer to structure DATE.
 * @return
 * - 0 if function has been correctly executed
 * - 1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ctrl_date:KSFAM_CAL:0x02
//  @GSIM_A:1:ONE_POINTER
// \endif
int ctrl_date (DATE * date);



/*! @brief This function is used to read the date in the terminal's calendar.
 * @param pt_date : pointer to structure DATE. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
// read_date:KSFAM_CAL:0x01
// 1:ONE_POINTER
// \endif
int  read_date (DATE *pt_date );



/*! @brief This function is used to read the date in the terminal's Booster.
 * @param pt_date : pointer to structure DATE. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
// ReadDateBooster:KSFAM_CAL:
// 1:ONE_POINTER
// \endif
int ReadDateBooster (DATE *pt_date );



/*! @brief This function is used to read the date in the terminal's Pinpad.
 * @param pt_date : pointer to structure DATE. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
// read_dateUsb:KSFAM_CAL:
// 1:ONE_POINTER
// \endif
int read_dateUsb(DATE *pt_date);



/*! @brief This function is used to program the terminal calendar.
 * @param pt_date : pointer to structure DATE.
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
// write_date:KSFAM_CAL:0x03
// 1: ONE_POINTER
// \endif
int  write_date ( DATE *pt_date);


#endif
/*! @}  */ 



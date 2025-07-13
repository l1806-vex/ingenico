/**
 * \file
 * This modules implements some generic functions.
 *
 * \author  Ingenico
 * \author  Copyright (c) 2012 Ingenico
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *       in this software. In particular, and without limitation, these intellectual property rights may\n
 *       include one or more patents.\n
 *       This software is distributed under licenses restricting its use, copying, distribution, and\n
 *       and decompilation. No part of this software may be reproduced in any form by any means\n
 *       without prior written authorization of Ingenico.
 */

#include "SDK30.h"
#include "APCLESS.h"

static int __APCLESS_Tools_DayOfYear (DATE *date);

/**
 * Convert an ASCII string into a BCD string
 * @param[in] ascii input number buffer
 * @param[in] asciiLen length of \a ascii
 * @param[out] bcd output buffer
 * @param[in] shift number of '0' digits to add at the beginning of \a bcd
 * Example
 *    -  ascii: "3"   shift:0  -> bcd=0x30
 *    -  ascii: "123" shift:1  -> bcd=0x01 0x23
 * @note \a bcd should be large enough to contain the shift digits and the converted digits.
 */
void APCLESS_Tools_ConvertAsciiToBcd(char* ascii, int asciiLen, unsigned char* bcd, int shift)
{
   int i, j;
   unsigned char digit;

   // put the '0' padding
   j = shift/2;
   if(j > 0)
   {
      memset(bcd, 0, j);
      bcd += j;
   }

   // convert
   *bcd = 0;
   i = shift & 1;
   while(asciiLen-- > 0)
   {
      digit = *(ascii++);
      if((i++) & 1)
      {
         *(bcd++) |= (digit & 0x0F);
      }
      else
      {
         *bcd = digit << 4;
      }
   }
}


/**
 * Search and get a specific information in a shared buffer.
 * @param[in] sharedData input buffer where to search
 * @param[in] tag tag number to look for
 * @param[out] info
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
int APCLESS_Tools_SharedBufferRetrieveInfo(T_SHARED_DATA_STRUCT* sharedData, unsigned long tag, unsigned char** info)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   if((sharedData == NULL) || (info == NULL))
      return FALSE;

   position = SHARED_EXCHANGE_POSITION_NULL;

   cr = GTL_SharedExchange_FindNext(sharedData, &position, tag, &readLength, &readValue);
   if (cr == STATUS_SHARED_EXCHANGE_OK)
   {
      // Set the result
      result = TRUE;
      *info = (unsigned char*) readValue;
   }
   else
   {
      result = FALSE;
      *info = NULL; // Default result : no information
   }

   return result;
}




//! \brief Calculate the day number in the year, based on the date.
//! \param[in] date Date.
//! \return The day number in the year.

static int __APCLESS_Tools_DayOfYear (DATE *date)
{
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned int i;
	int leap_year;

	const unsigned char day_per_month[2][13] = {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};

	Ascbin (&year, date->year, 2);
	Ascbin (&month, date->month, 2);
	Ascbin (&day, date->day, 2);

	// Determine if it is a leap year or not
	leap_year = (year % 4) == 0;

	// Calculate the days
	for (i=1; i<month; i++)
		day = day + day_per_month[leap_year][i];

	return (day);
}



//! \brief This function returns the number of days between two dates.
//! \param[in] date1 First date
//! \param[in] date2 Second date
//! \returns the number of days between date1 and date2.
//! \note No date check is done, so the provided dates shall be valid !

int APCLESS_Tools_NumberOfDaysBetweenTwoDates (DATE *date1, DATE *date2)
{
	int  day1, day2;
	unsigned long  year1, year2, year;
	DATE temp;
	int result;

	// Prepare temporary data set to 31/12, allowing to calculate the number of days or a given year
	Binasc(temp.day, 31, 2);
	Binasc(temp.month, 12, 2);

	// Calculate the delta in days
	day1 = __APCLESS_Tools_DayOfYear(date1);
	day2 = __APCLESS_Tools_DayOfYear(date2);
	result = day2 - day1;

	// Add the delat in years, if necessary
	Ascbin (&year1, date1->year, 2);
	Ascbin (&year2, date2->year, 2);

	// Management of year 2000
	if (year1 <= 50)
		year1 = year1 + 2000;
	else
		year1 = year1 + 1900;
	if (year2 <= 50)
		year2 = year2 + 2000;
	else
		year2 = year2 + 1900;

	// Determine the most recent year to determine the loop
	if (year2  <= year1 )
	{
		for (year=year2; year<year1; year++)
		{
			Binasc(temp.year, year % 100, 2);
			result = result - __APCLESS_Tools_DayOfYear(&temp); // Negative delta
		}
	}
	else
	{
		for (year=year1; year<year2; year++)
		{
			Binasc(temp.year, year % 100, 2);
			result = result + __APCLESS_Tools_DayOfYear(&temp); // Positive delta
		}
	}

	return (result);
}



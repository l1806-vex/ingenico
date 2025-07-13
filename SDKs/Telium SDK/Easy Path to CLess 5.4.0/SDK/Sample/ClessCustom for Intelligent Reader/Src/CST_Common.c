/**
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __CST_Common_DayOfYear (DATE *date);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Calculate the day number in the year, based on the date.
//! \param[in] date Date.
//! \return The day number in the year.

static int __CST_Common_DayOfYear (DATE *date)
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



//! \brief This function returns the number of days bewteen two dates.
//! \param[in] date1 First date
//! \param[in] date2 Second date
//! \returns the number of days between date1 and date2.
//! \note No date check is done, so the provided dates shall be valid !

int CST_Common_NumberOfDaysBetweenTwoDates (DATE *date1, DATE *date2)
{
	int  day1, day2;
	unsigned long  year1, year2, year;
	DATE temp;
	int result;

	// Prepare temporary data set to 31/12, allowing to calculate the number of days or a given year
	Binasc(temp.day, 31, 2);
	Binasc(temp.month, 12, 2);

	// Calculate the delta in days
	day1 = __CST_Common_DayOfYear(date1);
	day2 = __CST_Common_DayOfYear(date2);
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
			result = result - __CST_Common_DayOfYear(&temp); // Negative delta
		}
	}
	else
	{
		for (year=year1; year<year2; year++)
		{
			Binasc(temp.year, year % 100, 2);
			result = result + __CST_Common_DayOfYear(&temp); // Positive delta
		}
	}

	return (result);
}




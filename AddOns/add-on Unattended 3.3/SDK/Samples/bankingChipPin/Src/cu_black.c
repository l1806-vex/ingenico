/**
* \file cu_black.c
* \brief This module contains the functions that manages the black list.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "cu_term.h"
#include "cu_black.h"

//! \addtogroup Group_cu_black
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

static T_CUBLACKL_data BlackList [CUBLACKL_DEF_FILE_SIZE];
static T_CUBLACKL_management_data BLMngData;

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
T_Bool CUBLACKL_CreateFile(unsigned long black_list_size)

{
	T_Bool  ret;

	if ( BLMngData.black_list_max_size == 0)
	{
		// table does not exist

		// Initialisation of management data
		BLMngData.black_list_max_size = black_list_size;
		BLMngData.nb_record = 0;
		// Black-list not active, and expired
		BLMngData.activation_date.date [0] = 39;
		BLMngData.activation_date.date [1] = 12;
		BLMngData.activation_date.date [2] = 31;
		BLMngData.expiration_date.date [0] = 00;
		BLMngData.expiration_date.date [1] = 01;
		BLMngData.expiration_date.date [2] = 01;

		ret = B_TRUE;
	}
	else
	{
		// The file already exist
		ret = B_FALSE;
	}

	return (ret);
}


//===========================================================================
void CUBLACKL_DeleteBlackList(void)
{
	BLMngData.black_list_max_size = 0;
	BLMngData.nb_record = 0;
}

//===========================================================================
T_Bool CUBLACKL_IsInBlackList  ( unsigned char PAN[10], unsigned short lg,
								T_Bool is_presentPAN_seq_number,unsigned char PAN_seq_number)

{
	T_Bool  ret;
	T_Bool  found;
	T_Bool  ok;
	unsigned long current_rec;
	// VL suppr unsigned long i,j;
	T_CUBLACKL_data black_list_record;

	ret = B_FALSE;

	if (BLMngData.nb_record > 0)
	{
		found = B_FALSE;
		current_rec = 0;

		// Loop on the record list
		while ((!found) && (current_rec < BLMngData.nb_record ))
		{
			// Read record
			memcpy (&black_list_record, &(BlackList [current_rec]), sizeof(T_CUBLACKL_data));

			// Compare the PAN
			// VL suppr code optimization  
			/* i = 2;
			j = 0;
			ok = B_TRUE;
			while ((i < (unsigned long)(lg+2)) && (ok))
			{
				ok = (T_Bool)(black_list_record.PAN [i] == PAN [j]);

				i++;
				j++;
			} 
			*/
			// VL suppr code optimization end

			// VL begin code optimization
			if(memcmp(&black_list_record.PAN[2], PAN, lg) == 0)
			{
				ok = B_TRUE;
			}
			else
			{
				ok = B_FALSE;
			}
			// VL end code optimization

			if (ok)
			{
				if (is_presentPAN_seq_number==B_TRUE)
				{
					if (black_list_record.PAN[0]  == 01)  // flag says PAN seq number is present
						ok = (T_Bool)(black_list_record.PAN[1]  == PAN_seq_number );
				}
			}

			found = ok;

			current_rec++;
		}   // End of Loop on the record list

		ret = found;

	}

	return (ret);
}

//===========================================================================
T_Bool CUBLACKL_ReplaceBlackList (unsigned char *BlackListFile,
								  unsigned long BlackListSize,
								  T_CUBLACKL_date ExpirationDate)
{
	T_Bool  ret;
	T_CUBLACKL_data black_list_record;
	unsigned long i;

	ret = B_TRUE;


	if (BlackListSize <= BLMngData.black_list_max_size)
	{
		// Loop on File records
		for (i = 0; i < BlackListSize; i++)
		{
			// Copy PAN
			// memcpy (black_list_record.PAN, BlackListFile, 10);
			memcpy (black_list_record.PAN, BlackListFile +(i*sizeof(T_CUBLACKL_data)), 10);

			// Write record
			memcpy (&(BlackList [i]), &black_list_record, sizeof(T_CUBLACKL_data));
		}

		// Update Management Data
		BLMngData.nb_record = BlackListSize;
		BLMngData.expiration_date.date [0] = ExpirationDate.date [0];
		BLMngData.expiration_date.date [1] = ExpirationDate.date [1];
		BLMngData.expiration_date.date [2] = ExpirationDate.date [2];

	}
	else
	{
		ret = B_FALSE;
	}


	return (ret);
}

//===========================================================================
unsigned short CUBLACKL_IsValid (void)
{
	DATE_EXT CurrentDate;
	unsigned short Activated, Expired, isValid;

	// Read Current Date
	getdate (&CurrentDate);

	// Check if current date is greater than the activation date
	Activated = ( (BLMngData.activation_date.date [0] > CurrentDate.year) ||
				  ( (BLMngData.activation_date.date [0] == CurrentDate.year) &&
				    (BLMngData.activation_date.date [1] > CurrentDate.month) ) ||
				  ( (BLMngData.activation_date.date [0] == CurrentDate.year) &&
					(BLMngData.activation_date.date [1] == CurrentDate.month) &&
					(BLMngData.activation_date.date [2] > CurrentDate.day) ) );

	// Check if current date is greater than the expiration date
	Expired = ( (BLMngData.expiration_date.date [0] > CurrentDate.year) ||
				( (BLMngData.expiration_date.date [0] == CurrentDate.year) &&
				  (BLMngData.expiration_date.date [1] > CurrentDate.month) ) ||
				( (BLMngData.expiration_date.date [0] == CurrentDate.year) &&
				  (BLMngData.expiration_date.date [1] == CurrentDate.month) &&
				  (BLMngData.expiration_date.date [2] > CurrentDate.day) ) );

	isValid = ((Activated && !Expired));

	return (isValid);
}

//! @}



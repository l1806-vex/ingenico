/**
* \file convert.c
* \brief This module contains utility functions.
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

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
unsigned short CharToShort(unsigned char *data)
{
	return((data[0] << 8) + data[1]);
}

//===========================================================================
unsigned long CharToLong(unsigned char *data)
{
	return((data[0] << 24) + (data[1] <<16) +  (data[2] <<8) + data[3]);
}

//===========================================================================
void ShortToChar(unsigned short value,unsigned char *data)
{
	data[0] = (unsigned char)((value & 0xFF00) >> 8);
	data[1] = (unsigned char)(value & 0x00FF);
}

//===========================================================================
void LongToChar(unsigned long value,unsigned char *data)
{
	data[0] = (unsigned char)((value & 0xFF000000) >> 24);
	data[1] = (unsigned char)((value & 0x00FF0000) >> 16);
	data[2] = (unsigned char)((value & 0x0000FF00) >> 8);
	data[3] = (unsigned char)((value & 0x000000FF));
}

//===========================================================================
int HexToAscii (char * ac_x_hexbuf, int i_x_hexbuflg, unsigned char * ac_x_asciibuf)
{
	int i_l_Index;
	unsigned char value;

	for (i_l_Index = 0; i_l_Index<i_x_hexbuflg; i_l_Index++)
	{
		value = ac_x_hexbuf[i_l_Index] >> 4;
		value &= 0x0f;
		if (value <= 9)
			ac_x_asciibuf[2*i_l_Index] = value + 0x30;
		else
			ac_x_asciibuf[2*i_l_Index] = value + 0x37;

		value = ac_x_hexbuf[i_l_Index] & 0x0f;
		if (value <= 9)
			ac_x_asciibuf[2*i_l_Index+1] = value + 0x30;
		else
			ac_x_asciibuf[2*i_l_Index+1] = value + 0x37;
	}
	/* String end */
	ac_x_asciibuf[2*i_l_Index] = 0;
	return 1;
}

//===========================================================================
int Hexascii( unsigned char *dest , unsigned char *src , int size)
{
	int i ;

	if (size > 0)
	{
		for (i=0 ; i<(size/2) ; i++)
		{
			*(dest+(2*i)) = ((*(src+i) & 0xF0) >> 4) + 0x30 ;
			if ( *(dest+(2*i)) > 0x39 )
				*(dest+(2*i)) += 0x07 ;
			*(dest+(2*i)+1) =  (*(src+i) & 0x0F) + 0x30 ;
			if ( *(dest+(2*i)+1) > 0x39 )
				*(dest+(2*i)+1) += 0x07 ;
		}
		if (size%2 != 0)
		{ /* traitement size impaire */
			*(dest+(2*i)) = ((*(src+i) & 0xF0) >> 4) + 0x30 ;
			if ( *(dest+(2*i)) > 0x39 )
				*(dest+(2*i)) += 0x07 ;
		}
		return(0) ;
	}
	else
		return(1) ;
}



/**
* \file cu_pinen.c
* \brief This module contains the functions that perform the encipherment of the PIN code,
* for online presentation.
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
#include "cu_pinen.h"
#include "sec_interface.h"
#include "cu_term.h"
#include "tlvVar_def.h"
#include "schVar_def.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

T_SEC_DATAKEY_ID stKey;

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
int PIN_InjectKey ()
{
	unsigned char PIN_ciphering_key[] = {0x0D,0xA0,0x61,0x56,0xD0,0x95,0x94,0xC3}; // Change it with your own value
	T_SEC_DATAKEY_ID stCipherKey;
	int iret,iret1;
	char str[50];

	iret = KO;
/*&BEGIN FT/09/5296/MA    SEC_ISO9563 has to be called only if Injection successfull */
	iret1= SEC_isSecretArea (C_SEC_PINCODE, (SEG_ID) 0x00012030);
/*&END FT/09/5296/MA    SEC_ISO9563 has to be called only if Injection successfull */
	if (iret1 == OK )
	{
		stCipherKey.iSecretArea = 0x00012030;
		stCipherKey.cAlgoType = TLV_TYPE_KDES;
		stCipherKey.usNumber = 254*4;
		stCipherKey.uiBankId = 0x800000FE;

		stKey.iSecretArea = 0x00012030;
		stKey.cAlgoType = TLV_TYPE_KDES;
		stKey.usNumber = 16*4;
		stKey.uiBankId = BK_SAGEM;

		
		iret1 = SEC_FreeSecret(C_SEC_PINCODE, &stKey);
	
		iret = SEC_LoadKey (C_SEC_PINCODE,&stCipherKey, &stKey,PIN_ciphering_key, CIPHERING_PIN);

		sprintf(str, "SEC_LoadKey %d\n",iret);
		upload_diagnostic_txt((unsigned char*)str);
	}
	else
	{
		sprintf(str, "secret area absent\n");
		upload_diagnostic_txt((unsigned char*)str);
	}
	return iret;
}


//===========================================================================
int PIN_OnlineEncipher (unsigned char pucPAN [],	unsigned char pucEncipheredPin [],int *iLenEnc)
{
	int iRes;
	int iAllIsOk;
	char debug[50];
	unsigned char       iso9564Result       [50];
	unsigned int uiLengthOut;


	memset ( iso9564Result , 0 , 50);	

	iRes = SEC_Iso9564 (C_SEC_PINCODE, &stKey, ISO9564_F0_DES, &(pucPAN[0]), &iso9564Result[0], &uiLengthOut);

	sprintf(debug, "SEC_Iso9564 %d\n",iRes);
	upload_diagnostic_txt((unsigned char*)debug);

	sprintf(debug, " %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",iso9564Result[0],iso9564Result[1],iso9564Result[2],
		iso9564Result[3],iso9564Result[4],iso9564Result[5],iso9564Result[6],iso9564Result[7],iso9564Result[8],iso9564Result[9]);
	upload_diagnostic_txt((unsigned char*)debug);

	iAllIsOk = (iRes == OK);
	if (iAllIsOk)
	{
		memcpy (pucEncipheredPin, iso9564Result, uiLengthOut);
		*iLenEnc = uiLengthOut;
	}

	return (iAllIsOk);
}

#ifdef _USE_DEMO_
//===========================================================================
int PIN_OnlineEncipherDemo (unsigned char pucPAN [],	unsigned char pucEncipheredPin [],int *iLenEnc)
{
	*iLenEnc = 8;
	return 1;
}

//===========================================================================
void PIN_InjectKeyDemo (void)
{

}
#endif



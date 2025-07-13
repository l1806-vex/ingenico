/***
 * Copyright (c) 2010 Ingenico, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Ingenico has intellectual property rights relating
 * to the technology embodied in this software.  In particular,
 * and without limitation, these intellectual property rights
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting
 * its use, copying, distribution, and decompilation.
 * No part of this software may be reproduced in any form
 * by any means without prior written authorization of
 * Ingenico.
 *
 * @Title:        sample_ExtNumEntry.c
 * @Description: 
 * @Company:
 * @Reference:
 *****************************************************************************************************************************
 *
 * @Comment: Do not forget to extract MESS0101.zip and to copy the result in "swap" directory of the terminal
 *
 *****************************************************************************************************************************
 *
 * @author        S. R (Ingenico partner)
 * @version       1.0
 * @date          2012/06/12
 */

#include "SDK30.H"
#include "SEC_interface.h"
#include "schVar_def.h"  //!!

/******************************************************************************/
/* Example to read the signed Parameter Messages file : MESS0101 Application
Type 0xADB6 */
/******************************************************************************/
#define C_MessageFileType 0xADB6
/* Index according to the format of the signed parameter file */
#define C_IND_OFFSET_T1 4
#define C_IND_SIZE_T1 8
#define C_IND_OFFSET_T2 12
#define C_IND_SIZE_T2 16

char cFileNamePrefix[]={"MESS0201"};

unsigned char G_ptResult[8];
int G_iLenResult;

int Sample_SECExtNumEntry (void)
{
int PinpadIsDeclared,
	PinpadValue;

int iret, NbReadElements;

object_descriptor_t InfosDescriptor;

void* fdin;
char 	*MessagesBuffer,
		*ptBuff;

int ibPinpadT1,
	iInd_Size,
	iInd_Offset,
	iBuffSize,
	iOffset;

T_SEC_EXTNUMENTRYCONF stExtNumEntryConfig;
unsigned int  imin, imax, iIndice, ibToContinue, EndNumEntry, uiEventToWait;
unsigned char tab_mess[C_NUM_MESS_LENGTH], mess_num[] = "?", Key;

	MessagesBuffer=NULL;
	iret = OK;
	ibPinpadT1 = TRUE;

//
//********************* Find pinpad type
	PinpadIsDeclared = PSQ_Is_pinpad ();
	if (PinpadIsDeclared != 0)
	{
		PinpadValue = PSQ_Pinpad_Value ();
		switch (PinpadValue)
		{
			case PP30_PPAD :
			case PPC30_PPAD :
			case PPR30_PPAD :
				iret = KO; //Scheme doesn't work on this pinpads
			break;

			case P30_PPAD:
			case PP30S_PPAD:
				ibPinpadT1 = TRUE;
			break;

			default:
				ibPinpadT1 = FALSE;
			break;
		}
	}
	else
	iret = KO;;
//
//********************* Find and open signed message file
	if (iret == OK)
	{
		//get size
		ObjectGetDescriptor(OBJECT_TYPE_PARAM, C_MessageFileType,&InfosDescriptor);

		fdin = ObjectOpen( &InfosDescriptor );
		if (fdin != NULL)
		{
			MessagesBuffer = umalloc(InfosDescriptor.code_size);
			if (MessagesBuffer != NULL)
			{
				//read elements
				NbReadElements = ObjectRead( MessagesBuffer,1, InfosDescriptor.code_size, fdin );
				if (NbReadElements != InfosDescriptor.code_size)
					iret = KO;
			}
			else
				iret = KO;
			ObjectClose ( fdin ) ;
		}
//
//***** Now the signed messages buffer T1 and T2 are loaded in terminal memory at MessagesBuffer address
//
		if (ibPinpadT1 == TRUE)
		{
			iInd_Offset = C_IND_OFFSET_T1;
			iInd_Size = C_IND_SIZE_T1;
		}
		else
		{
			iInd_Offset = C_IND_OFFSET_T2;
			iInd_Size = C_IND_SIZE_T2;
		}

		memcpy (&iBuffSize, &MessagesBuffer[iInd_Size], sizeof(int));
		memcpy (&iOffset, &MessagesBuffer[iInd_Offset], sizeof(int));
		ptBuff = &MessagesBuffer[iOffset];

		if (iret == OK)
		{
			imin = 0x04; //Minimum number of digit to enter
			imax = 0x0D; //Maximum number of digit to enter

			stExtNumEntryConfig.iInterCharTimeOut = 5;
			stExtNumEntryConfig.iFirstCharTimeOut = 20;
			stExtNumEntryConfig.iMaskInput        = C_MSK_NUM | C_MSK_VAL | C_MSK_CORR | C_MSK_ANN | C_MSK_POINT | C_MSK_F | C_MSK_STAR
													| C_MSK_UP | C_MSK_DOWN |  C_MSK_SK1 | C_MSK_SK2 | C_MSK_SK3 | C_MSK_SK4;
			stExtNumEntryConfig.iHeadMessNo       = 0x01;
			stExtNumEntryConfig.iLineHeadMess     = 0x00;
			stExtNumEntryConfig.iColHeadMess      = 0x00;
			stExtNumEntryConfig.ucMode            = C_NUMGEN_MODE_TEXT;
			stExtNumEntryConfig.iFootMessNo       = 0xFF;
			stExtNumEntryConfig.iLineFootMess     = 0x03;
			stExtNumEntryConfig.iColFootMess      = 0x12;

			stExtNumEntryConfig.iLineVarMess      = 2;
			stExtNumEntryConfig.iColVarMess       = 4;

			stExtNumEntryConfig.iMovableMessNo  = 0xFF;

			stExtNumEntryConfig.iCurrencyCode     = 0xFFFF;
			stExtNumEntryConfig.iLineCurrencyCode = 0x02;
			stExtNumEntryConfig.iColCurrencyCode  = 0x00;

			stExtNumEntryConfig.ucFontWidth       = 0x06;
			stExtNumEntryConfig.ucFontHeight      = 0x10;

			stExtNumEntryConfig.pt_szMessFileName  = cFileNamePrefix;

			stExtNumEntryConfig.iBufferSize = iBuffSize;
			stExtNumEntryConfig.cBuffer = ptBuff;

			//
			//******************************* call scheme
			iret = SEC_ExtNumEntryInit (&stExtNumEntryConfig, C_SEC_PINCODE);

			iIndice = 0;
			ibToContinue = C_SEC_EXTNUMTRY_CONT;
			EndNumEntry = FALSE;
			if (iret == OK)
			{
				memset(tab_mess, 0, sizeof(tab_mess));

				tab_mess[0] = stExtNumEntryConfig.iLineVarMess; //Movable message line position
				tab_mess[1] = stExtNumEntryConfig.iColVarMess; //Movable message column position

				memcpy(&tab_mess[2], mess_num, sizeof(mess_num)); // Initial variable message

				while(EndNumEntry == FALSE)
				{
					uiEventToWait = KEYBOARD; /* To restore again for next call */
					iret = SEC_ExtNumEntry (&uiEventToWait, &ibToContinue, tab_mess, 0, NULL, &Key);
					if ( (iret == OK) && (ibToContinue != C_SEC_EXTNUMTRY_HALT_END) )
					{
						switch (Key)
						{
							case T_VAL:
								if (iIndice >= imin)
								{
								ibToContinue = C_SEC_EXTNUMTRY_HALT_END;  // To stop the scheme
								}
							break;

							case T_ANN:
								iIndice = 0;					       // Raz Nb
								ibToContinue = C_SEC_EXTNUMTRY_HALT;      // To halt input
							break;

							case T_CORR:
								if (iIndice != 0)				       // At least 1 character ?
								{
									iIndice--;
									tab_mess[2+iIndice] = 0x20;
									tab_mess[1] =iIndice + stExtNumEntryConfig.iColVarMess;
								}
							break;

							case T_POINT :
								if (iIndice < imax)
								{
									tab_mess[1] =iIndice + 1 + stExtNumEntryConfig.iColVarMess;
									tab_mess[2+iIndice++] = Key;
								}
							break;

							case T_APAP :
								if (iIndice < imax)
								{
									tab_mess[1] =iIndice + 1 + stExtNumEntryConfig.iColVarMess;
									tab_mess[2+iIndice++] = '*';
								}
							break;

							case SYNC_ERROR:
								printf("\x1B SYNC_ERROR\n");
								if (ibToContinue != C_SEC_EXTNUMTRY_HALT_END)
								{
									printf("Press key To end");
									getchar();
									ibToContinue = C_SEC_EXTNUMTRY_HALT_END;
								}
							break;

							default:
								if ((Key >= T_NUM0) && (Key <= T_NUM9))
								{
									if (iIndice < imax)
									{
										tab_mess[1] =iIndice + 1 + stExtNumEntryConfig.iColVarMess;
										tab_mess[2+iIndice++] = Key;
									}
								}
								else
								{
									printf("\x1B Key %x\n", (int) Key);
									if (iIndice < imax)
									{
									tab_mess[1] =iIndice + 1 + stExtNumEntryConfig.iColVarMess;
									tab_mess[2+iIndice++] = '$';
									}
								}
							break;
						}
					}
					else
					{
						if ( (iret == OK) && (Key == 0) )
						{
							printf("\x1B TimeOut Key\n");
							printf("Press a key");
							getchar();
						}
						if (ibToContinue != C_SEC_EXTNUMTRY_HALT_END)
						{
							if ((iret == ERR_TIMEOUT) && (uiEventToWait == KEYBOARD))
							{
							/* Received KEYBOARD event */
							getchar();
							}
							printf("\x1B iret %d\n", iret);
							printf("Press key To end");
							getchar();
							ibToContinue = C_SEC_EXTNUMTRY_HALT_END;
						}
						else
							EndNumEntry = TRUE;
					}
				}
			}
		}

		if (MessagesBuffer != NULL)
			ufree(MessagesBuffer);
	}

return 0;
}

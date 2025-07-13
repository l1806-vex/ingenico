/***
 * Copyright (c) 2003 SAGEM Monetel , rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * SAGEM Monetel has intellectual property rights relating
 * to the technology embodied in this software.  In particular,
 * and without limitation, these intellectual property rights
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting
 * its use, copying, distribution, and decompilation.
 * No part of this software may be reproduced in any form
 * by any means without prior written authorization of
 * SAGEM Monetel.
 *
 * Title:        P40_interface.h
 * Description:  Interface header file for DLL P40
 * @Reference:    
 * @Comment:      
 *
 * @author       Y. MORENO
 * @version      1.0
 * @Comment:      
 * @date:        2007/04/17 
 *
*/

#ifndef __P40_INTERF_H__
#define __P40_INTERF_H__

#include "crypto_def.h" // Not included with SDK30.h (R_RSA_PUBLIC_KEY structure)

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ERR_P40_OK						(0)		//!< No P40 error.
#define ERR_P40_KO						(1)		//!< P40 unknown error.
#define ERR_P40_DISCONNECT				(-1)	//!< The P40 device is not connected.
#define ERR_P40_COMPONENT_NOT_FOUND		(-2)	//!< The P40 software component is not found.
#define ERR_P40_NOT_CONFIGURED			(-3)	//!< The P40 is not configured in the manager.

#define P40_DIAGNOSTICS_SIZE				(TAILLE_DIAGNOSTIC_SYSTEME)	//!< Size, in bytes, of the text diagnostics of the P40 device.

#define P40_COMPONENT_LABEL_LENGTH				(20)	//!< Length of a component label of a P40 device.
#define P40_COMPONENT_IDENTIFICATION_LENGTH		(10)	//!< Length of a component number of a P40 device

#define P40_COMPONENT_TYPE_OS_RAM_LOADER			(0x00)	//!< The P40 component is the BOOT RAM loader.
#define P40_COMPONENT_TYPE_OS_FLASH_LOADER			(0x01)	//!< The P40 component is the BOOT FLASH loader.
#define P40_COMPONENT_TYPE_OS_SYSTEM				(0x02)	//!< The P40 component is the system.
#define P40_COMPONENT_TYPE_OS_SECURITY_FILE			(0x03)	//!< The P40 component is the security file.
#define P40_COMPONENT_TYPE_OS_HTERM_FILE			(0x04)	//!< The P40 component is the hardware description file.
#define P40_COMPONENT_TYPE_OS_STERM_FILE			(0x05)	//!< The P40 component is the hardware description file.
#define P40_COMPONENT_TYPE_OS_PPAD_RSA_CERTIFICAT	(0x08)	//!< The P40 component is the ingetrust certificate file.
#define P40_COMPONENT_TYPE_APPLI					(0x81)	//!< The P40 component is the application.
#define P40_COMPONENT_TYPE_APPLI_FLASH_DATA			(0x82)	//!< The P40 component is the data file of the application.

#define P40_PRODUCT_ID_LENGTH					(8)				//!< Length of a P40 product identifier.
#define P40_SERIAL_NUMBER_LENGTH				(8)				//!< Length of a P40 serial number.
#define P40_PRODUCT_CODE_LENGTH					(3)				//!< Length of a P40 product code.
#define P40_CONSTRUCTOR_CODE_LENGTH				(8)				//!< Length of a P40 constructor code.
#define P40_MANUFACTURING_DATE_LENGTH			(8)				//!< Length of a P40 manufacturing date.
#define P40_BOOSTER_VERSION_LENGTH				(4)				//!< Length of a P40 booster version.

#define P40_HARDWARE_OPTION_BUZZER				(0x00000001)	//!< The P40 has a buzzer.
#define P40_HARDWARE_OPTION_USB_SLAVE			(0x00000002)	//!< The P40 has a slave USB port.
#define P40_HARDWARE_OPTION_COM0				(0x00000010)	//!< The P40 has a COM0 port.
#define P40_HARDWARE_OPTION_COM1				(0x00000020)	//!< The P40 has a COM1 port.

#define P40_HARDWARE_OPTION_CAM_1				(0x00000100)	//!< The P40 has a SAM1 connector.
#define P40_HARDWARE_OPTION_CAM_2				(0x00000200)	//!< The P40 has a SAM2 connector.

#define P40_HARDWARE_OPTION_SAM_1				(0x00000400)	//!< The P40 has a SAM1 connector.
#define P40_HARDWARE_OPTION_SAM_2				(0x00000800)	//!< The P40 has a SAM2 connector.
#define P40_HARDWARE_OPTION_SAM_3				(0x00001000)	//!< The P40 has a SAM3 connector.
#define P40_HARDWARE_OPTION_SAM_4				(0x00002000)	//!< The P40 has a SAM4 connector.

#define P40_HARDWARE_OPTION_ISO_1				(0x00004000)	//!< The P40 has a SAM1 connector.
#define P40_HARDWARE_OPTION_ISO_2				(0x00008000)	//!< The P40 has a SAM2 connector.
#define P40_HARDWARE_OPTION_ISO_3				(0x00010000)	//!< The P40 has a SAM3 connector.

#define P40_HARDWARE_OPTION_DISPLAY_NONE		(0x00020000)	//!< The P40 has no display.
#define P40_HARDWARE_OPTION_DISPLAY_128_64		(0x00040000)	//!< The P40 has a 128x64 graphic display.

#define P40_HARDWARE_OPTION_INTER_UC_ON_COM0	(0x80000000)	//!< The inter-uc communication is mapped on COM0 (valid only when both COM0 and USB are available).
#define P40_HARDWARE_OPTION_COM0_COM1_SEPARATED	(0x40000000)	//!< The COM0 an COM1 are separated.

/////////////////////////////////////////////////////////////////

#define P40_GRAPHIC_MODE_DISABLED				0
#define P40_GRAPHIC_MODE_ENABLED				1

/////////////////////////////////////////////////////////////////

#define P40_UNKNOWN_STATE			0xFF
#define P40_UNAUTHORIZED_STATE		0x02
#define P40_OUT_OF_SERVICE_STATE	0x01	
#define P40_READY_STATE				0x00

//// Types //////////////////////////////////////////////////////

typedef struct
{
	char Label[P40_COMPONENT_LABEL_LENGTH + 1];						//!< Label of the software component.
	unsigned int Size;												//!< Size in bytes of the software component.
	unsigned short Crc;												//!< CRC of the software component.
	char Identification[P40_COMPONENT_IDENTIFICATION_LENGTH + 1];	//!< Identification (number + version) of the software component.
	unsigned char Type;												//!< Type of the software component. See \a P40_COMPONENT_TYPE_xxx.

	unsigned int Key;												//!< Key of the software component.
	unsigned int LoadingAddress;									//!< Loading address of the software component.
	unsigned int DataAddressStart;									//!< Start address of the data.
	unsigned int DataAddressEnd;									//!< End address of the data.
	unsigned int EntryPointAddress;									//!< Address of the entry point.
	unsigned int RufAddress1;										//!< Reserved for future use.
	unsigned int RufAddress2;										//!< Reserved for future use.
	unsigned int RufAddress3;										//!< Reserved for future use.
} T_P40_COMPONENT_INFO;

//! \brief Information on the hardware of a P40 device.
typedef struct
{
	char szProductIdentification[P40_PRODUCT_ID_LENGTH + 1];		//!< Product identification of the P40 device.
	char szSerialNumber[P40_SERIAL_NUMBER_LENGTH + 1];				//!< Serial number of the P40 device.
	char szProductCode[P40_PRODUCT_CODE_LENGTH + 1];				//!< Pruct code of the P40 device.
	char szConstructorCode[P40_CONSTRUCTOR_CODE_LENGTH + 1];		//!< Constructor code of the P40 device.
	char szManufacturingDate[P40_MANUFACTURING_DATE_LENGTH + 1];	//!< Manufacturing date of the P40 device.
	char szBoosterVersion[P40_BOOSTER_VERSION_LENGTH + 1];			//!< Booster version of the P40 device.
	unsigned int Options;											//!< Hardware options of the P40 device. See P40_HARDWARE_OPTION_xxx.
} T_P40_HARDWARE_CAPABILITIES;


//! \brief Version of the API lib interface with P40 DLL.
//! \return The version.
//int P40lib_version(void);

//! \brief Load the Peripheral P40 DLL.
//! \return The return value of the ObjectLoad function. 0 is successfull.
int P40lib_open(void);

//! \brief Unload the Peripheral P40 DLL.
void P40lib_close(void);


//! \brief Version of the Security services.
//! \return : Version as integer (BCD format 4 bytes : VVVVmmpp)
int P40_Version (void);

int	P40_SysInit( void ); 
int P40_DllInit( void );
int P40_Reset( void );
int P40_Display( char *message );
void P40_NumEntry( TAB_ENTRY_STRING *tabEntry );
void P40_FctEntry( TAB_ENTRY_FCT *tabEntry );
unsigned char P40_ReadEntry( BUFFER_SAISIE *buf_saisie_ppad );
void P40_StopEntry( void );
void P40_NewLine( void );
void P40_ClearLine( void );
void P40_FirstLine( void );
int P40_IsConnected( void );
void P40_NumEntryT( TAB_ENTRY_STRING_PPAD *tab_entry );

void P40_ProdLoad( void );
int P40_TransfertToBooster( void );

int P40_GetHardwareCapabilities(T_P40_HARDWARE_CAPABILITIES* pHardCapabilities);
void P40_PrintHardwareCapabilities(void);
void P40_PrintComponents(void);
void P40_PrintDiagnostics(void);

int P40_FastIsConnected (void);
int P40_SecurityLevel(unsigned char *NiveauSecurite);

int P40_EndSys(void);

int P40_GetComponentInfo(int nCommand, int nIndexOrType, T_P40_COMPONENT_INFO* pInfo, char* pDiagnostics);

int P40_SubmitPinCode( T_APDU *ptCmdApdu, T_APDU *ptRespApdu, int iFormat, int ilgPinCode, R_RSA_PUBLIC_KEY * ptKey );

int P40_Graphic_Mode( unsigned char i_uc_mode );

int P40_GetStatus( unsigned char *o_uc_status );

int P40_GenSysInit( unsigned char i_uc_ReaderBoosterPos, unsigned char i_uc_RetroEclairage );

int P40_DllVersion( void );

#endif /* __P40_INTERF_H__ */

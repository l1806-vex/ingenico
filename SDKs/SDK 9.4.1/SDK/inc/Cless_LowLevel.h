/**
 * \file
 * \brief Define the low level interface of the contactless DLL.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __CLESS_LOWLEVEL_H__INCLUDED__
#define __CLESS_LOWLEVEL_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

/*! \addtogroup TPassApiSams
\details The SAMs connectors of the TeliumPass+ or Vending Pass reader can be accessed using the following drivers:
<table><tr><th>SAM connector</th><th>Terminal driver name</th></tr>
<tr><td>SAM1</td><td>"SAM_C30_1"</td></tr>
<tr><td>SAM2</td><td>"SAM_C30_2"</td></tr>
<tr><td>SAM3</td><td>"SAM_C30_3"</td></tr>
<tr><td>SAM4</td><td>"SAM_C30_4"</td></tr>
</table>
*/

//! \addtogroup TPassApiErrors
//! @{

#define ERR_TPASS_OK						(0)		//!< No contactless error.
#define ERR_TPASS_KO						(1)		//!< Contactless unknown error.
#define ERR_TPASS_DISCONNECTED				(-1)	//!< The contactless reader is not connected.
#define ERR_TPASS_COMPONENT_NOT_FOUND		(-2)	//!< The contactless software component is not found.
#define ERR_TPASS_NOT_CONFIGURED			(-3)	//!< The contactless is not configured in the manager.

#define ERR_TPASS_DISCONNECT				ERR_TPASS_DISCONNECTED	//!< DEPRECATED: use \ref ERR_TPASS_DISCONNECTED instead.

//! @}

//! \addtogroup TPassApiGeneral
//! @{

#define TPASS_CLESS_TYPE_NONE						(0x0000)	//!< There is no contactless reader.
#define TPASS_CLESS_TYPE_TELIUM_PASS				(0x0001)	//!< The contactless reader is a TeliumPass+.
#define TPASS_CLESS_TYPE_VENDING_PASS				(0x0002)	//!< The contactless reader is a Vending Pass.
#define TPASS_CLESS_TYPE_P30C     					(0x0004)	//!< The contactless reader is a P30C.
#define TPASS_CLESS_TYPE_IPP2XX						(0x0008)	//!< The contactless reader is an iPP2xx.
#define TPASS_CLESS_TYPE_IPP3XX_EMUL_P30C			(0x0010)	//!< The contactless reader is an iPP3xx in P30C emulation mode.
#define TPASS_CLESS_TYPE_IST150_EMUL_TELIUM_PASS	(0x0020)	//!< The contactless reader is an iST150 in TeliumPass+ emulation mode.
#define TPASS_CLESS_TYPE_IUC150_EMUL_VENDING_PASS	(0x0040)	//!< The contactless reader is an iUC150 in Vending Pass emulation mode.
#define TPASS_CLESS_TYPE_EMBEDDED					(0x8001)	//!< The contactless reader is embedded into the terminal.
#define TPASS_CLESS_TYPE_UNKNOWN					(0xffff)	//!< The contactless reader is unknown.

// For compatibility
#define TPASS_CLESS_TYPE_CAD30VT			TPASS_CLESS_TYPE_VENDING_PASS	//!< DEPRECATED: use \ref TPASS_CLESS_TYPE_VENDING_PASS instead.
#define TPASS_CLESS_TYPE_P30     			TPASS_CLESS_TYPE_P30C			//!< DEPRECATED: use \ref TPASS_CLESS_TYPE_P30C instead.

//! @}

//! \addtogroup TPassApiBacklight
//! @{

#define TPASS_BACKLIGHT_OFF					(0)		//!< Backlight level to turn it off.
#define TPASS_BACKLIGHT_ON					(255)	//!< Backlight level to turn it on.

#define TPASS_BACKLIGHT_DEFAULT_FADE_RAMP	(512)	//!< Backlight default fade ramp (steps by second).

//! @}

//! \addtogroup TPassApiLeds
//! @{

#define TPASS_LED_1							(0x01)	//!< First contactless LED identifier.
#define TPASS_LED_2							(0x02)	//!< Second contactless LED identifier.
#define TPASS_LED_3							(0x04)	//!< Third contactless LED identifier.
#define TPASS_LED_4							(0x08)	//!< Fourth contactless LED identifier.
#define TPASS_LED_BLUE						(0x10)	//!< Fifth contactless LED identifier.
#define TPASS_LED_YELLOW					(0x20)	//!< Sixth contactless LED identifier.
#define TPASS_LED_RED						(0x40)	//!< Seventh contactless LED identifier.
#define TPASS_LED_GREEN						(0x80)	//!< Third contactless LED identifier.

#define LIGHTBLUE							0xFF0000FF //!< Color of the fifth LED
#define LIGHTYELLOW							0xFFFFFF00 //!< Color of the sifth LED
#define LIGHTRED							0xFFFF0000 //!< Color of the seventh LED
#define LIGHTGREEN							0xFF00FF00 //!< Color of the third LED

#define TPASS_LED_BLINK_TICKS				(2)		//!< Unit, in ticks, used to blink the contactless LEDs (= 20 ms).

//! @}

//! \addtogroup TPassTeliumPassVendingPass
//! @{

#define TPASS_DIAGNOSTICS_SIZE				(TAILLE_DIAGNOSTIC_SYSTEME)	//!< Size, in bytes, of the text diagnostics of the contactless reader.

//! @}

//! \addtogroup TPassComponents
//! @{

#define TPASS_COMPONENT_LABEL_LENGTH				(20)	//!< Length of a component label in a contactless reader.
#define TPASS_COMPONENT_IDENTIFICATION_LENGTH		(10)	//!< Length of a component number in a contactless reader.

#define TPASS_COMPONENT_TYPE_OS_RAM_LOADER			(0x00)	//!< The contactless component is the BOOT RAM loader.
#define TPASS_COMPONENT_TYPE_OS_FLASH_LOADER		(0x01)	//!< The contactless component is the BOOT FLASH loader.
#define TPASS_COMPONENT_TYPE_OS_SYSTEM				(0x02)	//!< The contactless component is the system.
#define TPASS_COMPONENT_TYPE_OS_SECURITY_FILE		(0x03)	//!< The contactless component is the security file.
#define TPASS_COMPONENT_TYPE_OS_HTERM_FILE			(0x04)	//!< The contactless component is the hardware description file.
#define TPASS_COMPONENT_TYPE_OS_STERM_FILE			(0x05)	//!< The contactless component is the hardware description file.
#define TPASS_COMPONENT_TYPE_APPLI					(0x81)	//!< The contactless component is the application.
#define TPASS_COMPONENT_TYPE_APPLI_FLASH_DATA		(0x82)	//!< The contactless component is the data file of the application.

//! @}

//! \addtogroup TPassCapabilities
//! @{

#define TPASS_PRODUCT_ID_LENGTH						(8)				//!< Length of a contactless reader product identifier.
#define TPASS_SERIAL_NUMBER_LENGTH					(8)				//!< Length of a contactless reader serial number.
#define TPASS_PRODUCT_CODE_LENGTH					(3)				//!< Length of a contactless reader product code.
#define TPASS_CONSTRUCTOR_CODE_LENGTH				(8)				//!< Length of a contactless reader constructor code.
#define TPASS_MANUFACTURING_DATE_LENGTH				(8)				//!< Length of a contactless reader manufacturing date.
#define TPASS_BOOSTER_VERSION_LENGTH				(4)				//!< Length of a contactless reader booster version.

#define TPASS_HARDWARE_OPTION_BUZZER				(0x00000001)	//!< The contactless reader has a buzzer.
#define TPASS_HARDWARE_OPTION_USB_SLAVE				(0x00000002)	//!< The contactless reader has a slave USB port.
#define TPASS_HARDWARE_OPTION_COM0					(0x00000010)	//!< The contactless reader has a COM0 port.
#define TPASS_HARDWARE_OPTION_COM1					(0x00000020)	//!< The contactless reader has a COM1 port.

#define TPASS_HARDWARE_OPTION_SAM_1					(0x00000100)	//!< The contactless reader has a SAM1 connector.
#define TPASS_HARDWARE_OPTION_SAM_2					(0x00000200)	//!< The contactless reader has a SAM2 connector.
#define TPASS_HARDWARE_OPTION_SAM_3					(0x00000400)	//!< The contactless reader has a SAM3 connector.
#define TPASS_HARDWARE_OPTION_SAM_4					(0x00000800)	//!< The contactless reader has a SAM4 connector.

#define TPASS_HARDWARE_OPTION_DISPLAY_NONE			(0x00001000)	//!< The contactless reader has no display.
#define TPASS_HARDWARE_OPTION_DISPLAY_128_64		(0x00002000)	//!< The contactless reader has a 128x64 graphic display.

#define TPASS_HARDWARE_OPTION_INTER_UC_ON_COM0		(0x80000000)	//!< The inter-uc communication is mapped on COM0 (valid only when both COM0 and USB are available).
#define TPASS_HARDWARE_OPTION_COM0_COM1_SEPARATED	(0x40000000)	//!< The COM0 an COM1 are separated.

//! @}

//! \addtogroup TPassContactLessMifareBlockOperations
//! @{

#define TPASS_MIFARE_KEY_LENGTH						(6)				//!< Length of a MIFARE key.

//! @}

//// Types //////////////////////////////////////////////////////

//! \addtogroup TPassComponents
//! @{

//! \brief Description of a contactless reader software component.
typedef struct
{
	char Label[TPASS_COMPONENT_LABEL_LENGTH + 1];					//!< Label of the software component.
	unsigned int Size;												//!< Size in bytes of the software component.
	unsigned short Crc;												//!< CRC of the software component.
	char Identification[TPASS_COMPONENT_IDENTIFICATION_LENGTH + 1];	//!< Identification (number + version) of the software component.
	unsigned char Type;												//!< Type of the software component. See \a TPASS_COMPONENT_TYPE_xxx.

	unsigned int Key;												//!< Key of the software component.
	unsigned int LoadingAddress;									//!< Loading address of the software component.
	unsigned int DataAddressStart;									//!< Start address of the data.
	unsigned int DataAddressEnd;									//!< End address of the data.
	unsigned int EntryPointAddress;									//!< Address of the entry point.
	unsigned int RufAddress1;										//!< Reserved for future use.
	unsigned int RufAddress2;										//!< Reserved for future use.
	unsigned int RufAddress3;										//!< Reserved for future use.
} T_TPASS_COMPONENT_INFO;

//! @}

//! \addtogroup TPassCapabilities
//! @{

//! \brief Information on the hardware of a contactless reader.
typedef struct
{
	char szProductIdentification[TPASS_PRODUCT_ID_LENGTH + 1];		//!< Product identification of the contactless reader.
	char szSerialNumber[TPASS_SERIAL_NUMBER_LENGTH + 1];			//!< Serial number of the contactless reader.
	char szProductCode[TPASS_PRODUCT_CODE_LENGTH + 1];				//!< Pruct code of the contactless reader.
	char szConstructorCode[TPASS_CONSTRUCTOR_CODE_LENGTH + 1];		//!< Constructor code of the contactless reader.
	char szManufacturingDate[TPASS_MANUFACTURING_DATE_LENGTH + 1];	//!< Manufacturing date of the contactless reader.
	char szBoosterVersion[TPASS_BOOSTER_VERSION_LENGTH + 1];		//!< Booster version of the contactless reader.
	unsigned int Options;											//!< Hardware options of the contactless reader. See TPASS_HARDWARE_OPTION_xxx.
} T_TPASS_HARDWARE_CAPABILITIES;

//! \brief Software capabilities of a contactless reader.
typedef struct
{
	unsigned int Ruf1;			//!< Reserved for future use.
	unsigned int Security;		//!< Not used.
	unsigned int Iso14443_C;	//!< ISO14443C is enabled on this reader.
	unsigned int Mifare;		//!< Mifare is enable on this reader.
	unsigned int Iso14443_AB;	//!< ISO14443AB is enabled on this reader.
	unsigned int Appli;			//!< Running an embedded application is allowed.
	unsigned int Ruf2;			//!< Reserved for future use.
} T_TPASS_SOFTWARE_CAPABILITIES;

//! @}

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \addtogroup TPassApiGeneral
//! @{

//! \brief Load the contactless DLL.
//! \return The return value of the ObjectLoad function. 0 is successull.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPasslib_open:KSFAM_DLL:0x22                                     */
/* ------------------------------------------------------------------------ */
int TPasslib_open(void);

//! \brief Unload the contactless DLL.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPasslib_close:KSFAM_DLL:0x23                                    */
/* ------------------------------------------------------------------------ */
void TPasslib_close(void);

//! \brief Check if a contactless reader is really connected.
//! \details This function sends a command to the external contactless reader (TeliumPass+ / Vending Pass / P30C) to know if it is still present or not.
//! It is quite fast if a reader is connected (~10ms), but quite slow if it is unplugged (~600ms).<br>
//! If you are using an internal contactless reader (ML30C for example), this function always returns \ref ERR_TPASS_OK.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref ERR_TPASS_OK</td><td>A contactless reader is present.</td></tr>
//! <tr><td>\ref ERR_TPASS_DISCONNECTED</td><td>There is no contactless reader connected.</td></tr>
//! <tr><td>\ref ERR_TPASS_NOT_CONFIGURED</td><td>No contactless reader is configured in the manager.</td></tr>
//! </table>
//! \remarks If the device is a TeliumPass+ or a VendingPass, this function turns on the device backlight (if device had been disconnected only).
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_CheckPresence:0x2D:0x01                                    */
/* ------------------------------------------------------------------------ */
int TPass_CheckPresence(void);

//! \brief Check the last known state of the connection with the contactless reader.
//! \details This function does not check for the presence of the contactless reader.
//! This returns the state of the software configuration.<br>
//! To really check the presence of the contactless reader, use the function \ref TPass_CheckPresence.
//! If you are using an internal contactless reader (ML30C for example), this function always returns \ref ERR_TPASS_OK.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref ERR_TPASS_OK</td><td>A contactless reader is present.</td></tr>
//! <tr><td>\ref ERR_TPASS_DISCONNECTED</td><td>There is no contactless reader connected.</td></tr>
//! <tr><td>\ref ERR_TPASS_NOT_CONFIGURED</td><td>No contactless reader is configured in the manager.</td></tr>
//! </table>
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_IsConnected:0x2D:0x02                                      */
/* ------------------------------------------------------------------------ */
int TPass_IsConnected(void);

//! \brief Retrieve the type of the contactless reader.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_NONE</td><td>There is no contactless reader.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_TELIUM_PASS</td><td>The contactless reader is a TeliumPass+ or an iST150 in TeliumPass+ emulation mode. Use \ref TPass_GetDeviceTypeEx to differentiate them.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_VENDING_PASS</td><td>The contactless reader is a Vending Pass.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_P30C</td><td>The contactless reader is a P30C or an iPP3xx in P30C emulation mode. Use \ref TPass_GetDeviceTypeEx to differentiate them.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_IPP2XX</td><td>The contactless reader is an iPP2xx.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_EMBEDDED</td><td>The contactless reader is embedded into the terminal.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_UNKNOWN</td><td>The contactless reader is unknown.</td></tr>
//! </table>
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetDeviceType:0x2D:0x24                                    */
/* ------------------------------------------------------------------------ */
int TPass_GetDeviceType(void);

//! \brief Retrieve the type of the contactless reader.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_NONE</td><td>There is no contactless reader.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_TELIUM_PASS</td><td>The contactless reader is a TeliumPass+.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_VENDING_PASS</td><td>The contactless reader is a Vending Pass.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_P30C</td><td>The contactless reader is a P30C.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_IPP2XX</td><td>The contactless reader is an iPP2xx.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_IPP3XX_EMUL_P30C</td><td>The contactless reader is an iPP3xx in P30C emulation mode.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_IST150_EMUL_TELIUM_PASS</td><td>The contactless reader is an iST150 in TeliumPass+ emulation mode.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_IUC150_EMUL_VENDING_PASS</td><td>The contactless reader is an iUC150 in Vending Pass emulation mode.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_EMBEDDED</td><td>The contactless reader is embedded into the terminal.</td></tr>
//! <tr><td>\ref TPASS_CLESS_TYPE_UNKNOWN</td><td>The contactless reader is unknown.</td></tr>
//! </table>
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetDeviceType:0x2D:0x24                                    */
/* ------------------------------------------------------------------------ */
int TPass_GetDeviceTypeEx(void);

//! \brief Determine if the the contactless interface is managed by a pinpad.
//! \return \a TRUE if the contactless is managed by a pinpad, \a FALSE otherwise.
int TPass_IsClessOnPinpad(void);

//! @}

//! \addtogroup TPassApiBacklight
//! @{

/*! \brief Set the backlight level of the contactless reader display.
\param[in] Level The backlight level:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_BACKLIGHT_OFF (0)</td><td>Turns off the backlight.</td></tr>
<tr><td>\ref TPASS_BACKLIGHT_ON (255)</td><td>Turns on the backlight.</td></tr>
<tr><td>1 to 254</td><td>Graduation of the backlight.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_01.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_BacklightLevel:0x2D:0x03                                   */
/* ------------------------------------------------------------------------ */
void TPass_BacklightLevel(unsigned char Level);

/*! \brief Fade the backlight of the contactless reader display to a defined level.
\param[in] StopLevel The backlight level to reach:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_BACKLIGHT_OFF (0)</td><td>Turns off the backlight.</td></tr>
<tr><td>\ref TPASS_BACKLIGHT_ON (255)</td><td>Turns on the backlight.</td></tr>
<tr><td>1 to 254</td><td>Graduation of the backlight.</td></tr>
</table>
\param[in] nRamp The fade ramp, in steps by second (512 implies a full fade in 0.5 second).
\remarks Example:

//! \include Cless_LowLevel_Sample_02.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_BacklightFadeToLevel:0x2D:0x04                             */
/* ------------------------------------------------------------------------ */
void TPass_BacklightFadeToLevel(unsigned char StopLevel, int nRamp);

//! @}

//! \addtogroup TPassApiBuzzer
//! @{

/*! \brief Set the buzzer state.
\param[in] nFrequency The frequency of the sound, in hertz (20 to 20000).
\param[in] Volume The volume of the sound (0 no sound, 255 maximum volume).
\remarks If the frequency is out of the range [20;20000] or if the volume is 0, the buzzer is turned off.
\remarks Example:

//! \include Cless_LowLevel_Sample_03.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_Buzzer:0x2D:0x05                                           */
/* ------------------------------------------------------------------------ */
void TPass_Buzzer(int nFrequency, unsigned char Volume);

/*! \brief Generate a beep.
\param[in] nFrequency The frequency of the sound, in hertz (20 to 20000).
\param[in] Volume The volume of the sound (0 no sound, 255 maximum volume).
\param[in] nDelay Duration of the beep, in 10 ms. unit.
\remarks This function blocks the caller until the sound is finished.
\remarks Example:

//! \include Cless_LowLevel_Sample_04.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_BuzzerBeep:0x2D:0x06                                       */
/* ------------------------------------------------------------------------ */
void TPass_BuzzerBeep(int nFrequency, unsigned char Volume, int nDelay);

//! @}

//! \addtogroup TPassApiLeds
//! @{

/*! \brief Turn on one or several LEDs.
\param[in] Leds LEDs to turn on. It is a combination of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_LED_1</td><td>Turn on the first LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_2</td><td>Turn on the second LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_3</td><td>Turn on the third LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_4</td><td>Turn on the fourth LED from the left.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_05.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_LedsOn:0x2D:0x07                                           */
/* ------------------------------------------------------------------------ */
void TPass_LedsOn(unsigned char Leds);


/*! \brief Turn on one or several LEDs.
\param[in] Leds LEDs to turn on. It is a combination of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_LED_1</td><td>Turn on the first LED from the left (in green).</td></tr>
<tr><td>\ref TPASS_LED_2</td><td>Turn on the second LED from the left (in green).</td></tr>
<tr><td>\ref TPASS_LED_3</td><td>Turn on the third LED from the left (in green).</td></tr>
<tr><td>\ref TPASS_LED_4</td><td>Turn on the fourth LED from the left (in green).</td></tr>
<tr><td>\ref TPASS_LED_BLUE</td><td>Turn on the first LED from the left (in blue).</td></tr>
<tr><td>\ref TPASS_LED_YELLOW</td><td>Turn on the second LED from the left (in yellow).</td></tr>
<tr><td>\ref TPASS_LED_GREEN</td><td>Turn on the third LED from the left (in green).</td></tr>
<tr><td>\ref TPASS_LED_RED</td><td>Turn on the fourth LED from the left (in red).</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_06.c
*/
void TPass_LedsOnColored(unsigned char Leds);


/*! \brief Turn off one or several LEDs.
\param[in] Leds LEDs to turn off. It is a combination of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_LED_1</td><td>Turn off the first LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_2</td><td>Turn off the second LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_3</td><td>Turn off the third LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_4</td><td>Turn off the fourth LED from the left.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_07.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_LedsOff:0x2D:0x08                                          */
/* ------------------------------------------------------------------------ */
void TPass_LedsOff(unsigned char Leds);


/*! \brief Turn off one or several LEDs.
\param[in] Leds LEDs to turn off. It is a combination of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_LED_1</td><td>Turn off the first LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_2</td><td>Turn off the second LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_3</td><td>Turn off the third LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_4</td><td>Turn off the fourth LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_BLUE</td><td>Turn off the first LED from the left (blue one).</td></tr>
<tr><td>\ref TPASS_LED_YELLOW</td><td>Turn off the second LED from the left (yellow one).</td></tr>
<tr><td>\ref TPASS_LED_GREEN</td><td>Turn off the third LED from the left (green one).</td></tr>
<tr><td>\ref TPASS_LED_RED</td><td>Turn off the fourth LED from the left (red one).</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_08.c
*/
void TPass_LedsOffColored(unsigned char Leds);


/*! \brief Blink one or several LEDs.
\param[in] Leds LEDs to blink. It is a combination of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_LED_1</td><td>Blink the first LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_2</td><td>Blink the second LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_3</td><td>Blink the third LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_4</td><td>Blink the fourth LED from the left.</td></tr>
</table>
\param[in] TimeOn Time during the LEDs are on (the unit is \ref TPASS_LED_BLINK_TICKS * 10ms => 20ms).
\param[in] TimeOff Time during the LEDs are off (the unit is \ref TPASS_LED_BLINK_TICKS * 10ms => 20ms).
\remarks Two blinking examples:

//! \include Cless_LowLevel_Sample_09.c

//! \include Cless_LowLevel_Sample_10.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_LedsBlink:0x2D:0x09                                        */
/* ------------------------------------------------------------------------ */
void TPass_LedsBlink(unsigned char Leds, unsigned char TimeOn, unsigned char TimeOff);


/*! \brief Blink one or several LEDs.
\param[in] Leds LEDs to blink. It is a combination of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_LED_1</td><td>Blink the first LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_2</td><td>Blink the second LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_3</td><td>Blink the third LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_4</td><td>Blink the fourth LED from the left.</td></tr>
<tr><td>\ref TPASS_LED_BLUE</td><td>Blink the first LED from the left (in blue).</td></tr>
<tr><td>\ref TPASS_LED_YELLOW</td><td>Blink the second LED from the left (in yellow).</td></tr>
<tr><td>\ref TPASS_LED_GREEN</td><td>Blink the third LED from the left (in green).</td></tr>
<tr><td>\ref TPASS_LED_RED</td><td>Blink the fourth LED from the left (in red).</td></tr>
</table>
\param[in] TimeOn Time during the LEDs are on (the unit is \ref TPASS_LED_BLINK_TICKS * 10ms => 20ms).
\param[in] TimeOff Time during the LEDs are off (the unit is \ref TPASS_LED_BLINK_TICKS * 10ms => 20ms).
\remarks Two blinking examples:

//! \include Cless_LowLevel_Sample_11.c

//! \include Cless_LowLevel_Sample_12.c
*/
void TPass_LedsBlinkColored(unsigned char Leds, unsigned char TimeOn, unsigned char TimeOff);


//! @}

//! \addtogroup TPassApiDisplay
//! @{

//! \brief Clear the contactless display and set the cursor position to the top-left corner.
//! \remarks The display can be changed by using the \ref TPass_SetCustomerDisplay function.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_FirstLine:0x2D:0x0A                                        */
/* ------------------------------------------------------------------------ */
void TPass_FirstLine(void);

//! \brief Set the contactless display cursor position to the beginning of the next line.
//! \remarks The display can be changed by using the \ref TPass_SetCustomerDisplay function.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_NewLine:0x2D:0x0B                                          */
/* ------------------------------------------------------------------------ */
void TPass_NewLine(void);

//! \brief Clear the current line of the contactless display and set the cursor position to its beginning.
//! \remarks The display can be changed by using the \ref TPass_SetCustomerDisplay function.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_ClearLine:0x2D:0x0C                                        */
/* ------------------------------------------------------------------------ */
void TPass_ClearLine(void);

//! \brief Display a string on the contactless display.
//! \param[in] szString String to display.
//! \remarks The display can be changed by using the \ref TPass_SetCustomerDisplay function.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_Display:0x2D:0x0D                                          */
/* @GSIM_A:1:DATA_CODE(strlen(szString)+1)                                  */
/* @GSIM_A:1:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
void TPass_Display(const char* szString);

//! \brief Display a string on the contactless display at a given position.
//! \param[in] nX X position.
//! \param[in] nY Y position.
//! \param[in] szString String to display at position [nX,nY].
//! \remarks The display can be changed by using the \ref TPass_SetCustomerDisplay function.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_DisplayXY:0x2D:0x0E                                        */
/* @GSIM_A:3:DATA_CODE(strlen(szString)+1)                                  */
/* @GSIM_A:3:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
void TPass_DisplayXY(int nX, int nY, const char* szString);

//! \brief Returns the driver name of the contactless customer display.
//! \param[out] pDisplayName Display driver name (NULL if not used). Empty string "" for no display.
//! \param[in] nBufferSize Size of the buffer \a pDisplayName (0 if not used).
//! \return Returns the graphic library peripheral identifier of the contactless customer display. -1 for no display.
//! \remarks The display can be changed by using the \ref TPass_SetCustomerDisplay function.
//! \remarks The default display is the display of the contactless reader : TeliumPass+, Vending Pass, P30CL or terminal display for embedded contactless.
//! \remarks For the iPP220 device, function returns -1 as there is no graphic feature on this device. Only \a pDisplayName is set.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetCustomerDisplay:0x2D:0x28                               */
/* @GSIM_A:1:DATA_SIZE(nBufferSize)                                         */
/* @GSIM_A:1:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetCustomerDisplay(char* pDisplayName, int nBufferSize);

/*! \brief Change the contactless customer display.
\param[in] pDisplayName Display driver name. Specify an empty string "" for no display.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>"DISPLAY"</td><td>Main terminal display.</td></tr>
<tr><td>"DISPLAY_PPR"</td><td>Pinpad display.</td></tr>
<tr><td>"DISPLAY_C30"</td><td>TeliumPass+ or Vending Pass display.</td></tr>
<tr><td>"DISPLAY_PP_2x16"</td><td>iPP2xx display (not graphical one).</td></tr>
</table>
\param[in] nDisplayID The graphic library peripheral identifier of the customer display.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>PERIPH_DISPLAY</td><td>Main terminal display.</td></tr>
<tr><td>PERIPH_PPR</td><td>Pinpad display.</td></tr>
<tr><td>PERIPH_C30</td><td>TeliumPass+ or Vending Pass display.</td></tr>
</table>
\remarks <b>There is no need to call this function during initialisation. The contactless DLL set the default value depending on the contactless reader.</b>
\remarks If \a pDisplayName is NULL, the value is calculated by using \a nDisplayID.
\remarks If \a nDisplayID is -1, the value is calculated by using \a pDisplayName.
\remarks If \a pDisplayName is NULL and \a nDisplayID is -1, the default display is used.
\remarks If you are using an iPP220 device, you shall set \a pDisplayName data (as there is no graphical context available for this device, \a nDisplayID shall not be used).
\remarks Some examples:

//! \include Cless_LowLevel_Sample_13.c

//! \include Cless_LowLevel_Sample_14.c

//! \include Cless_LowLevel_Sample_15.c

//! \include Cless_LowLevel_Sample_16.c

//! \include Cless_LowLevel_Sample_17.c

//! \include Cless_LowLevel_Sample_18.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_SetCustomerDisplay:0x2D:0x29                               */
/* @GSIM_A:1:SUPPLIED(BUF_SER_null_string;BUF_DES_null_string)              */
/* @GSIM_A:1:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
void TPass_SetCustomerDisplay(const char* pDisplayName, int nDisplayID);

//! @}

//! \addtogroup TPassContactLessStdDriver
//! @{

/*! \brief Open the ISO14443-4 contactless driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The driver is opened.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessEmv_OpenDriver(void);

//! \brief Close the ISO14443-4 contactless driver.
void ClessEmv_CloseDriver(void);

/*! \brief Retreive the version of the level 1 specification.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>-1</td><td>The information is not available (software componants too old, ...).</td></tr>
<tr><td>1</td><td>The driver is EMV 1.1 certified.</td></tr>
<tr><td>2</td><td>The driver is EMV 2.0 or 2.0.1 certified.</td></tr>
</table>
*/
int ClessEmv_GetSpecVersion(void);

/*! \cond NOT_DOCUMENTED
\brief Retrieve the ISO14443-4 contactless driver handle if it has been opened by using fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessEmv_GetDriver(void);

//! \endcond

/*! \brief Change the task that owns of the ISO14443-4 contactless driver.
\param[in] nNoTask The task number that will own the ISO14443-4 driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessEmv_ChangeOwner(unsigned short nNoTask);

//! \brief Indicate if the ISO14443-4 contactless driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
int ClessEmv_IsDriverOpened(void);

/*! \cond NOT_DOCUMENTED
\brief Execute an ISO14443-4 driver command.
\param[in] nCommand Command to execute.
\param[in] nData1 First parameter.
\param[in] nData2 Second parameter.
\param[in] nData3 Third parameter.
\param[in] nData4 Fourth parameter.
\return \a CL_xxx status code.
*/
int ClessEmv_FormatCommand(unsigned char nCommand, unsigned int nData1, unsigned int nData2, unsigned int nData3, unsigned int nData4);

//! \endcond

/*! \brief Retreive the UID of an ISO14443-4 contactless card.
\param[out] pUid The UID of the card. The buffer must be 12 bytes long. The UID can be on 4, 7 or 10 bytes.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
<tr><td>\a CLESS_NOT_IMPLEMENTED</td><td>The function is not implemented (the driver is too old).</td></tr>
</table>
*/
int ClessEmv_GetUid(unsigned char* pUid);

//! @}

//! \addtogroup TPassContactLessStdDetection
//! @{

/*! \brief Start the detection of an ISO14443-4 contactless card.
\param[in] nMaxNumOfCards Maximum number of cards. Shall be set to 1.
\param[in] nTypeOfCard Type of card that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_TYPE_A</td><td>Type A cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_B</td><td>Type B cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_AB</td><td>Type A and type B cards will be detected.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
\remarks
When a card is detected by the contactless driver, the <b>CLESS</b> event is generated. Use <i>ttestall(CLESS, timeout)</i> to wait for it.<br>
When the event occurs, the application shall call \ref ClessEmv_DetectCards to retrieve the result and the number of detected cards.<br>
To cancel the detection, call \ref ClessEmv_DetectCardsStop or \ref ClessEmv_CloseDriver.<br>
When a card is detected, the application shall call \ref ClessEmv_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_19.c
*/
int ClessEmv_DetectCardsStart(unsigned int nMaxNumOfCards, unsigned char nTypeOfCard);

/*! \brief Wait until an ISO14443-4 contactless card is detected.
\param[in] nTypeOfCard Type of card that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_TYPE_A</td><td>Type A cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_B</td><td>Type B cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_AB</td><td>Type A and type B cards will be detected.</td></tr>
</table>
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
<tr><td>\a CL_NOCARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a CL_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
</table>
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
If the caller does not want to be blocked, it must call first the \ref ClessEmv_DetectCardsStart function.
In such a case, the \ref ClessEmv_DetectCards functions will not block the caller. So, a small timeout may be given.<br>
When a card is detected, the application shall call \ref ClessEmv_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_20.c
*/
int ClessEmv_DetectCards(unsigned char nTypeOfCard, unsigned int* pNumOfCards, unsigned int nTimeout);

/*! \brief Stop the detection of an ISO14443-4 contactless card started with \ref ClessEmv_DetectCardsStart.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The detection is stopped.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
\remarks
See \ref ClessEmv_DetectCardsStart for more details.
*/
int ClessEmv_DetectCardsStop(void);

//! @}

//! \addtogroup TPassContactLessStdActivation
//! @{

/*! \brief Activate an ISO14443-4 contactless card to communicate with it.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessEmv_DetectCards function.
\param[in] nKindOfCard Is the kind of card that is waited. It must be \a CL_ISO14443_4.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is activated.</td></tr>
<tr><td>\a CL_INVALIDCARD</td><td>The detected card is not valid (\a nKindOfCard does not match).</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessEmv_ActiveCard(unsigned char nCardIndex, unsigned char nKindOfCard);

//! @}

//! \addtogroup TPassContactLessStdDeselection
//! @{

/*! \brief Deselect an ISO14443-4 contactless card.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessEmv_DetectCards function.
\param[in] bSendDeselect Indicate if the deselect command shall be sent to the card or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Send the deselect command to the card. Use it in the nominal case (no error).</td></tr>
<tr><td>\a FALSE</td><td>Do not send the deselect command to the card. Use it only when the last contactless function call returned an error.</td></tr>
</table>
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is deselected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessEmv_DeselectCard(unsigned char nCardIndex, unsigned int bSendDeselect, unsigned int bWaitRemove);

/*! \brief Start the deselection of an ISO14443-4 contactless card.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessEmv_DetectCards function.
\param[in] bSendDeselect Indicate if the deselect command shall be sent to the card or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Send the deselect command to the card. Use it in the nominal case (no error).</td></tr>
<tr><td>\a FALSE</td><td>Do not send the deselect command to the card. Use it only when the last contactless function call returned an error.</td></tr>
</table>
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is being deselected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
\remarks
When the operation is finished the <b>CLESS</b> event is generated. Use <i>ttestall(CLESS, timeout)</i> to wait for it.<br>
To cancel the deselection, call \ref ClessEmv_CloseDriver.<br>
*/
int ClessEmv_DeselectCardStart(unsigned char nCardIndex, unsigned int bSendDeselect, unsigned int bWaitRemove);

//! @}

//! \addtogroup TPassContactLessStdCommands
//! @{

/*! \brief Send a command to an ISO14443-4 contactless card.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessEmv_DetectCards function.
\param[in] pCommand Is the command to send to the card.
\param[in] nCommandLength Is the length of the command \a pCommand to be sent to the card.
\param[out] pResponse Will contain the card response.
\param[in,out] pResponseLength As input, it contains the size of the \a pResponse buffer.
As output, it contains the length of the card response \a pResponse. A card response cannot exceed 258 bytes (256 data bytes + SW1 and SW2).
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The command is sent.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessEmv_Apdu(unsigned char nCardIndex, const void* pCommand, unsigned int nCommandLength, void* pResponse, unsigned int* pResponseLength);

//! @}

//! \addtogroup TPassContactLessStdObsolete
//! @{

//! \brief <b>OBSOLETE. Use \ref ClessEmv_OpenDriver instead.</b> Open the ISO14443-4 driver.
//! \return Zero if an error occurs. Non zero if the driver is opened.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_OpenDriver:0x31:0x08                                       */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_OpenDriver (void);

//! \brief <b>OBSOLETE. Use \ref ClessEmv_CloseDriver instead.</b> Close the ISO14443-4 driver.
//! \return Zero if an error occurs. Non zero if the driver is closed.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_CloseDriver:0x31:0x09                                      */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_CloseDriver (void);

//! \brief <b>OBSOLETE. Use \ref ClessEmv_IsDriverOpened instead.</b> Indicate if the ISO14443-4 driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_IsDriverOpened:0x31:0x0A                                   */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_IsDriverOpened (void);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_DetectCardsStart instead.</b> Start the detection of an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nTypeOfCard Type of card that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_TYPE_A</td><td>Type A cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_B</td><td>Type B cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_AB</td><td>Type A and type B cards will be detected.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The detection has started.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
\remarks
When a card is detected by the contactless driver the <b>CLESS</b> event is generated. Use <i>ttestall(CLESS, timeout)</i> to wait for it.<br>
When the event occurs, the application shall call \ref CLESS_DetectCards to retrieve the result and the number of detected cards.<br>
To cancel the detection, call \ref CLESS_DetectCardsStop or \ref CLESS_CloseDriver.<br>
When a card is detected, the application shall call \ref CLESS_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_21.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DetectCardsStart:0x31:0x01                                 */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DetectCardsStart(FILE* hDriver, unsigned char nTypeOfCard);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_DetectCards instead.</b> Wait until an ISO14443-4 contactless card is detected.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nTypeOfCard Type of card that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_TYPE_A</td><td>Type A cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_B</td><td>Type B cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_AB</td><td>Type A and type B cards will be detected.</td></tr>
</table>
\param[out] pNumOfCards The number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
<tr><td>\a CL_NOCARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a CL_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
<tr><td>\a CL_INVALIDCARD</td><td>The detected card is not valid.</td></tr>
</table>
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
If the caller does not want to be blocked, it must call first the \ref CLESS_DetectCardsStart function.
In such a case, the \ref CLESS_DetectCards functions will not block the caller. So, a small timeout may be given.<br>
When a card is detected, the application shall call \ref CLESS_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_22.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DetectCards:0x31:0x02                                      */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DetectCards(FILE* hDriver, unsigned char nTypeOfCard, unsigned int* pNumOfCards, unsigned int nTimeout);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_DetectCardsStop instead.</b> Stop the detection of a contactless card started with \ref CLESS_DetectCardsStart.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The detection is stopped.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
\remarks
See \ref CLESS_DetectCardsStart for more details.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DetectCardsStop:0x31:0x03                                  */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DetectCardsStop(FILE* hDriver);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_ActiveCard instead.</b> Activate an ISO14443-4 contactless card to communicate with it.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref CLESS_DetectCards function.
\param[in] nKindOfCard Is the kind of card that is waited. It must be \a CL_ISO14443_4.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is activated.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_ActiveCard:0x31:0x04                                       */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_ActiveCard(FILE* hDriver, unsigned char nCardIndex, unsigned char nKindOfCard);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_DeselectCard instead.</b> Deselect an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref CLESS_DetectCards function.
\param[in] bSendDeselect Indicate if the deselect command shall be sent to the card or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Send the deselect command to the card. Use it in the nominal case (no error).</td></tr>
<tr><td>\a FALSE</td><td>Do not send the deselect command to the card. Use it only when the last contactless function call returned an error.</td></tr>
</table>
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is deselected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DeselectCard:0x31:0x05                                     */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DeselectCard(FILE* hDriver, unsigned char nCardIndex, unsigned int bSendDeselect, unsigned int bWaitRemove);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_DeselectCardStart instead.</b> Start the deselection of an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessEmv_DetectCards function.
\param[in] bSendDeselect Indicate if the deselect command shall be sent to the card or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Send the deselect command to the card. Use it in the nominal case (no error).</td></tr>
<tr><td>\a FALSE</td><td>Do not send the deselect command to the card. Use it only when the last contactless function call returned an error.</td></tr>
</table>
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is being deselected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
\remarks
When the operation is finished the <b>CLESS</b> event is generated. Use <i>ttestall(CLESS, timeout)</i> to wait for it.<br>
To cancel the deselection, call \ref CLESS_CloseDriver.<br>
*/
unsigned int CLESS_DeselectCardStart(FILE* hDriver, unsigned char nCardIndex, unsigned int bSendDeselect, unsigned int bWaitRemove);

/*! \brief <b>OBSOLETE. Use \ref ClessEmv_Apdu instead.</b> Send a command to an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref CLESS_DetectCards function.
\param[in] pCommand Is the command to send to the card.
\param[in] nCommandLength Is the length of the command to be sent to the card.
\param[out] pResponse Will contain the card response. The maximum response length is 288 bytes.
\param[out] pResponseLength Is the length of the card response.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The command is sent.</td></tr>
<tr><td>\a CL_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_Apdu:0x31:0x07                                             */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:DATA_SIZE(nCommandLength)                                      */
/* @GSIM_A:3:IN_ONLY                                                        */
/* @GSIM_A:5:DATA_CODE(*pResponseLength)                                    */
/* @GSIM_A:5:OUT_ONLY                                                       */
/* @GSIM_A:6:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_Apdu(FILE* hDriver, unsigned char nCardIndex, const void* pCommand, unsigned int nCommandLength, void* pResponse, unsigned int* pResponseLength);

//! @}

//! \addtogroup TPassContactLessMifareDriver
//! @{

/*! \brief Open the MIFARE driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The driver is opened.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_OpenDriver(void);

//! \brief Close the MIFARE driver.
void ClessMifare_CloseDriver(void);

/*! \cond NOT_DOCUMENTED
\brief Retrieve the MIFARE driver handle if it has been opened by using fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_GetDriver(void);
//! \endcond

/*! \brief Change the task that owns of the MIFARE driver.
\param[in] nNoTask The task number that will own the MIFARE driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_ChangeOwner(unsigned short nNoTask);

//! \brief Indicate if the MIFARE driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
int ClessMifare_IsDriverOpened(void);

/*! \cond NOT_DOCUMENTED
\brief Execute a MIFARE driver command.
\param[in] nCommand Command to execute.
\param[in] nData1 First parameter.
\param[in] nData2 Second parameter.
\param[in] nData3 Third parameter.
\param[in] nData4 Fourth parameter.
\return \a MF_xxx status code.
*/
int ClessMifare_FormatCommand(unsigned char nCommand, unsigned int nData1, unsigned int nData2, unsigned int nData3, unsigned int nData4);
//! \endcond

//! @}

//! \addtogroup TPassContactLessMifareDetection
//! @{

/*! \brief Wait until a MIFARE contactless card is detected.
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table>
<tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
<tr><td>\a MF_NO_CARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a MF_INVALIDCARD</td><td>The detected card is not a MIFARE one.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
When a card is detected, the application shall call \ref ClessMifare_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_23.c
*/
int ClessMifare_DetectCards(unsigned int *pNumOfCards, unsigned int nTimeout);

/*! \brief Wait until a MIFARE contactless card is detected.
\param[in] nKindOfCard Type of the MIFARE. Can a mix of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_MF_CLASSIC</td><td>Support for MIFARE Classic cards.</td></tr>
<tr><td>\a CL_MF_ULTRALIGHT</td><td>Support for MIFARE Ultra Light cards.</td></tr>
</table>
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
<tr><td>\a MF_NO_CARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a MF_INVALIDCARD</td><td>The detected card is not a MIFARE one.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
When a card is detected, the application shall call \ref ClessMifare_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_24.c
*/
int ClessMifare_DetectCardsEx(unsigned char nKindOfCard, unsigned int *pNumOfCards, unsigned int nTimeout);

/*! \brief Retrieve the type of the MIFARE card and its UID.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessMifare_DetectCards function.
\param[out] pKindOfCard The type of the MIFARE card.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_MF_CLASSIC</td><td>MIFARE Classic.</td></tr>
<tr><td>\a CL_MF_ULTRALIGHT</td><td>MIFARE Ultra Light.</td></tr>
</table>
\param[out] pUidLength Length of the UID.
\param[out] pUid UID of the card.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
<tr><td>\a CLESS_NOT_IMPLEMENTED</td><td>The function is not implemented (the driver is too old).</td></tr>
</table>
*/
int ClessMifare_GetUid(unsigned char nCardIndex, unsigned char *pKindOfCard, unsigned char *pUidLength, unsigned char *pUid);

//! @}

//! \addtogroup TPassContactLessMifareActivation
//! @{

/*! \brief Activate a MIFARE contactless card to communicate with it.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessMifare_DetectCards function.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The card is activated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_ActiveCard(unsigned char nCardIndex);

//! @}

//! \addtogroup TPassContactLessMifareBlockOperations
//! @{

/*! \brief Authenticate a sector of a MIFARE contactless card.
\param[in] nKeyType The type of the key:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a KEY_A</td><td>It is a type A key.</td></tr>
<tr><td>\a KEY_B</td><td>It is a type B key.</td></tr>
</table>
\param[in] pUncodedKey Is the key to use. The length of a MIFARE key is \ref TPASS_MIFARE_KEY_LENGTH (6 bytes).
\param[in] nSector The sector to authenticate.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The sector is authenticated.</td></tr>
<tr><td>\a MF_AUTH_ERR</td><td>Authentication failed.</td></tr>
<tr><td>\a MF_LOAD_KEY_ERR</td><td>Error during key loading.</td></tr>
<tr><td>\a MF_NOT_MF1</td><td>The card is a MIFARE UltraLight one.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_Authentication(unsigned char nKeyType, const unsigned char* pUncodedKey, unsigned char nSector);

/*! \brief Read a block of a sector of a MIFARE contactless card. On MiFare Ultralight cards, 
this function reads 4 consecutives memory pages (each page has a length of 4 bytes) so 16 bytes 
are directly read.
\param[in] nDataType Is the type of the data (not used on MiFare Ultralight cards) :
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a VALUE</td><td>To access to a 4 bytes value.</td></tr>
<tr><td>\a DATA</td><td>To access to a 16 bytes buffer.</td></tr>
</table>
\param[in] nSector The sector number to read (not used on MiFare Ultralight cards).
\param[in] nBlock The block number where the sector is located. On MiFare Ultralight cards, it indicates the page address.
\param[out] pBuffer The buffer that will receive the read data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The block is read.</td></tr>
<tr><td>\a MF_TIME_OUT_ERR</td><td>Communication timeout.</td></tr>
<tr><td>\a MF_RESPONSE_SIZE_ERR</td><td>Invalid response size.</td></tr>
<tr><td>\a MF_AUTH_ERR</td><td>The block is not authenticated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_ReadBlock(unsigned char nDataType, unsigned char nSector, unsigned char nBlock, void* pBuffer);

/*! \brief Write a block of a sector of a MIFARE contactless card. On MiFare Ultralight cards, 
this function writes in a memory page (a page has a length of 4 bytes). Some pages are reserved (Serial number or 
Internal bytes) so you have to respect the MF Ultralight specification.
\param[in] nDataType Is the type of the data (not used on MiFare Ultralight cards):
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a VALUE</td><td>To access to a 4 bytes value.</td></tr>
<tr><td>\a DATA</td><td>To access to a 16 bytes buffer.</td></tr>
</table>
\param[in] nSector The sector number to read (not used on MiFare Ultralight cards).
\param[in] nBlock The block number where the sector is located. On MF ultralight, it indicates the address of the page you want to write.
\param[in] pBuffer The buffer that contains the data to write.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The block is written.</td></tr>
<tr><td>\a MF_TIME_OUT_ERR</td><td>Communication timeout.</td></tr>
<tr><td>\a MF_RESPONSE_SIZE_ERR</td><td>Invalid response size.</td></tr>
<tr><td>\a MF_AUTH_ERR</td><td>The block is not authenticated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_WriteBlock(unsigned char nDataType, unsigned char nSector, unsigned char nBlock, const void* pBuffer);

/*! \brief Perform an operation on the value of a block of a MIFARE contactless card.
\param[in] nOperationType Is the operation to perform.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_INCREMENT</td><td>To increment the value.</td></tr>
<tr><td>\a MF_DECREMENT</td><td>To decrement the value.</td></tr>
<tr><td>\a MF_RESTORE</td><td>To restore the value.</td></tr>
</table>
\param[in] nSector The sector number on which the operation is performed.
\param[in] nSourceBlock The source block where the sector is located.
\param[in] nDestBlock The destination block where the sector is located.
\param[in] pValue The value used of the operation (4 bytes value). Only valid for \a MF_INCREMENT and \a MF_DECREMENT operations. On Mifare Ultra light, you write one page of 4 bytes.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The operation on the block is successful.</td></tr>
<tr><td>\a MF_TIME_OUT_ERR</td><td>Communication timeout.</td></tr>
<tr><td>\a MF_RESPONSE_SIZE_ERR</td><td>Invalid response size.</td></tr>
<tr><td>\a MF_AUTH_ERR</td><td>The block is not authenticated.</td></tr>
<tr><td>\a MF_AUTH_ERR</td><td>The block is not authenticated.</td></tr>
<tr><td>\a MF_VALUE_ERR</td><td>The memory area used to store the value is not consistent.</td></tr>
<tr><td>\a MF_NOT_MF1</td><td>The card is a MIFARE UltraLight one.</td></tr>
<tr><td>\a MF_AUTH_ERR</td><td>The block is not authenticated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessMifare_ValueOperation(unsigned char nOperationType, unsigned char nSector, unsigned char nSourceBlock, unsigned char nDestBlock, void* pValue);

//! @}

//! \addtogroup TPassContactLessMifareObsolete
//! @{

//! \brief <b>OBSOLETE. Use \ref ClessMifare_OpenDriver instead.</b> Open the MIFARE driver.
//! \return Zero if an error occurs. Non zero if the driver is opened.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_OpenDriver:0x2D:0x25                                          */
/* ------------------------------------------------------------------------ */
unsigned int MF_OpenDriver (void);

//! \brief <b>OBSOLETE. Use \ref ClessMifare_CloseDriver instead.</b> Close the MIFARE driver.
//! \return Zero if an error occurs. Non zero if the driver is closed.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_CloseDriver:0x2D:0x26                                         */
/* ------------------------------------------------------------------------ */
unsigned int MF_CloseDriver (void);

//! \brief <b>OBSOLETE. Use \ref ClessMifare_IsDriverOpened instead.</b> Indicate if the MIFARE driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_IsDriverOpened:0x2D:0x27                                      */
/* ------------------------------------------------------------------------ */
unsigned int MF_IsDriverOpened (void);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_DetectCards instead.</b> Wait until a MIFARE contactless card is detected.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
<tr><td>\a MF_NOCARD</td><td>There is no card (timeout).</td></tr>
</table>
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
When a card is detected, the application shall call \ref MF_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_25.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_DetectCards:0x2D:0x15                                         */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:2:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int MF_DetectCards(FILE* hDriver, unsigned int *pNumOfCards, unsigned int nTimeout);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_DetectCardsEx instead.</b> Wait until a MIFARE contactless card is detected.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nKindOfCard Type of the MIFARE. Can a mix of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_MF_CLASSIC</td><td>Support for MIFARE Classic cards.</td></tr>
<tr><td>\a CL_MF_ULTRALIGHT</td><td>Support for MIFARE Ultra Light cards.</td></tr>
</table>
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
<tr><td>\a MF_NOCARD</td><td>There is no card (timeout).</td></tr>
</table>
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
When a card is detected, the application shall call \ref MF_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_26.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_DetectCardsEx:0x2D:0x2A                                       */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int MF_DetectCardsEx(FILE* hDriver, unsigned char nKindOfCard, unsigned int *pNumOfCards, unsigned int nTimeout);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_GetUid instead.</b> Retrieve the type of the MIFARE card and its UID.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref MF_DetectCards function.
\param[out] pKindOfCard The type of the MIFARE card.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_MF_CLASSIC</td><td>MIFARE Classic.</td></tr>
<tr><td>\a CL_MF_ULTRALIGHT</td><td>MIFARE Ultra Light.</td></tr>
</table>
\param[out] pUidLength Length of the UID.
\param[out] pUid UID of the card.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
<tr><td>\a CLESS_NOT_IMPLEMENTED</td><td>The function is not implemented (the driver is too old).</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_GetUid:0x2D:0x2B                                              */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:2:IN_ONLY                                                       */
/* @GSIM_A:3:ONE_POINTER                                                    */
/* @GSIM_A:3:OUT_ONLY                                                       */
/* @GSIM_A:4:ONE_POINTER                                                    */
/* @GSIM_A:4:OUT_ONLY                                                       */
/* @GSIM_A:5:DATA_SIZE(10)                                                  */
/* @GSIM_A:5:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
unsigned int MF_GetUid(FILE* hDriver, unsigned char nCardIndex, unsigned char *pKindOfCard, unsigned char *pUidLength, unsigned char *pUid);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_ActiveCard instead.</b> Activate a MIFARE contactless card to communicate with it.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref MF_DetectCards function.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The card is activated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_ActiveCard:0x2D:0x16                                          */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int MF_ActiveCard(FILE* hDriver, unsigned char nCardIndex);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_Authentication instead.</b> Authenticate a sector of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nKeyType The type of the key:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a KEY_A</td><td>It is a type A key.</td></tr>
<tr><td>\a KEY_B</td><td>It is a type B key.</td></tr>
</table>
\param[in] pUncodedKey Is the key to use. The length of a MIFARE key is \ref TPASS_MIFARE_KEY_LENGTH (6 bytes).
\param[in] nSector The sector to authenticate.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The sector is authenticated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_Authentication:0x2D:0x17                                      */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:DATA_SIZE(6)                                                   */
/* @GSIM_A:3:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
unsigned int MF_Authentication(FILE* hDriver, unsigned char nKeyType, const unsigned char* pUncodedKey, unsigned char nSector);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_ReadBlock instead.</b> Read a block of a sector of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nDataType Is the type of the data:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a VALUE</td><td>To access to a 4 bytes value.</td></tr>
<tr><td>\a DATA</td><td>To access to a 16 bytes buffer.</td></tr>
</table>
\param[in] nSector The sector number to read.
\param[in] nBlock The block number where the sector is located.
\param[out] pBuffer The buffer that will receive the read data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The block is read.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_ReadBlock:0x2D:0x18                                           */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:5:DATA_CODE(((nDataType == 1) ? 4:16))                           */
/* @GSIM_A:5:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
unsigned int MF_ReadBlock(FILE* hDriver, unsigned char nDataType, unsigned char nSector, unsigned char nBlock, void* pBuffer);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_WriteBlock instead.</b> Write a block of a sector of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nDataType Is the type of the data:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a VALUE</td><td>To access to a 4 bytes value.</td></tr>
<tr><td>\a DATA</td><td>To access to a 16 bytes buffer.</td></tr>
</table>
\param[in] nSector The sector number to read.
\param[in] nBlock The block number where the sector is located.
\param[in] pBuffer The buffer that contains the data to write.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The block is written.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_WriteBlock:0x2D:0x19                                          */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:5:DATA_CODE(((nDataType == 1) ? 4:16))                           */
/* @GSIM_A:5:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
unsigned int MF_WriteBlock(FILE* hDriver, unsigned char nDataType, unsigned char nSector, unsigned char nBlock, const void* pBuffer);

/*! \brief <b>OBSOLETE. Use \ref ClessMifare_ValueOperation instead.</b> Perform an operation on the value of a block of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nOperationType Is the operation to perform.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_INCREMENT</td><td>To increment the value.</td></tr>
<tr><td>\a MF_DECREMENT</td><td>To decrement the value.</td></tr>
<tr><td>\a MF_RESTORE</td><td>To restore the value.</td></tr>
</table>
\param[in] nSector The sector number on which the operation is performed.
\param[in] nSourceBlock The source block where the sector is located.
\param[in] nDestBlock The destination block where the sector is located.
\param[in] pValue The value used of the operation.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The operation on the block is successful.</td></tr>
<tr><td>\a MF_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_ValueOperation:0x2D:0x1A                                      */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:6:DATA_SIZE(4)                                                   */
/* @GSIM_A:6:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
unsigned int MF_ValueOperation(FILE* hDriver, unsigned char nOperationType, unsigned char nSector, unsigned char nSourceBlock, unsigned char nDestBlock, void* pValue);

//! @}

//! \addtogroup TPassContactLessStmDriver
//! @{

/*! \brief Open the STMicroelectronics contactless driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The driver is opened.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_OpenDriver(void);

//! \brief Close the STMicroelectronics contactless driver.
void ClessStm_CloseDriver(void);

/*! \cond NOT_DOCUMENTED
\brief Retrieve the STMicroelectronics contactless driver handle if it has been opened by using fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_GetDriver(void);

//! \endcond

/*! \brief Change the task that owns of the STMicroelectronics contactless driver.
\param[in] nNoTask The task number that will own the STMicroelectronics contactless driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_ChangeOwner(unsigned short nNoTask);

//! \brief Indicate if the STMicroelectronics contactless driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
int ClessStm_IsDriverOpened(void);

/*! \cond NOT_DOCUMENTED
\brief Execute a STMicroelectronics contactless driver command.
\param[in] nCommand Command to execute.
\param[in] nData1 First parameter.
\param[in] nData2 Second parameter.
\param[in] nData3 Third parameter.
\param[in] nData4 Fourth parameter.
\return \a CLSTM_xxx status code.
*/
int ClessStm_FormatCommand(unsigned char nCommand, unsigned int nData1, unsigned int nData2, unsigned int nData3, unsigned int nData4);

//! \endcond

/*! \brief Retreive the type and the UID of a STMicroelectronics contactless card.
\param[out] pKindOfCard The type of the card:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a STM_SR176</td><td>SR176 card.</td></tr>
<tr><td>\a STM_SRIX4K</td><td>SRIX4K card.</td></tr>
<tr><td>\a STM_SRIX512</td><td>SRIX512 card.</td></tr>
<tr><td>\a STM_SRI512</td><td>SRI512 card.</td></tr>
<tr><td>\a STM_SRI4K</td><td>SRI4K card.</td></tr>
<tr><td>\a STM_SRT512</td><td>SRT512 card.</td></tr>
</table>
\param[out] pUid The UID of the card. The buffer must be 8 bytes long.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_GetUid(unsigned char *pKindOfCard, unsigned char *pUid);

//! @}

//! \addtogroup TPassContactLessStmDetection
//! @{

/*! \brief Start the detection of a STMicroelectronics contactless card.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>One card is detected.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
<tr><td>\a CLSTM_NOCARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a CLSTM_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_27.c
*/
int ClessStm_DetectCard(unsigned int nTimeout);

//! @}

//! \addtogroup TPassContactLessStmDeactivation
//! @{

/*! \brief Deactivate a STMicroelectronics contactless card.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The card is deactivated.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_DeactiveCard(void);

//! @}

//! \addtogroup TPassContactLessStmMemoryOperations
//! @{

/*! \brief Read a 32 bits data from a STMicroelectronics contactless card.
\param[in] nAddress Address of the data.
\param[out] pByte1 Pointer to a byte that will receive the first byte of the 32 bits data.
\param[out] pByte2 Pointer to a byte that will receive the second byte of the 32 bits data.
\param[out] pByte3 Pointer to a byte that will receive the third byte of the 32 bits data.
\param[out] pByte4 Pointer to a byte that will receive the fourth byte of the 32 bits data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The block is read.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
\remarks This function does not work for <b>SR176</b> cards. Please use \ref ClessStm_ReadBlock16 instead.
*/
int ClessStm_ReadBlock32(unsigned char nAddress, unsigned char* pByte1, unsigned char* pByte2, unsigned char* pByte3, unsigned char* pByte4);

/*! \brief Read a 16 bits data from a STMicroelectronics SR176 contactless card.
\param[in] nAddress Address of the data.
\param[out] pByte1 Pointer to a byte that will receive the first byte of the 32 bits data.
\param[out] pByte2 Pointer to a byte that will receive the second byte of the 32 bits data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The block is read.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
\remarks This function only works for <b>SR176</b> cards. Please use \ref ClessStm_ReadBlock32 for others card type.
*/
int ClessStm_ReadBlock16(unsigned char nAddress, unsigned char* pByte1, unsigned char* pByte2);

/*! \brief Write a 32 bits data to a STMicroelectronics contactless card.
\param[in] nAddress Address of the data.
\param[in] nByte1 Value of the first byte of the 32 bits data.
\param[in] nByte2 Value of the second byte of the 32 bits data.
\param[in] nByte3 Value of the third byte of the 32 bits data.
\param[in] nByte4 Value of the fourth byte of the 32 bits data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The block is read.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
\remarks This function does not work for <b>SR176</b> cards. Please use \ref ClessStm_WriteBlock16 instead.
*/
int ClessStm_WriteBlock32(unsigned char nAddress, unsigned char nByte1, unsigned char nByte2, unsigned char nByte3, unsigned char nByte4);

/*! \brief Write a 16 bits data to a STMicroelectronics contactless card.
\param[in] nAddress Address of the data.
\param[in] nByte1 Value of the first byte of the 32 bits data.
\param[in] nByte2 Value of the second byte of the 32 bits data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The block is read.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
\remarks This function only works for <b>SR176</b> cards. Please use \ref ClessStm_WriteBlock32 for others card type.
*/
int ClessStm_WriteBlock16(unsigned char nAddress, unsigned char nByte1, unsigned char nByte2);

/*! \brief Write protect some of the memory blocks of a STMicroelectronics contactless card.
\param[in] nLockReg Bit field representing the blocks to lock.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The block is read.</td></tr>
<tr><td>\a CLSTM_NOT_SUPPORTED</td><td>The card does not support write protection.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_ProtectBlock(unsigned char nLockReg);

/*! \brief Retreive the write protection flag of a STMicroelectronics contactless card.
\param[out] pLockReg Pointer that will receive the bit field representing the locked blocks.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLSTM_OK</td><td>The block is read.</td></tr>
<tr><td>\a CLSTM_NOT_SUPPORTED</td><td>The card does not support write protection.</td></tr>
<tr><td>\a CLSTM_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessStm_GetBlockProtection(unsigned char* pLockReg);

//! @}

/////////////////////////////////////////////////////////////////

//! \addtogroup TPassContactLessCalypsoDriver
//! @{

/*! \brief Open the Innovatron Calypso contactless driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>The driver is opened.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCalypso_OpenDriver(void);

//! \brief Close the Innovatron Calypso contactless driver.
void ClessCalypso_CloseDriver(void);

/*! \cond NOT_DOCUMENTED
\brief Retrieve the Innovatron Calypso contactless driver handle if it has been opened by using fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCalypso_GetDriver(void);

//! \endcond

/*! \brief Change the task that owns of the Innovatron Calypso contactless driver.
\param[in] nNoTask The task number that will own the Innovatron Calypso driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCalypso_ChangeOwner(unsigned short nNoTask);

//! \brief Indicate if the Innovatron Calypso contactless driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
int ClessCalypso_IsDriverOpened(void);

/*! \cond NOT_DOCUMENTED
\brief Execute an Innovatron Calypso driver command.
\param[in] nCommand Command to execute.
\param[in] nData1 First parameter.
\param[in] nData2 Second parameter.
\param[in] nData3 Third parameter.
\param[in] nData4 Fourth parameter.
\return \a CLBP_xxx status code.
*/
int ClessCalypso_FormatCommand(unsigned char nCommand, unsigned int nData1, unsigned int nData2, unsigned int nData3, unsigned int nData4);

//! \endcond

/*! \brief Retreive the ATR of an Innovatron Calypso contactless card.
\param[out] pAtrLength Pointer that will receive the length of the ATR.
\param[out] pAtr Pointer to a buffer that will receive the ATR of the card. The buffer must be 27 bytes long (= \a SIZE_ATR_BP).
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCalypso_GetAtr(unsigned char *pAtrLength, unsigned char *pAtr);

//! @}

//! \addtogroup TPassContactLessCalypsoDetection
//! @{

/*! \brief Wait until an Innovatron Calypso contactless card is detected.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
<tr><td>\a CLBP_NOCARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a CLBP_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_28.c
*/
int ClessCalypso_DetectCard(unsigned int nTimeout);

//! @}

//! \addtogroup TPassContactLessCalypsoDisconnection
//! @{

/*! \brief Disconnect an Innovatron Calypso contactless card.
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>The card is deselected.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCalypso_Disconnect(unsigned int bWaitRemove);

//! @}

//! \addtogroup TPassContactLessCalypsoCommands
//! @{

/*! \brief Send a command to an Innovatron Calypso contactless card.
\param[in] pCommand Is the command to send to the card.
\param[in] nCommandLength Is the length of the command \a pCommand to be sent to the card.
\param[out] pResponse Will contain the card response.
\param[in,out] pResponseLength As input, it contains the size of the \a pResponse buffer.
As output, it contains the length of the card response \a pResponse. A card response cannot exceed 258 bytes (256 data bytes + SW1 and SW2).
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLBP_OK</td><td>The command is sent.</td></tr>
<tr><td>\a CLBP_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCalypso_Apdu(const void* pCommand, unsigned int nCommandLength, void* pResponse, unsigned int* pResponseLength);

//! @}


// ////////////////// ASK CTS smardcards ///////////////////////////////////////////////////
//! \addtogroup TPassContactLessCtsDriver
//! @{

/*! \brief Open the ASK CTS contactless driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>The driver is opened.</td></tr>
<tr><td>\a CLCTS_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCts_OpenDriver(void);

//! \brief Close the ASK CTS contactless driver.
void ClessCts_CloseDriver(void);

/*! \cond NOT_DOCUMENTED
\brief Retrieve the ASK CTS contactless driver handle if it has been opened by using fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLCTS_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCts_GetDriver(void);

//! \endcond

/*! \brief Change the task that owns of the ASK CTS contactless driver.
\param[in] nNoTask The task number that will own the ASK CTS contactless driver.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>The operation is successful.</td></tr>
<tr><td>\a CLCTS_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCts_ChangeOwner(unsigned short nNoTask);

//! \brief Indicate if the ASK CTS contactless driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
int ClessCts_IsDriverOpened(void);

/*! \cond NOT_DOCUMENTED
\brief Execute a ASK CTS contactless driver command.
\param[in] nCommand Command to execute.
\param[in] nData1 First parameter.
\param[in] nData2 Second parameter.
\param[in] nData3 Third parameter.
\param[in] nData4 Fourth parameter.
\return \a CLCTS_xxx status code.
*/
int ClessCts_FormatCommand(unsigned char nCommand, unsigned int nData1, unsigned int nData2, unsigned int nData3, unsigned int nData4);

//! \endcond

//! @}

//! \addtogroup TPassContactLessCtsCardDetection
//! @{

/*! \brief Start the detection of an ASK CTS contactless card.
\param[in, out] pCardType As input, specify the type of card that is waited (\a CL_ALLKINDS, \a CL_CTS_256 or \a CL_CTS_512).
As output, gives the type of the card detected (\a CL_CTS_256, \a CL_CTS_512 or \a CL_CTS_NO_CARD).
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>One card of valid type is detected.</td></tr>
<tr><td>\a CLCTS_KO</td><td>An error occurred.</td></tr>
<tr><td>\a CLCTS_NOCARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a CLCTS_TOOMANYCARDS</td><td>More than one card is found.</td></tr>
<tr><td>\a CLCTS_INVALIDCARD</td><td>A card is found but not of type asked.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_31.c
*/
int ClessCts_DetectCard(int *pCardType, int nTimeout);

/*! \brief Deselect an ASK CTS contactless card.
\details This function either power off the field or wait for card removal before powering off the field.
\param[in] nType  Type of deselection that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_CTS_DESELECT_DEFAULT</td><td>default behaviour is no REMOVAL mechanism and lowpower enable.</td></tr>
<tr><td>\a CL_CTS_DESELECT_REMOVAL</td><td>wait for card being removed from operating field.</td></tr>
<tr><td>\a CL_CTS_DESELECT_NO_LOWPOWER</td><td>during removal procedure do not shutdown the field between two detects.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>The card is deselected.</td></tr>
<tr><td>\a CLCTS_KO</td><td>An error occured.</td></tr>
</table>
*/
int ClessCts_Deselect(int nType);

//! @}

//! \addtogroup TPassContactLessCtsMemoryOperations
//! @{

/*! \brief Read one block (16 bits) of an ASK CTS contactless card.
\param[in] iAddress Address of the block.
\param[out] pData Pointer to a short that will receive the 16 data bits.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>Successful read.</td></tr>
<tr><td>\a PROTOCOL_ERROR</td><td>Error in protocol check.</td></tr>
<tr><td>\a TRANSMISSION_ERROR</td><td>Error in transmission, CRC noise...</td></tr>
<tr><td>\a TIME_OUT_ERROR</td><td>No response from the card.</td></tr>
</table>
*/
int ClessCts_Read(int iAddress, unsigned short* pData);

/*! \brief Read four consecutive blocks of an ASK CTS contactless card.
\param[in] iAddress Address of the first block.
\param[out] pData Pointer to a short buffer that will receive the 4 blocks (4*16 bits).
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>Successful read.</td></tr>
<tr><td>\a PROTOCOL_ERROR</td><td>Error in protocol check.</td></tr>
<tr><td>\a TRANSMISSION_ERROR</td><td>Error in transmission, CRC noise...</td></tr>
<tr><td>\a TIME_OUT_ERROR</td><td>No response from the card.</td></tr>
</table>
\remarks This function only works for <b>CTS 512</b> cards.
*/
int ClessCts_MultiRead(int iAddress, unsigned short* pData);

/*! \brief Write one data block (16 bits) to an ASK CTS contactless card.
 \details This function is able to perform all write operations
 (on CTS 256: ERASE and WRITE, on CTS 512: UPDATE and WRITE).
 The exact function behavior is set by \a iFlag parameter.

 When data integrity is enabled, up to 3 retries are done before the function fails, and the following operations are done:
 - on CTS 256: READ or ERASE, WRITE data, READ and verify data (3 card operations),
 - on CTS 512: READ data (case no erase), WRITE or UPDATE data and check command result with expected data (1 or 2 card operations).

\note Write operation is performed according to system bits. In order to update a CTS 512 counter, flag erase should be set in order to force an UPDATE low level operation.
\param[in] iAddress Address of the block.
\param[in] usData Value to write.
\param[in] iFlag Specify the behavior of the write (CL_CTS_W_DEFAULT or bitwise between CL_CTS_W_ERASE and CL_CTS_W_NOCHECK):
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_CTS_W_DEFAULT</td><td>make a WRITE without erase, check data integrity.</td></tr>
<tr><td>\a CL_CTS_W_ERASE</td><td>on CTS 256 start with an ERASE, on CTS 512 perform an UPDATE.</td></tr>
<tr><td>\a CL_CTS_W_NOCHECK</td><td>disable data integrity check (perform a write but do not care of value written).</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CLCTS_OK</td><td>Successful write.</td></tr>
<tr><td>\a CLCTS_KO</td><td>Data not consistent.</td></tr>
<tr><td>\a PROTOCOL_ERROR</td><td>Error in protocol check.</td></tr>
<tr><td>\a TRANSMISSION_ERROR</td><td>Error in transmission, CRC noise...</td></tr>
<tr><td>\a TIME_OUT_ERROR</td><td>No response from the card.</td></tr>
</table>
*/
int ClessCts_Write(int iAddress, unsigned short usData, int iFlag);

//! @}


//! \addtogroup TPassTeliumPassVendingPass
//! @{

/*! \brief Reset the TeliumPass+ or Vending Pass device.
\param[in] bHardReset Obsolete. Shall be set to \a FALSE.
\param[in] bWaitReset Indicate if the function shall wait for the end of the reset or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the end of the reset.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediatly.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_Reset:0x2D:0x0F                                            */
/* ------------------------------------------------------------------------ */
void TPass_Reset(int bHardReset, int bWaitReset);

#ifdef _UIRAM_H
/*! \brief Retrieve the diagnostics of the TeliumPass+ or Vending Pass device.
\param[out] pSpyData Last exception details.
\param[out] pDiagnostics The text diagnostics of length \ref TPASS_DIAGNOSTICS_SIZE.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref ERR_TPASS_OK</td><td>The diagnostics are retrieved.</td></tr>
<tr><td>\ref ERR_TPASS_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetDiagnostics:0x2D:0x14                                   */
/* @GSIM_A:1:ONE_POINTER                                                    */
/* @GSIM_A:1:OUT_ONLY                                                       */
/* @GSIM_A:2:DATA_SIZE(257)                                                 */
/* @GSIM_A:2:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetDiagnostics(spy_data_t* pSpyData, char* pDiagnostics);
#endif

//! @}

//! \addtogroup TPassComponents
//! @{

/*! \brief Retrieve information about a TeliumPass+ or Vending Pass software component.
\param[in] nIndex Index of the component. It can take values from 0 to the number of components minus 1.
\param[out] pInfo Information about the requested component. See \ref T_TPASS_COMPONENT_INFO for more information.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref ERR_TPASS_OK</td><td>The information are retrieved.</td></tr>
<tr><td>\ref ERR_TPASS_COMPONENT_NOT_FOUND</td><td>The component is not present (\a nIndex is out of range).</td></tr>
<tr><td>\ref ERR_TPASS_KO</td><td>An error occured.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_29.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetComponentInfoByIndex:0x2D:0x10                          */
/* @GSIM_A:2:ONE_POINTER                                                    */
/* @GSIM_A:2:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetComponentInfoByIndex(int nIndex, T_TPASS_COMPONENT_INFO* pInfo);

/*! \brief Retrieve information about a TeliumPass+ or Vending Pass software component.
\param[in] nType Type of the component:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_OS_RAM_LOADER</td><td>BOOT Ram. Shall not be present.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_OS_FLASH_LOADER</td><td>BOOT Flash.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_OS_SYSTEM</td><td>System.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_OS_SECURITY_FILE</td><td>Security description file.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_OS_HTERM_FILE</td><td>Hardware description file.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_OS_STERM_FILE</td><td>Software description file.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_APPLI</td><td>Application.</td></tr>
<tr><td>\ref TPASS_COMPONENT_TYPE_APPLI_FLASH_DATA</td><td>Application data file.</td></tr>
</table>
\param[out] pInfo Information about the requested component. See \ref T_TPASS_COMPONENT_INFO for more information.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref ERR_TPASS_OK</td><td>The information are retrieved.</td></tr>
<tr><td>\ref ERR_TPASS_COMPONENT_NOT_FOUND</td><td>The component is not present.</td></tr>
<tr><td>\ref ERR_TPASS_KO</td><td>An error occured.</td></tr>
</table>
\remarks Example:

//! \include Cless_LowLevel_Sample_30.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetComponentInfoByType:0x2D:0x11                           */
/* @GSIM_A:2:ONE_POINTER                                                    */
/* @GSIM_A:2:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetComponentInfoByType(int nType, T_TPASS_COMPONENT_INFO* pInfo);

/*! \brief Retrieve information about a TeliumPass+ or Vending Pass software component.
\param[in] ulBufferSize Size of the buffer \a pBuffer to be filled.
\param[out] pBuffer Buffer to be filled with the application components.<br>It is a concatenation of "<Label>\n<Version>\n<CRC>\n\n" for each application module.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref ERR_TPASS_OK</td><td>The versions are retrieved.</td></tr>
<tr><td>\ref ERR_TPASS_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetApplicationVersions:0x2D:0x23                           */
/* @GSIM_A:1:DATA_SIZE(ulBufferSize)                                        */
/* @GSIM_A:1:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetApplicationVersions (unsigned char * pBuffer, unsigned long ulBufferSize);

//! @}

//! \addtogroup TPassCapabilities
//! @{

/*! \brief Retrieve the TeliumPass+ or Vending Pass hardware capabilities.
\param[out] pHardCapabilities The hardware capabilities. See \ref T_TPASS_HARDWARE_CAPABILITIES for more information.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref ERR_TPASS_OK</td><td>The versions are retrieved.</td></tr>
<tr><td>\ref ERR_TPASS_COMPONENT_NOT_FOUND</td><td>The is no hardware description file in the reader.</td></tr>
<tr><td>\ref ERR_TPASS_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetHardwareCapabilities:0x2D:0x13                          */
/* @GSIM_A:1:ONE_POINTER                                                    */
/* @GSIM_A:1:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetHardwareCapabilities(T_TPASS_HARDWARE_CAPABILITIES* pHardCapabilities);

/*! \brief Retrieve the TeliumPass+ or Vending Pass software capabilities.
\param[out] pSoftCapabilities The software capabilities. See \ref T_TPASS_SOFTWARE_CAPABILITIES for more information.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\ref ERR_TPASS_OK</td><td>The versions are retrieved.</td></tr>
<tr><td>\ref ERR_TPASS_COMPONENT_NOT_FOUND</td><td>The is no software description file in the reader.</td></tr>
<tr><td>\ref ERR_TPASS_KO</td><td>An error occured.</td></tr>
</table>
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:TPass_GetSoftwareCapabilities:0x2D:0x12                          */
/* @GSIM_A:1:ONE_POINTER                                                    */
/* @GSIM_A:1:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
int TPass_GetSoftwareCapabilities(T_TPASS_SOFTWARE_CAPABILITIES* pSoftCapabilities);

//! @}

#endif // __CLESS_LOWLEVEL_H__INCLUDED__

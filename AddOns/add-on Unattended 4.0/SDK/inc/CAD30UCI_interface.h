#ifndef __CAD30UCI_INTERF_H__
#define __CAD30UCI_INTERF_H__

//! \defgroup UCI_DLL CAD30 UCI DLL
//! \brief This DLL provides functions in order to manage CAD30 UCI device.
//! \brief CAD30 UCI DLL allows to access to Inputs/Outputs CAD30 UCI device.
//! CAD30 UCI device is equiped with :
//!    - 2 push buttons.
//!    - 1 output.
//!    - 1 optional output.
//!    - 5 inputs.
//!
//! @{
//! \defgroup UCI_TYPEDEF				Typedef Definition
//! \defgroup UCI_GENERIC_FUNCTIONS	Generic Functions
//! \defgroup UCI_FUNCTIONS			UCI Functions
//! \defgroup UCI_ERROR_LIST			Error List Definition
//! \defgroup UCI_SAMPLE				Sample
//! @}


//! \addtogroup UCI_ERROR_LIST
//! @{
//! \brief UCI communication handle.

//! \brief The operation has been successfully processed.
#define _CAD30UCI_OK			0
//! \brief The operation has failed.
#define _CAD30UCI_KO			1
//! @}

//! \addtogroup UCI_TYPEDEF
//! @{
//! \brief Structures definitions.

//! \brief Struct used by POLL command.

//! This structure allows to retrieve CAD30 UCI inputs/outputs.
//! Alarms fields allows to know which inputs have been changed between 2 poll command
typedef struct
{
	char							cCmd ;      /*!< Must be set to 'p' (answer to Poll command) */
	unsigned char				ucWA ;      /*!< Warning alarm field.\n*/
                                       /*!< Equal to 31h if an alarm is set.\n */ 
                                       /*!< Equal to 30h if no alarm. */ 
	char							cReset ;    /*!< Reset field.\n*/
                                       /*!< Equal to 'h' if a hard reset occurs.\n*/ 
                                       /*!< Equal to 's' if a soft reset occurs.\n*/ 
                                       /*!< Equal to '0' if no alarm occurs since the last poll command.*/
	unsigned char				ucBp1 ;     /*!< Push button 1 alarm field.\n*/
                                       /*!< Equal to 31h if push buton has been pressed more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if push buton hasn't been pressed.*/  
	unsigned char				ucBp0 ;     /*!< Push button 0 alarm field.\n*/
                                       /*!< Equal to 31h if push buton has been pushed more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if push buton hasn't been pushed.*/
	unsigned char				ucI4 ;      /*!< Input 4 alarm field.\n*/
                                       /*!< Equal to 31h if input 4 has been shortcutted more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if input 4 hasn't been shortcutted.*/
	unsigned char				ucI3 ;      /*!< Input 3 alarm field.\n*/
                                       /*!< Equal to 31h if input 3 has been shortcutted more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if input 3 hasn't been shortcutted.*/
	unsigned char				ucI2 ;      /*!< Input 2 alarm field.\n*/
                                       /*!< Equal to 31h if input 2 has been shortcutted more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if input 2 hasn't been shortcutted.*/
	unsigned char				ucI1 ;      /*!< Input 1 alarm field.\n*/
                                       /*!< Equal to 31h if input 1 has been shortcutted more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if input 1 hasn't been shortcutted.*/
	unsigned char				ucI0 ;      /*!< Input 0 alarm field.\n*/
                                       /*!< Equal to 31h if input 0 has been shortcutted more than 50 ms since the last poll command.\n*/ 
                                       /*!< Equal to 30h if input 0 hasn't been shortcutted.*/
	unsigned char				ucLed ;     /*!< Yellow LED status.\n*/
                                       /*!< Equal to 31h LED is on.\n */ 
                                       /*!< Equal to 30h LED is off. */ 
	unsigned char				ucO1 ;      /*!< Output 1 status.\n*/
                                       /*!< Equal to 31h if output 1 is closed.\n */ 
                                       /*!< Equal to 30h if output 1 is opened. */ 
	unsigned char				ucO0 ;      /*!< Output 0 status.\n*/
                                       /*!< Equal to 31h if output 0 is closed.\n */ 
                                       /*!< Equal to 30h if output 0 is opened. */ 
	unsigned char				ucSbp1 ;    /*!< Push button 1 status.\n*/
                                       /*!< Equal to 31h if Push button 1 is pressed.\n */ 
                                       /*!< Equal to 30h if Push button 1 isn't pressed. */
	unsigned char				ucSbp0 ;    /*!< Push button 0 status.\n*/
                                       /*!< Equal to 31h if Push button 0 is pressed.\n */ 
                                       /*!< Equal to 30h if Push button 0 isn't pressed. */
	unsigned char				ucSi4 ;     /*!< Input 4 status.\n*/
                                       /*!< Equal to 31h if input 4 isn't shortcutted (pin out tension = 3.3V)\n */ 
                                       /*!< Equal to 30h if input 4 is shortcutted. */
	unsigned char				ucSi3 ;	   /*!< Input 3 status.\n*/
                                       /*!< Equal to 31h if input 3 isn't shortcutted (pin out tension = 3.3V)\n */ 
                                       /*!< Equal to 30h if input 3 is shortcutted. */
	unsigned char				ucSi2 ;     /*!< Input 2 status.\n*/
                                       /*!< Equal to 31h if input 2 isn't shortcutted (pin out tension = 3.3V)\n */ 
                                       /*!< Equal to 30h if input 2 is shortcutted. */
	unsigned char				ucSi1 ;     /*!< Input 1 status.\n*/
                                       /*!< Equal to 31h if input 1 isn't shortcutted (pin out tension = 3.3V)\n */ 
                                       /*!< Equal to 30h if input 1 is shortcutted. */
	unsigned char				ucSi0 ;     /*!< Input 0 status.\n*/
                                       /*!< Equal to 31h if input 0 isn't shortcutted (pin out tension = 3.3V)\n */ 
                                       /*!< Equal to 30h if input 0 is shortcutted. */
	unsigned char				ucEndFrame ;/*!< Must be set to 0Dh */
} S_Poll ;

//! \brief Struct used by INFORMATION command.

//! This structure allows to retrieve CAD30 UCI hardware and firmware versions.
typedef struct
{
	char							cCmd ;                     /*!< Must be set to 'i' (answer to INFORMATION command) */
	char                    tcHardwareVersion [ 5 ] ;  /*!< CAD30 UCI hardware version e.g. H0100 for Hardware version 1.00*/
	char							tcFirmwareVersion [ 5 ] ;  /*!< CAD30 UCI firmware version e.g. F0100 for Firmware version 1.00*/
	unsigned char				ucEndFrame ;               /*!< Must be set to 0Dh */
} S_Info ;
//! @}

//! \addtogroup UCI_GENERIC_FUNCTIONS
//! @{
//! \brief Functions to load, unload and get the version of the CAD30 UCI DLL.

//! \brief Load CAD30 UCI DLL.
//! \return
//!		- 0	The DLL has been successfully opened.
//!		- <>0 The DLL can not be opened.
int CAD30UCI_LibOpen ( void ) ;
//! \brief Unload CAD30 UCI DLL.
//! \return none
void CAD30UCI_LibClose ( void ) ;
//! \brief Version of the CAD30 UCI DLL.
//! \return Version as hex value e.g. 0x0100 for version 1.00.
int CAD30UCI_Version ( void ) ;
//! @}


//! \addtogroup UCI_FUNCTIONS
//! @{
//! \brief Functions dedicated to CAD30 UCI

//! \brief Open CAD30 UCI session.
//! \details Memory for the handle is allocated.
//! \return
//!	\ref _CAD30UCI_OK if connection established\n
//!	\ref _CAD30UCI_KO if connection failure
int CAD30UCI_Connect( void ) ;
//! \brief Close CAD30 UCI session
//! \details Memory for the handle is deallocated.
//! \return
//!	\ref _CAD30UCI_OK if disconnection done\n
//!	\ref _CAD30UCI_KO if disconnection failure
int CAD30UCI_Disconnect( void ) ;
//! \brief Retrieves data from CAD30 UCI device.
//! \param[out] psPollAns_p structure wich provides CAD30 UCI inputs/outputs states (see S_Poll structure for more informations).
//! \return
//!	\ref _CAD30UCI_OK if CAD30 UCI inputs/outputs are correctly read.\n
//!	\ref _CAD30UCI_KO if CAD30 UCI inputs/outputs reading failure.
int CAD30UCI_Poll ( S_Poll * psPollAns_p ) ;
//! \brief Allows to set ON/OFF CAD30 UCI led.
//! \param[in] ucLedState_p (31h = Led on, 30h = Led off).
//! \return
//!	\ref _CAD30UCI_OK command correctly executed.\n
//!	\ref _CAD30UCI_KO command failure.
int CAD30UCI_Set_Led ( unsigned char ucLedState_p ) ;
//! \brief Allows to open/close CAD30 UCI output.
//! \param[in] ucOutputNumber_p output number. Possible value output 0 = 0, output 0 = 1.
//! \param[in] ucState_p output state. Possible value 30h, 31h.  
//! \return
//!	\ref _CAD30UCI_OK command correctly executed.\n
//!	\ref _CAD30UCI_KO command failure.
int CAD30UCI_Set_Output ( unsigned char ucOutputNumber_p, unsigned char ucState_p ) ;
//! \brief CAD30 UCI software reset.
//! \return
//!	\ref _CAD30UCI_OK command correctly executed.\n
//!	\ref _CAD30UCI_KO command failure.
int CAD30UCI_Reset ( void ) ;
//! \brief CAD30 UCI versions informations.
//! \param[out] psInfo_p structure wich provides CAD30 UCI hardware and firmware versions (see S_Info structure for more informations).
//! \return
//!	\ref _CAD30UCI_OK command correctly executed.\n
//!	\ref _CAD30UCI_KO command failure.
int CAD30UCI_Information  ( S_Info * psInfo_p ) ;
//! @}

//! \addtogroup UCI_SAMPLE
//! @{
//! This example shows how to use CAD30 UCI DLL functions.
//! It can be copied in more_function entry point. It allows via a menu to access to CAD30 UCI inputs/outputs.
//! \include CAD30UCI_interface_Sample_01.c
//! @}

#endif /* __CAD30UCI_INTERF_H__ */

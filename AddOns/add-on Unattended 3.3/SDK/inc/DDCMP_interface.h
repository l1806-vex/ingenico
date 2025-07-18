#ifndef __DDCMP_INTERF_H__
#define __DDCMP_INTERF_H__

//! \defgroup DDCMP_DLL DDCMP DLL
//! \brief This DLL provides functions in order to manage the DDCMP protocol.
//!
//! This protocol is defined by <a href="http://www.vending-europe.eu/eva/home.html"> EVA </a>(European Vending Association) and described in the EVA Data Transfer Standard (EVA DTS) document.
//! \n It's a method of transferring data within a vending environment.

//! @{
//!  \defgroup DDCMP_TYPEDEF            Typedef Definition
//!  \defgroup DDCMP_GENERIC_FUNCTIONS  Generic Functions
//!  \defgroup DDCMP_FUNCTIONS          DDCMP Functions
//!  \defgroup DDCMP_LIST_NUMBER        DDCMP List Numbers Definition
//!  \defgroup DDCMP_ADDRESS_LIST       Device Address Values Definition
//!  \defgroup DDCMP_ERROR_LIST         Error List Definition
//!  \defgroup DDCMP_EXAMPLE            DDCMP Examples
//!  @{
//!    \defgroup DDCMP_EXAMPLE_AUDIT    Audit Collection Example
//!    \defgroup DDCMP_EXAMPLE_CONFIG   Configuration Example
//!  @}
//! @}

//! \addtogroup DDCMP_EXAMPLE_AUDIT
//! @{
//! This example shows how to acquire audit data generated by the slave device.
//! \include DDCMP_interface_Sample_01.c
//! @}

//! \addtogroup DDCMP_EXAMPLE_CONFIG
//! @{
//! This example shows how to update configuration settings of the slave device (like product prices).
//! \include DDCMP_interface_Sample_02.c
//! @}

//! \addtogroup DDCMP_TYPEDEF
//! @{
//! \brief DDCMP communication handle.
//! This handle is created by calling \ref DDCMP_Connect and released by calling \ref DDCMP_Disconnect.
typedef void* DDCMP_HANDLE;
//! @}

//! \addtogroup DDCMP_ERROR_LIST
//! @{
//! \brief Definition of all the error codes of the DDCMP functions.

//! \brief The operation has been successfully processed.
#define _DDCMP_OK			0
//! \brief The operation has failed.
#define _DDCMP_KO			1
//! \brief The operation has not been successfully processed. Retry the operation.
#define _DDCMP_RETRY		2
//! \brief Part of the operation has been successfully processed. Do the operation again to complete it.
#define _DDCMP_CONTINUE		3
//! \brief All the operation has been successfully processed.
#define _DDCMP_END			4
//! @}

// DDCMP Predefined address value (cf. EVA-DTS 6.0 �3.6.2.1 Table 4 )
//! \addtogroup DDCMP_ADDRESS_LIST
//! @{
//! \brief Definition of device addresses either reserved or defined by the DDCMP standard.
//!
//! Definition of Device Address Values can be found in chapter 3.6.2.1 of the EVA-DTS v6.1 document.

//! \brief slave device address = all device
#define _DDCMP_ALL_DEVICE				0x01
//! \brief slave device address = coin mechanism
#define _DDCMP_COINMECH					0x02
//! \brief slave device address = cashless system
#define _DDCMP_CASHLESS_SYSTEM			0x03
//! \brief slave device address = bill validator
#define _DDCMP_BILL_VALIDATOR			0x04
//! \brief slave device address = audit module
#define _DDCMP_AUDIT_MODULE				0x05
//! \brief slave device address = public cashless system
#define _DDCMP_PUBLIC_CASHLESS_SYSTEM	0x06
//! \brief slave device address = vending machine
#define _DDCMP_VENDING_MACHINE			0x07
//! @}


// DDCMP List Numbers (cf. EVA-DTS 6.0 �3.6.1.2 )
//! \addtogroup DDCMP_LIST_NUMBER
//! @{
//! \brief Definition of list numbers used to specify the type of read or write that is being carried out.
//!
//! Definition of DDCMP List Numbers can be found in chapter 3.6.1.2 of the EVA-DTS v6.1 document.

//! \brief Standard audit data only.
#define _DDCMP_AUDIT_COLLECTION_LIST		1
//! \brief Standard audit data is read without resetting the interim data (Read Only).
#define _DDCMP_SECURITY_READ_LIST			2
//! \brief All data (configuration and audit) contained in the control board.
#define _DDCMP_DEFAULT_OVERALL_DUMP_LIST	50
//! \brief Control board configuration data e.g. space to sales data.
#define _DDCMP_MACHINE_CONFIGURATION_LIST	64
//! @}

//! \addtogroup DDCMP_GENERIC_FUNCTIONS
//! @{
//! \brief Functions to load, unload and get the version of the DDCMP DLL.

//! \brief Load the DDCMP DLL.
//! \return
//! - 0 The DLL has been successfully opened.
//! - <>0 The DLL can not be opened.
int DDCMPlib_open( void );
//! \brief Unload the DDCMP DLL.
//! \return none
void DDCMPlib_close( void );
//! \brief Version of the DDCMP DLL.
//! \return Version as hex value e.g. 0x0103 for version 1.03.
int DDCMP_Version( void );
//! @}


//! \addtogroup DDCMP_FUNCTIONS
//! @{
//! \brief Functions dedicated to the DDCMP protocol

//! \brief Open the DDCMP session.
//! - details Memory for the handle is allocated.
//! - serial port is opened at 2400 (standard starting rate).
//! \param[in,out] io_p_Ctx Pointer on handle.
//! \param[in] i_puc_Com Name of the serial port (e.g. "COM0").
//! \param[in] i_ul_ComSpeed Baud Rate requested (e.g. 38400). Will be used during the link initialisation step.
//! \return
//! \ref _DDCMP_OK
int DDCMP_Connect( DDCMP_HANDLE *io_p_Ctx, unsigned char *i_puc_Com, unsigned long i_ul_ComSpeed );
//! \brief Close the DDCMP session
//! - details Memory for the handle is deallocated.
//! - serial port is closed.
//! \param[in,out] io_p_Ctx Handle of the session.
//! \return
//! none
void DDCMP_Disconnect( DDCMP_HANDLE io_p_Ctx );
//! \brief Initialise the DDCMP link.
//! \param[in,out] io_p_Ctx Handle of the session.
//! \param[in] i_uc_DeviceAddress Address of the slave device (see \ref DDCMP_ADDRESS_LIST).
//! \return
//! \ref _DDCMP_KO Link initialisation failed.
//! \ref _DDCMP_END Link initialisation is done.
//! \remarks The baudrate specified in function \ref DDCMP_Connect is taken into account if the slave unit (vending machine...) supports it. Otherwise, the baudrate stays at 2400.
int DDCMP_LinkInitialisation( DDCMP_HANDLE io_p_Ctx, unsigned char i_uc_DeviceAddress );
//! \brief Read data from the slave device.
//! \param[in,out] io_p_Ctx Handle of the session.
//! \param[in] i_uc_list_number Number of the list to read (see \ref DDCMP_LIST_NUMBER ).
//! \param[out] o_puc_data Data read.
//! \param[out] o_us_data_length Length of data read.
//! \return
//! \ref _DDCMP_KO         Data reading failed.
//! \ref _DDCMP_CONTINUE   Some data have been read. Call this function again to read the following data.
//! \ref _DDCMP_END        All the data have been read.
int DDCMP_ReadData( DDCMP_HANDLE io_p_Ctx, unsigned char i_uc_list_number, void **o_puc_data, unsigned short *o_us_data_length );
//! \brief Write data to slave device.
//! \param[in,out] io_p_Ctx Handle of the session.
//! \param[in] i_uc_list_number Number of the list to write (see \ref DDCMP_LIST_NUMBER ).
//! \param[in] i_puc_data Data to write.
//! \param[in] i_us_data_length Length of data to write.
//! \return
//! \ref _DDCMP_KO	Data writing failed.
//! \ref _DDCMP_END	Data writing succeed.
int DDCMP_WriteData( DDCMP_HANDLE io_p_Ctx, unsigned char i_uc_list_number, void *i_puc_data, unsigned short i_us_data_length );
//! \brief End communication.
//! \param[in,out] io_p_Ctx Handle of the session.
//! \return
//! \ref _DDCMP_OK	Communication ended.
//! \ref _DDCMP_KO	Communication was not ended.
int DDCMP_FinishCommunications( DDCMP_HANDLE io_p_Ctx );
//! @}

#endif /* __DDCMP_INTERF_H__ */

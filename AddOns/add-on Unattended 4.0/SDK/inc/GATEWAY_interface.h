#ifndef __GATEWAY_INTERF_H__
#define __GATEWAY_INTERF_H__


//! \defgroup GATEWAY_FUNCTION GATEWAY FUNCTIONS
//! \brief These functions manage the GATEWAY protocol, part of the MDB protocol.
//!
//! This protocol is defined by <a href="http://www.vending.org/"> NAMA </a>(National Automatic Merchandising Association) and described in section 8 (Communications gateway) of the MDB/ICP (Multi-Drop Bus/Internal Communication Protocol) document .

//! @{
//! \defgroup GATEWAY_GENERIC_FUNCTIONS	Generic Functions
//! \defgroup GATEWAY_FUNCTIONS			GATEWAY Functions
//! \defgroup GATEWAY_ERROR_LIST		Error List Definition
//! \defgroup GATEWAY_SAMPLE			GATEWAY Samples
//! @}


//! \addtogroup GATEWAY_ERROR_LIST
//! @{
//! \brief Definition of all the error codes of the GATEWAY functions.

//! \brief The operation has been successfully processed.
#define _GATEWAY_OK			0
//! \brief The operation has failed.
#define _GATEWAY_KO			1
//! \brief The operation has not been successfully processed. Retry the operation.
#define _GATEWAY_RETRY		2
//! \brief Part of the operation has been successfully processed. Do the operation again to complete it.
#define _GATEWAY_CONTINUE	3
//! \brief All the operation has been successfully processed.
#define _GATEWAY_END		4
//! @}

//! \addtogroup GATEWAY_GENERIC_FUNCTIONS
//! @{
//! \brief Functions to load and unload the MDB DLL.

//! \brief Load the MDB DLL.
//! \return
//!		- 0	The DLL has been successfully opened.
//!		- <>0 The DLL can not be opened.
int GATEWAYlib_open( void );
//! \brief Unload the MDB DLL.
//! \return none
void GATEWAYlib_close( void );
//! @}

//! \addtogroup GATEWAY_FUNCTIONS
//! @{
//! \brief Functions dedicated to the GATEWAY protocol

//! \brief Open the audit session.
//! \param[in] i_uc_list_number Number of the list to read.
//! \return
//!	\ref _GATEWAY_OK The audit session has been opened.
//! \n \ref _GATEWAY_KO The audit session can not be opened.
int Gateway_LaunchAudit( unsigned char i_uc_list_number );
//! \brief Read data from the VMC (vending data controller).
//! \param[out] o_puc_data Data read.
//! \param[out] o_us_data_length Length of data read.
//! \return
//!	\ref _GATEWAY_CONTINUE Data are not yet fully read. Wait a little and call this function again.
//!	\n \ref _GATEWAY_END All the data have been read.
//! \n \ref _GATEWAY_KO Data reading failed.
//! \remarks Memory for the data will be automatically allocated at the beginning of data reception.
int Gateway_ReadData( void **o_puc_data, unsigned short *o_us_data_length );
//! \brief End the audit session.
//! \return
//!	\ref _GATEWAY_OK This audit session is ended.
//! \remarks Memory for the data read will be deallocated here.
int Gateway_EndAudit( void );
//! @}

//! \addtogroup GATEWAY_SAMPLE
//! @{
//!
//! This sample shows how to acquire audit data using GATEWAY protocol.
//! \include GATEWAY_interface_Sample_01.c
//! @}

#endif /* __GATEWAY_INTERF_H__ */

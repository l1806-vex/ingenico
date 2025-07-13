/**
 * \file
 * \brief Define the high level interface of the AUDIT Component.
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

#ifndef __AUDIT_INTERF_H__
#define __AUDIT_INTERF_H__

//! \defgroup AUDIT_CMP	AUDIT component
//! @{
//!   \defgroup AUDIT_OVERVIEW Overview of Audit
//!   \defgroup AUDIT_RECORD Description of records
//!   \defgroup AUDIT_COMMUN_FUNCTIONS	General Functions
//!   \defgroup AUDIT_APPLI_FUNCTIONS	Audit Application Functions
//!   \defgroup AUDIT_MULTI_FUNCTIONS	Behaviour of Multi-Audit Applications
//! @}

// Groupe commun a "General functions" et "Audit application functions"
//! \defgroup AUDIT_ERRORS Error list
//! @{
//! \brief OK. The operation has been successfully processed.
#define _AUDIT_OK                  0
//! \brief internal error.
#define	_AUDIT_ERROR              -1
//! \brief internal error.
#define	_AUDIT_UNDEFINED          -2
//! \brief AUDIT services not available (using AUDIT_Start_Services by the audit application)
#define	_AUDIT_UNAVAILABLE        -3
//! \brief parameters not valid. check parameters
#define _AUDIT_INVALID_PARAMETERS -4
//! \brief The audit file is full. It shall be read by the audit application. Some records may be lost
#define _AUDIT_OVERFLOW           -5
//! \brief internal error. Memory can't be allocated
#define _AUDIT_OUT_OF_MEMORY      -6
//! \brief internal error. The audit file is corrupted
#define _AUDIT_CORRUPTED          -7
//! \brief End of file. No more data to read
#define _AUDIT_EOF                -8
//! \brief No backup file exists.( returned only by AUDIT_File_Exist)
#define _AUDIT_NOT_EXIST          -9
//! \brief The function is not allowed.( returned only with multi audit application behaviour)
#define _AUDIT_NOT_ALLOWED       -10
//! @}


// Groupe commun a "General functions" et "Audit application functions"
//! \defgroup AUDIT_DEF_TYPE	Record types
//! \brief This parameter is the type of the record. This type is provided by the application or module who add the record. It is used by the audit application to filter records.
//! @{
#define RECORD_TYPE_PAYMENT   0x0001 /*!< Flag for payment records*/
#define RECORD_TYPE_INFO      0x0002 /*!< Flag for information records (application initialisation, deletion ...)*/
#define RECORD_TYPE_ALARM     0x0004 /*!< Flag for alarm record (critical event occured ...)*/
#define RECORD_TYPE_PROTOCOL  0x0008 /*!< Flag for protocol record (events from EXE, MDB ...)*/
#define RECORD_TYPE_USER      0x0010 /*!< Flag for user record (defined by vars)*/
#define RECORD_TYPE_ALL       0xFFFF /*!< all records --> use only with AUDIT_Get_Stats */
//! @}

//! \defgroup AUDIT_DEF_OPTION	Reading options 				
//! @{
#define	OPTION_NONE           0 /*!< no option */
#define	OPTION_SEEK_0         1 /*!< restart reading from beginning */
#define	OPTION_FILTER_TYPE    2 /*!< filter record by types (one or several)*/
//! @}

//-- Functions --------------------------------------------------
//! \addtogroup AUDIT_COMMUN_FUNCTIONS
//! \brief These functions can be used by all protocol modules, financial applications...
//! @{
//! \addtogroup AUDIT_ERRORS
//! \addtogroup AUDIT_DEF_TYPE

//! \brief Add one Audit record (could be used by all protocol modules, financial applications... ) --> \ref AUDIT_RECORD.
//! \param[in] usType_p	type of the record ( \ref AUDIT_DEF_TYPE).
//! \param[in] iSize_p size of the record <b>(max 1024 bytes) </b>.
//! \param[out] pcData_p record data.
//! \return
//! - \ref _AUDIT_OK  The record is stored.
//! - \ref _AUDIT_UNAVAILABLE  The audit application didn't start the Audit services or the audit application isn't loaded
//! - \ref _AUDIT_OVERFLOW The audit file is full, the record is not stored.
//! - errors... (see : \ref AUDIT_ERRORS ).
//! \note The application or modules should not test the return. A terminal could work with or without audit application.
//! 
//! <h3>Example: (add a record with type RECORD_TYPE_PAYMENT, selection number=2, selection price=100cts )</h3>
//! \include AUDIT_interface_Sample_01.c
extern int AUDIT_Add_Record(unsigned short usType_p,	int iSize_p,	char *pcData_p );
//! @}

//! \addtogroup AUDIT_APPLI_FUNCTIONS
//! \brief Those functions are used by the audit application
//! @{
//! \addtogroup AUDIT_ERRORS
//! \addtogroup AUDIT_DEF_TYPE
//! \addtogroup AUDIT_DEF_OPTION

//! \brief struct set by AUDIT_Get_Stats
typedef struct
{
	unsigned long ulStored;					/*!< provide the record number*/
	unsigned long ulStoredSize;				/*!< provide the record size (bytes)*/
	unsigned long ulFailed;					/*!< provide the lost record number*/
	unsigned long ulFailedSize;				/*!< provide the lost record size (bytes)*/
}T_AUDIT_STAT;
//! \brief Start the audit services. The records are stored.
//! \return
//! - \ref _AUDIT_OK no error.
//! - errors... (see : \ref AUDIT_ERRORS )
//! \note \ref AUDIT_Start_Services is called in the after reset of the audit application. If no application calls AUDIT_Start_Services, the records are not stored
extern int AUDIT_Start_Services(void);
//! \brief Stop the audit services. The records are deleted and will not be stored.
//! \return
//! - \ref _AUDIT_OK no error.
//! - errors... (see : \ref AUDIT_ERRORS )
extern int AUDIT_Stop_Services(void);
//! \brief Get the Audit component status (available, audit file full...).
//! \return
//! - \ref _AUDIT_OK  no error and the application shall read the next block
//! - \ref _AUDIT_OVERFLOW  The current file is full. The new records are lost.
//! - \ref _AUDIT_UNAVAILABLE  The audit application didn't start the Audit services or the audit application isn't loaded
//! - errors... (see : \ref AUDIT_ERRORS ).
extern int AUDIT_Is_Available(void);
//! \brief Get the Audit component version.
//! \return
//! - ie. 203 = component version 02.03
extern int AUDIT_Get_Version( void);
//! \brief Get the current audit file size
//! \note This service has to be used before AUDIT_Read_File routine in order to estimate the data size to be read and to copy data too often. 
extern int AUDIT_Get_Size(void);
//! \brief Read the Audit File by block
//! \param[in] usOption_p (\ref AUDIT_DEF_OPTION)
//! - \ref OPTION_NONE no specific option
//! - \ref OPTION_SEEK_0 to restart the reading from beginning
//! \param[in,out] piSize_p (pointer)
//! in input, provide to the audit component the output buffer size pcData_p <b>(max bloc size = 1024)</b>.
//! in out, provide to the application the read data size pcData_p
//! \param[out] pcData_p ouptut buffer.
//! \return
//! - \ref _AUDIT_OK  no error and the application shall read the next block
//! - \ref _AUDIT_EOF  no error and the reading is terminated
//! - errors... (see : \ref AUDIT_ERRORS ).
//! \note \ref AUDIT_Read_File has to be called several times until return \ref _AUDIT_EOF. When this function is called, the current audit file is moved to backup audit file. The current audit file is deleted and the audit application works on backup audit file. The blocks contain entire records. A record is never segmented into 2 blocks.
//! \warning If the terminal restarts during \ref AUDIT_Read_File service is running, the reading will restart from the beginning of the file. 
//! <h3>Example:</h3>
//! \include AUDIT_interface_Sample_02.c
extern int AUDIT_Read_File( unsigned short usOption_p,	int *piSize_p,	char * pcData_p);
//! \brief Read the Audit File by record.
//! \param[in] usOption_p (\ref AUDIT_DEF_OPTION)
//! - \ref OPTION_NONE no specific option.
//! - \ref OPTION_SEEK_0 to restart the reading from beginning.
//! - \ref OPTION_FILTER_TYPE to active a filter. The types read are set in *pusType_p parameters.
//! \param[out] pusNo_p provide the record ID. this ID is the circular record counter and automaticaly managned by the component. max value 65535. 
//! \param[in,out] pusType_p (\ref AUDIT_DEF_TYPE)
//! In input (if the option \ref OPTION_FILTER_TYPE is set), provide to the component the value of filter. Several types could be set (\ref RECORD_TYPE_PAYMENT|\ref RECORD_TYPE_PROTOCOL for ex)
//! In out, provide to the application the value of the type
//! \param[in,out] piSize_p (pointer)
//! In input, provide to cmp the output buffer size pcData_p
//! In out, provide to application the read data size pcData_p
//! \param[out] pcData_p ouptut record.
//! \return
//! - \ref _AUDIT_OK  no error and the application shall read the next block
//! - \ref _AUDIT_EOF  no error and the reading is terminated
//! - errors... (see : \ref AUDIT_ERRORS )
//! \note \ref AUDIT_Read_Record has to be called several times until return \ref _AUDIT_EOF. When this function is called, the current audit file is moved to backup audit file. The current audit file is deleted and the audit application works on backup audit file.
//! \warning If the terminal restarts during \ref AUDIT_Read_File service is running, the reading will restart from the beginning of the file.  
//! <h3>Example:</h3>
//! \include AUDIT_interface_Sample_03.c
extern int AUDIT_Read_Record( unsigned short  usOption_p,unsigned short * pusNo_p, unsigned short *pusType_p, int * piSize_p, char * pcData_p);	
//! \brief Get information about backup file (number of records, size..).
//! \param[in] usType_p .
//! set \ref RECORD_TYPE_ALL to get informations about all records. To get only information about one or severals type (ie number of payment records ), use the requested types.
//! \param[in] iSize_p size of the struct pStat_p  = sizeof( \ref T_AUDIT_STAT).
//! \param[out] pStat_p pointer on output struct \ref T_AUDIT_STAT.
//! \return
//! - \ref _AUDIT_OK  no error and the application shall read the next block
//! - errors... (see : \ref AUDIT_ERRORS )
//! \note The statistics are reseted at the creation of AUDIT file.
//! \warning ulFailed and ulFailedSize are not null when audit application doesn’t read the audit file fairly quickly.
extern int AUDIT_Get_Stats( unsigned short usType_p,	int iSize_p,	T_AUDIT_STAT * pStat_p);	
//! \brief Delete the backup file.
//! \return
//! - \ref _AUDIT_OK no error.
//! - errors... (see : \ref AUDIT_ERRORS )
//! \note \ref AUDIT_Delete_File shall be call after the audit file reading. However, it must not be called if the reading is done from the entry point \ref SERVICE_AUDIT_FILE_DELETION_ID 
extern int AUDIT_Delete_File(void);
//! \brief Inform that the backup audit file exists.
//! \return
//! - \ref _AUDIT_OK  The backup file exists. The audit file was read but wasn't be deleted.
//! - \ref _AUDIT_NOT_EXIST  The backup file does't exist. nomimal behaviour.
//! - errors... (see : \ref AUDIT_ERRORS )
extern int AUDIT_File_Exist(void);
//! \brief Wake up the audit application when the component receives one record.
//! \param[in] usType_p To set the types which wake up the audit application (one or several type are possible). if usType_p==0, the wakeup is disabled.
//! \return
//! - \ref _AUDIT_OK  no error
//! - \ref _AUDIT_INVALID_PARAMETERS  if \ref SERVICE_AUDIT_WAKE_UP_ID is not registred by the calling application.
//! - errors... (see : \ref AUDIT_ERRORS )
//! \note Only one audit application can use this service. it doesn't work with "multi audit appli" behaviour. The application entry point is called even if the record can't be stored (file full..).
extern int AUDIT_Set_WakeUp( unsigned short usType_p);	
//! \brief Audit wake up entry point --> entry point parameters (unsigned int uiSize_p, unsigned char *pRecordData_p)
//! \brief The Audit Application shall use \ref AUDIT_Set_WakeUp to register the wake up record types
//! \brief The Audit Application MUST NOT use terminal ressources (screen, keyboard,communication) when it is called from this event. 
//! \brief It must do the processing very quickly.
//! \brief It must not call audit functions (else it causes dead lock).
//! \note SERVICE_AUDIT_WAKE_UP_ID can be registred by only one audit application. It doesn't work in "multi audit appli" behaviour.
//! \warning max value of uiSize_p =1024. The application mustn't cause a terminal reset if it receives a record data size = 1024.
#define SERVICE_AUDIT_WAKE_UP_ID	0x1301
//! @}

//! \addtogroup AUDIT_MULTI_FUNCTIONS
//! \brief Several audit applications could sometimes be loaded in one terminal. In this configuration, the audit application must follow some rules for operating correctly and not losing some records...
//! \brief "multi audit appli" behaviour is not the nominal behaviour and should be used carefully. If you want to use this entry point, please contact technical support.
//! <br><br><h2> Overview </h2>
//! Therefore, the audit file reading has to be shared.
//! The first audit Application that reads the audit file, deletes the file when it calls the service \ref AUDIT_Delete_File.
//! The other audit Applications want to read the file before deletion.
//!
//! To be informed, the audit applications have to register the entry point \ref SERVICE_AUDIT_FILE_DELETION_ID.
//! (This entry point is registered when the application is called on give_interface)
//! Then, they will be called before the file deletion.
//! 
//! <br><h2>Restrictions</h2>
//! The audit application must only :
//! - use services \ref AUDIT_Read_File, \ref AUDIT_Read_Record or \ref AUDIT_Get_Stats to read or copy the audit file. 
//! quickly realize the processing.
//! 
//! When it is called on the entry point \ref SERVICE_AUDIT_FILE_DELETION_ID, The audit application must not:
//! - use the display or keyboard;
//! - call a distant host;
//! - call the service \ref AUDIT_Delete_File at the process end.
//! - call use ressources in general.
//! <br>
//!
//! It can not:
//! - Stop the file deletion.  The return values should not be checked.
//! <br>
//!
//! <h2>Notes</h2>
//! - The audit application that has called iAUDIT_Delete_File is not called on the entry point \ref SERVICE_AUDIT_FILE_DELETION_ID;
//! - The reading and filtering are reset at each call;
//! - iAUDIT_Get_Size returns the AUDIT.DIA file size and return 0 because the application works automatically with the backup file.\n The application should use AUDIT_Get_Stats to get  the backup file size;
//! - Implementation rules:
//! The audit application hasn’t only to wait for \ref SERVICE_AUDIT_FILE_DELETION_ID to read audit file.
//! It could be loaded alone in the terminal and then \ref SERVICE_AUDIT_FILE_DELETION_ID will never be called.

//! @{
//! \brief Audit file deletion enty point (multi appli audit behaviour) --> entry point parameters (0,NULL)
//! \brief "multi audit appli" behaviour is not the nominal behaviour and should be used carefully.
//! \brief If you want to use this entry point, please contact technical support.
#define SERVICE_AUDIT_FILE_DELETION_ID	0x1300
//! @}


//! \addtogroup AUDIT_OVERVIEW
//! \brief The audit component manages an audit file (creation, read, write, delete…).\n The audit file is filled by payment applications or the protocol DLL. It is read by the custom audit application. For that, the audit component has to give services to allow it.
//! <h2>Principle</h2>
//! When an application or a protocol DLL wants to add an audit record in the file, it must use of audit component’s services. These services are supplied by the library AUDIT.LIB.\n\n
//! The added records are stored in a file (audit file) managed by the AUDIT component.\n
//! The file size is 30 K bytes.\n\n
//! The AUDIT application must read audit file regularly in order to empty it.\n
//! It is the responsibility of the AUDIT application to empty the audit file before it is full.\n
//! To be done, AUDIT applications use services (size, reading, removal of the file) provided by AUDIT component.\n
//! <b>If audit file is full, it is not possible to add an other record.</b>\n\n
//! An error is returned to the application or protocol DLL which wants to add a record.\n
//! A Service supplies the number and the type of lost records.\n
//!
//! <h2>Architecture</h2>
//! @image html Audit1.jpg
//! <h2>File Creation</h2>
//! At each AfterReset, the AUDIT application activates audit management by means of services.\n
//! At the first activation, the AUDIT COMPONENT creates its disk and its environment.\n
//! While the service is not activated, the AUDIT COMPONENT doesn’t store audit records provided by applications and DLLs.\n An error is returned when audit services are called.\n
//!
//! <h2>File Management</h2>
//! The AUDIT COMPONENT creates F_AUDIT_CMP disk.\n
//! The AUDIT COMPONENT stores the events in AUDIT.DIA file. It uses, temporarily, AUDIT.BKP file in order to put at disposal to AUDIT CUSTOM application the records.\n
//! The file STAT.DIA is associated with AUDIT.DIA file. This file describes the number of records, the size of all records stored or lost. It is renamed at the same time as AUDIT.DIA file.\n
//! \n
//! When AUDIT CUSTOM application requires the reading of the audit file, the AUDIT COMPONENT realizes the following operations.\n
//! -	If AUDIT.BKP file doesn’t exist:
//! - Rename file AUDIT.DIA in AUDIT.BKP.
//! - Rename file STAT.DIA in STAT.BKP
//! - A new AUDIT.DIA file is created.
//! - A new STAT.DIA file is created and initialised to 0.
//! - Data of AUDIT.BKP file are provided to the calling routine.
//! - The data of STAT. BKP are placed at the disposal.
//! - If the file AUDIT.BKP exits, its content is provided to the calling routine.
//!
//! \n
//! The accesses are protected. Therefore the applications, DLLs and AUDIT application are able to access at the same time to the file.
//!
//! \note The Audit application, which requires the reading, must require the removal of the file at the end of its treatment.
//!
//! @{
//! @}

//! \addtogroup AUDIT_RECORD
//! <h2>Description</h2>
//! The audit file is made up of ASCII format records. The field separator character is *.\n
//! The characters CRLF (0xD 0x0A) terminate the record.\n
//! The AUDIT COMPONENT does not check the record format. Applications and DLLs must respect the format.\n
//! A record is composed of a header (made up of 7 fields) and variables data fields.\n
//! A VAR application will be able to define new types of recordings by respecting the heading.\n
//!
//! <h2>Header record </h2>
//! The header is composed of following fields:\n
//! <table>
//! <tr><th>Fields</th><th>Length (byte)</th><th>Format</th><th>Description</th></tr>
//! <tr><td>Record type</td><td>Variable</td><td>ASCII</td><td>Define the record type</td></tr>
//! <tr><td>Date</td><td>6</td><td>ASCII</td><td>Date of Event YYMMDD</td></tr>
//! <tr><td>Time</td><td>6</td><td>ASCII</td><td>Time of HHMMS </td></tr>
//! <tr><td>Issue number</td><td>Variable</td><td>Hexa coded ASCII</td><td>Application number, which generates the event</td></tr>
//! <tr><td>Event number</td><td>Variable</td><td>ASCII</td><td>Signle number, which allows to diversify a field "record type"</td></tr>
//! <tr><td>Event type</td><td>Variable</td><td>ASCII</td><td>Define the event type</td></tr>
//! <tr><td>Length</td><td>Variable</td><td>ASCII</td><td>Data size (bytes) with separators *</td></tr>
//! </table>
//! The fields of the header are mandatory. ** means that the field is not initialized and empty.
//! <h2>Data fields zone </h2>
//! The data field zone is \b variable.\n The following array describes each data field according to the field [Record type].\n Each application or DLL can add specific fields.\n\n
//! <table>
//! <tr><th>Record Type</th><th>Date<th></th>Time<th></th>Issue Number<th></th>Event number<th></th>Event type<th></th>Length (byte)</th><th>DATA</th><th>...</th></tr>
//! <tr><td>1 : payment/revalue</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>1 : payment succeded</td><td>1:card\n 2:cash</td><td>99</td><td>Selection number</td><td>Amount</td></tr>
//! <tr><td>1 : payment/revalue</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>2 : payment failed</td><td>1:card\n 2:cash</td><td>99</td><td>Selection number</td><td>Amount</td></tr>
//! <tr><td>1 : payment/revalue</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>3 : revalue card</td><td>1:coin\n 2:bill\n 3:Card</td><td>99</td><td>Amount of credit</td><td></td></tr>
//! <tr><td>1 : payment/revalue</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>4 : cancel</td><td>1:card\n 2:cash\n</td><td>99</td><td>Selection number</td><td>Amount</td></tr>
//! <tr><td>2 : Event</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>1 : alarm</td><td>Indicate here the alarm number</td><td>99</td><td>Alarm level(*)</td><td></td></tr>
//! <tr><td>2 : Event</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>2 : file management</td><td>(**)</td><td>99</td><td>(**)</td><td>(**)</td></tr>
//! <tr><td>2 : Event</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>3 : application</td><td>(**)</td><td>99</td><td>(**)</td><td>(**)</td></tr>
//! <tr><td>2 : Event</td><td>YYMMDD</td><td>HHMMSS</td><td>XXXX</td><td>4 : Protocol DLL</td><td>DLL event type:\n 1 : Communication enable\n 2: Incident\n 3:Settings\n 4:cash flow</td><td>99</td><td>DLL DATA 1(***)</td><td>DLL DATA2(***)</td></tr>
//! <tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
//! </table>
//! (*) Alarm level goes from 0 to 9 (0=low, 9=high). 1 byte formatted in hexadecimal coded ASCII.\n
//! (**) Each application manages its own events types or Data.\n
//! (***) See description of DLL DATA\n
//! 
//! <h2>Description of DLL DATA</h2>
//! <h3>Event type 1 : Communication enable</h3>
//! <table>
//! <tr><th></th><th>DATA 1</th><th> DATA 2</th><th>Available with EXE</th><th>Available with MDB</th></tr>
//! <tr><td>DLL communication enable</td><td>0</td><td>0</td><td>YES</td><td>YES</td></tr>
//! </table>
//!
//! <h3>Event type 2 : Incident</h3>
//! <table>
//! <tr><th></th><th>DATA 1</th><th> DATA 2</th><th>Available with EXE</th><th>Available with MDB</th></tr>
//! <tr><td><i>CashLess is disabled</i></td></tr>
//! <tr><td>The VMC inhibits Cashless</td><td>1</td><td>1</td><td>YES</td><td>YES</td></tr>
//! <tr><td>The VMC mode is Free vend</td><td>1</td><td>2</td><td>YES</td><td>NO</td></tr>
//! <tr><td>Reset requested by the VMC</td><td>1</td><td>3</td><td>NO</td><td>YES</td></tr>
//! <tr><td><i>Communication is lost, VMC is mute</i></td></tr>
//! <tr><td>The VMC doesn’t poll the cashless (CAD30)</td><td>0</td><td>0</td><td>NO</td><td>YES</td></tr>
//! <tr><td>The VMC never sends byte (check the link)</td><td>2</td><td>0</td><td>YES</td><td>NO</td></tr>
//! <tr><td>The communication is lost during the processing</td><td>3</td><td>0</td><td>YES</td><td>NO</td></tr>
//! <tr><td><i>Incident during vend</i></td></tr>
//! <tr><td>The Coin selector doesn’t answer during vend processing</td><td>4</td><td>2</td><td>YES</td><td>NO</td></tr>
//! <tr><td>The VMC doesn’t send vend response</td><td>4</td><td>3</td><td>YES</td><td>NO</td></tr>
//! <tr><td>The VMC keep inhibited state after vend</td><td>4</td><td>5</td><td>YES</td><td>NO</td></tr>
//! </table>
//!
//! <h3>Event type 3 : Settings</h3>
//! <table>
//! <tr><th></th><th>DATA 1</th><th> DATA 2</th><th>Available with EXE</th><th>Available with MDB</th></tr>
//! <tr><td>The Application provides to the DLL its operational settings </td><td>0</td><td>0</td><td>YES</td><td>YES</td></tr>
//! <tr><td>The Application inhibits DLL (Communication with VMC is OFF)</td><td>1</td><td>0</td><td>YES</td><td>YES</td></tr>
//! </table>
//!
//! <h3>Event type 4 : Cash Flow</h3>
//! <table>
//! <tr><th></th><th>DATA 1</th><th> DATA 2</th><th>Available with EXE</th><th>Available with MDB</th></tr>
//! <tr><td>Communication with cash flow is OK and exact change flag is off. </td><td>0</td><td>1</td><td>YES</td><td>NO</td></tr>
//! <tr><td>No communication with cash flow (cash flow doesn't poll the cashless. </td><td>0</td><td>2</td><td>YES</td><td>NO</td></tr>
//! <tr><td>Communication with cash flow is OK and exact change flag is on.</td><td>0</td><td>3</td><td>YES</td><td>NO</td></tr>
//! </table>
//!
//! <h2>MDB and cash transactions</h2>
//! In MDB configuration, the terminal (CAD30) is slave.\n
//! A cash transaction will be recorded only if the MDB master informs it.\n
//! This command is mandatory but some MDB Masters don’t respect it.\n
//!
//! <h2>Samples of Records</h2>
//! - revalue with 1 EUR coin :\n
//! 1*070312*154125*006E*3*1*4*100CRLF\n
//! \n
//! - 0.30 EUR card payment, selection 4:\n
//! 1*070312*154225*006E*1*1*5*4*30CRLF\n
//! \n
//! - 0.40 EUR card payment (VMC price):\n
//! 1*070312*154325*006E*1*1*4**40CRLF\n
//! \n
//! - Creation file alarm:\n
//! 2*070312*154425*006E*2*1*2*1CRLF\n
//! \n
//! - Communication lost with VMC\n
//! 2*070312*154425*0012*4*2*4*0*0CRLF\n
//! \n
//! - Communication enable with VMC\n
//! 2*070312*154425*0012*4*1*4*0*0CRLF\n
//! 
//! @{
//! @}

#endif /* __AUDIT_INTERF_H__ */

/**
* \file EmvEngineInterface.h
* \brief This module contains the definitions of EMV custom services.
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

#ifndef EMV_ENGINE_INTERFACE_H
#define EMV_ENGINE_INTERFACE_H

//! \defgroup Group_EmvEngineInterface EMV custom services definitions.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define I_EMVCUST_Type_Appli						(0x51)					//!< Custom application type.

/*#define I_EMVCUST_Initialise						(100)
#define I_EMVCUST_Get_Global_Param					(101)
#define I_EMVCUST_Get_AID_List						(102)
#define I_EMVCUST_Get_AID_DATA						(103)
#define I_EMVCUST_Get_AID_Param						(104)
#define I_EMVCUST_More_Function						(105)
#define I_EMVCUST_Periodic_Call						(106)
#define I_EMVCUST_Process_Step						(107)
#define I_EMVCUST_Display_Message					(108)
#define I_EMVCUST_Get_Last_Transaction				(109)
//#define I_EMVCUST_Last_Transaction_Status				(110)
//#define I_EMVCUST_Get_Data_Elements					(111)
//#define I_EMVCUST_Set_Data_Elements					(112)
#define I_EMVCUST_Voice_Referral					(113)
#define I_EMVCUST_Get_AID							(114)
#define I_EMVCUST_KeyManagement						(115)
#define I_EMVCUST_Authorisation						(116)
#define I_EMVCUST_Choose_Language_Menu				(117)
#define I_EMVCUST_Menu_Select						(118)
#define I_EMVCUST_Choose_Account_Type_Menu			(119)
*/
#define I_EMVCUST_Perform_Transaction				(120)					//!< Engine entry point perform transaction.
/* #define I_EMVCUST_Get_AID_ICS						(121)*/

#define I_EMVCUST_Initialise_TlvTree				(200)					//!< Manager entry point initialise.
#define I_EMVCUST_Get_Global_Param_TlvTree			(201)					//!< Engine entry point get global param.
#define I_EMVCUST_Get_AID_List_TlvTree				(202)					//!< Engine entry point get AID list.
#define I_EMVCUST_Get_AID_DATA_TlvTree				(203)					//!< Engine entry point get AID Data.
#define I_EMVCUST_Get_AID_Param_TlvTree				(204)					//!< Engine entry point get AID Param.
#define I_EMVCUST_More_Function_TlvTree				(205)					//!< Manager entry point more functions.
#define I_EMVCUST_Periodic_Call_TlvTree				(206)					//!< Manager entry point periodic call.
#define I_EMVCUST_Process_Step_TlvTree				(207)					//!< Engine entry point process step.
#define I_EMVCUST_Display_Message_TlvTree			(208)					//!< Engine entry point display message.
#define I_EMVCUST_Get_Last_Transaction_TlvTree		(209)					//!< Engine entry point get last transaction.
#define I_EMVCUST_Voice_Referral_TlvTree			(213)					//!< Engine entry point voice referral.
#define I_EMVCUST_Get_AID_TlvTree					(214)					//!< Manager entry point get AID.
#define I_EMVCUST_KeyManagement_TlvTree				(215)					//!< Manager entry point key management.
#define I_EMVCUST_Authorization_TlvTree				(216)					//!< Engine entry point authorization.
#define I_EMVCUST_Choose_Language_Menu_TlvTree		(217)					//!< Engine entry point choose language menu.
#define I_EMVCUST_Menu_Select_TlvTree				(218)					//!< Engine entry point menu select.
#define I_EMVCUST_Choose_Account_Type_Menu_TlvTree	(219)					//!< Engine entry point choose account type menu.
//#define I_EMVCUST_Perform_Transaction_TlvTree		(220)
#define I_EMVCUST_Get_AID_ICS_TlvTree				(221)					//!< Engine entry point get AID ICS.


#define CUST_TLVTREE_SERVICE_BUFFER_SIZE			(4096)					//!< size of inter application exchange buffer.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief Definition of header of data exchanged with engine.
typedef struct
{
	unsigned short m_usAppliType;									//!< Application type of called application.
	unsigned short m_usService;										//!< Service of called application.
	int m_nFunction;												//!< Function of service of called application.
	unsigned long m_ulRuf1;											//!< Reserved for future use.
	unsigned long m_ulRuf2;											//!< Reserved for future use.
} I_CUST_TLVTREE_SERVICE_HEADER;

//! \brief Definition of structure to exchange data with engine.
typedef struct
{
	I_CUST_TLVTREE_SERVICE_HEADER m_Header;							//!< Exchanged data header.
	unsigned char m_Buffer[CUST_TLVTREE_SERVICE_BUFFER_SIZE];		//!< Exchanged buffer.
} I_CUST_TLVTREE_SERVICE;


/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//! @}

#endif


/**
 * \file	CST_TaskStatus.h
 * \brief 	Management of the task that will retrieve the transaction status.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CST_TASK_STATUS_H__INCLUDED__
#define __CST_TASK_STATUS_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Launch the task that manage the transaction status.
//! \return OK if task correctly launched, KO else.

int CST_TaskStatus_LaunchTask (void);



//! \brief Kill the status task.

void CST_TaskStatus_KillTask (void);

#endif // __CST_TASK_STATUS_H__INCLUDED__

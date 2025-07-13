#ifndef _SEC_EXTEND_H

#define _SEC_EXTEND_H

// Copyright (c) 2009 INGENICO FRANCE, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// INGENICO FRANCE has intellectual property rights relating
// to the technology embodied in this software.  In particular,
// and without limitation, these intellectual property rights
// may include one or more patents.
// 
// This software is distributed under licenses restricting
// its use, copying, distribution, and decompilation.
// No part of this software may be reproduced in any form
// by any means without prior written authorization of
// Ingenico France.

//! \file        SEC_Extend.h
//! \brief This module regroups extended header files, added to DLL security.

//! \addtogroup DLLsecu_EXTEND
//! @{
//! \par Introduction
//! Extended package has been created, in order to add certified functions to DLL security.\n\n
//! This package is composed of include files SEC_extend.h which includes:\n 
//! - SEC_interface.h () \n
//! - SEC_AESHMacinterface.h\n
//! - SEC_DataCipherinterface.h\n
//! - SEC_ExtDukptinterface.h\n
//! and the static library SEC_extend.lib.\n\n
//! This interface allows to call functions implemented in additional schemes\n\n
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD></TD></TR>
//! <TR><TD><b>If you use this library, please include <SEC_extend.h> instead of <SEC_interface.h> in your source code and library in the project.</b></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//! @}
#include "SEC_interface.h"
#include "SEC_AESHMacinterface.h"
#include "SEC_DataCipherinterface.h"
#include "SEC_ExtDukptinterface.h"

#endif // _SEC_EXTEND_H

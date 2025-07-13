/*!
 ------------------------------------------------------------------------------
INGENICO Technical Software Department
------------------------------------------------------------------------------
Copyright (c) 2013, Ingenico.
 28-32 boulevard de Grenelle 75015 Paris, France.
 All rights reserved.
 This source program is the property of INGENICO Company and may not be copied
 in any form or by any means, whether in part or in whole, except under license
 expressly granted by INGENICO company
 All copies of this program, whether in part or in whole, and
 whether modified or not, must display this and all other
 embedded copyright and ownership notices in full.
 ------------------------------------------------------------------------------
 Project : Telium+ 
 Module : SDK
 This file allows T2 projects to use T+ renamed APIs and to have common code between T2 and T+ projects
 ------------------------------------------------------------------------------
*/

#ifdef __FRAMEWORK_TPLUS__
#include "sdk_tplus.h"
#else
#include "sdk30.h"
#include "sdk_compat_src_tpls.h"
#endif

// note: __FRAMEWORK_T2__ must not be checked as not present in old sdk

/////////////////////////////////////////////////////////////////

//! \file
//! This file describes the interface of the EmvDcInterface.lib library.

//// Macros & preprocessor definitions //////////////////////////

#ifndef _SECDEL_
#error _SECDEL_ must be defined !
#endif

//// Types //////////////////////////////////////////////////////

//// Functions //////////////////////////////////////////////////


/* specially design for AXIS in order to do French application with Custom */
void Mode_France (void);
void Mode_Export (void);
void TVR_ClearByte3(void);
void TVR_Set(unsigned char bitByte);
void TVR_UnSet(unsigned char bitByte);
void CVRResult_MethodSet(unsigned char method);
void Force_DC_Option( unsigned char icc_emv_dc_option );
void MPAA_Escota_Treatements(void);

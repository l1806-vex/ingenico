/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


//// Global variables ///////////////////////////////////////////
//extern Word g_nCallingTaskNumber;

//// Static function definitions ////////////////////////////////

//// Functions //////////////////////////////////////////////////
int PerformRemoteIP( int nRemoteType,					// TMSGPRS, TMSIP,TMSIPRTC 
					 const char *szCallNumber,			// PSTN Phone Number. 
				     const char *szAddress,				// TMS IP address : xxx.xxx.xxx.xxx:yyy
				     const char *szContractNumber,
				     const char *szSoftwareName,
					 const char *szLogin,				// PPP Login for ISP or GPRS.
					 const char *szPassword,			// PPP Password for ISP or GPRS.
					 const char *szAPN );				// GPRS APN

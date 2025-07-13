#ifndef __NAT__H__
#define __NAT__H__

//! \defgroup NAT_API NAT
//! \par Introduction
//! NAT (Network Address Translation) is a service that allows the terminal to act as a router between
//! its several IP interfaces. 
//! @{

#ifdef __cplusplus
extern "C"
{
#endif

//! \defgroup NAT_ERROR_CODES Error codes.
//! \brief Error codes returned by NAT API functions.
//! @{

#define NAT_OK             ( 0) //!< No error during the process.
#define NAT_NOT_SUPPORTED  (-1) //!< This feature is not supported.

//! @}

//! \defgroup NAT_OPTIONS Options to configure the NAT.
//! \brief Identifiers and data types for NAT option.
//! @{

#define NAT_IF_MODE_PRIVATE        (0) //!< The IP interface is private.
#define NAT_IF_MODE_PUBLIC         (1) //!< The IP interface is public.

//! @}

//! \brief Set a NAT option.
//! \param[in] szIf    String identifying the IP interface.
//! This parameter is "eth0" for Ethernet, "wlan0" for Wifi. For PPP interfaces, the name
//! must be retrieved by using PPP_GetOption() function. See \ref SAMPLE_NAT for an example.
//! \param[in] nOption Option identifier.
//! \param[in] pValue  Value of the option.
//! \return \ref NAT_OK or a negative error code (see \ref NAT_ERROR_CODES).
int NAT_SetOption( const char* szIf, int nOption, void* pValue );

//! \brief Get the value of a NAT option. Not implemented yet.
//! \param[in]  szIf    String identifying the IP interface.
//! This parameter is "eth0" for Ethernet, "wlan0" for Wifi. For PPP interfaces, the name
//! must be retrieved by using PPP_GetOption() function. See \ref SAMPLE_NAT for an example.
//! \param[in]  nOption Option identifier.
//! \param[out] pValue  Value of the option.
//! \return \ref NAT_OK or a negative error code (see \ref NAT_ERROR_CODES).
int NAT_GetOption( const char* szIf, int nOption, void* pValue );

//! \defgroup SAMPLE_NAT NAT sample.
//! \brief Basic use of NAT interfaces.
//!
//! \par Sample description.
//! This sample shows how to use the NAT API functions.
//!
//! \include NAT__Sample_01.c
//! \example NAT__Sample_01.c

#ifdef __cplusplus
}
#endif

//! @}
    
#endif // __NAT__H__


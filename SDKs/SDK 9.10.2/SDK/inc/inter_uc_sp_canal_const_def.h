#ifdef __cplusplus
extern "C" {
#endif

#ifndef __INTER_UC_SP_CANAL_CONST_DEF_H_INCLUDED__
#define __INTER_UC_SP_CANAL_CONST_DEF_H_INCLUDED__

/*! @addtogroup KSFAM_BLUE_TOOTH
	* @{
 */ 

/*
======================================================================
			Define of channel number corresponding to peripherals
======================================================================
*/


#define INTER_UC_SP_CANAL_RUF         (0)		/*!< Reserved for Futur Use */
#define INTER_UC_SP_CANAL_COM0        (1)		/*!< COM0 of base */
#define INTER_UC_SP_CANAL_MODEM       (2)		/*!< MODEM of base */
#define INTER_UC_SP_CANAL_ASSOCIATION (3)		/*!< Base information retrieval service */
#define INTER_UC_SP_CANAL_COMT        (4)		/*!< Virtual com used to download (Deprecated) */
#define INTER_UC_SP_CANAL_COMN        (5)		/*!< Virtual com for PPP link between terminal and Ethernet base */
#define INTER_UC_SP_CANAL_COM3        (8)		/*!< Second physical com port on Ethernet base (actually COM1 in the base)*/
#define INTER_UC_SP_CANAL_COM1        INTER_UC_SP_CANAL_COM3
#define INTER_UC_SP_CANAL_HTTP_SERVER (9)		/*!< HTTP-like server for file transfert */
#define INTER_UC_SP_CANAL_COMU        (10)		/*!< COM USB Slave of base */
#define INTER_UC_SP_CANAL_COMH        (11)		/*!< COM USB Host of BME base or First COM USB Host of base (IWL) */ 
#define INTER_UC_SP_CANAL_COMH2       (12)		/*!< Second COM USB Host of base (IWL only) */ 
#define INTER_UC_SP_CANAL_MODEM_V34   (13)		/*!< MODEM_V34 of base */
#define INTER_UC_SP_MAX_CANAL_NUMBER  (15)		/*!< Maximum channel index (nb max = MAX_CANAL + 1) */

// Related error codes
#define INTER_UC_SP_UNKNOWN_USER      (-2)		/*!< User for this channel unknown yet */
#define INTER_UC_SP_NO_SUCH_CHANEL    (-1)		/*!< Improper channel (number too high) */

/*! @}  */ 


#endif   // __INTER_UC_SP_CANAL_CONST_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif

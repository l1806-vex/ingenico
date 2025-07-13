#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_SYSFIOCTL_DEF_H_INCLUDED__
#define __OEM_SYSFIOCTL_DEF_H_INCLUDED__

//! \addtogroup SYSTEMFIOCTL
//! @{
		//! \defgroup SYSFIOTCL_IDENT Terminal identification
		//! @{
				//! \defgroup PLATEFORM_VALUE Platform ID
				//! \defgroup TERMTYPE_VALUE Type of Terminal
		//! @}
		//! \defgroup SYSFIOTCL_FEATURES Terminal features
		//! @{
				//! \defgroup TERM_DISPLAY_TYPE Type of Display
		//! @}
		//! \defgroup SYSFIOCTL_ETHERNET Ethernet sysfioctl
		//! @{
				//! \defgroup ETHERNET_CONNECTED_TYPE Type of Ethernet connected
		//! @}
		//! \defgroup SYSFIOCL_SECURITY Security sysfioctl
		//! @{
				//! \defgroup BOOSTER_VERSION Type of the secure processor
				//! \defgroup PCI_PTS_VERSION PCI PTS version
				//! \defgroup INGETRUST_TYPES Type of INGETRUST PKI
		//! @}
		//! \defgroup SYSTEMFIOCTL_MISCELLANEOUS Miscellaneous
//! @}


//! \addtogroup SYSTEMFIOCTL
	//! @{

//! \addtogroup PLATEFORM_VALUE
//! 
//! @include oem_sysfioctl_Sample_01.c
//! @{

#define PLATFORM_UNKNOWN     0			/*!< unknown platform */
#define PLATFORM_EFT30_V2    1			/*!< EFT30 V2 platform */
#define PLATFORM_EFT30_V3    2			/*!< EFT30 V3 platform */
#define PLATFORM_EFT930      3			/*!< EFT930 platform */
#define PLATFORM_TWIN        5			/*!< TWIN platform */
#define PLATFORM_UCM	       6		/*!< UCM platform */
#define PLATFORM_RADIO_BASE  7			/*!< radio base platform */
#define PLATFORM_EFT930S     8			/*!< EFT930S platform */
#define PLATFORM_MA2G        9			/*!< MA2G platform */
#define PLATFORM_EFT30_PCI  10			/*!< SMART2 platform */
#define PLATFORM_P300       11			/*!< ML30 platform */
#define PLATFORM_MA500        12		/*!< MA500 platform */
#define PLATFORM_MR40		  13		/*!< MR40 platform */
#define PLATFORM_EFT930_SGEM 14			/*!< EFT930 S Gprs Ethernet Modem platform */
#define PLATFORM_S4          15			/*!< S4 platform */
#define PLATFORM_SOCLE_BME   16			/*!< Blue tooth Modem EThernet BASE platform */
#define PLATFORM_X07_BASE  0x100		/*!< ICT220/250 platform */
#define PLATFORM_IWL2XX    0x101		/*!< IWL220/250 platform */
#define PLATFORM_ISTXXX    0x102		/*!< ISTxxx platform */
#define PLATFORM_SOCLE_IWL 0x103		/*!< IWL cradle platform */
#define PLATFORM_ISPM	   0x104		/*!< IWL cradle platform */
#define PLATFORM_IUN230	   0x105        /*!< IUN230 platform */
#define PLATFORM_IUN180	   0x106        /*!< IUN180 platform */
#define PLATFORM_IUN150	   0x107        /*!< IUN150 platform */
#define PLATFORM_IWB2XX	   0x108        /*!< IWB220/250 platform */
#define PLATFORM_IUC180B   0x109        /*!< iUC180B platform */
#define PLATFORM_ISCXXX	   0x500		/*!< ISC350/250 platform */
#define PLATFORM_IWLXXX_TH3  0x501		/*!< IWL280/IWE280/IWL350 platform */
#define PLATFORM_IPP4XX      0x502		/*!< IPP4XX platform */

//! @}

//! \addtogroup TERMTYPE_VALUE Type of Terminal
//! 
//! @include oem_sysfioctl_Sample_02.c
//! @{

#define TERM_SMART        0		/*!< SMART terminal */
#define TERM_EFT30        1		/*!< EFT30 terminal */
#define TERM_EFT30_PLUS   2		/*!< EFT30 Plus terminal */
#define TERM_EFT930       3		/*!< EFT930 terminal */
#define TERM_EFT930S      4		/*!< EFT930S terminal */
#define TERM_EFT930G      5		/*!< EFT930G terminal */
#define TERM_EFT930BT     6		/*!< EFT930BT terminal */
#define TERM_TWIN30       7		/*!< TWIN30 terminal */
#define TERM_UCM30        8		/*!< UCM30 terminal */
#define TERM_RADIO_BASE   9		/*!< Radio Base */
#define TERM_MA2G        10		/*!< MA2G terminal */
#define TERM_EFT30_PCI   11		/*!< SMART2 terminal */
#define TERM_P300        12		/*!< ML30 terminal */
#define TERM_MA500       13		/*!< MA500 terminal */
#define TERM_EFT930W     14		/*!< EFT930 Wifi terminal */
#define TERM_EFT930SGEM  15		/*!< EFT930S Gprs Ethernet Modem terminal */
#define TERM_MR40	       16		/*!< MR40 terminal */
#define TERM_TWIN33      17		/*!< Twin 33 terminal */
#define TERM_S4	         18		/*!< S4 terminal */
#define TERM_SOCLE_BME   19		/*!< Bluetooth Modem Ethernet Base  */
#define TERM_UNKNOWN     20		/*!< unknown terminal */
#define TERM_X07         0x100	/*!< iCT220 terminal */
#define TERM_ICT220		 0x100	/*!< iCT220 terminal */
#define TERM_ICT250		 0x100	/*!< iCT250 terminal */
#define TERM_SPM  		 0x101	/*!< SPM terminal */
#define TERM_IPP320		 0x102	/*!< iPP320 Monochrome Display */
#define TERM_IPP350		 0x103	/*!< iPP350 Color Display */
#define TERM_IWL220		 0x104	/*!< iWL220 */
#define TERM_IWL250		 0x105	/*!< iWL250 Color Display */
#define TERM_IST150		 0x106	/*!< iST150 */
#define TERM_SOCLE_IWL   0x107  /*!< Bluetooth IWL Base  */

#define TERM_E532		 0x108  /*!< E532 terminal */
#define TERM_IMP350		 0x109  /*!< iSPM Ingenico IMP350 */
#define TERM_IMP320		 0x10A  /*!< iSPM Ingenico IMP320 */
#define TERM_IUN230		 0x10B  /*!< iUN230 */
#define TERM_IUN180		 0x10C  /*!< iUN180 */
#define TERM_IUN150		 0x10D  /*!< iUN150 */
#define TERM_IWB220		 0x10E	/*!< iWB220 */
#define TERM_IWB250		 0x10F	/*!< iWB250 Color Display */
#define TERM_IUC180B	 0x110  /*!< iUC180B */
#define TERM_IPP310		 0x111	/*!< iPP310 */
#define TERM_ICM122	   0x112	/*!< iCM122 */

#define TERM_ICT280    0x300	/*!< iCT280 terminal */
#define TERM_ISC350    0x500	/*!< iSC350 terminal */
#define TERM_ISC250    0x501	/*!< iSC250 terminal */
#define TERM_ISC220    0x501	/*!< iSC220 terminal */
#define TERM_IWL280    0x503	/*!< iWL280 terminal */
#define TERM_IWL350    0x504	/*!< iWL350 terminal */
#define TERM_IPP480    0x505	/*!< iPP480 terminal */
#define TERM_ISC480    0x506	/*!< iSC480 terminal */
#define TERM_IWE280    0x507	/*!< iWE280 terminal */


//! @}

//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_DISPLAY_TYPE       0x8013					/*!< @param unsigned int * : gets the \ref TERM_DISPLAY_TYPE  
																		 @return 0. */

//! @}

//! \addtogroup TERM_DISPLAY_TYPE Type of Display
//! @brief Set by \ref SYS_FIOCTL_GET_DISPLAY_TYPE
//! 
//! @include oem_sysfioctl_Sample_05.c
//! @{

#define TERM_DISPLAY_2L_ALPHA             0							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : alpha 2 lines */
#define TERM_DISPLAY_2L_GRAPHIC           1							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : graphic 2 lines */
#define TERM_DISPLAY_VGA		          TERM_DISPLAY_2L_GRAPHIC	/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : VGA */
#define TERM_DISPLAY_4L_GRAPHIC           2							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : graphic 4 lines */
#define TERM_DISPLAY_240_320_COLOR		  TERM_DISPLAY_4L_GRAPHIC 	/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : QVGA 240*320 */
#define TERM_DISPLAY_8L_GRAPHIC           3							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : graphic 8 lines */
#define TERM_DISPLAY_320_240_COLOR		  TERM_DISPLAY_8L_GRAPHIC 	/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : QVGA 320*240 */
#define TERM_DISPLAY_GRAPHIC_128x64       4							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : graphic 128x64 pixels */
#define TERM_DISPLAY_GRAPHIC_128x128      5							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : graphic 128x128 pixels */
#define TERM_DISPLAY_HVGA_P               6							/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : HVGA Portrait : 320*480 */
#define TERM_DISPLAY_NULL                 0xFF 						/*!< value for \ref SYS_FIOCTL_GET_DISPLAY_TYPE : No display in this terminal */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_GET_SYS_TIMER                        0x8044 			/*!< param : unsigned int, Get slow clock counter.
	                                                                        This counter is increased at 32 KHz for Telium I (30,5µs period) and 100 Khz for Telium II (10 µs period) */
	                                                                        
//! @}

//! \addtogroup ETHERNET_CONNECTED_TYPE
//! @brief Set by \ref SYS_FIOCTL_GET_ETHERNET_INFO
//! 
//! @include oem_sysfioctl_Sample_06.c
//! @{

#define ETHERNET_NOT_CONNECTED                          0				/*!< Ethernet not connected */
#define ETHERNET_CONNECTED_HD_10MBITS                   1				/*!< Ethernet connected - Half duplex 10 Mbits/s */
#define ETHERNET_CONNECTED_FD_10MBITS                   2				/*!< Ethernet connected - Full duplex 10 Mbits/s  */
#define ETHERNET_CONNECTED_HD_100MBITS                  4				/*!< Ethernet connected - Half duplex 100 Mbits/s  */
#define ETHERNET_CONNECTED_FD_100MBITS                  8				/*!< Ethernet connected - Full duplex 100 Mbits/s  */

//! @}
//! \addtogroup BOOSTER_VERSION
//! 
//! @include oem_sysfioctl_Sample_07.c
//! @{

#define NO_BOOSTER                                      0					/*!< No booster in terminal */
#define BOOSTER_1                                       1					/*!< Booster I */
#define BOOSTER_2                                       2					/*!< Booster II */
#define BOOSTER_3                                       3					/*!< Booster III */

//! @}

//! \addtogroup INGETRUST_TYPES
//! 
//! @include oem_sysfioctl_Sample_12.c
//! @{

#define INGETRUST_TYPE_UNKNOWN 			-1	/*!< INGETRUST Type unknown */
#define INGETRUST_TYPE_NONE 			0	/*!< INGESTRUST Type none*/
#define INGETRUST_TYPE_PKIv1			1	/*!< INGESTRUST PKI v1 */
#define INGETRUST_TYPE_PKIv3			3	/*!< INGESTRUST PKI v3 */

//! @}

//! \addtogroup PCI_PTS_VERSION
//! @note On TELIUM II only.
//!
//! @include oem_sysfioctl_Sample_13.c
//! @{

#define PCI_PTS_V2 			2		/*!< PCI PTS V2 */
#define PCI_PTS_V3 			3		/*!< PCI PTS V3 */

//! @}

//! @}


#endif   // __OEM_SYSFIOCTL_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif

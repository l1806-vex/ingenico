/*! @addtogroup KSFAM_M2OS
	* @{
**/

#ifndef _HTERM_H
#define _HTERM_H

/*
======================================================================
					List of Defines
======================================================================
*/
#define EN_DEBUG_TRACE               0x01
#define EN_DEBUG_SANS_PATCH          0x02
#define EN_DEBUG_AVEC_ETAT_COMPLET   0x04
#define EN_DEBUG_AVEC_BANDEAU        0x08
#define EN_DEBUG_AVEC_REDIRECTION    0x10
#define EN_DEBUG_AVEC_TRACE          0x20
#define EN_DEBUG                     0x40

/*
======================================================================
			Functions Definition
======================================================================
*/

//! \brief Check the Terminal configuration.
/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if Portable terminal
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsPortable:KSFAM_M2OS:
// \endif
extern int        IsPortable(void);


/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if Usb host device
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsUsbHost:KSFAM_M2OS:
// \endif
extern int         IsUsbHost(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if USB slave device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsUsbSlave:KSFAM_M2OS:
//  \endif
extern int         IsUsbSlave(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if internal printer is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsPrinter:KSFAM_M2OS:
//  \endif
extern int         IsPrinter(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if printer is available and slow printing speed is configured.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsSlowPrinter:KSFAM_M2OS:
//  \endif
extern int         IsSlowPrinter(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if the display is a color display.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsColorDisplay:KSFAM_M2OS:
//  \endif
extern int         IsColorDisplay(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if ISO1 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsISO1:KSFAM_M2OS:
//  \endif
extern int         IsISO1(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 *  - 1 if ISO2 device is available.
 *  - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsISO2:KSFAM_M2OS:
//  \endif
extern int         IsISO2(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 *  - 1 if ISO3 device is available.
 *  - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsISO3:KSFAM_M2OS:
//  \endif
extern int         IsISO3(void);


/*! @brief This function tests if CAM1 Reader Available.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCAM1:KSFAM_M2OS:
// \endif
extern int         IsCAM1(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 *  - 1 if CAM2 device is available.
 *  - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCAM2:KSFAM_M2OS:
// \endif
extern int         IsCAM2(void);


/*! @brief This function tests if CAM3 Reader Available.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCAM3:KSFAM_M2OS:
// \endif
extern int         IsCAM3(void);


/*! @brief This function tests if SAM1 Reader Available.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsSAM1:KSFAM_M2OS:
// \endif
extern int         IsSAM1(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if SAM2 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsSAM2:KSFAM_M2OS:
// \endif
extern int         IsSAM2(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if SAM3 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsSAM3:KSFAM_M2OS:
// \endif
extern int         IsSAM3(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if SAM4 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsSAM4:KSFAM_M2OS:
//  \endif
extern int         IsSAM4(void);


/*! @brief This function tests if COM0 serial link Available .
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCOM0:KSFAM_M2OS:
// \endif
extern int         IsCOM0(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COM1 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCOM1:KSFAM_M2OS:
// \endif
extern int         IsCOM1(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COM1 is available and is an RS232 device.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsCOM1RS232:KSFAM_M2OS:
//  \endif
extern int         IsCOM1RS232(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COM1 is available and is a TTL device for PINPAD.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsCOM1Pinpad:KSFAM_M2OS:
//  \endif
extern int         IsCOM1Pinpad(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COM2 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCOM2:KSFAM_M2OS:
// \endif
extern int         IsCOM2(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COM3 device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCOM3:KSFAM_M2OS:
// \endif
extern int         IsCOM3(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COMN device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsCOMN:KSFAM_M2OS:
//  \endif
extern int         IsCOMN(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COMU device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCOMU:KSFAM_M2OS:
// \endif
extern int         IsCOMU(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if COMH device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsCOMH:KSFAM_M2OS:
// \endif
extern int         IsCOMH(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if modem device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsMODEM:KSFAM_M2OS:
//  \endif
extern int         IsMODEM(void);


/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if display is available and is a small display (128x64).
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsSmallDisplay:KSFAM_M2OS:
//  \endif
extern int         IsSmallDisplay(void);


/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if display is available and is a large display (128x128).
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsLargeDisplay:KSFAM_M2OS:
// \endif
extern int         IsLargeDisplay(void);


/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if touch screen is available
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsTouchScreen:KSFAM_M2OS:
// \endif
extern int         IsTouchScreen(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if BUZZER device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsBUZZER:KSFAM_M2OS:
//  \endif
extern int         IsBUZZER(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if TILTO device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsTILTO:KSFAM_M2OS:
//  \endif
extern int         IsTILTO(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if MMC device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsMMC:KSFAM_M2OS:
//  \endif
extern int         IsMMC(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if the terminal has a radio device (GPRS,WIFI,Bluetooth).
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsRadio:KSFAM_M2OS:
//  \endif
extern int         IsRadio(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if GPRS radio device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsRadioGPRS:KSFAM_M2OS:
//  \endif
extern int         IsRadioGPRS(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if GPRS 3G radio device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsRadio3G:KSFAM_M2OS:
//  \endif
extern int         IsRadio3G(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if CDMA radio device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsRadioCDMA:KSFAM_M2OS:
//  \endif
extern int         IsRadioCDMA(void);


/*! @brief This function tests if GPRS functionality Available
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsGPRS:KSFAM_M2OS:
// \endif
extern int         IsGPRS(void);


/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if Bluetooth radio device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsBT:KSFAM_M2OS:
//  \endif
extern int         IsBT(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if BIO device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsBIO:KSFAM_M2OS:
//  \endif
extern int         IsBIO(void);

/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if the terminal is an EFT30.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsEFT30:KSFAM_M2OS:
//  \endif
extern int         IsEFT30(void);


/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if Internal ETHERNET device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsRadioETHERNET:KSFAM_M2OS:
//  \endif
extern int         IsRadioETHERNET(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if Ethernet device is available (via WIFI,Bluetooth or internal)
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsETHERNET:KSFAM_M2OS:
//  \endif
extern int         IsETHERNET(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if internal wifi radio device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsRadioWifi:KSFAM_M2OS:
//  \endif
extern int         IsRadioWifi(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if wifi device is available (via USB Key or internal).
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsWifi:KSFAM_M2OS:
//  \endif
extern int         IsWifi(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if Internal Cless device is available.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsCless:KSFAM_M2OS:
//  \endif
extern int         IsCless(void);


/*! @brief This function checks if the terminal is a TWIN31.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsTwin31:KSFAM_M2OS:
// \endif
extern int         IsTwin31(void);

/*! @brief This function checks if the terminal is a twin32.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsTwin32:KSFAM_M2OS:
// \endif
extern int         IsTwin32(void);

/*! @brief This function checks if the terminal is a twin33.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsTwin33:KSFAM_M2OS:
// \endif
extern int         IsTwin33(void);


/*! @brief This function checks the terminal is an ICT220.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsICT220:KSFAM_M2OS:
// \endif
extern int         IsICT220(void);


/*! @brief This function checks the terminal is an ICT250.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsICT250:KSFAM_M2OS:
// \endif
extern int         IsICT250(void);


/*! @brief This function checks the terminal is an ICT280.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsICT280:KSFAM_M2OS:
// \endif
extern int         IsICT280(void);


/*! @brief This function checks the terminal is an ISC250.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsISC250:KSFAM_M2OS:
// \endif
extern int         IsISC250(void);


/*! @brief This function checks the terminal is an E532.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsE532:KSFAM_M2OS:
// \endif
extern int         IsE532(void);


/*! @brief This function checks the terminal is an IST150.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIST150:KSFAM_M2OS:
// \endif
extern int         IsIST150(void);


/*! @brief This function checks the terminal is an IUN150.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIUC150:KSFAM_M2OS:
// \endif
extern int         IsIUC150(void);


/*! @brief This function checks the terminal is an IUN180.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIUC180:KSFAM_M2OS:
// \endif
extern int         IsIUC180(void);


/*! @brief This function checks the terminal is an IUC180B.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIUC180B:KSFAM_M2OS:
// \endif
extern int         IsIUC180B(void);


/*! @brief This function checks the terminal is an IsIUN230.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIUP250:KSFAM_M2OS:
// \endif
extern int         IsIUP250(void);


/*! @brief This function checks the cless target manage Inter/UC mode
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsTargetModeAvailable:KSFAM_M2OS:
// \endif
extern int         IsTargetModeAvailable(void);


/*! @brief This function checks the terminal is an IWL220.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWL220:KSFAM_M2OS:
// \endif
extern int         IsIWL220(void);


/*! @brief This function checks the terminal is an IWL250.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWL250:KSFAM_M2OS:
// \endif
extern int         IsIWL250(void);


/*! @brief This function checks the terminal is an IWB220.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWB220:KSFAM_M2OS:
// \endif
extern int         IsIWB220(void);


/*! @brief This function checks the terminal is an IWB250.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWB250:KSFAM_M2OS:
// \endif
extern int         IsIWB250(void);


/*! @brief This function checks the terminal is an IWX2XX (IWL2XX or IWB2XX)
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWX2XX:KSFAM_M2OS:
// \endif
extern int         IsIWX2XX(void);


/*! @brief This function checks the terminal is an IWL2XX.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWL2XX:KSFAM_M2OS:
// \endif
extern int         IsIWL2XX(void);


/*! @brief This function checks the terminal is an IWB2XX.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWB2XX:KSFAM_M2OS:
// \endif
extern int         IsIWB2XX(void);


/*! @brief This function checks the terminal is an IsTermCGUI.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsTermCGUI:KSFAM_M2OS:
// \endif
extern int         IsTermCGUI(void);


/*! @brief This function checks the terminal is an IsIWL280.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWL280:KSFAM_M2OS:
// \endif
extern int         IsIWL280(void);


/*! @brief This function checks the terminal is an IsIWL350.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIWL350:KSFAM_M2OS:
// \endif
extern int         IsIWL350(void);


/*! @brief This function checks the terminal is an IsIPP480.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIPP480:KSFAM_M2OS:
// \endif
extern int         IsIPP480(void);


/*! @brief This function checks the terminal is an ISC350.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsISC350:KSFAM_M2OS:
// \endif
extern int         IsISC350(void);


/*! @brief This function checks the terminal is an ISC480.
 * @return != 0 if available.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsISC480:KSFAM_M2OS:
// \endif
extern int         IsISC480(void);


/*! @brief This function Check if the terminal is a SPM.
 * @return != 0 if terminal is a SPM.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsSPM:KSFAM_M2OS:
// \endif
extern int         IsSPM(void);


/*! @brief This function Check if the terminal is a IMP350.
 * @return != 0 if terminal is a IMP350.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsISPM:KSFAM_M2OS:
// \endif
extern int         IsIMP350(void);


/*! @brief This function Check if the terminal is a IsICM122
 * @return != 0 if terminal is a ICMP.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsICM122:KSFAM_M2OS:
// \endif
extern int         IsICM122(void);


/*! @brief This function Check if the terminal is a IMP3xx (IMP320 or IMP350) Companion.
 * @return != 0 if terminal is a IMP3xx (IMP320 or IMP350) Companion.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsISPM:KSFAM_M2OS:
// \endif
extern int         IsIMP3xxCompanion(void);


/*! @brief This function Check if the terminal is an ML30.
 * @return != 0 if terminal is a ML30.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsML30:KSFAM_M2OS:
// \endif
extern int         IsML30(void);


/*! @brief This function Check if the terminal is an IPP310.
 * @return != 0 if terminal is a IPP310.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIPP310:KSFAM_M2OS:
// \endif
extern int         IsIPP310(void);


/*! @brief This function Check if the terminal is an IPP320.
 * @return != 0 if terminal is a IPP320.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIPP320:KSFAM_M2OS:
// \endif
extern int         IsIPP320(void);


/*! @brief This function Check if the terminal is an IPP350.
 * @return != 0 if terminal is a IPP350.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIPP350:KSFAM_M2OS:
// \endif
extern int         IsIPP350(void);


/*! @brief This function checks if the terminal is an IPP3XX (IPP310 or IPP320 or IPP350).
 * @return != 0 if terminal is a IPPXX3.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsIPP3XX:KSFAM_M2OS:
// \endif
extern int         IsIPP3XX(void);


/*! @brief This function returns the configuration file.
 * @return configuration file.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:GetConfiguration:KSFAM_M2OS:
//  @GSIM_A:0:ONE_ADDRESS
//  \endif
extern hterm_t      *GetConfiguration(void);


/*! @brief This function returns the ethernet configuration file.
 * @return Ethernet configuration file.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:GetEthernetConfiguration:KSFAM_M2OS:
//  @GSIM_A:0:ONE_ADDRESS
//  \endif
extern ethernet_t   *GetEthernetConfiguration(void);


/*! @brief This function returns the product name.
 * @param Name : The product name string of 64 bytes.
 * @return 
 *  -  0 OK
 *  - -1 default value used
 *  - -2 bad parameter (NULL for ex)
 *  - -3 unknown product
 * @par exit None
 *	  
 * @link KSFAM_PSQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:v:KSFAM_PSQ:
//  @GSIM_A:1:DATA_SIZE(64)
// \endif
extern int GetProductName(unsigned char *Name);

/*! @brief This function checks the terminal configuration.
 * @return the type of terminal :
 * - TYPE_TERMINAL_ML30 '1'
 * - TYPE_TERMINAL_SMART '2'
 * - TYPE_TERMINAL_EFT30F '3'
 * - TYPE_TERMINAL_EFT30P '4'
 * - TYPE_TERMINAL_TWIN30 '5'
 * - TYPE_TERMINAL_EFT930 '6'
 * - TYPE_TERMINAL_CAD30 '7'
 * - TYPE_TERMINAL_X07 '8'
 * - TYPE_TERMINAL_MR40 '9'
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:GetTerminalType:KSFAM_M2OS:
//  \endif
extern char          GetTerminalType(void);


/*! @brief This function returns the product range.
 * @param produit : (significant value if return = 4 ) product in the EFT30P range.
 * - TYPE_TERMINAL_EFT930W '5'
 * - TYPE_TERMINAL_EFT930P '6'
 * - TYPE_TERMINAL_EFT930G '7'
 * - TYPE_TERMINAL_EFT930B '8'
 * - TYPE_TERMINAL_EFT930F '9'
 *
 * @return Gamme produit : product range :
 * - TYPE_TERMINAL_ML30 '1'
 * - TYPE_TERMINAL_SMART '2'
 * - TYPE_TERMINAL_EFT30F '3'
 * - TYPE_TERMINAL_EFT30P '4'
 * - TYPE_TERMINAL_TWIN30 '5'
 * - TYPE_TERMINAL_EFT930 '6'
 * - TYPE_TERMINAL_CAD30 '7'
 * - TYPE_TERMINAL_X07 '8'
 * - TYPE_TERMINAL_MR40 '9'
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:GetProductType:KSFAM_M2OS:
//  \endif
extern char          GetProductType(char *produit);

/*! @brief This function checks the terminal configuration.
 * @return
 * - 1 if ethernet connected.
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsEthernetConnected:KSFAM_M2OS:
// \endif
extern int           IsEthernetConnected(void);


/*! @brief This function checks the terminal configuration.
 * @return 
 * - 1 if the terminal is ZKA
 * - 0 otherwise.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:is_ZKA:KSFAM_M2OS:
//  \endif
extern int         is_ZKA(void);


/*! @brief Check if LEDS hardware or not
 * @return 
* -  1 if the terminal has software LEDS
* -  0 if the terminal has hardware LEDS
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:IsLedOnDisplay:KSFAM_M2OS:
//  \endif
extern int IsLedOnDisplay(void);
//! @}

//! \addtogroup KSFAM_M2OS
//! @{

//! \brief Check the Terminal configuration.
//! \return
//! - 1 if Modem is V34
//! - 0 otherwise.
// \if SIMULATION
//  @GSIM_F:IsModemV34:KSFAM_M2OS:
// \endif
extern int         IsModemV34(void);
//! @}

/*! @brief This function checks the terminal plateform type.
 * @return 
 * - 1 TELIUM1.
 * - 2 TELIUM2.
 * - -1 unvalaible
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
//  \if SIMULATION
//  @GSIM_F:TM_Platform_GetType:KSFAM_M2OS:
//  \endif
extern int         TM_Platform_GetType(void);

/*! @brief This function retrieves the VARID of an object present in active directory ('SYSTEM').
 * @param object_type : object Type : 
 * - OBJECT_TYPE_APPLI	 : Application object 
 * - OBJECT_TYPE_DLL	   : Dynamicaly Linked Library object 
 * - OBJECT_TYPE_DRIVER : System driver object 
 * - OBJECT_TYPE_PARAM  : Parameter file 
 * - OBJECT_TYPE_KEY    : Key file 
 * @param application_type : application type.
 * @param var_id : pointer to VARID.
 * @return
 * - 0 if no error. Else :
 * - -1 if object has not been found.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
//  \if SIMULATION
//  @GSIM_F:TM_Application_GetVARID:KSFAM_M2OS:
//  \endif
extern int TM_Application_GetVARID(object_type_t object_type,unsigned short application_type, unsigned short *var_id);

/*! @brief This function modify printer contrast.
 * @param prnt : PRINTER handle (result of fopen call)
 * @param darkness : Contrast :
 * - PRINTER_INTENSITY_NORMAL (70%)
 * - PRINTER_INTENSITY_HIGH (85%)
 * - PRINTER_INTENSITY_EXTRAHIGH (100%)
 * - others (100%+(darkness*3)%)
 * @return
 * - 0 if no error. Else :
 * - -1 if function doesn't exist
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
//  \if SIMULATION
//  @GSIM_F:TM_Printer_AdjustIntensity:KSFAM_M2OS:
//  \endif
extern int TM_Printer_AdjustIntensity(FILE*prnt,int darkness);

/*! @brief This function get printer contrast.
 * @param prnt : PRINTER handle (result of fopen call)
 * @param darkness : Contrast
 * @return
 * - 0 if no error. Else :
 * - -1 if function doesn't exist
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
//  \if SIMULATION
//  @GSIM_F:TM_Printer_GetIntensity:KSFAM_M2OS:
//  \endif
extern int TM_Printer_GetIntensity(FILE *prnt,int *darkness);

/*! @brief This function put terminal in power down mode.
 * @return 
 * -  0 if error occured
 *
 * @note 
 * the peripheral "POWER" must be closed before calling this function
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
//  \if SIMULATION
//  @GSIM_F:TM_EnterPowerDownMode:KSFAM_M2OS:
//  \endif
extern int TM_EnterPowerDownMode(void);

#endif
/*! @} **/

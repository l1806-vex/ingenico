/*! @addtogroup KSFAM_PPS_MANAGER
	* @{
**/
 
#ifndef PINPAD_H
#define PINPAD_H

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function returns the PPS version
 * @return The PPS version
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 13) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_Version:KSFAM_PPS_MANAGER:
// \endif
extern int           PPS_Version              (void);



/*! @brief This routine clears the display and sets the cursor on the first line at the first position.
 * @return None 
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_firstline:KSFAM_PPS_MANAGER:
// \endif
extern void          PPS_firstline            (void);


/*! @brief This routine clears the current line of the display.
 * @return None 
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 8) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_clearline:KSFAM_PPS_MANAGER:
// \endif
extern void          PPS_clearline            (void);


/*! @brief The next line becomes the current line of display.
 * @return None 
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 7) if function does not exist
 * @note When the current line is the latest one, PPS_newline has no effect.
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_newline:KSFAM_PPS_MANAGER:
// \endif
extern void          PPS_newline              (void);



/*! @brief This routine resets PPS.
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  PPS_Reset:KSFAM_PPS_MANAGER:
// \endif
extern int           PPS_Reset                (void);


/*! @brief This routine displays a message on current line.
 * @param message : pointer to message to be displayed (ASCII string from 1 up to 16 characters length, no Carriage Return required).
 * @return 0 if ok
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 11) if function does not exist
 * @note PPS_display calls are forbidden when a numeric (or a function) entry has been started and is in progress.
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_Display:KSFAM_PPS_MANAGER:
// \endif
extern int           PPS_Display              (char             *message);


/*! @brief This function starts a numeric entry with parameters set up and time out.
 * @param tabEntry : pointer to structure TAB_ENTRY_STRING.
 * @return None
 * @note This is the standard keying, if requested echo is done on each striked key at the specified column then the cursor is automatically right shifted. 
 *
 * - Yellow key is used to erase the last character entered. 
 * - Red key aborts the keying. 
 * - Green key sends the key to the buffer and ends the keying. 
 * - The key buffer ( green key not included ) has to be read with PPS_Read_Entry routine after the ENTRY_PPAD event has been received. 
 *
 *	If Minkeys is equal to Maxkeys, the keying will wait for the specified number of characters. 
 *	Keying ends when time-out elapses or green key is entered or Maxkeys+1 keys are entered or when less than 4 digits are entered. 
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  PPS_Num_Entry:KSFAM_PPS_MANAGER:
//  1:ONE_POINTER
// \endif
extern void          PPS_Num_Entry            (TAB_ENTRY_STRING *tabEntry);


/*! @brief This function starts function keys entry with parameters set up.
 * @param tabEntry : pointer to structure TAB_ENTRY_FCT.
 * - mask : key mask enabling or disabling the different awaited keys .
 * - MASK_F_PPAD 0x4000 F 
 * - MASK_ANN_PPAD 0x2000 Red 
 * - MASK_CORR_PPAD 0x1000 Yellow not available 
 * - MASK_VAL_PPAD 0x0800 Green 
 * - MASK_VIRGULE_PPAD 0x0400 Comma 
 * - MASK_ETOILE_PPAD 0x0200 * 
 * - MASK_SK1_PPAD 0x0100 F1 
 * - MASK_SK2_PPAD 0x0080 F2 
 * - MASK_SK3_PPAD 0x0040 F3 
 * - MASK_SK4_PPAD 0x0020 F4 
 * - time-out : in seconds ( 0 means no time-out, Max 255 seconds ) .
 *
 * @return None.
 * @note This is a key by key entry, no echo is done. The key buffer ( containing only one key ) has to be read with PPS_Read_Entry after the ENTRY_PPAD event has been received . 
 *
 * Keying ends when time-out elapses or when a key is entered. 
 *
 * This routine has to be used when one function key is awaited. 
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  PPS_Fct_Entry:KSFAM_PPS_MANAGER:
//  1:ONE_POINTER
// \endif
extern void          PPS_Fct_Entry            (TAB_ENTRY_FCT    *tabEntry);


/*! @brief This function is used to get the result of keying when numeric or function key entry has been previously requested through PPS_Num_Entry or PPS_Fct_Entry routines. 
 * @param buffer : pointer to structure BUFFER_SAISIE.
 * @return
 * 
 * @c return code of the keying process 
 * - CR_ENTRY_PINPAD_OK keying is OK ( numeric or function entry ) .
 * - CR_ENTRY_PINPAD_NOK : too much chars entered or entry error on numeric entry never 
 *
 * @c returned on function key entry .
 * - CR_ENTRY_PINPAD_CANCEL : red key entered on numeric or pin code entry .
 * - CR_ENTRY_PINPAD_TIME_OUT : time-out elapsed .
 * - CR_ETRYE_PINPAD_FCT :function key entered on numeric or pin code entry never 
 *
 * @c returned on function key entry .
 * - CR_ENTRY_PINPAD_IN_PROGRESS : keying in progress .
 * - CR_ENTRY_PINPAD_VALIDATED : green key only entered on numeric entry .
 * - CR_ENTRY_PINPAD_BREAK : keying entry stopped by PPS_Stop_Entry 
 *
 * @note keys buffer is significant when return code is : 
 * - CR_ENTRY_PINPAD_OK 
 * - CR_ENTRY_PINPAD_NOK 
 * - CR_ENTRY_PINPAD_CANCEL ( red key given only ) 
 * - CR_ENTRY_PINPAD_VALIDATED ( green key given only ) 
 * - CR_SAISIE_PINPAD_FCT ( function key given only ) 
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  PPS_Read_Entry:KSFAM_PPS_MANAGER:
//  1:ONE_POINTER
// \endif
extern unsigned char PPS_Read_Entry           (ENTRY_BUFFER    *buffer);


/*! @brief This function stops a previously started entry
 * @return None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  PPS_Stop_Entry:KSFAM_PPS_MANAGER:
// \endif
extern void          PPS_Stop_Entry           (void);


/*! @brief This routine starts a numeric entry with parameters set up and time out.
 * @param tabEntry : pointer to structure TAB_ENTRY_STRING_PPAD.
 * @return None 
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 17) if function does not exist
 * @note This is the standard keying, if requested echo is done on each striked key at the specified column then the cursor is automatically right shifted. 
 * - Yellow key is used to erase the last character entered. 
 * - Red key aborts the keying. 
 * - Green key sends the key to the buffer and ends the keying. 
 *
 *	The key buffer ( green key not included ) has to be read with PPS_Read_Entry routine after the ENTRY_PPAD event has been received. 
 *
 *	If Minkeys is equal to Maxkeys, the keying will wait for the specified number of characters. 
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_Num_Entry_T:KSFAM_PPS_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          PPS_Num_Entry_T          (TAB_ENTRY_STRING_PPAD *tabEntry);


/*! @brief This function sets the com format
 * @param Speed : Number of bits per second
 * @param ByteLen : Data bits length (7 or8)
 * @param Parity : PARITY (0) or NO_PARITY(1)
 * @param ParityType : ODD (1) or EVEN (0)
 * @return : 
 * - RET_PP_OK (0).
 * - negative value if function failed.
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_SetComFormat:KSFAM_PPS_MANAGER:
// \endif
extern int           PPS_SetComFormat         (int Speed,unsigned char ByteLen,unsigned char Parity,unsigned char ParityType);


/*
 For PP10 & phase 0 compatibility...
 */
#define       PPS10_firstline          PPS_firstline
#define       PPS10_clearline          PPS_clearline
#define       PPS10_newline            PPS_newline
#define       PPS10_Reset              PPS_Reset
#define       PP10_Display             PPS_Display
#define       PPS10_Display            PPS_Display
#define       send_message_pinpad      PPS_Display
#define       PP10_Display             PPS_Display
#define       PP10_Num_Entry           PPS_Num_Entry
#define       PP10_Fct_Entry           PPS_Fct_Entry
#define       PP10_Read_Entry          PPS_Read_Entry
#define       PP10_Stop_Entry          PPS_Stop_Entry
#define       PP30_Num_Entry_T         PPS_Num_Entry_T

#define       PinPadDll_version        PPS_Dll_Version


/*! @brief This function resets pinpad device
 * @return 
 * - RET_PP_OK (0)
 * - RET_PP_KO (1)
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 10) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:reset_pinpad:KSFAM_PPS_MANAGER:
// \endif
extern int           reset_pinpad             (void);


/*! @brief This function clears the display.
 * @return None
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 14) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_clear_display:KSFAM_PPS_MANAGER:
// \endif
extern unsigned char PPS_clear_display        (void);


/*! @brief This function tests if pinpad is connected
 * @return RET_PP_OK if pinpad is connected.
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 15) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:IsPPSConnected:KSFAM_PPS_MANAGER:
// \endif
extern int           IsPPSConnected           (void);


/*! @brief This function Stop pinpad PIN entry task
 * @return None
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PP30_KillTaskSaisiePpad:KSFAM_PPS_MANAGER:
// \endif
extern void          PP30_KillTaskSaisiePpad  (void);

/*! @brief This function stops PPS PIN entry
 * @return RET_PP_OK if successful
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 18) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_SendCancelCommand:KSFAM_PPS_MANAGER:
// \endif
extern int           PPS_SendCancelCommand            (void);



/*! @brief This function is used to get the information of the pinpad's software.
 * @param Reference : reference of the pinpad's software (output).
 * @param Version : version of the pinpad's software (output).
 * @return RET_PP_OK if successful
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 22) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_SendSoftwareReferenceCommand:KSFAM_PPS_MANAGER:
//  @GSIM_A:1:DATA_SIZE(9)
//  @GSIM_A:2:DATA_SIZE(7)
// \endif
extern int           PPS_SendSoftwareReferenceCommand (unsigned char *Reference, unsigned char *Version);


/*! @brief This function is used to get pinpad reference
 * @param Reference : pinpad reference (output)
 * @return RET_PP_OK if successful
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_SendTerminalRefRequestCommand:KSFAM_PPS_MANAGER:
//  @GSIM_A:Reference:DATA_SIZE(17)
// \endif
extern int           PPS_SendTerminalRefRequestCommand(unsigned char *Reference);



/*! @brief This function is used to print the diagnostic of a pinpad.
 * @return None
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 26) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_print_diagnostic:KSFAM_PPS_MANAGER:
// \endif
extern void          PPS_print_diagnostic             (void);


/*! @brief This function must be called to avoid the display of the french warning message "Saisissez votre code a l'abri des regards indiscrets", that is automatically displayed on pin entry. 
 *
 * Once this function has been called , the french warning message is no more displayed until next reset of the EFT30. 
 * @return None
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 28) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:ClearFrenchWarningDisplay:KSFAM_PPS_MANAGER:
// \endif
extern void          ClearFrenchWarningDisplay        (void);


/*! @brief This function is useful any time the pincode entered on PPR/PPC has to be transferred to the EFT30 crypto processor, for pin presentation in case of PPC, or for pin encryptation using an EFT30 key. 
 *
 *	The transfer is encrypted. 
 * @return The length of the transferred PIN or negative value in case of error
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 30) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:TransfertToBooster:KSFAM_PPS_MANAGER:
// \endif
extern int           TransfertToBooster(void);



/*! @brief This function is used to get security level of a pinpad
 * @param NiveauSecurite : 2 octets
 * - '8' '0' Standard Security Level
 * - '8' '1' PEDS Security Level
 * - '8' '2' ZKA Security Level
 *
 * @return
 * - RET_PP_OK (0) if the security level can be found.
 * - RET_PP_KO (-1) otherwise.
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPR_niveau_securite:KSFAM_PPS_MANAGER:
//  @GSIM_A:1: DATA_SIZE(2)
// \endif
extern int           PPR_niveau_securite(unsigned char * NiveauSecurite);


/*! @brief This function stops using of pinpad
 * @return RET_PP_OK
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPR_EndSysPPR:KSFAM_PPS_MANAGER:
// \endif
extern int           PPR_EndSysPPR(void);


/*! @brief This function is used to get the serial number
 * @param serial : serial number of pinpad (length 8+1)
 * @param product: product reference of pinpad (length 8+1)
 * @return RET_PP_OK (0) if successful.
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPR_GetSerialNumber:KSFAM_PPS_MANAGER:
// \endif
extern int           PPR_GetSerialNumber(char *serial/* 8+1 */,char *product/*8+1*/);


/*! @brief This function is used to test if pinpad is connected
 * @return RET_PP_OK if pinpad is connected
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPR_FastIsConnected:KSFAM_PPS_MANAGER:
// \endif
extern int           PPR_FastIsConnected(void);

#define PINPAD_STATE_UNKNOWN     0  /*!< Pinpad activated state is unknown*/
#define PINPAD_STATE_ACTIVATED   1  /*!< Pinpad activated state is activated*/
#define PINPAD_STATE_DEACTIVATED 2  /*!< Pinpad activated state is desactivated*/

/*! @brief This function is used to test if pinpad is activated
 * @return PINPAD_STATE_ACTIVATED if pinpad is activated (only for BOOSTERII)
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 40) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPR_GetActivationState:KSFAM_PPS_MANAGER:
// \endif
extern int PPR_GetActivationState(void);

/*! @brief Read the systeme and manager version of an emulated pinpad like IPP3xx
* @return
*   RET_PP_OK if successful
*   RET_PP_KO 
*
* @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPS_GetSoftwareConfig:KSFAM_PPS_MANAGER:
// \endif
extern int  PPS_GetSoftwareConfig(unsigned char thunder_pack[20], unsigned char manager_pack[20]);

/*! @brief This function start the entry task pinpad
 * @return 
 *   RET_PP_OK                    (0)
 *   RET_PP_KO                    (1)
 *   RET_PP_DISCONNECT           (-24) 
 *   RET_PP_BAD_SOFT_VERSION     (-25) DLL PPS only
 *   RET_PP_BAD_REFERENCE        (-26) DLL PPS only
 *   RET_PP_BAD_DOMAIN           (-27) DLL PPS only
 *   RET_PP_BAD_KEY               (-28) DLL PPS only
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:InitSysSaisiePpad:KSFAM_PPS_MANAGER:
// \endif
extern int           InitSysSaisiePpad        (void);

/*! @brief This function start the entry task pinpad
 * @param type_pinpad : type pinpad connected
 * @return 
 *   RET_PP_OK                    (0)
 *   RET_PP_KO                    (1)
 *   RET_PP_DISCONNECT           (-24) 
 *   RET_PP_BAD_SOFT_VERSION     (-25) DLL PPS only
 *   RET_PP_BAD_REFERENCE        (-26) DLL PPS only
 *   RET_PP_BAD_DOMAIN           (-27) DLL PPS only
 *   RET_PP_BAD_KEY               (-28) DLL PPS only
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 29) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:InitSysPpad:KSFAM_PPS_MANAGER:
// \endif
extern int           InitSysPpad              (int type_pinpad);

extern void          Saisie_Numerique_Ppad    (TAB_ENTRY_STRING *tab_numerique);
extern unsigned char Read_Saisie_Ppad         (BUFFER_SAISIE    *buf_saisie_ppad);
extern void          Stop_Saisie_Ppad         (void);
extern void          Saisie_Fonction_Ppad     (TAB_ENTRY_FCT    *tab_fonction);
extern int           EstDllReader             (void);

#define PPR_SecurityLevel             PPR_niveau_securite
#define PPS_ClearFrenchWarningDisplay ClearFrenchWarningDisplay
#define PPS_Reset                     reset_pinpad
#define PPS_Num_Entry                 Saisie_Numerique_Ppad
#define PPS_Read_Entry                Read_Saisie_Ppad
#define PPS_Stop_Entry                Stop_Saisie_Ppad
#define PPS_Fct_Entry                 Saisie_Fonction_Ppad
#define PPS_Dll_Open                  pinpadlib_open
#define PPS_Dll_init                  InitDLLSaisiePpad
#define PPS_DLLReader                 EstDllReader


/*! @} **/

#endif



/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifndef _STATUS_H
#define _STATUS_H


/*
======================================================================
					List of Defines
======================================================================
*/
#define SET_DISPONIBILITY       0
#define SET_CAM_STATE           1
#define SET_CALL_STATE          2
#define SET_M2OS_STATE          3

#define M2OS_STATE_OK           0
#define M2OS_STATE_NOK          1

#define CAM_STATE_REMOVED       0
#define CAM_STATE_INSERTED      1

#define CALL_STATE_NO_CALL      0
#define CALL_STATE_COLLECTING   1
#define CALL_STATE_PARAMETRING  2

#define M2OS_STATE_OK           0

#define SET_STATUS_OK              0 /* OK                      */
#define SET_STATUS_UNKNOW_INDEX    1 /* Index Unknown           */
#define SET_STATUS_UNKNOW_VALUE    2 /* Value not accepted      */
#define SET_STATUS_DISABLED_VALUE  3 /* Value is not modifiable */



/*
======================================================================
			Data Structures Definition
======================================================================
*/


//Declaration des variables

/*! @brief Define the status type.*/
typedef struct
{
	int Disponibility;			/*!< Should be : \li available (0)  \li or not (1).*/
	int M2OSState;					/*!< current state of the automaton */
	int CamState;						/*!< card missing (0) or present (1). */
	int CallState;					/*!< in MPAV5  : State of the servers calls :  \li 0: neither tele-collection, nor tele-parameters  \li 1: tele-collection in progress \li 2: tele-parameters in progress.*/
  int Header;							/*!< Should be :  \li 0 : Redirection is displayed  \li 1 : Redirection is not displayed */
  int Redirection;				/*!< Should be :  \li 0 : Redirection is activated  \li 1 : Redirection is not activated */
  int HeaderActivated;		/*!< Should be :  \li 0 : Header is activated  \li 1 : Header is not activated */
} T_Status;	


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function returns the states of the peripheral devices defined in TStatus.
 * @param Val : States of the peripheral devices.
 * @return SET_STATUS_OK 
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 129) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetGeneralStatus:KSFAM_AUTRES_MANAGER:0x90
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int     GetGeneralStatus(T_Status *Val);


/*! @brief This function sets the states on the peripherics defined in TStatus.
 * @param Index : 
 * - SET_DISPONIBILITY 0
 * - SET_CAM_STATE 1
 * - SET_CALL_STATE 2
 * - SET_M2OS_STATE 3
 *
 * @param Value : 
 * - M2OS_STATE_OK 0
 * - M2OS_STATE_NOK 1
 * - CAM_STATE_REMOVED 0
 * - CAM_STATE_INSERTED 1
 * - CALL_STATE_NO_CALL 0
 * - CALL_STATE_COLLECTING 1
 * - CALL_STATE_PARAMETRING 2
 *
 * @return
 * - SET_STATUS_OK 0 : OK 
 * - SET_STATUS_UNKNOW_INDEX 1 : Index Unknown 
 * - SET_STATUS_UNKNOW_VALUE 2 : Value not accepted 
 * - SET_STATUS_DISABLED_VALUE 3 : Value is not modifiable
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 130) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetGeneralStatus:KSFAM_AUTRES_MANAGER:0x91
// \endif
extern int     SetGeneralStatus(int Index,int Value);


/*! @brief This function is used to get the cam0 status.
 * @return Status Cam0
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  GetStatusCam0:KSFAM_AUTRES_MANAGER:0x92
// \endif
extern STATUS GetStatusCam0(void);


#endif

/*! @} **/

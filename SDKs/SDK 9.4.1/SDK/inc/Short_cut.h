/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/
#ifndef SHORT_CUT_H
#define SHORT_CUT_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define SIZE_SHORT_CUT_DATA (32*1024)
#define SHORTCUT_OK             0
#define SHORTCUT_PB_MALLOC    -1
#define SHORTCUT_OVERRUN      -2
#define SHORTCUT_NO_SHORTCUT -3
#define SHORTCUT_NOT_FOUND   -4


/*
======================================================================
			Data Structures Definition
======================================================================
*/
typedef int (*PFONCSHORTCUT) (void);
typedef struct
{
  unsigned short appli_id;
  char short_cut[3+1];
  char name_short_cut[50+1];
  PFONCSHORTCUT       sap;
}Serv_short_cut_t;

typedef struct
{
  unsigned short appli_id;
  char           short_cut[3+1];
  MSGinfos       name_short_cut;
  PFONCSHORTCUT  sap;
}wServ_short_cut_t;

typedef struct
{
  unsigned short   appli_id;
  char            short_cut[3+1];
  int              name_short_cut;
  PFONCSHORTCUT sap;
  PFONCSHORTCUT fonc;  
}Serv_short_cut_register_t;

/*! @brief Register a list of shortcut
* @param number_of_short_cut : number of shortcut
* @param data : list of shortcut
* @return
* - SHORTCUT_OK           OK
* - SHORTCUT_PB_MALLOC    not enough memory
* - SHORTCUT_OVERRUN      too much shortcut
*  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 63) if function does not exist
// \if SIMULATION
//  @GSIM_F:ShortCutRegister:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:IN_ONLY
// \endif
*
* @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int ShortCutRegister ( unsigned int number_of_short_cut, Serv_short_cut_t *data);

/*! @brief Register a list of shortcut
//! \brief wShortCutRegister manage language,fonts and UNICODE messages
* @param number_of_short_cut : number of shortcut
* @param data : list of shortcut
* @return
* - SHORTCUT_OK           OK
* - SHORTCUT_PB_MALLOC    not enough memory
* - SHORTCUT_OVERRUN      too much shortcut
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 82) if function does not exist
// \if SIMULATION
//  @GSIM_F:wShortCutRegister:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:IN_ONLY
// \endif
*
* @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int wShortCutRegister ( unsigned int number_of_short_cut, wServ_short_cut_t *data);


/*! @brief Test if shortcut exist
* @param appli_id : appli id
* @param shortcut : shortcut to find
* @return
* - SHORTCUT_NOT_FOUND    not found
* - rank in shortcut table
*  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 64) if function does not exist
// \if SIMULATION
//  @GSIM_F:ShortCutGet:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:2:DATA_CODE(strlen(shortcut))
// \endif
*
* @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int ShortCutGet(unsigned short appli_id, char* shortcut);


/*! @brief remove a shortcut
* @param appli_id : appli id
* @param shortcut : shortcut to find
* @return
* - SHORTCUT_OK           OK
* - SHORTCUT_NOT_FOUND    not found
*  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 65) if function does not exist
// \if SIMULATION
//  @GSIM_F:ShortCutRemove:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:2:DATA_CODE(strlen(shortcut))
// \endif
*
* @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int ShortCutRemove(unsigned short appli_id, char* shortcut);


/*! @brief Call a shortcut
* @param appli_id : appli id
* @param shortcut : shortcut to find
* @param cr : return from shortcut function
* @return
* - SHORTCUT_OK           OK
* - SHORTCUT_NOT_FOUND    not found
*  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 66) if function does not exist
// \if SIMULATION
//  @GSIM_F:ShortCutCall:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:2:DATA_CODE(strlen(shortcut))
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
// \endif
*
* @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int ShortCutCall(unsigned short appli_id, char* shortcut,int *cr);


/*! @brief print list of manager shortcut
 *  @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 67) if function does not exist
// \if SIMULATION
//  @GSIM_F:ShortCutPrint:KSFAM_AUTRES_MANAGER:
// \endif
*
* @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
extern void ShortCutPrint(void);


#endif
/*! @} **/

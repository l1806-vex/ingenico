/*! @addtogroup KSFAM_ENTRY
 * @{
 **/

#ifndef SAISIE_H
#define SAISIE_H

/*
 ======================================================================
 List of Defines
 ======================================================================
 */
/*! @brief Define for Pinpad_List_Entry return.*/
#define CR_PINPAD_LIST_ENTRY_PINPAD_OK          0  /*!< Entry OK on pinpad*/
#define CR_PINPAD_LIST_ENTRY_PINPAD_ANNUL       1  /*!< Cancel on pinpad*/
#define CR_PINPAD_LIST_ENTRY_PINPAD_TIMEOUT     2  /*!< Timeout*/
#define CR_PINPAD_LIST_ENTRY_KEYBOARD_ANNUL     3  /*!< Cancel on keyboard*/
#define CR_PINPAD_LIST_ENTRY_NO_PINPAD          4  /*!< No pinpad activated*/

/*! @brief Define for Pinpad_Confirm_AID return.*/
#define CR_PINPAD_CONFIRM_AID_PINPAD_OK      0  /*!< Entry OK on pinpad*/
#define CR_PINPAD_CONFIRM_AID_PINPAD_ANNUL   1  /*!< Cancel on pinpad*/
#define CR_PINPAD_CONFIRM_AID_PINPAD_TIMEOUT 2  /*!< Timeout*/
#define CR_PINPAD_CONFIRM_AID_KEYBOARD_ANNUL 3  /*!< Cancel on keyboard*/
#define CR_PINPAD_CONFIRM_AID_NO_PINPAD      4  /*!< No pinpad activated*/

/*   definition des touches */
#define TC_SK1		    0x20
#define TC_SK2		    0x21
#define TC_SK3		    0x22
#define TC_SK4		    0x23
#define TC_FONCTION	    0x24
#define TC_ANNULATION	0x25
#define TC_CORRECTION	0x26
#define TC_VALIDATION	0x27
#define TC_POINT	    0x28
#define TC_SKHAUT	    0x29
#define TC_SKBAS	    0x30
#define TC_SKVAL	    0x31
#define TC_SKCLEAR	    0x32

/* comptes rendus de saisie */

#define CR_SAISIE_OK		    0
#define CR_SAISIE_NOK	    	1
#define CR_SAISIE_ANNUL		    2
#define CR_SAISIE_TIME_OUT	    3
#define CR_SAISIE_FCT 		    4
#define CR_SAISIE_EN_COURS      5
#define CR_SAISIE_VAL           6
#define CR_SAISIE_ARRET         7
#define CR_SAISIE_SK1    		8
#define CR_SAISIE_SK2    		9
#define CR_SAISIE_SK3    		10
#define CR_SAISIE_SK4    		11
#define CR_SAISIE_HAUT   		12
#define CR_SAISIE_BAS    		13

/*  definitions de valeurs courantes des parametres*/

#define MINUTE  	60
#define NO_TIME_OUT	0
#define NO_ECHO		0
#define ECHO_NORMAL	1
#define ECHO_SPECIAL	2
#define ECHO_STANDARD 3
#define TAB_STANDARD    0

#define CAR_SECRET      '*'
#define ELVEC(x)       (sizeof(x) / sizeof(x[0]))

/*
 ======================================================================
 Data Structures Definition
 ======================================================================
 */

/*! @brief Define the format of a table for a numerical entry.*/
typedef struct {
	word mask; /*!< entry mask*/
	byte time_out; /*!< entry time out*/
	byte line; /*!< line where the entry will be displayed*/
	byte column; /*!< column where the entry will be displayed*/
	byte echo; /*!< character to display in echo on each entry characters*/
	byte nb_max; /*!< maximum count of entry characters*/
	byte nb_min; /*!< minimum count of entry characters*/
} TAB_ENTRY_STRING;

/*! @brief Define a pointer on a function called for navigation.*/
typedef int (*PFONCNAVI)(void);

/*! @brief Define a navigation list.*/
typedef struct {
	int itemlabel; /*!< item of the concerned label*/
	PFONCNAVI function; /*!< function call for navigation.*/
} NavigationListe;

/*! @brief Format of an entry table for navigation.*/
typedef struct {
	char *itemlabel; /*!< name of the item*/
	char *shortcommand; /*!< shortcut _ON_ or _OFF_ */
	char level; /*!< 1...*/
	PFONCNAVI function; /*!< function called for navigation.*/
} NavigationItems;

/*! @brief This type is a pointer on a function.*/
typedef int (*CTRL)(void);
#define NB_ELT_LISTE 101

/*! @brief Format of an entry table for graphic list entry.*/
typedef struct {
	int left; /*!< in pixels*/
	int top; /*!< in pixels*/
	int rigth; /*!< in pixels*/
	int bottom; /*!< in pixels*/
	int nblines; /*!< window lines number */
	int fontsize; /*!< Font size : \li _SMALL_ \li _MEDIUM_ \li _LARGE_ */
	int type; /*!< Font type : \li _PROPORTIONNEL_ \li _NORMALE_ */
	int police; /*!< font, should be 0 */
	int correct; /*!< process correction key ? _ON_ or _OFF_ */
	int offset; /*!< table index for selection */
	int shortcommand; /*!< shortcut ? _ON_ or _OFF_ */
	int selected; /*!< display a predefined item */
	int thickness; /*!< window border thickness */
	int border; /*!< border ? _ON_ or _OFF_ */
	int popup; /*!< save and restore screen ? _ON_ or _OFF_ */
	int first; /*!< first item of the list */
	int current; /*!< pre selected item if selected is _ON_ */
	int time_out; /*!< time out in seconds*/
	unsigned char *titre; /*!< NULL no title*/
} StructFenetre;

/*! @brief Structure describing a list.*/
// @GSIM_T:StructListe:SUPPLIED(BUF_SER_StructListe;BUF_DES_StructListe) 
typedef struct {
	StructFenetre Fenetre; /*!< structure describing the window.*/
	unsigned char *tab[NB_ELT_LISTE]; /*!< item list NULL terminated */
} StructListe;

/*! @brief Format of the entry table for an alphanumerical entry.*/
// @GSIM_T:TAB_ENTRY_ALPHA:SUPPLIED(BUF_SER_TAB_ENTRY_ALPHA;BUF_DES_TAB_ENTRY_ALPHA)  */
typedef struct {
	word mask; /*!< entry mask*/
	byte time_out; /*!< entry time out */
	byte line; /*!< number of line*/
	byte column; /*!< number of column*/
	byte echo; /*!< character to display in echo on each entry characters*/
	byte nb_max; /*!< maximum count of entry characters*/
	byte nb_min; /*!< minimum count of entry characters*/
	byte *tab_caracteres; /*!< entry characters*/
} TAB_ENTRY_ALPHA;

/*! @brief Format of the entry table for a Function Key entry.*/
typedef struct {
	word mask; /*!< mask*/
	byte time_out; /*!< time out value*/
} TAB_ENTRY_FCT;

/*! @brief Format of the entry table for an amount entry.*/
typedef struct {
	word mask; /*!< mask*/
	byte time_out; /*!< time out value*/
} TAB_ENTRY_AMOUNT;

/*! @brief Define the entry buffer.*/
typedef struct {
	byte nombre; /*!< data length.*/
	byte donnees[50]; /*!< data of the buffer.*/
} BUFFER_SAISIE;

//entry return codes

#define CR_ENTRY_OK				0		/*!< Successful entry. d_entry[0] contains the index of the selected item in the list for G_List_Entry d_len contains the entry length d_entry [50] contains the entry for G_Numerical_Entry . */
#define CR_ENTRY_NOK		    1		/*!< Correction (if authorised ) */
#define CR_ENTRY_CANCEL		    2		/*!< Entry Cancelled */
#define CR_ENTRY_TIME_OUT	    3		/*!< Timeout elapsed  */
#define CR_ENTRY_FCT 		    4		/*!< F key pushed (if authorised )  */
#define CR_ENTRY_IN_PROGRESS  	5		/*!< Entry in progress*/
#define CR_ENTRY_VALIDATED   	6		/*!< Entry validated*/
#define CR_ENTRY_BREAK       	7		/*!<  Entry break*/
#define CR_ENTRY_SK1    	 	8		/*!< SK1 ('1' on EFT930M or ML30) key pushed (if authorised ) */
#define CR_ENTRY_SK2    		9		/*!< SK2 ('2' on EFT930M or ML30) key pushed (if authorised ) */
#define CR_ENTRY_SK3    		10		/*!< SK3 ('3' on EFT930M or ML30) key pushed (if authorised ) */
#define CR_ENTRY_SK4    		11		/*!< SK4 ('4' on EFT930M or ML30) key pushed (if authorised )  */

/*! @brief Define value WGUI for mask field */
#define WGUI_MASK_IP 0x8001
#define WGUI_MASK_BINARY 0x8002
/*! @brief Define value for mask field */
#define MASK_NUM           0x8000
#define MASK_NUMERIQUE     0x8000
#define MASK_F             0x4000 			/*!< 'F' Key             */
#define MASK_FONCTION      0x4000 			/*!< 'F' Key             */
#define MASK_ANN           0x2000 			/*!< Red Key             */
#define MASK_ANNULATION    0x2000 			/*!< Red Key             */
#define MASK_CORR          0x1000 			/*!< Yellow Key          */
#define MASK_CORRECTION    0x1000 			/*!< Yellow Key          */
#define MASK_VAL           0x0800 			/*!< Green Key           */
#define MASK_VALIDATION    0x0800 			/*!< Green Key           */
#define MASK_DOT           0x0400 			/*!< '.' Key             */
#define MASK_POINT         0x0400 			/*!< '.' Key             */
#define MASK_SK1           0x0200 			/*!< F1 key              */
#define MASK_SK2           0x0100 			/*!< F2 key              */
#define MASK_SK3           0x0080 			/*!< F3 key              */
#define MASK_SK4           0x0040 			/*!< F4 key              */
#define MASK_SKVAL         0x0020 			/*!< OK key              */
#define MASK_ALPHA         0x0020 			/*!< Alphanumerical mode */
#define MASK_SKCORR        0x0010 			/*!< C key               */
#define MASK_DATE          0x0008 			/*!< DATE format         */
#define MASK_TIME          0x0004 			/*!< TIME key            */
#define MASK_HEURE         0x0004 			/*!< TIME key            */
#define MASK_UP            0x0002 			/*!< UP key              */
#define MASK_HAUT          0x0002 			/*!< UP key              */
#define MASK_DOWN          0x0001 			/*!< DOWN key            */
#define MASK_BAS           0x0001 			/*!< DOWN key            */

#define CGUI_ITEMS_LIST_NUMBER       20
#define CGUI_ITEMS_LARGE_LIST_NUMBER 101
#define ITEMS_LIST_NUMBER      101
/*! \brief Format of an entry table for gaphic list entry.*/
/* @GSIM_T:StructWindow:DATA_CODE(sizeof(StructWindow))  */
typedef struct {
	int left; /*!< in pixels */
	int top; /*!< in pixels */
	int rigth; /*!< in pixels */
	int bottom; /*!< in pixels */
	int nblines; /*!< window lines number */
	int fontsize; /*!< Font size : \li _SMALL_ \li _MEDIUM_ \li _LARGE_  */
	int type; /*!< Font type : \li _PROPORTIONNEL_ \li _NORMALE_  */
	int font; /*!< font, should be 0  */
	int correct; /*!< process correction key ? _ON_ or _OFF_  */
	int offset; /*!< table index for selection  */
	int shortcommand; /*!< shortcut ? _ON_ or _OFF_  */
	int selected; /*!< display a predefined item  */
	int thickness; /*!< window border thickness  */
	int border; /*!< border ? _ON_ or _OFF_  */
	int popup; /*!< save and restore screen ? _ON_ or _OFF_  */
	int first; /*!< first item of the list  */
	int current; /*!< pre selected item if selected is _ON_  */
	int time_out; /*!< time out in seconds */
	unsigned char *title; /*!< NULL no title */
} StructWindow;

/*! @brief Structure describing a list.*/
// @GSIM_T:StructList:DATA_CODE(sizeof(StructList))
typedef struct {
	StructWindow MyWindow; /*!< structure describing the window.*/
	unsigned char *tab[ITEMS_LIST_NUMBER]; /*!< item list the last item must be equal to PT_NULL */
} StructList;

/*! @brief Define the entry buffer.*/
typedef struct {
	byte d_len; /*!< data length.*/
	byte d_entry[50]; /*!< data of the buffer.*/
} ENTRY_BUFFER;

/*! @brief This type is a pointer on a function called in function calling tables.*/
typedef void (*PFONCSUP)(void);

/*! @brief This structure is used to create calling tables for functions.*/
typedef struct {
	char *Name; /*!< name of the function.*/
	PFONCSUP fonc; /*!< function to call.*/
} FCT_SUP;

/*
 ======================================================================
 Functions Definition
 ======================================================================
 */

/*! @brief This function is used to navigating in a list and select an item within a window on a PINPAD; 
 *  if return is not CR_PINPAD_LIST_ENTRY_PINPAD_OK, Indice is initialized with (LabelNumber+1)
 *	This function uses the graphic library capabilities. It starts an entry system task. 
 *  This function display message MESS184 on terminal display.
 *  timeout value is 4mn
 * @param LabelList        : List of label
 * @param LabelNumber      : Number of label
 * @param Indice           : Rank into list when entry OK
 * @param WaitForKeyboard  : Wait for cancel on keyboard if TRUE
 * @return
 *   CR_PINPAD_LIST_ENTRY_PINPAD_OK
 *   CR_PINPAD_LIST_ENTRY_PINPAD_ANNUL
 *   CR_PINPAD_LIST_ENTRY_PINPAD_TIMEOUT
 *   CR_PINPAD_LIST_ENTRY_KEYBOARD_ANNUL
 *   CR_PINPAD_LIST_ENTRY_NO_PINPAD
 * @par exit (EXIT_DLL_EMVSQ + 3) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Pinpad_List_Entry:KSFAM_ENTRY:0x100
// \endif
extern unsigned char Pinpad_List_Entry(T_LABEL *LabelList,
		unsigned char LabelNumber, unsigned char *Indice, int WaitForKeyboard);

/*! @brief This function is used to confirm AID value on PINPAD; 
 *	This function uses the graphic library capabilities. It starts an entry system task. 
 *  This function display message MESS185 on terminal display.
 *  timeout value is 1mn
 * @param aid              : label of AID (16+1)
 * @param WaitForKeyboard  : Wait for cancel on keyboard if TRUE
 * @return
 *   CR_PINPAD_CONFIRM_AID_PINPAD_OK
 *   CR_PINPAD_CONFIRM_AID_PINPAD_ANNUL
 *   CR_PINPAD_CONFIRM_AID_PINPAD_TIMEOUT
 *   CR_PINPAD_CONFIRM_AID_KEYBOARD_ANNUL
 *   CR_PINPAD_CONFIRM_AID_NO_PINPAD
 * @par exit (EXIT_DLL_EMVSQ + 4) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Pinpad_Confirm_AID:KSFAM_ENTRY:0x100
// \endif
extern unsigned char Pinpad_Confirm_AID(unsigned char *aid,
		int WaitForKeyboard);

/*! @brief This function is used to confirm AID value on TERMINAL; 
 *	This function uses the graphic library capabilities. It starts an entry system task. 
 *  timeout value is 1mn
 * @param aid              : label of AID (16+1)
 * @return
 *   CR_ENTRY_VALIDATED
 *   CR_ENTRY_CANCEL
 *   CR_ENTRY_TIME_OUT
 * @par exit (EXIT_DLL_EMVSQ + 6) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Terminal_Confirm_AID:KSFAM_ENTRY:0x100
// \endif
extern unsigned char Terminal_Confirm_AID(unsigned char *aid);

/*! @brief This function is used to navigating in a list and select an item within a window on TERMINAL 
 *  if return is not CR_ENTRY_VALIDATED Indice is initialized with (LabelNumber+1)
 *	This function uses the graphic library capabilities. It starts an entry system task. 
 *  timeout value is 4mn
 * @param LabelList        : List of label
 * @param LabelNumber      : Number of label
 * @param Indice           : Rank into list when entry OK
 * @return
 *   CR_ENTRY_OK
 *   CR_ENTRY_CANCEL
 *   CR_ENTRY_TIME_OUT
 * @par exit (EXIT_DLL_EMVSQ + 5) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Terminal_List_Entry:KSFAM_ENTRY:0x100
// \endif
extern unsigned char Terminal_List_Entry(T_LABEL *LabelList,
		unsigned char LabelNumber, unsigned char *Indice);

/*! @brief This function is used to start navigating in a list and select an item within a window; 
 *
 *	This routine uses the graphic library capabilities. It starts an entry system task. 
 *	Application has to wait for the event ENTRY then it can get the entry using Get_Entry .
 * @param table : Graphic context
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 8) if function does not exist
 *
 *	@section test_G_List_Entry

 * @include saisie_Sample_01.c
 *
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_List_Entry:KSFAM_ENTRY:0x41
//  @GSIM_S:G_List_Entry:E_G_Saisie_Liste
// \endif
extern void G_List_Entry(StructListe *table);

/*! @brief This function allows to enter a numerical entry within a window. 
 *
 *	This routine starts an entry system task. Application has to wait for the event ENTRY , then it can get the entry using Get_Entry 
 * @param menu : see G_List_Entry.
 * - Fields nblines, shortcommand, selected, current, time_out aren't significant. 
 * - Field title contains the title of the windows
 *   displayed at top of windows centered with police in font field 
 * - The field tab[0] contains a string specifying the first line to display on the window. 
 *   displayed behind title and centered using police in field fonttype
 * - The field tab[1] contains the predefined value to enter.
 *   displayed at line and column coordinates using police in field fonttype
 * - The field tab[2] contains a string specifying a comment inside the predefined value.
 *   displayed behind predefined value and centered using police in field fonttype
 * - The field tab[3] contains a string specifying a comment inside the predefined value.
 *   displayed behind field tab[2] and centered using police in field fonttype
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * - Fields line et column are in pixels 
 * - Fields mask contain the list of key allowed 
 *    MASK_F            for 'F' key
 *    MASK_DOT          for '.' key
 *    MASK_SK1          for F1 key
 *    MASK_SK2          for F2 key
 *    MASK_SK3          for F3 key
 *    MASK_SK4          for F4 key
 *    MASK_DATE         for date format of entry "../../...."
 *    MASK_TIME         for time format en entry "..:..:.."
 *    MASK_UP           for UP key
 *    MASK_DOWN         for DOWN key
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 6) if function does not exist
 *
 *	@section test_G_Numerical_Entry

 * @include saisie_Sample_02.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Numerical_Entry:KSFAM_ENTRY:0x42
//  @GSIM_S:G_Numerical_Entry:E_G_Saisie_Numerique
// \endif
extern void G_Numerical_Entry(StructListe *menu, TAB_ENTRY_STRING *table);

/*! @brief This function allows to enter an alphanumerical entry within a window. 
 *
 *	This routine starts an entry system task. Application has to wait for the event ENTRY , then it can get the entry using Get_Entry .
 * @param menu : see G_List_Entry.
 * - Field title contains the title of the windows
 *   displayed at top of windows centered with police in font field 
 * - The field tab[0] contains a string specifying the first line to display on the window. 
 *   displayed behind title and centered using police in field fonttype
 * - The field tab[1] contains the predefined value to enter.
 *   displayed at line and column coordinates using police in field fonttype
 * - The field tab[2] contains a string specifying a comment inside the predefined value.
 *   displayed behind predefined value and centered using police in field fonttype
 * - The field tab[3] contains a string specifying a comment inside the predefined value.
 *   displayed behind field tab[2] and centered using police in field fonttype
 * @param table : pointer to TAB_ENTRY_ALPHA structure.
 * - Fields line et column are in pixels 
 * - Fields mask contain the list of key allowed 
 *   MASK_F        'F' key
 *   MASK_SK1      F1 key
 *   MASK_SK2      F2 key
 *   MASK_SK3      F3 key
 *   MASK_SK4      F4 key
 *   MASK_ALPHA    Alphanumerical mode 
 * - Field tab_caracteres contains allowed characters
 * - Fields time_out contains the timeout in seconds
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 7) if function does not exist
 *
 *	@section test_G_Alphanumerical_Entry

 * @include saisie_Sample_03.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Alphanumerical_Entry:KSFAM_ENTRY:0x47
//  @GSIM_S:G_Alphanumerical_Entry:E_G_Saisie_Alphanumerique
// \endif
extern void G_Alphanumerical_Entry(StructListe *menu, TAB_ENTRY_ALPHA *table);

/*! @brief The function allows to enter the function keys. 
 *
 *	This routine starts an entry system task in the graphic context.
 * @param menu : see G_List_Entry.
 * - Fields nblines, shortcommand, selected, current, time_out aren't significant. 
 * - Field title contains the title of the windows
 *   displayed at top of windows centered with police in font field 
 * - The field tab[0] contains a string specifying the first line to display on the window. 
 *   displayed behind title and centered using police in field fonttype
 * - The field tab[1] contains a string specifying the second line to display on the window. 
 *   displayed behind first line and centered using police in field fonttype
 * - The field tab[2] contains a string specifying the third line  to display on the window.
 *   displayed behind second line and centered using police in field fonttype
 * - The field tab[3] contains a string specifying the fourth line to display on the window.
 *   displayed behind field tab[2] and centered using police in field fonttype
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * - Fields line, column, echo, nb_max, nb_min aren't significant. 
 * - Fields mask contains the Mask of the authorized keys.
 *    MASK_F             'F' Key
 *    MASK_ANN           Red Key
 *    MASK_CORR          Yellow Key
 *    MASK_VAL           Green Key
 *    MASK_DOT           '.' Key
 *    MASK_SK1           F1 key 
 *    MASK_SK2           F2 key
 *    MASK_SK3           F3 key
 *    MASK_SK4           F4 key
 *    MASK_SKVAL         OK key
 *    MASK_SKCORR        C key
 *    MASK_UP            ARROW UP key
 *    MASK_DOWN          DOWN ARROW key
 * - Fields time_out contains the timeout in seconds
 *
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 15) if function does not exist
 *
 *	@section test_G_Fct_Entry

 * @include saisie_Sample_04.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Fct_Entry:KSFAM_ENTRY:0x93
//  @GSIM_S:G_Fct_Entry:E_G_Saisie_Fonction
// \endif
extern void G_Fct_Entry(StructListe *menu, TAB_ENTRY_STRING *table);

/*! @brief The function allows to enter the function keys. 
 *
 *	This routine starts an entry system task.
 * @param table : 
 * Field mask contains Mask of the authorized keys
 *    MASK_F             'F' Key
 *    MASK_ANN           Red Key
 *    MASK_CORR          Yellow Key
 *    MASK_VAL           Green Key
 *    MASK_DOT           '.' Key
 *    MASK_SK1           F1 key 
 *    MASK_SK2           F2 key
 *    MASK_SK3           F3 key
 *    MASK_SK4           F4 key
 *    MASK_SKVAL         OK key
 *    MASK_SKCORR        C key
 *    MASK_UP            ARROW UP key
 *    MASK_DOWN          DOWN ARROW key
 * - Fields time_out contains the timeout in seconds
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 2) if function does not exist
 *
 *	@section test_Fct_Entry

 * @include saisie_Sample_05.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Fct_Entry:KSFAM_ENTRY:0x43
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:IN_ONLY
// \endif
extern void Fct_Entry(TAB_ENTRY_FCT *table);

/*! @brief This function allows to enter a numerical entry within a window. 
 *
 *	This routine starts an entry system task. Application has to wait for the event ENTRY , then it can get the entry using Get_Entry 
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * - Fields mask contain the list of key allowed 
 *    MASK_F            for 'F' key
 *    MASK_DOT          for '.' key
 *    MASK_SK1          for F1 key
 *    MASK_SK2          for F2 key
 *    MASK_SK3          for F3 key
 *    MASK_SK4          for F4 key
 *    MASK_DATE         for date format of entry "../../...."
 *    MASK_TIME         for time format en entry "..:..:.."
 *    MASK_UP           for UP key
 *    MASK_DOWN         for DOWN key
 * - Fields time_out contains the timeout in seconds
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 0) if function does not exist
 *
 *	@section test_Numerical_Entry

 * @include saisie_Sample_06.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Numerical_Entry:KSFAM_ENTRY:0x44
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:IN_ONLY
// \endif
extern void Numerical_Entry(TAB_ENTRY_STRING *table);

/*! @brief This function allows to enter an alphanumerical entry within a window. 
 *
 *	This routine starts an entry system task. Application has to wait for the event ENTRY , then it can get the entry using Get_Entry .
 * @param table : pointer to TAB_ENTRY_ALPHA structure.
 * - Fields mask contain the list of key allowed 
 *   MASK_F        'F' key
 *   MASK_SK1      F1 key
 *   MASK_SK2      F2 key
 *   MASK_SK3      F3 key
 *   MASK_SK4      F4 key
 *   MASK_ALPHA    Alphanumerical mode 
 * - Field tab_caracteres contains allowed characters
 * - Fields time_out contains the timeout in seconds
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 1) if function does not exist
 *
 *	@section test_Alphanumerical_Entry

 * @include saisie_Sample_07.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Alphanumerical_Entry:KSFAM_ENTRY:0x45
//  @GSIM_S:Alphanumerical_Entry:E_Saisie_Alphanumerique
//  GSIM_A:1:ONE_POINTER
//  GSIM_A:1:IN_ONLY
// \endif
extern void Alphanumerical_Entry(TAB_ENTRY_ALPHA *table);

/*! @brief This function allows to enter an amount.
 * @param table : mask of the authorized keys, and entry timeout.
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 3) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Saisie_Montant:KSFAM_ENTRY:0x46
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:IN_ONLY
// \endif
extern void Saisie_Montant(TAB_ENTRY_AMOUNT *table);

/*! @brief This function allows entry of the amount for a defined display.
 * @param table : structure of the amount entry.
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 4) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Saisie_Seuil:KSFAM_ENTRY:0x4C
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:IN_ONLY
// \endif
extern void Saisie_Seuil(TAB_ENTRY_AMOUNT *table);

/*! @brief This function stops the entry.
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Stop_Entry:KSFAM_ENTRY:0x4F
// \endif
extern void Stop_Entry(void);

/*! @brief This function is used to get the result of an entry previously started by G_List_Entry or G_Numerical_Entry or G_numerical_Entry assuming that ENTRY event already occured. 
 *
 * Check the return code first and then read data stored in ENTRY_BUFFER.
 * @param buf : Pointer to structure ENTRY_BUFFER.
 * @return 
 * - CR_ENTRY_OK : Successful entry. d_entry[0] contains the index of the selected item in the list for G_List_Entry d_len contains the entry length d_entry [50] contains the entry for G_Numerical_Entry .
 * - CR_ENTRY_NOK : Correction (if authorised ) 
 * - CR_ENTRY_TIME_OUT : Timeout elapsed 
 * - CR_ENTRY_CANCEL : Entry Cancelled 
 * - CR_ENTRY_VALIDATED : Green key (confirmation) 
 * - CR_ENTRY_FCT : F key pushed (if authorised ) 
 * - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised ,only for numerical and alphanumerical entry) 
 * - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised ,only for numerical and alphanumerical entry)
 * - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised ,only for numerical and alphanumerical entry)
 * - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised ,only for numerical and alphanumerical entry)
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 5) if function does not exist
 *
 *  @par Example:
 *	@section test_Get_Entry

 * @include saisie_Sample_08.c
 *
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Get_Entry:KSFAM_ENTRY:0x40
//  @GSIM_A:1:ONE_POINTER
// \endif
extern unsigned char Get_Entry(ENTRY_BUFFER * buf);

/*! @brief This function manages application menus and sub-menus using standard navigation system.
 * @param timeout : character wait time-out expressed in units of 10 ms.
 * @param no_appli : identifiant of the called application.
 * @param No : Menu level to be displayed at the top of the list with respect to the beginning of the table;  0=top of list.
 * @param Nb : Number of items in the navigation table.
 * @param Table : Navigation table.
 * @return
 * - CR_ENTRY_OK			Correct entry, selection is significant 
 * - CR_ENTRY_CANCELLED	Cancel key entered
 * - CR_ENTRY_NOK			Syntax error in navigation table
 * - CR_ENTRY_TIME_OUT		Time-out elapsed
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 10) if function does not exist
 *
 * @note 
 * - Each menu must have a name. This name must not exceed 12 characters. If it does, the string will be truncated to 12. 
 * - The depth of the tree is limited to 9. The tree levels must have the following continuity patterns: the difference in level between 
 two consecutive menus must be +1, 0 or -1. Within the limit of the number of items entered as a parameter, no item must have a level below that of the first item.
 * - Level 0 does not exist.
 *
 *  @par Example:
 *
 *	This example illustrates a manager menu tree. Note that Navigate returns leaves number only.
 *
 *	@section test_Navigate

 * @include saisie_Sample_09.c
 *
 *	Whatever the current level, the  ('.' on EFT930-B) key [1] is used to print the menus of the same  level as well as the tree structure starting from the current level. 
 *	For that reason, printer peripheral must be closed before calling Navigate routine.
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:Navigate:KSFAM_ENTRY:0xC4
//  @GSIM_S:Navigate:E_SaisieOperation
// \endif
extern unsigned char Navigate(unsigned short timeout, unsigned char no_appli,
		int *No, int Nb, NavigationItems *Table);

/*! @brief This function is the start of the entry task.
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 13) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:InitSysSaisie:KSFAM_ENTRY:0x4B
// \endif
extern void InitSysSaisie(void);
/*! @} **/

/*! @addtogroup KSFAM_USQ
 * @{
 */

/*! @brief This function displays a choice selection.
 * @param fd      : handle of the screen
 * @param **table : list of the choices
 * @param *nb     : number of choices
 * @param *debut  : pointer on the first choice
 * @param *indice : choice selected send back to the application
 * @param *cr     : report send back to the application
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:SLSQ_Affichage_choix:KSFAM_USQ:0x1E
//  @GSIM_S:SLSQ_Affichage_choix:E_SLSQ_Affichage_choix
// \endif
extern void SLSQ_Affichage_choix(FILE *fd, char **table, unsigned char *nb,
		unsigned char *debut, unsigned char *indice, unsigned char *cr);
/*! @} **/

/*! @addtogroup KSFAM_PPS_MANAGER
 * @{
 */

/*! @brief This function displays a list of items.
 * @param table : pointer on StructList (structure of the screen).
 * @return None
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 14) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Aff_Liste_Ppr:KSFAM_PPS_MANAGER:0x30
//  @GSIM_S:G_Aff_Liste_Ppr:E_G_Aff_Liste_Ppr
// \endif
extern void G_Aff_Liste_Ppr(StructListe *table);
/*! @} **/

/*! @addtogroup KSFAM_ENTRY
 * @{
 */

/*! @brief This function displays a list of items.
 * @param table : structure of the screen.
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 18) if function does not exist
 * @note  
    * - Please advice that you have to do a "ttestall(ENTRY, 0)" after calling G_Aff_liste. 
    * - This is the same behavior that for the function G_Fct_Entry (an example is available). 
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Aff_Liste:KSFAM_ENTRY:0x4A
//  @GSIM_S:G_Aff_Liste:E_G_Aff_Liste
// \endif
extern void G_Aff_Liste(StructListe *table);

/*! @brief This function initializes the screen.
 * @param Menu : Parameters of the window.
 * @param line : position of the cursor (Y)
 * @param column : position of the cursor (X)
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Init:KSFAM_ENTRY:0x4D
//  @GSIM_S:G_Init:E_G_Init
// \endif
extern void G_Init(StructListe *Menu, unsigned char line, unsigned char column);

/*! @brief This function allows to enter an alpha-numerical entry within a window using a friendly entry screen. 
 * @param menu : see G_List_Entry
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * - Fields nblines, shortcommand, selected, current, time_out aren't significant. 
 * - Field tab[0] is not used
 * - Field tab[1] contains the predefined string value to enter. 
 * - Field tab[2] is not used
 *
 * @return None 
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 17) if function does not exist
 *
 *  @par Example:

 * @include saisie_Sample_10.c
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:G_Extended_entry:KSFAM_ENTRY:0x49
//  @GSIM_S:G_Extended_entry:E_G_Saisie_Etendue
// \endif
extern void G_Extended_entry(StructListe *menu, TAB_ENTRY_STRING *table);

/*! @brief Format of an entry table for gaphic list entry.*/
// @GSIM_T:wStructFenetre:DATA_CODE(sizeof(wStructFenetre)) 
typedef struct {
	int left; /*!< in pixels*/
	int top; /*!< in pixels*/
	int rigth; /*!< in pixels*/
	int bottom; /*!< in pixels*/
	int nblines; /*!< window lines number */
	int fontsize; /*!< Font size _SMALL_ or _MEDIUM_ or _LARGE_ */
	int type; /*!< Font type _PROPORTIONNEL_ or _NORMALE_ */
	int police; /*!< font, should be 0 */
	int correct; /*!< process correction key ? _ON_ or _OFF_ */
	int offset; /*!< table index for selection */
	int shortcommand; /*!< shortcut ? _ON_ or _OFF_ */
	int selected; /*!< display a predefined item */
	int thickness; /*!< window border thickness */
	int border; /*!< border ? _ON_ or _OFF_ */
	int popup; /*!< save and restore screen ? _ON_ or _OFF_ */
	int first; /*!< first item of the list */
	int current; /*!< pre selected item if selected is _ON_ */
	int time_out; /*!< time out in seconds*/
	//unsigned char *titre;        /* */
	MSGinfos titre; /*!< NULL no title*/
} wStructFenetre;

/*! @brief Structure describing a list (using MSGinfos).*/
// @GSIM_T:wStructListe:DATA_CODE(sizeof(wStructListe)) 
typedef struct {
	wStructFenetre Fenetre; /*!< structure describing the window.*/
	MSGinfos tab[NB_ELT_LISTE]; /*!< item list NULL terminated */
} wStructListe;

/*! @brief Format of an entry table for gaphic list entry.*/
// @GSIM_T:wStructWindow:DATA_CODE(sizeof(wStructWindow))
typedef struct {
	int left; /*!< in pixels*/
	int top; /*!< in pixels*/
	int rigth; /*!< in pixels*/
	int bottom; /*!< in pixels*/
	int nblines; /*!< window lines number */
	int fontsize; /*!< Font size _SMALL_ or _MEDIUM_ or _LARGE_ */
	int type; /*!< Font type _PROPORTIONNEL_ or _NORMALE_ */
	int font; /*!< font, should be 0 */
	int correct; /*!< process correction key ? _ON_ or _OFF_ */
	int offset; /*!< table index for selection */
	int shortcommand; /*!< shortcut ? _ON_ or _OFF_ */
	int selected; /*!< display a predefined item */
	int thickness; /*!< window border thickness */
	int border; /*!< border ? _ON_ or _OFF_ 	*/
	int popup; /*!< save and restore screen ? _ON_ or _OFF_ */
	int first; /*!< first item of the list */
	int current; /*!< pre selected item if selected is _ON_ */
	int time_out; /*!< time out in seconds*/
	MSGinfos title; /*!< NULL no title*/
} wStructWindow;

#define CGUI_COMPLIANT_MANAGER

/*! @brief Structure describing a list (using MSGinfos)*/
// @GSIM_T:wStructList:DATA_CODE(sizeof(wStructList)) 
typedef struct {
	wStructWindow MyWindow; /*!< structure describing the window.*/
	MSGinfos tab[ITEMS_LIST_NUMBER]; /*!< item list NULL terminated */
} wStructList;

typedef struct {
	char *file_directory;
	char *name_icon; //!< pointer to the icon name
} IconList;

typedef struct {
	char *page_html; //!< page directory
	MSGinfos title; //!< NULL no title
	MSGinfos footer_left; //!< NULL no footer_left
	MSGinfos footer_center; //!< NULL no footer_center
	MSGinfos footer_right; //!< NULL no footer_right
	IconList List[CGUI_ITEMS_LIST_NUMBER]; //!< item list NULL terminated
	MSGinfos tab[CGUI_ITEMS_LIST_NUMBER]; //!< item list NULL terminated
	int time_out; //!< time out in milli seconds
	int key_dot; //!< enable or disable
	int key_correction; //!< enable or disable
	int key_base; //!< first item value, -1 if none
	int ruf[254];
} wIconList;

typedef struct {
	char *page_html; //!< page directory
	MSGinfos title; //!< NULL no title
	MSGinfos footer_left; //!< NULL no footer_left
	MSGinfos footer_center; //!< NULL no footer_center
	MSGinfos footer_right; //!< NULL no footer_right
	IconList List[CGUI_ITEMS_LARGE_LIST_NUMBER]; //!< item list NULL terminated
	MSGinfos tab[CGUI_ITEMS_LARGE_LIST_NUMBER]; //!< item list NULL terminated
	int time_out; //!< time out in milli seconds
	int key_dot; //!< enable or disable
	int key_correction; //!< enable or disable
	int key_base; //!< first item value, -1 if none
	int ruf[254];
} wLargeIconList;

typedef struct {
	char *page_html; //!< page directory
	MSGinfos title; //!< NULL no title
	int current; //!< pre selected item if selected is _ON_
	MSGinfos tab[CGUI_ITEMS_LIST_NUMBER]; //!< item list NULL terminated
	IconList Icon[CGUI_ITEMS_LIST_NUMBER]; //!< item list NULL terminated
	MSGinfos footer_left; //!< NULL no footer_left
	MSGinfos footer_center; //!< NULL no footer_center
	MSGinfos footer_right; //!< NULL no footer_right
	int full_screen; //!< no icon in list
	int time_out; //!< time out in milli seconds
	int key_correction; //!< enable or disable
	int multi_sel; //!< enable more than one selection in a list
	int key_base; //!< first item value, -1 if none
	int key_selected; //!< dialog with radio button
	int key_dot; //!< enable or disable
	int ruf[252];
} cGuiStructList;

typedef struct {
	char *page_html; //!< page directory
	MSGinfos title; //!< NULL no title
	int current; //!< pre selected item if selected is _ON_
	MSGinfos tab[CGUI_ITEMS_LARGE_LIST_NUMBER]; //!< item list NULL terminated
	IconList Icon[CGUI_ITEMS_LARGE_LIST_NUMBER]; //!< item list NULL terminated
	MSGinfos footer_left; //!< NULL no footer_left
	MSGinfos footer_center; //!< NULL no footer_center
	MSGinfos footer_right; //!< NULL no footer_right
	int full_screen; //!< no icon in list
	int time_out; //!< time out in milli seconds
	int key_correction; //!< enable or disable
	int multi_sel; //!< enable more than one selection in a list
	int key_base; //!< first item value, -1 if none
	int key_selected; //!< dialog with radio button
	int key_dot; //!< enable or disable
	int ruf[252];
} cGuiLargeStructList;

typedef struct {
	char *page_html; //!< page directory
	MSGinfos title; //!< NULL no title
	MSGinfos footer_left; //!< NULL no footer_left
	MSGinfos footer_right; //!< NULL no footer_right
	MSGinfos current_value; //!< default value
	byte echo; //!< character to display in echo on each entry characters
	word mask; //!< entry mask
	int time_out; //!< time out in milli seconds
	int nb_char_max; /*!< maximum count of entry characters*/
	int nb_char_min; /*!< minimum count of entry characters*/
	MSGinfos message_1; //!< message to guide the entry
	int ruf[250];
} cGuiStructEntry;

/*! @brief Use this constant to select html page for keying entry  
 * with cGUI_Numerical_Entry, cGUI_Extended_Entry or cGUI_Alphanum_Entry
 * manager routines
 *
 * cGuiStructEntry wGuiEntryMenu;
 * ...
 * {
 * ...
 * wGuiEntryMenu.page_html=(char*)entry_directory;
 * ...
 * }
 * ...
 *
 */
extern const char entry_directory[];

/*! @brief Use this constant to select html page for list entry  
 * with cGUI_List_Entry or cGUI_Aff_Liste manager routines
 *
 * cGuiStructEntry wGuiEntryMenu;
 * cGuiStructList wGuiMenu;
 * ...
 * {
 * ...
 * wGuiMenu.page_html=(char*)page_list;
 * ...
 * }
 * ...
 *
 */
extern const char page_navi[];

/*! @brief Use this constant to select html page for list entry  
 * with cGUI_Icon_List routine
 *
 * wIconList wIcon;
 * ...
 * {
 * ...
 * wIcon.page_html=(char*)page_navi;
 * ...
 * }
 * ...
 */
extern const char page_list[];

/*! @brief Start Navigating in a list and select an item within a window; this routine 
 * - uses the graphic library capabilities.
 * - This routine starts an entry system task. Application has to wait for the event ENTRY,
 * - then it can get the entry using Get_Entry .
 * -brief wG_List_Entry manage language,fonts and UNICODE messages
 * @param table : Graphic context
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 21) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_List_Entry:KSFAM_ENTRY:
//  @GSIM_S:wG_List_Entry:E_wG_Saisie_Liste
// \endif
extern void wG_List_Entry(wStructListe *table);

/*! @brief This function allows to enter a numerical entry within a window. This routine 
 * - starts an entry system task. Application has to wait for the event ENTRY , then it can
 * -  get the entry using Get_Entry
 * - \brief wG_Numerical_Entry manage language,fonts and UNICODE messages
 * @param menu : see wG_List_Entry.
 * - Fields nblines, shortcommand, selected, current, time_out aren't significant.
 * -Fields line et column are in pixels
 * - Field title contains the title of the windows
 *   displayed at top of windows centered with police in font field
 * - The field tab[0] contains a string specifying the first line to display on the window.
 *   displayed above predefined value and centered using police in field fonttype
 * - The field tab[1] contains the predefined value to enter.
 *   displayed at line and column coordinates using police in field fonttype
 * - The field tab[2] contains a string specifying a comment inside the predefined value.
 *   displayed behind predefined value and centered using police in field fonttype
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 20) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Numerical_Entry:KSFAM_ENTRY:
//  @GSIM_S:wG_Numerical_Entry:E_wG_Numerical_Entry
// \endif
extern void wG_Numerical_Entry(wStructListe *menu, TAB_ENTRY_STRING *table);

/*! @brief This Function allows to enter an alphanumerical entry within a window. This routine 
 * - starts an entry system task. Application has to wait for the event ENTRY , then it can
 * - get the entry using Get_Entry .
 * -  wG_Alphanumerical_Entry manage language,fonts and UNICODE messages
 * @param menu : see wG_List_Entry.
 * - nblines, shortcommand, selected, current, time_out aren't significant.
 * - Field title contains the title of the windows
 *   displayed at top of windows centered with police in font field
 * - The field tab[0] contains a string specifying the first line to display on the window.
 *   displayed above predefined value and centered using police in field fonttype
 * - The field tab[1] contains the predefined value to enter.
 *   displayed at line and column coordinates using police in field fonttype
 * - The field tab[2] contains a string specifying a comment inside the predefined value.
 *   displayed behind predefined value and centered using police in field fonttype
 * @param table : pointer to TAB_ENTRY_ALPHA structure.
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 22) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Alphanumerical_Entry:KSFAM_ENTRY:
//  @GSIM_S:wG_Alphanumerical_Entry:E_wG_Saisie_Alphanumerique
// \endif
extern void wG_Alphanumerical_Entry(wStructListe *menu,TAB_ENTRY_ALPHA *table);

/*! @brief This function initialize the screen.
 * - wG_Init manage language,fonts and UNICODE messages
 * @param Menu : Parameters of the window.
 * @param line : position of the cursor (Y)
 * @param column : position of the cursor (X)
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Init:KSFAM_ENTRY:
//  @GSIM_S:wG_Init:E_wG_Init
// \endif
extern void wG_Init(wStructListe *Menu, unsigned char line,
		unsigned char column);

/*! @brief This function allows to enter an alpha-numerical entry within a window using a friendly entry screen. 
 * - brief wG_Extended_entry manage language,fonts and UNICODE messages
 * @param menu : see wG_List_Entry
 * @param table : pointer to TAB_ENTRY_STRING structure.
 * - Fields nblines, shortcommand, selected, current, time_out aren't significant.
 * - Field tab[0] is not used
 * - Field tab[1] contains the predefined string value to enter. 
 * - Field tab[2] is not used
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 24) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Extended_entry:KSFAM_ENTRY:
//  @GSIM_S:wG_Extended_entry:E_wG_Saisie_Etendue
// \endif
extern void wG_Extended_entry(wStructListe *menu, TAB_ENTRY_STRING *table);

/*! @brief Display a list of items.
 * - wG_Aff_Liste manage language,fonts and UNICODE messages
 * @param table : pointer on StructList (structure of the screen).
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Aff_Liste:KSFAM_ENTRY:
//  @GSIM_S:wG_Aff_Liste:E_wG_Aff_Liste
// \endif
extern void wG_Aff_Liste(wStructListe *table);

/*! @brief The function allows to enter the function keys. 
 * - wG_Fct_Entry manage language,fonts and UNICODE messages
 * - This routine starts an entry system task in the graphic context.
 * @param menu : Graphic context.
 * - Field title contains the title of the windows
 *   displayed at top of windows centered with police in font field 
 * - The field tab[0] contains a string specifying the first line to display on the window. 
 *   displayed above second line and centered using police in field fonttype
 * - The field tab[1] contains a string specifying the second line to display on the window. 
 *   displayed at line and column coordinates using police in field fonttype
 * - The field tab[2] contains a string specifying the third line  to display on the window.
 *   displayed behind second line and centered using police in field fonttype
 * @param table : pointer to TAB_ENTRY_STRING structure.
 *
 * @link KSFAM_ENTRY Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Fct_Entry:KSFAM_ENTRY:
//  @GSIM_S:wG_Fct_Entry:E_wG_Saisie_Fonction
// \endif
extern void wG_Fct_Entry(wStructListe *menu, TAB_ENTRY_STRING *table);
/*! @} **/

/*! @addtogroup KSFAM_PPS_MANAGER
 * @{
 */

/*! @brief Display a list of items on PINPAD.
 * - wG_Aff_Liste_Ppr manage language,fonts and UNICODE messages
 * @param table : pointer on StructList (structure of the screen).
 * @par exit (EXIT_DLL_SAISIE_NOT_INITIALIZED + 26) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:wG_Aff_Liste_Ppr:KSFAM_PPS_MANAGER:
//  @GSIM_S:wG_Aff_Liste_Ppr:E_wG_Aff_Liste_Ppr
// \endif
extern void wG_Aff_Liste_Ppr(wStructListe *table);

/*! @} **/

/*! @addtogroup KSFAM_CGUI
 * @{
 */


////////////////////////////////////////////////////////////////////////////
// Fonctions PSQ : English / French pb
////////////////////////////////////////////////////////////////////////////

//!see \ref G_Extended_entry
extern void G_Saisie_Etendue(StructListe *p0, TAB_ENTRY_STRING *p1);
//!see \ref wG_Extended_entry
extern void wG_Saisie_Etendue(wStructListe *p0, TAB_ENTRY_STRING *p1);
//!see \ref G_List_Entry
extern void G_Saisie_Liste(StructListe *p0);
//!see \ref wG_List_Entry
extern void wG_Saisie_Liste(wStructListe *p0);
//!see \ref G_Numerical_Entry
extern void G_Saisie_Numerique(StructListe *p0, TAB_ENTRY_STRING *p1);
//!see \ref wG_Numerical_Entry
extern void wG_Saisie_Numerique(wStructListe *p0, TAB_ENTRY_STRING *p1);
//!see \ref wG_Alphanumerical_Entry
extern void wG_Saisie_Alphanumerique(wStructListe *p0, TAB_ENTRY_ALPHA *p1);
//!see \ref G_Alphanumerical_Entry
extern void G_Saisie_Alphanumerique(StructListe *p0, TAB_ENTRY_ALPHA *p1);
//!see \ref G_Fct_Entry
extern void G_Saisie_Fonction(StructListe *menu, TAB_ENTRY_STRING *table);
//!see \ref Numerical_Entry
extern void Saisie_Numerique(TAB_ENTRY_STRING *p0);
//!see \ref Alphanumerical_Entry
extern void Saisie_Alphanumerique(TAB_ENTRY_ALPHA *p0);
//!see \ref Fct_Entry
extern void Saisie_Fonction(TAB_ENTRY_FCT *p0);
//!see \ref Stop_Entry
extern void Stop_Saisie(void);
//!see \ref Navigate
extern unsigned char SaisieOperation(unsigned short timeout,
		unsigned char no_appli, int *No, int Nb, NavigationItems *Table);
//!see \ref Get_Entry
extern unsigned char Read_Saisie(BUFFER_SAISIE *p0);
//!see \ref wG_Fct_Entry
extern void wG_Saisie_Fonction(wStructListe *menu, TAB_ENTRY_STRING *table);

/*! \cond NON_VISIBLE */
#define G_Extended_entry(p0,p1)        G_Saisie_Etendue((StructListe *)p0,(TAB_ENTRY_STRING *)p1)
#define wG_Extended_entry(p0,p1)       wG_Saisie_Etendue((wStructListe *)p0,(TAB_ENTRY_STRING *)p1)
#define G_List_Entry(p0)               G_Saisie_Liste( (StructListe * )p0)
#define wG_List_Entry(p0)              wG_Saisie_Liste( (wStructListe * )p0)
#define G_Numerical_Entry(p0,p1)       G_Saisie_Numerique((StructListe *)p0,(TAB_ENTRY_STRING *)p1)
#define wG_Numerical_Entry(p0,p1)      wG_Saisie_Numerique((wStructListe *)p0,(TAB_ENTRY_STRING *)p1)
#define wG_Alphanumerical_Entry(p0,p1) wG_Saisie_Alphanumerique((wStructListe *)p0,(TAB_ENTRY_ALPHA *)p1)
#define G_Alphanumerical_Entry(p0,p1)  G_Saisie_Alphanumerique((StructListe *)p0,(TAB_ENTRY_ALPHA *)p1)
#define wG_Fct_Entry(p0,p1)            wG_Saisie_Fonction((wStructListe *)p0,(TAB_ENTRY_STRING *)p1)
#define G_Fct_Entry(p0,p1)             G_Saisie_Fonction((StructListe *)p0,(TAB_ENTRY_STRING *)p1)
#define Numerical_Entry(p0)            Saisie_Numerique((TAB_ENTRY_STRING *)p0)
#define Alphanumerical_Entry(p0)       Saisie_Alphanumerique((TAB_ENTRY_ALPHA *)p0)
#define Fct_Entry(p0)                  Saisie_Fonction((TAB_ENTRY_FCT *)p0)
#define Stop_Entry                     Stop_Saisie
#define Navigate                       SaisieOperation
#define Get_Entry(p0)                  Read_Saisie ((BUFFER_SAISIE *)p0)
#define entrylib_open                  saisielib_open
/*!\endcond*/

/*! @} **/

#endif


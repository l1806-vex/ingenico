/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifndef SERVICESH
#define SERVICESH

#define EXTENS_NOT_IMPLEMENTED -1

/*
======================================================================
					List of Defines
==============================================================f========
*/
/* pour service SCL_Affichage_choix */
#define CHOIX_OK  0
#define CHOIX_KO  1
#define EXCEPTION 2

/* pour services SCL_Attente_carte, SCL_Attente_crtcli, SCL_Atttente_piste et SCL_Attente_puce */
#define CR_ATTPISTE_OK 0
#define CR_ATTPUCE_OK  1
#define CR_LECPISTE_KO 2
#define CR_ATTCARTE_KO 3
#define CR_ATTCARTE_AB 4
#define CR_TFCT        5
#define CR_CHEQUE_OK   6

/* pour service SLC_Afficher_montant */
#define MNT_CADRE 1

/* pour service SLC_Afficher */
#define ATTENDRE 1
#define WAITING  1

/* pour service SLC_Effacer_ligne */
#define DEBUT_LIGNE 1

/* pour le moteur d'etat : structure de la table */
#define FIN_TABLE 256

/* numeros exception */
/* de 1 a 29 */
#define E_SQ_REGISTER_MAILBOX         1
#define E_SQ_RESET_TERMINAL           2
#define E_SQ_ET_ACTIVATE              3
#define E_SQ_PB_DLLMALLOC             4
#define E_SQ_PB_PINPAD_AUTODETECT     5
#define E_SQ_PB_DEVICE_MODE           6


/*! @brief Define a pointer on a function to link with an event.
*/
typedef unsigned char (*PFONCEV)();

typedef struct
{
   short et_cou;									//!< state.
   unsigned char (*eta_cou)();						//!< state function.
   unsigned char evenement;							//!< event on calling exit.
   short et_sui;									//!< next state.
} TAB_EV;

#define CGUI_NOT_NEEDED 0  // Dont test CGUI possibility
#define CGUI_NEEDED     1  // Test CGUI possibility

#define CGUI_REFRESH    2  // Force refresh at PopCGUICOntext

#define CANVAS_NOT_USED  0 // Dont manage canvas
#define CANVAS_MAXIMIZE  1 // Maximize canvas on UserArea
#define CANVAS_RESIZE    2 // Resize with data of CGUI_CONTEXT_STRUCT

/*! @} **/

/*! @addtogroup KSFAM_CGUI
	* @{
**/

/*! @brief Define a display CGUI context
*/
typedef struct
{
  // CGUI Properties
  int CGUIStatus; // CGUI_NEEDED or CGUI_NOT_NEEDED
  // Header inhibition _PERIPH_ON or _PERIPH_OFF
  int HeaderStatus;
  // Footer inhibition _PERIPH_ON or _PERIPH_OFF
  int FooterStatus;
  // Leds inhibition _PERIPH_ON or _PERIPH_OFF
  int LedsStatus;
  // Canvas properties
  int CanvasStatus; //CANVAS_NOT_USE or CANVAS_MAXIMIZE or CANVAS_RESIZE
  // the x position in pixels on root screen
  int x;
  // the y position in pixels on root screen
  int y;
  // the window width in pixels
  int width;
  // the window height in pixels
  int height;
} CGUI_CONTEXT_STRUCT;

/*! @} **/

/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

/* pour le moteur d'etat */
#define ERREUR    255
#define SORTIE    128

/* choix d'un libelle */
#define CHOIX_SK1 0
#define CHOIX_SK4 1
#define CHOIX_SK2 2
#define CHOIX_SK3 3
#define CHOIX_SK1_SUITE 3
#define CHOIX_SK4_SUITE 2
#define CHOIX_SK2_SUITE 1
#define TOUCHE_SUITE TC_SK3

/* pour acces a la table des messages communs */
#define M_SUITE        0
#define M_RETRCARTE    1
#define M_LECTUREPISTE 2
#define M_ERREURLECTUR 3
#define M_INTRCARTE    4

#define SPY_TYPE    0xBB
/* pour ascbin, binasc */
#define MAX  0x7FFFFFFF 


/* custom messages */
#define CUSTOMIZED_MESSAGE 0
#define NO_CUSTOMIZED_MESSAGE 1


/*! @brief Define the possible choice table.*/
typedef TAB_ENTRY_FCT T_CHOIX_POSS [4];

/*bitmap symbol euro*/
#define SYMBOL_EURO 0x80
#define SYMBOL_EURO_DAX 0xA4



/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief Call InitVar to initialize pre-initialized variables at reset
*
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:InitVar:KSFAM_AUTRES_MANAGER:
// \endif
extern void          InitVar                  (void);

/*! @brief This function inhibits or restores the EFT930 header.
 * @param state : New state of the header\n 
 * - 0=to inhibit. 
 * - 1=to restore the header.
 * @return Previous state.
 * @par exit None
// \if SIMULATION
//  @GSIM_F:StateHeader:KSFAM_AUTRES_MANAGER:
// \endif
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int           StateHeader          (int state);


/*! @brief This function customizes the EFT930 header.
 * @param state : mask of header features.
 * - _SOCLE_STATE_ 0x0001 
 * - _BATT_STATE_ 0x0002 
 * - _NIV_RECEP_ 0x0004 
 * - _GPRS_STATE_ 0x0008 
 * - _APPLI_STATE_ 0x0010 
 * - __RTC_STATE_ 0x0020 
 * - __INTER_STATE__ 0x0040 INTER_STATE_: May be used to display an empty second line of the header (i.e. without DATE or without application name). 
 * - _ALL_STATE_ (_APPLI_STATE_ | _SOCLE_STATE_ | _BATT_STATE_ | _NIV_RECEP_ | _GPRS_STATE_ | _RTC_STATE_) .
 *
 * @return old mask : Don't forget to memorize this state to be able to give it when necessary .
 * @par exit None
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EventHeader:KSFAM_AUTRES_MANAGER:
// \endif
extern int           EventHeader          (int state);


/*! @brief This function reads the header position & header size.
 * @param Height : return the header Height.
 * @param Width  :  return the header Width.
 * @return
 * - 0 = header is at top of screen
 * - 1 = header is at the bottom of screen
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 200) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetHeaderSize:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
// \endif
extern int  GetHeaderSize(int *Height,int *Width);


/*! @brief This function saves the header position & header size.
 * @param Height : save the header Height.
 * @param Width :  save the header Width.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 201) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetHeaderSize:KSFAM_AUTRES_MANAGER:
// \endif
extern void SetHeaderSize(int Height,int Width);


/*! @brief This function saves the header position & header size.
 * @param Position : save the header position.
 * - 0 = top of screen
 * - 1 = bottom of screen
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 202) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetHeaderPosition:KSFAM_AUTRES_MANAGER:
// \endif
extern void SetHeaderPosition(int Position);


/*! @brief This function is used to get the screen area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 227) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetScreenArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:4:OUT_ONLY
// \endif
extern void GetScreenArea(int *left,int *top,int *right,int *bottom);


/*! @brief This function is used to get the header area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 227) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetScreenArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:4:OUT_ONLY
// \endif
extern int GetHeaderArea(int *left,int *top,int *right,int *bottom);


/*! @brief This function is used to get the LEDS area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 227) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetLedsArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:4:OUT_ONLY
// \endif
extern int GetLedsArea(int *left,int *top,int *right,int *bottom);


/*! @brief This function is used to get the user area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 54) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetUserArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern void GetUserArea(int *left,int *top,int *right,int *bottom);



/*! @brief Positionne les evenements pour la gestion du decroche
* - pour mettre a jour le bandeau du terminal
* @param etat_modem : MODEM_FIOCTL_RELAY_ONLINE
* -                     MODEM_FIOCTL_RELAY_OFFLINE
* @param etat_porteuse : MODEM_FIOCTL_CD_ON.
* -                        MODEM_FIOCTL_CD_OFF.
* @param nom : nom du reseau (si MODEM_FIOCTL_CD_ON).
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetModemEvent:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:3:DATA_CODE(strlen(nom))
//  @GSIM_A:3:IN_ONLY
// \endif
extern int           SetModemEvent        (int etat_modem,int etat_porteuse,char *nom);


/*! @brief Lit les evenements pour la gestion du decroche
* @param etat_modem : 
* - MODEM_FIOCTL_RELAY_ONLINE
* - MODEM_FIOCTL_RELAY_OFFLINE
* @param etat_porteuse : 
* - MODEM_FIOCTL_CD_ON.
* - MODEM_FIOCTL_CD_OFF.
* @param nom : name of the network (if MODEM_FIOCTL_CD_ON).
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetModemEvent:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
// \endif
extern int           GetModemEvent        (int *etat_modem,int *etat_porteuse,char *nom);


/*! @brief SetHeaderPosition save the header position & header size.
* @param Position : save the header position.
* -0= top of screen
* -1= bottom of screen
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 232) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetFooterPosition:KSFAM_AUTRES_MANAGER:
// \endif
extern void SetFooterPosition(int Position);


/*! @brief SetFooterKeyStatus set the status of a key into the footer
* @param FooterKey : Footer Key Id
*   FOOTER_KEY1
*   FOOTER_KEY2
*   FOOTER_KEY3
*   FOOTER_KEY4
* @param Status : _ON_,_OFF_.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 217) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetFooterKeyStatus:KSFAM_AUTRES_MANAGER:
// \endif
extern void SetFooterKeyStatus(int FooterKey,int Status);


/*! @brief SetFooterKeyBmp set the bitmap of a key into the footer
* @param FooterKey : Footer Key Id
*   FOOTER_KEY1
*   FOOTER_KEY2
*   FOOTER_KEY3
*   FOOTER_KEY4
* @param PtBmp : New bitmap for key.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 187) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetFooterKeyBmp:KSFAM_AUTRES_MANAGER:
// \endif
extern void SetFooterKeyBmp(int FooterKey,char *PtBmp);


/*! @brief SetFooterBmp sets the bitmap of the footer.\n
*   Used to put a single bitmap to fill all the area 
*   The size of Bitmap is limited by the size of the area of footer (GetFooterSize)
*   The image is put at relative (0,0) into footer area
*   (TouchScreen is not manage with single bitmap)
* @param PtBmp : New bitmap for area.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 128) if function does not exist
 *
 *	@section Sample SetFooterBMP

 * @include services_Sample_01.c
 *
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetFooterKeyBmp:KSFAM_AUTRES_MANAGER:
// \endif
void SetFooterBmp(char *PtBmp);


/*! @brief DisplayPincodeKeyboard display Pincode keyboard for Touch Screen display
*   Used before call a pincode scheme 
* @param Status : status of keyboard.
* - _ON_  = to display 
* - _OFF_ = to restore default footer
* @par exit none
* @return
* -  0  = Pincode keyboard not available for this terminal.
* -  1  = OK.
* - -1  = function not implemented
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayPincodeKeyboard:KSFAM_AUTRES_MANAGER:
// \endif
int DisplayPincodeKeyboard(int Status);


/*! @brief IsHeader returns the header state.
* @return
* -0=header is not displayed.
* -1=header is displayed.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsHeader:KSFAM_AUTRES_MANAGER:
// \endif
extern int           IsHeader             (void);

/*! @brief IsFooter returns the header state.
* @return
* -0=footer is not displayed.
* -1=footer is displayed.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsFooter:KSFAM_AUTRES_MANAGER:
// \endif
extern int            IsFooter(void);

/*! @brief SetHeaderAreaBmp sets the bitmap of an area into header
* @param HeaderArea : Area Id
* - HEADER_GPRS_AREA
* - HEADER_BT_AREA
* - HEADER_WIFI_AREA
* - HEADER_NETWORK_AREA
* @param PtBmp : New bitmap for key.
* @par exit(EXIT_DLL_COLOR_NOT_INITIALIZED + 132) if function does not exist
 *
 *	@section Sample SetHeaderBMP

 * @include services_Sample_02.c
 *
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetHeaderAreaBmp:KSFAM_AUTRES_MANAGER:
// \endif
extern void SetHeaderAreaBmp(int HeaderArea,char *PtBmp);

/*! @brief SetApplicationContext sets the context of an application before calling MORE_FUNCTION entry point
* @param HeaderStatus : Inhibit or not display header : _PERIPH_OFF or _PERIPH_ON \n
* @param FooterStatus : Inhibit or not display footer : _PERIPH_OFF or _PERIPH_ON \n
* @param LedsStatus : Inhibit or not display leds : _PERIPH_OFF or _PERIPH_ON \n
* @param typcode : application type
 * @return 1 if OK
* @par exit none.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetApplicationContext:KSFAM_AUTRES_MANAGER:
// \endif
extern int SetApplicationContext(int HeaderStatus,int FooterStatus,int LedsStatus,unsigned short typcode);

/*! @brief This function converts an ascii string into binary.
 * @param dest : destination
 * @param src : string to convert
 * @param ln : length of the string
 * @return 0 if OK
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 32) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Ascbin:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:DATA_SIZE(ln)
//  @GSIM_A:2:IN_ONLY
// \endif
extern int           Ascbin               (unsigned long *dest, unsigned char *src,int ln);


/*! @brief This function returns hexadecimal value for a character string (range 0x30 to 0x3F)
 * @param dest : pointer on the destination string.
 * @param src  : pointer on the original string.
 * @param ln : length of the string
 * @return 0 if ok 
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 33) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Aschex:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1: DATA_CODE(sizeof(dest))
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:DATA_SIZE(ln)
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:3:IN_ONLY
// \endif
extern int           Aschex               (unsigned char *dest , unsigned char  *src , int ln); 

/*! @brief This function converts an integer into an ASCII.
* @param dest : pointer to the string to return
* @param src  : integer to convert
* @param ln   : length of this string
* @return
* -0 if ok
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 34) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Binasc:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:DATA_SIZE(ln)
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:3:IN_ONLY
// \endif
extern int           Binasc               (unsigned char *dest, unsigned long src, int ln); 



/*! @brief This function converts an integer into an hexa.
* @param dest : pointer to the string to return
* @param src  : integer to convert
* @param ln   : length of this string
* @return
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 35) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
//! int 0 si OK
//! \note 
// \if SIMULATION
//  @GSIM_F:Binhex:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:DATA_SIZE(ln)
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:3:IN_ONLY
// \endif
extern int           Binhex               (unsigned char *dest , unsigned long src , int ln); 



/*! @brief This function converts a hexa string to an ascii one.
* @param dest : pointer to the output string
* @param src  : pointer to the input string
* @param ln   : length of the string.
* @return
* - 0 if OK
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 36) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Hexasc:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:DATA_CODE(ln * 2)
//  @GSIM_A:2:DATA_SIZE(ln)
// \endif
extern int           Hexasc               (unsigned char *dest , unsigned char *src , int ln); 




/*! @brief Display a choices selection.
* @param file : pointer on the screen's handle
* @param table : table of the choices
* @param name : name of the choices
* @param select : pointer on the selected choice
* @param choice: choice
* @param report : selection report.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 37) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Affichage_choix:KSFAM_VISU:
//  @GSIM_S:SLC_Affichage_choix:E_SLC_Affichage_choix
//  1:ONE_ADDRESS
//  3:DATA_SIZE(6)
//  4:DATA_SIZE(1)
//  5:DATA_SIZE(1)
//  6:DATA_SIZE(1)
// \endif
extern void          SLC_Affichage_choix  (FILE *file, char **table, unsigned char *name, unsigned char *select, unsigned char *choice, unsigned char *report);



/*! @brief Display a message on the screen.
* @param message : message to be displayed.
* @param option : * a r w 
* - r, w : for read and write
* - * : force the opening
* - a : the screen is not cleaned
* @param flag : wait or not after display.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 38) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Afficher:KSFAM_VISU:
// \endif
extern void          SLC_Afficher (char *message, char *option, unsigned char flag);




/*! @brief Display the amount.
* @param option : openning of the display peripheric
* @param amount (long): amount
* @param flag : forced to 1.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 39) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Afficher_montant:KSFAM_VISU:
// \endif
extern void          SLC_Afficher_montant (char          *option,MONTANT        amount,unsigned char  flag);




/*! @brief This function add N minutes to a date.
* @param increment : number of minutes to add
* @param date : date to set.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 40) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Ajoutermn:KSFAM_VISU:
//  @GSIM_A:2:ONE_POINTER
// \endif
extern void          SLC_Ajoutermn (unsigned int  increment,DATE *date);




/*! @brief Waits for an ISO2 stripe buffer.
* @param buffer_piste : data of the stripe.
* @return Returns the result or an error code :
* - CR_ATTPISTE_OK 0
* - CR_LECPISTE_KO 2
* - CR_ATTCARTE_KO 3
* - CR_ATTCARTE_AB 4
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 41) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Attente_carte:KSFAM_USQ:
// \endif
extern int           SLC_Attente_carte    (BUFFER_PISTE buffer_piste);




/*! @brief This function waits for an ISO2 stripe buffer and a chip
* @param buffer_piste : stripe data
* @return 
* - CR_ATTPISTE_OK 0
* - CR_ATTPUCE_OK 
* - CR_LECPISTE_KO 2
* - CR_ATTCARTE_KO 3
* - CR_ATTCARTE_AB 4
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 42) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Attente_crtcli:KSFAM_USQ:
// \endif
extern int           SLC_Attente_crtcli   (BUFFER_PISTE buffer_piste);




/*! @brief Clear the display
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 45) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Clear_display:KSFAM_USQ:
// \endif
extern void          SLC_Clear_display    (void);



/*! @brief Returns the number of days between date2 and date1.
* @param date1 : the first date
* @param date2 : the second date
* @return Number of days.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 46) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Ecart_date:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
extern int           SLC_Ecart_date       (DATE *date1, DATE *date2);




/*! @brief Returns the number of hour between date2 and date1.
* @param date1 : first date
* @param date2 : second date
* @return Number of minute.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 47) if function does not exist
 *
 * @note 
 * The DATE Fields (day, month, year) have no effect on the result.
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Ecart_heure:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
extern int           SLC_Ecart_heure      (DATE *date1, DATE *date2);




/*! @brief Clear a line on the display
* @param ligne : number of the line (0 or 1)
* @param position : position of the cursor on this line
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 48) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Effacer_ligne:KSFAM_USQ:
// \endif
extern void          SLC_Effacer_ligne    (int ligne, unsigned char position);



/*! @brief Set the date to the next day.
* @param date : date to set.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 49) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Joursuivant:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void          SLC_Joursuivant      (DATE *date);



/*! @brief State automaton.
* @param etat : begining state
* @param table : pointer to structure TAB_EV, wich describe the begining and the ending states.
* @param offset : offset on the first element of the automaton
* @return
* -255 when the automaton stops
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Moteur:KSFAM_VISU:
//  @GSIM_S:SLC_Moteur:E_SLC_Moteur
// \endif
extern short         SLC_Moteur           (short etat,TAB_EV *table,ADRESSE offset);



/*! @brief Asks for the widthdrawal of the card.
* @param fdpuce : handle of the cam.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 50) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLC_Retrait_puce:KSFAM_USQ:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern void          SLC_Retrait_puce     (FILE *fdpuce);



/*! @brief This function convert DCB in alphanumerical.
* @param dest : destination
* @param src : source
* @param size : data size
* @return 0 if OK
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 51) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:USQ_Aschex_alphanum:KSFAM_USQ:
//  @GSIM_A:1:DATA_SIZE(size)
//  @GSIM_A:2:DATA_SIZE(size)
// \endif
extern int           USQ_Aschex_alphanum  (unsigned char *dest,unsigned char *src,int size);


/*! @brief d_tolong converts the OEM C system date to a long.
* @param ptr : pointer to DATE structure.
* @return
* -The date as a long.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 52) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:d_tolong:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern unsigned long d_tolong             (DATE *ptr);




/*! @brief longto_d converts the date as long to OEM C system date
* @param numsec : gives the date as a long.
* @param ptr : pointer to DATE structure. 
* -Output parameter.
* -Returns the date at OEM C DATE format.
* @return
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 53) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
//! \note 
// \if SIMULATION
//  @GSIM_F:longto_d:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:2:ONE_POINTER 
// \endif
extern int           longto_d             (unsigned long numsec, DATE *ptr);



/*! @brief Call the applications to ask its money table, then save it.
* @param devise : pointer to structure S_MONEY.
* @param Nb : count of registred money tables.
* @return
* - 1 if ok
* - 0 otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 54) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:USQ_Demande_money:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:DATA_SIZE(4)
// \endif
extern int           USQ_Demande_money    (S_MONEY *devise,int *Nb);



/*! @brief Check the manager configuration.
* @return
* -Returns 1 if the terminal is portable, 0 otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 55) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PSLQ_Est_portable:KSFAM_USQ:
// \endif
extern int           PSLQ_Est_portable    (void);



/*! @brief recherche une monnaie dans la table des monnaies en fonction du code.
* @param ptcod     : code de la monnaie a rechercher (EUR par exemple)
* @param pt_money  : monnaie trouve
* @return
* -Returns 
* -0 ==> Monnaie non-presente
* -1 ==> Monnaie presente
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 105) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:USQ_Rechercher_money:KSFAM_USQ:
//  @GSIM_A:1:DATA_CODE(3)
//  @GSIM_A:1:IN_ONLY
// \endif
extern int           USQ_Rechercher_money(unsigned char *ptcod,S_MONEY *pt_money);



/*! @brief recherche une monnaie dans la table des monnaies etendues en fonction du code.
* @param ptcod     : code de la monnaie a rechercher (EUR par exemple)
* @param pt_money  : monnaie trouve
* @return
* -0 ==> Monnaie non-presente
* -1 ==> Monnaie presente
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 134) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:USQ_Rechercher_money_etendue:KSFAM_USQ:
//  @GSIM_A:1:DATA_CODE(3)
//  @GSIM_A:1:IN_ONLY
// \endif
extern int           USQ_Rechercher_money_etendue(unsigned char *ptcod,S_MONEY_EXTENDED *pt_money);



/*! @brief Requesting an amount to be entered in a given format and currency is given as a 
//! parameter, TAB_ENTRY_FCT typedef can be found in the entry.h file 
* @param Format : How to display the amount 
* - 0 cents comma then dot 1.000,00 
* - 1 cents dot then comma 1,000.00 
* - 2 cents comma then space 1 000,00 
* - 3 no cents and dot 1.000 
* - 4 no cents and comma 1,000 
* - 5 no cents and space 1 000 
* - 6 cents comma then dot 1.000,000 
* - 7 cents dot then comma 1,000.000 
* - 8 cents comma then space 1 000,000 
* @param Devise : Currency 3 ASCII + \\0 example "USD" 
* @param Position : How to display the currency 
* - 0 amount trailer "USD 1000" 
* - 1 amount header "1000 USD" 
* @param montant : returned amount 
* @param chaine : pointer to the message to be displayed on the first line 
* @param table : pointer to the table configuring the entry table->timeout in seconds table->mask 
//! 0000 default mask ( numerics, Red, Green, Yellow keys ) 
* - MASK_FONCTION 0x4000 function keys 
* - MASK_SK1 0x0200 F1 
* - MASK_SK2 0x0100 F2 
* - MASK_SK3 0x0080 F3 
* - MASK_SK4 0x0040 F4 
* @return last key (T_VAL, T_ANN, T_SK1, T_SK2, T_SK3, T_SK4, T_F) or TIMEOUT
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 107) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetAmount:KSFAM_M2OS:
//  @GSIM_A:2:DATA_SIZE(4)
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:4:DATA_SIZE(4)
//  @GSIM_A:4:OUT_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(chaine) +1)
//  @GSIM_A:5:IN_ONLY
//  @GSIM_A:6:ONE_POINTER
// \endif
extern int           GetAmount(
						unsigned char  Format,
						unsigned char *Devise,
						unsigned char Position,
						unsigned long *montant,
						unsigned char *chaine,
						TAB_ENTRY_FCT *table);


/*! @brief Requesting an amount to be entered in a given format and currency is given as a 
//! parameter, TAB_ENTRY_FCT typedef can be found in the entry.h file 
* @param Format : How to display the amount 
* - 0 cents comma then dot 1.000,00 
* - 1 cents dot then comma 1,000.00 
* - 2 cents comma then space 1 000,00 
* - 3 no cents and dot 1.000 
* - 4 no cents and comma 1,000 
* - 5 no cents and space 1 000 
* - 6 cents comma then dot 1.000,000 
* - 7 cents dot then comma 1,000.000 
* - 8 cents comma then space 1 000,000 
* @param Devise : Currency 3 ASCII + \\0 example "USD" 
* @param Position : How to display the currency 
* - 0 amount trailer "USD 1000" 
* - 1 amount header "1000 USD" 
* @param montant : returned amount 
* @param chaine : pointer to the message to be displayed on the first line 
* @param table : pointer to the table configuring the entry table->timeout in seconds table->mask 
//! 0000 default mask ( numerics, Red, Green, Yellow keys ) 
* - MASK_FONCTION 0x4000 function keys 
* - MASK_SK1 0x0200 F1 
* - MASK_SK2 0x0100 F2 
* - MASK_SK3 0x0080 F3 
* - MASK_SK4 0x0040 F4 
* @return last key (T_VAL, T_ANN, T_SK1, T_SK2, T_SK3, T_SK4, T_F) or TIMEOUT
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 238) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetAmount:KSFAM_M2OS:
//  @GSIM_A:2:DATA_SIZE(4)
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:4:DATA_SIZE(4)
//  @GSIM_A:4:OUT_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(chaine) +1)
//  @GSIM_A:5:IN_ONLY
//  @GSIM_A:6:ONE_POINTER
// \endif
extern int CGUIGetAmount(unsigned char  Format,unsigned char *Devise,unsigned char Position,unsigned long *montant, 
                      unsigned char *chaine,TAB_ENTRY_FCT *table);


/*! @brief getdate gives the Manager date at Manager date format.
* @param date_ext : pointer to structure DATE_EXT.
* @return
* - -1 if date cannot be read.
* - 0 otherwise .
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 106) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:getdate:KSFAM_USQ:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int           getdate(DATE_EXT *date_ext);




/*! @brief stdcam0 returns the FILE handle on the smart card.
* @return 
* - 0 if smart card is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 56) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdcam0:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdcam0              (void);



/*! @brief stdcam1 returns the FILE handle on the smart card.
* @return 
* - 0 if smart card is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 57) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdcam1:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdcam1              (void);



/*! @brief stdcom0 returns the FILE handle on the com 0.
* @return
* - 0 if com is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 58) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdcom0:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdcom0              (void);




/*! @brief stdcom1 returns the FILE handle on the com 1.
* @return 
* - 0 if com1 is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 59) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdcom1:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdcom1              (void);


/*! @brief stdcom2 returns the FILE handle on the com 2.
* @return
* - 0 if com is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 109) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdcom2:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdcom2              (void);



/*! @brief stdcom5 returns the FILE handle on the com 5.
* @return 
* - 0 if com is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 110) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdcom5:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdcom5              (void);



/*! @brief stdmodem returns the FILE handle on the modem.
* @return
* - 0 if modem is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 60) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdmodem:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdmodem             (void);




/*! @brief stdprt returns the FILE structure of the printer.
* @return 
* - 0 if the printer is not open.
* - FILE * otherwise.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 97) if function does not exist
 *
 * @link KSFAM_FIC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:stdprt:KSFAM_FIC:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern FILE          *stdprt               (void);

/*! @brief Display a message
* @param nomessage : identifier of the message.
* @return None.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 61) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Afficher_message:KSFAM_VISU:
// \endif
extern void           SLSQ_Afficher_message        (unsigned char nomessage);

/*! @brief get a list of all the ISO codes of the languages in the Manager
* @param pLanguages : string containing all ISO codes.
* @return
*   - Number of langues.
*   - 0 means that the function is not supported
* @section test_SLSQ_Afficher_message

 * @include services_Sample_03.c
* @par exit none.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_GetSupportedLanguages:KSFAM_VISU:
// \endif
extern int SLSQ_GetSupportedLanguages(char *pLanguages);


/*! @brief Display a message without cleaning the screen before.
* @param nomessage : identifier of the message.
* @return None.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 62) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Afficher_message_ss_eff:KSFAM_VISU:
// \endif
extern void           SLSQ_Afficher_message_ss_eff (unsigned char nomessage);


/*! @brief Manual entry of a card number.
* @param noporteur : the card number
* @param dateexp : expiration date.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 194) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Manual_entry:KSFAM_USQ:
//  @GSIM_A:1:DATA_SIZE(19)
//  @GSIM_A:2:DATA_SIZE(4)
// \endif
extern unsigned char  SLSQ_Manual_entry (unsigned char *noporteur,unsigned char *dateexp);



/*! @brief Display the version.
* @param version : buffer containing the version.
* @return None.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 63) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Afficher_bienvenue:KSFAM_VISU:
// \endif
extern void           SLSQ_Afficher_bienvenue      (T_VERSION version);



/*! @brief This function display the string : "monnaie refusee par LIBELLE".
* @param libelle : name of the application.
* @return None (void).
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 64) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Aff_pb_money:KSFAM_USQ:
// \endif
extern void           SLSQ_Aff_pb_money            (T_AFFNOM libelle);



/*! @brief Reset the terminal and gives an error code on the diagnostic ticket.
* @param numero : reset code.
* @return None (void).
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 65) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SLSQ_Exception:KSFAM_USQ:
// \endif
extern void           SLSQ_Exception               (unsigned char numero);



/*! @brief Display a message on the screen.
* @param pMSGinfosCust : struct containing the info message
* @param old_display : old display feature
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 195) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayMSGcust:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void G_DisplayMSGcust(InfosMSG_CUST *pMSGinfosCust, char old_display);


/*! @brief Display a message on the screen.
* @param pMSGinfos : struct containing the info message
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 160) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayMSG:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  G_DisplayMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);

/*! @brief Display a message on the screen.
* @param num : Contain the range of the message (see english.h or french.h)
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 180) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayMSGnum:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  G_DisplayMSGnum(int num,char *option,unsigned char flag);

/*! @brief Display a message on the Pinpad.
* @param pMSGinfos : struct containing the info message
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 162) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayPprMSG:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  G_DisplayPprMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);

/*! @brief Display a message on the Pinpad.
* @param num : Contain the range of the message (see english.h or french.h)
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 181) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayPprMSGnum:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  G_DisplayPprMSGnum(int num,char *option,unsigned char flag);

/*! @brief Display a message on the external Cless device
* @param pMSGinfos : struct containing the info message
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 248) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayC30MSG:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  G_DisplayC30MSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);

/*! @brief Display a message on the external Cless device.
* @param num : Contain the range of the message (see english.h or french.h)
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 247) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayC30MSGnum:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  G_DisplayC30MSGnum(int num,char *option,unsigned char flag);

/*! @brief Verify if the service custmsg exist.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 197) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Register_Appli_Id_Sercice_Msgcust:KSFAM_AUTRES_MANAGER:
// \endif
extern void Register_Appli_Id_Sercice_Msgcust(void);


/*! @brief Display a message on the screen.
* @param message : buffer containing the message
* @param option : display options
* @param flag : wait after display
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 115) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_Display:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:DATA_CODE(strlen(message) +1)
// (depend de la taille de l'ecran)
// \endif
extern void           G_Display (unsigned char *message,char *option,unsigned char flag);

/*! @brief Display a message on the pinpad reader
* @param message : buffer containing the message
* @param option : display otpions
* @param flag : wait time
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 116) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayPpr:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:DATA_CODE(strlen(message) +1)
// (depend de la taille de l'ecran)
// \endif
extern void           G_DisplayPpr (unsigned char *message,char *option,unsigned char flag);




/*! @brief Display a message on the C30
* @param message : buffer containing the message
* @param option : display otpions
* @param flag : waiting time.
* @return none
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 132) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:G_DisplayC30:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:DATA_CODE(strlen(message) +1)
// (depend de la taille de l'ecran)
// \endif
extern void           G_DisplayC30 (unsigned char *message,char *option,unsigned char flag);


/*! @brief Display the "official" Cless target.
 *	@param periph    : Display to use.
 *	- #PERIPH_DISPLAY          : on internal display 
 *	- #PERIPH_PPR              : On display of the current PINPAD connected 
 *	- #PERIPH_C30              : On display of the current C30 connected
 *
 * The caller must test if a PINPAD or an external target is connected to the terminal
 *
 *	@return 0 if OK
 *  @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayTargetCless:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int 		  DisplayTargetCless(int periph);




/*! @brief Activate the redirection.
* @param type : code of the application wich starts on ends the redirection.
* @return
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 120) if function does not exist
//! Returns the application wich called the function previously.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:StartPatchAppli:KSFAM_AUTRES_MANAGER:
// \endif
extern unsigned short StartPatchAppli(unsigned short type);




/*! @brief Disable the redirection
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 119) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:StopPatchAppli:KSFAM_AUTRES_MANAGER:
// \endif
extern void           StopPatchAppli(void);






/*! @brief Check the manager's configuration.
* @return
* - 1 if display, 0 otherwise.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsDisplay:KSFAM_AUTRES_MANAGER:
// \endif
extern int            IsDisplay(void);




/*! @brief Returns the state of the header.
* @return
//! 1 (activated) otherwise 0
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:IsHeaderDisplayed:KSFAM_AUTRES_MANAGER:
// \endif
extern int            IsHeaderDisplayed(void);

#define _PERIPH_DISPLAY     0
#define _PERIPH_CAM0        1
#define _PERIPH_CAM1        2
#define _PERIPH_CAM2        3
#define _PERIPH_CAM9        4
#define _PERIPH_BANDEAU     2
#define _PERIPH_REDIRECTION 3
#define _PERIPH_LEDS        4
#define _PERIPH_FOOTER      5

#define _PERIPH_OFF             0
#define _PERIPH_ON              1
#define _PERIPH_PAINT           2
#define _PERIPH_KEYB_ON         3
#define _PERIPH_KEYB_OFF        4
#define _PERIPH_STARTUPCV20_OFF 5
#define _PERIPH_STARTUPCV20_ON  6
#define _PERIPH_START           7
#define _PERIPH_STOP            8





/*! @brief Close all periph used for transaction
* @return
//! 0 if OK
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CloseAllPeriph:KSFAM_AUTRES_MANAGER:
// \endif
extern int           CloseAllPeriph (void);


/*! @brief Activate or disactivate footer
* @param Status : _ON_ (activation) or _OFF_ (disactivation)
* @return
//! previous state (_ON_ or _OFF_)
//! EOF if function doesnt exist (for compatibility)
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayFooter:KSFAM_AUTRES_MANAGER:
// \endif
extern int           DisplayFooter(int Status);

/*! @brief Activate or disactivate header
* @param Status : _ON_ (activation) or _OFF_ (disactivation)
* @return
//! previous state (_ON_ or _OFF_)
//! EOF if function doesnt exist (for compatibility)
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayHeader:KSFAM_AUTRES_MANAGER:
// \endif
extern int           DisplayHeader(int Status);

/*! @brief Activate or disactivate leds
* @param Status : _ON_ (activation) or _OFF_ (disactivation)
* @return
//! previous state (_ON_ or _OFF_)
//! EOF if function doesnt exist (for compatibility)
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayLeds:KSFAM_AUTRES_MANAGER:
// \endif
extern int           DisplayLeds(int Status);


/*! @brief Activate the version of the patched peripheral device
* @param Periph : CAM0, DISPLAY, HEADER or redirection.
* @param Status : ON (activation) or OFF (disactivation)
* @return None.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 128) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetPatchAppli:KSFAM_AUTRES_MANAGER:
// \endif
extern void           SetPatchAppli(int Periph,int Status);

/*! @brief GetFooterSize read the Footer size.
* @param Height : return the Footer Height.
* @param Width :  return the Footer Width.
* @return position of footer
* - 0= Bottom (default)
* - 1= Right (ISC350 only)
* - 2= Left (ISC350 only)
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 246) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetFooterSize:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
// \endif
extern int GetFooterSize(int *Height,int *Width);

/*! @brief This function is used to get the footer area position.
 * @param left   : letf position.
 * @param top    : top position.
 * @param right  : right position.
 * @param bottom : bottom position.
* @return 
* - 0= if no footer management
* - 1= if footer management
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetFooterArea:KSFAM_AUTRES_MANAGER:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int GetFooterArea(int *left,int *top,int *right,int *bottom);

/*! @brief BoosterType return BOOSTER type
* @return
* - NO_BOOSTER = No booster (TWIN30 for exemple)
* - BOOSTER_1  = Booster 1  (EFT930P for exemple)
* - BOOSTER_2  = Booster 2  (EFT930CC for exemple)
* - BOOSTER_3  = Booster 3  (ICT2XX for exemple)
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:BoosterType:KSFAM_AUTRES_MANAGER:
// \endif
extern int BoosterType(void);
/*! @} **/

/*! @addtogroup KSFAM_LEDS
	* @{
**/

/*! @brief constant for GetLedEvent,SetLedEvent,SetLedBlinking,SetLedColor
 * @link KSFAM_LEDS Back to top @endlink
*/
#define SOFTWARE_LED_01				0x00	/*!< Software Led n� 1  (on color display only)                                         */
#define SOFTWARE_LED_02				0x01	/*!< Software Led n� 2  (on color display only)                                         */
#define SOFTWART_LED_03				0x02	/*!< Software Led n� 3  (on color display only)                                         */
#define SOFTWARE_LED_04				0x03	/*!< Software Led n� 4  (on color display only)                                         */
#define HARDWARE_LED_01				0x100	/*!< Led n� 1 C'Less (Green color)                                                      */
#define HARDWARE_LED_02				0x101	/*!< Led n� 2 C'Less (Green color)                                                      */
#define HARDWARE_LED_03				0x102	/*!< Led n� 3 C'Less (Green color)                                                      */
#define HARDWARE_LED_04				0x103	/*!< Led n� 4 C'Less (Green color)                                                      */
#define HARDWARE_LED_05				0x104	/*!< Led n� 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)    */
#define HARDWARE_LED_06				0x105	/*!< Led n� 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx) */
#define HARDWARE_LED_07				0x106	/*!< Led n� 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)       */
#define HARDWARE_LED_08				0x107	/*!< Led n� 8                                                                           */
#define HARDWARE_LED_CAM            0x200   /*!< CAM reader led on IPP320,IPP350,IPP480,ISC350                                      */
#define HARDWARE_LED_SWIPE          0x300   /*!< swipe reader led on IPP320,IPP350,ISC350                                           */

#define HARDWARE_LED_CAM_TO_GREEN   0xFF00FF00 /*!< value to set current CAM reader leds color to GREEN with SetLedColor API on IPP480,ISC350 */
#define HARDWARE_LED_CAM_TO_RED     0xFFFF0000 /*!< value to set current CAM reader leds color to RED with SetLedColor API on IPP480,ISC350   */

#define HARDWARE_LED_SWIPE_TO_GREEN   0xFF00FF00 /*!< value to set current SWIPE reader leds color to GREEN with SetLedColor API on ISC350      */
#define HARDWARE_LED_SWIPE_TO_RED     0xFFFF0000 /*!< value to set current SWIPE reader leds color to RED with SetLedColor API on ISC350        */

/*! @brief SetLedEvent set the led state.
* it is recommended to use TpassLedOn or TpassLedOff to manage the cless Led (Hardware or Sofware)  
* @param led   : num of led  (see above for value.
* - SOFTWARE_LED_01	   Software Led n� 1  (on color display only)
* - SOFTWARE_LED_02	   Software Led n� 2  (on color display only)
* - SOFTWART_LED_03	   Software Led n� 3  (on color display only)
* - SOFTWARE_LED_04    Software Led n� 4  (on color display only)
* - HARDWARE_LED_01	   Led n� 1 C'Less (Green color)
* - HARDWARE_LED_02	   Led n� 2 C'Less (Green color)
* - HARDWARE_LED_03	   Led n� 3 C'Less (Green color)
* - HARDWARE_LED_04	   Led n� 4 C'Less (Green color)
* - HARDWARE_LED_05	   Led n� 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_06	   Led n� 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_07	   Led n� 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_08	   Led n� 8
* - HARDWARE_LED_CAM   CAM reader led on IPP320,IPP350,IPP480,ISC350
* - HARDWARE_LED_SWIPE SWIPE reader led on IPP320,IPP350,ISC350
* @param state : _ON_ or _OFF_ .
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 198) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetLedEvent:KSFAM_LEDS:
// \endif
extern int           SetLedEvent        (int led,int state);



/*! @brief GetLedEvent give the led state.
* @param led   : num of led (see above for value)
* - SOFTWARE_LED_01	   Software Led n� 1  (on color display only)
* - SOFTWARE_LED_02	   Software Led n� 2  (on color display only)
* - SOFTWART_LED_03	   Software Led n� 3  (on color display only)
* - SOFTWARE_LED_04    Software Led n� 4  (on color display only)
* - HARDWARE_LED_01	   Led n� 1 C'Less (Green color)
* - HARDWARE_LED_02	   Led n� 2 C'Less (Green color)
* - HARDWARE_LED_03	   Led n� 3 C'Less (Green color)
* - HARDWARE_LED_04	   Led n� 4 C'Less (Green color)
* - HARDWARE_LED_05	   Led n� 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_06	   Led n� 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_07	   Led n� 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_08	   Led n� 8
* - HARDWARE_LED_CAM   CAM reader led on IPP320 and IPP380 OR Hybrid reader leds on IPP480
* - HARDWARE_LED_SWIPE SWIPE reader led (available on IPP320 and IPP350)
* @return
* - _ON_ or _OFF_ .
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 199) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetLedEvent:KSFAM_LEDS:
// \endif
extern int           GetLedEvent        (int led);


/*! @brief SetLedBlinking force blinking led
* @param led : num of led (see above for value)
* - SOFTWARE_LED_01	   Software Led n� 1  (on color display only)
* - SOFTWARE_LED_02	   Software Led n� 2  (on color display only)
* - SOFTWART_LED_03	   Software Led n� 3  (on color display only)
* - SOFTWARE_LED_04    Software Led n� 4  (on color display only)
* - HARDWARE_LED_01	   Led n� 1 C'Less (Green color)
* - HARDWARE_LED_02	   Led n� 2 C'Less (Green color)
* - HARDWARE_LED_03	   Led n� 3 C'Less (Green color)
* - HARDWARE_LED_04	   Led n� 4 C'Less (Green color)
* - HARDWARE_LED_05	   Led n� 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_06	   Led n� 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_07	   Led n� 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_08	   Led n� 8
* - HARDWARE_LED_CAM   CAM reader led on IPP320 and IPP380 OR Hybrid reader leds on IPP480
* - HARDWARE_LED_SWIPE SWIPE reader led (available on IPP320 and IPP350)
* @param timeon : Time of _ON_ state (20ms intervals)
* @param timeoff : Time of _OFF_ state (20ms intervals)
* @return 0.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 228) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetLedBlinking:KSFAM_LEDS:
// \endif
extern int           SetLedBlinking     (int led,int timeon,int timeoff);


/*! @brief SetLedColor force color of led (only for software LEDS)
* @param led : num of led (see above for value)
* - SOFTWARE_LED_01	   Software Led n� 1  (on color display only)
* - SOFTWARE_LED_02	   Software Led n� 2  (on color display only)
* - SOFTWART_LED_03	   Software Led n� 3  (on color display only)
* - SOFTWARE_LED_04    Software Led n� 4  (on color display only)
* - HARDWARE_LED_01	   Led n� 1 C'Less (Green color)
* - HARDWARE_LED_02	   Led n� 2 C'Less (Green color)
* - HARDWARE_LED_03	   Led n� 3 C'Less (Green color)
* - HARDWARE_LED_04	   Led n� 4 C'Less (Green color)
* - HARDWARE_LED_05	   Led n� 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_06	   Led n� 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_07	   Led n� 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_08	   Led n� 8
* - HARDWARE_LED_CAM   CAM reader led on IPP320 and IPP380 OR Hybrid reader leds on IPP480
* - HARDWARE_LED_SWIPE SWIPE reader led (available on IPP320 and IPP350)
* @param color : Color ARGB (for exemple, 0xFF00FF00 for GREEN)
* @return 0.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 229) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetLedColor:KSFAM_LEDS:
// \endif
extern int           SetLedColor        (int led,int color);



/*! @brief GetLedColor return current color of led (only for software LEDS)
* @param led : num of led (see above for value)
* - SOFTWARE_LED_01	   Software Led n� 1  (on color display only)
* - SOFTWARE_LED_02	   Software Led n� 2  (on color display only)
* - SOFTWART_LED_03	   Software Led n� 3  (on color display only)
* - SOFTWARE_LED_04    Software Led n� 4  (on color display only)
* - HARDWARE_LED_01	   Led n� 1 C'Less (Green color)
* - HARDWARE_LED_02	   Led n� 2 C'Less (Green color)
* - HARDWARE_LED_03	   Led n� 3 C'Less (Green color)
* - HARDWARE_LED_04	   Led n� 4 C'Less (Green color)
* - HARDWARE_LED_05	   Led n� 5 (green led on CAD30UPT(-C)) (Blue led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_06	   Led n� 6 (yellow led on CAD30UPT(-C)) (orange led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_07	   Led n� 7 (red led on CAD30UPT(-C)) (red led for Asian C'less only on IPP3xx)
* - HARDWARE_LED_08	   Led n� 8
* - HARDWARE_LED_CAM   CAM reader led on IPP320 and IPP380 OR Hybrid reader leds on IPP480
* - HARDWARE_LED_SWIPE SWIPE reader led (available on IPP320 and IPP350)
* @return color (for exemple, 0xFF00FF00 for GREEN) or 0 if num of led invalid.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 245) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetLedColor:KSFAM_LEDS:
// \endif
extern int           GetLedColor        (int led);


/*! @brief GetLedsSize read the Leds size (Software LEDS)
* @param Height : return the Leds Height.
* @param Width :  return the Leds Width.
* @return
* - 0= Leds is inactive
* - 1= Leds is active
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 233) if function does not exist
 *
 * @link KSFAM_LEDS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetLedsSize:KSFAM_LEDS:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:OUT_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
// \endif
extern int  GetLedsSize(int *Height,int *Width);


/*! @} **/


/*! @addtogroup KSFAM_CGUI
	* @{
**/

/*! @brief PushCGUIContext sets cgui context.
* 
* PushCGUIContext function allows you to set up a display context.\n
* Management of display context can perform following actions: \n
* - Test if the manager is in "CGUI" mode
* - Inhibit or not display header
* - Inhibit or not display footer
* - Inhibit or not display software LEDS area.
* - Change if needed the size and position of the "CGUI" windows.
* - Mandatory recommendations:
*   You must use PushCGUIContext() and PopCGUIContext() inside the SAME 
*   service call (you should think about multi-application environment).
* 
* @param NewCGUIContext : New value
* 
* CGUI_CONTEXT_STRUCT structure fields:\n
* 
* CGUIStatus: \n
* 	- CGUI_NEEDED, function will check if Manager is in CGUI mode. Manager functions as cGUI_List_Entry will work in CGUI mode.Can be used only on color terminals. \n
* 	- CGUI_NOT_NEEDED, no check for Manager mode.Manager functions as cGUI_List_Entry will work in standard, non-CGUI mode.Can be used on both color and B&W terminals. \n
* 	- CGUI_REFRESH, no check for Manager mode.Manager functions as cGUI_List_Entry will work in standard, non-CGUI mode.Can be used on both color and B&W terminals. Force refresh at next PopCGUIContext\n
* HeaderStatus: \n
* 	Inhibit or not display header : _PERIPH_OFF or _PERIPH_ON \n
* FooterStatus: \n
* 	Inhibit or not display footer : _PERIPH_OFF or _PERIPH_ON \n
* LedsStatus: \n
* 	Inhibit or not display software LEDS area: _PERIPH_OFF or _PERIPH_ON \n
* CanvasStatus: \n
* 	- CANVAS_NOT_USED "CGUI" windows don't change their size and position. \n
* 	- CANVAS_MAXIMIZE "CGUI" windows size is set to maximum possible size of display and it can change it position.Changes depend on HeaderStatus, FooterStatus and LedsStatus changes.Manager must be in "CGUI" mode. Can be used only on color terminals. \n
* 	- CANVAS_RESIZE "CGUI" windows area will be set to parameters given in CGUI_CONTEXT_STRUCT structure (x, y, width, height).Manager must be in "CGUI" mode.Can be used only on color terminals. \n
* X, y, width, height: \n
* 	Parameters for "CGUI" windows area used only if CanvasStatus is set to CANVAS_RESIZE. \n
*  
* @return
* - FALSE: if CGUIStatus is set to CGUI_NEEDED, but manager is not in CGUI mode 
* - TRUE: otherwise 
* @par exit None
*  
* @section samplepush1 Sample PushCGUIContext

 * @include services_Sample_04.c
* @section samplepush2 Sample PushCGUIContext

 * @include services_Sample_05.c
* @section samplepush3 Sample PushCGUIContext

 * @include services_Sample_06.c
*
* @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PushCGUIContext:KSFAM_CGUI:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern int PushCGUIContext(CGUI_CONTEXT_STRUCT *NewCGUIContext);


/*! @brief PopCGUIContext restore cgui context.
 * - Mandatory recommendations:
 *   You must use PushCGUIContext() and PopCGUIContext() inside the SAME 
 *   service call (you should think about multi-application environment).
 * @return
 * - TRUE  if success
 * - FALSE if not (CGUI is necessary and is not available
 * @par exit None
 *
 *	@section samplepop PopCGUIContext

 * @include services_Sample_07.c
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PopCGUIContext:KSFAM_CGUI:
// \endif
extern int PopCGUIContext(void);

/*! @brief GetCGUIContext return data cgui context.
* @return
* - TRUE  if success
* - FALSE if not (CGUI is necessary and is not available
* @par exit None
 *
 *	@section sampleget Sample GetCGUIContext

 * @include services_Sample_08.c
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PopCGUIContext:KSFAM_CGUI:
// \endif
extern int GetCGUIContext(int num_context, CGUI_CONTEXT_STRUCT *CGUIContext_data);

/*! @brief Get_StateWGUI return if manager is able to work with CGUI interface (DLL WGUI exist,browser and canvas has been succefully created)
* @return
* - TRUE  if success
* - FALSE if not 
* @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:Get_StateWGUI:KSFAM_CGUI:
// \endif
extern int Get_StateWGUI(void);

/*! @brief GetCguiFileName return the file name of the manager CGUI resource 
 * @param FileName : pointer to a string to store the name
 *   
 * @return
 *   pointer to a string containing the name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:GetCguiFileName:KSFAM_CGUI:
// \endif
extern char          *GetCguiFileName(char *FileName);

/*! @brief GetCguiPageList return the resource name for CGUI page list. 
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:GetCguiPageList:KSFAM_CGUI:
// \endif
extern char          *GetCguiPageList(void);

/*! @brief GetCguiPageFList return the resource name for CGUI page list. 
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:GetCguiPageFList:KSFAM_CGUI:
// \endif
extern char          *GetCguiPageFList(void);

/*! @brief GetCguiPageNavi return the resource name for CGUI page navigation. 
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:GetCguiPageNavi:KSFAM_CGUI:
// \endif
extern char          *GetCguiPageNavi(void);


/*! @brief GetCguiPathIcon return the path for the resource icon in a CGUI icon list or a list entry. 
 * @return
 *   pointer to a string containing the path
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:GetCguiPathIcon:KSFAM_CGUI:
// \endif
extern char          *GetCguiPathIcon(void);

/*! @brief GetCguiEntryDirectory return the resource name for CGUI page entry. 
 * @return
 *   pointer to a string containing the resource name
 * @par exit None
 *
 * @link KSFAM_CGUI Back to top @endlink
**/
//! \note 
// \if SIMULATION
//  @GSIM_F:GetCguiEntryDirectory:KSFAM_CGUI:
// \endif
extern char          *GetCguiEntryDirectory(void);

/*! @brief Display a message on the screen with WGUI interface
 *  WGUI window is automatically resized to fill the user area
 *  "DISPLAY" must be closed before calling this function
 *  if terminal is not WGUI, "old" way for displaying
 *  Waiting time, if the flag parameter is WAITING, can be parametered with the TimeOutDisplayMessage parameter
 *  (see function PSQ_write_state_param) 
* @param message : buffer containing the message
* @param option : display options
* @param flag : wait after display (WAITING or !WAITING)
* @return none
* @par exit exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 271) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CGUI_Display:KSFAM_CGUI:
//  @GSIM_A:1:DATA_CODE(strlen(message) +1)
// (depend de la taille de l'ecran)
// \endif
extern void           CGUI_Display (unsigned char *message,char *option,unsigned char flag);

/*! @brief Display a message on the screen with WGUI interface
 *  WGUI window is automatically resized to fill the user area
 *  "DISPLAY" must be closed before calling this function
 *  if terminal is not WGUI, "old" way for displaying
 *  Waiting time, if the flag parameter is WAITING, can be parametered with the TimeOutDisplayMessage parameter
 *  (see function PSQ_write_state_param) 
* @param pMSGinfos : struct containing the info message
* @param option : display options
* @param flag : wait after display (WAITING or !WAITING)
* @return none
* @par exit exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 272) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CGUI_DisplayMSG:KSFAM_CGUI:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  CGUI_DisplayMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);

/*! @brief Display a message on the screen with WGUI interface
 *  WGUI window is automatically resized to fill the user area
 *  "DISPLAY" must be closed before calling this function
 *  if terminal is not WGUI, "old" way for displaying
 *  Waiting time, if the flag parameter is WAITING, can be parametered with the TimeOutDisplayMessage parameter
 *  (see function PSQ_write_state_param) 
* @param num : Contain the range of the message (see english.h or french.h)
* @param option : display options
* @param flag : wait after display (WAITING or !WAITING)
* @return none
* @par exit exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 273) if function does not exist
 *
 * @link KSFAM_CGUI Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CGUI_DisplayMSGnum:KSFAM_CGUI:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void 		  CGUI_DisplayMSGnum(int num,char *option,unsigned char flag);

/*! @brief StopBacklightManagment put infinite time for backlight duration
* @return 
* - 0                       POS doesnt not support backlight
* - 1                       done
* - EXTENS_NOT_IMPLEMENTED  function is not implemented
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:StopBacklightManagment:KSFAM_AUTRES_MANAGER:
// \endif
extern int StopBacklightManagment(void);

/*! @brief EXT_Available search for external communication module (PCL)
* @return 
* - 0                       external communication module not found
* - EXTENS_NOT_IMPLEMENTED  function is not implemented
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXT_Available:KSFAM_AUTRES_MANAGER:
// \endif
extern int            EXT_Available(void);

/*! @brief EXT_Ethernet search if ethernet is available via external communication module (PCL)
* @return 
* - 0                       ethernet is not available via external communication module
* - EXTENS_NOT_IMPLEMENTED  function is not implemented
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXT_Ethernet:KSFAM_AUTRES_MANAGER:
// \endif
extern int            EXT_Ethernet(void);

/*! @brief EXT_Powered search via external communication module (PCL) if terminal is powered with a cradle
* @return 
* - 0                       terminal is not powered with a cradle
* - EXTENS_NOT_IMPLEMENTED  function is not implemented
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:EXT_Powered:KSFAM_AUTRES_MANAGER:
// \endif
extern int            EXT_Powered(void);

/*! @brief RestartBacklightManagment restore current value for backlight management
* @return 
* - 0                       POS doesnt not support backlight
* - 1                       done
* - EXTENS_NOT_IMPLEMENTED  function is not implemented
* @par exit none
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:RestartBacklightManagment:KSFAM_AUTRES_MANAGER:
// \endif
extern int RestartBacklightManagment(void);

//!see \ref G_DisplayMSGcust
extern void G_AfficherMSGcust(InfosMSG_CUST *pMSGinfosCust, char old_display);
//!see \ref G_DisplayMSG
extern void G_AfficherMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);
//!see \ref G_DisplayMSGnum
extern void G_AfficherMSGnum(int num,char *option,unsigned char flag);
//!see \ref G_DisplayPprMSG
extern void G_AfficherPprMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);
//!see \ref G_DisplayPprMSGnum
extern void G_AfficherPprMSGnum(int num,char *option,unsigned char flag);
//!see \ref G_DisplayC30MSG
extern void G_AfficherC30MSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);
//!see \ref G_DisplayC30MSGnum
extern void G_AfficherC30MSGnum(int num,char *option,unsigned char flag);
//!see \ref G_Display
extern void G_Afficher (unsigned char *message,char *option,unsigned char flag);
//!see \ref G_DisplayPpr
extern void G_AfficherPpr (unsigned char *message,char *option,unsigned char flag);
//!see \ref G_DisplayC30
extern void G_AfficherC30 (unsigned char *message,char *option,unsigned char flag);

/*! \cond NON_VISIBLE */
#define G_DisplayMSGcust    G_AfficherMSGcust
#define G_DisplayMSG        G_AfficherMSG
#define G_DisplayMSGnum     G_AfficherMSGnum
#define G_DisplayPprMSG     G_AfficherPprMSG
#define G_DisplayPprMSGnum  G_AfficherPprMSGnum
#define G_DisplayC30MSG     G_AfficherC30MSG
#define G_DisplayC30MSGnum  G_AfficherC30MSGnum
#define G_Display           G_Afficher
#define G_DisplayPpr        G_AfficherPpr
#define G_DisplayC30        G_AfficherC30
/*!\endcond*/

//!see \ref CGUI_Display
extern void           CGUI_Afficher (unsigned char *message,char *option,unsigned char flag);
//!see \ref CGUI_DisplayMSG
extern void 		  CGUI_AfficherMSG(MSGinfos *pMSGinfos,char *option,unsigned char flag);
//!see \ref CGUI_DisplayMSGnum
extern void 		  CGUI_AfficherMSGnum(int num,char *option,unsigned char flag);

/*! \cond NON_VISIBLE */
#define CGUI_Display        CGUI_Afficher
#define CGUI_DisplayMSG     CGUI_AfficherMSG
#define CGUI_DisplayMSGnum  CGUI_AfficherMSGnum
/*!\endcond*/
/*! @} **/

/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#define               min(a, b)  (((a) < (b)) ? (a) : (b)) 
#ifndef _SIMULPC_
#define               max(a, b)  (((a) < (b)) ? (b) : (a)) 
#endif   //_SIMULPC_

#endif
/*! @} **/

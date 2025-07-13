/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFDIAG_TMANAGER_
#define _DEFDIAG_TMANAGER_
/* ********************************************************** */
/* ********************************************************** */
/* ****************** COMPTEURS ***************************** */
/* ********************************************************** */
/* ********************************************************** */
#define SQ_NB_PISTES_LUES_OK              1002
#define SQ_NB_PISTES_LUES_KO              1003
#define SQ_NB_CONNEXION                   1010
#define SQ_NB_REPLI                       1011
#define SQ_NB_GARBAGE_MANAGER          1012

#define FUNCTION_NOT_IMPLEMENTED -1


/* gestionnaire EFT30 */
#define EXIT_DLL_SAISIE_NOT_INITIALIZED    0x0800
/*****************************************************************************/
/* Saisie_Numerique                  EXIT_DLL_SAISIE_NOT_INITIALIZED + 0     */
/* Saisie_Alphanumerique             EXIT_DLL_SAISIE_NOT_INITIALIZED + 1     */
/* Saisie_Fonction                   EXIT_DLL_SAISIE_NOT_INITIALIZED + 2     */
/* Saisie_Montant                    EXIT_DLL_SAISIE_NOT_INITIALIZED + 3     */
/* Saisie_Seuil                      EXIT_DLL_SAISIE_NOT_INITIALIZED + 4     */
/* Read_Saisie                       EXIT_DLL_SAISIE_NOT_INITIALIZED + 5     */
/* G_Saisie_Numerique                EXIT_DLL_SAISIE_NOT_INITIALIZED + 6     */
/* G_Saisie_Alphanumerique           EXIT_DLL_SAISIE_NOT_INITIALIZED + 7     */
/* G_Saisie_Liste                    EXIT_DLL_SAISIE_NOT_INITIALIZED + 8     */
/* Stop_Saisie                       EXIT_DLL_SAISIE_NOT_INITIALIZED + 9     */
/* SaisieOperation                   EXIT_DLL_SAISIE_NOT_INITIALIZED + 10    */
/* SLSQ_Affichage_choix              EXIT_DLL_SAISIE_NOT_INITIALIZED + 12    */
/* G_Aff_Liste_Ppr                   EXIT_DLL_SAISIE_NOT_INITIALIZED + 14    */
/* G_Saisie_Fonction                 EXIT_DLL_SAISIE_NOT_INITIALIZED + 15    */
/* G_Init                            EXIT_DLL_SAISIE_NOT_INITIALIZED + 16    */
/* G_Saisie_Etendue                  EXIT_DLL_SAISIE_NOT_INITIALIZED + 17    */
/* G_Aff_Liste                       EXIT_DLL_SAISIE_NOT_INITIALIZED + 18    */
/* IsTerminalPeds                    EXIT_DLL_SAISIE_NOT_INITIALIZED + 19    */
/* wG_Saisie_Numerique               EXIT_DLL_SAISIE_NOT_INITIALIZED + 20    */
/* wG_Saisie_Liste                   EXIT_DLL_SAISIE_NOT_INITIALIZED + 21    */
/* wG_Saisie_Alphanumerique          EXIT_DLL_SAISIE_NOT_INITIALIZED + 22    */
/* wG_Init                           EXIT_DLL_SAISIE_NOT_INITIALIZED + 23    */
/* wG_Saisie_Etendue                 EXIT_DLL_SAISIE_NOT_INITIALIZED + 24    */
/* wG_Aff_Liste                      EXIT_DLL_SAISIE_NOT_INITIALIZED + 25    */
/* wG_Aff_Liste_Ppr                  EXIT_DLL_SAISIE_NOT_INITIALIZED + 26    */
/* cGUI_List_Entry                   EXIT_DLL_SAISIE_NOT_INITIALIZED + 27    */
/* cGUI_Aff_Liste                    EXIT_DLL_SAISIE_NOT_INITIALIZED + 28    */
/* cGUI_Numerical_Entry              EXIT_DLL_SAISIE_NOT_INITIALIZED + 29    */
/* cGUI_Icon_List                    EXIT_DLL_SAISIE_NOT_INITIALIZED + 30    */
/* cGUI_Extended_Entry               EXIT_DLL_SAISIE_NOT_INITIALIZED + 31    */
/* cGUI_Alphanum_Entry               EXIT_DLL_SAISIE_NOT_INITIALIZED + 32    */
/* cGUI_List_Multi_Entry             EXIT_DLL_SAISIE_NOT_INITIALIZED + 49    */
/* IsTerminalIngetrust               EXIT_DLL_SAISIE_NOT_INITIALIZED + 50    */
/* cGUI_Large_List_Entry             EXIT_DLL_SAISIE_NOT_INITIALIZED + 51    */
/*****************************************************************************/
#define EXIT_DLL_LIBGR_NOT_INITIALIZED     0x0900
/*****************************************************************************/
/* PaintGraphics                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 0      */
/* StringWidth                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 1      */
/* SetFont                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 2      */
/* GetFont                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 3      */
/* SetType                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 4      */
/* GetType                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 5      */
/* CreateGraphics                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 6      */
/* _SetPixel                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 7      */
/* _DrawLine                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 8      */
/* DrawLine                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 9      */
/* SetPixel                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 10     */
/* _SetBitmap                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 11     */
/* SetBitmap                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 12     */
/* GetPixel                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 13     */
/* _DrawRect                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 14     */
/* DrawRect                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 15     */
/* _DrawCircle                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 16     */
/* DrawCircle                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 17     */
/* _DrawEllipse                      EXIT_DLL_LIBGR_NOT_INITIALIZED + 18     */
/* DrawEllipse                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 19     */
/* _DrawString                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 22     */
/* DrawString                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 23     */
/* _DrawWindow                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 24     */
/* DrawWindow                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 25     */
/* _SetArea                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 26     */
/* SetArea                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 27     */
/* CopyArea                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 28     */
/* SaveScreen                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 29     */
/* RestoreScreen                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 30     */
/* LibVersion                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 31     */
/* GetScreenSize                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 32     */
/* SetBmp                            EXIT_DLL_LIBGR_NOT_INITIALIZED + 33     */
/* _clrscr                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 34     */
/* _Sizeof                           EXIT_DLL_LIBGR_NOT_INITIALIZED + 35     */
/* GetPoliceSize                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 36     */
/* DefGraphicPattern                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 38     */
/* InitContexteGraphique             EXIT_DLL_LIBGR_NOT_INITIALIZED + 39     */
/* DisplayBitmap                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 40     */
/* _DisplayBitmap                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 41     */
/* _SizeofChaine                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 42     */
/* _ScrollString                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 43     */
/* ScrollString                      EXIT_DLL_LIBGR_NOT_INITIALIZED + 44     */
/* _PrintChaine                      EXIT_DLL_LIBGR_NOT_INITIALIZED + 45     */
/* PrintChaine                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 46     */
/* SetDefaultFont                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 47     */
/* GetDefaultFont                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 48     */
/* _DrawExtendedString               EXIT_DLL_LIBGR_NOT_INITIALIZED + 49     */
/* DrawExtendedString                EXIT_DLL_LIBGR_NOT_INITIALIZED + 50     */
/* _SizeofExtendedString             EXIT_DLL_LIBGR_NOT_INITIALIZED + 51     */
/* DefCurrentFont                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 53     */
/* DrawExtendedString8859            EXIT_DLL_LIBGR_NOT_INITIALIZED + 54     */
/* _DrawExtendedString8859           EXIT_DLL_LIBGR_NOT_INITIALIZED + 55     */
/* _DrawExtendedStringUnicode        EXIT_DLL_LIBGR_NOT_INITIALIZED + 56     */
/* pprintf8859                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 57     */
/* pprintfUnicode                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 58     */
/* strlenUNICODE                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 59     */
/* strcpyUNICODE                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 60     */
/* strcatUNICODE                     EXIT_DLL_LIBGR_NOT_INITIALIZED + 61     */
/* PrintPolice                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 62     */
/* SizeOfUnicodeString               EXIT_DLL_LIBGR_NOT_INITIALIZED + 63     */
/* SizeOfISO8859String               EXIT_DLL_LIBGR_NOT_INITIALIZED + 64     */
/* GetExtendedPoliceSize             EXIT_DLL_LIBGR_NOT_INITIALIZED + 65     */
/* DrawExtendedStringUnicode         EXIT_DLL_LIBGR_NOT_INITIALIZED + 66     */
/* LoadFont                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 67     */
/* ScrollString8859                  EXIT_DLL_LIBGR_NOT_INITIALIZED + 70     */
/* _ScrollString8859                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 71     */
/* ScrollStringUnicode               EXIT_DLL_LIBGR_NOT_INITIALIZED + 72     */
/* _ScrollStringUnicode              EXIT_DLL_LIBGR_NOT_INITIALIZED + 73     */
/* DefPrinterMargins                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 74     */
/* GetCurrentFont                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 75     */
/* PrintBmp                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 76     */
/* _PrintBmp                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 77     */
/* GetDefaultFONaddress              EXIT_DLL_LIBGR_NOT_INITIALIZED + 78     */
/* GetFontName                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 79     */
/* _PrintBmpXY                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 80     */
/* PaintPrinterGraphics              EXIT_DLL_LIBGR_NOT_INITIALIZED + 81     */
/* InitPrinterBitmap                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 82     */
/* _pprintfUnicodeXY                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 83     */
/* _pprintfUnicode                   EXIT_DLL_LIBGR_NOT_INITIALIZED + 84     */
/* _pprintf8859XY                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 85     */
/* _pprintf8859                      EXIT_DLL_LIBGR_NOT_INITIALIZED + 86     */
/* SetRegion                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 88     */
/* GetRegion                         EXIT_DLL_LIBGR_NOT_INITIALIZED + 89     */
/* ClearRegion                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 90     */
/* Paint                             EXIT_DLL_LIBGR_NOT_INITIALIZED + 104    */
/* RefreshUserArea                   EXIT_DLL_LIBGR_NOT_INITIALIZED + 105    */
/* RedrawUserArea                    EXIT_DLL_LIBGR_NOT_INITIALIZED + 106    */
/* GetColorScreenInfo                EXIT_DLL_LIBGR_NOT_INITIALIZED + 107    */
/* clrscr                            EXIT_DLL_LIBGR_NOT_INITIALIZED + 109    */
/* UnloadFont                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 111    */
/* GetFontPoliceSize                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 112    */
/* SizeOfUnicodeFontString           EXIT_DLL_LIBGR_NOT_INITIALIZED + 118    */
/* SizeOfISO8859FontString           EXIT_DLL_LIBGR_NOT_INITIALIZED + 119    */
/* InitModeGraphique                 EXIT_DLL_LIBGR_NOT_INITIALIZED + 121    */
/* GetBmpInfos                       EXIT_DLL_LIBGR_NOT_INITIALIZED + 122    */
/* ConvertIso8859toUnicode           EXIT_DLL_LIBGR_NOT_INITIALIZED + 129    */
/* GetBitMapUNICODE                  EXIT_DLL_LIBGR_NOT_INITIALIZED + 130    */
/* SearchFont                        EXIT_DLL_LIBGR_NOT_INITIALIZED + 131    */
/* SetColor                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 132    */
/* SetColorDisplay                   EXIT_DLL_LIBGR_NOT_INITIALIZED + 133    */
/* GetColor                          EXIT_DLL_LIBGR_NOT_INITIALIZED + 134    */
/* ISO8859Arabic2Unicode             EXIT_DLL_LIBGR_NOT_INITIALIZED + 135    */
/*****************************************************************************/
#define EXIT_DLL_EXTENS_NOT_INITIALIZED    0x0A00
/*****************************************************************************/
/* MO_Request                        EXIT_DLL_EXTENS_NOT_INITIALIZED + 2     */
/* GetMacAddress                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 3     */
/* Get_TypeCode                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 4     */
/* Get_Appli_Number                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 5     */
/* Hors_Ligne                        EXIT_DLL_EXTENS_NOT_INITIALIZED + 6     */
/* Validation_Hors_Ligne             EXIT_DLL_EXTENS_NOT_INITIALIZED + 7     */
/* Devalidation_Hors_Ligne           EXIT_DLL_EXTENS_NOT_INITIALIZED + 8     */
/* Emission_Modem                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 9     */
/* Reception_Co_Modem                EXIT_DLL_EXTENS_NOT_INITIALIZED + 10    */
/* Reception_Ca_Modem                EXIT_DLL_EXTENS_NOT_INITIALIZED + 11    */
/* Reception_To_Modem                EXIT_DLL_EXTENS_NOT_INITIALIZED + 12    */
/* Reception_Buf_Modem               EXIT_DLL_EXTENS_NOT_INITIALIZED + 13    */
/* Validation_DCD                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 14    */
/* Devalidation_DCD                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 15    */
/* GetHeaderArea                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 16    */
/* USQ_Calcrc_iso3309                EXIT_DLL_EXTENS_NOT_INITIALIZED + 17    */
/* USQ_Ajouterjour                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 19    */
/* USQ_Enleverjour                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 20    */
/* USQ_Enlevermn                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 21    */
/* USQ_Jourprecedent                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 22    */
/* USQ_Ajoutermnsec                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 23    */
/* USQ_Ajoutermn                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 24    */
/* USQ_Saisie_montant                EXIT_DLL_EXTENS_NOT_INITIALIZED + 25    */
/* USQ_Enlevermnsec                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 27    */
/* SLSQ_Ecart_heure_minute_seconde   EXIT_DLL_EXTENS_NOT_INITIALIZED + 28    */
/* USQ_Niveau_seq                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 29    */
/* Ascbin                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 32    */
/* Aschex                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 33    */
/* Binasc                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 34    */
/* Binhex                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 35    */
/* Hexasc                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 36    */
/* SLC_Affichage_choix               EXIT_DLL_EXTENS_NOT_INITIALIZED + 37    */
/* SLC_Afficher                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 38    */
/* SLC_Afficher_montant              EXIT_DLL_EXTENS_NOT_INITIALIZED + 39    */
/* SLC_Ajoutermn                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 40    */
/* SLC_Attente_carte                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 41    */
/* SLC_Attente_crtcli                EXIT_DLL_EXTENS_NOT_INITIALIZED + 42    */
/* SLC_Clear_display                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 45    */
/* SLC_Ecart_date                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 46    */
/* SLC_Ecart_heure                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 47    */
/* SLC_Effacer_ligne                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 48    */
/* SLC_Joursuivant                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 49    */
/* SLC_Retrait_puce                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 50    */
/* USQ_Aschex_alphanum               EXIT_DLL_EXTENS_NOT_INITIALIZED + 51    */
/* d_tolong                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 52    */
/* longto_d                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 53    */
/* USQ_Demande_money                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 54    */
/* PSLQ_Est_portable                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 55    */
/* stdcam0                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 56    */
/* stdcam1                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 57    */
/* stdcom0                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 58    */
/* stdcom1                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 59    */
/* stdmodem                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 60    */
/* SLSQ_Afficher_message             EXIT_DLL_EXTENS_NOT_INITIALIZED + 61    */
/* SLSQ_Afficher_message_ss_eff      EXIT_DLL_EXTENS_NOT_INITIALIZED + 62    */
/* SLSQ_Afficher_bienvenue           EXIT_DLL_EXTENS_NOT_INITIALIZED + 63    */
/* SLC_Moteur                        EXIT_DLL_EXTENS_NOT_INITIALIZED + 66    */
/* SLC_Error                         EXIT_DLL_EXTENS_NOT_INITIALIZED + 67    */
/* LireMessage                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 68    */
/* Get_Nb_Segment                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 73    */
/* G_Saisie_montant                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 79    */
/* USR_ServiceCall                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 86    */
/* GetSemaphoreUser                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 88    */
/* FreeSemaphoreUser                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 89    */
/* GetMailboxUser                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 90    */
/* FreeMailboxUser                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 91    */
/* GetDelayUser                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 92    */
/* FreeDelayUser                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 93    */
/* cde_com0                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 96    */
/* stdprt                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 97    */
/* Get_AppliName                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 99    */
/* Get_AppliCrc                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 100   */
/* Get_AppliData                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 101   */
/* DLLExist                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 102   */
/* USQ_Rechercher_money              EXIT_DLL_EXTENS_NOT_INITIALIZED + 105   */
/* getdate                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 106   */
/* GetAmount                         EXIT_DLL_EXTENS_NOT_INITIALIZED + 107   */
/* Get_AppliCode                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 108   */
/* stdcom2                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 109   */
/* stdcom5                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 110   */
/* Get_FileName                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 111   */
/* remote_downloading                EXIT_DLL_EXTENS_NOT_INITIALIZED + 112   */
/* remote_diagnostic                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 113   */
/* remote_download                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 114   */
/* G_Afficher                        EXIT_DLL_EXTENS_NOT_INITIALIZED + 115   */
/* G_AfficherPpr                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 116   */
/* StopPatchAppli                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 119   */
/* StartPatchAppli                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 120   */
/* remote_licencing                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 123   */
/* GestionRetourSocle                EXIT_DLL_EXTENS_NOT_INITIALIZED + 125   */
/* GestionSocle                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 126   */
/* SetModemEvent                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 127   */
/* SetPatchAppli                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 128   */
/* GetGeneralStatus                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 129   */
/* SetGeneralStatus                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 130   */
/* USQ_EthernetConfig                EXIT_DLL_EXTENS_NOT_INITIALIZED + 131   */
/* G_AfficherC30                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 132   */
/* IsHeaderActivated                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 133   */
/* USQ_Rechercher_money_etendue      EXIT_DLL_EXTENS_NOT_INITIALIZED + 134   */
/* _DisplayMSGinfos                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 135   */
/* SizeOfMSGinfos                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 136   */
/* _wDrawWindow                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 137   */
/* _wDrawWindowFont                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 138   */
/* DefCurrentMSG                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 139   */
/* GetCurrentMSG                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 140   */
/* DefDefaultMSG                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 141   */
/* GetDefaultMSG                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 142   */
/* DefCurrentLang                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 143   */
/* GetCurrentLang                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 144   */
/* DefDefaultLang                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 145   */
/* GetDefaultLang                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 146   */
/* GetManagerLanguage                EXIT_DLL_EXTENS_NOT_INITIALIZED + 147   */
/* GetFileType                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 148   */
/* GetAppliType                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 149   */
/* GetSpecificMessage                EXIT_DLL_EXTENS_NOT_INITIALIZED + 150   */
/* InitMSGinfos                      EXIT_DLL_EXTENS_NOT_INITIALIZED + 152   */
/* GetMessageInfos                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 154   */
/* DisplayMSG                        EXIT_DLL_EXTENS_NOT_INITIALIZED + 155   */
/* PrintMSG                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 156   */
/* LanguageExist                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 157   */
/* GetSupportedLanguages             EXIT_DLL_EXTENS_NOT_INITIALIZED + 158   */
/* GetMessageInfosInLang             EXIT_DLL_EXTENS_NOT_INITIALIZED + 159   */
/* G_AfficherMSG                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 160   */
/* _DisplayMSG                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 161   */
/* G_AfficherPprMSG                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 162   */
/* wG_AfficherC30                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 163   */
/* swprintf                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 166   */
/* SLC_AfficherMSG                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 168   */
/* wcslen                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 169   */
/* wcschr                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 170   */
/* wcsncpy                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 171   */
/* wcscat                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 172   */
/* wcscmp                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 173   */
/* wcscpy                            EXIT_DLL_EXTENS_NOT_INITIALIZED + 174   */
/* wcsncat                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 175   */
/* printfMSGInfos                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 177   */
/* printfMSG                         EXIT_DLL_EXTENS_NOT_INITIALIZED + 178   */
/* PrintMSGInfos                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 179   */
/* G_AfficherMSGnum                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 180   */
/* G_AfficherPprMSGnum               EXIT_DLL_EXTENS_NOT_INITIALIZED + 181   */
/* InitMSGinfos_message              EXIT_DLL_EXTENS_NOT_INITIALIZED + 182   */
/* wGetModemEvent                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 183   */
/* LoadMSG                           EXIT_DLL_EXTENS_NOT_INITIALIZED + 184   */
/* SWorSprintf                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 186   */
/* swprintf_liste                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 188   */
/* pprintf_SWorS                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 189   */
/* wSLC_Saisie_Liste                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 191   */
/* wSetModemEvent                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 192   */
/* DisplayMSGinfos                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 193   */
/* G_AfficherMSGcust                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 195   */
/* SetLedEvent                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 198   */
/* GetLedEvent                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 199   */
/* GetHeaderSize                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 200   */
/* SetHeaderSize                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 201   */
/* SetHeaderPosition                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 202   */
/* GetBtHandle                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 203   */
/* GetPeriphState                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 204   */
/* IsBaseKnown                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 205   */
/* IsBaseConnected                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 206   */
/* GetBaseName                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 207   */
/* Get_BtLevel                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 208   */
/* Get_battery_level                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 209   */
/* Get_Network_State                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 210   */
/* Get_SIM_State                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 211   */
/* Get_GPRS_State                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 212   */
/* Get_GPRS_Radio_Level              EXIT_DLL_EXTENS_NOT_INITIALIZED + 213   */
/* EraseHeader                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 214   */
/* EraseInfoArea                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 215   */
/* RefreshBattHeader                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 216   */
/* RefreshBaseHeader                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 218   */
/* RefreshNetworkHeader              EXIT_DLL_EXTENS_NOT_INITIALIZED + 219   */
/* RefreshEthernetHeader             EXIT_DLL_EXTENS_NOT_INITIALIZED + 220   */
/* RefreshGPRSHeader                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 221   */
/* RefreshWirelessHeader             EXIT_DLL_EXTENS_NOT_INITIALIZED + 222   */
/* RefreshInfoArea                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 223   */
/* DrawText                          EXIT_DLL_EXTENS_NOT_INITIALIZED + 225   */
/* _DrawText                         EXIT_DLL_EXTENS_NOT_INITIALIZED + 226   */
/* GetScreenArea                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 227   */
/* SetLedBlinking                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 228   */
/* SetLedColor                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 229   */
/* Beep                              EXIT_DLL_EXTENS_NOT_INITIALIZED + 231   */
/* SetFooterPosition                 EXIT_DLL_EXTENS_NOT_INITIALIZED + 232   */
/* GetLedsSize                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 233   */
/* CGUIGetAmount                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 238   */
/* Get_StateWGUI                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 241   */
/* GetCGUIContext                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 242   */
/* PushCGUIContext                   EXIT_DLL_EXTENS_NOT_INITIALIZED + 242   */
/* PopCGUIContext                    EXIT_DLL_EXTENS_NOT_INITIALIZED + 242   */
/* GetLedColor                       EXIT_DLL_EXTENS_NOT_INITIALIZED + 245   */
/* GetFooterSize                     EXIT_DLL_EXTENS_NOT_INITIALIZED + 246   */
/* G_AfficherC30MSGnum               EXIT_DLL_EXTENS_NOT_INITIALIZED + 247   */
/* G_AfficherC30MSG                  EXIT_DLL_EXTENS_NOT_INITIALIZED + 248   */
/*****************************************************************************/
#define EXIT_DLL_PARAM_NOT_INITIALIZED     0x0B00
/******************************************************************************/
/* PSQ_Donner_format_date             EXIT_DLL_PARAM_NOT_INITIALIZED + 6      */
/* PSQ_Donner_langue                  EXIT_DLL_PARAM_NOT_INITIALIZED + 7      */
/* PSQ_No_terminal                    EXIT_DLL_PARAM_NOT_INITIALIZED + 8      */
/* PSQ_Est_money                      EXIT_DLL_PARAM_NOT_INITIALIZED + 9      */
/* PSQ_No_standard                    EXIT_DLL_PARAM_NOT_INITIALIZED + 10     */
/* PSQ_Est_pinpad                     EXIT_DLL_PARAM_NOT_INITIALIZED + 11     */
/* PSQ_type_pinpad                    EXIT_DLL_PARAM_NOT_INITIALIZED + 12     */
/* PSQ_Est_ISO2                       EXIT_DLL_PARAM_NOT_INITIALIZED + 13     */
/* PSQ_Est_ISO1                       EXIT_DLL_PARAM_NOT_INITIALIZED + 14     */
/* PSQ_Est_ISO3                       EXIT_DLL_PARAM_NOT_INITIALIZED + 15     */
/* PSQ_Donner_noserie                 EXIT_DLL_PARAM_NOT_INITIALIZED + 16     */
/* PSQ_get_no_lecteur                 EXIT_DLL_PARAM_NOT_INITIALIZED + 17     */
/* PSQ_get_vitesse_lecteur            EXIT_DLL_PARAM_NOT_INITIALIZED + 18     */
/* PSQ_Est_chainage                   EXIT_DLL_PARAM_NOT_INITIALIZED + 19     */
/* PSQ_Est_RTC                        EXIT_DLL_PARAM_NOT_INITIALIZED + 20     */
/* PSQ_Est_cbcom_RTC                  EXIT_DLL_PARAM_NOT_INITIALIZED + 21     */
/* PSQ_Est_CLE                        EXIT_DLL_PARAM_NOT_INITIALIZED + 22     */
/* PSQ_Est_dtr                        EXIT_DLL_PARAM_NOT_INITIALIZED + 23     */
/* PSQ_Est_RNIS                       EXIT_DLL_PARAM_NOT_INITIALIZED + 24     */
/* PSQ_Est_GSM                        EXIT_DLL_PARAM_NOT_INITIALIZED + 25     */
/* PSQ_Donner_infos_reseau            EXIT_DLL_PARAM_NOT_INITIALIZED + 26     */
/* PSQ_Est_com_reseau                 EXIT_DLL_PARAM_NOT_INITIALIZED + 27     */
/* PSQ_Idf_telechgt                   EXIT_DLL_PARAM_NOT_INITIALIZED + 28     */
/* PSQ_Donner_reference               EXIT_DLL_PARAM_NOT_INITIALIZED + 30     */
/* PSQ_Est_double90                   EXIT_DLL_PARAM_NOT_INITIALIZED + 32     */
/* PSQ_Double90_cle                   EXIT_DLL_PARAM_NOT_INITIALIZED + 33     */
/* PSQ_Est_pinpad_2_lignes            EXIT_DLL_PARAM_NOT_INITIALIZED + 34     */
/* PSQ_Est_caisse                     EXIT_DLL_PARAM_NOT_INITIALIZED + 36     */
/* is_F_Manager                       EXIT_DLL_PARAM_NOT_INITIALIZED + 38     */
/* PSQ_Update_language                EXIT_DLL_PARAM_NOT_INITIALIZED + 39     */
/* PSQ_Update_phonenumber             EXIT_DLL_PARAM_NOT_INITIALIZED + 40     */
/* PSQ_Update_pabx                    EXIT_DLL_PARAM_NOT_INITIALIZED + 41     */
/* PSQ_Est_pinpad_lecteur             EXIT_DLL_PARAM_NOT_INITIALIZED + 43     */
/* PSQ_Manager_F                      EXIT_DLL_PARAM_NOT_INITIALIZED + 44     */
/* PSQ_Update_Cash_Connection         EXIT_DLL_PARAM_NOT_INITIALIZED + 45     */
/* PSQ_lire_type_materiel             EXIT_DLL_PARAM_NOT_INITIALIZED + 46     */
/* GetPackInfos                       EXIT_DLL_PARAM_NOT_INITIALIZED + 48     */
/* PSQ_Donner_infos_reseau_sup        EXIT_DLL_PARAM_NOT_INITIALIZED + 49     */
/* Powered                            EXIT_DLL_PARAM_NOT_INITIALIZED + 50     */
/* PSQ_telechgt                       EXIT_DLL_PARAM_NOT_INITIALIZED + 51     */
/* PSQ_lire_param                     EXIT_DLL_PARAM_NOT_INITIALIZED + 52     */
/* PSQ_ecrire_param                   EXIT_DLL_PARAM_NOT_INITIALIZED + 53     */
/* PSQ_Idf_telechgt_auto              EXIT_DLL_PARAM_NOT_INITIALIZED + 54     */
/* PSQ_Est_c30                        EXIT_DLL_PARAM_NOT_INITIALIZED + 55     */
/* PSQ_GetPacksInfos                  EXIT_DLL_PARAM_NOT_INITIALIZED + 56     */
/* PSQ_Est_Modem_Sur_Socle            EXIT_DLL_PARAM_NOT_INITIALIZED + 57     */
/* PSQ_Est_Forcage_V32                EXIT_DLL_PARAM_NOT_INITIALIZED + 58     */
/* PSQ_Est_PAD_Forcage_V32            EXIT_DLL_PARAM_NOT_INITIALIZED + 59     */
/* PSQ_est_pinpad_graphique           EXIT_DLL_PARAM_NOT_INITIALIZED + 70     */
/* PSQ_type_pinpad                    EXIT_DLL_PARAM_NOT_INITIALIZED + 71     */
/* PSQ_presence_swipe                 EXIT_DLL_PARAM_NOT_INITIALIZED + 72     */
/* PSQ_Is_Printer                     EXIT_DLL_PARAM_NOT_INITIALIZED + 73     */
/* PSQ_Donner_infos_reseau_sup_repli  EXIT_DLL_PARAM_NOT_INITIALIZED + 74     */
/* PSQ_Is_Ucm_Behaviour               EXIT_DLL_PARAM_NOT_INITIALIZED + 75     */
/* PSQ_Lire_Gamme_Produit             EXIT_DLL_PARAM_NOT_INITIALIZED + 80     */
/* PSQ_Donner_infos_apn               EXIT_DLL_PARAM_NOT_INITIALIZED + 81     */
/* wShortCutRegister                  EXIT_DLL_PARAM_NOT_INITIALIZED + 82     */
/* PSQ_Start_gprs                     EXIT_DLL_PARAM_NOT_INITIALIZED + 83     */
/* PSQ_write_state_param              EXIT_DLL_PARAM_NOT_INITIALIZED + 88     */
/* PSQ_read_state_param               EXIT_DLL_PARAM_NOT_INITIALIZED + 89     */
/* PSQ_Write_money                    EXIT_DLL_PARAM_NOT_INITIALIZED + 91     */
/* PSQ_SetPinpad                      EXIT_DLL_PARAM_NOT_INITIALIZED + 92     */
/* PSQ_init_ippcolor                  EXIT_DLL_PARAM_NOT_INITIALIZED + 94     */
/* PSQ_Get_Cless_Capabilities         EXIT_DLL_PARAM_NOT_INITIALIZED + 95     */
/* IST1XX_init_color                  EXIT_DLL_PARAM_NOT_INITIALIZED + 97     */
/*****************************************************************************/
#define EXIT_DLL_CB2A_NOT_INITIALIZED      0x0C00
/*****************************************************************************/
/* SERVEUR_demander_service          EXIT_DLL_CB2A_NOT_INITIALIZED + 0       */
/* SERVEUR_demander_auto             EXIT_DLL_CB2A_NOT_INITIALIZED + 1       */
/* PSQ_Est_Cb2a_compatibilite        EXIT_DLL_CB2A_NOT_INITIALIZED + 2       */
/* ipdu_etab_ligne                   EXIT_DLL_CB2A_NOT_INITIALIZED + 9       */
/* ipdu_coup_ligne                   EXIT_DLL_CB2A_NOT_INITIALIZED + 10      */
/* ipdu_deconnecte                   EXIT_DLL_CB2A_NOT_INITIALIZED + 11      */
/* ipdu_de_write                     EXIT_DLL_CB2A_NOT_INITIALIZED + 12      */
/* ipdu_dt_read                      EXIT_DLL_CB2A_NOT_INITIALIZED + 13      */
/* EXTCC_connexion                   EXIT_DLL_CB2A_NOT_INITIALIZED + 14      */
/* EXTCC_emission                    EXIT_DLL_CB2A_NOT_INITIALIZED + 15      */
/* EXTCC_reception                   EXIT_DLL_CB2A_NOT_INITIALIZED + 16      */
/* EXTCC_Handle                      EXIT_DLL_CB2A_NOT_INITIALIZED + 17      */
/* EXTCC_Reset_buf                   EXIT_DLL_CB2A_NOT_INITIALIZED + 18      */
/* EXTCC_Numero_Message_V42A         EXIT_DLL_CB2A_NOT_INITIALIZED + 19      */
/* EXTCC_init_liste                  EXIT_DLL_CB2A_NOT_INITIALIZED + 20      */
/* EXTCC_ajoute_liste                EXIT_DLL_CB2A_NOT_INITIALIZED + 21      */
/* EXTCC_extraire_liste              EXIT_DLL_CB2A_NOT_INITIALIZED + 22      */
/* EXTCC_deconnexion                 EXIT_DLL_CB2A_NOT_INITIALIZED + 23      */
/* CC_Validation_Hors_Ligne          EXIT_DLL_CB2A_NOT_INITIALIZED + 24      */
/* CC_Devalidation_Hors_Ligne        EXIT_DLL_CB2A_NOT_INITIALIZED + 25      */
/* CC_Hors_Ligne                     EXIT_DLL_CB2A_NOT_INITIALIZED + 26      */
/* CC_Emission_Modem                 EXIT_DLL_CB2A_NOT_INITIALIZED + 27      */
/* CC_Reception_Co_Modem             EXIT_DLL_CB2A_NOT_INITIALIZED + 28      */
/* CC_Reception_Ca_Modem             EXIT_DLL_CB2A_NOT_INITIALIZED + 29      */
/* CC_Reception_To_Modem             EXIT_DLL_CB2A_NOT_INITIALIZED + 30      */
/* CC_Reception_Buf_Modem            EXIT_DLL_CB2A_NOT_INITIALIZED + 31      */
/* CC_Validation_DCD                 EXIT_DLL_CB2A_NOT_INITIALIZED + 32      */
/* CC_Devalidation_DCD               EXIT_DLL_CB2A_NOT_INITIALIZED + 33      */
/* InitSysCB2A                       EXIT_DLL_CB2A_NOT_INITIALIZED + 34      */
/* ipdu_get_timer_effectif           EXIT_DLL_CB2A_NOT_INITIALIZED + 35      */
/* ipdu_capacite_raccordement        EXIT_DLL_CB2A_NOT_INITIALIZED + 36      */
/*****************************************************************************/
#define EXIT_DLL_SV_NOT_INITIALIZED        0x0D00
/*****************************************************************************/
/* OS_GetIdLecteur                   EXIT_DLL_SV_NOT_INITIALIZED + 0         */
/* OS_ClkDate                        EXIT_DLL_SV_NOT_INITIALIZED + 1         */
/* OS_ClkTime                        EXIT_DLL_SV_NOT_INITIALIZED + 2         */
/* OS_ClkInit                        EXIT_DLL_SV_NOT_INITIALIZED + 3         */
/* OS_ScrInit                        EXIT_DLL_SV_NOT_INITIALIZED + 4         */
/* OS_ScrMessage                     EXIT_DLL_SV_NOT_INITIALIZED + 5         */
/* OS_KbdFlush                       EXIT_DLL_SV_NOT_INITIALIZED + 6         */
/* OS_KbdKey                         EXIT_DLL_SV_NOT_INITIALIZED + 7         */
/* OS_SndBip                         EXIT_DLL_SV_NOT_INITIALIZED + 8         */
/* OS_CamOff                         EXIT_DLL_SV_NOT_INITIALIZED + 9         */
/* OS_CamOrder                       EXIT_DLL_SV_NOT_INITIALIZED + 10        */
/* OS_CamPres                        EXIT_DLL_SV_NOT_INITIALIZED + 11        */
/* OS_CamReset                       EXIT_DLL_SV_NOT_INITIALIZED + 12        */
/* OS_CamEtat                        EXIT_DLL_SV_NOT_INITIALIZED + 13        */
/* OS_CamInitEtat                    EXIT_DLL_SV_NOT_INITIALIZED + 14        */
/* OS_SysVerif                       EXIT_DLL_SV_NOT_INITIALIZED + 15        */
/* OS_SysGetParam                    EXIT_DLL_SV_NOT_INITIALIZED + 16        */
/* OS_SysGetParamAppli               EXIT_DLL_SV_NOT_INITIALIZED + 17        */
/* OS_SysGetFreeSpace                EXIT_DLL_SV_NOT_INITIALIZED + 18        */
/* SV_power_down                     EXIT_DLL_SV_NOT_INITIALIZED + 19        */
/* SV_input_command                  EXIT_DLL_SV_NOT_INITIALIZED + 20        */
/* SV_output_command                 EXIT_DLL_SV_NOT_INITIALIZED + 21        */
/* SV_power_on                       EXIT_DLL_SV_NOT_INITIALIZED + 22        */
/* SV_read_date                      EXIT_DLL_SV_NOT_INITIALIZED + 23        */
/* SV_write_date                     EXIT_DLL_SV_NOT_INITIALIZED + 24        */
/* SLSQ_EcartDate                    EXIT_DLL_SV_NOT_INITIALIZED + 25        */
/* SLSQ_EcartHeure                   EXIT_DLL_SV_NOT_INITIALIZED + 26        */
/* SLSQ_CalculJourSemaine            EXIT_DLL_SV_NOT_INITIALIZED + 27        */
/* SV_suppr_info_seg                 EXIT_DLL_SV_NOT_INITIALIZED + 29        */
/* allocate                          EXIT_DLL_SV_NOT_INITIALIZED + 30        */
/* activate                          EXIT_DLL_SV_NOT_INITIALIZED + 31        */
/* SLSQ_VerifTime                    EXIT_DLL_SV_NOT_INITIALIZED + 32        */
/* SLSQ_VerifDate                    EXIT_DLL_SV_NOT_INITIALIZED + 33        */
/* splitpath                         EXIT_DLL_SV_NOT_INITIALIZED + 34        */
/* lire_etat_materiel                EXIT_DLL_SV_NOT_INITIALIZED + 35        */
/* OpenPrivateProfile                EXIT_DLL_SV_NOT_INITIALIZED + 36        */
/* ClosePrivateProfile               EXIT_DLL_SV_NOT_INITIALIZED + 37        */
/* GetPrivateProfileInt              EXIT_DLL_SV_NOT_INITIALIZED + 38        */
/* GetPrivateProfileString           EXIT_DLL_SV_NOT_INITIALIZED + 39        */
/* Spy                               EXIT_DLL_SV_NOT_INITIALIZED + 40        */
/* BmpToPattern                      EXIT_DLL_SV_NOT_INITIALIZED + 41        */
/* iso2                              EXIT_DLL_SV_NOT_INITIALIZED + 42        */
/* OS_CamInit                        EXIT_DLL_SV_NOT_INITIALIZED + 43        */
/* OpenPrivateProfileObject          EXIT_DLL_SV_NOT_INITIALIZED + 44        */
/* OS_CamOrderLg                     EXIT_DLL_SV_NOT_INITIALIZED + 45        */
/* OS_ClkGetMilliseconds             EXIT_DLL_SV_NOT_INITIALIZED + 46        */
/*****************************************************************************/
#define EXIT_DLL_PSC_NOT_INITIALIZED       0x0F00
/*****************************************************************************/
/* Open_Psc                          EXIT_DLL_PSC_NOT_INITIALIZED + 0        */
/* Send_Psc                          EXIT_DLL_PSC_NOT_INITIALIZED + 1        */
/* Suspend_Psc                       EXIT_DLL_PSC_NOT_INITIALIZED + 2        */
/* Close_Psc                         EXIT_DLL_PSC_NOT_INITIALIZED + 3        */
/* Read_Psc                          EXIT_DLL_PSC_NOT_INITIALIZED + 4        */
/* Prise_Contact                     EXIT_DLL_PSC_NOT_INITIALIZED + 5        */
/* Receive_Psc                       EXIT_DLL_PSC_NOT_INITIALIZED + 6        */
/* Init_Psc                          EXIT_DLL_PSC_NOT_INITIALIZED + 7        */
/* Version_Psc                       EXIT_DLL_PSC_NOT_INITIALIZED + 8        */
/*****************************************************************************/
#define EXIT_DLL_PROTOCOLE_NOT_INITIALIZED 0x1000
/*****************************************************************************/
/* CA_Init_noappli                   EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 4  */
/* CA_Donner_noappli                 EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 5  */
/* CA_Application_en_cours           EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 6  */
/* CA_Dialogue_en_cours              EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 7  */
/* DIAL_Recept                       EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 8  */
/* DIAL_Emiss                        EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 9  */
/* DIAL_DemTemps                     EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 10 */
/* OS_SysGetParamEXT                 EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 11 */
/* APPLI_Dialogue                    EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 12 */
/* ParamDLLProtocole                 EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 13 */
/* PrintDLLProtocole                 EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 14 */
/* DefaultDLLProtocole               EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 15 */
/* FP_ParamDLLProtocole              EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 16 */
/* FP_Ecrire_ParamDLLProtocole       EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 17 */
/* DIAL_EnvoyerEvt                   EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 18 */
/* DIAL_ActiverTLV4                  EXIT_DLL_PROTOCOLE_NOT_INITIALIZED + 19 */
/*****************************************************************************/
#define EXIT_DLL_LANGUE_NOT_INITIALIZED    0x1100
/*****************************************************************************/
/* GetExtendedMessage                EXIT_DLL_LANGUE_NOT_INITIALIZED + 0     */
/* GetExtendedLangage                EXIT_DLL_LANGUE_NOT_INITIALIZED + 1     */
/* GetCurrentExtendedLangage         EXIT_DLL_LANGUE_NOT_INITIALIZED + 2     */
/*****************************************************************************/
#define EXIT_DLL_PINPAD_NOT_INITIALIZED    0x1200
/*****************************************************************************/
/* Saisie_Numerique_Ppad             EXIT_DLL_PINPAD_NOT_INITIALIZED + 0     */
/* Saisie_Fonction_Ppad              EXIT_DLL_PINPAD_NOT_INITIALIZED + 1     */
/* Stop_Saisie_Ppad                  EXIT_DLL_PINPAD_NOT_INITIALIZED + 2     */
/* Read_Saisie_Ppad                  EXIT_DLL_PINPAD_NOT_INITIALIZED + 3     */
/* PPS_newline                       EXIT_DLL_PINPAD_NOT_INITIALIZED + 7     */
/* PPS_clearline                     EXIT_DLL_PINPAD_NOT_INITIALIZED + 8     */
/* PPS_firstline                     EXIT_DLL_PINPAD_NOT_INITIALIZED + 9     */
/* reset_pinpad                      EXIT_DLL_PINPAD_NOT_INITIALIZED + 10    */
/* PPS_Display                       EXIT_DLL_PINPAD_NOT_INITIALIZED + 11    */
/* PPS_Version                       EXIT_DLL_PINPAD_NOT_INITIALIZED + 13    */
/* PPS_clear_display                 EXIT_DLL_PINPAD_NOT_INITIALIZED + 14    */
/* IsPPSConnected                    EXIT_DLL_PINPAD_NOT_INITIALIZED + 15    */
/* PPS_Num_Entry_T                   EXIT_DLL_PINPAD_NOT_INITIALIZED + 17    */
/* PPS_SetComFormat                  EXIT_DLL_PINPAD_NOT_INITIALIZED + 25    */
/* PPS_print_diagnostic              EXIT_DLL_PINPAD_NOT_INITIALIZED + 26    */
/* EstDllReader                      EXIT_DLL_PINPAD_NOT_INITIALIZED + 27    */
/* ClearFrenchWarningDisplay         EXIT_DLL_PINPAD_NOT_INITIALIZED + 28    */
/* TransfertToBooster                EXIT_DLL_PINPAD_NOT_INITIALIZED + 30    */
/* PPR_niveau_securite               EXIT_DLL_PINPAD_NOT_INITIALIZED + 31    */
/* PPR_FastIsConnected               EXIT_DLL_PINPAD_NOT_INITIALIZED + 32    */
/* PPR_Type                          EXIT_DLL_PINPAD_NOT_INITIALIZED + 34    */
/* P30_GetHardwareCapabilities       EXIT_DLL_PINPAD_NOT_INITIALIZED + 35    */
/* P30_ConfigSwipe                   EXIT_DLL_PINPAD_NOT_INITIALIZED + 36    */
/* P30_PrintHardwareCapabilities     EXIT_DLL_PINPAD_NOT_INITIALIZED + 37    */
/* P30_PrintComponents               EXIT_DLL_PINPAD_NOT_INITIALIZED + 38    */
/* PPR_GetSerialNumber               EXIT_DLL_PINPAD_NOT_INITIALIZED + 39    */
/* PPR_GetActivationState            EXIT_DLL_PINPAD_NOT_INITIALIZED + 40    */
/*****************************************************************************/
#define EXIT_DLL_PARTAGE_NOT_INITIALIZED   0x1300
/*****************************************************************************/
/* PART_creer_fichier                EXIT_DLL_PARTAGE_NOT_INITIALIZED + 0    */
/* PART_ecrire_donnees               EXIT_DLL_PARTAGE_NOT_INITIALIZED + 1    */
/* PART_fermer_fichier               EXIT_DLL_PARTAGE_NOT_INITIALIZED + 2    */
/* PART_init_recherche               EXIT_DLL_PARTAGE_NOT_INITIALIZED + 3    */
/* PART_fichier_existe               EXIT_DLL_PARTAGE_NOT_INITIALIZED + 4    */
/* PART_lire_fichier                 EXIT_DLL_PARTAGE_NOT_INITIALIZED + 5    */
/* PART_effacer_fichier              EXIT_DLL_PARTAGE_NOT_INITIALIZED + 6    */
/* PART_stop_recherche               EXIT_DLL_PARTAGE_NOT_INITIALIZED + 7    */
/*****************************************************************************/
#define EXIT_DLL_EMVSQ_NOT_INITIALIZED     0x1400
/*****************************************************************************/
/*****************************************************************************/
#define EXIT_DLL_IAM_NOT_INITIALIZED       0x1500
/*****************************************************************************/
/* Send_Message                      EXIT_DLL_IAM_NOT_INITIALIZED + 0        */
/* Read_Message                      EXIT_DLL_IAM_NOT_INITIALIZED + 1        */
/* SQ_Is_Message_For_Me              EXIT_DLL_IAM_NOT_INITIALIZED + 2        */
/* Register_Mailbox_User             EXIT_DLL_IAM_NOT_INITIALIZED + 3        */
/* SendToAllApplication              EXIT_DLL_IAM_NOT_INITIALIZED + 5        */
/* SendToApplication                 EXIT_DLL_IAM_NOT_INITIALIZED + 6        */
/* SendToTask                        EXIT_DLL_IAM_NOT_INITIALIZED + 7        */
/*****************************************************************************/
#define EXIT_DLL_GPRS_NOT_INITIALIZED      0x1600
/*****************************************************************************/
/* gprs_connect                      EXIT_DLL_GPRS_NOT_INITIALIZED + 0       */
/* tcp_connect_to_server             EXIT_DLL_GPRS_NOT_INITIALIZED + 10      */
/* ssl_connect_to_server             EXIT_DLL_GPRS_NOT_INITIALIZED + 11      */
/* tcp_send_to_server                EXIT_DLL_GPRS_NOT_INITIALIZED + 12      */
/* ssl_send_to_server                EXIT_DLL_GPRS_NOT_INITIALIZED + 13      */
/* tcp_recv_from_server              EXIT_DLL_GPRS_NOT_INITIALIZED + 14      */
/* ssl_recv_from_server              EXIT_DLL_GPRS_NOT_INITIALIZED + 15      */
/* tcp_disconnect_from_server        EXIT_DLL_GPRS_NOT_INITIALIZED + 16      */
/* ssl_disconnect_from_server        EXIT_DLL_GPRS_NOT_INITIALIZED + 17      */
/* gprs_stop                         EXIT_DLL_GPRS_NOT_INITIALIZED + 18      */
/* gsm_connect                       EXIT_DLL_GPRS_NOT_INITIALIZED + 19      */
/* gprs_errno                        EXIT_DLL_GPRS_NOT_INITIALIZED + 20      */
/* gprs_EmissionSMS                  EXIT_DLL_GPRS_NOT_INITIALIZED + 23      */
/* gsm_write                         EXIT_DLL_GPRS_NOT_INITIALIZED + 25      */
/* gsm_read                          EXIT_DLL_GPRS_NOT_INITIALIZED + 26      */
/* gsm_enable                        EXIT_DLL_GPRS_NOT_INITIALIZED + 27      */
/* gprs_enable                       EXIT_DLL_GPRS_NOT_INITIALIZED + 28      */
/* gprs_setpincode                   EXIT_DLL_GPRS_NOT_INITIALIZED + 29      */
/* gprslib_close                     EXIT_DLL_GPRS_NOT_INITIALIZED + 30      */
/* gprs_ppp_disconnect               EXIT_DLL_GPRS_NOT_INITIALIZED + 31      */
/* gprs_handle_ppp                   EXIT_DLL_GPRS_NOT_INITIALIZED + 32      */
/* connect_to_server                 EXIT_DLL_GPRS_NOT_INITIALIZED + 33      */
/* send_to_server                    EXIT_DLL_GPRS_NOT_INITIALIZED + 34      */
/* recv_from_server                  EXIT_DLL_GPRS_NOT_INITIALIZED + 35      */
/* disconnect_from_server            EXIT_DLL_GPRS_NOT_INITIALIZED + 36      */
/* SSL_connect_to_server             EXIT_DLL_GPRS_NOT_INITIALIZED + 37      */
/* SSL_send_to_server                EXIT_DLL_GPRS_NOT_INITIALIZED + 38      */
/* SSL_recv_from_server              EXIT_DLL_GPRS_NOT_INITIALIZED + 39      */
/* SSL_disconnect_from_server        EXIT_DLL_GPRS_NOT_INITIALIZED + 40      */
/* sms_set_sim_sca                   EXIT_DLL_GPRS_NOT_INITIALIZED + 41      */
/* sms_get_sim_sca                   EXIT_DLL_GPRS_NOT_INITIALIZED + 42      */
/* sms_send                          EXIT_DLL_GPRS_NOT_INITIALIZED + 43      */
/* sms_open                          EXIT_DLL_GPRS_NOT_INITIALIZED + 44      */
/* sms_first                         EXIT_DLL_GPRS_NOT_INITIALIZED + 45      */
/* sms_next                          EXIT_DLL_GPRS_NOT_INITIALIZED + 46      */
/* sms_wait                          EXIT_DLL_GPRS_NOT_INITIALIZED + 47      */
/* sms_read                          EXIT_DLL_GPRS_NOT_INITIALIZED + 48      */
/* sms_get_info                      EXIT_DLL_GPRS_NOT_INITIALIZED + 49      */
/* sms_delete                        EXIT_DLL_GPRS_NOT_INITIALIZED + 50      */
/* sms_purge_incomplete              EXIT_DLL_GPRS_NOT_INITIALIZED + 51      */
/* sms_close                         EXIT_DLL_GPRS_NOT_INITIALIZED + 52      */
/* sms_mem_info                      EXIT_DLL_GPRS_NOT_INITIALIZED + 53      */
/* gprs_submitpincode                EXIT_DLL_GPRS_NOT_INITIALIZED + 54      */
/* gprs_getParam                     EXIT_DLL_GPRS_NOT_INITIALIZED + 55      */
/*****************************************************************************/
#define EXIT_DLL_SSL_NOT_INITIALIZED       0x1700
/*****************************************************************************/
/* ngSSLAccept                       EXIT_DLL_SSL_NOT_INITIALIZED + 0        */
/* ngSSLAttachSockFd                 EXIT_DLL_SSL_NOT_INITIALIZED + 1        */
/* ngSSLCACertInfo                   EXIT_DLL_SSL_NOT_INITIALIZED + 2        */
/* ngSSLCertInfo                     EXIT_DLL_SSL_NOT_INITIALIZED + 3        */
/* ngSSLConnect                      EXIT_DLL_SSL_NOT_INITIALIZED + 4        */
/* ngSSLCtrl                         EXIT_DLL_SSL_NOT_INITIALIZED + 5        */
/* ngSSLCtxCtrl                      EXIT_DLL_SSL_NOT_INITIALIZED + 6        */
/* ngSSLCtxFree                      EXIT_DLL_SSL_NOT_INITIALIZED + 7        */
/* ngSSLCtxGetError                  EXIT_DLL_SSL_NOT_INITIALIZED + 8        */
/* ngSSLCtxGetTimeout                EXIT_DLL_SSL_NOT_INITIALIZED + 9        */
/* ngSSLCtxNew                       EXIT_DLL_SSL_NOT_INITIALIZED + 10       */
/* ngSSLCtxSessSetGetCb              EXIT_DLL_SSL_NOT_INITIALIZED + 11       */
/* ngSSLCtxSessSetNewCb              EXIT_DLL_SSL_NOT_INITIALIZED + 12       */
/* ngSSLCtxSessSetRemoveCb           EXIT_DLL_SSL_NOT_INITIALIZED + 13       */
/* ngSSLCtxSetCipherList             EXIT_DLL_SSL_NOT_INITIALIZED + 14       */
/* ngSSLCtxSetDefaultPasswdCb        EXIT_DLL_SSL_NOT_INITIALIZED + 15       */
/* ngSSLCtxSetInfoCallback           EXIT_DLL_SSL_NOT_INITIALIZED + 16       */
/* ngSSLCtxSetTimeout                EXIT_DLL_SSL_NOT_INITIALIZED + 17       */
/* ngSSLCtxSetVerify                 EXIT_DLL_SSL_NOT_INITIALIZED + 18       */
/* ngSSLCtxUseCertificateFile        EXIT_DLL_SSL_NOT_INITIALIZED + 19       */
/* ngSSLCtxUsePrivateKeyFile         EXIT_DLL_SSL_NOT_INITIALIZED + 20       */
/* ngSSLDoHandshake                  EXIT_DLL_SSL_NOT_INITIALIZED + 21       */
/* ngSSLFree                         EXIT_DLL_SSL_NOT_INITIALIZED + 22       */
/* ngSSLGetSession                   EXIT_DLL_SSL_NOT_INITIALIZED + 23       */
/* ngSSLGetVersion                   EXIT_DLL_SSL_NOT_INITIALIZED + 24       */
/* ngSSLNew                          EXIT_DLL_SSL_NOT_INITIALIZED + 25       */
/* ngSSLRead                         EXIT_DLL_SSL_NOT_INITIALIZED + 26       */
/* ngSSLRenegotiate                  EXIT_DLL_SSL_NOT_INITIALIZED + 27       */
/* ngSSLSessCertInfo                 EXIT_DLL_SSL_NOT_INITIALIZED + 28       */
/* ngSSLSetAcceptState               EXIT_DLL_SSL_NOT_INITIALIZED + 29       */
/* ngSSLSetConnectState              EXIT_DLL_SSL_NOT_INITIALIZED + 30       */
/* ngSSLCtxSetTmpDHCallback          EXIT_DLL_SSL_NOT_INITIALIZED + 31       */
/* ngSSLCtxSetTmpRSACallback         EXIT_DLL_SSL_NOT_INITIALIZED + 32       */
/* ngSSLShutdown                     EXIT_DLL_SSL_NOT_INITIALIZED + 33       */
/* ngSSLState                        EXIT_DLL_SSL_NOT_INITIALIZED + 34       */
/* ngSSLWrite                        EXIT_DLL_SSL_NOT_INITIALIZED + 35       */
/* SSLv2_method                      EXIT_DLL_SSL_NOT_INITIALIZED + 36       */
/* SSLv3_method                      EXIT_DLL_SSL_NOT_INITIALIZED + 37       */
/* SSLv23_method                     EXIT_DLL_SSL_NOT_INITIALIZED + 38       */
/* TLSv1_method                      EXIT_DLL_SSL_NOT_INITIALIZED + 39       */
/* loadCAFile                        EXIT_DLL_SSL_NOT_INITIALIZED + 40       */
/* SSL_set_session                   EXIT_DLL_SSL_NOT_INITIALIZED + 41       */
/* SSL_get_session                   EXIT_DLL_SSL_NOT_INITIALIZED + 42       */
/* SSL_New                           EXIT_DLL_SSL_NOT_INITIALIZED + 43       */
/* SSL_Free                          EXIT_DLL_SSL_NOT_INITIALIZED + 44       */
/* SSL_Connect                       EXIT_DLL_SSL_NOT_INITIALIZED + 45       */
/* SSL_Read                          EXIT_DLL_SSL_NOT_INITIALIZED + 46       */
/* SSL_Disconnect                    EXIT_DLL_SSL_NOT_INITIALIZED + 47       */
/* SSL_Write                         EXIT_DLL_SSL_NOT_INITIALIZED + 48       */
/* rsaCsrGen                         EXIT_DLL_SSL_NOT_INITIALIZED + 49       */
/* rsaKeyGen                         EXIT_DLL_SSL_NOT_INITIALIZED + 50       */
/* SSL_NewProfile                    EXIT_DLL_SSL_NOT_INITIALIZED + 51       */
/* SSL_LoadProfile                   EXIT_DLL_SSL_NOT_INITIALIZED + 52       */
/* SSL_UnloadProfile                 EXIT_DLL_SSL_NOT_INITIALIZED + 53       */
/* SSL_ProfileAddCertificateCA       EXIT_DLL_SSL_NOT_INITIALIZED + 54       */
/* SSL_ProfileRemoveCertificateCA    EXIT_DLL_SSL_NOT_INITIALIZED + 55       */
/* SSL_SaveProfile                   EXIT_DLL_SSL_NOT_INITIALIZED + 56       */
/* SSL_DeleteProfile                 EXIT_DLL_SSL_NOT_INITIALIZED + 57       */
/* SSL_ProfileGetLastError           EXIT_DLL_SSL_NOT_INITIALIZED + 58       */
/* SSL_ProfileGetCACount             EXIT_DLL_SSL_NOT_INITIALIZED + 59       */
/* SSL_ProfileGetCertificateFile     EXIT_DLL_SSL_NOT_INITIALIZED + 60       */
/* SSL_ProfileGetCAFile              EXIT_DLL_SSL_NOT_INITIALIZED + 61       */
/* SSL_ProfileSetKeyFile             EXIT_DLL_SSL_NOT_INITIALIZED + 62       */
/* SSL_ProfileSetCertificateFile     EXIT_DLL_SSL_NOT_INITIALIZED + 63       */
/* SSL_ProfileSetProtocol            EXIT_DLL_SSL_NOT_INITIALIZED + 64       */
/* SSL_ProfileGetProtocol            EXIT_DLL_SSL_NOT_INITIALIZED + 65       */
/* SSL_ProfileSetCipher              EXIT_DLL_SSL_NOT_INITIALIZED + 66       */
/* SSL_ProfileGetCipher              EXIT_DLL_SSL_NOT_INITIALIZED + 67       */
/* SSL_ProfileGetName                EXIT_DLL_SSL_NOT_INITIALIZED + 68       */
/* SSL_GetProfile                    EXIT_DLL_SSL_NOT_INITIALIZED + 69       */
/* SSL_GetProfileCount               EXIT_DLL_SSL_NOT_INITIALIZED + 70       */
/* SSL_ProfileGetLastIpServer        EXIT_DLL_SSL_NOT_INITIALIZED + 71       */
/* X509_Load                         EXIT_DLL_SSL_NOT_INITIALIZED + 72       */
/* X509_Unload                       EXIT_DLL_SSL_NOT_INITIALIZED + 73       */
/* X509_GetInfo                      EXIT_DLL_SSL_NOT_INITIALIZED + 74       */
/* X509_GetPeerCertificate           EXIT_DLL_SSL_NOT_INITIALIZED + 75       */
/* SSL_ProfileGetLastDate            EXIT_DLL_SSL_NOT_INITIALIZED + 76       */
/* SSL_GetSessionInfo                EXIT_DLL_SSL_NOT_INITIALIZED + 77       */
/* PKCS12_GetPrivateKeyv             EXIT_DLL_SSL_NOT_INITIALIZED + 78       */
/* PKCS12_GetCertificate             EXIT_DLL_SSL_NOT_INITIALIZED + 79       */
/* PKCS12_GetCA                      EXIT_DLL_SSL_NOT_INITIALIZED + 80       */
/* SSL_Server_Open                   EXIT_DLL_SSL_NOT_INITIALIZED + 81       */
/* SSL_Server_Accept                 EXIT_DLL_SSL_NOT_INITIALIZED + 82       */
/* SSL_Server_Close                  EXIT_DLL_SSL_NOT_INITIALIZED + 83       */
/* rsaSign                           EXIT_DLL_SSL_NOT_INITIALIZED + 84       */
/* SSL_ProfileGetKeyFile             EXIT_DLL_SSL_NOT_INITIALIZED + 85       */
/* rsaKeyCrypt                       EXIT_DLL_SSL_NOT_INITIALIZED + 86       */
/* SSL_Server_ClearCache             EXIT_DLL_SSL_NOT_INITIALIZED + 87       */
/*****************************************************************************/
#define EXIT_DLL_USM_NOT_INITIALIZED       0x1800
/*****************************************************************************/
/* WaitForUms                        EXIT_DLL_USM_NOT_INITIALIZED + 0        */
/* LoadFromUsb                       EXIT_DLL_USM_NOT_INITIALIZED + 1        */
/* LoadFromMmc                       EXIT_DLL_USM_NOT_INITIALIZED + 2        */
/* LoadFromUms                       EXIT_DLL_USM_NOT_INITIALIZED + 3        */
/*****************************************************************************/
#define EXIT_DLL_HWCNF_NOT_INITIALIZED       0x1900
/******************************************************************************/
/* HWCNF_Configure                    EXIT_DLL_HWCNF_NOT_INITIALIZED + 0      */
/* HWCNF_State                        EXIT_DLL_HWCNF_NOT_INITIALIZED + 1      */
/* HWCNF_TimeFunction                 EXIT_DLL_HWCNF_NOT_INITIALIZED + 2      */
/* HWCNF_DeepDischarging              EXIT_DLL_HWCNF_NOT_INITIALIZED + 3      */
/* HWCNF_GetBacklightDuration         EXIT_DLL_HWCNF_NOT_INITIALIZED + 4      */
/* HWCNF_SetBacklightDuration         EXIT_DLL_HWCNF_NOT_INITIALIZED + 5      */
/* HWCNF_GetStandbyDelay              EXIT_DLL_HWCNF_NOT_INITIALIZED + 6      */
/* HWCNF_SetStandbyDelay              EXIT_DLL_HWCNF_NOT_INITIALIZED + 7      */
/* HWCNF_Shortcut                     EXIT_DLL_HWCNF_NOT_INITIALIZED + 8      */
/* HWCNF_SetBacklightIntensity        EXIT_DLL_HWCNF_NOT_INITIALIZED + 9      */
/* HWCNF_GetBacklightIntensity        EXIT_DLL_HWCNF_NOT_INITIALIZED + 10     */
/* HWCNF_EthernetGetCurrentParameters EXIT_DLL_HWCNF_NOT_INITIALIZED + 11     */
/******************************************************************************/
#define EXIT_DLL_COLOR_NOT_INITIALIZED       0x2000
/******************************************************************************/
/* LoadBmp                             EXIT_DLL_COLOR_NOT_INITIALIZED + 0     */
/* PutBmp                              EXIT_DLL_COLOR_NOT_INITIALIZED + 1     */
/* BmpToScreen                         EXIT_DLL_COLOR_NOT_INITIALIZED + 12    */
/* StretchBmp                          EXIT_DLL_COLOR_NOT_INITIALIZED + 13    */
/* DrawBmp                             EXIT_DLL_COLOR_NOT_INITIALIZED + 14    */
/* _DrawBmp                            EXIT_DLL_COLOR_NOT_INITIALIZED + 15    */
/* DrawTextUnicode                     EXIT_DLL_COLOR_NOT_INITIALIZED + 16    */
/* _DrawTextUnicode                    EXIT_DLL_COLOR_NOT_INITIALIZED + 17    */
/* _DrawText8859                       EXIT_DLL_COLOR_NOT_INITIALIZED + 18    */
/* DrawText8859                        EXIT_DLL_COLOR_NOT_INITIALIZED + 19    */
/* BmpToMem                            EXIT_DLL_COLOR_NOT_INITIALIZED + 20    */
/* Scale                               EXIT_DLL_COLOR_NOT_INITIALIZED + 21    */
/* PaintFilm                           EXIT_DLL_COLOR_NOT_INITIALIZED + 22    */
/* _PutBmp                             EXIT_DLL_COLOR_NOT_INITIALIZED + 23    */
/* _Area                               EXIT_DLL_COLOR_NOT_INITIALIZED + 24    */
/* SaveScreenExtended                  EXIT_DLL_COLOR_NOT_INITIALIZED + 25    */
/* RestoreScreenExtended               EXIT_DLL_COLOR_NOT_INITIALIZED + 26    */
/* Ellipse                             EXIT_DLL_COLOR_NOT_INITIALIZED + 27    */
/* _Ellipse                            EXIT_DLL_COLOR_NOT_INITIALIZED + 28    */
/* Circle                              EXIT_DLL_COLOR_NOT_INITIALIZED + 29    */
/* _Rect                               EXIT_DLL_COLOR_NOT_INITIALIZED + 30    */
/* _Circle                             EXIT_DLL_COLOR_NOT_INITIALIZED + 31    */
/* Rect                                EXIT_DLL_COLOR_NOT_INITIALIZED + 32    */
/* Pixel                               EXIT_DLL_COLOR_NOT_INITIALIZED + 33    */
/* Line                                EXIT_DLL_COLOR_NOT_INITIALIZED + 34    */
/* _Line                               EXIT_DLL_COLOR_NOT_INITIALIZED + 35    */
/* _Pixel                              EXIT_DLL_COLOR_NOT_INITIALIZED + 36    */
/* _ClearScreen                        EXIT_DLL_COLOR_NOT_INITIALIZED + 37    */
/* Area                                EXIT_DLL_COLOR_NOT_INITIALIZED + 38    */
/* _SetScreenToScreen                  EXIT_DLL_COLOR_NOT_INITIALIZED + 39    */
/* SetScreenToScreen                   EXIT_DLL_COLOR_NOT_INITIALIZED + 40    */
/* GetPixelColor                       EXIT_DLL_COLOR_NOT_INITIALIZED + 41    */
/* SetScreenColor                      EXIT_DLL_COLOR_NOT_INITIALIZED + 42    */
/* SetRegionColor                      EXIT_DLL_COLOR_NOT_INITIALIZED + 43    */
/* GetRegionColor                      EXIT_DLL_COLOR_NOT_INITIALIZED + 44    */
/* ClearRegionColor                    EXIT_DLL_COLOR_NOT_INITIALIZED + 45    */
/* ScreenColor                         EXIT_DLL_COLOR_NOT_INITIALIZED + 46    */
/* DrawFont8859                        EXIT_DLL_COLOR_NOT_INITIALIZED + 47    */
/* DrawUnicode8859                     EXIT_DLL_COLOR_NOT_INITIALIZED + 48    */
/* _DrawFont8859                       EXIT_DLL_COLOR_NOT_INITIALIZED + 49    */
/* _DrawUnicode8859                    EXIT_DLL_COLOR_NOT_INITIALIZED + 50    */
/* GetColorScreenSize                  EXIT_DLL_COLOR_NOT_INITIALIZED + 53    */
/* GetUserArea                         EXIT_DLL_COLOR_NOT_INITIALIZED + 54    */
/* DrawFontUnicode                     EXIT_DLL_COLOR_NOT_INITIALIZED + 56    */
/* _DrawFontUnicode                    EXIT_DLL_COLOR_NOT_INITIALIZED + 57    */
/* GetColorScreenArea                  EXIT_DLL_COLOR_NOT_INITIALIZED + 58    */
/* ColorScreenSaver                    EXIT_DLL_COLOR_NOT_INITIALIZED + 59    */
/******************************************************************************/
#define EXIT_DLL_SCREEN_NOT_INITIALIZED       0x2100
/******************************************************************************/
/******************************************************************************/
/*! @} **/

#define EXIT_DLL_GRAPHIC_MANAGER_NOT_INITIALIZED       0x2200

#endif
#ifdef __cplusplus
}
#endif

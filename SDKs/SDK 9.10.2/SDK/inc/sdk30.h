#if defined(__cplusplus) || defined(_INTERNAL_REDEF_)
#include "cpp_e.h"                   // SYSTEME
#endif

#include <string.h>
#include <stdarg.h> 

#ifndef __FRAMEWORK_TELIUM_2__
#define __FRAMEWORK_TELIUM_2__
#endif
#include "macro_deprecated.h"           // SYSTEME
#include "loaderapi.h"                  // SYSTEME
#include "basearm.h"                    // SYSTEME
#include "xecarm.h"                     // SYSTEME
#include "oem_public.h"                 // SYSTEME
#include "oem_public_deprecated.h"      // SYSTEME
#include "fs.h"                         // SYSTEME
#include "config.h"                     // SYSTEME
#include "diag_def.h"                   // SYSTEME
#include "defdiag_TSys.h"               // SYSTEME
#include "oem_display_deprecated.h"     // SYSTEME
#include "oem_hid.h"                    // SYSTEME
#include "oem_com.h"                    // SYSTEME
#include "oem_sys.h"                    // SYSTEME
#include "oem_sysfioctl_def.h"          // SYSTEME
#include "oem_sysfioctl.h"              // SYSTEME
#include "oem_sysfioctl_deprecated.h"   // SYSTEME
#include "oem_public.h"                 // SYSTEME
#include "oem_ums.h"                    // SYSTEME
#include "callhost.h"                   // SYSTEME
#include "flashmanager.h"               // SYSTEME
#include "oem_power_def.h"              // SYSTEME
#include "oem_power.h"                  // SYSTEME
#include "oem_power_deprecated.h"       // SYSTEME
#include "oem_mmc_deprecated.h"         // SYSTEME
#include "oem_dgprs.h"                  // SYSTEME
#include "oem_dgprs_def.h"              // SYSTEME
#include "oem_dgprs.h"                  // SYSTEME
#include "oem_dgprs_deprecated.h"       // SYSTEME
#include "oem_modem.h"                  // SYSTEME
#include "oem_vfs.h"                    // SYSTEME
#define NG_CADDR_TYPE
#include "oem_leds_deprecated.h"        // SYSTEME
#include "oem_buzzer_peri_deprecated.h" // SYSTEME
#include "oem_print.h"                  // SYSTEME
#include "oem_usb.h"                    // SYSTEME
#include "oem_backlight_deprecated.h"   // SYSTEME
#include "oem_RetroEclairageC30.h"      // SYSTEME
#include "oem_ispm.h"                   // SYSTEME
#include "dbluetooth.h"                 // SYSTEME
#include "crypto_def.h"                 // SYSTEME
#include "inter_uc_sp_canal_const.h"    // SYSTEME
#include "ssl_profile.h"                // COMPONENT SSL
#ifndef EMVDCTAG
#include "_emvdctag_.h"                 // COMPONENT EMV
#endif

#include "clib.h"                       // MANAGER
#include "gprs_lib.h"                   // MANAGER
#include "tmoem.h"                      // MANAGER
#include "lib_iapp.h"                   // COMPONENT IAPP
#include "descript.h"                   // SYSTEME
#include "schmgmt_deprecated.h"         // SYSTEME
#include "submitpin.h"                  // COMPONENT PINLIB
#ifndef _EXPORT_
#include "ctype.h"                   // MANAGER
#endif
#include "nttypes.h"                 // MANAGER
#include "iso2.h"                    // MANAGER
#include "MSGlib.h"                  // MANANER
#include "MSGlib_deprecated.h"       // MANANER
#include "appel.h"                   // MANAGER
#include "appel_deprecated.h"        // MANAGER
#include "etat.h"                    // MANAGER
#include "config_TManager.h"         // MANAGER
#include "config_TManager_deprecated.h" // MANAGER
#include "defdiag_TManager.h"        // MANAGER
#include "typ.h"                     // MANAGER
#include "csymbol.h"                 // MANAGER
#include "fontlib.h"                 // MANAGER
#include "libgr.h"                   // MANAGER
#include "police.h"                  // MANAGER
//#include "servcall.h"
#include "saisie.h"                  // MANAGER
#include "saisie_deprecated.h"       // MANAGER
#include "saisie_ppad.h"             // MANAGER
#include "oemfrance.h"               // MANAGER
#include "modem.h"                   // MANAGER
#include "fct_gen.h"                 // MANAGER
#include "ccext.h"                   // MANAGER
#include "socle.h"                   // MANAGER
#include "services.h"                // MANAGER
#include "services_deprecated.h"     // MANAGER
#include "status.h"                  // MANAGER
#include "param.h"                   // MANAGER
#include "param_deprecated.h"        // MANAGER
#ifndef EMVDC
#include "_emvdc_.h"                 // COMPONENT EMV
#endif
#include "emvseq.h"                  // MANAGER
#include "os.h"                      // MANAGER
#include "pfpsai.h"                  // MANAGER
#include "pinpad.h"                  // MANAGER                 
#include "util_sq.h"                 // MANAGER
#include "psc.h"                     // MANAGER
#include "message.h"                 // MANAGER
#include "client_ip.h"               // MANAGER
#ifndef ManagerMessages_H
#define ManagerMessages_H
#include "ManagerMessages.h"         // MANAGER
#endif
#include "msgmgr.h"                  // MANAGER
#include "caisse.h"                  // MANAGER
#include "protocole.h"               // MANAGER
#include "hterm.h"                   // MANAGER
#include "hterm_deprecated.h"        // MANAGER

#include "P30.h"                     // MANAGER
#include "trace.h"                   // MANAGER
// Public for DLL COLOR
#include "DisplayAmount.h"           // MANAGER
#include "bitmap.h"                  // MANAGER
#include "wcharLib.h"                // MANAGER
// Public for DLL CRYPTO
#include "Telium_crypto.h"           // MANAGER
// Public for DLL HWCNF
#include "dll_hwcnf.h"               // MANAGER
#include "dll_hwcnf_deprecated.h"    // MANAGER
// Public for GPRS
#include "sms.h"                     // MANAGER
// Public for TIMER
#include "timer.h"                   // MANAGER
// Public for DLL UMS
#include "ums.h"                     // MANAGER
// Public for SHORTCUT
#include "Short_cut.h"               // MANAGER
// Public for LANGAGE
#include "langue.h"                  // MANAGER
#include "deprecated.h"              // MANAGER

#include "HomeScreen.h"              //MANAGER

#if defined(__cplusplus) || defined(_INTERNAL_REDEF_)
  #include "cpp_d.h"                 // SYSTEME
#endif

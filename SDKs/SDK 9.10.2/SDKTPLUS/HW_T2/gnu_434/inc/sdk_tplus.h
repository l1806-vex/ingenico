#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdarg.h> 

#ifndef __FRAMEWORK_TELIUM_PLUS__
#define __FRAMEWORK_TELIUM_PLUS__
#endif

#include "loaderapi_def.h"                  // SYSTEME
#include "basearm_def.h"                    // SYSTEME
#include "xecarm_def.h"                     // SYSTEME
#include "oem_public_def.h"                 // SYSTEME
#include "fs_def.h"                         // SYSTEME
#include "config_def.h"                     // SYSTEME
#include "diag_def.h"                       // SYSTEME
#include "defdiag_TSys_def.h"               // SYSTEME
#include "oem_hid_def.h"                    // SYSTEME
#include "oem_com_def.h"                    // SYSTEME
#include "oem_sys_def.h"                    // SYSTEME
#include "oem_sysfioctl_def.h"              // SYSTEME
#include "oem_ums_def.h"                    // SYSTEME
#include "callhost_def.h"                   // SYSTEME
#include "flashmanager_def.h"               // SYSTEME
#include "oem_power_def.h"                  // SYSTEME
#include "oem_dgprs_def.h"                  // SYSTEME
#include "oem_modem_def.h"                  // SYSTEME
#include "oem_vfs_def.h"                    // SYSTEME
#define NG_CADDR_TYPE
#include "oem_print_def.h"                  // SYSTEME
#include "oem_usb_def.h"                    // SYSTEME
#include "oem_RetroEclairageC30_def.h"      // SYSTEME
#include "oem_ispm_def.h"                   // SYSTEME
#include "dbluetooth_def.h"                 // SYSTEME
#include "crypto_def.h"                     // SYSTEME
#include "inter_uc_sp_canal_const_def.h"    // SYSTEME
#include "ssl_profile.h"                // COMPONENT SSL

#include "clib.h"                       // MANAGER
#include "gprs_lib.h"                   // MANAGER
#include "tmoem.h"                      // MANAGER
#include "oem_tplus.h"                  // MANAGER
#include "descript_def.h"                   // SYSTEME
#ifndef _EXPORT_
#include "ctype.h"                   // MANAGER
#endif
#include "nttypes.h"                 // MANAGER
#include "iso2.h"                    // MANAGER
#include "MSGlib.h"                  // MANANER
#include "appel.h"                   // MANAGER
#include "etat.h"                    // MANAGER
#include "config_TManager.h"         // MANAGER
#include "defdiag_TManager.h"        // MANAGER
#include "typ.h"                     // MANAGER
#include "csymbol.h"                 // MANAGER
#include "fontlib.h"                 // MANAGER
#include "libgr.h"                   // MANAGER
#include "police.h"                  // MANAGER
//#include "servcall.h"
#include "saisie.h"                  // MANAGER
#include "saisie_ppad.h"             // MANAGER
#include "oemfrance.h"               // MANAGER
#include "modem.h"                   // MANAGER
#include "fct_gen.h"                 // MANAGER
#include "ccext.h"                   // MANAGER
#include "socle.h"                   // MANAGER
#include "services.h"                // MANAGER
#include "status.h"                  // MANAGER
#include "param.h"                   // MANAGER
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

#include "HomeScreen.h"              //MANAGER

#include "OSL_Layer.h"              //Core platform

#ifdef __cplusplus
}
#endif

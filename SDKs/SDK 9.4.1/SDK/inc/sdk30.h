#if defined(__cplusplus) || defined(_INTERNAL_REDEF_)
 #include "cpp_e.h"
#endif

#ifndef _GSIM_
// includes supprimes pour l'analyse GSIM
#include <string.h>
#endif

// Definitions manquantes pour GSIM
#ifdef _GSIM_
typedef unsigned int size_t;
#endif

#include "ta_appli.h"
#include "diagnostic.h"
#include "reloc.h"
#include "typ.h"
#include "csymbol.h"
#include "oem_display.h"
#include "libgr.h"
#include "police.h"
#include "fs.h"
//#include "servcall.h"
#include "entry.h"
#include "saisie_ppad.h"
#include "oemfrance.h"
#include "modem.h"
#include "fct_gen.h"
#include "ccext.h"
#include "socle.h"
#include "services.h"
#include "status.h"
#include "param.h"
#ifndef EMVDC
#include "_emvdc_.h"
#endif
#include "emvseq.h"
#include "os.h"
#include "pfpsai.h"
#include "pinpad.h"
#include "util_sq.h"
#include "lib_iapp.h"
#include "oem_hid.h"
#include "oem_com.h"
#include "oem_sysfioctl.h"
#include "oem_public.h"
#include "callhost.h"
#include "psc.h"
#include "message.h"
#ifndef ManagerMessages_H
#define ManagerMessages_H
#include "ManagerMessages.h"
#endif
#include "msgmgr.h"
/* suppression des majuscules pour analyse GSIM */
#include "flashmanager.h"
#include "caisse.h"
#include "protocole.h"
#include "schmgmt.h"
#include "submitpin.h"
#include "oem_power.h"
#include "oem_vfs.h"
#include "oem_mmc.h"
#include "dbluetooth.h"
#include "hterm.h"

/* ajout de majuscule pour analyse GSIM */
#include "P30.h"
#if defined(__cplusplus) || defined(_INTERNAL_REDEF_)
  #include "cpp_d.h"
#endif

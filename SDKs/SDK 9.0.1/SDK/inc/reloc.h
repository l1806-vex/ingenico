#ifndef RELOC_H
#define RELOC_H

//! \brief This file is used to manage compatibility.
//! \brief between EFT10/20 and Telium Generic
//! \brief Used to manage relocatibility of CODE And DATA

//! \brief Define the RELOC table structure.
typedef struct
{
  char *mess;										//!< message
} S_TAB_RELOC;


//! \brief Define a pointer on a function to relocate.
typedef void * (*PFONCRELOC)(void);
extern ADRESSE pcode;
#ifdef _EFT20_
//! \brief for EFT10/20
extern  void *ACCES  (void *);
extern  int ACCES_FCT (PFONCRELOC ,...);
extern  int ACCES_FCT0 (PFONCRELOC ,...);
extern  int ACCES_FCT1 (PFONCRELOC ,...);
extern  int ACCES_FCT2 (PFONCRELOC ,...);
extern  int ACCES_FCT3 (PFONCRELOC ,...);
extern  int ACCES_FCT4 (PFONCRELOC ,...);
extern  int ACCES_FCT5 (PFONCRELOC ,...);
extern  int ACCES_FCT6 (PFONCRELOC ,...);
extern  int ACCES_FCT7 (PFONCRELOC ,...);

#define ACCES_FCT0    ACCES_FCT
#define ACCES_FCT1    ACCES_FCT
#define ACCES_FCT2    ACCES_FCT
#define ACCES_FCT3    ACCES_FCT
#define ACCES_FCT4    ACCES_FCT
#define ACCES_FCT5    ACCES_FCT
#define ACCES_FCT6    ACCES_FCT
#define ACCES_FCT7    ACCES_FCT
#else
//! \brief for Telium Generic

//! \brief Do nothing, only for compatibility
#define ACCES_APPLI(a, b) (a)
//! \brief Do nothing, only for compatibility
#define ACCES(a)          (char*)(a)
//! \brief Do nothing, only for compatibility
#define ACCES_DATA(a)     (a)
//! \brief Do nothing, only for compatibility
#define ACCES_FCT0(a)                       (a)()
//! \brief Do nothing, only for compatibility
#define ACCES_FCT1(a, b)                    (a)((b))
//! \brief Do nothing, only for compatibility
#define ACCES_FCT2(a, b, c)                 (a)((b), (c))
//! \brief Do nothing, only for compatibility
#define ACCES_FCT3(a, b, c, d)              (a)((b), (c), (d))
//! \brief Do nothing, only for compatibility
#define ACCES_FCT4(a, b, c, d, e)           (a)((b), (c), (d), (e))
//! \brief Do nothing, only for compatibility
#define ACCES_FCT5(a, b, c, d, e, f)        (a)((b), (c), (d), (e), (f))
//! \brief Do nothing, only for compatibility
#define ACCES_FCT6(a, b, c, d, e, f, g)     (a)((b), (c), (d), (e), (f), (g))
//! \brief Do nothing, only for compatibility
#define ACCES_FCT7(a, b, c, d, e, f, g, h)  (a)((b), (c), (d), (e), (f), (g), (h))

#endif
#endif

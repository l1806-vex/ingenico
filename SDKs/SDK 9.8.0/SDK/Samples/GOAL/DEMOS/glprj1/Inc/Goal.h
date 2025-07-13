#ifndef TDEFINE
#define TDEFINE extern
#undef  INIT_VALUE
#else
#define INIT_VALUE
#endif


TDEFINE void goalSInitContext(CGUI_CONTEXT_STRUCT *goalManagerContext, bool bFullScreenn);
TDEFINE void goalSReleaseContext(void);




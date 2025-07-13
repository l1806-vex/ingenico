/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

int HelperDisplayMenu(const char* szTitle, int nDefaultChoice, int nItems, const char* Items[]);
int HelperDisplayChoices(const char* szTitle, int nDefaultChoice, int nItems, const char* Items[]);
int HelperNumericInput(const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, const char* szDefault, char* szInput);
int HelperAlphanumericInput(const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, const char* szDefault, const char* szAllowedChars, char* szInput);

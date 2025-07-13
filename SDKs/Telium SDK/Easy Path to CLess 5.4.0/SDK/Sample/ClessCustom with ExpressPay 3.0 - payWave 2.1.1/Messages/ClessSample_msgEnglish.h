// #LANGUAGE en
// #FONFILE /SYSTEM/ISO1.SGN
// #MSGCODING ISO8859
// #FILETYPE 1
// #APPLITYPE 0122

/* ------------------------------------------------------------------------ */
/* Standards messages                                                       */
/* ------------------------------------------------------------------------ */
#message 0 STD_MESS_AVAILABLE                                   "AVAILABLE:"
#message 1 STD_MESS_REMOVE_CARD                                 "REMOVE CARD"
#message 2 STD_MESS_USER                                        "USER"
#message 3 STD_MESS_KEYBOARD                                    "KEYBOARD"
#message 4 STD_MESS_STOPPED                                     "STOPPED:?"
#message 5 STD_MESS_ERROR                                       "ERROR"
#message 6 STD_MESS_ERROR_STATUS                                "ERROR STATUS"
#message 7 STD_MESS_OFFLINE_APPROVED                            "OFFLINE APPROVED"
#message 8 STD_MESS_OFFLINE_DECLINED                            "DECLINED"
#message 9 STD_MESS_ONLINE_REQUEST                              "ONLINE REQUEST"
#message 10 STD_MESS_ONLINE_APPROVED                            "ONLINE APPROVED"
#message 11 STD_MESS_ONLINE_DECLINED                            "ONLINE DECLINED"
#message 12 STD_MESS_APPROVED                                   "APPROVED"
#message 13 STD_MESS_PIN_ERROR                                  "PIN ENTRY ERROR"
#message 14 STD_MESS_ENTER_AMOUNT                               "ENTER AMOUNT"
#message 15 STD_MESS_SIGNATURE_CHECK_L1                         "SIGNATURE"
#message 16 STD_MESS_SIGNATURE_CHECK_L2                         "CHECKING"
#message 17 STD_MESS_PRINT_RECEIPT                              "PRINT RECEIPT ?"
#message 18 STD_MESS_PRINT_TRANSACTION_LOG                      "PRINT LOG ?"
#message 19 STD_MESS_SIGNATURE_OK                               "SIGNATURE OK ?"
#message 20 STD_MESS_SIGNATURE_CORRECT                          "SIGNATURE OK"
#message 21 STD_MESS_SIGNATURE_INCORRECT                        "BAD SIGNATURE"
#message 22 STD_MESS_UNABLE_ON_LINE                             "ONLINE UNABLE"
#message 23 STD_MESS_ONLINE_PIN_ERROR                           "ONLINE PIN\n  FAILED"
#message 24 STD_MESS_CARD_BLOCKED                               "CARD BLOCKED"
#message 25 STD_MESS_APPLICATION_BLOCKED                        "APPLI. BLOCKED"
#message 26 STD_MESS_AMOUNT                                     "AMOUNT:"
#message 27 STD_MESS_DEBIT                                      "DEBIT"
#message 28 STD_MESS_CASH                                       "CASH"
#message 29 STD_MESS_REFUND                                     "REFUND"
#message 30 STD_MESS_TRANSAC_TYPE                               "TRANSAC TYPE"
#message 31 STD_MESS_APPROVED_TICKET                            "APPROVED"
#message 32 STD_MESS_DECLINED_TICKET                            "DECLINED"
#message 33 STD_MESS_BATCH_ERROR                                "BATCH ERROR"
#message 34 STD_MESS_CHOICE_YES_NO                              "YES              NO"
#message 35 STD_MESS_CHOICE_YES                                 "YES"
#message 36 STD_MESS_CHOICE_NO                                  "NO"
#message 37 STD_MESS_VALIDATE                                   "VALIDATE"
#message 38 STD_MESS_CANCEL                                     "CANCEL"

/* ------------------------------------------------------------------------ */
/* Pin input message                                                        */
/* ------------------------------------------------------------------------ */
#message 39 STD_MESS_ENTER_PIN                                  "ENTER YOUR PIN"
#message 40 STD_MESS_TRY_AGAIN                                  "TRY AGAIN"
#message 41 STD_MESS_SAFE                                       "SAFE FROM PRYING EYES"

/* ------------------------------------------------------------------------ */
/* Default messages                                                         */
/* ------------------------------------------------------------------------ */
#message 42 STD_MESS_REQUESTED_DATA                             "REQUESTED DATA"
#message 43 STD_MESS_DATA_RECORD                                "DATA RECORD"
#message 44 STD_MESS_DATABASE_DUMP                              "DATABASE DUMP"
#message 45 STD_MESS_PRESENT_CARD                               "PRESENT CARD"

/* ------------------------------------------------------------------------ */
/* MENU messages                                                            */
/* ------------------------------------------------------------------------ */
#message 46 STD_MESS_MENU_MAIN_DEBIT                            "DEBIT"
#message 47 STD_MESS_MENU_MAIN_CASH                             "CASH"
#message 48 STD_MESS_MENU_MAIN_REFUND                           "REFUND"
#message 49 STD_MESS_MENU_MAIN_CASHBACK                         "CASHBACK"
#message 50 STD_MESS_MENU_MAIN_TEST                             "TEST"
#message 51 STD_MESS_MENU_MAIN_PARAMETERS                       "PARAMETERS"
#message 52 STD_MESS_MENU_MAIN_MERCHANT                         "MERCHANT"
#message 53 STD_MESS_MENU_MAIN_BATCH                            "BATCH"
#message 54 STD_MESS_MENU_TEST_DUMP_TR                          "DUMP DATA TR"
#message 55 STD_MESS_MENU_TEST_DUMP_DB                          "DUMP DATA DB"
#message 56 STD_MESS_MENU_TEST_LOOP                             "TRANSAC LOOP"
#message 57 STD_MESS_MENU_IMPLICIT_SEL_LOOP                     "IMPLICIT SEL. LOOP"
#message 58 STD_MESS_MENU_TEST_CHANGE_OUTPUT                    "CHANGE OUTPUT"
#message 59 STD_MESS_MENU_TEST_TRACES                           "TRACES"
#message 60 STD_MESS_MENU_TEST_VISA_EUROPE                      "VISA EUROPE"
#message 61 STD_MESS_MENU_TEST_INPUT_TRANSACTION_TYPE           "INPUT TR. TYPE"
#message 62 STD_MESS_MENU_OUTPUT_NONE                           "NONE"
#message 63 STD_MESS_MENU_OUTPUT_PRINTER                        "PRINTER"
#message 64 STD_MESS_MENU_OUTPUT_COM0                           "COM0"
#message 65 STD_MESS_MENU_OUTPUT_USB                            "USB"
#message 66 STD_MESS_MENU_PARAMS_DUMP                           "DUMP"
#message 67 STD_MESS_MENU_PARAMS_DEFAULT                        "DEFAULT"
#message 68 STD_MESS_MENU_PARAMS_ERASE_ALL                      "ERASE ALL"
#message 69 STD_MESS_MENU_PARAMS_DUMP_ID                        "IDENTIFIER"
#message 70 STD_MESS_MENU_PARAMS_DUMP_AIDS                      "AIDS"
#message 71 STD_MESS_MENU_PARAMS_DUMP_CA                        "CA KEYS"
#message 72 STD_MESS_MENU_PARAMS_DUMP_GLOBALS                   "GLOBAL PARAMS"
#message 73 STD_MESS_MENU_PARAMS_DUMP_KERNEL_SPECIFIC           "KERNEL SPECIFIC"
#message 74 STD_MESS_MENU_PARAMS_DUMP_ALL                       "ALL"
#message 75 STD_MESS_MENU_PARAMS_MERCHANT_FORCE_ONLINE          "FORCE ONLINE"
#message 76 STD_MESS_MENU_PARAMS_MERCHANT_RESET_TSC             "RESET TSC"
#message 77 STD_MESS_MENU_PARAMS_BATCH_TOTALS                   "TOTALS"
#message 78 STD_MESS_MENU_PARAMS_BATCH_PRINT_LOG                "PRINT LOG"
#message 79 STD_MESS_MENU_PARAMS_BATCH_PRINT_DETAILED_LOG       "PRINT DETAILED LOG"

#message 80 STD_MESS_MENU_PARAMS_BATCH_CLEAR                    "CLEAR"
#message 81 STD_MESS_MENU_PARAMS_BATCH_LAST_TR                  "LAST TRANSACTION"

/* ------------------------------------------------------------------------ */
/* Default messages                                                         */
/* ------------------------------------------------------------------------ */
#message 90 STD_MESS_ENABLE                                     "ENABLED"
#message 91 STD_MESS_DISABLE                                    "DISABLED"
#message 92 STD_MESS_IN_PROGRESS                                "IN PROGRESS"
#message 93 STD_MESS_COMPLETE                                   "COMPLETED"
#message 94 STD_MESS_UPDATING_PARAMS                            "PARAMS UPDATE"
#message 95 STD_MESS_ERASING_PARAMS                             "PARAMS ERASE"
#message 96 STD_MESS_INVALID_CERTIFICATE                        "INVALID CERTIFICATE"
#message 97 STD_MESS_PIN_CANCEL                                 "INPUT PIN CANCELED"
#message 98 STD_MESS_REPRESENT_CARD                             "REPRESENT CARD"
#message 99 STD_MESS_PLEASE_REMOVE                              "PLEASE REMOVE"
#message 100 STD_MESS_CARD_DEVICE                               "CARD OR DEVICE"
#message 101 STD_MESS_INSERT_CARD                               "INSERT CARD"
#message 102 STD_MESS_AUTHORISING                               "AUTHORISING"
#message 103 STD_MESS_PLEASE_WAIT                               "PLEASE WAIT"
#message 104 STD_MESS_CARD_NOT_SUPPORTED                        "NOT SUPPORTED"
#message 105 STD_MESS_FAILED                                    "FAILED"
#message 106 STD_MESS_DLL_TPASS                                 "TPASS DLL"
#message 107 STD_MESS_NOT_LOADED                                "MISSING"
#message 108 STD_MESS_PHONE_INSTRUCTIONS_L1                     "SEE PHONE FOR"
#message 109 STD_MESS_PHONE_INSTRUCTIONS_L2                     "INSTRUCTIONS"


/* ------------------------------------------------------------------------ */
/* Interac Specific messages (Dual Language)                                */
/* ------------------------------------------------------------------------ */
#message 150 INTERAC_MESS_SELECT_ONE_CARD_L1                    "PRESENT/PRESENTER"
#message 151 INTERAC_MESS_SELECT_ONE_CARD_L2                    "1 CCARD/CARTE"
#message 152 INTERAC_MESS_NOT_SUPPORTED_L1                      "NOT SUPPORTED"
#message 153 INTERAC_MESS_NOT_SUPPORTED_L2                      "CARTE NON GEREE"
#message 154 INTERAC_MESS_INSERT_CARD_L1                        "INSERT/SWIPE CARD"
#message 155 INTERAC_MESS_INSERT_CARD_L2                        "INSERER/SWIPE CARTE"
#message 156 INTERAC_MESS_PRESENT_CARD                          "PRESENT CARD/CARTE"
#message 157 INTERAC_MESS_REFUND                                "CREDIT"
#message 158 INTERAC_MESS_DEBIT                                 "DEBIT"
#message 159 INTERAC_MESS_NO_CARD                               "NO CARD/CARTE"

/* ------------------------------------------------------------------------ */
/* ExpressPay Specific messages                                             */
/* ------------------------------------------------------------------------ */
#message 170 EXPRESSPAY_MESS_PROCESSING                         "PROCESSING"
#message 171 EXPRESSPAY_MESS_PLEASE_WAIT                        "PLEASE WAIT"

/* ------------------------------------------------------------------------ */
/* VisaWave Specific messages                                               */
/* ------------------------------------------------------------------------ */
#message 200 VISAWAVE_MESS_PROCESSING                            "PROCESSING..."
#message 201 VISAWAVE_MESS_REMOVE_CARD                           "REMOVE CARD"
#message 202 VISAWAVE_MESS_PLEASE_WAIT                           "PLEASE WAIT"
#message 203 VISAWAVE_MESS_THANK_YOU                             "THANK YOU"
#message 204 VISAWAVE_MESS_TRANSACTION                           "TRANSACTION"
#message 205 VISAWAVE_MESS_TRANSACTION_COMPLETED                 "COMPLETED"
#message 206 VISAWAVE_MESS_SIGNATURE_CHECK_L1                    "PLEASE SIGN ON"
#message 207 VISAWAVE_MESS_SIGNATURE_CHECK_L2                    "THE RECEIPT"
#message 208 VISAWAVE_MESS_ENTER_PIN                             "PLEASE ENTER PIN"
#message 209 VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L1            "OFFLINE"
#message 210 VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L2           "AVAILABLE FUNDS"
#message 211 VISAWAVE_MESS_TRANSACTION_DECLINED                 "DECLINED"
#message 212 VISAWAVE_MESS_TRANSACTION_TERMINATED               "TERMINATED"
#message 213 VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1               "PLEASE USE OTHER"
#message 214 VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2               "VISA CARD"
#message 215 VISAWAVE_MESS_INSERT_OR_SWIPE                      "INSERT OR SWIPE"
#message 216 VISAWAVE_MESS_PIN_REQUIRED                         "PIN ENTRY REQUIRED"
#message 217 VISAWAVE_MESS_SIGNATURE_REQUIRED                   "SIGNATURE REQUIRED"
#message 218 VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED            "NOT COMPLETED"
#message 219 VISAWAVE_MESS_NO_CARD                              "NO CARD"
#message 220 VISAWAVE_MESS_TRY_AGAIN                            "PLEASE TRY AGAIN"
#message 221 VISAWAVE_MESS_SELECT_ONE_CARD_L1                   "PLEASE SELECT"
#message 222 VISAWAVE_MESS_SELECT_ONE_CARD_L2                   "1 CARD"

/* ------------------------------------------------------------------------ */
/* PayPass Specific messages                                             */
/* ------------------------------------------------------------------------ */
#message 250 PAYPASS_MESS_NOT_AUTHORISED				                "NOT AUTHORISED"
#message 251 PAYPASS_MESS_ENTER_PIN						                  "ENETER PIN"
#message 252 PAYPASS_MESS_ENTER_PIN_L2					                "ON TERMINAL"
#message 253 PAYPASS_MESS_REMOVE						                    "REMOVE"
#message 254 PAYPASS_MESS_REMOVE_L2						                  "CARD / DEVICE"

#message 255 STD_MESS_COLLISION_LINE_1                          "PLEASE PRESENT"
#message 256 STD_MESS_COLLISION_LINE_2                          "ONLY ONE CARD"
#message 257 STD_MESS_RECEIPT_TXN_WITH_MOBILE                   "TRANSACTION USING MOBILE"
#message 258 STD_MESS_RECEIPT_TXN_WITH_CARD                     "TRANSACTION USING CARD"
#message 259 STD_MESS_RECEIPT_PIN_VERIFIED                      "CARDHOLDER PIN VERIFIED"
#message 260 STD_MESS_RECEIPT_NO_CARDHOLDER_VERIFICATION        "NO CARDHOLDER VERIFICATION"


// #LANGUAGE en
// #FONFILE /SYSTEM/ISO1.SGN
// #MSGCODING ISO8859
// #FILETYPE 1
// #APPLITYPE 0122

/* ------------------------------------------------------------------------ */
/* Standards messages                                                       */
/* ------------------------------------------------------------------------ */
#message 0 STD_MESS_AVAILABLE							        "AVAILABLE:"
#message 1 STD_MESS_REMOVE_CARD							        "REMOVE CARD"
#message 2 STD_MESS_USER                                        "USER"
#message 3 STD_MESS_KEYBOARD                                    "KEYBOARD"
#message 4 STD_MESS_STOPPED                                     "STOPPED:?"
#message 5 STD_MESS_ERROR                                       "ERROR"
#message 6 STD_MESS_ERROR_STATUS                                "ERROR STATUS"
#message 7 STD_MESS_OFFLINE_APPROVED                            "APPROVED"
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
#message 79 STD_MESS_MENU_PARAMS_BATCH_CLEAR                    "CLEAR"
#message 80 STD_MESS_MENU_PARAMS_BATCH_LAST_TR                  "LAST TRANSACTION"
#message 81 STD_MESS_ENABLE                                     "ENABLED"
#message 82 STD_MESS_DISABLE                                    "DISABLED"
#message 83 STD_MESS_IN_PROGRESS                                "IN PROGRESS"
#message 84 STD_MESS_COMPLETE                                   "COMPLETED"
#message 85 STD_MESS_UPDATING_PARAMS                            "PARAMS UPDATE"
#message 86 STD_MESS_ERASING_PARAMS                             "PARAMS ERASE"
#message 87 STD_MESS_INVALID_CERTIFICATE                        "INVALID CERTIFICATE"
#message 88 STD_MESS_PIN_CANCEL                                 "INPUT PIN CANCELED"
#message 89 STD_MESS_REPRESENT_CARD                             "REPRESENT CARD"
#message 90 STD_MESS_PLEASE_REMOVE                              "PLEASE REMOVE"
#message 91 STD_MESS_CARD_DEVICE                                "CARD OR DEVICE"
#message 92 STD_MESS_SALE                                       "SALE"
#message 93 STD_MESS_INSERT_OR_TRY_ANOTHER_CARD_L1              "INSERT, SWIPE, OR"
#message 94 STD_MESS_INSERT_OR_TRY_ANOTHER_CARD_L2              "TRY ANOTHER CARD"
#message 95 STD_MESS_AUTHORISING                                "AUTHORISING"
#message 96 STD_MESS_PLEASE_WAIT                                "PLEASE WAIT"
#message 97 STD_MESS_MENU_TEST_DUMP_APDU_DE                     "DUMP APDU DE"
#message 98 STD_MESS_MENU_TEST_HALKBANK_DE	                    "HALKBANK"

/* ------------------------------------------------------------------------ */
/* VisaWave Specific messages                                               */
/* ------------------------------------------------------------------------ */
#message 99 VISAWAVE_MESS_PROCESSING                            "PROCESSING..."
#message 100 VISAWAVE_MESS_REMOVE_CARD                          "REMOVE CARD"
#message 101 VISAWAVE_MESS_THANK_YOU                            "THANK YOU"
#message 102 VISAWAVE_MESS_TRANSACTION                          "TRANSACTION"
#message 103 VISAWAVE_MESS_TRANSACTION_COMPLETED                "COMPLETED"
#message 104 VISAWAVE_MESS_SIGNATURE_CHECK_L1                   "PLEASE SIGN ON"
#message 105 VISAWAVE_MESS_SIGNATURE_CHECK_L2                   "THE RECEIPT"
#message 106 VISAWAVE_MESS_ENTER_PIN                            "PLEASE ENTER PIN"
#message 107 VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L1	        "OFFLINE"
#message 108 VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L2	        "AVAILABLE FUNDS"
#message 109 VISAWAVE_MESS_TRANSACTION_DECLINED                 "DECLINED"
#message 110 VISAWAVE_MESS_TRANSACTION_TERMINATED               "TERMINATED"
#message 111 VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1               "PLEASE USE OTHER"
#message 112 VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2               "VISA CARD"
#message 113 VISAWAVE_MESS_INSERT_OR_SWIPE                      "INSERT OR SWIPE"
#message 114 VISAWAVE_MESS_PIN_REQUIRED					        "PIN ENTRY REQUIRED"
#message 115 VISAWAVE_MESS_SIGNATURE_REQUIRED			        "SIGNATURE REQUIRED"
#message 116 VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED	        "NOT COMPLETED"
#message 117 VISAWAVE_MESS_NO_CARD                  	        "NO CARD"
#message 118 VISAWAVE_MESS_TRY_AGAIN                  	        "PLEASE TRY AGAIN"
#message 119 VISAWAVE_MESS_SELECT_ONE_CARD_L1                   "PLEASE SELECT"
#message 120 VISAWAVE_MESS_SELECT_ONE_CARD_L2                   "1 CARD"
#message 121 VISAWAVE_MESS_PHONE_INSTRUCTIONS_L1                "SEE PHONE FOR"
#message 122 VISAWAVE_MESS_PHONE_INSTRUCTIONS_L2                "INSTRUCTIONS"

/* ------------------------------------------------------------------------ */
/* Interac Specific messages (Dual Language)                                */
/* ------------------------------------------------------------------------ */
#message 123 INTERAC_MESS_SELECT_ONE_CARD_L1                    "PRESENT/PRESENTER"
#message 124 INTERAC_MESS_SELECT_ONE_CARD_L2                    "1 CCARD/CARTE"
#message 125 INTERAC_MESS_NOT_SUPPORTED_L1                      "NOT SUPPORTED"
#message 126 INTERAC_MESS_NOT_SUPPORTED_L2                      "CARTE NON GEREE"
#message 127 INTERAC_MESS_INSERT_CARD_L1                        "INSERT/SWIPE CARD"
#message 128 INTERAC_MESS_INSERT_CARD_L2                        "INSERER/SWIPE CARTE"
#message 129 INTERAC_MESS_PRESENT_CARD                          "PRESENT CARD/CARTE"
#message 130 INTERAC_MESS_REFUND                                "CREDIT"
#message 131 INTERAC_MESS_DEBIT                                 "DEBIT"
#message 132 INTERAC_MESS_NO_CARD                  	            "NO CARD/CARTE"

/* ------------------------------------------------------------------------ */
/* ExpressPay Specific messages                                             */
/* ------------------------------------------------------------------------ */
#message 133 EXPRESSPAY_MESS_PROCESSING                         "PROCESSING"
#message 134 EXPRESSPAY_MESS_CLESS_TRANS_NOT_PERMITTED_L1       "TRANSACTION"
#message 135 EXPRESSPAY_MESS_CLESS_TRANS_NOT_PERMITTED_L2       "NOT PERMITTED"

/* ------------------------------------------------------------------------ */
/* PayPass Specific messages                                             */
/* ------------------------------------------------------------------------ */
#message 136 PAYPASS_MESS_NOT_AUTHORISED				        "NOT AUTHORISED"
#message 137 PAYPASS_MESS_ENTER_PIN						        "ENETER PIN"
#message 138 PAYPASS_MESS_ENTER_PIN_L2					        "ON TERMINAL"
#message 139 PAYPASS_MESS_REMOVE						        "REMOVE"
#message 140 PAYPASS_MESS_REMOVE_L2						        "CARD / DEVICE"
#message 141 PAYPASS_DS_MESS_MENU_ERASE                         "ERASE"
#message 142 PAYPASS_DS_MESS_MENU_CONSULT                       "CONSULT"
#message 143 PAYPASS_DS_MESS_MENU_DATA_STORAGE                  "DATA STORAGE"
#message 144 PAYPASS_DS_MESS_MENU_REDEEM                        "REDEEM"
#message 145 PAYPASS_DS_MESS_MENU_REGISTER                      "REGISTER"

#message 146 STD_MESS_COLLISION_LINE_1                          "PLEASE PRESENT"
#message 147 STD_MESS_COLLISION_LINE_2                          "ONLY ONE CARD"
#message 148 STD_MESS_RECEIPT_TXN_WITH_MOBILE                   "TRANSACTION USING MOBILE"
#message 149 STD_MESS_RECEIPT_TXN_WITH_CARD                     "TRANSACTION USING CARD"
#message 150 STD_MESS_RECEIPT_PIN_VERIFIED                      "CARDHOLDER PIN VERIFIED"
#message 151 STD_MESS_RECEIPT_NO_CARDHOLDER_VERIFICATION        "NO CARDHOLDER VERIFICATION"

/* ------------------------------------------------------------------------ */
/* Default messages                                                         */
/* ------------------------------------------------------------------------ */
#message 152 STD_MESS_FAILED                                    "FAILED"
#message 153 STD_MESS_DLL_TPASS                                 "TPASS DLL"
#message 154 STD_MESS_NOT_LOADED                                "MISSING"
#message 155 STD_MESS_MENU_DO_TRANSACTION                       "DO TXN"
#message 156 STD_MESS_CARD_NOT_SUPPORTED				        "NOT SUPPORTED"
#message 157 STD_MESS_MENU_TORN_LOG						        "TORN LOG"
#message 158 STD_MESS_MENU_PARAMS_TORN_PRINT_LOG                "PRINT LOG"
#message 159 STD_MESS_MENU_PARAMS_TORN_CLEAN_LOG                "CLEAN"
#message 160 STD_MESS_MENU_MAIN_MANUAL_CASH                     "MANUAL CASH"
#message 161 STD_MESS_MENU_MAIN_CASH_DEPOSIT                    "CASH DEPOSIT"
#message 162 STD_MESS_MENU_DATA_EXCHANGE                        "DATA EXCHANGE"
#message 163 STD_MESS_INSERT_CARD                               "INSERT CARD"
#message 164 STD_MESS_CASHBACK                                  "CASHBACK"
#message 165 STD_MESS_EMPTY                                     " "
#message 166 STD_MESS_MENU_PARAMS_TORN_AUTO_CLEAN_LOG           "AUTO CLEAN"

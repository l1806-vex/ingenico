//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  CASHREGISTER.C                      (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-June-2012     Kassovic
//  Last modified : 13-June-2012     Kassovic
//  Module : CASHREG
//                                                                          
//  Purpose :                                                               
//  How to manage IAM + Service call 100 with a cash register
//                                                                            
//  List of routines in file :  
//      SendTxMessage : Send message to the cash register.
//      ReceiveRxMessage : Receive message from the cash register.
//      CheckRestartTransaction : Check if transaction needs to be restarted.
//      CheckIdleState : Check if Manager is on Idle State or not.
//      Svc100Transaction : Transaction processes using Service Call 100.
//      Listener : Task to communicate with the cash register.
//      ForkListener : To fork listener task from after_reset() service call.
//
//  File history :
//  130612-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "CashReg.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxPrn;      // Peripheral file Printer
extern FILE *pxKbd;      // Peripheral file Keyboard

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define TRANSACTION_REQUEST     1
#define TRANSACTION_RESPONSE    2

#define CAM_ABSENT 0x0000

//#define COM_NAME  "COM0"
//#define COM_EVT COM0

//#define COM_NAME  "COM_MGBX"
//#define COM_EVT COM_EXT

#define COM_NAME  "COM5"
#define COM_EVT COM5

static bool bRestartTransaction; // Flag to restart transaction process
                                 // if a IAM message has been received

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
// Structure Transaction info in/out to communicate with service call 100 (Manager)
typedef struct
{
	S_TRANSIN     param_in;			// input parameter */
	S_TRANSOUT    param_out;	    // output parameter */
} ST_IO_TRANS;

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
static FILE *pxCom=NULL;                  // Peripheral file

static word usMainTaskNbr;
static t_topstack *hTsk=NULL;
static S_MESSAGE_IAM xMessage;

static ST_IO_TRANS xIOTrans;

//****************************************************************************
//          int SendTxMessage (char* pcTxBuffer, word usLenMsg)
//  This function sends a message through serial port COM0 to the cash register.
//  This function has parameters:
//     pcTxBuffer (I-) : Message to send.
//     usLenMsg (I-) : Length of the message to send.
//  This function has return value.
//     <0 : Sending failed.
//    >=0 : Sending done.
//****************************************************************************

static int SendTxMessage (char* pcTxBuffer, word usLenMsg)
{
	// Local variables
    // ***************
	Telium_size_t uiLen;
	byte ucSta;
	int iRet;

	// Send Message over RS232 line (COM0)
	// ***********************************
	uiLen = fwrite((void*) pcTxBuffer, 1, usLenMsg, pxCom);
	CHECK(uiLen==usLenMsg, lblKO);

	iRet = ttestall(COM_EVT, 1*100);
	CHECK (iRet!=0, lblKO);                                 // Timeout detected, sending failed => exit
	status (pxCom, &ucSta);
	CHECK ((ucSta & COM_SEND_END) == COM_SEND_END, lblKO);  // Transmission problem, sending failed

	iRet=1;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                      // Sending failed
    iRet=-1;
    goto lblEnd;
lblEnd:
    return iRet;
}

//****************************************************************************
//    int ReceiveRxMessage (char* pcRxBuffer, word usRxLen, word usTimeOut)
//  This function receives a message through serial port COM0 from the cash register.
//  This function has parameters:
//     pcRxBuffer (I-) : Reception buffer.
//     usLenMsg (I-) : Size of the reception buffer.
//     usTimeOut (I-) : Reception timeout.
//  This function has return value.
//     <0 : Reception failed.
//    >=0 : Length of the message received.
//****************************************************************************

static int ReceiveRxMessage (char* pcRxBuffer, word usRxLen, word usTimeOut)
{
	// Local variables
    // ***************
	word usLenMsg;
	Telium_size_t uiLen;
    int iRet;

    // Receive Message over RS232 line (COM0)
    // **************************************
    if (usTimeOut != 0)
    {
    	iRet = ttestall(COM_EVT, usTimeOut);      // Wait for first character
    	CHECK (iRet!=0, lblTimeOut);              // Timeout detected, reception failed => exit
    }

	usLenMsg=0;
	while (1)
	{
		uiLen = fread(pcRxBuffer, 1, 1, pxCom);
        if (uiLen != 1)
        {
        	iRet = ferror(pxCom);
        	CHECK(iRet==0, lblKO);                // Com0 error detected, reception failed => exit
        	iRet = ttestall(COM_EVT, 1*100);      // Wait for next characters
        	if (iRet==0) break;                   // Timeout inter character detected, reception done => exit
        }
        else
        {
        	usLenMsg++;
        	if (usLenMsg < usRxLen)
        		pcRxBuffer++;
        }
	};

	iRet = usLenMsg;
	goto lblEnd;

	// Errors treatment
    // ****************
lblTimeOut:                                       // Timeout
    iRet=0;
    goto lblEnd;
lblKO:                                            // Reception failed
    iRet=-1;
    goto lblEnd;
lblEnd:
    return iRet;
}

//****************************************************************************
//                  byte CheckRestartTransaction (void)
//  This function checks if a IAM message has been received during transaction
//   process.
//  This function has no parameters:
//  This function has return value.
//     false : No IAM message has been received during transaction process.
//             - Continue the transaction process with the data received from
//               the cash register.
//     true : A IAM message has been received during transaction process.
//             - Treat IAM message.
//             - Restart the transaction process with the previous data
//               received from the cash register.
//****************************************************************************

bool CheckRestartTransaction(void)
{
	return bRestartTransaction;
}

//****************************************************************************
//                       byte CheckIdleState (void)
//  This function checks if Manager is on IDLE state or not. Helpful from a
//   task to know if an application is under execution or Manager is under
//   IDLE state.
//  This function has no parameters:
//  This function has return value.
//     false : An application is under execution.
//     true : Manager is under IDLE state.
//****************************************************************************

static bool CheckIdleState(void)
{
	// Local variables
    // ***************
	T_Status xStatus;

    // Return Idle state status
    // ************************
	GetGeneralStatus(&xStatus);     // Retrieve some general status
	if(xStatus.M2OSState == 4)      // Check IDLE state
		return TRUE;                // Manager is in IDLE state
	else
		return FALSE;               // Manager is NOT in IDLE state
}

//****************************************************************************
//                  int Svc100Transaction (char* pcMessage)
//  This function jumps to the service call 100 to start the transaction.
//   1) It parses the message received from the cash register to pass the following
//   information to the service call 100:
//    - Amount
//    - Currency (Label, Code, Decimal position)
//    - Cash register number = "01"
//    - Payment mode = CARD_PAYMENT
//    - Payment type = Debit, Credit, Cancel and Pre-Authorization
//    - Payment support = UNKNOWN SUPPORT (All support done at Manager level).
//   2) Transaction payment done by ServiceCall() function
//   3) Build the transaction response to send to the cash register with the
//   following information:
//    - X = Status of the transaction (0=done, 1=failed).
//    - YYYYYYYYYYYYYYYYYYY = The Account number.
//  This function has no parameters:
//  This function has return value.
//     <0 : Service call 100 failed.
//    >=0 : Service call 100 done.
//****************************************************************************

int Svc100Transaction (char* pcMessage)
{
	// Local variables
    // ***************
	char tcAmount[50+1];
	unsigned long ulAmount;
	byte ucPriority;
	bool bRestart;
	int iRet, iCode;

	FILE *pxSmc=NULL;

	// Check if ServiceCall 100 is available
	// *************************************
	if ((iRet=ServiceGet(TYPE_GESTIONNAIRE, 100, &ucPriority)) == 0)
	{
		bRestart = CheckRestartTransaction();                          // IAM message receive during transaction process ?
		if (bRestart == FALSE)                                         // No, start transaction with data received from cash register
		{
			// Transaction Initialization
			// ==========================
			// Structure transaction out by default
			xIOTrans.param_out.noappli = 0xFF;
			xIOTrans.param_out.rc_payment  = PAY_KO;
			memset(xIOTrans.param_out.card_holder_nb, 0, sizeof(HOLDER_NB));

			// Structure transaction in by default
			xIOTrans.param_in.entry = CASH_REG_ENTRY;                  // Data comes from a cash register

			memset(tcAmount, 0, sizeof(tcAmount));                     // *** Amount ***
			memcpy(tcAmount, pcMessage+1, 8);
			ulAmount = (unsigned long) atoi(tcAmount);
			xIOTrans.param_in.amount = ulAmount;
	                                                                   // *** Currency ***
			memcpy(xIOTrans.param_in.currency.nom, pcMessage+9, 3);    // Label
			memcpy(xIOTrans.param_in.currency.code, pcMessage+12, 3);  // Code
			xIOTrans.param_in.currency.posdec = *(pcMessage+15) - '0'; // Decimal position
			memcpy(xIOTrans.param_in.cashreg, "01", 2);                // *** Cash register number ***

			xIOTrans.param_in.payment = CARD_PAYMENT;                  // *** Payment mode ***

			// DEBIT_TR, CREDIT_TR, CANCEL_TR, EXT_CANCEL_TR, PRE_AUTH_TR
			xIOTrans.param_in.transaction = *(pcMessage) - '0';        // *** Type ***

			// Detect support from manager then start application selection
			xIOTrans.param_in.support = UNKNOWN_SUPPORT;               // *** Support Type (all done by manager) ***
		}
		else                                                           // Yes, start the transaction with previous data received from cash register
		{
			// NOP
		}

		// Transaction process
		// ===================
		fclose(pxPrn);                                                 // Close "printer" channel before calling Manager
		fclose(pxKbd);                                                 // Close "keyboard" channel before calling Manager
		iRet = ServiceCall(TYPE_GESTIONNAIRE, 100, sizeof(ST_IO_TRANS), &xIOTrans, &iCode); // Service call failed => PAY_KO by default

		// Check the result of the transaction to determine if a IAM message has been received during transaction process
		if ((xIOTrans.param_out.rc_payment == 0) && *xIOTrans.param_out.card_holder_nb == 0)
			bRestartTransaction = TRUE;                                // IAM message received during transaction, transaction must be restarted
		else
			bRestartTransaction = FALSE;                               // NO IAM message received during transaction, transaction processing ending


		pxSmc = stdperif("CAM0", NULL);                                // Check "smart" channel already opened? (done by Svc100)
		if (pxSmc != NULL)                                             // !!! Bug Svc100 ? no problem with "mag" channel not reopened
			fclose(pxSmc);
		pxPrn = fopen("PRINTER", "w-");                                // Re-open "printer" channel
		pxKbd = fopen("KEYBOARD", "r");                                // Re-open "keyboard" channel

		// Send transaction results
		// ========================
		if (bRestartTransaction == FALSE)                              // Transaction ending correctly, send results to the cash register.
		{
			// Build the message, sends it to the protocol task
			// The response is an ASCII message of 20bytes:
			// XYYYYYYYYYYYYYYYYYYY where X is the status and Y the
			// holder number. X=1 means failure while 0 means success
			memset(xMessage.value, 0, sizeof(xMessage.value));
			xMessage.receiver = (TaskIam2*256)+ MANAGER_TYPE;
			xMessage.sender   = (TaskApplication*256);
			xMessage.type     = TRANSACTION_RESPONSE;
			sprintf((char*)xMessage.value, "%d%s", xIOTrans.param_out.rc_payment, xIOTrans.param_out.card_holder_nb);
			xMessage.length = strlen((char*)xMessage.value);

			// Send it
			iRet = Send_Message(&xMessage);
			if (iRet==1)
				iRet=0;                                                // Sending Message to the task done (SrvCall100 done)
			else
				iRet=-1;                                               // Sending Message to the task failed (SrvCall100 failed)
		}
		else                                                           // IAM message received during transaction process (SrvCall100 done)
			iRet=0;                                                    // Transaction must be restarted
	}

	return iRet;
}

//****************************************************************************
//                         word Listener(void)
//  This function represents the task which is going to communicate with the
//   cash register.
//   The cash register will send 3 messages to the task:
//    - Message to start a transaction using Service Call 100 via IAM on terminal.
//    - Message to cancel any activity on terminal.
//    - Message to manage a IAM message received during transaction process.
//   The task will send 1 message to the cash register:
//    - Message of the transaction response.
//   If the terminal is locked on the transaction process after 1 minute the,
//    task will automatically cancel any activity on terminal.
//  This function has no parameters:
//  This function has return value.
//     0 : Task error processing, kill itself (exit from the loop).
//****************************************************************************

static word Listener(void)
{
	// Local variables
    // ***************
	unsigned int   uiMask;        /* Mask of event to wait depending of task state */
	char tcTxBuffer[256];
    char tcRxBuffer[256];
    int iRet;

    // Com0 Initialization
    // *******************
	pxCom = fopen(COM_NAME, "rw*");                                 // Open channel
	CHECK(pxCom!=NULL, lblKO);

	if (COM_EVT != COM5)
	{
		iRet = format(COM_NAME, 115200, 8, 1, NO_PARITY, EVEN, 0);  // Format channel
		CHECK(iRet>=0, lblKO);
	}

    // Assign a mailbox to this task
	// *****************************
    iRet = Register_Mailbox_User(TaskIam2);
    CHECK(iRet>0, lblKO);

    // Send a event to Main task
	// *************************
    iRet = SignalEvent(usMainTaskNbr, EVT_DIALOG);                  // Signal to main task that listener task is initialized
    CHECK(iRet==cOK, lblKO);

    // Wait for incoming message
	// *************************
    uiMask = COM_EVT;
    while(1)
    {
    	iRet = ttestall(uiMask, 120*100);
    	if (iRet == COM_EVT)
    	{
    		// Message received from cash register (MASTER)
    		// ============================================
    		memset(tcRxBuffer, 0, sizeof(tcRxBuffer));
    		iRet = ReceiveRxMessage (tcRxBuffer, sizeof(tcRxBuffer)-1, 0);
    		CHECK(iRet>=0, lblKO);
    		if (iRet > 0)
    		{
    			// Analyze the message received and start the process from terminal (SLAVE)
    			// ========================================================================
    			switch (tcRxBuffer[0])
    			{
    			case 'B':
    			    // *** Service Call 100 ***
    				// IAM sent to application via Manager to start application selection process + transaction (CREDIT, DEBIT, CANCEL supported) using service call 100
    				// Build the message, sends it to the application itself
    				xMessage.receiver = (TaskApplication*256) + (CASHREG_APPLI_TYPE & 0x00FF);
    				xMessage.sender   = (CASHREG_APPLI_TYPE & 0xFF00);
    				xMessage.type     = TRANSACTION_REQUEST;

    				memset(xMessage.value, 0, sizeof(xMessage.value));
            		// Send a message to the manager with the following string:
    				//   - 1 ASCII bytes: Type       "0"=DEBIT_TR "1"=CREDIT_TR "2"=CANCEL_TR "3"=EXT_CANCEL_TR, "4"= PRE_AUTH_TR
    				//   - 8 ASCII bytes: Amount
            		//   - 3 ASCII bytes: Currency
            		//   - 3 ASCII bytes: Currency code
            		//   - 1 ASCII byte: Decimal position

    				strcpy((char*)&xMessage.value, &tcRxBuffer[1]);
    				xMessage.length = strlen(&tcRxBuffer[1]);
    				buzzer(10);
            		if (CheckIdleState())                         // Manager on Idle state?
            		{
            			iRet = Send_Message(&xMessage);           // Yes, send message to Manager
            			CHECK(iRet>0, lblKO);
            		}
            		else
            		{
                        strcpy(tcTxBuffer, "\r\nTerminal Busy");  // No, return busy to cash register
        				iRet = SendTxMessage(tcTxBuffer, strlen(tcTxBuffer));
        				CHECK(iRet>=0, lblKO);
            		}
    				strcpy(tcTxBuffer, "\r\n");
        			iRet = SendTxMessage(tcTxBuffer, strlen(tcTxBuffer));
    				CHECK(iRet>=0, lblKO);
            		uiMask = COM_EVT | MSG;

    				break;
    			case 'C':
                    // *** Send MSG event to cancel any active wait on terminal ***
    				if (!CheckIdleState())                        // Manager on Idle state?
    					SignalEvent(usMainTaskNbr, EVT_MSG);      // No, Read_Message called just after with return 1 (failure)
    				else
    				{
    					strcpy(tcTxBuffer, "No Transaction\r\n"); // Yes, return no transaction to cash register
    					iRet = SendTxMessage(tcTxBuffer, strlen(tcTxBuffer));
    					CHECK(iRet>=0, lblKO);
    				}
                    break;
    			case 'D':
            		// *** Send back message to the application itself (IAM message process) ***
            	    buzzer(10);
    				SendToApplication(CASHREG_APPLI_TYPE, 2, strlen(&tcRxBuffer[1]), (byte*)&tcRxBuffer[1]);
    				break;
    			default:
    				break;
    			}
    		}
    	}
    	else if (iRet == MSG)
    	{
    		// Receive transaction data from terminal and send it to cash register
    		iRet = Read_Message(&xMessage, 0);

    		// Analyze transaction type received
    		if (iRet > 0)
    		{
    			switch (xMessage.type)
    			{
    			// *** Send transaction data to cash register ***
    			case TRANSACTION_RESPONSE:
    				// IAM response to message TRANSACTION_REQUEST
                    // The response is an ASCII message of 20bytes:
                    // XYYYYYYYYYYYYYYYYYYY where X is the status and Y the
                    // holder number. X=1 means failure while 0 means success
    				buzzer(10);
                    sprintf(tcTxBuffer, "%s\r\n", (char*)xMessage.value);
    				iRet = SendTxMessage(tcTxBuffer, strlen(tcTxBuffer));
    				CHECK(iRet>=0, lblKO);
    				break;
    			default:
    				break;
    			}
    		}
     		uiMask = COM_EVT;
    	}
    	else
    	{
    		// Terminal locked on transaction process after 1 minute
       		//if(!CheckIdleState())                              // Manager on Idle state?
       		{
        	   	strcpy(tcTxBuffer, "Timeout\r\n");               // No, return timeout to cash register
        	    iRet = SendTxMessage(tcTxBuffer, strlen(tcTxBuffer));
        	    CHECK(iRet>=0, lblKO);
        	    // Send MSG event to cancel any active wait
        	    SignalEvent(usMainTaskNbr, EVT_MSG);             // No, Read_Message called just after with return 1 (failure)
        	}
    	}
    }

	// Errors treatment
    // ****************
lblKO:                    // Task failed
	if(pxCom)
		fclose(pxCom);    // Close channel
	hTsk=NULL;
	kill(hTsk, "");       // Delete task
	return 0;
}


//****************************************************************************
//                         void ForkListener (void)
//  This function fork the task listen. This task will listen on COM0 port
//   to communicate with the cash register. This function is called at startup
//   from the service call after_reset(). This task will run forever in
//   background.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void ForkListener(void)
{
	// Local variables 
    // ***************
	byte ucDum1;
	int iDum2=0;

	// Fork a task to listen the cash register
	// ***************************************
	usMainTaskNbr = CurrentTask();           // Retrieve main task number
	hTsk = fork(Listener, &ucDum1, iDum2);   // Fork second task
	ttestall(DIALOG, 0);                     // Wait until listener task properly initialized
	buzzer(10);
}


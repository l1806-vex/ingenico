//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  IAC.C                             (Copyright INGENICO 2012)
//============================================================================
//  Created :       16-July-2012     Kassovic
//  Last modified : 16-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//             *** Inter application communication ***
//          TRAINING calls a service in USER2 application.
//  The USER2 application must be loaded inside the terminal.
//  !!! AVL.lib must be implemented to link properly.
//                                                                                       
//  List of routines in file :  
//      IacCallUser2 : Call a service in USER2 application
//                            
//  File history :
//  071612-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "TlvTree.h"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the IAC screen (Goal)
// ===================================
static const ST_DSP_LINE txIAC[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line4
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

//****************************************************************************
//                      void IacCallUser2 (void)
//  This function sends a message to the application USER2 by calling a service.
//       NoAppli = 0x162
//       Service = WAIT_RESPONSE
//  The message is build under TLV tree format then serialized before sending.
//  An answer is received from USER2. This answer is unserialized to get
//  TLV tree format again. By using some browsing tree functions the message is
//  retrieved.       
//   - TlvTree_New() : Tree creation
//   - TlvTree_AddChildString() : Add the string message to the Tree
//   - TlvTree_GetSerializationSize() : Get the serialize buffer size
//   - TlvTree_Serialize() : Serialize the Tree to data
//     Send / Receive
//   - TlvTree_Unserialize() : Unserialize data to Tree
//   - TlvTree_GetFirstChild() : Search for message in the Tree
//   - TlvTree_GetData() : Retrieve the VALUE message from the Tree
//  This function has no parameters.  
//  This function has return value.
//    >0 : IAC done
//    =0 : IAC missing Appli or no response
//    <0 : IAC failed
//****************************************************************************

int IacCallUser2(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
    TLV_TREE_NODE piNode=NULL; // Tree to serialize
	byte *pucBuffer=NULL;      // Serialized buffer
	int iSize;
	word usNoAppli, usService; // Appli to call with service
	byte ucPriority;
	char tcSnd[256], tcRsp[256];
	byte p; // Printer line index
    int iRet, iSta, iCode;

    // Inter application communication in progress
	// *******************************************
	
    // Service to call
	// ===============
	usNoAppli=0x162;                                         // USER2 application to call
	usService = WAIT_RESPONSE;                               // Service to call
    strcpy(tcSnd, "Hello, do you hear me?\n"                 // Data to send
		          "Hello, do you hear me?\n"
			   	  "Hello, do you hear me?\n"
				  "Hello, do you hear me?");

    // Build message to send under TLV tree format
	// ===========================================
	xScreen = GoalCreateScreen(xGoal, txIAC, NUMBER_OF_LINES(txIAC), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                             // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, true);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "1-Msg to TlvTree", &txIAC[0], 1*1000, true);
	CHECK(iRet>=0, lblKO);

	piNode = TlvTree_New(0x1110);                            // Create tree
	TlvTree_AddChildString(piNode, 0x1111, tcSnd);           // Add message to the tree
	iRet = GoalDspLine(xScreen, 1, "1-Serialize Tree", &txIAC[1], 1*1000, true);
	CHECK(iRet>=0, lblKO);                                   // Get serialized buffer size
    iSize = TlvTree_GetSerializationSize(piNode, TLV_TREE_SERIALIZER_DEFAULT);
	CHECK(iSize>0, lblKO);
	pucBuffer=(byte *)umalloc(iSize);                        // Allocate the serialize buffer size
	CHECK(pucBuffer!=NULL, lblKO);
	                                                         // Serialize the tree in the allocated buffer
	iRet = TlvTree_Serialize(piNode, TLV_TREE_SERIALIZER_DEFAULT, pucBuffer, iSize);
    CHECK(iRet>0, lblKO);
    
    TlvTree_Release(piNode); piNode=NULL;                    // Serialization done release tree

    // Call USER2 service to send message and receive response
	// =======================================================
	iRet = GoalDspLine(xScreen, 2, "1-Send Data", &txIAC[2], 1*1000, true);
	CHECK(iRet>=0, lblKO);
	GoalDestroyScreen(&xScreen);                             // Destroy screen

	iRet = ServiceGet(usNoAppli, usService, &ucPriority);    // Check if User2 service WAIT_RESPONSE exists
	CHECK(iRet==0, lblNoService);
	ClosePeripherals();                                      // Close standard peripherals before calling User2
    iRet = ServiceCall(usNoAppli, usService, iSize, pucBuffer, &iCode); // Call User2 service WAIT_RESPONSE
    iSta = OpenPeripherals(); CHECK(iSta>=0, lblKO);         // Re-open standard peripherals
	CHECK(iRet==0, lblKO);
    CHECK(iCode>=0, lblNoRsp);                               // Check if response received

    xScreen = GoalCreateScreen(xGoal, txIAC, NUMBER_OF_LINES(txIAC), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                             // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "2-Receive Data", &txIAC[0], 1*1000, true);
	CHECK(iRet>=0, lblKO);

    // Parse message received from TLV tree format
	// ===========================================
	iRet = GoalDspLine(xScreen, 1, "2-Unserial. Tree", &txIAC[1], 1*1000, true);
	CHECK(iRet>=0, lblKO);                                   // UnSerialize the allocated buffer to create a tree
    iRet = TlvTree_Unserialize(&piNode, TLV_TREE_SERIALIZER_DEFAULT, pucBuffer, iSize);
    CHECK(iRet==TLV_TREE_OK, lblKO);
	memset (tcRsp, 0, sizeof(tcRsp));                        // Get message from the tree
    strcpy (tcRsp,TlvTree_GetData(TlvTree_GetFirstChild(piNode)));
	iRet = GoalDspLine(xScreen, 2, "2-TlvTree to Msg", &txIAC[2], 1*1000, true);
	CHECK(iRet>=0, lblKO);
	
	// Release resources
	// =================
	TlvTree_Release(piNode); piNode=NULL;                    // Release tree
	ufree (pucBuffer); pucBuffer=NULL;                       // Release allocated buffer

	// Display message received
	// ========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	xDspLine = txIAC[0];
	xDspLine.xBW.eTextAlign = GL_ALIGN_CENTER;
	xDspLine.xColor.eTextAlign = GL_ALIGN_CENTER; xDspLine.xColor.ulPen = GL_COLOR_YELLOW;
	iRet = GoalDspLine(xScreen, 0, "TRAIN (Msg from USER2)", &xDspLine, 0, false);
	CHECK(iRet>=0, lblKO);                                   // Show msg received
	iRet = GoalDspMultiLine(xScreen, 1, tcRsp, strlen(tcRsp), txIAC, NUMBER_OF_LINES(txIAC), 0, true);
	CHECK(iRet>=0, lblKO);

    // Print message received
	// ======================
	p=0;
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8); // Create document
	CHECK(xDocument!=NULL, lblKO);

	xPrnLine = xPrinter;                                     // Build document (Training, From User2, Msg info)
	xPrnLine.eTextAlign = GL_ALIGN_CENTER;
	xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "TRAINING", &xPrnLine);
	CHECK(iRet>=0, lblKO);
	xPrnLine.eTextAlign = GL_ALIGN_LEFT;
	xPrnLine.xFont.eScale = GL_SCALE_LARGE;
	iRet = GoalPrnLine(xDocument, p++, "Msg from USER2:", &xPrnLine);
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcRsp, &xPrnLine);    // Msg received
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                       // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);         // Wait for key pressed/touched (shortcut)                                                   // Wait for key pressed

	iRet=1;
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                       // None-classified low level error
    GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    iRet=-1;
    goto lblEnd;
lblNoService:                                                // Service unreachable
	GL_Dialog_Message(xGoal, NULL, "USER 2 missing\nOr Service Unreachable", GL_ICON_WARNING, GL_BUTTON_VALID, 3*1000);
    iRet=0;
    goto lblEnd;
lblNoRsp:                                                    // No response received
	GL_Dialog_Message(xGoal, NULL, "Waiting Response\nFrom Service Call", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    iRet=0;
lblEnd: 
    if (piNode)
    	TlvTree_Release(piNode);                             // Release tree
    if (pucBuffer)
    	ufree(pucBuffer);                                    // Release allocated buffer

	if (xScreen)
		GoalDestroyScreen(&xScreen);                         // Destroy screen
	if (xDocument)
		GoalDestroyScreen(&xDocument);                       // Destroy document

	return iRet;
}



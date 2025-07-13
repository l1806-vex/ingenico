//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  IAC.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Inter application communication:
//          TRAINING calls a service in USER2 application.
//  The USER2 application must be loaded inside the terminal.
//  !!! AVL.lib must be implemented to link properly.
//                                                                                       
//  List of routines in file :  
//      IacCallUser2 : Call a service in USER2 application
//                            
//  File history :
//  120508-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"
#include "TlvTree.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxPrn;      // Peripheral file Printer
extern FILE *pxKbd;      // Peripheral file Keyboard

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
    /* */

//****************************************************************************
//                   void IacCallUser2 (void)                             
//  This function sends a message to the application USER2 by calling a service.
//       NoAppli = 0x162
//       Service = WAIT_RESPONSE
//  The message is build under TLV tree format then serialize before sending.
//  An answer is received from USER2. This answer is unserialize to get 
//  TLV tree format again. By using some browsing tree functions the message is
//  retrieved.       
//       TlvTree_New() : Tree creation
//       TlvTree_AddChildString() : Add the string message to the Tree
//       TlvTree_GetSerializationSize() : Get the serialize buffer size
//       TlvTree_Serialize() : Serialize the Tree to data
//       Send / Receive
//       TlvTree_Unserialize() : Unserialize data to Tree
//       TlvTree_GetFirstChild() : Search for message in the Tree
//       TlvTree_GetData() : Retrieve the VALUE message from the Tree
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
    TLV_TREE_NODE piNode=NULL;                                                          // Tree to serialize
	byte *pucBuffer=NULL;                                                               // Serialized buffer
	int iSize;
	word usNoAppli, usService;                                                          // Appli to call with service
	byte ucPriority;
	char tcSnd[256], tcRsp[256];
    int iRet, iCode;

    // Inter application communication in progress
	// *******************************************
	_clrscr();                                                                          // Clear screen
	
    // Service to call
	// ===============
	usNoAppli=0x162;                                                                    // USER2 application to call
	usService = WAIT_RESPONSE;                                                          // Service to call
    strcpy(tcSnd, "Hello, do you hear me?\n"                                            // Data to send
		          "Hello, do you hear me?\n"
			   	  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?");

    // Build message to send under TLV tree format
	// ===========================================
   	DisplayMedium(0, 0, "1-Msg to TlvTree");
    ttestall(0, 1*100);                                                                 // Delay 1s 
	piNode = TlvTree_New(0x1110);                                                       // Create tree
	TlvTree_AddChildString(piNode, 0x1111, tcSnd);                                      // Add message to the tree                       
					                                      
    DisplayMedium(1, 0, "1-Serialize Tree");
    ttestall(0, 1*100);                                                                 // Delay 1s 
    iSize = TlvTree_GetSerializationSize(piNode, TLV_TREE_SERIALIZER_DEFAULT);          // Get serialized buffer size 
	CHECK(iSize>0, lblKO);
	pucBuffer=(byte *)umalloc(iSize);                                                   // Allocate the serialize buffer size
	CHECK(pucBuffer!=NULL, lblKO);

	iRet = TlvTree_Serialize(piNode, TLV_TREE_SERIALIZER_DEFAULT, pucBuffer, iSize);    // Serialize the tree in the allocated buffer
    CHECK(iRet>0, lblKO);
    
    TlvTree_Release(piNode); piNode=NULL;                                               // Serialization done release tree
    
    // Call USER2 service to send message and receive response
	// =======================================================
	DisplayMedium(2, 0, "1-Send Data");
    ttestall(0, 1*100);                                                                 // Delay 1s 
	iRet = ServiceGet(usNoAppli, usService, &ucPriority);                               // Check if User2 service WAIT_RESPONSE exists
	CHECK(iRet==0, lblNoService);
    fclose(pxPrn);                                                                      // Close "printer" channel before calling User2
    fclose(pxKbd);                                                                      // Close "keyboard" channel before calling User2
    iRet = ServiceCall(usNoAppli, usService, iSize, pucBuffer, &iCode);                 // Call User2 service WAIT_RESPONSE
	pxPrn = fopen("PRINTER", "w-*"); CHECK(pxPrn!=NULL, lblKO);                         // Re-open "printer" channel
	pxKbd = fopen("KEYBOARD", "r*"); CHECK(pxKbd!=NULL, lblKO);                         // Re-open "keyboard" channel
	CHECK(iRet==0, lblKO);
    CHECK(iCode>=0, lblNoRsp);
	_clrscr();                                                                          // Clear screen
	DisplayMedium(0, 0, "2-Receive Data");
    ttestall(0, 1*100);                                                                 // Delay 1s 

    // Parse message received from TLV tree format
	// ===========================================
    DisplayMedium(1, 0, "2-Unserial. Tree");
    ttestall(0, 1*100);                                                                 // Delay 1s 
    iRet = TlvTree_Unserialize(&piNode, TLV_TREE_SERIALIZER_DEFAULT, pucBuffer, iSize); // UnSerialize the allocated buffer to create a tree
    CHECK(iRet==TLV_TREE_OK, lblKO);
	memset (tcRsp, 0, sizeof(tcRsp));
    strcpy (tcRsp,TlvTree_GetData(TlvTree_GetFirstChild(piNode)));                      // Get message from the tree
    DisplayMedium(2, 0, "2-TlvTree to Msg");
    ttestall(0, 1*100);                                                                 // Delay 1s 
	
	// Release resources
	// =================
	TlvTree_Release(piNode); piNode=NULL;                                               // Release tree
	ufree (pucBuffer); pucBuffer=NULL;                                                  // Release allocated buffer  
	
	// Display message received
	// ========================
    _clrscr();                                                                          // Clear screen
    DisplaySmall(0, 0, "TRAINING");
    DisplaySmall(1, 0, "Msg from USER2:");
    Display25(2, tcRsp, strlen(tcRsp));                                                 // Display response
    DisplaySmall(7, 6, "Press a key");

    // Print message received
	// ======================
	iRet = pprintf("\x1b""E""TRAINING\n""\x1b""F"); CHECK(iRet>=0, lblKO);   
    iRet = pprintf("Msg from USER2:\n"); CHECK(iRet>=0, lblKO);
    iRet = Print24(tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);                        // Print msg received
    iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

    reset_buf(pxKbd, _receive_id);                                                      // Reset keyboard FIFO
    ttestall(KEYBOARD, 30*100);                                                         // Wait until key pressed or timeout
    reset_buf(pxKbd, _receive_id);                                                      // Reset keyboard FIFO to clear key pressed

	iRet=1;
    goto lblEnd;

	// Errors treatment 
    // ****************
lblNoService:                                                                       
	_clrscr();                                                                          // Clear screen
	DisplayMedium(0, 0, "Ap USER2 missing");                                            // Service unreachable
    ttestall(0, 5*100);                                                                 // Delay 5s 
    iRet=0;
    goto lblEnd;
lblNoRsp:
	_clrscr();                                                                          // Clear screen
	DisplayMedium(0, 0, "No Response");                                                 // No response from service
    ttestall(0, 5*100);                                                                 // Delay 5s 
    iRet=0;
    goto lblEnd;
lblKO:
	_clrscr();                                                                          // Clear screen
	DisplayMedium(0, 0, "Processing Error");                                            // Oops! error
    ttestall(0, 5*100);                                                                 // Delay 5s 
    iRet=-1;
lblEnd: 
    if (piNode)
    	TlvTree_Release(piNode);                                                        // Release tree                                                  
    if (pucBuffer)
    	ufree(pucBuffer);                                                               // Release allocated buffer

    return iRet;
}



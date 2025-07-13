#ifndef __LINKLAYER_H_INCLUDED
#define __LINKLAYER_H_INCLUDED


//! \defgroup LINK_LAYER	LinkLayer component
//!
//! \par Introduction
//!
//! The Link Layer component is designed to manage all the physical links and protocols available
//! on TELIUM terminals. This component is an application loaded in the terminal
//! The Link Layer can manage several communications at the same time using different
//! peripherals (modem and serial port for example).
//! It is not yet customisable. So, the Link Layer must be modified to add new protocols. They can
//! not be implemented as add-ons in DLL, for example.
//! The Link Layer is able to manage the OSI layers 1 to 6 (see below). It currently supports the
//! following protocols:
//! - Physical: RS232, internal modem, external modem (via RS232), USB, Ethernet, Wifi, Bluetooth, GSM, GPRS and 3G.
//! - Data Link: SDLC, PPP.
//! - Network: IP.
//! - Transport: TCP.
//! - Transport interface: X28 (part of the transport layer. Can be put over all transport layers)
//!
//! The Link Layer component is available in two versions :
//! - Standard version (application code 3429xxxx) is the one provided in the Telium
//! SDK package. This version does not support IP protocols. However it is possible
//! to use it to perform TCP communications from WIFI or GPRS terminals.
//! - TCP/IP version (application code 3628xxxx) supports PPP, TCP/IP and SSL
//! protocols. It is submitted to the same license as the Telium SDK Add-On TCP/IP.
//! Please contact your program manager for further details.
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD><b>Developers shall read the documents <a href="ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.html">[Pack IP Security Guidance]</a> and
//! <a href="ICO-PE-046-GU-EN_PackSSL_SecurityGuidance_UserGuide.html">[SSL Security Guidance]</a> provided with the Telium SDK.
//! They describe best practises for implementing TCP/IP and SSL/TLS enabled
//! applications, according to the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
//! </TABLE>
//!
//! \par Interface
//!
//! The Link Layer provides the following functions:
//!
//! <TABLE border="1" cellspacing="0" bordercolor="black">
//! <TR>
//! <TD>LL_Configure()</TD>
//! <TD>Create, modify or delete a Link Layer configuration.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GetInfo()</TD>
//! <TD><b>[Deprecated]</b> Retrieve the parameters of a Link Layer configuration.</TD>
//! </TR>
//! <TR>
//! <TD>LL_Connect()</TD>
//! <TD>Connect.</TD>
//! </TR>
//! <TR>
//! <TD>LL_Disconnect()</TD>
//! <TD>Disconnect.</TD>
//! </TR>
//! <TR>
//! <TD>LL_Send()</TD>
//! <TD>Send a frame.</TD>
//! </TR>
//! <TR>
//! <TD>LL_Receive()</TD>
//! <TD>Wait and receive a frame.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GetLastError()</TD>
//! <TD>Retrieve the last error.</TD>
//! </TR>
//! <TR>
//! <TD>LL_ClearSendBuffer()</TD>
//! <TD>Clear the send buffer.</TD>
//! </TR>
//! <TR>
//! <TD>LL_ClearReceiveBuffer()</TD>
//! <TD>Clear the receive buffer.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GetStatus()</TD>
//! <TD>Retrieve the status of the Link Layer (connected, disconnected, ...).</TD>
//! </TR>
//! <TR>
//! <TD>LL_WaitEvent()</TD>
//! <TD>Wait for the end of the send or for an incoming frame.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GetHandle()</TD>
//! <TD>Retrieve handle on specific structures.</TD>
//! </TR>
//! </TABLE>
//!
//! \par Principles
//!
//! To use the Link Layer, an application must first create a configuration. The Link Layer will give a
//! handle on it. The application will use this handle to connect, disconnect, send, receive, ...
//! The applications can create as many configurations they need. It is only limited by the free
//! memory that is available.
//!
//! The applications can use the Link Layer to perform several communications at a time on
//! different devices (modem and serial port for example).
//! There are two ways of functioning. The first one is to configure the Link Layer at start-up or
//! when a parameter changes.
//! The second way is to always configure the Link Layer just before a communication. So, the Link
//! Layer configuration is temporary. <b> IN THIS CASE, DO NOT FORGET TO DELETE THE
//! CONFIGURATION AFTER THE COMMUNICATION ENDS.</b>
//!
//! In all cases (either the application requests a disconnection or the host disconnects), a
//! communication is considered as terminated only when the LL_Disconnect() function is
//! called.
//!
//! The Link Layer API supports only synchronous function calls. For example, to perform a
//! background connection (pre-dialling, etc.), the caller must create a background task that will call
//! the Link Layer.
//!
//! \par OSI MODEL
//!
//! To define and implement protocols, the OSI model (Open System Interconnection) was defined
//! as an ISO standard. It decomposes a communication in 7 layers. Each layer has a well known
//! job that is described here after.
//!
//! <TABLE border="1" cellspacing="0" bordercolor="black" valign="middle" >
//! <TR><TD>Layer</TD><TD>Function</TD><TD>Protocol Examples</TD><TD>Network Components</TD></TR>
//! <TR>
//! <TD style="text-align:center;">7<br>Application</TD>
//! <TD><br>
//! - Allows access to network services that support applications.<br>
//! - Handles network access, flow control and error recovery.<br>
//! - Examples are file transfer, e-mail,...</TD>
//! <TD style="text-align:center;"><br>SMTP,<br>NFS,<br>ISO8583,<br>SPDH,<br> ...</TD><TD style="text-align:center;">Gateway,<br>...</TD>
//! </TR>
//! <TR>
//! <TD style="text-align:center;">6<br>Presentation</TD>
//! <TD><br>
//! - Translates from application to network format and vice-versa.<br>
//! - All different formats from all sources are made into a common uniform format that the rest of the
//! OSI model can understand.<br>
//! - Responsible for protocol conversion, character conversion, data encryption / decryption, expanding graphics commands, 
//! data compression, ...<br>
//! - Not always implemented in a network protocol.<br>
//! <TD style="text-align:center;"><br></TD>
//! <TD style="text-align:center;">Gateway,<br>...</TD>
//! </TR>
//! <TR>
//! <TD style="text-align:center;">5<br>Session</TD>
//! <TD><br>
//! - Establishes, maintains and ends sessions across the network.<br>
//! - Responsible for name recognition (identification), so only the designated parties can participate in
//! the session.<br>
//! <TD style="text-align:center;"><br>Named pipes,<br>RPC,<br>...</TD>
//! <TD style="text-align:center;">Gateway,<br>...</TD>
//! </TR>
//! <TR>
//! <TD style="text-align:center;">4<br>Transport</TD>
//! <TD><br>
//! - Manages the flow control of data between parties across the network.<br
//! - Divides streams of data into chunks or packets; the transport layer of the receiving computer
//! reassembles the message from packets.<br>
//! - Manage lost and duplicated packets.<br>
//! <TD style="text-align:center;">TCP,<br>SPX,<br>...</TD>
//! <TD style="text-align:center;">Gateway,<br>Router,<br>...</TD>
//! </TR>
//! <TR>
//! <TD style="text-align:center;">3<br>Network</TD>
//! <TD><br>
//! - Responsible for addressing, determining routes, managing network problems such as packet switching, 
//! data congestion and routing.<br>
//! - Break big packets into smaller ones. At the receiving end, the network layer reassembles the data.<br>
//!
//! <TD style="text-align:center;"><br>IP,<br>ARP,<br>ICMP,<br>IPX,<br>...</TD>
//! <TD style="text-align:center;">Router,<br>ATM Switch,<br>...</TD>
//! </TR>
//! <TR>
//! <TD style="text-align:center;">2<br>Data link</TD>
//! <TD><br>
//! - Responsible for error-free transfer of frames to other device via the Physical Layer.<br>
//! <TD style="text-align:center;"><br>PPP,<br>V42,<br>SDLC,<br>...<br></TD>
//! <TD style="text-align:center;">Switch,<br>ISDN router,<br>...</TD>
//! </TR>
//! <TR>
//! <TD style="text-align:center;">1<br>Physical</TD>
//! <TD><br>
//! - Transmits raw bit stream over physical cable.<br>
//! - Defines cables, cards, and physical aspects.<br>
//! - Defines techniques to transfer bit stream to cable.<br>
//! <TD style="text-align:center;"><br>ISDN,<br>V22,<br>V22bis,<br>...<br></TD>
//! <TD style="text-align:center;">Modem,<br>Ethernet,<br>Card,<br>Hub,<br>...</TD>
//! </TR>
//! </TABLE>
//!
//! \par Interface objects
//!
//! The LinkLayer components uses the TlvTree interface object to exchange the configuration
//! parameters. The TlvTree interface is described in the document : [SMO-SFO-0083_TlvTree_ReferenceManual.pdf].
//! The versions of LinkLayer prior to 3.1 used the _DEL_ object to interface. For reasons of
//! compatibility, the new versions of the LinkLayer component supports the two interface methods.
//! However, it is recommended to use the TlvTree object, because it does not limit the number of
//! elements and the size of an element.
//!
//! <b>Applications previously compiled and using the _DEL_ object do not need to be recompiled
//! to request services of the LinkLayer versions >= 3.1.</b>
//! 
//! The LinkLayer interface library (LinkLayerExeInterface.lib) requires the use of the TlvTree services
//! available in the AVL library (AVL.lib furnished in the Telium SDK from version 5.7). This library
//! must be included in the link command before the LinkLayer interface library. For compilation, the
//! LinkLayer header file <LinkLayer.h> requires the previous inclusion of the TLV tree library header
//! file <TlvTree.h>.
//! 
//! For compatibility reason, it is possible to recompile an application without using the TlvTree
//! interface object. It is not recommended but it allows developers not to modify the source code of
//! their applications. The developers just have to modify the compilation settings to define the preprocessor
//! variable __USE_DEL_INTERFACE__ and to link with the LinkLayerExeInterface_DEL
//! library.
//!
//! \par Network management
//!
//! The Link Layer component provides some functions to monitor the network (in particular the
//! GSM/GPRS/3G networks). These functions have been added in order to make easier and
//! more independent the particular management of these networks.
//!
//! <TABLE border="1" cellspacing="0" bordercolor="black">
//! <TR>
//! <TD>LL_Network_GetStatus()</TD>
//! <TD>Return the current status of a network.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GSM_Start()</TD>
//! <TD>Start the internal GSM modem and enables the GSM facility.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GSM_Stop()</TD>
//! <TD>This function disconnects the GSM network.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GPRS_Start()</TD>
//! <TD>This function starts the GPRS/3G modem and enables the GPRS/3G facility.</TD>
//! </TR>
//! <TR>
//! <TD>LL_GPRS_Connect()</TD>
//! <TD>This function establishes the PPP link with the GPRS/3G provider.</TD>
//! </TR>
//! </TABLE>
//!
//! A sample showing how to manage the connection to the GPRS/3G network : \ref LL_SAMPLE_GPRS_CONNECTION.
//!
//! \par Audit modem
//!
//! For PSTN communications, it is possible to get the signal line. This operation is called modem audit.
//! It is useful to solve the connection problems to a remote host and to investigate the performance 
//! of a PSTN communication
//!
//! To perform an audit :
//!	- (1) Load the audit modem driver :
//!		- 30158xxx.M30 for EFT30,
//!		- 40158xxx.M31 for EFT930.
//!
//!	- (2) Load the debug version of the LinkLayer component, available in Components\\Link Layer\\Traces directory.
//!
//! - (3) Perform one call with your application and get a trace using Trace.exe tool.
//!
//! - (4) Switch the terminal to LLT mode and retrieve the following files :
//!   - DAA.TXT in HOST directory (Activity = Downloading)
//!   - DETECTOR.BIN in HOST directory (Activity = Downloading)
//!   - MESSAGE.BIN in HOST directory (Activity = Downloading)
//!   - SAMPLES.RAW in HOST directory (Activity = Downloading)
//!   - SOFT_MODEM.TXT in HOST directory (Activity = Downloading)
//!   - MODEM.CFG in SWAP directory (Activity = Maintenance)
//!   - MODEM.DIA in SWAP directory (Activity = Maintenance)
//!
//! If several calls are performed in a row, only audit traces from the last call will be saved.
//!
//! If you can't find these files, please check that you've loaded both the audit modem driver 
//! and the debug version of the LinkLayer component.
//! If this is done correctly the text <b>">>LL has detected AuditModem"</b> should appear when using Trace.exe tool.
//!
//! - (5) Check that SAMPLES.RAW files is not empty. For this, open it with an hexadecimal editor 
//! and check that it's not starting with zeros. Otherwise perform another call.
//!
//! - (6) Send the 7 specified files and the trace file performed with Trace.exe tool.
//!
//! \par Modem configuration
//!
//! Depending on the modem available in the terminal (Netbricks or Conexant), the initialization string can changed.
//! To allow former applications to use new types of modem without being recompiled, a parameter file can be added.
//! This parameter file at XML format ('LINKLAYER.CFG') must be loaded in the SWAP directory of the terminal.
//! It defines an initialization string to be recognized and changed depending on the modem type as shown in the exemple below:
//!
//! \verbatim
//! <?xml version='1.0' encoding='us-ascii'?>
//! <linklayer version='1.0' >
//!     <modemConverter>
//!         <pattern initString='ATF5S144=16$M249$M251'>
//!             <!-- The following 'initString' attribute is 'AT&K0%C0\NO;+A8E=,,,0;+MS=V22B;+ES=6,,8;+ESA=0,0,,,1,0;S17=7<CR>ATW2' properly escaped -->
//!             <conversion modemType='CONEXANT' initString='AT&amp;K0%C0\\N0;+A8E=,,,0;+MS=V22B;+ES=6,,8;+ESA=0,0,,,1,0;S17=7\rATW2'/>
//!             <!-- Other 'conversion' tags might be added to handle several types of modem if needed -->
//!         </pattern>
//!         <!-- Other 'pattern' tags might be added to handle several initilization strings if needed -->
//!     </modemConverter>
//! </linklayer>
//! \endverbatim
//!
//! - The attribute 'initString' of the tag 'pattern' is the initialization string to be replaced. This is the initialization string passed
//! in the configuration TlvTree object (tag \ref LL_MODEM_T_INIT_STRING).
//! - The tag 'conversion' contains two mandatory attributes:
//!   - 'modemType' is the type of modem for which the command must be replaced. Its only possible value is 'CONEXANT' to match with Conexant hardware modem.
//!   - 'initString' is the string that must be used for the replacement.
//!
//! <b>The XML attribute 'initString' in both tags 'pattern' and 'conversion' must be formated as a C ASCII string, with the same escaped characters
//! ('\\\\' to encode '\\', '\\r' to encode carriage return etc.). The character '&' is also a special XML character and must be written in its escaped XML form ('&amp;amp;')</b>
//!
//! This file is unique for all the applications embedded in the terminal. If several applications use it, this file must be the result of the merge of
//! all the conversion parameters of the applications.
//!
//! \anchor SCRIPTING \par Communication scripting
//!
//! The LinkLayer supports the communication scripting.
//! It allows to store all the traces of communication in an ASCII file stored in the file system of the terminal.
//!
//! <b>This facility must used for development purpose only, to debug the application upper layers. This is not a way to debug communication problems.</b>
//! If the call sequence is modified between the capture and the replay of the scenario, the script file must be manually changed according to these changes.
//!
//! To use this mode, the application shall call the API \ref LL_Configure_Script() rather than \ref LL_Configure().
//! Please see the documentation of \ref LL_Configure_Script() for further details on this feature.
//!
//! This feature is available when linking the application with the 'LinkLayerExeInterface_Script.lib' library, and must be used for debug only.
//! This file is made of trace lines describing  :
//! - The connection (prefixed with "<->" and indicating the error code returned by LL_Connect() coded in big endian).
//! - The data reception (prefixed with "<--") followed by the data buffer sent.
//! - The data sending (prefixed with "-->") followed by the data buffer received.
//! - The disconnection (prefixed with ">-<" and indicating the error code returned by LL_Disconnect() coded in big endian).
//!
//! The data following the prefix is encoded as follow:
//! - Printable ASCII characters (0x20 to 0x7E) can be written 'as is' in the script file <b>EXCEPT</b>:
//!   - <b>Space (0x20) that can be either replaced by '.' or its hexadecimal value (x20, see below).</b>
//!   - <b>'x' character (0x78) that must be replaced by its hexadecimal value (x78, see below).</b>
//!   - <b>Point '.' (0x2E) that must be replaced by its hexadecimal value (x2E, see below).</b>
//! - Other bytes must be replaced by its hexadecimal value preceded by 'x'. 
//!
//! Example : 
//! \verbatim
//! <-> x00x00x00x00
//! --> This.is.a.message.sent.to.the.modemx2Ex00
//! <-- This.is.the.response.received.by.the.modemx2Ex00
//! >-< xFFxFFxFCx12
//! \endverbatim
//! In this example, the application calls:
//! - LL_Connect() which returns LL_ERROR_OK (0).
//! - LL_Send() with the buffer "This is a message sent to the modem." including the final '\\0'.
//! - LL_Receive() which returns the buffer "This is the response received by the modem." including the final '\\0'.
//! - LL_Disconnect() which returns LL_ERROR_NOT_CONNECTED (-1006).
//! 
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-----------------------------------------------------------------
#ifndef __LL_HANDLE__
#define __LL_HANDLE__

//! \brief LinkLayer communication handle. 
//! This handle is created and released by calls to the LL_Configure() function.
	typedef void* LL_HANDLE;

#endif

#ifndef __TLV_TREE_NODE__
#define __TLV_TREE_NODE__
//! \brief TLV tree node (please refer the AVL documentation.
	typedef int * TLV_TREE_NODE;
#endif


//-- Macros & preprocessor definitions ----------------------------

//-- Diagnostics --------------------------------------------------
#define LL_DIAGNOSTICS					0x8000

#define LL_DIAG_CONFIGURE				(LL_DIAGNOSTICS + 1)


//-- Tags ---------------------------------------------------------

#define LL_TAG_STATUS_CODE				0x9f8801


//! \defgroup LL_LAYER_TAGS	 LinkLayer tags
//! \ingroup LINK_LAYER
//! \brief Tags to specify the communication layers and the root of a configuration tree. 
//! @{

//! \brief LinkLayer parameters. Root tag for the parameter configuration tree.
#define LL_TAG_LINK_LAYER_CONFIG		0xBF9503

// -- DO NOT SUPPRESS THIS LINE -------------------
//! \brief Physical layer.
#define LL_TAG_PHYSICAL_LAYER_CONFIG	0x9f8810	

//! \brief Transport layer.
#define LL_TAG_TRANSPORT_LAYER_CONFIG	0x9f8811

//! \brief Data link layer.
#define LL_TAG_DATA_LINK_LAYER_CONFIG	0x9f881d
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Physical links
//! \defgroup LL_PHYSICAL_PARAMETERS	Physical layer parameters
//! \ingroup LINK_LAYER
//! \brief Parameters to configure the physical layer.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_DATA_LINK_PARAMETERS	Data link layer parameters
//! \ingroup LINK_LAYER
//! \brief Parameters to configure the data link layer.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_TRANSPORT_PARAMETERS	Transport layer parameters
//! \ingroup LINK_LAYER
//! \brief Parameters to configure the transport layer.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


#define LL_TAG_CONNECTION_STATUS		0x9f881b


//-- Protocols ----------------------------------------------------
#define LL_NO_PROTOCOL				0

// Transport protocols
#define LL_TRANSPORT_TCP			10

// Network protocols
#define LL_NETWORK_PAD				1


//-- Protocols parameters ----------------------------------------


//-- Physical parameters -----------------------------------------
/*! \brief  Tag to specify the physical link.

	\ref LL_PHYSICAL_LINK : list of values.
*/
#define LL_PHYSICAL_T_LINK			1 

//! \brief  Value length for the tag LL_PHYSICAL_T_LINK.
#define LL_PHYSICAL_L_LINK			1

//! \defgroup LL_PHYSICAL_LINK	Physical links
//! \ingroup LL_PHYSICAL_PARAMETERS
//! \brief The possible values of LL_PHYSICAL_T_LINK tag.
//! \note 
//! (1) Serial ports COM3, COM10 and COM11 are only available on CAD30 UCM.
//! \note 
//! (2) The type of USB/RS232 converter is automatically detected. The following devices are
//! currently supported :
//! - Keyspan,
//! - Prolific,
//! - Silicon Labs,
//! - FTDI.
//! \note 
//! (3) The default TCP/IP interface link has been defined in the scope of the TELICAPT
//! (U32->TELIUM). It allows application to not specify explicitly the TCP/IP interface
//! using directly the one currently established. In this mode, the LinkLayer is not able to
//! check the network availability and to perform the TCP/IP interface selection.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! \brief RS232 serial link. COMO port.
#define LL_PHYSICAL_V_COM0				0		
//! \brief RS232 serial link. COM1 port.
#define LL_PHYSICAL_V_COM1				1		
//! \brief RS232 serial link. COM2 port.
#define LL_PHYSICAL_V_COM2				2
//! \brief RS232 serial link. COM3 port. (1)
#define LL_PHYSICAL_V_COM3				3		
//! \brief RS232 serial link. COM10 port. (1)
#define LL_PHYSICAL_V_COM10				4		
//! \brief RS232 serial link. COM11 port. (1)
#define LL_PHYSICAL_V_COM11				5

//! \cond __EXCLUDE__
#define LL_PHYSICAL_V_COM_AIAP          6
//! \endcond

//! \brief Bluetooth SPP (Serial Port Profile).
#define LL_PHYSICAL_V_BLUETOOTH_SPP     7

//! \brief TCP link over AIAP (for iSMP terminals)
//! To perform TCP connections with iSMP, the TCP DLL for iSMP must be loaded in the terminal.
//! Otherwise the the connection will fail with the error \ref LL_ERROR_DLL.
#define LL_PHYSICAL_V_TCP_AIAP     8

//! \brief USB serial link (USB device=USB slave).
#define LL_PHYSICAL_V_USB				10		
//! \brief USB serial link (USB host).
#define LL_PHYSICAL_V_USB_HOST			11		
//! \brief USB serial link on base (USB device=USB slave).
#define LL_PHYSICAL_V_USB_BASE			12		
//! \brief USB serial link on iWL base (USB host slot 1).
#define LL_PHYSICAL_V_USB_BASE_HOST_1	13
//! \brief USB serial link on iWL base (USB host slot 2).
#define LL_PHYSICAL_V_USB_BASE_HOST_2	14
//! \brief USB serial link (USB host) when connected to an iST150.
#define LL_PHYSICAL_V_USB_HOST_CL       15
//! \brief USB serial link (USB host) when connected to an iPP320 or an iPP350.
#define LL_PHYSICAL_V_USB_HOST_PP       16
//! \brief Internal modem.
#define LL_PHYSICAL_V_MODEM				20		
//! \brief Internal modem V34.
#define LL_PHYSICAL_V_MODEM_V34			21		
//! \brief Ethernet interface.
#define LL_PHYSICAL_V_ETHERNET			30		
//! \brief GSM modem.
#define LL_PHYSICAL_V_GSM				40		
//! \brief GPRS/3G modem.
#define LL_PHYSICAL_V_GPRS				41		
//! \brief WIFI interface.
#define LL_PHYSICAL_V_WIFI				50		

//! \brief RS232 serial link using an USB/RS232 converter. (2)
#define LL_PHYSICAL_V_CONVERTER_USB_RS232	100	
//! \brief Current TCP/IP interface. (3)
#define LL_PHYSICAL_V_DEFAULT_TCPIP          60 
//! \brief Tailgate interface.
//! To perform connection using Tailgate channel, the TALIF DLL must be loaded in the terminal.
//! Otherwise the configuration will fail with the error \ref LL_ERROR_DLL.
#define LL_PHYSICAL_V_TAILGATE               70


// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_SERIAL_LINK_PARAMETERS	Serial link parameters
//! \ingroup LL_PHYSICAL_PARAMETERS
//!	\brief Parameters to configure the serial links.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup LL_SERIAL_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
// Baudrate
/*! \brief Tag to specify the speed of a serial RS232 communication.

	\ref LL_SERIAL_LINK_BAUDRATE : list of values.
*/
#define LL_PHYSICAL_T_BAUDRATE			2 

//! \brief  Value length for the tag LL_PHYSICAL_T_BAUDRATE.
#define LL_PHYSICAL_L_BAUDRATE			4
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_SERIAL_LINK_BAUDRATE	Serial link baurates
//! \ingroup LL_SERIAL_LINK_PARAMETERS
//! \brief The possible values of LL_PHYSICAL_T_BAUDRATE tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief 300 bauds.
#define LL_PHYSICAL_V_BAUDRATE_300		300		
//! \brief 1200 bauds.
#define LL_PHYSICAL_V_BAUDRATE_1200		1200	
//! \brief 2400 bauds.
#define LL_PHYSICAL_V_BAUDRATE_2400		2400	
//! \brief 4800 bauds.
#define LL_PHYSICAL_V_BAUDRATE_4800		4800	
//! \brief 9600 bauds.
#define LL_PHYSICAL_V_BAUDRATE_9600		9600	
//! \brief 19200 bauds.
#define LL_PHYSICAL_V_BAUDRATE_19200	19200	
//! \brief 38400 bauds.
#define LL_PHYSICAL_V_BAUDRATE_38400	38400	
//! \brief 57600 bauds.
#define LL_PHYSICAL_V_BAUDRATE_57600	57600
//! \brief 115200 bauds.
#define LL_PHYSICAL_V_BAUDRATE_115200	115200	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Bits per byte
//! \addtogroup LL_SERIAL_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Tag to specify the number of data bits.
#define LL_PHYSICAL_T_BITS_PER_BYTE		3

//! \brief  Value length for the tag LL_PHYSICAL_T_BITS_PER_BYTE.
#define LL_PHYSICAL_L_BITS_PER_BYTE		1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#define LL_PHYSICAL_V_7_BITS			7
#define LL_PHYSICAL_V_8_BITS			8

//! \addtogroup LL_SERIAL_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// Stop bit(s)
//! \brief Tag to set the stop bits.
#define LL_PHYSICAL_T_STOP_BITS			4

//! \brief  Value length for the tag LL_PHYSICAL_T_STOP_BITS.
#define LL_PHYSICAL_L_STOP_BITS			1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#define LL_PHYSICAL_V_1_STOP			1
#define LL_PHYSICAL_V_2_STOP			2

//! \addtogroup LL_SERIAL_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// Parity
/*! \brief Tag to specify the parity.

	\ref LL_SERIAL_LINK_PARITY : list of values.
*/
#define LL_PHYSICAL_T_PARITY			5	

//! \brief  Value length for the tag LL_PHYSICAL_T_PARITY.
#define LL_PHYSICAL_L_PARITY			1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_SERIAL_LINK_PARITY	Serial link parity
//! \ingroup LL_SERIAL_LINK_PARAMETERS
//! \brief The possible values of LL_PHYSICAL_T_PARITY tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief No parity.
#define LL_PHYSICAL_V_NO_PARITY			0	
//! \brief Odd parity.
#define LL_PHYSICAL_V_ODD_PARITY		1	
//! \brief Even parity.
#define LL_PHYSICAL_V_EVEN_PARITY		2	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup LL_SERIAL_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// Flow control
/*! \brief Tag to specify the flow control mode.

	\ref LL_SERIAL_LINK_FLOW_CTRL : list of values.
*/
#define LL_PHYSICAL_T_FLOW_CTRL			6	

//! \brief  Value length for the tag LL_PHYSICAL_T_FLOW_CTRL.
#define LL_PHYSICAL_L_FLOW_CTRL			1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_SERIAL_LINK_FLOW_CTRL	Serial link flow control mode
//! \ingroup LL_SERIAL_LINK_PARAMETERS
//! \brief The possible values of LL_PHYSICAL_T_FLOW_CTRL tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief No flow control.
#define LL_PHYSICAL_V_NO_FLOW_CTRL		0	
//! \brief Hardware flow control.
#define LL_PHYSICAL_V_HARD_FLOW_CTRL	1	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \brief Tag to specify that the underlying driver is already opened. The LinkLayer will be its owner during the communication.
#define LL_PHYSICAL_T_DRIVER_PREEMPTION    7
//! \brief Length of the tag \ref LL_PHYSICAL_T_DRIVER_PREEMPTION.
#define LL_PHYSICAL_L_DRIVER_PREEMPTION    1

//! \brief Tag to disable the DCD management (for serial ports only), set this tag to 0 to enable DCD management for USB port (option set to 1 by default). The DCD management doesn't work for COMU on iWL.
#define LL_PHYSICAL_T_DISABLE_DCD		8
//! \brief  Value length for the tag \ref LL_PHYSICAL_T_DISABLE_DCD.
#define LL_PHYSICAL_L_DISABLE_DCD		1

//! \brief Tag to enable the DCD monitoring (for serial ports only). The DCD monitoring doesn't work for COMU on iWL. Possible values are \ref LL_PHYSICAL_V_DCD_DISABLED or \ref LL_PHYSICAL_V_DCD_ENABLED.
#define LL_PHYSICAL_T_DCD_MONITORING    9
//! \brief  Value length for the tag \ref LL_PHYSICAL_T_DCD_MONITORING.
#define LL_PHYSICAL_L_DCD_MONITORING	1
//! \brief Disable DCD monitoring on a serial port (default value).
#define LL_PHYSICAL_V_DCD_DISABLED		0
//! \brief Enable DCD monitoring on a serial port.
#define LL_PHYSICAL_V_DCD_ENABLED		1


//-- GSM parameters -------------------------------------------------------

//! \defgroup LL_GSM_LINK_PARAMETERS	GSM link parameters
//! \ingroup LL_PHYSICAL_PARAMETERS
//! \brief Parameters to configure the GSM physical link.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


// GSM Protocol
//! \addtogroup LL_GSM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

/*! \brief Tag to specify the GSM mode (transparent or RLP)

	The RLP mode is the GSM embedded protocol for error correction. 
	It is often needed when the remote PSTN host requires the V42 protocol.

	\ref LL_GSM_MODE : list of values.
*/
#define LL_GSM_T_MODE				32 

//! \brief  Value length for the tag LL_GSM_T_MODE.
#define LL_GSM_L_MODE				1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_GSM_MODE	GSM modulation mode
//! \ingroup LL_GSM_LINK_PARAMETERS
//! \brief The possible values of LL_GSM_T_MODE tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Transparent mode (without error correction protocol).
#define LL_GSM_V_MODE_TRANSPARENT	0	

///! \brief RLP mode.
#define LL_GSM_V_MODE_RLP			1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \addtogroup LL_GSM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// GSM Modulation
/*! \brief Tag to specify the GSM modulation

	\ref LL_GSM_MODULATION : list of values.
*/
#define LL_GSM_T_MODULATION				33 

//! \brief  Value length for the tag LL_GSM_T_MODULATION.
#define LL_GSM_L_MODULATION				1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_GSM_MODULATION	Modulations supported by the internal GSM modem
//! \ingroup LL_GSM_LINK_PARAMETERS
//! \brief The possible values of LL_GSM_T_MODULATION tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------


//! \brief V22Bis - 2400 bauds.
#define LL_GSM_V_MODULATION_V22B_2400		4		
//! \brief V32 - 4800 bauds.
#define LL_GSM_V_MODULATION_V32_4800		6		
//! \brief V32 - 9600 bauds.
#define LL_GSM_V_MODULATION_V32_9600		7		
//! \brief V110 - 2400 bauds.
#define LL_GSM_V_MODULATION_V110_2400		68		
//! \brief V110 - 4800 bauds.
#define LL_GSM_V_MODULATION_V110_4800		70		
//! \brief V110 - 9600 bauds.
#define LL_GSM_V_MODULATION_V110_9600		71		

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup LL_GSM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Tag to specify the timeout connection for GSM communications.
//!
//! The value is a big-endian integer containing the timeout delay expressed in 10
//! milliseconds (ex : 6000 = 60 seconds). Set by default to 6000.
#define LL_GSM_T_CONNECTION_TIMEOUT		50

//! \brief  Value length for the tag LL_GSM_T_CONNECTION_TIMEOUT.
#define LL_GSM_L_CONNECTION_TIMEOUT		4

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \defgroup LL_TAILGATE_LINK_PARAMETERS	TAILGATE link parameters
//! \ingroup LL_PHYSICAL_PARAMETERS
//! \brief Parameters to configure the TAILGATE link.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \addtogroup LL_TAILGATE_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Tag to specify the TailGate channel.
#define LL_TAILGATE_T_CHANNEL			64

//! \brief Value length for the tag \ref LL_TAILGATE_T_CHANNEL.
#define LL_TAILGATE_L_CHANNEL		     1

//! \brief Tailgate channel 0 (default value for \ref LL_TAILGATE_T_CHANNEL). Only channel 0 is supported yet.
#define LL_TAILGATE_V_CHANNEL_0          0

//! \brief Tag to specify the TailGate address. Only addresses 0x64, 0x65, 0x68 and 0x69 are supported.
#define LL_TAILGATE_T_ADDRESS			65

//! \brief Maximum size for phone numbers.
#define LL_TAILGATE_L_ADDRESS		     1


// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//-- GPRS parameters -----------------------------------------------
//! \defgroup LL_GPRS_LINK_PARAMETERS	GPRS link parameters
//! \ingroup LL_PHYSICAL_PARAMETERS
//! \brief Parameters to configure the GPRS physical link.

//! The LinkLayer provides dedicated functions to configure the GPRS/3G link.
//! Please refer the functions : LL_GSM_Start(), LL_GPRS_Start() LL_GPRS_Connect().
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-- Modem parameters -----------------------------------------------

//! \defgroup LL_MODEM_LINK_PARAMETERS	Modem link parameters
//! \ingroup LL_PHYSICAL_PARAMETERS
//! \brief Parameters to configure the MODEM link.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup LL_MODEM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// Modem type
//! \brief Tag to specify the modem type.
//! \note Currently only PSTN modems are supported.
#define LL_MODEM_T_TYPE					      128

//! \brief  Value length for the tag LL_MODEM_T_TYPE.
#define LL_MODEM_L_TYPE					        1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_MODEM_TYPE	Modem types
//! \ingroup LL_MODEM_LINK_PARAMETERS
//! \brief The possible values of LL_MODEM_T_TYPE tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief PSTN modem (default value).
#define LL_MODEM_V_TYPE_STANDARD		        1	
//! \brief ISDN modem - channel B (not supported).
#define LL_MODEM_V_TYPE_ISDN_CHANNEL_B	        2	
//! \brief ISDN modem - channel D (not supported).
#define LL_MODEM_V_TYPE_ISDN_CHANNEL_D	        3	

//! @}

// Modem command terminator
//! \addtogroup LL_MODEM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
#define LL_MODEM_T_CMD_TERMINATOR		      129

//! \brief  Value length for the tag LL_MODEM_T_CMD_TERMINATOR.
#define LL_MODEM_L_CMD_TERMINATOR		        1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#define LL_MODEM_V_CMD_TERMINATOR_CR	        1
#define LL_MODEM_V_CMD_TERMINATOR_CRLF	        2

//! \addtogroup LL_MODEM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

/*! \brief Tag to specify the initialization string for internal modem.*/
#define LL_MODEM_T_INIT_STRING			      130

/*! \brief Tag to specify the initialization string for Conexant internal modem.*/
#define LL_MODEM_T_INIT_STRING_CONEXANT			      134

//! \brief  Value length for the tag LL_MODEM_T_INIT_STRING.
#define LL_MODEM_L_INIT_STRING_MAX		      128

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Phone number
//! \addtogroup LL_MODEM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

#define LL_MODEM_T_PHONE_NUMBER			      131

//! \brief Maximum size for phone numbers.
#define LL_MODEM_L_PHONE_NUMBER_MAX		       40

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup LL_MODEM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

#define LL_MODEM_T_DIAL_TIMEOUT			      132

//! \brief  Value length for the tag LL_MODEM_T_DIAL_TIMEOUT.
#define LL_MODEM_L_DIAL_TIMEOUT			        4

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#define LL_MODEM_V_DIAL_TIMEOUT_DEFAULT      6000     // 1 minute
#define LL_MODEM_V_DIAL_TIMEOUT_MIN           500     // 5 seconds

//! \addtogroup LL_MODEM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// Modem disconnection string
/*! \brief Tag to specify the disconnection type for modem communications.

	\ref LL_MODEM_DISCONNECTION_TYPE : list of values.
*/
#define LL_MODEM_T_DISCONNECTION_TYPE         133 

//! \brief  Value length for the tag LL_MODEM_T_DISCONNECTION_TYPE.
#define LL_MODEM_L_DISCONNECTION_TYPE           1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_MODEM_DISCONNECTION_TYPE	Modem disconnection types
//! \ingroup LL_MODEM_LINK_PARAMETERS
//! \brief The possible values of LL_MODEM_T_DISCONNECTION_TYPE tag.
//! \note The ATZ disconnection must be used when configuring a V29FC communication using the internal modem.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Normal disconnection (default value).
#define LL_MODEM_V_DISCONNECTION_TYPE_DEFAULT   0 
//! \brief Disconnection with reset of the modem configuration (ATZ command).
#define LL_MODEM_V_DISCONNECTION_TYPE_ATZ       1 

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \addtogroup LL_GSM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Tag to specify the phone number for GSM communications.
// GSM Phone number.
#define LL_GSM_T_PHONE_NUMBER			LL_MODEM_T_PHONE_NUMBER

//! \brief Maximum size for phone numbers.
#define LL_GSM_L_PHONE_NUMBER_MAX		LL_MODEM_L_PHONE_NUMBER_MAX

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//-- Data link parameters --------------------------------------------

//! \addtogroup LL_DATA_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

/*! \brief Tag to specify the data link protocol

	\ref LL_DATA_LINK_PROTOCOL : list of values.
*/
// Protocol
#define LL_DATA_LINK_T_PROTOCOL					1 

//! \brief  Value length for the tag LL_DATA_LINK_T_PROTOCOL.
#define LL_DATA_LINK_L_PROTOCOL					1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_DATA_LINK_PROTOCOL	Data link protocols
//! \ingroup LL_DATA_LINK_PARAMETERS
//! \brief The possible values of LL_DATA_LINK_T_PROTOCOL tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! \brief HDLC/SDLC protocol.
#define LL_DATA_LINK_V_HDLC						1	
//! \brief PPP protocol.
#define LL_DATA_LINK_V_PPP						2	
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-- HDLC parameters -------------------------------------------

//! \defgroup LL_HDLC_PARAMETERS	HDLC protocol parameters
//! \ingroup LL_DATA_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

// POS Address
//! \brief Tag to specify the HDLC address of the terminal.
#define LL_HDLC_T_ADDRESS						16

//! \brief  Value length for the tag LL_HDLC_T_ADDRESS.
#define LL_HDLC_L_ADDRESS						1

#define LL_HDLC_V_ADDRESS_ANY					0xff

//! \brief Tag to specif the maximum size for an HDLC frame.
#define LL_HDLC_T_FRAME_MAX_SIZE				17

//! \brief  Value length for the tag LL_HDLC_L_FRAME_MAX_SIZE.
//! \note For the Netbricks internal modem, the size of the HDLC frames is limited to 1950 bytes.
#define LL_HDLC_L_FRAME_MAX_SIZE				4

//! \brief Default size of HDLC frames.
#define LL_HDLC_V_FRAME_MAX_SIZE_DEFAULT		1024	

// Window size
//! \brief Tag to specify the HDLC window size.
#define LL_HDLC_T_WINDOW_SIZE					18

//! \brief  Value length for the tag LL_HDLC_L_WINDOW_SIZE.
#define LL_HDLC_L_WINDOW_SIZE					1

//! \brief Default size of the HDLC window.
#define LL_HDLC_V_WINDOW_SIZE_DEFAULT			8	

// Output buffer size
#define LL_HDLC_T_OUTPUT_BUFFER_SIZE			19

//! \brief  Value length for the tag LL_HDLC_T_OUTPUT_BUFFER_SIZE.
#define LL_HDLC_L_OUTPUT_BUFFER_SIZE			4

#define LL_HDLC_V_OUTPUT_BUFFER_SIZE_DEFAULT	(LL_HDLC_V_FRAME_MAX_SIZE_DEFAULT * LL_HDLC_V_WINDOW_SIZE_DEFAULT)

// Input buffer size
#define LL_HDLC_T_INPUT_BUFFER_SIZE				20

//! \brief  Value length for the tag LL_HDLC_T_INPUT_BUFFER_SIZE.
#define LL_HDLC_L_INPUT_BUFFER_SIZE				4

#define LL_HDLC_V_INPUT_BUFFER_SIZE_DEFAULT		(LL_HDLC_V_FRAME_MAX_SIZE_DEFAULT * LL_HDLC_V_WINDOW_SIZE_DEFAULT)

// Connection timeout
//! \brief Tag to specify the HDLC connection timeout.
#define LL_HDLC_T_CONNECT_TIMEOUT				21

//! \brief  Value length for the tag LL_HDLC_T_CONNECT_TIMEOUT.
#define LL_HDLC_L_CONNECT_TIMEOUT				4

//! \brief Default value for the HDLC connection timeout (10 seconds)
#define LL_HDLC_V_CONNECT_TIMEOUT_DEFAULT		1000	

// Minimum number of resend request before to resend
#define LL_HDLC_T_MIN_RESEND_REQUESTS			22

//! \brief  Value length for the tag LL_HDLC_T_MIN_RESEND_REQUESTS.
#define LL_HDLC_L_MIN_RESEND_REQUESTS			1

#define LL_HDLC_V_MIN_RESEND_REQUESTS_DEFAULT	1

// Synchronous V80 mode.
//! \brief Tag to activate the V80 mode.
#define LL_HDLC_T_V80_MODE						23

//! \brief  Value length for the tag LL_HDLC_T_V80_MODE.
#define LL_HDLC_L_V80_MODE						1

// Timeout for inactivity in HDLC
//! \brief Tag to specify the HDLC inactivity timeout.
#define LL_HDLC_T_INACTIVITY_TIMEOUT            24

//! \brief  Value length for the tag LL_HDLC_T_INACTIVITY_TIMEOUT.
#define LL_HDLC_L_INACTIVITY_TIMEOUT            4

//! \brief Default value (disable the HDLC inactivity timeout).
#define LL_HDLC_V_NO_INACTIVITY_TIMEOUT		    0	


//! \brief Tag to enable the fast connection mode
#define LL_HDLC_T_FAST_UA						25

//! \brief  Value length for the tag LL_HDLC_T_FAST_CONNECTION.
#define LL_HDLC_L_FAST_UA				1


//! \brief Tag to send a DISC before performing a disconnection.
#define LL_HDLC_T_SEND_DISC						26

//! \brief  Value length for the tag LL_HDLC_T_SEND_DISC.
#define LL_HDLC_L_SEND_DISC				1


// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-- GPRS/GSM parameters ---------------------------------------

//! \addtogroup LL_GSM_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Minimum size of a SIM pin code.
#define LL_GSM_L_PIN_CODE_MIN		4	

//! \brief Maximum size of a SIM pin code.
#define LL_GSM_L_PIN_CODE_MAX		8	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup LL_GPRS_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief Maximum size of an APN.
#define LL_GPRS_L_APN_MAX			128 
//! \brief Minimum size of a SIM pin code.
#define LL_GPRS_L_PIN_CODE_MIN		LL_GSM_L_PIN_CODE_MIN	
//! \brief Maximum size of a SIM pin code.
#define LL_GPRS_L_PIN_CODE_MAX		LL_GSM_L_PIN_CODE_MAX	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//-- PPP parameters --------------------------------------------


//! \defgroup LL_PPP_PARAMETERS	PPP protocol parameters
//! \ingroup LL_DATA_LINK_PARAMETERS
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------


// Login
//! \brief Tag to specify the PPP login
#define LL_PPP_T_LOGIN							32

//! \brief Maximum size for PPP login
#define LL_PPP_L_LOGIN_MAX						128

// Password
//! \brief Tag to specify the PPP password.
#define LL_PPP_T_PASSWORD						33

//! \brief Maximum size for PPP password
#define LL_PPP_L_PASSWORD_MAX					128

// Microsoft RAS PPP server mode
//! \brief Tag to specify that the PPP server uses Microsoft PPP RAS implementation.
//! In that case, the client must send "CLIENT" and receive "CLIENTSERVER" before initiating
//! the 'real' PPP negociation. The value must be set to 1 to activate this mode.
//! An example of code is given  : \ref LL_SAMPLE_PPP_CONNECTION.
#define LL_PPP_T_RAS_SERVER_MODE					34

//! \brief Size for PPP RAS server mode tag.
#define LL_PPP_L_RAS_SERVER_MODE					1

// Microsoft RAS PPP server mode timeout
//! \brief Tag to specify the time to wait for the "CLIENTSERVER" pattern in Microsoft RAS PPP server mode.
#define LL_PPP_T_RAS_SERVER_TIMEOUT				35

//! \brief Size for PPP RAS server mode timeout.
#define LL_PPP_L_RAS_SERVER_TIMEOUT				4

//! \brief Default maximum value (10 seconds) to wait for the reception of "CLIENTSERVER" pattern.
#define LL_PPP_V_RAS_SERVER_TIMEOUT_DEFAULT		1000

// Set the PPP handle
//! \brief Tag to specify the PPP handle to be used in a PPP connection.
//! In that case the PPP handle is created (PPP_Open) and destroyed (PPP_Close) by the application.
//! An example of code is given  : \ref LL_SAMPLE_PPP_CONNECTION.
#define LL_PPP_T_PPP_HANDLE						36

//! \brief Size of the PPP handle.
#define LL_PPP_L_PPP_HANDLE						4

//! \brief Tag to specify the delay to wait before closing the PPP link at disconnection time (in 10th of seconds).
#define LL_PPP_T_TERMINATION_DELAY                  37

//! \brief Size of the the tag \ref LL_PPP_T_TERMINATION_DELAY.
#define LL_PPP_L_TERMINATION_DELAY                  4

//! \brief Default value for the delay \ref LL_PPP_T_TERMINATION_DELAY. Do not wait.
#define LL_PPP_V_TERMINATION_DELAY_DEFAULT          0

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-- Transport parameters --------------------------------------

// Protocol

//! \brief Tag to specify the transport protocol.
#define LL_TRANSPORT_T_PROTOCOL					1

//! \brief  Value length for the tag LL_TRANSPORT_T_PROTOCOL.
#define LL_TRANSPORT_L_PROTOCOL					1

//! \brief TCP/IP protocol.
#define LL_TRANSPORT_V_TCPIP					1 

//! \brief UDP protocol.
#define LL_TRANSPORT_V_UDP                      2

//-- TCP/IP Parameters -----------------------------------------

//! \defgroup LL_TCPIP_PARAMETERS	TCP/IP protocol parameters
//! \ingroup LL_TRANSPORT_PARAMETERS
//! \brief Parameters to configure a TCP/IP communication.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------


// Host address

//! \brief TCP/IP address of the remote host.
//!
//! The value is a string containing either an IP address or a DNS name. 
//! It must be NULL terminated (use TlvTree_AddChildString to add this parameter).
#define LL_TCPIP_T_HOST_NAME					16	
#define LL_TCPIP_L_HOST_NAME_MAX				256


// Maximum TCP segment size

//! \brief Maximum TCP segment size
//!
//! The value is a positive integer.
//! If set to 0 it will be ignored and default segment size will apply.
#define LL_TCPIP_T_MAX_SEG_SIZE					31
#define LL_TCPIP_L_MAX_SEG_SIZE					4

// IP port
//! \brief Tag to specify the TCP/IP port.
//!
//! The value is coded in big endian and contains the TCP port to use.
#define LL_TCPIP_T_PORT							17

//! \brief  Value length for the tag LL_TCPIP_T_PORT.
#define LL_TCPIP_L_PORT							4

// Connection timeout
//! \brief Tag to specify the timeout on the TCP/IP connection (or a complete SSL connection (TCP+SSL)) (in 10ms).
//!
//! The value is coded in big endian and contains the timeout on the TCP connection.
//! Set to 0 by default (wait until connection is finished or failed).
//! When using the physical layer LL_PHYSICAL_V_TCP_AIAP the default value is \ref LL_TCPIP_V_AIAP_CONNECT_TIMEOUT_DEFAULT.
#define LL_TCPIP_T_CONNECT_TIMEOUT				18

//! \brief  Value length for the tag LL_TCPIP_T_CONNECT_TIMEOUT.
#define LL_TCPIP_L_CONNECT_TIMEOUT				4

//! \brief Default time out value for TCP AIAP connection.
#define LL_TCPIP_V_AIAP_CONNECT_TIMEOUT_DEFAULT          8000

// TCP Connection timeout part of a SSL connection
//! \brief Tag to specify the timeout on the TCP/IP connection when LinkLayer configured in SSL (in 10ms).
//!
//! The value is coded in big endian and contains the timeout on the TCP connection part of a SSL connection.
//! Set to 0 by default (wait until connection is finished or failed).
#define LL_TCPIP_T_SSL_TCP_CONNECT_TIMEOUT				28

//! \brief Former definition of \ref LL_TCPIP_T_SSL_TCP_CONNECT_TIMEOUT. Do not use anymore.
#define LL_TCPIP_T_SSL_TCP_CONNECT_TIMEOUT_DEPRECATED	19

//! \brief  Value length for the tag LL_TCPIP_T_SSL_TCP_CONNECT_TIMEOUT.
#define LL_TCPIP_L_SSL_TCP_CONNECT_TIMEOUT				4

// SSL Profile
//! \brief Tag to specify the SSL profile name.
//!
//! The value is a string containing the profile name. 
//! It must be NULL terminated (use TlvTree_AddChildString to add this parameter).
//! \note 
//! - The SSL profile must be created using SSL dedicated interface (see add-on TCP/IP
//! documentation [SMO-SFO-0044_D_PackSSL_ReferenceManual]).
//! - To perform SSL connections, SSL DLL must be loaded in the terminal and the SSL profile
//! specified in the configuration tag must be created. Otherwise the configuration or the connection
//! fails with the errors : LL_ERROR_DLL or LL_ERROR_SSL_PROFILE.
#define LL_TCPIP_T_SSL_PROFILE					26
//! \brief Max length for the tag LL_TCPIP_T_SSL_PROFILE.
#define LL_TCPIP_L_SSL_PROFILE_MAX				11

//! \brief Tag to set an error when a SSL read operation returns 0.
#define LL_TCPIP_T_SSL_ERROR_ON_READ_ZERO       27
//! \brief Length for the tag LL_TCPIP_T_SSL_ERROR_ON_READ_ZERO.
#define LL_TCPIP_L_SSL_ERROR_ON_READ_ZERO        1

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//-- Transport Protocol Interface Parameters -------------------
// Global link (for future adds)
/*! \brief Tag to specify an interface protocol.

	\ref LL_TRANSPORT_INTERFACE_PROTOCOL : list of values.
*/
#define LL_TRANSPORT_T_INTERFACE_PROTOCOL		19 

//! \brief  Value length for the tag LL_TRANSPORT_T_INTERFACE_PROTOCOL.
#define LL_TRANSPORT_L_INTERFACE_PROTOCOL		1


//! \defgroup LL_TRANSPORT_INTERFACE_PROTOCOL	Transport interface protocols
//! \ingroup LL_TRANSPORT_PARAMETERS
//! \brief The possible values of LL_TRANSPORT_T_INTERFACE_PROTOCOL tag.
//!
//! The transport interface protocols RFC1086 and CONCERT are used (mainly in France) to
//! access X25 servers through IP/X25 gateways (as done by the X28 protocol to communicate
//! with a PAD ; which is a PSTN/X25 gateway).
//! These protocols use the X28 parameters : 
//! - LL_X28_T_SERVER_ID_STRING : the host name to reach : (X25 address),
//! - LL_X28_T_ADDITIONAL_DATA_STRING : the additional data to send during the connection to the server.
//!
//! An example of code is given  : \ref LL_SAMPLE_CONCERT_SSL.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief X28 protocol (for X25 gateways).
#define LL_TRANSPORT_V_INTERFACE_PROTOCOL_X28		1	
//! \brief RFC1086 protocol (for IP/X25 gateways).
#define LL_TRANSPORT_V_INTERFACE_PROTOCOL_RFC1086	2	
//! \brief Concert protocol (modified RFC1086 - for IP/X25 gateways).
#define LL_TRANSPORT_V_INTERFACE_PROTOCOL_CONCERT	3	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-- Interface protocol parameters -----------------------------

//! \defgroup LL_X28_PARAMETERS	X28 protocol parameters
//! \ingroup LL_TRANSPORT_PARAMETERS
//! \brief Parameters to configure an X28 communication.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


// Global X25 parameters

//! \addtogroup LL_X28_PARAMETERS
//! @{

// Server ID to reach
#define LL_X25_T_SERVER_ID_STRING				21
#define LL_X25_L_SERVER_ID_STRING_MAX			16

// Additionnal Data
#define LL_X25_T_ADDITIONAL_DATA_STRING			25
#define LL_X25_L_ADDITIONAL_DATA_STRING_MAX		15




// X28 protocol parameters.

// X28 Mode (EBAM/EMA)
//! \brief Tag to specify the X28 protocol mode.
#define LL_X28_T_MODE							20

//! \brief  Value length for the tag LL_X28_T_MODE.
#define LL_X28_L_MODE							1

//! @}

//! \defgroup LL_X28_MODE	X28 protocol modes
//! \ingroup LL_X28_PARAMETERS
//! \brief The possible values of LL_X28_T_MODE tag.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief EBAM mode (default value).
#define LL_X28_V_MODE_EBAM						1	
//! \brief EMA mode. Do not used ; it requires a modified V42 (not currenlty supported by the LinkLayer).
#define LL_X28_V_MODE_EMA						2	

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \addtogroup LL_X28_PARAMETERS
//! @{

// X28 Server ID to reach
//! \brief The host name to reach (X25 address).
//! The value is a string containing the name of the server to reach. It must be NULL
//! terminated (use TlvTree_AddChildString to add this parameter).
#define LL_X28_T_SERVER_ID_STRING				LL_X25_T_SERVER_ID_STRING
#define LL_X28_L_SERVER_ID_STRING_MAX			LL_X25_L_SERVER_ID_STRING_MAX

// X28 Banner
//! \brief The string (or a part of the string) sent by the PAD as network identification.
//! The value is a string containing the name the network identification. It must be NULL
//! terminated (use TlvTree_AddChildString to add this parameter). If this string is {0x0D,
//! 0x0A} (default value), connection is allowed whatever the network identification.
//! Otherwise connection is only allowed once the network identification is compliant.
//! Common strings are "TRANSPAC" for France, or "SATIM" for Algeria.
#define LL_X28_T_PROMPT_STRING					22
#define LL_X28_L_PROMPT_STRING_MAX				20

//! \brief Maximum duration allowed for network identification (in 1/100 s).
#define LL_X28_T_PROMPT_TIMEOUT					23

//! \brief  Value length for the tag LL_X28_T_PROMPT_TIMEOUT.
#define LL_X28_L_PROMPT_TIMEOUT					2

// X28 PAD Configuration
//! \brief The string to configure the PAD (EBAM only).
//! The value is a string sent to the configure the PAD. By default this string is:
//! "SET 1:0, 2:0, 3:0, 4:2, 5:0" + {0x0D, 0x00}.
#define LL_X28_T_PAD_PROFILE_STRING				24
#define LL_X28_L_PAD_PROFILE_STRING_MAX			80

// X28 Additionnal Data
//! \brief Additional data to send during server connection
#define LL_X28_T_ADDITIONAL_DATA_STRING			LL_X25_T_ADDITIONAL_DATA_STRING
#define LL_X28_L_ADDITIONAL_DATA_STRING_MAX		LL_X25_L_ADDITIONAL_DATA_STRING_MAX

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


// RFC 1086/Concert protocol parameters
//! \defgroup LL_RFC1086_PARAMETERS	RFC1086 protocol parameters
//! \ingroup LL_TRANSPORT_PARAMETERS
//! \brief Parameters to configure an RFC1086 communication.
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
#define LL_RFC1086_T_INTERNAL_BUFFER_SIZE			30
#define LL_RFC1086_L_INTERNAL_BUFFER_SIZE			2
#define LL_RFC1086_V_INTERNAL_BUFFER_SIZE_DEFAULT	(1024+4)
#define LL_RFC1086_V_INTERNAL_BUFFER_SIZE_MIN		260
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_CONCERT_PARAMETERS	Concert protocol parameters
//! \ingroup LL_TRANSPORT_PARAMETERS
//! \brief Parameters to configure an Concert communication.
//! @{
#define LL_CONCERT_T_INTERNAL_BUFFER_SIZE			LL_RFC1086_T_INTERNAL_BUFFER_SIZE
#define LL_CONCERT_L_INTERNAL_BUFFER_SIZE			LL_RFC1086_L_INTERNAL_BUFFER_SIZE

#define LL_CONCERT_V_INTERNAL_BUFFER_SIZE_DEFAULT	LL_RFC1086_V_INTERNAL_BUFFER_SIZE_DEFAULT
#define LL_CONCERT_V_INTERNAL_BUFFER_SIZE_MIN		LL_RFC1086_V_INTERNAL_BUFFER_SIZE_MIN

// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//-- Status --------------------------------------------------------------------------
//! \addtogroup LINK_LAYER
//! @{

//! \cond __EXCLUDE__
#define LL_STATUS_MASK						0xff000000
#define LL_STATUS_LAYER_MASK				0x00ffff00
#define LL_STATUS_LAYER_STATE_MASK			0x000000ff
//! \endcond

//! @}


//! \defgroup LL_STATUS	Communication status
//! \ingroup LINK_LAYER
//! \brief Communication status
//!
//! The LinkLayer provides the function : LL_GetStatus() to know the current status of a communication.
//! @{

//! @}

//! \defgroup LL_STATUS_STATE	Status state
//! \ingroup LL_STATUS
//! \brief Status state
//!
//! Field in the status indicating the state of the connection (disconnected, connecting, connected...).
//! @{

//! \brief Status for a disconnected communication.
#define LL_STATUS_DISCONNECTED				0x01000000	

//! \brief Status for a communication performing a connection.
#define LL_STATUS_CONNECTING				0x02000000

//! \brief Status for a connected communication.
#define LL_STATUS_CONNECTED					0x03000000

//! \brief Status for a communication performing a disconnection.
#define LL_STATUS_DISCONNECTING				0x04000000

//! \brief
#define LL_STATUS_PHYSICAL_DISCONNECTION	0x05000000
//! @}


// Modem status
//! \defgroup LL_PHYSICAL_STATUS	Status for the serial/USB ports
//! \ingroup LL_STATUS
//! \brief Status for the serial/USB ports.
//! @{
#define LL_STATUS_LAYER_PHYSICAL			(0x00000100)
#define LL_STATUS_INITIALISING_MODEM		(LL_STATUS_CONNECTING | LL_STATUS_LAYER_PHYSICAL | 1)
#define LL_STATUS_DIALING					(LL_STATUS_CONNECTING | LL_STATUS_LAYER_PHYSICAL | 2)

#define LL_STATUS_PERIPHERAL_AVAILABLE      (LL_STATUS_CONNECTED    | LL_STATUS_LAYER_PHYSICAL | 1)
#define LL_STATUS_PERIPHERAL_BUSY           (LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_PHYSICAL | 1)
//! \brief The peripheral can't be used since the terminal is not on its cradle (can be obtained with \ref LL_PHYSICAL_V_USB_BASE, \ref LL_PHYSICAL_V_USB_BASE_HOST_1 or \ref LL_PHYSICAL_V_USB_BASE_HOST_2 link ).
#define LL_STATUS_PERIPHERAL_OUT_OF_BASE    (LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_PHYSICAL | 2)
//! @}

// USB/RS232 converter status
//! \defgroup LL_USB_CONVERTER_STATUS	Status for the USB/serial converters
//! \ingroup LL_STATUS
//! \brief Status for the USB/serial converters.
//! @{
#define LL_STATUS_CONVERTER_AVAILABLE    	LL_STATUS_PERIPHERAL_AVAILABLE
#define LL_STATUS_CONVERTER_NOT_PLUGGED		(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_PHYSICAL | 3)
//! @}

// HDLC status
//! \defgroup LL_HDLC_STATUS	Status for the HDLC communication
//! \ingroup LL_STATUS
//! \brief Status for the HDLC communication.
//! @{
#define LL_STATUS_LAYER_HDLC				(0x00000200)
#define LL_STATUS_SNRM_REQUESTED			(LL_STATUS_CONNECTING | LL_STATUS_LAYER_HDLC | 1)
//! @}

// PPP status
//! \defgroup LL_PPP_STATUS	Status for the PPP communication
//! \ingroup LL_STATUS
//! \brief Status for the PPP communications.
//! @{
#define LL_STATUS_LAYER_PPP					(0x00000300)
#define LL_STATUS_PPP_CONNECTING			(LL_STATUS_CONNECTING | LL_STATUS_LAYER_PPP | 1)
#define LL_STATUS_PPP_AUTHENTICATING		(LL_STATUS_CONNECTING | LL_STATUS_LAYER_PPP | 2)
//! @}

// TCP/IP status
//! \defgroup LL_TCP_STATUS	Status for the TCP communication
//! \ingroup LL_STATUS
//! \brief Status for the TCP communications.
//! @{
#define LL_STATUS_LAYER_TCPIP				(0x00000400)
#define LL_STATUS_TCPIP_RESOLVING_NAME		(LL_STATUS_CONNECTING | LL_STATUS_LAYER_TCPIP | 1)
#define LL_STATUS_TCPIP_CONNECTING			(LL_STATUS_CONNECTING | LL_STATUS_LAYER_TCPIP | 2)
//! @}

// GPRS status
//! \defgroup LL_GPRS_STATUS	GPRS Status
//! \ingroup LL_STATUS
//! \brief Status for the GPRS/3G physical layer.
//! @{
#define LL_STATUS_LAYER_GPRS				(0x00000500)

//! \brief 
#define LL_STATUS_GPRS_DISCONNECTED			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS )
//! \brief No SIM card is inserted in the terminal.
#define LL_STATUS_GPRS_ERROR_NO_SIM			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 1)
//! \brief The SIM card is lock.
#define LL_STATUS_GPRS_ERROR_SIM_LOCK		(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 2)
//! \brief The PIN code of the SIM is not valid.
#define LL_STATUS_GPRS_ERROR_BAD_PIN		(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 3)
//! \brief The PIN code of the SIM card is required.
#define LL_STATUS_GPRS_ERROR_NO_PIN			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 4)
//! \brief The GPRS/3G network is connected but an error occured during the PPP link establishment.
#define LL_STATUS_GPRS_ERROR_PPP			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 5)
//! \brief Loss of the GPRS radio coverage.
#define LL_STATUS_GPRS_ERROR_NO_SIGNAL   	(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 6)
//! \brief GPRS status unknown. This error code is deprecated and only kept for compatibility.
#define LL_STATUS_GPRS_ERROR_UNKNOWN		(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GPRS | 6)

//! \brief The connection to the GPRS/3G network is in progress.
#define LL_STATUS_GPRS_CONNECTING			(LL_STATUS_CONNECTING | LL_STATUS_LAYER_GPRS | 1 )
//! \brief The GPRS/3G network is available.
#define LL_STATUS_GPRS_AVAILABLE			(LL_STATUS_CONNECTING | LL_STATUS_LAYER_GPRS | 2 )
//! \brief The PPP connection with the GPRS/3G provider is currently in progress.
#define LL_STATUS_GPRS_CONNECTING_PPP		(LL_STATUS_CONNECTING | LL_STATUS_LAYER_GPRS | 3 )

//! \brief The GPRS/3G is connected and ready to perform a TCP/IP communication.
#define LL_STATUS_GPRS_CONNECTED			(LL_STATUS_CONNECTED | LL_STATUS_LAYER_GPRS )
//! @}

// GSM status
//! \defgroup LL_GSM_STATUS	GSM Status
//! \ingroup LL_STATUS
//! \brief Status for the GSM physical layer.
//! @{

#define LL_STATUS_LAYER_GSM					(0x00000600)

//! \brief The GSM network is disconnecting.
#define LL_STATUS_GSM_DISCONNECTED			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GSM )
//! \brief NO SIM card is inserted in the terminal.
#define LL_STATUS_GSM_ERROR_NO_SIM			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GSM | 1)
//! \brief The SIM card is lock.
#define LL_STATUS_GSM_ERROR_SIM_LOCK		(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GSM | 2)
//! \brief The PIN code of the SIM card is invalid.
#define LL_STATUS_GSM_ERROR_BAD_PIN			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GSM | 3)
//! \brief The PIN code of the SIM card is required.
#define LL_STATUS_GSM_ERROR_NO_PIN			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GSM | 4)
//! \brief
#define LL_STATUS_GSM_ERROR_UNKNOWN			(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_GSM | 5)

//! \brief The connection to the GSM is currently in progress.
#define LL_STATUS_GSM_CONNECTING			(LL_STATUS_CONNECTING | LL_STATUS_LAYER_GSM  )

//! \brief The GSM network is connected and ready to perform a communication.
#define LL_STATUS_GSM_CONNECTED				(LL_STATUS_CONNECTED  | LL_STATUS_LAYER_GSM | 1)
//! \brief
#define LL_STATUS_GSM_CALL_IN_PROGRESS		(LL_STATUS_CONNECTED  | LL_STATUS_LAYER_GSM | 2)
//! \brief
#define LL_STATUS_GSM_BUSY					(LL_STATUS_CONNECTED  | LL_STATUS_LAYER_GSM | 3)

//! @}

// Ethernet status
//! \defgroup LL_ETHERNET_STATUS	Ethernet Status
//! \ingroup LL_STATUS
//! \brief Status for the Ethernet physical layer
//! @{
#define LL_STATUS_LAYER_ETHERNET			(0x00000700)

//! \brief The Ethernet link is available and ready to perform a communication.
#define LL_STATUS_ETHERNET_AVAILABLE    	(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_ETHERNET | 1)

//! \brief No default route is configured for Ethernet.
#define LL_STATUS_ETHERNET_NO_DEFAULT_ROUTE	(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_ETHERNET | 2)
//! \brief The Ethernet cable is not plugged to the terminal.
#define LL_STATUS_ETHERNET_NOT_PLUGGED		(LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_ETHERNET | 3)
//! \brief The link between the Ethernet base and the terminal is not ready yet.
#define LL_STATUS_ETHERNET_BASE_NOT_READY   (LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_ETHERNET | 4)
//! \brief An Ethernet link is available through a base, but the terminal needs to be on its cradle to use it.
#define LL_STATUS_ETHERNET_OUT_OF_BASE      (LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_ETHERNET | 5)

//! @}

// Wifi status
//! \defgroup LL_WIFI_STATUS	Wifi Status
//! \ingroup LL_STATUS
//! \brief Status for the Wifi physical layer
//! @{
#define LL_STATUS_LAYER_WIFI                (0x00000800)

//! \brief The terminal is connected to a Wifi access point.
#define LL_STATUS_WIFI_CONNECTED            (LL_STATUS_CONNECTED    | LL_STATUS_LAYER_WIFI | 1)
//! \brief The terminal is not connected to a Wifi access point.
#define LL_STATUS_WIFI_NOT_CONNECTED        (LL_STATUS_DISCONNECTED | LL_STATUS_LAYER_WIFI | 1)

//! @}

// Bluetooth status
//! \defgroup LL_BT_STATUS	Bluetooth Status
//! \ingroup LL_STATUS
//! \brief Status for the Bluetooth terminal.
//! \note Bluetooth status can be obtained by setting the physical network tag to the value
// corresponding to the peripheral to be used on the base.
//! @{

#define LL_BT_STATUS							(0x00000900)

//! \brief No base is associated with the terminal.
#define LL_BT_STATUS_NO_BASE_ASSOCIATED			(LL_STATUS_DISCONNECTED | LL_BT_STATUS | 1 )

//! \brief The associated base does not have the specified communication interface.
#define LL_BT_STATUS_PERIPHERAL_NOT_AVAILABLE	(LL_STATUS_DISCONNECTED | LL_BT_STATUS | 2 )
//! \brief The specified interface of the base is already used.
#define LL_BT_STATUS_PERIPHERAL_BUSY			(LL_STATUS_DISCONNECTED | LL_BT_STATUS | 3 )

//! \brief The specified base is not available.
#define LL_BT_STATUS_BASE_NOT_AVAILABLE			(LL_STATUS_DISCONNECTED | LL_BT_STATUS | 4 )

//! \brief The terminal is connected to a BlueTooth base.
#define LL_BT_STATUS_CONNECTED					(LL_STATUS_CONNECTED    | LL_BT_STATUS )

//! @}


//-- Errors ----------------------------------------------------------

//! \defgroup LL_ERRORS	 Error list
//! \ingroup LINK_LAYER
//! \brief Error list.
//! @{

//! @}

// Common errors

//! \defgroup LL_GENERIC_ERRORS	 Generic errors
//! \ingroup LL_ERRORS
//! \brief Generic error list.
//! @{

//! \brief OK. The operation has been successfully processed.
#define LL_ERROR_OK								0

//! \brief Negative value (-1000) starting the range for the generic errors.
#define LL_ERRORS								-1000	

//! \brief Error in resource allocation. Refer the diagnostic ticket for more information.
#define LL_ERROR_INTERNAL_RESOURCE              (LL_ERRORS - 0)

//! \brief
#define LL_ERROR_UNKNOWN_CONFIG					(LL_ERRORS - 1)

//! \brief The specified handle is not valid.
#define LL_ERROR_INVALID_HANDLE					(LL_ERRORS - 2)

//! \brief 
#define LL_ERROR_SERVICE_NOT_SUPPORTED			(LL_ERRORS - 3)

//! \brief A timeout period has expired.
#define LL_ERROR_TIMEOUT						(LL_ERRORS - 4)

//! \brief 
#define LL_ERROR_INVALID_PARAMETER				(LL_ERRORS - 5)

//! \brief The communication is not connected.
//! This error is mainly returned when trying to call \ref LL_Send(), \ref LL_Receive()
//! on a communication handle which is not connected (call to \ref LL_Connect() failed or the link has been disconnected by the server).
#define LL_ERROR_NOT_CONNECTED					(LL_ERRORS - 6)

//! \brief You can not modify or delete a configuration that is in use. Disconnect it first.
#define LL_ERROR_ALREADY_CONNECTED				(LL_ERRORS - 7)
//! \brief  The communication is disconnected due to a protocol or physical error 
//! (host hanged up, ...). The only allowed operation is LL_Disconnect().
#define LL_ERROR_DISCONNECTED					(LL_ERRORS - 8)

//! \brief 
#define LL_ERROR_BUSY							(LL_ERRORS - 9)

//! \brief 
#define LL_ERROR_SERVICE_FORBIDDEN				(LL_ERRORS - 10)

//! \brief 
#define LL_ERROR_NOT_READY						(LL_ERRORS - 11)

//! \brief The physical network (GSM, GPRS...) is not ready to perform the requested
// operation To know the reason of this error, please use the function "LL_Network_GetStatus".
#define LL_ERROR_NETWORK_NOT_READY				(LL_ERRORS - 12)

//! \brief The requested physical network is not supported by the terminal.
#define LL_ERROR_NETWORK_NOT_SUPPORTED			(LL_ERRORS - 13)

//! \brief Only returned by \ref LL_GPRS_Connect(). The connection on the GPRS/3G network is already OK. 
#define LL_ERROR_NETWORK_ALREADY_CONNECTED		(LL_ERRORS - 14)

//! \brief Network error (such as Ethernet cable not plugged, default route not configured...).
//! Use \ref LL_Network_GetStatus() to retrieve details on the error.
#define LL_ERROR_NETWORK_ERROR					(LL_ERRORS - 15)

//! \brief An external DLL (SSL, Tailgate or TCP_ISMP) is not loaded in the terminal.
#define LL_ERROR_DLL							(LL_ERRORS - 16)

//! \brief Internal error. The interface object size is too short.
#define LL_ERROR_OUTPUT_BUFFER_TOO_SHORT		(LL_ERRORS - 17)

//! \brief  Error calling the service. Please check that the LinkLayer component is loaded in the terminal
#define LL_ERROR_SERVICE_CALL_FAILURE           (LL_ERRORS - 18)

//! \brief The configuration requires the TCP/IP version of LinkLayer component.
#define LL_ERROR_IP_VERSION_REQUIRED            (LL_ERRORS - 19)

//! \brief Unexpected error. Refer the diagnostic ticket for more information.
//!	\note Deprecated [kept for compatibility]
#define LL_ERROR_UNKNOWN    LL_ERROR_INTERNAL_RESOURCE  // Deprecated - Kept for compatibility

//! @}


//! \defgroup LL_SESSION_ERRORS	 Session errors
//! \ingroup LL_ERRORS
//! \brief Session error list.
//! @{

// Session errors

//! \brief Negative value (-1100) starting the range for the session errors.
#define LL_SESSION_ERROR						(LL_ERRORS - 100)

//! \brief Invalid session stack. It contains too many protocols.
#define LL_SESSION_ERROR_TOO_MANY_PROTOCOLS		(LL_SESSION_ERROR - 0)

//! \brief Invalid session stack. It contains an unknown protocol.
#define LL_SESSION_ERROR_UNKNOWN_PROTOCOL		(LL_SESSION_ERROR - 1)

//! @}

//! \defgroup LL_PHYSICAL_ERRORS	 Physical link errors
//! \ingroup LL_ERRORS
//! \brief Physical link error list.
//! @{

// Physical layer errors
//! \brief Negative value (-1200) starting the range for the physical link errors.
#define LL_PHYSICAL_ERROR						(LL_ERRORS - 200)

//! \brief Overrun buffer error.
#define LL_ERROR_PHYSICAL_OVERRUN_BUFFER		(LL_PHYSICAL_ERROR - 0)
//! \brief Overrun error (the stop bit is missing).
#define LL_ERROR_PHYSICAL_OVERRUN				(LL_PHYSICAL_ERROR - 1)
//! \brief Framing error.
#define LL_ERROR_PHYSICAL_FRAMING				(LL_PHYSICAL_ERROR - 2)
//! \brief Parity error.
#define LL_ERROR_PHYSICAL_PARITY				(LL_PHYSICAL_ERROR - 3)

//! @}

// Modem layer errors
//! \defgroup LL_MODEM_ERRORS	 Modem errors
//! \ingroup LL_ERRORS
//! \brief Modem error list.
//! @{

//! \brief Negative value (-1300) starting the range for the modem errors.
#define LL_MODEM_ERROR							(LL_ERRORS - 300)

//! \brief Overrun error of the sending buffer.
#define LL_MODEM_ERROR_SEND_BUFFER_OVERRUN		(LL_MODEM_ERROR - 0)

//! \cond __EXCLUDE__
#define LL_MODEM_ERROR_INIT_MODEM				(LL_MODEM_ERROR - 1)
//! \endcond

//! \brief The modem has returned an error.
#define LL_MODEM_ERROR_RESPONSE_ERROR			(LL_MODEM_ERROR - 2)

//! \brief The dialed number is blacklisted.
#define LL_MODEM_ERROR_RESPONSE_BLACKLISTED		(LL_MODEM_ERROR - 3)

//! \brief The modem has returned the DELAYED error.
#define LL_MODEM_ERROR_RESPONSE_DELAYED			(LL_MODEM_ERROR - 4)

//! \brief No dialtone error.
#define LL_MODEM_ERROR_RESPONSE_NO_DIALTONE		(LL_MODEM_ERROR - 5)

//! \brief The PSTN line is busy.
#define LL_MODEM_ERROR_RESPONSE_BUSY			(LL_MODEM_ERROR - 6)

//! \brief No anwser from the remote part.
#define LL_MODEM_ERROR_RESPONSE_NO_ANSWER		(LL_MODEM_ERROR - 7)

//! \brief The communication has failed upon reception of NO CARRIER.
#define LL_MODEM_ERROR_RESPONSE_NO_CARRIER		(LL_MODEM_ERROR - 8)

//! \brief The modem has returned an unexpected answser 
//! (e.g not supported by the LinkLayer).
#define LL_MODEM_ERROR_RESPONSE_INVALID			(LL_MODEM_ERROR - 9)

//! @}

// HDLC layer errors
//! \defgroup LL_HDLC_ERRORS	 HDLC errors
//! \ingroup LL_ERRORS
//! \brief HDLC error list.
//! @{

//! \brief Negative value (-1400) starting the range for the HDLC errors.
#define LL_HDLC_ERROR							(LL_ERRORS - 400)

//! \brief The timeout of the HDLC connection has expired.
#define LL_HDLC_ERROR_CONNECT_TIMEOUT			(LL_HDLC_ERROR - 0)

//! @}

// PPP layer errors
//! \defgroup LL_PPP_ERRORS	 PPP errors
//! \ingroup LL_ERRORS
//! \brief PPP error list.
//! @{

//! \brief Negative value (-1500) starting the range for the PPP errors.
#define LL_PPP_ERROR							(LL_ERRORS - 500)

//! \brief PPP connection error. Connection with the PPP provider failed (problem when negociating PPP options...).
#define LL_ERROR_PPP_CONNECT					(LL_PPP_ERROR - 0)

//! \brief PPP authentication error. The login and the password are not valid.
#define LL_ERROR_PPP_AUTHENTICATION				(LL_PPP_ERROR - 1)

//! \brief PPP connection error during the exchange "CLIENT" <-> "CLIENTSERVER"
#define LL_ERROR_PPP_RAS_MODE					(LL_PPP_ERROR - 2)

//! @}


// TCP/IP layer errors
//! \defgroup LL_TCP_ERRORS	 TCP/IP errors
//! \ingroup LL_ERRORS
//! \brief TCP/IP error list.
//! @{

//! \brief Negative value (-1600) starting the range for the TCP/IP errors.
#define LL_TCPIP_ERROR							(LL_ERRORS - 600)

//! \brief Unable to resolve the DNS name.
#define LL_ERROR_UNKNOWN_HOST					(LL_TCPIP_ERROR - 0)

//! \brief Error during the socket creation. Can be observed when too many sockets are used at the same time.
#define LL_ERROR_CREATE_SOCKET					(LL_TCPIP_ERROR - 1)

//! \brief Error during the socket connection. Either the remote server is not responding, or settings problems
//! (configuration parameters, wrong certificate in SSL...).
#define LL_ERROR_CANNOT_CONNECT					(LL_TCPIP_ERROR - 2)

//! \brief The connection is refused by the remote server.
//! In TCP, the 'errno' value of the socket is \ref __ECONNREFUSED.
//! In SSL, this can be caused by a failure during the SSL handshake.
#define LL_ERROR_CONNECTION_REFUSED				(LL_TCPIP_ERROR - 3)

//! \brief The host is unreachable. Cannot access the server.
//! The 'errno' value of the socket is \ref __EHOSTUNREACH.
#define LL_ERROR_HOST_UNREACHABLE				(LL_TCPIP_ERROR - 4)

//! \brief The network is unreachable. Cannot access the server.
//! The 'errno' value of the socket is \ref __ENETUNREACH.
#define LL_ERROR_NETWORK_UNREACHABLE			(LL_TCPIP_ERROR - 5)

//! @}

// X28 Errors
//! \defgroup LL_X28_ERRORS	 X28 errors
//! \ingroup LL_ERRORS
//! \brief X28 error list.
//! @{

//! \brief Negative value (-1700) starting the range for the X28 errors.
#define LL_X28_ERROR							(LL_ERRORS - 700)

//! \brief The network as returned the X28 message "LIB"
#define LL_X28_LIB								(LL_X28_ERROR - 1)

//! \brief The network as returned the X28 message "RESET"
#define LL_X28_RESET							(LL_X28_ERROR - 2)

//! \brief The network as returned the X28 message "CLR"
#define LL_X28_CLR								(LL_X28_ERROR - 3)

//! @}

// SSL Errors
//! \defgroup LL_SSL_ERRORS	 SSL errors
//! \ingroup LL_ERRORS
//! \brief SSL error list.
//!
//! A SSL connection can return many error codes. These errors are those returned by the SSL DLL.
//! These errors are remapped between -9000 and -12000 and returned by the LinkLayer.
//! To retrieve the SSL error code from the LinkLayer error code, the LinkLayer error code must be substracted from the offset value LL_SSL_ERROR_SPECIFIC.
//! The SSL error's description can then be found in either \ref SSL_.h or \ref IP_.h header files.
//! Examples: LL_Connect returns -10007, which gives error 7 \ref SSL_PROFILE_CERT_SIGNATURE_FAILURE ( LL_SSL_ERROR_SPECIFIC - (-10007) = 7 ).
//!           LL_Connect returns - 9986, which gives error -14 \ref __ECONNRESET ( LL_SSL_ERROR_SPECIFIC - (-9986) = -14 ).
//! @{

//! \brief Negative value (-1800) starting the range for the SSL errors.
#define LL_SSL_ERROR							(LL_ERRORS - 800)

//! \brief The SSL profile cannot be loaded.
#define LL_ERROR_SSL_PROFILE					(LL_SSL_ERROR - 0)

//! \brief Base error for all SSL Specific error (from -9000 to -12000)
#define LL_SSL_ERROR_SPECIFIC					(-10000)

//! @}

// Tailgate Errors
//! \defgroup LL_TAILGATE_ERRORS	 Tailgate errors
//! \ingroup LL_ERRORS
//! \brief Tailgate error list.
//! @{

//! \brief Negative value (-1900) starting the range for the Tailgate errors.
#define LL_TAILGATE_ERROR							(LL_ERRORS - 900)

//! \brief Error while trying to open the Tailgate channel.
#define LL_TAILGATE_ERROR_OPEN						(LL_TAILGATE_ERROR - 1)

//! \brief Error while receiving using the Tailgate channel.
#define LL_TAILGATE_ERROR_RECEIVE					(LL_TAILGATE_ERROR - 2)

//! \brief Error while sending using the Tailgate channel.
#define LL_TAILGATE_ERROR_SEND						(LL_TAILGATE_ERROR - 3)


//! @}

//-- Wait events ------------------------------------------------

//! \defgroup LL_EVENTS	Communication events
//! \ingroup LL_PHYSICAL_PARAMETERS
//! @{
//! \brief Event to notify the end of the sending operation.
#define LL_WAIT_SEND_END						0x0001
//! \brief Event to notify the reception of data.
#define LL_WAIT_RECEIVED_DATA					0x0002
//! @}


//-- Layer identification ---------------------------------------
//! \defgroup LL_HANDLE	Layer handle identifiers
//! \ingroup LL_PHYSICAL_PARAMETERS
//! \brief Handle identifiers.
//!
//! Identifiers required by the function LL_GetHandle() to return
//! an underlying handle of the communication.
//! @{
//
//! \brief Handle on the SSL session.
#define LL_GET_HANDLE_SSL_SESSION				(1)
//! \brief Handle on the SSL profile.
#define LL_GET_HANDLE_SSL_PROFILE			    (2)
//! \brief Handle on the PPP connection of the GPRS/3G channel.
#define LL_GET_HANDLE_GPRS                      (3)
//! \brief Handle on the PPP connection of the PSTN channel.
#define LL_GET_HANDLE_PPP                       (4)

//! @}

//! \addtogroup LINK_LAYER
//! @{

//! \brief Infinite timeout.
#define LL_INFINITE								0x7fffffff

//-- Types ------------------------------------------------------

//-- Functions --------------------------------------------------


//
// For interface compatibility : _DEL_ and TLV tree.
// To continue using the _DEL_ object interface : the preprocessor
// variable  __USE_DEL_INTERFACE__ must be defined.
//
#ifdef __USE_DEL_INTERFACE__

	// _DEL_ interface object [DEPRECATED].
	int LL_GetInfo(LL_HANDLE hSession, _DEL_ * phInfo);
	int LL_Configure( LL_HANDLE* phSession, const _DEL_ * hConfiguration );

#else

	// TLV tree interface object.
	//! \brief This function retrieves the parameters of a Link Layer configuration.
	//! \param[in]		hSession The handle of the configuration to use.
	//! \param[out]		*phInfo The TlvTree containing the configuration for the given handle.
    //! This TlvTree object is dynamically allocated by the function and must be released by the application using \ref TlvTree_Release().
	//!
	//! Please refer the "LL_Configure()" function for further details about the configuration tags.
	//! \note Deprecated.
	int LL_GetInfo(LL_HANDLE hSession, TLV_TREE_NODE * phInfo);

	//! \brief This function creates, modifies or deletes a Link Layer configuration.
	//! \param[in,out]		*phSession The handle of the configuration:
	//!	- NULL : to create a new configuration.
	//!	- A non-null *phSession handle with a non-null pConfiguration, modifies the specified configuration with
	//! the new specified parameters.
	//!	- A non-null *phSession handle with pConfiguration equal to NULL deletes the specified configuration (see : \ref LL_SAMPLE_CONF_DELETE).
	//! \param[in] hConfiguration TLV tree which contains the parameters describing the communications's protocol stack.
	//!
	//! The available tags for the TLV_Tree are : \ref LL_LAYER_TAGS.
	//
	int LL_Configure( LL_HANDLE* phSession, const TLV_TREE_NODE hConfiguration );

#endif

typedef enum
{
	LL_NO_SCRIPT_MODE,   //!< Script mode not activated.
	LL_SCRIPT_SAVE_MODE, //!< Save a script scenario.
	LL_SCRIPT_READ_MODE  //!< Read a script scenario.
}T_LL_SCRIPT_MODE;

//! \brief This function creates, modifies or deletes a Link Layer configuration for script mode only.
//! This function is exported in the 'LinkLayerExeInterface_Script' library only. It must be used for development purpose only.
//! \param[in,out]		*phSession The handle of the configuration:
//!	- NULL : to create a new configuration.
//!	- A non-null *phSession handle with a non-null pConfiguration, modifies the specified configuration with
//! the new specified parameters.
//!	- A non-null *phSession handle with pConfiguration equal to NULL deletes the specified configuration (see : \ref LL_SAMPLE_CONF_DELETE).
//! \param[in] hConfiguration TLV tree which contains the parameters describing the communications's protocol stack.
//! \param[in] eMode Scripting mode (\ref LL_NO_SCRIPT_MODE, \ref LL_SCRIPT_SAVE_MODE or \ref LL_SCRIPT_READ_MODE).
//! \param[in] szScriptPath Path to the scripting file (ex: "/HOST/SCRIPT.LL"). The FFMS disk must be created before calling this function.
//!
//! The available tags for the TLV_Tree are : \ref LL_LAYER_TAGS.
//! \return			LL_ERROR_OK or a negative error code (see : \ref LL_ERRORS ).
//!
//! When set to \ref LL_SCRIPT_SAVE_MODE, the script engine calls the native IAC functions, and depending on the functions called:
//! - Store the return code as a 4 bytes integer (big endian): \ref LL_Connect() and \ref LL_Disconnect().
//! - Store the data buffer: \ref LL_Send() and \ref LL_Receive().
//! - For all the other functions, nothing is stored in the script file.
//!
//! When set to \ref LL_SCRIPT_READ_MODE, the script engine parses the script file and returns:
//! - The code read in the file for \ref LL_Connect() and \ref LL_Disconnect().
//! - The size of the buffer passed to the application for \ref LL_Send().
//! - The buffer read in the file and its size for \ref LL_Receive().
//! - \ref LL_GetStatus() returns \ref LL_STATUS_CONNECTED after a successful call to \ref LL_Connect(), LL_STATUS_DISCONNECTED otherwise.
//! - The parameters 'nEvents' passed the function \ref LL_WaitEvent().
//! - LL_ERROR_OK for all others API.
//!
//! Please read the \ref SCRIPTING "Scripting mode section" for further details on the script mode.
//!
int LL_Configure_Script( LL_HANDLE* phSession, const TLV_TREE_NODE hConfiguration, T_LL_SCRIPT_MODE eMode, const char* szScriptPath );


//! \brief This function connects the requested physical and protocol layers. 
//
//! It blocks until the connection is done or an error occurs.
//! \param[in]		hSession The handle of the configuration to use.
//! \return			The function one of the following error codes
//!	- \ref LL_ERROR_OK
//!	- \ref LL_ERROR_INVALID_HANDLE
//!	- \ref LL_ERROR_ALREADY_CONNECTED
//!	- \ref LL_ERROR_SERVICE_CALL_FAILURE
//! - Any other connection error (see : \ref LL_ERRORS ).
int LL_Connect(LL_HANDLE hSession);

//! \brief		This function disconnects a connected communication.
//! \param		hSession The handle of the configuration to use.
//! \return		The function one of the following error codes
//!	- \ref LL_ERROR_OK
//!	- \ref LL_ERROR_INVALID_HANDLE
//!	- \ref LL_ERROR_NOT_CONNECTED
//!	- \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_Disconnect(LL_HANDLE hSession);

//! \brief			This function sends data.
//! \param[in]		hSession The handle of the configuration to use.
//! \param[in]		nSize Number of bytes to send.
//! \param[in]		pBuffer Pointer to the data to send.
//! \param[in]		nTimeout Send timeout in hundredth of seconds. 
//! It is mainly used to avoid blocking when the flow control is activated on a serial port.
//!		- 0 returns immediately.
//!		- \ref LL_INFINITE returns only when all the data are sent or when an error occurs.
//! If set to a negative value, the timeout is changed to zero.
//! \return The function always returns the number of bytes sent. 
//! Use LL_GetLastError() to retrieve a potential error.
int LL_Send(LL_HANDLE hSession, int nSize, const void* pBuffer, int nTimeout);

//! \brief		This function waits and receives data.
//! \param[in]		hSession The handle of the configuration to use.
//! \param[in]		nSize Maximum number of bytes to receive.
//! \param[out]		pBuffer The buffer is filled with the received data.
//! \param[in]		nTimeout Reception timeout in hundredth of seconds. 
//!		- 0 returns immediately.
//!		- \ref LL_INFINITE returns only when data are received or when an error occurs.
//! If set to a negative value, the timeout is changed to zero.
//! \return The function always returns the number of bytes read. 
//! Use LL_GetLastError() to retrieve a potential error.
int LL_Receive(LL_HANDLE hSession, int nSize, void* pBuffer, int nTimeout);

//! \brief This function clears the send buffer.
//! \param[in]	hSession The handle of the configuration to use.
//! \return			The function may return one of the following error codes :
//!		- \ref LL_ERROR_OK
//!		- \ref LL_ERROR_INVALID_HANDLE
//!		- \ref LL_ERROR_NOT_CONNECTED
//!		- \ref LL_ERROR_DISCONNECTED
//!		- \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_ClearSendBuffer(LL_HANDLE hSession);

//! \brief This function clears the reception buffer.
//! \param[in]	hSession The handle of the configuration to use.
//! \return			The function may return one of the following error codes :
//!		- \ref LL_ERROR_OK
//!		- \ref LL_ERROR_INVALID_HANDLE
//!		- \ref LL_ERROR_NOT_CONNECTED
//!		- \ref LL_ERROR_DISCONNECTED
//!		- \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_ClearReceiveBuffer(LL_HANDLE hSession);

//! \brief		This function retrieves the last error.
//! \param[in]	hSession The handle of the configuration to use.
//! \return		The function returns the last error that occurred on the specified communication 
//! (see : \ref LL_ERRORS ).
int LL_GetLastError(LL_HANDLE hSession);

//! \param[in]	hSession The handle of the configuration to use.
int LL_GetStatus(LL_HANDLE hSession);

//! \param[in]	hSession The handle of the configuration to use.
//! \param[in]	nEvents
//! \param[in]	nTimeout
//! \return  The function returns 0 when an error occurs or when the timeout is reached. 
//! Use the LL_GetLastError() function to retrieve the error.
//! The function returns the events that occurred. It can be one of the following values :
//!	- \ref LL_WAIT_SEND_END
//!	- \ref LL_WAIT_RECEIVED_DATA
//! \note This function is not supported in SSL mode. It returns always the requested events.
int LL_WaitEvent(LL_HANDLE hSession, int nEvents, int nTimeout);

//! \brief This function retrieves handle on specific structures (handle on a PPP connection, 
//! on PPP over GPRS/3G connection, on a SSL session, on a SSL profile).
//!
//! These handles can then be used to get further information on the connection using dedicated interfaces 
//! (such as PPP_GetOption or X509_GetPeerCertificat, please refer TELIUM add-on TCP/IP documents :
//! [SMO-SFO-0044_D_PackSSL_ReferenceManual] and [SMO-SFO-0039_E_PackIP _ReferenceManual]).
//! \param[in]		hSession	The handle of the configuration to use.
//! \param[in]		nLayerId	The layer identifier : \ref LL_HANDLE.
//! \param[out]		pHandle		Handle on the underlying resource
//! \note The session handle parameter "hSession" can be set to NULL when requesting the PPP handle
// of the GPRS/3G connection (\ref LL_GET_HANDLE_GPRS).
int LL_GetHandle(LL_HANDLE hSession, int nLayerId, LL_HANDLE *pHandle);

// Network functions.
//! \brief			This function returns the current status of the given network.
//! \param[in]		nNetwork The physical network tag (see : \ref LL_PHYSICAL_LINK).
//! \param[out]		pnStatus The current status of the network.
//! The possible values are :
//!	- For GSM : \ref LL_GSM_STATUS
//!	- For GPRS/3G : \ref LL_GPRS_STATUS
//!	- For Ethernet : \ref LL_ETHERNET_STATUS
//!	- For Wifi : \ref LL_WIFI_STATUS
//!	- For serial/USB ports and internal modem : \ref LL_PHYSICAL_STATUS
//!	- For Bluetooth : \ref LL_BT_STATUS
//! \return			The function may return one of the following error codes :
//!		- \ref LL_ERROR_OK
//!		- \ref LL_ERROR_NETWORK_NOT_SUPPORTED
//!		- \ref LL_ERROR_NETWORK_NOT_READY
//!		- \ref LL_ERROR_NETWORK_ERROR
//!		- \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_Network_GetStatus( int nNetwork, int *pnStatus );

// GSM
//! \brief This function starts the GSM modem and enables the GSM facility.
//! \param[in] *szPinCode A null terminated string containing the PIN code of the SIM card.
//! The size must be between 4 bytes (\ref LL_GSM_L_PIN_CODE_MIN)
//! and 8 bytes (\ref LL_GSM_L_PIN_CODE_MAX). 
//!
//! \note If no PIN code is required for the SIM card, "szPinCode" can be set to NULL.
//! \return			The function may return one of the following error codes :
//! - \ref LL_ERROR_OK
//! - \ref LL_ERROR_NETWORK_NOT_SUPPORTED
//! - \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_GSM_Start(const char *szPinCode );

//! \brief This function disconnects the GSM network.
//! \return			The function may return one of the following error codes :
//!	- \ref LL_ERROR_OK
//!	- \ref LL_ERROR_NETWORK_NOT_SUPPORTED
//!	- \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_GSM_Stop(void);

// GPRS
//! \brief This function starts the GPRS/3G modem and enables the GPRS/3G facility.
//! \param[in] *szPinCode A null terminated string containing the PIN code of the SIM card.
//! The size must be between 4 bytes (\ref LL_GSM_L_PIN_CODE_MIN)
//! and 8 bytes (\ref LL_GSM_L_PIN_CODE_MAX). 
//! \param[in] *szAPN	A null terminated string containing the APN.
//! \note If no PIN code is required for the SIM card, "szPinCode" can be set to NULL.
//! \return			The function may return one of the following error codes :
//! - \ref LL_ERROR_OK
//! - \ref LL_ERROR_NETWORK_NOT_SUPPORTED
//! - \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_GPRS_Start(const char *szPinCode, const char *szAPN);

//! \brief This function disconnects the GPRS/3G network.
//! \return			The function may return one of the following error codes :
//! - \ref LL_ERROR_OK
//! - \ref LL_ERROR_NETWORK_NOT_SUPPORTED
//! - \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_GPRS_Stop(void);

//! \brief This function establishes the PPP link with the GPRS/3G provider.
//! \param[in] *szAPN A null terminated string containing the APN.
//! \param[in] *szLoginPPP A null terminated string containing the PPP login.
//! \param[in] *szPasswordPPP A null terminated string containing the password.
//! \param[in] nTimeout Maximum timeout (in 10ms).
//! \return	The function may return one of the following error codes :
//! - \ref LL_ERROR_OK
//! - \ref LL_ERROR_NETWORK_NOT_SUPPORTED
//! - \ref LL_ERROR_NETWORK_ALREADY_CONNECTED
//! - \ref LL_ERROR_NETWORK_NOT_READY
//! - \ref LL_ERROR_NETWORK_ERROR
//! - \ref LL_ERROR_SERVICE_CALL_FAILURE
int LL_GPRS_Connect(const char *szAPN, const char *szLoginPPP, const char *szPasswordPPP, int nTimeout );

//! @}

//! \defgroup LL_CODE_SAMPLES Code samples
//! \ingroup LINK_LAYER
//! \brief Code samples.
//!
//! This section provides a set of samples.
//! @{

//! @}

//! \defgroup LL_SAMPLE_HDLC	HDLC configuration
//! \ingroup LL_CODE_SAMPLES
//! \brief 	HDLC configuration over PSTN (internal modem).
//! 
//! This sample shows how to configure an HDLC communication over PSTN using the internal modem.
//!
//! \include LinkLayer_Sample_01.c
//! \example LinkLayer_Sample_01.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_SAMPLE_ETERNET_SSL	Ethernet configuration with SSL
//! \ingroup LL_CODE_SAMPLES
//! \brief 	Ethernet configuration.
//! 
//! This sample shows how to configure a TCP (with or without SSL) or a UDP communication over the Ethernet link.
//!
//! \include LinkLayer_Sample_02.c
//! \example LinkLayer_Sample_02.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup LL_SAMPLE_CONF_DELETE	Configuration deletion
//! \ingroup LL_CODE_SAMPLES
//! \brief 	Delete a configuration.
//! 
//! This sample shows how to delete a configuration. It releases the session handle allocated by the LL_Configure() function.
//! Deleting an handle is done by requesting the LL_Configure() function with a NULL configuation stack.
//! \include LinkLayer_Sample_03.c
//! \example LinkLayer_Sample_03.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}



//! \defgroup LL_SAMPLE_CONCERT_SSL	CONCERT protocol configuration with SSL
//! \ingroup LL_CODE_SAMPLES
//! \brief 	CONCERT protocol configuration with SSL
//! 
//! This sample shows how to configure a communication to an IP/X25 gateway, using the CONCERT protocol and SSL.
//!
//! \include LinkLayer_Sample_04.c
//! \example LinkLayer_Sample_04.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \defgroup LL_SAMPLE_GPRS_CONNECTION	 GPRS/3G network management
//! \ingroup LL_CODE_SAMPLES
//! \brief 	GPRS/3G network management
//! 
//! This sample shows how to start and connect the GPRS/3G network. 
//!
//! \include LinkLayer_Sample_05.c
//! \example LinkLayer_Sample_05.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \defgroup LL_SAMPLE_PPP_CONNECTION	 PPP connection sample
//! \ingroup LL_CODE_SAMPLES
//! \brief 	PPP connection sample
//! 
//! This sample shows how to manage a PPP connection on a serial port
//! with a Microsoft RAS Server using MSCHAPV2 authentication.
//!
//! \include LinkLayer_Sample_06.c
//! \example LinkLayer_Sample_06.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


#endif // __LINKLAYER_H_INCLUDED

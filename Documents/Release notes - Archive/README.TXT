----------------------------------------------------------------------
		SDK30 package 5.3.1 vs 5.3 (February 2007) 
----------------------------------------------------------------------
1- TELIUM SYSTEM  Pack 5.70
     Add functions
     management of the base with two serial links
     enable to manage two USB keys on a Hub
	     
     Bug fix on
     improvements on P30 management
     improvement USB
     improvement management of FileSystem in R+ configuration

2- TELIUM MANAGER 38.20
     	
     Add functions
     manage the configuration EFT930Morpho with a CLess target		

3- DOCUMENTATION
     

----------------------------------------------------------------------
		SDK30 package 5.3 vs 5.2 ( December 2006) 
----------------------------------------------------------------------
1- TELIUM SYSTEM  Pack 5.58
     Add functions
	management of ML30
        management of UCM
	new function HeapFree() : returns the available memory in the application heap

     Bug fix on
	external GPRS module can be pluged on any COM port
	improve robustness of GPRS module management  
	improve robustness of Bluetooth module management
    !!!!!!!!!!!
	be careful, P30 requires new Schemes(B2 directory) except for the GetPin(B1 directory) 
        a sample is available for describing how to use new Schemes for P30  
 	ML30 still use old Schemes(B1 directory)
        please refer to TLV Standard Secure Scheme_Rev_C.pdf for new schemes
    !!!!!!!!!!!


2- TELIUM MANAGER 38.10
     Add functions	
	management of ML30 and P30
        management of UCM
     Bug fix on 
	till SDK 5.2, in DrawExtendedString(), management of the attribute 
        _NORMAL_ and _PROPORTIONNEL_ was reversed when using 
        fonts _XxY_
     !!!!!!!!!!!
	correction was already delivered in SDK 5.2
	be careful, this correction is not compatible with applications
        based on SDK 5.1 and previous ones
     !!!!!!!!!!!
	new function gprs_IsNetworkAvailable() in the Dll GPRS
	in cashregister mode, it s possible to use the USB link of the base
        improve robustness of MMC access
        pinpad software and hardware configurations can be printed out
        multiple calls to give_your_domain() are suppressed
        
      
	configuration for France :
        improve Dll CB2A

3- DOCUMENTATION
     
     "How to develop on EFT930" revision C
     "FontLib user guide" revision  C
     "FON tool user guide" revision C
     "TLV Standard Secure Scheme" revision C

4- Samples
     the sample "sample" is now available under
     Visual Express environment(VS2005)	  

5- Tools
     update Trace tool(v3.06) :
	time resolution is reduced from 10ms to 30µs
     LLT :
     the file LLT.prm must be updated for ML30(*.M36) and UCM(*.M34)

     M30: EFT30 stationary
     M31: portable
     M32: Twin
     M34: UCM
     M36: ML30
     M??:all EFT30 products

6- Add On
     an Add On UCM will be available very soon	

----------------------------------------------------------------------
		SDK30 package 5.2 vs 5.1 ( September 2006) 
----------------------------------------------------------------------
1- TELIUM SYSTEM  Pack 5.38
     Add functions
	P30 management
        disable red dot battery display information
	manage USB hub with keyboard and bar code reader in same time or two keyboard
	possibility to plug on USB hub TeliumPass reader + pinpad (P30, PPR30 or PPC30)
	CDC driver allow to manage KeySpan USB/RS232 convertor
     Bug fix on
	GPRS pin code presention
        Fseek on File system
    

2- TELIUM MANAGER 37.30
     Add menu shortcut
     Manage TeliumPass and pinpad

3- DOCUMENTATION
     Update "FFMS User Guide" describing r+ mode
     Update "Std secure Schemes User Guide" describinge XOR and RANDOM scheme
     Update "TELIUM Manager  User's Guide"
     Update "Link Layer Reference Guide"
     Add "FontLib User's guide" describing font library
     Add "ConvertBmp UserManual" describing Bmp Convertor graphical tool
     Add "Telium Pin Pad DLL user's guide" describing pinpad functions

4- Samples
     Add FontLib sample
     Adapt GPRS sample to use function gprs_IsNetworkAvailable 


5- Tools
     Add graphical tool to modify / convert BMP to C files
     see documentation "ConvertBmp_UserManual, rev A.pdf"
     This tool is provided in tools\Bmp convertor
----------------------------------------------------------------------
		SDK30 package 5.1 vs 5.0 ( June 2006 ) 
----------------------------------------------------------------------
1- TELIUM SYSTEM
	improve on Telium Pass USB driver
	minor correction on battery management

2- TELIUM MANAGER
	Correction on cash register protocole E+

3- DOCUMENTATION
	Graphical Library User Guide, rev E
		Add functions to manage Telium Pass

	Telium Manage User's guide, rev J
		updated with pack 35 functions.

4- EFTsimulator
	add DLL P30 Canada entry points

5- LinkLayer

----------------------------------------------------------------------
		SDK30 package 5.0 vs 4.8 ( April 2006 ) 
----------------------------------------------------------------------

1- TELIUM SYSTEM
	- add Hynix flash management
	- Update SetNextWakeUp function to wake up application 
	- Flash file System manage now write mode. use FS_OPEN("MyFile","r+").
	- add Control signal management on COM2
	- correction on printer inter-line management
	- SD and MMC management improving
	
2- TELIUM MANAGER
	- add menu to manage Telmium Pass

3- DOCUMENTATION
	- Telium Manager updated

4- EFTsimulator
	- The simulator composant is now delivered in Component\EFTsimulator
  	- Updated to manage Telium Pass DLL


----------------------------------------------------------------------
		SDK30 package 4.8 vs 4.7 ( Feb 2006 ) 
----------------------------------------------------------------------

1- TELIUM SYSTEM
	- Updated to manage new EFT
2- TELIUM MANAGER
        - Telium Manager can be configurated by parameters file
	See Telium Manager user guide, chapter 19
3- DOCUMENTATION
	- Telium Manager
	updated to describe Pack 33
	informations about Manager parameters files.
	- How to develop on EFT930 
	add documentation on function to get hardware information

4- EFTsimulator
	The simulator composant is now delivered in Component\EFTsimulator

----------------------------------------------------------------------
		SDK30 package 4.7 vs 4.6 ( September 2005 ) 
----------------------------------------------------------------------
Common Developement plateform for TELIUM 
    EFT30, EFT30plus, EFTsmart,EFTsmartPlus
    EFT930P,EFT930B,EFT930S, EFT930M (the morpho package is mandatory).

1- TELIUM SYSTEM
   - manage download from TMS using IP
   - blue tooth : multi-base synchronisation

2- TELIUM MANAGER
   - new menu to manage download from TMS using IP

3- DOCUMENTATION
	no update

	

----------------------------------------------------------------------
		SDK30 package 4.6 vs 4.5.1 ( June 2005 ) 
----------------------------------------------------------------------
Common Developement plateform for TELIUM 
    EFT30, EFT30plus, EFTsmart,EFTsmartPlus
    EFT930P,EFT930B,EFT930M,EFT930S

1- TELIUM SYSTEM
    - adapted to manage all terminal
    - increase speed of display on EFT930
    - manage trace on USB
    - manage new UBS device : hub, HID, com 
    - add synchronous chip card driver
    - add SDCARD management
    - correction on USB 
    - V22 fall back if connection problem in V32

2- TELIUM MANAGER
    - adapted to manage all terminal
    - add menu to manage UMS
   
3- DOCUMENTATION
    - documentation "How to develop on EFT930" 
    to help developer to move application from EFT30 to EFT930
    - update of GPRS documentation

4- EFT30 simulator
    - add function to manage VFS, MMC, Morpho
    - add feature to log trace file 


----------------------------------------------------------------------
		SDK30 package 4.5.4 vs 4.5.3 ( Mai 2005 ) 
----------------------------------------------------------------------
Developement plateform for TELIUM EFT930B only.

1- Telium system & Telium Manager 
	to manage EFT930B (BlueTooth)

----------------------------------------------------------------------
		SDK30 package 4.5.3 vs 4.5.2 ( April 2005 ) 
----------------------------------------------------------------------

Developement plateform for TELIUM EFT930M only.


1- Telium system for Morpho
	Manage flash up to 32 mbyte
	allow to manage flash file as r+ mode.

2- Add documentation "Morpho Smart-CBM module interface specification, rev A.pdf"

3- add morpho sample code in SDK\sample morpho



----------------------------------------------------------------------
		SDK30 package 4.5.2 vs 4.5.1 ( April 2005 ) 
----------------------------------------------------------------------

Developement plateform for TELIUM EFT930S only.


1- Telium system corrections
	Add traces in the USB host monitoring
	Support application size (> 1 MBytes)
	Add application heap protection
	Support 1000 files in flash
	USB Endpoint correction
	UMS correction (support more than 20 files on the disk)
	
2- Add new synchronous card drivers for SLE4436 and GFM.
3- Add USB driver or CDC (USB/serial adaptors)
4- Documentation update
     Std secure Schemes User Guide rev F	
     Telium Synchronous Chip Card User Guide, Rev B

----------------------------------------------------------------------
		SDK30 package 4.5.1 vs 4.5 ( March 2005 ) 
----------------------------------------------------------------------

1- Telium system corrections
     GPRS driver : more stable
     system : correction on PPP
     modem driver : 
		improving of fast connect 
		2 tonality detection during dialing
		improving of tonality detection


		
----------------------------------------------------------------------
		SDK30 package 4.5 vs 4.4 ( February 2005 ) 
----------------------------------------------------------------------

Common developement plateform for TELIUM product range
EFT30, EFT30plus,EFTsmart,EFT930G, EFT930P, Twin30

1- Manager
    new GPRS DLL, allow to switch GPRS/GSM
    UMS DLL  (UsbMass Storage)
        allow to use UMS to load application, read and write data from application.
   
2- System 
    add UMS driver
    driver for synchronous chip card, GPM271, S9, S10, GPM896

3- samples
     sample GPRS
     update Sample to run on EFT930

4- Documentation update
     Std secure Schemes User Guide rev E	
     TELIUM GPRS Librairy User's Guide, rev B	
     TELIUM Manager  User's Guide, rev E	
     TELIUM Systeme  Reference manuel, rev 
     SDK User Guide, rev E 
     Telium Synchronous Chip Card User Guide, Rev A

5- EFT Simulator
     updated to manage scheme ( see SDK User Guide)
     add new functions (GPRS, EFT930 specific functions).

----------------------------------------------------------------------
		SDK30 package 4.4 vs 4.3 ( October 2004 ) 
----------------------------------------------------------------------

Preliminary SDK to use GPRS DLL on EFT930
To use only on development phase.
Don't use this SDK on EFT30
Don't put SDK component on field

1- Manager
    add entry point to use GPRS DLL
    add Screen Menu to insert GPRS/GSM parameters
    add GPRS/GSM DLL
2- System 
    add GPRS/GSM driver

3- samples
	add Sample GPRS



----------------------------------------------------------------------
		SDK30 package 4.3 vs 4.2 ( September 2004 ) 
----------------------------------------------------------------------

1- Manager Updates
	Manage EFT930P and Twin30

2- System updated
	Manage EFT930P and Twin30

3- Tools
	= add DUMPSGN dos tools. This tool allow to display the containt of SGN file
	(signature of application and includes schemes)

4- Simulator
	manage : Pin Pad (PP30, PPC30 and PPR30), schemes and French Health entry points

5- samples
	add Sample Pin Pad
		this sample use EFT or external Pin Pad (PP30/PPC30/PPR30)
		with PPC30/PPR30 pin bloc is computed in Pin Pad
	add Sample French Health
		This sample help to call French Health (EI96) application
	add InitManeger sample
		This sample modify manager parameters

----------------------------------------------------------------------			      
		SDK30 package 4.2 vs 4.1 ( Jully 2004 ) 
----------------------------------------------------------------------

1- documentation
	Add "how to updateEFT30 with SDK" in documentation folder
	add "Componant list of SDK 4.2" in documentation folder
   
   complementaty information 
	= Real Time Kernel
	7.2.3 Killing task
		input parameters : "" or "-" or "*"
		"*" do not reset the task if the peripheral is open. return that the task
		whas not killed.
	= OEMC Ref Manual
	4.2.1 ttestall	
		event from 28 to 31 are user defined

2- Schemes 
        Add scheme : SchFree used to delete Secret Area in crypto
	new version of SchLoadData,SchCipherDa (correction data loadingfrom  1023 to 1024 ), 
			SchGetPin (correction VALID with pin lenght less than requested)
3- Manager Updates
        35390116 (Manager
		add Pin Pad diagnostic
		possibility to disable display message if pointer = NULL in language DLL
		suppress waiting of card remove after debit
	35930111 (CB 2A DLL)
		correction CBPR 
		add compatibility byte
        35940116  Extens DLL)
		possibility to disable display message if pointer = NULL in language DLL
        35950106 (Language DLL)
		add message 260 to 262 to manage EMV selection
        35960110 (Graphical Librairy)
		add management of Twin 30 
	35970113 (Parameter DLL)
		verification of Pin pad presence
	35980110 (Entry DLL)
		anomalie correction on display/capture pin 
        35990109 (Cam / date DLL)
		add management of Twin 30 
        36030109 (protocol DLL)
		possibility to use protocole at 1200 bauds
	36040111 (protocol DLL)
		add management of Twin 30 
	36080108 (EMV selection DLL)
		possibility to disable display message if pointer = NULL in language DLL
        36090104 (IAM DLL)
		change message header S_MESSAGE_IAM
	36100103 (Pin pad DLL)
		add PinPad diagnostic
        36110105 (PPR30 DLL)
		add PinPad diagnostic


4- Includes updated
	add FallBack management functions
	add PinPad definition
			
5- System updated
	- 30100180 (manager)
		add FallBack management by application
		manague NULL pointer in language DLL -> no disaplay
	- 30150223 (modem driver)
		manage BELL 103, BELL 212
		synchronous frame up 2048 bytes (for HDLC)
6- Warning		
	StartDelay : in the function called by StartDelay, use only Signal Event and 
		data appliction. Don't used any other system call !!!!!

		
----------------------------------------------------------------------	
		      SDK30 package 4.1 vs 3.4 ( Mars 2004 )
----------------------------------------------------------------------

The SDK30 release 4.1 provided a new organisation for the files and sample.

	>> 4 folders
		1 A Folder for the downloading files "Component"
		2 A Folder for the documentation "Documents"
		3 A Folder for library and sample "SDK"
		4 A Folder for the tools like GNU Compiler "Tools"

1 Terminal simulator
	>> A Terminal simulator is provided. Each library and sample are generated for 
Visual C++ 6.0 environement (with the name Lib_simul or Obj_simul)
	>> A simulator application for terminal simulation is provided in SDK/Lib_simul
	>> The installation processus is described in Appendix.A document

2 The GNU Compiler
	>> A GNU compiler is provided in this package for ARM processor (Tools Folder).
	>> Each library and sample are generated for GNU environement (with the name Lib_gnu
 or Obj_simul)
	>> Specifics makefile for GNU environement are provided for each sample.

3 The Schemes Library 
	>> Header files and Library are provided in the SDK/inc and SDK/Lib_XXX folders for 
the use of standard Schemes Library.
	>> A Specific document for "Standard secure schemes user guide" ii added in 
the documents folder. This document is in Preliminary version.
	>> A Specific sample for the use of schemes is located in /SDK/sample_schemes folder.


4 Manager Updates
	>> No new DLL
	>> The Export.m30 file contain the list of module to be downloaded for an export 
M2OS configuartion.
	>> Interne.m30 and Sante.m30 contain the list of modules for French or Health
configuration.
	
5 Includes updated
	
	>> A new set of include file is located in /SDK/inc folder. This set is design for 
the use of the new library as "Schemes", "Com_event", "Simulator".
	>> File SDK30.H include all includes files for M2OS used.
 
6 System updated
	>> Managment of the SAMSUNG and TOSHIBA Flash
	>> Optimisation for Flash Management and system
	>> The default mode for the display is 2 lines *16 char. 
	>> The font 4*7 is integrated in the driver .



----------------------------------------------------------------------
		      SDK30 package 3.5 vs 3.4 ( February 2004 )
----------------------------------------------------------------------

1 Manager updates : 
	>> reload all DLLs and Manager as DLL mapping has changed
	- 35920112 replaces 35920111 ( Manager kernel ) 
		>> a part of the modification to manage 16x16 Font
		>> Chineese Date format
	- 35930110 replaces 35930109 ( for french market ) 
		>> don't care 
	- 35940113 replaces 35940112 ( manager services )
		>> a part of the modification to manage 16x16 Font
		>> Chineese Date format
	- 35960109 replaces 35960108 ( Libgr)
		>> modification to manage 16x16 Font
	- 3970112 replaces 35970111 (Param)
		>> a part of the modification to manage 16x16 Font
		>> Chineese Date format	
		>> Display serial number of the POS
		>> A new function "PSQ_Update_Cash_Connection"
	- 35980109 replaces 35980108 ( Saisie)
		>> a part of the modification to manage 16x16 Font
		>> Chineese Date format			
	- 36020106 replaces 36020105 (Null Protocol)
		>> Implement COM_EVENT
	- 36130203 replaces 36050203 (PPS30)
		>> Change the number of the DLL
	- 36080105 replaces 36080104 (EMV SQ)
		>> a part of the modification to manage 16x16 Font
		>> Display "Card Rejected" in case of "use mag stripe"  

2 Includes updated
	
	param.h : added some type defines
	appel.h: added some type defines

		      SDK30 package 3.4 vs 3.3 ( January 2004 ) 

1 Manager updates : 
	>> reload all DLLs and Manager as DLL mapping has changed 
	- 35920111 replaces 35920110 ( Manager kernel ) 
		>> DLL mapping changed 
	- 35930109 replaces 35930108 ( for french market ) 
		>> don't care 
	- 35940112 replaces 35940111 ( manager services )
		>> DLL mapping changed
		>> corrected bug when USB KEYBOARD event occurs and when application redefines keys to standard keyboard on keyboard_event
		   Manager was not taking the key into account
	- 35960107 replaces 35960105 ( graphic library ) 
		>> corrected reverse video problem on user defined characters
		>> corrected slowness when navigating with user defined characters
		>> added right gap of dots of user defined characters
		>> added cyrillic characters missing from 0xE0 to 0xE6 and 0xEF(see New graphic library font.pdf)
		>> DLL mapping changed  
			0xE0034000 for code beginning address 
			0xE003B000 for data beginning address 
	- 35970111 replaces 35970110 ( manager parameters handling ) 
		>> DLL mapping changed
	- 35980108 replaces 35980107 ( entry services )
		>> DLL mapping changed
	- 35990108 replaces 35990107 ( for french market ) 
		>> DLL mapping changed
	- 36000102 removed 
	- 36020105 replaces 36020104 ( null protocol on COM0 ) 
		>> don't care
	- 3605xxxx no change 	     ( PP30 DLL ) 
		- 36050201 to be loaded on mock-up terminal ( see Manager/Debug )
		- 36050203 to be loaded on activated terminal ( PPS30 DLL )   
	- 36060103 no change 	     ( crypto DLL ) 
	- 36080104 no change	     ( EMV application selection )
	- 36090103 replaces 36080102 ( IAM ) 
		>> don't care
	- 36100102 no change 	     ( Pinpad global interface DLL )		           -------------------------

2 Modem driver 30150207 
	>> Taiwan Host connection problem fixed 
	>> V32bis + ADSL filter connection enhancement
	>> BELL 212 mode supported via AT$M248Z, AT$M250Z to back to V22 mode 


3 Includes updated
	oem.h : 
		added some missing defines ( KEYS_IN_BUFFER, TRACK_READ, CAM_PRESENT, CARD_REMOVAL )
		NAVI_OK & NAVI_CLEAR defines changed
	pinpad.h file added to give access again to PP30 routines in english !	
	param.h : added some pinpad type defines

4 HDLC library modified
	- changed pause from 100ms to 20ms after receiving an HDLC frame : can cause some problems during HDLC_connect to some Host 
	- HDLC_send_receive timeout might not be enough when receiving larger HDLC blocks ( > 256 bytes )
		modify protohdlc.c  line 176 replace 
		     if ( HDLC_ok == receive_hdlc (&sys_bytes, ptr_in+nb_recus,&a_recevoir_max, 300, periph) )
			by 
		     if ( HDLC_ok == receive_hdlc (&sys_bytes, ptr_in+nb_recus,&a_recevoir_max, 800, periph) )

5 Undocumented routine to print better graphics bit map
	int        DefprinterpatternHR (char weight, char density, char key, char *pattern);
		- weight 
			#define    PRINTER_WEIGHT_LIGHT      0		// Normal
			#define    PRINTER_WEIGHT_BOLD       1		// Bold 
		- density 
			#define    PRINTER_DENSITY_NORMAL    0		// Normal
			#define    PRINTER_DENSITY_CONDENSED 1		// Condensed
			#define    PRINTER_DENSITY_WIDE      3		// Large
		- pattern : same as defprinterpattern ! 

6 Customise 
	>> message.h updated
	>> link file and generation file for DLL changed 
		import eft30.alf and trap.o from sample/obj 
		change code & data beginning address
		removed libappli, trap.s in gen.bat that now are unuseful 
		output sgn instead of bin 

7 Documentation errata
	>> display code 0xFF is not allowed when defining user characters via defdisplaypattern routine
	   only 0x20 to 0xFE is allowed 
	>> is_delete only works with Manager function F-> Manager -> Deletion -> code 07 -> Navigation list
	>> fioctl example for RTS/CTS handling ( see oem_com.h ) 
		fioctl(COM_FIOCTL_SET_RTS,NULL,fd);   // Set RTS
	        fioctl(COM_FIOCTL_CLEAR_RTS,NULL,fd); // Clear RTS
		fioctl(COM_FIOCTL_GET_CTS,NULL,fd));  // Read CTS (0/1)

----------------------------------------------------------------------	
		      SDK30 package 3.3 vs 3.2 ( December 2003 ) 
----------------------------------------------------------------------

1 Manager updates 
	- 35920110 replaces 35920109 ( Manager kernel ) 
	- 35930108 replaces 35930107 ( for french market ) 
	- 35940111 replaces 35940110 ( manager services )
	- 35960105 replaces 35960104 ( graphic library ) 
	- 35970110 replaces 35970108 ( manager parameters handling ) 
	- 35980107 replaces 35980106 ( entry services )
	- 35990107 replaces 35990106 ( for french market ) 
	- 36020104 no change         ( null protocol on COM0 ) 
	- 3605xxxx 		     ( PP30 DLL ) 
		- 36050201 to be loaded on mock-up terminal ( see Manager/Debug )
		- 36050203 to be loaded on activated terminal ( PPS30 DLL )   
	- 36060103 no change 	     ( crypto DLL ) 
	- 36080104 replaces 36080103 ( EMV application selection )
	- 36090102 no change         ( IAM ) 
	- 36100102 replaces 36100101 ( Pinpad global interface DLL )
		>> DLL mapping changed, need to download the whole manager configuration 
		>> mapping for language DLL changed 
			E0030000 for code and E0037000 for data instead of 
			E0033000 for code and E003B000 for data
		>> Cyrillic font added in Graphic library ( see New graphic library font.pdf from /docs )
		>> PPS_SetComFormat to change PP30 framing to 8 bits : allows displaying Cyrillic characters (code from 0xA0 up to 0xC7, same font as graphic library, see above ) 
		>> ISO2 card with luhn code error are now accepted by the Manager and Manager gives focus to application via debit_non_EMV in polling mode ( the first application that returns STOP will stop the Manager polling process )
		>> chinese ISO3 cards decoding problem fixed 
		>> fixes case of reset in case of USB keyboard when the USB driver is absent 
		>> USB keyboard keys are now transmitted to application via keyboard_event but keycode is coded as following 
			leftmost bit of the keycode integer is 1 in case of USB keyboard, 0 otherwise  
			for instance 
				A entered on the USB keyboard will be coded as 0x8041 
				1 entered on the USB keyboard will be coded as 0x8031
				1 entered on the EFT30 keyboard will be coded as 0x0031 
		>> S_TRANSIN structure is given on is_for_you_before entry point like on is_for_you_after 
		>> S_TRANSIN structure is also given on give_AID entry point
		>> automatic Manager Parameters Initialisation 
			you need to load init application ( application type 0xAA ) that creates m2os.ini file first. Once parameters file is created this application kills itself 
			Manager is automatically initialised with default parameters
				Format :	DD/MM/YYYY
				Date & Time : 	current date & time of terminal 
				Language : 	English		
				PABX : 		No
				Pinpad :	No
				ISOx :		according to h/w
				Serial number :	according to h/w
				TMS network :	PSTN
				TMS number :	0836062424
				TMS Pad :	11111111111111
				TMS identifier:	1999183
				Remote loading: Not protected
			There is so no need to manually initialised all manager parameters, just change the date & time if needed
	

2 OS updates 
	- 30100154 replaces 30100152 ( OS kernel ) 
		>> fixes ISO3 decoding problem on Chinese cards
		>> RTS/CTS handling on COM0 via fioctl routine added 
		>> PPP on COM2 becoming possible
		>> fixes %% format on vsprintf routines

	- 30130206 replaces 30130204 ( Crypto OS ) 
		>> effraction handling enhanced 

	- 30150202 replaces 30150201 ( >>>> a confirmer ) 
		>> NAC connection supported via specific AT command and modem config  
			- 1300 Hz suppression via modem.cfg file 
			- AT commands to be sent for proper NAC connection
				ATS144=16 for synchronous mode
				ATF4  for V22 mode
				AT$M251 for general fast connect connexion 
				AT$M249 for specific NAC connexion 

3 includes 
	- malloc.h added giving access to 
		void *umalloc(unsigned int size);
		void ufree(void*p);
	- oem_com.h added for RTS/CTS handling
 	- trace routine added in api.h 
	- one EMV step defined added in _emvdc_.h 
	- version modified in libgr.h

4 Sample 
	- Project file updated for SDT 
		>> eft30.lib has been renamed to eft30.alf
		>> eft30.alf replaces previous existing .o files 

5 Customise Manager 
	- Language DLL : mapping changed, linking addresses changed 
	- message file updated

6 SST 3.1 does not work on Win 2000 chinese version, use english Win 2000 version : this will be corrected in a later release

7 Tools directory added 
	BMP converter as described in Graphic library user's guide 

8 Documentation Errata 
	>> Inter Application Message (IAM ) described in M2OS user's guide is now available provided IAM DLL is loaded (36090102+)
	>> prototype of ServiceCall in oem.h is correct but the first parameter is a concatenation between the application type (MSB) and the service id ( LSB ).
		int ServiceCall(unsigned int serv_id, unsigned int data_size, void* data_element, int *ret_code);

9 USB keyboard and Mouse 
	>> EFT30 and EFT30+ is required ( USB Host required ) 
	>> not compatible with PPR30 pinpad reader as it uses the same USB Host port
	>> 2 new peripherals KEYBUSB and MOUSE have been added 
	>> OS 30100152+ is required and a specific driver 30260101 must be loaded into the terminal 

	>> KEYUSB: The KEYUSB works like the KEYBOARD peripheral 
		-  2 features have been added 
		- You must define a new mapping for your specific KEYBOARD ( The native keyboard is the French).
		You can associate 4 values to each geographic  key ( NORMAL,SHIFT,CTRL,ALT).
		The null value correspond to no key return to the application.
		For fill this map use the trace tools of the EFT30. When you strike a key the gegraphic value appear on the screen  of the PC.

		- If you use the event  "SPECIAL_KEY" a push on the special key ( CTRL/ALT/SHIFT or WIN) send an event to the application.
	>> MOUSE:
		- You can read the mouse with the fioctl function.
		- You read 4 bytes:
			- 1 the state of the button
			- 2  the  dx of the mouse
			- 3 the dy of the mouse
			- 4 the wheel of the mouse

	>> hid.h include file added ( see /inc ) 
	>> a sample program is also given ( see /sample task_user.c )

----------------------------------------------------------------------
	      		SDK30 package 3.2 vs 3.1 ( November 2003 ) 
----------------------------------------------------------------------

1 Manager updates 
	- 35920109 replaces 35920108 ( Manager kernel ) 
	- 35930107 replaces 35930106 ( for french market ) 
	- 35940110 replaces 35940109 ( manager services )
	- 35960104 no change 	     ( graphic library ) 
	- 35970108 replaces 35970107 ( manager parameters handling ) 
	- 35980106 replaces 35980105 ( entry services )
	- 35990106 replaces 35990105 ( for french market ) 
	- 36010103 removed ( not useful ) 
	- 36020104 replaces 36020103 ( null protocol on COM0 ) 
	- 36050201 no change ( PP30 DLL with key loading )
	- 36050202 no change ( PP30 DLL without key )  
	- 36060103 replaces 36060102 ( crypto DLL ) 
	- 36080103 replaces 36080102  ( EMV application selection )
	- 36090102 replaces 36090101 ( IAM ) 
	- 36100101 added, Pinpad global interface DLL 
	- Message file updated ( see customise ) 
		>> compatible with future PPR30 Pinpad reader, during Pinpad selection, it is asked PP30 or PPR30
		>> compatible with EFT30+ ( large screen )
		>> change the message on manual entry ( card n° instead of card no ) 
		>> historical bytes given on give_aid entry point : change in give_aid structure
		>> expiration date message changed for french application
		>> EFT30F suppressed from Manager receipts
		>> hardware config receipt : printing activation & ethernet information
		>> lowercase not displayed during application name selection
		>> printing hardware configuration ( CAM, COM, USB ) 
		>> possibility to suppress DLLs via deletion menu + code 26 
		>> ttestall excepts an integer mask and returns an integer to accept new events
		>> Manager stops for 2 seconds per application during the state receipt : fixed 

2 OS updates 
	- 30100152 replaces 30100144 ( OS kernel ) 
		>> EFT30plus supported
		>> USB keyboard and mouse supported ( need for a specific driver and documentation : consult us ) 
		>> PPR30 supported ( pinpad reader ) 
		>> fork interface modified to allow an EFT20 compatible behavior : the forked task has the same priority than the caller task 
			extern t_topstack* fork(word(*task)(),byte*topstack,int spstacksize);
			spstacksize is used to specify a relative priority of the created task.
			spstacksize may vary from 0 up to 31 included
			priority of created task is current priority+spstacksize
	- 30150201 replaces 30150106 ( modem driver ) 
		>> fast connect supported for Turkey country   
		>> compatible with external modem configuration file ( modem.cfg ) : 
			such file allows country specific settings like STMF inter digit time changing
		>> line relay handling 
		>> karel switch problem fixed 
		>> HDLC / synchronous mode supported 
		
3 Library updates
	- trap.o, eft30.lib updated for both SDT & RVD 
	
4 Crypto OS updated 
	- 30130204 replaces 30130203 
		>> correct a bug found in 30130203 (case of desactivation of terminal !) 
		>> unchanged debug version ( 30138203 ) 

5 include updated
	- prototypes missing added 
	- ttestall expects and returns an unsigned int instead of unsigned short int for new events handling
		unsigned int ttestall(unsigned int events,unsigned int TimeOut);
	- is_for_you_before prototype changed
		int is_for_you_before (NO_SEGMENT, S_TRANSIN *,   S_ETATOUT *);
	- new Manager entry point select_aid for externalisation of EMV application selection 
		int select_aid  (NO_SEGMENT, S_SELECT_AID *,S_AID_OUT *);

6 HDLC protocol added
	- HDLC level 1 is at OS level
	- HDLC level 2 must be compiled and linked at application level
	- new documentation about HDLC interface provided 

7 USBdev directory added 
	- USB Host required
	- USB keyboard & mouse driver available : 30260101 
	- include and sample program 
	- new trap.o 
	- short documentation : see readme file in USBdev directory 

8 Big Display driver for EFT30+ 
	- This driver must be loaded on EFT30+ but do not load it on EFTsmart and EFT30 devices ! 

9 Trace tool updated
	>> it does not require to install files on the D:\ root directory any more 
	>> the 3 files only need to be on the same directory, trace_tool.cfg should point now to the working directory ! 

10 Documentation errata & skills 
	- idle message is run from a background task of the manager and can be interrupted at any time by the manager. 
	  When such situation occurs, Manager sends an event ( TIMER see below ) to the idle message in order to force application to  return to the manager
		#define EVT_TIMER              10
		#define TIMER                  1<<EVT_TIMER

	- How to get the EFT30 serial number ? 
		see param.h 
			typedef char NO_SERIE [20+1];
			void  PSQ_Donner_noserie ( char *noserie );
			PSQ_Donner_noserie retrieve the serial number of the terminal if not changed during at Manager initialisation

	- Language DLL : the data size should be 1000 in LDF file otherwise the DLL cannot be loaded and the new language cannot be seen at Manager level 

	- How to invoke SST30 in batch mode : see documentation in /docs

----------------------------------------------------------------------
		      SDK30 package 3.1 vs 3.0 ( September 2003 ) 
----------------------------------------------------------------------

1  OS updates : release 1.44 (30100144) replaces release 1.41 (30100141)
		- trace now on COM0 port avoiding to have specific cable
			- trace is working when LLT is not operating and when boot loader 0149107 is loaded
			- removing trace by loading boot loader 0140107 as usual 
			- tracing is now possible when PP30 is connected
		- COM2 and Ethernet operational on EFT30 Plus 
		- bugs fixed on SoftwareActivate and Fs_CreateDisk 
		- Booting with C key is now working again for debugging purpose (regression on OS 1.41) 

2  OS 1.41+ requires now only .sgn files on loading even if they are not signed for debugging purpose. 
   .bin are no more accepted. 
   Changes have so been done in various command files that generate now .sgn in \gen directory even they are not signed 
   All sample .adf files should point now to .sgn instead of pointing to .bin. 
   Be careful when signing software as all files have .sgn extension whether they are signed or not
   We so recommend to keep signed versions in \Program Files\SST EFT30\Destination directory

3  Crypto OS has got release 2.3 (30130203) : differences with release 2.2
		- fixes compatibility problem with internal Crypto OS release 2.1 that could be present on first EFTSmart manufactured in September 2003 

4  Known bugs  : 
	Manager stops for 2 seconds per application during the state receipt. 
	It will be solved in the next Manager release 

----------------------------------------------------------------------
		      SDK30 package 3.0 vs 2.2 ( September 2003 ) 
----------------------------------------------------------------------

1 New signed OS and Manager and DLLs according to the new certificates management described below : 
	- All Sagem Monetel modules will be signed with Kc key and Cc certificate pair. Such certificate authorises all Kpis
	- VAR modules will be signed with Kpi ( country key,  i identifies the VAR and corresponds to the RSA card you have got ), 
	  corresponding certificate Cpi will be sent to you asap and will replace the one you have got before July 2003. 

   Remark : certificate and signature will only be checked with standard Crypto OS version.
	OS release has got 1.41, differences with release 1.25 are listed below 
		- TCP/IP, Ethernet, USB Host and MMC supported 
		- EFTSmart compatible 
		- bug resolution on card removal handling on EFTSmart 
		- added printf float format 
		- bug on fast and multiple track reading fixed  
		- FFMS : bug fixed on invalid blocks management  
	Modem driver has got release 1.6, differences with release 1.3 are listed below 
		- pulse dialling problem fixed 
		- sending level setting changed ( -15dB instead of -11dB )
		- country table handling via configuration file to be loaded via LLT ( India table only ) 
	Crypto OS has got release 2.2, no differences with release 1.16
		- debug version 30138202 
		- standard version 30130202 ( auto activated version if previous OS was 30130113) 

 
2 added m30 catalog file for easier loading ( just click on m30 file when selecting files to be loaded ) 
	>> applied to OS and drivers modules 

3 New PP30 DLL 6050201 that injects the key for PP30 operation
	>> scheme bug fixed
	>> Caution : same loadable files, same release number !!  

4 Language DLL : adf file was missing for the DLL 

5 DLL EMV 6080102 replaces 6080101 : minor bug fixed for French EMV environment  

6 DLL Graphic library 5960104 replaces 5960103 : bug fixed when customising manager messages and redefining local characters
	>> new routine added to redefine user characters 
		int DefGraphicPattern(char key,char *pattern,int police)
			key = character to be defined  (all code authorized excepted 0xA0)
			pattern = same as defdisplaypattern
			police = 	_SMALL_ or
					_MEDIUM_ or
					_LARGE_

7 new library files for both SDT and RVD tools : 
	>> eft30.lib that replaces all previous libraries excepted cstartup.o and trap.o 
	>> updated trap.o file for OS APIs 

8 Boot loader has got release 01.07 
	>> 30140107 standard version
	>> 30148107 trace version
	This software normally does not need to be loaded as it is done at factory level
	Remind that boot loader just copy OS from flash to RAM and then runs it 
	You can find those files in /os/debug 

9 LLT in batch mode : see LLT batch documentation for details in /Docs directory 

----------------------------------------------------------------------
		      SDK30 package 2.2 vs 2.1 ( June 2003 ) 
----------------------------------------------------------------------

1 OS updates 0100125 release replaces the previous one 0100124 	
	- one severe bug found in FFMS in wrong Flash blocks management 
		
2 Crypto OS updates : 
	standard  version 0131116 replaces 0130113, terminal needs to be activated
	debug version  0138116 replaces 0138115 auto activated
	- initialisation problem found on some RAM profiles in Crypto processor

3 Multi Ice configuration file is now thunder.cfg instead of eft30.cfg for EFT30 mock-up 

----------------------------------------------------------------------
		      SDK30 package 2.1 vs 2.0 ( May 2003 ) 
----------------------------------------------------------------------

1 Modified sample entry.c when using num_entry ( MAXX, MAXY were not initialised ! ) 		

2 OS gets release 30100124, no more debug OS version, done in boot ram version ( 30148106 ) instead of standard 30140106 ( not provided because factory loaded )
	2.1 separated modem driver 
	2.2 USB Host operational 
	2.3 terminal start up time reduced
	2.4 1 bug corrected in FFMS during garbage 
	2.5 C key pressed on boot gets smiley and keeps boot mode for debugging purpose
		( C key must be pressed on reset when screen disappears and before the smiley happens ) 
		SDT script startc.inc must be invoked at ADW booting time ( when the breakpoint 0xFFFF0008 is reached , just go, EFT30 reboots with the debugger )
		RVD script not yet available, still need to turn the switch on LLT cable at boot time but requires Booster 0130103 that can be found in previous SDK30 release
	2.6 TestReceive & EventsOccured missing routines added  	 

3 Crypto OS gets different profiles release
	- 30138115  debug version (to be loaded onto mock-up terminal only, no signature check, it periodically displays "MOCK-UP", Start debugging session with C)
	- 30130113  standard version  (auto activation of the terminal, signature checking, no debug capabilities) 
   

4 Modem driver has been separated from OS and gets release 30150103 
	4.1 Turkish Fast connect integrated : 
		Fast connect command AT$M251 in ATF4 or ATF5 mode 
		Normal mode command AT$M250 
	4.2 separated from OS 
	4.3 2100Hz checking time reduced to 60ms instead of 600ms ( Akbank problem ) 
	4.4 Waiting time to take the line reduced to 500ms instead of 2 seconds 

5 Documentation Errata in M2OS user's guide 
	5.1 PSQ_No_terminal  returns an unsigned char NO_TERMINAL value
	5.2 PSQ_Give_Language returns 1 as English and 0 as French 
	5.3 Pinpad presence checking done through 
		int PPS_IsConnected(void) 
			returns 0 if connected 
			returns <> 0 otherwise 
	5.4 Pinpad initialisation : void PPS_Dll_Init (void) mandatory 

6 Documentation Errata in FFMS user's guide
	6.1 FS_dskcreate volume size only given for information, disk size can increase according to files writing

7 Documentation Errata in OEMC user's guide
	7.1 input_command & output_command never returns 0x29 as return code
	7.2 F1 has got value 0x19, F2 has got value 0x20, F3 has got value 0x21, F4 has got value 0x22
	7.3 S11 register described erroneously : it means : Set DMTF tone time  
	7.4 ATZ is no more necessary at application level
	7.5 SoftwareActivate routine missing, it supersedes allocate & activate in previous EFT10/20 platform. 
		int NTP_SoftwareActivate ( unsigned char * path )
			path : path of the disk where application files are located i.e 
				application.sgn 
				application.adf
			application must mount first a disk with at least 3 files, then copy the files and activate
			a reset must follow the activation in order to put the application in place

8 M20S and its DLL updates 
		- 35920108 Manager kernel and its DLL 
	 	- 35930106  CB2A DLL ( French Domain )
	 	- 35940109  Extens DLL
	 	- 35960103  Graphic Library DLL
	 	- 35970107  Param DLL
	 	- 35980105  Entry DLL
	 	- 35990105  SV DLL ( French Domain )
	 	- 36010103  PSC DLL ( French Domain ) 
	 	- 36020103  NULL protocol ( French Domain ) 
	 	- 36050201  Pinpad DLL + key injection for PP30 
				>> NOT TO BE USED on the field !
				>> to be loaded first prior loading 6050202
		- 36050202  Pinpad DLL 
	 	- 36060102  Crypto DLL
		- 36080101  Externalisation of EMV application selection
		- 36090101  Inter Application Messaging 

	- EMV level 2 compliant ( supports EMV level 2 package ) 
	- New entry point for user Chip card application selection  
	- added software configuration in Manager menu F -> Manager -> Consultation -> Configuration
	- new Pinpad & Crypto DLL

9 Manager Messages updated 
	9.1 Message file updated ( messages added ) 
	9.2 Language DLL must so be regenerated ( see customise ) 

10 New files and updates
	p30_api.o for SDT 
	eft30.lib for RVD 
	pp30_api.h 
	pp30_names.h
	pp30_def.h 

----------------------------------------------------------------------
		      SDK30 package 2.0 vs 1.0 
----------------------------------------------------------------------
 		     
1 Added compatibilities with RVCT 1.2 / RVD 1.6 RealView tools
	 - new sample files for RVCT/RVD tools 
	 - new compatible libraries for RVCT  

2 Language Customisation added in file distribution 

3 OS gets release 30100113 ( 1.13 normal )  30108113 ( Debug 1.13 ) 

4 Crypto OS gets release 30130113 ( 1.13 normal ) 30130103 ( Debug 1.3 ) without security and activation process 
  Do not install them on the field ! 
   

5 Doc updates 
	 - SDK30 user's guide get revision C 
	 - M2OS user's guide get revision B (DLL language management, PP30 handling ) 

----------------------------------------------------------------------
			  SDK30 package 
----------------------------------------------------------------------

CAUTION : 
>> please read first the licensing file coming with the CD-ROM 
>> This package constitutes the first version of the Software Development Tool KIT
>> all files found in this package are only delivered for software development not for the field ! 

You will find the following distribution files for EFT30. 
Standard InstallShield installation /sdk30v20

/OS 
 	- 010xxyy : Kernel OS  
	- 015xxyy : Modem driver 
	- 013xxyy : OS for Crypto processor 
		* 0131xyy : auto activated  	
		* 0138xyy : debug version for mock-up only  
	- 014xxyy : RAM boot ( only provided for debugging purpose )

/Manager/Export ( International configuration ) 
	- 3592xxyy Manager kernel 
	- and its DLL 
	 	- 3593xxyy  CB2A DLL ( French Domain )
	 	- 3594xxyy  Extens DLL
	 	- 3596xxyy  Graphic Library DLL
	 	- 3597xxyy  Param DLL
	 	- 3598xxyy  Entry DLL
	 	- 3599xxyy  SV DLL ( Health Care Domain )
	 	- 3601xxyy  PSC DLL ( French Domain ) 
	 	- 3602xxyy  NULL protocol ( French Domain ) 
	 	- 3605xxyy  Pinpad DLL 
	 	- 3606xxyy  Crypto DLL 

/Multiice
	- startc.inc script file to be run at ADW invokation ( startc.inc replaces cold.inc ) 
	- eft30.cfg script file to be run at Multi Ice server invokation
	- rvd.inc   script file to be run at RVD invokation 

/Sample/sdt  : an application skeletton and a project file for SDT tools appli1.prj
	- /DebugRel resulting files for Project Manager
	- /inc  include files
	- /gen	final files for SST generation & LLT loading 
	- /src  source code of sample application and a makefile 
	- /Obj  M2OS libraries for SDT 

/Sample/rvd : an application skeletton and a project file for RVCT/RVD tools appli2.prj
	
	- /inc  include files
	- /gen	final files for SST generation & LLT loading 
	- /src  source code of sample application and a makefile 
	- /Lib/arm  M2OS libraries for RVCT 

/Customise
	- /SDT files to generate a DLL language with SDT tools
	- /RVD files to generate a DLL language with RVCT/RVD tools
 

/Doc : all documentations at PDF format 

/Trace : Trace tool 
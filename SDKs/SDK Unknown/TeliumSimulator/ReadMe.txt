
Content of the package :
------------------------

- The file ParamSimulatorTelium1.txt is the parameter file for Telium 1 products
- The file ParamSimulatorTelium2.txt is the parameter file for Telium 2 products
- The file 813773xxxx.BIN is the Simulator software NOT SIGNED,
- The file eft30.lib is the library to link with on Ingedev
- The file SimulEft30.lib is the library to link with on Visual
- The file vc90.pdb contains visual project information, it is here to avoid warning on Visual
- The file SimuCst.txt is for future use

Before loading the software on the terminal, you have to sign the BIN file, with adding the schemes, by using SST (Telium 1) or SAT (Telium 2). 
For more details about the way to do that, please read the user guides of these tools.

To be compliant with version of Ingedev that manage the "Download simulation App" feature, the following files are delivered :
- The file 813773xxxx.SGN is the Simulator signed mock-up for Telium 1 
- The file 813773xxxx.ADF is the parameter file for Telium 1 
- The file 813773xxxx.mXX are the catalogue files for Telium 1 
- The file 813773xxxx.AGN is the Simulator signed mock-up for Telium 2 
 

The list of functions simulated is available in the file FunctionsSimulated.txt


Naming convention of the versions of the simulator :
----------------------------------------------------
XX.YY are official versions
XX.YY.ZZ are intermediate versions


Compatibility:
--------------
Used with Visual, it is compatible with versions equal or newer than version 2005



          =============================================================
          |||||||||||||||| WHAT'S NEW IN THE PACKAGE ? |||||||||||||||| 
          =============================================================


Version 02.07 (2010/02/24)
-------------

This version of the simulator is generated with:
- GSIM 1.14

It is based on :
- manager 55.00 
- system 08.44

- FT6654 : it was not possible to print some fonts using pprintf8859()



Version 02.06 (2009/12/23)
-------------

This version of the simulator is generated with:
- GSIM 1.14

It is based on :
- manager 55.00 
- system 08.42

- FT5385 : Graphical functions were not managed

- Update of makefile for IngedevLib API  regarding the new families

- FT5504 : Parameters of SEC_DukptLoadInitialKey could be null

- Correction of m39 catalogue



Version 02.05 (2009/10/22)
-------------

This version of the simulator is generated with:
- GSIM 1.14

It is based on :
- manager 54.00 
- system 08.33

- fork has not to be simulated (due to conception) : it is removed (it resetted the terminal when called)

- NumPrimitive of the structure S_DECODE_FUNCTION on 2 bytes instead of 1

- Syntax warning correction in array S[] in src_moteur/des.c

- Removed warning in supplied files

- Beginning of FT5379 : Files supplied splitted

- Simulation.dll has to display the function names which are in SimuCst.txt to avoid confusion of function 
	number between 2 SDK deliveries

- fwrite : buffer to write becomes IN_ONLY
	-> temporary Version 2.4.1 generated

- SEC_ExecScheme : pt_Execsch->cbResident was not transfered
	-> temporary Version 2.4.2 generated

- Optimization for ServiceCall simulated function : long buffer are transfered only if needed

- Function Saisie_Alphanumerique now not automatically generated to allocate memory for sub-structure

- Correction of serialisation of T_SEC_DATAKEY_ID

- Correction of serialisation of SEC_ExecScheme

- FT5283 : correction for functions in rtctimer (including correction of ReadDateBooster, FT5862)

- FTXXXX : Correction of Aschex

- Added simulation for service custom message (on simulateur engine only)

- new families for new files from manager

- Correction of PSQ_Donner_noserie (output was 0 all the time)

- catalogue m39 added


Version 02.04 (2009/08/06)
-------------

This version of the simulator is generated with:
- GSIM 1.14

It is based on :
- manager 53.02 
- system 08.12

- FT4318 : management of tags IN_ONLY/OUT_ONLY in __inet_aton 


- FT3926 : management of tags IN_ONLY/OUT_ONLY in functions in SSL_.h with const in parameters

- IN_ONLY/OUT_ONLY added for functions :
	PSQ_DonnerInfosReseauXXX
	is_iso1, is_iso2, is_iso3

- FT5252 : Correction of Binhex : parameters of the tag was inverted 
	-> temporary Version 2.3.1 (=2.99) generated

- FT5254 : Correction of oem_public.h et libgr.h : tags IN_ONLY add on input parameters
	-> temporary Version 2.3.2 (=2.98) generated

- Correction of BUF_DES_scalaire : in the case of a string is the return of a function, the 0 terminal could be forgotten
	For example, that could occur in Get_AppliName

- FT5262 : IAPP_SchGetSync reseted the terminal : it was a problem of automatic generation of CopyFile 
	CopyFile now supplied
	-> temporary Version 2.3.3 generated

- FT1378 : Message added if a fioctl non supported

- Management of fioctl functions is now OK

- Change of fonts used in the start-up screen

- Correction of Binasc : parameters of the tag was inverted 

- Correction of the tag of SEC_PinEntry : IN_ONLY and OUT_ONLY were mismanaged

- Correction of the tag of SEC_Iso9564 : Management of all the formats

- Value of the length of the third parameters of the functions is_iso_X

- The file SimuCst.txt is added for future use


Version 02.03
-------------

This version of the simulator is generated with:
- GSIM 1.14

It is based on :
- manager 53.00 
- system 08.09

Information about this version :

	FT4806 : Final integration of GSIM automatic tool to generate the source code of the simulator:
		Some functions or structures are not generated automatically due to bug in GSIM :
			StructScreenExtended
			SetBitmap
			_SetBitmap
			DisplayBitmap
			_DisplayBitmap
			T_Version
			T_Segment
			remote_download
			remote_downloading
			remote_downloading_from_manager
		Simu.h and Simumain.c are now in the GSIM working directories
		Functions coming back to the simulation due to libraries up to date : _DrawFontUnicode, DrawFontUnicode, ObjectGetSize, ObjectRemoveByFamily, DllUnlinkByType

	FT5197 : DrawExtendedString used to display the same startup on ICT250
		



Version 02.02
------------

This version of the simulator is generated with:
- GSIM 1.14

It is based on :
- manager 53.00 
- system 08.07

Information about this version :
	- Corrections of bug reported in the version 02.01 which was only a version for validation
	- Corrections due to bugs found in GSIM 1.x
	- Some improvement are waited with the next version of GSIM



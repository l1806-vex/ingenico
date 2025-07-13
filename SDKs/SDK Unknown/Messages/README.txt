--------------------------
 MANAGER AND DLL MESSAGES 
--------------------------

Manager’s messages and DLL’s messages can easily be modified by loading the EFT MSG file in the terminal.

EFT.bat builds a file named EFT.MSG with the manager’s messages and HWCNF DLL’s messages.
The name EFT.MSG (and also EFT.SGN) is reserved for the manager customization.
The english.h, french.h, HWCNFFrench and HWCNFEnglish files are given in example in the include of the SDK.

WARNING: FON files used to display/print your new messages must be loaded in the terminal and contain all 
the polices used by the manager (_dMEDIUM_, _dSMALL_, _pNORMAL_, _pBOLD_…)

The EFT.bat given in example builds the EFT.MSG file that contains english messages and some russian messages for
the manager and the HWCNF DLL.

To generate the EFT.MSG file, please perform the following steps.

1- Copy the folowing files in the tools\MSG tool directory
	EFT.bat, MANAGERRussian.h, HWCNFRussian.h (from Component\Messages directory)
	english.h and HWCNFEnglish.h (from SDK\inc directory) 

2- Use EFT.bat file to build the EFT.MSG messages file

3- Sign the EFT.MSG file

4- Load EFT.SGN and EFT.PDF file in the terminal

5- Load the font files in the terminal.
	Load ISO8859-5 font file in the terminal (ISO5.SGN and ISO5.PDF from Component\Fonts directory).
	This font file is used to display and print Russian messages.








 


---------------
 MESSAGE SAMPLE
---------------

This sample shows how to use new messages functionalities provided by the manager.
This sample is an application that uses its local messages in english (English.c file)
and customised messages provided by a messages file loaded in the terminal (SAMPLEMSG file)

To use this sample, please perform the following steps.

1- Build the local messages file and the MSG file to load in the terminal

The "Messages" folder contains:
	. SampleLocalEnglish.h file
	. SampleCustArabic.h, SampleCustEnglish.h, SampleCustGerman.h and SampleCustRussian.h files
	. Sample.bat
	
Put this files in the "tools\MSG tool" folder of the SDK and use Sample.bat that will automatically generate:
	. English.c and MessagesDefinitions.h files to include in the application (Src folder)
	. SAMPLEMSG.MSG to sign before loading it in the terminal

2 - Load the sample, the MSG file and the font files in the terminal.

Compile and load the sample in the terminal.
Sign and load the MSG file in the terminal.
Load ISO1 (English and German) ISO5 (Russian) and ISO6 (Arabic) fonts (from Component\Fonts folder) in the terminal.








 


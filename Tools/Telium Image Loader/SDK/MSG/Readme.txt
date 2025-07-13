*******************************************************************
*      Steps To create Custom Message File fro ImageLoader        *
*******************************************************************

1- Edit Custom_MESSAGES.bat
2- Enter the name of the message file.
3- Edit line "SST_DIR=C:\Program Files\TELIUM Tools\SST30" to put the correct SST Path
4- Replace Mockup.V03 certificate file with the certicate used for signing application : for SST or SAT part.
	echo CertificateFile=Mockup.V03>> "%SST_CONFIG_FILE%"
	echo CertificateFile=Mockup.V03>> "%SAT_CONFIG_FILE%"
5- Replace used code "00000000" for signature for both SAT and SST:
	"%SST_DIR%\SST30.exe" 2,%SST_CONFIG_FILE%,00000000
	"%SAT_DIR%\SAT.exe" 4,%SAT_CONFIG_FILE%,00000000

6- Save Edited bat file
7- Execute the Custom_MESSAGES.bat

Signed Message files can be located on Signed/SST And Signed/SAT Folder
	


'*******************************************************************************
'* BuildPackage.vbs
'*------------------------------------------------------------------------------
'* Visual Basic Script (VBS) used to generate packages for download operations.
'*******************************************************************************

'Don't stop if an exception is raised. We'll display an error
'message ourselves.
On Error Resume Next

Dim pkg, objApp, objFSO
Dim fso

packagerMinVersion = "5.2.8"

Set objArgs = WScript.Arguments
strPackageName = ""
strBinariesPath = ""
strBinaryCfgName = ""
strDataRootPath = ""
If (objArgs.count < 3) Then
    msgLine1 = "usage: buildPackage {package_name} {binaries_path} {binary_cfg_name} [{data_roo_path}]" & Chr(13) & Chr(13)
    msgLine2 = "package_name:    The name of the package" & Chr(13)
    msgLine3 = "binaries_path:   The path where binaries are generated (relative from project root)" & Chr(13)
    msgLine4 = "binary_cfg_name: The name of the configuration binary file" & Chr(13)
    msgLine5 = "data_root_path:  The optional data root directory path (not present if no data, relative from project root)"
	WScript.Echo(msgLine1 & msgLine2 & msgLine3 & msgLine4 & msgLine5) 
	WScript.Quit(-1)
Else
	strPackageName = objArgs(0)
	strBinariesPath = objArgs(1)
	strBinaryCfgName = objArgs(2)
	strDataRootPath = objArgs(3)
End If

Set WshShell = WScript.CreateObject("WScript.Shell") 

Set pkg = CreateObject("IngPackagerAutomation.Application")
If pkg Is Nothing Then
	WScript.Echo("IngPackager error: cannot create Packager object. Please make sure that IngPackager is installed.")
	WScript.Quit(-1)
End If

version = pkg.GetVersion()
If version < packagerMinVersion Then
	WScript.Echo("IngPackager error: you are using version " & version & " of IngPackager. At least version " & packagerMinVersion & " is required.")
	WScript.Quit(-1)
End If

Set objFSO = CreateObject("Scripting.FileSystemObject")
If objFSO Is Nothing Then
	WScript.Echo("IngPackager error: cannot create File System object!")
	WScript.Quit(-1)
End If

pkg.Visible = FALSE
pkg.PackageDescription = ""
pkg.Technology = "Unicapt32"

pkg.PackageLocation = WshShell.CurrentDirectory & "/" & strBinariesPath & "/" & strPackageName

'Delete the package if already exists.
'This prevents from downloading a invalid package.
Set fso = CreateObject("Scripting.FileSystemObject")
If fso.FileExists(pkg.PackageLocation) Then
	Set packageFile = fso.GetFile(pkg.PackageLocation)
	packageFile.Delete()
End If

'Add code files to package.
strFileName = WshShell.CurrentDirectory & "/" & strBinariesPath & "/" & strBinaryCfgName
iResult = pkg.AddCodeFile(strFileName)
If (iResult <> 0) Then
	WScript.Echo("IngPackager error: cannot add code files (configuration file '" & strFileName & "'): " & pkg.GetErrorMsg(iResult) & ".")
	pkg.close()
	WScript.Quit(-1)
End If

'Add optionally data files to package.
If (strDataRootPath <> "") Then
    Set objApp = pkg.GetApplicationByConfig(strBinaryCfgName)
    If objApp Is Nothing Then
	    WScript.Echo("IngPackager error: cannot get Application object. Please make sure that Application is present.")
		pkg.close()
	    WScript.Quit(-1)
    End If
	
	'Add all data from data root directory
	iResult = objApp.AddDataDirectory(WshShell.CurrentDirectory & "/" & strDataRootPath, "")
	If (iResult <> 0) Then
		WScript.Echo("IngPackager error: cannot add data files (directory '" & WshShell.CurrentDirectory & "/" & strDataRootPath & "'): " & pkg.GetErrorMsg(iResult) & ".")
		pkg.close()
		WScript.Quit(-1)
	End If
End If

'Create the package.
iResult = pkg.CreatePackage()
If (iResult <> 0) Then
	WScript.Echo("IngPackager error: cannot create package: " & pkg.GetErrorMsg(iResult) & ".")
	pkg.close()
	WScript.Quit(-1)
End If

pkg.close()

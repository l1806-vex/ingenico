'*******************************************************************************
'* BuildTeliumPackage.vbs
'*------------------------------------------------------------------------------
'* Visual Basic Script (VBS) used to generate Telium package for download.
'*******************************************************************************

'Don't stop if an exception is raised. We'll display an error
'message ourselves.
On Error Resume Next

Dim pkg, objApp, objFSO
Dim fso

packagerMinVersion = "6.2.0"

Set objArgs = WScript.Arguments
strPackageName = ""
strBinariesPath = ""
strT1CatalogFileName = ""
strT2CatalogFileName = ""
If (objArgs.count < 4) Then
    msgLine1 = "usage: buildTeliumPackage {package_name} {binaries_path} {T1_catalog_file_name} {T2_catalog_file_name}" & Chr(13) & Chr(13)
    msgLine2 = "package_name: The name of the package" & Chr(13)
    msgLine3 = "binaries_path: The path where binaries are generated (relative from project root)" & Chr(13)
    msgLine4 = "T1_catalog_file_name: The name of the Telium 1 catalog file ('<none>' if no Telium 1 catalog file)" & Chr(13)
    msgLine5 = "T2_catalog_file_name: The name of the Telium 2 catalog file ('<none>' if no Telium 2 catalog file)" & Chr(13)
	WScript.Echo(msgLine1 & msgLine2 & msgLine3 & msgLine4 & msgLine5) 
	WScript.Quit(-1)
Else
	strPackageName = objArgs(0)
	strBinariesPath = objArgs(1)
    strT1CatalogFileName = objArgs(2)
	strT2CatalogFileName = objArgs(3)
End If

Set WshShell = WScript.CreateObject("WScript.Shell") 

Set pkg = CreateObject("IngPackagerAutomation.Application")
If pkg Is Nothing Then
	WScript.Echo("IngPackager error: cannot create Packager object. Please make sure that IngPackager is installed.")
	WScript.Quit(-1)
End If

version = pkg.GetVersion()
If (version < packagerMinVersion) Then
	WScript.Echo("IngPackager error: you are using version " & version & " of IngPackager. At least version " & packagerMinVersion & " is required.")
	WScript.Quit(-1)
End If

pkg.Visible = FALSE
pkg.PackageDescription = ""
pkg.Technology = "Telium"

pkg.PackageLocation = WshShell.CurrentDirectory & "/" & strBinariesPath & "/" & strPackageName

'Delete the package if already exists.
'This prevents from downloading a invalid package.
Set fso = CreateObject("Scripting.FileSystemObject")
If fso.FileExists(pkg.PackageLocation) Then
	Set packageFile = fso.GetFile(pkg.PackageLocation)
	packageFile.Delete()
End If

If (strT1CatalogFileName <> "<none>") Then
    'Add Telium 1 catalog file to package.
    strFileName = WshShell.CurrentDirectory & "/" & strBinariesPath & "/" & strT1CatalogFileName
    iResult = pkg.AddTeliumCatalog(strFileName)
    If (iResult <> 0) Then
	   WScript.Echo("IngPackager error: cannot add Telium 1 catalog file '" & strFileName & "': " & pkg.GetErrorMsg(iResult) & ".")
	   pkg.close()
	   WScript.Quit(-1)
    End If
End If

If (strT2CatalogFileName <> "<none>") Then
    'Add Telium 2 catalog file to package.
    strFileName = WshShell.CurrentDirectory & "/" & strBinariesPath & "/" & strT2CatalogFileName
    iResult = pkg.AddTeliumCatalog(strFileName)
    If (iResult <> 0) Then
        WScript.Echo("IngPackager error: cannot add Telium 2 catalog file '" & strFileName & "': " & pkg.GetErrorMsg(iResult) & ".")
        pkg.close()
        WScript.Quit(-1)
    End If
End If

'Create the Telium package.
iResult = pkg.CreatePackage()
If (iResult <> 0) Then
	WScript.Echo("IngPackager error: cannot create package: " & pkg.GetErrorMsg(iResult) & ".")
	pkg.close()
	WScript.Quit(-1)
End If

pkg.close()

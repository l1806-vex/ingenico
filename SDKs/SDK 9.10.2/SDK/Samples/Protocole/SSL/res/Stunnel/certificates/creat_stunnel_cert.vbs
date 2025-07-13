' This scripts generates the hash name for the client cerificates 
' for openSSL ad Stunnel to have client authentication on the server
' side.
' Certificate must have extension .crt or .CRT 


Dim Files, File, objFSO, objFile
Dim str, FileName, FileNewName
Dim WshShell, oExec

Err.Clear
On Error Resume Next

'Get the path of the script
Set objFSO = CreateObject("Scripting.FileSystemObject")
strCurrentScript = WScript.ScriptFullName
Set objFile = objFSO.GetFile(strCurrentScript)
strParentFolder = objFile.ParentFolder

Set WshShell = CreateObject("WScript.Shell")

'Get all files in the folder
Set Folder = objFSO.GetFolder(strParentFolder)
Set Files = Folder.Files
if Files.Count <>0 then
  For Each File in Files
    FileName = File.name
    if (Right(FileName, 4) =".crt") or (Right(FileName, 4) =".CRT") then
      'We have a certificate file
      Set oExec = WshShell.Exec("openssl x509 -hash -noout -in " & FileName)  
      FileNewName =   oExec.StdOut.ReadLine & ".0"
      Set OldCertifFile = objFSO.GetFile(FileName)
      OldCertifFile.Copy(FileNewName)
      
    End if
  Next
End if

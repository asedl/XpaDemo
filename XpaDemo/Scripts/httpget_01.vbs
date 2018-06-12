Set Shell = WScript.CreateObject("WScript.Shell")
Set http = CreateObject("Microsoft.XmlHttp")
URL="https://www.magicsoftware.com/"

On Error Resume Next
http.open "GET", URL, False
http.send ""
if err.Number = 0 Then
     WScript.Echo http.responseText
Else
     Wscript.Echo "error " & Err.Number & ": " & Err.Description
End If
set WshShell = Nothing
Set http = Nothing

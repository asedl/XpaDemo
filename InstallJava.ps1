$url = "https://sdlc-esd.oracle.com/ESD6/JSCDL/jre/8u25-b11/jre-8u25-windows-i586.exe?GroupName=JSC&FilePath=/ESD6/JSCDL/jre/8u25-b11/jre-8u25-windows-i586.exe&BHost=javadl.sun.com&File=jre-8u25-windows-i586.exe&AuthParam=1541939669_7221bbd421a9c3f4f109d94fe4698c91&ext=.exe"
$output = "C:\Temp\jre-8u25-windows-i586.exe"
$start_time = Get-Date

try {
    $wc=new-object system.net.webclient
    $wc.downloadfile($url,$output)
}
catch [Net.WebException] {
    Write-Host $_.Exception.ToString()
  }


Write-Output "Time taken: $((Get-Date).Subtract($start_time).Seconds) second(s)"
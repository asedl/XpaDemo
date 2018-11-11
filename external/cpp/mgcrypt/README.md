# mgcrypt.dll

mgcrypt.dll is a UDF/UDP extension for Magic applications (all 32-Bit versions from v7 to latest Magic XPA) containing some functions 
required for security and encrption. At least that is what it is going to be because at the moment there is only a single function 
exported, which calculates the SHA-356 hash of a message and returns it in hexadecimal representation.

It's also just a wrapper around functionality from Crypto++ Library which is open source and freely distributable and available from here:
[Crypto++® Library 7.0](https://www.cryptopp.com/) . The project links this library statically so you do not need to download and install 
Crypto++ DLL if you have a mgcrypt.dll from releases. mgcrypt.dll you best copy to your Magic installation directory, that's where the 
runtime (MgxpaRuntime.exe for Xpa) resides. 
  
The Magic sample application is Xpa 3.3 and you can load that with the free Magic Xpa Single User edition, Magic UDP/UDF and/or 
CALLDLL function are however available in older versions as well (and preferred way of integrating external libraries). With Xpa you can do 
all this with Java or .NET instead. 


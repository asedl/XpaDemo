# Usage (in) and implementation of DLLs (for) Magic (general considerations)
Writing and using DLLs in Magic became lately a bit anachronistic and obsolete since there's sufficient support for .NET and Java now, they do however still work, performance is excellent and they work with all Magic versions (and probably always will). Those famous examples of DLLs which were (and partly still are) widely used in Magic applications which stopped working one day (GET.DLL and Hotfudge DLLs) only did this because they relied in parts on subclassing and hardcoded the Magic Windows classname, which MSE changes every once a while. 
  
Today you can still use DLLs and write DLLs for usage in Magic, just be sure about the Unicode issues since v10 uniPaaS and about multi-threading issues since there is multi-threaded Magic engines (Enterprise server in background mode) and parallel programs. A recompilation your DLLs then will require when Magic provides a 64-But version and its not clear if they ever will.

Here's some general considerations regarding functionality residing in (Magic) DLLs and their usage. 

 
## parameters / buffers
Functions which do return data and do not explicitely state that they will allocate the required memory require you to pass a buffer of 
sufficient length and will have an additional parameter where you have to specify the size (maximum number of Bytes which can be safely 
written to this buffer). If a mgcrypt function requires such a buffer (like a 64 Bytes buffer for the hexadecimal representation of a SHA-246 hash) 
and you pass a Magic variable which provides less space (like by passing a Magic variable which is declared as Alphanumeric 10) your Magic Runtime 
most likely will simply crash (unless you specified 10 as maximum length parameter too, in which case the function would simply do nothing 
but returning an error code telling that buffersize is insufficient)  

In older Magic versions (can't tell which and if it has been fixed in all eDeveloper v9 versions already) there was a problem when you 
declared a Magic variable with f.i. Virtual A := Alphanumeric 64 and then did not init/update that variable to anything or something shorter than 64 Bytes. 
Magic then eventually passed a buffer with maximum length = Len(Trim(A)), which has insufficient length and might result in a crash. 
To be on the safe side you should use Magic Fill function to ensure sufficient buffer length by Init or Update before actually calling the 
UDF/UDP function which will write to that buffer; Update/Init A = Fill('*', LEN(A)) or Update/Init A = Fill('*', VAL(TRIM(VARPIC('A'VAR')),'') . If the mgrypt.dll function states that it will allocate the required buffer itself, you do not have to do this.

## Unicode / ANSI
mgcrypt.dll is compiled Multibyte, does however support Unicode for those fuctions which need that and which do have Unicode parameters. 
In Magic, Unicode parameters were not supported before v10 (uniPaaS). If a specific function in mgcrypt.dll deals with character data there will be typically two functions then were the Unicode version ends with letter W (wide character) and the None-Unicode (ANSI) version ends 
with letter A.  Encryption and hashing is mostly about binary data and the parameters are byte arrays. In Magic that's a Blob of Type Binary and the Magic type specifier for a Blob parameter is 'T'. 
  
## Parameter types / return values
For Magic UDF/UDP functionality you do not need to tell Magiuc what the parameter types are, when you invoke a function from a UDF/UDP Dll 
because those DLLs export a special function named MAGIC_BIND from where Magic can lookup the function and read the parameter types but its 
good to know what the type specifiers are. You need them if you call a "regular" DLL (not having a MAGIC_BIND function) in order to specify 
parameter types and type of return value.

Magic Type specifier
A | Alphanumeric (ANSI), Pointer to char
U | Alphanumeric (Unicode), Pointer to wchar_t
B | Blob (Pointer to Blob)
T | Structure (Pointer to Structure /Buffer)
2 | Short (16 Bit signed integer)
4 | Long (32-Bit signed integer)
L | Pointer to Long (32-Bit integer value)
D | Double 
0 | void (can only be used for return value)

The Magic "signature" of a function then is a string with one letter with the type specifier for each parameter followed by the type specifier of the return value of the function. If the function has no return value you need to specify that explicitely by using '0' 
(void) for the return value. Magic signature of a C function "char* myfunc (char* pText, wchar_t* pUnicodeText, long* pBufflen) f.i. is: 'AULA'

When the parameter is of a pointer type, the DLL function can actually change the value of the Magic variable passed to the DLL function, that does however only work for UDF function and (Invoke) UDP operation. If you have a DLL function residing in a "regular" DLL which changes parameters you can invoke that as well witrh UDF/UDP, you just have to prefix the module name with an '@' character and pass a Magic type specifier (function signature) as first parameter.   



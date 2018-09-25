# mgcrypt.dll
  
  
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
UDF/UDP function which will write to that buffer; Update/Init A = Fill('*', LEN(A)) or Update/Init A = Fill('*', VAL(TRIM(VARPIC('A'VAR')),'') 

If the mgrypt.dll function states that it will allocate the required buffer itself, you do not have to do this.

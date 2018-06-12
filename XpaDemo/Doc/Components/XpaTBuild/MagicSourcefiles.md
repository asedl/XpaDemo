some notes regarding the Magic "Source" files ...

# Timestamps
Plenty of elements in Magic source file do have timestamp information, like the following element which is from a program header and where 
Magic stores date and time of the last modification of that program  
``` Magic XPA
<LastModified _date="736848" _time="37074" date="03/06/2018" time="10:17:54"/>
```
date := (gregorian) date of last modification in european format DD/MM/YYYY  
time := time of modification (UTC)  
_date := date of last modification in seconds since year 0 (not counting leap-days)  
_time := "Unix time" (seconds passed since midnight) (UTC)  
  
_date/_time is the internal Magic date/time format which is also used when you use Magic datatypes Date/Type in Magic programs and which is persisted to a database 
"as is" as numeric values when you use the native Magic storage tye and don't tell Magic to do differently by changing the storage type or SQL type.  

You can use https://www.epochconverter.com/seconds-days-since-y0 to convert Magic's internal date/time values and to get some more information about the 
calendar systems, Unix epoch time, ...  





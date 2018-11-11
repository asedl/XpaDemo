# Dockerfile for XpaDemo project

# For Magic XPA (Windows version) we need the windowservercore ....
FROM microsoft/windowsservercore

MAINTAINER  Andreas Sedlmeier <sedlmeier@hotmail.com>

COPY . c:/XpaDemo

# Install and start Microsoft IIS which we do need for some samples ...
RUN dism /online /enable-feature /all /featurename:iis-webserver /NoRestart
RUN echo "Hello World - Dockerfile" > c:\inetpub\wwwroot\index.html

# Install Java 8 (32-Bit) .....
ENV JAVA_HOME=C:\\XpaDemo\\bin\\jre1.8.0_192
RUN setx /M PATH %PATH%;%JAVA_HOME%\bin

# Install .NET 4.7.2
RUN powershell Invoke-WebRequest -Uri "https://download.microsoft.com/download/6/E/4/6E48E8AB-DC00-419E-9704-06DD46E5F81D/NDP472-KB4054530-x86-x64-AllOS-ENU.exe" -OutFile dotnet-framework-installer.exe & \
    .\dotnet-framework-installer.exe /q & \
    del .\dotnet-framework-installer.exe

# ngen .NET Fx
ENV COMPLUS_NGenProtectedProcess_FeatureEnabled 0
RUN \Windows\Microsoft.NET\Framework64\v4.0.30319\ngen update & \
    \Windows\Microsoft.NET\Framework\v4.0.30319\ngen update

WORKDIR c:/XpaDemo/bin/Xpa

RUN powershell.exe
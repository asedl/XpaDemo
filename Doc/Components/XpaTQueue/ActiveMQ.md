# XpaTQueue & Apache ActiveMQ

## Installation/Configuration
You can download Apache ActiveMQ from the (ActiveMQ website)[<http://activemq.apache.org/download.html>]. Distribution is a Zipfile which you can extract to a directory of your choice. Minimum required Java version is Java 8, that you should have installed before. For more detailled installation instructions check the Apache documentation. You can run ActiveMQ as standalone application started from command line or install it as a Windows service.  

XpaTQueue basically does not need to know where ActiveMQ is installed, some programs may however check environment variable ACTIVEMQ_HOME in order to find the installation and it's configuration files.  

## Some useful commands ...
### Starting ActiveMQ
cd %ACTIVEMQ_HOME%
bin\activemq start  

## Stopping ActiveMQ
cd %ACTIVEMQ_HOME%
bin\activemq stop  

## Using the administative interface
URL: http://localhost:8161/admin/
Login: admin / admin
(until you changed the defaults from installation)

## Examples
Send a text message with content obtained from an url:  
bin/activemq producer --payloadUrl http://activemq.apache.org/schema/core/activemq-core.xsd --messageCount 1

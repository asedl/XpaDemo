# Magic XpaDemo & Docker

One of the goals of XpaDemo Project is to get some stuff work with Docker (docker, docker-compose) and Kubernetes. Everything on Windows, resp. 
with Windows containers because only the free Magic Xpa Single User edition can be used in this open source project. Having a Linux version of 
Magix Xpa as an option would make all this stuff a lot easier.  
  
Actually Magic Software does maintain docker repositories for Magic Xpa 3.3 (Linux) and Magic Xpa 4.0 (Linux) in the Docker Store: https://store.docker.com/profiles/magicsoftware  
There is however no documentation whatsover (basically not even a hint of any kind if these images originate from MSE at all). You can pull these images  
and peek into them. Running them will be an issue because they do not contain license files.  

While running Magic Xpa (Single User) in a Windows container with Docker for Windows is actually only a small challenge, running a Windows container with a Magic Xpa 
application on Kubernetes will be a rather big challenge. Windows containers and Kubernetes is (still) quite an issue anyway and in order to actually 
profit from a Kubernetes deployment the Magic applications (services) will have to be enriched by stuff, which will require some "tweaking":
- Infrastructure endpoints (for liveness- and readyness-probes and metrics)
- Logging to STDOUT and STDERR / Console  

Logging will be redirected to a Log-Provider (f.i. Logstash - Elastic - Kibana)  


## Current status of XpaDemo & Docker
Not that much yet. There's a sample dockerfile absed on windowsservercore which basically simply loads the complete project in the container and starts  
a Magic Xpa application - which then does nothing and actually (just after a few seconds simply crashes). We hope to be able to provide something 
more featurerich soon :)


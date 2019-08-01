# Magic XpaDemo & Docker

Magic XpaDemo is also about some experiments with Magic Xpa and container technology, namely Docker. In the project's root folder 
you will find a Dockerfile which is used to build a Docker image with Magic XPA 3.3 (Single User) edition on base of a windows/servercore image of Microsoft. 

Another option we do not have in this project, there's no freely available Magic Linux versions which we could use instead so that we can build Linux containers instead. 

If you try to build the Docker image of this project be sure to switch your Docker for Windows to Windows containers before, you cannot build/run Windows containers on MS Windows if the Docker for Windows is configured for Linux containers. 

---
  
MSE (Magic Software Enterprises) did push some docker repositories for Magic Xpa 3.3 (Linux) and Magic Xpa 4.0 (Linux) to dockerhub. You can find them here in the Docker Store: https://store.docker.com/profiles/magicsoftware  
There is however no documentation or anything which would give insight regarding public use of these images and if you do not have a license for Magic on Linux you probably wont get run anything based on these containers anyways.  


## Current status of XpaDemo & Docker
Not that much yet. There's a sample dockerfile based on windowsservercore which basically simply loads the complete project in the container and starts  
a Magic Xpa application - which then does nothing and actually (just after a few seconds simply crashes). We hope to be able to provide something 
more featurerich soon but basically Docker withe Windows containers is not much fun so XpaDemo project basically waits for a sponsor in order to get a Linux license for Magic :)  

## Other stuff in XpaDemo related to Docker
There's usecases wher it makes sense to route Magic http requests thru a proxy in order to mitigate issues with Magic's TLS support and other security things. 
A description of such an environment can be found here: [Mitigate Magic TLS issues with a proxy setup](https://github.com/asedl/XpaDemo/blob/master/Doc/Samples/XpaTHttp/Mitigate_Magic_TLS_Issues.md). 




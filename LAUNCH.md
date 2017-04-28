# Instructions for running the server application

## Windows

1. Copy these DLLs into the application executable's directory:  
      `PocoFoundation(d).dll`  
      `PocoUtil(d).dll`  
      `PocoNet(d).dll`  
      `PocoXML(d).dll`  
      `PocoJSON(d).dll`  
	  
	They are located in the `PocoBase/bin/` directory, where `PocoBase` is your Poco Libraries base directory.
> DLLs with the `d` suffix are needed for running application built in _Debug_ configuration.
      
2. Copy the `WGCServer.properties` file from `config/` directory into the application executable's directory.  

      __NOTE:__ This config file __must__ have the same name as the executable file. Though, you can omit the `d` suffix, if the application          was built in _Debug_ configuration and has this suffix in its name.

> This configuration file contains configuration of the server application, including:
> * _server port number_ - default: 8080,
> * _the root directory of all web client's files_ - the server exits if not given.


## Linux

1. Copy the required dynamic libraries into the application executable's directory.

2. Copy the `WGCServer.properties` file from `config/` directory into the application executable's directory.  

      __NOTE:__ This config file __must__ have the same name as the executable file. Though, you can omit the `d` suffix, if the application          was built in _Debug_ configuration and has this suffix in its name.

> This configuration file contains configuration of the server application, including:
> * _server port number_ - default: 8080,
> * _the root directory of all web client's files_ - the server exits if not given.
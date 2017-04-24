## Visual Studio Project's Properties Configuration

#### 0. Install required tools and libraries:
* __[PocoLibrary](https://pocoproject.org/download/index.html "@pocoproject.org")__ 
  Version we used Poco 2.7.13 32 bit.
* [__Boost.Test__](http://www.boost.org/ "@www.boost.org")
* [__SCons__](http://scons.org/ "@scons.org")

  During the instalation I had a few errors. Some of then: 
    I coudn't install Poco (1.7.8p2) 64 bit version, so we used 32 bit version. 
    SCons requires [Python](https://www.python.org/downloads/ "@python.org") 2 not 3. We installed 2.7.13.
    SCons 2.7.13 is using Visual C++ 2015 compiler, so it is possible you need to install [Visual C++ 2015 Build Tools](http://landinghub.visualstudio.com/visual-cpp-build-tools "@landinghub.visualstudio.com")

#### 1. Change the values of (or create) these 2 macros:
* __PocoBase__ 
* __WGCProjectBase__

__PocoBase__ should point to the Poco C++ Libraries' base directory.  
__WGCProjectBase__ should point to the root directory of this repo on your local machine.

You can do it at  
_Property Manager > WGCServer > {Debug or Release}|{Win32 or x64} > Microsoft.Cpp.{Win32 or x64}.user > Common Properties > User Macros_.  

Choose from options in curly brackets (`{}`) depending on your build configuration and platform.

#### 2. Verify that these additional paths to the following options exist:

_WGCServer Property Pages > Configuration Properties_:
* _\> C/C++ > General > Additional Include Directories_:  
 `$(WGCProjectBase)`  
 `$(PocoBase)\Foundation\include`  
 `$(PocoBase)\Util\include`  
 `$(PocoBase)\Net\include`  
 `$(PocoBase)\JSON\include`

* _\> Linker > General > Additional Library Directories_:  
	`$(PocoBase)\lib`

Separate these entries by semicolons (;).

__NOTE:__ Specify this configuration for the exact same _Configuration_ & _Platform_ you are building for.

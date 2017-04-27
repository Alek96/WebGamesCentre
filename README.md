# WebGamesCentre
_A project for ZPR ('Advanced C++ Programming') classes at WUT_  
_Project title: Gra sieciowa - szachy_

Hosted game: **chess**.

## External Dependencies
This project uses the [Poco C++ Libraries][pocoproject] so, in order to get it working, you have to download and build Poco Libraries. Currently, the _Basic Edition_ is fully sufficient. In future, however, new features may be available (such as the use of TLS/SSL) which, if enabled at compilation, will require the _Complete Edition_ with its own external dependencies.  

Version of libraries used in this project: 1.7.8p2.

__Future possibility:__ To make the process of running the app from the ground up simpler, the use of a software container platform, such as Docker, is considered.

## Building
You can build the main application (server) and tests in 2 ways:
* using SCons
* using Visual Studio solution/project

### SCons
When using SCons, just type `scons` in console from the project's root directory.
You can also type `scons -h` to see available options.
Scons puts built executable files into _VSProject/Debug_ or _VSProject/Release_ dir for _Debug_ and _Release_ configurations respectively.  
This option works on both Windows and Linux (and possibly also others, but wasn't tested) systems.  

To use this option, first you have to install SCons on your system. You can get it from here: [SCons](http://scons.org/pages/download.html "download SCons"). Note that SCons requires Python version 2, not 3. You can get it from here: [Python](https://www.python.org/downloads/ "download Python"). Also note that the SCon's Windows installer can find only the 32-bit version of Python. 
SCons 2.5.1 uses Visual C++ 2015 compiler or older, so it is possible you need to install [Visual C++ 2015 Build Tools](http://landinghub.visualstudio.com/visual-cpp-build-tools "Visual C++ 2015 Build Tools").

Version of SCons used in this project: 2.5.1.  
Version of Python used: 2.7.13.

### Visual Studio solution/project
When using Visual Studio solution/project, you can build the app and tests from within Visual Studio or using MSBuild toolchain. This option works only on Windows systems.   
__In both cases it is important you read the VSProject's [README](VSProject/README.md).__

#### From within Visual Studio
In Visual Studio make sure that `Configuration Type` is set to `Application (.exe)` in project's Property Pages.
Next choose the configuration (Debug/Release) and platform(x86/x64) you want to build for, and build solution/project.  
You can build the whole solution - this will build both application and tests, or just single project (application or tests).

#### Using MSBuild toolchain from command line (no need to install Visual Studio)
Open console and go to directory:
* VSProject/WGCServer  --  for building application
* VSProject/WGCServerTests  --  for building tests

Then type `msbuild *.vcxproj` (where * is WGCServer or WGCServerTests) to build in _Debug_ configuration.  
Or type `msbuild /p:configuration=release *.vcxproj` to build in _Release_ configuration.

## Running application
The app executable can be found at `VSProject/${Configuration}` (when building with SCons or Visual Studio) or at `VSProject/WGCServer/${Configuration}` (when building with MSBuild toolchain from console), where `${Configuration}` is the build configuration you chose (_Debug_ or _Release_).  
__Important: see note below before running__

## Running tests
The tests executable can be found at `VSProject/${Configuration}` (when building with SCons or Visual Studio) or at `VSProject/WGCServerTest/${Configuration}` (when building with MSBuild toolchain from console), where `${Configuration}` is the build configuration you chose (_Debug_ or _Release_).

__NOTE: Before you run your built executables, fulfill the steps specified in [LAUNCH](LAUNCH.md).__

---
Authors: [Przemysław Poljański](https://github.com/Peperzastey "@Peperzastey"), [Aleksander Zamojski](https://github.com/Alek96 "@Alek96")

[pocoproject]: https://pocoproject.org/ ("pocoproject")

# WebGamesCentre
_A project for ZPR ('Advanced C++ Programming') classes at WUT_  
_Project title: Gra sieciowa - szachy_

Hosted game: **chess**.

## External Dependencies
This project uses the [Poco C++ Libraries][pocoproject] so, in order to get it working, you have to download and build Poco Libraries. Currently, the _Basic Edition_ is fully sufficient. In future, however, new features may be available (such as the use of TLS/SSL) which, if enabled at compilation, will require the _Complete Edition_ with its own external dependencies.  

Version of libraries used in this project: 1.7.8p2.

__Future possibility:__ To make the process of running the app from the ground up simpler, the use of a software container platform, such as Docker, is considered.

## Building (SCons)
Just type `scons` in console from the project's root directory.  
You can also type `scons -h` to see available options.  
Works on both Windows and Linux (and possibly also others, but wasn't tested) systems.  

Before you can build the project, you have to install SCons on your system. You can get it from here: [SCons](http://scons.org/pages/download.html "download SCons"). Note that SCons requires Python version 2, not 3. You can get it from here: [Python](https://www.python.org/downloads/ "download Python"). Also note that the SCon's Windows installer can find only the 32-bit version of Python. 
SCons 2.5.1 uses Visual C++ 2015 compiler or older, so it is possible you need to install [Visual C++ 2015 Build Tools](http://landinghub.visualstudio.com/visual-cpp-build-tools "Visual C++ 2015 Build Tools").

Version of SCons used in this project: 2.5.1.  
Version of Python used: 2.7.13.

#### Note about VSProject
Visual Studio project files were removed from this repository and also aren't planned to be provided in the future.  
From now on, the only officially supported build method is by using the SCons build tool with scripts provided in this repository.  
SCons is cross-platform, so it shouln't render any potential problems.

---
Authors: [Przemysław Poljański](https://github.com/Peperzastey "@Peperzastey"), [Aleksander Zamojski](https://github.com/Alek96 "@Alek96")

[pocoproject]: https://pocoproject.org/ ("pocoproject")

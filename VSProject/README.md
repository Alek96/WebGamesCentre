## Visual Studio Project's Properties Configuration

#### 1. Change the values of (or create) these 2 macros:
* __PocoBase__, 
* __WGCProjectBase__.

__PocoBase__ should point to the Poco C++ Libraries' base directory.  
__WGCProjectBase__ should point to the root directory of this repo on your local machine.

You can do it at  
_Property Manager > WGCServer > {Debug or Release}|{Win32 or x64} > Microsoft.Cpp.{Win32 or x64}.user > Common Properties > User Macros_.  

Choose from options in curly brackets (`{}`) depending on your build configuration and platform.

#### 2. Add these additional paths to the following options:

_WGCServer Property Pages > Configuration Properties_:
* _\> C/C++ > General > Additional Include Directories_:  
 `$(WGCProjectBase)`  
 `$(PocoBase)Foundation\include\`  
 `$(PocoBase)Util\include\`  
 `$(PocoBase)Net\include\`  
 `$(PocoBase)JSON\include\`

* _\> Linker > General > Additional Library Directories_:  
	`$(PocoBase)lib\`

Separate these entries by semicolons (;).

__NOTE:__ This instruction assumes you put a (back)slash at the end of __PocoBase__'s path.  
__ALSO NOTE:__ Specify this configuration for the exact same _Configuration_ & _Platform_ you are building for.

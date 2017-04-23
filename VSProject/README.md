## Visual Studio Project's Properties Configuration

All you need to do is change the values of these 2 macros:
* __$(PocoBase)__, 
* __$(WGCProjectBase)__.

__PocoBase__ should point to the Poco C++ Libraries' base directory.  
__WGCProjectBase__ should point to the root directory of this repo on your local machine.

You can do it at _Property Manager > WGCServer > {Debug or Release}|{Win32 or x64} > Microsoft.Cpp.{Win32 or x64}.user > Common Properties > User Macros_,  
depending on your build configuration and platform.

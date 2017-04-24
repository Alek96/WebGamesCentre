#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment

import os.path

PocoBase = "C:\\Libraries\\poco-1.7.8p2\\"
WGCProjectBase= "C:\\Users\\Aleksander\\Documents\\GitHub\\WebGamesCentre"

print "Building Server"

env = Environment(TARGET_ARCH= 'x86')   # Create an environmnet

Headers = ['Foundation\\include' , 'Util\\include', 'Net\\include', 'JSON\\include']
headers = [os.path.join(PocoBase, x) for x in Headers]

#$(PocoBase)\Util\include;$(PocoBase)\Net\include;$(PocoBase)\JSON\include</AdditionalIncludeDirectories>]

env.Program(target = "server", source = WGCProjectBase + "/src/Server.cpp", CPPPATH = [WGCProjectBase] + headers, LIBS = ['PocoFoundationd.lib', 'PocoNetd.lib', 'PocoUtild.lib',
'PocoXMLd.lib', 'PocoJSONd.lib'	], LIBPATH = PocoBase + "\\lib" )

#import os.path
#filenames = [os.path.join(prefix, x) for x in filenames]

#<AdditionalIncludeDirectories>$(WGCProjectBase);$(PocoBase)\Foundation\include;$(PocoBase)\Util\include;$(PocoBase)\Net\include;$(PocoBase)\JSON\include</AdditionalIncludeDirectories>
#<AdditionalLibraryDirectories>$(PocoBase)\lib</AdditionalLibraryDirectories>

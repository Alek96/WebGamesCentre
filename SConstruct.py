#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment
import sys	#for detect system
import os.path

PocoBase		= 'C:\\Libraries\\poco-1.7.8p2'
WGCProjectBase	= 'C:\\Users\\Aleksander\\Documents\\GitHub\\WebGamesCentre'

print "Building: WGCServer"

env = Environment(TARGET_ARCH= 'x86')   # Create an environmnet for 32 bit version

platform = ARGUMENTS.get('OS', Platform())
print platform

LibS = ['']
# Add the Debug Flags if debug=1 is specified on the command line, this tends to be compiler specific
if ARGUMENTS.get('debug') != '0':
    env.Append(CPPDEFINES = ['DEBUG', '_DEBUG'])
    env.Append(CCFLAGS='/MDd')
    #env.Append(CCFLAGS=Split('/Zi /Fd${TARGET}.pdb'))
    env.Append(LINKFLAGS = ['/DEBUG'])
    variant = 'Debug'
    #env.VariantDir('VSProject/Debug/', 'src', duplicate=0)	#not working ???
    libS = Split('PocoFoundationd PocoNetd PocoUtild PocoXMLd PocoJSONd')
else:
    env.Append(CPPDEFINES = ['NDEBUG'])
    variant = 'Release'
    libS = Split('PocoFoundation.lib PocoNet.lib PocoUtil.lib PocoXML.lib PocoJSON.lib')


print "Building: " + variant

#src_files = ['src/scons_test.cpp', 'src/class_test.cpp']
#consider to use Glob('*.c')
src_files = Split('''src/PageRequestHandler.cpp
					 src/RequestHandlerFactory.cpp
					 src/Server.cpp
					 src/WebSocketRequestHandler.cpp''')

PocoHeaders = Split('''/Foundation/include
					   /Util/include
					   /Net/include
					   /JSON/include''')
PocoHeaders = [PocoBase + x for x in PocoHeaders]


t = env.Program(target = 'VSProject/Debug/WGCServer', 
				source = src_files, 
				CPPPATH = [WGCProjectBase] + PocoHeaders,
				#LIBS = Split('''PocoFoundationd 
				#				PocoNetd
				#				PocoUtild 
				#				PocoXMLd 
				#				PocoJSONd'''),
				LIBS = LibS,
				LIBPATH = PocoBase + '/lib' )


Default(t)
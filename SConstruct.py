#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment
import getpass

print "User: " + getpass.getuser()

#Alek Path for Windows
if getpass.getuser() == 'Aleksander Zamojski':
    PocoBase		= 'C:\\Libraries\\poco-1.7.8p2'
    WGCProjectBase	= 'C:\\Users\\Aleksander\\Documents\\GitHub\\WebGamesCentre'
#Alek Path for Linux
elif getpass.getuser() == 'alek':
    PocoBase		= '/home/alek/Documents/poco-1.7.8p2'
    WGCProjectBase	= '/home/alek/Desktop/ZPR/WebGamesCentre'
else:
    PocoBase		= '' #path to Poco library, the main folder
    WGCProjectBase	= '' #path to project file

print "Building: WGCServer"

env = Environment(TARGET_ARCH= 'x86')   # Create an environmnet for 32 bit version

platform = ARGUMENTS.get('OS', Platform())
print "Platform: " + platform.name

LibS = ['']
# Debug Flags if debug=1 is specified on the command line
if ARGUMENTS.get('debug') != '0':
    env.Append(CPPDEFINES = ['DEBUG', '_DEBUG'])
    variant = 'Debug'
    #env.Append(CCFLAGS=Split('/Zi /Fd${TARGET}.pdb'))
    #env.VariantDir('VSProject/Debug/', 'src', duplicate=0)	#not working ???
    
    if platform.name == 'win32':
        env.Append(CCFLAGS='/MDd')
        env.Append(LINKFLAGS = ['/DEBUG'])
        LibS = Split('PocoFoundationd PocoNetd PocoUtild PocoXMLd PocoJSONd')
    elif platform.name == 'posix':
        env.Append(CCFLAGS='-std=c++11')
        env.Append(CCFLAGS='-g')
        LibS = Split('PocoFoundationd.so PocoNetd.so PocoUtild.so PocoXMLd.so PocoJSONd.so')
    else:
        print "Your platfor is not supported yet!"
        Exit(2)

else:
    env.Append(CPPDEFINES = ['NDEBUG'])
    variant = 'Release'
    if platform.name == 'win32':
        env.Append(CCFLAGS='/MD')
        LibS = Split('PocoFoundation.lib PocoNet.lib PocoUtil.lib PocoXML.lib PocoJSON.lib')
    elif platform.name == 'posix':
        LibS = Split('PocoFoundation.so PocoNet.so PocoUtil.so PocoXML.so PocoJSON.so')
    else:
        print "Your platfor is not supported yet!"
        Exit(2)


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
				CPPPATH = [WGCProjectBase] + PocoHeaders,# + ['/usr/local/include'], #may be usefull
				LIBS = LibS,
				LIBPATH = PocoBase + '/lib')


Default(t)

#Check
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+Linux+-+Shoggoth&structure=Development

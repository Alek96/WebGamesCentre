#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment
import getpass


env = Environment(TARGET_ARCH= 'x86')   # Create an environmnet for 32 bit version
print "Building: WGCServer"
print "User: " + getpass.getuser()

#Alek Path for Windows
if getpass.getuser() == 'Aleksander Zamojski':
	PocoBase		= 'C:\\Libraries\\poco-1.7.8p2'
#Alek Path for Linux
elif getpass.getuser() == 'alek':
	PocoBase		= '/home/alek/Documents/poco-1.7.8p2'
#Przemek Path for Windows
elif getpass.getuser() == 'Przemek':
	PocoBase		= 'B:\\Poco C++ Libraries\\poco-1.7.8-all'
#path to the main folder of Poco library
else:
	PocoBase		= ''
	
#WGCProjectBase	= '' #path to project file
#WGCProjectBase	= 'C:\\Users\\Aleksander\\Documents\\GitHub\\WebGamesCentre'
#WGCProjectBase	= '/home/alek/Desktop/ZPR/WebGamesCentre'
WGCProjectBase	= '.'
env.Append(CPPPATH = WGCProjectBase)


#source files
srcFiles = Split('''src/PageRequestHandler.cpp
					 src/RequestHandlerFactory.cpp
					 src/Server.cpp
					 src/WebSocketRequestHandler.cpp''')
#src_files = ['src/scons_test.cpp', 'src/class_test.cpp']
#consider to use Glob('*.c')

LibS = Split('''PocoFoundation 
				PocoNet 
				PocoUtil 
				PocoXML 
				PocoJSON''')

PocoHeaders = Split('''/Foundation/include
					   /Util/include
					   /Net/include
					   /JSON/include''')
PocoHeaders = [PocoBase + x for x in PocoHeaders]
env.Append(CPPPATH = PocoHeaders)

platform = ARGUMENTS.get('OS', Platform())
print "Platform: " + platform.name

# Debug Flags if debug=1 is specified on the command line
if ARGUMENTS.get('debug') == '1':
	env.Append(CPPDEFINES = ['DEBUG', '_DEBUG'])
	variant = 'Debug'
	#env.Append(CCFLAGS=Split('/Zi /Fd${TARGET}.pdb'))
	#env.VariantDir('VSProject/Debug/', 'src', duplicate=0)	#not working ???
    
	if platform.name == 'win32':
		env.Append(CCFLAGS='/MDd')
		env.Append(LINKFLAGS = ['/DEBUG'])
		LibS = [ x + 'd.lib' for x in LibS]
	elif platform.name == 'posix':
		env.Append(CCFLAGS='-std=c++11')
		env.Append(CCFLAGS='-g')
		#LibS = Split('''PocoFoundationd.so PocoNetd.so PocoUtild.so PocoXMLd.so PocoJSONd.so''')
		LibS = [ x + 'd.so' for x in LibS]
	else:
		print "Your platfor is not supported yet!"
		Exit(2)

else:
	env.Append(CPPDEFINES = ['NDEBUG'])
	variant = 'Release'

	if platform.name == 'win32':
		env.Append(CCFLAGS='/MD')
		LibS = [ x + '.lib' for x in LibS]
	elif platform.name == 'posix':
		#LibS = Split('PocoFoundation.so PocoNet.so PocoUtil.so PocoXML.so PocoJSON.so')
		LibS = [ x + '.so' for x in LibS]
	else:
		print "Your platfor is not supported yet!"
		Exit(2)

print "Building: " + variant
env.Append(LIBS = LibS)
env.Append(LIBPATH = PocoBase + '/lib')



t = env.Program(target = 'VSProject/'+variant+'/WGCServer', source = srcFiles)
Default(t)

#Check
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+Linux+-+Shoggoth&structure=Development

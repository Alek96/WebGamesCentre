#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment
import getpass
from shutil import copyfile
import os.path

env = Environment(TARGET_ARCH= 'x86')	# Create an environmnet for 32 bit version 

Help("""
usage: scons [OPTION] ...

SCons Options:
  debug=1               build the debug version
  VERBOSE=1             build with all information
""")

if ARGUMENTS.get('VERBOSE') != '1':
	env.Append(CCCOMSTR = 'Compiling $TARGET')
	env.Append(CXXCOMSTR = 'Compiling $TARGET')
	env.Append(LINKCOMSTR = 'Linking $TARGET')


#Alek Path for Windows
if getpass.getuser() == 'Aleksander Zamojski':
	PocoBase = 'C:\\Libraries\\poco-1.7.8p2'
#Alek Path for Linux
elif getpass.getuser() == 'alek':
	PocoBase = '/home/alek/Documents/poco-1.7.8p2'
#Przemek Path for Windows
elif getpass.getuser() == 'Przemek':
	PocoBase = 'B:\\Poco C++ Libraries\\poco-1.7.8-all'
#path to the main folder of Poco library
else:
	PocoBase = ''
	
WGCProjectBase	= '.'
env.Append(CPPPATH = WGCProjectBase)

#source files
srcFiles = Split('''
	src/PageRequestHandler.cpp
	src/RequestHandlerFactory.cpp
	src/Server.cpp
	src/WebSocketRequestHandler.cpp
	''')
#src_files = ['src/scons_test.cpp', 'src/class_test.cpp']
#consider to use Glob('*.c')

LibS = Split('''
	PocoFoundation 
	PocoNet 
	PocoUtil 
	PocoXML 
	PocoJSON
	''')

PocoHeaders = Split('''
	/Foundation/include
	/Util/include
	/Net/include
	/JSON/include
	''')
PocoHeaders = [PocoBase + x for x in PocoHeaders]
env.Append(CPPPATH = PocoHeaders)

platform = ARGUMENTS.get('OS', Platform())
#mode = ARGUMENTS.get('mode', "release")

if ARGUMENTS.get('debug') == '1':
	variant = 'Debug'
else:
	variant = 'Release'


if platform.name == "win32":
	if variant == 'Debug':
		env.Append(CPPDEFINES = ['DEBUG', '_DEBUG'])
		env.Append(CCFLAGS=['-W3', '-EHsc', '-D_DEBUG', '/MDd']) #'/Zi'
		env.Append(LINKFLAGS = ['/DEBUG', '/INCREMENTAL:NO'])
		LibS = [ x + 'd.lib' for x in LibS]
	else:
		env.Append(CPPDEFINES = ['NDEBUG'])
		env.Append(CCFLAGS=['-O2', '-EHsc', '-DNDEBUG', '/MD'])
		LibS = [ x + '.lib' for x in LibS]

else:	#posix and linux
	env.Append(CCFLAGS='-std=c++11')
	if variant == 'Debug':
		env.Append(CCFLAGS='-g')
		LibS = [ x + 'd.so' for x in LibS]
	else:
		LibS = [ x + '.so' for x in LibS]

#env.Append(CCFLAGS=Split('/Zi /Fd${TARGET}.pdb'))
#env.VariantDir('VSProject/Debug/', 'src', duplicate=0)	#not working ???
    
env.Append(LIBS = LibS)
env.Append(LIBPATH = PocoBase + '/lib')

t = env.Program(target = 'VSProject/'+variant+'/WGCServer', source = srcFiles)
Default(t)

#copy 
if os.path.isfile('config\WGCServer.properties'):
	copyfile('config\WGCServer.properties', 'VSProject/'+variant+'/WGCServer.properties')
	print 'copy file WGCServer.properties'

#Check
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+Linux+-+Shoggoth&structure=Development

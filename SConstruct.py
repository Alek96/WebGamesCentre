#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment
# ---
import getpass
from shutil import copyfile
import os.path
import os

env = Environment(TARGET_ARCH= 'x86')	# Create an environmnet for 32 bit version 

Help("""
usage: scons [OPTION] ...

SCons Options (case insensitive):
  debug=1               build the debug version
  VERBOSE=1             build with all information
  testOff=1             turns off building unit tests
""")

# keys to lower case (for case insensitiveness)
ARGUMENTS = dict((k.lower(), v) for (k,v) in ARGUMENTS.items())
# Generator expressions, see: https://www.python.org/dev/peps/pep-0289/

if ARGUMENTS.get('verbose') != '1':
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
	env.Append(ENV = os.environ)
#path to the main folder of Poco library
# ===== DEFINE HERE YOURS =====
else:
	PocoBase = ''
	
WGCProjectBase	= '.'
env.Append(CPPPATH = WGCProjectBase)

#source files
commonSrcFiles = Split('''
	src/PageRequestHandler.cpp
	src/RequestHandlerFactory.cpp
	src/WebSocketRequestHandler.cpp
	''')
srcFiles = commonSrcFiles + ['src/Server.cpp']
	
if ARGUMENTS.get('testoff', '0') == '0':
	testsSrcFiles = commonSrcFiles + Split('''
		tests/testsMain.cpp
		tests/RequestHandlerFactoryTest.cpp
		''')
	#print "testON"
	
#src_files = ['src/scons_test.cpp', 'src/class_test.cpp']
#consider to use Glob('*.c')
#exit(1)

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

platform = ARGUMENTS.get('os', Platform())
#mode = ARGUMENTS.get('mode', "release")

if ARGUMENTS.get('debug') == '1':
	variant = 'Debug'
else:
	variant = 'Release'


if platform.name == 'win32':
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

if ARGUMENTS.get('testoff', '0') == '0':
	testsTargetPath = 'VSProject/'+variant+'/WGCServerTests'
	tests = env.Program(target = testsTargetPath, source = testsSrcFiles)
	Default(tests)	#prepend

targetPath = 'VSProject/'+variant+'/WGCServer'

server = env.Program(target = targetPath, source = srcFiles)
Default(server)
# default targets, see: http://www.scons.org/doc/0.93/HTML/scons-user/c675.html

#copy 
fPath = 'VSProject/'+variant+'/WGCServer.properties'
if not env.GetOption('clean'):
	if not os.path.exists(fPath):
		if not os.path.exists('VSProject/'+variant):
			os.makedirs('VSProject/'+variant)
		copyfile('config\WGCServer.properties', fPath)
		print 'copy file WGCServer.properties to ' +  variant
elif os.path.exists(fPath):
	os.remove(fPath)
	print 'remove file WGCServer.properties from ' +  variant

#Check
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+Linux+-+Shoggoth&structure=Development

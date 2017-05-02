#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment
# ---
from shutil import copyfile
import os.path
import os

env = Environment(TARGET_ARCH= 'x86')	# Create an environmnet for 32 bit version 
# Make env global 
Export('env')

# This will be shown with flag -h
Help('''
usage: scons [OPTION] ...

SCons Options (case insensitive):
  release=1             Build the release version
  verbose=1             Build with all information

 unit test:
  test                  Build all unit tests
  testName              Build single unit test called 'testName'
  test=on               Turns on building unit tests (default)
  test=off              Turns off building unit tests
  test=all              Run all unit tests
  test=testName         Run unit tests whose name contains 'testName'

''')

# Keys to lower case (for case insensitiveness)
ARGUMENTS = dict((k.lower(), v) for (k,v) in ARGUMENTS.items())
# Generator expressions, see: https://www.python.org/dev/peps/pep-0289/

# Replace long comment for short version
if ARGUMENTS.get('verbose') != '1':
	env.Append(CCCOMSTR = ['Compiling $TARGET'])
	env.Append(CXXCOMSTR = ['Compiling $TARGET'])
	env.Append(LINKCOMSTR = ['Linking $TARGET'])

# Run PocoDir.py for configuration
SConscript('config/PocoDir.py')
PocoBase = env['POCOBASE']

# Get current path
WGCProjectBase = [os.getcwd()]
env.Append(CPPPATH = WGCProjectBase)

# Names of the libraries. 
# Letter 'd' for debug, and suffix .lib or .so will be added automatically
LibS = Split('''
	PocoFoundation 
	PocoNet 
	PocoUtil 
	PocoXML 
	PocoJSON
	''')

# Path in PocoBase directory where can be found header files
PocoHeaders = Split('''
	/Foundation/include
	/Util/include
	/Net/include
	/JSON/include
	''')
PocoHeaders = [PocoBase + x for x in PocoHeaders]
env.Append(CPPPATH = PocoHeaders)

# Detect the build mode
platform = ARGUMENTS.get('os', Platform())
if ARGUMENTS.get('release', '0') == '1':
	variant = 'Release'
else:
	variant = 'Debug'

# Add flags for detected platform and build mode
if platform.name == 'win32':
	if variant == 'Debug':
		env.Append(CPPDEFINES = ['DEBUG', '_DEBUG'])
		env.Append(CCFLAGS=['-W3', '-EHsc', '-D_DEBUG', '/MDd', '/Z7'])
		#env.Append(CCPDBFLAGS=['/Zi', '/Fd${TARGET}.pdb'])
		env.Append(LINKFLAGS = ['/DEBUG', '/INCREMENTAL:NO'])
		LibS = [ x + 'd.lib' for x in LibS]
	else:
		env.Append(CPPDEFINES = ['NDEBUG'])
		env.Append(CCFLAGS=['-O2', '-EHsc', '-DNDEBUG', '/MD'])
		LibS = [ x + '.lib' for x in LibS]
else:	#posix and linux
	env.Append(CCFLAGS=['-std=c++14'])
	if variant == 'Debug':
		env.Append(CCFLAGS=['-g'])
		LibS = [ x + 'd.so' for x in LibS]
	else:
		LibS = [ x + '.so' for x in LibS]

env.Append(LIBS = LibS)
env.Append(LIBPATH = [PocoBase + '/lib'])

# Initial unit test
testEnv = env.Clone()
Export('testEnv')
# Add new tool, that can be found in src/Server/unitTest.py
testEnv.Tool('unitTest',
	toolpath=['src/Server'],
	UTEST_MAIN_SRC=File('build/'+variant+'/testsMain.obj'))
# Save argument in testEnv
testEnv.SetDefault(test = [ARGUMENTS.get('test', 'on')])

# Hierarchical Builds
if not GetOption('help'):
	env.SConscript('src/Server/SConscript.py', variant_dir='build/'+variant, duplicate=0)
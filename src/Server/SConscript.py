#!python
import SCons.Script
from SCons.Environment import Environment
# ---

Import('env')

#Run SConscript files
libFiles = SConscript(Split('''
	RequestHandlers/SConscript.py
	'''))

#Make new library
libFiles = Library('Server', libFiles)

#Load and Compile main
objFiles = env.Object('Server.cpp')

#Load and Compile testsMain
objTestMain = env.Object('testsMain.cpp')

#Link program
env.Program(target = '#bin/WGCServer', source =  objFiles + libFiles)
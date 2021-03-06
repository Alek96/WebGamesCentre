#!python
import SCons.Script
from SCons.Environment import Environment
# ---

Import('env')

# Run SConscript files
libFiles = SConscript(Split('''
    Games/SConscript.py
    Connection/SConscript.py
	RequestHandlers/SConscript.py
    Player/SConscript.py
	'''))

#Load and Compile main
objFiles = env.Object('Server.cpp')

#Make new library
libFiles = env.Library('Server', libFiles)

#Link program
env.Program(target = '#bin/WGCServer', source = objFiles + libFiles)

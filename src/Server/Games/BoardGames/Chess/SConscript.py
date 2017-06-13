#!python
import SCons.Script
from SCons.Environment import Environment
# ---
import os

Import('env')

# Run SConscript files
libFiles = SConscript(Split('''
	ChessBoard/SConscript.py
	'''))
	
# Load and Compile all *.cpp file
srcFiles = Glob('*.cpp')
objFiles = env.Object(srcFiles)

# Unit tests
Import('testEnv')
# Add file with unit tests
#testEnv.addUnitTest(['test/ChessTest.cpp'] + objFiles + env['BOARDGAMEOBJ'] + libFiles)

# Get the name of current directory, which will be the default name for the library
dirPath = os.getcwd()
dirName = os.path.basename(dirPath)

# Rename the new library if you do not want a default name
libFiles = env.Library(dirName, objFiles + libFiles)
Return('libFiles')
#!python
import SCons.Script
from SCons.Environment import Environment
# ---
import os

Import('env')

# Run SConscript files
libFiles = SConscript(Split('''
    BoardGames/SConscript.py
	'''))

# Load and Compile all cpp file
srcFiles = Glob('*.cpp')
objFiles = env.Object(srcFiles)

# Unit tests
#Import('testEnv')
# Add file with unit tests
#testEnv.addUnitTest(['test/RequestHandlerFactoryTest.cpp'] + objFiles)

# Get the name of current directory
dirPath = os.getcwd()
dirName = os.path.basename(dirPath)

# Rename the new library if you do not want a default name
libFiles = env.Library(dirName, objFiles + libFiles)

# Add this librares to global values
#env.SetDefault(GAMESLIB = libFiles)
env.SetDefault(GAMESLIB = objFiles)

Return('libFiles')
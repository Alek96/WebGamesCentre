#!python
import SCons.Script
from SCons.Environment import Environment
# ---
import os

Import('env')

# Load and Compile all *.cpp file
srcFiles = Glob('*.cpp')
objFiles = env.Object(srcFiles)

# Unit tests
Import('testEnv')
testEnv = testEnv.Clone()
# Add file with unit tests
test = testEnv.addUnitTest(['test/...Test.cpp'] + objFiles)
# or
test = testEnv.addUnitTest(target = '#bin/...Test', source = ['test/...Test.cpp'] + objFiles)

# Run SConscript files
libFiles = SConscript(Split('''
	Directory/SConscript.py
	'''))

# Get the name of current directory
dirPath = os.getcwd()
dirName = os.path.basename(dirPath)

# Rename the new library if you do not want a default name
libFiles = Library(dirName, objFiles + libFiles)
Return('libFiles')
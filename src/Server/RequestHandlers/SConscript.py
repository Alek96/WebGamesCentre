#!python
import SCons.Script
from SCons.Environment import Environment
# ---
import os

Import('env')

# Load and Compile all cpp file
srcFiles = Glob('*.cpp')
objFiles = env.Object(srcFiles)

# Unit tests
Import('testEnv')
# Add file with unit tests
test = testEnv.addUnitTest(['test/RequestHandlerFactoryTest.cpp'] + objFiles)

# Get the name of current directory
dirPath = os.getcwd()
dirName = os.path.basename(dirPath)

# Make new library
libFiles = Library(dirName, objFiles)
Return('libFiles') 
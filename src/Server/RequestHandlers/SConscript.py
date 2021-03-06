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
testEnv.addUnitTest(['test/RequestHandlerFactoryTest.cpp'] + objFiles + env['GAMESLIB'] + env['CONNECTIONLIB'] ) #+ env['CONNECTIONLIB'] + env['PLAYERLIB']

# Get the name of current directory
dirPath = os.getcwd()
dirName = os.path.basename(dirPath)

# Make new library
libFiles = env.Library(dirName, objFiles)
Return('libFiles') 
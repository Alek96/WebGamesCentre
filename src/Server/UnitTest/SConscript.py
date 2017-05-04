#!python
import SCons.Script
from SCons.Environment import Environment
# ---

Import('testEnv')

#Load and Compile testsMain
objTestMain = testEnv.Object('testsMain.cpp')

# Add new tool, that can be found in UnitTest.py
testEnv.Tool('UnitTest',
	toolpath= ['.'],
	UTEST_MAIN_SRC= objTestMain[0].abspath )
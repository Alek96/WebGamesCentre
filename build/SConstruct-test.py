#!python

# These import lines are not really needed, but it helps intellisense within VS when editing the script
import SCons.Script
from SCons.Environment import Environment

print "Building scons_test"

env = Environment()   # Create an environmnet
env.Program(target = "scons_test", source = ["scons_test.c"])

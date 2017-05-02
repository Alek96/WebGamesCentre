#!python
import SCons.Script
from SCons.Environment import Environment
# ---

Import('env')
#path to the main folder of Poco library
# ===== DEFINE HERE YOURS =====
env.SetDefault(POCOBASE = '')
import subprocess
import logging
import sys

cxxPath         = []

# define the attributes of the build environment shared between
# both the debug and release builds
env = DefaultEnvironment()

def CheckRoot(context, version):
    context.Message('Checking for ROOT Version %s...' % (version))
    try:
        root_version = subprocess.check_output(['root-config', '--version'])
        ret = version in root_version
    except:
        ret = False
    context.Result(ret)
    return ret

def SetRootVariables():
    global cxxPath
    root_incdir = subprocess.check_output(['root-config', '--incdir'])
    cxxPath.append(root_incdir)

def CheckBoost(context, version):
    # Boost versions are in format major.minor.subminor
    v_arr = version.split(".")
    version_n = 0
    if len(v_arr) > 0:
        version_n += int(v_arr[0])*100000
    if len(v_arr) > 1:
        version_n += int(v_arr[1])*100
    if len(v_arr) > 2:
        version_n += int(v_arr[2])

    context.Message('Checking for Boost version >= %s... ' % (version))
    ret = context.TryCompile("""
    #include <boost/version.hpp>

    #if BOOST_VERSION < %d
    #error Installed boost is too old!
    #endif
    int main()
    {
        return 0;
    }
    """ % version_n, '.cpp')
    context.Result(ret)
    return ret

conf = Configure(env, custom_tests = { 'CheckBoost' : CheckBoost, 'CheckRoot': CheckRoot })

if not (conf.CheckBoost('1.53')):
    logging.error('Boost version >= 1.53 needed')
    sys.exit(-1)
if not (conf.CheckRoot('6.09/01')):
    logging.error("ROOT is incorrect Version")
    sys.exit(-1)
else:
    SetRootVariables()

env.Append(CPPPATH 		= cxxPath)

Export('env')
env.SConscript('core/SConscript')

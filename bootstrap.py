#!/usr/bin/env python3
"""
Bootstrapping MellowPlayer

Detect environment and execute MellowPlayer from source checkout.

.. note:: This script has been inspired by the bootstrap script of SpyderIDE.
"""
import os
import time

time_start = time.time()
import os.path as osp
import platform
import sys


#--- bootstrapping MellowPlayer
print("Executing MellowPlayer from source checkout")


#--- checking minimum python version, we need Python >= 3.4
pyver = "%s%s" % (sys.version_info[0], sys.version_info[1])
if pyver < '34':
    print('Cannot run MellowPlayer with Python %s, Python >= 3.4 is required' %
          platform.python_version())
    sys.exit(1)


#--- patching sys.path
DEVPATH = osp.dirname(osp.abspath(__file__))
sys.path.insert(0, DEVPATH)
print("01. Patched sys.path with %s" % DEVPATH)

#--- checking required dependencies
from mellowplayer import setup_sip_api
try:
    # make sure correct sip api is used
    setup_sip_api()
    import PyQt4
except ImportError:
    from mellowplayer.system import LINUX, linux_distribution
    if LINUX:
        # try to install pyqt4
        cmd = None
        # distro specific command for installing pyqt4
        if linux_distribution == 'KaOS':
            cmd = "\"pacman\" \"-S\" \"pyqt-python3\""
        elif linux_distribution == 'ArchLinux':
            cmd = "\"pacman\" \"-S\" \"python-pyqt4\""
        installed = False
        if cmd is not None:
            choice = input('03. WARNING: PyQt4 not detected. Do you want me to'
                           ' install it for you? [Y/n] ')
            if choice == 'Y' or not choice:  # Yes is the default choice
                if os.system('sudo %s' % cmd) == 0:
                    installed = True
        if not installed:
            sys.exit(1)
        else:
            # make sure correct sip api is used
            setup_sip_api()
            import PyQt4
    print('03. WARNING: PyQt4 not detected. Install PyQt4 for python3 and '
          'try again...')
    sys.exit(1)
else:
    print('03. PyQt4 detected')

#--- importing MellowPlayer
from mellowplayer.system import get_versions, get_vcs_revision
versions = get_versions()
print("04. Imported MellowPlayer %s (%s)" % (
    versions['mellowplayer'], get_vcs_revision()))
print("    [Python %s %dbits, Qt %s, %s %s on %s]" % \
      (versions['python'], versions['bitness'], versions['qt'],
       versions['qt_api'], versions['qt_api_ver'], versions['system']))


#--- executing MellowPlayer
print("04. Executing app.main()")
from mellowplayer import app
time_lapse = time.time() - time_start
print("Bootstrap completed in " +
      time.strftime("%H:%M:%S.", time.gmtime(time_lapse)) +
      # gmtime() converts float into tuple, but loses milliseconds
      ("%.4f" % time_lapse).split('.')[1])
app.main()

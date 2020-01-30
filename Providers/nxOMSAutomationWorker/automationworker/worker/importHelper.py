PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 2

CONFIGPARSER_KEY = "configparser"
import sys

def install_aliases():
    """
    Imports the relevant modules based on the python runtime version.
    After calling this method the caller can import the latest packages without having to consider about the 
    backward compatibility.

    Currently supported packages:
    1. ConfigParser

    """
    
    version_info = sys.version
    if int(version_info[PY_MAJOR_VERSION]) == 2 and int(version_info[PY_MINOR_VERSION]) <= 7:
        import ConfigParser
        sys.modules[CONFIGPARSER_KEY] = ConfigParser
    else:
        return


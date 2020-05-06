#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

"""IOHelper module. Contains io operation helper methods."""

import os

# octal numbers in python3 now must be specified using "0o" or "0O" according to "https://www.python.org/dev/peps/pep-3127/#id19"
os.umask(0o77)


def write_to_file(file_path, data, mode="w"):
    """Writes the data to the specified file_path. If the path doesn't exist, it will be created.

    Args:
        file_path   : string, the file path including the file name.
        data        : string, the data.
        mode        : string, mode.
    """
    assert_or_create_path(os.path.dirname(file_path))
    f = open(file_path, mode)
    f.write(data)
    f.close()


def assert_or_create_path(path):
    """Asserts that the specified path exists, else it will create the directory structure for it.

    Args:
        path : string, the path.
    """
    if not os.path.exists(path):
        os.makedirs(path)

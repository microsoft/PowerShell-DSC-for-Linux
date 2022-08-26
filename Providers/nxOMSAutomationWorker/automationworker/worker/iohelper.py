#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""IOHelper module. Contains io operation helper methods."""

import os

os.umask(077)


def write_to_file(file_path, data, mode="wb"):
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

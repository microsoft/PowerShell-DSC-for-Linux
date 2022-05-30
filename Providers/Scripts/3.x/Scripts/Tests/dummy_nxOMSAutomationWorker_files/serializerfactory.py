#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Serializer factory."""

PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 1


def get_serializer(version_info):
    """Returns the appropriate serializer module based on version_info. Python 2.6 and 2.6+ have the json module
    built-in, other version (2.6-) have to rely on the ancestral implementation (simplejson) which is included under
    the worker package.

    An instance of simplejson module if the installed Python version is below 2.6
    An instance of json module if the installed Python version is or is above 2.6

    Args:
        version_info : array, the build-in python version_info

    Returns:
        Json module
    """
    if version_info[PY_MAJOR_VERSION] == 2 and version_info[PY_MINOR_VERSION] < 6:
        import simplejson as json
    else:
        import json
    return json

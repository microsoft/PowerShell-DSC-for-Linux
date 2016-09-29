#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""RequestReponse for http clients."""

import serializerfactory
import sys


class RequestResponse:
    """Encapsulates all request response for http clients. Will also deserialize the response when the raw response
    data is deserializable.
    """
    def __init__(self, status_code, raw_response_data=None):
        self.status_code = int(status_code)
        self.raw_data = raw_response_data

        # TODO(dalbe): review deserialization logic
        self.json = serializerfactory.get_serializer(sys.version_info)
        if raw_response_data is not None:
            try:
                self.deserialized_data = self.json.loads(self.raw_data)
            except ValueError:
                self.deserialized_data = None
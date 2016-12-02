#!/bin/bash
chmod 755 $1
setcap cap_net_raw=ep $1



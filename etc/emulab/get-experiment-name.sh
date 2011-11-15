#!/bin/bash

#
# @file     get-experiment-name.sh
#
# $Id$
#
# @author   James H. Hill
#

cat /var/emulab/boot/nickname | awk -F '.' '{ printf "%s", $2 }'

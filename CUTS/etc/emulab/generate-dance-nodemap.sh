#!/bin/bash

#
# @file           generate-dance-nodemap.sh
#
# $Id$
#
# @author         James H. Hill
#

# save the command-line arguments
PORT_NUMBER=$1

# get the suffix for the hostname's alias
HOSTNAME_SUFFIX=`cat /var/emulab/boot/nickname | awk -F '.' '{ printf "%s.%s", $2, $3 }'`

# write the corbaloc for each host
grep 'h' /var/emulab/boot/ltmap | awk -F ' ' '{ printf "%s    corbaloc:iiop:%s.%s.isislab.vanderbilt.edu:"'"${PORT_NUMBER}"'"/NodeManager\n", $2, $2, "'"${HOSTNAME_SUFFIX}"'" }'

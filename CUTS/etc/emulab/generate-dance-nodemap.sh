#!/bin/bash

#
# @file           generate-dance-nodemap.sh
#
# $Id$
#
# @author         James H. Hill
#

# get the suffix for the hostname's alias
HOSTNAME_SUFFIX=`cat /var/emulab/boot/nickname | awk -F '.' '{ printf "%s.%s", $2, $3 }'`

# write the corbaloc for each host
grep 'h' /var/emulab/boot/ltmap | awk -F ' ' '{ printf "%s    corbaloc:iiop:%s.%s.isislab.vanderbilt.edu:30000/NodeManager\n", $2, $2, "'"${HOSTNAME_SUFFIX}"'" }'

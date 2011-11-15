#!/bin/bash

#
# @file     is-master-node.sh
#
# $Id$
#
# @author   James H. Hill
#

if [ ! /var/emulab/boot/syncserver ]; then
  grep -c `cat /var/emulab/boot/nickname` /var/emulab/boot/syncserver
else
  echo 0
fi

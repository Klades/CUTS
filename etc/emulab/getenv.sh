#!/bin/bash

#
# @file    emulab-getenv.sh
#
# $Id$
#
# @author  James H. Hill
#

# get the value of the environment variable
VALUE=`grep "ENV $1=" /var/emulab/boot/progagents | sed "s/ENV $1=//"`

# echo the environment variable
echo ${VALUE}

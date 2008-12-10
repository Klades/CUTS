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
echo "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>"
echo "<cuts:logging xmlns='http://www.dre.vanderbilt.edu/CUTS'"
echo "              xmlns:cuts='http://www.dre.vanderbilt.edu/CUTS'"
echo "              xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
echo "              xsi:schemaLocation='http://www.dre.vanderbilt.edu/CUTS logging.xsd'>"

grep h /var/emulab/boot/ltmap | sed "s/h //" | awk -F ' ' '{ if ($1 != "control") printf "  <client>corbaloc:iiop:%s.%s.isislab.vanderbilt.edu:"'"${PORT_NUMBER}"'"/CUTS/TestLoggerClient</client>\n", $1, "'"${HOSTNAME_SUFFIX}"'" }'
echo "</cuts:logging>"

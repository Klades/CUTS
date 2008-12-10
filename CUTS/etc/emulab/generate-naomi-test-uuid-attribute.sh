#!/bin/bash

#
# @file         generate-naomi-test-uuid-attribute.sh
#
# $Id$
#
# @author       James H. Hill
#

echo "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>"
echo "<attribute xmlns='http://www.atl.lmco.com/naomi/attributes'"
echo "           xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
echo "           xsi:schemaLocation='http://www.atl.lmco.com/naomi/attributes attribute.xsd'>"
echo "  <owner>CUTS.emulation</owner>"
echo "  <value>`${CUTS_ROOT}/etc/emulab/get-test-uuid-from-basic-summary.sh $1`</value>"
echo "  <documentation>Test UUID for the latest CUTS emulation</documentation>"
echo "</attribute>"

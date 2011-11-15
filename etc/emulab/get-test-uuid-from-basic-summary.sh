#!/bin/bash

#
# @file           get-test-uuid-from-basic-summary.sh
#
# $Id$
#
# @author         James H. Hill
#

# locate the UUID line in the summary
grep UUID $1 | sed "s/  UUID       : //"

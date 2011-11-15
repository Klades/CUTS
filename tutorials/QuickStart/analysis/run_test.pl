eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id$
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$CUTS_ROOT = "$ENV{'CUTS_ROOT'}";

# Invoke the CUTS node manager
print "Running the CUTS node manager\n";
$cutsnode = new PerlACE::Process ("$CUTS_ROOT/bin/cuts-unite", "-c QuickStart.unite -f ../descriptors/00000000-0000-0000-0000-000000000000.cdb");
$cutsnode->SpawnWaitKill ();

exit 0;

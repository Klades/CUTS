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
$cutsnode = new PerlACE::Process ("$CUTS_ROOT/bin/cutsnode_d", "-c deployment.config");
$cutsnode->Spawn ();

sleep (10);

print "Running the test manager for 30 seconds\n";
$TM = new PerlACE::Process ("$CUTS_ROOT/bin/cutstest", "-c test.config --time=30");

$TM->SpawnWaitKill (30000);

# wait for 10 seconds.
sleep (30);

# Kill the CUTS node daemon.
$cutsnode->Kill ();

exit 0;

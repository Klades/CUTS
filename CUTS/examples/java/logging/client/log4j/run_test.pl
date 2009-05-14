eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id$
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$REMOTE_ENDPOINT = "iiop://localhost:30000";
$LOCALHOST_PORT = 20000;

$CUTS_ROOT = "$ENV{'CUTS_ROOT'}";
$JAVA_HOME = "$ENV{'JAVA_HOME'}";

# spawn the CUTS node daemon
$node = new PerlACE::Process ("$CUTS_ROOT/bin/cutsnode_d", "-c cutsnode.config -DREMOTE_ENDPOINT=$REMOTE_ENDPOINT -DLOCALHOST_PORT=$LOCALHOST_PORT --debug --verbose");
$node->Spawn ();

# spawn a test manager
sleep (3);

# run the Java application
$classpath = ".;$CUTS_ROOT/lib/cuts.log4j.jar;$CUTS_ROOT/lib/CUTS.TestLogger.jar;$CUTS_ROOT/lib/cuts.java.jar;$CUTS_ROOT/contrib/java/log4j-1.2.15.jar";
$javapp = new PerlACE::Process ("$JAVA_HOME/bin/java", "-classpath $classpath HelloWorld");
$javapp->SpawnWaitKill ();

# kill the CUTS node daemon
$node->Kill ();
$node->TimedWait (1);


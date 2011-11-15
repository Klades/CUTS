eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id$
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$REMOTE_ENDPOINT = "iiop://localhost:30000";
$LOCALHOST_PORT = 20000;
$timeout = 10;

$CUTS_ROOT = "$ENV{'CUTS_ROOT'}";
$JAVA_HOME = "$ENV{'JAVA_HOME'}";

# spawn the node daemon; it will manage the processes
$node = new PerlACE::Process ("$CUTS_ROOT/bin/cutsnode_d", "-c cutsnode.config -v -DTEST_TIMEOUT=$timeout");
$node->Spawn ();

sleep (10);

# run the Java application
$classpath = ".;$CUTS_ROOT/lib/cuts.log4j.jar;$CUTS_ROOT/lib/cuts.testing.jar;$CUTS_ROOT/lib/cuts.clientlogger.jar;$CUTS_ROOT/lib/cuts.java.jar;$CUTS_ROOT/contrib/java/log4j-1.2.15.jar";
$javapp = new PerlACE::Process ("$JAVA_HOME/bin/java", "-classpath $classpath HelloWorld");
$javapp->SpawnWaitKill ();

sleep ($timeout);

# kill the CUTS node daemon
$node->Kill ();
$node->TimedWait (1);

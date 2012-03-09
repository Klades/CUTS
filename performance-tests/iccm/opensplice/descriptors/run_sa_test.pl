eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id$
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::Run_Test;

$CIAO_ROOT = "$ENV{'CIAO_ROOT'}";
$TAO_ROOT = "$ENV{'TAO_ROOT'}";
$DANCE_ROOT = "$ENV{'DANCE_ROOT'}";

$OSPL_HOME = "$ENV{'OSPL_HOME'}";
$CUTS_ROOT = "$ENV{'CUTS_ROOT'}";

$daemons_running = 0;
$em_running = 0;
$ns_running = 0;

$daemons = 2;
@ports = ( 60001, 60002 );
@iorfiles = ( "SenderNode.ior", "ReceiverNode.ior" );
@nodenames = ( "SenderNode", "ReceiverNode" );

$status = 0;
$dat_file = "S1R1.cdd";
$cdp_file = "S1R1.cdp";

$nsior = PerlACE::LocalFile ("ns.ior");

PerlACE::add_lib_path ('../lib');

unlink $nsior;

$E = 0;
$EM = 0;

sub kill_node_daemons {
  for ($i = 0; $i < $daemons; ++$i) {
    $Daemons[$i]->Kill (); $Daemons[$i]->TimedWait (1);
  }
}

# Invoke OpenSplice - start the server -
print "Invoke OpenSplice - start the server -\n";
$OSPL = new PerlACE::Process ("$OSPL_HOME/bin/ospl", "start");
$OSPL->SpawnWaitKill (3000);

# Invoke executor - start the application -.
print "Invoking executor - start the application -\n";
$E = new PerlACE::Process ("../lib/OpenSplice_Tput_Sender", "8");
$E->Spawn ();

# wait for 10 seconds.
sleep (10);

# Invoke executor - stop the application -.
print "Invoking executor - stop the application -\n";
$E->Kill ();
$E->TimedWait (1);

print "Executor returned.\n";

# Invoke OpenSplice - stop the server -
print "Invoke OpenSplice - stop the server -\n";
$OSPL = new PerlACE::Process ("$OSPL_HOME/bin/ospl", "stop");
$OSPL->SpawnWaitKill (3000);

print "Shutting down rest of the processes.\n";

exit $status;

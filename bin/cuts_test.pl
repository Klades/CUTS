# $Id$
# -*- perl -*-

eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# import module and libraries
use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::Run_Test;

# get the CIAO_ROOT and WLG_ROOT
$CIAO_ROOT = $ENV{'CIAO_ROOT'};

$time = 60;

while ($arg = shift)
{
  $arg eq "-p" and $plan = shift;
  $arg eq "--time" and $time = shift;
  $arg eq "--help" and print_help_2() and exit;
}

!defined($plan) and die "*** syntax error: you must specify a plan\n";

# spawn the an instance of the executor
$planner = "$CIAO_ROOT/bin/plan_launcher";
$planner_args = "-p $plan -k file://EM.ior -o DAM.ior -z CLIENT_PROPAGATED";

print "*** info: deploying $plan\n";

$planner_start = new PerlACE::Process ($planner, $planner_args);
$result = $planner_start->SpawnWaitKill (5000);

if ($result != 0) 
{
    die "*** error: failed to deploy $plan\n";
}

#time to run test
sleep ($time);

$planner_args = "-p $plan -k file://EM.ior -i file://DAM.ior";
$planner_shutdown = new PerlACE::Process ($planner, $planner_args);
$result = $planner_shutdown->SpawnWaitKill (5000);

if ($result != 0)
{
    die "*** error: failed to teardown $plan\n";
}

#
# print_help
#
sub print_help_2
{
  print "  SYNTAX: run_test.pl -p <deployment.cdp> --time <seconds>";
  return 0;
}

0;

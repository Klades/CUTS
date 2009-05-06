     eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
  &  eval 'exec perl -S $0 $argv:q'
  if 0;

# $Id$
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";

use PerlACE::Run_Test;

$driver = new PerlACE::Process ("dds_driver");
$driver->Arguments ("-s $ENV{CIAO_ROOT}/bin/ciao_componentserver");

system ('ospl start');

$status = $driver->SpawnWaitKill (10);

# Unix-specific, not portable
system ('killall -9 ciao_componentserver');

system ('ospl stop');
    
exit $status

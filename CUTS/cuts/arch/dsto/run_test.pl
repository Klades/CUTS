eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# $Id$
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

$status = 0;

my $driver = PerlACE::TestTarget::create_target (1) || die "Create target failed\n";
$DRV = $driver->CreateProcess ("driver", "-s $ENV{CIAO_ROOT}/bin/ciao_componentserver");
$status = $DRV->SpawnWaitKill (10);

exit $status;

eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# *****************************************************************************
# Description   :
# Author        : James H. Hill
#
# $Id$
# *****************************************************************************

use strict;

# import modules
use Getopt::Long;
use FileHandle;

my ($curr_dir)  = undef;
my ($curr_rev)  = undef;
my ($tags_dir)  = undef;
my ($tags_rev)  = undef;
my ($verbose)   = undef;
my ($help)      = undef;
my ($fh)        = new FileHandle();
my ($info)      = 'info.tmp';

#
# parse_args
#
# Purpose:
#      parse command-line arguments for the script
#
sub parse_args {
  GetOptions ('curr-directory:s' => \$curr_dir,
              'tags-directory:s' => \$tags_dir,
              'help'             => \$help,
              'verbose'          => \$verbose);
}

#
# get_svn_revision
#
# Purpose:
#      get the revision number from the svn info
#
sub get_svn_revision {
  my ($fh)  = shift;
  my ($rev) = undef;

  while (<$fh>) {
    my ($line) = $_;

    if ($line =~ /Last Changed Rev: (\d*)/) {
      $rev = $1;
    }
  }

  $rev;
}

#
# find_svn_directory
#
# Purpose:
#      locate the directory with the target revision
#
sub find_svn_directory {
  my ($fh)      = shift;
  my ($rev)     = shift;

  while (<$fh>) {
    my ($line) = $_;

    if ($line =~ /^\s+$rev\s+.*\s+\d\d\s(\d\d:\d\d|\d\d\d\d)\s+(.*)\s+.*$/) {
      return $2;
    }
  }

  return undef;
}

#
# get_executable_fullpath
#
# Purpose:
#      locate the full path of SVN
#
sub get_executable_fullpath {
  my ($filename)       = shift;
  my ($separator)      = shift;
  my ($path_separator) = shift;

  foreach (split /$separator/, $ENV{'PATH'}) {
    my ($fullname) = $_ . $path_separator . $filename;

    if (-x $fullname) {
      return $fullname;
    }
  }

  return $filename;
}

# *****************************************************************************
# begin main portion of program
# *****************************************************************************

# parse the command-line arguments
parse_args ();

if ($verbose) {
  print "*** info: getting info for $tags_dir\n";
}

if (open($fh, "svn info $tags_dir 2> $info |")) {
  $tags_rev = get_svn_revision ($fh);
  close ($fh);
}

if ($verbose) {
  print "*** info: getting info for $curr_dir\n";
}

if (open($fh, "svn info $curr_dir 2> $info |")) {
  $curr_rev = get_svn_revision ($fh);
  close ($fh);
}

if ($verbose) {
  print "Tags directory revision: $tags_rev\n";
  print "Target directory revision: $curr_rev\n";
}

if ($tags_rev != $curr_rev) {
  print "*** warning: current directory [$curr_dir] is out-of-date; latest tag revision is $tags_rev\n";

  if (open($fh, "svn ls --verbose $tags_dir 2> $info |")) {
    my ($svn_dir) = find_svn_directory ($fh, $tags_rev);
    close ($fh);

    if ($svn_dir) {
      my ($child);

      print "*** info: switching to $tags_dir/$svn_dir; please be patient...\n";

      if (!defined ($child = fork())) {
        die "*** error: $!\n";
      }
      elsif ($child == 0) {
        # fork returned 0, so this branch is the child
        exec("svn switch $tags_dir/$svn_dir $curr_dir");

        # if the exec fails, fall through to the next statement
        die "*** error: $!\n";
      }
      else {
        waitpid ($child, 0);
      }
    }
    else {
      die "*** error: failed to locate directory with revision $tags_rev\n";
    }
  }
}

# remove the temp file
unlink ($info);

1;

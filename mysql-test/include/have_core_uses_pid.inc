# This inc file detects core_uses_pid only on centOS/RHEL

--source include/not_windows.inc

--let OUTFILE= $MYSQLTEST_VARDIR/tmp/core_uses_pid.out

perl;
use strict;
# This file contents should only be either 0 or 1
my $file = "/proc/sys/kernel/core_uses_pid";
my $core_uses_pid = 0;
if ((-e $file) && (-r $file))
{
  local $/=undef;
  open FILE, $file or die "Couldn't open file: $!";
  $core_uses_pid = <FILE>;
  close FILE;
}

open(FILE, ">$ENV{OUTFILE}") or die;
print FILE "let \$core_uses_pid= $core_uses_pid;\n";
close(FILE);
EOF

--source $OUTFILE
--remove_file $OUTFILE

if (!$core_uses_pid) {
  --skip Test requires core_uses_pid enabled environment like centOS/RHEL
}

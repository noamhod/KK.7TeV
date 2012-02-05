#!/usr/bin/perl
# Merges all files in each subdirectory of $org

use warnings;
use strict;
use File::Find;

my $org = shift;
my $dst = shift;
my $mult = 300;
my $basename=qx/basename $org/;

(my @files) = split(/^/, qx/find $org -iname \"*.root*\" | sort/);
my $size = scalar @files;
chomp @files;
chomp $org;
chomp $dst;
chomp $basename;
my $list2 = "";

my $i = 1;
my $j = 1;
my $list = "";
foreach my $file (@files) {
  if ( $i % $mult == 0 || $i eq $size ) {
    $list = "$list $file";
    print "#############################\n";
    #print join ("\n", split (/\s/m, $list));
    #print "\n";
    my $mergedFile = "${org}/${basename}_merged_${j}-${i}.root";
    $list2 = "${list2} ${mergedFile}";
    my $cmd="hadd $mergedFile $list";
    print "$cmd\n";
    system($cmd);
    $j = $i;
    $list = "";
  } else {
    $list = "${list} ${file}";
  }
  $i++;
}

my $cmd = "hadd ${dst}/${basename}_merged_all.root ${list2}";
print "$cmd\n";
system($cmd);
system("rm ${list2}");

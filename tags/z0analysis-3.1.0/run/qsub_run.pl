#!/usr/bin/perl
$cmd1="source /srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/qsub_setup.sh";
exec($cmd1);
$DATDIR="/storage/t3_data/hod/D3PDntp/rel16/user.hod.WZphysD3PD/submission_08012011";
$RUNDIR="/srv01/tau/hod/z0analysis-tests/z0analysis-dev/run";
$LD_LIBRARY_PATH=$LD_LIBRARY_PATH.":".$RUNDIR;
$LD_LIBRARY_PATH=$LD_LIBRARY_PATH.":".$RUNDIR."/../GoodRunsLists-00-00-91/StandAlone";
$cmd2="less /srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/qsub_submission.list";
open(PS1, "$cmd2|") || die "can't run $pscmd1: $!";

while ($line1 = <PS1>)
{
    	chop $line1;    
	@parameter=split('\t',$line1);
	$runnumber=@parameter[0];
	$DATDIR="/storage/t3_data/hod/D3PDntp/rel16/user.hod.WZphysD3PD/submission_08012011";
	$dataset=@parameter[1];


print("DATDIR  $DATDIR \n");
print("dataset  $dataset \n");
print("run number  $runnumber \n");

$targetdir=$RUNDIR."/../conf/tmp";
$thisdir=$RUNDIR;
$datasetdir=$DATDIR."/".$dataset;
print ("targetdir $targetdir \n");
print ("thisdir $thisdir \n");

$commonstring=".WZphys.root";
$tabchar=".";

$file="local_dataset_".$runnumber.".list";
$tmpfile="temp.list";
print ("datasetdir  $datasetdir \n");
system("cd $datasetdir; rm -f $tmpfile; rm -f $file");
$PWD=`pwd`;
chomp($PWD);
print(" PWD : $PWD \n");
@lastdir=split('\/',$PWD);
$dirname=@lastdir[-1];
print ("last name in the dir : $dirname\n");

#$dir_to_search_in=$datasetdir."/*".$commonstring."*";
$dir_to_search_in=$datasetdir;
#$dir_to_search_in="/storage/t3_data/hod/D3PDntp/rel16/user.hod.WZphysD3PD/submission_08012011/user.hod.WZphys.167576.d28012011.h1012.110128101324";
print ("dir_to_search_in :$dir_to_search_in \n");
$directorylist=$targetdir."/".$file;
print (" file target : $file \n");
open(LISTFILE,">$directorylist");
opendir (DIR, $dir_to_search_in) or die "Couldn't open directory, $!";
foreach (sort grep(/^*\.root$/,readdir(DIR)))
{
  $rootfile=$dataset."/".$_;
  print "file  : $rootfile\n";
  print LISTFILE "$rootfile\n";
}
closedir DIR;
close(LISTFILE);

$jobname="../scripts/tmp/job_".$runnumber.".sh";
print("job name : $jobname \n");
open(JOB,">$jobname");
print JOB "#!/bin/bash \n";
print JOB "cd $RUNDIR \n";
print JOB "export RUNDIR=$RUNDIR \n";
print JOB "source \$RUNDIR/qsub_setup.sh \n";
print JOB "export RUNNUM=$runnumber \n";
print JOB "\$ROOTSYS/bin/root.exe -b -q \$RUNDIR/analysisParallelControlMain.C; \n";
close(JOB);
$qsub="qsub -q N -e tmp/err -o tmp/out $RUNDIR/$jobname";
print (" qsub = $qsub \n");
system($qsub) or print STDERR "couldn't call system: $!";

}

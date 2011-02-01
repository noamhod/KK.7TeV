#!/bin/bash
source /srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/qsub_setup.sh

runnumber=$1
dataset=$2
echo 'DATDIR ' $DATDIR
echo 'dataset ' $dataset
echo 'run number ' $runnumber
source $RUNDIR/makeList.sh	$runnumber	$DATDIR/$dataset
cd $RUNDIR/
export RUNNUM=$runnumber
#$ROOTSYS/bin/root.exe -b -q $RUNDIR/analysisParallelControlMain.C;
export RUNNUM=0

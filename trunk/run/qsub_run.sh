#!/bin/bash/

runnumber=$1
dataset=$2

source $HEREDIR/makeList.sh	$runnumber	$dataset	$CONFDIR	$HEREDIR
cd $HEREDIR/
#root.exe -b -q analysisParallelControlRun.C; load("00-00-91"); alc.initialize($runnumber,"localRunControl_noSkim.txt"); alc.loop(); .q;
export RUNNUM=$runnumber
#root.exe -b -q $HEREDIR/analysisParallelControlRun.C;
$ROOTSYS/bin/root.exe -b -q /srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/analysisParallelControlMain.C;
export RUNNUM=0

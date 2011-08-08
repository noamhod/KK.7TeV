#!/bin/bash
export DATDIR=/storage/t3_data/hod/D3PDntp/rel16/user.hod.WZphysD3PD/submission_08012011
export RUNDIR=/srv01/tau/hod/z0analysis-tests/z0analysis-dev/run
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$RUNDIR
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$RUNDIR/../GoodRunsLists-00-00-91/StandAlone
source ~hod/setROOT528.sh


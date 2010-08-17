#!/bin/bash/

export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH

# date
dateandhour=`date +d%d%m%Y.h%H%M`

# remove the arlier outputs
rm -f input.txt
rm -f z0analysis.root

# get the latest grl and cut flow
cp -f ../conf/cutFlow.cuts .
cp -f ../conf/Z_GRL_152844-159224.xml .

# make usable
chmod 777 cutFlow.cuts
chmod 777 Z_GRL_152844-159224.xml

chmod 777 ../GoodRunsLists-00-00-84/StandAlone/libGoodRunsLists.so


# submit the panda run
prun --exec "echo %IN > input.txt;  root.exe analysisGridControlRun.C;" --athenaTag=15.6.9 --outDS user.hod.z0analysis.$dateandhour --outputs z0analysis.root --inDS group10.phys-sm.data10_7TeV.00159224.physics_MuonswBeam.recon.ESD.x30.WZphys.100612.02.D3PD  --nFiles 2 --extFile analysisGridControl_C.so, ../GoodRunsLists-00-00-84/StandAlone/libGoodRunsLists.so --workDir ../

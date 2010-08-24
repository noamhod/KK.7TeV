#!/bin/bash/

# the data set
#datasetfiles=/tmp/hod/group10.phys-sm.data10_7TeV.00159224.physics_MuonswBeam.recon.ESD.x30.WZphys.100612.02.D3PD.D3PD._01067.root
datasetfiles=$1


# the GRL version
grlvs=00-00-84


# add to LD_LIBRARY_PATH
ispwdld=`echo $LD_LIBRARY_PATH | grep $PWD`
if [ "$ispwdld" = "" ] ; then
   export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$PWD
fi
isgrlld=`echo $LD_LIBRARY_PATH | grep $PWD/GoodRunsLists-$grlvs/StandAlone`
if [ "$isgrlld" = "" ] ; then
   export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$PWD/GoodRunsLists-$grlvs/StandAlone
fi


# date
dateandhour=`date +d%d%m%Y.h%H%M`


# remove the arlier outputs
rm -f input.txt
rm -f z0analysis.root
rm -f Loader_C.so

# get the latest grl and cut flow
cp -u ../conf/cutFlow.cuts .
cp -u ../conf/Z_GRL_152844-159224.xml .


# make usable
chmod 777 cutFlow.cuts
chmod 777 Z_GRL_152844-159224.xml


# submit the local run
echo $datasetfiles > input.txt;  root.exe analysisGridControlRun.C;

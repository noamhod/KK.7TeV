#!/bin/bash/

# mc or data ?
mcordata=$1
controller=analysisGridControlRun.C


# the data set
datasetfiles=$2


# the GRL version
grlvs=00-00-91

runcontrolfile='runControl.txt'


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
#rm -f input.txt
#rm -f WZphys.root
rm -f Loader_C.so

# get the latest grl and cut flow
cp -u ../conf/cutFlow.cuts .
cp -u ../conf/dataPeriods.data .
cp -u ../conf/Z_GRL_CURRENT.xml .


# make usable
chmod 777 cutFlow.cuts
chmod 777 dataPeriods.data
chmod 777 Z_GRL_CURRENT.xml


# submit the local run
rm -f $runcontrolfile;
echo "grid"  >> $runcontrolfile;
echo "staco" >> $runcontrolfile;
if [ "$mcordata" = "mc" ] ; then
   echo "mc" >> $runcontrolfile;
elif [ "$mcordata" = "data" ] ; then
   echo "data" >> $runcontrolfile;
fi

root.exe -b $controller
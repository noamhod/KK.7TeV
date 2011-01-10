#!/bin/bash/

#####################################################################################################
################################ view the job progress in: ##########################################
###### http://panda.cern.ch:25980/server/pandamon/query?ui=register&name=Noam%20Hod&reload=yes ######
#####################################################################################################

# ARGUMENT 1:
#   run type
type=""
mcordata=$1
inputtxt=""
if [ "$mcordata" = "mc" ] ; then
   echo ""
   echo "MC run"
   type="mcWZphys"
   inputtxt="inputMC.txt"
elif [ "$mcordata" = "data" ] ; then
   echo ""
   echo "DATA run"
   type="WZphys"
   inputtxt="input.txt"
else
   exit
fi

# ARGUMENT 2:
#   run number
runnumber=$2
# ARGUMENT 3:
#   dataset name
datasetname=$3

sitename=$4

# the GRL version
grlvs=00-00-91
athenatag=16.0.2
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
rm -f Loader_C.so

# get the latest grl and cut flow
cp -u ../conf/cutFlow.cuts .
cp -u ../conf/dataPeriods.data .
cp -u ../conf/Z_GRL_CURRENT.xml .


# make usable
chmod 777 cutFlow.cuts
chmod 777 dataPeriods.data
chmod 777 Z_GRL_CURRENT.xml


# submit the panda run with a single dataset using --writeInputToTxt
rm -f $runcontrolfile;
echo "grid"  >> $runcontrolfile;
echo "muid" >> $runcontrolfile;
if [ "$mcordata" = "mc" ] ; then
   echo "mc" >> $runcontrolfile;
elif [ "$mcordata" = "data" ] ; then
   echo "data" >> $runcontrolfile;
fi


if [ "$sitename" = "" ] ; then
   prun --exec "root.exe -b -q analysisGridControlRun.C;" --writeInputToTxt IN:$inputtxt  --athenaTag=$athenatag --outDS user.hod.$type.$runnumber.$dateandhour  --outputs $type.root --inDS $datasetname  --extFile analysisGridControl_C.so, Loader_C.so, ../GoodRunsLists-$grlvs/StandAlone/libGoodRunsLists.so --workDir ../  --tmpDir /tmp/hod/prun_info  --nGBPerJob=10
else
   prun --exec "root.exe -b -q analysisGridControlRun.C;" --writeInputToTxt IN:$inputtxt  --athenaTag=$athenatag --outDS user.hod.$type.$runnumber.$dateandhour  --outputs $type.root --inDS $datasetname  --extFile analysisGridControl_C.so, Loader_C.so, ../GoodRunsLists-$grlvs/StandAlone/libGoodRunsLists.so --workDir ../  --tmpDir /tmp/hod/prun_info  --nGBPerJob=10  --site=$sitename
fi

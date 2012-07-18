#!/bin/bash
source /srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/qsub_setup.sh

runnumber=$1
datasetdir=$2
targetdir=$RUNDIR/../conf/tmp
thisdir=$RUNDIR

commonstring='.WZphys.root'
tabchar='.'

file="local_dataset_$runnumber.list"
tmpfile='temp.list'
echo 'datasetdir' $datasetdir
cd $datasetdir
rm -f $tmpfile
rm -f $file
echo 'pwd test'
pwd
echo 'sed test'

dirname=`pwd | sed 's,^\(.*/\)\?\([^/]*\),\2,'`/
echo 'dirname' $dirname
find . | xargs grep $commonstring -sl > $tmpfile
sed -i 's/makeList.sh//g' $tmpfile
sed -i 's/$tmpfile//g' $tmpfile
sed -i "s/\.\///g" $tmpfile
sed -i '/^[ ]*$/d' $tmpfile
sed -i "s|^|$dirname|" $tmpfile
chmod 777 $tmpfile
#sort -t $tabchar +1 -n $tmpfile > $file
sort -u $tmpfile > $file
rm -f $tmpfile
mv -f $file $targetdir/
cd $thisdir

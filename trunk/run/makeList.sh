#!/bin/bash/
runnumber=$1
datasetdir=$2
targetdir=$3
thisdir=$4

commonstring='.WZphys.root'
tabchar='.'

file="local_dataset_$runnumber.list"
tmpfile='temp.list'

cd $datasetdir
rm -f $tmpfile
rm -f $file
find . | xargs grep $commonstring -sl > $tmpfile
#find $datasetdir | xargs grep $commonstring -sl > $tmpfile
sed -i 's/makeList.sh//g' $tmpfile
sed -i 's/$tmpfile//g' $tmpfile
sed -i "s/\.\///g" $tmpfile
sed -i '/^[ ]*$/d' $tmpfile
chmod 777 $tmpfile
#sort -t $tabchar +1 -n $tmpfile > $file
sed -i "s|^|$directory|" $tmpfile
sort -u $tmpfile > $file
rm -f $tmpfile
mv -f $file $targetdir/
cd $thisdir

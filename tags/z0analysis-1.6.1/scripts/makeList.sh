#!/bin/bash/

################################################
commonstring='group10.phys-sm.data10_7TeV'
file='dataset.list'
tabchar='V'
################################################

tmpfile='temp.list'

rm -f $tmpfile
rm -f $file
find . | xargs grep $commonstring -sl > $tmpfile
sed -i 's/analysisControl_C.so//g' $tmpfile
sed -i 's/physics.h//g' $tmpfile
sed -i 's/chains.C//g' $tmpfile
sed -i 's/makeList.sh//g' $tmpfile
sed -i 's/$tmpfile//g' $tmpfile
sed -i "s/\.\///g" $tmpfile
sed -i '/^[ ]*$/d' $tmpfile
#sed -i 's/total //g' $tmpfile
#sed -i 's/drwxr-xr-x  2 hod tauhepgrp 4096 //g' $tmpfile
#sed -i 's/-rw-r--r--  1 hod tauhepgrp  //g' $tmpfile
#sed -i 's/_D3PD/_D3PD._00001.root/g' $tmpfile
#sed -i 's/38 //g' $tmpfile
#sed -i 's/37 //g' $tmpfile

#Remove the last line (twice)
#sed -i '$d' $tmpfile
#sed -i '$d' $tmpfile

sort -t $tabchar +1 -n $tmpfile > file
rm -f $tmpfile

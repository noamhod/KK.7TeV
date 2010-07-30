#!/bin/bash/

commonstring='user.jmbutler.data10_7TeV.'
#commonstring='group10.phys-sm.data10_7TeV'

rm -f dataset.list
find . | xargs grep $commonstring -sl > dataset.list
sed -i 's/analysisControl_C.so//g' dataset.list
sed -i 's/physics.h//g' dataset.list
sed -i 's/chains.C//g' dataset.list
sed -i 's/makeList.sh//g' dataset.list
sed -i 's/dataset.list//g' dataset.list
sed -i "s/\.\///g" dataset.list
sed -i '/^[ ]*$/d' dataset.list
#sed -i 's/total //g' dataset.list
#sed -i 's/drwxr-xr-x  2 hod tauhepgrp 4096 //g' dataset.list
#sed -i 's/-rw-r--r--  1 hod tauhepgrp  //g' dataset.list
#sed -i 's/_D3PD/_D3PD._00001.root/g' dataset.list
#sed -i 's/38 //g' dataset.list
#sed -i 's/37 //g' dataset.list

#Remove the last line (twice)
#sed -i '$d' dataset.list
#sed -i '$d' dataset.list


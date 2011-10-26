#!/bin/bash/
file=$1
day=`date +%d/%m/%Y`
tim=`date +%H:%M`
suffix='*.h *.C'

#sed -i '1 d' $file
#sed -i '2 d' $file
#sed -i '3 d' $file
#sed -i '4 d' $file
#sed -i '5 d' $file
#sed -i '6 d' $file


sed -i '1 i /* * * * * * * * * * * */' $file
sed -i '2 i /* created by Naom Hod */' $file
sed -i '3 i /* noam.hod@cern.ch    */' $file
sed -i '4 i /* noam.com@gmail.com  */' $file
sed -i "5 i /* on $day $tim */"       $file
sed -i '6 i /* * * * * * * * * * * */\n' $file

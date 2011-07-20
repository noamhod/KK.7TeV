#!/bin/bash/

#Arguments:
#    1 ecmEnergy (float) # Center of mass energy parameter in GeV
#    2 runnum (int) # each run number corresponds to one physics process
#    3 firstEvent (int) # number of the first event in the output data file
#  [ 4 maxEvents] (int) default=-1 # Maximum number of events to process
#    5 randomSeed (int) # random seed for physics generators
#    6 jobConfig (list) # jobOptions fragment containing the physics and the configuration settings
#    7 outputEvgenFile (str) # Output file that contains generated events
#    8 outputAODFile (str) # Output file that contains AOD's
#    9 ntupleFile (str) # Output file that contains ntuples.
#  [10 histogramFile] (str) default='NONE' # Output file that contains histograms.
#  [11 inputGeneratorFile] (str) default='NONE' # Input file used by the particle generator to generate events
#  [12 EvgenJobOpts] (str) default='NONE' # Tarball containing the DBRelease to use

dir=$1
name=$2
runnum=$3
nevts=9999
ECM=7000
prefix=00000

if [ ! -d "$dir/$name" ]; then
	mkdir $dir/$name
else
	rm -f $dir/$name/*
fi
cd $dir/$name


if [ -f ${name}.py~ ]; then
	rm -fv ${name}.py~
fi
mv -fv ${name}.py ${name}.py~
cp -fv ../${name}.py .


if [ $runnum -ge 10 ]; then
	prefix=0000
elif [ $runnum -ge 100 ]; then
	prefix=000
elif [ $runnum -ge 1000 ]; then
	prefix=00
elif [ $runnum -ge 10000 ]; then
	prefix=0
elif [ $runnum -ge 100000 ]; then
	prefix=
else
	echo "noam error: RUN NUMBER IS > 10K"
fi



EvgenCorrAtlfast_trf.py   $ECM   $runnum   1   $nevts   1   ${dir}/${name}/${name}.py   ${dir}/${name}/EVNT_${name}   ${dir}/${name}/${name}.AOD._${prefix}${runnum}.pool.root   ${dir}/${name}/${name}.NTUP._${prefix}${runnum}.pool.root

cd -

#!/bin/bash/

#Arguments:
#    1 ecmEnergy (float) # Center of mass energy parameter in GeV
#    2 runNumber (int) # each run number corresponds to one physics process
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

name=$1
filenumber=$2
process=Pythia8_${name}_M1000_mumu
Nevents=10000
ECM=7000
EvgenCorrAtlfast_trf.py  $ECM 0 1 $Nevents 1   ./MC10.000000.$process.py   /tmp/hod/EVNT_${name}_$filenumber   /tmp/hod/MC10.000000.$process.AOD._$filenumber.pool.root   /tmp/hod/MC10.000000.$process.NTUP._$filenumber.pool.root


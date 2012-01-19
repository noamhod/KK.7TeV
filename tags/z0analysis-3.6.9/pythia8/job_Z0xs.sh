#!/bin/bash
min=$1
max=$2
echo   "host = $HOSTNAME"
export PBS_SERVER=tau-ce.hep.tau.ac.il
export ROOTSYS=$HOME/root528c/root
export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
export PATH=$ROOTSYS/bin:$PATH
export RUBYLIB=$ROOTSYS/lib:$RUBYLIB
export PYTHIA8=/srv01/tau/hod/pythia8157
export PYTHIA8DATA=$PYTHIA8/xmldoc
export LHAPDF=/srv01/tau/hod/lhapdf_current
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA8/lib
export PATH=$PATH:$LHAPDF/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LHAPDF/lib
export LHAPATH=$LHAPDF/share/lhapdf
./Z0xs $min $max xs${min}M${max}.dat mumu 10000

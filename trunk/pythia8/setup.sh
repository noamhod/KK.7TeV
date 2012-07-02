export PYTHIA8=/srv01/tau/hod/pythia8157
export PYTHIA8DATA=$PYTHIA8/xmldoc
export LHAPDF=/srv01/tau/hod/lhapdf_current
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA8/lib
export PATH=$PATH:$LHAPDF/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LHAPDF/lib
export LHAPATH=$LHAPDF/share/lhapdf/
source $HOME/setROOT528c.sh

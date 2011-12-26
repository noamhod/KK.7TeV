source setup.sh

g++ -o $1 $1.C -I$PYTHIA8/include `root-config --cflags --glibs` `lhapdf-config --cppflags --ldflags` -L$PYTHIA8/lib -lpythia8 -llhapdfdummy 

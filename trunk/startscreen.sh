#!/bin/bash/
host=$1
dirname=`pwd | sed 's,^\(.*/\)\?\([^/]*\),\2,'`
screen -S Zscreen_$dirname -c scripts/.screenrc_Z_$host

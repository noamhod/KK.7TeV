#!/bin/bash/
dirname=`pwd | sed 's,^\(.*/\)\?\([^/]*\),\2,'`
screen -S screen_$dirname -c .screenrc

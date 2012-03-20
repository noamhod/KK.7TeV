#!/bin/bash

#http://tldp.org/LDP/Bash-Beginners-Guide/html/sect_07_01.html

procname=$1
#null=""
#if [ $procname -eq $null ] then
if test "$procname" == "" ; then
	echo "ERROR: you must provide a screen name, e.g. DYmumu, Pythia6_DYmumu, etc."
	
else
	echo "starting screen_$procname"
	screen -S screen_$procname -c scripts/.screenrc_long_t302
fi

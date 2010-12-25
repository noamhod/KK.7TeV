#!/bin/bash/
name=`date +Day%d%m%YTime%H%M`
suffix='*.h *.C *.sh *.root *.list *.cuts *.inp *.xml'
mkdir $HOME/d3pdAnalysis/$name

#cp -rf $suffix $HOME/d3pdAnalysis/$name/
cp -rf * $HOME/d3pdAnalysis/$name/

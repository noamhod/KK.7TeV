#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
#require 'LoggerDecorator'
include FileUtils

#####################
channel="ee"
gPower="g4"
oversmeared=0
queue="HEP" #########
##########################################################################
puts "DID YOU REMEMBER TO EDIT THE FLAGS IN: fast_templates_run.C" #######
puts "AND TO RUN: broot fast_templates_compile.C  ???" ###################
##########################################################################


### set the base dir
dir = Dir.pwd()

workdir = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run";
thisdir = Dir.getwd();
Dir.chdir(workdir);

mKKmin      = 5130; # GeV
dm          = 100; # GeV
mKKmax      = 6030; # GeV
nMassPoints = (mKKmax-mKKmin)/dm;

def clean(workdir="")
	# %x(rm -f #{workdir}/tmp/*)
	# %x(rm -f #{workdir}/tmp/err/*)
	# %x(rm -f #{workdir}/tmp/out/*)
end

clean(workdir);

minpoint=(mKKmin-130)/dm;   # if mXmin=130 then minpoint=0, if mXmin=5130 then minpoint=50
maxpoint=(mKKmax-130)/dm-1; # if mXmax=5130 then maxpoint=49, if mXmax=6130 then maxpoint=59

#(0..nMassPoints).each do |j|
#	mass = j*dm+mKKmin;
(minpoint..maxpoint+1).each do |j|
	mass = j*dm+130;
	jobname = "#{workdir}/tmp/job#{j}_#{channel}_#{gPower}_smr#{oversmeared}.sh";
	jobfile = File.open(jobname, 'w') { |f|
		f.puts "#!/bin/bash"
		f.puts "echo   \"host = $HOSTNAME\""
		f.puts "cd #{workdir}"
		f.puts "echo $PWD"
		f.puts "echo \"mass=#{mass}\""
		f.puts "export PBS_SERVER=tau-ce.hep.tau.ac.il"
		f.puts "export ROOTSYS=$HOME/root528c/root"
		f.puts "export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH"
		f.puts "export PATH=$ROOTSYS/bin:$PATH"
		f.puts "export RUBYLIB=$ROOTSYS/lib:$RUBYLIB"
		f.puts "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA8/lib"
		f.puts "$ROOTSYS/bin/root.exe -b -l -q #{workdir}/fast_templates_compile.C --channel=#{channel} --gN=#{gPower} --oversmeared=#{oversmeared} --mass=#{mass}"
		f.puts "cd -"
	}
	
	%x(qsub -q #{queue} -e #{workdir}/tmp/err -o #{workdir}/tmp/out #{jobname})
	puts "sent -> #{jobname}"
end

Dir.chdir(thisdir);

puts "DID YOU REMEMBER TO EDIT THE FLAGS IN: fast_templates_run.C"
puts "AND TO RUN: broot fast_templates_compile.C  ???"

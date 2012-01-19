#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
#require 'LoggerDecorator'
include FileUtils

### set the base dir
dir = Dir.pwd()

workdir = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run";
thisdir = Dir.getwd();
Dir.chdir(workdir);

mKKmin      = 200;  #130;  # 500;  # GeV
dm          = 300;  #40;   # 250;  # GeV
mKKmax      = 2900; #3050; # 2000; # GeV
nMassPoints = (mKKmax-mKKmin)/dm;

def clean(workdir="")
	%x(rm -f #{workdir}/tmp/*)
	%x(rm -f #{workdir}/tmp/err/*)
	%x(rm -f #{workdir}/tmp/out/*)
end

def submitjob(jobname="", mass="", workdir="")
	jobfile = File.open(jobname, 'w') { |f| 
		f.puts "#!/bin/bash"
		f.puts "echo   \"host = $HOSTNAME\""
		f.puts "cd #{workdir}"
		f.puts "echo $PWD"
		f.puts "export PBS_SERVER=tau-ce.hep.tau.ac.il"
		f.puts "export ROOTSYS=$HOME/root528c/root"
		f.puts "export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH"
		f.puts "export PATH=$ROOTSYS/bin:$PATH"
		f.puts "export RUBYLIB=$ROOTSYS/lib:$RUBYLIB"
		f.puts "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA8/lib"
		f.puts "$ROOTSYS/bin/root.exe -b -l -q #{workdir}/fast_templates_compile.C --mass=#{mass}"
		f.puts "cd -"
	}
	
	%x(qsub -q S -e #{workdir}/tmp/err -o #{workdir}/tmp/out #{jobname})
	puts "sent --> #{jobname}"
end

clean(workdir);
(0..nMassPoints).each do |j|
	mass = j*dm+mKKmin;
	jobname = "#{workdir}/tmp/job_massnumber_#{j}.sh";
	submitjob(jobname, mass.to_s(), workdir);
end

Dir.chdir(thisdir); 

#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
#require 'LoggerDecorator'
include FileUtils

#####################
sigmaUp="no" #######
queue="S" #########
##########################################################################
puts "DID YOU REMEMBER TO EDIT THE FLAGS IN: fast_templates_run.C" #######
puts "AND TO RUN: broot fast_templates_compile.C  ???" ###################
##########################################################################


### set the base dir
dir = Dir.pwd()

workdir = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run";
thisdir = Dir.getwd();
Dir.chdir(workdir);

mKKmin      = 130; # GeV
dm          = 40; # 100; # GeV
mKKmax      = 3050;# 5030; # GeV
nMassPoints = (mKKmax-mKKmin)/dm;

def clean(workdir="")
	# %x(rm -f #{workdir}/tmp/*)
	# %x(rm -f #{workdir}/tmp/err/*)
	# %x(rm -f #{workdir}/tmp/out/*)
end

def submitjob(jobname="", mass="", workdir="", sigmaUp="no", queue="HEP")
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
		if(sigmaUp=="yes") then
			f.puts "$ROOTSYS/bin/root.exe -b -l -q #{workdir}/fast_templates_compile_up.C --mass=#{mass}"
		else
			f.puts "$ROOTSYS/bin/root.exe -b -l -q #{workdir}/fast_templates_compile.C --mass=#{mass}"
		end
		#f.puts "$ROOTSYS/bin/root.exe -b -l -q #{workdir}/fast_templates_compile.C --mass=#{mass}"
		f.puts "cd -"
	}
	
	%x(qsub -q #{queue} -e #{workdir}/tmp/err -o #{workdir}/tmp/out #{jobname})
	puts "sent -> #{jobname}"
end

clean(workdir);

(0..nMassPoints).each do |j|
	mass = j*dm+mKKmin;
	type = ""
	if(sigmaUp=="yes") then
		type = "sigmaup"
	else
		type = "nominal"
	end
	jobname = "#{workdir}/tmp/job#{j}_#{type}_mc11c.sh";
	submitjob(jobname, mass.to_s(), workdir, sigmaUp, queue);
end

Dir.chdir(thisdir);

puts "DID YOU REMEMBER TO EDIT THE FLAGS IN: fast_templates_run.C"
puts "AND TO RUN: broot fast_templates_compile.C  ???"

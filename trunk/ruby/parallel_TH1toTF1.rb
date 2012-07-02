#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
#require 'LoggerDecorator'
include FileUtils


mKKmin      = 130; # GeV
dm          = 100; # GeV
mKKmax      = 6030;# GeV
nMassPoints = (mKKmax-mKKmin)/dm;

###############################
model = "ZP" # "ZP" or "KK" ###
###############################

### set the base dir
dir = Dir.pwd()

workdir = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run";
thisdir = Dir.getwd();
Dir.chdir(workdir);

outlist = Array.new

(0..nMassPoints).each do |j|
	job_thread = Thread.new(j) { |trd|
		command = "$ROOTSYS/bin/root.exe -b -l -q #{workdir}/TH1toTF1.C+\\(\\\"#{model}\\\",#{trd}\\) > #{workdir}/tmp/inf/job#{model}_#{trd}.info 2>&1"
		system(command)
		puts "sent job -> #{trd}"
	}
	outlist << job_thread
end

# Wait for the threads to finish
outlist.each { |trd|
	trd.join
}

Dir.chdir(thisdir); 

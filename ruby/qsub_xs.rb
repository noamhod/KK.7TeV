#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
#require 'LoggerDecorator'
include FileUtils

# dir = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/pythia8"
# thisdir = Dir.getwd();
# Dir.chdir(dir); 
# y = Dir.getwd();

workdir = "/srv01/tau/hod/z0analysis-tests/z0analysis-r170/pythia8";
thisdir = Dir.getwd();
Dir.chdir(workdir);
mKKmin      = 500;  # 130;  # GeV
dm          = 250;  # 40;   # GeV
mKKmax      = 2000; # 4130; # GeV
nMassPoints = (mKKmax-mKKmin)/dm;

def clean(workdir="")
	#%x(rm -f #{workdir}/tmp/*)
	%x(rm -f #{workdir}/tmp/err/*)
	%x(rm -f #{workdir}/tmp/out/*)
end

def repeat_every(interval)
	# http://stackoverflow.com/questions/2279210/timer-in-ruby-performance
	loop do
		start_time = Time.now
		yield
		elapsed = Time.now - start_time
		sleep([interval - elapsed, 0].max)
	end
end

def wait(interval=5)
	# http://stackoverflow.com/questions/2279210/timer-in-ruby-performance
	iteration=0
	repeat_every(interval) do
		puts "... waiting[#{iteration}]"
		%x(qstat | grep hod > /dev/null)
		if($?!=0) then
			break
		end
		iteration += 1
	end
	seconds = interval*iteration
	puts "!!!---merging (after #{iteration} iterations [#{seconds} seconds])---!!!"
end

def find_substring(string="", prefix="")	
	string = string.gsub("#{prefix}/xs_", '');
	string = string.gsub(".dat", '');
	return string;
end

def search_directory(path="",pattern=".dat")
	# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
	hashmap = Hash.new
	Find.find(path) do |entry|
		if File.file?(entry) and entry[pattern]
			filepath = entry.to_s()
			number   = find_substring(filepath,path)
			lines    = IO.readlines(filepath)
			first    = lines.first.gsub("\n", '');
			hashmap[Float(number)] = first
		end
	end
	hashmap = hashmap.sort
	#puts hashmap
	return hashmap
end

def make_list(workdir="")	
	files = Hash.new
	files = search_directory("#{workdir}/tmp",".dat");
	listfilename = "#{workdir}/xs_merged.list"
	listfile = File.open(listfilename,'w')
	files.each {|key,val|
		listfile.puts "#{val}\n"
	}
	listfile.close
end

def submitjob(jobname="", mKK="", workdir="")
	jobfile = File.open(jobname, 'w') { |f| 
		f.puts "#!/bin/bash"
		f.puts "echo   \"host = $HOSTNAME\""
		f.puts "export PBS_SERVER=tau-ce.hep.tau.ac.il"
		f.puts "export ROOTSYS=$HOME/root528c/root"
		f.puts "export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH"
		f.puts "export PATH=$ROOTSYS/bin:$PATH"
		f.puts "export RUBYLIB=$ROOTSYS/lib:$RUBYLIB"
		f.puts "export PYTHIA8=/srv01/tau/hod/pythia8157"
		f.puts "export PYTHIA8DATA=$PYTHIA8/xmldoc"
		f.puts "export LHAPDF=/srv01/tau/hod/lhapdf_current"
		f.puts "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA8/lib"
		f.puts "export PATH=$PATH:$LHAPDF/bin"
		f.puts "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LHAPDF/lib"
		f.puts "export LHAPATH=$LHAPDF/share/lhapdf"
		f.puts "#{workdir}/KKxs #{mKK} #{workdir}/tmp/xs_#{mKK}.dat"
	}
	
	%x(qsub -q S -e #{workdir}/tmp/err -o #{workdir}/tmp/out #{jobname})
	puts "sent --> #{jobname}"
end

clean(workdir);

(0..nMassPoints).each do |j|
	mKK = j*dm+mKKmin
	# puts "mKK = #{mKK}"
	jobname = "#{workdir}/tmp/job_#{mKK}.sh"
	submitjob(jobname, mKK.to_s(), workdir)
end

wait(10);           # wait 10 seconds
make_list(workdir); # merge the xs values to one list

Dir.chdir(thisdir); 

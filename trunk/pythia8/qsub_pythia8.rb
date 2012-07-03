#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'time'
#require 'LoggerDecorator'
include FileUtils


# quit unless our script gets two command line arguments
unless ARGV.length==6
        puts "Dude, not the right number of arguments."
        puts "Usage: ruby parallel_pythia8.rb  model[=KK/ZP/DY]  submodel[null/ssm/psi/chi/eta/I] channel[=ee/mumu]  mass[=BSM mass in GeV]  maxevts[=any number > 0]  queue[N/HEP/S]\n"
        exit
end

model=ARGV[0]
submodel=ARGV[1]
channel=ARGV[2]
mass=ARGV[3]
maxevts=Integer(ARGV[4])
queue=ARGV[5]

targetdir="/storage/t3_data/hod/2011/pythia8_ntuples_2012/"
thisdir = Dir.getwd();

if(model!="KK" and model!="ZP" and model!="DY")
	puts "Dude,  model[=KK/ZP/DY]"
	exit
end

if(model=="ZP" and (submodel!="ssm" and submodel!="psi" and submodel!="chi" and submodel!="eta" and submodel!="I"))
	puts "Dude,  submodel[ssm/psi/chi/eta/I]"
	exit
end

if(channel!="ee" and channel!="mumu")
	puts "Dude, channel=ee OR channel=mm"
	exit
end

if(queue!="N" and queue!="HEP" and queue!="S")
	puts "Dude, queue[N/HEP/S]"
	exit
end

massbins  = Array.new
massbins  = ["50 250"   ,"250 500"  ,"500 750"  ,"750 1000",
	     "1000 1250","1250 1500","1500 1750","1750 2000",
	     "2000 2250","2250 2500","2500 2750","2750 3000",
	     "3000 3250","3250 3500","3500 3750","3750 4000",
	     "4000 4250","4250 4500","4500 4750","4750 5000"]

massbins.each { |bin|
	binname = bin.gsub(" ","M")
	jobname = "tmp/jobs/#{model}.#{submodel}.m#{mass}.#{binname}.sh"
	jobfile = File.open(jobname, 'w') { |f|
                f.puts "#!/bin/bash"
                f.puts "echo   \"host = $HOSTNAME\""
                f.puts "echo $PWD"
                f.puts "echo \"mass bin name = #{binname}\""
                f.puts "export PBS_SERVER=tau-ce.hep.tau.ac.il"
                f.puts "export ROOTSYS=$HOME/root528c/root"
                f.puts "export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH"
                f.puts "export PATH=$ROOTSYS/bin:$PATH"
                f.puts "export RUBYLIB=$ROOTSYS/lib:$RUBYLIB"
		f.puts "export PYTHIA8=/srv01/tau/hod/pythia8162"
		f.puts "export PYTHIA8DATA=$PYTHIA8/xmldoc"
		f.puts "export LHAPDF=/srv01/tau/hod/lhapdf_current"
		f.puts "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA8/lib"
		f.puts "export PATH=$PATH:$LHAPDF/bin"
		f.puts "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LHAPDF/lib"
		f.puts "export LHAPATH=$LHAPDF/share/lhapdf/"
		f.puts "cd #{thisdir}"
                f.puts "./theory  #{model}  #{submodel}  #{channel}  #{mass}  #{maxevts}  #{bin}"
		f.puts "cd -"
        }

        %x(qsub -q #{queue} -e tmp/err -o tmp/out #{jobname})
        puts "sent -> #{jobname}"
}


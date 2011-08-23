#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
include FileUtils

=begin
[0] compile the analysis code
[1] get the list of datasets directories, build an array of the output root files:
	rootfiles << "run00XXXXXX.root" # in a loop
[2] make a list of all files in each directory according to the run number: "run00XXXXXX.list"
[3] make a job macro for this run analysis
	//run00XXXXXX.C
	{
		gROOT->Reset();
		gROOT->ProcessLine(".L analysisLocalControlMain.C");
		gROOT->ProcessLine("load('00-00-91')");
		gROOT->ProcessLine("alc.initialize('run00XXXXXX')"); // this string has to appear in the output root file name, in the candidates and runSummary txt files and in the memory file name
		gROOT->ProcessLine("alc.loop(0,0)");
	}
[4] execute this macro in a threaded loop:
	%(x root -l -b -q run00XXXXXX.C) # in a loop
[5] wait for the threads to end and merge all the root files:
	%x(hadd -p mearged.root #{rootfiles})
[6] mrege all the run summary txt files and write the final cut flow table
[7] merge all the canddates txt files
=end


class Analysis
	def thisdir
		@@thisdir=pwd()
	end
	
	def initialize(dosetup=false)
		if(dosetup) then
			%x(source $HOME/setROOT528.sh)
		end
	end
	
	def get_run_number(dataset="",prefix="user.wanghill.data11_7TeV.",nchars=8)
		substring = prefix
		return dataset[substring.length,nchars]
	end
	
	def find_substring(string="",substring="._",nchars=5)
		start_ss = string.index(substring)
		return string[start_ss+substring.length, nchars]
	end
	
	def search_directory(path="",pattern=".root",fullprefix="")
		# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
		hashmap = Hash.new
		Find.find(path) do |entry|
			if File.file?(entry) and entry[pattern]
				filepath = entry.to_s()
				number     = get_run_number(filepath,fullprefix,6)
				subnumber  = find_substring(filepath,"._",5)
				fullnumber = "#{number}.#{subnumber}"
				#"key=#{fullnumber} ==> val=#{filepath}\n"
				hashmap[Float(fullnumber)] = filepath
			end
		end

		hashmap = hashmap.sort
		#puts hashmap
		return hashmap
	end
	
	def make_list(datasetdir="",targetdir="",fullprefix="",runnumber="")	
		files = Hash.new
		
		files = search_directory(datasetdir,".root",fullprefix)
		
		listfilename = targetdir+"/../../conf/tmp/#{runnumber}.list"
		listfile = File.open(listfilename,'w')
		files.each {|key,val|
			listfile.puts val
		}
		listfile.close
	end
	
	def analyze(sourcedir="",datasetdir="",targetdir="",macrodir="",dataset="",prefix="")
		#puts dataset
		runnumber = get_run_number(dataset,prefix,6)
		
		fullprefix = sourcedir+"/"+prefix
		
		make_list(datasetdir,targetdir,fullprefix,runnumber)
		
		macroname = "#{macrodir}/macro_#{runnumber}.C"
		
		rundirregular="#{thisdir}/../run"
		rundir='\"'+"#{thisdir}"+'/../run\"'
		
		grltag='\"00-00-91\"'
		singlerun = '\"SINGLERUN\"'
		
		#cd(rundir)
		macrofile = File.open(macroname, 'w') { |f| 
			f.puts "{"
			f.puts "   gROOT->Reset();"
			f.puts "   gROOT->ProcessLine(\".L #{rundirregular}/analysisLocalControlMain.C\");"
			f.puts "   gROOT->ProcessLine(\"load(#{grltag},#{rundir})\");"
			f.puts "   gROOT->ProcessLine(\"alc.initialize(#{runnumber},#{singlerun},#{rundir})\");"
			f.puts "   gROOT->ProcessLine(\"alc.loop(0,0)\");"
			f.puts "   //gROOT->ProcessLine(\".L #{macrodir}/../testMain.C\");"
			f.puts "   //gROOT->ProcessLine(\"print_out(#{runnumber})\");"
			f.puts "}"
		}
		
		%x(root -l -b -q #{macroname} > #{macrodir}/#{runnumber}.log)
		#%x(touch #{targetdir}/run_#{runnumber}.root) #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		#cd(thisdir)
		
	end
	
	def batch_analyze(inlist=[],outlist=[],runnumberslist=[],
					  sourcedir="/data/hod/2011/NTUP_SMDILEP_dimuon_p591",
					  targetdir="/srv01/tau/hod/z0analysis-tests/z0analysis-dev/data/tmp",
					  macrodir="/srv01/tau/hod/z0analysis-tests/z0analysis-dev/run/tmp",
					  prefix="user.wanghill.data11_7TeV.")
		# Set the threads going
		inlist.each{ |dataset|
			puts "submitted #{dataset}"
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset,prefix,6)
				runnumberslist << run
				datasetdir = sourcedir+"/"+dataset
				analyze(sourcedir,datasetdir,targetdir,macrodir,set,prefix)
			}
			outlist << dataset_thread
		}
		puts "SEND THREADS COMPLETE"
		
		# Wait for the threads to finish
		outlist.each { |dataset|
			dataset.join
		}
		puts "JOIN THREADS COMPLETE"
	end
	
	def merge(runnumbers=[], mergedfilename="merged.root", sourcedir="", targetdir="")
		line = String.new
		runnumbers.each { |run|
			line += "  #{sourcedir}/run_#{run}.root"
		}
		%x(hadd -f #{targetdir}/#{mergedfilename}    #{line})
		#puts "hadd -f #{targetdir}/#{mergedfilename}    #{line}"#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		puts "MERGE COMPLETE"
	end
	
	def finalize(targetdir="",macrodir="")
		%x(rm -f #{macrodir}/*.log)
		%x(rm -f #{macrodir}/*.C)
		%x(rm -f #{macrodir}/*.cuts)
		%x(rm -f #{macrodir}/*.txt)
		%x(rm -f #{macrodir}/*.png)
		%x(rm -f #{targetdir}/../../conf/tmp/*.list)
		%x(rm -f #{targetdir}/*.root)
		%x(rm -f #{targetdir}/*.dump)
	end
end


rootfiles = Array.new

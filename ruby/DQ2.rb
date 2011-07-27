#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
include FileUtils

class DQ2
	def thisdir
		@@thisdir=pwd()
	end
	
	def summary_file
		@@summary_file
	end

	def list_file
		@@list_file
	end
	
	def initialize(dosetup=false)
		if(dosetup) then
			%x(source $HOME/setupGrid.sh)
		end
		p Pathname.new($0).realpath()
		puts "current directory = " + thisdir + "\n"
	end
	
	def get_run_number(dataset="",prefix="user.wanghill.data11_7TeV.",nchars=8)
		substring = prefix
		#start_ss = dataset.index(substring)
		#puts dataset[substring.length,nchars]
		return dataset[substring.length,nchars]
	end
	
	def find_substring(string="",substring="._",nchars=5)
		start_ss = string.index(substring)
		return string[start_ss+substring.length, nchars]
	end

	def block_compare(a=0,b=0)
		if a>b then
			return +1
		elsif a<b then
			return -1
		else
			return 0
		end
	end
	
	def check_file(file="", run="", string="0 files failed")
		lines=[]
		File.open( file ) do |io|
			io.each {|line| line.chomp! ; lines << "run "+run+": "+line if(!line.include? string  and  line.length==14)}
		end
		lines
	end
	
	def search_directory(path="",pattern=".root",prefix="/user.wanghill.data11_7TeV.00",hashmap={})
		# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
		fullprefix = path+prefix
		Find.find(path) do |entry|
			if File.file?(entry) and entry[pattern]
				filepath = entry.to_s()
				number    = get_run_number(filepath,fullprefix,6)
				subnumber = find_substring(filepath,"._",5)
				fullnumber = "#{number}.#{subnumber}"
				#puts "key=#{fullnumber}: val=#{filepath}"
				hashmap[Float(fullnumber)] = filepath
			end
		end

		hashmap = hashmap.sort
		puts hashmap
		return hashmap
	end
	
	def dq2get(dir="", run="", dataset="", file="")
		puts dataset
		subdir = dataset[0,dataset.length-1]
		targetdir = thisdir+"/"+dir+"/"+subdir
		logdir    = thisdir+"/"+dir+"/logs"
		%x(mkdir -p #{targetdir})
		%x(rm -f #{logdir+"/"+run}.log)
		if(file=="") then
			%x(dq2-get -H #{targetdir}            #{dataset} > #{logdir+"/"+run}.log 2>&1)
		else
			%x(dq2-get -H #{targetdir} -f #{file} #{dataset} > #{logdir+"/"+run}.log 2>&1)
		end
	end
	
	def dq2validate(dir="", run="", dataset="", file="")
		puts dataset
		subdir = dataset[0,dataset.length-1]
		targetdir = thisdir+"/"+dir+"/"+subdir
		logdir    = thisdir+"/"+dir+"/validation_logs"
		%x(rm -f #{logdir+"/"+run}.log)
		if(file=="") then
			%x(dq2-get -H #{targetdir} -Z            #{dataset} > #{logdir+"/"+run}_validation.log 2>&1)
		else
			%x(dq2-get -H #{targetdir} -Z -f #{file} #{dataset} > #{logdir+"/"+run}_validation.log 2>&1)
		end
		
		logfile = logdir+"/"+run+"_validation.log"
		summary_file = File.open(thisdir+"/"+dir+"/summary.log",'a')
		summary_file.puts check_file(logfile,run,"0 files failed") # nagation
	end
	
	def batch_dq2get(inlist=[],outlist=[],dir="",prefix="")
		logdir = thisdir+"/"+dir+"/logs"
		%x(mkdir -p #{logdir})
		%x(rm -f #{logdir+"/*"})
		# Set the threads going
		inlist.each{ |dataset|
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset,prefix)
				dq2get(dir,run,set)
			}
			outlist << dataset_thread
		}
		
		# Wait for the threads to finish
		outlist.each { |dataset|
			dataset.join
		}
	end
	
	def batch_dq2validate(inlist=[],outlist=[],dir="",prefix="")
		logdir = thisdir+"/"+dir+"/validation_logs"
		%x(mkdir -p #{logdir})
		%x(rm -f #{logdir+"/*"})
		%x(rm -f #{thisdir+"/"+dir+"/summary.log"})
		# Set the threads going
		inlist.each{ |dataset|
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset,prefix)
				dq2validate(dir,run,set)
			}
			outlist << dataset_thread
		}
		
		# Wait for the threads to finish
		outlist.each { |dataset|
			dataset.join
		}
	end
	
	def make_list(dir="")
		files = Hash.new
		path = thisdir+"/"+dir
		prefix="/user.wanghill.data11_7TeV.00"
		files = search_directory(path,".root",prefix,files)
		#files = files.keys.sort
		
		listfile = thisdir+"/"+dir+"/"+dir+"_runs.list"
		list_file = File.open(listfile,'w')
		
		files.each {|key,val|
			puts "#{key} is #{val}"
			list_file.puts val
		}
	end
	
	def dq2ls
	
	end
	
	def finalize(dir="")
		puts "\nsee summary log in: "+thisdir+"/"+dir+"/summary.log"
		puts "\nsee runs list in:   "+thisdir+"/"+dir+"/"+dir+"_runs.list"
		#puts "pid=#{$?.pid}::exitstatus=#{$?.exitstatus}"
	end
end

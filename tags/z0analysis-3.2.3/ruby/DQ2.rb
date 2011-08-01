#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
include FileUtils

class DQ2
	attr_accessor :thisdir, :summary_file, :list_file, :type
	
	def initialize(dosetup=false,stype="data")
		if(dosetup) then
			%x(source $HOME/setupGrid.sh)
		end
		
		@thisdir=pwd()
		@type = stype
		
		#puts "TYPE=#{type}"
		LOG("INFO", "TYPE=#{type}")
		puts ""
	end
	
	def LOG(msgtype="DEBUG",msg="")
		puts "[#{__FILE__} +#{__LINE__}] #{msgtype}: #{msg}"
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

	def dq2get(dir="",run="",dataset="",file="",mcdir="")
		puts dataset
		subdir = dataset[0,dataset.length-1]
		targetdir = ""
		logdir    = ""
		if(type=="data") then
			targetdir = thisdir+"/"+dir+"/"+subdir
			logdir    = thisdir+"/"+dir+"/logs"
		elsif(type=="MC") then
			targetdir = thisdir+"/"+dir+"/"+mcdir+"/"+subdir
			logdir    = thisdir+"/"+dir+"/"+mcdir+"/logs"
		else
			LOG("ERROR","unknown type=#{type}")
			return
		end
		%x(mkdir -p #{targetdir})
		%x(rm -f #{logdir+"/"+run}.log)
		
		if(file=="") then
			#puts "%x(dq2-get -H #{targetdir}            #{dataset} > #{logdir+"/"+mcdir+"."+run}.log 2>&1)"
			%x(dq2-get -H #{targetdir}            #{dataset} > #{logdir+"/"+mcdir+"."+run}.log 2>&1)
		else
			#puts "%x(dq2-get -H #{targetdir} -f #{file} #{dataset} > #{logdir+"/"+mcdir+"."+run}.log 2>&1)"
			%x(dq2-get -H #{targetdir} -f #{file} #{dataset} > #{logdir+"/"+mcdir+"."+run}.log 2>&1)
		end
	end

	def dq2validate(dir="", run="", dataset="", file="", mcdir="")
		puts dataset
		subdir = dataset[0,dataset.length-1]
		targetdir = ""
		logdir    = ""
		if(type=="data") then
			targetdir = thisdir+"/"+dir+"/"+subdir
			logdir    = thisdir+"/"+dir+"/validation_logs"
		elsif(type=="MC") then
			targetdir = thisdir+"/"+dir+"/"+mcdir+"/"+subdir
			logdir    = thisdir+"/"+dir+"/"+mcdir+"/validation_logs"
		else
			LOG("ERROR","uknown type and size of mcdirs")
			return
		end
		
		%x(rm -f #{logdir+"/"+run}.log)
		if(file=="") then
			%x(dq2-get -H #{targetdir} -Z            #{dataset} > #{logdir+"/"+run}.validation.log 2>&1)
			#puts "%x(dq2-get -H #{targetdir} -Z            #{dataset} > #{logdir+"/"+mcdir+"."+run}.validation.log 2>&1)"
		else
			%x(dq2-get -H #{targetdir} -Z -f #{file} #{dataset} > #{logdir+"/"+run}.validation.log 2>&1)
			#puts "%x(dq2-get -H #{targetdir} -Z -f #{file} #{dataset} > #{logdir+"/"+mcdir+"."+run}.validation.log 2>&1)"
		end
		
		logfile = logdir+"/"+mcdir+"."+run+".validation.log"
		summary_file = File.open(thisdir+"/"+dir+"/summary.log",'a')
		summary_file.puts check_file(logfile,run,"0 files failed") # nagation
	end

	def batch_dq2get(inlist=[],outlist=[],dir="",prefix="",mclist={})
		if(mclist.length==0  &&  type=="data") then
			logdir = thisdir+"/"+dir+"/logs"
			%x(mkdir -p #{logdir})
			%x(rm -f #{logdir+"/*"})
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each{|key,val|
				logdir = thisdir+"/"+dir+"/"+key+"/logs"
				%x(mkdir -p #{logdir})
				%x(rm -f #{logdir+"/*"})
			}
		else
			LOG("ERROR","uknown type and size of mcdirs")
			return
		end
	
		# Set the threads going
		inlist.each{ |dataset|
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset,prefix,6)
				mcdir = "#{mclist.index(set)}"
				if(type=="data") then
					dq2get(dir,run,set)
				elsif(type=="MC") then
					dq2get(dir,run,set,"",mcdir)
				else
					LOG("ERROR","uknown type=#{type}")
					return
				end
			}
			outlist << dataset_thread
		}
		
		# Wait for the threads to finish
		outlist.each { |dataset|
			dataset.join
		}
	end

	def batch_dq2get_mc(inlist={},outlist=[],dir="",prefix="")
		mclist = Array.new
		inlist.each {|key,val|
			puts "#{key} is #{val}"
			mclist << val
		}
		batch_dq2get(mclist,outlist,dir,prefix,inlist)
	end
	
	def batch_dq2validate(inlist=[],outlist=[],dir="",prefix="",mclist={})
		if(mclist.length==0  &&  type=="data") then
			logdir = thisdir+"/"+dir+"/validation_logs"
			%x(mkdir -p #{logdir})
			%x(rm -f #{logdir+"/*"})
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each{|key,val|
				logdir = thisdir+"/"+dir+"/"+key+"/validation_logs"
				%x(mkdir -p #{logdir})
				%x(rm -f #{logdir+"/*"})
			}
		else
			LOG("ERROR","uknown type and size of mcdirs")
			return
		end
		%x(rm -f #{thisdir+"/"+dir+"/summary.log"})
		
		# Set the threads going
		inlist.each{ |dataset|
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset,prefix,6)
				mcdir = "#{mclist.index(set)}"
				if(type=="data") then
					dq2validate(dir,run,set)
				elsif(type=="MC") then
					dq2validate(dir,run,set,"",mcdir)
				else
					LOG("ERROR","uknown type=#{type}")
					return
				end
			}
			outlist << dataset_thread
		}
		
		# Wait for the threads to finish
		outlist.each { |dataset|
			dataset.join
		}
	end
	
	def batch_dq2validate_mc(inlist={},outlist=[],dir="",prefix="")
		mclist = Array.new
		inlist.each {|key,val|
			puts "#{key} is #{val}"
			mclist << val
		}
		batch_dq2validate(mclist,outlist,dir,prefix,inlist)
	end
	
	def make_list(dir="",prefix="",mclist={})
		if(mclist.length==0  &&  type=="data") then
			files = Hash.new
			path = thisdir+"/"+dir
			prefix="/"+prefix
			files = search_directory(path,".root",prefix,files)
			listfile = thisdir+"/"+dir+"/"+dir+"_runs.list"
			list_file = File.open(listfile,'w')
			files.each {|key,val|
				puts "#{key} is #{val}"
				list_file.puts val
			}
			list_file.close
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each {|key,val|
				files = Hash.new
				mcdir = key
				path = thisdir+"/"+dir+"/"+mcdir
				prefix="/"+prefix
				files = search_directory(path,".root",prefix,files)
				listfile = thisdir+"/"+dir+"/"+mcdir+"/"+mcdir+"_runs.list"
				list_file = File.new(listfile,'w')
				files.each {|key,val|
					puts "#{key} is #{val}"
					list_file.puts val
				}
				list_file.close
			}
		else
			LOG("ERROR","uknown type=#{type}")
			return
		end
	end
	
	def finalize(dir="")
		puts "\nsee summary log in: "+thisdir+"/"+dir+"/summary.log"
	end
end

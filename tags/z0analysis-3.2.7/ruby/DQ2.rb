#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'LoggerDecorator'
include FileUtils

class DQ2
	attr_accessor :logger,
				  :logd,
				  :targetdir,
				  :prefix,
				  :nchars,
				  :secondprefix,
				  :nsubchars,
				  :summary_file,
				  :list_file,
				  :type
	
	def initialize(dosetup=false)
		if(dosetup) then
			#%x(source ~hod/setupGrid_t302.sh)
			%x(source ~hod/setupGrid.sh)
		end
		
		set_loggerdec("")
		# set_loglvl(Logger::INFO)
		# set_loglvl(Logger::DEBUG)
		# set_loglvl(Logger::WARN)
		# set_loglvl(Logger::ERROR)
		# set_loglvl(Logger::FATAL)
	end
	
	def check_variables
		ok=true
		
		logd.info "target dir = #{targetdir}"
		logd.info "prefix = #{prefix}"
		logd.info "nchars = #{nchars}"
		logd.info "secondprefix = #{secondprefix}"
		logd.info "nsubchars = #{nsubchars}"
		logd.info "summary_file = #{summary_file}"
		logd.info "list_file = #{list_file}"
		logd.info "type = #{type}"
		
		if(!type)	then
			ok=false
			logd.error "type is not set"
		end
		if(!summary_file)	then
			ok=false
			logd.error "summary_file is not set"
		end
		if(!list_file)	then
			ok=false
			logd.error "list_file is not set"
		end
		if(!targetdir)	then
			ok=false
			logd.error "targetdir is not set"
		end
		if(!prefix)	then
			ok=false
			logd.error "prefix is not set"
		end
		if(!nchars)	then
			ok=false
			logd.error "nchars is not set"
		end
		if(!secondprefix)	then
			ok=false
			logd.error "secondprefix is not set"
		end
		if(!nsubchars)	then
			ok=false
			logd.error "nsubchars is not set"
		end
		
		return ok
	end
	
	def set_summary_file(str="")
		@summary_file = str
	end
	
	def set_list_file(str="")
		@list_file = str
	end
	
	def set_type(str="")
		@type = str
	end
	
	def set_targetdir(str="")
		@targetdir = str
	end
	
	def set_prefix(str="",ncr=8)
		@prefix = str
		@nchars = ncr
	end
	
	def set_secondprefix(str="",nsubcr=5)
		@secondprefix = str
		@nsubchars    = nsubcr
	end
	
	def set_loggerdec(logfilename="")
		@logger = Logger.new(STDERR)
		logger = Logger.new(STDOUT)
		if(logfilename!="") then
			@logger = Logger.new(logfilename)
		end
		@logd = LoggerDecorator.new(logger)
	end
	
	def set_loglvl(lvl=Logger::INFO)
		logger.level = lvl
	end
	
	def find_substring(string="", sfindthis="", n=0)
		if(sfindthis==""  and  n==0) then
			start_ss = string.index(secondprefix)
			return string[start_ss+secondprefix.length,nsubchars]
		elsif(sfindthis!=""  and  n>0) then
			return string[Integer(string.index(sfindthis))+Integer(sfindthis.length), n]
		else
			logd.error "in find_substring, sfindthis=#{sfindthis}, n=#{n}"
			return
		end
	end
	
	def get_run_number(string="")
		return find_substring(string,prefix,nchars)
	end
	
	def check_file(file="", run="", string="0 files failed")
		lines=[]
		File.open( file ) do |io|
			io.each {|line| line.chomp! ; lines << "run "+run+": "+line if(!line.include? string  and  line.length==14)}
		end
		lines
	end

	def search_directory(path="",pattern=".root",hashmap={})
		# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
		Find.find(targetdir) do |entry|
			if File.file?(entry) and entry[pattern]
				filepath = entry.to_s()
				number    = ""
				subnumber = ""
				if(type=="MC") then
					number    = find_substring(filepath,prefix,6)
					subnumber = find_substring(filepath,"._",6)
				else
					number    = find_substring(filepath,prefix+"00",6)
					subnumber = find_substring(filepath,"._",5)
				end
				fullnumber = "#{number}.#{subnumber}"
				#logd.info "Hash -> key=#{fullnumber}: val=#{filepath}"
				hashmap[Float(fullnumber)] = filepath
			end
		end

		hashmap = hashmap.sort
		#puts hashmap
		return hashmap
	end

	def dq2get(run="",dataset="",mcname="")
		logd.info "getting -> #{dataset}"
		subdir = dataset[0,dataset.length-1]
		path    = ""
		logdir  = ""
		logfile = ""
		if(type=="data") then
			path   = targetdir+"/"+subdir
			logdir = targetdir+"/logs"
			logfile = "#{logdir+"/"+run}.log"
		elsif(type=="MC") then
			path   = targetdir+"/"+mcname+"/"+subdir
			logdir = targetdir+"/"+mcname+"/logs"
			logfile = "#{logdir+"/"+mcname+"."+run}.log"
		else
			logd.error "unknown type=#{type}"
			return
		end
		
		%x(dq2-get -H #{path} #{dataset} > #{logfile} 2>&1)
	end

	def dq2validate(run="",dataset="",mcname="")
		logd.info "validating -> #{dataset}"
		subdir = dataset[0,dataset.length-1]
		path    = ""
		logdir  = ""
		logfile = ""
		if(type=="data") then
			path    = targetdir+"/"+subdir
			logdir  = targetdir+"/validation_logs"
			logfile = logdir+"/"+run+".validation.log"
		elsif(type=="MC") then
			path    = targetdir+"/"+mcname+"/"+subdir
			logdir  = targetdir+"/"+mcname+"/validation_logs"
			logfile = logdir+"/"+mcname+"."+run+".validation.log"
		else
			logd.error "unknown type=#{type}"
			return
		end
		
		%x(rm -f #{logdir}/*)
		%x(dq2-get -H #{path} -Z #{dataset} > #{logfile} 2>&1)

		f_summary_file = File.open(targetdir+"/"+summary_file,'a')
		f_summary_file.puts check_file(logfile,run,"0 files failed") # nagation
	end

	def batch_dq2get(inlist=[],outlist=[],mclist={})
		if(mclist.length==0  &&  type=="data") then
			logdir = targetdir+"/logs"
			%x(mkdir -p #{logdir})
			%x(rm -f #{logdir}/*)
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each{|key,val|
				mcname = key
				logdir = targetdir+"/"+mcname+"/logs"
				%x(mkdir -p #{logdir})
				%x(rm -f #{logdir}/*)
			}
		else
			logd.error "uknown type and size of mcdirs"
			return
		end
	
		# Set the threads going
		inlist.each{ |dataset|
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset)
				#logd.info "dataset = #{dataset}, run = #{run}"
				mcname = "#{mclist.index(set)}"
				if(type=="data") then
					dq2get(run,set)
				elsif(type=="MC") then
					dq2get(run,set,mcname)
				else
					logd.error "uknown type=#{type}"
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

	def batch_dq2get_mc(inlist={},outlist=[])
		mclist = Array.new
		inlist.each {|key,val|
			#logd.info "Hash -> #{key} is #{val}"
			mclist << val
		}
		batch_dq2get(mclist,outlist,inlist)
	end
	
	def batch_dq2validate(inlist=[],outlist=[],mclist={})
		if(mclist.length==0  &&  type=="data") then
			logdir = targetdir+"/validation_logs"
			%x(mkdir -p #{logdir})
			%x(rm -f #{logdir}/*)
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each{|key,val|
				mcname = key
				logdir = targetdir+"/"+mcname+"/validation_logs"
				%x(mkdir -p #{logdir})
				%x(rm -f #{logdir}/*)
			}
		else
			logd.error "uknown type and size of mcdirs"
			return
		end
		%x(rm -f #{targetdir+"/"+summary_file})
		
		# Set the threads going
		inlist.each{ |dataset|
			dataset_thread = Thread.new(dataset) { |set|
				run = get_run_number(dataset)
				mcname = "#{mclist.index(set)}"
				if(type=="data") then
					dq2validate(run,set)
				elsif(type=="MC") then
					dq2validate(run,set,mcname)
				else
					logd.error "uknown type=#{type}"
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
	
	def batch_dq2validate_mc(inlist={},outlist=[])
		mclist = Array.new
		inlist.each {|key,val|
			#logd.info "Hash -> #{key} is #{val}"
			mclist << val
		}
		batch_dq2validate(mclist,outlist,inlist)
	end
	
	def make_list(mclist={})
		if(mclist.length==0  &&  type=="data") then
			files = Hash.new
			files = search_directory(targetdir,".root",files)
			listfile = targetdir+"/"+list_file
			f_list_file = File.open(listfile,'w')
			files.each {|key,val|
				#logd.info "Hash -> #{key} is #{val}"
				f_list_file.puts val
			}
			f_list_file.close
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each {|key,val|
				files = Hash.new
				mcname = key
				files = search_directory(targetdir+"/"+mcname,".root",files)
				listfile = targetdir+"/"+mcname+"/"+mcname+"_runs.list"
				f_list_file = File.new(listfile,'w')
				files.each {|key,val|
					#logd.info "Hash -> #{key} is #{val}"
					f_list_file.puts val
				}
				f_list_file.close
			}
		else
			logd.error "uknown type=#{type}"
			return
		end
	end
	
	def finalize()
		puts "\nsee summary log in: "+targetdir+"/summary.log"
	end
end

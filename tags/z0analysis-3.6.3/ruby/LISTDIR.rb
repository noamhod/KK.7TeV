#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'LoggerDecorator'
include FileUtils

class LISTDIR
	attr_accessor :logger,
				  :logd,
				  :targetdir,
				  :prefix,
				  :nchars,
				  :secondprefix,
				  :nsubchars,
				  :list_file,
				  :type
	
	def initialize()
		set_loggerdec("")
	end
	
	def check_variables
		ok=true
		
		logd.info "target dir = #{targetdir}"
		logd.info "prefix = #{prefix}"
		logd.info "nchars = #{nchars}"
		logd.info "secondprefix = #{secondprefix}"
		logd.info "nsubchars = #{nsubchars}"
		logd.info "list_file = #{list_file}"
		logd.info "type = #{type}"
		
		if(!type)	then
			ok=false
			logd.error "type is not set"
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

	def search_directory(path="",pattern=".root",hashmap={})
		# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
		# Find.find(targetdir) do |entry|
		Find.find(path) do |entry|
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
	
	def make_list(mclist={})
		if(mclist.length==0  &&  type=="data") then
			files = Hash.new
			files = search_directory(targetdir,".root",files)
			listfile = targetdir+"/"+list_file
			f_list_file = File.open(listfile,'w')
			files.each {|key,val|
				logd.info "Hash -> #{key} is #{val}"
				f_list_file.puts val
			}
			f_list_file.close
		elsif(mclist.length>0  &&  type=="MC") then
			mclist.each {|key,val|
				files = Hash.new
				mcname = key
				path = targetdir+"/"+mcname
				logd.info "SEARCHING IN DIR: "+path
				files = search_directory(path,".root",files)
				listfile = path+"/"+mcname+"_runs.list"
				%x{rm -f #{listfile}}
				f_list_file = File.new(listfile,'w')
				files.each {|key,val|
					#logd.info "Hash -> #{key} is #{val}"
					f_list_file.puts val
				}
				f_list_file.close
				files.clear
			}
		else
			logd.error "uknown type=#{type}"
			return
		end
	end
end

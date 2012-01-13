#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
include FileUtils

if(ARGV.length!=2) then
	puts "Error: need 2 arguments: subdir name and unlink flag (unlink/list)"
	return
end

workdir = "/data/hod/2011";
subdir = ARGV[0];
flag   = ARGV[1];
if(ARGV[1]!="unlink" and ARGV[1]!="list") then
	puts "Error: unlink flag unknown"
	return
end 

def search_directory(path,flag,count,listfilename)
	# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
	Find.find(path) do |entry|
		if !File.file?(entry) and (entry.index(".root") || entry.index(".tgz") || entry.index(".log") || entry.index(".list"))
			filepath = entry.to_s()
			puts "missing: #{filepath}";
			if(flag=="unlink") then
				%x(munlink #{filepath});
			end
			count = count + 1;
			listfile = File.open(listfilename,'a') { |f| 
				f.puts entry
			}
		end
	end
	return count;
end

puts "entering dir: #{workdir}/#{subdir}"
count = 0;
count = search_directory("#{workdir}/#{subdir}", flag, count, "list_missing.dat");
puts "there were #{count} missing files"

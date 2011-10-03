#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'LoggerDecorator'
include FileUtils

def search_directory(dir="", pattern=".tex",list=[])
	# see: http://rosettacode.org/wiki/Walk_a_directory/Recursively
	Find.find(dir) do |entry|
		if File.file?(entry) and entry[pattern]
			filepath = entry.to_s()
			file = filepath[0,filepath.length-4]
			list << file
			puts "F: "+filepath
		end
	end
	list = list.sort
end

texdir = "/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/tex"
thisdir = Dir.getwd();
Dir.chdir(texdir); 
y = Dir.getwd();

%x(rm -f *.dvi)
%x(rm -f *.ps)
%x(rm -f *.pdf)
%x(rm -f *.log)
%x(rm -f *.aux)
%x(rm -f *.tmp)

array = Array.new
search_directory(texdir, ".tex", array)
array.each do |a|
	
	%x{latex #{a}.tex}
	#%x{dvipdf #{a}.dvi}
	%x{dvips -z #{a}.dvi -o #{a}.ps}
	%x{ps2pdf #{a}.ps}
end
Dir.chdir(thisdir); 
#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'time'
#require 'LoggerDecorator'
include FileUtils

def gettime(trial="")
	#t = Time.now
	#timestamp = "day" + t.day.to_s + "." + t.month.to_s + "_hour" + t.hour.to_s + "." + t.min.to_s + "_v#{trial}"
	t = Time.now.asctime
	timestamp = t+"_v#{trial}"
	timestamp = timestamp.gsub(" ",".");
	timestamp = timestamp.gsub(":",".");
	return timestamp
end

puts gettime("2")

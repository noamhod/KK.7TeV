#!/usr/bin/env ruby

dir = ""
str = ""

if(ARGV.length==1) then
	dir = "."
	str = ARGV[0]
	puts "WARNING: dir is not specified - searching within the current dir"
elsif(ARGV.length==2) then
	dir = ARGV[0]
	str = ARGV[1]
else
	puts "ERROR: this script (#{__FILE__}) gets 2 or 1 argumetns"
end

result = %x(find #{dir} | xargs grep '#{str}' -sl)
puts result

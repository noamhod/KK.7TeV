#!/usr/bin/env ruby

if(ARGV.length!=1) then
        puts "ERROR: this script (#{__FILE__}) gets 1 argumetn (the file name to be sorted)"
end

fname = ARGV[0]

f = File.open("#{fname}.sorted","w")
f.puts File.open(fname,"r").read.split("\n").sort_by {|x| x}


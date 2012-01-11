#!/usr/bin/env ruby

def parse_line(line="")
	if(line=="") then return end
	if(line.index("SELECTION")  or  line.index("PRESELECTION")  or  line.index("processed")) then
		line = line.gsub(/\t/," ")
		line = line.gsub("  "," ")
		line = line.gsub("   "," ")
		words = line.split(" ")
		size = words.length
		count = 0
		words.each do |word|
			if(word.index("|")) then next end
			if(word.index(":")) then word = word.gsub(":","") end
			# puts "word[#{count}/#{size}] = #{word}"
			count += 1
		end
		# puts ""
	else
		return
	end
	return words
end

def add_cut(types=[],names=[],evnts=[], type="",name="",evts=0)
	types << type
	names << name
	evnts << evts
end

def add_evts(cutindex=0,evnts=[],evts=0)
	evnts[cutindex] += Integer(evts)
end

files = [
		"/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/run/tmp/RunCutFlow.run_182518.cuts",
		"/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/run/tmp/RunCutFlow.run_182449.cuts"
	]

lastline=-1
firstline=-17
types = Array.new
names = Array.new
evnts = Array.new

filescount=0
files.each{|file|
	lines = IO.readlines(file)[firstline..lastline]
	puts lines
	cutindex = 0
	lines.each do |line|
		words = parse_line(line)
		if(!words) then next end
		if(words.length>0) then
			if(filescount==0) then
				# puts "words[0]=#{words[1]}"
				# puts "words[1]=#{words[2]}"
				# puts "words[2]=#{words[3]}"
				add_cut(types,names,evnts, words[1],words[2],Integer(words[3]))
			else
				add_evts(cutindex,evnts,Integer(words[3]))
			end
		end
		cutindex += 1
	end
	filescount += 1
}

puts "\n\n"

names.each do |name|
	puts "| #{types[names.index(name)]}  #{name}   #{evnts[names.index(name)]}"
end

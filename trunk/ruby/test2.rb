#!/usr/bin/env ruby

def insert(key="", val="", hashmap={})
	hashmap[key] = val
end

def parse_line(idx=0, line="", lbn=[], event=[], origlines=[])
	if(line=="") then return end
	origline = line
	line = line.gsub(/\t/," ")
	line = line.gsub("  "," ")
	words = line.split(" ")
	lbn[idx] = words[2]
	event[idx] = words[3]
	origlines[idx] = origline
	return words
end

def findmaxsize(event=[])
	max = 0
	event.each do |evt|
		if(Float(evt)>max) then
			puts "max=#{max}, now: max -> evt=#{evt}"
			max = Float(evt)
		end
	end
	smax = max.to_s()
	size = smax.length
	return size
end

def buildmap(lbn=[], event=[], origlines=[], hashmap={})
	size = findmaxsize(event)
	puts "size=#{size}"
	subkey = ""
	idx = 0
	event.each do |evt|
		dif = size - evt.length
		puts "dif=#{dif}, evt=#{evt}"
		subkey = evt
		if(dif > 0) then
			for i in 1..dif
				subkey = "0"+subkey
			end
		end
		key = lbn[idx] + "." + subkey
		val = origlines[idx]
		insert(Float(key),val,hashmap)	
		idx += 1
	end
end


hashmap = Hash.new
lbn = Array.new
event = Array.new
origlines = Array.new

#lines = IO.readlines("../run/candidates_all.run_0.cnd")
lines = IO.readlines(ARGV[0])
idx=0
lines.each do |line|
	parse_line(idx,line,lbn,event,origlines)
	idx += 1
end

buildmap(lbn,event,origlines,hashmap)
hashmap = hashmap.sort

#file = File.open("../run/candidates_all.run_0.cnd.sort",'w')
file = File.open("#{ARGV[0]}.sorted",'w')
hashmap.each{|key,val|
	file.puts val	
}
file.close
#puts hashmap

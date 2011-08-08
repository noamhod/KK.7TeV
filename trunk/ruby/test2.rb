#!/usr/bin/env ruby

hashmap = Hash.new

def parse_line(line="", hashmap={})
	if(line=="") then return end
	origline = line
	line = line.gsub(/\t/," ")
	line = line.gsub("  "," ")
	words = line.split(" ")
	size = words.length
	skey = words[2]+"."+words[3]
	key = Float(skey)
	hashmap[key] = origline
	return words
end


lines = IO.readlines("../run/tmp/candidates_all.run_178109.cnd")
lines.each do |line|
	parse_line(line,hashmap)
end

hashmap = hashmap.sort
file = File.open("../run/tmp/candidates_all.run_178109.cnd.sort",'w')
hashmap.each{|key,val|
	file.puts val	
}
file.close
#puts hashmap

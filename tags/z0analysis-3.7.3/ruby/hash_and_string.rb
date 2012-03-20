#!/usr/bin/ruby

def make_list(hmap)
	hmap = hmap.sort
	puts hmap
	hmap.each {|key,value| puts "#{key} is #{value}" }
end

mystring = "Steve was here"
print mystring, "\n"

substring = "was"
start_ss = mystring.index(substring)
mystring[start_ss, substring.length] = "is"
print mystring, "\n"

map = Hash.new
map = {"188254" => "a", "188253" => "c", "188252" => "d", "188251" => "r", "188250" => "z"}

puts map

map.each {|key,val| puts "#{key} is #{val}" }

make_list(map)

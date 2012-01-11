#!/usr/bin/env ruby

# http://lowfatlinux.com/linux-sort.html
# http://stackoverflow.com/questions/2232/calling-bash-commands-from-ruby

tag = "p716"
type = "NTUP_SMWZ"
campaign = "mc11_7TeV"

filename = campaign+"_"+type+"_"+tag

### make the inclusive list, put it in a file and sort it in another file
cmd = "dq2-ls #{campaign}.*#{type}.*#{tag}* > #{filename}.list"
puts cmd
dq2get = %x(#{cmd})
puts dq2get
cmd = "sort +11 -16 #{filename}.list > #{filename}_sorted.list"
puts cmd
sort   = %x(#{cmd})
puts sort



### make a list of all the required muon samples
muonsamples = ["WW_Herwig", "ZZ_Herwig", "WZ_Herwig",
			   "DYmumu",
			   "Zmumu_no_filter",
			   "Wmunu_no_filter",
			   "T1_McAtNlo_Jimmy",
			   "TTbar_McAtNlo_Jimmy",
			   "PythiaB_bbmu15X",
			   "PythiaB_ccmu15X",
			   "AlpgenJimmyWmunuNp",
			   "DYtautau",
			   "Zprime_mumu",
			   "ZStar",
			   "ExtraDimsTEV_m2000_mumu",
			   "ZprimeSSM_m2000_mumu"]


### read the sorted file's lines into an array and sort the array
linesarray = Array.new
file = File.new("#{filename}_sorted.list", "r")
while(line = file.gets)
	
	### skip incomplete / aggregate
	if(line.include?("_sub")) then next end
	if(line.include?("_tid")) then next end
	
	### check if this line points to a required muon sample
	ismuonsample = false
	muonsamples.each{|name|
		#if(line.include?(name)) then
		if(line.index(name)) then
			ismuonsample = true
			break
		end
	}
	if(!ismuonsample) then next end
	
	#puts line
	linesarray.push line
end
file.close
linesarray = linesarray.sort


### write the existing and missing sampels to 2 files
file_existing = File.open("datasets_existing_#{tag}.list", 'w')
file_missing  = File.open("datasets_missing_#{tag}.list",  'w')

firstline = -5;
lastline  = -1;
linesarray.each{ |line|
	line = line.gsub('\n','')
	cmd = "dq2-ls -f -H #{line}"
	result = %x(#{cmd})
	puts "result = #{result}"

	########### get the size if the dataset
	file_tmp_name = "datasets_tmp_#{tag}.list"
	file_tmp      = File.open(file_tmp_name,'w')	
	file_tmp.puts result
	file_tmp.close
	tmplines = IO.readlines(file_tmp_name)[firstline..lastline]
	datasetsize = ""
	nfiles = ""
	if(tmplines!=nil) then
		tmplines.each do |tmpline|
			if(tmpline.index("total size:")) then
				datasetsize = tmpline.gsub("total size:","")
			end
			if(tmpline.index("total files:")) then
				nfiles = tmpline.gsub("total files:","")
			end	
		end
	end
	#######################################
	

	if(result!="") then
		line = line.gsub("\n","")
		datasetsize = datasetsize.gsub("\n","")
		nfiles      = nfiles.gsub("\n","")
		file_existing.puts "#{line} -> #{datasetsize} (#{nfiles} files)"
	elsif
		file_missing.puts line
	end
}
file_existing.close
file_missing.close
#ids = %x[ps ax | grep java | awk '{ print $1 }' | xargs]

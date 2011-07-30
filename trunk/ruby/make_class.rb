#!/usr/bin/env ruby

require 'pathname'
require 'fileutils'
require 'ftools'
require 'find'
require 'strscan'
require 'time'
require 'date'
include FileUtils

:BEFORE
:AFTER
:BELOW


class MakeClass
	def thisdir
		@@thisdir=pwd()
	end
	
	def input_root_file
		@@input_root_file = "/data/hod/2011/MC10b/DYmumu.NTUP_SMWZ/mc10_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574_tid368312_00/NTUP_SMWZ.368312._000001.root.1"
	end
	
	def skeleton_code_file
		@@skeleton_code_file
	end
	
	def initialize(dosetup=false)
		if(dosetup) then
			%x(source $HOME/setROOT528.sh)
		end
	end
	
	def make_class(rootname=input_root_file,treenmae="physics",classnmae="WZphysD3PD")
		puts rootname
		puts treenmae
		puts classnmae
		make_class_file = File.open("make_class.C", 'w') { |f| 
			f.puts "{"
			f.puts "   gROOT->Reset();"
			f.puts "   TFile f(\"#{rootname}\");"
			f.puts "   TTree* t = (TTree*)f.Get(\"#{treenmae}\");"
			f.puts "   t->MakeClass(\"#{classnmae}\");"
			f.puts "}"
		}
		
		%x(root -l -b -q make_class.C)
	end
	
	def replace(filepath, regexp, *args, &block)
		# http://stackoverflow.com/questions/2139058/how-to-insert-a-string-into-a-textfile
		# http://www.ruby-forum.com/topic/156845
		# http://www.public.traineronrails.com/courses/ruby/pages/013-rubyregularexpressions.html
		# It basically reads the file, finds and replaces the line with itself and
		# whatever you want to add in to 'content'.  Then writes back to the file.
		content = File.read(filepath).gsub(regexp, *args, &block)
		File.open(filepath, 'wb') { |file| file.write(content) }
	end
	
	def freplace(hfile="WZphysD3PD.h",atline="",expression="")
		replace(hfile, atline) { |match| expression }
		#replace(hfile, /^#{atline}/mi) { |match| expression }
		#replace(hfile, /#{atline}(.*)/) { |match| expression }
	end
	
	def finsert(hfile="WZphysD3PD.h",atline="",expression="",location=:BELOW)
		#replace(hfile, /^#{atline}/mi) do |match| 
		replace(hfile, atline) do |match| 
			if(location==:BELOW)     then
				"#{match} \n#{expression}"
			elsif(location==:AFTER)  then
				"#{match} #{expression}"
			elsif(location==:BEFORE) then
				"#{expression} #{match}"
			else
				puts "in: fappend -> unsupported location=#{location}"
			end
		end
	end
	
	def matchtype(typesnospace=[],definition="")
		typesnospace.each do |type|
			if(definition.index(type)) then
				return type
			end
		end
		return nil
	end
	
	def propertype(type_nospace,types_nospace=[],propertypes=[])
		index = types_nospace.index(type_nospace)
		if(index) then
			return propertypes[index]
		end
		return nil
	end
	
	def correctmatch(mtcpattern={}, string="")
		mtcpattern.each {|key,val|
			if(string.index(key)) then
				return true
			end
		}
		return false
	end
=begin
	def newfile(filename, lines_to_delete)
		line_arr = File.readlines(filename)
		lines_to_delete.each do |index|
			line_arr.delete_at(index)
		end 
		File.open(filename, "w") do |f| 
			line_arr.each{|line| f.puts(line)}
		end
	end
=end
	def finalize(dir="")
		#puts "pid=#{$?.pid}::exitstatus=#{$?.exitstatus}"
	end
end

filename = "WZphysD3PD.h"

types    = [
			"vector<vector<unsigned short> >","vector<vector<short> >","vector<vector<unsigned int> >","vector<vector<int> >",
			"vector<vector<float> >","vector<vector<double> >",
			"vector<short>","vector<unsigned short>","vector<unsigned int>","vector<int>",
			"vector<float>","vector<double>",
			"bool","unsigned short","short","unsigned int","int","float","double",
			"Bool_t","UInt_t","Int_t","Float_t","Double_t"
			]
			
typesnospace = [
				"vector<vector<unsignedshort>>","vector<vector<short>>","vector<vector<unsignedint>>","vector<vector<int>>",
				"vector<vector<float>>","vector<vector<double>>",
				"vector<short>","vector<unsignedshort>","vector<unsignedint>","vector<int>",
				"vector<float>","vector<double>",
				"bool","unsignedshort","short","unsignedint","int","float","double",
				"Bool_t","UInt_t","Int_t","Float_t","Double_t"
				]
				
requiredpatterns = [
					"RunNumber", "EventNumber", "timestamp", "lbn", "bcid", "mu_muid", "mu_staco", "mu_calo", "hr_mu", "_mu_",
					"muonTruth", "MU", "EF_mu", "met", "MET", "vxp", "mcevt", "mc_", "trigmuonef", "trigmugirl"
					]

excludedpatterns = [
					"jet", "_L2_", "vxp_trk", "mu0", "_mu4_", "_mu4", "_mu4mu6_", "_mu6_", "_mu6", "mu7", "mu11", "mu18", "MU0", "MU6", "Jpsi", "Bmumu", "Upsi", "trk_MET", "cl_MET",
					"ph_MET", "tau_MET", "_2mu4", "_2mu6", "_2mu10", "_2mu13", "2MUL1", "_mu10", "_mu13", "_mu15", "_mu20", "_mu60", "_mu80", "_mu100",
					"L1_TAU", "MET_RefFinal", "MET_DM", "mu20_MSonly", "mu40_MSonly", "mu60_MSonly", "mu80_MSonly", "mu100_MSonly", "_slow", "_empty", "_NoAlg", "emtau", "MET_CellOut",
					"EMPTY", "UNPAIRED", "MU11", "MU15", "MU20", "J10", "2MU"
					]
					
matchedpatterns = { # if key is found accept although value should be excluded (key contains value)
					"EF_mu40_MSonly_barrel" => "EF_mu40_MSonly"
					}
					
truthpatterns     = ["truth", "Truth", "_mc_", "mc_", "mcevt"]

conditionpatterns = ["fChain->SetBranchAddress","fChain->SetBranchStatus", "= 0;"]
					
t = Time.now
puts "\nSTART: is #{t}"


x = MakeClass.new(false)
x.make_class

x.finsert(filename,"public :","   Bool_t          isMC;",:BELOW)
x.freplace(filename,"   WZphysD3PD(TTree *tree=0);","   WZphysD3PD(TTree *tree=0, Bool_t ismc=false);")
x.freplace(filename,"WZphysD3PD::WZphysD3PD(TTree *tree)","WZphysD3PD::WZphysD3PD(TTree *tree, Bool_t ismc)")
x.finsert(filename,"// used to generate this class and read the Tree.","   isMC = ismc;",:BELOW)
x.finsert(filename,"   isMC = ismc;", "\/*\n", :BELOW)
x.freplace(filename,"   Init(tree);", "*/\n   Init(tree);")
x.finsert(filename,"   delete fChain->GetCurrentFile();", "   //", :BEFORE)
x.freplace(filename,"// This function may be called from Loop.", "   if(false) cout << entry << endl;\n// This function may be called from Loop.")
x.finsert(filename,"   virtual Int_t    GetEntry(Long64_t entry);","   virtual void     GetEntryMinimal(Long64_t entry);",:BELOW)
x.freplace(filename,"Int_t WZphysD3PD::GetEntry(Long64_t entry)", "void WZphysD3PD::GetEntryMinimal(Long64_t entry)\n{\n\n}\nInt_t WZphysD3PD::GetEntry(Long64_t entry)")

allvars = Hash.new
minvars = Hash.new


# build the hash table of all the tree variables
File.readlines(filename).each do |line|
	if(!line.index("fChain") and !line.index("= 0") and !line.index("TBranch") and !line.index("TFile")) then
		tmpline = line.gsub(/ /,'')
		tmpline = tmpline.gsub(/\n/,'')
		tmpline = tmpline.gsub(/;/,'')
		type = x.matchtype(typesnospace,tmpline)
		if(type) then
			propertype = x.propertype(type,typesnospace,types)
			tmpline = tmpline.gsub(/#{type}/,propertype)
			allvars[tmpline[propertype.length,tmpline.length]]=propertype
		end
		requiredpatterns.each do |pattern|
			if(line.index(pattern)) then
				tmpline = line.gsub(/ /,'')
				tmpline = tmpline.gsub(/\n/,'')
				tmpline = tmpline.gsub(/;/,'')
				type = x.matchtype(typesnospace,tmpline)
				if(type) then
					propertype = x.propertype(type,typesnospace,types)
					tmpline = tmpline.gsub(/#{type}/,propertype)
					isfound = false
					excludedpatterns.each do |expattern|
						if(tmpline.index(expattern) and !x.correctmatch(matchedpatterns,tmpline)) then # if one of the excluded patterns were found ==> exclude this variable
							isfound = true
							break
						end
					end
					if(!isfound) then
						minvars[tmpline[propertype.length,tmpline.length]]=propertype
					end
				end
			end
		end
	end
end

allvars_file = File.open("tree_variable.list", 'w')
minvars = minvars.sort
minvars.each {|key,val|
	allvars_file.puts "MINVARS: #{key} ==> #{val}"
}
allvars_file.puts "------------------------------------------------\n\n\n------------------------------------------------"
allvars = allvars.sort
allvars.each {|key,val|
	allvars_file.puts "ALLVARS: #{key} ==> #{val}"
}

# disable all the unnecessary branches 
File.readlines(filename).each do |line|
	searchtext = "SetBranchAddress"
	if(line.index(searchtext)) then
		isfound = false
		requiredpatterns.each do |pattern|
			if(line.index(pattern)) then
				isfound = true
				break
			end
		end
		if(!isfound) then # if didn't find one of the required patterns ==> disable the branch
			tmparray = line.split(/"/) #line='fChain->SetBranchAddress("x",&x,&b_x);' ==> split result ["fChain->SetBranchAddress(", "x", ",&x,&b_x);"]
			#newline = "   fChain->SetBranchStatus(\"#{tmparray[1]}\", kFALSE);\n"
			#x.freplace(filename,line,newline)
			x.finsert(filename,line,"//",:BEFORE)
		else
			excludedpatterns.each do |pattern|
				if(line.index(pattern) and !x.correctmatch(matchedpatterns,line)) then # if one of the excluded patterns were found ==> disable the branch
					tmparray = line.split(/"/) #line='fChain->SetBranchAddress("x",&x,&b_x);' ==> split result ["fChain->SetBranchAddress(", "x", ",&x,&b_x);"]
					#newline = "   fChain->SetBranchStatus(\"#{tmparray[1]}\", kFALSE);\n"
					#x.freplace(filename,line,newline)
					x.finsert(filename,line,"//",:BEFORE)
					break
				end
			end
		end
	end
end

# put if condition on truth initializations (ONLY the initializations)
File.readlines(filename).each do |line|
	truthpatterns.each do |truthpattern|
		if(line.index(truthpattern)) then
			conditionpatterns.each do |conditionpattern|
				if(line.index(conditionpattern)) then
					x.finsert(filename, line, "   if(isMC) ", :BEFORE)
					break
				end
			end
		end
	end
end

=begin
# add the GetEntryMinimal() method implementation
previousline = "void WZphysD3PD::GetEntryMinimal(Long64_t entry)\n{"
minvars.each {|key,val|
	#puts "#{key} is #{val}"
	name = key.gsub('*','')
	newline = ""
	isfound = false
	truthpatterns.each do |truthpattern|
		if(name.index(truthpattern) and !x.correctmatch(matchedpatterns,name)) then
			isfound = true
			break
		end
	end
	if(isfound) then
		newline = "   if(isMC)   b_#{name}->GetEntry(entry);\n   _DEBUG(\"\");"
	else
		newline = "   b_#{name}->GetEntry(entry);\n   _DEBUG(\"#{name}\");"
	end
	x.finsert(filename,previousline,newline,:BELOW)
	previousline = newline
}
=end
t = Time.now
puts "\nEND: is #{t}"




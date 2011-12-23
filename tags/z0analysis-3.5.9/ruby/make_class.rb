#!/usr/bin/env ruby


### NEED TO FIX THE DOUBLE OCCURANCES OF (isMC)
### NEED TO FIX THE COMMENTING OF isMC = ismc;
### NEED TO FIX THE BRANCHES COMMENTING;

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
		@@input_root_file = "/data/hod/2011/MC11b/Pythia_DYmumu_75M120_unfiltered/mc11_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/NTUP_SMWZ.525289._000001.root.1"
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
			if(string.include?(key)) then
				return true
			end
		}
		return false
	end

	def finalize(dir="")
		#puts "pid=#{$?.pid}::exitstatus=#{$?.exitstatus}"
	end
end





filename = "WZphysD3PD.h"

types    = [
			"vector<vector<unsigned short> >","vector<vector<short> >","vector<vector<unsigned int> >","vector<vector<int> >",
			"vector<vector<float> >","vector<vector<double> >","vector<vector<string> >",
			"vector<short>","vector<unsigned short>","vector<unsigned int>","vector<int>",
			"vector<float>","vector<double>","vector<string>",
			"bool","unsigned short","short","unsigned int","int","float","double",
			"Bool_t","UInt_t","Int_t","Float_t","Double_t","Char_t"
			]
			
typesnospace = [
				"vector<vector<unsignedshort>>","vector<vector<short>>","vector<vector<unsignedint>>","vector<vector<int>>",
				"vector<vector<float>>","vector<vector<double>>","vector<vector<string>>",
				"vector<short>","vector<unsignedshort>","vector<unsignedint>","vector<int>",
				"vector<float>","vector<double>","vector<string>",
				"bool","unsignedshort","short","unsignedint","int","float","double",
				"Bool_t","UInt_t","Int_t","Float_t","Double_t","Char_t"
				]
				
requiredpatterns = [
					"RunNumber", "EventNumber", "timestamp", "lbn", "bcid", "mu_muid", "mu_staco", "mu_calo", "hr_mu", "_mu_",
					"muonTruth", "MU", "EF_mu", "met", "MET", "vxp", "mcevt", "mc_", "trigmuonef", "trigmugirl"
					]

excludedpatterns = [
					"jet", "_L2_", "vxp_trk", "mu0", "_mu4_", "_mu4", "_mu4mu6_", "_mu6_", "_mu6", "mu7", "mu11", "mu18", "MU0", "MU6", "Jpsi", "Bmumu", "Upsi", "trk_MET", "cl_MET",
					"ph_MET", "tau_MET", "_2mu4", "_2mu6", "_2mu10", "_2mu13", "2MUL1", "_mu10", "_mu13", "_mu15", "_mu20", "_mu60", "_mu80", "_mu100",
					"L1_TAU", "MET_RefFinal", "MET_DM", "mu20_MSonly", "mu40_MSonly", "mu60_MSonly", "mu80_MSonly", "mu100_MSonly", "_slow", "_empty", "_NoAlg", "emtau", "MET_CellOut",
					"EMPTY", "UNPAIRED", "MU11", "MU15", "MU20", "J10", "L1_2MU10", "L1_MU10_EMPTY", "L1_EM5_MU10",
					"trkpt5_", "trk_", "mb_", "mbtime_", "MBTS_", "jet_", "jet_AntiKt", "_jet_AntiKt",
					"trig_L2_", "trig_DB_", "trig_bgCode", "trig_L1_emtau", "trig_L2_emcl", "trig_L2_trk", "trig_L2_el", "trig_L2_ph", "trig_EF_emcl",
					"trig_EF_el", "trig_EF_ph", "trig_Nav", "trig_RoI", "trig_L2_", "el_MET", "trig_L1_esum", "trig_L2_met", "el_",
					"EF_2", "EF_3", "EF_4", "EF_6", "EF_ALFA", "EF_Background", "EF_Co", "EF_HLTTimeBurner", "EF_In", "EF_L1", "EF_Pre", "EF_ROBRequestMon",
					"EF_S", "EF_Tile", "EF_all", "EF_b", "EF_cost", "EF_e", "EF_f", "EF_g", "EF_h", "EF_j", "EF_l", "EF_mb", "EF_j", "EF_j",
					"trig_bg", "ph_", "tau_", "jet_AntiKt", "jet_antikt", "top_hfor_", "hr_el", "hr_roughRecoil", "hr_ueCorrection", "hr_corrRecoil",
					"hr_MET", "cl_", "clpt", "emclpt", "_trk_", "trkpt", "_mb_", "mbtime_", "_MBTS_", "_trig_L2_", "_trig_DB_", "_trig_bg", "_trig_L1_emtau",
					"_EF_2", "_EF_3", "_EF_4", "_EF_6", "_EF_ALFA", "_EF_Background", "_EF_Co", "_EF_HLTTimeBurner", "_EF_In", "_EF_L1", "_EF_Pre", "_EF_ROBRequestMon",
					"_trig_L2_emcl", "_trig_L2_trk_", "_trig_L2_el", "_trig_L2_ph", "_trig_EF_emcl", "_trig_EF_el", "_trig_EF_ph", "_trig_Nav", "_trig_RoI",
					"_trig_L2_muonfeaturedetails", "_trig_L2_combmuonfeature", "_trig_L2_isomuonfeature", "_trig_L2_tilemufeature", "_trig_L2_tiletrack", "_trig_L2_idscan",
					"_trig_L2_sitrack", "_trig_roidescriptor", "_trig_L1_esum", "_trig_L2_met", "_trig_EF_met"
					]
					
matchedpatterns = { # if key is found accept although value should be excluded (key contains value)
					"EF_mu40_MSonly_barrel" => "mu40_MSonly",
					"b_EF_mu40_MSonly_barrel" => "mu40_MSonly",
					"trig_EF_trigmuonef_EF_mu40_MSonly_barrel" => "mu40_MSonly",
					"trig_EF_trigmugirl_EF_mu40_MSonly_barrel" => "mu40_MSonly"
					}
matchedpatternsarray = [
						 "mu40_MSonly_barrel"
						]
					
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
minvarsarray = Array.new
allvarsarray = Array.new

puts "--------- build db ---------"
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
			allvarsarray << tmpline[propertype.length,tmpline.length]
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
						if(tmpline.include?(expattern) and !x.correctmatch(matchedpatterns,tmpline)) then # if one of the excluded patterns were found ==> exclude this variable
							isfound = true
							break
						end
					end
					if(!isfound) then
						minvars[tmpline[propertype.length,tmpline.length]]=propertype
						minvarsarray << tmpline[propertype.length,tmpline.length]
					end
				end
			end
		end
	end
end

puts "--------- sort db ---------"
vars_file = File.open("tree_variable.list", 'w')
minvars = minvars.sort
minvars.each {|key,val|
	vars_file.puts "MINVARS: #{key} ==> #{val}"
}
vars_file.puts "------------------------------------------------\n\n\n------------------------------------------------"
allvars = allvars.sort
allvars.each {|key,val|
	vars_file.puts "ALLVARS: #{key} ==> #{val}"
}

puts "--------- condition truth ---------"
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

puts "--------- start commenting out ---------"
# comment out all unnecessary patterns
File.readlines(filename).each do |line|

	# puts "\nline = "+line

	if(line.include?("//")  and  !line.include?("//!")) then
		next
	elsif(line.length<=1) then
		next
	elsif(line.include?("Bool_t          isMC;")) then
		next
	end
	
	words = line
	words = words.gsub("*b_","*") # for the TBranch definitions
	words = words.gsub(/ /,"|")
	words = words.gsub(/\n/,"|")
	words = words.gsub(/,/,"|")
	words = words.gsub(/&/,"|")
	words = words.gsub(/ = 0/,"|")
	words = words.gsub(/"/,"|")
	words = words.gsub(/;/,"|")
	
	words = words.split("|")
	
	if(words.length<=1) then
		next
	end
	
	words.each do |word|
		if(word.length<=1) then
			next
		end
		if(allvarsarray.index(word)  or  allvarsarray.index("*#{word}")) then
			if(!minvarsarray.index(word)  and  !minvarsarray.index("*#{word}")) then
				x.finsert(filename, line, "//", :BEFORE)
				break
			else
				puts "including branch: #{word}"
				break
			end
		end
	end
end

puts "--------- add new method ---------"
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

t = Time.now
puts "\nEND: is #{t}"
puts "--------- done ---------"



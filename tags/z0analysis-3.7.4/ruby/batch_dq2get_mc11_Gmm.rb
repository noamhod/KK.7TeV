#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia_Gmm_01_1750"	 => 'mc11_7TeV.119588.Pythia_Gmm_01_1750.merge.NTUP_SMWZ.e887_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Gmm_01_2000"	 => 'mc11_7TeV.119589.Pythia_Gmm_01_2000.merge.NTUP_SMWZ.e887_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Gmm_01_2250"	 => 'mc11_7TeV.119590.Pythia_Gmm_01_2250.merge.NTUP_SMWZ.e887_s1310_s1300_r2730_r2700_p756/'
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

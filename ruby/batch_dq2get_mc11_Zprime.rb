#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia_Zprime_mumu_SSM500" => 'mc11_7TeV.115270.Pythia_Zprime_mumu_SSM500.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Zprime_mumu_SSM750"  => 'mc11_7TeV.115271.Pythia_Zprime_mumu_SSM750.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Zprime_mumu_SSM1000" => 'mc11_7TeV.105601.Pythia_Zprime_mumu_SSM1000.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Zprime_mumu_SSM1500" => 'mc11_7TeV.105625.Pythia_Zprime_mumu_SSM1500.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Zprime_mumu_SSM1750" => 'mc11_7TeV.105544.Pythia_Zprime_mumu_SSM1750.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p756/',
			"Pythia_Zprime_mumu_SSM2000" => 'mc11_7TeV.105349.Pythia_Zprime_mumu_SSM2000.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p756/'
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary_Zprime.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

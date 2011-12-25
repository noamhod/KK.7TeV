#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia_DYtautau_75M120_unfiltered"    => 'mc11_7TeV.105488.Pythia_DYtautau_75M120_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_120M250_unfiltered"   => 'mc11_7TeV.105489.Pythia_DYtautau_120M250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_250M400_unfiltered"   => 'mc11_7TeV.105490.Pythia_DYtautau_250M400_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_400M600_unfiltered"   => 'mc11_7TeV.105491.Pythia_DYtautau_400M600_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_600M800_unfiltered"   => 'mc11_7TeV.105492.Pythia_DYtautau_600M800_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_800M1000_unfiltered"  => 'mc11_7TeV.105493.Pythia_DYtautau_800M1000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_1000M1250_unfiltered" => 'mc11_7TeV.105494.Pythia_DYtautau_1000M1250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_1250M1500_unfiltered" => 'mc11_7TeV.105495.Pythia_DYtautau_1250M1500_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_1500M1750_unfiltered" => 'mc11_7TeV.105496.Pythia_DYtautau_1500M1750_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/',
			"Pythia_DYtautau_1750M2000_unfiltered" => 'mc11_7TeV.105497.Pythia_DYtautau_1750M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2780_p801/',
			"Pythia_DYmumu_M2000_unfiltered"       => 'mc11_7TeV.105498.Pythia_DYtautau_M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p801/'
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

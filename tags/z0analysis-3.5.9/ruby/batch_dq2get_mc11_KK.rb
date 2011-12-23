#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia8_ExtraDimsTEV_m2000_mumu_120M450"   => 'mc11_7TeV.145016.Pythia8_ExtraDimsTEV_m2000_mumu_120M450.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_450M850"	=> 'mc11_7TeV.145017.Pythia8_ExtraDimsTEV_m2000_mumu_450M850.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_850M1300"	=> 'mc11_7TeV.145018.Pythia8_ExtraDimsTEV_m2000_mumu_850M1300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_1300M1800"	=> 'mc11_7TeV.145019.Pythia8_ExtraDimsTEV_m2000_mumu_1300M1800.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_1800M2300"	=> 'mc11_7TeV.145020.Pythia8_ExtraDimsTEV_m2000_mumu_1800M2300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_2300M2800"	=> 'mc11_7TeV.145021.Pythia8_ExtraDimsTEV_m2000_mumu_2300M2800.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_2800M3300"	=> 'mc11_7TeV.145022.Pythia8_ExtraDimsTEV_m2000_mumu_2800M3300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ExtraDimsTEV_m2000_mumu_M3300"	    => 'mc11_7TeV.145023.Pythia8_ExtraDimsTEV_m2000_mumu_M3300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',

			"Pythia8_ZprimeSSM_m2000_mumu_120M450"	 => 'mc11_7TeV.145024.Pythia8_ZprimeSSM_m2000_mumu_120M450.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_450M850"	 => 'mc11_7TeV.145025.Pythia8_ZprimeSSM_m2000_mumu_450M850.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_850M1300"	 => 'mc11_7TeV.145026.Pythia8_ZprimeSSM_m2000_mumu_850M1300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_1300M1800" => 'mc11_7TeV.145027.Pythia8_ZprimeSSM_m2000_mumu_1300M1800.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_1800M2300" => 'mc11_7TeV.145028.Pythia8_ZprimeSSM_m2000_mumu_1800M2300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_2300M2800" => 'mc11_7TeV.145029.Pythia8_ZprimeSSM_m2000_mumu_2300M2800.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_2800M3300" => 'mc11_7TeV.145030.Pythia8_ZprimeSSM_m2000_mumu_2800M3300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/',
			"Pythia8_ZprimeSSM_m2000_mumu_M3300"	 => 'mc11_7TeV.145031.Pythia8_ZprimeSSM_m2000_mumu_M3300.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p756/'
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

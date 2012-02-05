#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {

			"Pythia_DYmumu_75M120_unfiltered"	 => 'mc11_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_120M250_unfiltered"	 => 'mc11_7TeV.105478.Pythia_DYmumu_120M250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_250M400_unfiltered"	 => 'mc11_7TeV.105479.Pythia_DYmumu_250M400_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_400M600_unfiltered"	 => 'mc11_7TeV.105480.Pythia_DYmumu_400M600_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_600M800_unfiltered"	 => 'mc11_7TeV.105481.Pythia_DYmumu_600M800_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_800M1000_unfiltered"	 => 'mc11_7TeV.105482.Pythia_DYmumu_800M1000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1000M1250_unfiltered" => 'mc11_7TeV.105483.Pythia_DYmumu_1000M1250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1250M1500_unfiltered" => 'mc11_7TeV.105484.Pythia_DYmumu_1250M1500_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1500M1750_unfiltered" => 'mc11_7TeV.105485.Pythia_DYmumu_1500M1750_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1750M2000_unfiltered" => 'mc11_7TeV.105486.Pythia_DYmumu_1750M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_M2000_unfiltered"	 => 'mc11_7TeV.105487.Pythia_DYmumu_M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/'
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary_DYmumu_p756.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

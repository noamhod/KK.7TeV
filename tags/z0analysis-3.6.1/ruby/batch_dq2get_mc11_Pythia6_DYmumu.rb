#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia6_DYmumu_75M120"    => 'mc11_7TeV.145001.Pythia6_DYmumu_75M120.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			#"Pythia6_DYmumu_120M250"   => '?????????????????????????????????????????????????????????????????????????????????????????',
			"Pythia6_DYmumu_250M400"   => 'mc11_7TeV.145003.Pythia6_DYmumu_250M400.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_400M600"   => 'mc11_7TeV.145004.Pythia6_DYmumu_400M600.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_600M800"   => 'mc11_7TeV.145005.Pythia6_DYmumu_600M800.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_800M1000"  => 'mc11_7TeV.145006.Pythia6_DYmumu_800M1000.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2780_p801/',
			"Pythia6_DYmumu_1000M1250" => 'mc11_7TeV.145007.Pythia6_DYmumu_1000M1250.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_1250M1500" => 'mc11_7TeV.145008.Pythia6_DYmumu_1250M1500.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_1500M1750" => 'mc11_7TeV.145009.Pythia6_DYmumu_1500M1750.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_1750M2000" => 'mc11_7TeV.145010.Pythia6_DYmumu_1750M2000.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2780_p801/',
			"Pythia6_DYmumu_2000M2250" => 'mc11_7TeV.145011.Pythia6_DYmumu_2000M2250.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_2250M2500" => 'mc11_7TeV.145012.Pythia6_DYmumu_2250M2500.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_2500M2750" => 'mc11_7TeV.145013.Pythia6_DYmumu_2500M2750.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_2750M3000" => 'mc11_7TeV.145014.Pythia6_DYmumu_2750M3000.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/',
			"Pythia6_DYmumu_M3000"     => 'mc11_7TeV.145015.Pythia6_DYmumu_M3000.merge.NTUP_SMWZ.e861_s1310_s1300_r2730_r2700_p801/'
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

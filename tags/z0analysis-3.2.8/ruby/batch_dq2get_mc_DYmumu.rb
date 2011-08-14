#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia_DYmumu_75M120_unfiltered"	 => 'mc10_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_120M250_unfiltered"	 => 'mc10_7TeV.105478.Pythia_DYmumu_120M250_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_250M400_unfiltered"	 => 'mc10_7TeV.105479.Pythia_DYmumu_250M400_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_400M600_unfiltered"	 => 'mc10_7TeV.105480.Pythia_DYmumu_400M600_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_600M800_unfiltered"	 => 'mc10_7TeV.105481.Pythia_DYmumu_600M800_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_800M1000_unfiltered"	 => 'mc10_7TeV.105482.Pythia_DYmumu_800M1000_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_1000M1250_unfiltered" => 'mc10_7TeV.105483.Pythia_DYmumu_1000M1250_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_1250M1500_unfiltered" => 'mc10_7TeV.105484.Pythia_DYmumu_1250M1500_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_1500M1750_unfiltered" => 'mc10_7TeV.105485.Pythia_DYmumu_1500M1750_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_1750M2000_unfiltered" => 'mc10_7TeV.105486.Pythia_DYmumu_1750M2000_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
			"Pythia_DYmumu_M2000_unfiltered"	 => 'mc10_7TeV.105487.Pythia_DYmumu_M2000_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',

			"Pythia_Zprime_mumu_SSM1000" => 'mc10_7TeV.105601.Pythia_Zprime_mumu_SSM1000.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p591/',
		 }
outsets = []

x = DQ2.new(true)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC10b_p591")
x.set_summary_file("summary.log")
x.set_list_file("MC10b_runs.list")
x.set_prefix("mc10_7TeV.",6) # irrelevant but needs to be specified
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()
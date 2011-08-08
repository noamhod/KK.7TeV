#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"Pythia_DYmumu_75M120_unfiltered"	 => 'mc10_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/',
			"Pythia_DYtautau_75M120_unfiltered" => 'mc10_7TeV.105488.Pythia_DYtautau_75M120_unfiltered.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/'
		 }
outsets = []

x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/test/MC10b")
x.set_summary_file("summary.log")
x.set_list_file("MC10b_runs.list")
x.set_prefix("mc10_7TeV.",6) # irrelevant but needs to be specified
x.set_secondprefix("._",5)
x.check_variables

#x.batch_dq2get_mc(insets,outsets)
#outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

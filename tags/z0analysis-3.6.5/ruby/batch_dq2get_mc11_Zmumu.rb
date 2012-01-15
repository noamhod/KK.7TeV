#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"PythiaZmumu_no_filter" => 'mc11_7TeV.106047.PythiaZmumu_no_filter.merge.NTUP_SMWZ.e815_s1272_s1274_r2730_r2700_p716_tid525356_00',
			"PythiaWmunu_no_filter" => 'mc11_7TeV.106044.PythiaWmunu_no_filter.merge.NTUP_SMWZ.e815_s1272_s1274_r2730_r2700_p716/'
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary_Zmumu.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()


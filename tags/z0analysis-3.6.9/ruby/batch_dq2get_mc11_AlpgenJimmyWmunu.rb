#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"AlpgenJimmyWmunuNp0_pt20" => 'mc11_7TeV.107690.AlpgenJimmyWmunuNp0_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp1_pt20" => 'mc11_7TeV.107691.AlpgenJimmyWmunuNp1_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp2_pt20" => 'mc11_7TeV.107692.AlpgenJimmyWmunuNp2_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp3_pt20" => 'mc11_7TeV.107693.AlpgenJimmyWmunuNp3_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp4_pt20" => 'mc11_7TeV.107694.AlpgenJimmyWmunuNp4_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp5_pt20" => 'mc11_7TeV.107695.AlpgenJimmyWmunuNp5_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary_AlpgenJimmyWmunu.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

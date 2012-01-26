#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {
			"WW_Herwig" => 'mc11_7TeV.105985.WW_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"ZZ_Herwig" => 'mc11_7TeV.105986.ZZ_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"WZ_Herwig" => 'mc11_7TeV.105987.WZ_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary_diboson.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

#!/usr/bin/env ruby

require 'DQ2'

insets  = [
			'user.wanghill.data11_7TeV.00178109.physics_Muons.merge.NTUP_SMDILEP.r2276_p516_p523_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00178047.physics_Muons.merge.NTUP_SMDILEP.r2276_p516_p523_p591_dimuon_p591/'
		  ]
outsets = []

x = DQ2.new(false)
x.set_type("data")
x.set_targetdir("/data/hod/2011/test/NTUP_SMDILEP_dimuon_p591")
x.set_summary_file("summary.log")
x.set_list_file("NTUP_SMDILEP_dimuon_p591_runs.list")
x.set_prefix("data11_7TeV.",8)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get(insets,outsets)
outsets = []
x.batch_dq2validate(insets,outsets)
x.make_list()
x.finalize()

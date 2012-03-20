#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {

			"T1_McAtNlo_Jimmy"	 => 'mc11_7TeV.105200.T1_McAtNlo_Jimmy.merge.NTUP_SMWZ.e835_a128_r2780_p801/'
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary_TTbar.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(insets)
x.finalize()

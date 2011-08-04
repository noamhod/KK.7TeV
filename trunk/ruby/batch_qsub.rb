#!/usr/bin/env ruby

require 'QSUB'

insets  = [
			'user.wanghill.data11_7TeV.00178109.physics_Muons.merge.NTUP_SMDILEP.r2276_p516_p523_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00178047.physics_Muons.merge.NTUP_SMDILEP.r2276_p516_p523_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00178044.physics_Muons.merge.NTUP_SMDILEP.r2276_p516_p523_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179710.physics_Muons.merge.NTUP_SMDILEP.f361_m796_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179725.physics_Muons.merge.NTUP_SMDILEP.f361_m796_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179739.physics_Muons.merge.NTUP_SMDILEP.f361_m796_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179771.physics_Muons.merge.NTUP_SMDILEP.f362_m801_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179804.physics_Muons.merge.NTUP_SMDILEP.f363_m801_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179938.physics_Muons.merge.NTUP_SMDILEP.f365_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179939.physics_Muons.merge.NTUP_SMDILEP.f366_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00179940.physics_Muons.merge.NTUP_SMDILEP.f366_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180122.physics_Muons.merge.NTUP_SMDILEP.f367_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180124.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180139.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180144.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180149.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180153.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180164.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180212.physics_Muons.merge.NTUP_SMDILEP.f368_m806_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180225.physics_Muons.merge.NTUP_SMDILEP.f368_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180241.physics_Muons.merge.NTUP_SMDILEP.f368_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180242.physics_Muons.merge.NTUP_SMDILEP.f368_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180309.physics_Muons.merge.NTUP_SMDILEP.f369_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180400.physics_Muons.merge.NTUP_SMDILEP.f369_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180448.physics_Muons.merge.NTUP_SMDILEP.f369_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180481.physics_Muons.merge.NTUP_SMDILEP.f369_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180614.physics_Muons.merge.NTUP_SMDILEP.f369_m812_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180636.physics_Muons.merge.NTUP_SMDILEP.f371_m824_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180664.physics_Muons.merge.NTUP_SMDILEP.f371_m824_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180710.physics_Muons.merge.NTUP_SMDILEP.f371_m824_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00180776.physics_Muons.merge.NTUP_SMDILEP.f371_m824_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182013.physics_Muons.merge.NTUP_SMDILEP.f378_m849_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182161.physics_Muons.merge.NTUP_SMDILEP.f379_m849_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182284.physics_Muons.merge.NTUP_SMDILEP.f380_m855_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182346.physics_Muons.merge.NTUP_SMDILEP.f380_m855_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182372.physics_Muons.merge.NTUP_SMDILEP.f380_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182424.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182449.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182450.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182454.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182455.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182456.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182486.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182516.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182518.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182519.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182726.physics_Muons.merge.NTUP_SMDILEP.f381_m861_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182747.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182766.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182787.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182796.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182879.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182886.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00182997.physics_Muons.merge.NTUP_SMDILEP.f382_m866_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183003.physics_Muons.merge.NTUP_SMDILEP.f382_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183021.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183038.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183045.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183054.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183078.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183079.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183081.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183127.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183129.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183130.physics_Muons.merge.NTUP_SMDILEP.f383_m872_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183216.physics_Muons.merge.NTUP_SMDILEP.f383_m878_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183272.physics_Muons.merge.NTUP_SMDILEP.f384_m878_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183286.physics_Muons.merge.NTUP_SMDILEP.f384_m878_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183347.physics_Muons.merge.NTUP_SMDILEP.f384_m878_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183391.physics_Muons.merge.NTUP_SMDILEP.f384_m878_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183407.physics_Muons.merge.NTUP_SMDILEP.f384_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183412.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183426.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183462.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183544.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183580.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183581.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183602.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183780.physics_Muons.merge.NTUP_SMDILEP.f385_m884_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00183963.physics_Muons.merge.NTUP_SMDILEP.f386_m892_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184022.physics_Muons.merge.NTUP_SMDILEP.f386_m892_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184066.physics_Muons.merge.NTUP_SMDILEP.f386_m892_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184072.physics_Muons.merge.NTUP_SMDILEP.f386_m892_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184074.physics_Muons.merge.NTUP_SMDILEP.f386_m892_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184088.physics_Muons.merge.NTUP_SMDILEP.f386_m892_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184130.physics_Muons.merge.NTUP_SMDILEP.f387_m897_p591_dimuon_p591/',
			'user.wanghill.data11_7TeV.00184169.physics_Muons.merge.NTUP_SMDILEP.f387_m897_p591_dimuon_p591/'
		  ]
outlist=[]
runnumbers = Array.new


x = QSUB.new(false)

x.set_thisdir(pwd())
x.set_homedir("/srv01/tau/hod")
x.set_rootdir("/srv01/tau/hod/root528c/root")
x.set_sourcedir("/storage/t3_data/hod/2011/NTUP_SMDILEP_dimuon_p591")
x.set_targetdir("/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/data/tmp")
x.set_macrodir("/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/run/tmp")
x.set_jobdir("/srv01/tau/hod/z0analysis-tests/z0analysis-tmp_qsub/scripts/tmp")
x.set_prefix("user.wanghill.data11_7TeV.00",6)
x.set_secondprefix("._",5)

x.check_variables
#x.batch_qsub(insets,runnumbers)
#x.merge_root(insets,"merged.root")
#x.merge_cutflow(insets,"merged.cutflow")
x.waitNmerge(5,insets,"merged")
x.finalize()

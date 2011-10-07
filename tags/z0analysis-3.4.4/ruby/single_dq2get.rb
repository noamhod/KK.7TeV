#!/usr/bin/env ruby

require 'DQ2'

runnumber  = "00178109"
dataset    = "user.wanghill.data11_7TeV.00178109.physics_Muons.merge.NTUP_SMDILEP.r2276_p516_p523_p591_dimuon_p591/"
file       = "" # all...
targetdir  = "NTUP_SMDILEP_dimuon_p591"
nameprefix = "user.wanghill.data11_7TeV."

x = DQ2.new(false)
x.dq2get(targetdir,runumber,dataset)
x.dq2validate(targetdir,runnumber,dataset,file)
x.finalize(targetdir)

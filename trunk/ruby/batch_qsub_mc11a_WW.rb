#!/usr/bin/env ruby

require 'MCQSUB'

mcname = 'WW_Herwig'
insets  = [
			mcname+'/mc11_7TeV.105985.WW_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/'
			#mcname+'/mc11_7TeV.105985.WW_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2920_r2900_p833/'
		  ]
outlist=[]
runnumbers = Array.new


x = MCQSUB.new(true)

x.set_thisdir(pwd())
x.set_homedir("/srv01/tau/hod")
x.set_mcname(mcname)
x.set_maxlistsize(4)
x.set_nmcjobs(0)
x.set_rootdir("/srv01/tau/hod/root528c/root")
x.set_sourcedir("/storage/t3_data/hod/2011/MC11b")
x.set_targetdir("/srv01/tau/hod/z0analysis-tests/z0analysis-r170/data/tmp")
x.set_macrodir("/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run/tmp")
x.set_jobdir("/srv01/tau/hod/z0analysis-tests/z0analysis-r170/scripts/tmp")
x.set_prefix(mcname+"/mc11_7TeV.",6)
x.set_secondprefix("._",6)
x.set_grltag("00-00-96")
x.set_mcptag("00-05-00")
x.set_prwtag("00-02-01")

x.check_variables
x.batch_qsub(insets,runnumbers,true)

### x.merge_root(insets,"merged.root")
### x.merge_candidates(insets,"merged.candidates")
### x.merge_cutflow(insets,"merged.cutflow")

x.waitNmerge(5,insets,"merged_#{mcname}",true)
x.finalize()

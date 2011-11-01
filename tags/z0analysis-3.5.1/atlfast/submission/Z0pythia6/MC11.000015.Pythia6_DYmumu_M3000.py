###############################################################
# Job options file
# by: Noam Hod
#--------------------------------------------------------------
# Generator Pythia6
#--------------------------------------------------------------
 
# ... Main generator : Pythia
from AthenaCommon.AlgSequence import AlgSequence
topAlg = AlgSequence("TopAlg")
 
include ( "MC11JobOptions/MC11_Pythia_Common.py" )
Pythia.PythiaCommand += [
                         "pydat1 parj 90 9999",      # "pydat1 parj 90 100000"  !!!!
                         "pydat3 mdcy 15 1 0",
                         "pysubs msel 0",
                         "pysubs msub 1 1",
                         "pysubs ckin 1 3000.0",     # Lower invariant mass.
                        #"pysubs ckin 2 3000.0",     # Higher invariant mass.
                         "pydat3 mdme 174 1 0",
                         "pydat3 mdme 175 1 0",
                         "pydat3 mdme 176 1 0",
                         "pydat3 mdme 177 1 0",
                         "pydat3 mdme 178 1 0",
                         "pydat3 mdme 179 1 0",
                         "pydat3 mdme 182 1 0", #ee
                         "pydat3 mdme 183 1 0",
                         "pydat3 mdme 184 1 1", #mumu
                         "pydat3 mdme 185 1 0",
                         "pydat3 mdme 186 1 0", #tautau
                         "pydat3 mdme 187 1 0"]
 
include ( "MC11JobOptions/MC11_Tauola_Fragment.py" )
include ( "MC11JobOptions/MC11_Photos_Fragment.py" )
 

#--------------------------------------------------------------
# Filter
#--------------------------------------------------------------
 

#---------------------------------------------------------------
# POOL / Root output
#---------------------------------------------------------------
 
 
#--------------------------------------------------------------
# Configuration for EvgenJobTransforms
#--------------------------------------------------------------
from MC11JobOptions.EvgenConfig import evgenConfig
evgenConfig.generators += [ "Pythia" ]
evgenConfig.auxfiles += [ 'PDGTABLE.MeV', 'pdt.table', 'DECAY.DEC' ] 
evgenConfig.efficiency = 0.9
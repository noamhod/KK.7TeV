###############################################################
#
# Job options file
# Pythia8 QCD samples
# contact: James Monk, Claire Gwenlan
#==============================================================

# ... Main generator : Pythia8

MessageSvc = Service( "MessageSvc" )
#MessageSvc.OutputLevel = 4

from AthenaCommon.AppMgr import ServiceMgr as svcMgr
 
import AthenaServices
from AthenaCommon.AlgSequence import AlgSequence
topAlg = AlgSequence("TopAlg")
include ("MC10JobOptions/MC10_Pythia8_Common.py")

Pythia8.Commands += ["WeakSingleBoson:ffbar2gmZ = on"]
Pythia8.Commands += ["23:mMin = 120."]
Pythia8.Commands += ["23:mMax = 0."]
Pythia8.Commands += ["23:onMode = off"]
Pythia8.Commands += ["23:onIfAny = 13"]
Pythia8.Commands += ["PhaseSpace:mHatMin = 120."]
Pythia8.Commands += ["PhaseSpace:mHatMax = 0."]

#
from MC10JobOptions.Pythia8EvgenConfig import evgenConfig
evgenConfig.efficiency = 1.

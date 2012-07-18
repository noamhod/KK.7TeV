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

Pythia8.Commands += ["ExtraDimensionsTEV:ffbar2ffbar = on"]
Pythia8.Commands += ["ExtraDimensionsTEV:gmZmode = 3"]
Pythia8.Commands += ["ExtraDimensionsTEV:nMax = 100"]
Pythia8.Commands += ["ExtraDimensionsTEV:mStar = 1000."]
Pythia8.Commands += ["5000023:m0 = 1000."]
Pythia8.Commands += ["5000023:mWidth = 60."]
Pythia8.Commands += ["5000023:mMin = 120."]
Pythia8.Commands += ["5000023:mMax = 0."]
Pythia8.Commands += ["5000023:isResonance = false"]
Pythia8.Commands += ["PhaseSpace:mHatMin = 120."]
Pythia8.Commands += ["PhaseSpace:mHatMax = 0."]

#
from MC10JobOptions.Pythia8EvgenConfig import evgenConfig
evgenConfig.efficiency = 1.

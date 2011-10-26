###############################################################
# Job options file
# Pythia8 ExtraDimensionsTEV
# contact: Noam Hod
#==============================================================

# ... Main generator : Pythia8

MessageSvc = Service( "MessageSvc" )
#MessageSvc.OutputLevel = 4

from AthenaCommon.AppMgr import ServiceMgr as svcMgr
 
import AthenaServices
from AthenaCommon.AlgSequence import AlgSequence
topAlg = AlgSequence("TopAlg")

include ("MC11JobOptions/MC11_Pythia8_Common.py")

Pythia8.Commands += ["ExtraDimensionsTEV:ffbar2ffbar = on"]
Pythia8.Commands += ["ExtraDimensionsTEV:gmZmode = 3"]
Pythia8.Commands += ["ExtraDimensionsTEV:nMax = 100"]
Pythia8.Commands += ["ExtraDimensionsTEV:mStar = 2000."]
Pythia8.Commands += ["5000023:m0 = 2000."]
Pythia8.Commands += ["5000023:mWidth = 120."]
Pythia8.Commands += ["5000023:mMin = 2300."]
Pythia8.Commands += ["5000023:mMax = 2800."]
Pythia8.Commands += ["5000023:isResonance = false"]
Pythia8.Commands += ["PhaseSpace:mHatMin = 2300."]
Pythia8.Commands += ["PhaseSpace:mHatMax = 2800."]

#--------------------------------------------------------------
# Configuration for EvgenJobTransforms
#--------------------------------------------------------------
# efficiency = 0.95 - no filtering
from MC11JobOptions.Pythia8EvgenConfig import evgenConfig
evgenConfig.efficiency = 0.95
#==============================================================
#
# End of job options file
#
###############################################################

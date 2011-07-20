###############################################################
# Job options file
# Pythia8 NewGaugeBoson
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

Pythia8.Commands += ["NewGaugeBoson:ffbar2gmZZprime = on"]
Pythia8.Commands += ["Zprime:gmZmode = 0"]
Pythia8.Commands += ["32:m0 = 2000."]
Pythia8.Commands += ["32:mMin = 3300."]
Pythia8.Commands += ["32:mMax = 0."]
Pythia8.Commands += ["32:onMode = off"]
Pythia8.Commands += ["23:onMode = off"]
Pythia8.Commands += ["32:onIfAny = 13"]
Pythia8.Commands += ["23:onIfAny = 13"]
Pythia8.Commands += ["PhaseSpace:mHatMin = 3300."]
Pythia8.Commands += ["PhaseSpace:mHatMax = 0."]

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

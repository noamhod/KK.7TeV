#!/bin/bash/

source merge.sh DY
source merge.sh ZP_ssm_mBSM1000
source merge.sh ZP_psi_mBSM1000
source merge.sh ZP_chi_mBSM1000
source merge.sh ZP_eta_mBSM1000
source merge.sh KK_mBSM1000

echo "\n DONE MERGING \n";

broot theory_analysis_compile.C --mcname=DY     --channel=mumu --mBSM=-1   --runNum=4 &
broot theory_analysis_compile.C --mcname=ZP_ssm --channel=mumu --mBSM=1000 --runNum=4 &
broot theory_analysis_compile.C --mcname=ZP_psi --channel=mumu --mBSM=1000 --runNum=4 &
broot theory_analysis_compile.C --mcname=ZP_chi --channel=mumu --mBSM=1000 --runNum=4 &
broot theory_analysis_compile.C --mcname=ZP_eta --channel=mumu --mBSM=1000 --runNum=4 &
broot theory_analysis_compile.C --mcname=KK     --channel=mumu --mBSM=1000 --runNum=4 &

echo "\n DONE ANALYSIS \n";

broot hdraw.C++ --mtype=1000 --htype=Mass        --channel=mumu --runNumber=4
broot hdraw.C+ --mtype=1000 --htype=MassAFB_QRK --channel=mumu --runNumber=4
broot hdraw.C+ --mtype=1000 --htype=MassAFB_HE  --channel=mumu --runNumber=4
broot hdraw.C+ --mtype=1000 --htype=MassAFB_CS  --channel=mumu --runNumber=4
broot hdraw.C+ --mtype=1000 --htype=pTLeading   --channel=mumu --runNumber=4

echo "\n DONE ALL ANALYSES - RERUN WITH THE doKK flag set to opposite \n";
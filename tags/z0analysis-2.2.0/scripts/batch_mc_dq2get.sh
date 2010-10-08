#!/bin/bash/

source $HOME/setupGrid.sh

#---------------------------------------------------
# job submit    |  run    | sub |   day   |  hour  |
# script        |  number | set |         |        |
#---------------------------------------------------


# made from:  group10.phys-sm.mc09_7TeV.106047.PythiaZmumu_no_filter.merge.AOD.e468_s765_s767_r1388_r1389.WZphys.100612.12.D3PD
source dq2get_mc_dataset.sh   106047   28092010   0925

# made from:  group10.phys-sm.mc09_7TeV.106044.PythiaWmunu_no_filter.merge.AOD.e468_s765_s767_r1388_r1389.WZphys.100612.12.D3PD
source dq2get_mc_dataset.sh   106044   28092010   0926

# made from:  group10.phys-sm.mc09_7TeV.106052.PythiaZtautau.merge.AOD.e468_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   106052   28092010   0927

# made from:  group10.phys-sm.mc09_7TeV.105861.TTbar_PowHeg_Pythia.merge.AOD.e521_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   105861   28092010   0929

# made from:  group10.phys-sm.mc09_7TeV.108405.PythiaB_bbmu15X.merge.AOD.e521_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   108405   28092010   0930

# made from:  group10.phys-sm.mc09_7TeV.106059.PythiaB_ccmu15X.merge.AOD.e521_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   106059   28092010   0932


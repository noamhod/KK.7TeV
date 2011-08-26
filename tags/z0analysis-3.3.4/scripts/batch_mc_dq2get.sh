#!/bin/bash/

source $HOME/setupGrid.sh

#---------------------------------------------------
# job submit    |  run    | sub |   day   |  hour  |
# script        |  number | set |         |        |
#---------------------------------------------------


# made from:  group10.phys-sm.mc09_7TeV.106047.PythiaZmumu_no_filter.merge.AOD.e468_s765_s767_r1388_r1389.WZphys.100612.12.D3PD
source dq2get_mc_dataset.sh   106047   07112010   0953

# made from:  group10.phys-sm.mc09_7TeV.106044.PythiaWmunu_no_filter.merge.AOD.e468_s765_s767_r1388_r1389.WZphys.100612.12.D3PD
source dq2get_mc_dataset.sh   106044   07112010   0954

# made from:  group10.phys-sm.mc09_7TeV.106052.PythiaZtautau.merge.AOD.e468_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   106052   06112010   1751

# made from:  group10.phys-sm.mc09_7TeV.105861.TTbar_PowHeg_Pythia.merge.AOD.e521_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   105861   06112010   1752

# made from:  group10.phys-sm.mc09_7TeV.108405.PythiaB_bbmu15X.merge.AOD.e521_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   108405   06112010   1753

# made from:  group10.phys-sm.mc09_7TeV.106059.PythiaB_ccmu15X.merge.AOD.e521_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   106059   06112010   1755

# made from:
#group10.phys-sm.mc09_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105478.Pythia_DYmumu_120M250_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105479.Pythia_DYmumu_250M400_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105480.Pythia_DYmumu_400M600_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105481.Pythia_DYmumu_600M800_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105482.Pythia_DYmumu_800M1000_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105483.Pythia_DYmumu_1000M1250_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105484.Pythia_DYmumu_1250M1500_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.02.D3PD
#group10.phys-sm.mc09_7TeV.105485.Pythia_DYmumu_1500M1750_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105486.Pythia_DYmumu_1750M2000_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105487.Pythia_DYmumu_M2000_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   105477   06112010   1733
source dq2get_mc_dataset.sh   105478   06112010   1734
source dq2get_mc_dataset.sh   105479   06112010   1735
source dq2get_mc_dataset.sh   105480   06112010   1736
source dq2get_mc_dataset.sh   105481   06112010   1736
source dq2get_mc_dataset.sh   105482   06112010   1737
source dq2get_mc_dataset.sh   105483   06112010   1738
source dq2get_mc_dataset.sh   105484   06112010   1739
source dq2get_mc_dataset.sh   105485   06112010   1739
source dq2get_mc_dataset.sh   105486   06112010   1740
source dq2get_mc_dataset.sh   105487   06112010   1741

# made from: DYtautau SM background
#group10.phys-sm.mc09_7TeV.105488.Pythia_DYtautau_75M120_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105489.Pythia_DYtautau_120M250_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105490.Pythia_DYtautau_250M400_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105491.Pythia_DYtautau_400M600_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105492.Pythia_DYtautau_600M800_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105493.Pythia_DYtautau_800M1000_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105494.Pythia_DYtautau_1000M1250_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105495.Pythia_DYtautau_1250M1500_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.02.D3PD
#group10.phys-sm.mc09_7TeV.105496.Pythia_DYtautau_1500M1750_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105497.Pythia_DYtautau_1750M2000_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105498.Pythia_DYtautau_M2000_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   105488   06112010   1742
source dq2get_mc_dataset.sh   105489   06112010   1742
source dq2get_mc_dataset.sh   105490   06112010   1743
source dq2get_mc_dataset.sh   105491   06112010   1744
source dq2get_mc_dataset.sh   105492   06112010   1745
source dq2get_mc_dataset.sh   105493   06112010   1745
source dq2get_mc_dataset.sh   105494   06112010   1746
source dq2get_mc_dataset.sh   105495   06112010   1747
source dq2get_mc_dataset.sh   105496   06112010   1748
source dq2get_mc_dataset.sh   105497   06112010   1748
source dq2get_mc_dataset.sh   105498   06112010   1749


# made from: Z'mumu signals
#group10.phys-sm.mc09_7TeV.105534.Pythia_Zprime_mumu_SSM1250.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105544.Pythia_Zprime_mumu_SSM1750.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105601.Pythia_Zprime_mumu_SSM1000.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105625.Pythia_Zprime_mumu_SSM1500.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
#group10.phys-sm.mc09_7TeV.105349.Pythia_Zprime_mumu_SSM2000.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
source dq2get_mc_dataset.sh   105534   06112010   1756
source dq2get_mc_dataset.sh   105544   06112010   1757
source dq2get_mc_dataset.sh   105601   06112010   1758
source dq2get_mc_dataset.sh   105625   08112010   0013
source dq2get_mc_dataset.sh   105349   08112010   0018

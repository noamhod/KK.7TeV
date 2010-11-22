#/bin/bash/

#-------------------------------------------
# job submit       |  run    | sub | dataset
# script           |  number | set | name
#-------------------------------------------

# DY SM
 source panda_run.sh   mc   105483   group10.phys-sm.mc09_7TeV.105483.Pythia_DYmumu_1000M1250_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD

# DYtautau SM background
 source panda_run.sh   mc   105496   group10.phys-sm.mc09_7TeV.105496.Pythia_DYtautau_1500M1750_unfiltered.merge.AOD.e549_s765_s767_r1302_r1306.WZphys.100612.01.D3PD

# Z'mumu signals
 source panda_run.sh   mc   105534   group10.phys-sm.mc09_7TeV.105534.Pythia_Zprime_mumu_SSM1250.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
 source panda_run.sh   mc   105544   group10.phys-sm.mc09_7TeV.105544.Pythia_Zprime_mumu_SSM1750.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
 source panda_run.sh   mc   105601   group10.phys-sm.mc09_7TeV.105601.Pythia_Zprime_mumu_SSM1000.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
 source panda_run.sh   mc   105625   group10.phys-sm.mc09_7TeV.105625.Pythia_Zprime_mumu_SSM1500.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD
 source panda_run.sh   mc   105349   group10.phys-sm.mc09_7TeV.105349.Pythia_Zprime_mumu_SSM2000.merge.AOD.e524_s765_s767_r1302_r1306.WZphys.100612.01.D3PD

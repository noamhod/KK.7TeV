#!/bin/bash/


dir="/data/hod/2011/pythia8_ntuples_2012/"


# name="DY"
# name="ZP_ssm_mBSM1000"
# name="ZP_psi_mBSM1000"
# name="ZP_chi_mBSM1000"
# name="ZP_eta_mBSM1000"
# name="KK_mBSM1000"


name=$1


rm -f ${dir}${name}*_4.root ${dir}${name}*_4.dat


## merge the new (_3) and old (_2) ntuples
hadd ${dir}${name}_mumu_50M150_4.root    ${dir}${name}_mumu_50M150_2.root    ${dir}${name}_mumu_50M150_3.root    ${dir}${name}_mumu_50M150_5.root  
hadd ${dir}${name}_mumu_150M250_4.root   ${dir}${name}_mumu_150M250_2.root   ${dir}${name}_mumu_150M250_3.root   ${dir}${name}_mumu_150M250_5.root   
hadd ${dir}${name}_mumu_250M400_4.root   ${dir}${name}_mumu_250M400_2.root   ${dir}${name}_mumu_250M400_3.root   ${dir}${name}_mumu_250M400_5.root   
hadd ${dir}${name}_mumu_400M600_4.root   ${dir}${name}_mumu_400M600_2.root   ${dir}${name}_mumu_400M600_3.root   ${dir}${name}_mumu_400M600_5.root   
hadd ${dir}${name}_mumu_600M800_4.root   ${dir}${name}_mumu_600M800_2.root   ${dir}${name}_mumu_600M800_3.root   ${dir}${name}_mumu_600M800_5.root   
hadd ${dir}${name}_mumu_800M1000_4.root  ${dir}${name}_mumu_800M1000_2.root  ${dir}${name}_mumu_800M1000_3.root  ${dir}${name}_mumu_800M1000_5.root  
hadd ${dir}${name}_mumu_1000M1250_4.root ${dir}${name}_mumu_1000M1250_2.root ${dir}${name}_mumu_1000M1250_3.root ${dir}${name}_mumu_1000M1250_5.root 
hadd ${dir}${name}_mumu_1250M1500_4.root ${dir}${name}_mumu_1250M1500_2.root ${dir}${name}_mumu_1250M1500_3.root
hadd ${dir}${name}_mumu_1500M1750_4.root ${dir}${name}_mumu_1500M1750_2.root ${dir}${name}_mumu_1500M1750_3.root
hadd ${dir}${name}_mumu_1750M2000_4.root ${dir}${name}_mumu_1750M2000_2.root ${dir}${name}_mumu_1750M2000_3.root 
## cp the other bins to suffix "_4"
cp   ${dir}${name}_mumu_2000M2250_2.root ${dir}${name}_mumu_2000M2250_4.root
cp   ${dir}${name}_mumu_2250M2500_2.root ${dir}${name}_mumu_2250M2500_4.root
cp   ${dir}${name}_mumu_2500M2750_2.root ${dir}${name}_mumu_2500M2750_4.root
cp   ${dir}${name}_mumu_2750M3000_2.root ${dir}${name}_mumu_2750M3000_4.root
cp   ${dir}${name}_mumu_3000M3250_2.root ${dir}${name}_mumu_3000M3250_4.root
cp   ${dir}${name}_mumu_3250M3500_2.root ${dir}${name}_mumu_3250M3500_4.root
cp   ${dir}${name}_mumu_3500M3750_2.root ${dir}${name}_mumu_3500M3750_4.root
cp   ${dir}${name}_mumu_3750M4000_2.root ${dir}${name}_mumu_3750M4000_4.root
cp   ${dir}${name}_mumu_4000M4400_2.root ${dir}${name}_mumu_4000M4400_4.root
cp   ${dir}${name}_mumu_4400M5000_2.root ${dir}${name}_mumu_4400M5000_4.root


## cp the new bins to suffix "_4"
cp ${dir}${name}_mumu_50M150_3.dat    ${dir}${name}_mumu_50M150_4.dat
cp ${dir}${name}_mumu_150M250_3.dat   ${dir}${name}_mumu_150M250_4.dat
cp ${dir}${name}_mumu_250M400_3.dat   ${dir}${name}_mumu_250M400_4.dat
cp ${dir}${name}_mumu_400M600_3.dat   ${dir}${name}_mumu_400M600_4.dat
cp ${dir}${name}_mumu_600M800_3.dat   ${dir}${name}_mumu_600M800_4.dat
cp ${dir}${name}_mumu_800M1000_3.dat  ${dir}${name}_mumu_800M1000_4.dat
cp ${dir}${name}_mumu_1000M1250_3.dat ${dir}${name}_mumu_1000M1250_4.dat
cp ${dir}${name}_mumu_1250M1500_3.dat ${dir}${name}_mumu_1250M1500_4.dat
cp ${dir}${name}_mumu_1500M1750_3.dat ${dir}${name}_mumu_1500M1750_4.dat
cp ${dir}${name}_mumu_1750M2000_3.dat ${dir}${name}_mumu_1750M2000_4.dat
## cp the other bins to suffix "_4"
cp ${dir}${name}_mumu_2000M2250_2.dat ${dir}${name}_mumu_2000M2250_4.dat
cp ${dir}${name}_mumu_2250M2500_2.dat ${dir}${name}_mumu_2250M2500_4.dat
cp ${dir}${name}_mumu_2500M2750_2.dat ${dir}${name}_mumu_2500M2750_4.dat
cp ${dir}${name}_mumu_2750M3000_2.dat ${dir}${name}_mumu_2750M3000_4.dat
cp ${dir}${name}_mumu_3000M3250_2.dat ${dir}${name}_mumu_3000M3250_4.dat
cp ${dir}${name}_mumu_3250M3500_2.dat ${dir}${name}_mumu_3250M3500_4.dat
cp ${dir}${name}_mumu_3500M3750_2.dat ${dir}${name}_mumu_3500M3750_4.dat
cp ${dir}${name}_mumu_3750M4000_2.dat ${dir}${name}_mumu_3750M4000_4.dat
cp ${dir}${name}_mumu_4000M4400_2.dat ${dir}${name}_mumu_4000M4400_4.dat
cp ${dir}${name}_mumu_4400M5000_2.dat ${dir}${name}_mumu_4400M5000_4.dat


## correct the nEvents entry for the new suffix "_4"
sed -i 's/200000/500000/g' ${dir}${name}_mumu_50M150_4.dat
sed -i 's/200000/500000/g' ${dir}${name}_mumu_150M250_4.dat
sed -i 's/200000/500000/g' ${dir}${name}_mumu_250M400_4.dat
sed -i 's/200000/500000/g' ${dir}${name}_mumu_400M600_4.dat
sed -i 's/200000/500000/g' ${dir}${name}_mumu_600M800_4.dat
sed -i 's/200000/500000/g' ${dir}${name}_mumu_800M1000_4.dat
sed -i 's/200000/500000/g' ${dir}${name}_mumu_1000M1250_4.dat
sed -i 's/200000/300000/g' ${dir}${name}_mumu_1250M1500_4.dat
sed -i 's/200000/300000/g' ${dir}${name}_mumu_1500M1750_4.dat
sed -i 's/200000/300000/g' ${dir}${name}_mumu_1750M2000_4.dat


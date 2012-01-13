#!/usr/bin/env ruby

mcarray =
[
	'../conf/pileup_DYmumu_75M120.root',
	'../conf/pileup_DYmumu_120M250.root',
	'../conf/pileup_DYmumu_250M400.root',
	'../conf/pileup_DYmumu_400M600.root',
	'../conf/pileup_DYmumu_600M800.root',
	'../conf/pileup_DYmumu_800M1000.root',
	'../conf/pileup_DYmumu_1000M1250.root',
	'../conf/pileup_DYmumu_1250M1500.root',
	'../conf/pileup_DYmumu_1500M1750.root',
	'../conf/pileup_DYmumu_1750M2000.root',
	'../conf/pileup_DYmumu_M2000.root',

	'../conf/pileup_Pythia6_DYmumu_75M120.root',
	'../conf/pileup_Pythia6_DYmumu_120M250.root',
        '../conf/pileup_Pythia6_DYmumu_250M400.root',
        '../conf/pileup_Pythia6_DYmumu_400M600.root',
        '../conf/pileup_Pythia6_DYmumu_600M800.root',
        '../conf/pileup_Pythia6_DYmumu_800M1000.root',
        '../conf/pileup_Pythia6_DYmumu_1000M1250.root',
        '../conf/pileup_Pythia6_DYmumu_1250M1500.root',
        '../conf/pileup_Pythia6_DYmumu_1500M1750.root',
        '../conf/pileup_Pythia6_DYmumu_1750M2000.root',
        '../conf/pileup_Pythia6_DYmumu_2000M2250.root',
        '../conf/pileup_Pythia6_DYmumu_2250M2500.root',
        '../conf/pileup_Pythia6_DYmumu_2500M2750.root',
        '../conf/pileup_Pythia6_DYmumu_2750M3000.root',
        '../conf/pileup_Pythia6_DYmumu_M3000.root',
	
	'../conf/pileup_DYtautau_75M120.root',
	'../conf/pileup_DYtautau_120M250.root',
	'../conf/pileup_DYtautau_250M400.root',
	'../conf/pileup_DYtautau_400M600.root',
	'../conf/pileup_DYtautau_600M800.root',
	'../conf/pileup_DYtautau_800M1000.root',
	'../conf/pileup_DYtautau_1000M1250.root',
	'../conf/pileup_DYtautau_1250M1500.root',
	'../conf/pileup_DYtautau_1500M1750.root',
	'../conf/pileup_DYtautau_1750M2000.root',
	'../conf/pileup_DYtautau_M2000.root',
	
	'../conf/pileup_Zmumu.root',
	'../conf/pileup_Wmunu.root',

	'../conf/pileup_T1_McAtNlo_Jimmy.root',

	'../conf/pileup_WW_Herwig.root',
	'../conf/pileup_WZ_Herwig.root',
	'../conf/pileup_ZZ_Herwig.root',

	'../conf/pileup_AlpgenJimmyWmunuNp0_pt20.root',
	'../conf/pileup_AlpgenJimmyWmunuNp1_pt20.root',
	'../conf/pileup_AlpgenJimmyWmunuNp2_pt20.root',
	'../conf/pileup_AlpgenJimmyWmunuNp3_pt20.root',
	'../conf/pileup_AlpgenJimmyWmunuNp4_pt20.root',
	'../conf/pileup_AlpgenJimmyWmunuNp5_pt20.root',

	'../conf/pileup_Zprime_mumu_SSM500.root',
	'../conf/pileup_Zprime_mumu_SSM750.root',
	'../conf/pileup_Zprime_mumu_SSM1000.root',
	'../conf/pileup_Zprime_mumu_SSM1500.root',
	'../conf/pileup_Zprime_mumu_SSM1750.root',
	'../conf/pileup_Zprime_mumu_SSM2000.root',

	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_120M450.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_450M850.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_850M1300.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_1300M1800.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_1800M2300.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_2300M2800.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_2800M3300.root',
	'../conf/pileup_Pythia8_ExtraDimsTEV_m2000_mumu_M3300.root',

	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_120M450.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_450M850.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_850M1300.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_1300M1800.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_1800M2300.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_2300M2800.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_2800M3300.root',
	'../conf/pileup_Pythia8_ZprimeSSM_m2000_mumu_M3300.root'
]

line = "hadd -f ../conf/pileup_hadd.root ";
mcarray.each{ |mc|
	line = line + " " + mc;
}
%x(#{line})

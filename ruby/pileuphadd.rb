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
	'../conf/pileup_ZZ_Herwig.root'
]

line = "hadd ../conf/pileup_hadd.root ";
mcarray.each{ |mc|
	line = line + " " + mc;
}
%x(#{line})
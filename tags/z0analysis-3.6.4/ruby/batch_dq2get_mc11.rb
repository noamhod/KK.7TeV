#!/usr/bin/env ruby

require 'DQ2'

insets = Hash.new
insets = {

			"Pythia_DYmumu_75M120_unfiltered"	 => 'mc11_7TeV.105477.Pythia_DYmumu_75M120_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_120M250_unfiltered"	 => 'mc11_7TeV.105478.Pythia_DYmumu_120M250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_250M400_unfiltered"	 => 'mc11_7TeV.105479.Pythia_DYmumu_250M400_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_400M600_unfiltered"	 => 'mc11_7TeV.105480.Pythia_DYmumu_400M600_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_600M800_unfiltered"	 => 'mc11_7TeV.105481.Pythia_DYmumu_600M800_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_800M1000_unfiltered"	 => 'mc11_7TeV.105482.Pythia_DYmumu_800M1000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1000M1250_unfiltered" => 'mc11_7TeV.105483.Pythia_DYmumu_1000M1250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1250M1500_unfiltered" => 'mc11_7TeV.105484.Pythia_DYmumu_1250M1500_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1500M1750_unfiltered" => 'mc11_7TeV.105485.Pythia_DYmumu_1500M1750_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_1750M2000_unfiltered" => 'mc11_7TeV.105486.Pythia_DYmumu_1750M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYmumu_M2000_unfiltered"	 => 'mc11_7TeV.105487.Pythia_DYmumu_M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',

			#"PythiaZmumu_no_filter" => 'mc11_7TeV.106047.PythiaZmumu_no_filter.merge.NTUP_SMWZ.e815_s1272_s1274_r2730_r2700_p716/',
			"PythiaZmumu_no_filter" => 'mc11_7TeV.106047.PythiaZmumu_no_filter.merge.NTUP_SMWZ.e815_s1272_s1274_r2730_r2700_p716_tid525356_00',

			"PythiaWmunu_no_filter" => 'mc11_7TeV.106044.PythiaWmunu_no_filter.merge.NTUP_SMWZ.e815_s1272_s1274_r2730_r2700_p716/',

			### "TTbar_McAtNlo_Jimmy_2mu15_30M150" 	=> 'mc10_7TeV.115374.TTbar_McAtNlo_Jimmy_2mu15_30M150.merge.NTUP_SMWZ.e643_s933_s946_r2302_r2300_p574/',
			### "TTbar_McAtNlo_Jimmy_2mu15_150M300" => 'mc10_7TeV.115375.TTbar_McAtNlo_Jimmy_2mu15_150M300.merge.NTUP_SMWZ.e643_s933_s946_r2302_r2300_p574/',
			### "TTbar_McAtNlo_Jimmy_2mu15_300M450" => 'mc10_7TeV.115376.TTbar_McAtNlo_Jimmy_2mu15_300M450.merge.NTUP_SMWZ.e643_s933_s946_r2302_r2300_p574/',
			### "TTbar_McAtNlo_Jimmy_2mu15_M450" 	=> 'mc10_7TeV.115377.TTbar_McAtNlo_Jimmy_2mu15_M450.merge.NTUP_SMWZ.e643_s933_s946_r2302_r2300_p574/',
			
			"AlpgenJimmyWmunuNp0_pt20" => 'mc11_7TeV.107690.AlpgenJimmyWmunuNp0_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp1_pt20" => 'mc11_7TeV.107691.AlpgenJimmyWmunuNp1_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp2_pt20" => 'mc11_7TeV.107692.AlpgenJimmyWmunuNp2_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp3_pt20" => 'mc11_7TeV.107693.AlpgenJimmyWmunuNp3_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp4_pt20" => 'mc11_7TeV.107694.AlpgenJimmyWmunuNp4_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',
			"AlpgenJimmyWmunuNp5_pt20" => 'mc11_7TeV.107695.AlpgenJimmyWmunuNp5_pt20.merge.NTUP_SMWZ.e825_s1299_s1300_r2730_r2700_p716/',

			"WW_Herwig" => 'mc11_7TeV.105985.WW_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"ZZ_Herwig" => 'mc11_7TeV.105986.ZZ_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"WZ_Herwig" => 'mc11_7TeV.105987.WZ_Herwig.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',

			"Pythia_DYtautau_75M120_unfiltered"    => 'mc11_7TeV.105488.Pythia_DYtautau_75M120_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_120M250_unfiltered"   => 'mc11_7TeV.105489.Pythia_DYtautau_120M250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_250M400_unfiltered"   => 'mc11_7TeV.105490.Pythia_DYtautau_250M400_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_400M600_unfiltered"   => 'mc11_7TeV.105491.Pythia_DYtautau_400M600_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_600M800_unfiltered"   => 'mc11_7TeV.105492.Pythia_DYtautau_600M800_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_800M1000_unfiltered"  => 'mc11_7TeV.105493.Pythia_DYtautau_800M1000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_1000M1250_unfiltered" => 'mc11_7TeV.105494.Pythia_DYtautau_1000M1250_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_1250M1500_unfiltered" => 'mc11_7TeV.105495.Pythia_DYtautau_1250M1500_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_1500M1750_unfiltered" => 'mc11_7TeV.105496.Pythia_DYtautau_1500M1750_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_1750M2000_unfiltered" => 'mc11_7TeV.105497.Pythia_DYtautau_1750M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',
			"Pythia_DYtautau_M2000_unfiltered"     => 'mc11_7TeV.105498.Pythia_DYtautau_M2000_unfiltered.merge.NTUP_SMWZ.e825_s1310_s1300_r2730_r2700_p716/',

			### "Pythia_Zprime_mumu"		 => 'mc10_7TeV.115495.Pythia_Zprime_mumu.merge.NTUP_SMWZ.e670_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM250"  => 'mc10_7TeV.115269.Pythia_Zprime_mumu_SSM250.merge.NTUP_SMWZ.e660_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM500"  => 'mc10_7TeV.115270.Pythia_Zprime_mumu_SSM500.merge.NTUP_SMWZ.e660_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM750"  => 'mc10_7TeV.115271.Pythia_Zprime_mumu_SSM750.merge.NTUP_SMWZ.e660_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM1000" => 'mc10_7TeV.105601.Pythia_Zprime_mumu_SSM1000.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM1250" => 'mc10_7TeV.105534.Pythia_Zprime_mumu_SSM1250.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM1500" => 'mc10_7TeV.105625.Pythia_Zprime_mumu_SSM1500.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM1750" => 'mc10_7TeV.105544.Pythia_Zprime_mumu_SSM1750.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/',
			### "Pythia_Zprime_mumu_SSM2000" => 'mc10_7TeV.105349.Pythia_Zprime_mumu_SSM2000.merge.NTUP_SMWZ.e574_s933_s946_r2302_r2300_p574/'
		 }
outsets = []



x = DQ2.new(false)
x.set_type("MC")
x.set_targetdir("/data/hod/2011/MC11b")
x.set_summary_file("summary.log")
x.set_list_file("MC11b.list")
x.set_prefix("mc11_7TeV.",6)
x.set_secondprefix("._",5)
x.check_variables

x.batch_dq2get_mc(insets,outsets)
outsets = []
x.batch_dq2validate_mc(insets,outsets)
x.make_list(outsets)
x.finalize()

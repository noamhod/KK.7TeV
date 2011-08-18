#include "all.h"


// bins for the mHat histos
double    imassmin   = 75.; //GeV
double    imassmax   = 4000.; // GeV
const int nimassbins = 100;
static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nimassbins+1];
bool doLogx = true;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvHistos;
vector<double> dvWeights;
vector<Color_t> cvColors;
string sDir  = "/data/hod/newATLFAST/NEW/";
string sSubDir  = "";
string sSubSubDir  = "";
string sName = "";

TLorentzVector* pa = new TLorentzVector();
TLorentzVector* pb = new TLorentzVector();

void addSample(string path, string file, string name, Color_t color, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(path+file);
	if(doLogx) hvHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nimassbins,xbins));
	else       hvHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nimassbins,imassmin,imassmax));
	dvWeights.push_back(luminosity/(events/(sigma*nb2fb)));
	cvColors.push_back(color);
}

int plot_binned_samples()
{
	style();
	
	global_dbg_lvl = SILENT;
	
	float mHat;
	float qT;
	float ysystem;
	float cosThetaHE;
	float cosThetaCS;
	
	TMapdi pTtoIndex;
	
	vector<double>* MuonE  = new vector<double>; // is not given in the tree
	vector<int>*    MuonID = new vector<int>; // is not given in the tree

	UInt_t          MuonN;
	vector<double>  *MuonAuthor;
	vector<double>  *MuonCombTrkNt;
	vector<double>  *MuonInDetTrkNt;
	vector<double>  *MuonExtrNt;
	vector<double>  *MuonEta;
	vector<double>  *MuonPhi;
	vector<double>  *MuonPt;
	vector<double>  *MuonZ0;
	vector<double>  *MuonD0;
	vector<double>  *MuonCharge;
	vector<double>  *MuonKf;
	vector<double>  *MuonPx;
	vector<double>  *MuonPy;
	vector<double>  *MuonPz;
	vector<double>  *MuonEtCone10;
	vector<double>  *MuonEtCone20;
	vector<double>  *MuonEtCone30;
	vector<double>  *MuonEtCone40;
	vector<double>  *MuonNuCone10;
	vector<double>  *MuonNuCone20;
	vector<double>  *MuonNuCone30;
	vector<double>  *MuonNuCone40;
	vector<double>  *MuonFitChi2;
	vector<long>    *MuonFitNumberDoF;
	vector<double>  *MuonEnergyLossDeposit;
	vector<double>  *MuonEnergyLossSigma;
	vector<double>  *MuonMatchChi2;
	vector<long>    *MuonMatchNumberDoF;
	vector<long>    *MuonBestMatch;
	vector<long>    *MuonIsCombinedMuon;
	
	TBranch        *b_MuonN;   //!
	TBranch        *b_MuonAuthor;   //!
	TBranch        *b_MuonCombTrkNt;   //!
	TBranch        *b_MuonInDetTrkNt;   //!
	TBranch        *b_MuonExtrNt;   //!
	TBranch        *b_MuonEta;   //!
	TBranch        *b_MuonPhi;   //!
	TBranch        *b_MuonPt;   //!
	TBranch        *b_MuonZ0;   //!
	TBranch        *b_MuonD0;   //!
	TBranch        *b_MuonCharge;   //!
	TBranch        *b_MuonKf;   //!
	TBranch        *b_MuonPx;   //!
	TBranch        *b_MuonPy;   //!
	TBranch        *b_MuonPz;   //!
	TBranch        *b_MuonEtCone10;   //!
	TBranch        *b_MuonEtCone20;   //!
	TBranch        *b_MuonEtCone30;   //!
	TBranch        *b_MuonEtCone40;   //!
	TBranch        *b_MuonNuCone10;   //!
	TBranch        *b_MuonNuCone20;   //!
	TBranch        *b_MuonNuCone30;   //!
	TBranch        *b_MuonNuCone40;   //!
	TBranch        *b_MuonFitChi2;   //!
	TBranch        *b_MuonFitNumberDoF;   //!
	TBranch        *b_MuonEnergyLossDeposit;   //!
	TBranch        *b_MuonEnergyLossSigma;   //!
	TBranch        *b_MuonMatchChi2;   //!
	TBranch        *b_MuonMatchNumberDoF;   //!
	TBranch        *b_MuonBestMatch;   //!
	TBranch        *b_MuonIsCombinedMuon;   //!
	

	logMmin  = log10(imassmin);
	logMmax  = log10(imassmax);
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)nimassbins );
	xbins[0] = imassmin;
	for(Int_t i=1 ; i<=nimassbins ; i++) xbins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	
	string sModel = "";
	string sMass  = "2000";
	
	cout << "chose model KK/ZP/Z0...";
	cin >> sModel;
	
	TString fname = (sModel!="Z0") ? (TString)sModel+(TString)sMass : (TString)sModel;


	if(sModel=="Z0")
	{
		sSubDir = "Z0pythia6/";
		addSample(sDir+sSubDir+"MC11.000001.Pythia6_DYmumu_75M120/",    "MC11.000001.Pythia6_DYmumu_75M120.NTUP._000001.pool.root",    "Pythia6_DYmumu_75M120",    kBlack+0*5,  9999, 0.799352);
		addSample(sDir+sSubDir+"MC11.000002.Pythia6_DYmumu_120M250/",   "MC11.000002.Pythia6_DYmumu_120M250.NTUP._000002.pool.root",   "Pythia6_DYmumu_120M250",   kBlack+1*5,  9999, 0.00855332);
		addSample(sDir+sSubDir+"MC11.000003.Pythia6_DYmumu_250M400/",   "MC11.000003.Pythia6_DYmumu_250M400.NTUP._000003.pool.root",   "Pythia6_DYmumu_250M400",   kBlack+2*5,  9999, 0.000411489);
		addSample(sDir+sSubDir+"MC11.000004.Pythia6_DYmumu_400M600/",   "MC11.000004.Pythia6_DYmumu_400M600.NTUP._000004.pool.root",   "Pythia6_DYmumu_400M600",   kBlack+3*5,  9999, 6.63E-05);
		addSample(sDir+sSubDir+"MC11.000005.Pythia6_DYmumu_600M800/",   "MC11.000005.Pythia6_DYmumu_600M800.NTUP._000005.pool.root",   "Pythia6_DYmumu_600M800",   kBlack+4*5,  9999, 1.10E-05);
		addSample(sDir+sSubDir+"MC11.000006.Pythia6_DYmumu_800M1000/",  "MC11.000006.Pythia6_DYmumu_800M1000.NTUP._000006.pool.root",  "Pythia6_DYmumu_800M1000",  kBlack+5*5,  9999, 2.65E-06);
		addSample(sDir+sSubDir+"MC11.000007.Pythia6_DYmumu_1000M1250/", "MC11.000007.Pythia6_DYmumu_1000M1250.NTUP._000007.pool.root", "Pythia6_DYmumu_1000M1250", kBlack+6*5,  9999, 8.90E-07);
		addSample(sDir+sSubDir+"MC11.000008.Pythia6_DYmumu_1250M1500/", "MC11.000008.Pythia6_DYmumu_1250M1500.NTUP._000008.pool.root", "Pythia6_DYmumu_1250M1500", kBlack+7*5,  9999, 2.38E-07);
		addSample(sDir+sSubDir+"MC11.000009.Pythia6_DYmumu_1500M1750/", "MC11.000009.Pythia6_DYmumu_1500M1750.NTUP._000009.pool.root", "Pythia6_DYmumu_1500M1750", kBlack+8*5,  9999, 7.36E-08);
		addSample(sDir+sSubDir+"MC11.000010.Pythia6_DYmumu_1750M2000/", "MC11.000010.Pythia6_DYmumu_1750M2000.NTUP._000010.pool.root", "Pythia6_DYmumu_1750M2000", kBlack+9*5,  9999, 2.47E-08);
		addSample(sDir+sSubDir+"MC11.000011.Pythia6_DYmumu_2000M2250/", "MC11.000011.Pythia6_DYmumu_2000M2250.NTUP._000011.pool.root", "Pythia6_DYmumu_2000M2250", kBlack+10*5, 9999, 8.80E-09);
		addSample(sDir+sSubDir+"MC11.000012.Pythia6_DYmumu_2250M2500/", "MC11.000012.Pythia6_DYmumu_2250M2500.NTUP._000012.pool.root", "Pythia6_DYmumu_2250M2500", kBlack+11*5, 9999, 3.23E-09);
		addSample(sDir+sSubDir+"MC11.000013.Pythia6_DYmumu_2500M2750/", "MC11.000013.Pythia6_DYmumu_2500M2750.NTUP._000013.pool.root", "Pythia6_DYmumu_2500M2750", kBlack+12*5, 9999, 1.20E-09);
		addSample(sDir+sSubDir+"MC11.000014.Pythia6_DYmumu_2750M3000/", "MC11.000014.Pythia6_DYmumu_2750M3000.NTUP._000014.pool.root", "Pythia6_DYmumu_2750M3000", kBlack+13*5, 9999, 4.46E-10);
		addSample(sDir+sSubDir+"MC11.000015.Pythia6_DYmumu_M3000/",     "MC11.000015.Pythia6_DYmumu_M3000.NTUP._000015.pool.root",     "Pythia6_DYmumu_M3000",     kBlack+14*5, 9999, 2.55E-10);
		
		// addSample(sDir+sSubDir+"MC11.000001.Pythia6_DYmumu_75M120/",    "MC11.000001.Pythia6_DYmumu_75M120.NTUP._00001.pool.root",    "Pythia6_DYmumu_75M120",     kBlack+0*5,  9999, 0.799352);
		// addSample(sDir+sSubDir+"MC11.000002.Pythia6_DYmumu_120M250/",   "MC11.000001.Pythia6_DYmumu_120M250.NTUP._00001.pool.root",   "Pythia6_DYmumu_120M250",   kBlack+1*5,  9999, 0.00855332);
		// addSample(sDir+sSubDir+"MC11.000003.Pythia6_DYmumu_250M400/",   "MC11.000001.Pythia6_DYmumu_250M400.NTUP._00001.pool.root",   "Pythia6_DYmumu_250M400",   kBlack+2*5,  9999, 0.000411489);
		// addSample(sDir+sSubDir+"MC11.000004.Pythia6_DYmumu_400M600/",   "MC11.000001.Pythia6_DYmumu_400M600.NTUP._00001.pool.root",   "Pythia6_DYmumu_400M600",   kBlack+3*5,  9999, 6.63E-05);
		// addSample(sDir+sSubDir+"MC11.000005.Pythia6_DYmumu_600M800/",   "MC11.000001.Pythia6_DYmumu_600M800.NTUP._00001.pool.root",   "Pythia6_DYmumu_600M800",   kBlack+4*5,  9999, 1.10E-05);
		// addSample(sDir+sSubDir+"MC11.000006.Pythia6_DYmumu_800M1000/",  "MC11.000001.Pythia6_DYmumu_800M1000.NTUP._00001.pool.root",  "Pythia6_DYmumu_800M1000",  kBlack+5*5,  9999, 2.65E-06);
		// addSample(sDir+sSubDir+"MC11.000007.Pythia6_DYmumu_1000M1250/", "MC11.000001.Pythia6_DYmumu_1000M1250.NTUP._00001.pool.root", "Pythia6_DYmumu_1000M1250", kBlack+6*5,  9999, 8.90E-07);
		// addSample(sDir+sSubDir+"MC11.000008.Pythia6_DYmumu_1250M1500/", "MC11.000001.Pythia6_DYmumu_1250M1500.NTUP._00001.pool.root", "Pythia6_DYmumu_1250M1500", kBlack+7*5,  9999, 2.38E-07);
		// addSample(sDir+sSubDir+"MC11.000009.Pythia6_DYmumu_1500M1750/", "MC11.000001.Pythia6_DYmumu_1500M1750.NTUP._00001.pool.root", "Pythia6_DYmumu_1500M1750", kBlack+8*5,  9999, 7.36E-08);
		// addSample(sDir+sSubDir+"MC11.000010.Pythia6_DYmumu_1750M2000/", "MC11.000001.Pythia6_DYmumu_1750M2000.NTUP._00001.pool.root", "Pythia6_DYmumu_1750M2000", kBlack+9*5,  9999, 2.47E-08);
		// addSample(sDir+sSubDir+"MC11.000011.Pythia6_DYmumu_2000M2250/", "MC11.000001.Pythia6_DYmumu_2000M2250.NTUP._00001.pool.root", "Pythia6_DYmumu_2000M2250", kBlack+10*5, 9999, 8.80E-09);
		// addSample(sDir+sSubDir+"MC11.000012.Pythia6_DYmumu_2250M2500/", "MC11.000001.Pythia6_DYmumu_2250M2500.NTUP._00001.pool.root", "Pythia6_DYmumu_2250M2500", kBlack+11*5, 9999, 3.23E-09);
		// addSample(sDir+sSubDir+"MC11.000013.Pythia6_DYmumu_2500M2750/", "MC11.000001.Pythia6_DYmumu_2500M2750.NTUP._00001.pool.root", "Pythia6_DYmumu_2500M2750", kBlack+12*5, 9999, 1.20E-09);
		// addSample(sDir+sSubDir+"MC11.000014.Pythia6_DYmumu_2750M3000/", "MC11.000001.Pythia6_DYmumu_2750M3000.NTUP._00001.pool.root", "Pythia6_DYmumu_2750M3000", kBlack+13*5, 9999, 4.46E-10);
		// addSample(sDir+sSubDir+"MC11.000015.Pythia6_DYmumu_M3000/",     "MC11.000001.Pythia6_DYmumu_M3000.NTUP._00001.pool.root",     "Pythia6_DYmumu_M3000",     kBlack+14*5, 9999, 2.55E-10);
	}
	if(sModel=="ZP" && sMass=="2000")
	{
		sSubDir = "ZPpythia8/";
		addSample(sDir+sSubDir+"MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450/",   "MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450.NTUP._000001.pool.root",   "Pythia8_ZprimeSSM_m2000_mumu_120M450",   kBlack+0*5,  9999, 8.00E-03);
		addSample(sDir+sSubDir+"MC11.000002.Pythia8_ZprimeSSM_m2000_mumu_450M850/",   "MC11.000002.Pythia8_ZprimeSSM_m2000_mumu_450M850.NTUP._000002.pool.root",   "Pythia8_ZprimeSSM_m2000_mumu_450M850",   kBlack+1*5,  9999, 3.81E-05);
		addSample(sDir+sSubDir+"MC11.000003.Pythia8_ZprimeSSM_m2000_mumu_850M1300/",  "MC11.000003.Pythia8_ZprimeSSM_m2000_mumu_850M1300.NTUP._000003.pool.root",  "Pythia8_ZprimeSSM_m2000_mumu_850M1300",  kBlack+2*5,  9999, 1.74E-06);
		addSample(sDir+sSubDir+"MC11.000004.Pythia8_ZprimeSSM_m2000_mumu_1300M1800/", "MC11.000004.Pythia8_ZprimeSSM_m2000_mumu_1300M1800.NTUP._000004.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_1300M1800", kBlack+3*5,  9999, 1.50E-07);
		addSample(sDir+sSubDir+"MC11.000005.Pythia8_ZprimeSSM_m2000_mumu_1800M2300/", "MC11.000005.Pythia8_ZprimeSSM_m2000_mumu_1800M2300.NTUP._000005.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_1800M2300", kBlack+4*5,  9999, 1.01E-06);
		addSample(sDir+sSubDir+"MC11.000006.Pythia8_ZprimeSSM_m2000_mumu_2300M2800/", "MC11.000006.Pythia8_ZprimeSSM_m2000_mumu_2300M2800.NTUP._000006.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_2300M2800", kBlack+5*5,  9999, 1.15E-08);
		addSample(sDir+sSubDir+"MC11.000007.Pythia8_ZprimeSSM_m2000_mumu_2800M3300/", "MC11.000007.Pythia8_ZprimeSSM_m2000_mumu_2800M3300.NTUP._000007.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_2800M3300", kBlack+6*5,  9999, 7.02E-10);
		addSample(sDir+sSubDir+"MC11.000008.Pythia8_ZprimeSSM_m2000_mumu_M3300/",     "MC11.000008.Pythia8_ZprimeSSM_m2000_mumu_M3300.NTUP._000008.pool.root",     "Pythia8_ZprimeSSM_m2000_mumu_M3300",     kBlack+7*5,  9999, 6.72E-11);
		
		// sSubDir = "ZP/";
		// addSample(sDir+sSubDir+"MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450/",   "MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450.NTUP._00001.pool.root",   "Pythia8_ZprimeSSM_m2000_mumu_120M450",   kBlack+0*5,  9999, 8.00E-03);
		// addSample(sDir+sSubDir+"MC11.000002.Pythia8_ZprimeSSM_m2000_mumu_450M850/",   "MC11.000002.Pythia8_ZprimeSSM_m2000_mumu_450M850.NTUP._00001.pool.root",   "Pythia8_ZprimeSSM_m2000_mumu_450M850",   kBlack+1*5,  9999, 3.81E-05);
		// addSample(sDir+sSubDir+"MC11.000003.Pythia8_ZprimeSSM_m2000_mumu_850M1300/",  "MC11.000003.Pythia8_ZprimeSSM_m2000_mumu_850M1300.NTUP._00001.pool.root",  "Pythia8_ZprimeSSM_m2000_mumu_850M1300",  kBlack+2*5,  9999, 1.74E-06);
		// addSample(sDir+sSubDir+"MC11.000004.Pythia8_ZprimeSSM_m2000_mumu_1300M1800/", "MC11.000004.Pythia8_ZprimeSSM_m2000_mumu_1300M1800.NTUP._00001.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_1300M1800", kBlack+3*5,  9999, 1.50E-07);
		// addSample(sDir+sSubDir+"MC11.000005.Pythia8_ZprimeSSM_m2000_mumu_1800M2300/", "MC11.000005.Pythia8_ZprimeSSM_m2000_mumu_1800M2300.NTUP._00001.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_1800M2300", kBlack+4*5,  9999, 1.01E-06);
		// addSample(sDir+sSubDir+"MC11.000006.Pythia8_ZprimeSSM_m2000_mumu_2300M2800/", "MC11.000006.Pythia8_ZprimeSSM_m2000_mumu_2300M2800.NTUP._00001.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_2300M2800", kBlack+5*5,  9999, 1.15E-08);
		// addSample(sDir+sSubDir+"MC11.000007.Pythia8_ZprimeSSM_m2000_mumu_2800M3300/", "MC11.000007.Pythia8_ZprimeSSM_m2000_mumu_2800M3300.NTUP._00001.pool.root", "Pythia8_ZprimeSSM_m2000_mumu_2800M3300", kBlack+6*5,  9999, 7.02E-10);
		// addSample(sDir+sSubDir+"MC11.000008.Pythia8_ZprimeSSM_m2000_mumu_M3300/",     "MC11.000008.Pythia8_ZprimeSSM_m2000_mumu_M3300.NTUP._00001.pool.root",     "Pythia8_ZprimeSSM_m2000_mumu_M3300",     kBlack+7*5,  9999, 6.72E-11);
	}
	if(sModel=="KK" && sMass=="2000")
	{
		sSubDir = "KKpythia8/";
		addSample(sDir+sSubDir+"MC11.000001.Pythia8_ExtraDimensionsTEV_m2000_mumu_120M450/",   "MC11.000001.Pythia8_ExtraDimensionsTEV_m2000_mumu_120M450.NTUP._000001.pool.root",   "Pythia8_ExtraDimensionsTEV_m2000_mumu_120M450",   kBlack+0*5,  9999, 7.68E-03);
		addSample(sDir+sSubDir+"MC11.000002.Pythia8_ExtraDimensionsTEV_m2000_mumu_450M850/",   "MC11.000002.Pythia8_ExtraDimensionsTEV_m2000_mumu_450M850.NTUP._000002.pool.root",   "Pythia8_ExtraDimensionsTEV_m2000_mumu_450M850",   kBlack+1*5,  9999, 2.21E-05);
		addSample(sDir+sSubDir+"MC11.000003.Pythia8_ExtraDimensionsTEV_m2000_mumu_850M1300/",  "MC11.000003.Pythia8_ExtraDimensionsTEV_m2000_mumu_850M1300.NTUP._000003.pool.root",  "Pythia8_ExtraDimensionsTEV_m2000_mumu_850M1300",  kBlack+2*5,  9999, 1.99E-07);
		addSample(sDir+sSubDir+"MC11.000004.Pythia8_ExtraDimensionsTEV_m2000_mumu_1300M1800/", "MC11.000004.Pythia8_ExtraDimensionsTEV_m2000_mumu_1300M1800.NTUP._000004.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_1300M1800", kBlack+3*5,  9999, 1.36E-06);
		addSample(sDir+sSubDir+"MC11.000005.Pythia8_ExtraDimensionsTEV_m2000_mumu_1800M2300/", "MC11.000005.Pythia8_ExtraDimensionsTEV_m2000_mumu_1800M2300.NTUP._000005.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_1800M2300", kBlack+4*5,  9999, 9.39E-06);
		addSample(sDir+sSubDir+"MC11.000006.Pythia8_ExtraDimensionsTEV_m2000_mumu_2300M2800/", "MC11.000006.Pythia8_ExtraDimensionsTEV_m2000_mumu_2300M2800.NTUP._000006.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_2300M2800", kBlack+5*5,  9999, 4.75E-08);
		addSample(sDir+sSubDir+"MC11.000007.Pythia8_ExtraDimensionsTEV_m2000_mumu_2800M3300/", "MC11.000007.Pythia8_ExtraDimensionsTEV_m2000_mumu_2800M3300.NTUP._000007.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_2800M3300", kBlack+6*5,  9999, 2.98E-10);
		addSample(sDir+sSubDir+"MC11.000008.Pythia8_ExtraDimensionsTEV_m2000_mumu_M3300/",     "MC11.000008.Pythia8_ExtraDimensionsTEV_m2000_mumu_M3300.NTUP._000008.pool.root",     "Pythia8_ExtraDimensionsTEV_m2000_mumu_M3300",     kBlack+7*5,  9999, 3.20E-09);

		// sSubDir = "KK/";
		// addSample(sDir+sSubDir+"MC11.000001.Pythia8_ExtraDimensionsTEV_m2000_mumu_120M450/",   "MC11.000001.Pythia8_ExtraDimensionsTEV_m2000_mumu_120M450.NTUP._00001.pool.root",   "Pythia8_ExtraDimensionsTEV_m2000_mumu_120M450",   kBlack+0*5,  9999, 7.68E-03);
		// addSample(sDir+sSubDir+"MC11.000002.Pythia8_ExtraDimensionsTEV_m2000_mumu_450M850/",   "MC11.000002.Pythia8_ExtraDimensionsTEV_m2000_mumu_450M850.NTUP._00001.pool.root",   "Pythia8_ExtraDimensionsTEV_m2000_mumu_450M850",   kBlack+1*5,  9999, 2.21E-05);
		// addSample(sDir+sSubDir+"MC11.000003.Pythia8_ExtraDimensionsTEV_m2000_mumu_850M1300/",  "MC11.000003.Pythia8_ExtraDimensionsTEV_m2000_mumu_850M1300.NTUP._00001.pool.root",  "Pythia8_ExtraDimensionsTEV_m2000_mumu_850M1300",  kBlack+2*5,  9999, 1.99E-07);
		// addSample(sDir+sSubDir+"MC11.000004.Pythia8_ExtraDimensionsTEV_m2000_mumu_1300M1800/", "MC11.000004.Pythia8_ExtraDimensionsTEV_m2000_mumu_1300M1800.NTUP._00001.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_1300M1800", kBlack+3*5,  9999, 1.36E-06);
		// addSample(sDir+sSubDir+"MC11.000005.Pythia8_ExtraDimensionsTEV_m2000_mumu_1800M2300/", "MC11.000005.Pythia8_ExtraDimensionsTEV_m2000_mumu_1800M2300.NTUP._00001.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_1800M2300", kBlack+4*5,  9999, 9.39E-06);
		// addSample(sDir+sSubDir+"MC11.000006.Pythia8_ExtraDimensionsTEV_m2000_mumu_2300M2800/", "MC11.000006.Pythia8_ExtraDimensionsTEV_m2000_mumu_2300M2800.NTUP._00001.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_2300M2800", kBlack+5*5,  9999, 4.75E-08);
		// addSample(sDir+sSubDir+"MC11.000007.Pythia8_ExtraDimensionsTEV_m2000_mumu_2800M3300/", "MC11.000007.Pythia8_ExtraDimensionsTEV_m2000_mumu_2800M3300.NTUP._00001.pool.root", "Pythia8_ExtraDimensionsTEV_m2000_mumu_2800M3300", kBlack+6*5,  9999, 2.98E-10);
		// addSample(sDir+sSubDir+"MC11.000008.Pythia8_ExtraDimensionsTEV_m2000_mumu_M3300/",     "MC11.000008.Pythia8_ExtraDimensionsTEV_m2000_mumu_M3300.NTUP._00001.pool.root",     "Pythia8_ExtraDimensionsTEV_m2000_mumu_M3300",     kBlack+7*5,  9999, 3.20E-09);
	}
	
	
	string text = "";
	if(sModel=="Z0")
	{
		text = "SM #gamma/Z^{0}";
	}
	if(sModel=="ZP")
	{
		text = "2 TeV Z'_{SSM}";
	}
	if(sModel=="KK")
	{
		text = "2 TeV S^{1}/Z_{2} KK";
	}
	
	
	
	TCanvas* cnv_binned = new TCanvas("cnv_binned", "cnv_binned", 0,0,1200,800);
	cnv_binned->SetLogy();
	if(doLogx) cnv_binned->SetLogx();
	cnv_binned->cd();
	cnv_binned->Draw();
	
	TCanvas* cnv_merged = new TCanvas("cnv_merged", "cnv_merged", 0,0,1200,800);
	cnv_merged->SetLogy();
	if(doLogx) cnv_merged->SetLogx();
	cnv_merged->cd();
	cnv_merged->Draw();
	
	TCanvas* cnv_kin_merged = new TCanvas("cnv_kin_merged", "cnv_kin_merged", 0,0,1200,800);
	//cnv_kin_merged->SetLogy();
	cnv_kin_merged->Divide(3,2);
	TVirtualPad* pad_pT_leading    = cnv_kin_merged->cd(1);
	TVirtualPad* pad_pT_subleading = cnv_kin_merged->cd(4);
	pad_pT_leading->SetLogy();
	pad_pT_subleading->SetLogy();
	cnv_kin_merged->cd();
	cnv_kin_merged->Draw();
	
	TCanvas* cnv_stack = new TCanvas("cnv_stack", "cnv_stack", 0,0,1200,800);
	cnv_stack->SetLogy();
	if(doLogx) cnv_stack->SetLogx();
	cnv_stack->cd();
	cnv_stack->Draw();
	
	string sMergedNmae = "hMass";
	
	TH1D* hMassMerged;
	if(doLogx) hMassMerged = new TH1D(sMergedNmae.c_str(),sMergedNmae.c_str(),nimassbins,xbins);
	else       hMassMerged = new TH1D(sMergedNmae.c_str(),sMergedNmae.c_str(),nimassbins,imassmin,imassmax);
	
	vector<TH1D*> hpTMerged;
	sMergedNmae = "hpTMerged";
	hpTMerged.push_back( new TH1D((sMergedNmae+"_leadingMuon").c_str(),(sMergedNmae+"_leadingMuon").c_str(),100,0.,3000.) );
	hpTMerged.push_back( new TH1D((sMergedNmae+"_subLeadingMuon").c_str(),(sMergedNmae+"_subLeadingMuon").c_str(),100,0.,3000.) );
	
	vector<TH1D*> hEtaMerged;
	sMergedNmae = "hEtaMerged";
	hEtaMerged.push_back( new TH1D((sMergedNmae+"_leadingMuon").c_str(),(sMergedNmae+"_leadingMuon").c_str(),50,-3,+3) );
	hEtaMerged.push_back( new TH1D((sMergedNmae+"_subLeadingMuon").c_str(),(sMergedNmae+"_subLeadingMuon").c_str(),50,-3,+3) );
	
	vector<TH1D*> hPhiMerged;
	sMergedNmae = "hPhiMerged";
	hPhiMerged.push_back( new TH1D((sMergedNmae+"_leadingMuon").c_str(),(sMergedNmae+"_leadingMuon").c_str(),50,-1*TMath::Pi(),TMath::Pi()) );
	hPhiMerged.push_back( new TH1D((sMergedNmae+"_subLeadingMuon").c_str(),(sMergedNmae+"_subLeadingMuon").c_str(),50,-1*TMath::Pi(),TMath::Pi()) );
	
	
	TLegend* leg;
	if(sModel=="Z0") leg = new TLegend(0.6797659,0.5168394,0.8770903,0.9455959,NULL,"brNDC");
	else 			 leg = new TLegend(0.5585284,0.7318653,0.8762542,0.9430052,NULL,"brNDC");
	leg->SetFillColor(kWhite);
	
	TPaveText* pvtxt;
	if(sModel=="Z0") pvtxt = new TPaveText(0.2282609,0.8432642,0.4414716,0.9378238,"brNDC");
	else             pvtxt = new TPaveText(0.1822742,0.6593264,0.3954849,0.753886,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( text.c_str() );
	string L = tostring(luminosity);
	txt = pvtxt->AddText( ("normalized to "+L+"/fb").c_str() );
	
	
	THStack* hS = new THStack("hS","");
	
	TFile* file;
	TTree* tree;
	
	int vsize = (int)svPaths.size();
	
	double minimum = 10000.;
	
	for(int n=vsize-1 ; n>=0 ; n--)
	{
		LOG(DBG,VISUAL,"svPaths["+tostring(n)+"]="+svPaths[n]);
		
		file = TFile::Open(svPaths[n].c_str(),"READ");
		tree = (TTree*)file->Get("FastTree");
		
		MuonAuthor = 0;
		MuonCombTrkNt = 0;
		MuonInDetTrkNt = 0;
		MuonExtrNt = 0;
		MuonEta = 0;
		MuonPhi = 0;
		MuonPt = 0;
		MuonZ0 = 0;
		MuonD0 = 0;
		MuonCharge = 0;
		MuonKf = 0;
		MuonPx = 0;
		MuonPy = 0;
		MuonPz = 0;
		MuonEtCone10 = 0;
		MuonEtCone20 = 0;
		MuonEtCone30 = 0;
		MuonEtCone40 = 0;
		MuonNuCone10 = 0;
		MuonNuCone20 = 0;
		MuonNuCone30 = 0;
		MuonNuCone40 = 0;
		MuonFitChi2 = 0;
		MuonFitNumberDoF = 0;
		MuonEnergyLossDeposit = 0;
		MuonEnergyLossSigma = 0;
		MuonMatchChi2 = 0;
		MuonMatchNumberDoF = 0;
		MuonBestMatch = 0;
		MuonIsCombinedMuon = 0;
		
		tree->SetBranchAddress("MuonN", &MuonN, &b_MuonN);
		tree->SetBranchAddress("MuonAuthor", &MuonAuthor, &b_MuonAuthor);
		tree->SetBranchAddress("MuonCombTrkNt", &MuonCombTrkNt, &b_MuonCombTrkNt);
		tree->SetBranchAddress("MuonInDetTrkNt", &MuonInDetTrkNt, &b_MuonInDetTrkNt);
		tree->SetBranchAddress("MuonExtrNt", &MuonExtrNt, &b_MuonExtrNt);
		tree->SetBranchAddress("MuonEta", &MuonEta, &b_MuonEta);
		tree->SetBranchAddress("MuonPhi", &MuonPhi, &b_MuonPhi);
		tree->SetBranchAddress("MuonPt", &MuonPt, &b_MuonPt);
		tree->SetBranchAddress("MuonZ0", &MuonZ0, &b_MuonZ0);
		tree->SetBranchAddress("MuonD0", &MuonD0, &b_MuonD0);
		tree->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
		tree->SetBranchAddress("MuonKf", &MuonKf, &b_MuonKf);
		tree->SetBranchAddress("MuonPx", &MuonPx, &b_MuonPx);
		tree->SetBranchAddress("MuonPy", &MuonPy, &b_MuonPy);
		tree->SetBranchAddress("MuonPz", &MuonPz, &b_MuonPz);
		tree->SetBranchAddress("MuonEtCone10", &MuonEtCone10, &b_MuonEtCone10);
		tree->SetBranchAddress("MuonEtCone20", &MuonEtCone20, &b_MuonEtCone20);
		tree->SetBranchAddress("MuonEtCone30", &MuonEtCone30, &b_MuonEtCone30);
		tree->SetBranchAddress("MuonEtCone40", &MuonEtCone40, &b_MuonEtCone40);
		tree->SetBranchAddress("MuonNuCone10", &MuonNuCone10, &b_MuonNuCone10);
		tree->SetBranchAddress("MuonNuCone20", &MuonNuCone20, &b_MuonNuCone20);
		tree->SetBranchAddress("MuonNuCone30", &MuonNuCone30, &b_MuonNuCone30);
		tree->SetBranchAddress("MuonNuCone40", &MuonNuCone40, &b_MuonNuCone40);
		tree->SetBranchAddress("MuonFitChi2", &MuonFitChi2, &b_MuonFitChi2);
		tree->SetBranchAddress("MuonFitNumberDoF", &MuonFitNumberDoF, &b_MuonFitNumberDoF);
		tree->SetBranchAddress("MuonEnergyLossDeposit", &MuonEnergyLossDeposit, &b_MuonEnergyLossDeposit);
		tree->SetBranchAddress("MuonEnergyLossSigma", &MuonEnergyLossSigma, &b_MuonEnergyLossSigma);
		tree->SetBranchAddress("MuonMatchChi2", &MuonMatchChi2, &b_MuonMatchChi2);
		tree->SetBranchAddress("MuonMatchNumberDoF", &MuonMatchNumberDoF, &b_MuonMatchNumberDoF);
		tree->SetBranchAddress("MuonBestMatch", &MuonBestMatch, &b_MuonBestMatch);
		tree->SetBranchAddress("MuonIsCombinedMuon", &MuonIsCombinedMuon, &b_MuonIsCombinedMuon);
		
		for(Int_t i=0 ; i<tree->GetEntries() ; i++)
		{
			tree->GetEntry(i);
			
			int index_a = 0;
			int index_b = 0;
			int nPassed = 0;
			if(pTtoIndex.size()!=0)                 pTtoIndex.clear();
			if(MuonE!=NULL   &&  MuonE->size()!=0)  MuonE->clear();
			if(MuonID!=NULL  &&  MuonID->size()!=0) MuonID->clear();
			
			for(UInt_t mu=0 ; mu<MuonN ; mu++)
			{
				double E = sqrt(
									MuonPx->at(mu)*MuonPx->at(mu) +
									MuonPy->at(mu)*MuonPy->at(mu) +
									MuonPz->at(mu)*MuonPz->at(mu) +
									mumass*GeV2MeV*mumass*GeV2MeV
								);
				MuonE->push_back(E);
				MuonID->push_back( (MuonCharge->at(mu)<0)?13:-13 );
			
				////////////////////////////////////////////////////////////////////////
				// Single muon selection ///////////////////////////////////////////////
				LOG(DBG,VISUAL,"before cuts");
				if(MuonPt->at(mu)*MeV2GeV<25)                        continue; /////////
				LOG(DBG,VISUAL,"after pT cut");
				if(fabs(MuonEta->at(mu))>2.4)                        continue; /////////
				LOG(DBG,VISUAL,"after eta cut");
				//if(fabs(MuonZ0->at(mu))>0.2)                       continue; /////////
				//if(fabs(MuonD0->at(mu))>1.)                        continue; /////////
				//if(fabs(MuonEtCone30->at(mu)/MuonPt->at(mu))>0.05) continue; /////////
				////////////////////////////////////////////////////////////////////////
				pTtoIndex.insert( make_pair(MuonPt->at(mu),mu) );
				nPassed++;
			}
			
			LOG(DBG,VISUAL,"npassed="+tostring(nPassed));
			
			if(nPassed<2)                                          continue; // at least 2 muons
			pTSort(pTtoIndex,index_a,index_b);
			LOG(DBG,VISUAL,"after nmu=2 cut");
			if(MuonCharge->at(index_a)*MuonCharge->at(index_b)>=0) continue; // opposite charge
			LOG(DBG,VISUAL,"after opposite charge cut");
			
			pa->SetPxPyPzE(MuonPx->at(index_a)*MeV2GeV,MuonPy->at(index_a)*MeV2GeV,MuonPz->at(index_a)*MeV2GeV,MuonE->at(index_a)*MeV2GeV);
			pb->SetPxPyPzE(MuonPx->at(index_b)*MeV2GeV,MuonPy->at(index_b)*MeV2GeV,MuonPz->at(index_b)*MeV2GeV,MuonE->at(index_b)*MeV2GeV);
			
			if(imass(pa,pb)<75.)                                   continue; // invariant mass
			
			LOG(DBG,VISUAL,"after imass cut");
			
			mHat       = imass(pa,pb);
			LOG(DBG,VISUAL,"mass="+tostring(mHat)+" GeV");
			qT         = QT(pa,pb);
			ysystem    = ySystem(pa,pb);
			cosThetaCS = cosThetaCollinsSoper( pa, MuonCharge->at(index_a), pb, MuonCharge->at(index_a) );
			cosThetaHE = cosThetaBoost( pa, MuonCharge->at(index_b), pb, MuonCharge->at(index_b) );
			
			hvHistos[n]->Fill(mHat);
			hMassMerged->Fill(mHat,dvWeights[n]);
			for(int mu=0 ; mu<2 ; mu++)
			{
				hpTMerged[mu]->Fill( (mu==0) ? pa->Pt()  : pb->Pt(),  dvWeights[n]);
				hEtaMerged[mu]->Fill((mu==0) ? pa->Eta() : pb->Eta(), dvWeights[n]);
				hPhiMerged[mu]->Fill((mu==0) ? pa->Phi() : pb->Phi(), dvWeights[n]);
			}
		}
		
		cnv_binned->cd();
		leg->AddEntry(hvHistos[n], svNames[n].c_str(), "l");
		hvHistos[n]->SetLineColor(cvColors[n]);
		hvHistos[n]->SetLineWidth(2);
		hvHistos[n]->Scale(dvWeights[n]);
		hvHistos[n]->SetTitle("");
		if(doLogx) hvHistos[n]->GetXaxis()->SetMoreLogLabels(); 
		
		if(n==vsize-1)
		{
			double ymin = 0.5*getYmin(hvHistos[n]);
			hvHistos[n]->SetMinimum(ymin);
			hvHistos[n]->SetXTitle("m_{#mu#mu} GeV");
			hvHistos[n]->SetYTitle("Events");
			hvHistos[n]->Draw();
		}
		else hvHistos[n]->Draw("SAMES");
		
		double tmp = getYmin(hvHistos[n]);
		minimum = (tmp<minimum) ? tmp : minimum;
		
		file->Close();
	}
	
	cout << "Minimum = " << minimum << endl;
	
	
	cnv_binned->cd();
	hvHistos[vsize-1]->SetMaximum(1.5*hvHistos[0]->GetMaximum());
	leg->Draw("SAMES");
	pvtxt->Draw("SAMES");
	cnv_binned->RedrawAxis();
	cnv_binned->Update();
	TString name = "plots/plot_binned_" + fname;
	cnv_binned->SaveAs(name+".eps");
	cnv_binned->SaveAs(name+".C");
	cnv_binned->SaveAs(name+".root");
	cnv_binned->SaveAs(name+".png");
	
	cnv_merged->cd();
	hMassMerged->SetLineColor(kBlack);
	hMassMerged->SetLineWidth(2);
	hMassMerged->SetTitle("");
	if(doLogx) hMassMerged->GetXaxis()->SetMoreLogLabels(); 
	double ymin = 0.5*getYmin(hMassMerged);
	hMassMerged->SetMinimum(ymin);
	hMassMerged->SetXTitle("m_{#mu#mu} GeV");
	hMassMerged->SetYTitle("Events");
	hMassMerged->Draw();
	pvtxt->Draw("SAMES");
	cnv_merged->RedrawAxis();
	cnv_merged->Update();
	name = "plots/plot_merged_" + fname;
	cnv_merged->SaveAs(name+".eps");
	cnv_merged->SaveAs(name+".C");
	cnv_merged->SaveAs(name+".root");
	cnv_merged->SaveAs(name+".png");
	
	cnv_kin_merged->cd();
	pad_pT_leading->cd();
	hpTMerged[0]->SetLineColor(kBlack);
	hpTMerged[0]->SetLineWidth(2);
	hpTMerged[0]->SetTitle("");
	if(doLogx) hpTMerged[0]->GetXaxis()->SetMoreLogLabels(); 
	ymin = 0.5*getYmin(hpTMerged[0]);
	hpTMerged[0]->SetMinimum(ymin);
	hpTMerged[0]->SetXTitle("p_{T} leading #mu GeV");
	hpTMerged[0]->SetYTitle("Events");
	hpTMerged[0]->Draw();
	pad_pT_subleading->cd();
	hpTMerged[1]->SetLineColor(kBlack);
	hpTMerged[1]->SetLineWidth(2);
	hpTMerged[1]->SetTitle("");
	if(doLogx) hpTMerged[1]->GetXaxis()->SetMoreLogLabels(); 
	ymin = 0.5*getYmin(hpTMerged[1]);
	hpTMerged[1]->SetMinimum(ymin);
	hpTMerged[1]->SetXTitle("p_{T} subleading #mu GeV");
	hpTMerged[1]->SetYTitle("Events");
	hpTMerged[1]->Draw();
	
	cnv_kin_merged->cd(2);
	hEtaMerged[0]->SetLineColor(kBlack);
	hEtaMerged[0]->SetLineWidth(2);
	hEtaMerged[0]->SetTitle("");
	if(doLogx) hEtaMerged[0]->GetXaxis()->SetMoreLogLabels(); 
	ymin = 0.5*getYmin(hEtaMerged[0]);
	hEtaMerged[0]->SetMinimum(ymin);
	hEtaMerged[0]->SetXTitle("#eta leading #mu");
	hEtaMerged[0]->SetYTitle("Events");
	hEtaMerged[0]->Draw();
	cnv_kin_merged->cd(5);
	hEtaMerged[1]->SetLineColor(kBlack);
	hEtaMerged[1]->SetLineWidth(2);
	hEtaMerged[1]->SetTitle("");
	if(doLogx) hEtaMerged[1]->GetXaxis()->SetMoreLogLabels(); 
	ymin = 0.5*getYmin(hEtaMerged[1]);
	hEtaMerged[1]->SetMinimum(ymin);
	hEtaMerged[1]->SetXTitle("#eta subleading #mu");
	hEtaMerged[1]->SetYTitle("Events");
	hEtaMerged[1]->Draw();
	
	cnv_kin_merged->cd(3);
	hPhiMerged[0]->SetLineColor(kBlack);
	hPhiMerged[0]->SetLineWidth(2);
	hPhiMerged[0]->SetTitle("");
	if(doLogx) hPhiMerged[0]->GetXaxis()->SetMoreLogLabels(); 
	ymin = 0.5*getYmin(hPhiMerged[0]);
	hPhiMerged[0]->SetMinimum(ymin);
	hPhiMerged[0]->SetXTitle("#phi leading #mu");
	hPhiMerged[0]->SetYTitle("Events");
	hPhiMerged[0]->Draw();
	cnv_kin_merged->cd(6);
	hPhiMerged[1]->SetLineColor(kBlack);
	hPhiMerged[1]->SetLineWidth(2);
	hPhiMerged[1]->SetTitle("");
	if(doLogx) hPhiMerged[1]->GetXaxis()->SetMoreLogLabels(); 
	ymin = 0.5*getYmin(hPhiMerged[1]);
	hPhiMerged[1]->SetMinimum(ymin);
	hPhiMerged[1]->SetXTitle("#phi subleading #mu");
	hPhiMerged[1]->SetYTitle("Events");
	hPhiMerged[1]->Draw();
	
	//pvtxt->Draw("SAMES");
	//cnv_kin_merged->RedrawAxis();
	cnv_kin_merged->Update();
	name = "plots/plot_merged_kin_" + fname;
	cnv_kin_merged->SaveAs(name+".eps");
	cnv_kin_merged->SaveAs(name+".C");
	cnv_kin_merged->SaveAs(name+".root");
	cnv_kin_merged->SaveAs(name+".png");
	
	for(int n=0 ; n<vsize ; n++) hS->Add(hvHistos[n]);
	hS->SetMinimum(minimum);
	cnv_stack->cd();
	hS->Draw(/*"nostack"*/);
	cnv_stack->RedrawAxis();
	cnv_stack->Update();
	name = "plots/plot_stack_" + fname;
	cnv_stack->SaveAs(name+".eps");
	cnv_stack->SaveAs(name+".C");
	cnv_stack->SaveAs(name+".root");
	cnv_stack->SaveAs(name+".png");
	
	return 0;
}

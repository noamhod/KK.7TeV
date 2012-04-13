#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
#include "../include/units.h"
#include "../include/couplings.h"
#include "../include/width.h"
#include "../include/helicity.h"
#include "../include/kFactors.h"

using namespace couplings;
using namespace width;
using namespace helicity;
using namespace kFactors;

#define BosonPtReweightingTool_cxx
#include "BosonPtReweightingTool.C"
BosonPtReweightingTool* ZpTrw = new BosonPtReweightingTool("PythiaMC11",true);

Double_t singleMass = -1.;

///////////////////////////////////////
// selectors //////////////////////////
///////////////////////////////////////
bool doGrid             = false;
bool isMC11c            = true;
bool isMuons            = true;    // false for electrons
bool doSigmaUp          = false;
bool dog2               = false;
bool dog4               = true;
bool do33st             = true;
bool do32st             = true;
bool doSmearing         = true;     // false is simply the old selection (before 3+3 / 3+2) -> should not be changed  !
bool doFullKKtemplates  = false;    // will not change anything if doTemplates is "false"
bool doFullZPtemplates  = true;     // will not change anything if doTemplates is "false"
bool dopileup           = true;
bool doOverallEWkfactor = true;
bool doQCDkfactor       = false;
bool doZpT              = true;
bool doEEtrigSF         = true;
bool doTruth            = false;
bool doOfficialZP       = false;
bool doSingleMass       = false;
bool doInterference     = false;
bool doFixedwidth       = false;
bool doTreeLevel        = true; // relevant for truth only

TString channel   = "";
TString chlabel   = "";
TString tsgN      = "";
TString tsgNlabel = "";

void matchFlags(TString channelName="mm", TString gPower="g2", Bool_t doSigUp=0)
{
	doOverallEWkfactor = doInterference;
	
	if(channelName=="mm")      isMuons = true;
	else if(channelName=="ee") isMuons = false;
	
	if(gPower=="g2")      { dog2 = true;  dog4 = false; }
	else if(gPower=="g4") { dog2 = false; dog4 = true;  }
	
	if(doSigUp && isMuons)       doSigmaUp = true;
	else if(!doSigUp && isMuons) doSigmaUp = false;
	
	channel   = (isMuons) ? "mumu"   : "ee";
	chlabel   = (isMuons) ? "#mu#mu" : "ee";
	tsgN      = (dog4)    ? "g4"     : "g2";
	tsgNlabel = (dog4)    ? "g^{4}"  : "g^{2}";
}

TString fileNmaeSuffix()
{
	TString name = "";
	if(isMC11c)              name += "_mc11c";
	if(!isMC11c)             name += "_mc11a";
	if(isMuons)
	{
		if     (do32st && !do33st) name += "_32st";
		else if(do33st && !do32st) name += "_33st";
		else if(do33st && do32st)  name += "_3332st";
		else                       _FATAL("must choose 3+3 / 3+2 or both");
	}
	else                     name += "_ee";
	if(dog2)                 name += "_g2bins";
	else if(dog4)            name += "_g4bins";
	else                     _FATAL("either g4 or g2 bins");
	if(!doInterference)      name += "_noInterference";
	if(!doFullKKtemplates)   name += "_noKKtmplates";
	if(!doFullZPtemplates)   name += "_noZPtmplates";
	if(doSigmaUp && isMuons) name += "_SmrSigUp";
	if(!dopileup)            name += "_noPUrw";
	if(!doOverallEWkfactor)  name += "_noEWkF";
	if(!doQCDkfactor)        name += "_noQCDkF";
	if(!doZpT)               name += "_noZpTrw";
	if(!isMuons && !doEEtrigSF) name += "_noEEtrigSF";
	if(!doTruth)             name += "_noTruth";
	if(doOfficialZP)         name += "_wthOfficialZP";
	if(doFixedwidth)         name += "_fixedBWwidth";
	if(doTreeLevel&&doTruth) name += "_treeLevel";
	if(doSingleMass)         name += "_Xmass"+_s(singleMass);
	return name;
}
///////////////////////////////////////

// other parameters
TString ntupledir = "";
TString ntupledir_regular = (isMC11c) ? "/storage/t3_data/hod/2011/NTUPLEMC11C/AFTERMCP000503" : "/storage/t3_data/hod/2011/NTUPLEMC11C/AFTERMCP000503";

Int_t printmod    = 1000;
Bool_t dolog      = true;

double nZpeak     = 0.;
double nZpeakNoPU = 0.;

/*
double       gNshift = (dog4) ? g4shift : g2shift;
unsigned int ngNbins = (dog4) ? ng4bins : ng2bins;
double       gNNmin  = (dog4) ? g4min   : g2min;
double       gNNmax  = (dog4) ? g4max   : g2max;

double gNXXmin = (dog4) ? (double)(g4min+g4shift) : (double)(g2min+g2shift);
double gNXXmax = (dog4) ? (double)(g4max+g4shift) : (double)(g2max+g2shift);
double dgNXX   = (dog4) ? (gNXXmax-gNXXmin)/(double)ng4bins : (gNXXmax-gNXXmin)/(double)ng2bins;
*/

double gNXXbins = (double)ngNZPbins;
double gNXXmin  = 0.;
double gNXXmax  = gNZPmax;
double dgNXX    = (gNXXmax-gNXXmin)/(double)gNXXbins;

double maxKKwgt = 0.;
double maxZPwgt = 0.;

float event_weight = 1.;
float event_weight_nopileup = 1.;
float event_weight_signals = 1.;
float event_weight_backgrounds = 1.;
double ZpTweight = 1.;
double kFQCD_NNLOvLOss = 1.;
double kFEW_NNLOvLOs   = 1.;

TFile* file;
TTree* tree;
TEventList* elist;
TString fName;
TString tName;
TPaveText* pvtxt_lumi;
TPaveText* pvtxt_atlas;
TLegend*   leg;
TLegend*   leg_template;
TText* txt;
TMapTSP2TCNV  cnvMap;
TMapTSP2TOBJ  oMap;
TMapTSP2TH1   h1Map;
TMapTSP2TH2   h2Map;
TMapSP2TGraph grMap;
TMapTSP2TLINE linMap;
TMapTSP2TTREE treMap;
TMapTSTS      pathMap;
TMapTSd       flatLumiWgtMap;
TMapTSd       mcNeventsMap;
TMapTSd       mcSigmaMap;
TMapTSvf      mcPeriodsNevtsMap;
TMapdi        pTtoIndexMap;

TMapTS2GRPX grpx;
TMapiTS     grpx_ordered;

TLorentzVector* tlva   = new TLorentzVector;
TLorentzVector* tlvb   = new TLorentzVector;
TLorentzVector* tlvtmp = new TLorentzVector;
TVector3*       tv3a   = new TVector3;
TVector3*       tv3b   = new TVector3;
TVector3*       tv3mu  = new TVector3;

TLorentzVector* tlvleptontreelevel = new TLorentzVector;
TLorentzVector* tlvleptontrua = new TLorentzVector;
TLorentzVector* tlvleptontrub = new TLorentzVector;
TLorentzVector* tlvleptonreca = new TLorentzVector;
TLorentzVector* tlvleptonrecb = new TLorentzVector;
TLorentzVector* tlvqa  = new TLorentzVector;
TLorentzVector* tlvqb  = new TLorentzVector;

TLorentzVector* tlvleptontreelevelBoosted = new TLorentzVector;
TLorentzVector* tlvleptontruaBoosted = new TLorentzVector;
TLorentzVector* tlvleptontrubBoosted = new TLorentzVector;
TLorentzVector* tlvleptonrecaBoosted = new TLorentzVector;
TLorentzVector* tlvleptonrecbBoosted = new TLorentzVector;
TLorentzVector* tlvqaBoosted  = new TLorentzVector;
TLorentzVector* tlvqbBoosted  = new TLorentzVector;

TVector3*       tv3mutreelevel = new TVector3;
TVector3*       tv3mutrua = new TVector3;
TVector3*       tv3mutrub = new TVector3;
TVector3*       tv3mureca = new TVector3;
TVector3*       tv3murecb = new TVector3;
TVector3*       tv3qa  = new TVector3;
TVector3*       tv3qb  = new TVector3;
TVector3*       tv3q   = new TVector3;

TVector3*       tv3mutreelevelBoosted = new TVector3;
TVector3*       tv3mutruaBoosted = new TVector3;
TVector3*       tv3mutrubBoosted = new TVector3;
TVector3*       tv3murecaBoosted = new TVector3;
TVector3*       tv3murecbBoosted = new TVector3;
TVector3*       tv3qaBoosted  = new TVector3;
TVector3*       tv3qbBoosted  = new TVector3;


/////////////  MC  /////////////
float all_actualIntPerXing;
float all_averageIntPerXing;
unsigned int all_mc_channel_number;
unsigned int all_mc_event_number;
double all_mc_event_weight;

// int   all_RunNumber;
float all_pileup_weight;
float all_mcevent_weight;
float all_eeTriggerSF; // ELECTRONS ONLY
// float all_intime_pileup_weight;
// float all_outoftime_pileup_weight;
// float all_lumi_pileup_weight;
// float all_EW_kfactor_weight;
// float all_QCD_kfactor_weight;
// float all_total_weight;
// unsigned int all_randomized_decision;

bool truth_all_isValid;
vector<int>*   truth_all_mc_pdgId;
vector<float>* truth_all_mc_charge;
vector<float>* truth_all_mc_pt;
vector<float>* truth_all_mc_m;
vector<float>* truth_all_mc_eta;
vector<float>* truth_all_mc_phi;
float truth_all_Mhat;
// vector<int>*   truth_all_mc_status;
// vector<int>*   truth_all_mc_barcode;
// float truth_all_CosThetaCS;
// float truth_all_CosThetaHE;
// float truth_all_ySystem;
// float truth_all_QT;

vector<float>* truth_all_partons_mc_pt;
vector<float>* truth_all_partons_mc_m;
vector<float>* truth_all_partons_mc_eta;
vector<float>* truth_all_partons_mc_phi;
vector<int>*   truth_all_partons_mc_pdgId;
vector<float>* truth_all_partons_mc_charge;
// vector<int>*   truth_all_partons_mc_status;
// vector<int>*   truth_all_partons_mc_barcode;

// vector<double>* truth_all_vKKwgt;
// vector<double>* truth_all_vZPwgt;
// vector<double>* truth_all_vBSMmass;

// int recon_all_vxp_n;
bool recon_all_isValid;
vector<float>* recon_all_charge;
vector<int>*   recon_all_id;
vector<float>* recon_all_E;
vector<float>* recon_all_pt;
vector<float>* recon_all_m;
vector<float>* recon_all_eta;
vector<float>* recon_all_phi;
// vector<float>* recon_all_px;
// vector<float>* recon_all_py;
// vector<float>* recon_all_pz;
// vector<float>* recon_all_y;
// vector<float>* recon_all_theta;

// vector<float>* recon_all_ptcone20;
// vector<float>* recon_all_ptcone30;
// vector<float>* recon_all_ptcone40;
// vector<float>* recon_all_etcone20;
// vector<float>* recon_all_etcone30;
// vector<float>* recon_all_etcone40;
// vector<float>* recon_all_nucone20;
// vector<float>* recon_all_nucone30;
// vector<float>* recon_all_nucone40;
// vector<unsigned short>* recon_all_allauthor;
// vector<int>*   recon_all_author;
// vector<float>* recon_all_beta;
// vector<float>* recon_all_isMuonLikelihood;
// vector<float>* recon_all_matchchi2;
// vector<int>*   recon_all_matchndof;

float recon_all_Mhat;
// float recon_all_CosThetaCS;
// float recon_all_CosThetaHE;
// float recon_all_ySystem;
// float recon_all_QT;
////////////////////////////////

void clearMaps()
{
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		if(it->second) delete it->second; // the trees take a lot of memory, delete them.
	}
	
	treMap.clear();
	flatLumiWgtMap.clear();
	mcNeventsMap.clear();
	mcSigmaMap.clear();
	pathMap.clear();
}

void setMCtree(TString fPath, TString name, Double_t N, Double_t sigma)
{
	_DEBUG("setMCtree");
	
	file = new TFile(fPath,"READ");
	// TTree* treeTmp = (TTree*)file->Get("truth/truth_tree")/* ->Clone("") */;
	// TEventList* elist;
	// treeTmp->SetEventList(0);
	// treeTmp->Draw(">>elist","recon_all_isValid==1");
	// elist = (TEventList*)gDirectory->Get("elist");
	// treeTmp->SetEventList(elist);
	// Double_t Nrec = elist->GetN();
	// _INFO("Nrec="+_s(Nrec));
	// treMap.insert( make_pair(name, (TTree*)treeTmp->Clone("_valid_rec")) );
	// treeTmp->SetEventList(0);
	// delete treeTmp;
	
	if(isMuons) treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	else        treMap.insert( make_pair(name, (TTree*)file->Get("MyTree")->Clone("")) );
	double datalumi = (isMuons) ? mmluminosity : eeluminosity;
	flatLumiWgtMap.insert( make_pair(name, datalumi/(N/sigma)) );
	mcNeventsMap.insert( make_pair(name, N) );
	mcSigmaMap.insert( make_pair(name, sigma) );
	pathMap.insert( make_pair(name, fPath) );
}

int proccount(int& counter)
{
	counter = counter+1;
	return counter;
}

void samples()
{
	_DEBUG("samples");
	/*GRPX::GRPX(int o, TString l,
				 Color_t fc, Int_t fs,
				 Color_t lc, Int_t ls, Int_t lw,
				 Color_t mc, Int_t mst, Int_t mss,
				 )*/
	int counter = 0;
	grpx.insert( make_pair("DY"+channel,   new GRPX(counter,"#gamma/Z",      kAzure+8,-1,   kBlack,1,1,  -1,-1,-1)));
	grpx_ordered.insert( make_pair(grpx["DY"+channel]->order,"DY"+channel) );
	
	if(doOfficialZP)
	{
		counter = 100;
		if(isMuons)
		{
			grpx.insert( make_pair("Zprime_SSM1000",  new GRPX(counter,"1000 GeV Z'_{SSM}",  kAzure+0,-1,    kBlack,1,1,  -1,-1,-1)));
			grpx_ordered.insert( make_pair(grpx["Zprime_SSM1000"]->order,"Zprime_SSM1000") );
			if(isMC11c)
			{
				grpx.insert( make_pair("Zprime_SSM1250",  new GRPX(proccount(counter),"1250 GeV Z'_{SSM}",  kAzure-2,-1,  kBlack,1,1,  -1,-1,-1)));
				grpx_ordered.insert( make_pair(grpx["Zprime_SSM1250"]->order,"Zprime_SSM1250") );
			}
			grpx.insert( make_pair("Zprime_SSM1500",  new GRPX(proccount(counter),"1500 GeV Z'_{SSM}",  kAzure-2,-1,  kBlack,1,1,  -1,-1,-1)));
			grpx_ordered.insert( make_pair(grpx["Zprime_SSM1500"]->order,"Zprime_SSM1500") );
			grpx.insert( make_pair("Zprime_SSM1750",  new GRPX(proccount(counter),"1750 GeV Z'_{SSM}",  kAzure-2,-1,  kBlack,1,1,  -1,-1,-1)));
			grpx_ordered.insert( make_pair(grpx["Zprime_SSM1750"]->order,"Zprime_SSM1750") );
			grpx.insert( make_pair("Zprime_SSM2000",  new GRPX(proccount(counter),"2000 GeV Z'_{SSM}",  kAzure-3,-1,  kBlack,1,1,  -1,-1,-1)));
			grpx_ordered.insert( make_pair(grpx["Zprime_SSM2000"]->order,"Zprime_SSM2000") );
		}
		else
		{
			_INFO("not yet implemented the official Z'->ee");
		}
	}
}

void readInput(vector<TString>& vnames)
{
	if(vnames.size()!=0) vnames.clear();

	/*
	string line;
	ifstream myfile("input.txt");
	if(myfile.is_open())
	{
		while( myfile.good() )
		{
			getline(myfile,line);
			TString name = (TString)line;
			name.ReplaceAll("\n","");
			name.ReplaceAll(" ","");
			if(!name.Contains(".root")) continue;
			_INFO("reading -> "+line);
			vnames.push_back(name);
		}
		myfile.close();
	}
	else _FATAL("Unable to open file"); 
	*/

	string argStr;
	unsigned int delpos;
	string sFileName = "input.txt";
	ifstream ifs(sFileName.c_str());
	string sLine = "";
	while(!ifs.eof())
	{
		getline(ifs,sLine);
		argStr += sLine;
	}
	
	// split by ','
	vector<string> fileList;
	string tmp;
	for (size_t i=0 ; i<argStr.length(); ++i)
	{
		if(argStr.substr(i,1)!=",") tmp += argStr.substr(i,1);
		else
		{
			fileList.push_back(tmp);
			_INFO("tmp="+tmp);
			tmp.clear();
		}

		if(i==argStr.length()-1)
		{
			fileList.push_back(tmp);
			_INFO("tmp="+tmp);
			tmp.clear();
		}
	}

	// get the neames in TString
	for (unsigned int iFile=0; iFile<fileList.size(); ++iFile)
	{
		TString name = (TString)fileList[iFile];
		name.ReplaceAll("\n","");
		name.ReplaceAll(" ","");
		if(!name.Contains(".root")) continue;
		_INFO("reading -> "+(string)name);
		vnames.push_back(name);
	}
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	////////////////
	clearMaps(); ///
	////////////////

	if(doGrid)
	{
		vector<TString> vnames;
		readInput(vnames);

		TString name;
		Double_t N;
		Double_t sigma;

		for(unsigned int n=0 ; n<vnames.size() ; n++)
		{
			_INFO("setting file -> "+(string)vnames[n]);

			if(isMuons)
			{
				if(vnames[n].Contains("75M120"))    { name="mcLocalControl_Pythia6_DYmumu_75M120";    N=99999;  sigma=7.9836E-01*nb2fb; }
				if(vnames[n].Contains("120M250"))   { name="mcLocalControl_Pythia6_DYmumu_120M250";   N=99949;  sigma=8.5304E-03*nb2fb; }
				if(vnames[n].Contains("250M400"))   { name="mcLocalControl_Pythia6_DYmumu_250M400";   N=100000; sigma=4.1004E-04*nb2fb; }
				if(vnames[n].Contains("400M600"))   { name="mcLocalControl_Pythia6_DYmumu_400M600";   N=100000; sigma=6.6393E-05*nb2fb; }
				if(vnames[n].Contains("600M800"))   { name="mcLocalControl_Pythia6_DYmumu_600M800";   N=99900;  sigma=1.0955E-05*nb2fb; }
				if(vnames[n].Contains("800M1000"))  { name="mcLocalControl_Pythia6_DYmumu_800M1000";  N=99999;  sigma=2.6470E-06*nb2fb; }
				if(vnames[n].Contains("1000M1250")) { name="mcLocalControl_Pythia6_DYmumu_1000M1250"; N=100000; sigma=8.9015E-07*nb2fb; }
				if(vnames[n].Contains("1250M1500")) { name="mcLocalControl_Pythia6_DYmumu_1250M1500"; N=99999;  sigma=2.3922E-07*nb2fb; }
				if(vnames[n].Contains("1500M1750")) { name="mcLocalControl_Pythia6_DYmumu_1500M1750"; N=99999;  sigma=7.3439E-08*nb2fb; }
				if(vnames[n].Contains("1750M2000")) { name="mcLocalControl_Pythia6_DYmumu_1750M2000"; N=100000; sigma=2.4643E-08*nb2fb; }
				if(vnames[n].Contains("2000M2250")) { name="mcLocalControl_Pythia6_DYmumu_2000M2250"; N=100000; sigma=8.7619E-09*nb2fb; }
				if(vnames[n].Contains("2250M2500")) { name="mcLocalControl_Pythia6_DYmumu_2250M2500"; N=99950;  sigma=3.2232E-09*nb2fb; }
				if(vnames[n].Contains("2500M2750")) { name="mcLocalControl_Pythia6_DYmumu_2500M2750"; N=99000;  sigma=1.2073E-09*nb2fb; }
				if(vnames[n].Contains("2750M3000")) { name="mcLocalControl_Pythia6_DYmumu_2750M3000"; N=99999;  sigma=4.4763E-10*nb2fb; }
				if(vnames[n].Contains("M3000"))     { name="mcLocalControl_Pythia6_DYmumu_M3000";     N=100000; sigma=2.5586E-10*nb2fb; }
			}
			else
			{
				if(vnames[n].Contains("75M120"))    { name="mcLocalControl_Pythia6_DYee_75M120";    N=100000; sigma=7.9837E-01*nb2fb; }
				if(vnames[n].Contains("120M250"))   { name="mcLocalControl_Pythia6_DYee_120M250";   N=100000; sigma=8.5207E-03*nb2fb; }
				if(vnames[n].Contains("250M400"))   { name="mcLocalControl_Pythia6_DYee_250M400";   N=100000; sigma=4.1004E-04*nb2fb; }
				if(vnames[n].Contains("400M600"))   { name="mcLocalControl_Pythia6_DYee_400M600";   N=99999;  sigma=6.6397E-05*nb2fb; }
				if(vnames[n].Contains("600M800"))   { name="mcLocalControl_Pythia6_DYee_600M800";   N=100000; sigma=1.0959E-05*nb2fb; }
				if(vnames[n].Contains("800M1000"))  { name="mcLocalControl_Pythia6_DYee_800M1000";  N=99999;  sigma=2.6468E-06*nb2fb; }
				if(vnames[n].Contains("1000M1250")) { name="mcLocalControl_Pythia6_DYee_1000M1250"; N=99998;  sigma=8.9030E-07*nb2fb; }
				if(vnames[n].Contains("1250M1500")) { name="mcLocalControl_Pythia6_DYee_1250M1500"; N=99997;  sigma=2.3922E-07*nb2fb; }
				if(vnames[n].Contains("1500M1750")) { name="mcLocalControl_Pythia6_DYee_1500M1750"; N=99998;  sigma=7.3439E-08*nb2fb; }
				if(vnames[n].Contains("1750M2000")) { name="mcLocalControl_Pythia6_DYee_1750M2000"; N=99996;  sigma=2.4643E-08*nb2fb; }
				if(vnames[n].Contains("2000M2250")) { name="mcLocalControl_Pythia6_DYee_2000M2250"; N=99997;  sigma=8.7619E-09*nb2fb; }
				if(vnames[n].Contains("2250M2500")) { name="mcLocalControl_Pythia6_DYee_2250M2500"; N=99993;  sigma=3.2232E-09*nb2fb; }
				if(vnames[n].Contains("2500M2750")) { name="mcLocalControl_Pythia6_DYee_2500M2750"; N=99994;  sigma=1.2073E-09*nb2fb; }
				if(vnames[n].Contains("2750M3000")) { name="mcLocalControl_Pythia6_DYee_2750M3000"; N=99995;  sigma=4.4770E-10*nb2fb; }
				if(vnames[n].Contains("M3000"))     { name="mcLocalControl_Pythia6_DYee_M3000";     N=99994;  sigma=2.5586E-10*nb2fb; }
			}
			TString filename = vnames[n];

			///////////////////////////////////////
			setMCtree(filename,name,N,sigma); /////
			///////////////////////////////////////

		}

		///////////
		return; ///
		///////////
	}
	


	////////////////////////////////////////////////////////////////// 
	ntupledir = ntupledir_regular;

	TString sNMst = "";
	if(isMuons)
	{
		sNMst += (do33st && !do32st) ? "_33st" : "";
		sNMst += (do32st && !do33st) ? "_32st" : "";
		sNMst += (do32st && do33st)  ? "_3332st" : "";
	}
	else
	{
		sNMst += "";
	}
	
	TString sSMR = "";
	sSMR += (doSmearing && isMuons) ? "_smeared" : "";
	
	TString sSIGUP = "";
	sSIGUP += (doSigmaUp && isMuons) ? "_sigmaUp" : "";
	
	//////////////////////////////////////////////
	TString filesuffix = sNMst+sSMR+sSIGUP; //////
	//////////////////////////////////////////////
	
	if(tsMCname=="DYmumu")
	{
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_75M120"+filesuffix+".root",    "mcLocalControl_Pythia6_DYmumu_75M120",    99999,  7.9836E-01*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_120M250"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_120M250",   99949,  8.5304E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_250M400"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_250M400",   100000, 4.1004E-04*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_400M600"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_400M600",   100000, 6.6393E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_600M800"+filesuffix+".root",   "mcLocalControl_Pythia6_DYmumu_600M800",   99900,  1.0955E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_800M1000"+filesuffix+".root",  "mcLocalControl_Pythia6_DYmumu_800M1000",  99999,  2.6470E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1000M1250"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1000M1250", 100000, 8.9015E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1250M1500"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1250M1500", 99999,  2.3922E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1500M1750"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1500M1750", 99999,  7.3439E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_1750M2000"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_1750M2000", 100000, 2.4643E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2000M2250"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2000M2250", 100000, 8.7619E-09*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2250M2500"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2250M2500", 99950,  3.2232E-09*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2500M2750"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2500M2750", 99000,  1.2073E-09*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_2750M3000"+filesuffix+".root", "mcLocalControl_Pythia6_DYmumu_2750M3000", 99999,  4.4763E-10*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYmumu_M3000"+filesuffix+".root",     "mcLocalControl_Pythia6_DYmumu_M3000",     100000, 2.5586E-10*nb2fb);
	}
	else if(tsMCname=="DYee")
	{
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_75M120"+filesuffix+".root",    "mcLocalControl_Pythia6_DYee_75M120",    100000, 7.9837E-01*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_120M250"+filesuffix+".root",   "mcLocalControl_Pythia6_DYee_120M250",   100000, 8.5207E-03*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_250M400"+filesuffix+".root",   "mcLocalControl_Pythia6_DYee_250M400",   100000, 4.1004E-04*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_400M600"+filesuffix+".root",   "mcLocalControl_Pythia6_DYee_400M600",   99999 , 6.6397E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_600M800"+filesuffix+".root",   "mcLocalControl_Pythia6_DYee_600M800",   100000, 1.0959E-05*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_800M1000"+filesuffix+".root",  "mcLocalControl_Pythia6_DYee_800M1000",  99999,  2.6468E-06*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_1000M1250"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_1000M1250", 99998,  8.9030E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_1250M1500"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_1250M1500", 99997,  2.3922E-07*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_1500M1750"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_1500M1750", 99998,  7.3439E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_1750M2000"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_1750M2000", 99996,  2.4643E-08*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_2000M2250"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_2000M2250", 99997,  8.7619E-09*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_2250M2500"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_2250M2500", 99993,  3.2232E-09*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_2500M2750"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_2500M2750", 99994,  1.2073E-09*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_2750M3000"+filesuffix+".root", "mcLocalControl_Pythia6_DYee_2750M3000", 99995,  4.4770E-10*nb2fb);
		setMCtree(ntupledir+"/mcLocalControl_Pythia6_DYee_M3000"+filesuffix+".root",     "mcLocalControl_Pythia6_DYee_M3000",     99994,  2.5586E-10*nb2fb);
	}
	
	if(doOfficialZP)
	{
		if(isMuons)
		{
			if(tsMCname=="Zprime_SSM1000")
			{
				setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1000"+filesuffix+".root", "mcLocalControl_Zprime_SSM1000", 20000, 1.2466E-04*nb2fb);
			}
			if(tsMCname=="Zprime_SSM1250" && isMC11c)
			{
				setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1250"+filesuffix+".root", "mcLocalControl_Zprime_SSM1250", 20000, 3.9887E-05*nb2fb);
			}
			if(tsMCname=="Zprime_SSM1500")
			{
				setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1500"+filesuffix+".root", "mcLocalControl_Zprime_SSM1500", 20000, 1.4380E-05*nb2fb);
			}
			if(tsMCname=="Zprime_SSM1750")
			{
				setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM1750"+filesuffix+".root", "mcLocalControl_Zprime_SSM1750", 20000, 5.6743E-06*nb2fb);
			}
			if(tsMCname=="Zprime_SSM2000")
			{
				setMCtree(ntupledir+"/mcLocalControl_Zprime_mumu_SSM2000"+filesuffix+".root", "mcLocalControl_Zprime_SSM2000", 20000, 2.4357E-06*nb2fb);
			}
		}
		else
		{
			_INFO("not yet implemented the official Z'->ee");
		}
	}
}

void setMCbranches()
{
	_DEBUG("setMCbranches");

	truth_all_mc_pdgId = 0;
	truth_all_mc_charge = 0;
	truth_all_mc_pt = 0;
	truth_all_mc_m = 0;
	truth_all_mc_eta = 0;
	truth_all_mc_phi = 0;
	// truth_all_mc_status = 0;
	// truth_all_mc_barcode = 0;
	
	truth_all_partons_mc_pt = 0;
	truth_all_partons_mc_m = 0;
	truth_all_partons_mc_eta = 0;
	truth_all_partons_mc_phi = 0;
	truth_all_partons_mc_pdgId = 0;
	truth_all_partons_mc_charge = 0;
	// truth_all_partons_mc_status = 0;
	// truth_all_partons_mc_barcode = 0;

	recon_all_id = 0;
	recon_all_charge = 0;
	recon_all_E = 0;
	recon_all_pt = 0;
	recon_all_m = 0;
	recon_all_eta = 0;
	recon_all_phi = 0;
	// recon_all_px = 0;
	// recon_all_py = 0;
	// recon_all_pz = 0;
	// recon_all_y = 0;
	// recon_all_theta = 0;
	
	// recon_all_ptcone20 = 0;
	// recon_all_ptcone30 = 0;
	// recon_all_ptcone40 = 0;
	// recon_all_etcone20 = 0;
	// recon_all_etcone30 = 0;
	// recon_all_etcone40 = 0;
	// recon_all_nucone20 = 0;
	// recon_all_nucone30 = 0;
	// recon_all_nucone40 = 0;
	// recon_all_allauthor = 0;
	// recon_all_author = 0;
	// recon_all_beta = 0;
	// recon_all_isMuonLikelihood = 0;
	// recon_all_matchchi2 = 0;
	// recon_all_matchndof = 0;
	
	// tree->SetBranchAddress( "all_actualIntPerXing",  &all_actualIntPerXing );
	// tree->SetBranchAddress( "all_averageIntPerXing", &all_averageIntPerXing );
	// tree->SetBranchAddress( "all_mc_channel_number", &all_mc_channel_number );
	// tree->SetBranchAddress( "all_mc_event_number",   &all_mc_event_number );
	// tree->SetBranchAddress( "all_mc_event_weight",   &all_mc_event_weight );
	
	// tree->SetBranchAddress( "all_RunNumber",         &all_RunNumber );
	tree->SetBranchAddress( "all_mcevent_weight",     &all_mcevent_weight );
	tree->SetBranchAddress( "all_pileup_weight",      &all_pileup_weight );
	if(!isMuons) tree->SetBranchAddress( "all_eeTriggerSF", &all_eeTriggerSF );
	// tree->SetBranchAddress( "all_intime_pileup_weight",    &all_intime_pileup_weight );
	// tree->SetBranchAddress( "all_outoftime_pileup_weight", &all_outoftime_pileup_weight );
	// tree->SetBranchAddress( "all_lumi_pileup_weight", &all_lumi_pileup_weight );
	// tree->SetBranchAddress( "all_EW_kfactor_weight",  &all_EW_kfactor_weight );
	// tree->SetBranchAddress( "all_QCD_kfactor_weight", &all_QCD_kfactor_weight );
	// tree->SetBranchAddress( "all_total_weight",       &all_total_weight );
	// tree->SetBranchAddress( "all_randomized_decision",&all_randomized_decision );

	tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
	tree->SetBranchAddress("truth_all_mc_pt", &truth_all_mc_pt);
	tree->SetBranchAddress("truth_all_mc_m", &truth_all_mc_m);
	tree->SetBranchAddress("truth_all_mc_eta", &truth_all_mc_eta);
	tree->SetBranchAddress("truth_all_mc_phi", &truth_all_mc_phi);
	tree->SetBranchAddress("truth_all_mc_pdgId", &truth_all_mc_pdgId);
	tree->SetBranchAddress("truth_all_mc_charge", &truth_all_mc_charge);
	tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
	// tree->SetBranchAddress("truth_all_mc_status", &truth_all_mc_status);
	// tree->SetBranchAddress("truth_all_mc_barcode", &truth_all_mc_barcode);
	// tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
	// tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
	// tree->SetBranchAddress("truth_all_ySystem", &truth_all_ySystem);
	// tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
	
	tree->SetBranchAddress("truth_all_partons_mc_pt", &truth_all_partons_mc_pt);
	tree->SetBranchAddress("truth_all_partons_mc_m", &truth_all_partons_mc_m);
	tree->SetBranchAddress("truth_all_partons_mc_eta", &truth_all_partons_mc_eta);
	tree->SetBranchAddress("truth_all_partons_mc_phi", &truth_all_partons_mc_phi);
	tree->SetBranchAddress("truth_all_partons_mc_pdgId", &truth_all_partons_mc_pdgId);
	tree->SetBranchAddress("truth_all_partons_mc_charge", &truth_all_partons_mc_charge);
	// tree->SetBranchAddress("truth_all_partons_mc_status", &truth_all_partons_mc_status);
	// tree->SetBranchAddress("truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	
	// tree->SetBranchAddress("truth_all_vKKwgt",   &truth_all_vKKwgt);
	// tree->SetBranchAddress("truth_all_vZPwgt",   &truth_all_vZPwgt);
	// tree->SetBranchAddress("truth_all_vBSMmass", &truth_all_vBSMmass);

	// tree->SetBranchAddress("recon_all_vxp_n", &recon_all_vxp_n);
	tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
	tree->SetBranchAddress("recon_all_charge", &recon_all_charge);
	tree->SetBranchAddress("recon_all_id", &recon_all_id);
	tree->SetBranchAddress("recon_all_E", &recon_all_E);
	tree->SetBranchAddress("recon_all_pt", &recon_all_pt);
	tree->SetBranchAddress("recon_all_m", &recon_all_m);
	tree->SetBranchAddress("recon_all_eta", &recon_all_eta);
	tree->SetBranchAddress("recon_all_phi", &recon_all_phi);
	tree->SetBranchAddress("recon_all_Mhat", &recon_all_Mhat);
	// tree->SetBranchAddress("recon_all_px", &recon_all_px);
	// tree->SetBranchAddress("recon_all_py", &recon_all_py);
	// tree->SetBranchAddress("recon_all_pz", &recon_all_pz);
	// tree->SetBranchAddress("recon_all_ptcone20", &recon_all_ptcone20);
	// tree->SetBranchAddress("recon_all_ptcone30", &recon_all_ptcone30);
	// tree->SetBranchAddress("recon_all_ptcone40", &recon_all_ptcone40);
	// tree->SetBranchAddress("recon_all_etcone20", &recon_all_etcone20);
	// tree->SetBranchAddress("recon_all_etcone30", &recon_all_etcone30);
	// tree->SetBranchAddress("recon_all_etcone40", &recon_all_etcone40);
	// tree->SetBranchAddress("recon_all_nucone20", &recon_all_nucone20);
	// tree->SetBranchAddress("recon_all_nucone30", &recon_all_nucone30);
	// tree->SetBranchAddress("recon_all_nucone40", &recon_all_nucone40);
	// tree->SetBranchAddress("recon_all_allauthor", &recon_all_allauthor);
	// tree->SetBranchAddress("recon_all_author", &recon_all_author);
	// tree->SetBranchAddress("recon_all_beta", &recon_all_beta);
	// tree->SetBranchAddress("recon_all_isMuonLikelihood", &recon_all_isMuonLikelihood);
	// tree->SetBranchAddress("recon_all_matchchi2", &recon_all_matchchi2);
	// tree->SetBranchAddress("recon_all_matchndof", &recon_all_matchndof);
	// tree->SetBranchAddress("recon_all_y", &recon_all_y);
	// tree->SetBranchAddress("recon_all_theta", &recon_all_theta);
	// tree->SetBranchAddress("recon_all_CosThetaCS", &recon_all_CosThetaCS);
	// tree->SetBranchAddress("recon_all_CosThetaHE", &recon_all_CosThetaHE);
	// tree->SetBranchAddress("recon_all_ySystem", &recon_all_ySystem);
	// tree->SetBranchAddress("recon_all_QT", &recon_all_QT);
	
	_DEBUG("successfully read mc branches");
}

float getFlatLumiWeight(TString mcName)
{
	_DEBUG("getFlatLumiWeight");
	float N     = mcNeventsMap[mcName];
	float sigma = mcSigmaMap[mcName];
	float Lmc   = N/sigma;
	double datalumi = (isMuons) ? mmluminosity : eeluminosity;
	return datalumi/Lmc;
}

void hbook()
{
	_DEBUG("hbook");
	
	setLogBins(npbins,pmin,pmax,pbins);
	setLogBins(nlogptbins,logptmin,logptmax,logptbins);
	setLogBins(nlogqtbins,logqtmin,logqtmax,logqtbins);
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogimassbins,logimassmin,logimassmax,logimassbins);
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);
	setLogBins(nloglimitimassbins, loglimitimassmin, loglimitimassmax, loglimitimassbins);
	setLogBins(nlogofficialimassbins,logofficialimassmin,logofficialimassmax,logofficialimassbins);
	setLogBins(nlogisoimassbins,logisoimassmin,logisoimassmax,logisoimassbins);
	setSqrtBins(nsqrtofficialptbins, sqrtofficialptmin, sqrtofficialptmax, sqrtofficialptbins);
	setSqrtBins(nsqrtofficialqtbins, sqrtofficialqtmin, sqrtofficialqtmax, sqrtofficialqtbins);
	setSqrtBins(nsqrtg4bins, sqrtg4min, sqrtg4max, sqrtg4bins);
	setPowerBins(npowerbins,step,power,powerbins);
	setgNbins(ngNbinslow,ngNbinshigh,gNmin,gNmid,gNmax,gNbins);
	
	//// KK/ZP templates for the limit
	for(double M=mXXmin ; M<=mXXmax ; M+=dmXX)
	{
		//////////////////////////////////////
		if(doSingleMass) M = singleMass; /////
		//////////////////////////////////////
		
		TString massName = (TString)_s(M);
		
		if(doFullKKtemplates)
		{
			h1Map.insert( make_pair("hMass_template_KK"+massName, new TH1D("hMass_template_KK"+massName, chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
			if(doTruth) h1Map.insert( make_pair("hMass_truth_template_KK"+massName, new TH1D("hMass_truth_template_KK"+massName, chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
			
			h2Map.insert( make_pair("h"+tsgN+"Mass_template_KK"+massName, new TH2D("h"+tsgN+"Mass_template_KK"+massName, chlabel+" mass vs. "+tsgNlabel+";m_{"+chlabel+"} TeV;"+tsgNlabel+";Events", nloglimitimassbins,loglimitimassbins, ngNKKbins,gNKKmin,gNKKmax /*ngNbinstotal,gNbins*/ /*ngNbins,gNNmin,gNNmax*/ /*npowerbins,powerbins*/) ) );
			if(doTruth)
			{
				h2Map.insert( make_pair("h"+tsgN+"Mass_truth_template_KK"+massName, new TH2D("h"+tsgN+"Mass_truth_template_KK"+massName, chlabel+" mass vs. "+tsgNlabel+";m_{"+chlabel+"} TeV;g^{4};Events", nloglimitimassbins,loglimitimassbins, ngNKKbins,gNKKmin,gNKKmax /*ngNbinstotal,gNbins*/ /*ngNbins,gNNmin,gNNmax*/ /*npowerbins,powerbins*/) ) );
			}
		}
		if(doFullZPtemplates)
		{
			h1Map.insert( make_pair("hMass_template_Zprime_SSM"+massName, new TH1D("hMass_template_Zprime_SSM"+massName, chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
			if(doTruth) h1Map.insert( make_pair("hMass_truth_template_Zprime_SSM"+massName, new TH1D("hMass_truth_template_Zprime_SSM"+massName, chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
			
			h2Map.insert( make_pair("h"+tsgN+"Mass_template_Zprime_SSM"+massName, new TH2D("h"+tsgN+"Mass_template_Zprime_SSM"+massName, chlabel+" mass vs. "+tsgNlabel+";m_{"+chlabel+"} TeV;"+tsgNlabel+";Events", nloglimitimassbins,loglimitimassbins, ngNZPbins,gNZPmin,gNZPmax /*ngNbinstotal,gNbins*/ /*ngNbins,gNNmin,gNNmax*/ /*npowerbins,powerbins*/) ) );
			if(doTruth)
			{
				h2Map.insert( make_pair("h"+tsgN+"Mass_truth_template_Zprime_SSM"+massName, new TH2D("h"+tsgN+"Mass_truth_template_Zprime_SSM"+massName, chlabel+" mass vs. "+tsgNlabel+";m_{"+chlabel+"} TeV;"+tsgNlabel+";Events", nloglimitimassbins,loglimitimassbins, ngNZPbins,gNZPmin,gNZPmax /*ngNbinstotal,gNbins*/ /*ngNbins,gNNmin,gNNmax*/ /*npowerbins,powerbins*/) ) );
			}
		}
		
		/////////////////////////////
		if(doSingleMass) break; /////
		/////////////////////////////
	}
	
	// For the truth information of all the models
	for(TMapTS2GRPX::iterator it=grpx.begin() ; it!=grpx.end() ; ++it)
	{
		TString name = it->first;

		h1Map.insert( make_pair("hMass_"+name, new TH1D("hMass_"+name, chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		if(doTruth) h1Map.insert( make_pair("hMass_"+name+"_truth", new TH1D("hMass_"+name+"_truth", chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		
		if(doOfficialZP) h1Map.insert( make_pair("hMass_"+name+"_template", new TH1D("hMass_"+name+"_template", chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		if(doOfficialZP && doTruth) h1Map.insert( make_pair("hMass_"+name+"_template_truth", new TH1D("hMass_"+name+"_template_truth", chlabel+" mass;m_{"+chlabel+"} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
	}
}

void setSumW2()
{
	// Associated errors:
	// By default, for each bin, the sum of weights is computed at fill time.
	// One can also call TH1::Sumw2 to force the storage and computation of
	// the sum of the square of weights per bin. If Sumw2 has been called,
	// the error per bin is computed as the sqrt(sum of squares of weights),
	// otherwise the error is set equal to the sqrt(bin content).
	// To return the error for a given bin number, do:
	// Double_t error = h->GetBinError(bin);
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it) it->second->Sumw2();
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it) it->second->Sumw2();
}

void weightsNoPU(TString tsMCname, float mass=0., unsigned int truXid=0, double truXmass=0., double truXpT=0.)
{
	//// ZpT reweighting
	ZpTweight = (truXid==PDTZ || truXid==PDTZPRIME0 || truXid==PDTKK) ? ZpTrw->GetWeightZee(truXpT,truXmass) : 1.; 
	if(isnaninf(ZpTweight)) _FATAL("ZpTweight is nan or inf -> "+_s(ZpTweight)+": in truXid="+_s(truXid)+", truXmass="+_s(truXmass)+" MeV, truXpT="+_s(truXpT)+" MeV");
	
	//// kFactors:			
	kFQCD_NNLOvLOss = QCD(mass,"NNLO/LO**");
	kFEW_NNLOvLOs   = (isMuons) ? ElectroWeak(mass) : EWkFactorEle(mass);
	if(isnaninf(kFQCD_NNLOvLOss)) _FATAL("kFQCD_NNLOvLOss is nan or inf -> "+_s(kFQCD_NNLOvLOss)+": in "+_s(mass)+" GeV");
	if(isnaninf(kFEW_NNLOvLOs))   _FATAL("kFEW_NNLOvLOs is nan or inf -> "+_s(kFEW_NNLOvLOs)+": in "+_s(mass)+" GeV");
	
	event_weight =  (isMuons)                ? all_mcevent_weight : 1.; // the generator intrinsic event weight  //// should be the same for mm and ee
	event_weight *= (doQCDkfactor)           ? kFQCD_NNLOvLOss    : 1.;
	event_weight *= (doOverallEWkfactor)     ? kFEW_NNLOvLOs      : 1.;
	event_weight *= (doZpT)                  ? ZpTweight          : 1.;
	event_weight *= (!isMuons && doEEtrigSF) ? all_eeTriggerSF    : 1.;
	if(isnaninf(event_weight)) _FATAL("event_weight is nan or inf -> "+_s(event_weight));
}

void weights(TString tsMCname, float mass=0., unsigned int truXid=0, double truXmass=0., double truXpT=0.)
{
	//////////////////////////////////////////////////////////
	//// get the weights without the pileup //////////////////
	weightsNoPU(tsMCname, mass, truXid, truXmass, truXpT); ///
	//////////////////////////////////////////////////////////
	
	event_weight_nopileup = event_weight;
	if(isnaninf(event_weight_nopileup)) _FATAL("event_weight_nopileup is nan or inf -> "+_s(event_weight_nopileup));
	
	event_weight *= (dopileup) ? all_pileup_weight : 1.;
	if(isnaninf(event_weight)) _FATAL("event_weight is nan or inf -> "+_s(event_weight));
}

void hfill(TString tsMCname="", Double_t wgt=1.)
{
	_DEBUG("hfill");
	
	float mass = 0.;
	float ca   = 0.;
	float cb   = 0.;
	
	float truth_mass = 0.;
	float truth_s    = 0.;
	float truth_cost = 0.;
	unsigned int truth_idIn = 0;
	unsigned int idOut      = (isMuons) ? 13 : 11; // muon or electron
	double KKoverSM_weight     = 0.;
	double ZPoverSM_weight     = 0.;
	// double KKnoSMoverSM_weight = 0.;
	// double ZPnoSMoverSM_weight = 0.;
	
	int ileptontreelvl = -999;
	int ileptontru     = -999;
	int ialeptontru    = -999;
	int ileptonrec     = -999;
	int ialeptonrec    = -999;
	
	int iquark  = -999;
	int iaquark = -999;
	
	unsigned int truXid = 0;
	double truXmass  = 0.;
	double truXpT    = 0.;
	
	double leptonMass = (isMuons) ?  muonMass : elecMass;

	_DEBUG("");
	
	if(truth_all_isValid)
	{
		ileptontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
		ialeptontru = (ileptontru==0) ? 1 : 0;
		float leptonpt  = truth_all_mc_pt->at(ileptontru);
		float aleptonpt = truth_all_mc_pt->at(ialeptontru);
		if(!isMuons) //// ???????????????????????????????????????????????????????????????????????????????????????????????????????????
		{
			leptonpt  /= 1000.;
			aleptonpt /= 1000.;
		}
		tlvleptontrua->SetPtEtaPhiM(leptonpt,  truth_all_mc_eta->at(ileptontru),  truth_all_mc_phi->at(ileptontru),  leptonMass);
		tlvleptontrub->SetPtEtaPhiM(aleptonpt, truth_all_mc_eta->at(ialeptontru), truth_all_mc_phi->at(ialeptontru), leptonMass);
		(*tv3mutrua) = tlvleptontrua->Vect();
		(*tv3mutrub) = tlvleptontrub->Vect();
		tlvleptontruaBoosted = fkinematics::Boost(tlvleptontrua,tlvleptontrub,tlvleptontrua);
		tlvleptontrubBoosted = fkinematics::Boost(tlvleptontrua,tlvleptontrub,tlvleptontrub);
		(*tv3mutruaBoosted) = tlvleptontruaBoosted->Vect();
		(*tv3mutrubBoosted) = tlvleptontrubBoosted->Vect();
		mass = fkinematics::imass(tlvleptontrua,tlvleptontrub);
		
		_DEBUG("");
		
		// (1) take the true quark and the true lepton and boost it to the cmf.
		// (2) calculate cos(theta*) between the tree-level lepton and the quark
		// (3) get the quark id
		// (4) get the mass of the intermediate state (Z)
		// iquark = (truth_all_partons_mc_pdgId->at(0)>0) ? 0 : 1;
		// iaquark = (iquark==0) ? 1 : 0;
		ileptontreelvl = (truth_all_partons_mc_pdgId->at(5)>0) ? 5 : 6; // outgoing leptons are written in enties 2 and 3 of the vectors "truth_all_partons_mc_*"
		iquark  = (truth_all_partons_mc_pdgId->at(2)>0) ? 2 : 3;        // incoming partons are written in enties 2 and 3 of the vectors "truth_all_partons_mc_*"
		iaquark = (iquark==2) ? 3 : 2;
		tlvleptontreelevel->SetPtEtaPhiM(truth_all_partons_mc_pt->at(ileptontreelvl), truth_all_partons_mc_eta->at(ileptontreelvl), truth_all_partons_mc_phi->at(ileptontreelvl),truth_all_partons_mc_m->at(ileptontreelvl));
		tlvqa->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iquark), truth_all_partons_mc_eta->at(iquark), truth_all_partons_mc_phi->at(iquark),truth_all_partons_mc_m->at(iquark));
		tlvqb->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iaquark), truth_all_partons_mc_eta->at(iaquark), truth_all_partons_mc_phi->at(iaquark),truth_all_partons_mc_m->at(iaquark));
		(*tv3mutreelevel) = tlvleptontreelevel->Vect();
		(*tv3qa) = tlvqa->Vect();
		(*tv3qb) = tlvqb->Vect();
		tlvleptontreelevelBoosted = fkinematics::Boost(tlvqa,tlvqb,tlvleptontreelevel);
		tlvqaBoosted = fkinematics::Boost(tlvqa,tlvqb,tlvqa);
		tlvqbBoosted = fkinematics::Boost(tlvqa,tlvqb,tlvqb);
		(*tv3mutreelevelBoosted) = tlvleptontreelevelBoosted->Vect();
		(*tv3qaBoosted) = tlvqaBoosted->Vect();
		(*tv3qbBoosted) = tlvqbBoosted->Vect();
	
		_DEBUG("");
	
		// bits for the KK weights
		tv3q->SetPtEtaPhi(tlvqaBoosted->Pt(),tlvqaBoosted->Eta(),tlvqaBoosted->Phi());
		tv3mu->SetPtEtaPhi(tlvleptontreelevelBoosted->Pt(),tlvleptontreelevelBoosted->Eta(),tlvleptontreelevelBoosted->Phi());
		truth_cost = tv3q->Dot((*tv3mu))/(tv3q->Mag()*tv3mu->Mag()); // truth cos(theta*)
		truth_idIn = truth_all_partons_mc_pdgId->at(iquark);         // truth incoming flavor
		truth_mass = fkinematics::imass(tlvqa,tlvqb);                // truth gamma/Z mass
		//truth_mass = truth_all_partons_mc_m->at(4);                // truth gamma/Z mass
		if(fabs(truth_mass-truth_all_partons_mc_m->at(4))/sqrt(truth_all_partons_mc_m->at(4))>1.)
		{
			_WARNING("truth mass mismatch: M(qqbar)="+_s(truth_all_partons_mc_m->at(4))+", M(4->"+_s(truth_all_partons_mc_pdgId->at(4))+")="+_s(truth_mass));
		}
		truth_s = truth_mass*truth_mass;
		

		_DEBUG("");
		
		// X = Z/Z'/ZKK are always at index 4.
		truXid   = truth_all_partons_mc_pdgId->at(4);
		truXmass = truth_all_partons_mc_m->at(4)*GeV2MeV;
		truXpT   = truth_all_partons_mc_pt->at(4)*GeV2MeV;
		
		_DEBUG("");
		
		//////////////////////////////////////////////////////
		//// weights handeling ///////////////////////////////
		//// 2nd argument is the truth mass of the mm pair ///
		//// after FSR and it is not the mc_m->at(4) /////////
		weights(tsMCname, mass, truXid, truXmass, truXpT); ///
		// if kF for signals is done in the amplitude then the event_weight does not contain it 
		double weight_dy = (doOverallEWkfactor) ? event_weight : event_weight*kFEW_NNLOvLOs; // relevant only for truth, DY and the official Z'
		//////////////////////////////////////////////////////

		_DEBUG("");
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		mass = (doTreeLevel) ? truth_all_partons_mc_m->at(4) : mass; // mass is M(mumu after FSR) /////
		///////////////////////////////////////////////////////////////////////////////////////////////
		
		_DEBUG("");
		
		/////////// DY and official Z'
		if(doTruth) h1Map["hMass_"+tsMCname+"_truth"]->Fill(mass*GeV2TeV,wgt);
		if(doOfficialZP && doTruth && (tsMCname=="DYmumu" || tsMCname=="DYee"))
		{
			_DEBUG("");
		
			/////////////////////////////
			setCouplingsScale(false); ///
			resetfgZP(); ////////////////
			/////////////////////////////
			
			for(double M=1000. ; M<=2000. ; M+=250.)
			{
				if(!isMC11c && M==1250) continue;
			
				_DEBUG("M="+_s(M));
			
				/////////////////
				setZPmass(M); ///
				/////////////////
				
				TString tsMZP = (TString)_s(M);
				ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
				h1Map["hMass_Zprime_SSM"+tsMZP+"_template_truth"]->Fill(mass*GeV2TeV,wgt*ZPoverSM_weight);
			}
		}
		
		_DEBUG("");
		
		
		_DEBUG("");
		
		for(double M=mXXmin ; M<=mXXmax && doTruth && (tsMCname=="DYmumu" || tsMCname=="DYee") ; M+=dmXX)
		{
			//////////////////////////////////////
			if(doSingleMass) M = singleMass; /////
			//////////////////////////////////////
		
			//////////////////////////////
			// propagate the KK mass /////
			setKKmass(M); ////////////////
			setZPmass(M); ////////////////
			//////////////////////////////
			TString massName = (TString)_s(M);
			TMapTSP2TH2::iterator ii=h2Map.begin();
			TAxis*  gNaxis = (TAxis*)ii->second->GetYaxis();
			// TAxis*  gNaxis = (TAxis*)h2Map["h"+tsgN+"Mass_truth_template_ZP"+massName]->GetYaxis();
			
			_DEBUG("massName="+(string)massName);
			
			if(doTruth)
			{	
				if(doFullKKtemplates)
				{
					/////////////////////////////
					setCouplingsScale(false); ///
					resetfgGKK(); ///////////////
					resetfgZKK(); ///////////////
					/////////////////////////////
				
					if(doInterference) KKoverSM_weight = weightKK(truth_cost,truth_s,truth_idIn,idOut);
					else               KKoverSM_weight = weightKKnoSM(truth_cost,truth_s,truth_idIn,idOut);
					h1Map["hMass_truth_template_KK"+massName]->Fill(mass*GeV2TeV,wgt*KKoverSM_weight); // need to fluctuate this later
				}
				
				if(doFullZPtemplates)
				{
					/////////////////////////////
					setCouplingsScale(false); ///
					resetfgZP(); ////////////////
					/////////////////////////////
				
					if(doInterference) ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
					else               ZPoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
					h1Map["hMass_truth_template_Zprime_SSM"+massName]->Fill(mass*GeV2TeV,wgt*ZPoverSM_weight); // need to fluctuate this later
				}

				// for(double gN=gNXXmin ; gN<=gNXXmax ; gN+=dgNXX)
				// for(unsigned int gNbin=1 ; gNbin<=npowerbins ; gNbin++)
				// for(unsigned int gNbin=1 ; gNbin<=ngNbinstotal+1 ; gNbin++) // go up to the uoverflow bin and take its lower edge
				for(double gN=gNXXmin ; gN<=gNXXmax ; gN+=dgNXX)
				{
					// double gN = gNaxis->GetBinLowEdge(gNbin);
				
					if(doFullKKtemplates)
					{
						TH2* hTmp = h2Map["h"+tsgN+"Mass_truth_template_KK"+massName];
						if(gN<=hTmp->GetYaxis()->GetBinUpEdge(hTmp->GetNbinsY()))
						{
							/////////////////////////////
							setCouplingsScale(true); ////
							double gRe = (dog4) ? sqrt(sqrt(gN)) : sqrt(gN);
							double gIm = 0.; ////////////
							setFgGKK(gRe,gIm); //////////
							setFgZKK(gRe,gIm); //////////
							/////////////////////////////
						
							if(doInterference) KKoverSM_weight = weightKK(truth_cost,truth_s,truth_idIn,idOut);
							else               KKoverSM_weight = weightKKnoSM(truth_cost,truth_s,truth_idIn,idOut);
							if(KKoverSM_weight>0.)
							{
								h2Map["h"+tsgN+"Mass_truth_template_KK"+massName]->Fill(mass*GeV2TeV, gN, wgt*KKoverSM_weight);
							}
						}
					}
					if(doFullZPtemplates)
					{
						/////////////////////////////
						setCouplingsScale(true); ////
						double gRe = (dog4) ? sqrt(sqrt(gN)) : sqrt(gN);
						double gIm = 0.; ////////////
						setFgZP(gRe,gIm); ///////////
						/////////////////////////////
						
						if(doInterference) ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
						else               ZPoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
						if(ZPoverSM_weight>0.)
						{
							h2Map["h"+tsgN+"Mass_truth_template_Zprime_SSM"+massName]->Fill(mass*GeV2TeV, gN, wgt*ZPoverSM_weight);
						}
					}
				}
			}
			
			
			/////////////////////////////
			if(doSingleMass) break; /////
			/////////////////////////////
		}
		
		if(recon_all_isValid)
		{
			if(isMuons)
			{
				ileptonrec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				ialeptonrec = (ileptonrec==0) ? 1 : 0;
			}
			else
			{
				ileptonrec  = 0;
				ialeptonrec = 1;
			}

			/*
			tlvtmp->SetPtEtaPhiM(recon_all_pt->at(ileptonrec), recon_all_eta->at(ileptonrec), recon_all_phi->at(ileptonrec), leptonMass);
			dr1 = fkinematics::dR(tlvtmp,tlvleptontrua);
			dr2 = fkinematics::dR(tlvtmp,tlvleptontrub);
			ileptonrec  = (dr1<=dr2) ? ileptonrec : ialeptonrec;
			ialeptonrec = (ileptonrec==0) ? 1 : 0;
			// if(dr1>dr2) _WARNING("dr1(recA,truA) > dr2(recA,truB)");
			*/
			
			tlvleptonreca->SetPtEtaPhiM(recon_all_pt->at(ileptonrec),  recon_all_eta->at(ileptonrec),  recon_all_phi->at(ileptonrec),  leptonMass);
			tlvleptonrecb->SetPtEtaPhiM(recon_all_pt->at(ialeptonrec), recon_all_eta->at(ialeptonrec), recon_all_phi->at(ialeptonrec), leptonMass);
			(*tv3mureca) = tlvleptonreca->Vect();
			(*tv3murecb) = tlvleptonrecb->Vect();
			tlvleptonrecaBoosted = fkinematics::Boost(tlvleptonreca,tlvleptonrecb,tlvleptonreca);
			tlvleptonrecbBoosted = fkinematics::Boost(tlvleptonreca,tlvleptonrecb,tlvleptonrecb);
			(*tv3murecaBoosted) = tlvleptonrecaBoosted->Vect();
			(*tv3murecbBoosted) = tlvleptonrecbBoosted->Vect();
		}
		
		_DEBUG("");
		
		if(recon_all_isValid  &&  ileptonrec>=0. && ialeptonrec>=0.  &&  ileptonrec!=ialeptonrec)
		{
			ca = recon_all_charge->at(ileptonrec);
			cb = recon_all_charge->at(ialeptonrec);
			// if(ca*cb>=0.) _WARNING("ca*cb>=0");
			mass          = fkinematics::imass(tlvleptonreca,tlvleptonrecb);
		
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(mass>=70. && mass<=110. && (tsMCname=="DYmumu" || tsMCname=="DYee")) nZpeak += event_weight*wgt; ////////////////
			if(mass>=70. && mass<=110. && (tsMCname=="DYmumu" || tsMCname=="DYee")) nZpeakNoPU += event_weight_nopileup*wgt; ///
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
			_DEBUG("");
			
			for(double M=mXXmin ; M<=mXXmax && (tsMCname=="DYmumu" || tsMCname=="DYee") ; M+=dmXX)
			{
				//////////////////////////////////////
				if(doSingleMass) M = singleMass; /////
				//////////////////////////////////////
			
				//////////////////////////////
				// propagate the KK mass /////
				setKKmass(M); ////////////////
				setZPmass(M); ////////////////
				//////////////////////////////
				TString massName = (TString)_s(M);
				TMapTSP2TH2::iterator ii=h2Map.begin();
				TAxis*  gNaxis = (TAxis*)ii->second->GetYaxis();
				// TAxis* gNaxis = (TAxis*)h2Map["h"+tsgN+"Mass_template_ZP"+massName]->GetYaxis();
				
				_DEBUG("");
				
				if(doFullKKtemplates)
				{
					/////////////////////////////
					setCouplingsScale(false); ///
					resetfgGKK(); ///////////////
					resetfgZKK(); ///////////////
					/////////////////////////////
				
					if(doInterference) KKoverSM_weight = weightKK(truth_cost,truth_s,truth_idIn,idOut);
					else               KKoverSM_weight = weightKKnoSM(truth_cost,truth_s,truth_idIn,idOut);
					if(KKoverSM_weight>0.) h1Map["hMass_template_KK"+massName]->Fill(mass*GeV2TeV,wgt*event_weight*KKoverSM_weight); // need to fluctuate this later
				}
				if(doFullZPtemplates)
				{
					/////////////////////////////
					setCouplingsScale(false); ///
					resetfgZP(); ////////////////
					/////////////////////////////
				
					if(doInterference) ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
					else               ZPoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
					if(ZPoverSM_weight>0.) h1Map["hMass_template_Zprime_SSM"+massName]->Fill(mass*GeV2TeV,wgt*event_weight*ZPoverSM_weight); // need to fluctuate this later
				}
				
				
				_DEBUG("");
				
				// for(double gN=gNXXmin ; gN<=gNXXmax ; gN+=dgNXX)
				// for(unsigned int gNbin=1 ; gNbin<=npowerbins ; gNbin++)
				// for(unsigned int gNbin=1 ; gNbin<=ngNbinstotal+1 ; gNbin++) // go up to the uoverflow bin and take its lower edge
				for(double gN=gNXXmin ; gN<=gNXXmax ; gN+=dgNXX)
				{
					// double gN = gNaxis->GetBinLowEdge(gNbin);
					
					if(doFullKKtemplates)
					{
						TH2* hTmp = h2Map["h"+tsgN+"Mass_template_KK"+massName];
						if(gN<=hTmp->GetYaxis()->GetBinUpEdge(hTmp->GetNbinsY()))
						{
							////////////////////////////////
							setCouplingsScale(true); ///////
							double gRe = (dog4) ? sqrt(sqrt(gN)) : sqrt(gN);
							double gIm = 0.; ///////////////
							setFgGKK(gRe,gIm); /////////////
							setFgZKK(gRe,gIm); /////////////
							////////////////////////////////
							
							if(doInterference) KKoverSM_weight = weightKK(truth_cost,truth_s,truth_idIn,idOut);
							else               KKoverSM_weight = weightKKnoSM(truth_cost,truth_s,truth_idIn,idOut);
							if(KKoverSM_weight>0.)
							{
								h2Map["h"+tsgN+"Mass_template_KK"+massName]->Fill(mass*GeV2TeV, gN, wgt*event_weight*KKoverSM_weight);
							}
						}
					}
					if(doFullZPtemplates)
					{
						////////////////////////////////
						setCouplingsScale(true); ///////
						double gRe = (dog4) ? sqrt(sqrt(gN)) : sqrt(gN);
						double gIm = 0.; ///////////////
						setFgZP(gRe,gIm); //////////////
						////////////////////////////////
						
						if(doInterference) ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
						else               ZPoverSM_weight = weightZPnoSM(truth_cost,truth_s,truth_idIn,idOut);
						if(ZPoverSM_weight>0.)
						{
							h2Map["h"+tsgN+"Mass_template_Zprime_SSM"+massName]->Fill(mass*GeV2TeV, gN, wgt*event_weight*ZPoverSM_weight);
						}
					}
				}
				
				////////////////////////////
				if(doSingleMass) break; ////
				////////////////////////////
			}
			
			_DEBUG("");
			
			h1Map["hMass_"+tsMCname]->Fill(mass*GeV2TeV,wgt*weight_dy);
			
			_DEBUG("");
			
			if(doOfficialZP && (tsMCname=="DYmumu" || tsMCname=="DYee"))
			{
				_DEBUG("");
			
				/////////////////////////////
				setCouplingsScale(false); ///
				resetfgZP(); ////////////////
				/////////////////////////////
				
				for(double M=1000. ; M<=2000. ; M+=250.)
				{
					if(!isMC11c && M==1250) continue;
				
					/////////////////
					setZPmass(M); ///
					/////////////////
					
					TString tsMZP = (TString)_s(M);
					ZPoverSM_weight = weightZP(truth_cost,truth_s,truth_idIn,idOut);
					h1Map["hMass_Zprime_SSM"+tsMZP+"_template"]->Fill(mass*GeV2TeV,wgt*weight_dy*ZPoverSM_weight);
				}
				_DEBUG("");
			}
			_DEBUG("");
		}
	}
}

void init(TTree* t=NULL, TString name="")
{
	_DEBUG("init");
	tree = t;
	setMCbranches();
	_DEBUG("successfully fetched MC tree");
}

void writeTemplates()
{
	_DEBUG("writeTemplates");
	
	// remember old dir
	TDirectory* olddir = gDirectory;

	if(doGrid)
	{
		TString fTemplatesName = "template"+(TString)_s(singleMass)+"GeV.root";
		TFile* fTemplates = new TFile(fTemplatesName, "RECREATE");

		olddir->cd();

		TObjArray* templates_KK         = new TObjArray;
		TObjArray* templates_KK_truth   = new TObjArray;
		TObjArray* templates2d_KK       = new TObjArray;
		TObjArray* templates2d_KK_truth = new TObjArray;

		TObjArray* templates_ZP         = new TObjArray;
		TObjArray* templates_ZP_truth   = new TObjArray;
		TObjArray* templates2d_ZP       = new TObjArray;
		TObjArray* templates2d_ZP_truth = new TObjArray;

		///////////////////////////////////////
		double M = singleMass; ////////////////
		TString massName = (TString)_s(M); ////
		///////////////////////////////////////
		
		if(doFullKKtemplates)
		{
			templates_KK->Add( (TH1D*)h1Map["hMass_template_KK"+massName]->Clone("") );
			if(doTruth) templates_KK_truth->Add( (TH1D*)h1Map["hMass_truth_template_KK"+massName]->Clone("") );
			templates2d_KK->Add( (TH2D*)h2Map["h"+tsgN+"Mass_template_KK"+massName]->Clone("") );
			if(doTruth)
			{
				templates2d_KK_truth->Add( (TH2D*)h2Map["h"+tsgN+"Mass_truth_template_KK"+massName]->Clone("") );
			}
	
			fTemplates->cd();

			templates_KK->SetOwner(kTRUE);
			templates_KK->Write("templateKK", TObject::kSingleKey);
			if(doTruth) templates_KK_truth->SetOwner(kTRUE);
			if(doTruth) templates_KK_truth->Write("truth_templateKK", TObject::kSingleKey);
			templates2d_KK->SetOwner(kTRUE);
			templates2d_KK->Write("template2dKK", TObject::kSingleKey);
			if(doTruth) templates2d_KK_truth->SetOwner(kTRUE);
			if(doTruth) templates2d_KK_truth->Write("truth_template2dKK", TObject::kSingleKey);
		}
		if(doFullZPtemplates)
		{
			templates_ZP->Add( (TH1D*)h1Map["hMass_template_Zprime_SSM"+massName]->Clone("") );
			if(doTruth) templates_ZP_truth->Add( (TH1D*)h1Map["hMass_truth_template_Zprime_SSM"+massName]->Clone("") );
			templates2d_ZP->Add( (TH2D*)h2Map["h"+tsgN+"Mass_template_Zprime_SSM"+massName]->Clone("") );
			if(doTruth)
			{
				templates2d_ZP_truth->Add( (TH2D*)h2Map["h"+tsgN+"Mass_truth_template_Zprime_SSM"+massName]->Clone("") );
			}

			fTemplates->cd();

			templates_ZP->SetOwner(kTRUE);
			templates_ZP->Write("templateZP", TObject::kSingleKey);
			if(doTruth) templates_ZP_truth->SetOwner(kTRUE);
			if(doTruth) templates_ZP_truth->Write("truth_templateZP", TObject::kSingleKey);
			templates2d_ZP->SetOwner(kTRUE);
			templates2d_ZP->Write("template2dZP", TObject::kSingleKey);
			if(doTruth) templates2d_ZP_truth->SetOwner(kTRUE);
			if(doTruth) templates2d_ZP_truth->Write("truth_template2dZP", TObject::kSingleKey);
		}

		olddir->cd();

		TH1D* hDYrec = (TH1D*)h1Map["hMass_DY"+channel]->Clone("");
		fTemplates->cd();
		hDYrec->Write();
		TH1D* hDYtru = NULL;
		if(doTruth) { olddir->cd(); hDYtru = (TH1D*)h1Map["hMass_DY"+channel+"_truth"]->Clone("");}
		if(doTruth) { fTemplates->cd(); hDYtru->Write();}

		TString templateFname = (TString)fTemplates->GetName();
		_INFO("write -> "+(string)templateFname);
		fTemplates->Write();
		fTemplates->Close();
		_INFO("wrote -> "+(string)templateFname);

		/////////////
		return; /////
		/////////////
	}




	if(doFullKKtemplates)
	{
		TString fKKTemplatesName = "plots/KK_2dtemplates"+fileNmaeSuffix()+".root";
		if(doGrid) fKKTemplatesName = "KK_2dtemplates.root";
		TFile* fKKTemplates = new TFile(fKKTemplatesName, "RECREATE");
		
		olddir->cd();
		
		TObjArray* templates_KK         = new TObjArray;
		TObjArray* templates_KK_truth   = new TObjArray;
		TObjArray* templates2d_KK       = new TObjArray;
		TObjArray* templates2d_KK_truth = new TObjArray;

		for(double M=mXXmin ; M<=mXXmax ; M+=dmXX)
		{
			//////////////////////////////////////
			if(doSingleMass) M = singleMass; /////
			//////////////////////////////////////
		
			TString massName = (TString)_s(M);
			templates_KK->Add( (TH1D*)h1Map["hMass_template_KK"+massName]->Clone("") );
			if(doTruth) templates_KK_truth->Add( (TH1D*)h1Map["hMass_truth_template_KK"+massName]->Clone("") );
			templates2d_KK->Add( (TH2D*)h2Map["h"+tsgN+"Mass_template_KK"+massName]->Clone("") );
			if(doTruth)
			{
				templates2d_KK_truth->Add( (TH2D*)h2Map["h"+tsgN+"Mass_truth_template_KK"+massName]->Clone("") );
			}
			
			/////////////////////////////
			if(doSingleMass) break; /////
			/////////////////////////////
		}
		
		fKKTemplates->cd();
	
		templates_KK->SetOwner(kTRUE);
		templates_KK->Write("template", TObject::kSingleKey);
		if(doTruth) templates_KK_truth->SetOwner(kTRUE);
		if(doTruth) templates_KK_truth->Write("truth_template", TObject::kSingleKey);
		templates2d_KK->SetOwner(kTRUE);
		templates2d_KK->Write("template2d", TObject::kSingleKey);
		if(doTruth) templates2d_KK_truth->SetOwner(kTRUE);
		if(doTruth) templates2d_KK_truth->Write("truth_template2d", TObject::kSingleKey);
		
		
		olddir->cd();
		TH1D* hDYrec = (TH1D*)h1Map["hMass_DY"+channel]->Clone("");
		fKKTemplates->cd(); hDYrec->Write();
		TH1D* hDYtru = NULL;
		if(doTruth) {olddir->cd(); hDYtru = (TH1D*)h1Map["hMass_DY"+channel+"_truth"]->Clone("");}
		if(doTruth) {fKKTemplates->cd(); hDYtru->Write();}
		
		
		if(doOfficialZP)
		{
			TH1D* hZPofficial = NULL;
			for(double M=1000. ; M<=2000. ; M+=250.)
			{
				if(!isMC11c && M==1250) continue;
			
				TString tsMZP = (TString)_s(M);
				olddir->cd();
				hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP]->Clone("");
				fKKTemplates->cd();
				hZPofficial->Write();
				
				if(doTruth)
				{
					olddir->cd();
					hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP+"_truth"]->Clone("");
					fKKTemplates->cd();
					hZPofficial->Write();
				}
				
				olddir->cd();
				hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP+"_template"]->Clone("");
				fKKTemplates->cd();
				hZPofficial->Write();
				
				if(doTruth)
				{
					olddir->cd();
					hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP+"_template_truth"]->Clone("");
					fKKTemplates->cd();
					hZPofficial->Write();
				}
			}
		}
		TString templateFname = (TString)fKKTemplates->GetName();
		_INFO("write -> "+(string)templateFname);
		fKKTemplates->Write();
		fKKTemplates->Close();
		_INFO("wrote -> "+(string)templateFname);
	}
	
	if(doFullZPtemplates)
	{
		TString fZPTemplatesName = "plots/ZP_2dtemplates"+fileNmaeSuffix()+".root";
		if(doGrid) fZPTemplatesName = "ZP_2dtemplates.root";
		TFile* fZPTemplates = new TFile(fZPTemplatesName, "RECREATE");
		
		olddir->cd();
		
		TObjArray* templates_ZP         = new TObjArray;
		TObjArray* templates_ZP_truth   = new TObjArray;
		TObjArray* templates2d_ZP       = new TObjArray;
		TObjArray* templates2d_ZP_truth = new TObjArray;

		for(double M=mXXmin ; M<=mXXmax ; M+=dmXX)
		{
			//////////////////////////////////////
			if(doSingleMass) M = singleMass; /////
			//////////////////////////////////////
		
			TString massName = (TString)_s(M);
			templates_ZP->Add( (TH1D*)h1Map["hMass_template_Zprime_SSM"+massName]->Clone("") );
			if(doTruth) templates_ZP_truth->Add( (TH1D*)h1Map["hMass_truth_template_Zprime_SSM"+massName]->Clone("") );
			templates2d_ZP->Add( (TH2D*)h2Map["h"+tsgN+"Mass_template_Zprime_SSM"+massName]->Clone("") );
			if(doTruth)
			{
				templates2d_ZP_truth->Add( (TH2D*)h2Map["h"+tsgN+"Mass_truth_template_Zprime_SSM"+massName]->Clone("") );
			}
			
			/////////////////////////////
			if(doSingleMass) break; /////
			/////////////////////////////
		}
		
		fZPTemplates->cd();
	
		templates_ZP->SetOwner(kTRUE);
		templates_ZP->Write("template", TObject::kSingleKey);
		if(doTruth) templates_ZP_truth->SetOwner(kTRUE);
		if(doTruth) templates_ZP_truth->Write("truth_template", TObject::kSingleKey);
		templates2d_ZP->SetOwner(kTRUE);
		templates2d_ZP->Write("template2d", TObject::kSingleKey);
		if(doTruth) templates2d_ZP_truth->SetOwner(kTRUE);
		if(doTruth) templates2d_ZP_truth->Write("truth_template2d", TObject::kSingleKey);
		
		olddir->cd();
		TH1D* hDYrec = (TH1D*)h1Map["hMass_DY"+channel]->Clone("");
		fZPTemplates->cd(); hDYrec->Write();
		TH1D* hDYtru = NULL;
		if(doTruth) {olddir->cd(); hDYtru = (TH1D*)h1Map["hMass_DY"+channel+"_truth"]->Clone("");}
		if(doTruth) {fZPTemplates->cd(); hDYtru->Write();}
		
		if(doOfficialZP)
		{
			TH1D* hZPofficial = NULL;
			for(double M=1000. ; M<=2000. ; M+=250.)
			{
				if(!isMC11c && M==1250) continue;
			
				TString tsMZP = (TString)_s(M);
				olddir->cd();
				hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP]->Clone("");
				fZPTemplates->cd();
				hZPofficial->Write();
				
				if(doTruth)
				{
					olddir->cd();
					hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP+"_truth"]->Clone("");
					fZPTemplates->cd();
					hZPofficial->Write();
				}
				
				olddir->cd();
				hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP+"_template"]->Clone("");
				fZPTemplates->cd();
				hZPofficial->Write();
				
				if(doTruth)
				{
					olddir->cd();
					hZPofficial = (TH1D*)h1Map["hMass_Zprime_SSM"+tsMZP+"_template_truth"]->Clone("");
					fZPTemplates->cd();
					hZPofficial->Write();
				}
			}
		}
		TString templateFname = (TString)fZPTemplates->GetName();
		_INFO("write -> "+(string)templateFname);
		fZPTemplates->Write();
		fZPTemplates->Close();
		_INFO("wrote -> "+(string)templateFname);
	}
}

void monitor(TString name, Int_t entry, Int_t N)
{
	if(entry%printmod==0) cout << name << ": progress " << setprecision(2) << fixed << (float)entry/(float)N*100. << "%\r" << flush;
}

void runMCproc(TString mcName)
{
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		init(it->second);
				
		// tree->SetEventList(0);
		// tree->Draw(">>elist","recon_all_isValid==1");
		// elist = (TEventList*)gDirectory->Get("elist");
		// tree->SetEventList(elist);
		// TFile* fTmp = new TFile("tmp_"+it->first,"RECREATE");
		// TTree* treeTmp = tree->CopyTree("");
		// Double_t Nrec = elist->GetN();
		// Double_t Nrec1 = treeTmp->GetEntries();
		// Double_t Ntree = tree->GetEntries();
		// _INFO("Nrec="+_s(Nrec));
		// _INFO("Nrec1="+_s(Nrec1));
		// _INFO("Ntree="+_s(Ntree));
		// Int_t N = treeTmp->GetEntriesFast();
		
		Int_t N = tree->GetEntriesFast();
		_INFO((string)it->first+": starting ("+_s(N)+").");
		Int_t Npractice = 0;
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			// treeTmp->GetEntry(entry);
			
			Npractice++;
			
			//////////////////////////////////////////////////////////////////////////
			if(!truth_all_isValid)                                       continue; ///
			if(!recon_all_isValid && !doTruth)                           continue; ///
			hfill(mcName, getFlatLumiWeight(it->first)); /////////////////////////////		
			//////////////////////////////////////////////////////////////////////////
			
			monitor(mcName,entry,N);
		}		
		_INFO((string)it->first+": done ("+_s(Npractice)+").");
	}
}

void run(TString channelName="mm", TString gPower="g2", Bool_t doSigUp=0, Double_t Xmass=-1.)
{
	msglvl[DBG] = SILENT; // SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	_DEBUG("run");

	if(Xmass!=-1)
	{
		doSingleMass = true;
		singleMass   = Xmass;
		_INFO("Running with mass -> "+_s(singleMass));
	}
	
	///////////////////////////////////////////
	matchFlags(channelName,gPower,doSigUp); ///
	style(); //////////////////////////////////
	samples(); //////
	hbook(); ////////
	setSumW2(); /////
	/////////////////
	
	///////////////////////////////////////////////
	// theoretical stuff... ///////////////////////
	setFermions(); ////////////////////////////////
	setFixedWidth(false); /////////////////////////
	resetKKmass();/////////////////////////////////
	resetZPmass(); ////////////////////////////////
	resetfgZP(); //////////////////////////////////
	resetfgGKK(); /////////////////////////////////
	resetfgZKK(); /////////////////////////////////
	///////////////////////////////////////////////
	
	for(TMapiTS::iterator it=grpx_ordered.begin() ; it!=grpx_ordered.end() ; ++it)
	{
		int order    = it->first;
		TString name = it->second;

		_INFO((string)name+" -> starting");
		setMCtrees(name);
		runMCproc(name);
		_INFO((string)name+" -> finished");
	}
	
	// setMCtrees("DY"+channel);
	// runMCproc("DY"+channel);
	
	// finalize
	writeTemplates();
	
	_INFO("Done mass -> "+_s(singleMass));
	_INFO("nZpeakNoPU = "+_s(nZpeakNoPU));
	_INFO("nZpeak = "+_s(nZpeak));
}

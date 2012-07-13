#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/types.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
#include "../include/units.h"
#include "../include/enums.h"
#include "../src/AtlasStyle.C"

using namespace fkinematics;


void atlstyle()
{
	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("../src/AtlasStyle.C");
	SetAtlasStyle();
}


string dir = "/data/hod/2011/pythia8_ntuples_2012/";

Int_t printmod = 1000;

const unsigned int nMCs = 20; // 20;
// const char* vcMassBins[] = {"50M250",   "250M500",  "500M750",  "750M1000" , "1000M1250",
							// "1250M1500", "1500M1750","1750M2000","2000M2250","2250M2500",
							// "2500M2750","2750M3000","3000M3250","3250M3500","3500M3750",
							// "3750M4000","4000M4250","4250M4500","4500M4750","4750M5000"};
const char* vcMassBins[] = {"50M150",   "150M250",  "250M400",  "400M600" , "600M800",
							"800M1000",	"1000M1250","1250M1500","1500M1750","1750M2000",
							"2000M2250","2250M2500","2500M2750","2750M3000","3000M3250",
							"3250M3500","3500M3750","3750M4000","4000M4400","4400M5000"};
vector<TString> vsMassBins(vcMassBins,vcMassBins+nMCs);

TString mcname   = "";
TString massname = "";
TString channel  = "";
TString chlabel  = "";
Double_t mBSM    = 0.;
TString mBSMname = "";
Int_t runNum     = 0;
TString sRunNum  = "";
TString fullname = "";

TFile* file;
TTree* tree;
TMapTSP2TTREE treMap;
TMapTSTS      tre2nameMap;
TMapTSd       nEvetMap;
TMapTSd       sigmaMap;
TMapTSi       orderMap;
TMapTSP2TH1   h1Map;
TMapTSP2TH2   h2Map;
TMapdi        pTtoIndexMapTruth;
TLorentzVector* p3 = new TLorentzVector();
TLorentzVector* p4 = new TLorentzVector();
TLorentzVector* p5 = new TLorentzVector();
TVector3* qrkvec   = new TVector3;
TVector3*       tv3qa = new TVector3;
TLorentzVector* tlvqa = new TLorentzVector;
TLorentzVector* tlvqb = new TLorentzVector;
TLorentzVector* tlvqBoosted = new TLorentzVector;
TVector3*       tv3mua = new TVector3;
TLorentzVector* tlvmua = new TLorentzVector;
TLorentzVector* tlvmub = new TLorentzVector;
TLorentzVector* tlvmuaBoosted = new TLorentzVector;
TLorentzVector* tlvmubBoosted = new TLorentzVector;


//// for the trees
vector<double>* leptons_pt;
vector<double>* leptons_m;
vector<double>* leptons_eta;
vector<double>* leptons_phi;
vector<int>*    leptons_pdgId;
vector<double>* leptons_charge;

vector<double>* hardprocess_px;
vector<double>* hardprocess_py;
vector<double>* hardprocess_pz;
vector<double>* hardprocess_e;
vector<double>* hardprocess_pt;
vector<double>* hardprocess_m;
vector<double>* hardprocess_eta;
vector<double>* hardprocess_phi;
vector<int>*    hardprocess_pdgId;
vector<double>* hardprocess_charge;

vector<double>* partons_px;
vector<double>* partons_py;
vector<double>* partons_pz;
vector<double>* partons_e;
vector<double>* partons_pt;
vector<double>* partons_m;
vector<double>* partons_eta;
vector<double>* partons_phi;
vector<int>*    partons_pdgId;
vector<double>* partons_charge;

double truth_x1;
double truth_x2;
double truth_pdf1;
double truth_pdf2;
double truth_QFac;
double truth_Q2Fac;
double truth_QRen;
double truth_Q2Ren;
double truth_alphaS;
double truth_alphaEM;
double truth_y;
int truth_id1;
int truth_id2;
double truth_mHat;
double truth_m3Hat;
double truth_m4Hat;
double truth_sHat;
double truth_tHat;
double truth_uHat;
double truth_pTHat;
double truth_thetaHat;
double truth_phiHat;

//// for the analysis
int qhrdprc;
int aqhrdprc;
int lepton;
int alepton;
int quark;
int aquark;

int proccount(int& counter)
{
	_DEBUG("int proccount(int& counter)");
	counter = counter+1;
	return counter;
}

TString scounter(int counter)
{
	_DEBUG("TString scounter(int counter)");
	if(counter<10) return "0"+(TString)_s(counter);
	else           return (TString)_s(counter);
	return "XXX";
}

double getFlatLumiWeight(TString name)
{
	_DEBUG("double getFlatLumiWeight(TString name)");
	
	if(nEvetMap.find(name)==nEvetMap.end()) _FATAL("cannot find name="+(string)name+" in nEvetMap");
	if(sigmaMap.find(name)==sigmaMap.end()) _FATAL("cannot find name="+(string)name+" in sigmaMap");
	
	double N     = nEvetMap[name];
	double sigma = sigmaMap[name]*mb2fb;
	if(sigma==0.) _FATAL("sigma = 0 for name -> "+(string)name+" -> cannot calculate the luminosity weight");
	double Lmc   = N/sigma;
	double datalumi = 5.; // 1/fb
	return datalumi/Lmc;
}

double readSigma(string name)
{
	_DEBUG("double readSigma(string name)");
	string fname = dir+name+(string)sRunNum+".dat";
	ifstream* f = new ifstream(fname.c_str());
	if(!(*f)) _FATAL("Unable to open file "+fname);
	_INFO("reading: "+fname);
	double trash = 0.;
	double sigma = 0.;
	string strash = "";
	(*f) >> strash >> trash >> trash >> trash >> sigma;
	delete f;
	return sigma;
}

unsigned int readNevents(string name)
{
	_DEBUG("unsigned int readNevents(string name)");
	string fname = dir+name+(string)sRunNum+".dat";
	ifstream* f = new ifstream(fname.c_str());
	if(!(*f)) _FATAL("Unable to open file "+fname);
	_INFO("reading: "+fname);
	double trash = 0.;
	unsigned int events = 0;
	string strash = "";
	(*f) >> strash >> trash >> trash >> events;
	delete f;
	return events;
}

void fillMaps(TString prefix)
{
	_DEBUG("void fillMaps(TString prefix)");
	
	int counter = 0;
	for(unsigned int mc=0 ; mc<nMCs ; mc++)
	{
		nEvetMap.insert( make_pair(prefix+scounter(proccount(counter))+"_"+vsMassBins[counter]+sRunNum, readNevents((string)prefix+(string)vsMassBins[counter])) );
	}
	_DEBUG("Done: readNevents");
	
	counter = 0;
	for(unsigned int mc=0 ; mc<nMCs ; mc++)
	{
		sigmaMap.insert( make_pair(prefix+scounter(proccount(counter))+"_"+vsMassBins[counter]+sRunNum, readSigma((string)prefix+(string)vsMassBins[counter])) );
	}
	_DEBUG("Done: readSigma");
}

void setSigma()
{
	_DEBUG("void setSigma()");
	
	if     (mcname.Contains("DY"))  fillMaps("DY_mumu_");
	else if(mcname.Contains("ssm")) fillMaps("ZP_ssm_mBSM1000_mumu_");
	else if(mcname.Contains("psi")) fillMaps("ZP_psi_mBSM1000_mumu_");
	else if(mcname.Contains("chi")) fillMaps("ZP_chi_mBSM1000_mumu_");
	else if(mcname.Contains("eta")) fillMaps("ZP_eta_mBSM1000_mumu_");
	else if(mcname.Contains("KK"))  fillMaps("KK_mBSM1000_mumu_");
	else _FATAL("mcname = "+(string)mcname+", is unknown");
	
	for(TMapTSd::iterator it=sigmaMap.begin() ; it!=sigmaMap.end() ; ++it) _INFO("sample: "+(string)it->first+" -> "+_s(it->second)+" mb");
}

void clearTreeMaps()
{
	_DEBUG("void clearTreeMaps()");
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		if(it->second) delete it->second; // the trees take a lot of memory, delete them.
	}
	treMap.clear();
}

void setMCtree(TString fPath, TString name)
{
	_DEBUG("void setMCtree(TString fPath, TString name)");
	file = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
}

void setMCtrees()
{
	_DEBUG("void setMCtrees()");
	////////////////////
	clearTreeMaps(); ///
	////////////////////
	
	for(unsigned int mc=1 ; mc<=nMCs ; mc++)
	{
		TString massbin   = "_"+vsMassBins[mc-1];
		TString sumpleumber = (mc<10) ? "0"+(TString)_s(mc) : (TString)_s(mc);
		TString filename  = fullname+massbin+sRunNum+".root";
		TString name      = (mBSM>0.) ? mcname+mBSMname+channel+"_"+sumpleumber+massbin+sRunNum : mcname+channel+"_"+sumpleumber+massbin+sRunNum;
		setMCtree(dir+filename,name);
	}
}

void setMCbranches()
{
	_DEBUG("void setMCbranches()");

	leptons_pt = 0;
	leptons_m = 0;
	leptons_eta = 0;
	leptons_phi = 0;
	leptons_pdgId = 0;
	leptons_charge = 0;
	
	// hardprocess_px = 0;
	// hardprocess_py = 0;
	// hardprocess_pz = 0;
	// hardprocess_e = 0;
	// hardprocess_pt = 0;
	// hardprocess_m = 0;
	// hardprocess_eta = 0;
	// hardprocess_phi = 0;
	// hardprocess_pdgId = 0;
	// hardprocess_charge = 0;
	
	partons_px = 0;
	partons_py = 0;
	partons_pz = 0;
	partons_e = 0;
	partons_pt = 0;
	partons_m = 0;
	partons_eta = 0;
	partons_phi = 0;
	partons_pdgId = 0;
	partons_charge = 0;
	
	tree->SetBranchAddress("truth_all_mc_pt", &leptons_pt);
	tree->SetBranchAddress("truth_all_mc_m", &leptons_m);
	tree->SetBranchAddress("truth_all_mc_eta", &leptons_eta);
	tree->SetBranchAddress("truth_all_mc_phi", &leptons_phi);
	tree->SetBranchAddress("truth_all_mc_pdgId", &leptons_pdgId);
	tree->SetBranchAddress("truth_all_mc_charge", &leptons_charge);
	
	// tree->SetBranchAddress("truth_hardprocess_px",  &hardprocess_px);
	// tree->SetBranchAddress("truth_hardprocess_py",  &hardprocess_py);
	// tree->SetBranchAddress("truth_hardprocess_pz",  &hardprocess_pz);
	// tree->SetBranchAddress("truth_hardprocess_e",   &hardprocess_e);
	// tree->SetBranchAddress("truth_hardprocess_pt",  &hardprocess_pt);
	// tree->SetBranchAddress("truth_hardprocess_m",   &hardprocess_m);
	// tree->SetBranchAddress("truth_hardprocess_eta", &hardprocess_eta);
	// tree->SetBranchAddress("truth_hardprocess_phi", &hardprocess_phi);
	// tree->SetBranchAddress("truth_hardprocess_pdgId",  &hardprocess_pdgId);
	// tree->SetBranchAddress("truth_hardprocess_charge", &hardprocess_charge);
	
	tree->SetBranchAddress("truth_all_partons_mc_px", &partons_px);
	tree->SetBranchAddress("truth_all_partons_mc_py", &partons_py);
	tree->SetBranchAddress("truth_all_partons_mc_pz", &partons_pz);
	tree->SetBranchAddress("truth_all_partons_mc_e", &partons_e);
	tree->SetBranchAddress("truth_all_partons_mc_pt", &partons_pt);
	tree->SetBranchAddress("truth_all_partons_mc_m", &partons_m);
	tree->SetBranchAddress("truth_all_partons_mc_eta", &partons_eta);
	tree->SetBranchAddress("truth_all_partons_mc_phi", &partons_phi);
	tree->SetBranchAddress("truth_all_partons_mc_pdgId", &partons_pdgId);
	tree->SetBranchAddress("truth_all_partons_mc_charge", &partons_charge);
	
	tree->SetBranchAddress( "truth_x1", &truth_x1 );
	tree->SetBranchAddress( "truth_x2", &truth_x2 );
	tree->SetBranchAddress( "truth_pdf1", &truth_pdf1 );
	tree->SetBranchAddress( "truth_pdf2", &truth_pdf2 );
	tree->SetBranchAddress( "truth_QFac", &truth_QFac );
	tree->SetBranchAddress( "truth_Q2Fac", &truth_Q2Fac );
	tree->SetBranchAddress( "truth_QRen", &truth_QRen );
	tree->SetBranchAddress( "truth_Q2Ren", &truth_Q2Ren );
	tree->SetBranchAddress( "truth_alphaS", &truth_alphaS );
	tree->SetBranchAddress( "truth_alphaEM", &truth_alphaEM );
	tree->SetBranchAddress( "truth_y", &truth_y );
	tree->SetBranchAddress( "truth_id1", &truth_id1 );
	tree->SetBranchAddress( "truth_id2", &truth_id2 );
	tree->SetBranchAddress( "truth_mHat", &truth_mHat );
	tree->SetBranchAddress( "truth_m3Hat", &truth_m3Hat );
	tree->SetBranchAddress( "truth_m4Hat", &truth_m4Hat );
	tree->SetBranchAddress( "truth_sHat", &truth_sHat );
	tree->SetBranchAddress( "truth_tHat", &truth_tHat );
	tree->SetBranchAddress( "truth_uHat", &truth_uHat );
	tree->SetBranchAddress( "truth_pTHat", &truth_pTHat );
	tree->SetBranchAddress( "truth_thetaHat", &truth_thetaHat );
	tree->SetBranchAddress( "truth_phiHat", &truth_phiHat );

	_DEBUG("successfully read mc branches");
}

void hbook(TString name)
{
	_DEBUG("void hbook(TString name)");
	
	setLogBins(nlogptbins,logptmin,logptmax,logptbins);
	setLogBins(nlogqtbins,logqtmin,logqtmax,logqtbins);
	setLogBins(nloglimitimassbins, loglimitimassmin, loglimitimassmax, loglimitimassbins);
	setLogBins(nlogtheoryimassbins, logtheoryimassmin, logtheoryimassmax, logtheoryimassbins);
	setLogBins(nlogtheoryAFBimassbins, logtheoryAFBimassmin, logtheoryAFBimassmax, logtheoryAFBimassbins);
	h1Map.insert( make_pair("hMass"+name, new TH1D("hMass"+name, name+";m_{"+chlabel+"} GeV;Events", nlogtheoryimassbins,logtheoryimassbins)) );
	h1Map.insert( make_pair("hMassLinear"+name, new TH1D("hMassLinear"+name, name+";m_{"+chlabel+"} GeV;Events", 120,200.,1600)) );
	h1Map.insert( make_pair("hMassForwardHE"+name, new TH1D("hMassForwardHE"+name, name+";m_{"+chlabel+"} GeV;Forward Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassBackwardHE"+name, new TH1D("hMassBackwardHE"+name, name+";m_{"+chlabel+"} GeV;Backward Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassForwardCS"+name, new TH1D("hMassForwardCS"+name, name+";m_{"+chlabel+"} GeV;Forward Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassBackwardCS"+name, new TH1D("hMassBackwardCS"+name, name+";m_{"+chlabel+"} GeV;Backward Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassForwardQRK"+name, new TH1D("hMassForwardQRK"+name, name+";m_{"+chlabel+"} GeV;Forward Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassBackwardQRK"+name, new TH1D("hMassBackwardQRK"+name, name+";m_{"+chlabel+"} GeV;Backward Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassAFB_HE"+name, new TH1D("hMassAFB_HE"+name, name+";m_{"+chlabel+"} GeV;A_{FB}", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassAFB_CS"+name, new TH1D("hMassAFB_CS"+name, name+";m_{"+chlabel+"} GeV;A_{FB}", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	h1Map.insert( make_pair("hMassAFB_QRK"+name, new TH1D("hMassAFB_QRK"+name, name+";m_{"+chlabel+"} GeV;A_{FB}", nlogtheoryAFBimassbins,logtheoryAFBimassbins)) );
	// h1Map.insert( make_pair("hMass"+name, new TH1D("hMass"+name, name+";m_{"+chlabel+"} TeV;Events", 200,75.,7000. /*nloglimitimassbins,loglimitimassbins*/)) );
	h1Map.insert( make_pair("hQT"+name, new TH1D("hQT"+name, name+";Q_{T}^{"+chlabel+"} GeV;Events", nlogqtbins,logqtbins)) );
	h1Map.insert( make_pair("hyQ"+name, new TH1D("hyQ"+name, name+";y^{"+chlabel+"};Events", netaQbins,etaQmin,etaQmax)) );
	h1Map.insert( make_pair("hEtaSystem"+name, new TH1D("hEtaSystem"+name, name+";#eta^{System};Events", netaQbins,etaQmin,etaQmax)) );
	h1Map.insert( make_pair("hpTLeading"+name, new TH1D("hpTLeading"+name, name+";p_{T}^{Leading} GeV;Events", nlogptbins,logptbins)) );
	h1Map.insert( make_pair("hpTSubLeading"+name, new TH1D("hpTSubLeading"+name, name+";p_{T}^{SubLeading} GeV;Events", nlogptbins,logptbins)) );
	h1Map.insert( make_pair("hEtaLeading"+name, new TH1D("hEatLeading"+name, name+";#eta^{Leading};Events", nEtabins,Etamin,Etamax)) );
	h1Map.insert( make_pair("hEtaSubLeading"+name, new TH1D("hEtaSubLeading"+name, name+";#eta^{SubLeading};Events", nEtabins,Etamin,Etamax)) );
	h1Map.insert( make_pair("hBoostQRK_ALL"+name, new TH1D("hBoostQRK_ALL"+name, name+";y_{#mu#mu};Events", 100,-4.,+4.)) );
	h1Map.insert( make_pair("hBoostQRK_FLIP"+name, new TH1D("hBoostQRK_FLIP"+name, name+";y_{#mu#mu};Events", 100,-4.,+4.)) );
	h1Map.insert( make_pair("hBoostQRK"+name, new TH1D("hBoostQRK"+name, name+";y_{#mu#mu};P(y_{#mu#mu})", 100,-4.,+4.)) );
	
	h2Map.insert( make_pair("hMassCosThetaQRK"+name, new TH2D("hMassCosThetaQRK"+name, name+";m_{"+chlabel+"} GeV;cos#theta*;Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	h2Map.insert( make_pair("hMassCosThetaHE"+name, new TH2D("hMassCosThetaHE"+name, name+";m_{"+chlabel+"} GeV;cos#theta*;Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	h2Map.insert( make_pair("hMassCosThetaCS"+name, new TH2D("hMassCosThetaCS"+name, name+";m_{"+chlabel+"} GeV;cos#theta*;Events", nlogtheoryAFBimassbins,logtheoryAFBimassbins, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
}

void hfill(TString name, double wgt)
{
	_DEBUG("void hfill(TString name, double wgt)");
	
	// qhrdprc = (hardprocess_pdgId->at(0)>hardprocess_pdgId->at(1)) ? 0 : 1;
	// aqhrdprc = (qhrdprc==0) ? 1 : 0;
	
	lepton  = (leptons_pdgId->at(0)>leptons_pdgId->at(1)) ? 0 : 1;
	alepton = (lepton==0) ? 1 : 0;
	
	quark  = (partons_pdgId->at(0)>0) ? 0 : 1;
	aquark = (quark==0) ? 1 : 0;

	// the hard process
	// p3->SetPxPyPzE( hardprocess_px->at(qhrdprc),  hardprocess_py->at(qhrdprc),  hardprocess_pz->at(qhrdprc),  hardprocess_e->at(qhrdprc) );
	// p4->SetPxPyPzE( hardprocess_px->at(aqhrdprc), hardprocess_py->at(aqhrdprc), hardprocess_pz->at(aqhrdprc), hardprocess_e->at(aqhrdprc) );
	// p5->SetPxPyPzE( hardprocess_px->at(5),        hardprocess_py->at(5),        hardprocess_pz->at(5),        hardprocess_e->at(5) );
	
	// the muons
	tlvmua->SetPtEtaPhiM( leptons_pt->at(lepton),  leptons_eta->at(lepton),  leptons_phi->at(lepton),  leptons_m->at(lepton) );
	tlvmub->SetPtEtaPhiM( leptons_pt->at(alepton), leptons_eta->at(alepton), leptons_phi->at(alepton), leptons_m->at(alepton) );
	tlvmuaBoosted = Boost(tlvmua,tlvmub,tlvmua);
	tv3mua->SetPtEtaPhi(tlvmuaBoosted->Pt(),tlvmuaBoosted->Eta(),tlvmuaBoosted->Phi());

	// the quarks
	tlvqa->SetPxPyPzE( partons_px->at(quark),  partons_py->at(quark),  partons_pz->at(quark),  partons_e->at(quark) );
	tlvqb->SetPxPyPzE( partons_px->at(aquark), partons_py->at(aquark), partons_pz->at(aquark), partons_e->at(aquark) );
	qrkvec->SetXYZ(partons_px->at(quark),  partons_py->at(quark),  partons_pz->at(quark));
	tlvqBoosted = Boost(tlvqa,tlvqb,tlvqa);
	tv3qa->SetXYZ(tlvqBoosted->Px(),tlvqBoosted->Py(),tlvqBoosted->Pz());
	
	double c1          = leptons_charge->at(lepton);
	double c2          = leptons_charge->at(alepton);
	double cosThetaQRK = tv3qa->Dot((*tv3mua))/(tv3qa->Mag()*tv3mua->Mag());
	double mHat        = imass(tlvmua,tlvmub);
	double cosThetaCS  = cosThetaCollinsSoper(tlvmua,c1, tlvmub,c2);
	double cosThetaHE  = cosThetaBoost(tlvmua,c1, tlvmub,c2);
	double ysystem     = ySystem(tlvmua,tlvmub);
	double etasystem   = etaSystem(tlvmua,tlvmub);
	double qt          = QT(tlvmua,tlvmub);
	TVector3 boost     = (TVector3)systemBoostVector(tlvmua,tlvmub);
	double boostDotQrk = qrkvec->Dot(boost);
	
	h1Map["hMass"+name]->Fill(mHat,wgt);
	h1Map["hMassLinear"+name]->Fill(mHat,wgt);
	h1Map["hQT"+name]->Fill(qt,wgt);
	h1Map["hyQ"+name]->Fill(ysystem,wgt);
	h1Map["hEtaSystem"+name]->Fill(etasystem,wgt);
	h1Map["hpTLeading"+name]->Fill(leptons_pt->at(lepton),wgt);
	h1Map["hpTSubLeading"+name]->Fill(leptons_pt->at(alepton),wgt);
	h1Map["hEtaLeading"+name]->Fill(leptons_eta->at(lepton),wgt);
	h1Map["hEtaSubLeading"+name]->Fill(leptons_eta->at(alepton),wgt);
	if(boostDotQrk<=0.) h1Map["hBoostQRK_FLIP"+name]->Fill(ysystem,wgt);
	h1Map["hBoostQRK_ALL"+name]->Fill(ysystem,wgt);
	
	h2Map["hMassCosThetaQRK"+name]->Fill(mHat,cosThetaQRK,wgt);
	h2Map["hMassCosThetaHE"+name]->Fill(mHat,cosThetaHE,wgt);
	h2Map["hMassCosThetaCS"+name]->Fill(mHat,cosThetaCS,wgt);
	
	if(cosThetaHE<=0.)  h1Map["hMassBackwardHE"+name]->Fill(mHat,wgt);
	if(cosThetaHE>0.)   h1Map["hMassForwardHE"+name]->Fill(mHat,wgt);
	if(cosThetaCS<=0.)  h1Map["hMassBackwardCS"+name]->Fill(mHat,wgt);
	if(cosThetaCS>0.)   h1Map["hMassForwardCS"+name]->Fill(mHat,wgt);
	if(cosThetaQRK<=0.) h1Map["hMassBackwardQRK"+name]->Fill(mHat,wgt);
	if(cosThetaQRK>0.)  h1Map["hMassForwardQRK"+name]->Fill(mHat,wgt);
}

void postanalysis(TString name)
{
	_DEBUG("void postanalysis(TString name)");

	h1Map["hMassAFB_HE"+name]->SetMinimum(-1);
	h1Map["hMassAFB_HE"+name]->SetMaximum(+1);
	
	h1Map["hMassAFB_CS"+name]->SetMinimum(-1);
	h1Map["hMassAFB_CS"+name]->SetMaximum(+1);
	
	h1Map["hMassAFB_QRK"+name]->SetMinimum(-1);
	h1Map["hMassAFB_QRK"+name]->SetMaximum(+1);

	for(Int_t bin=1 ; bin<=h1Map["hMassAFB_HE"+name]->GetNbinsX() ; bin++)
	{
		Double_t Nf   = 0.;
		Double_t Nb   = 0.;
		Double_t N    = 0.;
		Double_t Afb  = 0.;
		Double_t dAfb = 0.;
		
		Nf = h1Map["hMassForwardHE"+name]->GetBinContent(bin);
		Nb = h1Map["hMassBackwardHE"+name]->GetBinContent(bin);
		N = Nf+Nb;
		if(N!=0.)
		{
			Afb = (Nf-Nb)/N;
			dAfb = sqrt((1.-Afb*Afb)/N);
			h1Map["hMassAFB_HE"+name]->SetBinContent(bin,Afb);
			h1Map["hMassAFB_HE"+name]->SetBinError(bin,dAfb);
		}
		
		Nf = h1Map["hMassForwardCS"+name]->GetBinContent(bin);
		Nb = h1Map["hMassBackwardCS"+name]->GetBinContent(bin);
		N = Nf+Nb;
		if(N!=0.)
		{
			Afb = (Nf-Nb)/N;
			dAfb = sqrt((1.-Afb*Afb)/N);
			h1Map["hMassAFB_CS"+name]->SetBinContent(bin,Afb);
			h1Map["hMassAFB_CS"+name]->SetBinError(bin,dAfb);
		}
		
		Nf = h1Map["hMassForwardQRK"+name]->GetBinContent(bin);
		Nb = h1Map["hMassBackwardQRK"+name]->GetBinContent(bin);
		N = Nf+Nb;
		if(N!=0.)
		{
			Afb = (Nf-Nb)/N;
			dAfb = sqrt((1.-Afb*Afb)/N);
			h1Map["hMassAFB_QRK"+name]->SetBinContent(bin,Afb);
			h1Map["hMassAFB_QRK"+name]->SetBinError(bin,dAfb);
		}
	}
	
	h1Map["hBoostQRK"+name]->Divide(h1Map["hBoostQRK_FLIP"+name],h1Map["hBoostQRK_ALL"+name],1.,1.);
}

bool dolog(TString hname, int axs)
{
	_DEBUG("bool dolog(TString hname, int axs)");

	if(hname.Contains("pT") && axs==1) return false; 
	if(hname.Contains("pT") && axs==2) return true; 
	if(hname.Contains("pT") && axs==3) return false; 
	
	if(hname.Contains("QT") && axs==1) return true; 
	if(hname.Contains("QT") && axs==2) return true;
	
	if(hname.Contains("Mass") && axs==1) return true;
	if(hname.Contains("Mass") && axs==2)
	{
		if(!hname.Contains("AFB") && !hname.Contains("CosTheta")) return true;
	}
	if(hname.Contains("Mass") && axs==3) return true;
	
	return false;
}

void setSumW2()
{
	_DEBUG("void setSumW2()");

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

void writeout(TString name)
{
	_DEBUG("void writeout(TString name)");

	TFile* outfile = new TFile("plots/"+name+sRunNum+".root","RECREATE");
	
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it)
	{
		outfile->cd();
		it->second->Write();
		TString hname = it->first;
		if(dolog(hname,1))
		{
			it->second->GetXaxis()->SetMoreLogLabels();
			it->second->GetXaxis()->SetNoExponent();
		}
		saveas(it->second, "plots/"+hname+sRunNum, dolog(hname,1), dolog(hname,2), dolog(hname,3));
	}
	
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it)
	{
		outfile->cd();
		it->second->Write();
		TString hname = it->first;
		if(dolog(hname,1))
		{
			it->second->GetXaxis()->SetMoreLogLabels();
			it->second->GetXaxis()->SetNoExponent();
			it->second->GetXaxis()->SetTitleOffset(1.);
			it->second->GetYaxis()->SetTitleOffset(1.);
			it->second->GetZaxis()->SetTitleOffset(1.);
		}
		saveas(it->second, "plots/"+hname+sRunNum, dolog(hname,1), dolog(hname,2), dolog(hname,3), false, "COLZ");
	}
	
	outfile->Write();
	outfile->Close();
	delete outfile;
}

void plotTheory(TString name)
{
	_DEBUG("void plotTheory(TString name)");
	
	TFile* fTheory = new TFile("/srv01/tau/hod/z0analysis-tests/z0analysis-r170/run/plots/theory_mass1000GeV_withpdf_histos.root","READ");
	
	TH1D* hmassTheory = NULL;
	TH1D* hAfbTheory  = NULL;

	TString model = "";
	if     (name.Contains("DY"))     model = "DY";
	else if(name.Contains("ZP_ssm")) model = "ZP";
	else if(name.Contains("ZP_psi")) model = "E6_psi";
	else if(name.Contains("ZP_chi")) model = "E6_chi";
	else if(name.Contains("ZP_eta")) model = "E6_eta";
	else if(name.Contains("KK"))     model = "KK";
	
	hmassTheory = (TH1D*)fTheory->Get("h1Sumq"+model)->Clone("hmassTheory");
	hAfbTheory  = (TH1D*)fTheory->Get("h1AfbSumq"+model)->Clone("hAfbTheory");
	
	hmassTheory->SetLineColor(kOrange+2);
	// for(Int_t b=1 ; b<=hmassTheory->GetNbinsX() ; b++) hmassTheory->SetBinContent(b, hmassTheory->GetBinContent(b)*hmassTheory->GetBinCenter(b));
	TCanvas* cnv_mass_ratio = hratio("cnv_mass_ratio", hmassTheory, h1Map["hMass"+name], NULL,"Ratio", true,true);
	saveas(cnv_mass_ratio,"plots/"+name+"_mass_ratio_withTheory"+sRunNum);
	
	TCanvas* cnv_afb = new TCanvas("cnv_afb","cnv_afb",600,400);
	cnv_afb->SetTicks(1,1);
	cnv_afb->SetLogx();
	cnv_afb->cd();
	cnv_afb->Draw();
	hAfbTheory->SetLineColor(kOrange+2);
	hAfbTheory->SetMinimum(-1.);
	hAfbTheory->SetMaximum(+1.);
	hAfbTheory->Draw();
	h1Map["hMassAFB_QRK"+name]->Draw("SAMES");
	saveas(cnv_afb,"plots/"+name+"_Afb_withTheory"+sRunNum);
}

void monitor(TString name, Int_t entry, Int_t N)
{
	if(entry%printmod==0) cout << name << ": progress " << setprecision(2) << fixed << (double)entry/(double)N*100. << "%\r" << flush;
}

void init(TTree* t=NULL)
{
	_DEBUG("void init(TTree* t=NULL)");
	tree = t;
	setMCbranches();
	_DEBUG("successfully fetched MC tree");
}

void loop(TString name)
{
	_DEBUG("void loop(TString name)");
	
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		init(it->second);
		
		Int_t N = tree->GetEntriesFast();
		_INFO((string)it->first+": starting ("+_s(N)+").");
		Int_t Npractice = 0;
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			
			Npractice++;
			
			//////////////////////////////////////////////
			double wgt = getFlatLumiWeight(it->first); ///
			hfill(name,wgt); /////////////////////////////
			//////////////////////////////////////////////
			
			monitor(name,entry,N);
		}		
		_INFO((string)it->first+": done ("+_s(Npractice)+").");
		
		///////////////////////
		delete it->second; ////
		///////////////////////
	}
}

void analysis(TString mc, TString ch, Double_t mbsm, Int_t runnum)
{
	msglvl[DBG] = SILENT; // SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	_DEBUG("void analysis(TString mc, TString ch)");
	
	atlstyle();
	// style();
	
	
	//////////////////////////////////////////////
	mcname   = mc+"_"; ///////////////////////////
	channel  = ch; ///////////////////////////////
	mBSM     = mbsm; /////////////////////////////
	mBSMname = "mBSM"+(TString)_s(mBSM)+"_"; /////
	runNum   = runnum; ///////////////////////////
	sRunNum  = "_"+(TString)_s(runnum); //////////
	/////////////////////////////////////////////////////////////////////
	chlabel   = (channel=="mumu") ? "#mu#mu" : "ee"; ////////////////////
	fullname  = mcname;                              ////////////////////
	fullname  += (mBSM>0.) ? mBSMname : "";          ////////////////////
	fullname  += channel;                            ////////////////////
	// fullname  += sRunNum;                            ////////////////////
	/////////////////////////////////////////////////////////////////////

	TString name = fullname;
	
	/////////////////
	setSigma(); /////
	hbook(name); ////
	setSumW2(); /////
	/////////////////
	
	_INFO((string)name+" -> starting");
	setMCtrees();
	loop(name);
	postanalysis(name);
	plotTheory(name);
	writeout(name);
	_INFO((string)name+" -> finished");
}




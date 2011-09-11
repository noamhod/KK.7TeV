#include "basicIncludes.h"

TFile* file;
TTree* tree;
TString fName;
TString tName;
TMapTSP2TCNV  cnvMap;
TMapTSP2TOBJ  oMap;
TMapTSP2TH1   h1Map;
TMapTSP2TH2   h2Map;
TMapSP2TGraph grMap;
TMapTSP2TLINE linMap;
TMapTSP2TTREE treMap;
TMapTSd       wgtMap;

Bool_t isMC=true;
Bool_t isZprime=false;
Bool_t dolog=true;
kinematics kin;
TLorentzVector* tlva   = new TLorentzVector;
TLorentzVector* tlvb   = new TLorentzVector;
TLorentzVector* tlvtmp = new TLorentzVector;
TVector3*       tv3a = new TVector3;
TVector3*       tv3b = new TVector3;


/////////////  MC  /////////////
bool truth_all_isValid;
vector<float>* truth_all_mc_pt;
vector<float>* truth_all_mc_m;
vector<float>* truth_all_mc_eta;
vector<float>* truth_all_mc_phi;
vector<int>*   truth_all_mc_status;
vector<int>*   truth_all_mc_barcode;
vector<int>*   truth_all_mc_pdgId;
vector<float>* truth_all_mc_charge;
float truth_all_Mhat;
float truth_all_CosThetaCS;
float truth_all_CosThetaHE;
float truth_all_ySystem;
float truth_all_QT;

vector<float>* truth_all_partons_mc_pt;
vector<float>* truth_all_partons_mc_m;
vector<float>* truth_all_partons_mc_eta;
vector<float>* truth_all_partons_mc_phi;
vector<int>*   truth_all_partons_mc_status;
vector<int>*   truth_all_partons_mc_barcode;
vector<int>*   truth_all_partons_mc_pdgId;
vector<float>* truth_all_partons_mc_charge;

bool recon_all_isValid;
vector<float>* recon_all_E;
vector<float>* recon_all_pt;
vector<float>* recon_all_m;
vector<float>* recon_all_eta;
vector<float>* recon_all_phi;
vector<float>* recon_all_px;
vector<float>* recon_all_py;
vector<float>* recon_all_pz;
vector<float>* recon_all_charge;
vector<float>* recon_all_y;
vector<int>*   recon_all_id;
vector<float>* recon_all_theta;
float recon_all_Mhat;
float recon_all_CosThetaCS;
float recon_all_CosThetaHE;
float recon_all_ySystem;
float recon_all_QT;
////////////////////////////////

///////////// data /////////////
vector<float>* E;
vector<float>* pt;
vector<float>* m;
vector<float>* eta;
vector<float>* phi;
vector<float>* px;
vector<float>* py;
vector<float>* pz;
vector<float>* charge;
vector<unsigned short>* allauthor;
vector<int>* author;
vector<float>* beta;
vector<float>* me_d0;
vector<float>* me_z0;
vector<float>* me_phi;
vector<float>* me_theta;
vector<float>* me_qoverp;
vector<float>* ie_d0;
vector<float>* ie_z0;
vector<float>* ie_phi;
vector<float>* ie_theta;
vector<float>* ie_qoverp;
float Mhat;
float CosThetaCS;
float CosThetaHE;
float Ysystem;
float Q_T;
float CosThetaDimu;
float ipTDiff;
float EtaSum;
////////////////////////////////



///////////// admin /////////////
void setisMC(Bool_t ismc, Bool_t iszprime)
{
	_DEBUG("setisMC");
	isMC = ismc;
	isZprime = iszprime;
}

void draw(TObject* tobj, TString oName, TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	_DEBUG("draw");

	TString cName = "c"+oName;
	cnvMap.insert( make_pair(oName, new TCanvas(cName,cName,600,400)) );
	if(logx) cnvMap[oName]->SetLogx();
	if(logy) cnvMap[oName]->SetLogy();
	cnvMap[oName]->cd();
	tobj->Draw(drawopt);
}

void setlogx(TH1* h)
{
	h->GetXaxis()->SetMoreLogLabels();
	h->GetXaxis()->SetNoExponent();
}

void setlogx(TH2* h)
{
	h->GetXaxis()->SetMoreLogLabels();
	h->GetXaxis()->SetNoExponent();
}

void drawon(TString existing_oName, TObject* tobj, TString drawopt="")
{
	_DEBUG("drawon");

	cnvMap[existing_oName]->cd();
	tobj->Draw(drawopt+" SAMES");
}

void save(TString oDir)
{
	_DEBUG("save");

	_INFO("save all canvases");
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		TString pName = oDir+"/"+it->first;
		it->second->SaveAs(pName+".png");
		it->second->SaveAs(pName+".eps");
		it->second->SaveAs(pName+".pdf");
		it->second->SaveAs(pName+".root");
		it->second->SaveAs(pName+".C");
	}
	
	_INFO("save all histograms (to a single .root file)");
	TString pName = "";
	if(isMC)
	{
		pName = (isZprime) ? oDir+"/Zpripe_histograms.root" : oDir+"/DY_histograms.root";
	}
	else
	{
		pName = oDir+"/datahistograms.root";
	}
	TFile* f = new TFile(pName,"RECREATE");
	f->cd();
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it) it->second->Write();
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it) it->second->Write();
	f->Write();
	f->Close();
	delete f;
}
////////////////////////////////


void settree(TString fPath, TString name, Double_t N, Double_t sigma)
{
	_DEBUG("settree");

	file = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	wgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
}

///////////////////////////
void settrees()
{
	_DEBUG("settrees");

	settree("../data/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 19999, 0.0086861*nb2fb);
	settree("../data/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 19996, 0.00041431*nb2fb);
	settree("../data/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 19993, 0.000067464*nb2fb);
	settree("../data/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 15994, 0.000011168*nb2fb);
	settree("../data/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 19992, 0.0000027277*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 19995, 0.00000091646*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 19993, 0.00000024942*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 19997, 0.000000076876*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 19993, 0.000000026003*nb2fb);
	settree("../data/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 19996, 0.000000015327*nb2fb);

	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 19999, 0.0086861*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 19996, 0.00041431*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 19993, 0.000067464*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 15994, 0.000011168*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 19992, 0.0000027277*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 19995, 0.00000091646*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 19993, 0.00000024942*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 19997, 0.000000076876*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 19993, 0.000000026003*nb2fb);
	// settree("/data/hod/pythia8_ntuples/ATLASZ0/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 19996, 0.000000015327*nb2fb);
	
	// settree("/tmp/hod/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 19999, 0.0086861*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 19996, 0.00041431*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 19993, 0.000067464*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 15994, 0.000011168*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 19992, 0.0000027277*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 19995, 0.00000091646*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 19993, 0.00000024942*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 19997, 0.000000076876*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 19993, 0.000000026003*nb2fb);
	// settree("/tmp/hod/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 19996, 0.000000015327*nb2fb);
}
///////////////////////////


void mcbranches()
{
	_DEBUG("mcbranches");

	truth_all_mc_pt = 0;
	truth_all_mc_m = 0;
	truth_all_mc_eta = 0;
	truth_all_mc_phi = 0;
	truth_all_mc_status = 0;
	truth_all_mc_barcode = 0;
	truth_all_mc_pdgId = 0;
	truth_all_mc_charge = 0;
	
	truth_all_partons_mc_pt = 0;
	truth_all_partons_mc_m = 0;
	truth_all_partons_mc_eta = 0;
	truth_all_partons_mc_phi = 0;
	truth_all_partons_mc_status = 0;
	truth_all_partons_mc_barcode = 0;
	truth_all_partons_mc_pdgId = 0;
	truth_all_partons_mc_charge = 0;

	recon_all_E = 0;
	recon_all_pt = 0;
	recon_all_m = 0;
	recon_all_eta = 0;
	recon_all_phi = 0;
	recon_all_px = 0;
	recon_all_py = 0;
	recon_all_pz = 0;
	recon_all_charge = 0;
	recon_all_y = 0;
	recon_all_id = 0;
	recon_all_theta = 0;
	
	E = 0;
	pt = 0;
	m = 0;
	eta = 0;
	phi = 0;
	px = 0;
	py = 0;
	pz = 0;
	charge = 0;
	allauthor = 0;
	author = 0;
	beta = 0;
	me_d0 = 0;
	me_z0 = 0;
	me_phi = 0;
	me_theta = 0;
	me_qoverp = 0;
	ie_d0 = 0;
	ie_z0 = 0;
	ie_phi = 0;
	ie_theta = 0;
	ie_qoverp = 0;

	tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
	tree->SetBranchAddress("truth_all_mc_pt", &truth_all_mc_pt);
	tree->SetBranchAddress("truth_all_mc_m", &truth_all_mc_m);
	tree->SetBranchAddress("truth_all_mc_eta", &truth_all_mc_eta);
	tree->SetBranchAddress("truth_all_mc_phi", &truth_all_mc_phi);
	tree->SetBranchAddress("truth_all_mc_status", &truth_all_mc_status);
	tree->SetBranchAddress("truth_all_mc_barcode", &truth_all_mc_barcode);
	tree->SetBranchAddress("truth_all_mc_pdgId", &truth_all_mc_pdgId);
	tree->SetBranchAddress("truth_all_mc_charge", &truth_all_mc_charge);
	tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
	tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
	tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
	tree->SetBranchAddress("truth_all_ySystem", &truth_all_ySystem);
	tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
	
	tree->SetBranchAddress("truth_all_partons_mc_pt", &truth_all_partons_mc_pt);
	tree->SetBranchAddress("truth_all_partons_mc_m", &truth_all_partons_mc_m);
	tree->SetBranchAddress("truth_all_partons_mc_eta", &truth_all_partons_mc_eta);
	tree->SetBranchAddress("truth_all_partons_mc_phi", &truth_all_partons_mc_phi);
	tree->SetBranchAddress("truth_all_partons_mc_status", &truth_all_partons_mc_status);
	tree->SetBranchAddress("truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	tree->SetBranchAddress("truth_all_partons_mc_pdgId", &truth_all_partons_mc_pdgId);
	tree->SetBranchAddress("truth_all_partons_mc_charge", &truth_all_partons_mc_charge);

	tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
	tree->SetBranchAddress("recon_all_E", &recon_all_E);
	tree->SetBranchAddress("recon_all_pt", &recon_all_pt);
	tree->SetBranchAddress("recon_all_m", &recon_all_m);
	tree->SetBranchAddress("recon_all_eta", &recon_all_eta);
	tree->SetBranchAddress("recon_all_phi", &recon_all_phi);
	tree->SetBranchAddress("recon_all_px", &recon_all_px);
	tree->SetBranchAddress("recon_all_py", &recon_all_py);
	tree->SetBranchAddress("recon_all_pz", &recon_all_pz);
	tree->SetBranchAddress("recon_all_charge", &recon_all_charge);
	tree->SetBranchAddress("recon_all_y", &recon_all_y);
	tree->SetBranchAddress("recon_all_id", &recon_all_id);
	tree->SetBranchAddress("recon_all_theta", &recon_all_theta);
	tree->SetBranchAddress("recon_all_Mhat", &recon_all_Mhat);
	tree->SetBranchAddress("recon_all_CosThetaCS", &recon_all_CosThetaCS);
	tree->SetBranchAddress("recon_all_CosThetaHE", &recon_all_CosThetaHE);
	tree->SetBranchAddress("recon_all_ySystem", &recon_all_ySystem);
	tree->SetBranchAddress("recon_all_QT", &recon_all_QT);
	
	_DEBUG("successfully read mc branches");
}

void databranches()
{
	_DEBUG("databranches");

	E = 0;
	pt = 0;
	m = 0;
	eta = 0;
	phi = 0;
	px = 0;
	py = 0;
	pz = 0;
	charge = 0;
	allauthor = 0;
	author = 0;
	beta = 0;
	me_d0 = 0;
	me_z0 = 0;
	me_phi = 0;
	me_theta = 0;
	me_qoverp = 0;
	ie_d0 = 0;
	ie_z0 = 0;
	ie_phi = 0;
	ie_theta = 0;
	ie_qoverp = 0;
	
	tree->SetBranchAddress("E", &E);
	tree->SetBranchAddress("pt", &pt);
	tree->SetBranchAddress("m", &m);
	tree->SetBranchAddress("eta", &eta);
	tree->SetBranchAddress("phi", &phi);
	tree->SetBranchAddress("px", &px);
	tree->SetBranchAddress("py", &py);
	tree->SetBranchAddress("pz", &pz);
	tree->SetBranchAddress("charge", &charge);
	tree->SetBranchAddress("allauthor", &allauthor);
	tree->SetBranchAddress("author", &author);
	tree->SetBranchAddress("beta", &beta);
	tree->SetBranchAddress("me_d0", &me_d0);
	tree->SetBranchAddress("me_z0", &me_z0);
	tree->SetBranchAddress("me_phi", &me_phi);
	tree->SetBranchAddress("me_theta", &me_theta);
	tree->SetBranchAddress("me_qoverp", &me_qoverp);
	tree->SetBranchAddress("ie_d0", &ie_d0);
	tree->SetBranchAddress("ie_z0", &ie_z0);
	tree->SetBranchAddress("ie_phi", &ie_phi);
	tree->SetBranchAddress("ie_theta", &ie_theta);
	tree->SetBranchAddress("ie_qoverp", &ie_qoverp);
	tree->SetBranchAddress("Mhat", &Mhat);
	tree->SetBranchAddress("CosThetaCS", &CosThetaCS);
	tree->SetBranchAddress("CosThetaHE", &CosThetaHE);
	tree->SetBranchAddress("Ysystem", &Ysystem);
	tree->SetBranchAddress("Q_T", &Q_T);
	tree->SetBranchAddress("CosThetaDimu", &CosThetaDimu);
	tree->SetBranchAddress("ipTDiff", &ipTDiff);
	tree->SetBranchAddress("EtaSum", &EtaSum);
	
	_DEBUG("successfully read data branches");
}

void hbook()
{
	_DEBUG("hbook");

	setLogBins(npbins,pmin,pmax,pbins);
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);

	h1Map.insert( make_pair("hMass", new TH1D("hMass",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMass"]);
	h1Map.insert( make_pair("hbetaZ", new TH1D("hbetaZ",";#beta_{Q}^{z};Events",200,-1.,1.)) );
	h1Map.insert( make_pair("hcosalpha_quark", new TH1D("hcosalpha_quark","#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q};#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q}/#beta_{Q}^{rec}p_{q};Events",50,-1.,1.)) );
	h1Map.insert( make_pair("hcosalpha_trumumu", new TH1D("hcosalpha_trumumu","#vec{#beta}_{Q}^{rec}#bullet#vec{#beta}_{Q}^{#mu#mu,tru};#vec{#beta}_{Q}^{rec}#bullet#vec{#beta}_{Q}^{#mu#mu,tru}/#beta_{Q}^{rec}#beta_{Q}^{#mu#mu,tru};Events",50,-1.,1.)) );
	h1Map.insert( make_pair("hcosalpha_truqqbar", new TH1D("hcosalpha_truqqbar","#vec{#beta}_{Q}^{rec}#bullet#vec{#beta}_{Q}^{q#bar{q}};#vec{#beta}_{Q}^{rec}#bullet#vec{#beta}_{Q}^{q#bar{q}}/#beta_{Q}^{rec}#beta_{Q}^{q#bar{q}};Events",50,-1.,1.)) );
	h1Map.insert( make_pair("hyQ", new TH1D("hyQ",";y_{Q};Events",100,-2.5,+2.5)) );
	h1Map.insert( make_pair("hyQabs", new TH1D("hyQabs",";|y_{Q}|;Events",50,0.,+2.5)) );
	
	h1Map.insert( make_pair("hprobabsyQ_quark_denominator", new TH1D("hprobabsyQ_quark_denominator",";|y_{Q}|;P(|y_{Q}|)",25,0.,+2.5)) );
	h1Map.insert( make_pair("hprobabsyQ_quark_ratio", new TH1D("hprobabsyQ_quark_ratio","P(|y_{Q}|)=#LT#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q}<0#GT/All;|y_{Q}|;P",25,0.,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_quark_denominator", new TH1D("hprobyQ_quark_denominator",";y_{Q};P(y_{Q})",16,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_quark_ratio", new TH1D("hprobyQ_quark_ratio","P(y_{Q})=#LT#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q}<0#GT/All;y_{Q};P",16,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_trumumu_denominator", new TH1D("hprobyQ_trumumu_denominator",";y_{Q};P(y_{Q})",16,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_trumumu_ratio", new TH1D("hprobyQ_trumumu_ratio","P(y_{Q})=#LT#vec{#beta}_{Q}^{rec}#bullet#vec{#beta}_{Q}^{#mu#mu,tru}<0#GT/All;y_{Q};P",16,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_truqqbar_denominator", new TH1D("hprobyQ_truqqbar_denominator",";y_{Q};P(y_{Q})",16,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_truqqbar_ratio", new TH1D("hprobyQ_truqqbar_ratio","P(y_{Q})=#LT#vec{#beta}_{Q}^{rec}#bullet#vec{#beta}_{Q}^{q#bar{q}}<0#GT/All;y_{Q};P",16,-2.5,+2.5)) );
	
	h1Map.insert( make_pair("hprobChargeFlip_p_denominator", new TH1D("hprobChargeFlip_p_denominator",";|p| GeV;P(|p|)",npbins,pbins)) );
	h1Map.insert( make_pair("hprobChargeFlip_p_ratio", new TH1D("hprobChargeFlip_p_ratio","P(|p|)=Charge Flip/All;|p| GeV;P",npbins,pbins)) );
	h1Map.insert( make_pair("hprobChargeFlip_pT_denominator", new TH1D("hprobChargeFlip_pT_denominator",";p_{T} GeV;P(p_{T})",npbins,pbins)) );
	h1Map.insert( make_pair("hprobChargeFlip_pT_ratio", new TH1D("hprobChargeFlip_pT_ratio","P(p_{T})=Charge Flips/All;p_{T} GeV;P",npbins,pbins)) );
	h1Map.insert( make_pair("hprobChargeFlip_y_denominator", new TH1D("hprobChargeFlip_y_denominator",";y;P(y)",25,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobChargeFlip_y_ratio", new TH1D("hprobChargeFlip_y_ratio","P(y)=Charge Flips/All;y;P",25,-2.5,+2.5)) );
	
	TString proc = "DYmumu";
	if(isZprime) proc = "Z' 1 TeV";
	h1Map.insert( make_pair("hforward_trumu_quark",new TH1D("hforward_trumu_quark",proc+" truth Forward events;m_{#mu#mu} GeV;N_{f}",nlogmassbins,logmassbins)));
	h1Map.insert( make_pair("hbackward_trumu_quark",new TH1D("hbackward_trumu_quark",proc+" truth Backward events;m_{#mu#mu} GeV;N_{b}",nlogmassbins,logmassbins)));
	h1Map.insert( make_pair("hAfb_trumu_quark",new TH1D("hAfb_trumu_quark",proc+" truth FB-asymmetry;m_{#mu#mu} GeV;A_{fb}",nlogmassbins,logmassbins)));
	
	h1Map.insert( make_pair("hEllipticity", new TH1D("hEllipticity","Uncorrected ellipticity;m_{#mu#mu} GeV;E_{#eta}",nlogmassbins,logmassbins)) );
	setlogx(h1Map["hEllipticity"]);
	for(int i=0 ; i<nlogmassbins ; i++)
	{
		TString tshName  = "";
		TString tshTitle = "";
		string  shName   = "";
		
		tshName = "hEllipticity_central_bin_"+(TString)_s(i+1);
		shName  = (string)tshName;
		tshTitle = "#eta_{central};#eta(#mu^{-});Events";
		h1Map.insert( make_pair(shName, new TH1D(tshName,tshTitle,netabins,etamin,etamax)) );
		
		tshName = "hEllipticity_sides_bin_"+(TString)_s(i+1);
		shName  = (string)tshName;
		tshTitle = "#eta_{sides};#eta(#mu^{-});Events";
		h1Map.insert( make_pair(shName, new TH1D(tshName,tshTitle,netabins,etamin,etamax)) );
	}
	
	h2Map.insert( make_pair("hMassCosThetaCS", new TH2D("hMassCosThetaCS",";m_{#mu#mu} GeV;cos(#theta*);Events",250,70.,2500., 50,-1.,+1)) );
	setlogx(h2Map["hMassCosThetaCS"]);
	linMap.insert( make_pair("hMassCosThetaCS_horline", new TLine(70.,0.,2500.,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassCosThetaCS_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],-1.,logmassbins[ms],+1.)) );
	}
	h2Map.insert( make_pair("hMassyQ", new TH2D("hMassyQ",";m_{#mu#mu} GeV;y_{Q};Events",250,70.,2500., 50,-2.5,+2.5)) );
	setlogx(h2Map["hMassyQ"]);
	linMap.insert( make_pair("hMassyQ_horline", new TLine(70.,0.,2500.,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassyQ_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],-2.5,logmassbins[ms],+2.5)) );
	}

	h2Map.insert( make_pair("hbetaZyQ", new TH2D("hbetaZyQ",";#beta_{Q}^{z};y_{Q};Events",50,-1.,+1, 50,-2.5,+2.5)) );
	h2Map.insert( make_pair("hbetaabsyQabs", new TH2D("hbetaabsyQabs",";|#beta_{Q}|;|y_{Q}|;Events",50,0.,+1., 50,0.,+2.5)) );
	h2Map.insert( make_pair("hyQCosThetaCS", new TH2D("hyQCosThetaCS",";y_{Q};cos(#theta*);Events",50,-2.5,+2.5, 50,-1.,+1)) );
	h2Map.insert( make_pair("hyQCosThetaCS_tru", new TH2D("hyQCosThetaCS_tru",";y_{Q};cos(#theta*);Events",25,-2.5,+2.5, 25,-1.,+1)) );
	h2Map.insert( make_pair("hyQCosThetaCS_acc", new TH2D("hyQCosThetaCS_acc","Acceptance;y_{Q};cos(#theta*)",25,-2.5,+2.5, 25,-1.,+1)) );
	h2Map.insert( make_pair("hbetaZyQtru", new TH2D("hbetaZyQtru",";#beta_{Q}^{z:tru};y_{Q}^{tru};Events",50,-1.,+1, 50,-2.5,+2.5)) );
	
	h2Map.insert( make_pair("hdRtru1dRtru2", new TH2D("hdRtru1dRtru2",";dR_{#mu rec 1}^{#mu tru};dR_{#mu rec 2}^{#mu tru};Events",50,0.,+5., 50,0.,+5.)) );
}

void hdraw()
{
	_DEBUG("hdraw");

	draw(h1Map["hMass"], "hMass", "", dolog, dolog);
	draw(h1Map["hbetaZ"], "hbetaZ");
	draw(h1Map["hcosalpha_quark"], "hcosalpha_quark", "", !dolog, dolog);
	draw(h1Map["hcosalpha_trumumu"], "hcosalpha_trumumu", "", !dolog, dolog);
	draw(h1Map["hcosalpha_truqqbar"], "hcosalpha_truqqbar", "", !dolog, dolog);
	draw(h1Map["hyQ"], "hyQ");
	draw(h1Map["hyQabs"], "hyQabs");

	h1Map["hprobabsyQ_quark_ratio"]->Divide(h1Map["hprobabsyQ_quark_denominator"]);
	h1Map["hprobabsyQ_quark_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobabsyQ_quark_ratio"]->SetMaximum(0.5);
	draw(h1Map["hprobabsyQ_quark_ratio"], "hprobabsyQ_quark_ratio", ""/*, !dolog, dolog*/);
	h1Map["hprobyQ_quark_ratio"]->Divide(h1Map["hprobyQ_quark_denominator"]);
	h1Map["hprobyQ_quark_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobyQ_quark_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobyQ_quark_ratio"], "hprobyQ_quark_ratio", ""/*, !dolog, dolog*/);
	h1Map["hprobyQ_trumumu_ratio"]->Divide(h1Map["hprobyQ_trumumu_denominator"]);
	h1Map["hprobyQ_trumumu_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobyQ_trumumu_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobyQ_trumumu_ratio"], "hprobyQ_trumumu_ratio", ""/*, !dolog, dolog*/);
	h1Map["hprobyQ_truqqbar_ratio"]->Divide(h1Map["hprobyQ_truqqbar_denominator"]);
	h1Map["hprobyQ_truqqbar_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobyQ_truqqbar_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobyQ_truqqbar_ratio"], "hprobyQ_truqqbar_ratio", ""/*, !dolog, dolog*/);
	
	h1Map["hprobChargeFlip_p_ratio"]->Divide(h1Map["hprobChargeFlip_p_denominator"]);
	h1Map["hprobChargeFlip_p_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobChargeFlip_p_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobChargeFlip_p_ratio"], "hprobChargeFlip_p_ratio", "");
	h1Map["hprobChargeFlip_pT_ratio"]->Divide(h1Map["hprobChargeFlip_pT_denominator"]);
	h1Map["hprobChargeFlip_pT_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobChargeFlip_pT_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobChargeFlip_pT_ratio"], "hprobChargeFlip_pT_ratio", "");
	h1Map["hprobChargeFlip_y_ratio"]->Divide(h1Map["hprobChargeFlip_y_denominator"]);
	h1Map["hprobChargeFlip_y_ratio"]->SetMinimum(1.e-5);
	h1Map["hprobChargeFlip_y_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobChargeFlip_y_ratio"], "hprobChargeFlip_y_ratio", "");
	
	h2Map["hyQCosThetaCS_acc"]->Divide(h2Map["hyQCosThetaCS_tru"]);
	h2Map["hyQCosThetaCS_acc"]->SetMinimum(0.);
	h2Map["hyQCosThetaCS_acc"]->SetMaximum(1.);
	draw(h2Map["hyQCosThetaCS_acc"], "hyQCosThetaCS_acc", "COLZ");
	
	draw(h2Map["hMassyQ"], "hMassyQ", "COLZ", dolog);
	drawon("hMassyQ", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQ", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	draw(h2Map["hMassCosThetaCS"], "hMassCosThetaCS", "COLZ", dolog);
	drawon("hMassCosThetaCS", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCS", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	
	draw(h2Map["hbetaabsyQabs"], "hbetaabsyQabs", "COLZ");
	draw(h2Map["hyQCosThetaCS"], "hyQCosThetaCS", "COLZ");
	draw(h2Map["hbetaZyQ"], "hbetaZyQ", "COLZ");
	draw(h2Map["hbetaZyQtru"], "hbetaZyQtru", "COLZ");
	
	draw(h2Map["hdRtru1dRtru2"], "hdRtru1dRtru2", "COLZ");
	
	for(Int_t b=1 ; b<=(Int_t)h1Map["hEllipticity"]->GetNbinsX() ; b++)
	{
		Double_t Nsides   = h1Map["hEllipticity_sides_bin_"+_s(b)]->Integral();
		Double_t Ncentral = h1Map["hEllipticity_central_bin_"+_s(b)]->Integral();
		Double_t Nall  = Ncentral+Nsides;
		Double_t Eeta  = (Nall!=0.) ? (Ncentral-Nsides)/(Ncentral+Nsides) : -999.;
		Double_t dEeta = (Nall!=0.) ? sqrt((1.-Eeta*Eeta)/Nall) : -999.;
		h1Map["hEllipticity"]->SetBinContent(b,Eeta);
		h1Map["hEllipticity"]->SetBinError(b,dEeta);
	}
	h1Map["hEllipticity"]->SetMinimum(-1.);
	h1Map["hEllipticity"]->SetMaximum(+1.);
	h1Map["hEllipticity"]->SetMarkerStyle(24);
	draw(h1Map["hEllipticity"], "hEllipticity", "e1x1", dolog);

	
	// Afb truth
	for(Int_t b=1 ; b<=(Int_t)h1Map["hAfb_trumu_quark"]->GetNbinsX() ; b++)
	{
		Double_t Nf = h1Map["hforward_trumu_quark"]->GetBinContent(b);
		Double_t Nb = h1Map["hbackward_trumu_quark"]->GetBinContent(b);
		Double_t N = Nf+Nb;
		if(N<=0.) continue;
		Double_t afb = (Nf-Nb)/N;
		h1Map["hAfb_trumu_quark"]->SetBinContent(b,afb);
		h1Map["hAfb_trumu_quark"]->SetBinError(b,TMath::Sqrt((1.-afb*afb)/N));
	}
	h1Map["hAfb_trumu_quark"]->GetXaxis()->SetMoreLogLabels(); 
	h1Map["hAfb_trumu_quark"]->GetXaxis()->SetNoExponent(); 
	h1Map["hAfb_trumu_quark"]->SetMinimum(-1.);
	h1Map["hAfb_trumu_quark"]->SetMaximum(+1.5);
	h1Map["hAfb_trumu_quark"]->SetMarkerStyle(24);
	draw(h1Map["hAfb_trumu_quark"], "hAfb_trumu_quark", "e1x1", dolog);
	//drawon("hAfb_trumu_quark", h1Map["hMass"]);
}

void hfill(Double_t wgt=1.)
{
	_DEBUG("hfill");

	float betax_rec   = -999.;	
	float betay_rec   = -999.;	
	float betaz_rec   = -999.;
	float betamag_rec = -999.;
			
	float betax_trumumu   = -999.;	
	float betay_trumumu   = -999.;	
	float betaz_trumumu   = -999.;	
	float betamag_trumumu = -999.;
		
	float betax_quarks   = -999.;	
	float betay_quarks   = -999.;	
	float betaz_quarks   = -999.;	
	float betamag_quarks = -999.;
	
	float cosalpha_quark    = -999.;
	float cosalpha_trumumu  = -999.;
	float cosalpha_truqqbar = -999.;
	float cosalpha_trumuon_quark = -999.;
	float betaztru          = -999.;
	
	float dr  = 0.;
	float dr1 = 0.;
	float dr2 = 0.;
	
	float mass       = 0.;
	float ca         = 0.;
	float cb         = 0.;
	float yQ         = 0.;
	float costhetaCS = 0.;
	
	int iquark    = -999;
	int imuontru  = -999;
	int iamuontru = -999;
	int imuonrec  = -999;
	int iamuonrec = -999;

	if(isMC)
	{
		if(truth_all_isValid)
		{
			if(recon_all_isValid)
			{
				betax_rec = kin.betaSystem(recon_all_px->at(0), recon_all_px->at(1), recon_all_E->at(0), recon_all_E->at(1));	
				betay_rec = kin.betaSystem(recon_all_py->at(0), recon_all_py->at(1), recon_all_E->at(0), recon_all_E->at(1));	
				betaz_rec = kin.betaSystem(recon_all_pz->at(0), recon_all_pz->at(1), recon_all_E->at(0), recon_all_E->at(1));
				betamag_rec = sqrt(betax_rec*betax_rec+betay_rec*betay_rec+betaz_rec*betaz_rec);
			}
			
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(0), truth_all_mc_eta->at(0), truth_all_mc_phi->at(0), muonMass);
			tlvb->SetPtEtaPhiM(truth_all_mc_pt->at(1), truth_all_mc_eta->at(1), truth_all_mc_phi->at(1), muonMass);
			betax_trumumu = kin.betaSystem(tlva->X(), tlvb->X(), tlva->E(), tlvb->E());	
			betay_trumumu = kin.betaSystem(tlva->Y(), tlvb->Y(), tlva->E(), tlvb->E());	
			betaz_trumumu = kin.betaSystem(tlva->Z(), tlvb->Z(), tlva->E(), tlvb->E());	
			betamag_trumumu = sqrt(betax_trumumu*betax_trumumu+betay_trumumu*betay_trumumu+betaz_trumumu*betaz_trumumu);
			
			tlva->SetPtEtaPhiM(truth_all_partons_mc_pt->at(0), truth_all_partons_mc_eta->at(0), truth_all_partons_mc_phi->at(0), muonMass);
			tlvb->SetPtEtaPhiM(truth_all_partons_mc_pt->at(1), truth_all_partons_mc_eta->at(1), truth_all_partons_mc_phi->at(1), muonMass);
			betax_quarks = kin.betaSystem(tlva->X(), tlvb->X(), tlva->E(), tlvb->E());	
			betay_quarks = kin.betaSystem(tlva->Y(), tlvb->Y(), tlva->E(), tlvb->E());	
			betaz_quarks = kin.betaSystem(tlva->Z(), tlvb->Z(), tlva->E(), tlvb->E());	
			betamag_quarks = sqrt(betax_quarks*betax_quarks+betay_quarks*betay_quarks+betaz_quarks*betaz_quarks);
			
			iquark   = (truth_all_partons_mc_pdgId->at(0)>0) ? 0 : 1;
			imuontru = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
			
			tv3b->SetXYZ(betax_rec, betay_rec, betaz_rec);
			if(recon_all_isValid)
			{
				iamuontru = (imuontru==0) ? 1 : 0;
				tlva->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),truth_all_mc_eta->at(imuontru),truth_all_mc_phi->at(imuontru),truth_all_mc_m->at(imuontru));
				tlvb->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru),truth_all_mc_eta->at(iamuontru),truth_all_mc_phi->at(iamuontru),truth_all_mc_m->at(iamuontru));
				yQ = kin.ySystem(tlva,tlvb);
				tv3a->SetPtEtaPhi(truth_all_partons_mc_pt->at(iquark), truth_all_partons_mc_eta->at(iquark), truth_all_partons_mc_phi->at(iquark));
				cosalpha_quark = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
				h1Map["hcosalpha_quark"]->Fill(cosalpha_quark,wgt);
				if(cosalpha_quark<=0.) h1Map["hprobyQ_quark_ratio"]->Fill(yQ/*truth_all_ySystem*/,wgt);
				if(cosalpha_quark<=0.) h1Map["hprobabsyQ_quark_ratio"]->Fill(fabs(yQ)/*truth_all_ySystem*/,wgt);
				// _INFO("cosalpha_quark = "+_s(cosalpha_quark));
				
				h1Map["hprobabsyQ_quark_denominator"]->Fill(fabs(yQ),wgt);
				h1Map["hprobyQ_quark_denominator"]->Fill(yQ,wgt);
				h1Map["hprobyQ_trumumu_denominator"]->Fill(yQ,wgt);
				h1Map["hprobyQ_truqqbar_denominator"]->Fill(yQ,wgt);
				
				
				tv3a->SetXYZ(betax_trumumu, betay_trumumu, betaz_trumumu);
				cosalpha_trumumu = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
				h1Map["hcosalpha_trumumu"]->Fill(cosalpha_trumumu,wgt);
				if(cosalpha_trumumu<=0.)     h1Map["hprobyQ_trumumu_ratio"]->Fill(truth_all_ySystem,wgt);
				// _INFO("cosalpha_trumumu = "+_s(cosalpha_trumumu));
			
				tv3a->SetXYZ(betax_quarks, betay_quarks, betaz_quarks);
				cosalpha_truqqbar = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
				h1Map["hcosalpha_truqqbar"]->Fill(cosalpha_truqqbar,wgt);
				if(cosalpha_truqqbar<=0.) h1Map["hprobyQ_truqqbar_ratio"]->Fill(truth_all_ySystem,wgt);
				// _INFO("cosalpha_truqqbar = "+_s(cosalpha_truqqbar));
				
				tlva->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru), truth_all_mc_eta->at(imuontru), truth_all_mc_phi->at(imuontru), muonMass);
				tlvb->SetPtEtaPhiM(recon_all_pt->at(0), recon_all_eta->at(0), recon_all_phi->at(0), muonMass);
				tlvtmp->SetPtEtaPhiM(recon_all_pt->at(1), recon_all_eta->at(1), recon_all_phi->at(1), muonMass);
				dr1 = kin.dR(tlva,tlvb);
				dr2 = kin.dR(tlva,tlvtmp);
				h2Map["hdRtru1dRtru2"]->Fill(dr1,dr2,wgt);
				imuonrec = (dr1<0.1) ? 0 : 1;
				dr = (dr1<0.2) ? dr1 : dr2;
				// _INFO("imuontru[qtru="+_s(truth_all_mc_charge->at(imuontru))+"]="+_s(imuontru)+",  imuonrec="+_s(imuonrec)+",  dr="+_s(dr)+",  qrec="+_s(recon_all_charge->at(imuonrec)));
				if(truth_all_mc_charge->at(imuontru)*recon_all_charge->at(imuonrec)<0.) // muon matched but the charge is flipped
				{
					_INFO("Charge flip  ->  dR0="+_s(dr1)+",  dR1="+_s(dr2)+"  ->  imuonrec="+_s(imuonrec)+"  ->  c(imuonrec)="+_s(recon_all_charge->at(imuonrec)));
					// _INFO("charge flip, TRUTH:  tlva->Pt()="+_s(tlva->Pt())+",  pt="+_s(truth_all_mc_pt->at(imuontru))+",  m="+_s(muonMass));
					// _INFO("charge flip, RECON:  tlvb->Pt()="+_s(tlvb->Pt())+",  pt="+_s(recon_all_pt->at(imuonrec))+",  m="+_s(muonMass));
					h1Map["hprobChargeFlip_p_ratio"]->Fill(tlva->P(),wgt);
					h1Map["hprobChargeFlip_pT_ratio"]->Fill(tlva->Pt(),wgt);
					h1Map["hprobChargeFlip_y_ratio"]->Fill(tlva->Rapidity(),wgt);
				}
			
				imuonrec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				tlva->SetPtEtaPhiM(recon_all_pt->at(imuonrec),recon_all_eta->at(imuonrec),recon_all_phi->at(imuonrec),recon_all_m->at(imuonrec));
				tlvb->SetPtEtaPhiM(recon_all_pt->at(iamuonrec),recon_all_eta->at(iamuonrec),recon_all_phi->at(iamuonrec),recon_all_m->at(iamuonrec));
				ca = recon_all_charge->at(imuonrec);
				cb = recon_all_charge->at(iamuonrec);
				if(ca*cb>=0.) _WARNING("ca*cb>=0., skipping event");
				mass = kin.imass(tlva,tlvb);
				if(mass<=minPossibleImass || mass>maxPossibleImass) _WARNING("mass<=minPossibleImass || mass>maxPossibleImass  ->  mass="+_s(mass));
				costhetaCS = kin.cosThetaCollinsSoper(tlva,ca,tlvb,cb);
				if(fabs(costhetaCS)>1.) _WARNING("|cos(theta)|>1.");
				yQ = kin.ySystem(tlva,tlvb);
				if(fabs(yQ)>6.) _WARNING("|yQ|>6.");
			
				h1Map["hMass"]->Fill(mass,wgt);
				h1Map["hbetaZ"]->Fill(betaz_rec,wgt);
				h1Map["hyQ"]->Fill(yQ,wgt);
				h1Map["hyQabs"]->Fill(fabs(yQ),wgt);
				
				h2Map["hMassyQ"]->Fill(mass,yQ,wgt);
				h2Map["hMassCosThetaCS"]->Fill(mass,costhetaCS,wgt);
				h2Map["hyQCosThetaCS"]->Fill(yQ,costhetaCS,wgt);
				h2Map["hyQCosThetaCS_acc"]->Fill(yQ,costhetaCS,wgt);
				h2Map["hbetaZyQ"]->Fill(betaz_rec,yQ,wgt);
				h2Map["hbetaabsyQabs"]->Fill(betamag_rec,fabs(yQ),wgt);
			
				// h1Map["hMass"]->Fill(recon_all_Mhat,wgt);
				// h1Map["hbetaZ"]->Fill(betaz_rec,wgt);
				// h1Map["hyQ"]->Fill(recon_all_ySystem,wgt);
				// h1Map["hyQabs"]->Fill(fabs(recon_all_ySystem),wgt);
				
				// h2Map["hMassyQ"]->Fill(recon_all_Mhat,recon_all_ySystem,wgt);
				// h2Map["hMassCosThetaCS"]->Fill(recon_all_Mhat,recon_all_CosThetaCS,wgt);
				// h2Map["hyQCosThetaCS"]->Fill(recon_all_ySystem,recon_all_CosThetaCS,wgt);
				// h2Map["hyQCosThetaCS_acc"]->Fill(recon_all_ySystem,recon_all_CosThetaCS,wgt);
				// h2Map["hbetaZyQ"]->Fill(betaz_rec,recon_all_ySystem,wgt);
				// h2Map["hbetaabsyQabs"]->Fill(betamag_rec,fabs(recon_all_ySystem),wgt);
				
				tlva->SetPtEtaPhiM(recon_all_pt->at(0), recon_all_eta->at(0), recon_all_phi->at(0), muonMass);
				tlvb->SetPtEtaPhiM(recon_all_pt->at(1), recon_all_eta->at(1), recon_all_phi->at(1), muonMass);
				mass = kin.imass(tlva,tlvb);
				if(mass>=logmassmin && mass<=logmassmax)
				{
					int bin = h1Map["hEllipticity"]->FindBin(mass);
					if(bin>0 && bin<h1Map["hEllipticity"]->GetNbinsX())
					{
						int imuonrec_uncorrected = (recon_all_id->at(0)>0) ? 0 : 1;
						float eta_rec = recon_all_eta->at(imuonrec_uncorrected);
						// _INFO("mass="+_s(mass)+", bin="+_s(bin)+", imuonrec_uncorrected="+_s(imuonrec_uncorrected)+", eta_rec="+_s(eta_rec));
						string hName = (fabs(eta_rec)<etax) ? "hEllipticity_sides_bin_" : "hEllipticity_central_bin_";
						hName += _s(bin);
						if(fabs(eta_rec)<=etamax) h1Map[hName]->Fill(eta_rec,wgt);
						//else _WARNING("Eta exceeds its cut limit  ->  "+_s(eta_rec));
					}
				}
			}
			
			// For the truth Afb
			iamuontru = (imuontru==0) ? 1 : 0;
			tv3a->SetPtEtaPhi(truth_all_mc_pt->at(imuontru),truth_all_mc_eta->at(imuontru),truth_all_mc_phi->at(imuontru));
			tv3b->SetPtEtaPhi(truth_all_partons_mc_pdgId->at(iquark),truth_all_partons_mc_eta->at(iquark),truth_all_partons_mc_phi->at(iquark));
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),truth_all_mc_eta->at(imuontru),truth_all_mc_phi->at(imuontru),truth_all_mc_m->at(imuontru));
			tlvb->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru),truth_all_mc_eta->at(iamuontru),truth_all_mc_phi->at(iamuontru),truth_all_mc_m->at(iamuontru));
			//yQ = kin.ySystem(tlva,tlvb);
			mass = kin.imass(tlva,tlvb);
			if(mass<=minPossibleImass || mass>maxPossibleImass) _WARNING("mass<=minPossibleImass || mass>maxPossibleImass  ->  mass="+_s(mass));
			cosalpha_trumuon_quark = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
			if(cosalpha_trumuon_quark>0.) h1Map["hforward_trumu_quark"]->Fill(mass,wgt);
			else                          h1Map["hbackward_trumu_quark"]->Fill(mass,wgt);
			
			
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru), truth_all_mc_eta->at(imuontru), truth_all_mc_phi->at(imuontru), muonMass);
			h1Map["hprobChargeFlip_p_denominator"]->Fill(tlva->P(),wgt);
			h1Map["hprobChargeFlip_pT_denominator"]->Fill(tlva->Pt(),wgt);
			h1Map["hprobChargeFlip_y_denominator"]->Fill(tlva->Rapidity(),wgt);
			
			
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(0), truth_all_mc_eta->at(0), truth_all_mc_phi->at(0), muonMass);
			tlvb->SetPtEtaPhiM(truth_all_mc_pt->at(1), truth_all_mc_eta->at(1), truth_all_mc_phi->at(1), muonMass);
			betaztru = kin.betaSystem(tlva->Pz(), tlvb->Pz(), tlva->E(), tlvb->E());
			h2Map["hbetaZyQtru"]->Fill(betaztru,yQ,wgt);
			h2Map["hyQCosThetaCS_tru"]->Fill(yQ,costhetaCS,wgt);
		}
	}
	else
	{
		betax_rec = kin.betaSystem(px->at(0), px->at(1), E->at(0), E->at(1));	
		betay_rec = kin.betaSystem(py->at(0), py->at(1), E->at(0), E->at(1));	
		betaz_rec = kin.betaSystem(pz->at(0), pz->at(1), E->at(0), E->at(1));
		betamag_rec = sqrt(betax_rec*betax_rec+betay_rec*betay_rec+betaz_rec*betaz_rec);
		
		imuonrec  = (charge->at(0)<0.) ? 0 : 1;
		iamuonrec = (imuonrec==0) ? 1 : 0;
		tlva->SetPtEtaPhiM(pt->at(imuonrec),eta->at(imuonrec),phi->at(imuonrec),m->at(imuonrec));
		tlvb->SetPtEtaPhiM(pt->at(iamuonrec),eta->at(iamuonrec),phi->at(iamuonrec),m->at(iamuonrec));
		ca = charge->at(imuonrec);
		cb = charge->at(iamuonrec);
		if(ca*cb>=0.) _WARNING("ca*cb>=0., skipping event");
		mass = kin.imass(tlva,tlvb)*MeV2GeV;
		if(mass<=minPossibleImass || mass>maxPossibleImass) _WARNING("mass<=minPossibleImass || mass>maxPossibleImass  ->  mass="+_s(mass));
		costhetaCS = kin.cosThetaCollinsSoper(tlva,ca,tlvb,cb);
		if(fabs(costhetaCS)>1.) _WARNING("|cos(theta)|>1.");
		yQ = kin.ySystem(tlva,tlvb);
		if(fabs(yQ)>6.) _WARNING("|yQ|>6.");
		
		h1Map["hMass"]->Fill(mass);
		h1Map["hbetaZ"]->Fill(betaz_rec);
		h1Map["hyQ"]->Fill(yQ);
		h1Map["hyQabs"]->Fill(fabs(yQ));
		
		h2Map["hMassyQ"]->Fill(mass,yQ);
		h2Map["hMassCosThetaCS"]->Fill(mass,costhetaCS);
		h2Map["hyQCosThetaCS"]->Fill(yQ,costhetaCS);
		h2Map["hbetaZyQ"]->Fill(betaz_rec,yQ);
		h2Map["hbetaabsyQabs"]->Fill(betamag_rec,fabs(yQ));
		
		// h1Map["hMass"]->Fill(Mhat*TeV2GeV);
		// h1Map["hbetaZ"]->Fill(betaz_rec);
		// h1Map["hyQ"]->Fill(Ysystem);
		// h1Map["hyQabs"]->Fill(fabs(Ysystem));
		
		// h2Map["hMassyQ"]->Fill(Mhat*TeV2GeV,Ysystem);
		// h2Map["hMassCosThetaCS"]->Fill(Mhat*TeV2GeV,CosThetaCS);
		// h2Map["hyQCosThetaCS"]->Fill(Ysystem,CosThetaCS);
		// h2Map["hbetaZyQ"]->Fill(betaz_rec,Ysystem);
		// h2Map["hbetaabsyQabs"]->Fill(betamag_rec,fabs(Ysystem));
		
		tlva->SetPtEtaPhiM(pt->at(0)*MeV2GeV, eta->at(0), phi->at(0), muonMass);
		tlvb->SetPtEtaPhiM(pt->at(1)*MeV2GeV, eta->at(1), phi->at(1), muonMass);
		mass = kin.imass(tlva,tlvb);
		if(mass>=logmassmin && mass<=logmassmax)
		{
			int bin = h1Map["hEllipticity"]->FindBin(mass);
			if(bin>0 && bin<h1Map["hEllipticity"]->GetNbinsX())
			{
				int imuonrec_uncorrected = (charge->at(0)<0.) ? 0 : 1;
				float eta_rec = eta->at(imuonrec_uncorrected);
				// _INFO("mass="+_s(mass)+", bin="+_s(bin)+", imuonrec_uncorrected="+_s(imuonrec_uncorrected)+", eta_rec="+_s(eta_rec));
				string hName = (fabs(eta_rec)<etax) ? "hEllipticity_sides_bin_" : "hEllipticity_central_bin_";
				hName += _s(bin);
				if(fabs(eta_rec)<=etamax) h1Map[hName]->Fill(eta_rec);
				//else _WARNING("Eta exceeds its cut limit  ->  "+_s(eta_rec));
			}
		}
	}
}

void init(TTree* t=NULL)
{
	_DEBUG("init");

	if(t==NULL)
	{
		if(isMC)
		{
			fName = "/data/hod/pythia8_ntuples/ATLASZP/mcLocalControl_Zprime_mumu_SSM1500.root";
			// fName = "/data/hod/pythia8_ntuples/ATLASZP/mcLocalControl_Zprime_mumu_SSM1000.root";
			tName = "truth/truth_tree";
		}
		else
		{
			fName = "../data/merged.root";
			tName = "allCuts/allCuts_tree";
		}
		
		file = new TFile(fName,"READ");
		tree = (TTree*)file->Get(tName);
		if(isMC) mcbranches();
		else     databranches();
		_DEBUG("successfully fetched tree");
	}
	else
	{
		tree = t;
		if(isMC) mcbranches();
		else     databranches();
		_DEBUG("successfully fetched tree");
	}
}

void run()
{
	msglvl[DBG] = SILENT;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	_DEBUG("run");
	
	style();
	hbook();

	if(!isMC || (isMC && isZprime))
	{
		init();
		Int_t N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			////////////////////////////////////
			//// blocks of analysis go here ////
			////////////////////////////////////
			hfill(); ///////////////////////////
			////////////////////////////////////
		}
	}
	else
	{
		settrees();
		for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
		{
			init(it->second);
			Int_t N = tree->GetEntriesFast();
			for(Int_t entry=0 ; entry<N ; entry++)
			{
				tree->GetEntry(entry);
				////////////////////////////////////
				//// blocks of analysis go here ////
				////////////////////////////////////
				hfill(wgtMap[it->first]); //////////
				////////////////////////////////////
			}
		}
	}
	
	hdraw();
	save("plots");
}

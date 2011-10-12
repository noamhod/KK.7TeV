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
float nDYmumu70to110 = 0;
float nData70to110   = 0;

Bool_t isMC=true;
Bool_t isZprime=false;
Bool_t dolog=true;

kinematics* K;

TLorentzVector* tlva   = new TLorentzVector;
TLorentzVector* tlvb   = new TLorentzVector;
TLorentzVector* tlvtmp = new TLorentzVector;
TVector3*       tv3a   = new TVector3;
TVector3*       tv3b   = new TVector3;

TLorentzVector* tlvmutrua = new TLorentzVector;
TLorentzVector* tlvmutrub = new TLorentzVector;
TLorentzVector* tlvmureca = new TLorentzVector;
TLorentzVector* tlvmurecb = new TLorentzVector;
TLorentzVector* tlvqa  = new TLorentzVector;
TLorentzVector* tlvqb  = new TLorentzVector;

TLorentzVector* tlvmutruaBoosted = new TLorentzVector;
TLorentzVector* tlvmutrubBoosted = new TLorentzVector;
TLorentzVector* tlvmurecaBoosted = new TLorentzVector;
TLorentzVector* tlvmurecbBoosted = new TLorentzVector;
TLorentzVector* tlvqaBoosted  = new TLorentzVector;
TLorentzVector* tlvqbBoosted  = new TLorentzVector;

TVector3*       tv3mutrua = new TVector3;
TVector3*       tv3mutrub = new TVector3;
TVector3*       tv3mureca = new TVector3;
TVector3*       tv3murecb = new TVector3;
TVector3*       tv3qa  = new TVector3;
TVector3*       tv3qb  = new TVector3;

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

float all_pileup_weight;
float all_EW_kfactor_weight;
float all_QCD_kfactor_weight;
float all_mcevent_weight;
float all_total_weight;

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
float actualIntPerXing;
float averageIntPerXing;
unsigned int mc_channel_number;
unsigned int mc_event_number;
double mc_event_weight;

float pileup_weight;
float EW_kfactor_weight;
float QCD_kfactor_weight;
float mcevent_weight;
float total_weight;

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
void graphics(TH1* th1,
			  Int_t mrkrstyle=-1, Int_t mrkrsize=-1,
			  Int_t fillstyle=-1,
			  Int_t linestyle=-1, Int_t linewidth=-1,
			  Color_t linecolor=-1, Color_t fillcolor=-1, Color_t mrkrcolor=-1,
			  Bool_t moreLogLabels=true, Bool_t noexponent=true,
			  TString title="", TString xtitle="", TString ytitle="")
{
	_DEBUG("graphics");
	
	if(mrkrstyle>0) th1->SetMarkerStyle(mrkrstyle);
	if(mrkrsize>0)  th1->SetMarkerSize(mrkrsize);
	if(fillstyle>0) th1->SetFillStyle(fillstyle);
	
	if(linecolor>0) th1->SetLineColor(linecolor);
	if(fillcolor>0) th1->SetFillColor(fillcolor);
	if(mrkrcolor>0) th1->SetMarkerColor(mrkrcolor);
	
	if(linestyle>0) th1->SetLineStyle(linestyle);
	if(linewidth>0) th1->SetLineWidth(linewidth);
	
	if(moreLogLabels) th1->GetXaxis()->SetMoreLogLabels(); 
	if(noexponent)    th1->GetXaxis()->SetNoExponent(); 
	
	if(title!="")  th1->SetTitle(title);
	if(xtitle!="") th1->SetXTitle(xtitle);
	if(ytitle!="") th1->SetYTitle(ytitle);
}


void draw(TObject* tobj, /*TString oName,*/ TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	_DEBUG("draw");

	// TString cName = "c"+oName;
	TString oName = (TString)tobj->GetName();
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
	if(drawopt=="") tobj->Draw("SAMES");
	else            tobj->Draw(drawopt+" SAMES");
}

void save(TString oDir)
{
	_DEBUG("save");

	_INFO("save all canvases");
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		TString pName = oDir+"/mcdata_"+it->first;
		it->second->SaveAs(pName+".png");
		it->second->SaveAs(pName+".eps");
		it->second->SaveAs(pName+".pdf");
		it->second->SaveAs(pName+".root");
		it->second->SaveAs(pName+".C");
	}
	
	_INFO("save all histograms (to a single .root file)");
	TString pName = oDir+"/mcdata_histograms.root";

	TFile* f = new TFile(pName,"RECREATE");
	f->cd();
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it) it->second->Write();
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it) it->second->Write();
	f->Write();
	f->Close();
	delete f;
}

void setMCtree(TString fPath, TString name, Double_t N, Double_t sigma)
{
	_DEBUG("setMCtree");

	file = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	wgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
}

void setDATAtree()
{
	_DEBUG("setDATAtree");
	
	//fName = "../data/merged.root";
	fName = "../data/analysisLocalControl.root";
	tName = "allCuts/allCuts_tree";
	file = new TFile(fName,"READ");
	tree = (TTree*)file->Get(tName);
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	if(tsMCname=="DYmumu")
	{
		setMCtree("../data/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 20000, 7.9862E-01*nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 20000, 4.1075E-04*nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 20000, 6.6459E-05*nb2fb);
		// setMCtree("../data/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 20000, *nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 20000, 2.6516E-06*nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 20000, 8.9229E-07*nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 20000, 2.3957E-07*nb2fb);
		// setMCtree("../data/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 20000, *nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 20000, 2.4614E-08*nb2fb);
		setMCtree("../data/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 20000, 1.4001E-08*nb2fb);
	}
}

void setMCbranches()
{
	_DEBUG("setMCbranches");

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
	
	tree->SetBranchAddress( "all_actualIntPerXing",  &all_actualIntPerXing );
	tree->SetBranchAddress( "all_averageIntPerXing", &all_averageIntPerXing );
	tree->SetBranchAddress( "all_mc_channel_number", &all_mc_channel_number );
	tree->SetBranchAddress( "all_mc_event_number",   &all_mc_event_number );
	tree->SetBranchAddress( "all_mc_event_weight",   &all_mc_event_weight );
	
	tree->SetBranchAddress( "all_pileup_weight",      &all_pileup_weight );
	tree->SetBranchAddress( "all_EW_kfactor_weight",  &all_EW_kfactor_weight );
	tree->SetBranchAddress( "all_QCD_kfactor_weight", &all_QCD_kfactor_weight );
	tree->SetBranchAddress( "all_mcevent_weight",     &all_mcevent_weight );
	tree->SetBranchAddress( "all_total_weight",       &all_total_weight );

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

void setDATAbranches()
{
	_DEBUG("setDATAbranches");

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
	
	tree->SetBranchAddress( "actualIntPerXing",  &actualIntPerXing );
	tree->SetBranchAddress( "averageIntPerXing", &averageIntPerXing );
	tree->SetBranchAddress( "mc_channel_number", &mc_channel_number );
	tree->SetBranchAddress( "mc_event_number",   &mc_event_number );
	tree->SetBranchAddress( "mc_event_weight",   &mc_event_weight );
	
	tree->SetBranchAddress( "pileup_weight",  &pileup_weight );
	tree->SetBranchAddress( "EW_kfactor_weight", &EW_kfactor_weight );
	tree->SetBranchAddress( "QCD_kfactor_weight", &QCD_kfactor_weight );
	tree->SetBranchAddress( "mcevent_weight", &mcevent_weight );
	tree->SetBranchAddress( "total_weight",   &total_weight );
	
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

// TH1* th1,
// Int_t mrkrstyle, Int_t mrkrsize,
// Int_t fillstyle,
// Int_t linestyle, Int_t linewidth,
// Color_t linecolor, Color_t fillcolor, Color_t mrkrcolor,
// Bool_t moreLogLabels=true, Bool_t noexponent=true,
// TString title="", TString xtitle="", TString ytitle=""
void hbook()
{
	_DEBUG("hbook");

	setLogBins(npbins,pmin,pmax,pbins);
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);

	h1Map.insert( make_pair("hMassData", new TH1D("hMassData",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassData"]);
	graphics(h1Map["hMassData"],  24,1);
	
	h1Map.insert( make_pair("hMassDYmumu", new TH1D("hMassDYmumu",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassDYmumu"]);
	graphics(h1Map["hMassDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
}

float getDataMCratio()
{
	float ratio = (nDYmumu70to110>0.) ? nData70to110/nDYmumu70to110 : 1.;
	_INFO("DATA/DYmumu in 70 to 110 GeV is: "+_s(ratio,8));
	return ratio;
}

void hdraw()
{
	_DEBUG("hdraw");

	// imass
	bool isXerr = false;
	//resetHistogramErrors(h1Map["hMassData"]);
	TGraphAsymmErrors* gMpoissonErr = GetPoissonizedGraph(h1Map["hMassData"], isXerr);
	//TGraphAsymmErrors* gMpoissonErr = GetSqrtErrorsGraph(h1Map["hMassData"], isXerr);
	//TGraphAsymmErrors* gMpoissonErr = GetDefaultErrorsGraph(h1Map["hMassData"], isXerr);
	gMpoissonErr->SetMarkerStyle(24);
	gMpoissonErr->SetMarkerSize(1);
	
	float ratio = getDataMCratio();
	Scale(h1Map["hMassDYmumu"],ratio);
	
	setMinMax(h1Map["hMassDYmumu"],h1Map["hMassData"]);
	draw(h1Map["hMassDYmumu"], "", dolog, dolog);
	drawon("hMassDYmumu", h1Map["hMassData"], "e1x1");
	//drawon("hMassDYmumu", gMpoissonErr, "e1x1");
}

void hfill(TString tsRunType="DATA", TString tsMCname="DYmumu", Double_t wgt=1.)
{
	_DEBUG("hfill");
	
	float mass = 0.;
	float dr1  = 0.;
	float dr2  = 0.;
	float ca   = 0.;
	float cb   = 0.;
	
	int imuontru  = -999;
	int iamuontru = -999;
	int imuonrec  = -999;
	int iamuonrec = -999;
	
	if(tsRunType=="MC")
	{
		if(truth_all_isValid)
		{
			imuontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
			iamuontru = (imuontru==0) ? 1 : 0;

			tlvmutrua->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),  truth_all_mc_eta->at(imuontru),  truth_all_mc_phi->at(imuontru),  muonMass);
			tlvmutrub->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru), truth_all_mc_eta->at(iamuontru), truth_all_mc_phi->at(iamuontru), muonMass);
			
			(*tv3mutrua) = tlvmutrua->Vect();
			(*tv3mutrub) = tlvmutrub->Vect();
			tlvmutruaBoosted = K->Boost(tlvmutrua,tlvmutrub,tlvmutrua);
			tlvmutrubBoosted = K->Boost(tlvmutrua,tlvmutrub,tlvmutrub);
			(*tv3mutruaBoosted) = tlvmutruaBoosted->Vect();
			(*tv3mutrubBoosted) = tlvmutrubBoosted->Vect();


			if(recon_all_isValid)
			{
				imuonrec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				
				tlvtmp->SetPtEtaPhiM(recon_all_pt->at(imuonrec), recon_all_eta->at(imuonrec), recon_all_phi->at(imuonrec), muonMass);
				dr1 = K->dR(tlvtmp,tlvmutrua);
				dr2 = K->dR(tlvtmp,tlvmutrub);
				imuonrec  = (dr1<=dr2) ? imuonrec : iamuonrec;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				if(dr1>dr2) _WARNING("dr1(recA,truA) > dr2(recA,truB)");
				
				tlvmureca->SetPtEtaPhiM(recon_all_pt->at(imuonrec),  recon_all_eta->at(imuonrec),  recon_all_phi->at(imuonrec),  muonMass);
				tlvmurecb->SetPtEtaPhiM(recon_all_pt->at(iamuonrec), recon_all_eta->at(iamuonrec), recon_all_phi->at(iamuonrec), muonMass);
				(*tv3mureca) = tlvmureca->Vect();
				(*tv3murecb) = tlvmurecb->Vect();
				tlvmurecaBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmureca);
				tlvmurecbBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmurecb);
				(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
				(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
			}
			
			////////////////////////////
			/// analysis statrs here ///
			////////////////////////////
			
			if(recon_all_isValid  &&  imuonrec>=0. && iamuonrec>=0.  &&  imuonrec!=iamuonrec)
			{
				ca = recon_all_charge->at(imuonrec);
				cb = recon_all_charge->at(iamuonrec);
				if(ca*cb>=0.) _WARNING("ca*cb>=0, skipping event");
				mass = K->imass(tlvmureca,tlvmurecb);
				
				float event_weight = all_total_weight;
				
				if(mass>=70.  &&  mass<=110.) nDYmumu70to110 += 1.*wgt*event_weight;
				
				_DEBUG("MC -> mass="+_s(mass));
				_DEBUG("MC -> ca="+_s(ca));
				_DEBUG("MC -> cb="+_s(cb));
				
				/////////////////////////////////
				/// MC histo fill statrs here ///
				/////////////////////////////////
				h1Map["hMass"+tsMCname]->Fill(mass,wgt*event_weight);
			}
		}
	}
	else if(tsRunType=="DATA")
	{
		imuonrec  = (charge->at(0)<0.) ? 0 : 1;
		iamuonrec = (imuonrec==0) ? 1 : 0;
		
		tlvmureca->SetPtEtaPhiM(pt->at(imuonrec)*MeV2GeV,  eta->at(imuonrec),  phi->at(imuonrec),  muonMass);
		tlvmurecb->SetPtEtaPhiM(pt->at(iamuonrec)*MeV2GeV, eta->at(iamuonrec), phi->at(iamuonrec), muonMass);
		(*tv3mureca) = tlvmureca->Vect();
		(*tv3murecb) = tlvmurecb->Vect();
		tlvmurecaBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmureca);
		tlvmurecbBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmurecb);
		(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
		(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
	
		////////////////////////////
		/// analysis statrs here ///
		////////////////////////////
	
		ca = charge->at(imuonrec);
		cb = charge->at(iamuonrec);
		if(ca*cb>=0.) _WARNING("ca*cb>=0, skipping event");
		mass = K->imass(tlvmureca,tlvmurecb);
		
		if(mass>=70.  &&  mass<=110.) nData70to110 += 1.;
		
		///////////////////////////////////
		/// DATA histo fill statrs here ///
		///////////////////////////////////
		h1Map["hMassData"]->Fill(mass);
	}
}

void init(TTree* t=NULL)
{
	_DEBUG("init");

	if(t==NULL) // data
	{
		setDATAtree();
		setDATAbranches();
		_DEBUG("successfully fetched data tree");
	}
	else // mc
	{
		tree = t;
		setMCbranches();
		_DEBUG("successfully fetched MC tree");
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

	Int_t N = 0;
	
	// data
	init();
	N = tree->GetEntriesFast();
	for(Int_t entry=0 ; entry<N ; entry++)
	{
		tree->GetEntry(entry);
		////////////////////////////////////
		//// blocks of analysis go here ////
		////////////////////////////////////
		hfill(); ///////////////////////////
		////////////////////////////////////
	}
	
	TString mcName = "DYmumu";
	setMCtrees(mcName);
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		init(it->second);
		N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			////////////////////////////////////////////
			//// blocks of analysis go here ////////////
			////////////////////////////////////////////
			hfill("MC", mcName, wgtMap[it->first]); ////
			////////////////////////////////////////////
		}
	}
	
	hdraw();
	save("plots");
}

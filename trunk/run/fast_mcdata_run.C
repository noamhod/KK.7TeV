#include "basicIncludes.h"

TFile* file;
TTree* tree;
TString fName;
TString tName;
TPaveText* pvtxt_lumi;
TPaveText* pvtxt_atlas;
TText* txt;
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
			  Int_t mrkrstyle=-1, Float_t mrkrsize=-1,
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

void text()
{
	pvtxt_atlas = new TPaveText(0.4032663,0.2797203,0.5678392,0.3741259,"brNDC"); // 0.2110553,0.7097902,0.3756281,0.8041958 -> for 2d
	//pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetFillStyle(4000); //will be transparent
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText("#bf{#splitline{#it{ATLAS}}{#scale[0.42]{work in progress}}}");

	pvtxt_lumi = new TPaveText(0.4032663,0.1660839,0.5678392,0.2727273,"brNDC"); // 0.2110553,0.5926573,0.3756281,0.6993007 -> for 2d
	//pvtxt_lumi->SetFillColor(kWhite);
	pvtxt_lumi->SetFillStyle(4000); //will be transparent
	pvtxt_lumi->SetFillColor(0);
	TString sLumi = (TString)_s(luminosity,2);
	txt = pvtxt_lumi->AddText( "#intLdt~"+ sLumi +" fb^{-1}" );
}

void draw(TObject* tobj, TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog, Bool_t logz=!dolog)
{
	_DEBUG("draw");

	TString oName = (TString)tobj->GetName();
	TString cName = "c"+oName;
	cnvMap.insert( make_pair(oName, new TCanvas(cName,cName,600,400)) );
	if(logx) cnvMap[oName]->SetLogx();
	if(logy) cnvMap[oName]->SetLogy();
	if(logz) cnvMap[oName]->SetLogz();
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

void drawtxton(TString existing_oName)
{
	_DEBUG("drawtxton");

	cnvMap[existing_oName]->cd();
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
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
	
	//fName = "/data/hod/2011/NTUPLE/DATA/merged.root";
	fName = "/data/hod/2011/NTUPLE/DATA/analysisLocalControl.root";
	tName = "allCuts/allCuts_tree";
	file = new TFile(fName,"READ");
	tree = (TTree*)file->Get(tName);
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	if(tsMCname=="DYmumu")
	{
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_Zmumu.root", "mcLocalControl_Zmumu", 5000000, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
		//// setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 20000, 7.9862E-01*nb2fb);
		//// setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb);
		
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 20000, 4.1075E-04*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 20000, 6.6459E-05*nb2fb);
		// setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 20000, *nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 20000, 2.6516E-06*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 20000, 8.9229E-07*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 20000, 2.3957E-07*nb2fb);
		// setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 20000, *nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 20000, 2.4614E-08*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/MC/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 20000, 1.4001E-08*nb2fb);
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

void hbook()
{
	_DEBUG("hbook");

	setLogBins(npbins,pmin,pmax,pbins);
	setLogBins(nlogptbins,logptmin,logptmax,logptbins);
	setLogBins(nlogqtbins,logqtmin,logqtmax,logqtbins);
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);

	h1Map.insert( make_pair("hMassData", new TH1D("hMassData",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassData"]);
	graphics(h1Map["hMassData"],  24,0.8);
	h1Map.insert( make_pair("hMassDYmumu", new TH1D("hMassDYmumu",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	//h1Map["hMassDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hMassDYmumu"]);
	graphics(h1Map["hMassDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hyQData", new TH1D("hyQData",";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
	setlogx(h1Map["hyQData"]);
	graphics(h1Map["hyQData"],  24,0.8);
	h1Map.insert( make_pair("hyQDYmumu", new TH1D("hyQDYmumu",";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
	///h1Map["hyQDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hyQDYmumu"]);
	graphics(h1Map["hyQDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hQTData", new TH1D("hQTData",";Q_{T} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hQTData"]);
	graphics(h1Map["hQTData"],  24,0.8);
	h1Map.insert( make_pair("hQTDYmumu", new TH1D("hQTDYmumu",";Q_{T} GeV;Events",nlogptbins,logptbins)) );
	//h1Map["hQTDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hQTDYmumu"]);
	graphics(h1Map["hQTDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hEtaLeadingData", new TH1D("hEtaLeadingData",";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaLeadingData"]);
	graphics(h1Map["hEtaLeadingData"],  24,0.8);
	h1Map.insert( make_pair("hEtaLeadingDYmumu", new TH1D("hEtaLeadingDYmumu",";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
	//h1Map["hEtaLeadingDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hEtaLeadingDYmumu"]);
	graphics(h1Map["hEtaLeadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hEtaSubleadingData", new TH1D("hEtaSubleadingData",";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaSubleadingData"]);
	graphics(h1Map["hEtaSubleadingData"],  24,0.8);
	h1Map.insert( make_pair("hEtaSubleadingDYmumu", new TH1D("hEtaSubleadingDYmumu",";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
	//h1Map["hEtaSubleadingDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hEtaSubleadingDYmumu"]);
	graphics(h1Map["hEtaSubleadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hPhiLeadingData", new TH1D("hPhiLeadingData",";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiLeadingData"]);
	graphics(h1Map["hPhiLeadingData"],  24,0.8);
	h1Map.insert( make_pair("hPhiLeadingDYmumu", new TH1D("hPhiLeadingDYmumu",";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
	//h1Map["hPhiLeadingDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hPhiLeadingDYmumu"]);
	graphics(h1Map["hPhiLeadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hPhiSubleadingData", new TH1D("hPhiSubleadingData",";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiSubleadingData"]);
	graphics(h1Map["hPhiSubleadingData"],  24,0.8);
	h1Map.insert( make_pair("hPhiSubleadingDYmumu", new TH1D("hPhiSubleadingDYmumu",";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
	//h1Map["hPhiSubleadingDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hPhiSubleadingDYmumu"]);
	graphics(h1Map["hPhiSubleadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hpTLeadingData", new TH1D("hpTLeadingData",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingData"]);
	graphics(h1Map["hpTLeadingData"],  24,0.8);
	h1Map.insert( make_pair("hpTLeadingDYmumu", new TH1D("hpTLeadingDYmumu",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	//h1Map["hpTLeadingDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hpTLeadingDYmumu"]);
	graphics(h1Map["hpTLeadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hpTSubleadingData", new TH1D("hpTSubleadingData",";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTSubleadingData"]);
	graphics(h1Map["hpTSubleadingData"],  24,0.8);
	h1Map.insert( make_pair("hpTSubleadingDYmumu", new TH1D("hpTSubleadingDYmumu",";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
	//h1Map["hpTSubleadingDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h1Map["hpTSubleadingDYmumu"]);
	graphics(h1Map["hpTSubleadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	///// 2d /////
	
	h2Map.insert( make_pair("hMassCosThetaCSData", new TH2D("hMassCosThetaCSData",";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	setlogx(h2Map["hMassCosThetaCSData"]);
	linMap.insert( make_pair("hMassCosThetaCS_horline", new TLine(linfullimassmin,0.,linfullimassmax,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassCosThetaCS_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],minFullCosTheta,logmassbins[ms],maxFullCosTheta)) );
	}
	h2Map.insert( make_pair("hMassCosThetaCSDYmumu", new TH2D("hMassCosThetaCSDYmumu",";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	//h1Map["hMassCosThetaCSDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h2Map["hMassCosThetaCSDYmumu"]);
	
	h2Map.insert( make_pair("hMassyQData", new TH2D("hMassyQData",";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
	setlogx(h2Map["hMassyQData"]);
	linMap.insert( make_pair("hMassyQ_horline", new TLine(linfullimassmin,0.,linfullimassmax,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassyQ_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],minfullyQ,logmassbins[ms],maxfullyQ)) );
	}
	h2Map.insert( make_pair("hMassyQDYmumu", new TH2D("hMassyQDYmumu",";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
	//h1Map["hMassyQDYmumu"]->SetDefaultSumw2(kTRUE);
	setlogx(h2Map["hMassyQDYmumu"]);
}

float getDataMCratio()
{
	float ratio = (nDYmumu70to110>0.) ? nData70to110/nDYmumu70to110 : 1.;
	_INFO("DATA/DYmumu in 70 to 110 GeV is: "+_s(ratio,8));
	return ratio;
}

void hscale2Zpeak()
{
	float ratio = getDataMCratio();
	
	Scale(h1Map["hMassDYmumu"],ratio);
	Scale(h1Map["hyQDYmumu"],ratio);
	Scale(h1Map["hQTDYmumu"],ratio);
	Scale(h1Map["hEtaLeadingDYmumu"],ratio);
	Scale(h1Map["hEtaSubleadingDYmumu"],ratio);
	Scale(h1Map["hPhiLeadingDYmumu"],ratio);
	Scale(h1Map["hPhiSubleadingDYmumu"],ratio);
	Scale(h1Map["hpTLeadingDYmumu"],ratio);
	Scale(h1Map["hpTSubleadingDYmumu"],ratio);
	
	///// 2d
	Scale(h2Map["hMassCosThetaCSDYmumu"],ratio);
	Scale(h2Map["hMassyQDYmumu"],ratio);
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
	
	setMinMax(h1Map["hMassDYmumu"],h1Map["hMassData"],true);
	draw(h1Map["hMassDYmumu"], "", dolog, dolog);
	drawon("hMassDYmumu", h1Map["hMassData"], "e1x1");
	//drawon("hMassDYmumu", gMpoissonErr, "e1x1");
	drawtxton("hMassDYmumu");
	
	setMinMax(h1Map["hyQDYmumu"],h1Map["hyQData"],true);
	draw(h1Map["hyQDYmumu"]);
	drawon("hyQDYmumu", h1Map["hyQData"], "e1x1");
	drawtxton("hyQDYmumu");
	
	setMinMax(h1Map["hQTDYmumu"],h1Map["hQTData"],true);
	draw(h1Map["hQTDYmumu"], "", dolog, dolog);
	drawon("hQTDYmumu", h1Map["hQTData"], "e1x1");
	drawtxton("hQTDYmumu");
	
	setMinMax(h1Map["hEtaLeadingDYmumu"],h1Map["hEtaLeadingData"]);
	draw(h1Map["hEtaLeadingDYmumu"]);
	drawon("hEtaLeadingDYmumu", h1Map["hEtaLeadingData"], "e1x1");
	drawtxton("hEtaLeadingDYmumu");
	setMinMax(h1Map["hEtaSubleadingDYmumu"],h1Map["hEtaSubleadingData"]);
	draw(h1Map["hEtaSubleadingDYmumu"]);
	drawon("hEtaSubleadingDYmumu", h1Map["hEtaSubleadingData"], "e1x1");
	drawtxton("hEtaSubleadingDYmumu");
	
	setMinMax(h1Map["hPhiLeadingDYmumu"],h1Map["hPhiLeadingData"]);
	draw(h1Map["hPhiLeadingDYmumu"]);
	drawon("hPhiLeadingDYmumu", h1Map["hPhiLeadingData"], "e1x1");
	drawtxton("hPhiLeadingDYmumu");
	setMinMax(h1Map["hPhiSubleadingDYmumu"],h1Map["hPhiSubleadingData"]);
	draw(h1Map["hPhiSubleadingDYmumu"]);
	drawon("hPhiSubleadingDYmumu", h1Map["hPhiSubleadingData"], "e1x1");
	drawtxton("hPhiSubleadingDYmumu");
	
	setMinMax(h1Map["hpTLeadingDYmumu"],h1Map["hpTLeadingData"],true);
	draw(h1Map["hpTLeadingDYmumu"], "", dolog, dolog);
	drawon("hpTLeadingDYmumu", h1Map["hpTLeadingData"], "e1x1");
	drawtxton("hpTLeadingDYmumu");
	setMinMax(h1Map["hpTSubleadingDYmumu"],h1Map["hpTSubleadingData"],true);
	draw(h1Map["hpTSubleadingDYmumu"], "", dolog, dolog);
	drawon("hpTSubleadingDYmumu", h1Map["hpTSubleadingData"], "e1x1");
	drawtxton("hpTSubleadingDYmumu");
	
	
	///// 2d
	draw(h2Map["hMassCosThetaCSData"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSData", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSData", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSData");
	draw(h2Map["hMassCosThetaCSDYmumu"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSDYmumu", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSDYmumu", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSDYmumu");
	
	draw(h2Map["hMassyQData"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassyQData", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQData", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQData");
	draw(h2Map["hMassyQDYmumu"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassyQDYmumu", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQDYmumu", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQDYmumu");
}

void hfill(TString tsRunType="DATA", TString tsMCname="DYmumu", Double_t wgt=1.)
{
	_DEBUG("hfill");
	
	float mass = 0.;
	float yQ   = 0.;
	float QT   = 0.;
	float cosThetaCS = 0.;
	float cosThetaHE = 0.;
	float dr1  = 0.;
	float dr2  = 0.;
	float ca   = 0.;
	float cb   = 0.;
	float etaLeading = 0.;
	float etaSubleading = 0.;
	float phiLeading = 0.;
	float phiSubleading = 0.;
	float pTLeading = 0.;
	float pTSubleading = 0.;
	
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
				mass          = K->imass(tlvmureca,tlvmurecb);
				yQ            = K->ySystem(tlvmureca,tlvmurecb);
				QT            = K->QT(tlvmureca,tlvmurecb);
				cosThetaCS    = K->cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
				cosThetaHE    = K->cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
				etaLeading    = recon_all_eta->at(0);
				etaSubleading = recon_all_eta->at(1);
				phiLeading    = recon_all_phi->at(0);
				phiSubleading = recon_all_phi->at(1);
				pTLeading     = recon_all_pt->at(0);
				pTSubleading  = recon_all_pt->at(1);
				
				float event_weight = all_total_weight;
				
				if(mass>=70.  &&  mass<=110.) nDYmumu70to110 += 1.*wgt*event_weight;

				
				/////////////////////////////////
				/// MC histo fill statrs here ///
				/////////////////////////////////
				h1Map["hMass"+tsMCname]->Fill(mass,wgt*event_weight);
				h1Map["hyQ"+tsMCname]->Fill(yQ,wgt*event_weight);
				h1Map["hQT"+tsMCname]->Fill(QT,wgt*event_weight);
				h1Map["hEtaLeading"+tsMCname]->Fill(etaLeading,wgt*event_weight);
				h1Map["hEtaSubleading"+tsMCname]->Fill(etaSubleading,wgt*event_weight);
				h1Map["hPhiLeading"+tsMCname]->Fill(phiLeading,wgt*event_weight);
				h1Map["hPhiSubleading"+tsMCname]->Fill(phiSubleading,wgt*event_weight);
				h1Map["hpTLeading"+tsMCname]->Fill(pTLeading,wgt*event_weight);
				h1Map["hpTSubleading"+tsMCname]->Fill(pTSubleading,wgt*event_weight);
				
				///// 2d
				h2Map["hMassCosThetaCS"+tsMCname]->Fill(mass,cosThetaCS,wgt*event_weight);
				h2Map["hMassyQ"+tsMCname]->Fill(mass,yQ,wgt*event_weight);
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
		mass          = K->imass(tlvmureca,tlvmurecb);
		yQ            = K->ySystem(tlvmureca,tlvmurecb);
		QT            = K->QT(tlvmureca,tlvmurecb);
		cosThetaCS    = K->cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
		cosThetaHE    = K->cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
		etaLeading    = eta->at(0);
		etaSubleading = eta->at(1);
		phiLeading    = phi->at(0);
		phiSubleading = phi->at(1);
		pTLeading     = pt->at(0)*MeV2GeV;
		pTSubleading  = pt->at(1)*MeV2GeV;
		
		if(mass>=70.  &&  mass<=110.) nData70to110 += 1.;
		
		///////////////////////////////////
		/// DATA histo fill statrs here ///
		///////////////////////////////////
		h1Map["hMassData"]->Fill(mass);
		h1Map["hyQData"]->Fill(yQ);
		h1Map["hQTData"]->Fill(QT);
		h1Map["hEtaLeadingData"]->Fill(etaLeading);
		h1Map["hEtaSubleadingData"]->Fill(etaSubleading);
		h1Map["hPhiLeadingData"]->Fill(phiLeading);
		h1Map["hPhiSubleadingData"]->Fill(phiSubleading);
		h1Map["hpTLeadingData"]->Fill(pTLeading);
		h1Map["hpTSubleadingData"]->Fill(pTSubleading);
		
		///// 2d
		h2Map["hMassCosThetaCSData"]->Fill(mass,cosThetaCS);
		h2Map["hMassyQData"]->Fill(mass,yQ);
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
	text();

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
			
			if(it->first=="mcLocalControl_Zmumu"  &&
			   truth_all_isValid                  && 
			   recon_all_isValid                  && 
			   truth_all_Mhat>250.) continue;
			
			////////////////////////////////////////////
			//// blocks of analysis go here ////////////
			////////////////////////////////////////////
			hfill("MC", mcName, wgtMap[it->first]); ////
			////////////////////////////////////////////
		}
	}
	
	hscale2Zpeak();
	hdraw();
	save("plots");
}

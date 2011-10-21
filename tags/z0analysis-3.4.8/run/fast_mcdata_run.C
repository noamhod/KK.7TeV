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
TMapTSTS      pathMap;
TMapTSd       wgtMap;
TMapTSd       mcSigmaMap;
TMapTSvf      mcPeriodsNevtsMap;
float nDYmumu70to110 = 0;
float nDYmumu70to110_nopileup = 0;
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

int   all_RunNumber;
float all_pileup_weight;
float all_lumi_pileup_weight;
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
int recon_all_vxp_n;
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

int vxp_n;
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
	
	pvtxt_lumi = new TPaveText(0.4032663,0.166,0.5678392,0.2726,"brNDC"); // 0.2110553,0.5926573,0.3756281,0.6993007 -> for 2d
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

void drawratio(TH1* th1n, TH1* th1d, TString drawopt_n="", TString drawopt_d="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	_DEBUG("draw");

	TString hName = (TString)th1n->GetName();
	hName = hName+"MCratio";
	TString cName = "c"+hName;
	
	cnvMap.insert( make_pair(hName, new TCanvas(cName,cName,600,550)) );
	
	cnvMap[hName]->Divide(1,2);
	TVirtualPad* tvp_hists = cnvMap[hName]->cd(1);
	TVirtualPad* tvp_ratio = cnvMap[hName]->cd(2);
	
	if(logx) tvp_ratio->SetLogx();
	if(logx) tvp_hists->SetLogx();
	if(logy) tvp_hists->SetLogy();
	
	tvp_hists->SetPad(0.00, 0.35, 1.00, 1.00);
	tvp_ratio->SetPad(0.00, 0.00, 1.00, 0.35);

	tvp_hists->SetBottomMargin(0.012);
	tvp_ratio->SetBottomMargin(0.20);
	tvp_ratio->SetTopMargin(0.012);
	
	tvp_ratio->SetTicks(1,1);

	TString cloneName_n = th1n->GetName();
	TString cloneName_d = th1d->GetName();
	TH1D* th1n_tmp = (TH1D*)th1n->Clone(cloneName_n+"_th1n_tmp");
	TH1D* th1d_tmp = (TH1D*)th1d->Clone(cloneName_d+"_th1d_tmp");
	th1n_tmp->Sumw2();
	th1d_tmp->Sumw2();

	TH1D* hr = (TH1D*)th1n->Clone(hName);
	TString sXtitle = (TString)th1n->GetXaxis()->GetTitle();
	// TString sTitle = "#frac{Data}{#sum MC#times wgt};"+sXtitle+";Ratio";
	TString sTitle = ";"+sXtitle+";Ratio";
	hr->SetTitle(sTitle);
	hr->Divide(th1n_tmp,th1d_tmp,1.,1.,"B");

	hr->GetXaxis()->SetLabelSize(0.075);
	hr->GetYaxis()->SetLabelSize(0.075);
	hr->GetXaxis()->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->SetTitleSize(0.075);
	hr->GetYaxis()->SetTitleOffset(0.5);
	hr->SetMinimum(0.);
	hr->SetMaximum(+2.);
	
	if(logx) setlogx(hr);
	
	string name = (string)hName;
	if(name.find("Nvxp")!=string::npos)
	{
		ofstream fWeights("pileup.weights");
		for(Int_t b=1 ; b<=hr->GetNbinsX() ; b++) fWeights << "pu weight: Nvtx=" << b << " -> wgt=" << hr->GetBinContent(b) << " +- " << hr->GetBinError(b) << endl;
		fWeights.close();
	}
	
	TString lName = "l"+hName;
	linMap.insert( make_pair(lName, new TLine(hr->GetXaxis()->GetXmin(),1.,hr->GetXaxis()->GetXmax(),1.)) );

	tvp_hists->cd();
	th1d->Draw(drawopt_d);
	th1n->Draw(drawopt_n+"SAMES");
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	cnvMap[hName]->Update();

	tvp_ratio->cd();
	hr->Draw("e1x1");
	linMap[lName]->Draw("SAMES");
	cnvMap[hName]->Update();
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
	mcSigmaMap.insert( make_pair(name, sigma) );
	pathMap.insert( make_pair(name, fPath) );
	
	
	// http://root.cern.ch/root/roottalk/roottalk03/4281.html
	vector<float> vnEvts;
	TEventList *elist;
	Int_t npassed = 0;
	
	treMap[name]->Draw(">>elist_periodBtoD",  "all_RunNumber==180164");
	elist = (TEventList*)gDirectory->Get("elist_periodBtoD");
	npassed = elist->GetN();  // number of events to pass cuts
	vnEvts.push_back( (float)npassed );
	//treMap[name]->SetEventList(elist);
	treMap[name]->SetEventList(0);
	
	treMap[name]->Draw(">>elist_periodEtoH",  "all_RunNumber==183003");
	elist = (TEventList*)gDirectory->Get("elist_periodEtoH");
	npassed = elist->GetN();  // number of events to pass cuts
	vnEvts.push_back( (float)npassed );
	//treMap[name]->SetEventList(elist);
	treMap[name]->SetEventList(0);
	
	treMap[name]->Draw(">>elist_periodItoK1", "all_RunNumber==185649");
	elist = (TEventList*)gDirectory->Get("elist_periodItoK1");
	npassed = elist->GetN();  // number of events to pass cuts
	vnEvts.push_back( (float)npassed );
	//treMap[name]->SetEventList(elist);
	treMap[name]->SetEventList(0);
	
	treMap[name]->Draw(">>elist_periodFuture","all_RunNumber==185761");
	elist = (TEventList*)gDirectory->Get("elist_periodFuture");
	npassed = elist->GetN();  // number of events to pass cuts
	vnEvts.push_back( (float)npassed );
	// treMap[name]->SetEventList(elist);
	treMap[name]->SetEventList(0);
	
	for(unsigned int i=0 ; i<vnEvts.size() ; i++) _INFO((string)name+" -> events in period "+_s(i+1)+" -> "+_s(vnEvts[i]));
	
	mcPeriodsNevtsMap.insert( make_pair(name,vnEvts) );
}

void setDATAtree()
{
	_DEBUG("setDATAtree");
	
	fName = "/data/hod/2011/NTUPLE/analysisLocalControl.root";
	tName = "allCuts/allCuts_tree";
	file = new TFile(fName,"READ");
	tree = (TTree*)file->Get(tName);
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	if(tsMCname=="DYmumu")
	{
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zmumu.root", "mcLocalControl_Zmumu", 5000000, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
		
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 20000, 7.9862E-01*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb);
		
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 20000, 4.1075E-04*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 20000, 6.6459E-05*nb2fb);
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 20000, *nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 20000, 2.6516E-06*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 20000, 8.9229E-07*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 20000, 2.3957E-07*nb2fb);
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 20000, *nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 20000, 2.4614E-08*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 20000, 1.4001E-08*nb2fb);
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
	
	tree->SetBranchAddress( "all_RunNumber",         &all_RunNumber );
	
	tree->SetBranchAddress( "all_pileup_weight",      &all_pileup_weight );
	tree->SetBranchAddress( "all_lumi_pileup_weight", &all_lumi_pileup_weight );
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
	tree->SetBranchAddress("recon_all_vxp_n", &recon_all_vxp_n);
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
	
	tree->SetBranchAddress("vxp_n", &vxp_n);
	
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
	setlogx(h1Map["hMassDYmumu"]);
	graphics(h1Map["hMassDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hNvxpData", new TH1D("hNvxpData",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpData"],  24,0.8);
	h1Map.insert( make_pair("hNvxpDYmumu", new TH1D("hNvxpDYmumu",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hNvxpData_with_puwgt", new TH1D("hNvxpData_with_puwgt",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpData_with_puwgt"],  24,0.8);
	h1Map.insert( make_pair("hNvxpDYmumu_with_puwgt", new TH1D("hNvxpDYmumu_with_puwgt",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpDYmumu_with_puwgt"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
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

float getDataMCratioNoPileup()
{
	float ratio = (nDYmumu70to110_nopileup>0.) ? nData70to110/nDYmumu70to110_nopileup : 1.;
	_INFO("DATA/DYmumu (no pileup) in 70 to 110 GeV is: "+_s(ratio,8));
	return ratio;
}

void hscale2Zpeak()
{
	float ratio          = getDataMCratio();
	float ratio_nopileup = getDataMCratioNoPileup();
	
	// Scale(h1Map["hNvxpDYmumu"],ratio_nopileup);
	// Scale(h1Map["hNvxpDYmumu"],ratio);
	
	Scale(h1Map["hNvxpDYmumu_with_puwgt"],ratio);
	
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
	drawratio(h1Map["hMassData"], h1Map["hMassDYmumu"], "e1x1", "", dolog, dolog);
	
	setMinMax(h1Map["hNvxpDYmumu"],h1Map["hNvxpData"]);
	draw(h1Map["hNvxpDYmumu"]);
	drawon("hNvxpDYmumu", h1Map["hNvxpData"], "e1x1");
	drawtxton("hNvxpDYmumu");
	drawratio(h1Map["hNvxpData"], h1Map["hNvxpDYmumu"], "e1x1");
	
	setMinMax(h1Map["hNvxpDYmumu_with_puwgt"],h1Map["hNvxpData_with_puwgt"]);
	draw(h1Map["hNvxpDYmumu_with_puwgt"]);
	drawon("hNvxpDYmumu_with_puwgt", h1Map["hNvxpData_with_puwgt"], "e1x1");
	drawtxton("hNvxpDYmumu_with_puwgt");
	drawratio(h1Map["hNvxpData_with_puwgt"], h1Map["hNvxpDYmumu_with_puwgt"], "e1x1");
	
	setMinMax(h1Map["hyQDYmumu"],h1Map["hyQData"],true);
	draw(h1Map["hyQDYmumu"]);
	drawon("hyQDYmumu", h1Map["hyQData"], "e1x1");
	drawtxton("hyQDYmumu");
	drawratio(h1Map["hyQData"], h1Map["hyQDYmumu"], "e1x1");
	
	setMinMax(h1Map["hQTDYmumu"],h1Map["hQTData"],true);
	draw(h1Map["hQTDYmumu"], "", dolog, dolog);
	drawon("hQTDYmumu", h1Map["hQTData"], "e1x1");
	drawtxton("hQTDYmumu");
	drawratio(h1Map["hQTData"], h1Map["hQTDYmumu"], "e1x1", "", dolog, dolog);
	
	setMinMax(h1Map["hEtaLeadingDYmumu"],h1Map["hEtaLeadingData"]);
	draw(h1Map["hEtaLeadingDYmumu"]);
	drawon("hEtaLeadingDYmumu", h1Map["hEtaLeadingData"], "e1x1");
	drawtxton("hEtaLeadingDYmumu");
	drawratio(h1Map["hEtaLeadingData"], h1Map["hEtaLeadingDYmumu"], "e1x1");
	setMinMax(h1Map["hEtaSubleadingDYmumu"],h1Map["hEtaSubleadingData"]);
	draw(h1Map["hEtaSubleadingDYmumu"]);
	drawon("hEtaSubleadingDYmumu", h1Map["hEtaSubleadingData"], "e1x1");
	drawtxton("hEtaSubleadingDYmumu");
	drawratio(h1Map["hEtaSubleadingData"], h1Map["hEtaSubleadingDYmumu"], "e1x1");
	
	setMinMax(h1Map["hPhiLeadingDYmumu"],h1Map["hPhiLeadingData"]);
	draw(h1Map["hPhiLeadingDYmumu"]);
	drawon("hPhiLeadingDYmumu", h1Map["hPhiLeadingData"], "e1x1");
	drawtxton("hPhiLeadingDYmumu");
	drawratio(h1Map["hPhiLeadingData"], h1Map["hPhiLeadingDYmumu"], "e1x1");
	setMinMax(h1Map["hPhiSubleadingDYmumu"],h1Map["hPhiSubleadingData"]);
	draw(h1Map["hPhiSubleadingDYmumu"]);
	drawon("hPhiSubleadingDYmumu", h1Map["hPhiSubleadingData"], "e1x1");
	drawtxton("hPhiSubleadingDYmumu");
	drawratio(h1Map["hPhiSubleadingData"], h1Map["hPhiSubleadingDYmumu"], "e1x1");
	
	setMinMax(h1Map["hpTLeadingDYmumu"],h1Map["hpTLeadingData"],true);
	draw(h1Map["hpTLeadingDYmumu"], "", dolog, dolog);
	drawon("hpTLeadingDYmumu", h1Map["hpTLeadingData"], "e1x1");
	drawtxton("hpTLeadingDYmumu");
	drawratio(h1Map["hpTLeadingData"], h1Map["hpTLeadingDYmumu"], "e1x1", "", dolog, dolog);
	setMinMax(h1Map["hpTSubleadingDYmumu"],h1Map["hpTSubleadingData"],true);
	draw(h1Map["hpTSubleadingDYmumu"], "", dolog, dolog);
	drawon("hpTSubleadingDYmumu", h1Map["hpTSubleadingData"], "e1x1");
	drawtxton("hpTSubleadingDYmumu");
	drawratio(h1Map["hpTSubleadingData"], h1Map["hpTSubleadingDYmumu"], "e1x1", "", dolog, dolog);
	
	
	///// 2d
	h2Map["hMassCosThetaCSData"]->SetMinimum( getXYmin(h2Map["hMassCosThetaCSData"]) );
	draw(h2Map["hMassCosThetaCSData"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSData", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSData", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSData");
	h2Map["hMassCosThetaCSDYmumu"]->SetMinimum( getXYmin(h2Map["hMassCosThetaCSDYmumu"]) );
	draw(h2Map["hMassCosThetaCSDYmumu"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSDYmumu", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSDYmumu", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSDYmumu");
	
	draw(h2Map["hMassyQData"], "COLZ", dolog, !dolog, dolog);
	h2Map["hMassyQData"]->SetMinimum( getXYmin(h2Map["hMassyQData"]) );
	drawon("hMassyQData", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQData", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQData");
	h2Map["hMassyQDYmumu"]->SetMinimum( getXYmin(h2Map["hMassyQDYmumu"]) );
	draw(h2Map["hMassyQDYmumu"], "COLZ", dolog, !dolog, dolog);
	drawon("hMassyQDYmumu", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQDYmumu", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQDYmumu");
}

float dummyPileupWeight(int Nvtx)
{
	float wgt = -999.;
	float err = -999.;
	switch(Nvtx)
	{
		case 1:  wgt=0.;         err=0.;          break;
		case 2:  wgt=1.25141;    err=0.00577822;  break;
		case 3:  wgt=1.16239;    err=0.00222276;  break;
		case 4:  wgt=1.05372;    err=0.000841156; break;
		case 5:  wgt=0.9909;     err=0.000282838; break;
		case 6:  wgt=0.959231;   err=0.00057051;  break;
		case 7:  wgt=0.960658;   err=0.000598648; break;
		case 8:  wgt=1.01366;    err=0.000420445; break;
		case 9:  wgt=1.11505;    err=0.00157366;  break;
		case 10: wgt=1.2236;     err=0.0029407;   break;
		case 11: wgt=1.31968;    err=0.00476801;  break;
		case 12: wgt=1.33966;    err=0.00640612;  break;
		case 13: wgt=1.13993;    err=0.00463242;  break;
		case 14: wgt=0.807529;   err=0.00522407;  break;
		case 15: wgt=0.502941;   err=0.00724853;  break;
		case 16: wgt=0.286545;   err=0.00710636;  break;
		case 17: wgt=0.15919;    err=0.00605587;  break;
		case 18: wgt=0.0809666;  err=0.00481376;  break;
		case 19: wgt=0.0428478;  err=0.00379524;  break;
		case 20: wgt=0.0262842;  err=0.00332082;  break;
		case 21: wgt=0.0117188;  err=0.00248377;  break;
		case 22: wgt=0.00716806; err=0.00215349;  break;
		case 23: wgt=0.00416974; err=0.00186087;  break;
		case 24: wgt=0.0022554;  err=0.00159301;  break;
		case 25: wgt=0.00300959; err=0.0021249;   break;
		case 26: wgt=0.00408355; err=0.00288161;  break;
		case 27: wgt=0.;         err=0.;          break;
		case 28: wgt=0.00400175; err=0.00399374;  break;
		case 29: wgt=0.;         err=0.;          break;
		case 30: wgt=0.;         err=0.;          break;
		case 31: wgt=0.;         err=0.;          break;
		case 32: wgt=0.;         err=0.;          break;
		case 33: wgt=0.;         err=0.;          break;
		case 34: wgt=0.;         err=0.;          break;
		case 35: wgt=0.;         err=0.;          break;
		default: wgt=-999.; _WARNING("in dummyPileupWeight -> the value Nvtx="+_s(Nvtx)+" is not supported"); break;
	}
	return wgt;
}

float getLumiWeight(TString mcName, int mcRunNumber)
{
	_DEBUG("getLumiWeight");

	/*//////////////////////////////////////////////////////////////////////
	B->D:   [178044->180481]: 187.91  pb-1 EF_mu22         wL=0.0527434243
	E->H:   [180614->184169]: 1015.2  pb-1 EF_mu22         wL=0.284950904
	I->K1:  [185353->186493]: 390.364 pb-1 EF_mu22         wL=0.241495049
			[186516->186934]: 470.015 pb-1 EF_mu22_medium
	Future: [186965->190120]: 1499.23 pb-1 EF_mu22_medium  wL=0.420810622
	----------------------------------------------------------------------
	Total:  [178044->190120]: 3562.719 pb-1
	*///////////////////////////////////////////////////////////////////////
	
	int iPeriod = 0;
	float Ldata = 1.;
	if     (mcRunNumber==180164) // periodBtoD
	{
		iPeriod = 0;
		Ldata = 0.18791;
	}
	else if(mcRunNumber==183003) // periodEtoH
	{
		iPeriod = 1;
		Ldata = 1.0152;
	}
	else if(mcRunNumber==185649) // periodItoK1
	{
		iPeriod = 2;
		Ldata = 0.860379;
	}
	else if(mcRunNumber==185761) // periodFuture
	{
		iPeriod = 3;
		Ldata = 1.49923;
	}
	else
	{
		_ERROR("unsupported RunNumber, exitting now");
		exit(-1);
	}
	float N     = mcPeriodsNevtsMap[mcName][iPeriod];
	float sigma = mcSigmaMap[mcName];
	float Lmc   = N/sigma;
	
	return Ldata/Lmc;
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
				
				
				
				/////////////////////////
				/// weights handeling ///
				/////////////////////////
				float event_weight          = 1.;
				float event_weight_nopileup = 1.;
				float dummy_pileup_weight   = 1.;
				
				event_weight = all_EW_kfactor_weight  *
							   all_QCD_kfactor_weight *
							   all_mcevent_weight;
				
				// option 1 for the event weight with pileup
				// event_weight = all_total_weight;
				
				// option 2 for the event weight with pileup and luminosity weight
				// These are taken from https://twiki.cern.ch/twiki/bin/viewauth/Atlas/MC11a
				// or from the luminosity itself, both done in the method analysisSkeleton::getPileupPeriodsWeight
				// event_weight *= all_pileup_weight *
								// all_lumi_pileup_weight; // equivalent to the line above
								
				// option 3 for the event weight with pileup and luminosity weight, normalized to the luminosity itself
				// event_weight *= all_pileup_weight;
				// if     (all_RunNumber==180164) event_weight *= 0.0527434243; // periodBtoD
				// else if(all_RunNumber==183003) event_weight *= 0.284950904;  // periodEtoH
				// else if(all_RunNumber==185649) event_weight *= 0.241495049;  // periodItoK1
				// else if(all_RunNumber==185761) event_weight *= 0.420810622;  // periodFuture
				// else
				// {
					// _WARNING("unsupported RunNumber, setting event_weight to 0.");
					// event_weight *= 0.;
				// }
				
				// option 4 for the event weight with pileup but with luminosity weight,
				// taken as wgt = Ldata/(Nperiod/sigma) where sigma is the MC sample cross section,
				// and Nperiod is the number of events in each of the four "dummy periods" that are in the MC sample.
				// So, the luminosity weight is calculated separately for each "dummy period" (this is done in the method setMCtree)
				// and there's no need to take the "pileup_luminosity_..." weigths from the ntuple
				event_weight *= all_pileup_weight;
				
				// option 5 for the event weight with pileup
				// dummy_pileup_weight = dummyPileupWeight(recon_all_vxp_n);
				// if(dummy_pileup_weight<0.) return;
				// event_weight *= dummy_pileup_weight;
				
				// for the event weight without pileup
				event_weight_nopileup = all_EW_kfactor_weight  *
										all_QCD_kfactor_weight *
										all_mcevent_weight;
				
				// for the Z peak normalization
				if(mass>=70.  &&  mass<=110.) nDYmumu70to110          += 1.*wgt*event_weight;
				if(mass>=70.  &&  mass<=110.) nDYmumu70to110_nopileup += 1.*wgt*event_weight_nopileup;
				
				
				
				/////////////////////////////////
				/// MC histo fill statrs here ///
				/////////////////////////////////
				h1Map["hNvxp"+tsMCname]->Fill(recon_all_vxp_n,wgt*event_weight_nopileup);
				h1Map["hNvxp"+tsMCname+"_with_puwgt"]->Fill(recon_all_vxp_n,wgt*event_weight);
				
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
		h1Map["hNvxpData"]->Fill(vxp_n);
		h1Map["hNvxpData_with_puwgt"]->Fill(vxp_n);
		
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
			// hfill("MC", mcName, wgtMap[it->first]); //////////////////////
			hfill("MC", mcName, getLumiWeight(it->first,all_RunNumber)); ////
			/////////////////////////////////////////////////////////////////
		}
	}
	
	hscale2Zpeak();
	hdraw();
	save("plots");
}

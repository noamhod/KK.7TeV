#include "../include/basicIncludes.h"

TFile* file;
TTree* tree;
TString fName;
TString tName;
TMapTSP2TCNV  cnvMap;
TMapTSP2TOBJ  oMap;
TMapTSP2TH1   h1Map;
TMapTSP2TH2   h2Map;
TMapTSP2TLINE linMap;
TMapTSP2TTREE treMap;
TMapTSd       wgtMap;

Bool_t isMC=true;
Bool_t dolog=true;
kinematics kin;
TLorentzVector* tlva = new TLorentzVector;
TLorentzVector* tlvb = new TLorentzVector;
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
void setisMC(Bool_t ismc)
{
	isMC = ismc;
}

void draw(TObject* tobj, TString oName, TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog)
{
	TString cName = "c"+oName;
	cnvMap.insert( make_pair(oName, new TCanvas(cName,cName,600,400)) );
	if(logx) cnvMap[oName]->SetLogx();
	if(logy) cnvMap[oName]->SetLogy();
	cnvMap[oName]->cd();
	tobj->Draw(drawopt);
}

void drawon(TString existing_oName, TObject* tobj, TString drawopt="")
{
	cnvMap[existing_oName]->cd();
	tobj->Draw(drawopt+" SAMES");
}

void save(TString oDir)
{
	for(TMapTSP2TCNV::iterator it=cnvMap.begin() ; it!=cnvMap.end() ; ++it)
	{
		TString pName = oDir+"/"+it->first;
		it->second->SaveAs(pName+".png");
		it->second->SaveAs(pName+".eps");
		it->second->SaveAs(pName+".pdf");
		it->second->SaveAs(pName+".root");
		it->second->SaveAs(pName+".C");
	}
	
	TString pName = (isMC) ? oDir+"/mchistograms.root" : oDir+"/datahistograms.root";
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
	file = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)file->Get("truth/truth_tree")->Clone("")) );
	wgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
}

///////////////////////////
void settrees()
{
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
	
	settree("/tmp/hod/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 19999, 0.0086861*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 19996, 0.00041431*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 19993, 0.000067464*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 15994, 0.000011168*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 19992, 0.0000027277*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 19995, 0.00000091646*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 19993, 0.00000024942*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 19997, 0.000000076876*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 19993, 0.000000026003*nb2fb);
	settree("/tmp/hod/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 19996, 0.000000015327*nb2fb);
}
///////////////////////////


void mcbranches()
{
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
	tree->SetBranchAddress("recon_all_m", &recon_all_eta);
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
	h1Map.insert( make_pair("hMass", new TH1D("hMass",";m_{#mu#mu} GeV;Events",250,70.,2500.)) );
	h1Map.insert( make_pair("hbetaZ", new TH1D("hbetaZ",";#beta_{Q}^{z};Events",200,-1.,1.)) );
	h1Map.insert( make_pair("hcosalpha_rec", new TH1D("hcosalpha_rec","#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q};#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q}/#beta_{Q}^{rec}p_{q};Events",50,-1.,1.)) );
	h1Map.insert( make_pair("hcosalpha_tru", new TH1D("hcosalpha_tru","#vec{#beta}_{Q}^{tru}#bullet#vec{p}_{q};#vec{#beta}_{Q}^{tru}#bullet#vec{p}_{q}/#beta_{Q}^{tru}p_{q};Events",50,-1.,1.)) );
	h1Map.insert( make_pair("hcosalpha_quarks", new TH1D("hcosalpha_quarks","#vec{#beta}_{Q}^{tru}#bullet#vec{#beta}_{Q}^{q#bar{q}};#vec{#beta}_{Q}^{tru}#bullet#vec{#beta}_{Q}^{q#bar{q}}/#beta_{Q}^{tru}#beta_{Q}^{q#bar{q}};Events",50,-1.,1.)) );
	h1Map.insert( make_pair("hyQ", new TH1D("hyQ",";y_{Q};Events",100,-2.5,+2.5)) );
	h1Map.insert( make_pair("hyQabs", new TH1D("hyQabs",";|y_{Q}|;Events",50,0.,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_rec_denominator", new TH1D("hprobyQ_rec_denominator",";y_{Q};P(y_{Q})",30,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_rec_ratio", new TH1D("hprobyQ_rec_ratio","P(y_{Q})=#LT#vec{#beta}_{Q}^{rec}#bullet#vec{p}_{q}<0#GT/All;y_{Q};P",30,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_tru_denominator", new TH1D("hprobyQ_tru_denominator",";y_{Q};P(y_{Q})",30,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_tru_ratio", new TH1D("hprobyQ_tru_ratio","P(y_{Q})=#LT#vec{#beta}_{Q}^{tru}#bullet#vec{p}_{q}<0#GT/All;y_{Q};P",30,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_quarks_denominator", new TH1D("hprobyQ_quarks_denominator",";y_{Q};P(y_{Q})",30,-2.5,+2.5)) );
	h1Map.insert( make_pair("hprobyQ_quarks_ratio", new TH1D("hprobyQ_quarks_ratio","P(y_{Q})=#LT#vec{#beta}_{Q}^{tru}#bullet#vec{#beta}_{Q}^{q#bar{q}}<0#GT/All;y_{Q};P",30,-2.5,+2.5)) );
	
	h2Map.insert( make_pair("hMassCosThetaCS", new TH2D("hMassCosThetaCS",";m_{#mu#mu} GeV;cos(#theta*);Events",250,70.,2500., 50,-1.,+1)) );
	linMap.insert( make_pair("hMassCosThetaCS_horline", new TLine(70.,0.,2500.,0.)) );
	linMap.insert( make_pair("hMassCosThetaCS_lonline", new TLine(646.33,-1.,646.33,+1.)) );
	
	h2Map.insert( make_pair("hMassyQ", new TH2D("hMassyQ",";m_{#mu#mu} GeV;y_{Q};Events",250,70.,2500., 50,-2.5,+2.5)) );
	linMap.insert( make_pair("hMassyQ_horline", new TLine(70.,0.,2500.,0.)) );
	linMap.insert( make_pair("hMassyQ_lonline", new TLine(646.33,-2.5,646.33,+2.5)) );

	h2Map.insert( make_pair("hbetaZyQ", new TH2D("hbetaZyQ",";#beta_{Q}^{z};y_{Q};Events",50,-1.,+1, 50,-2.5,+2.5)) );
	h2Map.insert( make_pair("hbetaabsyQabs", new TH2D("hbetaabsyQabs",";|#beta_{Q}|;|y_{Q}|;Events",50,0.,+1., 50,0.,+2.5)) );
	h2Map.insert( make_pair("hyQCosThetaCS", new TH2D("hyQCosThetaCS",";y_{Q};cos(#theta*);Events",50,-2.5,+2.5, 50,-1.,+1)) );
	h2Map.insert( make_pair("hyQCosThetaCS_tru", new TH2D("hyQCosThetaCS_tru",";y_{Q};cos(#theta*);Events",40,-2.5,+2.5, 40,-1.,+1)) );
	h2Map.insert( make_pair("hyQCosThetaCS_acc", new TH2D("hyQCosThetaCS_acc","Acceptance;y_{Q};cos(#theta*)",40,-2.5,+2.5, 40,-1.,+1)) );
	h2Map.insert( make_pair("hbetaZyQtru", new TH2D("hbetaZyQtru",";#beta_{Q}^{z:tru};y_{Q}^{tru};Events",50,-1.,+1, 50,-2.5,+2.5)) );
}

void hdraw()
{	
	draw(h1Map["hMass"], "hMass", "", dolog, dolog);
	draw(h1Map["hbetaZ"], "hbetaZ");
	draw(h1Map["hcosalpha_rec"], "hcosalpha_rec", "", !dolog, dolog);
	draw(h1Map["hcosalpha_tru"], "hcosalpha_tru", "", !dolog, dolog);
	draw(h1Map["hcosalpha_quarks"], "hcosalpha_quarks", "", !dolog, dolog);
	draw(h1Map["hyQ"], "hyQ");
	draw(h1Map["hyQabs"], "hyQabs");
	

	h1Map["hprobyQ_rec_ratio"]->Divide(h1Map["hprobyQ_rec_denominator"]);
	h1Map["hprobyQ_rec_ratio"]->SetMinimum(0.);
	h1Map["hprobyQ_rec_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobyQ_rec_ratio"], "hprobyQ_rec_ratio");
	h1Map["hprobyQ_tru_ratio"]->Divide(h1Map["hprobyQ_tru_denominator"]);
	h1Map["hprobyQ_tru_ratio"]->SetMinimum(0.);
	h1Map["hprobyQ_tru_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobyQ_tru_ratio"], "hprobyQ_tru_ratio");
	h1Map["hprobyQ_quarks_ratio"]->Divide(h1Map["hprobyQ_quarks_denominator"]);
	h1Map["hprobyQ_quarks_ratio"]->SetMinimum(0.);
	h1Map["hprobyQ_quarks_ratio"]->SetMaximum(1.);
	draw(h1Map["hprobyQ_quarks_ratio"], "hprobyQ_quarks_ratio");
	
	
	h2Map["hyQCosThetaCS_acc"]->Divide(h2Map["hyQCosThetaCS_tru"]);
	h2Map["hyQCosThetaCS_acc"]->SetMinimum(0.);
	h2Map["hyQCosThetaCS_acc"]->SetMaximum(1.);
	draw(h2Map["hyQCosThetaCS_acc"], "hyQCosThetaCS_acc", "COLZ");
	
	draw(h2Map["hMassyQ"], "hMassyQ", "COLZ", dolog);
	drawon("hMassyQ", linMap["hMassyQ_horline"]);
	drawon("hMassyQ", linMap["hMassyQ_lonline"]);
	draw(h2Map["hbetaabsyQabs"], "hbetaabsyQabs", "COLZ");
	draw(h2Map["hMassCosThetaCS"], "hMassCosThetaCS", "COLZ", dolog);
	drawon("hMassCosThetaCS", linMap["hMassCosThetaCS_horline"]);
	drawon("hMassCosThetaCS", linMap["hMassCosThetaCS_lonline"]);
	draw(h2Map["hyQCosThetaCS"], "hyQCosThetaCS", "COLZ");
	draw(h2Map["hbetaZyQ"], "hbetaZyQ", "COLZ");
	draw(h2Map["hbetaZyQtru"], "hbetaZyQtru", "COLZ");
}

void hfill(Double_t wgt=1.)
{
	float betax_rec;	
	float betay_rec;	
	float betaz_rec;
	float betamag_rec;
			
	float betax_tru;	
	float betay_tru;	
	float betaz_tru;	
	float betamag_tru;
		
	float betax_quarks;	
	float betay_quarks;	
	float betaz_quarks;	
	float betamag_quarks;
	
	float cosalpha_rec;
	float cosalpha_tru;
	float cosalpha_quarks;
	float betaztru;

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
			
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(0), truth_all_mc_eta->at(0), truth_all_mc_phi->at(0), truth_all_mc_m->at(0));
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(1), truth_all_mc_eta->at(1), truth_all_mc_phi->at(1), truth_all_mc_m->at(1));
			betax_tru = kin.betaSystem(tlva->X(), tlvb->X(), tlva->E(), tlvb->E());	
			betay_tru = kin.betaSystem(tlva->Y(), tlvb->Y(), tlva->E(), tlvb->E());	
			betaz_tru = kin.betaSystem(tlva->Z(), tlvb->Z(), tlva->E(), tlvb->E());	
			betamag_tru = sqrt(betax_tru*betax_tru+betay_tru*betay_tru+betaz_tru*betaz_tru);
			
			tlva->SetPtEtaPhiM(truth_all_partons_mc_pt->at(0), truth_all_partons_mc_eta->at(0), truth_all_partons_mc_phi->at(0), truth_all_partons_mc_m->at(0));
			tlva->SetPtEtaPhiM(truth_all_partons_mc_pt->at(1), truth_all_partons_mc_eta->at(1), truth_all_partons_mc_phi->at(1), truth_all_partons_mc_m->at(1));
			betax_quarks = kin.betaSystem(tlva->X(), tlvb->X(), tlva->E(), tlvb->E());	
			betay_quarks = kin.betaSystem(tlva->Y(), tlvb->Y(), tlva->E(), tlvb->E());	
			betaz_quarks = kin.betaSystem(tlva->Z(), tlvb->Z(), tlva->E(), tlvb->E());	
			betamag_quarks = sqrt(betax_quarks*betax_quarks+betay_quarks*betay_quarks+betaz_quarks*betaz_quarks);
			
			int iquark = (truth_all_partons_mc_pdgId->at(0)>0) ? 0 : 1;
			tv3a->SetPtEtaPhi(truth_all_partons_mc_pt->at(iquark), truth_all_partons_mc_eta->at(iquark), truth_all_partons_mc_phi->at(iquark));
			
			if(recon_all_isValid)
			{
				tv3b->SetXYZ(betax_rec, betay_rec, betaz_rec);
				cosalpha_rec = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
				h1Map["hcosalpha_rec"]->Fill(cosalpha_rec,wgt);
			}
			
			tv3b->SetXYZ(betax_tru, betay_tru, betaz_tru);
			cosalpha_tru = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
			h1Map["hcosalpha_tru"]->Fill(cosalpha_tru,wgt);
			
			tv3a->SetXYZ(betax_quarks, betay_quarks, betaz_quarks);
			tv3b->SetXYZ(betax_tru, betay_tru, betaz_tru);
			cosalpha_quarks = tv3a->Dot(*tv3b)/(tv3a->Mag()*tv3b->Mag());
			h1Map["hcosalpha_quarks"]->Fill(cosalpha_quarks,wgt);
			
			if(recon_all_isValid) 
			{
				if(cosalpha_rec<=0.)    h1Map["hprobyQ_rec_ratio"]->Fill(recon_all_ySystem,wgt);
				h1Map["hprobyQ_rec_denominator"]->Fill(recon_all_ySystem,wgt);
			}
			
			if(cosalpha_tru<=0.)    h1Map["hprobyQ_tru_ratio"]->Fill(truth_all_ySystem,wgt);
			h1Map["hprobyQ_tru_denominator"]->Fill(truth_all_ySystem,wgt);
			
			if(cosalpha_quarks<=0.) h1Map["hprobyQ_quarks_ratio"]->Fill(truth_all_ySystem,wgt);
			h1Map["hprobyQ_quarks_denominator"]->Fill(truth_all_ySystem,wgt);
			
			if(recon_all_isValid) 
			{
				h1Map["hMass"]->Fill(recon_all_Mhat,wgt);
				h1Map["hbetaZ"]->Fill(betaz_rec,wgt);
				h1Map["hyQ"]->Fill(recon_all_ySystem,wgt);
				h1Map["hyQabs"]->Fill(fabs(recon_all_ySystem),wgt);
				
				h2Map["hMassyQ"]->Fill(recon_all_Mhat,recon_all_ySystem,wgt);
				h2Map["hMassCosThetaCS"]->Fill(recon_all_Mhat,recon_all_CosThetaCS,wgt);
				h2Map["hyQCosThetaCS"]->Fill(recon_all_ySystem,recon_all_CosThetaCS,wgt);
				h2Map["hyQCosThetaCS_acc"]->Fill(recon_all_ySystem,recon_all_CosThetaCS,wgt);
				h2Map["hbetaZyQ"]->Fill(betaz_rec,recon_all_ySystem,wgt);
				h2Map["hbetaabsyQabs"]->Fill(betamag_rec,fabs(recon_all_ySystem),wgt);
			}
			
			tlva->SetPtEtaPhiM(truth_all_mc_pt->at(0), truth_all_mc_eta->at(0), truth_all_mc_phi->at(0), truth_all_mc_m->at(0));
			tlvb->SetPtEtaPhiM(truth_all_mc_pt->at(1), truth_all_mc_eta->at(1), truth_all_mc_phi->at(1), truth_all_mc_m->at(1));
			betaztru = kin.betaSystem(tlva->Pz(), tlvb->Pz(), tlva->E(), tlvb->E());
			h2Map["hbetaZyQtru"]->Fill(betaztru,truth_all_ySystem,wgt);
			h2Map["hyQCosThetaCS_tru"]->Fill(truth_all_ySystem,truth_all_CosThetaCS,wgt);
		}
	}
	else
	{
		float betax_rec = kin.betaSystem(px->at(0), px->at(1), E->at(0), E->at(1));	
		float betay_rec = kin.betaSystem(py->at(0), py->at(1), E->at(0), E->at(1));	
		float betaz_rec = kin.betaSystem(pz->at(0), pz->at(1), E->at(0), E->at(1));
		float betamag_rec = sqrt(betax_rec*betax_rec+betay_rec*betay_rec+betaz_rec*betaz_rec);
		
		h1Map["hMass"]->Fill(Mhat*TeV2GeV);
		h1Map["hbetaZ"]->Fill(betaz_rec);
		h1Map["hyQ"]->Fill(Ysystem);
		h1Map["hyQabs"]->Fill(fabs(Ysystem));
		
		h2Map["hMassyQ"]->Fill(Mhat*TeV2GeV,Ysystem);
		h2Map["hMassCosThetaCS"]->Fill(Mhat*TeV2GeV,CosThetaCS);
		h2Map["hyQCosThetaCS"]->Fill(Ysystem,CosThetaCS);
		h2Map["hbetaZyQ"]->Fill(betaz_rec,Ysystem);
		h2Map["hbetaabsyQabs"]->Fill(betamag_rec,fabs(Ysystem));
	}
}

void init(TTree* t=NULL)
{
	if(t==NULL)
	{
		if(isMC)
		{
			// fName = "/data/hod/pythia8_ntuples/ATLASZP/mcLocalControl_Zprime_mumu_SSM1500.root";
			fName = "/tmp/hod/mcLocalControl_Zprime_mumu_SSM1500.root";
			tName = "truth/truth_tree";
		}
		else
		{
			// fName = "../data/merged.root";
			fName = "/tmp/hod/merged.root";
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
	msglvl[DBG] = VISUAL;
	msglvl[INF] = VISUAL;
	msglvl[WRN] = VISUAL;
	msglvl[ERR] = VISUAL;
	msglvl[FAT] = VISUAL;

	style();
	hbook();

	if(!isMC)
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

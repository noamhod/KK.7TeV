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

bool drawGmm = false;

TMapTSTC cGmm;
TMapTSTC cZprime;
TMapTSTC cZprimeTemplate;
TMapTSTC cKKTemplate;

double mZprimeMin = 500.;
double mZprimeMax = 2000.;
double dMZprime   = 250.;
	
double mGmmMin = 1750.;
double mGmmMax = 2250.;
double dMGmm   = 250.;

TFile* file;
TTree* tree;
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
TMapTSd       wgtMap;
TMapTSd       mcSigmaMap;
TMapTSvf      mcPeriodsNevtsMap;
float nMCall70to110 = 0;
float nMCall70to110_nopileup = 0;
float nData70to110   = 0;

Bool_t isMC=true;
Bool_t isZprime=false;
Bool_t dolog=true;

//kinematics* K;

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
float all_intime_pileup_weight;
float all_outoftime_pileup_weight;
float all_lumi_pileup_weight;
float all_EW_kfactor_weight;
float all_QCD_kfactor_weight;
float all_mcevent_weight;
float all_total_weight;
unsigned int all_randomized_decision;

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

vector<double>* truth_all_vKKwgt;
vector<double>* truth_all_vZPwgt;
vector<double>* truth_all_vBSMmass;

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


TH1D* stitch(vector<TH1D*>& vh, TString name="", TString titles="")
{
	const unsigned int vhsize   = vh.size();
	const unsigned int nbins    = vh[0]->GetNbinsX();
	const unsigned int nlogbins = vhsize*nbins;
	
	Double_t xlogbins[nlogbins+1];
	unsigned int j = 0;
	xlogbins[j] = vh[0]->GetBinLowEdge(1);
	for(unsigned int i=0 ; i<vhsize ; i++)
	{
		Double_t offset = i*(vh[0]->GetBinLowEdge(nbins)+vh[0]->GetBinWidth(nbins));
		for(unsigned int b=1 ; b<=nbins ; b++)
		{
			j++;
			xlogbins[j] = vh[0]->GetBinLowEdge(b)+vh[0]->GetBinWidth(b) + offset;
		}
	}
	
	TH1D* hStitched = new TH1D(name, titles, nlogbins, xlogbins);
	
	Int_t noffsetbins = vh[0]->GetNbinsX();
	for(unsigned int i=0 ; i<vhsize ; i++)
	{
		for(int b=1 ; b<=vh[i]->GetNbinsX() ; b++)
		{
			Int_t bin = b + (Int_t)(i*noffsetbins);
			hStitched->SetBinContent(bin, vh[i]->GetBinContent(b));
		}
	}
	return hStitched;
}


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
	pvtxt_atlas = new TPaveText(0.4032663,0.2897141,0.5678392,0.3840259,"brNDC"); // 0.2110553,0.7097902,0.3756281,0.8041958 -> for 2d
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
	
	leg = new TLegend(0.6627517,0.60,0.7919463,0.87,NULL,"brNDC");
	leg->SetFillStyle(4000); //will be transparent
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->AddEntry(h1Map["hMassData"],"Data","lep");
	leg->AddEntry(h1Map["hMassDYmumu"],"DYmumu","f");
	leg->AddEntry(h1Map["hMassDiboson"],"Diboson","f");
	if(drawGmm) leg->AddEntry(h1Map["hMassGmm_01_1750"],"1750 GeV G*","l");
	if(drawGmm) leg->AddEntry(h1Map["hMassGmm_01_2000"],"2000 GeV G*","l");
	if(drawGmm) leg->AddEntry(h1Map["hMassGmm_01_2250"],"2250 GeV G*","l");
	leg->AddEntry(h1Map["hMassZprime_SSM1000"],"Z'_{SSM} 1.00 TeV","l");
	leg->AddEntry(h1Map["hMassZprime_SSM1500"],"Z'_{SSM} 1.50 TeV","l");
	leg->AddEntry(h1Map["hMassZprime_SSM1750"],"Z'_{SSM} 1.75 TeV","l");
	leg->AddEntry(h1Map["hMassZprime_SSM2000"],"Z'_{SSM} 2.00 TeV","l");
}

void templateText(TString tsMCname, TString tsMClegEntry)
{
	if(leg_template==NULL)
	{
		leg_template = new TLegend(0.6,0.70,0.7919463,0.87,NULL,"brNDC");
		leg_template->SetFillStyle(4000); //will be transparent
		leg_template->SetFillColor(0);
		leg_template->SetTextFont(42);
	}
	else leg_template->Clear();
	if(!tsMCname.Contains("KK"))
	{
		leg_template->AddEntry(h1Map[tsMCname+"_template"],tsMClegEntry+" Template","f");
		leg_template->AddEntry(h1Map[tsMCname],tsMClegEntry,"l");
	}
	else
	{
		leg_template->AddEntry(h1Map[tsMCname],tsMClegEntry+" Template","l");
		leg_template->AddEntry(h1Map["hMassDYmumu"],"DY","f");
	}
}


void draw(TObject* tobj, TString newname="", TString drawopt="", Bool_t logx=!dolog, Bool_t logy=!dolog, Bool_t logz=!dolog)
{
	_DEBUG("draw");

	TString oName = (newname=="") ? (TString)tobj->GetName() : newname;
	TString cName = "c"+oName;
	cnvMap.insert( make_pair(oName, new TCanvas(cName,cName,600,400)) );
	if(logx) cnvMap[oName]->SetLogx();
	if(logy) cnvMap[oName]->SetLogy();
	if(logz) cnvMap[oName]->SetLogz();
	cnvMap[oName]->cd();
	tobj->Draw(drawopt);
	cnvMap[oName]->RedrawAxis();
	cnvMap[oName]->Update();
}

void drawratio(TH1* th1n, TH1* th1d, vector<TString>& vtsMCbgds, TString drawopt_n="", TString drawopt_d="", Bool_t logx=!dolog, Bool_t logy=!dolog)
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
	TString sTitle = ";"+sXtitle+";Data/sumMC";
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
	for(int v=0 ; v<(int)vtsMCbgds.size() ; v++)
	{
		// th1d->Draw(drawopt_d);
		// th1n->Draw(drawopt_n+"SAMES");
		if(v==0) h1Map[vtsMCbgds[v]]->Draw(drawopt_d);
		else     h1Map[vtsMCbgds[v]]->Draw(drawopt_d+"SAMES");
	}
	th1n->Draw(drawopt_n+"SAMES");
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg->Draw("SAMES");
	cnvMap[hName]->Update();
	tvp_hists->RedrawAxis();

	tvp_ratio->cd();
	hr->Draw("e1x1");
	linMap[lName]->Draw("SAMES");
	cnvMap[hName]->Update();
	tvp_ratio->RedrawAxis();
}

void drawon(TString existing_oName, TObject* tobj, TString drawopt="", Int_t padNumber=-1)
{
	_DEBUG("drawon");

	if(padNumber<1) cnvMap[existing_oName]->cd();
	else            cnvMap[existing_oName]->cd(padNumber);
	if(drawopt=="") tobj->Draw("SAMES");
	else            tobj->Draw(drawopt+" SAMES");
	cnvMap[existing_oName]->RedrawAxis();
	cnvMap[existing_oName]->Update();
}

void drawtxton(TString existing_oName, bool is2d=false)
{
	_DEBUG("drawtxton");

	cnvMap[existing_oName]->cd();
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	if(!is2d) leg->Draw("SAMES");
}

void drawtemplatetxton(TString existing_oName)
{
	_DEBUG("drawtxton");

	cnvMap[existing_oName]->cd();
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg_template->DrawClone("SAMES");
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
	_INFO("");
	f->cd();
	_INFO("");
	for(TMapTSP2TH1::iterator it=h1Map.begin() ; it!=h1Map.end() ; ++it) it->second->Write();
	_INFO("");
	for(TMapTSP2TH2::iterator it=h2Map.begin() ; it!=h2Map.end() ; ++it) it->second->Write();
	_INFO("");
	f->Write();
	_INFO("");
	f->Close();
	_INFO("");
	delete f;
	_INFO("");
}

void clearMaps()
{
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		if(it->second) delete it->second; // the trees take a lot of memory, delete them.
	}
	
	treMap.clear();
	wgtMap.clear();
	mcSigmaMap.clear();
	pathMap.clear();
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
	
	/*
	if(name=="mcLocalControl_WW_Herwig")
	{
		vnEvts.push_back( 170959 );
		vnEvts.push_back( 1001330 );
		vnEvts.push_back( 465396 );
		vnEvts.push_back( 560356 );
		vnEvts.push_back( 244227 );
	}
	else if(name=="mcLocalControl_WZ_Herwig")
	{
		vnEvts.push_back( 16796 );
		vnEvts.push_back( 98379 );
		vnEvts.push_back( 45725 );
		vnEvts.push_back( 55054 );
		vnEvts.push_back( 23995 );
	}
	else if(name=="mcLocalControl_ZZ_Herwig")
	{
		vnEvts.push_back( 17150 );
		vnEvts.push_back( 100450 );
		vnEvts.push_back( 46687 );
		vnEvts.push_back( 56213 );
		vnEvts.push_back( 24500 );
	}
	else
	{
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
		
		treMap[name]->Draw(">>elist_periodItoK1_1", "all_RunNumber==185649  &&  all_randomized_decision==1");
		elist = (TEventList*)gDirectory->Get("elist_periodItoK1_1");
		npassed = elist->GetN();  // number of events to pass cuts
		vnEvts.push_back( (float)npassed );
		//treMap[name]->SetEventList(elist);
		treMap[name]->SetEventList(0);
		
		treMap[name]->Draw(">>elist_periodItoK1_2", "all_RunNumber==185649  &&  all_randomized_decision==2");
		elist = (TEventList*)gDirectory->Get("elist_periodItoK1_2");
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
	}
	*/
	
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
	
	treMap[name]->Draw(">>elist_periodItoK1_1", "all_RunNumber==185649  &&  all_randomized_decision==1");
	elist = (TEventList*)gDirectory->Get("elist_periodItoK1_1");
	npassed = elist->GetN();  // number of events to pass cuts
	vnEvts.push_back( (float)npassed );
	//treMap[name]->SetEventList(elist);
	treMap[name]->SetEventList(0);
	
	treMap[name]->Draw(">>elist_periodItoK1_2", "all_RunNumber==185649  &&  all_randomized_decision==2");
	elist = (TEventList*)gDirectory->Get("elist_periodItoK1_2");
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

void colors()
{
	cGmm.insert( make_pair("Gmm_01_1750",kViolet+1) );
	cGmm.insert( make_pair("Gmm_01_2000",kViolet+6) );
	cGmm.insert( make_pair("Gmm_01_2250",kViolet+10) );
	
	// cZprime.insert( make_pair("Zprime_SSM500",kAzure+0) );
	// cZprime.insert( make_pair("Zprime_SSM750",kAzure+0) );
	cZprime.insert( make_pair("Zprime_SSM1000",kAzure+0) );
	cZprime.insert( make_pair("Zprime_SSM1500",kAzure-2) );
	cZprime.insert( make_pair("Zprime_SSM1750",kAzure-3) );
	cZprime.insert( make_pair("Zprime_SSM2000",kAzure-4) );
	
	// cZprimeTemplate.insert( make_pair("Zprime_SSM500",kAzure+0) );
	// cZprimeTemplate.insert( make_pair("Zprime_SSM750",kAzure+0) );
	cZprimeTemplate.insert( make_pair("Zprime_SSM1000_template",kOrange+10) );
	cZprimeTemplate.insert( make_pair("Zprime_SSM1500_template",kOrange+8) );
	cZprimeTemplate.insert( make_pair("Zprime_SSM1750_template",kOrange+5) );
	cZprimeTemplate.insert( make_pair("Zprime_SSM2000_template",kOrange+3) );
	
	// cKKTemplate.insert( make_pair("Zprime_SSM500",kAzure+0) );
	// cKKTemplate.insert( make_pair("Zprime_SSM750",kAzure+0) );
	cKKTemplate.insert( make_pair("KK1000_template",kGreen+4) );
	cKKTemplate.insert( make_pair("KK1500_template",kOrange-1) );
	cKKTemplate.insert( make_pair("KK1750_template",kOrange-5) );
	cKKTemplate.insert( make_pair("KK2000_template",kOrange-8) );
}

void setMCtrees(TString tsMCname)
{
	_DEBUG("setMCtrees");
	
	////////////////
	clearMaps(); ///
	////////////////
	
	if(tsMCname=="DYmumu")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zmumu.root", "mcLocalControl_Zmumu", 4878990, 8.3470E-01*nb2fb); // need to do a cut to keep events only up to 250 GeV
		
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 20000, 7.9862E-01*nb2fb);
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_120M250.root", "mcLocalControl_DYmumu_120M250", 20000, 8.5275E-03*nb2fb);
		
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_250M400.root", "mcLocalControl_DYmumu_250M400", 20000, 4.1075E-04*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_400M600.root", "mcLocalControl_DYmumu_400M600", 20000, 6.6459E-05*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_600M800.root", "mcLocalControl_DYmumu_600M800", 20000, 1.1002E-05*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_800M1000.root", "mcLocalControl_DYmumu_800M1000", 20000, 2.6516E-06*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 20000, 8.9229E-07*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 20000, 2.3957E-07*nb2fb);
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 20000, *nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 99999, 7.3439E-08*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 20000, 2.4614E-08*nb2fb);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_DYmumu_M2000.root", "mcLocalControl_DYmumu_M2000", 20000, 1.4001E-08*nb2fb);
	}
	
	if(tsMCname=="Diboson")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_WW_Herwig.root", "mcLocalControl_WW_Herwig", 2442266, 3.1106E-02*nb2fb*3.8947E-01);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_WZ_Herwig.root", "mcLocalControl_WZ_Herwig", 239949,  1.1485E-02*nb2fb*3.1043E-01);
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_ZZ_Herwig.root", "mcLocalControl_ZZ_Herwig", 244999,  4.5721E-03*nb2fb*2.1319E-01);
	}
	
	
	if(tsMCname=="Gmm_01_1750")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Gmm_01_1750.root", "mcLocalControl_Gmm_01_1750", 10000, 1.6320E-06*nb2fb);
	}
	if(tsMCname=="Gmm_01_2000")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Gmm_01_2000.root", "mcLocalControl_Gmm_01_2000", 10000, 5.8721E-07*nb2fb);
	}
	if(tsMCname=="Gmm_01_2250")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Gmm_01_2250.root", "mcLocalControl_Gmm_01_2250", 10000, 2.1381E-07*nb2fb);
	}
	
	// if(tsMCname=="Zprime_SSM500")
	// {
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_SSM500.root", "mcLocalControl_Zprime_SSM500", 20000, 2.6071E-03*nb2fb);
	// }
	// if(tsMCname=="Zprime_SSM750")
	// {
		// setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_SSM750.root", "mcLocalControl_Zprime_SSM750", 20000, 4.7349E-04*nb2fb);
	// }
	if(tsMCname=="Zprime_SSM1000")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_mumu_SSM1000.root", "mcLocalControl_Zprime_SSM1000", 20000, 1.2466E-04*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1500")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_mumu_SSM1500.root", "mcLocalControl_Zprime_SSM1500", 20000, 1.4380E-05*nb2fb);
	}
	if(tsMCname=="Zprime_SSM1750")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_mumu_SSM1750.root", "mcLocalControl_Zprime_SSM1750", 20000, 5.6743E-06*nb2fb);
	}
	if(tsMCname=="Zprime_SSM2000")
	{
		setMCtree("/data/hod/2011/NTUPLE/mcLocalControl_Zprime_mumu_SSM2000.root", "mcLocalControl_Zprime_SSM2000", 20000, 2.4357E-06*nb2fb);
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
	tree->SetBranchAddress( "all_intime_pileup_weight",    &all_intime_pileup_weight );
	tree->SetBranchAddress( "all_outoftime_pileup_weight", &all_outoftime_pileup_weight );
	tree->SetBranchAddress( "all_lumi_pileup_weight", &all_lumi_pileup_weight );
	tree->SetBranchAddress( "all_EW_kfactor_weight",  &all_EW_kfactor_weight );
	tree->SetBranchAddress( "all_QCD_kfactor_weight", &all_QCD_kfactor_weight );
	tree->SetBranchAddress( "all_mcevent_weight",     &all_mcevent_weight );
	tree->SetBranchAddress( "all_total_weight",       &all_total_weight );
	tree->SetBranchAddress( "all_randomized_decision",&all_randomized_decision );

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
	
	tree->SetBranchAddress("truth_all_vKKwgt",   &truth_all_vKKwgt);
	tree->SetBranchAddress("truth_all_vZPwgt",   &truth_all_vZPwgt);
	tree->SetBranchAddress("truth_all_vBSMmass", &truth_all_vBSMmass);

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
	setLogBins(nloglimitimassbins, loglimitimassmin, loglimitimassmax, loglimitimassbins);

	/* graphics(TH1* th1,
			  Int_t mrkrstyle=-1, Float_t mrkrsize=-1,
			  Int_t fillstyle=-1,
			  Int_t linestyle=-1, Int_t linewidth=-1,
			  Color_t linecolor=-1, Color_t fillcolor=-1, Color_t mrkrcolor=-1,
			  Bool_t moreLogLabels=true, Bool_t noexponent=true,
			  TString title="", TString xtitle="", TString ytitle="") */
	
	// no need to draw these
	h1Map.insert( make_pair("hCosThetaLimitBins_Data", new TH1D("hCosThetaLimitBins_Data","Data;cos#theta*;Events",nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit)) );
	h1Map.insert( make_pair("hCosThetaLimitBins_DYmumu", new TH1D("hCosThetaLimitBins_DYmumu","DYmumu;cos#theta*;Events",nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit)) );
	h1Map.insert( make_pair("hCosThetaLimitBins_Diboson", new TH1D("hCosThetaLimitBins_Diboson","Diboson;cos#theta*;Events",nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit)) );
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname  = "hCosThetaLimitBins_Gmm_01_" + (TString)_s(M);
		TString tstitle = "Gmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,tstitle+";cos#theta*;Events",nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit)) );
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hCosThetaLimitBins_Zprime_SSM" + (TString)_s(M);
		TString tstitle = "Zprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,tstitle+";cos#theta*;Events",nCosThetaBinsLimit,minCosThetaLimit,maxCosThetaLimit)) );
	}
	
	// no need to draw these
	h1Map.insert( make_pair("hdEtaLimitBins_Data", new TH1D("hdEtaLimitBins_Data","Data;#Delta#eta;Events",ndEtaBinsLimit,mindEtaLimit,maxdEtaLimit)) );
	h1Map.insert( make_pair("hdEtaLimitBins_DYmumu", new TH1D("hdEtaLimitBins_DYmumu","DYmumu;#Delta#eta;Events",ndEtaBinsLimit,mindEtaLimit,maxdEtaLimit)) );
	h1Map.insert( make_pair("hdEtaLimitBins_Diboson", new TH1D("hdEtaLimitBins_Diboson","Diboson;#Delta#eta;Events",ndEtaBinsLimit,mindEtaLimit,maxdEtaLimit)) );
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname  = "hdEtaLimitBins_Gmm_01_" + (TString)_s(M);
		TString tstitle = "Gmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,tstitle+";#Delta#eta;Events",ndEtaBinsLimit,mindEtaLimit,maxdEtaLimit)) );
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hdEtaLimitBins_Zprime_SSM" + (TString)_s(M);
		TString tstitle = "Zprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,tstitle+";#Delta#eta;Events",ndEtaBinsLimit,mindEtaLimit,maxdEtaLimit)) );
	}
	
	
	/////////////////////////////////////
	// TEMPLATES
	h1Map.insert( make_pair("hMassDYmumu_truth", new TH1D("hMassDYmumu_truth",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassDYmumu_truth"]);
	graphics(h1Map["hMassDYmumu_truth"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hMassDYmumu_noEWkfactor", new TH1D("hMassDYmumu_noEWkfactor",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassDYmumu_noEWkfactor"]);
	graphics(h1Map["hMassDYmumu_noEWkfactor"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	
	h1Map.insert( make_pair("hpTLeadingDYmumu_truth", new TH1D("hpTLeadingDYmumu_truth",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingDYmumu_truth"]);
	graphics(h1Map["hpTLeadingDYmumu_truth"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hpTLeadingDYmumu_noEWkfactor", new TH1D("hpTLeadingDYmumu_noEWkfactor",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingDYmumu_noEWkfactor"]);
	graphics(h1Map["hpTLeadingDYmumu_noEWkfactor"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "";
		TString tsname = "";
		TString tsTname = "";
		
		/// imass
		tsMCname = "Zprime_SSM" + (TString)_s(M) + "_template";
		tsname   = "hMassZprime_SSM" + (TString)_s(M) + "_template";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprimeTemplate[tsMCname],cZprimeTemplate[tsMCname],-1);
		
		tsTname = "Zprime_SSM" + (TString)_s(M) + "_template";
		tsMCname = "Zprime_SSM" + (TString)_s(M) + "_template_truth";
		tsname   = "hMassZprime_SSM" + (TString)_s(M) + "_template_truth";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,"Truth;m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprimeTemplate[tsTname],cZprimeTemplate[tsTname],-1);
		
		tsMCname = "KK" + (TString)_s(M) + "_template";
		tsname   = "hMassKK" + (TString)_s(M) + "_template";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cKKTemplate[tsMCname],-1,-1);
		
		tsTname = "KK" + (TString)_s(M) + "_template";
		tsMCname = "KK" + (TString)_s(M) + "_template_truth";
		tsname   = "hMassKK" + (TString)_s(M) + "_template_truth";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,"Truth;m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cKKTemplate[tsTname],-1,-1);
		
		/// pT leading
		tsMCname = "Zprime_SSM" + (TString)_s(M) + "_template";
		tsname   = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_template";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprimeTemplate[tsMCname],cZprimeTemplate[tsMCname],-1);
		
		tsTname = "Zprime_SSM" + (TString)_s(M) + "_template";
		tsMCname = "Zprime_SSM" + (TString)_s(M) + "_template_truth";
		tsname   = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_template_truth";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,"Truth;p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprimeTemplate[tsTname],cZprimeTemplate[tsTname],-1);
		
		tsMCname = "KK" + (TString)_s(M) + "_template";
		tsname   = "hpTLeadingKK" + (TString)_s(M) + "_template";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cKKTemplate[tsMCname],-1,-1);
		
		tsTname = "KK" + (TString)_s(M) + "_template";
		tsMCname = "KK" + (TString)_s(M) + "_template_truth";
		tsname   = "hpTLeadingKK" + (TString)_s(M) + "_template_truth";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,"Truth;p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cKKTemplate[tsTname],-1,-1);
	}
	
	/////////////////////////////////////
	h1Map.insert( make_pair("hMassMCsum", new TH1D("hMassMCsum",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassMCsum"]);
	graphics(h1Map["hMassMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hMassData", new TH1D("hMassData",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassData"]);
	graphics(h1Map["hMassData"],  24,0.8);
	h1Map.insert( make_pair("hMassDYmumu", new TH1D("hMassDYmumu",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassDYmumu"]);
	graphics(h1Map["hMassDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hMassDiboson", new TH1D("hMassDiboson",";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
	setlogx(h1Map["hMassDiboson"]);
	graphics(h1Map["hMassDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hMassGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hMassZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
		
		tsMCname = "Zprime_SSM" + (TString)_s(M) + "_truth";
		tsname = "hMassZprime_SSM" + (TString)_s(M) + "_truth";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";m_{#mu#mu} GeV;Events",nlogfullimassbins,logfullimassbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	
	h1Map.insert( make_pair("hNvxpMCsum", new TH1D("hNvxpMCsum",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hNvxpData", new TH1D("hNvxpData",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpData"],  24,0.8);
	h1Map.insert( make_pair("hNvxpDYmumu", new TH1D("hNvxpDYmumu",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hNvxpDiboson", new TH1D("hNvxpDiboson",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hNvxpGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";N_{vertices};Events",35,1.,36.)) );
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hNvxpZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";N_{vertices};Events",35,1.,36.)) );
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hNvxpMCsum_with_puwgt", new TH1D("hNvxpMCsum_with_puwgt",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpMCsum_with_puwgt"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hNvxpData_with_puwgt", new TH1D("hNvxpData_with_puwgt",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpData_with_puwgt"],  24,0.8);
	h1Map.insert( make_pair("hNvxpDYmumu_with_puwgt", new TH1D("hNvxpDYmumu_with_puwgt",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpDYmumu_with_puwgt"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hNvxpDiboson_with_puwgt", new TH1D("hNvxpDiboson_with_puwgt",";N_{vertices};Events",35,1.,36.)) );
	graphics(h1Map["hNvxpDiboson_with_puwgt"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hNvxpGmm_01_" + (TString)_s(M) + "_with_puwgt";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";N_{vertices};Events",35,1.,36.)) );
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hNvxpZprime_SSM" + (TString)_s(M) + "_with_puwgt";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";N_{vertices};Events",35,1.,36.)) );
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hyQMCsum", new TH1D("hyQMCsum",";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
	setlogx(h1Map["hyQMCsum"]);
	graphics(h1Map["hyQMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hyQData", new TH1D("hyQData",";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
	setlogx(h1Map["hyQData"]);
	graphics(h1Map["hyQData"],  24,0.8);
	h1Map.insert( make_pair("hyQDYmumu", new TH1D("hyQDYmumu",";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
	setlogx(h1Map["hyQDYmumu"]);
	graphics(h1Map["hyQDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hyQDiboson", new TH1D("hyQDiboson",";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
	setlogx(h1Map["hyQDiboson"]);
	graphics(h1Map["hyQDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hyQGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hyQZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";y_{Q};Events",nyQbins,minyQ,maxyQ)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hQTMCsum", new TH1D("hQTMCsum",";Q_{T} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hQTMCsum"]);
	graphics(h1Map["hQTMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hQTData", new TH1D("hQTData",";Q_{T} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hQTData"]);
	graphics(h1Map["hQTData"],  24,0.8);
	h1Map.insert( make_pair("hQTDYmumu", new TH1D("hQTDYmumu",";Q_{T} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hQTDYmumu"]);
	graphics(h1Map["hQTDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hQTDiboson", new TH1D("hQTDiboson",";Q_{T} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hQTDiboson"]);
	graphics(h1Map["hQTDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hQTGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";Q_{T} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hQTZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";Q_{T} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hEtaLeadingMCsum", new TH1D("hEtaLeadingMCsum",";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaLeadingMCsum"]);
	graphics(h1Map["hEtaLeadingMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hEtaLeadingData", new TH1D("hEtaLeadingData",";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaLeadingData"]);
	graphics(h1Map["hEtaLeadingData"],  24,0.8);
	h1Map.insert( make_pair("hEtaLeadingDYmumu", new TH1D("hEtaLeadingDYmumu",";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaLeadingDYmumu"]);
	graphics(h1Map["hEtaLeadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hEtaLeadingDiboson", new TH1D("hEtaLeadingDiboson",";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaLeadingDiboson"]);
	graphics(h1Map["hEtaLeadingDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hEtaLeadingGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hEtaLeadingZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#eta_{#mu}^{leading};Events",etalogicnbins,etalogicbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hEtaSubleadingMCsum", new TH1D("hEtaSubleadingMCsum",";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaSubleadingMCsum"]);
	graphics(h1Map["hEtaSubleadingMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hEtaSubleadingData", new TH1D("hEtaSubleadingData",";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaSubleadingData"]);
	graphics(h1Map["hEtaSubleadingData"],  24,0.8);
	h1Map.insert( make_pair("hEtaSubleadingDYmumu", new TH1D("hEtaSubleadingDYmumu",";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaSubleadingDYmumu"]);
	graphics(h1Map["hEtaSubleadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hEtaSubleadingDiboson", new TH1D("hEtaSubleadingDiboson",";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
	setlogx(h1Map["hEtaSubleadingDiboson"]);
	graphics(h1Map["hEtaSubleadingDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hEtaSubleadingGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hEtaSubleadingZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#eta_{#mu}^{subleading};Events",etalogicnbins,etalogicbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hPhiLeadingMCsum", new TH1D("hPhiLeadingMCsum",";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiLeadingMCsum"]);
	graphics(h1Map["hPhiLeadingMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hPhiLeadingData", new TH1D("hPhiLeadingData",";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiLeadingData"]);
	graphics(h1Map["hPhiLeadingData"],  24,0.8);
	h1Map.insert( make_pair("hPhiLeadingDYmumu", new TH1D("hPhiLeadingDYmumu",";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiLeadingDYmumu"]);
	graphics(h1Map["hPhiLeadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hPhiLeadingDiboson", new TH1D("hPhiLeadingDiboson",";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiLeadingDiboson"]);
	graphics(h1Map["hPhiLeadingDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hPhiLeadingGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hPhiLeadingZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#phi_{#mu}^{leading};Events",nphibins,phimin,phimax)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hPhiSubleadingMCsum", new TH1D("hPhiSubleadingMCsum",";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiSubleadingMCsum"]);
	graphics(h1Map["hPhiSubleadingMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hPhiSubleadingData", new TH1D("hPhiSubleadingData",";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiSubleadingData"]);
	graphics(h1Map["hPhiSubleadingData"],  24,0.8);
	h1Map.insert( make_pair("hPhiSubleadingDYmumu", new TH1D("hPhiSubleadingDYmumu",";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiSubleadingDYmumu"]);
	graphics(h1Map["hPhiSubleadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hPhiSubleadingDiboson", new TH1D("hPhiSubleadingDiboson",";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
	setlogx(h1Map["hPhiSubleadingDiboson"]);
	graphics(h1Map["hPhiSubleadingDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hPhiSubleadingGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hPhiSubleadingZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";#phi_{#mu}^{subleading};Events",nphibins,phimin,phimax)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hpTLeadingMCsum", new TH1D("hpTLeadingMCsum",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingMCsum"]);
	graphics(h1Map["hpTLeadingMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hpTLeadingData", new TH1D("hpTLeadingData",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingData"]);
	graphics(h1Map["hpTLeadingData"],  24,0.8);
	h1Map.insert( make_pair("hpTLeadingDYmumu", new TH1D("hpTLeadingDYmumu",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingDYmumu"]);
	graphics(h1Map["hpTLeadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hpTLeadingDiboson", new TH1D("hpTLeadingDiboson",";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTLeadingDiboson"]);
	graphics(h1Map["hpTLeadingDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hpTLeadingGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hpTLeadingZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
		
		tsMCname = "Zprime_SSM" + (TString)_s(M) + "_truth";
		tsname = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_truth";
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{leading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	h1Map.insert( make_pair("hpTSubleadingMCsum", new TH1D("hpTSubleadingMCsum",";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTSubleadingMCsum"]);
	graphics(h1Map["hpTSubleadingMCsum"],  20,0.8,  -1,  -1,-1,  -1,-1,kRed);
	h1Map.insert( make_pair("hpTSubleadingData", new TH1D("hpTSubleadingData",";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTSubleadingData"]);
	graphics(h1Map["hpTSubleadingData"],  24,0.8);
	h1Map.insert( make_pair("hpTSubleadingDYmumu", new TH1D("hpTSubleadingDYmumu",";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTSubleadingDYmumu"]);
	graphics(h1Map["hpTSubleadingDYmumu"],  -1,-1,  -1,  -1,-1,  kAzure+8,kAzure+8,-1);
	h1Map.insert( make_pair("hpTSubleadingDiboson", new TH1D("hpTSubleadingDiboson",";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
	setlogx(h1Map["hpTSubleadingDiboson"]);
	graphics(h1Map["hpTSubleadingDiboson"],  -1,-1,  -1,  -1,-1,  kOrange-4,kOrange-4,-1);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsMCname = "Gmm_01_" + (TString)_s(M);
		TString tsname = "hpTSubleadingGmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cGmm[tsMCname],-1,-1);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsMCname = "Zprime_SSM" + (TString)_s(M);
		TString tsname = "hpTSubleadingZprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(tsname, new TH1D(tsname,";p_{T}^{subleading} GeV;Events",nlogptbins,logptbins)) );
		setlogx(h1Map[tsname]);
		graphics(h1Map[tsname],  -1,-1,  -1,  1,2,  cZprime[tsMCname],-1,-1);
	}
	
	
	TString baseName = "hMass_1d_full";
	h1Map.insert( make_pair(baseName+"_Data", new TH1D(baseName+"_Data", "#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
	h1Map.insert( make_pair(baseName+"_DYmumu", new TH1D(baseName+"_DYmumu", "DY#rightarrow#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
	h1Map.insert( make_pair(baseName+"_Diboson", new TH1D(baseName+"_Diboson", "Diboson#rightarrow#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname  = "_Gmm_01_" + (TString)_s(M);
		h1Map.insert( make_pair(baseName+tsname, new TH1D(baseName+tsname, (TString)_s(M)+" GeV G*#rightarrow#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "_Zprime_SSM" + (TString)_s(M);
		h1Map.insert( make_pair(baseName+tsname, new TH1D(baseName+tsname, (TString)_s(M)+" GeV Z'_{SSM}#rightarrow#mu#mu mass;m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
	}
	
	for(int i=1 ; i<=nCosThetaBinsLimit ; i++)
	{
		baseName = "hMass_cosThSlice_"+(TString)_s(i);
		h1Map.insert( make_pair(baseName+"_Data", new TH1D(baseName+"_Data", "#mu#mu mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		h1Map.insert( make_pair(baseName+"_DYmumu", new TH1D(baseName+"_DYmumu", "DY#rightarrow#mu#mu mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		h1Map.insert( make_pair(baseName+"_Diboson", new TH1D(baseName+"_Diboson", "Diboson#rightarrow#mu#mu mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
		{
			TString tsname  = "_Gmm_01_" + (TString)_s(M);
			h1Map.insert( make_pair(baseName+tsname, new TH1D(baseName+tsname, (TString)_s(M)+" GeV G*#rightarrow#mu#mu mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		}
		for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
		{
			if(M==1250.) continue;
			TString tsname = "_Zprime_SSM" + (TString)_s(M);
			h1Map.insert( make_pair(baseName+tsname, new TH1D(baseName+tsname, (TString)_s(M)+" GeV Z'_{SSM}#rightarrow#mu#mu mass in cos#theta* slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		}
	}
	for(int i=1 ; i<=ndEtaBinsLimit ; i++)
	{
		baseName = "hMass_dEtaSlice_"+(TString)_s(i);
		h1Map.insert( make_pair(baseName+"_Data", new TH1D(baseName+"_Data", "#mu#mu mass in #Delta#eta slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		h1Map.insert( make_pair(baseName+"_DYmumu", new TH1D(baseName+"_DYmumu", "DY#rightarrow#mu#mu mass in #Delta#eta slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		h1Map.insert( make_pair(baseName+"_Diboson", new TH1D(baseName+"_Diboson", "Diboson#rightarrow#mu#mu mass in #Delta#eta slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
		{
			TString tsname  = "_Gmm_01_" + (TString)_s(M);
			h1Map.insert( make_pair(baseName+tsname, new TH1D(baseName+tsname, (TString)_s(M)+" GeV G*#rightarrow#mu#mu mass in #Delta#eta slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		}
		for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
		{
			if(M==1250.) continue;
			TString tsname = "_Zprime_SSM" + (TString)_s(M);
			h1Map.insert( make_pair(baseName+tsname, new TH1D(baseName+tsname, (TString)_s(M)+" GeV Z'_{SSM}#rightarrow#mu#mu mass in #Delta#eta slice "+(TString)_s(i)+";m_{#mu#mu} TeV;Events", nloglimitimassbins,loglimitimassbins) ) );
		}
	}
	
	
	///// 2d /////
	h2Map.insert( make_pair("hMassCosThetaCSMCsum", new TH2D("hMassCosThetaCSMCsum",";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	setlogx(h2Map["hMassCosThetaCSMCsum"]);
	h2Map.insert( make_pair("hMassCosThetaCSData", new TH2D("hMassCosThetaCSData",";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	setlogx(h2Map["hMassCosThetaCSData"]);
	linMap.insert( make_pair("hMassCosThetaCS_horline", new TLine(linfullimassmin,0.,linfullimassmax,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassCosThetaCS_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],minFullCosTheta,logmassbins[ms],maxFullCosTheta)) );
	}
	h2Map.insert( make_pair("hMassCosThetaCSDYmumu", new TH2D("hMassCosThetaCSDYmumu",";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	setlogx(h2Map["hMassCosThetaCSDYmumu"]);
	h2Map.insert( make_pair("hMassCosThetaCSDiboson", new TH2D("hMassCosThetaCSDiboson",";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
	setlogx(h2Map["hMassCosThetaCSDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hMassCosThetaCSGmm_01_" + (TString)_s(M);
		h2Map.insert( make_pair(tsname, new TH2D(tsname,";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
		setlogx(h2Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hMassCosThetaCSZprime_SSM" + (TString)_s(M);
		h2Map.insert( make_pair(tsname, new TH2D(tsname,";m_{#mu#mu} GeV;cos(#theta*);Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nFullCosThetaBins,minFullCosTheta,maxFullCosTheta)) );
		setlogx(h2Map[tsname]);
	}
	
	h2Map.insert( make_pair("hMassyQMCsum", new TH2D("hMassyQMCsum",";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
	setlogx(h2Map["hMassyQMCsum"]);
	h2Map.insert( make_pair("hMassyQData", new TH2D("hMassyQData",";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
	setlogx(h2Map["hMassyQData"]);
	linMap.insert( make_pair("hMassyQ_horline", new TLine(linfullimassmin,0.,linfullimassmax,0.)) );
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		linMap.insert( make_pair("hMassyQ_vertline_"+_s(logmassbins[ms]), new TLine(logmassbins[ms],minfullyQ,logmassbins[ms],maxfullyQ)) );
	}
	h2Map.insert( make_pair("hMassyQDYmumu", new TH2D("hMassyQDYmumu",";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
	setlogx(h2Map["hMassyQDYmumu"]);
	h2Map.insert( make_pair("hMassyQDiboson", new TH2D("hMassyQDiboson",";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
	setlogx(h2Map["hMassyQDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hMassyQGmm_01_" + (TString)_s(M);
		h2Map.insert( make_pair(tsname, new TH2D(tsname,";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
		setlogx(h2Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hMassyQZprime_SSM" + (TString)_s(M);
		h2Map.insert( make_pair(tsname, new TH2D(tsname,";m_{#mu#mu} GeV;y_{Q};Events",nlinfullimassbins,linfullimassmin,linfullimassmax, nfullyQbins,minfullyQ,maxfullyQ)) );
		setlogx(h2Map[tsname]);
	}
}

float getDataMCratio()
{
	float ratio = (nMCall70to110>0.) ? nData70to110/nMCall70to110 : 1.;
	_INFO("DATA/MC in 70 to 110 GeV is: "+_s(ratio,8));
	return ratio;
}

float getDataMCratioNoPileup()
{
	float ratio = (nMCall70to110_nopileup>0.) ? nData70to110/nMCall70to110_nopileup : 1.;
	_INFO("DATA/MC (no pileup) in 70 to 110 GeV is: "+_s(ratio,8));
	return ratio;
}

void hscale2Zpeak()
{
	float ratio          = getDataMCratio();
	float ratio_nopileup = getDataMCratioNoPileup();
	
	// Scale(h1Map["hNvxpDYmumu"],ratio_nopileup);
	// Scale(h1Map["hNvxpDYmumu"],ratio);
	
	// Scale(h1Map["hNvxpDiboson"],ratio_nopileup);
	// Scale(h1Map["hNvxpDiboson"],ratio);

	Scale(h1Map["hNvxpMCsum_with_puwgt"],ratio);
	Scale(h1Map["hNvxpDYmumu_with_puwgt"],ratio);
	Scale(h1Map["hNvxpDiboson_with_puwgt"],ratio);

	Scale(h1Map["hMassMCsum"],ratio);
	Scale(h1Map["hyQMCsum"],ratio);
	Scale(h1Map["hQTMCsum"],ratio);
	Scale(h1Map["hEtaLeadingMCsum"],ratio);
	Scale(h1Map["hEtaSubleadingMCsum"],ratio);
	Scale(h1Map["hPhiLeadingMCsum"],ratio);
	Scale(h1Map["hPhiSubleadingMCsum"],ratio);
	Scale(h1Map["hpTLeadingMCsum"],ratio);
	Scale(h1Map["hpTSubleadingMCsum"],ratio);

	Scale(h1Map["hMassDYmumu"],ratio);
	Scale(h1Map["hMassDYmumu"],ratio);
	Scale(h1Map["hyQDYmumu"],ratio);
	Scale(h1Map["hQTDYmumu"],ratio);
	Scale(h1Map["hEtaLeadingDYmumu"],ratio);
	Scale(h1Map["hEtaSubleadingDYmumu"],ratio);
	Scale(h1Map["hPhiLeadingDYmumu"],ratio);
	Scale(h1Map["hPhiSubleadingDYmumu"],ratio);
	Scale(h1Map["hpTLeadingDYmumu"],ratio);
	Scale(h1Map["hpTSubleadingDYmumu"],ratio);

	Scale(h1Map["hMassDiboson"],ratio);
	Scale(h1Map["hyQDiboson"],ratio);
	Scale(h1Map["hQTDiboson"],ratio);
	Scale(h1Map["hEtaLeadingDiboson"],ratio);
	Scale(h1Map["hEtaSubleadingDiboson"],ratio);
	Scale(h1Map["hPhiLeadingDiboson"],ratio);
	Scale(h1Map["hPhiSubleadingDiboson"],ratio);
	Scale(h1Map["hpTLeadingDiboson"],ratio);
	Scale(h1Map["hpTSubleadingDiboson"],ratio);

	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "Gmm_01_" + (TString)_s(M);
		Scale(h1Map["hMass"+tsname],ratio);
		Scale(h1Map["hyQ"+tsname],ratio);
		Scale(h1Map["hQT"+tsname],ratio);
		Scale(h1Map["hEtaLeading"+tsname],ratio);
		Scale(h1Map["hEtaSubleading"+tsname],ratio);
		Scale(h1Map["hPhiLeading"+tsname],ratio);
		Scale(h1Map["hPhiSubleading"+tsname],ratio);
		Scale(h1Map["hpTLeading"+tsname],ratio);
		Scale(h1Map["hpTSubleading"+tsname],ratio);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "Zprime_SSM" + (TString)_s(M);
		Scale(h1Map["hMass"+tsname],ratio);
		Scale(h1Map["hyQ"+tsname],ratio);
		Scale(h1Map["hQT"+tsname],ratio);
		Scale(h1Map["hEtaLeading"+tsname],ratio);
		Scale(h1Map["hEtaSubleading"+tsname],ratio);
		Scale(h1Map["hPhiLeading"+tsname],ratio);
		Scale(h1Map["hPhiSubleading"+tsname],ratio);
		Scale(h1Map["hpTLeading"+tsname],ratio);
		Scale(h1Map["hpTSubleading"+tsname],ratio);
	}
	
	/////////////////////////////////////
	// TEMPLATES
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "";
		
		/// imass
		tsname = "Zprime_SSM" + (TString)_s(M) + "_template";
		Scale(h1Map["hMass"+tsname],ratio);
		tsname = "KK" + (TString)_s(M) + "_template";
		Scale(h1Map["hMass"+tsname],ratio);
		
		/// pTleading
		tsname = "Zprime_SSM" + (TString)_s(M) + "_template";
		Scale(h1Map["hpTLeading"+tsname],ratio);
		tsname = "KK" + (TString)_s(M) + "_template";
		Scale(h1Map["hpTLeading"+tsname],ratio);
	}
	
	
	for(int i=1 ; i<=nCosThetaBinsLimit ; i++)
	{
		TString baseName = "hMass_cosThSlice_"+(TString)_s(i);
		Scale(h1Map[baseName+"_DYmumu"],ratio);
		Scale(h1Map[baseName+"_Diboson"],ratio);
		for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
		{
			TString tsname = "_Gmm_01_" + (TString)_s(M);
			Scale(h1Map[baseName+tsname],ratio);
		}

		for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
		{
			if(M==1250.) continue;
			TString tsname = "_Zprime_SSM" + (TString)_s(M);
			Scale(h1Map[baseName+tsname],ratio);
		}
	}

	for(int i=1 ; i<=ndEtaBinsLimit ; i++)
	{
		TString baseName = "hMass_dEtaSlice_"+(TString)_s(i);
		Scale(h1Map[baseName+"_DYmumu"],ratio);
		Scale(h1Map[baseName+"_Diboson"],ratio);

		for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
		{
			TString tsname = "_Gmm_01_" + (TString)_s(M);
			Scale(h1Map[baseName+tsname],ratio);
		}

		for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
		{
			if(M==1250.) continue;
			TString tsname = "_Zprime_SSM" + (TString)_s(M);
			Scale(h1Map[baseName+tsname],ratio);
		}
	}

	///// 2d
	Scale(h2Map["hMassCosThetaCSMCsum"],ratio);
	Scale(h2Map["hMassyQMCsum"],ratio);
	Scale(h2Map["hMassCosThetaCSDYmumu"],ratio);
	Scale(h2Map["hMassyQDYmumu"],ratio);
	Scale(h2Map["hMassCosThetaCSDiboson"],ratio);
	Scale(h2Map["hMassyQDiboson"],ratio);
	
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "Gmm_01_" + (TString)_s(M);
		Scale(h2Map["hMassCosThetaCS"+tsname],ratio);
		Scale(h2Map["hMassyQ"+tsname],ratio);
	}

	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "Zprime_SSM" + (TString)_s(M);
		Scale(h2Map["hMassCosThetaCS"+tsname],ratio);
		Scale(h2Map["hMassyQ"+tsname],ratio);
	}
}

void hMCsumall(TString tsMCname)
{	
	h1Map["hNvxpMCsum"]->Add(h1Map["hNvxp"+tsMCname]);
	
	h1Map["hNvxpMCsum_with_puwgt"]->Add(h1Map["hNvxp"+tsMCname+"_with_puwgt"]);
	
	h1Map["hMassMCsum"]->Add(h1Map["hMass"+tsMCname]);
	h1Map["hyQMCsum"]->Add(h1Map["hyQ"+tsMCname]);
	h1Map["hQTMCsum"]->Add(h1Map["hQT"+tsMCname]);
	h1Map["hEtaLeadingMCsum"]->Add(h1Map["hEtaLeading"+tsMCname]);
	h1Map["hEtaSubleadingMCsum"]->Add(h1Map["hEtaSubleading"+tsMCname]);
	h1Map["hPhiLeadingMCsum"]->Add(h1Map["hPhiLeading"+tsMCname]);
	h1Map["hPhiSubleadingMCsum"]->Add(h1Map["hPhiSubleading"+tsMCname]);
	h1Map["hpTLeadingMCsum"]->Add(h1Map["hpTLeading"+tsMCname]);
	h1Map["hpTSubleadingMCsum"]->Add(h1Map["hpTSubleading"+tsMCname]);
	
	///// 2d
	h2Map["hMassCosThetaCSMCsum"]->Add(h2Map["hMassCosThetaCS"+tsMCname]);
	h2Map["hMassyQMCsum"]->Add(h2Map["hMassyQ"+tsMCname]);
}

void hdraw()
{
	_DEBUG("hdraw");

	vector<TString> vtsMCbgds;
	vector<TString> vtsMCsigs;
	
	////////////////////////////////////////
	// TEMPLATES
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "";
		TString tsnameTpt = "";
		
		_INFO("");
		
		/// imass
		tsname = "hMassZprime_SSM" + (TString)_s(M);
		tsnameTpt = tsname + "_template";
		setMinMax(h1Map[tsnameTpt],h1Map[tsname],true);
		draw(h1Map[tsnameTpt], "", "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsname]);
		templateText(tsname, (TString)_s(M)+" GeV Z'_{SSM}");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		tsname = "hMassZprime_SSM" + (TString)_s(M) + "_truth";
		tsnameTpt = "hMassZprime_SSM" + (TString)_s(M) + "_template_truth";
		setMinMax(h1Map[tsnameTpt],h1Map[tsname],true);
		draw(h1Map[tsnameTpt], "", "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsname]);
		templateText(tsname, (TString)_s(M)+" GeV Z'_{SSM}");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		tsname = "hMassDYmumu_noEWkfactor";
		tsnameTpt = "hMassKK" + (TString)_s(M) + "_template";
		setMinMax(h1Map[tsname],h1Map[tsnameTpt],true);
		draw(h1Map[tsname], tsnameTpt, "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsnameTpt]);
		templateText(tsnameTpt, (TString)_s(M)+" GeV KK");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		tsname = "hMassDYmumu_truth";
		tsnameTpt = "hMassKK" + (TString)_s(M) + "_template_truth";
		setMinMax(h1Map[tsname],h1Map[tsnameTpt],true);
		draw(h1Map[tsname], tsnameTpt, "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsnameTpt]);
		templateText(tsnameTpt, (TString)_s(M)+" GeV KK");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		/// pTleading
		tsname = "hpTLeadingZprime_SSM" + (TString)_s(M);
		tsnameTpt = tsname + "_template";
		setMinMax(h1Map[tsnameTpt],h1Map[tsname],true);
		draw(h1Map[tsnameTpt], "", "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsname]);
		templateText(tsname, (TString)_s(M)+" GeV Z'_{SSM}");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		tsname = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_truth";
		tsnameTpt = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_template_truth";
		setMinMax(h1Map[tsnameTpt],h1Map[tsname],true);
		draw(h1Map[tsnameTpt], "", "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsname]);
		templateText(tsname, (TString)_s(M)+" GeV Z'_{SSM}");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		tsname = "hpTLeadingDYmumu_noEWkfactor";
		tsnameTpt = "hpTLeadingKK" + (TString)_s(M) + "_template";
		setMinMax(h1Map[tsname],h1Map[tsnameTpt],true);
		draw(h1Map[tsname], tsnameTpt, "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsnameTpt]);
		templateText(tsnameTpt, (TString)_s(M)+" GeV KK");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
		
		tsname = "hpTLeadingDYmumu_truth";
		tsnameTpt = "hpTLeadingKK" + (TString)_s(M) + "_template_truth";
		setMinMax(h1Map[tsname],h1Map[tsnameTpt],true);
		draw(h1Map[tsname], tsnameTpt, "", dolog, dolog);
		drawon(tsnameTpt, h1Map[tsnameTpt]);
		templateText(tsnameTpt, (TString)_s(M)+" GeV KK");
		drawtemplatetxton(tsnameTpt);
		
		_INFO("");
	}
	_INFO("");
	
	///////////////////////////////////
	vtsMCbgds.clear();
	setMinMax(h1Map["hMassDYmumu"],h1Map["hMassData"],true);
	draw(h1Map["hMassDYmumu"], "", "", dolog, dolog);
	drawon("hMassDYmumu", h1Map["hMassDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hMassGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hMassDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hMassZprime_SSM" + (TString)_s(M);
		drawon("hMassDYmumu", h1Map[tsname]);
	}
	drawon("hMassDYmumu", h1Map["hMassData"], "e1x1");
	drawtxton("hMassDYmumu");
	// drawratio(h1Map["hMassData"], h1Map["hMassDYmumu"], "e1x1", "", dolog, dolog);
	vtsMCbgds.push_back("hMassDYmumu");
	vtsMCbgds.push_back("hMassDiboson");
	drawratio(h1Map["hMassData"], h1Map["hMassMCsum"], vtsMCbgds, "e1x1", "", dolog, dolog);
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hNvxpDYmumu"],h1Map["hNvxpData"]);
	draw(h1Map["hNvxpDYmumu"]);
	drawon("hNvxpDYmumu", h1Map["hNvxpDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hNvxpGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hNvxpDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hNvxpZprime_SSM" + (TString)_s(M);
		drawon("hNvxpDYmumu", h1Map[tsname]);
	}
	drawon("hNvxpDYmumu", h1Map["hNvxpData"], "e1x1");
	drawtxton("hNvxpDYmumu");
	// drawratio(h1Map["hNvxpData"], h1Map["hNvxpDYmumu"], "e1x1");
	vtsMCbgds.push_back("hNvxpDYmumu");
	vtsMCbgds.push_back("hNvxpDiboson");
	drawratio(h1Map["hNvxpData"], h1Map["hNvxpMCsum"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hNvxpDYmumu_with_puwgt"],h1Map["hNvxpData_with_puwgt"]);
	draw(h1Map["hNvxpDYmumu_with_puwgt"]);
	drawon("hNvxpDYmumu_with_puwgt", h1Map["hNvxpDiboson_with_puwgt"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hNvxpGmm_01_" + (TString)_s(M) + "_with_puwgt";
		if(drawGmm) drawon("hNvxpDYmumu_with_puwgt", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hNvxpZprime_SSM" + (TString)_s(M) + "_with_puwgt";
		drawon("hNvxpDYmumu_with_puwgt", h1Map[tsname]);
	}
	drawon("hNvxpDYmumu_with_puwgt", h1Map["hNvxpData_with_puwgt"], "e1x1");
	drawtxton("hNvxpDYmumu_with_puwgt");
	// drawratio(h1Map["hNvxpData_with_puwgt"], h1Map["hNvxpDYmumu_with_puwgt"], "e1x1");
	vtsMCbgds.push_back("hNvxpDYmumu_with_puwgt");
	vtsMCbgds.push_back("hNvxpDiboson_with_puwgt");
	drawratio(h1Map["hNvxpData_with_puwgt"], h1Map["hNvxpMCsum_with_puwgt"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hyQDYmumu"],h1Map["hyQData"],true);
	h1Map["hyQDYmumu"]->SetMinimum(0.);
	draw(h1Map["hyQDYmumu"]);
	drawon("hyQDYmumu", h1Map["hyQDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hyQGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hyQDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hyQZprime_SSM" + (TString)_s(M);
		drawon("hyQDYmumu", h1Map[tsname]);
	}
	drawon("hyQDYmumu", h1Map["hyQData"], "e1x1");
	drawtxton("hyQDYmumu");
	// drawratio(h1Map["hyQData"], h1Map["hyQDYmumu"], "e1x1");
	vtsMCbgds.push_back("hyQDYmumu");
	vtsMCbgds.push_back("hyQDiboson");
	drawratio(h1Map["hyQData"], h1Map["hyQMCsum"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	
	_INFO("");
	
	
	setMinMax(h1Map["hQTDYmumu"],h1Map["hQTData"],true);
	draw(h1Map["hQTDYmumu"], "", "", dolog, dolog);
	drawon("hQTDYmumu", h1Map["hQTDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hQTGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hQTDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hQTZprime_SSM" + (TString)_s(M);
		drawon("hQTDYmumu", h1Map[tsname]);
	}
	drawon("hQTDYmumu", h1Map["hQTData"], "e1x1");
	drawtxton("hQTDYmumu");
	// drawratio(h1Map["hQTData"], h1Map["hQTDYmumu"], "e1x1", "", dolog, dolog);
	vtsMCbgds.push_back("hQTDYmumu");
	vtsMCbgds.push_back("hQTDiboson");
	drawratio(h1Map["hQTData"], h1Map["hQTMCsum"], vtsMCbgds, "e1x1", "", dolog, dolog);
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hEtaLeadingDYmumu"],h1Map["hEtaLeadingData"]);
	h1Map["hEtaLeadingDYmumu"]->SetMinimum(0.);
	draw(h1Map["hEtaLeadingDYmumu"]);
	drawon("hEtaLeadingDYmumu", h1Map["hEtaLeadingDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hEtaLeadingGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hEtaLeadingDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hEtaLeadingZprime_SSM" + (TString)_s(M);
		drawon("hEtaLeadingDYmumu", h1Map[tsname]);
	}
	drawon("hEtaLeadingDYmumu", h1Map["hEtaLeadingData"], "e1x1");
	drawtxton("hEtaLeadingDYmumu");
	// drawratio(h1Map["hEtaLeadingData"], h1Map["hEtaLeadingDYmumu"], "e1x1");
	vtsMCbgds.push_back("hEtaLeadingDYmumu");
	vtsMCbgds.push_back("hEtaLeadingDiboson");
	drawratio(h1Map["hEtaLeadingData"], h1Map["hEtaLeadingMCsum"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hEtaSubleadingDYmumu"],h1Map["hEtaSubleadingData"]);
	h1Map["hEtaSubleadingDYmumu"]->SetMinimum(0.);
	draw(h1Map["hEtaSubleadingDYmumu"]);
	drawon("hEtaSubleadingDYmumu", h1Map["hEtaSubleadingDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hEtaSubleadingGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hEtaSubleadingDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hEtaSubleadingZprime_SSM" + (TString)_s(M);
		drawon("hEtaSubleadingDYmumu", h1Map[tsname]);
	}
	drawon("hEtaSubleadingDYmumu", h1Map["hEtaSubleadingData"], "e1x1");
	drawtxton("hEtaSubleadingDYmumu");
	// drawratio(h1Map["hEtaSubleadingData"], h1Map["hEtaSubleadingDYmumu"], "e1x1");
	vtsMCbgds.push_back("hEtaSubleadingDYmumu");
	vtsMCbgds.push_back("hEtaSubleadingDiboson");
	drawratio(h1Map["hEtaSubleadingData"], h1Map["hEtaSubleadingMCsum"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	
	_INFO("");
	
	
	setMinMax(h1Map["hPhiLeadingDYmumu"],h1Map["hPhiLeadingData"]);
	h1Map["hPhiLeadingDYmumu"]->SetMinimum(0.);
	draw(h1Map["hPhiLeadingDYmumu"]);
	drawon("hPhiLeadingDYmumu", h1Map["hPhiLeadingDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hPhiLeadingGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hPhiLeadingDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hPhiLeadingZprime_SSM" + (TString)_s(M);
		drawon("hPhiLeadingDYmumu", h1Map[tsname]);
	}
	drawon("hPhiLeadingDYmumu", h1Map["hPhiLeadingData"], "e1x1");
	drawtxton("hPhiLeadingDYmumu");
	// drawratio(h1Map["hPhiLeadingData"], h1Map["hPhiLeadingDYmumu"], "e1x1");
	vtsMCbgds.push_back("hPhiLeadingDYmumu");
	vtsMCbgds.push_back("hPhiLeadingDiboson");
	drawratio(h1Map["hPhiLeadingData"], h1Map["hPhiLeadingMCsum"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hPhiSubleadingDYmumu"],h1Map["hPhiSubleadingData"]);
	h1Map["hPhiSubleadingDYmumu"]->SetMinimum(0.);
	draw(h1Map["hPhiSubleadingDYmumu"]);
	drawon("hPhiSubleadingDYmumu", h1Map["hPhiSubleadingDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hPhiSubleadingGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hPhiSubleadingDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hPhiSubleadingZprime_SSM" + (TString)_s(M);
		drawon("hPhiSubleadingDYmumu", h1Map[tsname]);
	}
	drawon("hPhiSubleadingDYmumu", h1Map["hPhiSubleadingData"], "e1x1");
	drawtxton("hPhiSubleadingDYmumu");
	// drawratio(h1Map["hPhiSubleadingData"], h1Map["hPhiSubleadingDYmumu"], "e1x1");
	vtsMCbgds.push_back("hPhiSubleadingDYmumu");
	vtsMCbgds.push_back("hPhiSubleadingDiboson");
	drawratio(h1Map["hPhiSubleadingData"], h1Map["hPhiSubleadingMCsum"], vtsMCbgds, "e1x1");
	vtsMCbgds.clear();
	
	setMinMax(h1Map["hpTLeadingDYmumu"],h1Map["hpTLeadingData"],true);
	draw(h1Map["hpTLeadingDYmumu"], "", "", dolog, dolog);
	drawon("hpTLeadingDYmumu", h1Map["hpTLeadingDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hpTLeadingGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hpTLeadingDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hpTLeadingZprime_SSM" + (TString)_s(M);
		drawon("hpTLeadingDYmumu", h1Map[tsname]);
	}
	drawon("hpTLeadingDYmumu", h1Map["hpTLeadingData"], "e1x1");
	drawtxton("hpTLeadingDYmumu");
	// drawratio(h1Map["hpTLeadingData"], h1Map["hpTLeadingDYmumu"], "e1x1", "", dolog, dolog);
	vtsMCbgds.push_back("hpTLeadingDYmumu");
	vtsMCbgds.push_back("hpTLeadingDiboson");
	drawratio(h1Map["hpTLeadingData"], h1Map["hpTLeadingMCsum"], vtsMCbgds, "e1x1", "", dolog, dolog);
	vtsMCbgds.clear();
	
	
	_INFO("");
	
	
	setMinMax(h1Map["hpTSubleadingDYmumu"],h1Map["hpTSubleadingData"],true);
	draw(h1Map["hpTSubleadingDYmumu"], "", "", dolog, dolog);
	drawon("hpTSubleadingDYmumu", h1Map["hpTSubleadingDiboson"]);
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hpTSubleadingGmm_01_" + (TString)_s(M);
		if(drawGmm) drawon("hpTSubleadingDYmumu", h1Map[tsname]);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hpTSubleadingZprime_SSM" + (TString)_s(M);
		drawon("hpTSubleadingDYmumu", h1Map[tsname]);
	}
	drawon("hpTSubleadingDYmumu", h1Map["hpTSubleadingData"], "e1x1");
	drawtxton("hpTSubleadingDYmumu");
	// drawratio(h1Map["hpTSubleadingData"], h1Map["hpTSubleadingDYmumu"], "e1x1", "", dolog, dolog);
	vtsMCbgds.push_back("hpTSubleadingDYmumu");
	vtsMCbgds.push_back("hpTSubleadingDiboson");
	drawratio(h1Map["hpTSubleadingData"], h1Map["hpTSubleadingMCsum"], vtsMCbgds, "e1x1", "", dolog, dolog);
	vtsMCbgds.clear();
	
	
	_INFO("");
	
	
	for(int i=1 ; i<=nCosThetaBinsLimit ; i++)
	{
		TString baseName = "hMass_cosThSlice_"+(TString)_s(i);
		draw(h1Map[baseName+"_Data"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_DYmumu"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Diboson"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Gmm_01_1750"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Gmm_01_2000"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Gmm_01_2250"], "", "", !dolog, dolog);
	}
	for(int i=1 ; i<=ndEtaBinsLimit ; i++)
	{
		TString baseName = "hMass_dEtaSlice_"+(TString)_s(i);
		draw(h1Map[baseName+"_Data"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_DYmumu"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Diboson"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Gmm_01_1750"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Gmm_01_2000"], "", "", !dolog, dolog);
		draw(h1Map[baseName+"_Gmm_01_2250"], "", "", !dolog, dolog);
	}
	
	
	_INFO("");
	
	
	///// 2d
	bool is2d = true;
	h2Map["hMassCosThetaCSData"]->SetMinimum( getXYmin(h2Map["hMassCosThetaCSData"]) );
	draw(h2Map["hMassCosThetaCSData"], "", "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSData", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSData", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSData", is2d);
	
	h2Map["hMassCosThetaCSDYmumu"]->SetMinimum( getXYmin(h2Map["hMassCosThetaCSDYmumu"]) );
	draw(h2Map["hMassCosThetaCSDYmumu"], "", "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSDYmumu", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSDYmumu", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSDYmumu", is2d);
	
	h2Map["hMassCosThetaCSDiboson"]->SetMinimum( getXYmin(h2Map["hMassCosThetaCSDiboson"]) );
	draw(h2Map["hMassCosThetaCSDiboson"], "", "COLZ", dolog, !dolog, dolog);
	drawon("hMassCosThetaCSDiboson", linMap["hMassCosThetaCS_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassCosThetaCSDiboson", linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassCosThetaCSDiboson", is2d);
	
	
	_INFO("");
	
	
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hMassCosThetaCSGmm_01_" + (TString)_s(M);
		h2Map[tsname]->SetMinimum( getXYmin(h2Map[tsname]) );
		draw(h2Map[tsname], "", "COLZ", dolog, !dolog, dolog);
		drawon(tsname, linMap["hMassCosThetaCS_horline"]);
		for(int ms=0 ; ms<=nlogmassbins ; ms++)
		{
			drawon(tsname, linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
		}
		drawtxton(tsname, is2d);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hMassCosThetaCSZprime_SSM" + (TString)_s(M);
		h2Map[tsname]->SetMinimum( getXYmin(h2Map[tsname]) );
		draw(h2Map[tsname], "", "COLZ", dolog, !dolog, dolog);
		drawon(tsname, linMap["hMassCosThetaCS_horline"]);
		for(int ms=0 ; ms<=nlogmassbins ; ms++)
		{
			drawon(tsname, linMap["hMassCosThetaCS_vertline_"+_s(logmassbins[ms])]);
		}
		drawtxton(tsname, is2d);
	}
	
	draw(h2Map["hMassyQData"], "", "COLZ", dolog, !dolog, dolog);
	h2Map["hMassyQData"]->SetMinimum( getXYmin(h2Map["hMassyQData"]) );
	drawon("hMassyQData", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQData", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQData", is2d);
	
	h2Map["hMassyQDYmumu"]->SetMinimum( getXYmin(h2Map["hMassyQDYmumu"]) );
	draw(h2Map["hMassyQDYmumu"], "", "COLZ", dolog, !dolog, dolog);
	drawon("hMassyQDYmumu", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQDYmumu", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQDYmumu", is2d);
	
	h2Map["hMassyQDiboson"]->SetMinimum( getXYmin(h2Map["hMassyQDiboson"]) );
	draw(h2Map["hMassyQDiboson"], "", "COLZ", dolog, !dolog, dolog);
	drawon("hMassyQDiboson", linMap["hMassyQ_horline"]);
	for(int ms=0 ; ms<=nlogmassbins ; ms++)
	{
		drawon("hMassyQDiboson", linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
	}
	drawtxton("hMassyQDiboson", is2d);
	
	
	_INFO("");
	
	
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		TString tsname = "hMassyQGmm_01_" + (TString)_s(M);
		h2Map[tsname]->SetMinimum( getXYmin(h2Map[tsname]) );
		draw(h2Map[tsname], "", "COLZ", dolog, !dolog, dolog);
		drawon(tsname, linMap["hMassyQ_horline"]);
		for(int ms=0 ; ms<=nlogmassbins ; ms++)
		{
			drawon(tsname, linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
		}
		drawtxton(tsname, is2d);
	}
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		TString tsname = "hMassyQZprime_SSM" + (TString)_s(M);
		h2Map[tsname]->SetMinimum( getXYmin(h2Map[tsname]) );
		draw(h2Map[tsname], "", "COLZ", dolog, !dolog, dolog);
		drawon(tsname, linMap["hMassyQ_horline"]);
		for(int ms=0 ; ms<=nlogmassbins ; ms++)
		{
			drawon(tsname, linMap["hMassyQ_vertline_"+_s(logmassbins[ms])]);
		}
		drawtxton(tsname, is2d);
	}
	
	
	_INFO("");
}

float dummyPileupWeight(int Nvtx)
{
	float wgt = -999.;
	float err = -999.;
	switch(Nvtx)
	{
		case 1:  wgt=0.;         err=0.;          break;
		case 2:  wgt=1.81326;    err=0.0150585;   break;
		case 3:  wgt=1.65073;    err=0.00631874;  break;
		case 4:  wgt=1.41608;    err=0.00314592;  break;
		case 5:  wgt=1.26549;    err=0.00195111;  break;
		case 6:  wgt=1.12297;    err=0.00115998;  break;
		case 7:  wgt=1.01051;    err=0.000325553; break;
		case 8:  wgt=0.902816;   err=0.000998862; break;
		case 9:  wgt=0.815026;   err=0.00145847;  break;
		case 10: wgt=0.729515;   err=0.00192831;  break;
		case 11: wgt=0.641988;   err=0.00245465;  break;
		case 12: wgt=0.584297;   err=0.00309103;  break;
		case 13: wgt=0.494007;   err=0.00381757;  break;
		case 14: wgt=0.438138;   err=0.00484277;  break;
		case 15: wgt=0.395561;   err=0.00628664;  break;
		case 16: wgt=0.32917;    err=0.00791585;  break;
		case 17: wgt=0.280448;   err=0.0098695;   break;
		case 18: wgt=0.300399;   err=0.0155825;   break;
		case 19: wgt=0.261624;   err=0.0203534;   break;
		case 20: wgt=0.333972;   err=0.0348973;   break;
		case 21: wgt=0.190723;   err=0.0365797;   break;
		case 22: wgt=0.267786;   err=0.0690892;   break;
		case 23: wgt=0.205879;   err=0.0820484;   break;
		case 24: wgt=3.92444;    err=4.74552;     break;
		case 25: wgt=0.192857;   err=0.122517;    break;
		case 26: wgt=7.84888;    err= 14.5245;    break;
		case 27: wgt=0.;         err=0.;          break;
		case 28: wgt=0.;         err=0.;          break;
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

float getLumiWeight(TString mcName, int mcRunNumber, unsigned int randomized_decision=-1)
{
	_DEBUG("getLumiWeight");

	/*//////////////////////////////////////////////////////////////////////
	------------------------------------------------------------------------------------------------------------------------------------
	B->D:     [178044->180481]:   L1_MU10+EF_mu22        187.91   pb-1  wL=0.0423497425  https://atlas-lumicalc.cern.ch/results/25ef16/
	E->H:     [180614->184169]:   L1_MU10+EF_mu22        1015.2   pb-1  wL=0.22879814    https://atlas-lumicalc.cern.ch/results/8ccfda/
	I->K1_1:  [185353->186493]:   L1_MU10+EF_mu22        390.364  pb-1  wL=0.0879773023  https://atlas-lumicalc.cern.ch/results/8076cb/
	I->K1_2:  [186516->186934]:   L1_MU11+EF_mu22_medium 470.015  pb-1  wL=0.105928446   https://atlas-lumicalc.cern.ch/results/391636/
	Future:   [186965->191139]:   L1_MU11+EF_mu22_medium 2373.61  pb-1  wL=0.534946369   https://atlas-lumicalc.cern.ch/results/a6a915/
	Total:    [178044->191139]:                          4437.099 pb-1
	------------------------------------------------------------------------------------------------------------------------------------
	*///////////////////////////////////////////////////////////////////////
	
	int iPeriod = -1;
	float Ldata = -1.;
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
	else if(mcRunNumber==185649  &&  randomized_decision==1) // periodItoK1_1
	{
		iPeriod = 2;
		Ldata = 0.390364;
	}
	else if(mcRunNumber==185649  &&  randomized_decision==2) // periodItoK1_2
	{
		iPeriod = 3;
		Ldata = 0.470015;
	}
	else if(mcRunNumber==185761) // periodFuture
	{
		iPeriod = 4;
		Ldata = 2.37361;
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

void hfill(TString tsRunType="", TString tsMCname="", Double_t wgt=1.)
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
	int   slice_cost = 0;
	int   slice_deta = 0;
	float dEta = 0.;
	
	int imuontru  = -999;
	int iamuontru = -999;
	int imuonrec  = -999;
	int iamuonrec = -999;
	
	float event_weight          = 1.;
	float event_weight_nopileup = 1.;
	float dummy_pileup_weight   = 1.;
	float noEWkfactor_weight    = 1.;
	
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
			// tlvmutruaBoosted = K->Boost(tlvmutrua,tlvmutrub,tlvmutrua);
			// tlvmutrubBoosted = K->Boost(tlvmutrua,tlvmutrub,tlvmutrub);
			tlvmutruaBoosted = fkinematics::Boost(tlvmutrua,tlvmutrub,tlvmutrua);
			tlvmutrubBoosted = fkinematics::Boost(tlvmutrua,tlvmutrub,tlvmutrub);
			(*tv3mutruaBoosted) = tlvmutruaBoosted->Vect();
			(*tv3mutrubBoosted) = tlvmutrubBoosted->Vect();
			
			mass          = fkinematics::imass(tlvmutrua,tlvmutrub);
			pTLeading     = truth_all_mc_pt->at(imuontru);
			
			if(tsMCname.Contains("Zprime"))
			{
				/// imass
				h1Map["hMass"+tsMCname+"_truth"]->Fill(mass,wgt);
				/// pT leading
				h1Map["hpTLeading"+tsMCname+"_truth"]->Fill(pTLeading,wgt);
			}

			if(tsMCname=="DYmumu") // templates truth
			{
				/// imass
				h1Map["hMassDYmumu_truth"]->Fill(mass,wgt);
				/// pT leading
				h1Map["hpTLeadingDYmumu_truth"]->Fill(pTLeading,wgt);

				for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
				{
					if(M==1250.) continue;
					TString tsname_ZP = "";
					TString tsname_KK = "";
					double template_weight_ZP = 0.;
					double template_weight_KK = 0.;
					for(unsigned int j=0 ; j<truth_all_vBSMmass->size() ; j++)
					{
						if(truth_all_vBSMmass->at(j)==M)
						{
							template_weight_ZP = truth_all_vZPwgt->at(j);
							template_weight_KK = truth_all_vKKwgt->at(j);
							break;
						}
					}

					/// imass
					tsname_ZP = "hMassZprime_SSM" + (TString)_s(M) + "_template_truth";
					tsname_KK = "hMassKK"         + (TString)_s(M) + "_template_truth";
					h1Map[tsname_ZP]->Fill(mass,wgt*template_weight_ZP);
					h1Map[tsname_KK]->Fill(mass,wgt*template_weight_KK);

					/// pT leading
					tsname_ZP = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_template_truth";
					tsname_KK = "hpTLeadingKK"         + (TString)_s(M) + "_template_truth";
					h1Map[tsname_ZP]->Fill(pTLeading,wgt*template_weight_ZP);
					h1Map[tsname_KK]->Fill(pTLeading,wgt*template_weight_KK);
				}
			}

			if(recon_all_isValid)
			{
				imuonrec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				
				tlvtmp->SetPtEtaPhiM(recon_all_pt->at(imuonrec), recon_all_eta->at(imuonrec), recon_all_phi->at(imuonrec), muonMass);
				// dr1 = K->dR(tlvtmp,tlvmutrua);
				// dr2 = K->dR(tlvtmp,tlvmutrub);
				dr1 = fkinematics::dR(tlvtmp,tlvmutrua);
				dr2 = fkinematics::dR(tlvtmp,tlvmutrub);
				imuonrec  = (dr1<=dr2) ? imuonrec : iamuonrec;
				iamuonrec = (imuonrec==0) ? 1 : 0;
				if(dr1>dr2) _WARNING("dr1(recA,truA) > dr2(recA,truB)");
				
				tlvmureca->SetPtEtaPhiM(recon_all_pt->at(imuonrec),  recon_all_eta->at(imuonrec),  recon_all_phi->at(imuonrec),  muonMass);
				tlvmurecb->SetPtEtaPhiM(recon_all_pt->at(iamuonrec), recon_all_eta->at(iamuonrec), recon_all_phi->at(iamuonrec), muonMass);
				(*tv3mureca) = tlvmureca->Vect();
				(*tv3murecb) = tlvmurecb->Vect();
				// tlvmurecaBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmureca);
				// tlvmurecbBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmurecb);
				tlvmurecaBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmureca);
				tlvmurecbBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmurecb);
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
				// mass          = K->imass(tlvmureca,tlvmurecb);
				// yQ            = K->ySystem(tlvmureca,tlvmurecb);
				// QT            = K->QT(tlvmureca,tlvmurecb);
				// cosThetaCS    = K->cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
				// cosThetaHE    = K->cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
				mass          = fkinematics::imass(tlvmureca,tlvmurecb);
				yQ            = fkinematics::ySystem(tlvmureca,tlvmurecb);
				QT            = fkinematics::QT(tlvmureca,tlvmurecb);
				cosThetaCS    = fkinematics::cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
				cosThetaHE    = fkinematics::cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
				etaLeading    = recon_all_eta->at(0);
				etaSubleading = recon_all_eta->at(1);
				phiLeading    = recon_all_phi->at(0);
				phiSubleading = recon_all_phi->at(1);
				pTLeading     = recon_all_pt->at(0);
				pTSubleading  = recon_all_pt->at(1);
				dEta          = fabs(etaLeading-etaSubleading);
				slice_cost    = h1Map["hCosThetaLimitBins_DYmumu"]->FindBin(cosThetaCS);
				slice_deta    = h1Map["hdEtaLimitBins_DYmumu"]->FindBin(dEta);
				
				/////////////////////////
				/// weights handeling ///
				/////////////////////////
				event_weight          = 1.;
				event_weight_nopileup = 1.;
				dummy_pileup_weight   = 1.;
				noEWkfactor_weight    = 1.;
				
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
				event_weight *= all_pileup_weight;           // [1] out-of-time-pileup
				// event_weight *= all_outoftime_pileup_weight; // [2] out-of-time-pileup
				// event_weight *= all_intime_pileup_weight;       // [3] in-time-pileup (should describe better the vxp_n distribution)
				
				// option 5 for the event weight with pileup
				// dummy_pileup_weight = dummyPileupWeight(recon_all_vxp_n);
				// if(dummy_pileup_weight<0.) return;
				// event_weight *= dummy_pileup_weight;
				
				// for the event weight without pileup
				event_weight_nopileup = all_EW_kfactor_weight  *
										all_QCD_kfactor_weight *
										all_mcevent_weight;
										
				noEWkfactor_weight = event_weight/all_EW_kfactor_weight;
				
				// for the Z peak normalization
				if(mass>=70.  &&  mass<=110.) nMCall70to110          += 1.*wgt*event_weight;
				if(mass>=70.  &&  mass<=110.) nMCall70to110_nopileup += 1.*wgt*event_weight_nopileup;

				/////////////////////////////////
				/// MC histo fill statrs here ///
				/////////////////////////////////
				if(tsMCname=="DYmumu") // templates
				{
					/// imass
					h1Map["hMassDYmumu_noEWkfactor"]->Fill(mass,wgt*noEWkfactor_weight);
					/// pT leading
					h1Map["hpTLeadingDYmumu_noEWkfactor"]->Fill(pTLeading,wgt*noEWkfactor_weight);
				
					for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
					{
						if(M==1250.) continue;
						TString tsname_ZP = "";
						TString tsname_KK = "";
						double template_weight_ZP = 0.;
						double template_weight_KK = 0.;
						for(unsigned int j=0 ; j<truth_all_vBSMmass->size() ; j++)
						{
							if(truth_all_vBSMmass->at(j)==M)
							{
								template_weight_ZP = truth_all_vZPwgt->at(j);
								template_weight_KK = truth_all_vKKwgt->at(j);
								break;
							}
						}
						
						/// imass
						tsname_ZP = "hMassZprime_SSM" + (TString)_s(M) + "_template";
						tsname_KK = "hMassKK"         + (TString)_s(M) + "_template";
						h1Map[tsname_ZP]->Fill(mass,wgt*noEWkfactor_weight*template_weight_ZP);
						h1Map[tsname_KK]->Fill(mass,wgt*noEWkfactor_weight*template_weight_KK);
						
						/// pT leading
						tsname_ZP = "hpTLeadingZprime_SSM" + (TString)_s(M) + "_template";
						tsname_KK = "hpTLeadingKK"         + (TString)_s(M) + "_template";
						h1Map[tsname_ZP]->Fill(pTLeading,wgt*noEWkfactor_weight*template_weight_ZP);
						h1Map[tsname_KK]->Fill(pTLeading,wgt*noEWkfactor_weight*template_weight_KK);
					}
				}
				
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
				
				h1Map["hMass_1d_full_"+tsMCname]->Fill(mass*GeV2TeV,wgt*event_weight); // for the 1d limit
				// for the 2d limit
				if(slice_cost<=h1Map["hCosThetaLimitBins_DYmumu"]->GetNbinsX() && slice_cost>0)
				{
					h1Map["hMass_cosThSlice_"+(TString)_s(slice_cost)+"_"+tsMCname]->Fill(mass*GeV2TeV,wgt*event_weight);
				}
				if(slice_deta<=h1Map["hdEtaLimitBins_DYmumu"]->GetNbinsX() && slice_deta>0)
				{
					h1Map["hMass_dEtaSlice_"+(TString)_s(slice_deta)+"_"+tsMCname]->Fill(mass*GeV2TeV,wgt*event_weight);
				}
				
				h1Map["hCosThetaLimitBins_"+tsMCname]->Fill(cosThetaCS,wgt*event_weight);
				h1Map["hdEtaLimitBins_"+tsMCname]->Fill(dEta,wgt*event_weight);
				
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
		// tlvmurecaBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmureca);
		// tlvmurecbBoosted = K->Boost(tlvmureca,tlvmurecb,tlvmurecb);
		tlvmurecaBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmureca);
		tlvmurecbBoosted = fkinematics::Boost(tlvmureca,tlvmurecb,tlvmurecb);
		(*tv3murecaBoosted) = tlvmurecaBoosted->Vect();
		(*tv3murecbBoosted) = tlvmurecbBoosted->Vect();
	
		////////////////////////////
		/// analysis statrs here ///
		////////////////////////////
	
		ca = charge->at(imuonrec);
		cb = charge->at(iamuonrec);
		if(ca*cb>=0.) _WARNING("ca*cb>=0, skipping event");
		// mass          = K->imass(tlvmureca,tlvmurecb);
		// yQ            = K->ySystem(tlvmureca,tlvmurecb);
		// QT            = K->QT(tlvmureca,tlvmurecb);
		// cosThetaCS    = K->cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
		// cosThetaHE    = K->cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
		mass          = fkinematics::imass(tlvmureca,tlvmurecb);
		yQ            = fkinematics::ySystem(tlvmureca,tlvmurecb);
		QT            = fkinematics::QT(tlvmureca,tlvmurecb);
		cosThetaCS    = fkinematics::cosThetaCollinsSoper(tlvmureca,ca,tlvmurecb,cb);
		cosThetaHE    = fkinematics::cosThetaBoost(tlvmureca,ca,tlvmurecb,cb);
		etaLeading    = eta->at(0);
		etaSubleading = eta->at(1);
		phiLeading    = phi->at(0);
		phiSubleading = phi->at(1);
		pTLeading     = pt->at(0)*MeV2GeV;
		pTSubleading  = pt->at(1)*MeV2GeV;
		dEta  = fabs(etaLeading-etaSubleading);
		slice_cost = h1Map["hCosThetaLimitBins_DYmumu"]->FindBin(cosThetaCS);
		slice_deta = h1Map["hdEtaLimitBins_DYmumu"]->FindBin(dEta);
		
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
		
		h1Map["hMass_1d_full_Data"]->Fill(mass*GeV2TeV); // for the 1d limit
		// for the 2d limit
		if(slice_cost<=h1Map["hCosThetaLimitBins_DYmumu"]->GetNbinsX() && slice_cost>0)
		{
			h1Map["hMass_cosThSlice_"+(TString)_s(slice_cost)+"_Data"]->Fill(mass*GeV2TeV);
		}
		if(slice_deta<=h1Map["hdEtaLimitBins_DYmumu"]->GetNbinsX() && slice_deta>0)
		{
			h1Map["hMass_dEtaSlice_"+(TString)_s(slice_deta)+"_Data"]->Fill(mass*GeV2TeV);
		}
		
		h1Map["hCosThetaLimitBins_Data"]->Fill(cosThetaCS);
		h1Map["hdEtaLimitBins_Data"]->Fill(dEta);
		
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


void stitchProc(TString sProc)
{
	// remember old dir
	TDirectory* olddir = gDirectory;

	TFile* fTemplates = new TFile("plots/"+sProc+"_templates.root", "RECREATE");
	
	olddir->cd();
	
	TObjArray* template_cosThetaSlices = new TObjArray;
	TObjArray* template_dEtaSlices = new TObjArray;
	
	TString name   = "";
	TString titles = "";
	
	vector<TString> modelNames;
	if(sProc=="Gmm")
	{
		modelNames.push_back("Gmm_01_1750");
		modelNames.push_back("Gmm_01_2000");
		modelNames.push_back("Gmm_01_2250");
	}
	else if(sProc=="DYmumu")  modelNames.push_back("DYmumu");
	else if(sProc=="Diboson") modelNames.push_back("Diboson");
	else if(sProc=="Data")    modelNames.push_back("Data");
	
	for(unsigned int imodel=0 ; imodel<modelNames.size() ; imodel++)
	{
		vector<TH1D*> vhMass_cosThetaSlices;
		vector<TH1D*> vhMass_dEtaSlices;
		
		for(int i=1 ; i<=nCosThetaBinsLimit ; i++)
		{
			TString baseName = "hMass_cosThSlice_"+(TString)_s(i)+"_"+modelNames[imodel];
			vhMass_cosThetaSlices.push_back( (TH1D*)h1Map[baseName] );
		}
		for(int i=1 ; i<=ndEtaBinsLimit ; i++)
		{
			TString baseName = "hMass_dEtaSlice_"+(TString)_s(i)+"_"+modelNames[imodel];
			vhMass_dEtaSlices.push_back( (TH1D*)h1Map[baseName] );
		}
		
		name   = "mHat_stitchedCosTheta_"+modelNames[imodel]+"_"+(TString)_s(imodel);
		titles = "mass in stitched cos#theta* slices;Extended m_{#mu#mu} TeV;Events";
		template_cosThetaSlices->Add( (TH1D*)stitch(vhMass_cosThetaSlices,name,titles)->Clone("") );
		template_cosThetaSlices->At(imodel)->Print();
		
		name   = "mHat_stitcheddEta_"+modelNames[imodel]+"_"+(TString)_s(imodel);
		titles = "mass in stitched #Delta#eta slices;Extended m_{#mu#mu} TeV;Events";
		template_dEtaSlices->Add( (TH1D*)stitch(vhMass_dEtaSlices,name,titles)->Clone("") );
		template_dEtaSlices->At(imodel)->Print();
		
		
		fTemplates->cd();
		h1Map["hCosThetaLimitBins_"+modelNames[imodel]]->SetMinimum(0.5*h1Map["hCosThetaLimitBins_"+modelNames[imodel]]->GetMinimum());
		h1Map["hCosThetaLimitBins_"+modelNames[imodel]]->Write();
		h1Map["hdEtaLimitBins_"+modelNames[imodel]]->SetMinimum(0.5*h1Map["hdEtaLimitBins_"+modelNames[imodel]]->GetMinimum());
		h1Map["hdEtaLimitBins_"+modelNames[imodel]]->Write();
		h1Map["hMass_1d_full_"+modelNames[imodel]]->Write();
		olddir->cd();
	}

	fTemplates->cd();
	if(modelNames.size()>1)
	{
		template_cosThetaSlices->SetOwner(kTRUE);
		template_cosThetaSlices->Write("template_cosThetaSlices", TObject::kSingleKey);
	}
	else template_cosThetaSlices->At(0)->Write();
	
	if(modelNames.size()>1)
	{
		template_dEtaSlices->SetOwner(kTRUE);
		template_dEtaSlices->Write("template_dEtaSlices", TObject::kSingleKey);
	}
	else template_dEtaSlices->At(0)->Write();
	
	fTemplates->Write();
	fTemplates->Close();
}

void runMCproc(TString mcName)
{
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		init(it->second);
		Int_t N = tree->GetEntriesFast();
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			
			////////////////////////////////////////////
			//// blocks of analysis go here ////////////
			////////////////////////////////////////////
			if(!truth_all_isValid) continue;
			// hfill("MC", mcName, wgtMap[it->first]); //////////////////////////////////////////////
			hfill("MC", mcName, getLumiWeight(it->first,all_RunNumber,all_randomized_decision)); ////
			/////////////////////////////////////////////////////////////////////////////////////////
		}
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
	
	/////////////////////
	setFermions(); //////
	/////////////////////
	
	style();
	colors();
	hbook();
	text();

	Int_t N = 0;
	TString mcName = "";
	
	// data
	init();
	N = tree->GetEntriesFast();
	for(Int_t entry=0 ; entry<N ; entry++)
	{
		tree->GetEntry(entry);
		////////////////////////////////////
		//// blocks of analysis go here ////
		////////////////////////////////////
		hfill("DATA"); /////////////////////
		////////////////////////////////////
	}
	

	//---- MCs
	mcName = "DYmumu";
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
			if(!truth_all_isValid) continue;
			// hfill("MC", mcName, wgtMap[it->first]); //////////////////////////////////////////////
			hfill("MC", mcName, getLumiWeight(it->first,all_RunNumber,all_randomized_decision)); ////
			/////////////////////////////////////////////////////////////////////////////////////////
		}
	} 
	hMCsumall(mcName);
	
	mcName = "Diboson";
	setMCtrees(mcName);
	runMCproc(mcName);
	hMCsumall(mcName);
	
	for(double M=mGmmMin ; M<=mGmmMax ; M+=dMGmm)
	{
		mcName = "Gmm_01_" + (TString)_s(M);
		setMCtrees(mcName);
		runMCproc(mcName);
		//hMCsumall(mcName);
	}
	
	for(double M=mZprimeMin ; M<=mZprimeMax ; M+=dMZprime)
	{
		if(M==1250.) continue;
		mcName = "Zprime_SSM" + (TString)_s(M);
		setMCtrees(mcName);
		runMCproc(mcName);
		//hMCsumall(mcName);
	}
	
	
	stitchProc("Data");
	stitchProc("DYmumu");
	stitchProc("Diboson");
	stitchProc("Gmm");
	
	
	// finalize
	hscale2Zpeak();
	hdraw();
	save("plots");
}

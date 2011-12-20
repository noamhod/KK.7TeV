#include "all.h"

TLorentzVector* tlva_tru = new TLorentzVector;
TLorentzVector* tlvb_tru = new TLorentzVector;
int imuon_tru  = 0;
int iamuon_tru = 0;
float ca_tru = 0.;
float cb_tru = 0.;
float M_tru = 0.;
float YQ_tru = 0.;
float Ystar_tru = 0.;
float COSTHETA_tru = 0.;
float ETAMU_tru = 0.;

TLorentzVector* tlva_rec = new TLorentzVector;
TLorentzVector* tlvb_rec = new TLorentzVector;
int imuon_rec  = 0;
int iamuon_rec = 0;
float ca_rec = 0.;
float cb_rec = 0.;
float M_rec = 0.;
float YQ_rec = 0.;
float Ystar_rec = 0.;
float COSTHETA_rec = 0.;
float ETAMU_rec = 0.;

// bins for the cosTheta histos
double    costmin   = minCosTheta;
double    costmax   = maxCosTheta;
const int ncostbins = nCosThetaBins;

// bins for the etamu histos 
double   etamumin   = minetamu;
double   etamumax   = maxetamu;
int      netamubins = nbinsetamu;

// bins for the yQ histos 
double   yqmin   = minyQ;
double   yqmax   = maxyQ;
int      nyqbins = nyQbins;

// bins for the mHat histos
double    imassmin   = minMassBin; //120.;
double    imassmax   = maxMassBin; //4000.;
const int nimassbins = niMassBins; // 400;

// bins for the ystar histos
double     minyStar   = minystar; //120.;
double     maxyStar   = maxystar; //4000.;
static int nyStarbins = nystarbins;

static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nimassbins+1];

// bins for the afb (the binning is in mHat)
static double   imass_afb_min   = minMassBin; //120.;
static double   imass_afb_max   = maxMassBin; //4000.;
const int       imass_afb_nbins = nMassBins;  // const int nMassBins is defined in constants.h
static Double_t logMmin_afb;
static Double_t logMmax_afb;
static Double_t logMbinwidth_afb;
static Double_t imass_afb_bins[imass_afb_nbins+1];



TFile* fWeights;
TDirectory* dirAllHistograms;
TDirectory* dirCostHistograms;
TDirectory* dirMassHistograms;
TDirectory* diryQHistograms;
TDirectory* dirEtaHistograms;
TDirectory* diryStarHistograms;
TDirectory* dirNtuples;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvBinnedHistos_imass;
vector<TH1D*>  hvBinnedHistos_imass_unscaled;
vector<TH1D*>  hvBinnedHistos_imassRes;
vector<vector<TH1D*> > hvvBinnedHistos_cosTh;
vector<vector<TH1D*> > hvvBinnedHistos_cosTh_unscaled;
vector<vector<TH1D*> > hvvBinnedHistos_yQ;
vector<vector<TH1D*> > hvvBinnedHistos_yQ_unscaled;
vector<vector<TH1D*> > hvvBinnedHistos_eta;
vector<vector<TH1D*> > hvvBinnedHistos_eta_unscaled;
vector<vector<TH1D*> > hvvBinnedHistos_yStar;
vector<vector<TH1D*> > hvvBinnedHistos_yStar_unscaled;
vector<vector<TTree*> > vvtBinnedNtuples;


TTree* tMassBins;
TTree* tAfbMassBins;
vector<double> dvWeights;
vector<Color_t> cvColors;

float mass_tru, mass_rec, mass_wgt,
	  cost_tru, cost_rec, cost_wgt,
	  yQ_tru, yQ_rec, yQ_wgt,
	  eta_tru, eta_rec, eta_wgt,
	  yStar_tru, yStar_rec, yStar_wgt,
	  xscn_wgt;
TLorentzVector* tlv1Tru = new TLorentzVector;
TLorentzVector* tlv2Tru = new TLorentzVector;
TLorentzVector* tlv1Rec = new TLorentzVector;
TLorentzVector* tlv2Rec = new TLorentzVector;

string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";
TString tsname;
TString tsrange;

bool doLogx = true;

double sumWeights = 0.;

void clearSamples()
{	
	svNames.clear();
	svPaths.clear();
	for(int n=0 ; n<(int)hvBinnedHistos_imass.size() ; n++)
	{
		if(hvBinnedHistos_imass[n]!=NULL)          delete hvBinnedHistos_imass[n];
		if(hvBinnedHistos_imass_unscaled[n]!=NULL) delete hvBinnedHistos_imass_unscaled[n];
		if(hvBinnedHistos_imassRes[n]!=NULL)       delete hvBinnedHistos_imassRes[n];
		for(int m=0 ; m<(int)hvvBinnedHistos_cosTh[n].size() ; m++)
		{
			if(hvvBinnedHistos_cosTh[n][m]!=NULL)          delete hvvBinnedHistos_cosTh[n][m];
			if(hvvBinnedHistos_cosTh_unscaled[n][m]!=NULL) delete hvvBinnedHistos_cosTh_unscaled[n][m];
			
			if(hvvBinnedHistos_yQ[n][m]!=NULL)          delete hvvBinnedHistos_yQ[n][m];
			if(hvvBinnedHistos_yQ_unscaled[n][m]!=NULL) delete hvvBinnedHistos_yQ_unscaled[n][m];
			
			if(hvvBinnedHistos_eta[n][m]!=NULL)          delete hvvBinnedHistos_eta[n][m];
			if(hvvBinnedHistos_eta_unscaled[n][m]!=NULL) delete hvvBinnedHistos_eta_unscaled[n][m];
			
			if(hvvBinnedHistos_yStar[n][m]!=NULL)          delete hvvBinnedHistos_yStar[n][m];
			if(hvvBinnedHistos_yStar_unscaled[n][m]!=NULL) delete hvvBinnedHistos_yStar_unscaled[n][m];
		}
		hvvBinnedHistos_cosTh[n].clear();
		hvvBinnedHistos_yQ[n].clear();
		hvvBinnedHistos_eta[n].clear();
		hvvBinnedHistos_yStar[n].clear();
	}
	hvBinnedHistos_imass.clear();
	hvBinnedHistos_imass_unscaled.clear();
	hvBinnedHistos_imassRes.clear();
	hvvBinnedHistos_cosTh.clear();
	hvvBinnedHistos_cosTh_unscaled.clear();
	hvvBinnedHistos_yQ.clear();
	hvvBinnedHistos_yQ_unscaled.clear();
	hvvBinnedHistos_eta.clear();
	hvvBinnedHistos_eta_unscaled.clear();
	hvvBinnedHistos_yStar.clear();
	hvvBinnedHistos_yStar_unscaled.clear();
	dvWeights.clear();
	cvColors.clear();
}

void addSample(string sname, Color_t color, double events, double sigma /*in [mb]*/)
{	
	svNames.push_back(sname);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	
	if(doLogx)
	{
		hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nimassbins,xbins));
		hvBinnedHistos_imass_unscaled.push_back(new TH1D((sName+"_unscaled").c_str(),(sName+"_unscaled").c_str(),nimassbins,xbins));
	}
	else
	{
		hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nimassbins,imassmin,imassmax));
		hvBinnedHistos_imass_unscaled.push_back(new TH1D((sName+"_unscaled").c_str(),(sName+"_unscaled").c_str(),nimassbins,imassmin,imassmax));
	}

	hvBinnedHistos_imassRes.push_back(new TH1D((sName+"Res").c_str(),(sName+"Res").c_str(),nimassbins,-0.2,+0.2));

	vector<TH1D*> vTmp;
	vector<TH1D*> vTmp_unscaled;
	for(int b=0 ; b<imass_afb_nbins ; b++)
	{
		vTmp.push_back( new TH1D((sName+"_massbin_cost_"+_s(b)).c_str(),(sName+"_massbin_cost_"+_s(b)).c_str(),ncostbins,costmin,costmax) );
		vTmp_unscaled.push_back( new TH1D((sName+"unscaled_cost_massbin_"+_s(b)).c_str(),(sName+"unscaled_cost_massbin_"+_s(b)).c_str(),ncostbins,costmin,costmax) );
	}
	hvvBinnedHistos_cosTh.push_back( vTmp );
	hvvBinnedHistos_cosTh_unscaled.push_back( vTmp_unscaled );
	
	
	vTmp.clear();
	vTmp_unscaled.clear();
	for(int b=0 ; b<imass_afb_nbins ; b++)
	{
		vTmp.push_back( new TH1D((sName+"_massbin_yQ_"+_s(b)).c_str(),(sName+"_massbin_yQ_"+_s(b)).c_str(),nyqbins,yqmin,yqmax) );
		vTmp_unscaled.push_back( new TH1D((sName+"unscaled_massbin_yQ_"+_s(b)).c_str(),(sName+"unscaled_massbin_yQ_"+_s(b)).c_str(),nyqbins,yqmin,yqmax) );
	}
	hvvBinnedHistos_yQ.push_back( vTmp );
	hvvBinnedHistos_yQ_unscaled.push_back( vTmp_unscaled );
	
	
	vTmp.clear();
	vTmp_unscaled.clear();
	for(int b=0 ; b<imass_afb_nbins ; b++)
	{
		vTmp.push_back( new TH1D((sName+"_massbin_etamu_"+_s(b)).c_str(),(sName+"_massbin_etamu_"+_s(b)).c_str(),etalogicnbins,etalogicbins) );
		vTmp_unscaled.push_back( new TH1D((sName+"unscaled_massbin_etamu_"+_s(b)).c_str(),(sName+"unscaled_massbin_etamu_"+_s(b)).c_str(),etalogicnbins,etalogicbins) );
	}
	hvvBinnedHistos_eta.push_back( vTmp );
	hvvBinnedHistos_eta_unscaled.push_back( vTmp_unscaled );
	
	vTmp.clear();
	vTmp_unscaled.clear();
	for(int b=0 ; b<imass_afb_nbins ; b++)
	{
		vTmp.push_back( new TH1D((sName+"_massbin_yStar_"+_s(b)).c_str(),(sName+"_massbin_yStar_"+_s(b)).c_str(),nyStarbins,minyStar,maxyStar) );
		vTmp_unscaled.push_back( new TH1D((sName+"unscaled_massbin_yStar_"+_s(b)).c_str(),(sName+"unscaled_massbin_yStar_"+_s(b)).c_str(),nyStarbins,minyStar,maxyStar) );
	}
	hvvBinnedHistos_yStar.push_back( vTmp );
	hvvBinnedHistos_yStar_unscaled.push_back( vTmp_unscaled );
	
	
	dvWeights.push_back(luminosity/(events/(sigma*mb2fb)));
	cvColors.push_back(color);
	
	sumWeights += luminosity/(events/(sigma*mb2fb));
}

// initialize the trees that will be handed to RooFit
void initOutNtuples(TDirectory* tDir)
{
	tDir->cd();
	
	for(int t=1 ; t<=imass_afb_nbins ; t++)
	{
		vector<TTree*> vtBinnedNtuplesTmp;
		vtBinnedNtuplesTmp.clear();
		vvtBinnedNtuples.push_back(vtBinnedNtuplesTmp);
		
		for(int mod=Z0 ; mod<=DT ; mod++)
		{
			if(mod==Z0) tsname = "tree_Z0_" + (TString)tostring(t);
			if(mod==ZP) tsname = "tree_ZP_" + (TString)tostring(t);
			if(mod==KK) tsname = "tree_KK_" + (TString)tostring(t);
			if(mod==DT) tsname = "tree_DT_" + (TString)tostring(t);
		
			vvtBinnedNtuples[t-1].push_back( new TTree(tsname, tsname) );
			vvtBinnedNtuples[t-1][mod]->Branch( "mass_tru", &mass_tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "mass_rec", &mass_rec );
			vvtBinnedNtuples[t-1][mod]->Branch( "mass_wgt", &mass_wgt );
			vvtBinnedNtuples[t-1][mod]->Branch( "cost_tru", &cost_tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "cost_rec", &cost_rec );
			vvtBinnedNtuples[t-1][mod]->Branch( "cost_wgt", &cost_wgt );
			vvtBinnedNtuples[t-1][mod]->Branch( "yQ_tru",   &yQ_tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "yQ_rec",   &yQ_rec );
			vvtBinnedNtuples[t-1][mod]->Branch( "yQ_wgt",   &yQ_wgt );
			vvtBinnedNtuples[t-1][mod]->Branch( "eta_tru",  &eta_tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "eta_rec",  &eta_rec );
			vvtBinnedNtuples[t-1][mod]->Branch( "eta_wgt",  &eta_wgt );
			vvtBinnedNtuples[t-1][mod]->Branch( "yStar_tru",  &yStar_tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "yStar_rec",  &yStar_rec );
			vvtBinnedNtuples[t-1][mod]->Branch( "yStar_wgt",  &yStar_wgt );
			vvtBinnedNtuples[t-1][mod]->Branch( "xscn_wgt", &xscn_wgt );
			
			vvtBinnedNtuples[t-1][mod]->Branch( "tlv1Tru", &tlv1Tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "tlv2Tru", &tlv2Tru );
			vvtBinnedNtuples[t-1][mod]->Branch( "tlv1Rec", &tlv1Rec );
			vvtBinnedNtuples[t-1][mod]->Branch( "tlv2Rec", &tlv2Rec );
		}
	}
}

void writeOutNtuples(TDirectory* tDir)
{
	tDir->cd();

	for(int t=0 ; t<imass_afb_nbins ; t++)
	{
		for(int mod=Z0 ; mod<=DT ; mod++)
		{
			fWeights = vvtBinnedNtuples[t][mod]->GetCurrentFile();
			fWeights->cd();
			tDir->cd();
			vvtBinnedNtuples[t][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	tMassBins->Write();
	tAfbMassBins->Write();
	
	fWeights->Write();
	fWeights->Close();
}



void fillNtuple(TTree* t, int counter, int modulu)
{
	t->Fill();
	if(counter%modulu==0)
	{
		t->FlushBaskets();
		//t->Write("", TObject::kOverwrite);
	}
	counter++;
}



int plot_ratio_weights()
{
	setMSGlevel(VISUAL,VISUAL,VISUAL);

	style();
	colors();
	
	fWeights = new TFile("weights.root", "RECREATE");

	dirNtuples = fWeights->mkdir("ntuples");
	dirCostHistograms = fWeights->mkdir("cosTheta_histograms");
	dirMassHistograms = fWeights->mkdir("iMass_histograms");
	diryQHistograms   = fWeights->mkdir("yQ_histograms");
	dirEtaHistograms  = fWeights->mkdir("etamu_histograms");
	diryStarHistograms  = fWeights->mkdir("yStar_histograms");
	dirAllHistograms  = fWeights->mkdir("all_histograms");
	
	dirAllHistograms->cd();
	
	initOutNtuples(dirNtuples);
	
	int counter = 0;
	int modulu = 1000;
	
	float mHat;
	float qT;
	float ysystem;
	float cosThetaHE;
	float cosThetaCS;
	vector<int>*    id     = new vector<int>;
	vector<double>* charge = new vector<double>;
	vector<double>* px     = new vector<double>;
	vector<double>* py     = new vector<double>;
	vector<double>* pz     = new vector<double>;
	vector<double>* E      = new vector<double>;
	vector<double>* m      = new vector<double>;
	vector<double>* y      = new vector<double>;
	vector<double>* pT     = new vector<double>;
	vector<double>* eta    = new vector<double>;
	vector<double>* phi    = new vector<double>;
	vector<double>* theta  = new vector<double>;	
	
	vector<float>* truth_all_mc_pt      = new vector<float>;
	vector<float>* truth_all_mc_m       = new vector<float>;
	vector<float>* truth_all_mc_eta     = new vector<float>;
	vector<float>* truth_all_mc_phi     = new vector<float>;
	vector<int>*   truth_all_mc_status  = new vector<int>;
	vector<int>*   truth_all_mc_barcode = new vector<int>;
	vector<int>*   truth_all_mc_pdgId   = new vector<int>;
	vector<float>* truth_all_mc_charge  = new vector<float>;
	bool  truth_all_isValid;
	float truth_all_Mhat;
	float truth_all_CosThetaCS;
	float truth_all_CosThetaHE;
	float truth_all_ySystem;
	float truth_all_QT;
	
	bool recon_all_isValid;
	vector<float>* recon_all_E = new vector<float>;
	vector<float>* recon_all_pt = new vector<float>;
	vector<float>* recon_all_m = new vector<float>;
	vector<float>* recon_all_eta = new vector<float>;
	vector<float>* recon_all_phi = new vector<float>;
	vector<float>* recon_all_px = new vector<float>;
	vector<float>* recon_all_py = new vector<float>;
	vector<float>* recon_all_pz = new vector<float>;
	vector<float>* recon_all_charge = new vector<float>;
	vector<float>* recon_all_y = new vector<float>;
	vector<int>*   recon_all_id = new vector<int>;
	vector<float>* recon_all_theta = new vector<float>;
	float recon_all_Mhat;
	float recon_all_CosThetaCS;
	float recon_all_CosThetaHE;
	float recon_all_ySystem;
	float recon_all_QT;

	string sModel = "";
	string sMass  = "";
	cout << "chose mass_tru(GeV)...";
	cin >> sMass;
	

	
	
	logMmin  = log10(imassmin);
	logMmax  = log10(imassmax);
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)nimassbins );
	xbins[0] = imassmin;
	for(Int_t i=1 ; i<=nimassbins ; i++) xbins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	tMassBins = new TTree("MassBins", "MassBins");
	Double_t MassBin;
	tMassBins->Branch( "MassBin", &MassBin );
	for(int i=0 ; i<nimassbins ; i++)
	{
		MassBin = xbins[i];
		tMassBins->Fill();
	}
	
	
	
	TCanvas* cnv = new TCanvas("cnv", "cnv", 0,0,1200,800);
	cnv->Divide(2,2);
	
	TVirtualPad* pad_recon_template = cnv->cd(2);
	pad_recon_template->SetLogy();
	if(doLogx) pad_recon_template->SetLogx();
	pad_recon_template->SetTickx(1);
	pad_recon_template->SetTicky(1);
	
	TVirtualPad* pad_sigma = cnv->cd(1);
	pad_sigma->SetLogy();
	if(doLogx) pad_sigma->SetLogx();
	pad_sigma->SetTickx(1);
	pad_sigma->SetTicky(1);
	
	TVirtualPad* pad_weights = cnv->cd(3);
	pad_weights->SetLogy();
	if(doLogx) pad_weights->SetLogx();
	pad_weights->SetTickx(1);
	pad_weights->SetTicky(1);
	
	TVirtualPad* pad_compare = cnv->cd(4);
	pad_compare->SetLogy();
	if(doLogx) pad_compare->SetLogx();
	pad_compare->SetTickx(1);
	pad_compare->SetTicky(1);
	
	cnv->cd();
	cnv->Draw();
	
	
	
	TLegend* leg_mass = new TLegend(0.1462841,0.1774325,0.5373268,0.4004816,NULL,"brNDC");
	leg_mass->SetFillColor(kWhite);
	
	TLegend* leg_mass_recon = new TLegend(0.1446488,0.1788644,0.6376115,0.4271373,NULL,"brNDC");
	leg_mass_recon->SetFillColor(kWhite);
	
	TLegend* leg_weights = new TLegend(0.1480616,0.7509715,0.4342337,0.9272078,NULL,"brNDC");
	leg_weights->SetFillColor(kWhite);
	
	TLegend* leg_compare = new TLegend(0.2840022,0.8211356,0.8361901,0.9290803,NULL,"brNDC");
	leg_compare->SetFillColor(kWhite);
	
	TPaveText* pvtxt = new TPaveText(0.3345178,0.7347798,0.7072882,0.9317789,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( "#splitline{Sum of binned #bf{truth}}{samples normalized to ~"+(TString)tostring(luminosity,2)+"/fb}" );
	
	TPaveText* pvtxt_recon = new TPaveText(0.3258082,0.7698618,0.6985786,0.9236831,"brNDC");
	pvtxt_recon->SetFillColor(kWhite);
	txt = pvtxt_recon->AddText( "#splitline{Sum of binned #bf{template}}{samples normalized to ~"+(TString)tostring(luminosity,2)+"/fb}" );
	
	TPaveText* pvtxt_compare = new TPaveText(0.1688387,0.4001352,0.4258138,0.5691372,"brNDC");
	pvtxt_compare->SetFillColor(kWhite);
	txt = pvtxt_compare->AddText( "#splitline{Template vs. #it{ATLAS}}{MC10 reconstructed}" );
	
	
	
	
	// for the binned-wights histograms
	logMmin_afb       = log10(imass_afb_min);
	logMmax_afb       = log10(imass_afb_max);
	logMbinwidth_afb  = (Double_t)( (logMmax_afb-logMmin_afb)/(Double_t)imass_afb_nbins );
	imass_afb_bins[0] = imass_afb_min;
	for(Int_t i=1 ; i<=imass_afb_nbins ; i++) imass_afb_bins[i] = TMath::Power( 10,(logMmin_afb + i*logMbinwidth_afb) );
	
	///////////////////////////////
	// imass_afb_bins[0] = imass_afb_min;
	// imass_afb_bins[1] = 200.;
	// imass_afb_bins[2] = 300.;
	// imass_afb_bins[3] = 430.;
	// imass_afb_bins[4] = 600.;
	// imass_afb_bins[5] = 1000.;
	// imass_afb_bins[6] = imass_afb_max;
	///////////////////////////////
	
	tAfbMassBins = new TTree("AfbMassBins", "AfbMassBins");
	Double_t AfbMassBin;
	tAfbMassBins->Branch( "AfbMassBin", &AfbMassBin );
	for(int i=0 ; i<imass_afb_nbins ; i++)
	{
		AfbMassBin = imass_afb_bins[i];
		tAfbMassBins->Fill();
	}
	
	
	
	//dirCostHistograms->cd();
	TH1D* hDummy_afb = new TH1D("dummy","dummy",imass_afb_nbins,imass_afb_bins);
	
	vector<TH1D*> vhCosThSumTmp;
	vector<TH1D*> vhCosThSumTmp_unscaled;
	vector<TH1D*> vhyQSumTmp;
	vector<TH1D*> vhyQSumTmp_unscaled;
	vector<TH1D*> vhEtaSumTmp;
	vector<TH1D*> vhEtaSumTmp_unscaled;
	vector<TH1D*> vhyStarSumTmp;
	vector<TH1D*> vhyStarSumTmp_unscaled;
	
	vector<TH1D*> vhCosThSumZ0d3pd_unscaled;
	vector<TH1D*> vhCosThSumZ0d3pd_acceptance;
	vector<TH1D*> vhCosThSumZ0d3pd;
	vector<TH1D*> vhCosThSumReconZ0d3pd;
	vector<TH1D*> vhCosThSumReconDTd3pd;
	
	vector<TH1D*> vhyQSumZ0d3pd_unscaled;
	vector<TH1D*> vhyQSumZ0d3pd;
	vector<TH1D*> vhyQSumReconZ0d3pd;
	vector<TH1D*> vhyQSumReconDTd3pd;
	
	vector<TH1D*> vhEtaSumZ0d3pd_unscaled;
	vector<TH1D*> vhEtaSumZ0d3pd_acceptance;
	vector<TH1D*> vhEtaSumZ0d3pd;
	vector<TH1D*> vhEtaSumReconZ0d3pd;
	vector<TH1D*> vhEtaSumReconDTd3pd;
	
	vector<TH1D*> vhyStarSumZ0d3pd_unscaled;
	vector<TH1D*> vhyStarSumZ0d3pd_acceptance;
	vector<TH1D*> vhyStarSumZ0d3pd;
	vector<TH1D*> vhyStarSumReconZ0d3pd;
	vector<TH1D*> vhyStarSumReconDTd3pd;
	
	vector<vector<TH1D*> > vvhCosThSum;
	vector<vector<TH1D*> > vvhCosThSumRecTemplate;
	vector<vector<TH1D*> > vvhCosThSumAcceptance;
	vector<vector<TH1D*> > vvhCosThSumWeights;
	
	vector<vector<TH1D*> > vvhyQSum;
	vector<vector<TH1D*> > vvhyQSumRecTemplate;
	vector<vector<TH1D*> > vvhyQSumWeights;
	
	vector<vector<TH1D*> > vvhEtaSum;
	vector<vector<TH1D*> > vvhEtaSumRecTemplate;
	vector<vector<TH1D*> > vvhEtaSumAcceptance;
	vector<vector<TH1D*> > vvhEtaSumWeights;
	
	vector<vector<TH1D*> > vvhyStarSum;
	vector<vector<TH1D*> > vvhyStarSumRecTemplate;
	vector<vector<TH1D*> > vvhyStarSumAcceptance;
	vector<vector<TH1D*> > vvhyStarSumWeights;
	
	vector<TH1D*>          vhCosThSumXSweights;
	vector<TH1D*>          vhyQSumXSweights;
	vector<TH1D*>          vhEtaSumXSweights;
	vector<TH1D*>          vhyStarSumXSweights;

	
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{	
		tsrange = (TString)tostring(imass_afb_bins[i]) +  " GeV #rightarrow "  + (TString)tostring(imass_afb_bins[i+1]) + " GeV";
		
		vhCosThSumTmp.push_back( new TH1D("cost_"+tsrange,"cost_"+tsrange, ncostbins,costmin,costmax) );
		vhCosThSumTmp_unscaled.push_back( new TH1D("cost_xs"+tsrange,"cost_xs"+tsrange, ncostbins,costmin,costmax) );
		
		vhyQSumTmp.push_back( new TH1D("yQ_"+tsrange,"yQ_"+tsrange, nyqbins,yqmin,yqmax) );
		vhyQSumTmp_unscaled.push_back( new TH1D("yQ_xs"+tsrange,"yQ_xs"+tsrange, nyqbins,yqmin,yqmax) );
		
		vhEtaSumTmp.push_back( new TH1D("etamu_"+tsrange,"etamu_"+tsrange, etalogicnbins,etalogicbins) );
		vhEtaSumTmp_unscaled.push_back( new TH1D("etamu_xs"+tsrange,"etamu_xs"+tsrange, etalogicnbins,etalogicbins) );

		vhyStarSumTmp.push_back( new TH1D("yStar_"+tsrange,"yStar_"+tsrange, nyStarbins,minyStar,maxyStar) );
		vhyStarSumTmp_unscaled.push_back( new TH1D("yStar_xs"+tsrange,"yStar_xs"+tsrange, nyStarbins,minyStar,maxyStar) );
		
		vhCosThSumZ0d3pd.push_back( new TH1D("cost_sumZ0d3pd_"+tsrange, "cost_cost_sumZ0d3pd_"+tsrange, ncostbins,costmin,costmax) );
		vhCosThSumReconZ0d3pd.push_back( new TH1D("cost_sumRecZ0d3pd_"+tsrange, "cost_sumRecZ0d3pd_"+tsrange, ncostbins,costmin,costmax) );
		vhCosThSumReconDTd3pd.push_back( new TH1D("cost_sumRecDTd3pd_"+tsrange, "cost_sumRecDTd3pd_"+tsrange, ncostbins,costmin,costmax) );
		vhCosThSumZ0d3pd_unscaled.push_back( new TH1D("cost_sumZ0d3pd_unscaled_"+tsrange, "cost_sumZ0d3pd_unscaled_"+tsrange, ncostbins,costmin,costmax) );
		vhCosThSumZ0d3pd_acceptance.push_back( new TH1D("cost_sumZ0d3pd_acceptance_"+tsrange, "cost_sumZ0d3pd_acceptance_"+tsrange, ncostbins,costmin,costmax) );
		
		vhyQSumZ0d3pd.push_back( new TH1D("yQ_sumZ0d3pd_"+tsrange, "yQ_sumZ0d3pd_"+tsrange, nyqbins,yqmin,yqmax) );
		vhyQSumReconZ0d3pd.push_back( new TH1D("yQ_sumRecZ0d3pd_"+tsrange, "yQ_sumRecZ0d3pd_"+tsrange, nyqbins,yqmin,yqmax) );
		vhyQSumReconDTd3pd.push_back( new TH1D("yQ_sumRecDTd3pd_"+tsrange, "yQ_sumRecDTd3pd_"+tsrange, nyqbins,yqmin,yqmax) );
		vhyQSumZ0d3pd_unscaled.push_back( new TH1D("yQ_sumZ0d3pd_unscaled_"+tsrange, "yQ_sumZ0d3pd_unscaled_"+tsrange, nyqbins,yqmin,yqmax) );
		
		vhEtaSumZ0d3pd.push_back( new TH1D("etamu_sumZ0d3pd_"+tsrange, "etamu_sumZ0d3pd_"+tsrange, etalogicnbins,etalogicbins) );
		vhEtaSumReconZ0d3pd.push_back( new TH1D("etamu_sumRecZ0d3pd_"+tsrange, "etamu_sumRecZ0d3pd_"+tsrange, etalogicnbins,etalogicbins) );
		vhEtaSumReconDTd3pd.push_back( new TH1D("etamu_sumRecDTd3pd_"+tsrange, "etamu_sumRecDTd3pd_"+tsrange, etalogicnbins,etalogicbins) );
		vhEtaSumZ0d3pd_unscaled.push_back( new TH1D("etamu_sumZ0d3pd_unscaled_"+tsrange, "etamu_sumZ0d3pd_unscaled_"+tsrange, etalogicnbins,etalogicbins) );
		vhEtaSumZ0d3pd_acceptance.push_back( new TH1D("etamu_sumZ0d3pd_acceptance_"+tsrange, "etamu_sumZ0d3pd_acceptance_"+tsrange, etalogicnbins,etalogicbins) );
		
		vhyStarSumZ0d3pd.push_back( new TH1D("yStar_sumZ0d3pd_"+tsrange, "yStar_sumZ0d3pd_"+tsrange, nyStarbins,minyStar,maxyStar) );
		vhyStarSumReconZ0d3pd.push_back( new TH1D("yStar_sumRecZ0d3pd_"+tsrange, "yStar_sumRecZ0d3pd_"+tsrange, nyStarbins,minyStar,maxyStar) );
		vhyStarSumReconDTd3pd.push_back( new TH1D("yStar_sumRecDTd3pd_"+tsrange, "yStar_sumRecDTd3pd_"+tsrange, nyStarbins,minyStar,maxyStar) );
		vhyStarSumZ0d3pd_unscaled.push_back( new TH1D("yStar_sumZ0d3pd_unscaled_"+tsrange, "yStar_sumZ0d3pd_unscaled_"+tsrange, nyStarbins,minyStar,maxyStar) );
		vhyStarSumZ0d3pd_acceptance.push_back( new TH1D("yStar_sumZ0d3pd_acceptance_"+tsrange, "yStar_sumZ0d3pd_acceptance_"+tsrange, nyStarbins,minyStar,maxyStar) );
		
		
		
		vector<TH1D*> vhTmp;
		vhTmp.clear();
		
		vvhCosThSum.push_back(vhTmp);
		vvhCosThSumRecTemplate.push_back(vhTmp);
		vvhCosThSumAcceptance.push_back(vhTmp);
		vvhCosThSumWeights.push_back(vhTmp);
		
		vvhyQSum.push_back(vhTmp);
		vvhyQSumRecTemplate.push_back(vhTmp);
		vvhyQSumWeights.push_back(vhTmp);
		
		vvhEtaSum.push_back(vhTmp);
		vvhEtaSumRecTemplate.push_back(vhTmp);
		vvhEtaSumAcceptance.push_back(vhTmp);
		vvhEtaSumWeights.push_back(vhTmp);
		
		vvhyStarSum.push_back(vhTmp);
		vvhyStarSumRecTemplate.push_back(vhTmp);
		vvhyStarSumAcceptance.push_back(vhTmp);
		vvhyStarSumWeights.push_back(vhTmp);
		
		
		
		for(int mod=Z0 ; mod<=DT ; mod++)
		{
			if(mod==Z0) tsname = "Z0_" + tsrange;
			if(mod==ZP) tsname = "ZP_" + tsrange;
			if(mod==KK) tsname = "KK_" + tsrange;
			if(mod==DT) tsname = "DT_" + tsrange;
		
			vvhCosThSum[i].push_back( new TH1D("cost_sum"+tsname, "cost_sum"+tsname, ncostbins,costmin,costmax) );
			vvhCosThSumRecTemplate[i].push_back( new TH1D("cost_sumRec"+tsname, "cost_sumRec"+tsname, ncostbins,costmin,costmax) );
			vvhCosThSumAcceptance[i].push_back( new TH1D("cost_sumAcc"+tsname, "cost_sumAcc"+tsname, ncostbins,costmin,costmax) );
			vvhCosThSumWeights[i].push_back( new TH1D("cost_wgt"+tsname, "cost_wgt"+tsname, ncostbins,costmin,costmax) );
			
			vvhyQSum[i].push_back( new TH1D("yQ_sum"+tsname, "yQ_sum"+tsname, nyqbins,yqmin,yqmax) );
			vvhyQSumRecTemplate[i].push_back( new TH1D("yQ_sumRec"+tsname, "yQ_sumRec"+tsname, nyqbins,yqmin,yqmax) );
			vvhyQSumWeights[i].push_back( new TH1D("yQ_wgt"+tsname, "yQ_wgt"+tsname, nyqbins,yqmin,yqmax) );
			
			vvhEtaSum[i].push_back( new TH1D("etamu_sum"+tsname, "etamu_sum"+tsname, etalogicnbins,etalogicbins) );
			vvhEtaSumRecTemplate[i].push_back( new TH1D("etamu_sumRec"+tsname, "etamu_sumRec"+tsname, etalogicnbins,etalogicbins) );
			vvhEtaSumAcceptance[i].push_back( new TH1D("etamu_sumAcc"+tsname, "etamu_sumAcc"+tsname, etalogicnbins,etalogicbins) );
			vvhEtaSumWeights[i].push_back( new TH1D("etamu_wgt"+tsname, "etamu_wgt"+tsname, etalogicnbins,etalogicbins) );
			
			vvhyStarSum[i].push_back( new TH1D("yStar_sum"+tsname, "yStar_sum"+tsname, nyStarbins,minyStar,maxyStar) );
			vvhyStarSumRecTemplate[i].push_back( new TH1D("yStar_sumRec"+tsname, "yStar_sumRec"+tsname, nyStarbins,minyStar,maxyStar) );
			vvhyStarSumAcceptance[i].push_back( new TH1D("yStar_sumAcc"+tsname, "yStar_sumAcc"+tsname, nyStarbins,minyStar,maxyStar) );
			vvhyStarSumWeights[i].push_back( new TH1D("yStar_wgt"+tsname, "yStar_wgt"+tsname, nyStarbins,minyStar,maxyStar) );
			
			
		}
		vhCosThSumXSweights.push_back( new TH1D("cost_wgtXS_"+tsrange,"cost_wgtXS_"+tsrange, ncostbins,costmin,costmax) );
		vhyQSumXSweights.push_back( new TH1D("yQ_wgtXS_"+tsrange,"yQ_wgtXS_"+tsrange, nyqbins,yqmin,yqmax) );
		vhEtaSumXSweights.push_back( new TH1D("etamu_wgtXS_"+tsrange,"etamu_wgtXS_"+tsrange, etalogicnbins,etalogicbins) );
		vhyStarSumXSweights.push_back( new TH1D("yStar_wgtXS_"+tsrange,"yStar_wgtXS_"+tsrange, nyStarbins,minyStar,maxyStar) );
		
		
	}
	
	
	// combined histos
	//dirMassHistograms->cd();
	TH1D* hMassSumTmp;
	TH1D* hMassSumTmp_unscaled;
	TH1D* hResTmp;
	TH1D* hMassSumDTd3pd;
	TH1D* hMassSumZ0d3pd;
	TH1D* hMassSumZ0d3pd_unscaled;
	TH1D* hMassSumZ0d3pd_acceptance;
	
	vector<TH1D*> vhMassSum;
	vector<TH1D*> vhMassAcceptance;
	vector<TH1D*> vhMassWeights;
	vector<TH1D*> vhMassReconTemplate;
	vector<TH1D*> vhResTemplate;
	TH1D* hWeightsXS;

	TH1D* hMassReconDTd3pd;
	TH1D* hMassReconZ0d3pd;
	TH1D* hMassReconZPd3pd;
	TH1D* hResReconZ0d3pd;
	TH1D* hResReconZPd3pd;
	
	
	
	if(doLogx)
	{
		hMassSumTmp = new TH1D("sumTmp","sumTmp",nimassbins,xbins);
		hMassSumTmp_unscaled = new TH1D("sumTmp_unscaled","sumTmp_unscaled",nimassbins,xbins);

		hMassSumDTd3pd = new TH1D("sumDTd3pd","sumDTd3pd",nimassbins,xbins);
		hMassSumZ0d3pd = new TH1D("sumZ0d3pd","sumZ0d3pd",nimassbins,xbins);
		hMassSumZ0d3pd_unscaled = new TH1D("sumZ0d3pd_unscaled","sumZ0d3pd_unscaled",nimassbins,xbins);
		hMassSumZ0d3pd_acceptance = new TH1D("sumZ0d3pd_acceptance","sumZ0d3pd_acceptance",nimassbins,xbins);
		
		
		
		for(int mod=Z0 ; mod<=DT ; mod++)
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			if(mod==DT) tsname = "DT";
			
			
		
			vhMassSum.push_back( new TH1D("sum"+tsname,"sum"+tsname,nimassbins,xbins) );
			vhMassAcceptance.push_back( new TH1D("sumAcc"+tsname,"sumAcc"+tsname,nimassbins,xbins) );
			vhMassWeights.push_back( new TH1D("weights"+tsname,"weights"+tsname,nimassbins,xbins) );
			vhMassReconTemplate.push_back( new TH1D("RecTemplate"+tsname,"RecTemplate"+tsname,nimassbins,xbins) );
			
			
		}
		hWeightsXS = new TH1D("weightsXS","weightsXS",nimassbins,xbins);
		
		hMassReconDTd3pd = new TH1D("ReconDTd3pd","ReconDTd3pd",nimassbins,xbins);
		hMassReconZ0d3pd = new TH1D("ReconZ0d3pd","ReconZ0d3pd",nimassbins,xbins);
		hMassReconZPd3pd = new TH1D("ReconZPd3pd","ReconZPd3pd",nimassbins,xbins);
		
		
	}
	else
	{
		hMassSumTmp = new TH1D("sumTmp","sumTmp",nimassbins,imassmin,imassmax);
		hMassSumTmp_unscaled = new TH1D("sumTmp_unscaled","sumTmp_unscaled",nimassbins,imassmin,imassmax);
		
		hMassSumDTd3pd = new TH1D("sumDTd3pd","sumDTd3pd",nimassbins,imassmin,imassmax);
		hMassSumZ0d3pd = new TH1D("sumZ0d3pd","sumZ0d3pd",nimassbins,imassmin,imassmax);
		hMassSumZ0d3pd_unscaled = new TH1D("sumZ0d3pd_unscaled","sumZ0d3pd_unscaled",nimassbins,imassmin,imassmax);
		hMassSumZ0d3pd_acceptance = new TH1D("sumZ0d3pd_acceptance","sumZ0d3pd_acceptance",nimassbins,imassmin,imassmax);
		
		
		
		for(int mod=Z0 ; mod<=DT ; mod++)
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			if(mod==DT) tsname = "DT";
		
			vhMassSum.push_back( new TH1D("sum"+tsname,"sum"+tsname,nimassbins,imassmin,imassmax) );
			vhMassAcceptance.push_back( new TH1D("sumAcc"+tsname,"sumAcc"+tsname,nimassbins,imassmin,imassmax) );
			vhMassWeights.push_back( new TH1D("weights"+tsname,"weights"+tsname,nimassbins,imassmin,imassmax) );
			vhMassReconTemplate.push_back( new TH1D("RecTemplate"+tsname,"RecTemplate"+tsname,nimassbins,imassmin,imassmax) );
			
			
		}
		hWeightsXS = new TH1D("weightsXS","weightsXS",nimassbins,imassmin,imassmax);
		
		hMassReconDTd3pd = new TH1D("ReconDTd3pd","ReconDTd3pd",nimassbins,imassmin,imassmax);
		hMassReconZ0d3pd = new TH1D("ReconZ0d3pd","ReconZ0d3pd",nimassbins,imassmin,imassmax);
		hMassReconZPd3pd = new TH1D("ReconZPd3pd","ReconZPd3pd",nimassbins,imassmin,imassmax);
		
		
	}
	
	//dirAllHistograms->cd();
	hResTmp = new TH1D("ResTmp","ResTmp",nimassbins,-0.2,+0.2);
	hResReconZ0d3pd = new TH1D("ResReconZ0d3pd","ResReconZ0d3pd",nimassbins,-0.2,+0.2);
	hResReconZPd3pd = new TH1D("ResReconZPd3pd","ResReconZPd3pd",nimassbins,-0.2,+0.2);
	for(int mod=Z0 ; mod<=KK ; mod++)
	{
		if(mod==Z0) tsname = "Z0";
		if(mod==ZP) tsname = "ZP";
		if(mod==KK) tsname = "KK";
		vhResTemplate.push_back( new TH1D("Res"+tsname,"Res"+tsname,nimassbins,-0.2,+0.2) );
	}
	
	TFile* file;
	TTree* tree;
	double ymin = 0.;
	int vsize = 0;
	
	
	
	for(int model=Z0d3pd ; model<=KK ; model++)
	{
		
	
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hMassSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
		if(doLogx) hMassSumTmp_unscaled->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp_unscaled->GetNbinsX() ; b++) hMassSumTmp_unscaled->SetBinContent(b,0.); }
		for(int i=0 ; i<imass_afb_nbins ; i++)
		{
			
		
			vhCosThSumTmp[i]->Reset();
			vhCosThSumTmp_unscaled[i]->Reset();
			
			vhyQSumTmp[i]->Reset();
			vhyQSumTmp_unscaled[i]->Reset();
			
			vhEtaSumTmp[i]->Reset();
			vhEtaSumTmp_unscaled[i]->Reset();
			
			vhyStarSumTmp[i]->Reset();
			vhyStarSumTmp_unscaled[i]->Reset();
			
			
		}
		////////////////////////////
	
		
	
		if(model==Z0d3pd)
		{
			addSample("ATLASZ0/mcLocalControl_DYmumu_120M250",   col0, 19999, 0.0086861*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_250M400",   col1, 19996, 0.00041431*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_400M600",   col2, 19993, 0.000067464*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_600M800",   col3, 15994, 0.000011168*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_800M1000",  col5, 19992, 0.0000027277*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1000M1250", col5, 19995, 0.00000091646*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1250M1500", col5, 19993, 0.00000024942*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1500M1750", col5, 19997, 0.000000076876*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1750M2000", col5, 19993, 0.000000026003*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_M2000",     col5, 19996, 0.000000015327*nb2mb);
		}
		
		
		
		if(model==Z0)
		{
			addSample("PYTHIA8Z0/Pythia8_Z0mumu_120M500",  col0, nGeneratedEvents, 7.926e-09);
			addSample("PYTHIA8Z0/Pythia8_Z0mumu_500M1500", col1, nGeneratedEvents, 2.797e-11);
			addSample("PYTHIA8Z0/Pythia8_Z0mumu_1500M0",   col2, nGeneratedEvents, 8.809e-14);
		}
		if(model==ZP && sMass=="1000")
		{
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM1000mumu_120M500",  col0, nGeneratedEvents, 7.78812E-09);
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM1000mumu_500M1500", col1, nGeneratedEvents, 1.08535E-10);
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM1000mumu_1500M0",   col2, nGeneratedEvents, 2.42594E-13);
		}
		if(model==ZP && sMass=="2000")
		{
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM2000mumu_120M1000",  col0, nGeneratedEvents, 7.91467E-09);
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM2000mumu_1000M3000", col1, nGeneratedEvents, 1.94433E-12);
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM2000mumu_3000M0",    col2, nGeneratedEvents, 3.27844E-16);
		}
		if(model==ZP && sMass=="3000")
		{
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM3000mumu_120M1500",  col0, nGeneratedEvents, 7.94181E-09);
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM3000mumu_1500M4500", col1, nGeneratedEvents, 8.9226E-14);
			addSample("PYTHIA8ZP/Pythia8_ZprimeSSM3000mumu_4500M0",    col2, nGeneratedEvents, 1.18978E-19);
		}
		
		
		if(model==KK && sMass=="1000")
		{
			addSample("PYTHIA8KK/Pythia8_ZKK1000mumu_120M500",  col0, nGeneratedEvents, 6.87332E-09);
			addSample("PYTHIA8KK/Pythia8_ZKK1000mumu_500M1500", col1, nGeneratedEvents, 7.83954E-10);
			addSample("PYTHIA8KK/Pythia8_ZKK1000mumu_1500M0",   col2, nGeneratedEvents, 1.11827E-11);
		}
		if(model==KK && sMass=="2000")
		{
			addSample("PYTHIA8KK/Pythia8_ZKK2000mumu_120M1000",  col0, nGeneratedEvents, 7.68181E-09);
			addSample("PYTHIA8KK/Pythia8_ZKK2000mumu_1000M3000", col1, nGeneratedEvents, 1.22497E-11);
			addSample("PYTHIA8KK/Pythia8_ZKK2000mumu_3000M0",    col2, nGeneratedEvents, 3.44554E-15);
		}
		if(model==KK && sMass=="3000")
		{
			addSample("PYTHIA8KK/Pythia8_ZKK3000mumu_120M1500",  col0, nGeneratedEvents, 7.8351E-09);
			addSample("PYTHIA8KK/Pythia8_ZKK3000mumu_1500M4500", col1, nGeneratedEvents, 2.98849E-13);
			addSample("PYTHIA8KK/Pythia8_ZKK3000mumu_4500M0",    col2, nGeneratedEvents, 7.56956E-20);
		}
			
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		
		
		
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");	
			if(model==Z0d3pd)
			{
				tree = (TTree*)file->Get("truth/truth_tree");
				tree->SetBranchAddress( "truth_all_mc_pt", &truth_all_mc_pt );
				tree->SetBranchAddress( "truth_all_mc_m", &truth_all_mc_m );
				tree->SetBranchAddress( "truth_all_mc_eta", &truth_all_mc_eta );
				tree->SetBranchAddress( "truth_all_mc_phi", &truth_all_mc_phi );
				tree->SetBranchAddress( "truth_all_mc_status", &truth_all_mc_status );
				tree->SetBranchAddress( "truth_all_mc_barcode", &truth_all_mc_barcode );
				tree->SetBranchAddress( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
				tree->SetBranchAddress( "truth_all_mc_charge", &truth_all_mc_charge );
				tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
				tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
				tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
				tree->SetBranchAddress("truth_all_ySystem",&truth_all_ySystem);
				tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
				tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
				
				int valids = 0;

				for(Int_t i=0 ; i<tree->GetEntries() ; i++)
				{
					tree->GetEntry(i);
					
					if(truth_all_isValid)
					{
						valids++;
						imuon_tru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
						iamuon_tru = (imuon_tru==0) ? 1 : 0;
						tlva_tru->SetPtEtaPhiM(truth_all_mc_pt->at(imuon_tru),truth_all_mc_eta->at(imuon_tru),truth_all_mc_phi->at(imuon_tru),muonMass);
						tlvb_tru->SetPtEtaPhiM(truth_all_mc_pt->at(iamuon_tru),truth_all_mc_eta->at(iamuon_tru),truth_all_mc_phi->at(iamuon_tru),muonMass);
						ca_tru = truth_all_mc_charge->at(imuon_tru);
						cb_tru = truth_all_mc_charge->at(iamuon_tru);
						if(ca_tru*cb_tru>=0.)       {_WARNING("Truth: ca_tru*cb_tru>=0., skipping event"); continue;};
						M_tru        = imass(tlva_tru,tlvb_tru);
						if(M_tru<=minPossibleImass || M_tru>maxPossibleImass) {_WARNING("Truth: M_tru<=minPossibleImass || M_tru>maxPossibleImass  ->  M_tru="+_s(M_tru)+", skipping event"); continue;}
						COSTHETA_tru = cosThetaCollinsSoper(tlva_tru,ca_tru,tlvb_tru,cb_tru);
						if(fabs(COSTHETA_tru)>1.)   _WARNING("Truth: |cos(theta)|>1.");
						YQ_tru       = ySystem(tlva_tru,tlvb_tru);
						if(fabs(YQ_tru)>6.)         _WARNING("Truth: |yQ|>6.");
						Ystar_tru = yStar(tlva_tru,tlvb_tru);
						
						

						hvBinnedHistos_imass[n]->Fill(M_tru);
						hvBinnedHistos_imass_unscaled[n]->Fill(M_tru);
						int bin = hDummy_afb->FindBin(M_tru);
						if(bin<=0 || bin>imass_afb_nbins) continue;
						hvvBinnedHistos_cosTh[n][bin-1]->Fill(COSTHETA_tru);
						hvvBinnedHistos_cosTh_unscaled[n][bin-1]->Fill(COSTHETA_tru);
						hvvBinnedHistos_yQ[n][bin-1]->Fill(YQ_tru);
						hvvBinnedHistos_yQ_unscaled[n][bin-1]->Fill(YQ_tru);
						hvvBinnedHistos_eta[n][bin-1]->Fill(truth_all_mc_eta->at(imuon_tru));
						hvvBinnedHistos_eta_unscaled[n][bin-1]->Fill(truth_all_mc_eta->at(imuon_tru));
						hvvBinnedHistos_yStar[n][bin-1]->Fill(Ystar_tru);
						hvvBinnedHistos_yStar_unscaled[n][bin-1]->Fill(Ystar_tru);
					}
				}
				cout << "n=" << n << ", valids=" << valids << endl;
			}
			else
			{
				tree = (TTree*)file->Get("tree");
				tree->SetBranchAddress("mHat",&mHat);
				tree->SetBranchAddress("QT",&qT);
				tree->SetBranchAddress("ySystem",&ysystem);
				tree->SetBranchAddress("cosThetaHE",&cosThetaHE);
				tree->SetBranchAddress("cosThetaCS",&cosThetaCS);
				tree->SetBranchAddress("id",&id);
				tree->SetBranchAddress("charge",&charge);
				tree->SetBranchAddress("px",&px);
				tree->SetBranchAddress("py",&py);
				tree->SetBranchAddress("pz",&pz);
				tree->SetBranchAddress("E",&E);
				tree->SetBranchAddress("m",&m);
				tree->SetBranchAddress("y",&y);
				tree->SetBranchAddress("pT",&pT);
				tree->SetBranchAddress("eta",&eta);
				tree->SetBranchAddress("phi",&phi);
				tree->SetBranchAddress("theta",&theta);

				for(Int_t i=0 ; i<tree->GetEntries() ; i++)
				{
					tree->GetEntry(i);
					
					imuon_tru  = (charge->at(0)<0.) ? 0 : 1;
					iamuon_tru = (imuon_tru==0) ? 1 : 0;
					tlva_tru->SetPtEtaPhiM(pT->at(imuon_tru),eta->at(imuon_tru),phi->at(imuon_tru),muonMass);
					tlvb_tru->SetPtEtaPhiM(pT->at(iamuon_tru),eta->at(iamuon_tru),phi->at(iamuon_tru),muonMass);
					ca_tru = charge->at(imuon_tru);
					cb_tru = charge->at(iamuon_tru);
					if(ca_tru*cb_tru>=0.)
					{
						_WARNING("Truth: ca_tru*cb_tru>=0., skipping event");
						_WARNING("ca="+_s(charge->at(imuon_tru))+", cb="+_s(charge->at(iamuon_tru)));
						continue;
					}
					M_tru        = imass(tlva_tru,tlvb_tru);
					if(M_tru<=minPossibleImass || M_tru>maxPossibleImass)
					{
						_WARNING("Truth: M_tru<=minPossibleImass || M_tru>maxPossibleImass  ->  M_tru="+_s(M_tru)+", skipping event");
						_WARNING("\t pT="+_s(pT->at(imuon_tru))+",  m="+_s(muonMass));
						continue;
					}
					COSTHETA_tru = cosThetaCollinsSoper(tlva_tru,ca_tru,tlvb_tru,cb_tru);
					if(fabs(COSTHETA_tru)>1.)   _WARNING("Truth: |cos(theta)|>1.");
					YQ_tru       = ySystem(tlva_tru,tlvb_tru);
					if(fabs(YQ_tru)>6.)         _WARNING("Truth: |yQ|>6.");
					Ystar_tru = yStar(tlva_tru,tlvb_tru);
					
					hvBinnedHistos_imass[n]->Fill(M_tru);
					int bin = hDummy_afb->FindBin(M_tru);
					if(bin<=0 || bin>imass_afb_nbins) continue;
					hvvBinnedHistos_cosTh[n][bin-1]->Fill(COSTHETA_tru); 
					hvvBinnedHistos_yQ[n][bin-1]->Fill(YQ_tru); 
					hvvBinnedHistos_eta[n][bin-1]->Fill(eta->at(imuon_tru)); 
					hvvBinnedHistos_yStar[n][bin-1]->Fill(Ystar_tru); 
				}
			}
			
			/////////////////////////////////////////////////////////////
			// scale ////////////////////////////////////////////////////
			hvBinnedHistos_imass[n]->Scale(dvWeights[n]);
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				hvvBinnedHistos_cosTh[n][i]->Scale(dvWeights[n]);
				hvvBinnedHistos_yQ[n][i]->Scale(dvWeights[n]);
				hvvBinnedHistos_eta[n][i]->Scale(dvWeights[n]);
				hvvBinnedHistos_yStar[n][i]->Scale(dvWeights[n]);
			}
			/////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////
			// sum /////////////////////////////////////////////////
			hMassSumTmp->Add(hvBinnedHistos_imass[n]);
			if(model==Z0d3pd) hMassSumTmp_unscaled->Add(hvBinnedHistos_imass_unscaled[n]);
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				vhCosThSumTmp[i]->Add(hvvBinnedHistos_cosTh[n][i]);
				vhyQSumTmp[i]->Add(hvvBinnedHistos_yQ[n][i]);
				vhEtaSumTmp[i]->Add(hvvBinnedHistos_eta[n][i]);
				vhyStarSumTmp[i]->Add(hvvBinnedHistos_yStar[n][i]);
				
				if(model==Z0d3pd)
				{
					vhCosThSumTmp_unscaled[i]->Add(hvvBinnedHistos_cosTh_unscaled[n][i]);
					vhyQSumTmp_unscaled[i]->Add(hvvBinnedHistos_yQ_unscaled[n][i]);
					vhEtaSumTmp_unscaled[i]->Add(hvvBinnedHistos_eta_unscaled[n][i]);
					vhyStarSumTmp_unscaled[i]->Add(hvvBinnedHistos_yStar_unscaled[n][i]);
				}
			}
			////////////////////////////////////////////////////////
			
			file->Close();
		}
		
		/////////////////////////////////////////////////////////////
		// clone ////////////////////////////////////////////////////
		if(model==Z0d3pd)
		{
			hMassSumZ0d3pd = (TH1D*)hMassSumTmp->Clone("");
			hMassSumZ0d3pd_unscaled = (TH1D*)hMassSumTmp_unscaled->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				vhCosThSumZ0d3pd[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
				vhCosThSumZ0d3pd_unscaled[i] = (TH1D*)vhCosThSumTmp_unscaled[i]->Clone("");
				
				vhyQSumZ0d3pd[i] = (TH1D*)vhyQSumTmp[i]->Clone("");
				vhyQSumZ0d3pd_unscaled[i] = (TH1D*)vhyQSumTmp_unscaled[i]->Clone("");
				
				vhEtaSumZ0d3pd[i] = (TH1D*)vhEtaSumTmp[i]->Clone("");
				vhEtaSumZ0d3pd_unscaled[i] = (TH1D*)vhEtaSumTmp_unscaled[i]->Clone("");
				
				vhyStarSumZ0d3pd[i] = (TH1D*)vhyStarSumTmp[i]->Clone("");
				vhyStarSumZ0d3pd_unscaled[i] = (TH1D*)vhyStarSumTmp_unscaled[i]->Clone("");
			}
		}
		else
		{
			vhMassSum[model] = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				vvhCosThSum[i][model] = (TH1D*)vhCosThSumTmp[i]->Clone("");
				vvhyQSum[i][model] = (TH1D*)vhyQSumTmp[i]->Clone("");
				vvhEtaSum[i][model] = (TH1D*)vhEtaSumTmp[i]->Clone("");
				vvhyStarSum[i][model] = (TH1D*)vhyStarSumTmp[i]->Clone("");
			}
		}
	}
	

	////////////////////////////////////////////////////////////////
	// The ratios //////////////////////////////////////////////////
	hWeightsXS = (TH1D*)hMassSumZ0d3pd->Clone("");
	//hWeightsXS->Divide(hMassSumZ0d3pd_unscaled);
	divide(hWeightsXS,hMassSumZ0d3pd_unscaled);
	dirMassHistograms->cd();
	hWeightsXS->SetName("hMassXS_wgt");
	hWeightsXS->Write("", TObject::kOverwrite);
	for(int mod=Z0 ; mod<=KK ; mod++) 
	{
		if(mod==Z0) tsname = "Z0";
		if(mod==ZP) tsname = "ZP";
		if(mod==KK) tsname = "KK";
	
		vhMassWeights[mod] = (TH1D*)vhMassSum[mod]->Clone(""); 
		//vhMassWeights[mod]->Divide(hMassSumZ0d3pd);
		divide(vhMassWeights[mod],hMassSumZ0d3pd);
		dirMassHistograms->cd();
		vhMassWeights[mod]->SetName("hMass"+tsname+"_wgt");
		vhMassWeights[mod]->Write("", TObject::kOverwrite);
	}
	
	dirCostHistograms->cd();
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		TString b = (TString)tostring(i+1);
	
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			vvhCosThSumWeights[i][mod] = (TH1D*)vvhCosThSum[i][mod]->Clone(""); 
			//vvhCosThSumWeights[i][mod]->Divide(vhCosThSumZ0d3pd[i]);
			divide(vvhCosThSumWeights[i][mod],vhCosThSumZ0d3pd[i]);
			
			dirCostHistograms->cd();
			vvhCosThSumWeights[i][mod]->SetTitle((TString)"cost weights: " + (TString)vvhCosThSumWeights[i][mod]->GetTitle());
			vvhCosThSumWeights[i][mod]->SetName( "hCosTh"+tsname+"_wgt_"+b );
			vvhCosThSumWeights[i][mod]->Write("", TObject::kOverwrite);
		}
		
		vhCosThSumXSweights[i] = (TH1D*)vhCosThSumZ0d3pd[i]->Clone(""); 
		//vhCosThSumXSweights[i]->Divide(vhCosThSumZ0d3pd_unscaled[i]); 
		divide(vhCosThSumXSweights[i],vhCosThSumZ0d3pd_unscaled[i]); 
		
		dirCostHistograms->cd();
		vhCosThSumXSweights[i]->SetTitle((TString)"cost weights_XS: " + (TString)vhCosThSumXSweights[i]->GetTitle());
		vhCosThSumXSweights[i]->SetName( "hCosThXS_wgt_"+b );
		vhCosThSumXSweights[i]->Write("", TObject::kOverwrite);
	}
	
	diryQHistograms->cd();
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		TString b = (TString)tostring(i+1);
	
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			vvhyQSumWeights[i][mod] = (TH1D*)vvhyQSum[i][mod]->Clone(""); 
			//vvhyQSumWeights[i][mod]->Divide(vhyQSumZ0d3pd[i]);
			divide(vvhyQSumWeights[i][mod],vhyQSumZ0d3pd[i]);
			
			diryQHistograms->cd();
			vvhyQSumWeights[i][mod]->SetTitle((TString)"yQ weights: " + (TString)vvhyQSumWeights[i][mod]->GetTitle());
			vvhyQSumWeights[i][mod]->SetName( "hyQ"+tsname+"_wgt_"+b );
			vvhyQSumWeights[i][mod]->Write("", TObject::kOverwrite);
		}
		
		vhyQSumXSweights[i] = (TH1D*)vhyQSumZ0d3pd[i]->Clone(""); 
		//vhyQSumXSweights[i]->Divide(vhyQSumZ0d3pd_unscaled[i]); 
		divide(vhyQSumXSweights[i],vhyQSumZ0d3pd_unscaled[i]); 
		
		diryQHistograms->cd();
		vhyQSumXSweights[i]->SetTitle((TString)"yQ weights_XS: " + (TString)vhyQSumXSweights[i]->GetTitle());
		vhyQSumXSweights[i]->SetName( "hyQXS_wgt_"+b );
		vhyQSumXSweights[i]->Write("", TObject::kOverwrite);
	}
	////////////////////////////////////////////////////////////////

	
	dirEtaHistograms->cd();
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		TString b = (TString)tostring(i+1);
	
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			vvhEtaSumWeights[i][mod] = (TH1D*)vvhEtaSum[i][mod]->Clone(""); 
			//vvhEtaSumWeights[i][mod]->Divide(vhEtaSumZ0d3pd[i]);
			divide(vvhEtaSumWeights[i][mod],vhEtaSumZ0d3pd[i]);
			
			dirEtaHistograms->cd();
			vvhEtaSumWeights[i][mod]->SetTitle((TString)"etamu weights: " + (TString)vvhEtaSumWeights[i][mod]->GetTitle());
			vvhEtaSumWeights[i][mod]->SetName( "hEtamu"+tsname+"_wgt_"+b );
			vvhEtaSumWeights[i][mod]->Write("", TObject::kOverwrite);
		}
		
		vhEtaSumXSweights[i] = (TH1D*)vhEtaSumZ0d3pd[i]->Clone(""); 
		//vhEtaSumXSweights[i]->Divide(vhEtaSumZ0d3pd_unscaled[i]); 
		divide(vhEtaSumXSweights[i],vhEtaSumZ0d3pd_unscaled[i]); 
		
		dirEtaHistograms->cd();
		vhEtaSumXSweights[i]->SetTitle((TString)"etamu weights_XS: " + (TString)vhEtaSumXSweights[i]->GetTitle());
		vhEtaSumXSweights[i]->SetName( "hEtamuXS_wgt_"+b );
		vhEtaSumXSweights[i]->Write("", TObject::kOverwrite);
	}
	////////////////////////////////////////////////////////////////
	
	
	diryStarHistograms->cd();
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		TString b = (TString)tostring(i+1);
	
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			vvhyStarSumWeights[i][mod] = (TH1D*)vvhyStarSum[i][mod]->Clone(""); 
			//vvhyStarSumWeights[i][mod]->Divide(vhyStarSumZ0d3pd[i]);
			divide(vvhyStarSumWeights[i][mod],vhyStarSumZ0d3pd[i]);
			
			diryStarHistograms->cd();
			vvhyStarSumWeights[i][mod]->SetTitle((TString)"yStar weights: " + (TString)vvhyStarSumWeights[i][mod]->GetTitle());
			vvhyStarSumWeights[i][mod]->SetName( "hyStar"+tsname+"_wgt_"+b );
			vvhyStarSumWeights[i][mod]->Write("", TObject::kOverwrite);
		}
		
		vhyStarSumXSweights[i] = (TH1D*)vhyStarSumZ0d3pd[i]->Clone(""); 
		//vhyStarSumXSweights[i]->Divide(vhyStarSumZ0d3pd_unscaled[i]); 
		divide(vhyStarSumXSweights[i],vhyStarSumZ0d3pd_unscaled[i]); 
		
		diryStarHistograms->cd();
		vhyStarSumXSweights[i]->SetTitle((TString)"yStar weights_XS: " + (TString)vhyStarSumXSweights[i]->GetTitle());
		vhyStarSumXSweights[i]->SetName( "hyStarXS_wgt_"+b );
		vhyStarSumXSweights[i]->Write("", TObject::kOverwrite);
	}
	////////////////////////////////////////////////////////////////

	
	
	
	// draw cost
	dirCostHistograms->cd();
	vector<TCanvas*> vC;
	vector<TVirtualPad*> vP1;
	vector<TVirtualPad*> vP2;
	vector<TLegend*> vL1;
	vector<TLegend*> vL2;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		
		TString b = (TString)tostring(i+1);
		
		vC.push_back( new TCanvas("cost_c"+b,"cost_c"+b,0,0,1200,800) );
		vC[i]->Divide(1,2);
		vC[i]->Draw();
		
		vP1.push_back( vC[i]->cd(1) );
		vP1[i]->SetLogy();
		
		vP2.push_back( vC[i]->cd(2) );
		vP2[i]->SetLogy();
		
		vL1.push_back( new TLegend(0.6928196,0.1761658,0.8771074,0.3353843,NULL,"brNDC") );
		vL1[i]->SetFillColor(kWhite);
		
		vL2.push_back( new TLegend(0.7554766,0.8272493,0.877596,0.947087,NULL,"brNDC") );
		vL2[i]->SetFillColor(kWhite);
		
		
		vP1[i]->cd();
		vP1[i]->Draw();
		
		float min = 1.e-2;
		float max = vhCosThSumZ0d3pd[i]->GetMaximum();
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhCosThSum[i][mod]->GetMaximum() > max) ? vvhCosThSum[i][mod]->GetMaximum() : max;
	
		vhCosThSumZ0d3pd[i]->SetMinimum(1.e-2);
		vhCosThSumZ0d3pd[i]->SetMaximum(5.*max);
		vhCosThSumZ0d3pd[i]->SetLineColor(col0);
		vhCosThSumZ0d3pd[i]->SetLineStyle(1);
		vhCosThSumZ0d3pd[i]->SetLineWidth(2);
		vhCosThSumZ0d3pd[i]->SetXTitle("cos#theta*");
		vhCosThSumZ0d3pd[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhCosThSumZ0d3pd[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumZ0d3pd[i]->Draw();
		vL1[i]->AddEntry(vhCosThSumZ0d3pd[i], "SM #gamma/Z^{0} (#it{ATLAS} MC10 tru)", "l");
		
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0} (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
		
			vvhCosThSum[i][mod]->SetMinimum(min);
			vvhCosThSum[i][mod]->SetMaximum(5.*max);
			vvhCosThSum[i][mod]->SetLineColor(col);
			vvhCosThSum[i][mod]->SetLineStyle(1);
			vvhCosThSum[i][mod]->SetLineWidth(2);
			vvhCosThSum[i][mod]->SetXTitle("cos#theta*");
			vvhCosThSum[i][mod]->SetYTitle("Events");
			//if(5.*max<1.e2) vvhCosThSum[i][mod]->GetYaxis()->SetMoreLogLabels();
			vvhCosThSum[i][mod]->Draw("SAMES");
			vL1[i]->AddEntry(vvhCosThSum[i][mod], sName.c_str(), "l");
		}
		vL1[i]->Draw("SAMES");
		
		vP1[i]->cd();
		vP1[i]->RedrawAxis();
		vP1[i]->Update();
		
		//--------------------------------------------
		
		vP2[i]->cd();
		vP2[i]->Draw();
		
		min = 1.e-1;
		max = -1.;
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhCosThSumWeights[i][mod]->GetMaximum() > max) ? vvhCosThSumWeights[i][mod]->GetMaximum() : max;
		string sYTitle = "Events_{#scale[1.1]{P}#scale[0.9]{YTHIA8}}/Events_{#gamma/Z^{0}}";
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			TString drawOpt = "";
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0}";
				drawOpt = "";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV Z' SSM";
				drawOpt = "SAMES";
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName   = sMass + " GeV S^{1}/Z_{2} KK";
				drawOpt = "SAMES";
			}
			vvhCosThSumWeights[i][mod]->SetMinimum(min);
			vvhCosThSumWeights[i][mod]->SetMaximum(5.*max);
			vvhCosThSumWeights[i][mod]->SetLineColor(col2);
			vvhCosThSumWeights[i][mod]->SetLineStyle(1);
			vvhCosThSumWeights[i][mod]->SetLineWidth(2);
			vvhCosThSumWeights[i][mod]->SetXTitle("cos#theta*");
			vvhCosThSumWeights[i][mod]->SetYTitle(sYTitle.c_str());
			//if(5.*max<1.e2) vvhCosThSumWeights[i][mod]->GetYaxis()->SetMoreLogLabels(); 
			vvhCosThSumWeights[i][mod]->Draw(drawOpt);
			vL2[i]->AddEntry(vvhCosThSumWeights[i][mod], sName.c_str(), "l");
		}
		vL2[i]->Draw("SAMES");
		
		vP2[i]->cd();
		vP2[i]->RedrawAxis();
		vP2[i]->Update();
		vC[i]->Update();
		
		tsname = "plots/plot_cosTheta_" + b;
		vC[i]->SaveAs(tsname+".eps");
		vC[i]->SaveAs(tsname+".C");
		vC[i]->SaveAs(tsname+".root");
		vC[i]->SaveAs(tsname+".png");
	}
	cout << "CosTheta weights are calculated and written\n" << endl;
	//-------------------------------------------------------------------------------------
	
	
	// draw yQ
	diryQHistograms->cd();
	vector<TCanvas*> vCyQ;
	vector<TVirtualPad*> vP1yQ;
	vector<TVirtualPad*> vP2yQ;
	vector<TLegend*> vL1yQ;
	vector<TLegend*> vL2yQ;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		
		TString b = (TString)tostring(i+1);
		
		vCyQ.push_back( new TCanvas("yQ_c"+b,"yQ_c"+b,0,0,1200,800) );
		vCyQ[i]->Divide(1,2);
		vCyQ[i]->Draw();
		
		vP1yQ.push_back( vCyQ[i]->cd(1) );
		vP1yQ[i]->SetLogy();
		
		vP2yQ.push_back( vCyQ[i]->cd(2) );
		vP2yQ[i]->SetLogy();
		
		vL1yQ.push_back( new TLegend(0.6928196,0.1761658,0.8771074,0.3353843,NULL,"brNDC") );
		vL1yQ[i]->SetFillColor(kWhite);
		
		vL2yQ.push_back( new TLegend(0.7554766,0.8272493,0.877596,0.947087,NULL,"brNDC") );
		vL2yQ[i]->SetFillColor(kWhite);
		
		
		vP1yQ[i]->cd();
		vP1yQ[i]->Draw();
		
		float min = 1.e-2;
		float max = vhyQSumZ0d3pd[i]->GetMaximum();
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhyQSum[i][mod]->GetMaximum() > max) ? vvhyQSum[i][mod]->GetMaximum() : max;
	
		vhyQSumZ0d3pd[i]->SetMinimum(1.e-2);
		vhyQSumZ0d3pd[i]->SetMaximum(5.*max);
		vhyQSumZ0d3pd[i]->SetLineColor(col0);
		vhyQSumZ0d3pd[i]->SetLineStyle(1);
		vhyQSumZ0d3pd[i]->SetLineWidth(2);
		vhyQSumZ0d3pd[i]->SetXTitle("y_{Q}");
		vhyQSumZ0d3pd[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhyQSumZ0d3pd[i]->GetYaxis()->SetMoreLogLabels();
		vhyQSumZ0d3pd[i]->Draw();
		vL1yQ[i]->AddEntry(vhyQSumZ0d3pd[i], "SM #gamma/Z^{0} (#it{ATLAS} MC10 tru)", "l");
		
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0} (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
		
			vvhyQSum[i][mod]->SetMinimum(min);
			vvhyQSum[i][mod]->SetMaximum(5.*max);
			vvhyQSum[i][mod]->SetLineColor(col);
			vvhyQSum[i][mod]->SetLineStyle(1);
			vvhyQSum[i][mod]->SetLineWidth(2);
			vvhyQSum[i][mod]->SetXTitle("y_{Q}");
			vvhyQSum[i][mod]->SetYTitle("Events");
			//if(5.*max<1.e2) vvhyQSum[i][mod]->GetYaxis()->SetMoreLogLabels();
			vvhyQSum[i][mod]->Draw("SAMES");
			vL1yQ[i]->AddEntry(vvhyQSum[i][mod], sName.c_str(), "l");
		}
		vL1yQ[i]->Draw("SAMES");
		
		vP1yQ[i]->cd();
		vP1yQ[i]->RedrawAxis();
		vP1yQ[i]->Update();
		
		//--------------------------------------------
		
		vP2yQ[i]->cd();
		vP2yQ[i]->Draw();
		
		min = 1.e-1;
		max = -1.;
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhyQSumWeights[i][mod]->GetMaximum() > max) ? vvhyQSumWeights[i][mod]->GetMaximum() : max;
		string sYTitle = "Events_{#scale[1.1]{P}#scale[0.9]{YTHIA8}}/Events_{#gamma/Z^{0}}";
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			TString drawOpt = "";
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0}";
				drawOpt = "";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV Z' SSM";
				drawOpt = "SAMES";
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName   = sMass + " GeV S^{1}/Z_{2} KK";
				drawOpt = "SAMES";
			}
			vvhyQSumWeights[i][mod]->SetMinimum(min);
			vvhyQSumWeights[i][mod]->SetMaximum(5.*max);
			vvhyQSumWeights[i][mod]->SetLineColor(col2);
			vvhyQSumWeights[i][mod]->SetLineStyle(1);
			vvhyQSumWeights[i][mod]->SetLineWidth(2);
			vvhyQSumWeights[i][mod]->SetXTitle("y_{Q}");
			vvhyQSumWeights[i][mod]->SetYTitle(sYTitle.c_str());
			//if(5.*max<1.e2) vvhyQSumWeights[i][mod]->GetYaxis()->SetMoreLogLabels(); 
			vvhyQSumWeights[i][mod]->Draw(drawOpt);
			vL2yQ[i]->AddEntry(vvhyQSumWeights[i][mod], sName.c_str(), "l");
		}
		vL2yQ[i]->Draw("SAMES");
		
		vP2yQ[i]->cd();
		vP2yQ[i]->RedrawAxis();
		vP2yQ[i]->Update();
		vCyQ[i]->Update();
		
		tsname = "plots/plot_yQ_" + b;
		vCyQ[i]->SaveAs(tsname+".eps");
		vCyQ[i]->SaveAs(tsname+".C");
		vCyQ[i]->SaveAs(tsname+".root");
		vCyQ[i]->SaveAs(tsname+".png");
	}
	cout << "yQ weights are calculated and written\n" << endl;
	//---------------------------------------------------------------------------
	
	
	
	// draw etamu
	dirEtaHistograms->cd();
	vector<TCanvas*> vCetamu;
	vector<TVirtualPad*> vP1etamu;
	vector<TVirtualPad*> vP2etamu;
	vector<TLegend*> vL1etamu;
	vector<TLegend*> vL2etamu;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		
		TString b = (TString)tostring(i+1);
		
		vCetamu.push_back( new TCanvas("etamu_c"+b,"etamu_c"+b,0,0,1200,800) );
		vCetamu[i]->Divide(1,2);
		vCetamu[i]->Draw();
		
		vP1etamu.push_back( vCetamu[i]->cd(1) );
		vP1etamu[i]->SetLogy();
		
		vP2etamu.push_back( vCetamu[i]->cd(2) );
		vP2etamu[i]->SetLogy();
		
		vL1etamu.push_back( new TLegend(0.6928196,0.1761658,0.8771074,0.3353843,NULL,"brNDC") );
		vL1etamu[i]->SetFillColor(kWhite);
		
		vL2etamu.push_back( new TLegend(0.7554766,0.8272493,0.877596,0.947087,NULL,"brNDC") );
		vL2etamu[i]->SetFillColor(kWhite);
		
		
		vP1etamu[i]->cd();
		vP1etamu[i]->Draw();
		
		float min = 1.e-2;
		float max = vhEtaSumZ0d3pd[i]->GetMaximum();
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhEtaSum[i][mod]->GetMaximum() > max) ? vvhEtaSum[i][mod]->GetMaximum() : max;
	
		vhEtaSumZ0d3pd[i]->SetMinimum(1.e-2);
		vhEtaSumZ0d3pd[i]->SetMaximum(5.*max);
		vhEtaSumZ0d3pd[i]->SetLineColor(col0);
		vhEtaSumZ0d3pd[i]->SetLineStyle(1);
		vhEtaSumZ0d3pd[i]->SetLineWidth(2);
		vhEtaSumZ0d3pd[i]->SetXTitle("#eta_{#mu^{-}}");
		vhEtaSumZ0d3pd[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhEtaSumZ0d3pd[i]->GetYaxis()->SetMoreLogLabels();
		vhEtaSumZ0d3pd[i]->Draw();
		vL1yQ[i]->AddEntry(vhEtaSumZ0d3pd[i], "SM #gamma/Z^{0} (#it{ATLAS} MC10 tru)", "l");
		
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0} (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
		
			vvhEtaSum[i][mod]->SetMinimum(min);
			vvhEtaSum[i][mod]->SetMaximum(5.*max);
			vvhEtaSum[i][mod]->SetLineColor(col);
			vvhEtaSum[i][mod]->SetLineStyle(1);
			vvhEtaSum[i][mod]->SetLineWidth(2);
			vvhEtaSum[i][mod]->SetXTitle("#eta_{#mu^{-}}");
			vvhEtaSum[i][mod]->SetYTitle("Events");
			//if(5.*max<1.e2) vvhEtaSum[i][mod]->GetYaxis()->SetMoreLogLabels();
			vvhEtaSum[i][mod]->Draw("SAMES");
			vL1etamu[i]->AddEntry(vvhEtaSum[i][mod], sName.c_str(), "l");
		}
		vL1etamu[i]->Draw("SAMES");
		
		vP1etamu[i]->cd();
		vP1etamu[i]->RedrawAxis();
		vP1etamu[i]->Update();
		
		//--------------------------------------------
		
		vP2etamu[i]->cd();
		vP2etamu[i]->Draw();
		
		min = 1.e-1;
		max = -1.;
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhEtaSumWeights[i][mod]->GetMaximum() > max) ? vvhEtaSumWeights[i][mod]->GetMaximum() : max;
		string sYTitle = "Events_{#scale[1.1]{P}#scale[0.9]{YTHIA8}}/Events_{#gamma/Z^{0}}";
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			TString drawOpt = "";
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0}";
				drawOpt = "";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV Z' SSM";
				drawOpt = "SAMES";
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName   = sMass + " GeV S^{1}/Z_{2} KK";
				drawOpt = "SAMES";
			}
			vvhEtaSumWeights[i][mod]->SetMinimum(min);
			vvhEtaSumWeights[i][mod]->SetMaximum(5.*max);
			vvhEtaSumWeights[i][mod]->SetLineColor(col2);
			vvhEtaSumWeights[i][mod]->SetLineStyle(1);
			vvhEtaSumWeights[i][mod]->SetLineWidth(2);
			vvhEtaSumWeights[i][mod]->SetXTitle("#eta_{#mu^{-}}");
			vvhEtaSumWeights[i][mod]->SetYTitle(sYTitle.c_str());
			//if(5.*max<1.e2) vvhEtaSumWeights[i][mod]->GetYaxis()->SetMoreLogLabels(); 
			vvhEtaSumWeights[i][mod]->Draw(drawOpt);
			vL2etamu[i]->AddEntry(vvhEtaSumWeights[i][mod], sName.c_str(), "l");
		}
		vL2etamu[i]->Draw("SAMES");
		
		vP2etamu[i]->cd();
		vP2etamu[i]->RedrawAxis();
		vP2etamu[i]->Update();
		vCetamu[i]->Update();
		
		tsname = "plots/plot_etamu_" + b;
		vCetamu[i]->SaveAs(tsname+".eps");
		vCetamu[i]->SaveAs(tsname+".C");
		vCetamu[i]->SaveAs(tsname+".root");
		vCetamu[i]->SaveAs(tsname+".png");
	}
	cout << "eta weights are calculated and written\n" << endl;
	//---------------------------------------------------------------------------
	
	
	// draw yStar
	diryStarHistograms->cd();
	vector<TCanvas*> vCyStar;
	vector<TVirtualPad*> vP1yStar;
	vector<TVirtualPad*> vP2yStar;
	vector<TLegend*> vL1yStar;
	vector<TLegend*> vL2yStar;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		
		TString b = (TString)tostring(i+1);
		
		vCyStar.push_back( new TCanvas("yStar_c"+b,"yStar_c"+b,0,0,1200,800) );
		vCyStar[i]->Divide(1,2);
		vCyStar[i]->Draw();
		
		vP1yStar.push_back( vCyStar[i]->cd(1) );
		vP1yStar[i]->SetLogy();
		
		vP2yStar.push_back( vCyStar[i]->cd(2) );
		vP2yStar[i]->SetLogy();
		
		vL1yStar.push_back( new TLegend(0.6928196,0.1761658,0.8771074,0.3353843,NULL,"brNDC") );
		vL1yStar[i]->SetFillColor(kWhite);
		
		vL2yStar.push_back( new TLegend(0.7554766,0.8272493,0.877596,0.947087,NULL,"brNDC") );
		vL2yStar[i]->SetFillColor(kWhite);
		
		
		vP1yStar[i]->cd();
		vP1yStar[i]->Draw();
		
		float min = 1.e-2;
		float max = vhyStarSumZ0d3pd[i]->GetMaximum();
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhyStarSum[i][mod]->GetMaximum() > max) ? vvhyStarSum[i][mod]->GetMaximum() : max;
	
		vhyStarSumZ0d3pd[i]->SetMinimum(1.e-2);
		vhyStarSumZ0d3pd[i]->SetMaximum(5.*max);
		vhyStarSumZ0d3pd[i]->SetLineColor(col0);
		vhyStarSumZ0d3pd[i]->SetLineStyle(1);
		vhyStarSumZ0d3pd[i]->SetLineWidth(2);
		vhyStarSumZ0d3pd[i]->SetXTitle("y*");
		vhyStarSumZ0d3pd[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhyStarSumZ0d3pd[i]->GetYaxis()->SetMoreLogLabels();
		vhyStarSumZ0d3pd[i]->Draw();
		vL1yQ[i]->AddEntry(vhyStarSumZ0d3pd[i], "SM #gamma/Z^{0} (#it{ATLAS} MC10 tru)", "l");
		
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0} (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
			}
		
			vvhyStarSum[i][mod]->SetMinimum(min);
			vvhyStarSum[i][mod]->SetMaximum(5.*max);
			vvhyStarSum[i][mod]->SetLineColor(col);
			vvhyStarSum[i][mod]->SetLineStyle(1);
			vvhyStarSum[i][mod]->SetLineWidth(2);
			vvhyStarSum[i][mod]->SetXTitle("y*");
			vvhyStarSum[i][mod]->SetYTitle("Events");
			//if(5.*max<1.e2) vvhyStarSum[i][mod]->GetYaxis()->SetMoreLogLabels();
			vvhyStarSum[i][mod]->Draw("SAMES");
			vL1yStar[i]->AddEntry(vvhyStarSum[i][mod], sName.c_str(), "l");
		}
		vL1yStar[i]->Draw("SAMES");
		
		vP1yStar[i]->cd();
		vP1yStar[i]->RedrawAxis();
		vP1yStar[i]->Update();
		
		//--------------------------------------------
		
		vP2yStar[i]->cd();
		vP2yStar[i]->Draw();
		
		min = 1.e-1;
		max = -1.;
		for(int mod=Z0 ; mod<=KK ; mod++) max = (vvhyStarSumWeights[i][mod]->GetMaximum() > max) ? vvhyStarSumWeights[i][mod]->GetMaximum() : max;
		string sYTitle = "Events_{#scale[1.1]{P}#scale[0.9]{YTHIA8}}/Events_{#gamma/Z^{0}}";
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			Color_t  col = 0;
			TString drawOpt = "";
			if(mod==Z0)
			{
				col = kBlue;
				sName = "SM #gamma/Z^{0}";
				drawOpt = "";
			}
			if(mod==ZP)
			{
				col = col2;
				sName = sMass + " GeV Z' SSM";
				drawOpt = "SAMES";
			}
			if(mod==KK)
			{
				col = kGreen+3;
				sName   = sMass + " GeV S^{1}/Z_{2} KK";
				drawOpt = "SAMES";
			}
			vvhyStarSumWeights[i][mod]->SetMinimum(min);
			vvhyStarSumWeights[i][mod]->SetMaximum(5.*max);
			vvhyStarSumWeights[i][mod]->SetLineColor(col2);
			vvhyStarSumWeights[i][mod]->SetLineStyle(1);
			vvhyStarSumWeights[i][mod]->SetLineWidth(2);
			vvhyStarSumWeights[i][mod]->SetXTitle("y*");
			vvhyStarSumWeights[i][mod]->SetYTitle(sYTitle.c_str());
			//if(5.*max<1.e2) vvhyStarSumWeights[i][mod]->GetYaxis()->SetMoreLogLabels(); 
			vvhyStarSumWeights[i][mod]->Draw(drawOpt);
			vL2yStar[i]->AddEntry(vvhyStarSumWeights[i][mod], sName.c_str(), "l");
		}
		vL2yStar[i]->Draw("SAMES");
		
		vP2yStar[i]->cd();
		vP2yStar[i]->RedrawAxis();
		vP2yStar[i]->Update();
		vCyStar[i]->Update();
		
		tsname = "plots/plot_yStar_" + b;
		vCyStar[i]->SaveAs(tsname+".eps");
		vCyStar[i]->SaveAs(tsname+".C");
		vCyStar[i]->SaveAs(tsname+".root");
		vCyStar[i]->SaveAs(tsname+".png");
	}
	cout << "yStar weights are calculated and written\n" << endl;
	//---------------------------------------------------------------------------
	
	
	
	
	
	
	// read the rec+tru branches simultaneously
	for(int model=Z0d3pd ; model<=DT ; model++)
	{
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hMassSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
		hResTmp->Reset();
		for(int i=0 ; i<imass_afb_nbins ; i++) vhCosThSumTmp[i]->Reset();
		for(int i=0 ; i<imass_afb_nbins ; i++) vhyQSumTmp[i]->Reset();
		for(int i=0 ; i<imass_afb_nbins ; i++) vhEtaSumTmp[i]->Reset();
		for(int i=0 ; i<imass_afb_nbins ; i++) vhyStarSumTmp[i]->Reset();
		
		////////////////////////////
	
		if(model==Z0d3pd ||  (model>=Z0 && model<=KK))
		{
			addSample("ATLASZ0/mcLocalControl_DYmumu_120M250",   col0, 19999, 0.0086861*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_250M400",   col1, 19996, 0.00041431*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_400M600",   col2, 19993, 0.000067464*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_600M800",   col3, 15994, 0.000011168*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_800M1000",  col5, 19992, 0.0000027277*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1000M1250", col5, 19995, 0.00000091646*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1250M1500", col5, 19993, 0.00000024942*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1500M1750", col5, 19997, 0.000000076876*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_1750M2000", col5, 19993, 0.000000026003*nb2mb);
			addSample("ATLASZ0/mcLocalControl_DYmumu_M2000",     col5, 19996, 0.000000015327*nb2mb);
		}
		
		if(model==DT)
		{
			addSample("DATA/analysisLocalControl", kBlack, luminosity, 1.);
		}
		
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		int afb_bin = 0;
		double bin_xs_weight = 1.;
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");	
			
			if(model!=DT)
			{
				tree = (TTree*)file->Get("truth/truth_tree");
				
				tree->SetBranchAddress( "truth_all_mc_pt", &truth_all_mc_pt );
				tree->SetBranchAddress( "truth_all_mc_m", &truth_all_mc_m );
				tree->SetBranchAddress( "truth_all_mc_eta", &truth_all_mc_eta );
				tree->SetBranchAddress( "truth_all_mc_phi", &truth_all_mc_phi );
				tree->SetBranchAddress( "truth_all_mc_status", &truth_all_mc_status );
				tree->SetBranchAddress( "truth_all_mc_barcode", &truth_all_mc_barcode );
				tree->SetBranchAddress( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
				tree->SetBranchAddress( "truth_all_mc_charge", &truth_all_mc_charge );
				tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
				tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
				tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
				tree->SetBranchAddress("truth_all_ySystem",&truth_all_ySystem);
				tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
				tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
					
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
				tree->SetBranchAddress("recon_all_ySystem",&recon_all_ySystem);
				tree->SetBranchAddress("recon_all_QT", &recon_all_QT);

				bin_xs_weight = dvWeights[n]/luminosity; // in units of fb
			}
			else
			{
				tree = (TTree*)file->Get("allCuts/allCuts_tree");
				
				tree->SetBranchAddress("E", &recon_all_E);
				tree->SetBranchAddress("pt", &recon_all_pt);
				tree->SetBranchAddress("m", &recon_all_m);
				tree->SetBranchAddress("eta", &recon_all_eta);
				tree->SetBranchAddress("phi", &recon_all_phi);
				tree->SetBranchAddress("px", &recon_all_px);
				tree->SetBranchAddress("py", &recon_all_py);
				tree->SetBranchAddress("pz", &recon_all_pz);
				tree->SetBranchAddress("charge", &recon_all_charge);
				//tree->SetBranchAddress("y", &recon_all_y);
				//tree->SetBranchAddress("recon_all_id", &recon_all_id);
				//tree->SetBranchAddress("recon_all_theta", &recon_all_theta);
				tree->SetBranchAddress("Mhat", &recon_all_Mhat);
				tree->SetBranchAddress("CosThetaCS", &recon_all_CosThetaCS);
				tree->SetBranchAddress("CosThetaHE", &recon_all_CosThetaHE);
				tree->SetBranchAddress("Ysystem",&recon_all_ySystem);
				tree->SetBranchAddress("Q_T", &recon_all_QT);
				
				bin_xs_weight = 1.;
			}
			
			for(Int_t i=0 ; i<tree->GetEntries() ; i++)
			{
				tree->GetEntry(i);
				Int_t    bin          = 0;
				Double_t mass_weight  = 0.;
				Double_t cost_weight  = 0.;
				Double_t yQ_weight    = 0.;
				Double_t eta_weight   = 0.;
				Double_t yStar_weight = 0.;
				if(model!=DT)
				{
					if(recon_all_isValid  &&  truth_all_isValid)
					{
						// for all models (practically we read only the Z0 and weight the ZP and KK)
						imuon_tru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
						iamuon_tru = (imuon_tru==0) ? 1 : 0;
						tlva_tru->SetPtEtaPhiM(truth_all_mc_pt->at(imuon_tru),truth_all_mc_eta->at(imuon_tru),truth_all_mc_phi->at(imuon_tru),muonMass);
						tlvb_tru->SetPtEtaPhiM(truth_all_mc_pt->at(iamuon_tru),truth_all_mc_eta->at(iamuon_tru),truth_all_mc_phi->at(iamuon_tru),muonMass);
						ca_tru = truth_all_mc_charge->at(imuon_tru);
						cb_tru = truth_all_mc_charge->at(iamuon_tru);
						if(ca_tru*cb_tru>=0.)       {_WARNING("Truth: ca_tru*cb_tru>=0., skipping event"); continue;};
						M_tru        = imass(tlva_tru,tlvb_tru);
						if(M_tru<=minPossibleImass || M_tru>maxPossibleImass) {_WARNING("Truth: M_tru<=minPossibleImass || M_tru>maxPossibleImass  ->  M_tru="+_s(M_tru)+", skipping event"); continue;}
						COSTHETA_tru = cosThetaCollinsSoper(tlva_tru,ca_tru,tlvb_tru,cb_tru);
						if(fabs(COSTHETA_tru)>1.)   _WARNING("Truth: |cos(theta)|>1.");
						YQ_tru       = ySystem(tlva_tru,tlvb_tru);
						if(fabs(YQ_tru)>6.)         _WARNING("Truth: |yQ|>6.");
						Ystar_tru = yStar(tlva_tru,tlvb_tru);
						
						imuon_rec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
						iamuon_rec = (imuon_rec==0) ? 1 : 0;
						tlva_rec->SetPtEtaPhiM(recon_all_pt->at(imuon_rec),recon_all_eta->at(imuon_rec),recon_all_phi->at(imuon_rec),muonMass);
						tlvb_rec->SetPtEtaPhiM(recon_all_pt->at(iamuon_rec),recon_all_eta->at(iamuon_rec),recon_all_phi->at(iamuon_rec),muonMass);
						ca_rec = recon_all_charge->at(imuon_rec);
						cb_rec = recon_all_charge->at(iamuon_rec);
						if(ca_rec*cb_rec>=0.)       {_WARNING("Reconstructed: ca_rec*cb_rec>=0., skipping event"); continue;};
						M_rec        = imass(tlva_rec,tlvb_rec);
						if(M_rec<=minPossibleImass || M_rec>maxPossibleImass)
						{
							_WARNING("Reconstructed: M_rec<=minPossibleImass || M_rec>maxPossibleImass  ->  M_rec="+_s(M_rec)+", skipping event");
							_WARNING("\t pT="+_s(recon_all_pt->at(imuon_rec))+",  m="+_s(muonMass));
							continue;
						}
						COSTHETA_rec = cosThetaCollinsSoper(tlva_rec,ca_rec,tlvb_rec,cb_rec);
						if(fabs(COSTHETA_rec)>1.)   _WARNING("Reconstructed: |cos(theta)|>1.");
						YQ_rec       = ySystem(tlva_rec,tlvb_rec);
						if(fabs(YQ_rec)>6.)         _WARNING("Reconstructed: |yQ|>6.");
						Ystar_rec = yStar(tlva_rec,tlvb_rec);
						
						
						// afb_bin = hDummy_afb->FindBin(truth_all_Mhat);
						afb_bin = hDummy_afb->FindBin(M_tru); // ?????????????????????????????? MAYBE need to be M_tru ?????????????????????????????????????????????????????????????????????????????????????????????????
						if(afb_bin<=0 || afb_bin>imass_afb_nbins) continue;
						
						// fill from d3pd
						if(model==Z0d3pd)
						{
							//------------ imass
							// hvBinnedHistos_imass[n]->Fill(recon_all_Mhat);
							// hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat); // use all events
							
							hvBinnedHistos_imass[n]->Fill(M_rec);
							hvBinnedHistos_imassRes[n]->Fill((M_rec-M_tru)/M_tru); // use all events
							
							//------------ cosTheta
							// hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(recon_all_CosThetaCS);
							hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(COSTHETA_rec);
							
							//------------ yQ
							// hvvBinnedHistos_yQ[n][afb_bin-1]->Fill(recon_all_ySystem);
							hvvBinnedHistos_yQ[n][afb_bin-1]->Fill(YQ_rec);
							
							//------------ etamu
							// hvvBinnedHistos_eta[n][afb_bin-1]->Fill(recon_all_eta->at(imuon_rec));
							hvvBinnedHistos_eta[n][afb_bin-1]->Fill(recon_all_eta->at(imuon_rec));
							
							//------------ yStar
							// hvvBinnedHistos_yStar[n][afb_bin-1]->Fill(Ystar_rec);
							hvvBinnedHistos_yStar[n][afb_bin-1]->Fill(Ystar_rec);
						}
						
						else // for Z0, ZP and KK we need to scale by the weight
						{
							//------------ imass
							// bin = vhMassWeights[model]->FindBin(truth_all_Mhat);
							// mass_weight = vhMassWeights[model]->GetBinContent(bin);
							// hvBinnedHistos_imass[n]->Fill(recon_all_Mhat,mass_weight);
							// hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat, mass_weight); // use all events
							bin = vhMassWeights[model]->FindBin(M_tru);
							mass_weight = vhMassWeights[model]->GetBinContent(bin);
							hvBinnedHistos_imass[n]->Fill(M_rec,mass_weight);
							hvBinnedHistos_imassRes[n]->Fill((M_rec-M_tru)/M_tru, mass_weight); // use all events
							
							//------------ cosTheta
							// bin = vvhCosThSumWeights[afb_bin-1][model]->FindBin(truth_all_CosThetaCS);
							// cost_weight = vvhCosThSumWeights[afb_bin-1][model]->GetBinContent(bin);
							// hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(recon_all_CosThetaCS,cost_weight);
							bin = vvhCosThSumWeights[afb_bin-1][model]->FindBin(COSTHETA_tru);
							if(bin<1  ||  bin>vvhCosThSumWeights[afb_bin-1][model]->GetNbinsX()) continue;
							cost_weight = vvhCosThSumWeights[afb_bin-1][model]->GetBinContent(bin);
							hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(COSTHETA_rec,cost_weight);
							
							//------------ yQ
							// bin = vvhyQSumWeights[afb_bin-1][model]->FindBin(truth_all_ySystem);
							// yQ_weight = vvhyQSumWeights[afb_bin-1][model]->GetBinContent(bin);
							// hvvBinnedHistos_yQ[n][afb_bin-1]->Fill(recon_all_ySystem,yQ_weight);
							bin = vvhyQSumWeights[afb_bin-1][model]->FindBin(YQ_tru);
							if(bin<1  ||  bin>vvhyQSumWeights[afb_bin-1][model]->GetNbinsX()) continue;
							yQ_weight = vvhyQSumWeights[afb_bin-1][model]->GetBinContent(bin);
							hvvBinnedHistos_yQ[n][afb_bin-1]->Fill(YQ_rec,yQ_weight);
							
							//------------ etamu
							bin = vvhEtaSumWeights[afb_bin-1][model]->FindBin(truth_all_mc_eta->at(imuon_tru));
							if(bin<1  ||  bin>vvhEtaSumWeights[afb_bin-1][model]->GetNbinsX()) continue;
							eta_weight = vvhEtaSumWeights[afb_bin-1][model]->GetBinContent(bin);
							hvvBinnedHistos_eta[n][afb_bin-1]->Fill(recon_all_eta->at(imuon_rec),eta_weight);
							
							//------------ yStar
							bin = vvhyStarSumWeights[afb_bin-1][model]->FindBin(Ystar_tru);
							if(bin<1  ||  bin>vvhyStarSumWeights[afb_bin-1][model]->GetNbinsX()) continue;
							yStar_weight = vvhyStarSumWeights[afb_bin-1][model]->GetBinContent(bin);
							hvvBinnedHistos_yStar[n][afb_bin-1]->Fill(Ystar_rec,yStar_weight);
							
							//------------ ntuple
							mass_tru = M_tru;
							mass_rec = M_rec;
							mass_wgt = mass_weight;
							cost_tru = COSTHETA_tru;
							cost_rec = COSTHETA_rec;
							cost_wgt = cost_weight;
							yQ_tru   = YQ_tru;
							yQ_rec   = YQ_rec;
							yQ_wgt   = yQ_weight;
							eta_tru  = truth_all_mc_eta->at(imuon_tru);
							eta_rec  = recon_all_eta->at(imuon_rec);
							eta_wgt  = eta_weight;
							yStar_tru = Ystar_tru;
							yStar_rec = Ystar_rec;
							yStar_wgt = yStar_weight;
							xscn_wgt = bin_xs_weight; // in units of fb
							
							tlv1Tru->SetPtEtaPhiM(truth_all_mc_pt->at(imuon_tru),truth_all_mc_eta->at(imuon_tru),truth_all_mc_phi->at(imuon_tru),muonMass);
							tlv2Tru->SetPtEtaPhiM(truth_all_mc_pt->at(iamuon_tru),truth_all_mc_eta->at(iamuon_tru),truth_all_mc_phi->at(iamuon_tru),muonMass);
							tlv1Rec->SetPtEtaPhiM(recon_all_pt->at(imuon_rec),recon_all_eta->at(imuon_rec),recon_all_phi->at(imuon_rec),muonMass);
							tlv2Rec->SetPtEtaPhiM(recon_all_pt->at(iamuon_rec),recon_all_eta->at(iamuon_rec),recon_all_phi->at(iamuon_rec),muonMass);
							
							fillNtuple(vvtBinnedNtuples[afb_bin-1][model],counter,modulu);
						}
						counter++;
					}
				}
				else // data
				{	
					imuon_rec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
					iamuon_rec = (imuon_rec==0) ? 1 : 0;
					tlva_rec->SetPtEtaPhiM(recon_all_pt->at(imuon_rec)*MeV2GeV,recon_all_eta->at(imuon_rec),recon_all_phi->at(imuon_rec),muonMass);
					tlvb_rec->SetPtEtaPhiM(recon_all_pt->at(iamuon_rec)*MeV2GeV,recon_all_eta->at(iamuon_rec),recon_all_phi->at(iamuon_rec),muonMass);
					ca_rec = recon_all_charge->at(imuon_rec);
					cb_rec = recon_all_charge->at(iamuon_rec);
					if(ca_rec*cb_rec>=0.)        {_WARNING("Reconstructed: ca_rec*cb_rec>=0., skipping event"); continue;};
					M_rec        = imass(tlva_rec,tlvb_rec);
					if(M_rec<=minPossibleImass || M_rec>maxPossibleImass) {_WARNING("Reconstructed: M_rec<=minPossibleImass || M_rec>maxPossibleImass  ->  M_rec="+_s(M_rec)+", skipping event"); continue;}
					COSTHETA_rec = cosThetaCollinsSoper(tlva_rec,ca_rec,tlvb_rec,cb_rec);
					if(fabs(COSTHETA_rec)>1.)   _WARNING("Reconstructed: |cos(theta)|>1.");
					YQ_rec       = ySystem(tlva_rec,tlvb_rec);
					if(fabs(YQ_rec)>6.)         _WARNING("Reconstructed: |yQ|>6.");
					Ystar_rec = yStar(tlva_rec,tlvb_rec);
				
					// afb_bin = hDummy_afb->FindBin(recon_all_Mhat*TeV2GeV);
					afb_bin = hDummy_afb->FindBin(M_rec);
					if(afb_bin<=0 || afb_bin>imass_afb_nbins) continue;
					
					// fill from d3pd, use all events

					//------------ imass
					// hvBinnedHistos_imass[n]->Fill(recon_all_Mhat*TeV2GeV);
					hvBinnedHistos_imass[n]->Fill(M_rec);
					
					//------------ cosTheta
					// hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(recon_all_CosThetaCS);
					hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(COSTHETA_rec);
					
					//------------ yQ
					// hvvBinnedHistos_yQ[n][afb_bin-1]->Fill(recon_all_ySystem);
					hvvBinnedHistos_yQ[n][afb_bin-1]->Fill(YQ_rec);
					
					//------------ etamu
					// hvvBinnedHistos_eta[n][afb_bin-1]->Fill(recon_all_eta->at(imuon_rec));
					hvvBinnedHistos_eta[n][afb_bin-1]->Fill(recon_all_eta->at(imuon_rec));
					
					//------------ yStar
					// hvvBinnedHistos_yStar[n][afb_bin-1]->Fill(Ystar_rec);
					hvvBinnedHistos_yStar[n][afb_bin-1]->Fill(Ystar_rec);
					
					//------------ ntuple
					mass_tru = -1;
					mass_rec = M_rec;
					mass_wgt = 1.;
					cost_tru = -1;
					cost_rec = COSTHETA_rec;
					cost_wgt = 1.;
					yQ_tru   = -1;
					yQ_rec   = YQ_rec;
					yQ_wgt   = 1.;
					eta_tru   = -1;
					eta_rec   = recon_all_eta->at(imuon_rec);
					eta_wgt   = 1.;
					yStar_tru   = -1;
					yStar_rec   = Ystar_rec;
					yStar_wgt   = 1.;
					xscn_wgt = 1.; // in units of fb
					
					tlv1Rec->SetPtEtaPhiM(recon_all_pt->at(imuon_rec),recon_all_eta->at(imuon_rec),recon_all_phi->at(imuon_rec),muonMass);
					tlv2Rec->SetPtEtaPhiM(recon_all_pt->at(iamuon_rec),recon_all_eta->at(iamuon_rec),recon_all_phi->at(iamuon_rec),muonMass);
					
					fillNtuple(vvtBinnedNtuples[afb_bin-1][model],counter,modulu);

					counter++;
				}
			}
			
			
			/////////////////////////////////////////////////////////////
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)       // scale /////
			{
				if(model!=DT)
				{
					hvvBinnedHistos_cosTh[n][i]->Scale(dvWeights[n]);
					hvvBinnedHistos_yQ[n][i]->Scale(dvWeights[n]);
					hvvBinnedHistos_eta[n][i]->Scale(dvWeights[n]);
					hvvBinnedHistos_yStar[n][i]->Scale(dvWeights[n]);
				}
				vhCosThSumTmp[i]->Add(hvvBinnedHistos_cosTh[n][i]);
				vhyQSumTmp[i]->Add(hvvBinnedHistos_yQ[n][i]);
				vhEtaSumTmp[i]->Add(hvvBinnedHistos_eta[n][i]);
				vhyStarSumTmp[i]->Add(hvvBinnedHistos_yStar[n][i]);
			}
			/////////////////////////////////////////////////////////////
			
			
			/////////////////////////////////////////////////////////////
			if(model!=DT)
			{
				hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
				hvBinnedHistos_imassRes[n]->Scale(dvWeights[n]); // scale ///
			}
			/////////////////////////////////////////////////////////////
			
			
			////////////////////////////////////////////////////
			hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //
			if(model!=DT) hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
			////////////////////////////////////////////////////
			
			file->Close();
		}
		
		

		if(model==DT)
		{
			hMassReconDTd3pd = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				vhCosThSumReconDTd3pd[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
				vhyQSumReconDTd3pd[i] = (TH1D*)vhyQSumTmp[i]->Clone("");
				vhEtaSumReconDTd3pd[i] = (TH1D*)vhEtaSumTmp[i]->Clone("");
				vhyStarSumReconDTd3pd[i] = (TH1D*)vhyStarSumTmp[i]->Clone("");
			}
		}
		else if(model==Z0d3pd)
		{
			hMassReconZ0d3pd = (TH1D*)hMassSumTmp->Clone("");
			hResReconZ0d3pd  = (TH1D*)hResTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				vhCosThSumReconZ0d3pd[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
				vhyQSumReconZ0d3pd[i] = (TH1D*)vhyQSumTmp[i]->Clone("");
				vhEtaSumReconZ0d3pd[i] = (TH1D*)vhEtaSumTmp[i]->Clone("");
				vhyStarSumReconZ0d3pd[i] = (TH1D*)vhyStarSumTmp[i]->Clone("");
			}
		}
		else
		{	
			vhMassReconTemplate[model] = (TH1D*)hMassSumTmp->Clone("");
			vhResTemplate[model] = (TH1D*)hResTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)
			{
				vvhCosThSumRecTemplate[i][model] = (TH1D*)vhCosThSumTmp[i]->Clone("");
				vvhyQSumRecTemplate[i][model] = (TH1D*)vhyQSumTmp[i]->Clone("");
				vvhEtaSumRecTemplate[i][model] = (TH1D*)vhEtaSumTmp[i]->Clone("");
				vvhyStarSumRecTemplate[i][model] = (TH1D*)vhyStarSumTmp[i]->Clone("");
			}
		}
		
	}
	cout << "Templates + data are ready\n" << endl;
	//-----------------------------------------------------------------------------
	
	
	// now do the acceptance calculations in every bin of imass and for the whole tsrange
	dirMassHistograms->cd();
	hMassSumZ0d3pd_acceptance = (TH1D*)hMassReconZ0d3pd->Clone("");
	//hMassSumZ0d3pd_acceptance->Divide(hMassSumZ0d3pd);
	divide(hMassSumZ0d3pd_acceptance,hMassSumZ0d3pd);
	hMassSumZ0d3pd_acceptance->SetName("hMassZ0d3pd_acceptance");
	hMassSumZ0d3pd_acceptance->Write("", TObject::kOverwrite);
	
	for(int mod=Z0 ; mod<=KK ; mod++)
	{
		if(mod==Z0) tsname = "Z0";
		if(mod==ZP) tsname = "ZP";
		if(mod==KK) tsname = "KK";
	
		dirMassHistograms->cd();
		vhMassAcceptance[mod] = (TH1D*)vhMassReconTemplate[mod]->Clone("");
		//vhMassAcceptance[mod]->Divide(vhMassSum[mod]);
		divide(vhMassAcceptance[mod],vhMassSum[mod]);
		vhMassAcceptance[mod]->SetName("hMass"+tsname+"_acceptance");
		vhMassAcceptance[mod]->Write("", TObject::kOverwrite);
	}
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		dirCostHistograms->cd();
		vhCosThSumZ0d3pd_acceptance[i] = (TH1D*)vhCosThSumReconZ0d3pd[i]->Clone("");
		//vhCosThSumZ0d3pd_acceptance[i]->Divide(vhCosThSumZ0d3pd[i]);
		divide(vhCosThSumZ0d3pd_acceptance[i],vhCosThSumZ0d3pd[i]);
		
		dirCostHistograms->cd();
		vhCosThSumZ0d3pd_acceptance[i]->SetName("hCosThZ0d3pd_acceptance_"+b);
		vhCosThSumZ0d3pd_acceptance[i]->Write("", TObject::kOverwrite);
		dirCostHistograms->cd();
		vhCosThSumReconZ0d3pd[i]->SetName("hCosThRecZ0d3pd_"+b);
		vhCosThSumReconZ0d3pd[i]->Write("", TObject::kOverwrite);
		dirCostHistograms->cd();
		vhCosThSumReconDTd3pd[i]->SetName("hCosThRecDTd3pd_"+b);
		vhCosThSumReconDTd3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
		
			dirCostHistograms->cd();
			vvhCosThSumAcceptance[i][mod] = (TH1D*)vvhCosThSumRecTemplate[i][mod]->Clone("");
			//vvhCosThSumAcceptance[i][mod]->Divide(vvhCosThSum[i][mod]);
			divide(vvhCosThSumAcceptance[i][mod],vvhCosThSum[i][mod]);
			
			dirCostHistograms->cd();
			vvhCosThSumAcceptance[i][mod]->SetName("hCosTh"+tsname+"_acceptance_"+b);
			vvhCosThSumAcceptance[i][mod]->Write("", TObject::kOverwrite);
			dirCostHistograms->cd();
			vvhCosThSumRecTemplate[i][mod]->SetName("hCosThRec"+tsname+"_"+b);
			vvhCosThSumRecTemplate[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		diryQHistograms->cd();
		vhyQSumReconZ0d3pd[i]->SetName("hyQRecZ0d3pd_"+b);
		vhyQSumReconZ0d3pd[i]->Write("", TObject::kOverwrite);
		diryQHistograms->cd();
		vhyQSumReconDTd3pd[i]->SetName("hyQRecDTd3pd_"+b);
		vhyQSumReconDTd3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			diryQHistograms->cd();
			vvhyQSumRecTemplate[i][mod]->SetName("hyQRec"+tsname+"_"+b);
			vvhyQSumRecTemplate[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		dirEtaHistograms->cd();
		vhEtaSumZ0d3pd_acceptance[i] = (TH1D*)vhEtaSumReconZ0d3pd[i]->Clone("");
		//vhEtaSumZ0d3pd_acceptance[i]->Divide(vhEtaSumZ0d3pd[i]);
		divide(vhEtaSumZ0d3pd_acceptance[i],vhEtaSumZ0d3pd[i]);
		
		dirEtaHistograms->cd();
		vhEtaSumZ0d3pd_acceptance[i]->SetName("hEtaZ0d3pd_acceptance_"+b);
		vhEtaSumZ0d3pd_acceptance[i]->Write("", TObject::kOverwrite);
		
		dirEtaHistograms->cd();
		vhEtaSumReconZ0d3pd[i]->SetName("hEtaRecZ0d3pd_"+b);
		vhEtaSumReconZ0d3pd[i]->Write("", TObject::kOverwrite);
		dirEtaHistograms->cd();
		vhEtaSumReconDTd3pd[i]->SetName("hEtaRecDTd3pd_"+b);
		vhEtaSumReconDTd3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			dirEtaHistograms->cd();
			vvhEtaSumAcceptance[i][mod] = (TH1D*)vvhEtaSumRecTemplate[i][mod]->Clone("");
			//vvhEtaSumAcceptance[i][mod]->Divide(vvhEtaSum[i][mod]);
			divide(vvhEtaSumAcceptance[i][mod],vvhEtaSum[i][mod]);
			
			dirEtaHistograms->cd();
			vvhEtaSumAcceptance[i][mod]->SetName("hEta"+tsname+"_acceptance_"+b);
			vvhEtaSumAcceptance[i][mod]->Write("", TObject::kOverwrite);
			dirEtaHistograms->cd();
			vvhEtaSumRecTemplate[i][mod]->SetName("hEtaRec"+tsname+"_"+b);
			vvhEtaSumRecTemplate[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		diryStarHistograms->cd();
		vhyStarSumZ0d3pd_acceptance[i] = (TH1D*)vhyStarSumReconZ0d3pd[i]->Clone("");
		//vhyStarSumZ0d3pd_acceptance[i]->Divide(vhyStarSumZ0d3pd[i]);
		divide(vhyStarSumZ0d3pd_acceptance[i],vhyStarSumZ0d3pd[i]);
		
		diryStarHistograms->cd();
		vhyStarSumZ0d3pd_acceptance[i]->SetName("hyStarZ0d3pd_acceptance_"+b);
		vhyStarSumZ0d3pd_acceptance[i]->Write("", TObject::kOverwrite);
		
		diryStarHistograms->cd();
		vhyStarSumReconZ0d3pd[i]->SetName("hyStarRecZ0d3pd_"+b);
		vhyStarSumReconZ0d3pd[i]->Write("", TObject::kOverwrite);
		diryStarHistograms->cd();
		vhyStarSumReconDTd3pd[i]->SetName("hyStarRecDTd3pd_"+b);
		vhyStarSumReconDTd3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			diryStarHistograms->cd();
			vvhyStarSumAcceptance[i][mod] = (TH1D*)vvhyStarSumRecTemplate[i][mod]->Clone("");
			//vvhyStarSumAcceptance[i][mod]->Divide(vvhyStarSum[i][mod]);
			divide(vvhyStarSumAcceptance[i][mod],vvhyStarSum[i][mod]);
			
			diryStarHistograms->cd();
			vvhyStarSumAcceptance[i][mod]->SetName("hyStar"+tsname+"_acceptance_"+b);
			vvhyStarSumAcceptance[i][mod]->Write("", TObject::kOverwrite);
			diryStarHistograms->cd();
			vvhyStarSumRecTemplate[i][mod]->SetName("hyStarRec"+tsname+"_"+b);
			vvhyStarSumRecTemplate[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	
	
	

	////////////////////////////
	// reset all ///////////////
	clearSamples(); ////////////
	if(doLogx) hMassSumTmp->Reset(); //////////
	else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
	hResTmp->Reset();
	////////////////////////////
	
	addSample("ATLASZP/mcLocalControl_Zprime_mumu_SSM1000",  col2, 18996, 0.00012973*nb2mb);
	
	// get the data
	ymin = 0.;
	vsize = (int)svPaths.size();
	
	for(int n=vsize-1 ; n>=0 ; n--)
	{
		cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
		file = TFile::Open(svPaths[n].c_str(),"READ");	
		tree = (TTree*)file->Get("truth/truth_tree");
		
		tree->SetBranchAddress( "truth_all_mc_pt", &truth_all_mc_pt );
		tree->SetBranchAddress( "truth_all_mc_m", &truth_all_mc_m );
		tree->SetBranchAddress( "truth_all_mc_eta", &truth_all_mc_eta );
		tree->SetBranchAddress( "truth_all_mc_phi", &truth_all_mc_phi );
		tree->SetBranchAddress( "truth_all_mc_status", &truth_all_mc_status );
		tree->SetBranchAddress( "truth_all_mc_barcode", &truth_all_mc_barcode );
		tree->SetBranchAddress( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
		tree->SetBranchAddress( "truth_all_mc_charge", &truth_all_mc_charge );
		tree->SetBranchAddress("truth_all_Mhat", &truth_all_Mhat);
		tree->SetBranchAddress("truth_all_CosThetaCS", &truth_all_CosThetaCS);
		tree->SetBranchAddress("truth_all_CosThetaHE", &truth_all_CosThetaHE);
		tree->SetBranchAddress("truth_all_ySystem",&truth_all_ySystem);
		tree->SetBranchAddress("truth_all_QT", &truth_all_QT);
		tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
				
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
		tree->SetBranchAddress("recon_all_ySystem",&recon_all_ySystem);
		tree->SetBranchAddress("recon_all_QT", &recon_all_QT);
		for(Int_t i=0 ; i<tree->GetEntries() ; i++)
		{
			tree->GetEntry(i);
			
			if(recon_all_isValid  &&  truth_all_isValid)
			{
				imuon_tru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
				iamuon_tru = (imuon_tru==0) ? 1 : 0;
				tlva_tru->SetPtEtaPhiM(truth_all_mc_pt->at(imuon_tru),truth_all_mc_eta->at(imuon_tru),truth_all_mc_phi->at(imuon_tru),muonMass);
				tlvb_tru->SetPtEtaPhiM(truth_all_mc_pt->at(iamuon_tru),truth_all_mc_eta->at(iamuon_tru),truth_all_mc_phi->at(iamuon_tru),muonMass);
				ca_tru = truth_all_mc_charge->at(imuon_tru);
				cb_tru = truth_all_mc_charge->at(iamuon_tru);
				if(ca_tru*cb_tru>=0.)       {_WARNING("Truth: ca_tru*cb_tru>=0., skipping event"); continue;};
				M_tru        = imass(tlva_tru,tlvb_tru);
				if(M_tru<=minPossibleImass || M_tru>maxPossibleImass) {_WARNING("Truth: M_tru<=minPossibleImass || M_tru>maxPossibleImass  ->  M_tru="+_s(M_tru)+", skipping event"); continue;}
				COSTHETA_tru = cosThetaCollinsSoper(tlva_tru,ca_tru,tlvb_tru,cb_tru);
				if(fabs(COSTHETA_tru)>1.)   _WARNING("Truth: |cos(theta)|>1.");
				YQ_tru       = ySystem(tlva_tru,tlvb_tru);
				if(fabs(YQ_tru)>6.)         _WARNING("Truth: |yQ|>6.");
				Ystar_tru = yStar(tlva_tru,tlvb_tru);
			
				imuon_rec  = (recon_all_charge->at(0)<0.) ? 0 : 1;
				iamuon_rec = (imuon_rec==0) ? 1 : 0;
				tlva_rec->SetPtEtaPhiM(recon_all_pt->at(imuon_rec),recon_all_eta->at(imuon_rec),recon_all_phi->at(imuon_rec),muonMass);
				tlvb_rec->SetPtEtaPhiM(recon_all_pt->at(iamuon_rec),recon_all_eta->at(iamuon_rec),recon_all_phi->at(iamuon_rec),muonMass);
				ca_rec = recon_all_charge->at(imuon_rec);
				cb_rec = recon_all_charge->at(iamuon_rec);
				if(ca_rec*cb_rec>=0.)       {_WARNING("Reconstructed: ca_rec*cb_rec>=0., skipping event"); continue;};
				M_rec        = imass(tlva_rec,tlvb_rec);
				if(M_rec<=minPossibleImass || M_rec>maxPossibleImass)
				{
					_WARNING("Reconstructed: M_rec<=minPossibleImass || M_rec>maxPossibleImass  ->  M_rec="+_s(M_rec)+", skipping event");
					_WARNING("\t pT="+_s(recon_all_pt->at(imuon_rec))+",  m="+_s(muonMass));
					continue;
				}
				COSTHETA_rec = cosThetaCollinsSoper(tlva_rec,ca_rec,tlvb_rec,cb_rec);
				if(fabs(COSTHETA_rec)>1.)   _WARNING("Reconstructed: |cos(theta)|>1.");
				YQ_rec       = ySystem(tlva_rec,tlvb_rec);
				if(fabs(YQ_rec)>6.)         _WARNING("Reconstructed: |yQ|>6.");
				Ystar_rec = yStar(tlva_rec,tlvb_rec);
			
				// hvBinnedHistos_imass[n]->Fill(recon_all_Mhat);
				// hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat); // use all events
				hvBinnedHistos_imass[n]->Fill(M_rec);
				hvBinnedHistos_imassRes[n]->Fill((M_rec-M_tru)/M_tru); // use all events
			}
		}

		/////////////////////////////////////////////////////////////
		hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
		hvBinnedHistos_imassRes[n]->Scale(dvWeights[n]); // scale ///
		/////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
		hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
		////////////////////////////////////////////////////

		file->Close();
		hMassReconZPd3pd = (TH1D*)hMassSumTmp->Clone("");
		hResReconZPd3pd = (TH1D*)hResTmp->Clone("");
	}
	cout << "Z' d3pd is read\n" << endl;
	//-----------------------------------------------------------------------------
	
	dirMassHistograms->cd();
	hMassSumZ0d3pd->SetName("hMassZ0d3pd");
	hMassSumZ0d3pd->Write("", TObject::kOverwrite);
	
	for(int mod=Z0 ; mod<=KK ; mod++) 
	{
		if(mod==Z0) tsname = "Z0";
		if(mod==ZP) tsname = "ZP";
		if(mod==KK) tsname = "KK";
		
		dirMassHistograms->cd();
		vhMassSum[mod]->SetName("hMass"+tsname);
		vhMassSum[mod]->Write("", TObject::kOverwrite);
		
		dirMassHistograms->cd();
		vhMassReconTemplate[mod]->SetName("hMassReconTemplate"+tsname);
		vhMassReconTemplate[mod]->Write("", TObject::kOverwrite);
	}

	dirMassHistograms->cd();
	hMassReconZ0d3pd->SetName("hMassReconZ0d3pd");
	hMassReconZ0d3pd->Write("", TObject::kOverwrite);
	
	dirMassHistograms->cd();
	hMassReconDTd3pd->SetName("hMassReconDTd3pd");
	hMassReconDTd3pd->Write("", TObject::kOverwrite);
	
	dirMassHistograms->cd();
	hMassReconZPd3pd->SetName("hMassReconZPd3pd");
	hMassReconZPd3pd->Write("", TObject::kOverwrite);
	
	dirAllHistograms->cd();
	hDummy_afb->SetName("hDummy_afb");
	hDummy_afb->Write("", TObject::kOverwrite);
	
	dirAllHistograms->cd();
	hMassSumTmp->SetName("hMassTmp");
	hMassSumTmp->Write("", TObject::kOverwrite);
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		dirCostHistograms->cd();
		vhCosThSumZ0d3pd[i]->SetName("hCosThTruZ0d3pd_"+b);
		vhCosThSumZ0d3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			dirCostHistograms->cd();
			vvhCosThSum[i][mod]->SetName("hCosThTru"+tsname+"_"+b);
			vvhCosThSum[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		diryQHistograms->cd();
		vhyQSumZ0d3pd[i]->SetName("hyQTruZ0d3pd_"+b);
		vhyQSumZ0d3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			diryQHistograms->cd();
			vvhyQSum[i][mod]->SetName("hyQTru"+tsname+"_"+b);
			vvhyQSum[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		dirEtaHistograms->cd();
		vhEtaSumZ0d3pd[i]->SetName("hEtaTruZ0d3pd_"+b);
		vhEtaSumZ0d3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++) 
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			dirEtaHistograms->cd();
			vvhEtaSum[i][mod]->SetName("hEtaTru"+tsname+"_"+b);
			vvhEtaSum[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		TString b = (TString)tostring(i+1);
		
		diryStarHistograms->cd();
		vhyStarSumZ0d3pd[i]->SetName("hyStarTruZ0d3pd_"+b);
		vhyStarSumZ0d3pd[i]->Write("", TObject::kOverwrite);
		
		for(int mod=Z0 ; mod<=KK ; mod++)
		{
			if(mod==Z0) tsname = "Z0";
			if(mod==ZP) tsname = "ZP";
			if(mod==KK) tsname = "KK";
			
			diryStarHistograms->cd();
			vvhyStarSum[i][mod]->SetName("hyStarTru"+tsname+"_"+b);
			vvhyStarSum[i][mod]->Write("", TObject::kOverwrite);
		}
	}
	
	
	
	
	string sYTitle = "";
	dirMassHistograms->cd();
	pad_sigma->cd();
	pad_sigma->Draw();
	ymin = 0.5*getYmin(hMassSumZ0d3pd);
	hMassSumZ0d3pd->SetMinimum(ymin);
	hMassSumZ0d3pd->SetMaximum(1.5*hMassSumZ0d3pd->GetMaximum());
	hMassSumZ0d3pd->SetLineColor(col0);
	hMassSumZ0d3pd->SetLineWidth(2);
	hMassSumZ0d3pd->SetTitle("");
	hMassSumZ0d3pd->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumZ0d3pd->SetYTitle("Events");
	if(doLogx) hMassSumZ0d3pd->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumZ0d3pd->GetXaxis()->SetMoreLogLabels(); 
	hMassSumZ0d3pd->Draw();
	//leg_mass->AddEntry(hMassSumZ0d3pd, "SM #gamma/Z^{0}", "l");
	leg_mass->AddEntry(hMassSumZ0d3pd, "SM #gamma/Z^{0} (#it{ATLAS} MC10 tru)", "l");
	
	for(int mod=Z0 ; mod<=DT ; mod++) 
	{
		Color_t col = 0;
		if(mod==Z0)
		{
			sName = "SM #gamma/Z^{0} (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			col = kBlue;
		}
		if(mod==ZP)
		{
			sName = sMass + " GeV Z' SSM (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			col = col2;
		}
		if(mod==KK)
		{
			sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
			col = kGreen+3;
		}
		if(mod==DT)
		{
			sName = "2011 Data";
			col = kBlack;
		}
	
		vhMassSum[mod]->SetLineColor(col);
		vhMassSum[mod]->SetLineWidth(2);
		vhMassSum[mod]->SetTitle("");
		vhMassSum[mod]->SetXTitle("#hat{m}_{#mu#mu} GeV");
		vhMassSum[mod]->SetYTitle("Events");
		if(doLogx) vhMassSum[mod]->GetXaxis()->SetMoreLogLabels(); 
		if(doLogx) vhMassSum[mod]->GetXaxis()->SetMoreLogLabels(); 
		vhMassSum[mod]->Draw("SAMES");
		leg_mass->AddEntry(vhMassSum[mod], sName.c_str(), "l");
	}
	leg_mass->Draw("SAMES");
	pvtxt->Draw("SAMES");
	pad_sigma->cd();
	pad_sigma->RedrawAxis();
	pad_sigma->Update();
	//-----------------------------------------------------------
	
	
	sYTitle = "Events_{#scale[1.1]{P}#scale[0.9]{YTHIA8}}/Events_{#gamma/Z^{0}}";
	dirMassHistograms->cd();
	pad_weights->cd();
	pad_weights->Draw();
	for(int mod=KK ; mod>=Z0 ; mod--)  // reverse !!!!
	{
		Color_t col = 0;
		TString drawOpt = "";
		if(mod==Z0)
		{
			sName = "SM #gamma/Z^{0}";
			col = kBlue;
			drawOpt = "SAMES";
		}
		if(mod==ZP)
		{
			sName = sMass + " GeV Z' SSM";
			col = col2;
			drawOpt = "SAMES";
		}
		if(mod==KK)
		{
			sName = sMass + " GeV S^{1}/Z_{2} KK";
			col = kGreen+3;
			drawOpt = "";
			ymin = 0.5*getYmin(vhMassWeights[mod]);
			vhMassWeights[mod]->SetMinimum(ymin);
			vhMassWeights[mod]->SetMaximum(1.5*vhMassWeights[mod]->GetMaximum());
		}
		
		vhMassWeights[mod]->SetLineColor(col);
		vhMassWeights[mod]->SetLineWidth(2);
		vhMassWeights[mod]->SetTitle("");
		vhMassWeights[mod]->SetXTitle("#hat{m}_{#mu#mu} GeV");
		vhMassWeights[mod]->SetYTitle(sYTitle.c_str());
		if(doLogx) vhMassWeights[mod]->GetXaxis()->SetMoreLogLabels(); 
		if(doLogx) vhMassWeights[mod]->GetXaxis()->SetMoreLogLabels(); 
		vhMassWeights[mod]->Draw(drawOpt);
		leg_weights->AddEntry(vhMassWeights[mod], sName.c_str(), "l");
	}
	leg_weights->Draw("SAMES");
	pad_weights->cd();
	pad_weights->RedrawAxis();
	pad_weights->Update();
	//-----------------------------------------------------------
	
	
	
	
	sYTitle = "Events";
	pad_recon_template->cd();
	pad_recon_template->Draw();
	
	ymin = 0.5*getYmin(hMassReconZ0d3pd);
	hMassReconZ0d3pd->SetMinimum(ymin);
	hMassReconZ0d3pd->SetMaximum(1.5*vhMassReconTemplate[KK]->GetMaximum()); // !!!
	hMassReconZ0d3pd->SetLineColor(col0);
	hMassReconZ0d3pd->SetLineWidth(2);
	hMassReconZ0d3pd->SetTitle("");
	hMassReconZ0d3pd->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconZ0d3pd->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconZ0d3pd->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconZ0d3pd->GetXaxis()->SetMoreLogLabels(); 
	hMassReconZ0d3pd->Draw();
	leg_mass_recon->AddEntry(hMassReconZ0d3pd, "SM #gamma/Z^{0} (#it{ATLAS} MC10 rec)", "l");
	
	for(int mod=Z0 ; mod<=KK ; mod++) 
	{
		Color_t col = 0;
		if(mod==Z0)
		{
			sName = "SM #gamma/Z^{0} Template";
			col = kBlue;
		}
		if(mod==ZP)
		{
			sName = sMass + " GeV Z' SSM Template";
			col = col2;
		}
		if(mod==KK)
		{
			sName = sMass + " GeV S^{1}/Z_{2} KK Template";
			col = kGreen+3;
		}
		
		vhMassReconTemplate[mod]->SetLineColor(col);
		vhMassReconTemplate[mod]->SetLineWidth(2);
		vhMassReconTemplate[mod]->SetTitle("");
		vhMassReconTemplate[mod]->SetXTitle("#hat{m}_{#mu#mu} GeV");
		vhMassReconTemplate[mod]->SetYTitle(sYTitle.c_str());
		if(doLogx) vhMassReconTemplate[mod]->GetXaxis()->SetMoreLogLabels(); 
		if(doLogx) vhMassReconTemplate[mod]->GetXaxis()->SetMoreLogLabels(); 
		vhMassReconTemplate[mod]->Draw("SAMES");
		leg_mass_recon->AddEntry(vhMassReconTemplate[mod], sName.c_str(), "l");
	}
	
	hMassReconDTd3pd->SetLineColor(kBlack);
	hMassReconDTd3pd->SetLineWidth(2);
	hMassReconDTd3pd->SetTitle("");
	hMassReconDTd3pd->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconDTd3pd->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconDTd3pd->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconDTd3pd->GetXaxis()->SetMoreLogLabels(); 
	// hMassReconDTd3pd->Draw("e1x0 SAMES");
	// leg_mass_recon->AddEntry(hMassReconDTd3pd, "2011 Data (#it{ATLAS} rec)", "lep");
	
	leg_mass_recon->Draw("SAMES");
	pvtxt_recon->Draw("SAMES");
	
	pad_recon_template->cd();
	pad_recon_template->RedrawAxis();
	pad_recon_template->Update();
	//--------------------------------------------------------------------------
	
	
	
	
	sYTitle = "Events";
	pad_compare->cd();
	pad_compare->Draw();
	
	sName = sMass + " GeV Z' SSM Template";
	ymin = 0.5*getYmin(vhMassReconTemplate[ZP]);
	vhMassReconTemplate[ZP]->SetMinimum(ymin);
	vhMassReconTemplate[ZP]->SetMaximum(1.5*vhMassReconTemplate[ZP]->GetMaximum()); // !!!
	vhMassReconTemplate[ZP]->SetLineColor(col2);
	vhMassReconTemplate[ZP]->SetLineWidth(2);
	vhMassReconTemplate[ZP]->SetTitle("");
	vhMassReconTemplate[ZP]->SetXTitle("#hat{m}_{#mu#mu} GeV");
	vhMassReconTemplate[ZP]->SetYTitle(sYTitle.c_str());
	if(doLogx) vhMassReconTemplate[ZP]->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) vhMassReconTemplate[ZP]->GetXaxis()->SetMoreLogLabels(); 
	vhMassReconTemplate[ZP]->Draw();
	leg_compare->AddEntry(vhMassReconTemplate[ZP], sName.c_str(), "l");
	
	
	sName = sMass + " GeV Z' SSM (#it{ATLAS} MC10 rec)";
	hMassReconZPd3pd->SetLineColor(col5);
	//hMassReconZPd3pd->SetLineStyle(2);
	hMassReconZPd3pd->SetLineWidth(2);
	hMassReconZPd3pd->SetTitle("");
	hMassReconZPd3pd->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconZPd3pd->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconZPd3pd->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconZPd3pd->GetXaxis()->SetMoreLogLabels(); 
	hMassReconZPd3pd->Draw("SAMES");
	leg_compare->AddEntry(hMassReconZPd3pd, sName.c_str(), "l");
	
	leg_compare->Draw("SAMES");
	pvtxt_compare->Draw("SAMES");
	
	pad_compare->cd();
	pad_compare->RedrawAxis();
	pad_compare->Update();
	
	
	
	cnv->Update();
	tsname = "plots/plot_weights_M" + (TString)sMass;
	cnv->SaveAs(tsname+".eps");
	cnv->SaveAs(tsname+".C");
	cnv->SaveAs(tsname+".root");
	cnv->SaveAs(tsname+".png");
	
	
	writeOutNtuples(dirNtuples);
	
	return 0;
}

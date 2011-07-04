#include "all.h"

// bins fore the cosTheta histos
double   costmin = minCosTheta;
double   costmax = maxCosTheta;
int      ncostbins = nCosThetaBins;

// bins for the mHat histos
double   xmin  = minMassBin; //120.;
double   xmax  = maxMassBin; //4000.;
const int        nxbins = 200;       //200;
static Double_t logMmin;
static Double_t logMmax;
static Double_t logMbinwidth;
static Double_t xbins[nxbins+1];

// bins for the afb (the binning is in mHat)
static double   imass_afb_min   = minMassBin; //120.;
static double   imass_afb_max   = maxMassBin; //4000.;
const int       imass_afb_nbins = nMassBins;  // const int nMassBins is defined in constants.h
static Double_t logMmin_afb;
static Double_t logMmax_afb;
static Double_t logMbinwidth_afb;
static Double_t imass_afb_bins[imass_afb_nbins+1];

static double lumi = 5.;
static double mb2fb = 1.e12;
static double nb2mb = 1.e-6;

TFile* fWeights;
TDirectory* dirAllHistograms;
TDirectory* dirCostHistograms;
TDirectory* dirMassHistograms;
TDirectory* dirNtuples;

vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvBinnedHistos_imass;
vector<TH1D*>  hvBinnedHistos_imass_unscaled;
vector<TH1D*>  hvBinnedHistos_imassRes;
vector<vector<TH1D*> > hvvBinnedHistos_cosTh;
vector<vector<TH1D*> > hvvBinnedHistos_cosTh_unscaled;
vector<TTree*> vtBinnedNtuples_KK;
vector<TTree*> vtBinnedNtuples_ZP;
TTree* tMassBins;
TTree* tAfbMassBins;
vector<double> dvWeights;
vector<Color_t> cvColors;

float mass_tru, mass_rec, mass_wgt, cost_tru, cost_rec, cost_wgt, xscn_wgt;

string sDir  = "/data/hod/pythia8_ntuples/";
string sName = "";

bool doLogx = true;

double sumWeights = 0.;

void clearSamples()
{	
	svNames.clear();
	svPaths.clear();
	for(int n=0 ; n<(int)hvBinnedHistos_imass.size() ; n++)
	{
		if(hvBinnedHistos_imass[n]!=NULL) delete hvBinnedHistos_imass[n];
		if(hvBinnedHistos_imass_unscaled[n]!=NULL) delete hvBinnedHistos_imass_unscaled[n];
		if(hvBinnedHistos_imassRes[n]!=NULL) delete hvBinnedHistos_imassRes[n];
		for(int m=0 ; m<(int)hvvBinnedHistos_cosTh[n].size() ; m++)
		{
			if(hvvBinnedHistos_cosTh[n][m]!=NULL) delete hvvBinnedHistos_cosTh[n][m];
			if(hvvBinnedHistos_cosTh_unscaled[n][m]!=NULL) delete hvvBinnedHistos_cosTh_unscaled[n][m];
		}
		hvvBinnedHistos_cosTh[n].clear();
	}
	hvBinnedHistos_imass.clear();
	hvBinnedHistos_imass_unscaled.clear();
	hvBinnedHistos_imassRes.clear();
	hvvBinnedHistos_cosTh.clear();
	hvvBinnedHistos_cosTh_unscaled.clear();
	dvWeights.clear();
	cvColors.clear();
}

void addSample(string name, Color_t color, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(sDir+sName+".root");
	
	if(doLogx)
	{
		hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nxbins,xbins));
		hvBinnedHistos_imass_unscaled.push_back(new TH1D((sName+"_unscaled").c_str(),(sName+"_unscaled").c_str(),nxbins,xbins));
	}
	else
	{
		hvBinnedHistos_imass.push_back(new TH1D(sName.c_str(),sName.c_str(),nxbins,xmin,xmax));
		hvBinnedHistos_imass_unscaled.push_back(new TH1D((sName+"_unscaled").c_str(),(sName+"_unscaled").c_str(),nxbins,xmin,xmax));
	}

	hvBinnedHistos_imassRes.push_back(new TH1D((sName+"Res").c_str(),(sName+"Res").c_str(),nxbins,-0.2,+0.2));

	vector<TH1D*> vTmp;
	vector<TH1D*> vTmp_unscaled;
	stringstream strm;
	string s;
	for(int b=0 ; b<imass_afb_nbins ; b++)
	{
		strm.clear();
		s.clear();
		strm << b;
		strm >> s;
		vTmp.push_back( new TH1D((sName+"_massbin_"+s).c_str(),(sName+"_massbin_"+s).c_str(),ncostbins,costmin,costmax) );
		vTmp_unscaled.push_back( new TH1D((sName+"unscaled_massbin_"+s).c_str(),(sName+"unscaled_massbin_"+s).c_str(),ncostbins,costmin,costmax) );
	}
	hvvBinnedHistos_cosTh.push_back( vTmp );
	hvvBinnedHistos_cosTh_unscaled.push_back( vTmp_unscaled );
	
	dvWeights.push_back(lumi/(events/(sigma*mb2fb)));
	cvColors.push_back(color);
	
	sumWeights += lumi/(events/(sigma*mb2fb));
}

// initialize the trees that will be handed to RooFit
void initOutNtuples(TDirectory* tDir)
{
	tDir->cd();
	
	stringstream strm;
	string str;
	string name;
	for(int t=1 ; t<=imass_afb_nbins ; t++)
	{
		strm.clear();
		str.clear();
		strm << t;
		strm >> str;

		name = "tree_ZP_" + str;
		vtBinnedNtuples_ZP.push_back( new TTree(name.c_str(), name.c_str()) );
		vtBinnedNtuples_ZP[t-1]->Branch( "mass_tru", &mass_tru );
		vtBinnedNtuples_ZP[t-1]->Branch( "mass_rec", &mass_rec );
		vtBinnedNtuples_ZP[t-1]->Branch( "mass_wgt", &mass_wgt );
		vtBinnedNtuples_ZP[t-1]->Branch( "cost_tru", &cost_tru );
		vtBinnedNtuples_ZP[t-1]->Branch( "cost_rec", &cost_rec );
		vtBinnedNtuples_ZP[t-1]->Branch( "cost_wgt", &cost_wgt );
		vtBinnedNtuples_ZP[t-1]->Branch( "xscn_wgt", &xscn_wgt );
		
		name = "tree_KK_" + str;
		vtBinnedNtuples_KK.push_back( new TTree(name.c_str(), name.c_str()) );
		vtBinnedNtuples_KK[t-1]->Branch( "mass_tru", &mass_tru );
		vtBinnedNtuples_KK[t-1]->Branch( "mass_rec", &mass_rec );
		vtBinnedNtuples_KK[t-1]->Branch( "mass_wgt", &mass_wgt );
		vtBinnedNtuples_KK[t-1]->Branch( "cost_tru", &cost_tru );
		vtBinnedNtuples_KK[t-1]->Branch( "cost_rec", &cost_rec );
		vtBinnedNtuples_KK[t-1]->Branch( "cost_wgt", &cost_wgt );
		vtBinnedNtuples_KK[t-1]->Branch( "xscn_wgt", &xscn_wgt );
	}
}

void writeOutNtuples(TDirectory* tDir)
{
	tDir->cd();

	for(int t=0 ; t<imass_afb_nbins ; t++)
	{
		fWeights = vtBinnedNtuples_ZP[t]->GetCurrentFile();
		fWeights->cd();
		tDir->cd();
		vtBinnedNtuples_ZP[t]->Write("", TObject::kOverwrite);
		
		fWeights = vtBinnedNtuples_KK[t]->GetCurrentFile();
		fWeights->cd();
		tDir->cd();
		vtBinnedNtuples_KK[t]->Write("", TObject::kOverwrite);
	}
	
	tMassBins->Write();
	tAfbMassBins->Write();
	
	fWeights->Write();
	fWeights->Close();
}



void fillNtuple(TTree* t, int counter, int mod)
{
	t->Fill();
	if(counter%mod==0)
	{
		t->FlushBaskets();
		//t->Write("", TObject::kOverwrite);
	}
	counter++;
}



int plot_ratio_weights()
{
	style();
	
	fWeights = new TFile("weights.root", "RECREATE");

	dirNtuples = fWeights->mkdir("ntuples");
	dirCostHistograms = fWeights->mkdir("cosTheta_histograms");
	dirMassHistograms = fWeights->mkdir("iMass_histograms");
	dirAllHistograms = fWeights->mkdir("all_histograms");
	
	dirAllHistograms->cd();
	
	initOutNtuples(dirNtuples);
	
	int counter = 0;
	int mod = 1000;
	
	float mHat;
	float qT;
	float ysystem;
	float cosThetaHE;
	float cosThetaCS;
	vector<int>*    index  = new vector<int>;
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
	

	logMmin  = log10(xmin);
	logMmax  = log10(xmax);
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)nxbins );
	xbins[0] = xmin;
	for(Int_t i=1 ; i<=nxbins ; i++) xbins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	tMassBins = new TTree("MassBins", "MassBins");
	Double_t MassBin;
	tMassBins->Branch( "MassBin", &MassBin );
	for(int i=0 ; i<nxbins ; i++)
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
	
	TPaveText* pvtxt = new TPaveText(0.1462841,0.4417869,0.5177747,0.6400528,"brNDC");
	pvtxt->SetFillColor(kWhite);
	TText* txt = pvtxt->AddText( "#splitline{Sum of binned #bf{truth}}{samples normalized to ~5 fb^{-1}}" );
	
	TPaveText* pvtxt_recon = new TPaveText(0.1462841,0.4417869,0.5177747,0.6400528,"brNDC");
	pvtxt_recon->SetFillColor(kWhite);
	txt = pvtxt_recon->AddText( "#splitline{Sum of binned #bf{template}}{samples normalized to ~5 fb^{-1}}" );
	
	TPaveText* pvtxt_compare = new TPaveText(0.5940635,0.6619171,0.8501254,0.8319301,"brNDC");
	pvtxt_compare->SetFillColor(kWhite);
	txt = pvtxt_compare->AddText( "#splitline{Template vs. #it{ATLAS}}{MC10 reconstructed}" );
	
	
	// for the binned-wights histograms
	logMmin_afb       = log10(imass_afb_min);
	logMmax_afb       = log10(imass_afb_max);
	logMbinwidth_afb  = (Double_t)( (logMmax_afb-logMmin_afb)/(Double_t)imass_afb_nbins );
	imass_afb_bins[0] = imass_afb_min;
	for(Int_t i=1 ; i<=imass_afb_nbins ; i++) imass_afb_bins[i] = TMath::Power( 10,(logMmin_afb + i*logMbinwidth_afb) );
	tAfbMassBins = new TTree("AfbMassBins", "AfbMassBins");
	Double_t AfbMassBin;
	tAfbMassBins->Branch( "AfbMassBin", &AfbMassBin );
	for(int i=0 ; i<imass_afb_nbins ; i++)
	{
		AfbMassBin = imass_afb_bins[i];
		tAfbMassBins->Fill();
	}
	
	dirCostHistograms->cd();
	TH1D* hDummy_afb = new TH1D("dummy","dummy",imass_afb_nbins,imass_afb_bins);
	
	vector<TH1D*> vhCosThSumTmp;
	vector<TH1D*> vhCosThSumTmp_unscaled;
	vector<TH1D*> vhCosThSumZ0_unscaled;
	vector<TH1D*> vhCosThSumZ0_acceptance;
	vector<TH1D*> vhCosThSumZ0;
	vector<TH1D*> vhCosThSumReconZ0;
	vector<TH1D*> vhCosThSumKK;
	vector<TH1D*> vhCosThSumReconTemplateKK;
	vector<TH1D*> vhCosThSumKK_acceptance;
	vector<TH1D*> vhCosThSumZP;
	vector<TH1D*> vhCosThSumReconTemplateZP;
	vector<TH1D*> vhCosThSumZP_acceptance;
	vector<TH1D*> vhCosThSumXSweights;
	vector<TH1D*> vhCosThSumKKweights;
	vector<TH1D*> vhCosThSumZPweights;
	stringstream strm;
	string str;
	string range;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		range.clear();
		strm.clear();
		str.clear();
		strm << imass_afb_bins[i];
		strm >> str;
		range += str + " GeV #rightarrow ";
		strm.clear();
		str.clear();
		strm << imass_afb_bins[i+1];
		strm >> str;
		range += str + " GeV";
		
		vhCosThSumTmp.push_back( new TH1D((""+range).c_str(),(""+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumTmp_unscaled.push_back( new TH1D(("xs"+range).c_str(),("xs"+range).c_str(), ncostbins,costmin,costmax) );
		
		vhCosThSumZ0.push_back( new TH1D(("sumZ0_"+range).c_str(),("sumZ0_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumReconZ0.push_back( new TH1D(("sumRecZ0_"+range).c_str(),("sumRecZ0_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumZ0_unscaled.push_back( new TH1D(("sumZ0_unscaled_"+range).c_str(),("sumZ0_unscaled_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumZ0_acceptance.push_back( new TH1D(("sumZ0_acceptance_"+range).c_str(),("sumZ0_acceptance_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumZP.push_back( new TH1D(("sumZP_"+range).c_str(),("sumZP_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumReconTemplateZP.push_back( new TH1D(("sumRecZP_"+range).c_str(),("sumRecZP_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumZP_acceptance.push_back( new TH1D(("sumZP_acceptance_"+range).c_str(),("sumZP_acceptance_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumKK.push_back( new TH1D(("sumKK_"+range).c_str(),("sumKK_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumReconTemplateKK.push_back( new TH1D(("sumRecKK_"+range).c_str(),("sumRecKK_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumKK_acceptance.push_back( new TH1D(("sumKK_acceptance_"+range).c_str(),("sumKK_acceptance_"+range).c_str(), ncostbins,costmin,costmax) );
		
		vhCosThSumXSweights.push_back( new TH1D(("wgtXS_"+range).c_str(),("wgtXS_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumZPweights.push_back( new TH1D(("wgtZP_"+range).c_str(),("wgtZP_"+range).c_str(), ncostbins,costmin,costmax) );
		vhCosThSumKKweights.push_back( new TH1D(("wgtKK_"+range).c_str(),("wgtKK_"+range).c_str(), ncostbins,costmin,costmax) );
	}
	
	
	// combined histos
	dirMassHistograms->cd();
	TH1D* hMassSumTmp;
	TH1D* hMassSumTmp_unscaled;
	TH1D* hResTmp;
	TH1D* hMassSumZ0;
	TH1D* hMassSumZ0_unscaled;
	TH1D* hMassSumZ0_acceptance;
	TH1D* hMassSumZP;
	TH1D* hMassSumZP_acceptance;
	TH1D* hMassSumKK;
	TH1D* hMassSumKK_acceptance;
	TH1D* hWeightsXS;
	TH1D* hWeightsZP;
	TH1D* hWeightsKK;
	TH1D* hMassReconZ0;
	TH1D* hMassReconZP;
	TH1D* hMassReconTemplateZP;
	TH1D* hMassReconTemplateKK;
	TH1D* hResReconZ0;
	TH1D* hResReconZP;
	TH1D* hResTemplateZP;
	TH1D* hResTemplateKK;
	if(doLogx)
	{
		hMassSumTmp = new TH1D("sumTmp","sumTmp",nxbins,xbins);
		hMassSumTmp_unscaled = new TH1D("sumTmp_unscaled","sumTmp_unscaled",nxbins,xbins);
		
		hMassSumZ0_unscaled = new TH1D("sumZ0_unscaled","sumZ0_unscaled",nxbins,xbins);
		hMassSumZ0 = new TH1D("sumZ0","sumZ0",nxbins,xbins);
		hMassSumZ0_acceptance = new TH1D("sumZ0_acceptance","sumZ0_acceptance",nxbins,xbins);
		hMassSumZP = new TH1D("sumZP","sumZP",nxbins,xbins);
		hMassSumZP_acceptance = new TH1D("sumZP_acceptance","sumZP_acceptance",nxbins,xbins);
		hMassSumKK = new TH1D("sumKK","sumKK",nxbins,xbins);
		hMassSumKK_acceptance = new TH1D("sumKK_acceptance","sumKK_acceptance",nxbins,xbins);
		hWeightsXS = new TH1D("weightsXS","weightsXS",nxbins,xbins);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nxbins,xbins);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nxbins,xbins);
		
		hMassReconZ0 = new TH1D("ReconZ0","ReconZ0",nxbins,xbins);
		hMassReconZP = new TH1D("ReconZP","ReconZP",nxbins,xbins);
		hMassReconTemplateZP = new TH1D("ReconTemplateZP","ReconTemplateZP",nxbins,xbins);
		hMassReconTemplateKK = new TH1D("ReconTemplateKK","ReconTemplateKK",nxbins,xbins);
	}
	else
	{
		hMassSumTmp = new TH1D("sumTmp","sumTmp",nxbins,xmin,xmax);
		hMassSumTmp_unscaled = new TH1D("sumTmp_unscaled","sumTmp_unscaled",nxbins,xmin,xmax);
		
		hMassSumZ0_unscaled = new TH1D("sumZ0_unscaled","sumZ0_unscaled",nxbins,xmin,xmax);
		hMassSumZ0 = new TH1D("sumZ0","sumZ0",nxbins,xmin,xmax);
		hMassSumZ0_acceptance = new TH1D("sumZ0_acceptance","sumZ0_acceptance",nxbins,xmin,xmax);
		hMassSumZP = new TH1D("sumZP","sumZP",nxbins,xmin,xmax);
		hMassSumZP_acceptance = new TH1D("sumZP_acceptance","sumZP_acceptance",nxbins,xmin,xmax);
		hMassSumKK = new TH1D("sumKK","sumKK",nxbins,xmin,xmax);
		hMassSumKK_acceptance = new TH1D("sumKK_acceptance","sumKK_acceptance",nxbins,xmin,xmax);
		hWeightsXS = new TH1D("weightsXS","weightsXS",nxbins,xmin,xmax);
		hWeightsZP = new TH1D("weightsZP","weightsZP",nxbins,xmin,xmax);
		hWeightsKK = new TH1D("weightsKK","weightsKK",nxbins,xmin,xmax);
		
		hMassReconZ0 = new TH1D("ReconZ0","ReconZ0",nxbins,xmin,xmax);
		hMassReconZP = new TH1D("ReconZP","ReconZP",nxbins,xmin,xmax);
		hMassReconTemplateZP = new TH1D("ReconTemplateZP","ReconTemplateZP",nxbins,xmin,xmax);
		hMassReconTemplateKK = new TH1D("ReconTemplateKK","ReconTemplateKK",nxbins,xmin,xmax);
	}
	dirAllHistograms->cd();
	hResTmp = new TH1D("ResTmp","ResTmp",nxbins,-0.2,+0.2);
	hResReconZ0 = new TH1D("ResReconZ0","ResReconZ0",nxbins,-0.2,+0.2);
	hResReconZP = new TH1D("ResReconZP","ResReconZP",nxbins,-0.2,+0.2);
	hResTemplateZP = new TH1D("ResZP","ResZP",nxbins,-0.2,+0.2);
	hResTemplateKK = new TH1D("ResKK","ResKK",nxbins,-0.2,+0.2);
	
	
	///////////////////////////////////
	double nGeneratedEvents = 5e5; ////
	///////////////////////////////////
	
	TFile* file;
	TTree* tree;
	double ymin = 0.;
	int vsize = 0;
	
	for(int model=Z0 ; model<=KK ; model++)
	{
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hMassSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
		if(doLogx) hMassSumTmp_unscaled->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp_unscaled->GetNbinsX() ; b++) hMassSumTmp_unscaled->SetBinContent(b,0.); }
		for(int i=0 ; i<imass_afb_nbins ; i++) vhCosThSumTmp[i]->Reset();
		for(int i=0 ; i<imass_afb_nbins ; i++) vhCosThSumTmp_unscaled[i]->Reset();
		////////////////////////////
	
		if(model==Z0)
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
		
		if(model==ZP && sMass=="1000")
		{
			addSample("Pythia8_ZprimeSSM1000mumu_120M500",  col0, nGeneratedEvents, 7.78812E-09);
			addSample("Pythia8_ZprimeSSM1000mumu_500M1500", col1, nGeneratedEvents, 1.08535E-10);
			addSample("Pythia8_ZprimeSSM1000mumu_1500M0",   col2, nGeneratedEvents, 2.42594E-13);
		}
		if(model==ZP && sMass=="2000")
		{
			addSample("Pythia8_ZprimeSSM2000mumu_120M1000",  col0, nGeneratedEvents, 7.91467E-09);
			addSample("Pythia8_ZprimeSSM2000mumu_1000M3000", col1, nGeneratedEvents, 1.94433E-12);
			addSample("Pythia8_ZprimeSSM2000mumu_3000M0",    col2, nGeneratedEvents, 3.27844E-16);
		}
		if(model==ZP && sMass=="3000")
		{
			addSample("Pythia8_ZprimeSSM3000mumu_120M1500",  col0, nGeneratedEvents, 7.94181E-09);
			addSample("Pythia8_ZprimeSSM3000mumu_1500M4500", col1, nGeneratedEvents, 8.9226E-14);
			addSample("Pythia8_ZprimeSSM3000mumu_4500M0",    col2, nGeneratedEvents, 1.18978E-19);
		}
		
		
		if(model==KK && sMass=="1000")
		{
			addSample("Pythia8_ZKK1000mumu_120M500",  col0, nGeneratedEvents, 6.87332E-09);
			addSample("Pythia8_ZKK1000mumu_500M1500", col1, nGeneratedEvents, 7.83954E-10);
			addSample("Pythia8_ZKK1000mumu_1500M0",   col2, nGeneratedEvents, 1.11827E-11);
		}
		if(model==KK && sMass=="2000")
		{
			addSample("Pythia8_ZKK2000mumu_120M1000",  col0, nGeneratedEvents, 7.68181E-09);
			addSample("Pythia8_ZKK2000mumu_1000M3000", col1, nGeneratedEvents, 1.22497E-11);
			addSample("Pythia8_ZKK2000mumu_3000M0",    col2, nGeneratedEvents, 3.44554E-15);
		}
		if(model==KK && sMass=="3000")
		{
			addSample("Pythia8_ZKK3000mumu_120M1500",  col0, nGeneratedEvents, 7.8351E-09);
			addSample("Pythia8_ZKK3000mumu_1500M4500", col1, nGeneratedEvents, 2.98849E-13);
			addSample("Pythia8_ZKK3000mumu_4500M0",    col2, nGeneratedEvents, 7.56956E-20);
		}
			
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");	
			if(model==Z0)
			{
				tree = (TTree*)file->Get("truth/truth_tree");
				tree->Branch( "truth_all_mc_pt", &truth_all_mc_pt );
				tree->Branch( "truth_all_mc_m", &truth_all_mc_m );
				tree->Branch( "truth_all_mc_eta", &truth_all_mc_eta );
				tree->Branch( "truth_all_mc_phi", &truth_all_mc_phi );
				tree->Branch( "truth_all_mc_status", &truth_all_mc_status );
				tree->Branch( "truth_all_mc_barcode", &truth_all_mc_barcode );
				tree->Branch( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
				tree->Branch( "truth_all_mc_charge", &truth_all_mc_charge );
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
						hvBinnedHistos_imass[n]->Fill(truth_all_Mhat);
						hvBinnedHistos_imass_unscaled[n]->Fill(truth_all_Mhat);
						int bin = hDummy_afb->FindBin(truth_all_Mhat);
						if(bin<=0 || bin>imass_afb_nbins) continue;
						hvvBinnedHistos_cosTh[n][bin-1]->Fill(truth_all_CosThetaCS);
						hvvBinnedHistos_cosTh_unscaled[n][bin-1]->Fill(truth_all_CosThetaCS);
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
					hvBinnedHistos_imass[n]->Fill(mHat);
					
					int bin = hDummy_afb->FindBin(mHat);
					if(bin<=0 || bin>imass_afb_nbins) continue;
					hvvBinnedHistos_cosTh[n][bin-1]->Fill(cosThetaCS); 
				}
			}
			
			/////////////////////////////////////////////////////////////
			hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)       // scale /////
			{
				hvvBinnedHistos_cosTh[n][i]->Scale(dvWeights[n]);
			}
			/////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////
			hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
			if(model==Z0) hMassSumTmp_unscaled->Add(hvBinnedHistos_imass_unscaled[n]); // sum //////
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)   // sum //////
			{
				vhCosThSumTmp[i]->Add(hvvBinnedHistos_cosTh[n][i]);
				if(model==Z0) vhCosThSumTmp_unscaled[i]->Add(hvvBinnedHistos_cosTh_unscaled[n][i]);
			}
			////////////////////////////////////////////////////////
			
			file->Close();
		}
		
		if(model==Z0)
		{
			hMassSumZ0 = (TH1D*)hMassSumTmp->Clone("");
			hMassSumZ0_unscaled = (TH1D*)hMassSumTmp_unscaled->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumZ0[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumZ0_unscaled[i] = (TH1D*)vhCosThSumTmp_unscaled[i]->Clone("");
		}
		if(model==ZP)
		{
			hMassSumZP = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumZP[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		}
		if(model==KK)
		{
			hMassSumKK = (TH1D*)hMassSumTmp->Clone("");
			for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumKK[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		}
	}
	

	////////////////////////////////////////////////////////////////
	// The ratios //////////////////////////////////////////////////
	hWeightsXS = (TH1D*)hMassSumZ0->Clone("");
	hWeightsXS->Divide(hMassSumZ0_unscaled); ////////////////////////////////
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		vhCosThSumXSweights[i] = (TH1D*)vhCosThSumZ0[i]->Clone(""); 
		vhCosThSumXSweights[i]->Divide(vhCosThSumZ0_unscaled[i]); 
	}
	//--------------------------------------------------------------
	hWeightsZP = (TH1D*)hMassSumZP->Clone(""); /////////////////////
	hWeightsZP->Divide(hMassSumZ0); ////////////////////////////////
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		vhCosThSumZPweights[i] = (TH1D*)vhCosThSumZP[i]->Clone(""); 
		vhCosThSumZPweights[i]->Divide(vhCosThSumZ0[i]); 
	}
	//--------------------------------------------------------------
	hWeightsKK = (TH1D*)hMassSumKK->Clone(""); /////////////////////
	hWeightsKK->Divide(hMassSumZ0); ////////////////////////////////
	for(Int_t i=0 ; i<imass_afb_nbins ; i++) 
	{
		vhCosThSumKKweights[i] = (TH1D*)vhCosThSumKK[i]->Clone(""); 
		vhCosThSumKKweights[i]->Divide(vhCosThSumZ0[i]); 
	}
	////////////////////////////////////////////////////////////////
	
	
	////////////////////////
	// Write weights ///////
	dirMassHistograms->cd(); ///
	hWeightsZP->SetName("hMassZP_wgt");
	hWeightsZP->Write(); ///
	dirMassHistograms->cd(); ///
	hWeightsXS->SetName("hMassXS_wgt");
	hWeightsXS->Write(); ///
	dirMassHistograms->cd(); ///
	hWeightsKK->SetName("hMassKK_wgt");
	hWeightsKK->Write(); ///
	////////////////////////

	
	
	// Rename cosTheta weights:
	dirCostHistograms->cd();
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		// WEIGHTS ....
		strm.clear();
		str.clear();
		strm << i+1;
		strm >> str;
		vhCosThSumXSweights[i]->SetTitle((TString)"weights_XS: " + (TString)vhCosThSumXSweights[i]->GetTitle());
		vhCosThSumXSweights[i]->SetName( ("hCosThXS_wgt_"+str).c_str() );
		vhCosThSumZPweights[i]->SetTitle((TString)"weights: " + (TString)vhCosThSumZPweights[i]->GetTitle());
		vhCosThSumZPweights[i]->SetName( ("hCosThZP_wgt_"+str).c_str() );
		vhCosThSumKKweights[i]->SetTitle((TString)"weights: " + (TString)vhCosThSumKKweights[i]->GetTitle());
		vhCosThSumKKweights[i]->SetName( ("hCosThKK_wgt_"+str).c_str() );
	}
	////////////////////////////////////////////////////////////////////////////
	
	
	// test draw
	dirCostHistograms->cd();
	vector<TCanvas*> vC;
	vector<TVirtualPad*> vP1;
	vector<TVirtualPad*> vP2;
	vector<TLegend*> vL1;
	vector<TLegend*> vL2;
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		strm.clear();
		str.clear();
		strm << i;
		strm >> str;
		vC.push_back( new TCanvas(("c"+str).c_str(),("c"+str).c_str(),0,0,1200,800) );
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
		float max = vhCosThSumZ0[i]->GetMaximum();
		max = (vhCosThSumZP[i]->GetMaximum() > max) ? vhCosThSumZP[i]->GetMaximum() : max;
		max = (vhCosThSumKK[i]->GetMaximum() > max) ? vhCosThSumKK[i]->GetMaximum() : max;
	
		vhCosThSumZ0[i]->SetMinimum(1.e-2);
		vhCosThSumZ0[i]->SetMaximum(5.*max);
		vhCosThSumZ0[i]->SetLineColor(col0);
		vhCosThSumZ0[i]->SetLineStyle(1);
		vhCosThSumZ0[i]->SetLineWidth(2);
		vhCosThSumZ0[i]->SetXTitle("cos#theta*");
		vhCosThSumZ0[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhCosThSumZ0[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumZ0[i]->Draw();
		vL1[i]->AddEntry(vhCosThSumZ0[i], "SM #gamma/Z^{0} (#it{ATLAS} MC10 truth)", "l");
		vhCosThSumZP[i]->SetMinimum(1.e-2);
		vhCosThSumZP[i]->SetMaximum(5.*max);
		vhCosThSumZP[i]->SetLineColor(col2);
		vhCosThSumZP[i]->SetLineStyle(1);
		vhCosThSumZP[i]->SetLineWidth(2);
		vhCosThSumZP[i]->SetXTitle("cos#theta*");
		vhCosThSumZP[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhCosThSumZP[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumZP[i]->Draw("SAMES");
		sName = sMass + " GeV Z' SSM (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
		vL1[i]->AddEntry(vhCosThSumZP[i], sName.c_str(), "l");
		vhCosThSumKK[i]->SetMinimum(1.e-2);
		vhCosThSumKK[i]->SetMaximum(5.*max);
		vhCosThSumKK[i]->SetLineColor(col1);
		vhCosThSumKK[i]->SetLineStyle(1);
		vhCosThSumKK[i]->SetLineWidth(2);
		vhCosThSumKK[i]->SetXTitle("cos#theta*");
		vhCosThSumKK[i]->SetYTitle("Events");
		//if(5.*max<1.e2) vhCosThSumKK[i]->GetYaxis()->SetMoreLogLabels();
		vhCosThSumKK[i]->Draw("SAMES");
		sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})"; 
		vL1[i]->AddEntry(vhCosThSumKK[i], sName.c_str(), "l");
		vL1[i]->Draw("SAMES");
		
		vP1[i]->cd();
		vP1[i]->RedrawAxis();
		vP1[i]->Update();
		
		//--------------------------------------------
		
		vP2[i]->cd();
		vP2[i]->Draw();
		max = vhCosThSumZPweights[i]->GetMaximum();
		max = (vhCosThSumKKweights[i]->GetMaximum() > max) ? vhCosThSumKKweights[i]->GetMaximum() : max;
		
		string sYTitle = "Events_{BSM}/Events_{#gamma/Z^{0}}";
		sName = sMass + " GeV Z' SSM";
		vhCosThSumZPweights[i]->SetMinimum(1.e-1);
		vhCosThSumZPweights[i]->SetMaximum(5.*max);
		vhCosThSumZPweights[i]->SetLineColor(col2);
		vhCosThSumZPweights[i]->SetLineStyle(1);
		vhCosThSumZPweights[i]->SetLineWidth(2);
		vhCosThSumZPweights[i]->SetXTitle("cos#theta*");
		vhCosThSumZPweights[i]->SetYTitle(sYTitle.c_str());
		//if(5.*max<1.e2) vhCosThSumZPweights[i]->GetYaxis()->SetMoreLogLabels(); 
		vhCosThSumZPweights[i]->Draw();
		vL2[i]->AddEntry(vhCosThSumZPweights[i], sName.c_str(), "l");
		sName   = sMass + " GeV S^{1}/Z_{2} KK";
		vhCosThSumKKweights[i]->SetMinimum(1.e-1);
		vhCosThSumKKweights[i]->SetMaximum(5.*max);
		vhCosThSumKKweights[i]->SetLineColor(col1);
		vhCosThSumKKweights[i]->SetLineStyle(1);
		vhCosThSumKKweights[i]->SetLineWidth(2);
		vhCosThSumKKweights[i]->SetXTitle("cos#theta*");
		vhCosThSumKKweights[i]->SetYTitle(sYTitle.c_str());
		//if(5.*max<1.e2) vhCosThSumKKweights[i]->GetYaxis()->SetMoreLogLabels(); 
		vhCosThSumKKweights[i]->Draw("SAMES");
		vL2[i]->AddEntry(vhCosThSumKKweights[i], sName.c_str(), "l");
		vL2[i]->Draw("SAMES");
		
		vP2[i]->cd();
		vP2[i]->RedrawAxis();
		vP2[i]->Update();
		
		vC[i]->Update();
		TString name = "plots/plot_cosTheta_" + str;
		vC[i]->SaveAs(name+".eps");
		vC[i]->SaveAs(name+".C");
		vC[i]->SaveAs(name+".root");
		vC[i]->SaveAs(name+".png");
	}
	
	
	/////////////////////////////////////////////////////
	// Write all to the weights.root file ///////////////
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		dirCostHistograms->cd();
		vhCosThSumXSweights[i]->Write();
		dirCostHistograms->cd();
		vhCosThSumZPweights[i]->Write();
		dirCostHistograms->cd();
		vhCosThSumKKweights[i]->Write();
	}
	///////////////////////////////////////////////////////
	cout << "Weights are calculated and written\n" << endl;
	//-------------------------------------------------------------------------------------
	
	
	
	
	
	
	
	// read the rec+tru branches simultaneously
	for(int model=Z0 ; model<=KK ; model++)
	{
		////////////////////////////
		// reset all ///////////////
		clearSamples(); ////////////
		if(doLogx) hMassSumTmp->Reset(); //////////
		else { for(Int_t b=0 ; b<=hMassSumTmp->GetNbinsX() ; b++) hMassSumTmp->SetBinContent(b,0.); }
		hResTmp->Reset();
		for(int i=0 ; i<imass_afb_nbins ; i++) vhCosThSumTmp[i]->Reset();
		
		////////////////////////////
	
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
			
		// get the data
		ymin = 0.;
		vsize = (int)svPaths.size();
		int afb_bin = 0;
		for(int n=vsize-1 ; n>=0 ; n--)
		{
			cout << "svPaths[" << n << "]=" << svPaths[n] << endl;
			file = TFile::Open(svPaths[n].c_str(),"READ");	
			tree = (TTree*)file->Get("truth/truth_tree");
			
			tree->Branch( "truth_all_mc_pt", &truth_all_mc_pt );
			tree->Branch( "truth_all_mc_m", &truth_all_mc_m );
			tree->Branch( "truth_all_mc_eta", &truth_all_mc_eta );
			tree->Branch( "truth_all_mc_phi", &truth_all_mc_phi );
			tree->Branch( "truth_all_mc_status", &truth_all_mc_status );
			tree->Branch( "truth_all_mc_barcode", &truth_all_mc_barcode );
			tree->Branch( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
			tree->Branch( "truth_all_mc_charge", &truth_all_mc_charge );
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
				Int_t    bin    = 0;
				Double_t weight = 0.;
				
				
				if(recon_all_isValid  &&  truth_all_isValid)
				{
					// for all models (practically we read only the Z0 and weight the ZP and KK)
					afb_bin = hDummy_afb->FindBin(truth_all_Mhat);
					if(afb_bin<=0 || afb_bin>imass_afb_nbins) continue;
				
					if(model==Z0) hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(recon_all_CosThetaCS);
					
					// for ZP and KK we need to scale by the weight
					if(model==ZP)
					{
						bin    = vhCosThSumZPweights[afb_bin-1]->FindBin(truth_all_CosThetaCS);
						weight = vhCosThSumZPweights[afb_bin-1]->GetBinContent(bin);
						hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(recon_all_CosThetaCS,weight);
					}
					if(model==KK)
					{
						bin    = vhCosThSumKKweights[afb_bin-1]->FindBin(truth_all_CosThetaCS);
						weight = vhCosThSumKKweights[afb_bin-1]->GetBinContent(bin);
						hvvBinnedHistos_cosTh[n][afb_bin-1]->Fill(recon_all_CosThetaCS,weight);
					}
				}
				
				
				
			
				
				if(recon_all_isValid  &&  truth_all_isValid)
				{
					
					if(model==Z0)
					{
						hvBinnedHistos_imass[n]->Fill(recon_all_Mhat);
						hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat); // use all events
					}
					if(model==ZP)
					{
						bin = hWeightsZP->FindBin(truth_all_Mhat);
						weight = hWeightsZP->GetBinContent(bin);
						hvBinnedHistos_imass[n]->Fill(recon_all_Mhat,weight);
						hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat, weight); // use all events
						
						afb_bin = hDummy_afb->FindBin(truth_all_Mhat);
						if(afb_bin<=0 || afb_bin>imass_afb_nbins) continue;
						mass_tru = truth_all_Mhat;
						mass_rec = recon_all_Mhat;
						mass_wgt = weight;
						cost_tru = truth_all_CosThetaCS;
						cost_rec = recon_all_CosThetaCS;
						bin = vhCosThSumZPweights[afb_bin-1]->FindBin(truth_all_CosThetaCS);
						cost_wgt = vhCosThSumZPweights[afb_bin-1]->GetBinContent(bin);
						xscn_wgt = dvWeights[n]/lumi; // in units of fb
						fillNtuple(vtBinnedNtuples_ZP[afb_bin-1],counter,mod);
					}
					if(model==KK)
					{
						bin = hWeightsKK->FindBin(truth_all_Mhat);
						weight = hWeightsKK->GetBinContent(bin);
						hvBinnedHistos_imass[n]->Fill(recon_all_Mhat,weight);
						hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat, weight); // use all events
						
						afb_bin = hDummy_afb->FindBin(truth_all_Mhat);
						if(afb_bin<=0 || afb_bin>imass_afb_nbins) continue;
						mass_tru = truth_all_Mhat;
						mass_rec = recon_all_Mhat;
						mass_wgt = weight;
						cost_tru = truth_all_CosThetaCS;
						cost_rec = recon_all_CosThetaCS;
						bin = vhCosThSumKKweights[afb_bin-1]->FindBin(truth_all_CosThetaCS);
						cost_wgt = vhCosThSumKKweights[afb_bin-1]->GetBinContent(bin);
						xscn_wgt = dvWeights[n]/lumi; // in units of fb
						fillNtuple(vtBinnedNtuples_KK[afb_bin-1],counter,mod);
					}
					counter++;
				}
			}
			
			
			/////////////////////////////////////////////////////////////
			for(Int_t i=0 ; i<imass_afb_nbins ; i++)       // scale /////
			{
				hvvBinnedHistos_cosTh[n][i]->Scale(dvWeights[n]);
				vhCosThSumTmp[i]->Add(hvvBinnedHistos_cosTh[n][i]);
			}
			/////////////////////////////////////////////////////////////
			
			
			
			/////////////////////////////////////////////////////////////
			hvBinnedHistos_imass[n]->Scale(dvWeights[n]); // scale //////
			hvBinnedHistos_imassRes[n]->Scale(dvWeights[n]); // scale ///
			/////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////
			hMassSumTmp->Add(hvBinnedHistos_imass[n]); // sum //////
			hResTmp->Add(hvBinnedHistos_imassRes[n]); // sum ///
			////////////////////////////////////////////////////
			
			file->Close();
		}
		

		if(model==Z0) for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumReconZ0[i]         = (TH1D*)vhCosThSumTmp[i]->Clone("");
		if(model==ZP) for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumReconTemplateZP[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		if(model==KK) for(Int_t i=0 ; i<imass_afb_nbins ; i++) vhCosThSumReconTemplateKK[i] = (TH1D*)vhCosThSumTmp[i]->Clone("");
		
		if(model==Z0) hMassReconZ0         = (TH1D*)hMassSumTmp->Clone("");
		if(model==ZP) hMassReconTemplateZP = (TH1D*)hMassSumTmp->Clone("");
		if(model==KK) hMassReconTemplateKK = (TH1D*)hMassSumTmp->Clone("");
		
		if(model==Z0) hResReconZ0 = (TH1D*)hResTmp->Clone("");
		if(model==ZP) hResTemplateZP = (TH1D*)hResTmp->Clone("");
		if(model==KK) hResTemplateKK = (TH1D*)hResTmp->Clone("");
	}
	cout << "Templates are ready\n" << endl;
	//-----------------------------------------------------------------------------
	
	
	
	// now do the acceptance calculations in every bin of imass and for the whole range
	dirMassHistograms->cd();
	hMassSumZ0_acceptance = (TH1D*)hMassReconZ0->Clone("");
	hMassSumZ0_acceptance->Divide(hMassSumZ0);
	hMassSumZ0_acceptance->SetName("hMassZ0_acceptance");
	hMassSumZ0_acceptance->Write();
	dirMassHistograms->cd();
	hMassSumZP_acceptance = (TH1D*)hMassReconTemplateZP->Clone("");
	hMassSumZP_acceptance->Divide(hMassSumZP);
	hMassSumZP_acceptance->SetName("hMassZP_acceptance");
	hMassSumZP_acceptance->Write();
	dirMassHistograms->cd();
	hMassSumKK_acceptance = (TH1D*)hMassReconTemplateKK->Clone("");
	hMassSumKK_acceptance->Divide(hMassSumKK);
	hMassSumKK_acceptance->SetName("hMassKK_acceptance");
	hMassSumKK_acceptance->Write();
	
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		strm.clear();
		str.clear();
		strm << i+1;
		strm >> str;
		
		dirCostHistograms->cd();
		vhCosThSumZ0_acceptance[i] = (TH1D*)vhCosThSumReconZ0[i]->Clone("");
		vhCosThSumZ0_acceptance[i]->Divide(vhCosThSumZ0[i]);
		vhCosThSumZ0_acceptance[i]->SetName(("hCosThZ0_acceptance_"+str).c_str());
		vhCosThSumZ0_acceptance[i]->Write();
		vhCosThSumReconZ0[i]->SetName(("hCosThRecZ0_"+str).c_str());
		vhCosThSumReconZ0[i]->Write();
		dirCostHistograms->cd();
		vhCosThSumZP_acceptance[i] = (TH1D*)vhCosThSumReconTemplateZP[i]->Clone("");
		vhCosThSumZP_acceptance[i]->Divide(vhCosThSumZP[i]);
		vhCosThSumZP_acceptance[i]->SetName(("hCosThZP_acceptance_"+str).c_str());
		vhCosThSumZP_acceptance[i]->Write();
		vhCosThSumReconTemplateZP[i]->SetName(("hCosThRecZP_"+str).c_str());
		vhCosThSumReconTemplateZP[i]->Write();
		dirCostHistograms->cd();
		vhCosThSumKK_acceptance[i] = (TH1D*)vhCosThSumReconTemplateKK[i]->Clone("");
		vhCosThSumKK_acceptance[i]->Divide(vhCosThSumKK[i]);
		vhCosThSumKK_acceptance[i]->SetName(("hCosThKK_acceptance_"+str).c_str());
		vhCosThSumKK_acceptance[i]->Write();
		vhCosThSumReconTemplateKK[i]->SetName(("hCosThRecKK_"+str).c_str());
		vhCosThSumReconTemplateKK[i]->Write();
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
		
		tree->Branch( "truth_all_mc_pt", &truth_all_mc_pt );
		tree->Branch( "truth_all_mc_m", &truth_all_mc_m );
		tree->Branch( "truth_all_mc_eta", &truth_all_mc_eta );
		tree->Branch( "truth_all_mc_phi", &truth_all_mc_phi );
		tree->Branch( "truth_all_mc_status", &truth_all_mc_status );
		tree->Branch( "truth_all_mc_barcode", &truth_all_mc_barcode );
		tree->Branch( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
		tree->Branch( "truth_all_mc_charge", &truth_all_mc_charge );
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
			
			//if(recon_all_isValid  &&  truth_all_isValid)
			//{
				hvBinnedHistos_imass[n]->Fill(recon_all_Mhat);
				hvBinnedHistos_imassRes[n]->Fill((recon_all_Mhat-truth_all_Mhat)/truth_all_Mhat); // use all events
			//}
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
		hMassReconZP = (TH1D*)hMassSumTmp->Clone("");
		hResReconZP = (TH1D*)hResTmp->Clone("");
	}
	cout << "Templates are ready\n" << endl;
	//-----------------------------------------------------------------------------
	
	dirMassHistograms->cd();
	hMassSumZ0->SetName("hMassZ0");
	hMassSumZ0->Write();
	dirMassHistograms->cd();
	hMassSumKK->SetName("hMassKK");
	hMassSumKK->Write();
	dirMassHistograms->cd();
	hMassSumZP->SetName("hMassZP");
	hMassSumZP->Write();
	dirMassHistograms->cd();
	hMassReconZ0->SetName("hMassReconZ0");
	hMassReconZ0->Write();
	dirMassHistograms->cd();
	hMassReconTemplateZP->SetName("hMassReconTemplateZP");
	hMassReconTemplateZP->Write();
	dirMassHistograms->cd();
	hMassReconTemplateKK->SetName("hMassReconTemplateKK");
	hMassReconTemplateKK->Write();
	dirMassHistograms->cd();
	hMassReconZP->SetName("hMassReconZP");
	hMassReconZP->Write();
	dirAllHistograms->cd();
	hDummy_afb->SetName("hDummy_afb");
	hDummy_afb->Write();
	dirAllHistograms->cd();
	hMassSumTmp->SetName("hMassTmp");
	hMassSumTmp->Write();
	for(Int_t i=0 ; i<imass_afb_nbins ; i++)
	{
		strm.clear();
		str.clear();
		strm << i+1;
		strm >> str;
		
		dirCostHistograms->cd();
		vhCosThSumZ0[i]->SetName(("hCosThTruZ0_"+str).c_str());
		vhCosThSumZ0[i]->Write();
		dirCostHistograms->cd();
		vhCosThSumZP[i]->SetName(("hCosThTruZP_"+str).c_str());
		vhCosThSumZP[i]->Write();
		dirCostHistograms->cd();
		vhCosThSumKK[i]->SetName(("hCosThTruKK_"+str).c_str());
		vhCosThSumKK[i]->Write();
	}
	
	
	
	
	string sYTitle = "";
	
	dirMassHistograms->cd();
	pad_sigma->cd();
	pad_sigma->Draw();
	ymin = 0.5*getYmin(hMassSumZ0);
	hMassSumZ0->SetMinimum(ymin);
	hMassSumZ0->SetMaximum(1.5*hMassSumZ0->GetMaximum());
	hMassSumZ0->SetLineColor(col0);
	hMassSumZ0->SetLineWidth(2);
	hMassSumZ0->SetTitle("");
	hMassSumZ0->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumZ0->SetYTitle("Events");
	if(doLogx) hMassSumZ0->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumZ0->GetXaxis()->SetMoreLogLabels(); 
	hMassSumZ0->Draw();
	//leg_mass->AddEntry(hMassSumZ0, "SM #gamma/Z^{0}", "l");
	leg_mass->AddEntry(hMassSumZ0, "SM #gamma/Z^{0} (#it{ATLAS} MC10 truth)", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} KK (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
	hMassSumKK->SetLineColor(col1);
	hMassSumKK->SetLineWidth(2);
	hMassSumKK->SetTitle("");
	hMassSumKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumKK->SetYTitle("Events");
	if(doLogx) hMassSumKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumKK->GetXaxis()->SetMoreLogLabels();
	hMassSumKK->Draw("SAMES");
	leg_mass->AddEntry(hMassSumKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM (#scale[1.1]{P}#scale[0.9]{YTHIA8})";
	hMassSumZP->SetLineColor(col2);
	hMassSumZP->SetLineWidth(2);
	hMassSumZP->SetTitle("");
	hMassSumZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassSumZP->SetYTitle("Events");
	if(doLogx) hMassSumZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassSumZP->GetXaxis()->SetMoreLogLabels(); 
	hMassSumZP->Draw("SAMES");
	leg_mass->AddEntry(hMassSumZP, sName.c_str(), "l");
	
	leg_mass->Draw("SAMES");
	pvtxt->Draw("SAMES");
	
	pad_sigma->cd();
	pad_sigma->RedrawAxis();
	pad_sigma->Update();
	//-----------------------------------------------------------
	
	
	
	
	sYTitle = "Events_{BSM}/Events_{#gamma/Z^{0}}";
	pad_weights->cd();
	pad_weights->Draw();
	sName = sMass + " GeV S^{1}/Z_{2} KK";
	ymin = 0.5*getYmin(hWeightsKK);
	hWeightsKK->SetMinimum(ymin);
	hWeightsKK->SetMaximum(1.5*hWeightsKK->GetMaximum());
	hWeightsKK->SetLineColor(col1);
	hWeightsKK->SetLineWidth(2);
	hWeightsKK->SetTitle("");
	hWeightsKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hWeightsKK->SetYTitle(sYTitle.c_str());
	if(doLogx) hWeightsKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hWeightsKK->GetXaxis()->SetMoreLogLabels(); 
	hWeightsKK->Draw();
	leg_weights->AddEntry(hWeightsKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM";
	hWeightsZP->SetLineColor(col2);
	hWeightsZP->SetLineWidth(2);
	hWeightsZP->SetTitle("");
	hWeightsZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hWeightsZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hWeightsZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hWeightsZP->GetXaxis()->SetMoreLogLabels(); 
	hWeightsZP->Draw("SAMES");
	leg_weights->AddEntry(hWeightsZP, sName.c_str(), "l");
	
	leg_weights->Draw("SAMES");
	
	pad_weights->cd();
	pad_weights->RedrawAxis();
	pad_weights->Update();
	//-----------------------------------------------------------
	
	
	
	
	sYTitle = "Events";
	pad_recon_template->cd();
	pad_recon_template->Draw();
	
	ymin = 0.5*getYmin(hMassReconZ0);
	hMassReconZ0->SetMinimum(ymin);
	hMassReconZ0->SetMaximum(1.5*hMassReconTemplateKK->GetMaximum()); // !!!
	hMassReconZ0->SetLineColor(col0);
	hMassReconZ0->SetLineWidth(2);
	hMassReconZ0->SetTitle("");
	hMassReconZ0->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconZ0->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconZ0->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconZ0->GetXaxis()->SetMoreLogLabels(); 
	hMassReconZ0->Draw();
	leg_mass_recon->AddEntry(hMassReconZ0, "SM #gamma/Z^{0} (#it{ATLAS} MC10 reconstructed)", "l");
	
	sName = sMass + " GeV S^{1}/Z_{2} KK Template";
	hMassReconTemplateKK->SetLineColor(col1);
	hMassReconTemplateKK->SetLineWidth(2);
	hMassReconTemplateKK->SetTitle("");
	hMassReconTemplateKK->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconTemplateKK->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconTemplateKK->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconTemplateKK->GetXaxis()->SetMoreLogLabels();
	hMassReconTemplateKK->Draw("SAMES");
	leg_mass_recon->AddEntry(hMassReconTemplateKK, sName.c_str(), "l");
	
	sName = sMass + " GeV Z' SSM Template";
	hMassReconTemplateZP->SetLineColor(col2);
	hMassReconTemplateZP->SetLineWidth(2);
	hMassReconTemplateZP->SetTitle("");
	hMassReconTemplateZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconTemplateZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	hMassReconTemplateZP->Draw("SAMES");
	leg_mass_recon->AddEntry(hMassReconTemplateZP, sName.c_str(), "l");
	
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
	ymin = 0.5*getYmin(hMassReconTemplateZP);
	hMassReconTemplateZP->SetMinimum(ymin);
	hMassReconTemplateZP->SetMaximum(1.5*hMassReconTemplateZP->GetMaximum()); // !!!
	hMassReconTemplateZP->SetLineColor(col2);
	hMassReconTemplateZP->SetLineWidth(2);
	hMassReconTemplateZP->SetTitle("");
	hMassReconTemplateZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconTemplateZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconTemplateZP->GetXaxis()->SetMoreLogLabels(); 
	hMassReconTemplateZP->Draw();
	leg_compare->AddEntry(hMassReconTemplateZP, sName.c_str(), "l");
	
	
	sName = sMass + " GeV Z' SSM (#it{ATLAS} MC10 reconstructed)";
	hMassReconZP->SetLineColor(col5);
	//hMassReconZP->SetLineStyle(2);
	hMassReconZP->SetLineWidth(2);
	hMassReconZP->SetTitle("");
	hMassReconZP->SetXTitle("#hat{m}_{#mu#mu} GeV");
	hMassReconZP->SetYTitle(sYTitle.c_str());
	if(doLogx) hMassReconZP->GetXaxis()->SetMoreLogLabels(); 
	if(doLogx) hMassReconZP->GetXaxis()->SetMoreLogLabels(); 
	hMassReconZP->Draw("SAMES");
	leg_compare->AddEntry(hMassReconZP, sName.c_str(), "l");
	
	leg_compare->Draw("SAMES");
	pvtxt_compare->Draw("SAMES");
	
	pad_compare->cd();
	pad_compare->RedrawAxis();
	pad_compare->Update();
	
	
	
	cnv->Update();
	TString name = "plots/plot_weights_M" + (TString)sMass;
	cnv->SaveAs(name+".eps");
	cnv->SaveAs(name+".C");
	cnv->SaveAs(name+".root");
	cnv->SaveAs(name+".png");
	
	
	writeOutNtuples(dirNtuples);
	
	return 0;
}

#include "all.h"
#include "roofit.h"
// #include "RooAngular.h"
// #include "RooCollinsSoper.h"
#include "RooFBfalseIdentifyCS.h"

bool doAcc = true;

const double minMass = 120.;
const double maxMass = 1500.;

// const int             nlogicmassbins = 44;
// static const Double_t logicmassmin   = 75.;
// static const Double_t logicmassmax   = maxMass;
// const Double_t logicmassbins[nlogicmassbins+1] =
// {
// 75,85,95,105,120,
// 135,150,165,180,195,215,230,250,
// 270,290,310,330,350,375,400,
// 430,460,490,520,560,600,
// 640,680,720,760,800,850,900,
// 950,1000,1075,1150,1250,
// 1375,1500,1625,1750,
// 1875,2000,
// maxMass
// };
// const int             nlogicmassbins = 36;
// static const Double_t logicmassmin   = 75.;
// static const Double_t logicmassmax   = maxMass;
// const Double_t logicmassbins[nlogicmassbins+1] =
// {
// 75,85,95,105,120,
// 135,150,170,190,210,230,250,
// 280,310,340,370,400,
// 440,480,520,560,600,
// 650,700,750,800,
// 900,1000,
// 1125,1250,
// 1375,1500,
// 1625,1750,
// 1875,2000,
// maxMass
// };

// const int             nlogicmassbins = 15;
// static const Double_t logicmassmin   = 75.;
// static const Double_t logicmassmax   = maxMass;
// const Double_t logicmassbins[nlogicmassbins+1] =
// {
// 75,95,120,
// 180,250,
// 325,400,
// 500,600,
// 800,
// 1000,
// 1250,
// 1500,
// 1750,
// 2000,
// maxMass
// };

// const int      ndymassbins = 11;
// const Double_t dymassbins[ndymassbins+1] =
// {
// 75,120,250,400,600,800,1000,1250,1500,1750,2000,maxMass
// };
// TH1* hDYbins = new TH1("hDYbins","hDYbins",ndymassbins,dymassbins);	

static const Int_t    nlogmassbins = 6;
static const Double_t logmassmin   = minMass;
static const Double_t logmassmax   = maxMass;
static Double_t logmassbins[nlogmassbins+1];

static const Int_t    nlogfullimassbins = 60;
static const Double_t logfullimassmin   = minMass;
static const Double_t logfullimassmax   = maxMass;
static Double_t logfullimassbins[nlogfullimassbins+1];


int truth_entries = 0;
int recon_entries = 0;

double   costmin   = minCosTheta;
double   costmax   = maxCosTheta;
int      ncostbins = nCosThetaBins;

double   abscostmin   = minAbsCosTheta;
double   abscostmax   = maxAbsCosTheta;
int      nabscostbins = nAbsCosThetaBins;

double   yqmin   = minyQ;
double   yqmax   = maxyQ;
int      nyqbins = nyQbins;

double   absyqmin   = minabsyQ;
double   absyqmax   = maxabsyQ;
int      nabsyqbins = nabsyQbins;

double minA0 = -10.;
double maxA0 = +10.;
double minA4 = -10.; //-2.666;
double maxA4 = +10.; //+2.666;
double _A0 = 0.;
double _A4 = 0.;
struct fitpars
{
	double A0;
	double A4;
};
TRandom* randGen;
vector<fitpars> vInitialGuess;

bool truth_all_isValid;
vector<float>* truth_all_mc_pt;
vector<float>* truth_all_mc_m;
vector<float>* truth_all_mc_eta;
vector<float>* truth_all_mc_phi;
vector<int>*   truth_all_mc_status;
vector<int>*   truth_all_mc_barcode;
vector<int>*   truth_all_mc_pdgId;
vector<float>* truth_all_mc_charge;

vector<float>* truth_all_partons_mc_pt;
vector<float>* truth_all_partons_mc_m;
vector<float>* truth_all_partons_mc_eta;
vector<float>* truth_all_partons_mc_phi;
vector<int>*   truth_all_partons_mc_status;
vector<int>*   truth_all_partons_mc_barcode;
vector<int>*   truth_all_partons_mc_pdgId;
vector<float>* truth_all_partons_mc_charge;

bool recon_all_isValid;
vector<float>* recon_all_pt;
vector<float>* recon_all_m;
vector<float>* recon_all_eta;
vector<float>* recon_all_phi;
vector<float>* recon_all_charge;

TVector3*       tv3qa = new TVector3;
TLorentzVector* tlvqa = new TLorentzVector;
TLorentzVector* tlvqb = new TLorentzVector;
TLorentzVector* tlvqBoosted = new TLorentzVector;
TVector3*       tv3mua = new TVector3;
TVector3*       tv3b = new TVector3;
TLorentzVector* tlvmua = new TLorentzVector;
TLorentzVector* tlvmub = new TLorentzVector;
TLorentzVector* tlvmuaBoosted = new TLorentzVector;
TLorentzVector* tlvmubBoosted = new TLorentzVector;
TLorentzVector* tlvBoostVector = new TLorentzVector;
TVector3*       tv3BoostVector = new TVector3;
TMapTSd       wgtMap;
TMapTSP2TTREE treMap;
TTree* tree;
TString fName;
TString tName;

TH1D* hMass;
TH1D* hAfbFit;
TH1D* hAfbCount;
TH1D* hForward;
TH1D* hBackward;
TLegend* leg_mHat;
TText* txt;
vector<TGraphAsymmErrors*> gMpoissonErr;

TString sName = "Z^{0}";
TString sChannelFit   = "#gamma/Z^{0} [MC10b Reco']: A_{FB} fit";
TString sChannelCount = "#gamma/Z^{0} [MC10b Truth]: A_{FB} count";
TString sChannelMass  = "#gamma/Z^{0} [MC10b Reco']: Events";
Int_t fillStyle = 3003;
Int_t lineStyle = 2;
Int_t markerStyle = 24;
Int_t markerSize = 24;

TPaveText* pvtxt_lumi;
TPaveText* pvtxt_atlas;
TCanvas* cnvAfb;
TPad *pad_mHat;
TPad *pad_Afb;
TPad *pad_compare;

RooRealVar* cosThe; // the variable 
RooRealVar* cosTheAbs; // the variable 
RooRealVar* yQ;     // the variable 
RooRealVar* yQabs;  // the variable 
RooRealVar* weight; // the weight
RooRealVar* A0;     // the parameter to find
RooRealVar* A4;     // the parameter to find


RooAbsData* unbinnedDataSet; // Roo Data holder

vector<RooFitResult*> vFitResult;
vector<bool>          vbFitStatus;
vector<TH1D*> vhPyQ;
vector<TH1D*> vhPyQnumerator;
vector<TH1D*> vhPyQdenominator;
vector<TH1D*> vhAcceptance;
vector<TH1D*> vhAcceptanceNumerator;
vector<TH1D*> vhAcceptanceDenominator;
vector<TH1D*> vh1dSymmAcceptance;
vector<TH2D*> vh2dAcceptance;
vector<TH2D*> vh2dAcceptanceNumerator;
vector<TH2D*> vh2dAcceptanceDenominator;
vector<TH2D*> vh2dSymmAcceptance;

vector<TH1D*> vhEtaAcceptanceNumerator;
vector<TH1D*> vhEtaAcceptanceDenominator;
vector<TH1D*> vhEtaAcceptance;

RooAbsPdf* modelPdf; // the final model pdf
RooAbsPdf* sigPdf;   // the truth pdf
RooAbsPdf* detAccPdf;
RooAbsPdf* recEffPdf;  // will be taken from the reconstruction efficiency histogram
RooAbsPdf* trigEffPdf; // will be taken from the trigger efficiency histogram
RooAbsPdf* totEffPdf;  // will be the product of all the eff-like pdf's (=rec*trig*acc)

RooDataHist* rdhAcc;
RooHistPdf*  rhpdfAcc; // will be taken from the acceptance histogram


//////////////////////////////////
// flags to config the run
bool doLumiXSweights = false; //!!! // true if want to scale binned samples to 1 smooth sample and to scale MC to data luminosity. This affects mostly the errors
bool doBinomialError = false;
Int_t minEntries2Fit = 5;
void printRunConfig()
{
	cout << "//////////////////////////////////" << endl;
	cout << "// flags to config the run" << endl;
	cout << "bool doLumiXSweights = " << doLumiXSweights << "; // true if want to scale binned samples to 1 smooth sample and to scale MC to data luminosity. This affects mostly the errors " << endl;
	cout << "bool doBinomialError = " << doBinomialError << ";" << endl;
	cout << "Int_t minEntries2Fit = " << minEntries2Fit << ";" << endl;
	cout << "//////////////////////////////////" << endl;
}
//////////////////////////////////

void settree(TString fPath, TString name, Double_t N, Double_t sigma)
{
	_DEBUG("settree");
	
	TFile* f = new TFile(fPath,"READ");
	treMap.insert( make_pair(name, (TTree*)f->Get("truth/truth_tree")->Clone("")) );
	wgtMap.insert( make_pair(name, luminosity/(N/sigma)) );
	//delete f;
}

void settrees()
{
	_DEBUG("settrees");

	treMap.clear();
	wgtMap.clear();
	// settree("../data/mcLocalControl_DYmumu_75M120.root",    "mcLocalControl_DYmumu_75M120",    19996, 0.81705*nb2fb);
	settree("../data/mcLocalControl_DYmumu_120M250.root",   "mcLocalControl_DYmumu_120M250",   19999, 0.0086861*nb2fb);
	settree("../data/mcLocalControl_DYmumu_250M400.root",   "mcLocalControl_DYmumu_250M400",   19996, 0.00041431*nb2fb);
	settree("../data/mcLocalControl_DYmumu_400M600.root",   "mcLocalControl_DYmumu_400M600",   19993, 0.000067464*nb2fb);
	settree("../data/mcLocalControl_DYmumu_600M800.root",   "mcLocalControl_DYmumu_600M800",   15994, 0.000011168*nb2fb);
	settree("../data/mcLocalControl_DYmumu_800M1000.root",  "mcLocalControl_DYmumu_800M1000",  19992, 0.0000027277*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1000M1250.root", "mcLocalControl_DYmumu_1000M1250", 19995, 0.00000091646*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1250M1500.root", "mcLocalControl_DYmumu_1250M1500", 19993, 0.00000024942*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1500M1750.root", "mcLocalControl_DYmumu_1500M1750", 19997, 0.000000076876*nb2fb);
	settree("../data/mcLocalControl_DYmumu_1750M2000.root", "mcLocalControl_DYmumu_1750M2000", 19993, 0.000000026003*nb2fb);
	settree("../data/mcLocalControl_DYmumu_M2000.root",     "mcLocalControl_DYmumu_M2000",     19996, 0.000000015327*nb2fb);
}

void parseDYbinName(string name, Double_t& massbinlowedge, Double_t& massbinhighedge)
{
	string prefix = "mcLocalControl_DYmumu_";
	string::size_type loc = name.find("M");
	string high = name.substr(loc+1);
	string low = "";
	string chr = "";
	for(int i=(int)prefix.length() ; i<(int)loc ; i++)
	{
		chr = name[i];
		if(chr!="M") low+=chr;
	}
	if(low=="")
	{
		massbinlowedge  = logmassbins[nlogmassbins-1]; //2000.;
		massbinhighedge = logmassbins[nlogmassbins];   //maxMass;
		return;
	}
	massbinhighedge = validate_double(high);
	massbinlowedge  = validate_double(low);
}

void setbranches()
{
	_DEBUG("setbranches");

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
	
	recon_all_pt     = 0;
	recon_all_m      = 0;
	recon_all_eta    = 0;
	recon_all_phi    = 0;
	recon_all_charge = 0;

	tree->SetBranchAddress("truth_all_isValid", &truth_all_isValid);
	tree->SetBranchAddress("truth_all_mc_pt",   &truth_all_mc_pt);
	tree->SetBranchAddress("truth_all_mc_m",    &truth_all_mc_m);
	tree->SetBranchAddress("truth_all_mc_eta",  &truth_all_mc_eta);
	tree->SetBranchAddress("truth_all_mc_phi",  &truth_all_mc_phi);
	tree->SetBranchAddress("truth_all_mc_status",  &truth_all_mc_status);
	tree->SetBranchAddress("truth_all_mc_barcode", &truth_all_mc_barcode);
	tree->SetBranchAddress("truth_all_mc_pdgId",   &truth_all_mc_pdgId);
	tree->SetBranchAddress("truth_all_mc_charge",  &truth_all_mc_charge);
	
	tree->SetBranchAddress("truth_all_partons_mc_pt", &truth_all_partons_mc_pt);
	tree->SetBranchAddress("truth_all_partons_mc_m", &truth_all_partons_mc_m);
	tree->SetBranchAddress("truth_all_partons_mc_eta", &truth_all_partons_mc_eta);
	tree->SetBranchAddress("truth_all_partons_mc_phi", &truth_all_partons_mc_phi);
	tree->SetBranchAddress("truth_all_partons_mc_status", &truth_all_partons_mc_status);
	tree->SetBranchAddress("truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	tree->SetBranchAddress("truth_all_partons_mc_pdgId", &truth_all_partons_mc_pdgId);
	tree->SetBranchAddress("truth_all_partons_mc_charge", &truth_all_partons_mc_charge);
	
	tree->SetBranchAddress("recon_all_isValid", &recon_all_isValid);
	tree->SetBranchAddress("recon_all_pt",      &recon_all_pt);
	tree->SetBranchAddress("recon_all_m",       &recon_all_m);
	tree->SetBranchAddress("recon_all_eta",     &recon_all_eta);
	tree->SetBranchAddress("recon_all_phi",     &recon_all_phi);
	tree->SetBranchAddress("recon_all_charge",  &recon_all_charge);
	
	_DEBUG("successfully read mc branches");
}


double randomizeItialGuess(double min, double max)
{
	_DEBUG("randomizeItialGuess");
	return min + (max-min)*randGen->Uniform(); // Uniform(x1=0) returns a uniform deviate on the interval [0,x1].
}

double getAfb(double a, double b, bool validate)
{
	if(validate)
	{
		return (a>0.) ? 3.*b/(8.*a) : -999;
	}
	else return 3.*b/(8.*a);
	
	return -999.;
}

double getAfb(double a4)
{
	return 3./8.*a4;
}

double getAfb(double Nf, double Nb)
{
	double N=Nf+Nb;
	return (N>0.) ? (Nf-Nb)/N : -999;
}

double getAfbErr(double Afb, double N)
{
	return (N>0.) ? sqrt((1-Afb*Afb)/N) : -999;
}

double getAfbErr(double dA4)
{
	return (3./8.)*dA4;
}

void setLogBins(Int_t nbins, Double_t min, Double_t max, Double_t* xpoints)
{
	_DEBUG("setLogBins");

	Double_t logmin  = log10(min);
	Double_t logmax  = log10(max);
	Double_t logbinwidth = (Double_t)( (logmax-logmin)/(Double_t)nbins );
	xpoints[0] = min;
	for(Int_t i=1 ; i<=nbins ; i++) xpoints[i] = TMath::Power( 10,(logmin + i*logbinwidth) );
}

double getMassBinCenter(int massBin)
{
	return logmassbins[massBin-1]+(logmassbins[massBin]-logmassbins[massBin-1])/2.;
}

double getMassBinLowEdge(int massBin)
{
	_DEBUG("getMassBinLowEdge");
	return logmassbins[massBin-1];
}

double getMassBinHighEdge(int massBin)
{
	_DEBUG("getMassBinHighEdge");
	return logmassbins[massBin];
}

void AfbCount()
{
	for(Int_t b=1 ; b<=hAfbCount->GetNbinsX() ; b++)
	{	
		Double_t Nf = hForward->GetBinContent(b);
		Double_t Nb = hBackward->GetBinContent(b);
		Double_t N = Nf+Nb;
		
		if(N<=0.) continue;
		Double_t AFB = (Nf-Nb)/N;
		Double_t dAFB = TMath::Sqrt( (1.-AFB*AFB)/N );
		_INFO("Mass bin "+_s(b)+"  ->  Count: Afb="+_s(AFB)+"+-"+_s(dAFB));
		hAfbCount->SetBinContent(b,AFB);
		hAfbCount->SetBinError(b,dAFB);
	}
}

void correctHisto(TH1D* h)
{
	if(h->GetBinContent(0)>0.)                h->SetBinContent(0,0.);
	if(h->GetBinContent(h->GetNbinsX()+1)>0.) h->SetBinContent(h->GetNbinsX()+1,0.);
	for(Int_t b=1 ; b<=h->GetNbinsX() ; b++)
	{
		if(h->GetBinContent(b)<=0.) h->SetBinContent(b,1.e-30);
	}
}

void symmetrizeHisto(TH2D* hAbs, TH2D* hSymm)
{
	Int_t Nx = hAbs->GetNbinsX();
	Int_t Ny = hAbs->GetNbinsY();

	for(Int_t bx=1 ; bx<=Nx ; bx++)
	{
		for(Int_t by=1 ; by<=Ny ; by++)
		{
			// Double_t val = (hAbs->GetBinContent(bx,by)>0.) ? hAbs->GetBinContent(bx,by) : 1.e-30;
			Double_t val = hAbs->GetBinContent(bx,by);
			Double_t err = hAbs->GetBinError(bx,by);

			Int_t x1 = Nx + bx;			
			Int_t x2 = Nx + 1 - bx;
			Int_t y1 = Ny + by;
			Int_t y2 = Ny + 1 - by;

			hSymm->SetBinContent(x1,y1,val);
			hSymm->SetBinContent(x1,y2,val);
			hSymm->SetBinContent(x2,y1,val);
			hSymm->SetBinContent(x2,y2,val);
			
			hSymm->SetBinError(x1,y1,err);
			hSymm->SetBinError(x1,y2,err);
			hSymm->SetBinError(x2,y1,err);
			hSymm->SetBinError(x2,y2,err);
		}
	}
}

void symmetrizeHisto(TH1D* hAbs, TH1D* hSymm)
{
	Int_t Nx = hAbs->GetNbinsX();

	for(Int_t bx=1 ; bx<=Nx ; bx++)
	{
		// Double_t val = (hAbs->GetBinContent(bx)>0.) ? hAbs->GetBinContent(bx) : 1.e-30;
		Double_t val = hAbs->GetBinContent(bx);
		Double_t err = hAbs->GetBinError(bx);
		
		Int_t x1 = Nx + bx;			
		Int_t x2 = Nx + 1 - bx;

		hSymm->SetBinContent(x1,val);
		hSymm->SetBinContent(x2,val);
		
		hSymm->SetBinError(x1,err);
		hSymm->SetBinError(x2,err);
	}
}

void init(int massBin)
{
	_DEBUG("init");
	
	double iMassMin = getMassBinLowEdge(massBin);
	double iMassMax = getMassBinHighEdge(massBin);
	
	TString sMassBin = (TString)_s(massBin);
	string sMassMin = _s((double)iMassMin);
	string sMassMax = _s((double)iMassMax);
	TString sTitle = "Mass-bin[" + sMassBin + "] " + sMassMin + "#rightarrow" + sMassMax + " GeV";

	// cosThe = new RooRealVar("cosTheta","cos#theta*",costmin,costmax);
	// cosThe->setRange("range_cosThe",costmin,costmax);
	// cosThe->setBins(ncostbins);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	cosThe = new RooRealVar("cosTheta","cos#theta*",-1.*abscostmax,abscostmax);
	cosThe->setRange("range_cosThe",-1.*abscostmax,abscostmax);
	//cosThe->setBins(2*nabscostbins); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	cosTheAbs = new RooRealVar("cosThetaAbs","|cos#theta*|",abscostmin,abscostmax);
	cosTheAbs->setRange("range_cosTheAbs",abscostmin,abscostmax);
	// cosTheAbs->setBins(nabscostbins);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	// yQ = new RooRealVar("yQ","y_{Q}",yqmin,yqmax);
	// yQ->setRange("range_yQ",yqmin,yqmax);
	// // yQ->setBins(nyqbins);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	yQ = new RooRealVar("yQ","y_{Q}",-1.*absyqmax,absyqmax);
	yQ->setRange("range_yQ",-1.*absyqmax,absyqmax);
	// yQ->setBins(nabsyqbins);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	yQabs = new RooRealVar("yQabs","|y_{Q}|",absyqmin,absyqmax);
	yQabs->setRange("range_yQabs",absyqmin,absyqmax);
	// yQabs->setBins(nabsyqbins);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	weight = new RooRealVar("weight","weight",0.,1e10);

	_A0 = randomizeItialGuess(minA0,maxA0);
	_A4 = randomizeItialGuess(minA4,maxA4);
	fitpars fp;
	fp.A0 = _A0;
	fp.A4 = _A4;
	vInitialGuess.push_back(fp);
	
	A0 = new RooRealVar("A0","A0",_A0,minA0,maxA0);
	A4 = new RooRealVar("A4","A4",_A4,minA4,maxA4);
	A0->setError(0.0001);
	A4->setError(0.0001);
	
	// A0 = new RooRealVar("A0","A0",0.);
	// A0->setConstant(kTRUE);
	// A4 = new RooRealVar("A4","A4",_A4,minA4,maxA4);
	// A4->setError(0.0001);
	
	if(doAcc)
	{
		// if(doLumiXSweights) unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*cosTheAbs,*yQ,*yQabs,*weight),WeightVar(weight->GetName()));
		// else                unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*cosTheAbs,*yQ,*yQabs));
		
		if(doLumiXSweights) unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*yQ,*weight),WeightVar(weight->GetName()));
		else                unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*yQ));
	}
	else
	{
		if(doLumiXSweights) unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*yQ,*weight),WeightVar(weight->GetName()));
		else                unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*yQ));
	}
}

void reset()
{	
	delete cosThe;
	delete cosTheAbs;
	delete yQ;
	delete yQabs;
	delete weight;
	delete A0;
	delete A4;
	
	delete unbinnedDataSet;
	delete modelPdf;
	delete sigPdf;
	delete rdhAcc;
	delete rhpdfAcc;
	delete detAccPdf;
	//if(detAccPdf)       delete detAccPdf;
}

Int_t loop(int massBin)
{
	_DEBUG("loop");
	Int_t    N = 0;
	Double_t W = 1.;
	
	Double_t lowmasscut  = getMassBinLowEdge(massBin);
	Double_t highmasscut = getMassBinHighEdge(massBin);
	
	recon_entries = 0;
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		tree = it->second;
		setbranches();
		N = tree->GetEntriesFast();
		W = wgtMap[it->first];
		_INFO("name = "+(string)it->first+" -> N(all)="+_s(N));
		
		float YQ = -999.;
		float mHat = -999.;
		float ca = -999.;
		float cb = -999.;
		float cost = -999.;
		
		truth_entries = 0;
		bool isTruth = true;
		bool isRecon = true;
		
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			
			isTruth = true;
			isRecon = true;
			
			/////////////////////////////
			/// truth ///////////////////
			/////////////////////////////
			if(!truth_all_isValid) continue;
			
			int imuontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
			int iamuontru = (imuontru==0) ? 1 : 0;
			tlvmua->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),truth_all_mc_eta->at(imuontru),truth_all_mc_phi->at(imuontru),truth_all_mc_m->at(imuontru));
			tlvmub->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru),truth_all_mc_eta->at(iamuontru),truth_all_mc_phi->at(iamuontru),truth_all_mc_m->at(iamuontru));
			YQ   = ySystem(tlvmua,tlvmub);
			mHat = imass(tlvmua,tlvmub);
			
			// Double_t massbinlowedge  = 0.;
			// Double_t massbinhighedge = 0.;
			// parseDYbinName((string)it->first,massbinlowedge,massbinhighedge);
			// if(mHat<massbinlowedge || mHat>massbinhighedge) isTruth = false; // in this mass bin, do not take events from different DY mass bins
			if(mHat<lowmasscut || mHat>highmasscut) isTruth = false; // to get the events in the relevant mass bin
			if(YQ>+2.5 || YQ<-2.5)                  isTruth = false; // to reject events that have no P(yQ) calculated
			
			if(isTruth)
			{
				ca   = truth_all_mc_charge->at(imuontru);
				cb   = truth_all_mc_charge->at(iamuontru);
				cost = cosThetaCollinsSoper(tlvmua,ca,tlvmub,cb);
				// double cost = cosThetaBoost(tlvmua,ca,tlvmub,cb);
				
				vhAcceptanceDenominator[massBin-1]->Fill(fabs(cost),W);
				vh2dAcceptanceDenominator[massBin-1]->Fill(fabs(cost),fabs(YQ),W);
				vhEtaAcceptanceDenominator[massBin-1]->Fill(truth_all_mc_eta->at(imuontru),W);
				
				int iquark = (truth_all_partons_mc_pdgId->at(0)>0) ? 0 : 1;
				int iaquark = (iquark==0) ? 1 : 0;
				tlvqa->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iquark), truth_all_partons_mc_eta->at(iquark), truth_all_partons_mc_phi->at(iquark),truth_all_partons_mc_m->at(iquark));
				tlvqb->SetPtEtaPhiM(truth_all_partons_mc_pt->at(iaquark), truth_all_partons_mc_eta->at(iaquark), truth_all_partons_mc_phi->at(iaquark),truth_all_partons_mc_m->at(iaquark));
				
				// boost to the qqbar system rest frame
				// tlvqBoosted   = Boost(tlvqa,tlvqb,tlvqa); 
				// tlvmuaBoosted = Boost(tlvqa,tlvqb,tlvmua);
				
				// boost to the mu+mu- system rest frame
				tlvqBoosted   = Boost(tlvmua,tlvmub,tlvqa);
				tlvmuaBoosted = Boost(tlvmua,tlvmub,tlvmua);
				
				tv3qa->SetPtEtaPhi(tlvqBoosted->Pt(),tlvqBoosted->Eta(),tlvqBoosted->Phi());
				tv3mua->SetPtEtaPhi(tlvmuaBoosted->Pt(),tlvmuaBoosted->Eta(),tlvmuaBoosted->Phi());
				double costheta_mutru_quark = tv3qa->Dot((*tv3mua))/(tv3qa->Mag()*tv3mua->Mag());
				
				(*tlvBoostVector) = (*tlvqa)+(*tlvqb);
				(*tv3BoostVector) = tlvBoostVector->BoostVector();
				double cosalpha_beta_quark = tv3qa->Dot((*tv3BoostVector))/(tv3qa->Mag()*tv3BoostVector->Mag());
				int currentMassBin = hForward->FindBin(mHat);
				if(currentMassBin!=massBin) _WARNING("currentMassBin!=massBin  ->  "+_s(currentMassBin)+":"+_s(massBin));
				if(cosalpha_beta_quark<=0.)
				{
					vhPyQnumerator[massBin-1]->Fill(YQ,W);
					vhPyQ[massBin-1]->Fill(YQ,W);
				}
				vhPyQdenominator[massBin-1]->Fill(YQ,W);
				
				if(doLumiXSweights)
				{
					if(costheta_mutru_quark>=0.) hForward->Fill(mHat,W);
					else                         hBackward->Fill(mHat,W);
				}
				else
				{
					if(costheta_mutru_quark>=0.) hForward->Fill(mHat);
					else                         hBackward->Fill(mHat);
				}
				
				truth_entries++;
				
				if(!doAcc)
				{
					/////////////////////////////
					/// fill the dataset ////////
					/////////////////////////////
					*yQ = YQ;
					*cosThe = cost;
					*weight = W;
					hMass->Fill(mHat,W);					
					if(doLumiXSweights) unbinnedDataSet->add(RooArgSet(*cosThe,*yQ,*weight),W); // WEIGHTED
					else                unbinnedDataSet->add(RooArgSet(*cosThe,*yQ));           // UNWEIGHTED
				}
			}
			
			
			
			/////////////////////////////
			/// reconstructed ///////////
			/////////////////////////////
			if(!recon_all_isValid) continue;
			
			int imuonrec  = (recon_all_charge->at(0)<0) ? 0 : 1;
			int iamuonrec = (imuonrec==0) ? 1 : 0;
			tlvmua->SetPtEtaPhiM(recon_all_pt->at(imuonrec),  recon_all_eta->at(imuonrec),  recon_all_phi->at(imuonrec),  recon_all_m->at(imuonrec));
			tlvmub->SetPtEtaPhiM(recon_all_pt->at(iamuonrec), recon_all_eta->at(iamuonrec), recon_all_phi->at(iamuonrec), recon_all_m->at(iamuonrec));
			YQ   = ySystem(tlvmua,tlvmub);
			mHat = imass(tlvmua,tlvmub);
			
			if(mHat<lowmasscut || mHat>highmasscut) isRecon = false; // to get the events in the relevant mass bin
			if(YQ>+2.5 || YQ<-2.5)                  isRecon = false; // to reject events that have no P(yQ) calculated
			
			if(isRecon)
			{
				ca   = recon_all_charge->at(imuonrec);
				cb   = recon_all_charge->at(iamuonrec);
				cost = cosThetaCollinsSoper(tlvmua,ca,tlvmub,cb);
				// double cost = cosThetaBoost(tlvmua,ca,tlvmub,cb);
				
				if(fabs(cost)>1.) _WARNING("cos(theta)="+_s(cost));
				
				vhAcceptance[massBin-1]->Fill(fabs(cost),W);
				vh2dAcceptance[massBin-1]->Fill(fabs(cost),fabs(YQ),W);
				vhEtaAcceptance[massBin-1]->Fill(recon_all_eta->at(imuonrec),W);
				
				vhAcceptanceNumerator[massBin-1]->Fill(fabs(cost),W);
				vh2dAcceptanceNumerator[massBin-1]->Fill(fabs(cost),fabs(YQ),W);
				vhEtaAcceptanceNumerator[massBin-1]->Fill(recon_all_eta->at(imuonrec),W);
				
				recon_entries++;
				
				if(doAcc)
				{
					/////////////////////////////
					/// fill the dataset ////////
					/////////////////////////////
					*yQ        = YQ;
					*yQabs     = fabs(YQ);
					*cosThe    = cost;
					*cosTheAbs = fabs(cost);
					*weight    = W;
					hMass->Fill(mHat,W);
					
					// if(doLumiXSweights) unbinnedDataSet->add(RooArgSet(*cosThe,*cosTheAbs,*yQ,*weight),W); // WEIGHTED
					// else                unbinnedDataSet->add(RooArgSet(*cosThe,*cosTheAbs,*yQ));           // UNWEIGHTED
					
					// if(doLumiXSweights) unbinnedDataSet->add(RooArgSet(*cosThe,*cosTheAbs,*yQ,*yQabs,*weight),W); // WEIGHTED
					// else                unbinnedDataSet->add(RooArgSet(*cosThe,*cosTheAbs,*yQ,*yQabs));           // UNWEIGHTED
					
					if(doLumiXSweights) unbinnedDataSet->add(RooArgSet(*cosThe,*yQ,*weight),W); // WEIGHTED
					else                unbinnedDataSet->add(RooArgSet(*cosThe,*yQ));           // UNWEIGHTED
				}
			}
		}
		_INFO("truth_entries = "+_s(truth_entries));
		_INFO("recon_entries = "+_s(recon_entries));
	}
	
	vhPyQ[massBin-1]->Divide(vhPyQdenominator[massBin-1]);
	vhAcceptance[massBin-1]->Divide(vhAcceptanceDenominator[massBin-1]);
	vh2dAcceptance[massBin-1]->Divide(vh2dAcceptanceDenominator[massBin-1]);
	vhEtaAcceptance[massBin-1]->Divide(vhEtaAcceptanceDenominator[massBin-1]);
	
	symmetrizeHisto(vh2dAcceptance[massBin-1],vh2dSymmAcceptance[massBin-1]);
	symmetrizeHisto(vhAcceptance[massBin-1],vh1dSymmAcceptance[massBin-1]);
	
	sigPdf    = new RooFBfalseIdentifyCS("SignalPdf", "SignalPdf", *cosThe,*yQ,*A0,*A4,*vhPyQ[massBin-1]);
	
	// rdhAcc    = new RooDataHist("rdhAcc","rdhAcc",RooArgSet(*cosTheAbs),vhAcceptance[massBin-1]);
	// rhpdfAcc  = new RooHistPdf("rhpdfAcc","rhpdfAcc",RooArgSet(*cosTheAbs),*rdhAcc,2);
	
	// rdhAcc    = new RooDataHist("rdhAcc","rdhAcc",RooArgSet(*cosTheAbs,*yQabs),vh2dAcceptance[massBin-1]);
	// rhpdfAcc  = new RooHistPdf("rhpdfAcc","rhpdfAcc",RooArgSet(*cosTheAbs,*yQabs),*rdhAcc,2);
	
	// rdhAcc    = new RooDataHist("rdhAcc","rdhAcc",RooArgSet(*cosThe,*yQ),vh2dSymmAcceptance[massBin-1]);
	// rhpdfAcc  = new RooHistPdf("rhpdfAcc","rhpdfAcc",RooArgSet(*cosThe,*yQ),*rdhAcc,2);
	
	rdhAcc    = new RooDataHist("rdhAcc","rdhAcc",RooArgSet(*cosThe),Import(*vh1dSymmAcceptance[massBin-1])); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//rdhAcc    = new RooDataHist("rdhAcc","rdhAcc",RooArgSet(*cosThe),vh1dSymmAcceptance[massBin-1]);
	rhpdfAcc  = new RooHistPdf("rhpdfAcc","rhpdfAcc",RooArgSet(*cosThe),*rdhAcc,2); // the best interpulation is of order 2.
	
	detAccPdf = (RooAbsPdf*)rhpdfAcc->Clone("");
	
	// if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",RooArgSet(*sigPdf),Conditional(*detAccPdf,*cosTheAbs));
	
	// if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",RooArgSet(*sigPdf),Conditional(*detAccPdf,*cosTheAbs,*yQabs));
	
	// if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",RooArgSet(*sigPdf),Conditional(*detAccPdf,*yQ));
	
	// if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",RooArgSet(*sigPdf),Conditional(*detAccPdf,RooArgSet(*cosThe,*yQ)));
	
	// if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",RooArgSet(*sigPdf),Conditional(*detAccPdf,RooArgSet(*yQ)));
	
	// if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",RooArgSet(*sigPdf),Conditional(*detAccPdf,RooArgSet(*cosThe,*yQ)));
	
	if(doAcc) modelPdf = new RooProdPdf("model","truPdf*accPdf",*sigPdf,*detAccPdf);
	
	else      modelPdf = (RooAbsPdf*)sigPdf->Clone("");
	
	return recon_entries;
}

bool minuitStatus(TMinuit* m) 
{
	_DEBUG("minuitStatus");
	if (!m) return false;

	TString stat = gMinuit->fCstatu;
	_INFO("Minuit: "+(string)stat+". ");
	if ( stat.Contains("SUCCESSFUL")  || stat.Contains("CONVERGED")  ||  stat.Contains("OK") ) return true;

	return false;
}

RooFitResult* fit()
{
	_DEBUG("fit");
	TMinuit* gFit(0);
	
	_A0 = 0.;
	_A4 = 0.;
	
	const RooArgSet* fitParsInital;
	fitParsInital = modelPdf->getParameters(unbinnedDataSet,false);
	RooRealVar* x = (RooRealVar*)fitParsInital->find("A0");
	RooRealVar* y = (RooRealVar*)fitParsInital->find("A4");
	if(x) *x = 0.;
	if(y) *y = 0.;
	delete fitParsInital;
	
	RooFitResult* fitresult;
	if(!unbinnedDataSet->isWeighted()  &&  doLumiXSweights) _WARNING("$$$$$$$$$$$ The dataset is unweighted $$$$$$$$$$$");
	if(doAcc)
	{	
		// if(doLumiXSweights) fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),SumW2Error(kTRUE),NumCPU(8),ConditionalObservables(RooArgSet(*cosTheAbs,*yQ)));
		// else                fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),NumCPU(8),ConditionalObservables(RooArgSet(*cosTheAbs,*yQ)));
		
		// if(doLumiXSweights) fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),SumW2Error(kTRUE),NumCPU(8),ConditionalObservables(RooArgSet(*cosTheAbs,*yQabs,*yQ)));
		// else                fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),NumCPU(8),ConditionalObservables(RooArgSet(*cosTheAbs,*yQabs,*yQ)));
		
		if(doLumiXSweights) fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),SumW2Error(kTRUE),NumCPU(8),ConditionalObservables(RooArgSet(*yQ)));
		else                fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),NumCPU(8),ConditionalObservables(RooArgSet(*yQ)));
	}
	else
	{
		if(doLumiXSweights) fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),SumW2Error(kTRUE),NumCPU(8),ConditionalObservables(*yQ));
		else                fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),NumCPU(8),ConditionalObservables(*yQ));
	}
	gFit = gMinuit;
	
	vbFitStatus.push_back( minuitStatus(gFit) );
	
	fitresult->Print("v");
	
	return fitresult;
}

void fixTitleStyle()
{
	gStyle->SetTitleX(0.); //title X location 
	gStyle->SetTitleY(0.94); //title Y location 
	gStyle->SetTitleW(0.3); //title width 
	gStyle->SetTitleH(0.05); //title height
	gStyle->SetTitleBorderSize(0);
}

void resetTitleStyle()
{
	gStyle->SetTitleX(0.25); //title X location 
	gStyle->SetTitleY(0.94); //title Y location 
	gStyle->SetTitleW(0.5); //title width 
	gStyle->SetTitleH(0.05); //title height
	gStyle->SetTitleBorderSize(0);
}

void plot(int massbin)
{
	_DEBUG("plot");
	
	TCanvas* cnv = new TCanvas("cnv_"+(TString)_s(massbin),"cnv_"+(TString)_s(massbin), 600,400);
	cnv->SetFillColor(kWhite);
	cnv->Draw();
	cnv->cd();
	
	TString sMassBin = (TString)_s(massbin);
	
	////////////////////////
	fixTitleStyle(); ///////
	////////////////////////
	
	RooPlot* cosThetaFrame = cosThe->frame(Name("cosThetaFrame"), Title("DYmumu"));
	if(!unbinnedDataSet->isWeighted()  &&  doLumiXSweights) _WARNING("$$$$$$$$$$$ The dataset is unweighted $$$$$$$$$$$");
	if(doLumiXSweights) unbinnedDataSet->plotOn(cosThetaFrame,Name("cos#theta*"),XErrorSize(0),MarkerSize(0.3),Binning(2*nabscostbins),DataError(RooAbsData::SumW2),NumCPU(8));
	else                unbinnedDataSet->plotOn(cosThetaFrame,Name("cos#theta*"),XErrorSize(0),MarkerSize(0.3),Binning(2*nabscostbins),NumCPU(8));
	
	// if(doAcc) modelPdf->plotOn(cosThetaFrame,ProjWData(RooArgSet(*cosTheAbs,*yQ),*unbinnedDataSet),LineWidth(1),LineColor(cPdf),NormRange("range_cosThe"),NumCPU(8));
	
	// if(doAcc) modelPdf->plotOn(cosThetaFrame,ProjWData(RooArgSet(*cosTheAbs,*yQabs,*yQ),*unbinnedDataSet),LineWidth(1),LineColor(cPdf),NormRange("range_cosThe"),NumCPU(8));

	if(doAcc) modelPdf->plotOn(cosThetaFrame,ProjWData(RooArgSet(*yQ),*unbinnedDataSet),LineWidth(1),LineColor(cPdf),NormRange("range_cosThe"),NumCPU(8));
	
	else      modelPdf->plotOn(cosThetaFrame,ProjWData(*yQ,*unbinnedDataSet),LineWidth(1),LineColor(cPdf),NormRange("range_cosThe"),NumCPU(8));
	
	modelPdf->paramOn(cosThetaFrame,Layout(0.4,0.75,1), Format("NEU", AutoPrecision(1)));
	cosThetaFrame->getAttText()->SetTextSize(0.05);
	cnv->SetLeftMargin(0.2);
	cosThetaFrame->SetTitleOffset(2,"Y");
	cosThetaFrame->Draw();
	
	cnv->Update();
	cnv->SaveAs("fitplots/truth_2d_FitMassBin_" + sMassBin + ".root");
	cnv->SaveAs("fitplots/truth_2d_FitMassBin_" + sMassBin + ".C");
	cnv->SaveAs("fitplots/truth_2d_FitMassBin_" + sMassBin + ".eps");
	cnv->SaveAs("fitplots/truth_2d_FitMassBin_" + sMassBin + ".ps");
	cnv->SaveAs("fitplots/truth_2d_FitMassBin_" + sMassBin + ".pdf");
	cnv->SaveAs("fitplots/truth_2d_FitMassBin_" + sMassBin + ".png");
	
	////////////////////////
	resetTitleStyle(); /////
	////////////////////////
	
	delete cnv;
}

void getFit()
{
	_DEBUG("getFit");
	vFitResult.push_back( fit() );
}


void drawAfb()
{
	_DEBUG("drawAfb");

	cnvAfb->cd();
	pad_mHat->Draw();
	pad_mHat->cd();

	hMass->SetMaximum(1.5*hMass->GetMaximum());
	hMass->SetMinimum((hMass->GetMinimum()<=0) ? 1. : 0.5*hMass->GetMinimum());
	hMass->GetXaxis()->SetMoreLogLabels();
	hMass->GetXaxis()->SetNoExponent();
	hMass->Draw();

	cnvAfb->cd();

	pad_Afb->Draw();
	pad_Afb->cd();
	hAfbFit->GetYaxis()->SetRangeUser(-1.,+1.);
	// hAfbFit->Draw("E5 Y+");
	hAfbFit->Draw("e1x1 Y+");
	hAfbFit->GetXaxis()->SetMoreLogLabels(); 
	hAfbFit->GetXaxis()->SetNoExponent();
	// hAfbCounthAfbCount->Draw("E5 Y+ SAMES");
	hAfbCount->Draw("e1x1 Y+ SAMES");
	hAfbCount->GetXaxis()->SetMoreLogLabels(); 
	hAfbCount->GetXaxis()->SetNoExponent();

	TLine* line = new TLine(logmassmin,0.,logmassmax,0.);
	line->SetLineStyle(2);
	line->Draw("SAMES");
	
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlas->Draw("SAMES");
	leg_mHat->Draw("SAMES");
	//pad_Afb->RedrawAxis();
	
	cnvAfb->cd();
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();
	cnvAfb->Update();
	
	cnvAfb->SaveAs("fitplots/truth_2d_FitAfb.root");
	cnvAfb->SaveAs("fitplots/truth_2d_FitAfb.C");
	cnvAfb->SaveAs("fitplots/truth_2d_FitAfb.eps");
	cnvAfb->SaveAs("fitplots/truth_2d_FitAfb.ps");
	cnvAfb->SaveAs("fitplots/truth_2d_FitAfb.pdf");
	cnvAfb->SaveAs("fitplots/truth_2d_FitAfb.png");
}

void drawHistos(int massBin)
{
	TString sMassBin = (TString)_s(massBin);
	
	TCanvas* cnvPyQ = new TCanvas("c_"+sMassBin, "", 600,400);
	cnvPyQ->SetFillColor(0);
	
	TCanvas* cnvAcc = new TCanvas("cAcc_"+sMassBin, "", 600,400);
	cnvAcc->SetFillColor(0);
	
	TCanvas* cnv1dSymmAcc = new TCanvas("c1dSymmAcc_"+sMassBin, "", 600,400);
	cnv1dSymmAcc->SetFillColor(0);
	
	TCanvas* cnv2dAcc = new TCanvas("c2dAcc_"+sMassBin, "", 600,400);
	cnv2dAcc->SetFillColor(0);
	
	TCanvas* cnv2dSymmAcc = new TCanvas("c2dSymmAcc_"+sMassBin, "", 600,400);
	cnv2dSymmAcc->SetFillColor(0);
	
	TCanvas* cnvEtaAcc = new TCanvas("cEtaAcc_"+sMassBin, "", 600,400);
	cnvEtaAcc->SetFillColor(0);
	
	TPaveText* pvtxt_massbinname = new TPaveText(0.3277592,0.8056995,0.4916388,0.9002591,"brNDC");
	pvtxt_massbinname->SetFillColor(0);
	pvtxt_massbinname->SetTextFont(42);
	txt = pvtxt_massbinname->AddText("m_{#mu#mu}: "+(TString)_s(logmassbins[massBin-1])+"#rightarrow"+(TString)_s(logmassbins[massBin])+" GeV");
	
	/// P(yQ)
	cnvPyQ->cd();
	cnvPyQ->Draw();
	vhPyQ[massBin-1]->SetMinimum(0.);
	vhPyQ[massBin-1]->SetMaximum(0.65);
	vhPyQ[massBin-1]->SetMarkerStyle(24);
	vhPyQ[massBin-1]->SetMarkerSize(1);
	vhPyQ[massBin-1]->Draw("e1x1");
	pvtxt_massbinname->Draw("SAMES");
	cnvPyQ->SaveAs("fitplots/PyQ_"+sMassBin+".png");
	cnvPyQ->SaveAs("fitplots/PyQ_"+sMassBin+".eps");
	cnvPyQ->SaveAs("fitplots/PyQ_"+sMassBin+".pdf");
	cnvPyQ->SaveAs("fitplots/PyQ_"+sMassBin+".ps");
	cnvPyQ->SaveAs("fitplots/PyQ_"+sMassBin+".root");
	cnvPyQ->SaveAs("fitplots/PyQ_"+sMassBin+".C");
	
	/// Acceptance
	cnvAcc->cd();
	cnvAcc->Draw();
	vhAcceptance[massBin-1]->SetMinimum(0.);
	vhAcceptance[massBin-1]->SetMaximum(1.);
	vhAcceptance[massBin-1]->SetMarkerStyle(24);
	vhAcceptance[massBin-1]->SetMarkerSize(1);
	vhAcceptance[massBin-1]->Draw("e1x1");
	pvtxt_massbinname->Draw("SAMES");
	cnvAcc->SaveAs("fitplots/Acceptance_"+sMassBin+".png");
	cnvAcc->SaveAs("fitplots/Acceptance_"+sMassBin+".eps");
	cnvAcc->SaveAs("fitplots/Acceptance_"+sMassBin+".pdf");
	cnvAcc->SaveAs("fitplots/Acceptance_"+sMassBin+".ps");
	cnvAcc->SaveAs("fitplots/Acceptance_"+sMassBin+".root");
	cnvAcc->SaveAs("fitplots/Acceptance_"+sMassBin+".C");
	
	/// 1d Symmetrized Acceptance
	cnv1dSymmAcc->cd();
	cnv1dSymmAcc->Draw();
	vh1dSymmAcceptance[massBin-1]->SetMinimum(0.);
	vh1dSymmAcceptance[massBin-1]->SetMaximum(1.);
	vh1dSymmAcceptance[massBin-1]->SetMarkerStyle(24);
	vh1dSymmAcceptance[massBin-1]->SetMarkerSize(1);
	vh1dSymmAcceptance[massBin-1]->Draw("e1x1");
	pvtxt_massbinname->Draw("SAMES");
	cnv1dSymmAcc->SaveAs("fitplots/AcceptanceSymm1d_"+sMassBin+".png");
	cnv1dSymmAcc->SaveAs("fitplots/AcceptanceSymm1d_"+sMassBin+".eps");
	cnv1dSymmAcc->SaveAs("fitplots/AcceptanceSymm1d_"+sMassBin+".pdf");
	cnv1dSymmAcc->SaveAs("fitplots/AcceptanceSymm1d_"+sMassBin+".ps");
	cnv1dSymmAcc->SaveAs("fitplots/AcceptanceSymm1d_"+sMassBin+".root");
	cnv1dSymmAcc->SaveAs("fitplots/AcceptanceSymm1d_"+sMassBin+".C");
	
	/// 2d Acceptance
	cnv2dAcc->cd();
	cnv2dAcc->Draw();
	vh2dAcceptance[massBin-1]->SetMinimum(0.);
	vh2dAcceptance[massBin-1]->SetMaximum(1.);
	vh2dAcceptance[massBin-1]->Draw("COLZ");
	pvtxt_massbinname->Draw("SAMES");
	cnv2dAcc->SaveAs("fitplots/Acceptance2d_"+sMassBin+".png");
	cnv2dAcc->SaveAs("fitplots/Acceptance2d_"+sMassBin+".eps");
	cnv2dAcc->SaveAs("fitplots/Acceptance2d_"+sMassBin+".pdf");
	cnv2dAcc->SaveAs("fitplots/Acceptance2d_"+sMassBin+".ps");
	cnv2dAcc->SaveAs("fitplots/Acceptance2d_"+sMassBin+".root");
	cnv2dAcc->SaveAs("fitplots/Acceptance2d_"+sMassBin+".C");
	
	/// 2d Symmetrized Acceptance
	cnv2dSymmAcc->cd();
	cnv2dSymmAcc->Draw();
	vh2dSymmAcceptance[massBin-1]->SetMinimum(0.);
	vh2dSymmAcceptance[massBin-1]->SetMaximum(1.);
	vh2dSymmAcceptance[massBin-1]->Draw("COLZ");
	pvtxt_massbinname->Draw("SAMES");
	cnv2dSymmAcc->SaveAs("fitplots/AcceptanceSymm2d_"+sMassBin+".png");
	cnv2dSymmAcc->SaveAs("fitplots/AcceptanceSymm2d_"+sMassBin+".eps");
	cnv2dSymmAcc->SaveAs("fitplots/AcceptanceSymm2d_"+sMassBin+".pdf");
	cnv2dSymmAcc->SaveAs("fitplots/AcceptanceSymm2d_"+sMassBin+".ps");
	cnv2dSymmAcc->SaveAs("fitplots/AcceptanceSymm2d_"+sMassBin+".root");
	cnv2dSymmAcc->SaveAs("fitplots/AcceptanceSymm2d_"+sMassBin+".C");
	
	/// Eta(mu) Acceptance
	cnvEtaAcc->cd();
	cnvEtaAcc->Draw();
	vhEtaAcceptance[massBin-1]->SetMinimum(0.);
	vhEtaAcceptance[massBin-1]->SetMaximum(1.);
	vhEtaAcceptance[massBin-1]->SetMarkerStyle(24);
	vhEtaAcceptance[massBin-1]->SetMarkerSize(1);
	vhEtaAcceptance[massBin-1]->Draw("e1x1");
	pvtxt_massbinname->Draw("SAMES");
	cnvEtaAcc->SaveAs("fitplots/AcceptanceEta_"+sMassBin+".png");
	cnvEtaAcc->SaveAs("fitplots/AcceptanceEta_"+sMassBin+".eps");
	cnvEtaAcc->SaveAs("fitplots/AcceptanceEta_"+sMassBin+".pdf");
	cnvEtaAcc->SaveAs("fitplots/AcceptanceEta_"+sMassBin+".ps");
	cnvEtaAcc->SaveAs("fitplots/AcceptanceEta_"+sMassBin+".root");
	cnvEtaAcc->SaveAs("fitplots/AcceptanceEta_"+sMassBin+".C");
	
	
	TFile* f = new TFile("fitplots/DYmumu_all.root","UPDATE");
	f->cd();
	vhPyQ[massBin-1]->Write();
	vhPyQnumerator[massBin-1]->Write();
	vhPyQdenominator[massBin-1]->Write();
	vhAcceptanceNumerator[massBin-1]->Write();
	vhAcceptanceDenominator[massBin-1]->Write();
	vhAcceptance[massBin-1]->Write();
	vh2dAcceptanceNumerator[massBin-1]->Write();
	vh2dAcceptanceDenominator[massBin-1]->Write();
	vh2dAcceptance[massBin-1]->Write();
	vh2dSymmAcceptance[massBin-1]->Write();
	vh1dSymmAcceptance[massBin-1]->Write();
	vhEtaAcceptanceNumerator[massBin-1]->Write();
	vhEtaAcceptanceDenominator[massBin-1]->Write();
	vhEtaAcceptance[massBin-1]->Write();
	f->Write();
	f->Close();
	delete f;
	
	delete cnvPyQ;
	delete cnvAcc;
	delete cnv2dAcc;
	delete cnv1dSymmAcc;
	delete cnvEtaAcc;
	delete pvtxt_massbinname;
}

void setHistos(int massBin)
{
	TString sMassBin = (TString)_s(massBin);
	TString sTitles = "";
	
	sTitles = "Fraction of events where #vec{#beta}_{Q}^{det}#bullet#vec{p}_{q}^{cmf}<0;y_{Q};P(y_{Q})";
	vhPyQ.push_back(new TH1D("PyQ_massbin_"+sMassBin,sTitles,nyqbins,yqmin,yqmax));
	sTitles = "Events where #vec{#beta}_{Q}^{det}#bullet#vec{p}_{q}^{cmf}<0;y_{Q};Events";
	vhPyQnumerator.push_back(new TH1D("PyQ_massbin_"+sMassBin+"_numerator",sTitles,nyqbins,yqmin,yqmax));
	sTitles = "All events;y_{Q};P(y_{Q});Events";
	vhPyQdenominator.push_back(new TH1D("PyQ_massbin_"+sMassBin+"_denominator",sTitles,nyqbins,yqmin,yqmax));
	vhPyQ[massBin-1]->SetDefaultSumw2(kTRUE);
	vhPyQnumerator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhPyQdenominator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhPyQ[massBin-1]->SetMarkerStyle(24);
	vhPyQ[massBin-1]->SetMarkerSize(1);
	vhPyQnumerator[massBin-1]->SetMarkerStyle(24);
	vhPyQnumerator[massBin-1]->SetMarkerSize(1);
	vhPyQdenominator[massBin-1]->SetMarkerStyle(24);
	vhPyQdenominator[massBin-1]->SetMarkerSize(1);
	
	sTitles = "Acceptance in |cos#theta*|;|cos#theta*|;Acceptance";
	vhAcceptance.push_back(new TH1D("acc_massbin_"+sMassBin,sTitles,nabscostbins,abscostmin,abscostmax));
	sTitles = "Reconstructed(+selection) |cos#theta*| distribution;|cos#theta*|;Events";
	vhAcceptanceNumerator.push_back(new TH1D("acc_massbin_"+sMassBin+"_numerator",sTitles,nabscostbins,abscostmin,abscostmax));
	sTitles = "Truth |cos#theta*| distribution;|cos#theta*|;Events";
	vhAcceptanceDenominator.push_back(new TH1D("acc_massbin_"+sMassBin+"_denominator",sTitles,nabscostbins,abscostmin,abscostmax));
	vhAcceptance[massBin-1]->SetDefaultSumw2(kTRUE);
	vhAcceptanceNumerator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhAcceptanceDenominator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhAcceptance[massBin-1]->SetMarkerStyle(24);
	vhAcceptance[massBin-1]->SetMarkerSize(1);
	vhAcceptanceNumerator[massBin-1]->SetMarkerStyle(24);
	vhAcceptanceNumerator[massBin-1]->SetMarkerSize(1);
	vhAcceptanceDenominator[massBin-1]->SetMarkerStyle(24);
	vhAcceptanceDenominator[massBin-1]->SetMarkerSize(1);
	
	sTitles = "Acceptance in #eta_{#mu^{-}};#eta_{#mu^{-}};Acceptance";
	vhEtaAcceptance.push_back(new TH1D("acc_eta_massbin_"+sMassBin,sTitles,etalogicnbins,etalogicbins));
	sTitles = "Reconstructed(+selection) #eta_{#mu^{-}} distribution;#eta_{#mu^{-}};Events";
	vhEtaAcceptanceNumerator.push_back(new TH1D("acc_eta_massbin_"+sMassBin+"_numerator",sTitles,etalogicnbins,etalogicbins));
	sTitles = "Truth #eta_{#mu^{-}} distribution;#eta_{#mu^{-}};Events";
	vhEtaAcceptanceDenominator.push_back(new TH1D("acc_eta_massbin_"+sMassBin+"_denominator",sTitles,etalogicnbins,etalogicbins));
	vhEtaAcceptance[massBin-1]->SetDefaultSumw2(kTRUE);
	vhEtaAcceptanceNumerator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhEtaAcceptanceDenominator[massBin-1]->SetDefaultSumw2(kTRUE);
	vhEtaAcceptance[massBin-1]->SetMarkerStyle(24);
	vhEtaAcceptance[massBin-1]->SetMarkerSize(1);
	vhEtaAcceptanceNumerator[massBin-1]->SetMarkerStyle(24);
	vhEtaAcceptanceNumerator[massBin-1]->SetMarkerSize(1);
	vhEtaAcceptanceDenominator[massBin-1]->SetMarkerStyle(24);
	vhEtaAcceptanceDenominator[massBin-1]->SetMarkerSize(1);
	
	sTitles = "2d Acceptance in |cos#theta*| vs |y_{Q}|;|cos#theta*|;|y_{Q}|;Acceptance";
	vh2dAcceptance.push_back(new TH2D("2d_acc_massbin_"+sMassBin,sTitles,nabscostbins,abscostmin,abscostmax, nabsyqbins,absyqmin,absyqmax));
	sTitles = "Reconstructed(+selection) |cos#theta*| vs |y_{Q}| distribution;|cos#theta*|;|y_{Q}|;Events";
	vh2dAcceptanceNumerator.push_back(new TH2D("2d_acc_massbin_"+sMassBin+"_numerator",sTitles,nabscostbins,abscostmin,abscostmax, nabsyqbins,absyqmin,absyqmax));
	sTitles = "Truth |cos#theta*| vs |y_{Q}| distribution;|cos#theta*|;|y_{Q}|;Events";
	vh2dAcceptanceDenominator.push_back(new TH2D("2d_acc_massbin_"+sMassBin+"_denominator",sTitles,nabscostbins,abscostmin,abscostmax, nabsyqbins,absyqmin,absyqmax));
	vh2dAcceptance[massBin-1]->SetDefaultSumw2(kTRUE);
	vh2dAcceptanceNumerator[massBin-1]->SetDefaultSumw2(kTRUE);
	vh2dAcceptanceDenominator[massBin-1]->SetDefaultSumw2(kTRUE);

	sTitles = "1d Symmetrized Acceptance in cos#theta*;Symm|cos#theta*|;Acceptance";
	vh1dSymmAcceptance.push_back(new TH1D("1d_symm_acc_massbin_"+sMassBin,sTitles,2*nabscostbins,-1.*abscostmax,abscostmax));
	vh1dSymmAcceptance[massBin-1]->SetDefaultSumw2(kTRUE);
	vh1dSymmAcceptance[massBin-1]->SetMarkerStyle(24);
	vh1dSymmAcceptance[massBin-1]->SetMarkerSize(1);
	
	sTitles = "2d Symmetrized Acceptance in cos#theta* vs y_{Q};Symm|cos#theta*|;Symm|y_{Q}|;Acceptance";
	vh2dSymmAcceptance.push_back(new TH2D("2d_symm_acc_massbin_"+sMassBin,sTitles,2*nabscostbins,-1.*abscostmax,abscostmax, 2*nabsyqbins,-1.*absyqmax,absyqmax));
	vh2dSymmAcceptance[massBin-1]->SetDefaultSumw2(kTRUE);
}


void Afb_RooFit_weighted_2d_DYandDATA()
{
	setMSGlevel(SILENT,VISUAL,VISUAL);

	_DEBUG("Afb_RooFit_weighted");
	style();
	colors();
	
	TFile* fTmp = new TFile("fitplots/PyQ_DYmumu_all.root","RECREATE");
	fTmp->Write();
	fTmp->Close();
	delete fTmp;
	
	setLogBins(nlogmassbins,logmassmin,logmassmax,logmassbins);
	setLogBins(nlogfullimassbins,logfullimassmin,logfullimassmax,logfullimassbins);
	
	randGen = new TRandom();
	randGen->SetSeed(0); // Note that the machine clock is returned with a precision of 1 second.
	// If one calls SetSeed(0) within a loop and the loop time is less than 1s,
	// all generated numbers will be identical!
	
	vector<fitpars> vFitParsResult;
	vector<fitpars> vFitParsResultErr;
	vector<double>  vAfbResult;
	vector<double>  vAfbError;
	
	leg_mHat = new TLegend(0.1545226,0.208042,0.4183417,0.3513986,NULL,"brNDC");
	leg_mHat->SetFillColor(kWhite);
	
	pvtxt_lumi = new TPaveText(0.4648241,0.1975524,0.6432161,0.3409091,"brNDC");
	pvtxt_lumi->SetFillColor(kWhite);
	TString sLumi = (TString)_s(luminosity,2);
	txt = pvtxt_lumi->AddText( "#intLdt~"+ sLumi +" fb^{-1}" );
	
	pvtxt_atlas = new TPaveText(0.5213568,0.7395105,0.6859296,0.8339161,"brNDC");
	pvtxt_atlas->SetFillColor(0);
	pvtxt_atlas->SetTextFont(42);
	txt = pvtxt_atlas->AddText("#bf{#splitline{#it{ATLAS}}{#scale[0.42]{work in progress}}}");
	
	cnvAfb = new TCanvas("cnvAfb", "cnvAfb", 0,0,1200,800);
	pad_mHat = new TPad("padMhat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
	pad_mHat->SetLogy();
	pad_mHat->SetLogx();
	pad_Afb = new TPad("padAfb", "",0,0,1,1);
	pad_Afb->SetTicky(0);
	pad_Afb->SetTickx(1);
	pad_Afb->SetFillStyle(0);
	pad_Afb->SetFrameFillStyle(4000); //will be transparent
	pad_Afb->SetFrameFillColor(0);
	pad_Afb->SetLogx();
	
	
	hMass = new TH1D("hMass","",nlogfullimassbins,logfullimassbins);
	hMass->SetDefaultSumw2(); // The error per bin will be computed as sqrt(sum of squares of weight) for each bin.
	hMass->SetLineColor(kBlue);
	hMass->SetXTitle("m_{#mu#mu} GeV");
	hMass->SetYTitle("Events");
	hMass->GetXaxis()->SetMoreLogLabels(); 
	hMass->GetXaxis()->SetMoreLogLabels();
	leg_mHat->AddEntry( hMass, sChannelMass, "l");
	
	
	hForward  = new TH1D("hForward","",nlogmassbins,logmassbins);
	hBackward = new TH1D("hBackward","",nlogmassbins,logmassbins);
	
	
	hAfbCount = new TH1D("hAfbCount","",nlogmassbins,logmassbins);
	hAfbCount->SetXTitle( "m_{#mu#mu} GeV" );
	hAfbCount->SetYTitle( "A_{FB}" );
	hAfbCount->SetLineColor(kBlue);
	hAfbCount->SetFillColor(kBlue);
	// hAfbFit->SetFillStyle(fillStyle);
	hAfbCount->SetLineWidth(1);
	hAfbCount->SetMarkerSize(1);
	hAfbCount->SetMarkerStyle(24);
	hAfbCount->SetMarkerColor(kBlue);
	// leg_mHat->AddEntry( hAfbCount, sChannelCount, "f");
	leg_mHat->AddEntry( hAfbCount, sChannelCount, "lep");
	
	
	hAfbFit = new TH1D("hAfbFit","",nlogmassbins,logmassbins);
	hAfbFit->SetXTitle( "m_{#mu#mu} GeV" );
	hAfbFit->SetYTitle( "A_{FB}" );
	hAfbFit->SetLineColor(kRed);
	hAfbFit->SetFillColor(kRed);
	// hAfbFit->SetFillStyle(fillStyle);
	hAfbFit->SetLineWidth(1);
	hAfbFit->SetMarkerSize(1);
	hAfbFit->SetMarkerStyle(24);
	hAfbFit->SetMarkerColor(kRed);
	// leg_mHat->AddEntry( hAfbFit, sChannelFit, "f");
	leg_mHat->AddEntry( hAfbFit, sChannelFit, "lep");
	
	///////////////////
	settrees(); ///////
	///////////////////
	
	
	for(int massBin=1 ; massBin<=nlogmassbins ; massBin++)
	{
		TString sMassBin = (TString)_s(massBin);
		
		_INFO("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~START: mass bin "+_s(massBin)+"~~~~~~~~~~~~~~~~~~~~~~~~");
		bool skip = false;
		////////////////////////////////////////////////////
		init(massBin); /////////////////////////////////////
		setHistos(massBin); ////////////////////////////////
		Int_t N = loop(massBin); ///////////////////////////
		drawHistos(massBin); ///////////////////////////////
		if(N<=minEntries2Fit) skip=true; ///////////////////
		if(!skip) getFit(); ////////////////////////////////
		////////////////////////////////////////////////////
		_INFO("\n~~~~~~~~~~~~~~~~~~~~~~~~END:   mass bin "+_s(massBin)+"~~~~~~~~~~~~~~~~~~~~~~~~");
		
		if(!skip)
		{
			fitpars fp;
			fitpars dfp;
			double Afb;
			double dAfb;
			fp.A0 = A0->getVal();
			fp.A4 = A4->getVal();
			dfp.A0 = A0->getError();
			dfp.A4 = A4->getError();
			vFitParsResult.push_back( fp );
			vFitParsResultErr.push_back( dfp );
			Afb = getAfb(A4->getVal());
			if(doBinomialError) dAfb = getAfbErr(Afb,N);
			else                dAfb = getAfbErr(dfp.A4);
			vAfbResult.push_back( Afb );
			vAfbError.push_back( dAfb );
			plot(massBin);
			_INFO("N="+_s(N)+" --> Afb = "+_s(vAfbResult[massBin-1])+" +- "+_s(vAfbError[massBin-1]));
			Double_t Nf = hForward->GetBinContent(massBin);
			Double_t Nb = hBackward->GetBinContent(massBin);
			double afbCount = getAfb(Nf,Nb);
			double dafbCount = getAfbErr(afbCount, Nf+Nb);
			_INFO("N="+_s(N)+"(Nf="+_s(Nf)+",Nb="+_s(Nb)+") --> Afb = "+_s(afbCount)+" +- "+_s(dafbCount));
		}
		else
		{
			vAfbResult.push_back( -999. );
			vAfbError.push_back( -999. );
			_INFO("0 entries, skipping.");
		}

		hAfbFit->SetBinContent(massBin,vAfbResult[massBin-1]);
		hAfbFit->SetBinError(massBin,vAfbError[massBin-1]);
		
		_INFO("completted massBin="+_s(massBin));
		/////////////
		reset(); ////
		/////////////
		_INFO("reset massBin="+_s(massBin));
	}
	
	////////////////
	AfbCount(); ////
	drawAfb(); /////
	////////////////
	
	// for(unsigned int i=0 ; i<vInitialGuess.size() ; i++)
	for(int massBin=1 ; massBin<=nlogmassbins ; massBin++)
	{
		int i = massBin-1;
		
		cout << "\nmass bin " << i << " [" << logfullimassbins[i] << "->" << logfullimassbins[i+1] << "]:" << endl; 
		cout << "STATUS=" << vbFitStatus[i]
		<< "\t[A0,A4](guess)=[" << vInitialGuess[i].A0 << "," << vInitialGuess[i].A4
		<< "]\t->  Afb(guess)=" << getAfb(vInitialGuess[i].A4)
		<< "\t-> \tA0(fit)=" << vFitParsResult[i].A0 << "+-" << vFitParsResultErr[i].A0
		<< "\t-> \tA4(fit)=" << vFitParsResult[i].A4 << "+-" << vFitParsResultErr[i].A4
		<< ",\tAfb(fit)=" << vAfbResult[i] << "+-" << vAfbError[i] << endl;
	}
	
	printRunConfig();
}



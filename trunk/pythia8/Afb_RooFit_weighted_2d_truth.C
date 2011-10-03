#include "all.h"
#include "roofit.h"
#include "RooAngular.h"
#include "RooCollinsSoper.h"
#include "RooFBfalseIdentifyCS.h"

const double maxMass = 3000.;

const int             nlogicmassbins = 44;
static const Double_t logicmassmin   = 75.;
static const Double_t logicmassmax   = maxMass;
const Double_t logicmassbins[nlogicmassbins+1] =
				{
					75,85,95,105,120,
					135,150,165,180,195,215,230,250,
					270,290,310,330,350,375,400,
					430,460,490,520,560,600,
					640,680,720,760,800,850,900,
					950,1000,1075,1150,1250,
					1375,1500,1625,1750,
					1875,2000,
					maxMass
				};

const int      ndymassbins = 11;
const Double_t dymassbins[ndymassbins+1] =
				{
					75,120,250,400,600,800,1000,1250,1500,1750,2000,maxMass
				};
TH1* hDYbins = new TH1("hDYbins","hDYbins",ndymassbins,dymassbins);	

static const Int_t    nlogmassbins = 25;
static const Double_t logmassmin   = 75.;
static const Double_t logmassmax   = maxMass;
static Double_t logmassbins[nlogmassbins+1];

static const Int_t    nlogfullimassbins = 60;
static const Double_t logfullimassmin   = 75.;
static const Double_t logfullimassmax   = maxMass;
static Double_t logfullimassbins[nlogfullimassbins+1];


int truth_entries = 0;

double   costmin   = minCosTheta;
double   costmax   = maxCosTheta;
int      ncostbins = nCosThetaBins;

double   yqmin   = minyQ;
double   yqmax   = maxyQ;
int      nyqbins = nyQbins;

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
TString sChannelFit   = "#gamma/Z^{0} [MC10b Truth]: A_{FB} fit";
TString sChannelCount = "#gamma/Z^{0} [MC10b Truth]: A_{FB} count";
TString sChannelMass  = "#gamma/Z^{0} [MC10b Truth]: Events";
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
RooRealVar* yQ;     // the variable 
RooRealVar* weight; // the weight
RooRealVar* A0;     // the parameter to find
RooRealVar* A4;     // the parameter to find


RooAbsData* unbinnedDataSet; // Roo Data holder
vector<RooFitResult*> vFitResult;
vector<bool>          vbFitStatus;
vector<TH1D*> vhPyQ;
vector<TH1D*> vhPyQdenominator;

RooAbsPdf* modelPdf;   // the final model pdf
RooAbsPdf* sigPdf;   // the truth pdf

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
	settree("../data/mcLocalControl_DYmumu_75M120.root", "mcLocalControl_DYmumu_75M120", 19996, 0.81705*nb2fb);
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
		massbinlowedge  = logicmassbins[nlogicmassbins-1]; //2000.;
		massbinhighedge = logicmassbins[nlogicmassbins];   //maxMass;
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

double getAfbErr(double Afb, int N)
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
	return logicmassbins[massBin-1]+(logicmassbins[massBin]-logicmassbins[massBin-1])/2.;
}

double getMassBinLowEdge(int massBin)
{
	_DEBUG("getMassBinLowEdge");
	return logicmassbins[massBin-1];
}

double getMassBinHighEdge(int massBin)
{
	_DEBUG("getMassBinHighEdge");
	return logicmassbins[massBin];
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

void init(int massBin)
{
	_DEBUG("init");
	
	double iMassMin = getMassBinLowEdge(massBin);
	double iMassMax = getMassBinHighEdge(massBin);
	
	TString sMassBin = (TString)_s(massBin);
	string sMassMin = _s((double)iMassMin);
	string sMassMax = _s((double)iMassMax);
	TString sTitle = "Mass-bin[" + sMassBin + "] " + sMassMin + "#rightarrow" + sMassMax + " GeV";

	cosThe = new RooRealVar("cosTheta","cos#theta*",costmin,costmax);
	cosThe->setRange("range_cosThe",costmin,costmax);
	cosThe->setBins(ncostbins);
	
	yQ = new RooRealVar("yQ","y_{Q}",yqmin,yqmax);
	yQ->setRange("range_yQ",yqmin,yqmax);
	yQ->setBins(nyqbins);
	
	weight = new RooRealVar("weight","weight",0.,1e10);
	//weight->setRange("range_weight",costmin,costmax);
	//weight->setBins(ncostbins);

	_A0 = randomizeItialGuess(minA0,maxA0);
	_A4 = randomizeItialGuess(minA4,maxA4);
	fitpars fp;
	fp.A0 = _A0;
	fp.A4 = _A4;
	vInitialGuess.push_back(fp);
	A0 = new RooRealVar("A0","A0",_A0,minA0,maxA0);
	A4 = new RooRealVar("A4","A4",_A4,minA4,maxA4);
	A0->setError(0.00001);
	A4->setError(0.00001);
	
	// A0 = new RooRealVar("A0","A0",0.);
	// A0->setConstant(kTRUE);
	// A4 = new RooRealVar("A4","A4",_A4,minA4,maxA4);
	// A4->setError(0.00001);
	
	if(doLumiXSweights) unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*yQ,*weight),WeightVar(weight->GetName()));
	else                unbinnedDataSet = new RooDataSet("data","data",RooArgSet(*cosThe,*yQ));
}

void reset()
{	
	delete cosThe;
	delete yQ;
	delete weight;
	delete A0;
	delete A4;
	delete sigPdf;
	// delete modelPdf;
	delete unbinnedDataSet;
}

Int_t loop(int massBin)
{
	_DEBUG("loop");
	Int_t    N = 0;
	Double_t W = 1.;
	
	Double_t lowmasscut  = getMassBinLowEdge(massBin);
	Double_t highmasscut = getMassBinHighEdge(massBin);
	
	for(TMapTSP2TTREE::iterator it=treMap.begin() ; it!=treMap.end() ; ++it)
	{
		tree = it->second;
		setbranches();
		N = tree->GetEntriesFast();
		W = wgtMap[it->first];
		_INFO("name = "+(string)it->first+" -> N="+_s(N));
		truth_entries = 0;
		for(Int_t entry=0 ; entry<N ; entry++)
		{
			tree->GetEntry(entry);
			if(!truth_all_isValid) continue;
			
			int imuontru  = (truth_all_mc_pdgId->at(0)>0) ? 0 : 1;
			int iamuontru = (imuontru==0) ? 1 : 0;
			tlvmua->SetPtEtaPhiM(truth_all_mc_pt->at(imuontru),truth_all_mc_eta->at(imuontru),truth_all_mc_phi->at(imuontru),truth_all_mc_m->at(imuontru));
			tlvmub->SetPtEtaPhiM(truth_all_mc_pt->at(iamuontru),truth_all_mc_eta->at(iamuontru),truth_all_mc_phi->at(iamuontru),truth_all_mc_m->at(iamuontru));
			double YQ   = ySystem(tlvmua,tlvmub);
			double mHat = imass(tlvmua,tlvmub);
			
			// Double_t massbinlowedge  = 0.;
			// Double_t massbinhighedge = 0.;
			// parseDYbinName((string)it->first,massbinlowedge,massbinhighedge);
			// if(mHat<massbinlowedge || mHat>massbinhighedge) continue; // in this mass bin, do not take events from different DY mass bins
			if(mHat<lowmasscut || mHat>highmasscut)         continue; // to get the events in the relevant mass bin
			if(YQ>+2.5 || YQ<-2.5)                          continue; // to reject events that have no P(yQ) calculated
			
			float ca    = truth_all_mc_charge->at(imuontru);
			float cb    = truth_all_mc_charge->at(iamuontru);
			double cost = cosThetaCollinsSoper(tlvmua,ca,tlvmub,cb);
			// double cost = cosThetaBoost(tlvmua,ca,tlvmub,cb);
			
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
			if(cosalpha_beta_quark<=0.) vhPyQ[massBin-1]->Fill(YQ,W);
			vhPyQdenominator[massBin-1]->Fill(YQ,W);
			
			*cosThe = cost;
			//*cosThe = costheta_mutru_quark;
			*yQ     = YQ;
			hMass->Fill(mHat,W);
			
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
			
			if(doLumiXSweights) unbinnedDataSet->add(RooArgSet(*cosThe,*yQ),W); // WEIGHTED
			else                unbinnedDataSet->add(RooArgSet(*cosThe,*yQ)); // WEIGHTED
			
			truth_entries++;
		}
		_INFO("truth_entries = "+_s(truth_entries));
	}
	
	vhPyQ[massBin-1]->Divide(vhPyQdenominator[massBin-1]);
	sigPdf = new RooFBfalseIdentifyCS("SignalPdf", "SignalPdf", *cosThe,*yQ,*A0,*A4,*vhPyQ[massBin-1]);
	modelPdf = sigPdf;
	
	return N;
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
	if(doLumiXSweights) fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),SumW2Error(kTRUE),NumCPU(8),ConditionalObservables(*yQ));
	else                fitresult = modelPdf->fitTo( *unbinnedDataSet,Minos(kTRUE),Range("range_cosThe"),Strategy(2),Save(kTRUE),Timer(kTRUE),NumCPU(8),ConditionalObservables(*yQ));
	gFit = gMinuit;
	
	vbFitStatus.push_back( minuitStatus(gFit) );
	
	fitresult->Print("v");
	
	return fitresult;
}

void plot(int massbin)
{
	_DEBUG("plot");
	
	TCanvas* cnv = new TCanvas("cnv_"+(TString)_s(massbin),"cnv_"+(TString)_s(massbin), 600,400);
	cnv->SetFillColor(kWhite);
	cnv->Draw();
	cnv->cd();
	
	TString sMassBin = (TString)_s(massbin);
	
	RooPlot* cosThetaFrame = cosThe->frame(Name("cosThetaFrame"), Title( "DYmumu" ));
	if(!unbinnedDataSet->isWeighted()  &&  doLumiXSweights) _WARNING("$$$$$$$$$$$ The dataset is unweighted $$$$$$$$$$$");
	if(doLumiXSweights) unbinnedDataSet->plotOn(cosThetaFrame,Name("cos#theta*"),XErrorSize(0),MarkerSize(0.3),Binning(ncostbins),DataError(RooAbsData::SumW2),NumCPU(8));
	else                 unbinnedDataSet->plotOn(cosThetaFrame,Name("cos#theta*"),XErrorSize(0),MarkerSize(0.3),Binning(ncostbins),NumCPU(8));
	modelPdf->plotOn(cosThetaFrame,ProjWData(*yQ,*unbinnedDataSet),LineWidth(1),LineColor(cPdf),NormRange("range_cosThe"),NumCPU(8));
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
	hAfbFit->GetYaxis()->SetRangeUser(-1.5,+1.5);
	// hAfbFit->Draw("E5 Y+");
	hAfbFit->Draw("e1x1 Y+");
	hAfbFit->GetXaxis()->SetMoreLogLabels(); 
	hAfbFit->GetXaxis()->SetNoExponent();
	// hAfbCounthAfbCount->Draw("E5 Y+ SAMES");
	hAfbCount->Draw("e1x1 Y+ SAMES");
	hAfbCount->GetXaxis()->SetMoreLogLabels(); 
	hAfbCount->GetXaxis()->SetNoExponent();

	TLine* line = new TLine(logicmassmin,0.,logicmassmax,0.);
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

void drawPyQ(int massBin)
{
	TString sMassBin = (TString)_s(massBin);
	TCanvas* cnvPyQ = new TCanvas("c_"+sMassBin, "", 600,400);
	cnvPyQ->SetFillColor(0);
	
	TPaveText* pvtxt_massbinname = new TPaveText(0.3277592,0.8056995,0.4916388,0.9002591,"brNDC");
	pvtxt_massbinname->SetFillColor(0);
	pvtxt_massbinname->SetTextFont(42);
	txt = pvtxt_massbinname->AddText("m_{#mu#mu}: "+(TString)_s(logicmassbins[massBin-1])+"#rightarrow"+(TString)_s(logicmassbins[massBin])+" GeV");
	
	cnvPyQ->cd();
	cnvPyQ->Draw();
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
	
	TFile* f = new TFile("fitplots/PyQ_DYmumu_all.root","UPDATE");
	f->cd();
	vhPyQ[massBin-1]->Write();
	f->Write();
	f->Close();
	delete f;
	
	delete cnvPyQ;
	delete pvtxt_massbinname;
}


void Afb_RooFit_weighted_2d_truth()
{
	setMSGlevel(SILENT,VISUAL,VISUAL);

	_DEBUG("Afb_RooFit_weighted");
	style();
	colors();
	
	TFile* fTmp = new TFile("fitplots/PyQ_DYmumu_all.root","RECREATE");
	fTmp->Write();
	fTmp->Close();
	delete fTmp;
	
	//setLogBins(nlogicmassbins,logicmassmin,logicmassmax,logicmassbins);
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
	
	
	hForward  = new TH1D("hForward","",nlogicmassbins,logicmassbins);
	hBackward = new TH1D("hBackward","",nlogicmassbins,logicmassbins);
	
	
	hAfbCount = new TH1D("hAfbCount","",nlogicmassbins,logicmassbins);
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
	
	
	hAfbFit = new TH1D("hAfbFit","",nlogicmassbins,logicmassbins);
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
	
	
	for(int massBin=1 ; massBin<=nlogicmassbins ; massBin++)
	{
		TString sMassBin = (TString)_s(massBin);
		
		_INFO("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~START: mass bin "+_s(massBin)+"~~~~~~~~~~~~~~~~~~~~~~~~");
		bool skip = false;
		////////////////////////////////////////////////////
		init(massBin); /////////////////////////////////////
		vhPyQ.push_back(new TH1D("massbin_"+sMassBin,"Fraction of events where #vec{#beta}_{Q}^{det}#bullet#vec{p}_{q}^{cmf}<0;y_{Q};P(y_{Q})",nyqbins,yqmin,yqmax));
		vhPyQdenominator.push_back(new TH1D("massbin_"+sMassBin+"_denominator","Fraction of events where #vec{#beta}_{Q}^{det}#bullet#vec{p}_{q}^{cmf}<0;y_{Q};P(y_{Q})",nyqbins,yqmin,yqmax));
		Int_t N = loop(massBin); ///////////////////////////
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
	for(int massBin=1 ; massBin<=nlogicmassbins ; massBin++)
	{
		int i = massBin-1;
	
		/////////////////////////
		drawPyQ(massBin); ///////
		/////////////////////////
	
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



#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // for the sprintf call
#include <string>
#include <sstream>      // for the int to string operation (stringstream call)
#include <cstring>      // for the string functions
#include <math.h>
#include <cmath>
#include <complex>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <time.h>

#include <TROOT.h>
#include <TSystem.h>
#include <TMatrix.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TCut.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <TF1.h>
#include <TAxis.h>
#include <TLine.h>
#include <TPaveText.h>
#include <TThread.h>
#include <TList.h>
#include <TRandom.h>

using namespace std;

// Declare pointer to data as global (not elegant but TMinuit needs this).
vector<TLorentzVector*> vLV;
vector<vector<double> *> VVCOSTH;
vector<TH1D*> VHIST_Z0;
vector<TH1D*> VHIST_KK;
vector<TH1D*> VHIST_ZP;
vector<TVirtualPad*> VPAD;
TCanvas* CNV = new TCanvas("C", "C", 1200, 800);
unsigned int CURRENTBIN;
bool ISZ0;
bool ISZP;
bool ISKK;
string REFNAME = "CosThetaCS";
//string REFNAME = "CosThetaHE";
Float_t IMASS;
Float_t COSTH;
vector<double>* CHARGE;
vector<int>*    ID;
vector<double>* PX;
vector<double>* PY;
vector<double>* PZ;
vector<double>* E;
vector<double>* PT;
vector<double>* PHI;
vector<double>* THETA;
vector<double>* ETA;

Float_t IMASStmp;
Float_t COSTHtmp;
vector<double>* CHARGEtmp = new vector<double>;
vector<int>*    IDtmp = new vector<int>;
vector<double>* PXtmp = new vector<double>;
vector<double>* PYtmp = new vector<double>;
vector<double>* PZtmp = new vector<double>;
vector<double>* Etmp = new vector<double>;
vector<double>* PTtmp = new vector<double>;
vector<double>* PHItmp = new vector<double>;
vector<double>* THETAtmp = new vector<double>;
vector<double>* ETAtmp = new vector<double>;

TLorentzVector* pa = new TLorentzVector();
TLorentzVector* pb = new TLorentzVector();

vector<double>* PXsmr = new vector<double>;
vector<double>* PYsmr = new vector<double>;
vector<double>* PZsmr = new vector<double>;
vector<double>* Esmr  = new vector<double>;
vector<double>* PTsmr = new vector<double>;


vector<bool>* muQAflag = new vector<bool>;

TLorentzVector m_pTmp;

////////////////////////////////////////////////////////////////////////////
// definitions /////////////////////////////////////////////////////////////
const double GeV2TeV  = 1.e-3;
const double MeV2TeV  = 1.e-6;
const double GeV2MeV  = 1.e+3;
const double muonMass = 0.105658367; // GeV

const double sigma_KK   = 7.68E-09; // mb
double nevents_KK = 1500000.;
const double sigma_ZP   = 7.88E-09; // mb
double nevents_ZP = 1500000.;
const double sigma_Z0   = 7.96E-09; // mb
double nevents_Z0 = 1500000.;

const double minAsymmetry  = -1.; //-0.6;
const double maxAsymmetry  = +1.; //+0.6;

const double ifb2imb = 1.e+12;
const double L       = 5.; // 1/fb

const bool DOSELECTION      = false;
const bool DOSMEAR          = false;
const bool FITWITHALLEVENTS = true; // false if only fit to N events for a given luminosity (see L above)

const int minEntriesDATA = 10;
const int minEntriesMC   = 10;
const string refframe    = REFNAME;
const bool doLogM        = true;
const bool doLogx        = true;

const double AVERAGE      = 0.; // for gaussian smearing
const double SIGMA        = 1.; // for gaussian smearing
const double RESOLUTION   = 0.12; // resolution for smearing pT~1TeV
const double PTTRACKSCALE = 1.e+3; // in GeV/c
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
// global branches and variables
TBranch        *b_RunNumber;   //!
TBranch        *b_EventNumber;   //!
TBranch        *b_Token;   //!
TBranch        *b_Run;   //!
TBranch        *b_Event;   //!
TBranch        *b_Time;   //!
TBranch        *b_LumiBlock;   //!
TBranch        *b_BCID;   //!
TBranch        *b_LVL1ID;   //!
TBranch        *b_Weight;   //!
TBranch        *b_IEvent;   //!
TBranch        *b_StatusElement;   //!
TBranch        *b_LVL1TriggerType;   //!
TBranch        *b_LVL1TriggerInfo;   //!
TBranch        *b_LVL2TriggerInfo;   //!
TBranch        *b_EventFilterInfo;   //!
TBranch        *b_StreamTagName;   //!
TBranch        *b_StreamTagType;   //!

TBranch        *b_MuonN;   //!
TBranch        *b_MuonAuthor;   //!
TBranch        *b_MuonCombTrkNt;   //!
TBranch        *b_MuonInDetTrkNt;   //!
TBranch        *b_MuonExtrNt;   //!
TBranch        *b_MuonEta;   //!
TBranch        *b_MuonPhi;   //!
TBranch        *b_MuonPt;   //!
TBranch        *b_MuonZ0;   //!
TBranch        *b_MuonD0;   //!
TBranch        *b_MuonCharge;   //!
TBranch        *b_MuonKf;   //!
TBranch        *b_MuonPx;   //!
TBranch        *b_MuonPy;   //!
TBranch        *b_MuonPz;   //!
TBranch        *b_MuonEtCone10;   //!
TBranch        *b_MuonEtCone20;   //!
TBranch        *b_MuonEtCone30;   //!
TBranch        *b_MuonEtCone40;   //!
TBranch        *b_MuonNuCone10;   //!
TBranch        *b_MuonNuCone20;   //!
TBranch        *b_MuonNuCone30;   //!
TBranch        *b_MuonNuCone40;   //!
TBranch        *b_MuonFitChi2;   //!
TBranch        *b_MuonFitNumberDoF;   //!
TBranch        *b_MuonEnergyLossDeposit;   //!
TBranch        *b_MuonEnergyLossSigma;   //!
TBranch        *b_MuonMatchChi2;   //!
TBranch        *b_MuonMatchNumberDoF;   //!
TBranch        *b_MuonBestMatch;   //!
TBranch        *b_MuonIsCombinedMuon;   //!

Int_t           RunNumber;
Int_t           EventNumber;
Char_t          Token;
Int_t           Run;
Int_t           Event;
Int_t           Time;
Int_t           LumiBlock;
Int_t           BCID;
Int_t           LVL1ID;
Double_t        Weight;
Int_t           IEvent;
Int_t           StatusElement;
Int_t           LVL1TriggerType;
vector<unsigned int> *LVL1TriggerInfo;
vector<unsigned int> *LVL2TriggerInfo;
vector<unsigned int> *EventFilterInfo;
vector<string>  *StreamTagName;
vector<string>  *StreamTagType;
UInt_t          MuonN;
vector<double>  *MuonAuthor;
vector<double>  *MuonCombTrkNt;
vector<double>  *MuonInDetTrkNt;
vector<double>  *MuonExtrNt;
vector<double>  *MuonEta;
vector<double>  *MuonPhi;
vector<double>  *MuonPt;
vector<double>  *MuonZ0;
vector<double>  *MuonD0;
vector<double>  *MuonCharge;
vector<double>  *MuonKf;
vector<double>  *MuonPx;
vector<double>  *MuonPy;
vector<double>  *MuonPz;
vector<double>  *MuonEtCone10;
vector<double>  *MuonEtCone20;
vector<double>  *MuonEtCone30;
vector<double>  *MuonEtCone40;
vector<double>  *MuonNuCone10;
vector<double>  *MuonNuCone20;
vector<double>  *MuonNuCone30;
vector<double>  *MuonNuCone40;
vector<double>  *MuonFitChi2;
vector<long>    *MuonFitNumberDoF;
vector<double>  *MuonEnergyLossDeposit;
vector<double>  *MuonEnergyLossSigma;
vector<double>  *MuonMatchChi2;
vector<long>    *MuonMatchNumberDoF;
vector<long>    *MuonBestMatch;
vector<long>    *MuonIsCombinedMuon;


//////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////
// Kinematics /////////////////////////////////////////////////////////////////////////
inline float imass( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.M();
}

inline float QT( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.Perp();
}

inline float ySystem( TLorentzVector* pa, TLorentzVector* pb )
{
	m_pTmp = (*pa)+(*pb);
	return m_pTmp.Rapidity();
}

inline float cosThetaBoost( TLorentzVector* pa, float ca, TLorentzVector* pb, float cb )
{
	// http://xrootd.slac.stanford.edu/BFROOT/www/doc/workbook_backup_010108/analysis/analysis.html
	// A useful quantity in many analyses is the helicity angle.
	// In the reaction Y -> X -> a + b, the helicity angle of 
	// particle a is the angle measured in the rest frame of the
	//decaying parent particle, X, between the direction of the
	// decay daughter a and the direction of the grandparent particle Y.

	m_pTmp = (*pa)+(*pb); // this is the mumu system (Z) 4vector
	TVector3 ZboostVector = m_pTmp.BoostVector(); // this is the 3vector of the Z
	TLorentzVector p; // this is the muon 4vector
	
	if(ca<0)      p.SetPxPyPzE(pa->Px(),pa->Py(),pa->Pz(),pa->E());
	else if(cb<0) p.SetPxPyPzE(pb->Px(),pb->Py(),pb->Pz(),pb->E());
	p.Boost( -ZboostVector ); // boost p to the dimuon CM (rest) frame
	float cosThetaB = p.Vect()*m_pTmp.Vect()/(p.P()*m_pTmp.P());
	//if (ySystem(pa,pb) < 0) cosThetaB *= -1.; // reclassify ???
	return cosThetaB;
}

inline float cosThetaCollinsSoper( TLorentzVector* pa, float ca, TLorentzVector* pb, float cb )
{
	// this will work only for leptons e, mu and tau
	// by default it is assumed that pa is the lepton
	// if instead pb is the lepton, then the result is
	// reclassified by a (-) sign - see line 4.
	float mass2 = imass(pa,pb)*imass(pa,pb);
	float QT2 = QT(pa,pb)*QT(pa,pb);
	//float cosThetaCS = 2.*( pa->Plus()*pb->Minus() - pa->Minus()*pb->Plus() ) / sqrt( mass2 * (mass2 + QT2) );
	float cosThetaCS = 2.*( pa->Pz()*pb->E() - pa->E()*pb->Pz() ) / sqrt( mass2 * (mass2 + QT2) );
	if (ca>0. && cb<0.)     cosThetaCS *= -1.; // if pb is the lepton
	if (ySystem(pa,pb) < 0) cosThetaCS *= -1.; // reclassify
	return cosThetaCS;
}
///////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////
// initialize the tree
inline void initTree(TTree* t)
{
	LVL1TriggerInfo = 0;
	LVL2TriggerInfo = 0;
	EventFilterInfo = 0;
	StreamTagName = 0;
	StreamTagType = 0;

	MuonAuthor = 0;
	MuonCombTrkNt = 0;
	MuonInDetTrkNt = 0;
	MuonExtrNt = 0;
	MuonEta = 0;
	MuonPhi = 0;
	MuonPt = 0;
	MuonZ0 = 0;
	MuonD0 = 0;
	MuonCharge = 0;
	MuonKf = 0;
	MuonPx = 0;
	MuonPy = 0;
	MuonPz = 0;
	MuonEtCone10 = 0;
	MuonEtCone20 = 0;
	MuonEtCone30 = 0;
	MuonEtCone40 = 0;
	MuonNuCone10 = 0;
	MuonNuCone20 = 0;
	MuonNuCone30 = 0;
	MuonNuCone40 = 0;
	MuonFitChi2 = 0;
	MuonFitNumberDoF = 0;
	MuonEnergyLossDeposit = 0;
	MuonEnergyLossSigma = 0;
	MuonMatchChi2 = 0;
	MuonMatchNumberDoF = 0;
	MuonBestMatch = 0;
	MuonIsCombinedMuon = 0;
	
	t->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
	t->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
	t->SetBranchAddress("Token", &Token, &b_Token);
	t->SetBranchAddress("Run", &Run, &b_Run);
	t->SetBranchAddress("Event", &Event, &b_Event);
	t->SetBranchAddress("Time", &Time, &b_Time);
	t->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
	t->SetBranchAddress("BCID", &BCID, &b_BCID);
	t->SetBranchAddress("LVL1ID", &LVL1ID, &b_LVL1ID);
	t->SetBranchAddress("Weight", &Weight, &b_Weight);
	t->SetBranchAddress("IEvent", &IEvent, &b_IEvent);
	t->SetBranchAddress("StatusElement", &StatusElement, &b_StatusElement);
	t->SetBranchAddress("LVL1TriggerType", &LVL1TriggerType, &b_LVL1TriggerType);
	t->SetBranchAddress("LVL1TriggerInfo", &LVL1TriggerInfo, &b_LVL1TriggerInfo);
	t->SetBranchAddress("LVL2TriggerInfo", &LVL2TriggerInfo, &b_LVL2TriggerInfo);
	t->SetBranchAddress("EventFilterInfo", &EventFilterInfo, &b_EventFilterInfo);
	t->SetBranchAddress("StreamTagName", &StreamTagName, &b_StreamTagName);
	t->SetBranchAddress("StreamTagType", &StreamTagType, &b_StreamTagType);

	t->SetBranchAddress("MuonN", &MuonN, &b_MuonN);
	t->SetBranchAddress("MuonAuthor", &MuonAuthor, &b_MuonAuthor);
	t->SetBranchAddress("MuonCombTrkNt", &MuonCombTrkNt, &b_MuonCombTrkNt);
	t->SetBranchAddress("MuonInDetTrkNt", &MuonInDetTrkNt, &b_MuonInDetTrkNt);
	t->SetBranchAddress("MuonExtrNt", &MuonExtrNt, &b_MuonExtrNt);
	t->SetBranchAddress("MuonEta", &MuonEta, &b_MuonEta);
	t->SetBranchAddress("MuonPhi", &MuonPhi, &b_MuonPhi);
	t->SetBranchAddress("MuonPt", &MuonPt, &b_MuonPt);
	t->SetBranchAddress("MuonZ0", &MuonZ0, &b_MuonZ0);
	t->SetBranchAddress("MuonD0", &MuonD0, &b_MuonD0);
	t->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
	t->SetBranchAddress("MuonKf", &MuonKf, &b_MuonKf);
	t->SetBranchAddress("MuonPx", &MuonPx, &b_MuonPx);
	t->SetBranchAddress("MuonPy", &MuonPy, &b_MuonPy);
	t->SetBranchAddress("MuonPz", &MuonPz, &b_MuonPz);
	t->SetBranchAddress("MuonEtCone10", &MuonEtCone10, &b_MuonEtCone10);
	t->SetBranchAddress("MuonEtCone20", &MuonEtCone20, &b_MuonEtCone20);
	t->SetBranchAddress("MuonEtCone30", &MuonEtCone30, &b_MuonEtCone30);
	t->SetBranchAddress("MuonEtCone40", &MuonEtCone40, &b_MuonEtCone40);
	t->SetBranchAddress("MuonNuCone10", &MuonNuCone10, &b_MuonNuCone10);
	t->SetBranchAddress("MuonNuCone20", &MuonNuCone20, &b_MuonNuCone20);
	t->SetBranchAddress("MuonNuCone30", &MuonNuCone30, &b_MuonNuCone30);
	t->SetBranchAddress("MuonNuCone40", &MuonNuCone40, &b_MuonNuCone40);
	t->SetBranchAddress("MuonFitChi2", &MuonFitChi2, &b_MuonFitChi2);
	t->SetBranchAddress("MuonFitNumberDoF", &MuonFitNumberDoF, &b_MuonFitNumberDoF);
	t->SetBranchAddress("MuonEnergyLossDeposit", &MuonEnergyLossDeposit, &b_MuonEnergyLossDeposit);
	t->SetBranchAddress("MuonEnergyLossSigma", &MuonEnergyLossSigma, &b_MuonEnergyLossSigma);
	t->SetBranchAddress("MuonMatchChi2", &MuonMatchChi2, &b_MuonMatchChi2);
	t->SetBranchAddress("MuonMatchNumberDoF", &MuonMatchNumberDoF, &b_MuonMatchNumberDoF);
	t->SetBranchAddress("MuonBestMatch", &MuonBestMatch, &b_MuonBestMatch);
	t->SetBranchAddress("MuonIsCombinedMuon", &MuonIsCombinedMuon, &b_MuonIsCombinedMuon);
}

inline bool getEntry(TTree* t, Long64_t l64t_entry)
{
	t->GetEntry(l64t_entry);
	
	CHARGEtmp->clear();
	IDtmp->clear();
	PXtmp->clear();
	PYtmp->clear();
	PZtmp->clear();
	Etmp->clear();
	PTtmp->clear();
	PHItmp->clear();
	ETAtmp->clear();
	
	int nPassed = 0;
	for(UInt_t mu=0 ; mu<MuonN ; mu++)
	{		
		//////////////////////////////////////////////////////////////////////
		// Single muon selection /////////////////////////////////////////////
		if(MuonPt->at(mu)*MeV2TeV<0.025)                     continue; /////////
		if(fabs(MuonEta->at(mu)*MeV2TeV)>2.4)                continue; /////////
		//if(fabs(MuonZ0->at(mu))>0.2)                       continue; /////////
		//if(fabs(MuonD0->at(mu))>1.)                        continue; /////////
		//if(fabs(MuonEtCone30->at(mu)/MuonPt->at(mu))>0.05) continue; /////////
		//////////////////////////////////////////////////////////////////////
		
		nPassed++;
		
		double nrg = sqrt(MuonPx->at(mu)*MuonPx->at(mu) + MuonPy->at(mu)*MuonPy->at(mu) + MuonPz->at(mu)*MuonPz->at(mu) + muonMass*GeV2MeV*muonMass*GeV2MeV);
		
		//Etmp->push_back(MuonKf->at(mu));
		Etmp->push_back(nrg);
		PXtmp->push_back(MuonPx->at(mu));
		PYtmp->push_back(MuonPy->at(mu));
		PZtmp->push_back(MuonPz->at(mu));
		PTtmp->push_back(MuonPt->at(mu));
		PHItmp->push_back(MuonPhi->at(mu));
		ETAtmp->push_back(MuonEta->at(mu));
		CHARGEtmp->push_back(MuonCharge->at(mu));
		IDtmp->push_back( (MuonCharge->at(mu)<0)?13:-13 );
	}
	
	if(nPassed!=2)                           return false; // 2 muons ???????????????????????????????????????????
	if(CHARGEtmp->at(0)*CHARGEtmp->at(1)>=0) return false; // opposite charge
	
	pa->SetPxPyPzE(PXtmp->at(0)*MeV2TeV,PYtmp->at(0)*MeV2TeV,PZtmp->at(0)*MeV2TeV,Etmp->at(0)*MeV2TeV);
	pb->SetPxPyPzE(PXtmp->at(1)*MeV2TeV,PYtmp->at(1)*MeV2TeV,PZtmp->at(1)*MeV2TeV,Etmp->at(1)*MeV2TeV);
	
	if(imass(pa,pb)<0.06)                    return false; // invariant mass
	
	E = Etmp;
	PX = PXtmp;
	PY = PYtmp;
	PZ = PZtmp;
	PT = PTtmp;
	PHI = PHItmp;
	ETA = ETAtmp;
	CHARGE = CHARGEtmp;
	ID = IDtmp;
	IMASS = imass(pa,pb);
	if     (REFNAME=="CosThetaCS") COSTH = cosThetaCollinsSoper( pa, CHARGE->at(0), pb, CHARGE->at(1) );
	else if(REFNAME=="CosThetaHE") COSTH = cosThetaBoost( pa, CHARGE->at(0), pb, CHARGE->at(1) );
	else COSTH = 0.;
	
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void Scale(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for(int i=0 ; i<=h->GetNbinsX()+1 ; i++)
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
	}
}

void ScaleWerrors(TH1D* h, double d)
{ 
	/// scale including over/underflow
	for ( int i=0 ; i<=h->GetNbinsX()+1 ; i++ )
	{ 
		h->SetBinContent(i,h->GetBinContent(i)*d);
		h->SetBinError(i,h->GetBinError(i)*d);
	}
}


///////////////////////////////////////////////////////////////////////////////////////
// The pdf to be fitted ///////////////////////////////////////////////////////////////
// First argument needs to be a pointer in order to plot with the TF1 class.
double cosThetaPdf(double* xPtr, double par[])
{
	double x   = *xPtr;
	double pdf = 1.;
	double A4  = par[0];

	if (fabs(x)<=1.)
	{
		// see: http://arxiv.org/PS_cache/arxiv/pdf/1004/1004.1649v1.pdf
		// pdf_CollinsSoper = (1/N)*dN/dcosThetaCS = (3/8)*((1+0.5*A0) + A4*cosThetaCS + (1-3/2*A0)*cosTetaCS^2)
		// pdf_Helicity     = (1/N)*dN/dcosThetaHE = (3/8)*(1+cosTetaHE^2 + Afb*cosThetaHE)
		// if A0=~0 then pdf_CollinsSoper = pdf_Helicity (in the Z/Z'/Z* cases, it is approximately true)
		pdf  = (3./8.)*(1. + x*x + A4*x);
		if (pdf > 0) { return pdf; }
		else { cout << "warning:  pdf<=0, pdf=" << pdf << endl; return 1e-30; }
	}
	else { cout << "warning:  x<-1 || x>+1, x=" << x << endl; return 1e-30; }
}

// fcn passes back f = - 2*ln(L), the function to be minimized.
void fcn(int& npar, double* deriv, double& f, double par[], int flag)
{	
	vector<double> xVec = *VVCOSTH[CURRENTBIN]; // VVCOSTH is global

	int n = xVec.size();
	double lnL = 0.;
	double x   = 0.;
	double pdf = 0.;
	for (int i=0; i<n; i++){
		x = xVec[i];
		pdf = cosThetaPdf(&x, par);
		if (pdf > 0.) {
			lnL += log(pdf); // need positive f
		}
		else { cout << "WARNING -- pdf is negative!!!" << endl; }
	}
	f = -2.0 * lnL; // factor of -2 so minuit gets the errors right
}
///////////////////////////////////////////////////////////////////////////////////////


inline void fill(TTree* t, Int_t Nmax, TH1D* h, TH1D* hMass)
{
	for(int v=0 ; v<(int)VVCOSTH.size() ; v++) VVCOSTH[v]->clear();
	if (t==0) return;
	
	TAxis* xaxis = h->GetXaxis();
	
	Int_t N = (Nmax > t->GetEntries()) ? t->GetEntries() : Nmax;
	
	for (Long64_t l64t_jentry=0 ; l64t_jentry<t->GetEntries() ; l64t_jentry++)
	{
		///////////////////////////////////////////////////
		// getEntry already include the basic selection ///
		if( !getEntry(t,l64t_jentry) ) continue; //////////
		///////////////////////////////////////////////////
		
		pa->SetPxPyPzE(PX->at(0)*MeV2TeV,PY->at(0)*MeV2TeV,PZ->at(0)*MeV2TeV,E->at(0)*MeV2TeV);
		pb->SetPxPyPzE(PX->at(1)*MeV2TeV,PY->at(1)*MeV2TeV,PZ->at(1)*MeV2TeV,E->at(1)*MeV2TeV);
		
		double mHat = imass(pa,pb);
		
		int bin = (int)xaxis->FindBin((Double_t)mHat);
		if(bin<=0 || bin>(int)VVCOSTH.size()) continue;
		
		if     (REFNAME=="CosThetaCS") COSTH = cosThetaCollinsSoper( pa, CHARGE->at(0), pb, CHARGE->at(1) );
		else if(REFNAME=="CosThetaHE") COSTH = cosThetaBoost( pa, CHARGE->at(0), pb, CHARGE->at(1) );
		else COSTH = 0.;
		
		
		////////////////////////////////////////////////////////////////////////////
		// fill in the vectors (for the fit) only the N events corresponding to ////
		// the desired luminosity //////////////////////////////////////////////////
		if(l64t_jentry<N) //////////////////////////////////////////////////////////
		{                 //////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////
			// fill the appropriate vector with cos(theta) /////////////////////////
			VVCOSTH[bin-1]->push_back(COSTH); //////////////////////////////////////
			////////////////////////////////////////////////////////////////////////
		} //////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////
		// fill the invariant mass histo //////
		// fill all the events that are in ////
		// the sample and afterwards, scale ///
		// the histograms to the luminosity /// 
		hMass->Fill(mHat); ////////////////////
		///////////////////////////////////////
	}
}

void minimize(double guess, double& A4, double& dA4)
{
	int npar = 1;      // the number of parameters
	TMinuit minuit(npar);
	minuit.SetFCN(fcn);

	double par[npar];        // the start values
	double stepSize[npar];   // step sizes
	double minVal[npar];     // minimum bound on parameter
	double maxVal[npar];     // maximum bound on parameter
	string parName[npar];

	par[0]      = guess; 
	stepSize[0] = 1e-4;
	minVal[0]   = -1.;
	maxVal[0]   = +1.;
	parName[0]  = "A4";

	for (int i=0; i<npar; i++)
	{
		minuit.DefineParameter(i, parName[i].c_str(), par[i], stepSize[i], minVal[i], maxVal[i]);
	}

	// Do the minimization!
	minuit.Migrad(); // Minuit's best minimization algorithm
	double outpar[npar], err[npar];
	for (int i=0; i<npar; i++)
	{
		minuit.GetParameter(i,outpar[i],err[i]);
	}
	
	/*
	TF1* func = new TF1("pdf", cosThetaPdf, -1., 1., npar);
	func->SetParameters(outpar);
	func->SetLineStyle(1);
	func->SetLineColor(1);
	func->SetLineWidth(1);
	func->GetXaxis()->SetTitle("cos#left(#theta^{*}#right)");
	func->GetYaxis()->SetTitle("pdf");
	*/
	
	A4  = 0.;
	dA4 = 0.;
	minuit.GetParameter(0,A4,dA4);
}


////////////////////////////////////////////////////////////////////////////////
double merge(string sMergedFileName, string dir, vector<string>& vsNames)
{
	TList* list = new TList();
	string path;
	vector<TFile*> vf;
	
	double N = 0.;
	TTree* t = NULL;
	
	for(int i=0 ; i<(int)vsNames.size() ; i++)
	{
		path = dir + vsNames[i];
		cout << "path=" << path << endl;
		vf.push_back( new TFile( path.c_str(),"READ") );
		list->Add( (TTree*)vf[i]->Get("FastTree") );
		
		t = (TTree*)vf[i]->Get("FastTree");
		N += t->GetEntries();
	}
	
	cout << "Merging trees...patience..." << endl;
	TFile* mergedFile = new TFile( sMergedFileName.c_str(), "RECREATE");
	TTree::MergeTrees(list);
	mergedFile->Write();
	mergedFile->Close();
	cout << "written file: " << sMergedFileName << "\n\n" << endl;
	
	// clean
	for(int i=0 ; i<(int)vf.size() ; i++) delete vf[i];
	vf.clear();
	delete list;
	delete mergedFile;
	
	cout << "N events = " << N << endl;
	
	return N;
}
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
void execute()
{
	ofstream* of = new ofstream;
	of->open("test.tmp");
	
	
	// logarithmic boundries and bins of histograms
	Double_t logMmin;
	Double_t logMmax;
	Double_t logMbinwidth;
	
	const int imass_asymmetry_nbins = 8; //14;
	double    imass_asymmetry_min   = 120.*GeV2TeV;
	double    imass_asymmetry_max   = 1620.*GeV2TeV;
	const int ncol_pads   = 2; // = imass_asymmetry_nbins/nrow_pads !!!
	const int nrow_pads   = 50; // = imass_asymmetry_nbins/ncol_pads !!!
	logMmin     = log10(imass_asymmetry_min);
	logMmax     = log10(imass_asymmetry_max);
	Double_t imass_asymmetry_bins[imass_asymmetry_nbins+1];
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_asymmetry_nbins );
	imass_asymmetry_bins[0] = imass_asymmetry_min;
	for(Int_t i=1 ; i<=imass_asymmetry_nbins ; i++) imass_asymmetry_bins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	/*
	const int imass_asymmetry_nbins = 12;
	const int ncol_pads   = 2; // = imass_asymmetry_nbins/nrow_pads !!!
	const int nrow_pads   = 6; // = imass_asymmetry_nbins/ncol_pads !!!
	double imass_asymmetry_min   = 72.62*GeV2TeV;
	double imass_asymmetry_max   = 381.09*GeV2TeV;
	Double_t imass_asymmetry_bins[imass_asymmetry_nbins+1] = {72.62*GeV2TeV, 83.37*GeV2TeV, 95.73*GeV2TeV, 109.91*GeV2TeV,
									126.19*GeV2TeV, 144.89*GeV2TeV, 166.35*GeV2TeV, 191.00*GeV2TeV,
									219.30*GeV2TeV, 251.79*GeV2TeV, 289.09*GeV2TeV, 331.92*GeV2TeV, 381.09*GeV2TeV};
	//imass_asymmetry_bins = {2.00*GeV, 2.30*GeV, 2.64*GeV, 3.03*GeV, 3.48*GeV, 3.99*GeV, 4.58*GeV, 5.26*GeV, 6.04*GeV, 6.93*GeV, 7.96*GeV, 9.14*GeV, 10.50*GeV, 12.05*GeV, 13.84*GeV, 15.89*GeV, 18.24*GeV, 20.94*GeV, 24.05*GeV, 27.61*GeV, 31.70*GeV, 36.39*GeV, 41.79*GeV, 47.98*GeV, 55.08*GeV, 63.25*GeV, 72.62*GeV, 83.37*GeV, 95.73*GeV, 109.91*GeV, 126.19*GeV, 144.89*GeV, 166.35*GeV, 191.00*GeV, 219.30*GeV, 251.79*GeV, 289.09*GeV, 331.92*GeV, 381.09*GeV, 437.55*GeV, 502.38*GeV, 576.81*GeV, 662.26*GeV, 760.38*GeV, 873.03*GeV, 1002.37*GeV, 1150.88*GeV, 1321.39*GeV, 1517.16*GeV, 1741.93*GeV, 2000.00*GeV};
	*/
	
	const int imass_nbins = 40;
	double    imass_min   = 120.*GeV2TeV;
	double    imass_max   = 1620.*GeV2TeV;
	logMmin     = log10(imass_min);
	logMmax     = log10(imass_max);
	Double_t imass_bins[imass_nbins+1];
	logMbinwidth = (Double_t)( (logMmax-logMmin)/(Double_t)imass_nbins );
	imass_bins[0] = imass_min;
	for(Int_t i=1 ; i<=imass_nbins ; i++) imass_bins[i] = TMath::Power( 10,(logMmin + i*logMbinwidth) );
	
	
	
	//////////////////////////////////////////////////////////////////////////////////
	// fill the vector with new vector<double> pointers //////////////////////////////
	for(int i=0 ; i<imass_asymmetry_nbins ; i++) VVCOSTH.push_back(new vector<double>);
	//////////////////////////////////////////////////////////////////////////////////
	


	string dir   = "/data/hod/ATLFAST/26032011/";
	string hDir  = "";
	string hName = "Afb";
	string xTitle = "#hat{m}_{#mu#mu} TeV";
	string yTitle= "A_{FB}";

	string hNameFixed = hName;

	gStyle->SetOptStat(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	//gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetPaperSize(20,26);
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.12);
	Int_t font=42;
	Double_t tsize=0.04;
	gStyle->SetTextFont(font);
	gStyle->SetTextSize(tsize);
	gStyle->SetLabelFont(font,"x");
	gStyle->SetTitleFont(font,"x");
	gStyle->SetLabelFont(font,"y");
	gStyle->SetTitleFont(font,"y");
	gStyle->SetLabelFont(font,"z");
	gStyle->SetTitleFont(font,"z");
	gStyle->SetLabelSize(tsize,"x");
	gStyle->SetTitleSize(tsize,"x");
	gStyle->SetLabelSize(tsize,"y");
	gStyle->SetTitleSize(tsize,"y");
	gStyle->SetLabelSize(tsize,"z");
	gStyle->SetTitleSize(tsize,"z");
	gStyle->SetStatBorderSize(0);
	gStyle->SetStatColor(0);
	gStyle->SetStatX(0);
	gStyle->SetStatY(0);
	gStyle->SetStatFont(42);
	gStyle->SetStatFontSize(0);
	gStyle->SetOptStat(0);
	gStyle->SetStatW(0);
	gStyle->SetStatH(0);
	
	
	TLegend* leg_mHat = new TLegend(0.1557789,0.1818182,0.3806533,0.458042,NULL,"brNDC");
	leg_mHat->SetFillColor(kWhite);
	
	TLegend* leg_histos = new TLegend(0.85, 0.15, 0.97, 0.45,NULL,"brNDC");
	leg_histos->SetFillColor(kWhite);
	
	
	stringstream strm;
	string str;
	
	strm.clear();
	str.clear();
	strm << L;
	strm >> str;
	string lumilabel = "#intLdt~" + str + " fb^{-1}";
	TPaveText* pvtxt_lumi = new TPaveText(0.1620603,0.458042,0.3140704,0.5716783,"brNDC");
	pvtxt_lumi->SetFillColor(kWhite);
	TText* txt  = pvtxt_lumi->AddText( lumilabel.c_str() );
	
	TPaveText* pvtxt_atlfast = new TPaveText(0.2537688,0.8076923,0.3932161,0.9090909,"brNDC");
	pvtxt_atlfast->SetFillColor(0);
	pvtxt_atlfast->SetTextFont(42);
	txt = pvtxt_atlfast->AddText("#bf{#it{ATLFAST}}");
	pvtxt_atlfast->Draw();
	
	string cName = "cnv_" + hNameFixed;
	TCanvas* cnv = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	
	TPad *pad_mHat = new TPad("pad_mHat","",0,0,1,1);
	pad_mHat->SetFillColor(kWhite);
	pad_mHat->SetTicky(0);
	pad_mHat->SetLogy();
	if(doLogx) pad_mHat->SetLogx();

	TPad *pad_Afb  = new TPad("pad_Afb", "",0,0,1,1);
	//pad_Afb->SetGridy();
	pad_Afb->SetTicky(0);
	pad_Afb->SetTickx(1);
	pad_Afb->SetFillStyle(0);
	pad_Afb->SetFrameFillStyle(4000); //will be transparent
	pad_Afb->SetFrameFillColor(0);
	if(doLogx) pad_Afb->SetLogx();
	
	string path = "";
	string sProc = "";
	string channel = "";
	
	
	
	///////////////////////////////////////////////
	// Z0 /////////////////////////////////////////
	TH1D* hMZ0;
	if(doLogM) hMZ0  = new TH1D("mHat_Z0","mHat_Z0", imass_nbins, imass_bins );
	else       hMZ0  = new TH1D("mHat_Z0","mHat_Z0", imass_nbins, imass_min, imass_max );
	hMZ0->SetTitle("");
	hMZ0->SetYTitle("Events");
	hMZ0->SetLineColor(kAzure-5);
	hMZ0->SetLineWidth(1);
	hMZ0->SetLineStyle(2);
	leg_mHat->AddEntry( hMZ0, "#gamma/Z^{0}: Events", "l");
	
	channel = "#gamma/Z^{0}: A_{FB} fit";
	TH1D* hAfbZ0;
	if(doLogM) hAfbZ0 = new TH1D("Afb_Z0","Afb_Z0", imass_asymmetry_nbins, imass_asymmetry_bins );
	else       hAfbZ0 = new TH1D("Afb_Z0","Afb_Z0", imass_asymmetry_nbins, imass_asymmetry_min, imass_asymmetry_max );
	hAfbZ0->SetLineColor(kAzure-5);
	hAfbZ0->SetFillColor(kAzure-5);
	hAfbZ0->SetFillStyle(3003);
	hAfbZ0->SetLineWidth(1);
	hAfbZ0->SetMarkerSize(0);
	hAfbZ0->SetMarkerColor(0);
	hAfbZ0->SetTitle("");
	hAfbZ0->SetXTitle( xTitle.c_str() );
	hAfbZ0->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hAfbZ0, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// Z' /////////////////////////////////////////
	TH1D* hMZP;
	if(doLogM) hMZP  = new TH1D("mHat_ZP","mHat_ZP", imass_nbins, imass_bins );
	else       hMZP  = new TH1D("mHat_ZP","mHat_ZP", imass_nbins, imass_min, imass_max );
	hMZP->SetTitle("");
	hMZP->SetYTitle("Events");
	hMZP->SetLineColor(kRed);
	hMZP->SetLineWidth(1);
	hMZP->SetLineStyle(3);
	leg_mHat->AddEntry( hMZP, "1 TeV Z'_{SSM}: Events", "l");
	
	channel = "1 TeV Z'_{SSM}: A_{FB} fit";
	TH1D* hAfbZP;
	if(doLogM) hAfbZP = new TH1D("Afb_ZP","Afb_ZP", imass_asymmetry_nbins, imass_asymmetry_bins );
	else       hAfbZP = new TH1D("Afb_ZP","Afb_ZP", imass_asymmetry_nbins, imass_asymmetry_min, imass_asymmetry_max );
	hAfbZP->SetLineColor(kRed);
	hAfbZP->SetFillColor(kRed);
	hAfbZP->SetFillStyle(3017);
	hAfbZP->SetLineWidth(1);
	hAfbZP->SetMarkerSize(0);
	hAfbZP->SetMarkerColor(0);
	hAfbZP->SetTitle("");
	hAfbZP->SetXTitle( xTitle.c_str() );
	hAfbZP->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hAfbZP, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// KK /////////////////////////////////////////
	TH1D* hMKK;
	if(doLogM) hMKK  = new TH1D("mHat_KK","mHat_KK", imass_nbins, imass_bins );
	else       hMKK  = new TH1D("mHat_KK","mHat_KK", imass_nbins, imass_min, imass_max );
	hMKK->SetTitle("");
	hMKK->SetYTitle("Events");
	hMKK->SetLineColor(kBlack);
	hMKK->SetLineWidth(1);
	hMKK->SetLineStyle(1);
	leg_mHat->AddEntry( hMKK, "1 TeV #gamma_{KK}/Z_{KK}: Events", "l");
	
	channel = "1 TeV #gamma_{KK}/Z_{KK}: A_{FB} fit";
	TH1D* hAfbKK;
	if(doLogM) hAfbKK = new TH1D("Afb_KK","Afb_KK", imass_asymmetry_nbins, imass_asymmetry_bins );
	else       hAfbKK = new TH1D("Afb_KK","Afb_KK", imass_asymmetry_nbins, imass_asymmetry_min, imass_asymmetry_max );
	hAfbKK->SetLineColor(kBlack);
	hAfbKK->SetFillColor(kBlack);
	hAfbKK->SetFillStyle(3018);
	hAfbKK->SetLineWidth(1);
	hAfbKK->SetMarkerSize(0);
	hAfbKK->SetMarkerColor(0);
	hAfbKK->SetTitle("");
	hAfbKK->SetXTitle( xTitle.c_str() );
	hAfbKK->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hAfbKK, channel.c_str(), "f");
	
	Int_t maxEvents = 0;
	Int_t lumEvents = 0;
	vector<string> vsNames;
	string sMergedFileName; 
	TAxis *xaxis = hAfbZ0->GetXaxis();
	double a4  = 0.;
	double da4 = 0.;
	double afb  = 0.;
	double dafb = 0.;
	double guess = -0.1;

	ISZ0 = true;
	ISZP = false;
	ISKK = false;
	vsNames.clear();
	sMergedFileName = "Z0.merged.root";
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00001.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00002.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00003.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00004.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00005.pool.root");
	nevents_Z0 = merge(sMergedFileName, dir, vsNames);
	//sMergedFileName = "MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00001.pool.root";
	TFile* fZ0 = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_Z0 = (TTree*)fZ0->Get("FastTree");
	initTree(tree_Z0);
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = true;
	ISKK = false;
	lumEvents = (Int_t)(L*ifb2imb*sigma_Z0);
	maxEvents = (FITWITHALLEVENTS) ? tree_Z0->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_Z0->GetEntries() << " events" << endl;
	fill(tree_Z0, maxEvents, hAfbZ0, hMZ0); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbZ0->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		//if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbZ0->SetBinContent(b,afb);
		hAfbZ0->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbZ0->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
		(*of) << "Z0[currentbin=" << CURRENTBIN << "][bin=" << b << "]: " << VVCOSTH[CURRENTBIN]->size() << ", from histo: " << hMZ0->GetBinContent(b) << endl;
	}
	(*of) << endl;
	
	
	vsNames.clear();
	sMergedFileName = "ZprimeSSM.merged.root";
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00001.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00002.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00003.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00004.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00005.pool.root");
	nevents_ZP = merge(sMergedFileName, dir, vsNames);
	//sMergedFileName = "MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00001.pool.root";
	TFile* fZP = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_ZP = (TTree*)fZP->Get("FastTree");
	initTree(tree_ZP);
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = false;
	ISKK = true;
	lumEvents = (Int_t)(L*ifb2imb*sigma_ZP);
	maxEvents = (FITWITHALLEVENTS) ? tree_ZP->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_ZP->GetEntries() << " events" << endl;
	fill(tree_ZP, maxEvents, hAfbZP, hMZP); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbZP->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		//if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbZP->SetBinContent(b,afb);
		hAfbZP->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbZP->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
		(*of) << "ZP[currentbin=" << CURRENTBIN << "][bin=" << b << "]: " << VVCOSTH[CURRENTBIN]->size() << ", from histo: " << hMZP->GetBinContent(b) << endl;
	}
	(*of) << endl;
	
	
	vsNames.clear();
	sMergedFileName = "KK.merged.root";
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00001.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00002.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00003.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00004.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00005.pool.root");
	nevents_KK = merge(sMergedFileName, dir, vsNames);
	//sMergedFileName = "MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00001.pool.root";
	TFile* fKK = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_KK = (TTree*)fKK->Get("FastTree");
	initTree(tree_KK);
	a4   = 0.;
	da4  = 0.;
	afb  = 0.;
	dafb = 0.;
	guess = -0.1;
	ISZ0 = false;
	ISZP = false;
	ISKK = true;
	lumEvents = (Int_t)(L*ifb2imb*sigma_KK);
	maxEvents = (FITWITHALLEVENTS) ? tree_KK->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_KK->GetEntries() << " events" << endl;
	fill(tree_KK, maxEvents, hAfbKK, hMKK); // the VVCOSTH vectors are full
	for(Int_t b=1 ; b<=hAfbKK->GetNbinsX() ; b++)
	{
		// norm to bin width
		//hMZ0->SetBinContent(b, hMZ0->GetBinContent(b)/hMZ0->GetBinWidth(b));
		CURRENTBIN = (unsigned int)(b-1);
		//if((int)VVCOSTH[CURRENTBIN]->size()<minEntriesDATA) continue;
		minimize(guess, a4, da4);
		afb = (3./8.)*a4;
		dafb = (3./8.)*da4;
		guess = a4;
		hAfbKK->SetBinContent(b,afb);
		hAfbKK->SetBinError(b,dafb);
		cout << "mHat["<< b << "/" << hAfbKK->GetNbinsX() << "]=" << xaxis->GetBinCenter(b) << ", Afb=" << afb << " +- " << dafb << "\n" << endl;
		(*of) << "KK[currentbin=" << CURRENTBIN << "][bin=" << b << "]: " << VVCOSTH[CURRENTBIN]->size() << ", from histo: " << hMKK->GetBinContent(b) << endl;
	}
	(*of) << endl;
	
	
	
	
	TH1D* hMKKerr = (TH1D*)hMKK->Clone("");
	hMKKerr->SetMarkerStyle(1);
	hMKKerr->SetMarkerSize(1);
	
	TH1D* hMZPerr = (TH1D*)hMZP->Clone("");
	hMZPerr->SetMarkerStyle(1);
	hMZPerr->SetMarkerSize(1);
	
	TH1D* hMZ0err = (TH1D*)hMZ0->Clone("");
	hMZ0err->SetMarkerStyle(1);
	hMZ0err->SetMarkerSize(1);
	
	
	// scale all to lumi
	Scale(hMZ0, (L*ifb2imb)*(sigma_Z0/nevents_Z0));
	Scale(hMZP, (L*ifb2imb)*(sigma_ZP/nevents_ZP));
	Scale(hMKK, (L*ifb2imb)*(sigma_KK/nevents_KK));
	
	ScaleWerrors(hMZ0err, (L*ifb2imb)*(sigma_Z0/nevents_Z0));
	ScaleWerrors(hMZPerr, (L*ifb2imb)*(sigma_ZP/nevents_ZP));
	ScaleWerrors(hMKKerr, (L*ifb2imb)*(sigma_KK/nevents_KK));
	
	
	
	
	pad_mHat->Draw();
	pad_mHat->cd();
	//hMKK->GetYaxis()->SetRangeUser(1,1.5*hMKK->GetMaximum());
	hMKK->SetMaximum(1.5*hMKK->GetMaximum());
	hMKK->SetMinimum((hMZ0->GetMinimum()<=0) ? 1. : 0.5*hMZ0->GetMinimum());
	hMKK->Draw();
	hMKKerr->Draw("SAMES");
	hMKK->GetXaxis()->SetMoreLogLabels(); 
	hMKK->GetXaxis()->SetNoExponent();
	hMKKerr->GetXaxis()->SetMoreLogLabels(); 
	hMKKerr->GetXaxis()->SetNoExponent(); 
	hMZ0->Draw("SAMES");
	hMZ0err->Draw("SAMES");
	hMZ0->GetXaxis()->SetMoreLogLabels(); 
	hMZ0->GetXaxis()->SetNoExponent();
	hMZ0err->GetXaxis()->SetMoreLogLabels(); 
	hMZ0err->GetXaxis()->SetNoExponent(); 
	hMZP->Draw("SAMES");
	hMZPerr->Draw("SAMES");
	hMZP->GetXaxis()->SetMoreLogLabels(); 
	hMZP->GetXaxis()->SetNoExponent(); 
	hMZPerr->GetXaxis()->SetMoreLogLabels(); 
	hMZPerr->GetXaxis()->SetNoExponent(); 

	cnv->cd();

	pad_Afb->Draw();
	pad_Afb->cd();
	hAfbKK->GetYaxis()->SetRangeUser(minAsymmetry,maxAsymmetry);
	hAfbKK->Draw("E5 Y+");
	hAfbKK->GetXaxis()->SetMoreLogLabels(); 
	hAfbKK->GetXaxis()->SetNoExponent(); 
	hAfbZ0->Draw("E5 Y+ SAMES");
	hAfbZ0->GetXaxis()->SetMoreLogLabels(); 
	hAfbZ0->GetXaxis()->SetMoreLogLabels(); 
	//hAfbZ0->Draw("e1x0SAMES");
	hAfbZP->Draw("E5 Y+ SAMES");
	hAfbZP->GetXaxis()->SetMoreLogLabels(); 
	hAfbZP->GetXaxis()->SetMoreLogLabels(); 
	pvtxt_lumi->Draw("SAMES");
	pvtxt_atlfast->Draw("SAMES");
	leg_mHat->Draw("SAMES");
	TLine* lUnit = new TLine(imass_asymmetry_min,0.,imass_asymmetry_max,0.);
	lUnit->SetLineColor(kBlack);
	lUnit->SetLineStyle(2);
	//lUnit->Draw("SAMES");
	//pad_Afb->RedrawAxis();
	
	cnv->cd();
	
	pad_mHat->cd();
	pad_mHat->RedrawAxis();
	pad_mHat->Update();

	cnv->Update();
	
	TString fName = (DOSMEAR) ? (TString)hNameFixed + ".smear.plot"  :  (TString)hNameFixed + ".true.plot";
	cnv->SaveAs(fName+".eps");
	cnv->SaveAs(fName+".C");
	cnv->SaveAs(fName+".root");
	cnv->SaveAs(fName+".png");
	
	of->close();
}

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
#include <TGraphAsymmErrors.h>

using namespace std;

// Declare pointer to data as global (not elegant but TMinuit needs this).
vector<TLorentzVector*> vLV;
Float_t IMASS;
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

TLorentzVector* paGen = new TLorentzVector();
TLorentzVector* pbGen = new TLorentzVector();
int iaGen, ibGen;

vector<bool>* muQAflag = new vector<bool>;

TLorentzVector m_pTmp;

////////////////////////////////////////////////////////////////////////////
// definitions /////////////////////////////////////////////////////////////
const double GeV2TeV  = 1.e-3;
const double MeV2TeV  = 1.e-6;
const double GeV2MeV  = 1.e+3;
const double muonMass = 0.105658367; // GeV

const double sigma_KK   = 7.68E-09; // mb
double nevents_KK       = 1500000.;
double neventsGen_KK    = 50000.;
const double sigma_ZP   = 7.88E-09; // mb
double nevents_ZP       = 1500000.;
double neventsGen_ZP    = 50000.;
const double sigma_Z0   = 7.96E-09; // mb
double nevents_Z0       = 1500000.;
double neventsGen_Z0    = 50000.;

const double ifb2imb = 1.e+12;
const double L       = 5.; // 1/fb

const bool FITWITHALLEVENTS = false; // false if only fit to N events for a given luminosity (see L above)
const bool doLogM           = true;
const bool doLogx           = true;
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


////////////////////////
// truth tree //////////////////////////
Int_t           EventNumberGen;
UInt_t          NPar;
vector<long>    *Type;
vector<long>    *KMothNt;
vector<float>   *PtGen;
vector<float>   *PhiGen;
vector<float>   *EtaGen;
vector<float>   *MGen;
vector<float>   *Charge;
vector<long>    *GenStat;
vector<long>    *GenRef;

TBranch        *b_EventNumberGen;   //!
TBranch        *b_NPar;   //!
TBranch        *b_Type;   //!
TBranch        *b_KMothNt;   //!
TBranch        *b_PtGen;   //!
TBranch        *b_PhiGen;   //!
TBranch        *b_EtaGen;   //!
TBranch        *b_MGen;   //!
TBranch        *b_Charge;   //!
TBranch        *b_GenStat;   //!
TBranch        *b_GenRef;   //!
////////////////////////



///////////////////////////////////////////////////////////////////////
double error_poisson_up(double data)
{
	double y1 = data + 1.0;
	double d = 1.0 - 1.0/(9.0*y1) + 1.0/(3*TMath::Sqrt(y1));
	return y1*d*d*d-data;
}

double error_poisson_down(double data)
{
	double y = data;
	if (y == 0.0) return 0.0;
	double d = 1.0 - 1.0/(9.0*y) - 1.0/(3.0*TMath::Sqrt(y));
	return data-y*d*d*d;
}

TGraphAsymmErrors* GetPoissonizedGraph(TH1D* histo, bool isXerr)
{
	TGraphAsymmErrors* graph = new TGraphAsymmErrors();
	int j=0;
	for (int i=1;i<=histo->GetNbinsX();++i)
	{
		if (histo->GetBinContent(i)!=0)
		{ 
			graph->SetPoint(j, histo->GetBinCenter(i), histo->GetBinContent(i));
			graph->SetPointError(
					j,
					(isXerr) ? histo->GetBinWidth(i)/2. : 0.,
					(isXerr) ? histo->GetBinWidth(i)/2. : 0.,
					error_poisson_down(histo->GetBinContent(i)),
					error_poisson_up(histo->GetBinContent(i))
					    );
			++j;
		}
	}
	return graph;
}
///////////////////////////////////////////////////////////////////////



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
inline void initGenTree(TTree* t)
{
	Type = 0;
	KMothNt = 0;
	PtGen = 0;
	PhiGen = 0;
	EtaGen = 0;
	MGen = 0;
	Charge = 0;
	GenStat = 0;
	GenRef = 0;
	
	t->SetBranchAddress("EventNumber", &EventNumberGen, &b_EventNumberGen);
	t->SetBranchAddress("NPar", &NPar, &b_NPar);
	t->SetBranchAddress("Type", &Type, &b_Type);
	t->SetBranchAddress("KMothNt", &KMothNt, &b_KMothNt);
	t->SetBranchAddress("PtGen", &PtGen, &b_PtGen);
	t->SetBranchAddress("PhiGen", &PhiGen, &b_PhiGen);
	t->SetBranchAddress("EtaGen", &EtaGen, &b_EtaGen);
	t->SetBranchAddress("MGen", &MGen, &b_MGen);
	t->SetBranchAddress("Charge", &Charge, &b_Charge);
	t->SetBranchAddress("GenStat", &GenStat, &b_GenStat);
	t->SetBranchAddress("GenRef", &GenRef, &b_GenRef);
}

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


inline void getGenEntry(TTree* t, Long64_t l64t_entry)
{
	t->GetEntry(l64t_entry);
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

inline void fill(TTree* t, TTree* tGen, Int_t Nmax, TH1D* hMhatRes, TH1D* hpTRes, TH1D* hdR)
{
	if(t==0)    return;
	if(tGen==0) return;
		
	Int_t N = (Nmax > t->GetEntries()) ? t->GetEntries() : Nmax;
	
	for (Long64_t l64t_jentry=0 ; l64t_jentry<t->GetEntries() ; l64t_jentry++)
	{
		///////////////////////////////////////////////////
		// getEntry already include the basic selection ///
		if( !getEntry(t,l64t_jentry) ) continue; //////////
		//cout << "\nEventNumber = " << EventNumber << endl; //
		getGenEntry(tGen,l64t_jentry); /////////////////////
		//cout << "EventNumberGen = " << EventNumberGen << endl; //
		///////////////////////////////////////////////////
		
		pa->SetPxPyPzE(PX->at(0)*MeV2TeV,PY->at(0)*MeV2TeV,PZ->at(0)*MeV2TeV,E->at(0)*MeV2TeV);
		pb->SetPxPyPzE(PX->at(1)*MeV2TeV,PY->at(1)*MeV2TeV,PZ->at(1)*MeV2TeV,E->at(1)*MeV2TeV);
		
		double mHat = imass(pa,pb);
		
		iaGen = -1;
		ibGen = -1;
		bool isa = false;
		bool isb = false;
		double dRaMin = 10000.;
		double dRbMin = 10000.;
		double dRMin  = 10000.;
		double dRthresh = 0.2;
		bool afound = false;
		bool bfound = false;
		double dRaFound;
		double dRbFound;
		for (Int_t p=0 ; p<NPar ; p++) 
		{
			// muon from Z mother
			//if(abs(Type->at(p)==13) && Type->at(KMothNt->at(p))==23)
			if(abs(Type->at(p))==13) 
			{
				double dRa = sqrt( (pa->Phi()-PhiGen->at(p))*(pa->Phi()-PhiGen->at(p)) + (pa->Eta()-EtaGen->at(p))*(pa->Eta()-EtaGen->at(p)) );
				double dRb = sqrt( (pb->Phi()-PhiGen->at(p))*(pb->Phi()-PhiGen->at(p)) + (pb->Eta()-EtaGen->at(p))*(pb->Eta()-EtaGen->at(p)) );
				
				double dR = (dRa<dRb) ? dRa : dRb;
				
				if(dR<dRthresh)
				{
					isa = (dRa<dRb) ? true : false; 
					isb = (dRb<dRa) ? true : false;
					string s;
					if(isa)
					{
						iaGen = p;
						s="a";
						paGen->SetPtEtaPhiM(PtGen->at(p)*MeV2TeV, EtaGen->at(p), PhiGen->at(p), MGen->at(p)*MeV2TeV);
						dRaFound = dR;
						afound = true;
					}
					if(isb)
					{
						ibGen = p;
						s="b";
						pbGen->SetPtEtaPhiM(PtGen->at(p)*MeV2TeV, EtaGen->at(p), PhiGen->at(p), MGen->at(p)*MeV2TeV);
						dRbFound = dR;
						bfound = true;
					}
				}
			}
		}
		
		if(afound  &&  bfound  &&  iaGen!=ibGen)
		{
			//cout << "GenStat->at(iaGen)=" << GenStat->at(iaGen) << ", GenStat->at(ibGen)=" << GenStat->at(ibGen) << endl;
		
			double mHatGen = imass(paGen,pbGen);
			if(mHatGen!=0.) hMhatRes->Fill( (mHat-mHatGen)/mHatGen );
			
			double pTtru = (Charge->at(iaGen)<0  &&  Charge->at(ibGen)>0) ? paGen->Pt() : pbGen->Pt();
			double pTrec = (CHARGE->at(0)<0  &&  CHARGE->at(1)>0) ? pa->Pt() : pb->Pt();
			if(Charge->at(iaGen)*CHARGE->at(0)<0) cout << "CHARGE FLIP (a)!" << endl;
			if(Charge->at(ibGen)*CHARGE->at(1)<0) cout << "CHARGE FLIP (b)!" << endl;
			if(pTtru!=0. && pTrec!=0.) hpTRes->Fill((1./pTrec-1./pTtru)/(1./pTtru));
			
			double dRFound = (Charge->at(iaGen)<0  &&  Charge->at(ibGen)>0) ? dRaFound : dRbFound;
			hdR->Fill(dRFound);
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
double merge(string sMergedFileName, string dir, vector<string>& vsNames, string sTreeName)
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
		list->Add( (TTree*)vf[i]->Get(sTreeName.c_str()) );
		
		t = (TTree*)vf[i]->Get(sTreeName.c_str());
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
	Double_t logdRmin;
	Double_t logdRmax;
	Double_t logdRbinwidth;
	
	const int dr_nbins = 100;
	double    dr_min   = 1.e-10;
	double    dr_max   = 0.3;
	logdRmin     = log10(dr_min);
	logdRmax     = log10(dr_max);
	Double_t dr_bins[dr_nbins+1];
	logdRbinwidth = (Double_t)( (logdRmax-logdRmin)/(Double_t)dr_nbins );
	dr_bins[0] = dr_min;
	for(Int_t i=1 ; i<=dr_nbins ; i++) dr_bins[i] = TMath::Power( 10,(logdRmin + i*logdRbinwidth) );
	


	string dir   = "/data/hod/ATLFAST/26032011/";
	string hDir  = "";
	string hName = "res";
	string xTitle = "#delta(1/p_{T})";
	string yTitle= "Events";

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
	gStyle->SetPadBottomMargin(0.18); // 0.16
	gStyle->SetPadLeftMargin(0.12); // 
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
	
	TLegend* leg_pT = new TLegend(0.2,0.2,0.5,0.45,NULL,"brNDC");
	leg_pT->SetFillColor(kWhite);
	
	TLegend* leg_dR = new TLegend(0.2,0.2,0.5,0.45,NULL,"brNDC");
	leg_dR->SetFillColor(kWhite);
	
	stringstream strm;
	string str;
	
	strm.clear();
	str.clear();
	strm << L;
	strm >> str;
	string lumilabel = "#intLdt~" + str + " fb^{-1}";
	TPaveText* pvtxt_lumi = new TPaveText(0.2,0.45,0.5,0.7,"brNDC");
	pvtxt_lumi->SetFillColor(0);
	pvtxt_lumi->SetBorderSize(0);
	TText* txt  = pvtxt_lumi->AddText( lumilabel.c_str() );
	
	TPaveText* pvtxt_atlfast = new TPaveText(0.2,0.72,0.5,0.9,"brNDC");
	pvtxt_atlfast->SetFillColor(0);
	pvtxt_atlfast->SetBorderSize(0);
	pvtxt_atlfast->SetTextFont(42);
	txt = pvtxt_atlfast->AddText("#bf{#it{ATLFAST}}");
	pvtxt_atlfast->Draw();
	
	
	TPaveText* pvtxt_var_pTres = new TPaveText(0.56,0.27,0.93,0.78,"brNDC");
	pvtxt_var_pTres->SetFillColor(0);
	pvtxt_var_pTres->SetBorderSize(0);
	pvtxt_var_pTres->SetTextFont(42);
	txt = pvtxt_var_pTres->AddText("#splitline{#delta(1/p_{T}) #equiv #frac{#frac{1}{p_{T}^{rec}} - #frac{1}{p_{T}^{tru}}}{#frac{1}{p_{T}^{tru}}}}{for #mu^{-} only}");
	pvtxt_var_pTres->Draw();
	
	
	TPaveText* pvtxt_var_dR = new TPaveText(0.525,0.244,0.996,0.843,"brNDC");
	pvtxt_var_dR->SetFillColor(0);
	pvtxt_var_dR->SetBorderSize(0);
	pvtxt_var_dR->SetTextFont(42);
	txt = pvtxt_var_dR->AddText("#splitline{#delta R = #sqrt{(#eta_{rec}-#eta_{tru})^{2} + (#phi_{rec}-#phi_{tru})^{2}} }{for #mu^{-} only}");
	pvtxt_var_dR->Draw();
	
	
	string cName = "";
	
	cName = "cnv_dr";
	TCanvas* cnv_dr = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv_dr->Divide(2,2);
	
	TVirtualPad *pad_dr_txt = cnv_dr->cd(1);
	pad_dr_txt->SetTicky(0);
	pad_dr_txt->SetTickx(1);
	
	TVirtualPad *pad_dr_Z0 = cnv_dr->cd(2);
	pad_dr_Z0->SetTicky(0);
	pad_dr_Z0->SetTickx(1);
	pad_dr_Z0->SetLogy();
	pad_dr_Z0->SetLogx();
	
	TVirtualPad *pad_dr_ZP = cnv_dr->cd(3);
	pad_dr_ZP->SetTicky(0);
	pad_dr_ZP->SetTickx(1);
	pad_dr_ZP->SetLogy();
	pad_dr_ZP->SetLogx();
	
	TVirtualPad *pad_dr_KK = cnv_dr->cd(4);
	pad_dr_KK->SetTicky(0);
	pad_dr_KK->SetTickx(1);
	pad_dr_KK->SetLogy();
	pad_dr_KK->SetLogx();
	

	
	
	cName = "cnv_res";
	TCanvas* cnv_res = new TCanvas(cName.c_str(), cName.c_str(), 0,0,1200,800);
	cnv_res->Divide(2,2);
	
	TVirtualPad *pad_res_txt = cnv_res->cd(1);
	pad_res_txt->SetTicky(0);
	pad_res_txt->SetTickx(1);
	
	TVirtualPad *pad_res_Z0 = cnv_res->cd(2);
	pad_res_Z0->SetTicky(0);
	pad_res_Z0->SetTickx(1);
	pad_res_Z0->SetLogy();
	
	TVirtualPad *pad_res_ZP = cnv_res->cd(3);
	pad_res_ZP->SetTicky(0);
	pad_res_ZP->SetTickx(1);
	pad_res_ZP->SetLogy();
	
	TVirtualPad *pad_res_KK = cnv_res->cd(4);
	pad_res_KK->SetTicky(0);
	pad_res_KK->SetTickx(1);
	pad_res_KK->SetLogy();
	
	string path = "";
	string sProc = "";
	string channel = "";
	
	
	
	///////////////////////////////////////////////
	// Z0 /////////////////////////////////////////
	
	xTitle = "#delta(m_{#mu#mu})";
	channel = "#gamma/Z^{0}";
	TH1D* hMResZ0;
	hMResZ0 = new TH1D("res_Z0","res_Z0", 100, -0.3, +0.3 );
	hMResZ0->SetLineColor(kAzure-5);
	hMResZ0->SetFillColor(kAzure-5);
	hMResZ0->SetFillStyle(3003);
	hMResZ0->SetLineWidth(1);
	hMResZ0->SetMarkerSize(0);
	hMResZ0->SetMarkerColor(0);
	hMResZ0->SetTitle("");
	hMResZ0->SetXTitle( xTitle.c_str() );
	hMResZ0->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hMResZ0, channel.c_str(), "f");
	
	xTitle = "#delta(1/p_{T})";
	TH1D* hpTResZ0;
	hpTResZ0 = new TH1D("res_Z0","res_Z0", 100, -0.3, +0.3 );
	hpTResZ0->SetLineColor(kAzure-5);
	hpTResZ0->SetFillColor(kAzure-5);
	hpTResZ0->SetFillStyle(3003);
	hpTResZ0->SetLineWidth(1);
	hpTResZ0->SetMarkerSize(0);
	hpTResZ0->SetMarkerColor(0);
	hpTResZ0->SetTitle("");
	hpTResZ0->SetXTitle( xTitle.c_str() );
	hpTResZ0->SetYTitle( yTitle.c_str() );
	leg_pT->AddEntry( hpTResZ0, channel.c_str(), "f");
	
	xTitle = "#delta R";
	TH1D* hdRZ0;
	hdRZ0 = new TH1D("dr_Z0","dr_Z0", dr_nbins, dr_bins );
	hdRZ0->SetLineColor(kAzure-5);
	hdRZ0->SetFillColor(kAzure-5);
	hdRZ0->SetFillStyle(3003);
	hdRZ0->SetLineWidth(1);
	hdRZ0->SetMarkerSize(0);
	hdRZ0->SetMarkerColor(0);
	hdRZ0->SetTitle("");
	hdRZ0->SetXTitle( xTitle.c_str() );
	hdRZ0->SetYTitle( yTitle.c_str() );
	leg_dR->AddEntry( hdRZ0, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// Z' /////////////////////////////////////////
	xTitle = "#delta(m_{#mu#mu})";
	channel = "1 TeV Z'_{SSM}";
	TH1D* hMResZP;
	hMResZP = new TH1D("res_ZP","res_ZP", 100, -0.3, +0.3 );
	hMResZP->SetLineColor(kRed);
	hMResZP->SetFillColor(kRed);
	hMResZP->SetFillStyle(3017);
	hMResZP->SetLineWidth(1);
	hMResZP->SetMarkerSize(0);
	hMResZP->SetMarkerColor(0);
	hMResZP->SetTitle("");
	hMResZP->SetXTitle( xTitle.c_str() );
	hMResZP->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hMResZP, channel.c_str(), "f");
	
	xTitle = "#delta(1/p_{T})";
	TH1D* hpTResZP;
	hpTResZP = new TH1D("res_ZP","res_ZP", 100, -0.3, +0.3 );
	hpTResZP->SetLineColor(kRed);
	hpTResZP->SetFillColor(kRed);
	hpTResZP->SetFillStyle(3017);
	hpTResZP->SetLineWidth(1);
	hpTResZP->SetMarkerSize(0);
	hpTResZP->SetMarkerColor(0);
	hpTResZP->SetTitle("");
	hpTResZP->SetXTitle( xTitle.c_str() );
	hpTResZP->SetYTitle( yTitle.c_str() );
	leg_pT->AddEntry( hpTResZP, channel.c_str(), "f");
	
	xTitle = "#delta R";
	TH1D* hdRZP;
	hdRZP = new TH1D("dr_ZP","dr_ZP", dr_nbins, dr_bins );
	hdRZP->SetLineColor(kRed);
	hdRZP->SetFillColor(kRed);
	hdRZP->SetFillStyle(3017);
	hdRZP->SetLineWidth(1);
	hdRZP->SetMarkerSize(0);
	hdRZP->SetMarkerColor(0);
	hdRZP->SetTitle("");
	hdRZP->SetXTitle( xTitle.c_str() );
	hdRZP->SetYTitle( yTitle.c_str() );
	leg_dR->AddEntry( hdRZP, channel.c_str(), "f");
	
	
	///////////////////////////////////////////////
	// KK /////////////////////////////////////////
	channel = "1 TeV #gamma_{KK}/Z_{KK}";
	xTitle = "#delta(m_{#mu#mu})";
	TH1D* hMResKK;
	hMResKK = new TH1D("res_KK","res_KK", 100, -0.3, +0.3 );
	hMResKK->SetLineColor(kBlack);
	hMResKK->SetFillColor(kBlack);
	hMResKK->SetFillStyle(3018);
	hMResKK->SetLineWidth(1);
	hMResKK->SetMarkerSize(0);
	hMResKK->SetMarkerColor(0);
	hMResKK->SetTitle("");
	hMResKK->SetXTitle( xTitle.c_str() );
	hMResKK->SetYTitle( yTitle.c_str() );
	leg_mHat->AddEntry( hMResKK, channel.c_str(), "f");
	
	xTitle = "#delta(1/p_{T})";
	TH1D* hpTResKK;
	hpTResKK = new TH1D("res_KK","res_KK", 100, -0.3, +0.3 );
	hpTResKK->SetLineColor(kBlack);
	hpTResKK->SetFillColor(kBlack);
	hpTResKK->SetFillStyle(3018);
	hpTResKK->SetLineWidth(1);
	hpTResKK->SetMarkerSize(0);
	hpTResKK->SetMarkerColor(0);
	hpTResKK->SetTitle("");
	hpTResKK->SetXTitle( xTitle.c_str() );
	hpTResKK->SetYTitle( yTitle.c_str() );
	leg_pT->AddEntry( hpTResKK, channel.c_str(), "f");
	
	xTitle = "#delta R";
	TH1D* hdRKK;
	hdRKK = new TH1D("dr_KK","dr_KK", dr_nbins, dr_bins );
	hdRKK->SetLineColor(kBlack);
	hdRKK->SetFillColor(kBlack);
	hdRKK->SetFillStyle(3018);
	hdRKK->SetLineWidth(1);
	hdRKK->SetMarkerSize(0);
	hdRKK->SetMarkerColor(0);
	hdRKK->SetTitle("");
	hdRKK->SetXTitle( xTitle.c_str() );
	hdRKK->SetYTitle( yTitle.c_str() );
	leg_dR->AddEntry( hdRKK, channel.c_str(), "f");
	
	Int_t maxEvents = 0;
	Int_t lumEvents = 0;
	vector<string> vsNames;
	string sMergedFileName; 
	string sGenMergedFileName; 
	TAxis *xaxis = hMResZ0->GetXaxis();
	
	bool doMerge = false;
	cout << "do merge(1/0)?...";
	cin >> doMerge;
	if(doMerge) cout << "merging files" << endl;
	else        cout << "skipping merge" << endl;
	

	
	vsNames.clear();
	sMergedFileName = "Z0.merged.root";
	sGenMergedFileName = "Z0.gen.merged.root";
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00001.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00002.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00003.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00004.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00005.pool.root");
	
	if(doMerge) nevents_Z0 = merge(sMergedFileName, dir, vsNames, "FastTree");
	TFile* fZ0 = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_Z0 = (TTree*)fZ0->Get("FastTree");
	initTree(tree_Z0);
	if(!doMerge) nevents_Z0 = tree_Z0->GetEntries();
	
	if(doMerge) neventsGen_Z0 = merge(sGenMergedFileName, dir, vsNames, "CollectionTree");
	TFile* fZ0Gen = new TFile(sGenMergedFileName.c_str(), "READ");
	TTree* treeGen_Z0 = (TTree*)fZ0Gen->Get("CollectionTree");
	initGenTree(treeGen_Z0);
	if(!doMerge) neventsGen_Z0 = treeGen_Z0->GetEntries();
	
	lumEvents = (Int_t)(L*ifb2imb*sigma_Z0);
	maxEvents = (FITWITHALLEVENTS) ? tree_Z0->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_Z0->GetEntries() << " events" << endl;
	fill(tree_Z0, treeGen_Z0, maxEvents, hMResZ0, hpTResZ0, hdRZ0);
	
	
	
	vsNames.clear();
	sMergedFileName = "ZprimeSSM.merged.root";
	sGenMergedFileName = "ZprimeSSM.gen.merged.root";
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00001.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00002.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00003.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00004.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_ZprimeSSM_M1000_mumu.NTUP._00005.pool.root");
	
	if(doMerge) nevents_ZP = merge(sMergedFileName, dir, vsNames, "FastTree");
	TFile* fZP = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_ZP = (TTree*)fZP->Get("FastTree");
	initTree(tree_ZP);
	if(!doMerge) nevents_ZP = tree_ZP->GetEntries();
	
	if(doMerge) neventsGen_ZP = merge(sGenMergedFileName, dir, vsNames, "CollectionTree");
	TFile* fZPGen = new TFile(sGenMergedFileName.c_str(), "READ");
	TTree* treeGen_ZP = (TTree*)fZPGen->Get("CollectionTree");
	initGenTree(treeGen_ZP);
	if(!doMerge) neventsGen_ZP = treeGen_ZP->GetEntries();

	lumEvents = (Int_t)(L*ifb2imb*sigma_ZP);
	maxEvents = (FITWITHALLEVENTS) ? tree_ZP->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_ZP->GetEntries() << " events" << endl;
	fill(tree_ZP, treeGen_ZP, maxEvents, hMResZP, hpTResZP, hdRZP);
	
	
	
	
	vsNames.clear();
	sMergedFileName = "KK.merged.root";
	sGenMergedFileName = "KK.gen.merged.root";
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00001.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00002.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00003.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00004.pool.root");
	vsNames.push_back("MC10.000000.Pythia8_KK_M1000_mumu.NTUP._00005.pool.root");
	
	if(doMerge) nevents_KK = merge(sMergedFileName, dir, vsNames, "FastTree");
	TFile* fKK = new TFile(sMergedFileName.c_str(), "READ");
	TTree* tree_KK = (TTree*)fKK->Get("FastTree");
	initTree(tree_KK);
	if(!doMerge) nevents_KK = tree_KK->GetEntries();
	
	if(doMerge) neventsGen_KK = merge(sGenMergedFileName, dir, vsNames, "CollectionTree");
	TFile* fKKGen = new TFile(sGenMergedFileName.c_str(), "READ");
	TTree* treeGen_KK = (TTree*)fKKGen->Get("CollectionTree");
	initGenTree(treeGen_KK);
	if(!doMerge) neventsGen_KK = treeGen_KK->GetEntries();
	
	lumEvents = (Int_t)(L*ifb2imb*sigma_KK);
	maxEvents = (FITWITHALLEVENTS) ? tree_KK->GetEntries() : lumEvents;
	cout << "Using " << maxEvents << "/" << tree_KK->GetEntries() << " events" << endl;
	fill(tree_KK, treeGen_KK, maxEvents, hMResKK, hpTResKK, hdRKK);
	
	


	
	
	
	cnv_res->cd();
	cnv_res->Draw();
	
	pad_res_txt->cd();
	pvtxt_lumi->Draw();
	pvtxt_atlfast->Draw("SAMES");
	leg_pT->Draw("SAMES");
	pvtxt_var_pTres->Draw("SAMES");
	pad_res_txt->RedrawAxis();
	pad_res_txt->Update();
	
	pad_res_Z0->cd();
	hpTResZ0->Draw();
	pad_res_Z0->RedrawAxis();
	pad_res_Z0->Update();
	
	pad_res_ZP->cd();
	hpTResZP->Draw();
	pad_res_ZP->RedrawAxis();
	pad_res_ZP->Update();
	
	pad_res_KK->cd();
	hpTResKK->Draw();
	pad_res_KK->RedrawAxis();
	pad_res_KK->Update();
	
	cnv_res->cd();
	cnv_res->Update();
	
	
	
	
	cnv_dr->cd();
	cnv_dr->Draw();
	
	pad_dr_txt->cd();
	pvtxt_lumi->Draw();
	pvtxt_atlfast->Draw("SAMES");
	leg_pT->Draw("SAMES");
	pvtxt_var_dR->Draw("SAMES");
	pad_dr_txt->RedrawAxis();
	pad_dr_txt->Update();
	
	pad_dr_Z0->cd();
	hdRZ0->Draw();
	pad_dr_Z0->RedrawAxis();
	pad_dr_Z0->Update();
	
	pad_dr_ZP->cd();
	hdRZP->Draw();
	pad_dr_ZP->RedrawAxis();
	pad_dr_ZP->Update();
	
	pad_dr_KK->cd();
	hdRKK->Draw();
	pad_dr_KK->RedrawAxis();
	pad_dr_KK->Update();
	
	cnv_dr->cd();
	cnv_dr->Update();
	
	

	
	TString fName = "";

	
	fName = "res.atlfast.plot";
	cnv_res->SaveAs(fName+".eps");
	cnv_res->SaveAs(fName+".C");
	cnv_res->SaveAs(fName+".root");
	cnv_res->SaveAs(fName+".png");
	
	fName = "dr.atlfast.plot";
	cnv_dr->SaveAs(fName+".eps");
	cnv_dr->SaveAs(fName+".C");
	cnv_dr->SaveAs(fName+".root");
	cnv_dr->SaveAs(fName+".png");
	
	of->close();
}

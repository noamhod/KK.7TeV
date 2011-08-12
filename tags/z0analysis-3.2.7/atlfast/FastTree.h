//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 20 15:24:14 2011 by ROOT version 5.28/00
// from TTree FastTree/FastTree
// found on file: MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450.NTUP._00001.pool.root
//////////////////////////////////////////////////////////

#ifndef FastTree_h
#define FastTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


double xmin  = 0.;
double xmax  = 4000.;
int    nbins = 200;
vector<string> svNames;
vector<string> svPaths;
vector<TH1D*>  hvHistos;
vector<double> dvWeights;
vector<Color_t> cvColors;
string sDir  = "/data/hod/newATLFAST/";
string sSubDir  = "";
string sSubSubDir  = "";
string sName = "";

TLorentzVector* pa = new TLorentzVector();
TLorentzVector* pb = new TLorentzVector();

void addSample(string path, string file, string name, Color_t color, double events, double sigma)
{	
	svNames.push_back(name);

	sName = svNames[svNames.size()-1];

	svPaths.push_back(path+file);
	hvHistos.push_back(new TH1D(sName.c_str(),sName.c_str(),nbins,xmin,xmax));
	dvWeights.push_back(luminosity/(events/(sigma*nb2fb)));
	cvColors.push_back(color);
}


class FastTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
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
   Int_t           Elenc;
   vector<float>   *Elee;
   vector<float>   *Eleeta;
   vector<float>   *Elephi;
   vector<float>   *Eleauthor;
   vector<float>   *EleKf;
   vector<float>   *ElePx;
   vector<float>   *ElePy;
   vector<float>   *ElePz;
   Int_t           Phonc;
   vector<float>   *Phoe;
   vector<float>   *Phoeta;
   vector<float>   *Phophi;
   vector<float>   *Phoauthor;
   vector<float>   *PhoKf;
   vector<float>   *PhoPx;
   vector<float>   *PhoPy;
   vector<float>   *PhoPz;
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
   Int_t           AtlfastTauJet_NCand;
   vector<long>    *AtlfastTauJet_Author;
   vector<long>    *AtlfastTauJet_valid;
   vector<float>   *AtlfastTauJet_eta;
   vector<float>   *AtlfastTauJet_phi;
   vector<float>   *AtlfastTauJet_pt;
   vector<float>   *AtlfastTauJet_m;
   vector<float>   *AtlfastTauJet_ET;
   vector<double>  *AtlfastTauJet_charge;
   vector<long>    *AtlfastTauJet_pdgId;
   vector<long>    *AtlfastTauJet_ntrack;
   vector<long>    *AtlfastTauJet_isTau;
   vector<int>     *AtlfastTauJet_ElectronFlag;
   vector<int>     *AtlfastTauJet_MuonFlag;
   UInt_t          jetNumAtlfastJets;
   vector<double>  *jetEtaAtlfastJets;
   vector<double>  *jetPhiAtlfastJets;
   vector<double>  *jetEAtlfastJets;
   vector<double>  *jetEtAtlfastJets;
   vector<double>  *jetMAtlfastJets;
   vector<double>  *jetPxAtlfastJets;
   vector<double>  *jetPyAtlfastJets;
   vector<double>  *jetPzAtlfastJets;
   vector<long>    *jetSizeAtlfastJets;
   vector<double>  *jetEmfAtlfastJets;
   vector<double>  *jetErawAtlfastJets;
   vector<double>  *jetPxrawAtlfastJets;
   vector<double>  *jetPyrawAtlfastJets;
   vector<double>  *jetPzrawAtlfastJets;
   vector<double>  *jetMrawAtlfastJets;
   Double_t        METAod_PxMiss;
   Double_t        METAod_PyMiss;
   Double_t        METAod_SumET;

   // List of branches
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
   TBranch        *b_Elenc;   //!
   TBranch        *b_Elee;   //!
   TBranch        *b_Eleeta;   //!
   TBranch        *b_Elephi;   //!
   TBranch        *b_Eleauthor;   //!
   TBranch        *b_EleKf;   //!
   TBranch        *b_ElePx;   //!
   TBranch        *b_ElePy;   //!
   TBranch        *b_ElePz;   //!
   TBranch        *b_Phonc;   //!
   TBranch        *b_Phoe;   //!
   TBranch        *b_Phoeta;   //!
   TBranch        *b_Phophi;   //!
   TBranch        *b_Phoauthor;   //!
   TBranch        *b_PhoKf;   //!
   TBranch        *b_PhoPx;   //!
   TBranch        *b_PhoPy;   //!
   TBranch        *b_PhoPz;   //!
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
   TBranch        *b_AtlfastTauJet_N;   //!
   TBranch        *b_AtlfastTauJet_Author;   //!
   TBranch        *b_AtlfastTauJet_valid;   //!
   TBranch        *b_AtlfastTauJet_eta;   //!
   TBranch        *b_AtlfastTauJet_phi;   //!
   TBranch        *b_AtlfastTauJet_pt;   //!
   TBranch        *b_AtlfastTauJet_m;   //!
   TBranch        *b_AtlfastTauJet_ET;   //!
   TBranch        *b_AtlfastTauJet_charge;   //!
   TBranch        *b_AtlfastTauJet_pdgId;   //!
   TBranch        *b_AtlfastTauJet_ntrack;   //!
   TBranch        *b_AtlfastTauJet_isTau;   //!
   TBranch        *b_AtlfastTauJet_ElectronFlag;   //!
   TBranch        *b_AtlfastTauJet_MuonFlag;   //!
   TBranch        *b_AtlfastJetsjetNum;   //!
   TBranch        *b_jetEtaAtlfastJets;   //!
   TBranch        *b_jetPhiAtlfastJets;   //!
   TBranch        *b_jetEAtlfastJets;   //!
   TBranch        *b_jetEtAtlfastJets;   //!
   TBranch        *b_jetMAtlfastJets;   //!
   TBranch        *b_jetPxAtlfastJets;   //!
   TBranch        *b_jetPyAtlfastJets;   //!
   TBranch        *b_jetPzAtlfastJets;   //!
   TBranch        *b_jetSizeAtlfastJets;   //!
   TBranch        *b_jetEmfAtlfastJets;   //!
   TBranch        *b_jetErawAtlfastJets;   //!
   TBranch        *b_jetPxrawAtlfastJets;   //!
   TBranch        *b_jetPyrawAtlfastJets;   //!
   TBranch        *b_jetPzrawAtlfastJets;   //!
   TBranch        *b_jetMrawAtlfastJets;   //!
   TBranch        *b_METAod_PxMiss;   //!
   TBranch        *b_METAod_PyMiss;   //!
   TBranch        *b_METAod_SumET;   //!

   FastTree(TTree *tree=0);
   virtual ~FastTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FastTree_cxx
FastTree::FastTree(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450.NTUP._00001.pool.root");
      if (!f) {
         f = new TFile("MC11.000001.Pythia8_ZprimeSSM_m2000_mumu_120M450.NTUP._00001.pool.root");
      }
      tree = (TTree*)gDirectory->Get("FastTree");

   }
   Init(tree);
}

FastTree::~FastTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FastTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FastTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void FastTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   LVL1TriggerInfo = 0;
   LVL2TriggerInfo = 0;
   EventFilterInfo = 0;
   StreamTagName = 0;
   StreamTagType = 0;
   Elee = 0;
   Eleeta = 0;
   Elephi = 0;
   Eleauthor = 0;
   EleKf = 0;
   ElePx = 0;
   ElePy = 0;
   ElePz = 0;
   Phoe = 0;
   Phoeta = 0;
   Phophi = 0;
   Phoauthor = 0;
   PhoKf = 0;
   PhoPx = 0;
   PhoPy = 0;
   PhoPz = 0;
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
   AtlfastTauJet_Author = 0;
   AtlfastTauJet_valid = 0;
   AtlfastTauJet_eta = 0;
   AtlfastTauJet_phi = 0;
   AtlfastTauJet_pt = 0;
   AtlfastTauJet_m = 0;
   AtlfastTauJet_ET = 0;
   AtlfastTauJet_charge = 0;
   AtlfastTauJet_pdgId = 0;
   AtlfastTauJet_ntrack = 0;
   AtlfastTauJet_isTau = 0;
   AtlfastTauJet_ElectronFlag = 0;
   AtlfastTauJet_MuonFlag = 0;
   jetEtaAtlfastJets = 0;
   jetPhiAtlfastJets = 0;
   jetEAtlfastJets = 0;
   jetEtAtlfastJets = 0;
   jetMAtlfastJets = 0;
   jetPxAtlfastJets = 0;
   jetPyAtlfastJets = 0;
   jetPzAtlfastJets = 0;
   jetSizeAtlfastJets = 0;
   jetEmfAtlfastJets = 0;
   jetErawAtlfastJets = 0;
   jetPxrawAtlfastJets = 0;
   jetPyrawAtlfastJets = 0;
   jetPzrawAtlfastJets = 0;
   jetMrawAtlfastJets = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("Token", &Token, &b_Token);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Time", &Time, &b_Time);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("LVL1ID", &LVL1ID, &b_LVL1ID);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("IEvent", &IEvent, &b_IEvent);
   fChain->SetBranchAddress("StatusElement", &StatusElement, &b_StatusElement);
   fChain->SetBranchAddress("LVL1TriggerType", &LVL1TriggerType, &b_LVL1TriggerType);
   fChain->SetBranchAddress("LVL1TriggerInfo", &LVL1TriggerInfo, &b_LVL1TriggerInfo);
   fChain->SetBranchAddress("LVL2TriggerInfo", &LVL2TriggerInfo, &b_LVL2TriggerInfo);
   fChain->SetBranchAddress("EventFilterInfo", &EventFilterInfo, &b_EventFilterInfo);
   fChain->SetBranchAddress("StreamTagName", &StreamTagName, &b_StreamTagName);
   fChain->SetBranchAddress("StreamTagType", &StreamTagType, &b_StreamTagType);
   fChain->SetBranchAddress("Elenc", &Elenc, &b_Elenc);
   fChain->SetBranchAddress("Elee", &Elee, &b_Elee);
   fChain->SetBranchAddress("Eleeta", &Eleeta, &b_Eleeta);
   fChain->SetBranchAddress("Elephi", &Elephi, &b_Elephi);
   fChain->SetBranchAddress("Eleauthor", &Eleauthor, &b_Eleauthor);
   fChain->SetBranchAddress("EleKf", &EleKf, &b_EleKf);
   fChain->SetBranchAddress("ElePx", &ElePx, &b_ElePx);
   fChain->SetBranchAddress("ElePy", &ElePy, &b_ElePy);
   fChain->SetBranchAddress("ElePz", &ElePz, &b_ElePz);
   fChain->SetBranchAddress("Phonc", &Phonc, &b_Phonc);
   fChain->SetBranchAddress("Phoe", &Phoe, &b_Phoe);
   fChain->SetBranchAddress("Phoeta", &Phoeta, &b_Phoeta);
   fChain->SetBranchAddress("Phophi", &Phophi, &b_Phophi);
   fChain->SetBranchAddress("Phoauthor", &Phoauthor, &b_Phoauthor);
   fChain->SetBranchAddress("PhoKf", &PhoKf, &b_PhoKf);
   fChain->SetBranchAddress("PhoPx", &PhoPx, &b_PhoPx);
   fChain->SetBranchAddress("PhoPy", &PhoPy, &b_PhoPy);
   fChain->SetBranchAddress("PhoPz", &PhoPz, &b_PhoPz);
   fChain->SetBranchAddress("MuonN", &MuonN, &b_MuonN);
   fChain->SetBranchAddress("MuonAuthor", &MuonAuthor, &b_MuonAuthor);
   fChain->SetBranchAddress("MuonCombTrkNt", &MuonCombTrkNt, &b_MuonCombTrkNt);
   fChain->SetBranchAddress("MuonInDetTrkNt", &MuonInDetTrkNt, &b_MuonInDetTrkNt);
   fChain->SetBranchAddress("MuonExtrNt", &MuonExtrNt, &b_MuonExtrNt);
   fChain->SetBranchAddress("MuonEta", &MuonEta, &b_MuonEta);
   fChain->SetBranchAddress("MuonPhi", &MuonPhi, &b_MuonPhi);
   fChain->SetBranchAddress("MuonPt", &MuonPt, &b_MuonPt);
   fChain->SetBranchAddress("MuonZ0", &MuonZ0, &b_MuonZ0);
   fChain->SetBranchAddress("MuonD0", &MuonD0, &b_MuonD0);
   fChain->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
   fChain->SetBranchAddress("MuonKf", &MuonKf, &b_MuonKf);
   fChain->SetBranchAddress("MuonPx", &MuonPx, &b_MuonPx);
   fChain->SetBranchAddress("MuonPy", &MuonPy, &b_MuonPy);
   fChain->SetBranchAddress("MuonPz", &MuonPz, &b_MuonPz);
   fChain->SetBranchAddress("MuonEtCone10", &MuonEtCone10, &b_MuonEtCone10);
   fChain->SetBranchAddress("MuonEtCone20", &MuonEtCone20, &b_MuonEtCone20);
   fChain->SetBranchAddress("MuonEtCone30", &MuonEtCone30, &b_MuonEtCone30);
   fChain->SetBranchAddress("MuonEtCone40", &MuonEtCone40, &b_MuonEtCone40);
   fChain->SetBranchAddress("MuonNuCone10", &MuonNuCone10, &b_MuonNuCone10);
   fChain->SetBranchAddress("MuonNuCone20", &MuonNuCone20, &b_MuonNuCone20);
   fChain->SetBranchAddress("MuonNuCone30", &MuonNuCone30, &b_MuonNuCone30);
   fChain->SetBranchAddress("MuonNuCone40", &MuonNuCone40, &b_MuonNuCone40);
   fChain->SetBranchAddress("MuonFitChi2", &MuonFitChi2, &b_MuonFitChi2);
   fChain->SetBranchAddress("MuonFitNumberDoF", &MuonFitNumberDoF, &b_MuonFitNumberDoF);
   fChain->SetBranchAddress("MuonEnergyLossDeposit", &MuonEnergyLossDeposit, &b_MuonEnergyLossDeposit);
   fChain->SetBranchAddress("MuonEnergyLossSigma", &MuonEnergyLossSigma, &b_MuonEnergyLossSigma);
   fChain->SetBranchAddress("MuonMatchChi2", &MuonMatchChi2, &b_MuonMatchChi2);
   fChain->SetBranchAddress("MuonMatchNumberDoF", &MuonMatchNumberDoF, &b_MuonMatchNumberDoF);
   fChain->SetBranchAddress("MuonBestMatch", &MuonBestMatch, &b_MuonBestMatch);
   fChain->SetBranchAddress("MuonIsCombinedMuon", &MuonIsCombinedMuon, &b_MuonIsCombinedMuon);
   fChain->SetBranchAddress("AtlfastTauJet_NCand", &AtlfastTauJet_NCand, &b_AtlfastTauJet_N);
   fChain->SetBranchAddress("AtlfastTauJet_Author", &AtlfastTauJet_Author, &b_AtlfastTauJet_Author);
   fChain->SetBranchAddress("AtlfastTauJet_valid", &AtlfastTauJet_valid, &b_AtlfastTauJet_valid);
   fChain->SetBranchAddress("AtlfastTauJet_eta", &AtlfastTauJet_eta, &b_AtlfastTauJet_eta);
   fChain->SetBranchAddress("AtlfastTauJet_phi", &AtlfastTauJet_phi, &b_AtlfastTauJet_phi);
   fChain->SetBranchAddress("AtlfastTauJet_pt", &AtlfastTauJet_pt, &b_AtlfastTauJet_pt);
   fChain->SetBranchAddress("AtlfastTauJet_m", &AtlfastTauJet_m, &b_AtlfastTauJet_m);
   fChain->SetBranchAddress("AtlfastTauJet_ET", &AtlfastTauJet_ET, &b_AtlfastTauJet_ET);
   fChain->SetBranchAddress("AtlfastTauJet_charge", &AtlfastTauJet_charge, &b_AtlfastTauJet_charge);
   fChain->SetBranchAddress("AtlfastTauJet_pdgId", &AtlfastTauJet_pdgId, &b_AtlfastTauJet_pdgId);
   fChain->SetBranchAddress("AtlfastTauJet_ntrack", &AtlfastTauJet_ntrack, &b_AtlfastTauJet_ntrack);
   fChain->SetBranchAddress("AtlfastTauJet_isTau", &AtlfastTauJet_isTau, &b_AtlfastTauJet_isTau);
   fChain->SetBranchAddress("AtlfastTauJet_ElectronFlag", &AtlfastTauJet_ElectronFlag, &b_AtlfastTauJet_ElectronFlag);
   fChain->SetBranchAddress("AtlfastTauJet_MuonFlag", &AtlfastTauJet_MuonFlag, &b_AtlfastTauJet_MuonFlag);
   fChain->SetBranchAddress("jetNumAtlfastJets", &jetNumAtlfastJets, &b_AtlfastJetsjetNum);
   fChain->SetBranchAddress("jetEtaAtlfastJets", &jetEtaAtlfastJets, &b_jetEtaAtlfastJets);
   fChain->SetBranchAddress("jetPhiAtlfastJets", &jetPhiAtlfastJets, &b_jetPhiAtlfastJets);
   fChain->SetBranchAddress("jetEAtlfastJets", &jetEAtlfastJets, &b_jetEAtlfastJets);
   fChain->SetBranchAddress("jetEtAtlfastJets", &jetEtAtlfastJets, &b_jetEtAtlfastJets);
   fChain->SetBranchAddress("jetMAtlfastJets", &jetMAtlfastJets, &b_jetMAtlfastJets);
   fChain->SetBranchAddress("jetPxAtlfastJets", &jetPxAtlfastJets, &b_jetPxAtlfastJets);
   fChain->SetBranchAddress("jetPyAtlfastJets", &jetPyAtlfastJets, &b_jetPyAtlfastJets);
   fChain->SetBranchAddress("jetPzAtlfastJets", &jetPzAtlfastJets, &b_jetPzAtlfastJets);
   fChain->SetBranchAddress("jetSizeAtlfastJets", &jetSizeAtlfastJets, &b_jetSizeAtlfastJets);
   fChain->SetBranchAddress("jetEmfAtlfastJets", &jetEmfAtlfastJets, &b_jetEmfAtlfastJets);
   fChain->SetBranchAddress("jetErawAtlfastJets", &jetErawAtlfastJets, &b_jetErawAtlfastJets);
   fChain->SetBranchAddress("jetPxrawAtlfastJets", &jetPxrawAtlfastJets, &b_jetPxrawAtlfastJets);
   fChain->SetBranchAddress("jetPyrawAtlfastJets", &jetPyrawAtlfastJets, &b_jetPyrawAtlfastJets);
   fChain->SetBranchAddress("jetPzrawAtlfastJets", &jetPzrawAtlfastJets, &b_jetPzrawAtlfastJets);
   fChain->SetBranchAddress("jetMrawAtlfastJets", &jetMrawAtlfastJets, &b_jetMrawAtlfastJets);
   fChain->SetBranchAddress("METAod_PxMiss", &METAod_PxMiss, &b_METAod_PxMiss);
   fChain->SetBranchAddress("METAod_PyMiss", &METAod_PyMiss, &b_METAod_PyMiss);
   fChain->SetBranchAddress("METAod_SumET", &METAod_SumET, &b_METAod_SumET);
   Notify();
}

Bool_t FastTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FastTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FastTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FastTree_cxx

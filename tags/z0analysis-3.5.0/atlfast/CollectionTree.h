//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  6 09:16:40 2011 by ROOT version 5.28/00
// from TTree CollectionTree/CollectionTree
// found on file: MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00001.pool.root
//////////////////////////////////////////////////////////

#ifndef CollectionTree_h
#define CollectionTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class CollectionTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           EventNumber;
   Char_t          Token;
   UInt_t          NPar;
   vector<long>    *Type;
   vector<float>   *PtGen;
   vector<float>   *PhiGen;
   vector<float>   *EtaGen;
   vector<float>   *MGen;
   vector<float>   *Charge;
   vector<long>    *GenStat;
   vector<long>    *GenRef;
   vector<long>    *KMothNt;
   vector<long>    *KFDauNt;
   vector<long>    *KLDauNt;
   vector<long>    *KOriVNt;
   vector<long>    *KEndVNt;
   vector<long>    *BunchNum;
   vector<float>   *RVGen;
   vector<float>   *PhiVGen;
   vector<float>   *ZVGen;
   UInt_t          NVer;
   vector<long>    *BunchV;
   vector<float>   *RV;
   vector<float>   *PhiV;
   vector<float>   *ZV;
   vector<long>    *GenRefV;
   vector<long>    *KVMothNt;
   vector<long>    *KVFDauNt;
   vector<long>    *KVLDauNt;
   UInt_t          IVPrimary;
   UInt_t          jetNumCone4TruthJets;
   vector<double>  *jetEtaCone4TruthJets;
   vector<double>  *jetPhiCone4TruthJets;
   vector<double>  *jetECone4TruthJets;
   vector<double>  *jetEtCone4TruthJets;
   vector<double>  *jetMCone4TruthJets;
   vector<double>  *jetPxCone4TruthJets;
   vector<double>  *jetPyCone4TruthJets;
   vector<double>  *jetPzCone4TruthJets;
   vector<long>    *jetSizeCone4TruthJets;
   vector<double>  *jetEmfCone4TruthJets;
   vector<double>  *jetErawCone4TruthJets;
   vector<double>  *jetPxrawCone4TruthJets;
   vector<double>  *jetPyrawCone4TruthJets;
   vector<double>  *jetPzrawCone4TruthJets;
   vector<double>  *jetMrawCone4TruthJets;
   Float_t         MET_ExTruthInt;
   Float_t         MET_EyTruthInt;
   Float_t         MET_EtSumTruthInt;
   Float_t         MET_ExTruthNonInt;
   Float_t         MET_EyTruthNonInt;
   Float_t         MET_EtSumTruthNonInt;
   Float_t         MET_ExTruthIntCentral;
   Float_t         MET_EyTruthIntCentral;
   Float_t         MET_EtSumTruthIntCentral;
   Float_t         MET_ExTruthIntFwd;
   Float_t         MET_EyTruthIntFwd;
   Float_t         MET_EtSumTruthIntFwd;
   Float_t         MET_ExTruthIntOutOfCov;
   Float_t         MET_EyTruthIntOutOfCov;
   Float_t         MET_EtSumTruthIntOutOfCov;
   Float_t         MET_ExTruthMuons;
   Float_t         MET_EyTruthMuons;
   Float_t         MET_EtSumTruthMuons;
   Float_t         MET_ExTruthInt_Pile;
   Float_t         MET_EyTruthInt_Pile;
   Float_t         MET_EtSumTruthInt_Pile;
   Float_t         MET_ExTruthNonInt_Pile;
   Float_t         MET_EyTruthNonInt_Pile;
   Float_t         MET_EtSumTruthNonInt_Pile;
   Float_t         MET_ExTruthIntCentral_Pile;
   Float_t         MET_EyTruthIntCentral_Pile;
   Float_t         MET_EtSumTruthIntCentral_Pile;
   Float_t         MET_ExTruthIntFwd_Pile;
   Float_t         MET_EyTruthIntFwd_Pile;
   Float_t         MET_EtSumTruthIntFwd_Pile;
   Float_t         MET_ExTruthIntOutOfCov_Pile;
   Float_t         MET_EyTruthIntOutOfCov_Pile;
   Float_t         MET_EtSumTruthIntOutOfCov_Pile;
   Float_t         MET_ExTruthMuons_Pile;
   Float_t         MET_EyTruthMuons_Pile;
   Float_t         MET_EtSumTruthMuons_Pile;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_Token;   //!
   TBranch        *b_NPar;   //!
   TBranch        *b_Type;   //!
   TBranch        *b_PtGen;   //!
   TBranch        *b_PhiGen;   //!
   TBranch        *b_EtaGen;   //!
   TBranch        *b_MGen;   //!
   TBranch        *b_Charge;   //!
   TBranch        *b_GenStat;   //!
   TBranch        *b_GenRef;   //!
   TBranch        *b_KMothNt;   //!
   TBranch        *b_KFDauNt;   //!
   TBranch        *b_KLDauNt;   //!
   TBranch        *b_KOriVNt;   //!
   TBranch        *b_KEndVNt;   //!
   TBranch        *b_BunchNum;   //!
   TBranch        *b_RVGen;   //!
   TBranch        *b_PhiVGen;   //!
   TBranch        *b_ZVGen;   //!
   TBranch        *b_NVer;   //!
   TBranch        *b_BunchV;   //!
   TBranch        *b_RV;   //!
   TBranch        *b_PhiV;   //!
   TBranch        *b_ZV;   //!
   TBranch        *b_GenRefV;   //!
   TBranch        *b_KVMothNt;   //!
   TBranch        *b_KVFDauNt;   //!
   TBranch        *b_KVLDauNt;   //!
   TBranch        *b_IVPrimary;   //!
   TBranch        *b_Cone4TruthJetsjetNum;   //!
   TBranch        *b_jetEtaCone4TruthJets;   //!
   TBranch        *b_jetPhiCone4TruthJets;   //!
   TBranch        *b_jetECone4TruthJets;   //!
   TBranch        *b_jetEtCone4TruthJets;   //!
   TBranch        *b_jetMCone4TruthJets;   //!
   TBranch        *b_jetPxCone4TruthJets;   //!
   TBranch        *b_jetPyCone4TruthJets;   //!
   TBranch        *b_jetPzCone4TruthJets;   //!
   TBranch        *b_jetSizeCone4TruthJets;   //!
   TBranch        *b_jetEmfCone4TruthJets;   //!
   TBranch        *b_jetErawCone4TruthJets;   //!
   TBranch        *b_jetPxrawCone4TruthJets;   //!
   TBranch        *b_jetPyrawCone4TruthJets;   //!
   TBranch        *b_jetPzrawCone4TruthJets;   //!
   TBranch        *b_jetMrawCone4TruthJets;   //!
   TBranch        *b_MET_ExTruthInt;   //!
   TBranch        *b_MET_EyTruthInt;   //!
   TBranch        *b_MET_EtSumTruthInt;   //!
   TBranch        *b_MET_ExTruthNonInt;   //!
   TBranch        *b_MET_EyTruthNonInt;   //!
   TBranch        *b_MET_EtSumTruthNonInt;   //!
   TBranch        *b_MET_ExTruthIntCentral;   //!
   TBranch        *b_MET_EyTruthIntCentral;   //!
   TBranch        *b_MET_EtSumTruthIntCentral;   //!
   TBranch        *b_MET_ExTruthIntFwd;   //!
   TBranch        *b_MET_EyTruthIntFwd;   //!
   TBranch        *b_MET_EtSumTruthIntFwd;   //!
   TBranch        *b_MET_ExTruthIntOutOfCov;   //!
   TBranch        *b_MET_EyTruthIntOutOfCov;   //!
   TBranch        *b_MET_EtSumTruthIntOutOfCov;   //!
   TBranch        *b_MET_ExTruthMuons;   //!
   TBranch        *b_MET_EyTruthMuons;   //!
   TBranch        *b_MET_EtSumTruthMuons;   //!
   TBranch        *b_MET_ExTruthInt_Pile;   //!
   TBranch        *b_MET_EyTruthInt_Pile;   //!
   TBranch        *b_MET_EtSumTruthInt_Pile;   //!
   TBranch        *b_MET_ExTruthNonInt_Pile;   //!
   TBranch        *b_MET_EyTruthNonInt_Pile;   //!
   TBranch        *b_MET_EtSumTruthNonInt_Pile;   //!
   TBranch        *b_MET_ExTruthIntCentral_Pile;   //!
   TBranch        *b_MET_EyTruthIntCentral_Pile;   //!
   TBranch        *b_MET_EtSumTruthIntCentral_Pile;   //!
   TBranch        *b_MET_ExTruthIntFwd_Pile;   //!
   TBranch        *b_MET_EyTruthIntFwd_Pile;   //!
   TBranch        *b_MET_EtSumTruthIntFwd_Pile;   //!
   TBranch        *b_MET_ExTruthIntOutOfCov_Pile;   //!
   TBranch        *b_MET_EyTruthIntOutOfCov_Pile;   //!
   TBranch        *b_MET_EtSumTruthIntOutOfCov_Pile;   //!
   TBranch        *b_MET_ExTruthMuons_Pile;   //!
   TBranch        *b_MET_EyTruthMuons_Pile;   //!
   TBranch        *b_MET_EtSumTruthMuons_Pile;   //!

   CollectionTree(TTree *tree=0);
   virtual ~CollectionTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CollectionTree_cxx
CollectionTree::CollectionTree(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00001.pool.root");
      if (!f) {
         f = new TFile("MC10.000000.Pythia8_Z0_M1000_mumu.NTUP._00001.pool.root");
      }
      tree = (TTree*)gDirectory->Get("CollectionTree");

   }
   Init(tree);
}

CollectionTree::~CollectionTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CollectionTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CollectionTree::LoadTree(Long64_t entry)
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

void CollectionTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Type = 0;
   PtGen = 0;
   PhiGen = 0;
   EtaGen = 0;
   MGen = 0;
   Charge = 0;
   GenStat = 0;
   GenRef = 0;
   KMothNt = 0;
   KFDauNt = 0;
   KLDauNt = 0;
   KOriVNt = 0;
   KEndVNt = 0;
   BunchNum = 0;
   RVGen = 0;
   PhiVGen = 0;
   ZVGen = 0;
   BunchV = 0;
   RV = 0;
   PhiV = 0;
   ZV = 0;
   GenRefV = 0;
   KVMothNt = 0;
   KVFDauNt = 0;
   KVLDauNt = 0;
   jetEtaCone4TruthJets = 0;
   jetPhiCone4TruthJets = 0;
   jetECone4TruthJets = 0;
   jetEtCone4TruthJets = 0;
   jetMCone4TruthJets = 0;
   jetPxCone4TruthJets = 0;
   jetPyCone4TruthJets = 0;
   jetPzCone4TruthJets = 0;
   jetSizeCone4TruthJets = 0;
   jetEmfCone4TruthJets = 0;
   jetErawCone4TruthJets = 0;
   jetPxrawCone4TruthJets = 0;
   jetPyrawCone4TruthJets = 0;
   jetPzrawCone4TruthJets = 0;
   jetMrawCone4TruthJets = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("Token", &Token, &b_Token);
   fChain->SetBranchAddress("NPar", &NPar, &b_NPar);
   fChain->SetBranchAddress("Type", &Type, &b_Type);
   fChain->SetBranchAddress("PtGen", &PtGen, &b_PtGen);
   fChain->SetBranchAddress("PhiGen", &PhiGen, &b_PhiGen);
   fChain->SetBranchAddress("EtaGen", &EtaGen, &b_EtaGen);
   fChain->SetBranchAddress("MGen", &MGen, &b_MGen);
   fChain->SetBranchAddress("Charge", &Charge, &b_Charge);
   fChain->SetBranchAddress("GenStat", &GenStat, &b_GenStat);
   fChain->SetBranchAddress("GenRef", &GenRef, &b_GenRef);
   fChain->SetBranchAddress("KMothNt", &KMothNt, &b_KMothNt);
   fChain->SetBranchAddress("KFDauNt", &KFDauNt, &b_KFDauNt);
   fChain->SetBranchAddress("KLDauNt", &KLDauNt, &b_KLDauNt);
   fChain->SetBranchAddress("KOriVNt", &KOriVNt, &b_KOriVNt);
   fChain->SetBranchAddress("KEndVNt", &KEndVNt, &b_KEndVNt);
   fChain->SetBranchAddress("BunchNum", &BunchNum, &b_BunchNum);
   fChain->SetBranchAddress("RVGen", &RVGen, &b_RVGen);
   fChain->SetBranchAddress("PhiVGen", &PhiVGen, &b_PhiVGen);
   fChain->SetBranchAddress("ZVGen", &ZVGen, &b_ZVGen);
   fChain->SetBranchAddress("NVer", &NVer, &b_NVer);
   fChain->SetBranchAddress("BunchV", &BunchV, &b_BunchV);
   fChain->SetBranchAddress("RV", &RV, &b_RV);
   fChain->SetBranchAddress("PhiV", &PhiV, &b_PhiV);
   fChain->SetBranchAddress("ZV", &ZV, &b_ZV);
   fChain->SetBranchAddress("GenRefV", &GenRefV, &b_GenRefV);
   fChain->SetBranchAddress("KVMothNt", &KVMothNt, &b_KVMothNt);
   fChain->SetBranchAddress("KVFDauNt", &KVFDauNt, &b_KVFDauNt);
   fChain->SetBranchAddress("KVLDauNt", &KVLDauNt, &b_KVLDauNt);
   fChain->SetBranchAddress("IVPrimary", &IVPrimary, &b_IVPrimary);
   fChain->SetBranchAddress("jetNumCone4TruthJets", &jetNumCone4TruthJets, &b_Cone4TruthJetsjetNum);
   fChain->SetBranchAddress("jetEtaCone4TruthJets", &jetEtaCone4TruthJets, &b_jetEtaCone4TruthJets);
   fChain->SetBranchAddress("jetPhiCone4TruthJets", &jetPhiCone4TruthJets, &b_jetPhiCone4TruthJets);
   fChain->SetBranchAddress("jetECone4TruthJets", &jetECone4TruthJets, &b_jetECone4TruthJets);
   fChain->SetBranchAddress("jetEtCone4TruthJets", &jetEtCone4TruthJets, &b_jetEtCone4TruthJets);
   fChain->SetBranchAddress("jetMCone4TruthJets", &jetMCone4TruthJets, &b_jetMCone4TruthJets);
   fChain->SetBranchAddress("jetPxCone4TruthJets", &jetPxCone4TruthJets, &b_jetPxCone4TruthJets);
   fChain->SetBranchAddress("jetPyCone4TruthJets", &jetPyCone4TruthJets, &b_jetPyCone4TruthJets);
   fChain->SetBranchAddress("jetPzCone4TruthJets", &jetPzCone4TruthJets, &b_jetPzCone4TruthJets);
   fChain->SetBranchAddress("jetSizeCone4TruthJets", &jetSizeCone4TruthJets, &b_jetSizeCone4TruthJets);
   fChain->SetBranchAddress("jetEmfCone4TruthJets", &jetEmfCone4TruthJets, &b_jetEmfCone4TruthJets);
   fChain->SetBranchAddress("jetErawCone4TruthJets", &jetErawCone4TruthJets, &b_jetErawCone4TruthJets);
   fChain->SetBranchAddress("jetPxrawCone4TruthJets", &jetPxrawCone4TruthJets, &b_jetPxrawCone4TruthJets);
   fChain->SetBranchAddress("jetPyrawCone4TruthJets", &jetPyrawCone4TruthJets, &b_jetPyrawCone4TruthJets);
   fChain->SetBranchAddress("jetPzrawCone4TruthJets", &jetPzrawCone4TruthJets, &b_jetPzrawCone4TruthJets);
   fChain->SetBranchAddress("jetMrawCone4TruthJets", &jetMrawCone4TruthJets, &b_jetMrawCone4TruthJets);
   fChain->SetBranchAddress("MET_ExTruthInt", &MET_ExTruthInt, &b_MET_ExTruthInt);
   fChain->SetBranchAddress("MET_EyTruthInt", &MET_EyTruthInt, &b_MET_EyTruthInt);
   fChain->SetBranchAddress("MET_EtSumTruthInt", &MET_EtSumTruthInt, &b_MET_EtSumTruthInt);
   fChain->SetBranchAddress("MET_ExTruthNonInt", &MET_ExTruthNonInt, &b_MET_ExTruthNonInt);
   fChain->SetBranchAddress("MET_EyTruthNonInt", &MET_EyTruthNonInt, &b_MET_EyTruthNonInt);
   fChain->SetBranchAddress("MET_EtSumTruthNonInt", &MET_EtSumTruthNonInt, &b_MET_EtSumTruthNonInt);
   fChain->SetBranchAddress("MET_ExTruthIntCentral", &MET_ExTruthIntCentral, &b_MET_ExTruthIntCentral);
   fChain->SetBranchAddress("MET_EyTruthIntCentral", &MET_EyTruthIntCentral, &b_MET_EyTruthIntCentral);
   fChain->SetBranchAddress("MET_EtSumTruthIntCentral", &MET_EtSumTruthIntCentral, &b_MET_EtSumTruthIntCentral);
   fChain->SetBranchAddress("MET_ExTruthIntFwd", &MET_ExTruthIntFwd, &b_MET_ExTruthIntFwd);
   fChain->SetBranchAddress("MET_EyTruthIntFwd", &MET_EyTruthIntFwd, &b_MET_EyTruthIntFwd);
   fChain->SetBranchAddress("MET_EtSumTruthIntFwd", &MET_EtSumTruthIntFwd, &b_MET_EtSumTruthIntFwd);
   fChain->SetBranchAddress("MET_ExTruthIntOutOfCov", &MET_ExTruthIntOutOfCov, &b_MET_ExTruthIntOutOfCov);
   fChain->SetBranchAddress("MET_EyTruthIntOutOfCov", &MET_EyTruthIntOutOfCov, &b_MET_EyTruthIntOutOfCov);
   fChain->SetBranchAddress("MET_EtSumTruthIntOutOfCov", &MET_EtSumTruthIntOutOfCov, &b_MET_EtSumTruthIntOutOfCov);
   fChain->SetBranchAddress("MET_ExTruthMuons", &MET_ExTruthMuons, &b_MET_ExTruthMuons);
   fChain->SetBranchAddress("MET_EyTruthMuons", &MET_EyTruthMuons, &b_MET_EyTruthMuons);
   fChain->SetBranchAddress("MET_EtSumTruthMuons", &MET_EtSumTruthMuons, &b_MET_EtSumTruthMuons);
   fChain->SetBranchAddress("MET_ExTruthInt_Pile", &MET_ExTruthInt_Pile, &b_MET_ExTruthInt_Pile);
   fChain->SetBranchAddress("MET_EyTruthInt_Pile", &MET_EyTruthInt_Pile, &b_MET_EyTruthInt_Pile);
   fChain->SetBranchAddress("MET_EtSumTruthInt_Pile", &MET_EtSumTruthInt_Pile, &b_MET_EtSumTruthInt_Pile);
   fChain->SetBranchAddress("MET_ExTruthNonInt_Pile", &MET_ExTruthNonInt_Pile, &b_MET_ExTruthNonInt_Pile);
   fChain->SetBranchAddress("MET_EyTruthNonInt_Pile", &MET_EyTruthNonInt_Pile, &b_MET_EyTruthNonInt_Pile);
   fChain->SetBranchAddress("MET_EtSumTruthNonInt_Pile", &MET_EtSumTruthNonInt_Pile, &b_MET_EtSumTruthNonInt_Pile);
   fChain->SetBranchAddress("MET_ExTruthIntCentral_Pile", &MET_ExTruthIntCentral_Pile, &b_MET_ExTruthIntCentral_Pile);
   fChain->SetBranchAddress("MET_EyTruthIntCentral_Pile", &MET_EyTruthIntCentral_Pile, &b_MET_EyTruthIntCentral_Pile);
   fChain->SetBranchAddress("MET_EtSumTruthIntCentral_Pile", &MET_EtSumTruthIntCentral_Pile, &b_MET_EtSumTruthIntCentral_Pile);
   fChain->SetBranchAddress("MET_ExTruthIntFwd_Pile", &MET_ExTruthIntFwd_Pile, &b_MET_ExTruthIntFwd_Pile);
   fChain->SetBranchAddress("MET_EyTruthIntFwd_Pile", &MET_EyTruthIntFwd_Pile, &b_MET_EyTruthIntFwd_Pile);
   fChain->SetBranchAddress("MET_EtSumTruthIntFwd_Pile", &MET_EtSumTruthIntFwd_Pile, &b_MET_EtSumTruthIntFwd_Pile);
   fChain->SetBranchAddress("MET_ExTruthIntOutOfCov_Pile", &MET_ExTruthIntOutOfCov_Pile, &b_MET_ExTruthIntOutOfCov_Pile);
   fChain->SetBranchAddress("MET_EyTruthIntOutOfCov_Pile", &MET_EyTruthIntOutOfCov_Pile, &b_MET_EyTruthIntOutOfCov_Pile);
   fChain->SetBranchAddress("MET_EtSumTruthIntOutOfCov_Pile", &MET_EtSumTruthIntOutOfCov_Pile, &b_MET_EtSumTruthIntOutOfCov_Pile);
   fChain->SetBranchAddress("MET_ExTruthMuons_Pile", &MET_ExTruthMuons_Pile, &b_MET_ExTruthMuons_Pile);
   fChain->SetBranchAddress("MET_EyTruthMuons_Pile", &MET_EyTruthMuons_Pile, &b_MET_EyTruthMuons_Pile);
   fChain->SetBranchAddress("MET_EtSumTruthMuons_Pile", &MET_EtSumTruthMuons_Pile, &b_MET_EtSumTruthMuons_Pile);
   Notify();
}

Bool_t CollectionTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CollectionTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CollectionTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CollectionTree_cxx

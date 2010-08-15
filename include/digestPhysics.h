//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug 10 23:44:14 2010 by ROOT version 5.22/00
// from TChain digest/
//////////////////////////////////////////////////////////

#ifndef digestPhysics_h
#define digestPhysics_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class digestPhysics {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run_RunNumber;
   Int_t           run_lbn;
   Int_t           run_EventNumber;
   Double_t        kin_imass;
   Double_t        kin_pT_mu;
   Double_t        kin_eta_mu;
   Double_t        kin_cosTheta_mu;
   Bool_t          is_null;
   Bool_t          is_GRL;
   Bool_t          is_L1_MU6;
   Bool_t          is_z0;
   Bool_t          is_d0;
   Bool_t          is_cosThetaDimuCut;
   Bool_t          is_imass;
   Bool_t          is_pT;
   Bool_t          is_eta;

   // List of branches
   TBranch        *b_run_RunNumber;   //!
   TBranch        *b_run_lbn;   //!
   TBranch        *b_run_EventNumber;   //!
   TBranch        *b_kin_imass;   //!
   TBranch        *b_kin_pT_mu;   //!
   TBranch        *b_kin_eta_mu;   //!
   TBranch        *b_kin_cosTheta_mu;   //!
   TBranch        *b_is_null;   //!
   TBranch        *b_is_GRL;   //!
   TBranch        *b_is_L1_MU6;   //!
   TBranch        *b_is_z0;   //!
   TBranch        *b_is_d0;   //!
   TBranch        *b_is_cosThetaDimuCut;   //!
   TBranch        *b_is_imass;   //!
   TBranch        *b_is_pT;   //!
   TBranch        *b_is_eta;   //!

   digestPhysics(TTree *tree=0);
   virtual ~digestPhysics();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef digestPhysics_cxx
digestPhysics::digestPhysics(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("digest");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("digest","");
      chain->Add("digest_datasetdir/offlineTreeDigest.root/digest");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

digestPhysics::~digestPhysics()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t digestPhysics::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t digestPhysics::LoadTree(Long64_t entry)
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

void digestPhysics::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_RunNumber", &run_RunNumber, &b_run_RunNumber);
   fChain->SetBranchAddress("run_lbn", &run_lbn, &b_run_lbn);
   fChain->SetBranchAddress("run_EventNumber", &run_EventNumber, &b_run_EventNumber);
   fChain->SetBranchAddress("kin_imass", &kin_imass, &b_kin_imass);
   fChain->SetBranchAddress("kin_pT_mu", &kin_pT_mu, &b_kin_pT_mu);
   fChain->SetBranchAddress("kin_eta_mu", &kin_eta_mu, &b_kin_eta_mu);
   fChain->SetBranchAddress("kin_cosTheta_mu", &kin_cosTheta_mu, &b_kin_cosTheta_mu);
   fChain->SetBranchAddress("is_null", &is_null, &b_is_null);
   fChain->SetBranchAddress("is_GRL", &is_GRL, &b_is_GRL);
   fChain->SetBranchAddress("is_L1_MU6", &is_L1_MU6, &b_is_L1_MU6);
   fChain->SetBranchAddress("is_z0", &is_z0, &b_is_z0);
   fChain->SetBranchAddress("is_d0", &is_d0, &b_is_d0);
   fChain->SetBranchAddress("is_cosThetaDimuCut", &is_cosThetaDimuCut, &b_is_cosThetaDimuCut);
   fChain->SetBranchAddress("is_imass", &is_imass, &b_is_imass);
   fChain->SetBranchAddress("is_pT", &is_pT, &b_is_pT);
   fChain->SetBranchAddress("is_eta", &is_eta, &b_is_eta);
   Notify();
}

Bool_t digestPhysics::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void digestPhysics::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t digestPhysics::Cut(Long64_t entry)
{
   if(false) cout << "entry=" << entry << endl;
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef digestPhysics_cxx

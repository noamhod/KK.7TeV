//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Aug  1 21:01:25 2010 by ROOT version 5.22/00
// from TChain offline/
//////////////////////////////////////////////////////////

#ifndef offlinePhysics_h
#define offlinePhysics_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class offlinePhysics {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runnumber;
   Int_t           lumiblock;
   Bool_t          GRL;
   Bool_t          L1_MU6;
   vector<float>   *mustaco_E;
   vector<float>   *mustaco_px;
   vector<float>   *mustaco_py;
   vector<float>   *mustaco_pz;
   vector<float>   *mustaco_m;
   vector<float>   *mustaco_c;
   vector<float>   *mustaco_pT;
   vector<float>   *mustaco_eta;
   vector<float>   *mustaco_theta;
   vector<float>   *mustaco_phi;
   vector<float>   *mustaco_d0exPV;
   vector<float>   *mustaco_z0exPV;
   vector<float>   *mustaco_qop;
   vector<unsigned short> *mustaco_allauthor;
   vector<int>     *mustaco_author;

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_lumiblock;   //!
   TBranch        *b_GRL;   //!
   TBranch        *b_L1_MU6;   //!
   TBranch        *b_mustaco_E;   //!
   TBranch        *b_mustaco_px;   //!
   TBranch        *b_mustaco_py;   //!
   TBranch        *b_mustaco_pz;   //!
   TBranch        *b_mustaco_m;   //!
   TBranch        *b_mustaco_c;   //!
   TBranch        *b_mustaco_pT;   //!
   TBranch        *b_mustaco_eta;   //!
   TBranch        *b_mustaco_theta;   //!
   TBranch        *b_mustaco_phi;   //!
   TBranch        *b_mustaco_d0exPV;   //!
   TBranch        *b_mustaco_z0exPV;   //!
   TBranch        *b_mustaco_qop;   //!
   TBranch        *b_mustaco_allauthor;   //!
   TBranch        *b_mustaco_author;   //!

   offlinePhysics(TTree *tree=0);
   virtual ~offlinePhysics();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef offlinePhysics_cxx
offlinePhysics::offlinePhysics(TTree *tree)
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
      tree = (TTree*)gDirectory->Get("offline");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("offline","");
      chain->Add("offline_datasetdir/analysisTrees.root/offline");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

offlinePhysics::~offlinePhysics()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t offlinePhysics::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t offlinePhysics::LoadTree(Long64_t entry)
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

void offlinePhysics::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mustaco_E = 0;
   mustaco_px = 0;
   mustaco_py = 0;
   mustaco_pz = 0;
   mustaco_m = 0;
   mustaco_c = 0;
   mustaco_pT = 0;
   mustaco_eta = 0;
   mustaco_theta = 0;
   mustaco_phi = 0;
   mustaco_d0exPV = 0;
   mustaco_z0exPV = 0;
   mustaco_qop = 0;
   mustaco_allauthor = 0;
   mustaco_author = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("lumiblock", &lumiblock, &b_lumiblock);
   fChain->SetBranchAddress("GRL", &GRL, &b_GRL);
   fChain->SetBranchAddress("L1_MU6", &L1_MU6, &b_L1_MU6);
   fChain->SetBranchAddress("mustaco_E", &mustaco_E, &b_mustaco_E);
   fChain->SetBranchAddress("mustaco_px", &mustaco_px, &b_mustaco_px);
   fChain->SetBranchAddress("mustaco_py", &mustaco_py, &b_mustaco_py);
   fChain->SetBranchAddress("mustaco_pz", &mustaco_pz, &b_mustaco_pz);
   fChain->SetBranchAddress("mustaco_m", &mustaco_m, &b_mustaco_m);
   fChain->SetBranchAddress("mustaco_c", &mustaco_c, &b_mustaco_c);
   fChain->SetBranchAddress("mustaco_pT", &mustaco_pT, &b_mustaco_pT);
   fChain->SetBranchAddress("mustaco_eta", &mustaco_eta, &b_mustaco_eta);
   fChain->SetBranchAddress("mustaco_theta", &mustaco_theta, &b_mustaco_theta);
   fChain->SetBranchAddress("mustaco_phi", &mustaco_phi, &b_mustaco_phi);
   fChain->SetBranchAddress("mustaco_d0exPV", &mustaco_d0exPV, &b_mustaco_d0exPV);
   fChain->SetBranchAddress("mustaco_z0exPV", &mustaco_z0exPV, &b_mustaco_z0exPV);
   fChain->SetBranchAddress("mustaco_qop", &mustaco_qop, &b_mustaco_qop);
   fChain->SetBranchAddress("mustaco_allauthor", &mustaco_allauthor, &b_mustaco_allauthor);
   fChain->SetBranchAddress("mustaco_author", &mustaco_author, &b_mustaco_author);
   Notify();
}

Bool_t offlinePhysics::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void offlinePhysics::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t offlinePhysics::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef offlinePhysics_cxx

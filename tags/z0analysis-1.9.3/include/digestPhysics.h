//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep  2 00:03:14 2010 by ROOT version 5.22/00
// from TTree digest/digest
// found on file: offlineTreeDigest.root
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
   Int_t           RunNumber;
   Int_t           lbn;
   Int_t           EventNumber;
   Int_t           isGRL;
   Int_t           L1_MU6;
   Int_t           mu_staco_n;
   vector<float>   *mu_staco_px;
   vector<float>   *mu_staco_py;
   vector<float>   *mu_staco_pz;
   vector<float>   *mu_staco_E;
   vector<float>   *mu_staco_m;
   vector<float>   *mu_staco_charge;
   vector<float>   *mu_staco_pt;
   vector<float>   *mu_staco_ptcone20;
   vector<float>   *mu_staco_ptcone30;
   vector<float>   *mu_staco_ptcone40;
   vector<float>   *mu_staco_eta;
   vector<float>   *mu_staco_d0_exPV;
   vector<float>   *mu_staco_z0_exPV;
   vector<float>   *mu_staco_me_qoverp;
   vector<float>   *mu_staco_id_qoverp;
   vector<float>   *mu_staco_me_theta;
   vector<float>   *mu_staco_id_theta;
   vector<int>     *mu_staco_isCombinedMuon;
   vector<int>     *mu_staco_nSCTHits;
   vector<int>     *mu_staco_nPixHits;
   Int_t           vxp_n;
   vector<int>     *vxp_nTracks;
   vector<int>     *vxp_type;
   vector<float>   *vxp_z;
   vector<float>   *vxp_z_err;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_isGRL;   //!
   TBranch        *b_L1_MU6;   //!
   TBranch        *b_mu_staco_n;   //!
   TBranch        *b_mu_staco_px;   //!
   TBranch        *b_mu_staco_py;   //!
   TBranch        *b_mu_staco_pz;   //!
   TBranch        *b_mu_staco_E;   //!
   TBranch        *b_mu_staco_m;   //!
   TBranch        *b_mu_staco_charge;   //!
   TBranch        *b_mu_staco_pt;   //!
   TBranch        *b_mu_staco_ptcone20;   //!
   TBranch        *b_mu_staco_ptcone30;   //!
   TBranch        *b_mu_staco_ptcone40;   //!
   TBranch        *b_mu_staco_eta;   //!
   TBranch        *b_mu_staco_d0_exPV;   //!
   TBranch        *b_mu_staco_z0_exPV;   //!
   TBranch        *b_mu_staco_me_qoverp;   //!
   TBranch        *b_mu_staco_id_qoverp;   //!
   TBranch        *b_mu_staco_me_theta;   //!
   TBranch        *b_mu_staco_id_theta;   //!
   TBranch        *b_mu_staco_isCombinedMuon;   //!
   TBranch        *b_mu_staco_nSCTHits;   //!
   TBranch        *b_mu_staco_nPixHits;   //!
   TBranch        *b_vxp_n;   //!
   TBranch        *b_vxp_nTracks;   //!
   TBranch        *b_vxp_type;   //!
   TBranch        *b_vxp_z;   //!
   TBranch        *b_vxp_z_err;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("offlineTreeDigest.root");
      if (!f) {
         f = new TFile("offlineTreeDigest.root");
      }
      tree = (TTree*)gDirectory->Get("digest");

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

   // Set object pointer
   mu_staco_px = 0;
   mu_staco_py = 0;
   mu_staco_pz = 0;
   mu_staco_E = 0;
   mu_staco_m = 0;
   mu_staco_charge = 0;
   mu_staco_pt = 0;
   mu_staco_ptcone20 = 0;
   mu_staco_ptcone30 = 0;
   mu_staco_ptcone40 = 0;
   mu_staco_eta = 0;
   mu_staco_d0_exPV = 0;
   mu_staco_z0_exPV = 0;
   mu_staco_me_qoverp = 0;
   mu_staco_id_qoverp = 0;
   mu_staco_me_theta = 0;
   mu_staco_id_theta = 0;
   mu_staco_isCombinedMuon = 0;
   mu_staco_nSCTHits = 0;
   mu_staco_nPixHits = 0;
   vxp_nTracks = 0;
   vxp_type = 0;
   vxp_z = 0;
   vxp_z_err = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("isGRL", &isGRL, &b_isGRL);
   fChain->SetBranchAddress("L1_MU6", &L1_MU6, &b_L1_MU6);
   fChain->SetBranchAddress("mu_staco_n", &mu_staco_n, &b_mu_staco_n);
   fChain->SetBranchAddress("mu_staco_px", &mu_staco_px, &b_mu_staco_px);
   fChain->SetBranchAddress("mu_staco_py", &mu_staco_py, &b_mu_staco_py);
   fChain->SetBranchAddress("mu_staco_pz", &mu_staco_pz, &b_mu_staco_pz);
   fChain->SetBranchAddress("mu_staco_E", &mu_staco_E, &b_mu_staco_E);
   fChain->SetBranchAddress("mu_staco_m", &mu_staco_m, &b_mu_staco_m);
   fChain->SetBranchAddress("mu_staco_charge", &mu_staco_charge, &b_mu_staco_charge);
   fChain->SetBranchAddress("mu_staco_pt", &mu_staco_pt, &b_mu_staco_pt);
   fChain->SetBranchAddress("mu_staco_ptcone20", &mu_staco_ptcone20, &b_mu_staco_ptcone20);
   fChain->SetBranchAddress("mu_staco_ptcone30", &mu_staco_ptcone30, &b_mu_staco_ptcone30);
   fChain->SetBranchAddress("mu_staco_ptcone40", &mu_staco_ptcone40, &b_mu_staco_ptcone40);
   fChain->SetBranchAddress("mu_staco_eta", &mu_staco_eta, &b_mu_staco_eta);
   fChain->SetBranchAddress("mu_staco_d0_exPV", &mu_staco_d0_exPV, &b_mu_staco_d0_exPV);
   fChain->SetBranchAddress("mu_staco_z0_exPV", &mu_staco_z0_exPV, &b_mu_staco_z0_exPV);
   fChain->SetBranchAddress("mu_staco_me_qoverp", &mu_staco_me_qoverp, &b_mu_staco_me_qoverp);
   fChain->SetBranchAddress("mu_staco_id_qoverp", &mu_staco_id_qoverp, &b_mu_staco_id_qoverp);
   fChain->SetBranchAddress("mu_staco_me_theta", &mu_staco_me_theta, &b_mu_staco_me_theta);
   fChain->SetBranchAddress("mu_staco_id_theta", &mu_staco_id_theta, &b_mu_staco_id_theta);
   fChain->SetBranchAddress("mu_staco_isCombinedMuon", &mu_staco_isCombinedMuon, &b_mu_staco_isCombinedMuon);
   fChain->SetBranchAddress("mu_staco_nSCTHits", &mu_staco_nSCTHits, &b_mu_staco_nSCTHits);
   fChain->SetBranchAddress("mu_staco_nPixHits", &mu_staco_nPixHits, &b_mu_staco_nPixHits);
   fChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
   fChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
   fChain->SetBranchAddress("vxp_type", &vxp_type, &b_vxp_type);
   fChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
   fChain->SetBranchAddress("vxp_z_err", &vxp_z_err, &b_vxp_z_err);
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
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef digestPhysics_cxx
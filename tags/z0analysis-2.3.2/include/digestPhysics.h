//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov  8 10:08:11 2010 by ROOT version 5.22/00
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
   Int_t           isGRL;
   string          *period;
   vector<string>  *triggers;
   Int_t           RunNumber;
   Int_t           lbn;
   Int_t           EventNumber;
   Int_t           L1_MU0;
   Int_t           L1_MU10;
   Int_t           L1_MU15;
   Int_t           L1_MU20;
   Int_t           L1_MU6;
   Int_t           EF_mu10;
   Int_t           EF_mu10_MG;
   Int_t           EF_mu10_MSonly;
   Int_t           EF_mu10_MSonly_tight;
   Int_t           EF_mu10_NoAlg;
   Int_t           EF_mu10_tight;
   Int_t           EF_mu10i_loose;
   Int_t           EF_mu13;
   Int_t           EF_mu13_MG;
   Int_t           EF_mu13_MG_tight;
   Int_t           EF_mu13_tight;
   Int_t           EF_mu15;
   Int_t           EF_mu15_NoAlg;
   Int_t           EF_mu20;
   Int_t           EF_mu20_MSonly;
   Int_t           EF_mu20_NoAlg;
   Int_t           EF_mu20_slow;
   Int_t           EF_mu30_MSonly;
   Int_t           EF_mu4;
   Int_t           EF_mu40_MSonly;
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
   vector<float>   *mu_staco_phi;
   vector<float>   *mu_staco_d0_exPV;
   vector<float>   *mu_staco_z0_exPV;
   vector<unsigned short> *mu_staco_allauthor;
   vector<int>     *mu_staco_author;
   vector<float>   *mu_staco_matchchi2;
   vector<int>     *mu_staco_matchndof;
   vector<float>   *mu_staco_me_qoverp;
   vector<float>   *mu_staco_id_qoverp;
   vector<float>   *mu_staco_me_theta;
   vector<float>   *mu_staco_id_theta;
   vector<int>     *mu_staco_isCombinedMuon;
   vector<int>     *mu_staco_nSCTHits;
   vector<int>     *mu_staco_nPixHits;
   vector<int>     *mu_staco_nMDTBIHits;
   vector<int>     *mu_staco_nMDTBMHits;
   vector<int>     *mu_staco_nMDTBOHits;
   vector<int>     *mu_staco_nMDTBEEHits;
   vector<int>     *mu_staco_nMDTBIS78Hits;
   vector<int>     *mu_staco_nMDTEIHits;
   vector<int>     *mu_staco_nMDTEMHits;
   vector<int>     *mu_staco_nMDTEOHits;
   vector<int>     *mu_staco_nMDTEEHits;
   vector<int>     *mu_staco_nRPCLayer1EtaHits;
   vector<int>     *mu_staco_nRPCLayer2EtaHits;
   vector<int>     *mu_staco_nRPCLayer3EtaHits;
   vector<int>     *mu_staco_nRPCLayer1PhiHits;
   vector<int>     *mu_staco_nRPCLayer2PhiHits;
   vector<int>     *mu_staco_nRPCLayer3PhiHits;
   vector<int>     *mu_staco_nTGCLayer1EtaHits;
   vector<int>     *mu_staco_nTGCLayer2EtaHits;
   vector<int>     *mu_staco_nTGCLayer3EtaHits;
   vector<int>     *mu_staco_nTGCLayer4EtaHits;
   vector<int>     *mu_staco_nTGCLayer1PhiHits;
   vector<int>     *mu_staco_nTGCLayer2PhiHits;
   vector<int>     *mu_staco_nTGCLayer3PhiHits;
   vector<int>     *mu_staco_nTGCLayer4PhiHits;
   Int_t           mu_muid_n;
   vector<float>   *mu_muid_px;
   vector<float>   *mu_muid_py;
   vector<float>   *mu_muid_pz;
   vector<float>   *mu_muid_E;
   vector<float>   *mu_muid_m;
   vector<float>   *mu_muid_charge;
   vector<float>   *mu_muid_pt;
   vector<float>   *mu_muid_ptcone20;
   vector<float>   *mu_muid_ptcone30;
   vector<float>   *mu_muid_ptcone40;
   vector<float>   *mu_muid_eta;
   vector<float>   *mu_muid_phi;
   vector<float>   *mu_muid_d0_exPV;
   vector<float>   *mu_muid_z0_exPV;
   vector<unsigned short> *mu_muid_allauthor;
   vector<int>     *mu_muid_author;
   vector<float>   *mu_muid_matchchi2;
   vector<int>     *mu_muid_matchndof;
   vector<float>   *mu_muid_me_qoverp;
   vector<float>   *mu_muid_id_qoverp;
   vector<float>   *mu_muid_me_theta;
   vector<float>   *mu_muid_id_theta;
   vector<int>     *mu_muid_isCombinedMuon;
   vector<int>     *mu_muid_nSCTHits;
   vector<int>     *mu_muid_nPixHits;
   vector<int>     *mu_muid_nMDTBIHits;
   vector<int>     *mu_muid_nMDTBMHits;
   vector<int>     *mu_muid_nMDTBOHits;
   vector<int>     *mu_muid_nMDTBEEHits;
   vector<int>     *mu_muid_nMDTBIS78Hits;
   vector<int>     *mu_muid_nMDTEIHits;
   vector<int>     *mu_muid_nMDTEMHits;
   vector<int>     *mu_muid_nMDTEOHits;
   vector<int>     *mu_muid_nMDTEEHits;
   vector<int>     *mu_muid_nRPCLayer1EtaHits;
   vector<int>     *mu_muid_nRPCLayer2EtaHits;
   vector<int>     *mu_muid_nRPCLayer3EtaHits;
   vector<int>     *mu_muid_nRPCLayer1PhiHits;
   vector<int>     *mu_muid_nRPCLayer2PhiHits;
   vector<int>     *mu_muid_nRPCLayer3PhiHits;
   vector<int>     *mu_muid_nTGCLayer1EtaHits;
   vector<int>     *mu_muid_nTGCLayer2EtaHits;
   vector<int>     *mu_muid_nTGCLayer3EtaHits;
   vector<int>     *mu_muid_nTGCLayer4EtaHits;
   vector<int>     *mu_muid_nTGCLayer1PhiHits;
   vector<int>     *mu_muid_nTGCLayer2PhiHits;
   vector<int>     *mu_muid_nTGCLayer3PhiHits;
   vector<int>     *mu_muid_nTGCLayer4PhiHits;
   Int_t           vxp_n;
   vector<int>     *vxp_nTracks;
   vector<int>     *vxp_type;
   vector<float>   *vxp_z;
   vector<float>   *vxp_z_err;

   // List of branches
   TBranch        *b_isGRL;   //!
   TBranch        *b_period;   //!
   TBranch        *b_triggers;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_L1_MU0;   //!
   TBranch        *b_L1_MU10;   //!
   TBranch        *b_L1_MU15;   //!
   TBranch        *b_L1_MU20;   //!
   TBranch        *b_L1_MU6;   //!
   TBranch        *b_EF_mu10;   //!
   TBranch        *b_EF_mu10_MG;   //!
   TBranch        *b_EF_mu10_MSonly;   //!
   TBranch        *b_EF_mu10_MSonly_tight;   //!
   TBranch        *b_EF_mu10_NoAlg;   //!
   TBranch        *b_EF_mu10_tight;   //!
   TBranch        *b_EF_mu10i_loose;   //!
   TBranch        *b_EF_mu13;   //!
   TBranch        *b_EF_mu13_MG;   //!
   TBranch        *b_EF_mu13_MG_tight;   //!
   TBranch        *b_EF_mu13_tight;   //!
   TBranch        *b_EF_mu15;   //!
   TBranch        *b_EF_mu15_NoAlg;   //!
   TBranch        *b_EF_mu20;   //!
   TBranch        *b_EF_mu20_MSonly;   //!
   TBranch        *b_EF_mu20_NoAlg;   //!
   TBranch        *b_EF_mu20_slow;   //!
   TBranch        *b_EF_mu30_MSonly;   //!
   TBranch        *b_EF_mu4;   //!
   TBranch        *b_EF_mu40_MSonly;   //!
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
   TBranch        *b_mu_staco_phi;   //!
   TBranch        *b_mu_staco_d0_exPV;   //!
   TBranch        *b_mu_staco_z0_exPV;   //!
   TBranch        *b_mu_staco_allauthor;   //!
   TBranch        *b_mu_staco_author;   //!
   TBranch        *b_mu_staco_matchchi2;   //!
   TBranch        *b_mu_staco_matchndof;   //!
   TBranch        *b_mu_staco_me_qoverp;   //!
   TBranch        *b_mu_staco_id_qoverp;   //!
   TBranch        *b_mu_staco_me_theta;   //!
   TBranch        *b_mu_staco_id_theta;   //!
   TBranch        *b_mu_staco_isCombinedMuon;   //!
   TBranch        *b_mu_staco_nSCTHits;   //!
   TBranch        *b_mu_staco_nPixHits;   //!
   TBranch        *b_mu_staco_nMDTBIHits;   //!
   TBranch        *b_mu_staco_nMDTBMHits;   //!
   TBranch        *b_mu_staco_nMDTBOHits;   //!
   TBranch        *b_mu_staco_nMDTBEEHits;   //!
   TBranch        *b_mu_staco_nMDTBIS78Hits;   //!
   TBranch        *b_mu_staco_nMDTEIHits;   //!
   TBranch        *b_mu_staco_nMDTEMHits;   //!
   TBranch        *b_mu_staco_nMDTEOHits;   //!
   TBranch        *b_mu_staco_nMDTEEHits;   //!
   TBranch        *b_mu_staco_nRPCLayer1EtaHits;   //!
   TBranch        *b_mu_staco_nRPCLayer2EtaHits;   //!
   TBranch        *b_mu_staco_nRPCLayer3EtaHits;   //!
   TBranch        *b_mu_staco_nRPCLayer1PhiHits;   //!
   TBranch        *b_mu_staco_nRPCLayer2PhiHits;   //!
   TBranch        *b_mu_staco_nRPCLayer3PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer1EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer2EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer3EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer4EtaHits;   //!
   TBranch        *b_mu_staco_nTGCLayer1PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer2PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer3PhiHits;   //!
   TBranch        *b_mu_staco_nTGCLayer4PhiHits;   //!
   TBranch        *b_mu_muid_n;   //!
   TBranch        *b_mu_muid_px;   //!
   TBranch        *b_mu_muid_py;   //!
   TBranch        *b_mu_muid_pz;   //!
   TBranch        *b_mu_muid_E;   //!
   TBranch        *b_mu_muid_m;   //!
   TBranch        *b_mu_muid_charge;   //!
   TBranch        *b_mu_muid_pt;   //!
   TBranch        *b_mu_muid_ptcone20;   //!
   TBranch        *b_mu_muid_ptcone30;   //!
   TBranch        *b_mu_muid_ptcone40;   //!
   TBranch        *b_mu_muid_eta;   //!
   TBranch        *b_mu_muid_phi;   //!
   TBranch        *b_mu_muid_d0_exPV;   //!
   TBranch        *b_mu_muid_z0_exPV;   //!
   TBranch        *b_mu_muid_allauthor;   //!
   TBranch        *b_mu_muid_author;   //!
   TBranch        *b_mu_muid_matchchi2;   //!
   TBranch        *b_mu_muid_matchndof;   //!
   TBranch        *b_mu_muid_me_qoverp;   //!
   TBranch        *b_mu_muid_id_qoverp;   //!
   TBranch        *b_mu_muid_me_theta;   //!
   TBranch        *b_mu_muid_id_theta;   //!
   TBranch        *b_mu_muid_isCombinedMuon;   //!
   TBranch        *b_mu_muid_nSCTHits;   //!
   TBranch        *b_mu_muid_nPixHits;   //!
   TBranch        *b_mu_muid_nMDTBIHits;   //!
   TBranch        *b_mu_muid_nMDTBMHits;   //!
   TBranch        *b_mu_muid_nMDTBOHits;   //!
   TBranch        *b_mu_muid_nMDTBEEHits;   //!
   TBranch        *b_mu_muid_nMDTBIS78Hits;   //!
   TBranch        *b_mu_muid_nMDTEIHits;   //!
   TBranch        *b_mu_muid_nMDTEMHits;   //!
   TBranch        *b_mu_muid_nMDTEOHits;   //!
   TBranch        *b_mu_muid_nMDTEEHits;   //!
   TBranch        *b_mu_muid_nRPCLayer1EtaHits;   //!
   TBranch        *b_mu_muid_nRPCLayer2EtaHits;   //!
   TBranch        *b_mu_muid_nRPCLayer3EtaHits;   //!
   TBranch        *b_mu_muid_nRPCLayer1PhiHits;   //!
   TBranch        *b_mu_muid_nRPCLayer2PhiHits;   //!
   TBranch        *b_mu_muid_nRPCLayer3PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer1EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer2EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer3EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer4EtaHits;   //!
   TBranch        *b_mu_muid_nTGCLayer1PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer2PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer3PhiHits;   //!
   TBranch        *b_mu_muid_nTGCLayer4PhiHits;   //!
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
   //delete fChain->GetCurrentFile();
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
   period = 0;
   triggers = 0;
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
   mu_staco_phi = 0;
   mu_staco_d0_exPV = 0;
   mu_staco_z0_exPV = 0;
   mu_staco_allauthor = 0;
   mu_staco_author = 0;
   mu_staco_matchchi2 = 0;
   mu_staco_matchndof = 0;
   mu_staco_me_qoverp = 0;
   mu_staco_id_qoverp = 0;
   mu_staco_me_theta = 0;
   mu_staco_id_theta = 0;
   mu_staco_isCombinedMuon = 0;
   mu_staco_nSCTHits = 0;
   mu_staco_nPixHits = 0;
   mu_staco_nMDTBIHits = 0;
   mu_staco_nMDTBMHits = 0;
   mu_staco_nMDTBOHits = 0;
   mu_staco_nMDTBEEHits = 0;
   mu_staco_nMDTBIS78Hits = 0;
   mu_staco_nMDTEIHits = 0;
   mu_staco_nMDTEMHits = 0;
   mu_staco_nMDTEOHits = 0;
   mu_staco_nMDTEEHits = 0;
   mu_staco_nRPCLayer1EtaHits = 0;
   mu_staco_nRPCLayer2EtaHits = 0;
   mu_staco_nRPCLayer3EtaHits = 0;
   mu_staco_nRPCLayer1PhiHits = 0;
   mu_staco_nRPCLayer2PhiHits = 0;
   mu_staco_nRPCLayer3PhiHits = 0;
   mu_staco_nTGCLayer1EtaHits = 0;
   mu_staco_nTGCLayer2EtaHits = 0;
   mu_staco_nTGCLayer3EtaHits = 0;
   mu_staco_nTGCLayer4EtaHits = 0;
   mu_staco_nTGCLayer1PhiHits = 0;
   mu_staco_nTGCLayer2PhiHits = 0;
   mu_staco_nTGCLayer3PhiHits = 0;
   mu_staco_nTGCLayer4PhiHits = 0;
   mu_muid_px = 0;
   mu_muid_py = 0;
   mu_muid_pz = 0;
   mu_muid_E = 0;
   mu_muid_m = 0;
   mu_muid_charge = 0;
   mu_muid_pt = 0;
   mu_muid_ptcone20 = 0;
   mu_muid_ptcone30 = 0;
   mu_muid_ptcone40 = 0;
   mu_muid_eta = 0;
   mu_muid_phi = 0;
   mu_muid_d0_exPV = 0;
   mu_muid_z0_exPV = 0;
   mu_muid_allauthor = 0;
   mu_muid_author = 0;
   mu_muid_matchchi2 = 0;
   mu_muid_matchndof = 0;
   mu_muid_me_qoverp = 0;
   mu_muid_id_qoverp = 0;
   mu_muid_me_theta = 0;
   mu_muid_id_theta = 0;
   mu_muid_isCombinedMuon = 0;
   mu_muid_nSCTHits = 0;
   mu_muid_nPixHits = 0;
   mu_muid_nMDTBIHits = 0;
   mu_muid_nMDTBMHits = 0;
   mu_muid_nMDTBOHits = 0;
   mu_muid_nMDTBEEHits = 0;
   mu_muid_nMDTBIS78Hits = 0;
   mu_muid_nMDTEIHits = 0;
   mu_muid_nMDTEMHits = 0;
   mu_muid_nMDTEOHits = 0;
   mu_muid_nMDTEEHits = 0;
   mu_muid_nRPCLayer1EtaHits = 0;
   mu_muid_nRPCLayer2EtaHits = 0;
   mu_muid_nRPCLayer3EtaHits = 0;
   mu_muid_nRPCLayer1PhiHits = 0;
   mu_muid_nRPCLayer2PhiHits = 0;
   mu_muid_nRPCLayer3PhiHits = 0;
   mu_muid_nTGCLayer1EtaHits = 0;
   mu_muid_nTGCLayer2EtaHits = 0;
   mu_muid_nTGCLayer3EtaHits = 0;
   mu_muid_nTGCLayer4EtaHits = 0;
   mu_muid_nTGCLayer1PhiHits = 0;
   mu_muid_nTGCLayer2PhiHits = 0;
   mu_muid_nTGCLayer3PhiHits = 0;
   mu_muid_nTGCLayer4PhiHits = 0;
   vxp_nTracks = 0;
   vxp_type = 0;
   vxp_z = 0;
   vxp_z_err = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("isGRL", &isGRL, &b_isGRL);
   fChain->SetBranchAddress("period", &period, &b_period);
   fChain->SetBranchAddress("triggers", &triggers, &b_triggers);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("L1_MU0", &L1_MU0, &b_L1_MU0);
   fChain->SetBranchAddress("L1_MU10", &L1_MU10, &b_L1_MU10);
   fChain->SetBranchAddress("L1_MU15", &L1_MU15, &b_L1_MU15);
   fChain->SetBranchAddress("L1_MU20", &L1_MU20, &b_L1_MU20);
   fChain->SetBranchAddress("L1_MU6", &L1_MU6, &b_L1_MU6);
   fChain->SetBranchAddress("EF_mu10", &EF_mu10, &b_EF_mu10);
   fChain->SetBranchAddress("EF_mu10_MG", &EF_mu10_MG, &b_EF_mu10_MG);
   fChain->SetBranchAddress("EF_mu10_MSonly", &EF_mu10_MSonly, &b_EF_mu10_MSonly);
   fChain->SetBranchAddress("EF_mu10_MSonly_tight", &EF_mu10_MSonly_tight, &b_EF_mu10_MSonly_tight);
   fChain->SetBranchAddress("EF_mu10_NoAlg", &EF_mu10_NoAlg, &b_EF_mu10_NoAlg);
   fChain->SetBranchAddress("EF_mu10_tight", &EF_mu10_tight, &b_EF_mu10_tight);
   fChain->SetBranchAddress("EF_mu10i_loose", &EF_mu10i_loose, &b_EF_mu10i_loose);
   fChain->SetBranchAddress("EF_mu13", &EF_mu13, &b_EF_mu13);
   fChain->SetBranchAddress("EF_mu13_MG", &EF_mu13_MG, &b_EF_mu13_MG);
   fChain->SetBranchAddress("EF_mu13_MG_tight", &EF_mu13_MG_tight, &b_EF_mu13_MG_tight);
   fChain->SetBranchAddress("EF_mu13_tight", &EF_mu13_tight, &b_EF_mu13_tight);
   fChain->SetBranchAddress("EF_mu15", &EF_mu15, &b_EF_mu15);
   fChain->SetBranchAddress("EF_mu15_NoAlg", &EF_mu15_NoAlg, &b_EF_mu15_NoAlg);
   fChain->SetBranchAddress("EF_mu20", &EF_mu20, &b_EF_mu20);
   fChain->SetBranchAddress("EF_mu20_MSonly", &EF_mu20_MSonly, &b_EF_mu20_MSonly);
   fChain->SetBranchAddress("EF_mu20_NoAlg", &EF_mu20_NoAlg, &b_EF_mu20_NoAlg);
   fChain->SetBranchAddress("EF_mu20_slow", &EF_mu20_slow, &b_EF_mu20_slow);
   fChain->SetBranchAddress("EF_mu30_MSonly", &EF_mu30_MSonly, &b_EF_mu30_MSonly);
   fChain->SetBranchAddress("EF_mu4", &EF_mu4, &b_EF_mu4);
   fChain->SetBranchAddress("EF_mu40_MSonly", &EF_mu40_MSonly, &b_EF_mu40_MSonly);
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
   fChain->SetBranchAddress("mu_staco_phi", &mu_staco_phi, &b_mu_staco_phi);
   fChain->SetBranchAddress("mu_staco_d0_exPV", &mu_staco_d0_exPV, &b_mu_staco_d0_exPV);
   fChain->SetBranchAddress("mu_staco_z0_exPV", &mu_staco_z0_exPV, &b_mu_staco_z0_exPV);
   fChain->SetBranchAddress("mu_staco_allauthor", &mu_staco_allauthor, &b_mu_staco_allauthor);
   fChain->SetBranchAddress("mu_staco_author", &mu_staco_author, &b_mu_staco_author);
   fChain->SetBranchAddress("mu_staco_matchchi2", &mu_staco_matchchi2, &b_mu_staco_matchchi2);
   fChain->SetBranchAddress("mu_staco_matchndof", &mu_staco_matchndof, &b_mu_staco_matchndof);
   fChain->SetBranchAddress("mu_staco_me_qoverp", &mu_staco_me_qoverp, &b_mu_staco_me_qoverp);
   fChain->SetBranchAddress("mu_staco_id_qoverp", &mu_staco_id_qoverp, &b_mu_staco_id_qoverp);
   fChain->SetBranchAddress("mu_staco_me_theta", &mu_staco_me_theta, &b_mu_staco_me_theta);
   fChain->SetBranchAddress("mu_staco_id_theta", &mu_staco_id_theta, &b_mu_staco_id_theta);
   fChain->SetBranchAddress("mu_staco_isCombinedMuon", &mu_staco_isCombinedMuon, &b_mu_staco_isCombinedMuon);
   fChain->SetBranchAddress("mu_staco_nSCTHits", &mu_staco_nSCTHits, &b_mu_staco_nSCTHits);
   fChain->SetBranchAddress("mu_staco_nPixHits", &mu_staco_nPixHits, &b_mu_staco_nPixHits);
   fChain->SetBranchAddress("mu_staco_nMDTBIHits", &mu_staco_nMDTBIHits, &b_mu_staco_nMDTBIHits);
   fChain->SetBranchAddress("mu_staco_nMDTBMHits", &mu_staco_nMDTBMHits, &b_mu_staco_nMDTBMHits);
   fChain->SetBranchAddress("mu_staco_nMDTBOHits", &mu_staco_nMDTBOHits, &b_mu_staco_nMDTBOHits);
   fChain->SetBranchAddress("mu_staco_nMDTBEEHits", &mu_staco_nMDTBEEHits, &b_mu_staco_nMDTBEEHits);
   fChain->SetBranchAddress("mu_staco_nMDTBIS78Hits", &mu_staco_nMDTBIS78Hits, &b_mu_staco_nMDTBIS78Hits);
   fChain->SetBranchAddress("mu_staco_nMDTEIHits", &mu_staco_nMDTEIHits, &b_mu_staco_nMDTEIHits);
   fChain->SetBranchAddress("mu_staco_nMDTEMHits", &mu_staco_nMDTEMHits, &b_mu_staco_nMDTEMHits);
   fChain->SetBranchAddress("mu_staco_nMDTEOHits", &mu_staco_nMDTEOHits, &b_mu_staco_nMDTEOHits);
   fChain->SetBranchAddress("mu_staco_nMDTEEHits", &mu_staco_nMDTEEHits, &b_mu_staco_nMDTEEHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer1EtaHits", &mu_staco_nRPCLayer1EtaHits, &b_mu_staco_nRPCLayer1EtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer2EtaHits", &mu_staco_nRPCLayer2EtaHits, &b_mu_staco_nRPCLayer2EtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer3EtaHits", &mu_staco_nRPCLayer3EtaHits, &b_mu_staco_nRPCLayer3EtaHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer1PhiHits", &mu_staco_nRPCLayer1PhiHits, &b_mu_staco_nRPCLayer1PhiHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer2PhiHits", &mu_staco_nRPCLayer2PhiHits, &b_mu_staco_nRPCLayer2PhiHits);
   fChain->SetBranchAddress("mu_staco_nRPCLayer3PhiHits", &mu_staco_nRPCLayer3PhiHits, &b_mu_staco_nRPCLayer3PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer1EtaHits", &mu_staco_nTGCLayer1EtaHits, &b_mu_staco_nTGCLayer1EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer2EtaHits", &mu_staco_nTGCLayer2EtaHits, &b_mu_staco_nTGCLayer2EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer3EtaHits", &mu_staco_nTGCLayer3EtaHits, &b_mu_staco_nTGCLayer3EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer4EtaHits", &mu_staco_nTGCLayer4EtaHits, &b_mu_staco_nTGCLayer4EtaHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer1PhiHits", &mu_staco_nTGCLayer1PhiHits, &b_mu_staco_nTGCLayer1PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer2PhiHits", &mu_staco_nTGCLayer2PhiHits, &b_mu_staco_nTGCLayer2PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer3PhiHits", &mu_staco_nTGCLayer3PhiHits, &b_mu_staco_nTGCLayer3PhiHits);
   fChain->SetBranchAddress("mu_staco_nTGCLayer4PhiHits", &mu_staco_nTGCLayer4PhiHits, &b_mu_staco_nTGCLayer4PhiHits);
   fChain->SetBranchAddress("mu_muid_n", &mu_muid_n, &b_mu_muid_n);
   fChain->SetBranchAddress("mu_muid_px", &mu_muid_px, &b_mu_muid_px);
   fChain->SetBranchAddress("mu_muid_py", &mu_muid_py, &b_mu_muid_py);
   fChain->SetBranchAddress("mu_muid_pz", &mu_muid_pz, &b_mu_muid_pz);
   fChain->SetBranchAddress("mu_muid_E", &mu_muid_E, &b_mu_muid_E);
   fChain->SetBranchAddress("mu_muid_m", &mu_muid_m, &b_mu_muid_m);
   fChain->SetBranchAddress("mu_muid_charge", &mu_muid_charge, &b_mu_muid_charge);
   fChain->SetBranchAddress("mu_muid_pt", &mu_muid_pt, &b_mu_muid_pt);
   fChain->SetBranchAddress("mu_muid_ptcone20", &mu_muid_ptcone20, &b_mu_muid_ptcone20);
   fChain->SetBranchAddress("mu_muid_ptcone30", &mu_muid_ptcone30, &b_mu_muid_ptcone30);
   fChain->SetBranchAddress("mu_muid_ptcone40", &mu_muid_ptcone40, &b_mu_muid_ptcone40);
   fChain->SetBranchAddress("mu_muid_eta", &mu_muid_eta, &b_mu_muid_eta);
   fChain->SetBranchAddress("mu_muid_phi", &mu_muid_phi, &b_mu_muid_phi);
   fChain->SetBranchAddress("mu_muid_d0_exPV", &mu_muid_d0_exPV, &b_mu_muid_d0_exPV);
   fChain->SetBranchAddress("mu_muid_z0_exPV", &mu_muid_z0_exPV, &b_mu_muid_z0_exPV);
   fChain->SetBranchAddress("mu_muid_allauthor", &mu_muid_allauthor, &b_mu_muid_allauthor);
   fChain->SetBranchAddress("mu_muid_author", &mu_muid_author, &b_mu_muid_author);
   fChain->SetBranchAddress("mu_muid_matchchi2", &mu_muid_matchchi2, &b_mu_muid_matchchi2);
   fChain->SetBranchAddress("mu_muid_matchndof", &mu_muid_matchndof, &b_mu_muid_matchndof);
   fChain->SetBranchAddress("mu_muid_me_qoverp", &mu_muid_me_qoverp, &b_mu_muid_me_qoverp);
   fChain->SetBranchAddress("mu_muid_id_qoverp", &mu_muid_id_qoverp, &b_mu_muid_id_qoverp);
   fChain->SetBranchAddress("mu_muid_me_theta", &mu_muid_me_theta, &b_mu_muid_me_theta);
   fChain->SetBranchAddress("mu_muid_id_theta", &mu_muid_id_theta, &b_mu_muid_id_theta);
   fChain->SetBranchAddress("mu_muid_isCombinedMuon", &mu_muid_isCombinedMuon, &b_mu_muid_isCombinedMuon);
   fChain->SetBranchAddress("mu_muid_nSCTHits", &mu_muid_nSCTHits, &b_mu_muid_nSCTHits);
   fChain->SetBranchAddress("mu_muid_nPixHits", &mu_muid_nPixHits, &b_mu_muid_nPixHits);
   fChain->SetBranchAddress("mu_muid_nMDTBIHits", &mu_muid_nMDTBIHits, &b_mu_muid_nMDTBIHits);
   fChain->SetBranchAddress("mu_muid_nMDTBMHits", &mu_muid_nMDTBMHits, &b_mu_muid_nMDTBMHits);
   fChain->SetBranchAddress("mu_muid_nMDTBOHits", &mu_muid_nMDTBOHits, &b_mu_muid_nMDTBOHits);
   fChain->SetBranchAddress("mu_muid_nMDTBEEHits", &mu_muid_nMDTBEEHits, &b_mu_muid_nMDTBEEHits);
   fChain->SetBranchAddress("mu_muid_nMDTBIS78Hits", &mu_muid_nMDTBIS78Hits, &b_mu_muid_nMDTBIS78Hits);
   fChain->SetBranchAddress("mu_muid_nMDTEIHits", &mu_muid_nMDTEIHits, &b_mu_muid_nMDTEIHits);
   fChain->SetBranchAddress("mu_muid_nMDTEMHits", &mu_muid_nMDTEMHits, &b_mu_muid_nMDTEMHits);
   fChain->SetBranchAddress("mu_muid_nMDTEOHits", &mu_muid_nMDTEOHits, &b_mu_muid_nMDTEOHits);
   fChain->SetBranchAddress("mu_muid_nMDTEEHits", &mu_muid_nMDTEEHits, &b_mu_muid_nMDTEEHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer1EtaHits", &mu_muid_nRPCLayer1EtaHits, &b_mu_muid_nRPCLayer1EtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer2EtaHits", &mu_muid_nRPCLayer2EtaHits, &b_mu_muid_nRPCLayer2EtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer3EtaHits", &mu_muid_nRPCLayer3EtaHits, &b_mu_muid_nRPCLayer3EtaHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer1PhiHits", &mu_muid_nRPCLayer1PhiHits, &b_mu_muid_nRPCLayer1PhiHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer2PhiHits", &mu_muid_nRPCLayer2PhiHits, &b_mu_muid_nRPCLayer2PhiHits);
   fChain->SetBranchAddress("mu_muid_nRPCLayer3PhiHits", &mu_muid_nRPCLayer3PhiHits, &b_mu_muid_nRPCLayer3PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer1EtaHits", &mu_muid_nTGCLayer1EtaHits, &b_mu_muid_nTGCLayer1EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer2EtaHits", &mu_muid_nTGCLayer2EtaHits, &b_mu_muid_nTGCLayer2EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer3EtaHits", &mu_muid_nTGCLayer3EtaHits, &b_mu_muid_nTGCLayer3EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer4EtaHits", &mu_muid_nTGCLayer4EtaHits, &b_mu_muid_nTGCLayer4EtaHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer1PhiHits", &mu_muid_nTGCLayer1PhiHits, &b_mu_muid_nTGCLayer1PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer2PhiHits", &mu_muid_nTGCLayer2PhiHits, &b_mu_muid_nTGCLayer2PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer3PhiHits", &mu_muid_nTGCLayer3PhiHits, &b_mu_muid_nTGCLayer3PhiHits);
   fChain->SetBranchAddress("mu_muid_nTGCLayer4PhiHits", &mu_muid_nTGCLayer4PhiHits, &b_mu_muid_nTGCLayer4PhiHits);
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
   cout << "entry = " << entry << endl;
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef digestPhysics_cxx

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 28 14:49:57 2010 by ROOT version 5.22/00
// from TTree offline/offline
// found on file: user.hod.001239._00003.mcWZphys.root
//////////////////////////////////////////////////////////

#ifndef mcOfflinePhysics_h
#define mcOfflinePhysics_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class mcOfflinePhysics {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           lbn;
   Int_t           EventNumber;
   Int_t           isGRL;
   Int_t           L1_MU6;
   Int_t           EF_mu10;
   Int_t           EF_mu13;
   Int_t           EF_mu15;
   Int_t           EF_mu20;
   Int_t           EF_mu4;
   Int_t           EF_mu6;
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
   Int_t           vxp_n;
   vector<int>     *vxp_nTracks;
   vector<int>     *vxp_type;
   vector<float>   *vxp_z;
   vector<float>   *vxp_z_err;
   vector<float>   *mu_staco_truth_E;
   vector<float>   *mu_staco_truth_pt;
   vector<float>   *mu_staco_truth_eta;
   vector<float>   *mu_staco_truth_phi;
   vector<int>     *mu_staco_truth_type;
   vector<int>     *mu_staco_truth_mothertype;
   vector<int>     *mu_staco_truth_barcode;
   vector<int>     *mu_staco_truth_motherbarcode;
   vector<int>     *mu_staco_truth_status;
   vector<float>   *mu_staco_truth_dr;
   vector<int>     *mu_staco_truth_matched;
   vector<float>   *mu_muid_truth_E;
   vector<float>   *mu_muid_truth_pt;
   vector<float>   *mu_muid_truth_eta;
   vector<float>   *mu_muid_truth_phi;
   vector<int>     *mu_muid_truth_type;
   vector<int>     *mu_muid_truth_mothertype;
   vector<int>     *mu_muid_truth_barcode;
   vector<int>     *mu_muid_truth_motherbarcode;
   vector<int>     *mu_muid_truth_status;
   vector<float>   *mu_muid_truth_dr;
   vector<int>     *mu_muid_truth_matched;
   Int_t           muonTruth_n;
   vector<float>   *muonTruth_pt;
   vector<float>   *muonTruth_m;
   vector<float>   *muonTruth_eta;
   vector<float>   *muonTruth_phi;
   vector<float>   *muonTruth_charge;
   vector<int>     *muonTruth_PDGID;
   vector<int>     *muonTruth_type;
   vector<int>     *muonTruth_origin;
   Int_t           mcevt_n;
   vector<int>     *mcevt_signal_process_id;
   vector<int>     *mcevt_event_number;
   vector<double>  *mcevt_event_scale;
   vector<double>  *mcevt_alphaQCD;
   vector<double>  *mcevt_alphaQED;
   vector<int>     *mcevt_pdf_id1;
   vector<int>     *mcevt_pdf_id2;
   vector<double>  *mcevt_pdf_x1;
   vector<double>  *mcevt_pdf_x2;
   vector<double>  *mcevt_pdf_scale;
   vector<double>  *mcevt_pdf1;
   vector<double>  *mcevt_pdf2;
   vector<double>  *mcevt_weight;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_isGRL;   //!
   TBranch        *b_L1_MU6;   //!
   TBranch        *b_EF_mu10;   //!
   TBranch        *b_EF_mu13;   //!
   TBranch        *b_EF_mu15;   //!
   TBranch        *b_EF_mu20;   //!
   TBranch        *b_EF_mu4;   //!
   TBranch        *b_EF_mu6;   //!
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
   TBranch        *b_vxp_n;   //!
   TBranch        *b_vxp_nTracks;   //!
   TBranch        *b_vxp_type;   //!
   TBranch        *b_vxp_z;   //!
   TBranch        *b_vxp_z_err;   //!
   TBranch        *b_mu_staco_truth_E;   //!
   TBranch        *b_mu_staco_truth_pt;   //!
   TBranch        *b_mu_staco_truth_eta;   //!
   TBranch        *b_mu_staco_truth_phi;   //!
   TBranch        *b_mu_staco_truth_type;   //!
   TBranch        *b_mu_staco_truth_mothertype;   //!
   TBranch        *b_mu_staco_truth_barcode;   //!
   TBranch        *b_mu_staco_truth_motherbarcode;   //!
   TBranch        *b_mu_staco_truth_status;   //!
   TBranch        *b_mu_staco_truth_dr;   //!
   TBranch        *b_mu_staco_truth_matched;   //!
   TBranch        *b_mu_muid_truth_E;   //!
   TBranch        *b_mu_muid_truth_pt;   //!
   TBranch        *b_mu_muid_truth_eta;   //!
   TBranch        *b_mu_muid_truth_phi;   //!
   TBranch        *b_mu_muid_truth_type;   //!
   TBranch        *b_mu_muid_truth_mothertype;   //!
   TBranch        *b_mu_muid_truth_barcode;   //!
   TBranch        *b_mu_muid_truth_motherbarcode;   //!
   TBranch        *b_mu_muid_truth_status;   //!
   TBranch        *b_mu_muid_truth_dr;   //!
   TBranch        *b_mu_muid_truth_matched;   //!
   TBranch        *b_muonTruth_n;   //!
   TBranch        *b_muonTruth_pt;   //!
   TBranch        *b_muonTruth_m;   //!
   TBranch        *b_muonTruth_eta;   //!
   TBranch        *b_muonTruth_phi;   //!
   TBranch        *b_muonTruth_charge;   //!
   TBranch        *b_muonTruth_PDGID;   //!
   TBranch        *b_muonTruth_type;   //!
   TBranch        *b_muonTruth_origin;   //!
   TBranch        *b_mcevt_n;   //!
   TBranch        *b_mcevt_signal_process_id;   //!
   TBranch        *b_mcevt_event_number;   //!
   TBranch        *b_mcevt_event_scale;   //!
   TBranch        *b_mcevt_alphaQCD;   //!
   TBranch        *b_mcevt_alphaQED;   //!
   TBranch        *b_mcevt_pdf_id1;   //!
   TBranch        *b_mcevt_pdf_id2;   //!
   TBranch        *b_mcevt_pdf_x1;   //!
   TBranch        *b_mcevt_pdf_x2;   //!
   TBranch        *b_mcevt_pdf_scale;   //!
   TBranch        *b_mcevt_pdf1;   //!
   TBranch        *b_mcevt_pdf2;   //!
   TBranch        *b_mcevt_weight;   //!

   mcOfflinePhysics(TTree *tree=0);
   virtual ~mcOfflinePhysics();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef mcOfflinePhysics_cxx
mcOfflinePhysics::mcOfflinePhysics(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("user.hod.001239._00003.mcWZphys.root");
      if (!f) {
         f = new TFile("user.hod.001239._00003.mcWZphys.root");
      }
      tree = (TTree*)gDirectory->Get("offline");

   }
   Init(tree);
}

mcOfflinePhysics::~mcOfflinePhysics()
{
   if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t mcOfflinePhysics::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mcOfflinePhysics::LoadTree(Long64_t entry)
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

void mcOfflinePhysics::Init(TTree *tree)
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
   vxp_nTracks = 0;
   vxp_type = 0;
   vxp_z = 0;
   vxp_z_err = 0;
   mu_staco_truth_E = 0;
   mu_staco_truth_pt = 0;
   mu_staco_truth_eta = 0;
   mu_staco_truth_phi = 0;
   mu_staco_truth_type = 0;
   mu_staco_truth_mothertype = 0;
   mu_staco_truth_barcode = 0;
   mu_staco_truth_motherbarcode = 0;
   mu_staco_truth_status = 0;
   mu_staco_truth_dr = 0;
   mu_staco_truth_matched = 0;
   mu_muid_truth_E = 0;
   mu_muid_truth_pt = 0;
   mu_muid_truth_eta = 0;
   mu_muid_truth_phi = 0;
   mu_muid_truth_type = 0;
   mu_muid_truth_mothertype = 0;
   mu_muid_truth_barcode = 0;
   mu_muid_truth_motherbarcode = 0;
   mu_muid_truth_status = 0;
   mu_muid_truth_dr = 0;
   mu_muid_truth_matched = 0;
   muonTruth_pt = 0;
   muonTruth_m = 0;
   muonTruth_eta = 0;
   muonTruth_phi = 0;
   muonTruth_charge = 0;
   muonTruth_PDGID = 0;
   muonTruth_type = 0;
   muonTruth_origin = 0;
   mcevt_signal_process_id = 0;
   mcevt_event_number = 0;
   mcevt_event_scale = 0;
   mcevt_alphaQCD = 0;
   mcevt_alphaQED = 0;
   mcevt_pdf_id1 = 0;
   mcevt_pdf_id2 = 0;
   mcevt_pdf_x1 = 0;
   mcevt_pdf_x2 = 0;
   mcevt_pdf_scale = 0;
   mcevt_pdf1 = 0;
   mcevt_pdf2 = 0;
   mcevt_weight = 0;
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
   fChain->SetBranchAddress("EF_mu10", &EF_mu10, &b_EF_mu10);
   fChain->SetBranchAddress("EF_mu13", &EF_mu13, &b_EF_mu13);
   fChain->SetBranchAddress("EF_mu15", &EF_mu15, &b_EF_mu15);
   fChain->SetBranchAddress("EF_mu20", &EF_mu20, &b_EF_mu20);
   fChain->SetBranchAddress("EF_mu4", &EF_mu4, &b_EF_mu4);
   fChain->SetBranchAddress("EF_mu6", &EF_mu6, &b_EF_mu6);
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
   fChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
   fChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
   fChain->SetBranchAddress("vxp_type", &vxp_type, &b_vxp_type);
   fChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
   fChain->SetBranchAddress("vxp_z_err", &vxp_z_err, &b_vxp_z_err);
   fChain->SetBranchAddress("mu_staco_truth_E", &mu_staco_truth_E, &b_mu_staco_truth_E);
   fChain->SetBranchAddress("mu_staco_truth_pt", &mu_staco_truth_pt, &b_mu_staco_truth_pt);
   fChain->SetBranchAddress("mu_staco_truth_eta", &mu_staco_truth_eta, &b_mu_staco_truth_eta);
   fChain->SetBranchAddress("mu_staco_truth_phi", &mu_staco_truth_phi, &b_mu_staco_truth_phi);
   fChain->SetBranchAddress("mu_staco_truth_type", &mu_staco_truth_type, &b_mu_staco_truth_type);
   fChain->SetBranchAddress("mu_staco_truth_mothertype", &mu_staco_truth_mothertype, &b_mu_staco_truth_mothertype);
   fChain->SetBranchAddress("mu_staco_truth_barcode", &mu_staco_truth_barcode, &b_mu_staco_truth_barcode);
   fChain->SetBranchAddress("mu_staco_truth_motherbarcode", &mu_staco_truth_motherbarcode, &b_mu_staco_truth_motherbarcode);
   fChain->SetBranchAddress("mu_staco_truth_status", &mu_staco_truth_status, &b_mu_staco_truth_status);
   fChain->SetBranchAddress("mu_staco_truth_dr", &mu_staco_truth_dr, &b_mu_staco_truth_dr);
   fChain->SetBranchAddress("mu_staco_truth_matched", &mu_staco_truth_matched, &b_mu_staco_truth_matched);
   fChain->SetBranchAddress("mu_muid_truth_E", &mu_muid_truth_E, &b_mu_muid_truth_E);
   fChain->SetBranchAddress("mu_muid_truth_pt", &mu_muid_truth_pt, &b_mu_muid_truth_pt);
   fChain->SetBranchAddress("mu_muid_truth_eta", &mu_muid_truth_eta, &b_mu_muid_truth_eta);
   fChain->SetBranchAddress("mu_muid_truth_phi", &mu_muid_truth_phi, &b_mu_muid_truth_phi);
   fChain->SetBranchAddress("mu_muid_truth_type", &mu_muid_truth_type, &b_mu_muid_truth_type);
   fChain->SetBranchAddress("mu_muid_truth_mothertype", &mu_muid_truth_mothertype, &b_mu_muid_truth_mothertype);
   fChain->SetBranchAddress("mu_muid_truth_barcode", &mu_muid_truth_barcode, &b_mu_muid_truth_barcode);
   fChain->SetBranchAddress("mu_muid_truth_motherbarcode", &mu_muid_truth_motherbarcode, &b_mu_muid_truth_motherbarcode);
   fChain->SetBranchAddress("mu_muid_truth_status", &mu_muid_truth_status, &b_mu_muid_truth_status);
   fChain->SetBranchAddress("mu_muid_truth_dr", &mu_muid_truth_dr, &b_mu_muid_truth_dr);
   fChain->SetBranchAddress("mu_muid_truth_matched", &mu_muid_truth_matched, &b_mu_muid_truth_matched);
   fChain->SetBranchAddress("muonTruth_n", &muonTruth_n, &b_muonTruth_n);
   fChain->SetBranchAddress("muonTruth_pt", &muonTruth_pt, &b_muonTruth_pt);
   fChain->SetBranchAddress("muonTruth_m", &muonTruth_m, &b_muonTruth_m);
   fChain->SetBranchAddress("muonTruth_eta", &muonTruth_eta, &b_muonTruth_eta);
   fChain->SetBranchAddress("muonTruth_phi", &muonTruth_phi, &b_muonTruth_phi);
   fChain->SetBranchAddress("muonTruth_charge", &muonTruth_charge, &b_muonTruth_charge);
   fChain->SetBranchAddress("muonTruth_PDGID", &muonTruth_PDGID, &b_muonTruth_PDGID);
   fChain->SetBranchAddress("muonTruth_type", &muonTruth_type, &b_muonTruth_type);
   fChain->SetBranchAddress("muonTruth_origin", &muonTruth_origin, &b_muonTruth_origin);
   fChain->SetBranchAddress("mcevt_n", &mcevt_n, &b_mcevt_n);
   fChain->SetBranchAddress("mcevt_signal_process_id", &mcevt_signal_process_id, &b_mcevt_signal_process_id);
   fChain->SetBranchAddress("mcevt_event_number", &mcevt_event_number, &b_mcevt_event_number);
   fChain->SetBranchAddress("mcevt_event_scale", &mcevt_event_scale, &b_mcevt_event_scale);
   fChain->SetBranchAddress("mcevt_alphaQCD", &mcevt_alphaQCD, &b_mcevt_alphaQCD);
   fChain->SetBranchAddress("mcevt_alphaQED", &mcevt_alphaQED, &b_mcevt_alphaQED);
   fChain->SetBranchAddress("mcevt_pdf_id1", &mcevt_pdf_id1, &b_mcevt_pdf_id1);
   fChain->SetBranchAddress("mcevt_pdf_id2", &mcevt_pdf_id2, &b_mcevt_pdf_id2);
   fChain->SetBranchAddress("mcevt_pdf_x1", &mcevt_pdf_x1, &b_mcevt_pdf_x1);
   fChain->SetBranchAddress("mcevt_pdf_x2", &mcevt_pdf_x2, &b_mcevt_pdf_x2);
   fChain->SetBranchAddress("mcevt_pdf_scale", &mcevt_pdf_scale, &b_mcevt_pdf_scale);
   fChain->SetBranchAddress("mcevt_pdf1", &mcevt_pdf1, &b_mcevt_pdf1);
   fChain->SetBranchAddress("mcevt_pdf2", &mcevt_pdf2, &b_mcevt_pdf2);
   fChain->SetBranchAddress("mcevt_weight", &mcevt_weight, &b_mcevt_weight);
   Notify();
}

Bool_t mcOfflinePhysics::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mcOfflinePhysics::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mcOfflinePhysics::Cut(Long64_t entry)
{
   if(false) cout << "entry = " << entry << endl;
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mcOfflinePhysics_cxx

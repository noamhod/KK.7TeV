/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OFFTREE_H
#define OFFTREE_H

class offTree
{
	public:
		// pointers
		physics* m_phys;
		mcPhysics* m_mcPhys;
		TFile*   m_treeFile;
		TTree*   m_tree;
		
		// check
		Bool_t emptyEvent;
		
		// event info branches
		int RunNumber;
		int lbn;
		int EventNumber;
		string period;
		vector<string>* triggers;
		int isGRL;
		
		
		// L1 triggers
		int L1_MU0;
		int L1_MU10;
		int L1_MU15;
		int L1_MU20;
		int L1_MU6;
		
		// EF triggers
		int EF_mu10;
		int EF_mu10_MG;
		int EF_mu10_MSonly;
		int EF_mu10_MSonly_tight;
		int EF_mu10_NoAlg;
		int EF_mu10_tight;
		int EF_mu10i_loose;
		int EF_mu13;
		int EF_mu13_MG;
		int EF_mu13_MG_tight;
		int EF_mu13_tight;
		int EF_mu15;
		int EF_mu15_NoAlg;
		int EF_mu20;
		int EF_mu20_MSonly;
		int EF_mu20_NoAlg;
		int EF_mu20_slow;
		int EF_mu30_MSonly;
		int EF_mu4;
		int EF_mu40_MSonly;
		
		
		// mu_staco
		Int_t          mu_staco_n;
		vector<float>* mu_staco_px;
		vector<float>* mu_staco_py;
		vector<float>* mu_staco_pz;
		vector<float>* mu_staco_E;
		vector<float>* mu_staco_m;
		vector<float>* mu_staco_charge;
		vector<float>* mu_staco_pt;
		vector<float>* mu_staco_ptcone20;
		vector<float>* mu_staco_ptcone30;
		vector<float>* mu_staco_ptcone40;
		vector<float>* mu_staco_eta;
		vector<float>* mu_staco_phi;
		vector<float>* mu_staco_d0_exPV;
		vector<float>* mu_staco_z0_exPV;
		vector<float>* mu_staco_me_qoverp;
		vector<float>* mu_staco_id_qoverp;
		vector<float>* mu_staco_me_theta;
		vector<float>* mu_staco_id_theta;
		vector<int>*   mu_staco_isCombinedMuon;
		vector<int>*   mu_staco_nSCTHits;
		vector<int>*   mu_staco_nPixHits;
		vector<int>*   mu_staco_nMDTBIHits;
		vector<int>*   mu_staco_nMDTBMHits;
		vector<int>*   mu_staco_nMDTBOHits;
		vector<int>*   mu_staco_nMDTBEEHits;
		vector<int>*   mu_staco_nMDTBIS78Hits;
		vector<int>*   mu_staco_nMDTEIHits;
		vector<int>*   mu_staco_nMDTEMHits;
		vector<int>*   mu_staco_nMDTEOHits;
		vector<int>*   mu_staco_nMDTEEHits;
		vector<int>*   mu_staco_nRPCLayer1EtaHits;
		vector<int>*   mu_staco_nRPCLayer2EtaHits;
		vector<int>*   mu_staco_nRPCLayer3EtaHits;
		vector<int>*   mu_staco_nRPCLayer1PhiHits;
		vector<int>*   mu_staco_nRPCLayer2PhiHits;
		vector<int>*   mu_staco_nRPCLayer3PhiHits;
		vector<int>*   mu_staco_nTGCLayer1EtaHits;
		vector<int>*   mu_staco_nTGCLayer2EtaHits;
		vector<int>*   mu_staco_nTGCLayer3EtaHits;
		vector<int>*   mu_staco_nTGCLayer4EtaHits;
		vector<int>*   mu_staco_nTGCLayer1PhiHits;
		vector<int>*   mu_staco_nTGCLayer2PhiHits;
		vector<int>*   mu_staco_nTGCLayer3PhiHits;
		vector<int>*   mu_staco_nTGCLayer4PhiHits;
		vector<unsigned short>* mu_staco_allauthor;
		vector<int>*   mu_staco_author;
		vector<float>* mu_staco_matchchi2;
		vector<int>*   mu_staco_matchndof;
		
		
		// muid
		Int_t          mu_muid_n;
		vector<float>* mu_muid_px;
		vector<float>* mu_muid_py;
		vector<float>* mu_muid_pz;
		vector<float>* mu_muid_E;
		vector<float>* mu_muid_m;
		vector<float>* mu_muid_charge;
		vector<float>* mu_muid_pt;
		vector<float>* mu_muid_ptcone20;
		vector<float>* mu_muid_ptcone30;
		vector<float>* mu_muid_ptcone40;
		vector<float>* mu_muid_eta;
		vector<float>* mu_muid_phi;
		vector<float>* mu_muid_d0_exPV;
		vector<float>* mu_muid_z0_exPV;
		vector<float>* mu_muid_me_qoverp;
		vector<float>* mu_muid_id_qoverp;
		vector<float>* mu_muid_me_theta;
		vector<float>* mu_muid_id_theta;
		vector<int>*   mu_muid_isCombinedMuon;
		vector<int>*   mu_muid_nSCTHits;
		vector<int>*   mu_muid_nPixHits;
		vector<int>*   mu_muid_nMDTBIHits;
		vector<int>*   mu_muid_nMDTBMHits;
		vector<int>*   mu_muid_nMDTBOHits;
		vector<int>*   mu_muid_nMDTBEEHits;
		vector<int>*   mu_muid_nMDTBIS78Hits;
		vector<int>*   mu_muid_nMDTEIHits;
		vector<int>*   mu_muid_nMDTEMHits;
		vector<int>*   mu_muid_nMDTEOHits;
		vector<int>*   mu_muid_nMDTEEHits;
		vector<int>*   mu_muid_nRPCLayer1EtaHits;
		vector<int>*   mu_muid_nRPCLayer2EtaHits;
		vector<int>*   mu_muid_nRPCLayer3EtaHits;
		vector<int>*   mu_muid_nRPCLayer1PhiHits;
		vector<int>*   mu_muid_nRPCLayer2PhiHits;
		vector<int>*   mu_muid_nRPCLayer3PhiHits;
		vector<int>*   mu_muid_nTGCLayer1EtaHits;
		vector<int>*   mu_muid_nTGCLayer2EtaHits;
		vector<int>*   mu_muid_nTGCLayer3EtaHits;
		vector<int>*   mu_muid_nTGCLayer4EtaHits;
		vector<int>*   mu_muid_nTGCLayer1PhiHits;
		vector<int>*   mu_muid_nTGCLayer2PhiHits;
		vector<int>*   mu_muid_nTGCLayer3PhiHits;
		vector<int>*   mu_muid_nTGCLayer4PhiHits;
		vector<unsigned short>* mu_muid_allauthor;
		vector<int>*   mu_muid_author;
		vector<float>* mu_muid_matchchi2;
		vector<int>*   mu_muid_matchndof;
		
		// vertex variables
		Int_t          vxp_n;
		vector<float>* vxp_z;
		vector<float>* vxp_z_err;
		vector<int>*   vxp_nTracks;
		vector<int>*   vxp_type;
	
	public:
		offTree();
		offTree(physics* phys, mcPhysics* mcPhys, TFile* treeFile);
		~offTree();
		
		TTree* getTree();
		void setBranches();
		void fill(int isGrl, string sPeriod, vector<string>* vsTriggers);
		void reset();
		void write();

	private:

};
#endif


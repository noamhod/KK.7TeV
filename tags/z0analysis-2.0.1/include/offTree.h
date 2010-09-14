/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OFFTREE_H
#define OFFTREE_H

class offTree : public utilities
{
	public:
		// pointers
		physics* m_phys;
		TFile*   m_treeFile;
		TTree*   m_tree;
		
		// check
		Bool_t emptyEvent;
		
		// event info branches
		int RunNumber;
		int lbn;
		int EventNumber;
		
		// event preselection
		int isGRL;
		int L1_MU6;
		
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
		vector<float>* mu_staco_d0_exPV;
		vector<float>* mu_staco_z0_exPV;
		vector<float>* mu_staco_me_qoverp;
		vector<float>* mu_staco_id_qoverp;
		vector<float>* mu_staco_me_theta;
		vector<float>* mu_staco_id_theta;
		vector<int>*   mu_staco_isCombinedMuon;
		vector<int>*   mu_staco_nSCTHits;
		vector<int>*   mu_staco_nPixHits;
		
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
		vector<float>* mu_muid_d0_exPV;
		vector<float>* mu_muid_z0_exPV;
		vector<float>* mu_muid_me_qoverp;
		vector<float>* mu_muid_id_qoverp;
		vector<float>* mu_muid_me_theta;
		vector<float>* mu_muid_id_theta;
		vector<int>*   mu_muid_isCombinedMuon;
		vector<int>*   mu_muid_nSCTHits;
		vector<int>*   mu_muid_nPixHits;
		
		// vertex variables
		Int_t          vxp_n;
		vector<float>* vxp_z;
		vector<float>* vxp_z_err;
		vector<int>*   vxp_nTracks;
		vector<int>*   vxp_type;
	
	public:
		offTree();
		offTree(physics* phys, TFile* treeFile);
		~offTree();
		
		void setBranches();
		void fill();
		void fill(int isGrl);
		void reset();
		void write();

	private:

};
#endif


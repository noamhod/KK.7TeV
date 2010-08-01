/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OFFLINEANALYSIS_H
#define OFFLINEANALYSIS_H

class offlineTree
{
	public:
		// pointers to classes
		physics*        m_phys;
		TFile*		m_treeFile;
		TTree*		m_tree;

		// evemnt level branches
		int    i_runnumber;
                int    i_lumiblock;
		Bool_t b_isgrl;
		Bool_t b_l1mu6;

		// muon_staco branches
		int n_mustaco;
		vector<float>* mustaco_E;
                vector<float>* mustaco_px;
                vector<float>* mustaco_py;
                vector<float>* mustaco_pz;
                vector<float>* mustaco_m;
                vector<float>* mustaco_c;
                vector<float>* mustaco_pT;
                vector<float>* mustaco_eta;
                vector<float>* mustaco_theta;
                vector<float>* mustaco_phi;
                vector<float>* mustaco_d0exPV;
                vector<float>* mustaco_z0exPV;
                vector<float>* mustaco_qop;
                vector<unsigned short>* mustaco_allauthor;
                vector<int>*            mustaco_author;
		/*
		vector<float>   *mu_staco_matchchi2;
		vector<int>     *mu_staco_matchndof;
		vector<float>   *mu_staco_etcone20;
		vector<float>   *mu_staco_etcone30;
		vector<float>   *mu_staco_etcone40;
		vector<float>   *mu_staco_nucone20;
		vector<float>   *mu_staco_nucone30;
		vector<float>   *mu_staco_nucone40;
		vector<float>   *mu_staco_ptcone20;
		vector<float>   *mu_staco_ptcone30;
		vector<float>   *mu_staco_ptcone40;
		vector<float>   *mu_staco_energyLossPar;
		vector<float>   *mu_staco_energyLossErr;
		vector<int>     *mu_staco_bestMatch;
		vector<int>     *mu_staco_isStandAloneMuon;
		vector<int>     *mu_staco_isCombinedMuon;
		vector<int>     *mu_staco_isLowPtReconstructedMuon;
		vector<float>   *mu_staco_d0_exPV;
		vector<float>   *mu_staco_z0_exPV;
		vector<float>   *mu_staco_phi_exPV;
		vector<float>   *mu_staco_theta_exPV;
		vector<float>   *mu_staco_qoverp_exPV;
		*/

	public:
		offlineTree();
		offlineTree(physics* phys, TFile* treeFile);
		~offlineTree();

		void setBranches();

		void fill(Bool_t isgrl);
		void write();

	private:

};
#endif


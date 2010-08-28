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
		Bool_t m_emptyEvent;
		
		// event info branches
		int m_RunNumber;
		int m_lbn;
		int m_EventNumber;
		
		// event preselection
		int m_isGRL;
		int m_L1_MU6;
		
		// dimuon kinematics variables
		double m_imass;
		double m_cosTheta;
		
		// mua and mub
		double m_mua_m;
		double m_mub_m;
		double m_mua_charge;
		double m_mub_charge;
		double m_mua_pT;
		double m_mub_pT;
		double m_mua_pTcone20;
		double m_mub_pTcone20;
		double m_mua_pTcone30;
		double m_mub_pTcone30;
		double m_mua_pTcone40;
		double m_mub_pTcone40;
		double m_mua_eta;
		double m_mub_eta;
		double m_mua_d0_exPV;
		double m_mub_d0_exPV;
		double m_mua_z0_exPV;
		double m_mub_z0_exPV;
		double m_mua_me_qOp;
		double m_mub_me_qOp;
		double m_mua_id_qOp;
		double m_mub_id_qOp;
		double m_mua_me_theta;
		double m_mub_me_theta;
		double m_mua_id_theta;
		double m_mub_id_theta;
		double m_mua_isCombMu;
		double m_mub_isCombMu;
		double m_mua_nSCThits;
		double m_mub_nSCThits;
		double m_mua_nPIXhits;
		double m_mub_nPIXhits;
		double m_mua_nIDhits;
		double m_mub_nIDhits;
		
		TLorentzVector m_mua_p4Vec;
		TLorentzVector m_mub_p4Vec;
		
		// vertex variables
		double m_vxp_z;
		double m_vxp_z_err;
		double m_vxp_nTracks;
		double m_vxp_type;
	
	public:
		offTree();
		offTree(physics* phys, TFile* treeFile);
		~offTree();
		
		void setBranches();
		void fill();
		void fill(int isGRL, TMapsd& kinVars, int ia, int ib, int iVtx);
		void reset();
		void write();

	private:

};
#endif


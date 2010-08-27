/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "basicIncludes.h"

#ifndef OFFLINETREEDIGEST_H
#define OFFLINETREEDIGEST_H

class offlineTreeDigest : public utilities
{
	public:
		// pointers
		offlinePhysics*  m_offPhys;
		TFile*           m_treeFile;
		TTree*	         m_tree;
		
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
		
		// muPlus and muMinus
		double m_muPlus_m;
		double m_muMinus_m;
		double m_muPlus_charge;
		double m_muMinus_charge;
		double m_muPlus_pT;
		double m_muMinus_pT;
		double m_muPlus_pTcone20;
		double m_muMinus_pTcone20;
		double m_muPlus_pTcone30;
		double m_muMinus_pTcone30;
		double m_muPlus_pTcone40;
		double m_muMinus_pTcone40;
		double m_muPlus_eta;
		double m_muMinus_eta;
		double m_muPlus_d0_exPV;
		double m_muMinus_d0_exPV;
		double m_muPlus_z0_exPV;
		double m_muMinus_z0_exPV;
		double m_muPlus_me_qOp;
		double m_muMinus_me_qOp;
		double m_muPlus_id_qOp;
		double m_muMinus_id_qOp;
		double m_muPlus_me_theta;
		double m_muMinus_me_theta;
		double m_muPlus_id_theta;
		double m_muMinus_id_theta;
		double m_muPlus_isCombMu;
		double m_muMinus_isCombMu;
		double m_muPlus_nSCThits;
		double m_muMinus_nSCThits;
		double m_muPlus_nPIXhits;
		double m_muMinus_nPIXhits;
		double m_muPlus_nIDhits;
		double m_muMinus_nIDhits;
		
		TLorentzVector m_muPlus_p4Vec;
		TLorentzVector m_muMinus_p4Vec;
		
		// vertex variables
		double m_vxp_z;
		double m_vxp_z_err;
		double m_vxp_nTracks;
		double m_vxp_type;
	
	public:
		offlineTreeDigest();
		offlineTreeDigest(offlinePhysics* offPhys, TFile* treeFile);
		~offlineTreeDigest();
		
		void setBranches();
		void fill();
		void fill(TMapsd& kinVars, int iMup, int iMum, int iVtx);
		void reset();
		void write();

	private:

};
#endif


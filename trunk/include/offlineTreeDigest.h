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
		TFile*    m_treeFile;
		TTree*	  m_tree;
		
		// branches
		int m_RunNumber;
		int m_lbn;
		int m_EventNumber;
		
		double m_imass;
		double m_mu_pT;
		double m_mu_eta;
		double m_mu_cosTheta;
		
		Bool_t b_null;
		Bool_t b_GRL;
		Bool_t b_L1_MU6;
		Bool_t b_z0;
		Bool_t b_d0;
		Bool_t b_cosmicCut;
		Bool_t b_imass;
		Bool_t b_pT;
		Bool_t b_eta;
	
	public:
		offlineTreeDigest();
		offlineTreeDigest(offlinePhysics*  offPhys, TFile* treeFile);
		~offlineTreeDigest();
		
		void setBranches(TMapds* cutFlowOrdered);
		void fill();
		void fill(TMapsb& cutFlowDecision, TMapsd& kinematicVariables);
		void reset();
		void write();

	private:

};
#endif


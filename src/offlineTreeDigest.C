/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineTreeDigest.h"

offlineTreeDigest::offlineTreeDigest()
{

}

offlineTreeDigest::~offlineTreeDigest()
{

}

offlineTreeDigest::offlineTreeDigest(offlinePhysics* offPhys, TFile* treeFile)
{
	m_offPhys = offPhys;

	m_treeFile = treeFile;

	m_treeFile->cd();

	m_tree = new TTree("digest", "digest");

	//m_tree->SetMaxTreeSize(50000000); // 50Mb per file
}

void offlineTreeDigest::setBranches(TMapds* cutFlowOrdered)
{	
	// run variables branches
	m_tree->Branch( "run_RunNumber", &m_RunNumber );
	m_tree->Branch( "run_lbn", &m_lbn );
	m_tree->Branch( "run_EventNumber", &m_EventNumber );
	
	// kinematic variables branches
	m_tree->Branch( "kin_imass", &m_imass );
	m_tree->Branch( "kin_pT_mu",  &m_mu_pT );
	m_tree->Branch( "kin_eta_mu", &m_mu_eta );
	m_tree->Branch( "kin_cosTheta_mu",  &m_mu_cosTheta );
	
	// set cut flow branches
	/*
	for(TMapds::iterator it=cutFlowOrdered->begin() ; it!=cutFlowOrdered->end() ; ++it)
	{
		//double snumber = it->first;
		string sname = it->second;
		
		if(sname=="null")      m_tree->Branch( ("is_" + sname).c_str(), &b_null );
		if(sname=="GRL")       m_tree->Branch( ("is_" + sname).c_str(), &b_GRL );
		if(sname=="L1_MU6")    m_tree->Branch( ("is_" + sname).c_str(), &b_L1_MU6 );
		if(sname=="z0")        m_tree->Branch( ("is_" + sname).c_str(), &b_z0 );
		if(sname=="d0")        m_tree->Branch( ("is_" + sname).c_str(), &b_d0 );
		if(sname=="cosmicCut") m_tree->Branch( ("is_" + sname).c_str(), &b_cosmicCut );
		if(sname=="imass")     m_tree->Branch( ("is_" + sname).c_str(), &b_imass );
		if(sname=="pT")        m_tree->Branch( ("is_" + sname).c_str(), &b_pT );
		if(sname=="eta")       m_tree->Branch( ("is_" + sname).c_str(), &b_eta );
	}
	*/
	m_tree->Branch( "is_null", &b_null );
	m_tree->Branch( "is_GRL", &b_GRL );
	m_tree->Branch( "is_L1_MU6", &b_L1_MU6 );
	m_tree->Branch( "is_z0", &b_z0 );
	m_tree->Branch( "is_d0", &b_d0 );
	m_tree->Branch( "is_cosmicCut", &b_cosmicCut );
	m_tree->Branch( "is_imass", &b_imass );
	m_tree->Branch( "is_pT", &b_pT );
	m_tree->Branch( "is_eta", &b_eta );
}

void offlineTreeDigest::fill()
{
	/*---------------------------*/
	/*---*/ m_tree->Fill(); /*---*/
	/*---------------------------*/
}

void offlineTreeDigest::fill(TMapsb& cutFlowDecision, TMapsd& kinematicVariables)
{
	// fill run branches
	m_RunNumber   = m_offPhys->RunNumber;
	m_lbn         = m_offPhys->lbn;
	m_EventNumber = m_offPhys->EventNumber;

	// fill kin branches
	for(TMapsd::iterator it=kinematicVariables.begin() ; it!=kinematicVariables.end() ; ++it)
	{
		string sname = it->first;
		double dval  = it->second;
		
		if(sname=="imass")    m_imass       = dval;
		if(sname=="pT")       m_mu_pT       = dval;
		if(sname=="eta")      m_mu_eta      = dval;
		if(sname=="cosTheta") m_mu_cosTheta = dval;
	}

	// fill cutFlow branches
	for(TMapsb::iterator it=cutFlowDecision.begin() ; it!=cutFlowDecision.end() ; ++it)
	{
		string sname = it->first;
		Bool_t bval  = (Bool_t)it->second;
		
		if(sname=="null")      b_null      = bval;
		if(sname=="GRL")       b_GRL       = bval;
		if(sname=="L1_MU6")    b_L1_MU6    = bval;
		if(sname=="z0")        b_z0        = bval;
		if(sname=="d0")        b_d0        = bval;
		if(sname=="cosmicCut") b_cosmicCut = bval;
		if(sname=="imass")     b_imass     = bval;
		if(sname=="pT")        b_pT        = bval;
		if(sname=="eta")       b_eta       = bval;
	}
	
	/*---------------------------*/
	/*---*/ m_tree->Fill(); /*---*/
	/*---------------------------*/
}

void offlineTreeDigest::reset()
{
	// run
	m_RunNumber   = -999;
	m_lbn         = -999;
	m_EventNumber = -999;

	// kin
	m_imass       = -999;
	m_mu_pT       = -999;
	m_mu_eta      = -999;
	m_mu_cosTheta = -999;

	// cutFlow
	b_null      = false;
	b_GRL       = false;
	b_L1_MU6    = false;
	b_z0        = false;
	b_d0        = false;
	b_cosmicCut = false;
	b_imass     = false;
	b_pT        = false;
	b_eta       = false;
}

void offlineTreeDigest::write()
{
	m_treeFile->cd();
	m_tree->Write();
}



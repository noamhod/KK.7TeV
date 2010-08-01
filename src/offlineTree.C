/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineTree.h"

offlineTree::offlineTree()
{

}

offlineTree::~offlineTree()
{

}

offlineTree::offlineTree(physics* phys, TFile* treeFile)
{
	m_phys = phys;

	m_treeFile = treeFile;

	m_treeFile->cd();

	m_tree = new TTree("offline", "offline");

	setBranches();
}

void offlineTree::setBranches()
{
	// event level
	m_tree->Branch( "runnumber", &i_runnumber );
        m_tree->Branch( "lumiblock", &i_lumiblock );
        m_tree->Branch( "GRL", &b_isgrl );
        m_tree->Branch( "L1_MU6", &b_l1mu6 );

	// muon_staco
	mustaco_E     = new vector<float>;
	mustaco_px    = new vector<float>;
	mustaco_py    = new vector<float>;
	mustaco_pz    = new vector<float>;
	mustaco_m     = new vector<float>;
	mustaco_c     = new vector<float>;
	mustaco_pT    = new vector<float>;
	mustaco_eta   = new vector<float>;
	mustaco_theta = new vector<float>;
	mustaco_phi   = new vector<float>;
	mustaco_d0exPV= new vector<float>;
	mustaco_z0exPV= new vector<float>;
	mustaco_qop   = new vector<float>;
	mustaco_allauthor = new vector<unsigned short>;
	mustaco_author    = new vector<int>;
	m_tree->Branch( "mustaco_E", &mustaco_E );
	m_tree->Branch( "mustaco_px", &mustaco_px );
	m_tree->Branch( "mustaco_py", &mustaco_py );
	m_tree->Branch( "mustaco_pz", &mustaco_pz );
	m_tree->Branch( "mustaco_m", &mustaco_m );
	m_tree->Branch( "mustaco_c", &mustaco_c );
	m_tree->Branch( "mustaco_pT", &mustaco_pT );
	m_tree->Branch( "mustaco_eta", &mustaco_eta );
	m_tree->Branch( "mustaco_theta", &mustaco_theta );
	m_tree->Branch( "mustaco_phi", &mustaco_phi );
	m_tree->Branch( "mustaco_d0exPV", &mustaco_d0exPV );
	m_tree->Branch( "mustaco_z0exPV", &mustaco_z0exPV );
	m_tree->Branch( "mustaco_qop", &mustaco_qop );
	m_tree->Branch( "mustaco_allauthor", &mustaco_allauthor );
	m_tree->Branch( "mustaco_author", &mustaco_author );

}

void offlineTree::fill(Bool_t isgrl)
{
	// external
	b_isgrl     = isgrl;

	// event level
	i_runnumber = m_phys->RunNumber;
	i_lumiblock = m_phys->lbn;
	b_l1mu6     = m_phys->L1_MU6;
	
	// muon staco
	n_mustaco      = m_phys->mu_staco_n;
	mustaco_E      = m_phys->mu_staco_E;
        mustaco_px     = m_phys->mu_staco_px;
        mustaco_py     = m_phys->mu_staco_py;
        mustaco_pz     = m_phys->mu_staco_pz;
        mustaco_m      = m_phys->mu_staco_m;
        mustaco_c      = m_phys->mu_staco_charge;
        mustaco_pT     = m_phys->mu_staco_pt;
        mustaco_eta    = m_phys->mu_staco_eta;
        mustaco_theta  = m_phys->mu_staco_theta_exPV;
        mustaco_phi    = m_phys->mu_staco_phi;
        mustaco_d0exPV = m_phys->mu_staco_d0_exPV;
        mustaco_z0exPV = m_phys->mu_staco_z0_exPV;
        mustaco_qop    = m_phys->mu_staco_qoverp_exPV;
        mustaco_allauthor = m_phys->mu_staco_allauthor;
        mustaco_author    = m_phys->mu_staco_author;	

	/*---------------------------*/
	/*---*/ m_tree->Fill(); /*---*/
	/*---------------------------*/
}

void offlineTree::write()
{
	m_treeFile->cd();
	m_tree->Write();
}

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

	//m_tree = new TTree("offline", "offline");
	m_tree = phys->fChain->CloneTree();
	m_tree->SetName("offline");
	
	m_tree->SetMaxTreeSize(1000000000); // 50Mb per file
	
	setBranches();
}

void offlineTree::setBranches()
{
	// event level
	b_isGRL = m_tree->Branch("isGRL", &isGRL, "isGRL/B");
}

void offlineTree::fill(Bool_t isgrl)
{
	// external branches:
	isGRL = isgrl;
	b_isGRL->Fill();
}

void offlineTree::write()
{
	m_treeFile->cd();
	m_tree->Write("", TObject::kOverwrite);
	//m_tree->Write();
}

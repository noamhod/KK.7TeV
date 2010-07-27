/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef muon_staco_tree_cxx
#include "muon_staco_tree.h"

muon_staco_tree::muon_staco_tree() {}

muon_staco_tree::muon_staco_tree(muon_staco* mustaco, TDirectory* dir)
{
	m_mustaco = mustaco;

	setTree("muon_staco", dir);
}

muon_staco_tree::~muon_staco_tree() {}

void muon_staco_tree::setMoreBranches()
{
	// do something
}

void muon_staco_tree::fillVectors()
{
	vd_E->push_back(m_mustaco->prtE);
	vd_Px->push_back(m_mustaco->prtPx);
	vd_Py->push_back(m_mustaco->prtPy);
	vd_Pz->push_back(m_mustaco->prtPz);
	vd_M->push_back(m_mustaco->prtM);
	vd_Ch->push_back(m_mustaco->prtCh);
	vd_Pt->push_back(m_mustaco->prtPt);
	vd_Eta->push_back(m_mustaco->prtEta);
	vd_Theta->push_back(m_mustaco->prtTheta);
	vd_Phi->push_back(m_mustaco->prtPhi);
	vd_D0->push_back(m_mustaco->prtD0);
	vd_Z0->push_back(m_mustaco->prtZ0);
	vd_QOP->push_back(m_mustaco->prtQOP);
	vus_Allauthor->push_back(m_mustaco->prtAllauthor);
	vi_Author->push_back(m_mustaco->prtAuthor);
}

#endif


/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef muon_muid_cxx
#include "muon_muid.h"

muon_muid::muon_muid() {}

muon_muid::muon_muid(physics* phys)
{
	physPtr = phys;
	//physPtr->fChain->SetBranchStatus("mu_muid_*", 1);
}

muon_muid::~muon_muid() {}

int muon_muid::getNParticles()
{
	return (int)physPtr->mu_muid_n;
}

void muon_muid::setParticle(int index)
{
	//----- can change these lines -----
	//      only the container name
	//      should be changed
	if(index<0 || index>=physPtr->mu_muid_n) { cerr << "ERROR: index=" << index << " is out of range" << endl; exit(-1); }

	prtE      = (double)physPtr->mu_muid_E->at(index);
	prtPx     = (double)physPtr->mu_muid_px->at(index);
	prtPy     = (double)physPtr->mu_muid_py->at(index);
	prtPz     = (double)physPtr->mu_muid_pz->at(index);
	prtM      = (double)physPtr->mu_muid_m->at(index);
	prtCh     = (double)physPtr->mu_muid_charge->at(index);
	prtPt     = (double)physPtr->mu_muid_pt->at(index);
	prtEta    = (double)physPtr->mu_muid_eta->at(index);
	prtPhi    = (double)physPtr->mu_muid_phi->at(index);
	prtD0     = (double)physPtr->mu_muid_d0_exPV->at(index);
	prtZ0     = (double)physPtr->mu_muid_z0_exPV->at(index);
	prtQOP    = (double)physPtr->mu_muid_qoverp_exPV->at(index);
	prtTheta  = (double)physPtr->mu_muid_theta_exPV->at(index);
	prtAllauthor = physPtr->mu_muid_allauthor->at(index);
	prtAuthor    = physPtr->mu_muid_author->at(index);
	//-------------------------------------

	//----- do not change these lines -----
	setPvec(); //--------------------------
	setQvec(); //--------------------------
	setVertex(); //------------------------
	//-------------------------------------
}

void muon_muid::setMore(int index)
{
	// user input goes here
	// ...
	
	// stupid, just to use these variables
	// so there are no compilation warnings
	index = 0;
}

#endif


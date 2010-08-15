/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#ifdef muon_staco_cxx
#include "muon_staco.h"

muon_staco::muon_staco() {}

muon_staco::muon_staco(physics* phys)
{
	physPtr = phys;
	physPtr->fChain->SetBranchStatus("mu_staco_*", 1);
}

muon_staco::~muon_staco() {}

int muon_staco::getNParticles()
{
	return (int)physPtr->mu_staco_n;
}

void muon_staco::setParticle(int index)
{
	//----- can change these lines -----
	//      only the container name
	//      should be changed
	if(index<0 || index>physPtr->mu_staco_n) { cerr << "ERROR: index=" << index << " is out of range" << endl; exit(-1); }

	prtE      = (double)physPtr->mu_staco_E->at(index);
	prtPx     = (double)physPtr->mu_staco_px->at(index);
	prtPy     = (double)physPtr->mu_staco_py->at(index);
	prtPz     = (double)physPtr->mu_staco_pz->at(index);
	prtM      = (double)physPtr->mu_staco_m->at(index);
	prtCh     = (double)physPtr->mu_staco_charge->at(index);
	prtPt     = (double)physPtr->mu_staco_pt->at(index);
	prtEta    = (double)physPtr->mu_staco_eta->at(index);
	prtPhi    = (double)physPtr->mu_staco_phi->at(index);
	prtD0     = (double)physPtr->mu_staco_d0_exPV->at(index);
	prtZ0     = (double)physPtr->mu_staco_z0_exPV->at(index);
	prtQOP    = (double)physPtr->mu_staco_qoverp_exPV->at(index);
	prtTheta  = (double)physPtr->mu_staco_theta_exPV->at(index);
	prtAllauthor = physPtr->mu_staco_allauthor->at(index);
	prtAuthor    = physPtr->mu_staco_author->at(index);
	//-------------------------------------

	//----- do not change these lines -----
	setPvec(); //--------------------------
	setQvec(); //--------------------------
	setVertex(); //------------------------
	//-------------------------------------
}

void muon_staco::setMore(int index)
{
	// user input goes here
	// ...
	
	// stupid, just to use these variables
	// so there are no compilation warnings
	index = 0;
}

#endif


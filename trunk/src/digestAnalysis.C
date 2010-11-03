/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "digestAnalysis.h"

digestAnalysis::digestAnalysis()
{

}

digestAnalysis::~digestAnalysis()
{

}

void digestAnalysis::executeAdvanced()
{

/*
	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_digestPhys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mustaco->getNParticles() ; n++)
		{
			m_mustaco->setParticle(n);
			m_graphicobjs->h2_xyVertex->Fill( m_mustaco->pvVec->X(), m_mustaco->pvVec->Y() );
		}
	}
*/
}

void digestAnalysis::executeCutFlow()
{
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// start allocating the variables for the preselection

	// event level (for preselection)
	analysisSkeleton::runnumber   = m_digestPhys->RunNumber;
	analysisSkeleton::lumiblock   = m_digestPhys->lbn;
	analysisSkeleton::eventnumber = m_digestPhys->EventNumber;
	analysisSkeleton::isGRL       = m_digestPhys->isGRL;
	analysisSkeleton::sPeriod     = m_digestPhys->period;
	
	
	analysisSkeleton::isL1_MU6    = m_digestPhys->L1_MU6;
	analysisSkeleton::isEF_mu13   = m_digestPhys->EF_mu13;
	
	// muon (for the setMUindeces call)
	analysisSkeleton::mu_staco_charge = m_digestPhys->mu_staco_charge;
	
	// muon  (for hipTmuon preselection)
	analysisSkeleton::mu_staco_n         = m_digestPhys->mu_staco_n;
	analysisSkeleton::mu_staco_pt        = m_digestPhys->mu_staco_pt;
	analysisSkeleton::mu_staco_me_qoverp = m_digestPhys->mu_staco_me_qoverp;
	analysisSkeleton::mu_staco_me_theta  = m_digestPhys->mu_staco_me_theta;
	
	// vertexes (for the PV preselection)
	analysisSkeleton::vxp_n       = m_digestPhys->vxp_n;
	analysisSkeleton::vxp_nTracks = m_digestPhys->vxp_nTracks;
	analysisSkeleton::vxp_type    = m_digestPhys->vxp_type;
	analysisSkeleton::vxp_z       = m_digestPhys->vxp_z;
	

	///////////////////////////////////////////////////////////////
	// preform the entire preselection and counting job ///////////
	bool passPreselection = applyPreselection("digest"); //////////
	if( !passPreselection ) return; ///////////////////////////////
	///////////////////////////////////////////////////////////////
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// start allocating the variables for TLorentzVector and indices settings
	
	//////////////////////////////////////////////////////////////////////
	// build vector of the muons TLorentzVector //////////////////////////
    // this needs to be looped acording to the size of the vector rather
	// than according to the value of mu_staco_n since in the digest tree
	// only the successive COUPLE is written.
	TVectorP2VL	pmu;
	for(int n=0 ; n<(int)m_digestPhys->mu_staco_m->size() ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_digestPhys->mu_staco_px->at(n)*MeV2TeV );
		pmu[n]->SetPy( m_digestPhys->mu_staco_py->at(n)*MeV2TeV );
		pmu[n]->SetPz( m_digestPhys->mu_staco_pz->at(n)*MeV2TeV );
		pmu[n]->SetE(  m_digestPhys->mu_staco_E->at(n)*MeV2TeV );
	}
	///////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////
	// set the ai and bi muon indices /////////////////////////////////
	bool is2validIndices = setMUindices(pmu, "digest"); ///////////////
	if(!is2validIndices) return; //////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// start allocating the variables for the selection
	
	// calculate the necessary variables
	analysisSkeleton::current_imass    = imass(pmu[ai],pmu[bi]);
	analysisSkeleton::current_cosTheta = cosThetaCollinsSoper( pmu[ai], (double)m_digestPhys->mu_staco_charge->at(ai),
											 pmu[bi], (double)m_digestPhys->mu_staco_charge->at(bi) );
	analysisSkeleton::current_mu_pT       = (m_digestPhys->mu_staco_charge->at(ai)<0) ? m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV : m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	analysisSkeleton::current_muplus_pT   = (m_digestPhys->mu_staco_charge->at(ai)>0) ? m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV : m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	analysisSkeleton::current_mu_eta      = (m_digestPhys->mu_staco_charge->at(ai)<0) ? m_digestPhys->mu_staco_eta->at(ai) : m_digestPhys->mu_staco_eta->at(bi);
	analysisSkeleton::current_muplus_eta  = (m_digestPhys->mu_staco_charge->at(ai)>0) ? m_digestPhys->mu_staco_eta->at(ai) : m_digestPhys->mu_staco_eta->at(bi);
	analysisSkeleton::current_cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );
	analysisSkeleton::current_ipTdiff     = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	analysisSkeleton::current_etaSum      = current_muplus_eta + current_mu_eta;
	
	// deprecated !!!
	analysisSkeleton::d0exPVa = m_digestPhys->mu_staco_d0_exPV->at(ai);
	analysisSkeleton::z0exPVa = m_digestPhys->mu_staco_z0_exPV->at(ai);
	analysisSkeleton::d0exPVb = m_digestPhys->mu_staco_d0_exPV->at(bi);
	analysisSkeleton::z0exPVb = m_digestPhys->mu_staco_z0_exPV->at(bi);
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	analysisSkeleton::nPVtracksPtr = m_digestPhys->vxp_nTracks; // number of tracks > 2
	analysisSkeleton::nPVtypePtr   = m_digestPhys->vxp_type;    // ==1
	analysisSkeleton::PVz0Ptr      = m_digestPhys->vxp_z;       // = absolute z position of primary vertex < 150mm
	analysisSkeleton::PVz0errPtr   = m_digestPhys->vxp_z_err;   // = error
	
	// combined muon ?
	analysisSkeleton::isMuaComb  = m_digestPhys->mu_staco_isCombinedMuon->at(ai);
	analysisSkeleton::isMubComb  = m_digestPhys->mu_staco_isCombinedMuon->at(bi);	
	
	// inner detector hits
	analysisSkeleton::nSCThitsMua  = m_digestPhys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
	analysisSkeleton::nSCThitsMub  = m_digestPhys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
	analysisSkeleton::nPIXhitsMua  = m_digestPhys->mu_staco_nPixHits->at(ai); // pixel hits >=1
	analysisSkeleton::nPIXhitsMub  = m_digestPhys->mu_staco_nPixHits->at(bi); // pixel hits >=1
	analysisSkeleton::nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
	analysisSkeleton::nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	analysisSkeleton::me_qOp_a   = m_digestPhys->mu_staco_me_qoverp->at(ai)/MeV2TeV;
	analysisSkeleton::id_qOp_a   = m_digestPhys->mu_staco_id_qoverp->at(ai)/MeV2TeV;
	analysisSkeleton::me_theta_a = m_digestPhys->mu_staco_me_theta->at(ai);
	analysisSkeleton::id_theta_a = m_digestPhys->mu_staco_id_theta->at(ai);
	analysisSkeleton::me_qOp_b   = m_digestPhys->mu_staco_me_qoverp->at(bi)/MeV2TeV;
	analysisSkeleton::id_qOp_b   = m_digestPhys->mu_staco_id_qoverp->at(bi)/MeV2TeV;
	analysisSkeleton::me_theta_b = m_digestPhys->mu_staco_me_theta->at(bi);
	analysisSkeleton::id_theta_b = m_digestPhys->mu_staco_id_theta->at(bi);
	
	// impact parameter
	analysisSkeleton::impPrmZ0 = m_digestPhys->mu_staco_z0_exPV->at(ai);
	analysisSkeleton::impPrmD0 = m_digestPhys->mu_staco_d0_exPV->at(ai);
	
	// isolation
	analysisSkeleton::mu_pTa   = m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV;
	analysisSkeleton::mu_pTb   = m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	analysisSkeleton::pTcone20a = m_digestPhys->mu_staco_ptcone20->at(ai)*MeV2TeV;
	analysisSkeleton::pTcone20b = m_digestPhys->mu_staco_ptcone20->at(bi)*MeV2TeV;
	analysisSkeleton::pTcone30a = m_digestPhys->mu_staco_ptcone30->at(ai)*MeV2TeV;
	analysisSkeleton::pTcone30b = m_digestPhys->mu_staco_ptcone30->at(bi)*MeV2TeV;
	analysisSkeleton::pTcone40a = m_digestPhys->mu_staco_ptcone40->at(ai)*MeV2TeV;
	analysisSkeleton::pTcone40b = m_digestPhys->mu_staco_ptcone40->at(bi)*MeV2TeV;
	
	// charge
	analysisSkeleton::mu_charge_a = m_digestPhys->mu_staco_charge->at(ai);
	analysisSkeleton::mu_charge_b = m_digestPhys->mu_staco_charge->at(bi);
	
	
	///////////////////////////////////////////////////////////////////////
	// these values go in the cutFlow histograms //////////////////////////
	TMapsd values2fill; ///////////////////////////////////////////////////
	values2fill.insert( make_pair( "imass",current_imass ) ); /////////////
	values2fill.insert( make_pair( "pT",   current_mu_pT ) ); /////////////
	///////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////
	// the entire selection and fill job /////
	applySelection(pmu, values2fill); ////////
	//////////////////////////////////////////
	
	////////////////////////////////////////////
	// re-initialize ///////////////////////////
	if(pmu.size()>0) pmu.clear(); //////////////
	////////////////////////////////////////////
}

void digestAnalysis::write()
{
	//m_treeFile->cd();
	//m_offTreeDigest->write();
}

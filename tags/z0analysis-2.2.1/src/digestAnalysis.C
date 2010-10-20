/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "digestAnalysis.h"

digestAnalysis::digestAnalysis()
{
	initialize();
}

digestAnalysis::digestAnalysis(digestPhysics* digestPhysics, graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, TFile* treeFile)
{
	initialize();

	m_digestPhys = digestPhysics;

	m_treeFile = treeFile;

	m_cutFlowHandler     = cutFlowHandler;
	m_cutFlowMapSVD      = m_cutFlowHandler->getCutFlowMapSVDPtr();
	m_cutFlowOrdered     = m_cutFlowHandler->getCutFlowOrderedMapPtr();
	m_cutFlowTypeOrdered = m_cutFlowHandler->getCutFlowTypeOrderedMapPtr();
	m_cutFlowNumbers     = m_cutFlowHandler->getCutFlowNumbersMapPtr();
	
	// cut flow has been read out already
	initSelectionCuts(m_cutFlowMapSVD, m_cutFlowOrdered, m_cutFlowTypeOrdered);

	m_graphicobjs = graphicobjs;
	m_graphicobjs->setCutFlowMapSVDPtr( m_cutFlowMapSVD );
	m_graphicobjs->ginitialize();
	
	m_fitter = fitter;
	
	// this is where all the analysis happens
	string sEventDumpFilePath = "digestAnalysis_interestingEvents.dump";
	initCombinedSelection(m_graphicobjs, m_cutFlowHandler, m_fitter, sEventDumpFilePath);
}

digestAnalysis::~digestAnalysis()
{

}

void digestAnalysis::initialize()
{

}

void digestAnalysis::finalize()
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
	runnumber   = m_digestPhys->RunNumber;
	lumiblock   = m_digestPhys->lbn;
	eventnumber = m_digestPhys->EventNumber;
	isGRL       = m_digestPhys->isGRL;
	isL1MU6     = m_digestPhys->L1_MU6;
	isEF_mu13   = m_digestPhys->EF_mu13;
	
	// muon (for the setMUindeces call)
	mu_staco_charge = m_digestPhys->mu_staco_charge;
	
	// muon  (for hipTmuon preselection)
	mu_staco_n         = m_digestPhys->mu_staco_n;
	mu_staco_pt        = m_digestPhys->mu_staco_pt;
	mu_staco_me_qoverp = m_digestPhys->mu_staco_me_qoverp;
	mu_staco_me_theta  = m_digestPhys->mu_staco_me_theta;
	
	// vertexes (for the PV preselection)
	vxp_n       = m_digestPhys->vxp_n;
	vxp_nTracks = m_digestPhys->vxp_nTracks;
	vxp_type    = m_digestPhys->vxp_type;
	vxp_z       = m_digestPhys->vxp_z;
	

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
	current_imass    = imass(pmu[ai],pmu[bi]);
	current_cosTheta = cosThetaCollinsSoper( pmu[ai], (double)m_digestPhys->mu_staco_charge->at(ai),
											 pmu[bi], (double)m_digestPhys->mu_staco_charge->at(bi) );
	current_mu_pT       = (m_digestPhys->mu_staco_charge->at(ai)<0) ? m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV : m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	current_muplus_pT   = (m_digestPhys->mu_staco_charge->at(ai)>0) ? m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV : m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	current_mu_eta      = (m_digestPhys->mu_staco_charge->at(ai)<0) ? m_digestPhys->mu_staco_eta->at(ai) : m_digestPhys->mu_staco_eta->at(bi);
	current_muplus_eta  = (m_digestPhys->mu_staco_charge->at(ai)>0) ? m_digestPhys->mu_staco_eta->at(ai) : m_digestPhys->mu_staco_eta->at(bi);
	current_cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );
	current_ipTdiff     = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_etaSum      = current_muplus_eta + current_mu_eta;
	
	// deprecated !!!
	d0exPVa = m_digestPhys->mu_staco_d0_exPV->at(ai);
	z0exPVa = m_digestPhys->mu_staco_z0_exPV->at(ai);
	d0exPVb = m_digestPhys->mu_staco_d0_exPV->at(bi);
	z0exPVb = m_digestPhys->mu_staco_z0_exPV->at(bi);
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	nPVtracksPtr = m_digestPhys->vxp_nTracks; // number of tracks > 2
	nPVtypePtr   = m_digestPhys->vxp_type;    // ==1
	PVz0Ptr      = m_digestPhys->vxp_z;       // = absolute z position of primary vertex < 150mm
	PVz0errPtr   = m_digestPhys->vxp_z_err;   // = error
	
	// combined muon ?
	isMuaComb  = m_digestPhys->mu_staco_isCombinedMuon->at(ai);
	isMubComb  = m_digestPhys->mu_staco_isCombinedMuon->at(bi);	
	
	// inner detector hits
	nSCThitsMua  = m_digestPhys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
	nSCThitsMub  = m_digestPhys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
	nPIXhitsMua  = m_digestPhys->mu_staco_nPixHits->at(ai); // pixel hits >=1
	nPIXhitsMub  = m_digestPhys->mu_staco_nPixHits->at(bi); // pixel hits >=1
	nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
	nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	me_qOp_a   = m_digestPhys->mu_staco_me_qoverp->at(ai)/MeV2TeV;
	id_qOp_a   = m_digestPhys->mu_staco_id_qoverp->at(ai)/MeV2TeV;
	me_theta_a = m_digestPhys->mu_staco_me_theta->at(ai);
	id_theta_a = m_digestPhys->mu_staco_id_theta->at(ai);
	me_qOp_b   = m_digestPhys->mu_staco_me_qoverp->at(bi)/MeV2TeV;
	id_qOp_b   = m_digestPhys->mu_staco_id_qoverp->at(bi)/MeV2TeV;
	me_theta_b = m_digestPhys->mu_staco_me_theta->at(bi);
	id_theta_b = m_digestPhys->mu_staco_id_theta->at(bi);
	
	// impact parameter
	impPrmZ0 = m_digestPhys->mu_staco_z0_exPV->at(ai);
	impPrmD0 = m_digestPhys->mu_staco_d0_exPV->at(ai);
	
	// isolation
	mu_pTa   = m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV;
	mu_pTb   = m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	pTcone20a = m_digestPhys->mu_staco_ptcone20->at(ai)*MeV2TeV;
	pTcone20b = m_digestPhys->mu_staco_ptcone20->at(bi)*MeV2TeV;
	pTcone30a = m_digestPhys->mu_staco_ptcone30->at(ai)*MeV2TeV;
	pTcone30b = m_digestPhys->mu_staco_ptcone30->at(bi)*MeV2TeV;
	pTcone40a = m_digestPhys->mu_staco_ptcone40->at(ai)*MeV2TeV;
	pTcone40b = m_digestPhys->mu_staco_ptcone40->at(bi)*MeV2TeV;
	
	// charge
	mu_charge_a = m_digestPhys->mu_staco_charge->at(ai);
	mu_charge_b = m_digestPhys->mu_staco_charge->at(bi);
	
	
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

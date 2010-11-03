/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysis.h"

analysis::analysis()
{

}

analysis::~analysis()
{

}

void analysis::executeAdvanced()
{

	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_phys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mustaco->getNParticles() ; n++)
		{
			m_mustaco->setParticle(n);
			h2_xyVertex->Fill( m_mustaco->pvVec->X(), m_mustaco->pvVec->Y() );
		}
	}
}

void analysis::executeCutFlow()
{
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// start allocating the variables for the preselection

	// event level (for preselection)
	analysisSkeleton::runnumber   = m_phys->RunNumber;
	analysisSkeleton::lumiblock   = m_phys->lbn;
	analysisSkeleton::eventnumber = m_phys->EventNumber;
	
	//////////////////////////////////////////////////////
	// do this only if the run number has changed ////////
	analysisSkeleton::sPeriod = getPeriodName(); /////////
	analysisSkeleton::vTriggers = getPeriodTriggers(); ///
	//////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	analysisSkeleton::isGRL       = m_analysis_grl->m_grl.HasRunLumiBlock( m_phys->RunNumber, m_phys->lbn ); ////
	m_offTree->fill(analysisSkeleton::isGRL, analysisSkeleton::sPeriod, analysisSkeleton::vTriggers); ///////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	// L1 triggers
	analysisSkeleton::isL1_MU0 = m_phys->L1_MU0;
	analysisSkeleton::isL1_MU10 = m_phys->L1_MU10;
	analysisSkeleton::isL1_MU15 = m_phys->L1_MU15;
	analysisSkeleton::isL1_MU20 = m_phys->L1_MU20;
	analysisSkeleton::isL1_MU6 = m_phys->L1_MU6;
	
	// EF triggers
	analysisSkeleton::isEF_mu10 = m_phys->EF_mu10;
	analysisSkeleton::isEF_mu10_MG = m_phys->EF_mu10_MG;
	analysisSkeleton::isEF_mu10_MSonly = m_phys->EF_mu10_MSonly;
	analysisSkeleton::isEF_mu10_MSonly_tight = m_phys->EF_mu10_MSonly_tight;
	analysisSkeleton::isEF_mu10_NoAlg = m_phys->EF_mu10_NoAlg;
	analysisSkeleton::isEF_mu10_tight = m_phys->EF_mu10_tight;
	analysisSkeleton::isEF_mu10i_loose = m_phys->EF_mu10i_loose;
	analysisSkeleton::isEF_mu13 = m_phys->EF_mu13;
	analysisSkeleton::isEF_mu13_MG = m_phys->EF_mu13_MG;
	analysisSkeleton::isEF_mu13_MG_tight = m_phys->EF_mu13_MG_tight;
	analysisSkeleton::isEF_mu13_tight = m_phys->EF_mu13_tight;
	analysisSkeleton::isEF_mu15 = m_phys->EF_mu15;
	analysisSkeleton::isEF_mu15_NoAlg = m_phys->EF_mu15_NoAlg;
	analysisSkeleton::isEF_mu20 = m_phys->EF_mu20;
	analysisSkeleton::isEF_mu20_MSonly = m_phys->EF_mu20_MSonly;
	analysisSkeleton::isEF_mu20_NoAlg = m_phys->EF_mu20_NoAlg;
	analysisSkeleton::isEF_mu20_slow = m_phys->EF_mu20_slow;
	analysisSkeleton::isEF_mu30_MSonly = m_phys->EF_mu30_MSonly;
	analysisSkeleton::isEF_mu4 = m_phys->EF_mu4;
	analysisSkeleton::isEF_mu40_MSonly = m_phys->EF_mu40_MSonly;
	
	
	// muon (for the setMUindeces call)
	analysisSkeleton::mu_staco_charge = m_phys->mu_staco_charge;
	
	// muon  (for hipTmuon preselection)
	analysisSkeleton::mu_staco_n         = m_phys->mu_staco_n;
	analysisSkeleton::mu_staco_pt        = m_phys->mu_staco_pt;
	analysisSkeleton::mu_staco_me_qoverp = m_phys->mu_staco_me_qoverp;
	analysisSkeleton::mu_staco_me_theta  = m_phys->mu_staco_me_theta;
	
	// vertexes (for the PV preselection)
	analysisSkeleton::vxp_n       = m_phys->vxp_n;
	analysisSkeleton::vxp_nTracks = m_phys->vxp_nTracks;
	analysisSkeleton::vxp_type    = m_phys->vxp_type;
	analysisSkeleton::vxp_z       = m_phys->vxp_z;
	

	///////////////////////////////////////////////////////
	// preform the entire preselection and counting job ///
	bool passPreselection = applyPreselection(); //////////
	if( !passPreselection ) return; ///////////////////////
	///////////////////////////////////////////////////////
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// start allocating the variables for TLorentzVector and indices settings
	
	//////////////////////////////////////////////////////////////////////
	// build vector of the muons TLorentzVector //////////////////////////
    // this needs to be looped acording to the size of the vector rather
	// than according to the value of mu_staco_n since in the digest tree
	// only the successive COUPLE is written.
	TVectorP2VL	pmu;
	for(int n=0 ; n<(int)m_phys->mu_staco_m->size() ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_phys->mu_staco_px->at(n)*MeV2TeV );
		pmu[n]->SetPy( m_phys->mu_staco_py->at(n)*MeV2TeV );
		pmu[n]->SetPz( m_phys->mu_staco_pz->at(n)*MeV2TeV );
		pmu[n]->SetE(  m_phys->mu_staco_E->at(n)*MeV2TeV );
	}
	///////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////
	// set the ai and bi muon indices /////////////////////////////////
	bool is2validIndices = setMUindices(pmu); /////////////////////////
	if(!is2validIndices) return; //////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	
	
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// start allocating the variables for the selection
	
	// calculate the necessary variables
	analysisSkeleton::current_imass    = imass(pmu[ai],pmu[bi]);
	analysisSkeleton::current_cosTheta = cosThetaCollinsSoper( pmu[ai], (double)m_phys->mu_staco_charge->at(ai),
											 pmu[bi], (double)m_phys->mu_staco_charge->at(bi) );
	analysisSkeleton::current_mu_pT       = (m_phys->mu_staco_charge->at(ai)<0) ? m_phys->mu_staco_pt->at(ai)*MeV2TeV : m_phys->mu_staco_pt->at(bi)*MeV2TeV;
	analysisSkeleton::current_muplus_pT   = (m_phys->mu_staco_charge->at(ai)>0) ? m_phys->mu_staco_pt->at(ai)*MeV2TeV : m_phys->mu_staco_pt->at(bi)*MeV2TeV;
	analysisSkeleton::current_mu_eta      = (m_phys->mu_staco_charge->at(ai)<0) ? m_phys->mu_staco_eta->at(ai) : m_phys->mu_staco_eta->at(bi);
	analysisSkeleton::current_muplus_eta  = (m_phys->mu_staco_charge->at(ai)>0) ? m_phys->mu_staco_eta->at(ai) : m_phys->mu_staco_eta->at(bi);
	analysisSkeleton::current_cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );
	analysisSkeleton::current_ipTdiff     = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	analysisSkeleton::current_etaSum      = current_muplus_eta + current_mu_eta;
	
	// deprecated !!!
	analysisSkeleton::d0exPVa = m_phys->mu_staco_d0_exPV->at(ai);
	analysisSkeleton::z0exPVa = m_phys->mu_staco_z0_exPV->at(ai);
	analysisSkeleton::d0exPVb = m_phys->mu_staco_d0_exPV->at(bi);
	analysisSkeleton::z0exPVb = m_phys->mu_staco_z0_exPV->at(bi);
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	analysisSkeleton::nPVtracksPtr = m_phys->vxp_nTracks; // number of tracks > 2
	analysisSkeleton::nPVtypePtr   = m_phys->vxp_type;    // ==1
	analysisSkeleton::PVz0Ptr      = m_phys->vxp_z;       // = absolute z position of primary vertex < 150mm
	analysisSkeleton::PVz0errPtr   = m_phys->vxp_err_z;   // = error
	
	// combined muon ?
	analysisSkeleton::isMuaComb  = m_phys->mu_staco_isCombinedMuon->at(ai);
	analysisSkeleton::isMubComb  = m_phys->mu_staco_isCombinedMuon->at(bi);	
	
	// inner detector hits
	analysisSkeleton::nSCThitsMua  = m_phys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
	analysisSkeleton::nSCThitsMub  = m_phys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
	analysisSkeleton::nPIXhitsMua  = m_phys->mu_staco_nPixHits->at(ai); // pixel hits >=1
	analysisSkeleton::nPIXhitsMub  = m_phys->mu_staco_nPixHits->at(bi); // pixel hits >=1
	analysisSkeleton::nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
	analysisSkeleton::nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
	
	// muon spectrometer hits
	analysisSkeleton::nMDTBIHitsMua = m_phys->mu_staco_nMDTBIHits->at(ai);
	analysisSkeleton::nMDTBMHitsMua = m_phys->mu_staco_nMDTBMHits->at(ai);
	analysisSkeleton::nMDTBOHitsMua = m_phys->mu_staco_nMDTBOHits->at(ai);
	analysisSkeleton::nMDTBEEHitsMua = m_phys->mu_staco_nMDTBEEHits->at(ai);
	analysisSkeleton::nMDTBIS78HitsMua = m_phys->mu_staco_nMDTBIS78Hits->at(ai);
	analysisSkeleton::nMDTEIHitsMua = m_phys->mu_staco_nMDTEIHits->at(ai);
	analysisSkeleton::nMDTEMHitsMua = m_phys->mu_staco_nMDTEMHits->at(ai);
	analysisSkeleton::nMDTEOHitsMua = m_phys->mu_staco_nMDTEOHits->at(ai);
	analysisSkeleton::nMDTEEHitsMua = m_phys->mu_staco_nMDTEEHits->at(ai);
	analysisSkeleton::nRPCLayer1EtaHitsMua = m_phys->mu_staco_nRPCLayer1EtaHits->at(ai);
	analysisSkeleton::nRPCLayer2EtaHitsMua = m_phys->mu_staco_nRPCLayer2EtaHits->at(ai);
	analysisSkeleton::nRPCLayer3EtaHitsMua = m_phys->mu_staco_nRPCLayer3EtaHits->at(ai);
	analysisSkeleton::nRPCLayer1PhiHitsMua = m_phys->mu_staco_nRPCLayer1PhiHits->at(ai);
	analysisSkeleton::nRPCLayer2PhiHitsMua = m_phys->mu_staco_nRPCLayer2PhiHits->at(ai);
	analysisSkeleton::nRPCLayer3PhiHitsMua = m_phys->mu_staco_nRPCLayer3PhiHits->at(ai);
	analysisSkeleton::nTGCLayer1EtaHitsMua = m_phys->mu_staco_nTGCLayer1EtaHits->at(ai);
	analysisSkeleton::nTGCLayer2EtaHitsMua = m_phys->mu_staco_nTGCLayer2EtaHits->at(ai);
	analysisSkeleton::nTGCLayer3EtaHitsMua = m_phys->mu_staco_nTGCLayer3EtaHits->at(ai);
	analysisSkeleton::nTGCLayer4EtaHitsMua = m_phys->mu_staco_nTGCLayer4EtaHits->at(ai);
	analysisSkeleton::nTGCLayer1PhiHitsMua = m_phys->mu_staco_nTGCLayer1PhiHits->at(ai);
	analysisSkeleton::nTGCLayer2PhiHitsMua = m_phys->mu_staco_nTGCLayer2PhiHits->at(ai);
	analysisSkeleton::nTGCLayer3PhiHitsMua = m_phys->mu_staco_nTGCLayer3PhiHits->at(ai);
	analysisSkeleton::nTGCLayer4PhiHitsMua = m_phys->mu_staco_nTGCLayer4PhiHits->at(ai);
	
	analysisSkeleton::nMDTBIHitsMub = m_phys->mu_staco_nMDTBIHits->at(bi);
	analysisSkeleton::nMDTBMHitsMub = m_phys->mu_staco_nMDTBMHits->at(bi);
	analysisSkeleton::nMDTBOHitsMub = m_phys->mu_staco_nMDTBOHits->at(bi);
	analysisSkeleton::nMDTBEEHitsMub = m_phys->mu_staco_nMDTBEEHits->at(bi);
	analysisSkeleton::nMDTBIS78HitsMub = m_phys->mu_staco_nMDTBIS78Hits->at(bi);
	analysisSkeleton::nMDTEIHitsMub = m_phys->mu_staco_nMDTEIHits->at(bi);
	analysisSkeleton::nMDTEMHitsMub = m_phys->mu_staco_nMDTEMHits->at(bi);
	analysisSkeleton::nMDTEOHitsMub = m_phys->mu_staco_nMDTEOHits->at(bi);
	analysisSkeleton::nMDTEEHitsMub = m_phys->mu_staco_nMDTEEHits->at(bi);
	analysisSkeleton::nRPCLayer1EtaHitsMub = m_phys->mu_staco_nRPCLayer1EtaHits->at(bi);
	analysisSkeleton::nRPCLayer2EtaHitsMub = m_phys->mu_staco_nRPCLayer2EtaHits->at(bi);
	analysisSkeleton::nRPCLayer3EtaHitsMub = m_phys->mu_staco_nRPCLayer3EtaHits->at(bi);
	analysisSkeleton::nRPCLayer1PhiHitsMub = m_phys->mu_staco_nRPCLayer1PhiHits->at(bi);
	analysisSkeleton::nRPCLayer2PhiHitsMub = m_phys->mu_staco_nRPCLayer2PhiHits->at(bi);
	analysisSkeleton::nRPCLayer3PhiHitsMub = m_phys->mu_staco_nRPCLayer3PhiHits->at(bi);
	analysisSkeleton::nTGCLayer1EtaHitsMub = m_phys->mu_staco_nTGCLayer1EtaHits->at(bi);
	analysisSkeleton::nTGCLayer2EtaHitsMub = m_phys->mu_staco_nTGCLayer2EtaHits->at(bi);
	analysisSkeleton::nTGCLayer3EtaHitsMub = m_phys->mu_staco_nTGCLayer3EtaHits->at(bi);
	analysisSkeleton::nTGCLayer4EtaHitsMub = m_phys->mu_staco_nTGCLayer4EtaHits->at(bi);
	analysisSkeleton::nTGCLayer1PhiHitsMub = m_phys->mu_staco_nTGCLayer1PhiHits->at(bi);
	analysisSkeleton::nTGCLayer2PhiHitsMub = m_phys->mu_staco_nTGCLayer2PhiHits->at(bi);
	analysisSkeleton::nTGCLayer3PhiHitsMub = m_phys->mu_staco_nTGCLayer3PhiHits->at(bi);
	analysisSkeleton::nTGCLayer4PhiHitsMub = m_phys->mu_staco_nTGCLayer4PhiHits->at(bi);
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	analysisSkeleton::me_qOp_a   = m_phys->mu_staco_me_qoverp->at(ai)/MeV2TeV;
	analysisSkeleton::id_qOp_a   = m_phys->mu_staco_id_qoverp->at(ai)/MeV2TeV;
	analysisSkeleton::me_theta_a = m_phys->mu_staco_me_theta->at(ai);
	analysisSkeleton::id_theta_a = m_phys->mu_staco_id_theta->at(ai);
	analysisSkeleton::me_qOp_b   = m_phys->mu_staco_me_qoverp->at(bi)/MeV2TeV;
	analysisSkeleton::id_qOp_b   = m_phys->mu_staco_id_qoverp->at(bi)/MeV2TeV;
	analysisSkeleton::me_theta_b = m_phys->mu_staco_me_theta->at(bi);
	analysisSkeleton::id_theta_b = m_phys->mu_staco_id_theta->at(bi);
	
	// impact parameter
	analysisSkeleton::impPrmZ0 = m_phys->mu_staco_z0_exPV->at(ai);
	analysisSkeleton::impPrmD0 = m_phys->mu_staco_d0_exPV->at(ai);
	
	// isolation
	analysisSkeleton::mu_pTa   = m_phys->mu_staco_pt->at(ai)*MeV2TeV;
	analysisSkeleton::mu_pTb   = m_phys->mu_staco_pt->at(bi)*MeV2TeV;
	analysisSkeleton::pTcone20a = m_phys->mu_staco_ptcone20->at(ai)*MeV2TeV;
	analysisSkeleton::pTcone20b = m_phys->mu_staco_ptcone20->at(bi)*MeV2TeV;
	analysisSkeleton::pTcone30a = m_phys->mu_staco_ptcone30->at(ai)*MeV2TeV;
	analysisSkeleton::pTcone30b = m_phys->mu_staco_ptcone30->at(bi)*MeV2TeV;
	analysisSkeleton::pTcone40a = m_phys->mu_staco_ptcone40->at(ai)*MeV2TeV;
	analysisSkeleton::pTcone40b = m_phys->mu_staco_ptcone40->at(bi)*MeV2TeV;
	
	// charge
	analysisSkeleton::mu_charge_a = m_phys->mu_staco_charge->at(ai);
	analysisSkeleton::mu_charge_b = m_phys->mu_staco_charge->at(bi);
	
	
	
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

void analysis::write()
{
	m_treeFile->cd();
	m_offTree->write();
}

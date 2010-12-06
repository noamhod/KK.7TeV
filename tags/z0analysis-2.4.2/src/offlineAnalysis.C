/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineAnalysis.h"

offlineAnalysis::offlineAnalysis()
{

}


offlineAnalysis::~offlineAnalysis()
{

}


void offlineAnalysis::executeAdvanced()
{

/*
	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_offPhys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mustaco->getNParticles() ; n++)
		{
			m_mustaco->setParticle(n);
			m_graphicobjs->h2_xyVertex->Fill( m_mustaco->pvVec->X(), m_mustaco->pvVec->Y() );
		}
	}
*/
}

void offlineAnalysis::executeCutFlow()
{
	sMuonRecoAlgo = "muid";
	
	///////////////////////////////////
	// set all the event-level vars ///
	setEventVariables(); //////////////
	///////////////////////////////////
	
	/////////////////////////////////////////////////////
	// set all the muon reco' alg vars //////////////////
	if(sMuonRecoAlgo=="staco")
	{
		setStacoVariables();
		nMus = (int)m_offPhys->mu_staco_pt->size();
	}
	if(sMuonRecoAlgo=="muid")
	{
		setMuidVariables();
		nMus = (int)m_offPhys->mu_muid_pt->size();
	}
	/////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////
	// reset the muQAflags vector with "true" flags /////
	// build the muons TLorentzVector ///////////////////
	// no need to do this if didn't pass preselection ///
	buildMU4Vector(nMus, "angles"); /////////////////////
	//buildMU4Vector(nMus); /////////////////////////////
	/////////////////////////////////////////////////////

	////////////////////////////////////////
	// execute the cut profile analysis ////
	fillCutProfile1D(); ////////////////////
	fillCutProfile2D(); ////////////////////
	////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////
	// write to the digest tree only the pairs that pass skim ////
	bool passSkim = digestSkim(nMus); ////////////////////////////
	if( passSkim ) m_muSkimD3PD->fill(analysisSkeleton::isGRL); //
	//////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	// preform the entire preselection //////////////////
	bool passPreselection = applyPreselection(); ////////
	if( !passPreselection ) return; /////////////////////
	/////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////
	// the single muon selection //////////////////////////
	bool pass1MUselection = applySingleMuonSelection(); ///
	if( !pass1MUselection ) return; ///////////////////////
	///////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////
	// the double muon selection ///////////////////////////
	bool pass2MUselection = applyDoubleMuonSelection(); ////
	if( !pass2MUselection ) return; ////////////////////////
	////////////////////////////////////////////////////////
}

void offlineAnalysis::setEventVariables()
{
	// event level (for preselection)
	analysisSkeleton::RunNumber    = m_offPhys->RunNumber;
	analysisSkeleton::EventNumber  = m_offPhys->EventNumber;
	analysisSkeleton::timestamp    = m_offPhys->timestamp;
	analysisSkeleton::timestamp_ns = m_offPhys->timestamp_ns;
	analysisSkeleton::lbn          = m_offPhys->lbn;
	analysisSkeleton::bcid         = m_offPhys->bcid;
	analysisSkeleton::detmask0     = m_offPhys->detmask0;
	analysisSkeleton::detmask1     = m_offPhys->detmask1;
	analysisSkeleton::pixelFlags   = m_offPhys->pixelFlags;
	analysisSkeleton::sctFlags     = m_offPhys->sctFlags;
	analysisSkeleton::trtFlags     = m_offPhys->trtFlags;
	analysisSkeleton::larFlags     = m_offPhys->larFlags;
	analysisSkeleton::tileFlags    = m_offPhys->tileFlags;
	analysisSkeleton::muonFlags    = m_offPhys->muonFlags;
	analysisSkeleton::fwdFlags     = m_offPhys->fwdFlags;
	analysisSkeleton::coreFlags    = m_offPhys->coreFlags;
	analysisSkeleton::pixelError   = m_offPhys->pixelError;
	analysisSkeleton::sctError     = m_offPhys->sctError;
	analysisSkeleton::trtError     = m_offPhys->trtError;
	analysisSkeleton::larError     = m_offPhys->larError;
	analysisSkeleton::tileError    = m_offPhys->tileError;
	analysisSkeleton::muonError    = m_offPhys->muonError;
	analysisSkeleton::fwdError     = m_offPhys->fwdError;
	analysisSkeleton::coreError    = m_offPhys->coreError;
	analysisSkeleton::lar_ncellA   = m_offPhys->lar_ncellA;
	analysisSkeleton::lar_ncellC   = m_offPhys->lar_ncellC;
	analysisSkeleton::lar_energyA  = m_offPhys->lar_energyA;
	analysisSkeleton::lar_energyC  = m_offPhys->lar_energyC;
	analysisSkeleton::lar_timeA    = m_offPhys->lar_timeA;
	analysisSkeleton::lar_timeC    = m_offPhys->lar_timeC;
	analysisSkeleton::lar_timeDiff = m_offPhys->lar_timeDiff;
	
	analysisSkeleton::isGRL       = m_offAnalysis_grl->m_grl.HasRunLumiBlock( m_offPhys->RunNumber, m_offPhys->lbn );
	
	//////////////////////////////////////////////////////
	// do this only if the run number has changed ////////
	analysisSkeleton::sPeriod   = getPeriodName(); ///////
	analysisSkeleton::vTriggers = getPeriodTriggers(); ///
	//////////////////////////////////////////////////////
	//analysisSkeleton::sPeriod     = m_offPhys->period;
	//analysisSkeleton::vTriggers   = m_offPhys->vTriggers;
	
	// L1 triggers
	analysisSkeleton::isL1_MU0  = m_offPhys->L1_MU0;
	analysisSkeleton::isL1_MU10 = m_offPhys->L1_MU10;
	analysisSkeleton::isL1_MU15 = m_offPhys->L1_MU15;
	analysisSkeleton::isL1_MU20 = m_offPhys->L1_MU20;
	analysisSkeleton::isL1_MU6  = m_offPhys->L1_MU6;
	
	// NOTE !!! THESE BRANCHES ARE DISABLED ALSO IN THE "offTree" CLASS
	// EF triggers
	analysisSkeleton::isEF_mu10 = m_offPhys->EF_mu10;
	analysisSkeleton::isEF_mu10_MG = m_offPhys->EF_mu10_MG;
	analysisSkeleton::isEF_mu10_MSonly = m_offPhys->EF_mu10_MSonly;
	analysisSkeleton::isEF_mu10_MSonly_tight = m_offPhys->EF_mu10_MSonly_tight;
	analysisSkeleton::isEF_mu10_NoAlg = m_offPhys->EF_mu10_NoAlg;
	analysisSkeleton::isEF_mu10_tight = m_offPhys->EF_mu10_tight;
	analysisSkeleton::isEF_mu10i_loose = m_offPhys->EF_mu10i_loose;
	analysisSkeleton::isEF_mu13 = m_offPhys->EF_mu13;
	analysisSkeleton::isEF_mu13_MG = m_offPhys->EF_mu13_MG;
	analysisSkeleton::isEF_mu13_MG_tight = m_offPhys->EF_mu13_MG_tight;
	analysisSkeleton::isEF_mu13_tight = m_offPhys->EF_mu13_tight;
	analysisSkeleton::isEF_mu15 = m_offPhys->EF_mu15;
	analysisSkeleton::isEF_mu15_NoAlg = m_offPhys->EF_mu15_NoAlg;
	analysisSkeleton::isEF_mu20 = m_offPhys->EF_mu20;
	analysisSkeleton::isEF_mu20_MSonly = m_offPhys->EF_mu20_MSonly;
	analysisSkeleton::isEF_mu20_NoAlg = m_offPhys->EF_mu20_NoAlg;
	analysisSkeleton::isEF_mu20_slow = m_offPhys->EF_mu20_slow;
	analysisSkeleton::isEF_mu30_MSonly = m_offPhys->EF_mu30_MSonly;
	analysisSkeleton::isEF_mu4 = m_offPhys->EF_mu4;
	analysisSkeleton::isEF_mu40_MSonly = m_offPhys->EF_mu40_MSonly;
	
	// vertexes (for the PV preselection)
	analysisSkeleton::vxp_n       = m_offPhys->vxp_n;
	analysisSkeleton::vxp_nTracks = m_offPhys->vxp_nTracks;
	analysisSkeleton::vxp_type    = m_offPhys->vxp_type;
	analysisSkeleton::vxp_z       = m_offPhys->vxp_z;
}

void offlineAnalysis::setStacoVariables()
{
	// muon 
	analysisSkeleton::mu_n         = m_offPhys->mu_staco_n;
	analysisSkeleton::mu_m         = m_offPhys->mu_staco_m;
	analysisSkeleton::mu_px        = m_offPhys->mu_staco_px;
	analysisSkeleton::mu_py        = m_offPhys->mu_staco_py;
	analysisSkeleton::mu_pz        = m_offPhys->mu_staco_pz;
	analysisSkeleton::mu_E         = m_offPhys->mu_staco_E;
	analysisSkeleton::mu_eta       = m_offPhys->mu_staco_eta;
	analysisSkeleton::mu_phi       = m_offPhys->mu_staco_phi;
	analysisSkeleton::mu_pt        = m_offPhys->mu_staco_pt;
	analysisSkeleton::mu_charge    = m_offPhys->mu_staco_charge;
	analysisSkeleton::mu_allauthor = m_offPhys->mu_staco_allauthor;
	analysisSkeleton::mu_author    = m_offPhys->mu_staco_author;
	analysisSkeleton::mu_matchchi2 = m_offPhys->mu_staco_matchchi2;
	analysisSkeleton::mu_matchndof = m_offPhys->mu_staco_matchndof;
	
	// isolation
	analysisSkeleton::mu_ptcone20 = m_offPhys->mu_staco_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_offPhys->mu_staco_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_offPhys->mu_staco_ptcone40;
	
	// for pT
	analysisSkeleton::mu_me_qoverp = m_offPhys->mu_staco_me_qoverp;
	analysisSkeleton::mu_id_qoverp = m_offPhys->mu_staco_id_qoverp;
	analysisSkeleton::mu_me_theta  = m_offPhys->mu_staco_me_theta;
	analysisSkeleton::mu_id_theta  = m_offPhys->mu_staco_id_theta;
	
	// for impact parameter
	analysisSkeleton::mu_d0_exPV = m_offPhys->mu_staco_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_offPhys->mu_staco_z0_exPV;
	
	// combined muons
	analysisSkeleton::mu_isCombinedMuon  = m_offPhys->mu_staco_isCombinedMuon;
	
	// inner detector hits
	analysisSkeleton::mu_nSCTHits  = m_offPhys->mu_staco_nSCTHits;
	analysisSkeleton::mu_nPixHits  = m_offPhys->mu_staco_nPixHits; 

	// muon spectrometer hits
	analysisSkeleton::mu_nMDTBIHits = m_offPhys->mu_staco_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_offPhys->mu_staco_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_offPhys->mu_staco_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_offPhys->mu_staco_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_offPhys->mu_staco_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_offPhys->mu_staco_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_offPhys->mu_staco_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_offPhys->mu_staco_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_offPhys->mu_staco_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_offPhys->mu_staco_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_offPhys->mu_staco_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_offPhys->mu_staco_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_offPhys->mu_staco_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_offPhys->mu_staco_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_offPhys->mu_staco_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_offPhys->mu_staco_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_offPhys->mu_staco_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_offPhys->mu_staco_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_offPhys->mu_staco_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_offPhys->mu_staco_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_offPhys->mu_staco_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_offPhys->mu_staco_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_offPhys->mu_staco_nTGCLayer4PhiHits;
	
	analysisSkeleton::mu_etcone20 = m_offPhys->mu_staco_etcone20;
	analysisSkeleton::mu_etcone30 = m_offPhys->mu_staco_etcone30;
	analysisSkeleton::mu_etcone40 = m_offPhys->mu_staco_etcone40;
	analysisSkeleton::mu_nucone20 = m_offPhys->mu_staco_nucone20;
	analysisSkeleton::mu_nucone30 = m_offPhys->mu_staco_nucone30;
	analysisSkeleton::mu_nucone40 = m_offPhys->mu_staco_nucone40;
	analysisSkeleton::mu_energyLossPar = m_offPhys->mu_staco_energyLossPar;
	analysisSkeleton::mu_energyLossErr = m_offPhys->mu_staco_energyLossErr;
	analysisSkeleton::mu_bestMatch = m_offPhys->mu_staco_bestMatch;
	analysisSkeleton::mu_isStandAloneMuon = m_offPhys->mu_staco_isStandAloneMuon;
	analysisSkeleton::mu_isLowPtReconstructedMuon = m_offPhys->mu_staco_isLowPtReconstructedMuon;
	analysisSkeleton::mu_loose = m_offPhys->mu_staco_loose;
	analysisSkeleton::mu_medium = m_offPhys->mu_staco_medium;
	analysisSkeleton::mu_tight = m_offPhys->mu_staco_tight;
	analysisSkeleton::mu_phi_exPV = m_offPhys->mu_staco_phi_exPV;
	analysisSkeleton::mu_theta_exPV = m_offPhys->mu_staco_theta_exPV;
	analysisSkeleton::mu_qoverp_exPV = m_offPhys->mu_staco_qoverp_exPV;
	analysisSkeleton::mu_cov_d0_exPV = m_offPhys->mu_staco_cov_d0_exPV;
	analysisSkeleton::mu_cov_z0_exPV = m_offPhys->mu_staco_cov_z0_exPV;
	analysisSkeleton::mu_cov_phi_exPV = m_offPhys->mu_staco_cov_phi_exPV;
	analysisSkeleton::mu_cov_theta_exPV = m_offPhys->mu_staco_cov_theta_exPV;
	analysisSkeleton::mu_cov_qoverp_exPV = m_offPhys->mu_staco_cov_qoverp_exPV;
	analysisSkeleton::mu_cov_d0_z0_exPV = m_offPhys->mu_staco_cov_d0_z0_exPV;
	analysisSkeleton::mu_cov_d0_phi_exPV = m_offPhys->mu_staco_cov_d0_phi_exPV;
	analysisSkeleton::mu_cov_d0_theta_exPV = m_offPhys->mu_staco_cov_d0_theta_exPV;
	analysisSkeleton::mu_cov_d0_qoverp_exPV = m_offPhys->mu_staco_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_cov_z0_phi_exPV = m_offPhys->mu_staco_cov_z0_phi_exPV;
	analysisSkeleton::mu_cov_z0_theta_exPV = m_offPhys->mu_staco_cov_z0_theta_exPV;
	analysisSkeleton::mu_cov_z0_qoverp_exPV = m_offPhys->mu_staco_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_cov_phi_theta_exPV = m_offPhys->mu_staco_cov_phi_theta_exPV;
	analysisSkeleton::mu_cov_phi_qoverp_exPV = m_offPhys->mu_staco_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_cov_theta_qoverp_exPV = m_offPhys->mu_staco_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_ms_d0 = m_offPhys->mu_staco_ms_d0;
	analysisSkeleton::mu_ms_z0 = m_offPhys->mu_staco_ms_z0;
	analysisSkeleton::mu_ms_phi = m_offPhys->mu_staco_ms_phi;
	analysisSkeleton::mu_ms_theta = m_offPhys->mu_staco_ms_theta;
	analysisSkeleton::mu_ms_qoverp = m_offPhys->mu_staco_ms_qoverp;
	analysisSkeleton::mu_id_d0 = m_offPhys->mu_staco_id_d0;
	analysisSkeleton::mu_id_z0 = m_offPhys->mu_staco_id_z0;
	analysisSkeleton::mu_id_phi = m_offPhys->mu_staco_id_phi;
	analysisSkeleton::mu_me_d0 = m_offPhys->mu_staco_me_d0;
	analysisSkeleton::mu_me_z0 = m_offPhys->mu_staco_me_z0;
	analysisSkeleton::mu_me_phi = m_offPhys->mu_staco_me_phi;
	analysisSkeleton::mu_ie_d0 = m_offPhys->mu_staco_ie_d0;
	analysisSkeleton::mu_ie_z0 = m_offPhys->mu_staco_ie_z0;
	analysisSkeleton::mu_ie_phi = m_offPhys->mu_staco_ie_phi;
	analysisSkeleton::mu_ie_theta = m_offPhys->mu_staco_ie_theta;
	analysisSkeleton::mu_ie_qoverp = m_offPhys->mu_staco_ie_qoverp;
	analysisSkeleton::mu_nBLHits = m_offPhys->mu_staco_nBLHits;
	analysisSkeleton::mu_nTRTHighTHits = m_offPhys->mu_staco_nTRTHighTHits;
	analysisSkeleton::mu_nBLSharedHits = m_offPhys->mu_staco_nBLSharedHits;
	analysisSkeleton::mu_nPixSharedHits = m_offPhys->mu_staco_nPixSharedHits;
	analysisSkeleton::mu_nPixHoles = m_offPhys->mu_staco_nPixHoles;
	analysisSkeleton::mu_nSCTSharedHits = m_offPhys->mu_staco_nSCTSharedHits;
	analysisSkeleton::mu_nSCTHoles = m_offPhys->mu_staco_nSCTHoles;
	analysisSkeleton::mu_nTRTOutliers = m_offPhys->mu_staco_nTRTOutliers;
	analysisSkeleton::mu_nTRTHighTOutliers = m_offPhys->mu_staco_nTRTHighTOutliers;
	analysisSkeleton::mu_nMDTHits = m_offPhys->mu_staco_nMDTHits;
	analysisSkeleton::mu_nMDTHoles = m_offPhys->mu_staco_nMDTHoles;
	analysisSkeleton::mu_nCSCEtaHits = m_offPhys->mu_staco_nCSCEtaHits;
	analysisSkeleton::mu_nCSCEtaHoles = m_offPhys->mu_staco_nCSCEtaHoles;
	analysisSkeleton::mu_nCSCPhiHits = m_offPhys->mu_staco_nCSCPhiHits;
	analysisSkeleton::mu_nCSCPhiHoles = m_offPhys->mu_staco_nCSCPhiHoles;
	analysisSkeleton::mu_nRPCEtaHits = m_offPhys->mu_staco_nRPCEtaHits;
	analysisSkeleton::mu_nRPCEtaHoles = m_offPhys->mu_staco_nRPCEtaHoles;
	analysisSkeleton::mu_nRPCPhiHits = m_offPhys->mu_staco_nRPCPhiHits;
	analysisSkeleton::mu_nRPCPhiHoles = m_offPhys->mu_staco_nRPCPhiHoles;
	analysisSkeleton::mu_nTGCEtaHits = m_offPhys->mu_staco_nTGCEtaHits;
	analysisSkeleton::mu_nTGCEtaHoles = m_offPhys->mu_staco_nTGCEtaHoles;
	analysisSkeleton::mu_nTGCPhiHits = m_offPhys->mu_staco_nTGCPhiHits;
	analysisSkeleton::mu_nTGCPhiHoles = m_offPhys->mu_staco_nTGCPhiHoles;
	analysisSkeleton::mu_nGangedPixels = m_offPhys->mu_staco_nGangedPixels;
	analysisSkeleton::mu_nOutliersOnTrack = m_offPhys->mu_staco_nOutliersOnTrack;
	analysisSkeleton::mu_barrelSectors = m_offPhys->mu_staco_barrelSectors;
	analysisSkeleton::mu_endcapSectors = m_offPhys->mu_staco_endcapSectors;
	analysisSkeleton::mu_trackd0 = m_offPhys->mu_staco_trackd0;
	analysisSkeleton::mu_trackz0 = m_offPhys->mu_staco_trackz0;
	analysisSkeleton::mu_trackphi = m_offPhys->mu_staco_trackphi;
	analysisSkeleton::mu_tracktheta = m_offPhys->mu_staco_tracktheta;
	analysisSkeleton::mu_trackqoverp = m_offPhys->mu_staco_trackqoverp;
	analysisSkeleton::mu_trackcov_d0 = m_offPhys->mu_staco_trackcov_d0;
	analysisSkeleton::mu_trackcov_z0 = m_offPhys->mu_staco_trackcov_z0;
	analysisSkeleton::mu_trackcov_phi = m_offPhys->mu_staco_trackcov_phi;
	analysisSkeleton::mu_trackcov_theta = m_offPhys->mu_staco_trackcov_theta;
	analysisSkeleton::mu_trackcov_qoverp = m_offPhys->mu_staco_trackcov_qoverp;
	analysisSkeleton::mu_trackcov_d0_z0 = m_offPhys->mu_staco_trackcov_d0_z0;
	analysisSkeleton::mu_trackcov_d0_phi = m_offPhys->mu_staco_trackcov_d0_phi;
	analysisSkeleton::mu_trackcov_d0_theta = m_offPhys->mu_staco_trackcov_d0_theta;
	analysisSkeleton::mu_trackcov_d0_qoverp = m_offPhys->mu_staco_trackcov_d0_qoverp;
	analysisSkeleton::mu_trackcov_z0_phi = m_offPhys->mu_staco_trackcov_z0_phi;
	analysisSkeleton::mu_trackcov_z0_theta = m_offPhys->mu_staco_trackcov_z0_theta;
	analysisSkeleton::mu_trackcov_z0_qoverp = m_offPhys->mu_staco_trackcov_z0_qoverp;
	analysisSkeleton::mu_trackcov_phi_theta = m_offPhys->mu_staco_trackcov_phi_theta;
	analysisSkeleton::mu_trackcov_phi_qoverp = m_offPhys->mu_staco_trackcov_phi_qoverp;
	analysisSkeleton::mu_trackcov_theta_qoverp = m_offPhys->mu_staco_trackcov_theta_qoverp;
	analysisSkeleton::mu_trackfitchi2 = m_offPhys->mu_staco_trackfitchi2;
	analysisSkeleton::mu_trackfitndof = m_offPhys->mu_staco_trackfitndof;
	analysisSkeleton::mu_hastrack = m_offPhys->mu_staco_hastrack;
	analysisSkeleton::mu_EF_dr = m_offPhys->mu_staco_EF_dr;
	analysisSkeleton::mu_EF_cb_eta = m_offPhys->mu_staco_EF_cb_eta;
	analysisSkeleton::mu_EF_cb_phi = m_offPhys->mu_staco_EF_cb_phi;
	analysisSkeleton::mu_EF_cb_pt = m_offPhys->mu_staco_EF_cb_pt;
	analysisSkeleton::mu_EF_ms_eta = m_offPhys->mu_staco_EF_ms_eta;
	analysisSkeleton::mu_EF_ms_phi = m_offPhys->mu_staco_EF_ms_phi;
	analysisSkeleton::mu_EF_ms_pt = m_offPhys->mu_staco_EF_ms_pt;
	analysisSkeleton::mu_EF_me_eta = m_offPhys->mu_staco_EF_me_eta;
	analysisSkeleton::mu_EF_me_phi = m_offPhys->mu_staco_EF_me_phi;
	analysisSkeleton::mu_EF_me_pt = m_offPhys->mu_staco_EF_me_pt;
	analysisSkeleton::mu_EF_matched = m_offPhys->mu_staco_EF_matched;
	analysisSkeleton::mu_L2CB_dr = m_offPhys->mu_staco_L2CB_dr;
	analysisSkeleton::mu_L2CB_pt = m_offPhys->mu_staco_L2CB_pt;
	analysisSkeleton::mu_L2CB_eta = m_offPhys->mu_staco_L2CB_eta;
	analysisSkeleton::mu_L2CB_phi = m_offPhys->mu_staco_L2CB_phi;
	analysisSkeleton::mu_L2CB_id_pt = m_offPhys->mu_staco_L2CB_id_pt;
	analysisSkeleton::mu_L2CB_ms_pt = m_offPhys->mu_staco_L2CB_ms_pt;
	analysisSkeleton::mu_L2CB_nPixHits = m_offPhys->mu_staco_L2CB_nPixHits;
	analysisSkeleton::mu_L2CB_nSCTHits = m_offPhys->mu_staco_L2CB_nSCTHits;
	analysisSkeleton::mu_L2CB_nTRTHits = m_offPhys->mu_staco_L2CB_nTRTHits;
	analysisSkeleton::mu_L2CB_nTRTHighTHits = m_offPhys->mu_staco_L2CB_nTRTHighTHits;
	analysisSkeleton::mu_L2CB_matched = m_offPhys->mu_staco_L2CB_matched;
	analysisSkeleton::mu_L1_dr = m_offPhys->mu_staco_L1_dr;
	analysisSkeleton::mu_L1_pt = m_offPhys->mu_staco_L1_pt;
	analysisSkeleton::mu_L1_eta = m_offPhys->mu_staco_L1_eta;
	analysisSkeleton::mu_L1_phi = m_offPhys->mu_staco_L1_phi;
	analysisSkeleton::mu_L1_thrNumber = m_offPhys->mu_staco_L1_thrNumber;
	analysisSkeleton::mu_L1_RoINumber = m_offPhys->mu_staco_L1_RoINumber;
	analysisSkeleton::mu_L1_sectorAddress = m_offPhys->mu_staco_L1_sectorAddress;
	analysisSkeleton::mu_L1_firstCandidate = m_offPhys->mu_staco_L1_firstCandidate;
	analysisSkeleton::mu_L1_moreCandInRoI = m_offPhys->mu_staco_L1_moreCandInRoI;
	analysisSkeleton::mu_L1_moreCandInSector = m_offPhys->mu_staco_L1_moreCandInSector;
	analysisSkeleton::mu_L1_source = m_offPhys->mu_staco_L1_source;
	analysisSkeleton::mu_L1_hemisphere = m_offPhys->mu_staco_L1_hemisphere;
	analysisSkeleton::mu_L1_matched = m_offPhys->mu_staco_L1_matched;
}

void offlineAnalysis::setMuidVariables()
{
	// muon 
	analysisSkeleton::mu_n         = m_offPhys->mu_muid_n;
	analysisSkeleton::mu_m         = m_offPhys->mu_muid_m;
	analysisSkeleton::mu_px        = m_offPhys->mu_muid_px;
	analysisSkeleton::mu_py        = m_offPhys->mu_muid_py;
	analysisSkeleton::mu_pz        = m_offPhys->mu_muid_pz;
	analysisSkeleton::mu_E         = m_offPhys->mu_muid_E;
	analysisSkeleton::mu_eta       = m_offPhys->mu_muid_eta;
	analysisSkeleton::mu_phi       = m_offPhys->mu_muid_phi;
	analysisSkeleton::mu_pt        = m_offPhys->mu_muid_pt;
	analysisSkeleton::mu_charge    = m_offPhys->mu_muid_charge;
	analysisSkeleton::mu_allauthor = m_offPhys->mu_muid_allauthor;
	analysisSkeleton::mu_author    = m_offPhys->mu_muid_author;
	analysisSkeleton::mu_matchchi2 = m_offPhys->mu_muid_matchchi2;
	analysisSkeleton::mu_matchndof = m_offPhys->mu_muid_matchndof;
	
	// isolation
	analysisSkeleton::mu_ptcone20 = m_offPhys->mu_muid_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_offPhys->mu_muid_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_offPhys->mu_muid_ptcone40;
	
	// for pT
	analysisSkeleton::mu_me_qoverp = m_offPhys->mu_muid_me_qoverp;
	analysisSkeleton::mu_id_qoverp = m_offPhys->mu_muid_id_qoverp;
	analysisSkeleton::mu_me_theta  = m_offPhys->mu_muid_me_theta;
	analysisSkeleton::mu_id_theta  = m_offPhys->mu_muid_id_theta;
	
	// for impact parameter
	analysisSkeleton::mu_d0_exPV = m_offPhys->mu_muid_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_offPhys->mu_muid_z0_exPV;
	
	// combined muons
	analysisSkeleton::mu_isCombinedMuon  = m_offPhys->mu_muid_isCombinedMuon;
	
	// inner detector hits
	analysisSkeleton::mu_nSCTHits  = m_offPhys->mu_muid_nSCTHits;
	analysisSkeleton::mu_nPixHits  = m_offPhys->mu_muid_nPixHits; 

	// muon spectrometer hits
	analysisSkeleton::mu_nMDTBIHits = m_offPhys->mu_muid_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_offPhys->mu_muid_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_offPhys->mu_muid_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_offPhys->mu_muid_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_offPhys->mu_muid_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_offPhys->mu_muid_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_offPhys->mu_muid_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_offPhys->mu_muid_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_offPhys->mu_muid_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_offPhys->mu_muid_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_offPhys->mu_muid_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_offPhys->mu_muid_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_offPhys->mu_muid_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_offPhys->mu_muid_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_offPhys->mu_muid_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_offPhys->mu_muid_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_offPhys->mu_muid_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_offPhys->mu_muid_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_offPhys->mu_muid_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_offPhys->mu_muid_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_offPhys->mu_muid_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_offPhys->mu_muid_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_offPhys->mu_muid_nTGCLayer4PhiHits;
	
	analysisSkeleton::mu_etcone20 = m_offPhys->mu_muid_etcone20;
	analysisSkeleton::mu_etcone30 = m_offPhys->mu_muid_etcone30;
	analysisSkeleton::mu_etcone40 = m_offPhys->mu_muid_etcone40;
	analysisSkeleton::mu_nucone20 = m_offPhys->mu_muid_nucone20;
	analysisSkeleton::mu_nucone30 = m_offPhys->mu_muid_nucone30;
	analysisSkeleton::mu_nucone40 = m_offPhys->mu_muid_nucone40;
	analysisSkeleton::mu_energyLossPar = m_offPhys->mu_muid_energyLossPar;
	analysisSkeleton::mu_energyLossErr = m_offPhys->mu_muid_energyLossErr;
	analysisSkeleton::mu_bestMatch = m_offPhys->mu_muid_bestMatch;
	analysisSkeleton::mu_isStandAloneMuon = m_offPhys->mu_muid_isStandAloneMuon;
	analysisSkeleton::mu_isLowPtReconstructedMuon = m_offPhys->mu_muid_isLowPtReconstructedMuon;
	analysisSkeleton::mu_loose = m_offPhys->mu_muid_loose;
	analysisSkeleton::mu_medium = m_offPhys->mu_muid_medium;
	analysisSkeleton::mu_tight = m_offPhys->mu_muid_tight;
	analysisSkeleton::mu_phi_exPV = m_offPhys->mu_muid_phi_exPV;
	analysisSkeleton::mu_theta_exPV = m_offPhys->mu_muid_theta_exPV;
	analysisSkeleton::mu_qoverp_exPV = m_offPhys->mu_muid_qoverp_exPV;
	analysisSkeleton::mu_cov_d0_exPV = m_offPhys->mu_muid_cov_d0_exPV;
	analysisSkeleton::mu_cov_z0_exPV = m_offPhys->mu_muid_cov_z0_exPV;
	analysisSkeleton::mu_cov_phi_exPV = m_offPhys->mu_muid_cov_phi_exPV;
	analysisSkeleton::mu_cov_theta_exPV = m_offPhys->mu_muid_cov_theta_exPV;
	analysisSkeleton::mu_cov_qoverp_exPV = m_offPhys->mu_muid_cov_qoverp_exPV;
	analysisSkeleton::mu_cov_d0_z0_exPV = m_offPhys->mu_muid_cov_d0_z0_exPV;
	analysisSkeleton::mu_cov_d0_phi_exPV = m_offPhys->mu_muid_cov_d0_phi_exPV;
	analysisSkeleton::mu_cov_d0_theta_exPV = m_offPhys->mu_muid_cov_d0_theta_exPV;
	analysisSkeleton::mu_cov_d0_qoverp_exPV = m_offPhys->mu_muid_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_cov_z0_phi_exPV = m_offPhys->mu_muid_cov_z0_phi_exPV;
	analysisSkeleton::mu_cov_z0_theta_exPV = m_offPhys->mu_muid_cov_z0_theta_exPV;
	analysisSkeleton::mu_cov_z0_qoverp_exPV = m_offPhys->mu_muid_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_cov_phi_theta_exPV = m_offPhys->mu_muid_cov_phi_theta_exPV;
	analysisSkeleton::mu_cov_phi_qoverp_exPV = m_offPhys->mu_muid_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_cov_theta_qoverp_exPV = m_offPhys->mu_muid_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_ms_d0 = m_offPhys->mu_muid_ms_d0;
	analysisSkeleton::mu_ms_z0 = m_offPhys->mu_muid_ms_z0;
	analysisSkeleton::mu_ms_phi = m_offPhys->mu_muid_ms_phi;
	analysisSkeleton::mu_ms_theta = m_offPhys->mu_muid_ms_theta;
	analysisSkeleton::mu_ms_qoverp = m_offPhys->mu_muid_ms_qoverp;
	analysisSkeleton::mu_id_d0 = m_offPhys->mu_muid_id_d0;
	analysisSkeleton::mu_id_z0 = m_offPhys->mu_muid_id_z0;
	analysisSkeleton::mu_id_phi = m_offPhys->mu_muid_id_phi;
	analysisSkeleton::mu_me_d0 = m_offPhys->mu_muid_me_d0;
	analysisSkeleton::mu_me_z0 = m_offPhys->mu_muid_me_z0;
	analysisSkeleton::mu_me_phi = m_offPhys->mu_muid_me_phi;
	analysisSkeleton::mu_ie_d0 = m_offPhys->mu_muid_ie_d0;
	analysisSkeleton::mu_ie_z0 = m_offPhys->mu_muid_ie_z0;
	analysisSkeleton::mu_ie_phi = m_offPhys->mu_muid_ie_phi;
	analysisSkeleton::mu_ie_theta = m_offPhys->mu_muid_ie_theta;
	analysisSkeleton::mu_ie_qoverp = m_offPhys->mu_muid_ie_qoverp;
	analysisSkeleton::mu_nBLHits = m_offPhys->mu_muid_nBLHits;
	analysisSkeleton::mu_nTRTHighTHits = m_offPhys->mu_muid_nTRTHighTHits;
	analysisSkeleton::mu_nBLSharedHits = m_offPhys->mu_muid_nBLSharedHits;
	analysisSkeleton::mu_nPixSharedHits = m_offPhys->mu_muid_nPixSharedHits;
	analysisSkeleton::mu_nPixHoles = m_offPhys->mu_muid_nPixHoles;
	analysisSkeleton::mu_nSCTSharedHits = m_offPhys->mu_muid_nSCTSharedHits;
	analysisSkeleton::mu_nSCTHoles = m_offPhys->mu_muid_nSCTHoles;
	analysisSkeleton::mu_nTRTOutliers = m_offPhys->mu_muid_nTRTOutliers;
	analysisSkeleton::mu_nTRTHighTOutliers = m_offPhys->mu_muid_nTRTHighTOutliers;
	analysisSkeleton::mu_nMDTHits = m_offPhys->mu_muid_nMDTHits;
	analysisSkeleton::mu_nMDTHoles = m_offPhys->mu_muid_nMDTHoles;
	analysisSkeleton::mu_nCSCEtaHits = m_offPhys->mu_muid_nCSCEtaHits;
	analysisSkeleton::mu_nCSCEtaHoles = m_offPhys->mu_muid_nCSCEtaHoles;
	analysisSkeleton::mu_nCSCPhiHits = m_offPhys->mu_muid_nCSCPhiHits;
	analysisSkeleton::mu_nCSCPhiHoles = m_offPhys->mu_muid_nCSCPhiHoles;
	analysisSkeleton::mu_nRPCEtaHits = m_offPhys->mu_muid_nRPCEtaHits;
	analysisSkeleton::mu_nRPCEtaHoles = m_offPhys->mu_muid_nRPCEtaHoles;
	analysisSkeleton::mu_nRPCPhiHits = m_offPhys->mu_muid_nRPCPhiHits;
	analysisSkeleton::mu_nRPCPhiHoles = m_offPhys->mu_muid_nRPCPhiHoles;
	analysisSkeleton::mu_nTGCEtaHits = m_offPhys->mu_muid_nTGCEtaHits;
	analysisSkeleton::mu_nTGCEtaHoles = m_offPhys->mu_muid_nTGCEtaHoles;
	analysisSkeleton::mu_nTGCPhiHits = m_offPhys->mu_muid_nTGCPhiHits;
	analysisSkeleton::mu_nTGCPhiHoles = m_offPhys->mu_muid_nTGCPhiHoles;
	analysisSkeleton::mu_nGangedPixels = m_offPhys->mu_muid_nGangedPixels;
	analysisSkeleton::mu_nOutliersOnTrack = m_offPhys->mu_muid_nOutliersOnTrack;
	analysisSkeleton::mu_barrelSectors = m_offPhys->mu_muid_barrelSectors;
	analysisSkeleton::mu_endcapSectors = m_offPhys->mu_muid_endcapSectors;
	analysisSkeleton::mu_trackd0 = m_offPhys->mu_muid_trackd0;
	analysisSkeleton::mu_trackz0 = m_offPhys->mu_muid_trackz0;
	analysisSkeleton::mu_trackphi = m_offPhys->mu_muid_trackphi;
	analysisSkeleton::mu_tracktheta = m_offPhys->mu_muid_tracktheta;
	analysisSkeleton::mu_trackqoverp = m_offPhys->mu_muid_trackqoverp;
	analysisSkeleton::mu_trackcov_d0 = m_offPhys->mu_muid_trackcov_d0;
	analysisSkeleton::mu_trackcov_z0 = m_offPhys->mu_muid_trackcov_z0;
	analysisSkeleton::mu_trackcov_phi = m_offPhys->mu_muid_trackcov_phi;
	analysisSkeleton::mu_trackcov_theta = m_offPhys->mu_muid_trackcov_theta;
	analysisSkeleton::mu_trackcov_qoverp = m_offPhys->mu_muid_trackcov_qoverp;
	analysisSkeleton::mu_trackcov_d0_z0 = m_offPhys->mu_muid_trackcov_d0_z0;
	analysisSkeleton::mu_trackcov_d0_phi = m_offPhys->mu_muid_trackcov_d0_phi;
	analysisSkeleton::mu_trackcov_d0_theta = m_offPhys->mu_muid_trackcov_d0_theta;
	analysisSkeleton::mu_trackcov_d0_qoverp = m_offPhys->mu_muid_trackcov_d0_qoverp;
	analysisSkeleton::mu_trackcov_z0_phi = m_offPhys->mu_muid_trackcov_z0_phi;
	analysisSkeleton::mu_trackcov_z0_theta = m_offPhys->mu_muid_trackcov_z0_theta;
	analysisSkeleton::mu_trackcov_z0_qoverp = m_offPhys->mu_muid_trackcov_z0_qoverp;
	analysisSkeleton::mu_trackcov_phi_theta = m_offPhys->mu_muid_trackcov_phi_theta;
	analysisSkeleton::mu_trackcov_phi_qoverp = m_offPhys->mu_muid_trackcov_phi_qoverp;
	analysisSkeleton::mu_trackcov_theta_qoverp = m_offPhys->mu_muid_trackcov_theta_qoverp;
	analysisSkeleton::mu_trackfitchi2 = m_offPhys->mu_muid_trackfitchi2;
	analysisSkeleton::mu_trackfitndof = m_offPhys->mu_muid_trackfitndof;
	analysisSkeleton::mu_hastrack = m_offPhys->mu_muid_hastrack;
	analysisSkeleton::mu_EF_dr = m_offPhys->mu_muid_EF_dr;
	analysisSkeleton::mu_EF_cb_eta = m_offPhys->mu_muid_EF_cb_eta;
	analysisSkeleton::mu_EF_cb_phi = m_offPhys->mu_muid_EF_cb_phi;
	analysisSkeleton::mu_EF_cb_pt = m_offPhys->mu_muid_EF_cb_pt;
	analysisSkeleton::mu_EF_ms_eta = m_offPhys->mu_muid_EF_ms_eta;
	analysisSkeleton::mu_EF_ms_phi = m_offPhys->mu_muid_EF_ms_phi;
	analysisSkeleton::mu_EF_ms_pt = m_offPhys->mu_muid_EF_ms_pt;
	analysisSkeleton::mu_EF_me_eta = m_offPhys->mu_muid_EF_me_eta;
	analysisSkeleton::mu_EF_me_phi = m_offPhys->mu_muid_EF_me_phi;
	analysisSkeleton::mu_EF_me_pt = m_offPhys->mu_muid_EF_me_pt;
	analysisSkeleton::mu_EF_matched = m_offPhys->mu_muid_EF_matched;
	analysisSkeleton::mu_L2CB_dr = m_offPhys->mu_muid_L2CB_dr;
	analysisSkeleton::mu_L2CB_pt = m_offPhys->mu_muid_L2CB_pt;
	analysisSkeleton::mu_L2CB_eta = m_offPhys->mu_muid_L2CB_eta;
	analysisSkeleton::mu_L2CB_phi = m_offPhys->mu_muid_L2CB_phi;
	analysisSkeleton::mu_L2CB_id_pt = m_offPhys->mu_muid_L2CB_id_pt;
	analysisSkeleton::mu_L2CB_ms_pt = m_offPhys->mu_muid_L2CB_ms_pt;
	analysisSkeleton::mu_L2CB_nPixHits = m_offPhys->mu_muid_L2CB_nPixHits;
	analysisSkeleton::mu_L2CB_nSCTHits = m_offPhys->mu_muid_L2CB_nSCTHits;
	analysisSkeleton::mu_L2CB_nTRTHits = m_offPhys->mu_muid_L2CB_nTRTHits;
	analysisSkeleton::mu_L2CB_nTRTHighTHits = m_offPhys->mu_muid_L2CB_nTRTHighTHits;
	analysisSkeleton::mu_L2CB_matched = m_offPhys->mu_muid_L2CB_matched;
	analysisSkeleton::mu_L1_dr = m_offPhys->mu_muid_L1_dr;
	analysisSkeleton::mu_L1_pt = m_offPhys->mu_muid_L1_pt;
	analysisSkeleton::mu_L1_eta = m_offPhys->mu_muid_L1_eta;
	analysisSkeleton::mu_L1_phi = m_offPhys->mu_muid_L1_phi;
	analysisSkeleton::mu_L1_thrNumber = m_offPhys->mu_muid_L1_thrNumber;
	analysisSkeleton::mu_L1_RoINumber = m_offPhys->mu_muid_L1_RoINumber;
	analysisSkeleton::mu_L1_sectorAddress = m_offPhys->mu_muid_L1_sectorAddress;
	analysisSkeleton::mu_L1_firstCandidate = m_offPhys->mu_muid_L1_firstCandidate;
	analysisSkeleton::mu_L1_moreCandInRoI = m_offPhys->mu_muid_L1_moreCandInRoI;
	analysisSkeleton::mu_L1_moreCandInSector = m_offPhys->mu_muid_L1_moreCandInSector;
	analysisSkeleton::mu_L1_source = m_offPhys->mu_muid_L1_source;
	analysisSkeleton::mu_L1_hemisphere = m_offPhys->mu_muid_L1_hemisphere;
	analysisSkeleton::mu_L1_matched = m_offPhys->mu_muid_L1_matched;
}


void offlineAnalysis::write()
{
	m_muSkimD3PD->write();
}

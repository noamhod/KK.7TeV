/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcOfflineAnalysis.h"

mcOfflineAnalysis::mcOfflineAnalysis()
{
	
}

mcOfflineAnalysis::~mcOfflineAnalysis()
{

}


void mcOfflineAnalysis::executeAdvanced()
{

/*
	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_mcOffPhys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mustaco->getNParticles() ; n++)
		{
			m_mustaco->setParticle(n);
			m_graphicobjs->h2_xyVertex->Fill( m_mustaco->pvVec->X(), m_mustaco->pvVec->Y() );
		}
	}
*/
}

void mcOfflineAnalysis::executeCutFlow()
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
		nMus = (int)m_mcOffPhys->mu_staco_pt->size();
	}
	if(sMuonRecoAlgo=="muid")
	{
		setMuidVariables();
		nMus = (int)m_mcOffPhys->mu_muid_pt->size();
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
	
	////////////////////////////////////////////////////////////
	// write to the digest tree only the pairs that pass skim //
	bool passSkim = digestSkim(nMus); //////////////////////////
	if( passSkim )
	{
		m_muSkimMCD3PD->fillMC(); // this does *not* call TTree::Fill()
		m_muSkimD3PD->fill(analysisSkeleton::isGRL);
		m_muSkimMCD3PD->resetVectorPtrsMC(); // in muSkimD3PD this is done internally
											 // but in muSkimMCD3PD this has to be
											 // done externally, i.e. here since
											 // the tree is being filled in the
											 // muSkimD3PD class.
	}
	////////////////////////////////////////////////////////////

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

void mcOfflineAnalysis::setEventVariables()
{
	// event level (for preselection)
	analysisSkeleton::RunNumber    = m_mcOffPhys->RunNumber;
	analysisSkeleton::EventNumber  = m_mcOffPhys->EventNumber;
	analysisSkeleton::timestamp    = m_mcOffPhys->timestamp;
	analysisSkeleton::timestamp_ns = m_mcOffPhys->timestamp_ns;
	analysisSkeleton::lbn          = m_mcOffPhys->lbn;
	analysisSkeleton::bcid         = m_mcOffPhys->bcid;
	analysisSkeleton::detmask0     = m_mcOffPhys->detmask0;
	analysisSkeleton::detmask1     = m_mcOffPhys->detmask1;
	analysisSkeleton::pixelFlags   = m_mcOffPhys->pixelFlags;
	analysisSkeleton::sctFlags     = m_mcOffPhys->sctFlags;
	analysisSkeleton::trtFlags     = m_mcOffPhys->trtFlags;
	analysisSkeleton::larFlags     = m_mcOffPhys->larFlags;
	analysisSkeleton::tileFlags    = m_mcOffPhys->tileFlags;
	analysisSkeleton::muonFlags    = m_mcOffPhys->muonFlags;
	analysisSkeleton::fwdFlags     = m_mcOffPhys->fwdFlags;
	analysisSkeleton::coreFlags    = m_mcOffPhys->coreFlags;
	analysisSkeleton::pixelError   = m_mcOffPhys->pixelError;
	analysisSkeleton::sctError     = m_mcOffPhys->sctError;
	analysisSkeleton::trtError     = m_mcOffPhys->trtError;
	analysisSkeleton::larError     = m_mcOffPhys->larError;
	analysisSkeleton::tileError    = m_mcOffPhys->tileError;
	analysisSkeleton::muonError    = m_mcOffPhys->muonError;
	analysisSkeleton::fwdError     = m_mcOffPhys->fwdError;
	analysisSkeleton::coreError    = m_mcOffPhys->coreError;
	//analysisSkeleton::lar_ncellA   = m_mcOffPhys->lar_ncellA;
	//analysisSkeleton::lar_ncellC   = m_mcOffPhys->lar_ncellC;
	//analysisSkeleton::lar_energyA  = m_mcOffPhys->lar_energyA;
	//analysisSkeleton::lar_energyC  = m_mcOffPhys->lar_energyC;
	//analysisSkeleton::lar_timeA    = m_mcOffPhys->lar_timeA;
	//analysisSkeleton::lar_timeC    = m_mcOffPhys->lar_timeC;
	//analysisSkeleton::lar_timeDiff = m_mcOffPhys->lar_timeDiff;
	
	analysisSkeleton::isGRL       = 1;
	
	//////////////////////////////////////////////////////
	// do this only if the run number has changed ////////
	analysisSkeleton::sPeriod = getPeriodName(); /////////
	analysisSkeleton::vTriggers = getPeriodTriggers(); ///
	//////////////////////////////////////////////////////
	//analysisSkeleton::sPeriod     = m_mcOffPhys->period;
	//analysisSkeleton::vTriggers   = m_mcOffPhys->vTriggers;
	
	// L1 triggers
	analysisSkeleton::isL1_MU0  = m_mcOffPhys->L1_MU0;
	analysisSkeleton::isL1_MU10 = m_mcOffPhys->L1_MU10;
	analysisSkeleton::isL1_MU15 = m_mcOffPhys->L1_MU15;
	analysisSkeleton::isL1_MU20 = m_mcOffPhys->L1_MU20;
	analysisSkeleton::isL1_MU6  = m_mcOffPhys->L1_MU6;
	
	// NOTE !!! THESE BRANCHES ARE DISABLED ALSO IN THE "offTree" CLASS
	// EF triggers
	analysisSkeleton::isEF_mu10 = m_mcOffPhys->EF_mu10;
	analysisSkeleton::isEF_mu10_MG = m_mcOffPhys->EF_mu10_MG;
	analysisSkeleton::isEF_mu10_MSonly = m_mcOffPhys->EF_mu10_MSonly;
	analysisSkeleton::isEF_mu10_MSonly_tight = m_mcOffPhys->EF_mu10_MSonly_tight;
	analysisSkeleton::isEF_mu10_NoAlg = m_mcOffPhys->EF_mu10_NoAlg;
	analysisSkeleton::isEF_mu10_tight = m_mcOffPhys->EF_mu10_tight;
	analysisSkeleton::isEF_mu10i_loose = m_mcOffPhys->EF_mu10i_loose;
	analysisSkeleton::isEF_mu13 = m_mcOffPhys->EF_mu13;
	analysisSkeleton::isEF_mu13_MG = m_mcOffPhys->EF_mu13_MG;
	analysisSkeleton::isEF_mu13_MG_tight = m_mcOffPhys->EF_mu13_MG_tight;
	analysisSkeleton::isEF_mu13_tight = m_mcOffPhys->EF_mu13_tight;
	analysisSkeleton::isEF_mu15 = m_mcOffPhys->EF_mu15;
	analysisSkeleton::isEF_mu15_NoAlg = m_mcOffPhys->EF_mu15_NoAlg;
	analysisSkeleton::isEF_mu20 = m_mcOffPhys->EF_mu20;
	analysisSkeleton::isEF_mu20_MSonly = m_mcOffPhys->EF_mu20_MSonly;
	analysisSkeleton::isEF_mu20_NoAlg = m_mcOffPhys->EF_mu20_NoAlg;
	analysisSkeleton::isEF_mu20_slow = m_mcOffPhys->EF_mu20_slow;
	analysisSkeleton::isEF_mu30_MSonly = m_mcOffPhys->EF_mu30_MSonly;
	analysisSkeleton::isEF_mu4 = m_mcOffPhys->EF_mu4;
	analysisSkeleton::isEF_mu40_MSonly = m_mcOffPhys->EF_mu40_MSonly;
	
	// vertexes (for the PV preselection)
	analysisSkeleton::vxp_n       = m_mcOffPhys->vxp_n;
	analysisSkeleton::vxp_nTracks = m_mcOffPhys->vxp_nTracks;
	analysisSkeleton::vxp_type    = m_mcOffPhys->vxp_type;
	analysisSkeleton::vxp_z       = m_mcOffPhys->vxp_z;
}

void mcOfflineAnalysis::setStacoVariables()
{
	// muon 
	analysisSkeleton::mu_n         = m_mcOffPhys->mu_staco_n;
	analysisSkeleton::mu_m         = m_mcOffPhys->mu_staco_m;
	analysisSkeleton::mu_px        = m_mcOffPhys->mu_staco_px;
	analysisSkeleton::mu_py        = m_mcOffPhys->mu_staco_py;
	analysisSkeleton::mu_pz        = m_mcOffPhys->mu_staco_pz;
	analysisSkeleton::mu_E         = m_mcOffPhys->mu_staco_E;
	analysisSkeleton::mu_eta       = m_mcOffPhys->mu_staco_eta;
	analysisSkeleton::mu_phi       = m_mcOffPhys->mu_staco_phi;
	analysisSkeleton::mu_pt        = m_mcOffPhys->mu_staco_pt;
	analysisSkeleton::mu_charge    = m_mcOffPhys->mu_staco_charge;
	
	// isolation
	analysisSkeleton::mu_ptcone20 = m_mcOffPhys->mu_staco_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_mcOffPhys->mu_staco_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_mcOffPhys->mu_staco_ptcone40;
	
	// for pT
	analysisSkeleton::mu_me_qoverp = m_mcOffPhys->mu_staco_me_qoverp;
	analysisSkeleton::mu_id_qoverp = m_mcOffPhys->mu_staco_id_qoverp;
	analysisSkeleton::mu_me_theta  = m_mcOffPhys->mu_staco_me_theta;
	analysisSkeleton::mu_id_theta  = m_mcOffPhys->mu_staco_id_theta;
	
	// for impact parameter
	analysisSkeleton::mu_d0_exPV = m_mcOffPhys->mu_staco_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_mcOffPhys->mu_staco_z0_exPV;
	
	// combined muons
	analysisSkeleton::mu_isCombinedMuon  = m_mcOffPhys->mu_staco_isCombinedMuon;
	
	// inner detector hits
	analysisSkeleton::mu_nSCTHits  = m_mcOffPhys->mu_staco_nSCTHits;
	analysisSkeleton::mu_nPixHits  = m_mcOffPhys->mu_staco_nPixHits; 

	// muon spectrometer hits
	analysisSkeleton::mu_nMDTBIHits = m_mcOffPhys->mu_staco_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_mcOffPhys->mu_staco_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_mcOffPhys->mu_staco_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_mcOffPhys->mu_staco_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_mcOffPhys->mu_staco_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_mcOffPhys->mu_staco_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_mcOffPhys->mu_staco_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_mcOffPhys->mu_staco_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_mcOffPhys->mu_staco_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_mcOffPhys->mu_staco_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_mcOffPhys->mu_staco_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_mcOffPhys->mu_staco_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_mcOffPhys->mu_staco_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_mcOffPhys->mu_staco_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_mcOffPhys->mu_staco_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_mcOffPhys->mu_staco_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_mcOffPhys->mu_staco_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_mcOffPhys->mu_staco_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_mcOffPhys->mu_staco_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_mcOffPhys->mu_staco_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_mcOffPhys->mu_staco_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_mcOffPhys->mu_staco_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_mcOffPhys->mu_staco_nTGCLayer4PhiHits;
}

void mcOfflineAnalysis::setMuidVariables()
{
	// muon 
	analysisSkeleton::mu_n         = m_mcOffPhys->mu_muid_n;
	analysisSkeleton::mu_m         = m_mcOffPhys->mu_muid_m;
	analysisSkeleton::mu_px        = m_mcOffPhys->mu_muid_px;
	analysisSkeleton::mu_py        = m_mcOffPhys->mu_muid_py;
	analysisSkeleton::mu_pz        = m_mcOffPhys->mu_muid_pz;
	analysisSkeleton::mu_E         = m_mcOffPhys->mu_muid_E;
	analysisSkeleton::mu_eta       = m_mcOffPhys->mu_muid_eta;
	analysisSkeleton::mu_phi       = m_mcOffPhys->mu_muid_phi;
	analysisSkeleton::mu_pt        = m_mcOffPhys->mu_muid_pt;
	analysisSkeleton::mu_charge    = m_mcOffPhys->mu_muid_charge;
	
	// isolation
	analysisSkeleton::mu_ptcone20 = m_mcOffPhys->mu_muid_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_mcOffPhys->mu_muid_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_mcOffPhys->mu_muid_ptcone40;
	
	// for pT
	analysisSkeleton::mu_me_qoverp = m_mcOffPhys->mu_muid_me_qoverp;
	analysisSkeleton::mu_id_qoverp = m_mcOffPhys->mu_muid_id_qoverp;
	analysisSkeleton::mu_me_theta  = m_mcOffPhys->mu_muid_me_theta;
	analysisSkeleton::mu_id_theta  = m_mcOffPhys->mu_muid_id_theta;
	
	// for impact parameter
	analysisSkeleton::mu_d0_exPV = m_mcOffPhys->mu_muid_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_mcOffPhys->mu_muid_z0_exPV;
	
	// combined muons
	analysisSkeleton::mu_isCombinedMuon  = m_mcOffPhys->mu_muid_isCombinedMuon;
	
	// inner detector hits
	analysisSkeleton::mu_nSCTHits  = m_mcOffPhys->mu_muid_nSCTHits;
	analysisSkeleton::mu_nPixHits  = m_mcOffPhys->mu_muid_nPixHits; 

	// muon spectrometer hits
	analysisSkeleton::mu_nMDTBIHits = m_mcOffPhys->mu_muid_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_mcOffPhys->mu_muid_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_mcOffPhys->mu_muid_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_mcOffPhys->mu_muid_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_mcOffPhys->mu_muid_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_mcOffPhys->mu_muid_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_mcOffPhys->mu_muid_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_mcOffPhys->mu_muid_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_mcOffPhys->mu_muid_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_mcOffPhys->mu_muid_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_mcOffPhys->mu_muid_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_mcOffPhys->mu_muid_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_mcOffPhys->mu_muid_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_mcOffPhys->mu_muid_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_mcOffPhys->mu_muid_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_mcOffPhys->mu_muid_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_mcOffPhys->mu_muid_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_mcOffPhys->mu_muid_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_mcOffPhys->mu_muid_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_mcOffPhys->mu_muid_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_mcOffPhys->mu_muid_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_mcOffPhys->mu_muid_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_mcOffPhys->mu_muid_nTGCLayer4PhiHits;
}

void mcOfflineAnalysis::write()
{
	m_treeFile->cd();
	m_muSkimD3PD->write();
}

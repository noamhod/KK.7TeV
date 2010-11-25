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
	candidatesFile->close();
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
		nMus = (int)m_digestPhys->mu_staco_pt->size();
	}
	if(sMuonRecoAlgo=="muid")
	{
		setMuidVariables();
		nMus = (int)m_digestPhys->mu_muid_pt->size();
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
	
	
	(*candidatesFile) << "Staco run " << analysisSkeleton::RunNumber
					  << " lb " 	  << analysisSkeleton::lbn
					  << " event " 	  << analysisSkeleton::EventNumber
					  << endl;
}

void digestAnalysis::setEventVariables()
{
	// event level (for preselection)
	analysisSkeleton::RunNumber    = m_digestPhys->RunNumber;
	analysisSkeleton::EventNumber  = m_digestPhys->EventNumber;
	analysisSkeleton::timestamp    = m_digestPhys->timestamp;
	analysisSkeleton::timestamp_ns = m_digestPhys->timestamp_ns;
	analysisSkeleton::lbn          = m_digestPhys->lbn;
	analysisSkeleton::bcid         = m_digestPhys->bcid;
	analysisSkeleton::detmask0     = m_digestPhys->detmask0;
	analysisSkeleton::detmask1     = m_digestPhys->detmask1;
	analysisSkeleton::pixelFlags   = m_digestPhys->pixelFlags;
	analysisSkeleton::sctFlags     = m_digestPhys->sctFlags;
	analysisSkeleton::trtFlags     = m_digestPhys->trtFlags;
	analysisSkeleton::larFlags     = m_digestPhys->larFlags;
	analysisSkeleton::tileFlags    = m_digestPhys->tileFlags;
	analysisSkeleton::muonFlags    = m_digestPhys->muonFlags;
	analysisSkeleton::fwdFlags     = m_digestPhys->fwdFlags;
	analysisSkeleton::coreFlags    = m_digestPhys->coreFlags;
	analysisSkeleton::pixelError   = m_digestPhys->pixelError;
	analysisSkeleton::sctError     = m_digestPhys->sctError;
	analysisSkeleton::trtError     = m_digestPhys->trtError;
	analysisSkeleton::larError     = m_digestPhys->larError;
	analysisSkeleton::tileError    = m_digestPhys->tileError;
	analysisSkeleton::muonError    = m_digestPhys->muonError;
	analysisSkeleton::fwdError     = m_digestPhys->fwdError;
	analysisSkeleton::coreError    = m_digestPhys->coreError;
	analysisSkeleton::lar_ncellA   = m_digestPhys->lar_ncellA;
	analysisSkeleton::lar_ncellC   = m_digestPhys->lar_ncellC;
	analysisSkeleton::lar_energyA  = m_digestPhys->lar_energyA;
	analysisSkeleton::lar_energyC  = m_digestPhys->lar_energyC;
	analysisSkeleton::lar_timeA    = m_digestPhys->lar_timeA;
	analysisSkeleton::lar_timeC    = m_digestPhys->lar_timeC;
	analysisSkeleton::lar_timeDiff = m_digestPhys->lar_timeDiff;
	
	
	analysisSkeleton::isGRL       = m_digestAnalysis_grl->m_grl.HasRunLumiBlock( analysisSkeleton::runnumber, analysisSkeleton::lumiblock );
	//analysisSkeleton::isGRL     = m_digestPhys->isGRL;

	//////////////////////////////////////////////////////
	// do this only if the run number has changed ////////
	analysisSkeleton::sPeriod = getPeriodName(); /////////
	analysisSkeleton::vTriggers = getPeriodTriggers(); ///
	//////////////////////////////////////////////////////
	//analysisSkeleton::sPeriod     = m_digestPhys->period;
	//analysisSkeleton::vTriggers   = m_digestPhys->vTriggers;
	
	// L1 triggers
	analysisSkeleton::isL1_MU0  = m_digestPhys->L1_MU0;
	analysisSkeleton::isL1_MU10 = m_digestPhys->L1_MU10;
	analysisSkeleton::isL1_MU15 = m_digestPhys->L1_MU15;
	analysisSkeleton::isL1_MU20 = m_digestPhys->L1_MU20;
	analysisSkeleton::isL1_MU6  = m_digestPhys->L1_MU6;
	
	// NOTE !!! THESE BRANCHES ARE DISABLED ALSO IN THE "offTree" CLASS
	// EF triggers
	analysisSkeleton::isEF_mu10 = m_digestPhys->EF_mu10;
	analysisSkeleton::isEF_mu10_MG = m_digestPhys->EF_mu10_MG;
	analysisSkeleton::isEF_mu10_MSonly = m_digestPhys->EF_mu10_MSonly;
	analysisSkeleton::isEF_mu10_MSonly_tight = m_digestPhys->EF_mu10_MSonly_tight;
	analysisSkeleton::isEF_mu10_NoAlg = m_digestPhys->EF_mu10_NoAlg;
	analysisSkeleton::isEF_mu10_tight = m_digestPhys->EF_mu10_tight;
	analysisSkeleton::isEF_mu10i_loose = m_digestPhys->EF_mu10i_loose;
	analysisSkeleton::isEF_mu13 = m_digestPhys->EF_mu13;
	analysisSkeleton::isEF_mu13_MG = m_digestPhys->EF_mu13_MG;
	analysisSkeleton::isEF_mu13_MG_tight = m_digestPhys->EF_mu13_MG_tight;
	analysisSkeleton::isEF_mu13_tight = m_digestPhys->EF_mu13_tight;
	analysisSkeleton::isEF_mu15 = m_digestPhys->EF_mu15;
	analysisSkeleton::isEF_mu15_NoAlg = m_digestPhys->EF_mu15_NoAlg;
	analysisSkeleton::isEF_mu20 = m_digestPhys->EF_mu20;
	analysisSkeleton::isEF_mu20_MSonly = m_digestPhys->EF_mu20_MSonly;
	analysisSkeleton::isEF_mu20_NoAlg = m_digestPhys->EF_mu20_NoAlg;
	analysisSkeleton::isEF_mu20_slow = m_digestPhys->EF_mu20_slow;
	analysisSkeleton::isEF_mu30_MSonly = m_digestPhys->EF_mu30_MSonly;
	analysisSkeleton::isEF_mu4 = m_digestPhys->EF_mu4;
	analysisSkeleton::isEF_mu40_MSonly = m_digestPhys->EF_mu40_MSonly;
	
	// vertexes (for the PV preselection)
	analysisSkeleton::vxp_n       = m_digestPhys->vxp_n;
	analysisSkeleton::vxp_nTracks = m_digestPhys->vxp_nTracks;
	analysisSkeleton::vxp_type    = m_digestPhys->vxp_type;
	analysisSkeleton::vxp_z       = m_digestPhys->vxp_z;
}

void digestAnalysis::setStacoVariables()
{
	// muon 
	analysisSkeleton::mu_n         = m_digestPhys->mu_staco_n;
	analysisSkeleton::mu_m         = m_digestPhys->mu_staco_m;
	analysisSkeleton::mu_px        = m_digestPhys->mu_staco_px;
	analysisSkeleton::mu_py        = m_digestPhys->mu_staco_py;
	analysisSkeleton::mu_pz        = m_digestPhys->mu_staco_pz;
	analysisSkeleton::mu_E         = m_digestPhys->mu_staco_E;
	analysisSkeleton::mu_eta       = m_digestPhys->mu_staco_eta;
	analysisSkeleton::mu_phi       = m_digestPhys->mu_staco_phi;
	analysisSkeleton::mu_pt        = m_digestPhys->mu_staco_pt;
	analysisSkeleton::mu_charge    = m_digestPhys->mu_staco_charge;
	
	// isolation
	analysisSkeleton::mu_ptcone20 = m_digestPhys->mu_staco_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_digestPhys->mu_staco_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_digestPhys->mu_staco_ptcone40;
	
	// for pT
	analysisSkeleton::mu_me_qoverp = m_digestPhys->mu_staco_me_qoverp;
	analysisSkeleton::mu_id_qoverp = m_digestPhys->mu_staco_id_qoverp;
	analysisSkeleton::mu_me_theta  = m_digestPhys->mu_staco_me_theta;
	analysisSkeleton::mu_id_theta  = m_digestPhys->mu_staco_id_theta;
	
	// for impact parameter
	analysisSkeleton::mu_d0_exPV = m_digestPhys->mu_staco_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_digestPhys->mu_staco_z0_exPV;
	
	// combined muons
	analysisSkeleton::mu_isCombinedMuon  = m_digestPhys->mu_staco_isCombinedMuon;
	
	// inner detector hits
	analysisSkeleton::mu_nSCTHits  = m_digestPhys->mu_staco_nSCTHits;
	analysisSkeleton::mu_nPixHits  = m_digestPhys->mu_staco_nPixHits; 

	// muon spectrometer hits
	analysisSkeleton::mu_nMDTBIHits = m_digestPhys->mu_staco_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_digestPhys->mu_staco_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_digestPhys->mu_staco_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_digestPhys->mu_staco_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_digestPhys->mu_staco_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_digestPhys->mu_staco_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_digestPhys->mu_staco_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_digestPhys->mu_staco_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_digestPhys->mu_staco_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_digestPhys->mu_staco_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_digestPhys->mu_staco_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_digestPhys->mu_staco_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_digestPhys->mu_staco_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_digestPhys->mu_staco_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_digestPhys->mu_staco_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_digestPhys->mu_staco_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_digestPhys->mu_staco_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_digestPhys->mu_staco_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_digestPhys->mu_staco_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_digestPhys->mu_staco_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_digestPhys->mu_staco_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_digestPhys->mu_staco_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_digestPhys->mu_staco_nTGCLayer4PhiHits;
}

void digestAnalysis::setMuidVariables()
{
	// muon 
	analysisSkeleton::mu_n         = m_digestPhys->mu_muid_n;
	analysisSkeleton::mu_m         = m_digestPhys->mu_muid_m;
	analysisSkeleton::mu_px        = m_digestPhys->mu_muid_px;
	analysisSkeleton::mu_py        = m_digestPhys->mu_muid_py;
	analysisSkeleton::mu_pz        = m_digestPhys->mu_muid_pz;
	analysisSkeleton::mu_E         = m_digestPhys->mu_muid_E;
	analysisSkeleton::mu_eta       = m_digestPhys->mu_muid_eta;
	analysisSkeleton::mu_phi       = m_digestPhys->mu_muid_phi;
	analysisSkeleton::mu_pt        = m_digestPhys->mu_muid_pt;
	analysisSkeleton::mu_charge    = m_digestPhys->mu_muid_charge;
	
	// isolation
	analysisSkeleton::mu_ptcone20 = m_digestPhys->mu_muid_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_digestPhys->mu_muid_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_digestPhys->mu_muid_ptcone40;
	
	// for pT
	analysisSkeleton::mu_me_qoverp = m_digestPhys->mu_muid_me_qoverp;
	analysisSkeleton::mu_id_qoverp = m_digestPhys->mu_muid_id_qoverp;
	analysisSkeleton::mu_me_theta  = m_digestPhys->mu_muid_me_theta;
	analysisSkeleton::mu_id_theta  = m_digestPhys->mu_muid_id_theta;
	
	// for impact parameter
	analysisSkeleton::mu_d0_exPV = m_digestPhys->mu_muid_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_digestPhys->mu_muid_z0_exPV;
	
	// combined muons
	analysisSkeleton::mu_isCombinedMuon  = m_digestPhys->mu_muid_isCombinedMuon;
	
	// inner detector hits
	analysisSkeleton::mu_nSCTHits  = m_digestPhys->mu_muid_nSCTHits;
	analysisSkeleton::mu_nPixHits  = m_digestPhys->mu_muid_nPixHits; 

	// muon spectrometer hits
	analysisSkeleton::mu_nMDTBIHits = m_digestPhys->mu_muid_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_digestPhys->mu_muid_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_digestPhys->mu_muid_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_digestPhys->mu_muid_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_digestPhys->mu_muid_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_digestPhys->mu_muid_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_digestPhys->mu_muid_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_digestPhys->mu_muid_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_digestPhys->mu_muid_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_digestPhys->mu_muid_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_digestPhys->mu_muid_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_digestPhys->mu_muid_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_digestPhys->mu_muid_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_digestPhys->mu_muid_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_digestPhys->mu_muid_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_digestPhys->mu_muid_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_digestPhys->mu_muid_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_digestPhys->mu_muid_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_digestPhys->mu_muid_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_digestPhys->mu_muid_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_digestPhys->mu_muid_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_digestPhys->mu_muid_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_digestPhys->mu_muid_nTGCLayer4PhiHits;
}

void digestAnalysis::write()
{
	//m_treeFile->cd();
	//m_offTreeDigest->write();
}

/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysis.h"

analysis::analysis()
{
	_DEBUG("analysis::analysis");
}

analysis::~analysis()
{
	fCandidates->close();
}

void analysis::setAllCandidatesFiles(string sCandFilePath, string srunnumber)
{

	string sLogFileName = sCandFilePath+"/candidates_all.run_"+srunnumber+".cnd";//".time_"+getDateHour()+".cnd";
	fCandidates = new ofstream( sLogFileName.c_str() );

}

void analysis::execute()
{
	_DEBUG("analysis::execute");
	
	////////////////////////////////////////////////
	//set all the graphicObjects trees branches ////
	clearTreeVars(); ///////////////////////////////
	////////////////////////////////////////////////
	
	///////////////////////////////////
	// set all the event-level vars ///
	setEventVariables(); //////////////
	///////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	// skim 1: at least one CB muon (staco/muid) with pT>pTthreshold /////////
	float pTthreshold = 10.; // in GeV ///////////////////////////////////////
	if(sRunType=="grid" && !m_isMC) //////////////////////////////////////////
	{                               //////////////////////////////////////////
		bool passedSkim = m_WZphysD3PDmaker->passPTskim(pTthreshold); ////////
		if(passedSkim) m_WZphysD3PDmaker->fill(); ////////////////////////////
		if(passedSkim) nSkim++; //////////////////////////////////////////////
	} ////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////
	// NO skim for MC in the grid //////////////////////////////////////
	if(sRunType=="grid" && m_isMC) /////////////////////////////////////
	{                              /////////////////////////////////////
		bool passedSkim = true; ////////////////////////////////////////
		if(passedSkim) m_WZphysD3PDmaker->fill(); //////////////////////
		if(passedSkim) nSkim++; ////////////////////////////////////////
	} //////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////
	// skim 2: 2 mus at least and at least Nmu CB muons (staco/muid) with pT>pTthreshold2 
	float pTthreshold2 = 25.; // in GeV ///////////////////////////////////////////////////
	int   Nmu  = 1; ///////////////////////////////////////////////////////////////////////
	if(sRunType=="local") /////////////////////////////////////////////////////////////////
	{                     /////////////////////////////////////////////////////////////////
		bool passedSkim = m_WZphysD3PDmaker->passNPTCBskim(Nmu, pTthreshold2); ////////////
		if(passedSkim) m_WZphysD3PDmaker->fill(); /////////////////////////////////////////
		if(passedSkim) nSkim++; ///////////////////////////////////////////////////////////
	} /////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	
	_DEBUG("");
	
	////////////////////////////////////////////////////////
	// set all the muon reco' alg vars /////////////////////
	if(sMuonRecoAlgo=="staco") /////////////////////////////
	{                          /////////////////////////////
		setStacoVariables(); ///////////////////////////////
		nMus = (int)m_WZphysD3PD->mu_staco_pt->size(); /////
	}                         //////////////////////////////
	if(sMuonRecoAlgo=="muid") //////////////////////////////
	{                         //////////////////////////////
		setMuidVariables();   //////////////////////////////
		nMus = (int)m_WZphysD3PD->mu_muid_pt->size(); //////
	}                         //////////////////////////////
	////////////////////////////////////////////////////////
	
	_DEBUG("");
	
	/////////////////////////////////////////
	// SMEAR THE MUON PT FOR MC /////////////
	if(m_isMC) setSmearedMCPpT(nMus); ///////
	/////////////////////////////////////////
	
	_DEBUG("");
	
	/////////////////////////////////////
	// set all the trigger vars /////////
	setTrigVariables(); /////////////////
	/////////////////////////////////////
	
	_DEBUG("");
	
	/////////////////////////////////////////////////////
	// reset the muQAflags vector with "true" flags /////
	// build the muons TLorentzVector ///////////////////
	// no need to do this if didn't pass preselection ///
	buildMU4Vector(nMus); ///////////////////////////////
	/////////////////////////////////////////////////////
	
	_DEBUG("");
	
	//////////////////////////////////////////////////
	// Do the Tag&Probe analysis /////////////////////
	applyTagNProbe( (*m_cutsFlowSkipMap) ); //////////
	//////////////////////////////////////////////////
	
	_DEBUG("");
	
	////////////////////////////////////////////////////////////
	// Do the truth weights analysis ///////////////////////////
	if(sRunType=="local_noskim" && m_isMC) applyTruth(); ///////
	////////////////////////////////////////////////////////////
	
	_DEBUG("");
	
	////////////////////////////////////////
	// execute the cut profile analysis ////
	fillCutProfile(); //////////////////////
	////////////////////////////////////////
	
	_DEBUG("");
	
	/*
	nAll++;
	if(mu_n==0) n0mu++;
	int N=0;
	for(int n=0 ; n<mu_n ; n++)
	{
		if( fabs(analysisSkeleton::mu_pt->at(n)*MeV2GeV) > pTthreshold ) N++;
	}
	if(mu_n==1 && N>0) n1mu++;
	if(mu_n==2 && N>0) n2mu++;
	if(mu_n==3 && N>0) n3mu++;
	if(mu_n==4 && N>0) n4mu++;
	if(mu_n>4  && N>0) nNmu++;
 	*/
	
	_DEBUG("");
	
	/////////////////////////////////////////////////////
	// preform the entire preselection //////////////////
	bool passPreselection = applyPreselection(); ////////
	if( !passPreselection ) return; /////////////////////
	/////////////////////////////////////////////////////
	
	_DEBUG("");
	
	///////////////////////////////////////////////////////
	// the single muon selection //////////////////////////
	bool pass1MUselection = applySingleMuonSelection(); ///
	if( !pass1MUselection ) return; ///////////////////////
	///////////////////////////////////////////////////////
	
	_DEBUG("");
	
	//////////////////////////////////////////////////////////////
	// the double muon selection /////////////////////////////////
	bool pass2MUselection = applyDoubleMuonSelection(); //////////
	if( !pass2MUselection ) return; //////////////////////////////
	//////////////////////////////////////////////////////////////
	
	// if(analysisSkeleton::pileup_weight>=0.) _INFO("pileup_weight = "+_s(analysisSkeleton::pileup_weight,5));
	// if(analysisSkeleton::EW_kfactor_weight>1.) _INFO("EW_kfactor_weight = "+_s(analysisSkeleton::EW_kfactor_weight,5));
	// if(analysisSkeleton::QCD_kfactor_weight>0.) _INFO("QCD_kfactor_weight = "+_s(analysisSkeleton::QCD_kfactor_weight,5));
	// if(analysisSkeleton::mcevent_weight>0.) _INFO("mcevent_weight = "+_s(analysisSkeleton::mcevent_weight,5));
	
	
	_DEBUG("");
	
	(*fCandidates)	<< "Run-LB-Evt-Wgt  "
					<< analysisSkeleton::RunNumber	 << " "
					<< analysisSkeleton::lbn 		 << " "
					<< analysisSkeleton::EventNumber << " "
					<< analysisSkeleton::pileup_weight
					<< endl;

	_DEBUG("");
}

void analysis::setEventVariables()
{
	_DEBUG("analysis::setEventVariables");	
	
	// event level
	analysisSkeleton::RunNumber    = m_WZphysD3PD->RunNumber;
	_DEBUG("analysisSkeleton::RunNumber="+_s(analysisSkeleton::RunNumber)+", m_WZphysD3PD->RunNumber="+_s(m_WZphysD3PD->RunNumber));
	analysisSkeleton::EventNumber  = m_WZphysD3PD->EventNumber;
	analysisSkeleton::timestamp    = m_WZphysD3PD->timestamp;
	analysisSkeleton::timestamp_ns = m_WZphysD3PD->timestamp_ns;
	analysisSkeleton::lbn          = m_WZphysD3PD->lbn;
	analysisSkeleton::bcid         = m_WZphysD3PD->bcid;
	
	// EventHash = RunNumber+EventNumber+lbn;
	
	//////////////////////////////////////////////////////
	// do this only if the run number has changed ////////
	analysisSkeleton::sPeriod   = getPeriodName(); ///////
	analysisSkeleton::vTriggers = getPeriodTriggers(); ///
	//////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(!m_isMC) analysisSkeleton::isGRL = m_analysis_grl->m_grl.HasRunLumiBlock( m_WZphysD3PD->RunNumber,m_WZphysD3PD->lbn ); ///
	if(m_isMC) analysisSkeleton::isGRL = 1; /////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	analysisSkeleton::actualIntPerXing  = m_WZphysD3PD->actualIntPerXing;
	analysisSkeleton::averageIntPerXing = m_WZphysD3PD->averageIntPerXing;
	if(m_isMC)
	{
		analysisSkeleton::mc_channel_number = m_WZphysD3PD->mc_channel_number;
		analysisSkeleton::mc_event_number   = m_WZphysD3PD->mc_event_number;
		analysisSkeleton::mc_event_weight   = m_WZphysD3PD->mc_event_weight;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// pileup reweighting, needs to come after setting the lbn //////////////////////
	analysisSkeleton::pileup_weight = 1.;
	if(m_isMC)
	{
		analysisSkeleton::pileup_weight = getPileUpWeight();
		if(analysisSkeleton::pileup_weight<0.) analysisSkeleton::pileup_weight = 1.;
	}
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	analysisSkeleton::EW_kfactor_weight  = 1.;
	analysisSkeleton::QCD_kfactor_weight = 1.;
	if(m_isMC  &&  kFactors::iskFactor(sMCsampleName))
	{	
		// apply EW & QCD corrections to the Z and DY MC
		if(sMCsampleName.find("DYmumu")!=string::npos  ||  sMCsampleName.find("Zmumu")!=string::npos)
		{
			double truth_mass = kFactors::getTruthMass(m_WZphysD3PD->mc_pdgId, m_WZphysD3PD->mc_m, PDTZ)*MeV2GeV;
			analysisSkeleton::EW_kfactor_weight = kFactors::ElectroWeak(truth_mass, "NNLO/LO*");
			analysisSkeleton::QCD_kfactor_weight = kFactors::QCD(truth_mass, "NNLO/LO*");
		}
		
		// apply ONLY QCD corrections to the Z'
		if(sMCsampleName.find("Zprime_mumu")!=string::npos)
		{
			double truth_mass = kFactors::getTruthMass(m_WZphysD3PD->mc_pdgId, m_WZphysD3PD->mc_m, PDTZPRIME0)*MeV2GeV;
			analysisSkeleton::QCD_kfactor_weight = kFactors::QCD(truth_mass, "NNLO/LO*");
		}
		
		// do not apply to any other sample !!!
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////
	analysisSkeleton::mcevent_weight = 1.; /////////////////////////////////////////////
	if(m_isMC)                                    //////////////////////////////////////
	{                                             //////////////////////////////////////
		if(m_WZphysD3PD->mcevt_weight->size()>=1) //////////////////////////////////////
		{                                         //////////////////////////////////////
			analysisSkeleton::mcevent_weight = m_WZphysD3PD->mcevt_weight->at(0)[0]; ///
		}                                         //////////////////////////////////////
	}                                             //////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	
	analysisSkeleton::total_weight = analysisSkeleton::pileup_weight*
									 analysisSkeleton::EW_kfactor_weight*
									 analysisSkeleton::QCD_kfactor_weight*
									 analysisSkeleton::mcevent_weight;
									 
									 
	// L1 triggers
	analysisSkeleton::L1_MU10 = m_WZphysD3PD->L1_MU10;

	// EF triggers
	analysisSkeleton::EF_mu18 = m_WZphysD3PD->EF_mu18;
	analysisSkeleton::EF_mu18_MG = m_WZphysD3PD->EF_mu18_MG;
	
	analysisSkeleton::EF_mu18_MG_medium = m_WZphysD3PD->EF_mu18_MG_medium;
	analysisSkeleton::EF_mu18_medium = m_WZphysD3PD->EF_mu18_medium;

	analysisSkeleton::EF_mu22 = m_WZphysD3PD->EF_mu22;
	analysisSkeleton::EF_mu22_MG = m_WZphysD3PD->EF_mu22_MG;
	
	analysisSkeleton::EF_mu22_medium = m_WZphysD3PD->EF_mu22_medium;
	analysisSkeleton::EF_mu22_MG_medium = m_WZphysD3PD->EF_mu22_MG_medium;

	analysisSkeleton::EF_mu40_MSonly_barrel = m_WZphysD3PD->EF_mu40_MSonly_barrel;
	analysisSkeleton::EF_mu40_MSonly_barrel_medium = m_WZphysD3PD->EF_mu40_MSonly_barrel_medium;
	
	// vertexes (for the PV preselection)
	analysisSkeleton::vxp_n       = m_WZphysD3PD->vxp_n;
	analysisSkeleton::vxp_nTracks = m_WZphysD3PD->vxp_nTracks;
	analysisSkeleton::vxp_type    = m_WZphysD3PD->vxp_type;
	analysisSkeleton::vxp_z       = m_WZphysD3PD->vxp_z;
	
	if(m_isMC)
	{
		// muonTruth
		analysisSkeleton::muonTruth_n = m_WZphysD3PD->muonTruth_n;
		analysisSkeleton::muonTruth_pt = m_WZphysD3PD->muonTruth_pt;
		analysisSkeleton::muonTruth_m = m_WZphysD3PD->muonTruth_m;
		analysisSkeleton::muonTruth_eta = m_WZphysD3PD->muonTruth_eta;
		analysisSkeleton::muonTruth_phi = m_WZphysD3PD->muonTruth_phi;
		analysisSkeleton::muonTruth_charge = m_WZphysD3PD->muonTruth_charge;
		analysisSkeleton::muonTruth_PDGID = m_WZphysD3PD->muonTruth_PDGID;
		analysisSkeleton::muonTruth_barcode = m_WZphysD3PD->muonTruth_barcode;
		analysisSkeleton::muonTruth_type = m_WZphysD3PD->muonTruth_type;
		analysisSkeleton::muonTruth_origin = m_WZphysD3PD->muonTruth_origin;
		
		// MC event
		analysisSkeleton::mcevt_n = m_WZphysD3PD->mcevt_n;
		analysisSkeleton::mcevt_signal_process_id = m_WZphysD3PD->mcevt_signal_process_id;
		analysisSkeleton::mcevt_event_number = m_WZphysD3PD->mcevt_event_number;
		analysisSkeleton::mcevt_event_scale = m_WZphysD3PD->mcevt_event_scale;
		analysisSkeleton::mcevt_alphaQCD = m_WZphysD3PD->mcevt_alphaQCD;
		analysisSkeleton::mcevt_alphaQED = m_WZphysD3PD->mcevt_alphaQED;
		analysisSkeleton::mcevt_pdf_id1 = m_WZphysD3PD->mcevt_pdf_id1;
		analysisSkeleton::mcevt_pdf_id2 = m_WZphysD3PD->mcevt_pdf_id2;
		analysisSkeleton::mcevt_pdf_x1 = m_WZphysD3PD->mcevt_pdf_x1;
		analysisSkeleton::mcevt_pdf_x2 = m_WZphysD3PD->mcevt_pdf_x2;
		analysisSkeleton::mcevt_pdf_scale = m_WZphysD3PD->mcevt_pdf_scale;
		analysisSkeleton::mcevt_pdf1 = m_WZphysD3PD->mcevt_pdf1;
		analysisSkeleton::mcevt_pdf2 = m_WZphysD3PD->mcevt_pdf2;
		// analysisSkeleton::mcevt_weight = m_WZphysD3PD->mcevt_weight;
		
		// MC
		analysisSkeleton::mc_n = m_WZphysD3PD->mc_n;
		analysisSkeleton::mc_pt = m_WZphysD3PD->mc_pt;
		analysisSkeleton::mc_m = m_WZphysD3PD->mc_m;
		analysisSkeleton::mc_eta = m_WZphysD3PD->mc_eta;
		analysisSkeleton::mc_phi = m_WZphysD3PD->mc_phi;
		analysisSkeleton::mc_status = m_WZphysD3PD->mc_status;
		analysisSkeleton::mc_barcode = m_WZphysD3PD->mc_barcode;
		analysisSkeleton::mc_parents = m_WZphysD3PD->mc_parents;
		analysisSkeleton::mc_children = m_WZphysD3PD->mc_children;
		analysisSkeleton::mc_pdgId = m_WZphysD3PD->mc_pdgId;
		analysisSkeleton::mc_charge = m_WZphysD3PD->mc_charge;
		analysisSkeleton::mc_vx_x = m_WZphysD3PD->mc_vx_x;
		analysisSkeleton::mc_vx_y = m_WZphysD3PD->mc_vx_y;
		analysisSkeleton::mc_vx_z = m_WZphysD3PD->mc_vx_z;
		analysisSkeleton::mc_child_index = m_WZphysD3PD->mc_child_index;
		analysisSkeleton::mc_parent_index = m_WZphysD3PD->mc_parent_index;
	}
}

void analysis::setStacoVariables()
{
	_DEBUG("analysis::setStacoVariables");

	analysisSkeleton::mu_n = m_WZphysD3PD->mu_staco_n;
	analysisSkeleton::mu_E = m_WZphysD3PD->mu_staco_E;
	analysisSkeleton::mu_pt = m_WZphysD3PD->mu_staco_pt;
	analysisSkeleton::mu_m = m_WZphysD3PD->mu_staco_m;
	analysisSkeleton::mu_eta = m_WZphysD3PD->mu_staco_eta;
	analysisSkeleton::mu_phi = m_WZphysD3PD->mu_staco_phi;
	analysisSkeleton::mu_px = m_WZphysD3PD->mu_staco_px;
	analysisSkeleton::mu_py = m_WZphysD3PD->mu_staco_py;
	analysisSkeleton::mu_pz = m_WZphysD3PD->mu_staco_pz;
	analysisSkeleton::mu_charge = m_WZphysD3PD->mu_staco_charge;
	analysisSkeleton::mu_allauthor = m_WZphysD3PD->mu_staco_allauthor;
	analysisSkeleton::mu_author = m_WZphysD3PD->mu_staco_author;
	analysisSkeleton::mu_beta = m_WZphysD3PD->mu_staco_beta;
	analysisSkeleton::mu_isMuonLikelihood = m_WZphysD3PD->mu_staco_isMuonLikelihood;
	analysisSkeleton::mu_matchchi2 = m_WZphysD3PD->mu_staco_matchchi2;
	analysisSkeleton::mu_matchndof = m_WZphysD3PD->mu_staco_matchndof;
	analysisSkeleton::mu_etcone20 = m_WZphysD3PD->mu_staco_etcone20;
	analysisSkeleton::mu_etcone30 = m_WZphysD3PD->mu_staco_etcone30;
	analysisSkeleton::mu_etcone40 = m_WZphysD3PD->mu_staco_etcone40;
	analysisSkeleton::mu_nucone20 = m_WZphysD3PD->mu_staco_nucone20;
	analysisSkeleton::mu_nucone30 = m_WZphysD3PD->mu_staco_nucone30;
	analysisSkeleton::mu_nucone40 = m_WZphysD3PD->mu_staco_nucone40;
	analysisSkeleton::mu_ptcone20 = m_WZphysD3PD->mu_staco_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_WZphysD3PD->mu_staco_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_WZphysD3PD->mu_staco_ptcone40;
	analysisSkeleton::mu_energyLossPar = m_WZphysD3PD->mu_staco_energyLossPar;
	analysisSkeleton::mu_energyLossErr = m_WZphysD3PD->mu_staco_energyLossErr;
	analysisSkeleton::mu_etCore = m_WZphysD3PD->mu_staco_etCore;
	analysisSkeleton::mu_energyLossType = m_WZphysD3PD->mu_staco_energyLossType;
	analysisSkeleton::mu_caloMuonIdTag = m_WZphysD3PD->mu_staco_caloMuonIdTag;
	analysisSkeleton::mu_caloLRLikelihood = m_WZphysD3PD->mu_staco_caloLRLikelihood;
	analysisSkeleton::mu_bestMatch = m_WZphysD3PD->mu_staco_bestMatch;
	analysisSkeleton::mu_isStandAloneMuon = m_WZphysD3PD->mu_staco_isStandAloneMuon;
	analysisSkeleton::mu_isCombinedMuon = m_WZphysD3PD->mu_staco_isCombinedMuon;
	analysisSkeleton::mu_isLowPtReconstructedMuon = m_WZphysD3PD->mu_staco_isLowPtReconstructedMuon;
	analysisSkeleton::mu_loose = m_WZphysD3PD->mu_staco_loose;
	analysisSkeleton::mu_medium = m_WZphysD3PD->mu_staco_medium;
	analysisSkeleton::mu_tight = m_WZphysD3PD->mu_staco_tight;
	analysisSkeleton::mu_d0_exPV = m_WZphysD3PD->mu_staco_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_WZphysD3PD->mu_staco_z0_exPV;
	analysisSkeleton::mu_phi_exPV = m_WZphysD3PD->mu_staco_phi_exPV;
	analysisSkeleton::mu_theta_exPV = m_WZphysD3PD->mu_staco_theta_exPV;
	analysisSkeleton::mu_qoverp_exPV = m_WZphysD3PD->mu_staco_qoverp_exPV;
	analysisSkeleton::mu_cb_d0_exPV = m_WZphysD3PD->mu_staco_cb_d0_exPV;
	analysisSkeleton::mu_cb_z0_exPV = m_WZphysD3PD->mu_staco_cb_z0_exPV;
	analysisSkeleton::mu_cb_phi_exPV = m_WZphysD3PD->mu_staco_cb_phi_exPV;
	analysisSkeleton::mu_cb_theta_exPV = m_WZphysD3PD->mu_staco_cb_theta_exPV;
	analysisSkeleton::mu_cb_qoverp_exPV = m_WZphysD3PD->mu_staco_cb_qoverp_exPV;
	analysisSkeleton::mu_id_d0_exPV = m_WZphysD3PD->mu_staco_id_d0_exPV;
	analysisSkeleton::mu_id_z0_exPV = m_WZphysD3PD->mu_staco_id_z0_exPV;
	analysisSkeleton::mu_id_phi_exPV = m_WZphysD3PD->mu_staco_id_phi_exPV;
	analysisSkeleton::mu_id_theta_exPV = m_WZphysD3PD->mu_staco_id_theta_exPV;
	analysisSkeleton::mu_id_qoverp_exPV = m_WZphysD3PD->mu_staco_id_qoverp_exPV;
	analysisSkeleton::mu_me_d0_exPV = m_WZphysD3PD->mu_staco_me_d0_exPV;
	analysisSkeleton::mu_me_z0_exPV = m_WZphysD3PD->mu_staco_me_z0_exPV;
	analysisSkeleton::mu_me_phi_exPV = m_WZphysD3PD->mu_staco_me_phi_exPV;
	analysisSkeleton::mu_me_theta_exPV = m_WZphysD3PD->mu_staco_me_theta_exPV;
	analysisSkeleton::mu_me_qoverp_exPV = m_WZphysD3PD->mu_staco_me_qoverp_exPV;
	analysisSkeleton::mu_ie_d0_exPV = m_WZphysD3PD->mu_staco_ie_d0_exPV;
	analysisSkeleton::mu_ie_z0_exPV = m_WZphysD3PD->mu_staco_ie_z0_exPV;
	analysisSkeleton::mu_ie_phi_exPV = m_WZphysD3PD->mu_staco_ie_phi_exPV;
	analysisSkeleton::mu_ie_theta_exPV = m_WZphysD3PD->mu_staco_ie_theta_exPV;
	analysisSkeleton::mu_ie_qoverp_exPV = m_WZphysD3PD->mu_staco_ie_qoverp_exPV;
	analysisSkeleton::mu_SpaceTime_detID = m_WZphysD3PD->mu_staco_SpaceTime_detID;
	analysisSkeleton::mu_SpaceTime_t = m_WZphysD3PD->mu_staco_SpaceTime_t;
	analysisSkeleton::mu_SpaceTime_tError = m_WZphysD3PD->mu_staco_SpaceTime_tError;
	analysisSkeleton::mu_SpaceTime_weight = m_WZphysD3PD->mu_staco_SpaceTime_weight;
	analysisSkeleton::mu_SpaceTime_x = m_WZphysD3PD->mu_staco_SpaceTime_x;
	analysisSkeleton::mu_SpaceTime_y = m_WZphysD3PD->mu_staco_SpaceTime_y;
	analysisSkeleton::mu_SpaceTime_z = m_WZphysD3PD->mu_staco_SpaceTime_z;
/*	analysisSkeleton::mu_SpaceTime_t_Tile = m_WZphysD3PD->mu_staco_SpaceTime_t_Tile;
	analysisSkeleton::mu_SpaceTime_tError_Tile = m_WZphysD3PD->mu_staco_SpaceTime_tError_Tile;
	analysisSkeleton::mu_SpaceTime_weight_Tile = m_WZphysD3PD->mu_staco_SpaceTime_weight_Tile;
	analysisSkeleton::mu_SpaceTime_x_Tile = m_WZphysD3PD->mu_staco_SpaceTime_x_Tile;
	analysisSkeleton::mu_SpaceTime_y_Tile = m_WZphysD3PD->mu_staco_SpaceTime_y_Tile;
	analysisSkeleton::mu_SpaceTime_z_Tile = m_WZphysD3PD->mu_staco_SpaceTime_z_Tile;
	analysisSkeleton::mu_SpaceTime_t_TRT = m_WZphysD3PD->mu_staco_SpaceTime_t_TRT;
	analysisSkeleton::mu_SpaceTime_tError_TRT = m_WZphysD3PD->mu_staco_SpaceTime_tError_TRT;
	analysisSkeleton::mu_SpaceTime_weight_TRT = m_WZphysD3PD->mu_staco_SpaceTime_weight_TRT;
	analysisSkeleton::mu_SpaceTime_x_TRT = m_WZphysD3PD->mu_staco_SpaceTime_x_TRT;
	analysisSkeleton::mu_SpaceTime_y_TRT = m_WZphysD3PD->mu_staco_SpaceTime_y_TRT;
	analysisSkeleton::mu_SpaceTime_z_TRT = m_WZphysD3PD->mu_staco_SpaceTime_z_TRT;
	analysisSkeleton::mu_SpaceTime_t_MDT = m_WZphysD3PD->mu_staco_SpaceTime_t_MDT;
	analysisSkeleton::mu_SpaceTime_tError_MDT = m_WZphysD3PD->mu_staco_SpaceTime_tError_MDT;
	analysisSkeleton::mu_SpaceTime_weight_MDT = m_WZphysD3PD->mu_staco_SpaceTime_weight_MDT;
	analysisSkeleton::mu_SpaceTime_x_MDT = m_WZphysD3PD->mu_staco_SpaceTime_x_MDT;
	analysisSkeleton::mu_SpaceTime_y_MDT = m_WZphysD3PD->mu_staco_SpaceTime_y_MDT;
	analysisSkeleton::mu_SpaceTime_z_MDT = m_WZphysD3PD->mu_staco_SpaceTime_z_MDT;
	analysisSkeleton::mu_TileCellEnergyLayer1 = m_WZphysD3PD->mu_staco_TileCellEnergyLayer1;
	analysisSkeleton::mu_TileTimeLayer1 = m_WZphysD3PD->mu_staco_TileTimeLayer1;
	analysisSkeleton::mu_TileCellRmsNoiseLayer1 = m_WZphysD3PD->mu_staco_TileCellRmsNoiseLayer1;
	analysisSkeleton::mu_TileCellSignLayer1 = m_WZphysD3PD->mu_staco_TileCellSignLayer1;
	analysisSkeleton::mu_TileCellEnergyLayer2 = m_WZphysD3PD->mu_staco_TileCellEnergyLayer2;
	analysisSkeleton::mu_TileTimeLayer2 = m_WZphysD3PD->mu_staco_TileTimeLayer2;
	analysisSkeleton::mu_TileCellRmsNoiseLayer2 = m_WZphysD3PD->mu_staco_TileCellRmsNoiseLayer2;
	analysisSkeleton::mu_TileCellSignLayer2 = m_WZphysD3PD->mu_staco_TileCellSignLayer2;
	analysisSkeleton::mu_TileCellEnergyLayer3 = m_WZphysD3PD->mu_staco_TileCellEnergyLayer3;
	analysisSkeleton::mu_TileTimeLayer3 = m_WZphysD3PD->mu_staco_TileTimeLayer3;
	analysisSkeleton::mu_TileCellRmsNoiseLayer3 = m_WZphysD3PD->mu_staco_TileCellRmsNoiseLayer3;
	analysisSkeleton::mu_TileCellSignLayer3 = m_WZphysD3PD->mu_staco_TileCellSignLayer3;
	analysisSkeleton::mu_MSTrkT0_1 = m_WZphysD3PD->mu_staco_MSTrkT0_1;
	analysisSkeleton::mu_MSTrkT0_2 = m_WZphysD3PD->mu_staco_MSTrkT0_2;
	analysisSkeleton::mu_MSTrkT0_3 = m_WZphysD3PD->mu_staco_MSTrkT0_3;
*/
	analysisSkeleton::mu_cov_d0_exPV = m_WZphysD3PD->mu_staco_cov_d0_exPV;
	analysisSkeleton::mu_cov_z0_exPV = m_WZphysD3PD->mu_staco_cov_z0_exPV;
	analysisSkeleton::mu_cov_phi_exPV = m_WZphysD3PD->mu_staco_cov_phi_exPV;
	analysisSkeleton::mu_cov_theta_exPV = m_WZphysD3PD->mu_staco_cov_theta_exPV;
	analysisSkeleton::mu_cov_qoverp_exPV = m_WZphysD3PD->mu_staco_cov_qoverp_exPV;
	analysisSkeleton::mu_cov_d0_z0_exPV = m_WZphysD3PD->mu_staco_cov_d0_z0_exPV;
	analysisSkeleton::mu_cov_d0_phi_exPV = m_WZphysD3PD->mu_staco_cov_d0_phi_exPV;
	analysisSkeleton::mu_cov_d0_theta_exPV = m_WZphysD3PD->mu_staco_cov_d0_theta_exPV;
	analysisSkeleton::mu_cov_d0_qoverp_exPV = m_WZphysD3PD->mu_staco_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_cov_z0_phi_exPV = m_WZphysD3PD->mu_staco_cov_z0_phi_exPV;
	analysisSkeleton::mu_cov_z0_theta_exPV = m_WZphysD3PD->mu_staco_cov_z0_theta_exPV;
	analysisSkeleton::mu_cov_z0_qoverp_exPV = m_WZphysD3PD->mu_staco_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_cov_phi_theta_exPV = m_WZphysD3PD->mu_staco_cov_phi_theta_exPV;
	analysisSkeleton::mu_cov_phi_qoverp_exPV = m_WZphysD3PD->mu_staco_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_cov_theta_qoverp_exPV = m_WZphysD3PD->mu_staco_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_id_cov_d0_exPV = m_WZphysD3PD->mu_staco_id_cov_d0_exPV;
	analysisSkeleton::mu_id_cov_z0_exPV = m_WZphysD3PD->mu_staco_id_cov_z0_exPV;
	analysisSkeleton::mu_id_cov_phi_exPV = m_WZphysD3PD->mu_staco_id_cov_phi_exPV;
	analysisSkeleton::mu_id_cov_theta_exPV = m_WZphysD3PD->mu_staco_id_cov_theta_exPV;
	analysisSkeleton::mu_id_cov_qoverp_exPV = m_WZphysD3PD->mu_staco_id_cov_qoverp_exPV;
	analysisSkeleton::mu_id_cov_d0_z0_exPV = m_WZphysD3PD->mu_staco_id_cov_d0_z0_exPV;
	analysisSkeleton::mu_id_cov_d0_phi_exPV = m_WZphysD3PD->mu_staco_id_cov_d0_phi_exPV;
	analysisSkeleton::mu_id_cov_d0_theta_exPV = m_WZphysD3PD->mu_staco_id_cov_d0_theta_exPV;
	analysisSkeleton::mu_id_cov_d0_qoverp_exPV = m_WZphysD3PD->mu_staco_id_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_id_cov_z0_phi_exPV = m_WZphysD3PD->mu_staco_id_cov_z0_phi_exPV;
	analysisSkeleton::mu_id_cov_z0_theta_exPV = m_WZphysD3PD->mu_staco_id_cov_z0_theta_exPV;
	analysisSkeleton::mu_id_cov_z0_qoverp_exPV = m_WZphysD3PD->mu_staco_id_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_id_cov_phi_theta_exPV = m_WZphysD3PD->mu_staco_id_cov_phi_theta_exPV;
	analysisSkeleton::mu_id_cov_phi_qoverp_exPV = m_WZphysD3PD->mu_staco_id_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_id_cov_theta_qoverp_exPV = m_WZphysD3PD->mu_staco_id_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_me_cov_d0_exPV = m_WZphysD3PD->mu_staco_me_cov_d0_exPV;
	analysisSkeleton::mu_me_cov_z0_exPV = m_WZphysD3PD->mu_staco_me_cov_z0_exPV;
	analysisSkeleton::mu_me_cov_phi_exPV = m_WZphysD3PD->mu_staco_me_cov_phi_exPV;
	analysisSkeleton::mu_me_cov_theta_exPV = m_WZphysD3PD->mu_staco_me_cov_theta_exPV;
	analysisSkeleton::mu_me_cov_qoverp_exPV = m_WZphysD3PD->mu_staco_me_cov_qoverp_exPV;
	analysisSkeleton::mu_me_cov_d0_z0_exPV = m_WZphysD3PD->mu_staco_me_cov_d0_z0_exPV;
	analysisSkeleton::mu_me_cov_d0_phi_exPV = m_WZphysD3PD->mu_staco_me_cov_d0_phi_exPV;
	analysisSkeleton::mu_me_cov_d0_theta_exPV = m_WZphysD3PD->mu_staco_me_cov_d0_theta_exPV;
	analysisSkeleton::mu_me_cov_d0_qoverp_exPV = m_WZphysD3PD->mu_staco_me_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_me_cov_z0_phi_exPV = m_WZphysD3PD->mu_staco_me_cov_z0_phi_exPV;
	analysisSkeleton::mu_me_cov_z0_theta_exPV = m_WZphysD3PD->mu_staco_me_cov_z0_theta_exPV;
	analysisSkeleton::mu_me_cov_z0_qoverp_exPV = m_WZphysD3PD->mu_staco_me_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_me_cov_phi_theta_exPV = m_WZphysD3PD->mu_staco_me_cov_phi_theta_exPV;
	analysisSkeleton::mu_me_cov_phi_qoverp_exPV = m_WZphysD3PD->mu_staco_me_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_me_cov_theta_qoverp_exPV = m_WZphysD3PD->mu_staco_me_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_ms_d0 = m_WZphysD3PD->mu_staco_ms_d0;
	analysisSkeleton::mu_ms_z0 = m_WZphysD3PD->mu_staco_ms_z0;
	analysisSkeleton::mu_ms_phi = m_WZphysD3PD->mu_staco_ms_phi;
	analysisSkeleton::mu_ms_theta = m_WZphysD3PD->mu_staco_ms_theta;
	analysisSkeleton::mu_ms_qoverp = m_WZphysD3PD->mu_staco_ms_qoverp;
	analysisSkeleton::mu_id_d0 = m_WZphysD3PD->mu_staco_id_d0;
	analysisSkeleton::mu_id_z0 = m_WZphysD3PD->mu_staco_id_z0;
	analysisSkeleton::mu_id_phi = m_WZphysD3PD->mu_staco_id_phi;
	analysisSkeleton::mu_id_theta = m_WZphysD3PD->mu_staco_id_theta;
	analysisSkeleton::mu_id_qoverp = m_WZphysD3PD->mu_staco_id_qoverp;
	analysisSkeleton::mu_me_d0 = m_WZphysD3PD->mu_staco_me_d0;
	analysisSkeleton::mu_me_z0 = m_WZphysD3PD->mu_staco_me_z0;
	analysisSkeleton::mu_me_phi = m_WZphysD3PD->mu_staco_me_phi;
	analysisSkeleton::mu_me_theta = m_WZphysD3PD->mu_staco_me_theta;
	analysisSkeleton::mu_me_qoverp = m_WZphysD3PD->mu_staco_me_qoverp;
	analysisSkeleton::mu_ie_d0 = m_WZphysD3PD->mu_staco_ie_d0;
	analysisSkeleton::mu_ie_z0 = m_WZphysD3PD->mu_staco_ie_z0;
	analysisSkeleton::mu_ie_phi = m_WZphysD3PD->mu_staco_ie_phi;
	analysisSkeleton::mu_ie_theta = m_WZphysD3PD->mu_staco_ie_theta;
	analysisSkeleton::mu_ie_qoverp = m_WZphysD3PD->mu_staco_ie_qoverp;
	analysisSkeleton::mu_nOutliersOnTrack = m_WZphysD3PD->mu_staco_nOutliersOnTrack;
	analysisSkeleton::mu_nBLHits = m_WZphysD3PD->mu_staco_nBLHits;
	analysisSkeleton::mu_nPixHits = m_WZphysD3PD->mu_staco_nPixHits;
	analysisSkeleton::mu_nSCTHits = m_WZphysD3PD->mu_staco_nSCTHits;
	analysisSkeleton::mu_nTRTHits = m_WZphysD3PD->mu_staco_nTRTHits;
	analysisSkeleton::mu_nTRTHighTHits = m_WZphysD3PD->mu_staco_nTRTHighTHits;
	analysisSkeleton::mu_nBLSharedHits = m_WZphysD3PD->mu_staco_nBLSharedHits;
	analysisSkeleton::mu_nPixSharedHits = m_WZphysD3PD->mu_staco_nPixSharedHits;
	analysisSkeleton::mu_nPixHoles = m_WZphysD3PD->mu_staco_nPixHoles;
	analysisSkeleton::mu_nSCTSharedHits = m_WZphysD3PD->mu_staco_nSCTSharedHits;
	analysisSkeleton::mu_nSCTHoles = m_WZphysD3PD->mu_staco_nSCTHoles;
	analysisSkeleton::mu_nTRTOutliers = m_WZphysD3PD->mu_staco_nTRTOutliers;
	analysisSkeleton::mu_nTRTHighTOutliers = m_WZphysD3PD->mu_staco_nTRTHighTOutliers;
	analysisSkeleton::mu_nGangedPixels = m_WZphysD3PD->mu_staco_nGangedPixels;
	analysisSkeleton::mu_nPixelDeadSensors = m_WZphysD3PD->mu_staco_nPixelDeadSensors;
	analysisSkeleton::mu_nSCTDeadSensors = m_WZphysD3PD->mu_staco_nSCTDeadSensors;
	analysisSkeleton::mu_nTRTDeadStraws = m_WZphysD3PD->mu_staco_nTRTDeadStraws;
	analysisSkeleton::mu_expectBLayerHit = m_WZphysD3PD->mu_staco_expectBLayerHit;
	analysisSkeleton::mu_nMDTHits = m_WZphysD3PD->mu_staco_nMDTHits;
	analysisSkeleton::mu_nMDTHoles = m_WZphysD3PD->mu_staco_nMDTHoles;
	analysisSkeleton::mu_nCSCEtaHits = m_WZphysD3PD->mu_staco_nCSCEtaHits;
	analysisSkeleton::mu_nCSCEtaHoles = m_WZphysD3PD->mu_staco_nCSCEtaHoles;
	analysisSkeleton::mu_nCSCPhiHits = m_WZphysD3PD->mu_staco_nCSCPhiHits;
	analysisSkeleton::mu_nCSCPhiHoles = m_WZphysD3PD->mu_staco_nCSCPhiHoles;
	analysisSkeleton::mu_nRPCEtaHits = m_WZphysD3PD->mu_staco_nRPCEtaHits;
	analysisSkeleton::mu_nRPCEtaHoles = m_WZphysD3PD->mu_staco_nRPCEtaHoles;
	analysisSkeleton::mu_nRPCPhiHits = m_WZphysD3PD->mu_staco_nRPCPhiHits;
	analysisSkeleton::mu_nRPCPhiHoles = m_WZphysD3PD->mu_staco_nRPCPhiHoles;
	analysisSkeleton::mu_nTGCEtaHits = m_WZphysD3PD->mu_staco_nTGCEtaHits;
	analysisSkeleton::mu_nTGCEtaHoles = m_WZphysD3PD->mu_staco_nTGCEtaHoles;
	analysisSkeleton::mu_nTGCPhiHits = m_WZphysD3PD->mu_staco_nTGCPhiHits;
	analysisSkeleton::mu_nTGCPhiHoles = m_WZphysD3PD->mu_staco_nTGCPhiHoles;
	analysisSkeleton::mu_nMDTBIHits = m_WZphysD3PD->mu_staco_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_WZphysD3PD->mu_staco_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_WZphysD3PD->mu_staco_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_WZphysD3PD->mu_staco_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_WZphysD3PD->mu_staco_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_WZphysD3PD->mu_staco_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_WZphysD3PD->mu_staco_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_WZphysD3PD->mu_staco_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_WZphysD3PD->mu_staco_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_WZphysD3PD->mu_staco_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_WZphysD3PD->mu_staco_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_WZphysD3PD->mu_staco_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_WZphysD3PD->mu_staco_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_WZphysD3PD->mu_staco_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_WZphysD3PD->mu_staco_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_WZphysD3PD->mu_staco_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_WZphysD3PD->mu_staco_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_WZphysD3PD->mu_staco_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_WZphysD3PD->mu_staco_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_WZphysD3PD->mu_staco_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_WZphysD3PD->mu_staco_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_WZphysD3PD->mu_staco_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_WZphysD3PD->mu_staco_nTGCLayer4PhiHits;
	analysisSkeleton::mu_barrelSectors = m_WZphysD3PD->mu_staco_barrelSectors;
	analysisSkeleton::mu_endcapSectors = m_WZphysD3PD->mu_staco_endcapSectors;
	analysisSkeleton::mu_trackd0 = m_WZphysD3PD->mu_staco_trackd0;
	analysisSkeleton::mu_trackz0 = m_WZphysD3PD->mu_staco_trackz0;
	analysisSkeleton::mu_trackphi = m_WZphysD3PD->mu_staco_trackphi;
	analysisSkeleton::mu_tracktheta = m_WZphysD3PD->mu_staco_tracktheta;
	analysisSkeleton::mu_trackqoverp = m_WZphysD3PD->mu_staco_trackqoverp;
	analysisSkeleton::mu_trackcov_d0 = m_WZphysD3PD->mu_staco_trackcov_d0;
	analysisSkeleton::mu_trackcov_z0 = m_WZphysD3PD->mu_staco_trackcov_z0;
	analysisSkeleton::mu_trackcov_phi = m_WZphysD3PD->mu_staco_trackcov_phi;
	analysisSkeleton::mu_trackcov_theta = m_WZphysD3PD->mu_staco_trackcov_theta;
	analysisSkeleton::mu_trackcov_qoverp = m_WZphysD3PD->mu_staco_trackcov_qoverp;
	analysisSkeleton::mu_trackcov_d0_z0 = m_WZphysD3PD->mu_staco_trackcov_d0_z0;
	analysisSkeleton::mu_trackcov_d0_phi = m_WZphysD3PD->mu_staco_trackcov_d0_phi;
	analysisSkeleton::mu_trackcov_d0_theta = m_WZphysD3PD->mu_staco_trackcov_d0_theta;
	analysisSkeleton::mu_trackcov_d0_qoverp = m_WZphysD3PD->mu_staco_trackcov_d0_qoverp;
	analysisSkeleton::mu_trackcov_z0_phi = m_WZphysD3PD->mu_staco_trackcov_z0_phi;
	analysisSkeleton::mu_trackcov_z0_theta = m_WZphysD3PD->mu_staco_trackcov_z0_theta;
	analysisSkeleton::mu_trackcov_z0_qoverp = m_WZphysD3PD->mu_staco_trackcov_z0_qoverp;
	analysisSkeleton::mu_trackcov_phi_theta = m_WZphysD3PD->mu_staco_trackcov_phi_theta;
	analysisSkeleton::mu_trackcov_phi_qoverp = m_WZphysD3PD->mu_staco_trackcov_phi_qoverp;
	analysisSkeleton::mu_trackcov_theta_qoverp = m_WZphysD3PD->mu_staco_trackcov_theta_qoverp;
	analysisSkeleton::mu_trackfitchi2 = m_WZphysD3PD->mu_staco_trackfitchi2;
	analysisSkeleton::mu_trackfitndof = m_WZphysD3PD->mu_staco_trackfitndof;
	analysisSkeleton::mu_hastrack = m_WZphysD3PD->mu_staco_hastrack;
	if(m_isMC)
	{
		analysisSkeleton::mu_truth_dr = m_WZphysD3PD->mu_staco_truth_dr;
		analysisSkeleton::mu_truth_E = m_WZphysD3PD->mu_staco_truth_E;
		analysisSkeleton::mu_truth_pt = m_WZphysD3PD->mu_staco_truth_pt;
		analysisSkeleton::mu_truth_eta = m_WZphysD3PD->mu_staco_truth_eta;
		analysisSkeleton::mu_truth_phi = m_WZphysD3PD->mu_staco_truth_phi;
		analysisSkeleton::mu_truth_type = m_WZphysD3PD->mu_staco_truth_type;
		analysisSkeleton::mu_truth_status = m_WZphysD3PD->mu_staco_truth_status;
		analysisSkeleton::mu_truth_barcode = m_WZphysD3PD->mu_staco_truth_barcode;
		analysisSkeleton::mu_truth_mothertype = m_WZphysD3PD->mu_staco_truth_mothertype;
		analysisSkeleton::mu_truth_motherbarcode = m_WZphysD3PD->mu_staco_truth_motherbarcode;
		analysisSkeleton::mu_truth_matched = m_WZphysD3PD->mu_staco_truth_matched;
	}
	analysisSkeleton::mu_EFCB_dr = m_WZphysD3PD->mu_staco_EFCB_dr;
	analysisSkeleton::mu_EFCB_index = m_WZphysD3PD->mu_staco_EFCB_index;
	analysisSkeleton::mu_EFMG_dr = m_WZphysD3PD->mu_staco_EFMG_dr;
	analysisSkeleton::mu_EFMG_index = m_WZphysD3PD->mu_staco_EFMG_index;
	analysisSkeleton::mu_EFME_dr = m_WZphysD3PD->mu_staco_EFME_dr;
	analysisSkeleton::mu_EFME_index = m_WZphysD3PD->mu_staco_EFME_index;
	analysisSkeleton::mu_L2CB_dr = m_WZphysD3PD->mu_staco_L2CB_dr;
	analysisSkeleton::mu_L2CB_index = m_WZphysD3PD->mu_staco_L2CB_index;
	analysisSkeleton::mu_L1_dr = m_WZphysD3PD->mu_staco_L1_dr;
	analysisSkeleton::mu_L1_index = m_WZphysD3PD->mu_staco_L1_index;
}

void analysis::setMuidVariables()
{
	_DEBUG("analysis::setMuidVariables");

	analysisSkeleton::mu_n = m_WZphysD3PD->mu_muid_n;
	analysisSkeleton::mu_E = m_WZphysD3PD->mu_muid_E;
	analysisSkeleton::mu_pt = m_WZphysD3PD->mu_muid_pt;
	analysisSkeleton::mu_m = m_WZphysD3PD->mu_muid_m;
	analysisSkeleton::mu_eta = m_WZphysD3PD->mu_muid_eta;
	analysisSkeleton::mu_phi = m_WZphysD3PD->mu_muid_phi;
	analysisSkeleton::mu_px = m_WZphysD3PD->mu_muid_px;
	analysisSkeleton::mu_py = m_WZphysD3PD->mu_muid_py;
	analysisSkeleton::mu_pz = m_WZphysD3PD->mu_muid_pz;
	analysisSkeleton::mu_charge = m_WZphysD3PD->mu_muid_charge;
	analysisSkeleton::mu_allauthor = m_WZphysD3PD->mu_muid_allauthor;
	analysisSkeleton::mu_author = m_WZphysD3PD->mu_muid_author;
	analysisSkeleton::mu_beta = m_WZphysD3PD->mu_muid_beta;
	analysisSkeleton::mu_isMuonLikelihood = m_WZphysD3PD->mu_muid_isMuonLikelihood;
	analysisSkeleton::mu_matchchi2 = m_WZphysD3PD->mu_muid_matchchi2;
	analysisSkeleton::mu_matchndof = m_WZphysD3PD->mu_muid_matchndof;
	analysisSkeleton::mu_etcone20 = m_WZphysD3PD->mu_muid_etcone20;
	analysisSkeleton::mu_etcone30 = m_WZphysD3PD->mu_muid_etcone30;
	analysisSkeleton::mu_etcone40 = m_WZphysD3PD->mu_muid_etcone40;
	analysisSkeleton::mu_nucone20 = m_WZphysD3PD->mu_muid_nucone20;
	analysisSkeleton::mu_nucone30 = m_WZphysD3PD->mu_muid_nucone30;
	analysisSkeleton::mu_nucone40 = m_WZphysD3PD->mu_muid_nucone40;
	analysisSkeleton::mu_ptcone20 = m_WZphysD3PD->mu_muid_ptcone20;
	analysisSkeleton::mu_ptcone30 = m_WZphysD3PD->mu_muid_ptcone30;
	analysisSkeleton::mu_ptcone40 = m_WZphysD3PD->mu_muid_ptcone40;
	analysisSkeleton::mu_energyLossPar = m_WZphysD3PD->mu_muid_energyLossPar;
	analysisSkeleton::mu_energyLossErr = m_WZphysD3PD->mu_muid_energyLossErr;
	analysisSkeleton::mu_etCore = m_WZphysD3PD->mu_muid_etCore;
	analysisSkeleton::mu_energyLossType = m_WZphysD3PD->mu_muid_energyLossType;
	analysisSkeleton::mu_caloMuonIdTag = m_WZphysD3PD->mu_muid_caloMuonIdTag;
	analysisSkeleton::mu_caloLRLikelihood = m_WZphysD3PD->mu_muid_caloLRLikelihood;
	analysisSkeleton::mu_bestMatch = m_WZphysD3PD->mu_muid_bestMatch;
	analysisSkeleton::mu_isStandAloneMuon = m_WZphysD3PD->mu_muid_isStandAloneMuon;
	analysisSkeleton::mu_isCombinedMuon = m_WZphysD3PD->mu_muid_isCombinedMuon;
	analysisSkeleton::mu_isLowPtReconstructedMuon = m_WZphysD3PD->mu_muid_isLowPtReconstructedMuon;
	analysisSkeleton::mu_loose = m_WZphysD3PD->mu_muid_loose;
	analysisSkeleton::mu_medium = m_WZphysD3PD->mu_muid_medium;
	analysisSkeleton::mu_tight = m_WZphysD3PD->mu_muid_tight;
	analysisSkeleton::mu_d0_exPV = m_WZphysD3PD->mu_muid_d0_exPV;
	analysisSkeleton::mu_z0_exPV = m_WZphysD3PD->mu_muid_z0_exPV;
	analysisSkeleton::mu_phi_exPV = m_WZphysD3PD->mu_muid_phi_exPV;
	analysisSkeleton::mu_theta_exPV = m_WZphysD3PD->mu_muid_theta_exPV;
	analysisSkeleton::mu_qoverp_exPV = m_WZphysD3PD->mu_muid_qoverp_exPV;
	analysisSkeleton::mu_cb_d0_exPV = m_WZphysD3PD->mu_muid_cb_d0_exPV;
	analysisSkeleton::mu_cb_z0_exPV = m_WZphysD3PD->mu_muid_cb_z0_exPV;
	analysisSkeleton::mu_cb_phi_exPV = m_WZphysD3PD->mu_muid_cb_phi_exPV;
	analysisSkeleton::mu_cb_theta_exPV = m_WZphysD3PD->mu_muid_cb_theta_exPV;
	analysisSkeleton::mu_cb_qoverp_exPV = m_WZphysD3PD->mu_muid_cb_qoverp_exPV;
	analysisSkeleton::mu_id_d0_exPV = m_WZphysD3PD->mu_muid_id_d0_exPV;
	analysisSkeleton::mu_id_z0_exPV = m_WZphysD3PD->mu_muid_id_z0_exPV;
	analysisSkeleton::mu_id_phi_exPV = m_WZphysD3PD->mu_muid_id_phi_exPV;
	analysisSkeleton::mu_id_theta_exPV = m_WZphysD3PD->mu_muid_id_theta_exPV;
	analysisSkeleton::mu_id_qoverp_exPV = m_WZphysD3PD->mu_muid_id_qoverp_exPV;
	analysisSkeleton::mu_me_d0_exPV = m_WZphysD3PD->mu_muid_me_d0_exPV;
	analysisSkeleton::mu_me_z0_exPV = m_WZphysD3PD->mu_muid_me_z0_exPV;
	analysisSkeleton::mu_me_phi_exPV = m_WZphysD3PD->mu_muid_me_phi_exPV;
	analysisSkeleton::mu_me_theta_exPV = m_WZphysD3PD->mu_muid_me_theta_exPV;
	analysisSkeleton::mu_me_qoverp_exPV = m_WZphysD3PD->mu_muid_me_qoverp_exPV;
	analysisSkeleton::mu_ie_d0_exPV = m_WZphysD3PD->mu_muid_ie_d0_exPV;
	analysisSkeleton::mu_ie_z0_exPV = m_WZphysD3PD->mu_muid_ie_z0_exPV;
	analysisSkeleton::mu_ie_phi_exPV = m_WZphysD3PD->mu_muid_ie_phi_exPV;
	analysisSkeleton::mu_ie_theta_exPV = m_WZphysD3PD->mu_muid_ie_theta_exPV;
	analysisSkeleton::mu_ie_qoverp_exPV = m_WZphysD3PD->mu_muid_ie_qoverp_exPV;
	analysisSkeleton::mu_SpaceTime_detID = m_WZphysD3PD->mu_muid_SpaceTime_detID;
	analysisSkeleton::mu_SpaceTime_t = m_WZphysD3PD->mu_muid_SpaceTime_t;
	analysisSkeleton::mu_SpaceTime_tError = m_WZphysD3PD->mu_muid_SpaceTime_tError;
	analysisSkeleton::mu_SpaceTime_weight = m_WZphysD3PD->mu_muid_SpaceTime_weight;
	analysisSkeleton::mu_SpaceTime_x = m_WZphysD3PD->mu_muid_SpaceTime_x;
	analysisSkeleton::mu_SpaceTime_y = m_WZphysD3PD->mu_muid_SpaceTime_y;
	analysisSkeleton::mu_SpaceTime_z = m_WZphysD3PD->mu_muid_SpaceTime_z;
/*	analysisSkeleton::mu_SpaceTime_t_Tile = m_WZphysD3PD->mu_muid_SpaceTime_t_Tile;
	analysisSkeleton::mu_SpaceTime_tError_Tile = m_WZphysD3PD->mu_muid_SpaceTime_tError_Tile;
	analysisSkeleton::mu_SpaceTime_weight_Tile = m_WZphysD3PD->mu_muid_SpaceTime_weight_Tile;
	analysisSkeleton::mu_SpaceTime_x_Tile = m_WZphysD3PD->mu_muid_SpaceTime_x_Tile;
	analysisSkeleton::mu_SpaceTime_y_Tile = m_WZphysD3PD->mu_muid_SpaceTime_y_Tile;
	analysisSkeleton::mu_SpaceTime_z_Tile = m_WZphysD3PD->mu_muid_SpaceTime_z_Tile;
	analysisSkeleton::mu_SpaceTime_t_TRT = m_WZphysD3PD->mu_muid_SpaceTime_t_TRT;
	analysisSkeleton::mu_SpaceTime_tError_TRT = m_WZphysD3PD->mu_muid_SpaceTime_tError_TRT;
	analysisSkeleton::mu_SpaceTime_weight_TRT = m_WZphysD3PD->mu_muid_SpaceTime_weight_TRT;
	analysisSkeleton::mu_SpaceTime_x_TRT = m_WZphysD3PD->mu_muid_SpaceTime_x_TRT;
	analysisSkeleton::mu_SpaceTime_y_TRT = m_WZphysD3PD->mu_muid_SpaceTime_y_TRT;
	analysisSkeleton::mu_SpaceTime_z_TRT = m_WZphysD3PD->mu_muid_SpaceTime_z_TRT;
	analysisSkeleton::mu_SpaceTime_t_MDT = m_WZphysD3PD->mu_muid_SpaceTime_t_MDT;
	analysisSkeleton::mu_SpaceTime_tError_MDT = m_WZphysD3PD->mu_muid_SpaceTime_tError_MDT;
	analysisSkeleton::mu_SpaceTime_weight_MDT = m_WZphysD3PD->mu_muid_SpaceTime_weight_MDT;
	analysisSkeleton::mu_SpaceTime_x_MDT = m_WZphysD3PD->mu_muid_SpaceTime_x_MDT;
	analysisSkeleton::mu_SpaceTime_y_MDT = m_WZphysD3PD->mu_muid_SpaceTime_y_MDT;
	analysisSkeleton::mu_SpaceTime_z_MDT = m_WZphysD3PD->mu_muid_SpaceTime_z_MDT;
	analysisSkeleton::mu_TileCellEnergyLayer1 = m_WZphysD3PD->mu_muid_TileCellEnergyLayer1;
	analysisSkeleton::mu_TileTimeLayer1 = m_WZphysD3PD->mu_muid_TileTimeLayer1;
	analysisSkeleton::mu_TileCellRmsNoiseLayer1 = m_WZphysD3PD->mu_muid_TileCellRmsNoiseLayer1;
	analysisSkeleton::mu_TileCellSignLayer1 = m_WZphysD3PD->mu_muid_TileCellSignLayer1;
	analysisSkeleton::mu_TileCellEnergyLayer2 = m_WZphysD3PD->mu_muid_TileCellEnergyLayer2;
	analysisSkeleton::mu_TileTimeLayer2 = m_WZphysD3PD->mu_muid_TileTimeLayer2;
	analysisSkeleton::mu_TileCellRmsNoiseLayer2 = m_WZphysD3PD->mu_muid_TileCellRmsNoiseLayer2;
	analysisSkeleton::mu_TileCellSignLayer2 = m_WZphysD3PD->mu_muid_TileCellSignLayer2;
	analysisSkeleton::mu_TileCellEnergyLayer3 = m_WZphysD3PD->mu_muid_TileCellEnergyLayer3;
	analysisSkeleton::mu_TileTimeLayer3 = m_WZphysD3PD->mu_muid_TileTimeLayer3;
	analysisSkeleton::mu_TileCellRmsNoiseLayer3 = m_WZphysD3PD->mu_muid_TileCellRmsNoiseLayer3;
	analysisSkeleton::mu_TileCellSignLayer3 = m_WZphysD3PD->mu_muid_TileCellSignLayer3;
	analysisSkeleton::mu_MSTrkT0_1 = m_WZphysD3PD->mu_muid_MSTrkT0_1;
	analysisSkeleton::mu_MSTrkT0_2 = m_WZphysD3PD->mu_muid_MSTrkT0_2;
	analysisSkeleton::mu_MSTrkT0_3 = m_WZphysD3PD->mu_muid_MSTrkT0_3;
*/
	analysisSkeleton::mu_cov_d0_exPV = m_WZphysD3PD->mu_muid_cov_d0_exPV;
	analysisSkeleton::mu_cov_z0_exPV = m_WZphysD3PD->mu_muid_cov_z0_exPV;
	analysisSkeleton::mu_cov_phi_exPV = m_WZphysD3PD->mu_muid_cov_phi_exPV;
	analysisSkeleton::mu_cov_theta_exPV = m_WZphysD3PD->mu_muid_cov_theta_exPV;
	analysisSkeleton::mu_cov_qoverp_exPV = m_WZphysD3PD->mu_muid_cov_qoverp_exPV;
	analysisSkeleton::mu_cov_d0_z0_exPV = m_WZphysD3PD->mu_muid_cov_d0_z0_exPV;
	analysisSkeleton::mu_cov_d0_phi_exPV = m_WZphysD3PD->mu_muid_cov_d0_phi_exPV;
	analysisSkeleton::mu_cov_d0_theta_exPV = m_WZphysD3PD->mu_muid_cov_d0_theta_exPV;
	analysisSkeleton::mu_cov_d0_qoverp_exPV = m_WZphysD3PD->mu_muid_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_cov_z0_phi_exPV = m_WZphysD3PD->mu_muid_cov_z0_phi_exPV;
	analysisSkeleton::mu_cov_z0_theta_exPV = m_WZphysD3PD->mu_muid_cov_z0_theta_exPV;
	analysisSkeleton::mu_cov_z0_qoverp_exPV = m_WZphysD3PD->mu_muid_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_cov_phi_theta_exPV = m_WZphysD3PD->mu_muid_cov_phi_theta_exPV;
	analysisSkeleton::mu_cov_phi_qoverp_exPV = m_WZphysD3PD->mu_muid_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_cov_theta_qoverp_exPV = m_WZphysD3PD->mu_muid_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_id_cov_d0_exPV = m_WZphysD3PD->mu_muid_id_cov_d0_exPV;
	analysisSkeleton::mu_id_cov_z0_exPV = m_WZphysD3PD->mu_muid_id_cov_z0_exPV;
	analysisSkeleton::mu_id_cov_phi_exPV = m_WZphysD3PD->mu_muid_id_cov_phi_exPV;
	analysisSkeleton::mu_id_cov_theta_exPV = m_WZphysD3PD->mu_muid_id_cov_theta_exPV;
	analysisSkeleton::mu_id_cov_qoverp_exPV = m_WZphysD3PD->mu_muid_id_cov_qoverp_exPV;
	analysisSkeleton::mu_id_cov_d0_z0_exPV = m_WZphysD3PD->mu_muid_id_cov_d0_z0_exPV;
	analysisSkeleton::mu_id_cov_d0_phi_exPV = m_WZphysD3PD->mu_muid_id_cov_d0_phi_exPV;
	analysisSkeleton::mu_id_cov_d0_theta_exPV = m_WZphysD3PD->mu_muid_id_cov_d0_theta_exPV;
	analysisSkeleton::mu_id_cov_d0_qoverp_exPV = m_WZphysD3PD->mu_muid_id_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_id_cov_z0_phi_exPV = m_WZphysD3PD->mu_muid_id_cov_z0_phi_exPV;
	analysisSkeleton::mu_id_cov_z0_theta_exPV = m_WZphysD3PD->mu_muid_id_cov_z0_theta_exPV;
	analysisSkeleton::mu_id_cov_z0_qoverp_exPV = m_WZphysD3PD->mu_muid_id_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_id_cov_phi_theta_exPV = m_WZphysD3PD->mu_muid_id_cov_phi_theta_exPV;
	analysisSkeleton::mu_id_cov_phi_qoverp_exPV = m_WZphysD3PD->mu_muid_id_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_id_cov_theta_qoverp_exPV = m_WZphysD3PD->mu_muid_id_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_me_cov_d0_exPV = m_WZphysD3PD->mu_muid_me_cov_d0_exPV;
	analysisSkeleton::mu_me_cov_z0_exPV = m_WZphysD3PD->mu_muid_me_cov_z0_exPV;
	analysisSkeleton::mu_me_cov_phi_exPV = m_WZphysD3PD->mu_muid_me_cov_phi_exPV;
	analysisSkeleton::mu_me_cov_theta_exPV = m_WZphysD3PD->mu_muid_me_cov_theta_exPV;
	analysisSkeleton::mu_me_cov_qoverp_exPV = m_WZphysD3PD->mu_muid_me_cov_qoverp_exPV;
	analysisSkeleton::mu_me_cov_d0_z0_exPV = m_WZphysD3PD->mu_muid_me_cov_d0_z0_exPV;
	analysisSkeleton::mu_me_cov_d0_phi_exPV = m_WZphysD3PD->mu_muid_me_cov_d0_phi_exPV;
	analysisSkeleton::mu_me_cov_d0_theta_exPV = m_WZphysD3PD->mu_muid_me_cov_d0_theta_exPV;
	analysisSkeleton::mu_me_cov_d0_qoverp_exPV = m_WZphysD3PD->mu_muid_me_cov_d0_qoverp_exPV;
	analysisSkeleton::mu_me_cov_z0_phi_exPV = m_WZphysD3PD->mu_muid_me_cov_z0_phi_exPV;
	analysisSkeleton::mu_me_cov_z0_theta_exPV = m_WZphysD3PD->mu_muid_me_cov_z0_theta_exPV;
	analysisSkeleton::mu_me_cov_z0_qoverp_exPV = m_WZphysD3PD->mu_muid_me_cov_z0_qoverp_exPV;
	analysisSkeleton::mu_me_cov_phi_theta_exPV = m_WZphysD3PD->mu_muid_me_cov_phi_theta_exPV;
	analysisSkeleton::mu_me_cov_phi_qoverp_exPV = m_WZphysD3PD->mu_muid_me_cov_phi_qoverp_exPV;
	analysisSkeleton::mu_me_cov_theta_qoverp_exPV = m_WZphysD3PD->mu_muid_me_cov_theta_qoverp_exPV;
	analysisSkeleton::mu_ms_d0 = m_WZphysD3PD->mu_muid_ms_d0;
	analysisSkeleton::mu_ms_z0 = m_WZphysD3PD->mu_muid_ms_z0;
	analysisSkeleton::mu_ms_phi = m_WZphysD3PD->mu_muid_ms_phi;
	analysisSkeleton::mu_ms_theta = m_WZphysD3PD->mu_muid_ms_theta;
	analysisSkeleton::mu_ms_qoverp = m_WZphysD3PD->mu_muid_ms_qoverp;
	analysisSkeleton::mu_id_d0 = m_WZphysD3PD->mu_muid_id_d0;
	analysisSkeleton::mu_id_z0 = m_WZphysD3PD->mu_muid_id_z0;
	analysisSkeleton::mu_id_phi = m_WZphysD3PD->mu_muid_id_phi;
	analysisSkeleton::mu_id_theta = m_WZphysD3PD->mu_muid_id_theta;
	analysisSkeleton::mu_id_qoverp = m_WZphysD3PD->mu_muid_id_qoverp;
	analysisSkeleton::mu_me_d0 = m_WZphysD3PD->mu_muid_me_d0;
	analysisSkeleton::mu_me_z0 = m_WZphysD3PD->mu_muid_me_z0;
	analysisSkeleton::mu_me_phi = m_WZphysD3PD->mu_muid_me_phi;
	analysisSkeleton::mu_me_theta = m_WZphysD3PD->mu_muid_me_theta;
	analysisSkeleton::mu_me_qoverp = m_WZphysD3PD->mu_muid_me_qoverp;
	analysisSkeleton::mu_ie_d0 = m_WZphysD3PD->mu_muid_ie_d0;
	analysisSkeleton::mu_ie_z0 = m_WZphysD3PD->mu_muid_ie_z0;
	analysisSkeleton::mu_ie_phi = m_WZphysD3PD->mu_muid_ie_phi;
	analysisSkeleton::mu_ie_theta = m_WZphysD3PD->mu_muid_ie_theta;
	analysisSkeleton::mu_ie_qoverp = m_WZphysD3PD->mu_muid_ie_qoverp;
	analysisSkeleton::mu_nOutliersOnTrack = m_WZphysD3PD->mu_muid_nOutliersOnTrack;
	analysisSkeleton::mu_nBLHits = m_WZphysD3PD->mu_muid_nBLHits;
	analysisSkeleton::mu_nPixHits = m_WZphysD3PD->mu_muid_nPixHits;
	analysisSkeleton::mu_nSCTHits = m_WZphysD3PD->mu_muid_nSCTHits;
	analysisSkeleton::mu_nTRTHits = m_WZphysD3PD->mu_muid_nTRTHits;
	analysisSkeleton::mu_nTRTHighTHits = m_WZphysD3PD->mu_muid_nTRTHighTHits;
	analysisSkeleton::mu_nBLSharedHits = m_WZphysD3PD->mu_muid_nBLSharedHits;
	analysisSkeleton::mu_nPixSharedHits = m_WZphysD3PD->mu_muid_nPixSharedHits;
	analysisSkeleton::mu_nPixHoles = m_WZphysD3PD->mu_muid_nPixHoles;
	analysisSkeleton::mu_nSCTSharedHits = m_WZphysD3PD->mu_muid_nSCTSharedHits;
	analysisSkeleton::mu_nSCTHoles = m_WZphysD3PD->mu_muid_nSCTHoles;
	analysisSkeleton::mu_nTRTOutliers = m_WZphysD3PD->mu_muid_nTRTOutliers;
	analysisSkeleton::mu_nTRTHighTOutliers = m_WZphysD3PD->mu_muid_nTRTHighTOutliers;
	analysisSkeleton::mu_nGangedPixels = m_WZphysD3PD->mu_muid_nGangedPixels;
	analysisSkeleton::mu_nPixelDeadSensors = m_WZphysD3PD->mu_muid_nPixelDeadSensors;
	analysisSkeleton::mu_nSCTDeadSensors = m_WZphysD3PD->mu_muid_nSCTDeadSensors;
	analysisSkeleton::mu_nTRTDeadStraws = m_WZphysD3PD->mu_muid_nTRTDeadStraws;
	analysisSkeleton::mu_expectBLayerHit = m_WZphysD3PD->mu_muid_expectBLayerHit;
	analysisSkeleton::mu_nMDTHits = m_WZphysD3PD->mu_muid_nMDTHits;
	analysisSkeleton::mu_nMDTHoles = m_WZphysD3PD->mu_muid_nMDTHoles;
	analysisSkeleton::mu_nCSCEtaHits = m_WZphysD3PD->mu_muid_nCSCEtaHits;
	analysisSkeleton::mu_nCSCEtaHoles = m_WZphysD3PD->mu_muid_nCSCEtaHoles;
	analysisSkeleton::mu_nCSCPhiHits = m_WZphysD3PD->mu_muid_nCSCPhiHits;
	analysisSkeleton::mu_nCSCPhiHoles = m_WZphysD3PD->mu_muid_nCSCPhiHoles;
	analysisSkeleton::mu_nRPCEtaHits = m_WZphysD3PD->mu_muid_nRPCEtaHits;
	analysisSkeleton::mu_nRPCEtaHoles = m_WZphysD3PD->mu_muid_nRPCEtaHoles;
	analysisSkeleton::mu_nRPCPhiHits = m_WZphysD3PD->mu_muid_nRPCPhiHits;
	analysisSkeleton::mu_nRPCPhiHoles = m_WZphysD3PD->mu_muid_nRPCPhiHoles;
	analysisSkeleton::mu_nTGCEtaHits = m_WZphysD3PD->mu_muid_nTGCEtaHits;
	analysisSkeleton::mu_nTGCEtaHoles = m_WZphysD3PD->mu_muid_nTGCEtaHoles;
	analysisSkeleton::mu_nTGCPhiHits = m_WZphysD3PD->mu_muid_nTGCPhiHits;
	analysisSkeleton::mu_nTGCPhiHoles = m_WZphysD3PD->mu_muid_nTGCPhiHoles;
	analysisSkeleton::mu_nMDTBIHits = m_WZphysD3PD->mu_muid_nMDTBIHits;
	analysisSkeleton::mu_nMDTBMHits = m_WZphysD3PD->mu_muid_nMDTBMHits;
	analysisSkeleton::mu_nMDTBOHits = m_WZphysD3PD->mu_muid_nMDTBOHits;
	analysisSkeleton::mu_nMDTBEEHits = m_WZphysD3PD->mu_muid_nMDTBEEHits;
	analysisSkeleton::mu_nMDTBIS78Hits = m_WZphysD3PD->mu_muid_nMDTBIS78Hits;
	analysisSkeleton::mu_nMDTEIHits = m_WZphysD3PD->mu_muid_nMDTEIHits;
	analysisSkeleton::mu_nMDTEMHits = m_WZphysD3PD->mu_muid_nMDTEMHits;
	analysisSkeleton::mu_nMDTEOHits = m_WZphysD3PD->mu_muid_nMDTEOHits;
	analysisSkeleton::mu_nMDTEEHits = m_WZphysD3PD->mu_muid_nMDTEEHits;
	analysisSkeleton::mu_nRPCLayer1EtaHits = m_WZphysD3PD->mu_muid_nRPCLayer1EtaHits;
	analysisSkeleton::mu_nRPCLayer2EtaHits = m_WZphysD3PD->mu_muid_nRPCLayer2EtaHits;
	analysisSkeleton::mu_nRPCLayer3EtaHits = m_WZphysD3PD->mu_muid_nRPCLayer3EtaHits;
	analysisSkeleton::mu_nRPCLayer1PhiHits = m_WZphysD3PD->mu_muid_nRPCLayer1PhiHits;
	analysisSkeleton::mu_nRPCLayer2PhiHits = m_WZphysD3PD->mu_muid_nRPCLayer2PhiHits;
	analysisSkeleton::mu_nRPCLayer3PhiHits = m_WZphysD3PD->mu_muid_nRPCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer1EtaHits = m_WZphysD3PD->mu_muid_nTGCLayer1EtaHits;
	analysisSkeleton::mu_nTGCLayer2EtaHits = m_WZphysD3PD->mu_muid_nTGCLayer2EtaHits;
	analysisSkeleton::mu_nTGCLayer3EtaHits = m_WZphysD3PD->mu_muid_nTGCLayer3EtaHits;
	analysisSkeleton::mu_nTGCLayer4EtaHits = m_WZphysD3PD->mu_muid_nTGCLayer4EtaHits;
	analysisSkeleton::mu_nTGCLayer1PhiHits = m_WZphysD3PD->mu_muid_nTGCLayer1PhiHits;
	analysisSkeleton::mu_nTGCLayer2PhiHits = m_WZphysD3PD->mu_muid_nTGCLayer2PhiHits;
	analysisSkeleton::mu_nTGCLayer3PhiHits = m_WZphysD3PD->mu_muid_nTGCLayer3PhiHits;
	analysisSkeleton::mu_nTGCLayer4PhiHits = m_WZphysD3PD->mu_muid_nTGCLayer4PhiHits;
	analysisSkeleton::mu_barrelSectors = m_WZphysD3PD->mu_muid_barrelSectors;
	analysisSkeleton::mu_endcapSectors = m_WZphysD3PD->mu_muid_endcapSectors;
	analysisSkeleton::mu_trackd0 = m_WZphysD3PD->mu_muid_trackd0;
	analysisSkeleton::mu_trackz0 = m_WZphysD3PD->mu_muid_trackz0;
	analysisSkeleton::mu_trackphi = m_WZphysD3PD->mu_muid_trackphi;
	analysisSkeleton::mu_tracktheta = m_WZphysD3PD->mu_muid_tracktheta;
	analysisSkeleton::mu_trackqoverp = m_WZphysD3PD->mu_muid_trackqoverp;
	analysisSkeleton::mu_trackcov_d0 = m_WZphysD3PD->mu_muid_trackcov_d0;
	analysisSkeleton::mu_trackcov_z0 = m_WZphysD3PD->mu_muid_trackcov_z0;
	analysisSkeleton::mu_trackcov_phi = m_WZphysD3PD->mu_muid_trackcov_phi;
	analysisSkeleton::mu_trackcov_theta = m_WZphysD3PD->mu_muid_trackcov_theta;
	analysisSkeleton::mu_trackcov_qoverp = m_WZphysD3PD->mu_muid_trackcov_qoverp;
	analysisSkeleton::mu_trackcov_d0_z0 = m_WZphysD3PD->mu_muid_trackcov_d0_z0;
	analysisSkeleton::mu_trackcov_d0_phi = m_WZphysD3PD->mu_muid_trackcov_d0_phi;
	analysisSkeleton::mu_trackcov_d0_theta = m_WZphysD3PD->mu_muid_trackcov_d0_theta;
	analysisSkeleton::mu_trackcov_d0_qoverp = m_WZphysD3PD->mu_muid_trackcov_d0_qoverp;
	analysisSkeleton::mu_trackcov_z0_phi = m_WZphysD3PD->mu_muid_trackcov_z0_phi;
	analysisSkeleton::mu_trackcov_z0_theta = m_WZphysD3PD->mu_muid_trackcov_z0_theta;
	analysisSkeleton::mu_trackcov_z0_qoverp = m_WZphysD3PD->mu_muid_trackcov_z0_qoverp;
	analysisSkeleton::mu_trackcov_phi_theta = m_WZphysD3PD->mu_muid_trackcov_phi_theta;
	analysisSkeleton::mu_trackcov_phi_qoverp = m_WZphysD3PD->mu_muid_trackcov_phi_qoverp;
	analysisSkeleton::mu_trackcov_theta_qoverp = m_WZphysD3PD->mu_muid_trackcov_theta_qoverp;
	analysisSkeleton::mu_trackfitchi2 = m_WZphysD3PD->mu_muid_trackfitchi2;
	analysisSkeleton::mu_trackfitndof = m_WZphysD3PD->mu_muid_trackfitndof;
	analysisSkeleton::mu_hastrack = m_WZphysD3PD->mu_muid_hastrack;
	if(m_isMC)
	{
		analysisSkeleton::mu_truth_dr = m_WZphysD3PD->mu_muid_truth_dr;
		analysisSkeleton::mu_truth_E = m_WZphysD3PD->mu_muid_truth_E;
		analysisSkeleton::mu_truth_pt = m_WZphysD3PD->mu_muid_truth_pt;
		analysisSkeleton::mu_truth_eta = m_WZphysD3PD->mu_muid_truth_eta;
		analysisSkeleton::mu_truth_phi = m_WZphysD3PD->mu_muid_truth_phi;
		analysisSkeleton::mu_truth_type = m_WZphysD3PD->mu_muid_truth_type;
		analysisSkeleton::mu_truth_status = m_WZphysD3PD->mu_muid_truth_status;
		analysisSkeleton::mu_truth_barcode = m_WZphysD3PD->mu_muid_truth_barcode;
		analysisSkeleton::mu_truth_mothertype = m_WZphysD3PD->mu_muid_truth_mothertype;
		analysisSkeleton::mu_truth_motherbarcode = m_WZphysD3PD->mu_muid_truth_motherbarcode;
		analysisSkeleton::mu_truth_matched = m_WZphysD3PD->mu_muid_truth_matched;
	}
	analysisSkeleton::mu_EFCB_dr = m_WZphysD3PD->mu_muid_EFCB_dr;
	analysisSkeleton::mu_EFCB_index = m_WZphysD3PD->mu_muid_EFCB_index;
	analysisSkeleton::mu_EFMG_dr = m_WZphysD3PD->mu_muid_EFMG_dr;
	analysisSkeleton::mu_EFMG_index = m_WZphysD3PD->mu_muid_EFMG_index;
	analysisSkeleton::mu_EFME_dr = m_WZphysD3PD->mu_muid_EFME_dr;
	analysisSkeleton::mu_EFME_index = m_WZphysD3PD->mu_muid_EFME_index;
	analysisSkeleton::mu_L2CB_dr = m_WZphysD3PD->mu_muid_L2CB_dr;
	analysisSkeleton::mu_L2CB_index = m_WZphysD3PD->mu_muid_L2CB_index;
	analysisSkeleton::mu_L1_dr = m_WZphysD3PD->mu_muid_L1_dr;
	analysisSkeleton::mu_L1_index = m_WZphysD3PD->mu_muid_L1_index;
}

void analysis::setTrigVariables()
{
	_DEBUG("analysis::setTrigVariables");

	analysisSkeleton::trig_L1_mu_n = m_WZphysD3PD->trig_L1_mu_n;
	analysisSkeleton::trig_L1_mu_pt = m_WZphysD3PD->trig_L1_mu_pt;
	analysisSkeleton::trig_L1_mu_eta = m_WZphysD3PD->trig_L1_mu_eta;
	analysisSkeleton::trig_L1_mu_phi = m_WZphysD3PD->trig_L1_mu_phi;
	analysisSkeleton::trig_L1_mu_thrName = m_WZphysD3PD->trig_L1_mu_thrName;

	analysisSkeleton::trig_EF_trigmuonef_n = m_WZphysD3PD->trig_EF_trigmuonef_n;
	analysisSkeleton::trig_EF_trigmuonef_track_n = m_WZphysD3PD->trig_EF_trigmuonef_track_n;
	analysisSkeleton::trig_EF_trigmuonef_track_MuonType = m_WZphysD3PD->trig_EF_trigmuonef_track_MuonType;
	analysisSkeleton::trig_EF_trigmuonef_track_MS_pt = m_WZphysD3PD->trig_EF_trigmuonef_track_MS_pt;
	analysisSkeleton::trig_EF_trigmuonef_track_MS_eta = m_WZphysD3PD->trig_EF_trigmuonef_track_MS_eta;
	analysisSkeleton::trig_EF_trigmuonef_track_MS_phi = m_WZphysD3PD->trig_EF_trigmuonef_track_MS_phi;
	analysisSkeleton::trig_EF_trigmuonef_track_MS_hasMS = m_WZphysD3PD->trig_EF_trigmuonef_track_MS_hasMS;
	analysisSkeleton::trig_EF_trigmuonef_track_SA_pt = m_WZphysD3PD->trig_EF_trigmuonef_track_SA_pt;
	analysisSkeleton::trig_EF_trigmuonef_track_SA_eta = m_WZphysD3PD->trig_EF_trigmuonef_track_SA_eta;
	analysisSkeleton::trig_EF_trigmuonef_track_SA_phi = m_WZphysD3PD->trig_EF_trigmuonef_track_SA_phi;
	analysisSkeleton::trig_EF_trigmuonef_track_SA_hasSA = m_WZphysD3PD->trig_EF_trigmuonef_track_SA_hasSA;
	analysisSkeleton::trig_EF_trigmuonef_track_CB_pt = m_WZphysD3PD->trig_EF_trigmuonef_track_CB_pt;
	analysisSkeleton::trig_EF_trigmuonef_track_CB_eta = m_WZphysD3PD->trig_EF_trigmuonef_track_CB_eta;
	analysisSkeleton::trig_EF_trigmuonef_track_CB_phi = m_WZphysD3PD->trig_EF_trigmuonef_track_CB_phi;
	analysisSkeleton::trig_EF_trigmuonef_track_CB_hasCB = m_WZphysD3PD->trig_EF_trigmuonef_track_CB_hasCB;
	
	/*
	(*f) << "\n---------- run=" << analysisSkeleton::RunNumber << ", evt=" << analysisSkeleton::EventNumber << " ----------" << endl;
	int L1roi   = 0;
	int EFCBroi = 0;
	float pTthr = 10.; // GeV
	for(int i=0 ; i<(int)mu_pt->size() ; i++)
	{
		L1roi = tagNprobe::matchLXtrigger(analysisSkeleton::mu_L1_index->at(i),
							   analysisSkeleton::mu_L1_dr->at(i),
							   analysisSkeleton::mu_phi->at(i),
							   analysisSkeleton::mu_eta->at(i),
							   pTthr,
							   analysisSkeleton::trig_L1_mu_phi,
							   analysisSkeleton::trig_L1_mu_eta,
							   analysisSkeleton::trig_L1_mu_pt,
							   analysisSkeleton::trig_L1_mu_thrName, f);
		if(L1roi>=0)   (*f) << "[" << i << "] L1 matched to pT="     << pTthr << " (pT=" << analysisSkeleton::trig_L1_mu_pt->at(L1roi) << "), mu_dr=" << analysisSkeleton::mu_L1_dr->at(i) << endl;
		else           (*f) << "[" << i << "] L1 NOT matched to pT=" << pTthr << endl;
		EFCBroi = tagNprobe::matchEFtrigger(analysisSkeleton::mu_EFCB_index->at(i),
							   analysisSkeleton::mu_EFCB_dr->at(i),
							   analysisSkeleton::mu_phi->at(i),
							   analysisSkeleton::mu_eta->at(i),
							   pTthr,
							   analysisSkeleton::trig_EF_trigmuonef_track_CB_phi,
							   analysisSkeleton::trig_EF_trigmuonef_track_CB_eta,
							   analysisSkeleton::trig_EF_trigmuonef_track_CB_pt,
							   analysisSkeleton::trig_EF_trigmuonef_track_CB_hasCB, f);
		if(EFCBroi>=0) (*f) << "[" << i << "] EFCB matched to pT="     << pTthr << " (pT=" << analysisSkeleton::trig_EF_trigmuonef_track_CB_pt->at(analysisSkeleton::mu_EFCB_index->at(i))[EFCBroi] << "), mu_dr=" << analysisSkeleton::mu_EFCB_dr->at(i) << endl;
		else           (*f) << "[" << i << "] EFCB NOT matched to pT=" << pTthr << endl;
	}
	(*f) << "---------------------------------------------" << endl;
	*/
	
	/*
	(*f) << "\n---------- run=" << analysisSkeleton::RunNumber << ", evt=" << analysisSkeleton::EventNumber << " ----------" << endl;
	(*f) << "mu_n=" << analysisSkeleton::mu_n << endl;
	for(int i=0 ; i<(int)analysisSkeleton::mu_L1_dr->size() ; i++)
	{
		(*f) << "mu_L1_dr[" << i << "]=" << analysisSkeleton::mu_L1_dr->at(i) << endl;
		(*f) << "mu_L1_index[" << i << "]=" << analysisSkeleton::mu_L1_index->at(i) << endl;
	}
	(*f) << "trig_L1_mu_n=" << analysisSkeleton::trig_L1_mu_n << endl;
	for(int i=0 ; i<(int)analysisSkeleton::trig_L1_mu_pt->size() ; i++)
	{
		(*f) << "trig_L1_mu_pt[" << i << "]=" << analysisSkeleton::trig_L1_mu_pt->at(i) << endl;
		(*f) << "trig_L1_mu_thrName[" << i << "]=" << analysisSkeleton::trig_L1_mu_thrName->at(i) << endl;
	}
	for(int i=0 ; i<(int)analysisSkeleton::mu_EFCB_dr->size() ; i++)
	{
		(*f) << "mu_EFCB_dr[" << i << "]=" << analysisSkeleton::mu_EFCB_dr->at(i) << endl;
		(*f) << "mu_EFCB_index[" << i << "]=" << analysisSkeleton::mu_EFCB_index->at(i) << endl;
	}
	(*f) << "trig_EF_trigmuonef_n=" << analysisSkeleton::trig_EF_trigmuonef_n << endl;
	for(int i=0 ; i<(int)analysisSkeleton::trig_EF_trigmuonef_track_n->size() ; i++)
	{
		(*f) << "trig_EF_trigmuonef_track_n[" << i << "]=" << analysisSkeleton::trig_EF_trigmuonef_track_n->at(i) << endl;
		for(int j=0 ; j<(int)analysisSkeleton::trig_EF_trigmuonef_track_MuonType->at(i).size() ; j++)
		{
			(*f) << "trig_EF_trigmuonef_track_MuonType[" << i << "][" << j << "]=" << analysisSkeleton::trig_EF_trigmuonef_track_MuonType->at(i)[j] << endl;
			(*f) << "trig_EF_trigmuonef_track_CB_hasCB[" << i << "][" << j << "]=" << analysisSkeleton::trig_EF_trigmuonef_track_CB_hasCB->at(i)[j] << endl;
			(*f) << "trig_EF_trigmuonef_track_CB_pt["    << i << "][" << j << "]=" << analysisSkeleton::trig_EF_trigmuonef_track_CB_pt->at(i)[j] << endl;
		}
	}
	(*f) << "---------------------------------------------" << endl;
	*/
	
	analysisSkeleton::trig_EF_trigmugirl_n = m_WZphysD3PD->trig_EF_trigmugirl_n;
	analysisSkeleton::trig_EF_trigmugirl_track_n = m_WZphysD3PD->trig_EF_trigmugirl_track_n;
	analysisSkeleton::trig_EF_trigmugirl_track_MuonType = m_WZphysD3PD->trig_EF_trigmugirl_track_MuonType;
	analysisSkeleton::trig_EF_trigmugirl_track_MS_pt = m_WZphysD3PD->trig_EF_trigmugirl_track_MS_pt;
	analysisSkeleton::trig_EF_trigmugirl_track_MS_eta = m_WZphysD3PD->trig_EF_trigmugirl_track_MS_eta;
	analysisSkeleton::trig_EF_trigmugirl_track_MS_phi = m_WZphysD3PD->trig_EF_trigmugirl_track_MS_phi;
	analysisSkeleton::trig_EF_trigmugirl_track_MS_hasMS = m_WZphysD3PD->trig_EF_trigmugirl_track_MS_hasMS;
	analysisSkeleton::trig_EF_trigmugirl_track_SA_pt = m_WZphysD3PD->trig_EF_trigmugirl_track_SA_pt;
	analysisSkeleton::trig_EF_trigmugirl_track_SA_eta = m_WZphysD3PD->trig_EF_trigmugirl_track_SA_eta;
	analysisSkeleton::trig_EF_trigmugirl_track_SA_phi = m_WZphysD3PD->trig_EF_trigmugirl_track_SA_phi;
	analysisSkeleton::trig_EF_trigmugirl_track_SA_hasSA = m_WZphysD3PD->trig_EF_trigmugirl_track_SA_hasSA;
	analysisSkeleton::trig_EF_trigmugirl_track_CB_pt = m_WZphysD3PD->trig_EF_trigmugirl_track_CB_pt;
	analysisSkeleton::trig_EF_trigmugirl_track_CB_eta = m_WZphysD3PD->trig_EF_trigmugirl_track_CB_eta;
	analysisSkeleton::trig_EF_trigmugirl_track_CB_phi = m_WZphysD3PD->trig_EF_trigmugirl_track_CB_phi;
	analysisSkeleton::trig_EF_trigmugirl_track_CB_hasCB = m_WZphysD3PD->trig_EF_trigmugirl_track_CB_hasCB;
}

void analysis::write()
{
	_DEBUG("analysis::write");

	if(m_treeFile!=NULL)
	{
		m_treeFile->cd();
		m_WZphysD3PDmaker->write();
	}
}

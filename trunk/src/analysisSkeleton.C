
/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisSkeleton.h"

analysisSkeleton::analysisSkeleton()
{
	nMultiMuonEvents = 0;
}

analysisSkeleton::~analysisSkeleton()
{
	fCand->close();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void analysisSkeleton::resetMuQAflags(int nMus)
{
	if(muQAflags.size()>0)      muQAflags.clear();
	for(int n=0 ; n<nMus ; n++) muQAflags.push_back(true);
}

string analysisSkeleton::getPeriodName()
{
	string speriod = sCurrentPeriod;
	if(RunNumber != currentRun)
	{
		speriod = getPeriod( RunNumber, m_firstrun2periodMap, m_lastrun2periodMap );
		cout << "switching to period: " << speriod << endl;
		currentRun     = RunNumber;
		sCurrentPeriod = speriod;
	}
	if(speriod=="")
	{
		cout << "ERROR: in analysisSkeleton::getPeriodName -> (speriod==""), exitting now" << endl;
		exit(-1);
	}
	
	return speriod;
}

string analysisSkeleton::getPeriodName(int run)
{
	return getPeriod( run, m_firstrun2periodMap, m_lastrun2periodMap );
}

vector<string>* analysisSkeleton::getPeriodTriggers()
{
	if(sPeriod==""  ||  m_period2triggerMap==NULL)
	{
		cout << "ERROR: in analysisSkeleton::getPeriodTriggers -> (sPeriod=="" || m_period2triggerMap==NULL), exitting now" << endl;
		exit(-1);
	}
	
	return getTrigs(sPeriod, m_period2triggerMap);
}

int analysisSkeleton::isTrigger(string trigName)
{
	if(trigName=="")
	{
		cout << "ERROR: in analysisSkeleton::isTrigger -> (trigName==""), exitting now" << endl;
		exit(-1);
	}
	
	int isTrig = 0;
	if     (trigName=="L1_MU10")          isTrig = L1_MU10;
	else if(trigName=="EF_mu10")          isTrig = EF_mu10;
	else if(trigName=="EF_mu10_MG")       isTrig = EF_mu10_MG;
	else if(trigName=="EF_mu13")          isTrig = EF_mu13;
	else if(trigName=="EF_mu13_MG")       isTrig = EF_mu13_MG;
	else if(trigName=="EF_mu13_tight")    isTrig = EF_mu13_tight;
	else if(trigName=="EF_mu13_MG_tight") isTrig = EF_mu13_MG_tight;
	else cout << "WARNING:  in analysisSkeleton::isTrigger -> the trigger " << trigName << " was not found and the event is regected by default" << endl;
	return isTrig;
}

void analysisSkeleton::matchTrigger(string speriod, string sTrigType)
{
	/*
	EFCB: the trig muon for the regular EF trigger
	EFME: the MSonly trig muons
	EFMG: trig mugirl (_MG type triggers)
	L2CB: combinedmuonfeature (mucomb)
	L1:   the level 1 RoI
	
	For the first two, the trigger block variables are the ones starting
	with trig_EF_trigmuonef_ while for mugirl the trigger variables are trig_EF_trigmugirl_
	The L2 information matches to the trig_L2_combmuonfeature_ blocks and L1 ->trig_L1_mu_
	*/

	if(speriod=="")
	{
		cout << "ERROR: in analysisSkeleton::matchTrigger -> (speriod==""), exitting now" << endl;
		exit(-1);
	}
	
	if
	(
		speriod=="MC" ||
		speriod=="A"  || speriod=="B1-B2" || speriod=="C1" || speriod=="C2" || speriod=="D1-D6" ||
		speriod=="E1" || speriod=="E2"    || speriod=="E3"
	)
	{
		mu_LLT_index = mu_L1_index;
		mu_LLT_dr    = mu_L1_dr;
		LLT_pt       = trig_L1_mu_pt;
		LLT_phi      = trig_L1_mu_phi;
		LLT_eta      = trig_L1_mu_eta;
	}
	
	else if
	(
		speriod=="E4" || speriod=="E5" || speriod=="E6" || speriod=="E7" ||
		speriod=="F1" || speriod=="F2" ||
		speriod=="G1" || speriod=="G2" || speriod=="G3" || speriod=="G4" ||
		speriod=="G5" || speriod=="G6" ||
		speriod=="H1" || speriod=="H2" ||
		speriod=="I1" || speriod=="I2"
	)
	{
		if(sTrigType=="CB")
		{
			mu_HLT_dr = mu_EFCB_dr;
			mu_HLT_index = mu_EFCB_index;
			HLT_pt = trig_EF_trigmuonef_track_CB_pt;
			HLT_phi = trig_EF_trigmuonef_track_CB_phi;
			HLT_eta = trig_EF_trigmuonef_track_CB_eta;
			HLT_has = trig_EF_trigmuonef_track_CB_hasCB;
		}
		else if(sTrigType=="MS")
		{
			mu_HLT_dr = mu_EFME_dr;
			mu_HLT_index = mu_EFME_index;
			HLT_pt = trig_EF_trigmuonef_track_MS_pt;
			HLT_phi = trig_EF_trigmuonef_track_MS_phi;
			HLT_eta = trig_EF_trigmuonef_track_MS_eta;
			HLT_has = trig_EF_trigmuonef_track_MS_hasMS;
		}
		else if(sTrigType=="MG")
		{
			mu_HLT_dr = mu_EFMG_dr;
			mu_HLT_index = mu_EFMG_index;
			HLT_pt = trig_EF_trigmugirl_track_CB_pt;
			HLT_phi = trig_EF_trigmugirl_track_CB_phi;
			HLT_eta = trig_EF_trigmugirl_track_CB_eta;
			HLT_has = trig_EF_trigmugirl_track_CB_hasCB;
		}
		
	}
	
	else cout << "WARNING:  in analysisSkeleton::matchTrigger -> the period name " << speriod << " was not found" << endl;
}

void analysisSkeleton::runEventDumper()
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// write the interesting events to a flat file ///////////////////////////////////////////////
	if(doEventDump)
	{
		//int lead_mu = (mu_charge->at(ai)<0) ? ai : bi;
		//int sublead_mu  = (mu_charge->at(ai)>0) ? ai : bi;
		int lead_mu     = ai;
		int sublead_mu  = bi;
		if( mu_pt->at(ai) < mu_pt->at(bi) )
		{
			lead_mu     = bi;
			sublead_mu  = ai;
		}
		
		current_imass       = imass(pmu[lead_mu],pmu[sublead_mu]);
		current_cosTheta    = cosThetaCollinsSoper( pmu[lead_mu], -1, pmu[sublead_mu], +1 );
		current_mu_pT       = mu_pt->at(lead_mu)*MeV2TeV;//pT(mu_me_qoverp->at(lead_mu),mu_me_theta->at(lead_mu))*MeV2TeV;
		current_muplus_pT   = mu_pt->at(sublead_mu)*MeV2TeV;//pT(mu_me_qoverp->at(sublead_mu),mu_me_theta->at(sublead_mu))*MeV2TeV;
		current_mu_eta      = mu_eta->at(lead_mu);
		current_muplus_eta  = mu_eta->at(sublead_mu);
		current_cosmicCosth = cosThetaDimu(pmu[lead_mu],pmu[sublead_mu]);
		current_etaSum      = current_muplus_eta + current_mu_eta;
		
		setCurrentEventMass( imass(pmu[lead_mu],pmu[sublead_mu]) );
		writeEventHeader(RunNumber, lbn, EventNumber);
		
		//writeProperty("$p_T$", pT(mu_me_qoverp->at(lead_mu),mu_me_theta->at(lead_mu))*MeV2TeV, pT(mu_me_qoverp->at(sublead_mu),mu_me_theta->at(sublead_mu))*MeV2TeV);
		writeProperty("$p_T$", mu_pt->at(lead_mu)*MeV2TeV, mu_pt->at(sublead_mu)*MeV2TeV);
		writeProperty("$\\eta$", mu_eta->at(lead_mu), mu_eta->at(sublead_mu));
		
		writeProperty("$\\sum{p_T^{cone20}}/p_T$", mu_ptcone20->at(lead_mu)/mu_pt->at(lead_mu), mu_ptcone20->at(sublead_mu)/mu_pt->at(sublead_mu));
		writeProperty("$\\sum{p_T^{cone30}}/p_T$", mu_ptcone30->at(lead_mu)/mu_pt->at(lead_mu), mu_ptcone30->at(sublead_mu)/mu_pt->at(sublead_mu));
		writeProperty("$\\sum{p_T^{cone40}}/p_T$", mu_ptcone40->at(lead_mu)/mu_pt->at(lead_mu), mu_ptcone40->at(sublead_mu)/mu_pt->at(sublead_mu));
		
		writeProperty("nSCThits", mu_nSCTHits->at(lead_mu), mu_nSCTHits->at(sublead_mu));
		writeProperty("nPIXhits", mu_nPixHits->at(lead_mu), mu_nPixHits->at(sublead_mu));
		writeProperty("nIDhits ", mu_nSCTHits->at(lead_mu)+mu_nPixHits->at(lead_mu), mu_nSCTHits->at(sublead_mu)+mu_nPixHits->at(sublead_mu));
		
		writeProperty("$\\hat{m}_{\\mu\\mu}$", "red", imass(pmu[lead_mu],pmu[sublead_mu]));
		writeProperty("$\\sum{\\eta_{\\mu}}$", "red", current_muplus_eta + current_mu_eta);
		writeProperty("$\\hat{p}_{\\mu^-}\\cdot\\hat{p}_{\\mu^+}$", cosThetaDimu(pmu[lead_mu],pmu[sublead_mu]));
		writeProperty("$\\cos\\theta_{\\mu^-}$", cosThetaCollinsSoper( pmu[lead_mu], -1, pmu[sublead_mu], +1 ));
		
		
		writeEventFooter();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
}

void analysisSkeleton::printAllProperties(int ai, int bi, int iv)
{
	// event
	printProperty("RunNumber", RunNumber);
	printProperty("lbn", lbn);
	printProperty("EventNumber", EventNumber);
	printProperty("isGRL", isGRL);
	printProperty("imass", imass(pmu[ai],pmu[bi]));
	
	// L1 triggers
	printProperty("L1_MU10", L1_MU10);
	printProperty("L1_MU15", L1_MU15);
	printProperty("L1_MU20", L1_MU20);

	// EF triggers
	printProperty("EF_mu10", EF_mu10);
	printProperty("EF_mu10_MG", EF_mu10_MG);
	printProperty("EF_mu10_MSonly", EF_mu10_MSonly);
	printProperty("EF_mu10_MSonly_tight", EF_mu10_MSonly_tight);
	printProperty("EF_mu10_NoAlg", EF_mu10_NoAlg);
	printProperty("EF_mu10_tight", EF_mu10_tight);
	printProperty("EF_mu10i_loose", EF_mu10i_loose);
	printProperty("EF_mu13", EF_mu13);
	printProperty("EF_mu13_MG", EF_mu13_MG);
	printProperty("EF_mu13_MG_tight", EF_mu13_MG_tight);
	printProperty("EF_mu13_tight", EF_mu13_tight);
	printProperty("EF_mu15", EF_mu15);
	printProperty("EF_mu15_NoAlg", EF_mu15_NoAlg);
	printProperty("EF_mu20", EF_mu20);
	printProperty("EF_mu20_MSonly", EF_mu20_MSonly);
	printProperty("EF_mu20_NoAlg", EF_mu20_NoAlg);
	printProperty("EF_mu20_slow", EF_mu20_slow);
	printProperty("EF_mu30_MSonly", EF_mu30_MSonly);
	printProperty("EF_mu4", EF_mu4);
	printProperty("EF_mu40_MSonly", EF_mu40_MSonly);
   
	// vertexes (for the PV preselection)
	printProperty("vxp_n", vxp_n);
	printProperty("vxp_nTracks", vxp_nTracks->at(iv));
	printProperty("vxp_type", vxp_type->at(iv));
	printProperty("vxp_z", vxp_z->at(iv));
	
	// muon
	printProperty("mu_1_n",mu_n);
	printProperty("mu_1_m", mu_m->at(ai));
	printProperty("mu_1_px", mu_px->at(ai));
	printProperty("mu_1_py", mu_py->at(ai));
	printProperty("mu_1_pz", mu_pz->at(ai));
	printProperty("mu_1_E", mu_E->at(ai));
	printProperty("mu_1_eta", mu_eta->at(ai));
	printProperty("mu_1_phi", mu_phi->at(ai));
	printProperty("mu_1_pt", mu_pt->at(ai));
	printProperty("mu_1_charge", mu_charge->at(ai));
	
	// isolation
	printProperty("mu_1_ptcone20", mu_ptcone20->at(ai));
	printProperty("mu_1_ptcone30", mu_ptcone30->at(ai));
	printProperty("mu_1_ptcone40", mu_ptcone40->at(ai));
	
	// for pT
	printProperty("mu_1_me_qoverp", mu_me_qoverp->at(ai));
	printProperty("mu_1_id_qoverp", mu_id_qoverp->at(ai));
	printProperty("mu_1_me_theta", mu_me_theta->at(ai));
	printProperty("mu_1_id_theta", mu_id_theta->at(ai));
	
	// for impact parameter
	printProperty("mu_1_d0_exPV", mu_d0_exPV->at(ai));
	printProperty("mu_1_z0_exPV", mu_z0_exPV->at(ai));
	
	// combined muons
	printProperty("mu_1_isCombinedMuon", mu_isCombinedMuon->at(ai));
	
	// inner detector hits
	printProperty("mu_1_nSCTHits", mu_nSCTHits->at(ai));
	printProperty("mu_1_nPixHits", mu_nPixHits->at(ai)); 

	// muon spectrometer hits
	printProperty("mu_1_nMDTBIHits", mu_nMDTBIHits->at(ai));
	printProperty("mu_1_nMDTBMHits", mu_nMDTBMHits->at(ai));
	printProperty("mu_1_nMDTBOHits", mu_nMDTBOHits->at(ai));
	printProperty("mu_1_nMDTBEEHits", mu_nMDTBEEHits->at(ai));
	printProperty("mu_1_nMDTBIS78Hits", mu_nMDTBIS78Hits->at(ai));
	printProperty("mu_1_nMDTEIHits", mu_nMDTEIHits->at(ai));
	printProperty("mu_1_nMDTEMHits", mu_nMDTEMHits->at(ai));
	printProperty("mu_1_nMDTEOHits", mu_nMDTEOHits->at(ai));
	printProperty("mu_1_nMDTEEHits", mu_nMDTEEHits->at(ai));
	printProperty("mu_1_nRPCLayer1EtaHits", mu_nRPCLayer1EtaHits->at(ai));
	printProperty("mu_1_nRPCLayer2EtaHits", mu_nRPCLayer2EtaHits->at(ai));
	printProperty("mu_1_nRPCLayer3EtaHits", mu_nRPCLayer3EtaHits->at(ai));
	printProperty("mu_1_nRPCLayer1PhiHits", mu_nRPCLayer1PhiHits->at(ai));
	printProperty("mu_1_nRPCLayer2PhiHits", mu_nRPCLayer2PhiHits->at(ai));
	printProperty("mu_1_nRPCLayer3PhiHits", mu_nRPCLayer3PhiHits->at(ai));
	printProperty("mu_1_nTGCLayer1EtaHits", mu_nTGCLayer1EtaHits->at(ai));
	printProperty("mu_1_nTGCLayer2EtaHits", mu_nTGCLayer2EtaHits->at(ai));
	printProperty("mu_1_nTGCLayer3EtaHits", mu_nTGCLayer3EtaHits->at(ai));
	printProperty("mu_1_nTGCLayer4EtaHits", mu_nTGCLayer4EtaHits->at(ai));
	printProperty("mu_1_nTGCLayer1PhiHits", mu_nTGCLayer1PhiHits->at(ai));
	printProperty("mu_1_nTGCLayer2PhiHits", mu_nTGCLayer2PhiHits->at(ai));
	printProperty("mu_1_nTGCLayer3PhiHits", mu_nTGCLayer3PhiHits->at(ai));
	printProperty("mu_1_nTGCLayer4PhiHits", mu_nTGCLayer4PhiHits->at(ai));

	printProperty("mu_2_m", mu_m->at(bi));
	printProperty("mu_2_px", mu_px->at(bi));
	printProperty("mu_2_py", mu_py->at(bi));
	printProperty("mu_2_pz", mu_pz->at(bi));
	printProperty("mu_2_E", mu_E->at(bi));
	printProperty("mu_2_eta", mu_eta->at(bi));
	printProperty("mu_2_phi", mu_phi->at(bi));
	printProperty("mu_2_pt", mu_pt->at(bi));
	printProperty("mu_2_charge", mu_charge->at(bi));
	
	// isolation
	printProperty("mu_2_ptcone20", mu_ptcone20->at(bi));
	printProperty("mu_2_ptcone30", mu_ptcone30->at(bi));
	printProperty("mu_2_ptcone40", mu_ptcone40->at(bi));
	
	// for pT
	printProperty("mu_2_me_qoverp", mu_me_qoverp->at(bi));
	printProperty("mu_2_id_qoverp", mu_id_qoverp->at(bi));
	printProperty("mu_2_me_theta", mu_me_theta->at(bi));
	printProperty("mu_2_id_theta", mu_id_theta->at(bi));
	
	// for impact parameter
	printProperty("mu_2_d0_exPV", mu_d0_exPV->at(bi));
	printProperty("mu_2_z0_exPV", mu_z0_exPV->at(bi));
	
	// combined muons
	printProperty("mu_2_isCombinedMuon", mu_isCombinedMuon->at(bi));
	
	// inner detector hits
	printProperty("mu_2_nSCTHits", mu_nSCTHits->at(bi));
	printProperty("mu_2_nPixHits", mu_nPixHits->at(bi)); 

	// muon spectrometer hits
	printProperty("mu_2_nMDTBIHits", mu_nMDTBIHits->at(bi));
	printProperty("mu_2_nMDTBMHits", mu_nMDTBMHits->at(bi));
	printProperty("mu_2_nMDTBOHits", mu_nMDTBOHits->at(bi));
	printProperty("mu_2_nMDTBEEHits", mu_nMDTBEEHits->at(bi));
	printProperty("mu_2_nMDTBIS78Hits", mu_nMDTBIS78Hits->at(bi));
	printProperty("mu_2_nMDTEIHits", mu_nMDTEIHits->at(bi));
	printProperty("mu_2_nMDTEMHits", mu_nMDTEMHits->at(bi));
	printProperty("mu_2_nMDTEOHits", mu_nMDTEOHits->at(bi));
	printProperty("mu_2_nMDTEEHits", mu_nMDTEEHits->at(bi));
	printProperty("mu_2_nRPCLayer1EtaHits", mu_nRPCLayer1EtaHits->at(bi));
	printProperty("mu_2_nRPCLayer2EtaHits", mu_nRPCLayer2EtaHits->at(bi));
	printProperty("mu_2_nRPCLayer3EtaHits", mu_nRPCLayer3EtaHits->at(bi));
	printProperty("mu_2_nRPCLayer1PhiHits", mu_nRPCLayer1PhiHits->at(bi));
	printProperty("mu_2_nRPCLayer2PhiHits", mu_nRPCLayer2PhiHits->at(bi));
	printProperty("mu_2_nRPCLayer3PhiHits", mu_nRPCLayer3PhiHits->at(bi));
	printProperty("mu_2_nTGCLayer1EtaHits", mu_nTGCLayer1EtaHits->at(bi));
	printProperty("mu_2_nTGCLayer2EtaHits", mu_nTGCLayer2EtaHits->at(bi));
	printProperty("mu_2_nTGCLayer3EtaHits", mu_nTGCLayer3EtaHits->at(bi));
	printProperty("mu_2_nTGCLayer4EtaHits", mu_nTGCLayer4EtaHits->at(bi));
	printProperty("mu_2_nTGCLayer1PhiHits", mu_nTGCLayer1PhiHits->at(bi));
	printProperty("mu_2_nTGCLayer2PhiHits", mu_nTGCLayer2PhiHits->at(bi));
	printProperty("mu_2_nTGCLayer3PhiHits", mu_nTGCLayer3PhiHits->at(bi));
	printProperty("mu_2_nTGCLayer4PhiHits", mu_nTGCLayer4PhiHits->at(bi));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void analysisSkeleton::fillAfterCuts(bool isMC)
{
	///////////////////////////////////////////////////////////
	// fill the "allCuts" histograms only after the last cut 
	// for the final histograms:
	// i.e., not the curFlow histos
	
	//int lead_mu = (mu_charge->at(ai)<0) ? ai : bi;
	//int sublead_mu  = (mu_charge->at(ai)>0) ? ai : bi;
	int lead_mu     = ai;
	int sublead_mu  = bi;
	if( mu_pt->at(ai) < mu_pt->at(bi) )
	{
		lead_mu     = bi;
		sublead_mu  = ai;
	}

	current_mu_me_pT     = pT(mu_me_qoverp->at(lead_mu),mu_me_theta->at(lead_mu))*MeV2TeV;
	current_muplus_me_pT = pT(mu_me_qoverp->at(sublead_mu),mu_me_theta->at(sublead_mu))*MeV2TeV;
	current_mu_id_pT     = pT(mu_id_qoverp->at(lead_mu),mu_id_theta->at(lead_mu))*MeV2TeV;
	current_muplus_id_pT = pT(mu_id_qoverp->at(sublead_mu),mu_id_theta->at(sublead_mu))*MeV2TeV;
	current_mu_pT        = mu_pt->at(lead_mu)*MeV2TeV;
	current_muplus_pT    = mu_pt->at(sublead_mu)*MeV2TeV;
	current_mu_eta       = mu_eta->at(lead_mu);
	current_muplus_eta   = mu_eta->at(sublead_mu);
	current_mu_me_qop    = mu_me_qoverp->at(lead_mu)*MeV2TeV;
	current_muplus_me_qop = mu_me_qoverp->at(sublead_mu)*MeV2TeV;
	current_mu_id_qop     = mu_id_qoverp->at(lead_mu)*MeV2TeV;
	current_muplus_id_qop = mu_me_qoverp->at(sublead_mu)*MeV2TeV;
	current_mu_me_theta     = mu_me_theta->at(lead_mu);
	current_muplus_me_theta = mu_me_theta->at(sublead_mu);;
	current_mu_id_theta     = mu_id_theta->at(lead_mu);;
	current_muplus_id_theta = mu_id_theta->at(sublead_mu);;
	
	current_imass       = imass(pmu[lead_mu],pmu[sublead_mu]);
	current_cosTheta    = cosThetaCollinsSoper( pmu[lead_mu], mu_charge->at(lead_mu), pmu[sublead_mu], mu_charge->at(sublead_mu) );
	current_cosThetaCS  = cosThetaCollinsSoper( pmu[lead_mu], mu_charge->at(lead_mu), pmu[sublead_mu], mu_charge->at(sublead_mu) );
	current_cosThetaHE  = cosThetaBoost( pmu[lead_mu], mu_charge->at(lead_mu), pmu[sublead_mu], mu_charge->at(sublead_mu) );
	current_ySystem     = ySystem( pmu[lead_mu], pmu[sublead_mu] );
	current_QT          = QT( pmu[lead_mu], pmu[sublead_mu] );
	current_cosmicCosth = cosThetaDimu(pmu[lead_mu],pmu[sublead_mu]);
	current_ipTdiff     = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_etaSum      = current_muplus_eta + current_mu_eta;
	current_pTdiff      = current_mu_me_pT - current_mu_id_pT;
	current_pTdiff_muplus  = current_muplus_me_pT - current_muplus_id_pT;
	current_pTratio        = (current_mu_id_pT!=0.) ? fabs( current_mu_me_pT / current_mu_id_pT ) : -999.;
	current_pTres          = (current_mu_id_pT!=0.) ? (current_mu_me_pT-current_mu_id_pT)/current_mu_id_pT : -999.;
	current_pTratio_muplus = (current_muplus_id_pT!=0.) ? fabs( current_muplus_me_pT / current_muplus_id_pT ) : -999.;
	current_pTres_muplus   = (current_muplus_id_pT!=0.) ? (current_muplus_me_pT-current_muplus_id_pT)/current_muplus_id_pT : -999.;
	
	
	if(current_imass>=XMIN  &&  current_imass<=XMAX) { h1_costh->Fill( current_cosTheta ); }
	h1_cosmicCosthAllCuts->Fill( current_cosmicCosth );
	h1_eta->Fill(                current_mu_eta );
	h1_eta_muplus->Fill(         current_muplus_eta );
	h1_ipTdiff->Fill(            current_ipTdiff );
	h1_etaSum->Fill(             current_etaSum );
	h1_imass->Fill(              current_imass );
	h1_imassFit->Fill(           current_imass );
	h1_pT->Fill(                 current_mu_pT );
	h1_pT_muplus->Fill(          current_muplus_pT );
	h1_pTdiff->Fill( current_pTdiff );
	h1_pTdiff_muplus->Fill( current_pTdiff_muplus );
	h1_pTratio->Fill( current_pTratio );
	h1_pTratio_muplus->Fill( current_pTratio_muplus );
	h1_pTres->Fill( current_pTres );
	h1_pTres_muplus->Fill( current_pTres_muplus );
	h2_pTmevspTid->Fill( current_mu_me_pT, current_mu_id_pT );
	h2_pTmevspTid_muplus->Fill( current_muplus_me_pT, current_muplus_id_pT );
	
	
	/////////////////////////////////////////////////
	// fill the graphicObjects all cuts tree ////////
	graphicObjects::RunNumber = RunNumber;
	graphicObjects::EventNumber = EventNumber;
	graphicObjects::timestamp = timestamp;
	graphicObjects::timestamp_ns = timestamp_ns;
	graphicObjects::lbn = lbn;
	graphicObjects::bcid = bcid;

	graphicObjects::ivxp            = getPVindex();
	graphicObjects::iLeadingMuon    = lead_mu;
	graphicObjects::iSubLeadingMuon = sublead_mu;
	
	// all cuts - vectors
	graphicObjects::graphicObjects::vxp_n;
	graphicObjects::vxp_nTracks->push_back(vxp_nTracks->at(getPVindex()));
	graphicObjects::vxp_type->push_back(vxp_type->at(getPVindex()));
	graphicObjects::vxp_z->push_back(vxp_z->at(getPVindex()));
	
	graphicObjects::Mhat         = current_imass;
	graphicObjects::CosThetaCS   = current_cosThetaCS;
	graphicObjects::CosThetaHE   = current_cosThetaHE;
	graphicObjects::Ysystem      = current_ySystem;
	graphicObjects::Q_T          = current_QT;
	graphicObjects::CosThetaDimu = current_cosmicCosth;
	graphicObjects::ipTDiff      = current_ipTdiff;
	graphicObjects::EtaSum       = current_etaSum;
	
	graphicObjects::n = mu_n;
	graphicObjects::E->push_back(mu_E->at(lead_mu));
	graphicObjects::pt->push_back(mu_pt->at(lead_mu));
	graphicObjects::m->push_back(mu_m->at(lead_mu));
	graphicObjects::eta->push_back(mu_eta->at(lead_mu));
	graphicObjects::phi->push_back(mu_phi->at(lead_mu));
	graphicObjects::px->push_back(mu_px->at(lead_mu));
	graphicObjects::py->push_back(mu_py->at(lead_mu));
	graphicObjects::pz->push_back(mu_pz->at(lead_mu));
	graphicObjects::charge->push_back(mu_charge->at(lead_mu));
	graphicObjects::allauthor->push_back(mu_allauthor->at(lead_mu));
	graphicObjects::author->push_back(mu_author->at(lead_mu));
	graphicObjects::beta->push_back(mu_beta->at(lead_mu));
	graphicObjects::isMuonLikelihood->push_back(mu_isMuonLikelihood->at(lead_mu));
	graphicObjects::matchchi2->push_back(mu_matchchi2->at(lead_mu));
	graphicObjects::matchndof->push_back(mu_matchndof->at(lead_mu));
	graphicObjects::etcone20->push_back(mu_etcone20->at(lead_mu));
	graphicObjects::etcone30->push_back(mu_etcone30->at(lead_mu));
	graphicObjects::etcone40->push_back(mu_etcone40->at(lead_mu));
	graphicObjects::nucone20->push_back(mu_nucone20->at(lead_mu));
	graphicObjects::nucone30->push_back(mu_nucone30->at(lead_mu));
	graphicObjects::nucone40->push_back(mu_nucone40->at(lead_mu));
	graphicObjects::ptcone20->push_back(mu_ptcone20->at(lead_mu));
	graphicObjects::ptcone30->push_back(mu_ptcone30->at(lead_mu));
	graphicObjects::ptcone40->push_back(mu_ptcone40->at(lead_mu));
	graphicObjects::energyLossPar->push_back(mu_energyLossPar->at(lead_mu));
	graphicObjects::energyLossErr->push_back(mu_energyLossErr->at(lead_mu));
	graphicObjects::etCore->push_back(mu_etCore->at(lead_mu));
	graphicObjects::energyLossType->push_back(mu_energyLossType->at(lead_mu));
	graphicObjects::caloMuonIdTag->push_back(mu_caloMuonIdTag->at(lead_mu));
	graphicObjects::caloLRLikelihood->push_back(mu_caloLRLikelihood->at(lead_mu));
	graphicObjects::bestMatch->push_back(mu_bestMatch->at(lead_mu));
	graphicObjects::isStandAloneMuon->push_back(mu_isStandAloneMuon->at(lead_mu));
	graphicObjects::isCombinedMuon->push_back(mu_isCombinedMuon->at(lead_mu));
	graphicObjects::isLowPtReconstructedMuon->push_back(mu_isLowPtReconstructedMuon->at(lead_mu));
	graphicObjects::loose->push_back(mu_loose->at(lead_mu));
	graphicObjects::medium->push_back(mu_medium->at(lead_mu));
	graphicObjects::tight->push_back(mu_tight->at(lead_mu));
	graphicObjects::d0_exPV->push_back(mu_d0_exPV->at(lead_mu));
	graphicObjects::z0_exPV->push_back(mu_z0_exPV->at(lead_mu));
	graphicObjects::phi_exPV->push_back(mu_phi_exPV->at(lead_mu));
	graphicObjects::theta_exPV->push_back(mu_theta_exPV->at(lead_mu));
	graphicObjects::qoverp_exPV->push_back(mu_qoverp_exPV->at(lead_mu));
	graphicObjects::cb_d0_exPV->push_back(mu_cb_d0_exPV->at(lead_mu));
	graphicObjects::cb_z0_exPV->push_back(mu_cb_z0_exPV->at(lead_mu));
	graphicObjects::cb_phi_exPV->push_back(mu_cb_phi_exPV->at(lead_mu));
	graphicObjects::cb_theta_exPV->push_back(mu_cb_theta_exPV->at(lead_mu));
	graphicObjects::cb_qoverp_exPV->push_back(mu_cb_qoverp_exPV->at(lead_mu));
	graphicObjects::id_d0_exPV->push_back(mu_id_d0_exPV->at(lead_mu));
	graphicObjects::id_z0_exPV->push_back(mu_id_z0_exPV->at(lead_mu));
	graphicObjects::id_phi_exPV->push_back(mu_id_phi_exPV->at(lead_mu));
	graphicObjects::id_theta_exPV->push_back(mu_id_theta_exPV->at(lead_mu));
	graphicObjects::id_qoverp_exPV->push_back(mu_id_qoverp_exPV->at(lead_mu));
	graphicObjects::me_d0_exPV->push_back(mu_me_d0_exPV->at(lead_mu));
	graphicObjects::me_z0_exPV->push_back(mu_me_z0_exPV->at(lead_mu));
	graphicObjects::me_phi_exPV->push_back(mu_me_phi_exPV->at(lead_mu));
	graphicObjects::me_theta_exPV->push_back(mu_me_theta_exPV->at(lead_mu));
	graphicObjects::me_qoverp_exPV->push_back(mu_me_qoverp_exPV->at(lead_mu));
	graphicObjects::ie_d0_exPV->push_back(mu_ie_d0_exPV->at(lead_mu));
	graphicObjects::ie_z0_exPV->push_back(mu_ie_z0_exPV->at(lead_mu));
	graphicObjects::ie_phi_exPV->push_back(mu_ie_phi_exPV->at(lead_mu));
	graphicObjects::ie_theta_exPV->push_back(mu_ie_theta_exPV->at(lead_mu));
	graphicObjects::ie_qoverp_exPV->push_back(mu_ie_qoverp_exPV->at(lead_mu));
	//graphicObjects::SpaceTime_detID->push_back(mu_SpaceTime_detID->at(lead_mu));
	//graphicObjects::SpaceTime_t->push_back(mu_SpaceTime_t->at(lead_mu));
	//graphicObjects::SpaceTime_tError->push_back(mu_SpaceTime_tError->at(lead_mu));
	//graphicObjects::SpaceTime_weight->push_back(mu_SpaceTime_weight->at(lead_mu));
	//graphicObjects::SpaceTime_x->push_back(mu_SpaceTime_x->at(lead_mu));
	//graphicObjects::SpaceTime_y->push_back(mu_SpaceTime_y->at(lead_mu));
	//graphicObjects::SpaceTime_z->push_back(mu_SpaceTime_z->at(lead_mu));
	//graphicObjects::SpaceTime_t_Tile->push_back(mu_SpaceTime_t_Tile->at(lead_mu));
	//graphicObjects::SpaceTime_tError_Tile->push_back(mu_SpaceTime_tError_Tile->at(lead_mu));
	//graphicObjects::SpaceTime_weight_Tile->push_back(mu_SpaceTime_weight_Tile->at(lead_mu));
	//graphicObjects::SpaceTime_x_Tile->push_back(mu_SpaceTime_x_Tile->at(lead_mu));
	//graphicObjects::SpaceTime_y_Tile->push_back(mu_SpaceTime_y_Tile->at(lead_mu));
	//graphicObjects::SpaceTime_z_Tile->push_back(mu_SpaceTime_z_Tile->at(lead_mu));
	//graphicObjects::SpaceTime_t_TRT->push_back(mu_SpaceTime_t_TRT->at(lead_mu));
	//graphicObjects::SpaceTime_tError_TRT->push_back(mu_SpaceTime_tError_TRT->at(lead_mu));
	//graphicObjects::SpaceTime_weight_TRT->push_back(mu_SpaceTime_weight_TRT->at(lead_mu));
	//graphicObjects::SpaceTime_x_TRT->push_back(mu_SpaceTime_x_TRT->at(lead_mu));
	//graphicObjects::SpaceTime_y_TRT->push_back(mu_SpaceTime_y_TRT->at(lead_mu));
	//graphicObjects::SpaceTime_z_TRT->push_back(mu_SpaceTime_z_TRT->at(lead_mu));
	//graphicObjects::SpaceTime_t_MDT->push_back(mu_SpaceTime_t_MDT->at(lead_mu));
	//graphicObjects::SpaceTime_tError_MDT->push_back(mu_SpaceTime_tError_MDT->at(lead_mu));
	//graphicObjects::SpaceTime_weight_MDT->push_back(mu_SpaceTime_weight_MDT->at(lead_mu));
	//graphicObjects::SpaceTime_x_MDT->push_back(mu_SpaceTime_x_MDT->at(lead_mu));
	//graphicObjects::SpaceTime_y_MDT->push_back(mu_SpaceTime_y_MDT->at(lead_mu));
	//graphicObjects::SpaceTime_z_MDT->push_back(mu_SpaceTime_z_MDT->at(lead_mu));
	graphicObjects::TileCellEnergyLayer1->push_back(mu_TileCellEnergyLayer1->at(lead_mu));
	graphicObjects::TileTimeLayer1->push_back(mu_TileTimeLayer1->at(lead_mu));
	graphicObjects::TileCellRmsNoiseLayer1->push_back(mu_TileCellRmsNoiseLayer1->at(lead_mu));
	graphicObjects::TileCellSignLayer1->push_back(mu_TileCellSignLayer1->at(lead_mu));
	graphicObjects::TileCellEnergyLayer2->push_back(mu_TileCellEnergyLayer2->at(lead_mu));
	graphicObjects::TileTimeLayer2->push_back(mu_TileTimeLayer2->at(lead_mu));
	graphicObjects::TileCellRmsNoiseLayer2->push_back(mu_TileCellRmsNoiseLayer2->at(lead_mu));
	graphicObjects::TileCellSignLayer2->push_back(mu_TileCellSignLayer2->at(lead_mu));
	graphicObjects::TileCellEnergyLayer3->push_back(mu_TileCellEnergyLayer3->at(lead_mu));
	graphicObjects::TileTimeLayer3->push_back(mu_TileTimeLayer3->at(lead_mu));
	graphicObjects::TileCellRmsNoiseLayer3->push_back(mu_TileCellRmsNoiseLayer3->at(lead_mu));
	graphicObjects::TileCellSignLayer3->push_back(mu_TileCellSignLayer3->at(lead_mu));
	graphicObjects::MSTrkT0_1->push_back(mu_MSTrkT0_1->at(lead_mu));
	graphicObjects::MSTrkT0_2->push_back(mu_MSTrkT0_2->at(lead_mu));
	graphicObjects::MSTrkT0_3->push_back(mu_MSTrkT0_3->at(lead_mu));
	graphicObjects::cov_d0_exPV->push_back(mu_cov_d0_exPV->at(lead_mu));
	graphicObjects::cov_z0_exPV->push_back(mu_cov_z0_exPV->at(lead_mu));
	graphicObjects::cov_phi_exPV->push_back(mu_cov_phi_exPV->at(lead_mu));
	graphicObjects::cov_theta_exPV->push_back(mu_cov_theta_exPV->at(lead_mu));
	graphicObjects::cov_qoverp_exPV->push_back(mu_cov_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_d0_z0_exPV->push_back(mu_cov_d0_z0_exPV->at(lead_mu));
	graphicObjects::cov_d0_phi_exPV->push_back(mu_cov_d0_phi_exPV->at(lead_mu));
	graphicObjects::cov_d0_theta_exPV->push_back(mu_cov_d0_theta_exPV->at(lead_mu));
	graphicObjects::cov_d0_qoverp_exPV->push_back(mu_cov_d0_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_z0_phi_exPV->push_back(mu_cov_z0_phi_exPV->at(lead_mu));
	graphicObjects::cov_z0_theta_exPV->push_back(mu_cov_z0_theta_exPV->at(lead_mu));
	graphicObjects::cov_z0_qoverp_exPV->push_back(mu_cov_z0_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_phi_theta_exPV->push_back(mu_cov_phi_theta_exPV->at(lead_mu));
	graphicObjects::cov_phi_qoverp_exPV->push_back(mu_cov_phi_qoverp_exPV->at(lead_mu));
	graphicObjects::cov_theta_qoverp_exPV->push_back(mu_cov_theta_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_exPV->push_back(mu_id_cov_d0_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_exPV->push_back(mu_id_cov_z0_exPV->at(lead_mu));
	graphicObjects::id_cov_phi_exPV->push_back(mu_id_cov_phi_exPV->at(lead_mu));
	graphicObjects::id_cov_theta_exPV->push_back(mu_id_cov_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_qoverp_exPV->push_back(mu_id_cov_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_z0_exPV->push_back(mu_id_cov_d0_z0_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_phi_exPV->push_back(mu_id_cov_d0_phi_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_theta_exPV->push_back(mu_id_cov_d0_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_d0_qoverp_exPV->push_back(mu_id_cov_d0_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_phi_exPV->push_back(mu_id_cov_z0_phi_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_theta_exPV->push_back(mu_id_cov_z0_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_z0_qoverp_exPV->push_back(mu_id_cov_z0_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_phi_theta_exPV->push_back(mu_id_cov_phi_theta_exPV->at(lead_mu));
	graphicObjects::id_cov_phi_qoverp_exPV->push_back(mu_id_cov_phi_qoverp_exPV->at(lead_mu));
	graphicObjects::id_cov_theta_qoverp_exPV->push_back(mu_id_cov_theta_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_exPV->push_back(mu_me_cov_d0_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_exPV->push_back(mu_me_cov_z0_exPV->at(lead_mu));
	graphicObjects::me_cov_phi_exPV->push_back(mu_me_cov_phi_exPV->at(lead_mu));
	graphicObjects::me_cov_theta_exPV->push_back(mu_me_cov_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_qoverp_exPV->push_back(mu_me_cov_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_z0_exPV->push_back(mu_me_cov_d0_z0_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_phi_exPV->push_back(mu_me_cov_d0_phi_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_theta_exPV->push_back(mu_me_cov_d0_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_d0_qoverp_exPV->push_back(mu_me_cov_d0_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_phi_exPV->push_back(mu_me_cov_z0_phi_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_theta_exPV->push_back(mu_me_cov_z0_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_z0_qoverp_exPV->push_back(mu_me_cov_z0_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_phi_theta_exPV->push_back(mu_me_cov_phi_theta_exPV->at(lead_mu));
	graphicObjects::me_cov_phi_qoverp_exPV->push_back(mu_me_cov_phi_qoverp_exPV->at(lead_mu));
	graphicObjects::me_cov_theta_qoverp_exPV->push_back(mu_me_cov_theta_qoverp_exPV->at(lead_mu));
	graphicObjects::ms_d0->push_back(mu_ms_d0->at(lead_mu));
	graphicObjects::ms_z0->push_back(mu_ms_z0->at(lead_mu));
	graphicObjects::ms_phi->push_back(mu_ms_phi->at(lead_mu));
	graphicObjects::ms_theta->push_back(mu_ms_theta->at(lead_mu));
	graphicObjects::ms_qoverp->push_back(mu_ms_qoverp->at(lead_mu));
	graphicObjects::id_d0->push_back(mu_id_d0->at(lead_mu));
	graphicObjects::id_z0->push_back(mu_id_z0->at(lead_mu));
	graphicObjects::id_phi->push_back(mu_id_phi->at(lead_mu));
	graphicObjects::id_theta->push_back(mu_id_theta->at(lead_mu));
	graphicObjects::id_qoverp->push_back(mu_id_qoverp->at(lead_mu));
	graphicObjects::me_d0->push_back(mu_me_d0->at(lead_mu));
	graphicObjects::me_z0->push_back(mu_me_z0->at(lead_mu));
	graphicObjects::me_phi->push_back(mu_me_phi->at(lead_mu));
	graphicObjects::me_theta->push_back(mu_me_theta->at(lead_mu));
	graphicObjects::me_qoverp->push_back(mu_me_qoverp->at(lead_mu));
	graphicObjects::ie_d0->push_back(mu_ie_d0->at(lead_mu));
	graphicObjects::ie_z0->push_back(mu_ie_z0->at(lead_mu));
	graphicObjects::ie_phi->push_back(mu_ie_phi->at(lead_mu));
	graphicObjects::ie_theta->push_back(mu_ie_theta->at(lead_mu));
	graphicObjects::ie_qoverp->push_back(mu_ie_qoverp->at(lead_mu));
	graphicObjects::nOutliersOnTrack->push_back(mu_nOutliersOnTrack->at(lead_mu));
	graphicObjects::nBLHits->push_back(mu_nBLHits->at(lead_mu));
	graphicObjects::nPixHits->push_back(mu_nPixHits->at(lead_mu));
	graphicObjects::nSCTHits->push_back(mu_nSCTHits->at(lead_mu));
	graphicObjects::nTRTHits->push_back(mu_nTRTHits->at(lead_mu));
	graphicObjects::nTRTHighTHits->push_back(mu_nTRTHighTHits->at(lead_mu));
	graphicObjects::nBLSharedHits->push_back(mu_nBLSharedHits->at(lead_mu));
	graphicObjects::nPixSharedHits->push_back(mu_nPixSharedHits->at(lead_mu));
	graphicObjects::nPixHoles->push_back(mu_nPixHoles->at(lead_mu));
	graphicObjects::nSCTSharedHits->push_back(mu_nSCTSharedHits->at(lead_mu));
	graphicObjects::nSCTHoles->push_back(mu_nSCTHoles->at(lead_mu));
	graphicObjects::nTRTOutliers->push_back(mu_nTRTOutliers->at(lead_mu));
	graphicObjects::nTRTHighTOutliers->push_back(mu_nTRTHighTOutliers->at(lead_mu));
	graphicObjects::nGangedPixels->push_back(mu_nGangedPixels->at(lead_mu));
	graphicObjects::nPixelDeadSensors->push_back(mu_nPixelDeadSensors->at(lead_mu));
	graphicObjects::nSCTDeadSensors->push_back(mu_nSCTDeadSensors->at(lead_mu));
	graphicObjects::nTRTDeadStraws->push_back(mu_nTRTDeadStraws->at(lead_mu));
	graphicObjects::expectBLayerHit->push_back(mu_expectBLayerHit->at(lead_mu));
	graphicObjects::nMDTHits->push_back(mu_nMDTHits->at(lead_mu));
	graphicObjects::nMDTHoles->push_back(mu_nMDTHoles->at(lead_mu));
	graphicObjects::nCSCEtaHits->push_back(mu_nCSCEtaHits->at(lead_mu));
	graphicObjects::nCSCEtaHoles->push_back(mu_nCSCEtaHoles->at(lead_mu));
	graphicObjects::nCSCPhiHits->push_back(mu_nCSCPhiHits->at(lead_mu));
	graphicObjects::nCSCPhiHoles->push_back(mu_nCSCPhiHoles->at(lead_mu));
	graphicObjects::nRPCEtaHits->push_back(mu_nRPCEtaHits->at(lead_mu));
	graphicObjects::nRPCEtaHoles->push_back(mu_nRPCEtaHoles->at(lead_mu));
	graphicObjects::nRPCPhiHits->push_back(mu_nRPCPhiHits->at(lead_mu));
	graphicObjects::nRPCPhiHoles->push_back(mu_nRPCPhiHoles->at(lead_mu));
	graphicObjects::nTGCEtaHits->push_back(mu_nTGCEtaHits->at(lead_mu));
	graphicObjects::nTGCEtaHoles->push_back(mu_nTGCEtaHoles->at(lead_mu));
	graphicObjects::nTGCPhiHits->push_back(mu_nTGCPhiHits->at(lead_mu));
	graphicObjects::nTGCPhiHoles->push_back(mu_nTGCPhiHoles->at(lead_mu));
	graphicObjects::nMDTBIHits->push_back(mu_nMDTBIHits->at(lead_mu));
	graphicObjects::nMDTBMHits->push_back(mu_nMDTBMHits->at(lead_mu));
	graphicObjects::nMDTBOHits->push_back(mu_nMDTBOHits->at(lead_mu));
	graphicObjects::nMDTBEEHits->push_back(mu_nMDTBEEHits->at(lead_mu));
	graphicObjects::nMDTBIS78Hits->push_back(mu_nMDTBIS78Hits->at(lead_mu));
	graphicObjects::nMDTEIHits->push_back(mu_nMDTEIHits->at(lead_mu));
	graphicObjects::nMDTEMHits->push_back(mu_nMDTEMHits->at(lead_mu));
	graphicObjects::nMDTEOHits->push_back(mu_nMDTEOHits->at(lead_mu));
	graphicObjects::nMDTEEHits->push_back(mu_nMDTEEHits->at(lead_mu));
	graphicObjects::nRPCLayer1EtaHits->push_back(mu_nRPCLayer1EtaHits->at(lead_mu));
	graphicObjects::nRPCLayer2EtaHits->push_back(mu_nRPCLayer2EtaHits->at(lead_mu));
	graphicObjects::nRPCLayer3EtaHits->push_back(mu_nRPCLayer3EtaHits->at(lead_mu));
	graphicObjects::nRPCLayer1PhiHits->push_back(mu_nRPCLayer1PhiHits->at(lead_mu));
	graphicObjects::nRPCLayer2PhiHits->push_back(mu_nRPCLayer2PhiHits->at(lead_mu));
	graphicObjects::nRPCLayer3PhiHits->push_back(mu_nRPCLayer3PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer1EtaHits->push_back(mu_nTGCLayer1EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer2EtaHits->push_back(mu_nTGCLayer2EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer3EtaHits->push_back(mu_nTGCLayer3EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer4EtaHits->push_back(mu_nTGCLayer4EtaHits->at(lead_mu));
	graphicObjects::nTGCLayer1PhiHits->push_back(mu_nTGCLayer1PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer2PhiHits->push_back(mu_nTGCLayer2PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer3PhiHits->push_back(mu_nTGCLayer3PhiHits->at(lead_mu));
	graphicObjects::nTGCLayer4PhiHits->push_back(mu_nTGCLayer4PhiHits->at(lead_mu));
	graphicObjects::barrelSectors->push_back(mu_barrelSectors->at(lead_mu));
	graphicObjects::endcapSectors->push_back(mu_endcapSectors->at(lead_mu));
	graphicObjects::trackd0->push_back(mu_trackd0->at(lead_mu));
	graphicObjects::trackz0->push_back(mu_trackz0->at(lead_mu));
	graphicObjects::trackphi->push_back(mu_trackphi->at(lead_mu));
	graphicObjects::tracktheta->push_back(mu_tracktheta->at(lead_mu));
	graphicObjects::trackqoverp->push_back(mu_trackqoverp->at(lead_mu));
	graphicObjects::trackcov_d0->push_back(mu_trackcov_d0->at(lead_mu));
	graphicObjects::trackcov_z0->push_back(mu_trackcov_z0->at(lead_mu));
	graphicObjects::trackcov_phi->push_back(mu_trackcov_phi->at(lead_mu));
	graphicObjects::trackcov_theta->push_back(mu_trackcov_theta->at(lead_mu));
	graphicObjects::trackcov_qoverp->push_back(mu_trackcov_qoverp->at(lead_mu));
	graphicObjects::trackcov_d0_z0->push_back(mu_trackcov_d0_z0->at(lead_mu));
	graphicObjects::trackcov_d0_phi->push_back(mu_trackcov_d0_phi->at(lead_mu));
	graphicObjects::trackcov_d0_theta->push_back(mu_trackcov_d0_theta->at(lead_mu));
	graphicObjects::trackcov_d0_qoverp->push_back(mu_trackcov_d0_qoverp->at(lead_mu));
	graphicObjects::trackcov_z0_phi->push_back(mu_trackcov_z0_phi->at(lead_mu));
	graphicObjects::trackcov_z0_theta->push_back(mu_trackcov_z0_theta->at(lead_mu));
	graphicObjects::trackcov_z0_qoverp->push_back(mu_trackcov_z0_qoverp->at(lead_mu));
	graphicObjects::trackcov_phi_theta->push_back(mu_trackcov_phi_theta->at(lead_mu));
	graphicObjects::trackcov_phi_qoverp->push_back(mu_trackcov_phi_qoverp->at(lead_mu));
	graphicObjects::trackcov_theta_qoverp->push_back(mu_trackcov_theta_qoverp->at(lead_mu));
	graphicObjects::trackfitchi2->push_back(mu_trackfitchi2->at(lead_mu));
	graphicObjects::trackfitndof->push_back(mu_trackfitndof->at(lead_mu));
	graphicObjects::hastrack->push_back(mu_hastrack->at(lead_mu));
	if(isMC)
	{
		graphicObjects::truth_dr->push_back(mu_truth_dr->at(lead_mu));
		graphicObjects::truth_E->push_back(mu_truth_E->at(lead_mu));
		graphicObjects::truth_pt->push_back(mu_truth_pt->at(lead_mu));
		graphicObjects::truth_eta->push_back(mu_truth_eta->at(lead_mu));
		graphicObjects::truth_phi->push_back(mu_truth_phi->at(lead_mu));
		graphicObjects::truth_type->push_back(mu_truth_type->at(lead_mu));
		graphicObjects::truth_status->push_back(mu_truth_status->at(lead_mu));
		graphicObjects::truth_barcode->push_back(mu_truth_barcode->at(lead_mu));
		graphicObjects::truth_mothertype->push_back(mu_truth_mothertype->at(lead_mu));
		graphicObjects::truth_motherbarcode->push_back(mu_truth_motherbarcode->at(lead_mu));
		graphicObjects::truth_matched->push_back(mu_truth_matched->at(lead_mu));
	}
	graphicObjects::EFCB_dr->push_back(mu_EFCB_dr->at(lead_mu));
	graphicObjects::EFCB_index->push_back(mu_EFCB_index->at(lead_mu));
	graphicObjects::EFMG_dr->push_back(mu_EFMG_dr->at(lead_mu));
	graphicObjects::EFMG_index->push_back(mu_EFMG_index->at(lead_mu));
	graphicObjects::EFME_dr->push_back(mu_EFME_dr->at(lead_mu));
	graphicObjects::EFME_index->push_back(mu_EFME_index->at(lead_mu));
	graphicObjects::L2CB_dr->push_back(mu_L2CB_dr->at(lead_mu));
	graphicObjects::L2CB_index->push_back(mu_L2CB_index->at(lead_mu));
	graphicObjects::L1_dr->push_back(mu_L1_dr->at(lead_mu));
	graphicObjects::L1_index->push_back(mu_L1_index->at(lead_mu));
	graphicObjects::E->push_back(mu_E->at(sublead_mu));
	graphicObjects::pt->push_back(mu_pt->at(sublead_mu));
	graphicObjects::m->push_back(mu_m->at(sublead_mu));
	graphicObjects::eta->push_back(mu_eta->at(sublead_mu));
	graphicObjects::phi->push_back(mu_phi->at(sublead_mu));
	graphicObjects::px->push_back(mu_px->at(sublead_mu));
	graphicObjects::py->push_back(mu_py->at(sublead_mu));
	graphicObjects::pz->push_back(mu_pz->at(sublead_mu));
	graphicObjects::charge->push_back(mu_charge->at(sublead_mu));
	graphicObjects::allauthor->push_back(mu_allauthor->at(sublead_mu));
	graphicObjects::author->push_back(mu_author->at(sublead_mu));
	graphicObjects::beta->push_back(mu_beta->at(sublead_mu));
	graphicObjects::isMuonLikelihood->push_back(mu_isMuonLikelihood->at(sublead_mu));
	graphicObjects::matchchi2->push_back(mu_matchchi2->at(sublead_mu));
	graphicObjects::matchndof->push_back(mu_matchndof->at(sublead_mu));
	graphicObjects::etcone20->push_back(mu_etcone20->at(sublead_mu));
	graphicObjects::etcone30->push_back(mu_etcone30->at(sublead_mu));
	graphicObjects::etcone40->push_back(mu_etcone40->at(sublead_mu));
	graphicObjects::nucone20->push_back(mu_nucone20->at(sublead_mu));
	graphicObjects::nucone30->push_back(mu_nucone30->at(sublead_mu));
	graphicObjects::nucone40->push_back(mu_nucone40->at(sublead_mu));
	graphicObjects::ptcone20->push_back(mu_ptcone20->at(sublead_mu));
	graphicObjects::ptcone30->push_back(mu_ptcone30->at(sublead_mu));
	graphicObjects::ptcone40->push_back(mu_ptcone40->at(sublead_mu));
	graphicObjects::energyLossPar->push_back(mu_energyLossPar->at(sublead_mu));
	graphicObjects::energyLossErr->push_back(mu_energyLossErr->at(sublead_mu));
	graphicObjects::etCore->push_back(mu_etCore->at(sublead_mu));
	graphicObjects::energyLossType->push_back(mu_energyLossType->at(sublead_mu));
	graphicObjects::caloMuonIdTag->push_back(mu_caloMuonIdTag->at(sublead_mu));
	graphicObjects::caloLRLikelihood->push_back(mu_caloLRLikelihood->at(sublead_mu));
	graphicObjects::bestMatch->push_back(mu_bestMatch->at(sublead_mu));
	graphicObjects::isStandAloneMuon->push_back(mu_isStandAloneMuon->at(sublead_mu));
	graphicObjects::isCombinedMuon->push_back(mu_isCombinedMuon->at(sublead_mu));
	graphicObjects::isLowPtReconstructedMuon->push_back(mu_isLowPtReconstructedMuon->at(sublead_mu));
	graphicObjects::loose->push_back(mu_loose->at(sublead_mu));
	graphicObjects::medium->push_back(mu_medium->at(sublead_mu));
	graphicObjects::tight->push_back(mu_tight->at(sublead_mu));
	graphicObjects::d0_exPV->push_back(mu_d0_exPV->at(sublead_mu));
	graphicObjects::z0_exPV->push_back(mu_z0_exPV->at(sublead_mu));
	graphicObjects::phi_exPV->push_back(mu_phi_exPV->at(sublead_mu));
	graphicObjects::theta_exPV->push_back(mu_theta_exPV->at(sublead_mu));
	graphicObjects::qoverp_exPV->push_back(mu_qoverp_exPV->at(sublead_mu));
	graphicObjects::cb_d0_exPV->push_back(mu_cb_d0_exPV->at(sublead_mu));
	graphicObjects::cb_z0_exPV->push_back(mu_cb_z0_exPV->at(sublead_mu));
	graphicObjects::cb_phi_exPV->push_back(mu_cb_phi_exPV->at(sublead_mu));
	graphicObjects::cb_theta_exPV->push_back(mu_cb_theta_exPV->at(sublead_mu));
	graphicObjects::cb_qoverp_exPV->push_back(mu_cb_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_d0_exPV->push_back(mu_id_d0_exPV->at(sublead_mu));
	graphicObjects::id_z0_exPV->push_back(mu_id_z0_exPV->at(sublead_mu));
	graphicObjects::id_phi_exPV->push_back(mu_id_phi_exPV->at(sublead_mu));
	graphicObjects::id_theta_exPV->push_back(mu_id_theta_exPV->at(sublead_mu));
	graphicObjects::id_qoverp_exPV->push_back(mu_id_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_d0_exPV->push_back(mu_me_d0_exPV->at(sublead_mu));
	graphicObjects::me_z0_exPV->push_back(mu_me_z0_exPV->at(sublead_mu));
	graphicObjects::me_phi_exPV->push_back(mu_me_phi_exPV->at(sublead_mu));
	graphicObjects::me_theta_exPV->push_back(mu_me_theta_exPV->at(sublead_mu));
	graphicObjects::me_qoverp_exPV->push_back(mu_me_qoverp_exPV->at(sublead_mu));
	graphicObjects::ie_d0_exPV->push_back(mu_ie_d0_exPV->at(sublead_mu));
	graphicObjects::ie_z0_exPV->push_back(mu_ie_z0_exPV->at(sublead_mu));
	graphicObjects::ie_phi_exPV->push_back(mu_ie_phi_exPV->at(sublead_mu));
	graphicObjects::ie_theta_exPV->push_back(mu_ie_theta_exPV->at(sublead_mu));
	graphicObjects::ie_qoverp_exPV->push_back(mu_ie_qoverp_exPV->at(sublead_mu));
	//graphicObjects::SpaceTime_detID->push_back(mu_SpaceTime_detID->at(sublead_mu));
	//graphicObjects::SpaceTime_t->push_back(mu_SpaceTime_t->at(sublead_mu));
	//graphicObjects::SpaceTime_tError->push_back(mu_SpaceTime_tError->at(sublead_mu));
	//graphicObjects::SpaceTime_weight->push_back(mu_SpaceTime_weight->at(sublead_mu));
	//graphicObjects::SpaceTime_x->push_back(mu_SpaceTime_x->at(sublead_mu));
	//graphicObjects::SpaceTime_y->push_back(mu_SpaceTime_y->at(sublead_mu));
	//graphicObjects::SpaceTime_z->push_back(mu_SpaceTime_z->at(sublead_mu));
	//graphicObjects::SpaceTime_t_Tile->push_back(mu_SpaceTime_t_Tile->at(sublead_mu));
	//graphicObjects::SpaceTime_tError_Tile->push_back(mu_SpaceTime_tError_Tile->at(sublead_mu));
	//graphicObjects::SpaceTime_weight_Tile->push_back(mu_SpaceTime_weight_Tile->at(sublead_mu));
	//graphicObjects::SpaceTime_x_Tile->push_back(mu_SpaceTime_x_Tile->at(sublead_mu));
	//graphicObjects::SpaceTime_y_Tile->push_back(mu_SpaceTime_y_Tile->at(sublead_mu));
	//graphicObjects::SpaceTime_z_Tile->push_back(mu_SpaceTime_z_Tile->at(sublead_mu));
	//graphicObjects::SpaceTime_t_TRT->push_back(mu_SpaceTime_t_TRT->at(sublead_mu));
	//graphicObjects::SpaceTime_tError_TRT->push_back(mu_SpaceTime_tError_TRT->at(sublead_mu));
	//graphicObjects::SpaceTime_weight_TRT->push_back(mu_SpaceTime_weight_TRT->at(sublead_mu));
	//graphicObjects::SpaceTime_x_TRT->push_back(mu_SpaceTime_x_TRT->at(sublead_mu));
	//graphicObjects::SpaceTime_y_TRT->push_back(mu_SpaceTime_y_TRT->at(sublead_mu));
	//graphicObjects::SpaceTime_z_TRT->push_back(mu_SpaceTime_z_TRT->at(sublead_mu));
	//graphicObjects::SpaceTime_t_MDT->push_back(mu_SpaceTime_t_MDT->at(sublead_mu));
	//graphicObjects::SpaceTime_tError_MDT->push_back(mu_SpaceTime_tError_MDT->at(sublead_mu));
	//graphicObjects::SpaceTime_weight_MDT->push_back(mu_SpaceTime_weight_MDT->at(sublead_mu));
	//graphicObjects::SpaceTime_x_MDT->push_back(mu_SpaceTime_x_MDT->at(sublead_mu));
	//graphicObjects::SpaceTime_y_MDT->push_back(mu_SpaceTime_y_MDT->at(sublead_mu));
	//graphicObjects::SpaceTime_z_MDT->push_back(mu_SpaceTime_z_MDT->at(sublead_mu));
	graphicObjects::TileCellEnergyLayer1->push_back(mu_TileCellEnergyLayer1->at(sublead_mu));
	graphicObjects::TileTimeLayer1->push_back(mu_TileTimeLayer1->at(sublead_mu));
	graphicObjects::TileCellRmsNoiseLayer1->push_back(mu_TileCellRmsNoiseLayer1->at(sublead_mu));
	graphicObjects::TileCellSignLayer1->push_back(mu_TileCellSignLayer1->at(sublead_mu));
	graphicObjects::TileCellEnergyLayer2->push_back(mu_TileCellEnergyLayer2->at(sublead_mu));
	graphicObjects::TileTimeLayer2->push_back(mu_TileTimeLayer2->at(sublead_mu));
	graphicObjects::TileCellRmsNoiseLayer2->push_back(mu_TileCellRmsNoiseLayer2->at(sublead_mu));
	graphicObjects::TileCellSignLayer2->push_back(mu_TileCellSignLayer2->at(sublead_mu));
	graphicObjects::TileCellEnergyLayer3->push_back(mu_TileCellEnergyLayer3->at(sublead_mu));
	graphicObjects::TileTimeLayer3->push_back(mu_TileTimeLayer3->at(sublead_mu));
	graphicObjects::TileCellRmsNoiseLayer3->push_back(mu_TileCellRmsNoiseLayer3->at(sublead_mu));
	graphicObjects::TileCellSignLayer3->push_back(mu_TileCellSignLayer3->at(sublead_mu));
	graphicObjects::MSTrkT0_1->push_back(mu_MSTrkT0_1->at(sublead_mu));
	graphicObjects::MSTrkT0_2->push_back(mu_MSTrkT0_2->at(sublead_mu));
	graphicObjects::MSTrkT0_3->push_back(mu_MSTrkT0_3->at(sublead_mu));
	graphicObjects::cov_d0_exPV->push_back(mu_cov_d0_exPV->at(sublead_mu));
	graphicObjects::cov_z0_exPV->push_back(mu_cov_z0_exPV->at(sublead_mu));
	graphicObjects::cov_phi_exPV->push_back(mu_cov_phi_exPV->at(sublead_mu));
	graphicObjects::cov_theta_exPV->push_back(mu_cov_theta_exPV->at(sublead_mu));
	graphicObjects::cov_qoverp_exPV->push_back(mu_cov_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_d0_z0_exPV->push_back(mu_cov_d0_z0_exPV->at(sublead_mu));
	graphicObjects::cov_d0_phi_exPV->push_back(mu_cov_d0_phi_exPV->at(sublead_mu));
	graphicObjects::cov_d0_theta_exPV->push_back(mu_cov_d0_theta_exPV->at(sublead_mu));
	graphicObjects::cov_d0_qoverp_exPV->push_back(mu_cov_d0_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_z0_phi_exPV->push_back(mu_cov_z0_phi_exPV->at(sublead_mu));
	graphicObjects::cov_z0_theta_exPV->push_back(mu_cov_z0_theta_exPV->at(sublead_mu));
	graphicObjects::cov_z0_qoverp_exPV->push_back(mu_cov_z0_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_phi_theta_exPV->push_back(mu_cov_phi_theta_exPV->at(sublead_mu));
	graphicObjects::cov_phi_qoverp_exPV->push_back(mu_cov_phi_qoverp_exPV->at(sublead_mu));
	graphicObjects::cov_theta_qoverp_exPV->push_back(mu_cov_theta_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_exPV->push_back(mu_id_cov_d0_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_exPV->push_back(mu_id_cov_z0_exPV->at(sublead_mu));
	graphicObjects::id_cov_phi_exPV->push_back(mu_id_cov_phi_exPV->at(sublead_mu));
	graphicObjects::id_cov_theta_exPV->push_back(mu_id_cov_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_qoverp_exPV->push_back(mu_id_cov_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_z0_exPV->push_back(mu_id_cov_d0_z0_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_phi_exPV->push_back(mu_id_cov_d0_phi_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_theta_exPV->push_back(mu_id_cov_d0_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_d0_qoverp_exPV->push_back(mu_id_cov_d0_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_phi_exPV->push_back(mu_id_cov_z0_phi_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_theta_exPV->push_back(mu_id_cov_z0_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_z0_qoverp_exPV->push_back(mu_id_cov_z0_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_phi_theta_exPV->push_back(mu_id_cov_phi_theta_exPV->at(sublead_mu));
	graphicObjects::id_cov_phi_qoverp_exPV->push_back(mu_id_cov_phi_qoverp_exPV->at(sublead_mu));
	graphicObjects::id_cov_theta_qoverp_exPV->push_back(mu_id_cov_theta_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_exPV->push_back(mu_me_cov_d0_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_exPV->push_back(mu_me_cov_z0_exPV->at(sublead_mu));
	graphicObjects::me_cov_phi_exPV->push_back(mu_me_cov_phi_exPV->at(sublead_mu));
	graphicObjects::me_cov_theta_exPV->push_back(mu_me_cov_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_qoverp_exPV->push_back(mu_me_cov_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_z0_exPV->push_back(mu_me_cov_d0_z0_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_phi_exPV->push_back(mu_me_cov_d0_phi_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_theta_exPV->push_back(mu_me_cov_d0_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_d0_qoverp_exPV->push_back(mu_me_cov_d0_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_phi_exPV->push_back(mu_me_cov_z0_phi_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_theta_exPV->push_back(mu_me_cov_z0_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_z0_qoverp_exPV->push_back(mu_me_cov_z0_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_phi_theta_exPV->push_back(mu_me_cov_phi_theta_exPV->at(sublead_mu));
	graphicObjects::me_cov_phi_qoverp_exPV->push_back(mu_me_cov_phi_qoverp_exPV->at(sublead_mu));
	graphicObjects::me_cov_theta_qoverp_exPV->push_back(mu_me_cov_theta_qoverp_exPV->at(sublead_mu));
	graphicObjects::ms_d0->push_back(mu_ms_d0->at(sublead_mu));
	graphicObjects::ms_z0->push_back(mu_ms_z0->at(sublead_mu));
	graphicObjects::ms_phi->push_back(mu_ms_phi->at(sublead_mu));
	graphicObjects::ms_theta->push_back(mu_ms_theta->at(sublead_mu));
	graphicObjects::ms_qoverp->push_back(mu_ms_qoverp->at(sublead_mu));
	graphicObjects::id_d0->push_back(mu_id_d0->at(sublead_mu));
	graphicObjects::id_z0->push_back(mu_id_z0->at(sublead_mu));
	graphicObjects::id_phi->push_back(mu_id_phi->at(sublead_mu));
	graphicObjects::id_theta->push_back(mu_id_theta->at(sublead_mu));
	graphicObjects::id_qoverp->push_back(mu_id_qoverp->at(sublead_mu));
	graphicObjects::me_d0->push_back(mu_me_d0->at(sublead_mu));
	graphicObjects::me_z0->push_back(mu_me_z0->at(sublead_mu));
	graphicObjects::me_phi->push_back(mu_me_phi->at(sublead_mu));
	graphicObjects::me_theta->push_back(mu_me_theta->at(sublead_mu));
	graphicObjects::me_qoverp->push_back(mu_me_qoverp->at(sublead_mu));
	graphicObjects::ie_d0->push_back(mu_ie_d0->at(sublead_mu));
	graphicObjects::ie_z0->push_back(mu_ie_z0->at(sublead_mu));
	graphicObjects::ie_phi->push_back(mu_ie_phi->at(sublead_mu));
	graphicObjects::ie_theta->push_back(mu_ie_theta->at(sublead_mu));
	graphicObjects::ie_qoverp->push_back(mu_ie_qoverp->at(sublead_mu));
	graphicObjects::nOutliersOnTrack->push_back(mu_nOutliersOnTrack->at(sublead_mu));
	graphicObjects::nBLHits->push_back(mu_nBLHits->at(sublead_mu));
	graphicObjects::nPixHits->push_back(mu_nPixHits->at(sublead_mu));
	graphicObjects::nSCTHits->push_back(mu_nSCTHits->at(sublead_mu));
	graphicObjects::nTRTHits->push_back(mu_nTRTHits->at(sublead_mu));
	graphicObjects::nTRTHighTHits->push_back(mu_nTRTHighTHits->at(sublead_mu));
	graphicObjects::nBLSharedHits->push_back(mu_nBLSharedHits->at(sublead_mu));
	graphicObjects::nPixSharedHits->push_back(mu_nPixSharedHits->at(sublead_mu));
	graphicObjects::nPixHoles->push_back(mu_nPixHoles->at(sublead_mu));
	graphicObjects::nSCTSharedHits->push_back(mu_nSCTSharedHits->at(sublead_mu));
	graphicObjects::nSCTHoles->push_back(mu_nSCTHoles->at(sublead_mu));
	graphicObjects::nTRTOutliers->push_back(mu_nTRTOutliers->at(sublead_mu));
	graphicObjects::nTRTHighTOutliers->push_back(mu_nTRTHighTOutliers->at(sublead_mu));
	graphicObjects::nGangedPixels->push_back(mu_nGangedPixels->at(sublead_mu));
	graphicObjects::nPixelDeadSensors->push_back(mu_nPixelDeadSensors->at(sublead_mu));
	graphicObjects::nSCTDeadSensors->push_back(mu_nSCTDeadSensors->at(sublead_mu));
	graphicObjects::nTRTDeadStraws->push_back(mu_nTRTDeadStraws->at(sublead_mu));
	graphicObjects::expectBLayerHit->push_back(mu_expectBLayerHit->at(sublead_mu));
	graphicObjects::nMDTHits->push_back(mu_nMDTHits->at(sublead_mu));
	graphicObjects::nMDTHoles->push_back(mu_nMDTHoles->at(sublead_mu));
	graphicObjects::nCSCEtaHits->push_back(mu_nCSCEtaHits->at(sublead_mu));
	graphicObjects::nCSCEtaHoles->push_back(mu_nCSCEtaHoles->at(sublead_mu));
	graphicObjects::nCSCPhiHits->push_back(mu_nCSCPhiHits->at(sublead_mu));
	graphicObjects::nCSCPhiHoles->push_back(mu_nCSCPhiHoles->at(sublead_mu));
	graphicObjects::nRPCEtaHits->push_back(mu_nRPCEtaHits->at(sublead_mu));
	graphicObjects::nRPCEtaHoles->push_back(mu_nRPCEtaHoles->at(sublead_mu));
	graphicObjects::nRPCPhiHits->push_back(mu_nRPCPhiHits->at(sublead_mu));
	graphicObjects::nRPCPhiHoles->push_back(mu_nRPCPhiHoles->at(sublead_mu));
	graphicObjects::nTGCEtaHits->push_back(mu_nTGCEtaHits->at(sublead_mu));
	graphicObjects::nTGCEtaHoles->push_back(mu_nTGCEtaHoles->at(sublead_mu));
	graphicObjects::nTGCPhiHits->push_back(mu_nTGCPhiHits->at(sublead_mu));
	graphicObjects::nTGCPhiHoles->push_back(mu_nTGCPhiHoles->at(sublead_mu));
	graphicObjects::nMDTBIHits->push_back(mu_nMDTBIHits->at(sublead_mu));
	graphicObjects::nMDTBMHits->push_back(mu_nMDTBMHits->at(sublead_mu));
	graphicObjects::nMDTBOHits->push_back(mu_nMDTBOHits->at(sublead_mu));
	graphicObjects::nMDTBEEHits->push_back(mu_nMDTBEEHits->at(sublead_mu));
	graphicObjects::nMDTBIS78Hits->push_back(mu_nMDTBIS78Hits->at(sublead_mu));
	graphicObjects::nMDTEIHits->push_back(mu_nMDTEIHits->at(sublead_mu));
	graphicObjects::nMDTEMHits->push_back(mu_nMDTEMHits->at(sublead_mu));
	graphicObjects::nMDTEOHits->push_back(mu_nMDTEOHits->at(sublead_mu));
	graphicObjects::nMDTEEHits->push_back(mu_nMDTEEHits->at(sublead_mu));
	graphicObjects::nRPCLayer1EtaHits->push_back(mu_nRPCLayer1EtaHits->at(sublead_mu));
	graphicObjects::nRPCLayer2EtaHits->push_back(mu_nRPCLayer2EtaHits->at(sublead_mu));
	graphicObjects::nRPCLayer3EtaHits->push_back(mu_nRPCLayer3EtaHits->at(sublead_mu));
	graphicObjects::nRPCLayer1PhiHits->push_back(mu_nRPCLayer1PhiHits->at(sublead_mu));
	graphicObjects::nRPCLayer2PhiHits->push_back(mu_nRPCLayer2PhiHits->at(sublead_mu));
	graphicObjects::nRPCLayer3PhiHits->push_back(mu_nRPCLayer3PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer1EtaHits->push_back(mu_nTGCLayer1EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer2EtaHits->push_back(mu_nTGCLayer2EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer3EtaHits->push_back(mu_nTGCLayer3EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer4EtaHits->push_back(mu_nTGCLayer4EtaHits->at(sublead_mu));
	graphicObjects::nTGCLayer1PhiHits->push_back(mu_nTGCLayer1PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer2PhiHits->push_back(mu_nTGCLayer2PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer3PhiHits->push_back(mu_nTGCLayer3PhiHits->at(sublead_mu));
	graphicObjects::nTGCLayer4PhiHits->push_back(mu_nTGCLayer4PhiHits->at(sublead_mu));
	graphicObjects::barrelSectors->push_back(mu_barrelSectors->at(sublead_mu));
	graphicObjects::endcapSectors->push_back(mu_endcapSectors->at(sublead_mu));
	graphicObjects::trackd0->push_back(mu_trackd0->at(sublead_mu));
	graphicObjects::trackz0->push_back(mu_trackz0->at(sublead_mu));
	graphicObjects::trackphi->push_back(mu_trackphi->at(sublead_mu));
	graphicObjects::tracktheta->push_back(mu_tracktheta->at(sublead_mu));
	graphicObjects::trackqoverp->push_back(mu_trackqoverp->at(sublead_mu));
	graphicObjects::trackcov_d0->push_back(mu_trackcov_d0->at(sublead_mu));
	graphicObjects::trackcov_z0->push_back(mu_trackcov_z0->at(sublead_mu));
	graphicObjects::trackcov_phi->push_back(mu_trackcov_phi->at(sublead_mu));
	graphicObjects::trackcov_theta->push_back(mu_trackcov_theta->at(sublead_mu));
	graphicObjects::trackcov_qoverp->push_back(mu_trackcov_qoverp->at(sublead_mu));
	graphicObjects::trackcov_d0_z0->push_back(mu_trackcov_d0_z0->at(sublead_mu));
	graphicObjects::trackcov_d0_phi->push_back(mu_trackcov_d0_phi->at(sublead_mu));
	graphicObjects::trackcov_d0_theta->push_back(mu_trackcov_d0_theta->at(sublead_mu));
	graphicObjects::trackcov_d0_qoverp->push_back(mu_trackcov_d0_qoverp->at(sublead_mu));
	graphicObjects::trackcov_z0_phi->push_back(mu_trackcov_z0_phi->at(sublead_mu));
	graphicObjects::trackcov_z0_theta->push_back(mu_trackcov_z0_theta->at(sublead_mu));
	graphicObjects::trackcov_z0_qoverp->push_back(mu_trackcov_z0_qoverp->at(sublead_mu));
	graphicObjects::trackcov_phi_theta->push_back(mu_trackcov_phi_theta->at(sublead_mu));
	graphicObjects::trackcov_phi_qoverp->push_back(mu_trackcov_phi_qoverp->at(sublead_mu));
	graphicObjects::trackcov_theta_qoverp->push_back(mu_trackcov_theta_qoverp->at(sublead_mu));
	graphicObjects::trackfitchi2->push_back(mu_trackfitchi2->at(sublead_mu));
	graphicObjects::trackfitndof->push_back(mu_trackfitndof->at(sublead_mu));
	graphicObjects::hastrack->push_back(mu_hastrack->at(sublead_mu));
	if(isMC)
	{
		graphicObjects::truth_dr->push_back(mu_truth_dr->at(sublead_mu));
		graphicObjects::truth_E->push_back(mu_truth_E->at(sublead_mu));
		graphicObjects::truth_pt->push_back(mu_truth_pt->at(sublead_mu));
		graphicObjects::truth_eta->push_back(mu_truth_eta->at(sublead_mu));
		graphicObjects::truth_phi->push_back(mu_truth_phi->at(sublead_mu));
		graphicObjects::truth_type->push_back(mu_truth_type->at(sublead_mu));
		graphicObjects::truth_status->push_back(mu_truth_status->at(sublead_mu));
		graphicObjects::truth_barcode->push_back(mu_truth_barcode->at(sublead_mu));
		graphicObjects::truth_mothertype->push_back(mu_truth_mothertype->at(sublead_mu));
		graphicObjects::truth_motherbarcode->push_back(mu_truth_motherbarcode->at(sublead_mu));
		graphicObjects::truth_matched->push_back(mu_truth_matched->at(sublead_mu));
	}
	graphicObjects::EFCB_dr->push_back(mu_EFCB_dr->at(sublead_mu));
	graphicObjects::EFCB_index->push_back(mu_EFCB_index->at(sublead_mu));
	graphicObjects::EFMG_dr->push_back(mu_EFMG_dr->at(sublead_mu));
	graphicObjects::EFMG_index->push_back(mu_EFMG_index->at(sublead_mu));
	graphicObjects::EFME_dr->push_back(mu_EFME_dr->at(sublead_mu));
	graphicObjects::EFME_index->push_back(mu_EFME_index->at(sublead_mu));
	graphicObjects::L2CB_dr->push_back(mu_L2CB_dr->at(sublead_mu));
	graphicObjects::L2CB_index->push_back(mu_L2CB_index->at(sublead_mu));
	graphicObjects::L1_dr->push_back(mu_L1_dr->at(sublead_mu));
	graphicObjects::L1_index->push_back(mu_L1_index->at(sublead_mu));
	
	/////////////////////////////////////////////////////
	// fill the all cuts tree ///////////////////////////
	tree_allCuts->Fill(); ///////////////////////////////
	if(m_allCuts_counter%m_trees_counter_mod==0) ////////
	{                             ///////////////////////
		tree_allCuts->FlushBaskets(); ///////////////////
		//tree_allCuts->Write("", TObject::kOverwrite); ///
	} ///////////////////////////////////////////////////
	m_allCuts_counter++; ////////////////////////////////
	/////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////
	// for the Afb calculation ////////////////////////////////////////////
	fillAfbMap(current_imass,current_cosThetaCS,current_cosThetaHE); //////
	///////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////
	// fill the xVector for the ML fit: /////////
	fillXvec( current_imass ); //////////////////
	/////////////////////////////////////////////
}

void analysisSkeleton::fillBeforeCuts()
{
	int muSize = (int)mu_pt->size();

	if(muSize==2)
	{
		TLorentzVector* p1 = new TLorentzVector();
		TLorentzVector* p2 = new TLorentzVector();
		p1->SetPtEtaPhiM( mu_pt->at(0)*MeV2TeV, mu_eta->at(0), mu_phi->at(0), muonMass*GeV2TeV);
		p2->SetPtEtaPhiM( mu_pt->at(1)*MeV2TeV, mu_eta->at(1), mu_phi->at(1), muonMass*GeV2TeV);
		current_cosmicCosth = cosThetaDimu(p1,p2);
		h1_cosmicCosth->Fill( current_cosmicCosth );
		delete p1;
		delete p2;
		
		h1_d0exPV->Fill(mu_d0_exPV->at(0));
		h1_d0exPV->Fill(mu_d0_exPV->at(1));
		
		h1_z0exPV->Fill(mu_z0_exPV->at(0));
		h1_z0exPV->Fill(mu_z0_exPV->at(1));
		
		//X( prtD0*cos(phi) );
		//Y( prtD0*sin(phi) );
		//Z( Z0 );
		h2_xyVertex->Fill( mu_d0_exPV->at(0)*cos(mu_phi->at(0)), mu_d0_exPV->at(0)*sin(mu_phi->at(0)) );
		h2_xyVertex->Fill( mu_d0_exPV->at(1)*cos(mu_phi->at(1)), mu_d0_exPV->at(1)*sin(mu_phi->at(1)) );
	}
}

void analysisSkeleton::fillCutFlow(string sorderedcutname, string sIsPreselection)
{
	/////////////////////////////////////////////////////////
	// count the cut flow numbers ///////////////////////////
	m_cutFlowNumbers->operator[](sorderedcutname)++; ////////
	/////////////////////////////////////////////////////////

	/////////////////////////////////
	// THIS IS DEPRECATED !!!! //////
	/////////////////////////////////
	int muSize = (int)mu_pt->size();
	if(sIsPreselection != "preselection"  &&  muSize==2)
	{
		//int lead_mu = (mu_charge->at(0)<0) ? 0 : 1;
		//int sublead_mu  = (mu_charge->at(0)>0) ? 0 : 1;
		int lead_mu     = 0;
		int sublead_mu  = 1;
		if( mu_pt->at(0) < mu_pt->at(1) )
		{
			lead_mu     = 1;
			sublead_mu  = 0;
		}

		if(values2fill.size()>0) values2fill.clear();
		
		current_imass    = imass(pmu[lead_mu],pmu[sublead_mu]);
		current_mu_pT    = mu_pt->at(lead_mu)*MeV2TeV; //pT(mu_me_qoverp->at(lead_mu),mu_me_theta->at(lead_mu))*MeV2TeV;
		current_cosTheta = cosThetaCollinsSoper( pmu[lead_mu], -1, pmu[sublead_mu], +1 );
		
		///////////////////////////////////////////////////////////////////////
		// these values go in the cutFlow histograms //////////////////////////
		values2fill.insert( make_pair( "imass",current_imass ) ); /////////////
		values2fill.insert( make_pair( "pT",   current_mu_pT ) ); /////////////
		///////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		// fill the cut flow histopgrams //////////////////////////////////////////////////////////////
		hmap_cutFlow_imass->operator[]("imass."+sorderedcutname)->Fill( values2fill["imass"] ); ///////
		hmap_cutFlow_pT->operator[]("pT."+sorderedcutname)->Fill( values2fill["pT"] ); ////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int analysisSkeleton::countQAflags()
{
	int nGoodQAflags = 0;
	int muSize = (int)mu_pt->size();
	if(pTtoIndexMap.size()>0) pTtoIndexMap.clear();
	// count the good muons and find their id's
	for(int mu=0 ; mu<muSize ; mu++)
	{
		if(muQAflags[mu])
		{
			pTtoIndexMap.insert( make_pair( mu_pt->at(mu) , mu ) );
			nGoodQAflags++;
		}
	}
	
	return nGoodQAflags;
}

void analysisSkeleton::pTSort()
{
	// the map is already sorted by the pT size but,
	// from the lowest to the highest, so there's
	// no need to convert values.
	// the following line defines the reversed iterator
	// so the "rbegin()" points the iterator to the entry
	// with the largest pT and so on.
	
	if(pTtoIndexMap.size()<2)
	{
		cout << "ERROR: in pTSort(), trying to sort a <2 map. Exitting now !" << endl;
		exit(-1);
	}
	
	///////////////////////////////////////////////////////////////////////////////
	// no matter how many entries in the map, just take the 2 with highest pT: ////
	TMapdi::reverse_iterator rit=pTtoIndexMap.rbegin(); ///////////////////////////
	ai = rit->second; /////////////////////////////////////////////////////////////
	rit++; ////////////////////////////////////////////////////////////////////////
	bi = rit->second; /////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
}

void analysisSkeleton::imassSort()
{
	float im   = 0.;
	float max  = 0.;
	int muSize = (int)mu_pt->size();
	for(int i=0 ; i<muSize ; i++)
	{
		for(int j=0 ; j<muSize && j!=i ; j++)
		{
			if(muQAflags[i]  &&  muQAflags[j])
			{
				im = imass(pmu[i], pmu[j]);
				if(im>max)
				{
					max = im;
					ai = i;
					bi = j;
				}
			}
		}
	}
}

void analysisSkeleton::buildMU4Vector(int nMus)
{
	wipeMU4Vector();
	for(int n=0 ; n<nMus ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( mu_px->at(n)*MeV2TeV );
		pmu[n]->SetPy( mu_py->at(n)*MeV2TeV );
		pmu[n]->SetPz( mu_pz->at(n)*MeV2TeV );
		pmu[n]->SetE(  mu_E->at(n)*MeV2TeV );
	}
}

void analysisSkeleton::buildMU4Vector(int nMus, string fromAngles)
{
	if(fromAngles=="")
	{
		cout << "you should call buildMU4Vector(int nMus) instead" << endl;
	}
	else
	{
		wipeMU4Vector();
		for(int n=0 ; n<nMus ; n++)
		{
			pmu.push_back( new TLorentzVector() );
			pmu[n]->SetPtEtaPhiM( mu_pt->at(n)*MeV2TeV, mu_eta->at(n), mu_phi->at(n), muonMass*GeV2TeV);
		}
	}
}

void analysisSkeleton::wipeMU4Vector()
{
	int nMus = (int)pmu.size();
	if(nMus>0)
	{
		for(int n=0 ; n<nMus ; n++)
		{
			if(pmu[n]) delete pmu[n];
		}
		pmu.clear();
	}
}

bool analysisSkeleton::assignPairIndices()
{
	// select the final muon pair
	if(pTtoIndexMap.size()==2)
	{
		pTSort();
		//ai = 0;
		//bi = 1;
	}
	else if(pTtoIndexMap.size()>2)
	{
		pTSort();
		//imassSort();
		nMultiMuonEvents++;
	}
	else
	{
		cout << "WARNING: in analysisSkeleton::assignPairIndices, but there are <2 good single-muons" << endl;
		return false;
	}
	
	if(!muQAflags[ai] || !muQAflags[bi]) return false;
	
	return true;
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


bool analysisSkeleton::applyPreselection()
{
	///////////////////////////////////////////
	// do not skip this for correct counting //
	incrementNallEvents(); ////////////////////
	///////////////////////////////////////////

	TMapsb cutsToSkip; // dummy (empty)
	passCutFlow = preselection(cutsToSkip);
	
	return passCutFlow;
}

bool analysisSkeleton::applySingleMuonSelection()
{
	////////////////////////////////////////
	// fill the NO CUTS items //////////////
	fillBeforeCuts(); //////////////////////
	////////////////////////////////////////
	
	inApplySingleSelection = true;
	
	TMapsb cutsToSkip; // dummy (empty)
	passCutFlow = singleSelection(cutsToSkip);
	
	inApplySingleSelection = false;
	
	return passCutFlow;
}

bool analysisSkeleton::applyDoubleMuonSelection(bool isMC)
{
	TMapsb cutsToSkip; // dummy (empty)
	passCutFlow = doubleSelection(cutsToSkip);
	
	if(passCutFlow)
	{
		///////////////////////////////////////////////
		// fill the cutFlow and the allCuts items /////
		fillAfterCuts(isMC); //////////////////////////////
		///////////////////////////////////////////////
		
		////////////////////////////////////////////////////
		// dump events. only if doEventDump==true //////////
		runEventDumper(); //////////////////////////////////
		////////////////////////////////////////////////////
	}
	
	return passCutFlow;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void analysisSkeleton::fillCutProfile1D()
{
	bool pass;
	
	for(TMapSP2TH1D::iterator it=h1map_cutProfile->begin() ; it!=h1map_cutProfile->end() ; it++)
	{
		string sname = it->first;
		
		string snameNoSuffix = sname;
		string suffix = sname.substr(sname.length()-2,sname.length()-1);
		if(suffix=="_1"  ||  suffix=="_2") snameNoSuffix = sname.substr(0,sname.length()-2);
	
		// do the ms hits cut only once...
		if(snameNoSuffix=="nMDTBI")
		{
			snameNoSuffix = "msHitsRel16";
			sname         = snameNoSuffix;
		}
		else if(snameNoSuffix=="nMDTBM")    continue;
		else if(snameNoSuffix=="nMDTBO")    continue;
		else if(snameNoSuffix=="nMDTEI")    continue;
		else if(snameNoSuffix=="nMDTEM")    continue;
		else if(snameNoSuffix=="nMDTEO")    continue;
		else if(snameNoSuffix=="nMDTBEE")   continue;
		else if(snameNoSuffix=="nMDTEE")    continue;
		else if(snameNoSuffix=="nMDTBIS78") continue;
		else if(snameNoSuffix=="nMDTBI")    continue;
		else if(snameNoSuffix=="nRPCPhi1")  continue;
		else if(snameNoSuffix=="nRPCPhi2")  continue;
		else if(snameNoSuffix=="nRPCPhi3")  continue;
		else if(snameNoSuffix=="nTGCPhi1")  continue;
		else if(snameNoSuffix=="nTGCPhi2")  continue;
		else if(snameNoSuffix=="nTGCPhi3")  continue;
		else if(snameNoSuffix=="nTGCPhi4")  continue;
		else if(snameNoSuffix=="nCSCEta")   continue;
		else if(snameNoSuffix=="nCSCPhi")   continue;
		
		// do the id hits cut only once...
		if(snameNoSuffix=="expectBLayerHit")
		{
			snameNoSuffix = "idHitsRel16";
			sname         = snameNoSuffix;
		}
		else if(snameNoSuffix=="nBLHits")           continue;
		else if(snameNoSuffix=="nPixHits")          continue;
		else if(snameNoSuffix=="nPixelDeadSensors") continue;
		else if(snameNoSuffix=="nPixHoles")         continue;
		else if(snameNoSuffix=="nSCTHits")          continue;
		else if(snameNoSuffix=="nSCTDeadSensors")   continue;
		else if(snameNoSuffix=="nSCTHoles")         continue;
		else if(snameNoSuffix=="nTRTHits")          continue;
		else if(snameNoSuffix=="nTRTOutliers")      continue;
		else if(snameNoSuffix=="TRTHitsVSeta")      continue;
		else if(snameNoSuffix=="nTRTOutliersVSeta") continue;
		
		
		// apply the cut:
		pass = true;
		pass = (pass && preselection(snameNoSuffix))    ? true : false;
		pass = (pass && singleSelection(snameNoSuffix)) ? true : false;
		pass = (pass && doubleSelection(snameNoSuffix)) ? true : false;
		
		if(pass)
		{
			if     (sname=="GRL")     (*h1map_cutProfile)[sname]->Fill( isGRL );
			else if(sname=="Trigger")
			{
				int trigDecision = 0;
				for(int t=0 ; t<(int)vTriggers->size() ; t++)
				{
					if( isTrigger(vTriggers->at(t)) )
					{
						trigDecision = 1;
						break;
					}
				}
				(*h1map_cutProfile)[sname]->Fill( trigDecision );
			}
			else if(sname=="pT_1")
			{ 
				(*h1map_cutProfile)[sname]->Fill( mu_pt->at(ai)*MeV2TeV );
				pT_profile->push_back( mu_pt->at(ai)*MeV2TeV );
			}
			else if(sname=="pT_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_pt->at(bi)*MeV2TeV );
				pT_profile->push_back( mu_pt->at(bi)*MeV2TeV );
			}
			
			else if(sname=="pT_loose_1")
			{ 
				(*h1map_cutProfile)[sname]->Fill( mu_pt->at(ai)*MeV2TeV );
				pT_loose_profile->push_back( mu_pt->at(ai)*MeV2TeV );
			}
			else if(sname=="pT_loose_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_pt->at(bi)*MeV2TeV );
				pT_loose_profile->push_back( mu_pt->at(bi)*MeV2TeV );
			}
			else if(sname=="pT_qOp+theta_1")
			{
				float tmp = pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai));
				(*h1map_cutProfile)[sname]->Fill( tmp );
				pT_qOp_and_theta_profile->push_back( tmp );
			}
			else if(sname=="pT_qOp+theta_2")
			{
				float tmp = pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi));
				(*h1map_cutProfile)[sname]->Fill( tmp );
				pT_qOp_and_theta_profile->push_back( tmp );
			}
			else if(sname=="pT_qOp+theta_loose_1")
			{
				float tmp = pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai));
				(*h1map_cutProfile)[sname]->Fill( tmp );
				pT_qOp_and_theta_loose_profile->push_back( tmp );
			}
			else if(sname=="pT_qOp+theta_loose_2")
			{
				float tmp = pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi));
				(*h1map_cutProfile)[sname]->Fill( tmp );
				pT_qOp_and_theta_loose_profile->push_back( tmp );
			}
			else if(sname=="eta_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
				eta_profile->push_back( mu_eta->at(ai) );
			}
			else if(sname=="eta_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
				eta_profile->push_back( mu_eta->at(bi) );
			}
			else if(sname=="etaTight_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
				etaTight_profile->push_back( mu_eta->at(ai) );
			}
			else if(sname=="etaTight_2") 
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
				etaTight_profile->push_back( mu_eta->at(bi) );
			}
			else if(sname=="etaBarrel_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
				etaBarrel_profile->push_back( mu_eta->at(ai) );
			}
			else if(sname=="etaBarrel_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
				etaBarrel_profile->push_back( mu_eta->at(bi) );
			}
			else if(sname=="etaFwd_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
				etaFwd_profile->push_back( mu_eta->at(ai) );
			}
			else if(sname=="etaFwd_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
				etaFwd_profile->push_back( mu_eta->at(bi) );
			}
			else if(sname=="etaFull_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
				etaFull_profile->push_back( mu_eta->at(ai) );
			}
			else if(sname=="etaFull_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
				etaFull_profile->push_back( mu_eta->at(bi) );
			}
			else if(sname=="pTmatchingRatio_1")
			{
				float pTid = pT(mu_id_qoverp->at(ai), mu_id_theta->at(ai));
				float pTme = pT(mu_me_qoverp->at(ai), mu_me_theta->at(ai));
				if(pTid!=0.) (*h1map_cutProfile)[sname]->Fill( pTme / pTid );
				if(pTid!=0.) pTmatchingRatio_profile->push_back( pTme / pTid );
			}
			else if(sname=="pTmatchingRatio_2")
			{
				float pTid = pT(mu_id_qoverp->at(bi), mu_id_theta->at(bi));
				float pTme = pT(mu_me_qoverp->at(bi), mu_me_theta->at(bi));
				if(pTid!=0.) (*h1map_cutProfile)[sname]->Fill( pTme / pTid );
				if(pTid!=0.) pTmatchingRatio_profile->push_back( pTme / pTid );
			}
			else if(sname=="pTmatchingAbsDiff_1")
			{
				float pTid = pT(mu_id_qoverp->at(ai), mu_id_theta->at(ai));
				float pTme = pT(mu_me_qoverp->at(ai), mu_me_theta->at(ai));
				(*h1map_cutProfile)[sname]->Fill( pTme - pTid );
				pTmatchingAbsDiff_profile->push_back( pTme - pTid );
			}
			else if(sname=="pTmatchingAbsDiff_2")
			{
				float pTid = pT(mu_id_qoverp->at(bi), mu_id_theta->at(bi));
				float pTme = pT(mu_me_qoverp->at(bi), mu_me_theta->at(bi));
				(*h1map_cutProfile)[sname]->Fill( pTme - pTid );
				pTmatchingAbsDiff_profile->push_back( pTme - pTid );
			}
			else if(sname=="d0_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_d0_exPV->at(ai) );
				d0_profile->push_back( mu_d0_exPV->at(ai) );
			}
			else if(sname=="d0_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_d0_exPV->at(bi) );
				d0_profile->push_back( mu_d0_exPV->at(bi) );
			}
			else if(sname=="z0_1")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_z0_exPV->at(ai) );
				z0_profile->push_back( mu_z0_exPV->at(ai) );
			}
			else if(sname=="z0_2")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_z0_exPV->at(bi) );
				z0_profile->push_back( mu_z0_exPV->at(bi) );
			}
			else if(sname=="isolation20_1")
			{
				//float iso = mu_ptcone20->at(ai)/pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai));
				float iso = mu_ptcone20->at(ai)/mu_pt->at(ai);
				(*h1map_cutProfile)[sname]->Fill( iso );
				isolation20_profile->push_back( iso );
			}
			else if(sname=="isolation20_2")
			{
				//float iso = mu_ptcone20->at(bi)/pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi));
				float iso = mu_ptcone20->at(bi)/mu_pt->at(bi);
				(*h1map_cutProfile)[sname]->Fill( iso );
				isolation20_profile->push_back( iso );
			}
			else if(sname=="isolation30_1")
			{
				//float iso = mu_ptcone30->at(ai)/pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai));
				float iso = mu_ptcone30->at(ai)/mu_pt->at(ai);
				(*h1map_cutProfile)[sname]->Fill( iso );
				isolation30_profile->push_back( iso );
			}
			else if(sname=="isolation30_2")
			{
				//float iso = mu_ptcone30->at(ai)/pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi));
				float iso = mu_ptcone30->at(bi)/mu_pt->at(bi);
				(*h1map_cutProfile)[sname]->Fill( iso );
				isolation30_profile->push_back( iso );
			}
			else if(sname=="isolation40_1")
			{
				//float iso = mu_ptcone40->at(ai)/pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai));
				float iso = mu_ptcone40->at(ai)/mu_pt->at(ai);
				(*h1map_cutProfile)[sname]->Fill( iso );
				isolation40_profile->push_back( iso );
			}
			else if(sname=="isolation40_2")
			{
				//float iso = mu_ptcone40->at(bi)/pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi));
				float iso = mu_ptcone40->at(bi)/mu_pt->at(bi);
				(*h1map_cutProfile)[sname]->Fill( iso );
				isolation40_profile->push_back( iso );
			}
			
			else if(sname=="msHitsRel16")
			{
				(*h1map_cutProfile)["nMDTBI_1"]->Fill( mu_nMDTBIHits->at(ai) );
				nMDTBI_profile->push_back( mu_nMDTBIHits->at(ai) );
				(*h1map_cutProfile)["nMDTBM_1"]->Fill( mu_nMDTBMHits->at(ai) );
				nMDTBM_profile->push_back( mu_nMDTBMHits->at(ai) );
				(*h1map_cutProfile)["nMDTBO_1"]->Fill( mu_nMDTBOHits->at(ai) );
				nMDTBO_profile->push_back( mu_nMDTBOHits->at(ai) );
				(*h1map_cutProfile)["nMDTBI_2"]->Fill( mu_nMDTBIHits->at(bi) );
				nMDTBI_profile->push_back( mu_nMDTBIHits->at(bi) );
				(*h1map_cutProfile)["nMDTBM_2"]->Fill( mu_nMDTBMHits->at(bi) );
				nMDTBM_profile->push_back( mu_nMDTBMHits->at(bi) );
				(*h1map_cutProfile)["nMDTBO_2"]->Fill( mu_nMDTBOHits->at(bi) );
				nMDTBO_profile->push_back( mu_nMDTBOHits->at(bi) );
				(*h1map_cutProfile)["nMDTEI_1"]->Fill( mu_nMDTEIHits->at(ai) );
				nMDTEI_profile->push_back( mu_nMDTEIHits->at(ai) );
				(*h1map_cutProfile)["nMDTEM_1"]->Fill( mu_nMDTEMHits->at(ai) );
				nMDTEM_profile->push_back( mu_nMDTEMHits->at(ai) );
				(*h1map_cutProfile)["nMDTEO_1"]->Fill( mu_nMDTEOHits->at(ai) );
				nMDTEO_profile->push_back( mu_nMDTEOHits->at(ai) );
				(*h1map_cutProfile)["nMDTEI_2"]->Fill( mu_nMDTEIHits->at(bi) );
				nMDTEI_profile->push_back( mu_nMDTEIHits->at(bi) );
				(*h1map_cutProfile)["nMDTEM_2"]->Fill( mu_nMDTEMHits->at(bi) );
				nMDTEM_profile->push_back( mu_nMDTEMHits->at(bi) );
				(*h1map_cutProfile)["nMDTEO_2"]->Fill( mu_nMDTEOHits->at(bi) );
				nMDTEO_profile->push_back( mu_nMDTEOHits->at(bi) );
				(*h1map_cutProfile)["nMDTBEE_1"]->Fill( mu_nMDTBEEHits->at(ai) );
				nMDTBEE_profile->push_back( mu_nMDTBEEHits->at(ai) );
				(*h1map_cutProfile)["nMDTBEE_2"]->Fill( mu_nMDTBEEHits->at(bi) );
				nMDTBEE_profile->push_back( mu_nMDTBEEHits->at(bi) );
				(*h1map_cutProfile)["nMDTEE_1"]->Fill( mu_nMDTEEHits->at(ai) );
				nMDTEE_profile->push_back( mu_nMDTEEHits->at(ai) );
				(*h1map_cutProfile)["nMDTEE_2"]->Fill( mu_nMDTEEHits->at(bi) );
				nMDTEE_profile->push_back( mu_nMDTEEHits->at(bi) );
				(*h1map_cutProfile)["nMDTBIS78_1"]->Fill( mu_nMDTBIS78Hits->at(ai) );
				nMDTBIS78_profile->push_back( mu_nMDTBIS78Hits->at(ai) );
				(*h1map_cutProfile)["nMDTBIS78_2"]->Fill( mu_nMDTBIS78Hits->at(bi) );
				nMDTBIS78_profile->push_back( mu_nMDTBIS78Hits->at(bi) );
				(*h1map_cutProfile)["nRPCPhi1_1"]->Fill( mu_nRPCLayer1PhiHits->at(ai) );
				nRPCPhi1_profile->push_back( mu_nRPCLayer1PhiHits->at(ai) );
				(*h1map_cutProfile)["nRPCPhi2_1"]->Fill( mu_nRPCLayer2PhiHits->at(ai) );
				nRPCPhi2_profile->push_back( mu_nRPCLayer2PhiHits->at(ai) );
				(*h1map_cutProfile)["nRPCPhi3_1"]->Fill( mu_nRPCLayer3PhiHits->at(ai) );
				nRPCPhi3_profile->push_back( mu_nRPCLayer3PhiHits->at(ai) );
				(*h1map_cutProfile)["nRPCPhi1_2"]->Fill( mu_nRPCLayer1PhiHits->at(bi) );
				nRPCPhi1_profile->push_back( mu_nRPCLayer1PhiHits->at(bi) );
				(*h1map_cutProfile)["nRPCPhi2_2"]->Fill( mu_nRPCLayer2PhiHits->at(bi) );
				nRPCPhi2_profile->push_back( mu_nRPCLayer2PhiHits->at(bi) );
				(*h1map_cutProfile)["nRPCPhi3_2"]->Fill( mu_nRPCLayer3PhiHits->at(bi) );
				nRPCPhi3_profile->push_back( mu_nRPCLayer3PhiHits->at(bi) );
				(*h1map_cutProfile)["nTGCPhi1_1"]->Fill( mu_nTGCLayer1PhiHits->at(ai) );
				nTGCPhi1_profile->push_back( mu_nTGCLayer1PhiHits->at(ai) );
				(*h1map_cutProfile)["nTGCPhi2_1"]->Fill( mu_nTGCLayer2PhiHits->at(ai) );
				nTGCPhi2_profile->push_back( mu_nTGCLayer2PhiHits->at(ai) );
				(*h1map_cutProfile)["nTGCPhi3_1"]->Fill( mu_nTGCLayer3PhiHits->at(ai) );
				nTGCPhi3_profile->push_back( mu_nTGCLayer3PhiHits->at(ai) );
				(*h1map_cutProfile)["nTGCPhi4_1"]->Fill( mu_nTGCLayer4PhiHits->at(ai) );
				nTGCPhi4_profile->push_back( mu_nTGCLayer4PhiHits->at(ai) );
				(*h1map_cutProfile)["nTGCPhi1_2"]->Fill( mu_nTGCLayer1PhiHits->at(bi) );
				nTGCPhi1_profile->push_back( mu_nTGCLayer1PhiHits->at(bi) );
				(*h1map_cutProfile)["nTGCPhi2_2"]->Fill( mu_nTGCLayer2PhiHits->at(bi) );
				nTGCPhi2_profile->push_back( mu_nTGCLayer2PhiHits->at(bi) );
				(*h1map_cutProfile)["nTGCPhi3_2"]->Fill( mu_nTGCLayer3PhiHits->at(bi) );
				nTGCPhi3_profile->push_back( mu_nTGCLayer3PhiHits->at(bi) );
				(*h1map_cutProfile)["nTGCPhi4_2"]->Fill( mu_nTGCLayer4PhiHits->at(bi) );
				nTGCPhi4_profile->push_back( mu_nTGCLayer4PhiHits->at(bi) );
				(*h1map_cutProfile)["nCSCEta_1"]->Fill( mu_nCSCEtaHits->at(ai) );
				nCSCEta_profile->push_back( mu_nCSCEtaHits->at(ai) );
				(*h1map_cutProfile)["nCSCEta_2"]->Fill( mu_nCSCEtaHits->at(bi) );
				nCSCEta_profile->push_back( mu_nCSCEtaHits->at(bi) );
				(*h1map_cutProfile)["nCSCPhi_1"]->Fill( mu_nCSCPhiHits->at(ai) );
				nCSCPhi_profile->push_back( mu_nCSCPhiHits->at(ai) );
				(*h1map_cutProfile)["nCSCPhi_2"]->Fill( mu_nCSCPhiHits->at(bi) );
				nCSCPhi_profile->push_back( mu_nCSCPhiHits->at(bi) );
			}
			
			else if(sname=="idHitsRel16")
			{
				(*h1map_cutProfile)["expectBLayerHit_1"]->Fill( mu_expectBLayerHit->at(ai) );
				expectBLayerHit_profile->push_back( mu_expectBLayerHit->at(ai) );
				(*h1map_cutProfile)["expectBLayerHit_2"]->Fill( mu_expectBLayerHit->at(bi) );
				expectBLayerHit_profile->push_back( mu_expectBLayerHit->at(bi) );
				(*h1map_cutProfile)["nBLHits_1"]->Fill( mu_nBLHits->at(ai) );
				nBLHits_profile->push_back( mu_nBLHits->at(ai) );
				(*h1map_cutProfile)["nBLHits_2"]->Fill( mu_nBLHits->at(bi) );
				nBLHits_profile->push_back( mu_nBLHits->at(bi) );
				(*h1map_cutProfile)["nPixHits_1"]->Fill( mu_nPixHits->at(ai) );
				nPixHits_profile->push_back( mu_nPixHits->at(ai) );
				(*h1map_cutProfile)["nPixHits_2"]->Fill( mu_nPixHits->at(bi) );
				nPixHits_profile->push_back( mu_nPixHits->at(bi) );
				(*h1map_cutProfile)["nPixelDeadSensors_1"]->Fill( mu_nPixelDeadSensors->at(ai) );
				nPixelDeadSensors_profile->push_back( mu_nPixelDeadSensors->at(ai) );
				(*h1map_cutProfile)["nPixelDeadSensors_2"]->Fill( mu_nPixelDeadSensors->at(bi) );
				nPixelDeadSensors_profile->push_back( mu_nPixelDeadSensors->at(bi) );
				(*h1map_cutProfile)["nPixHoles_1"]->Fill( mu_nPixHoles->at(ai) );
				nPixHoles_profile->push_back( mu_nPixHoles->at(ai) );
				(*h1map_cutProfile)["nPixHoles_2"]->Fill( mu_nPixHoles->at(bi) );
				nPixHoles_profile->push_back( mu_nPixHoles->at(bi) );
				(*h1map_cutProfile)["nSCTHits_1"]->Fill( mu_nSCTHits->at(ai) );
				nSCTHits_profile->push_back( mu_nSCTHits->at(ai) );
				(*h1map_cutProfile)["nSCTHits_2"]->Fill( mu_nSCTHits->at(bi) );
				nSCTHits_profile->push_back( mu_nSCTHits->at(bi) );
				(*h1map_cutProfile)["nSCTDeadSensors_1"]->Fill( mu_nSCTDeadSensors->at(ai) );
				nSCTDeadSensors_profile->push_back( mu_nSCTDeadSensors->at(ai) );
				(*h1map_cutProfile)["nSCTDeadSensors_2"]->Fill( mu_nSCTDeadSensors->at(bi) );
				nSCTDeadSensors_profile->push_back( mu_nSCTDeadSensors->at(bi) );
				(*h1map_cutProfile)["nSCTHoles_1"]->Fill( mu_nSCTHoles->at(ai) );
				nSCTHoles_profile->push_back( mu_nSCTHoles->at(ai) );
				(*h1map_cutProfile)["nSCTHoles_2"]->Fill( mu_nSCTHoles->at(bi) );
				nSCTHoles_profile->push_back( mu_nSCTHoles->at(bi) );
				(*h1map_cutProfile)["nTRTHits_1"]->Fill( mu_nTRTHits->at(ai) );
				nTRTHits_profile->push_back( mu_nTRTHits->at(ai) );
				(*h1map_cutProfile)["nTRTHits_2"]->Fill( mu_nTRTHits->at(bi) );
				nTRTHits_profile->push_back( mu_nTRTHits->at(bi) );
				(*h1map_cutProfile)["nTRTOutliers_1"]->Fill( mu_nTRTOutliers->at(ai) );
				nTRTOutliers_profile->push_back( mu_nTRTOutliers->at(ai) );
				(*h1map_cutProfile)["nTRTOutliers_2"]->Fill( mu_nTRTOutliers->at(bi) );
				nTRTOutliers_profile->push_back( mu_nTRTOutliers->at(bi) );
				
				eta_forTRThits_profile->push_back( mu_eta->at(ai) );
				eta_forTRThits_profile->push_back( mu_eta->at(bi) );
			}
			
			//-------------------------------------
			// cuts on the 2-muon system
			else if(sname=="oppositeCharge")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_charge->at(ai)*mu_charge->at(bi) );
				oppositeCharge_profile->push_back( mu_charge->at(ai)*mu_charge->at(bi) );
			}
			else if(sname=="imass")
			{
				float tmp = imass(pmu[ai],pmu[bi]);
				(*h1map_cutProfile)[sname]->Fill( tmp );
				imass_profile->push_back( tmp );
			}
			else if(sname=="cosThetaDimu")
			{
				float tmp = cosThetaDimu(pmu[ai],pmu[bi]);
				(*h1map_cutProfile)[sname]->Fill( tmp );
				cosThetaDimu_profile->push_back( tmp );
			}
			else if(sname=="etaSum")
			{
				(*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai)+mu_eta->at(bi) );
				etaSum_profile->push_back( mu_eta->at(ai)+mu_eta->at(bi) );
			}
		}
	}
}

void analysisSkeleton::fillCutProfile2D()
{
	bool pass;
	for(TMapSP2TH2D::iterator it=h2map_cutProfile->begin() ; it!=h2map_cutProfile->end() ; it++)
	{
		string sname = it->first;
		
		string snameNoSuffix = "";
		string suffix = sname.substr(sname.length()-2,sname.length()-1);
		if(suffix=="_1"  ||  suffix=="_2") snameNoSuffix = sname.substr(0,sname.length()-2);
		
		// do the id hits cut only once...
		if(snameNoSuffix=="nTRTHitsVSeta")
		{
			snameNoSuffix = "idHitsRel16";
			sname         = snameNoSuffix;
		}
		else if(snameNoSuffix=="nTRTOutliersVSeta") continue;
		
		pass = true;
		pass = (pass && preselection(snameNoSuffix))    ? true : false;
		pass = (pass && singleSelection(snameNoSuffix)) ? true : false;
		pass = (pass && doubleSelection(snameNoSuffix)) ? true : false;
		
		if(pass)
		{
			if(sname=="PV")
			{
				float cutval = (*m_cutFlowMapSVD)[sname][1]; // vxp_type==1 (the second cutVal)
				for(int v=0 ; (v<(int)vxp_type->size() && vxp_type->at(v)==cutval) ; v++)
				{
					(*h2map_cutProfile)[sname]->Fill( vxp_z->at(v),vxp_nTracks->at(v) );
					vxp_z_profile->push_back( vxp_z->at(v) );
					vxp_nTracks_profile->push_back( vxp_nTracks->at(v) );
				}
			}
			else if(sname=="pTandEta_1")
			{
				float tmp = mu_pt->at(ai)*MeV2TeV;//pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai));
				(*h2map_cutProfile)[sname]->Fill( tmp, mu_eta->at(ai) );
				pT_profile->push_back( tmp ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				eta_profile->push_back( mu_eta->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="pTandEta_2")
			{
				float tmp = mu_pt->at(bi)*MeV2TeV;//pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi));
				(*h2map_cutProfile)[sname]->Fill( tmp, mu_eta->at(bi) );
				pT_profile->push_back( tmp ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				eta_profile->push_back( mu_eta->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="pTandEtaTight_1")
			{
				float tmp = mu_pt->at(ai)*MeV2TeV;//pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai));
				(*h2map_cutProfile)[sname]->Fill( tmp, mu_eta->at(ai) );
				pT_profile->push_back( tmp ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				etaTight_profile->push_back( mu_eta->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="pTandEtaTight_2") 
			{
				float tmp = mu_pt->at(bi)*MeV2TeV;//pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi));
				(*h2map_cutProfile)[sname]->Fill( tmp, mu_eta->at(bi) );
				pT_profile->push_back( tmp ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				etaTight_profile->push_back( mu_eta->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="pTandEtaBarrel_1")
			{
				float tmp = mu_pt->at(ai)*MeV2TeV;//pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai));
				(*h2map_cutProfile)[sname]->Fill( tmp, mu_eta->at(ai) );
				pT_profile->push_back( tmp ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				etaBarrel_profile->push_back( mu_eta->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="pTandEtaBarrel_2")
			{
				float tmp = mu_pt->at(bi)*MeV2TeV;//pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi));
				(*h2map_cutProfile)[sname]->Fill( tmp, mu_eta->at(bi) );
				pT_profile->push_back( tmp ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				etaBarrel_profile->push_back( mu_eta->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="idHits_1")
			{
				(*h2map_cutProfile)[sname]->Fill( mu_nSCTHits->at(ai), mu_nPixHits->at(ai) );
				nSCTHits_profile->push_back( mu_nSCTHits->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				nPixHits_profile->push_back( mu_nPixHits->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="idHits_2")
			{
				(*h2map_cutProfile)[sname]->Fill( mu_nSCTHits->at(bi), mu_nPixHits->at(bi) );
				nSCTHits_profile->push_back( mu_nSCTHits->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				nPixHits_profile->push_back( mu_nPixHits->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="idHitsRel16")
			{
				(*h2map_cutProfile)["nTRTHitsVSeta_1"]->Fill( mu_eta->at(ai), mu_nTRTHits->at(ai) );
				(*h2map_cutProfile)["nTRTHitsVSeta_2"]->Fill( mu_eta->at(bi), mu_nTRTHits->at(bi) );
				(*h2map_cutProfile)["nTRTOutliersVSeta_1"]->Fill( mu_eta->at(ai), mu_nTRTOutliers->at(ai) );
				(*h2map_cutProfile)["nTRTOutliersVSeta_2"]->Fill( mu_eta->at(bi), mu_nTRTOutliers->at(bi) );
			}
			else if(sname=="impactParameter_1")
			{
				(*h2map_cutProfile)[sname]->Fill( mu_d0_exPV->at(ai), mu_z0_exPV->at(ai) );
				ip_d0_profile->push_back( mu_d0_exPV->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				ip_z0_profile->push_back( mu_z0_exPV->at(ai) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if(sname=="impactParameter_2")
			{
				(*h2map_cutProfile)[sname]->Fill( mu_d0_exPV->at(bi), mu_z0_exPV->at(bi) );
				ip_d0_profile->push_back( mu_d0_exPV->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				ip_z0_profile->push_back( mu_z0_exPV->at(bi) ); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}
}

void analysisSkeleton::fillCutProfile()
{
	fillCutProfile1D();
	
	fillCutProfile2D();
	
	/////////////////////////////////////////////////////////
	// fill the cut profile tree ////////////////////////////
	tree_cutsProfile->Fill(); ///////////////////////////////
	if(m_cutsProfile_counter%m_trees_counter_mod==0) ////////
	{                                ////////////////////////
		tree_cutsProfile->FlushBaskets(); ///////////////////
		//tree_cutsProfile->Write("", TObject::kOverwrite); ///
	} ///////////////////////////////////////////////////////
	m_cutsProfile_counter++; ////////////////////////////////
	/////////////////////////////////////////////////////////
}

void analysisSkeleton::fill_tNp()
{
	int mask = -1;
	string sTrigType = "";
	bool isLLT = false;
	bool isHLT = false;
	bool isCBpT = true;
	
	//////////////////////////////////////////////////////////////////////////////////
	float trig_pTmin       = (float)m_period2pTminMap->operator[](sPeriod); //////////
	float trig_pTthreshold = (float)m_period2pTthresholdMap->operator[](sPeriod); ////
	string sTrigPeriod     = (*m_period2triggerperiodMap)[sPeriod]; //////////////////
	//////////////////////////////////////////////////////////////////////////////////
	if( (size_t)sTrigPeriod.find("L1")!=string::npos )      sTrigType = "L1"; ////////
	else if( (size_t)sTrigPeriod.find("MG")!=string::npos ) sTrigType = "MG"; ////////
	else if( (size_t)sTrigPeriod.find("MS")!=string::npos ) sTrigType = "MS"; ////////
	else                                                    sTrigType = "CB"; ////////
	//////////////////////////////////////////////////////////////////////////////////
	if     ( (size_t)sTrigPeriod.find("L1")!=string::npos ) isLLT = true; ////////////
	else if( (size_t)sTrigPeriod.find("EF")!=string::npos ) isHLT = true; ////////////
	//////////////////////////////////////////////////////////////////////////////////
	if     (sTrigType=="L1" || sTrigType=="MS") isCBpT = false; //////////////////////
	else if(sTrigType=="MG" || sTrigType=="CB") isCBpT = true;  //////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	matchTrigger(sPeriod, sTrigType); ////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	
	float pTtmp;
	int previousTag;
	int muTag = -1;
	int ROITag;
	int trigTrkTag;
	int muProb;
	int ROIProb;
	int trigTrkProb;
	
	// tag&probe with respect to EFCB
	for(int mu=0 ; mu<(int)mu_pt->size() ; mu++)
	{
		previousTag = muTag;
	
		if(isHLT)
		{
			mask = tagMask
			(
				sTrigPeriod, sTrigType, trig_pTthreshold,
				muQAflags,
				previousTag,
				muTag, ROITag, trigTrkTag,
				mu_HLT_index, mu_HLT_dr,
				mu_phi, mu_eta, mu_pt, mu_me_qoverp, mu_me_theta,
				HLT_phi, HLT_eta, HLT_pt, HLT_has
			);
		}
		else if(isLLT)
		{
			mask = tagMask
			(
				sTrigPeriod, sTrigType, trig_pTthreshold,
				muQAflags,
				previousTag,
				muTag, ROITag,
				mu_LLT_index, mu_LLT_dr,
				mu_phi, mu_eta, mu_pt, mu_me_qoverp, mu_me_theta,
				LLT_phi, LLT_eta, LLT_pt
			);
		}
		if(mask!=12) continue;
		
		mask = probeCandMask
		(
			sTrigType,
			pmu, muQAflags,
			muTag,
			mu_phi, mu_eta, mu_pt, mu_me_qoverp, mu_me_theta, mu_d0_exPV, mu_z0_exPV, mu_charge
		);
		if(mask!=5) continue;
		
		for(int probs=0 ; probs<(int)m_viProbes.size() ; probs++)
		{
			int iprobeCand = m_viProbes[probs];
			if(!isCBpT) pTtmp = fabs(pT(mu_me_qoverp->at(iprobeCand)/MeV2TeV, mu_me_theta->at(iprobeCand)));
			else        pTtmp = mu_pt->at(iprobeCand)*MeV2TeV;
			
			if(isHLT)
			{
				mask = probeMask
				(
					iprobeCand,
					sTrigPeriod, trig_pTthreshold,
					muQAflags,
					muTag, ROITag, trigTrkTag,
					muProb, ROIProb, trigTrkProb,
					mu_HLT_index, mu_HLT_dr,
					mu_phi, mu_eta,
					HLT_phi, HLT_eta, HLT_pt, HLT_has
				);
			}
			else if(isLLT)
			{
				mask = probeMask
				(
					iprobeCand,
					sTrigPeriod, trig_pTthreshold,
					muQAflags,
					muTag, ROITag,
					muProb, ROIProb,
					mu_LLT_index, mu_LLT_dr,
					mu_phi, mu_eta,
					LLT_phi, LLT_eta, LLT_pt
				);
			}
			if(mask!=12) // cannot probe the candidate, fill the denominator histos
			{
				(*h1map_tagNprobe_candidates_pT)[sTrigPeriod]->Fill( pTtmp );
				(*h1map_tagNprobe_candidates_eta)[sTrigPeriod]->Fill( mu_eta->at(iprobeCand) );
				(*h1map_tagNprobe_candidates_phi)[sTrigPeriod]->Fill( mu_phi->at(iprobeCand) );
				tNp_triggerName->push_back(sTrigPeriod);
				tNp_cand_pT->push_back( pTtmp );
				tNp_cand_eta->push_back( mu_eta->at(iprobeCand) );
				tNp_cand_phi->push_back( mu_phi->at(iprobeCand) );
				continue;
			}
			
			// mask=12 ==> fill both the denominator and the numerator histograms
			(*h1map_tagNprobe_candidates_pT)[sTrigPeriod]->Fill( pTtmp );
			(*h1map_tagNprobe_candidates_eta)[sTrigPeriod]->Fill( mu_eta->at(iprobeCand) );
			(*h1map_tagNprobe_candidates_phi)[sTrigPeriod]->Fill( mu_phi->at(iprobeCand) );
			(*h1map_tagNprobe_succeeded_pT)[sTrigPeriod]->Fill( pTtmp );
			(*h1map_tagNprobe_succeeded_eta)[sTrigPeriod]->Fill( mu_eta->at(iprobeCand) );
			(*h1map_tagNprobe_succeeded_phi)[sTrigPeriod]->Fill( mu_phi->at(iprobeCand) );
			tNp_triggerName->push_back(sTrigPeriod);
			tNp_cand_pT->push_back( pTtmp );
			tNp_cand_eta->push_back( mu_eta->at(iprobeCand) );
			tNp_cand_phi->push_back( mu_phi->at(iprobeCand) );
			tNp_succ_pT->push_back( pTtmp );
			tNp_succ_eta->push_back( mu_eta->at(iprobeCand) );
			tNp_succ_phi->push_back( mu_phi->at(iprobeCand) );
		}
	}
}

void analysisSkeleton::fillTruthEfficiency()
{
	//mu_truth_matched    : True if muon is matched to the truth
	//mu_truth_status     : Status oMC status = 1 final particle, status = 3 intermediate particle (documentary)
	//mu_truth_mothertype : description: True mother PDG type
	
	if(mu_truth_pt==0)         return;
	if(mu_truth_status==0)     return;
	if(mu_truth_mothertype==0) return;
	if(mu_me_qoverp==0)        return;
	if(mu_me_theta==0)         return;
	
	//////////////////////////////////////////////////////////////////////////////////
	float trig_pTmin       = (float)m_period2pTminMap->operator[](sPeriod); //////////
	float trig_pTthreshold = (float)m_period2pTthresholdMap->operator[](sPeriod); ////
	string sTrigPeriod     = (*m_period2triggerperiodMap)[sPeriod]; //////////////////
	string sTrigType = "L1"; /////////////////////////////////////////////////////////
	matchTrigger(sPeriod, sTrigType); ////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////
	if(mu_truth_pt->size()!=2) return; ///
	//////////////////////////////////////
	
	float pTreconstructed = 0.;
	for(int t=0 ; t<(int)mu_truth_pt->size() ; t++)
	{
		//if(sTrigType!="CB") pTreconstructed = fabs(pT(mu_me_qoverp->at(t), mu_me_theta->at(t))*MeV2GeV); ??????????????????????
		//else                pTreconstructed = mu_pt->at(t)*MeV2GeV; // ????????????????????????????????????????????????????????
		pTreconstructed = fabs(pT(mu_me_qoverp->at(t), mu_me_theta->at(t))*MeV2GeV); // L1 doesn't do CB measurement ????????????
	
		if(!mu_truth_status->at(t))          continue; // has to be final particle
		if(mu_truth_mothertype->at(t)!=PDTZ) continue; // has to come out of Z^0
		if(pTreconstructed<=trig_pTmin)      continue; // has to be above pT min
	
		// fill the probe candidate histos
		(*h1map_truth_candidates_pT)[sTrigPeriod]->Fill( pTreconstructed*GeV2TeV );
		(*h1map_truth_candidates_eta)[sTrigPeriod]->Fill( mu_eta->at(t) );
		(*h1map_truth_candidates_phi)[sTrigPeriod]->Fill( mu_phi->at(t) );
		tru_triggerName->push_back( sTrigPeriod );
		tru_cand_pT->push_back( pTreconstructed*GeV2TeV );
		tru_cand_eta->push_back( mu_eta->at(t) );
		tru_cand_phi->push_back( mu_phi->at(t) );
		
		// for monte carlo, use L1_MU10
		float dr = mu_LLT_dr->at(t);
		int iROI = mu_LLT_index->at(t); 
		if(dr<0.)          continue;
		if(dr>dRmax_mu_L1) continue;
		if(iROI<0)         continue;
	
		float dphi = LLT_phi->at(iROI) - mu_phi->at(t);
		float deta = LLT_eta->at(iROI) - mu_eta->at(t);
		dr = sqrt(dphi*dphi + deta*deta);
		if(dr>dRmax_mu_L1) continue;
		
		float pTprobTrig = LLT_pt->at(iROI)*MeV2GeV;
		float pTtrigThreshold = 10.; // in GeV
		if(pTprobTrig<pTtrigThreshold) continue;
		
		// fill the probe histos
		(*h1map_truth_succeeded_pT)[sTrigPeriod]->Fill( pTreconstructed*GeV2TeV );
		(*h1map_truth_succeeded_eta)[sTrigPeriod]->Fill( mu_eta->at(t) );
		(*h1map_truth_succeeded_phi)[sTrigPeriod]->Fill( mu_phi->at(t) );
		tru_succ_pT->push_back( pTreconstructed*GeV2TeV );
		tru_succ_eta->push_back( mu_eta->at(t) );
		tru_succ_phi->push_back( mu_phi->at(t) );
	}
}


void analysisSkeleton::fillTruth()
{
	//mu_truth_matched    : True if muon is matched to the truth
	//mu_truth_status     : Status oMC status = 1 final particle, status = 3 intermediate particle (documentary)
	//mu_truth_mothertype : description: True mother PDG type
	
	if(mu_truth_pt==0)         return;
	if(mu_truth_status==0)     return;
	if(mu_truth_mothertype==0) return;
	
	//////////////////////////////////////
	if(mu_truth_pt->size()<2) return;  ///
	//////////////////////////////////////
	
	int mu_tru_ai=-1, mu_tru_bi=-1;
	for(int t=0 ; t<(int)mu_truth_pt->size() ; t++)
	{	
		if(!mu_truth_status->at(t))                                                    continue; // has to be final particle
		if(mu_truth_mothertype->at(t)!=PDTZ  &&  mu_truth_mothertype->at(t)!=PDTGAMMA) continue; // has to come out of Z^0
		if(mu_tru_ai<0) mu_tru_ai = t;
		if(mu_tru_bi<0  &&  mu_tru_ai>=0  &&  mu_tru_ai!=t) mu_tru_bi = t;
		if(mu_tru_ai>=0  &&  mu_tru_bi>=0) break;
		/*
		truth_all_dr->push_back( mu_truth_dr->at(t) );
		truth_all_E->push_back( mu_truth_E->at(t) );
		truth_all_pt->push_back( mu_truth_pt->at(t) );
		truth_all_eta->push_back( mu_truth_eta->at(t) );
		truth_all_phi->push_back( mu_truth_phi->at(t) );
		truth_all_type->push_back( mu_truth_type->at(t) );
		truth_all_status->push_back( mu_truth_status->at(t) );
		truth_all_barcode->push_back( mu_truth_barcode->at(t) );
		truth_all_mothertype->push_back( mu_truth_mothertype->at(t) );
		truth_all_motherbarcode->push_back( mu_truth_motherbarcode->at(t) );
		truth_all_matched->push_back( mu_truth_matched->at(t) );
		*/
	}
	
	if(mu_tru_ai>=0  &&  mu_tru_bi>=0)
	{
		truth_all_dr->push_back( mu_truth_dr->at(mu_tru_ai) );
		truth_all_dr->push_back( mu_truth_dr->at(mu_tru_bi) );
		truth_all_E->push_back( mu_truth_E->at(mu_tru_ai)*MeV2GeV );
		truth_all_E->push_back( mu_truth_E->at(mu_tru_bi)*MeV2GeV );
		truth_all_pt->push_back( mu_truth_pt->at(mu_tru_ai)*MeV2GeV );
		truth_all_pt->push_back( mu_truth_pt->at(mu_tru_bi)*MeV2GeV );
		truth_all_eta->push_back( mu_truth_eta->at(mu_tru_ai) );
		truth_all_eta->push_back( mu_truth_eta->at(mu_tru_bi) );
		truth_all_phi->push_back( mu_truth_phi->at(mu_tru_ai) );
		truth_all_phi->push_back( mu_truth_phi->at(mu_tru_bi) );
		truth_all_type->push_back( mu_truth_type->at(mu_tru_ai) );
		truth_all_type->push_back( mu_truth_type->at(mu_tru_bi) );
		truth_all_status->push_back( mu_truth_status->at(mu_tru_ai) );
		truth_all_status->push_back( mu_truth_status->at(mu_tru_bi) );
		truth_all_barcode->push_back( mu_truth_barcode->at(mu_tru_ai) );
		truth_all_barcode->push_back( mu_truth_barcode->at(mu_tru_bi) );
		truth_all_mothertype->push_back( mu_truth_mothertype->at(mu_tru_ai) );
		truth_all_mothertype->push_back( mu_truth_mothertype->at(mu_tru_bi) );
		truth_all_motherbarcode->push_back( mu_truth_motherbarcode->at(mu_tru_ai) );
		truth_all_motherbarcode->push_back( mu_truth_motherbarcode->at(mu_tru_bi) );
		truth_all_matched->push_back( mu_truth_matched->at(mu_tru_ai) );
		truth_all_matched->push_back( mu_truth_matched->at(mu_tru_bi) );
	
		float c1 = (mu_truth_type->at(mu_tru_ai)<0) ? -1. : +1.;
		float c2 = (mu_truth_type->at(mu_tru_bi)<0) ? -1. : +1.;
		
		truth_all_isValid = true;
		
		TLorentzVector* p1 = new TLorentzVector();
		TLorentzVector* p2 = new TLorentzVector();
		p1->SetPtEtaPhiE( mu_truth_pt->at(mu_tru_ai)*MeV2GeV, mu_truth_eta->at(mu_tru_ai), mu_truth_phi->at(mu_tru_ai), mu_truth_E->at(mu_tru_ai)*MeV2GeV);
		p2->SetPtEtaPhiE( mu_truth_pt->at(mu_tru_bi)*MeV2GeV, mu_truth_eta->at(mu_tru_bi), mu_truth_phi->at(mu_tru_bi), mu_truth_E->at(mu_tru_bi)*MeV2GeV);
		truth_all_Mhat       = imass(p1,p2);
		truth_all_CosThetaCS = cosThetaCollinsSoper(p1,c1, p2,c2);
		truth_all_CosThetaHE = cosThetaBoost(p1,c1, p2,c2);
		truth_all_ySystem    = ySystem(p1,p2);
		truth_all_QT         = QT(p1,p2);
		delete p1;
		delete p2;
	}
}

void analysisSkeleton::fillRecon(int a, int b)
{
	recon_all_E->push_back(mu_E->at(ai)*MeV2GeV);
	recon_all_E->push_back(mu_E->at(bi)*MeV2GeV);
	recon_all_pt->push_back(mu_pt->at(ai)*MeV2GeV);
	recon_all_pt->push_back(mu_pt->at(bi)*MeV2GeV);
	recon_all_m->push_back(mu_m->at(ai)*MeV2GeV);
	recon_all_m->push_back(mu_m->at(bi)*MeV2GeV);
	recon_all_eta->push_back(mu_eta->at(ai));
	recon_all_eta->push_back(mu_eta->at(bi));
	recon_all_phi->push_back(mu_phi->at(ai));
	recon_all_phi->push_back(mu_phi->at(bi));
	recon_all_px->push_back(mu_px->at(ai)*MeV2GeV);
	recon_all_px->push_back(mu_px->at(bi)*MeV2GeV);
	recon_all_py->push_back(mu_py->at(ai)*MeV2GeV);
	recon_all_py->push_back(mu_py->at(bi)*MeV2GeV);
	recon_all_pz->push_back(mu_pz->at(ai)*MeV2GeV);
	recon_all_pz->push_back(mu_pz->at(bi)*MeV2GeV);
	recon_all_charge->push_back(mu_charge->at(ai));
	recon_all_charge->push_back(mu_charge->at(bi));
	recon_all_y->push_back(y(pmu[ai]));
	recon_all_y->push_back(y(pmu[bi]));
	recon_all_id->push_back((mu_charge->at(ai)<0.) ? PDTMU : -1*PDTMU);
	recon_all_id->push_back((mu_charge->at(bi)<0.) ? PDTMU : -1*PDTMU);
	recon_all_theta->push_back( pmu[ai]->Theta() );
	recon_all_theta->push_back( pmu[bi]->Theta() );
	
	TLorentzVector* p1 = new TLorentzVector();
	TLorentzVector* p2 = new TLorentzVector();
	p1->SetPtEtaPhiE( mu_pt->at(ai)*MeV2GeV, mu_eta->at(ai), mu_phi->at(ai), mu_E->at(ai)*MeV2GeV);
	p2->SetPtEtaPhiE( mu_pt->at(bi)*MeV2GeV, mu_eta->at(bi), mu_phi->at(bi), mu_E->at(bi)*MeV2GeV);
	float c1 = mu_charge->at(ai);
	float c2 = mu_charge->at(bi);
	recon_all_Mhat = imass(p1,p2);
	recon_all_CosThetaCS = cosThetaCollinsSoper(p1,c1, p2,c2);
	recon_all_CosThetaHE = cosThetaBoost(p1,c1, p2,c2);
	recon_all_ySystem = ySystem(p1,p2);
	recon_all_QT = QT(p1,p2);
	delete p1;
	delete p2;
	
	recon_all_isValid = true;
}

void analysisSkeleton::applyTagNProbe(TMapsb& cutsToSkip, bool isMC)
{
	bool pass;
	
	pass = true;
	pass = (pass && preselection(cutsToSkip))    ? true : false;
	pass = (pass && singleSelection(cutsToSkip)) ? true : false;
	if(pass)
	{
		/////////////////////////
		// Tag&Probe mask ///////
		//fillTagNProbe(); ////////
		fill_tNp(); /////////////
		/////////////////////////
		
		/////////////////////////////////////////
		// Truth efficiency mask ////////////////
		if(isMC) fillTruthEfficiency(); /////////
		/////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// fill the efficiency tree ////////////////////////////
		tree_efficiency->Fill(); ///////////////////////////////
		if(m_efficiency_counter%m_trees_counter_mod==0) ////////
		{                               ////////////////////////
			tree_efficiency->FlushBaskets(); ///////////////////
			//tree_efficiency->Write("", TObject::kOverwrite); ///
		} //////////////////////////////////////////////////////
		m_efficiency_counter++; ////////////////////////////////
		////////////////////////////////////////////////////////
	}
}

void analysisSkeleton::applyTruth()
{
	///////////////////////////
	// fill all events ////////
	fillTruth(); //////////////
	///////////////////////////

	bool didItPass = true;
	// passing an empty string will deal with it as if there is a skipped cut
	// and therefore no fill will be done in the pre-/single-/double-selection calls:
	didItPass      = (didItPass && preselection("noFills"))    ? true : false;
	didItPass      = (didItPass && singleSelection("noFills")) ? true : false;
	didItPass      = (didItPass && doubleSelection("noFills")) ? true : false;
	
	/////////////////////////////////////////////
	// fill the recon vars only if passed ///////
	// but fill the tree anyway, also if ////////
	// these vars are empty so the matching /////
	// to truth will be easy ////////////////////
	if(didItPass) fillRecon(ai,bi); /////////////
	/////////////////////////////////////////////
	
	////////////////////////////////////////////////////////
	// fill the truth tree ////////////////////////////
	tree_truth->Fill(); ///////////////////////////////
	if(m_truth_counter%m_trees_counter_mod==0) ////////
	{                               ////////////////////////
		tree_truth->FlushBaskets(); ///////////////////
		//tree_truth->Write("", TObject::kOverwrite); ///
	} //////////////////////////////////////////////////////
	m_truth_counter++; ////////////////////////////////
	////////////////////////////////////////////////////////
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool analysisSkeleton::preselection(string sSkipCut)
{
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return preselection(cutsToSkip);
}

bool analysisSkeleton::singleSelection(string sSkipCut)
{
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return singleSelection(cutsToSkip);
}

bool analysisSkeleton::doubleSelection(string sSkipCut)
{
	TMapsb cutsToSkip;
	cutsToSkip.insert(make_pair(sSkipCut,true));
	return doubleSelection(cutsToSkip);
}

inline bool analysisSkeleton::preselection(TMapsb& cutsToSkip)
{
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;

	int nMus = (int)mu_pt->size();
	resetMuQAflags(nMus);
	
	passCutFlow    = true;
	passCurrentCut = true;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		///////////////////////////////////////////////////////////////////////////
		// ignore selection: //////////////////////////////////////////////////////
		float num = ii->first; ////////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="selection") continue; //////////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}

		if(sorderedcutname=="GRL"  &&  !bSkipCut)
		{
			passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], isGRL) ) ? true : false;
		}
		
		else if(sorderedcutname=="Trigger"  &&  !bSkipCut)
		{
			string trigName;
			int trigVal;
			bool pass1Trig = false;
			for(int t=0 ; t<(int)vTriggers->size() ; t++)
			{
				trigName  = vTriggers->at(t);
				trigVal   = isTrigger( trigName );
				pass1Trig = ( triggerCut((*m_cutFlowMapSVD)[sorderedcutname][0], trigVal, trigName) ) ? true : false;
				if(pass1Trig) break;
			}
			passCurrentCut = pass1Trig;
		}
		
		else if(sorderedcutname=="EF_mu13"  &&  !bSkipCut)
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], EF_mu13) ) ? true : false;
		}
		
		else if(sorderedcutname=="hipTmuon"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			passCurrentCut = ( findHipTmuon(cutval1, cutval2,
			(int)mu_pt->size(), mu_pt, mu_me_qoverp, mu_me_theta) ) ? true : false;
		}
		
		else if(sorderedcutname=="PV"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
			(int)vxp_type->size(), vxp_nTracks, vxp_type, vxp_z) ) ? true : false;
			iVtx = getPVindex();
		}
		
		else continue;
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		// cutFlow /////////////////////////////////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut  && bDoFill) fillCutFlow(sorderedcutname, "preselection"); ///////
		////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	
	return passCutFlow;
}

inline bool analysisSkeleton::singleSelection(TMapsb& cutsToSkip)
{
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;
	
	int muSize  = (int)mu_charge->size();

	passCutFlow = true;
	
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{	
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;
		nMusPassed = 0;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}
		
		
		if(sorderedcutname=="pT"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pT_loose"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pT_qOp+theta"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(mu), mu_me_theta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pT_qOp+theta_loose"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(mu), mu_me_theta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="eta"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaTight"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaTightCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaBarrel"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaBarrelCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaFwd"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaFull"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTandEta"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
				float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
				thisMuPass = ( pTandEtaCut(cutval1, cutval2,
				mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_eta->at(mu)) ) ? true : false;
				//thisMuPass = ( pTandEtaTightCut(cutval1, cutval2, mu_pt->at(mu), mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTandEtaTight"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
				float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
				thisMuPass = ( pTandEtaTightCut(cutval1, cutval2,
				mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_eta->at(mu)) ) ? true : false;
				//thisMuPass = ( pTandEtaTightCut(cutval1, cutval2, mu_pt->at(mu), mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTandEtaBarrel"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
				float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
				thisMuPass = (pTandEtaBarrelCut(cutval1,cutval2,mu_me_qoverp->at(mu),mu_me_theta->at(mu),mu_eta->at(mu))) ? true : false;
				//thisMuPass = ( pTandEtaBarrelCut(cutval1, cutval2, mu_pt->at(mu), mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="d0"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_d0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="z0"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_z0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="impactParameter"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( impactParameterCut(cutval1,cutval2, mu_d0_exPV->at(mu), mu_z0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="isCombMu"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_isCombinedMuon->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="idHits"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nIDhitsCut( cutval1,cutval2,cutval3, mu_nSCTHits->at(mu), mu_nPixHits->at(mu) ) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="idHitsMCPrel15"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nIDhitsMCPrel15Cut(cutval1,cutval2,cutval3,cutval4,cutval5,
												  mu_nSCTHits->at(mu),mu_nPixHits->at(mu),
												  mu_nTRTHits->at(mu),mu_nTRTOutliers->at(mu),
												  mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="idHitsRel16"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6 = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7 = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8 = (*m_cutFlowMapSVD)[sorderedcutname][7];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nIDhitsRel16Cut(cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,
											   mu_expectBLayerHit->at(mu),mu_nBLHits->at(mu),
											   mu_nPixHits->at(mu),mu_nPixelDeadSensors->at(mu),mu_nPixHoles->at(mu),
											   mu_nSCTHits->at(mu),mu_nSCTDeadSensors->at(mu),mu_nSCTHoles->at(mu),
											   mu_nTRTHits->at(mu),mu_nTRTOutliers->at(mu),
											   mu_eta->at(mu))) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="ms3stationsMDThits"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMS3stationsMDThits( cutval1,cutval2,cutval3,cutval4,cutval5,
				mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
				mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEOHits->at(mu),
				mu_nMDTBEEHits->at(mu), mu_nMDTBIS78Hits->at(mu))
				) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHits"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6 = (*m_cutFlowMapSVD)[sorderedcutname][5];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMShits( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,
				mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),mu_nMDTBIS78Hits->at(mu), mu_nMDTBEEHits->at(mu),
				mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu)
				)
				) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHits1"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6 = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7 = (*m_cutFlowMapSVD)[sorderedcutname][6];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMShits1( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,
										 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
										 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTEOHits->at(mu),
										 mu_nMDTBIS78Hits->at(mu), mu_nMDTBEEHits->at(mu),
										 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
										 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
										 mu_nCSCEtaHits->at(mu), mu_nCSCPhiHits->at(mu)
										)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHits2"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3  = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4  = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5  = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6  = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7  = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8  = (*m_cutFlowMapSVD)[sorderedcutname][7];
			float cutval9  = (*m_cutFlowMapSVD)[sorderedcutname][8];
			float cutval10 = (*m_cutFlowMapSVD)[sorderedcutname][9];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMShits2( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,cutval9,cutval10,
										 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
										 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTEOHits->at(mu),
										 mu_nMDTBIS78Hits->at(mu), mu_nMDTBEEHits->at(mu),
										 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
										 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
										 mu_nCSCEtaHits->at(mu), mu_nCSCPhiHits->at(mu)
										)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHits2noCSCphi"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3  = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4  = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5  = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6  = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7  = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8  = (*m_cutFlowMapSVD)[sorderedcutname][7];
			float cutval9  = (*m_cutFlowMapSVD)[sorderedcutname][8];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMShits2noCSCphi( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,cutval9,
										 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
										 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTEOHits->at(mu),
										 mu_nMDTBIS78Hits->at(mu), mu_nMDTBEEHits->at(mu),
										 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
										 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
										 mu_nCSCEtaHits->at(mu)
										)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHits3"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4 = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5 = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6 = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7 = (*m_cutFlowMapSVD)[sorderedcutname][6];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				// msHits3 has identical functionality to msHits1 but with different 6th parameter (nMDTCSCsumCutVal)
				thisMuPass = ( nMShits1( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,
										 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
										 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTEOHits->at(mu),
										 mu_nMDTBIS78Hits->at(mu), mu_nMDTBEEHits->at(mu),
										 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
										 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
										 mu_nCSCEtaHits->at(mu), mu_nCSCPhiHits->at(mu)
										)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHits4"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3  = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4  = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5  = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6  = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7  = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8  = (*m_cutFlowMapSVD)[sorderedcutname][7];
			float cutval9  = (*m_cutFlowMapSVD)[sorderedcutname][8];
			float cutval10 = (*m_cutFlowMapSVD)[sorderedcutname][9];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				// msHits4 has identical functionality to msHits2 but with different 5th parameter (nCSCEtaHitsCutVal)
				thisMuPass = ( nMShits2( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,cutval9,cutval10,
										 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
										 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTEOHits->at(mu),
										 mu_nMDTBIS78Hits->at(mu), mu_nMDTBEEHits->at(mu),
										 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
										 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
										 mu_nCSCEtaHits->at(mu), mu_nCSCPhiHits->at(mu)
										)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="msHitsRel16"  &&  !bSkipCut)
		{
			float cutval1  = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2  = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3  = (*m_cutFlowMapSVD)[sorderedcutname][2];
			float cutval4  = (*m_cutFlowMapSVD)[sorderedcutname][3];
			float cutval5  = (*m_cutFlowMapSVD)[sorderedcutname][4];
			float cutval6  = (*m_cutFlowMapSVD)[sorderedcutname][5];
			float cutval7  = (*m_cutFlowMapSVD)[sorderedcutname][6];
			float cutval8  = (*m_cutFlowMapSVD)[sorderedcutname][7];
			float cutval9 = (*m_cutFlowMapSVD)[sorderedcutname][8];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( nMShitsRel16( cutval1,cutval2,cutval3,cutval4,cutval5,cutval6,cutval7,cutval8,cutval9,
											 mu_nMDTBIHits->at(mu), mu_nMDTBMHits->at(mu), mu_nMDTBOHits->at(mu),
											 mu_nMDTEIHits->at(mu), mu_nMDTEMHits->at(mu), mu_nMDTEOHits->at(mu),
											 mu_nMDTBEEHits->at(mu), mu_nMDTEEHits->at(mu), mu_nMDTBIS78Hits->at(mu),
											 mu_nRPCLayer1PhiHits->at(mu), mu_nRPCLayer2PhiHits->at(mu), mu_nRPCLayer3PhiHits->at(mu),
											 mu_nTGCLayer1PhiHits->at(mu), mu_nTGCLayer2PhiHits->at(mu), mu_nTGCLayer3PhiHits->at(mu), mu_nTGCLayer4PhiHits->at(mu),
											 mu_nCSCEtaHits->at(mu), mu_nCSCPhiHits->at(mu)
											)
							 ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="isolation30"  &&  !bSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",mu_pt->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				//thisMuPass = ( isolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",
				//mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTmatchingRatio"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTmatchRatioCut( cutval1,cutval2,
				mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_id_qoverp->at(mu), mu_id_theta->at(mu) ) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTmatchingAbsDiff"  &&  !bSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTmatchAbsDiffCut( cutval1,
				mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_id_qoverp->at(mu), mu_id_theta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else continue;
		
		/////////////////////////////////////////////////////////////////////////
		// increment if passes the cut flow /////////////////////////////////////
		passCutFlow = (passCutFlow  &&  nMusPassed>1) ? true : false; ///////////
		/////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////
		// cutFlow /////////////////////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut  && bDoFill) fillCutFlow(sorderedcutname); ///////////
		if(passCutFlow  &&  !isSkippedCut 
						&&  sorderedcutname=="pT"
						&&  inApplySingleSelection
						&&  bDoFill)
		{
			(*fCand)	<< "Run-LB-Evt  "
						<< RunNumber  << " "
						<< lbn 		 << " "
						<< EventNumber
						<< endl;
		}
		////////////////////////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}

inline bool analysisSkeleton::doubleSelection(TMapsb& cutsToSkip)
{	
	bool isSkippedCut = (cutsToSkip.size()==0) ? false : true;
	TMapsb::iterator itrEnd = cutsToSkip.end();
	TMapsb::iterator itr;
	
	//////////////////////////////////////////
	// need at least 2 muons...///////////////
	int muSize = (int)mu_pt->size(); /////////
	if(muSize<2) return false; ///////////////
	//////////////////////////////////////////
	
	/////////////////////////////////////////////////////
	// count the good muons and find their id's /////////
	int nQAflags = countQAflags(); //////////////////////
	if(nQAflags<2) return false; ////////////////////////
	/////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////
	// see if there's a good pair (pT or imass sorted) //
	// and assign the ai and bi indices /////////////////
	bool isPair = assignPairIndices(); //////////////////
	if(!isPair) return false; ///////////////////////////
	/////////////////////////////////////////////////////
	
	passCutFlow    = true;
	passCurrentCut = true;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{	
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ////////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;
		
		bool bSkipCut = false;
		bool bDoFill  = true;
		if(isSkippedCut)
		{
			itr = cutsToSkip.find(sorderedcutname);
			if(itr!=itrEnd) bSkipCut = itr->second;
			else
			{
				itr = cutsToSkip.find("noFills");
				if(itr!=itrEnd) bDoFill = false;
			}
		}

		if(sorderedcutname=="oppositeCharge"  &&  !bSkipCut)
		{
			//passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(ai), mu_me_qoverp->at(bi)) ) ? true : false;
			//passCurrentCut = ( oppositeChargeCut(mu_me_qoverp->at(ai), mu_me_qoverp->at(bi)) ) ? true : false;
			passCurrentCut = ( oppositeChargeCut(mu_charge->at(ai), mu_charge->at(bi)) ) ? true : false;
		}

		else if(sorderedcutname=="imass"  &&  !bSkipCut)
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else if(sorderedcutname=="imassMax"  &&  !bSkipCut)
		{
			passCurrentCut = ( imassMaxCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		else if(sorderedcutname=="cosThetaDimu"  &&  !bSkipCut)
		{
			passCurrentCut = ( cosThetaDimuCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else if(sorderedcutname=="etaSum"  &&  !bSkipCut)
		{
			passCurrentCut = ( etaSumCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else continue;
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		//////////////////////////////////////////////////////////////////////////////////
		// cutFlow ///////////////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut  &&  bDoFill) fillCutFlow(sorderedcutname); ////
		//////////////////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}



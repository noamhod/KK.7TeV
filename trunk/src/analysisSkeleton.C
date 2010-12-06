
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
	if     (trigName=="L1_MU10") isTrig = isL1_MU10;
	else if(trigName=="EF_mu10") isTrig = isEF_mu10;
	else if(trigName=="EF_mu10_MG") isTrig = isEF_mu10_MG;
	else if(trigName=="EF_mu13") isTrig = isEF_mu13;
	else if(trigName=="EF_mu13_MG") isTrig = isEF_mu13_MG;
	else if(trigName=="EF_mu13_tight") isTrig = isEF_mu13_tight;
	else if(trigName=="EF_mu13_MG_tight") isTrig = isEF_mu13_MG_tight;
	else cout << "WARNING:  in analysisSkeleton::isTrigger -> the trigger " << trigName << " was not found and the event is regected by default" << endl;
	return isTrig;
}


////////////////////////////////////////////////////
// use this method only in the offline analysis. ///
// it should be called after the preselection //////
bool analysisSkeleton::digestSkim(int muSize)
{
	int skim  = 0;
	for(int mu=0 ; mu<muSize ; mu++)
	{
		if(mu_isCombinedMuon->at(mu)) skim++;
		//if( fabs(mu_pt->at(mu))>=15*GeV2MeV )
	}
	if( skim>1 ) return true;
	
	return false;
}
////////////////////////////////////////////////////


bool analysisSkeleton::skimD3PD(physics* phys)
{
	if(phys->mu_staco_n<1  &&  phys->mu_muid_n<1) return false;
	
	for(int m=0 ; m<(int)phys->mu_staco_n ; m++)
	{
		if( fabs(pT(phys->mu_staco_me_qoverp->at(m), phys->mu_staco_me_theta->at(m)))*MeV2GeV >= 15. ) return true;
	}

	for(int m=0 ; m<(int)phys->mu_muid_n ; m++)
	{
		if( fabs(pT(phys->mu_muid_me_qoverp->at(m), phys->mu_muid_me_theta->at(m))*MeV2GeV) >= 15. ) return true;
	}
	
	return false;
}


void analysisSkeleton::runEventDumper()
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// write the interesting events to a flat file ///////////////////////////////////////////////
	if(doEventDump)
	{
		int muMinus = (mu_charge->at(ai)<0) ? ai : bi;
		int muPlus  = (mu_charge->at(ai)>0) ? ai : bi;
		
		current_imass       = imass(pmu[muMinus],pmu[muPlus]);
		current_cosTheta    = cosThetaCollinsSoper( pmu[muMinus], -1, pmu[muPlus], +1 );
		current_mu_pT       = pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV;
		current_muplus_pT   = pT(mu_me_qoverp->at(muPlus),mu_me_theta->at(muPlus))*MeV2TeV;
		current_mu_eta      = mu_eta->at(muMinus);
		current_muplus_eta  = mu_eta->at(muPlus);
		current_cosmicCosth = cosThetaDimu(pmu[muMinus],pmu[muPlus]);
		current_etaSum      = current_muplus_eta + current_mu_eta;
		
		setCurrentEventMass( imass(pmu[muMinus],pmu[muPlus]) );
		writeEventHeader(RunNumber, lbn, EventNumber);
		
		writeProperty("$p_T$", pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV, pT(mu_me_qoverp->at(muPlus),mu_me_theta->at(muPlus))*MeV2TeV);
		writeProperty("$\\eta$", mu_eta->at(muMinus), mu_eta->at(muPlus));
		
		writeProperty("$\\sum{p_T^{cone20}}/p_T$", mu_ptcone20->at(muMinus)/mu_pt->at(muMinus), mu_ptcone20->at(muPlus)/mu_pt->at(muPlus));
		writeProperty("$\\sum{p_T^{cone30}}/p_T$", mu_ptcone30->at(muMinus)/mu_pt->at(muMinus), mu_ptcone30->at(muPlus)/mu_pt->at(muPlus));
		writeProperty("$\\sum{p_T^{cone40}}/p_T$", mu_ptcone40->at(muMinus)/mu_pt->at(muMinus), mu_ptcone40->at(muPlus)/mu_pt->at(muPlus));
		
		writeProperty("nSCThits", mu_nSCTHits->at(muMinus), mu_nSCTHits->at(muPlus));
		writeProperty("nPIXhits", mu_nPixHits->at(muMinus), mu_nPixHits->at(muPlus));
		writeProperty("nIDhits ", mu_nSCTHits->at(muMinus)+mu_nPixHits->at(muMinus), mu_nSCTHits->at(muPlus)+mu_nPixHits->at(muPlus));
		
		writeProperty("$\\hat{m}_{\\mu\\mu}$", "red", imass(pmu[muMinus],pmu[muPlus]));
		writeProperty("$\\sum{\\eta_{\\mu}}$", "red", current_muplus_eta + current_mu_eta);
		writeProperty("$\\hat{p}_{\\mu^-}\\cdot\\hat{p}_{\\mu^+}$", cosThetaDimu(pmu[muMinus],pmu[muPlus]));
		writeProperty("$\\cos\\theta_{\\mu^-}$", cosThetaCollinsSoper( pmu[muMinus], -1, pmu[muPlus], +1 ));
		
		
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
	printProperty("isL1_MU0", isL1_MU0);
	printProperty("isL1_MU10", isL1_MU10);
	printProperty("isL1_MU15", isL1_MU15);
	printProperty("isL1_MU20", isL1_MU20);
	printProperty("isL1_MU6", isL1_MU6);

	// EF triggers
	printProperty("isEF_mu10", isEF_mu10);
	printProperty("isEF_mu10_MG", isEF_mu10_MG);
	printProperty("isEF_mu10_MSonly", isEF_mu10_MSonly);
	printProperty("isEF_mu10_MSonly_tight", isEF_mu10_MSonly_tight);
	printProperty("isEF_mu10_NoAlg", isEF_mu10_NoAlg);
	printProperty("isEF_mu10_tight", isEF_mu10_tight);
	printProperty("isEF_mu10i_loose", isEF_mu10i_loose);
	printProperty("isEF_mu13", isEF_mu13);
	printProperty("isEF_mu13_MG", isEF_mu13_MG);
	printProperty("isEF_mu13_MG_tight", isEF_mu13_MG_tight);
	printProperty("isEF_mu13_tight", isEF_mu13_tight);
	printProperty("isEF_mu15", isEF_mu15);
	printProperty("isEF_mu15_NoAlg", isEF_mu15_NoAlg);
	printProperty("isEF_mu20", isEF_mu20);
	printProperty("isEF_mu20_MSonly", isEF_mu20_MSonly);
	printProperty("isEF_mu20_NoAlg", isEF_mu20_NoAlg);
	printProperty("isEF_mu20_slow", isEF_mu20_slow);
	printProperty("isEF_mu30_MSonly", isEF_mu30_MSonly);
	printProperty("isEF_mu4", isEF_mu4);
	printProperty("isEF_mu40_MSonly", isEF_mu40_MSonly);
   
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


void analysisSkeleton::fillAfterCuts()
{
	///////////////////////////////////////////////////////////
	// fill the "allCuts" histograms only after the last cut 
	// for the final histograms:
	// i.e., not the curFlow histos
	
	int muMinus = (mu_charge->at(ai)<0) ? ai : bi;
	int muPlus  = (mu_charge->at(ai)>0) ? ai : bi;
	
	current_imass       = imass(pmu[muMinus],pmu[muPlus]);
	current_cosTheta    = cosThetaCollinsSoper( pmu[muMinus], -1, pmu[muPlus], +1 );
	current_mu_pT       = pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV;
	current_muplus_pT   = pT(mu_me_qoverp->at(muPlus),mu_me_theta->at(muPlus))*MeV2TeV;
	current_mu_eta      = mu_eta->at(muMinus);
	current_muplus_eta  = mu_eta->at(muPlus);
	current_cosmicCosth = cosThetaDimu(pmu[muMinus],pmu[muPlus]);
	current_ipTdiff     = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_etaSum      = current_muplus_eta + current_mu_eta;
	
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
	
	h1_pTdiff->Fill( pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV - pT(mu_id_qoverp->at(muMinus),mu_id_theta->at(muMinus))*MeV2TeV );
	h1_pTdiff_muplus->Fill( pT(mu_me_qoverp->at(muPlus),mu_me_theta->at(muPlus))*MeV2TeV - pT(mu_id_qoverp->at(muPlus),mu_id_theta->at(muPlus))*MeV2TeV );
	h1_pTratio->Fill( fabs( pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus)) / pT(mu_id_qoverp->at(muMinus),mu_id_theta->at(muMinus)) ) );
	h1_pTratio_muplus->Fill( fabs( pT(mu_me_qoverp->at(muPlus),mu_me_theta->at(muPlus)) / pT(mu_id_qoverp->at(muPlus),mu_id_theta->at(muPlus)) ) );
	h2_pTmevspTid->Fill( pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV, pT(mu_id_qoverp->at(muMinus),mu_id_theta->at(muMinus))*MeV2TeV );
	h2_pTmevspTid_muplus->Fill( pT(mu_me_qoverp->at(muPlus),mu_me_theta->at(muPlus))*MeV2TeV, pT(mu_id_qoverp->at(muPlus),mu_id_theta->at(muPlus))*MeV2TeV );
	
	//cout << "\n$$$$$$$$$ dimuon $$$$$$$$$" << endl;
	//cout << "\t im=" << current_imass << endl;
	//cout << "\t pTmu=" << current_mu_pT  << endl;
	//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
	
	// fill the xVector for the ML fit:
	fillXvec( current_imass );
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

	int muSize = (int)mu_pt->size();
	if(sIsPreselection != "preselection"  &&  muSize==2)
	{
		int muMinus = (mu_charge->at(0)<0) ? 0 : 1;
		int muPlus  = (mu_charge->at(0)>0) ? 0 : 1;
		
		if(values2fill.size()>0) values2fill.clear();
		
		current_imass    = imass(pmu[muMinus],pmu[muPlus]);
		current_mu_pT    = pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV;
		current_cosTheta = cosThetaCollinsSoper( pmu[muMinus], -1, pmu[muPlus], +1 );
		
		//////////////////////////////////////////////////
		// for the Afb calculation ///////////////////////
		fillAfbMap(current_imass,current_cosTheta); //////
		//////////////////////////////////////////////////
		
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
	// the map is already sorted, no need to convert values
	TMapdi::reverse_iterator rit = pTtoIndexMap.rbegin();
	ai = rit->second;
	++rit;
	bi = rit->second;
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
	//if(pmu.size()>0) pmu.clear();
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
		cout << "you shhould call buildMU4Vector(int nMus) instead" << endl;
	}
	else
	{
		//if(pmu.size()>0) pmu.clear();
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
		ai = 0;
		bi = 1;
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
	return true;
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


bool analysisSkeleton::applyPreselection(string sSkipCut)
{
	bool isSkippedCut = (sSkipCut!="") ? true : false;

	///////////////////////////////////////////
	// do not skip this for correct counting //
	if(!isSkippedCut) incrementNallEvents(); //
	///////////////////////////////////////////

	passCutFlow = preselection(sSkipCut);
	
	return passCutFlow;
}

bool analysisSkeleton::applySingleMuonSelection(string sSkipCut)
{
	bool isSkippedCut = (sSkipCut=="") ? false : true;

	////////////////////////////////////////
	// fill the NO CUTS items //////////////
	if(!isSkippedCut) fillBeforeCuts(); ////
	////////////////////////////////////////
	
	passCutFlow = singleSelection(sSkipCut);
	
	return passCutFlow;
}

bool analysisSkeleton::applyDoubleMuonSelection(string sSkipCut)
{
	bool isSkippedCut = (sSkipCut=="") ? false : true;
	
	passCutFlow = doubleSelection(sSkipCut);
	
	if(passCutFlow  &&  !isSkippedCut)
	{
		///////////////////////////////////////////////
		// fill the cutFlow and the allCuts items /////
		fillAfterCuts(); //////////////////////////////
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
		
		pass = true;
		pass = (pass && preselection(sname))    ? true : false;
		pass = (pass && singleSelection(sname)) ? true : false;
		pass = (pass && doubleSelection(sname)) ? true : false;
		
		if(pass)
		{
			if     (sname=="GRL")     (*h1map_cutProfile)[sname]->Fill( isGRL );
			else if(sname=="Trigger") (*h1map_cutProfile)[sname]->Fill( isTrigger(vTriggers->at(0)) );
			
			else if(sname=="pT_1")      (*h1map_cutProfile)[sname]->Fill( mu_pt->at(ai)*MeV2TeV );
			else if(sname=="pT_2")      (*h1map_cutProfile)[sname]->Fill( mu_pt->at(bi)*MeV2TeV );
			else if(sname=="pT_use_qOp_and_theta_1") (*h1map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai)) );
			else if(sname=="pT_use_qOp_and_theta_2") (*h1map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi)) );
			else if(sname=="eta_1") (*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
			else if(sname=="eta_2") (*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
			else if(sname=="etaTight_1")  (*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
			else if(sname=="etaTight_2")  (*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
			else if(sname=="etaBarrel_1") (*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai) );
			else if(sname=="etaBarrel_2") (*h1map_cutProfile)[sname]->Fill( mu_eta->at(bi) );
			else if(sname=="pTmatchingRatio_1")
			{
				float pTid = pT(mu_id_qoverp->at(ai), mu_id_theta->at(ai));
				if(pTid!=0.) (*h1map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(ai), mu_me_theta->at(ai)) / pTid );
			}
			else if(sname=="pTmatchingRatio_2")
			{
				float pTid = pT(mu_id_qoverp->at(bi), mu_id_theta->at(bi));
				if(pTid!=0.) (*h1map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(bi), mu_me_theta->at(bi)) / pTid );
			}
			else if(sname=="pTmatchingAbsDiff_1") (*h1map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai)) - pT(mu_id_qoverp->at(ai), mu_id_theta->at(ai)) );
			else if(sname=="pTmatchingAbsDiff_2") (*h1map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi)) - pT(mu_id_qoverp->at(bi), mu_id_theta->at(bi)) );
			else if(sname=="d0_1") (*h1map_cutProfile)[sname]->Fill( mu_d0_exPV->at(ai) );
			else if(sname=="d0_2") (*h1map_cutProfile)[sname]->Fill( mu_d0_exPV->at(bi) );
			else if(sname=="z0_1") (*h1map_cutProfile)[sname]->Fill( mu_z0_exPV->at(ai) );
			else if(sname=="z0_2") (*h1map_cutProfile)[sname]->Fill( mu_z0_exPV->at(bi) );
			else if(sname=="isolation20_1") (*h1map_cutProfile)[sname]->Fill( mu_ptcone20->at(ai)/pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai)) );
			else if(sname=="isolation20_2") (*h1map_cutProfile)[sname]->Fill( mu_ptcone20->at(bi)/pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi)) );
			else if(sname=="isolation30_1") (*h1map_cutProfile)[sname]->Fill( mu_ptcone30->at(ai)/pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai)) );
			else if(sname=="isolation30_2") (*h1map_cutProfile)[sname]->Fill( mu_ptcone30->at(bi)/pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi)) );
			else if(sname=="isolation40_1") (*h1map_cutProfile)[sname]->Fill( mu_ptcone40->at(ai)/pT(mu_me_qoverp->at(ai),mu_me_theta->at(ai)) );
			else if(sname=="isolation40_2") (*h1map_cutProfile)[sname]->Fill( mu_ptcone40->at(bi)/pT(mu_me_qoverp->at(bi),mu_me_theta->at(bi)) );
			else if(sname=="nMDTBI_1") (*h1map_cutProfile)[sname]->Fill( mu_nMDTBIHits->at(ai) );
			else if(sname=="nMDTBM_1") (*h1map_cutProfile)[sname]->Fill( mu_nMDTBMHits->at(ai) );
			else if(sname=="nMDTBO_1") (*h1map_cutProfile)[sname]->Fill( mu_nMDTBOHits->at(ai) );
			else if(sname=="nMDTBI_2") (*h1map_cutProfile)[sname]->Fill( mu_nMDTBIHits->at(bi) );
			else if(sname=="nMDTBM_2") (*h1map_cutProfile)[sname]->Fill( mu_nMDTBMHits->at(bi) );
			else if(sname=="nMDTBO_2") (*h1map_cutProfile)[sname]->Fill( mu_nMDTBOHits->at(bi) );
			else if(sname=="nRPCPhi1_1") (*h1map_cutProfile)[sname]->Fill( mu_nRPCLayer1PhiHits->at(ai) );
			else if(sname=="nRPCPhi2_1") (*h1map_cutProfile)[sname]->Fill( mu_nRPCLayer2PhiHits->at(ai) );
			else if(sname=="nRPCPhi3_1") (*h1map_cutProfile)[sname]->Fill( mu_nRPCLayer3PhiHits->at(ai) );
			else if(sname=="nRPCPhi1_2") (*h1map_cutProfile)[sname]->Fill( mu_nRPCLayer1PhiHits->at(bi) );
			else if(sname=="nRPCPhi2_2") (*h1map_cutProfile)[sname]->Fill( mu_nRPCLayer2PhiHits->at(bi) );
			else if(sname=="nRPCPhi3_2") (*h1map_cutProfile)[sname]->Fill( mu_nRPCLayer3PhiHits->at(bi) );
			
			else if(sname=="oppositeCharge") (*h1map_cutProfile)[sname]->Fill( mu_charge->at(ai)*mu_charge->at(bi) );
			else if(sname=="imass")          (*h1map_cutProfile)[sname]->Fill( imass(pmu[ai],pmu[bi]) );
			else if(sname=="cosThetaDimu")   (*h1map_cutProfile)[sname]->Fill( cosThetaDimu(pmu[ai],pmu[bi]) );
			else if(sname=="etaSum")         (*h1map_cutProfile)[sname]->Fill( mu_eta->at(ai)+mu_eta->at(bi) );
		}
	}
}

void analysisSkeleton::fillCutProfile2D()
{
	bool pass;
	for(TMapSP2TH2D::iterator it=h2map_cutProfile->begin() ; it!=h2map_cutProfile->end() ; it++)
	{
		string sname = it->first;
		
		pass = true;
		pass = (pass && preselection(sname))    ? true : false;
		pass = (pass  & singleSelection(sname)) ? true : false;
		pass = (pass && doubleSelection(sname)) ? true : false;
		
		if(pass)
		{
			if(sname=="PV")
			{
				float cutval = (*m_cutFlowMapSVD)[sname][1]; // vxp_type==1 (the second cutVal)
				for(int v=0 ; (v<(int)vxp_type->size() && vxp_type->at(v)==cutval) ; v++)
				{
					(*h2map_cutProfile)[sname]->Fill( vxp_z->at(v),vxp_nTracks->at(v) );
				}
			}
			else if(sname=="pTandEta_1")  (*h2map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai)), mu_eta->at(ai) );
			else if(sname=="pTandEta_2")  (*h2map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi)), mu_eta->at(bi) );
			else if(sname=="pTandEtaTight_1")  (*h2map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai)), mu_eta->at(ai) );
			else if(sname=="pTandEtaTight_2")  (*h2map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi)), mu_eta->at(bi) );
			else if(sname=="pTandEtaBarrel_1") (*h2map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(ai)/MeV2TeV, mu_me_theta->at(ai)), mu_eta->at(ai) );
			else if(sname=="pTandEtaBarrel_2") (*h2map_cutProfile)[sname]->Fill( pT(mu_me_qoverp->at(bi)/MeV2TeV, mu_me_theta->at(bi)), mu_eta->at(bi) );
			else if(sname=="idHits_1") (*h2map_cutProfile)[sname]->Fill( mu_nSCTHits->at(ai), mu_nPixHits->at(ai) );
			else if(sname=="idHits_2") (*h2map_cutProfile)[sname]->Fill( mu_nSCTHits->at(bi), mu_nPixHits->at(bi) );
			else if(sname=="impactParameter_1") (*h2map_cutProfile)[sname]->Fill( mu_d0_exPV->at(ai), mu_z0_exPV->at(ai) );
			else if(sname=="impactParameter_2") (*h2map_cutProfile)[sname]->Fill( mu_d0_exPV->at(bi), mu_z0_exPV->at(bi) );
		}
	}
}

/*
void analysisSkeleton::fillTagNProbe()
{
	// Tag&Probe mask:
	// retrun 0: event was not triggered
	// retrun 1: matched vector is NULL or empty
	// retrun 2: event was not tagged
	// retrun 3: event was tagged but with a problem
	// retrun 4: event was tagged, found a probe candidate but not probed it and there's a problem with this cand
	// retrun 5: event was tagged, found a probe candidate but not probed it
	// retrun 6: event was tagged, found a probe candidate and probed it but the probe has a problem
	// retrun 7: event was tagged and probed
	// retrun 8: else
	int itag   = -1;
	int iprobe = -1;
	int tNp_mask = tagNprobeMask(isL1_MU10, mu_L1_matched, mu_L1_dr, pmu, mu_charge, itag, iprobe);
	switch(tNp_mask)
	{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5:
			h1_tagNprobe_candidates_pT->Fill( fabs(pT(mu_me_qoverp->at(iprobe)/MeV2TeV, mu_me_theta->at(iprobe))) );
			h1_tagNprobe_candidates_eta->Fill( mu_eta->at(iprobe) );
			h1_tagNprobe_candidates_phi->Fill( mu_phi->at(iprobe) );
			break;
		case 6: break;
		case 7:
			h1_tagNprobe_candidates_pT->Fill( fabs(pT(mu_me_qoverp->at(iprobe)/MeV2TeV, mu_me_theta->at(iprobe))) );
			h1_tagNprobe_candidates_eta->Fill( mu_eta->at(iprobe) );
			h1_tagNprobe_candidates_phi->Fill( mu_phi->at(iprobe) );
			h1_tagNprobe_succeeded_pT->Fill( fabs(pT(mu_me_qoverp->at(iprobe)/MeV2TeV, mu_me_theta->at(iprobe))) );
			h1_tagNprobe_succeeded_eta->Fill( mu_eta->at(iprobe) );
			h1_tagNprobe_succeeded_phi->Fill( mu_phi->at(iprobe) );
			break;
		case 8: break;
		default: break;
	}
}
*/

void analysisSkeleton::fillTagNProbe()
{
	// Tag&Probe mask:
	// retrun 0: matched vector is null or empty (no fill)
	// retrun 1: event CANNOT be tagged (no fill)
	// retrun 2: event was tagged, probe candidate found but not probed
	// retrun 3: event was tagged, probe candidate found and probed
	// retrun 4: else
	
	int itag;
	int iprobe;
	int tNp_mask;
	for(int i=1 ; i<=2 ; i++)
	{
		if(i==1)
		{
			itag   = -1;
			iprobe = -1;
		}
		tNp_mask = tagNprobeMask(mu_L1_matched, pmu, mu_charge, itag, iprobe);
		switch(tNp_mask)
		{
			case 0: break;
			case 1: break;
			case 2:
				h1_tagNprobe_candidates_pT->Fill( fabs(pT(mu_me_qoverp->at(iprobe)/MeV2TeV, mu_me_theta->at(iprobe))) );
				h1_tagNprobe_candidates_eta->Fill( mu_eta->at(iprobe) );
				h1_tagNprobe_candidates_phi->Fill( mu_phi->at(iprobe) );
				break;
			case 3:
				h1_tagNprobe_candidates_pT->Fill( fabs(pT(mu_me_qoverp->at(iprobe)/MeV2TeV, mu_me_theta->at(iprobe))) );
				h1_tagNprobe_candidates_eta->Fill( mu_eta->at(iprobe) );
				h1_tagNprobe_candidates_phi->Fill( mu_phi->at(iprobe) );
				h1_tagNprobe_succeeded_pT->Fill( fabs(pT(mu_me_qoverp->at(iprobe)/MeV2TeV, mu_me_theta->at(iprobe))) );
				h1_tagNprobe_succeeded_eta->Fill( mu_eta->at(iprobe) );
				h1_tagNprobe_succeeded_phi->Fill( mu_phi->at(iprobe) );
				break;
			case 4: break;
			default: break;
		}
	}
}

void analysisSkeleton::fillTruthEfficiency()
{
	//mu_truth_matched = True if muon is matched to the truth
	//mu_truth_status  : Status oMC status = 1 pfinal particle, status = 3 intermediate particle (documentary)
	//mu_truth_mothertype : description: True mother PDG type
	
	cout << "\nmu_truth_pt->size() = " << mu_truth_pt->size() << ",  mu_pt->size() = " << mu_pt->size() << endl;
	for(int t=0 ; t<(int)mu_truth_pt->size() ; t++)
	{
		//if(mu_n<2) continue; 
	
		//if(!mu_truth_matched->at(t)) continue;
		if(!mu_truth_status->at(t)) continue;
		if(mu_truth_mothertype->at(t)!=PDTZ  &&  mu_truth_mothertype->at(t)!=PDTGAMMA) continue;
		//if(as_mcevt_n==1)
		//{
		//	if(fabs(as_mcevt_pdf_scale->at(0)-mZ0)>10.) continue; // everything is in GeV
		//}
		
		float dphi = mu_truth_phi->at(t) - mu_phi->at(t);
		float deta = mu_truth_eta->at(t) - mu_eta->at(t);
		float drMatch = sqrt(dphi*dphi + deta*deta);
		cout << "truth-reco matching : mu_truth_matched->at(" << t << ") = " << mu_truth_matched->at(t) << endl;
		cout <<	"truth-reco dR       : mu_truth_dr->at(" << t << ") = " << mu_truth_dr->at(t) << ",  dRcalculatedManually->at(" << t << ") = " << drMatch << endl;
		cout << "truth-reco pT       : mu_truth_pt->at(" << t << ") = " << mu_truth_pt->at(t) << ",  mu_pt->at(" << t << ") = " << mu_pt->at(t) << endl;
		cout << "reco-trig matching  : mu_L1_matched->at(" << t << ") = " << mu_L1_matched->at(t) << endl;
		
		// fill the denominator histos
		h1_truth_candidates_pT->Fill( fabs(pT(mu_me_qoverp->at(t)/MeV2TeV, mu_me_theta->at(t))) );
		h1_truth_candidates_eta->Fill( mu_eta->at(t) );
		h1_truth_candidates_phi->Fill( mu_phi->at(t) );
		
		//if(!isL1_MU10) continue;
		if(!mu_L1_matched->at(t)) continue;
		if(mu_L1_dr->at(t)<0.)    continue;
		//if(mu_L1_dr->at(t)>dRthreshold  ||  mu_L1_dr->at(t)<0.) continue;

		h1_truth_succeeded_pT->Fill( fabs(pT(mu_me_qoverp->at(t)/MeV2TeV, mu_me_theta->at(t))) );
		h1_truth_succeeded_eta->Fill( mu_eta->at(t) );
		h1_truth_succeeded_phi->Fill( mu_phi->at(t) );
	}
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


bool analysisSkeleton::preselection(string sSkipCut)
{
	bool isSkippedCut = (sSkipCut=="") ? false : true;

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

		if(sorderedcutname=="GRL"  &&  sorderedcutname!=sSkipCut)
		{
			passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], isGRL) ) ? true : false;
		}

		else if(sorderedcutname=="L1_MU6"  &&  sorderedcutname!=sSkipCut)
		{
			passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], isL1_MU6) ) ? true : false;
		}
		
		else if(sorderedcutname=="Trigger"  &&  sorderedcutname!=sSkipCut)
		{
			//string trigName = vTriggers->at(0);
			//int trigVal = isTrigger(trigName);
			//passCurrentCut = ( triggerCut((*m_cutFlowMapSVD)[sorderedcutname][0], trigVal, trigName) ) ? true : false;
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
		
		else if(sorderedcutname=="EF_mu13"  &&  sorderedcutname!=sSkipCut)
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], isEF_mu13) ) ? true : false;
		}
		
		else if(sorderedcutname=="hipTmuon"  &&  sorderedcutname!=sSkipCut)
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			passCurrentCut = ( findHipTmuon(cutval1, cutval2,
			(int)mu_pt->size(), mu_pt, mu_me_qoverp, mu_me_theta) ) ? true : false;
		}
		
		else if(sorderedcutname=="PV"  &&  sorderedcutname!=sSkipCut)
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
		
		////////////////////////////////////////////////////////////////////////////////////////
		// cutFlow /////////////////////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut) fillCutFlow(sorderedcutname, "preselection"); ///////
		////////////////////////////////////////////////////////////////////////////////////////
	}
	
	return passCutFlow;
}

bool analysisSkeleton::singleSelection(string sSkipCut)
{
	bool isSkippedCut = (sSkipCut=="") ? false : true;
	
	int muSize  = (int)mu_charge->size();

	passCutFlow = true;
	
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string sorderedcutname = ii->second;
		nMusPassed = 0;
		
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
		
		if(sorderedcutname=="pT"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pT_use_qOp_and_theta"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(mu), mu_me_theta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="eta"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaTight"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaTightCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaBarrel"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaBarrelCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTandEta"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="pTandEtaTight"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="pTandEtaBarrel"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
				float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
				thisMuPass = ( pTandEtaBarrelCut(cutval1, cutval2,
				mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_eta->at(mu)) ) ? true : false;
				//thisMuPass = ( pTandEtaBarrelCut(cutval1, cutval2, mu_pt->at(mu), mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="d0"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_d0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="z0"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_z0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="impactParameter"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="isCombMu"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_isCombinedMuon->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="idHits"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="ms3stationsMDThits"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="msHits"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="isolation30"  &&  sorderedcutname!=sSkipCut)
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				//thisMuPass = ( isolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",
				//mu_pt->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				thisMuPass = ( isolationXXCut((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",
				mu_me_qoverp->at(mu), mu_me_theta->at(mu), mu_ptcone30->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTmatchingRatio"  &&  sorderedcutname!=sSkipCut)
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
		
		else if(sorderedcutname=="pTmatchingAbsDiff"  &&  sorderedcutname!=sSkipCut)
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
		
		////////////////////////////////////////////////////////////////////////
		// cutFlow /////////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut) fillCutFlow(sorderedcutname); ///////
		////////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}

bool analysisSkeleton::doubleSelection(string sSkipCut)
{
	bool isSkippedCut = (sSkipCut=="") ? false : true;
	
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

		if(sorderedcutname=="oppositeCharge"  &&  sorderedcutname!=sSkipCut)
		{
			//passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(ai), mu_me_qoverp->at(bi)) ) ? true : false;
			//passCurrentCut = ( oppositeChargeCut(mu_me_qoverp->at(ai), mu_me_qoverp->at(bi)) ) ? true : false;
			passCurrentCut = ( oppositeChargeCut(mu_charge->at(ai), mu_charge->at(bi)) ) ? true : false;
		}

		else if(sorderedcutname=="imass"  &&  sorderedcutname!=sSkipCut)
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		else if(sorderedcutname=="cosThetaDimu"  &&  sorderedcutname!=sSkipCut)
		{
			passCurrentCut = ( cosThetaDimuCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else if(sorderedcutname=="etaSum"  &&  sorderedcutname!=sSkipCut)
		{
			passCurrentCut = ( etaSumCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else continue;
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		/////////////////////////////////////////////////////////////////////
		// cutFlow //////////////////////////////////////////////////////////
		if(passCutFlow  &&  !isSkippedCut) fillCutFlow(sorderedcutname); ////
		/////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}




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
	if(runnumber != currentRun)
	{
		speriod = getPeriod( runnumber, m_firstrun2periodMap, m_lastrun2periodMap );
		cout << "switching to period: " << speriod << endl;
		currentRun     = runnumber;
		sCurrentPeriod = speriod;
	}
	if(speriod=="")
	{
		cout << "ERROR: in analysisSkeleton::getPeriodName -> (speriod==""), exitting now" << endl;
		exit(-1);
	}
	
	return speriod;
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
	int skim1 = 0;
	int skim2 = 0;
	for(int mu=0 ; mu<muSize ; mu++)
	{
		if( fabs(mu_pt->at(mu))>15*GeV2MeV ) skim1++;
		if( mu_isCombinedMuon->at(mu) )      skim2++;
	}
	
	if( skim1>1  &&  skim2>1 ) return true;
	return false;
}
////////////////////////////////////////////////////


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
		writeEventHeader(runnumber, lumiblock, eventnumber);
		
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
	
		current_imass = imass(pmu[muMinus],pmu[muPlus]);
		current_mu_pT = pT(mu_me_qoverp->at(muMinus),mu_me_theta->at(muMinus))*MeV2TeV;
	
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


bool analysisSkeleton::applyPreselection(string sRunType)
{
	///////////////////////////////////////////
	// do not skip this for correct counting //
	nAllEvents++; ///////////
	///////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////
	// no need to preselect in the digest-like run //////////////////
	// only need to count the total number of events ////////////////
	if(sRunType=="digest" || sRunType=="mcDigest") return true; /////
	/////////////////////////////////////////////////////////////////
	
	// local variables
	passCutFlow    = true;
	passCurrentCut = true;
	counter = 0;
	
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		
		///////////////////////////////////////////////////////////////////////////
		// ignore selection: //////////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="selection") continue; //////////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;

		if(sorderedcutname=="GRL")
		{
			passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], isGRL) ) ? true : false;
		}

		else if(sorderedcutname=="L1_MU6")
		{
			passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], isL1_MU6) ) ? true : false;
		}
		
		else if(sorderedcutname=="Trigger")
		{
			string trigName = vTriggers->at(0);
			int trigVal = isTrigger(trigName);
			passCurrentCut = ( triggerCut((*m_cutFlowMapSVD)[sorderedcutname][0], trigVal, trigName) ) ? true : false;
		}
		
		else if(sorderedcutname=="EF_mu13")
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], isEF_mu13) ) ? true : false;
		}
		
		else if(sorderedcutname=="hipTmuon")
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			passCurrentCut = ( findHipTmuon(cutval1, cutval2,
											(int)mu_pt->size(), mu_pt, mu_me_qoverp, mu_me_theta) ) ? true : false;
		}
		
		else if(sorderedcutname=="PV")
		{
			float cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			float cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			float cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
											  (int)vxp_type->size(), vxp_nTracks, vxp_type, vxp_z) ) ? true : false;
		}
		
		else continue;
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		/////////////////////////////////////////////////////////////////////
		// cutFlow //////////////////////////////////////////////////////////
		if(passCutFlow) fillCutFlow(sorderedcutname, "preselection"); ///////
		/////////////////////////////////////////////////////////////////////
	}
	
	//////////////////////////////////////////////
	// need at least 2 muons...///////////////////
	if(mu_n<2) passCutFlow = false; //////////////
	//////////////////////////////////////////////
	
	return passCutFlow;
}

bool analysisSkeleton::applySingleMuonSelection()
{
	///////////////////////////////////
	// fill the NO CUTS items /////////
	fillBeforeCuts(); /////////////////
	///////////////////////////////////
	
	// fill the cut flow, stop at the relevant cut each time.
	// the cut objects don't have to be "correctly" ordered
	// since it is done by the loop on the ordered cut flow map
	counter = 0;
	passCutFlow = true;
	int muSize = (int)mu_charge->size();
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		string sorderedcutname = ii->second;
		nMusPassed = 0;
		
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////

		if(sorderedcutname=="pT")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_pt->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
	
		else if(sorderedcutname=="pT_use_qOp_and_theta")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(mu), mu_me_theta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="eta")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="etaTight")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( etaTightCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_eta->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="pTandEtaTight")
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
		
		else if(sorderedcutname=="d0")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_d0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="z0")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_z0_exPV->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="impactParameter")
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
		
		else if(sorderedcutname=="isCombMu")
		{
			for(int mu=0 ; mu<muSize ; mu++)
			{
				thisMuPass = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_isCombinedMuon->at(mu)) ) ? true : false;
				muQAflags[mu] = (muQAflags[mu]  &&  thisMuPass) ? true : false;
				if(thisMuPass  &&  muQAflags[mu]) nMusPassed++;
			}
		}
		
		else if(sorderedcutname=="idHits")
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
		
		else if(sorderedcutname=="ms3stationsMDThits")
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
		
		else if(sorderedcutname=="isolation30")
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
		
		else if(sorderedcutname=="pTmatchingRatio")
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
		
		else if(sorderedcutname=="pTmatchingAbsDiff")
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
		
		/////////////////////////////////////////////////////
		// cutFlow //////////////////////////////////////////
		if(passCutFlow) fillCutFlow(sorderedcutname); ///////
		/////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	return passCutFlow;
}

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
	if(pmu.size()>0) pmu.clear();
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
		if(pmu.size()>0) pmu.clear();
		for(int n=0 ; n<nMus ; n++)
		{
			pmu.push_back( new TLorentzVector() );
			pmu[n]->SetPtEtaPhiM( mu_pt->at(n)*MeV2TeV, mu_eta->at(n), mu_phi->at(n), muonMass*GeV2TeV);
		}
	}
}


bool analysisSkeleton::applyDoubleMuonSelection()
{
	int muSize = (int)mu_pt->size();
	
	//////////////////////////////////////////
	// need at least 2 muons...///////////////
	if(muSize<2) return false; ///////////////
	//////////////////////////////////////////
	
	/////////////////////////////////////////////////////
	// count the good muons and find their id's /////////
	int nQAflags = countQAflags(); //////////////////////
	if(nQAflags<2) return false; ////////////////////////
	/////////////////////////////////////////////////////
	
	// select the final muon pair
	if(pTtoIndexMap.size()==2)
	{
		ai = 0;
		bi = 1;
	}
	else if(pTtoIndexMap.size()>2)
	{
		//pTSort();
		imassSort();
		nMultiMuonEvents++;
	}
	else
	{
		cout << "WARNING: in analysisSkeleton::applyDoubleMuonSelection(TVectorP2VL& pmu) but there are <2 good single-muons" << endl;
		return false;
	}
	
	// the cut objects don't have to be "correctly" ordered
	// since it is done by the loop on the ordered cut flow map
	passCutFlow    = true;
	passCurrentCut = true;
	counter        = 0;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		
		///////////////////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////////////////
		float num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////////////////
	
		string sorderedcutname = ii->second;

		if(sorderedcutname=="oppositeCharge")
		{
			//passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_me_qoverp->at(ai), mu_me_qoverp->at(bi)) ) ? true : false;
			//passCurrentCut = ( oppositeChargeCut(mu_me_qoverp->at(ai), mu_me_qoverp->at(bi)) ) ? true : false;
			passCurrentCut = ( oppositeChargeCut(mu_charge->at(ai), mu_charge->at(bi)) ) ? true : false;
		}

		else if(sorderedcutname=="imass")
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		else if(sorderedcutname=="cosThetaDimu")
		{
			passCurrentCut = ( cosThetaDimuCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else if(sorderedcutname=="etaSum")
		{
			passCurrentCut = ( etaSumCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		else continue;
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		/////////////////////////////////////////////////////////////////////
		// cutFlow //////////////////////////////////////////////////////////
		if(passCutFlow) fillCutFlow(sorderedcutname); ///////////////////////
		/////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	if(passCutFlow)
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


/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "combinedSelection.h"

combinedSelection::combinedSelection()
{
	doEventDump = false;
}

combinedSelection::~combinedSelection()
{

}

void combinedSelection::initCombinedSelection(graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, fit* fitter, string sEventDumpFilePath)
{
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
	
	if(sEventDumpFilePath != "") setEventDumper(sEventDumpFilePath);
	
	m_fitter = fitter;
	
	cout << "init combined selection OK" << endl;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void combinedSelection::setEventDumper(string sEventDumpFilePath)
{
	doEventDump = true;
	m_eventDumper = new eventDumper( sEventDumpFilePath );
	m_eventDumper->setInterestingThreshold( 250.*GeV2TeV );
	
	cout << "set event dumper OK" << endl;
}

void combinedSelection::runEventDumper(bool passCutFlow, int ai)
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// write the interesting events to a flat file ///////////////////////////////////////////////
	if(passCutFlow  &&  doEventDump)
	{	
		m_eventDumper->setCurrentEventMass( current_imass );
		m_eventDumper->writeEventHeader(runnumber, lumiblock, eventnumber);
		
		m_eventDumper->writeProperty("$p_T$", current_mu_pT, current_muplus_pT);
		m_eventDumper->writeProperty("$\\eta$", current_mu_eta, current_muplus_eta);
		
		double ca = mu_staco_charge->at(ai);
		if(ca<0)
		{
			m_eventDumper->writeProperty("$\\sum{p_T^{cone20}}/p_T$", pTcone20a/mu_pTa, pTcone20b/mu_pTb);
			m_eventDumper->writeProperty("$\\sum{p_T^{cone30}}/p_T$", pTcone30a/mu_pTa, pTcone30b/mu_pTb);
			m_eventDumper->writeProperty("$\\sum{p_T^{cone40}}/p_T$", pTcone40a/mu_pTa, pTcone40b/mu_pTb);
			
			m_eventDumper->writeProperty("nSCThits", nSCThitsMua, nSCThitsMub);
			m_eventDumper->writeProperty("nPIXhits", nPIXhitsMua, nPIXhitsMub);
			m_eventDumper->writeProperty("nIDhits ", nIDhitsMua, nIDhitsMub);
		}
		else
		{
			m_eventDumper->writeProperty("$\\sum{p_T^{cone20}}/p_T$", pTcone20b/mu_pTb, pTcone20a/mu_pTa);
			m_eventDumper->writeProperty("$\\sum{p_T^{cone30}}/p_T$", pTcone30b/mu_pTb, pTcone30a/mu_pTa);
			m_eventDumper->writeProperty("$\\sum{p_T^{cone40}}/p_T$", pTcone40b/mu_pTb, pTcone40a/mu_pTa);
			
			m_eventDumper->writeProperty("nSCThits", nSCThitsMub, nSCThitsMua);
			m_eventDumper->writeProperty("nPIXhits", nPIXhitsMub, nPIXhitsMua);
			m_eventDumper->writeProperty("nIDhits ", nIDhitsMub, nIDhitsMua);
		}
		
		m_eventDumper->writeProperty("$\\hat{m}_{\\mu\\mu}$", "red", current_imass);
		m_eventDumper->writeProperty("$\\hat{p}_{\\mu^-}\\cdot\\hat{p}_{\\mu^+}$", current_cosmicCosth);
		m_eventDumper->writeProperty("$\\cos\\theta_{\\mu^-}$", current_cosTheta);
		
		m_eventDumper->writeEventFooter();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void combinedSelection::fillAfterCuts(bool passCutFlow, int counter, string sorderedcutname, TMapsd& values2fill)
{
	if(passCutFlow)
	{
		//////////////////////////////////////////////////////
		// for the cut flow: /////////////////////////////////
		m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+sorderedcutname)->Fill( values2fill["imass"] );
		m_graphicobjs->hmap_cutFlow_pT->operator[]("pT."+sorderedcutname)->Fill( values2fill["pT"] );
		//////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////
		// count the numbers: ////////////////////////////////
		m_cutFlowNumbers->operator[](sorderedcutname) ++; ////
		//////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////
		// fill the "allCuts" histograms only after the last cut 
		if(counter==(int)m_cutFlowOrdered->size())
		{
			// for the final histograms:
			// i.e., not the curFlow histos
			if(current_imass>=XMIN  &&  current_imass<=XMAX) m_graphicobjs->h1_costh->Fill( current_cosTheta );
			m_graphicobjs->h1_cosmicCosthAllCuts->Fill( current_cosmicCosth );
			m_graphicobjs->h1_pT->Fill( current_mu_pT );
			m_graphicobjs->h1_pT_muplus->Fill( current_muplus_pT );
			m_graphicobjs->h1_eta->Fill( current_mu_eta );
			m_graphicobjs->h1_eta_muplus->Fill( current_muplus_eta );
			m_graphicobjs->h1_ipTdiff->Fill( current_ipTdiff );
			m_graphicobjs->h1_etaSum->Fill( current_etaSum );
			m_graphicobjs->h1_imass->Fill( current_imass );
			m_graphicobjs->h1_imassFit->Fill( current_imass );
			
			cout << "\n$$$$$$$$$ dimuon $$$$$$$$$" << endl;
			cout << "\t im=" << current_imass << endl;
			cout << "\t pTmu=" << current_mu_pT  << endl;
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			
			// fill the xVector for the ML fit:
			m_fitter->fillXvec( current_imass );
		}
		///////////////////////////////////////////////////////////
	} // end if(passCutFlow)
}

void combinedSelection::fillBeforeCuts()
{
	// fill nocuts histograms
	m_graphicobjs->h1_cosmicCosth->Fill( current_cosmicCosth );
	m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
	m_graphicobjs->h1_d0exPV->Fill(d0exPVb);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVa);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVb);
	//X( prtD0*cos(phi) );
	//Y( prtD0*sin(phi) );
	//Z( Z0 );
	m_graphicobjs->h2_xyVertex->Fill( d0exPVa*cos(phi_a), d0exPVa*sin(phi_a) );
	m_graphicobjs->h2_xyVertex->Fill( d0exPVb*cos(phi_b), d0exPVb*sin(phi_b) );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


bool combinedSelection::applyPreselection(string sRunType)
{
	///////////////////////////////////////////
	// do not skip this for correct counting //
	m_cutFlowHandler->nAllEvents++; ///////////
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
		double num = ii->first; ///////////////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="selection") continue; //////////
		///////////////////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;

		if(sorderedcutname=="GRL")
		{
			passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], isGRL) ) ? true : false;
		}
		

		if(sorderedcutname=="L1_MU6")
		{
			passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], isL1MU6) ) ? true : false;
		}
		
		
		if(sorderedcutname=="EF_mu13")
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], isEF_mu13) ) ? true : false;
		}
		
		
		if(sorderedcutname=="hipTmuon")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			//passCurrentCut = ( findHipTmuon(cutval1, cutval2,
			//								mu_staco_n, mu_staco_pt, mu_staco_me_qoverp, mu_staco_me_theta) ) ? true : false;
			passCurrentCut = ( findHipTmuon(cutval1, cutval2,
											(int)mu_staco_pt->size(), mu_staco_pt, mu_staco_me_qoverp, mu_staco_me_theta) ) ? true : false;
		}
		
		
		if(sorderedcutname=="PV")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			//passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
			//								   vxp_n, vxp_nTracks, vxp_type, vxp_z) ) ? true : false;
			passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
											   (int)vxp_type->size(), vxp_nTracks, vxp_type, vxp_z) ) ? true : false;
		}
		
		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		if(passCutFlow)
		{
			//////////////////////////////////////////////////////
			// count the numbers: ////////////////////////////////
			m_cutFlowNumbers->operator[](sorderedcutname) ++; ////
			//////////////////////////////////////////////////////
		}
	}
	
	return passCutFlow;
}


bool combinedSelection::setMUindices(TVectorP2VL& pmu, string sRunType)
{
	////////////////////////////////////////
	// need at least 2 muons.../////////////
	// otherwise, continue /////////////////
	// the next cut which identifies as ////
	// the 1st selection cut, MUST be the //
	// opposite charge cut, otherwise the //
	// entire counting procedure will get //
	// screwed up. This is determined in  //
	// the cutFlow.cuts file ///////////////
	if(pmu.size()<2) return false; /////////
	////////////////////////////////////////
	

	if(sRunType == "digest")
	{
		iVtx = 0;
		ai = 0;
		bi = 1;
	}
	else
	{
		/////////////////////////////////////////////////////////////
		// build the map of all the muon pair combinations //////////
		buildMuonPairMap( muPairMap, pmu ); /////////////////////////
		/////////////////////////////////////////////////////////////
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// get the index of the best PV /////////////////////////////////////////////////////////////////////////////////////////////////
		double cutval1 = (*m_cutFlowMapSVD)["PV"][0]; ///////////////////////////////////////////////////////////////////////////////////
		double cutval2 = (*m_cutFlowMapSVD)["PV"][1]; ///////////////////////////////////////////////////////////////////////////////////
		double cutval3 = (*m_cutFlowMapSVD)["PV"][2]; ///////////////////////////////////////////////////////////////////////////////////
		iVtx = getPVindex( (int)cutval1, (int)cutval2, cutval3, (int)vxp_n, vxp_nTracks, vxp_type, vxp_z);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////////
		// extract the indices of the best pair if there are >1 pairs
		// the selection is done for the most *massive* pair
		if(muPairMap.size()>1)
		{
			findMostMassivePair(mu_staco_charge, pmu, muPairMap, ai, bi);
		}
		if(muPairMap.size()==1)
		{
			TMapii::iterator it=muPairMap.begin();
			ai = it->first;
			bi = it->second;
		}
		////////////////////////////////////////////////////////////////
	}
	return true;
}



void combinedSelection::applySelection(TVectorP2VL& pmu, TMapsd& values2fill)
{	
	//////////////////////////////////////////////
	// double check on the setMUindices method ///
	// need at least 2 muons...///////////////////
	if(mu_staco_n<2) return; /////////////////////
	//////////////////////////////////////////////
	
	
	///////////////////////////////////
	// fill the NO CUTS items /////////
	fillBeforeCuts(); /////////////////
	///////////////////////////////////
	
	
	// fill the cut flow, stop at the relevant cut each time.
	// the cut objects don't have to be "correctly" ordered
	// since it is done by the loop on the ordered cut flow map
	passCutFlow    = true;
	passCurrentCut = true;
	counter        = 0;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////
	
		string sorderedcutname = ii->second;

		if(sorderedcutname=="oppositeCharge")
		{
			passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_charge_a, mu_charge_b) ) ? true : false;
		}

		if(sorderedcutname=="imass")
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		if(sorderedcutname=="pT")
		{
			passCurrentCut = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(sorderedcutname=="eta")
		{
			passCurrentCut = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		if(sorderedcutname=="etaTight")
		{
			passCurrentCut = ( etaTightCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		if(sorderedcutname=="cosThetaDimu")
		{
			passCurrentCut = ( cosThetaDimuCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		if(sorderedcutname=="d0")
		{
			passCurrentCut = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], d0exPVa, d0exPVb) ) ? true : false;
		}

		if(sorderedcutname=="z0")
		{
			passCurrentCut = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], z0exPVa, z0exPVb) ) ? true : false;
		}
		
		if(sorderedcutname=="PV ????????")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			int bestVertexIndex;
			passCurrentCut = ( primaryVertexCut(cutval1,cutval2,cutval3, nPVtracksPtr, nPVtypePtr, PVz0Ptr, PVz0errPtr, bestVertexIndex) ) ? true : false;
			if(iVtx != bestVertexIndex) cout << "iVtx != bestVertexIndex" << endl;
		}
		
		if(sorderedcutname=="isCombMu")
		{
			passCurrentCut = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0],isMuaComb,isMubComb) ) ? true : false;
		}
		
		/*
		if(sorderedcutname=="idHits")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( nIDhitsCut( cutval1,cutval2,cutval3,nSCThits,nPIXhits ) ) ? true : false;
		}
		*/
		
		if(sorderedcutname=="isolation40")
		{
			passCurrentCut =
			(
			pairXXisolation((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation40",mu_pTa,mu_pTb,pTcone40a,pTcone40b)
			) ? true : false;
		}
		
		if(sorderedcutname=="pTmatchingRatio")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			passCurrentCut =
			(
			pTmatchingRatioCut( cutval1,cutval2,
			me_qOp_a,me_theta_a,id_qOp_a,id_theta_a,
			me_qOp_b,me_theta_b,id_qOp_b,id_theta_b)
			) ? true : false;
		}

		if(sorderedcutname=="pTmatchingAbsDiff")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			passCurrentCut =
			(
			pTmatchingAbsDiffCut( cutval1,
			me_qOp_a,me_theta_a,id_qOp_a,id_theta_a,
			me_qOp_b,me_theta_b,id_qOp_b,id_theta_b)
			) ? true : false;
		}

		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		
		////////////////////////////////////////////////////////////////////////
		// fill the cutFlow and the allCuts items //////////////////////////////
		fillAfterCuts(passCutFlow, counter, sorderedcutname, values2fill); /////
		////////////////////////////////////////////////////////////////////////
		
	} // end for(m_cutFlowOrdered)
	
	//////////////////////////////////////////////////////
	// dump events. only if doEventDump==true and this ///
	// happens if the setEventDumper method is calle   ///
	// where this happens if the last (string) argument //
	// of initCombinedSelection is not empty "" //////////
	runEventDumper(passCutFlow, ai); /////////////////////////
	//////////////////////////////////////////////////////

	// re-initialize
	if(muPairMap.size()>0)   muPairMap.clear();
}

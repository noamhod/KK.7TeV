
/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisSkeleton.h"

analysisSkeleton::analysisSkeleton()
{
	
}

analysisSkeleton::~analysisSkeleton()
{

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


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

void analysisSkeleton::runEventDumper(bool passCutFlow, int ai)
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// write the interesting events to a flat file ///////////////////////////////////////////////
	if(passCutFlow  &&  doEventDump)
	{	
		setCurrentEventMass( current_imass );
		writeEventHeader(runnumber, lumiblock, eventnumber);
		
		writeProperty("$p_T$", current_mu_pT, current_muplus_pT);
		writeProperty("$\\eta$", current_mu_eta, current_muplus_eta);
		
		double ca = mu_staco_charge->at(ai);
		if(ca<0)
		{
			writeProperty("$\\sum{p_T^{cone20}}/p_T$", pTcone20a/mu_pTa, pTcone20b/mu_pTb);
			writeProperty("$\\sum{p_T^{cone30}}/p_T$", pTcone30a/mu_pTa, pTcone30b/mu_pTb);
			writeProperty("$\\sum{p_T^{cone40}}/p_T$", pTcone40a/mu_pTa, pTcone40b/mu_pTb);
			
			writeProperty("nSCThits", nSCThitsMua, nSCThitsMub);
			writeProperty("nPIXhits", nPIXhitsMua, nPIXhitsMub);
			writeProperty("nIDhits ", nIDhitsMua, nIDhitsMub);
		}
		else
		{
			writeProperty("$\\sum{p_T^{cone20}}/p_T$", pTcone20b/mu_pTb, pTcone20a/mu_pTa);
			writeProperty("$\\sum{p_T^{cone30}}/p_T$", pTcone30b/mu_pTb, pTcone30a/mu_pTa);
			writeProperty("$\\sum{p_T^{cone40}}/p_T$", pTcone40b/mu_pTb, pTcone40a/mu_pTa);
			
			writeProperty("nSCThits", nSCThitsMub, nSCThitsMua);
			writeProperty("nPIXhits", nPIXhitsMub, nPIXhitsMua);
			writeProperty("nIDhits ", nIDhitsMub, nIDhitsMua);
		}
		
		writeProperty("$\\hat{m}_{\\mu\\mu}$", "red", current_imass);
		writeProperty("$\\hat{p}_{\\mu^-}\\cdot\\hat{p}_{\\mu^+}$", current_cosmicCosth);
		writeProperty("$\\cos\\theta_{\\mu^-}$", current_cosTheta);
		
		writeEventFooter();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


void analysisSkeleton::fillAfterCuts(bool passCutFlow, int counter, string sorderedcutname, TMapsd& values2fill)
{
	if(passCutFlow)
	{
		//////////////////////////////////////////////////////
		// for the cut flow: /////////////////////////////////
		hmap_cutFlow_imass->operator[]("imass."+sorderedcutname)->Fill( values2fill["imass"] );
		hmap_cutFlow_pT->operator[]("pT."+sorderedcutname)->Fill( values2fill["pT"] );
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
			if(current_imass>=XMIN  &&  current_imass<=XMAX) h1_costh->Fill( current_cosTheta );
			
			h1_cosmicCosthAllCuts->Fill( current_cosmicCosth );
			h1_pT->Fill( current_mu_pT );
			h1_pT_muplus->Fill( current_muplus_pT );
			h1_eta->Fill( current_mu_eta );
			h1_eta_muplus->Fill( current_muplus_eta );
			h1_ipTdiff->Fill( current_ipTdiff );
			h1_etaSum->Fill( current_etaSum );
			h1_imass->Fill( current_imass );
			h1_imassFit->Fill( current_imass );
			
			cout << "\n$$$$$$$$$ dimuon $$$$$$$$$" << endl;
			cout << "\t im=" << current_imass << endl;
			cout << "\t pTmu=" << current_mu_pT  << endl;
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			
			// fill the xVector for the ML fit:
			fillXvec( current_imass );
		}
		///////////////////////////////////////////////////////////
	} // end if(passCutFlow)
}

void analysisSkeleton::fillBeforeCuts()
{
	// fill nocuts histograms
	h1_cosmicCosth->Fill( current_cosmicCosth );
	h1_d0exPV->Fill(d0exPVa);
	h1_d0exPV->Fill(d0exPVb);
	h1_z0exPV->Fill(z0exPVa);
	h1_z0exPV->Fill(z0exPVb);
	//X( prtD0*cos(phi) );
	//Y( prtD0*sin(phi) );
	//Z( Z0 );
	h2_xyVertex->Fill( d0exPVa*cos(phi_a), d0exPVa*sin(phi_a) );
	h2_xyVertex->Fill( d0exPVb*cos(phi_b), d0exPVb*sin(phi_b) );
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
			passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], isL1_MU6) ) ? true : false;
		}
		
		
		if(sorderedcutname=="Trigger")
		{
			string trigName = vTriggers->at(0);
			int trigVal = isTrigger(trigName);
			passCurrentCut = ( triggerCut((*m_cutFlowMapSVD)[sorderedcutname][0], trigVal, trigName) ) ? true : false;
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


bool analysisSkeleton::setMUindices(TVectorP2VL& pmu, string sRunType)
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



void analysisSkeleton::applySelection(TVectorP2VL& pmu, TMapsd& values2fill)
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
		
		if(sorderedcutname=="pT_use_qOp_and_theta")
		{
			passCurrentCut = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], me_qOp_a, me_theta_a, me_qOp_b, me_theta_b) ) ? true : false;
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
		
		if(sorderedcutname=="etaSum")
		{
			passCurrentCut = ( etaSumCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
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
		
		
		if(sorderedcutname=="idHits")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( nIDhitsCut( cutval1,cutval2,cutval3,nSCThitsMua,nPIXhitsMub ) ) ? true : false;
		}
		
		
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
	
	////////////////////////////////////////////////////////////
	// dump events. only if doEventDump==true ///
	runEventDumper(passCutFlow, ai); ///////////////////////////
	////////////////////////////////////////////////////////////

	// re-initialize
	if(muPairMap.size()>0)   muPairMap.clear();
}

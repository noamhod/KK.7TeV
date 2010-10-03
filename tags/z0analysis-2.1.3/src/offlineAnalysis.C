/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "offlineAnalysis.h"

offlineAnalysis::offlineAnalysis()
{
	initialize();
}

offlineAnalysis::offlineAnalysis(offlinePhysics* offPhys, graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, TFile* treeFile, string sLastCut2Hist)
{
	initialize();

	m_offPhys = offPhys;

	m_treeFile = treeFile;
	
	//m_offTree = new offTree( m_offPhys, m_treeFile );
	m_offTreeDigest = new offlineTreeDigest( m_offPhys, m_treeFile );

	//m_muid    = new muon_muid(  m_offPhys ); // this will also "turn on" the desired branches (virtual in the base)
	//m_mustaco = new muon_staco( m_offPhys ); // this will also  "turn on" the desired branches (virtual in the base)
	//m_dir_muon_staco = m_treeFile->mkdir("muon_staco");
	//m_mustacotree = new muon_staco_tree( m_mustaco, m_dir_muon_staco );

	m_cutFlowHandler = cutFlowHandler;
	m_cutFlowMapSVD  = m_cutFlowHandler->getCutFlowMapSVDPtr();
	m_cutFlowOrdered = m_cutFlowHandler->getCutFlowOrderedMapPtr();
	m_cutFlowTypeOrdered = m_cutFlowHandler->getCutFlowTypeOrderedMapPtr();
	m_cutFlowNumbers = m_cutFlowHandler->getCutFlowNumbersMapPtr();
	
	// cut flow has been read out already
	initSelectionCuts(m_cutFlowMapSVD, m_cutFlowOrdered, m_cutFlowTypeOrdered);

	m_graphicobjs = graphicobjs;
	
	m_fit = new fit();
	
	m_offTreeDigest = new offlineTreeDigest( m_offPhys, m_treeFile );
	
	m_sLastCut2Hist = sLastCut2Hist;
}

offlineAnalysis::~offlineAnalysis()
{

}

void offlineAnalysis::initialize()
{

}

void offlineAnalysis::finalize()
{

}

void offlineAnalysis::fitter()
{
	double yields[2];
	
	///////////////////////////////////////////////////////////////
	// Preform the fit ////////////////////////////////////////////
	m_fit->minimize( false, m_graphicobjs->h1_imassFit, yields );
	///////////////////////////////////////////////////////////////
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
	///////////////////////////////////////////
	// do not skip this for correct counting //
	m_cutFlowHandler->nAllEvents++; ///////////
	///////////////////////////////////////////

	// local variables
	TVectorP2VL	pmu;
	TMapii		muPairMap;
	
	bool passCutFlow    = true;
	bool passCurrentCut = true;
	
	int cutFlowMapSize = (int)m_cutFlowOrdered->size();
	int counter = 0;

	
	//////////////////////////////////////////////////////////////////
	// build vector of the muons TLorentzVector //////////////////////
	for(int n=0 ; n<(int)m_offPhys->mu_staco_n ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_offPhys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_offPhys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_offPhys->mu_staco_pz->at(n) );
		pmu[n]->SetE(  m_offPhys->mu_staco_E->at(n)  );
	}
	///////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////
	// build the map of all the muon pair combinations //////////
	buildMuonPairMap( muPairMap, pmu ); /////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	// preselection
	passCutFlow    = true;
	passCurrentCut = true;
	counter = 0;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore selection: //////////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="selection") continue; //////////
		///////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;

		if(sorderedcutname=="GRL")
		{
			passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], m_offPhys->isGRL) ) ? true : false;
		}

		if(sorderedcutname=="L1_MU6")
		{
			passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], m_offPhys->L1_MU6) ) ? true : false;
		}
		
		if(sorderedcutname=="hipTmuon")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			passCurrentCut = ( findHipTmuon(cutval1, cutval2,
											(int)m_offPhys->mu_staco_n,
											m_offPhys->mu_staco_pt,
											m_offPhys->mu_staco_me_qoverp,
											m_offPhys->mu_staco_me_theta) ) ? true : false;
		}
		
		if(sorderedcutname=="PV")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
											   (int)m_offPhys->vxp_n,
											   m_offPhys->vxp_nTracks,
											   m_offPhys->vxp_type,
											   m_offPhys->vxp_z) ) ? true : false;
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
	//////////////////////////////////////////////////////////
	// do not continue if didn't pass the preselection ///////
	if(!passCutFlow) return; /////////////////////////////////
	//////////////////////////////////////////////////////////
	
	
	
	////////////////////////////////////////
	// need at least 2 muons.../////////////
	// otherwise, continue /////////////////
	// the next cut which identifies as ////
	// the 1st selection cut, MUST be the //
	// opposite charge cut, otherwise the //
	// entire counting procedure will get //
	// screwed up. This is determined in  //
	// the cutFlow.cuts file ///////////////
	if(m_offPhys->mu_staco_n<2) return; ////
	////////////////////////////////////////
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// get the index of the best PV /////////////////////////////////////////////////////////////////////////////////////////////////
	double cutval1 = (*m_cutFlowMapSVD)["PV"][0]; ///////////////////////////////////////////////////////////////////////////////////
	double cutval2 = (*m_cutFlowMapSVD)["PV"][1]; ///////////////////////////////////////////////////////////////////////////////////
	double cutval3 = (*m_cutFlowMapSVD)["PV"][2]; ///////////////////////////////////////////////////////////////////////////////////
	int iVtx = getPVindex( (int)cutval1, (int)cutval2, cutval3, (int)m_offPhys->vxp_n, m_offPhys->vxp_nTracks, m_offPhys->vxp_type, m_offPhys->vxp_z);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////
	// extract the indices of the best pair if there are >1 pairs
	// the selection is done for the most *massive* pair
	int ai, bi;
	if(muPairMap.size()>1)
	{
		findMostMassivePair(m_offPhys->mu_staco_charge, pmu, muPairMap, ai, bi);
	}
	if(muPairMap.size()==1)
	{
		TMapii::iterator it=muPairMap.begin();
		ai = it->first;
		bi = it->second;
	}
	////////////////////////////////////////////////////////////////
	
	

	// calculate the necessary variables
	current_imass    = imass(pmu[ai],pmu[bi]);
	current_cosTheta = cosThetaCollinsSoper( pmu[ai], (double)m_offPhys->mu_staco_charge->at(ai),
	pmu[bi], (double)m_offPhys->mu_staco_charge->at(bi) );
	current_mu_pT     = (m_offPhys->mu_staco_charge->at(ai)<0) ? m_offPhys->mu_staco_pt->at(ai) : m_offPhys->mu_staco_pt->at(bi);
	current_muplus_pT = (m_offPhys->mu_staco_charge->at(ai)>0) ? m_offPhys->mu_staco_pt->at(ai) : m_offPhys->mu_staco_pt->at(bi);
	current_mu_eta     = (m_offPhys->mu_staco_charge->at(ai)<0) ? m_offPhys->mu_staco_eta->at(ai) : m_offPhys->mu_staco_eta->at(bi);
	current_muplus_eta = (m_offPhys->mu_staco_charge->at(ai)>0) ? m_offPhys->mu_staco_eta->at(ai) : m_offPhys->mu_staco_eta->at(bi);
	current_cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );
	current_ipTdiff = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_etaSum = current_muplus_eta + current_mu_eta;
	
	// event level
	runnumber  = m_offPhys->RunNumber;
	lumiblock  = m_offPhys->lbn;
	isL1MU6    = m_offPhys->L1_MU6;
	isEF_mu10  = m_offPhys->EF_mu10;
	isGRL      = m_offPhys->isGRL;
	
	// deprecated !!!
	d0exPVa = m_offPhys->mu_staco_d0_exPV->at(ai);
	z0exPVa = m_offPhys->mu_staco_z0_exPV->at(ai);
	d0exPVb = m_offPhys->mu_staco_d0_exPV->at(bi);
	z0exPVb = m_offPhys->mu_staco_z0_exPV->at(bi);
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	nPVtracksPtr = m_offPhys->vxp_nTracks; // number of tracks > 2
	nPVtypePtr   = m_offPhys->vxp_type;    // ==1
	PVz0Ptr      = m_offPhys->vxp_z;       // = absolute z position of primary vertex < 150mm
	PVz0errPtr   = m_offPhys->vxp_z_err;   // = error
	
	// combined muon ?
	isMuaComb  = m_offPhys->mu_staco_isCombinedMuon->at(ai);
	isMubComb  = m_offPhys->mu_staco_isCombinedMuon->at(bi);	
	
	// inner detector hits
	nSCThitsMua  = m_offPhys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
	nSCThitsMub  = m_offPhys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
	nPIXhitsMua  = m_offPhys->mu_staco_nPixHits->at(ai); // pixel hits >=1
	nPIXhitsMub  = m_offPhys->mu_staco_nPixHits->at(bi); // pixel hits >=1
	nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
	nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	me_qOp_a   = m_offPhys->mu_staco_me_qoverp->at(ai);
	id_qOp_a   = m_offPhys->mu_staco_id_qoverp->at(ai);
	me_theta_a = m_offPhys->mu_staco_me_theta->at(ai);
	id_theta_a = m_offPhys->mu_staco_id_theta->at(ai);
	me_qOp_b   = m_offPhys->mu_staco_me_qoverp->at(bi);
	id_qOp_b   = m_offPhys->mu_staco_id_qoverp->at(bi);
	me_theta_b = m_offPhys->mu_staco_me_theta->at(bi);
	id_theta_b = m_offPhys->mu_staco_id_theta->at(bi);
	
	// impact parameter
	impPrmZ0 = m_offPhys->mu_staco_z0_exPV->at(ai);
	impPrmD0 = m_offPhys->mu_staco_d0_exPV->at(ai);
	
	// isolation
	mu_pTa   = m_offPhys->mu_staco_pt->at(ai);
	mu_pTb   = m_offPhys->mu_staco_pt->at(bi);
	pTcone20a = m_offPhys->mu_staco_ptcone20->at(ai);
	pTcone20b = m_offPhys->mu_staco_ptcone20->at(bi);
	pTcone30a = m_offPhys->mu_staco_ptcone30->at(ai);
	pTcone30b = m_offPhys->mu_staco_ptcone30->at(bi);
	pTcone40a = m_offPhys->mu_staco_ptcone40->at(ai);
	pTcone40b = m_offPhys->mu_staco_ptcone40->at(bi);
	
	// charge
	mu_charge_a = m_offPhys->mu_staco_charge->at(ai);
	mu_charge_b = m_offPhys->mu_staco_charge->at(bi);
	
	
	
	// fill nocuts histograms
	m_graphicobjs->h1_cosmicCosth->Fill( current_cosmicCosth );
	m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
	m_graphicobjs->h1_d0exPV->Fill(d0exPVb);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVa);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVb);
	//X( prtD0*cos(phi) );
	//Y( prtD0*sin(phi) );
	//Z( Z0 );
	//m_graphicobjs->h2_xyVertex->Fill( d0exPVa*cos(m_offPhys->mu_staco_phi->at(ai)), d0exPVa*sin(m_offPhys->mu_staco_phi->at(ai)) );
	//m_graphicobjs->h2_xyVertex->Fill( d0exPVb*cos(m_offPhys->mu_staco_phi->at(bi)), d0exPVb*sin(m_offPhys->mu_staco_phi->at(bi)) );
	
	
	TMapsd values2fill;
	values2fill.insert( make_pair( "imass",current_imass ) );
	values2fill.insert( make_pair( "pT",   current_mu_pT ) );
	
	passCutFlow    = true;
	passCurrentCut = true;
	counter = 0;
	// fill the cut flow, stop at the relevant cut each time.
	// the cut objects don't have to be "correctly" ordered
	// since it is done by the loop on the ordered cut flow map
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; /////////
		///////////////////////////////////////////////////////////////
		
		string sorderedcutname = ii->second;

		if(sorderedcutname=="oppositeCharge")
		{
			passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_charge_a, mu_charge_b) ) ? true : false;
		}

		if(sorderedcutname=="EF_mu10")
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], isEF_mu10) ) ? true : false;
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
			if(counter==cutFlowMapSize)
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
				m_fit->fillXvec( current_imass );
			}
			///////////////////////////////////////////////////////////
		} // end if(passCutFlow)
	} // end for(m_cutFlowOrdered)
	
	// write to the digest tree only the pairs that passed the preselection
	m_offTreeDigest->fill(ai, bi, iVtx);

	// re-initialize
	if(muPairMap.size()>0) muPairMap.clear();
	if(pmu.size()>0)       pmu.clear();
}

void offlineAnalysis::write()
{
	m_treeFile->cd();
	m_offTreeDigest->write();
}

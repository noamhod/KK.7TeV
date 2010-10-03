/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysis.h"

analysis::analysis()
{
	initialize();
}

analysis::analysis(physics* phys, graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, GRLinterface* grl, TFile* treeFile)
{
	initialize();

	m_phys = phys;

	m_analysis_grl = grl;	

	m_treeFile = treeFile;

	m_offTree = new offTree( m_phys, NULL, m_treeFile ); // the NULL arg is the [mcPhysics* m_mcPhys;] variable

	m_muid    = new muon_muid(  m_phys ); // this will also "turn on" the desired branches (virtual in the base)
	m_mustaco = new muon_staco( m_phys ); // this will also  "turn on" the desired branches (virtual in the base)

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
	
}

analysis::~analysis()
{
	finalize();
}

void analysis::initialize()
{

}

void analysis::finalize()
{

}

void analysis::executeAdvanced()
{

	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_phys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mustaco->getNParticles() ; n++)
		{
			m_mustaco->setParticle(n);
			m_graphicobjs->h2_xyVertex->Fill( m_mustaco->pvVec->X(), m_mustaco->pvVec->Y() );
		}
	}
}

void analysis::executeCutFlow()
{
	bool debugmode = false;

	if(debugmode) cout << "### 0 ###" << endl;

	///////////////////////////////////////////
	// do not skip this for correct counting //
	m_cutFlowHandler->nAllEvents++; ///////////
	///////////////////////////////////////////
	
	if(debugmode) cout << "### 1 ###" << endl;
	
	///////////////////////////////////////////////////////////////////////////////////////
	// Good Run List //////////////////////////////////////////////////////////////////////
	isGRL = m_analysis_grl->m_grl.HasRunLumiBlock( m_phys->RunNumber, m_phys->lbn ); //////
	///////////////////////////////////////////////////////////////////////////////////////
	
	if(debugmode) cout << "### 2 ###" << endl;
	
	/////////////////////////////////////////
	m_offTree->fill(isGRL); /////////////////
	/////////////////////////////////////////

	if(debugmode) cout << "### 3 ###" << endl;
	
	// local variables
	TVectorP2VL	pmu;
	TMapii		muPairMap;
	
	bool passCutFlow    = true;
	bool passCurrentCut = true;
	
	int cutFlowMapSize = (int)m_cutFlowOrdered->size();
	int counter = 0;


	if(debugmode) cout << "### 4 ###" << endl;
	
	//////////////////////////////////////////////////////////////////
	// build vector of the muons TLorentzVector //////////////////////
	for(int n=0 ; n<(int)m_phys->mu_staco_n ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_phys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_phys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_phys->mu_staco_pz->at(n) );
		pmu[n]->SetE(  m_phys->mu_staco_E->at(n)  );
	}
	///////////////////////////////////////////////////////////////////

	if(debugmode) cout << "### 5 ###" << endl;
	
	/////////////////////////////////////////////////////////////
	// build the map of all the muon pair combinations //////////
	buildMuonPairMap( muPairMap, pmu ); /////////////////////////
	/////////////////////////////////////////////////////////////
	
	if(debugmode) cout << "### 6 ###" << endl;
	
	
	// preselection
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
			passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], m_phys->L1_MU6) ) ? true : false;
		}
		
		if(sorderedcutname=="hipTmuon")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			passCurrentCut = ( findHipTmuon(cutval1, cutval2,
											(int)m_phys->mu_staco_n,
											m_phys->mu_staco_pt,
											m_phys->mu_staco_me_qoverp,
											m_phys->mu_staco_me_theta) ) ? true : false;
		}
		
		if(sorderedcutname=="PV")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( findBestVertex((int)cutval1, (int)cutval2, cutval3,
											   (int)m_phys->vxp_n,
											   m_phys->vxp_nTracks,
											   m_phys->vxp_type,
											   m_phys->vxp_z) ) ? true : false;
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
	if(m_phys->mu_staco_n<2) return; ///////
	////////////////////////////////////////
	
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// get the index of the best PV /////////////////////////////////////////////////////////////////////////////////////////////////
	double cutval1 = (*m_cutFlowMapSVD)["PV"][0]; ///////////////////////////////////////////////////////////////////////////////////
	double cutval2 = (*m_cutFlowMapSVD)["PV"][1]; ///////////////////////////////////////////////////////////////////////////////////
	double cutval3 = (*m_cutFlowMapSVD)["PV"][2]; ///////////////////////////////////////////////////////////////////////////////////
	int iVtx = getPVindex( (int)cutval1, (int)cutval2, cutval3, (int)m_phys->vxp_n, m_phys->vxp_nTracks, m_phys->vxp_type, m_phys->vxp_z);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if(debugmode) cout << "### 7 ###" << endl;
	
	///////////////////////////////////////////////////////////////
	// extract the indices of the best pair if there are >1 pairs
	// the selection is done for the most *massive* pair
	int ai, bi;
	if(muPairMap.size()>1)
	{
		findMostMassivePair(m_phys->mu_staco_charge, pmu, muPairMap, ai, bi);
	}
	if(muPairMap.size()==1)
	{
		TMapii::iterator it=muPairMap.begin();
		ai = it->first;
		bi = it->second;
	}
	////////////////////////////////////////////////////////////////
	
	if(debugmode) cout << "### 8 ###" << endl;
	if(debugmode) cout << "### pmu.size()=" << pmu.size() << ",ai=" << ai << ", bi=" << bi << " ###" << endl;
	
	// calculate the necessary variables
	current_imass    = imass(pmu[ai],pmu[bi]);
	current_cosTheta = cosThetaCollinsSoper( pmu[ai], (double)m_phys->mu_staco_charge->at(ai),
	pmu[bi], (double)m_phys->mu_staco_charge->at(bi) );
	current_mu_pT    = (m_phys->mu_staco_charge->at(ai)<0) ? m_phys->mu_staco_pt->at(ai) : m_phys->mu_staco_pt->at(bi);
	current_muplus_pT    = (m_phys->mu_staco_charge->at(ai)>0) ? m_phys->mu_staco_pt->at(ai) : m_phys->mu_staco_pt->at(bi);
	current_mu_eta   = (m_phys->mu_staco_charge->at(ai)<0) ? m_phys->mu_staco_eta->at(ai) : m_phys->mu_staco_eta->at(bi);
	current_muplus_eta   = (m_phys->mu_staco_charge->at(ai)>0) ? m_phys->mu_staco_eta->at(ai) : m_phys->mu_staco_eta->at(bi);
	current_cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );
	current_ipTdiff = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_etaSum = current_muplus_eta + current_mu_eta;
	
	if(debugmode) cout << "### 9 ###" << endl;
	
	// event level
	runnumber  = m_phys->RunNumber;
	lumiblock  = m_phys->lbn;
	isL1MU6    = m_phys->L1_MU6;
	isEF_mu10  = m_phys->EF_mu10;
	
	if(debugmode) cout << "### 10 ###" << endl;
	
	// deprecated !!!
	d0exPVa = m_phys->mu_staco_d0_exPV->at(ai);
	z0exPVa = m_phys->mu_staco_z0_exPV->at(ai);
	d0exPVb = m_phys->mu_staco_d0_exPV->at(bi);
	z0exPVb = m_phys->mu_staco_z0_exPV->at(bi);
	
	if(debugmode) cout << "### 11 ###" << endl;
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	nPVtracksPtr = m_phys->vxp_nTracks; // number of tracks > 2
	nPVtypePtr   = m_phys->vxp_type;    // ==1
	PVz0Ptr      = m_phys->vxp_z;       // = absolute z position of primary vertex < 150mm
	PVz0errPtr   = m_phys->vxp_err_z;   // = error
	
	if(debugmode) cout << "### 12 ###" << endl;
	
	// combined muon ?
	isMuaComb  = m_phys->mu_staco_isCombinedMuon->at(ai);
	isMubComb  = m_phys->mu_staco_isCombinedMuon->at(bi);	
	
	if(debugmode) cout << "### 13 ###" << endl;
	
	// inner detector hits
	nSCThitsMua  = m_phys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
	nSCThitsMub  = m_phys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
	nPIXhitsMua  = m_phys->mu_staco_nPixHits->at(ai); // pixel hits >=1
	nPIXhitsMub  = m_phys->mu_staco_nPixHits->at(bi); // pixel hits >=1
	nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
	nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
	
	if(debugmode) cout << "### 14 ###" << endl;
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	me_qOp_a   = m_phys->mu_staco_me_qoverp->at(ai);
	id_qOp_a   = m_phys->mu_staco_id_qoverp->at(ai);
	me_theta_a = m_phys->mu_staco_me_theta->at(ai);
	id_theta_a = m_phys->mu_staco_id_theta->at(ai);
	me_qOp_b   = m_phys->mu_staco_me_qoverp->at(bi);
	id_qOp_b   = m_phys->mu_staco_id_qoverp->at(bi);
	me_theta_b = m_phys->mu_staco_me_theta->at(bi);
	id_theta_b = m_phys->mu_staco_id_theta->at(bi);
	
	if(debugmode) cout << "### 15 ###" << endl;
	
	// impact parameter
	impPrmZ0 = m_phys->mu_staco_z0_exPV->at(ai);
	impPrmD0 = m_phys->mu_staco_d0_exPV->at(ai);
	
	if(debugmode) cout << "### 16 ###" << endl;
	
	// isolation
	mu_pTa   = m_phys->mu_staco_pt->at(ai);
	mu_pTb   = m_phys->mu_staco_pt->at(bi);
	pTcone20a = m_phys->mu_staco_ptcone20->at(ai);
	pTcone20b = m_phys->mu_staco_ptcone20->at(bi);
	pTcone30a = m_phys->mu_staco_ptcone30->at(ai);
	pTcone30b = m_phys->mu_staco_ptcone30->at(bi);
	pTcone40a = m_phys->mu_staco_ptcone40->at(ai);
	pTcone40b = m_phys->mu_staco_ptcone40->at(bi);
	
	if(debugmode) cout << "### 17 ###" << endl;
	
	// charge
	mu_charge_a = m_phys->mu_staco_charge->at(ai);
	mu_charge_b = m_phys->mu_staco_charge->at(bi);
	
	if(debugmode) cout << "### 18 ###" << endl;
	
	
	
	// fill nocuts histograms
	m_graphicobjs->h1_cosmicCosth->Fill( current_cosmicCosth );
	m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
	m_graphicobjs->h1_d0exPV->Fill(d0exPVb);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVa);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVb);
	//X( prtD0*cos(phi) );
	//Y( prtD0*sin(phi) );
	//Z( Z0 );
	//m_graphicobjs->h2_xyVertex->Fill( d0exPVa*cos(m_phys->mu_staco_phi->at(ai)), d0exPVa*sin(m_phys->mu_staco_phi->at(ai)) );
	//m_graphicobjs->h2_xyVertex->Fill( d0exPVb*cos(m_phys->mu_staco_phi->at(bi)), d0exPVb*sin(m_phys->mu_staco_phi->at(bi)) );
	
	
	TMapsd values2fill;
	values2fill.insert( make_pair( "imass",current_imass ) );
	values2fill.insert( make_pair( "pT",   current_mu_pT ) );
	
	if(debugmode) cout << "### 19 ###" << endl;
	
	
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
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////
	
		string sorderedcutname = ii->second;

		if(sorderedcutname=="oppositeCharge")
		{
			passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_charge_a, mu_charge_b) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.1 ###" << endl;

		if(sorderedcutname=="EF_mu10")
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], isEF_mu10) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.2 ###" << endl;

		if(sorderedcutname=="imass")
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.3 ###" << endl;

		if(sorderedcutname=="pT")
		{
			passCurrentCut = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}

		if(debugmode) cout << "### 19.4 ###" << endl;
		
		if(sorderedcutname=="eta")
		{
			passCurrentCut = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.5 ###" << endl;

		if(sorderedcutname=="cosThetaDimu")
		{
			passCurrentCut = ( cosThetaDimuCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.6 ###" << endl;

		if(sorderedcutname=="d0")
		{
			passCurrentCut = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], d0exPVa, d0exPVb) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.7 ###" << endl;

		if(sorderedcutname=="z0")
		{
			passCurrentCut = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], z0exPVa, z0exPVb) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.8 ###" << endl;
		
		if(sorderedcutname=="PV ????????")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			int bestVertexIndex;
			passCurrentCut = ( primaryVertexCut(cutval1,cutval2,cutval3, nPVtracksPtr, nPVtypePtr, PVz0Ptr, PVz0errPtr, bestVertexIndex) ) ? true : false;
			if(iVtx != bestVertexIndex) cout << "iVtx != bestVertexIndex" << endl;
		}
		
		if(debugmode) cout << "### 19.9 ###" << endl;
		
		if(sorderedcutname=="isCombMu")
		{
			passCurrentCut = ( isCombMuCut((*m_cutFlowMapSVD)[sorderedcutname][0],isMuaComb,isMubComb) ) ? true : false;
		}
		
		if(debugmode) cout << "### 19.10 ###" << endl;
		
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
		
		if(debugmode) cout << "### 19.11 ###" << endl;
		
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
		
		if(debugmode) cout << "### 19.12 ###" << endl;

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
		
		if(debugmode) cout << "### 19.13 ###" << endl;

		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		if(passCutFlow)
		{
			//////////////////////////////////////////////////////
			// for the cut flow: /////////////////////////////////
			m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+sorderedcutname)->Fill( values2fill["imass"] );
			m_graphicobjs->hmap_cutFlow_pT->operator[]("pT."+sorderedcutname)->Fill( values2fill["pT"] );
			//////////////////////////////////////////////////////

			if(debugmode) cout << "### 19.20 ###" << endl;
			
			//////////////////////////////////////////////////////
			// count the numbers: ////////////////////////////////
			m_cutFlowNumbers->operator[](sorderedcutname) ++; ////
			//////////////////////////////////////////////////////

			if(debugmode) cout << "### 19.21 ###" << endl;
			
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
				
				cout << "\n$$$$$$$$$ dimuon $$$$$$$$$" << endl;
				cout << "\t im=" << current_imass << endl;
				cout << "\t pTmu=" << current_mu_pT  << endl;
				cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			}
			
			if(debugmode) cout << "### 19.22 ###" << endl;
			
			///////////////////////////////////////////////////////////
		} // end if(passCutFlow)
	} // end for(m_cutFlowOrdered)
	
	if(debugmode) cout << "### 20 ###" << endl;

	// re-initialize
	if(muPairMap.size()>0) muPairMap.clear();
	if(pmu.size()>0)       pmu.clear();
	
	if(debugmode) cout << "### 21 ###" << endl;
}

void analysis::write()
{
	m_treeFile->cd();
	m_offTree->write();
}

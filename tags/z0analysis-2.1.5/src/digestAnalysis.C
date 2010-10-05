/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "digestAnalysis.h"

digestAnalysis::digestAnalysis()
{
	initialize();
}

digestAnalysis::digestAnalysis(digestPhysics* digestPhysics, graphicObjects* graphicobjs, cutFlowHandler* cutFlowHandler, TFile* treeFile, string sLastCut2Hist)
{
	initialize();

	m_digestPhys = digestPhysics;

	m_treeFile = treeFile;

	m_cutFlowHandler = cutFlowHandler;
	m_cutFlowMapSVD  = m_cutFlowHandler->getCutFlowMapSVDPtr();
	m_cutFlowOrdered = m_cutFlowHandler->getCutFlowOrderedMapPtr();
	m_cutFlowTypeOrdered = m_cutFlowHandler->getCutFlowTypeOrderedMapPtr();
	m_cutFlowNumbers = m_cutFlowHandler->getCutFlowNumbersMapPtr();
	
	// cut flow has been read out already
	initSelectionCuts(m_cutFlowMapSVD, m_cutFlowOrdered, m_cutFlowTypeOrdered);

	m_graphicobjs = graphicobjs;
	
	m_fit = new fit();
	
	m_sLastCut2Hist = sLastCut2Hist;
}

digestAnalysis::~digestAnalysis()
{

}

void digestAnalysis::initialize()
{

}

void digestAnalysis::finalize()
{

}

void digestAnalysis::fitter()
{
	double yields[2];
	
	///////////////////////////////////////////////////////////////
	// Preform the fit ////////////////////////////////////////////
	m_fit->minimize( false, m_graphicobjs->h1_imassFit, yields );
	///////////////////////////////////////////////////////////////
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
	bool debugmode = false;

	///////////////////////////////////////////
	// do not skip this for correct counting //
	m_cutFlowHandler->nAllEvents++; ///////////
	///////////////////////////////////////////

	if(debugmode) cout << "### 0 ###" << endl;
	
	// local variables
	TVectorP2VL	pmu;
	int         iVtx = 0;
	
	if(debugmode) cout << "### 1 ###" << endl;

	//////////////////////////////////////////////////////////////////
	// build vector of the muons TLorentzVector //////////////////////
	if(mu_staco_n<=1) return; ////////////////////////////////////////
    // this needs to be looped acording to the size of the vector rather
	// than according to the value of mu_staco_n since in the digest tree
	// only the successive COUPLE is written.
	for(int n=0 ; n<(int)m_digestPhys->mu_staco_m->size() ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_digestPhys->mu_staco_px->at(n)*MeV2TeV );
		pmu[n]->SetPy( m_digestPhys->mu_staco_py->at(n)*MeV2TeV );
		pmu[n]->SetPz( m_digestPhys->mu_staco_pz->at(n)*MeV2TeV );
		pmu[n]->SetE(  m_digestPhys->mu_staco_E->at(n)*MeV2TeV );
	}
	///////////////////////////////////////////////////////////////////
	
	if(debugmode) cout << "### 2 ###" << endl;
	
	///////////////////////////////////////
	int ai=0, bi=1; ///////////////////////
	///////////////////////////////////////
	
	if(debugmode) cout << "### 3 ###" << endl;
	

	// calculate the necessary variables
	current_imass    = imass(pmu[ai],pmu[bi]);
	current_cosTheta = cosThetaCollinsSoper( pmu[ai], (double)m_digestPhys->mu_staco_charge->at(ai),
											 pmu[bi], (double)m_digestPhys->mu_staco_charge->at(bi) );
	current_mu_pT     = (m_digestPhys->mu_staco_charge->at(ai)<0) ? m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV : m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	current_muplus_pT = (m_digestPhys->mu_staco_charge->at(ai)>0) ? m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV : m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	current_mu_eta   = (m_digestPhys->mu_staco_charge->at(ai)<0) ? m_digestPhys->mu_staco_eta->at(ai) : m_digestPhys->mu_staco_eta->at(bi);
	current_muplus_eta   = (m_digestPhys->mu_staco_charge->at(ai)>0) ? m_digestPhys->mu_staco_eta->at(ai) : m_digestPhys->mu_staco_eta->at(bi);
	current_cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );
	current_ipTdiff = (current_muplus_pT!=0.  &&  current_mu_pT!=0.) ? 1./current_muplus_pT-1./current_mu_pT : -999.;
	current_etaSum = current_muplus_eta + current_mu_eta;
	
	if(debugmode) cout << "### 4 ###" << endl;
	
	// event level
	runnumber  = m_digestPhys->RunNumber;
	lumiblock  = m_digestPhys->lbn;
	isL1MU6    = m_digestPhys->L1_MU6;
	isGRL      = m_digestPhys->isGRL;
	isEF_mu10  = m_digestPhys->EF_mu10;
	
	if(debugmode) cout << "### 5 ###" << endl;
	
	// deprecated !!!
	d0exPVa = m_digestPhys->mu_staco_d0_exPV->at(ai);
	z0exPVa = m_digestPhys->mu_staco_z0_exPV->at(ai);
	d0exPVb = m_digestPhys->mu_staco_d0_exPV->at(bi);
	z0exPVb = m_digestPhys->mu_staco_z0_exPV->at(bi);
	
	if(debugmode) cout << "### 6 ###" << endl;
	
	// primary vertex:
	// at least one primary vtx passes the z selection
	nPVtracksPtr = m_digestPhys->vxp_nTracks; // number of tracks > 2
	nPVtypePtr   = m_digestPhys->vxp_type;    // ==1
	PVz0Ptr      = m_digestPhys->vxp_z;       // = absolute z position of primary vertex < 150mm
	PVz0errPtr   = m_digestPhys->vxp_z_err;   // = error
	
	if(debugmode) cout << "### 7 ###" << endl;
	
	// combined muon ?
	isMuaComb  = m_digestPhys->mu_staco_isCombinedMuon->at(ai);
	isMubComb  = m_digestPhys->mu_staco_isCombinedMuon->at(bi);	
	
	if(debugmode) cout << "### 8 ###" << endl;
	
	// inner detector hits
	nSCThitsMua  = m_digestPhys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
	nSCThitsMub  = m_digestPhys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
	nPIXhitsMua  = m_digestPhys->mu_staco_nPixHits->at(ai); // pixel hits >=1
	nPIXhitsMub  = m_digestPhys->mu_staco_nPixHits->at(bi); // pixel hits >=1
	nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
	nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
	
	if(debugmode) cout << "### 9 ###" << endl;
	
	// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
	me_qOp_a   = m_digestPhys->mu_staco_me_qoverp->at(ai)/MeV2TeV;
	id_qOp_a   = m_digestPhys->mu_staco_id_qoverp->at(ai)/MeV2TeV;
	me_theta_a = m_digestPhys->mu_staco_me_theta->at(ai);
	id_theta_a = m_digestPhys->mu_staco_id_theta->at(ai);
	me_qOp_b   = m_digestPhys->mu_staco_me_qoverp->at(bi)/MeV2TeV;
	id_qOp_b   = m_digestPhys->mu_staco_id_qoverp->at(bi)/MeV2TeV;
	me_theta_b = m_digestPhys->mu_staco_me_theta->at(bi);
	id_theta_b = m_digestPhys->mu_staco_id_theta->at(bi);
	
	if(debugmode) cout << "### 10 ###" << endl;
	
	// impact parameter
	impPrmZ0 = m_digestPhys->mu_staco_z0_exPV->at(ai);
	impPrmD0 = m_digestPhys->mu_staco_d0_exPV->at(ai);
	
	if(debugmode) cout << "### 11 ###" << endl;
	
	// isolation
	mu_pTa   = m_digestPhys->mu_staco_pt->at(ai)*MeV2TeV;
	mu_pTb   = m_digestPhys->mu_staco_pt->at(bi)*MeV2TeV;
	pTcone20a = m_digestPhys->mu_staco_ptcone20->at(ai)*MeV2TeV;
	pTcone20b = m_digestPhys->mu_staco_ptcone20->at(bi)*MeV2TeV;
	pTcone30a = m_digestPhys->mu_staco_ptcone30->at(ai)*MeV2TeV;
	pTcone30b = m_digestPhys->mu_staco_ptcone30->at(bi)*MeV2TeV;
	pTcone40a = m_digestPhys->mu_staco_ptcone40->at(ai)*MeV2TeV;
	pTcone40b = m_digestPhys->mu_staco_ptcone40->at(bi)*MeV2TeV;
	
	if(debugmode) cout << "### 12 ###" << endl;
	
	// charge
	mu_charge_a = m_digestPhys->mu_staco_charge->at(ai);
	mu_charge_b = m_digestPhys->mu_staco_charge->at(bi);
	
	if(debugmode) cout << "### 13 ###" << endl;
	
	TMapsd values2fill;
	values2fill.insert( make_pair( "imass",current_imass ) );
	values2fill.insert( make_pair( "pT",   current_mu_pT ) );
	
	if(debugmode) cout << "### 14 ###" << endl;
	
	
	
	// fill nocuts histograms
	m_graphicobjs->h1_cosmicCosth->Fill( current_cosmicCosth );
	m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
	m_graphicobjs->h1_d0exPV->Fill(d0exPVb);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVa);
	m_graphicobjs->h1_z0exPV->Fill(z0exPVb);
	//X( prtD0*cos(phi) );
	//Y( prtD0*sin(phi) );
	//Z( Z0 );
	m_graphicobjs->h2_xyVertex->Fill( d0exPVa*cos(m_digestPhys->mu_staco_phi->at(ai)), d0exPVa*sin(m_digestPhys->mu_staco_phi->at(ai)) );
	m_graphicobjs->h2_xyVertex->Fill( d0exPVb*cos(m_digestPhys->mu_staco_phi->at(bi)), d0exPVb*sin(m_digestPhys->mu_staco_phi->at(bi)) );
	
	
	bool passCutFlow    = true;
	bool passCurrentCut = true;
	// fill the cut flow, stop at the relevant cut each time.
	// the cut objects don't have to be "correctly" ordered
	// since it is done by the loop on the ordered cut flow map
	int cutFlowMapSize = (int)m_cutFlowOrdered->size();
	int counter = 0;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		counter++;
		
		double num = ii->first;
		///////////////////////////////////////////////////////////////
		// ignore preselection: ///////////////////////////////////////
		if(m_cutFlowTypeOrdered->operator[](num)=="preselection") continue; ///////
		///////////////////////////////////////////////////////////////
	
		string sorderedcutname = ii->second;

		if(debugmode) cout << "### 15 ###" << endl;
		
		if(sorderedcutname=="oppositeCharge")
		{
			passCurrentCut = ( oppositeChargeCut((*m_cutFlowMapSVD)[sorderedcutname][0], mu_charge_a, mu_charge_b) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.1 ###" << endl;

		if(sorderedcutname=="EF_mu10")
		{
			passCurrentCut = ( isEF_muXCut((*m_cutFlowMapSVD)[sorderedcutname][0], isEF_mu10) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.3 ###" << endl;

		if(sorderedcutname=="imass")
		{
			passCurrentCut = ( imassCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.4 ###" << endl;

		if(sorderedcutname=="pT")
		{
			passCurrentCut = ( pTCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.5 ###" << endl;

		if(sorderedcutname=="eta")
		{
			passCurrentCut = ( etaCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.6 ###" << endl;

		if(sorderedcutname=="cosThetaDimu")
		{
			passCurrentCut = ( cosThetaDimuCut((*m_cutFlowMapSVD)[sorderedcutname][0], pmu[ai], pmu[bi]) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.7 ###" << endl;

		if(sorderedcutname=="d0")
		{
			passCurrentCut = ( d0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], d0exPVa, d0exPVb) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.8 ###" << endl;

		if(sorderedcutname=="z0")
		{
			passCurrentCut = ( z0Cut((*m_cutFlowMapSVD)[sorderedcutname][0], z0exPVa, z0exPVb) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.9 ###" << endl;
		
		if(sorderedcutname=="PV ???????")
		{
			double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
			double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
			double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
			passCurrentCut = ( primaryVertexCut(cutval1,cutval2,cutval3, nPVtracksPtr, nPVtypePtr, PVz0Ptr, PVz0errPtr, iVtx) ) ? true : false;
		}
		
		if(debugmode) cout << "### 15.10 ###" << endl;
		
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
		
		if(debugmode) cout << "### 15.11 ###" << endl;
		
		if(sorderedcutname=="isolation40")
		{
			passCurrentCut =
			(
			pairXXisolation((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation40",mu_pTa,mu_pTb,pTcone40a,pTcone40b)
			) ? true : false;
		}
		
		if(debugmode) cout << "### 15.12 ###" << endl;
		
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
		
		if(debugmode) cout << "### 15.13 ###" << endl;

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
		
		if(debugmode) cout << "### 15.14 ###" << endl;

		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		if(passCutFlow)
		{
			//////////////////////////////////////////////////////
			// for the cut flow: /////////////////////////////////
			m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+sorderedcutname)->Fill( values2fill["imass"] );
			m_graphicobjs->hmap_cutFlow_pT->operator[]("pT."+sorderedcutname)->Fill( values2fill["pT"] );
			//////////////////////////////////////////////////////

			if(debugmode) cout << "### 15.15 ###" << endl;
			
			//////////////////////////////////////////////////////
			// count the numbers: ////////////////////////////////
			m_cutFlowNumbers->operator[](sorderedcutname) ++; ////
			//////////////////////////////////////////////////////

			if(debugmode) cout << "### 15.16 ###" << endl;
			
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
				
				if(debugmode) cout << "### 15.17 ###" << endl;
				
				//cout << "\n$$$$$$$$$ dimuon $$$$$$$$$" << endl;
				//cout << "\t im=" << current_imass << endl;
				//cout << "\t pTmu=" << current_mu_pT  << endl;
				//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
				
				// fill the xVector for the ML fit:
				m_fit->fillXvec( current_imass );
				
				if(debugmode) cout << "### 15.18 ###" << endl;
			}
			///////////////////////////////////////////////////////////
			
			if(debugmode) cout << "### 15.19 ###" << endl;
			
		} // end if(passCutFlow)
		
		if(debugmode) cout << "### 15.20 ###" << endl;
		
	} // end for(m_cutFlowOrdered)
	
	if(debugmode) cout << "### 16 ###" << endl;

	// re-initialize
	if(pmu.size()>0)       pmu.clear();
	
	if(debugmode) cout << "### 17 ###" << endl;
}

void digestAnalysis::write()
{
	//m_treeFile->cd();
	//m_offTreeDigest->write();
}

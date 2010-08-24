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

	m_offlineTree = new offlineTree(m_phys, m_treeFile);

	m_muid    = new muon_muid(  m_phys ); // this will also "turn on" the desired branches (virtual in the base)
	m_mustaco = new muon_staco( m_phys ); // this will also  "turn on" the desired branches (virtual in the base)

	//m_dir_muon_staco = m_treeFile->mkdir("muon_staco");
	//m_mustacotree = new muon_staco_tree( m_mustaco, m_dir_muon_staco );

	m_cutFlowHandler = cutFlowHandler;
	m_cutFlowMapSVD  = m_cutFlowHandler->getCutFlowMapSVDPtr();
	m_cutFlowOrdered = m_cutFlowHandler->getCutFlowOrderedMapPtr();
	m_cutFlowNumbers = m_cutFlowHandler->getCutFlowNumbersMapPtr();
	
	// cut flow has been read out already
	initSelectionCuts(m_cutFlowMapSVD, m_cutFlowOrdered);

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

void analysis::fillCutFlow(string sCurrentCutName, TMapsd& values2fill)
{
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+scutname)->Fill( values2fill["imass"] );
		m_graphicobjs->hmap_cutFlow_pT->operator[]("pT."+scutname)->Fill(       values2fill["pT"]    );
		if(scutname==sCurrentCutName) break;
	}
}

void analysis::executeTree(bool isendofrun)
{
	if(isendofrun) cout << "--- !!! END OF RUN !!! ---" << endl;
	
	b_isGRL = m_analysis_grl->m_grl.HasRunLumiBlock( m_phys->RunNumber, m_phys->lbn );
	m_offlineTree->fill( b_isGRL );
}

void analysis::executeBasic()
{
	// local variables
	TMapii      mupairMap;
	TVectorP2VL pmu;

	double im;
	double pTa;
	double pTb;
	double etaa;
	double etab;
	double costh;
	double d0exPVa;
	double z0exPVa;
	double d0exPVb;
	double z0exPVb;
	double cosmicCosth;

	// build vector of the muons TLorentzVector
	for(int n=0 ; n<(int)m_phys->mu_staco_n ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_phys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_phys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_phys->mu_staco_pz->at(n) );
		pmu[n]->SetE( m_phys->mu_staco_E->at(n) );
	}

	// build the map of the good muon pairs	
	for(int n=0 ; n<(int)pmu.size() ; n++)
	{
		for(int m=0 ; m<(int)pmu.size() ; m++)
		{
			// dont pair with itself
			if( m==n ) continue;

			// remove overlaps
			if( removeOverlaps(mupairMap, n, m) ) continue;

			// now can insert dimuon into the index map (all the final selection criteria)
			b_isGRL = m_analysis_grl->m_grl.HasRunLumiBlock( m_phys->RunNumber, m_phys->lbn );
			if( b_isGRL == 1 ) // this is a cut and not overlap removal
			{
				if( m_phys->L1_MU6 == 1 ) // this is also a cut and not overlap removal
				{
					buildMuonPairMap( mupairMap,
									  pmu[n], m_phys->mu_staco_charge->at(n), m_phys->mu_staco_d0_exPV->at(n), m_phys->mu_staco_z0_exPV->at(n), n,
									  pmu[m], m_phys->mu_staco_charge->at(m), m_phys->mu_staco_d0_exPV->at(m), m_phys->mu_staco_z0_exPV->at(m), m );
				}
			}

			// check before cuts
			if(m_phys->mu_staco_charge->at(n) * m_phys->mu_staco_charge->at(m)<0.)
			{
				cosmicCosth = cosThetaDimu( pmu[n], pmu[m] );
				m_graphicobjs->h1_cosmicCosth->Fill( cosmicCosth );
				
				d0exPVa = m_phys->mu_staco_d0_exPV->at(n);
				d0exPVb = m_phys->mu_staco_d0_exPV->at(m);
				m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
				m_graphicobjs->h1_d0exPV->Fill(d0exPVb);

				z0exPVa = m_phys->mu_staco_z0_exPV->at(n);
				z0exPVb = m_phys->mu_staco_z0_exPV->at(m);
				m_graphicobjs->h1_z0exPV->Fill(z0exPVa);
				m_graphicobjs->h1_z0exPV->Fill(z0exPVb);
			}
		}
	}

	// get the pmuon pairs from the dimuon good pairs map
	if(mupairMap.size()>0)
	{
		for(TMapii::iterator it=mupairMap.begin() ; it!=mupairMap.end() ; ++it)
		{
			int ai = it->first;
			int bi = it->second;
			
			im = imass( pmu[ai], pmu[bi] );
			pTa = pT( pmu[ai] );
			pTb = pT( pmu[bi] );
			etaa = eta( pmu[ai] );	
			etab = eta( pmu[bi] );
			costh = cosThetaCollinsSoper( 	pmu[ai], (double)m_phys->mu_staco_charge->at(ai),
			pmu[bi], (double)m_phys->mu_staco_charge->at(bi) );
			d0exPVa = m_phys->mu_staco_d0_exPV->at(ai);
			z0exPVa = m_phys->mu_staco_z0_exPV->at(ai);
			d0exPVb = m_phys->mu_staco_d0_exPV->at(bi);
			z0exPVb = m_phys->mu_staco_z0_exPV->at(bi);
			//cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );

			cout << "$$$$$$$$$ dimuon $$$$$$$$$" << endl;
			cout << "\t im=" << im << endl;
			cout << "\t pTa=" << pTa  << endl;
			cout << "\t pTb=" << pTb  << endl;
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;

			// fill the histos
			if( m_phys->mu_staco_charge->at(ai)<0. )
			{
				m_graphicobjs->h1_pT->Fill( pTa );
				m_graphicobjs->h1_eta->Fill( etaa );
			}
			else
			{
				m_graphicobjs->h1_pT->Fill( pTb );
				m_graphicobjs->h1_eta->Fill( etab );
			}
			
			m_graphicobjs->h1_imass->Fill( im );
			m_graphicobjs->h1_costh->Fill( costh );
		}
	}

	// re-initialize
	if(mupairMap.size()>0)    mupairMap.clear();
	if(pmu.size()>0)          pmu.clear();
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
	/////////////////////////////////////////
	m_cutFlowHandler->nAllEvents++; /////////
	/////////////////////////////////////////

	// local variables
	TMapii      allmupairMap;
	TVectorP2VL pmu;

	// build vector of the muons TLorentzVector
	for(int n=0 ; n<(int)m_phys->mu_staco_n ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_phys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_phys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_phys->mu_staco_pz->at(n) );
		pmu[n]->SetE(  m_phys->mu_staco_E->at(n)  );
	}

	// build the map of the good muon pairs 
	if(pmu.size()>1)
	{               
		for(int n=0 ; n<(int)pmu.size() ; n++)
		{               
			for(int m=0 ; m<(int)pmu.size() ; m++)
			{
				// dont pair with itself
				if( m==n ) continue;

				// remove overlaps
				if( removeOverlaps(allmupairMap, n, m) ) continue;
				// now can insert all dimuons into the index map (only opposite charge requirement)
				buildMuonPairMap( allmupairMap,
				(double)m_phys->mu_staco_charge->at(n), n,
				(double)m_phys->mu_staco_charge->at(m), m );
			}
		}
	}

	// get the pmuon pairs from the all pairs map
	if(allmupairMap.size()>0)
	{
		for(TMapii::iterator it=allmupairMap.begin() ; it!=allmupairMap.end() ; ++it)
		{
			int ai = it->first;
			int bi = it->second;

			//-----------------------------
			// event level
			int runnumber  = m_phys->RunNumber;
			int lumiblock  = m_phys->lbn;
			int isGRL      = m_analysis_grl->m_grl.HasRunLumiBlock( runnumber, lumiblock );
			int isL1MU6    = m_phys->L1_MU6;
			
			// calculate the necessary variables
			double current_imass       = imass(pmu[ai],pmu[bi]);
			double current_mu_pT       = (m_phys->mu_staco_charge->at(ai)<0.)?pT(pmu[ai]):pT(pmu[bi]);
			double current_mu_eta      = (m_phys->mu_staco_charge->at(ai)<0.)?eta(pmu[ai]):eta(pmu[bi]);
			double current_mu_cosTheta = cosThetaCollinsSoper( 	pmu[ai], (double)m_phys->mu_staco_charge->at(ai),
																pmu[bi], (double)m_phys->mu_staco_charge->at(bi) );
			
			// deprecated !!!
			double d0exPVa = m_phys->mu_staco_d0_exPV->at(ai);
			double z0exPVa = m_phys->mu_staco_z0_exPV->at(ai);
			double d0exPVb = m_phys->mu_staco_d0_exPV->at(bi);
			double z0exPVb = m_phys->mu_staco_z0_exPV->at(bi);
			
			// primary vertex:
			// at least one primary vtx passes the z selection
			vector<int>*   nPVtracksPtr = m_phys->vxp_nTracks; // number of tracks > 2
			vector<int>*   nPVtypePtr   = m_phys->vxp_type;    // ==1
			vector<float>* PVz0Ptr      = m_phys->vxp_z;       // = absolute z position of primary vertex < 150mm
			vector<float>* PVz0errPtr   = m_phys->vxp_err_z;   // = error
			
			// combined muon ?
			int isMuaComb  = m_phys->mu_staco_isCombinedMuon->at(ai);
			int isMubComb  = m_phys->mu_staco_isCombinedMuon->at(bi);
			
			// inner detector hits
			int nSCThitsMua  = m_phys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
			int nSCThitsMub  = m_phys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
			int nPIXhitsMua  = m_phys->mu_staco_nPixHits->at(ai); // pixel hits >=1
			int nPIXhitsMub  = m_phys->mu_staco_nPixHits->at(bi); // pixel hits >=1
			int nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
			int nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
					
			// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
			double me_qOp_a   = m_phys->mu_staco_me_qoverp->at(ai);
			double id_qOp_a   = m_phys->mu_staco_id_qoverp->at(ai);
			double me_theta_a = m_phys->mu_staco_me_theta->at(ai);
			double id_theta_a = m_phys->mu_staco_id_theta->at(ai);
			double me_qOp_b   = m_phys->mu_staco_me_qoverp->at(bi);
			double id_qOp_b   = m_phys->mu_staco_id_qoverp->at(bi);
			double me_theta_b = m_phys->mu_staco_me_theta->at(bi);
			double id_theta_b = m_phys->mu_staco_id_theta->at(bi);
			
			/*
			// impact parameter
			double impPrmZ0 = m_phys->mu_staco_z0_exPV->at(ai);
			double impPrmD0 = m_phys->mu_staco_d0_exPV->at(ai);
			*/
			
			// isolation
			double mu_pTa   = m_phys->mu_staco_pt->at(ai);
			double mu_pTb   = m_phys->mu_staco_pt->at(bi);
			double pTcone20a = m_phys->mu_staco_ptcone20->at(ai);
			double pTcone20b = m_phys->mu_staco_ptcone20->at(bi);
			double pTcone30a = m_phys->mu_staco_ptcone30->at(ai);
			double pTcone30b = m_phys->mu_staco_ptcone30->at(bi);
			double pTcone40a = m_phys->mu_staco_ptcone40->at(ai);
			double pTcone40b = m_phys->mu_staco_ptcone40->at(bi);

			// calculate the necessary variables to be filled
			TMapsd values2fill;
			values2fill.insert( make_pair("imass",current_imass) );
			values2fill.insert( make_pair("pT",current_mu_pT) );

			
			bool passCutFlow    = true;
			bool passCurrentCut = true;
			// fill the cut flow, stop at the relevant cut each time.
			// the cut objects don't have to be "correctly" ordered
			// since it is done by the loop on the ordered cut flow map
			
			int cutFlowSize  = (int)m_cutFlowOrdered->size();
			int cutFlowCount = 0;
			for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
			{
				cutFlowCount++;
				
				string sorderedcutname = ii->second;

				if(sorderedcutname=="oppositeCharcge")
				{
					passCurrentCut = (true) ? true : false;
				}

				if(sorderedcutname=="GRL")
				{
					passCurrentCut = ( isGRLCut((*m_cutFlowMapSVD)[sorderedcutname][0], isGRL) ) ? true : false;
				}

				if(sorderedcutname=="L1_MU6")
				{
					passCurrentCut = ( isL1_MU6Cut((*m_cutFlowMapSVD)[sorderedcutname][0], isL1MU6) ) ? true : false;
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
				
				if(sorderedcutname=="PV")
				{
					double cutval1 = (*m_cutFlowMapSVD)[sorderedcutname][0];
					double cutval2 = (*m_cutFlowMapSVD)[sorderedcutname][1];
					double cutval3 = (*m_cutFlowMapSVD)[sorderedcutname][2];
					passCurrentCut = ( primaryVertexCut(cutval1,cutval2,cutval3, nPVtracksPtr, nPVtypePtr, PVz0Ptr, PVz0errPtr) ) ? true : false;
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
					if(passCutFlow)
					{
						cout << "nSCThits=" << nSCThits << ", nPIXhits=" << nPIXhits << ", nIDhits=" << nSCThits+nPIXhits << endl;
					}
					passCurrentCut = ( nIDhitsCut( cutval1,cutval2,cutval3,nSCThits,nPIXhits ) ) ? true : false;
				}
				*/
				
				if(sorderedcutname=="isolation30")
				{
					passCurrentCut =
					(
						pairXXisolation((*m_cutFlowMapSVD)[sorderedcutname][0],"isolation30",mu_pTa,mu_pTb,pTcone30a,pTcone30b)
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

				// decide
				passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
				
				// do some stuff
				if(passCutFlow)
				{
					//////////////////////////////////////////////////////
					// for the cut flow: /////////////////////////////////
					// stop at this(sorderedcutname) cut /////////////////
					fillCutFlow(sorderedcutname, values2fill); ///////////
					//////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////
					// count the numbers: ////////////////////////////////////////////////
					if(passCutFlow) m_cutFlowNumbers->operator[](sorderedcutname) ++; ////
					//////////////////////////////////////////////////////////////////////
					
					////////////////////////////////////////////////////////////////////
					if(cutFlowCount==cutFlowSize) ///////////////////////////////
					{
						// for the final histograms:
						// i.e., not the curFlow histos
						m_graphicobjs->h1_eta->Fill( current_mu_eta );
						m_graphicobjs->h1_costh->Fill( current_mu_cosTheta );
						m_graphicobjs->h1_pT->Fill( current_mu_pT );
						m_graphicobjs->h1_imass->Fill( current_imass );
					
						cout << "$$$$$$$$$ dimuon $$$$$$$$$" << endl;
						cout << "\t im=" << current_imass << endl;
						cout << "\t pTmu=" << current_mu_pT  << endl;
						cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
					}
					/////////////////////////////////////////////////////////////////////
				} // end if(passCutFlow)
			} // end for(m_cutFlowOrdered)
		} // for(allmupairMap)
	} // end if(allmupairMap.size()>0)
	// re-initialize
	if(allmupairMap.size()>0) allmupairMap.clear();
	if(pmu.size()>0)          pmu.clear();
}

void analysis::write()
{
	m_treeFile->cd();
	m_offlineTree->write();
	//m_treeFile->Close();
}

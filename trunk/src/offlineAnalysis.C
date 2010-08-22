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

offlineAnalysis::offlineAnalysis(offlinePhysics* offPhys, graphicObjects* graphicobjs, TFile* treeFile, cutFlowHandler* cutFlowHandler, string sLastCut2Hist)
{
	initialize();

	m_offPhys = offPhys;
	
	m_treeFile = treeFile;

	/*
	m_muid    = new muon_muid(  m_offPhys ); // this will also "turn on" the desired branches (virtual in the base)
	m_mu_staco = new muon_staco( m_offPhys ); // this will also  "turn on" the desired branches (virtual in the base)
	*/

	//m_cutFlowMap         = new TMapsd();
	//m_cutFlowMapSVD	 = new TMapsvd();
	//m_cutFlowOrdered = new TMapds();
	//m_cutFlowNumbers = new TMapsi();
	
	m_cutFlowHandler = cutFlowHandler;
	m_cutFlowMapSVD  = m_cutFlowHandler->getCutFlowMapSVDPtr();
	m_cutFlowOrdered = m_cutFlowHandler-> getCutFlowOrderedMapPtr();
	m_cutFlowNumbers = m_cutFlowHandler->getCutFlowNumbersMapPtr();
	
	m_graphicobjs = graphicobjs;

	m_fit = new fit();
	
	m_offTreeDigest = new offlineTreeDigest( m_offPhys, m_treeFile );
	
	m_sLastCut2Hist = sLastCut2Hist;
	
	// cut flow has been read out already
	initSelectionCuts(m_cutFlowMapSVD, m_cutFlowOrdered);
	//m_offTreeDigest->setBranches();

	m_bOldD3PDwarning = false;
	m_nPrevRunWithWarning = 0;
}

/*
void offlineAnalysis::readCutFlow(string sCutFlowFilePath)
{
	fstream file;
	file.open( sCutFlowFilePath.c_str() );

	string sLine = "";
	string skey  = "";
	double dval  = 0.;
	double dnum  = 0.;

	vector<string> orderedVec;

	int nLinesRead = 0;

	if (!file)
	{
		cerr << "Unable to open file: " << sCutFlowFilePath << endl;
		exit(1);   // call system to stop
	}

	while(!file.eof())
	{
		getline(file,sLine);

		if(sLine == "") continue;
		if(sLine.substr(0,1) == "#")    continue;

		// parse the line (ownership utilitis):
		parseKeyValLine(sLine);

		// get the key = cut name (ownership utilitis):
		skey = getKey();

		// get the 1st val = cut value:
		dval = getVal(0);

		// get the 2nd val = cut number:
		dnum = getVal(1);

		//for(int i=0 ; i<(int)getNVals() ; i++) { dval = getVal(i); }

		nLinesRead++;

		if(b_print) { cout << "key=" << skey << "\tval=" << dval << "\tdnum=" << dnum << endl; }

		// pair the map
		m_cutFlowMap->insert( make_pair(skey,dval) );
		m_cutFlowOrdered->insert( make_pair(dnum,skey) );
		m_cutFlowNumbers->insert( make_pair(skey,0) );
	}
	cout << "\nread " << nLinesRead << " lines from " << sCutFlowFilePath << endl;

	// ownership: selection class:
	initSelectionCuts(m_cutFlowMap, m_cutFlowOrdered);
	
	m_offTreeDigest->setBranches(m_cutFlowOrdered);
	
	file.close();
}
*/


/*
TMapsd* offlineAnalysis::getCutFlowMapPtr()
{
	return m_cutFlowMap;
}

TMapds* offlineAnalysis::getCutFlowOrderedPtr()
{
	return m_cutFlowOrdered;
}
*/
offlineAnalysis::~offlineAnalysis()
{
	finalize();
}

void offlineAnalysis::initialize()
{
	//nAllEvents = 0;
}

void offlineAnalysis::finalize()
{
	
}

void offlineAnalysis::fitter()
{
	string lastCutName = m_sLastCut2Hist;

	// clone the last wanted histogram to preform the fit on:
	m_graphicobjs->h1_imassFinal = (TH1D*)m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+lastCutName)->Clone("imassFinal");
	double yields[2];
	
	///////////////////////////////////////////////////////////////
	// Preform the fit ////////////////////////////////////////////
	m_fit->minimize( false, m_graphicobjs->h1_imassFinal, yields );
	///////////////////////////////////////////////////////////////
					
	cout << "\nyields[0] = " <<  yields[0] << endl;
	cout << "yields[1] = " <<  yields[1] << "\n" << endl;
	
	m_fGuess  = (TF1*)m_fit->m_fGuess->Clone();
	m_fFitted = (TF1*)m_fit->m_fFitted->Clone();
}

/*
void offlineAnalysis::printCutFlowNumbers(Long64_t chainEntries)
{
	cout << "+------------------------------------------------" << endl;
	cout << "|             print cut flow numbers             " << endl;
	cout << "|................................................" << endl;
	cout << "|    all events in chain, " << chainEntries << endl;
	cout << "|    all processed events, " << nAllEvents << endl;
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		cout << "|    events remaining after " << scutname << " cut, " << m_cutFlowNumbers->operator[](scutname) << endl;
	}
	cout << "+------------------------------------------------" << endl;
}
*/

void offlineAnalysis::fillCutFlow(string sCurrentCutName, TMapsd& values2fill)
{
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+scutname)->Fill( values2fill["imass"] );
		m_graphicobjs->hmap_cutFlow_pT->operator[]("pT."+scutname)->Fill(       values2fill["pT"]    );
		if(scutname==sCurrentCutName) break;
	}
}

void offlineAnalysis::executeBasic()
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
	for(int n=0 ; n<(int)m_offPhys->mu_staco_m->size() ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_offPhys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_offPhys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_offPhys->mu_staco_pz->at(n) );
		pmu[n]->SetE( m_offPhys->mu_staco_E->at(n) );
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
			if( m_offPhys->isGRL ) // this is a cut and not overlap removal
			{
				if( m_offPhys->L1_MU6 ) // this is also a cut and not overlap removal
				{
					buildMuonPairMap( mupairMap,
					pmu[n], m_offPhys->mu_staco_charge->at(n), m_offPhys->mu_staco_d0_exPV->at(n), m_offPhys->mu_staco_z0_exPV->at(n), n,
					pmu[m], m_offPhys->mu_staco_charge->at(m), m_offPhys->mu_staco_d0_exPV->at(m), m_offPhys->mu_staco_z0_exPV->at(m), m );
				}
			}

			// check before cuts
			if(m_offPhys->mu_staco_charge->at(n) * m_offPhys->mu_staco_charge->at(m)<0.)
			{
				cosmicCosth = cosThetaDimu( pmu[n], pmu[m] );
				m_graphicobjs->h1_cosmicCosth->Fill( cosmicCosth );
				
				d0exPVa = m_offPhys->mu_staco_d0_exPV->at(n);
				d0exPVb = m_offPhys->mu_staco_d0_exPV->at(m);
				m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
				m_graphicobjs->h1_d0exPV->Fill(d0exPVb);

				z0exPVa = m_offPhys->mu_staco_z0_exPV->at(n);
				z0exPVb = m_offPhys->mu_staco_z0_exPV->at(m);
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
			costh = cosThetaCollinsSoper( 	pmu[ai], (double)m_offPhys->mu_staco_charge->at(ai),
			pmu[bi], (double)m_offPhys->mu_staco_charge->at(bi) );
			d0exPVa = m_offPhys->mu_staco_d0_exPV->at(ai);
			z0exPVa = m_offPhys->mu_staco_z0_exPV->at(ai);
			d0exPVb = m_offPhys->mu_staco_d0_exPV->at(bi);
			z0exPVb = m_offPhys->mu_staco_z0_exPV->at(bi);
			//cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );

			cout << "$$$$$$$$$ dimuon $$$$$$$$$" << endl;
			cout << "\t im=" << im << endl;
			cout << "\t pTa=" << pTa  << endl;
			cout << "\t pTb=" << pTb  << endl;
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			
			// fill the histos
			if( m_offPhys->mu_staco_charge->at(ai)<0. )
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

/*
void offlineAnalysis::executeAdvanced()
{

	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_offPhys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mu_staco->getNParticles() ; n++)
		{
			m_mu_staco->setParticle(n);
			m_graphicobjs->h2_xyVertex->Fill( m_mu_staco->pvVec->X(), m_mu_staco->pvVec->Y() );
		}
	}
}
*/

bool offlineAnalysis::isD3PDreconOld()
{

	/////////////////////////////////////////////////////////////////////////////
	// the old "recon" D3PDs haven't got the mu_staco_me_qoverp branch //////////
	// it is called mu_staco_msextrap_qoverp whereas, the new ones, have it. ////
	if((TBranch*)m_offPhys->fChain->GetBranch("mu_staco_me_qoverp")==NULL)
	{
		cout << "mu_staco_me_qoverp == NULL" << endl;
		return true;
	}
	else // the branch exists but it is empty:
	{
		if(m_offPhys->mu_staco_me_qoverp->size()==0)
		{
			if(m_nPrevRunWithWarning != m_offPhys->RunNumber)
			{
				m_nPrevRunWithWarning = m_offPhys->RunNumber;
				m_bOldD3PDwarning     = false;
			}
			if(!m_bOldD3PDwarning)
			{
				cout << "WARNING:  in run " << m_offPhys->RunNumber  << " ::" << endl;
				cout << "          mu_staco_me_qoverp->size()==0." << endl;
				cout << "          probably and old recon D3PD where this" << endl;
				cout << "          branch is called mu_staco_msextrap_qoverp" << endl;
				m_bOldD3PDwarning = true;
			}
			return true;
		}
	}
	
	return false;
	
}

void offlineAnalysis::executeCutFlow()
{
	/////////////////////////////////////////
	m_cutFlowHandler->nAllEvents++; /////////
	/////////////////////////////////////////

	// local variables
	TMapii      allmupairMap;
	TVectorP2VL pmu;
	
	TMapsb cutFlowDecision;
	TMapsd kinematicVariables;

	///////////////////////////////////////////////////
	m_offTreeDigest->reset(); /////////////////////////
	///////////////////////////////////////////////////

	// build vector of the muons TLorentzVector
	for(int n=0 ; n<(int)m_offPhys->mu_staco_m->size() ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_offPhys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_offPhys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_offPhys->mu_staco_pz->at(n) );
		pmu[n]->SetE(  m_offPhys->mu_staco_E->at(n)  );
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
				(double)m_offPhys->mu_staco_charge->at(n), n,
				(double)m_offPhys->mu_staco_charge->at(m), m );
			}
		}
	}

	// get the pmuon pairs from the all pairs map
	if(allmupairMap.size()>0)
	{
		if(cutFlowDecision.size()>0)    cutFlowDecision.clear();
		if(kinematicVariables.size()>0) kinematicVariables.clear();
		
		for(TMapii::iterator it=allmupairMap.begin() ; it!=allmupairMap.end() ; ++it)
		{
			if( isD3PDreconOld() ) break;
			
			int ai = it->first;
			int bi = it->second;

			//-----------------------------
			// fill the cut flow histograms:

			// calculate the necessary variables
			double current_imass       = imass(pmu[ai],pmu[bi]);
			double current_mu_pT       = (m_offPhys->mu_staco_charge->at(ai)<0.)?pT(pmu[ai]):pT(pmu[bi]);
			double current_mu_eta      = (m_offPhys->mu_staco_charge->at(ai)<0.)?eta(pmu[ai]):eta(pmu[bi]);
			double current_mu_cosTheta = cosThetaCollinsSoper( 	pmu[ai], (double)m_offPhys->mu_staco_charge->at(ai),
																pmu[bi], (double)m_offPhys->mu_staco_charge->at(bi) );
			
			// event level
			int isGRL      = m_offPhys->isGRL;
			int isL1MU6    = m_offPhys->L1_MU6;
			
			// deprecated !!!
			double d0exPVa = m_offPhys->mu_staco_d0_exPV->at(ai);
			double z0exPVa = m_offPhys->mu_staco_z0_exPV->at(ai);
			double d0exPVb = m_offPhys->mu_staco_d0_exPV->at(bi);
			double z0exPVb = m_offPhys->mu_staco_z0_exPV->at(bi);
			
			
			// primary vertex:
			// at least one primary vtx passes the z selection
			vector<int>*   nPVtracksPtr = m_offPhys->vxp_nTracks; // number of tracks > 2
			vector<int>*   nPVtypePtr   = m_offPhys->vxp_type;    // ==1
			vector<float>* PVz0Ptr      = m_offPhys->vxp_z;       // = absolute z position of primary vertex < 150mm
			vector<float>* PVz0errPtr   = m_offPhys->vxp_err_z;   // = error
			
			// combined muon ?
			int isMuaComb  = m_offPhys->mu_staco_isCombinedMuon->at(ai);
			int isMubComb  = m_offPhys->mu_staco_isCombinedMuon->at(bi);
			
			
			// inner detector hits
			int nSCThitsMua  = m_offPhys->mu_staco_nSCTHits->at(ai); //  SCT hits >=4
			int nSCThitsMub  = m_offPhys->mu_staco_nSCTHits->at(bi); //  SCT hits >=4
			int nPIXhitsMua  = m_offPhys->mu_staco_nPixHits->at(ai); // pixel hits >=1
			int nPIXhitsMub  = m_offPhys->mu_staco_nPixHits->at(bi); // pixel hits >=1
			int nIDhitsMua   = nSCThitsMua+nPIXhitsMua; // pixel+SCT hits >=5
			int nIDhitsMub   = nSCThitsMub+nPIXhitsMub; // pixel+SCT hits >=5
			
			
			// ID - MS pT matching: pT=|p|*sin(theta), qOp=charge/|p|
			double me_qOp_a   = m_offPhys->mu_staco_me_qoverp->at(ai);
			double id_qOp_a   = m_offPhys->mu_staco_id_qoverp->at(ai);
			double me_theta_a = m_offPhys->mu_staco_me_theta->at(ai);
			double id_theta_a = m_offPhys->mu_staco_id_theta->at(ai);
			double me_qOp_b   = m_offPhys->mu_staco_me_qoverp->at(bi);
			double id_qOp_b   = m_offPhys->mu_staco_id_qoverp->at(bi);
			double me_theta_b = m_offPhys->mu_staco_me_theta->at(bi);
			double id_theta_b = m_offPhys->mu_staco_id_theta->at(bi);
			
			/*
			// impact parameter
			double impPrmZ0 = m_offPhys->mu_staco_z0_exPV->at(ai);
			double impPrmD0 = m_offPhys->mu_staco_d0_exPV->at(ai);
			*/
			
			// isolation
			double mu_pTa   = m_offPhys->mu_staco_pt->at(ai);
			double mu_pTb   = m_offPhys->mu_staco_pt->at(bi);
			double pTcone20a = m_offPhys->mu_staco_ptcone20->at(ai);
			double pTcone20b = m_offPhys->mu_staco_ptcone20->at(bi);
			double pTcone30a = m_offPhys->mu_staco_ptcone30->at(ai);
			double pTcone30b = m_offPhys->mu_staco_ptcone30->at(bi);
			double pTcone40a = m_offPhys->mu_staco_ptcone40->at(ai);
			double pTcone40b = m_offPhys->mu_staco_ptcone40->at(bi);
			
			// fill the kinematic variables of this pair for the digested tree
			kinematicVariables.insert( make_pair("imass", current_imass) );
			kinematicVariables.insert( make_pair("pT", current_mu_pT) );
			kinematicVariables.insert( make_pair("eta", current_mu_eta) );
			kinematicVariables.insert( make_pair("cosTheta", current_mu_cosTheta) );
			
			TMapsd values2fill;
			values2fill.insert( make_pair( "imass",current_imass ) );
			values2fill.insert( make_pair( "pT",current_mu_pT ) );
			

			bool passCutFlow    = true;
			bool passCurrentCut = true;
			// fill the cut flow, stop at the relevant cut each time.
			// the cut objects don't have to be "correctly" ordered
			// since it is done by the loop on the ordered cut flow map
			for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
			{
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
					
					/*
					if(passCutFlow)
					{
						double pT_id = (id_qOp_a!=0) ? fabs(1./id_qOp_a)*sin(id_theta_a) : 0.;
						double pT_ms = (me_qOp_a!=0) ? fabs(1./me_qOp_a)*sin(me_theta_a) : 0.;
						double ratio = (pT_id!=0.) ? fabs(pT_ms/pT_id) : 0.;					
						cout << "A: pT_id=" << pT_id << ", pT_ms=" << pT_ms << ", ratio=" << ratio << endl;
					
						pT_id = (id_qOp_b!=0) ? fabs(1./id_qOp_b)*sin(id_theta_b) : 0.;
						pT_ms = (me_qOp_b!=0) ? fabs(1./me_qOp_b)*sin(me_theta_b) : 0.;
						ratio = (pT_id!=0.) ? fabs(pT_ms/pT_id) : 0.;					
						cout << "B: pT_id=" << pT_id << ", pT_ms=" << pT_ms << ", ratio=" << ratio << endl;
					}
					*/
				}

				
				passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
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
					if(m_sLastCut2Hist==sorderedcutname) ///////////////////////////////
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
						
						// fill the xVector for the ML fit:
						m_fit->fillXvec( current_imass );
					}
					///////////////////////////////////////////////////////////////////
				} // end if(passCutFlow)
				
				// fill the decision
				cutFlowDecision.insert( make_pair(sorderedcutname, passCurrentCut) );
			} // end for(m_cutFlowOrdered)
		} // for(allmupairMap)
		////////////////////////////////////////////////////////////////////////////
		m_offTreeDigest->fill(cutFlowDecision, kinematicVariables); ////////////////
		////////////////////////////////////////////////////////////////////////////
	} // end if(allmupairMap.size()>0)
	else // no mu pair(s) at all
	{
		//////////////////////////////////////////////////
		m_offTreeDigest->fill(); /////////////////////////
		//////////////////////////////////////////////////
	}

	// re-initialize
	if(allmupairMap.size()>0) allmupairMap.clear();
	if(pmu.size()>0)          pmu.clear();
}

void offlineAnalysis::write()
{
	m_treeFile->cd();
	m_offTreeDigest->write();
	//m_treeFile->Close();
}

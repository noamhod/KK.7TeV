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

analysis::analysis(physics* phys, graphicObjects* graphicobjs, GRLinterface* grl, TFile* treeFile)
{
	initialize();

	m_phys = phys;

	m_analysis_grl = grl;	

	m_treeFile = treeFile;

	m_offlineTree = new offlineTree(m_phys, m_treeFile);

	// need to switch off all the branches with:
	enableGeneralBranches();

	m_muid    = new muon_muid(  m_phys ); // this will also "turn on" the desired branches (virtual in the base)
	m_mustaco = new muon_staco( m_phys ); // this will also  "turn on" the desired branches (virtual in the base)

	//m_dir_muon_staco = m_treeFile->mkdir("muon_staco");
	//m_mustacotree = new muon_staco_tree( m_mustaco, m_dir_muon_staco );

	m_cutFlowMap     = new TMapsd();
	m_cutFlowOrdered = new TMapds();
	m_cutFlowNumbers = new TMapsi();

	m_graphicobjs = graphicobjs;
}

void analysis::enableGeneralBranches()
{
	cout << "WARNING:   in analysis::enableGeneralBranches()" << endl;
	cout << "           did you remember to enable the all the" << endl;
	cout << "           branches that you are using ?" << endl;
	/*----------------------------------------------------------------*/
	/*--- this method disables all the branches of the chain.      ---*/
	/*--- then, the relevant branches are enabled in 2 places:     ---*/
	/*--- 1. in this method the event level branchea are enabled.  ---*/
	/*--- 2. in the muon_staco and muon_muid classes, the relevant ---*/
	/*---    branches are enabled for the relevant analysis        ---*/
	/*----------------------------------------------------------------*/

	m_phys->fChain->SetBranchStatus("*", 0); // disable all

	// enable the event-level branches 
	m_phys->fChain->SetBranchStatus("L1_*", 1); // enable L1
	m_phys->fChain->SetBranchStatus("RunNumber", 1); // enable run nuber
	m_phys->fChain->SetBranchStatus("lbn", 1); // enable lumi block number
	m_phys->fChain->SetBranchStatus("EventNumber", 1); // enable event number
	
	//m_phys->fChain->SetBranchStatus("*", 1); // enable all
}

void analysis::readCutFlow(string sCutFlowFilePath)
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
	
	file.close();
}

TMapsd* analysis::getCutFlowMapPtr()
{
	return m_cutFlowMap;
}

TMapds* analysis::getCutFlowOrderedPtr()
{
	return m_cutFlowOrdered;
}

analysis::~analysis()
{
	finalize();
}

void analysis::initialize()
{
	nAllEvents = 0;
}

void analysis::finalize()
{

}

void analysis::printCutFlowNumbers(Long64_t chainEntries)
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
        b_isGRL = m_analysis_grl->m_grl.HasRunLumiBlock( m_phys->RunNumber, m_phys->lbn );
        m_offlineTree->fill( b_isGRL );
        if(isendofrun) m_offlineTree->write();
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
				cosmicCosth = dimuonCosth( pmu[n], pmu[m] );
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
			//cosmicCosth = dimuonCosth( pmu[ai], pmu[bi] );

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
	nAllEvents++;

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
			// fill the cut flow histograms:

			// calculate the necessary variables to be filled
			TMapsd values2fill;
			values2fill.insert( make_pair( "imass",imass(pmu[ai],pmu[bi]) ) );
			values2fill.insert( make_pair( "pT",(m_phys->mu_staco_charge->at(ai)<0.)?pT(pmu[ai]):pT(pmu[bi]) ) );

			// help
			double d0exPVa = m_phys->mu_staco_d0_exPV->at(ai);
			double z0exPVa = m_phys->mu_staco_z0_exPV->at(ai);
			double d0exPVb = m_phys->mu_staco_d0_exPV->at(bi);
			double z0exPVb = m_phys->mu_staco_z0_exPV->at(bi);

			int runnumber  = m_phys->RunNumber;
			int lumiblock  = m_phys->lbn;
			int GRL        = m_analysis_grl->m_grl.HasRunLumiBlock( runnumber, lumiblock );

			bool passCut  = true;

			// fill the cut flow, stop at the relevant cut each time.
			// the cut objects don't have to be "correctly" ordered
			// since it is done by the loop on the ordered cut flow map
			for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
			{
				string sorderedcutname = ii->second;

				if(sorderedcutname=="null")
				{
					passCut = (passCut)                                                                  ? true : false;
					if(passCut) fillCutFlow("null", values2fill); // stop at null cut
				}

				if(sorderedcutname=="GRL")
				{
					passCut = (GRL==(int)(*m_cutFlowMap)["GRL"]  &&  passCut) ? true : false;
					if(passCut) fillCutFlow("GRL", values2fill); // stop at null cut
				}

				if(sorderedcutname=="L1_MU6")
				{
					passCut = (m_phys->L1_MU6==(int)(*m_cutFlowMap)["L1_MU6"]  &&  passCut)             ? true : false;
					if(passCut) fillCutFlow("L1_MU6", values2fill); // stop at null cut
				}		

				if(sorderedcutname=="imass")
				{
					passCut = ( imassCut((*m_cutFlowMap)["imass"], pmu[ai], pmu[bi])  &&  passCut )      ? true : false;
					if(passCut) fillCutFlow("imass", values2fill); // stop at imass cut
				}

				if(sorderedcutname=="pT")
				{
					passCut = ( pTCut((*m_cutFlowMap)["pT"], pmu[ai], pmu[bi])  &&  passCut )            ? true : false;
					if(passCut) fillCutFlow("pT", values2fill); // stop at pT cut
				}

				if(sorderedcutname=="eta")
				{
					passCut = ( etaCut((*m_cutFlowMap)["eta"], pmu[ai], pmu[bi])  &&  passCut )          ? true : false;
					if(passCut) fillCutFlow("eta", values2fill); // stop at eta cut
				}

				if(sorderedcutname=="cosmicCut")
				{
					passCut = ( cosmicCut((*m_cutFlowMap)["cosmicCut"], pmu[ai], pmu[bi])  &&  passCut ) ? true : false;
					if(passCut) fillCutFlow("cosmicCut", values2fill); // stop at cosmic cut
				}

				if(sorderedcutname=="d0")
				{
					passCut = ( d0Cut((*m_cutFlowMap)["d0"], d0exPVa, d0exPVb)  &&  passCut )            ? true : false;
					if(passCut) fillCutFlow("d0", values2fill); // stop at d0 cut
				}

				if(sorderedcutname=="z0")
				{
					passCut = ( z0Cut((*m_cutFlowMap)["z0"], z0exPVa, z0exPVb)  &&  passCut )            ? true : false;
					if(passCut) fillCutFlow("z0", values2fill); // stop at d0 cut
				}

				// count the numbers
				if(passCut) m_cutFlowNumbers->operator[](sorderedcutname) ++;
			}
		}
	}
	// re-initialize
	if(allmupairMap.size()>0) allmupairMap.clear();
	if(pmu.size()>0)          pmu.clear();
}


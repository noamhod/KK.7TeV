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

digestAnalysis::digestAnalysis(digestPhysics* offPhys, graphicObjects* graphicobjs, string sLastCut2Hist)
{
	initialize();

	m_digestPhys = offPhys;

	/*
	m_muid    = new muon_muid(  m_digestPhys ); // this will also "turn on" the desired branches (virtual in the base)
	m_mu_staco = new muon_staco( m_digestPhys ); // this will also  "turn on" the desired branches (virtual in the base)
	*/

	m_cutFlowMap         = new TMapsd();
	m_cutFlowOrdered     = new TMapds();
	m_cutFlowNumbers     = new TMapsi();

	m_graphicobjs = graphicobjs;

	m_fit = new fit();
	
	m_sLastCut2Hist = sLastCut2Hist;
}

void digestAnalysis::readCutFlow(string sCutFlowFilePath)
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

TMapsd* digestAnalysis::getCutFlowMapPtr()
{
	return m_cutFlowMap;
}

TMapds* digestAnalysis::getCutFlowOrderedPtr()
{
	return m_cutFlowOrdered;
}

digestAnalysis::~digestAnalysis()
{
	finalize();
}

void digestAnalysis::initialize()
{
	nAllEvents = 0;
}

void digestAnalysis::finalize()
{
	
}

void digestAnalysis::fitter()
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

void digestAnalysis::printCutFlowNumbers(Long64_t chainEntries)
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

void digestAnalysis::fillCutFlow(string sCurrentCutName, TMapsd& values2fill)
{
	for(TMapds::iterator ii=m_cutFlowOrdered->begin() ; ii!=m_cutFlowOrdered->end() ; ++ii)
	{
		string scutname = ii->second;
		m_graphicobjs->hmap_cutFlow_imass->operator[]("imass."+scutname)->Fill( values2fill["imass"] );
		m_graphicobjs->hmap_cutFlow_pT->operator[]("pT."+scutname)->Fill(       values2fill["pT"]    );
		if(scutname==sCurrentCutName) break;
	}
}

/*
void digestAnalysis::executeBasic()
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
	for(int n=0 ; n<(int)m_digestPhys->mu_staco_m->size() ; n++)
	{
		pmu.push_back( new TLorentzVector() );
		pmu[n]->SetPx( m_digestPhys->mu_staco_px->at(n) );
		pmu[n]->SetPy( m_digestPhys->mu_staco_py->at(n) );
		pmu[n]->SetPz( m_digestPhys->mu_staco_pz->at(n) );
		pmu[n]->SetE( m_digestPhys->mu_staco_E->at(n) );
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
			if( m_digestPhys->isGRL ) // this is a cut and not overlap removal
			{
				if( m_digestPhys->L1_MU6 ) // this is also a cut and not overlap removal
				{
					buildMuonPairMap( mupairMap,
					pmu[n], m_digestPhys->mu_staco_charge->at(n), m_digestPhys->mu_staco_d0_exPV->at(n), m_digestPhys->mu_staco_z0_exPV->at(n), n,
					pmu[m], m_digestPhys->mu_staco_charge->at(m), m_digestPhys->mu_staco_d0_exPV->at(m), m_digestPhys->mu_staco_z0_exPV->at(m), m );
				}
			}

			// check before cuts
			if(m_digestPhys->mu_staco_charge->at(n) * m_digestPhys->mu_staco_charge->at(m)<0.)
			{
				cosmicCosth = cosThetaDimu( pmu[n], pmu[m] );
				m_graphicobjs->h1_cosmicCosth->Fill( cosmicCosth );
				
				d0exPVa = m_digestPhys->mu_staco_d0_exPV->at(n);
				d0exPVb = m_digestPhys->mu_staco_d0_exPV->at(m);
				m_graphicobjs->h1_d0exPV->Fill(d0exPVa);
				m_graphicobjs->h1_d0exPV->Fill(d0exPVb);

				z0exPVa = m_digestPhys->mu_staco_z0_exPV->at(n);
				z0exPVb = m_digestPhys->mu_staco_z0_exPV->at(m);
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
			costh = cosThetaCollinsSoper( 	pmu[ai], (double)m_digestPhys->mu_staco_charge->at(ai),
			pmu[bi], (double)m_digestPhys->mu_staco_charge->at(bi) );
			d0exPVa = m_digestPhys->mu_staco_d0_exPV->at(ai);
			z0exPVa = m_digestPhys->mu_staco_z0_exPV->at(ai);
			d0exPVb = m_digestPhys->mu_staco_d0_exPV->at(bi);
			z0exPVb = m_digestPhys->mu_staco_z0_exPV->at(bi);
			//cosmicCosth = cosThetaDimu( pmu[ai], pmu[bi] );

			cout << "$$$$$$$$$ dimuon $$$$$$$$$" << endl;
			cout << "\t im=" << im << endl;
			cout << "\t pTa=" << pTa  << endl;
			cout << "\t pTb=" << pTb  << endl;
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;

			// fill the histos
			if( m_digestPhys->mu_staco_charge->at(ai)<0. )
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
*/

/*
void digestAnalysis::executeAdvanced()
{

	// stupid example
	if(m_muid->getNParticles()>0)
	{
		m_muid->setParticle(0);
	}

	// stupid example
	if(m_digestPhys->mu_staco_n>0)
	{
		for(int n=0 ; n<(int)m_mu_staco->getNParticles() ; n++)
		{
			m_mu_staco->setParticle(n);
			m_graphicobjs->h2_xyVertex->Fill( m_mu_staco->pvVec->X(), m_mu_staco->pvVec->Y() );
		}
	}
}
*/

void digestAnalysis::executeCutFlow()
{
	nAllEvents++;
	// fill the cut flow histograms:

	// calculate the necessary variables to be filled
	double current_imass       = m_digestPhys->kin_imass;
	double current_mu_pT       = m_digestPhys->kin_pT_mu;
	double current_mu_eta      = m_digestPhys->kin_eta_mu;
	double current_mu_cosTheta = m_digestPhys->kin_cosTheta_mu;
	
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

		if(sorderedcutname=="c1*c2<0")
		{
			passCurrentCut = (m_digestPhys->is_null) ? true : false;
		}

		if(sorderedcutname=="GRL")
		{
			passCurrentCut = (m_digestPhys->is_GRL) ? true : false;
		}

		if(sorderedcutname=="L1_MU6")
		{
			passCurrentCut = (m_digestPhys->is_L1_MU6) ? true : false;
		}		

		if(sorderedcutname=="imass")
		{
			passCurrentCut = ( m_digestPhys->is_imass ) ? true : false;
		}

		if(sorderedcutname=="pT")
		{
			passCurrentCut = ( m_digestPhys->is_pT ) ? true : false;
		}

		if(sorderedcutname=="eta")
		{
			passCurrentCut = ( m_digestPhys->is_eta ) ? true : false;
		}

		if(sorderedcutname=="cosThetaDimu")
		{
			passCurrentCut = ( m_digestPhys->is_cosThetaDimuCut ) ? true : false;
		}

		if(sorderedcutname=="d0")
		{
			passCurrentCut = ( m_digestPhys->is_d0 ) ? true : false;
		}

		if(sorderedcutname=="z0")
		{
			passCurrentCut = ( m_digestPhys->is_z0 ) ? true : false;
		}

		passCutFlow = (passCurrentCut  &&  passCutFlow) ? true : false;
		if(passCutFlow) fillCutFlow(sorderedcutname, values2fill); // stop at this(sorderedcutname) cut
		if(m_sLastCut2Hist==sorderedcutname && passCutFlow) m_fit->fillXvec( current_imass );
		
		// count the numbers
		if(passCutFlow) m_cutFlowNumbers->operator[](sorderedcutname) ++;
	}
}



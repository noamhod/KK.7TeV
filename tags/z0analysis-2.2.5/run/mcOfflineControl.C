/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "mcOfflineControl.h"


mcOfflineControl::mcOfflineControl()
{
	startTimer();

	initialize();
	
	string str = "";

	///////////////////////////////
	// chose the MC sample here ///
	//string sMCsample = "DYmumu_250M400";
	string sMCsample = pickMCinputSampe();
	///////////////////////////////
	
	str = checkANDsetFilepath("PWD", "/../conf/offline_mc_dataset_"+sMCsample+".list");
	string strb = checkANDsetFilepath("PWD", "/offline_mc_datasetdir/"); // ln -s  ~hod/data  datasetdir
	makeChain(true, str, strb);

	m_mcOffPhys = new mcOfflinePhysics( m_chain );

	str = checkANDsetFilepath("PWD", "/../data/mcOfflineTreeDigest_"+sMCsample+".root");
	m_treefile = new TFile( str.c_str(), "RECREATE");
	
	str = checkANDsetFilepath("PWD", "/../data/mcOfflineControl_"+sMCsample+".root");
	m_histfile = new TFile( str.c_str(), "RECREATE");
	m_histfile->cd();
	
	string str1 = checkANDsetFilepath("PWD", "/../conf/cutFlow.cuts");
	string str2 = checkANDsetFilepath("PWD", "/../conf/dataPeriods.data");
	
	m_mcOfflineAnalysis = new mcOfflineAnalysis( m_mcOffPhys, m_treefile, str1, str2, "" );
	
	book();
}

mcOfflineControl::~mcOfflineControl()
{
	//finalize();
}

string mcOfflineControl::pickMCinputSampe()
{
	int n = 0;
	TMapis mcSamplesMap;
	
	mcSamplesMap.insert( make_pair( 0,"Zmumu" ) ); 
	
	mcSamplesMap.insert( make_pair( 1,"DYmumu_75M120" ) );
	mcSamplesMap.insert( make_pair( 2,"DYmumu_120M250" ) );
	mcSamplesMap.insert( make_pair( 3,"DYmumu_250M400" ) );
	mcSamplesMap.insert( make_pair( 4,"DYmumu_400M600" ) );
	mcSamplesMap.insert( make_pair( 5,"DYmumu_600M800" ) );
	mcSamplesMap.insert( make_pair( 6,"DYmumu_800M1000" ) );
	mcSamplesMap.insert( make_pair( 7,"DYmumu_1000M1250" ) );
	mcSamplesMap.insert( make_pair( 8,"DYmumu_1250M1500" ) );
	mcSamplesMap.insert( make_pair( 9,"DYmumu_1500M1750" ) );
	mcSamplesMap.insert( make_pair( 10,"DYmumu_1750M2000" ) );
	mcSamplesMap.insert( make_pair( 11,"DYmumu_M2000" ) );

	mcSamplesMap.insert( make_pair( 100,"DYtautau_75M120" ) );
	mcSamplesMap.insert( make_pair( 101,"DYtautau_120M250" ) );
	mcSamplesMap.insert( make_pair( 102,"DYtautau_250M400" ) );
	mcSamplesMap.insert( make_pair( 103,"DYtautau_400M600" ) );
	mcSamplesMap.insert( make_pair( 104,"DYtautau_600M800" ) );
	mcSamplesMap.insert( make_pair( 105,"DYtautau_800M1000" ) );
	mcSamplesMap.insert( make_pair( 106,"DYtautau_1000M1250" ) );
	mcSamplesMap.insert( make_pair( 107,"DYtautau_1250M1500" ) );
	mcSamplesMap.insert( make_pair( 108,"DYtautau_1500M1750" ) );
	mcSamplesMap.insert( make_pair( 109,"DYtautau_1750M2000" ) );
	mcSamplesMap.insert( make_pair( 110,"DYtautau_M2000" ) );

	mcSamplesMap.insert( make_pair( 200,"Ztautau" ) );
	mcSamplesMap.insert( make_pair( 201,"TTbar" ) );
	mcSamplesMap.insert( make_pair( 202,"Wmunu" ) );
	mcSamplesMap.insert( make_pair( 203,"bbmu15X" ) );
	mcSamplesMap.insert( make_pair( 204,"ccmu15X" ) );

	mcSamplesMap.insert( make_pair( 300,"Zprime_mumu_SSM1000" ) );
	mcSamplesMap.insert( make_pair( 301,"Zprime_mumu_SSM1250" ) );
	mcSamplesMap.insert( make_pair( 302,"Zprime_mumu_SSM1500" ) );
	mcSamplesMap.insert( make_pair( 303,"Zprime_mumu_SSM1750" ) );
	mcSamplesMap.insert( make_pair( 304,"Zprime_mumu_SSM2000" ) );
	
	
	cout << "PICK AN MC CHANNEL FORM THE LIST:" << endl;
	for(TMapis::iterator it=mcSamplesMap.begin() ; it!=mcSamplesMap.end() ; it++)
	{
		cout << "\t[" << it->first << "]\t" << it->second << endl;
	}
	cout << "...";
	cin >> n;
	TMapis::iterator it=mcSamplesMap.find(n);
	return it->second;
}

void mcOfflineControl::initialize()
{
	// run control
	l64t_nentries = 0;
	l64t_nbytes   = 0;
	l64t_nb       = 0;
	l64t_jentry   = 0;
	l64t_ientry   = 0;

	// pointers
	m_mcOffPhys     = NULL;
	m_mcOfflineAnalysis = NULL;
	m_histfile = NULL;
	m_treefile = NULL;
}

void mcOfflineControl::finalize()
{
	// write the tree
	m_mcOfflineAnalysis->write();

	// files
	m_histfile->Write();
	m_histfile->Close();

	m_treefile->Write();
	m_treefile->Close();
}

void mcOfflineControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_mcOfflineAnalysis->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_mcOfflineAnalysis->bookHistos(m_dirAllCuts);
	
	m_dirFit = m_histfile->mkdir("fit");
	m_mcOfflineAnalysis->bookFitHistos(m_dirFit);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
	m_mcOfflineAnalysis->bookHistosMap( m_mcOfflineAnalysis->getCutFlowOrderedMapPtr(), m_mcOfflineAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
}

void mcOfflineControl::draw()
{
	m_mcOfflineAnalysis->drawBareHistos(m_dirNoCuts);
	m_mcOfflineAnalysis->drawHistos(m_dirAllCuts);
	m_mcOfflineAnalysis->drawHistosMap( m_mcOfflineAnalysis->getCutFlowOrderedMapPtr(), m_mcOfflineAnalysis->getCutFlowTypeOrderedMapPtr(), m_dirCutFlow );
	m_mcOfflineAnalysis->drawFitHistos(m_dirFit, m_mcOfflineAnalysis->m_fitROOT->guess, m_mcOfflineAnalysis->m_fitROOT->fitFCN);
	//m_mcOfflineAnalysis->drawFitHistos(m_dirFit, m_mcOfflineAnalysis->m_fitMinuit->guess, m_mcOfflineAnalysis->m_fitMinuit->fitFCN);

	m_mcOfflineAnalysis->printCutFlowNumbers(l64t_nentries);
}

void mcOfflineControl::fits()
{
	cout << "### in fits ####" << endl;

	double yields[2];
	
	// Preform the fit
	m_mcOfflineAnalysis->minimize( false, m_mcOfflineAnalysis->h1_imassFit, yields );
}

void mcOfflineControl::analyze()
{
	m_mcOfflineAnalysis->executeCutFlow();
}

void mcOfflineControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_mcOffPhys->fChain == 0)  return;

	l64t_nentries = m_mcOffPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 100000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;

	if(stopAfterNevents <= 0)                            { l64t_stopEvent = l64t_nentries; cout << "1. stop at event " << l64t_stopEvent << endl; }
	else if(startEvent+stopAfterNevents < l64t_nentries) { l64t_stopEvent = startEvent+stopAfterNevents; cout << "3. stop at event " << l64t_stopEvent << endl; }
	if(startEvent+stopAfterNevents > l64t_nentries)      { l64t_stopEvent = l64t_nentries; cout << "2. stop at event " << l64t_stopEvent << endl; }

	for (l64t_jentry=l64t_startEvent ; l64t_jentry<l64t_stopEvent/*l64t_nentries*/ ; l64t_jentry++)
	{
		l64t_ientry = m_mcOffPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcOffPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		if(l64t_jentry%100000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcOffPhys->RunNumber << "\tlumiblock=" << m_mcOffPhys->lbn << endl;
		if(l64t_jentry%l64t_mod==0) m_mcOfflineAnalysis->printCutFlowNumbers(l64t_nentries);
		
		analyze();
	}
	
	fits();
	
	draw();
	
	//finalize();
	
	stopTimer(true);
}







void mcOfflineControl::getCandidates(string sFilePath)
{
	fstream file;
	file.open( sFilePath.c_str() );

	string sLine = "";
	vector<double> values;
	double tmpVal = 0.;

	int nLinesRead = 0;

	while(!file.eof())
	{
		getline(file,sLine);

		if(sLine == "") continue;
		cout << sLine << endl;

		// parse the line:
		if(values.size()>0) values.clear();
		stringstream strm(sLine);
		while(!strm.eof())
		{
			strm >> tmpVal;
			values.push_back(tmpVal);
		}
		
		for(int i=0 ; i<(int)values.size() ; i++)
		{
			// encoding:
			// 0=RN
			// 1=LB
			// 2=EN
			// 3=Mass(CB)
			// 4=Mass(ID)
			// 5=Mass(ME)
			// 6=pT1
			// 7=pT2
			switch(i)
			{
				case 0: runNumber.push_back( values[i] ); break;
				case 1: lumiBlock.push_back( values[i] ); break;
				case 2: eventNumber.push_back( values[i] ); break;
				case 3: mass_cb.push_back( values[i] ); break;
				case 4: mass_id.push_back( values[i] ); break;
				case 5: mass_me.push_back( values[i] ); break;
				case 6: pT1.push_back( values[i] ); break;
				case 7: pT2.push_back( values[i] ); break;
				default: break;
			}
		}
		nLinesRead++;
	}
	cout << "read " << nLinesRead << " lines" << endl;
}

bool mcOfflineControl::matchCandidates()
{	
	for(int rn=0 ; rn<(int)runNumber.size() ; rn++)
	{
		if( runNumber[rn] != (double)m_mcOffPhys->RunNumber ) continue;
		for(int lb=0 ; lb<(int)lumiBlock.size() ; lb++)
		{
			if( lumiBlock[lb] != (double)m_mcOffPhys->lbn ) continue;
			for(int en=0 ; en<(int)eventNumber.size() ; en++)
			{
				if( eventNumber[en] != (double)m_mcOffPhys->EventNumber ) continue;			
				cout << "match !" << endl;
				return true;
			}
		}
	}
	return false;
}

void mcOfflineControl::loopCandidates()
{
	if (m_mcOffPhys->fChain == 0)  return;

	l64t_nentries = m_mcOffPhys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	// read the external list of Z candidates
	int nMatched = 0;
	string sFilePath = checkANDsetFilepath("PWD", "/../conf/STACO.cand");
	getCandidates(sFilePath);
	
	for (l64t_jentry=0 ; l64t_jentry<l64t_nentries ; l64t_jentry++)
	{
		l64t_ientry = m_mcOffPhys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_mcOffPhys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		
		if(l64t_jentry%1000==0) cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << "\trun=" << m_mcOffPhys->RunNumber << "\tlumiblock=" << m_mcOffPhys->lbn << "\tnMatched=" << nMatched << endl;
		
		// try to match this event to an entry from the external list
		if( matchCandidates() ) nMatched++;
	}
}

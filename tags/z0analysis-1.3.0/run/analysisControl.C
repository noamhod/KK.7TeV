/* * * * * * * * * * * */
/* created by Naom Hod */
/* noam.hod@cern.ch    */
/* noam.com@gmail.com  */
/* on 23/07/2010 11:24 */
/* * * * * * * * * * * */

#include "analysisControl.h"


analysisControl::analysisControl()
{
	initialize();

	//---------------------------------------------------------------/
	/*---*/ string  slocalpath  = "/srv01/tau/hod/z0analysis/" /*---*/
	/*---*/ TString tslocalpath = (TString)slocalpath;         /*---*/
	/*---*/ string  sdatapath   = "/data/hod/D3PDs/"           /*---*/
	//---------------------------------------------------------------/



	makeChain(true, slocalpath+"conf/dataset.list", sdatapath+"group10.phys-sm.data10_7TeV_physics_MuonswBeam_WZphys_D3PD/");

	m_phys = new physics( m_chain );


	m_treefile = new TFile( (slocalpath+"data/analysisTrees.root").c_str(), "RECREATE");
        m_treefile->cd();

	m_histfile = new TFile( (slocalpath+"data/analysisControl.root").c_str(), "RECREATE");
        m_histfile->cd();

	m_graphics = new graphicObjects();
	m_graphics->setStyle();

	m_GRL = new GRLinterface();
        m_GRL->glrinitialize(tslocalpath+"conf/Z_GRL_152844-159224.xml");

        m_analysis = new analysis( m_phys, m_graphics, m_GRL, m_treefile );

	// read the cut flow (ownership: selection class which analysis inherits from)
	m_analysis->readCutFlow(slocalpath+"conf/cutFlow.cuts");

	book();
}

void analysisControl::setLocalPath(string spath)
{
	m_spath = spath;	
}

void analysisControl::initialize()
{
	// run control
	l64t_nentries = 0;
        l64t_nbytes   = 0;
        l64t_nb       = 0;
        l64t_jentry   = 0;
        l64t_ientry   = 0;

        // pointers
	m_phys     = NULL;
	m_analysis = NULL;
	m_graphics = NULL;
	m_histfile = NULL;
	m_treefile = NULL;

	cinitialize();
	kinitialize();
	uinitialize();
}

void analysisControl::finalize()
{
	// file
	m_histfile->Write();
	m_histfile->Close();

	// pointers
	delete m_phys;
	delete m_analysis;
	delete m_graphics;
	delete m_histfile;
	delete m_treefile;

	cfinalize();
	kfinalize();
        ufinalize();
}

void analysisControl::book()
{
	m_dirNoCuts = m_histfile->mkdir("noCuts");
	m_graphics->bookBareHistos(m_dirNoCuts);

	m_dirAllCuts = m_histfile->mkdir("allCuts");
	m_graphics->bookHistos(m_dirAllCuts);

	m_dirCutFlow = m_histfile->mkdir("cutFlow");
        m_graphics->bookHistosMap( m_analysis->getCutFlowMapPtr(), m_analysis->getCutFlowOrderedPtr(), m_dirCutFlow );	
}

void analysisControl::draw()
{
	m_graphics->drawBareHistos(m_dirNoCuts);
	m_graphics->drawHistos(m_dirAllCuts);
        m_graphics->drawHistosMap( m_analysis->getCutFlowMapPtr(), m_analysis->getCutFlowOrderedPtr(), m_dirCutFlow );

        m_analysis->printCutFlowNumbers(l64t_nentries);
}

void analysisControl::analyze()
{
	bool isendofrun = (l64t_jentry==l64t_stopEvent-1) ? true : false;

	m_analysis->executeBasic( isendofrun );
	m_analysis->executeAdvanced( isendofrun );
	m_analysis->executeCutFlow();
}

void analysisControl::makeTreeFriends()
{
	m_analysis->m_eventLevelTree->AddFriend( m_analysis->m_mustacotree->m_tree );
	//m_analysis->m_eventLevelTree->AddFriend( m_analysis->m_mumuidtree->m_tree );
        //m_analysis->m_eventLevelTree->AddFriend( m_analysis->m_eelctrontree->m_tree );
        //....
}

void analysisControl::loop(Long64_t startEvent, Long64_t stopAfterNevents)
{
	if (m_phys->fChain == 0)  return;

	l64t_nentries = m_phys->fChain->GetEntriesFast();
	l64t_nbytes = 0;
	l64t_nb = 0;

	l64t_mod = 5000;

	l64t_startEvent = startEvent;
	l64t_stopEvent = l64t_nentries;

	if(stopAfterNevents <= 0)                            { l64t_stopEvent = l64t_nentries; cout << "1. stop at event " << l64t_stopEvent << endl; }
	else if(startEvent+stopAfterNevents < l64t_nentries) { l64t_stopEvent = startEvent+stopAfterNevents; cout << "3. stop at event " << l64t_stopEvent << endl; }
	if(startEvent+stopAfterNevents > l64t_nentries)      { l64t_stopEvent = l64t_nentries; cout << "2. stop at event " << l64t_stopEvent << endl; }

	for (l64t_jentry=l64t_startEvent ; l64t_jentry<l64t_stopEvent/*l64t_nentries*/ ; l64t_jentry++)
	{
		l64t_ientry = m_phys->LoadTree(l64t_jentry);
		if (l64t_ientry < 0) break;
		l64t_nb = m_phys->fChain->GetEntry(l64t_jentry);
		l64t_nbytes += l64t_nb;
		// if (Cut(l64t_ientry) < 0) continue;
		
		cout << "jentry=" << l64t_jentry << "\t ientry=" << l64t_ientry << endl;
		if(l64t_jentry%l64t_mod==0) m_analysis->printCutFlowNumbers(l64t_nentries);
	
		analyze();
	}
	
	makeTreeFriends();

	draw();
}


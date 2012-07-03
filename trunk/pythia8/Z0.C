#include "pythiaROOT.h"
#include "all.h"

void findpair(vector<int>* index, Event& evt, int& ia, int& ib)
{
	if(index->size()==2)
	{
		ia = index->at(0);
		ib = index->at(1);
		return;
	}

	for(int i=0 ; i<(int)index->size() ; ++i)
	{
		for(int j=0 ; (j<(int)index->size()  &&  j>i) ; ++j)
		{
			if(evt[index->at(i)].charge()*evt[index->at(j)].charge()<0.)
			{
				ia = index->at(i);
				ib = index->at(j);
			}
		}
	}

	ia = -1;
	ib = -1;
}

int main()
{
	// Generator.
	Pythia pythia;
	//ParticleData& pdt = pythia.particleData;

	// Pick new random number seed for each run, based on clock.
	pythia.readString("Random:setSeed = on");
	pythia.readString("Random:seed = 0");

	// Process selection.
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
	//pythia.readString("WeakZ0:gmZmode = 0"); // full gamma/Z0 interference
	//Zprime:gmZmode = 0 ---> 6
	//0 = full gamma/Z0/Z' interference
	// rule out all gamma/Z decays except for muons
	//pythia.readString("22:onMode = off"); // switch off all of the gamma decay modes
	//pythia.readString("22:onIfAny = 13"); // switch on the gamma->mu-mu+ decay mode only
	pythia.readString("23:onMode = off"); // switch off all of the Z0 decay modes
	pythia.readString("23:onIfAny = 13"); // switch on the Z0->mu-mu+ decay mode only
	
	readParameters();

	stringstream strm;
	string sNewLowBound, sNewHighBound;

	strm.clear();
	strm << prm.mMin; // prm.newMass/4.;
	strm >> sNewLowBound;
	strm.clear();
	strm << prm.mMax; //prm.newMass*1.5; // prm.newMass*2.;
	strm >> sNewHighBound;


	/*
	// PDF initialization
	pythia.readString("PDF:useLHAPDF = on");
	pythia.readString("PDF:LHAPDFset = MRST2001lo.LHgrid");
	pythia.readString("PDF:LHAPDFmember = 0");
	// Allow extrapolation of PDF's beyond x and Q2 boundaries, at own risk.
	// Default behaviour is to freeze PDF's at boundaries.
	pythia.readString("PDF:extrapolateLHAPDF = on");
	// Need to change pT0Ref depending on choice of PDF.
	// One possibility: retune to same <n_charged>.
	//pythia.readString("MultipleInteractions:pT0Ref = 10"); 
	*/

	// Initialize.
	pythia.readString("23:mMin = " + sNewLowBound);
	pythia.readString("23:mMax = " + sNewHighBound);
	pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
	pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);
	pythia.init( 2212, 2212, 7000.);


	//ROOT
	TLorentzVector* pa = new TLorentzVector();
	TLorentzVector* pb = new TLorentzVector();
	string sDir   = "/data/hod/pythia8_ntuples/";
	string sTitle = prm.sName + prm.sFFbar + "_" + sNewLowBound + "M" + sNewHighBound;
	string sFileName = sDir + sTitle + ".root";
	TFile *file = TFile::Open(sFileName.c_str(),"recreate");
	TDirectory* tDir = file->mkdir("truth");
	tDir->cd();
	TTree *tree = new TTree("truth_tree","truth_tree");
	
	
	bool truth_all_isValid;
	
	vector<double>* truth_all_mc_pt = new vector<double>;
	vector<double>* truth_all_mc_m = new vector<double>;
	vector<double>* truth_all_mc_eta = new vector<double>;
	vector<double>* truth_all_mc_phi = new vector<double>;
	vector<int>*   truth_all_mc_status = new vector<int>;
	vector<int>*   truth_all_mc_barcode = new vector<int>;
	vector<int>*   truth_all_mc_pdgId = new vector<int>;
	vector<double>* truth_all_mc_charge = new vector<double>;
	
	vector<double>* truth_all_partons_mc_pt = new vector<double>;
	vector<double>* truth_all_partons_mc_m = new vector<double>;
	vector<double>* truth_all_partons_mc_eta = new vector<double>;
	vector<double>* truth_all_partons_mc_phi = new vector<double>;
	vector<int>*   truth_all_partons_mc_status = new vector<int>;
	vector<int>*   truth_all_partons_mc_barcode = new vector<int>;
	vector<int>*   truth_all_partons_mc_pdgId = new vector<int>;
	vector<double>* truth_all_partons_mc_charge = new vector<double>;
	
	tree->Branch( "truth_all_isValid", &truth_all_isValid );
	
	tree->Branch( "truth_all_mc_pt", &truth_all_mc_pt );
	tree->Branch( "truth_all_mc_m", &truth_all_mc_m );
	tree->Branch( "truth_all_mc_eta", &truth_all_mc_eta );
	tree->Branch( "truth_all_mc_phi", &truth_all_mc_phi );
	tree->Branch( "truth_all_mc_status", &truth_all_mc_status );
	tree->Branch( "truth_all_mc_barcode", &truth_all_mc_barcode );
	tree->Branch( "truth_all_mc_pdgId", &truth_all_mc_pdgId );
	tree->Branch( "truth_all_mc_charge", &truth_all_mc_charge );
	
	tree->Branch( "truth_all_partons_mc_pt", &truth_all_partons_mc_pt);
	tree->Branch( "truth_all_partons_mc_m", &truth_all_partons_mc_m);
	tree->Branch( "truth_all_partons_mc_eta", &truth_all_partons_mc_eta);
	tree->Branch( "truth_all_partons_mc_phi", &truth_all_partons_mc_phi);
	tree->Branch( "truth_all_partons_mc_status", &truth_all_partons_mc_status);
	tree->Branch( "truth_all_partons_mc_barcode", &truth_all_partons_mc_barcode);
	tree->Branch( "truth_all_partons_mc_pdgId", &truth_all_partons_mc_pdgId);
	tree->Branch( "truth_all_partons_mc_charge", &truth_all_partons_mc_charge);
	
	
	vector<int>* index  = new vector<int>;

	// Measure the cpu runtime,
	clock_t start, stop;
	double t = 0.0;
	// Depending on operating system, either of lines below gives warning.
	assert((start = clock()) != -1); // Start timer; clock_t signed.
	//assert((start = clock()) != -1u); // Start timer; clock_t unsigned.

	// list changes before the run
	pythia.settings.listChanged();
	pythia.particleData.listChanged();
	
	// Begin event loop. Generate event. Skip if error. List first one.
	for (int iEvent=0 ; iEvent<prm.nEvents ; ++iEvent)
	{
		if (!pythia.next()) continue;
		//if (iEvent < 1)   {pythia.info.list(); pythia.event.list();}
		//if (iEvent < 1)   {pythia.info.list();}
		//if (iEvent%10==0) {pythia.process.list();}
		
		// Begin event analysis.
		index->clear();
		
		truth_all_mc_pt->clear();
		truth_all_mc_m->clear();
		truth_all_mc_eta->clear();
		truth_all_mc_phi->clear();
		truth_all_mc_status->clear();
		truth_all_mc_barcode->clear();
		truth_all_mc_pdgId->clear();
		truth_all_mc_charge->clear();
		
		truth_all_partons_mc_pt->clear();
		truth_all_partons_mc_m->clear();
		truth_all_partons_mc_eta->clear();
		truth_all_partons_mc_phi->clear();
		truth_all_partons_mc_status->clear();
		truth_all_partons_mc_barcode->clear();
		truth_all_partons_mc_pdgId->clear();
		truth_all_partons_mc_charge->clear();
		
		int iZ = 0;
		for (int i=20 ; i>=0 ; --i)
		{
			if(pythia.event[i].id()==23)
			{
				iZ = i;
				
				int momA = pythia.event[i].mother1();
				int momB = pythia.event[i].mother2();
				
				if(momA==momB) continue;
				
				truth_all_partons_mc_pdgId->push_back(pythia.event[momA].id());
				truth_all_partons_mc_charge->push_back(pythia.event[momA].charge());
				truth_all_partons_mc_m->push_back(pythia.event[momA].m());
				truth_all_partons_mc_pt->push_back(pythia.event[momA].pT());
				truth_all_partons_mc_eta->push_back(pythia.event[momA].eta());
				truth_all_partons_mc_phi->push_back(pythia.event[momA].phi());
				
				truth_all_partons_mc_pdgId->push_back(pythia.event[momB].id());
				truth_all_partons_mc_charge->push_back(pythia.event[momB].charge());
				truth_all_partons_mc_m->push_back(pythia.event[momB].m());
				truth_all_partons_mc_pt->push_back(pythia.event[momB].pT());
				truth_all_partons_mc_eta->push_back(pythia.event[momB].eta());
				truth_all_partons_mc_phi->push_back(pythia.event[momB].phi());
				
				break;
			}
		}
		
		// loop on the particles in the event
		// find the Z and its final fermion decay products
		for (int i=0 ; i<pythia.event.size() ; ++i)
		{
			// find the final fermion who's first mother is the Z
			int isfinal = pythia.event[i].isFinal();
			int status  = pythia.event[i].status();
			int idf     = pythia.event[i].id();
			
			// Particle::status() = 21 - 29 : particles of the hardest subprocess
			// Particle::status() = 31 - 39 : particles of subsequent subprocesses
			// Particle::status() = 41 - 49 : particles produced by initial-state-showers
			// Particle::status() = 51 - 59 : particles produced by final-state-showers
			bool isHardProcsess = (
			(status>=21 && status<=29)  ||
			(status>=31 && status<=39)  ||
			(status>=41 && status<=49)  ||
			(status>=51 && status<=59)
			);
			
			bool isZ = pythia.event.isAncestor(i,iZ);
			
			if(isfinal  &&  isHardProcsess  &&  idf*idf==prm.idF*prm.idF  &&  isZ)
			{
				index->push_back(i);
			}
		}
		
		if(index->size()>1)
		{
			int ia = -1;
			int ib = -1;
			findpair(index,pythia.event,ia,ib);
			
			if(ia>=0  &&  ib>=0  &&  ia!=ib)
			{
				truth_all_mc_pdgId->push_back(pythia.event[ia].id());
				truth_all_mc_charge->push_back(pythia.event[ia].charge());
				truth_all_mc_m->push_back(pythia.event[ia].m());
				truth_all_mc_pt->push_back(pythia.event[ia].pT());
				truth_all_mc_eta->push_back(pythia.event[ia].eta());
				truth_all_mc_phi->push_back(pythia.event[ia].phi());
				
				truth_all_mc_pdgId->push_back(pythia.event[ib].id());
				truth_all_mc_charge->push_back(pythia.event[ib].charge());
				truth_all_mc_m->push_back(pythia.event[ib].m());
				truth_all_mc_pt->push_back(pythia.event[ib].pT());
				truth_all_mc_eta->push_back(pythia.event[ib].eta());
				truth_all_mc_phi->push_back(pythia.event[ib].phi());
				
				truth_all_isValid = true;
				
				///////////////////
				tree->Fill(); /////
				///////////////////
			}
		}
		if(iEvent%1000==0) cout << "Event: " << iEvent << endl;
	} // end for iEvent<prm.nEvents

	// Done. Print results.
	stop = clock(); // Stop timer
	t = (double) (stop-start)/CLOCKS_PER_SEC;

	// List changes.
	pythia.settings.listChanged();
	pythia.particleData.listChanged();
	pythia.statistics();

	cout << "\n" << "|----------------------------------------|" << endl;
	cout << "| CPU Runtime = " << t << " sec" << endl;
	cout << "|----------------------------------------|" << "\n" << endl;

	file = tree->GetCurrentFile();
	file->cd();
	tree->Write("", TObject::kOverwrite);
	file->Write();
	file->Close();
	
	ofstream* f = new ofstream("XSs_Z0_current.dat", ios_base::app);
	(*f) << sTitle << "\t\t"
		 << pythia.info.nTried() << "\t\t"
		 << pythia.info.nSelected() << "\t\t"
		 << pythia.info.nAccepted() << "\t\t"
		 << pythia.info.sigmaGen() << "\t\t"
		 << pythia.info.sigmaErr() << endl;
	f->close();
	delete f;

	return 0;
}

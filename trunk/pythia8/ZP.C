#include "pythiaROOT.h"
#include "all.h"

int main() {

	// Generator.
	Pythia pythia;
	//ParticleData& pdt = pythia.particleData;

	// Pick new random number seed for each run, based on clock.
	pythia.readString("Random:setSeed = on");
	pythia.readString("Random:seed = 0");

	// Process selection.
	 pythia.readString("NewGaugeBoson:ffbar2gmZZprime = on");
	pythia.readString("Zprime:gmZmode = 0"); // full gamma/Z0/Z' interference
	//Zprime:gmZmode = 0 ---> 6
	//0 = full gamma/Z0/Z' interference

	readParameters();


	cout << "|-------------------------" << endl;
	cout << "| Z' mass is: " << prm.newMass << endl;
	cout << "|-------------------------" << endl;
	stringstream strm;
	string sNewMass, sNewWidth, sNewLowBound, sNewHighBound, sId;

	// Manually set the mass and therefore the width 
	// and the phase space for the sampling
	strm.clear();
	strm << prm.newMass;
	strm >> sNewMass;
	strm.clear();
	//strm << prm.newMass / pdt.m0(5000023) * pdt.mWidth(5000023);
	strm << prm.newMass / 4000. * 140.;
	strm >> sNewWidth;

	strm.clear();
	strm << prm.mMin; // prm.newMass/4.;
	strm >> sNewLowBound;
	strm.clear();
	strm << prm.mMax; //prm.newMass*1.5; // prm.newMass*2.;
	strm >> sNewHighBound;

	strm.clear();
        strm << prm.idF;
        strm >> sId;

	// Feed in KK state information and other generation specifics.
	pythia.readString("32:m0 = " + sNewMass);
	//pythia.readString("32:mWidth = " + sNewWidth);
	pythia.readString("32:mMin = " + sNewLowBound);
	pythia.readString("32:mMax = " + sNewHighBound);
	pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
	pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);


	pythia.readString("32:onMode = off");
        pythia.readString("32:onIfAny = " + sId);
        pythia.readString("23:onMode = off"); // switch off all of the Z0 decay modes
        pythia.readString("23:onIfAny = " + sId); // switch on the Z0->mu-mu+ decay mode only


	// Initialize.
	pythia.init( 2212, 2212, 7000.);


	//ROOT
	TLorentzVector* pa = new TLorentzVector();
	TLorentzVector* pb = new TLorentzVector();
	
	string sDir   = "/data/hod/pythia8_ntuples/";
	string sTitle = prm.sName + sNewMass + prm.sFFbar + "_" + sNewLowBound + "M" + sNewHighBound;
	string sFileName = sDir + sTitle + ".root";
	TFile *file = TFile::Open(sFileName.c_str(),"recreate");
	TTree *tree = new TTree("tree","tree");
	float mHat;
	float qT;
	float ysystem;
	float cosThetaHE;
	float cosThetaCS;
	vector<int>*    index  = new vector<int>;
	vector<int>*    id     = new vector<int>;
	vector<double>* charge = new vector<double>;
	vector<double>* px     = new vector<double>;
	vector<double>* py     = new vector<double>;
	vector<double>* pz     = new vector<double>;
	vector<double>* E      = new vector<double>;
	vector<double>* m      = new vector<double>;
	vector<double>* y      = new vector<double>;
	vector<double>* pT     = new vector<double>;
	vector<double>* eta    = new vector<double>;
	vector<double>* phi    = new vector<double>;
	vector<double>* theta  = new vector<double>;
	tree->Branch("mHat",&mHat);
	tree->Branch("QT",&qT);
	tree->Branch("ySystem",&ysystem);
	tree->Branch("cosThetaHE",&cosThetaHE);
	tree->Branch("cosThetaCS",&cosThetaCS);
	tree->Branch("id",&id);
	tree->Branch("charge",&charge);
	tree->Branch("px",&px);
	tree->Branch("py",&py);
	tree->Branch("pz",&pz);
	tree->Branch("E",&E);
	tree->Branch("m",&m);
	tree->Branch("y",&y);
	tree->Branch("pT",&pT);
	tree->Branch("eta",&eta);
	tree->Branch("phi",&phi);
	tree->Branch("theta",&theta);

	vector<int> moms;

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
			
		id->clear();
		charge->clear();
		px->clear();
		py->clear();
		pz->clear();
		E->clear();
		m->clear();
		y->clear();
		pT->clear();
		eta->clear();
		phi->clear();
		theta->clear();
		
		int iZ = 0;
		for (int i=0 ; i<10 ; ++i)
		{
			if(pythia.event[i].id()==32)
			{
				iZ = i;
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
			
				id->push_back(pythia.event[i].id());
				charge->push_back(pythia.event[i].charge());
				px->push_back(pythia.event[i].px());
				py->push_back(pythia.event[i].py());
				pz->push_back(pythia.event[i].pz());
				E->push_back(pythia.event[i].e());
				m->push_back(pythia.event[i].m());
				y->push_back(pythia.event[i].y());
				pT->push_back(pythia.event[i].pT());
				eta->push_back(pythia.event[i].eta());
				phi->push_back(pythia.event[i].phi());
				theta->push_back(pythia.event[i].theta());
			} // end if final fermion
		} // end for event.size()
		
		if(index->size()>1)
		{
			pa->SetPtEtaPhiM( pT->at(0), eta->at(0), phi->at(0), m->at(0));
			pb->SetPtEtaPhiM( pT->at(1), eta->at(1), phi->at(1), m->at(1));
			float ca = charge->at(0);
			float cb = charge->at(1);
			
			mHat       = imass(pa,pb);
			qT         = QT(pa,pb);
			ysystem    = ySystem(pa,pb);
			cosThetaHE = cosThetaBoost(pa,ca,pb,cb);
			cosThetaCS = cosThetaCollinsSoper(pa,ca,pb,cb);
				
			///////////////////
			tree->Fill(); /////
			///////////////////
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
	
	ofstream* f = new ofstream("XSs_ZP_current.dat", ios_base::app);
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

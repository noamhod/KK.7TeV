// #include "pythiaROOT.h"
// #include "all.h"
#include "../include/rawStd.h"
#include "../include/rawROOT.h"
#include "../include/enums.h"
#include "../include/logs.h"
#include "../include/style.h"
#include "../include/bins.h"
#include "../include/histos.h"
#include "../include/fkinematics.h"
#include "../include/units.h"
// #include "../include/couplings.h"
// #include "../include/width.h"
// #include "../include/helicity.h"
// #include "../include/kFactors.h"
// #include "../include/integrals.h"
// #include "../include/lhapdf.h"

// using namespace couplings;
// using namespace width;
// using namespace helicity;
// using namespace kFactors;
// using namespace lhapdf;

#include "Pythia.h"
using namespace Pythia8;

//////////////////////////////////////////////////////////
// to compile this code, run "source compile.sh theory" //
//////////////////////////////////////////////////////////


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

inline double gVE6(unsigned int id, double thetaE6)
{
	double gV = 0.;
	
	if     (id==12 || id==14 || id==16) gV =1./6.*(sqrt(10.)*cos(thetaE6)-3.*sqrt(6.)*sin(thetaE6))*sqrt(sw2); // neutrinos
	else if(id==11 || id==13 || id==15) gV = -4./sqrt(6.)*sin(thetaE6)*sqrt(sw2); // charged leptons
	else if(id==2  || id==4  || id==6)  gV = 0.; // up-type  quarks
	else if(id==1  || id==3  || id==5)  gV = +4./sqrt(6.)*sin(thetaE6)*sqrt(sw2); // down-type  quarks
	else _FATAL("id="+_s(id)+" is unknown");
	return gV;
}

inline double gAE6(unsigned int id, double thetaE6)
{
	double gA = 0.;
	if     (id==12 || id==14 || id==16) gA = 1./6.*(sqrt(10.)*cos(thetaE6)-3.*sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==11 || id==13 || id==15) gA = 1./3.*(sqrt(10.)*cos(thetaE6)-sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==2  || id==4  || id==6)  gA = 1./3.*(sqrt(10.)*cos(thetaE6)+sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else if(id==1  || id==3  || id==5)  gA = 1./3.*(sqrt(10.)*cos(thetaE6)-sqrt(6.)*sin(thetaE6))*sqrt(sw2);
	else _FATAL("id="+_s(id)+" is unknown");
	return gA;
}

int main(int argc, char *argv[])
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// usage: ./theory  model[DY/ZP/KK]  submodel[psi/chi/eta/I]  channel[mumu/ee]  mBSM[in GeV]  nEvents[integer>0]  minPhaseSpace[in GeV]  maxPhaseSpace[in GeV] ////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "argc = " << argc << endl; 
	for(int i=0; i < argc; i++) cout << "argv[" << i << "] = " << argv[i] << endl; 

	if(argc!=8)
	{
		_ERROR("argc!=7, exitting now");
		_ERROR("usage: ./theory  model[DY/ZP/KK]  channel[mumu/ee]  mBSM[in GeV]  nEvents[integer>0]  minPhaseSpace[in GeV]  maxPhaseSpace[in GeV]");
		exit(-1);
	}
	
	// variables...
	double mZ0      = 91.18760;
	string model    = argv[1];
	string submodel = argv[2];
	string channel  = argv[3];
	double mBSM     = validate_double(argv[4]);
	string smBSM    = argv[4];
	int nEvents     = validate_int(argv[5]);
	double minPhaseSpace = validate_double(argv[6]);
	double maxPhaseSpace = validate_double(argv[7]);
	double mKK1st = sqrt(mBSM*mBSM+mZ0*mZ0);
	
	string sNewLowBound  = _s(minPhaseSpace);
	string sNewHighBound = _s(maxPhaseSpace);
	string sIDout        = (channel=="mumu") ? "13" : "11";
	int    iIDout        = (channel=="mumu") ?  13  :  11;
	string sNewMass      = _s(mBSM);

	// Generator.
	Pythia pythia;

	// PDF initialization
	string pdfSet = "MRSTMCal.LHgrid";
	int pdfMember_int = 0;
	string pdfMember  = "0";
	pythia.readString("PDF:useLHAPDF = on");
	pythia.readString("PDF:LHAPDFset = " + pdfSet);
	pythia.readString("PDF:LHAPDFmember = " + pdfMember);
	
	// Allow extrapolation of PDF's beyond x and Q2 boundaries, at own risk.
	// Default behaviour is to freeze PDF's at boundaries.
	pythia.readString("PDF:extrapolateLHAPDF = on");

	// Need to change pT0Ref depending on choice of PDF.
	// One possibility: retune to same <n_charged>.
	//pythia.readString("MultipleInteractions:pT0Ref = 10");
	
	// Pick new random number seed for each run, based on clock.
	pythia.readString("Random:setSeed = on");
	pythia.readString("Random:seed = 0");

	// Process selection.
	if(model=="KK")
	{
		if     (channel=="mumu") pythia.readString("ExtraDimensionsTEV:ffbar2mu+mu- = on");
		else if(channel=="ee")   pythia.readString("ExtraDimensionsTEV:ffbar2e+e-   = on");
		
		cout << "KK mass is: " << mBSM << endl;
		
		// set the mass and therefore the width 
		string sNewKKMass    = _s(mBSM);
		string sNewWidth     = _s(mBSM / 4000. * 240.);
		
		// Feed in KK state information and other generation specifics.
		// pythia.readString("5000023:m0 = " + _s(mKK1st));
		// pythia.readString("5000023:mWidth = " + sNewWidth);
		// pythia.readString("5000023:mMin = " + sNewLowBound);
		// pythia.readString("5000023:mMax = " + sNewHighBound);
		pythia.readString("5000023:isResonance = false");
		pythia.readString("ExtraDimensionsTEV:gmZmode = 3"); // 0=(gm+Z), 1=(gm), 2=(Z), 3=(gm+Z+gmKK+ZKK), 4=(Z+gmKK), 5=(Z+ZKK), 6=(gmKK+ZKK)
		pythia.readString("ExtraDimensionsTEV:nMax = 10"); // min=0, max=100, default=10
		pythia.readString("ExtraDimensionsTEV:mStar = " + sNewKKMass);
		pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
		pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);
	}
	else if(model=="ZP") 
	{
		pythia.readString("NewGaugeBoson:ffbar2gmZZprime = on");
	
		cout << "Z' mass is: " << mBSM << endl;

		if(submodel=="ssm") _INFO("running with SSM");
		else
		{
			_INFO("running with E6 model: "+submodel);
			
			double thetaE6 = 0.;
			if     (submodel=="psi") thetaE6 = 0.;
			else if(submodel=="chi") thetaE6 = -pi/2.;
			else if(submodel=="eta") thetaE6 = atan(-sqrt(5./3.))+pi/2.; //+asin(sqrt(3./8.));
			else if(submodel=="I")   thetaE6 = -asin(sqrt(5./8.));
			
			string gVnu = _s(gVE6(12,thetaE6));
			string gVe  = _s(gVE6(11,thetaE6));
			string gVu  = _s(gVE6(2,thetaE6));
			string gVd  = _s(gVE6(1,thetaE6));
			string gAnu = _s(gAE6(12,thetaE6));
			string gAe  = _s(gAE6(11,thetaE6));
			string gAu  = _s(gAE6(2,thetaE6));
			string gAd  = _s(gAE6(1,thetaE6));
			pythia.readString("Zprime:vd   = "+gVd);
			pythia.readString("Zprime:ad   = "+gAd);
			pythia.readString("Zprime:vu   = "+gVu);
			pythia.readString("Zprime:au   = "+gAu);
			pythia.readString("Zprime:ve   = "+gVe);
			pythia.readString("Zprime:ae   = "+gAe);
			pythia.readString("Zprime:vnue = "+gVnu);
			pythia.readString("Zprime:anue = "+gAnu);
		}
		
		pythia.readString("32:m0 = " + sNewMass);
		//pythia.readString("32:mWidth = " + sNewWidth);
		// pythia.readString("32:mMin = " + sNewLowBound);
		// pythia.readString("32:mMax = " + sNewHighBound);
		pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
		pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);
		pythia.readString("32:onMode = off"); // switch on the Z'->mu-mu+ decay mode only
		pythia.readString("32:onIfAny = " + sIDout);
	}
	else if(model=="DY")
	{
		pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
	
		//pythia.readString("WeakZ0:gmZmode = 0"); // full gamma/Z0 interference
		pythia.readString("23:onMode = off"); // switch off all of the Z0 decay modes
		pythia.readString("23:onIfAny = " + sIDout); // switch on the Z0->ffbar decay mode only
		// pythia.readString("23:mMin = " + sNewLowBound);
		// pythia.readString("23:mMax = " + sNewHighBound);
		pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
		pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);
	}
	else
	{
		cout << "unknown model = " << model << endl;
		return 0;
	}
	
	// Initialize.
	pythia.init( 2212, 2212, 7000.);

	// list changes before the run
	pythia.settings.listChanged();
	pythia.particleData.listChanged();
	
	
	//ROOT
	TLorentzVector* pa = new TLorentzVector();
	TLorentzVector* pb = new TLorentzVector();
	string sDir   = "/storage/t3_data/hod/2011/pythia8_ntuples_2012/";
	string sTitle = "";
	if(model=="ZP") sTitle = model + "_" + submodel + "_mBSM" + sNewMass + "_" + channel + "_" + sNewLowBound + "M" + sNewHighBound;
	if(model=="KK") sTitle = model + "_mBSM" + sNewMass + "_" + channel + "_" + sNewLowBound + "M" + sNewHighBound;
	if(model=="DY") sTitle = model + "_" + channel + "_" + sNewLowBound + "M" + sNewHighBound;
	string sFileName = sDir + sTitle + ".root";
	TFile *file = TFile::Open(sFileName.c_str(),"recreate");
	TDirectory* tDir = file->mkdir("truth");
	tDir->cd();
	TTree *tree = new TTree("truth_tree","truth_tree");
	
	
	bool truth_all_isValid;
	
	double truth_x1;
	double truth_x2;
	double truth_pdf1;
	double truth_pdf2;
	double truth_QFac;
	double truth_Q2Fac;
	double truth_QRen;
	double truth_Q2Ren;
	double truth_alphaS;
	double truth_alphaEM;
	double truth_y;
	int truth_id1;
	int truth_id2;
	double truth_mHat;
	double truth_m3Hat;
	double truth_m4Hat;
	double truth_sHat;
	double truth_tHat;
	double truth_uHat;
	double truth_pTHat;
	double truth_thetaHat;
	double truth_phiHat;
	
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
	
	tree->Branch( "truth_x1", &truth_x1 );
	tree->Branch( "truth_x2", &truth_x2 );
	tree->Branch( "truth_pdf1", &truth_pdf1 );
	tree->Branch( "truth_pdf2", &truth_pdf2 );
	tree->Branch( "truth_QFac", &truth_QFac );
	tree->Branch( "truth_Q2Fac", &truth_Q2Fac );
	tree->Branch( "truth_QRen", &truth_QRen );
	tree->Branch( "truth_Q2Ren", &truth_Q2Ren );
	tree->Branch( "truth_alphaS", &truth_alphaS );
	tree->Branch( "truth_alphaEM", &truth_alphaEM );
	tree->Branch( "truth_y", &truth_y );
	tree->Branch( "truth_id1", &truth_id1 );
	tree->Branch( "truth_id2", &truth_id2 );
	tree->Branch( "truth_mHat", &truth_mHat );
	tree->Branch( "truth_m3Hat", &truth_m3Hat );
	tree->Branch( "truth_m4Hat", &truth_m4Hat );
	tree->Branch( "truth_sHat", &truth_sHat );
	tree->Branch( "truth_tHat", &truth_tHat );
	tree->Branch( "truth_uHat", &truth_uHat );
	tree->Branch( "truth_pTHat", &truth_pTHat );
	tree->Branch( "truth_thetaHat", &truth_thetaHat );
	tree->Branch( "truth_phiHat", &truth_phiHat );
	
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
	int mod = (int)(nEvents/10.);
	for (int iEvent=0 ; iEvent<nEvents ; ++iEvent)
	{
		if (!pythia.next()) continue;
		if (iEvent < 1)   {pythia.info.list(); pythia.event.list();}
		//if (iEvent < 1)   {pythia.info.list();}
		//if (iEvent%10==0) {pythia.process.list();}
		
		truth_x1       = pythia.info.x1();
		truth_x2       = pythia.info.x2();
		truth_pdf1     = pythia.info.pdf1();
		truth_pdf2     = pythia.info.pdf2();
		truth_QFac     = pythia.info.QFac();
		truth_Q2Fac    = pythia.info.Q2Fac();
		truth_QRen     = pythia.info.QRen();
		truth_Q2Ren    = pythia.info.Q2Ren();
		truth_alphaS   = pythia.info.alphaS();
		truth_alphaEM  = pythia.info.alphaEM();
		truth_y        = pythia.info.y();
		truth_id1      = pythia.info.id1();
		truth_id2      = pythia.info.id2();
		truth_mHat     = pythia.info.mHat();
		truth_m3Hat    = pythia.info.m3Hat();
		truth_m4Hat    = pythia.info.m4Hat();
		truth_sHat     = pythia.info.sHat();
		truth_tHat     = pythia.info.tHat();
		truth_uHat     = pythia.info.uHat();
		truth_pTHat    = pythia.info.pTHat();
		truth_thetaHat = pythia.info.thetaHat();
		truth_phiHat   = pythia.info.phiHat();
		
		
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
			if(pythia.event[i].id()==5000023 || pythia.event[i].id()==23 || pythia.event[i].id()==32)
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
		for(int i=0 ; i<pythia.event.size() ; ++i)
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
			
			if(isfinal  &&  isHardProcsess  &&  idf*idf==iIDout*iIDout  &&  isZ)
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
		if(iEvent%mod==0) cout << "Event: " << iEvent << endl;
	} // end for iEvent<nEvents

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
	tDir->cd();
	tree->Write("", TObject::kOverwrite);
	file->Write();
	file->Close();

	TString tsFileName = (TString)sFileName;
	tsFileName.ReplaceAll(".root",".dat");
	string summaryFileNmae = (string)tsFileName;
	ofstream* f = new ofstream(summaryFileNmae.c_str(), ios_base::app);
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

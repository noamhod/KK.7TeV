#include "pythiaROOT.h"
#include "all.h"

int main(int argc, char *argv[])
{
	cout << "argc = " << argc << endl; 
	for(int i=0; i < argc; i++) cout << "argv[" << i << "] = " << argv[i] << endl; 

	if(argc!=5)
	{
		_ERROR("argc!=3, exitting now");
		exit(-1);
	}
	
	// variables...
	double minPhaseSpace = 70.;
	double maxPhaseSpace = 7000.;
	double xsZP    = 0.;
	double dxsZP   = 0.;
	double mZ0     = 91.18760;
	double mZP     = validate_double(argv[1]);
	string fname   = argv[2];
	string channel = argv[3];
	int nEvents    = validate_int(argv[4]);
	
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
	pythia.readString("NewGaugeBoson:ffbar2gmZZprime = on");
    pythia.readString("Zprime:gmZmode = 3"); // only Z'

	cout << "Z' mass is: " << mZP << endl;
	
	// set the mass and therefore the width 
	string sNewZPMass    = _s(mZP);
	string sNewWidth     = _s(mZP / 4000. * 140.);
	string sNewLowBound  = _s(minPhaseSpace);
	string sNewHighBound = _s(maxPhaseSpace);
	string sIDout        = (channel=="mumu")?"13":"11";

	pythia.readString("32:m0 = " + sNewZPMass);
	//pythia.readString("32:mWidth = " + sNewWidth);
	pythia.readString("32:mMin = " + sNewLowBound);
	pythia.readString("32:mMax = " + sNewHighBound);
	pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
	pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);
	pythia.readString("32:onMode = off"); // switch on the Z'->mu-mu+ decay mode only
	pythia.readString("32:onIfAny = " + sIDout);
	pythia.readString("23:onMode = off"); // switch off all of the Z0 decay modes
	pythia.readString("23:onIfAny = " + sIDout); // switch on the Z0->mu-mu+ decay mode only
	
	// Initialize.
	pythia.init( 2212, 2212, 7000.);

	// list changes before the run
	pythia.settings.listChanged();
	pythia.particleData.listChanged();
	
	// Begin event loop. Generate event. Skip if error. List first one.
	int mod = (int)(nEvents/10.);
	for(int iEvent=0 ; iEvent<nEvents ; ++iEvent)
	{
		if (!pythia.next()) continue;
		if(iEvent%mod==0) cout << "Event: " << iEvent << endl;
	}
	
	xsZP = pythia.info.sigmaGen();
	dxsZP = pythia.info.sigmaErr();

	ofstream* f = new ofstream(fname.c_str());
	(*f) << mZP << "\t" << xsZP << "\t" << dxsZP << endl;
	f->close();
	delete f;
	
	return 0;
}

#include "pythiaROOT.h"
#include "all.h"

int main(int argc, char *argv[])
{
	cout << "argc = " << argc << endl; 
	for(int i=0; i < argc; i++) cout << "argv[" << i << "] = " << argv[i] << endl; 

	if(argc!=6)
	{
		_ERROR("argc!=6, exitting now");
		exit(-1);
	}
	
	// variables...
	double minPhaseSpace = validate_double(argv[1]);
	double maxPhaseSpace = validate_double(argv[2]);
	double xsZ0    = 0.;
	double dxsZ0   = 0.;
	double mZ0     = 91.18760;
	string fname   = argv[3];
	string channel = argv[4];
	int nEvents    = validate_int(argv[5]);
	
	 // set the mass and therefore the width 
	string sNewLowBound  = _s(minPhaseSpace);
	string sNewHighBound = _s(maxPhaseSpace);
	string sIDout        = (channel=="mumu")?"13":"11";

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

	string sprocName = "";


	/*
	// Z0(internal) Process selection.
	sprocName = "Z0";
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
        pythia.readString("23:onMode = off"); // switch off all of the Z0 decay modes
        pythia.readString("23:onIfAny = 13"); // switch on the Z0->mu-mu+ decay mode only
	pythia.readString("23:onMode = off"); // switch off all of the Z0 decay modes
	pythia.readString("23:onIfAny = " + sIDout); // switch on the Z0->mu-mu+ decay mode only	
	*/

	/*
	// KK Process selection.
	sprocName = "KK";
	double mKK     = 2000.;
        double mKK1st = sqrt(mKK*mKK+mZ0*mZ0);	
	string sNewKKMass = _s(mKK);
        string sNewMass   = _s(mKK1st);
        string sNewWidth  = _s(mKK1st / 4000. * 240.);
	pythia.readString("ExtraDimensionsTEV:ffbar2mu+mu- = on");
        pythia.readString("5000023:isResonance = false");
        pythia.readString("ExtraDimensionsTEV:gmZmode = 3"); // 0=(gm+Z), 1=(gm), 2=(Z), 3=(gm+Z+gmKK+ZKK), 4=(Z+gmKK), 5=(Z+ZKK), 6=(gmKK+ZKK)
        pythia.readString("ExtraDimensionsTEV:nMax = 100"); // min=0, max=100, default=10
	pythia.readString("ExtraDimensionsTEV:mStar = " + sNewKKMass);
        pythia.readString("5000023:m0 = " + sNewKKMass);
        pythia.readString("5000023:mWidth = " + sNewWidth);
        pythia.readString("5000023:mMin = " + sNewLowBound);
        pythia.readString("5000023:mMax = " + sNewHighBound);
        pythia.readString("5000023:isResonance = false");
	*/

	// ZP Process selection.
        sprocName = "ZP";
	double mZP = 2000.;
	string sNewZPMass    = _s(mZP);
        string sNewWidth     = _s(mZP / 500. * 14.54029);
        pythia.readString("NewGaugeBoson:ffbar2gmZZprime = on");
        pythia.readString("Zprime:gmZmode = 0"); // full Z'
	pythia.readString("32:m0 = " + sNewZPMass);
        //pythia.readString("32:mWidth = " + sNewWidth);
        pythia.readString("32:mMin = " + sNewLowBound);
        pythia.readString("32:mMax = " + sNewHighBound);
        pythia.readString("32:onMode = off"); // switch on the Z'->mu-mu+ decay mode only
        pythia.readString("32:onIfAny = " + sIDout);


	// phase space
	pythia.readString("PhaseSpace:mHatMin = " + sNewLowBound);
	pythia.readString("PhaseSpace:mHatMax = " + sNewHighBound);
	
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
	
	xsZ0 = pythia.info.sigmaGen();
	dxsZ0 = pythia.info.sigmaErr();

	ofstream* f = new ofstream((sprocName+"_"+fname).c_str());
	(*f) << minPhaseSpace << "-" << maxPhaseSpace << "\t" << xsZ0 << "\t" << dxsZ0 << endl;
	f->close();
	delete f;
	
	return 0;
}

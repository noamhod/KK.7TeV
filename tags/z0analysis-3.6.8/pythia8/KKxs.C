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
	double xsKK    = 0.;
	double dxsKK   = 0.;
	double mZ0     = 91.18760;
	double mKK     = validate_double(argv[1]);
	string fname   = argv[2];
	string channel = argv[3];
	int nEvents    = validate_int(argv[4]);
	double mKK1st = sqrt(mKK*mKK+mZ0*mZ0);
	
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
	if     (channel=="mumu") pythia.readString("ExtraDimensionsTEV:ffbar2mu+mu- = on");
	else if(channel=="ee")   pythia.readString("ExtraDimensionsTEV:ffbar2e+e-   = on");
	cout << "KK mass is: " << mKK << endl;
	
	// set the mass and therefore the width 
	string sNewKKMass    = _s(mKK);
	string sNewMass      = _s(mKK1st);
	string sNewWidth     = _s(mKK1st / 4000. * 240.);
	string sNewLowBound  = _s(minPhaseSpace);
	string sNewHighBound = _s(maxPhaseSpace);
	
	// Feed in KK state information and other generation specifics.
	pythia.readString("5000023:m0 = " + sNewMass);
	pythia.readString("5000023:mWidth = " + sNewWidth);
	pythia.readString("5000023:mMin = " + sNewLowBound);
	pythia.readString("5000023:mMax = " + sNewHighBound);
	pythia.readString("5000023:isResonance = false");
	pythia.readString("ExtraDimensionsTEV:gmZmode = 6"); // 0=(gm+Z), 1=(gm), 2=(Z), 3=(gm+Z+gmKK+ZKK), 4=(Z+gmKK), 5=(Z+ZKK), 6=(gmKK+ZKK)
	pythia.readString("ExtraDimensionsTEV:nMax = 10"); // min=0, max=100, default=10
	pythia.readString("ExtraDimensionsTEV:mStar = " + sNewKKMass);
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
	
	xsKK = pythia.info.sigmaGen();
	dxsKK = pythia.info.sigmaErr();

	ofstream* f = new ofstream(fname.c_str());
	(*f) << mKK << "\t" << xsKK << "\t" << dxsKK << endl;
	f->close();
	delete f;
	
	return 0;
}
